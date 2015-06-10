// ==============================================================================================
// This file is part of the VRmagic DSP Camera Demo Application
// ==============================================================================================
// directfb Window
// ----------------------------------------------------------------------------------------------

#include  "header.h"

#include <unistd.h> 
#include <termios.h>

#include <iostream>
#include <sstream>

#include <ce_api.h>

#define BLACK		0x00,0x00,0x00,0xff

static IDirectFB *dfb = NULL;
static IDirectFBSurface *primary = NULL;
static const int num_back_buffers = 2;
static IDirectFBSurface *surface[num_back_buffers];
static IDirectFBEventBuffer *kb_buf = NULL;
static IDirectFBInputDevice *keyboard= NULL;
static IDirectFBFont *default_font= NULL;
static int screen_width  = 0;
static int screen_height = 0;

static void* p_surface_buffer[2];
static int l_surface_buffer_size;

struct termios initial_settings, new_settings;

// Makes std type handling easier
using namespace std;
bool WindowInit(VRmDWORD& f_screen_width, VRmDWORD& f_screen_height, VRmColorFormat& f_screen_colorformat)
{
  DFBSurfaceDescription dsc;
  DFBFontDescription fontdesc;
  
  // Init dfb
  DFBCHECK (DirectFBCreate (&dfb));
  DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_FULLSCREEN));

  // Ensure deallocation of window/dfb at application exit 
  // NOTE: this must be called AFTER DirectFBCreate()
  atexit(WindowClose);
 
  // Prepare kbhit() for console inputs ( 
  tcgetattr(0,&initial_settings);
  new_settings = initial_settings;
  new_settings.c_lflag &= ~ICANON;
  new_settings.c_lflag &= ~ECHO;
  //comment out next line to enable keyboard signals e.g. CTRL-C for SIGTERM
  new_settings.c_lflag &= ~ISIG;
  new_settings.c_cc[VMIN] = 1;
  new_settings.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &new_settings);
  
  // Create primary surface
  dsc.flags = DSDESC_CAPS;
  dsc.caps  = DFBSurfaceCapabilities(DSCAPS_PRIMARY | DSCAPS_FLIPPING);
  DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));
  DFBCHECK (primary->GetSize (primary, &screen_width, &screen_height));
  f_screen_height =(VRmDWORD) screen_height;
  f_screen_width= (VRmDWORD) screen_width;

  // Clear background in case camera resolution is lower than screen resolution
  DFBCHECK (primary->Clear (primary,0,0,0,0xff));
  DFBCHECK (primary->Flip (primary, NULL, DSFLIP_NONE));
  DFBCHECK (primary->Clear (primary,0,0,0,0xff));
  DFBSurfacePixelFormat pixelformat;
  DFBCHECK (primary->GetPixelFormat(primary,&pixelformat));

  switch(pixelformat)
  {
  case DSPF_RGB16:
	  f_screen_colorformat=VRM_RGB_565; 
	  break;
  case DSPF_RGB24:
	  f_screen_colorformat=VRM_BGR_3X8; 
	  break;
  case DSPF_RGB32:
  case DSPF_ARGB:
	  cout << "32 bit color" << endl; 
	  f_screen_colorformat=VRM_ARGB_4X8 ;
	 break;

  default:
	  cout << "WindowInit: Unsupported pixel format!" << endl;
	  return false;
  }	

 //Create default font
  DFBCHECK (dfb->CreateFont (dfb, NULL, NULL, &default_font));
 
  // Init keyboard (coonected to the USB port of the Davinci)
  DFBCHECK (dfb->GetInputDevice (dfb, DIDID_KEYBOARD, &keyboard));
  DFBCHECK (keyboard->CreateEventBuffer (keyboard, &kb_buf));

  return true;

}

bool SurfaceInit(VRmImageFormat f_format)
{
	// Calculate buffer size
  VRmDWORD target_pixel_depth;
  if(!VRmUsbCamGetPixelDepthFromColorFormat(f_format.m_color_format, &target_pixel_depth))
    LogExit();
  l_surface_buffer_size= f_format.m_height * f_format.m_width * target_pixel_depth;
  
  // Create off-screen surfaces
  DFBSurfaceDescription dsc;
  dsc.flags= DFBSurfaceDescriptionFlags(DSDESC_CAPS | DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PREALLOCATED | DSDESC_PIXELFORMAT);
  dsc.caps= DSCAPS_NONE;
  dsc.preallocated[0].pitch= f_format.m_width * target_pixel_depth;
  dsc.width= f_format.m_width;
  dsc.height= f_format.m_height;
  switch( f_format.m_color_format)
  { 
  case VRM_RGB_565:
	  dsc.pixelformat=DSPF_RGB16;
	  break;
  case VRM_BGR_3X8:
	  dsc.pixelformat= DSPF_RGB24;
	  break;
  case VRM_ARGB_4X8:
	  dsc.pixelformat= DSPF_RGB32;
      break;
  default: 
	  cout << "surfaceInit: unhandled pixelformat" << endl;
	  return false;
  }
 
  // Allocate contigous memory for surface buffer
  for(int i=0;i<num_back_buffers;i++)
  {
	p_surface_buffer[i]= DspAllocMemory(l_surface_buffer_size);
	if(!p_surface_buffer[i])
	{
	  cerr << "Could not allocate memory for target surface." << endl;
	  LogExit();
	}
	dsc.preallocated[0].data= p_surface_buffer[i];
	DFBCHECK (dfb->CreateSurface( dfb, &dsc, &surface[i] ));
	DFBCHECK (surface[i]->SetFont ( surface[i], default_font ));
	DFBCHECK (surface[i]->SetColor ( surface[i], BLACK ));
  }

  return true;
}

void WindowClose()
{
	// Free all dfb resources
	if(kb_buf != NULL) kb_buf->Release (kb_buf);
	kb_buf= NULL;

	if(keyboard != NULL) keyboard->Release (keyboard);
	keyboard= NULL;

	if(default_font != NULL) default_font->Release (default_font);
	default_font= NULL;
	
	for(int i=0;i<2;i++)
	{
		if(surface[i] != NULL) 
		{
			DspFreeMemory((char*)p_surface_buffer[i], l_surface_buffer_size);
			surface[i]->Release (surface[i]);
			surface[i]= NULL;
		}
	}
	
	if(primary != NULL) primary->Release (primary);
	primary= NULL;

	if(dfb != NULL) dfb->Release (dfb);
	dfb= NULL;

	// Restore initial keyboard settings of the remote console
	tcsetattr(0, TCSANOW, &initial_settings);
}

unsigned char* LockBuffer(unsigned int& f_pitch, int number )
{
	void *p_buffer;

	DFBCHECK( surface[number]->Lock( surface[number], DSLF_WRITE, &p_buffer, (int*)&f_pitch ) ); 

	return static_cast<unsigned char*>(p_buffer);
}

void UnlockBuffer(int number)
{
	DFBCHECK( surface[number]->Unlock( surface[number] ) );
}

void Update(int number, float fps)
{
	stringstream ss;
	ss << "Frames/sec: " << fps;
	

	//char fps_string[10];
	//sprintf(fps_string,"Frames/sec: %3.4f",fps);
	
	DFBRectangle rect;
	rect.x= 0;
	rect.y= 0;
	rect.w= screen_width;
	rect.h= screen_height;
	
	// Show framerate at left top of screen
	//DFBCHECK (surface[number]->DrawString ( surface[number],ss.str().c_str(), -1, 43, 67, DSTF_BOTTOMLEFT ));

	// Blit video buffer into framebuffer
	DFBCHECK (surface[number]->Blit ( primary, surface[number], &rect, 0, 0 ) );

	// Update framebuffer
    DFBCHECK ( primary->Flip ( primary, NULL, DSFLIP_NONE /*DSFLIP_WAITFORSYNC*/ ) );
}

bool Quit()
{
    // Check input of USB keyboard connected directly to Davinci
	DFBInputEvent kb_event;
	
    while (kb_buf->GetEvent (kb_buf, DFB_EVENT(&kb_event)) == DFB_OK)
	{
		if (kb_event.type == DIET_KEYPRESS) 
			return true;
	}

	// Check for remote console keyboard input
	unsigned char ch;
	int nread;

	new_settings.c_cc[VMIN]=0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0,&ch,1);
	new_settings.c_cc[VMIN]=1;
	tcsetattr(0, TCSANOW, &new_settings);
	if (nread == 1)
		return true;

	return false;
}
