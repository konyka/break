#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHISampler sampler;
    i32 loc_mode;
    i32 loc_near;
    i32 loc_far;
    i32 loc_split0;
    i32 loc_split1;
    i32 loc_split2;
    i32 loc_split3;
    bool ready;
} DebugVizSystem;

bool debug_viz_init(DebugVizSystem *s, RHIDevice *dev, u32 w, u32 h);
void debug_viz_shutdown(DebugVizSystem *s);
void debug_viz_apply(DebugVizSystem *s, RHICmdBuffer *cmd,
                     RHITexture input_tex, RHITexture depth_tex,
                     i32 mode, f32 near_plane, f32 far_plane,
                     const f32 *cascade_splits, u32 w, u32 h);
