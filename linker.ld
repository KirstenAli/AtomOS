OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS {
  . = 1M;

  /* Ensure GRUB always finds the header */
  .multiboot : { KEEP(*(.multiboot)) }

  /* Code & read-only data */
  .text   : ALIGN(4K) { *(.text*) }
  .rodata : ALIGN(4K) { *(.rodata*) }

  /* Writable data */
  .data   : ALIGN(4K) { *(.data*) }

  /* BSS (optionally mark NOLOAD—fine either way) */
  .bss (NOLOAD) : ALIGN(4K) { *(COMMON) *(.bss*) }

  /* Strip junk we don’t need in a freestanding kernel */
  /DISCARD/ : {
    *(.comment) *(.note*) *(.eh_frame) *(.eh_frame_hdr) *(.gcc_except_table)
  }
}
