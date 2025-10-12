<p align="center">
  <img src="logo.svg" width="140" alt="AtomOS logo">
</p>

**AtomOS** is a tiny educational operating system kernel written in C and x86 assembly.

<p align="center">
  <img src="https://img.shields.io/badge/language-C-blue?style=flat-square" alt="C">
  <img src="https://img.shields.io/badge/arch-x86--32-red?style=flat-square" alt="x86-32">
  <img src="https://img.shields.io/badge/build-Makefile-lightgrey?style=flat-square" alt="Makefile">
</p>

---

## 🚀 Features

- Bootable via **GRUB (Multiboot spec)**
- Written in **pure C + minimal x86 assembly**
- Runs in **32-bit protected mode**
- Prints directly to **VGA text buffer (0xB8000)**
- Minimal kernel — perfect for learning low-level concepts

---

## 🧰 Build & Run (macOS)

### Install dependencies

```bash
brew install i686-elf-binutils i686-elf-gcc i686-elf-grub xorriso mtools qemu
make
make iso
make run
```

---

## 📋 To Do

- Tiny terminal output (VGA helpers)
- Keyboard input (polling)
- Programmable Interval Timer (PIT)
- Frame loop & simple renderer
- Color support
- Panic screen
- IDT (interrupts)
- PIC remap
- GDT (own descriptors)
- Parse Multiboot memory map
- Paging (MMU)
- Simple memory allocator



