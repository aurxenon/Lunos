include ../../Kernel/kernel.mk

LIBLUNOS_OBJECTS =  $(OBJDIR)/bastring.o
LIBLUNOS_OBJECTS += $(OBJDIR)/string.o
LIBLUNOS_OBJECTS += $(OBJDIR)/stdlib.o
LIBLUNOS_OBJECTS += $(OBJDIR)/ConvertNums.o
LIBLUNOS_OBJECTS += $(OBJDIR)/sstream.o
LIBLUNOS_OBJECTS += $(OBJDIR)/Vector.o

all : LibLunos

LibLunos : $(LIBLUNOS_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(LIBLUNOS_OBJECTS)

#RIGHT NOW LIBLUNOS IS BUILT UNDER KERNEL ASSUMPTIONS

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ] $@"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<