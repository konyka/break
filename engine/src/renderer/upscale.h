#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHIOffscreenFBO history[2];
    i32 history_idx;
    RHISampler sampler;
    i32 loc_rw;
    i32 loc_rh;
    i32 loc_dw;
    i32 loc_dh;
    i32 loc_sharp;
    i32 loc_inv_proj;
    i32 loc_prev_vp;
    bool ready;
} UpscaleSystem;

bool upscale_init(UpscaleSystem *s, RHIDevice *dev, u32 render_w, u32 render_h, u32 display_w, u32 display_h);
void upscale_shutdown(UpscaleSystem *s);
void upscale_apply(UpscaleSystem *s, RHICmdBuffer *cmd,
                   RHITexture input_tex, RHITexture depth_tex,
                   const f32 *inv_proj, const f32 *prev_vp,
                   f32 sharpness,
                   u32 render_w, u32 render_h, u32 display_w, u32 display_h);
