#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      cine_pipe;
    RHISampler       sampler;
    i32              loc_aberration;
    i32              loc_vignette;
    i32              loc_grain;
    i32              loc_time;
    i32              loc_screen_w;
    i32              loc_screen_h;
    f32              aberration;
    f32              vignette;
    f32              grain;
    bool             ready;
} CinematicSystem;

bool cinematic_init(CinematicSystem *cine, RHIDevice *dev);
void cinematic_shutdown(CinematicSystem *cine);
void cinematic_apply(CinematicSystem *cine, RHICmdBuffer *cmd, RHITexture input_tex,
                     u32 screen_w, u32 screen_h, f32 time);
