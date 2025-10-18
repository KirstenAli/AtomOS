#include <stdint.h>
#include "../include/common.h"
#include "../drivers/console.h"
#include "../apps/calc.h"

__attribute__((noreturn)) static inline void halt_forever(void) {
    for (;;) __asm__ __volatile__("hlt");
}

void kmain(void) {
    console_init(DEFAULT_COLOR);
    console_write("AtomOS (C)\n");
    calc_run();
    halt_forever();
}
