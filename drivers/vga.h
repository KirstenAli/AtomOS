#ifndef VGA_H
#define VGA_H
#include <stdint.h>

void vga_init(uint8_t color);

void vga_set_color(uint8_t color);

void vga_clear(void);

void vga_putc(char c);

void vga_write(const char *s);

void vga_disable_cursor(void);

void vga_enable_cursor(uint8_t start, uint8_t end);

void vga_move_cursor(int x, int y);

#endif
