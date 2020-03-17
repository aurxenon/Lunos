TOPDIR := $(shell /bin/pwd)
OBJDIR := ${TOPDIR}/obj
BINDIR := ${TOPDIR}/bin

INCLUDES =  -IInclude/
INCLUDES += -IArch/x86/Include/
INCLUDES += -I$(TOPDIR)
INCLUDES += -I../Libs

### compilers and options
CC = i686-elf-g++
AS = i686-elf-g++
CFLAGS = -m32 -O2 $(INCLUDES) -DKERNEL_INCLUDES -DOF_ELF -DOF_X86 -lobjc -Wall -march=pentium -no-pie -fno-builtin -ffreestanding -lgcc
LD = i686-elf-g++
LDFLAGS	= -T ldscript.ld -Wl,-Map=bin/output.map -ffreestanding -nostdlib
OBJCOPY	= i686-elf-objcopy

### objects
OBJECTS  = $(TOPDIR)/obj/boot.o
OBJECTS += $(TOPDIR)/obj/Init.o
OBJECTS += $(TOPDIR)/obj/KLog.o
OBJECTS += $(TOPDIR)/obj/SerialDevice.o
OBJECTS += $(TOPDIR)/obj/KMalloc.o
OBJECTS += $(TOPDIR)/obj/bastring.o
OBJECTS += $(TOPDIR)/obj/string.o

QUIET=>/dev/null

# target:
all	: clean dir LunosKernel

dir :
	@mkdir $(OBJDIR)
	@mkdir $(BINDIR)
	
LunosKernel : ${OBJECTS}
	@echo "[ LD ] $@"
	@${LD} -o $(BINDIR)/LunosKernel ${LDFLAGS} ${OBJECTS}

clean :
	@echo "[ CLEAN ]"
	@rm -rf $(OBJDIR) $(BINDIR)
	
### rules:
$(TOPDIR)/obj/%.o : $(TOPDIR)/Include/Utils/%.cpp
	@echo "[ CXX ] $@"
	@${CC} ${CFLAGS} -o $@ -c $<

$(TOPDIR)/obj/%.o : $(TOPDIR)/System/%.cpp
	@echo "[ CXX ] $@"
	@${CC} ${CFLAGS} -o $@ -c $<

$(TOPDIR)/obj/%.o : $(TOPDIR)/Drivers/%.cpp
	@echo "[ CXX ] $@"
	@${CC} ${CFLAGS} -o $@ -c $<

$(TOPDIR)/obj/%.o : $(TOPDIR)/../Libs/LibLunos/%.cpp
	@echo "[ CXX ] $@"
	@${CC} ${CFLAGS} -o $@ -c $<

$(TOPDIR)/obj/%.o : $(TOPDIR)/Init/%.cpp
	@echo "[ CXX ] $@"
	@${CC} ${CFLAGS} -o $@ -c $<

$(TOPDIR)/obj/%.o : $(TOPDIR)/Arch/x86/%.s
	@echo "[ AS ]  $@"
	@${AS} -DASSEMBLER ${CFLAGS} -o $@ -c $<