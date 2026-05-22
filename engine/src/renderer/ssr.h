#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      ssr_pipe;
    RHIOffscreenFBO  ssr_fbo;
    RHISampler       sampler;
    i32              loc_proj;
    i32              loc_inv_proj;
    i32              loc_view;
    i32              loc_screen_w;
    i32              loc_screen_h;
    i32              loc_max_steps;
    i32              loc_stride;
    i32              loc_thickness;
    bool             ready;
} SSRSystem;

bool ssr_init(SSRSystem *ssr, RHIDevice *dev, u32 width, u32 height);
void ssr_shutdown(SSRSystem *ssr);
void ssr_apply(SSRSystem *ssr, RHICmdBuffer *cmd, RHITexture color_tex, RHITexture depth_tex,
               const f32 *proj, const f32 *inv_proj, const f32 *view, u32 screen_w, u32 screen_h);
RHITexture ssr_get_texture(SSRSystem *ssr);
