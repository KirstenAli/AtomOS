#include <stdint.h>

#define VGA   ((volatile uint16_t*)0xB8000)
#define COLS  80
#define ROWS  25
#define COLOR 0x0F  /* bright white on black */

static inline uint16_t make_cell(char c, uint8_t color) {
    return (uint16_t) c | ((uint16_t) color << 8);
}

static inline void clear_screen(uint8_t color) {
    for (int i = 0; i < COLS * ROWS; i++) {
        VGA[i] = make_cell(' ', color);
    }
}

__attribute__((noreturn))
static inline void halt_forever(void) {
    for (;;) __asm__ __volatile__("hlt");
}

static inline void print(const char *s) {
    for (int i = 0; s[i]; i++) {
        VGA[i] = make_cell(s[i], COLOR);
    }
}

void kmain(void) {
    clear_screen(COLOR);
    print("AtomOS (C): Hello, world!");
    halt_forever();
}
