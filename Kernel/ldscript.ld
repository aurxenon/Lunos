OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386);
ENTRY(_start)
SECTIONS
{
  . = 1M;
  .text BLOCK(4K) : ALIGN(4K)
  {
    *(.multiboot)
    *(.paging_area)
    *(.text)
  }

  .rodata BLOCK(4K) : ALIGN(4K)
	{
    *(.rodata)
	}
	
  .data BLOCK(4K) : ALIGN(4K)
	{
    *(.data)
	}
	
  .bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
 }