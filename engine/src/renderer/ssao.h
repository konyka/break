#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      ssao_pipe;
    RHIPipeline      blur_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  ssao_fbo;
    RHIOffscreenFBO  blur_fbo;
    i32              loc_proj;
    i32              loc_inv_proj;
    i32              loc_screen_w;
    i32              loc_screen_h;
    i32              loc_radius;
    i32              loc_bias;
    f32              radius;
    f32              bias;
    bool             ready;
} SSAOSystem;

bool ssao_init(SSAOSystem *ssao, RHIDevice *dev, u32 width, u32 height);
void ssao_shutdown(SSAOSystem *ssao);
void ssao_apply(SSAOSystem *ssao, RHICmdBuffer *cmd, RHITexture depth_tex,
                const f32 *proj, const f32 *inv_proj, u32 screen_w, u32 screen_h);
RHITexture ssao_get_texture(SSAOSystem *ssao);
