#include "god_rays.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline gr_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("GodRays: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("GodRays: shader compile failed");
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

bool god_rays_init(GodRaysSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
        !shader_variant_path("shaders/god_rays.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
        LOG_WARN("GodRays: capability query or shader variant path failed");
        return false;
    }
    s->pipe = gr_create_pipe(dev, vs_path, fs_path);

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("GodRays: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_gr_ 前缀名是
     * god_rays(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    s->bind_pipe = rhi_pipeline_bindings_create(dev, s->pipe);
    if (!s->bind_pipe)
        LOG_WARN("GodRays: bindings create failed; uniform locations resolve -1");

    s->fbo = rhi_offscreen_fbo_create_fmt(dev, w, h, RHI_FORMAT_R8G8B8A8_UNORM);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    /* R348: align R347 — do not mark ready with empty FBO/sampler handles. */
    if (!rhi_handle_valid(s->fbo.fb) || !rhi_handle_valid(s->sampler)) {
        LOG_WARN("GodRays: FBO/sampler creation failed");
        god_rays_shutdown(s);
        return false;
    }

    s->loc_sun_x    = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_gr_sun_x");
    s->loc_sun_y    = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_gr_sun_y");
    s->loc_intensity = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_gr_intensity");
    s->loc_sw       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_gr_sw");
    s->loc_sh       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_gr_sh");

    s->ready = true;
    LOG_INFO("GodRays: initialized (%ux%u)", w, h);
    return true;
}

void god_rays_shutdown(GodRaysSystem *s) {
    if (!s->dev) return;
    if (s->bind_pipe) { rhi_pipeline_bindings_destroy(s->dev, s->bind_pipe); s->bind_pipe = NULL; }
    if (rhi_handle_valid(s->fbo.fb))   rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->sampler))  rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->pipe))     rhi_pipeline_destroy(s->dev, s->pipe);
    s->ready = false;
}

void god_rays_apply(GodRaysSystem *s, RHICmdBuffer *cmd,
                    RHITexture scene_tex, RHITexture depth_tex,
                    f32 sun_x, f32 sun_y, f32 intensity,
                    u32 w, u32 h) {
    if (!s->ready) return;
    /* R217-B: intensity==0 → no rays; skip fullscreen pass (caller must not
     * switch tonemap_input to stale fbo). */
    if (intensity <= 0.0f) return;

    rhi_offscreen_fbo_bind(cmd, &s->fbo);

    rhi_cmd_bind_pipeline(cmd, s->pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures to avoid VK texture binding
     * overwrite bug when binding two textures. */
    rhi_cmd_bind_material_textures(cmd, scene_tex, scene_tex, scene_tex,
                                   scene_tex, depth_tex, scene_tex, s->sampler);

    if (s->loc_sun_x >= 0)     rhi_cmd_set_uniform_f32(cmd, s->loc_sun_x, sun_x);
    if (s->loc_sun_y >= 0)     rhi_cmd_set_uniform_f32(cmd, s->loc_sun_y, sun_y);
    if (s->loc_intensity >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_intensity, intensity);
    if (s->loc_sw >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_sw, (f32)w);
    if (s->loc_sh >= 0)        rhi_cmd_set_uniform_f32(cmd, s->loc_sh, (f32)h);

    rhi_cmd_draw(cmd, 3, 1);
}
