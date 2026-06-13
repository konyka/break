#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      resolve_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  history_fbo[2];
    i32              history_idx;
    i32              loc_curr_tex;
    i32              loc_hist_tex;
    i32              loc_depth_tex;
    i32              loc_curr_vp;
    i32              loc_prev_vp;
    i32              loc_inv_proj;
    i32              loc_screen_w;
    i32              loc_screen_h;
    i32              loc_blend;
    i32              loc_first_frame;
    i32              loc_use_velocity;
    bool             ready;
    bool             first_frame;
} TAASystem;

bool taa_init(TAASystem *taa, RHIDevice *dev, u32 width, u32 height);
void taa_shutdown(TAASystem *taa);
void taa_resolve(TAASystem *taa, RHICmdBuffer *cmd,
                 RHITexture current_color, RHITexture depth_tex,
                 RHITexture velocity_tex,
                 const f32 *curr_vp, const f32 *prev_vp,
                 const f32 *inv_proj, u32 screen_w, u32 screen_h);
RHITexture taa_get_output(TAASystem *taa);
