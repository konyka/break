/**
 * @file my_vgcanvas_break_rhi.h
 * @brief Break RHI backend for myui's vector canvas interface.
 *
 * The canvas records triangles in myui's font-vertex layout
 * (xy + uv + RGBA) and submits them through the Break RHI. Solid geometry
 * and glyphs share a single atlas-backed pipeline; images use a second
 * RGBA-texture pipeline. Path tessellation is delegated to my_vggeometry.
 * The canvas borrows an optional Break RHI offscreen target. BreakUI owns the
 * target transaction; the canvas queues quality changes requested during a
 * paint callback and never destroys or replaces the active target itself.
 */
#ifndef MY_VGCANVAS_BREAK_RHI_H
#define MY_VGCANVAS_BREAK_RHI_H

#include "myr/my_vgcanvas.h"
#include "rhi/rhi.h"

my_vgcanvas_t *my_vgcanvas_break_rhi_create(const my_allocator_t *allocator,
                                            RHIDevice *device, u32 width,
                                            u32 height);

void my_vgcanvas_break_rhi_set_cmd(my_vgcanvas_t *vg, RHICmdBuffer *cmd);

/* Attach the currently active target without transferring ownership. Passing
 * NULL disables target-backed AA negotiation. */
void my_vgcanvas_break_rhi_set_target(my_vgcanvas_t *vg,
                                      RHIOffscreenFBO *target);
void my_vgcanvas_break_rhi_set_target_preserve_pending(
    my_vgcanvas_t *vg, RHIOffscreenFBO *target, int pending_level);

/* Returns 0 or 2 when a target switch is queued, otherwise -1. */
int my_vgcanvas_break_rhi_pending_antialias_level(const my_vgcanvas_t *vg);

/* Map the portable AA level to the RHI target sample count. */
u32 my_vgcanvas_break_rhi_sample_count_for_aa_level(int level);

my_ret_t my_vgcanvas_break_rhi_resize(my_vgcanvas_t *vg, u32 width,
                                      u32 height);

#endif /* MY_VGCANVAS_BREAK_RHI_H */
