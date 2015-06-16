#
_XDCBUILDCOUNT = 79
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /opt/vrmagic/sdk-4.3.3/D3/;;/opt/vrmagic/vrm-d3-ezsdk/component-sources/xdais_7_22_00_03/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/bios_6_33_05_46/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/linuxutils_3_22_00_02/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/syslink_2_20_02_20/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/osal_1_22_01_09/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/framework_components_3_22_01_07/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/ipc_1_24_03_32/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/codec_engine_3_22_01_06/packages;
override XDCROOT = /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = CODEGEN_INSTALL_DIR="/opt/vrmagic/vrm-d3-ezsdk/dsp-devkit/cgt6x_7_3_4"
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /opt/vrmagic/sdk-4.3.3/D3/;/opt/vrmagic/vrm-d3-ezsdk/component-sources/xdais_7_22_00_03/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/bios_6_33_05_46/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/linuxutils_3_22_00_02/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/syslink_2_20_02_20/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/osal_1_22_01_09/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/framework_components_3_22_01_07/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/ipc_1_24_03_32/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/codec_engine_3_22_01_06/packages;/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages;..
HOSTOS = Linux
endif
