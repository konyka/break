/**
 * @file my_lcd_mem.c
 * @brief In-memory framebuffer lcd backend with per-format specialization.
 */
#include "myr/my_lcd_mem.h"

#include <stdint.h>
#include <string.h>

typedef struct my_lcd_mem_t {
  my_lcd_t base;
  const my_allocator_t* allocator;
  uint32_t w;
  uint32_t h;
  my_pixel_format_t format;
  uint32_t stride; /**< bytes per row */
  uint8_t* buffer;
  bool buffer_owned; /**< false for create_from_buffer (e.g. mmap'd fb) */
} my_lcd_mem_t;

static void blend_row(my_lcd_mem_t* m, uint8_t* row, int32_t x0, uint32_t n,
                      my_color_t c);

/* ---------------- vtable: properties ---------------- */

static uint32_t lcd_mem_get_width(my_lcd_t* lcd) {
  return ((my_lcd_mem_t*)lcd)->w;
}

static uint32_t lcd_mem_get_height(my_lcd_t* lcd) {
  return ((my_lcd_mem_t*)lcd)->h;
}

static my_pixel_format_t lcd_mem_get_format(my_lcd_t* lcd) {
  return ((my_lcd_mem_t*)lcd)->format;
}

static my_ret_t lcd_mem_begin_frame(my_lcd_t* lcd, const my_rect_t* dirty) {
  (void)lcd;
  (void)dirty;
  return MY_RET_OK;
}

static my_ret_t lcd_mem_end_frame(my_lcd_t* lcd) {
  (void)lcd;
  return MY_RET_OK;
}

/* ---------------- pixel writers (format specialization) ---------------- */

static inline void write_rgb565(uint8_t* dst, my_color_t c) {
  uint16_t v = (uint16_t)(((c.r >> 3) << 11) | ((c.g >> 2) << 5) | (c.b >> 3));
  memcpy(dst, &v, 2);
}

static inline void write_rgb888(uint8_t* dst, my_color_t c) {
  dst[0] = c.r;
  dst[1] = c.g;
  dst[2] = c.b;
}

static inline void write_argb8888(uint8_t* dst, my_color_t c) {
  dst[0] = c.a;
  dst[1] = c.r;
  dst[2] = c.g;
  dst[3] = c.b;
}

static inline void write_bgra8888(uint8_t* dst, my_color_t c) {
  dst[0] = c.b;
  dst[1] = c.g;
  dst[2] = c.r;
  dst[3] = c.a;
}

static inline bool mono_is_on(my_color_t c) {
  /* ITU-R BT.601 luma threshold */
  return (uint32_t)c.r * 299 + (uint32_t)c.g * 587 + (uint32_t)c.b * 114 >=
         128u * 1000u;
}

static void fill_row_rgb565(uint8_t* row, uint32_t n, my_color_t c) {
  uint16_t v = (uint16_t)(((c.r >> 3) << 11) | ((c.g >> 2) << 5) | (c.b >> 3));
  uint16_t* p = (uint16_t*)(void*)row;
  uint32_t i;
  for (i = 0; i < n; i++) {
    p[i] = v;
  }
}

static void fill_row_rgb888(uint8_t* row, uint32_t n, my_color_t c) {
  uint32_t i;
  for (i = 0; i < n; i++) {
    write_rgb888(row + (size_t)i * 3, c);
  }
}

static void fill_row_argb8888(uint8_t* row, uint32_t n, my_color_t c) {
  uint32_t i;
  for (i = 0; i < n; i++) {
    write_argb8888(row + (size_t)i * 4, c);
  }
}

static void fill_row_bgra8888(uint8_t* row, uint32_t n, my_color_t c) {
  uint32_t i;
  for (i = 0; i < n; i++) {
    write_bgra8888(row + (size_t)i * 4, c);
  }
}

static void fill_mono_bits(my_lcd_mem_t* m, const my_rect_t* r, bool on) {
  int32_t x, y;
  for (y = r->y; y < r->y + r->h; y++) {
    uint8_t* row = m->buffer + (size_t)y * m->stride;
    for (x = r->x; x < r->x + r->w; x++) {
      uint8_t mask = (uint8_t)(0x80u >> ((uint32_t)x % 8u));
      if (on) {
        row[(uint32_t)x / 8u] |= mask;
      } else {
        row[(uint32_t)x / 8u] &= (uint8_t)~mask;
      }
    }
  }
}

/* ---------------- vtable: drawing ---------------- */

static my_ret_t lcd_mem_fill_rect(my_lcd_t* lcd, const my_rect_t* rect,
                                  my_color_t color) {
  my_lcd_mem_t* m = (my_lcd_mem_t*)lcd;
  my_rect_t bounds, clipped;
  int32_t y;

  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  bounds = my_rect_init(0, 0, (int32_t)m->w, (int32_t)m->h);
  if (!my_rect_intersect(rect, &bounds, &clipped)) {
    return MY_RET_OK; /* fully outside: nothing to do */
  }

  if (m->format == MY_PIXEL_FORMAT_MONO) {
    fill_mono_bits(m, &clipped, mono_is_on(color));
    return MY_RET_OK;
  }

  /* translucent color: per-pixel src-over (opaque keeps the fast path) */
  if (color.a < 255) {
    for (y = clipped.y; y < clipped.y + clipped.h; y++) {
      blend_row(m, m->buffer + (size_t)y * m->stride, clipped.x,
                (uint32_t)clipped.w, color);
    }
    return MY_RET_OK;
  }

  for (y = clipped.y; y < clipped.y + clipped.h; y++) {
    uint8_t* row = m->buffer + (size_t)y * m->stride;
    uint32_t n = (uint32_t)clipped.w;
    switch (m->format) {
      case MY_PIXEL_FORMAT_RGB565:
        fill_row_rgb565(row + (size_t)clipped.x * 2, n, color);
        break;
      case MY_PIXEL_FORMAT_RGB888:
        fill_row_rgb888(row + (size_t)clipped.x * 3, n, color);
        break;
      case MY_PIXEL_FORMAT_ARGB8888:
        fill_row_argb8888(row + (size_t)clipped.x * 4, n, color);
        break;
      case MY_PIXEL_FORMAT_BGRA8888:
        fill_row_bgra8888(row + (size_t)clipped.x * 4, n, color);
        break;
      default:
        return MY_RET_NOT_SUPPORTED;
    }
  }
  return MY_RET_OK;
}

static my_ret_t lcd_mem_draw_pixels(my_lcd_t* lcd, const void* pixels, int32_t x,
                                    int32_t y, uint32_t w, uint32_t h) {
  my_lcd_mem_t* m = (my_lcd_mem_t*)lcd;
  uint32_t bpp;
  size_t bytes;
  int32_t src_x = 0, src_y = 0, row;
  my_rect_t bounds, dst, clipped;

  if (pixels == NULL || w == 0 || h == 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (w > (uint32_t)INT32_MAX || h > (uint32_t)INT32_MAX) {
    return MY_RET_INVALID_PARAMS;
  }
  if (m->format == MY_PIXEL_FORMAT_MONO) {
    const uint8_t* src = (const uint8_t*)pixels;
    uint32_t src_stride = w / 8u + (w % 8u != 0u ? 1u : 0u);
    uint32_t row;
    if ((size_t)h > SIZE_MAX / src_stride) {
      return MY_RET_INVALID_PARAMS;
    }
    bounds = my_rect_init(0, 0, (int32_t)m->w, (int32_t)m->h);
    dst = my_rect_init(x, y, (int32_t)w, (int32_t)h);
    if (!my_rect_intersect(&dst, &bounds, &clipped)) {
      return MY_RET_OK;
    }
    for (row = 0; row < (uint32_t)clipped.h; row++) {
      uint32_t sy = (uint32_t)(clipped.y - y) + row;
      int32_t col;
      for (col = 0; col < clipped.w; col++) {
        uint32_t sx = (uint32_t)(clipped.x - x) + (uint32_t)col;
        bool on = (src[(size_t)sy * src_stride + sx / 8u] &
                   (uint8_t)(0x80u >> (sx % 8u))) != 0;
        uint8_t* dst_row = m->buffer + (size_t)(clipped.y + (int32_t)row) *
                           m->stride;
        uint8_t mask = (uint8_t)(0x80u >>
                                 ((uint32_t)(clipped.x + col) % 8u));
        if (on) {
          dst_row[(uint32_t)(clipped.x + col) / 8u] |= mask;
        } else {
          dst_row[(uint32_t)(clipped.x + col) / 8u] &= (uint8_t)~mask;
        }
      }
    }
    return MY_RET_OK;
  }
  bpp = my_pixel_format_bpp(m->format) / 8;
  if (bpp == 0u || (size_t)w > SIZE_MAX / bpp ||
      (size_t)h > SIZE_MAX / ((size_t)w * bpp)) {
    return MY_RET_INVALID_PARAMS;
  }

  bounds = my_rect_init(0, 0, (int32_t)m->w, (int32_t)m->h);
  dst = my_rect_init(x, y, (int32_t)w, (int32_t)h);
  if (!my_rect_intersect(&dst, &bounds, &clipped)) {
    return MY_RET_OK;
  }
  src_x = clipped.x - x;
  src_y = clipped.y - y;
  bytes = (size_t)clipped.w * bpp;

  for (row = 0; row < clipped.h; row++) {
    const uint8_t* src =
        (const uint8_t*)pixels +
        ((size_t)(src_y + row) * w + (size_t)src_x) * bpp;
    uint8_t* d = m->buffer + (size_t)(clipped.y + row) * m->stride +
                 (size_t)clipped.x * bpp;
    memcpy(d, src, bytes);
  }
  return MY_RET_OK;
}

/* ---------------- blend (src-over) ---------------- */

static inline uint8_t blend_ch(uint8_t src, uint8_t dst, uint8_t a) {
  /* out = (src*a + dst*(255-a)) / 255, truncating division */
  return (uint8_t)(((uint32_t)src * a + (uint32_t)dst * (255u - a)) / 255u);
}

/** @brief Blend one row of n pixels of the given format with src-over. */
static void blend_row(my_lcd_mem_t* m, uint8_t* row, int32_t x0, uint32_t n,
                      my_color_t c) {
  uint32_t i;
  uint8_t a = c.a;
  for (i = 0; i < n; i++) {
    uint8_t* p = row + (size_t)(x0 + (int32_t)i) *
                       (my_pixel_format_bpp(m->format) / 8u);
    switch (m->format) {
      case MY_PIXEL_FORMAT_RGB565: {
        uint16_t v, o;
        uint8_t dr, dg, db;
        memcpy(&v, p, 2);
        dr = (uint8_t)((v >> 11) << 3);
        dg = (uint8_t)(((v >> 5) & 0x3F) << 2);
        db = (uint8_t)((v & 0x1F) << 3);
        o = (uint16_t)(((blend_ch(c.r, dr, a) >> 3) << 11) |
                       ((blend_ch(c.g, dg, a) >> 2) << 5) |
                       (blend_ch(c.b, db, a) >> 3));
        memcpy(p, &o, 2);
        break;
      }
      case MY_PIXEL_FORMAT_RGB888:
        p[0] = blend_ch(c.r, p[0], a);
        p[1] = blend_ch(c.g, p[1], a);
        p[2] = blend_ch(c.b, p[2], a);
        break;
      case MY_PIXEL_FORMAT_ARGB8888:
        p[1] = blend_ch(c.r, p[1], a);
        p[2] = blend_ch(c.g, p[2], a);
        p[3] = blend_ch(c.b, p[3], a);
        break;
      case MY_PIXEL_FORMAT_BGRA8888:
        p[0] = blend_ch(c.b, p[0], a);
        p[1] = blend_ch(c.g, p[1], a);
        p[2] = blend_ch(c.r, p[2], a);
        break;
      default:
        break;
    }
  }
}

static my_ret_t lcd_mem_blend_span(my_lcd_t* lcd, int32_t x, int32_t y,
                                   const uint8_t* alpha, int32_t n,
                                   my_color_t color) {
  my_lcd_mem_t* m = (my_lcd_mem_t*)lcd;
  int32_t i;
  if (alpha == NULL || n <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (y < 0 || y >= (int32_t)m->h) {
    return MY_RET_OK;
  }
  if (x < 0) { /* clip left */
    alpha += -x;
    n += x;
    x = 0;
  }
  if (x + n > (int32_t)m->w) {
    n = (int32_t)m->w - x;
  }
  if (n <= 0) {
    return MY_RET_OK;
  }
  for (i = 0; i < n; i++) {
    uint8_t a = alpha[i];
    uint8_t* p;
    if (a == 0) {
      continue;
    }
    p = m->buffer + (size_t)y * m->stride;
    switch (m->format) {
      case MY_PIXEL_FORMAT_RGB565: {
        uint16_t v;
        uint8_t dr, dg, db;
        uint16_t o;
        memcpy(&v, p + (size_t)(x + i) * 2, 2);
        dr = (uint8_t)((v >> 11) << 3);
        dg = (uint8_t)(((v >> 5) & 0x3F) << 2);
        db = (uint8_t)((v & 0x1F) << 3);
        o = (uint16_t)(((blend_ch(color.r, dr, a) >> 3) << 11) |
                       ((blend_ch(color.g, dg, a) >> 2) << 5) |
                       (blend_ch(color.b, db, a) >> 3));
        memcpy(p + (size_t)(x + i) * 2, &o, 2);
        break;
      }
      case MY_PIXEL_FORMAT_RGB888:
        p += (size_t)(x + i) * 3;
        p[0] = blend_ch(color.r, p[0], a);
        p[1] = blend_ch(color.g, p[1], a);
        p[2] = blend_ch(color.b, p[2], a);
        break;
      case MY_PIXEL_FORMAT_ARGB8888:
        p += (size_t)(x + i) * 4;
        p[1] = blend_ch(color.r, p[1], a);
        p[2] = blend_ch(color.g, p[2], a);
        p[3] = blend_ch(color.b, p[3], a);
        break;
      case MY_PIXEL_FORMAT_BGRA8888:
        p += (size_t)(x + i) * 4;
        p[0] = blend_ch(color.b, p[0], a);
        p[1] = blend_ch(color.g, p[1], a);
        p[2] = blend_ch(color.r, p[2], a);
        break;
      case MY_PIXEL_FORMAT_MONO:
        if (a >= 128) {
          bool on = mono_is_on(color);
          uint8_t mask = (uint8_t)(0x80u >> ((uint32_t)(x + i) % 8u));
          if (on) {
            p[(uint32_t)(x + i) / 8u] |= mask;
          } else {
            p[(uint32_t)(x + i) / 8u] &= (uint8_t)~mask;
          }
        }
        break;
      default:
        return MY_RET_NOT_SUPPORTED;
    }
  }
  return MY_RET_OK;
}

static void lcd_mem_destroy(my_lcd_t* lcd) {
  my_lcd_mem_t* m = (my_lcd_mem_t*)lcd;
  if (m != NULL) {
    if (m->buffer_owned) {
      my_mem_free(m->allocator, m->buffer);
    }
    my_mem_free(m->allocator, m);
  }
}

/* ---------------- create / accessors ---------------- */

static uint8_t* lcd_mem_buffer_slot(my_lcd_t* lcd) {
  return my_lcd_mem_get_buffer(lcd);
}
static uint32_t lcd_mem_stride_slot(my_lcd_t* lcd) {
  return my_lcd_mem_get_stride(lcd);
}

static const my_lcd_vtable_t s_lcd_mem_vtable = {
    lcd_mem_get_width,  lcd_mem_get_height, lcd_mem_get_format,
    lcd_mem_begin_frame, lcd_mem_end_frame, lcd_mem_draw_pixels,
    lcd_mem_fill_rect,  lcd_mem_blend_span, lcd_mem_destroy,
    lcd_mem_buffer_slot, lcd_mem_stride_slot};

my_lcd_t* my_lcd_mem_create(const my_allocator_t* allocator, uint32_t w, uint32_t h,
                            my_pixel_format_t format) {
  my_lcd_mem_t* m;
  uint32_t stride;
  uint32_t bpp = my_pixel_format_bpp(format);

  if (w == 0 || h == 0 || w > (uint32_t)INT32_MAX ||
      h > (uint32_t)INT32_MAX || bpp == 0) {
    return NULL;
  }
  if (format == MY_PIXEL_FORMAT_MONO) {
    stride = w / 8u + (w % 8u != 0u ? 1u : 0u);
  } else {
    uint32_t bytes_per_pixel = bpp / 8u;
    if (bytes_per_pixel == 0u || w > UINT32_MAX / bytes_per_pixel) {
      return NULL;
    }
    stride = w * bytes_per_pixel;
  }
  if (h > SIZE_MAX / stride) {
    return NULL;
  }

  m = (my_lcd_mem_t*)my_mem_calloc(allocator, 1, sizeof(my_lcd_mem_t));
  if (m == NULL) {
    return NULL;
  }
  m->buffer = (uint8_t*)my_mem_calloc(allocator, (size_t)stride * h, 1);
  if (m->buffer == NULL) {
    my_mem_free(allocator, m);
    return NULL;
  }
  m->buffer_owned = true;
  m->base.vtable = &s_lcd_mem_vtable;
  m->allocator = allocator;
  m->w = w;
  m->h = h;
  m->format = format;
  m->stride = stride;
  return (my_lcd_t*)m;
}

static my_lcd_mem_t* as_mem(my_lcd_t* lcd) {
  if (lcd == NULL || lcd->vtable != &s_lcd_mem_vtable) {
    return NULL;
  }
  return (my_lcd_mem_t*)lcd;
}

uint8_t* my_lcd_mem_get_buffer(my_lcd_t* lcd) {
  my_lcd_mem_t* m = as_mem(lcd);
  return m != NULL ? m->buffer : NULL;
}

uint32_t my_lcd_mem_get_stride(my_lcd_t* lcd) {
  my_lcd_mem_t* m = as_mem(lcd);
  return m != NULL ? m->stride : 0;
}

my_lcd_t* my_lcd_mem_create_from_buffer(const my_allocator_t* allocator,
                                        uint32_t w, uint32_t h,
                                        my_pixel_format_t format,
                                        uint8_t* buffer, uint32_t stride) {
  my_lcd_mem_t* m;
  if (w == 0 || h == 0 || buffer == NULL ||
      w > (uint32_t)INT32_MAX || h > (uint32_t)INT32_MAX ||
      my_pixel_format_bpp(format) == 0) {
    return NULL;
  }
  {
    uint32_t bpp = my_pixel_format_bpp(format);
    uint32_t min_stride;
    if (format == MY_PIXEL_FORMAT_MONO) {
      min_stride = w / 8u + (w % 8u != 0u ? 1u : 0u);
    } else {
      uint32_t bytes_per_pixel = bpp / 8u;
      if (bytes_per_pixel == 0u || w > UINT32_MAX / bytes_per_pixel) {
        return NULL;
      }
      min_stride = w * bytes_per_pixel;
    }
    if (stride < min_stride) {
      return NULL;
    }
  }
  m = (my_lcd_mem_t*)my_mem_calloc(allocator, 1, sizeof(my_lcd_mem_t));
  if (m == NULL) {
    return NULL;
  }
  m->base.vtable = &s_lcd_mem_vtable;
  m->allocator = allocator;
  m->w = w;
  m->h = h;
  m->format = format;
  m->stride = stride;
  m->buffer = buffer;
  m->buffer_owned = false;
  return (my_lcd_t*)m;
}
