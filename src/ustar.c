#include <ustar.h>
#include <string.h>
#include <pmm.h>

// OSDev Wiki: https://wiki.osdev.org/USTAR
int oct2bin(unsigned char *str, int size) {
    int n = 0;
    unsigned char *c = str;
    while (size-- > 0) {
        n *= 8;
        n += *c - '0';
        c++;
    }
    return n;
}

int ustarGetFile(USTARHeader* archive, const char* fileName, int fileNameN, uintptr_t* out) {
    if(!archive || !fileName || !out) return 0;
    while(!memcmp(archive->signature, "ustar", 5)) {
        size_t fsz = oct2bin(archive->fileSize, 11);
        if(!memcmp(archive->fileName, fileName, fileNameN)) {
            *out = (uintptr_t)((uintptr_t)archive + 512);
            printf("[ustar] found file: %s\n", archive->fileName);
            return fsz;
        }
        archive += (uintptr_t)(char*)(((fsz + 511) / 512) + 1) * 512;
    }
    return 0;
}


USTARFs* createUstarFsFromArchive(USTARHeader* archive) {
    if(!archive)
        return NULL;
    USTARFs* fs = pmmAllocPage();
    if(!fs)
        return NULL;
    memset(fs, 0, sizeof(USTARFs));
    while(!memcmp(archive->signature, "ustar", 5)) {
        USTARFile *file = pmmAllocPage();
        memset(file, 0, sizeof(USTARFile));
        memcpy(file->filename, archive->fileName, 100);
        memcpy(file->prefix, archive->filenamePrefix, 155);
        file->fileSize = oct2bin(archive->fileSize, 11);
        file->contents = (char *)(archive + sizeof(USTARHeader));
        if (!fs->files) {
            file->next = fs->files;
            fs->files = file;
        }
        file->next = fs->files->next;
        fs->files->next = file;
        printf("[ustar] created: %s\n", archive->fileName);
        archive += (uintptr_t)(char*)((((file ? file->fileSize : 512) + 511) / 512) + 1);
    }
    return fs;
}


USTARFile* getFileFromUstarFs(USTARFs* fs, const char* filename) {
    if(!fs || !filename)
        return NULL;
    USTARFile* n = fs->files;
    while(n) {
        if(!memcmp(n->filename, filename, strlen(filename))) { // no
            return n;
        } 
        n = n->next;
    }
    return NULL;
}