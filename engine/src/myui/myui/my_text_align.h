/**
 * @file my_text_align.h
 * @brief Horizontal text alignment shared by label and text_area (M11d).
 *
 * Semantics under the M11a "x is always the left edge" draw_text rule:
 * alignment shifts the whole line's base x within the widget's inner
 * width (LEFT: line starts at the left edge; RIGHT: the line's right
 * edge touches the inner right edge; CENTER: centered). JUSTIFY
 * stretches word spacing (text_area wrap mode only; a single-line label
 * and a non-wrapping text_area treat it as LEFT, noted in the widget
 * docs). RTL paragraphs follow the same setting (the visual block is
 * shifted as a whole).
 */
#ifndef MY_TEXT_ALIGN_H
#define MY_TEXT_ALIGN_H

#include "myc/my_str.h"

typedef enum my_text_align_t {
  MY_TEXT_ALIGN_LEFT = 0,
  MY_TEXT_ALIGN_CENTER,
  MY_TEXT_ALIGN_RIGHT,
  MY_TEXT_ALIGN_JUSTIFY
} my_text_align_t;

/** @brief Parse "left|center|right|justify" (NULL/unknown -> LEFT). */
static inline my_text_align_t my_text_align_parse(const char* s) {
  if (s == NULL) {
    return MY_TEXT_ALIGN_LEFT;
  }
  if (my_str_eq(s, "center")) {
    return MY_TEXT_ALIGN_CENTER;
  }
  if (my_str_eq(s, "right")) {
    return MY_TEXT_ALIGN_RIGHT;
  }
  if (my_str_eq(s, "justify")) {
    return MY_TEXT_ALIGN_JUSTIFY;
  }
  return MY_TEXT_ALIGN_LEFT;
}

/** @brief Enum -> canonical string ("left" for unknown values). */
static inline const char* my_text_align_str(my_text_align_t a) {
  switch (a) {
    case MY_TEXT_ALIGN_CENTER:
      return "center";
    case MY_TEXT_ALIGN_RIGHT:
      return "right";
    case MY_TEXT_ALIGN_JUSTIFY:
      return "justify";
    default:
      return "left";
  }
}

#endif /* MY_TEXT_ALIGN_H */
