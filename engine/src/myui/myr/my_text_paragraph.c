/**
 * @file my_text_paragraph.c
 * @brief Shaping-aware bounded paragraph model.
 */
#include "myr/my_text_paragraph.h"

#include <string.h>

#include "myc/my_str.h"
#include "myr/my_line_break.h"
#include "myr/my_text_layout.h"

static my_ret_t paragraph_add_line(my_text_paragraph_t* paragraph,
                                   size_t* capacity, size_t start_byte,
                                   size_t end_byte, size_t start_cp,
                                   size_t cp_count) {
  if (paragraph->line_count == *capacity) {
    size_t next = *capacity > 0 ? *capacity * 2 : 8;
    if (next < *capacity || next > SIZE_MAX / sizeof(*paragraph->lines)) {
      return MY_RET_OOM;
    }
    my_text_paragraph_line_t* lines = (my_text_paragraph_line_t*)my_mem_realloc(
        paragraph->allocator, paragraph->lines,
        next * sizeof(my_text_paragraph_line_t));
    if (lines == NULL) return MY_RET_OOM;
    paragraph->lines = lines;
    *capacity = next;
  }
  paragraph->lines[paragraph->line_count++] =
      (my_text_paragraph_line_t){start_byte, end_byte, start_cp, cp_count};
  return MY_RET_OK;
}

static bool paragraph_bounded_text_len(const char* text, size_t* out_len) {
  size_t len = 0;
  while (len <= MY_TEXT_PARAGRAPH_MAX_BYTES && text[len] != '\0') {
    len++;
  }
  if (len > MY_TEXT_PARAGRAPH_MAX_BYTES) {
    return false;
  }
  *out_len = len;
  return true;
}

static bool paragraph_param_len(const char* value, size_t limit,
                                size_t* out_len) {
  size_t length;
  if (value == NULL) {
    *out_len = 0u;
    return true;
  }
  for (length = 0u; length <= limit; ++length) {
    if (value[length] == '\0') {
      *out_len = length;
      return true;
    }
  }
  return false;
}

static char* paragraph_copy_param(const my_allocator_t* allocator,
                                  const char* value, size_t length) {
  char* copy;
  if (value == NULL) return NULL;
  if (length == SIZE_MAX) return NULL;
  copy = (char*)my_mem_alloc(allocator, length + 1u);
  if (copy == NULL) return NULL;
  memcpy(copy, value, length + 1u);
  return copy;
}

static size_t paragraph_cp_index(const size_t* offsets, size_t count,
                                 size_t byte) {
  size_t lo = 0, hi = count;
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    if (offsets[mid] < byte) {
      lo = mid + 1;
    } else if (offsets[mid] > byte) {
      hi = mid;
    } else {
      return mid;
    }
  }
  return count;
}

static void paragraph_destroy_arrays(const my_allocator_t* allocator,
                                     uint32_t* cps, size_t* offsets,
                                     float* widths, bool* blocked) {
  my_mem_free(allocator, cps);
  my_mem_free(allocator, offsets);
  my_mem_free(allocator, widths);
  my_mem_free(allocator, blocked);
}

static my_ret_t paragraph_measure(const my_allocator_t* allocator,
                                  const char* text, my_font_t* font,
                                  int32_t size, uint32_t* cps, size_t* offsets,
                                  size_t count, float* widths, bool* blocked,
                                  const my_font_shape_params_t* shape_params) {
  my_font_shape_result_t shaped = {0};
  my_text_layout_t* layout = NULL;
  my_ret_t shape_ret;
  size_t i;
  if (font == NULL) {
    for (i = 0; i < count; i++) widths[i] = 8.0f;
    return MY_RET_OK;
  }
  if (my_text_layout_may_need_bidi(text)) {
    layout = my_text_layout_process(allocator, text);
    if (layout == NULL) return MY_RET_OOM;
    shape_ret = my_text_layout_shape_ex(layout, text, font, size, shape_params,
                                        allocator, &shaped);
    my_text_layout_destroy(layout);
  } else {
    shape_ret = my_font_shape_ex(font, text, size, shape_params, allocator,
                                 &shaped);
  }
  if (shape_ret == MY_RET_OK) {
    size_t glyph;
    size_t text_len = strlen(text);
    for (glyph = 0; glyph < shaped.count; glyph++) {
      size_t cp;
      if (shaped.glyphs[glyph].cluster >= text_len) {
        my_font_shape_destroy(&shaped);
        return MY_RET_FAIL;
      }
      cp = paragraph_cp_index(offsets, count,
                              shaped.glyphs[glyph].cluster);
      if (cp >= count) {
        my_font_shape_destroy(&shaped);
        return MY_RET_FAIL;
      }
      widths[cp] +=
          (float)shaped.glyphs[glyph].advance_x_26_6 / 64.0f;
      blocked[cp] = true;
    }
    for (i = 1; i < count; i++) {
      blocked[i] = !blocked[i];
    }
    my_font_shape_destroy(&shaped);
    return MY_RET_OK;
  }
  if (shape_ret == MY_RET_OOM) return shape_ret;
  if (shape_ret != MY_RET_NOT_SUPPORTED) return shape_ret;
  if (font->vtable == NULL || font->vtable->get_glyph == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  for (i = 0; i < count; i++) {
    my_glyph_t glyph = {0};
    if (my_font_get_glyph(font, cps[i], size, &glyph) == MY_RET_OK &&
        glyph.advance > 0) {
      widths[i] = (float)glyph.advance;
    } else {
      widths[i] = 0.0f;
    }
  }
  return MY_RET_OK;
}

static my_ret_t paragraph_build_segment(my_text_paragraph_t* paragraph,
                                        size_t* capacity, size_t start_byte,
                                        size_t end_byte, size_t start_cp,
                                        size_t count, my_font_t* font,
                                        int32_t size, int32_t max_width,
                                        const my_font_shape_params_t* shape_params) {
  const char* segment = paragraph->text + start_byte;
  uint32_t* cps = NULL;
  size_t* offsets = NULL;
  float* widths = NULL;
  bool* blocked = NULL;
  size_t i, off = 0, line_start = 0, col = 0;
  float line_width = 0.0f;
  size_t last_break = (size_t)-1;
  my_ret_t ret = MY_RET_OK;

  if (count == 0) {
    return paragraph_add_line(paragraph, capacity, start_byte, end_byte,
                              start_cp, 0);
  }
  if (count > SIZE_MAX / sizeof(uint32_t) ||
      count > SIZE_MAX / sizeof(size_t) ||
      count > SIZE_MAX / sizeof(float) ||
      count + 1 < count || count + 1 > SIZE_MAX / sizeof(bool)) {
    return MY_RET_OOM;
  }
  cps = (uint32_t*)my_mem_alloc(paragraph->allocator, count * sizeof(uint32_t));
  offsets = (size_t*)my_mem_alloc(paragraph->allocator, count * sizeof(size_t));
  widths = (float*)my_mem_calloc(paragraph->allocator, count, sizeof(float));
  blocked = (bool*)my_mem_calloc(paragraph->allocator, count + 1, sizeof(bool));
  if (cps == NULL || offsets == NULL || widths == NULL || blocked == NULL) {
    ret = MY_RET_OOM;
    goto done;
  }
  for (i = 0; i < count; i++) {
    const char* p = segment + off;
    offsets[i] = off;
    cps[i] = my_utf8_next(&p);
    off += (size_t)(p - (segment + off));
  }
  ret = paragraph_measure(paragraph->allocator, segment, font, size, cps,
                          offsets, count, widths, blocked, shape_params);
  if (ret != MY_RET_OK) goto done;

  if (max_width <= 0) {
    ret = paragraph_add_line(paragraph, capacity, start_byte, end_byte,
                             start_cp, count);
    goto done;
  }
  while (col < count) {
    float next_width = line_width + widths[col];
    if (col > line_start && !blocked[col] &&
        my_line_break_allowed(cps[col - 1], cps[col])) {
      last_break = col;
    }
    if (next_width > (float)max_width && col > line_start) {
      size_t break_at = last_break;
      if (break_at == (size_t)-1 && !blocked[col]) break_at = col;
      if (break_at != (size_t)-1 && break_at > line_start) {
        size_t next_start = break_at;
        while (next_start < count && cps[next_start] == ' ') next_start++;
        ret = paragraph_add_line(
            paragraph, capacity, start_byte + offsets[line_start],
            start_byte + offsets[break_at], start_cp + line_start,
            break_at - line_start);
        if (ret != MY_RET_OK) goto done;
        line_start = next_start;
        col = next_start;
        line_width = 0.0f;
        last_break = (size_t)-1;
        continue;
      }
    }
    line_width = next_width;
    col++;
  }
  if (line_start < count || paragraph->line_count == 0) {
    ret = paragraph_add_line(
        paragraph, capacity, start_byte + offsets[line_start], end_byte,
        start_cp + line_start, count - line_start);
  }

done:
  paragraph_destroy_arrays(paragraph->allocator, cps, offsets, widths, blocked);
  return ret;
}

my_text_paragraph_t* my_text_paragraph_process_ex(
    const my_allocator_t* allocator, const char* text, my_font_t* font,
    int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params) {
  my_text_paragraph_t* paragraph;
  my_font_shape_params_t default_shape_params = {false, 0u, NULL, NULL};
  const my_font_shape_params_t* effective_shape_params =
      shape_params != NULL ? shape_params : &default_shape_params;
  size_t capacity = 0, start_byte = 0, start_cp = 0, cp_count = 0;
  size_t text_len;
  size_t language_len;
  size_t features_len;
  const char* p;
  if (text == NULL || (font != NULL && size <= 0) ||
      !paragraph_bounded_text_len(text, &text_len) ||
      !paragraph_param_len(effective_shape_params->language,
                           MY_FONT_SHAPE_MAX_LANGUAGE_BYTES, &language_len) ||
      !paragraph_param_len(effective_shape_params->features,
                           MY_FONT_SHAPE_MAX_FEATURE_BYTES, &features_len)) {
    return NULL;
  }
  paragraph = (my_text_paragraph_t*)my_mem_calloc(
      allocator, 1, sizeof(my_text_paragraph_t));
  if (paragraph == NULL) return NULL;
  paragraph->allocator = allocator;
  paragraph->shape_params = *effective_shape_params;
  if (effective_shape_params->language != NULL) {
    paragraph->shape_language = paragraph_copy_param(
        allocator, effective_shape_params->language, language_len);
    if (paragraph->shape_language == NULL) {
      my_text_paragraph_destroy(paragraph);
      return NULL;
    }
    paragraph->shape_params.language = paragraph->shape_language;
  }
  if (effective_shape_params->features != NULL) {
    paragraph->shape_features = paragraph_copy_param(
        allocator, effective_shape_params->features, features_len);
    if (paragraph->shape_features == NULL) {
      my_text_paragraph_destroy(paragraph);
      return NULL;
    }
    paragraph->shape_params.features = paragraph->shape_features;
  }
  paragraph->text = (char*)my_mem_alloc(allocator, text_len + 1u);
  if (paragraph->text == NULL) {
    my_text_paragraph_destroy(paragraph);
    return NULL;
  }
  memcpy(paragraph->text, text, text_len + 1u);
  p = paragraph->text;
  while (true) {
    if (*p == '\0' || *p == '\n') {
      if (paragraph_build_segment(paragraph, &capacity, start_byte,
                                  (size_t)(p - paragraph->text), start_cp,
                                  cp_count, font, size, max_width,
                                  effective_shape_params) != MY_RET_OK) {
        my_text_paragraph_destroy(paragraph);
        return NULL;
      }
      if (*p == '\0') break;
      p++;
      start_byte = (size_t)(p - paragraph->text);
      start_cp += cp_count;
      paragraph->logical_len = start_cp;
      cp_count = 0;
      continue;
    }
    {
      const char* next = p;
      (void)my_utf8_next(&next);
      p = next;
      cp_count++;
    }
  }
  paragraph->logical_len = start_cp + cp_count;
  return paragraph;
}

my_text_paragraph_t* my_text_paragraph_process(const my_allocator_t* allocator,
                                               const char* text,
                                               my_font_t* font, int32_t size,
                                               int32_t max_width) {
  return my_text_paragraph_process_ex(allocator, text, font, size, max_width,
                                      NULL);
}

void my_text_paragraph_destroy(my_text_paragraph_t* paragraph) {
  const my_allocator_t* allocator;
  if (paragraph == NULL) return;
  allocator = paragraph->allocator;
  my_mem_free(allocator, paragraph->shape_features);
  my_mem_free(allocator, paragraph->shape_language);
  my_mem_free(allocator, paragraph->text);
  my_mem_free(allocator, paragraph->lines);
  my_mem_free(allocator, paragraph);
}

const my_text_paragraph_line_t* my_text_paragraph_line_at(
    const my_text_paragraph_t* paragraph, size_t index) {
  if (paragraph == NULL || index >= paragraph->line_count) return NULL;
  return &paragraph->lines[index];
}

const my_font_shape_params_t* my_text_paragraph_shape_params(
    const my_text_paragraph_t* paragraph) {
  return paragraph != NULL ? &paragraph->shape_params : NULL;
}
