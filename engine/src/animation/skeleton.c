#include <animation/skeleton.h>
#include <core/log.h>
#include <math/math.h>
#include <rhi/rhi.h>
#include <string.h>
#include <math.h>

void skeleton_init(Skeleton *sk, RHIDevice *dev) {
    memset(sk, 0, sizeof(*sk));
    sk->device = dev;
}

void skeleton_shutdown(Skeleton *sk) {
    if (sk->device && rhi_handle_valid(sk->joint_buf)) {
        rhi_buffer_destroy(sk->device, sk->joint_buf);
    }
    memset(sk, 0, sizeof(*sk));
}

void skeleton_set_joints(Skeleton *sk, u32 count, const u32 *parents, const Mat4 *inv_bind) {
    sk->joint_count = count > SKELETON_MAX_JOINTS ? SKELETON_MAX_JOINTS : count;
    for (u32 i = 0; i < sk->joint_count; i++) {
        sk->joint_parents[i] = parents[i];
        sk->inverse_bind[i] = inv_bind[i];
        sk->current_pose[i] = mat4_identity();
    }

    if (!rhi_handle_valid(sk->joint_buf)) {
        RHIBufferDesc desc = {0};
        desc.usage = RHI_BUFFER_USAGE_TEXEL;
        desc.size = SKELETON_MAX_JOINTS * sizeof(Mat4);
        sk->joint_buf = rhi_buffer_create(sk->device, &desc);
    }
}

static Vec3 anim_lerp_vec3(const f32 *a, const f32 *b, f32 t) {
    Vec3 r;
    r.e[0] = a[0] + (b[0] - a[0]) * t;
    r.e[1] = a[1] + (b[1] - a[1]) * t;
    r.e[2] = a[2] + (b[2] - a[2]) * t;
    return r;
}

static Quat anim_slerp_quat(const f32 *a, const f32 *b, f32 t) {
    f32 dot = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
    f32 ba[4];
    if (dot < 0.0f) {
        dot = -dot;
        ba[0] = -b[0]; ba[1] = -b[1]; ba[2] = -b[2]; ba[3] = -b[3];
    } else {
        ba[0] = b[0]; ba[1] = b[1]; ba[2] = b[2]; ba[3] = b[3];
    }
    f32 s0 = 1.0f - t;
    f32 s1 = t;
    if (dot < 0.999f) {
        f32 omega = acosf(dot);
        f32 inv = 1.0f / sinf(omega);
        s0 = sinf(s0 * omega) * inv;
        s1 = sinf(s1 * omega) * inv;
    }
    Quat r;
    r.e[0] = s0 * a[0] + s1 * ba[0];
    r.e[1] = s0 * a[1] + s1 * ba[1];
    r.e[2] = s0 * a[2] + s1 * ba[2];
    r.e[3] = s0 * a[3] + s1 * ba[3];
    return r;
}

static u32 anim_find_keyframe(const AnimChannel *ch, f32 time) {
    for (u32 i = 0; i < ch->keyframe_count - 1; i++) {
        if (time < ch->times[i + 1]) return i;
    }
    return ch->keyframe_count > 0 ? ch->keyframe_count - 1 : 0;
}

void skeleton_evaluate(Skeleton *sk, const AnimClip *clip, f32 dt) {
    if (clip->channel_count == 0) {
        for (u32 i = 0; i < sk->joint_count; i++) {
            sk->current_pose[i] = mat4_identity();
        }
        return;
    }

    Vec3 translations[SKELETON_MAX_JOINTS];
    Quat rotations[SKELETON_MAX_JOINTS];
    Vec3 scales[SKELETON_MAX_JOINTS];

    for (u32 i = 0; i < sk->joint_count; i++) {
        translations[i] = (Vec3){{0, 0, 0}};
        rotations[i] = (Quat){{0, 0, 0, 1}};
        scales[i] = (Vec3){{1, 1, 1}};
    }

    f32 t = clip->time;
    for (u32 ci = 0; ci < clip->channel_count; ci++) {
        const AnimChannel *ch = &clip->channels[ci];
        if (ch->keyframe_count == 0) continue;
        u32 ji = ch->joint_index;
        if (ji >= sk->joint_count) continue;

        if (ch->keyframe_count == 1) {
            if (ch->path == ANIM_PATH_TRANSLATION) {
                translations[ji] = (Vec3){{ch->values[0][0], ch->values[0][1], ch->values[0][2]}};
            } else if (ch->path == ANIM_PATH_ROTATION) {
                rotations[ji] = (Quat){{ch->values[0][0], ch->values[0][1], ch->values[0][2], ch->values[0][3]}};
            } else if (ch->path == ANIM_PATH_SCALE) {
                scales[ji] = (Vec3){{ch->values[0][0], ch->values[0][1], ch->values[0][2]}};
            }
            continue;
        }

        u32 kf = anim_find_keyframe(ch, t);
        u32 kf_next = kf + 1;
        if (kf_next >= ch->keyframe_count) kf_next = kf;

        f32 t0 = ch->times[kf];
        f32 t1 = ch->times[kf_next];
        f32 frac = (t1 > t0) ? (t - t0) / (t1 - t0) : 0.0f;
        if (frac < 0.0f) frac = 0.0f;
        if (frac > 1.0f) frac = 1.0f;

        if (ch->path == ANIM_PATH_TRANSLATION) {
            translations[ji] = anim_lerp_vec3(ch->values[kf], ch->values[kf_next], frac);
        } else if (ch->path == ANIM_PATH_ROTATION) {
            rotations[ji] = anim_slerp_quat(ch->values[kf], ch->values[kf_next], frac);
        } else if (ch->path == ANIM_PATH_SCALE) {
            scales[ji] = anim_lerp_vec3(ch->values[kf], ch->values[kf_next], frac);
        }
    }

    Mat4 local_poses[SKELETON_MAX_JOINTS];
    for (u32 i = 0; i < sk->joint_count; i++) {
        Mat4 T = mat4_translation(translations[i].e[0], translations[i].e[1], translations[i].e[2]);
        Mat4 R = mat4_from_quat(rotations[i]);
        Mat4 S = mat4_scaling(scales[i].e[0], scales[i].e[1], scales[i].e[2]);
        local_poses[i] = mat4_mul(T, mat4_mul(R, S));
    }

    Mat4 world_poses[SKELETON_MAX_JOINTS];
    for (u32 i = 0; i < sk->joint_count; i++) {
        if (sk->joint_parents[i] == UINT32_MAX || sk->joint_parents[i] >= i) {
            world_poses[i] = local_poses[i];
        } else {
            world_poses[i] = mat4_mul(world_poses[sk->joint_parents[i]], local_poses[i]);
        }
        sk->current_pose[i] = mat4_mul(world_poses[i], sk->inverse_bind[i]);
    }

    (void)dt;
}

void skeleton_upload(Skeleton *sk) {
    if (!rhi_handle_valid(sk->joint_buf)) return;
    rhi_buffer_update(sk->device, sk->joint_buf, sk->current_pose,
        sk->joint_count * sizeof(Mat4));
}

void anim_clip_init(AnimClip *clip, f32 duration, bool loop) {
    memset(clip, 0, sizeof(*clip));
    clip->duration = duration;
    clip->loop = loop;
    clip->playing = true;
}

void anim_clip_add_channel(AnimClip *clip, u32 joint_index, AnimPathType path,
                            u32 keyframe_count, const f32 *times, const f32 *values) {
    if (clip->channel_count >= SKELETON_MAX_CHANNELS) return;
    AnimChannel *ch = &clip->channels[clip->channel_count++];
    ch->joint_index = joint_index;
    ch->path = path;
    ch->keyframe_count = keyframe_count > SKELETON_MAX_KEYFRAMES ? SKELETON_MAX_KEYFRAMES : keyframe_count;
    for (u32 i = 0; i < ch->keyframe_count; i++) {
        ch->times[i] = times[i];
        memcpy(ch->values[i], values + i * 4, sizeof(f32) * 4);
    }
}
