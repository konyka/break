/**
 * @file my_str.c
 * @brief UTF-8 aware string utilities.
 */
#include "myc/my_str.h"

#include <string.h>

char* my_strdup(const my_allocator_t* allocator, const char* s) {
  size_t len;
  char* copy;
  if (s == NULL) {
    return NULL;
  }
  len = strlen(s) + 1;
  copy = (char*)my_mem_alloc(allocator, len);
  if (copy == NULL) {
    return NULL;
  }
  memcpy(copy, s, len);
  return copy;
}

char* my_strndup(const my_allocator_t* allocator, const char* s, size_t n) {
  size_t len;
  char* copy;
  if (s == NULL) {
    return NULL;
  }
  len = 0;
  while (len < n && s[len] != '\0') {
    len++;
  }
  copy = (char*)my_mem_alloc(allocator, len + 1);
  if (copy == NULL) {
    return NULL;
  }
  memcpy(copy, s, len);
  copy[len] = '\0';
  return copy;
}

size_t my_str_len(const char* s) {
  return s != NULL ? strlen(s) : 0;
}

bool my_str_eq(const char* a, const char* b) {
  if (a == NULL || b == NULL) {
    return a == b;
  }
  return strcmp(a, b) == 0;
}

bool my_str_start_with(const char* s, const char* prefix) {
  if (s == NULL || prefix == NULL) {
    return false;
  }
  while (*prefix != '\0') {
    if (*s++ != *prefix++) {
      return false;
    }
  }
  return true;
}

bool my_str_end_with(const char* s, const char* suffix) {
  size_t s_len, suffix_len;
  if (s == NULL || suffix == NULL) {
    return false;
  }
  s_len = strlen(s);
  suffix_len = strlen(suffix);
  if (suffix_len > s_len) {
    return false;
  }
  return strcmp(s + s_len - suffix_len, suffix) == 0;
}

size_t my_str_utf8_char_len(const char* s) {
  unsigned char c;
  if (s == NULL || *s == '\0') {
    return 0;
  }
  c = (unsigned char)*s;
  if (c < 0x80) {
    return 1;
  }
  if ((c & 0xE0) == 0xC0) {
    return 2;
  }
  if ((c & 0xF0) == 0xE0) {
    return 3;
  }
  if ((c & 0xF8) == 0xF0) {
    return 4;
  }
  return 1; /* invalid lead byte: skip one byte to stay progressing */
}

size_t my_str_utf8_strlen(const char* s) {
  size_t count = 0;
  size_t step;
  if (s == NULL) {
    return 0;
  }
  while (*s != '\0') {
    step = my_str_utf8_char_len(s);
    s += step;
    count++;
  }
  return count;
}
