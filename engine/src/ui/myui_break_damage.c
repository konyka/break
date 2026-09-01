#include "ui/myui_break_damage.h"

#include <stdint.h>

#include "myui/my_window_manager.h"

bool break_ui_drawable_damage_to_logical(
    const RHIPresentRect* damage, uint32_t logical_width,
    uint32_t logical_height, uint32_t drawable_width,
    uint32_t drawable_height, my_rect_t* out) {
  uint64_t right;
  uint64_t bottom;
  uint64_t x0;
  uint64_t y0;
  uint64_t x1;
  uint64_t y1;
  if (damage == NULL || out == NULL || logical_width == 0u ||
      logical_height == 0u || drawable_width == 0u || drawable_height == 0u ||
      damage->x < 0 || damage->y < 0 || damage->w == 0u || damage->h == 0u ||
      (uint64_t)damage->x + damage->w > drawable_width ||
      (uint64_t)damage->y + damage->h > drawable_height ||
      logical_width > INT32_MAX || logical_height > INT32_MAX) {
    return false;
  }
  right = (uint64_t)damage->x + damage->w;
  bottom = (uint64_t)damage->y + damage->h;
  x0 = ((uint64_t)damage->x * logical_width) / drawable_width;
  y0 = ((uint64_t)damage->y * logical_height) / drawable_height;
  x1 = (right * logical_width + drawable_width - 1u) / drawable_width;
  y1 = (bottom * logical_height + drawable_height - 1u) / drawable_height;
  if (x1 > logical_width) x1 = logical_width;
  if (y1 > logical_height) y1 = logical_height;
  if (x0 >= x1 || y0 >= y1) return false;
  *out = (my_rect_t){(int32_t)x0, (int32_t)y0, (int32_t)(x1 - x0),
                     (int32_t)(y1 - y0)};
  return true;
}

#define BREAK_UI_DEFAULT_MAX_DAMAGE_RECTS 8u
#define BREAK_UI_DEFAULT_MAX_SCISSOR_AREA_PERCENT 60u

bool break_ui_damage_to_drawable_scissor(
    const my_dirty_rects_t* damage, uint32_t logical_width,
    uint32_t logical_height, uint32_t drawable_width,
    uint32_t drawable_height, break_ui_damage_scissor_t* out) {
  uint32_t min_x = drawable_width;
  uint32_t min_y = drawable_height;
  uint32_t max_x = 0;
  uint32_t max_y = 0;
  bool found = false;
  size_t i;

  if (damage == NULL || out == NULL || logical_width == 0 ||
      logical_height == 0 || drawable_width == 0 || drawable_height == 0) {
    return false;
  }
  for (i = 0; i < my_dirty_rects_count(damage); i++) {
    const my_rect_t* rect = my_dirty_rects_get(damage, i);
    int64_t right;
    int64_t bottom;
    uint32_t x0;
    uint32_t y0;
    uint32_t x1;
    uint32_t y1;
    uint64_t mapped_x0;
    uint64_t mapped_y0;
    uint64_t mapped_x1;
    uint64_t mapped_y1;
    if (rect == NULL || rect->w <= 0 || rect->h <= 0) {
      continue;
    }
    right = (int64_t)rect->x + (int64_t)rect->w;
    bottom = (int64_t)rect->y + (int64_t)rect->h;
    x0 = rect->x > 0 ? (uint32_t)rect->x : 0;
    y0 = rect->y > 0 ? (uint32_t)rect->y : 0;
    x1 = right < (int64_t)logical_width ? (right > 0 ? (uint32_t)right : 0)
                                        : logical_width;
    y1 = bottom < (int64_t)logical_height
             ? (bottom > 0 ? (uint32_t)bottom : 0)
             : logical_height;
    if (x0 >= x1 || y0 >= y1) {
      continue;
    }
    mapped_x0 = ((uint64_t)x0 * drawable_width) / logical_width;
    mapped_y0 = ((uint64_t)y0 * drawable_height) / logical_height;
    mapped_x1 = (((uint64_t)x1 * drawable_width) + logical_width - 1u) /
                logical_width;
    mapped_y1 = (((uint64_t)y1 * drawable_height) + logical_height - 1u) /
                logical_height;
    if (mapped_x1 > drawable_width) mapped_x1 = drawable_width;
    if (mapped_y1 > drawable_height) mapped_y1 = drawable_height;
    if (mapped_x0 >= mapped_x1 || mapped_y0 >= mapped_y1) {
      continue;
    }
    if ((uint32_t)mapped_x0 < min_x) min_x = (uint32_t)mapped_x0;
    if ((uint32_t)mapped_y0 < min_y) min_y = (uint32_t)mapped_y0;
    if ((uint32_t)mapped_x1 > max_x) max_x = (uint32_t)mapped_x1;
    if ((uint32_t)mapped_y1 > max_y) max_y = (uint32_t)mapped_y1;
    found = true;
  }
  if (!found || min_x >= max_x || min_y >= max_y) {
    return false;
  }
  out->x = min_x;
  out->y = min_y;
  out->w = max_x - min_x;
  out->h = max_y - min_y;
  return true;
}

bool break_ui_surface_composite_decide(
    const my_dirty_rects_t* damage,
    const break_ui_surface_composite_options_t* options,
    break_ui_surface_composite_decision_t* out) {
  uint32_t max_rects;
  uint32_t max_area_percent;
  uint64_t scissor_area;
  uint64_t drawable_area;

  if (damage == NULL || options == NULL || out == NULL) return false;
  out->mode = BREAK_UI_COMPOSITE_FULL;
  out->scissor = (break_ui_damage_scissor_t){0, 0, options->drawable_width,
                                             options->drawable_height};
  if (options->logical_width == 0u || options->logical_height == 0u ||
      options->drawable_width == 0u || options->drawable_height == 0u) {
    return true;
  }
  if (!options->retained_surface_valid || !options->present_target_preserved) {
    return true;
  }
  if (my_dirty_rects_count(damage) == 0u) {
    out->mode = BREAK_UI_COMPOSITE_SKIP;
    return true;
  }
  if (!options->scissor_supported) return true;

  max_rects = options->max_damage_rects == 0u
                  ? BREAK_UI_DEFAULT_MAX_DAMAGE_RECTS
                  : options->max_damage_rects;
  max_area_percent = options->max_scissor_area_percent == 0u
                         ? BREAK_UI_DEFAULT_MAX_SCISSOR_AREA_PERCENT
                         : options->max_scissor_area_percent;
  if (max_area_percent > 100u || my_dirty_rects_count(damage) > max_rects ||
      !break_ui_damage_to_drawable_scissor(
          damage, options->logical_width, options->logical_height,
          options->drawable_width, options->drawable_height, &out->scissor)) {
    return true;
  }
  scissor_area = (uint64_t)out->scissor.w * out->scissor.h;
  drawable_area = (uint64_t)options->drawable_width *
                  options->drawable_height;
  if (drawable_area == 0u) {
    out->scissor = (break_ui_damage_scissor_t){0, 0, options->drawable_width,
                                               options->drawable_height};
    return true;
  }
  {
    uint64_t area_quotient = drawable_area / 100u;
    uint64_t area_remainder = drawable_area % 100u;
    uint64_t threshold = area_quotient * max_area_percent +
                         (area_remainder * max_area_percent) / 100u;
    uint64_t threshold_remainder =
        (area_remainder * max_area_percent) % 100u;
    if (scissor_area > threshold ||
        (scissor_area == threshold && threshold_remainder != 0u)) {
      out->scissor = (break_ui_damage_scissor_t){0, 0, options->drawable_width,
                                                 options->drawable_height};
      return true;
    }
  }
  out->mode = BREAK_UI_COMPOSITE_PARTIAL;
  return true;
}

void break_ui_collect_surface_damage_for_windows(
    my_window_t* const* windows, size_t count, my_dirty_rects_t* damage) {
  size_t i;
  if (damage == NULL) {
    return;
  }
  my_dirty_rects_init(damage);
  if (windows == NULL) {
    return;
  }
  for (i = 0; i < count; i++) {
    my_window_t* win = windows[i];
    size_t j;
    if (win == NULL) {
      continue;
    }
    for (j = 0; j < my_dirty_rects_count(&win->dirty); j++) {
      const my_rect_t* rect = my_dirty_rects_get(&win->dirty, j);
      if (rect != NULL) {
        (void)my_dirty_rects_add(damage, rect);
      }
    }
  }
}

void break_ui_expand_surface_damage_for_windows(
    my_window_t* const* windows, size_t count,
    const my_dirty_rects_t* damage) {
  size_t i;
  if (windows == NULL || damage == NULL) {
    return;
  }
  for (i = 0; i < count; i++) {
    my_window_t* win = windows[i];
    my_widget_t* root;
    my_rect_t bounds;
    size_t j;
    if (win == NULL) {
      continue;
    }
    root = (my_widget_t*)win;
    bounds = root->rect;
    for (j = 0; j < my_dirty_rects_count(damage); j++) {
      my_rect_t clipped;
      const my_rect_t* rect = my_dirty_rects_get(damage, j);
      if (rect != NULL && my_rect_intersect(&bounds, rect, &clipped)) {
        (void)my_dirty_rects_add(&win->dirty, &clipped);
      }
    }
  }
}

void break_ui_restore_surface_dirty_for_windows(
    my_window_t* const* windows, size_t count,
    const my_dirty_rects_t* snapshots) {
  size_t i;
  if (windows == NULL || snapshots == NULL) {
    return;
  }
  for (i = 0; i < count; i++) {
    if (windows[i] != NULL) {
      my_window_restore_dirty(windows[i], &snapshots[i]);
    }
  }
}

void break_ui_collect_surface_damage(my_window_manager_t* wm,
                                     my_dirty_rects_t* damage) {
  my_window_t** windows = NULL;
  size_t count = 0;
  if (damage == NULL) {
    return;
  }
  if (wm == NULL) {
    my_dirty_rects_init(damage);
    return;
  }
  if (my_window_manager_snapshot_windows(wm, &windows, &count) != MY_RET_OK) {
    my_dirty_rects_init(damage);
    return;
  }
  break_ui_collect_surface_damage_for_windows(windows, count, damage);
  my_window_manager_release_snapshot(wm, windows, count);
}

void break_ui_expand_surface_damage(my_window_manager_t* wm,
                                    const my_dirty_rects_t* damage) {
  my_window_t** windows = NULL;
  size_t count = 0;
  if (wm == NULL || damage == NULL) {
    return;
  }
  if (my_window_manager_snapshot_windows(wm, &windows, &count) != MY_RET_OK) {
    return;
  }
  break_ui_expand_surface_damage_for_windows(windows, count, damage);
  my_window_manager_release_snapshot(wm, windows, count);
}

void break_ui_restore_surface_dirty(my_window_manager_t* wm,
                                    const my_dirty_rects_t* snapshots) {
  size_t i;
  if (wm == NULL || snapshots == NULL) {
    return;
  }
  for (i = 0; i < my_darray_size(wm->windows); i++) {
    my_window_t* win = (my_window_t*)my_darray_get(wm->windows, i);
    my_window_restore_dirty(win, &snapshots[i]);
  }
}
