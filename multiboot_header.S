/* Multiboot header (GRUB) + entry */
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

/* Must be allocatable so it’s placed in a loadable segment */
.section .multiboot, "a"
.balign 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global _start
_start:
    call kmain
1:  hlt
    jmp 1b
