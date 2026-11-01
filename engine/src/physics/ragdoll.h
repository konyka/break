#pragma once
#include <core/types.h>
#include <physics/physics.h>
#include <animation/skeleton.h>

typedef struct RagdollBone {
    u32 joint;
    u32 body_id;
    u32 parent_bone; /* UINT32_MAX is the root */
} RagdollBone;

typedef struct Ragdoll {
    RagdollBone bones[32];
    u32 bone_count;
    bool active;
} Ragdoll;

bool ragdoll_activate(Ragdoll *rd, PhysicsWorld *pw, const Skeleton *sk);
void ragdoll_write_pose(const Ragdoll *rd, const PhysicsWorld *pw, Skeleton *sk);
