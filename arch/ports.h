#pragma once
#include <stdint.h>

/*
 * If we're not compiling for x86, provide harmless stubs so clangd (e.g. on arm64)
 * doesn't complain. The real x86 versions below are used when building with
 * i686-elf-gcc.
 */
#if !defined(__i386__) && !defined(__x86_64__)

/* Stub implementations for non-x86 environments */
static inline uint8_t inb(uint16_t port) {
    (void) port;
    return 0;
}

static inline void outb(uint16_t port, uint8_t val) {
    (void) port;
    (void) val;
}

static inline void io_wait(void) {
    /* no-op */
}

#else /* x86 real implementations */

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0"
        : "=a"(ret)
        : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__("outb %0, %1"
        :
        : "a"(val), "Nd"(port));
}

static inline void io_wait(void) {
    (void) inb(0x80); /* tiny delay */
}

#endif /* x86 */
