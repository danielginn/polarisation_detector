// ================================================================================================
// This file is part of the Polarisation Detection program by Daniel Ginn using VRmagic's D3
// ================================================================================================
// Main Function
// ------------------------------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <vrmusbcam2.h>
#include <ce_api.h>
#include <signal.h>
#include "header.h"

extern bool g_quit;


using namespace std;

// ------------------------------------------------------------------------------------------------
// main function
// ------------------------------------------------------------------------------------------------
//

void LogExit()
{
	cerr << "VRmUsbCam Error: " <<  VRmUsbCamGetLastError() << "\nApplication exit" << endl;
	exit(-1);
}

void GotSignal(int f_sig_nr)
{
	//simple signal handler, add more signals if needed
	
	switch(f_sig_nr){
		case SIGTERM: 
			printf("\nGot SIGTERM signal. Exiting...\n");
			g_quit= true;
			break;
		case SIGINT:
			printf("\nGot SIGINT signal. Exiting...\n");
			g_quit= true;
			break;
		default:
			printf("Unkown signal");
	}
}

int main(int argc, char** argv)
{
	// at first, be sure to call VRmUsbCamCleanup() at exit, even in case
	// of an error
	atexit(VRmUsbCamCleanup);

    	// Init DirectFB
	DFBCHECK (DirectFBInit (&argc, &argv));
	
	// read libversion (for informational purposes only)
	VRmDWORD libversion;
	if (!VRmUsbCamGetVersion(&libversion))
		LogExit();

	cout << "========================================================" << endl
	     << "===         Polarisation Detection Program           ===" << endl
	     << "========================================================" << endl
	     << "(v." << libversion << ")" << endl << endl;

	// Check for connected devices
	VRmDWORD size=0;
	if(!VRmUsbCamGetDeviceKeyListSize(&size))
		LogExit();

	// Open first usable device, which is always the local, i.e. Davinci, camera
	VRmUsbCamDevice device=0;
	VRmDeviceKey* p_device_key=0;
	for(VRmDWORD i=0; i<size && !device; ++i)
	{
		if(!VRmUsbCamGetDeviceKeyListEntry(i,&p_device_key))
			LogExit();
		if(!p_device_key->m_busy) {
			if(!VRmUsbCamOpenDevice(p_device_key,&device))
				LogExit();
		}
		if(!VRmUsbCamFreeDeviceKey(&p_device_key))
			LogExit();
	}

	// Display error when no camera has been found
	if(!device)
	{
		cerr << "No suitable VRmagic device found!" << endl;
		exit(-1);
	}

	// Initialize directfb window
	VRmDWORD screen_width;
	VRmDWORD screen_height;
	VRmColorFormat screen_colorformat;
	if(!WindowInit(screen_width,screen_height,screen_colorformat))
	{
		cerr << "Could not initialize DirectFB primary surface." << endl;
		VRmUsbCamCloseDevice(device);
		exit(-1);
	}
	cout << "WindowInit:\nScreen width: " << screen_width << endl;
	cout << "Screen height: " << screen_height << endl;
	cout << "Screen colour format: " << screen_colorformat << endl << endl;

	VRmImageFormat target_format;
	VRmDWORD port=0;
	VRmRectI source_cropping_region = {0,0,0,0};
	initCamera(device,port,target_format,screen_width,screen_height,screen_colorformat,source_cropping_region);
	
	// Initialize Codec Engine and create Codecs
	if(DspInit())
	{
		cerr << "Could not initialize Codec Engine." << endl;
		exit(-1);
	}
	
	// initialize off-screen surfaces in CMEM
	if (!SurfaceInit(target_format))
	{
		cerr << "Could not initialize DirectFB off screen surfaces." << endl;
		VRmUsbCamCloseDevice(device);
		exit(-1);
	}
	
	// Catch some signals for clean exit, add more handlers if needed.
	// This has to be done after WindowInit (DirectFBCreate()), to override directfb's own signal handler,
	// alternatively directfb signal handling can be disabled in /etc/directfbrc.
	signal(SIGTERM,GotSignal);
	signal(SIGINT,GotSignal);

    // and read pictures...
	readCamera(device,port,target_format,source_cropping_region);


	// close the device
	if(!VRmUsbCamCloseDevice(device))
		LogExit();
	
	cout << endl << "exit." << endl;

	return 0;
}
