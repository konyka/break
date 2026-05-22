#include <physics/character.h>
#include <core/log.h>
#include <math.h>

CharacterController character_create(Vec3 pos, f32 radius, f32 height) {
    CharacterController cc = {0};
    cc.position = pos;
    cc.velocity = vec3(0, 0, 0);
    cc.radius = radius;
    cc.height = height;
    cc.slope_limit = 0.7f;
    cc.step_height = 0.3f;
    cc.grounded = false;
    cc.jump_requested = false;
    return cc;
}

void character_update(CharacterController *cc, PhysicsWorld *pw, f32 dt,
                       Vec3 move_input, bool jump) {
    f32 gravity = -20.0f;
    f32 move_speed = 6.0f;
    f32 jump_speed = 8.0f;
    f32 damping = 0.85f;

    cc->velocity.e[0] = move_input.e[0] * move_speed;
    cc->velocity.e[2] = move_input.e[2] * move_speed;

    cc->velocity.e[0] *= damping;
    cc->velocity.e[2] *= damping;

    if (jump && cc->grounded) {
        cc->velocity.e[1] = jump_speed;
        cc->grounded = false;
    }

    cc->velocity.e[1] += gravity * dt;

    Vec3 next_pos = vec3_add(cc->position, vec3_scale(cc->velocity, dt));

    AABB char_aabb;
    char_aabb.min = vec3(next_pos.e[0] - cc->radius, next_pos.e[1], next_pos.e[2] - cc->radius);
    char_aabb.max = vec3(next_pos.e[0] + cc->radius, next_pos.e[1] + cc->height, next_pos.e[2] + cc->radius);

    cc->grounded = false;

    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (!b->is_static) continue;

        AABB body_aabb = aabb_from_body(b);
        if (!aabb_overlap(char_aabb, body_aabb)) continue;

        Vec3 depth = aabb_overlap_depth(char_aabb, body_aabb);
        f32 abs_x = fabsf(depth.e[0]);
        f32 abs_y = fabsf(depth.e[1]);
        f32 abs_z = fabsf(depth.e[2]);

        if (abs_y <= abs_x && abs_y <= abs_z) {
            if (depth.e[1] > 0) {
                next_pos.e[1] += depth.e[1];
                if (cc->velocity.e[1] < 0) cc->velocity.e[1] = 0;
                cc->grounded = true;
            } else {
                next_pos.e[1] += depth.e[1];
                if (cc->velocity.e[1] > 0) cc->velocity.e[1] = 0;
            }
        } else if (abs_x <= abs_z) {
            next_pos.e[0] += depth.e[0];
        } else {
            next_pos.e[2] += depth.e[2];
        }
    }

    cc->position = next_pos;
}

Vec3 character_get_position(const CharacterController *cc) {
    return cc->position;
}

bool character_is_grounded(const CharacterController *cc) {
    return cc->grounded;
}

bool physics_sweep_test(const PhysicsWorld *pw, Vec3 origin, Vec3 delta,
                         u32 ignore_body, Vec3 *out_hit_pos, f32 *out_t) {
    f32 best_t = 1.0f;
    bool hit = false;

    for (u32 i = 0; i < pw->count; i++) {
        if (i == ignore_body) continue;
        AABB box = aabb_from_body(&pw->bodies[i]);

        f32 tmin = 0.0f, tmax = best_t;
        bool valid = true;

        for (int axis = 0; axis < 3; axis++) {
            if (fabsf(delta.e[axis]) < 0.0001f) {
                if (origin.e[axis] < box.min.e[axis] || origin.e[axis] > box.max.e[axis]) {
                    valid = false;
                    break;
                }
            } else {
                f32 inv_d = 1.0f / delta.e[axis];
                f32 t1 = (box.min.e[axis] - origin.e[axis]) * inv_d;
                f32 t2 = (box.max.e[axis] - origin.e[axis]) * inv_d;
                if (t1 > t2) { f32 tmp = t1; t1 = t2; t2 = tmp; }
                if (t1 > tmin) tmin = t1;
                if (t2 < tmax) tmax = t2;
                if (tmin > tmax) { valid = false; break; }
            }
        }

        if (valid && tmin < best_t) {
            best_t = tmin;
            hit = true;
        }
    }

    if (hit) {
        if (out_t) *out_t = best_t;
        if (out_hit_pos) {
            out_hit_pos->e[0] = origin.e[0] + delta.e[0] * best_t;
            out_hit_pos->e[1] = origin.e[1] + delta.e[1] * best_t;
            out_hit_pos->e[2] = origin.e[2] + delta.e[2] * best_t;
        }
    }
    return hit;
}
