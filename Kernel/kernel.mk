TOPDIR = $(LUNOS_DIR)

include $(TOPDIR)/include.mk

KERNELDIR = $(TOPDIR)/Kernel

OBJDIR    = ${KERNELDIR}/obj
BINDIR    = ${KERNELDIR}/bin

INCLUDES += -I$(KERNELDIR)/Include/
INCLUDES += -I$(KERNELDIR)/Arch/x86/Include/
INCLUDES += -I$(KERNELDIR)

KERNEL_CFLAGS = $(CFLAGS) $(INCLUDES) -DKERNEL_INCLUDES -DOF_ELF -DOF_X86 -lobjc -no-pie -fno-builtin -ffreestanding -lgcc -fno-exceptions -fno-rtti

LDFLAGS	= -g -T ldscript.ld -Wl,-Map=bin/output.map -ffreestanding -nostdlib