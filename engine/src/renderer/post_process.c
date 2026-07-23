#include <renderer/post_process.h>
#include <core/log.h>
#include <math/math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *pp_read_file(const char *path, usize *out_len) {
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

static RHIPipeline pp_create_pipe(RHIDevice *dev,
                                   const char *vert_path, const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = pp_read_file(vert_path, &vs_len);
    char *fs_src = pp_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("PostProcess: shaders not found (%s)", frag_path);
        free(vs_src); free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

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

bool post_process_init(PostProcess *pp, RHIDevice *dev, u32 width, u32 height) {
    memset(pp, 0, sizeof(*pp));
    pp->device = dev;
    pp->bloom_strength = 0.4f;
    pp->threshold = 1.0f;

    pp->extract_pipe = pp_create_pipe(dev,
#ifdef ENGINE_VULKAN
        "shaders/post_vk.vert", "shaders/bloom_extract_vk.frag");
#else
        "shaders/post.vert", "shaders/bloom_extract.frag");
#endif
    if (!rhi_handle_valid(pp->extract_pipe)) {
        LOG_WARN("PostProcess: extract pipeline failed");
        return false;
    }

    pp->blur_pipe = pp_create_pipe(dev,
#ifdef ENGINE_VULKAN
        "shaders/post_vk.vert", "shaders/bloom_blur_vk.frag");
#else
        "shaders/post.vert", "shaders/bloom_blur.frag");
#endif
    if (!rhi_handle_valid(pp->blur_pipe)) {
        LOG_WARN("PostProcess: blur pipeline failed");
        return false;
    }

    pp->tex_pipe = pp_create_pipe(dev,
#ifdef ENGINE_VULKAN
        "shaders/post_vk.vert", "shaders/post_tex_vk.frag");
#else
        "shaders/post.vert", "shaders/post_tex.frag");
#endif
    if (!rhi_handle_valid(pp->tex_pipe)) {
        LOG_WARN("PostProcess: tex pipeline failed");
        return false;
    }

    pp->composite_pipe = pp_create_pipe(dev,
#ifdef ENGINE_VULKAN
        "shaders/post_vk.vert", "shaders/bloom_composite_vk.frag");
#else
        "shaders/post.vert", "shaders/bloom_composite.frag");
#endif
    if (!rhi_handle_valid(pp->composite_pipe)) {
        LOG_WARN("PostProcess: composite pipeline failed");
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
        return false;
    }

    u32 pw = width / 2;
    u32 ph = height / 2;
    if (pw < 1) pw = 1;
    if (ph < 1) ph = 1;

    pp->fbo_ping = rhi_offscreen_fbo_create_fmt(dev, pw, ph, RHI_FORMAT_R16G16B16A16_SFLOAT);
    pp->fbo_pong = rhi_offscreen_fbo_create_fmt(dev, pw, ph, RHI_FORMAT_R16G16B16A16_SFLOAT);
    pp->fbo_composite = rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_R16G16B16A16_SFLOAT);
    /* R349: composite is the apply target — include it in the readiness gate. */
    if (!rhi_handle_valid(pp->fbo_ping.fb) || !rhi_handle_valid(pp->fbo_pong.fb) ||
        !rhi_handle_valid(pp->fbo_composite.fb)) {
        LOG_WARN("PostProcess: FBO creation failed");
        post_process_shutdown(pp);
        return false;
    }

    pp->loc_bloom_strength = rhi_pipeline_get_uniform_location(dev, pp->composite_pipe, "u_bloom_strength");
    pp->loc_threshold = rhi_pipeline_get_uniform_location(dev, pp->extract_pipe, "u_threshold");
    pp->loc_direction = rhi_pipeline_get_uniform_location(dev, pp->blur_pipe, "u_direction");

    LOG_INFO("PostProcess: bloom initialized (%ux%u)", pw, ph);
    pp->ready = true;
    return true;
}

void post_process_shutdown(PostProcess *pp) {
    if (!pp->device) return;
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

    rhi_cmd_bind_pipeline(cmd, pp->extract_pipe);
    if (pp->loc_threshold >= 0) rhi_cmd_set_uniform_f32(cmd, pp->loc_threshold, pp->threshold);
    rhi_cmd_bind_texture(cmd, scene_color, pp->sampler, 0);
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_ping);
    rhi_cmd_draw(cmd, 3, 1);

    rhi_cmd_bind_pipeline(cmd, pp->blur_pipe);

    if (pp->loc_direction >= 0) rhi_cmd_set_uniform_vec2(cmd, pp->loc_direction, 1.0f, 0.0f);
    rhi_cmd_bind_texture(cmd, pp->fbo_ping.color_tex, pp->sampler, 0);
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_pong);
    rhi_cmd_draw(cmd, 3, 1);

    if (pp->loc_direction >= 0) rhi_cmd_set_uniform_vec2(cmd, pp->loc_direction, 0.0f, 1.0f);
    rhi_cmd_bind_texture(cmd, pp->fbo_pong.color_tex, pp->sampler, 0);
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_ping);
    rhi_cmd_draw(cmd, 3, 1);

    if (pp->loc_direction >= 0) rhi_cmd_set_uniform_vec2(cmd, pp->loc_direction, 1.0f, 0.0f);
    rhi_cmd_bind_texture(cmd, pp->fbo_ping.color_tex, pp->sampler, 0);
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_pong);
    rhi_cmd_draw(cmd, 3, 1);

    if (pp->loc_direction >= 0) rhi_cmd_set_uniform_vec2(cmd, pp->loc_direction, 0.0f, 1.0f);
    rhi_cmd_bind_texture(cmd, pp->fbo_pong.color_tex, pp->sampler, 0);
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_ping);
    rhi_cmd_draw(cmd, 3, 1);

    rhi_cmd_bind_pipeline(cmd, pp->composite_pipe);
    /* R99-2: Use rhi_cmd_bind_material_textures — rhi_cmd_bind_texture ignores
     * the unit parameter in VK and binds all 9 slots to one texture. */
    rhi_cmd_bind_material_textures(cmd, scene_color, scene_color, scene_color,
                                   scene_color, pp->fbo_ping.color_tex, scene_color, pp->sampler);
    if (pp->loc_bloom_strength >= 0) rhi_cmd_set_uniform_f32(cmd, pp->loc_bloom_strength, pp->bloom_strength);
    rhi_offscreen_fbo_bind(cmd, &pp->fbo_composite);
    rhi_cmd_draw(cmd, 3, 1);

    /* R196-B: skip intermediate swapchain CLEAR unbind. */
}

RHITexture post_process_get_bloom_texture(PostProcess *pp) {
    if (!pp->ready) return RHI_HANDLE_NULL;
    if (rhi_handle_valid(pp->fbo_composite.fb)) return pp->fbo_composite.color_tex;
    return pp->fbo_ping.color_tex;
}
