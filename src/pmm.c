#include <pmm.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <panic.h>
uint8_t* bitmap = NULL;
uint32_t systemPageNumber = 0;


void initPmm(multiboot_info_t* mbinfo) {
    uint32_t totalMem = (mbinfo->mem_lower + mbinfo->mem_upper) * 1000;
    uint32_t totalPages = totalMem / 4096;
    uint32_t totalBytes = totalPages / 8;
    systemPageNumber = totalPages;
    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbinfo->mmap_addr;
    int k = 0;
    uint32_t bitmapLen = 0;
    while(k < mbinfo->mmap_length) {
        if(mmap->len >= totalBytes) {
            printf("[pmm] found area\n");
            bitmap = (uint8_t*)mmap->addr;
            bitmapLen = totalBytes;
            break;
        }
        if(k == mbinfo->mmap_length) {
            printf("[pmm] found no area\n");
            return;
        }
        k += sizeof(struct multiboot_mmap_entry);
        mmap += sizeof(struct multiboot_mmap_entry);
    }
    memset(bitmap, 0xFF, bitmapLen);
    k = 0;
    mmap = (multiboot_memory_map_t*)mbinfo->mmap_addr;
    while(k <= mbinfo->mmap_length) {
        int s = sizeof(struct multiboot_mmap_entry);
        if(mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
            for(uint32_t z = mmap->addr; z < (mmap->addr + mmap->len); z += 0x1000) {
                int offPage = z / 4096;
                int offByte = offPage / 8;
                int offBit = offPage % 8;
                bitmap[offByte] &= ~(1 << offBit);
            }
        }
        k += s;
        mmap += s;
    }
    printf("[pmm] initialized pmm\n");
}

void* pmmAllocPage(void) {
    unsigned pageFound = 0;
    for(unsigned i = 0; i < systemPageNumber; i++) {
        unsigned byteOff = i / 8;
        unsigned bitOff = i % 8;
        int bit = (bitmap[byteOff] >> bitOff) & 1;
        if(!bit) {
            pageFound = i;
        }
    }
    if(!pageFound) 
        return NULL;
    return (void*)(pageFound * 4096);
}