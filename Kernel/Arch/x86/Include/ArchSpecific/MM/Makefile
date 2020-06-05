include ../../../../../kernel.mk

MM_OBJECTS =  $(OBJDIR)/MemoryManager.o
MM_OBJECTS += $(OBJDIR)/InterruptManager.o

all : MM

MM : $(MM_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(MM_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ] $@"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<