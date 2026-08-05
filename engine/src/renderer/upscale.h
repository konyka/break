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
    i32 loc_copy_only;
    i32 loc_inv_proj;
    i32 loc_prev_vp;
    /* R446: no first-frame guard existed — Pass 1 blended 85% of the
     * uninitialized history texture for the first ~18 frames after init/resize
     * (mix weight 0.15, 0.85^n decay). Bind the current input as its own
     * history on the first frame, same contract as taa_resolve. */
    bool first_frame;
    bool ready;
} UpscaleSystem;

bool upscale_init(UpscaleSystem *s, RHIDevice *dev, u32 render_w, u32 render_h, u32 display_w, u32 display_h);
void upscale_shutdown(UpscaleSystem *s);
void upscale_apply(UpscaleSystem *s, RHICmdBuffer *cmd,
                   RHITexture input_tex, RHITexture depth_tex,
                   const f32 *inv_proj, const f32 *prev_vp,
                   f32 sharpness,
                   u32 render_w, u32 render_h, u32 display_w, u32 display_h);
