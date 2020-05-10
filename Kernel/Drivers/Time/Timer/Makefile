include ../../../kernel.mk

TIMER_OBJECTS =  $(OBJDIR)/TimerDriver.o

all : TIMER

TIMER : $(TIMER_OBJECTS)

CWD = $(shell /bin/pwd)

TIMER_LEVEL_DIRS =  $(CWD)/PIT

.PHONY: all $(TIMER_LEVEL_DIRS)
all : $(TIMER_OBJECTS) $(TIMER_LEVEL_DIRS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ] $@"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<

$(TIMER_LEVEL_DIRS) : 
	@echo "[ MAKE ] Kernel/Drivers/Time/TIMER/$@"
	@$(MAKE) --directory=$@