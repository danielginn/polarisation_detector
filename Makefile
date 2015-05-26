# include Rules file with architecture dependent definitions of 
# VRMSDK_INSTALL_DIR, CROSS_COMPILE_PREFIX, VRM_INCPATH, VRM_LIBPATH, VRM_LFLAGS, VRM_CFLAGS

include Rules.make

CXX      = $(CROSS_COMPILE_PREFIX)g++
CXXFLAGS = -pipe -O2 -fmessage-length=0 -fPIC -Wno-deprecated -Wall -W -Wno-unused $(VRM_CFLAGS)

# append your additional includes with -I<path_to_new_dir>
INCPATH  = $(VRM_INCPATH) -I$(CPP_WRAPPER_PATH)
# append your additional library search dirs with -L<path_to_new_dir>
LIBPATH  = $(VRM_LIBPATH)
# add additional linker flags as needed 
LFLAGS= $(VRM_LFLAGS)

LIBS     = -lvrmusbcam2 -lpthread -lboost_thread-mt
DEL_FILE = rm -f

####### Files

OBJECTS = $(CPP_WRAPPER_PATH)/vrmusbcamcpp.o \
		main.o 
TARGET   = simple_cpp

first: all
####### Implicit rules

.SUFFIXES: .o .cpp

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBPATH) $(LIBS)

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core
	-$(DEL_FILE) $(TARGET)
	
