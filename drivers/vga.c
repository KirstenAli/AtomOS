#include "vga.h"
#include "../arch/ports.h"
#include "../include/common.h"

#define VGA_MEM ((volatile uint16_t*)0xB8000)
#define CRT_IDX  0x3D4
#define CRT_DATA 0x3D5

static uint8_t g_color = DEFAULT_COLOR;
static int cursor = 0; /* linear index */

static inline uint16_t make_cell(char c, uint8_t color) {
    return (uint16_t) c | ((uint16_t) color << 8);
}

static inline void scroll_if_needed(void) {
    if (cursor < COLS * ROWS) return;
    /* scroll up one row */
    for (int i = 0; i < COLS * (ROWS - 1); i++)
        VGA_MEM[i] = VGA_MEM[i + COLS];
    for (int i = COLS * (ROWS - 1); i < COLS * ROWS; i++)
        VGA_MEM[i] = make_cell(' ', g_color);
    cursor = COLS * (ROWS - 1);
}

void vga_init(uint8_t color) {
    g_color = color;
    vga_clear();
}

void vga_set_color(uint8_t color) { g_color = color; }

void vga_clear(void) {
    for (int i = 0; i < COLS * ROWS; i++)
        VGA_MEM[i] = make_cell(' ', g_color);
    cursor = 0;
}

void vga_putc(char c) {
    if (c == '\n') {
        cursor += COLS - (cursor % COLS);
        scroll_if_needed();
        return;
    }
    if (c == '\r') {
        cursor -= (cursor % COLS);
        return;
    }
    if (c == '\b') {
        if (cursor > 0) {
            cursor--;
            VGA_MEM[cursor] = make_cell(' ', g_color);
        }
        return;
    }
    VGA_MEM[cursor++] = make_cell(c, g_color);
    if (cursor % COLS == 0) scroll_if_needed();
}

void vga_write(const char *s) {
    for (int i = 0; s[i]; i++) vga_putc(s[i]);
}

void vga_disable_cursor(void) {
    /* Set bit 5 (cursor disable) in Cursor Start register (0x0A) */
    outb(CRT_IDX, 0x0A);
    outb(CRT_DATA, 0x20);
}

void vga_enable_cursor(uint8_t start, uint8_t end) {
    outb(CRT_IDX, 0x0A);
    outb(CRT_DATA, (inb(CRT_DATA) & 0xC0) | (start & 0x1F));
    outb(CRT_IDX, 0x0B);
    outb(CRT_DATA, (inb(CRT_DATA) & 0xE0) | (end & 0x1F));
}

void vga_move_cursor(int x, int y) {
    uint16_t pos = (uint16_t) (y * COLS + x);
    outb(CRT_IDX, 0x0F);
    outb(CRT_DATA, (uint8_t) (pos & 0xFF));
    outb(CRT_IDX, 0x0E);
    outb(CRT_DATA, (uint8_t) (pos >> 8));
}
