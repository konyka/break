#pragma once
#include <core/types.h>
#include <physics/physics.h>
#include <animation/animation.h>

typedef struct RagdollBone {
    u32 joint;
    PhysicsBodyHandle body_id;
    u32 parent_bone;
    PhysicsConstraintHandle constraint_id;
    Vec3 body_to_joint_pos;
    Quat body_to_joint_rot;
    Vec3 local_scale;
} RagdollBone;

typedef struct Ragdoll {
    RagdollBone bones[32];
    u32 bone_count;
    bool active;
    IKSystem *ik;
} Ragdoll;

bool ragdoll_activate(Ragdoll *rd, PhysicsWorld *pw, const Skeleton *sk, IKSystem *ik);
void ragdoll_deactivate(Ragdoll *rd, PhysicsWorld *pw);
bool ragdoll_write_local_trs(const Ragdoll *rd, const PhysicsWorld *pw,
                             const Skeleton *sk, Vec3 *out_local_pos,
                             Quat *out_local_rot, Vec3 *out_local_scale);
void ragdoll_write_pose(const Ragdoll *rd, const PhysicsWorld *pw, Skeleton *sk);
