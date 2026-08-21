/**
 * @file my_image.h
 * @brief Image widget: loads via my_image_loader_t, caches decoded images
 * by path (LRU, default 8 entries), scales by mode and blits to the lcd.
 *
 * Scale modes: NONE (natural size, top-left), CENTER (natural size,
 * centered), FIT (aspect-preserving fit), FILL (stretch). Scaling is
 * nearest-neighbor (bilinear: TODO). Transparency is composited over the
 * widget's themed bg_color. Without MYUI_IMAGE_STB the widget paints a
 * placeholder box.
 */
#ifndef MY_IMAGE_H
#define MY_IMAGE_H

#include "myui/my_image_loader.h"
#include "myui/my_widget.h"

/** @brief Image scale modes. */
typedef enum my_image_scale_t {
  MY_IMAGE_SCALE_NONE = 0,
  MY_IMAGE_SCALE_CENTER,
  MY_IMAGE_SCALE_FIT,
  MY_IMAGE_SCALE_FILL
} my_image_scale_t;

/** @brief Image widget (IS-A widget). */
typedef struct my_image_t {
  my_widget_t base;
  const my_allocator_t* allocator;
  char* path;                     /**< owned */
  my_image_scale_t scale_mode;
  my_scale_filter_t scale_filter; /**< sampling filter (M9b) */
  my_image_loader_t* loader;      /**< borrowed; NULL = default stb loader */
} my_image_t;

my_widget_t* my_image_create(const my_allocator_t* allocator);
my_ret_t my_image_set_image(my_widget_t* image, const char* path);
my_ret_t my_image_set_scale_mode(my_widget_t* image, my_image_scale_t mode);
/** @brief Sampling filter preference (BILINEAR default; backend-dependent). */
my_ret_t my_image_set_scale_filter(my_widget_t* image,
                                   my_scale_filter_t filter);
/** @brief Override the loader (borrowed; NULL resets to the stb default). */
my_ret_t my_image_set_loader(my_widget_t* image, my_image_loader_t* loader);

/** @brief Diagnostics: global image cache hit/miss counters. */
void my_image_cache_stats(size_t* hits, size_t* misses);

#endif /* MY_IMAGE_H */
