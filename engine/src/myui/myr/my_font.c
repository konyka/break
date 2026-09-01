/**
 * @file my_font.c
 * @brief UTF-8 decoding + built-in 8x8 bitmap font.
 */
#include "myr/my_font.h"

#include <string.h>

#include "myr/my_font_bitmap_data.h"

/* ---------------- UTF-8 ---------------- */

uint32_t my_utf8_next(const char** s) {
  const unsigned char* p = (const unsigned char*)*s;
  uint32_t cp;
  size_t n;
  if (*p < 0x80) {
    cp = *p;
    n = 1;
  } else if ((*p & 0xE0) == 0xC0) {
    cp = *p & 0x1F;
    n = 2;
  } else if ((*p & 0xF0) == 0xE0) {
    cp = *p & 0x0F;
    n = 3;
  } else if ((*p & 0xF8) == 0xF0) {
    cp = *p & 0x07;
    n = 4;
  } else {
    *s += 1; /* invalid lead byte: replacement char, advance 1 */
    return 0xFFFD;
  }
  {
    size_t i;
    for (i = 1; i < n; i++) {
      if ((p[i] & 0xC0) != 0x80) {
        *s += 1;
        return 0xFFFD;
      }
      cp = (cp << 6) | (uint32_t)(p[i] & 0x3F);
    }
  }
  *s += n;
  return cp;
}

/* ---------------- bitmap font ---------------- */

typedef struct my_font_bitmap_t {
  my_font_t base;
  const my_allocator_t* allocator;
  uint8_t bitmap[95][64];
  uint8_t fallback[64];
} my_font_bitmap_t;

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
  int32_t width = 0;
  (void)font;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  while (*p != '\0') {
    my_utf8_next(&p);
    width += size; /* monospace: one cell per codepoint */
  }
  if (w != NULL) {
    *w = width;
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

static void bmp_destroy(my_font_t* font) {
  my_font_bitmap_t* f = (my_font_bitmap_t*)font;
  if (f != NULL) {
    my_mem_free(f->allocator, f);
  }
}

static bool bmp_has_glyph(my_font_t* font, uint32_t codepoint) {
  (void)font;
  return codepoint >= 32 && codepoint <= 126; /* built-in 8x8 coverage */
}

static const my_font_vtable_t s_bitmap_vtable = {bmp_measure, bmp_get_glyph,
                                                 bmp_ascent, bmp_descent,
                                                 bmp_line_height, bmp_destroy,
                                                 bmp_has_glyph, NULL, NULL};

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

/** @brief First face containing cp; the last face when none has it. */
static my_font_t* chain_face_for(my_font_chain_t* c, uint32_t cp) {
  size_t i;
  for (i = 0; i < c->count; i++) {
    if (my_font_has_glyph(c->faces[i], cp)) {
      return c->faces[i];
    }
  }
  return c->faces[c->count - 1];
}

static my_ret_t chain_measure(my_font_t* font, const char* text, int32_t size,
                              int32_t* w, int32_t* h) {
  my_font_chain_t* c = (my_font_chain_t*)font;
  const char* p = text;
  int32_t width = 0;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  while (*p != '\0') {
    uint32_t cp = my_utf8_next(&p);
    char one[8];
    int32_t cw = 0, ch = 0;
    size_t n = 0;
    my_font_t* face = chain_face_for(c, cp);
    /* re-encode the codepoint for the face's own measure */
    if (cp < 0x80) {
      one[n++] = (char)cp;
    } else if (cp < 0x800) {
      one[n++] = (char)(0xC0 | (cp >> 6));
      one[n++] = (char)(0x80 | (cp & 0x3F));
    } else if (cp < 0x10000) {
      one[n++] = (char)(0xE0 | (cp >> 12));
      one[n++] = (char)(0x80 | ((cp >> 6) & 0x3F));
      one[n++] = (char)(0x80 | (cp & 0x3F));
    } else {
      one[n++] = (char)(0xF0 | (cp >> 18));
      one[n++] = (char)(0x80 | ((cp >> 12) & 0x3F));
      one[n++] = (char)(0x80 | ((cp >> 6) & 0x3F));
      one[n++] = (char)(0x80 | (cp & 0x3F));
    }
    one[n] = '\0';
    if (my_font_measure(face, one, size, &cw, &ch) == MY_RET_OK) {
      width += cw;
    }
  }
  if (w != NULL) {
    *w = width;
  }
  if (h != NULL) {
    *h = my_font_line_height(c->faces[0], size);
  }
  return MY_RET_OK;
}

static my_ret_t chain_get_glyph(my_font_t* font, uint32_t codepoint,
                                int32_t size, my_glyph_t* glyph) {
  my_font_chain_t* c = (my_font_chain_t*)font;
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
    int32_t size, bool rtl, const my_allocator_t* allocator,
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
  ret = my_font_shape(face, segment, size, rtl, allocator, &shaped);
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

static my_ret_t chain_shape(my_font_t* font, const char* text, int32_t size,
                            bool rtl, const my_allocator_t* allocator,
                            my_font_shape_result_t* result) {
  my_font_chain_t* c = (my_font_chain_t*)font;
  const char* p = text;
  my_font_t* run_face = NULL;
  size_t run_start = 0;
  size_t capacity = 0;
  my_ret_t ret;
  bool crossed_face = false;

  while (*p != '\0') {
    const char* next = p;
    uint32_t codepoint = my_utf8_next(&next);
    my_font_t* face = chain_face_for(c, codepoint);
    size_t byte = (size_t)(p - text);
    if (run_face == NULL) {
      run_face = face;
      run_start = byte;
    } else if (face != run_face) {
      if (rtl) {
        crossed_face = true;
        break;
      }
      ret = chain_shape_run(run_face, text, run_start, byte, size, false,
                            allocator, result, &capacity);
      if (ret != MY_RET_OK) {
        my_font_shape_destroy(result);
        return ret;
      }
      run_face = face;
      run_start = byte;
    }
    p = next;
  }
  if (!crossed_face) {
    if (run_face != NULL) {
      ret = chain_shape_run(run_face, text, run_start, (size_t)(p - text),
                            size, rtl, allocator, result, &capacity);
      if (ret != MY_RET_OK) {
        my_font_shape_destroy(result);
        return ret;
      }
    }
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
      const char* next = p;
      uint32_t codepoint = my_utf8_next(&next);
      my_font_t* face = chain_face_for(c, codepoint);
      size_t byte = (size_t)(p - text);
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
      p = next;
    }
    if (run_face != NULL) run_count++;
    if (run_count == 0 || run_count > SIZE_MAX / sizeof(*segments)) {
      my_font_shape_destroy(result);
      return run_count == 0 ? MY_RET_FAIL : MY_RET_OOM;
    }
    segments = (chain_shape_segment_t*)my_mem_alloc(
        allocator, run_count * sizeof(*segments));
    if (segments == NULL) {
      my_font_shape_destroy(result);
      return MY_RET_OOM;
    }

    p = text;
    run_face = NULL;
    run_start = 0;
    i = 0;
    while (*p != '\0') {
      const char* next = p;
      uint32_t codepoint = my_utf8_next(&next);
      my_font_t* face = chain_face_for(c, codepoint);
      size_t byte = (size_t)(p - text);
      if (run_face == NULL) {
        run_face = face;
        run_start = byte;
      } else if (face != run_face) {
        segments[i++] = (chain_shape_segment_t){run_face, run_start, byte};
        run_face = face;
        run_start = byte;
      }
      p = next;
    }
    segments[i++] = (chain_shape_segment_t){run_face, run_start,
                                            (size_t)(p - text)};
    for (i = run_count; i > 0; i--) {
      ret = chain_shape_run(segments[i - 1].face, text,
                            segments[i - 1].start, segments[i - 1].end, size,
                            true, allocator, result, &capacity);
      if (ret != MY_RET_OK) {
        my_mem_free(allocator, segments);
        my_font_shape_destroy(result);
        return ret;
      }
    }
    my_mem_free(allocator, segments);
  }
  result->used_complex_shaping = true;
  return MY_RET_OK;
}

static int32_t chain_ascent(my_font_t* font, int32_t size) {
  return my_font_ascent(((my_font_chain_t*)font)->faces[0], size);
}

static int32_t chain_descent(my_font_t* font, int32_t size) {
  my_font_chain_t* c = (my_font_chain_t*)font;
  return c->faces[0]->vtable->descent(c->faces[0], size);
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
    NULL};

my_ret_t my_font_shape(my_font_t* font, const char* text, int32_t size,
                       bool rtl, const my_allocator_t* allocator,
                       my_font_shape_result_t* result) {
  if (result == NULL) return MY_RET_INVALID_PARAMS;
  memset(result, 0, sizeof(*result));
  result->allocator = allocator;
  result->rtl = rtl;
  if (font == NULL || text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (font->vtable == NULL || font->vtable->shape == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  {
    my_ret_t ret =
        font->vtable->shape(font, text, size, rtl, allocator, result);
    result->allocator = allocator;
    if (ret != MY_RET_OK) {
      my_font_shape_destroy(result);
      return ret;
    }
    if (result->count > 0 && result->glyphs == NULL) {
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

void my_font_shape_destroy(my_font_shape_result_t* result) {
  if (result == NULL) return;
  my_mem_free(result->allocator, result->glyphs);
  memset(result, 0, sizeof(*result));
}

my_ret_t my_font_get_glyph_id(my_font_t* font, uint32_t glyph_id,
                              int32_t size, my_glyph_t* glyph) {
  if (font == NULL || glyph == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (font->vtable->get_glyph_id == NULL) return MY_RET_NOT_SUPPORTED;
  return font->vtable->get_glyph_id(font, glyph_id, size, glyph);
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
  if (f == NULL && source->face_index == 0) {
    f = my_font_stb_create(allocator, source->path, cache_capacity);
  }
  return f;
}

my_font_t* my_font_create_chain_ex(const my_allocator_t* allocator,
                                   const my_font_source_t* sources,
                                   size_t source_count,
                                   size_t cache_capacity) {
  my_font_chain_t* c;
  size_t i;
  if (sources == NULL || source_count == 0) {
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

  if (paths == NULL || path_count == 0) {
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
