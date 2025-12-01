#include <paging.h>
#include <string.h>


extern uint8_t* bitmap;
extern uint32_t bitmapLn;

__attribute__((aligned(0x1000)))
static uintptr_t initialPageDir[1024];
uintptr_t* pagedir = (uintptr_t*)initialPageDir;

void mapAddr(void* phys, void* virt, int flags) {
    uintptr_t v = (uintptr_t)virt;
    uintptr_t p = (uintptr_t)phys;

    if((v % 4096) || (p % 4096)) {
        printf("[paging] please align your addrs\n");
        return;
    }

    uint32_t off = GET_OFF(virt);
    uint32_t pt = GET_PT(virt);
    uint32_t pd = GET_PD(virt);



    if(!(pagedir[pd] & PDE_PRESENT)) {
        uintptr_t t = (uintptr_t)pmmAllocPage();
        memset((void*)t, 0, 4096);
        pagedir[pd] = t | PDE_PRESENT | PDE_US | PDE_RW;
    }
    uintptr_t* pagetable = (uintptr_t*)(pagedir[pd] & PDE_PHYS);
    pagetable[pt] = ((uintptr_t)phys) | flags;
}

extern char __kernel_start[];
extern char __kernel_end[];
extern char __text_start[];
extern char __text_end[];
extern char __rodata_start[];
extern char __rodata_end[];
extern char __data_start[];
extern char __data_end[];
extern char __bss_start[];
extern char __bss_end[];


void initPaging(void* begin, void* end, multiboot_info_t* mbinfo) {
    if(((uintptr_t)begin % 4096 || (uintptr_t)end % 4096)) {
        printf("[paging] please align your addrs\n");
        return;
    }
    memset(pagedir, 0, 4096);
    mapAddr(pagedir, pagedir, PTE_PRESENT | PTE_RW);


    for(void* i = (void*)ROUND_DOWN(__text_start); i < (void*)ROUND_UP(__text_end); i += 0x1000) {
        mapAddr(i, i, PTE_PRESENT);
    }

    for(void* i = (void*)ROUND_DOWN(__rodata_start); i < (void*)ROUND_UP(__rodata_end); i += 0x1000) {
        mapAddr(i, i, PTE_PRESENT);
    }
    
    for(void* i = (void*)ROUND_DOWN(__data_start); i < (void*)ROUND_UP(__data_end); i += 0x1000) {
        mapAddr(i, i, PTE_PRESENT | PTE_RW);
    }

    for(void* i = (void*)ROUND_DOWN(__bss_start); i < (void*)ROUND_UP(__bss_end); i += 0x1000) {
        mapAddr(i, i, PTE_PRESENT | PTE_RW);
    }

    for(void* i = (void*)ROUND_UP(begin); i < (void*)ROUND_UP(end); i += 0x1000) {
        mapAddr(i, i, PTE_PRESENT | PTE_RW);
    }


    for(void* i = (void*)mbinfo->framebuffer_addr; i < (void*)(uintptr_t)ROUND_UP(mbinfo->framebuffer_addr + (mbinfo->framebuffer_width * mbinfo->framebuffer_height * (mbinfo->framebuffer_bpp / 8))); i += 0x1000) {
        mapAddr(i, i, PTE_PRESENT | PTE_RW);
    }

    for(void* i = (void*)bitmap; i < (void*)ROUND_UP((uintptr_t)(bitmap + bitmapLn)); i += 0x1000) {
        mapAddr(i, i, PTE_PRESENT | PTE_RW);
    }

    // FUCKKIT
    // for(void* i = (void*)(0x209000); i < (void*)(uintptr_t)ROUND_UP((uintptr_t)(__kernel_end + 0x200000)); i += 0x1000) {
    //     mapAddr(i, i, PTE_PRESENT | PTE_RW);
    // }


    __asm__ volatile(
        "movl %0, %%cr3\n\t"
        "movl %%cr0, %%eax\n\t"
        "orl $(1 << 31), %%eax\n\t"
        "movl %%eax, %%cr0\n\t"
        :: "r"((uintptr_t)pagedir)
    );
    printf("[paging] initialized paging\n");
}
