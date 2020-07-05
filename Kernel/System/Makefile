include ../kernel.mk

SYSTEM_OBJECTS = $(OBJDIR)/KMalloc.o

all : System

System : $(SYSTEM_OBJECTS)

CWD = $(shell /bin/pwd)

SYSTEM_LEVEL_DIRS =  $(CWD)/Scheduler
SYSTEM_LEVEL_DIRS += $(CWD)/Process

.PHONY: all $(SYSTEM_LEVEL_DIRS)

all : $(SYSTEM_OBJECTS) $(SYSTEM_LEVEL_DIRS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<

$(SYSTEM_LEVEL_DIRS) : 
	@echo "[ MAKE ]  $(shell realpath --relative-to=$(TOPDIR) $@)"
	@$(MAKE) --directory=$@