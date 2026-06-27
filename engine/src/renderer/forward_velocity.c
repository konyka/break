#include <renderer/forward_velocity.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *fv_read_file(const char *path, usize *out_len) {
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

static RHIPipeline fv_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = fv_read_file(vert_path, &vs_len);
    char *fs_src = fv_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("ForwardVelocity: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
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

bool forward_velocity_init(ForwardVelocitySystem *sys, RHIDevice *dev, u32 w, u32 h) {
    if (!sys || !dev) return false;
    memset(sys, 0, sizeof(*sys));
    sys->device = dev;

#ifdef ENGINE_VULKAN
    sys->pipe = fv_create_pipe(dev, "shaders/post_vk.vert", "shaders/camera_velocity_vk.frag");
#else
    sys->pipe = fv_create_pipe(dev, "shaders/post.vert", "shaders/camera_velocity.frag");
#endif
    if (!rhi_handle_valid(sys->pipe)) {
        LOG_WARN("ForwardVelocity: pipeline creation failed");
        return false;
    }

    sys->fbo = rhi_offscreen_fbo_create_fmt(dev, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u     = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v     = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w     = RHI_WRAP_CLAMP_TO_EDGE,
    };
    sys->sampler = rhi_sampler_create(dev, &sdesc);

    sys->loc_inv_proj = rhi_pipeline_get_uniform_location(dev, sys->pipe, "u_inv_proj");
    sys->loc_curr_vp  = rhi_pipeline_get_uniform_location(dev, sys->pipe, "u_curr_vp");
    sys->loc_prev_vp  = rhi_pipeline_get_uniform_location(dev, sys->pipe, "u_prev_vp");

    sys->ready = true;
    LOG_INFO("ForwardVelocity: initialized (%ux%u)", w, h);
    return true;
}

void forward_velocity_shutdown(ForwardVelocitySystem *sys) {
    if (!sys || !sys->device) return;
    if (rhi_handle_valid(sys->fbo.fb)) rhi_offscreen_fbo_destroy(sys->device, &sys->fbo);
    if (rhi_handle_valid(sys->sampler)) rhi_sampler_destroy(sys->device, sys->sampler);
    if (rhi_handle_valid(sys->pipe)) rhi_pipeline_destroy(sys->device, sys->pipe);
    sys->ready = false;
}

void forward_velocity_apply(ForwardVelocitySystem *sys, RHICmdBuffer *cmd,
                            RHITexture depth_tex,
                            const f32 *inv_proj, const f32 *curr_vp, const f32 *prev_vp,
                            u32 w, u32 h) {
    if (!sys || !sys->ready || !rhi_handle_valid(sys->fbo.fb)) return;

    rhi_offscreen_fbo_bind(cmd, &sys->fbo);
    rhi_cmd_bind_pipeline(cmd, sys->pipe);
    rhi_cmd_bind_texture(cmd, depth_tex, sys->sampler, 0u);
    if (inv_proj && sys->loc_inv_proj >= 0)
        rhi_cmd_set_uniform_mat4(cmd, sys->loc_inv_proj, inv_proj);
    if (curr_vp && sys->loc_curr_vp >= 0)
        rhi_cmd_set_uniform_mat4(cmd, sys->loc_curr_vp, curr_vp);
    if (prev_vp && sys->loc_prev_vp >= 0)
        rhi_cmd_set_uniform_mat4(cmd, sys->loc_prev_vp, prev_vp);
    rhi_cmd_draw(cmd, 3u, 1u);
    (void)w; (void)h;
}

RHITexture forward_velocity_get_texture(ForwardVelocitySystem *sys) {
    if (!sys || !sys->ready) return RHI_HANDLE_NULL;
    return sys->fbo.color_tex;
}
