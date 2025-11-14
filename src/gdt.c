#include <gdt.h>
#include <stdio.h>

static GDTEntry gdt[3];
static GDTPtr gdtPtr;

void loadGdt(GDTPtr* p);

void gdtInit() {
    gdt[0].baseLo = 0;
    gdt[0].baseHi = 0;
    gdt[0].baseMi = 0;
    gdt[0].access = 0;
    gdt[0].granularity = 0;
    gdt[0].limitLo = 0;

    /* kernel code */
    gdt[1].baseLo = 0;
    gdt[1].baseMi = 0;
    gdt[1].baseHi = 0;
    gdt[1].limitLo = 0xFFFF;
    gdt[1].access = 0b10011011;
    gdt[1].granularity = 0b11001111;

    /* kernel data */
    gdt[2].baseLo = 0;
    gdt[2].baseMi = 0;
    gdt[2].baseHi = 0;
    gdt[2].limitLo = 0xFFFF;
    gdt[2].access = 0b10010011;
    gdt[2].granularity = 0b11001111;

    gdtPtr.offset = (uint32_t)&gdt;
    gdtPtr.size = sizeof(gdt) - 1;
    loadGdt(&gdtPtr);
    printf("[x86] initialized gdt\n");
}