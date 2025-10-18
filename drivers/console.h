#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdint.h>

void console_init(uint8_t color);

void console_clear(void);

void console_putc(char c);

void console_write(const char *s);

void console_newline(void);

void console_write_dec(int value);

#endif
