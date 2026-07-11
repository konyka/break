#include <renderer/ssr.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ssr_read_file(const char *path, usize *out_len) {
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

static RHIPipeline ssr_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = ssr_read_file(vert_path, &vs_len);
    char *fs_src = ssr_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("SSR: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("SSR: shader compile failed");
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

bool ssr_init(SSRSystem *ssr, RHIDevice *dev, u32 width, u32 height) {
    memset(ssr, 0, sizeof(*ssr));
    ssr->device = dev;

#ifdef ENGINE_VULKAN
    ssr->ssr_pipe = ssr_create_pipe(dev, "shaders/post_vk.vert", "shaders/ssr_vk.frag");
#else
    ssr->ssr_pipe = ssr_create_pipe(dev, "shaders/post.vert", "shaders/ssr.frag");
#endif

    if (!rhi_handle_valid(ssr->ssr_pipe)) {
        LOG_WARN("SSR: pipeline creation failed");
        return false;
    }

    ssr->ssr_fbo = rhi_offscreen_fbo_create_fmt(dev, width / 2, height / 2, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    ssr->sampler = rhi_sampler_create(dev, &sdesc);

    ssr->loc_proj       = rhi_pipeline_get_uniform_location(dev, ssr->ssr_pipe, "u_ssr_proj");
    ssr->loc_inv_proj   = rhi_pipeline_get_uniform_location(dev, ssr->ssr_pipe, "u_ssr_inv_proj");
    ssr->loc_view       = rhi_pipeline_get_uniform_location(dev, ssr->ssr_pipe, "u_ssr_view");
    ssr->loc_screen_w   = rhi_pipeline_get_uniform_location(dev, ssr->ssr_pipe, "u_ssr_sw");
    ssr->loc_screen_h   = rhi_pipeline_get_uniform_location(dev, ssr->ssr_pipe, "u_ssr_sh");
    ssr->loc_max_steps  = rhi_pipeline_get_uniform_location(dev, ssr->ssr_pipe, "u_ssr_max_steps");
    ssr->loc_stride     = rhi_pipeline_get_uniform_location(dev, ssr->ssr_pipe, "u_ssr_stride");
    ssr->loc_thickness  = rhi_pipeline_get_uniform_location(dev, ssr->ssr_pipe, "u_ssr_thickness");

    ssr->ready = true;
    LOG_INFO("SSR: initialized (%ux%u)", width / 2, height / 2);
    return true;
}

void ssr_shutdown(SSRSystem *ssr) {
    if (!ssr->device) return;
    if (rhi_handle_valid(ssr->ssr_fbo.fb)) rhi_offscreen_fbo_destroy(ssr->device, &ssr->ssr_fbo);
    if (rhi_handle_valid(ssr->sampler)) rhi_sampler_destroy(ssr->device, ssr->sampler);
    if (rhi_handle_valid(ssr->ssr_pipe)) rhi_pipeline_destroy(ssr->device, ssr->ssr_pipe);
    ssr->ready = false;
}

void ssr_apply(SSRSystem *ssr, RHICmdBuffer *cmd, RHITexture color_tex, RHITexture depth_tex,
               const f32 *proj, const f32 *inv_proj, const f32 *view, u32 screen_w, u32 screen_h) {
    if (!ssr->ready) return;

    rhi_cmd_end_render_pass(cmd);

    rhi_offscreen_fbo_bind(cmd, &ssr->ssr_fbo);

    rhi_cmd_bind_pipeline(cmd, ssr->ssr_pipe);

    RHITexture tex[2] = { color_tex, depth_tex };
    rhi_cmd_bind_textures_multi(cmd, tex, 2, ssr->sampler);

    if (ssr->loc_proj >= 0)      rhi_cmd_set_uniform_mat4(cmd, ssr->loc_proj, proj);
    if (ssr->loc_inv_proj >= 0)  rhi_cmd_set_uniform_mat4(cmd, ssr->loc_inv_proj, inv_proj);
    if (ssr->loc_view >= 0)      rhi_cmd_set_uniform_mat4(cmd, ssr->loc_view, view);
    if (ssr->loc_screen_w >= 0)  rhi_cmd_set_uniform_f32(cmd, ssr->loc_screen_w, (f32)screen_w);
    if (ssr->loc_screen_h >= 0)  rhi_cmd_set_uniform_f32(cmd, ssr->loc_screen_h, (f32)screen_h);
    if (ssr->loc_max_steps >= 0) rhi_cmd_set_uniform_f32(cmd, ssr->loc_max_steps, 32.0f);
    if (ssr->loc_stride >= 0)    rhi_cmd_set_uniform_f32(cmd, ssr->loc_stride, 2.0f);
    if (ssr->loc_thickness >= 0) rhi_cmd_set_uniform_f32(cmd, ssr->loc_thickness, 0.05f);

    rhi_cmd_draw(cmd, 3, 1);

    /* R196-B: skip intermediate swapchain CLEAR unbind. */
}

RHITexture ssr_get_texture(SSRSystem *ssr) {
    return ssr->ready ? ssr->ssr_fbo.color_tex : RHI_HANDLE_NULL;
}
