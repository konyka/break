#include "ui/myui_break_damage.h"

#include "myui/my_window_manager.h"

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
