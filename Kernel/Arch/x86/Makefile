include ../../kernel.mk

X86_OBJECTS = $(OBJDIR)/boot.o

all : X86

X86 : $(X86_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(X86_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.s
	@echo "[ AS ]  $@"
	@${AS} ${KERNEL_CFLAGS} -o $@ -c $<