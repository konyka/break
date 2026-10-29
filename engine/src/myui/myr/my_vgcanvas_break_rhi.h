/**
 * @file my_vgcanvas_break_rhi.h
 * @brief Break RHI backend for myui's vector canvas interface.
 *
 * The canvas records triangles in myui's font-vertex layout
 * (xy + uv + RGBA) and submits them through the Break RHI. Solid geometry
 * and glyphs share a single atlas-backed pipeline; images use a second
 * RGBA-texture pipeline. Draws are replayed in issue order (consecutive
 * solids, and consecutive images of one texture, share a draw), so later
 * paint covers earlier paint across the two pipelines. Path tessellation is
 * delegated to my_vggeometry.
 * The canvas borrows an optional Break RHI offscreen target. BreakUI owns the
 * target transaction; the canvas queues quality changes requested during a
 * paint callback and never destroys or replaces the active target itself.
 */
#ifndef MY_VGCANVAS_BREAK_RHI_H
#define MY_VGCANVAS_BREAK_RHI_H

#include "myr/my_vgcanvas.h"
#include "rhi/rhi.h"

/** @brief Whether a drawable size fits myui's signed rectangle ABI. */
static inline bool my_vgcanvas_break_rhi_size_valid(u32 width, u32 height) {
  return width != 0u && height != 0u && width <= (u32)INT32_MAX &&
         height <= (u32)INT32_MAX;
}

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

/* Cancel a queued target switch without changing the active target. */
void my_vgcanvas_break_rhi_cancel_pending_antialias_level(my_vgcanvas_t *vg);

/* Map the portable AA level to the RHI target sample count. */
u32 my_vgcanvas_break_rhi_sample_count_for_aa_level(int level);

my_ret_t my_vgcanvas_break_rhi_resize(my_vgcanvas_t *vg, u32 width,
                                      u32 height);

/* Stage 4 scene editor Phase 2 Task 3 (additive extension slot): blit an
 * existing RHI texture (e.g. an offscreen FBO's color attachment) into the
 * dst rect of the current frame's command stream. Implemented with the
 * canvas's existing image pipeline/batch path — no vtable change, and the
 * CPU-bitmap image cache (image_texture()) is NOT involved: the texture
 * handle is used as-is and never inserted into the cache slots.
 *
 * Coordinates are canvas-local logical units (the current transform/scale
 * applies, exactly like draw_image): (x,y) is the dst top-left. UV
 * convention matches draw_image: texture v=0 lands at the dst TOP edge —
 * callers blitting an FBO rendered with the default bind viewport (NDC +Y ->
 * v=1 on both backends) must flip their content up front (the editor
 * viewport renderer negates the projection's Y scale).
 *
 * The blit is recorded into the CURRENT frame's batch: call between
 * my_vgcanvas_begin_frame/end_frame (typically from a widget on_paint) with
 * set_cmd() already pointing at a live command buffer. Bounded no-op errors
 * (nothing recorded): NULL/foreign canvas (not this backend), invalid
 * texture handle, non-finite or non-positive w/h, vertex or run storage
 * allocation failure (MY_RET_OOM). */
my_ret_t my_vgcanvas_break_rhi_blit_texture(my_vgcanvas_t *vg,
                                            RHITexture texture, float x,
                                            float y, float w, float h);

#endif /* MY_VGCANVAS_BREAK_RHI_H */
