#include <gdt.h>
#include <stdio.h>
#include <idt.h>
#include <panic.h>
#include <serial.h>
#include <multiboot.h>
#include <pmm.h>
#include <paging.h>
#include <stddef.h>

void kmain(multiboot_info_t* mbinfo) {
    initSerial();
    gdtInit();
    idtInit();
    initPmm(mbinfo);
    void* x = pmmAllocPage();
    printf("%x\n", x);

    x = pmmAllocPage();
    printf("%x\n", x);
    
    initPaging((void*)NULL, (void*)0x400000);

    printf("[sys] system initialized\n%dM memory.\n", (mbinfo->mem_lower + mbinfo->mem_upper) / 1024);
    panic("Nothing.");
}