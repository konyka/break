#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline h_pipe;
    RHIPipeline v_pipe;
    /* 计划 E Task 5 T1：反射物化表，loc_ 与 v_loc_ 缓存的查询来源。 */
    RHIPipelineBindings *bind_h;
    RHIPipelineBindings *bind_v;
    RHIOffscreenFBO fbo;
    RHIOffscreenFBO blur_fbo;
    RHISampler sampler;
    i32 loc_strength;
    i32 loc_sw;
    i32 loc_sh;
    i32 loc_max_dist;
    i32 v_loc_strength;
    i32 v_loc_sw;
    i32 v_loc_sh;
    i32 v_loc_max_dist;
    bool ready;
} SSSSystem;

bool sss_init(SSSSystem *s, RHIDevice *dev, u32 w, u32 h);
void sss_shutdown(SSSSystem *s);
void sss_apply(SSSSystem *s, RHICmdBuffer *cmd,
               RHITexture color_tex, RHITexture depth_tex,
               f32 strength, f32 max_dist, u32 w, u32 h);
