#include <physics/ragdoll.h>
#include <math/math.h>

static Vec3 joint_pos(const Skeleton *sk, u32 joint) {
    const Mat4 *m = &sk->current_pose[joint];
    return vec3(m->e[3][0], m->e[3][1], m->e[3][2]);
}

bool ragdoll_activate(Ragdoll *rd, PhysicsWorld *pw, const Skeleton *sk) {
    if (!rd || !pw || !sk || sk->joint_count == 0 || sk->joint_count > 32u) return false;
    u32 hinges = sk->joint_count - 1u;
    u32 free_slots = 0;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (!pw->constraints[i].active) free_slots++;
    }
    if (free_slots < hinges) return false;
    if (pw->count + sk->joint_count > pw->capacity) return false;

    u32 created[32];
    u32 ncreated = 0;
    for (u32 j = 0; j < sk->joint_count; j++) {
        Vec3 pos = joint_pos(sk, j);
        f32 half_h = 0.02f;
        if (j > 0) {
            Vec3 parent = joint_pos(sk, j - 1u);
            f32 dist = vec3_len(vec3_sub(pos, parent));
            half_h = dist * 0.5f - 0.05f;
            if (half_h < 0.01f) half_h = 0.01f;
            pos = vec3_scale(vec3_add(pos, parent), 0.5f);
        }
        u32 id = physics_body_create_capsule(pw, pos, 0.05f, half_h, 1.0f, false, 0);
        if (id == UINT32_MAX) {
            for (u32 k = 0; k < ncreated; k++) physics_body_park(pw, created[k]);
            return false;
        }
        created[ncreated++] = id;
        rd->bones[j].joint = j;
        rd->bones[j].body_id = id;
        rd->bones[j].parent_bone = j == 0 ? UINT32_MAX : j - 1u;
    }
    for (u32 j = 1; j < sk->joint_count; j++) {
        HingeDesc hinge;
        hinge.body_a = rd->bones[j - 1u].body_id;
        hinge.body_b = rd->bones[j].body_id;
        hinge.anchor_local_a = vec3(0, 0, 0);
        hinge.anchor_local_b = vec3(0, 0, 0);
        hinge.axis_local_a = vec3(0, 1, 0);
        hinge.limit_min = -1.2f;
        hinge.limit_max = 1.2f;
        if (physics_constraint_add_hinge(pw, &hinge) == UINT32_MAX) {
            for (u32 k = 0; k < ncreated; k++) physics_body_park(pw, created[k]);
            rd->bone_count = 0;
            rd->active = false;
            return false;
        }
    }
    rd->bone_count = sk->joint_count;
    rd->active = true;
    return true;
}

void ragdoll_write_pose(const Ragdoll *rd, const PhysicsWorld *pw, Skeleton *sk) {
    if (!rd || !pw || !sk || !rd->active) return;
    for (u32 i = 0; i < rd->bone_count; i++) {
        u32 id = rd->bones[i].body_id;
        if (id >= pw->count) continue;
        const RigidBody *b = &pw->bodies[id];
        Quat q = b->orientation;
        f32 l2 = q.e[0] * q.e[0] + q.e[1] * q.e[1] + q.e[2] * q.e[2] + q.e[3] * q.e[3];
        if (l2 <= 1e-12f) q = QUAT_IDENTITY;
        Mat4 m = mat4_from_quat(q);
        m.e[3][0] = b->position.e[0];
        m.e[3][1] = b->position.e[1];
        m.e[3][2] = b->position.e[2];
        m.e[3][3] = 1.0f;
        sk->current_pose[rd->bones[i].joint] = m;
    }
}
