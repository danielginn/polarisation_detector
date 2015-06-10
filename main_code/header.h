// ==============================================================================================
// This file is part of the VRmagic DSP Camera Demo Application
// ==============================================================================================
#ifndef VRMDSPCAMDEMO_H
#define VRMDSPCAMDEMO_H

// include the api of the library
#include  <vrmusbcam2.h>

#include <directfb.h>

#define DFBCHECK(x)                                            \
  {                                                            \
    DFBResult err = x;                                         \
                                                               \
    if (err != DFB_OK)                                         \
      {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }


// function prototypes "main.cpp"
void LogExit();

// function prototypes "initcamera.cpp"
void initCamera(VRmUsbCamDevice device, VRmDWORD& port, VRmImageFormat& target_format, VRmDWORD screen_width, VRmDWORD screen_height, VRmColorFormat screen_format, VRmRectI& source_cropping_region);

// function prototypes "readcamera.cpp"
void readCamera( VRmUsbCamDevice device,VRmDWORD port, VRmImageFormat target_format, VRmRectI source_cropping_region );

// function prototypes "directfbwindow.cpp"
bool WindowInit(VRmDWORD& f_screen_width, VRmDWORD& f_screen_height, VRmColorFormat& f_screen_colorformat);
bool SurfaceInit( VRmImageFormat f_format );
void WindowClose();
unsigned char* LockBuffer( unsigned int& f_pitch, int number );
void UnlockBuffer( int number );
void Update( int number, float fps );
bool Quit();

#endif //VRMDSPCAMDEMO_H
