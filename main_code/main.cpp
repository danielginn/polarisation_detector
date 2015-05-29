// ================================================================================================
// This file is part of the Polarisation Detection program by Daniel Ginn using VRmagic's D3
// ================================================================================================
// Main Function
// ------------------------------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <vrmusbcam2.h>
#include <ce_api.h>

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

int main(int argc, char** argv)
{
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

	// close the device
	if(!VRmUsbCamCloseDevice(device))
		LogExit();
	
	cout << endl << "exit." << endl;

	return 0;
}
