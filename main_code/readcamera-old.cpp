// ==============================================================================================
// This file is part of the VRmagic DSP Camera Demo Application
// ==============================================================================================
// Camera Reading / Main Loop
// ----------------------------------------------------------------------------------------------

#include "header.h"
#include "vrmusbcam2.h"
#include <sstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <string>

#include <../ce_api/ce_api.h>

bool g_quit= false;

// Just for convenience
using namespace std;

// small helper macro to check function for success and call LogExit when function fails
#define VRM_EXEC_AND_CHECK(function)\
{\
	if (VRM_SUCCESS!=function)\
	LogExit();\
}

void readCamera(VRmUsbCamDevice device, VRmDWORD port, VRmImageFormat target_format, VRmRectI source_cropping_region)
{	
	// frames per second, shown on S-Video and on console
	float fps= 0;

	// the source image
	VRmImage* p_source_img = 0;

    // sub-image of the source img containing the region that is displayed
    VRmImage* p_cropped_source_img=0;

	// the target buffers
	VRmImage* p_target_img[2]= {0,0};

	bool first_loop_run= true;
	VRmDWORD frame_counter= 0;
	int target_buffer_no= 0;
	
	if(!VRmUsbCamResetFrameCounter(device))
		LogExit();

	// start grabber at first
	if(!VRmUsbCamStart(device))
		LogExit();

	// ------------------------------------------------------------------------
	// main loop: read images and draw them to screen
	// ------------------------------------------------------------------------

	cout << "Reading from camera..." << endl;
	int i = 0;
	do
	{
		// Lock next (raw) image for read access, convert it to the desired
		// format and unlock it again, so that grabbing can go on
		VRmDWORD frames_dropped;
		if(!VRmUsbCamLockNextImageEx(device,port,&p_source_img,&frames_dropped))
		{
			// in case of an error, check for trigger timeouts and trigger stalls.
			// both can be recovered, so continue. otherwise exit the app
			if(VRmUsbCamLastErrorWasTriggerTimeout())
				cerr << "trigger timeout" << endl;
			else if(VRmUsbCamLastErrorWasTriggerStall())
				cerr << "trigger stall" << endl;
			else
				LogExit();
		}

		// Note: p_source_img may be null in case a recoverable error
		// (like a trigger timeout) occured.
		if (p_source_img)
		{		
			// crop source image, such that output fits to screen
			if(!VRmUsbCamCropImage(&p_cropped_source_img,p_source_img,&source_cropping_region))
				LogExit();;
			
			// Lock the dfb off-screen buffer to output the image to the screen.
			// The screen_buffer_pitch variable will receive the pitch (byte size of 
			// one line) of the buffer.l;
			VRmDWORD screen_buffer_pitch;
			VRmBYTE* p_screen_buffer=LockBuffer(screen_buffer_pitch,target_buffer_no);

			// Now, wrap a VRmImage around the locked screen buffer to receive the converted image
			if(!VRmUsbCamSetImage(&p_target_img[target_buffer_no],target_format,p_screen_buffer,screen_buffer_pitch))
				LogExit();

			// Start the DSP conversion of the image 
			// Note that this is an asynchronous call, i.e. the conversion is by no means 
			// finished when the function returns
			if(DspConvertImage(PROC_ASYNC, p_cropped_source_img, p_target_img[target_buffer_no]))
			{
				cout << "Encoding of buffer failed!" << endl; 
				exit(-1);
			}

			// Show image on screen
			// At first loop run we have no image to show, so skip this step
			if(first_loop_run)
				first_loop_run= false;
			else
			{
				// Give the off-screen buffer back to dfb...
				UnlockBuffer(!target_buffer_no);
				// ...and update the screen
				Update(!target_buffer_no,fps);

				// Save image to file
				char fileName[255];
				if(i<10){
					sprintf(fileName, "image_00%d.png", i);
				}
				else if(i<100){
					sprintf(fileName, "image_0%d.png", i);
				}
				else{
					sprintf(fileName, "image_%d.png", i);
				}
				cout << "Saving image: " << i << endl;
				VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(fileName, p_target_img[target_buffer_no], 0));
			}
			
			// see, if we had to drop some frames due to data transfer stalls. if so,
			// output a message
			if (frames_dropped)
				cout << "- " << frames_dropped <<  " frame(s) dropped -" << endl;

			// Show a frame rate on screen, which is updated every tenth image
			frame_counter++;
			if(frame_counter >= 10)
			{
				if(!VRmUsbCamGetPropertyValueF(device,VRM_PROPID_GRAB_FRAMERATE_AVERAGE_F,&fps))
					LogExit();
				std::cout << "\rFrames/sec: " << fps;
				fflush(stdout);
				frame_counter= 0;
			}
	
			// Wait until DSP processing of the new image has been finished
			if(DspConvertImage(PROC_WAIT, p_cropped_source_img, p_target_img[target_buffer_no]))
			{
				cout << "Encoding of buffer failed!" << endl;
				exit(-1);
			}
			if(!VRmUsbCamFreeImage(&p_cropped_source_img))
			{
				LogExit();
			}

			// Unlock source image
			if(!VRmUsbCamUnlockNextImage(device, &p_source_img))
				LogExit();

			// Free the resources of the target image
			if(!VRmUsbCamFreeImage(&p_target_img[target_buffer_no]))
				LogExit();
					
			//switch to next image
			target_buffer_no= !target_buffer_no;
		}
		i = i+1;
	} while (!Quit() && !g_quit);

	// Unlock the dfb buffer which is still locked
	UnlockBuffer(!target_buffer_no);

	// stop grabber
	if(!VRmUsbCamStop(device))
		LogExit();
}
