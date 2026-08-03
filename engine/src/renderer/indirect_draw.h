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

/* R437: upper bound on material groups a single system can compact at once
 * (matches MEGA_MAX_MAT_GROUPS in main.c). */
#define INDIRECT_DRAW_MAX_GROUPS 64

typedef struct {
    RHIBuffer   all_draws_buf;      /* STORAGE: every potential draw */
    RHIBuffer   visible_draws_buf;  /* STORAGE | INDIRECT: compacted visible draws */
    RHIBuffer   draw_count_buf;     /* STORAGE | INDIRECT: atomic counter */
    RHIBuffer   visibility_buf[2];  /* R182: dual-slot host upload vs in-flight GPU read */
    RHIPipeline compact_pipeline;   /* compute pipeline running compact_draws.comp */
    u32         max_draws;
    u32         current_draw_count; /* CPU-side count of entries uploaded this frame */
    bool        ready;
    i32         _loc_total_draws;  /* cached uniform location */
    /* R437: grouped (per-material) compact. Cmds are uploaded sorted by group;
     * the compact shader scatters each visible cmd into its group's capacity
     * interval [group_cpu_base[g], group_cpu_base[g]+group_cpu_cap[g]) using a
     * per-group atomic cursor (group_counts_buf[g]). Group intervals are
     * CPU-known capacity prefix sums — NOT prefix sums of visible counts —
     * because indirect_draw_execute needs the cmd-buffer offset as a CPU-side
     * value (vkCmdDrawIndexedIndirectCount / glMultiDrawElementsIndirectCount
     * take no GPU-side offset indirection). One compact dispatch covers all
     * groups; execute loops groups with per-group offset+count source. */
    RHIBuffer   mat_id_buf;         /* STORAGE: per-cmd group index */
    RHIBuffer   group_base_buf;     /* STORAGE: per-cmd group capacity base slot */
    RHIBuffer   group_counts_buf;   /* STORAGE | INDIRECT: per-group visible cursors */
    u32         group_count;
    u32         group_cpu_base[INDIRECT_DRAW_MAX_GROUPS]; /* capacity prefix sums */
    u32         group_cpu_cap[INDIRECT_DRAW_MAX_GROUPS];  /* per-group cmd capacity */
} IndirectDrawSystem;

/* Current-frame visibility slot (rhi_frame_index & 1). */
static inline RHIBuffer indirect_draw_visibility_slot(const IndirectDrawSystem *sys, RHIDevice *dev) {
    return sys->visibility_buf[rhi_frame_index(dev) & 1u];
}

/* Lifecycle */
bool indirect_draw_init(IndirectDrawSystem *sys, RHIDevice *dev, u32 max_draws);
/* R437: grouped variant — reserves group bookkeeping for up to group_count
 * material groups (clamped to INDIRECT_DRAW_MAX_GROUPS). */
bool indirect_draw_init_grouped(IndirectDrawSystem *sys, RHIDevice *dev,
                                u32 max_draws, u32 group_count);
void indirect_draw_destroy(IndirectDrawSystem *sys, RHIDevice *dev);

/* Per-frame: refresh draw command list (CPU side). */
void indirect_draw_upload(IndirectDrawSystem *sys, RHIDevice *dev,
                          const DrawIndexedIndirectCmd *cmds, u32 count);
/* R437: grouped upload — cmds must be sorted by group; group_sizes[g] is the
 * number of consecutive cmds belonging to group g (sum = total cmd count).
 * Derives per-cmd mat_id / group capacity base and uploads them too. */
void indirect_draw_upload_grouped(IndirectDrawSystem *sys, RHIDevice *dev,
                                  const DrawIndexedIndirectCmd *cmds,
                                  const u32 *group_sizes, u32 group_count);

/* Per-frame: refresh visibility flags (one u32 per object: 1 visible / 0 culled). */
void indirect_draw_upload_visibility(IndirectDrawSystem *sys, RHIDevice *dev,
                                     const u32 *flags, u32 count);

/* R183: Same as upload_visibility but records the write into `cmd` so multiple
 * cascade/face uploads in one CB stay ordered with their compact dispatches. */
void indirect_draw_upload_visibility_cmd(IndirectDrawSystem *sys, RHIDevice *dev,
                                         RHICmdBuffer *cmd, const u32 *flags, u32 count);

/* GPU compact: read visibility, append visible commands, atomically increment count.
 * Includes a memory barrier after the compute dispatch. */
void indirect_draw_compact(IndirectDrawSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd);

/* R76-3: Same as indirect_draw_compact but without the trailing memory barrier.
 * Allows batching multiple groups' compacts before a single barrier,
 * reducing G barriers per pass to 1. Caller must issue rhi_cmd_memory_barrier
 * before indirect_draw_execute. */
void indirect_draw_compact_no_barrier(IndirectDrawSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd);

/* Issue the indirect draw using the compacted command + count buffers. */
void indirect_draw_execute(IndirectDrawSystem *sys, RHIDevice *dev);

/* R437: execute only one material group's capacity interval. The cmd-buffer
 * offset (CPU-known capacity prefix sum) and count source (group_counts_buf[g])
 * let the caller loop groups with per-group material binds after a single
 * merged compact. Groups with zero capacity are skipped. */
void indirect_draw_execute_group(IndirectDrawSystem *sys, RHIDevice *dev, u32 group);

/* R437: observability — number of compact dispatches issued since the last
 * reset. The merged per-material path must cost exactly 1 per frame. */
u32  indirect_draw_debug_compact_count(void);
void indirect_draw_debug_reset_compact_count(void);

#endif /* INDIRECT_DRAW_H */
