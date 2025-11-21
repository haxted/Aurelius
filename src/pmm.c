#include <pmm.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <panic.h>
uint8_t* bitmap = NULL;
uint32_t systemPageNumber = 0;
uint32_t bitmapLn = 0;


void initPmm(multiboot_info_t* mbinfo) {
    uint32_t totalMem = 0;
    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbinfo->mmap_addr;
    int k = 0;
    uint32_t bitmapLen = 0;
    while(k < mbinfo->mmap_length) {
        if(mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
            if(mmap->addr + mmap->len > totalMem) {
                totalMem = mmap->addr + mmap->len;
            }
        }
        k += mmap->size;
        mmap += mmap->size;
    }
    uint32_t totalPages = totalMem / 4096;
    uint32_t bitmapBytes = totalPages / 8;
    systemPageNumber = totalPages;
    bitmapLen = bitmapBytes;
    bitmapLn = bitmapLen;

    printf("[pmm] total memory: %d\n", totalMem);
    mmap = (multiboot_memory_map_t*)mbinfo->mmap_addr;
    k = 0;
    while(k < mbinfo->mmap_length) {
        printf("[pmm] mmap->type = %x\n[pmm] mmap->addr = %x\n[pmm] mmap->len = %x\n[pmm] mmap->size = %x\n", mmap->type, mmap->addr, mmap->len, mmap->size);
        if(mmap->len >= bitmapBytes) {
            printf("[pmm] found area\n");
            bitmap = (uint8_t*)mmap->addr;
            break;
        }
        if(k == mbinfo->mmap_length) {
            printf("[pmm] found no area\n");
            return;
        }
        
        k += mmap->size;
        mmap += mmap->size;
    }
    memset(bitmap, 0xFF, bitmapLen);
    k = 0;
    mmap = (multiboot_memory_map_t*)mbinfo->mmap_addr;
    while(k < mbinfo->mmap_length) {
        int s = mmap->size;
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
    for(uint8_t* j = bitmap; j < (bitmap + bitmapLen); j += 0x1000) {
        int offPage = (uint32_t)j / 4096;
        int offByte = offPage / 8;
        int offBit = offPage % 8;
        bitmap[offByte] |= (1 << offBit);
    }
    printf("[pmm] initialized pmm\n");
}

void* pmmAllocPage(void) {
    unsigned pageFound = 0;
    for(unsigned i = 0; i < systemPageNumber; i++) {
        unsigned byteOff = i / 8;
        if(bitmap[byteOff] == 0xff)
            continue;
        unsigned bitOff = i % 8;
        int bit = (bitmap[byteOff] >> bitOff) & 1;
        if(!bit) {
            pageFound = i;
            bitmap[byteOff] |= (1 << bitOff);
            return (void*)(pageFound * 4096);
        }
    }
    
    return NULL;
}

void pmmFreePage(void* ptr) {
    uint32_t u = (uint32_t)ptr;
    unsigned page = u / 4096;
    unsigned byte = page / 8;
    unsigned bit = page % 8;
    if(!((bitmap[byte] >> bit) & 1)) {
        return; // already free
    }
    bitmap[byte] &= ~(1 << bit);
}