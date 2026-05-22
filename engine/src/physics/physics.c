#include <physics/physics.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

AABB aabb_from_body(const RigidBody *b) {
    return (AABB){
        .min = vec3_sub(b->position, b->half_extent),
        .max = vec3_add(b->position, b->half_extent),
    };
}

bool aabb_overlap(AABB a, AABB b) {
    for (int i = 0; i < 3; i++) {
        if (a.max.e[i] < b.min.e[i] || b.max.e[i] < a.min.e[i])
            return false;
    }
    return true;
}

Vec3 aabb_overlap_depth(AABB a, AABB b) {
    Vec3 depth = {{0, 0, 0}};
    for (int i = 0; i < 3; i++) {
        f32 d1 = a.max.e[i] - b.min.e[i];
        f32 d2 = b.max.e[i] - a.min.e[i];
        depth.e[i] = d1 < d2 ? d1 : -d2;
    }
    return depth;
}

PhysicsWorld *physics_world_create(u32 max_bodies) {
    PhysicsWorld *pw = calloc(1, sizeof(PhysicsWorld));
    pw->capacity = max_bodies;
    pw->bodies = calloc(max_bodies, sizeof(RigidBody));
    pw->count = 0;
    return pw;
}

void physics_world_destroy(PhysicsWorld *pw) {
    free(pw->bodies);
    free(pw);
}

u32 physics_body_create(PhysicsWorld *pw, Vec3 pos, Vec3 half_ext, f32 mass, bool is_static) {
    if (pw->count >= pw->capacity) {
        LOG_WARN("Physics body limit reached");
        return pw->count;
    }
    u32 id = pw->count++;
    RigidBody *b = &pw->bodies[id];
    b->position = pos;
    b->velocity = vec3(0, 0, 0);
    b->acceleration = vec3(0, -9.81f, 0);
    b->half_extent = half_ext;
    b->mass = is_static ? 0.0f : mass;
    b->restitution = 0.3f;
    b->is_static = is_static;
    return id;
}

void physics_body_apply_impulse(PhysicsWorld *pw, u32 body_id, Vec3 impulse) {
    if (body_id >= pw->count) return;
    RigidBody *b = &pw->bodies[body_id];
    if (b->is_static || b->mass <= 0.0f) return;
    f32 inv_mass = 1.0f / b->mass;
    b->velocity.e[0] += impulse.e[0] * inv_mass;
    b->velocity.e[1] += impulse.e[1] * inv_mass;
    b->velocity.e[2] += impulse.e[2] * inv_mass;
}

static void resolve_contact(RigidBody *a, RigidBody *b, Vec3 normal, f32 depth) {
    f32 total_inv_mass = 0.0f;
    if (!a->is_static && a->mass > 0.0f) total_inv_mass += 1.0f / a->mass;
    if (!b->is_static && b->mass > 0.0f) total_inv_mass += 1.0f / b->mass;
    if (total_inv_mass <= 0.0f) return;

    if (!a->is_static && a->mass > 0.0f) {
        f32 ratio = (1.0f / a->mass) / total_inv_mass;
        a->position.e[0] -= normal.e[0] * depth * ratio;
        a->position.e[1] -= normal.e[1] * depth * ratio;
        a->position.e[2] -= normal.e[2] * depth * ratio;
    }
    if (!b->is_static && b->mass > 0.0f) {
        f32 ratio = (1.0f / b->mass) / total_inv_mass;
        b->position.e[0] += normal.e[0] * depth * ratio;
        b->position.e[1] += normal.e[1] * depth * ratio;
        b->position.e[2] += normal.e[2] * depth * ratio;
    }

    Vec3 rel_vel = vec3_sub(a->velocity, b->velocity);
    f32 vel_along_normal = vec3_dot(rel_vel, normal);
    if (vel_along_normal > 0.0f) return;

    f32 e = a->restitution < b->restitution ? a->restitution : b->restitution;
    f32 j = -(1.0f + e) * vel_along_normal / total_inv_mass;

    Vec3 impulse = vec3_scale(normal, j);
    if (!a->is_static && a->mass > 0.0f) {
        a->velocity.e[0] += impulse.e[0] / a->mass;
        a->velocity.e[1] += impulse.e[1] / a->mass;
        a->velocity.e[2] += impulse.e[2] / a->mass;
    }
    if (!b->is_static && b->mass > 0.0f) {
        b->velocity.e[0] -= impulse.e[0] / b->mass;
        b->velocity.e[1] -= impulse.e[1] / b->mass;
        b->velocity.e[2] -= impulse.e[2] / b->mass;
    }
}

void physics_step(PhysicsWorld *pw, f32 dt) {
    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (b->is_static) continue;

        b->velocity.e[0] += b->acceleration.e[0] * dt;
        b->velocity.e[1] += b->acceleration.e[1] * dt;
        b->velocity.e[2] += b->acceleration.e[2] * dt;

        f32 damping = 0.98f;
        b->velocity.e[0] *= damping;
        b->velocity.e[1] *= damping;
        b->velocity.e[2] *= damping;

        b->position.e[0] += b->velocity.e[0] * dt;
        b->position.e[1] += b->velocity.e[1] * dt;
        b->position.e[2] += b->velocity.e[2] * dt;
    }

    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *a = &pw->bodies[i];
        AABB aa = aabb_from_body(a);
        for (u32 j = i + 1; j < pw->count; j++) {
            RigidBody *b = &pw->bodies[j];
            AABB ba = aabb_from_body(b);
            if (!aabb_overlap(aa, ba)) continue;

            Vec3 depth = aabb_overlap_depth(aa, ba);
            f32 abs_depth = fabsf(depth.e[0]);
            int axis = 0;
            if (fabsf(depth.e[1]) < abs_depth) { abs_depth = fabsf(depth.e[1]); axis = 1; }
            if (fabsf(depth.e[2]) < abs_depth) { abs_depth = fabsf(depth.e[2]); axis = 2; }

            Vec3 normal = {{0, 0, 0}};
            normal.e[axis] = depth.e[axis] > 0 ? 1.0f : -1.0f;
            resolve_contact(a, b, normal, abs_depth);
        }
    }

    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (b->is_static) continue;
        if (b->position.e[1] - b->half_extent.e[1] < -10.0f) {
            b->position.e[1] = -10.0f + b->half_extent.e[1];
            b->velocity.e[1] = -b->velocity.e[1] * b->restitution;
        }
    }
}

bool physics_raycast(const PhysicsWorld *pw, Vec3 origin, Vec3 dir, f32 max_dist, u32 *out_body, f32 *out_t) {
    u32 best_body = 0;
    f32 best_t = max_dist;
    bool hit = false;

    for (u32 i = 0; i < pw->count; i++) {
        AABB box = aabb_from_body(&pw->bodies[i]);

        f32 tmin = 0.0f, tmax = best_t;
        for (int axis = 0; axis < 3; axis++) {
            if (fabsf(dir.e[axis]) < 0.0001f) {
                if (origin.e[axis] < box.min.e[axis] || origin.e[axis] > box.max.e[axis])
                    goto next_body;
            } else {
                f32 inv_d = 1.0f / dir.e[axis];
                f32 t1 = (box.min.e[axis] - origin.e[axis]) * inv_d;
                f32 t2 = (box.max.e[axis] - origin.e[axis]) * inv_d;
                if (t1 > t2) { f32 tmp = t1; t1 = t2; t2 = tmp; }
                if (t1 > tmin) tmin = t1;
                if (t2 < tmax) tmax = t2;
                if (tmin > tmax) goto next_body;
            }
        }

        if (tmin < best_t) {
            best_t = tmin;
            best_body = i;
            hit = true;
        }
        next_body:;
    }

    if (hit) {
        if (out_body) *out_body = best_body;
        if (out_t) *out_t = best_t;
    }
    return hit;
}
