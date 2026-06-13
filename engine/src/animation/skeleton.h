#pragma once
#include <core/types.h>
#include <math/math.h>
#include <rhi/rhi.h>

#define SKELETON_MAX_JOINTS 128
#define SKELETON_MAX_CHANNELS 64
#define SKELETON_MAX_KEYFRAMES 256

typedef struct {
    u32   joint_count;
    u32   joint_parents[SKELETON_MAX_JOINTS];
    Mat4  inverse_bind[SKELETON_MAX_JOINTS];
    Mat4  current_pose[SKELETON_MAX_JOINTS];
    /* Persistent scratch buffers for local/world pose computation
     * (avoids ~16KB stack allocation per evaluate call). */
    Mat4  _local_poses[SKELETON_MAX_JOINTS];
    Mat4  _world_poses[SKELETON_MAX_JOINTS];
    RHIBuffer joint_buf;
    RHIDevice *device;
} Skeleton;

typedef enum {
    ANIM_PATH_TRANSLATION,
    ANIM_PATH_ROTATION,
    ANIM_PATH_SCALE,
} AnimPathType;

typedef struct {
    AnimPathType path;
    u32          joint_index;
    u32          keyframe_count;
    f32          times[SKELETON_MAX_KEYFRAMES];
    f32          values[SKELETON_MAX_KEYFRAMES][4];
} AnimChannel;

typedef struct {
    f32         duration;
    f32         time;
    bool        playing;
    bool        loop;
    u32         channel_count;
    AnimChannel channels[SKELETON_MAX_CHANNELS];
} AnimClip;

void skeleton_init(Skeleton *sk, RHIDevice *dev);
void skeleton_shutdown(Skeleton *sk);
void skeleton_set_joints(Skeleton *sk, u32 count, const u32 *parents, const Mat4 *inv_bind);
void skeleton_evaluate(Skeleton *sk, const AnimClip *clip, f32 dt);
/* Apply per-bone local TRS (from anim_blend_evaluate) and compute skinning matrices. */
void skeleton_apply_local_trs(Skeleton *sk,
                              const Vec3 *local_pos, const Quat *local_rot, const Vec3 *local_scale);
/* Joint world matrices from local TRS (no inverse-bind); for IK after blending. */
void skeleton_compute_world_transforms(Skeleton *sk,
                                       const Vec3 *local_pos, const Quat *local_rot, const Vec3 *local_scale,
                                       Mat4 *out_world);
void skeleton_upload(Skeleton *sk);
void anim_clip_init(AnimClip *clip, f32 duration, bool loop);
void anim_clip_add_channel(AnimClip *clip, u32 joint_index, AnimPathType path,
                            u32 keyframe_count, const f32 *times, const f32 *values);
