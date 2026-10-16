#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    /* 计划 E Task 5 T1：反射物化表，loc_ 系列缓存的查询来源。 */
    RHIPipelineBindings *bind_pipe;
    RHIOffscreenFBO fbo;
    RHISampler sampler;
    i32 loc_sun_x;
    i32 loc_sun_y;
    i32 loc_intensity;
    i32 loc_sw;
    i32 loc_sh;
    bool ready;
} GodRaysSystem;

bool god_rays_init(GodRaysSystem *s, RHIDevice *dev, u32 w, u32 h);
void god_rays_shutdown(GodRaysSystem *s);
void god_rays_apply(GodRaysSystem *s, RHICmdBuffer *cmd,
                    RHITexture scene_tex, RHITexture depth_tex,
                    f32 sun_x, f32 sun_y, f32 intensity,
                    u32 w, u32 h);
