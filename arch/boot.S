/* arch/boot.S — Multiboot header (GRUB) + 32-bit entry */
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

/* Keep the header in a loadable segment */
.section .multiboot, "a"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Tiny stack (16 KiB) */
.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:

.section .text
.code32
.global _start
.extern kmain

_start:
    mov $stack_top, %esp
    call kmain
1:  hlt
    jmp 1b
