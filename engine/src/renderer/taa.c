#include <renderer/taa.h>
#include <renderer/post_targets.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline taa_create_pipe_path(RHIDevice *dev, const char *vert_path,
                                       const char *frag_path) {
    RHIShader vs = rhi_shader_create_path(dev, vert_path, false);
    RHIShader fs = rhi_shader_create_path(dev, frag_path, true);
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("TAA: sidecar shader unavailable (%s, %s)", vert_path, frag_path);
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs;
    pdesc.frag = fs;
    pdesc.no_vertex_input = true;
    pdesc.uses_textures = true;
    pdesc.depth_write_disable = true;
    pdesc.disable_culling = true;
    pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

static RHIPipeline taa_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("TAA: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("TAA: shader compile failed");
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

static bool taa_targets_create(TAASystem *s, RHIDevice *dev, u32 w, u32 h) {
    const PostTargetSpec t[2] = {
        { &s->history_fbo[0], w, h, RHI_FORMAT_R16G16B16A16_SFLOAT },
        { &s->history_fbo[1], w, h, RHI_FORMAT_R16G16B16A16_SFLOAT },
    };
    return post_targets_replace(dev, t, 2u);
}

bool taa_init(TAASystem *taa, RHIDevice *dev, u32 width, u32 height) {
    memset(taa, 0, sizeof(*taa));
    taa->device = dev;
    taa->history_idx = 0;
    taa->first_frame = true;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps)) {
        LOG_WARN("TAA: capability query failed");
        return false;
    }
    if (caps.shader_sidecar_paths) {
        /* R623: D3D12 never compiles HLSL in-process; the backend
         * resolves these to post_hlsl.vert / taa_hlsl.frag. */
        taa->resolve_pipe = taa_create_pipe_path(dev, "shaders/post.vert",
                                                "shaders/taa.frag");
    } else {
        if (!shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
            !shader_variant_path("shaders/taa.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
            LOG_WARN("TAA: shader variant path failed");
            return false;
        }
        taa->resolve_pipe = taa_create_pipe(dev, vs_path, fs_path);
    }

    if (!rhi_handle_valid(taa->resolve_pipe)) {
        LOG_WARN("TAA: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。 */
    taa->bind_resolve = rhi_pipeline_bindings_create(dev, taa->resolve_pipe);
    if (!taa->bind_resolve)
        LOG_WARN("TAA: bindings create failed; uniform locations resolve -1");

    (void)taa_targets_create(taa, dev, width, height);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    taa->sampler = rhi_sampler_create(dev, &sdesc);

    /* R348: align R347 — do not mark ready with empty history FBO/sampler. */
    if (!rhi_handle_valid(taa->history_fbo[0].fb) || !rhi_handle_valid(taa->history_fbo[1].fb) ||
        !rhi_handle_valid(taa->sampler)) {
        LOG_WARN("TAA: FBO/sampler creation failed");
        taa_shutdown(taa);
        return false;
    }

    taa->loc_curr_tex = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_curr_tex");
    taa->loc_hist_tex = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_hist_tex");
    taa->loc_depth_tex = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_depth");
    taa->loc_curr_vp = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_curr_vp");
    taa->loc_prev_vp = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_prev_vp");
    taa->loc_inv_proj = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_inv_proj");
    taa->loc_screen_w = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_sw");
    taa->loc_screen_h = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_sh");
    taa->loc_blend = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_blend");
    taa->loc_first_frame = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_first_frame");
    taa->loc_use_velocity = rhi_pipeline_bindings_resolve(taa->bind_resolve, "u_taa_use_velocity");

    taa->ready = true;
    LOG_INFO("TAA: initialized (%ux%u)", width, height);
    return true;
}

bool taa_resize(TAASystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev || !s->ready || s->device != dev) return false;
    if (!taa_targets_create(s, dev, w, h)) {
        LOG_WARN("TAA: resize to %ux%u failed; keeping previous targets", w, h);
        return false;
    }
    s->history_idx = 0;
    s->first_frame = true;
    return true;
}

void taa_shutdown(TAASystem *taa) {
    if (!taa->device) return;
    if (taa->bind_resolve) rhi_pipeline_bindings_destroy(taa->device, taa->bind_resolve);
    taa->bind_resolve = NULL;
    for (int i = 0; i < 2; i++) {
        if (rhi_handle_valid(taa->history_fbo[i].fb))
            rhi_offscreen_fbo_destroy(taa->device, &taa->history_fbo[i]);
    }
    if (rhi_handle_valid(taa->sampler)) rhi_sampler_destroy(taa->device, taa->sampler);
    if (rhi_handle_valid(taa->resolve_pipe)) rhi_pipeline_destroy(taa->device, taa->resolve_pipe);
    taa->ready = false;
}

void taa_resolve(TAASystem *taa, RHICmdBuffer *cmd,
                 RHITexture current_color, RHITexture depth_tex,
                 RHITexture velocity_tex,
                 const f32 *curr_vp, const f32 *prev_vp,
                 const f32 *inv_proj, u32 screen_w, u32 screen_h) {
    if (!taa->ready) return;

    int write_idx = taa->history_idx;
    int read_idx = 1 - taa->history_idx;

    rhi_cmd_end_render_pass(cmd);

    rhi_offscreen_fbo_bind(cmd, &taa->history_fbo[write_idx]);

    rhi_cmd_bind_pipeline(cmd, taa->resolve_pipe);

    RHITexture hist_tex = taa->first_frame ? current_color : taa->history_fbo[read_idx].color_tex;
    bool use_vel = rhi_handle_valid(velocity_tex);
    /* R437: always update all 4 descriptors — the shader statically declares
       binding 3 (u_taa_velocity), so an unupdated descriptor trips
       VUID-vkCmdDraw-None-08114 even when u_taa_use_velocity gates it off. */
    RHITexture vel_tex = use_vel ? velocity_tex : current_color;
    RHITexture tex[4] = { current_color, hist_tex, depth_tex, vel_tex };
    rhi_cmd_bind_textures_multi(cmd, tex, 4, taa->sampler);

    if (taa->loc_curr_vp >= 0) rhi_cmd_set_uniform_mat4(cmd, taa->loc_curr_vp, curr_vp);
    if (taa->loc_prev_vp >= 0) rhi_cmd_set_uniform_mat4(cmd, taa->loc_prev_vp, prev_vp);
    if (taa->loc_inv_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, taa->loc_inv_proj, inv_proj);
    if (taa->loc_screen_w >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_screen_w, (f32)screen_w);
    if (taa->loc_screen_h >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_screen_h, (f32)screen_h);
    if (taa->loc_blend >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_blend, 0.1f);
    if (taa->loc_first_frame >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_first_frame, taa->first_frame ? 1.0f : 0.0f);
    if (taa->loc_use_velocity >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_use_velocity, use_vel ? 1.0f : 0.0f);

    rhi_cmd_draw(cmd, 3, 1);

    /* R196-B: skip intermediate swapchain CLEAR unbind. */

    taa->history_idx = read_idx;
    taa->first_frame = false;
}

RHITexture taa_get_output(TAASystem *taa) {
    if (!taa->ready) return RHI_HANDLE_NULL;
    return taa->history_fbo[1 - taa->history_idx].color_tex;
}
