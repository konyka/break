#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      dof_pipe;
    RHIOffscreenFBO  dof_fbo;
    RHISampler       sampler;
    i32              loc_focus_dist;
    i32              loc_focus_range;
    i32              loc_near;
    i32              loc_far;
    i32              loc_screen_w;
    i32              loc_screen_h;
    f32              focus_dist;
    f32              focus_range;
    bool             ready;
} DOFSystem;

bool dof_init(DOFSystem *dof, RHIDevice *dev, u32 width, u32 height);
void dof_shutdown(DOFSystem *dof);
void dof_apply(DOFSystem *dof, RHICmdBuffer *cmd, RHITexture color_tex, RHITexture depth_tex,
               const f32 *inv_proj, u32 screen_w, u32 screen_h);
RHITexture dof_get_texture(DOFSystem *dof);
