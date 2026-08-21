/**
 * @file my_image_loader.h
 * @brief Image loader abstraction + stb_image backend.
 *
 * Decoded images use a single intermediate format: RGBA8888
 * (my_image_data_t). The my_image widget blits via the lcd.
 * Compile-time switch: MYUI_IMAGE_STB (default ON).
 */
#ifndef MY_IMAGE_LOADER_H
#define MY_IMAGE_LOADER_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

/** @brief Decoded image (RGBA8888, row-major, owned by the loader). */
typedef struct my_image_data_t {
  uint8_t* pixels;
  int32_t w;
  int32_t h;
} my_image_data_t;

typedef struct my_image_loader_t my_image_loader_t;

/** @brief Image loader vtable. */
typedef struct my_image_loader_vtable_t {
  /** @brief Load an image file; NULL when unreadable/unsupported. */
  my_image_data_t* (*load)(my_image_loader_t* loader, const char* path);
  /** @brief Free a loaded image. */
  void (*free_data)(my_image_loader_t* loader, my_image_data_t* data);
  void (*destroy)(my_image_loader_t* loader);
} my_image_loader_vtable_t;

/** @brief Image loader base "class". */
struct my_image_loader_t {
  const my_image_loader_vtable_t* vtable;
};

static inline my_image_data_t* my_image_loader_load(my_image_loader_t* loader,
                                                    const char* path) {
  return loader->vtable->load(loader, path);
}

static inline void my_image_loader_free_data(my_image_loader_t* loader,
                                             my_image_data_t* data) {
  if (data != NULL) {
    loader->vtable->free_data(loader, data);
  }
}

static inline void my_image_loader_destroy(my_image_loader_t* loader) {
  if (loader != NULL) {
    loader->vtable->destroy(loader);
  }
}

/**
 * @brief stb_image backend (NULL when built without MYUI_IMAGE_STB).
 */
my_image_loader_t* my_image_loader_stb_create(const my_allocator_t* allocator);

#endif /* MY_IMAGE_LOADER_H */
