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
} my_font_bitmap_t;

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
  static const uint8_t blank[8] = {0};
  (void)font;
  if (glyph == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (codepoint < 32 || codepoint > 126) {
    /* non-ASCII: hollow box fallback glyph */
    static const uint8_t box[8] = {0xFE, 0x82, 0x82, 0x82, 0x82, 0x82, 0xFE, 0};
    glyph->bitmap = box;
    glyph->w = 8;
    glyph->h = 8;
  } else if (codepoint == 32) {
    glyph->bitmap = blank;
    glyph->w = 8;
    glyph->h = 8;
  } else {
    glyph->bitmap = MY_FONT_BITMAP_DATA[codepoint - 32];
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
  if (f == NULL) {
    return NULL;
  }
  f->base.vtable = &s_bitmap_vtable;
  f->allocator = allocator;
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
    chain_line_height, chain_destroy, NULL /* per-face has_glyph */, NULL,
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
  if (font->vtable->shape == NULL) return MY_RET_NOT_SUPPORTED;
  return font->vtable->shape(font, text, size, rtl, allocator, result);
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
