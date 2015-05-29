include $(abspath $(dir $(lastword $(MAKEFILE_LIST))))/Rules.make

EZSDK_INSTALL_DIR=/opt/vrmagic/vrm-d3-ezsdk
ifeq ($(wildcard $(EZSDK_INSTALL_DIR)),)
  $(error "EZSDK_INSTALL_DIR=$(EZSDK_INSTALL_DIR) specifies a directory that does not exist. Please check the path in the file xdcpaths.mak!")
endif

XDC_INSTALL_DIR=	$(EZSDK_INSTALL_DIR)/component-sources/xdctools_3_23_03_53
CE_INSTALL_DIR =	$(EZSDK_INSTALL_DIR)/component-sources/codec_engine_3_22_01_06
BIOS_INSTALL_DIR =	$(EZSDK_INSTALL_DIR)/component-sources/bios_6_33_05_46
FC_INSTALL_DIR =	$(EZSDK_INSTALL_DIR)/component-sources/framework_components_3_22_01_07
XDAIS_INSTALL_DIR =	$(EZSDK_INSTALL_DIR)/component-sources/xdais_7_22_00_03
CODEGEN_INSTALL_DIR=$(EZSDK_INSTALL_DIR)/dsp-devkit/cgt6x_7_3_4
IPC_INSTALL_DIR=	$(EZSDK_INSTALL_DIR)/component-sources/ipc_1_24_03_32
OSAL_INSTALL_DIR=	$(EZSDK_INSTALL_DIR)/component-sources/osal_1_22_01_09
LINK_INSTALL_DIR =	$(EZSDK_INSTALL_DIR)/component-sources/syslink_2_20_02_20
CMEM_INSTALL_DIR = 	$(EZSDK_INSTALL_DIR)/component-sources/linuxutils_3_22_00_02

VRM_CODEC_INSTALL_DIR = $(VRMSDK_INSTALL_DIR);
VM_LIB_C674_INSTALL_DIR = $(VRMSDK_INSTALL_DIR)/dsp/vm_lib-$(VM_LIB_VERSION)

XDC_PATH = $(VRM_CODEC_INSTALL_DIR);$(XDAIS_INSTALL_DIR)/packages;$(BIOS_INSTALL_DIR)/packages;$(CMEM_INSTALL_DIR)/packages;$(LINK_INSTALL_DIR)/packages;$(OSAL_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(IPC_INSTALL_DIR)/packages;$(CE_INSTALL_DIR)/packages
