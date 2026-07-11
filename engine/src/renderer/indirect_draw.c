#include <renderer/indirect_draw.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================
 * Helpers
 * ======================================================================== */

static char *id_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    char *buf = (char *)malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

static RHIPipeline id_load_compute(RHIDevice *dev, const char *path) {
    usize src_len = 0;
    char *src = id_read_file(path, &src_len);
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

bool indirect_draw_init(IndirectDrawSystem *sys, RHIDevice *dev, u32 max_draws) {
    if (!sys || !dev || max_draws == 0) return false;

    memset(sys, 0, sizeof(*sys));
    sys->max_draws = max_draws;

    /* All draw commands - storage buffer (CPU-uploaded once). R186: DEVICE_LOCAL. */
    usize all_bytes = (usize)max_draws * sizeof(DrawIndexedIndirectCmd);
    void *all_zero = calloc(1, all_bytes);
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

    if (!rhi_handle_valid(sys->all_draws_buf) ||
        !rhi_handle_valid(sys->visible_draws_buf) ||
        !rhi_handle_valid(sys->draw_count_buf) ||
        !rhi_handle_valid(sys->visibility_buf[0]) ||
        !rhi_handle_valid(sys->visibility_buf[1])) {
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
    LOG_INFO("IndirectDraw: initialized (max %u draws)", max_draws);
    return true;
}

void indirect_draw_destroy(IndirectDrawSystem *sys, RHIDevice *dev) {
    if (!sys || !dev) return;
    if (rhi_handle_valid(sys->compact_pipeline)) {
        rhi_pipeline_destroy(dev, sys->compact_pipeline);
        sys->compact_pipeline = RHI_HANDLE_NULL;
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
}

/* ========================================================================
 * Per-frame data upload
 * ======================================================================== */

void indirect_draw_upload(IndirectDrawSystem *sys, RHIDevice *dev,
                          const DrawIndexedIndirectCmd *cmds, u32 count) {
    if (!sys || !sys->ready || !cmds || count == 0) return;
    if (count > sys->max_draws) count = sys->max_draws;

    rhi_buffer_update_region(dev, sys->all_draws_buf, 0, cmds,
                             (usize)count * sizeof(DrawIndexedIndirectCmd));
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

void indirect_draw_compact(IndirectDrawSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd) {
    indirect_draw_compact_no_barrier(sys, dev, cmd);
    rhi_cmd_memory_barrier(cmd);
}

void indirect_draw_compact_no_barrier(IndirectDrawSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd) {
    if (!sys || !sys->ready || sys->current_draw_count == 0) return;

    /* R175: GPU fill so reset is ordered with this CB's compact dispatch
     * (host rhi_buffer_update is invisible to later recorded GPU work). */
    rhi_cmd_fill_buffer(cmd, sys->draw_count_buf, 0, sizeof(u32), 0u);

    rhi_cmd_bind_pipeline(cmd, sys->compact_pipeline);
    rhi_cmd_bind_storage_buffer(cmd, sys->all_draws_buf,     0);
    rhi_cmd_bind_storage_buffer(cmd, indirect_draw_visibility_slot(sys, dev), 1);
    rhi_cmd_bind_storage_buffer(cmd, sys->visible_draws_buf, 2);
    rhi_cmd_bind_storage_buffer(cmd, sys->draw_count_buf,    3);

    /* Push the total draw count (uniform/push-constant: name "total_draws"). */
    if (sys->_loc_total_draws >= 0) {
        rhi_cmd_set_uniform_i32(cmd, sys->_loc_total_draws, (i32)sys->current_draw_count);
    }

    u32 groups = (sys->current_draw_count + 63u) / 64u;
    rhi_cmd_dispatch(cmd, groups, 1, 1);

    /* R76-3: Barrier moved to caller — allows batching multiple groups'
     * compacts before a single rhi_cmd_memory_barrier. */
}

/* ========================================================================
 * Execute the compacted indirect draw
 * ======================================================================== */

void indirect_draw_execute(IndirectDrawSystem *sys, RHIDevice *dev) {
    if (!sys || !sys->ready || sys->current_draw_count == 0) return;

    rhi_cmd_draw_indexed_indirect_count(
        dev,
        sys->visible_draws_buf, 0,
        sys->draw_count_buf,    0,
        sys->current_draw_count,
        (u32)sizeof(DrawIndexedIndirectCmd));
}
