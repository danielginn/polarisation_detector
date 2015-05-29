/* 
 *  ======== ce_api.c ========
 *  The CodecEngine-using part of the Linux application, separated from the
 *  rest of the Linux app to simplify the interface towards the rest of
 *  the main app. CodecEngine API and especially APIs for individual codecs
 *  are much more capable than what we need for simple (dummy) video
 *  encode/decode.
 */

#include "ce_api.h"
/* include various CodecEngine header files */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/CERuntime.h>
// TraceUtil should not be used anymore on CE 3.X
//#include <ti/sdo/ce/utils/trace/TraceUtil.h>
#include <ti/sdo/ce/image1/imgenc1.h>
#include <dsp/vrmcodec/vrmcodec.h>


#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#include <cstdlib>

// Codec Engine OSAL
extern "C" Void Memory_registerContigBuf(UInt32 virtualAddress,UInt32 sizeInBytes, UInt32 physicalAddress);
extern "C" Void Memory_unregisterContigBuf(UInt32 virtualAddress, UInt32 sizeInBytes);

// Forward declarations of internal functions 
void vrmUsbCamStaticCallbackHandler(VRmStaticCallbackType f_type, void* fp_user_data, const void* fcp_callback_params);

// Define names of engine/codecs to use 
static String engine_name= String("bin/server");
static String vrmcodec_name= String("vrmcodec");

// Define handles to use 
Engine_Handle engine_handle  = NULL;
IMGENC1_Handle vrmcodec_handle = NULL;

Memory_AllocParams mem_params;

// Callback function that is called from within VRmUsbCam API.
// We currently just pass through memory management hooks
void vrmUsbCamStaticCallbackHandler(VRmStaticCallbackType f_type, void* fp_user_data, const void* fcp_callback_params)
{
	if (f_type==VRM_STATIC_CALLBACK_TYPE_CMEM_ALLOCATION_CHANGE)
	{
		const VRmStaticCallbackCMemAllocationChangeParams* lp_params= 
			(const VRmStaticCallbackCMemAllocationChangeParams*) fcp_callback_params;
		if (lp_params->m_allocate){
			Memory_registerContigBuf((UInt32)lp_params->mp_virtual, lp_params->m_size , (UInt32)lp_params->mp_physical);
		}
		else{
			Memory_unregisterContigBuf((UInt32)lp_params->mp_virtual, lp_params->m_size);
		}
	}
}


char* DspAllocMemory(int bufSize)
{
    char *buf;

	mem_params= Memory_DEFAULTPARAMS;
	mem_params.type= Memory_CONTIGHEAP;
	mem_params.flags= Memory_CACHED;

	buf = (char *)Memory_alloc(bufSize, &mem_params);

    if (buf == NULL) {
        printf("DspAllocImage(): failed to allocate contiguous memory block.\n");
    }

    return (buf);
}

void DspFreeMemory(char *buf, int bufSize)
{
	Memory_free(buf, bufSize,&mem_params);
}


int DspInit()
{  
	Engine_Error err;
	
	// Register callbacks at VRmUsbCam
	VRmUsbCamRegisterStaticCallback(vrmUsbCamStaticCallbackHandler,0);

	// Initialize Codec Engine runtime first 
	CERuntime_init();

	 // Activate DSP trace collection thread 
    	//TraceUtil_start(engine_name);

    // Reset, load, and start DSP Engine 
    if ((engine_handle = Engine_open(String(engine_name), NULL, &err)) == NULL) {
		printf("DspInit(): can't open engine %s error code: %d\n", engine_name, err);
        return -1;
    }

	// Register for CRT destruction
	// Note: this has to be done after Engine_Open to avoid problems during deinitialization
    atexit(DspExit);

	// Allocate and initialize vrmcodec on the engine
    	vrmcodec_handle = IMGENC1_create(engine_handle, vrmcodec_name, NULL);
    	if (vrmcodec_handle == NULL) {
            printf("DspInit(): can't open codec %s\n", vrmcodec_name);
    		return -1;
    	}
	return 0;
}

void DspExit()
{

	if (vrmcodec_handle != NULL) {
			IMGENC1_delete(vrmcodec_handle);
			vrmcodec_handle= NULL;
	}

	if (engine_handle != NULL) {
        Engine_close(engine_handle);
		engine_handle= NULL;
    }

	// close tracing thread
	//TraceUtil_stop();  

	CERuntime_exit();

	// Unregister callbacks at VRmUsbCam
	VRmUsbCamUnregisterStaticCallback(vrmUsbCamStaticCallbackHandler);

}

int DspConvertImage(dsp_cmd cmd, VRmImage *vrm_source, VRmImage *vrm_target)
{
	int i;

	VRMCODEC_InArgs	inArgs;
	inArgs.size = sizeof(inArgs);

	VRMCODEC_OutArgs	outArgs;
	outArgs.size = sizeof(outArgs);

	void* p_source_img_handle= vrm_source->mp_private;
	void* p_target_img_handle= vrm_target->mp_private;

	const VRmBYTE* source_lut;
	VRmDWORD lut_size;
	if(!VRmUsbCamGetImageLut(vrm_source, &source_lut, &lut_size))
	{
		printf("DspConvertImage(): VRmUsbCamGetImageLut(vrm_source, &source_lut, &lut_size) failed\n");
		return -1;
	}

	// define the arrays describing I/O buffers and their sizes
	XDM1_BufDesc sourceDesc;

    sourceDesc.descs[0].buf			= (XDAS_Int8*)vrm_source->mp_buffer;
	if(!VRmUsbCamGetImageBufferSize(vrm_source, (VRmDWORD*)&sourceDesc.descs[0].bufSize))
	{
		printf("VRmUsbCam Error1: %s", VRmUsbCamGetLastError());
		return -1;
	}

	sourceDesc.descs[1].buf			= (XDAS_Int8*)p_source_img_handle;
	sourceDesc.descs[1].bufSize		= *(XDAS_Int32*)p_source_img_handle;

	sourceDesc.descs[2].buf			= (XDAS_Int8*)p_target_img_handle;
	sourceDesc.descs[2].bufSize		= *(XDAS_Int32*)p_target_img_handle;

	sourceDesc.numBufs				= 3;

	if( source_lut != NULL )
	{
		sourceDesc.descs[3].buf			= (XDAS_Int8*)source_lut;
		sourceDesc.descs[3].bufSize		= (XDAS_Int32)lut_size;
		sourceDesc.numBufs++;
	}

	XDM1_BufDesc targetDesc;
	targetDesc.numBufs				= 1;
    targetDesc.descs[0].buf			= (XDAS_Int8*)vrm_target->mp_buffer;
	if(!VRmUsbCamGetImageBufferSize(vrm_target, (VRmDWORD*)&targetDesc.descs[0].bufSize))
	{
		printf("VRmUsbCam Error2: %s", VRmUsbCamGetLastError());
		return -1;
	}

	// ARM/DSP cache handling
	if(cmd != PROC_WAIT)
	{
		for(i=1;i<sourceDesc.numBufs;i++)
		{
			CMEM_cacheWb((void*)sourceDesc.descs[i].buf,sourceDesc.descs[i].bufSize);
		}
        CMEM_cacheInv((void*)targetDesc.descs[0].buf,targetDesc.descs[0].bufSize);
	}

    // encode the frame, pass addresses of the structures we populated above
	Int32 status=-1;
	switch(cmd)
	{
	case PROC_WAIT:
		status= IMGENC1_processWait(vrmcodec_handle, &sourceDesc, &targetDesc, (IMGENC1_InArgs*)&inArgs, (IMGENC1_OutArgs*)&outArgs, IMGENC1_FOREVER);
		break;
	case PROC_ASYNC:
		status= IMGENC1_processAsync(vrmcodec_handle, &sourceDesc, &targetDesc, (IMGENC1_InArgs*)&inArgs, (IMGENC1_OutArgs*)&outArgs);
		break;
	case PROC_SYNC:
		status= IMGENC1_process(vrmcodec_handle, &sourceDesc, &targetDesc, (IMGENC1_InArgs*)&inArgs, (IMGENC1_OutArgs*)&outArgs);
		break;
	default:
		printf("DspconvertImage(): Unknown command %d\n", cmd);
	}

	switch(status)
	{
	case IMGENC1_EOK:
		break;
	case IMGENC1_EFAIL:
		printf("DspconvertImage(): convertImage error: %s\n", outArgs.cvt_err_string);
		return status;
	default:
		printf("DspconvertImage(): IMGENC1_processXXX() failed, status = 0x%lx, extendedError = 0x%lx\n", status, outArgs.extendedError);
		return status;
	}

	vrm_target->m_time_stamp= vrm_source->m_time_stamp;

    return 0;
}

