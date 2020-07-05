include ../../kernel.mk

TIME_OBJECTS =  $(OBJDIR)/TimeDriver.o

all : Time

Time : $(TIME_OBJECTS)

CWD = $(shell /bin/pwd)

TIME_LEVEL_DIRS =  $(CWD)/RTC
TIME_LEVEL_DIRS += $(CWD)/Timer

.PHONY: all $(TIME_LEVEL_DIRS)
all : $(TIME_OBJECTS) $(TIME_LEVEL_DIRS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<

$(TIME_LEVEL_DIRS) : 
	@echo "[ MAKE ]  $(shell realpath --relative-to=$(TOPDIR) $@)"
	@$(MAKE) --directory=$@