#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    /* 计划 E Task 5 T1：反射物化表，loc_* 缓存的查询来源。 */
    RHIPipelineBindings *bind_pipe;
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
/* FS3: recreate only the size-dependent render targets; pipelines, bindings,
 * samplers and uniform locations are kept. On failure the previous targets
 * stay live and false is returned (the caller falls back to shutdown+init). */
bool debug_viz_resize(DebugVizSystem *s, RHIDevice *dev, u32 w, u32 h);
void debug_viz_shutdown(DebugVizSystem *s);
void debug_viz_apply(DebugVizSystem *s, RHICmdBuffer *cmd,
                     RHITexture input_tex, RHITexture depth_tex,
                     i32 mode, f32 near_plane, f32 far_plane,
                     const f32 *cascade_splits, u32 w, u32 h);
