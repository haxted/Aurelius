#include <panic.h>
#include <stddef.h>

void _panic(const char* reason, int line, const char* file) {
    StackFrame* s = NULL;
    __asm__ volatile("movl %%ebp, %0" : "=r"(s));
    printf("[panic] kernel panic -- %s\n", reason);
    printf("-- at %s:%d\n", file, line);
    while(s) {
        printf("-- at %x\n", s->ret);
        s = s->n;
    } 
    printf("halting.\n");
    __asm__ volatile("cli; hlt");
}