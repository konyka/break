#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      ssgi_pipe;
    RHIPipeline      ssgi_blur_pipe;
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
void ssgi_shutdown(SSGISystem *ssgi);
/* R550-A: color_tex is both the GI source and the incoming frame-chain
 * color; the final blur stage self-composites (scene + blurred GI) into
 * ssgi_blur_fbo, which becomes the new chain tail (god_rays idiom). */
void ssgi_apply(SSGISystem *ssgi, RHICmdBuffer *cmd,
                RHITexture depth_tex, RHITexture color_tex,
                const f32 *inv_proj, const f32 *proj,
                u32 screen_w, u32 screen_h);
RHITexture ssgi_get_texture(SSGISystem *ssgi);
