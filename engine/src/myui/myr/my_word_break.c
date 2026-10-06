/**
 * @file my_word_break.c
 * @brief Allocation-free byte-space word boundaries (R662).
 */
#include "myr/my_word_break.h"

#include <stdbool.h>

typedef enum wb_class_t {
  WB_WS = 0,
  WB_WORD,
  WB_PUNCT
} wb_class_t;

static size_t wb_cp_bytes(uint8_t lead) {
  if (lead < 0x80u) return 1u;
  if (lead < 0xC0u) return 1u;
  if (lead < 0xE0u) return 2u;
  if (lead < 0xF0u) return 3u;
  return 4u;
}

static bool wb_is_ascii_ws(uint8_t lead) {
  return lead == ' ' || lead == '\t' || lead == '\r' || lead == '\n';
}

static wb_class_t wb_class_of_lead(const char* text, size_t len, size_t pos) {
  uint8_t lead = (uint8_t)text[pos];
  (void)len;
  if (wb_is_ascii_ws(lead)) return WB_WS;
  if (lead >= 0x80u) return WB_WORD; /* every non-ASCII codepoint */
  if ((lead >= 'a' && lead <= 'z') || (lead >= 'A' && lead <= 'Z') ||
      (lead >= '0' && lead <= '9') || lead == '_') {
    return WB_WORD;
  }
  return WB_PUNCT;
}

static size_t wb_prev_start(const char* text, size_t offset) {
  size_t prev = offset - 1u;
  while (prev > 0u && ((uint8_t)text[prev] & 0xC0u) == 0x80u) {
    prev--;
  }
  return prev;
}

static size_t wb_next_start(const char* text, size_t len, size_t pos) {
  size_t next = pos + wb_cp_bytes((uint8_t)text[pos]);
  return next > len ? len : next;
}

size_t my_word_break_right(const char* text, size_t len, size_t offset) {
  wb_class_t cls;
  size_t i;
  if (text == NULL) return 0u;
  if (offset >= len) return len;
  i = offset;
  cls = wb_class_of_lead(text, len, i);
  if (cls != WB_WS) {
    while (i < len && wb_class_of_lead(text, len, i) == cls) {
      i = wb_next_start(text, len, i);
    }
  }
  while (i < len && wb_class_of_lead(text, len, i) == WB_WS) {
    i = wb_next_start(text, len, i);
  }
  return i;
}

size_t my_word_break_left(const char* text, size_t len, size_t offset) {
  wb_class_t cls;
  size_t i;
  if (text == NULL || offset == 0u) return 0u;
  if (offset > len) offset = len;
  i = offset;
  cls = wb_class_of_lead(text, len, wb_prev_start(text, i));
  if (cls == WB_WS) {
    while (i > 0u && wb_class_of_lead(text, len, wb_prev_start(text, i)) ==
                         WB_WS) {
      i = wb_prev_start(text, i);
    }
    if (i == 0u) return 0u;
    cls = wb_class_of_lead(text, len, wb_prev_start(text, i));
  }
  while (i > 0u &&
         wb_class_of_lead(text, len, wb_prev_start(text, i)) == cls) {
    i = wb_prev_start(text, i);
  }
  return i;
}
