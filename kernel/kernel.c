#include <stdint.h>
#include "../include/common.h"
#include "../drivers/console.h"
#include "../ui/menu.h"

__attribute__((noreturn)) static inline void halt_forever(void) {
    for (;;) __asm__ __volatile__("hlt");
}

void kmain(void) {
    console_init(DEFAULT_COLOR);
    menu_run_loop(); /* never returns; loops between menus and apps */
    halt_forever();
}
