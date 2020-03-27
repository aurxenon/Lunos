TOPDIR = $(LUNOS_DIR)

INCLUDES = -I$(TOPDIR)/Libs

CC  = $(TOPDIR)/Toolchain/Local/bin/i686-elf-gcc
CXX = $(TOPDIR)/Toolchain/Local/bin/i686-elf-g++
AS  = $(TOPDIR)/Toolchain/Local/bin/i686-elf-g++
LD  = $(TOPDIR)/Toolchain/Local/bin/i686-elf-g++

CFLAGS = -g -m32 -Wall -march=pentium

QUIET=>/dev/null