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
#include <module.h>
#include <ustar.h>
#include <string.h>
#include <flanterm/src/flanterm.h>
#include <flanterm/src/flanterm_backends/fb.h>
extern char __kernel_start[];
struct flanterm_context* fctx = NULL;

void kmain(multiboot_info_t* mbinfo) {
    fctx = flanterm_fb_init(
        NULL, NULL,
        (uint32_t*)mbinfo->framebuffer_addr,
        mbinfo->framebuffer_width, mbinfo->framebuffer_height,
        mbinfo->framebuffer_pitch, mbinfo->framebuffer_red_mask_size,
        mbinfo->framebuffer_red_field_position, mbinfo->framebuffer_green_mask_size,
        mbinfo->framebuffer_green_field_position, mbinfo->framebuffer_blue_mask_size,
        mbinfo->framebuffer_blue_field_position, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1,
        0, 0, 0
    );
    initSerial();
    gdtInit();
    idtInit();
    initPmm(mbinfo);


    initPaging((void*)NULL, (void*)__kernel_start, mbinfo);
    uintptr_t end = 0;
    char* mod = getModuleByFileName("tarfs", mbinfo, &end);
    printf("[sys] system initialized\n");
    panic("Hello");
}