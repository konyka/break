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

static my_text_paragraph_t* paragraph_process_n_break_profile_callback_ex(
    const my_allocator_t* allocator, const char* text, size_t text_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options,
    const my_line_break_profile_options_t* profile_options,
    const my_line_break_dictionary_profile_t* dictionary_profile);

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
    my_font_glyph_release(&glyph);
  }
  return MY_RET_OK;
}

static my_ret_t paragraph_build_segment(my_text_paragraph_t* paragraph,
                                        size_t* capacity, size_t start_byte,
                                        size_t end_byte, size_t start_cp,
                                        size_t count, my_font_t* font,
                                        int32_t size, int32_t max_width,
                                        const my_font_shape_params_t* shape_params,
                                        const my_line_break_options_t* break_options,
                                        const my_line_break_profile_options_t*
                                            profile_options,
                                        const my_line_break_dictionary_profile_t*
                                            dictionary_profile) {
  const char* segment = paragraph->text + start_byte;
  uint32_t* cps = NULL;
  size_t* offsets = NULL;
  float* widths = NULL;
  bool* blocked = NULL;
  bool* break_allowed = NULL;
  my_line_break_state_t break_state;
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
      count + 1 < count || count + 1 > SIZE_MAX / sizeof(bool) ||
      count > SIZE_MAX / sizeof(bool)) {
    return MY_RET_OOM;
  }
  cps = (uint32_t*)my_mem_alloc(paragraph->allocator, count * sizeof(uint32_t));
  offsets = (size_t*)my_mem_alloc(paragraph->allocator, count * sizeof(size_t));
  widths = (float*)my_mem_calloc(paragraph->allocator, count, sizeof(float));
  blocked = (bool*)my_mem_calloc(paragraph->allocator, count + 1, sizeof(bool));
  break_allowed = (bool*)my_mem_alloc(paragraph->allocator, count *
                                      sizeof(bool));
  if (cps == NULL || offsets == NULL || widths == NULL || blocked == NULL ||
      break_allowed == NULL) {
    ret = MY_RET_OOM;
    goto done;
  }
  for (i = 0; i < count; i++) {
    const char* p = segment + off;
    offsets[i] = off;
    cps[i] = my_utf8_next(&p);
    off += (size_t)(p - (segment + off));
  }
  my_line_break_state_init(&break_state);
  for (i = 0; i < count; i++) {
    break_allowed[i] = my_line_break_state_feed_with_lookahead(
        &break_state, cps[i], i + 1u < count ? cps[i + 1u] : 0u,
        i + 1u < count);
  }
  if (profile_options != NULL) {
    ret = my_line_break_apply_dictionary_profile(
        cps, count, break_allowed, profile_options, dictionary_profile);
  } else {
    ret = my_line_break_apply_dictionary_ex(cps, count, break_allowed,
                                            break_options, dictionary_profile);
  }
  if (ret != MY_RET_OK) goto done;
  {
    char saved_end = paragraph->text[end_byte];
    paragraph->text[end_byte] = '\0';
    ret = paragraph_measure(paragraph->allocator, segment, font, size, cps,
                            offsets, count, widths, blocked, shape_params);
    paragraph->text[end_byte] = saved_end;
  }
  if (ret != MY_RET_OK) goto done;

  if (max_width <= 0) {
    ret = paragraph_add_line(paragraph, capacity, start_byte, end_byte,
                             start_cp, count);
    goto done;
  }
  while (col < count) {
    float next_width = line_width + widths[col];
    if (col > line_start && !blocked[col] && break_allowed[col]) {
      last_break = col;
    }
    if (next_width > (float)max_width && col > line_start) {
      if (my_line_break_is_breaking_space(cps[col])) {
        line_width = next_width;
        col++;
        continue;
      }
      size_t break_at = last_break;
      if (break_at == (size_t)-1 && !blocked[col]) break_at = col;
      if (break_at != (size_t)-1 && break_at > line_start) {
        size_t next_start = break_at;
        size_t line_end = break_at;
        while (next_start < count &&
               my_line_break_is_breaking_space(cps[next_start])) {
          next_start++;
        }
        while (line_end > line_start &&
               my_line_break_is_breaking_space(cps[line_end - 1u])) {
          line_end--;
        }
        if (line_end == line_start) {
          line_end = break_at;
        }
        ret = paragraph_add_line(
            paragraph, capacity, start_byte + offsets[line_start],
            start_byte + offsets[line_end], start_cp + line_start,
            line_end - line_start);
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
  my_mem_free(paragraph->allocator, break_allowed);
  return ret;
}

my_text_paragraph_t* my_text_paragraph_process_ex(
    const my_allocator_t* allocator, const char* text, my_font_t* font,
    int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params) {
  size_t text_len;
  if (text == NULL || !paragraph_bounded_text_len(text, &text_len)) {
    return NULL;
  }
  return my_text_paragraph_process_n_ex(allocator, text, text_len, font, size,
                                        max_width, shape_params);
}

my_text_paragraph_t* my_text_paragraph_process_break_ex(
    const my_allocator_t* allocator, const char* text, my_font_t* font,
    int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options) {
  size_t text_len;
  if (text == NULL || !paragraph_bounded_text_len(text, &text_len)) {
    return NULL;
  }
  return my_text_paragraph_process_n_break_ex(
      allocator, text, text_len, font, size, max_width, shape_params,
      break_options);
}

my_text_paragraph_t* my_text_paragraph_process_break_profile_ex(
    const my_allocator_t* allocator, const char* text, my_font_t* font,
    int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options,
    const my_line_break_dictionary_profile_t* dictionary_profile) {
  size_t text_len;
  if (text == NULL || !paragraph_bounded_text_len(text, &text_len)) {
    return NULL;
  }
  return my_text_paragraph_process_n_break_profile_ex(
      allocator, text, text_len, font, size, max_width, shape_params,
      break_options, dictionary_profile);
}

my_text_paragraph_t* my_text_paragraph_process_n_ex(
    const my_allocator_t* allocator, const char* text, size_t text_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params) {
  return my_text_paragraph_process_n_break_ex(
      allocator, text, text_len, font, size, max_width, shape_params, NULL);
}

my_text_paragraph_t* my_text_paragraph_process_n_break_ex(
    const my_allocator_t* allocator, const char* text, size_t text_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options) {
  return my_text_paragraph_process_n_break_profile_ex(
      allocator, text, text_len, font, size, max_width, shape_params,
      break_options, NULL);
}

my_text_paragraph_t* my_text_paragraph_process_n_break_profile_ex(
    const my_allocator_t* allocator, const char* text, size_t text_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options,
    const my_line_break_dictionary_profile_t* dictionary_profile) {
  return paragraph_process_n_break_profile_callback_ex(
      allocator, text, text_len, font, size, max_width, shape_params,
      break_options, NULL, dictionary_profile);
}

static my_text_paragraph_t* paragraph_process_n_break_profile_callback_ex(
    const my_allocator_t* allocator, const char* text, size_t text_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_options_t* break_options,
    const my_line_break_profile_options_t* profile_options,
    const my_line_break_dictionary_profile_t* dictionary_profile) {
  my_text_paragraph_t* paragraph;
  my_font_shape_params_t default_shape_params = {false, 0u, NULL, NULL};
  my_font_shape_params_t owned_shape_params;
  const my_font_shape_params_t* effective_shape_params;
  char normalized_features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  size_t capacity = 0, start_byte = 0, start_cp = 0, cp_count = 0;
  size_t language_len;
  size_t features_len;
  const char* p;
  if (dictionary_profile != NULL &&
      !my_line_break_dictionary_profile_valid(dictionary_profile)) {
    return NULL;
  }
  if (profile_options != NULL &&
      (dictionary_profile == NULL || profile_options->dictionary == NULL ||
       profile_options->max_codepoints == 0u ||
       profile_options->max_codepoints >
           MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS)) {
    return NULL;
  }
  effective_shape_params = shape_params != NULL ? shape_params
                                                : &default_shape_params;
  owned_shape_params = *effective_shape_params;
  if (owned_shape_params.features != NULL &&
      !my_font_shape_features_normalize(owned_shape_params.features,
                                        normalized_features,
                                        sizeof(normalized_features))) {
    return NULL;
  }
  if (owned_shape_params.features != NULL) {
    owned_shape_params.features = normalized_features[0] != '\0'
                                      ? normalized_features
                                      : NULL;
  }
  effective_shape_params = &owned_shape_params;
  if (text == NULL || text_len > MY_TEXT_PARAGRAPH_MAX_BYTES ||
      memchr(text, '\0', text_len) != NULL || (font != NULL && size <= 0) ||
      !my_font_shape_params_valid(effective_shape_params) ||
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
  paragraph->text_len = text_len;
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
  if (text_len == SIZE_MAX) {
    my_text_paragraph_destroy(paragraph);
    return NULL;
  }
  paragraph->text = (char*)my_mem_alloc(allocator, text_len + 1u);
  if (paragraph->text == NULL) {
    my_text_paragraph_destroy(paragraph);
    return NULL;
  }
  if (text_len > 0u) {
    memcpy(paragraph->text, text, text_len);
  }
  paragraph->text[text_len] = '\0';
  p = paragraph->text;
  while ((size_t)(p - paragraph->text) <= text_len) {
    size_t current_offset = (size_t)(p - paragraph->text);
    size_t hard_break_len = current_offset < text_len
                                ? my_line_break_hard_break_len(
                                      p, text_len - current_offset)
                                : 0u;
    if (current_offset == text_len || hard_break_len > 0u) {
      if (paragraph_build_segment(paragraph, &capacity, start_byte,
                                  current_offset, start_cp,
                                  cp_count, font, size, max_width,
                                  effective_shape_params, break_options,
                                  profile_options,
                                  dictionary_profile) != MY_RET_OK) {
        my_text_paragraph_destroy(paragraph);
        return NULL;
      }
      if (current_offset == text_len) break;
      p += hard_break_len;
      start_byte = current_offset + hard_break_len;
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

my_text_paragraph_t* my_text_paragraph_process_n_break_profile_callback_ex(
    const my_allocator_t* allocator, const char* text, size_t text_len,
    my_font_t* font, int32_t size, int32_t max_width,
    const my_font_shape_params_t* shape_params,
    const my_line_break_profile_options_t* profile_options,
    const my_line_break_dictionary_profile_t* dictionary_profile) {
  return paragraph_process_n_break_profile_callback_ex(
      allocator, text, text_len, font, size, max_width, shape_params, NULL,
      profile_options, dictionary_profile);
}

my_text_paragraph_t* my_text_paragraph_process(const my_allocator_t* allocator,
                                               const char* text,
                                               my_font_t* font, int32_t size,
                                               int32_t max_width) {
  return my_text_paragraph_process_ex(allocator, text, font, size, max_width,
                                      NULL);
}

my_text_paragraph_t* my_text_paragraph_process_n(
    const my_allocator_t* allocator, const char* text, size_t byte_len,
    my_font_t* font, int32_t size, int32_t max_width) {
  return my_text_paragraph_process_n_ex(allocator, text, byte_len, font, size,
                                        max_width, NULL);
}

void my_text_paragraph_destroy(my_text_paragraph_t* paragraph) {
  const my_allocator_t* allocator;
  size_t i;
  if (paragraph == NULL) return;
  allocator = paragraph->allocator;
  for (i = 0u; i < MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY; i++) {
    my_text_layout_destroy(paragraph->line_layout_cache[i].layout);
  }
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

static uint64_t paragraph_line_layout_next_tick(my_text_paragraph_t* paragraph) {
  size_t i;
  if (paragraph->line_layout_cache_tick == UINT64_MAX) {
    paragraph->line_layout_cache_tick = 0u;
    for (i = 0u; i < MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY; i++) {
      paragraph->line_layout_cache[i].last_used = 0u;
    }
  }
  paragraph->line_layout_cache_tick++;
  return paragraph->line_layout_cache_tick;
}

const my_text_layout_t* my_text_paragraph_line_layout(
    const my_text_paragraph_t* paragraph, size_t index) {
  my_text_paragraph_t* mutable_paragraph = (my_text_paragraph_t*)paragraph;
  const my_text_paragraph_line_t* line;
  my_text_paragraph_line_layout_cache_entry_t* entry;
  my_text_paragraph_line_layout_cache_entry_t* victim = NULL;
  size_t length;
  size_t i;
  my_text_layout_t* layout;

  if (mutable_paragraph == NULL || index >= mutable_paragraph->line_count) {
    return NULL;
  }
  line = &mutable_paragraph->lines[index];
  if (line->start_byte > mutable_paragraph->text_len ||
      line->end_byte < line->start_byte ||
      line->end_byte > mutable_paragraph->text_len) {
    return NULL;
  }
  for (i = 0u; i < MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY; i++) {
    entry = &mutable_paragraph->line_layout_cache[i];
    if (entry->layout != NULL && entry->line_index == index) {
      entry->last_used = paragraph_line_layout_next_tick(mutable_paragraph);
      return entry->layout;
    }
  }
  length = line->end_byte - line->start_byte;
  if (length == SIZE_MAX) return NULL;
  layout = my_text_layout_process_n(mutable_paragraph->allocator,
                                    mutable_paragraph->text + line->start_byte,
                                    length);
  if (layout == NULL) return NULL;
  for (i = 0u; i < MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY; i++) {
    entry = &mutable_paragraph->line_layout_cache[i];
    if (entry->layout == NULL) {
      victim = entry;
      break;
    }
    if (victim == NULL || entry->last_used < victim->last_used) {
      victim = entry;
    }
  }
  my_text_layout_destroy(victim->layout);
  victim->layout = layout;
  victim->line_index = index;
  victim->last_used = paragraph_line_layout_next_tick(mutable_paragraph);
  return layout;
}

size_t my_text_paragraph_line_visual_of_logical(
    const my_text_paragraph_t* paragraph, size_t index,
    size_t logical_boundary) {
  const my_text_paragraph_line_t* line;
  const my_text_layout_t* layout;
  size_t local_boundary;

  line = my_text_paragraph_line_at(paragraph, index);
  layout = my_text_paragraph_line_layout(paragraph, index);
  if (line == NULL || layout == NULL) {
    return 0u;
  }
  if (logical_boundary <= line->start_cp) {
    local_boundary = 0u;
  } else if (logical_boundary - line->start_cp >= line->cp_count) {
    local_boundary = line->cp_count;
  } else {
    local_boundary = logical_boundary - line->start_cp;
  }
  return my_text_layout_visual_of_logical(layout, local_boundary);
}

size_t my_text_paragraph_line_logical_at_visual(
    const my_text_paragraph_t* paragraph, size_t index,
    size_t visual_boundary) {
  const my_text_paragraph_line_t* line;
  const my_text_layout_t* layout;
  size_t local_boundary;

  line = my_text_paragraph_line_at(paragraph, index);
  layout = my_text_paragraph_line_layout(paragraph, index);
  if (line == NULL || layout == NULL) {
    return 0u;
  }
  local_boundary = my_text_layout_logical_at_visual(layout, visual_boundary);
  if (line->start_cp > SIZE_MAX - local_boundary) {
    return SIZE_MAX;
  }
  return line->start_cp + local_boundary;
}
