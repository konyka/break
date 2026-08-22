/**
 * @file my_dirty_rects.h
 * @brief Dirty rectangle collector for partial (redraw-only-what-changed)
 * rendering.
 *
 * Merge policy (kept simple and deterministic):
 *  - empty rects are ignored;
 *  - a new rect that intersects OR directly touches an existing one is
 *    merged into it (repeated until no merge happens, so cascades merge);
 *  - otherwise it is appended, up to MY_DIRTY_RECTS_MAX slots;
 *  - when full, everything (including the new rect) collapses into a
 *    single bounding box.
 *
 * The collector is a plain value type: my_dirty_rects_init() it on the
 * stack, no heap involved.
 */
#ifndef MY_DIRTY_RECTS_H
#define MY_DIRTY_RECTS_H

#include "myc/my_error.h"
#include "myr/my_rect.h"

/** @brief Maximum number of tracked rects before collapsing to a bbox. */
#define MY_DIRTY_RECTS_MAX 16

/** @brief Dirty rectangle set. */
typedef struct my_dirty_rects_t {
  my_rect_t rects[MY_DIRTY_RECTS_MAX]; /**< merged rects, count in use */
  size_t count;                        /**< number of valid entries */
} my_dirty_rects_t;

/** @brief Reset to the empty set. */
void my_dirty_rects_init(my_dirty_rects_t* dr);

/** @brief Add a rect, applying the merge policy. */
my_ret_t my_dirty_rects_add(my_dirty_rects_t* dr, const my_rect_t* rect);

/** @brief Remove all rects (same as init). */
void my_dirty_rects_clear(my_dirty_rects_t* dr);

/** @brief Number of rects (0 for NULL). */
size_t my_dirty_rects_count(const my_dirty_rects_t* dr);

/** @brief Get the i-th rect, NULL when out of range. */
const my_rect_t* my_dirty_rects_get(const my_dirty_rects_t* dr, size_t index);

#endif /* MY_DIRTY_RECTS_H */
