/**
 * @file my_label.h
 * @brief Minimal label widget (colored background + text placeholder).
 */
#ifndef MY_LABEL_H
#define MY_LABEL_H

#include "myui/my_text_align.h"
#include "myui/my_widget.h"

/** @brief Label (IS-A widget). Non-interactive: enable=false by default. */
typedef struct my_label_t {
  my_widget_t base;
  char* text;      /**< owned copy */
  my_color_t bg;   /**< background color */
  my_color_t fg;   /**< text (placeholder bar) color */
  my_text_align_t align; /**< horizontal alignment (M11d, default LEFT) */
} my_label_t;

/** @brief Create a label (NULL allocator = default, NULL text allowed). */
my_widget_t* my_label_create(const my_allocator_t* allocator, const char* text);

/** @brief Replace the label text (owned copy). */
my_ret_t my_label_set_text(my_widget_t* label, const char* text);

/**
 * @brief Horizontal alignment (M11d). LEFT/CENTER/RIGHT shift the text
 * within the label width (labels were CENTER-ish before M11d; set
 * MY_TEXT_ALIGN_CENTER explicitly for that look). JUSTIFY behaves as
 * LEFT for a single-line label (no wrapping to stretch).
 */
my_ret_t my_label_set_align(my_widget_t* label, my_text_align_t align);

#endif /* MY_LABEL_H */
