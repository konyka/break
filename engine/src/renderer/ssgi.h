#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      ssgi_pipe;
    RHIPipeline      ssgi_blur_pipe;
    /* 计划 E Task 5 T1：反射物化表，loc_* 缓存的查询来源。 */
    RHIPipelineBindings *bind_pipe;
    RHIPipelineBindings *bind_blur;
    RHISampler       sampler;
    RHIOffscreenFBO  ssgi_fbo;
    RHIOffscreenFBO  ssgi_blur_fbo;
    i32              loc_inv_proj;
    i32              loc_proj;
    i32              loc_radius;
    i32              loc_intensity;
    i32              loc_screen_w;
    i32              loc_screen_h;
    i32              loc_blur_dir_x;
    i32              loc_blur_dir_y;
    f32              radius;
    f32              intensity;
    bool             ready;
} SSGISystem;

bool ssgi_init(SSGISystem *ssgi, RHIDevice *dev, u32 width, u32 height);
/* FS3: recreate only the size-dependent render targets; pipelines, bindings,
 * samplers and uniform locations are kept. On failure the previous targets
 * stay live and false is returned (the caller falls back to shutdown+init). */
bool ssgi_resize(SSGISystem *s, RHIDevice *dev, u32 w, u32 h);
void ssgi_shutdown(SSGISystem *ssgi);
/* R550-A: color_tex is both the GI source and the incoming frame-chain
 * color; the final blur stage self-composites (scene + blurred GI) into
 * ssgi_blur_fbo, which becomes the new chain tail (god_rays idiom). */
void ssgi_apply(SSGISystem *ssgi, RHICmdBuffer *cmd,
                RHITexture depth_tex, RHITexture color_tex,
                const f32 *inv_proj, const f32 *proj,
                u32 screen_w, u32 screen_h);
RHITexture ssgi_get_texture(SSGISystem *ssgi);
