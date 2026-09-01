#ifndef MY_VGCANVAS_QUALITY_TRANSACTION_H
#define MY_VGCANVAS_QUALITY_TRANSACTION_H

#include <stdint.h>

#include "myc/my_error.h"

typedef struct my_vgcanvas_sample_transaction_t {
  uint32_t active_sample_count;
  uint32_t active_width;
  uint32_t active_height;
  void* active_candidate;
  uint32_t supported_sample_counts;
} my_vgcanvas_sample_transaction_t;

static inline uint32_t my_vgcanvas_sample_count_bit(uint32_t sample_count) {
  if (sample_count == 0u ||
      (sample_count & (sample_count - 1u)) != 0u) {
    return 0u;
  }
  return sample_count;
}

/** @brief Map the portable AA level to a concrete multisample count. */
static inline uint32_t my_vgcanvas_antialias_level_sample_count(int level) {
  if (level < 0 || level > 2) {
    return 0u;
  }
  return 1u << (uint32_t)level;
}

/** @brief Convert Vulkan/RHI sample-count bits to portable AA level bits. */
static inline uint32_t my_vgcanvas_antialias_levels_for_sample_counts(
    uint32_t sample_counts) {
  uint32_t levels = 0u;
  int level;
  for (level = 0; level <= 2; level++) {
    uint32_t samples = my_vgcanvas_antialias_level_sample_count(level);
    if ((sample_counts & my_vgcanvas_sample_count_bit(samples)) != 0u) {
      levels |= 1u << (uint32_t)level;
    }
  }
  return levels;
}

typedef struct my_vgcanvas_sample_transaction_ops_t {
  my_ret_t (*create)(void* ctx, uint32_t sample_count, uint32_t width,
                     uint32_t height, void** out_candidate);
  my_ret_t (*validate)(void* ctx, void* candidate);
  my_ret_t (*submit)(void* ctx, void* candidate);
  void (*activate)(void* ctx, void* candidate);
  void (*retire)(void* ctx, void* candidate);
  void (*destroy)(void* ctx, void* candidate);
} my_vgcanvas_sample_transaction_ops_t;

void my_vgcanvas_sample_transaction_init(
    my_vgcanvas_sample_transaction_t* tx, uint32_t active_sample_count,
    uint32_t active_width, uint32_t active_height, void* active_candidate,
    uint32_t supported_sample_counts);

my_ret_t my_vgcanvas_sample_transaction_set(
    my_vgcanvas_sample_transaction_t* tx, uint32_t sample_count,
    uint32_t width, uint32_t height,
    const my_vgcanvas_sample_transaction_ops_t* ops, void* ctx);

#endif
