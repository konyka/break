#include <renderer/volumetric.h>
#include <core/log.h>
#include <math/math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *vol_read_file(const char *path, usize *out_len) {
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

static RHIPipeline vol_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = vol_read_file(vert_path, &vs_len);
    char *fs_src = vol_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("Volumetric: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Volumetric: shader compile failed");
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
        .alpha_blend = true,
    };
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

bool volumetric_init(VolumetricSystem *vol, RHIDevice *dev, u32 width, u32 height) {
    memset(vol, 0, sizeof(*vol));
    vol->device = dev;
    vol->fog_density = 0.015f;
    vol->fog_color[0] = 0.5f;
    vol->fog_color[1] = 0.55f;
    vol->fog_color[2] = 0.6f;

#ifdef ENGINE_VULKAN
    vol->vol_pipe = vol_create_pipe(dev, "shaders/post_vk.vert", "shaders/volumetric_vk.frag");
#else
    vol->vol_pipe = vol_create_pipe(dev, "shaders/post.vert", "shaders/volumetric.frag");
#endif

    if (!rhi_handle_valid(vol->vol_pipe)) {
        LOG_WARN("Volumetric: pipeline creation failed");
        return false;
    }

    /* R347: main clamps render size to ≥1; width/2 can still be 0 → VK extent 0. */
    u32 pw = width / 2, ph = height / 2;
    if (pw < 1) pw = 1;
    if (ph < 1) ph = 1;

    vol->vol_fbo = rhi_offscreen_fbo_create(dev, pw, ph);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    vol->sampler = rhi_sampler_create(dev, &sdesc);

    if (!rhi_handle_valid(vol->vol_fbo.fb) || !rhi_handle_valid(vol->sampler)) {
        LOG_WARN("Volumetric: FBO/sampler creation failed");
        volumetric_shutdown(vol);
        return false;
    }

    vol->loc_inv_proj     = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_inv_proj");
    vol->loc_view         = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_view");
    vol->loc_inv_view     = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_inv_view");
    vol->loc_ldx          = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_ldx");
    vol->loc_ldy          = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_ldy");
    vol->loc_ldz          = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_ldz");
    vol->loc_lcx          = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_lcx");
    vol->loc_lcy          = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_lcy");
    vol->loc_lcz          = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_lcz");
    vol->loc_fog_density  = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_density");
    vol->loc_fog_color_r  = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_fog_r");
    vol->loc_fog_color_g  = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_fog_g");
    vol->loc_fog_color_b  = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_fog_b");
    vol->loc_screen_w     = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_sw");
    vol->loc_screen_h     = rhi_pipeline_get_uniform_location(dev, vol->vol_pipe, "u_vol_sh");

    vol->ready = true;
    LOG_INFO("Volumetric: initialized (%ux%u, density=%.4f)", pw, ph, vol->fog_density);
    return true;
}

void volumetric_shutdown(VolumetricSystem *vol) {
    if (!vol->device) return;
    if (rhi_handle_valid(vol->vol_fbo.fb)) rhi_offscreen_fbo_destroy(vol->device, &vol->vol_fbo);
    if (rhi_handle_valid(vol->sampler)) rhi_sampler_destroy(vol->device, vol->sampler);
    if (rhi_handle_valid(vol->vol_pipe)) rhi_pipeline_destroy(vol->device, vol->vol_pipe);
    vol->ready = false;
}

void volumetric_apply(VolumetricSystem *vol, RHICmdBuffer *cmd,
                      RHITexture depth_tex, RHITexture shadow_tex,
                      const f32 *inv_proj, const f32 *view,
                      const f32 *light_dir, const f32 *light_color,
                      u32 screen_w, u32 screen_h) {
    if (!vol->ready) return;

    rhi_cmd_end_render_pass(cmd);

    rhi_offscreen_fbo_bind(cmd, &vol->vol_fbo);

    rhi_cmd_bind_pipeline(cmd, vol->vol_pipe);

    RHITexture tex[2] = { depth_tex, shadow_tex };
    rhi_cmd_bind_textures_multi(cmd, tex, 2, vol->sampler);

    if (vol->loc_inv_proj >= 0)     rhi_cmd_set_uniform_mat4(cmd, vol->loc_inv_proj, inv_proj);
    if (vol->loc_view >= 0)         rhi_cmd_set_uniform_mat4(cmd, vol->loc_view, view);
    /* R224-B: One CPU inverse instead of per-fragment GLSL inverse(). */
    if (vol->loc_inv_view >= 0 && view) {
        Mat4 inv_view = mat4_inverse(*(const Mat4 *)view);
        rhi_cmd_set_uniform_mat4(cmd, vol->loc_inv_view, &inv_view.e[0][0]);
    }
    if (vol->loc_ldx >= 0)          rhi_cmd_set_uniform_f32(cmd, vol->loc_ldx, light_dir[0]);
    if (vol->loc_ldy >= 0)          rhi_cmd_set_uniform_f32(cmd, vol->loc_ldy, light_dir[1]);
    if (vol->loc_ldz >= 0)          rhi_cmd_set_uniform_f32(cmd, vol->loc_ldz, light_dir[2]);
    if (vol->loc_lcx >= 0)          rhi_cmd_set_uniform_f32(cmd, vol->loc_lcx, light_color[0]);
    if (vol->loc_lcy >= 0)          rhi_cmd_set_uniform_f32(cmd, vol->loc_lcy, light_color[1]);
    if (vol->loc_lcz >= 0)          rhi_cmd_set_uniform_f32(cmd, vol->loc_lcz, light_color[2]);
    if (vol->loc_fog_density >= 0)  rhi_cmd_set_uniform_f32(cmd, vol->loc_fog_density, vol->fog_density);
    if (vol->loc_fog_color_r >= 0)  rhi_cmd_set_uniform_f32(cmd, vol->loc_fog_color_r, vol->fog_color[0]);
    if (vol->loc_fog_color_g >= 0)  rhi_cmd_set_uniform_f32(cmd, vol->loc_fog_color_g, vol->fog_color[1]);
    if (vol->loc_fog_color_b >= 0)  rhi_cmd_set_uniform_f32(cmd, vol->loc_fog_color_b, vol->fog_color[2]);
    if (vol->loc_screen_w >= 0)     rhi_cmd_set_uniform_f32(cmd, vol->loc_screen_w, (f32)screen_w);
    if (vol->loc_screen_h >= 0)     rhi_cmd_set_uniform_f32(cmd, vol->loc_screen_h, (f32)screen_h);

    rhi_cmd_draw(cmd, 3, 1);

    /* R196-B: skip intermediate swapchain CLEAR unbind. */
}

RHITexture volumetric_get_texture(VolumetricSystem *vol) {
    return vol->ready ? vol->vol_fbo.color_tex : RHI_HANDLE_NULL;
}
