# include Rules file with architecture dependent definitions of 
# VRMSDK_INSTALL_DIR, CROSS_COMPILE_PREFIX, VRM_INCPATH, VRM_LIBPATH, VRM_LFLAGS
include ../Rules.make

CXX      = $(CROSS_COMPILE_PREFIX)g++
CXXFLAGS = -pipe -O2 -fmessage-length=0 -fPIC -Wno-deprecated -Wall -W -Wno-unused

# append your additional includes with -I<path_to_new_dir>
INCPATH  = $(VRM_INCPATH) -I../ce_api -I/usr/arm-linux-gnueabihf/vrmagic/usr/include/directfb
# append your additional library search dirs with -L<path_to_new_dir>
LIBPATH  = $(VRM_LIBPATH) -L../ce_api
# add additional linker flags as needed 
LFLAGS= $(VRM_LFLAGS)

LIBS     = -lvrmusbcam2 -ldirectfb -lce_api -lpthread -ldl -lrt
DEL_FILE = rm -f


####### Files

OBJECTS = main.o directfbwindow.o readcamera.o initcamera.o
TARGET   = ../bin/polarisation_detector

first: all
####### Implicit rules

.SUFFIXES: .o .cpp

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS) ../ce_api/libce_api.a
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBPATH) $(LIBS)

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)
	
