#include "solution.hpp"

unsigned int StrLen(const char* c_str) {
  unsigned int size = 0;
  while (*c_str++ != '\0') ++size;
  return size;
}

void Cstringcpy(const char* src, char* dest) {
  while (*src != '\0') {
    *(dest++) = *(src++);
  }
  *dest = '\0';
}

void StrCpy(char*& to, const char* from) {
  if (from == nullptr) return;
  char* copy = new char[StrLen(from) + 1];
  Cstringcpy(from, copy);
  delete[] to;
  to = copy;
}