include kernel.mk

KERNEL_LEVEL_DIRS =  Arch/x86
KERNEL_LEVEL_DIRS += Drivers
KERNEL_LEVEL_DIRS += Include/Log
KERNEL_LEVEL_DIRS += Init
KERNEL_LEVEL_DIRS += System
KERNEL_LEVEL_DIRS += ../Libs/LibLunos

.PHONY: all $(KERNEL_LEVEL_DIRS)
all	: clean dir $(KERNEL_LEVEL_DIRS) LunosKernel

dir :
	@mkdir $(OBJDIR)
	@mkdir $(BINDIR)

clean :
	@echo "[ CLEAN ]"
	@rm -rf $(OBJDIR) $(BINDIR)

LunosKernel : ${OBJECTS}
	@echo "[ LD ] $@"
	@${LD} -o $(BINDIR)/LunosKernel ${LDFLAGS} $(shell find $(OBJDIR) -name '*.o')

$(KERNEL_LEVEL_DIRS) :
	@echo "[ MAKE ] Kernel/$@"
	@$(MAKE) --directory=$@