#include "../drivers/console.h"
#include "ui.h"

void ui_clear(void) { console_clear(); }

void ui_title(const char *title) {
    console_write(title);
    console_write("\n------------------------------\n");
}

void ui_line(const char *s) {
    console_write(s);
    console_write("\n");
}

void ui_blank(void) { console_write("\n"); }
void ui_prompt(const char *s) { console_write(s); }
