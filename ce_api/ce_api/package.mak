#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = ce_api
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/include/utils.tci:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/include/utils.tci
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/xdc.tci:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/xdc.tci
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/template.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/template.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/om2.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/om2.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/xmlgen.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/xmlgen.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/xmlgen2.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/xmlgen2.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/IPackage.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/IPackage.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/package.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/package.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/services/global/Clock.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/services/global/Clock.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/services/global/Trace.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/services/global/Trace.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/bld.js:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/bld.js
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/BuildEnvironment.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/BuildEnvironment.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/PackageContents.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/PackageContents.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/_gen.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/_gen.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Library.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Library.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Executable.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Executable.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Repository.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Repository.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Configuration.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Configuration.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Script.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Script.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Manifest.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Manifest.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Utils.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/Utils.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITarget.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITarget.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITarget2.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITarget2.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITargetFilter.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/ITargetFilter.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/package.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/bld/package.xs
package.mak: config.bld
/opt/vrmagic/vrm-d3-ezsdk/component-sources/codec_engine_3_22_01_06/codec_engine.bld:
package.mak: /opt/vrmagic/vrm-d3-ezsdk/component-sources/codec_engine_3_22_01_06/codec_engine.bld
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/ITarget.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/ITarget.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/Linux86.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/Linux86.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/Mingw.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/Mingw.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/MVArm9.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/MVArm9.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/UCArm9.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/UCArm9.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/package.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/package.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/GCArmv6.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/GCArmv6.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/GCArmv7A.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/GCArmv7A.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M3.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M3.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M4.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M4.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M4F.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/M4F.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/MVArm9.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/MVArm9.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/UCArm9.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/UCArm9.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/package.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/package.xs
package.mak: package.bld
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/tools/configuro/template/compiler.opt.xdt:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/tools/configuro/template/compiler.opt.xdt
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/services/io/File.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/services/io/File.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/services/io/package.xs:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/services/io/package.xs
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/tools/configuro/template/custom.mak.exe.xdt:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/tools/configuro/template/custom.mak.exe.xdt
/opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/tools/configuro/template/package.xs.xdt:
package.mak: /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/xdc/tools/configuro/template/package.xs.xdt
endif

gnu.targets.arm.GCArmv5T.rootDir ?= /usr
gnu.targets.arm.packageBase ?= /opt/ti/ti-ezsdk-5_05_02_00/component-sources/xdctools_3_23_03_53/packages/gnu/targets/arm/
.PRECIOUS: $(XDCCFGDIR)/%.ov5T
.PHONY: all,v5T .dlls,v5T .executables,v5T test,v5T
all,v5T: .executables,v5T
.executables,v5T: .libraries,v5T
.executables,v5T: .dlls,v5T
.dlls,v5T: .libraries,v5T
.libraries,v5T: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,v5T
	@$(ECHO) xdc .executables,v5T
	@$(ECHO) xdc .libraries,v5T
	@$(ECHO) xdc .dlls,v5T


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_ce_api.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package ce_api" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

.dlls,v5T .dlls: ce_api.pv5T

-include package/cfg/ce_api_pv5T.mak
-include package/cfg/ce_api_pv5T.cfg.mak
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/ce_api_pv5T.dep
endif
ce_api.pv5T: package/cfg/ce_api_pv5T.xdl
	@


ifeq (,$(wildcard .libraries,v5T))
ce_api.pv5T package/cfg/ce_api_pv5T.c: .libraries,v5T
endif

package/cfg/ce_api_pv5T.c package/cfg/ce_api_pv5T.h package/cfg/ce_api_pv5T.xdl: override _PROG_NAME := ce_api.xv5T
package/cfg/ce_api_pv5T.c: package/cfg/ce_api_pv5T.cfg

clean:: clean,v5T
	-$(RM) package/cfg/ce_api_pv5T.cfg
	-$(RM) package/cfg/ce_api_pv5T.dep
	-$(RM) package/cfg/ce_api_pv5T.c
	-$(RM) package/cfg/ce_api_pv5T.xdc.inc

clean,v5T::
	-$(RM) ce_api.pv5T
.executables,v5T .executables: ce_api.xv5T

ce_api.xv5T: |ce_api.pv5T

-include package/cfg/ce_api.xv5T.mak
ce_api.xv5T: package/cfg/ce_api_pv5T.ov5T 
	$(RM) $@
	@$(MSG) lnkv5T $@ ...
	$(RM) $(XDCCFGDIR)$@.map
	$(gnu.targets.arm.GCArmv5T.rootDir)/bin/arm-linux-gnueabihf-gcc  -Wl,--gc-sections  -o $@ package/cfg/ce_api_pv5T.ov5T -Wl,-T,package/cfg/ce_api_pv5T.xdl   -Wl,-Map=$(XDCCFGDIR)/$@.map  -L$(gnu.targets.arm.GCArmv5T.rootDir)/arm-linux-gnueabihf/lib -lpthread -lrt -ldl 
	
ce_api.xv5T: export LD_LIBRARY_PATH=

ce_api.test test,v5T test: ce_api.xv5T.test

ce_api.xv5T.test:: ce_api.xv5T
ifeq (,$(_TESTLEVEL))
	@$(MAKE) -R -r --no-print-directory -f $(XDCROOT)/packages/xdc/bld/xdc.mak _TESTLEVEL=1 ce_api.xv5T.test
else
	@$(MSG) running $<  ...
	$(call EXEC.ce_api.xv5T, ) 
endif

clean,v5T::
	-$(RM) .tmp,ce_api.xv5T,0,*


clean:: clean,v5T

clean,v5T::
	-$(RM) ce_api.xv5T
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
ce_api_pv5T.ov5T,copy : package/cfg/ce_api_pv5T.ov5T
ce_api_pv5T.sv5T,copy : package/cfg/ce_api_pv5T.sv5T

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg .interfaces $(XDCROOT)/packages/xdc/cfg/Main.xs
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,ce_api
ce_api.tar: package/package.bld.xml
ce_api.tar: package/package.ext.xml
ce_api.tar: package/package.rel.dot
ce_api.tar: package/build.cfg
ce_api.tar: package/package.xdc.inc
ifeq (,$(MK_NOGENDEPS))
-include package/rel/ce_api.tar.dep
endif
package/rel/ce_api/ce_api/package/package.rel.xml:

ce_api.tar: package/rel/ce_api.xdc.inc package/rel/ce_api/ce_api/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/ce_api.xdc.inc,package/rel/ce_api.tar.dep)


release release,ce_api: all ce_api.tar
clean:: .clean
	-$(RM) ce_api.tar
	-$(RM) package/rel/ce_api.xdc.inc
	-$(RM) package/rel/ce_api.tar.dep

clean:: .clean
	-$(RM) .libraries .libraries,*
clean:: 
	-$(RM) .dlls .dlls,*
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
ifeq (,$(wildcard package/external))
    $(shell $(MKDIR) package/external)
endif
endif
clean::
	-$(RMDIR) package

include custom.mak
