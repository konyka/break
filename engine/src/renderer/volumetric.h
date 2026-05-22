#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      vol_pipe;
    RHIOffscreenFBO  vol_fbo;
    RHISampler       sampler;
    i32              loc_inv_proj;
    i32              loc_view;
    i32              loc_ldx;
    i32              loc_ldy;
    i32              loc_ldz;
    i32              loc_lcx;
    i32              loc_lcy;
    i32              loc_lcz;
    i32              loc_fog_density;
    i32              loc_fog_color_r;
    i32              loc_fog_color_g;
    i32              loc_fog_color_b;
    i32              loc_screen_w;
    i32              loc_screen_h;
    f32              fog_density;
    f32              fog_color[3];
    bool             ready;
} VolumetricSystem;

bool volumetric_init(VolumetricSystem *vol, RHIDevice *dev, u32 width, u32 height);
void volumetric_shutdown(VolumetricSystem *vol);
void volumetric_apply(VolumetricSystem *vol, RHICmdBuffer *cmd,
                      RHITexture depth_tex, RHITexture shadow_tex,
                      const f32 *inv_proj, const f32 *view,
                      const f32 *light_dir, const f32 *light_color,
                      u32 screen_w, u32 screen_h);
RHITexture volumetric_get_texture(VolumetricSystem *vol);
