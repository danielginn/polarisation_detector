// ==============================================================================================
// This file is part of the VRmagic DSP Camera Demo Application
// ==============================================================================================
// Camera Initialization
// ----------------------------------------------------------------------------------------------

#include <iostream>

#include "header.h"

#include <../ce_api/ce_api.h>

// Just for convenience
using namespace std;

void initCamera(VRmUsbCamDevice device, VRmDWORD& port, VRmImageFormat& target_format, 
				VRmDWORD screen_width, VRmDWORD screen_height, VRmColorFormat screen_colorformat,
				VRmRectI& src_cropping_region ) 
{
	
	// some examples for properties / camera settings
	VRmBOOL supported;

	// check number of connected sensors
	VRmDWORD num_sensorports=0;
	if(!VRmUsbCamGetSensorPortListSize(device,&num_sensorports))
		LogExit();

	// for this demo we switch off all connected sensor but the first one in the port list
	for(VRmDWORD ii=0; ii<num_sensorports;ii++)
	{
		if(!VRmUsbCamGetSensorPortListEntry(device,ii,&port))
			LogExit();

		// on single sensor devices this property does not exist
		VRmPropId sensor_enable = (VRmPropId)(VRM_PROPID_GRAB_SENSOR_ENABLE_1_B-1+port);
		if(!VRmUsbCamGetPropertySupported(device,sensor_enable,&supported))
			LogExit();
		if(supported)
		{
			//enable first sensor in port list
			VRmBOOL enable = 1;
			if(ii) 
				enable = 0;
			if(!VRmUsbCamSetPropertyValueB(device,sensor_enable,&enable))
				LogExit();
		}
	}

	//now get the first sensor port
	if(!VRmUsbCamGetSensorPortListEntry(device,0,&port))
		LogExit();

	//check if exposure time can be set
	if(!VRmUsbCamGetPropertySupported(device,VRM_PROPID_CAM_EXPOSURE_TIME_F,&supported))
		LogExit();
	if(supported)
	{
		float value=75.f;
		// uncomment the following lines to change exposure time to 25ms
		// when camera supports this feature
		if(!VRmUsbCamSetPropertyValueF(device,VRM_PROPID_CAM_EXPOSURE_TIME_F,&value))
			LogExit();
	}

	// Get the current source format (only for user info)
	VRmImageFormat source_format;
	if (!VRmUsbCamGetSourceFormatEx(device,port,&source_format))
		LogExit();
	
	const char *source_color_format_str;
	if (!VRmUsbCamGetStringFromColorFormat(source_format.m_color_format,&source_color_format_str))
		LogExit();
	cout << "Selected source format: " 
		<< source_format.m_width << "x" << source_format.m_height 
		<< " (" << source_color_format_str << ")" << endl;




	// Select a target format from the list of formats we can convert the source images to.
    // We search for the color format of the connected screen, since this is the format
	// which can be displayed by the Davinci.
	VRmDWORD number_of_target_formats, i;
	if (!VRmUsbCamGetTargetFormatListSizeEx2( device, port, &number_of_target_formats ) )
		LogExit();

	for (i= 0; i < number_of_target_formats; ++i )
	{
		if(!VRmUsbCamGetTargetFormatListEntryEx2(device,port,i,&target_format))
			LogExit();
		if ( target_format.m_color_format == screen_colorformat )
			break;
	}

	// on the davinci devices, the video output can go to S-Video, LCD, DVI, of HDMI
	// each having different resolution
	// we crop the source image to this size, because not all camera models 
	// allow setting of a User ROI of this size
 	src_cropping_region.m_left = 0;
	src_cropping_region.m_top  = 0;
	int bayer_border = source_format.m_width - target_format.m_width;
	src_cropping_region.m_height=min((int)screen_height+bayer_border,(int) source_format.m_height);
	src_cropping_region.m_width=min((int)screen_width+bayer_border,(int) source_format.m_width);
	target_format.m_width =src_cropping_region.m_width  - bayer_border;
	target_format.m_height=src_cropping_region.m_height - bayer_border;
	if((int) source_format.m_width != src_cropping_region.m_width || (int)source_format.m_height != src_cropping_region.m_height)
	{		
		cout << "Cropping source format to " << src_cropping_region.m_width 
		 << "x" << src_cropping_region.m_height << " to fit image size to screen." <<endl;
	}
	const char *target_color_format_str;
	if (!VRmUsbCamGetStringFromColorFormat(target_format.m_color_format,&target_color_format_str))
		LogExit();
	cout << "Selected target format: " 
		<< target_format.m_width << "x" << target_format.m_height 
		<< " (" << target_color_format_str << ")" << endl;

}

	
