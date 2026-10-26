#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    /* 计划 E Task 5 T1：反射物化表，loc_* 缓存的查询来源。 */
    RHIPipelineBindings *bind_pipe;
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
/* FS3: recreate only the size-dependent render targets; pipelines, bindings,
 * samplers and uniform locations are kept. On failure the previous targets
 * stay live and false is returned (the caller falls back to shutdown+init). */
bool contact_shadow_resize(ContactShadowSystem *s, RHIDevice *dev, u32 w, u32 h);
void contact_shadow_shutdown(ContactShadowSystem *s);
/* R550-A: self-compositing (god_rays idiom) — scene_tex is the incoming
 * frame-chain color; the pass multiplies it by the shadow mask and the
 * result in s->fbo.color_tex becomes the new chain tail. */
void contact_shadow_apply(ContactShadowSystem *s, RHICmdBuffer *cmd,
                          RHITexture depth_tex, RHITexture scene_tex,
                          const f32 *inv_proj,
                          f32 lx, f32 ly, f32 lz, u32 w, u32 h);
