include ../../../../kernel.mk

CMOS_OBJECTS = $(OBJDIR)/CMOS.o

all : CMOS_DRIVER

CMOS_DRIVER : $(CMOS_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(CMOS_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<