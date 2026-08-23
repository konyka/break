/**
 * @file my_text_paragraph.h
 * @brief Bounded paragraph wrapping over logical UTF-8 codepoint ranges.
 *
 * The model keeps source ranges in logical order. Each line can therefore be
 * shaped and visually reordered independently without losing cursor or
 * selection offsets. Shaping clusters are treated as indivisible boundaries.
 */
#ifndef MY_TEXT_PARAGRAPH_H
#define MY_TEXT_PARAGRAPH_H

#include "myc/my_mem.h"
#include "myr/my_font.h"

typedef struct my_text_paragraph_line_t {
  size_t start_byte;
  size_t end_byte;
  size_t start_cp;
  size_t cp_count;
} my_text_paragraph_line_t;

typedef struct my_text_paragraph_t {
  const my_allocator_t* allocator;
  char* text;
  my_text_paragraph_line_t* lines;
  size_t line_count;
  size_t logical_len;
} my_text_paragraph_t;

/** @brief Build a bounded paragraph; max_width <= 0 disables wrapping. */
my_text_paragraph_t* my_text_paragraph_process(const my_allocator_t* allocator,
                                               const char* text,
                                               my_font_t* font, int32_t size,
                                               int32_t max_width);

/** @brief Destroy a paragraph returned by my_text_paragraph_process. */
void my_text_paragraph_destroy(my_text_paragraph_t* paragraph);

/** @brief Read one logical line; NULL is returned for an invalid index. */
const my_text_paragraph_line_t* my_text_paragraph_line_at(
    const my_text_paragraph_t* paragraph, size_t index);

#endif /* MY_TEXT_PARAGRAPH_H */
