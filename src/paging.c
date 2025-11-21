#include <paging.h>
#include <string.h>


__attribute__((aligned(0x1000)))
static uint32_t initialPageDir[1024];
uint32_t* pagedir = (uint32_t*)initialPageDir;

void mapAddr(void* phys, void* virt, int flags) {
    uint32_t v = (uint32_t)virt;
    uint32_t p = (uint32_t)phys;

    if((v % 4096) || (p % 4096)) {
        printf("[paging] please align your addrs\n");
        return;
    }

    uint32_t off = GET_OFF(virt);
    uint32_t pt = GET_PT(virt);
    uint32_t pd = GET_PD(virt);

    uint32_t pde = pagedir[pd];

    if(!(pde & PDE_PRESENT)) {
        uint32_t t = (uint32_t)pmmAllocPage();
        memset((void*)t, 0, 4096);
        pagedir[pd] = t | PDE_PRESENT | PDE_US | PDE_RW;
        pde = pagedir[pd];
    }
    uint32_t* pagetable = (uint32_t*)(pde & PDE_PHYS);
    pagetable[pt] = ((uint32_t)phys) | flags;
}

void initPaging(uint32_t identMapLen) {
    memset(pagedir, 0, 4096);
    mapAddr(pagedir, pagedir, PTE_PRESENT | PTE_RW);
    for(uint32_t i = 0; i < identMapLen; i += 0x1000) {
        mapAddr((void*)i, (void*)i, PTE_PRESENT | PTE_RW);
    }
    __asm__ volatile(
        "movl %0, %%cr3\n\t"
        "movl %%cr0, %%eax\n\t"
        "orl $(1 << 31), %%eax\n\t"
        "movl %%eax, %%cr0\n\t"
        :: "r"((uint32_t)pagedir)
    );
    printf("[paging] initialized paging\n");
}
