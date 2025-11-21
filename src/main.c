#include <gdt.h>
#include <stdio.h>
#include <idt.h>
#include <panic.h>
#include <serial.h>
#include <multiboot.h>
#include <pmm.h>
#include <paging.h>
#include <pit.h>
#include <stddef.h>
#include <pic.h>

void kmain(multiboot_info_t* mbinfo) {
    initSerial();
    gdtInit();
    idtInit();
    initPmm(mbinfo);
 
    initPaging((void*)NULL, (void*)0x400000);
    printf("[sys] system initialized\n");
    panic("Hello");
}