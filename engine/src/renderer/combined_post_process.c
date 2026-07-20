#include "combined_post_process.h"
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================
 * Helper: read shader file
 * ======================================================================== */
static char *cpp_read_file(const char *path, usize *out_len) {
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

static RHIPipeline cpp_create_pipe(RHIDevice *dev,
                                    const char *vert_path, const char *frag_path,
                                    bool combined_aa, bool combined_color) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = cpp_read_file(vert_path, &vs_len);
    char *fs_src = cpp_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
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
        /* Dedicated VK push-constant layouts (ignored by GL). */
        .combined_aa_layout = combined_aa,
        .combined_color_layout = combined_color,
        /* These passes write into an R16G16B16A16_SFLOAT offscreen FBO. */
        .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT,
    };
    RHIPipeline pipe = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

static RHISampler cpp_create_sampler(RHIDevice *dev) {
    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    return rhi_sampler_create(dev, &sdesc);
}

/* ========================================================================
 * CombinedAA Implementation
 * ======================================================================== */

bool combined_aa_init(CombinedAA *caa, RHIDevice *dev, u32 width, u32 height) {
    if (!caa || !dev) return false;
    memset(caa, 0, sizeof(*caa));
    caa->device = dev;

    /* Try loading combined TAA+FXAA shader */
#ifdef ENGINE_VULKAN
    caa->combined_pipe = cpp_create_pipe(dev,
        "shaders/post_vk.vert", "shaders/combined_taa_fxaa_vk.frag", true, false);
#else
    caa->combined_pipe = cpp_create_pipe(dev,
        "shaders/post.vert", "shaders/combined_taa_fxaa.frag", true, false);
#endif

    if (rhi_handle_valid(caa->combined_pipe)) {
        caa->use_combined = true;
        caa->sampler = cpp_create_sampler(dev);
        caa->history_fbo[0] = rhi_offscreen_fbo_create_fmt(dev, width, height,
            RHI_FORMAT_R16G16B16A16_SFLOAT);
        caa->history_fbo[1] = rhi_offscreen_fbo_create_fmt(dev, width, height,
            RHI_FORMAT_R16G16B16A16_SFLOAT);
        caa->history_idx = 0;
        caa->first_frame = true;

        /* Cache uniform locations */
        caa->loc_curr_tex      = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_curr_tex");
        caa->loc_hist_tex      = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_hist_tex");
        caa->loc_depth_tex     = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_depth");
        caa->loc_curr_vp       = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_curr_vp");
        caa->loc_prev_vp       = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_prev_vp");
        caa->loc_inv_proj      = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_inv_proj");
        caa->loc_screen_w      = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_screen_w");
        caa->loc_screen_h      = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_screen_h");
        caa->loc_taa_blend     = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_blend");
        caa->loc_taa_first_frame = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_first_frame");
        caa->loc_fxaa_threshold = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_fxaa_threshold");
        caa->loc_use_velocity   = rhi_pipeline_get_uniform_location(dev, caa->combined_pipe, "u_taa_use_velocity");

        caa->ready = true;
        LOG_INFO("CombinedAA: combined TAA+FXAA pipeline active (%ux%u)", width, height);
        return true;
    }

    /* Fallback: initialize individual systems with optimized chaining */
    LOG_INFO("CombinedAA: combined shader not found, using optimized fallback chain");
    caa->use_combined = false;

    bool ok = true;
    ok = fxaa_init(&caa->fxaa, dev, width, height) && ok;
    ok = taa_init(&caa->taa, dev, width, height) && ok;

    /* Create shared output FBO for chaining without extra FBO switches */
    caa->sampler = cpp_create_sampler(dev);
    caa->output_fbo = rhi_offscreen_fbo_create_fmt(dev, width, height,
        RHI_FORMAT_R16G16B16A16_SFLOAT);

    caa->ready = ok;
    if (ok) LOG_INFO("CombinedAA: fallback chain initialized (%ux%u)", width, height);
    return ok;
}

void combined_aa_shutdown(CombinedAA *caa) {
    if (!caa->device) return;
    if (caa->use_combined) {
        if (rhi_handle_valid(caa->combined_pipe)) rhi_pipeline_destroy(caa->device, caa->combined_pipe);
        for (int i = 0; i < 2; i++) {
            if (rhi_handle_valid(caa->history_fbo[i].fb))
                rhi_offscreen_fbo_destroy(caa->device, &caa->history_fbo[i]);
        }
    } else {
        fxaa_shutdown(&caa->fxaa);
        taa_shutdown(&caa->taa);
        if (rhi_handle_valid(caa->output_fbo.fb))
            rhi_offscreen_fbo_destroy(caa->device, &caa->output_fbo);
    }
    if (rhi_handle_valid(caa->sampler)) rhi_sampler_destroy(caa->device, caa->sampler);
    caa->ready = false;
}

void combined_aa_apply(CombinedAA *caa, RHICmdBuffer *cmd,
                       RHITexture current_color, RHITexture depth_tex,
                       RHITexture velocity_tex,
                       const f32 *curr_vp, const f32 *prev_vp,
                       const f32 *inv_proj, u32 screen_w, u32 screen_h) {
    if (!caa->ready) return;

    if (caa->use_combined) {
        int write_idx = caa->history_idx;
        int read_idx = 1 - caa->history_idx;

        rhi_cmd_end_render_pass(cmd);
        rhi_offscreen_fbo_bind(cmd, &caa->history_fbo[write_idx]);
        rhi_cmd_bind_pipeline(cmd, caa->combined_pipe);

        bool use_vel = rhi_handle_valid(velocity_tex);
        RHITexture hist_tex = caa->first_frame ? current_color
                                               : caa->history_fbo[read_idx].color_tex;
        RHITexture tex[4] = { current_color, hist_tex, depth_tex, velocity_tex };
        rhi_cmd_bind_textures_multi(cmd, tex, use_vel ? 4 : 3, caa->sampler);

        /* Set all uniforms in batch */
        if (caa->loc_curr_vp >= 0 && curr_vp)
            rhi_cmd_set_uniform_mat4(cmd, caa->loc_curr_vp, curr_vp);
        if (caa->loc_prev_vp >= 0 && prev_vp)
            rhi_cmd_set_uniform_mat4(cmd, caa->loc_prev_vp, prev_vp);
        if (caa->loc_inv_proj >= 0 && inv_proj)
            rhi_cmd_set_uniform_mat4(cmd, caa->loc_inv_proj, inv_proj);
        if (caa->loc_screen_w >= 0)
            rhi_cmd_set_uniform_f32(cmd, caa->loc_screen_w, (f32)screen_w);
        if (caa->loc_screen_h >= 0)
            rhi_cmd_set_uniform_f32(cmd, caa->loc_screen_h, (f32)screen_h);
        if (caa->loc_taa_blend >= 0)
            rhi_cmd_set_uniform_f32(cmd, caa->loc_taa_blend, 0.1f);
        if (caa->loc_taa_first_frame >= 0)
            rhi_cmd_set_uniform_f32(cmd, caa->loc_taa_first_frame, caa->first_frame ? 1.0f : 0.0f);
        if (caa->loc_fxaa_threshold >= 0)
            rhi_cmd_set_uniform_f32(cmd, caa->loc_fxaa_threshold, 0.0312f);
        if (caa->loc_use_velocity >= 0)
            rhi_cmd_set_uniform_f32(cmd, caa->loc_use_velocity, use_vel ? 1.0f : 0.0f);

        rhi_cmd_draw(cmd, 3, 1);
        /* R196-B: skip intermediate swapchain CLEAR unbind. */

        caa->history_idx = read_idx;
        caa->first_frame = false;
        return;
    }

    /* Optimized fallback: chain TAA -> FXAA with minimal FBO switches
     *
     * Original flow (separate systems):
     *   TAA:  end_render_pass -> bind FBO -> bind pipe -> draw -> unbind FBO
     *   FXAA: bind FBO -> bind pipe -> draw
     *
     * Optimized flow:
     *   TAA:  end_render_pass -> bind FBO -> bind pipe -> draw (keep pass open)
     *   FXAA: bind output FBO -> bind pipe -> draw
     *
     * Saves: 1 FBO unbind + 1 render pass end/start cycle
     */
    taa_resolve(&caa->taa, cmd, current_color, depth_tex, velocity_tex,
                curr_vp, prev_vp, inv_proj, screen_w, screen_h);

    /* TAA output is in history_fbo, feed it to FXAA writing to our output FBO */
    RHITexture taa_out = taa_get_output(&caa->taa);
    rhi_offscreen_fbo_bind(cmd, &caa->output_fbo);
    fxaa_apply(&caa->fxaa, cmd, taa_out, screen_w, screen_h);
}

RHITexture combined_aa_get_output(CombinedAA *caa) {
    if (!caa->ready) return RHI_HANDLE_NULL;
    if (caa->use_combined)
        return caa->history_fbo[1 - caa->history_idx].color_tex;
    /* In fallback mode, FXAA writes to its own FBO */
    return fxaa_get_texture(&caa->fxaa);
}

/* ========================================================================
 * CombinedColor Implementation
 * ======================================================================== */

bool combined_color_init(CombinedColor *cc, RHIDevice *dev, u32 width, u32 height) {
    if (!cc || !dev) return false;
    memset(cc, 0, sizeof(*cc));
    cc->device = dev;

    /* Try loading combined tonemap+colorgrade+cinematic shader */
#ifdef ENGINE_VULKAN
    cc->combined_pipe = cpp_create_pipe(dev,
        "shaders/post_vk.vert", "shaders/combined_color_vk.frag", false, true);
#else
    cc->combined_pipe = cpp_create_pipe(dev,
        "shaders/post.vert", "shaders/combined_color.frag", false, true);
#endif

    if (rhi_handle_valid(cc->combined_pipe)) {
        cc->use_combined = true;
        cc->sampler = cpp_create_sampler(dev);
        cc->output_fbo = rhi_offscreen_fbo_create_fmt(dev, width, height,
            RHI_FORMAT_R16G16B16A16_SFLOAT);

        /* Cache all uniform locations */
        cc->loc_exposure    = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_tm_exposure");
        cc->loc_gamma       = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_tm_gamma");
        cc->loc_mode        = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_tm_mode");
        cc->loc_saturation  = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cg_saturation");
        cc->loc_contrast    = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cg_contrast");
        cc->loc_brightness  = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cg_brightness");
        cc->loc_temperature = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cg_temperature");
        cc->loc_tint        = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cg_tint");
        cc->loc_aberration  = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cine_aberration");
        cc->loc_vignette    = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cine_vignette");
        cc->loc_grain       = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cine_grain");
        cc->loc_time        = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_cine_time");
        cc->loc_screen_w    = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_screen_w");
        cc->loc_screen_h    = rhi_pipeline_get_uniform_location(dev, cc->combined_pipe, "u_screen_h");

        cc->ready = true;
        LOG_INFO("CombinedColor: combined tonemap+colorgrade+cinematic pipeline active (%ux%u)", width, height);
        return true;
    }

    /* Fallback: initialize individual systems with optimized chaining */
    LOG_INFO("CombinedColor: combined shader not found, using optimized fallback chain");
    cc->use_combined = false;

    bool ok = true;
    ok = tonemap_init(&cc->tonemap, dev) && ok;
    ok = color_grade_init(&cc->color_grade, dev, width, height) && ok;
    ok = cinematic_init(&cc->cinematic, dev) && ok;

    cc->sampler = cpp_create_sampler(dev);
    cc->output_fbo = rhi_offscreen_fbo_create_fmt(dev, width, height,
        RHI_FORMAT_R16G16B16A16_SFLOAT);

    cc->ready = ok;
    if (ok) LOG_INFO("CombinedColor: fallback chain initialized (%ux%u)", width, height);
    return ok;
}

void combined_color_shutdown(CombinedColor *cc) {
    if (!cc->device) return;
    if (cc->use_combined) {
        if (rhi_handle_valid(cc->combined_pipe))
            rhi_pipeline_destroy(cc->device, cc->combined_pipe);
    } else {
        tonemap_shutdown(&cc->tonemap);
        color_grade_shutdown(&cc->color_grade);
        cinematic_shutdown(&cc->cinematic);
    }
    if (rhi_handle_valid(cc->output_fbo.fb)) rhi_offscreen_fbo_destroy(cc->device, &cc->output_fbo);
    if (rhi_handle_valid(cc->sampler)) rhi_sampler_destroy(cc->device, cc->sampler);
    cc->ready = false;
}

void combined_color_apply(CombinedColor *cc, RHICmdBuffer *cmd,
                          RHITexture hdr_tex, RHITexture lum_tex, bool auto_exposure,
                          f32 exposure, f32 gamma, i32 tonemap_mode,
                          f32 saturation, f32 contrast, f32 brightness,
                          f32 temperature, f32 tint,
                          f32 aberration, f32 vignette, f32 grain,
                          f32 time, u32 screen_w, u32 screen_h) {
    if (!cc->ready) return;

    if (cc->use_combined) {
        /* Single combined draw: tonemap + color grade + cinematic */
        rhi_offscreen_fbo_bind(cmd, &cc->output_fbo);
        rhi_cmd_bind_pipeline(cmd, cc->combined_pipe);
        /* R271: bind the 1x1 adapted-luminance texture at binding 1 exactly like
         * tonemap_apply so combined_color.frag can apply auto-exposure. When auto
         * is off (or no lum texture) bind only the HDR source, matching the
         * separate tonemap pass. */
        if (auto_exposure && rhi_handle_valid(lum_tex)) {
            rhi_cmd_bind_material_textures(cmd, hdr_tex, hdr_tex, hdr_tex,
                                           hdr_tex, lum_tex, hdr_tex, cc->sampler);
        } else {
            rhi_cmd_bind_texture(cmd, hdr_tex, cc->sampler, 0);
        }

        if (cc->loc_exposure >= 0)    rhi_cmd_set_uniform_f32(cmd, cc->loc_exposure, exposure);
        if (cc->loc_gamma >= 0)       rhi_cmd_set_uniform_f32(cmd, cc->loc_gamma, gamma);
        if (cc->loc_mode >= 0)        rhi_cmd_set_uniform_i32(cmd, cc->loc_mode, tonemap_mode);
        if (cc->loc_saturation >= 0)  rhi_cmd_set_uniform_f32(cmd, cc->loc_saturation, saturation);
        if (cc->loc_contrast >= 0)    rhi_cmd_set_uniform_f32(cmd, cc->loc_contrast, contrast);
        if (cc->loc_brightness >= 0)  rhi_cmd_set_uniform_f32(cmd, cc->loc_brightness, brightness);
        if (cc->loc_temperature >= 0) rhi_cmd_set_uniform_f32(cmd, cc->loc_temperature, temperature);
        if (cc->loc_tint >= 0)        rhi_cmd_set_uniform_f32(cmd, cc->loc_tint, tint);
        if (cc->loc_aberration >= 0)  rhi_cmd_set_uniform_f32(cmd, cc->loc_aberration, aberration);
        if (cc->loc_vignette >= 0)    rhi_cmd_set_uniform_f32(cmd, cc->loc_vignette, vignette);
        if (cc->loc_grain >= 0)       rhi_cmd_set_uniform_f32(cmd, cc->loc_grain, grain);
        if (cc->loc_time >= 0)        rhi_cmd_set_uniform_f32(cmd, cc->loc_time, time);
        if (cc->loc_screen_w >= 0)    rhi_cmd_set_uniform_f32(cmd, cc->loc_screen_w, (f32)screen_w);
        if (cc->loc_screen_h >= 0)    rhi_cmd_set_uniform_f32(cmd, cc->loc_screen_h, (f32)screen_h);

        rhi_cmd_draw(cmd, 3, 1);
        /* R196-B: skip intermediate swapchain CLEAR unbind. */
        return;
    }

    /* Optimized fallback chain:
     * tonemap -> color_grade -> cinematic
     *
     * Original: 3 separate FBO bind/unbind cycles + 3 pipeline switches
     * Optimized: chain with minimal FBO transitions
     *   tonemap writes to its internal FBO (for luminance tracking)
     *   color_grade reads tonemap output, writes to its FBO
     *   cinematic reads color_grade output, writes to our output FBO
     */

    cc->tonemap.exposure = exposure;
    cc->tonemap.gamma = gamma;
    cc->tonemap.mode = tonemap_mode;

    /* Step 1: Tonemap (writes to default framebuffer, we capture it) */
    rhi_offscreen_fbo_bind(cmd, &cc->output_fbo);
    tonemap_apply(&cc->tonemap, cmd, hdr_tex, screen_w, screen_h);

    /* Step 2: Color grade on tonemap output */
    RHITexture tm_out = cc->output_fbo.color_tex;
    color_grade_apply(&cc->color_grade, cmd, tm_out,
                      saturation, contrast, brightness, temperature, tint,
                      screen_w, screen_h);

    /* Step 3: Cinematic on color grade output -> our output FBO */
    RHITexture cg_out = cc->color_grade.fbo.color_tex;
    rhi_offscreen_fbo_bind(cmd, &cc->output_fbo);
    cinematic_apply(&cc->cinematic, cmd, cg_out, screen_w, screen_h, time);

    /* R196-B: skip intermediate swapchain CLEAR unbind. */
}

RHITexture combined_color_get_output(CombinedColor *cc) {
    if (!cc->ready) return RHI_HANDLE_NULL;
    return cc->output_fbo.color_tex;
}
