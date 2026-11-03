#pragma once

#include <core/types.h>
#include <math/math.h>

#define ANIM_MORPH_MAX_TARGETS 32u
#define ANIM_MORPH_MAX_VERTICES 65536u
#define ANIM_MORPH_NAME_CAP 32u
#define ANIM_MORPH_SKIN_VERTEX_BYTES 64u

typedef struct {
    char name[ANIM_MORPH_NAME_CAP];
    const Vec3 *position_deltas;
} AnimMorphTarget;

typedef struct {
    u32 vertex_count;
    u32 target_count;
    AnimMorphTarget targets[ANIM_MORPH_MAX_TARGETS];
} AnimMorphSet;

bool anim_morph_init(AnimMorphSet *set, u32 vertex_count);
bool anim_morph_add_target(AnimMorphSet *set, const char *name,
                           const Vec3 *position_deltas);
bool anim_morph_evaluate(const AnimMorphSet *set, const f32 *base_xyz,
                         const f32 *weights, u32 weight_count, f32 *out_xyz);
bool anim_morph_evaluate_skinned(const AnimMorphSet *set, const void *base_vertices,
                                 const f32 *weights, u32 weight_count,
                                 void *out_vertices, usize out_bytes);
