#ifndef MYUI_BREAK_DAMAGE_H
#define MYUI_BREAK_DAMAGE_H

#include "myr/my_dirty_rects.h"

struct my_window_manager_t;
struct my_window_t;

void break_ui_collect_surface_damage_for_windows(
    struct my_window_t* const* windows, size_t count,
    my_dirty_rects_t* damage);
void break_ui_expand_surface_damage_for_windows(
    struct my_window_t* const* windows, size_t count,
    const my_dirty_rects_t* damage);
void break_ui_restore_surface_dirty_for_windows(
    struct my_window_t* const* windows, size_t count,
    const my_dirty_rects_t* snapshots);

void break_ui_collect_surface_damage(struct my_window_manager_t* wm,
                                     my_dirty_rects_t* damage);
void break_ui_expand_surface_damage(struct my_window_manager_t* wm,
                                    const my_dirty_rects_t* damage);

/** @brief Restore dirty snapshots after a failed shared-surface frame. */
void break_ui_restore_surface_dirty(struct my_window_manager_t* wm,
                                    const my_dirty_rects_t* snapshots);

#endif /* MYUI_BREAK_DAMAGE_H */
