/**
 * @file my_text_area.c
 * @brief Multi-line text editing widget.
 */
#include "myui/widgets/my_text_area.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_str.h"
#include "myc/myconf/my_conf.h"
#include "myr/my_font.h"
#include "myr/my_text_paragraph.h"
#include "myr/my_text_layout.h"
#include "myui/my_undo_manager.h"
#include "myui/my_undo_stack.h"
#include "myui/my_window.h"
#include "myui/widgets/my_scroll_bar.h"

#define TA_PAD_X 4
#define TA_PAD_Y 3
#define TA_CELL_W 8 /* fallback cell width without a font */
#define TA_LINE_NUMBER_GAP 6
#define TA_SYNTAX_DEFAULT_LINE_BUDGET 32
#define TA_MAX_FOLD_STATE_BYTES (64u * 1024u)
#define TA_MAX_FOLD_RANGES 4096u
#define TA_FOLD_STATE_LEGACY_VERSION 0
#define TA_FOLD_STATE_VERSION 1
#define TA_FOLD_STATE_HEADER "version: 1\nfolds:\n"

static int32_t ta_sat_i64(int64_t value) {
  if (value > INT32_MAX) return INT32_MAX;
  if (value < INT32_MIN) return INT32_MIN;
  return (int32_t)value;
}

static int32_t ta_sat_size_mul(size_t value, int32_t factor) {
  if (factor <= 0 || value == 0) return 0;
  if (value > (size_t)INT32_MAX / (size_t)factor) return INT32_MAX;
  return (int32_t)(value * (size_t)factor);
}

static int32_t ta_sat_add(int32_t left, int32_t right) {
  return ta_sat_i64((int64_t)left + (int64_t)right);
}

static size_t ta_sat_size_add(size_t left, size_t right) {
  return right > SIZE_MAX - left ? SIZE_MAX : left + right;
}

static int32_t ta_sat_f32(float value) {
  if (!isfinite(value)) return 0;
  if (value >= (float)INT32_MAX) return INT32_MAX;
  if (value <= (float)INT32_MIN) return INT32_MIN;
  return (int32_t)value;
}

static int32_t ta_content_left_value(const my_text_area_t* ta);

static int32_t ta_inner_width_i32(const my_text_area_t* ta) {
  const my_widget_t* widget = (const my_widget_t*)ta;
  int64_t width = (int64_t)widget->rect.w - ta_content_left_value(ta) -
                  TA_PAD_X;
  return width > INT32_MAX ? INT32_MAX : width > 0 ? (int32_t)width : 0;
}

static int32_t ta_inner_height(const my_text_area_t* ta) {
  const my_widget_t* widget = (const my_widget_t*)ta;
  int64_t height = (int64_t)widget->rect.h - 2 * TA_PAD_Y;
  return height > INT32_MAX ? INT32_MAX : height > 0 ? (int32_t)height : 0;
}

typedef struct my_text_fold_range_t {
  size_t start_row;
  size_t end_row;
} my_text_fold_range_t;

/* ---------------- line offset cache ---------------- */

static size_t ta_line_count(const my_text_area_t* ta) {
  return my_darray_size(ta->line_offsets);
}

static size_t ta_line_content_end(const my_text_area_t* ta, size_t start,
                                  size_t end) {
  size_t pos = start;
  while (pos < end) {
    size_t break_len = my_line_break_hard_break_len(ta->text + pos, end - pos);
    if (break_len > 0u) return pos;
    pos += my_str_utf8_char_len(ta->text + pos);
  }
  return end;
}

static void ta_visible_rows_invalidate(my_text_area_t* ta) {
  ta->visible_rows_dirty = true;
}

static bool ta_row_hidden(const my_text_area_t* ta, size_t row) {
  size_t i;
  if (ta == NULL || ta->fold_ranges == NULL) {
    return false;
  }
  for (i = 0; i < my_darray_size(ta->fold_ranges); i++) {
    const my_text_fold_range_t* range =
        (const my_text_fold_range_t*)my_darray_get(ta->fold_ranges, i);
    if (range == NULL) {
      continue;
    }
    if (row < range->start_row) {
      break;
    }
    if (row <= range->end_row && row > range->start_row) {
      return true;
    }
  }
  return false;
}

static size_t ta_visible_row_count_uncached(const my_text_area_t* ta) {
  size_t row;
  size_t visible = 0;
  for (row = 0; row < ta_line_count(ta); row++) {
    if (!ta_row_hidden(ta, row)) visible++;
  }
  return visible;
}

static size_t ta_visible_row_at_uncached(const my_text_area_t* ta,
                                         size_t index) {
  size_t row;
  size_t visible = 0;
  size_t line_count = ta_line_count(ta);
  if (line_count == 0) return 0;
  for (row = 0; row < line_count; row++) {
    if (ta_row_hidden(ta, row)) continue;
    if (visible == index) return row;
    visible++;
  }
  return line_count - 1;
}

static size_t ta_visible_index_of_row_uncached(const my_text_area_t* ta,
                                               size_t row) {
  size_t current;
  size_t visible = 0;
  for (current = 0; current < row && current < ta_line_count(ta);
       current++) {
    if (!ta_row_hidden(ta, current)) visible++;
  }
  if (row >= ta_line_count(ta) || ta_row_hidden(ta, row)) return 0;
  return visible;
}

static my_ret_t ta_visible_rows_ensure(my_text_area_t* ta) {
  my_darray_t* rows;
  size_t row;
  size_t range_index = 0;
  size_t active_count = 0;
  size_t range_count;
  size_t* active_ends;
  if (ta->fold_ranges == NULL || my_darray_size(ta->fold_ranges) == 0) {
    return MY_RET_OK;
  }
  if (!ta->visible_rows_dirty && ta->visible_rows != NULL) {
    return MY_RET_OK;
  }
  rows = my_darray_create(ta->allocator, 0);
  if (rows == NULL) {
    return MY_RET_OOM;
  }
  range_count = my_darray_size(ta->fold_ranges);
  if (range_count > SIZE_MAX / sizeof(*active_ends)) {
    my_darray_destroy(rows);
    return MY_RET_OOM;
  }
  active_ends = (size_t*)my_mem_alloc(ta->allocator,
                                      range_count * sizeof(*active_ends));
  if (active_ends == NULL) {
    my_darray_destroy(rows);
    return MY_RET_OOM;
  }
  for (row = 0; row < ta_line_count(ta); row++) {
    while (active_count > 0 && active_ends[active_count - 1] < row) {
      active_count--;
    }
    while (range_index < my_darray_size(ta->fold_ranges)) {
      const my_text_fold_range_t* range =
          (const my_text_fold_range_t*)my_darray_get(ta->fold_ranges,
                                                     range_index);
      if (range == NULL || range->start_row >= row) break;
      if (range->end_row >= row) {
        active_ends[active_count++] = range->end_row;
      }
      range_index++;
    }
    if (active_count == 0 &&
        my_darray_push(rows, (void*)row) != MY_RET_OK) {
      my_mem_free(ta->allocator, active_ends);
      my_darray_destroy(rows);
      return MY_RET_OOM;
    }
  }
  my_mem_free(ta->allocator, active_ends);
  my_darray_destroy(ta->visible_rows);
  ta->visible_rows = rows;
  ta->visible_rows_dirty = false;
  return MY_RET_OK;
}

static size_t ta_visible_row_count(my_text_area_t* ta) {
  if (ta->fold_ranges == NULL || my_darray_size(ta->fold_ranges) == 0) {
    return ta_line_count(ta);
  }
  if (ta_visible_rows_ensure(ta) != MY_RET_OK || ta->visible_rows == NULL) {
    return ta_visible_row_count_uncached(ta);
  }
  return my_darray_size(ta->visible_rows);
}

static size_t ta_visible_row_at(my_text_area_t* ta, size_t index) {
  if (ta->fold_ranges == NULL || my_darray_size(ta->fold_ranges) == 0) {
    return index;
  }
  if (ta_visible_rows_ensure(ta) != MY_RET_OK || ta->visible_rows == NULL) {
    return ta_visible_row_at_uncached(ta, index);
  }
  return (size_t)my_darray_get(ta->visible_rows, index);
}

static size_t ta_visible_index_of_row(my_text_area_t* ta, size_t row) {
  size_t i;
  if (ta->fold_ranges == NULL || my_darray_size(ta->fold_ranges) == 0) {
    return row;
  }
  if (ta_visible_rows_ensure(ta) != MY_RET_OK || ta->visible_rows == NULL) {
    return ta_visible_index_of_row_uncached(ta, row);
  }
  for (i = 0; i < my_darray_size(ta->visible_rows); i++) {
    if ((size_t)my_darray_get(ta->visible_rows, i) == row) {
      return i;
    }
  }
  return 0;
}

static void ta_clear_folds(my_text_area_t* ta) {
  size_t i;
  if (ta->fold_ranges != NULL) {
    for (i = 0; i < my_darray_size(ta->fold_ranges); i++) {
      my_mem_free(ta->allocator, my_darray_get(ta->fold_ranges, i));
    }
    my_darray_destroy(ta->fold_ranges);
    ta->fold_ranges = NULL;
  }
  my_darray_destroy(ta->visible_rows);
  ta->visible_rows = NULL;
  ta->visible_rows_dirty = false;
}

static void ta_fold_ranges_destroy(const my_allocator_t* allocator,
                                   my_darray_t* ranges) {
  size_t i;
  if (ranges == NULL) return;
  for (i = 0; i < my_darray_size(ranges); i++) {
    my_mem_free(allocator, my_darray_get(ranges, i));
  }
  my_darray_destroy(ranges);
}

static bool ta_fold_ranges_can_add(const my_darray_t* ranges, size_t start,
                                   size_t end) {
  size_t i;
  for (i = 0; i < my_darray_size(ranges); i++) {
    const my_text_fold_range_t* range =
        (const my_text_fold_range_t*)my_darray_get(ranges, i);
    bool new_contains_old;
    bool old_contains_new;
    if (range == NULL || start > range->end_row || end < range->start_row) {
      continue;
    }
    new_contains_old = start < range->start_row && end >= range->end_row;
    old_contains_new = range->start_row < start && range->end_row >= end;
    if (!new_contains_old && !old_contains_new) return false;
  }
  return true;
}

static my_ret_t ta_fold_ranges_add_sorted(const my_allocator_t* allocator,
                                          my_darray_t* ranges, size_t start,
                                          size_t end) {
  my_text_fold_range_t* range;
  size_t insert_at = 0;
  size_t i;
  if (!ta_fold_ranges_can_add(ranges, start, end)) {
    return MY_RET_INVALID_PARAMS;
  }
  range = (my_text_fold_range_t*)my_mem_calloc(allocator, 1, sizeof(*range));
  if (range == NULL) return MY_RET_OOM;
  range->start_row = start;
  range->end_row = end;
  while (insert_at < my_darray_size(ranges)) {
    const my_text_fold_range_t* current =
        (const my_text_fold_range_t*)my_darray_get(ranges, insert_at);
    if (current == NULL || start < current->start_row) break;
    insert_at++;
  }
  if (my_darray_push(ranges, range) != MY_RET_OK) {
    my_mem_free(allocator, range);
    return MY_RET_OOM;
  }
  for (i = my_darray_size(ranges) - 1; i > insert_at; i--) {
    ranges->items[i] = ranges->items[i - 1];
  }
  ranges->items[insert_at] = range;
  return MY_RET_OK;
}

static size_t ta_decimal_digits(size_t value) {
  size_t digits = 1;
  while (value >= 10) {
    value /= 10;
    digits++;
  }
  return digits;
}

static int ta_justify_space_count(const char* text, size_t len) {
  const char* p = text;
  int count = 0;
  const char* end = text != NULL ? text + len : NULL;
  if (text == NULL) return 0;
  while (p < end && *p != '\0') {
    const char* next = p;
    uint32_t cp = my_utf8_next(&next);
    if (my_line_break_is_breaking_space(cp) && next < end) count++;
    p = next;
  }
  return count;
}

static int32_t ta_codepoint_advance(const my_text_area_t* ta, uint32_t cp) {
  my_glyph_t glyph = {0};
  if (my_font_is_variation_selector(cp)) return 0;
  if (ta->font != NULL && ta->font->vtable != NULL &&
      ta->font->vtable->get_glyph != NULL &&
      my_font_get_glyph(ta->font, cp, ta->font_size, &glyph) == MY_RET_OK &&
      glyph.advance > 0) {
    int32_t advance = glyph.advance;
    my_font_glyph_release(&glyph);
    return advance;
  }
  my_font_glyph_release(&glyph);
  return TA_CELL_W;
}

static size_t ta_line_start(const my_text_area_t* ta, size_t row);
static const my_visual_line_t* ta_vline_at(my_text_area_t* ta, size_t vi);
static my_text_layout_t* ta_layout_rtl(my_text_area_t* ta,
                                       const my_visual_line_t* vl);
static my_ret_t ta_draw_text(my_text_area_t* ta, my_vgcanvas_t* vg,
                             const char* text, float x, float y);

static bool ta_geometry_reserve(my_text_area_t* ta, size_t required) {
  size_t capacity;
  int32_t* grown;
  if (required == SIZE_MAX) return false;
  if (required <= ta->geometry_capacity) return true;
  capacity = ta->geometry_capacity == 0 ? 16 : ta->geometry_capacity;
  while (capacity < required) {
    if (capacity > SIZE_MAX / 2) {
      capacity = required;
      break;
    }
    capacity *= 2;
  }
  if (capacity > SIZE_MAX / sizeof(*grown)) return false;
  grown = (int32_t*)my_mem_realloc(ta->allocator, ta->geometry_boundaries,
                                   capacity * sizeof(*grown));
  if (grown == NULL) return false;
  ta->geometry_boundaries = grown;
  ta->geometry_capacity = capacity;
  return true;
}

static bool ta_geometry_from_shaping(my_text_area_t* ta, size_t row,
                                     size_t count) {
  size_t start = ta_line_start(ta, row);
  size_t end = row + 1 < ta_line_count(ta) ? ta_line_start(ta, row + 1)
                                           : ta->text_len;
  size_t line_end = start;
  size_t len;
  my_text_layout_t* layout;
  size_t i;
  while (line_end < end && ta->text[line_end] != '\0' &&
         my_line_break_hard_break_len(ta->text + line_end, end - line_end) == 0u) {
    line_end += my_str_utf8_char_len(ta->text + line_end);
  }
  if (line_end < start) return false;
  len = line_end - start;
  if (len == SIZE_MAX) return false;
  layout = my_text_layout_process_n(ta->allocator, ta->text + start, len);
  if (layout == NULL) return false;
  for (i = 0; i <= count; i++) {
    ta->geometry_boundaries[i] =
        my_text_layout_visual_x_ex(layout, ta->font, ta->font_size, i,
                                   &ta->shaping_params);
  }
  my_text_layout_destroy(layout);
  return true;
}

static bool ta_geometry_ensure(my_text_area_t* ta, size_t row) {
  size_t start, end, line_start, line_bytes, count = 0, cp_count;
  const char* p;
  if (row >= ta_line_count(ta)) return false;
  if (ta->geometry_row == row && ta->geometry_revision == ta->text_revision &&
      ta->geometry_shaping_revision == ta->shaping_revision &&
      ta->geometry_font == ta->font &&
      ta->geometry_font_size == ta->font_size) {
    return true;
  }
  start = ta_line_start(ta, row);
  line_start = start;
  end = row + 1 < ta_line_count(ta) ? ta_line_start(ta, row + 1)
                                   : ta->text_len;
  p = ta->text + start;
  while (start < end && *p != '\0' &&
         my_line_break_hard_break_len(p, end - start) == 0u) {
    p += my_str_utf8_char_len(p);
    start = (size_t)(p - ta->text);
    count++;
  }
  line_bytes = start - line_start;
  if (count == SIZE_MAX || !ta_geometry_reserve(ta, count + 1)) return false;
  cp_count = count;
  if (ta->font != NULL && ta->font->vtable != NULL &&
      (ta->font->vtable->shape != NULL ||
       ta->font->vtable->shape_ex != NULL) &&
      ta_geometry_from_shaping(ta, row, cp_count)) {
    ta->geometry_row = row;
    ta->geometry_count = cp_count;
    ta->geometry_revision = ta->text_revision;
    ta->geometry_shaping_revision = ta->shaping_revision;
    ta->geometry_font = ta->font;
    ta->geometry_font_size = ta->font_size;
    return true;
  }
  if (ta->font != NULL && ta->font->vtable != NULL &&
      ta->font->vtable->shape == NULL &&
      my_text_layout_may_need_bidi_n(ta->text + line_start, line_bytes)) {
    const my_visual_line_t* vl = ta_vline_at(ta, row);
    my_text_layout_t* layout = vl != NULL ? ta_layout_rtl(ta, vl) : NULL;
    if (layout != NULL && layout->logical_len == cp_count) {
      size_t i;
      for (i = 0; i <= cp_count; i++) {
        ta->geometry_boundaries[i] = my_text_layout_visual_x_ex(
            layout, ta->font, ta->font_size, i, &ta->shaping_params);
      }
      ta->geometry_row = row;
      ta->geometry_count = cp_count;
      ta->geometry_revision = ta->text_revision;
      ta->geometry_shaping_revision = ta->shaping_revision;
      ta->geometry_font = ta->font;
      ta->geometry_font_size = ta->font_size;
      return true;
    }
  }
  start = ta_line_start(ta, row);
  p = ta->text + start;
  ta->geometry_boundaries[0] = 0;
  while (count > 0) {
    const char* next = p;
    uint32_t cp = my_utf8_next(&next);
    size_t index = cp_count - count;
    ta->geometry_boundaries[index + 1] = ta_sat_add(
        ta->geometry_boundaries[index], ta_codepoint_advance(ta, cp));
    p = next;
    count--;
  }
  ta->geometry_row = row;
  ta->geometry_count = cp_count;
  ta->geometry_revision = ta->text_revision;
  ta->geometry_shaping_revision = ta->shaping_revision;
  ta->geometry_font = ta->font;
  ta->geometry_font_size = ta->font_size;
  return true;
}

static size_t ta_line_start(const my_text_area_t* ta, size_t row);

static int32_t ta_line_boundary_x(my_text_area_t* ta, size_t row,
                                  size_t boundary) {
  if (ta_geometry_ensure(ta, row) && boundary <= ta->geometry_count) {
    return ta->geometry_boundaries[boundary];
  }
  size_t start = ta_line_start(ta, row);
  size_t end = row + 1 < ta_line_count(ta) ? ta_line_start(ta, row + 1)
                                           : ta->text_len;
  size_t index = 0;
  int32_t x = 0;
  const char* p = ta->text + start;
  while (start < end && *p != '\0' && index < boundary &&
         my_line_break_hard_break_len(p, end - start) == 0u) {
    const char* next = p;
    uint32_t cp = my_utf8_next(&next);
    x = ta_sat_add(x, ta_codepoint_advance(ta, cp));
    start += (size_t)(next - p);
    p = next;
    index++;
  }
  return x;
}

static size_t ta_line_col_at_x(my_text_area_t* ta, size_t row,
                               int32_t x) {
  if (x <= 0) return 0;
  if (ta_geometry_ensure(ta, row)) {
    size_t lo = 0, hi = ta->geometry_count;
    while (lo < hi) {
      size_t mid = lo + (hi - lo) / 2;
      int32_t advance = ta->geometry_boundaries[mid + 1] -
                        ta->geometry_boundaries[mid];
      if (x < ta->geometry_boundaries[mid] + (advance + 1) / 2) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    return lo;
  }
  size_t start = ta_line_start(ta, row);
  size_t end = row + 1 < ta_line_count(ta) ? ta_line_start(ta, row + 1)
                                           : ta->text_len;
  size_t col = 0;
  int32_t boundary = 0;
  const char* p = ta->text + start;
  while (start < end && *p != '\0' &&
         my_line_break_hard_break_len(p, end - start) == 0u) {
    const char* next = p;
    uint32_t cp = my_utf8_next(&next);
    int32_t advance = ta_codepoint_advance(ta, cp);
    if (x < boundary + (advance + 1) / 2) return col;
    boundary += advance;
    start += (size_t)(next - p);
    p = next;
    col++;
  }
  return col;
}

static int32_t ta_justify_boundary_x(const my_text_area_t* ta, const char* text,
                                     size_t boundary, size_t space_count,
                                     int32_t line_width, int32_t inner_width) {
  const char* p = text;
  size_t cp_index = 0;
  float x = 0.0f;
  float extra = space_count > 0 && inner_width > line_width
                    ? (float)(inner_width - line_width) / (float)space_count
                    : 0.0f;
  while (*p != '\0' && cp_index < boundary) {
    uint32_t cp = my_utf8_next(&p);
    x += (float)ta_codepoint_advance(ta, cp);
    if (my_line_break_is_breaking_space(cp)) x += extra;
    cp_index++;
  }
  return (int32_t)x;
}

static bool ta_layout_justify_space(const my_text_layout_t* layout,
                                    size_t visual_index) {
  size_t logical;
  size_t span;
  if (layout == NULL || visual_index >= layout->len ||
      !my_line_break_is_breaking_space(layout->visual_cps[visual_index])) {
    return false;
  }
  logical = layout->visual_to_logical[visual_index];
  span = layout->visual_logical_span[visual_index];
  if (span > SIZE_MAX - logical) {
    return false;
  }
  return logical + span < layout->logical_len;
}

static size_t ta_layout_justify_space_count(const my_text_layout_t* layout) {
  size_t i;
  size_t count = 0;
  if (layout == NULL) return 0;
  for (i = 0; i < layout->len; i++) {
    if (ta_layout_justify_space(layout, i)) count++;
  }
  return count;
}

static size_t ta_layout_justify_spaces_before(const my_text_layout_t* layout,
                                              size_t visual_boundary) {
  size_t i;
  size_t count = 0;
  if (layout == NULL || visual_boundary > layout->len) return 0;
  for (i = 0; i < visual_boundary; i++) {
    if (ta_layout_justify_space(layout, i)) count++;
  }
  return count;
}

static int32_t ta_layout_justify_boundary_x(
    const my_text_area_t* ta, const my_text_layout_t* layout,
    size_t logical_boundary, size_t space_count, int32_t line_width,
    int32_t inner_width) {
  size_t visual_boundary;
  size_t spaces_before;
  float extra;
  float x;
  if (layout == NULL || space_count == 0u || inner_width <= line_width) {
    return my_text_layout_visual_x_ex(layout, ta->font, ta->font_size,
                                      logical_boundary, &ta->shaping_params);
  }
  visual_boundary = my_text_layout_visual_of_logical(layout, logical_boundary);
  spaces_before = ta_layout_justify_spaces_before(layout, visual_boundary);
  extra = (float)(inner_width - line_width) / (float)space_count;
  x = (float)my_text_layout_visual_boundary_x_ex(
      layout, ta->font, ta->font_size, visual_boundary, &ta->shaping_params);
  x += extra * (float)spaces_before;
  if (x >= (float)INT32_MAX) return INT32_MAX;
  return ta_sat_f32(x + 0.5f);
}

static size_t ta_layout_justify_rects(
    const my_text_area_t* ta, const my_text_layout_t* layout, size_t l0,
    size_t l1, my_rectf_t* rects, size_t cap, size_t space_count,
    int32_t line_width, int32_t inner_width) {
  size_t count;
  size_t boundary;
  size_t rect_index = 0u;
  size_t spaces_before = 0u;
  size_t start_spaces = 0u;
  bool start_found = false;
  float extra;
  if (layout == NULL || rects == NULL || cap == 0u) return 0u;
  count = my_text_layout_visual_rects_ex(
      layout, ta->font, ta->font_size, l0, l1, rects, cap,
      &ta->shaping_params);
  if (space_count == 0u || inner_width <= line_width) return count;
  extra = (float)(inner_width - line_width) / (float)space_count;
  if (count > cap) count = cap;
  for (boundary = 0u; boundary <= layout->len && rect_index < count;
       boundary++) {
    int32_t x = my_text_layout_visual_boundary_x_ex(
        layout, ta->font, ta->font_size, boundary, &ta->shaping_params);
    while (rect_index < count) {
      int32_t start_x = ta_sat_f32(rects[rect_index].x + 0.5f);
      int32_t end_x = ta_sat_f32(rects[rect_index].x + rects[rect_index].w +
                                 0.5f);
      if (!start_found) {
        if (x != start_x) break;
        start_found = true;
        start_spaces = spaces_before;
      }
      if (x != end_x) break;
      rects[rect_index].x += extra * (float)start_spaces;
      rects[rect_index].w += extra * (float)(spaces_before - start_spaces);
      rect_index++;
      start_found = false;
    }
    if (boundary < layout->len && ta_layout_justify_space(layout, boundary)) {
      spaces_before++;
    }
  }
  return count;
}

static void ta_draw_justify_layout(
    my_text_area_t* ta, my_vgcanvas_t* vg, my_text_layout_t* layout,
    float base_x, float y, size_t space_count, int32_t line_width,
    int32_t inner_width) {
  size_t i;
  size_t word_start = 0u;
  size_t word_start_byte = 0u;
  size_t visual_offset = 0u;
  float x = base_x;
  float extra = space_count > 0u && inner_width > line_width
                    ? (float)(inner_width - line_width) /
                          (float)space_count
                    : 0.0f;

  if (layout == NULL || layout->visual_utf8 == NULL) return;
  for (i = 0u; i <= layout->len; i++) {
    bool separator = i < layout->len && ta_layout_justify_space(layout, i);
    size_t current_byte = visual_offset;
    if (separator || i == layout->len) {
      if (current_byte > word_start_byte) {
        char saved = layout->visual_utf8[current_byte];
        layout->visual_utf8[current_byte] = '\0';
        ta_draw_text(ta, vg, layout->visual_utf8 + word_start_byte, x, y);
        layout->visual_utf8[current_byte] = saved;
        x += (float)(my_text_layout_visual_boundary_x_ex(
                         layout, ta->font, ta->font_size, i,
                         &ta->shaping_params) -
                     my_text_layout_visual_boundary_x_ex(
                         layout, ta->font, ta->font_size, word_start,
                         &ta->shaping_params));
      }
      if (separator) {
        x += (float)(my_text_layout_visual_boundary_x_ex(
                         layout, ta->font, ta->font_size, i + 1u,
                         &ta->shaping_params) -
                     my_text_layout_visual_boundary_x_ex(
                         layout, ta->font, ta->font_size, i,
                         &ta->shaping_params));
        x += extra;
        word_start = i + 1u;
        word_start_byte = current_byte;
        {
          const char* next = layout->visual_utf8 + current_byte;
          (void)my_utf8_next(&next);
          word_start_byte = (size_t)(next - layout->visual_utf8);
          visual_offset = word_start_byte;
        }
      }
    }
    if (i < layout->len && !separator) {
      const char* next = layout->visual_utf8 + visual_offset;
      (void)my_utf8_next(&next);
      visual_offset = (size_t)(next - layout->visual_utf8);
    }
  }
}

static int32_t ta_content_left_value(const my_text_area_t* ta) {
  size_t digits;
  size_t width;
  if (ta == NULL || !ta->line_numbers) {
    return TA_PAD_X;
  }
  digits = ta_decimal_digits(ta_line_count(ta));
  if (digits > (SIZE_MAX - TA_PAD_X - TA_LINE_NUMBER_GAP) / TA_CELL_W) {
    return INT32_MAX;
  }
  width = TA_PAD_X + digits * TA_CELL_W + TA_LINE_NUMBER_GAP;
  return width > (size_t)INT32_MAX ? INT32_MAX : (int32_t)width;
}

static size_t ta_line_start(const my_text_area_t* ta, size_t row) {
  return (size_t)my_darray_get(ta->line_offsets, row);
}

static void ta_offsets_push(my_text_area_t* ta, size_t offset) {
  my_darray_push(ta->line_offsets, (void*)offset);
}

/** @brief Rebuild line offsets from `row` to the end of the buffer. */
static my_ret_t ta_vlines_rebuild_from(my_text_area_t* ta, size_t from);
static void ta_vlines_invalidate_from(my_text_area_t* ta, size_t from);

static void ta_rebuild_from(my_text_area_t* ta, size_t row) {
  if (ta->wrap) {
    ta_vlines_invalidate_from(ta, row);
  }
  ta_visible_rows_invalidate(ta);
  size_t pos, line;
  if (row == 0) {
    my_darray_clear(ta->line_offsets);
    ta_offsets_push(ta, 0);
    row = 0;
  }
  line = row;
  pos = ta_line_start(ta, line);
  /* drop stale entries beyond row */
  while (ta_line_count(ta) > row + 1) {
    my_darray_remove_at(ta->line_offsets, ta_line_count(ta) - 1);
  }
  while (pos < ta->text_len) {
    size_t break_len = my_line_break_hard_break_len(
        ta->text + pos, ta->text_len - pos);
    if (break_len > 0u) {
      ta_offsets_push(ta, pos + break_len);
      line++;
      pos += break_len;
      continue;
    }
    pos += my_str_utf8_char_len(ta->text + pos);
  }
  if (ta->wrap) {
    ta_vlines_invalidate_from(ta, row);
  }
}

static size_t ta_offset_of(const my_text_area_t* ta, size_t row, size_t col) {
  size_t start, end, off, c = 0;
  if (row >= ta_line_count(ta)) {
    return ta->text_len;
  }
  start = ta_line_start(ta, row);
  end = row + 1 < ta_line_count(ta) ? ta_line_start(ta, row + 1)
                                    : ta->text_len;
  end = ta_line_content_end(ta, start, end);
  off = start;
  while (off < end && c < col &&
         my_line_break_hard_break_len(ta->text + off, end - off) == 0u) {
    off += my_str_utf8_char_len(ta->text + off);
    c++;
  }
  return off;
}

static void ta_pos_of(const my_text_area_t* ta, size_t offset, size_t* row,
                      size_t* col) {
  size_t r = 0, start, c = 0, off;
  /* binary search the line */
  size_t lo = 0, hi = ta_line_count(ta);
  while (lo + 1 < hi) {
    size_t mid = (lo + hi) / 2;
    if (ta_line_start(ta, mid) <= offset) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  r = lo;
  start = ta_line_start(ta, r);
  off = start;
  while (off < offset && my_line_break_hard_break_len(ta->text + off,
                                           offset - off) == 0u) {
    off += my_str_utf8_char_len(ta->text + off);
    c++;
  }
  if (row != NULL) *row = r;
  if (col != NULL) *col = c;
}

static size_t ta_line_cp_len(const my_text_area_t* ta, size_t row) {
  size_t start, end, len = 0;
  if (row >= ta_line_count(ta)) {
    return 0;
  }
  start = ta_line_start(ta, row);
  end = row + 1 < ta_line_count(ta) ? ta_line_start(ta, row + 1)
                                    : ta->text_len;
  end = ta_line_content_end(ta, start, end);
  while (start < end) {
    start += my_str_utf8_char_len(ta->text + start);
    len++;
  }
  return len;
}

/* ---------------- visual lines (paragraph model) ----------------
 * Physical lines map to logical ranges from the shared paragraph wrapper.
 * Widths are precomputed once and shaping clusters remain indivisible.
 */

static float ta_inner_width(const my_text_area_t* ta) {
  float w = (float)((my_widget_t*)ta)->rect.w -
            (float)ta_content_left_value(ta) - (float)TA_PAD_X;
  return w > 1.0f ? w : 1.0f;
}

static my_ret_t ta_vline_push(my_text_area_t* ta, size_t phys,
                              size_t start_byte, size_t end_byte,
                              size_t start, size_t len) {
  my_visual_line_t* v =
      (my_visual_line_t*)my_mem_calloc(ta->allocator, 1,
                                       sizeof(my_visual_line_t));
  if (v == NULL) {
    return MY_RET_OOM;
  }
  v->phys = phys;
  v->start_byte = start_byte;
  v->len_bytes = end_byte - start_byte;
  v->start_cp = start;
  v->len_cp = len;
  if (my_darray_push(ta->vlines, v) != MY_RET_OK) {
    my_mem_free(ta->allocator, v);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

static void ta_vlines_destroy_array(my_text_area_t* ta, my_darray_t* lines) {
  size_t i;
  if (lines == NULL) return;
  for (i = 0; i < my_darray_size(lines); i++) {
    my_mem_free(ta->allocator, my_darray_get(lines, i));
  }
  my_darray_destroy(lines);
}

static void ta_vlines_destroy_range(my_text_area_t* ta, my_darray_t* lines,
                                    size_t from) {
  size_t i;
  if (lines == NULL) {
    return;
  }
  for (i = from; i < my_darray_size(lines); i++) {
    my_mem_free(ta->allocator, my_darray_get(lines, i));
  }
}

static void ta_vlines_destroy_range_to(my_text_area_t* ta,
                                       my_darray_t* lines, size_t from,
                                       size_t to) {
  size_t i;
  if (lines == NULL) return;
  if (from > my_darray_size(lines)) from = my_darray_size(lines);
  if (to > my_darray_size(lines)) to = my_darray_size(lines);
  if (to < from) to = from;
  for (i = from; i < to; i++) {
    my_mem_free(ta->allocator, my_darray_get(lines, i));
  }
}

static my_ret_t ta_vlines_append_paragraph(
    my_text_area_t* ta, my_text_paragraph_t* paragraph, size_t from,
    size_t suffix_start) {
  size_t i;
  size_t physical_row = from;
  size_t physical_count = ta_line_count(ta);
  size_t physical_cp_base = 0u;
  if (suffix_start > ta->text_len) return MY_RET_INVALID_PARAMS;
  for (i = 0u; i < paragraph->line_count; i++) {
    const my_text_paragraph_line_t* line =
        my_text_paragraph_line_at(paragraph, i);
    size_t global_start;
    size_t global_end;
    size_t phys;
    size_t physical_start;
    size_t physical_end;
    size_t start_cp;
    if (line == NULL || line->start_byte > paragraph->text_len ||
        line->end_byte < line->start_byte ||
        line->end_byte > paragraph->text_len ||
        line->end_byte > ta->text_len - suffix_start) {
      return MY_RET_FAIL;
    }
    global_start = suffix_start + line->start_byte;
    global_end = suffix_start + line->end_byte;
    while (physical_row + 1u < physical_count &&
           ta_line_start(ta, physical_row + 1u) <= global_start) {
      size_t row_cp_count = ta_line_cp_len(ta, physical_row);
      if (physical_cp_base > SIZE_MAX - row_cp_count) {
        return MY_RET_FAIL;
      }
      physical_cp_base += row_cp_count;
      physical_row++;
    }
    phys = physical_row;
    if (phys < from || phys >= physical_count) return MY_RET_FAIL;
    physical_start = ta_line_start(ta, phys);
    physical_end = phys + 1u < physical_count
                       ? ta_line_start(ta, phys + 1u)
                       : ta->text_len;
    if (global_end < physical_start || global_end > physical_end ||
        ta_line_content_end(ta, physical_start, physical_end) < global_end) {
      return MY_RET_FAIL;
    }
    if (line->start_cp < physical_cp_base) return MY_RET_FAIL;
    start_cp = line->start_cp - physical_cp_base;
    if (ta_vline_push(ta, phys, global_start - physical_start,
                      global_end - physical_start, start_cp,
                      line->cp_count) != MY_RET_OK) {
      return MY_RET_OOM;
    }
  }
  return MY_RET_OK;
}

/** @brief Rebuild visual lines transactionally for physical rows [from, end). */
static my_ret_t ta_vlines_rebuild_from(my_text_area_t* ta, size_t from) {
  my_darray_t* old_lines = ta->vlines;
  my_darray_t* new_lines;
  size_t pi, n, old_count, prefix_count = 0;
  size_t old_suffix_start = 0u;
  size_t old_physical_count = 0u;
  size_t candidate_end = 0u;
  bool reuse_suffix = ta->vlines_reuse_suffix &&
                      ta->vlines_reuse_old_line_index <=
                          my_darray_size(old_lines) &&
                      ta->vlines_reuse_new_phys >= from &&
                      ta->vlines_reuse_new_phys <= ta_line_count(ta) &&
                      my_darray_size(ta->fold_ranges) == 0u;
  if (from > ta_line_count(ta)) {
    from = ta_line_count(ta);
  }
  n = ta_line_count(ta);
  new_lines = my_darray_create(ta->allocator, 0);
  if (new_lines == NULL) return MY_RET_OOM;
  old_count = my_darray_size(old_lines);
  if (old_count > 0u) {
    const my_visual_line_t* last_line =
        (const my_visual_line_t*)my_darray_get(old_lines, old_count - 1u);
    if (last_line != NULL) old_physical_count = last_line->phys + 1u;
  }
  if (reuse_suffix &&
      (ta->vlines_reuse_old_line_index >= old_count ||
       old_physical_count <= ta->vlines_reuse_old_phys)) {
    reuse_suffix = false;
  }
  while (prefix_count < old_count) {
    const my_visual_line_t* line =
        (const my_visual_line_t*)my_darray_get(old_lines, prefix_count);
    if (line == NULL || line->phys >= from) {
      break;
    }
    if (my_darray_push(new_lines, (void*)line) != MY_RET_OK) {
      my_darray_destroy(new_lines);
      return MY_RET_OOM;
    }
    prefix_count++;
  }
  ta->vlines = new_lines;
  if (reuse_suffix) {
    for (pi = from; pi < ta->vlines_reuse_new_phys; ++pi) {
      size_t start_off;
      size_t end_off;
      size_t segment_end;
      size_t segment_len;
      my_text_paragraph_t* paragraph;
      size_t i;
      if (ta_row_hidden(ta, pi)) continue;
      start_off = ta_line_start(ta, pi);
      end_off = pi + 1u < n ? ta_line_start(ta, pi + 1u) : ta->text_len;
      segment_end = ta_line_content_end(ta, start_off, end_off);
      segment_len = segment_end > start_off ? segment_end - start_off : 0u;
      paragraph = my_text_paragraph_process_n_ex(
          ta->allocator, ta->text + start_off, segment_len, ta->font,
          ta->font_size, (int32_t)ta_inner_width(ta), &ta->shaping_params);
      if (paragraph == NULL) {
        ta->vlines = old_lines;
        ta_vlines_destroy_range(ta, new_lines, prefix_count);
        my_darray_destroy(new_lines);
        return MY_RET_OOM;
      }
      for (i = 0u; i < paragraph->line_count; ++i) {
        const my_text_paragraph_line_t* line =
            my_text_paragraph_line_at(paragraph, i);
        if (line != NULL &&
            ta_vline_push(ta, pi, line->start_byte, line->end_byte,
                          line->start_cp, line->cp_count) != MY_RET_OK) {
          my_text_paragraph_destroy(paragraph);
          ta->vlines = old_lines;
          ta_vlines_destroy_range(ta, new_lines, prefix_count);
          my_darray_destroy(new_lines);
          return MY_RET_OOM;
        }
      }
      my_text_paragraph_destroy(paragraph);
    }
    old_suffix_start = ta->vlines_reuse_old_line_index;
    candidate_end = my_darray_size(new_lines);
    {
      size_t i;
      for (i = old_suffix_start; i < old_count; ++i) {
        const my_visual_line_t* line =
            (const my_visual_line_t*)my_darray_get(old_lines, i);
        if (line == NULL || my_darray_push(new_lines, (void*)line) != MY_RET_OK) {
          new_lines->size = candidate_end;
          ta_vlines_destroy_range_to(ta, new_lines, prefix_count,
                                     candidate_end);
          my_darray_destroy(new_lines);
          ta->vlines = old_lines;
          return MY_RET_OOM;
        }
      }
      for (i = candidate_end; i < my_darray_size(new_lines); ++i) {
        my_visual_line_t* line =
            (my_visual_line_t*)my_darray_get(new_lines, i);
        line->phys = ta->vlines_reuse_new_phys +
                     (line->phys - ta->vlines_reuse_old_phys);
      }
    }
  } else if (my_darray_size(ta->fold_ranges) == 0u &&
      old_physical_count == ta_line_count(ta) && from < ta_line_count(ta)) {
    size_t i = prefix_count;
    while (i < old_count) {
      const my_visual_line_t* line =
          (const my_visual_line_t*)my_darray_get(old_lines, i);
      if (line == NULL || line->phys > from) break;
      i++;
    }
    old_suffix_start = i;
  }
  if (!reuse_suffix && my_darray_size(ta->fold_ranges) == 0u &&
      old_physical_count == n && from < n) {
    my_text_paragraph_t* paragraph;
    size_t suffix_start = ta_line_start(ta, from);
    size_t suffix_end = from + 1u < n ? ta_line_start(ta, from + 1u)
                                      : ta->text_len;
    size_t segment_end = ta_line_content_end(ta, suffix_start, suffix_end);
    size_t suffix_len = segment_end - suffix_start;
    paragraph = my_text_paragraph_process_n_ex(
        ta->allocator, ta->text + suffix_start, suffix_len, ta->font,
        ta->font_size, (int32_t)ta_inner_width(ta), &ta->shaping_params);
    if (paragraph == NULL) {
      ta->vlines = old_lines;
      ta_vlines_destroy_range(ta, new_lines, prefix_count);
      my_darray_destroy(new_lines);
      return MY_RET_OOM;
    }
    {
      my_ret_t append_ret =
          ta_vlines_append_paragraph(ta, paragraph, from, suffix_start);
      if (append_ret != MY_RET_OK) {
        my_text_paragraph_destroy(paragraph);
        ta->vlines = old_lines;
        ta_vlines_destroy_range(ta, new_lines, prefix_count);
        my_darray_destroy(new_lines);
        return append_ret;
      }
    }
    my_text_paragraph_destroy(paragraph);
    candidate_end = my_darray_size(new_lines);
    if (old_suffix_start < old_count) {
      size_t i;
      for (i = old_suffix_start; i < old_count; i++) {
        const my_visual_line_t* line =
            (const my_visual_line_t*)my_darray_get(old_lines, i);
        if (line == NULL || line->phys <= from ||
            my_darray_push(new_lines, (void*)line) != MY_RET_OK) {
          ta->vlines = old_lines;
          ta_vlines_destroy_range_to(ta, new_lines, prefix_count,
                                     candidate_end);
          my_darray_destroy(new_lines);
          return MY_RET_OOM;
        }
      }
    }
  } else if (!reuse_suffix) for (pi = from; pi < n; pi++) {
    if (ta_row_hidden(ta, pi)) {
      continue;
    }
    size_t start_off = ta_line_start(ta, pi);
    size_t end_off = pi + 1 < n ? ta_line_start(ta, pi + 1) : ta->text_len;
    size_t segment_end = end_off;
    size_t segment_len;
    my_text_paragraph_t* paragraph;
    size_t i;
    if (segment_end > start_off)
      segment_end = ta_line_content_end(ta, start_off, segment_end);
    segment_len = segment_end > start_off ? segment_end - start_off : 0;
    paragraph = my_text_paragraph_process_n_ex(
        ta->allocator, ta->text + start_off, segment_len, ta->font,
        ta->font_size, (int32_t)ta_inner_width(ta), &ta->shaping_params);
    if (paragraph == NULL) {
      ta->vlines = old_lines;
      ta_vlines_destroy_range(ta, new_lines, prefix_count);
      my_darray_destroy(new_lines);
      return MY_RET_OOM;
    }
    for (i = 0; i < paragraph->line_count; i++) {
      const my_text_paragraph_line_t* line =
          my_text_paragraph_line_at(paragraph, i);
      if (line != NULL) {
        if (ta_vline_push(ta, pi, line->start_byte, line->end_byte,
                          line->start_cp, line->cp_count) != MY_RET_OK) {
          my_text_paragraph_destroy(paragraph);
          ta->vlines = old_lines;
          ta_vlines_destroy_range(ta, new_lines, prefix_count);
          my_darray_destroy(new_lines);
          return MY_RET_OOM;
        }
      }
    }
    my_text_paragraph_destroy(paragraph);
  }
  ta->vlines = new_lines;
  if (old_suffix_start == 0u) old_suffix_start = old_count;
  ta_vlines_destroy_range_to(ta, old_lines, prefix_count, old_suffix_start);
  my_darray_destroy(old_lines);
  ta->vlines_reuse_suffix = false;
  return MY_RET_OK;
}

static void ta_vlines_invalidate_from(my_text_area_t* ta, size_t from) {
  my_mem_free(ta->allocator, ta->vline_first_by_phys);
  ta->vline_first_by_phys = NULL;
  ta->vline_last_by_phys = NULL;
  ta->vline_index_count = 0;
  ta->vline_index_dirty = true;
  if (!ta->vlines_dirty || from < ta->vlines_dirty_from) {
    ta->vlines_dirty_from = from;
  }
  ta->vlines_dirty = true;
}

/** @brief Ensure visual lines are built (when wrap is on). */
static void ta_vlines_ensure(my_text_area_t* ta) {
  if (ta->wrap && ta->vlines_dirty) {
    if (ta_vlines_rebuild_from(ta, ta->vlines_dirty_from) == MY_RET_OK) {
      ta->vlines_dirty = false;
    }
  }
}

static bool ta_vline_index_ensure(my_text_area_t* ta) {
  size_t physical_count;
  size_t visual_count;
  size_t* map;
  size_t* first;
  size_t* last;
  size_t i;
  if (!ta->wrap) return false;
  ta_vlines_ensure(ta);
  if (!ta->vline_index_dirty) {
    return ta->vline_first_by_phys != NULL;
  }
  physical_count = ta_line_count(ta);
  my_mem_free(ta->allocator, ta->vline_first_by_phys);
  ta->vline_first_by_phys = NULL;
  ta->vline_last_by_phys = NULL;
  ta->vline_index_count = 0;
  ta->vline_index_dirty = false;
  if (physical_count == 0 ||
      physical_count > SIZE_MAX / (2u * sizeof(size_t))) {
    return false;
  }
  map = (size_t*)my_mem_alloc(ta->allocator,
                              physical_count * 2u * sizeof(size_t));
  if (map == NULL) return false;
  first = map;
  last = map + physical_count;
  for (i = 0; i < physical_count; i++) {
    first[i] = SIZE_MAX;
    last[i] = SIZE_MAX;
  }
  visual_count = my_darray_size(ta->vlines);
  for (i = 0; i < visual_count; i++) {
    const my_visual_line_t* line =
        (const my_visual_line_t*)my_darray_get(ta->vlines, i);
    if (line == NULL || line->phys >= physical_count) continue;
    if (first[line->phys] == SIZE_MAX) first[line->phys] = i;
    last[line->phys] = i;
  }
  ta->vline_first_by_phys = first;
  ta->vline_last_by_phys = last;
  ta->vline_index_count = physical_count;
  return true;
}

static size_t ta_vline_count(my_text_area_t* ta) {
  if (!ta->wrap) {
    return ta_visible_row_count(ta);
  }
  ta_vlines_ensure(ta);
  return ta->vlines != NULL ? my_darray_size(ta->vlines) : 0;
}

static const my_visual_line_t* ta_vline_at(my_text_area_t* ta, size_t vi) {
  if (!ta->wrap) {
    static my_visual_line_t tmp;
    size_t start;
    size_t end;
    tmp.phys = ta_visible_row_at(ta, vi);
    start = ta_line_start(ta, tmp.phys);
    end = tmp.phys + 1 < ta_line_count(ta)
              ? ta_line_start(ta, tmp.phys + 1)
              : ta->text_len;
    end = ta_line_content_end(ta, start, end);
    tmp.start_byte = 0;
    tmp.len_bytes = end - start;
    tmp.start_cp = 0;
    tmp.len_cp = ta_line_cp_len(ta, tmp.phys);
    return &tmp;
  }
  ta_vlines_ensure(ta);
  return (const my_visual_line_t*)my_darray_get(ta->vlines, vi);
}

/** @brief Visual line index containing (row, col); -1 when beyond. */
static size_t ta_vline_of_pos(my_text_area_t* ta, size_t row, size_t col,
                              size_t* col_in_v) {
  size_t n = ta_vline_count(ta);
  size_t lo = 0, hi = n;
  if (n == 0) {
    *col_in_v = 0;
    return 0;
  }
  if (ta_vline_index_ensure(ta) && row < ta->vline_index_count &&
      ta->vline_first_by_phys[row] != SIZE_MAX) {
    lo = ta->vline_first_by_phys[row];
    hi = ta->vline_last_by_phys[row] + 1;
  }
  /* vlines are sorted by (phys, start_cp): binary search the last vline
   * with (phys, start_cp) <= (row, col). At a shared boundary col the
   * LATER visual line owns it, which the upper-bound search yields. */
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    const my_visual_line_t* v = ta_vline_at(ta, mid);
    if (v->phys < row || (v->phys == row && v->start_cp <= col)) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }
  if (lo > 0) {
    const my_visual_line_t* v = ta_vline_at(ta, lo - 1);
    if (v->phys == row && col <= v->start_cp + v->len_cp) {
      *col_in_v = col - v->start_cp;
      return lo - 1;
    }
  }
  *col_in_v = 0;
  return n - 1;
}


/* ---------------- buffer ops ---------------- */

static bool ta_syntax_active(const my_text_area_t* ta) {
  return ta != NULL && ta->syntax_enabled &&
         ta->syntax_language != MY_SYNTAX_NONE;
}

static void ta_syntax_destroy(my_text_area_t* ta) {
  if (ta == NULL) return;
  my_syntax_cache_destroy(ta->syntax_cache);
  ta->syntax_cache = NULL;
}

static void ta_syntax_drop_on_error(my_text_area_t* ta) {
  ta_syntax_destroy(ta);
}

static void ta_syntax_sync_after_edit(my_text_area_t* ta, size_t row,
                                      size_t old_line_count) {
  size_t start, end, line_len;
  if (!ta_syntax_active(ta) || ta->syntax_cache == NULL) return;
  if (old_line_count != ta_line_count(ta)) {
    if (my_syntax_cache_set_text(ta->syntax_cache, ta->text) != MY_RET_OK) {
      ta_syntax_drop_on_error(ta);
    }
    return;
  }
  if (row >= ta_line_count(ta)) {
    ta_syntax_drop_on_error(ta);
    return;
  }
  start = ta_line_start(ta, row);
  end = row + 1 < ta_line_count(ta) ? ta_line_start(ta, row + 1)
                                    : ta->text_len;
  line_len = end > start ? end - start : 0;
  line_len = ta_line_content_end(ta, start, start + line_len) - start;
  if (my_syntax_cache_replace_line_n(ta->syntax_cache, row, ta->text + start,
                                     line_len) != MY_RET_OK) {
    ta_syntax_drop_on_error(ta);
  }
}

static my_ret_t ta_syntax_prepare_document(my_text_area_t* ta,
                                            const char* text,
                                            my_syntax_cache_t** out_cache) {
  my_syntax_cache_t* cache;
  if (out_cache == NULL) return MY_RET_INVALID_PARAMS;
  *out_cache = NULL;
  if (!ta_syntax_active(ta)) return MY_RET_OK;
  cache = my_syntax_cache_create(ta->allocator, ta->syntax_language);
  if (cache == NULL) return MY_RET_OOM;
  if (my_syntax_cache_set_text(cache, text != NULL ? text : "") != MY_RET_OK) {
    my_syntax_cache_destroy(cache);
    return MY_RET_INVALID_PARAMS;
  }
  *out_cache = cache;
  return MY_RET_OK;
}

static my_ret_t ta_syntax_ensure_cache(my_text_area_t* ta) {
  my_syntax_cache_t* cache;
  if (!ta_syntax_active(ta) || ta->syntax_cache != NULL) return MY_RET_OK;
  if (ta_syntax_prepare_document(ta, ta->text, &cache) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  ta->syntax_cache = cache;
  return MY_RET_OK;
}

static uint32_t ta_syntax_color(uint32_t normal,
                                my_syntax_token_kind_t kind) {
  switch (kind) {
    case MY_SYNTAX_TOKEN_KEYWORD: return 0x9B59B6FFu;
    case MY_SYNTAX_TOKEN_NUMBER: return 0x1D70A2FFu;
    case MY_SYNTAX_TOKEN_STRING: return 0xA04000FFu;
    case MY_SYNTAX_TOKEN_COMMENT: return 0x6B7280FFu;
    default: return normal;
  }
}

static my_syntax_token_kind_t ta_syntax_kind_at(
    const my_syntax_token_t* tokens, size_t count, size_t logical) {
  size_t lo = 0;
  size_t hi = count;
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    size_t start = tokens[mid].start_cp;
    size_t len = tokens[mid].len_cp;
    if (logical < start) {
      hi = mid;
    } else if (logical - start < len) {
      return tokens[mid].kind;
    } else {
      lo = mid + 1;
    }
  }
  return MY_SYNTAX_TOKEN_TEXT;
}

static my_ret_t ta_draw_text(my_text_area_t* ta, my_vgcanvas_t* vg,
                             const char* text, float x, float y) {
  return my_vgcanvas_draw_text_ex(vg, text, x, y, &ta->shaping_params);
}

static void ta_draw_visual_syntax_segment(
    my_text_area_t* ta, my_vgcanvas_t* vg, my_text_layout_t* layout,
    size_t start, size_t end, size_t visual_start,
    my_syntax_token_kind_t kind, float base_x, int32_t ty, uint32_t normal) {
  char saved = layout->visual_utf8[end];
  layout->visual_utf8[end] = '\0';
  my_vgcanvas_set_fill_color(
      vg, my_color_from_rgba32(ta_syntax_color(normal, kind)));
  ta_draw_text(
      ta, vg, layout->visual_utf8 + start,
      base_x + (float)my_text_layout_visual_boundary_x_ex(
                   layout, ta->font, ta->font_size, visual_start,
                   &ta->shaping_params),
      (float)ty);
  layout->visual_utf8[end] = saved;
}

static bool ta_draw_syntax_line(my_text_area_t* ta, my_vgcanvas_t* vg,
                                const my_visual_line_t* vl, const char* line,
                                float base_x, int32_t ty, uint32_t normal,
                                my_text_layout_t* layout) {
  size_t count = 0, i;
  const my_syntax_token_t* tokens;
  if (ta->font == NULL || ta->syntax_cache == NULL ||
      !my_syntax_cache_line_ready(ta->syntax_cache, vl->phys)) {
    return false;
  }
  tokens = my_syntax_cache_line_tokens(ta->syntax_cache, vl->phys, &count);
  if (tokens == NULL || count == 0) return false;
  if (layout != NULL) {
    size_t visual_offset = 0;
    size_t group_start = 0;
    size_t group_visual_start = 0;
    my_syntax_token_kind_t group_kind = MY_SYNTAX_TOKEN_TEXT;
    bool group_open = false;
    const char* visual = layout->visual_utf8;
    size_t visual_index;
    for (visual_index = 0; visual_index < layout->len; visual_index++) {
      size_t item_start = visual_offset;
      size_t logical = layout->visual_to_logical[visual_index];
      my_syntax_token_kind_t kind =
          ta_syntax_kind_at(tokens, count, logical + vl->start_cp);
      (void)my_utf8_next(&visual);
      visual_offset = (size_t)(visual - layout->visual_utf8);
      if (layout->visual_rtl[visual_index] != 0) {
        if (group_open) {
          ta_draw_visual_syntax_segment(ta, vg, layout, group_start,
                                        item_start, group_visual_start,
                                        group_kind, base_x, ty, normal);
        }
        ta_draw_visual_syntax_segment(ta, vg, layout, item_start,
                                      visual_offset, visual_index, kind,
                                      base_x, ty, normal);
        group_open = false;
      } else if (!group_open) {
        group_open = true;
        group_start = item_start;
        group_visual_start = visual_index;
        group_kind = kind;
      } else if (kind != group_kind) {
        ta_draw_visual_syntax_segment(ta, vg, layout, group_start, item_start,
                                      group_visual_start, group_kind, base_x,
                                      ty, normal);
        group_start = item_start;
        group_visual_start = visual_index;
        group_kind = kind;
      }
    }
    if (group_open) {
      ta_draw_visual_syntax_segment(ta, vg, layout, group_start, visual_offset,
                                    group_visual_start, group_kind, base_x, ty,
                                    normal);
    }
    return true;
  }
  for (i = 0; i < count; i++) {
    size_t start = tokens[i].start_cp > vl->start_cp
                       ? tokens[i].start_cp : vl->start_cp;
    size_t end = ta_sat_size_add(tokens[i].start_cp, tokens[i].len_cp);
    size_t visual_end = ta_sat_size_add(vl->start_cp, vl->len_cp);
    size_t byte_start, byte_end;
    char saved;
    int32_t token_width = 0;
    if (end > visual_end) end = visual_end;
    if (start >= end) continue;
    byte_start = start == vl->start_cp
                     ? 0
                     : tokens[i].start_byte - vl->start_byte;
    byte_end = end == visual_end
                   ? vl->len_bytes
                   : tokens[i].start_byte + tokens[i].len_bytes -
                         vl->start_byte;
    if (byte_start >= byte_end || byte_end > vl->len_bytes) continue;
    saved = ((char*)line)[byte_end];
    ((char*)line)[byte_end] = '\0';
    my_vgcanvas_set_fill_color(
        vg, my_color_from_rgba32(ta_syntax_color(normal, tokens[i].kind)));
    ta_draw_text(ta, vg, line + byte_start, base_x, (float)ty);
    if (ta->font != NULL) {
      my_vgcanvas_measure_text(vg, line + byte_start, &token_width, NULL);
    } else {
      token_width = ta_sat_size_mul(end - start, TA_CELL_W);
    }
    base_x += (float)token_width;
    ((char*)line)[byte_end] = saved;
  }
  return true;
}

static void ta_cursor_to_offset(my_text_area_t* ta, size_t offset) {
  ta_pos_of(ta, offset, &ta->cursor_row, &ta->cursor_col);
  ta->anchor_row = ta->cursor_row;
  ta->anchor_col = ta->cursor_col;
  ta->goal_col = ta->cursor_col;
}

static my_ret_t ta_reserve(my_text_area_t* ta, size_t extra) {
  size_t need;
  size_t cap;
  char* p;
  if (ta->text_len == SIZE_MAX || extra > SIZE_MAX - ta->text_len - 1) {
    return MY_RET_OOM;
  }
  need = ta->text_len + extra + 1;
  if (need <= ta->text_cap) {
    return MY_RET_OK;
  }
  cap = ta->text_cap > 0 ? ta->text_cap : 1;
  while (cap < need) {
    if (cap > SIZE_MAX / 2) {
      cap = need;
      break;
    }
    cap *= 2;
  }
  p = (char*)my_mem_realloc(ta->allocator, ta->text, cap);
  if (p == NULL) return MY_RET_OOM;
  ta->text = p;
  ta->text_cap = cap;
  return MY_RET_OK;
}

static size_t ta_total_cps(const my_text_area_t* ta) {
  size_t n = 0, off = 0;
  while (off < ta->text_len) {
    off += my_str_utf8_char_len(ta->text + off);
    n++;
  }
  return n;
}

static bool ta_sel(const my_text_area_t* ta, size_t* r0, size_t* c0,
                   size_t* r1, size_t* c1) {
  bool fwd;
  if (ta->cursor_row == ta->anchor_row && ta->cursor_col == ta->anchor_col) {
    return false;
  }
  fwd = ta->cursor_row < ta->anchor_row ||
        (ta->cursor_row == ta->anchor_row && ta->cursor_col < ta->anchor_col);
  if (fwd) {
    *r0 = ta->cursor_row;
    *c0 = ta->cursor_col;
    *r1 = ta->anchor_row;
    *c1 = ta->anchor_col;
  } else {
    *r0 = ta->anchor_row;
    *c0 = ta->anchor_col;
    *r1 = ta->cursor_row;
    *c1 = ta->cursor_col;
  }
  return true;
}

static void emit_changed(my_text_area_t* ta) {
  my_emitter_emit(((my_widget_t*)ta)->emitter, "changed",
                  ta->text != NULL ? ta->text : "");
}

static void ta_rtl_cache_clear(my_text_area_t* ta) {
  size_t i;
  for (i = 0; i < MY_TEXT_AREA_RTL_CACHE_CAPACITY; i++) {
    my_text_layout_destroy(ta->rtl_cache[i].layout);
    memset(&ta->rtl_cache[i], 0, sizeof(ta->rtl_cache[i]));
  }
  ta->rtl_cache_tick = 0;
  ta->rtl_layout = NULL;
}

static uint64_t ta_rtl_cache_next_tick(my_text_area_t* ta) {
  size_t i;
  if (ta->rtl_cache_tick == UINT64_MAX) {
    ta->rtl_cache_tick = 0;
    for (i = 0; i < MY_TEXT_AREA_RTL_CACHE_CAPACITY; i++) {
      ta->rtl_cache[i].last_used = 0;
    }
  }
  ta->rtl_cache_tick++;
  return ta->rtl_cache_tick;
}

static void ta_rtl_cache_mirror(my_text_area_t* ta,
                                const my_text_area_rtl_cache_entry_t* entry) {
  ta->rtl_layout = entry->layout;
  ta->rtl_phys = entry->phys;
  ta->rtl_start_byte = entry->start_byte;
  ta->rtl_len_bytes = entry->len_bytes;
  ta->rtl_revision = entry->text_revision;
  ta->rtl_shaping_revision = entry->shaping_revision;
  ta->rtl_font = entry->font;
  ta->rtl_font_size = entry->font_size;
}

static void ta_bump_text_revision(my_text_area_t* ta) {
  ta->text_revision = ta->text_revision == UINT64_MAX
                           ? 1
                           : ta->text_revision + 1;
  ta_rtl_cache_clear(ta);
  ta->navigation_valid = false;
}

static my_ret_t ta_replace_prepare(my_text_area_t* ta, size_t start,
                                   size_t end, const char* bytes, size_t n,
                                   bool enforce_max_len) {
  size_t removed_len;
  size_t removed_cps;
  size_t inserted_cps;
  size_t current_cps;
  size_t extra = 0;
  if (ta == NULL || start > end || end > ta->text_len) {
    return MY_RET_INVALID_PARAMS;
  }
  removed_len = end - start;
  if (n > SIZE_MAX - (ta->text_len - removed_len) ||
      (bytes == NULL && n > 0)) {
    return MY_RET_INVALID_PARAMS;
  }
  removed_cps = my_str_utf8_strlen(ta->text + start) -
                my_str_utf8_strlen(ta->text + end);
  inserted_cps = my_str_utf8_strlen(bytes != NULL ? bytes : "");
  current_cps = ta_total_cps(ta);
  if (removed_cps > current_cps) {
    return MY_RET_INVALID_PARAMS;
  }
  if (enforce_max_len && ta->max_len > 0) {
    size_t remaining = current_cps - removed_cps;
    if (inserted_cps > ta->max_len ||
        remaining > ta->max_len - inserted_cps) {
      return MY_RET_FAIL;
    }
  }
  if (n > removed_len) {
    extra = n - removed_len;
  }
  if (ta_reserve(ta, extra) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

static my_ret_t ta_replace_bytes_prepared(my_text_area_t* ta, size_t start,
                                          size_t end, const char* bytes,
                                          size_t n) {
  size_t removed_len;
  size_t old_lines;
  size_t old_text_len;
  size_t old_suffix_phys = 0u;
  size_t old_suffix_byte = 0u;
  bool suffix_candidate = false;
  size_t row;
  removed_len = end - start;
  old_lines = ta_line_count(ta);
  old_text_len = ta->text_len;
  ta->vlines_reuse_suffix = false;
  if (ta->wrap && !ta->vlines_dirty && old_lines > 1u &&
      (ta->fold_ranges == NULL || my_darray_size(ta->fold_ranges) == 0u)) {
    size_t edit_row;
    size_t candidate;
    ta_pos_of(ta, start, &edit_row, NULL);
    for (candidate = edit_row + 1u; candidate < old_lines; ++candidate) {
      old_suffix_byte = ta_line_start(ta, candidate);
      if (old_suffix_byte > end ||
          (n >= removed_len && old_suffix_byte == end)) {
        old_suffix_phys = candidate;
        suffix_candidate = true;
        break;
      }
    }
  }
  memmove(ta->text + start + n, ta->text + end,
          ta->text_len - end + 1);
  if (n > 0) {
    memcpy(ta->text + start, bytes, n);
  }
  ta->text_len = ta->text_len - removed_len + n;
  ta_bump_text_revision(ta);
  ta_pos_of(ta, start, &row, NULL);
  ta_rebuild_from(ta, row);
  if (suffix_candidate && old_suffix_byte <= old_text_len) {
    size_t delta = n >= removed_len ? n - removed_len : removed_len - n;
    size_t new_suffix_byte;
    size_t new_suffix_phys;
    if (n >= removed_len) {
      new_suffix_byte = old_suffix_byte > SIZE_MAX - delta
                            ? SIZE_MAX
                            : old_suffix_byte + delta;
    } else {
      new_suffix_byte = old_suffix_byte < delta
                            ? SIZE_MAX
                            : old_suffix_byte - delta;
    }
    for (new_suffix_phys = row + 1u; new_suffix_phys < ta_line_count(ta);
         ++new_suffix_phys) {
      if (ta_line_start(ta, new_suffix_phys) == new_suffix_byte) break;
    }
    if (new_suffix_phys < ta_line_count(ta)) {
      size_t old_line_index = 0u;
      size_t old_visual_count = my_darray_size(ta->vlines);
      while (old_line_index < old_visual_count) {
        const my_visual_line_t* line =
            (const my_visual_line_t*)my_darray_get(ta->vlines,
                                                   old_line_index);
        if (line != NULL && line->phys >= old_suffix_phys) break;
        old_line_index++;
      }
      if (old_line_index < old_visual_count) {
        ta->vlines_reuse_suffix = true;
        ta->vlines_reuse_old_line_index = old_line_index;
        ta->vlines_reuse_old_phys = old_suffix_phys;
        ta->vlines_reuse_new_phys = new_suffix_phys;
      }
    }
  }
  ta_syntax_sync_after_edit(ta, row, old_lines);
  if (ta_line_count(ta) != old_lines) {
    ta_clear_folds(ta);
    if (ta->wrap) {
      ta_vlines_invalidate_from(ta, 0);
    }
  }
  return MY_RET_OK;
}

static my_ret_t ta_replace_bytes(my_text_area_t* ta, size_t start, size_t end,
                                 const char* bytes, size_t n,
                                 bool enforce_max_len) {
  my_ret_t result = ta_replace_prepare(ta, start, end, bytes, n,
                                       enforce_max_len);
  if (result != MY_RET_OK) return result;
  return ta_replace_bytes_prepared(ta, start, end, bytes, n);
}

static void user_insert(my_text_area_t* ta, const char* bytes, size_t n,
                        size_t cp_count) {
  my_widget_t* held = my_widget_ref((my_widget_t*)ta);
  size_t r0, c0, r1, c1, start;
  if (ta->readonly) {
    goto done;
  }
  if (ta_sel(ta, &r0, &c0, &r1, &c1)) {
    size_t s0 = ta_offset_of(ta, r0, c0);
    size_t s1 = ta_offset_of(ta, r1, c1);
    my_ret_t result;
    if (ta_replace_prepare(ta, s0, s1, bytes, n, true) != MY_RET_OK) {
      goto done;
    }
    if (!ta->applying_history) {
      if (ta->undo_shared != NULL) {
        result = my_undo_manager_record_replace(
            ta->undo_shared, ta, s0, ta->text + s0, s1 - s0, bytes, n);
      } else if (ta->undo != NULL) {
        result = my_undo_stack_record_replace(ta->undo, s0, ta->text + s0,
                                              s1 - s0, bytes, n);
      } else {
        result = MY_RET_OK;
      }
      if (result != MY_RET_OK) {
        goto done;
      }
    }
    if (ta_replace_bytes_prepared(ta, s0, s1, bytes, n) != MY_RET_OK) {
      goto done;
    }
    ta_cursor_to_offset(ta, s0 + n);
    emit_changed(ta);
    my_widget_invalidate((my_widget_t*)ta, NULL);
    goto done;
  }
  start = ta_offset_of(ta, ta->cursor_row, ta->cursor_col);
  if (ta_replace_prepare(ta, start, start, bytes, n, true) != MY_RET_OK) {
    goto done;
  }
  (void)cp_count;
  if (!ta->applying_history) {
    if (ta->undo_shared != NULL) {
      if (my_undo_manager_record_insert(ta->undo_shared, ta, start, bytes,
                                        n) != MY_RET_OK) {
        goto done;
      }
    } else if (ta->undo != NULL) {
      if (my_undo_stack_record_insert(ta->undo, start, bytes, n) != MY_RET_OK) {
        goto done;
      }
    }
  }
  if (ta_replace_bytes_prepared(ta, start, start, bytes, n) != MY_RET_OK) {
    return;
  }
  ta_cursor_to_offset(ta, start + n);
  emit_changed(ta);
  my_widget_invalidate((my_widget_t*)ta, NULL);
done:
  my_widget_unref(held);
}

static my_ret_t ta_paste(my_text_area_t* ta) {
  my_pal_t* pal = my_window_pal_of_widget((my_widget_t*)ta);
  char* text = NULL;
  my_ret_t result;
  if (pal == NULL || ta->readonly) return MY_RET_NOT_FOUND;
  result = my_pal_clipboard_get_text_alloc(pal, ta->allocator, &text);
  if (result != MY_RET_OK) return result;
  if (*text != '\0') {
    user_insert(ta, text, strlen(text), my_str_utf8_strlen(text));
  }
  my_mem_free(ta->allocator, text);
  return MY_RET_OK;
}

static void user_delete_range(my_text_area_t* ta, size_t start, size_t end) {
  my_widget_t* held = my_widget_ref((my_widget_t*)ta);
  my_ret_t result;
  if (ta->readonly) {
    goto done;
  }
  if (ta_replace_prepare(ta, start, end, NULL, 0, false) != MY_RET_OK) {
    goto done;
  }
  if (!ta->applying_history) {
    if (ta->undo_shared != NULL) {
      result = my_undo_manager_record_delete(ta->undo_shared, ta, start,
                                              ta->text + start, end - start);
    } else if (ta->undo != NULL) {
      result = my_undo_stack_record_delete(ta->undo, start, ta->text + start,
                                            end - start);
    } else {
      result = MY_RET_OK;
    }
    if (result != MY_RET_OK) {
      goto done;
    }
  }
  if (ta_replace_bytes_prepared(ta, start, end, NULL, 0) != MY_RET_OK) {
    return;
  }
  ta_cursor_to_offset(ta, start);
  emit_changed(ta);
  my_widget_invalidate((my_widget_t*)ta, NULL);
done:
  my_widget_unref(held);
}

/* ---------------- scrolling ---------------- */

static int32_t ta_line_height(const my_text_area_t* ta) {
  int32_t line_h = ta->font != NULL
                       ? my_font_line_height(ta->font, ta->font_size)
                       : ta->font_size;
  return line_h > 0 ? line_h : 16;
}

static void ta_sync_scroll_bar(my_text_area_t* ta) {
  my_widget_t* w = (my_widget_t*)ta;
  int32_t content, max;
  if (ta->scroll_bar == NULL) {
    return;
  }
  content = ta_sat_size_mul(ta_vline_count(ta), ta_line_height(ta));
  max = ta_sat_i64((int64_t)content -
                   ((int64_t)w->rect.h - 2 * TA_PAD_Y));
  if (max < 0) {
    max = 0;
  }
  my_scroll_bar_set_page_size(
      ta->scroll_bar, content > 0 ? (float)ta_inner_height(ta) / (float)content
                                  : 1.0f);
  my_scroll_bar_set_value(ta->scroll_bar,
                          max > 0 ? (float)ta->scroll_y / (float)max : 0.0f);
}

static void ta_on_scroll_bar_changed(void* ctx, const char* event, void* data) {
  my_text_area_t* ta = (my_text_area_t*)ctx;
  int32_t max = ta_sat_i64(
      (int64_t)ta_sat_size_mul(ta_vline_count(ta), ta_line_height(ta)) -
      ((int64_t)((my_widget_t*)ta)->rect.h - 2 * TA_PAD_Y));
  (void)event;
  (void)data;
  if (max < 0) {
    max = 0;
  }
  ta->scroll_y = ta_sat_f32(
      my_scroll_bar_get_value(ta->scroll_bar) * (float)max);
  ta_sync_scroll_bar(ta);
  my_widget_invalidate((my_widget_t*)ta, NULL);
}

my_ret_t my_text_area_set_scroll_bar(my_widget_t* area, my_widget_t* bar) {
  my_text_area_t* ta = (my_text_area_t*)area;
  uint32_t listener_id;
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (bar != NULL && !my_scroll_bar_is_instance(bar)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (bar == ta->scroll_bar) {
    ta_sync_scroll_bar(ta);
    return MY_RET_OK;
  }
  if (bar != NULL) {
    listener_id = my_widget_on(bar, "changed", ta_on_scroll_bar_changed, ta);
    if (listener_id == 0u) return MY_RET_OOM;
  } else {
    listener_id = 0u;
  }
  if (ta->scroll_bar != NULL && ta->scroll_bar_listener_id != 0u) {
    (void)my_widget_off(ta->scroll_bar, ta->scroll_bar_listener_id);
  }
  if (ta->scroll_bar != NULL) {
    my_widget_unref(ta->scroll_bar);
  }
  ta->scroll_bar = bar;
  ta->scroll_bar_listener_id = listener_id;
  if (ta->scroll_bar != NULL) {
    my_widget_ref(ta->scroll_bar);
  }
  ta_sync_scroll_bar(ta);
  return MY_RET_OK;
}

static void ta_ensure_visible(my_text_area_t* ta) {
  int32_t line_h = ta->font != NULL
                       ? my_font_line_height(ta->font, ta->font_size)
                       : ta->font_size;
  int32_t inner_h, inner_w, cy, row_px;
  int64_t row_px_64;
  if (line_h <= 0) {
    line_h = ta->font_size > 0 ? ta->font_size : 16;
  }
  inner_h = ta_inner_height(ta);
  inner_w = ta_inner_width_i32(ta);
  if (ta->wrap) {
    size_t civ;
    ta->scroll_x = 0; /* wrap: no horizontal scrolling */
    row_px_64 = (int64_t)ta_vline_of_pos(ta, ta->cursor_row, ta->cursor_col,
                                         &civ) * line_h;
  } else {
    row_px_64 = (int64_t)ta_visible_index_of_row(ta, ta->cursor_row) * line_h;
  }
  row_px = ta_sat_i64(row_px_64);
  if (inner_h > 0) {
    if (row_px - ta->scroll_y < 0) {
      ta->scroll_y = row_px;
    }
    if (row_px_64 + line_h - ta->scroll_y > inner_h) {
      ta->scroll_y = ta_sat_i64(row_px_64 + line_h - inner_h);
    }
  }
  if (!ta->wrap && inner_w > 0) {
    cy = ta_sat_add(ta_content_left_value(ta),
                    ta_line_boundary_x(ta, ta->cursor_row, ta->cursor_col));
    if (cy - ta->scroll_x < 0) {
      ta->scroll_x = cy;
    }
    if (cy - ta->scroll_x > inner_w) {
      ta->scroll_x = cy - inner_w;
    }
  }
  ta_sync_scroll_bar(ta);
}

/* ---------------- key handling ---------------- */

static char* ta_vline_text(my_text_area_t* ta, const my_visual_line_t* vl);
static void ta_update_ime_spot(my_text_area_t* ta); /* fwd (M13a) */

static void ta_move_to(my_text_area_t* ta, size_t row, size_t col,
                       bool select) {
  size_t lines = ta_line_count(ta);
  ta->navigation_valid = false;
  if (row >= lines) {
    row = lines > 0 ? lines - 1 : 0;
  }
  if (ta_row_hidden(ta, row)) {
    size_t i;
    for (i = 0; i < my_darray_size(ta->fold_ranges); i++) {
      const my_text_fold_range_t* range =
          (const my_text_fold_range_t*)my_darray_get(ta->fold_ranges, i);
      if (range != NULL && row <= range->end_row && row > range->start_row) {
        row = range->start_row;
        break;
      }
    }
  }
  {
    size_t max_col = ta_line_cp_len(ta, row);
    if (col > max_col) {
      col = max_col;
    }
  }
  ta->cursor_row = row;
  ta->cursor_col = col;
  if (!select) {
    ta->anchor_row = row;
    ta->anchor_col = col;
    /* goal_col is intentionally NOT updated here: vertical moves keep it,
     * horizontal moves set it at the call site */
  }
  ta_ensure_visible(ta);
  ta_update_ime_spot(ta); /* candidate anchor follows the cursor (M13a) */
  my_widget_invalidate((my_widget_t*)ta, NULL);
}

/** @brief Push the cursor's window coordinates to the PAL as the IME
 * candidate anchor (M13a; no-op without a window/IM). */
static void ta_update_ime_spot(my_text_area_t* ta) {
  my_widget_t* root = (my_widget_t*)ta;
  my_window_t* win;
  int32_t line_h, x, y;
  size_t visual_index = ta->cursor_row;
  size_t col_in = ta->cursor_col;
  int32_t cursor_x = ta_sat_size_mul(ta->cursor_col, TA_CELL_W);
  int32_t line_width = 0;
  int32_t inner_width;
  int32_t line_offset = 0;
  bool justify = false;
  size_t space_count = 0u;
  const my_visual_line_t* visual_line = NULL;
  my_text_layout_t* line_layout = NULL;
  char* line = NULL;
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (!my_str_eq(root->widget_type, "window")) {
    return;
  }
  win = (my_window_t*)root;
  if (win->pal_window == NULL) {
    return;
  }
  line_h = ta->font != NULL ? my_font_line_height(ta->font, ta->font_size)
                            : ta->font_size;
  if (line_h <= 0) {
    line_h = 16;
  }
  if (ta->wrap) {
    visual_index = ta_vline_of_pos(ta, ta->cursor_row, ta->cursor_col,
                                   &col_in);
    visual_line = ta_vline_at(ta, visual_index);
    if (visual_line != NULL) {
      col_in = ta->cursor_col - visual_line->start_cp;
      line_layout = ta_layout_rtl(ta, visual_line);
      if (line_layout == NULL) {
        line = ta_vline_text(ta, visual_line);
      }
      line_width = ta_sat_size_mul(visual_line->len_cp, TA_CELL_W);
      if (line_layout != NULL) {
        line_width = my_text_layout_visual_boundary_x_ex(
            line_layout, ta->font, ta->font_size, line_layout->len,
            &ta->shaping_params);
        space_count = ta_layout_justify_space_count(line_layout);
      } else if (line != NULL && ta->font != NULL) {
        (void)my_font_measure(ta->font, line, ta->font_size, &line_width,
                              NULL);
      }
      if (line == NULL && line_layout == NULL) {
        space_count = 0u;
      } else if (line_layout == NULL && line != NULL) {
        space_count = (size_t)ta_justify_space_count(line, strlen(line));
      }
      inner_width = ta_inner_width_i32(ta);
      if (ta->align == MY_TEXT_ALIGN_JUSTIFY && inner_width > line_width &&
          space_count > 0u && visual_index + 1 < ta_vline_count(ta) &&
          ta_vline_at(ta, visual_index + 1)->phys == visual_line->phys) {
        justify = true;
      }
      if (justify && line_layout != NULL) {
        cursor_x = ta_layout_justify_boundary_x(
            ta, line_layout, col_in, space_count, line_width, inner_width);
      } else if (justify && line != NULL) {
        cursor_x = ta_justify_boundary_x(ta, line, col_in, space_count,
                                         line_width, inner_width);
      } else if (line_layout != NULL) {
        cursor_x = my_text_layout_visual_x_ex(
            line_layout, ta->font, ta->font_size, col_in,
            &ta->shaping_params);
      } else {
        cursor_x = ta_line_boundary_x(
                       ta, visual_line->phys, visual_line->start_cp + col_in) -
                   ta_line_boundary_x(ta, visual_line->phys,
                                      visual_line->start_cp);
      }
      if (!justify) {
        if (ta->align == MY_TEXT_ALIGN_CENTER) {
          line_offset = (inner_width - line_width) / 2;
        } else if (ta->align == MY_TEXT_ALIGN_RIGHT ||
                   (ta->align == MY_TEXT_ALIGN_LEFT && line_layout != NULL &&
                    line_layout->rtl_base)) {
          line_offset = inner_width - line_width;
        }
        if (line_offset < 0) {
          line_offset = 0;
        }
        cursor_x += line_offset;
      }
    }
  }
  if (!ta->wrap) {
    visual_line = ta_vline_at(ta, visual_index);
    line_layout = visual_line != NULL ? ta_layout_rtl(ta, visual_line) : NULL;
    if (line_layout != NULL) {
      line_width = my_text_layout_visual_boundary_x_ex(
          line_layout, ta->font, ta->font_size, line_layout->len,
          &ta->shaping_params);
    } else if (visual_line != NULL) {
      line_width = ta_sat_size_mul(visual_line->len_cp, TA_CELL_W);
      line = ta_vline_text(ta, visual_line);
      if (line != NULL && ta->font != NULL) {
        (void)my_font_measure(ta->font, line, ta->font_size, &line_width,
                              NULL);
      }
    }
    inner_width = ta_inner_width_i32(ta);
    if (ta->align == MY_TEXT_ALIGN_CENTER) {
      line_offset = (inner_width - line_width) / 2;
    } else if (ta->align == MY_TEXT_ALIGN_RIGHT ||
               (ta->align == MY_TEXT_ALIGN_LEFT && line_layout != NULL &&
                line_layout->rtl_base)) {
      line_offset = inner_width - line_width;
    }
    if (line_offset < 0) {
      line_offset = 0;
    }
    if (line_layout != NULL) {
      cursor_x = my_text_layout_visual_x_ex(
          line_layout, ta->font, ta->font_size, ta->cursor_col,
          &ta->shaping_params);
    } else {
      cursor_x = ta_line_boundary_x(ta, ta->cursor_row, ta->cursor_col);
    }
    cursor_x += line_offset;
  }
  x = ta_sat_i64((int64_t)ta_content_left_value(ta) + cursor_x -
                 ta->scroll_x);
  y = ta_sat_i64((int64_t)TA_PAD_Y +
                 (int64_t)visual_index * line_h - ta->scroll_y + line_h);
  my_mem_free(ta->allocator, line);
  my_widget_local_to_global((my_widget_t*)ta, &x, &y);
  my_pal_window_ime_set_spot(win->pal_window, x, y);
  my_pal_window_ime_set_surrounding(
      win->pal_window, ta->text != NULL ? ta->text : "",
      (int32_t)ta_offset_of(ta, ta->cursor_row, ta->cursor_col),
      (int32_t)ta_offset_of(ta, ta->anchor_row, ta->anchor_col));
}

static void ta_set_ime_enabled(my_text_area_t* ta, bool enabled) {
  my_widget_t* root = (my_widget_t*)ta;
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (my_str_eq(root->widget_type, "window")) {
    my_window_t* win = (my_window_t*)root;
    if (win->pal_window != NULL) {
      my_pal_window_ime_set_enabled(win->pal_window, enabled);
    }
  }
}

/* ---------------- IME events (M13a) ---------------- */

static my_ret_t ta_on_ime_preedit(my_text_area_t* ta, const my_event_t* ev) {
  char* copy = my_strdup(ta->allocator, ev->u.ime.text != NULL
                                              ? ev->u.ime.text
                                              : "");
  if (copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(ta->allocator, ta->ime_preedit);
  ta->ime_preedit = *copy != '\0' ? copy : NULL;
  if (ta->ime_preedit == NULL) {
    my_mem_free(ta->allocator, copy);
  }
  ta->ime_caret = ev->u.ime.cursor;
  my_widget_invalidate((my_widget_t*)ta, NULL);
  return MY_RET_OK;
}

static my_ret_t ta_on_ime_commit(my_text_area_t* ta, const my_event_t* ev) {
  const char* text = ev->u.ime.text;
  my_mem_free(ta->allocator, ta->ime_preedit);
  ta->ime_preedit = NULL;
  if (!ta->readonly && text != NULL && *text != '\0') {
    /* a real edit: undo stack + "changed" + MVVM, like typed text */
    user_insert(ta, text, strlen(text), my_str_utf8_strlen(text));
  }
  my_widget_invalidate((my_widget_t*)ta, NULL);
  return MY_RET_OK;
}

static my_ret_t ta_on_ime_delete_surrounding(my_text_area_t* ta,
                                              const my_event_t* ev) {
  size_t before = ev->u.ime.before > 0 ? (size_t)ev->u.ime.before : 0;
  size_t after = ev->u.ime.after > 0 ? (size_t)ev->u.ime.after : 0;
  size_t cursor = ta_offset_of(ta, ta->cursor_row, ta->cursor_col);
  size_t start = before < cursor ? cursor - before : 0;
  size_t end = after < ta->text_len - cursor ? cursor + after : ta->text_len;
  if (!ta->readonly && start < end) {
    user_delete_range(ta, start, end);
  }
  return MY_RET_OK;
}

static my_ret_t ta_apply_history(my_text_area_t* ta, const my_undo_op_t* op) {
  my_widget_t* held = my_widget_ref((my_widget_t*)ta);
  my_ret_t result;
  ta->applying_history = true;
  if (op->offset > SIZE_MAX - op->remove_len) {
    ta->applying_history = false;
    my_widget_unref(held);
    return MY_RET_INVALID_PARAMS;
  }
  result = ta_replace_bytes(ta, op->offset, op->offset + op->remove_len,
                             op->bytes, op->bytes_len, false);
  if (result != MY_RET_OK) {
    ta->applying_history = false;
    my_widget_unref(held);
    return result;
  }
  ta_cursor_to_offset(ta, op->offset + op->bytes_len);
  ta->applying_history = false;
  emit_changed(ta);
  my_widget_invalidate((my_widget_t*)ta, NULL);
  my_widget_unref(held);
  return MY_RET_OK;
}

/** @brief Shared-mode apply callback (M11b). */
static my_ret_t ta_apply_undo_op(void* widget, const my_undo_op_t* op) {
  return ta_apply_history((my_text_area_t*)widget, op);
}

/* ---------------- RTL mapping (M12a): per visual line segment ---------
 * Wrap breaking itself stays in LOGICAL order; drawing, cursor, clicks and
 * selection use the visual mapping. Arrow navigation retains the visual-line
 * identity across shared logical boundaries. */

/** @brief Fresh NUL-terminated text of a visual line (caller frees). */
static char* ta_vline_text(my_text_area_t* ta, const my_visual_line_t* vl);
static my_text_layout_t* ta_layout_rtl(my_text_area_t* ta,
                                       const my_visual_line_t* vl);
static my_ret_t ta_paste_tick(void* ctx);

static my_ret_t ta_on_key(my_text_area_t* ta, const my_event_t* event) {
  uint32_t key = event->u.key.key;  uint8_t mods = event->u.key.modifiers;
  bool shift = (mods & MY_KEYMOD_SHIFT) != 0;
  bool ctrl = (mods & MY_KEYMOD_CTRL) != 0;

  if (ctrl && (key == 'z' || key == 'Z')) {
    if (ta->undo_shared != NULL) {
      if (shift) {
        my_undo_manager_redo(ta->undo_shared);
      } else {
        my_undo_manager_undo(ta->undo_shared);
      }
      return MY_RET_OK;
    }
    {
      my_undo_op_t op;
      bool redo = shift;
      my_ret_t r = redo ? my_undo_stack_redo_peek_tagged(ta->undo, &op, NULL)
                        : my_undo_stack_undo_peek_tagged(ta->undo, &op, NULL);
      if (r == MY_RET_OK && ta_apply_history(ta, &op) == MY_RET_OK) {
        if (redo) my_undo_stack_commit_redo(ta->undo);
        else my_undo_stack_commit_undo(ta->undo);
      }
    }
    return MY_RET_OK;
  }
  if (ctrl && (key == 'y' || key == 'Y')) {
    if (ta->undo_shared != NULL) {
      my_undo_manager_redo(ta->undo_shared);
      return MY_RET_OK;
    }
    {
      my_undo_op_t op;
      if (my_undo_stack_redo_peek_tagged(ta->undo, &op, NULL) == MY_RET_OK &&
          ta_apply_history(ta, &op) == MY_RET_OK) {
        my_undo_stack_commit_redo(ta->undo);
      }
    }
    return MY_RET_OK;
  }

  if (ctrl && (key == 'a' || key == 'A')) {
    ta->anchor_row = 0;
    ta->anchor_col = 0;
    ta->cursor_row = ta_line_count(ta) - 1;
    ta->cursor_col = ta_line_cp_len(ta, ta->cursor_row);
    my_widget_invalidate((my_widget_t*)ta, NULL);
    return MY_RET_OK;
  }
  if (ctrl && (key == 'c' || key == 'C' || key == 'x' || key == 'X')) {
    my_pal_t* pal = my_window_pal_of_widget((my_widget_t*)ta);
    size_t r0, c0, r1, c1;
    if (pal != NULL && ta_sel(ta, &r0, &c0, &r1, &c1)) {
      size_t s0 = ta_offset_of(ta, r0, c0);
      size_t s1 = ta_offset_of(ta, r1, c1);
      char* buf = (char*)my_mem_alloc(ta->allocator, s1 - s0 + 1);
      if (buf != NULL) {
        memcpy(buf, ta->text + s0, s1 - s0);
        buf[s1 - s0] = '\0';
        my_pal_clipboard_set_text(pal, buf);
        my_mem_free(ta->allocator, buf);
      }
      if (key == 'x' || key == 'X') {
        user_delete_range(ta, s0, s1);
      }
    }
    return MY_RET_OK;
  }
  if (ctrl && (key == 'v' || key == 'V')) {
    if (ta_paste(ta) == MY_RET_PENDING && ta->paste_timer_id == 0) {
      my_pal_main_loop_t* loop = my_window_loop_of_widget((my_widget_t*)ta);
      if (loop != NULL) {
        ta->paste_timer_id = my_pal_main_loop_add_timer(loop, ta_paste_tick,
                                                        ta, 10);
        ta->paste_loop = ta->paste_timer_id > 0 ? loop : NULL;
      }
    }
    return MY_RET_OK;
  }

  switch (key) {
    case MY_KEY_LEFT:
    case MY_KEY_RIGHT: {
      /* RTL (M12a): arrows move through the global visual-line order. The
       * adjacent visual line may belong to another physical line. */
      size_t vi;
      size_t navigation_target;
      bool track_navigation = ta->wrap;
      if (ta->wrap && ta->navigation_valid &&
          ta->navigation_row == ta->cursor_row &&
          ta->navigation_col == ta->cursor_col &&
          ta->navigation_visual_index < ta_vline_count(ta)) {
        vi = ta->navigation_visual_index;
      } else {
        vi = ta->wrap ? ta_vline_of_pos(ta, ta->cursor_row,
                                        ta->cursor_col, &(size_t){0})
                      : ta->cursor_row;
      }
      navigation_target = vi;
      const my_visual_line_t* vl = ta_vline_at(ta, vi);
      my_text_layout_t* l = ta_layout_rtl(ta, vl);
      if (l != NULL) {
        size_t col_in = ta->cursor_col - vl->start_cp;
        bool at_visual_start = col_in == my_text_layout_boundary_home(l);
        bool at_visual_end = col_in == my_text_layout_boundary_end(l);
        bool crossed_visual_line = false;
        size_t target_visual_col = 0;
        if (key == MY_KEY_LEFT && at_visual_start) {
          if (ta->wrap && vi > 0) {
            const my_visual_line_t* previous = ta_vline_at(ta, vi - 1);
            if (previous != NULL) {
              my_text_layout_t* previous_layout =
                  ta_layout_rtl(ta, previous);
              target_visual_col = previous_layout != NULL
                                      ? my_text_layout_boundary_end(
                                            previous_layout)
                                      : previous->len_cp;
              ta_move_to(ta, previous->phys,
                         previous->start_cp + target_visual_col, shift);
              crossed_visual_line = true;
              navigation_target = vi - 1u;
            }
          }
          if (!crossed_visual_line && ta->cursor_row > 0) {
            ta_move_to(ta, ta->cursor_row - 1,
                       ta_line_cp_len(ta, ta->cursor_row - 1), shift);
          }
        } else if (key == MY_KEY_RIGHT && at_visual_end) {
          if (ta->wrap && vi + 1 < ta_vline_count(ta)) {
            const my_visual_line_t* next = ta_vline_at(ta, vi + 1);
            if (next != NULL) {
              my_text_layout_t* next_layout = ta_layout_rtl(ta, next);
              target_visual_col = next_layout != NULL
                                      ? my_text_layout_boundary_home(next_layout)
                                      : 0;
              ta_move_to(ta, next->phys,
                         next->start_cp + target_visual_col, shift);
              crossed_visual_line = true;
              navigation_target = vi + 1u;
            }
          }
          if (!crossed_visual_line &&
              ta->cursor_row + 1 < ta_line_count(ta)) {
            ta_move_to(ta, ta->cursor_row + 1, 0, shift);
          }
        } else {
          size_t nb =
              key == MY_KEY_LEFT ? my_text_layout_boundary_left(l, col_in)
                                 : my_text_layout_boundary_right(l, col_in);
          ta_move_to(ta, ta->cursor_row, vl->start_cp + nb, shift);
        }
        if (!shift) {
          if (crossed_visual_line) {
            ta->goal_col = target_visual_col;
          } else {
            /* goal column tracks the VISUAL boundary index (identity for
             * pure LTR, so the legacy semantics are unchanged) */
            ta->goal_col = my_text_layout_visual_of_logical(
                l, ta->cursor_col - vl->start_cp);
          }
        }
        if (ta->wrap && track_navigation) {
          ta->navigation_visual_index = navigation_target;
          ta->navigation_row = ta->cursor_row;
          ta->navigation_col = ta->cursor_col;
          ta->navigation_valid = true;
        }
        return MY_RET_OK;
      }
      if (key == MY_KEY_LEFT) {
        if (ta->cursor_col > 0) {
          ta_move_to(ta, ta->cursor_row, ta->cursor_col - 1, shift);
        } else if (ta->cursor_row > 0) {
          ta_move_to(ta, ta->cursor_row - 1,
                     ta_line_cp_len(ta, ta->cursor_row - 1), shift);
        }
      } else {
        if (ta->cursor_col < ta_line_cp_len(ta, ta->cursor_row)) {
          ta_move_to(ta, ta->cursor_row, ta->cursor_col + 1, shift);
        } else if (ta->cursor_row + 1 < ta_line_count(ta)) {
          ta_move_to(ta, ta->cursor_row + 1, 0, shift);
        }
      }
      if (!shift) {
        ta->goal_col = ta->cursor_col;
      }
      return MY_RET_OK;
    }
    case MY_KEY_UP:
    case MY_KEY_DOWN: {
      /* goal column = visual boundary index (identity for LTR). With an
       * RTL target line the column goes through the mapping (M12a). */
      size_t civ = 0, vi;
      const my_visual_line_t* v = NULL;
      if (ta->wrap) {
        vi = ta_vline_of_pos(ta, ta->cursor_row, ta->cursor_col, &civ);
        if (key == MY_KEY_UP && vi > 0) {
          v = ta_vline_at(ta, vi - 1);
        } else if (key == MY_KEY_DOWN && vi + 1 < ta_vline_count(ta)) {
          v = ta_vline_at(ta, vi + 1);
        }
      } else {
        size_t current = ta_visible_index_of_row(ta, ta->cursor_row);
        if (key == MY_KEY_UP && current > 0) {
          v = ta_vline_at(ta, current - 1);
        } else if (key == MY_KEY_DOWN && current + 1 < ta_vline_count(ta)) {
          v = ta_vline_at(ta, current + 1);
        }
      }
      if (v != NULL) {
        my_text_layout_t* l = ta_layout_rtl(ta, v);
        size_t nc = ta->goal_col < v->len_cp ? ta->goal_col : v->len_cp;
        if (l != NULL) {
          nc = my_text_layout_logical_at_visual(l, nc);
          if (nc > v->len_cp) {
            nc = v->len_cp;
          }
        }
        ta_move_to(ta, v->phys, v->start_cp + nc, shift);
      }
      return MY_RET_OK;
    }
    case MY_KEY_HOME:
    case MY_KEY_END:
      if (ctrl) {
        if (key == MY_KEY_HOME) {
          ta_move_to(ta, 0, 0, shift);
        } else {
          ta_move_to(ta, ta_line_count(ta) - 1,
                     ta_line_cp_len(ta, ta_line_count(ta) - 1), shift);
        }
      } else {
        /* visual line start/end (wrap semantics documented); with RTL
         * the visual edge maps to a logical boundary inside the line */
        size_t civ = 0, vi = ta->wrap
                                 ? ta_vline_of_pos(ta, ta->cursor_row,
                                                   ta->cursor_col, &civ)
                                 : ta->cursor_row;
        const my_visual_line_t* v = ta_vline_at(ta, vi);
        my_text_layout_t* l = ta_layout_rtl(ta, v);
        size_t col;
        if (l != NULL) {
          col = v->start_cp + (key == MY_KEY_HOME
                                   ? my_text_layout_boundary_home(l)
                                   : my_text_layout_boundary_end(l));
        } else {
          col = key == MY_KEY_HOME ? v->start_cp
                                   : v->start_cp + v->len_cp;
        }
        ta_move_to(ta, v->phys, col, shift);
      }
      if (!shift) {
        ta->goal_col = ta->cursor_col;
      }
      return MY_RET_OK;
    case MY_KEY_PAGE_DOWN:
    case MY_KEY_PAGE_UP: {
      int32_t visible = (((my_widget_t*)ta)->rect.h - 2 * TA_PAD_Y) /
                        ta_line_height(ta);
      if (visible < 1) {
        visible = 1;
      }
      if (ta->wrap) {
        size_t civ = 0;
        size_t current =
            ta_vline_of_pos(ta, ta->cursor_row, ta->cursor_col, &civ);
        size_t count = ta_vline_count(ta);
        size_t amount = (size_t)visible;
        size_t target = current;
        const my_visual_line_t* v;

        if (count == 0) {
          return MY_RET_OK;
        }
        if (key == MY_KEY_PAGE_DOWN) {
          target = amount >= count - current ? count - 1 : current + amount;
        } else if (current > amount) {
          target = current - amount;
        } else {
          target = 0;
        }
        v = ta_vline_at(ta, target);
        if (v != NULL) {
          my_text_layout_t* l = ta_layout_rtl(ta, v);
          size_t col = ta->goal_col < v->len_cp ? ta->goal_col : v->len_cp;
          if (l != NULL) {
            col = my_text_layout_logical_at_visual(l, col);
            if (col > v->len_cp) {
              col = v->len_cp;
            }
          }
          ta_move_to(ta, v->phys, v->start_cp + col, shift);
        }
      } else {
        size_t current = ta_visible_index_of_row(ta, ta->cursor_row);
        size_t target = key == MY_KEY_PAGE_DOWN
                            ? current + (size_t)visible
                            : current > (size_t)visible
                                ? current - (size_t)visible
                                : 0;
        size_t row = ta_visible_row_at(ta, target < ta_vline_count(ta)
                                                ? target
                                                : ta_vline_count(ta) - 1);
        ta_move_to(ta, row, ta->goal_col, shift);
      }
      return MY_RET_OK;
    }
    case MY_KEY_BACKSPACE: {
      size_t r0, c0, r1, c1;
      if (ta_sel(ta, &r0, &c0, &r1, &c1)) {
        user_delete_range(ta, ta_offset_of(ta, r0, c0),
                          ta_offset_of(ta, r1, c1));
      } else {
        size_t off = ta_offset_of(ta, ta->cursor_row, ta->cursor_col);
        if (off > 0) {
          /* previous codepoint boundary (skip continuation bytes) */
          size_t prev = off - 1;
          while (prev > 0 && (ta->text[prev] & 0xC0) == 0x80) {
            prev--;
          }
          user_delete_range(ta, prev, off);
        }
      }
      return MY_RET_OK;
    }
    case MY_KEY_DELETE: {
      size_t r0, c0, r1, c1;
      if (ta_sel(ta, &r0, &c0, &r1, &c1)) {
        user_delete_range(ta, ta_offset_of(ta, r0, c0),
                          ta_offset_of(ta, r1, c1));
      } else {
        size_t off = ta_offset_of(ta, ta->cursor_row, ta->cursor_col);
        if (off < ta->text_len) {
          user_delete_range(ta, off, off + my_str_utf8_char_len(ta->text + off));
        }
      }
      return MY_RET_OK;
    }
    case MY_KEY_RETURN:
      user_insert(ta, "\n", 1, 1);
      return MY_RET_OK;
    default:
      break;
  }
  if (key >= 32 && key <= 126 && !ctrl) {
    char ch[2] = {(char)key, '\0'};
    user_insert(ta, ch, 1, 1);
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

/* ---------------- RTL mapping (M12a): per visual line segment ---------
 * Wrap breaking stays in logical order; drawing, cursor, clicks and
 * selection use the visual mapping. Dirty suffixes are processed as one
 * paragraph so hard-line boundaries remain explicit without per-line setup.
 */

/** @brief Fresh NUL-terminated text of a visual line (caller frees). */
static bool ta_vline_slice_bounds(const my_text_area_t* ta,
                                  const my_visual_line_t* vl, size_t* start,
                                  size_t* end) {
  size_t line_start;
  if (ta == NULL || vl == NULL || start == NULL || end == NULL ||
      vl->phys >= ta_line_count(ta)) {
    return false;
  }
  line_start = ta_line_start(ta, vl->phys);
  if (line_start > ta->text_len || vl->start_byte > ta->text_len - line_start)
    return false;
  *start = line_start + vl->start_byte;
  if (vl->len_bytes > ta->text_len - *start) return false;
  *end = *start + vl->len_bytes;
  return true;
}

static char* ta_vline_text(my_text_area_t* ta, const my_visual_line_t* vl) {
  size_t start;
  size_t end;
  char* s;
  if (!ta_vline_slice_bounds(ta, vl, &start, &end)) return NULL;
  if (end <= start) {
    return NULL;
  }
  s = (char*)my_mem_alloc(ta->allocator, end - start + 1);
  if (s != NULL) {
    memcpy(s, ta->text + start, end - start);
    s[end - start] = '\0';
  }
  return s;
}

static bool ta_paint_text_reserve(my_text_area_t* ta, size_t required) {
  size_t capacity;
  char* grown;
  if (required == SIZE_MAX) return false;
  if (required <= ta->paint_text_cap) return true;
  capacity = ta->paint_text_cap == 0 ? 64 : ta->paint_text_cap;
  while (capacity < required) {
    if (capacity > (size_t)-1 / 2) {
      capacity = required;
      break;
    }
    capacity *= 2;
  }
  grown = (char*)my_mem_realloc(ta->allocator, ta->paint_text, capacity);
  if (grown == NULL) return false;
  ta->paint_text = grown;
  ta->paint_text_cap = capacity;
  return true;
}

static char* ta_paint_vline_text(my_text_area_t* ta,
                                 const my_visual_line_t* vl) {
  size_t start;
  size_t end;
  size_t len;
  if (!ta_vline_slice_bounds(ta, vl, &start, &end)) return NULL;
  if (end <= start) {
    ta->paint_text_len = 0;
    return NULL;
  }
  len = end - start;
  if (!ta_paint_text_reserve(ta, len + 1)) return NULL;
  memcpy(ta->paint_text, ta->text + start, len);
  ta->paint_text[len] = '\0';
  ta->paint_text_len = len;
  return ta->paint_text;
}

/** @brief Cached layout of a visual line's text when it needs bidi. */
static my_text_layout_t* ta_layout_rtl(my_text_area_t* ta,
                                       const my_visual_line_t* vl) {
  my_text_area_rtl_cache_entry_t* entry;
  my_text_area_rtl_cache_entry_t* victim;
  uint64_t tick;
  size_t i;
  size_t start;
  size_t end;
  size_t length;
  my_text_layout_t* layout;
  for (i = 0; i < MY_TEXT_AREA_RTL_CACHE_CAPACITY; i++) {
    entry = &ta->rtl_cache[i];
    if (entry->layout != NULL && entry->phys == vl->phys &&
        entry->start_byte == vl->start_byte &&
        entry->len_bytes == vl->len_bytes &&
        entry->text_revision == ta->text_revision && entry->font == ta->font &&
        entry->font_size == ta->font_size &&
        entry->shaping_revision == ta->shaping_revision) {
      entry->last_used = ta_rtl_cache_next_tick(ta);
      ta_rtl_cache_mirror(ta, entry);
      return entry->layout;
    }
  }
  if (!ta_vline_slice_bounds(ta, vl, &start, &end)) return NULL;
  length = end - start;
  if (!my_text_layout_may_need_bidi_n(ta->text + start, length)) return NULL;
  layout = my_text_layout_process_n(ta->allocator, ta->text + start, length);
  if (layout == NULL) return NULL;
  victim = NULL;
  for (i = 0; i < MY_TEXT_AREA_RTL_CACHE_CAPACITY; i++) {
    entry = &ta->rtl_cache[i];
    if (entry->layout == NULL) {
      victim = entry;
      break;
    }
    if (victim == NULL || entry->last_used < victim->last_used) {
      victim = entry;
    }
  }
  my_text_layout_destroy(victim->layout);
  memset(victim, 0, sizeof(*victim));
  victim->layout = layout;
  victim->phys = vl->phys;
  victim->start_byte = vl->start_byte;
  victim->len_bytes = vl->len_bytes;
  victim->text_revision = ta->text_revision;
  victim->shaping_revision = ta->shaping_revision;
  victim->font = ta->font;
  victim->font_size = ta->font_size;
  tick = ta_rtl_cache_next_tick(ta);
  victim->last_used = tick;
  ta_rtl_cache_mirror(ta, victim);
  return layout;
}

/* ---------------- events ---------------- */

static my_ret_t ta_on_event_impl(my_widget_t* widget,
                                 const my_event_t* event) {
  my_text_area_t* ta = (my_text_area_t*)widget;
  switch (event->type) {
    case MY_EVENT_POINTER_DOWN: {
      int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
      int32_t line_h = ta_line_height(ta);
      size_t row;
      const my_visual_line_t* vl;
      my_text_layout_t* l;
      size_t col;
      my_widget_global_to_local(widget, &lx, &ly);
      {
        int64_t content_y = (int64_t)ly - TA_PAD_Y + ta->scroll_y;
        int64_t candidate_row;
        size_t visible_count = ta_vline_count(ta);
        candidate_row = content_y > 0 ? content_y / line_h : 0;
        if (candidate_row <= 0 || visible_count == 0) {
          row = 0;
        } else if ((uint64_t)candidate_row >= (uint64_t)visible_count) {
          row = visible_count - 1;
        } else {
          row = (size_t)candidate_row;
        }
      }
      vl = ta_vline_at(ta, row); /* row is a VISUAL index (wrap-aware) */
      l = ta_layout_rtl(ta, vl);
      if (l != NULL) {
        /* RTL (M12a): visual hit-test inside the line */
        col = vl->start_cp + my_text_layout_logical_at_x_ex(
                                  l, ta->font, ta->font_size,
                                  lx - ta_content_left_value(ta) +
                                      ta->scroll_x, &ta->shaping_params);
      } else {
        if (lx < ta_content_left_value(ta)) {
          lx = ta_content_left_value(ta);
        }
        col = ta_line_col_at_x(
            ta, vl->phys,
            lx - ta_content_left_value(ta) + ta->scroll_x +
                (ta->wrap ? ta_line_boundary_x(ta, vl->phys, vl->start_cp)
                          : 0));
        if (col > vl->start_cp + vl->len_cp) {
          col = vl->start_cp + vl->len_cp;
        }
      }
      ta_move_to(ta, vl->phys, col, false);
      ta->goal_col = ta->cursor_col;
      return MY_RET_OK;
    }
    case MY_EVENT_IME_PREEDIT:
      return ta_on_ime_preedit(ta, event);
    case MY_EVENT_IME_COMMIT:
      return ta_on_ime_commit(ta, event);
    case MY_EVENT_IME_DELETE_SURROUNDING:
      return ta_on_ime_delete_surrounding(ta, event);
    case MY_EVENT_KEY_DOWN:
      if (!ta->focused) {
        return MY_RET_FAIL;
      }
      return ta_on_key(ta, event);
    default:
      return MY_RET_FAIL;
  }
}

static my_ret_t ta_on_event(my_widget_t* widget, const my_event_t* event) {
  my_widget_t* held = my_widget_ref(widget);
  my_ret_t result = ta_on_event_impl(widget, event);
  my_widget_unref(held);
  return result;
}

/* ---------------- paint ---------------- */

static void ta_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_text_area_t* ta = (my_text_area_t*)widget;
  (void)ta_syntax_ensure_cache(ta);
  if (ta->syntax_cache != NULL && ta->syntax_line_budget > 0) {
    (void)my_syntax_cache_ensure(ta->syntax_cache, ta->syntax_line_budget);
  }
  /* M24b: deliberately NOT my_widget_current_state(): the focused border
   * borrows the HOVER style slot (same convention as my_edit). */
  uint32_t bg = my_widget_style_get_color(
      widget, widget->enable ? MY_STATE_NORMAL : MY_STATE_DISABLED, MY_STYLE_BG_COLOR,
      0xFFFFFFFFu);
  uint32_t border = my_widget_style_get_color(
      widget, ta->focused ? MY_STATE_HOVER : MY_STATE_NORMAL, MY_STYLE_BORDER_COLOR,
      0x9E9E9EFFu);
  uint32_t fg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_FG_COLOR,
                                          0x212121FFu);
  int32_t line_h = ta->font != NULL
                       ? my_font_line_height(ta->font, ta->font_size)
                       : ta->font_size;
  size_t sel_r0 = 0, sel_c0 = 0, sel_r1 = 0, sel_c1 = 0;
  bool has_sel;

  if (line_h <= 0) {
    line_h = ta->font_size > 0 ? ta->font_size : 16;
  }
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(border));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});

  my_vgcanvas_save(vg);
  my_vgcanvas_clip_rect(vg, &(my_rectf_t){TA_PAD_X, TA_PAD_Y,
                                          (float)(widget->rect.w - 2 * TA_PAD_X),
                                          (float)(widget->rect.h -
                                                  2 * TA_PAD_Y)});

  has_sel = ta_sel(ta, &sel_r0, &sel_c0, &sel_r1, &sel_c1);

  if ((ta->text == NULL || ta->text_len == 0) && ta->hint != NULL &&
      !ta->focused) {
    my_vgcanvas_set_fill_color(vg, my_color_rgb(150, 150, 150));
    ta_draw_text(ta, vg, ta->hint, (float)ta_content_left_value(ta),
                 TA_PAD_Y);
  }

  {
    /* iterate VISUAL lines (wrap on: wrapped segments; off: = physical) */
    size_t vcount = ta_vline_count(ta), vi;
    size_t vfirst = (size_t)(ta->scroll_y / line_h);
    size_t vlast = ta_sat_size_add(
        ta_sat_size_add(vfirst, (size_t)(widget->rect.h / line_h)), 1u);
    if (vlast >= vcount && vcount > 0) {
      vlast = vcount - 1;
    }
    for (vi = vfirst; vi <= vlast && vi < vcount; vi++) {
      const my_visual_line_t* vl = ta_vline_at(ta, vi);
      size_t start;
      size_t end;
      if (!ta_vline_slice_bounds(ta, vl, &start, &end)) continue;
      size_t len = end > start ? end - start : 0;
      int32_t ty = ta_sat_i64((int64_t)TA_PAD_Y +
                              (int64_t)vi * line_h - ta->scroll_y);
      if (ta->line_numbers && (vi == vfirst ||
                               ta_vline_at(ta, vi - 1)->phys != vl->phys)) {
        char number[32];
        int32_t number_width = 0;
        int32_t content_left = ta_content_left_value(ta);
        snprintf(number, sizeof(number), "%zu", vl->phys + 1);
        if (ta->font != NULL) {
          my_vgcanvas_measure_text(vg, number, &number_width, NULL);
        } else {
          number_width = ta_sat_size_mul(strlen(number), TA_CELL_W);
        }
        my_vgcanvas_set_fill_color(vg, my_color_rgb(130, 130, 130));
        ta_draw_text(
            ta, vg, number,
            (float)(content_left - TA_LINE_NUMBER_GAP - number_width),
            (float)ty);
      }
      if (len > 0) {
        char* line = ta_paint_vline_text(ta, vl);
        if (line != NULL) {
          int32_t inner_w = ta_inner_width_i32(ta);
          int32_t lw = 0;
          int32_t base_x = ta_content_left_value(ta) - ta->scroll_x;
          int32_t delta = 0;
          bool justify = false;
          my_text_layout_t* line_layout = NULL;
          int nseps = 0;
          /* alignment (M11d): measure the segment, shift its base x */
          if (ta->font != NULL) {
            my_vgcanvas_measure_text(vg, line, &lw, NULL);
          } else {
            lw = ta_sat_size_mul(vl->len_cp, TA_CELL_W);
          }
          nseps = ta_justify_space_count(line, len);
          if (my_text_layout_may_need_bidi(line) &&
              (ta->align == MY_TEXT_ALIGN_LEFT || has_sel ||
               (ta->syntax_cache != NULL &&
                my_syntax_cache_line_ready(ta->syntax_cache, vl->phys)))) {
            line_layout = ta_layout_rtl(ta, vl);
          }
          if (line_layout != NULL) {
            lw = my_text_layout_visual_boundary_x_ex(
                line_layout, ta->font, ta->font_size, line_layout->len,
                &ta->shaping_params);
          }
          if (ta->align == MY_TEXT_ALIGN_CENTER) {
            base_x += (inner_w - lw) / 2;
          } else if (ta->align == MY_TEXT_ALIGN_RIGHT) {
            base_x += inner_w - lw;
          } else if (ta->align == MY_TEXT_ALIGN_JUSTIFY && ta->wrap &&
                     inner_w > lw) {
            /* stretch word spacing: only visual lines that are NOT the
             * last segment of their physical line */
            bool phys_continues =
                vi + 1 < vcount && ta_vline_at(ta, vi + 1)->phys == vl->phys;
            justify = phys_continues && nseps > 0;
          } else if (line_layout != NULL) {
            /* M13b: the default (LEFT) follows the paragraph direction:
             * an RTL line is right-aligned unless align was set to
             * CENTER/RIGHT/JUSTIFY explicitly */
            if (line_layout->rtl_base) {
              base_x += inner_w - lw;
            }
          }
          /* selection/cursor shift with the line for CENTER/RIGHT
           * (delta); justified boundaries use the stretched word spacing. */
          delta = justify ? 0 :
              base_x - (ta_content_left_value(ta) - ta->scroll_x);
          if (has_sel && vl->phys >= sel_r0 && vl->phys <= sel_r1) {
            size_t c0 = vl->phys == sel_r0 ? sel_c0 : 0;
            size_t c1 = vl->phys == sel_r1
                            ? sel_c1
                            : vl->start_cp + vl->len_cp + (vi + 1 < vcount ? 1 : 0);
            size_t s0 = c0 > vl->start_cp ? c0 : vl->start_cp;
            size_t s1 = c1 < vl->start_cp + vl->len_cp
                            ? c1
                            : vl->start_cp + vl->len_cp;
            if (s1 > s0) {
              /* RTL (M12a): the contiguous logical selection may show as
               * several visual segments at run boundaries */
              my_vgcanvas_set_fill_color(vg, my_color_rgb(130, 170, 230));
              if (line_layout != NULL) {
                my_rectf_t rects[4];
                size_t n = justify
                               ? ta_layout_justify_rects(
                                     ta, line_layout, s0 - vl->start_cp,
                                     s1 - vl->start_cp, rects, 4,
                                     (size_t)nseps, lw, inner_w)
                               : my_text_layout_visual_rects_ex(
                                     line_layout, ta->font, ta->font_size,
                                     s0 - vl->start_cp, s1 - vl->start_cp,
                                     rects, 4, &ta->shaping_params);
                size_t k;
                for (k = 0; k < n && k < 4; k++) {
                  my_vgcanvas_fill_rect(
                      vg, &(my_rectf_t){(float)(ta_content_left_value(ta) +
                                                    delta +
                                                    (int32_t)rects[k].x -
                                                    ta->scroll_x),
                                        (float)ty, rects[k].w,
                                        (float)line_h});
                }
              } else {
                int32_t sx0 = ta_sat_size_mul(s0 - vl->start_cp, TA_CELL_W);
                int32_t sx1 = ta_sat_size_mul(s1 - vl->start_cp, TA_CELL_W);
                if (justify) {
                  sx0 = ta_justify_boundary_x(
                      ta, line, s0 - vl->start_cp, (size_t)nseps, lw,
                      inner_w);
                  sx1 = ta_justify_boundary_x(
                      ta, line, s1 - vl->start_cp, (size_t)nseps, lw,
                      inner_w);
                } else if (ta->font != NULL) {
                  sx0 = ta_line_boundary_x(ta, vl->phys, s0);
                  sx1 = ta_line_boundary_x(ta, vl->phys, s1);
                  sx0 -= ta_line_boundary_x(ta, vl->phys, vl->start_cp);
                  sx1 -= ta_line_boundary_x(ta, vl->phys, vl->start_cp);
                }
                my_vgcanvas_fill_rect(
                    vg, &(my_rectf_t){(float)(ta_content_left_value(ta) +
                                                  delta + sx0 - ta->scroll_x),
                                      (float)ty, (float)(sx1 - sx0),
                                      (float)line_h});
              }
            }
          }
          my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
          if (justify && line_layout != NULL) {
            ta_draw_justify_layout(ta, vg, line_layout, (float)base_x,
                                   (float)ty, (size_t)nseps, lw, inner_w);
          } else if (justify) {
            /* draw word by word, stretching each separating space */
            float x = (float)base_x;
            float space_extra = (float)(inner_w - lw) / (float)nseps;
            float space_w = (float)TA_CELL_W;
            char* p = line;
            if (ta->font != NULL) {
              int32_t spw = 0;
              my_vgcanvas_measure_text(vg, " ", &spw, NULL);
              space_w = (float)spw;
            }
            while (*p != '\0') {
              char* wstart = p;
              size_t word_count = 0u;
              size_t wlen;
              while (*p != '\0') {
                const char* next = p;
                uint32_t cp = my_utf8_next(&next);
                if (my_line_break_is_breaking_space(cp)) break;
                p = (char*)next;
                word_count++;
              }
              wlen = (size_t)(p - wstart);
              if (wlen > 0) {
                char separator = *p;
                int32_t ww = 0;
                *p = '\0';
                ta_draw_text(ta, vg, wstart, x, (float)ty);
                if (ta->font != NULL) {
                  my_vgcanvas_measure_text(vg, wstart, &ww, NULL);
                } else {
                  ww = ta_sat_size_mul(word_count, TA_CELL_W);
                }
                x += (float)ww;
                *p = separator;
              }
              while (*p != '\0') {
                const char* next = p;
                uint32_t cp = my_utf8_next(&next);
                if (!my_line_break_is_breaking_space(cp)) break;
                x += space_w + space_extra;
                p = (char*)next;
              }
            }
          } else {
            if (!ta_draw_syntax_line(ta, vg, vl, line, (float)base_x, ty, fg,
                                     line_layout)) {
              ta_draw_text(ta, vg, line, (float)base_x, (float)ty);
            }
          }
        }
      }
    }
  }

  /* cursor + IME composing text (M13a) */
  if (ta->focused && (ta->cursor_visible || ta->ime_preedit != NULL)) {
    size_t civ = 0, cvi = ta->wrap
                              ? ta_vline_of_pos(ta, ta->cursor_row,
                                                ta->cursor_col, &civ)
                              : ta->cursor_row;
    const my_visual_line_t* cv = ta_vline_at(ta, cvi);
    char* ctext = ta_paint_vline_text(ta, cv);
    int32_t cx = ta_content_left_value(ta) - ta->scroll_x;
    int32_t cy = ta_sat_i64((int64_t)TA_PAD_Y +
                            (int64_t)(ta->wrap ? cvi : ta->cursor_row) *
                                line_h -
                            ta->scroll_y);
    if (ctext != NULL) {
      int32_t inner_w = ta_inner_width_i32(ta);
      int32_t lw = 0;
      size_t col_in = ta->cursor_col - cv->start_cp;
      int nseps = 0;
      bool justify = false;
      my_text_layout_t* cursor_layout = ta_layout_rtl(ta, cv);
      /* same base as the text line (scroll + align), then the mapped
       * visual x for RTL, cell math otherwise (M12a) */
      if (ta->font != NULL) {
        my_vgcanvas_measure_text(vg, ctext, &lw, NULL);
      } else {
        lw = ta_sat_size_mul(cv->len_cp, TA_CELL_W);
      }
      nseps = ta_justify_space_count(ctext, strlen(ctext));
      if (ta->align == MY_TEXT_ALIGN_CENTER) {
        cx += (inner_w - lw) / 2;
      } else if (ta->align == MY_TEXT_ALIGN_RIGHT) {
        cx += inner_w - lw;
      } else if (ta->align == MY_TEXT_ALIGN_JUSTIFY && ta->wrap &&
                 inner_w > lw && nseps > 0 && cvi + 1 < ta_vline_count(ta) &&
                 ta_vline_at(ta, cvi + 1)->phys == cv->phys) {
        justify = true;
      } else if (cursor_layout != NULL) {
        /* M13b: default follows paragraph direction (RTL -> right) */
        if (cursor_layout->rtl_base) {
          cx += inner_w - lw;
        }
      }
      if (cursor_layout != NULL) {
        cx += my_text_layout_visual_x_ex(
            cursor_layout, ta->font, ta->font_size, col_in,
            &ta->shaping_params);
      } else if (justify) {
        cx = ta_sat_add(cx, ta_justify_boundary_x(
                                ta, ctext, col_in, (size_t)nseps, lw,
                                inner_w));
      } else {
        if (ta->wrap) {
          cx = ta_sat_add(
              cx, ta_sat_i64(
                      (int64_t)ta_line_boundary_x(
                          ta, cv->phys, ta_sat_size_add(cv->start_cp, col_in)) -
                      ta_line_boundary_x(ta, cv->phys, cv->start_cp)));
        } else {
          cx = ta_sat_add(cx,
                          ta_line_boundary_x(ta, cv->phys, ta->cursor_col));
        }
      }
    } else {
      cx = ta_sat_add(cx, ta_sat_size_mul(
                              ta->wrap ? civ : ta->cursor_col, TA_CELL_W));
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
    if (ta->cursor_visible) {
      my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)cx, (float)cy, 1,
                                              (float)line_h});
    }
    /* IME composing text: underlined at the cursor, NOT part of the
     * document (no undo, no "changed"); does not blink with the caret */
    if (ta->ime_preedit != NULL) {
      int32_t pw = 0;
      ta_draw_text(ta, vg, ta->ime_preedit, (float)cx, (float)cy);
      if (ta->font != NULL) {
        my_vgcanvas_measure_text(vg, ta->ime_preedit, &pw, NULL);
      } else {
        pw = ta_sat_size_mul(my_str_utf8_strlen(ta->ime_preedit), TA_CELL_W);
      }
      if (pw > 0) {
        my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)cx,
                                                (float)ta_sat_i64(
                                                    (int64_t)cy + line_h - 1),
                                                (float)pw, 1.0f});
      }
    }
  }
  my_vgcanvas_restore(vg);
}

static const my_widget_vtable_t s_ta_vtable = {ta_on_paint, ta_on_event, NULL, NULL};

bool my_text_area_is_instance(const my_widget_t* widget) {
  return widget != NULL && widget->vtable == &s_ta_vtable;
}

/* ---------------- focus / blink / lifecycle ---------------- */

static my_ret_t ta_blink_tick(void* ctx) {
  my_text_area_t* ta = (my_text_area_t*)ctx;
  my_widget_t* held = my_widget_ref((my_widget_t*)ta);
  ta->cursor_visible = !ta->cursor_visible;
  my_widget_invalidate((my_widget_t*)ta, NULL);
  my_widget_unref(held);
  return MY_RET_OK;
}

static my_ret_t ta_paste_tick(void* ctx) {
  my_text_area_t* ta = (my_text_area_t*)ctx;
  my_widget_t* held = my_widget_ref((my_widget_t*)ta);
  if (ta->focused && ta_paste(ta) == MY_RET_PENDING) {
    my_widget_unref(held);
    return MY_RET_OK;
  }
  ta->paste_timer_id = 0;
  ta->paste_loop = NULL;
  my_widget_unref(held);
  return MY_RET_FAIL;
}

static void ta_on_focus(void* ctx, const char* event, void* data) {
  my_text_area_t* ta = (my_text_area_t*)ctx;
  my_pal_main_loop_t* loop;
  (void)event;
  (void)data;
  ta->focused = true;
  ta->cursor_visible = true;
  ta_set_ime_enabled(ta, true);
  ta_update_ime_spot(ta);
  loop = my_window_loop_of_widget((my_widget_t*)ta);
  if (loop != NULL && ta->blink_timer_id == 0) {
    ta->blink_timer_id =
        my_pal_main_loop_add_timer(loop, ta_blink_tick, ta, 500);
    ta->blink_loop = ta->blink_timer_id > 0 ? loop : NULL;
  }
  my_widget_invalidate((my_widget_t*)ta, NULL);
}

static void ta_on_blur(void* ctx, const char* event, void* data) {
  my_text_area_t* ta = (my_text_area_t*)ctx;
  (void)event;
  (void)data;
  if (ta->undo_shared != NULL) {
    my_undo_manager_break_batch(ta->undo_shared);
  } else {
    my_undo_stack_break_batch(ta->undo);
  }
  if (ta->ime_preedit != NULL) {
    my_mem_free(ta->allocator, ta->ime_preedit);
    ta->ime_preedit = NULL;
  }
  ta->focused = false;
  ta_set_ime_enabled(ta, false);
  ta->cursor_visible = true;
  if (ta->blink_timer_id > 0 && ta->blink_loop != NULL) {
    my_pal_main_loop_remove_timer(ta->blink_loop, ta->blink_timer_id);
    ta->blink_timer_id = 0;
    ta->blink_loop = NULL;
  }
  if (ta->paste_timer_id > 0 && ta->paste_loop != NULL) {
    my_pal_main_loop_remove_timer(ta->paste_loop, ta->paste_timer_id);
    ta->paste_timer_id = 0;
    ta->paste_loop = NULL;
  }
  my_widget_invalidate((my_widget_t*)ta, NULL);
}

static void ta_destroy_chain(my_object_t* obj) {
  my_text_area_t* ta = (my_text_area_t*)obj;
  if (ta->scroll_bar != NULL && ta->scroll_bar_listener_id != 0u) {
    (void)my_widget_off(ta->scroll_bar, ta->scroll_bar_listener_id);
    ta->scroll_bar_listener_id = 0u;
  }
  if (ta->scroll_bar != NULL) {
    my_widget_unref(ta->scroll_bar);
    ta->scroll_bar = NULL;
  }
  if (ta->blink_timer_id > 0 && ta->blink_loop != NULL) {
    my_pal_main_loop_remove_timer(ta->blink_loop, ta->blink_timer_id);
  }
  if (ta->paste_timer_id > 0 && ta->paste_loop != NULL) {
    my_pal_main_loop_remove_timer(ta->paste_loop, ta->paste_timer_id);
  }
  if (ta->undo_shared != NULL) {
    my_undo_manager_unregister(ta->undo_shared, ta);
  }
  my_undo_stack_destroy(ta->undo);
  my_mem_free(ta->allocator, ta->ime_preedit);
  ta_clear_folds(ta);
  ta_vlines_destroy_array(ta, ta->vlines);
  ta_syntax_destroy(ta);
  my_mem_free(ta->allocator, ta->paint_text);
  ta_rtl_cache_clear(ta);
  my_mem_free(ta->allocator, ta->geometry_boundaries);
  my_mem_free(ta->allocator, ta->shaping_language);
  my_mem_free(ta->allocator, ta->shaping_features);
  my_mem_free(ta->allocator, ta->vline_first_by_phys);
  my_darray_destroy(ta->line_offsets);
  my_mem_free(ta->allocator, ta->text);
  my_mem_free(ta->allocator, ta->hint);
  my_widget_destroy((my_widget_t*)ta);
  my_object_destroy(obj);
}

my_widget_t* my_text_area_create(const my_allocator_t* allocator) {
  my_text_area_t* ta =
      (my_text_area_t*)my_mem_calloc(allocator, 1, sizeof(my_text_area_t));
  if (ta == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)ta, allocator, &s_ta_vtable,
                     "text_area") != MY_RET_OK) {
    my_mem_free(allocator, ta);
    return NULL;
  }
  ((my_object_t*)ta)->destroy = ta_destroy_chain;
  ta->allocator = allocator;
  ta->font_size = 16;
  ta->syntax_language = MY_SYNTAX_NONE;
  ta->syntax_line_budget = TA_SYNTAX_DEFAULT_LINE_BUDGET;
  ta->cursor_visible = true;
  ta->line_offsets = my_darray_create(allocator, 0);
  if (ta->line_offsets == NULL) {
    my_object_unref((my_object_t*)ta);
    return NULL;
  }
  ta_offsets_push(ta, 0);
  ta->visible_rows_dirty = false;
  ta->text = (char*)my_mem_calloc(allocator, 1, 1);
  if (ta->text == NULL) {
    my_object_unref((my_object_t*)ta);
    return NULL;
  }
  ta->text_cap = 1;
  ta->undo = my_undo_stack_create(allocator, 0);
  if (ta->undo == NULL) {
    my_object_unref((my_object_t*)ta);
    return NULL;
  }
  ((my_widget_t*)ta)->focusable = true;
  ((my_widget_t*)ta)->widget_type = "text_area";
  my_widget_on((my_widget_t*)ta, "focus", ta_on_focus, ta);
  my_widget_on((my_widget_t*)ta, "blur", ta_on_blur, ta);
  return (my_widget_t*)ta;
}

my_ret_t my_text_area_set_text(my_widget_t* area, const char* text) {
  my_text_area_t* ta = (my_text_area_t*)area;
  my_syntax_cache_t* replacement = NULL;
  my_syntax_cache_t* previous;
  my_ret_t syntax_status;
  size_t len;
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  len = text != NULL ? strlen(text) : 0;
  if (len == SIZE_MAX) return MY_RET_OOM;
  if (ta_syntax_active(ta)) {
    syntax_status = ta_syntax_prepare_document(ta, text, &replacement);
    if (syntax_status != MY_RET_OK) return syntax_status;
  }
  if (len + 1 > ta->text_cap) {
    size_t cap = ta->text_cap > 0 ? ta->text_cap : 1;
    while (cap < len + 1) {
      if (cap > SIZE_MAX / 2) {
        cap = len + 1;
        break;
      }
      cap *= 2;
    }
    {
      char* p = (char*)my_mem_realloc(ta->allocator, ta->text, cap);
      if (p == NULL) {
        my_syntax_cache_destroy(replacement);
        return MY_RET_OOM;
      }
      ta->text = p;
      ta->text_cap = cap;
    }
  }
  if (len > 0) {
    memcpy(ta->text, text, len);
  }
  /* Programmatic replacement is not undoable, but clear history only after
   * every fallible preparation step has succeeded. */
  if (ta->undo_shared != NULL) {
    my_undo_manager_clear_widget(ta->undo_shared, ta);
  } else if (ta->undo != NULL) {
    my_undo_stack_clear(ta->undo);
  }
  ta->text[len] = '\0';
  ta->text_len = len;
  ta_bump_text_revision(ta);
  ta_clear_folds(ta);
  ta_rebuild_from(ta, 0);
  previous = ta->syntax_cache;
  ta->syntax_cache = replacement;
  my_syntax_cache_destroy(previous);
  ta_cursor_to_offset(ta, len);
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

const char* my_text_area_get_text(my_widget_t* area) {
  my_text_area_t* ta = (my_text_area_t*)area;
  return !my_text_area_is_instance(area) || ta->text == NULL ? "" : ta->text;
}

my_ret_t my_text_area_set_hint(my_widget_t* area, const char* hint) {
  my_text_area_t* ta = (my_text_area_t*)area;
  char* copy;
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  copy = my_strdup(ta->allocator, hint);
  if (hint != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(ta->allocator, ta->hint);
  ta->hint = copy;
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

my_ret_t my_text_area_set_wrap(my_widget_t* area, bool wrap) {
  my_text_area_t* ta = (my_text_area_t*)area;
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (ta->wrap != wrap) {
    ta->wrap = wrap;
    ta->scroll_x = 0;
    ta_vlines_invalidate_from(ta, 0);
    ta->navigation_valid = false;
  }
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

my_ret_t my_text_area_set_line_numbers(my_widget_t* area, bool enabled) {
  my_text_area_t* ta = (my_text_area_t*)area;
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (ta->line_numbers != enabled) {
    ta->line_numbers = enabled;
    ta->scroll_x = 0;
    if (ta->wrap) {
      ta_vlines_invalidate_from(ta, 0);
    }
    my_widget_invalidate(area, NULL);
  }
  return MY_RET_OK;
}

bool my_text_area_line_numbers_enabled(const my_widget_t* area) {
  return my_text_area_is_instance(area) &&
         ((const my_text_area_t*)area)->line_numbers;
}

int32_t my_text_area_content_left(const my_widget_t* area) {
  if (!my_text_area_is_instance(area)) {
    return 0;
  }
  return ta_content_left_value((const my_text_area_t*)area);
}

my_ret_t my_text_area_set_folded_range(my_widget_t* area, size_t start_row,
                                       size_t end_row, bool folded) {
  my_text_area_t* ta = (my_text_area_t*)area;
  size_t i;
  if (!my_text_area_is_instance(area) || start_row >= end_row ||
      end_row >= ta_line_count(ta)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (ta->fold_ranges == NULL) {
    if (!folded) {
      return MY_RET_INVALID_PARAMS;
    }
    ta->fold_ranges = my_darray_create(ta->allocator, 0);
    if (ta->fold_ranges == NULL) {
      return MY_RET_OOM;
    }
  }
  for (i = 0; i < my_darray_size(ta->fold_ranges); i++) {
    my_text_fold_range_t* range =
        (my_text_fold_range_t*)my_darray_get(ta->fold_ranges, i);
    if (range == NULL) {
      continue;
    }
    if (range->start_row == start_row && range->end_row == end_row) {
      if (folded) {
        return MY_RET_OK;
      }
      my_mem_free(ta->allocator, range);
      my_darray_remove_at(ta->fold_ranges, i);
      ta_visible_rows_invalidate(ta);
      ta_vlines_invalidate_from(ta, 0);
      my_widget_invalidate(area, NULL);
      return MY_RET_OK;
    }
    if (folded && start_row <= range->end_row &&
        end_row >= range->start_row) {
      bool new_contains_old = start_row < range->start_row &&
                              end_row >= range->end_row;
      bool old_contains_new = range->start_row < start_row &&
                              range->end_row >= end_row;
      if (!new_contains_old && !old_contains_new) {
        return MY_RET_INVALID_PARAMS;
      }
    }
  }
  if (!folded) {
    return MY_RET_INVALID_PARAMS;
  }
  {
    my_text_fold_range_t* range =
        (my_text_fold_range_t*)my_mem_calloc(ta->allocator, 1, sizeof(*range));
    size_t insert_at = 0;
    if (range == NULL) {
      return MY_RET_OOM;
    }
    range->start_row = start_row;
    range->end_row = end_row;
    while (insert_at < my_darray_size(ta->fold_ranges)) {
      const my_text_fold_range_t* current =
          (const my_text_fold_range_t*)my_darray_get(ta->fold_ranges,
                                                     insert_at);
      if (current == NULL || start_row < current->start_row) {
        break;
      }
      insert_at++;
    }
    if (my_darray_push(ta->fold_ranges, range) != MY_RET_OK) {
      my_mem_free(ta->allocator, range);
      return MY_RET_OOM;
    }
    for (i = my_darray_size(ta->fold_ranges) - 1; i > insert_at; i--) {
      ta->fold_ranges->items[i] = ta->fold_ranges->items[i - 1];
    }
    ta->fold_ranges->items[insert_at] = range;
  }
  ta_visible_rows_invalidate(ta);
  ta_vlines_invalidate_from(ta, 0);
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

my_ret_t my_text_area_folds_to_yaml(const my_widget_t* area,
                                    const my_allocator_t* allocator,
                                    char** out_yaml) {
  const my_text_area_t* ta = (const my_text_area_t*)area;
  size_t i;
  size_t len = 0;
  char* yaml;
  if (!my_text_area_is_instance(area) || out_yaml == NULL)
    return MY_RET_INVALID_PARAMS;
  *out_yaml = NULL;
  if (ta->fold_ranges == NULL || my_darray_size(ta->fold_ranges) == 0) {
    yaml = (char*)my_mem_alloc(allocator, sizeof(TA_FOLD_STATE_HEADER));
    if (yaml == NULL) return MY_RET_OOM;
    memcpy(yaml, TA_FOLD_STATE_HEADER, sizeof(TA_FOLD_STATE_HEADER));
    *out_yaml = yaml;
    return MY_RET_OK;
  }
  if (my_darray_size(ta->fold_ranges) > TA_MAX_FOLD_RANGES) {
    return MY_RET_INVALID_PARAMS;
  }
  len = sizeof(TA_FOLD_STATE_HEADER) - 1;
  for (i = 0; i < my_darray_size(ta->fold_ranges); i++) {
    const my_text_fold_range_t* range =
        (const my_text_fold_range_t*)my_darray_get(ta->fold_ranges, i);
    int n = range == NULL ? -1 : snprintf(NULL, 0,
                                          "  - start: %zu\n    end: %zu\n",
                                          range->start_row, range->end_row);
    if (n < 0 || (size_t)n > TA_MAX_FOLD_STATE_BYTES - len) {
      return MY_RET_INVALID_PARAMS;
    }
    len += (size_t)n;
  }
  yaml = (char*)my_mem_alloc(allocator, len + 1);
  if (yaml == NULL) return MY_RET_OOM;
  memcpy(yaml, TA_FOLD_STATE_HEADER, sizeof(TA_FOLD_STATE_HEADER) - 1);
  len = sizeof(TA_FOLD_STATE_HEADER) - 1;
  for (i = 0; i < my_darray_size(ta->fold_ranges); i++) {
    const my_text_fold_range_t* range =
        (const my_text_fold_range_t*)my_darray_get(ta->fold_ranges, i);
    int n = snprintf(yaml + len, TA_MAX_FOLD_STATE_BYTES - len,
                     "  - start: %zu\n    end: %zu\n", range->start_row,
                     range->end_row);
    if (n < 0) {
      my_mem_free(allocator, yaml);
      return MY_RET_INVALID_PARAMS;
    }
    len += (size_t)n;
  }
  yaml[len] = '\0';
  *out_yaml = yaml;
  return MY_RET_OK;
}

my_ret_t my_text_area_folds_from_yaml(my_widget_t* area, const char* yaml) {
  my_text_area_t* ta = (my_text_area_t*)area;
  my_conf_node_t* root = NULL;
  my_conf_node_t* folds;
  my_conf_node_t* version;
  int64_t version_value;
  my_conf_error_t error;
  my_darray_t* candidate = NULL;
  size_t i;
  if (!my_text_area_is_instance(area) || yaml == NULL ||
      strlen(yaml) > TA_MAX_FOLD_STATE_BYTES) {
    return MY_RET_INVALID_PARAMS;
  }
  root = my_conf_parse_yaml(ta->allocator, yaml, strlen(yaml), &error);
  if (root == NULL || my_conf_type(root) != MY_CONF_OBJECT) goto invalid;
  if (my_conf_child_count(root) == 1 &&
      strcmp(my_conf_key(my_conf_child(root, 0)), "folds") == 0) {
    version = NULL;
  } else if (my_conf_child_count(root) == 2) {
    version = my_conf_get(root, "version");
    if (version == NULL || my_conf_type(version) != MY_CONF_INT64) goto invalid;
    version_value = my_conf_as_int64(version, -1);
    if (version_value != TA_FOLD_STATE_LEGACY_VERSION &&
        version_value != TA_FOLD_STATE_VERSION) goto invalid;
    if (strcmp(my_conf_key(my_conf_child(root, 0)), "version") != 0 &&
        strcmp(my_conf_key(my_conf_child(root, 0)), "folds") != 0) goto invalid;
    if (strcmp(my_conf_key(my_conf_child(root, 1)), "version") != 0 &&
        strcmp(my_conf_key(my_conf_child(root, 1)), "folds") != 0) goto invalid;
  } else {
    goto invalid;
  }
  folds = my_conf_get(root, "folds");
  if (folds == NULL || my_conf_type(folds) != MY_CONF_ARRAY ||
      my_conf_child_count(folds) > TA_MAX_FOLD_RANGES) goto invalid;
  candidate = my_darray_create(ta->allocator, 0);
  if (candidate == NULL) goto oom;
  for (i = 0; i < my_conf_child_count(folds); i++) {
    my_conf_node_t* item = my_conf_child(folds, i);
    my_conf_node_t* start_node;
    my_conf_node_t* end_node;
    int64_t start_value, end_value;
    if (item == NULL || my_conf_type(item) != MY_CONF_OBJECT ||
        my_conf_child_count(item) != 2) goto invalid_candidate;
    if (strcmp(my_conf_key(my_conf_child(item, 0)), "start") != 0 &&
        strcmp(my_conf_key(my_conf_child(item, 0)), "end") != 0) {
      goto invalid_candidate;
    }
    if (strcmp(my_conf_key(my_conf_child(item, 1)), "start") != 0 &&
        strcmp(my_conf_key(my_conf_child(item, 1)), "end") != 0) {
      goto invalid_candidate;
    }
    start_node = my_conf_get(item, "start");
    end_node = my_conf_get(item, "end");
    if (start_node == NULL || end_node == NULL ||
        my_conf_type(start_node) != MY_CONF_INT64 ||
        my_conf_type(end_node) != MY_CONF_INT64) goto invalid_candidate;
    start_value = my_conf_as_int64(start_node, -1);
    end_value = my_conf_as_int64(end_node, -1);
    if (start_value < 0 || end_value < 0 || start_value >= end_value ||
        (uint64_t)end_value >= ta_line_count(ta)) goto invalid_candidate;
    if (ta_fold_ranges_add_sorted(ta->allocator, candidate,
                                  (size_t)start_value, (size_t)end_value) !=
        MY_RET_OK) goto invalid_candidate;
  }
  my_conf_destroy(root);
  ta_fold_ranges_destroy(ta->allocator, ta->fold_ranges);
  ta->fold_ranges = candidate;
  my_darray_destroy(ta->visible_rows);
  ta->visible_rows = NULL;
  ta->visible_rows_dirty = true;
  ta_vlines_invalidate_from(ta, 0);
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;

invalid_candidate:
  ta_fold_ranges_destroy(ta->allocator, candidate);
invalid:
  my_conf_destroy(root);
  return MY_RET_INVALID_PARAMS;
oom:
  ta_fold_ranges_destroy(ta->allocator, candidate);
  my_conf_destroy(root);
  return MY_RET_OOM;
}

bool my_text_area_is_folded(const my_widget_t* area, size_t row) {
  const my_text_area_t* ta = (const my_text_area_t*)area;
  size_t i;
  if (!my_text_area_is_instance(area) || ta->fold_ranges == NULL) {
    return false;
  }
  for (i = 0; i < my_darray_size(ta->fold_ranges); i++) {
    const my_text_fold_range_t* range =
        (const my_text_fold_range_t*)my_darray_get(ta->fold_ranges, i);
    if (range == NULL || range->start_row > row) {
      break;
    }
    if (range->start_row == row) {
      return true;
    }
  }
  return false;
}

my_ret_t my_text_area_set_align(my_widget_t* area, my_text_align_t align) {
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_text_area_t*)area)->align = align;
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

my_ret_t my_text_area_set_syntax_enabled(my_widget_t* area, bool enabled) {
  my_text_area_t* ta = (my_text_area_t*)area;
  my_syntax_cache_t* cache = NULL;
  if (!my_text_area_is_instance(area)) return MY_RET_INVALID_PARAMS;
  if (!enabled) {
    ta->syntax_enabled = false;
    ta_syntax_destroy(ta);
    my_widget_invalidate(area, NULL);
    return MY_RET_OK;
  }
  ta->syntax_enabled = true;
  if (ta->syntax_language != MY_SYNTAX_NONE && ta->syntax_cache == NULL) {
    if (ta_syntax_prepare_document(ta, ta->text, &cache) != MY_RET_OK) {
      ta->syntax_enabled = false;
      return MY_RET_OOM;
    }
    ta->syntax_cache = cache;
  }
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

my_ret_t my_text_area_set_syntax_language(my_widget_t* area,
                                          my_syntax_language_t language) {
  my_text_area_t* ta = (my_text_area_t*)area;
  my_syntax_cache_t* cache = NULL;
  if (!my_text_area_is_instance(area) || language < MY_SYNTAX_NONE ||
      language > MY_SYNTAX_YAML) {
    return MY_RET_INVALID_PARAMS;
  }
  if (ta->syntax_language == language) return MY_RET_OK;
  if (ta->syntax_enabled && language != MY_SYNTAX_NONE) {
    my_syntax_language_t old = ta->syntax_language;
    ta->syntax_language = language;
    if (ta_syntax_prepare_document(ta, ta->text, &cache) != MY_RET_OK) {
      ta->syntax_language = old;
      return MY_RET_OOM;
    }
  }
  ta->syntax_language = language;
  ta_syntax_destroy(ta);
  ta->syntax_cache = cache;
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

my_ret_t my_text_area_set_syntax_line_budget(my_widget_t* area,
                                             size_t line_budget) {
  if (!my_text_area_is_instance(area)) return MY_RET_INVALID_PARAMS;
  ((my_text_area_t*)area)->syntax_line_budget = line_budget;
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

bool my_text_area_syntax_enabled(const my_widget_t* area) {
  return my_text_area_is_instance(area) &&
         ((const my_text_area_t*)area)->syntax_enabled;
}

bool my_text_area_syntax_line_ready(const my_widget_t* area, size_t row) {
  const my_text_area_t* ta = (const my_text_area_t*)area;
  return my_text_area_is_instance(area) && ta->syntax_cache != NULL &&
         my_syntax_cache_line_ready(ta->syntax_cache, row);
}

size_t my_text_area_visual_line_count(my_widget_t* area) {
  return my_text_area_is_instance(area)
             ? ta_vline_count((my_text_area_t*)area)
             : 0;
}

const my_visual_line_t* my_text_area_visual_line_at(my_widget_t* area,
                                                    size_t index) {
  if (!my_text_area_is_instance(area)) {
    return NULL;
  }
  if (index >= ta_vline_count((my_text_area_t*)area)) {
    return NULL;
  }
  return ta_vline_at((my_text_area_t*)area, index);
}

size_t my_text_area_visual_line_of_pos(my_widget_t* area, size_t row,
                                       size_t col, size_t* col_in_v) {
  size_t civ = 0;
  if (!my_text_area_is_instance(area)) {
    return 0;
  }
  return ta_vline_of_pos((my_text_area_t*)area, row, col,
                         col_in_v != NULL ? col_in_v : &civ);
}

my_ret_t my_text_area_set_undo_shared(my_widget_t* area, void* mgr) {  my_text_area_t* ta = (my_text_area_t*)area;
  my_undo_manager_t* next = (my_undo_manager_t*)mgr;
  my_ret_t result;
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (ta->undo_shared == next) {
    return MY_RET_OK;
  }
  if (next != NULL) {
    result = my_undo_manager_register(next, ta, ta_apply_undo_op);
    if (result != MY_RET_OK) {
      return result;
    }
  }
  if (ta->undo_shared != NULL) {
    /* leaving shared mode discards the widget's shared history
     * (documented): entries whose owner is unregistered cannot be
     * applied by a routed undo */
    my_undo_manager_clear_widget(ta->undo_shared, ta);
    my_undo_manager_unregister(ta->undo_shared, ta);
  }
  ta->undo_shared = next;
  return MY_RET_OK;
}

my_ret_t my_text_area_set_readonly(my_widget_t* area, bool readonly) {
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_text_area_t*)area)->readonly = readonly;
  return MY_RET_OK;
}

my_ret_t my_text_area_set_max_len(my_widget_t* area, size_t max_codepoints) {
  if (!my_text_area_is_instance(area)) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_text_area_t*)area)->max_len = max_codepoints;
  return MY_RET_OK;
}

static bool ta_shape_string_valid(const char* value, size_t max_bytes) {
  size_t i;
  if (value == NULL) return true;
  for (i = 0; i <= max_bytes; i++) {
    if (value[i] == '\0') return true;
  }
  return false;
}

static bool ta_shape_string_equal(const char* left, const char* right,
                                  size_t max_bytes) {
  if (left == NULL || right == NULL) return left == right;
  return ta_shape_string_valid(right, max_bytes) &&
         strcmp(left, right) == 0;
}

my_ret_t my_text_area_set_shaping_params(
    my_widget_t* area, const my_font_shape_params_t* params) {
  my_text_area_t* ta = (my_text_area_t*)area;
  my_font_shape_params_t effective = {false, 0u, NULL, NULL};
  char normalized_features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  char* language = NULL;
  char* features = NULL;
  if (!my_text_area_is_instance(area)) return MY_RET_INVALID_PARAMS;
  if (params != NULL) effective = *params;
  if (!my_font_shape_params_valid(&effective)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (effective.features != NULL &&
      !my_font_shape_features_normalize(effective.features,
                                        normalized_features,
                                        sizeof(normalized_features))) {
    return MY_RET_INVALID_PARAMS;
  }
  if (effective.features != NULL) {
    effective.features = normalized_features[0] != '\0'
                             ? normalized_features
                             : NULL;
  }
  if (ta->shaping_params.rtl == effective.rtl &&
      ta->shaping_params.script == effective.script &&
      ta_shape_string_equal(ta->shaping_params.language, effective.language,
                            MY_FONT_SHAPE_MAX_LANGUAGE_BYTES) &&
      ta_shape_string_equal(ta->shaping_params.features, effective.features,
                            MY_FONT_SHAPE_MAX_FEATURE_BYTES)) {
    return MY_RET_OK;
  }
  if (effective.language != NULL) {
    language = my_strdup(ta->allocator, effective.language);
  }
  if (effective.features != NULL) {
    features = my_strdup(ta->allocator, effective.features);
  }
  if ((effective.language != NULL && language == NULL) ||
      (effective.features != NULL && features == NULL)) {
    my_mem_free(ta->allocator, language);
    my_mem_free(ta->allocator, features);
    return MY_RET_OOM;
  }
  my_mem_free(ta->allocator, ta->shaping_language);
  my_mem_free(ta->allocator, ta->shaping_features);
  ta->shaping_language = language;
  ta->shaping_features = features;
  ta->shaping_params = effective;
  ta->shaping_params.language = ta->shaping_language;
  ta->shaping_params.features = ta->shaping_features;
  if (ta->shaping_revision == UINT64_MAX) {
    ta->shaping_revision = 1u;
  } else {
    ta->shaping_revision++;
  }
  ta_rtl_cache_clear(ta);
  ta_vlines_invalidate_from(ta, 0);
  ta->navigation_valid = false;
  my_widget_invalidate(area, NULL);
  return MY_RET_OK;
}

void my_text_area_set_font(my_widget_t* area, my_font_t* font, int32_t size) {
  my_text_area_t* ta = (my_text_area_t*)area;
  if (my_text_area_is_instance(area)) {
    if (font != NULL) {
      ta->font = font;
    }
    if (size > 0) {
      ta->font_size = size;
    }
    ta_rtl_cache_clear(ta);
    ta_vlines_invalidate_from(ta, 0);
    my_widget_invalidate(area, NULL);
  }
}

size_t my_text_area_line_count(my_widget_t* area) {
  return my_text_area_is_instance(area)
             ? ta_line_count((my_text_area_t*)area)
             : 0;
}
