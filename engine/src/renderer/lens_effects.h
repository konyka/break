#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHISampler sampler;
    i32 loc_ca_strength;
    i32 loc_vignette_strength;
    i32 loc_vignette_softness;
    i32 loc_grain_strength;
    bool ready;
} LensEffectsSystem;

bool lens_effects_init(LensEffectsSystem *s, RHIDevice *dev, u32 w, u32 h);
void lens_effects_shutdown(LensEffectsSystem *s);
void lens_effects_apply(LensEffectsSystem *s, RHICmdBuffer *cmd,
                        RHITexture input_tex,
                        f32 ca_strength, f32 vignette_strength,
                        f32 vignette_softness, f32 grain_strength,
                        u32 w, u32 h);
