#include <gdt.h>
#include <stdio.h>
#include <string.h>

static GDTEntry gdt[6];
static GDTPtr gdtPtr;
static TSSEntry tss;
extern uintptr_t stack;
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
    // user code segment
    gdt[3].baseLo = 0;
    gdt[3].baseMi = 0;
    gdt[3].baseHi = 0;
    gdt[3].limitLo = 0xFFFF;
    gdt[3].access = 0b11111011;
    gdt[3].granularity = 0b11001111;

    // user data segment
    gdt[4].baseLo = 0;
    gdt[4].baseMi = 0;
    gdt[4].baseHi = 0;
    gdt[4].limitLo = 0xFFFF;
    gdt[4].access = 0b11110011;
    gdt[4].granularity = 0b11001111;

    memset(&tss, 0, sizeof(TSSEntry));
    
    tss.esp0 = stack;
    tss.ss0 = 0x10;
    // tss
    gdt[5].limitLo = sizeof(TSSEntry) - 1;
    gdt[5].baseLo = ((uintptr_t)&tss) & 0xFFFF;
    gdt[5].baseMi = ((uintptr_t)&tss >> 16) & 0xFF;
    gdt[5].baseHi = ((uintptr_t)&tss >> 24) & 0xFF;
    gdt[5].access = 0b10000001;
    gdt[5].granularity = 0b01000000;
    

    gdtPtr.offset = (uint32_t)&gdt;
    gdtPtr.size = sizeof(gdt) - 1;
    loadGdt(&gdtPtr);
    printf("[x86] initialized gdt\n");
}