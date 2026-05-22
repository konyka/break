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
    i32 loc_max_dist;
    bool ready;
} SSSSystem;

bool sss_init(SSSSystem *s, RHIDevice *dev, u32 w, u32 h);
void sss_shutdown(SSSSystem *s);
void sss_apply(SSSSystem *s, RHICmdBuffer *cmd,
               RHITexture color_tex, RHITexture depth_tex,
               f32 strength, f32 max_dist, u32 w, u32 h);
