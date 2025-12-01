#include <module.h>
#include <stddef.h>
#include <panic.h>
#include <string.h>

// extremely unsafe, do NOT use this function
void* getModuleByFileName(const char* fileName, multiboot_info_t* mbinfo, uintptr_t* end) {
    if(!fileName || !mbinfo) return NULL;
    if(!mbinfo->mods_count)
        panic("No modules found");
    multiboot_module_t* modList = (multiboot_module_t*)mbinfo->mods_addr;
    for(int i = 0; i < mbinfo->mods_count; i++) {
        if(!memcmp((void*)modList->cmdline, fileName, strlen(fileName))) {
            printf("[mod] found module, begin: %x end: %x\n", modList->mod_start, modList->mod_end);
            *end = (uintptr_t)modList->mod_end;
            return (void*)modList->mod_start;
        }
        modList += i * sizeof(multiboot_module_t);
    }
    return NULL;
}