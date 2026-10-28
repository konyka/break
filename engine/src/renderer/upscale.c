#include "upscale.h"
#include <renderer/post_targets.h>
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline ups_create_pipe(RHIDevice *dev, bool sidecar,
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
            LOG_WARN("Upscale: shaders not found (%s)", frag_path);
            free(vs_src); free(fs_src);
            return RHI_HANDLE_NULL;
        }
        vs = rhi_shader_create(dev, vs_src, vs_len, false);
        fs = rhi_shader_create(dev, fs_src, fs_len, true);
        free(vs_src); free(fs_src);
    }

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Upscale: shader compile failed");
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

static bool upscale_targets_create(UpscaleSystem *s, RHIDevice *dev,
                                   u32 display_w, u32 display_h) {
    const PostTargetSpec t[2] = {
        { &s->history[0], display_w, display_h, RHI_FORMAT_R8G8B8A8_UNORM },
        { &s->history[1], display_w, display_h, RHI_FORMAT_R8G8B8A8_UNORM },
    };
    return post_targets_replace(dev, t, 2u);
}

bool upscale_init(UpscaleSystem *s, RHIDevice *dev,
                  u32 render_w, u32 render_h,
                  u32 display_w, u32 display_h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
        !shader_variant_path("shaders/upscale.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
        LOG_WARN("Upscale: capability query or shader variant path failed");
        return false;
    }
    s->pipe = ups_create_pipe(dev, caps.shader_sidecar_paths, vs_path, fs_path);

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("Upscale: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_ups_* 是
     * upscale(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    s->bind_pipe = rhi_pipeline_bindings_create(dev, s->pipe);
    if (!s->bind_pipe)
        LOG_WARN("Upscale: bindings create failed; uniform locations resolve -1");

    (void)upscale_targets_create(s, dev, display_w, display_h);
    s->history_idx = 0;
    s->first_frame = true; /* R446: invalidate stale/uninitialized history */

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    /* R348: align R347 — present path uses upscale when ready; reject empty FBOs. */
    if (!rhi_handle_valid(s->history[0].fb) ||
        !rhi_handle_valid(s->history[1].fb) || !rhi_handle_valid(s->sampler)) {
        LOG_WARN("Upscale: FBO/sampler creation failed");
        upscale_shutdown(s);
        return false;
    }

    s->loc_rw       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_rw");
    s->loc_rh       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_rh");
    s->loc_dw       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_dw");
    s->loc_dh       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_dh");
    s->loc_sharp     = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_sharp");
    s->loc_copy_only = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_copy_only");
    s->loc_first_frame = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_first_frame");
    s->loc_inv_proj  = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_inv_proj");
    s->loc_prev_vp   = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ups_prev_vp");

    s->ready = true;
    LOG_INFO("Upscale: TSR initialized (%ux%u → %ux%u)", render_w, render_h, display_w, display_h);
    return true;
}

bool upscale_resize(UpscaleSystem *s, RHIDevice *dev,
                    u32 render_w, u32 render_h,
                    u32 display_w, u32 display_h) {
    if (!s || !dev || !s->ready || s->dev != dev) return false;
    if (!upscale_targets_create(s, dev, display_w, display_h)) {
        LOG_WARN("Upscale: resize to %ux%u failed; keeping previous targets",
                 display_w, display_h);
        return false;
    }
    s->history_idx = 0;
    s->first_frame = true;
    LOG_INFO("Upscale: resized (%ux%u -> %ux%u)", render_w, render_h, display_w, display_h);
    return true;
}

void upscale_shutdown(UpscaleSystem *s) {
    if (!s->dev) return;
    if (s->bind_pipe) { rhi_pipeline_bindings_destroy(s->dev, s->bind_pipe); s->bind_pipe = NULL; }
    if (rhi_handle_valid(s->history[0].fb))   rhi_offscreen_fbo_destroy(s->dev, &s->history[0]);
    if (rhi_handle_valid(s->history[1].fb))   rhi_offscreen_fbo_destroy(s->dev, &s->history[1]);
    if (rhi_handle_valid(s->sampler))         rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->pipe))            rhi_pipeline_destroy(s->dev, s->pipe);
    s->ready = false;
}

void upscale_apply(UpscaleSystem *s, RHICmdBuffer *cmd,
                   RHITexture input_tex, RHITexture depth_tex,
                   const f32 *inv_proj, const f32 *prev_vp,
                   f32 sharpness,
                   u32 render_w, u32 render_h,
                   u32 display_w, u32 display_h) {
    if (!s->ready) return;

    i32 read_idx  = s->history_idx;
    i32 write_idx = 1 - s->history_idx;

    /* Temporal upscale straight into the next history target, which is also
     * this frame's output (R686: the R197-A copy-only pass 2 that blitted a
     * separate output FBO into history cost a full display-res pass). */
    rhi_offscreen_fbo_bind(cmd, &s->history[write_idx]);
    rhi_cmd_bind_pipeline(cmd, s->pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures instead of three rhi_cmd_bind_texture
     * calls. In the VK path, rhi_cmd_bind_texture ignores the unit parameter and
     * binds all 9 descriptor slots to the same texture — each subsequent call
     * overwrites the previous, so only the last texture (history) would be visible.
     * rhi_cmd_bind_material_textures correctly assigns albedo->binding 0 (u_ups_src),
     * shadow->binding 1 (u_ups_depth), mr->binding 2 (u_ups_history) in one call. */
    /* The shader also skips reprojection on this frame. Binding current input
     * keeps every declared descriptor valid on both backends. */
    RHITexture hist_tex = s->first_frame ? input_tex : s->history[read_idx].color_tex;
    rhi_cmd_bind_material_textures(cmd, input_tex, hist_tex,
                                   input_tex, input_tex, depth_tex, input_tex, s->sampler);

    if (s->loc_rw >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_rw, (f32)render_w);
    if (s->loc_rh >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_rh, (f32)render_h);
    if (s->loc_dw >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_dw, (f32)display_w);
    if (s->loc_dh >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_dh, (f32)display_h);
    if (s->loc_sharp >= 0)     rhi_cmd_set_uniform_f32(cmd, s->loc_sharp, sharpness);
    if (s->loc_copy_only >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_copy_only, 0.0f);
    if (s->loc_first_frame >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_first_frame,
                                                          s->first_frame ? 1.0f : 0.0f);
    if (s->loc_inv_proj >= 0)  rhi_cmd_set_uniform_mat4(cmd, s->loc_inv_proj, inv_proj);
    if (s->loc_prev_vp >= 0)   rhi_cmd_set_uniform_mat4(cmd, s->loc_prev_vp, prev_vp);

    rhi_cmd_draw(cmd, 3, 1);

    s->history_idx = write_idx;
    s->first_frame = false; /* R446 */
}

RHITexture upscale_output_texture(const UpscaleSystem *s) {
    return s->history[s->history_idx].color_tex;
}
