#include <gdt.h>
#include <stdio.h>
#include <idt.h>
void kmain() {
    gdtInit();
    idtInit();
    printf("[sys] system initialized");
}