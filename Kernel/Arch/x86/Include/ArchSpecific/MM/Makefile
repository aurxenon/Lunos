include ../../../../../kernel.mk

MM_OBJECTS =  $(OBJDIR)/MemoryManager.o
MM_OBJECTS += $(OBJDIR)/InterruptManager.o
MM_OBJECTS += $(OBJDIR)/PIC.o
MM_OBJECTS += $(OBJDIR)/PageTable.o
MM_OBJECTS += $(OBJDIR)/PageDirectory.o
MM_OBJECTS += $(OBJDIR)/GDT.o

all : MM

MM : $(MM_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(MM_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<