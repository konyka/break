/**
 * @file my_font_stb.c
 * @brief stb_truetype font backend with an LRU glyph cache.
 */
#include "myr/my_font.h"

#ifdef MYUI_FONT_STB

#include <stdio.h>
#include <string.h>

#include <stb_truetype.h>

#define MY_FONT_STB_DEFAULT_CACHE 256

typedef struct glyph_cache_entry_t {
  uint32_t codepoint;
  int32_t size;
  uint8_t* bitmap; /**< owned, w*h bytes (NULL for blank) */
  int32_t w, h, bearing_x, bearing_y, advance;
  uint64_t last_used;
  bool occupied;
} glyph_cache_entry_t;

typedef struct my_font_stb_t {
  my_font_t base;
  const my_allocator_t* allocator;
  uint8_t* ttf_data; /**< owned; stbtt_fontinfo points into it */
  stbtt_fontinfo info;
  glyph_cache_entry_t* cache;
  size_t cache_capacity;
  uint64_t tick;
  size_t hits;
  size_t misses;
} my_font_stb_t;

static float stb_scale(my_font_stb_t* f, int32_t size) {
  return stbtt_ScaleForPixelHeight(&f->info, (float)size);
}

/* ---------------- vtable ---------------- */

static my_ret_t stb_measure(my_font_t* font, const char* text, int32_t size,
                            int32_t* w, int32_t* h) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  const char* p = text;
  float scale;
  float width = 0.0f;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  scale = stb_scale(f, size);
  while (*p != '\0') {
    uint32_t cp = my_utf8_next(&p);
    int adv, lsb;
    stbtt_GetCodepointHMetrics(&f->info, (int)cp, &adv, &lsb);
    width += (float)adv * scale;
  }
  if (w != NULL) {
    *w = (int32_t)(width + 0.5f);
  }
  if (h != NULL) {
    *h = my_font_line_height(font, size);
  }
  return MY_RET_OK;
}

static glyph_cache_entry_t* cache_lookup(my_font_stb_t* f, uint32_t cp,
                                         int32_t size) {
  size_t i;
  for (i = 0; i < f->cache_capacity; i++) {
    glyph_cache_entry_t* e = &f->cache[i];
    if (e->occupied && e->codepoint == cp && e->size == size) {
      e->last_used = ++f->tick;
      f->hits++;
      return e;
    }
  }
  f->misses++;
  return NULL;
}

static glyph_cache_entry_t* cache_slot(my_font_stb_t* f) {
  size_t i;
  glyph_cache_entry_t* lru = &f->cache[0];
  for (i = 0; i < f->cache_capacity; i++) {
    if (!f->cache[i].occupied) {
      return &f->cache[i];
    }
    if (f->cache[i].last_used < lru->last_used) {
      lru = &f->cache[i];
    }
  }
  my_mem_free(f->allocator, lru->bitmap); /* evict LRU */
  lru->bitmap = NULL;
  return lru;
}

static my_ret_t stb_get_glyph(my_font_t* font, uint32_t codepoint, int32_t size,
                              my_glyph_t* glyph) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  glyph_cache_entry_t* e;
  int adv, lsb;
  float scale;
  if (glyph == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  e = cache_lookup(f, codepoint, size);
  if (e == NULL) {
    int bw, bh, xoff, yoff;
    uint8_t* bm;
    scale = stb_scale(f, size);
    bm = stbtt_GetCodepointBitmap(&f->info, scale, scale, (int)codepoint, &bw,
                                  &bh, &xoff, &yoff);
    e = cache_slot(f);
    e->occupied = true;
    e->codepoint = codepoint;
    e->size = size;
    e->w = bw;
    e->h = bh;
    e->bearing_x = xoff;
    e->bearing_y = -yoff; /* stb yoff is baseline-relative top, negative up */
    stbtt_GetCodepointHMetrics(&f->info, (int)codepoint, &adv, &lsb);
    e->advance = (int32_t)((float)adv * scale + 0.5f);
    e->bitmap = NULL;
    if (bm != NULL && bw > 0 && bh > 0) {
      size_t bytes = (size_t)bw * (size_t)bh;
      e->bitmap = (uint8_t*)my_mem_alloc(f->allocator, bytes);
      if (e->bitmap != NULL) {
        memcpy(e->bitmap, bm, bytes);
      }
    }
    stbtt_FreeBitmap(bm, NULL);
    e->last_used = ++f->tick;
  }
  glyph->bitmap = e->bitmap;
  glyph->w = e->w;
  glyph->h = e->h;
  glyph->bearing_x = e->bearing_x;
  glyph->bearing_y = e->bearing_y;
  glyph->advance = e->advance;
  return MY_RET_OK;
}

static int32_t stb_ascent(my_font_t* font, int32_t size) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  int ascent, descent, gap;
  stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &gap);
  return (int32_t)((float)ascent * stb_scale(f, size) + 0.5f);
}

static int32_t stb_descent(my_font_t* font, int32_t size) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  int ascent, descent, gap;
  stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &gap);
  return (int32_t)((float)descent * stb_scale(f, size) - 0.5f);
}

static int32_t stb_line_height(my_font_t* font, int32_t size) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  int ascent, descent, gap;
  stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &gap);
  return (int32_t)((float)(ascent - descent + gap) * stb_scale(f, size) + 0.5f);
}

static void stb_destroy(my_font_t* font) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  size_t i;
  if (f == NULL) {
    return;
  }
  for (i = 0; i < f->cache_capacity; i++) {
    my_mem_free(f->allocator, f->cache[i].bitmap);
  }
  my_mem_free(f->allocator, f->cache);
  my_mem_free(f->allocator, f->ttf_data);
  my_mem_free(f->allocator, f);
}

static bool stb_has_glyph(my_font_t* font, uint32_t codepoint) {
  my_font_stb_t* f = (my_font_stb_t*)font;
  return stbtt_FindGlyphIndex(&f->info, (int)codepoint) != 0;
}

static const my_font_vtable_t s_stb_vtable = {stb_measure, stb_get_glyph,
                                              stb_ascent, stb_descent,
                                              stb_line_height, stb_destroy,
                                              stb_has_glyph, NULL, NULL};

my_font_t* my_font_stb_create(const my_allocator_t* allocator, const char* path,
                              size_t cache_capacity) {
  my_font_stb_t* f;
  FILE* file;
  long size;
  if (path == NULL) {
    return NULL;
  }
  file = fopen(path, "rb");
  if (file == NULL) {
    return NULL;
  }
  f = (my_font_stb_t*)my_mem_calloc(allocator, 1, sizeof(my_font_stb_t));
  if (f == NULL) {
    fclose(file);
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);
  f->ttf_data = (uint8_t*)my_mem_alloc(allocator, (size_t)size);
  if (f->ttf_data == NULL || fread(f->ttf_data, 1, (size_t)size, file) != (size_t)size) {
    fclose(file);
    my_mem_free(allocator, f->ttf_data);
    my_mem_free(allocator, f);
    return NULL;
  }
  fclose(file);
  {
    int offset = 0;
    /* TrueType Collection (.ttc): take the first face (stb needs the
     * face offset; "ttcf" header at 0 is not a font) */
    if (size >= 4 && f->ttf_data[0] == 't' && f->ttf_data[1] == 't' &&
        f->ttf_data[2] == 'c' && f->ttf_data[3] == 'f') {
      offset = stbtt_GetFontOffsetForIndex(f->ttf_data, 0);
      if (offset < 0) {
        offset = 0;
      }
    }
    if (!stbtt_InitFont(&f->info, f->ttf_data, offset)) {
      my_mem_free(allocator, f->ttf_data);
      my_mem_free(allocator, f);
      return NULL;
    }
  }
  f->base.vtable = &s_stb_vtable;
  f->allocator = allocator;
  f->cache_capacity = cache_capacity > 0 ? cache_capacity
                                         : MY_FONT_STB_DEFAULT_CACHE;
  f->cache = (glyph_cache_entry_t*)my_mem_calloc(allocator, f->cache_capacity,
                                                 sizeof(glyph_cache_entry_t));
  if (f->cache == NULL) {
    my_mem_free(allocator, f->ttf_data);
    my_mem_free(allocator, f);
    return NULL;
  }
  return (my_font_t*)f;
}

#else /* !MYUI_FONT_STB */

my_font_t* my_font_stb_create(const my_allocator_t* allocator, const char* path,
                              size_t cache_capacity) {
  (void)allocator;
  (void)path;
  (void)cache_capacity;
  return NULL;
}

#endif /* MYUI_FONT_STB */

size_t my_font_stb_cache_hits(my_font_t* font) {
#ifdef MYUI_FONT_STB
  my_font_stb_t* f = (my_font_stb_t*)font;
  return f != NULL && f->base.vtable == &s_stb_vtable ? f->hits : 0;
#else
  (void)font;
  return 0;
#endif
}

size_t my_font_stb_cache_misses(my_font_t* font) {
#ifdef MYUI_FONT_STB
  my_font_stb_t* f = (my_font_stb_t*)font;
  return f != NULL && f->base.vtable == &s_stb_vtable ? f->misses : 0;
#else
  (void)font;
  return 0;
#endif
}
