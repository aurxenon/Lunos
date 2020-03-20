include ../kernel.mk

DRIVER_OBJECTS =  $(OBJDIR)/SerialDevice.o
DRIVER_OBJECTS += $(OBJDIR)/VideoConsole.o

all : Drivers

Drivers : $(DRIVER_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(DRIVER_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ] $@"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<