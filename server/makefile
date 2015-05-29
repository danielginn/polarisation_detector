#uncomment this for verbose builds
XDCOPTIONS=v

# If we're a subcomponent, allow larger product settings to override our
# defaults.  The variable $(RULES_MAKE) can be overridden on the 'make'
# command-line if the location below is not correct (for example, if you
# want to use a Rules.make from some other location.
RULES_MAKE := ../xdcpaths.mak
ifneq ($(wildcard $(RULES_MAKE)),)
include $(RULES_MAKE)
endif

XDCARGS=CODEGEN_INSTALL_DIR=\"$(CODEGEN_INSTALL_DIR)\"

# Construct XDCPATH from the paths above - this is the path containing
# dependencies required for this Server
XDCPATH=$(XDC_PATH);

TRACE_LEVEL=
TRACE_GROUPS=

# To enable RTSC trace support for Genserver builds, uncomment the two
# lines following this description. More detailed tracing can be enabled.
# See http://rtsc.eclipse.org/docs-tip/Trace_Support for full details.
#TRACE_LEVEL=1
#TRACE_GROUPS=genserver

TARGET=../bin/server.xe674

all:  
	"$(XDC_INSTALL_DIR)/xdc" XDC_TRACE_LEVEL=$(TRACE_LEVEL) XDC_TRACE_GROUPS=$(TRACE_GROUPS) XDCOPTIONS=$(XDCOPTIONS) XDCARGS="$(XDCARGS)" --xdcpath="$(XDCPATH)" release
	mkdir -p ../bin
	cp -f bin/server.xe674 $(TARGET)
	
	
clean:
	"$(XDC_INSTALL_DIR)/xdc" XDCOPTIONS=$(XDCOPTIONS) clean
	rm -f $(TARGET)

