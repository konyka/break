/**
 * @file my_rect.h
 * @brief Integer (lcd space) and float (vgcanvas space) rectangles.
 */
#ifndef MY_RECT_H
#define MY_RECT_H

#include "myc/my_types.h"

/** @brief Integer rectangle, device/lcd coordinates. */
typedef struct my_rect_t {
  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;
} my_rect_t;

/** @brief Float rectangle, vgcanvas user coordinates. */
typedef struct my_rectf_t {
  float x;
  float y;
  float w;
  float h;
} my_rectf_t;

/** @brief Construct an integer rectangle. */
static inline my_rect_t my_rect_init(int32_t x, int32_t y, int32_t w, int32_t h) {
  my_rect_t r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  return r;
}

/** @brief Construct a float rectangle. */
static inline my_rectf_t my_rectf_init(float x, float y, float w, float h) {
  my_rectf_t r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  return r;
}

/** @brief A rect is empty when NULL or has non-positive size. */
static inline bool my_rect_is_empty(const my_rect_t* r) {
  return r == NULL || r->w <= 0 || r->h <= 0;
}

static inline int64_t my_rect_right_i64(const my_rect_t* r) {
  return (int64_t)r->x + (int64_t)r->w;
}

static inline int64_t my_rect_bottom_i64(const my_rect_t* r) {
  return (int64_t)r->y + (int64_t)r->h;
}

static inline int32_t my_rect_extent_i32(int64_t extent) {
  return extent > INT32_MAX ? INT32_MAX : extent < 0 ? 0 : (int32_t)extent;
}

/** @brief Center a child extent in an axis without signed overflow. */
static inline int32_t my_rect_center_axis_i32(int32_t origin,
                                              int32_t available,
                                              int32_t child_extent) {
  int64_t centered = (int64_t)origin +
                     ((int64_t)available - (int64_t)child_extent) / 2;
  if (centered > INT32_MAX) return INT32_MAX;
  if (centered < INT32_MIN) return INT32_MIN;
  return (int32_t)centered;
}

/** @brief Add a signed offset to an axis and saturate to int32_t. */
static inline int32_t my_rect_offset_i32(int32_t origin, int64_t offset) {
  int64_t value = (int64_t)origin + offset;
  if (value > INT32_MAX) return INT32_MAX;
  if (value < INT32_MIN) return INT32_MIN;
  return (int32_t)value;
}

/** @brief Whether point (px,py) is inside r (half-open: [x, x+w) x [y, y+h)). */
static inline bool my_rect_contains(const my_rect_t* r, int32_t px, int32_t py) {
  return r != NULL && px >= r->x && (int64_t)px < my_rect_right_i64(r) &&
         py >= r->y && (int64_t)py < my_rect_bottom_i64(r);
}

/**
 * @brief Intersect a and b into out (out may be NULL).
 * @return true when the intersection is non-empty.
 */
static inline bool my_rect_intersect(const my_rect_t* a, const my_rect_t* b,
                                     my_rect_t* out) {
  int64_t x1, y1, x2, y2;
  if (my_rect_is_empty(a) || my_rect_is_empty(b)) {
    return false;
  }
  x1 = a->x > b->x ? a->x : b->x;
  y1 = a->y > b->y ? a->y : b->y;
  x2 = my_rect_right_i64(a) < my_rect_right_i64(b)
           ? my_rect_right_i64(a)
           : my_rect_right_i64(b);
  y2 = my_rect_bottom_i64(a) < my_rect_bottom_i64(b)
           ? my_rect_bottom_i64(a)
           : my_rect_bottom_i64(b);
  if (x2 <= x1 || y2 <= y1) {
    return false;
  }
  if (out != NULL) {
    *out = my_rect_init((int32_t)x1, (int32_t)y1,
                        my_rect_extent_i32(x2 - x1),
                        my_rect_extent_i32(y2 - y1));
  }
  return true;
}

/**
 * @brief Bounding box (union) of a and b into out.
 * Empty inputs are ignored; both empty yields a zero rect.
 */
static inline void my_rect_union(const my_rect_t* a, const my_rect_t* b,
                                 my_rect_t* out) {
  int64_t x1, y1, x2, y2;
  if (out == NULL) return;
  if (my_rect_is_empty(a)) {
    *out = my_rect_is_empty(b) ? my_rect_init(0, 0, 0, 0) : *b;
    return;
  }
  if (my_rect_is_empty(b)) {
    *out = *a;
    return;
  }
  x1 = a->x < b->x ? a->x : b->x;
  y1 = a->y < b->y ? a->y : b->y;
  x2 = my_rect_right_i64(a) > my_rect_right_i64(b)
           ? my_rect_right_i64(a)
           : my_rect_right_i64(b);
  y2 = my_rect_bottom_i64(a) > my_rect_bottom_i64(b)
           ? my_rect_bottom_i64(a)
           : my_rect_bottom_i64(b);
  *out = my_rect_init((int32_t)x1, (int32_t)y1,
                      my_rect_extent_i32(x2 - x1),
                      my_rect_extent_i32(y2 - y1));
}

#endif /* MY_RECT_H */
