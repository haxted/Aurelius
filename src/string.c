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