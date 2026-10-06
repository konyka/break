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

typedef struct paragraph_wrap_config_t {
  my_font_t* font;
  int32_t size;
  int32_t max_width;
  const my_font_shape_params_t* shape_params;
  const my_line_break_options_t* break_options;
  const my_line_break_profile_options_t* profile_options;
  const my_line_break_dictionary_profile_t* dictionary_profile;
} paragraph_wrap_config_t;

/* Wrap [range_start, range_end) of paragraph->text into lines, splitting at
 * hard breaks. Hard-break detection sees the full remaining text so an
 * atomic CRLF straddling range_end is recognized; such a break ends the
 * range after the current segment without emitting a trailing empty segment
 * (its '\n' belongs to the caller-owned suffix). When
 * skip_leading_hard_break is set, a hard break at range_start (a CRLF whose
 * '\r' belongs to the caller-owned prefix) is skipped without emitting an
 * empty segment. *out_cp_count receives the emitted codepoint count (hard
 * breaks excluded, matching the logical_len convention). */
static my_ret_t paragraph_wrap_range(my_text_paragraph_t* paragraph,
                                     size_t* capacity, size_t range_start,
                                     size_t range_end,
                                     bool skip_leading_hard_break,
                                     size_t cp_base,
                                     const paragraph_wrap_config_t* config,
                                     size_t* out_cp_count) {
  size_t pos = range_start;
  size_t start_byte = range_start;
  size_t start_cp = cp_base;
  size_t cp_count = 0u;
  while (pos <= range_end) {
    size_t hard_break_len =
        pos < paragraph->text_len
            ? my_line_break_hard_break_len(paragraph->text + pos,
                                           paragraph->text_len - pos)
            : 0u;
    if (pos == range_end || hard_break_len > 0u) {
      my_ret_t ret;
      bool emit;
      if (hard_break_len > 0u && pos == range_start &&
          skip_leading_hard_break) {
        pos += hard_break_len;
        start_byte = pos;
        continue;
      }
      /* An empty trailing emit is only a real segment when the range ends
       * at the text end or the suffix itself starts with a hard break;
       * otherwise the next segment is suffix-owned and emitting here would
       * duplicate its line. */
      emit = start_byte < pos || range_end == paragraph->text_len ||
             hard_break_len > 0u;
      if (emit) {
        ret = paragraph_build_segment(
            paragraph, capacity, start_byte, pos, start_cp, cp_count,
            config->font, config->size, config->max_width,
            config->shape_params, config->break_options,
            config->profile_options, config->dictionary_profile);
        if (ret != MY_RET_OK) return ret;
      }
      start_cp += cp_count;
      cp_count = 0u;
      if (pos == range_end ||
          hard_break_len > range_end - pos /* straddles the suffix */) {
        break;
      }
      pos += hard_break_len;
      start_byte = pos;
      continue;
    }
    {
      const char* next = paragraph->text + pos;
      (void)my_utf8_next(&next);
      pos = (size_t)(next - paragraph->text);
      cp_count++;
    }
  }
  *out_cp_count = start_cp + cp_count - cp_base;
  return MY_RET_OK;
}

/* Count codepoints in [start, end), skipping hard breaks (the logical_len
 * convention). */
static size_t paragraph_count_cps(const char* text, size_t start, size_t end) {
  size_t pos = start;
  size_t count = 0u;
  while (pos < end) {
    size_t hard_break_len =
        my_line_break_hard_break_len(text + pos, end - pos);
    if (hard_break_len > 0u) {
      pos += hard_break_len;
      continue;
    }
    {
      const char* next = text + pos;
      (void)my_utf8_next(&next);
      pos = (size_t)(next - text);
      count++;
    }
  }
  return count;
}

/* Locate the minimal byte region of the OLD text whose segments an edit
 * [s, e) can affect. Segments wrap independently, so untouched segments
 * keep their lines. The edit range is expanded over any hard-break bytes it
 * intersects (deleting one side of a break merges/splits neighbors); for a
 * pure insertion (s == e) a hard break STRICTLY CONTAINING the insertion
 * point (splitting an atomic CRLF) counts as intersected. The region then
 * covers every segment touching the closed range [rs, re]. */
static void paragraph_edit_region(const char* text, size_t text_len, size_t s,
                                  size_t e, size_t* out_start,
                                  size_t* out_end, size_t* out_edit_end) {
  size_t rs = s;
  size_t re = e;
  size_t pos = 0u;
  size_t seg_start = 0u;
  size_t region_start = text_len;
  size_t region_end = 0u;
  bool any = false;
  while (pos < text_len) {
    size_t hard_break_len =
        my_line_break_hard_break_len(text + pos, text_len - pos);
    if (hard_break_len > 0u) {
      if (pos + hard_break_len > s && pos < e) {
        if (pos < rs) rs = pos;
        if (pos + hard_break_len > re) re = pos + hard_break_len;
      }
      pos += hard_break_len;
      continue;
    }
    {
      const char* next = text + pos;
      (void)my_utf8_next(&next);
      pos = (size_t)(next - text);
    }
  }
  pos = 0u;
  while (pos <= text_len) {
    size_t hard_break_len =
        pos < text_len ? my_line_break_hard_break_len(text + pos,
                                                      text_len - pos)
                       : 0u;
    if (pos == text_len || hard_break_len > 0u) {
      if (seg_start <= re && pos >= rs) {
        if (!any || seg_start < region_start) region_start = seg_start;
        if (!any || pos > region_end) region_end = pos;
        any = true;
      }
      if (pos == text_len) break;
      pos += hard_break_len;
      seg_start = pos;
      continue;
    }
    {
      const char* next = text + pos;
      (void)my_utf8_next(&next);
      pos = (size_t)(next - text);
    }
  }
  if (!any) {
    region_start = 0u;
    region_end = text_len;
  }
  *out_start = region_start;
  *out_end = region_end;
  *out_edit_end = re;
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
  size_t capacity = 0;
  size_t language_len;
  size_t features_len;
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
  paragraph->font = font;
  paragraph->size = size;
  paragraph->max_width = max_width;
  if (break_options != NULL) {
    paragraph->break_options = *break_options;
    paragraph->break_options_valid = true;
  }
  if (profile_options != NULL) {
    paragraph->profile_options = *profile_options;
    paragraph->profile_options_valid = true;
  }
  if (dictionary_profile != NULL) {
    size_t locale_len = 0u;
    paragraph->dictionary_profile = *dictionary_profile;
    paragraph->dictionary_profile_valid = true;
    if (dictionary_profile->locale != NULL) {
      if (!paragraph_param_len(dictionary_profile->locale,
                               MY_LINE_BREAK_DICTIONARY_MAX_LOCALE_BYTES,
                               &locale_len)) {
        my_text_paragraph_destroy(paragraph);
        return NULL;
      }
      paragraph->dictionary_profile_locale = paragraph_copy_param(
          allocator, dictionary_profile->locale, locale_len);
      if (paragraph->dictionary_profile_locale == NULL) {
        my_text_paragraph_destroy(paragraph);
        return NULL;
      }
      paragraph->dictionary_profile.locale =
          paragraph->dictionary_profile_locale;
    }
  }
  {
    paragraph_wrap_config_t config;
    config.font = font;
    config.size = size;
    config.max_width = max_width;
    config.shape_params = &paragraph->shape_params;
    config.break_options = break_options;
    config.profile_options = profile_options;
    config.dictionary_profile = dictionary_profile;
    if (paragraph_wrap_range(paragraph, &capacity, 0u, text_len, false, 0u,
                             &config,
                             &paragraph->logical_len) != MY_RET_OK) {
      my_text_paragraph_destroy(paragraph);
      return NULL;
    }
  }
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
  my_mem_free(allocator, paragraph->dictionary_profile_locale);
  my_mem_free(allocator, paragraph->text);
  my_mem_free(allocator, paragraph->lines);
  my_mem_free(allocator, paragraph);
}

my_ret_t my_text_paragraph_replace(my_text_paragraph_t* paragraph,
                                   size_t start_byte, size_t end_byte,
                                   const char* text, size_t byte_len) {
  char* new_text;
  char* old_text;
  my_text_paragraph_line_t* old_lines;
  size_t old_count;
  size_t old_len;
  size_t new_len;
  size_t capacity = 0u;
  size_t removed_cps;
  size_t inserted_cps;
  size_t region_lo;
  size_t region_hi;
  size_t region_edit_end;
  size_t prefix_count = 0u;
  size_t middle_count;
  size_t suffix_count = 0u;
  size_t i;
  ptrdiff_t byte_delta;
  ptrdiff_t cp_delta;
  bool skip_leading = false;
  paragraph_wrap_config_t config;
  my_ret_t ret;

  if (paragraph == NULL || start_byte > end_byte ||
      end_byte > paragraph->text_len || (byte_len > 0u && text == NULL) ||
      (byte_len > 0u && memchr(text, '\0', byte_len) != NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (byte_len > MY_TEXT_PARAGRAPH_MAX_BYTES) {
    return MY_RET_INVALID_PARAMS;
  }
  new_len = paragraph->text_len - (end_byte - start_byte) + byte_len;
  if (new_len > MY_TEXT_PARAGRAPH_MAX_BYTES) {
    return MY_RET_INVALID_PARAMS;
  }

  removed_cps = paragraph_count_cps(paragraph->text, start_byte, end_byte);
  new_text = (char*)my_mem_alloc(paragraph->allocator, new_len + 1u);
  if (new_text == NULL) return MY_RET_OOM;
  memcpy(new_text, paragraph->text, start_byte);
  if (byte_len > 0u) {
    memcpy(new_text + start_byte, text, byte_len);
  }
  memcpy(new_text + start_byte + byte_len, paragraph->text + end_byte,
         paragraph->text_len - end_byte);
  new_text[new_len] = '\0';
  inserted_cps =
      paragraph_count_cps(new_text, start_byte, start_byte + byte_len);

  paragraph_edit_region(paragraph->text, paragraph->text_len, start_byte,
                        end_byte, &region_lo, &region_hi, &region_edit_end);
  /* An inserted '\n' right after a prefix '\r' joins it into one atomic
   * CRLF: wrap from the '\r' and skip the break without emitting. */
  if (region_lo > 0u && region_lo < new_len &&
      new_text[region_lo - 1u] == '\r' && new_text[region_lo] == '\n') {
    skip_leading = true;
  }
  byte_delta = (ptrdiff_t)byte_len - (ptrdiff_t)(end_byte - start_byte);
  cp_delta = (ptrdiff_t)inserted_cps - (ptrdiff_t)removed_cps;

  config.font = paragraph->font;
  config.size = paragraph->size;
  config.max_width = paragraph->max_width;
  config.shape_params = &paragraph->shape_params;
  config.break_options =
      paragraph->break_options_valid ? &paragraph->break_options : NULL;
  config.profile_options =
      paragraph->profile_options_valid ? &paragraph->profile_options : NULL;
  config.dictionary_profile = paragraph->dictionary_profile_valid
                                  ? &paragraph->dictionary_profile
                                  : NULL;

  old_text = paragraph->text;
  old_len = paragraph->text_len;
  old_lines = paragraph->lines;
  old_count = paragraph->line_count;

  /* Build into a fresh line array against the new text; roll back on any
   * failure so the paragraph stays unchanged. */
  paragraph->lines = NULL;
  paragraph->line_count = 0u;
  paragraph->text = new_text;
  paragraph->text_len = new_len;

  while (prefix_count < old_count &&
         old_lines[prefix_count].start_byte < region_lo) {
    const my_text_paragraph_line_t* line = &old_lines[prefix_count];
    ret = paragraph_add_line(paragraph, &capacity, line->start_byte,
                             line->end_byte, line->start_cp, line->cp_count);
    if (ret != MY_RET_OK) goto rollback;
    prefix_count++;
  }
  {
    size_t wrap_start = skip_leading ? region_lo - 1u : region_lo;
    size_t wrap_end = (size_t)((ptrdiff_t)region_hi + byte_delta);
    size_t cp_base =
        prefix_count > 0u
            ? old_lines[prefix_count - 1u].start_cp +
                  old_lines[prefix_count - 1u].cp_count
            : 0u;
    size_t middle_cps = 0u;
    ret = paragraph_wrap_range(paragraph, &capacity, wrap_start, wrap_end,
                               skip_leading, cp_base, &config, &middle_cps);
    if (ret != MY_RET_OK) goto rollback;
  }
  middle_count = paragraph->line_count - prefix_count;
  for (i = 0u; i < old_count; i++) {
    const my_text_paragraph_line_t* line = &old_lines[i];
    /* Untouched suffix lines shift by the edit deltas. Touched segments'
     * lines sit inside [region_lo, region_hi]; the trailing boundary is
     * subtle for an EMPTY segment exactly at region_hi: it was touched (and
     * is rebuilt in the middle) iff the edit's closed end reached it, i.e.
     * region_hi == region_edit_end; otherwise it follows the region's last
     * hard break untouched and shifts as suffix. */
    bool region_tail_empty =
        line->start_byte == region_hi && line->end_byte == region_hi &&
        region_hi == region_edit_end;
    if (line->start_byte < region_hi || line->start_byte <= region_lo ||
        region_tail_empty) {
      continue;
    }
    if (cp_delta < 0 && line->start_cp < (size_t)-cp_delta) goto fail;
    ret = paragraph_add_line(
        paragraph, &capacity,
        (size_t)((ptrdiff_t)line->start_byte + byte_delta),
        (size_t)((ptrdiff_t)line->end_byte + byte_delta),
        (size_t)((ptrdiff_t)line->start_cp + cp_delta), line->cp_count);
    if (ret != MY_RET_OK) goto rollback;
    suffix_count++;
  }

  paragraph->logical_len =
      (size_t)((ptrdiff_t)paragraph->logical_len + cp_delta);
  for (i = 0u; i < MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY; i++) {
    my_text_layout_destroy(paragraph->line_layout_cache[i].layout);
    paragraph->line_layout_cache[i].layout = NULL;
    paragraph->line_layout_cache[i].line_index = 0u;
    paragraph->line_layout_cache[i].last_used = 0u;
  }
  paragraph->replace_count++;
  paragraph->last_replace_prefix_lines = prefix_count;
  paragraph->last_replace_middle_lines = middle_count;
  paragraph->last_replace_suffix_lines = suffix_count;
  my_mem_free(paragraph->allocator, old_lines);
  my_mem_free(paragraph->allocator, old_text);
  return MY_RET_OK;

fail:
  ret = MY_RET_FAIL;
rollback:
  my_mem_free(paragraph->allocator, paragraph->lines);
  paragraph->lines = old_lines;
  paragraph->line_count = old_count;
  paragraph->text = old_text;
  paragraph->text_len = old_len;
  my_mem_free(paragraph->allocator, new_text);
  return ret;
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
