include ../../../kernel.mk

PATA_OBJECTS =  $(OBJDIR)/PATADriver.o
PATA_OBJECTS += $(OBJDIR)/PATADevice.o

all : PATA

PATA : $(PATA_OBJECTS)

CWD = $(shell /bin/pwd)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<