#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHISampler sampler;
    i32 loc_strength;
    i32 loc_sw;
    i32 loc_sh;
    i32 loc_inv_proj;
    i32 loc_prev_vp;
    bool ready;
} MotionBlurSystem;

bool motion_blur_init(MotionBlurSystem *s, RHIDevice *dev, u32 w, u32 h);
void motion_blur_shutdown(MotionBlurSystem *s);
void motion_blur_apply(MotionBlurSystem *s, RHICmdBuffer *cmd,
                       RHITexture color_tex, RHITexture depth_tex,
                       const f32 *inv_proj, const f32 *prev_vp,
                       f32 strength, u32 w, u32 h);
