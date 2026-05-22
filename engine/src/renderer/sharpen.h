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
    bool ready;
} SharpenSystem;

bool sharpen_init(SharpenSystem *s, RHIDevice *dev, u32 w, u32 h);
void sharpen_shutdown(SharpenSystem *s);
void sharpen_apply(SharpenSystem *s, RHICmdBuffer *cmd,
                   RHITexture input_tex, f32 strength,
                   u32 w, u32 h);
