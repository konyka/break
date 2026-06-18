#include <renderer/gpucull.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emmintrin.h>  /* SSE2 for SoA→AoS pack */

static char *gc_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

bool gpucull_init(GPUCullSystem *gc, RHIDevice *dev) {
    memset(gc, 0, sizeof(*gc));
    gc->device = dev;
    gc->unified_ready = false;

    usize cs_len = 0;
    char *cs_src = gc_read_file("shaders/cull.comp", &cs_len);
    if (!cs_src) {
        LOG_WARN("GPUCull: compute shader not found");
        return false;
    }

    RHIShader cs = rhi_shader_create_compute(dev, cs_src, cs_len);
    free(cs_src);
    if (!rhi_handle_valid(cs)) {
        LOG_WARN("GPUCull: shader compile failed");
        return false;
    }

    RHIPipelineDesc pdesc = {0};
    pdesc.frag = cs;
    pdesc.is_compute = true;
    pdesc.uses_storage = true;
    gc->cull_pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, cs);

    if (!rhi_handle_valid(gc->cull_pipe)) {
        LOG_WARN("GPUCull: pipeline creation failed");
        return false;
    }

    RHIBufferDesc obj_desc = {
        .size = GPUCULL_MAX_OBJECTS * sizeof(f32) * 4,
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    gc->object_ssbo = rhi_buffer_create(dev, &obj_desc);

    RHIBufferDesc vis_desc = {
        .size = GPUCULL_MAX_OBJECTS * sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    gc->visible_ssbo = rhi_buffer_create(dev, &vis_desc);

    RHIBufferDesc count_desc = {
        .size = sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    gc->count_buf = rhi_buffer_create(dev, &count_desc);

    gc->ready = true;

    /* Cache uniform locations for legacy pipeline */
    gc->_loc_cull_vp    = rhi_pipeline_get_uniform_location(dev, gc->cull_pipe, "u_cull_vp");
    gc->_loc_cull_count = rhi_pipeline_get_uniform_location(dev, gc->cull_pipe, "u_cull_count");

    /* Pre-allocate persistent pack + zero buffer (single alloc: _pack_buf + _zero_buf) */
    gc->_pack_buf_cap = GPUCULL_MAX_OBJECTS * 4;
    gc->_zero_buf_cap = GPUCULL_MAX_OBJECTS;
    usize pb_bytes = (usize)gc->_pack_buf_cap * sizeof(f32);
    usize zb_off   = (pb_bytes + 3u) & ~(usize)3u;
    usize zb_bytes = (usize)gc->_zero_buf_cap * sizeof(u32);
    u8 *gc_block   = (u8 *)malloc(zb_off + zb_bytes);
    gc->_pack_buf   = (f32 *)gc_block;
    gc->_zero_buf   = (u32 *)(gc_block + pb_bytes);  /* pre-allocated, zeroed on first use */

    LOG_INFO("GPUCull: initialized (max %u objects)", GPUCULL_MAX_OBJECTS);
    return true;
}

void gpucull_shutdown(GPUCullSystem *gc) {
    if (!gc->device) return;
    
    /* Free persistent staging buffers (single alloc: _pack_buf + _zero_buf) */
    if (gc->_pack_buf)  { free(gc->_pack_buf);  gc->_pack_buf  = NULL; gc->_pack_buf_cap  = 0; gc->_zero_buf = NULL; gc->_zero_buf_cap = 0; }

    /* Destroy unified pipeline resources */
    if (gc->unified_ready) {
        if (rhi_handle_valid(gc->unified_cull_pipe)) rhi_pipeline_destroy(gc->device, gc->unified_cull_pipe);
        if (rhi_handle_valid(gc->draw_cmds_ssbo)) rhi_buffer_destroy(gc->device, gc->draw_cmds_ssbo);
        if (rhi_handle_valid(gc->visible_draws_ssbo)) rhi_buffer_destroy(gc->device, gc->visible_draws_ssbo);
        if (rhi_handle_valid(gc->draw_count_buf)) rhi_buffer_destroy(gc->device, gc->draw_count_buf);
        if (rhi_handle_valid(gc->visible_flags_ssbo)) rhi_buffer_destroy(gc->device, gc->visible_flags_ssbo);
        if (rhi_handle_valid(gc->hi_z_sampler)) rhi_sampler_destroy(gc->device, gc->hi_z_sampler);
        if (rhi_handle_valid(gc->hi_z_fallback)) rhi_texture_destroy(gc->device, gc->hi_z_fallback);
    }
    
    /* Destroy legacy pipeline resources */
    if (rhi_handle_valid(gc->count_buf)) rhi_buffer_destroy(gc->device, gc->count_buf);
    if (rhi_handle_valid(gc->visible_ssbo)) rhi_buffer_destroy(gc->device, gc->visible_ssbo);
    if (rhi_handle_valid(gc->object_ssbo)) rhi_buffer_destroy(gc->device, gc->object_ssbo);
    if (rhi_handle_valid(gc->cull_pipe)) rhi_pipeline_destroy(gc->device, gc->cull_pipe);
    
    gc->ready = false;
    gc->unified_ready = false;
}

void gpucull_update_objects(GPUCullSystem *gc, const f32 *positions, const f32 *radii, u32 count) {
    if (!gc->ready || count == 0) return;
    gc->object_count = count > GPUCULL_MAX_OBJECTS ? GPUCULL_MAX_OBJECTS : count;

    /* R74-1: Scalar pack — SSE shuffle _mm_movelh_ps(pos, shuffle(pos, rad, 0,0,2,2))
     * produced (x,y,z,z) instead of (x,y,z,r), silently replacing radius with z.
     * The scalar loop is correct and equally fast (one element per iteration either way). */
    f32 *data = gc->_pack_buf;
    for (u32 i = 0; i < gc->object_count; i++) {
        data[i * 4 + 0] = positions[i * 3 + 0];
        data[i * 4 + 1] = positions[i * 3 + 1];
        data[i * 4 + 2] = positions[i * 3 + 2];
        data[i * 4 + 3] = radii[i];
    }
    rhi_buffer_update(gc->device, gc->object_ssbo, data, gc->object_count * 4 * sizeof(f32));
}

/* Internal: dispatch frustum cull, writing per-object visibility flags (1/0)
 * into `flags_buf` at binding 1. The cull shader (cull.comp) is guarded by the
 * actual object count, so a flags buffer sized to object_count is safe. */
static void gpucull_dispatch_to(GPUCullSystem *gc, RHICmdBuffer *cmd,
                                const f32 *vp, RHIBuffer flags_buf) {
    if (!gc->ready || gc->object_count == 0) return;

    u32 zero = 0;
    rhi_buffer_update(gc->device, gc->count_buf, &zero, sizeof(u32));

    rhi_cmd_bind_pipeline(cmd, gc->cull_pipe);
    rhi_cmd_bind_storage_buffer(cmd, gc->object_ssbo, 0);
    rhi_cmd_bind_storage_buffer(cmd, flags_buf, 1);
    rhi_cmd_bind_storage_buffer(cmd, gc->count_buf, 2);

    if (gc->_loc_cull_vp >= 0)    rhi_cmd_set_uniform_mat4(cmd, gc->_loc_cull_vp, vp);
    if (gc->_loc_cull_count >= 0) rhi_cmd_set_uniform_i32(cmd, gc->_loc_cull_count, (i32)gc->object_count);

    u32 groups = (gc->object_count + 63) / 64;
    rhi_cmd_dispatch(cmd, groups, 1, 1);
    rhi_cmd_memory_barrier(cmd);
}

void gpucull_dispatch(GPUCullSystem *gc, RHICmdBuffer *cmd, const f32 *vp) {
    gpucull_dispatch_to(gc, cmd, vp, gc->visible_ssbo);
}

void gpucull_dispatch_flags(GPUCullSystem *gc, RHICmdBuffer *cmd,
                            const f32 *vp, RHIBuffer flags_buf) {
    if (!rhi_handle_valid(flags_buf)) return;
    gpucull_dispatch_to(gc, cmd, vp, flags_buf);
}

void gpucull_get_results(GPUCullSystem *gc, u32 *out_visible_count) {
    if (!gc->ready || !out_visible_count) return;
    *out_visible_count = gc->object_count;
}

/* ============================================================
 * Unified Culling Pipeline
 * Combines frustum culling + occlusion culling + draw compaction
 * into a single compute pass for maximum GPU efficiency.
 * ============================================================ */

bool gpucull_init_unified(GPUCullSystem *gc, RHIDevice *dev) {
    if (!gc || !dev) return false;
    
    /* Initialize base system if not already done */
    if (!gc->ready) {
        if (!gpucull_init(gc, dev)) return false;
    }
    
    gc->device = dev;
    
    /* Load unified culling compute shader */
    usize cs_len = 0;
    char *cs_src = gc_read_file("shaders/unified_cull.comp", &cs_len);
    if (!cs_src) {
        LOG_WARN("UnifiedCull: compute shader not found, using fallback");
        /* Create a minimal inline shader as fallback */
        gc->unified_cull_pipe = RHI_HANDLE_NULL;
        gc->unified_ready = false;
        return true; /* Not a fatal error - can use legacy path */
    }
    
    RHIShader cs = rhi_shader_create_compute(dev, cs_src, cs_len);
    free(cs_src);
    
    if (!rhi_handle_valid(cs)) {
        LOG_WARN("UnifiedCull: shader compile failed");
        gc->unified_ready = false;
        return true;
    }
    
    RHIPipelineDesc pdesc = {0};
    pdesc.frag = cs;
    pdesc.is_compute = true;
    pdesc.uses_storage = true;
    gc->unified_cull_pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, cs);
    
    if (!rhi_handle_valid(gc->unified_cull_pipe)) {
        LOG_WARN("UnifiedCull: pipeline creation failed");
        gc->unified_ready = false;
        return true;
    }
    
    /* Create draw commands SSBO (input) */
    RHIBufferDesc draw_desc = {
        .size = GPUCULL_MAX_DRAWS * sizeof(GPUCullDrawCmd),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    gc->draw_cmds_ssbo = rhi_buffer_create(dev, &draw_desc);
    
    /* Create visible draws SSBO (output, also used for indirect draw) */
    RHIBufferDesc vis_draws_desc = {
        .size = GPUCULL_MAX_DRAWS * sizeof(GPUCullDrawCmd),
        .usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT,
    };
    gc->visible_draws_ssbo = rhi_buffer_create(dev, &vis_draws_desc);
    
    /* Create draw count buffer (atomic counter) */
    RHIBufferDesc draw_count_desc = {
        .size = sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT,
    };
    gc->draw_count_buf = rhi_buffer_create(dev, &draw_count_desc);

    RHIBufferDesc vis_flags_desc = {
        .size = GPUCULL_MAX_OBJECTS * sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    gc->visible_flags_ssbo = rhi_buffer_create(dev, &vis_flags_desc);
    
    if (!rhi_handle_valid(gc->draw_cmds_ssbo) ||
        !rhi_handle_valid(gc->visible_draws_ssbo) ||
        !rhi_handle_valid(gc->draw_count_buf) ||
        !rhi_handle_valid(gc->visible_flags_ssbo)) {
        LOG_WARN("UnifiedCull: buffer creation failed");
        gc->unified_ready = false;
        return true;
    }

    RHISamplerDesc hz_samp = {
        .min_filter = RHI_FILTER_NEAREST,
        .mag_filter = RHI_FILTER_NEAREST,
        .wrap_u     = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v     = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w     = RHI_WRAP_CLAMP_TO_EDGE,
    };
    gc->hi_z_sampler = rhi_sampler_create(dev, &hz_samp);

    f32 white_depth = 1.0f;
    RHITextureDesc fb_desc = {
        .width = 1, .height = 1,
        .format = RHI_FORMAT_R32_FLOAT,
        .mip_levels = 1,
        .data = &white_depth,
    };
    gc->hi_z_fallback = rhi_texture_create(dev, &fb_desc);
    
    gc->unified_ready = true;

    /* Cache uniform locations for unified pipeline */
    gc->_loc_uni_vp    = rhi_pipeline_get_uniform_location(dev, gc->unified_cull_pipe, "u_cull_vp");
    gc->_loc_uni_count = rhi_pipeline_get_uniform_location(dev, gc->unified_cull_pipe, "u_cull_count");
    gc->_loc_uni_hz_w  = rhi_pipeline_get_uniform_location(dev, gc->unified_cull_pipe, "u_cull_hi_z_width");
    gc->_loc_uni_hz_h  = rhi_pipeline_get_uniform_location(dev, gc->unified_cull_pipe, "u_cull_hi_z_height");
    gc->_loc_uni_use   = rhi_pipeline_get_uniform_location(dev, gc->unified_cull_pipe, "u_cull_use_hi_z");

    /* Zero the pre-allocated zero buffer (part of _pack_buf block) */
    memset(gc->_zero_buf, 0, gc->_zero_buf_cap * sizeof(u32));

    LOG_INFO("UnifiedCull: initialized (max %u objects, %u draws)", 
             GPUCULL_MAX_OBJECTS, GPUCULL_MAX_DRAWS);
    return true;
}

void gpucull_upload_draw_cmds(GPUCullSystem *gc, const GPUCullDrawCmd *cmds, u32 count) {
    if (!gc || !gc->unified_ready || !cmds || count == 0) return;
    if (count > GPUCULL_MAX_DRAWS) count = GPUCULL_MAX_DRAWS;
    
    rhi_buffer_update_region(gc->device, gc->draw_cmds_ssbo, 0, 
                             cmds, count * sizeof(GPUCullDrawCmd));
    gc->draw_count = count;
}

void gpucull_upload_objects_unified(GPUCullSystem *gc, const GPUCullObject *objects, u32 count) {
    if (!gc || !gc->unified_ready || !objects || count == 0) return;
    if (count > GPUCULL_MAX_OBJECTS) count = GPUCULL_MAX_OBJECTS;

    /* Use persistent pack buffer (cap = GPUCULL_MAX_OBJECTS * 4, always sufficient) */
    f32 *packed = gc->_pack_buf;
    /* SSE2 SoA→AoS pack: position[4] is already (x,y,z,r), direct store */
    u32 i = 0;
    for (; i + 1 <= count; i++) {
        _mm_storeu_ps(&packed[i * 4], _mm_loadu_ps(objects[i].position));
    }
    rhi_buffer_update_region(gc->device, gc->object_ssbo, 0,
                             packed, (usize)count * 4 * sizeof(f32));
    gc->object_count = count;
}

/*
 * Single-pass GPU-driven cull + compaction (unified_cull.comp). Object i must
 * correspond to draw command i. Optional Hi-Z rejects draws occluded in the
 * previous frame's depth pyramid (1-frame latency, same as occlusion_cull).
 */
void gpucull_dispatch_unified(GPUCullSystem *gc, RHICmdBuffer *cmd,
                              const f32 *vp, const f32 *camera_pos,
                              RHITexture hi_z_texture,
                              u32 hi_z_width, u32 hi_z_height,
                              RHIBuffer vis_flags_out) {
    (void)camera_pos;
    if (!gc || !gc->unified_ready || gc->object_count == 0 || gc->draw_count == 0) return;

    u32 n = gc->draw_count < gc->object_count ? gc->draw_count : gc->object_count;

    RHIBuffer flags_buf = rhi_handle_valid(vis_flags_out) ? vis_flags_out : gc->visible_flags_ssbo;
    if (rhi_handle_valid(flags_buf)) {
        /* Use persistent zero buffer (cap = GPUCULL_MAX_OBJECTS, n never exceeds it) */
        rhi_buffer_update_region(gc->device, flags_buf, 0, gc->_zero_buf, n * sizeof(u32));
    }

    /* Reset the compacted-draw atomic counter. */
    u32 zero = 0;
    rhi_buffer_update(gc->device, gc->draw_count_buf, &zero, sizeof(u32));

    rhi_cmd_bind_pipeline(cmd, gc->unified_cull_pipe);
    rhi_cmd_bind_storage_buffer(cmd, gc->object_ssbo,        0);
    rhi_cmd_bind_storage_buffer(cmd, gc->draw_cmds_ssbo,     1);
    rhi_cmd_bind_storage_buffer(cmd, gc->visible_draws_ssbo, 2);
    rhi_cmd_bind_storage_buffer(cmd, gc->draw_count_buf,     3);
    if (rhi_handle_valid(flags_buf))
        rhi_cmd_bind_storage_buffer(cmd, flags_buf, 4);

    bool use_hi_z = rhi_handle_valid(hi_z_texture) && hi_z_width > 0u && hi_z_height > 0u
                 && rhi_handle_valid(gc->hi_z_sampler);
    RHITexture hi_z_bind = use_hi_z ? hi_z_texture : gc->hi_z_fallback;
    if (rhi_handle_valid(hi_z_bind)) {
        rhi_cmd_bind_texture_compute(cmd, hi_z_bind, gc->hi_z_sampler, 0);
    }

    i32 loc_vp = gc->_loc_uni_vp;
    if (loc_vp >= 0) rhi_cmd_set_uniform_mat4(cmd, loc_vp, vp);
    i32 loc_n = gc->_loc_uni_count;
    if (loc_n >= 0) rhi_cmd_set_uniform_i32(cmd, loc_n, (i32)n);
    i32 loc_hz_w = gc->_loc_uni_hz_w;
    if (loc_hz_w >= 0) rhi_cmd_set_uniform_f32(cmd, loc_hz_w, (f32)hi_z_width);
    i32 loc_hz_h = gc->_loc_uni_hz_h;
    if (loc_hz_h >= 0) rhi_cmd_set_uniform_f32(cmd, loc_hz_h, (f32)hi_z_height);
    i32 loc_use = gc->_loc_uni_use;
    if (loc_use >= 0) rhi_cmd_set_uniform_f32(cmd, loc_use, use_hi_z ? 1.0f : 0.0f);

    u32 groups = (n + 63) / 64;
    rhi_cmd_dispatch(cmd, groups, 1, 1);
    rhi_cmd_memory_barrier(cmd);
}

bool gpucull_read_vis_flags(GPUCullSystem *gc, u32 count, u32 *out_flags) {
    if (!gc || !gc->unified_ready || !out_flags || count == 0u) return false;
    if (!rhi_handle_valid(gc->visible_flags_ssbo)) return false;
    if (count > GPUCULL_MAX_OBJECTS) count = GPUCULL_MAX_OBJECTS;

    void *mapped = rhi_buffer_map(gc->device, gc->visible_flags_ssbo);
    if (!mapped) return false;
    memcpy(out_flags, mapped, (usize)count * sizeof(u32));
    rhi_buffer_unmap(gc->device, gc->visible_flags_ssbo);
    return true;
}

void gpucull_get_unified_results(GPUCullSystem *gc, 
                                 u32 *out_visible_objects,
                                 u32 *out_visible_draws) {
    if (!gc || !gc->unified_ready) return;

    /* Conservative upper bound; exact counts live in draw_count_buf on the GPU
     * and are consumed by the indirect-count draw without CPU readback. */
    if (out_visible_objects) *out_visible_objects = gc->object_count;
    if (out_visible_draws) *out_visible_draws = gc->draw_count;
}

void gpucull_execute_indirect_draws(GPUCullSystem *gc, RHIDevice *dev) {
    if (!gc || !gc->unified_ready || gc->draw_count == 0) return;
    
    /* Execute compacted indirect draws */
    rhi_cmd_draw_indexed_indirect_count(
        dev,
        gc->visible_draws_ssbo, 0,
        gc->draw_count_buf, 0,
        gc->draw_count,
        (u32)sizeof(GPUCullDrawCmd));
}
