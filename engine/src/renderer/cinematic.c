#include <renderer/cinematic.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *cine_read_file(const char *path, usize *out_len) {
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

static RHIPipeline cine_create_pipe(RHIDevice *dev,
                                     const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = cine_read_file(vert_path, &vs_len);
    char *fs_src = cine_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("Cinematic: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Cinematic: shader compile failed");
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

bool cinematic_init(CinematicSystem *cine, RHIDevice *dev) {
    memset(cine, 0, sizeof(*cine));
    cine->device = dev;
    cine->aberration = 0.003f;
    cine->vignette = 0.4f;
    cine->grain = 0.03f;

#ifdef ENGINE_VULKAN
    cine->cine_pipe = cine_create_pipe(dev, "shaders/post_vk.vert", "shaders/cinematic_vk.frag");
#else
    cine->cine_pipe = cine_create_pipe(dev, "shaders/post.vert", "shaders/cinematic.frag");
#endif

    if (!rhi_handle_valid(cine->cine_pipe)) {
        LOG_WARN("Cinematic: pipeline creation failed");
        return false;
    }

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    cine->sampler = rhi_sampler_create(dev, &sdesc);

    /* R350: align R348 — do not mark ready with empty sampler. */
    if (!rhi_handle_valid(cine->sampler)) {
        LOG_WARN("Cinematic: sampler creation failed");
        cinematic_shutdown(cine);
        return false;
    }

    cine->loc_aberration = rhi_pipeline_get_uniform_location(dev, cine->cine_pipe, "u_cine_aberration");
    cine->loc_vignette   = rhi_pipeline_get_uniform_location(dev, cine->cine_pipe, "u_cine_vignette");
    cine->loc_grain      = rhi_pipeline_get_uniform_location(dev, cine->cine_pipe, "u_cine_grain");
    cine->loc_time       = rhi_pipeline_get_uniform_location(dev, cine->cine_pipe, "u_cine_time");
    cine->loc_screen_w   = rhi_pipeline_get_uniform_location(dev, cine->cine_pipe, "u_cine_sw");
    cine->loc_screen_h   = rhi_pipeline_get_uniform_location(dev, cine->cine_pipe, "u_cine_sh");

    cine->ready = true;
    LOG_INFO("Cinematic: initialized (aberration=%.4f vignette=%.2f grain=%.3f)",
             cine->aberration, cine->vignette, cine->grain);
    return true;
}

void cinematic_shutdown(CinematicSystem *cine) {
    if (!cine->device) return;
    if (rhi_handle_valid(cine->sampler)) rhi_sampler_destroy(cine->device, cine->sampler);
    if (rhi_handle_valid(cine->cine_pipe)) rhi_pipeline_destroy(cine->device, cine->cine_pipe);
    cine->ready = false;
}

void cinematic_apply(CinematicSystem *cine, RHICmdBuffer *cmd, RHITexture input_tex,
                     u32 screen_w, u32 screen_h, f32 time) {
    if (!cine->ready) return;

    rhi_cmd_bind_pipeline(cmd, cine->cine_pipe);
    rhi_cmd_bind_texture(cmd, input_tex, cine->sampler, 0);

    if (cine->loc_aberration >= 0) rhi_cmd_set_uniform_f32(cmd, cine->loc_aberration, cine->aberration);
    if (cine->loc_vignette >= 0)   rhi_cmd_set_uniform_f32(cmd, cine->loc_vignette, cine->vignette);
    if (cine->loc_grain >= 0)      rhi_cmd_set_uniform_f32(cmd, cine->loc_grain, cine->grain);
    if (cine->loc_time >= 0)       rhi_cmd_set_uniform_f32(cmd, cine->loc_time, time);
    if (cine->loc_screen_w >= 0)   rhi_cmd_set_uniform_f32(cmd, cine->loc_screen_w, (f32)screen_w);
    if (cine->loc_screen_h >= 0)   rhi_cmd_set_uniform_f32(cmd, cine->loc_screen_h, (f32)screen_h);

    rhi_cmd_draw(cmd, 3, 1);
}
