#pragma once

#include <animation/morph.h>

#define ANIM_FACIAL_MAX_EXPRESSIONS 16u
#define ANIM_FACIAL_MAX_CURVES 8u
#define ANIM_FACIAL_MAX_KEYS 16u
#define ANIM_FACIAL_NAME_CAP 32u

typedef struct {
    char name[ANIM_FACIAL_NAME_CAP];
    char morph_target[ANIM_MORPH_NAME_CAP];
    u32 keyframe_count;
    f32 times[ANIM_FACIAL_MAX_KEYS];
    f32 values[ANIM_FACIAL_MAX_KEYS];
} AnimFacialCurve;

typedef struct {
    char name[ANIM_FACIAL_NAME_CAP];
    u32 curve_count;
    AnimFacialCurve curves[ANIM_FACIAL_MAX_CURVES];
} AnimFacialExpression;

typedef struct {
    u32 expression_count;
    AnimFacialExpression expressions[ANIM_FACIAL_MAX_EXPRESSIONS];
} AnimFacialLibrary;

void anim_facial_library_init(AnimFacialLibrary *library);
bool anim_facial_add_expression(AnimFacialLibrary *library, const char *name);
bool anim_facial_add_curve(AnimFacialLibrary *library,
                           const char *expression_name, const char *curve_name,
                           const char *morph_target_name, u32 keyframe_count,
                           const f32 *times, const f32 *values);
bool anim_facial_evaluate(const AnimFacialLibrary *library,
                          const AnimMorphSet *morphs, const char *expression_name,
                          f32 time, f32 *out_weights, u32 weight_count);
