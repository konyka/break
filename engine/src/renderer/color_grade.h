#pragma once
#include <rhi/rhi.h>

typedef struct {
    RHIDevice *dev;
    RHIPipeline pipe;
    RHIOffscreenFBO fbo;
    RHISampler sampler;
    i32 loc_saturation;
    i32 loc_contrast;
    i32 loc_brightness;
    i32 loc_temperature;
    i32 loc_tint;
    bool ready;
} ColorGradeSystem;

bool color_grade_init(ColorGradeSystem *s, RHIDevice *dev, u32 w, u32 h);
void color_grade_shutdown(ColorGradeSystem *s);
void color_grade_apply(ColorGradeSystem *s, RHICmdBuffer *cmd,
                       RHITexture input_tex, f32 saturation, f32 contrast,
                       f32 brightness, f32 temperature, f32 tint, u32 w, u32 h);
