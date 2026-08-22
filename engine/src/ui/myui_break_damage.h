#ifndef MYUI_BREAK_DAMAGE_H
#define MYUI_BREAK_DAMAGE_H

#include <stdint.h>

#include "myr/my_dirty_rects.h"

struct my_window_manager_t;
struct my_window_t;

/** @brief Conservative drawable-pixel scissor for a logical damage set. */
typedef struct break_ui_damage_scissor_t {
  uint32_t x;
  uint32_t y;
  uint32_t w;
  uint32_t h;
} break_ui_damage_scissor_t;

/** @brief Map logical damage to a conservative drawable bounding scissor. */
bool break_ui_damage_to_drawable_scissor(
    const my_dirty_rects_t* damage, uint32_t logical_width,
    uint32_t logical_height, uint32_t drawable_width,
    uint32_t drawable_height, break_ui_damage_scissor_t* out);

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
