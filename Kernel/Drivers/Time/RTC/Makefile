include ../../../kernel.mk

RTC_OBJECTS =  $(OBJDIR)/RTCDriver.o

all : RTC

RTC : $(RTC_OBJECTS)

CWD = $(shell /bin/pwd)

RTC_LEVEL_DIRS = $(CWD)/CMOS

.PHONY: all $(RTC_LEVEL_DIRS)
all : $(RTC_OBJECTS) $(RTC_LEVEL_DIRS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ] $@"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<

$(RTC_LEVEL_DIRS) : 
	@echo "[ MAKE ] Kernel/Drivers/Time/RTC/$@"
	@$(MAKE) --directory=$@