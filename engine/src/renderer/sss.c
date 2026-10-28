#include "sss.h"
#include <renderer/post_targets.h>
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline sss_create_pipe(RHIDevice *dev, bool sidecar,
                                    const char *vert_path, const char *frag_path) {
    RHIShader vs, fs;
    if (sidecar) {
        /* D3D12 never compiles source in-process: the GLSL path resolves to
         * the precompiled <name>_hlsl sidecar instead. */
        vs = rhi_shader_create_path(dev, vert_path, false);
        fs = rhi_shader_create_path(dev, frag_path, true);
    } else {
        usize vs_len = 0, fs_len = 0;
        char *vs_src = shader_read_file(vert_path, &vs_len);
        char *fs_src = shader_read_file(frag_path, &fs_len);
        if (!vs_src || !fs_src) {
            LOG_WARN("SSS: shaders not found (%s)", frag_path);
            free(vs_src); free(fs_src);
            return RHI_HANDLE_NULL;
        }
        vs = rhi_shader_create(dev, vs_src, vs_len, false);
        fs = rhi_shader_create(dev, fs_src, fs_len, true);
        free(vs_src); free(fs_src);
    }

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("SSS: shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }

    RHIPipelineDesc pdesc = {
        .vert = vs, .frag = fs,
        .no_vertex_input = true,
        .uses_textures = true,
        .depth_write_disable = true,
        .disable_culling = true,
    };
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

static bool sss_targets_create(SSSSystem *s, RHIDevice *dev, u32 w, u32 h) {
    const PostTargetSpec t[2] = {
        { &s->fbo, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT },
        { &s->blur_fbo, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT },
    };
    return post_targets_replace(dev, t, 2u);
}

bool sss_init(SSSSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], h_path[96], v_path[96];
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
        !shader_variant_path("shaders/sss.frag", (RHIShaderVariant)caps.shader_variant, h_path, sizeof(h_path)) ||
        !shader_variant_path("shaders/sss_vertical.frag", (RHIShaderVariant)caps.shader_variant, v_path, sizeof(v_path))) {
        LOG_WARN("SSS: capability query or shader variant path failed");
        return false;
    }
    s->h_pipe = sss_create_pipe(dev, caps.shader_sidecar_paths, vs_path, h_path);
    s->v_pipe = sss_create_pipe(dev, caps.shader_sidecar_paths, vs_path, v_path);

    if (!rhi_handle_valid(s->h_pipe) || !rhi_handle_valid(s->v_pipe)) {
        LOG_WARN("SSS: pipeline creation failed");
        /* R355: align R354 SSAO/SSGI — free the pipe that succeeded. */
        sss_shutdown(s);
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_sss_ 与 u_sssv_
     * 前缀分别是 sss(_vk).frag / sss_vertical(_vk).frag 的真实成员名，无别名行。 */
    s->bind_h = rhi_pipeline_bindings_create(dev, s->h_pipe);
    s->bind_v = rhi_pipeline_bindings_create(dev, s->v_pipe);
    if (!s->bind_h || !s->bind_v)
        LOG_WARN("SSS: bindings create failed; uniform locations resolve -1");

    (void)sss_targets_create(s, dev, w, h);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    /* R348: align R347 — do not mark ready with empty FBO/sampler handles. */
    if (!rhi_handle_valid(s->fbo.fb) || !rhi_handle_valid(s->blur_fbo.fb) ||
        !rhi_handle_valid(s->sampler)) {
        LOG_WARN("SSS: FBO/sampler creation failed");
        sss_shutdown(s);
        return false;
    }

    s->loc_strength  = rhi_pipeline_bindings_resolve(s->bind_h, "u_sss_strength");
    s->loc_sw        = rhi_pipeline_bindings_resolve(s->bind_h, "u_sss_sw");
    s->loc_sh        = rhi_pipeline_bindings_resolve(s->bind_h, "u_sss_sh");
    s->loc_max_dist  = rhi_pipeline_bindings_resolve(s->bind_h, "u_sss_max_dist");

    s->v_loc_strength = rhi_pipeline_bindings_resolve(s->bind_v, "u_sssv_strength");
    s->v_loc_sw       = rhi_pipeline_bindings_resolve(s->bind_v, "u_sssv_sw");
    s->v_loc_sh       = rhi_pipeline_bindings_resolve(s->bind_v, "u_sssv_sh");
    s->v_loc_max_dist = rhi_pipeline_bindings_resolve(s->bind_v, "u_sssv_max_dist");

    s->ready = true;
    LOG_INFO("SSS: initialized (%ux%u)", w, h);
    return true;
}

bool sss_resize(SSSSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev || !s->ready || s->dev != dev) return false;
    if (!sss_targets_create(s, dev, w, h)) {
        LOG_WARN("SSS: resize to %ux%u failed; keeping previous targets", w, h);
        return false;
    }
    return true;
}

void sss_shutdown(SSSSystem *s) {
    if (!s->dev) return;
    if (s->bind_h) { rhi_pipeline_bindings_destroy(s->dev, s->bind_h); s->bind_h = NULL; }
    if (s->bind_v) { rhi_pipeline_bindings_destroy(s->dev, s->bind_v); s->bind_v = NULL; }
    if (rhi_handle_valid(s->fbo.fb))      rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->blur_fbo.fb)) rhi_offscreen_fbo_destroy(s->dev, &s->blur_fbo);
    if (rhi_handle_valid(s->sampler))     rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->h_pipe))      rhi_pipeline_destroy(s->dev, s->h_pipe);
    if (rhi_handle_valid(s->v_pipe))      rhi_pipeline_destroy(s->dev, s->v_pipe);
    s->ready = false;
}

void sss_apply(SSSSystem *s, RHICmdBuffer *cmd,
               RHITexture color_tex, RHITexture depth_tex,
               f32 strength, f32 max_dist, u32 w, u32 h) {
    if (!s->ready) return;

    /* Pass 1: Horizontal blur → blur_fbo */
    rhi_offscreen_fbo_bind(cmd, &s->blur_fbo);
    rhi_cmd_bind_pipeline(cmd, s->h_pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures — rhi_cmd_bind_texture ignores
     * the unit parameter in VK and binds all 9 slots to one texture. */
    rhi_cmd_bind_material_textures(cmd, color_tex, color_tex, color_tex,
                                   color_tex, depth_tex, color_tex, s->sampler);

    if (s->loc_strength >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_strength, strength);
    if (s->loc_sw >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sw, (f32)w);
    if (s->loc_sh >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sh, (f32)h);
    if (s->loc_max_dist >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_max_dist, max_dist);

    rhi_cmd_draw(cmd, 3, 1);

    /* Pass 2: Vertical blur → fbo (reads blur_fbo + depth + original) */
    rhi_offscreen_fbo_bind(cmd, &s->fbo);
    rhi_cmd_bind_pipeline(cmd, s->v_pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures for multi-texture binding. */
    rhi_cmd_bind_material_textures(cmd, s->blur_fbo.color_tex, color_tex,
                                   s->blur_fbo.color_tex, s->blur_fbo.color_tex,
                                   depth_tex, s->blur_fbo.color_tex, s->sampler);

    if (s->v_loc_strength >= 0) rhi_cmd_set_uniform_f32(cmd, s->v_loc_strength, strength);
    if (s->v_loc_sw >= 0)       rhi_cmd_set_uniform_f32(cmd, s->v_loc_sw, (f32)w);
    if (s->v_loc_sh >= 0)       rhi_cmd_set_uniform_f32(cmd, s->v_loc_sh, (f32)h);
    if (s->v_loc_max_dist >= 0) rhi_cmd_set_uniform_f32(cmd, s->v_loc_max_dist, max_dist);

    rhi_cmd_draw(cmd, 3, 1);
}
