#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      tm_pipe;
    RHIPipeline      lum_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  lum_fbo;
    i32              loc_exposure;
    i32              loc_gamma;
    i32              loc_aberration;
    i32              loc_vignette;
    i32              loc_grain;
    i32              loc_time;
    i32              loc_screen_w;
    i32              loc_screen_h;
    i32              loc_saturation;
    i32              loc_contrast;
    i32              loc_brightness;
    i32              loc_temperature;
    i32              loc_tint;
    f32              exposure;
    f32              gamma;
    f32              aberration;
    f32              vignette;
    f32              grain;
    f32              saturation;
    f32              contrast;
    f32              brightness;
    f32              temperature;
    f32              tint;
    f32              min_exposure;
    f32              max_exposure;
    f32              adaptation_speed;
    f32              current_luma;
    bool             auto_exposure;
    bool             ready;
} TonemapSystem;

bool tonemap_init(TonemapSystem *tm, RHIDevice *dev);
void tonemap_shutdown(TonemapSystem *tm);
void tonemap_apply(TonemapSystem *tm, RHICmdBuffer *cmd,
                   RHITexture hdr_tex, u32 screen_w, u32 screen_h, f32 time, f32 dt);
void tonemap_update_auto_exposure(TonemapSystem *tm, RHICmdBuffer *cmd,
                                   RHITexture hdr_tex, f32 dt);
