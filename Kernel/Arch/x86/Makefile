include ../../kernel.mk

X86_OBJECTS = $(OBJDIR)/boot.o

all : X86

X86 : $(X86_OBJECTS)

CWD = $(shell /bin/pwd)

X86_LEVEL_DIRS = $(CWD)/Include/ArchSpecific/MM

.PHONY: all $(X86_LEVEL_DIRS)
all : $(X86_OBJECTS) $(X86_LEVEL_DIRS)

$(OBJDIR)/%.o : $(CWD)/%.s
	@echo "[ AS ]    $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${AS} ${KERNEL_CFLAGS} -o $@ -c $<

$(X86_LEVEL_DIRS) : 
	@echo "[ MAKE ]  $(shell realpath --relative-to=$(TOPDIR) $@)"
	@$(MAKE) --directory=$@