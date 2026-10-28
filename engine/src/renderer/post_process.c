#include <renderer/post_process.h>
#include <renderer/post_targets.h>
#include <core/log.h>
#include <math/math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/shader_io.h>


static RHIPipeline pp_create_pipe(RHIDevice *dev, bool sidecar,
                                   const char *vert_path, const char *frag_path) {
    RHIShader vs, fs;
    if (sidecar) {
        /* D3D12 never compiles source in-process: the GLSL path resolves to
         * the precompiled <name>_hlsl sidecar instead. */
        vs = rhi_shader_create_path(dev, vert_path, false);
        fs = rhi_shader_create_path(dev, frag_path, true);
    } else {
        usize vs_len = 0, fs_len = 0;
        char *vs_src = shader_read_file(vert_path, &vs_len);
        char *fs_src = shader_read_file(frag_path, &fs_len);
        if (!vs_src || !fs_src) {
            LOG_WARN("PostProcess: shaders not found (%s)", frag_path);
            free(vs_src); free(fs_src);
            return RHI_HANDLE_NULL;
        }
        vs = rhi_shader_create(dev, vs_src, vs_len, false);
        fs = rhi_shader_create(dev, fs_src, fs_len, true);
        free(vs_src); free(fs_src);
    }

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("PostProcess: shader compile failed");
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

static bool post_process_targets_create(PostProcess *s, RHIDevice *dev, u32 w, u32 h) {
    const PostTargetSpec t[3] = {
        { &s->fbo_ping, post_targets_half(w), post_targets_half(h), RHI_FORMAT_R16G16B16A16_SFLOAT },
        { &s->fbo_pong, post_targets_half(w), post_targets_half(h), RHI_FORMAT_R16G16B16A16_SFLOAT },
        { &s->fbo_composite, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT },
    };
    return post_targets_replace(dev, t, 3u);
}

bool post_process_init(PostProcess *pp, RHIDevice *dev, u32 width, u32 height) {
    memset(pp, 0, sizeof(*pp));
    pp->device = dev;
    pp->bloom_strength = 0.15f; /* R446: default tuned down -- the composite chain only became visible in R445, 0.4 haze-washed the whole frame */
    pp->threshold = 1.0f;

    /* 计划 E Task 6 F2：shader 源变体由 caps.shader_variant 契约决定。 */
    RHICapabilities caps;
    char vs_path[96], fs_path[96];
    if (!rhi_device_get_capabilities(dev, &caps) ||
        !shader_variant_path("shaders/post.vert", (RHIShaderVariant)caps.shader_variant, vs_path, sizeof(vs_path))) {
        LOG_WARN("PostProcess: capability query or shader variant path failed");
        return false;
    }

    if (!shader_variant_path("shaders/bloom_extract.frag", (RHIShaderVariant)caps.shader_variant,
                             fs_path, sizeof(fs_path))) {
        LOG_WARN("PostProcess: shader variant path failed");
        return false;
    }
    pp->extract_pipe = pp_create_pipe(dev, caps.shader_sidecar_paths, vs_path, fs_path);
    if (!rhi_handle_valid(pp->extract_pipe)) {
        LOG_WARN("PostProcess: extract pipeline failed");
        return false;
    }

    if (!shader_variant_path("shaders/bloom_blur.frag", (RHIShaderVariant)caps.shader_variant,
                             fs_path, sizeof(fs_path))) {
        LOG_WARN("PostProcess: shader variant path failed");
        return false;
    }
    pp->blur_pipe = pp_create_pipe(dev, caps.shader_sidecar_paths, vs_path, fs_path);
    if (!rhi_handle_valid(pp->blur_pipe)) {
        LOG_WARN("PostProcess: blur pipeline failed");
        /* R354: extract_pipe already live — mirror FBO failure shutdown. */
        post_process_shutdown(pp);
        return false;
    }

    if (!shader_variant_path("shaders/post_tex.frag", (RHIShaderVariant)caps.shader_variant,
                             fs_path, sizeof(fs_path))) {
        LOG_WARN("PostProcess: shader variant path failed");
        return false;
    }
    pp->tex_pipe = pp_create_pipe(dev, caps.shader_sidecar_paths, vs_path, fs_path);
    if (!rhi_handle_valid(pp->tex_pipe)) {
        LOG_WARN("PostProcess: tex pipeline failed");
        post_process_shutdown(pp);
        return false;
    }

    if (!shader_variant_path("shaders/bloom_composite.frag", (RHIShaderVariant)caps.shader_variant,
                             fs_path, sizeof(fs_path))) {
        LOG_WARN("PostProcess: shader variant path failed");
        return false;
    }
    pp->composite_pipe = pp_create_pipe(dev, caps.shader_sidecar_paths, vs_path, fs_path);
    if (!rhi_handle_valid(pp->composite_pipe)) {
        LOG_WARN("PostProcess: composite pipeline failed");
        post_process_shutdown(pp);
        return false;
    }

    RHISamplerDesc sdesc;
    memset(&sdesc, 0, sizeof(sdesc));
    sdesc.min_filter = RHI_FILTER_LINEAR;
    sdesc.mag_filter = RHI_FILTER_LINEAR;
    sdesc.wrap_u = RHI_WRAP_CLAMP_TO_EDGE;
    sdesc.wrap_v = RHI_WRAP_CLAMP_TO_EDGE;
    sdesc.wrap_w = RHI_WRAP_CLAMP_TO_EDGE;
    pp->sampler = rhi_sampler_create(dev, &sdesc);
    if (!rhi_handle_valid(pp->sampler)) {
        LOG_WARN("PostProcess: sampler failed");
        post_process_shutdown(pp);
        return false;
    }

    u32 pw = width / 2;
    u32 ph = height / 2;
    if (pw < 1) pw = 1;
    if (ph < 1) ph = 1;

    (void)post_process_targets_create(pp, dev, width, height);
    /* R349: composite is the apply target — include it in the readiness gate. */
    if (!rhi_handle_valid(pp->fbo_ping.fb) || !rhi_handle_valid(pp->fbo_pong.fb) ||
        !rhi_handle_valid(pp->fbo_composite.fb)) {
        LOG_WARN("PostProcess: FBO creation failed");
        post_process_shutdown(pp);
        return false;
    }

    /* 计划 E Task 5 T2：三张被查询管线的反射物化表。u_bloom_strength/
     * u_threshold/u_direction 分别是 bloom_composite、bloom_extract、
     * bloom_blur 系 shader 的真实成员名，两后端同源，无别名行。 */
    pp->bind_composite = rhi_pipeline_bindings_create(dev, pp->composite_pipe);
    pp->bind_extract   = rhi_pipeline_bindings_create(dev, pp->extract_pipe);
    pp->bind_blur      = rhi_pipeline_bindings_create(dev, pp->blur_pipe);
    if (!pp->bind_composite || !pp->bind_extract || !pp->bind_blur)
        LOG_WARN("PostProcess: bindings create failed; uniform locations resolve -1");

    pp->loc_bloom_strength = rhi_pipeline_bindings_resolve(pp->bind_composite, "u_bloom_strength");
    pp->loc_threshold = rhi_pipeline_bindings_resolve(pp->bind_extract, "u_threshold");
    pp->loc_direction = rhi_pipeline_bindings_resolve(pp->bind_blur, "u_direction");

    LOG_INFO("PostProcess: bloom initialized (%ux%u)", pw, ph);
    pp->ready = true;
    return true;
}

bool post_process_resize(PostProcess *s, RHIDevice *dev, u32 w, u32 h) {
    if (!s || !dev || !s->ready || s->device != dev) return false;
    if (!post_process_targets_create(s, dev, w, h)) {
        LOG_WARN("PostProcess: resize to %ux%u failed; keeping previous targets", w, h);
        return false;
    }
    return true;
}

void post_process_shutdown(PostProcess *pp) {
    if (!pp->device) return;
    /* 计划 E Task 5 T4：反射物化表先于管线销毁（memset 随后清零指针）。 */
    if (pp->bind_composite) { rhi_pipeline_bindings_destroy(pp->device, pp->bind_composite); pp->bind_composite = NULL; }
    if (pp->bind_extract)   { rhi_pipeline_bindings_destroy(pp->device, pp->bind_extract);   pp->bind_extract = NULL; }
    if (pp->bind_blur)      { rhi_pipeline_bindings_destroy(pp->device, pp->bind_blur);      pp->bind_blur = NULL; }
    if (rhi_handle_valid(pp->fbo_ping.fb)) rhi_offscreen_fbo_destroy(pp->device, &pp->fbo_ping);
    if (rhi_handle_valid(pp->fbo_pong.fb)) rhi_offscreen_fbo_destroy(pp->device, &pp->fbo_pong);
    if (rhi_handle_valid(pp->fbo_composite.fb)) rhi_offscreen_fbo_destroy(pp->device, &pp->fbo_composite);
    if (rhi_handle_valid(pp->sampler)) rhi_sampler_destroy(pp->device, pp->sampler);
    if (rhi_handle_valid(pp->extract_pipe)) rhi_pipeline_destroy(pp->device, pp->extract_pipe);
    if (rhi_handle_valid(pp->blur_pipe)) rhi_pipeline_destroy(pp->device, pp->blur_pipe);
    if (rhi_handle_valid(pp->composite_pipe)) rhi_pipeline_destroy(pp->device, pp->composite_pipe);
    if (rhi_handle_valid(pp->tex_pipe)) rhi_pipeline_destroy(pp->device, pp->tex_pipe);
    memset(pp, 0, sizeof(*pp));
}

void post_process_apply(PostProcess *pp, RHICmdBuffer *cmd, RHITexture scene_color,
                         u32 screen_w, u32 screen_h) {
    if (!pp->ready) return;
    /* R214-B: bloom_strength==0 → skip extract/blur/composite (~6 fullscreen passes). */
    if (pp->bloom_strength <= 0.0f) return;
    (void)screen_w; (void)screen_h; /* R196-B: kept for API; unbind removed */

    /* Each pass binds its target before its pipeline (Metal needs the render
     * pass open to bind a pipeline, a323c379). A blur pass whose target was
     * the previous pass's source first rebinds the pipeline: that drops the
     * source from the D3D12 descriptor tables, so the texture is never live
     * as a shader resource while it becomes the render target (R643
     * diagnostic). On Metal the extra bind only sets state on the encoder
     * that is still open. */
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_ping);
    rhi_cmd_bind_pipeline(cmd, pp->extract_pipe);
    if (pp->loc_threshold >= 0) rhi_cmd_set_uniform_f32(cmd, pp->loc_threshold, pp->threshold);
    rhi_cmd_bind_texture(cmd, scene_color, pp->sampler, 0);
    rhi_cmd_draw(cmd, 3, 1);

    rhi_offscreen_fbo_bind(cmd, &pp->fbo_pong);
    rhi_cmd_bind_pipeline(cmd, pp->blur_pipe);
    if (pp->loc_direction >= 0) rhi_cmd_set_uniform_vec2(cmd, pp->loc_direction, 1.0f, 0.0f);
    rhi_cmd_bind_texture(cmd, pp->fbo_ping.color_tex, pp->sampler, 0);
    rhi_cmd_draw(cmd, 3, 1);

    rhi_cmd_bind_pipeline(cmd, pp->blur_pipe); /* drop the ping SRV first */
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_ping);
    rhi_cmd_bind_pipeline(cmd, pp->blur_pipe);
    if (pp->loc_direction >= 0) rhi_cmd_set_uniform_vec2(cmd, pp->loc_direction, 0.0f, 1.0f);
    rhi_cmd_bind_texture(cmd, pp->fbo_pong.color_tex, pp->sampler, 0);
    rhi_cmd_draw(cmd, 3, 1);

    rhi_cmd_bind_pipeline(cmd, pp->blur_pipe); /* drop the pong SRV first */
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_pong);
    rhi_cmd_bind_pipeline(cmd, pp->blur_pipe);
    if (pp->loc_direction >= 0) rhi_cmd_set_uniform_vec2(cmd, pp->loc_direction, 1.0f, 0.0f);
    rhi_cmd_bind_texture(cmd, pp->fbo_ping.color_tex, pp->sampler, 0);
    rhi_cmd_draw(cmd, 3, 1);

    rhi_cmd_bind_pipeline(cmd, pp->blur_pipe); /* drop the ping SRV first */
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_ping);
    rhi_cmd_bind_pipeline(cmd, pp->blur_pipe);
    if (pp->loc_direction >= 0) rhi_cmd_set_uniform_vec2(cmd, pp->loc_direction, 0.0f, 1.0f);
    rhi_cmd_bind_texture(cmd, pp->fbo_pong.color_tex, pp->sampler, 0);
    rhi_cmd_draw(cmd, 3, 1);

    rhi_offscreen_fbo_bind(cmd, &pp->fbo_composite);
    rhi_cmd_bind_pipeline(cmd, pp->composite_pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures — rhi_cmd_bind_texture ignores
     * the unit parameter in VK and binds all 9 slots to one texture. */
    rhi_cmd_bind_material_textures(cmd, scene_color, scene_color, scene_color,
                                   scene_color, pp->fbo_ping.color_tex, scene_color, pp->sampler);
    if (pp->loc_bloom_strength >= 0) rhi_cmd_set_uniform_f32(cmd, pp->loc_bloom_strength, pp->bloom_strength);
    rhi_cmd_draw(cmd, 3, 1);

    /* R196-B: skip intermediate swapchain CLEAR unbind. */
}

RHITexture post_process_get_bloom_texture(PostProcess *pp) {
    if (!pp->ready) return RHI_HANDLE_NULL;
    if (rhi_handle_valid(pp->fbo_composite.fb)) return pp->fbo_composite.color_tex;
    return pp->fbo_ping.color_tex;
}
