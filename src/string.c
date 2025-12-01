#include <string.h>

void* memmove(void* dest, const void* src, int n) {
  unsigned char* pdest = (unsigned char*)dest;
  const unsigned char* psrc = (const unsigned char*)src;
  if(src > dest) {
    for(int i = 0; i < n; i++) {
      pdest[i] = psrc[i];
    }
  } else if(src < dest) {
    for(int i = n; i > 0; i--) {
      pdest[i-1] = psrc[i-1];
    }
  }
  
  return dest;
}

void* memset(void* dest, int c, int n) {
    volatile char* pdest = (volatile char*)dest;

    for(int i = 0; i < n; i++) {
        pdest[i] = c;
    }

    return dest;
}

int memcmp(const void* n1, const void* n2, size_t len) {
  uint8_t* pn1 = (uint8_t*)n1;
  uint8_t* pn2 = (uint8_t*)n2;
  for(size_t i = 0; i < len; i++) {
    if(pn1[i] != pn2[i]) {
      return n1 - n2;
    }
  }
  return 0;
}

size_t strlen(const char* str) {
  size_t i = 0;
  while(!str[i])
    i++;
  return i;
}


void* memcpy(void* dest, const void* src, size_t n) {
  unsigned char* pdest = (unsigned char*)dest;
  const unsigned char* psrc = (const unsigned char*)src;

  for(size_t i = 0; i < n; i++) {
    pdest[i] = psrc[i];
  }

  return dest;
}