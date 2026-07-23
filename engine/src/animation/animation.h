#pragma once
/*
 * Layered animation blending + Two-Bone IK
 * -----------------------------------------
 * Sits on top of skeleton.h's AnimClip data. The blend state owns the
 * final per-bone local TRS arrays. IK solving is an optional pass that
 * runs after blending and mutates local rotations in place.
 *
 * Constraints:
 *   - No dynamic memory allocation (all storage is fixed-size).
 *   - Bone mask is a 64-bit bitmask; bones with index < 64 can be masked
 *     individually. A mask value of 0 means "no filtering" (all bones).
 *   - Backward compatible with existing skeleton/AnimClip API.
 */

#include <core/types.h>
#include <math/math.h>
#include <animation/skeleton.h>

#define ANIM_MAX_LAYERS        8
#define ANIM_MAX_IK_TARGETS    8
#define ANIM_BLEND_MAX_BONES   SKELETON_MAX_JOINTS

typedef enum {
    ANIM_BLEND_OVERRIDE = 0,
    ANIM_BLEND_ADDITIVE = 1,
} AnimBlendMode;

typedef struct {
    u32           clip_index;
    f32           time;
    f32           speed;
    f32           weight;
    AnimBlendMode mode;
    u64           bone_mask;
    bool          looping;
    bool          active;
} AnimationLayer;

typedef struct {
    u32  from_clip;
    u32  to_clip;
    u32  layer_index;
    f32  duration;
    f32  inv_duration;  /* 1.0f / duration, precomputed to avoid per-frame division */
    f32  elapsed;
    bool active;
} AnimCrossfade;

typedef void (*AnimEventCallback)(const char *event_name, f32 time, void *user_data);

typedef struct {
    AnimationLayer    layers[ANIM_MAX_LAYERS];
    u32               layer_count;
    AnimCrossfade     crossfade;

    /* Final per-bone local-space TRS (output of anim_blend_evaluate). */
    Vec3              local_positions[ANIM_BLEND_MAX_BONES];
    Quat              local_rotations[ANIM_BLEND_MAX_BONES];
    Vec3              local_scales[ANIM_BLEND_MAX_BONES];
    u32               bone_count;

    AnimEventCallback event_callback;
    void             *event_user_data;
} AnimBlendState;

typedef struct {
    u32  chain_root;
    u32  chain_mid;
    u32  chain_tip;
    Vec3 target_pos;
    Vec3 pole_target;
    f32  weight;
    bool active;
} IKTarget;

typedef struct {
    IKTarget targets[ANIM_MAX_IK_TARGETS];
    u32      target_count;
} IKSystem;

/* ---- Blend state lifecycle ---- */
void anim_blend_state_init(AnimBlendState *state, u32 bone_count);
void anim_blend_state_destroy(AnimBlendState *state);

/* ---- Layer operations ---- */
void anim_layer_play(AnimBlendState *state, u32 layer, u32 clip_index, f32 speed, bool loop);
void anim_layer_set_weight(AnimBlendState *state, u32 layer, f32 weight);
void anim_layer_set_bone_mask(AnimBlendState *state, u32 layer, u64 mask);
void anim_layer_set_mode(AnimBlendState *state, u32 layer, AnimBlendMode mode);
void anim_layer_stop(AnimBlendState *state, u32 layer);

/* ---- Crossfade (single, applies to a specific layer) ---- */
void anim_crossfade(AnimBlendState *state, u32 layer, u32 new_clip, f32 duration);

/* ---- Per-frame evaluation ---- */
void anim_blend_evaluate(AnimBlendState *state, f32 dt,
                         const AnimClip *clips, u32 clip_count);

/* ---- Animation events ---- */
void anim_set_event_callback(AnimBlendState *state, AnimEventCallback cb, void *user_data);

/* ---- IK system ---- */
void anim_ik_init(IKSystem *ik);
void anim_ik_set_target(IKSystem *ik, u32 index,
                        u32 root, u32 mid, u32 tip,
                        Vec3 target, Vec3 pole);
void anim_ik_set_weight(IKSystem *ik, u32 index, f32 weight);
void anim_ik_set_active(IKSystem *ik, u32 index, bool active);

/*
 * Apply all active IK targets. `world_transforms` provides the current
 * world-space matrices for each joint (caller computes them from the
 * blend output). `positions` and `rotations` are the per-bone local TRS
 * to be modified in place.
 */
void anim_ik_solve(IKSystem *ik, Vec3 *positions, Quat *rotations,
                   const Mat4 *world_transforms, u32 bone_count);

/*
 * Two-Bone IK analytic solver. Outputs world-space rotation deltas to
 * apply to the root and mid joints so that the tip reaches `target`.
 * `pole_target` controls the bend plane.
 */
void anim_ik_two_bone(Vec3 root_pos, Vec3 mid_pos, Vec3 tip_pos,
                      Vec3 target, Vec3 pole_target,
                      Quat *out_root_rot, Quat *out_mid_rot);
