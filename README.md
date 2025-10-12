<p align="center">
  <img src="logo.svg" width="50" alt="AtomOS logo">
</p>

**AtomOS** is a tiny educational operating system written in C and x86 assembly.  
It boots directly using GRUB via the Multiboot specification and runs entirely without an underlying OS or standard library.

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


