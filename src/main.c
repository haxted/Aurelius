#include <gdt.h>
#include <stdio.h>
#include <idt.h>
#include <panic.h>
#include <serial.h>


void kmain() {
    initSerial();
    gdtInit();
    idtInit();
    printf("[sys] system initialized\n");
    panic("Nothing.");
}