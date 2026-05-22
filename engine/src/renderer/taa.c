#include <renderer/taa.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *taa_read_file(const char *path, usize *out_len) {
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

static RHIPipeline taa_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = taa_read_file(vert_path, &vs_len);
    char *fs_src = taa_read_file(frag_path, &fs_len);
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

bool taa_init(TAASystem *taa, RHIDevice *dev, u32 width, u32 height) {
    memset(taa, 0, sizeof(*taa));
    taa->device = dev;
    taa->history_idx = 0;
    taa->first_frame = true;

#ifdef ENGINE_VULKAN
    taa->resolve_pipe = taa_create_pipe(dev, "shaders/post_vk.vert", "shaders/taa_vk.frag");
#else
    taa->resolve_pipe = taa_create_pipe(dev, "shaders/post.vert", "shaders/taa.frag");
#endif

    if (!rhi_handle_valid(taa->resolve_pipe)) {
        LOG_WARN("TAA: pipeline creation failed");
        return false;
    }

    taa->history_fbo[0] = rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_R16G16B16A16_SFLOAT);
    taa->history_fbo[1] = rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    taa->sampler = rhi_sampler_create(dev, &sdesc);

    taa->loc_curr_tex = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_curr_tex");
    taa->loc_hist_tex = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_hist_tex");
    taa->loc_depth_tex = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_depth");
    taa->loc_curr_vp = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_curr_vp");
    taa->loc_prev_vp = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_prev_vp");
    taa->loc_inv_proj = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_inv_proj");
    taa->loc_screen_w = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_sw");
    taa->loc_screen_h = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_sh");
    taa->loc_blend = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_blend");
    taa->loc_first_frame = rhi_pipeline_get_uniform_location(dev, taa->resolve_pipe, "u_taa_first_frame");

    taa->ready = true;
    LOG_INFO("TAA: initialized (%ux%u)", width, height);
    return true;
}

void taa_shutdown(TAASystem *taa) {
    if (!taa->device) return;
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
                 const f32 *curr_vp, const f32 *prev_vp,
                 const f32 *inv_proj, u32 screen_w, u32 screen_h) {
    if (!taa->ready) return;

    int write_idx = taa->history_idx;
    int read_idx = 1 - taa->history_idx;

    rhi_cmd_end_render_pass(cmd);

    rhi_offscreen_fbo_bind(cmd, &taa->history_fbo[write_idx]);

    rhi_cmd_bind_pipeline(cmd, taa->resolve_pipe);

    RHITexture hist_tex = taa->first_frame ? current_color : taa->history_fbo[read_idx].color_tex;
    RHITexture tex[3] = { current_color, hist_tex, depth_tex };
    rhi_cmd_bind_textures_multi(cmd, tex, 3, taa->sampler);

    if (taa->loc_curr_vp >= 0) rhi_cmd_set_uniform_mat4(cmd, taa->loc_curr_vp, curr_vp);
    if (taa->loc_prev_vp >= 0) rhi_cmd_set_uniform_mat4(cmd, taa->loc_prev_vp, prev_vp);
    if (taa->loc_inv_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, taa->loc_inv_proj, inv_proj);
    if (taa->loc_screen_w >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_screen_w, (f32)screen_w);
    if (taa->loc_screen_h >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_screen_h, (f32)screen_h);
    if (taa->loc_blend >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_blend, 0.1f);
    if (taa->loc_first_frame >= 0) rhi_cmd_set_uniform_f32(cmd, taa->loc_first_frame, taa->first_frame ? 1.0f : 0.0f);

    rhi_cmd_draw(cmd, 3, 1);

    rhi_offscreen_fbo_unbind(cmd, screen_w, screen_h);

    taa->history_idx = read_idx;
    taa->first_frame = false;
}

RHITexture taa_get_output(TAASystem *taa) {
    if (!taa->ready) return RHI_HANDLE_NULL;
    return taa->history_fbo[1 - taa->history_idx].color_tex;
}
