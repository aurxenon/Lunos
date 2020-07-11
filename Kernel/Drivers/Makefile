include ../kernel.mk

DRIVER_OBJECTS =  $(OBJDIR)/SerialDevice.o
DRIVER_OBJECTS += $(OBJDIR)/VideoConsole.o
DRIVER_OBJECTS += $(OBJDIR)/Driver.o
DRIVER_OBJECTS += $(OBJDIR)/DriverManager.o

all : Drivers

Drivers : $(DRIVER_OBJECTS)

CWD = $(shell /bin/pwd)

DRIVER_LEVEL_DIRS =  $(CWD)/Time
DRIVER_LEVEL_DIRS += $(CWD)/PCI

.PHONY: all $(DRIVER_LEVEL_DIRS)
all : $(DRIVER_OBJECTS) $(DRIVER_LEVEL_DIRS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<

$(DRIVER_LEVEL_DIRS) : 
	@echo "[ MAKE ]  $(shell realpath --relative-to=$(TOPDIR) $@)"
	@$(MAKE) --directory=$@