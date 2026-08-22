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

/** @brief Whether point (px,py) is inside r (half-open: [x, x+w) x [y, y+h)). */
static inline bool my_rect_contains(const my_rect_t* r, int32_t px, int32_t py) {
  return r != NULL && px >= r->x && px < r->x + r->w && py >= r->y &&
         py < r->y + r->h;
}

/**
 * @brief Intersect a and b into out (out may be NULL).
 * @return true when the intersection is non-empty.
 */
static inline bool my_rect_intersect(const my_rect_t* a, const my_rect_t* b,
                                     my_rect_t* out) {
  int32_t x1, y1, x2, y2;
  if (my_rect_is_empty(a) || my_rect_is_empty(b)) {
    return false;
  }
  x1 = a->x > b->x ? a->x : b->x;
  y1 = a->y > b->y ? a->y : b->y;
  x2 = a->x + a->w < b->x + b->w ? a->x + a->w : b->x + b->w;
  y2 = a->y + a->h < b->y + b->h ? a->y + a->h : b->y + b->h;
  if (x2 <= x1 || y2 <= y1) {
    return false;
  }
  if (out != NULL) {
    *out = my_rect_init(x1, y1, x2 - x1, y2 - y1);
  }
  return true;
}

/**
 * @brief Bounding box (union) of a and b into out.
 * Empty inputs are ignored; both empty yields a zero rect.
 */
static inline void my_rect_union(const my_rect_t* a, const my_rect_t* b,
                                 my_rect_t* out) {
  int32_t x1, y1, x2, y2;
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
  x2 = a->x + a->w > b->x + b->w ? a->x + a->w : b->x + b->w;
  y2 = a->y + a->h > b->y + b->h ? a->y + a->h : b->y + b->h;
  *out = my_rect_init(x1, y1, x2 - x1, y2 - y1);
}

#endif /* MY_RECT_H */
