#pragma once
#include <stdio.h>
#include <stdint.h>


typedef struct {
    char fileName[100];
    char fileMode[8];
    char ownerId[8];
    char groupId[8];
    char fileSize[12];
    char lastModificationTime[12];
    char checksum[8];
    char type;
    char linkedFileName[100];
    char signature[6];
    char version[2];
    char ownerUsername[32];
    char groupName[32];
    char deviceMajor[8];
    char deviceMinor[8];
    char filenamePrefix[155];
    char pad[12];
} __attribute__((packed)) USTARHeader;

typedef struct USTARFile{
    char filename[100];
    char prefix[155];
    int fileSize;
    char* contents;
    struct USTARFile* next;
} __attribute__((packed)) USTARFile;


// file system design
typedef struct {
    USTARFile* files;
} __attribute__((packed)) USTARFs;


#define TYPE_NORMAL '0'
#define TYPE_HARDLINK '1'
#define TYPE_SYMLINK '2'
#define TYPE_CHARDEV '3'
#define TYPE_BLKDEV '4'
#define TYPE_DIR '5'
#define TYPE_NAMEDPIPE '6'

int ustarGetFile(USTARHeader* archive, const char* fileName, int fileNameN,  uintptr_t* out);
USTARFs* createUstarFsFromArchive(USTARHeader* archive);
USTARFile* getFileFromUstarFs(USTARFs* fs, const char* filename);