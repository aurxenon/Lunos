include ../../kernel.mk

SCHEDULER_OBJECTS = $(OBJDIR)/Scheduler.o

all : SysScheduler

SysScheduler : $(SCHEDULER_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(SCHEDULER_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<