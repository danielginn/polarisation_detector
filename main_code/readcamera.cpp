// ==============================================================================================
// This file is part of the VRmagic DSP Camera Demo Application
// ==============================================================================================
// Camera Reading / Main Loop
// ----------------------------------------------------------------------------------------------

#include "header.h"
#include "vrmusbcam2.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <string>

#include <../ce_api/ce_api.h>

bool g_quit= false;;

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
	// Setting up GPIO pin
	fstream fs;
	fs.open("/sys/class/gpio/export");
	fs.write("36",2);
	fs.close();
	fs.open("/sys/class/gpio/gpio36/direction");
	fs.write("out",3);
	fs.close();
	fs.open("/sys/class/gpio/gpio36/value");
	fs.write("0",1); // "1" for on

	// the source image
	VRmImage* p_source_img1 = 0;
	VRmImage* p_source_img2 = 0;
	VRmImage* p_source_img3 = 0;

    // sub-image of the source img containing the region that is displayed
    VRmImage* p_cropped_source_img1=0;
    VRmImage* p_cropped_source_img2=0;
    VRmImage* p_cropped_source_img3=0;

	// the target buffers
	VRmImage* p_target_img1 = 0;
	VRmImage* p_target_img2 = 0;
	VRmImage* p_target_img3 = 0;


	bool first_loop_run= true;
	VRmDWORD frame_counter= 0;
	int target_buffer_no= 0;
	
	if(!VRmUsbCamResetFrameCounter(device))
		LogExit();

	// start grabber at first
	if(!VRmUsbCamStart(device))
		LogExit();
	double looptime_start = 0;
	double looptime_finish = 0;
	double looptime = 0;
	double convtime1_start = 0;
	double convtime1_finish = 0;
	double convtime1 = 0;
	double convtime1_percent = 0;
	double save1time_start = 0;
	double save1time_finish = 0;
	double save1time = 0;
	double save1time_percent = 0;
	double save2time_start = 0;
	double save2time_finish = 0;
	double save2time = 0;
	double save2time_percent = 0;
	double save3time_start = 0;
	double save3time_finish = 0;
	double save3time = 0;
	double save3time_percent = 0;
	double capturetime_start = 0;
	double capturetime_finish = 0;
	double capturetime = 0;
	double capturetime_percentage = 0;


	// ------------------------------------------------------------------------
	// main loop: read images and draw them to screen
	// ------------------------------------------------------------------------

	cout << "Reading from camera..." << endl;
	int i = 0;
	int flip = 0;
	do
	{;
		if (flip==0)
			fs.write("1",1);
		else
			fs.write("0",1);
		flip = !flip;

		VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&looptime_start));
		// Lock next (raw) image for read access, convert it to the desired
		// format and unlock it again, so that grabbing can go on
		VRmDWORD frames_dropped1;
		VRmDWORD frames_dropped2;
		VRmDWORD frames_dropped3;
		cout << "Locking Images" << endl;
		VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&capturetime_start));
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
		VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&capturetime_finish));
		cout << "All Cam Images locked" << endl;



		// Note: p_source_img may be null in case a recoverable error
		// (like a trigger timeout) occured.
		if (p_source_img1 && p_source_img2 && p_source_img3)
		{		
			/*
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

			// Start the DSP conversion of the image 
			// Note that this is an asynchronous call, i.e. the conversion is by no means 
			// finished when the function returns
			cout << "Running synchronous image conversion for Image 1" << endl;
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&convtime1_start));
			if(VRmUsbCamConvertImage(p_cropped_source_img1, p_target_img1))
			{
				cout << "Encoding of buffer failed!" << endl; 
				exit(-1);
			}
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&convtime1_finish));
			convtime1 = convtime1_finish - convtime1_start;
			cout << "Conv 1 time: " << convtime1 << endl;
			
			cout << "Running synchronous image conversion for Image 2" << endl;
			if(VRmUsbCamConvertImage(p_cropped_source_img2, p_target_img2))
			{
				cout << "Encoding of buffer failed!" << endl; 
				exit(-1);
			}
			cout << "Running synchronous image conversion for Image 3" << endl;
			if(VRmUsbCamConvertImage(p_cropped_source_img3, p_target_img3))
			{
				cout << "Encoding of buffer failed!" << endl; 
				exit(-1);
			}
			*/
			// Saving Image 1
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
			cout << "Saving image: " << i << "a" << endl;
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&save1time_start));
			VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(fileName1, p_source_img1, 0));
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&save1time_finish));
			
			cout << "Saving image: " << i << "b" << endl;
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&save2time_start));
			VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(fileName2, p_source_img2, 0));
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&save2time_finish));
			cout << "Saving image: " << i << "c" << endl;
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&save3time_start));
			VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(fileName3, p_source_img3, 0));
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&save3time_finish));

			cout << "Freeing Source Image" << endl;
			// Unlock source image
			if(!VRmUsbCamUnlockNextImage(device, &p_source_img1))
				LogExit();
			if(!VRmUsbCamUnlockNextImage(device, &p_source_img2))
				LogExit();
			if(!VRmUsbCamUnlockNextImage(device, &p_source_img3))
				LogExit();
			
			VRM_EXEC_AND_CHECK(VRmUsbCamGetCurrentTime(&looptime_finish));
			looptime = looptime_finish - looptime_start;
			convtime1_percent = (convtime1/looptime)*100;
			save1time = save1time_finish - save1time_start;
			save1time_percent = (save1time/looptime)*100;
			save2time = save2time_finish - save2time_start;
			save2time_percent = (save2time/looptime)*100;
			save3time = save3time_finish - save3time_start;
			save3time_percent = (save3time/looptime)*100;
			capturetime = capturetime_finish - capturetime_start;
			capturetime_percentage = (capturetime/looptime)*100;
			cout << "--------------------------------------------------" << endl;
			cout << "Times:\nLoop time: " << looptime << endl;
			cout << "Capture time: " << capturetime << " (" << capturetime_percentage << ")" << endl;
			cout << "First Conv time (Synchronous): " << convtime1 << " (" << convtime1_percent << ")" << endl;
			cout << "Save1 time: " << save1time << " (" << save1time_percent << ")" << endl;
			cout << "Save2 time: " << save2time << " (" << save2time_percent << ")" << endl;
			cout << "Save3 time: " << save3time << " (" << save3time_percent << ")" << endl;
			cout << "--------------------------------------------------" << endl;
		}
		i = i+1;
	} while (!Quit() && !g_quit);
	fs.close();
	// Unlock the dfb buffer which is still locked
	UnlockBuffer(!target_buffer_no);

	// stop grabber
	if(!VRmUsbCamStop(device))
		LogExit();
}
