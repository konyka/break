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
