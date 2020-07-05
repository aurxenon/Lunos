include ../../kernel.mk

PROCESS_OBJECTS = $(OBJDIR)/Process.o

all : SysProcess

SysProcess : $(PROCESS_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(PROCESS_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<