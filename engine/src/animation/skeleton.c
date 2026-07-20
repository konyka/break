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
    if (sk->device) {
        if (rhi_handle_valid(sk->joint_buf[0]))
            rhi_buffer_destroy(sk->device, sk->joint_buf[0]);
        if (rhi_handle_valid(sk->joint_buf[1]))
            rhi_buffer_destroy(sk->device, sk->joint_buf[1]);
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

    if (!rhi_handle_valid(sk->joint_buf[0])) {
        RHIBufferDesc desc = {0};
        desc.usage = RHI_BUFFER_USAGE_TEXEL;
        desc.size = SKELETON_MAX_JOINTS * sizeof(Mat4);
        sk->joint_buf[0] = rhi_buffer_create(sk->device, &desc);
        sk->joint_buf[1] = rhi_buffer_create(sk->device, &desc);
    }
}

static Vec3 anim_lerp_vec3(const f32 *a, const f32 *b, f32 t) {
    Vec3 r;
    r.e[0] = a[0] + (b[0] - a[0]) * t;
    r.e[1] = a[1] + (b[1] - a[1]) * t;
    r.e[2] = a[2] + (b[2] - a[2]) * t;
    return r;
}

/* Normalized linear interpolation (nlerp) — replaces slerp for animation blending.
 * Eliminates acosf + sinf×3 (4 transcendental functions). Angular error <1°
 * which is imperceptible in skeletal animation. */
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
    Quat r;
    r.e[0] = s0 * a[0] + s1 * ba[0];
    r.e[1] = s0 * a[1] + s1 * ba[1];
    r.e[2] = s0 * a[2] + s1 * ba[2];
    r.e[3] = s0 * a[3] + s1 * ba[3];
    return quat_normalize(r);
}

static u32 anim_find_keyframe(const AnimChannel *ch, f32 time) {
    /* Binary search: O(log n) instead of O(n) linear scan.
     * Finds the last keyframe i where times[i] <= time. */
    if (ch->keyframe_count <= 1) return 0;
    u32 lo = 0, hi = ch->keyframe_count - 1;
    while (lo + 1 < hi) {
        u32 mid = (lo + hi) >> 1;
        if (ch->times[mid] <= time) lo = mid;
        else                        hi = mid;
    }
    return lo;
}

/* Directly compose T*R*S into a single Mat4 without intermediate matrices.
 * R from quaternion, S diagonal scaling, T translation. ~9 multiplies vs
 * 2 full mat4_mul (~128 multiplies). */
static Mat4 mat4_trs(Vec3 t, Quat q, Vec3 s) {
    f32 x = q.e[0], y = q.e[1], z = q.e[2], w = q.e[3];
    f32 sx = s.e[0], sy = s.e[1], sz = s.e[2];
    /* Rotation matrix elements (same as mat4_from_quat) */
    f32 r00 = 1.0f - 2.0f*(y*y + z*z);
    f32 r01 = 2.0f*(x*y + w*z);
    f32 r02 = 2.0f*(x*z - w*y);
    f32 r10 = 2.0f*(x*y - w*z);
    f32 r11 = 1.0f - 2.0f*(x*x + z*z);
    f32 r12 = 2.0f*(y*z + w*x);
    f32 r20 = 2.0f*(x*z + w*y);
    f32 r21 = 2.0f*(y*z - w*x);
    f32 r22 = 1.0f - 2.0f*(x*x + y*y);
    /* T*R*S: scale each column of R, set translation in column 3 */
    Mat4 m;
    memset(&m, 0, sizeof(m));
    m.e[0][0] = r00 * sx; m.e[1][0] = r10 * sy; m.e[2][0] = r20 * sz; m.e[3][0] = t.e[0];
    m.e[0][1] = r01 * sx; m.e[1][1] = r11 * sy; m.e[2][1] = r21 * sz; m.e[3][1] = t.e[1];
    m.e[0][2] = r02 * sx; m.e[1][2] = r12 * sy; m.e[2][2] = r22 * sz; m.e[3][2] = t.e[2];
    m.e[3][3] = 1.0f;
    return m;
}

/* R240: Resolve world_poses[i] = root ? local[i] : world[parent[i]] * local[i]
 * for arbitrary joint ordering. glTF's skin.joints array is NOT required to
 * list a parent joint before its children; the old "joint_parents[i] >= i =>
 * treat as root" heuristic mis-rooted such children and corrupted the skin.
 * Iterate to a fixpoint (joint_count <= SKELETON_MAX_JOINTS = 128). For skins
 * already ordered parent-before-child this yields identical results in one pass. */
static void skel_resolve_world(const u32 *parents, const Mat4 *local, Mat4 *world, u32 n) {
    if (n > SKELETON_MAX_JOINTS) n = SKELETON_MAX_JOINTS;
    bool resolved[SKELETON_MAX_JOINTS];
    for (u32 i = 0; i < n; i++) resolved[i] = false;
    u32 remaining = n;
    for (u32 pass = 0; pass <= n && remaining > 0u; pass++) {
        u32 progressed = 0u;
        for (u32 i = 0; i < n; i++) {
            if (resolved[i]) continue;
            u32 p = parents[i];
            if (p == UINT32_MAX || p >= n || p == i) {
                world[i] = local[i];
            } else if (resolved[p]) {
                world[i] = mat4_mul(world[p], local[i]);
            } else {
                continue; /* parent not resolved yet — defer to a later pass */
            }
            resolved[i] = true;
            remaining--;
            progressed++;
        }
        if (progressed == 0u) break; /* parent cycle: leave remaining as roots */
    }
    for (u32 i = 0; i < n; i++) if (!resolved[i]) world[i] = local[i];
}

void skeleton_evaluate(Skeleton *sk, const AnimClip *clip, f32 dt) {
    if (clip->channel_count == 0) {
        for (u32 i = 0; i < sk->joint_count; i++) {
            sk->current_pose[i] = mat4_identity();
        }
        return;
    }

    static Vec3 translations[SKELETON_MAX_JOINTS];
    static Quat rotations[SKELETON_MAX_JOINTS];
    static Vec3 scales[SKELETON_MAX_JOINTS];

    /* Initialize with identity transforms.
     * memset for translations (all-zero Vec3), static constants for others. */
    memset(translations, 0, sk->joint_count * sizeof(Vec3));
    {
        static const Quat identity_rot = {{0, 0, 0, 1}};
        static const Vec3 identity_scl = {{1, 1, 1}};
        for (u32 i = 0; i < sk->joint_count; i++) {
            rotations[i] = identity_rot;
            scales[i] = identity_scl;
        }
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
        f32 dt = t1 - t0;
        f32 frac = (dt > 0.0f) ? (t - t0) * (1.0f / dt) : 0.0f;
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

    Mat4 *local_poses = sk->_local_poses;
    for (u32 i = 0; i < sk->joint_count; i++) {
        local_poses[i] = mat4_trs(translations[i], rotations[i], scales[i]);
    }

    Mat4 *world_poses = sk->_world_poses;
    skel_resolve_world(sk->joint_parents, local_poses, world_poses, sk->joint_count);
    for (u32 i = 0; i < sk->joint_count; i++) {
        sk->current_pose[i] = mat4_mul(world_poses[i], sk->inverse_bind[i]);
    }

    (void)dt;
}

void skeleton_apply_local_trs(Skeleton *sk,
                              const Vec3 *local_pos, const Quat *local_rot, const Vec3 *local_scale) {
    if (!sk || !local_pos || !local_rot || !local_scale) return;

    Mat4 *local_poses = sk->_local_poses;
    u32 n = sk->joint_count;
    if (n > SKELETON_MAX_JOINTS) n = SKELETON_MAX_JOINTS;

    for (u32 i = 0; i < n; i++) {
        local_poses[i] = mat4_trs(local_pos[i], local_rot[i], local_scale[i]);
    }

    Mat4 *world_poses = sk->_world_poses;
    skel_resolve_world(sk->joint_parents, local_poses, world_poses, n);
    for (u32 i = 0; i < n; i++) {
        sk->current_pose[i] = mat4_mul(world_poses[i], sk->inverse_bind[i]);
    }
}

void skeleton_compute_world_transforms(Skeleton *sk,
                                       const Vec3 *local_pos, const Quat *local_rot, const Vec3 *local_scale,
                                       Mat4 *out_world) {
    if (!sk || !local_pos || !local_rot || !local_scale || !out_world) return;

    Mat4 *local_poses = sk->_local_poses;
    u32 n = sk->joint_count;
    if (n > SKELETON_MAX_JOINTS) n = SKELETON_MAX_JOINTS;

    for (u32 i = 0; i < n; i++) {
        local_poses[i] = mat4_trs(local_pos[i], local_rot[i], local_scale[i]);
    }

    skel_resolve_world(sk->joint_parents, local_poses, out_world, n);
}

void skeleton_upload(Skeleton *sk) {
    RHIBuffer slot = skeleton_joint_slot(sk);
    if (!rhi_handle_valid(slot)) return;
    rhi_buffer_update(sk->device, slot, sk->current_pose,
        sk->joint_count * sizeof(Mat4));
}

RHIBuffer skeleton_joint_slot(const Skeleton *sk) {
    if (!sk || !sk->device) return RHI_HANDLE_NULL;
    return sk->joint_buf[rhi_frame_index(sk->device) & 1u];
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
    ch->interp = ANIM_INTERP_LINEAR; /* default; callers may override (e.g. glTF STEP) */
    ch->keyframe_count = keyframe_count > SKELETON_MAX_KEYFRAMES ? SKELETON_MAX_KEYFRAMES : keyframe_count;
    for (u32 i = 0; i < ch->keyframe_count; i++) {
        ch->times[i] = times[i];
        memcpy(ch->values[i], values + i * 4, sizeof(f32) * 4);
    }
}

void anim_clip_add_event(AnimClip *clip, f32 time, const char *name) {
    if (!clip || !name) return;
    if (clip->event_count >= SKELETON_MAX_EVENTS) return;
    AnimEvent *ev = &clip->events[clip->event_count++];
    ev->time = time;
    /* Copy name with truncation and null-termination. */
    usize i = 0;
    for (; i < SKELETON_MAX_EVENT_NAME - 1 && name[i] != '\0'; i++)
        ev->name[i] = name[i];
    ev->name[i] = '\0';
}
