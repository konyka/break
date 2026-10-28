#include "debug_viz.h"
#include <renderer/post_targets.h>
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline dv_create_pipe(RHIDevice *dev, bool sidecar,
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
            LOG_WARN("DebugViz: shaders not found (%s)", frag_path);
            free(vs_src); free(fs_src);
            return RHI_HANDLE_NULL;
        }
        vs = rhi_shader_create(dev, vs_src, vs_len, false);
        fs = rhi_shader_create(dev, fs_src, fs_len, true);
        free(vs_src); free(fs_src);
    }

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("DebugViz: shader compile failed");
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

static bool debug_viz_targets_create(DebugVizSystem *s, RHIDevice *dev, u32 w, u32 h) {
    const PostTargetSpec t[1] = {
        { &s->fbo, w, h, RHI_FORMAT_UNDEFINED },
    };
    return post_targets_replace(dev, t, 1u);
}

bool debug_viz_init(DebugVizSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
        !shader_variant_path("shaders/debug_viz.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
        LOG_WARN("DebugViz: capability query or shader variant path failed");
        return false;
    }
    s->pipe = dv_create_pipe(dev, caps.shader_sidecar_paths, vs_path, fs_path);

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("DebugViz: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_dv_* 是
     * debug_viz(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    s->bind_pipe = rhi_pipeline_bindings_create(dev, s->pipe);
    if (!s->bind_pipe)
        LOG_WARN("DebugViz: bindings create failed; uniform locations resolve -1");

    (void)debug_viz_targets_create(s, dev, w, h);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    /* R350: align R348 — do not mark ready with empty FBO/sampler. */
    if (!rhi_handle_valid(s->fbo.fb) || !rhi_handle_valid(s->sampler)) {
        LOG_WARN("DebugViz: FBO/sampler creation failed");
        debug_viz_shutdown(s);
        return false;
    }

    s->loc_mode = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_dv_mode");
    s->loc_near = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_dv_near");
    s->loc_far  = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_dv_far");
    s->loc_split0 = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_dv_split0");
    s->loc_split1 = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_dv_split1");
    s->loc_split2 = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_dv_split2");
    s->loc_split3 = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_dv_split3");

    s->ready = true;
    return true;
}

bool debug_viz_resize(DebugVizSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev || !s->ready || s->dev != dev) return false;
    if (!debug_viz_targets_create(s, dev, w, h)) {
        LOG_WARN("DebugViz: resize to %ux%u failed; keeping previous targets", w, h);
        return false;
    }
    return true;
}

void debug_viz_shutdown(DebugVizSystem *s) {
    if (!s || !s->dev) return;
    if (s->bind_pipe) { rhi_pipeline_bindings_destroy(s->dev, s->bind_pipe); s->bind_pipe = NULL; }
    if (rhi_handle_valid(s->pipe)) rhi_pipeline_destroy(s->dev, s->pipe);
    if (rhi_handle_valid(s->fbo.fb)) rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->sampler)) rhi_sampler_destroy(s->dev, s->sampler);
    memset(s, 0, sizeof(*s));
}

void debug_viz_apply(DebugVizSystem *s, RHICmdBuffer *cmd,
                     RHITexture input_tex, RHITexture depth_tex,
                     i32 mode, f32 near_plane, f32 far_plane,
                     const f32 *cascade_splits, u32 w, u32 h) {
    if (!s || !s->ready) return;
    (void)w; (void)h;

    rhi_offscreen_fbo_bind(cmd, &s->fbo);

    rhi_cmd_bind_pipeline(cmd, s->pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures — rhi_cmd_bind_texture ignores
     * the unit parameter in VK and binds all 9 slots to one texture. */
    rhi_cmd_bind_material_textures(cmd, input_tex, input_tex, input_tex,
                                   input_tex, depth_tex, input_tex, s->sampler);

    if (s->loc_mode >= 0) rhi_cmd_set_uniform_i32(cmd, s->loc_mode, mode);
    if (s->loc_near >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_near, near_plane);
    if (s->loc_far  >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_far, far_plane);
    if (cascade_splits) {
        if (s->loc_split0 >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_split0, cascade_splits[1]);
        if (s->loc_split1 >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_split1, cascade_splits[2]);
        if (s->loc_split2 >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_split2, cascade_splits[3]);
        if (s->loc_split3 >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_split3, cascade_splits[4]);
    }

    rhi_cmd_draw(cmd, 3, 1);
    /* R197-B: skip intermediate swapchain CLEAR unbind (main does final unbind). */
}
