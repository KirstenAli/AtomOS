# Cross toolchain
CROSS_CC := i686-elf-gcc
CROSS_LD := i686-elf-ld

# Flags
CFLAGS   := -m32 -ffreestanding -Os -fno-stack-protector -fno-pic -nostdlib -Wall -Wextra -Iinclude
LDFLAGS  := -m elf_i386 -T linker.ld -nostdlib

# Sources
SRC_C := \
  drivers/vga.c \
  drivers/console.c \
  drivers/keyboard.c \
  lib/util.c \
  lib/input.c \
  apps/parser.c \
  apps/calc.c \
  kernel/kernel.c

OBJ_C := $(SRC_C:.c=.o)

# Phony
.PHONY: all clean run iso grubiso run_iso check_grub

# Default
all: kernel.elf

# Assemble boot in arch/
arch/boot.o: arch/boot.S
	$(CROSS_CC) $(CFLAGS) -c $< -o $@

# Compile C
%.o: %.c
	$(CROSS_CC) $(CFLAGS) -c $< -o $@

# Link kernel
kernel.elf: arch/boot.o $(OBJ_C)
	$(CROSS_LD) $(LDFLAGS) -o $@ $^

# Run directly (no ISO needed)
run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

# Stage ELF in iso/ (no ISO creation)
iso: kernel.elf
	mkdir -p iso/boot
	cp kernel.elf iso/boot/kernel.elf

# Optional GRUB ISO (requires grub-mkrescue + xorriso)
check_grub:
	@command -v grub-mkrescue >/dev/null 2>&1 || { \
	  echo "grub-mkrescue not found. On macOS: brew install qemu xorriso grub-pc-bin"; \
	  exit 1; }

grubiso: check_grub kernel.elf
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	printf 'set timeout=0\nset default=0\n\nmenuentry \"AtomOS\" {\n    multiboot /boot/kernel.elf\n    boot\n}\n' > iso/boot/grub/grub.cfg
	grub-mkrescue -o atomos.iso iso

run_iso: grubiso
	qemu-system-i386 -cdrom atomos.iso

clean:
	rm -f arch/boot.o $(OBJ_C) kernel.elf kernel.o
	rm -rf iso atomos.iso
