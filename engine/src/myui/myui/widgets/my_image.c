/**
 * @file my_image.c
 * @brief Image widget with a path-keyed LRU decode cache.
 */
#include "myui/widgets/my_image.h"

#include <string.h>

#include "myc/my_str.h"

/* ---------------- decode cache (global, LRU) ---------------- */

#define MY_IMAGE_CACHE_SIZE 8

typedef struct image_cache_entry_t {
  char* path;
  uint8_t* pixels; /**< RGBA8888 */
  int32_t w, h;
  uint64_t last_used;
  bool occupied;
} image_cache_entry_t;

static image_cache_entry_t g_cache[MY_IMAGE_CACHE_SIZE];
static uint64_t g_cache_tick = 0;
static size_t g_cache_hits = 0;
static size_t g_cache_misses = 0;
static my_image_loader_t* g_default_loader = NULL;

void my_image_cache_stats(size_t* hits, size_t* misses) {
  if (hits != NULL) {
    *hits = g_cache_hits;
  }
  if (misses != NULL) {
    *misses = g_cache_misses;
  }
}

static my_image_loader_t* default_loader(void) {
  if (g_default_loader == NULL) {
    g_default_loader = my_image_loader_stb_create(NULL);
  }
  return g_default_loader;
}

/** @brief Decoded image ref into the cache (owned by the cache). */
typedef struct cached_image_t {
  const uint8_t* pixels;
  int32_t w;
  int32_t h;
} cached_image_t;

static bool cache_get(my_image_loader_t* loader, const char* path,
                      cached_image_t* out) {
  size_t i;
  image_cache_entry_t* lru = &g_cache[0];
  for (i = 0; i < MY_IMAGE_CACHE_SIZE; i++) {
    image_cache_entry_t* e = &g_cache[i];
    if (!e->occupied) {
      lru = e;
      continue;
    }
    if (e->last_used < lru->last_used) {
      lru = e;
    }
    if (my_str_eq(e->path, path)) {
      e->last_used = ++g_cache_tick;
      g_cache_hits++;
      out->pixels = e->pixels;
      out->w = e->w;
      out->h = e->h;
      return true;
    }
  }
  g_cache_misses++;
  if (loader == NULL) {
    return false;
  }
  {
    my_image_data_t* data = my_image_loader_load(loader, path);
    if (data == NULL) {
      return false;
    }
    if (lru->occupied) {
      my_mem_free(NULL, lru->path);
      my_mem_free(NULL, lru->pixels);
    }
    lru->occupied = true;
    lru->path = my_strdup(NULL, path);
    lru->pixels = data->pixels;
    lru->w = data->w;
    lru->h = data->h;
    lru->last_used = ++g_cache_tick;
    my_mem_free(NULL, data); /* pixels taken over by the cache */
    out->pixels = lru->pixels;
    out->w = lru->w;
    out->h = lru->h;
    return true;
  }
}

/* ---------------- widget ---------------- */

static my_ret_t image_on_paint_blit(my_widget_t* widget, my_vgcanvas_t* vg,
                                    const cached_image_t* img, int32_t dx,
                                    int32_t dy, int32_t dw, int32_t dh) {
  my_image_t* im = (my_image_t*)widget;
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                          0x00000000u);
  my_color_t bgc = my_color_from_rgba32(bg);
  (void)my_vgcanvas_set_scale_filter(vg, im->scale_filter);
  return my_vgcanvas_draw_image(vg, img->pixels, img->w, img->h,
                                &(my_rectf_t){(float)dx, (float)dy, (float)dw,
                                              (float)dh},
                                bgc.a > 0 ? &bgc : NULL);
}

static void image_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_image_t* im = (my_image_t*)widget;
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                          0x00000000u);
  cached_image_t img;
  int32_t dw, dh, dx, dy;
  my_color_t bgc = my_color_from_rgba32(bg);

  if (bgc.a > 0) {
    my_vgcanvas_set_fill_color(vg, bgc);
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  }
  if (im->path == NULL ||
      !cache_get(im->loader != NULL ? im->loader : default_loader(), im->path,
                 &img)) {
    /* placeholder: empty frame box */
    my_vgcanvas_set_stroke_color(vg, my_color_rgb(150, 150, 150));
    my_vgcanvas_set_line_width(vg, 1);
    my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                              (float)widget->rect.h});
    return;
  }

  switch (im->scale_mode) {
    case MY_IMAGE_SCALE_NONE:
      dw = img.w;
      dh = img.h;
      dx = 0;
      dy = 0;
      break;
    case MY_IMAGE_SCALE_CENTER:
      dw = img.w;
      dh = img.h;
      dx = (widget->rect.w - img.w) / 2;
      dy = (widget->rect.h - img.h) / 2;
      break;
    case MY_IMAGE_SCALE_FILL:
      dw = widget->rect.w;
      dh = widget->rect.h;
      dx = 0;
      dy = 0;
      break;
    case MY_IMAGE_SCALE_FIT:
    default: {
      float sx = (float)widget->rect.w / (float)img.w;
      float sy = (float)widget->rect.h / (float)img.h;
      float s = sx < sy ? sx : sy;
      dw = (int32_t)(img.w * s);
      dh = (int32_t)(img.h * s);
      dx = (widget->rect.w - dw) / 2;
      dy = (widget->rect.h - dh) / 2;
      break;
    }
  }
  if (dw <= 0 || dh <= 0) {
    return;
  }
  image_on_paint_blit(widget, vg, &img, dx, dy, dw, dh);
}

static const my_widget_vtable_t s_image_vtable = {image_on_paint, NULL, NULL, NULL};

static void image_destroy_chain(my_object_t* obj) {
  my_image_t* im = (my_image_t*)obj;
  my_mem_free(im->allocator, im->path);
  my_widget_destroy((my_widget_t*)im);
  my_object_destroy(obj);
}

my_widget_t* my_image_create(const my_allocator_t* allocator) {
  my_image_t* im = (my_image_t*)my_mem_calloc(allocator, 1, sizeof(my_image_t));
  if (im == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)im, allocator, &s_image_vtable, "image") !=
      MY_RET_OK) {
    my_mem_free(allocator, im);
    return NULL;
  }
  ((my_object_t*)im)->destroy = image_destroy_chain;
  im->allocator = allocator;
  im->scale_mode = MY_IMAGE_SCALE_FIT;
  im->scale_filter = MY_SCALE_FILTER_BILINEAR;
  ((my_widget_t*)im)->enable = false;
  ((my_widget_t*)im)->widget_type = "image";
  return (my_widget_t*)im;
}

my_ret_t my_image_set_image(my_widget_t* image, const char* path) {
  my_image_t* im = (my_image_t*)image;
  char* copy;
  if (image == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  copy = my_strdup(im->allocator, path);
  if (path != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(im->allocator, im->path);
  im->path = copy;
  my_widget_invalidate(image, NULL);
  return MY_RET_OK;
}

my_ret_t my_image_set_scale_mode(my_widget_t* image, my_image_scale_t mode) {
  if (image == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_image_t*)image)->scale_mode = mode;
  my_widget_invalidate(image, NULL);
  return MY_RET_OK;
}

my_ret_t my_image_set_scale_filter(my_widget_t* image,
                                   my_scale_filter_t filter) {
  if (image == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_image_t*)image)->scale_filter = filter;
  my_widget_invalidate(image, NULL);
  return MY_RET_OK;
}

my_ret_t my_image_set_loader(my_widget_t* image, my_image_loader_t* loader) {
  if (image == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_image_t*)image)->loader = loader;
  return MY_RET_OK;
}
