#include <io.h>

uint8_t inb(uint16_t port) {
    uint8_t out = 0;
    __asm__ volatile(
        "in %1, %0"
        : "=a"(out)
        : "d"(port)
    );
}

void outb(uint8_t dat, uint16_t port) {
    __asm__ volatile(
        "out %0, %1"
        :: "a"(dat), "d"(port)
    );
}