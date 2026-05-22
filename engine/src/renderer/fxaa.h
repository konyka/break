#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      fxaa_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  fxaa_fbo;
    i32              loc_screen_w;
    i32              loc_screen_h;
    bool             ready;
} FXAASystem;

bool fxaa_init(FXAASystem *fxaa, RHIDevice *dev, u32 width, u32 height);
void fxaa_shutdown(FXAASystem *fxaa);
void fxaa_apply(FXAASystem *fxaa, RHICmdBuffer *cmd,
                RHITexture input_tex, u32 screen_w, u32 screen_h);
RHITexture fxaa_get_texture(FXAASystem *fxaa);
