#include <physics/ragdoll.h>
#include <math.h>
#include <string.h>

#define RAGDOLL_MAX_BONES 32u

static Quat body_quat(const RigidBody *b) {
    f32 l2 = 0.0f;
    for (int i = 0; i < 4; i++) l2 += b->orientation.e[i] * b->orientation.e[i];
    return l2 > 1e-12f ? quat_normalize(b->orientation) : QUAT_IDENTITY;
}

static bool mat4_finite(Mat4 m) {
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            if (!isfinite(m.e[c][r])) return false;
    return true;
}

static bool matrix_scale(Mat4 m, Vec3 *out_scale) {
    if (!mat4_finite(m)) return false;
    Vec3 scale;
    for (int c = 0; c < 3; c++) {
        scale.e[c] = sqrtf(m.e[c][0] * m.e[c][0] +
                           m.e[c][1] * m.e[c][1] +
                           m.e[c][2] * m.e[c][2]);
        if (!(scale.e[c] > 1e-8f)) return false;
    }
    *out_scale = scale;
    return true;
}

static bool matrix_rotation(Mat4 m, Quat *out_rotation) {
    Vec3 scale;
    if (!matrix_scale(m, &scale)) return false;
    f32 r00 = m.e[0][0] / scale.e[0];
    f32 r10 = m.e[0][1] / scale.e[0];
    f32 r20 = m.e[0][2] / scale.e[0];
    f32 r01 = m.e[1][0] / scale.e[1];
    f32 r11 = m.e[1][1] / scale.e[1];
    f32 r21 = m.e[1][2] / scale.e[1];
    f32 r02 = m.e[2][0] / scale.e[2];
    f32 r12 = m.e[2][1] / scale.e[2];
    f32 r22 = m.e[2][2] / scale.e[2];
    Quat q;
    f32 trace = r00 + r11 + r22;
    if (trace > 0.0f) {
        f32 s = 2.0f * sqrtf(trace + 1.0f);
        q.e[3] = 0.25f * s;
        q.e[0] = (r21 - r12) / s;
        q.e[1] = (r02 - r20) / s;
        q.e[2] = (r10 - r01) / s;
    } else if (r00 > r11 && r00 > r22) {
        f32 s = 2.0f * sqrtf(1.0f + r00 - r11 - r22);
        q.e[3] = (r21 - r12) / s;
        q.e[0] = 0.25f * s;
        q.e[1] = (r01 + r10) / s;
        q.e[2] = (r02 + r20) / s;
    } else if (r11 > r22) {
        f32 s = 2.0f * sqrtf(1.0f + r11 - r00 - r22);
        q.e[3] = (r02 - r20) / s;
        q.e[0] = (r01 + r10) / s;
        q.e[1] = 0.25f * s;
        q.e[2] = (r12 + r21) / s;
    } else {
        f32 s = 2.0f * sqrtf(1.0f + r22 - r00 - r11);
        q.e[3] = (r10 - r01) / s;
        q.e[0] = (r02 + r20) / s;
        q.e[1] = (r12 + r21) / s;
        q.e[2] = 0.25f * s;
    }
    for (int i = 0; i < 4; i++) if (!isfinite(q.e[i])) return false;
    *out_rotation = quat_normalize(q);
    return true;
}

static Vec3 matrix_translation(Mat4 m) {
    return vec3(m.e[3][0], m.e[3][1], m.e[3][2]);
}

static bool validate_hierarchy(const Skeleton *sk) {
    u32 n = sk->joint_count;
    for (u32 joint = 0; joint < n; joint++) {
        u32 node = joint;
        for (u32 depth = 0; depth <= n; depth++) {
            u32 parent = sk->joint_parents[node];
            if (parent == UINT32_MAX) break;
            if (parent >= n || parent == node || parent == joint) return false;
            node = parent;
            if (depth == n) return false;
        }
    }
    return true;
}

static void ragdoll_rollback(Ragdoll *rd, PhysicsWorld *pw) {
    for (u32 i = 0; i < rd->bone_count; i++) {
        if (physics_constraint_handle_is_valid(rd->bones[i].constraint_id))
            physics_constraint_remove(pw, rd->bones[i].constraint_id);
    }
    for (u32 i = 0; i < rd->bone_count; i++) {
        if (physics_body_handle_is_valid(rd->bones[i].body_id))
            physics_body_park(pw, rd->bones[i].body_id);
    }
}

bool ragdoll_activate(Ragdoll *rd, PhysicsWorld *pw, const Skeleton *sk, IKSystem *ik) {
    if (!rd || !pw || !sk || rd->active || sk->joint_count == 0 ||
        sk->joint_count > RAGDOLL_MAX_BONES) return false;
    u32 n = sk->joint_count;
    if (!validate_hierarchy(sk)) return false;

    Mat4 world_m[RAGDOLL_MAX_BONES];
    Vec3 world_p[RAGDOLL_MAX_BONES];
    Quat world_q[RAGDOLL_MAX_BONES];
    Vec3 local_scale[RAGDOLL_MAX_BONES];
    u32 required_constraints = 0;
    for (u32 j = 0; j < n; j++) {
        world_m[j] = mat4_mul(sk->current_pose[j], mat4_inverse(sk->inverse_bind[j]));
        world_p[j] = matrix_translation(world_m[j]);
        if (!isfinite(world_p[j].e[0]) || !isfinite(world_p[j].e[1]) ||
            !isfinite(world_p[j].e[2]) || !matrix_rotation(world_m[j], &world_q[j])) return false;
        u32 parent = sk->joint_parents[j];
        Mat4 local = world_m[j];
        if (parent != UINT32_MAX) {
            local = mat4_mul(mat4_inverse(world_m[parent]), world_m[j]);
            required_constraints++;
        }
        if (!matrix_scale(local, &local_scale[j])) return false;
    }

    u32 free_constraints = 0;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++)
        if (!pw->constraints[i].active) free_constraints++;
    if (free_constraints < required_constraints) return false;
    u32 available_bodies = pw->capacity - pw->count;
    for (u32 i = 0; i < pw->count; i++)
        if (physics_body_is_parked(&pw->bodies[i])) available_bodies++;
    if (available_bodies < n) return false;

    Ragdoll next;
    memset(&next, 0, sizeof(next));
    next.bone_count = n;
    for (u32 j = 0; j < n; j++) {
        next.bones[j].joint = j;
        next.bones[j].body_id = PHYSICS_BODY_HANDLE_INVALID;
        next.bones[j].constraint_id = PHYSICS_CONSTRAINT_HANDLE_INVALID;
        next.bones[j].parent_bone = sk->joint_parents[j];
        next.bones[j].local_scale = local_scale[j];
    }

    for (u32 j = 0; j < n; j++) {
        u32 parent = sk->joint_parents[j];
        Vec3 body_p = world_p[j];
        f32 half_h = 0.02f;
        if (parent != UINT32_MAX) {
            f32 distance = vec3_len(vec3_sub(world_p[j], world_p[parent]));
            half_h = distance * 0.5f - 0.05f;
            if (half_h < 0.01f) half_h = 0.01f;
            body_p = vec3_scale(vec3_add(world_p[j], world_p[parent]), 0.5f);
        }
        PhysicsBodyHandle id = physics_body_create_capsule(pw, body_p, 0.05f, half_h, 1.0f, false, 0);
        if (!physics_body_handle_is_valid(id)) {
            ragdoll_rollback(&next, pw);
            return false;
        }
        PhysicsPose pose;
        pose.orientation = world_q[j];
        pose.angular_velocity = vec3(0, 0, 0);
        pose.inertia_diag = vec3(1, 1, 1);
        physics_body_set_pose(pw, id, &pose);
        next.bones[j].body_id = id;
        next.bones[j].body_to_joint_pos = quat_rotate_vec3(
            quat_inverse(world_q[j]), vec3_sub(world_p[j], body_p));
        next.bones[j].body_to_joint_rot = quat_normalize(quat_mul(
            quat_inverse(world_q[j]), world_q[j]));
    }

    for (u32 j = 0; j < n; j++) {
        u32 parent = sk->joint_parents[j];
        if (parent == UINT32_MAX) continue;
        RigidBody *a = &pw->bodies[next.bones[parent].body_id.index];
        RigidBody *b = &pw->bodies[next.bones[j].body_id.index];
        Quat qa = body_quat(a);
        Quat qb = body_quat(b);
        Vec3 direction = vec3_sub(world_p[j], world_p[parent]);
        if (vec3_dot(direction, direction) <= 1e-12f) direction = vec3(0, 1, 0);
        direction = vec3_normalize(direction);
        ConeTwistDesc desc;
        memset(&desc, 0, sizeof(desc));
        desc.body_a = next.bones[parent].body_id;
        desc.body_b = next.bones[j].body_id;
        desc.anchor_local_a = quat_rotate_vec3(quat_inverse(qa), vec3_sub(world_p[j], a->position));
        desc.anchor_local_b = quat_rotate_vec3(quat_inverse(qb), vec3_sub(world_p[j], b->position));
        desc.axis_local_a = quat_rotate_vec3(quat_inverse(qa), direction);
        desc.axis_local_b = quat_rotate_vec3(quat_inverse(qb), direction);
        desc.swing_max = 1.2f;
        desc.twist_min = -0.6f;
        desc.twist_max = 0.6f;
        PhysicsConstraintHandle constraint = physics_constraint_add_cone_twist(pw, &desc);
        if (!physics_constraint_handle_is_valid(constraint)) {
            ragdoll_rollback(&next, pw);
            return false;
        }
        next.bones[j].constraint_id = constraint;
    }

    next.active = true;
    next.ik = ik;
    next.ik_was_suspended = ik ? ik->physics_suspended : false;
    if (ik) anim_ik_set_physics_suspended(ik, true);
    *rd = next;
    return true;
}

void ragdoll_deactivate(Ragdoll *rd, PhysicsWorld *pw) {
    if (!rd || !rd->active) return;
    if (pw) ragdoll_rollback(rd, pw);
    if (rd->ik) anim_ik_set_physics_suspended(rd->ik, rd->ik_was_suspended);
    memset(rd, 0, sizeof(*rd));
}

bool ragdoll_write_local_trs(const Ragdoll *rd, const PhysicsWorld *pw,
                             const Skeleton *sk, Vec3 *out_local_pos,
                             Quat *out_local_rot, Vec3 *out_local_scale) {
    if (!rd || !pw || !sk || !out_local_pos || !out_local_rot || !out_local_scale ||
        !rd->active || rd->bone_count != sk->joint_count || rd->bone_count > RAGDOLL_MAX_BONES)
        return false;
    u32 n = rd->bone_count;
    Vec3 world_p[RAGDOLL_MAX_BONES];
    Quat world_q[RAGDOLL_MAX_BONES];
    Vec3 local_p[RAGDOLL_MAX_BONES];
    Quat local_q[RAGDOLL_MAX_BONES];
    Vec3 local_s[RAGDOLL_MAX_BONES];
    for (u32 j = 0; j < n; j++) {
        const RagdollBone *bone = &rd->bones[j];
        if (bone->joint != j || !physics_body_handle_is_valid(bone->body_id) ||
            bone->body_id.index >= pw->count) return false;
        const RigidBody *b = &pw->bodies[bone->body_id.index];
        if (physics_body_is_parked(b) || b->generation != bone->body_id.generation) return false;
        Quat q = body_quat(b);
        world_q[j] = quat_normalize(quat_mul(q, bone->body_to_joint_rot));
        world_p[j] = vec3_add(b->position, quat_rotate_vec3(q, bone->body_to_joint_pos));
        for (int k = 0; k < 3; k++)
            if (!isfinite(world_p[j].e[k])) return false;
        for (int k = 0; k < 4; k++)
            if (!isfinite(world_q[j].e[k])) return false;
    }
    for (u32 j = 0; j < n; j++) {
        const RagdollBone *bone = &rd->bones[j];
        u32 parent = bone->parent_bone;
        if (parent == UINT32_MAX) {
            local_p[j] = world_p[j];
            local_q[j] = world_q[j];
        } else {
            if (parent >= n) return false;
            Quat inverse_parent = quat_inverse(world_q[parent]);
            local_p[j] = quat_rotate_vec3(inverse_parent, vec3_sub(world_p[j], world_p[parent]));
            local_q[j] = quat_normalize(quat_mul(inverse_parent, world_q[j]));
            Vec3 parent_scale = vec3(1, 1, 1);
            u32 node = parent;
            for (u32 depth = 0; depth < n; depth++) {
                Vec3 scale = rd->bones[node].local_scale;
                for (int k = 0; k < 3; k++) parent_scale.e[k] *= scale.e[k];
                u32 next = rd->bones[node].parent_bone;
                if (next == UINT32_MAX) break;
                if (next >= n || depth + 1u == n) return false;
                node = next;
            }
            for (int k = 0; k < 3; k++) {
                if (!isfinite(parent_scale.e[k]) || fabsf(parent_scale.e[k]) <= 1e-8f) return false;
                local_p[j].e[k] /= parent_scale.e[k];
            }
        }
        local_s[j] = bone->local_scale;
    }
    memcpy(out_local_pos, local_p, n * sizeof(*local_p));
    memcpy(out_local_rot, local_q, n * sizeof(*local_q));
    memcpy(out_local_scale, local_s, n * sizeof(*local_s));
    return true;
}

void ragdoll_write_pose(const Ragdoll *rd, const PhysicsWorld *pw, Skeleton *sk) {
    if (!rd || !pw || !sk || !rd->active) return;
    Vec3 local_p[RAGDOLL_MAX_BONES];
    Quat local_q[RAGDOLL_MAX_BONES];
    Vec3 local_s[RAGDOLL_MAX_BONES];
    if (!ragdoll_write_local_trs(rd, pw, sk, local_p, local_q, local_s)) return;
    skeleton_apply_local_trs(sk, local_p, local_q, local_s);
}
