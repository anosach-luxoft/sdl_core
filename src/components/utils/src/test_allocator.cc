#include "utils/macro.h"
#include <stdio.h>

void* operator new(std::size_t size, const char* file, unsigned int line) {
  void* x = operator new(size);
  printf("%s: %d Memory allocation of %ld bytes at %p\n", file, line, size, x);
  return x;
}

void* operator new[](std::size_t size, const char* file, unsigned int line) {
  void* x = operator new[](size);
  printf("%s: %d Memory allocation of %ld bytes at %p\n", file, line, size, x);
  return x;
}

void operator delete(void* ptr) {
  printf("Memory deallocation at %p\n", ptr);
  free(ptr);
}

void operator delete[](void* ptr) {
  printf("Memory deallocation at %p\n", ptr);
  free(ptr);
}
