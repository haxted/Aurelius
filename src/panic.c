#include <panic.h>


void _panic(const char* reason, int line, const char* file) {
    printf("[panic] kernel panic -- %s\n", reason);
    printf("-- at %s:%d\n", file, line);
    printf("halting.\n");
    __asm__ volatile("cli; hlt");
}