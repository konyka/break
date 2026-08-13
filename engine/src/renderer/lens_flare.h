#pragma once

#include <rhi/rhi.h>

typedef struct {
    RHIDevice       *device;
    RHIPipeline      lf_pipe;
    RHISampler       sampler;
    RHIOffscreenFBO  lf_fbo;
    i32              loc_light_x;
    i32              loc_light_y;
    i32              loc_intensity;
    i32              loc_screen_w;
    i32              loc_screen_h;
    i32              loc_lc_r;
    i32              loc_lc_g;
    i32              loc_lc_b;
    f32              intensity;
    bool             ready;
} LensFlareSystem;

bool lens_flare_init(LensFlareSystem *lf, RHIDevice *dev, u32 width, u32 height);
void lens_flare_shutdown(LensFlareSystem *lf);
/* R550-A: self-compositing (god_rays idiom) — scene_tex is the incoming
 * frame-chain color; the shader outputs scene + flare and the result in
 * lf->lf_fbo.color_tex becomes the new chain tail.
 * R552-D: light_dir points TOWARD the sun (callers pass -sun_dir_vec,
 * matching the god_rays convention); the pass renders only when the sun
 * is in front of the camera (R551-E fixed the inverted convention). */
void lens_flare_apply(LensFlareSystem *lf, RHICmdBuffer *cmd,
                      RHITexture depth_tex, RHITexture scene_tex,
                      const f32 *view, const f32 *proj,
                      const f32 *light_dir,
                      f32 lc_r, f32 lc_g, f32 lc_b,
                      u32 screen_w, u32 screen_h);
RHITexture lens_flare_get_texture(LensFlareSystem *lf);
