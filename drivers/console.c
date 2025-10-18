#include "console.h"
#include "vga.h"
#include "../include/common.h"
#include "../lib/util.h"

void console_init(uint8_t color) { vga_init(color); }
void console_clear(void) { vga_clear(); }
void console_putc(char c) { vga_putc(c); }
void console_write(const char *s) { vga_write(s); }
void console_newline(void) { vga_putc('\n'); }

void console_write_dec(int value) {
    char buf[32];
    itoa_dec(value, buf, sizeof(buf));
    vga_write(buf);
}
