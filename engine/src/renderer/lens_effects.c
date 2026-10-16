#include "lens_effects.h"
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline le_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("LensEffects: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("LensEffects: shader compile failed");
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

bool lens_effects_init(LensEffectsSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
        !shader_variant_path("shaders/lens_effects.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
        LOG_WARN("LensEffects: capability query or shader variant path failed");
        return false;
    }
    s->pipe = le_create_pipe(dev, vs_path, fs_path);

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("LensEffects: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_ca_strength 等
     * 是 lens_effects(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    s->bind_pipe = rhi_pipeline_bindings_create(dev, s->pipe);
    if (!s->bind_pipe)
        LOG_WARN("LensEffects: bindings create failed; uniform locations resolve -1");

    s->fbo = rhi_offscreen_fbo_create(dev, w, h);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    s->sampler = rhi_sampler_create(dev, &sdesc);

    /* R349: align R348 — do not mark ready with empty FBO/sampler handles. */
    if (!rhi_handle_valid(s->fbo.fb) || !rhi_handle_valid(s->sampler)) {
        LOG_WARN("LensEffects: FBO/sampler creation failed");
        lens_effects_shutdown(s);
        return false;
    }

    s->loc_ca_strength = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_ca_strength");
    s->loc_vignette_strength = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_vignette_strength");
    s->loc_vignette_softness = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_vignette_softness");
    s->loc_grain_strength = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_grain_strength");

    s->ready = true;
    return true;
}

void lens_effects_shutdown(LensEffectsSystem *s) {
    if (!s || !s->dev) return;
    if (s->bind_pipe) { rhi_pipeline_bindings_destroy(s->dev, s->bind_pipe); s->bind_pipe = NULL; }
    if (rhi_handle_valid(s->pipe)) rhi_pipeline_destroy(s->dev, s->pipe);
    if (rhi_handle_valid(s->fbo.fb)) rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->sampler)) rhi_sampler_destroy(s->dev, s->sampler);
    memset(s, 0, sizeof(*s));
}

void lens_effects_apply(LensEffectsSystem *s, RHICmdBuffer *cmd,
                        RHITexture input_tex,
                        f32 ca_strength, f32 vignette_strength,
                        f32 vignette_softness, f32 grain_strength,
                        u32 w, u32 h) {
    if (!s || !s->ready) return;
    (void)w; (void)h;

    rhi_offscreen_fbo_bind(cmd, &s->fbo);

    rhi_cmd_bind_pipeline(cmd, s->pipe);
    rhi_cmd_bind_texture(cmd, input_tex, s->sampler, 0);

    if (s->loc_ca_strength >= 0)      rhi_cmd_set_uniform_f32(cmd, s->loc_ca_strength, ca_strength);
    if (s->loc_vignette_strength >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_vignette_strength, vignette_strength);
    if (s->loc_vignette_softness >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_vignette_softness, vignette_softness);
    if (s->loc_grain_strength >= 0)    rhi_cmd_set_uniform_f32(cmd, s->loc_grain_strength, grain_strength);

    rhi_cmd_draw(cmd, 3, 1);
    /* R197-B: skip intermediate swapchain CLEAR unbind (main does final unbind). */
}
