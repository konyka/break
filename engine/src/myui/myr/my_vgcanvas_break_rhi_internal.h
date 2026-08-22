#ifndef MY_VGCANVAS_BREAK_RHI_INTERNAL_H
#define MY_VGCANVAS_BREAK_RHI_INTERNAL_H

#include "myr/my_rect.h"

static inline u32 my_vgcanvas_break_rhi_sample_count_for_aa_level_internal(int level) {
  return level == 2 ? 2u : 1u;
}

static inline bool my_vgcanvas_break_rhi_aa_level_is_supported(int level) {
  return level == 0 || level == 2;
}

static inline int my_vgcanvas_break_rhi_preserved_pending_level(
    int pending_level, u32 target_sample_count) {
  if (!my_vgcanvas_break_rhi_aa_level_is_supported(pending_level) ||
      target_sample_count ==
          my_vgcanvas_break_rhi_sample_count_for_aa_level_internal(
              pending_level)) {
    return -1;
  }
  return pending_level;
}

/* Keep an implicit full-surface clip full after a drawable resize. Explicit
 * clips stay in device coordinates and are clamped to the new surface. */
static inline my_rect_t my_vgcanvas_break_rhi_resize_clip(my_rect_t clip,
                                                          u32 old_width,
                                                          u32 old_height,
                                                          u32 new_width,
                                                          u32 new_height) {
  my_rect_t surface = my_rect_init(0, 0, (int32_t)new_width,
                                   (int32_t)new_height);
  my_rect_t clipped;
  if (clip.x == 0 && clip.y == 0 && clip.w == (int32_t)old_width &&
      clip.h == (int32_t)old_height) {
    return surface;
  }
  return my_rect_intersect(&clip, &surface, &clipped)
             ? clipped
             : my_rect_init(0, 0, 0, 0);
}

#endif /* MY_VGCANVAS_BREAK_RHI_INTERNAL_H */
