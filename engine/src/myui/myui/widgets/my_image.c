/**
 * @file my_image.c
 * @brief Image widget with a path-keyed LRU decode cache.
 */
#include "myui/widgets/my_image.h"
#include "myr/my_ui_metrics.h"

#include <stdatomic.h>
#include <string.h>

#include "myc/my_str.h"

/* ---------------- decode cache (global, LRU) ---------------- */

#define MY_IMAGE_CACHE_SIZE 8

typedef struct image_cache_entry_t {
  my_image_loader_t* loader;
  my_image_loader_lease_t* lease;
  char* path;
  uint8_t* pixels; /**< RGBA8888 */
  int32_t w, h;
  uint64_t last_used;
  bool occupied;
} image_cache_entry_t;

typedef struct image_cache_state_t {
  image_cache_entry_t entries[MY_IMAGE_CACHE_SIZE];
  uint64_t tick;
} image_cache_state_t;

static _Thread_local image_cache_state_t g_cache;
static atomic_size_t g_cache_hits;
static atomic_size_t g_cache_misses;
static _Atomic(my_image_loader_t*) g_default_loader;

static bool image_loader_valid(const my_image_loader_t* loader) {
  return my_image_loader_is_valid(loader);
}

static void image_cache_drop_entry(image_cache_entry_t* entry) {
  if (entry == NULL || !entry->occupied) {
    return;
  }
  my_mem_free(NULL, entry->path);
  my_mem_free(NULL, entry->pixels);
  my_image_loader_lease_unref(entry->lease);
  memset(entry, 0, sizeof(*entry));
}

void my_image_cache_stats(size_t* hits, size_t* misses) {
  if (hits != NULL) {
    *hits = atomic_load_explicit(&g_cache_hits, memory_order_relaxed);
  }
  if (misses != NULL) {
    *misses = atomic_load_explicit(&g_cache_misses, memory_order_relaxed);
  }
}

void my_image_cache_clear(void) {
  size_t i;
  for (i = 0; i < MY_IMAGE_CACHE_SIZE; i++) {
    image_cache_drop_entry(&g_cache.entries[i]);
  }
}

static my_image_loader_t* default_loader(void) {
  my_image_loader_t* loader =
      atomic_load_explicit(&g_default_loader, memory_order_acquire);
  if (loader == NULL) {
    my_image_loader_t* candidate = my_image_loader_stb_create(NULL);
    if (candidate == NULL) {
      return NULL;
    }
    if (!atomic_compare_exchange_strong_explicit(
            &g_default_loader, &loader, candidate, memory_order_release,
            memory_order_acquire)) {
      my_image_loader_destroy(candidate);
    } else {
      loader = candidate;
    }
  }
  return loader;
}

/** @brief Decoded image ref into the cache (owned by the cache). */
typedef struct cached_image_t {
  const uint8_t* pixels;
  int32_t w;
  int32_t h;
  my_image_data_t* transient;
  my_image_loader_t* transient_loader;
} cached_image_t;

static void image_release_transient(cached_image_t* image) {
  if (image != NULL && image->transient != NULL &&
      image->transient_loader != NULL) {
    my_image_loader_free_data(image->transient_loader, image->transient);
    image->transient = NULL;
    image->transient_loader = NULL;
  }
}

static bool cache_get(my_image_loader_t* loader, my_image_loader_lease_t* lease,
                      const char* path,
                      cached_image_t* out) {
  size_t i;
  image_cache_entry_t* lru = &g_cache.entries[0];
  if (image_loader_valid(loader)) {
    my_image_loader_t* default_loader_instance =
        atomic_load_explicit(&g_default_loader, memory_order_acquire);
    bool cacheable = lease != NULL || loader == default_loader_instance;
    if (cacheable) {
      for (i = 0; i < MY_IMAGE_CACHE_SIZE; i++) {
        image_cache_entry_t* e = &g_cache.entries[i];
        if (!e->occupied) {
          lru = e;
          continue;
        }
        if (e->last_used < lru->last_used) {
          lru = e;
        }
        if (e->loader == loader && e->lease == lease &&
            my_str_eq(e->path, path)) {
          e->last_used = ++g_cache.tick;
          atomic_fetch_add_explicit(&g_cache_hits, 1u, memory_order_relaxed);
          out->pixels = e->pixels;
          out->w = e->w;
          out->h = e->h;
          return true;
        }
      }
    }
  }
  atomic_fetch_add_explicit(&g_cache_misses, 1u, memory_order_relaxed);
  my_ui_metrics_record_image_cache_miss();
  if (!image_loader_valid(loader)) {
    return false;
  }
  {
    my_image_data_t* data = my_image_loader_load(loader, path);
    if (data == NULL) {
      return false;
    }
    if (lease == NULL &&
        loader != atomic_load_explicit(&g_default_loader, memory_order_acquire)) {
      if (data->pixels == NULL || data->w <= 0 || data->h <= 0) {
        my_image_loader_free_data(loader, data);
        return false;
      }
      out->pixels = data->pixels;
      out->w = data->w;
      out->h = data->h;
      out->transient = data;
      out->transient_loader = loader;
      return true;
    }
    if (data->pixels != NULL && data->w > 0 && data->h > 0 &&
        (size_t)data->w <= SIZE_MAX / (size_t)data->h &&
        (size_t)data->w * (size_t)data->h <= SIZE_MAX / 4u) {
      int32_t data_w = data->w;
      int32_t data_h = data->h;
      size_t pixel_bytes = (size_t)data->w * (size_t)data->h * 4u;
      uint8_t* pixels = (uint8_t*)my_mem_alloc(NULL, pixel_bytes);
      char* key = my_strdup(NULL, path);
      if (pixels != NULL && key != NULL) {
        memcpy(pixels, data->pixels, pixel_bytes);
        my_image_loader_free_data(loader, data);
        image_cache_drop_entry(lru);
        lru->loader = loader;
        lru->lease = my_image_loader_lease_ref(lease);
        lru->occupied = true;
        lru->path = key;
        lru->pixels = pixels;
        lru->w = data_w;
        lru->h = data_h;
        lru->last_used = ++g_cache.tick;
        out->pixels = lru->pixels;
        out->w = lru->w;
        out->h = lru->h;
        return true;
      }
      my_mem_free(NULL, key);
      my_mem_free(NULL, pixels);
    }
    my_image_loader_free_data(loader, data);
    return false;
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
  cached_image_t img = {0};
  int32_t dw, dh, dx, dy;
  my_color_t bgc = my_color_from_rgba32(bg);

  if (bgc.a > 0) {
    my_vgcanvas_set_fill_color(vg, bgc);
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  }
  {
    my_image_loader_t* loader = im->loader != NULL ? im->loader : default_loader();
    my_image_loader_lease_t* lease = im->loader_lease;
    if (im->path == NULL || !cache_get(loader, lease, im->path, &img)) {
      /* placeholder: empty frame box */
      my_vgcanvas_set_stroke_color(vg, my_color_rgb(150, 150, 150));
      my_vgcanvas_set_line_width(vg, 1);
      my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                (float)widget->rect.h});
      return;
    }
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
    image_release_transient(&img);
    return;
  }
  image_on_paint_blit(widget, vg, &img, dx, dy, dw, dh);
  image_release_transient(&img);
}

static const my_widget_vtable_t s_image_vtable = {image_on_paint, NULL, NULL, NULL};

bool my_image_is_instance(const my_widget_t* widget) {
  return widget != NULL && widget->vtable == &s_image_vtable;
}

static void image_destroy_chain(my_object_t* obj) {
  my_image_t* im = (my_image_t*)obj;
  my_image_loader_lease_unref(im->loader_lease);
  im->loader_lease = NULL;
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
  if (!my_image_is_instance(image)) {
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
  if (!my_image_is_instance(image)) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_image_t*)image)->scale_mode = mode;
  my_widget_invalidate(image, NULL);
  return MY_RET_OK;
}

my_ret_t my_image_set_scale_filter(my_widget_t* image,
                                   my_scale_filter_t filter) {
  if (!my_image_is_instance(image)) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_image_t*)image)->scale_filter = filter;
  my_widget_invalidate(image, NULL);
  return MY_RET_OK;
}

my_ret_t my_image_set_loader(my_widget_t* image, my_image_loader_t* loader) {
  if (!my_image_is_instance(image)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (loader != NULL && !image_loader_valid(loader)) {
    return MY_RET_INVALID_PARAMS;
  }
  my_image_loader_lease_unref(((my_image_t*)image)->loader_lease);
  ((my_image_t*)image)->loader_lease = NULL;
  ((my_image_t*)image)->loader = loader;
  return MY_RET_OK;
}

my_ret_t my_image_set_loader_lease(my_widget_t* image,
                                   my_image_loader_lease_t* lease) {
  my_image_t* im = (my_image_t*)image;
  my_image_loader_t* loader;
  my_image_loader_lease_t* retained;
  if (!my_image_is_instance(image) || lease == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  loader = my_image_loader_lease_loader(lease);
  if (!image_loader_valid(loader)) {
    return MY_RET_INVALID_PARAMS;
  }
  retained = my_image_loader_lease_ref(lease);
  my_image_loader_lease_unref(im->loader_lease);
  im->loader_lease = retained;
  im->loader = loader;
  return MY_RET_OK;
}
