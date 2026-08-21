/**
 * @file my_color.h
 * @brief RGBA8888 color type and helpers (header-only).
 */
#ifndef MY_COLOR_H
#define MY_COLOR_H

#include "myc/my_types.h"

/** @brief 8-bit per channel RGBA color. */
typedef struct my_color_t {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} my_color_t;

/** @brief Construct a color from channels. */
static inline my_color_t my_color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  my_color_t c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;
  return c;
}

/** @brief Construct an opaque color from RGB channels. */
static inline my_color_t my_color_rgb(uint8_t r, uint8_t g, uint8_t b) {
  return my_color_rgba(r, g, b, 255u);
}

/** @brief Pack to a 32-bit value 0xRRGGBBAA. */
static inline uint32_t my_color_to_rgba32(my_color_t c) {
  return ((uint32_t)c.r << 24) | ((uint32_t)c.g << 16) | ((uint32_t)c.b << 8) |
         (uint32_t)c.a;
}

/** @brief Unpack from a 32-bit value 0xRRGGBBAA. */
static inline my_color_t my_color_from_rgba32(uint32_t v) {
  return my_color_rgba((uint8_t)(v >> 24), (uint8_t)(v >> 16), (uint8_t)(v >> 8),
                       (uint8_t)v);
}

/** @brief Channel-wise equality. */
static inline bool my_color_eq(my_color_t a, my_color_t b) {
  return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

#endif /* MY_COLOR_H */
