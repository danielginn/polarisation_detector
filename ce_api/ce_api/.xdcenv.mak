#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /opt/vrmagic/sdk-4.3.3/D3;/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdais_7_22_00_03/packages;/opt/ti/ti-ezsdk-5_05_02_00/component-sources/bios_6_33_05_46/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/linuxutils_3_22_00_02/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/syslink_2_20_02_20/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/osal_1_22_01_09/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/framework_components_3_22_01_07/packages;/opt/ti/ti-ezsdk-5_05_02_00/component-sources/ipc_1_24_03_32/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/codec_engine_3_22_01_06/packages;/home/daniel/vrm-demos-d3-4.3.3/demos/advanced/arm-dsp/directfb_viewer_d3
override XDCROOT = /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = DEVICE="" PROGRAMS="" GPPOS="" ti.targets.C64P="" ti.targets.C674="" ti.targets.arm.elf.M3="" ti.targets.elf.C64P="" ti.targets.elf.C64T="" ti.targets.elf.C66="" ti.targets.elf.C674="" gnu.targets.arm.GCArmv5T="/usr;LONGNAME=bin/arm-linux-gnueabihf-gcc;profiles.release.compileOpts.copts=-O2 -ffunction-sections -marm -pthread" google.targets.arm.Bionic=""
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /opt/vrmagic/sdk-4.3.3/D3;/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdais_7_22_00_03/packages;/opt/ti/ti-ezsdk-5_05_02_00/component-sources/bios_6_33_05_46/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/linuxutils_3_22_00_02/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/syslink_2_20_02_20/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/osal_1_22_01_09/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/framework_components_3_22_01_07/packages;/opt/ti/ti-ezsdk-5_05_02_00/component-sources/ipc_1_24_03_32/packages;/opt/vrmagic/vrm-d3-ezsdk/component-sources/codec_engine_3_22_01_06/packages;/home/daniel/vrm-demos-d3-4.3.3/demos/advanced/arm-dsp/directfb_viewer_d3;/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages;..
HOSTOS = Linux
endif
