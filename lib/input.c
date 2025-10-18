#include "input.h"
#include "../drivers/keyboard.h"
#include "../drivers/console.h"

int input_read_line(char *buf, int maxlen, const char *prompt) {
    int len = 0;
    if (prompt) console_write(prompt);
    for (;;) {
        char c = kbd_getch_blocking();
        if (c == '\n') {
            console_putc('\n');
            buf[len] = 0;
            return len;
        }
        if (c == '\b') {
            if (len > 0) {
                len--;
                console_putc('\b');
            }
            continue;
        }
        if (len < maxlen - 1) {
            buf[len++] = c;
            console_putc(c);
        }
    }
}
