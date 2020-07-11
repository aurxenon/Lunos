include ../../kernel.mk

PCI_OBJECTS = $(OBJDIR)/PCI.o

all : PCIDriver

PCIDriver : $(PCI_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(PCI_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<