#include "contact_shadow.h"
#include <renderer/post_targets.h>
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline cs_create_pipe_path(RHIDevice *dev, const char *vert_path,
                                       const char *frag_path) {
    RHIShader vs = rhi_shader_create_path(dev, vert_path, false);
    RHIShader fs = rhi_shader_create_path(dev, frag_path, true);
    RHIPipelineDesc pdesc;
    RHIPipeline pipe;
    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("ContactShadow: sidecar shader unavailable (%s, %s)",
                 vert_path, frag_path);
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

static RHIPipeline cs_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
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

static bool contact_shadow_targets_create(ContactShadowSystem *s, RHIDevice *dev, u32 w, u32 h) {
    const PostTargetSpec t[1] = {
        { &s->fbo, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT },
    };
    return post_targets_replace(dev, t, 1u);
}

bool contact_shadow_init(ContactShadowSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev) return false;
    memset(s, 0, sizeof(*s));
    s->dev = dev;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps)) {
        LOG_WARN("ContactShadow: capability query failed");
        return false;
    }
    if (caps.shader_sidecar_paths) {
        /* R625: D3D12 never compiles HLSL in-process; the backend resolves
         * these to post_hlsl.vert / contact_shadow_hlsl.frag. */
        s->pipe = cs_create_pipe_path(dev, "shaders/post.vert",
                                      "shaders/contact_shadow.frag");
    } else {
        if (!shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path)) ||
            !shader_variant_path("shaders/contact_shadow.frag", (RHIShaderVariant)caps.shader_variant, fs_path, sizeof(fs_path))) {
            LOG_WARN("ContactShadow: shader variant path failed");
            return false;
        }
        s->pipe = cs_create_pipe(dev, vs_path, fs_path);
    }

    if (!rhi_handle_valid(s->pipe)) {
        LOG_WARN("ContactShadow: pipeline creation failed");
        return false;
    }

    /* 计划 E Task 5 T2：管线创建成功后立刻物化反射表。u_cs_* 是
     * contact_shadow(_vk).frag 的真实成员名，两后端同源，无别名行。 */
    s->bind_pipe = rhi_pipeline_bindings_create(dev, s->pipe);
    if (!s->bind_pipe)
        LOG_WARN("ContactShadow: bindings create failed; uniform locations resolve -1");

    /* R550-A: full-res FBO — the pass now self-composites the frame-chain
     * color (god_rays idiom), so the output must not lose scene detail.
     * Pass stays opt-in (cs_enabled default off), so no default cost. */
    u32 hw = w, hh = h;
    (void)contact_shadow_targets_create(s, dev, hw, hh);

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
        LOG_WARN("ContactShadow: FBO/sampler creation failed");
        contact_shadow_shutdown(s);
        return false;
    }

    s->loc_light_x = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cs_light_x");
    s->loc_light_y = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cs_light_y");
    s->loc_light_z = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cs_light_z");
    s->loc_inv_proj = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cs_inv_proj");
    s->loc_sw       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cs_sw");
    s->loc_sh       = rhi_pipeline_bindings_resolve(s->bind_pipe, "u_cs_sh");

    s->ready = true;
    LOG_INFO("ContactShadow: initialized (%ux%u)", hw, hh);
    return true;
}

bool contact_shadow_resize(ContactShadowSystem *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev || !s->ready || s->dev != dev) return false;
    if (!contact_shadow_targets_create(s, dev, w, h)) {
        LOG_WARN("ContactShadow: resize to %ux%u failed; keeping previous targets", w, h);
        return false;
    }
    return true;
}

void contact_shadow_shutdown(ContactShadowSystem *s) {
    if (!s->dev) return;
    if (s->bind_pipe) { rhi_pipeline_bindings_destroy(s->dev, s->bind_pipe); s->bind_pipe = NULL; }
    if (rhi_handle_valid(s->fbo.fb))   rhi_offscreen_fbo_destroy(s->dev, &s->fbo);
    if (rhi_handle_valid(s->sampler))  rhi_sampler_destroy(s->dev, s->sampler);
    if (rhi_handle_valid(s->pipe))     rhi_pipeline_destroy(s->dev, s->pipe);
    s->ready = false;
}

void contact_shadow_apply(ContactShadowSystem *s, RHICmdBuffer *cmd,
                          RHITexture depth_tex, RHITexture scene_tex,
                          const f32 *inv_proj,
                          f32 lx, f32 ly, f32 lz, u32 w, u32 h) {
    if (!s->ready) return;

    rhi_offscreen_fbo_bind(cmd, &s->fbo);

    rhi_cmd_bind_pipeline(cmd, s->pipe);
    /* R550-A: depth@0 + chain color@1 (multi writes consecutive bindings on
     * VK; rhi_cmd_bind_texture would replicate depth over every slot). */
    RHITexture tex[2] = { depth_tex, scene_tex };
    rhi_cmd_bind_textures_multi(cmd, tex, 2, s->sampler);

    if (s->loc_light_x >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_light_x, lx);
    if (s->loc_light_y >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_light_y, ly);
    if (s->loc_light_z >= 0) rhi_cmd_set_uniform_f32(cmd, s->loc_light_z, lz);
    if (s->loc_inv_proj >= 0) rhi_cmd_set_uniform_mat4(cmd, s->loc_inv_proj, inv_proj);
    if (s->loc_sw >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sw, (f32)w);
    if (s->loc_sh >= 0)       rhi_cmd_set_uniform_f32(cmd, s->loc_sh, (f32)h);

    rhi_cmd_draw(cmd, 3, 1);
}
