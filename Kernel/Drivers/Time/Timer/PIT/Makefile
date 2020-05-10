include ../../../../kernel.mk

PIT_OBJECTS = $(OBJDIR)/PIT.o

all : PIT_DRIVER

PIT_DRIVER : $(PIT_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(PIT_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ] $@"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<