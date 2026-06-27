#include <renderer/occlusion_cull.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emmintrin.h>  /* SSE2 for visibility count */

/* ---- Helper: file read ---- */
static char *oc_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

/* ---- Helper: calculate mip levels for given resolution ---- */
static u32 oc_calc_mip_levels(u32 width, u32 height) {
    u32 max_dim = width > height ? width : height;
    u32 levels = 1;
    while (max_dim > 1) {
        max_dim >>= 1;
        levels++;
    }
    return levels;
}

/* ---- Helper: load compute pipeline from shader file ---- */
static RHIPipeline oc_load_compute_pipeline(RHIDevice *dev, const char *shader_path) {
    usize src_len = 0;
    char *src = oc_read_file(shader_path, &src_len);
    if (!src) {
        LOG_WARN("OcclusionCull: shader not found: %s", shader_path);
        return RHI_HANDLE_NULL;
    }

    RHIShader cs = rhi_shader_create_compute(dev, src, src_len);
    free(src);
    if (!rhi_handle_valid(cs)) {
        LOG_WARN("OcclusionCull: shader compile failed: %s", shader_path);
        return RHI_HANDLE_NULL;
    }

    RHIPipelineDesc pdesc = {0};
    pdesc.frag = cs;
    pdesc.is_compute = true;
    pdesc.uses_storage = true;
    pdesc.uses_textures = true;
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, cs);

    if (!rhi_handle_valid(pipe)) {
        LOG_WARN("OcclusionCull: pipeline creation failed: %s", shader_path);
    }
    return pipe;
}

/* ---- Create Hi-Z texture with full mip chain ---- */
static RHITexture oc_create_hi_z_texture(RHIDevice *dev, u32 width, u32 height, u32 mip_levels) {
    RHITextureDesc desc = {0};
    desc.width = width;
    desc.height = height;
    desc.format = RHI_FORMAT_R32_FLOAT;
    desc.mip_levels = mip_levels;
    desc.data = NULL;
    return rhi_texture_create(dev, &desc);
}

/* ========================================================================
 * occlusion_cull_init
 * ======================================================================== */
bool occlusion_cull_init(OcclusionCullSystem *sys, RHIDevice *dev, u32 width, u32 height) {
    memset(sys, 0, sizeof(*sys));
    sys->device = dev;

    /* Calculate Hi-Z dimensions (half resolution is typical) */
    sys->hi_z_width  = width / 2;
    sys->hi_z_height = height / 2;
    if (sys->hi_z_width  < 1) sys->hi_z_width  = 1;
    if (sys->hi_z_height < 1) sys->hi_z_height = 1;
    sys->hi_z_levels = oc_calc_mip_levels(sys->hi_z_width, sys->hi_z_height);

    /* Create Hi-Z pyramid texture */
    sys->hi_z_texture = oc_create_hi_z_texture(dev, sys->hi_z_width, sys->hi_z_height, sys->hi_z_levels);
    if (!rhi_handle_valid(sys->hi_z_texture)) {
        LOG_WARN("OcclusionCull: failed to create Hi-Z texture");
        return false;
    }

    /* Create AABB SSBO */
    RHIBufferDesc aabb_desc = {
        .size  = OCCLUSION_MAX_OBJECTS * sizeof(ObjectAABB),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    sys->aabb_buffer = rhi_buffer_create(dev, &aabb_desc);
    if (!rhi_handle_valid(sys->aabb_buffer)) {
        LOG_WARN("OcclusionCull: failed to create AABB buffer");
        occlusion_cull_shutdown(sys);
        return false;
    }

    /* Create visibility SSBO */
    RHIBufferDesc vis_desc = {
        .size  = OCCLUSION_MAX_OBJECTS * sizeof(u32),
        .usage = RHI_BUFFER_USAGE_STORAGE,
    };
    sys->visibility_buffer = rhi_buffer_create(dev, &vis_desc);
    if (!rhi_handle_valid(sys->visibility_buffer)) {
        LOG_WARN("OcclusionCull: failed to create visibility buffer");
        occlusion_cull_shutdown(sys);
        return false;
    }

    /* R87-1: Create staging buffer for non-blocking GPU-side copy readback. */
    sys->readback_staging = rhi_buffer_create(dev, &vis_desc);
    if (!rhi_handle_valid(sys->readback_staging)) {
        LOG_WARN("OcclusionCull: failed to create readback staging buffer");
        occlusion_cull_shutdown(sys);
        return false;
    }

    /* Create nearest sampler for Hi-Z */
    RHISamplerDesc samp_desc = {
        .min_filter = RHI_FILTER_NEAREST,
        .mag_filter = RHI_FILTER_NEAREST,
        .wrap_u     = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v     = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w     = RHI_WRAP_CLAMP_TO_EDGE,
    };
    sys->hi_z_sampler = rhi_sampler_create(dev, &samp_desc);

    /* Load compute pipelines */
    sys->hi_z_pipeline = oc_load_compute_pipeline(dev, "shaders/hi_z_generate.comp");
    sys->cull_pipeline = oc_load_compute_pipeline(dev, "shaders/occlusion_cull.comp");

    if (!rhi_handle_valid(sys->hi_z_sampler) ||
        !rhi_handle_valid(sys->hi_z_pipeline) || !rhi_handle_valid(sys->cull_pipeline)) {
        LOG_WARN("OcclusionCull: sampler or compute pipeline creation failed");
        occlusion_cull_shutdown(sys);
        return false;
    }

    /* Cache uniform locations once at init (avoids per-frame glGetUniformLocation). */
    sys->_loc_hi_z_output_size  = rhi_pipeline_get_uniform_location(dev, sys->hi_z_pipeline, "pc_output_size");
    sys->_loc_cull_view_proj    = rhi_pipeline_get_uniform_location(dev, sys->cull_pipeline, "pc_view_proj");
    sys->_loc_cull_object_count = rhi_pipeline_get_uniform_location(dev, sys->cull_pipeline, "pc_object_count");
    sys->_loc_cull_hi_z_width   = rhi_pipeline_get_uniform_location(dev, sys->cull_pipeline, "pc_hi_z_width");
    sys->_loc_cull_hi_z_height  = rhi_pipeline_get_uniform_location(dev, sys->cull_pipeline, "pc_hi_z_height");

    /* Allocate CPU readback buffer */
    sys->visibility_readback = calloc(OCCLUSION_MAX_OBJECTS, sizeof(u32));
    if (!sys->visibility_readback) {
        LOG_WARN("OcclusionCull: failed to allocate readback buffer");
        occlusion_cull_shutdown(sys);
        return false;
    }

    /* Mark all as visible initially */
    for (u32 i = 0; i < OCCLUSION_MAX_OBJECTS; i++) {
        sys->visibility_readback[i] = 1;
    }

    sys->object_count = 0;
    sys->enabled = true;

    LOG_INFO("OcclusionCull: initialized (%ux%u, %u mip levels, max %u objects)",
             sys->hi_z_width, sys->hi_z_height, sys->hi_z_levels, OCCLUSION_MAX_OBJECTS);
    return true;
}

/* ========================================================================
 * occlusion_cull_shutdown
 * ======================================================================== */
void occlusion_cull_shutdown(OcclusionCullSystem *sys) {
    if (!sys->device) return;

    if (rhi_handle_valid(sys->hi_z_texture))
        rhi_texture_destroy(sys->device, sys->hi_z_texture);
    if (rhi_handle_valid(sys->aabb_buffer))
        rhi_buffer_destroy(sys->device, sys->aabb_buffer);
    if (rhi_handle_valid(sys->visibility_buffer))
        rhi_buffer_destroy(sys->device, sys->visibility_buffer);
    if (rhi_handle_valid(sys->readback_staging))
        rhi_buffer_destroy(sys->device, sys->readback_staging);
    if (rhi_handle_valid(sys->hi_z_pipeline))
        rhi_pipeline_destroy(sys->device, sys->hi_z_pipeline);
    if (rhi_handle_valid(sys->cull_pipeline))
        rhi_pipeline_destroy(sys->device, sys->cull_pipeline);
    if (rhi_handle_valid(sys->hi_z_sampler))
        rhi_sampler_destroy(sys->device, sys->hi_z_sampler);

    free(sys->visibility_readback);
    memset(sys, 0, sizeof(*sys));
}

/* ========================================================================
 * occlusion_cull_resize
 * ======================================================================== */
void occlusion_cull_resize(OcclusionCullSystem *sys, u32 width, u32 height) {
    if (!sys->device || !sys->enabled) return;

    u32 new_w = width / 2;
    u32 new_h = height / 2;
    if (new_w < 1) new_w = 1;
    if (new_h < 1) new_h = 1;

    /* Skip if size unchanged */
    if (new_w == sys->hi_z_width && new_h == sys->hi_z_height) return;

    /* Destroy old Hi-Z texture */
    if (rhi_handle_valid(sys->hi_z_texture)) {
        rhi_texture_destroy(sys->device, sys->hi_z_texture);
    }

    /* Recreate */
    sys->hi_z_width  = new_w;
    sys->hi_z_height = new_h;
    sys->hi_z_levels = oc_calc_mip_levels(new_w, new_h);
    sys->hi_z_texture = oc_create_hi_z_texture(sys->device, new_w, new_h, sys->hi_z_levels);

    if (!rhi_handle_valid(sys->hi_z_texture)) {
        LOG_WARN("OcclusionCull: resize failed, disabling");
        sys->enabled = false;
    } else {
        LOG_INFO("OcclusionCull: resized Hi-Z to %ux%u (%u levels)", new_w, new_h, sys->hi_z_levels);
    }
}

/* ========================================================================
 * occlusion_cull_upload_aabbs
 * ======================================================================== */
void occlusion_cull_upload_aabbs(OcclusionCullSystem *sys, const ObjectAABB *aabbs, u32 count) {
    if (!sys->device || !sys->enabled || count == 0) return;

    sys->object_count = count > OCCLUSION_MAX_OBJECTS ? OCCLUSION_MAX_OBJECTS : count;
    rhi_buffer_update(sys->device, sys->aabb_buffer, aabbs,
                      sys->object_count * sizeof(ObjectAABB));
}

/* ========================================================================
 * occlusion_cull_generate_hi_z
 *
 * Generates the Hi-Z mipmap pyramid from the current depth buffer.
 * Each mip level is generated by dispatching a compute shader that reads
 * the previous level and writes the max depth into the next (smaller) level.
 * ======================================================================== */
void occlusion_cull_generate_hi_z(OcclusionCullSystem *sys, RHICmdBuffer *cmd, RHITexture depth_buffer) {
    if (!sys->device || !sys->enabled) return;
    if (!rhi_handle_valid(sys->hi_z_pipeline)) return;

    /* Transition depth buffer for shader read */
    rhi_cmd_transition_depth_to_read(cmd, depth_buffer);

    /* Bind the Hi-Z generation pipeline */
    rhi_cmd_bind_pipeline(cmd, sys->hi_z_pipeline);

    /* Generate each mip level */
    for (u32 mip = 0; mip < sys->hi_z_levels; mip++) {
        u32 out_w = sys->hi_z_width  >> mip;
        u32 out_h = sys->hi_z_height >> mip;
        if (out_w < 1) out_w = 1;
        if (out_h < 1) out_h = 1;

        /* Bind input: mip 0 reads from depth_buffer, subsequent mips read from previous level.
         * Both must target the compute sampler set (set 2). rhi_cmd_bind_texture would
         * wrongly target the graphics material set, leaving set 2 unbound -> GPU crash. */
        if (mip == 0) {
            rhi_cmd_bind_texture_compute(cmd, depth_buffer, sys->hi_z_sampler, 0);
        } else {
            rhi_cmd_bind_texture_mip(cmd, sys->hi_z_texture, sys->hi_z_sampler, 0, mip - 1);
        }

        /* Bind output: current mip level as image for writing */
        rhi_cmd_bind_image_texture(cmd, sys->hi_z_texture, 1, mip, true);

        /* Set push constants: output size (using cached location) */
        if (sys->_loc_hi_z_output_size >= 0) {
            rhi_cmd_set_uniform_vec2(cmd, sys->_loc_hi_z_output_size, (f32)out_w, (f32)out_h);
        }

        /* Dispatch: 8x8 workgroups */
        u32 groups_x = (out_w + 7) / 8;
        u32 groups_y = (out_h + 7) / 8;
        rhi_cmd_dispatch(cmd, groups_x, groups_y, 1);

        /* Memory barrier between mip levels */
        rhi_cmd_memory_barrier(cmd);
    }
}

/* ========================================================================
 * occlusion_cull_dispatch
 *
 * Dispatches the occlusion culling compute shader.
 * For each object, the shader projects its AABB to screen space and tests
 * against the Hi-Z pyramid to determine visibility.
 *
 * Uses 1-frame latency: reads back results from the previous frame's
 * visibility buffer before dispatching the new cull pass.
 * ======================================================================== */
void occlusion_cull_dispatch(OcclusionCullSystem *sys, RHICmdBuffer *cmd, const Mat4 *view_proj, u32 object_count) {
    if (!sys->device || !sys->enabled) return;
    if (!rhi_handle_valid(sys->cull_pipeline)) return;
    if (object_count == 0) return;

    u32 count = object_count > OCCLUSION_MAX_OBJECTS ? OCCLUSION_MAX_OBJECTS : object_count;

    /* ---- Readback from staging buffer (1-frame latency, non-blocking) — R87-1 ---- */
    void *mapped = rhi_buffer_map(sys->device, sys->readback_staging);
    if (mapped) {
        memcpy(sys->visibility_readback, mapped, count * sizeof(u32));
        rhi_buffer_unmap(sys->device, sys->readback_staging);
    }

    /* ---- Dispatch new cull pass ---- */
    rhi_cmd_bind_pipeline(cmd, sys->cull_pipeline);

    /* Bind AABB buffer (binding 0) */
    rhi_cmd_bind_storage_buffer(cmd, sys->aabb_buffer, 0);

    /* Bind visibility buffer (binding 1) */
    rhi_cmd_bind_storage_buffer(cmd, sys->visibility_buffer, 1);

    /* Bind Hi-Z texture (compute sampler set 2, binding 2). */
    rhi_cmd_bind_texture_compute(cmd, sys->hi_z_texture, sys->hi_z_sampler, 2);

    /* Set push constants using cached uniform locations. */
    if (sys->_loc_cull_view_proj >= 0) {
        rhi_cmd_set_uniform_mat4(cmd, sys->_loc_cull_view_proj, &view_proj->e[0][0]);
    }

    if (sys->_loc_cull_object_count >= 0) {
        rhi_cmd_set_uniform_i32(cmd, sys->_loc_cull_object_count, (i32)count);
    }

    if (sys->_loc_cull_hi_z_width >= 0) {
        rhi_cmd_set_uniform_f32(cmd, sys->_loc_cull_hi_z_width, (f32)sys->hi_z_width);
    }

    if (sys->_loc_cull_hi_z_height >= 0) {
        rhi_cmd_set_uniform_f32(cmd, sys->_loc_cull_hi_z_height, (f32)sys->hi_z_height);
    }

    /* Dispatch: 64 threads per workgroup */
    u32 groups = (count + 63) / 64;
    rhi_cmd_dispatch(cmd, groups, 1, 1);

    /* Memory barrier: ensure compute writes complete before GPU-side copy */
    rhi_cmd_memory_barrier(cmd);

    /* R87-1: GPU-side copy to staging buffer (avoids glMapBufferRange stall next frame). */
    rhi_cmd_copy_buffer(cmd, sys->visibility_buffer, sys->readback_staging, count * sizeof(u32));

    sys->object_count = count;
}

/* ========================================================================
 * occlusion_cull_is_visible
 *
 * Queries the CPU-side readback buffer (previous frame's results).
 * ======================================================================== */
bool occlusion_cull_is_visible(const OcclusionCullSystem *sys, u32 object_index) {
    if (!sys->enabled || !sys->visibility_readback) return true;
    if (object_index >= sys->object_count) return true;
    return sys->visibility_readback[object_index] != 0;
}

/* ========================================================================
 * occlusion_cull_visible_count
 * ======================================================================== */
u32 occlusion_cull_visible_count(const OcclusionCullSystem *sys) {
    if (!sys->enabled || !sys->visibility_readback || sys->object_count == 0) {
        return sys->object_count;
    }

    /* SSE2 branchless counting: process 4 u32 per iteration.
     * Each visibility_readback[i] is 0 (hidden) or nonzero (visible).
     * Compare against zero → mask all-ones or all-zeros → popcount bytes. */
    const u32 *rb = sys->visibility_readback;
    u32 n = sys->object_count;
    u32 count = 0;
    u32 i = 0;

    /* SIMD path: 4 elements per iteration */
    for (; i + 4 <= n; i += 4) {
        __m128i v = _mm_loadu_si128((const __m128i *)(rb + i));
        __m128i zero = _mm_setzero_si128();
        __m128i eq = _mm_cmpeq_epi32(v, zero);      /* 0xFF per byte if visible==0 */
        __m128i nz = _mm_cmpeq_epi32(zero, zero);   /* all 1s */
        __m128i vis = _mm_andnot_si128(eq, nz);      /* all 1s if visible!=0 */
        /* Count visible elements: each contributes 4 bytes of 0xFF */
        int mask = _mm_movemask_epi8(vis);
        count += (u32)__builtin_popcount(mask) / 4;
    }

    /* Scalar tail */
    for (; i < n; i++) {
        if (rb[i] != 0) count++;
    }

    return count;
}
