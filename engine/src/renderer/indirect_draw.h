#ifndef INDIRECT_DRAW_H
#define INDIRECT_DRAW_H

#include <rhi/rhi.h>
#include <core/types.h>

/*
 * Indirect draw / GPU-driven rendering pipeline.
 *
 * Pipeline stages:
 *  1. CPU uploads the full set of DrawIndexedIndirectCmd entries into
 *     all_draws_buf (one entry per renderable).
 *  2. A separate culling pass (frustum + Hi-Z occlusion) writes a per-object
 *     visibility flag (1 = visible, 0 = culled) into visibility_buf.
 *  3. indirect_draw_compact dispatches the compact compute shader, which
 *     atomically appends visible commands into visible_draws_buf and
 *     increments draw_count_buf.
 *  4. indirect_draw_execute issues a single
 *     vkCmdDrawIndexedIndirectCount / glMultiDrawElementsIndirectCount call
 *     that reads visible_draws_buf as the indirect source and
 *     draw_count_buf as the count source.
 *
 * The DrawIndexedIndirectCmd layout matches both
 *   VkDrawIndexedIndirectCommand (Vulkan)
 * and
 *   GL DrawElementsIndirectCommand (OpenGL),
 * so the same buffer can be consumed by either backend.
 */

typedef struct {
    u32 index_count;
    u32 instance_count;
    u32 first_index;
    i32 vertex_offset;
    u32 first_instance;
} DrawIndexedIndirectCmd;

typedef struct {
    RHIBuffer   all_draws_buf;      /* STORAGE: every potential draw */
    RHIBuffer   visible_draws_buf;  /* STORAGE | INDIRECT: compacted visible draws */
    RHIBuffer   draw_count_buf;     /* STORAGE | INDIRECT: atomic counter */
    RHIBuffer   visibility_buf;     /* STORAGE: per-object visibility flags */
    RHIPipeline compact_pipeline;   /* compute pipeline running compact_draws.comp */
    u32         max_draws;
    u32         current_draw_count; /* CPU-side count of entries uploaded this frame */
    bool        ready;
    i32         _loc_total_draws;  /* cached uniform location */
} IndirectDrawSystem;

/* Lifecycle */
bool indirect_draw_init(IndirectDrawSystem *sys, RHIDevice *dev, u32 max_draws);
void indirect_draw_destroy(IndirectDrawSystem *sys, RHIDevice *dev);

/* Per-frame: refresh draw command list (CPU side). */
void indirect_draw_upload(IndirectDrawSystem *sys, RHIDevice *dev,
                          const DrawIndexedIndirectCmd *cmds, u32 count);

/* Per-frame: refresh visibility flags (one u32 per object: 1 visible / 0 culled). */
void indirect_draw_upload_visibility(IndirectDrawSystem *sys, RHIDevice *dev,
                                     const u32 *flags, u32 count);

/* GPU compact: read visibility, append visible commands, atomically increment count. */
void indirect_draw_compact(IndirectDrawSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd);

/* Issue the indirect draw using the compacted command + count buffers. */
void indirect_draw_execute(IndirectDrawSystem *sys, RHIDevice *dev);

#endif /* INDIRECT_DRAW_H */
