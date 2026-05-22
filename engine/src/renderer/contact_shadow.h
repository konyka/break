#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHISampler sampler;
    i32 loc_light_x;
    i32 loc_light_y;
    i32 loc_light_z;
    i32 loc_inv_proj;
    i32 loc_sw;
    i32 loc_sh;
    bool ready;
} ContactShadowSystem;

bool contact_shadow_init(ContactShadowSystem *s, RHIDevice *dev, u32 w, u32 h);
void contact_shadow_shutdown(ContactShadowSystem *s);
void contact_shadow_apply(ContactShadowSystem *s, RHICmdBuffer *cmd,
                          RHITexture depth_tex, const f32 *inv_proj,
                          f32 lx, f32 ly, f32 lz, u32 w, u32 h);
