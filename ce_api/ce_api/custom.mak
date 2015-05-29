## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,v5T linker.cmd \
  package/cfg/ce_api_pv5T.ov5T \

linker.cmd: package/cfg/ce_api_pv5T.xdl
	$(SED) 's"^\"\(package/cfg/ce_api_pv5Tcfg.cmd\)\"$""\"/home/daniel/vrm-demos-d3-4.3.3/demos/advanced/arm-dsp/directfb_viewer_d3/ce_api/ce_api/\1\""' package/cfg/ce_api_pv5T.xdl > $@
