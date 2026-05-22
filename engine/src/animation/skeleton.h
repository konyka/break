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
void skeleton_upload(Skeleton *sk);
void anim_clip_init(AnimClip *clip, f32 duration, bool loop);
void anim_clip_add_channel(AnimClip *clip, u32 joint_index, AnimPathType path,
                            u32 keyframe_count, const f32 *times, const f32 *values);
