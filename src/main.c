#include <gdt.h>
#include <stdio.h>
#include <idt.h>
#include <panic.h>


void kmain() {
    gdtInit();
    idtInit();
    printf("[sys] system initialized\n");
    panic("Nothing.");
}