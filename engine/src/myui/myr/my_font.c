/**
 * @file my_font.c
 * @brief UTF-8 decoding + built-in 8x8 bitmap font.
 */
#include "myr/my_font.h"
#include "myr/my_ui_metrics.h"

#include <stdint.h>
#include <stdatomic.h>
#include <string.h>

#include "myr/my_font_bitmap_data.h"
#include "myr/generated/my_combining_marks_data.h"

/* ---------------- UTF-8 ---------------- */

uint32_t my_utf8_next(const char** s) {
  const unsigned char* p = (const unsigned char*)*s;
  uint32_t cp;
  unsigned char second;

  if (*p < 0x80u) {
    *s += 1;
    return *p;
  }
  if (*p >= 0xC2u && *p <= 0xDFu) {
    if (p[1] == '\0' || (p[1] & 0xC0u) != 0x80u) goto invalid;
    cp = ((uint32_t)(*p & 0x1Fu) << 6) | (uint32_t)(p[1] & 0x3Fu);
    *s += 2;
    return cp;
  }
  if (*p >= 0xE0u && *p <= 0xEFu) {
    if (p[1] == '\0' || p[2] == '\0' ||
        (p[1] & 0xC0u) != 0x80u || (p[2] & 0xC0u) != 0x80u)
      goto invalid;
    second = p[1];
    if ((*p == 0xE0u && second < 0xA0u) ||
        (*p == 0xEDu && second >= 0xA0u))
      goto invalid;
    cp = ((uint32_t)(*p & 0x0Fu) << 12) |
         ((uint32_t)(second & 0x3Fu) << 6) | (uint32_t)(p[2] & 0x3Fu);
    *s += 3;
    return cp;
  }
  if (*p >= 0xF0u && *p <= 0xF4u) {
    if (p[1] == '\0' || p[2] == '\0' || p[3] == '\0' ||
        (p[1] & 0xC0u) != 0x80u || (p[2] & 0xC0u) != 0x80u ||
        (p[3] & 0xC0u) != 0x80u)
      goto invalid;
    second = p[1];
    if ((*p == 0xF0u && second < 0x90u) ||
        (*p == 0xF4u && second > 0x8Fu))
      goto invalid;
    cp = ((uint32_t)(*p & 0x07u) << 18) |
         ((uint32_t)(second & 0x3Fu) << 12) |
         ((uint32_t)(p[2] & 0x3Fu) << 6) | (uint32_t)(p[3] & 0x3Fu);
    *s += 4;
    return cp;
  }

invalid:
  *s += 1;
  return 0xFFFDu;
}

/* ---------------- bitmap font ---------------- */

typedef struct my_font_bitmap_t {
  my_font_t base;
  const my_allocator_t* allocator;
  uint8_t bitmap[95][64];
  uint8_t fallback[64];
  atomic_size_t lifetime_state;
} my_font_bitmap_t;

static void bmp_finalize(my_font_bitmap_t* font) {
  my_mem_free(font->allocator, font);
}

static bool bmp_acquire_lease(my_font_bitmap_t* font) {
  size_t state = atomic_load_explicit(&font->lifetime_state,
                                      memory_order_acquire);
  for (;;) {
    if ((state & 1u) != 0u || state > SIZE_MAX - 2u) return false;
    if (atomic_compare_exchange_weak_explicit(
            &font->lifetime_state, &state, state + 2u, memory_order_acquire,
            memory_order_acquire)) {
      return true;
    }
  }
}

static void bmp_release_owner(void* owner) {
  my_font_bitmap_t* font = (my_font_bitmap_t*)owner;
  size_t state;
  if (font == NULL) return;
  state = atomic_load_explicit(&font->lifetime_state, memory_order_acquire);
  for (;;) {
    size_t next;
    if (state < 2u) return;
    next = state - 2u;
    if (atomic_compare_exchange_weak_explicit(
            &font->lifetime_state, &state, next, memory_order_acq_rel,
            memory_order_acquire)) {
      if (next == 1u) {
        bmp_finalize(font);
      }
      return;
    }
  }
}

static bool bmp_request_destroy(my_font_bitmap_t* font) {
  size_t state = atomic_load_explicit(&font->lifetime_state,
                                      memory_order_acquire);
  for (;;) {
    if ((state & 1u) != 0u) return false;
    if (atomic_compare_exchange_weak_explicit(
            &font->lifetime_state, &state, state | 1u, memory_order_acq_rel,
            memory_order_acquire)) {
      return state == 0u;
    }
  }
}

static void bmp_destroy(my_font_t* font) {
  my_font_bitmap_t* f = (my_font_bitmap_t*)font;
  if (f == NULL) return;
  if (bmp_request_destroy(f)) {
    bmp_finalize(f);
  }
}

static void bmp_expand_glyph(uint8_t* destination, const uint8_t* source) {
  size_t row;
  size_t column;
  for (row = 0; row < 8; row++) {
    for (column = 0; column < 8; column++) {
      destination[row * 8 + column] =
          (source[row] & (uint8_t)(0x80u >> column)) != 0 ? 255u : 0u;
    }
  }
}

static my_ret_t bmp_measure(my_font_t* font, const char* text, int32_t size,
                            int32_t* w, int32_t* h) {
  const char* p = text;
  int64_t width = 0;
  (void)font;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  while (*p != '\0') {
    if (!my_font_is_variation_selector(my_utf8_next(&p))) {
      width += size; /* monospace: one cell per codepoint */
    }
  }
  if (w != NULL) {
    *w = width > INT32_MAX ? INT32_MAX : width < 0 ? 0 : (int32_t)width;
  }
  if (h != NULL) {
    *h = size;
  }
  return MY_RET_OK;
}

static my_ret_t bmp_get_glyph(my_font_t* font, uint32_t codepoint, int32_t size,
                              my_glyph_t* glyph) {
  my_font_bitmap_t* bitmap_font = (my_font_bitmap_t*)font;
  if (glyph == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!bmp_acquire_lease(bitmap_font)) return MY_RET_FAIL;
  if (my_font_is_variation_selector(codepoint)) {
    memset(glyph, 0, sizeof(*glyph));
    glyph->lease = bitmap_font;
    glyph->release_lease = bmp_release_owner;
    return MY_RET_OK;
  }
  if (codepoint < 32 || codepoint > 126) {
    glyph->bitmap = bitmap_font->fallback;
    glyph->w = 8;
    glyph->h = 8;
  } else {
    glyph->bitmap = bitmap_font->bitmap[codepoint - 32];
    glyph->w = 8;
    glyph->h = 8;
  }
  glyph->bearing_x = 0;
  glyph->bearing_y = (8 * size) / 8; /* baseline at bottom of the cell */
  glyph->advance = size;
  glyph->lease = bitmap_font;
  glyph->release_lease = bmp_release_owner;
  return MY_RET_OK;
}

static int32_t bmp_ascent(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static int32_t bmp_descent(my_font_t* font, int32_t size) {
  (void)font;
  (void)size;
  return 0;
}

static int32_t bmp_line_height(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static bool bmp_has_glyph(my_font_t* font, uint32_t codepoint) {
  (void)font;
  return codepoint >= 32 && codepoint <= 126; /* built-in 8x8 coverage */
}

static const my_font_vtable_t s_bitmap_vtable = {bmp_measure, bmp_get_glyph,
                                                 bmp_ascent, bmp_descent,
                                                 bmp_line_height, bmp_destroy,
                                                 bmp_has_glyph, NULL, NULL, NULL,
                                                 NULL, NULL};

my_font_t* my_font_bitmap_create(const my_allocator_t* allocator) {
  my_font_bitmap_t* f =
      (my_font_bitmap_t*)my_mem_calloc(allocator, 1, sizeof(my_font_bitmap_t));
  static const uint8_t fallback[8] = {0xFE, 0x82, 0x82, 0x82,
                                      0x82, 0x82, 0xFE, 0};
  size_t glyph_index;
  if (f == NULL) {
    return NULL;
  }
  f->base.vtable = &s_bitmap_vtable;
  f->allocator = allocator;
  for (glyph_index = 0; glyph_index < 95; glyph_index++) {
    bmp_expand_glyph(f->bitmap[glyph_index],
                     MY_FONT_BITMAP_DATA[glyph_index]);
  }
  bmp_expand_glyph(f->fallback, fallback);
  return (my_font_t*)f;
}

/* ---------------- fallback chain (M14b; backend-neutral since M16) ----
 * CJK fonts often ship without Latin glyphs (e.g. DroidSansFallback)
 * and vice versa; the chain routes each codepoint to the first face
 * that actually contains it. Faces are loaded with FreeType when built
 * with MYUI_FONT_FREETYPE (hinted), stb_truetype otherwise. */

typedef struct my_font_chain_t {
  my_font_t base;
  const my_allocator_t* allocator;
  my_font_t** faces; /**< owned array */
  size_t count;
} my_font_chain_t;

static bool shape_text_valid(const char* text);
static my_font_t* chain_face_for(my_font_chain_t* chain, uint32_t codepoint);

static bool chain_is_combining_mark(uint32_t codepoint) {
  size_t low = 0u;
  size_t high = sizeof(MY_COMBINING_MARKS) /
                sizeof(MY_COMBINING_MARKS[0]);
  while (low < high) {
    size_t middle = low + (high - low) / 2u;
    const my_combining_mark_range_t* range = &MY_COMBINING_MARKS[middle];
    if (codepoint < range->first) {
      high = middle;
    } else if (codepoint > range->last) {
      low = middle + 1u;
    } else {
      return true;
    }
  }
  return false;
}

static bool chain_cluster_extension(uint32_t codepoint) {
  return chain_is_combining_mark(codepoint) ||
         my_font_is_variation_selector(codepoint) ||
         codepoint == 0x200Cu ||
         (codepoint >= 0x1F3FBu && codepoint <= 0x1F3FFu) ||
         (codepoint >= 0xE0020u && codepoint <= 0xE007Fu);
}

static size_t chain_cluster_end(const char* text, size_t start) {
  const char* cursor = text + start;
  const char* next;
  uint32_t codepoint;

  next = cursor;
  codepoint = my_utf8_next(&next);
  cursor = next;
  for (;;) {
    next = cursor;
    if (*next == '\0') break;
    codepoint = my_utf8_next(&next);
    if (chain_cluster_extension(codepoint)) {
      cursor = next;
      continue;
    }
    if (codepoint != 0x200Du) break;
    cursor = next;
    if (*cursor == '\0') break;
    next = cursor;
    (void)my_utf8_next(&next);
    cursor = next;
  }
  return (size_t)(cursor - text);
}

typedef enum chain_cluster_coverage_t {
  CHAIN_CLUSTER_UNCOVERED = 0,
  CHAIN_CLUSTER_UNKNOWN_VARIATION = 1,
  CHAIN_CLUSTER_CONFIRMED = 2
} chain_cluster_coverage_t;

static chain_cluster_coverage_t chain_face_cluster_coverage(
    my_font_t* face, const char* text, size_t start, size_t end) {
  const char* cursor = text + start;
  uint32_t variation_base = 0u;
  bool unknown_variation = false;
  while ((size_t)(cursor - text) < end) {
    const char* next = cursor;
    uint32_t codepoint = my_utf8_next(&next);
    if (my_font_is_variation_selector(codepoint)) {
      if (variation_base != 0u) {
        my_font_variation_support_t variation_support;
        if (face->vtable->variation_support == NULL) {
          unknown_variation = true;
        } else {
          variation_support = face->vtable->variation_support(
              face, variation_base, codepoint);
          if (variation_support == MY_FONT_VARIATION_UNSUPPORTED) {
            return CHAIN_CLUSTER_UNCOVERED;
          }
          if (variation_support == MY_FONT_VARIATION_SUPPORT_UNKNOWN) {
            unknown_variation = true;
          }
        }
      }
      cursor = next;
      continue;
    }
    if (codepoint != 0x200Cu && codepoint != 0x200Du &&
        !(codepoint >= 0xE0020u && codepoint <= 0xE007Fu) &&
        !my_font_has_glyph(face, codepoint)) {
      return CHAIN_CLUSTER_UNCOVERED;
    }
    if (codepoint != 0x200Cu && codepoint != 0x200Du &&
        !(codepoint >= 0xE0020u && codepoint <= 0xE007Fu) &&
        !chain_is_combining_mark(codepoint)) {
      variation_base = codepoint;
    }
    cursor = next;
  }
  return unknown_variation ? CHAIN_CLUSTER_UNKNOWN_VARIATION
                           : CHAIN_CLUSTER_CONFIRMED;
}

static my_font_t* chain_face_for_cluster(my_font_chain_t* chain,
                                         const char* text, size_t start,
                                         size_t end) {
  const char* cursor = text + start;
  const char* next = cursor;
  uint32_t first = my_utf8_next(&next);
  my_font_t* unknown_face = NULL;
  size_t i;

  if (end == (size_t)(next - text)) return chain_face_for(chain, first);
  for (i = 0u; i < chain->count; i++) {
    chain_cluster_coverage_t coverage = chain_face_cluster_coverage(
        chain->faces[i], text, start, end);
    if (coverage == CHAIN_CLUSTER_CONFIRMED) {
      if (i != 0u) my_ui_metrics_record_fallback();
      return chain->faces[i];
    }
    if (coverage == CHAIN_CLUSTER_UNKNOWN_VARIATION && unknown_face == NULL) {
      unknown_face = chain->faces[i];
    }
  }
  if (unknown_face != NULL) {
    if (unknown_face != chain->faces[0]) my_ui_metrics_record_fallback();
    return unknown_face;
  }
  return chain_face_for(chain, first);
}

static my_font_t* chain_face_for_cluster_shape(
    my_font_chain_t* chain, const char* text, size_t start, size_t end,
    const my_font_shape_params_t* params,
    const my_font_shape_support_t* supports) {
  my_font_t* unknown_face = NULL;
  my_font_t* unknown_variation_face = NULL;
  const char* next = text + start;
  uint32_t first = my_utf8_next(&next);
  size_t i;

  for (i = 0u; i < chain->count; i++) {
    my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
    my_ret_t ret;
    chain_cluster_coverage_t coverage = chain_face_cluster_coverage(
        chain->faces[i], text, start, end);
    if (coverage == CHAIN_CLUSTER_UNCOVERED) {
      continue;
    }
    if (supports != NULL) {
      support = supports[i];
      ret = MY_RET_OK;
    } else {
      ret = my_font_shape_support_query(chain->faces[i], params, &support);
    }
    if (ret == MY_RET_OK && support == MY_FONT_SHAPE_SUPPORTED) {
      if (coverage == CHAIN_CLUSTER_CONFIRMED) {
        if (i != 0u) my_ui_metrics_record_fallback();
        return chain->faces[i];
      }
      if (unknown_variation_face == NULL) {
        unknown_variation_face = chain->faces[i];
      }
    }
    if (coverage == CHAIN_CLUSTER_CONFIRMED && unknown_face == NULL &&
        (ret != MY_RET_OK || support == MY_FONT_SHAPE_SUPPORT_UNKNOWN)) {
      unknown_face = chain->faces[i];
    }
  }
  if (unknown_face != NULL) {
    if (unknown_face != chain->faces[0]) my_ui_metrics_record_fallback();
    return unknown_face;
  }
  if (unknown_variation_face != NULL) {
    if (unknown_variation_face != chain->faces[0]) {
      my_ui_metrics_record_fallback();
    }
    return unknown_variation_face;
  }
  return chain_face_for(chain, first);
}

static my_ret_t chain_measure_codepoint(my_font_t* face, uint32_t codepoint,
                                        int32_t size, int32_t* width) {
  char encoded[8];
  size_t length = 0u;
  int32_t height;

  if (face == NULL || width == NULL) return MY_RET_INVALID_PARAMS;
  if (codepoint < 0x80u) {
    encoded[length++] = (char)codepoint;
  } else if (codepoint < 0x800u) {
    encoded[length++] = (char)(0xC0u | (codepoint >> 6));
    encoded[length++] = (char)(0x80u | (codepoint & 0x3Fu));
  } else if (codepoint < 0x10000u) {
    encoded[length++] = (char)(0xE0u | (codepoint >> 12));
    encoded[length++] = (char)(0x80u | ((codepoint >> 6) & 0x3Fu));
    encoded[length++] = (char)(0x80u | (codepoint & 0x3Fu));
  } else {
    encoded[length++] = (char)(0xF0u | (codepoint >> 18));
    encoded[length++] = (char)(0x80u | ((codepoint >> 12) & 0x3Fu));
    encoded[length++] = (char)(0x80u | ((codepoint >> 6) & 0x3Fu));
    encoded[length++] = (char)(0x80u | (codepoint & 0x3Fu));
  }
  encoded[length] = '\0';
  return my_font_measure(face, encoded, size, width, &height) == MY_RET_OK
             ? MY_RET_OK
             : MY_RET_FAIL;
}

/** @brief First face containing cp; the last face when none has it. */
static my_font_t* chain_face_for(my_font_chain_t* c, uint32_t cp) {
  size_t i;
  for (i = 0; i < c->count; i++) {
    if (my_font_has_glyph(c->faces[i], cp)) {
      if (i != 0u) my_ui_metrics_record_fallback();
      return c->faces[i];
    }
  }
  if (c->count > 1u) my_ui_metrics_record_fallback();
  return c->faces[c->count - 1];
}

static my_ret_t chain_measure(my_font_t* font, const char* text, int32_t size,
                              int32_t* w, int32_t* h) {
  my_font_chain_t* c = (my_font_chain_t*)font;
  const char* p = text;
  int64_t width = 0;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  while (*p != '\0') {
    size_t start = (size_t)(p - text);
    size_t end = chain_cluster_end(text, start);
    const char* cluster = text + start;
    const char* cluster_end = text + end;
    my_font_t* face = chain_face_for_cluster(c, text, start, end);
    while (cluster < cluster_end) {
      const char* next = cluster;
      uint32_t codepoint = my_utf8_next(&next);
      int32_t codepoint_width = 0;
      if (!my_font_is_variation_selector(codepoint) &&
          chain_measure_codepoint(face, codepoint, size,
                                  &codepoint_width) == MY_RET_OK) {
        width += codepoint_width;
      }
      cluster = next;
    }
    p = cluster_end;
  }
  if (w != NULL) {
    *w = width > INT32_MAX ? INT32_MAX : width < 0 ? 0 : (int32_t)width;
  }
  if (h != NULL) {
    *h = my_font_line_height(c->faces[0], size);
  }
  return MY_RET_OK;
}

static my_ret_t chain_get_glyph(my_font_t* font, uint32_t codepoint,
                                int32_t size, my_glyph_t* glyph) {
  my_font_chain_t* c = (my_font_chain_t*)font;
  if (glyph == NULL || size <= 0) return MY_RET_INVALID_PARAMS;
  if (my_font_is_variation_selector(codepoint)) {
    memset(glyph, 0, sizeof(*glyph));
    return MY_RET_OK;
  }
  return my_font_get_glyph(chain_face_for(c, codepoint), codepoint, size,
                           glyph);
}

static my_ret_t chain_append_shape(
    const my_allocator_t* allocator, my_font_shape_result_t* result,
    size_t* capacity, const my_font_shape_result_t* shaped,
    size_t cluster_base, my_font_t* face) {
  size_t required;
  size_t next_capacity;
  size_t i;
  my_font_shape_glyph_t* glyphs;

  if (cluster_base > UINT32_MAX) {
    return MY_RET_FAIL;
  }
  if (shaped->count > MY_FONT_SHAPE_MAX_GLYPHS ||
      result->count > MY_FONT_SHAPE_MAX_GLYPHS - shaped->count) {
    return MY_RET_FAIL;
  }
  if (shaped->count > SIZE_MAX - result->count) {
    return MY_RET_OOM;
  }
  required = result->count + shaped->count;
  if (required > *capacity) {
    next_capacity = *capacity > 0 ? *capacity : 8;
    while (next_capacity < required) {
      if (next_capacity > SIZE_MAX / 2) {
        next_capacity = required;
        break;
      }
      next_capacity *= 2;
    }
    if (next_capacity > SIZE_MAX / sizeof(*result->glyphs)) {
      return MY_RET_OOM;
    }
    glyphs = (my_font_shape_glyph_t*)my_mem_realloc(
        allocator, result->glyphs,
        next_capacity * sizeof(*result->glyphs));
    if (glyphs == NULL) {
      return MY_RET_OOM;
    }
    result->glyphs = glyphs;
    *capacity = next_capacity;
  }
  for (i = 0; i < shaped->count; i++) {
    my_font_shape_glyph_t glyph = shaped->glyphs[i];
    if (glyph.cluster > UINT32_MAX - (uint32_t)cluster_base) {
      return MY_RET_FAIL;
    }
    glyph.font = face;
    glyph.cluster += (uint32_t)cluster_base;
    result->glyphs[result->count++] = glyph;
  }
  return MY_RET_OK;
}

static my_ret_t chain_shape_run(
    my_font_t* face, const char* text, size_t start, size_t end,
    int32_t size, const my_font_shape_params_t* params,
    const my_allocator_t* allocator,
    my_font_shape_result_t* result, size_t* capacity) {
  my_font_shape_result_t shaped = {0};
  char* segment;
  size_t length = end - start;
  my_ret_t ret;

  if (length > SIZE_MAX - 1) {
    return MY_RET_OOM;
  }
  segment = (char*)my_mem_alloc(allocator, length + 1);
  if (segment == NULL) {
    return MY_RET_OOM;
  }
  memcpy(segment, text + start, length);
  segment[length] = '\0';
  ret = my_font_shape_ex(face, segment, size, params, allocator, &shaped);
  if (ret == MY_RET_OK) {
    ret = chain_append_shape(allocator, result, capacity, &shaped, start,
                             face);
  }
  my_font_shape_destroy(&shaped);
  my_mem_free(allocator, segment);
  return ret;
}

typedef struct chain_shape_segment_t {
  my_font_t* face;
  size_t start;
  size_t end;
} chain_shape_segment_t;

static my_ret_t chain_shape_ex(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  my_font_chain_t* c = (my_font_chain_t*)font;
  const char* p = text;
  my_font_t* run_face = NULL;
  size_t run_start = 0;
  size_t capacity = 0;
  my_ret_t ret;
  bool crossed_face = false;
  bool rtl;
  my_font_shape_support_t* supports = NULL;
  bool explicit_params;

  if (result == NULL) return MY_RET_INVALID_PARAMS;
  memset(result, 0, sizeof(*result));
  result->allocator = allocator;
  if (font == NULL || text == NULL || size <= 0 || params == NULL ||
      !shape_text_valid(text) || !my_font_shape_params_valid(params)) {
    return MY_RET_INVALID_PARAMS;
  }
  result->rtl = params->rtl;
  rtl = params->rtl;
  explicit_params = params->script != 0u || params->language != NULL ||
                    params->features != NULL;
  if (explicit_params && c->count > 0u) {
    supports = (my_font_shape_support_t*)my_mem_alloc(
        allocator, c->count * sizeof(*supports));
    if (supports == NULL) return MY_RET_OOM;
    {
      size_t i;
      for (i = 0u; i < c->count; i++) {
        supports[i] = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
        ret = my_font_shape_support_query(c->faces[i], params, &supports[i]);
        if (ret != MY_RET_OK) {
          my_mem_free(allocator, supports);
          return ret;
        }
      }
    }
  }

  while (*p != '\0') {
    size_t byte = (size_t)(p - text);
    size_t end = chain_cluster_end(text, byte);
    my_font_t* face = explicit_params
                          ? chain_face_for_cluster_shape(c, text, byte, end,
                                                         params, supports)
                          : chain_face_for_cluster(c, text, byte, end);
    if (run_face == NULL) {
      run_face = face;
      run_start = byte;
    } else if (face != run_face) {
      if (rtl) {
        crossed_face = true;
        break;
      }
      {
        my_font_shape_params_t run_params = *params;
        run_params.rtl = false;
        ret = chain_shape_run(run_face, text, run_start, byte, size,
                              &run_params,
                            allocator, result, &capacity);
      }
      if (ret != MY_RET_OK) {
        my_mem_free(allocator, supports);
        my_font_shape_destroy(result);
        return ret;
      }
      run_face = face;
      run_start = byte;
    }
    p = text + end;
  }
  if (!crossed_face) {
    if (run_face != NULL) {
      ret = chain_shape_run(run_face, text, run_start, (size_t)(p - text),
                            size, params, allocator, result, &capacity);
      if (ret != MY_RET_OK) {
        my_mem_free(allocator, supports);
        my_font_shape_destroy(result);
        return ret;
      }
    }
    my_mem_free(allocator, supports);
    result->used_complex_shaping = true;
    return MY_RET_OK;
  }

  if (rtl) {
    chain_shape_segment_t* segments;
    size_t run_count = 0;
    size_t i;

    p = text;
    run_face = NULL;
    run_start = 0;
    while (*p != '\0') {
      size_t byte = (size_t)(p - text);
      size_t end = chain_cluster_end(text, byte);
      my_font_t* face = explicit_params
                            ? chain_face_for_cluster_shape(c, text, byte, end,
                                                           params, supports)
                            : chain_face_for_cluster(c, text, byte, end);
      if (run_face == NULL) {
        run_face = face;
        run_start = byte;
      } else if (face != run_face) {
        if (run_count == SIZE_MAX) {
          my_font_shape_destroy(result);
          return MY_RET_OOM;
        }
        run_count++;
        run_face = face;
        run_start = byte;
      }
      p = text + end;
    }
    if (run_face != NULL) run_count++;
    if (run_count == 0 || run_count > SIZE_MAX / sizeof(*segments)) {
      my_mem_free(allocator, supports);
      my_font_shape_destroy(result);
      return run_count == 0 ? MY_RET_FAIL : MY_RET_OOM;
    }
    segments = (chain_shape_segment_t*)my_mem_alloc(
        allocator, run_count * sizeof(*segments));
    if (segments == NULL) {
      my_mem_free(allocator, supports);
      my_font_shape_destroy(result);
      return MY_RET_OOM;
    }

    p = text;
    run_face = NULL;
    run_start = 0;
    i = 0;
    while (*p != '\0') {
      size_t byte = (size_t)(p - text);
      size_t end = chain_cluster_end(text, byte);
      my_font_t* face = explicit_params
                            ? chain_face_for_cluster_shape(c, text, byte, end,
                                                           params, supports)
                            : chain_face_for_cluster(c, text, byte, end);
      if (run_face == NULL) {
        run_face = face;
        run_start = byte;
      } else if (face != run_face) {
        segments[i++] = (chain_shape_segment_t){run_face, run_start, byte};
        run_face = face;
        run_start = byte;
      }
      p = text + end;
    }
    segments[i++] = (chain_shape_segment_t){run_face, run_start,
                                            (size_t)(p - text)};
    for (i = run_count; i > 0; i--) {
      ret = chain_shape_run(segments[i - 1].face, text,
                            segments[i - 1].start, segments[i - 1].end, size,
                            params, allocator, result, &capacity);
      if (ret != MY_RET_OK) {
        my_mem_free(allocator, segments);
        my_mem_free(allocator, supports);
        my_font_shape_destroy(result);
        return ret;
      }
    }
    my_mem_free(allocator, segments);
  }
  my_mem_free(allocator, supports);
  result->used_complex_shaping = true;
  return MY_RET_OK;
}

static my_ret_t chain_shape(my_font_t* font, const char* text, int32_t size,
                            bool rtl, const my_allocator_t* allocator,
                            my_font_shape_result_t* result) {
  my_font_shape_params_t params = {rtl, 0u, NULL, NULL};
  return chain_shape_ex(font, text, size, &params, allocator, result);
}

static my_ret_t chain_shape_support(
    my_font_t* font, const my_font_shape_params_t* params,
    my_font_shape_support_t* support) {
  my_font_chain_t* chain = (my_font_chain_t*)font;
  bool unknown = false;
  size_t i;
  if (chain == NULL || params == NULL || support == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  *support = MY_FONT_SHAPE_UNSUPPORTED;
  for (i = 0u; i < chain->count; i++) {
    my_font_shape_support_t face_support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
    my_ret_t ret = my_font_shape_support_query(chain->faces[i], params,
                                               &face_support);
    if (ret != MY_RET_OK) return ret;
    if (face_support == MY_FONT_SHAPE_SUPPORTED) {
      *support = MY_FONT_SHAPE_SUPPORTED;
      return MY_RET_OK;
    }
    if (face_support == MY_FONT_SHAPE_SUPPORT_UNKNOWN) unknown = true;
  }
  if (unknown) *support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  return MY_RET_OK;
}

static int32_t chain_ascent(my_font_t* font, int32_t size) {
  return my_font_ascent(((my_font_chain_t*)font)->faces[0], size);
}

static int32_t chain_descent(my_font_t* font, int32_t size) {
  my_font_chain_t* c = (my_font_chain_t*)font;
  return my_font_descent(c->faces[0], size);
}

static int32_t chain_line_height(my_font_t* font, int32_t size) {
  return my_font_line_height(((my_font_chain_t*)font)->faces[0], size);
}

static void chain_destroy(my_font_t* font) {
  my_font_chain_t* c = (my_font_chain_t*)font;
  size_t i;
  if (c == NULL) {
    return;
  }
  for (i = 0; i < c->count; i++) {
    my_font_destroy(c->faces[i]);
  }
  my_mem_free(c->allocator, c->faces);
  my_mem_free(c->allocator, c);
}

static const my_font_vtable_t s_chain_vtable = {
    chain_measure, chain_get_glyph,  chain_ascent,   chain_descent,
    chain_line_height, chain_destroy, NULL /* per-face has_glyph */, chain_shape,
    NULL, chain_shape_ex, chain_shape_support, NULL};

static bool shape_param_string_valid(const char* value, size_t max_bytes) {
  size_t length;
  if (value == NULL) return true;
  for (length = 0u; length <= max_bytes; ++length) {
    if (value[length] == '\0') return true;
  }
  return false;
}

typedef struct shape_feature_entry_t {
  char tag[5];
  uint32_t value;
  uint32_t start;
  uint32_t end;
} shape_feature_entry_t;

#define MY_FONT_SHAPE_NORMALIZED_FEATURE_CAPACITY \
  (MY_FONT_SHAPE_MAX_FEATURE_COUNT * 2u)

static bool shape_ascii_space(char value) {
  return value == ' ' || value == '\t' || value == '\r' || value == '\n';
}

static bool shape_ascii_digit(char value) {
  return value >= '0' && value <= '9';
}

static bool shape_ascii_tag_char(char value) {
  return (value >= 'a' && value <= 'z') ||
         (value >= 'A' && value <= 'Z') ||
         (value >= '0' && value <= '9');
}

static void shape_skip_space(const char* value, size_t length, size_t* index) {
  while (*index < length && shape_ascii_space(value[*index])) (*index)++;
}

static bool shape_parse_u32(const char* value, size_t length, size_t* index,
                            uint32_t* output) {
  uint32_t parsed = 0u;
  size_t digits = 0u;
  while (*index < length && shape_ascii_digit(value[*index])) {
    uint32_t digit = (uint32_t)(value[*index] - '0');
    if (parsed > (UINT32_MAX - digit) / 10u) return false;
    parsed = parsed * 10u + digit;
    (*index)++;
    digits++;
  }
  if (digits == 0u) return false;
  *output = parsed;
  return true;
}

static bool shape_word_equal(const char* value, size_t length,
                             size_t start, const char* word) {
  size_t word_length = strlen(word);
  return length - start == word_length &&
         memcmp(value + start, word, word_length) == 0;
}

static bool shape_parse_feature(const char* value, size_t length,
                                shape_feature_entry_t* entry) {
  size_t index = 0u;
  size_t token_start;
  bool has_sign = false;
  char sign = 0;
  bool has_value = false;

  shape_skip_space(value, length, &index);
  if (index < length && (value[index] == '+' || value[index] == '-')) {
    has_sign = true;
    sign = value[index++];
  }
  if (length - index < 4u) return false;
  if (!shape_ascii_tag_char(value[index]) ||
      !shape_ascii_tag_char(value[index + 1u]) ||
      !shape_ascii_tag_char(value[index + 2u]) ||
      !shape_ascii_tag_char(value[index + 3u])) {
    return false;
  }
  memcpy(entry->tag, value + index, 4u);
  entry->tag[4] = '\0';
  index += 4u;
  entry->start = 0u;
  entry->end = UINT32_MAX;
  shape_skip_space(value, length, &index);
  if (index < length && value[index] == '[') {
    index++;
    shape_skip_space(value, length, &index);
    if (index < length && value[index] != ':') {
      if (!shape_parse_u32(value, length, &index, &entry->start)) return false;
      shape_skip_space(value, length, &index);
    }
    if (index >= length || value[index++] != ':') return false;
    shape_skip_space(value, length, &index);
    if (index < length && value[index] != ']') {
      if (!shape_parse_u32(value, length, &index, &entry->end)) return false;
      shape_skip_space(value, length, &index);
    }
    if (index >= length || value[index++] != ']' ||
        entry->start > entry->end) {
      return false;
    }
    shape_skip_space(value, length, &index);
  }
  if (has_sign && index < length && value[index] == '=') return false;
  if (index < length && value[index] == '=') {
    index++;
    shape_skip_space(value, length, &index);
    token_start = index;
    while (index < length && !shape_ascii_space(value[index])) index++;
    if (token_start == index) return false;
    if (shape_word_equal(value, index, token_start, "on") ||
        shape_word_equal(value, index, token_start, "true")) {
      entry->value = 1u;
    } else if (shape_word_equal(value, index, token_start, "off") ||
               shape_word_equal(value, index, token_start, "false")) {
      entry->value = 0u;
    } else {
      size_t value_index = token_start;
      if (value_index >= index ||
          !shape_parse_u32(value, index, &value_index, &entry->value) ||
          value_index != index) {
        return false;
      }
    }
    has_value = true;
    shape_skip_space(value, length, &index);
  } else {
    entry->value = has_sign && sign == '-' ? 0u : 1u;
  }
  return index == length && (!has_sign || has_value || sign == '+' ||
                             sign == '-');
}

static bool shape_feature_overlap(const shape_feature_entry_t* left,
                                  const shape_feature_entry_t* right) {
  return left->start < right->end && right->start < left->end;
}

static bool shape_feature_append(shape_feature_entry_t* entries, size_t* count,
                                 const shape_feature_entry_t* entry) {
  if (*count >= MY_FONT_SHAPE_NORMALIZED_FEATURE_CAPACITY) return false;
  entries[(*count)++] = *entry;
  return true;
}

static int shape_feature_compare(const shape_feature_entry_t* left,
                                 const shape_feature_entry_t* right) {
  int tag_result = memcmp(left->tag, right->tag, 4u);
  if (tag_result != 0) return tag_result;
  if (left->start < right->start) return -1;
  if (left->start > right->start) return 1;
  if (left->end < right->end) return -1;
  if (left->end > right->end) return 1;
  if (left->value < right->value) return -1;
  if (left->value > right->value) return 1;
  return 0;
}

static bool shape_output_text(char* output, size_t output_size, size_t* used,
                              const char* text, size_t length) {
  if (*used >= output_size || length > output_size - *used - 1u) return false;
  memcpy(output + *used, text, length);
  *used += length;
  output[*used] = '\0';
  return true;
}

static bool shape_output_u32(char* output, size_t output_size, size_t* used,
                             uint32_t value) {
  char digits[10];
  size_t count = 0u;
  size_t i;
  do {
    digits[count++] = (char)('0' + value % 10u);
    value /= 10u;
  } while (value != 0u);
  if (*used >= output_size || count > output_size - *used - 1u) return false;
  for (i = 0u; i < count; i++) output[*used + i] = digits[count - i - 1u];
  *used += count;
  output[*used] = '\0';
  return true;
}

bool my_font_shape_features_normalize(const char* features, char* output,
                                      size_t output_size) {
  shape_feature_entry_t entries[MY_FONT_SHAPE_NORMALIZED_FEATURE_CAPACITY];
  shape_feature_entry_t next[MY_FONT_SHAPE_NORMALIZED_FEATURE_CAPACITY];
  size_t length = 0u;
  size_t start = 0u;
  size_t count = 0u;
  size_t parsed_count = 0u;
  size_t i;
  size_t used = 0u;

  if (output == NULL || output_size == 0u) return false;
  output[0] = '\0';
  if (features == NULL || features[0] == '\0') return true;
  while (length <= MY_FONT_SHAPE_MAX_FEATURE_BYTES && features[length] != '\0') {
    length++;
  }
  if (length > MY_FONT_SHAPE_MAX_FEATURE_BYTES) return false;
  while (start < length) {
    size_t end = start;
    shape_feature_entry_t parsed;
    size_t next_count = 0u;
    while (end < length && features[end] != ',') end++;
    if (parsed_count >= MY_FONT_SHAPE_MAX_FEATURE_COUNT) {
      output[0] = '\0';
      return false;
    }
    if (end == start || !shape_parse_feature(features + start, end - start,
                                              &parsed)) {
      output[0] = '\0';
      return false;
    }
    for (i = 0u; i < count; i++) {
      shape_feature_entry_t existing = entries[i];
      if (memcmp(existing.tag, parsed.tag, 4u) != 0 ||
          !shape_feature_overlap(&existing, &parsed)) {
        if (!shape_feature_append(next, &next_count, &existing)) {
          output[0] = '\0';
          return false;
        }
        continue;
      }
      if (existing.start < parsed.start) {
        existing.end = parsed.start;
        if (!shape_feature_append(next, &next_count, &existing)) {
          output[0] = '\0';
          return false;
        }
      }
      if (parsed.end < entries[i].end) {
        existing.start = parsed.end;
        existing.end = entries[i].end;
        if (!shape_feature_append(next, &next_count, &existing)) {
          output[0] = '\0';
          return false;
        }
      }
    }
    if (!shape_feature_append(next, &next_count, &parsed)) {
      output[0] = '\0';
      return false;
    }
    memcpy(entries, next, next_count * sizeof(*entries));
    count = next_count;
    parsed_count++;
    if (end == length) break;
    start = end + 1u;
  }
  for (i = 1u; i < count; i++) {
    shape_feature_entry_t value = entries[i];
    size_t position = i;
    while (position > 0u &&
           shape_feature_compare(&value, &entries[position - 1u]) < 0) {
      entries[position] = entries[position - 1u];
      position--;
    }
    entries[position] = value;
  }
  for (i = 0u; i < count; i++) {
    shape_feature_entry_t* entry = &entries[i];
    if (i != 0u && !shape_output_text(output, output_size, &used, ",", 1u))
      goto invalid;
    if (!shape_output_text(output, output_size, &used, entry->tag, 4u))
      goto invalid;
    if (entry->start != 0u || entry->end != UINT32_MAX) {
      if (!shape_output_text(output, output_size, &used, "[", 1u) ||
          !shape_output_u32(output, output_size, &used, entry->start) ||
          !shape_output_text(output, output_size, &used, ":", 1u) ||
          !shape_output_u32(output, output_size, &used, entry->end) ||
          !shape_output_text(output, output_size, &used, "]", 1u))
        goto invalid;
    }
    if (!shape_output_text(output, output_size, &used, "=", 1u) ||
        !shape_output_u32(output, output_size, &used, entry->value))
      goto invalid;
  }
  return true;

invalid:
  output[0] = '\0';
  return false;
}

static bool shape_feature_list_valid(const char* value) {
  char normalized[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  return my_font_shape_features_normalize(value, normalized,
                                           sizeof(normalized));
}

static bool shape_support_value_valid(my_font_shape_support_t support) {
  return support == MY_FONT_SHAPE_SUPPORT_UNKNOWN ||
         support == MY_FONT_SHAPE_SUPPORTED ||
         support == MY_FONT_SHAPE_UNSUPPORTED;
}

static bool shape_text_valid(const char* text) {
  size_t length;
  for (length = 0u; length <= MY_FONT_SHAPE_MAX_BYTES; ++length) {
    if (text[length] == '\0') return true;
  }
  return false;
}

bool my_font_shape_params_valid(const my_font_shape_params_t* params) {
  if (params == NULL) return true;
  return shape_param_string_valid(params->language,
                                  MY_FONT_SHAPE_MAX_LANGUAGE_BYTES) &&
         shape_param_string_valid(params->features,
                                  MY_FONT_SHAPE_MAX_FEATURE_BYTES) &&
         shape_feature_list_valid(params->features);
}

my_ret_t my_font_shape_support_query(
    my_font_t* font, const my_font_shape_params_t* params,
    my_font_shape_support_t* support) {
  my_font_shape_params_t defaults = {false, 0u, NULL, NULL};
  my_font_shape_params_t effective;
  char normalized_features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  my_ret_t ret;

  if (support == NULL || font == NULL || font->vtable == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  *support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  effective = params != NULL ? *params : defaults;
  if (!my_font_shape_params_valid(&effective)) return MY_RET_INVALID_PARAMS;
  if (effective.features != NULL) {
    if (!my_font_shape_features_normalize(effective.features,
                                          normalized_features,
                                          sizeof(normalized_features))) {
      return MY_RET_INVALID_PARAMS;
    }
    effective.features = normalized_features[0] != '\0' ? normalized_features
                                                          : NULL;
  }
  if (font->vtable->shape_support != NULL) {
    ret = font->vtable->shape_support(font, &effective, support);
    if (ret != MY_RET_OK) *support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
    if (!shape_support_value_valid(*support)) {
      *support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
      return MY_RET_FAIL;
    }
    return ret;
  }
  if (font->vtable->shape_ex != NULL) return MY_RET_OK;
  if (font->vtable->shape != NULL && effective.script == 0u &&
      effective.language == NULL && effective.features == NULL) {
    *support = MY_FONT_SHAPE_SUPPORTED;
  } else if (font->vtable->shape != NULL) {
    *support = MY_FONT_SHAPE_UNSUPPORTED;
  }
  return MY_RET_OK;
}

my_ret_t my_font_shape_ex(my_font_t* font, const char* text, int32_t size,
                          const my_font_shape_params_t* params,
                          const my_allocator_t* allocator,
                          my_font_shape_result_t* result) {
  my_font_shape_params_t defaults = {false, 0u, NULL, NULL};
  my_font_shape_params_t effective;
  char normalized_features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  if (result == NULL) return MY_RET_INVALID_PARAMS;
  memset(result, 0, sizeof(*result));
  result->allocator = allocator;
  effective = params != NULL ? *params : defaults;
  result->rtl = effective.rtl;
  if (font == NULL || text == NULL || size <= 0 || !shape_text_valid(text) ||
      !my_font_shape_params_valid(&effective)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (effective.features != NULL) {
    if (!my_font_shape_features_normalize(effective.features,
                                          normalized_features,
                                          sizeof(normalized_features))) {
      return MY_RET_INVALID_PARAMS;
    }
    effective.features = normalized_features[0] != '\0' ? normalized_features
                                                          : NULL;
  }
  if (font->vtable == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  {
    my_ret_t ret;
    my_font_shape_params_t call_params = effective;
    my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
    if (font->vtable->shape_support != NULL) {
      ret = font->vtable->shape_support(font, &effective, &support);
      if (ret != MY_RET_OK) return ret;
      if (!shape_support_value_valid(support)) return MY_RET_FAIL;
      if (support == MY_FONT_SHAPE_UNSUPPORTED) {
        my_font_shape_support_t fallback_support =
            MY_FONT_SHAPE_SUPPORT_UNKNOWN;
        if (call_params.language != NULL) {
          call_params.language = NULL;
          ret = font->vtable->shape_support(font, &call_params,
                                             &fallback_support);
          if (ret != MY_RET_OK || !shape_support_value_valid(fallback_support)) {
            return ret != MY_RET_OK ? ret : MY_RET_FAIL;
          }
          if (fallback_support == MY_FONT_SHAPE_UNSUPPORTED) {
            if (call_params.features != NULL) return MY_RET_NOT_SUPPORTED;
            call_params.script = 0u;
          }
        } else {
          if (call_params.features != NULL) return MY_RET_NOT_SUPPORTED;
          call_params.script = 0u;
        }
      }
    }
    if (font->vtable->shape_ex != NULL) {
      ret = font->vtable->shape_ex(font, text, size, &call_params, allocator,
                                   result);
    } else if (font->vtable->shape != NULL && call_params.script == 0u &&
               call_params.language == NULL && call_params.features == NULL) {
      ret = font->vtable->shape(font, text, size, call_params.rtl, allocator,
                                result);
    } else {
      return MY_RET_NOT_SUPPORTED;
    }
    if (ret == MY_RET_NOT_SUPPORTED && font->vtable->shape != NULL &&
        call_params.script != 0u && call_params.language == NULL &&
        call_params.features == NULL) {
      my_font_shape_destroy(result);
      ret = font->vtable->shape(font, text, size, effective.rtl, allocator,
                                result);
    }
    result->allocator = allocator;
    if (ret != MY_RET_OK) {
      my_font_shape_destroy(result);
      return ret;
    }
    result->rtl = effective.rtl;
    if (result->count > MY_FONT_SHAPE_MAX_GLYPHS ||
        (result->count > 0 && result->glyphs == NULL)) {
      my_font_shape_destroy(result);
      return MY_RET_FAIL;
    }
    {
      size_t i;
      for (i = 0; i < result->count; i++) {
        if (result->glyphs[i].font == NULL) {
          result->glyphs[i].font = font;
        }
      }
    }
    return MY_RET_OK;
  }
}

my_ret_t my_font_shape(my_font_t* font, const char* text, int32_t size,
                       bool rtl, const my_allocator_t* allocator,
                       my_font_shape_result_t* result) {
  my_font_shape_params_t params = {rtl, 0u, NULL, NULL};
  return my_font_shape_ex(font, text, size, &params, allocator, result);
}

void my_font_shape_destroy(my_font_shape_result_t* result) {
  if (result == NULL) return;
  my_mem_free(result->allocator, result->glyphs);
  memset(result, 0, sizeof(*result));
}

my_ret_t my_font_get_glyph_id(my_font_t* font, uint32_t glyph_id,
                              int32_t size, my_glyph_t* glyph) {
  if (glyph == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  memset(glyph, 0, sizeof(*glyph));
  if (font == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (font->vtable == NULL || font->vtable->get_glyph_id == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  {
    my_ret_t result = font->vtable->get_glyph_id(font, glyph_id, size, glyph);
    if (result != MY_RET_OK) my_font_glyph_release(glyph);
    return result;
  }
}

/** @brief Load one face: FreeType preferred (hinted), stb fallback. */
static my_font_t* chain_load_face(const my_allocator_t* allocator,
                                  const my_font_source_t* source,
                                  size_t cache_capacity) {
  my_font_t* f = NULL;
  if (source == NULL || source->path == NULL || source->face_index < 0) {
    return NULL;
  }
#ifdef MYUI_FONT_FREETYPE
  f = my_font_ft_create(allocator, source->path, source->face_index,
                        cache_capacity);
#endif
  if (f == NULL) {
    f = my_font_stb_create_ex(allocator, source->path, source->face_index,
                              cache_capacity);
  }
  return f;
}

my_font_t* my_font_create_chain_ex(const my_allocator_t* allocator,
                                   const my_font_source_t* sources,
                                   size_t source_count,
                                   size_t cache_capacity) {
  my_font_chain_t* c;
  size_t i;
  if (sources == NULL || source_count == 0 ||
      source_count > MY_FONT_CHAIN_MAX_SOURCES ||
      source_count > SIZE_MAX / sizeof(*c->faces)) {
    return NULL;
  }
  c = (my_font_chain_t*)my_mem_calloc(allocator, 1, sizeof(my_font_chain_t));
  if (c == NULL) {
    return NULL;
  }
  c->allocator = allocator;
  c->faces = (my_font_t**)my_mem_calloc(allocator, source_count,
                                        sizeof(my_font_t*));
  if (c->faces == NULL) {
    my_mem_free(allocator, c);
    return NULL;
  }
  for (i = 0; i < source_count; i++) {
    /* faces that fail to load are skipped (missing file, CFF2-only
     * OpenType stb cannot parse, ...) */
    my_font_t* f = chain_load_face(allocator, &sources[i], cache_capacity);
    if (f != NULL) {
      c->faces[c->count++] = f;
    }
  }
  if (c->count == 0) {
    my_mem_free(allocator, c->faces);
    my_mem_free(allocator, c);
    return NULL;
  }
  c->base.vtable = &s_chain_vtable;
  return (my_font_t*)c;
}

my_font_t* my_font_create_chain(const my_allocator_t* allocator,
                                const char* const* paths, size_t path_count,
                                size_t cache_capacity) {
  my_font_source_t* sources;
  my_font_t* font;
  size_t i;

  if (paths == NULL || path_count == 0 ||
      path_count > MY_FONT_CHAIN_MAX_SOURCES ||
      path_count > SIZE_MAX / sizeof(*sources)) {
    return NULL;
  }
  sources = (my_font_source_t*)my_mem_calloc(allocator, path_count,
                                              sizeof(my_font_source_t));
  if (sources == NULL) {
    return NULL;
  }
  for (i = 0; i < path_count; i++) {
    sources[i].path = paths[i];
    sources[i].face_index = 0;
  }
  font = my_font_create_chain_ex(allocator, sources, path_count,
                                 cache_capacity);
  my_mem_free(allocator, sources);
  return font;
}
