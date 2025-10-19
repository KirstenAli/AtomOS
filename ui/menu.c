#include <stdbool.h>
#include "../drivers/console.h"
#include "../drivers/keyboard.h"
#include "../apps/registry.h"
#include "../drivers/vga.h"
#include "../include/common.h"
#include "ui.h"

typedef enum { SCREEN_HOME, SCREEN_MY_APPS } Screen;

static char read_nav_key(void) {
    /* Returns one of: 'u' (up), 'd' (down), '\n' (enter), 27 (esc) */
    for (;;) {
        char c = kbd_getch_blocking();
        if (c == '\n' || c == 27) return c;
        if (c == 'w' || c == 'W' || c == 'k' || c == 'K') return 'u';
        if (c == 's' || c == 'S' || c == 'j' || c == 'J') return 'd';
        /* ignore others */
    }
}

static void draw_home(int sel) {
    ui_clear();
    ui_title("AtomOS (C)");
    ui_line(sel == 0 ? "> My Apps" : "  My Apps");
    ui_blank();
    ui_line("Navigate: w/s (or k/j), Enter to select");
}

static void draw_my_apps(int sel) {
    ui_clear();
    ui_title("My Apps");
    int count = 0;
    const App *apps = get_apps(&count);
    for (int i = 0; i < count; i++) {
        console_write(i == sel ? "> " : "  ");
        console_write(apps[i].name);
        console_write("\n");
    }
    ui_blank();
    ui_line("Navigate: w/s (or k/j), Enter to run, Esc to go back");
}

static inline void menu_reset_ui(void) {
    vga_set_color(DEFAULT_COLOR);
    ui_clear();
}

static inline int clamp_sel(int sel, int count) {
    if (count <= 0) return 0;
    if (sel < 0) return 0;
    if (sel >= count) return count - 1;
    return sel;
}

static inline int wrap_up(int sel, int count) { return count ? (sel + count - 1) % count : 0; }
static inline int wrap_down(int sel, int count) { return count ? (sel + 1) % count : 0; }

static void handle_home_screen(int *sel, Screen *screen) {
    draw_home(*sel);
    char k = read_nav_key();

    if (k == 'u' || k == 'd') {
        *sel = 0; // only one focusable item on home? keep as-is
    } else if (k == '\n') {
        *screen = SCREEN_MY_APPS;
        *sel = 0;
    } else if (k == 27) {
        // Esc on home: no-op
    }
}

static void run_app_with_cleanup(void (*entry)(void)) {
    entry();
    menu_reset_ui();
}

static void handle_my_apps_screen(int *sel, Screen *screen) {
    int count = 0;
    const App *apps = get_apps(&count);

    *sel = clamp_sel(*sel, count);

    draw_my_apps(*sel);
    char k = read_nav_key();

    if (k == 'u' && count) {
        *sel = wrap_up(*sel, count);
    } else if (k == 'd' && count) {
        *sel = wrap_down(*sel, count);
    } else if (k == 27) {
        *screen = SCREEN_HOME;
        *sel = 0;
    } else if (k == '\n' && count) {
        run_app_with_cleanup(apps[*sel].run);
    }
}

void menu_run_loop(void) {
    Screen screen = SCREEN_HOME;
    int sel = 0;

    for (;;) {
        if (screen == SCREEN_HOME) {
            handle_home_screen(&sel, &screen);
        } else {
            handle_my_apps_screen(&sel, &screen);
        }
    }
}
