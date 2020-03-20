include ../kernel.mk

SYSTEM_OBJECTS = $(OBJDIR)/KMalloc.o

all : System

System : $(SYSTEM_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(SYSTEM_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ] $@"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<