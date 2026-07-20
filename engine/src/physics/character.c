#include <physics/character.h>
#include <physics/bvh.h>
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

/* Build a capsule RigidBody (centre-origin) for a character whose `position`
 * is its feet. Returns false for degenerate dimensions (treated as a sphere). */
static RigidBody char_capsule(const CharacterController *cc, Vec3 feet) {
    f32 r = cc->radius;
    f32 cy0 = feet.e[1] + r;             /* bottom sphere centre */
    f32 cy1 = feet.e[1] + cc->height - r;/* top sphere centre */
    if (cy1 < cy0) {                     /* height < 2r: collapse to sphere */
        f32 mid = feet.e[1] + cc->height * 0.5f;
        cy0 = cy1 = mid;
    }
    RigidBody cap = {0};
    cap.shape       = SHAPE_CAPSULE;
    cap.position    = vec3(feet.e[0], (cy0 + cy1) * 0.5f, feet.e[2]);
    cap.radius      = r;
    cap.half_height = (cy1 - cy0) * 0.5f;
    cap.is_static   = false;
    return cap;
}

/* Push the capsule (feet at `pos`) out of all static geometry. Reports whether
 * a walkable (slope_limit-passing) surface was contacted. Does not touch
 * velocity. */
static Vec3 char_slide_resolve(const CharacterController *cc, PhysicsWorld *pw,
                               Vec3 pos, bool *out_grounded) {
    bool grounded = false;
    const int MAX_ITERS = 6;

    f32 r = cc->radius;
    f32 hh = cc->height * 0.5f;

    /* Query BVH for nearby candidates; fall back to all bodies if BVH not built */
    static u32 candidates[64];
    u32 nc = 0;
    bool use_bvh = (pw->bvh.node_count > 0);
    if (use_bvh) {
        f32 margin = r * 2.0f;
        BVHAABB query_box;
        query_box.min = vec3(pos.e[0] - r - margin, pos.e[1] - margin, pos.e[2] - r - margin);
        query_box.max = vec3(pos.e[0] + r + margin, pos.e[1] + hh + cc->height + margin, pos.e[2] + r + margin);
        nc = bvh_query_aabb(&pw->bvh, query_box, candidates, 64);
        /* R239 (CORRECTNESS): bvh_query_aabb stops writing once it fills the 64
         * candidate slots, silently dropping any further overlapping static
         * bodies. If the query saturated, fall back to the full linear scan
         * below so the capsule cannot tunnel through the dropped geometry. */
        if (nc >= 64u) use_bvh = false;
    }

    for (int iter = 0; iter < MAX_ITERS; iter++) {
        RigidBody cap = char_capsule(cc, pos);
        f32 best_depth = 0.0f;
        Vec3 best_n = vec3(0, 0, 0);
        bool any = false;
        if (use_bvh) {
            for (u32 ci = 0; ci < nc; ci++) {
                u32 i = candidates[ci];
                RigidBody *b = &pw->bodies[i];
                if (!b->is_static) continue;
                Contact ct;
                if (!physics_collide(&cap, b, &ct)) continue;
                if (ct.depth > best_depth) {
                    best_depth = ct.depth;
                    best_n = ct.normal;
                    any = true;
                }
            }
        } else {
            for (u32 i = 0; i < pw->count; i++) {
                RigidBody *b = &pw->bodies[i];
                if (!b->is_static) continue;
                Contact ct;
                if (!physics_collide(&cap, b, &ct)) continue;
                if (ct.depth > best_depth) {
                    best_depth = ct.depth;
                    best_n = ct.normal;
                    any = true;
                }
            }
        }
        if (!any) break;
        Vec3 sep = vec3_scale(best_n, -1.0f);
        pos = vec3_add(pos, vec3_scale(sep, best_depth));
        if (sep.e[1] > cc->slope_limit) grounded = true;
    }
    if (out_grounded) *out_grounded = grounded;
    return pos;
}

/* Signed horizontal progress of `p` from `start` along direction `dir`. */
static f32 horiz_progress(Vec3 start, Vec3 p, Vec3 dir) {
    Vec3 d = vec3_sub(p, start);
    d.e[1] = 0.0f;
    return vec3_dot(d, dir);
}

void character_update(CharacterController *cc, PhysicsWorld *pw, f32 dt,
                       Vec3 move_input, bool jump) {
    f32 gravity     = -20.0f;
    f32 move_speed  = 6.0f;
    f32 jump_speed  = 8.0f;
    f32 damping     = 0.85f;

    cc->velocity.e[0] = move_input.e[0] * move_speed * damping;
    cc->velocity.e[2] = move_input.e[2] * move_speed * damping;

    if (jump && cc->grounded) {
        cc->velocity.e[1] = jump_speed;
        cc->grounded = false;
    }
    cc->velocity.e[1] += gravity * dt;

    Vec3 start = cc->position;

    /* 1) Vertical move (gravity / jump) + landing resolve. */
    Vec3 pos = start;
    pos.e[1] += cc->velocity.e[1] * dt;
    bool grounded_v = false;
    pos = char_slide_resolve(cc, pw, pos, &grounded_v);
    if (grounded_v && cc->velocity.e[1] < 0.0f) cc->velocity.e[1] = 0.0f;

    /* 2) Horizontal move + wall slide.
     * Compute horiz_len and inv_len together: avoids redundant fast_rsqrt call. */
    Vec3 horiz = vec3(cc->velocity.e[0] * dt, 0.0f, cc->velocity.e[2] * dt);
    f32  horiz_l2 = horiz.e[0] * horiz.e[0] + horiz.e[2] * horiz.e[2];
    f32  horiz_inv = fast_rsqrt(horiz_l2);
    f32  horiz_len = horiz_l2 * horiz_inv;
    Vec3 flat_target = vec3_add(pos, horiz);
    bool grounded_h = false;
    Vec3 flat = char_slide_resolve(cc, pw, flat_target, &grounded_h);

    bool grounded = grounded_v || grounded_h;

    /* 3) Step-up: if grounded and horizontally obstructed, try up->forward->down. */
    if (horiz_len > 1e-5f && grounded) {
        Vec3 dir = vec3_scale(horiz, horiz_inv);

        Vec3 up = vec3_add(pos, vec3(0.0f, cc->step_height, 0.0f));
        bool gtmp;
        up = char_slide_resolve(cc, pw, up, &gtmp);
        Vec3 stepped = char_slide_resolve(cc, pw, vec3_add(up, horiz), &gtmp);
        bool grounded_d = false;
        Vec3 down = char_slide_resolve(cc, pw,
            vec3_add(stepped, vec3(0.0f, -cc->step_height, 0.0f)), &grounded_d);

        if (grounded_d &&
            horiz_progress(start, down, dir) > horiz_progress(start, flat, dir) + 1e-4f) {
            pos = down;
            grounded = true;
        } else {
            pos = flat;
        }
    } else {
        pos = flat;
    }

    cc->grounded = grounded;
    cc->position = pos;
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

    /* Compute swept AABB for BVH broadphase; fall back if BVH not built */
    bool use_bvh = (pw->bvh.node_count > 0);
    u32 candidates[64];
    u32 nc = 0;
    if (use_bvh) {
        Vec3 end = vec3_add(origin, delta);
        BVHAABB sweep_box;
        sweep_box.min = vec3(
            origin.e[0] < end.e[0] ? origin.e[0] : end.e[0],
            origin.e[1] < end.e[1] ? origin.e[1] : end.e[1],
            origin.e[2] < end.e[2] ? origin.e[2] : end.e[2]);
        sweep_box.max = vec3(
            origin.e[0] > end.e[0] ? origin.e[0] : end.e[0],
            origin.e[1] > end.e[1] ? origin.e[1] : end.e[1],
            origin.e[2] > end.e[2] ? origin.e[2] : end.e[2]);
        nc = bvh_query_aabb(&pw->bvh, sweep_box, candidates, 64);
    }

    u32 total = use_bvh ? nc : pw->count;

    /* Precompute inverse delta and parallel flags (saves 3 div per candidate). */
    f32 inv_delta[3];
    bool axis_parallel[3];
    for (int a = 0; a < 3; a++) {
        axis_parallel[a] = fabsf(delta.e[a]) < 0.0001f;
        inv_delta[a] = axis_parallel[a] ? 0.0f : 1.0f / delta.e[a];
    }

    for (u32 ci = 0; ci < total; ci++) {
        u32 i = use_bvh ? candidates[ci] : ci;
        if (i == ignore_body) continue;
        AABB box = aabb_from_body(&pw->bodies[i]);

        f32 tmin = 0.0f, tmax = best_t;
        bool valid = true;

        for (int axis = 0; axis < 3; axis++) {
            if (axis_parallel[axis]) {
                if (origin.e[axis] < box.min.e[axis] || origin.e[axis] > box.max.e[axis]) {
                    valid = false;
                    break;
                }
            } else {
                f32 t1 = (box.min.e[axis] - origin.e[axis]) * inv_delta[axis];
                f32 t2 = (box.max.e[axis] - origin.e[axis]) * inv_delta[axis];
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
