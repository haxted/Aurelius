#include <gdt.h>
#include <stdio.h>
#include <idt.h>
#include <panic.h>
#include <serial.h>
#include <multiboot.h>
#include <pmm.h>

void kmain(multiboot_info_t* mbinfo) {
    initSerial();
    gdtInit();
    idtInit();
    initPmm(mbinfo);
    printf("%x\n", pmmAllocPage());
    printf("[sys] system initialized\n%dK memory.\n", mbinfo->mem_lower + mbinfo->mem_upper);
    panic("Nothing.");
}