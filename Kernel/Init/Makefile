include ../kernel.mk

START_OBJECTS = $(OBJDIR)/Init.o

all : Start

Start : $(START_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(START_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<