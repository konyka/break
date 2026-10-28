#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      fxaa_pipe;
    /* 计划 E Task 5 T1：反射物化表，loc_ 系列缓存的查询来源。 */
    RHIPipelineBindings *bind_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  fxaa_fbo;
    i32              loc_screen_w;
    i32              loc_screen_h;
    i32              loc_threshold;
    f32              threshold;
    bool             ready;
} FXAASystem;

bool fxaa_init(FXAASystem *fxaa, RHIDevice *dev, u32 width, u32 height);
/* FS3: recreate only the size-dependent render targets; pipelines, bindings,
 * samplers and uniform locations are kept. On failure the previous targets
 * stay live and false is returned (the caller falls back to shutdown+init). */
bool fxaa_resize(FXAASystem *s, RHIDevice *dev, u32 w, u32 h);
void fxaa_shutdown(FXAASystem *fxaa);
void fxaa_apply(FXAASystem *fxaa, RHICmdBuffer *cmd,
                RHITexture input_tex, u32 screen_w, u32 screen_h);
RHITexture fxaa_get_texture(FXAASystem *fxaa);
