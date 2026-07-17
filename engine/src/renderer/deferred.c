/* ============================================================================
 * deferred.c -- Deferred (G-Buffer) rendering path.
 *
 * The forward path under `pbr_clustered` is the engine's default. This module
 * provides an alternative G-Buffer + screen-space lighting pipeline that
 * mirrors that BRDF, so applications can flip RenderPath at runtime without
 * touching the existing forward implementation.
 *
 * Capacity matrix (current RHI):
 *   - The RHI now exposes native MRT (Multiple Render Targets) support.
 *     The G-Buffer is backed by a single RHIMRTFBO with three color
 *     attachments plus a shared depth attachment.  Geometry is rendered
 *     once and all attachments are populated in a single pass.
 *
 * Strict warnings: this file compiles cleanly under -Wall -Wextra -Werror
 * -pedantic with both GCC and Clang.
 * ========================================================================== */

#include <renderer/deferred.h>
#include <core/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ----------------------------------------------------------------------------
 * Small helpers
 * -------------------------------------------------------------------------- */

static char *defrd_inject_define(const char *src, usize len, const char *name, usize *out_len) {
    if (!src || !name) return NULL;
    const char *nl = memchr(src, '\n', len);
    usize head = nl ? (usize)(nl - src) + 1u : len;
    int def_raw = snprintf(NULL, 0, "#define %s 1\n", name);
    if (def_raw < 0) return NULL;
    usize def_len = (usize)def_raw;
    char *out = (char *)malloc(len + def_len + 1u);
    if (!out) return NULL;
    memcpy(out, src, head);
    int n = snprintf(out + head, def_len + 1u, "#define %s 1\n", name);
    if (n < 0) { free(out); return NULL; }
    memcpy(out + head + (usize)n, src + head, len - head);
    out[head + (usize)n + (len - head)] = '\0';
    if (out_len) *out_len = head + (usize)n + (len - head);
    return out;
}

static char *defrd_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }

    char *buf = (char *)malloc((usize)sz + 1u);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

static RHIPipeline defrd_compile_pipeline(RHIDevice *dev,
                                          const char *vert_path,
                                          const char *frag_path,
                                          const RHIPipelineDesc *base_desc) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = defrd_read_file(vert_path, &vs_len);
    char *fs_src = defrd_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("deferred: shader source missing (%s | %s)",
                 vert_path ? vert_path : "(null)",
                 frag_path ? frag_path : "(null)");
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    free(vs_src);

    usize fs_use_len = fs_len;
    char *fs_use = defrd_inject_define(fs_src, fs_len, "HAS_IBL", &fs_use_len);
    if (!fs_use) fs_use = fs_src;
    RHIShader fs = rhi_shader_create(dev, fs_use, fs_use_len, true);
    if (fs_use != fs_src) free(fs_use);
    free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("deferred: shader compile failed (%s)", frag_path);
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }

    RHIPipelineDesc desc = *base_desc;
    desc.vert = vs;
    desc.frag = fs;

    RHIPipeline pipe = rhi_pipeline_create(dev, &desc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

static void defrd_alloc_targets(DeferredSystem *sys, RHIDevice *dev,
                                u32 width, u32 height) {
    /* Build a single MRT with four color attachments:
     *   RT0 = R8G8B8A8_UNORM  (albedo + metallic)
     *   RT1 = R16G16B16A16_SFLOAT (oct-encoded normal)
     *   RT2 = R8G8B8A8_UNORM  (roughness + ao + emissive)
     *   RT3 = R16G16B16A16_SFLOAT (velocity NDC delta)
     * Plus a shared D32F depth attachment. */
    RHIFormat fmts[4] = {
        RHI_FORMAT_R8G8B8A8_UNORM,
        RHI_FORMAT_R16G16B16A16_SFLOAT,
        RHI_FORMAT_R8G8B8A8_UNORM,
        RHI_FORMAT_R16G16B16A16_SFLOAT,
    };
    sys->_mrt_fbo = rhi_mrt_fbo_create(dev, width, height, fmts, 4);

    sys->gbuf_albedo_metallic = sys->_mrt_fbo.color_tex[0];
    sys->gbuf_normal          = sys->_mrt_fbo.color_tex[1];
    sys->gbuf_roughness_ao    = sys->_mrt_fbo.color_tex[2];
    sys->gbuf_velocity        = sys->_mrt_fbo.color_tex[3];
    sys->gbuf_depth           = sys->_mrt_fbo.depth_tex;
    sys->gbuf_fbo             = sys->_mrt_fbo.fb;
    sys->width                = width;
    sys->height               = height;
}

static void defrd_release_targets(DeferredSystem *sys, RHIDevice *dev) {
    if (rhi_handle_valid(sys->_mrt_fbo.fb)) {
        rhi_mrt_fbo_destroy(dev, &sys->_mrt_fbo);
    }

    sys->gbuf_albedo_metallic = RHI_HANDLE_NULL;
    sys->gbuf_normal          = RHI_HANDLE_NULL;
    sys->gbuf_roughness_ao    = RHI_HANDLE_NULL;
    sys->gbuf_velocity        = RHI_HANDLE_NULL;
    sys->gbuf_depth           = RHI_HANDLE_NULL;
    sys->gbuf_fbo             = RHI_HANDLE_NULL;
}

static void defrd_cache_uniform_locations(DeferredSystem *sys, RHIDevice *dev) {
    /* G-Buffer pass pipeline uniforms. */
    RHIPipeline gp = sys->gbuffer_pipeline;
    sys->_loc_gbuf_model = rhi_pipeline_get_uniform_location(dev, gp, "u_model");
    sys->_loc_gbuf_view  = rhi_pipeline_get_uniform_location(dev, gp, "u_view");
    sys->_loc_gbuf_proj  = rhi_pipeline_get_uniform_location(dev, gp, "u_proj");
    sys->_loc_gbuf_prev_vp = rhi_pipeline_get_uniform_location(dev, gp, "u_prev_vp");

    /* Lighting pass pipeline uniforms. */
    RHIPipeline p = sys->lighting_pipeline;
    sys->_loc_inv_vp       = rhi_pipeline_get_uniform_location(dev, p, "u_inv_vp");
    sys->_loc_view         = rhi_pipeline_get_uniform_location(dev, p, "u_view");
    sys->_loc_camera_pos   = rhi_pipeline_get_uniform_location(dev, p, "u_camera_pos");
    sys->_loc_screen_w     = rhi_pipeline_get_uniform_location(dev, p, "u_screen_w");
    sys->_loc_screen_h     = rhi_pipeline_get_uniform_location(dev, p, "u_screen_h");
    sys->_loc_near         = rhi_pipeline_get_uniform_location(dev, p, "u_near");
    sys->_loc_far          = rhi_pipeline_get_uniform_location(dev, p, "u_far");
    sys->_loc_shadow_bias  = rhi_pipeline_get_uniform_location(dev, p, "u_shadow_bias");
    sys->_loc_point_count  = rhi_pipeline_get_uniform_location(dev, p, "u_point_count");
    sys->_loc_dir_count    = rhi_pipeline_get_uniform_location(dev, p, "u_dir_count");
    sys->_loc_point_shadow_far_planes = rhi_pipeline_get_uniform_location(dev, p, "u_point_shadow_far_planes");
}

/* ----------------------------------------------------------------------------
 * Public API
 * -------------------------------------------------------------------------- */

void deferred_init(DeferredSystem *sys, RHIDevice *dev, u32 width, u32 height) {
    if (!sys || !dev) return;

    memset(sys, 0, sizeof(*sys));
    sys->_loc_inv_vp          = -1;
    sys->_loc_view            = -1;
    sys->_loc_camera_pos      = -1;
    sys->_loc_screen_w        = -1;
    sys->_loc_screen_h        = -1;
    sys->_loc_near            = -1;
    sys->_loc_far             = -1;
    sys->_loc_shadow_bias     = -1;
    sys->_loc_point_count     = -1;
    sys->_loc_dir_count       = -1;
    sys->_loc_point_shadow_far_planes = -1;
    sys->_loc_gbuf_model      = -1;
    sys->_loc_gbuf_view       = -1;
    sys->_loc_gbuf_proj       = -1;
    sys->_loc_gbuf_prev_vp    = -1;

    if (width == 0u || height == 0u) {
        LOG_WARN("deferred: zero-size init (%ux%u) -- skipping", width, height);
        return;
    }

    /* Allocate G-Buffer attachments. */
    defrd_alloc_targets(sys, dev, width, height);

    /* G-Buffer write pipeline: standard vertex input, depth-tested. */
    {
        RHIPipelineDesc gbuf_desc;
        memset(&gbuf_desc, 0, sizeof(gbuf_desc));
        gbuf_desc.vertex_stride        = 8u * sizeof(f32); /* pos3 + normal3 + uv2 */
        gbuf_desc.uses_textures        = true;
        gbuf_desc.depth_compare_lequal = true;

#ifdef ENGINE_VULKAN
        sys->gbuffer_pipeline = defrd_compile_pipeline(
            dev, "shaders/gbuffer_vk.vert", "shaders/gbuffer_vk.frag", &gbuf_desc);
#else
        sys->gbuffer_pipeline = defrd_compile_pipeline(
            dev, "shaders/gbuffer.vert", "shaders/gbuffer.frag", &gbuf_desc);
#endif
    }

    /* Lighting pipeline: full-screen triangle, no vertex input, no depth. */
    {
        RHIPipelineDesc light_desc;
        memset(&light_desc, 0, sizeof(light_desc));
        light_desc.no_vertex_input     = true;
        light_desc.uses_textures       = true;
        light_desc.uses_texel_buffer   = true;
        light_desc.depth_write_disable = true;
        light_desc.disable_culling    = true;

#ifdef ENGINE_VULKAN
        sys->lighting_pipeline = defrd_compile_pipeline(
            dev, "shaders/deferred_light_vk.vert", "shaders/deferred_light_vk.frag",
            &light_desc);
#else
        sys->lighting_pipeline = defrd_compile_pipeline(
            dev, "shaders/deferred_light.vert", "shaders/deferred_light.frag",
            &light_desc);
#endif
    }

    /* Sampler used to bind G-Buffer textures during the lighting pass. */
    {
        RHISamplerDesc sd;
        memset(&sd, 0, sizeof(sd));
        sd.min_filter = RHI_FILTER_NEAREST;
        sd.mag_filter = RHI_FILTER_NEAREST;
        sd.wrap_u     = RHI_WRAP_CLAMP_TO_EDGE;
        sd.wrap_v     = RHI_WRAP_CLAMP_TO_EDGE;
        sd.wrap_w     = RHI_WRAP_CLAMP_TO_EDGE;
        sys->_gbuf_sampler = rhi_sampler_create(dev, &sd);
    }

    /* LINEAR sampler for shadow cubemap binding on GL backend. */
    {
        RHISamplerDesc lsd;
        memset(&lsd, 0, sizeof(lsd));
        lsd.min_filter = RHI_FILTER_LINEAR;
        lsd.mag_filter = RHI_FILTER_LINEAR;
        lsd.wrap_u     = RHI_WRAP_CLAMP_TO_EDGE;
        lsd.wrap_v     = RHI_WRAP_CLAMP_TO_EDGE;
        lsd.wrap_w     = RHI_WRAP_CLAMP_TO_EDGE;
        sys->_linear_sampler = rhi_sampler_create(dev, &lsd);
    }

    if (!rhi_handle_valid(sys->gbuffer_pipeline) ||
        !rhi_handle_valid(sys->lighting_pipeline)) {
        LOG_WARN("deferred: pipeline creation failed -- system disabled");
        deferred_destroy(sys, dev);
        return;
    }

    defrd_cache_uniform_locations(sys, dev);

    sys->initialized = true;
    LOG_INFO("deferred: initialized (%ux%u)", width, height);
}

void deferred_destroy(DeferredSystem *sys, RHIDevice *dev) {
    if (!sys || !dev) return;

    if (rhi_handle_valid(sys->_gbuf_sampler)) {
        rhi_sampler_destroy(dev, sys->_gbuf_sampler);
        sys->_gbuf_sampler = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->_linear_sampler)) {
        rhi_sampler_destroy(dev, sys->_linear_sampler);
        sys->_linear_sampler = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->lighting_pipeline)) {
        rhi_pipeline_destroy(dev, sys->lighting_pipeline);
        sys->lighting_pipeline = RHI_HANDLE_NULL;
    }
    if (rhi_handle_valid(sys->gbuffer_pipeline)) {
        rhi_pipeline_destroy(dev, sys->gbuffer_pipeline);
        sys->gbuffer_pipeline = RHI_HANDLE_NULL;
    }

    defrd_release_targets(sys, dev);

    sys->width       = 0u;
    sys->height      = 0u;
    sys->initialized = false;
}

void deferred_resize(DeferredSystem *sys, RHIDevice *dev, u32 width, u32 height) {
    if (!sys || !dev) return;
    if (!sys->initialized) return;
    if (width == 0u || height == 0u) return;
    if (sys->width == width && sys->height == height) return;

    defrd_release_targets(sys, dev);
    defrd_alloc_targets(sys, dev, width, height);
    LOG_INFO("deferred: resized to %ux%u", width, height);
}

/* The RHI does not expose the active command buffer outside frame_begin's
 * The deferred helpers accept the command buffer from the caller (typically
 * the value returned by `rhi_frame_begin`), ensuring consistent behaviour
 * across both OpenGL and Vulkan backends. */

void deferred_begin_gbuffer(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd) {
    if (!sys || !dev || !sys->initialized) return;

    /* Bind the MRT FBO — all three color attachments + shared depth are
     * cleared and ready in a single bind. */
    rhi_mrt_fbo_bind(cmd, &sys->_mrt_fbo);
    rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 0.0f);
    rhi_cmd_clear_depth(cmd);
    rhi_cmd_set_viewport(cmd, 0.0f, 0.0f, (f32)sys->width, (f32)sys->height, 0.0f, 1.0f);

    rhi_cmd_bind_pipeline(cmd, sys->gbuffer_pipeline);
}

void deferred_end_gbuffer(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd) {
    if (!sys || !dev || !sys->initialized) return;
    rhi_mrt_fbo_unbind(cmd, sys->width, sys->height);
}

void deferred_lighting_pass(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd,
                            RHIBuffer light_data_buf, RHIBuffer light_grid_buf,
                            u32 point_count, u32 dir_count,
                            RHITexture shadow_map,
                            RHITexture brdf_lut, RHICubemap irradiance, RHICubemap prefilter,
                            u32 psc_count, const RHITexture *psc_tex, const f32 *psc_far_planes,
                            f32 near_plane, f32 far_plane, f32 shadow_bias,
                            const f32 *view_mat, const f32 *camera_data) {
    if (!sys || !dev || !sys->initialized) return;

    rhi_cmd_bind_pipeline(cmd, sys->lighting_pipeline);

    /* Point shadow cubemap data is pre-gathered by the caller (g_psc cache). */
    u32 psc_n = psc_count;
    if (psc_n > 4u) psc_n = 4u;

#ifdef ENGINE_VULKAN
    rhi_cmd_bind_material_textures_ibl(cmd,
        sys->gbuf_albedo_metallic,
        sys->gbuf_roughness_ao,
        sys->gbuf_normal,
        sys->gbuf_depth,
        shadow_map,
        RHI_HANDLE_NULL,
        sys->_gbuf_sampler,
        brdf_lut, irradiance, prefilter,
        psc_n > 0u ? psc_tex : NULL, psc_n);
#else
    rhi_cmd_bind_texture(cmd, sys->gbuf_albedo_metallic, sys->_gbuf_sampler, 0);
    rhi_cmd_bind_texture(cmd, sys->gbuf_normal,          sys->_gbuf_sampler, 1);
    rhi_cmd_bind_texture(cmd, sys->gbuf_roughness_ao,    sys->_gbuf_sampler, 2);
    rhi_cmd_bind_texture(cmd, sys->gbuf_depth,           sys->_gbuf_sampler, 3);
    if (rhi_handle_valid(shadow_map)) {
        rhi_cmd_bind_texture(cmd, shadow_map, sys->_gbuf_sampler, 4);
    }
    for (u32 i = 0u; i < psc_n; i++) {
        if (psc_tex && rhi_handle_valid(psc_tex[i]))
            rhi_cmd_bind_texture(cmd, psc_tex[i], sys->_linear_sampler, 10u + i);
    }
    if (rhi_handle_valid(brdf_lut)) {
        rhi_cmd_bind_texture(cmd, brdf_lut, sys->_gbuf_sampler, 7);
    }
    if (rhi_handle_valid(irradiance)) {
        rhi_cmd_bind_cubemap(cmd, irradiance, sys->_gbuf_sampler, 8);
    }
    if (rhi_handle_valid(prefilter)) {
        rhi_cmd_bind_cubemap(cmd, prefilter, sys->_gbuf_sampler, 9);
    }
#endif

    if (rhi_handle_valid(light_data_buf)) {
        rhi_cmd_bind_texel_buffers(cmd, light_data_buf, light_grid_buf);
    }

    if (view_mat && sys->_loc_view >= 0) {
        rhi_cmd_set_uniform_mat4(cmd, sys->_loc_view, view_mat);
    }

    /* camera_data layout (matches main.c):
     *   [0..15]  inv_vp (mat4, column-major)
     *   [16..18] camera_pos (vec3)
     */
    if (camera_data) {
        const f32 *cd = (const f32 *)camera_data;
        if (sys->_loc_inv_vp >= 0) {
            rhi_cmd_set_uniform_mat4(cmd, sys->_loc_inv_vp, cd);
        }
        if (sys->_loc_camera_pos >= 0) {
            rhi_cmd_set_uniform_vec3(cmd, sys->_loc_camera_pos,
                                     cd[16], cd[17], cd[18]);
        }
    }

    if (sys->_loc_screen_w >= 0) {
        rhi_cmd_set_uniform_f32(cmd, sys->_loc_screen_w, (f32)sys->width);
    }
    if (sys->_loc_screen_h >= 0) {
        rhi_cmd_set_uniform_f32(cmd, sys->_loc_screen_h, (f32)sys->height);
    }
    if (sys->_loc_near >= 0) {
        rhi_cmd_set_uniform_f32(cmd, sys->_loc_near, near_plane);
    }
    if (sys->_loc_far >= 0) {
        rhi_cmd_set_uniform_f32(cmd, sys->_loc_far, far_plane);
    }
    if (sys->_loc_shadow_bias >= 0) {
        rhi_cmd_set_uniform_f32(cmd, sys->_loc_shadow_bias, shadow_bias);
    }
    if (sys->_loc_point_count >= 0) {
        rhi_cmd_set_uniform_i32(cmd, sys->_loc_point_count, (i32)point_count);
    }
    if (sys->_loc_dir_count >= 0) {
        rhi_cmd_set_uniform_i32(cmd, sys->_loc_dir_count, (i32)dir_count);
    }
    if (sys->_loc_point_shadow_far_planes >= 0) {
        f32 far_planes[4] = {25.0f, 25.0f, 25.0f, 25.0f};
        if (psc_far_planes) {
            for (u32 i = 0u; i < psc_n; i++) far_planes[i] = psc_far_planes[i];
        }
        rhi_cmd_set_uniform_vec4(cmd, sys->_loc_point_shadow_far_planes,
                                 far_planes[0], far_planes[1], far_planes[2], far_planes[3]);
    }

    rhi_cmd_draw(cmd, 3u, 1u);
}
