/**
 * @file my_dirty_rects.c
 * @brief Dirty rectangle collector (merge policy documented in the header).
 */
#include "myr/my_dirty_rects.h"

void my_dirty_rects_init(my_dirty_rects_t* dr) {
  if (dr != NULL) {
    dr->count = 0;
  }
}

void my_dirty_rects_clear(my_dirty_rects_t* dr) {
  my_dirty_rects_init(dr);
}

size_t my_dirty_rects_count(const my_dirty_rects_t* dr) {
  return dr != NULL ? dr->count : 0;
}

const my_rect_t* my_dirty_rects_get(const my_dirty_rects_t* dr, size_t index) {
  if (dr == NULL || index >= dr->count) {
    return NULL;
  }
  return &dr->rects[index];
}

/**
 * @brief Whether a and b overlap or touch directly (closed intervals).
 * Touching rects are merged so partial redraws coalesce into fewer,
 * larger blits.
 */
static bool my_rect_touches(const my_rect_t* a, const my_rect_t* b) {
  return a->x <= b->x + b->w && b->x <= a->x + a->w && a->y <= b->y + b->h &&
         b->y <= a->y + a->h;
}

my_ret_t my_dirty_rects_add(my_dirty_rects_t* dr, const my_rect_t* rect) {
  my_rect_t r;
  size_t i;
  bool merged;

  if (dr == NULL || rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (my_rect_is_empty(rect)) {
    return MY_RET_OK;
  }
  r = *rect;

  /* merge with everything the new rect overlaps or touches (cascading) */
  do {
    merged = false;
    for (i = 0; i < dr->count; i++) {
      if (my_rect_touches(&r, &dr->rects[i])) {
        my_rect_union(&r, &dr->rects[i], &r);
        dr->rects[i] = dr->rects[dr->count - 1];
        dr->count--;
        merged = true;
      }
    }
  } while (merged);

  if (dr->count < MY_DIRTY_RECTS_MAX) {
    dr->rects[dr->count++] = r;
    return MY_RET_OK;
  }

  /* full: collapse everything into a single bounding box */
  r = dr->rects[0];
  for (i = 1; i < dr->count; i++) {
    my_rect_union(&r, &dr->rects[i], &r);
  }
  my_rect_union(&r, rect, &r);
  dr->rects[0] = r;
  dr->count = 1;
  return MY_RET_OK;
}
