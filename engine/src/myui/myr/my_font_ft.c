/**
 * @file my_font_ft.c
 * @brief FreeType font backend (M16): hinted glyph rendering with an
 * LRU cache (same structure as the stb backend).
 */
#include "myr/my_font_ft.h"

#ifdef MYUI_FONT_FREETYPE

#include <string.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MULTIPLE_MASTERS_H
#ifdef MYUI_FONT_HARFBUZZ
#include <hb.h>
#include <hb-ft.h>
#endif

#define MY_FONT_FT_DEFAULT_CACHE 256

typedef struct ft_cache_entry_t {
  uint32_t codepoint;
  bool key_is_glyph_id;
  int32_t size;
  uint8_t* bitmap; /**< owned, w*h bytes (NULL for blank) */
  int32_t w, h, bearing_x, bearing_y, advance;
  uint64_t last_used;
  bool occupied;
} ft_cache_entry_t;

typedef struct my_font_ft_t {
  my_font_t base;
  const my_allocator_t* allocator;
  FT_Face face;
  int32_t cur_size; /**< last FT_Set_Pixel_Sizes size (0 = unset) */
  ft_cache_entry_t* cache;
  size_t cache_capacity;
  uint64_t tick;
  size_t hits;
  size_t misses;
} my_font_ft_t;

/** @brief One process-wide library is enough (single-threaded UI). */
static FT_Library s_ft_lib;
static int s_ft_lib_state; /**< 0 = untried, 1 = ready, -1 = failed */

static FT_Library ft_library(void) {
  if (s_ft_lib_state == 0) {
    s_ft_lib_state = FT_Init_FreeType(&s_ft_lib) == 0 ? 1 : -1;
  }
  return s_ft_lib_state == 1 ? s_ft_lib : NULL;
}

static void ft_set_size(my_font_ft_t* f, int32_t size) {
  if (f->cur_size != size) {
    FT_Set_Pixel_Sizes(f->face, 0, (FT_UInt)size);
    f->cur_size = size;
  }
}

/* ---------------- vtable ---------------- */

static my_ret_t ft_measure(my_font_t* font, const char* text, int32_t size,
                           int32_t* w, int32_t* h) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  const char* p = text;
  int32_t width = 0;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  ft_set_size(f, size);
  while (*p != '\0') {
    uint32_t cp = my_utf8_next(&p);
    if (FT_Load_Char(f->face, cp, FT_LOAD_DEFAULT) == 0) {
      width += (int32_t)(f->face->glyph->advance.x >> 6);
    }
  }
  if (w != NULL) {
    *w = width;
  }
  if (h != NULL) {
    *h = my_font_line_height(font, size);
  }
  return MY_RET_OK;
}

static ft_cache_entry_t* ft_cache_lookup(my_font_ft_t* f, uint32_t cp,
                                         int32_t size) {
  size_t i;
  for (i = 0; i < f->cache_capacity; i++) {
    ft_cache_entry_t* e = &f->cache[i];
    if (e->occupied && !e->key_is_glyph_id && e->codepoint == cp &&
        e->size == size) {
      e->last_used = ++f->tick;
      f->hits++;
      return e;
    }
  }
  f->misses++;
  return NULL;
}

static ft_cache_entry_t* ft_cache_slot(my_font_ft_t* f);

static ft_cache_entry_t* ft_cache_lookup_glyph(my_font_ft_t* f,
                                                uint32_t glyph_id,
                                                int32_t size) {
  size_t i;
  for (i = 0; i < f->cache_capacity; i++) {
    ft_cache_entry_t* e = &f->cache[i];
    if (e->occupied && e->key_is_glyph_id && e->codepoint == glyph_id &&
        e->size == size) {
      e->last_used = ++f->tick;
      f->hits++;
      return e;
    }
  }
  f->misses++;
  return NULL;
}

static my_ret_t ft_raster_glyph(my_font_ft_t* f, uint32_t cache_key,
                                uint32_t glyph_id, int32_t size,
                                bool key_is_glyph_id,
                                my_glyph_t* glyph) {
  ft_cache_entry_t* e = key_is_glyph_id
                            ? ft_cache_lookup_glyph(f, cache_key, size)
                            : ft_cache_lookup(f, cache_key, size);
  if (e == NULL) {
    FT_GlyphSlot slot;
    ft_set_size(f, size);
    if (FT_Load_Glyph(f->face, glyph_id, FT_LOAD_DEFAULT) != 0 ||
        FT_Render_Glyph(f->face->glyph, FT_RENDER_MODE_NORMAL) != 0) {
      return MY_RET_FAIL;
    }
    slot = f->face->glyph;
    e = ft_cache_slot(f);
    e->occupied = true;
    e->key_is_glyph_id = key_is_glyph_id;
    e->codepoint = cache_key;
    e->size = size;
    e->w = (int32_t)slot->bitmap.width;
    e->h = (int32_t)slot->bitmap.rows;
    e->bearing_x = slot->bitmap_left;
    e->bearing_y = slot->bitmap_top;
    e->advance = (int32_t)(slot->advance.x >> 6);
    e->bitmap = NULL;
    if (e->w > 0 && e->h > 0) {
      size_t bytes = (size_t)e->w * (size_t)e->h;
      e->bitmap = (uint8_t*)my_mem_alloc(f->allocator, bytes);
      if (e->bitmap != NULL) {
        int32_t row;
        for (row = 0; row < e->h; row++) {
          memcpy(e->bitmap + (size_t)row * (size_t)e->w,
                 slot->bitmap.buffer + (size_t)row * (size_t)slot->bitmap.pitch,
                 (size_t)e->w);
        }
      }
    }
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

static ft_cache_entry_t* ft_cache_slot(my_font_ft_t* f) {
  size_t i;
  ft_cache_entry_t* lru = &f->cache[0];
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

static my_ret_t ft_get_glyph(my_font_t* font, uint32_t codepoint, int32_t size,
                             my_glyph_t* glyph) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  if (glyph == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  {
    FT_UInt glyph_id = FT_Get_Char_Index(f->face, codepoint);
    if (glyph_id == 0u) return MY_RET_NOT_FOUND;
    return ft_raster_glyph(f, codepoint, glyph_id, size, false, glyph);
  }
}

static my_ret_t ft_get_glyph_id(my_font_t* font, uint32_t glyph_id,
                                int32_t size, my_glyph_t* glyph) {
  if (glyph_id == 0u) return MY_RET_NOT_FOUND;
  return ft_raster_glyph((my_font_ft_t*)font, glyph_id, glyph_id, size, true,
                         glyph);
}

static int32_t ft_ascent(my_font_t* font, int32_t size) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  ft_set_size(f, size);
  return (int32_t)(f->face->size->metrics.ascender >> 6);
}

static int32_t ft_descent(my_font_t* font, int32_t size) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  ft_set_size(f, size);
  return (int32_t)(f->face->size->metrics.descender >> 6);
}

static int32_t ft_line_height(my_font_t* font, int32_t size) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  ft_set_size(f, size);
  return (int32_t)(f->face->size->metrics.height >> 6);
}

static my_ret_t ft_shape(my_font_t* font, const char* text, int32_t size,
                         bool rtl, const my_allocator_t* allocator,
                         my_font_shape_result_t* result) {
#ifdef MYUI_FONT_HARFBUZZ
  my_font_ft_t* f = (my_font_ft_t*)font;
  hb_font_t* hb_font;
  hb_buffer_t* buffer;
  unsigned int count = 0;
  const hb_glyph_info_t* infos;
  const hb_glyph_position_t* positions;
  unsigned int i;
  if (text == NULL || size <= 0 || result == NULL) return MY_RET_INVALID_PARAMS;
  ft_set_size(f, size);
  hb_font = hb_ft_font_create_referenced(f->face);
  buffer = hb_buffer_create();
  if (hb_font == NULL || buffer == NULL ||
      !hb_buffer_allocation_successful(buffer)) {
    if (buffer != NULL) hb_buffer_destroy(buffer);
    if (hb_font != NULL) hb_font_destroy(hb_font);
    return MY_RET_OOM;
  }
  hb_buffer_add_utf8(buffer, text, -1, 0, -1);
  hb_buffer_set_direction(buffer, rtl ? HB_DIRECTION_RTL : HB_DIRECTION_LTR);
  hb_buffer_guess_segment_properties(buffer);
  hb_shape(hb_font, buffer, NULL, 0);
  infos = hb_buffer_get_glyph_infos(buffer, &count);
  positions = hb_buffer_get_glyph_positions(buffer, &count);
  if (count > 0) {
    result->glyphs = (my_font_shape_glyph_t*)my_mem_alloc(
        allocator, (size_t)count * sizeof(*result->glyphs));
    if (result->glyphs == NULL) {
      hb_buffer_destroy(buffer);
      hb_font_destroy(hb_font);
      return MY_RET_OOM;
    }
  }
  result->allocator = allocator;
  result->count = count;
  result->used_complex_shaping = true;
  for (i = 0; i < count; i++) {
    result->glyphs[i].font = font;
    result->glyphs[i].glyph_id = infos[i].codepoint;
    result->glyphs[i].cluster = infos[i].cluster;
    result->glyphs[i].advance_x_26_6 = positions[i].x_advance;
    result->glyphs[i].offset_x_26_6 = positions[i].x_offset;
    result->glyphs[i].offset_y_26_6 = positions[i].y_offset;
  }
  hb_buffer_destroy(buffer);
  hb_font_destroy(hb_font);
  return MY_RET_OK;
#else
  (void)font; (void)text; (void)size; (void)rtl; (void)allocator;
  (void)result;
  return MY_RET_NOT_SUPPORTED;
#endif
}

static void ft_destroy(my_font_t* font) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  size_t i;
  if (f == NULL) {
    return;
  }
  for (i = 0; i < f->cache_capacity; i++) {
    my_mem_free(f->allocator, f->cache[i].bitmap);
  }
  my_mem_free(f->allocator, f->cache);
  if (f->face != NULL) {
    FT_Done_Face(f->face);
  }
  my_mem_free(f->allocator, f);
}

static bool ft_has_glyph(my_font_t* font, uint32_t codepoint) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  return FT_Get_Char_Index(f->face, codepoint) != 0;
}

static const my_font_vtable_t s_ft_vtable = {ft_measure,  ft_get_glyph,
                                             ft_ascent,   ft_descent,
                                             ft_line_height, ft_destroy,
                                             ft_has_glyph, ft_shape,
                                             ft_get_glyph_id};

my_font_t* my_font_ft_create_ex(const my_allocator_t* allocator,
                                const char* path, int32_t face_index,
                                int32_t weight, size_t cache_capacity) {
  my_font_ft_t* f;
  FT_Library lib = ft_library();
  if (lib == NULL || path == NULL) {
    return NULL;
  }
  f = (my_font_ft_t*)my_mem_calloc(allocator, 1, sizeof(my_font_ft_t));
  if (f == NULL) {
    return NULL;
  }
  if (FT_New_Face(lib, path, face_index, &f->face) != 0) {
    my_mem_free(allocator, f);
    return NULL;
  }
  if (weight > 0) { /* variable font: pin the wght axis (0 = font default) */
    FT_MM_Var* mm = NULL;
    if (FT_Get_MM_Var(f->face, &mm) == 0 && mm != NULL) {
      FT_Fixed* coords = (FT_Fixed*)my_mem_calloc(allocator, mm->num_axis,
                                                  sizeof(FT_Fixed));
      FT_UInt i;
      for (i = 0; i < mm->num_axis; i++) {
        coords[i] = mm->axis[i].def;
        if (mm->axis[i].tag == 0x77676874u) { /* 'wght' */
          FT_Fixed w = (FT_Fixed)(weight << 16);
          if (w < mm->axis[i].minimum) {
            w = mm->axis[i].minimum;
          }
          if (w > mm->axis[i].maximum) {
            w = mm->axis[i].maximum;
          }
          coords[i] = w;
        }
      }
      FT_Set_Var_Design_Coordinates(f->face, mm->num_axis, coords);
      my_mem_free(allocator, coords);
      FT_Done_MM_Var(lib, mm);
    }
  }
  f->base.vtable = &s_ft_vtable;
  f->allocator = allocator;
  f->cache_capacity = cache_capacity > 0 ? cache_capacity
                                         : MY_FONT_FT_DEFAULT_CACHE;
  f->cache = (ft_cache_entry_t*)my_mem_calloc(allocator, f->cache_capacity,
                                              sizeof(ft_cache_entry_t));
  if (f->cache == NULL) {
    FT_Done_Face(f->face);
    my_mem_free(allocator, f);
    return NULL;
  }
  return (my_font_t*)f;
}

my_font_t* my_font_ft_create(const my_allocator_t* allocator,
                             const char* path, int32_t face_index,
                             size_t cache_capacity) {
  return my_font_ft_create_ex(allocator, path, face_index, 0, cache_capacity);
}

#else /* !MYUI_FONT_FREETYPE */

my_font_t* my_font_ft_create_ex(const my_allocator_t* allocator,
                                const char* path, int32_t face_index,
                                int32_t weight, size_t cache_capacity) {
  (void)allocator;
  (void)weight;
  (void)path;
  (void)face_index;
  (void)cache_capacity;
  return NULL;
}

my_font_t* my_font_ft_create(const my_allocator_t* allocator,
                             const char* path, int32_t face_index,
                             size_t cache_capacity) {
  return my_font_ft_create_ex(allocator, path, face_index, 0, cache_capacity);
}

#endif /* MYUI_FONT_FREETYPE */

size_t my_font_ft_cache_hits(my_font_t* font) {
#ifdef MYUI_FONT_FREETYPE
  my_font_ft_t* f = (my_font_ft_t*)font;
  return f != NULL && f->base.vtable == &s_ft_vtable ? f->hits : 0;
#else
  (void)font;
  return 0;
#endif
}

size_t my_font_ft_cache_misses(my_font_t* font) {
#ifdef MYUI_FONT_FREETYPE
  my_font_ft_t* f = (my_font_ft_t*)font;
  return f != NULL && f->base.vtable == &s_ft_vtable ? f->misses : 0;
#else
  (void)font;
  return 0;
#endif
}
