#include "contact_shadow.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *cs_read_file(const char *path, usize *out_len) {
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

static RHIPipeline cs_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = cs_read_file(vert_path, &vs_len);
    char *fs_src = cs_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("ContactShadow: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("ContactShadow: shader compile failed");
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

bool contact_shadow_init(ContactShadowSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

#ifdef ENGINE_VULKAN
    s->pipe = cs_create_pipe(dev, "shaders/post_vk.vert", "shaders/contact_shadow_vk.frag");
#else
    s->pipe = cs_create_pipe(dev, "shaders/post.vert", "shaders/contact_shadow.frag");
#endif

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("ContactShadow: pipeline creation failed");
        return false;
    }

    u32 hw = w / 2, hh = h / 2;
    if (hw < 1) hw = 1;
    if (hh < 1) hh = 1;
    s->fbo = rhi_offscreen_fbo_create_fmt(dev, hw, hh, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    s->loc_light_x = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cs_light_x");
    s->loc_light_y = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cs_light_y");
    s->loc_light_z = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cs_light_z");
    s->loc_inv_proj = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cs_inv_proj");
    s->loc_sw       = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cs_sw");
    s->loc_sh       = rhi_pipeline_get_uniform_location(dev, s->pipe, "u_cs_sh");

    s->ready = true;
    LOG_INFO("ContactShadow: initialized (%ux%u)", hw, hh);
    return true;
}

void contact_shadow_shutdown(ContactShadowSystem *s) {
    if (!s->dev) return;
    if (rhi_handle_valid(s->fbo.fb))   rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->sampler))  rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->pipe))     rhi_pipeline_destroy(s->dev, s->pipe);
    s->ready = false;
}

void contact_shadow_apply(ContactShadowSystem *s, RHICmdBuffer *cmd,
                          RHITexture depth_tex, const f32 *inv_proj,
                          f32 lx, f32 ly, f32 lz, u32 w, u32 h) {
    if (!s->ready) return;

    rhi_offscreen_fbo_bind(cmd, &s->fbo);

    rhi_cmd_bind_pipeline(cmd, s->pipe);
    rhi_cmd_bind_texture(cmd, depth_tex, s->sampler, 0);

    if (s->loc_light_x >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_light_x, lx);
    if (s->loc_light_y >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_light_y, ly);
    if (s->loc_light_z >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_light_z, lz);
    if (s->loc_inv_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, s->loc_inv_proj, inv_proj);
    if (s->loc_sw >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sw, (f32)w);
    if (s->loc_sh >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sh, (f32)h);

    rhi_cmd_draw(cmd, 3, 1);
}
