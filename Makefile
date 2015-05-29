all:
%::
	$(MAKE) -C server $@
	$(MAKE) -C ce_api $@
	$(MAKE) -C main_code $@
