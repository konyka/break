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
#include "myr/my_line_break.h"

typedef struct my_text_layout_t my_text_layout_t;

#define MY_TEXT_PARAGRAPH_MAX_BYTES (4u * 1024u * 1024u)
#define MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY 4u

typedef struct my_text_paragraph_line_t {
  size_t start_byte;
  size_t end_byte;
  size_t start_cp;
  size_t cp_count;
} my_text_paragraph_line_t;

typedef struct my_text_paragraph_line_layout_cache_entry_t {
  my_text_layout_t* layout;
  size_t line_index;
  uint64_t last_used;
} my_text_paragraph_line_layout_cache_entry_t;

typedef struct my_text_paragraph_t {
  const my_allocator_t* allocator;
  char* text;
  size_t text_len;
  my_text_paragraph_line_t* lines;
  size_t line_count;
  size_t logical_len;
  my_font_shape_params_t shape_params;
  char* shape_language;
  char* shape_features;
  my_text_paragraph_line_layout_cache_entry_t
      line_layout_cache[MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY];
  uint64_t line_layout_cache_tick;
} my_text_paragraph_t;

/** @brief Build a bounded paragraph; oversized text returns NULL, and
 * max_width <= 0 disables wrapping. */
my_text_paragraph_t* my_text_paragraph_process(const my_allocator_t* allocator,
                                               const char* text,
                                               my_font_t* font, int32_t size,
                                               int32_t max_width);

/** @brief Build a paragraph using explicit shaping parameters. */
my_text_paragraph_t* my_text_paragraph_process_ex(
    const my_allocator_t* allocator, const char* text, my_font_t* font,
    int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params);

/** @brief Build a bounded paragraph with an optional SA dictionary. */
my_text_paragraph_t* my_text_paragraph_process_break_ex(
    const my_allocator_t* allocator, const char* text, my_font_t* font,
    int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options);

/** @brief Build a paragraph with an explicit SA dictionary profile. */
my_text_paragraph_t* my_text_paragraph_process_break_profile_ex(
    const my_allocator_t* allocator, const char* text, my_font_t* font,
    int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options,
    const my_line_break_dictionary_profile_t* dictionary_profile);

/** @brief Build a paragraph from an exact NUL-free UTF-8 byte slice. */
my_text_paragraph_t* my_text_paragraph_process_n(
    const my_allocator_t* allocator, const char* text, size_t byte_len,
    my_font_t* font, int32_t size, int32_t max_width);

/** @brief Build a paragraph from an exact slice with shaping parameters. */
my_text_paragraph_t* my_text_paragraph_process_n_ex(
    const my_allocator_t* allocator, const char* text, size_t byte_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params);

/** @brief Build a paragraph with an optional bounded SA dictionary. */
my_text_paragraph_t* my_text_paragraph_process_n_break_ex(
    const my_allocator_t* allocator, const char* text, size_t byte_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options);

/** @brief Build an exact slice with an explicit SA dictionary profile. */
my_text_paragraph_t* my_text_paragraph_process_n_break_profile_ex(
    const my_allocator_t* allocator, const char* text, size_t byte_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options,
    const my_line_break_dictionary_profile_t* dictionary_profile);

/** @brief Build an exact slice with a profile-aware SA dictionary callback. */
my_text_paragraph_t* my_text_paragraph_process_n_break_profile_callback_ex(
    const my_allocator_t* allocator, const char* text, size_t byte_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_profile_options_t* profile_options,
    const my_line_break_dictionary_profile_t* dictionary_profile);

/** @brief Destroy a paragraph returned by my_text_paragraph_process. */
void my_text_paragraph_destroy(my_text_paragraph_t* paragraph);

/** @brief Read one logical line; NULL is returned for an invalid index. */
const my_text_paragraph_line_t* my_text_paragraph_line_at(
    const my_text_paragraph_t* paragraph, size_t index);

/** @brief Read shaping parameters owned by the paragraph. */
const my_font_shape_params_t* my_text_paragraph_shape_params(
    const my_text_paragraph_t* paragraph);

/** @brief Return a cached visual layout for one logical line.
 * The paragraph owns the returned layout until it is evicted or destroyed;
 * NULL means invalid index or OOM.
 */
const my_text_layout_t* my_text_paragraph_line_layout(
    const my_text_paragraph_t* paragraph, size_t index);

/** @brief Convert a paragraph logical boundary to a line visual boundary.
 * The logical boundary is global to the paragraph and is clamped to the
 * selected line. The returned boundary is local to that line layout.
 */
size_t my_text_paragraph_line_visual_of_logical(
    const my_text_paragraph_t* paragraph, size_t index,
    size_t logical_boundary);

/** @brief Convert a line visual boundary to a paragraph logical boundary. */
size_t my_text_paragraph_line_logical_at_visual(
    const my_text_paragraph_t* paragraph, size_t index,
    size_t visual_boundary);

#endif /* MY_TEXT_PARAGRAPH_H */
