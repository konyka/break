#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      tm_pipe;
    RHIPipeline      lum_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  lum_fbo[2];
    i32              lum_idx;
    i32              loc_exposure;
    i32              loc_gamma;
    i32              loc_mode;
    i32              loc_tm_lum;
    i32              loc_lum_w;
    i32              loc_lum_h;
    i32              loc_lum_speed;
    i32              loc_lum_dt;
    i32              loc_lum_tex;
    i32              loc_lum_prev;
    f32              exposure;
    f32              gamma;
    i32              mode;
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
                   RHITexture hdr_tex, u32 screen_w, u32 screen_h);
void tonemap_update_auto_exposure(TonemapSystem *tm, RHICmdBuffer *cmd,
                                   RHITexture hdr_tex, u32 screen_w, u32 screen_h, f32 dt);
