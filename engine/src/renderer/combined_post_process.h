#pragma once

#include <rhi/rhi.h>
#include "fxaa.h"
#include "taa.h"
#include "tonemap.h"
#include "color_grade.h"
#include "cinematic.h"

/*
 * Combined Post-Process Passes
 *
 * Reduces GPU overhead by merging related post-processing effects:
 *   1. CombinedAA:    FXAA + TAA in a single render pass (fewer FBO switches)
 *   2. CombinedColor: Tonemap + ColorGrade + Cinematic in a single pass
 *
 * Falls back to individual systems if combined init fails.
 */

/* ---- Combined Anti-Aliasing (FXAA + TAA) ---- */
typedef struct {
    RHIDevice       *device;
    /* Combined pipeline: TAA resolve -> FXAA in one render pass */
    RHIPipeline      combined_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  output_fbo;       /* fallback chain only */
    RHIOffscreenFBO  history_fbo[2]; /* combined path ping-pong */
    i32              history_idx;
    bool             first_frame;
    /* Uniform locations */
    i32              loc_curr_tex;
    i32              loc_hist_tex;
    i32              loc_depth_tex;
    i32              loc_curr_vp;
    i32              loc_prev_vp;
    i32              loc_inv_proj;
    i32              loc_screen_w;
    i32              loc_screen_h;
    i32              loc_taa_blend;
    i32              loc_taa_first_frame;
    i32              loc_fxaa_threshold;
    i32              loc_use_velocity;
    /* State */
    bool             ready;
    bool             use_combined;   /* true if combined pipe loaded */
    /* Sub-system fallbacks */
    FXAASystem       fxaa;
    TAASystem        taa;
} CombinedAA;

bool combined_aa_init(CombinedAA *caa, RHIDevice *dev, u32 width, u32 height);
void combined_aa_shutdown(CombinedAA *caa);
void combined_aa_apply(CombinedAA *caa, RHICmdBuffer *cmd,
                       RHITexture current_color, RHITexture depth_tex,
                       RHITexture velocity_tex,
                       const f32 *curr_vp, const f32 *prev_vp,
                       const f32 *inv_proj, u32 screen_w, u32 screen_h);
RHITexture combined_aa_get_output(CombinedAA *caa);

/* ---- Combined Color (Tonemap + ColorGrade + Cinematic) ---- */
typedef struct {
    RHIDevice       *device;
    /* Combined pipeline: tonemap -> color grade -> cinematic in one pass */
    RHIPipeline      combined_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  output_fbo;
    /* Uniform locations */
    i32              loc_exposure;
    i32              loc_gamma;
    i32              loc_mode;
    i32              loc_saturation;
    i32              loc_contrast;
    i32              loc_brightness;
    i32              loc_temperature;
    i32              loc_tint;
    i32              loc_aberration;
    i32              loc_vignette;
    i32              loc_grain;
    i32              loc_time;
    i32              loc_screen_w;
    i32              loc_screen_h;
    /* State */
    bool             ready;
    bool             use_combined;
    /* Sub-system fallbacks */
    TonemapSystem    tonemap;
    ColorGradeSystem color_grade;
    CinematicSystem  cinematic;
} CombinedColor;

bool combined_color_init(CombinedColor *cc, RHIDevice *dev, u32 width, u32 height);
void combined_color_shutdown(CombinedColor *cc);
/* R271: lum_tex + auto_exposure mirror tonemap_apply so the combined path
 * applies auto-exposure identically to the separate tonemap pass. Pass the
 * TonemapSystem's current lum_fbo[lum_idx].color_tex and its auto_exposure
 * flag; when auto is off (or lum_tex invalid) it falls back to fixed exposure. */
void combined_color_apply(CombinedColor *cc, RHICmdBuffer *cmd,
                          RHITexture hdr_tex, RHITexture lum_tex, bool auto_exposure,
                          f32 exposure, f32 gamma, i32 tonemap_mode,
                          f32 saturation, f32 contrast, f32 brightness,
                          f32 temperature, f32 tint,
                          f32 aberration, f32 vignette, f32 grain,
                          f32 time, u32 screen_w, u32 screen_h);
RHITexture combined_color_get_output(CombinedColor *cc);
