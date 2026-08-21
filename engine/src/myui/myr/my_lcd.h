/**
 * @file my_lcd.h
 * @brief LCD (framebuffer target) abstract interface — vtable.
 *
 * An lcd is the lowest render target: a rectangular pixel surface with a
 * fixed pixel format. Backends: my_lcd_mem (in-RAM, M1), later linux-fb,
 * SDL texture, etc. All drawing on top (vgcanvas) talks only to this vtable.
 *
 * draw_pixels() takes source pixels ALREADY in the lcd's native format
 * (raw row-major blit, tightly packed rows). Format conversion belongs to
 * the caller.
 */
#ifndef MY_LCD_H
#define MY_LCD_H

#include "myc/my_error.h"
#include "myr/my_color.h"
#include "myr/my_rect.h"

/** @brief Framebuffer pixel formats. */
typedef enum my_pixel_format_t {
  MY_PIXEL_FORMAT_RGB565 = 0, /**< 2 bytes/px: rrrrrggg gggbbbbb */
  MY_PIXEL_FORMAT_RGB888,     /**< 3 bytes/px: R,G,B */
  MY_PIXEL_FORMAT_ARGB8888,   /**< 4 bytes/px: A,R,G,B */
  MY_PIXEL_FORMAT_BGRA8888,   /**< 4 bytes/px: B,G,R,A */
  MY_PIXEL_FORMAT_MONO        /**< 1 bit/px, MSB first, 1 = on (white) */
} my_pixel_format_t;

/** @brief Bits per pixel of a format (16/24/32/32/1, 0 for invalid). */
static inline uint32_t my_pixel_format_bpp(my_pixel_format_t format) {
  switch (format) {
    case MY_PIXEL_FORMAT_RGB565:
      return 16;
    case MY_PIXEL_FORMAT_RGB888:
      return 24;
    case MY_PIXEL_FORMAT_ARGB8888:
    case MY_PIXEL_FORMAT_BGRA8888:
      return 32;
    case MY_PIXEL_FORMAT_MONO:
      return 1;
    default:
      return 0;
  }
}

typedef struct my_lcd_t my_lcd_t;

/** @brief LCD vtable. */
typedef struct my_lcd_vtable_t {
  uint32_t (*get_width)(my_lcd_t* lcd);
  uint32_t (*get_height)(my_lcd_t* lcd);
  my_pixel_format_t (*get_format)(my_lcd_t* lcd);
  /** @brief Begin a frame; dirty hints the redrawn region (may be NULL). */
  my_ret_t (*begin_frame)(my_lcd_t* lcd, const my_rect_t* dirty);
  my_ret_t (*end_frame)(my_lcd_t* lcd);
  /** @brief Blit native-format pixels (row-major, w*h pixels) at (x,y). */
  my_ret_t (*draw_pixels)(my_lcd_t* lcd, const void* pixels, int32_t x, int32_t y,
                          uint32_t w, uint32_t h);
  /** @brief Fill rect with color (clipped to the surface, no blending). */
  my_ret_t (*fill_rect)(my_lcd_t* lcd, const my_rect_t* rect, my_color_t color);
  /**
   * @brief Blend a horizontal span of n pixels at (x, y) with src-over:
   * out = color * alpha[i] + dst * (255 - alpha[i]). Used by text
   * rendering (M7a). Clipped to the surface.
   */
  my_ret_t (*blend_span)(my_lcd_t* lcd, int32_t x, int32_t y,
                         const uint8_t* alpha, int32_t n, my_color_t color);
  void (*destroy)(my_lcd_t* lcd);
  /** @brief Optional: raw framebuffer access (mem-backed lcds; wrappers
   * forward). NULL when the backend has no readable buffer. */
  uint8_t* (*get_buffer)(my_lcd_t* lcd);
  uint32_t (*get_stride)(my_lcd_t* lcd);
} my_lcd_vtable_t;

/** @brief LCD base "class": first member of every backend. */
struct my_lcd_t {
  const my_lcd_vtable_t* vtable;
};

static inline uint32_t my_lcd_get_width(my_lcd_t* lcd) {
  return lcd->vtable->get_width(lcd);
}

/** @brief Raw framebuffer access; NULL when the backend has none. */
static inline uint8_t* my_lcd_get_buffer(my_lcd_t* lcd) {
  return lcd->vtable->get_buffer != NULL ? lcd->vtable->get_buffer(lcd) : NULL;
}
static inline uint32_t my_lcd_get_stride(my_lcd_t* lcd) {
  return lcd->vtable->get_stride != NULL ? lcd->vtable->get_stride(lcd) : 0;
}

static inline uint32_t my_lcd_get_height(my_lcd_t* lcd) {
  return lcd->vtable->get_height(lcd);
}

static inline my_pixel_format_t my_lcd_get_format(my_lcd_t* lcd) {
  return lcd->vtable->get_format(lcd);
}

static inline my_ret_t my_lcd_begin_frame(my_lcd_t* lcd, const my_rect_t* dirty) {
  return lcd->vtable->begin_frame(lcd, dirty);
}

static inline my_ret_t my_lcd_end_frame(my_lcd_t* lcd) {
  return lcd->vtable->end_frame(lcd);
}

static inline my_ret_t my_lcd_draw_pixels(my_lcd_t* lcd, const void* pixels,
                                          int32_t x, int32_t y, uint32_t w,
                                          uint32_t h) {
  return lcd->vtable->draw_pixels(lcd, pixels, x, y, w, h);
}

static inline my_ret_t my_lcd_fill_rect(my_lcd_t* lcd, const my_rect_t* rect,
                                        my_color_t color) {
  return lcd->vtable->fill_rect(lcd, rect, color);
}

static inline my_ret_t my_lcd_blend_span(my_lcd_t* lcd, int32_t x, int32_t y,
                                         const uint8_t* alpha, int32_t n,
                                         my_color_t color) {
  return lcd->vtable->blend_span(lcd, x, y, alpha, n, color);
}

static inline void my_lcd_destroy(my_lcd_t* lcd) {
  if (lcd != NULL) {
    lcd->vtable->destroy(lcd);
  }
}

#endif /* MY_LCD_H */
