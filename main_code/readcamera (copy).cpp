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

void readCamera(VRmUsbCamDevice device, VRmDWORD port1, VRmDWORD port2, VRmDWORD port3, VRmImageFormat target_format, VRmRectI source_cropping_region)
{	
	// frames per second, shown on S-Video and on console
	float fps= 0;

	// the source image
	VRmImage* p_source_img1 = 0;
	VRmImage* p_source_img2 = 0;
	VRmImage* p_source_img3 = 0;

    // sub-image of the source img containing the region that is displayed
    VRmImage* p_cropped_source_img1=0;
    VRmImage* p_cropped_source_img2=0;
    VRmImage* p_cropped_source_img3=0;

	// the target buffers
	VRmImage* p_target_img[6]= {0,0,0,0,0,0};

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
		VRmDWORD frames_dropped1;
		VRmDWORD frames_dropped2;
		VRmDWORD frames_dropped3;
		cout << "Locking Image 1" << endl;
		if(!VRmUsbCamLockNextImageEx(device,port1,&p_source_img1,&frames_dropped1))
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
		cout << "Locking Image 2" << endl;
		if(!VRmUsbCamLockNextImageEx(device,port2,&p_source_img2,&frames_dropped2))
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
		cout << "Locking Image 3" << endl;
		if(!VRmUsbCamLockNextImageEx(device,port3,&p_source_img3,&frames_dropped3))
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
		cout << "All Cam Images locked" << endl;
		// Note: p_source_img may be null in case a recoverable error
		// (like a trigger timeout) occured.
		if (p_source_img1 && p_source_img2 && p_source_img3)
		{		
			cout << "Cropping Images" << endl;
			// crop source image, such that output fits to screen
			if(!VRmUsbCamCropImage(&p_cropped_source_img1,p_source_img1,&source_cropping_region))
				LogExit();;
			cout << "Image 1 cropped";
			if(!VRmUsbCamCropImage(&p_cropped_source_img2,p_source_img2,&source_cropping_region))
				LogExit();;
			cout << "Image 2 cropped";
			if(!VRmUsbCamCropImage(&p_cropped_source_img3,p_source_img3,&source_cropping_region))
				LogExit();;
			cout << "Image 3 cropped";

			// Lock the dfb off-screen buffer to output the image to the screen.
			// The screen_buffer_pitch variable will receive the pitch (byte size of 
			// one line) of the buffer.l;
			VRmDWORD screen_buffer_pitch1;
			VRmDWORD screen_buffer_pitch2;
			VRmDWORD screen_buffer_pitch3;
			cout << "Locking Buffer 1" << endl;
			VRmBYTE* p_screen_buffer1=LockBuffer(screen_buffer_pitch1,target_buffer_no);
			cout << "Locking Buffer 2" << endl;
			VRmBYTE* p_screen_buffer2=LockBuffer(screen_buffer_pitch2,target_buffer_no+2);
			cout << "Locking Buffer 3" << endl;
			VRmBYTE* p_screen_buffer3=LockBuffer(screen_buffer_pitch3,target_buffer_no+4);
			cout << "All Buffers Locked" << endl;

			// Now, wrap a VRmImage around the locked screen buffer to receive the converted image
			cout << "Wrapping Image 1" << endl;
			if(!VRmUsbCamSetImage(&p_target_img[target_buffer_no],target_format,p_screen_buffer1,screen_buffer_pitch1))
				LogExit();
			cout << "Wrapping Image 2" << endl;
			if(!VRmUsbCamSetImage(&p_target_img[target_buffer_no+2],target_format,p_screen_buffer2,screen_buffer_pitch2))
				LogExit();
			cout << "Wrapping Image 3" << endl;
			if(!VRmUsbCamSetImage(&p_target_img[target_buffer_no+4],target_format,p_screen_buffer3,screen_buffer_pitch3))
				LogExit();
			cout << "All Images Wrapped" << endl;

			// Start the DSP conversion of the image 
			// Note that this is an asynchronous call, i.e. the conversion is by no means 
			// finished when the function returns
			cout << "Running asynchronous image conversion for Image 1" << endl;
			if(DspConvertImage(PROC_ASYNC, p_cropped_source_img1, p_target_img[target_buffer_no]))
			{
				cout << "Encoding of buffer failed!" << endl; 
				exit(-1);
			}
			cout << "Running asynchronous image conversion for Image 2" << endl;
			if(DspConvertImage(PROC_ASYNC, p_cropped_source_img1, p_target_img[target_buffer_no]))
			{
				cout << "Encoding of buffer failed!" << endl; 
				exit(-1);
			}
			cout << "Running asynchronous image conversion for Image 3" << endl;
			if(DspConvertImage(PROC_ASYNC, p_cropped_source_img3, p_target_img[target_buffer_no]))
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
				cout << "Unlocking Buffer" << endl;
				UnlockBuffer(!target_buffer_no);
				// ...and update the screen
				cout << "Updating screen" << endl;
				Update(!target_buffer_no,fps);

				// Save image to file
				cout << "Saving Images to sd-card" << endl;
				char fileName1[255];
				char fileName2[255];
				char fileName3[255];
				if(i<10){
					sprintf(fileName1, "image_00%da.png", i);
					sprintf(fileName2, "image_00%db.png", i);
					sprintf(fileName3, "image_00%dc.png", i);
				}
				else if(i<100){
					sprintf(fileName1, "image_0%da.png", i);
					sprintf(fileName2, "image_0%db.png", i);
					sprintf(fileName3, "image_0%dc.png", i);
				}
				else{
					sprintf(fileName1, "image_%da.png", i);
					sprintf(fileName2, "image_%db.png", i);
					sprintf(fileName3, "image_%dc.png", i);
				}
				cout << "Saving image: " << i << endl;
				VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(fileName1, p_target_img[target_buffer_no], 0));
				VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(fileName2, p_target_img[target_buffer_no+2], 0));
				VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(fileName3, p_target_img[target_buffer_no+4], 0));
			}
			
			// see, if we had to drop some frames due to data transfer stalls. if so,
			// output a message
			if (frames_dropped1)
				cout << "- " << frames_dropped1 <<  " Cam 1 frame(s) dropped -" << endl;
			if (frames_dropped2)
				cout << "- " << frames_dropped2 <<  " Cam 2 frame(s) dropped -" << endl;
			if (frames_dropped3)
				cout << "- " << frames_dropped3 <<  " Cam 3 frame(s) dropped -" << endl;

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
			cout << "Waiting until DOP processing for Image 1 complete" << endl;
			if(DspConvertImage(PROC_WAIT, p_cropped_source_img1, p_target_img[target_buffer_no]))
			{
				cout << "Encoding of buffer failed!" << endl;
				exit(-1);
			}
			cout << "Freeing Images: Cropped Image";
			if(!VRmUsbCamFreeImage(&p_cropped_source_img1))
				LogExit();
			cout << "Source Image...";
			// Unlock source image
			if(!VRmUsbCamUnlockNextImage(device, &p_source_img1))
				LogExit();
			cout << "Target Image...";
			// Free the resources of the target image
			if(!VRmUsbCamFreeImage(&p_target_img[target_buffer_no]))
				LogExit();
			cout << "Done!" << endl;
			
			cout << "Waiting until DOP processing for Image 2 complete" << endl;
			if(DspConvertImage(PROC_WAIT, p_cropped_source_img2, p_target_img[target_buffer_no+2]))
			{
				cout << "Encoding of buffer failed!" << endl;
				exit(-1);
			}
			cout << "Freeing Images: Cropped Image";
			if(!VRmUsbCamFreeImage(&p_cropped_source_img2))
				LogExit();
			cout << "Source Image...";
			// Unlock source image
			if(!VRmUsbCamUnlockNextImage(device, &p_source_img2))
				LogExit();
			cout << "Target Image...";
			// Free the resources of the target image
			if(!VRmUsbCamFreeImage(&p_target_img[target_buffer_no+2]))
				LogExit();
			cout << "Done!" << endl;

			cout << "Waiting until DOP processing for Image 3 complete" << endl;
			if(DspConvertImage(PROC_WAIT, p_cropped_source_img3, p_target_img[target_buffer_no+4]))
			{
				cout << "Encoding of buffer failed!" << endl;
				exit(-1);
			}
			cout << "Freeing Images: Cropped Image";
			if(!VRmUsbCamFreeImage(&p_cropped_source_img3))
				LogExit();
			cout << "Source Image...";
			// Unlock source image
			if(!VRmUsbCamUnlockNextImage(device, &p_source_img3))
				LogExit();
			cout << "Target Image...";
			// Free the resources of the target image
			if(!VRmUsbCamFreeImage(&p_target_img[target_buffer_no+4]))
				LogExit();
			cout << "Done!" << endl;		
			//switch to next image
			cout << "Switching Buffer number" << endl;
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
