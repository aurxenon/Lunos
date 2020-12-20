.code32

.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
multiboot_start:
.long MAGIC
.long FLAGS
.long CHECKSUM
multiboot_end:

/*16kb stack*/
.section .bss
.align 64
stack_begin:
.skip 1024 * 64
stack_end:

.section .paging_area
.align 4096
paging_area_begin:
.skip 4096 * 2

.section .text
.extern kmain

.global _start

_start:
	mov %ebp, stack_begin
	mov %esp, stack_end

	pushl %eax /*magic*/
	pushl %ebx /*multiboot information*/
	pushl $paging_area_begin
	call kmain

loop:
    hlt
    jmp loop
