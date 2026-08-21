/**
 * @file my_image_loader.c
 * @brief stb_image loader backend.
 */
#include "myui/my_image_loader.h"

#ifdef MYUI_IMAGE_STB

#include <stb_image.h>

typedef struct my_image_loader_stb_t {
  my_image_loader_t base;
  const my_allocator_t* allocator;
} my_image_loader_stb_t;

static my_image_data_t* stb_load(my_image_loader_t* loader, const char* path) {
  my_image_loader_stb_t* s = (my_image_loader_stb_t*)loader;
  my_image_data_t* data;
  int w = 0, h = 0, channels = 0;
  uint8_t* px;
  if (path == NULL) {
    return NULL;
  }
  px = stbi_load(path, &w, &h, &channels, 4); /* force RGBA8888 */
  if (px == NULL || w <= 0 || h <= 0) {
    return NULL;
  }
  data = (my_image_data_t*)my_mem_calloc(s->allocator, 1,
                                         sizeof(my_image_data_t));
  if (data == NULL) {
    stbi_image_free(px);
    return NULL;
  }
  data->pixels = px; /* owned by stb; freed with stbi_image_free */
  data->w = w;
  data->h = h;
  return data;
}

static void stb_free_data(my_image_loader_t* loader, my_image_data_t* data) {
  my_image_loader_stb_t* s = (my_image_loader_stb_t*)loader;
  if (data != NULL) {
    stbi_image_free(data->pixels);
    my_mem_free(s->allocator, data);
  }
}

static void stb_loader_destroy(my_image_loader_t* loader) {
  my_image_loader_stb_t* s = (my_image_loader_stb_t*)loader;
  if (s != NULL) {
    my_mem_free(s->allocator, s);
  }
}

static const my_image_loader_vtable_t s_stb_loader_vtable = {
    stb_load, stb_free_data, stb_loader_destroy};

my_image_loader_t* my_image_loader_stb_create(const my_allocator_t* allocator) {
  my_image_loader_stb_t* s =
      (my_image_loader_stb_t*)my_mem_calloc(allocator, 1,
                                            sizeof(my_image_loader_stb_t));
  if (s == NULL) {
    return NULL;
  }
  s->base.vtable = &s_stb_loader_vtable;
  s->allocator = allocator;
  return (my_image_loader_t*)s;
}

#else /* !MYUI_IMAGE_STB */

my_image_loader_t* my_image_loader_stb_create(const my_allocator_t* allocator) {
  (void)allocator;
  return NULL;
}

#endif /* MYUI_IMAGE_STB */
