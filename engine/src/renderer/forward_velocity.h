#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice      *device;
    RHIPipeline     pipe;
    RHISampler      sampler;
    RHIOffscreenFBO fbo;
    i32             loc_inv_proj;
    i32             loc_curr_vp;
    i32             loc_prev_vp;
    bool            ready;
} ForwardVelocitySystem;

bool forward_velocity_init(ForwardVelocitySystem *sys, RHIDevice *dev, u32 w, u32 h);
void forward_velocity_shutdown(ForwardVelocitySystem *sys);
void forward_velocity_apply(ForwardVelocitySystem *sys, RHICmdBuffer *cmd,
                            RHITexture depth_tex,
                            const f32 *inv_proj, const f32 *curr_vp, const f32 *prev_vp,
                            u32 w, u32 h);
RHITexture forward_velocity_get_texture(ForwardVelocitySystem *sys);
