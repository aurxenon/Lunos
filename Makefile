include include.mk

LUNOS_DIRS =  Kernel
#LUNOS_DIRS += Libs/LibStandard

.PHONY: all $(LUNOS_DIRS)

all : $(LUNOS_DIRS)

$(LUNOS_DIRS) :
	@echo "[ MAKE ]  $(shell realpath --relative-to=$(TOPDIR) $@)"
	@$(MAKE) --directory=$@