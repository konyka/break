#include <animation/animation.h>
#include <core/log.h>
#include <math/math.h>
#include <math.h>
#include <string.h>

/* ----------------------------------------------------------------- */
/* Internal helpers                                                  */
/* ----------------------------------------------------------------- */

static f32 clampf(f32 v, f32 lo, f32 hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

static u32 clip_find_keyframe(const AnimChannel *ch, f32 time) {
    /* Binary search: O(log n) instead of O(n) linear scan. */
    if (ch->keyframe_count <= 1) return 0;
    u32 lo = 0, hi = ch->keyframe_count - 1;
    while (lo + 1 < hi) {
        u32 mid = (lo + hi) >> 1;
        if (ch->times[mid] <= time) lo = mid;
        else                        hi = mid;
    }
    return lo;
}

/*
 * Sample one clip into the provided per-bone TRS arrays.
 * Bones not addressed by any channel keep their current value, so callers
 * should pre-fill identity defaults.
 */
static void clip_sample(const AnimClip *clip, f32 time,
                        Vec3 *out_pos, Quat *out_rot, Vec3 *out_scl,
                        u32 bone_count) {
    if (!clip) return;
    for (u32 ci = 0; ci < clip->channel_count; ci++) {
        const AnimChannel *ch = &clip->channels[ci];
        if (ch->keyframe_count == 0) continue;
        u32 ji = ch->joint_index;
        if (ji >= bone_count) continue;

        const f32 *v0;
        const f32 *v1;
        f32 frac;

        if (ch->keyframe_count == 1) {
            v0 = ch->values[0];
            v1 = v0;
            frac = 0.0f;
        } else {
            u32 k0 = clip_find_keyframe(ch, time);
            u32 k1 = k0 + 1;
            if (k1 >= ch->keyframe_count) k1 = k0;
            f32 t0 = ch->times[k0];
            f32 t1 = ch->times[k1];
            f32 dt = t1 - t0;
            frac = (dt > 0.0f) ? (time - t0) * (1.0f / dt) : 0.0f;
            frac = clampf(frac, 0.0f, 1.0f);
            v0 = ch->values[k0];
            v1 = ch->values[k1];
        }

        if (ch->path == ANIM_PATH_TRANSLATION) {
            Vec3 a = (Vec3){{v0[0], v0[1], v0[2]}};
            Vec3 b = (Vec3){{v1[0], v1[1], v1[2]}};
            out_pos[ji] = vec3_lerp(a, b, frac);
        } else if (ch->path == ANIM_PATH_ROTATION) {
            Quat a = (Quat){{v0[0], v0[1], v0[2], v0[3]}};
            Quat b = (Quat){{v1[0], v1[1], v1[2], v1[3]}};
            out_rot[ji] = quat_nlerp(a, b, frac);
        } else if (ch->path == ANIM_PATH_SCALE) {
            Vec3 a = (Vec3){{v0[0], v0[1], v0[2]}};
            Vec3 b = (Vec3){{v1[0], v1[1], v1[2]}};
            out_scl[ji] = vec3_lerp(a, b, frac);
        }
    }
}

static void fill_bind_pose(Vec3 *pos, Quat *rot, Vec3 *scl, u32 count) {
    for (u32 i = 0; i < count; i++) {
        pos[i] = (Vec3){{0, 0, 0}};
        rot[i] = QUAT_IDENTITY;
        scl[i] = (Vec3){{1, 1, 1}};
    }
}

static bool layer_includes_bone(const AnimationLayer *layer, u32 bone) {
    if (layer->bone_mask == 0) return true;          /* 0 == no mask */
    if (bone >= 64) return true;                     /* mask only spans 0..63 */
    return (layer->bone_mask & (1ULL << bone)) != 0;
}

static const AnimClip *clip_at(const AnimClip *clips, u32 count, u32 idx) {
    if (!clips || idx >= count) return NULL;
    return &clips[idx];
}

/* ----------------------------------------------------------------- */
/* Blend state lifecycle                                             */
/* ----------------------------------------------------------------- */

void anim_blend_state_init(AnimBlendState *state, u32 bone_count) {
    if (!state) return;
    memset(state, 0, sizeof(*state));
    if (bone_count > ANIM_BLEND_MAX_BONES) bone_count = ANIM_BLEND_MAX_BONES;
    state->bone_count = bone_count;
    fill_bind_pose(state->local_positions, state->local_rotations,
                   state->local_scales, bone_count);
    for (u32 i = 0; i < ANIM_MAX_LAYERS; i++) {
        state->layers[i].speed   = 1.0f;
        state->layers[i].weight  = 0.0f;
        state->layers[i].mode    = ANIM_BLEND_OVERRIDE;
        state->layers[i].looping = true;
    }
}

void anim_blend_state_destroy(AnimBlendState *state) {
    if (!state) return;
    /* No dynamic resources held; reset for safety. */
    memset(state, 0, sizeof(*state));
}

/* ----------------------------------------------------------------- */
/* Layer operations                                                  */
/* ----------------------------------------------------------------- */

void anim_layer_play(AnimBlendState *state, u32 layer, u32 clip_index,
                     f32 speed, bool loop) {
    if (!state || layer >= ANIM_MAX_LAYERS) return;
    AnimationLayer *L = &state->layers[layer];
    L->clip_index = clip_index;
    L->time       = 0.0f;
    L->speed      = speed;
    L->looping    = loop;
    L->active     = true;
    if (L->weight <= 0.0f) L->weight = 1.0f;
    if (layer >= state->layer_count) state->layer_count = layer + 1;
}

void anim_layer_set_weight(AnimBlendState *state, u32 layer, f32 weight) {
    if (!state || layer >= ANIM_MAX_LAYERS) return;
    state->layers[layer].weight = clampf(weight, 0.0f, 1.0f);
}

void anim_layer_set_bone_mask(AnimBlendState *state, u32 layer, u64 mask) {
    if (!state || layer >= ANIM_MAX_LAYERS) return;
    state->layers[layer].bone_mask = mask;
}

void anim_layer_set_mode(AnimBlendState *state, u32 layer, AnimBlendMode mode) {
    if (!state || layer >= ANIM_MAX_LAYERS) return;
    state->layers[layer].mode = mode;
}

void anim_layer_stop(AnimBlendState *state, u32 layer) {
    if (!state || layer >= ANIM_MAX_LAYERS) return;
    state->layers[layer].active = false;
    state->layers[layer].weight = 0.0f;
}

/* ----------------------------------------------------------------- */
/* Crossfade                                                         */
/* ----------------------------------------------------------------- */

void anim_crossfade(AnimBlendState *state, u32 layer, u32 new_clip, f32 duration) {
    if (!state || layer >= ANIM_MAX_LAYERS) return;
    AnimationLayer *L = &state->layers[layer];
    if (duration <= 0.0f) {
        /* Instant switch. */
        L->clip_index = new_clip;
        L->time       = 0.0f;
        L->active     = true;
        state->crossfade.active = false;
        return;
    }
    state->crossfade.from_clip   = L->clip_index;
    state->crossfade.to_clip     = new_clip;
    state->crossfade.layer_index = layer;
    state->crossfade.duration    = duration;
    state->crossfade.inv_duration = 1.0f / duration;
    state->crossfade.elapsed     = 0.0f;
    state->crossfade.active      = true;
    L->active = true;
    if (layer >= state->layer_count) state->layer_count = layer + 1;
}

void anim_set_event_callback(AnimBlendState *state, AnimEventCallback cb,
                             void *user_data) {
    if (!state) return;
    state->event_callback = cb;
    state->event_user_data = user_data;
}

/* ----------------------------------------------------------------- */
/* Per-frame evaluation                                              */
/* ----------------------------------------------------------------- */

static void advance_layer_time(AnimationLayer *L, f32 dt, f32 duration) {
    L->time += dt * L->speed;
    if (duration > 0.0f) {
        if (L->looping) {
            L->time = fmodf(L->time, duration);
            if (L->time < 0.0f) L->time += duration;
        } else if (L->time > duration) {
            L->time = duration;
        }
    }
}

/* R101: Fire animation events whose timestamps fall in [t0, t1).
 * Called after advance_layer_time to notify the host of timeline crossings. */
static void fire_events_in_range(const AnimClip *clip, f32 t0, f32 t1,
                                  AnimBlendState *state) {
    if (!state->event_callback || !clip || clip->event_count == 0) return;
    for (u32 i = 0; i < clip->event_count; i++) {
        f32 et = clip->events[i].time;
        if (et >= t0 && et < t1) {
            state->event_callback(clip->events[i].name, et,
                                  state->event_user_data);
        }
    }
}

void anim_blend_evaluate(AnimBlendState *state, f32 dt,
                         const AnimClip *clips, u32 clip_count) {
    if (!state) return;

    /* Reset output to bind pose. */
    fill_bind_pose(state->local_positions, state->local_rotations,
                   state->local_scales, state->bone_count);

    /* Advance crossfade timer. */
    f32 fade_t = 0.0f;
    bool fade_done = false;
    if (state->crossfade.active && state->crossfade.duration > 0.0f) {
        state->crossfade.elapsed += dt;
        fade_t = state->crossfade.elapsed * state->crossfade.inv_duration;
        if (fade_t >= 1.0f) {
            fade_t = 1.0f;
            fade_done = true;
        }
    }

    /* Per-layer scratch buffers (static — avoids ~5KB per-frame stack). */
    static Vec3 sample_pos[ANIM_BLEND_MAX_BONES];
    static Quat sample_rot[ANIM_BLEND_MAX_BONES];
    static Vec3 sample_scl[ANIM_BLEND_MAX_BONES];

    for (u32 li = 0; li < state->layer_count && li < ANIM_MAX_LAYERS; li++) {
        AnimationLayer *L = &state->layers[li];
        if (!L->active || L->weight <= 0.0f) continue;

        const AnimClip *clip = clip_at(clips, clip_count, L->clip_index);
        f32 dur = clip ? clip->duration : 0.0f;
        f32 prev_time = L->time;
        advance_layer_time(L, dt, dur);

        /* R101: Fire events that fall in the time interval crossed this frame.
         * For looping clips that wrapped, fire two ranges: [prev, dur) + [0, now). */
        if (state->event_callback && clip && clip->event_count > 0) {
            if (L->time > prev_time) {
                fire_events_in_range(clip, prev_time, L->time, state);
            } else if (L->time < prev_time && L->looping && dur > 0.0f) {
                fire_events_in_range(clip, prev_time, dur, state);
                fire_events_in_range(clip, 0.0f, L->time, state);
            }
        }

        /* Copy current output to sample buffer instead of fill_bind_pose.
         * clip_sample only writes bones with animation channels; unaddressed
         * bones retain the output value (bind pose or accumulated result),
         * which is the correct default for blending. */
        u32 bc = state->bone_count;
        memcpy(sample_pos, state->local_positions, bc * sizeof(Vec3));
        memcpy(sample_rot, state->local_rotations, bc * sizeof(Quat));
        memcpy(sample_scl, state->local_scales,    bc * sizeof(Vec3));
        if (clip) clip_sample(clip, L->time, sample_pos, sample_rot,
                              sample_scl, state->bone_count);

        if (state->crossfade.active && state->crossfade.layer_index == li) {
            const AnimClip *from_clip = clip_at(clips, clip_count,
                                                state->crossfade.from_clip);
            if (from_clip) {
                static Vec3 from_pos[ANIM_BLEND_MAX_BONES];
                static Quat from_rot[ANIM_BLEND_MAX_BONES];
                static Vec3 from_scl[ANIM_BLEND_MAX_BONES];
                fill_bind_pose(from_pos, from_rot, from_scl, state->bone_count);
                /* Approximate from-clip time as wrapped current time. */
                f32 ft = L->time;
                if (from_clip->duration > 0.0f)
                    ft = fmodf(ft, from_clip->duration);
                clip_sample(from_clip, ft, from_pos, from_rot, from_scl,
                            state->bone_count);
                for (u32 b = 0; b < state->bone_count; b++) {
                    sample_pos[b] = vec3_lerp(from_pos[b], sample_pos[b], fade_t);
                    sample_rot[b] = quat_nlerp(from_rot[b], sample_rot[b], fade_t);
                    sample_scl[b] = vec3_lerp(from_scl[b], sample_scl[b], fade_t);
                }
            }
        }

        /* Mix scratch into output, honoring weight, mask, and mode. */
        f32 w = clampf(L->weight, 0.0f, 1.0f);
        for (u32 b = 0; b < state->bone_count; b++) {
            if (!layer_includes_bone(L, b)) continue;

            if (L->mode == ANIM_BLEND_OVERRIDE) {
                state->local_positions[b] =
                    vec3_lerp(state->local_positions[b], sample_pos[b], w);
                state->local_rotations[b] =
                    quat_nlerp(state->local_rotations[b], sample_rot[b], w);
                state->local_scales[b] =
                    vec3_lerp(state->local_scales[b], sample_scl[b], w);
            } else { /* ANIM_BLEND_ADDITIVE */
                /* Treat sampled rotation as a delta applied on top. */
                Quat delta = quat_nlerp(QUAT_IDENTITY, sample_rot[b], w);
                state->local_rotations[b] =
                    quat_normalize(quat_mul(delta, state->local_rotations[b]));
                state->local_positions[b] =
                    vec3_add(state->local_positions[b], vec3_scale(sample_pos[b], w));
                /* Multiplicative additive scale. */
                Vec3 s = state->local_scales[b];
                s.e[0] *= 1.0f + (sample_scl[b].e[0] - 1.0f) * w;
                s.e[1] *= 1.0f + (sample_scl[b].e[1] - 1.0f) * w;
                s.e[2] *= 1.0f + (sample_scl[b].e[2] - 1.0f) * w;
                state->local_scales[b] = s;
            }
        }
    }

    if (fade_done) {
        AnimationLayer *L = &state->layers[state->crossfade.layer_index];
        L->clip_index = state->crossfade.to_clip;
        state->crossfade.active = false;
    }
}

/* ----------------------------------------------------------------- */
/* IK system                                                         */
/* ----------------------------------------------------------------- */

void anim_ik_init(IKSystem *ik) {
    if (!ik) return;
    memset(ik, 0, sizeof(*ik));
}

void anim_ik_set_target(IKSystem *ik, u32 index,
                        u32 root, u32 mid, u32 tip,
                        Vec3 target, Vec3 pole) {
    if (!ik || index >= ANIM_MAX_IK_TARGETS) return;
    IKTarget *T = &ik->targets[index];
    T->chain_root  = root;
    T->chain_mid   = mid;
    T->chain_tip   = tip;
    T->target_pos  = target;
    T->pole_target = pole;
    if (T->weight <= 0.0f) T->weight = 1.0f;
    T->active      = true;
    if (index >= ik->target_count) ik->target_count = index + 1;
}

void anim_ik_set_weight(IKSystem *ik, u32 index, f32 weight) {
    if (!ik || index >= ANIM_MAX_IK_TARGETS) return;
    ik->targets[index].weight = clampf(weight, 0.0f, 1.0f);
}

void anim_ik_set_active(IKSystem *ik, u32 index, bool active) {
    if (!ik || index >= ANIM_MAX_IK_TARGETS) return;
    ik->targets[index].active = active;
}

static Vec3 mat4_get_translation(const Mat4 *m) {
    return (Vec3){{m->e[3][0], m->e[3][1], m->e[3][2]}};
}

void anim_ik_two_bone(Vec3 root_pos, Vec3 mid_pos, Vec3 tip_pos,
                      Vec3 target, Vec3 pole_target,
                      Quat *out_root_rot, Quat *out_mid_rot) {
    /*
     * Analytic Two-Bone IK following the standard "law of cosines" derivation.
     * Solves for delta rotations at root and mid joints (in world space) so
     * that the tip reaches `target`. `pole_target` defines the bend plane.
     */
    Vec3 ab = vec3_sub(mid_pos, root_pos);   /* upper bone vector */
    Vec3 cb = vec3_sub(mid_pos, tip_pos);    /* mid->tip reversed  */
    Vec3 ac = vec3_sub(tip_pos, root_pos);   /* current chain vec  */
    Vec3 at = vec3_sub(target, root_pos);    /* desired chain vec  */

    f32 lab = vec3_len(ab);
    f32 lcb = vec3_len(cb);
    f32 lat = clampf(vec3_len(at), 0.001f, lab + lcb - 0.001f);

    f32 eps = 1e-6f;
    if (lab < eps || lcb < eps) {
        if (out_root_rot) *out_root_rot = QUAT_IDENTITY;
        if (out_mid_rot)  *out_mid_rot  = QUAT_IDENTITY;
        return;
    }

    /* Current angles — atan2f(cross_len, dot) avoids clamp and is more robust
     * near 0 and pi than acosf(clamp(dot)). */
    Vec3 ac_n = vec3_normalize(ac);
    Vec3 ab_n = vec3_normalize(ab);
    Vec3 ba_n = vec3_normalize(vec3_sub(root_pos, mid_pos));
    Vec3 bc_n = vec3_normalize(vec3_sub(tip_pos, mid_pos));
    Vec3 at_n = vec3_normalize(at);

    f32 ac_ab_0 = atan2f(vec3_len(vec3_cross(ac_n, ab_n)), vec3_dot(ac_n, ab_n));
    f32 ba_bc_0 = atan2f(vec3_len(vec3_cross(ba_n, bc_n)), vec3_dot(ba_n, bc_n));
    f32 ac_at_0 = atan2f(vec3_len(vec3_cross(ac_n, at_n)), vec3_dot(ac_n, at_n));

    /* Desired angles (law of cosines via atan2f — avoids clamp + acosf).
     * Use fast_rsqrt for sin computation: sqrt(x) = x * rsqrt(x). */
    f32 lab2 = lab * lab, lcb2 = lcb * lcb, lat2 = lat * lat;
    f32 cos_ac_ab = (lab2 + lat2 - lcb2) / (2.0f * lab * lat);
    f32 sin2_ac_ab = fmaxf(1.0f - cos_ac_ab * cos_ac_ab, 0.0f);
    f32 sin_ac_ab = sin2_ac_ab > 1e-12f ? sin2_ac_ab * fast_rsqrt(sin2_ac_ab) : 0.0f;
    f32 ac_ab_1 = atan2f(sin_ac_ab, cos_ac_ab);

    f32 cos_ba_bc = (lab2 + lcb2 - lat2) / (2.0f * lab * lcb);
    f32 sin2_ba_bc = fmaxf(1.0f - cos_ba_bc * cos_ba_bc, 0.0f);
    f32 sin_ba_bc = sin2_ba_bc > 1e-12f ? sin2_ba_bc * fast_rsqrt(sin2_ba_bc) : 0.0f;
    f32 ba_bc_1 = atan2f(sin_ba_bc, cos_ba_bc);

    /* Bend axis: derived from current chain and pole direction. Falls
     * back to a stable axis when the pole is collinear with the chain. */
    Vec3 pole_dir = vec3_sub(pole_target, root_pos);
    Vec3 axis0 = vec3_cross(ac, pole_dir);
    if (vec3_len(axis0) < eps) {
        /* Pole degenerate: pick any perpendicular to ac. */
        Vec3 up = (Vec3){{0, 1, 0}};
        if (fabsf(vec3_dot(ac_n, up)) > 0.95f) up = (Vec3){{1, 0, 0}};
        axis0 = vec3_cross(ac, up);
    }
    axis0 = vec3_normalize(axis0);

    /* Reach axis: rotates current chain (ac) to point at target (at). */
    Vec3 axis1 = vec3_cross(ac, at);
    if (vec3_len(axis1) < eps) axis1 = axis0;
    axis1 = vec3_normalize(axis1);

    Quat r0 = quat_from_axis_angle(axis0, ac_ab_1 - ac_ab_0);
    Quat r1 = quat_from_axis_angle(axis0, ba_bc_1 - ba_bc_0);
    Quat r2 = quat_from_axis_angle(axis1, ac_at_0);

    if (out_root_rot) *out_root_rot = quat_normalize(quat_mul(r2, r0));
    if (out_mid_rot)  *out_mid_rot  = quat_normalize(r1);
}

void anim_ik_solve(IKSystem *ik, Vec3 *positions, Quat *rotations,
                   const Mat4 *world_transforms) {
    (void)positions;
    if (!ik || !rotations || !world_transforms) return;

    for (u32 i = 0; i < ik->target_count && i < ANIM_MAX_IK_TARGETS; i++) {
        IKTarget *T = &ik->targets[i];
        if (!T->active || T->weight <= 0.0f) continue;

        Vec3 root_pos = mat4_get_translation(&world_transforms[T->chain_root]);
        Vec3 mid_pos  = mat4_get_translation(&world_transforms[T->chain_mid]);
        Vec3 tip_pos  = mat4_get_translation(&world_transforms[T->chain_tip]);

        Quat root_delta;
        Quat mid_delta;
        anim_ik_two_bone(root_pos, mid_pos, tip_pos,
                         T->target_pos, T->pole_target,
                         &root_delta, &mid_delta);

        f32 w = clampf(T->weight, 0.0f, 1.0f);
        Quat root_w = quat_nlerp(QUAT_IDENTITY, root_delta, w);
        Quat mid_w  = quat_nlerp(QUAT_IDENTITY, mid_delta,  w);

        rotations[T->chain_root] =
            quat_normalize(quat_mul(root_w, rotations[T->chain_root]));
        rotations[T->chain_mid] =
            quat_normalize(quat_mul(mid_w,  rotations[T->chain_mid]));
    }
}
