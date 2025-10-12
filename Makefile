TARGET   = i686-elf
CC       = $(TARGET)-gcc
LD       = $(TARGET)-ld
AS       = $(TARGET)-as
GRUBMK   = i686-elf-grub-mkrescue
QEMU     = qemu-system-i386

CFLAGS   = -m32 -ffreestanding -Os -fno-stack-protector -fno-pic -nostdlib -Wall -Wextra
LDFLAGS  = -m elf_i386 -T linker.ld -nostdlib

.PHONY: all iso run clean

all: kernel.elf

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

multiboot_header.o: multiboot_header.S
	$(AS) --32 $< -o $@

kernel.elf: multiboot_header.o kernel.o linker.ld
	$(LD) $(LDFLAGS) -o $@ multiboot_header.o kernel.o

iso: kernel.elf
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/
	$(GRUBMK) -o atomos.iso iso

run: iso
	$(QEMU) -cdrom atomos.iso

clean:
	rm -f *.o *.elf atomos.iso
	rm -rf iso/boot/kernel.elf

