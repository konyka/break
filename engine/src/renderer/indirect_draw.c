#include <renderer/indirect_draw.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>

/* ========================================================================
 * Helpers
 * ======================================================================== */


static RHIPipeline id_load_compute(RHIDevice *dev, const char *path) {
    usize src_len = 0;
    char *src = shader_read_file(path, &src_len);
    if (!src) {
        LOG_WARN("IndirectDraw: shader not found: %s", path);
        return RHI_HANDLE_NULL;
    }

    RHIShader cs = rhi_shader_create_compute(dev, src, src_len);
    free(src);
    if (!rhi_handle_valid(cs)) {
        LOG_WARN("IndirectDraw: compute shader compile failed: %s", path);
        return RHI_HANDLE_NULL;
    }

    RHIPipelineDesc pdesc = {0};
    pdesc.frag         = cs;
    pdesc.is_compute   = true;
    pdesc.uses_storage = true;
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, cs);

    if (!rhi_handle_valid(pipe)) {
        LOG_WARN("IndirectDraw: pipeline creation failed: %s", path);
    }
    return pipe;
}

/* ========================================================================
 * Lifecycle
 * ======================================================================== */

bool indirect_draw_init_grouped(IndirectDrawSystem *sys, RHIDevice *dev,
                                u32 max_draws, u32 group_count) {
    if (!sys || !dev || max_draws == 0) return false;
    if (group_count == 0) group_count = 1;
    if (group_count > INDIRECT_DRAW_MAX_GROUPS) group_count = INDIRECT_DRAW_MAX_GROUPS;

    memset(sys, 0, sizeof(*sys));
    sys->max_draws = max_draws;
    sys->group_count = group_count;
    /* R437: single implicit group covering the whole capacity until a
     * (grouped) upload refines the CPU-side intervals. */
    sys->group_cpu_cap[0] = max_draws;

    /* All draw commands - storage buffer (CPU-uploaded once). R186: DEVICE_LOCAL. */
    usize all_bytes = (usize)max_draws * sizeof(DrawIndexedIndirectCmd);
    void *all_zero = calloc(1, all_bytes);
    /* R362: NULL initial_data skips DEVICE_LOCAL zero-init but handle may still validate. */
    if (!all_zero) {
        LOG_WARN("IndirectDraw: all_draws zero-init alloc failed");
        return false;
    }
    RHIBufferDesc all_desc = {
        .size  = all_bytes,
        .usage = RHI_BUFFER_USAGE_STORAGE,
        .initial_data = all_zero,
    };
    sys->all_draws_buf = rhi_buffer_create(dev, &all_desc);
    free(all_zero);

    /* Compacted visible draws - both storage (compute writes) AND indirect
     * (graphics reads as draw command source). R185: DEVICE_LOCAL. */
    usize visible_bytes = (usize)max_draws * sizeof(DrawIndexedIndirectCmd);
    void *visible_zero = calloc(1, visible_bytes);
    if (!visible_zero) {
        LOG_WARN("IndirectDraw: visible_draws zero-init alloc failed");
        indirect_draw_destroy(sys, dev);
        return false;
    }
    RHIBufferDesc visible_desc = {
        .size  = visible_bytes,
        .usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT,
        .initial_data = visible_zero,
    };
    sys->visible_draws_buf = rhi_buffer_create(dev, &visible_desc);
    free(visible_zero);

    /* Atomic draw counter - storage (atomicAdd target) + indirect (count source). */
    u32 count_zero = 0u;
    RHIBufferDesc count_desc = {
        .size  = sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT,
        .initial_data = &count_zero,
    };
    sys->draw_count_buf = rhi_buffer_create(dev, &count_desc);

    /* Per-object visibility flags — host-updated dual slot; stay HOST_VISIBLE. */
    RHIBufferDesc vis_desc = {
        .size  = (usize)max_draws * sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    sys->visibility_buf[0] = rhi_buffer_create(dev, &vis_desc);
    sys->visibility_buf[1] = rhi_buffer_create(dev, &vis_desc);

    /* R437: grouped compact bookkeeping. mat_id/group_base are uploaded with
     * the draw list (zero-init = single implicit group 0 at base 0, which keeps
     * the ungrouped path byte-identical to the legacy shader behaviour).
     * group_counts is the per-group atomic cursor + indirect count source. */
    usize ids_bytes = (usize)max_draws * sizeof(u32);
    void *ids_zero = calloc(1, ids_bytes);
    if (!ids_zero) {
        LOG_WARN("IndirectDraw: mat_id zero-init alloc failed");
        indirect_draw_destroy(sys, dev);
        return false;
    }
    RHIBufferDesc ids_desc = {
        .size  = ids_bytes,
        .usage = RHI_BUFFER_USAGE_STORAGE,
        .initial_data = ids_zero,
    };
    sys->mat_id_buf = rhi_buffer_create(dev, &ids_desc);
    sys->group_base_buf = rhi_buffer_create(dev, &ids_desc);
    free(ids_zero);

    usize gc_bytes = (usize)group_count * sizeof(u32);
    void *gc_zero = calloc(1, gc_bytes);
    if (!gc_zero) {
        LOG_WARN("IndirectDraw: group_counts zero-init alloc failed");
        indirect_draw_destroy(sys, dev);
        return false;
    }
    RHIBufferDesc gc_desc = {
        .size  = gc_bytes,
        .usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT,
        .initial_data = gc_zero,
    };
    sys->group_counts_buf = rhi_buffer_create(dev, &gc_desc);
    free(gc_zero);

    if (!rhi_handle_valid(sys->all_draws_buf) ||
        !rhi_handle_valid(sys->visible_draws_buf) ||
        !rhi_handle_valid(sys->draw_count_buf) ||
        !rhi_handle_valid(sys->visibility_buf[0]) ||
        !rhi_handle_valid(sys->visibility_buf[1]) ||
        !rhi_handle_valid(sys->mat_id_buf) ||
        !rhi_handle_valid(sys->group_base_buf) ||
        !rhi_handle_valid(sys->group_counts_buf)) {
        LOG_WARN("IndirectDraw: buffer creation failed");
        indirect_draw_destroy(sys, dev);
        return false;
    }

    /* The compact compute shader uses #ifdef VULKAN internally (auto-defined
     * by shaderc) to switch between push-constant and uniform layouts. The
     * same source file therefore works on both backends. */
    sys->compact_pipeline = id_load_compute(dev, "shaders/compact_draws.comp");
    if (!rhi_handle_valid(sys->compact_pipeline)) {
        LOG_WARN("IndirectDraw: compact pipeline failed to load");
        indirect_draw_destroy(sys, dev);
        return false;
    }

    sys->ready = true;
    sys->_loc_total_draws = rhi_pipeline_get_uniform_location(dev, sys->compact_pipeline, "total_draws");
    LOG_INFO("IndirectDraw: initialized (max %u draws, %u groups)", max_draws, group_count);
    return true;
}

bool indirect_draw_init(IndirectDrawSystem *sys, RHIDevice *dev, u32 max_draws) {
    /* R437: ungrouped = one implicit group. */
    return indirect_draw_init_grouped(sys, dev, max_draws, 1);
}

void indirect_draw_destroy(IndirectDrawSystem *sys, RHIDevice *dev) {
    if (!sys || !dev) return;
    if (rhi_handle_valid(sys->compact_pipeline)) {
        rhi_pipeline_destroy(dev, sys->compact_pipeline);
        sys->compact_pipeline = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->group_counts_buf)) {
        rhi_buffer_destroy(dev, sys->group_counts_buf);
        sys->group_counts_buf = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->group_base_buf)) {
        rhi_buffer_destroy(dev, sys->group_base_buf);
        sys->group_base_buf = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->mat_id_buf)) {
        rhi_buffer_destroy(dev, sys->mat_id_buf);
        sys->mat_id_buf = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->visibility_buf[0])) {
        rhi_buffer_destroy(dev, sys->visibility_buf[0]);
        sys->visibility_buf[0] = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->visibility_buf[1])) {
        rhi_buffer_destroy(dev, sys->visibility_buf[1]);
        sys->visibility_buf[1] = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->draw_count_buf)) {
        rhi_buffer_destroy(dev, sys->draw_count_buf);
        sys->draw_count_buf = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->visible_draws_buf)) {
        rhi_buffer_destroy(dev, sys->visible_draws_buf);
        sys->visible_draws_buf = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->all_draws_buf)) {
        rhi_buffer_destroy(dev, sys->all_draws_buf);
        sys->all_draws_buf = RHI_HANDLE_NULL;
    }
    sys->ready = false;
    sys->max_draws = 0;
    sys->current_draw_count = 0;
    sys->group_count = 0;
}

/* ========================================================================
 * Per-frame data upload
 * ======================================================================== */

void indirect_draw_upload(IndirectDrawSystem *sys, RHIDevice *dev,
                          const DrawIndexedIndirectCmd *cmds, u32 count) {
    /* R437: single implicit group covering [0,count). Goes through the grouped
     * path so mat_id/group_base are refreshed too (a stale grouped upload on
     * the same system must not leak its intervals). */
    indirect_draw_upload_grouped(sys, dev, cmds, &count, 1);
}

void indirect_draw_upload_grouped(IndirectDrawSystem *sys, RHIDevice *dev,
                                  const DrawIndexedIndirectCmd *cmds,
                                  const u32 *group_sizes, u32 group_count) {
    if (!sys || !sys->ready || !cmds || !group_sizes || group_count == 0) return;
    if (group_count > sys->group_count) {
        /* R437: intervals/counters are sized at init — refuse to overrun. */
        LOG_WARN("IndirectDraw: upload_grouped group_count %u > init %u",
                 group_count, sys->group_count);
        return;
    }

    u32 count = 0;
    for (u32 g = 0; g < group_count; g++) count += group_sizes[g];
    if (count == 0) return;
    if (count > sys->max_draws) count = sys->max_draws;

    /* R437: per-cmd group index + capacity base, derived from the group-size
     * prefix sums. Scatter target = group_base[idx] + atomic cursor of
     * mat_id[idx]; intervals are CPU-known so execute needs no readback. */
    u32 *mat_id = malloc((usize)count * sizeof(u32));
    u32 *base   = malloc((usize)count * sizeof(u32));
    if (!mat_id || !base) {
        LOG_WARN("IndirectDraw: grouped upload scratch alloc failed");
        free(mat_id); free(base);
        return;
    }
    u32 run = 0, ci = 0;
    for (u32 g = 0; g < group_count; g++) {
        sys->group_cpu_base[g] = run;
        sys->group_cpu_cap[g]  = group_sizes[g];
        for (u32 k = 0; k < group_sizes[g] && ci < count; k++, ci++) {
            mat_id[ci] = g;
            base[ci]   = run;
        }
        run += group_sizes[g];
    }

    rhi_buffer_update_region(dev, sys->all_draws_buf, 0, cmds,
                             (usize)count * sizeof(DrawIndexedIndirectCmd));
    rhi_buffer_update_region(dev, sys->mat_id_buf, 0, mat_id,
                             (usize)count * sizeof(u32));
    rhi_buffer_update_region(dev, sys->group_base_buf, 0, base,
                             (usize)count * sizeof(u32));
    free(mat_id);
    free(base);
    sys->current_draw_count = count;
}

void indirect_draw_upload_visibility(IndirectDrawSystem *sys, RHIDevice *dev,
                                     const u32 *flags, u32 count) {
    if (!sys || !sys->ready || !flags || count == 0) return;
    if (count > sys->max_draws) count = sys->max_draws;
    /* R182: write the slot that this frame's compact will read. */
    rhi_buffer_update_region(dev, indirect_draw_visibility_slot(sys, dev), 0, flags,
                             (usize)count * sizeof(u32));
}

void indirect_draw_upload_visibility_cmd(IndirectDrawSystem *sys, RHIDevice *dev,
                                         RHICmdBuffer *cmd, const u32 *flags, u32 count) {
    if (!sys || !sys->ready || !cmd || !flags || count == 0) return;
    if (count > sys->max_draws) count = sys->max_draws;
    /* R183: CB-ordered write — safe when the same slot is rewritten per cascade. */
    rhi_cmd_update_buffer(cmd, indirect_draw_visibility_slot(sys, dev), 0, flags,
                          (usize)count * sizeof(u32));
}

/* ========================================================================
 * GPU compact: dispatch compute shader to compact visible draws
 * ======================================================================== */

/* R437: compact dispatch counter (observability for the merged per-material
 * path: all groups must cost exactly 1 dispatch per frame). */
static u32 g_id_compact_count = 0u;

u32 indirect_draw_debug_compact_count(void) { return g_id_compact_count; }
void indirect_draw_debug_reset_compact_count(void) { g_id_compact_count = 0u; }

/* R441: execute counter (observability for the material-array path: the whole
 * forward mega draw must cost exactly 1 indirect execute per frame). */
static u32 g_id_execute_count = 0u;

u32 indirect_draw_debug_execute_count(void) { return g_id_execute_count; }
void indirect_draw_debug_reset_execute_count(void) { g_id_execute_count = 0u; }

void indirect_draw_compact(IndirectDrawSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd) {
    indirect_draw_compact_no_barrier(sys, dev, cmd);
    rhi_cmd_memory_barrier(cmd);
}

void indirect_draw_compact_no_barrier(IndirectDrawSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd) {
    if (!sys || !sys->ready || sys->current_draw_count == 0) return;

    /* R175: GPU fill so reset is ordered with this CB's compact dispatch
     * (host rhi_buffer_update is invisible to later recorded GPU work). */
    rhi_cmd_fill_buffer(cmd, sys->draw_count_buf, 0, sizeof(u32), 0u);
    /* R437: reset per-group scatter cursors (doubling as per-group visible
     * counts consumed by indirect_draw_execute_group). */
    rhi_cmd_fill_buffer(cmd, sys->group_counts_buf, 0,
                        (usize)sys->group_count * sizeof(u32), 0u);
    /* R234-B: Zero visible slots before compact so VK IndirectCount fallback
     * (draw max_draws) cannot resurrect stale surplus commands. Matches
     * gpucull_dispatch_unified (R171). Live slots are rewritten by compact. */
    rhi_cmd_fill_buffer(cmd, sys->visible_draws_buf, 0,
                        (usize)sys->current_draw_count * sizeof(DrawIndexedIndirectCmd), 0u);

    rhi_cmd_bind_pipeline(cmd, sys->compact_pipeline);
    rhi_cmd_bind_storage_buffer(cmd, sys->all_draws_buf,     0);
    rhi_cmd_bind_storage_buffer(cmd, indirect_draw_visibility_slot(sys, dev), 1);
    rhi_cmd_bind_storage_buffer(cmd, sys->visible_draws_buf, 2);
    rhi_cmd_bind_storage_buffer(cmd, sys->draw_count_buf,    3);
    /* R437: grouped scatter inputs/outputs (bindings 4..6). */
    rhi_cmd_bind_storage_buffer(cmd, sys->mat_id_buf,        4);
    rhi_cmd_bind_storage_buffer(cmd, sys->group_counts_buf,  5);
    rhi_cmd_bind_storage_buffer(cmd, sys->group_base_buf,    6);

    /* Push the total draw count (uniform/push-constant: name "total_draws"). */
    if (sys->_loc_total_draws >= 0) {
        rhi_cmd_set_uniform_i32(cmd, sys->_loc_total_draws, (i32)sys->current_draw_count);
    }

    u32 groups = (sys->current_draw_count + 63u) / 64u;
    rhi_cmd_dispatch(cmd, groups, 1, 1);
    g_id_compact_count++; /* R437 */

    /* R76-3: Barrier moved to caller — allows batching multiple groups'
     * compacts before a single rhi_cmd_memory_barrier. */
}

/* ========================================================================
 * Execute the compacted indirect draw
 * ======================================================================== */

void indirect_draw_execute(IndirectDrawSystem *sys, RHIDevice *dev) {
    /* R437: ungrouped execute = group 0 over the whole uploaded range. */
    indirect_draw_execute_group(sys, dev, 0);
}

void indirect_draw_execute_group(IndirectDrawSystem *sys, RHIDevice *dev, u32 group) {
    if (!sys || !sys->ready || sys->current_draw_count == 0) return;
    if (group >= sys->group_count) return;
    u32 cap = sys->group_cpu_cap[group];
    if (cap == 0) return; /* R437: empty group — nothing could have scattered. */

    /* R437: offset = CPU-known capacity base; count source = the group's
     * compact cursor. R234-B fallback safety: the whole uploaded range is
     * zero-filled before compact, so drawing `cap` surplus slots after the
     * live ones only emits indexCount=0 no-ops. */
    rhi_cmd_draw_indexed_indirect_count(
        dev,
        sys->visible_draws_buf, sys->group_cpu_base[group] * (u32)sizeof(DrawIndexedIndirectCmd),
        sys->group_counts_buf,  group * (u32)sizeof(u32),
        cap,
        (u32)sizeof(DrawIndexedIndirectCmd));
    g_id_execute_count++; /* R441 */
}
