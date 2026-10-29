/**
 * @file my_str.c
 * @brief UTF-8 aware string utilities.
 */
#include "myc/my_str.h"

#include <locale.h>
#include <stdlib.h>
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
  const unsigned char* p;
  unsigned char c;
  unsigned char second;
  if (s == NULL || *s == '\0') {
    return 0;
  }
  p = (const unsigned char*)s;
  c = (unsigned char)*s;
  if (c < 0x80) {
    return 1;
  }
  if (c >= 0xC2u && c <= 0xDFu && p[1] != '\0' &&
      (p[1] & 0xC0u) == 0x80u) {
    return 2;
  }
  if (c >= 0xE0u && c <= 0xEFu && p[1] != '\0' && p[2] != '\0' &&
      (p[1] & 0xC0u) == 0x80u && (p[2] & 0xC0u) == 0x80u) {
    second = p[1];
    if (c == 0xE0u && second < 0xA0u) return 1;
    if (c == 0xEDu && second >= 0xA0u) return 1;
    return 3;
  }
  if (c >= 0xF0u && c <= 0xF4u && p[1] != '\0' && p[2] != '\0' &&
      p[3] != '\0' && (p[1] & 0xC0u) == 0x80u &&
      (p[2] & 0xC0u) == 0x80u && (p[3] & 0xC0u) == 0x80u) {
    second = p[1];
    if (c == 0xF0u && second < 0x90u) return 1;
    if (c == 0xF4u && second > 0x8Fu) return 1;
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

double my_strtod_c(const char* text, char** end) {
  char buf[256];
  size_t map[256];
  char* buf_end = NULL;
  const struct lconv* lc = localeconv();
  const char* point = (lc != NULL && lc->decimal_point != NULL &&
                       lc->decimal_point[0] != '\0')
                          ? lc->decimal_point
                          : ".";
  size_t point_len = strlen(point);
  size_t i = 0;
  size_t o = 0;
  double v;
  if (text == NULL) {
    if (end != NULL) *end = NULL;
    return 0.0;
  }
  if (point_len == 1 && point[0] == '.') return strtod(text, end);
  /* Leading whitespace is skipped by strtod; keep it in the copy. */
  while (text[i] == ' ' || text[i] == '\t' || text[i] == '\n' ||
         text[i] == '\r' || text[i] == '\f' || text[i] == '\v') {
    if (o + 1 >= sizeof(buf)) break;
    map[o] = i;
    buf[o++] = text[i++];
  }
  while (text[i] != '\0') {
    char ch = text[i];
    int numeric = (ch >= '0' && ch <= '9') || ch == '.' || ch == '+' ||
                  ch == '-' || (ch >= 'a' && ch <= 'z') ||
                  (ch >= 'A' && ch <= 'Z');
    size_t need = ch == '.' ? point_len : 1;
    if (!numeric || o + need >= sizeof(buf)) break;
    if (ch == '.') {
      size_t k;
      memcpy(buf + o, point, point_len);
      for (k = 0; k < point_len; k++) map[o + k] = i;
      o += point_len;
    } else {
      map[o] = i;
      buf[o++] = ch;
    }
    i++;
  }
  buf[o] = '\0';
  v = strtod(buf, &buf_end);
  if (end != NULL) {
    size_t used = (size_t)(buf_end - buf);
    /* used lands at the start of a (possibly multi-byte) point only when
     * strtod rejected it, so mapping the first byte is exact. */
    *end = (char*)text + (used < o ? map[used] : i);
  }
  return v;
}

float my_strtof_c(const char* text, char** end) {
  return (float)my_strtod_c(text, end);
}

void my_str_c_decimal(char* buf) {
  const struct lconv* lc = localeconv();
  const char* point;
  size_t point_len;
  char* hit;
  if (buf == NULL || lc == NULL || lc->decimal_point == NULL) return;
  point = lc->decimal_point;
  point_len = strlen(point);
  if (point_len == 0 || (point_len == 1 && point[0] == '.')) return;
  hit = strstr(buf, point);
  if (hit == NULL) return;
  *hit = '.';
  if (point_len > 1) memmove(hit + 1, hit + point_len, strlen(hit + point_len) + 1);
}
