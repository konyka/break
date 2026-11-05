#include <physics/physics.h>
#include <core/log.h>
#include <math/simd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* SSE detection and fast_rsqrt provided by math.h via simd.h */

static bool physics_vec3_finite(Vec3 v) {
    return isfinite(v.e[0]) && isfinite(v.e[1]) && isfinite(v.e[2]);
}

static bool physics_quat_finite(Quat q) {
    return isfinite(q.e[0]) && isfinite(q.e[1]) && isfinite(q.e[2]) && isfinite(q.e[3]);
}

#ifdef PHYSICS_TEST_HOOKS
static i32 body_failure_countdown = -1;
static i32 constraint_failure_countdown = -1;
void fail_after(i32 body, i32 constraint) {
    body_failure_countdown = body;
    constraint_failure_countdown = constraint;
}
static bool physics_test_fail_body(void) {
    if (body_failure_countdown < 0) return false;
    if (body_failure_countdown == 0) return true;
    body_failure_countdown--;
    return false;
}
static bool physics_test_fail_constraint(void) {
    if (constraint_failure_countdown < 0) return false;
    if (constraint_failure_countdown == 0) return true;
    constraint_failure_countdown--;
    return false;
}
#else
static bool physics_test_fail_body(void) { return false; }
static bool physics_test_fail_constraint(void) { return false; }
#endif

AABB aabb_from_body(const RigidBody *b) {
    Vec3 ext;
    switch (b->shape) {
        case SHAPE_SPHERE:
            ext = vec3(b->radius, b->radius, b->radius);
            break;
        case SHAPE_CAPSULE:
            ext = vec3(b->radius, b->half_height + b->radius, b->radius);
            break;
        case SHAPE_BOX:
        default:
            ext = b->half_extent;
            break;
    }
    return (AABB){
        .min = vec3_sub(b->position, ext),
        .max = vec3_add(b->position, ext),
    };
}

bool aabb_overlap(AABB a, AABB b) {
#if SIMD_SSE2
    /* Use SIMD-optimized version for better performance */
    return simd_aabb_overlap_sse2(
        a.min.e, a.max.e,
        b.min.e, b.max.e) != 0;
#else
    for (int i = 0; i < 3; i++) {
        if (a.max.e[i] < b.min.e[i] || b.max.e[i] < a.min.e[i])
            return false;
    }
    return true;
#endif
}

Vec3 aabb_overlap_depth(AABB a, AABB b) {
#if MATH_SSE
    /* SSE2: compute all 3 axes in parallel using SIMD min/negate/select.
     * _mm_loadu_ps on min.e is safe (reads min[0..2]+max[0], all within struct).
     * For max.e, use _mm_set_ps to avoid reading past the struct end. */
    __m128 a_min = _mm_loadu_ps(a.min.e);
    __m128 a_max = _mm_set_ps(0.0f, a.max.e[2], a.max.e[1], a.max.e[0]);
    __m128 b_min = _mm_loadu_ps(b.min.e);
    __m128 b_max = _mm_set_ps(0.0f, b.max.e[2], b.max.e[1], b.max.e[0]);
    __m128 d1 = _mm_sub_ps(a_max, b_min);       /* a.max - b.min */
    __m128 d2 = _mm_sub_ps(b_max, a_min);       /* b.max - a.min */
    __m128 mask = _mm_cmplt_ps(d1, d2);          /* d1 < d2 */
    __m128 neg_d2 = _mm_sub_ps(_mm_setzero_ps(), d2);
    __m128 result = _mm_or_ps(
        _mm_and_ps(mask, d1),
        _mm_andnot_ps(mask, neg_d2)
    );
    Vec3 depth;
    depth.e[0] = _mm_cvtss_f32(result);
    depth.e[1] = _mm_cvtss_f32(_mm_shuffle_ps(result, result, _MM_SHUFFLE(1,1,1,1)));
    depth.e[2] = _mm_cvtss_f32(_mm_shuffle_ps(result, result, _MM_SHUFFLE(2,2,2,2)));
    return depth;
#else
    Vec3 depth = {{0, 0, 0}};
    for (int i = 0; i < 3; i++) {
        f32 d1 = a.max.e[i] - b.min.e[i];
        f32 d2 = b.max.e[i] - a.min.e[i];
        depth.e[i] = d1 < d2 ? d1 : -d2;
    }
    return depth;
#endif
}

PhysicsWorld *physics_world_create(u32 max_bodies) {
    /* Single allocation: PhysicsWorld + RigidBody[] + BVHAABB[] staging.
     * Layout: [PhysicsWorld pw][RigidBody bodies * N][BVHAABB staging * N] */
    usize pw_bytes = sizeof(PhysicsWorld);
    /* Mirror bvh.c's count_fits_size guard: on 32-bit a max_bodies near
     * UINT32_MAX overflows the size computation and the wrapped calloc would
     * hand back a block smaller than the layout below assumes. */
    if ((usize)max_bodies > (SIZE_MAX - pw_bytes) / (sizeof(RigidBody) + sizeof(BVHAABB)))
        return NULL;
    usize bodies_bytes = (usize)max_bodies * sizeof(RigidBody);
    usize stage_bytes  = (usize)max_bodies * sizeof(BVHAABB);
    u8 *block = (u8 *)calloc(1, pw_bytes + bodies_bytes + stage_bytes);
    if (!block) return NULL;
    PhysicsWorld *pw = (PhysicsWorld *)block;
    pw->capacity = max_bodies;
    pw->bodies = (RigidBody *)(block + pw_bytes);
    pw->count = 0;
    bvh_init(&pw->bvh, max_bodies);
    pw->bvh_dirty = true;
    pw->_bvh_staging = (BVHAABB *)(block + pw_bytes + bodies_bytes);
    pw->_bvh_staging_cap = max_bodies;
    return pw;
}

void physics_world_destroy(PhysicsWorld *pw) {
    if (!pw) return;
    bvh_destroy(&pw->bvh);
    /* Single free: bodies and _bvh_staging are within the same block as pw */
    free(pw);
}

static u32 physics_next_generation(u32 generation) {
    generation++;
    return generation == 0u ? 1u : generation;
}

static PhysicsBodyHandle physics_body_handle_from_slot(const PhysicsWorld *pw, u32 index) {
    PhysicsBodyHandle h = PHYSICS_BODY_HANDLE_INVALID;
    if (!pw || index >= pw->count) return h;
    h.index = index;
    h.generation = pw->bodies[index].generation;
    return h;
}

static PhysicsConstraintHandle physics_constraint_handle_from_slot(const PhysicsWorld *pw, u32 index) {
    PhysicsConstraintHandle h = PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!pw || index >= PHYSICS_MAX_CONSTRAINTS) return h;
    h.index = index;
    h.generation = pw->constraints[index].generation;
    return h;
}

RigidBody *physics_body_resolve(PhysicsWorld *pw, PhysicsBodyHandle body) {
    if (!pw || !physics_body_handle_is_valid(body) || body.index >= pw->count) return NULL;
    RigidBody *b = &pw->bodies[body.index];
    if (b->generation != body.generation || physics_body_is_parked(b)) return NULL;
    return b;
}

static DistanceConstraint *physics_constraint_resolve(PhysicsWorld *pw, PhysicsConstraintHandle handle) {
    if (!pw || !physics_constraint_handle_is_valid(handle) || handle.index >= PHYSICS_MAX_CONSTRAINTS)
        return NULL;
    DistanceConstraint *c = &pw->constraints[handle.index];
    return c->active && c->generation == handle.generation ? c : NULL;
}

void physics_body_park(PhysicsWorld *pw, PhysicsBodyHandle body) {
    RigidBody *pb = physics_body_resolve(pw, body);
    if (!pb) return;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        DistanceConstraint *c = &pw->constraints[i];
        if (!c->active) continue;
        if (physics_body_handle_equal(c->body_a, body) || physics_body_handle_equal(c->body_b, body))
            physics_constraint_remove(pw, physics_constraint_handle_from_slot(pw, i));
    }
    pb->generation = physics_next_generation(pb->generation);
    pb->is_static = true;
    pb->inv_mass = 0.0f;
    pb->velocity = vec3(0, 0, 0);
    pb->angular_velocity = vec3(0, 0, 0);
    pb->position = vec3(0, -1000.0f, 0);
    pb->spawn_frame = UINT32_MAX;
    pb->rest_frames = 0;
    pb->sleeping = true;
    if (pw->transaction_depth == 0u) {
        for (u32 i = 0; i < pw->count; i++) {
            RigidBody *other = &pw->bodies[i];
            if (!other->is_static && !physics_body_is_parked(other))
                physics_body_wake(pw, physics_body_handle_from_slot(pw, i));
        }
    }
    pw->bvh_dirty = true;
}

PhysicsBodyHandle physics_body_revive(PhysicsWorld *pw, PhysicsBodyHandle body, f32 mass, bool is_static, u32 frame) {
    if (!pw || !physics_body_handle_is_valid(body) || body.index >= pw->count || !isfinite(mass))
        return PHYSICS_BODY_HANDLE_INVALID;
    RigidBody *rb = &pw->bodies[body.index];
    if (!physics_body_is_parked(rb) && rb->generation != body.generation)
        return PHYSICS_BODY_HANDLE_INVALID;
    rb->generation = physics_next_generation(rb->generation);
    rb->mass = (mass > 0.0f) ? mass : 1.0f;
    rb->is_static = is_static;
    rb->inv_mass = (is_static || rb->mass <= 0.0f) ? 0.0f : (1.0f / rb->mass);
    rb->spawn_frame = frame;
    rb->sleeping = false;
    rb->rest_frames = 0;
    return physics_body_handle_from_slot(pw, body.index);
}

PhysicsBodyHandle physics_body_create(PhysicsWorld *pw, Vec3 pos, Vec3 half_ext, f32 mass, bool is_static, u32 frame) {
    u32 id;
    RigidBody *b;
    if (!pw || !physics_vec3_finite(pos) || !physics_vec3_finite(half_ext) || !isfinite(mass) ||
        physics_test_fail_body()) return PHYSICS_BODY_HANDLE_INVALID;
    for (int i = 0; i < 3; i++) {
        if (!(half_ext.e[i] >= 0.0f)) half_ext.e[i] = 0.0f;
    }
    for (id = 0; id < pw->count; id++) {
        RigidBody *cand = &pw->bodies[id];
        if (physics_body_is_parked(cand)) {
            b = cand;
            goto init;
        }
    }
    if (pw->count >= pw->capacity) {
        LOG_WARN("Physics body limit reached");
        return PHYSICS_BODY_HANDLE_INVALID;
    }
    id = pw->count++;
    b = &pw->bodies[id];
init:
    if (b->generation == 0u) b->generation = 1u;
    b->position = pos;
    b->velocity = vec3(0, 0, 0);
    b->acceleration = vec3(0, -9.81f, 0);
    b->half_extent = half_ext;
    b->mass = is_static ? 0.0f : mass;
    b->inv_mass = (is_static || mass <= 0.0f) ? 0.0f : (1.0f / mass);
    b->restitution = 0.3f;
    b->is_static = is_static;
    b->spawn_frame = frame;
    b->spawn_pos = pos;
    b->sleeping = false;
    b->contact_active = false;
    b->rest_frames = 0;
    b->collision_count = 0;
    b->shape = SHAPE_BOX;
    b->radius = 0.0f;
    b->half_height = 0.0f;
    b->ccd = false;
    b->orientation = (Quat){{0, 0, 0, 0}};
    b->angular_velocity = vec3(0, 0, 0);
    b->inertia_diag = vec3(0, 0, 0);
    b->step_start_position = pos;
    pw->bvh_dirty = true;
    return physics_body_handle_from_slot(pw, id);
}

PhysicsBodyHandle physics_body_create_sphere(PhysicsWorld *pw, Vec3 pos, f32 radius, f32 mass, bool is_static, u32 frame) {
    if (!pw || !isfinite(radius)) return PHYSICS_BODY_HANDLE_INVALID;
    if (!(radius >= 0.0f)) radius = 0.0f;
    PhysicsBodyHandle id = physics_body_create(pw, pos, vec3(radius, radius, radius), mass, is_static, frame);
    if (physics_body_handle_is_valid(id)) {
        RigidBody *b = &pw->bodies[id.index];
        b->shape = SHAPE_SPHERE;
        b->radius = radius;
    }
    return id;
}

PhysicsBodyHandle physics_body_create_capsule(PhysicsWorld *pw, Vec3 pos, f32 radius, f32 half_height, f32 mass, bool is_static, u32 frame) {
    if (!pw || !isfinite(radius) || !isfinite(half_height)) return PHYSICS_BODY_HANDLE_INVALID;
    if (!(radius >= 0.0f)) radius = 0.0f;
    if (!(half_height >= 0.0f)) half_height = 0.0f;
    PhysicsBodyHandle id = physics_body_create(pw, pos, vec3(radius, half_height + radius, radius), mass, is_static, frame);
    if (physics_body_handle_is_valid(id)) {
        RigidBody *b = &pw->bodies[id.index];
        b->shape = SHAPE_CAPSULE;
        b->radius = radius;
        b->half_height = half_height;
    }
    return id;
}

void physics_body_set_ccd(PhysicsWorld *pw, PhysicsBodyHandle body, bool enable) {
    RigidBody *b = physics_body_resolve(pw, body);
    if (b) b->ccd = enable;
}

void physics_set_contact_callback(PhysicsWorld *pw, PhysicsContactFn fn, void *user) {
    if (!pw) return;
    pw->on_contact   = fn;
    pw->contact_user = user;
}

bool physics_add_post_step(PhysicsWorld *pw, PhysicsPostStepFn fn, void *user) {
    if (!pw || !fn || pw->post_step_count >= PHYSICS_MAX_POST_STEPS) return false;
    pw->post_step_fn[pw->post_step_count] = fn;
    pw->post_step_user[pw->post_step_count] = user;
    pw->post_step_count++;
    return true;
}

/* ---- R435: distance constraints (position projection) ---- */

PhysicsConstraintHandle physics_constraint_add_distance(PhysicsWorld *pw, PhysicsBodyHandle body_a, PhysicsBodyHandle body_b, f32 rest_length) {
    if (physics_test_fail_constraint()) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!pw || !physics_body_resolve(pw, body_a) || !physics_body_resolve(pw, body_b) ||
        physics_body_handle_equal(body_a, body_b) || !isfinite(rest_length) || rest_length < 0.0f)
        return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (pw->constraints[i].active) continue;
        DistanceConstraint c;
        memset(&c, 0, sizeof(c));
        c.body_a = body_a;
        c.body_b = body_b;
        c.generation = pw->constraints[i].generation;
        if (c.generation == 0u) c.generation = 1u;
        c.rest_length = rest_length;
        c.active = true;
        pw->constraints[i] = c;
        pw->constraint_count++;
        return physics_constraint_handle_from_slot(pw, i);
    }
    return PHYSICS_CONSTRAINT_HANDLE_INVALID;
}

PhysicsConstraintHandle physics_constraint_add_ball(PhysicsWorld *pw, PhysicsBodyHandle body_a, PhysicsBodyHandle body_b, Vec3 anchor_a, Vec3 anchor_b) {
    if (physics_test_fail_constraint()) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!pw || !physics_body_resolve(pw, body_a) || !physics_body_resolve(pw, body_b) ||
        physics_body_handle_equal(body_a, body_b)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!physics_vec3_finite(anchor_a) || !physics_vec3_finite(anchor_b))
        return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (pw->constraints[i].active) continue;
        DistanceConstraint c;
        memset(&c, 0, sizeof(c));
        c.body_a = body_a;
        c.body_b = body_b;
        c.generation = pw->constraints[i].generation;
        if (c.generation == 0u) c.generation = 1u;
        c.offset_a = anchor_a;
        c.offset_b = anchor_b;
        c.is_ball = true;
        c.active = true;
        pw->constraints[i] = c;
        pw->constraint_count++;
        return physics_constraint_handle_from_slot(pw, i);
    }
    return PHYSICS_CONSTRAINT_HANDLE_INVALID;
}

void physics_body_set_pose(PhysicsWorld *pw, PhysicsBodyHandle body, const PhysicsPose *pose) {
    if (!pose || !physics_quat_finite(pose->orientation) ||
        !physics_vec3_finite(pose->angular_velocity) || !physics_vec3_finite(pose->inertia_diag)) return;
    RigidBody *b = physics_body_resolve(pw, body);
    if (!b) return;
    physics_body_wake(pw, body);
    b->orientation = pose->orientation;
    b->angular_velocity = pose->angular_velocity;
    b->inertia_diag = pose->inertia_diag;
}

PhysicsConstraintHandle physics_constraint_add_hinge(PhysicsWorld *pw, const HingeDesc *desc) {
    if (physics_test_fail_constraint()) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!pw || !desc) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!physics_body_resolve(pw, desc->body_a) || !physics_body_resolve(pw, desc->body_b))
        return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (physics_body_handle_equal(desc->body_a, desc->body_b)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!(desc->limit_min <= desc->limit_max)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    f32 axis_len2 = vec3_dot(desc->axis_local_a, desc->axis_local_a);
    if (!(axis_len2 > 1e-8f)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    for (int i = 0; i < 3; i++) {
        if (!isfinite(desc->anchor_local_a.e[i]) || !isfinite(desc->anchor_local_b.e[i]) ||
            !isfinite(desc->axis_local_a.e[i])) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    }
    if (!isfinite(desc->limit_min) || !isfinite(desc->limit_max)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    f32 inv = 1.0f / sqrtf(axis_len2);
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (!pw->constraints[i].active) {
            pw->constraints[i].body_a = desc->body_a;
            pw->constraints[i].body_b = desc->body_b;
            pw->constraints[i].rest_length = 0.0f;
            pw->constraints[i].offset_a = desc->anchor_local_a;
            pw->constraints[i].offset_b = desc->anchor_local_b;
            pw->constraints[i].is_ball = false;
            pw->constraints[i].is_hinge = true;
            pw->constraints[i].is_slider = false;
            pw->constraints[i].hinge_axis = vec3_scale(desc->axis_local_a, inv);
            pw->constraints[i].limit_min = desc->limit_min;
            pw->constraints[i].limit_max = desc->limit_max;
            if (pw->constraints[i].generation == 0u) pw->constraints[i].generation = 1u;
            pw->constraints[i].active = true;
            pw->constraint_count++;
            return physics_constraint_handle_from_slot(pw, i);
        }
    }
    return PHYSICS_CONSTRAINT_HANDLE_INVALID;
}

PhysicsConstraintHandle physics_constraint_add_slider(PhysicsWorld *pw, const SliderDesc *desc) {
    if (physics_test_fail_constraint()) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!pw || !desc) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!physics_body_resolve(pw, desc->body_a) || !physics_body_resolve(pw, desc->body_b))
        return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (physics_body_handle_equal(desc->body_a, desc->body_b)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!(desc->limit_min <= desc->limit_max)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    f32 axis_len2 = vec3_dot(desc->axis_local_a, desc->axis_local_a);
    if (!(axis_len2 > 1e-8f)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    for (int i = 0; i < 3; i++) {
        if (!isfinite(desc->anchor_local_a.e[i]) || !isfinite(desc->anchor_local_b.e[i]) ||
            !isfinite(desc->axis_local_a.e[i])) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    }
    if (!isfinite(desc->limit_min) || !isfinite(desc->limit_max)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    f32 inv = 1.0f / sqrtf(axis_len2);
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (!pw->constraints[i].active) {
            pw->constraints[i].body_a = desc->body_a;
            pw->constraints[i].body_b = desc->body_b;
            pw->constraints[i].rest_length = 0.0f;
            pw->constraints[i].offset_a = desc->anchor_local_a;
            pw->constraints[i].offset_b = desc->anchor_local_b;
            pw->constraints[i].is_ball = false;
            pw->constraints[i].is_hinge = false;
            pw->constraints[i].is_slider = true;
            pw->constraints[i].hinge_axis = vec3_scale(desc->axis_local_a, inv);
            pw->constraints[i].limit_min = desc->limit_min;
            pw->constraints[i].limit_max = desc->limit_max;
            pw->constraints[i].slider_torsion = 1.0f;
            pw->constraints[i].slider_damping = 1.0f;
            pw->constraints[i].slider_stiffness = 100.0f;
            if (pw->constraints[i].generation == 0u) pw->constraints[i].generation = 1u;
            pw->constraints[i].active = true;
            pw->constraint_count++;
            return physics_constraint_handle_from_slot(pw, i);
        }
    }
    return PHYSICS_CONSTRAINT_HANDLE_INVALID;
}

static Quat rigid_orientation(const RigidBody *b);

PhysicsConstraintHandle physics_constraint_add_cone_twist(PhysicsWorld *pw, const ConeTwistDesc *desc) {
    if (physics_test_fail_constraint()) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    const f32 pi = 3.14159265358979323846f;
    if (!pw || !desc) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (!physics_body_resolve(pw, desc->body_a) || !physics_body_resolve(pw, desc->body_b))
        return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (physics_body_handle_equal(desc->body_a, desc->body_b)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    for (int i = 0; i < 3; i++) {
        if (!isfinite(desc->anchor_local_a.e[i]) || !isfinite(desc->anchor_local_b.e[i]) ||
            !isfinite(desc->axis_local_a.e[i]) || !isfinite(desc->axis_local_b.e[i]))
            return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    }
    if (!isfinite(desc->swing_min) || !isfinite(desc->swing_max) ||
        !isfinite(desc->twist_min) || !isfinite(desc->twist_max)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (desc->swing_min < 0.0f || desc->swing_min > desc->swing_max || desc->swing_max > pi)
        return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    if (desc->twist_min < -pi || desc->twist_min > desc->twist_max || desc->twist_max > pi)
        return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    f32 len_a = vec3_dot(desc->axis_local_a, desc->axis_local_a);
    f32 len_b = vec3_dot(desc->axis_local_b, desc->axis_local_b);
    if (!(len_a > 1e-8f) || !(len_b > 1e-8f)) return PHYSICS_CONSTRAINT_HANDLE_INVALID;
    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        if (pw->constraints[i].active) continue;
        DistanceConstraint c;
        memset(&c, 0, sizeof(c));
        c.body_a = desc->body_a;
        c.body_b = desc->body_b;
        c.generation = pw->constraints[i].generation;
        if (c.generation == 0u) c.generation = 1u;
        c.offset_a = desc->anchor_local_a;
        c.offset_b = desc->anchor_local_b;
        c.is_cone_twist = true;
        c.hinge_axis = vec3_scale(desc->axis_local_a, 1.0f / sqrtf(len_a));
        c.cone_axis_b = vec3_scale(desc->axis_local_b, 1.0f / sqrtf(len_b));
        c.reference_a = rigid_orientation(&pw->bodies[desc->body_a.index]);
        c.reference_b = rigid_orientation(&pw->bodies[desc->body_b.index]);
        c.swing_min = desc->swing_min;
        c.swing_max = desc->swing_max;
        c.twist_min = desc->twist_min;
        c.twist_max = desc->twist_max;
        c.active = true;
        pw->constraints[i] = c;
        pw->constraint_count++;
        return physics_constraint_handle_from_slot(pw, i);
    }
    return PHYSICS_CONSTRAINT_HANDLE_INVALID;
}

void physics_constraint_set_slider_torsion(PhysicsWorld *pw, PhysicsConstraintHandle constraint, f32 torsion) {
    DistanceConstraint *c = physics_constraint_resolve(pw, constraint);
    if (!c || !c->is_slider || !isfinite(torsion)) return;
    if (torsion < 0.0f) torsion = 0.0f;
    if (torsion > 1.0f) torsion = 1.0f;
    c->slider_torsion = torsion;
}

void physics_constraint_set_slider_damping(PhysicsWorld *pw, PhysicsConstraintHandle constraint, f32 damping) {
    DistanceConstraint *c = physics_constraint_resolve(pw, constraint);
    if (!c || !c->is_slider || !isfinite(damping)) return;
    if (damping < 0.0f) damping = 0.0f;
    if (damping > 1.0f) damping = 1.0f;
    c->slider_damping = damping;
}

void physics_constraint_set_slider_stiffness(PhysicsWorld *pw, PhysicsConstraintHandle constraint, f32 stiffness) {
    DistanceConstraint *c = physics_constraint_resolve(pw, constraint);
    if (!c || !c->is_slider || !isfinite(stiffness) || stiffness < 0.0f) return;
    if (stiffness > 1.0e6f) stiffness = 1.0e6f;
    c->slider_stiffness = stiffness;
}

static Quat rigid_orientation(const RigidBody *b) {
    f32 l2 = b->orientation.e[0] * b->orientation.e[0] + b->orientation.e[1] * b->orientation.e[1] +
             b->orientation.e[2] * b->orientation.e[2] + b->orientation.e[3] * b->orientation.e[3];
    if (l2 <= 1e-12f) return QUAT_IDENTITY;
    return quat_normalize(b->orientation);
}

static void integrate_orientation(RigidBody *b, f32 dt) {
    if (!b || b->is_static) return;
    Quat q = rigid_orientation(b);
    Vec3 local = quat_rotate_vec3(quat_inverse(q), b->angular_velocity);
    if (b->inertia_diag.e[0] == 0.0f) local.e[0] = 0.0f;
    if (b->inertia_diag.e[1] == 0.0f) local.e[1] = 0.0f;
    if (b->inertia_diag.e[2] == 0.0f) local.e[2] = 0.0f;
    Vec3 w = quat_rotate_vec3(q, local);
    f32 wlen = vec3_len(w);
    if (wlen <= 1e-8f) return;
    Quat dq = quat_from_axis_angle(w, wlen * dt);
    b->orientation = quat_normalize(quat_mul(dq, rigid_orientation(b)));
}

static f32 hinge_twist(Quat qa, Quat qb, Vec3 axis_local) {
    Quat rel = quat_mul(quat_inverse(qa), qb);
    f32 dot = rel.e[0] * axis_local.e[0] + rel.e[1] * axis_local.e[1] + rel.e[2] * axis_local.e[2];
    return 2.0f * atan2f(dot, rel.e[3]);
}

static void clamp_hinge(RigidBody *a, RigidBody *b, const DistanceConstraint *c) {
    if (c->limit_min == 0.0f && c->limit_max == 0.0f) return;
    if (b->inv_mass <= 0.0f) return;
    Quat qa = rigid_orientation(a);
    Quat qb = rigid_orientation(b);
    f32 angle = hinge_twist(qa, qb, c->hinge_axis);
    f32 limited = angle;
    if (limited > c->limit_max) limited = c->limit_max;
    if (limited < c->limit_min) limited = c->limit_min;
    if (limited == angle) return;
    b->sleeping = false;
    b->rest_frames = 0;
    b->orientation = quat_normalize(quat_mul(qa, quat_from_axis_angle(c->hinge_axis, limited)));
    Vec3 axis_w = quat_rotate_vec3(qa, c->hinge_axis);
    f32 along = vec3_dot(b->angular_velocity, axis_w);
    if ((angle > c->limit_max && along > 0.0f) || (angle < c->limit_min && along < 0.0f)) {
        b->angular_velocity = vec3_sub(b->angular_velocity, vec3_scale(axis_w, along));
    }
}

static f32 cone_angular_weight(const RigidBody *b, Vec3 axis_w) {
    if (b->inv_mass <= 0.0f) return 0.0f;
    Quat q = rigid_orientation(b);
    Vec3 n = quat_rotate_vec3(quat_inverse(q), axis_w);
    f32 weight = 0.0f;
    for (int i = 0; i < 3; i++) {
        if (b->inertia_diag.e[i] > 0.0f)
            weight += n.e[i] * n.e[i] / b->inertia_diag.e[i];
    }
    return weight;
}

static void cone_clip_outward_velocity(RigidBody *a, RigidBody *b, Vec3 axis) {
    f32 wa = cone_angular_weight(a, axis);
    f32 wb = cone_angular_weight(b, axis);
    f32 total = wa + wb;
    if (total <= 1e-12f) return;
    Vec3 rel = vec3_sub(b->angular_velocity, a->angular_velocity);
    f32 speed = vec3_dot(rel, axis);
    if (speed >= 0.0f) return;
    if (wa > 0.0f)
        a->angular_velocity = vec3_add(a->angular_velocity, vec3_scale(axis, speed * wa / total));
    if (wb > 0.0f)
        b->angular_velocity = vec3_sub(b->angular_velocity, vec3_scale(axis, speed * wb / total));
}

static void cone_apply_angular_delta(RigidBody *a, RigidBody *b, Vec3 axis, f32 angle) {
    if (!(angle > 1e-8f)) return;
    f32 wa = cone_angular_weight(a, axis);
    f32 wb = cone_angular_weight(b, axis);
    f32 total = wa + wb;
    if (total <= 1e-12f) return;
    cone_clip_outward_velocity(a, b, axis);
    if (wa > 0.0f) {
        Quat q = rigid_orientation(a);
        Quat delta = quat_from_axis_angle(axis, -angle * wa / total);
        a->orientation = quat_normalize(quat_mul(delta, q));
        a->sleeping = false; a->rest_frames = 0;
    }
    if (wb > 0.0f) {
        Quat q = rigid_orientation(b);
        Quat delta = quat_from_axis_angle(axis, angle * wb / total);
        b->orientation = quat_normalize(quat_mul(delta, q));
        b->sleeping = false; b->rest_frames = 0;
    }
}

static Vec3 cone_perpendicular(Vec3 axis) {
    Vec3 helper = fabsf(axis.e[0]) < 0.9f ? vec3(1, 0, 0) : vec3(0, 1, 0);
    return vec3_normalize(vec3_cross(axis, helper));
}

static Quat cone_relative_twist(const DistanceConstraint *c, Quat qa, Quat qb) {
    Quat current = quat_mul(quat_inverse(qa), qb);
    Quat reference = quat_mul(quat_inverse(c->reference_a), c->reference_b);
    Quat rel = quat_mul(current, quat_inverse(reference));
    if (rel.e[3] < 0.0f) {
        for (int i = 0; i < 4; i++) rel.e[i] = -rel.e[i];
    }
    return rel;
}

static void clamp_cone_twist(RigidBody *a, RigidBody *b, const DistanceConstraint *c) {
    const f32 pi = 3.14159265358979323846f;
    Quat qa = rigid_orientation(a);
    Quat qb = rigid_orientation(b);
    Vec3 axis_a = quat_rotate_vec3(qa, c->hinge_axis);
    Vec3 axis_b = quat_rotate_vec3(qb, c->cone_axis_b);
    Vec3 cross = vec3_cross(axis_b, axis_a);
    f32 sine = vec3_len(cross);
    f32 angle = atan2f(sine, vec3_dot(axis_a, axis_b));
    if (angle > c->swing_max) {
        Vec3 axis = sine > 1e-8f ? vec3_scale(cross, 1.0f / sine) : cone_perpendicular(axis_a);
        cone_apply_angular_delta(a, b, axis, angle - c->swing_max);
    } else if (angle < c->swing_min) {
        Vec3 axis = sine > 1e-8f ? vec3_scale(cross, -1.0f / sine) : cone_perpendicular(axis_a);
        cone_apply_angular_delta(a, b, axis, c->swing_min - angle);
    }

    qa = rigid_orientation(a);
    qb = rigid_orientation(b);
    axis_a = quat_rotate_vec3(qa, c->hinge_axis);
    Quat rel = cone_relative_twist(c, qa, qb);
    Vec3 imag = vec3(rel.e[0], rel.e[1], rel.e[2]);
    f32 twist = 2.0f * atan2f(vec3_dot(imag, c->hinge_axis), rel.e[3]);
    if (twist > pi) twist -= 2.0f * pi;
    if (twist < -pi) twist += 2.0f * pi;
    if (twist > c->twist_max) {
        cone_apply_angular_delta(a, b, vec3_scale(axis_a, -1.0f), twist - c->twist_max);
    } else if (twist < c->twist_min) {
        cone_apply_angular_delta(a, b, axis_a, c->twist_min - twist);
    }
}

void physics_constraint_remove(PhysicsWorld *pw, PhysicsConstraintHandle constraint) {
    DistanceConstraint *c = physics_constraint_resolve(pw, constraint);
    if (!c) return;
    RigidBody *a = physics_body_resolve(pw, c->body_a);
    RigidBody *b = physics_body_resolve(pw, c->body_b);
    if (a && a->inv_mass > 0.0f) {
        a->sleeping = false;
        a->rest_frames = 0;
    }
    if (b && b->inv_mass > 0.0f) {
        b->sleeping = false;
        b->rest_frames = 0;
    }
    u32 generation = physics_next_generation(c->generation);
    memset(c, 0, sizeof(*c));
    c->generation = generation;
    pw->constraint_count--;
}

u32 physics_constraint_count(const PhysicsWorld *pw) {
    return pw ? pw->constraint_count : 0u;
}

/* Gauss-Seidel projection with a small fixed iteration count. Linear correction
 * is split by inverse mass; cone-twist angular correction uses effective inverse
 * inertia. The translational velocity pass runs once after this pass. */
static void solve_distance_constraints(PhysicsWorld *pw) {
    if (pw->constraint_count == 0) return;
    for (int iter = 0; iter < 4; iter++) {
        for (u32 ci = 0; ci < PHYSICS_MAX_CONSTRAINTS; ci++) {
            DistanceConstraint *c = &pw->constraints[ci];
            if (!c->active) continue;
            RigidBody *a = physics_body_resolve(pw, c->body_a);
            RigidBody *b = physics_body_resolve(pw, c->body_b);
            if (!a || !b) continue;
            f32 inv_a = a->inv_mass;
            f32 inv_b = b->inv_mass;
            f32 inv_total = inv_a + inv_b;
            if (inv_total <= 0.0f) continue; /* both static: nothing can move */
            /* R443: constraints bind at anchor points, not centroids. For
             * distance constraints the offsets are zero, so pa/pb ARE the
             * centroids and the math below is unchanged from R435. */
            /* Anchors are local. A zero orientation is identity, so existing
             * distance and ball constraints keep their previous world offsets. */
            Vec3 pa = vec3_add(a->position, quat_rotate_vec3(rigid_orientation(a), c->offset_a));
            Vec3 pb = vec3_add(b->position, quat_rotate_vec3(rigid_orientation(b), c->offset_b));
            if (c->is_slider) {
                Vec3 axis = quat_rotate_vec3(rigid_orientation(a), c->hinge_axis);
                Vec3 delta = vec3_sub(pb, pa);
                f32 along = vec3_dot(delta, axis);
                Vec3 perp = vec3_sub(delta, vec3_scale(axis, along));
                Vec3 corr = vec3_scale(perp, 1.0f / inv_total);
                bool moved = vec3_dot(perp, perp) > 1e-16f;
                if (inv_a > 0.0f && moved) {
                    a->position = vec3_add(a->position, vec3_scale(corr, inv_a));
                    a->sleeping = false; a->rest_frames = 0;
                }
                if (inv_b > 0.0f && moved) {
                    b->position = vec3_sub(b->position, vec3_scale(corr, inv_b));
                    b->sleeping = false; b->rest_frames = 0;
                }
                if (!(c->limit_min == 0.0f && c->limit_max == 0.0f)) {
                    f32 target = along;
                    if (target < c->limit_min) target = c->limit_min;
                    if (target > c->limit_max) target = c->limit_max;
                    f32 err = along - target;
                    Vec3 along_corr = vec3_scale(axis, err / inv_total);
                    moved = fabsf(err) > 1e-8f;
                    if (inv_a > 0.0f && moved) {
                        a->position = vec3_add(a->position, vec3_scale(along_corr, inv_a));
                        a->sleeping = false; a->rest_frames = 0;
                    }
                    if (inv_b > 0.0f && moved) {
                        b->position = vec3_sub(b->position, vec3_scale(along_corr, inv_b));
                        b->sleeping = false; b->rest_frames = 0;
                    }
                }
                continue;
            }
            if (c->is_ball || c->is_hinge || c->is_cone_twist) {
                /* Pull anchors to coincidence with a full 3-axis correction.
                 * The centroid correction is linear; hinge and cone-twist
                 * angular limits are applied separately below. */
                Vec3 err = vec3_sub(pb, pa);
                Vec3 corr = vec3_scale(err, 1.0f / inv_total);
                bool moved = vec3_dot(err, err) > 1e-16f;
                if (inv_a > 0.0f && moved) {
                    a->position = vec3_add(a->position, vec3_scale(corr, inv_a));
                    a->sleeping = false; a->rest_frames = 0;
                }
                if (inv_b > 0.0f && moved) {
                    b->position = vec3_sub(b->position, vec3_scale(corr, inv_b));
                    b->sleeping = false; b->rest_frames = 0;
                }
                if (c->is_hinge) clamp_hinge(a, b, c);
                if (c->is_cone_twist) clamp_cone_twist(a, b, c);
                continue;
            }
            Vec3 d = vec3_sub(pb, pa);
            f32 len2 = vec3_dot(d, d);
            if (len2 < 1e-12f) continue;     /* coincident: no defined axis */
            f32 len = sqrtf(len2);
            f32 err = len - c->rest_length;
            Vec3 n = vec3_scale(d, 1.0f / len);
            f32 corr = err / inv_total;
            bool moved = fabsf(err) > 1e-8f;
            if (inv_a > 0.0f && moved) {
                a->position = vec3_add(a->position, vec3_scale(n, corr * inv_a));
                a->sleeping = false; a->rest_frames = 0; /* R432 pattern: we moved it, so the BVH
                                     * refit passes must not skip its AABB. */
            }
            if (inv_b > 0.0f && moved) {
                b->position = vec3_sub(b->position, vec3_scale(n, corr * inv_b));
                b->sleeping = false; b->rest_frames = 0;
            }
        }
    }
}

/* R440: velocity-level pass for distance constraints, run ONCE per step
 * after the position projection above (R435 left velocities untouched, so a
 * taut constraint kept its axial relative velocity and jittered as the
 * position pass dragged the bodies back every frame).
 *
 * For each constraint with axis n = normalize(pb - pa) we remove the axial
 * relative velocity rel = dot(vb - va, n) with an impulse split by inverse
 * mass, exactly like the position split (and resolve_contact):
 *     j  = -rel / (inv_a + inv_b)
 *     va -= j * inv_a * n;  vb += j * inv_b * n
 * Static ends (inv_mass 0) absorb nothing, so a free end anchored to a
 * static body loses ALL of its axial velocity. Tangential components are
 * untouched, so swinging motion is undamped.
 *
 * Softening: we eliminate rel fully (factor 1.0) rather than scaling by a
 * 0..1 coefficient. The constraint is bilateral (rope AND rod), the impulse
 * is unconditionally stable (it can only remove energy along the axis), and
 * partial elimination would just re-introduce the R435 drift over more
 * frames. Velocities produced by THIS step's integration (gravity along the
 * axis etc.) are removed here; external forces re-enter on the next step's
 * integration, which is the standard sequential-impulse semantic.
 *
 * Nonzero corrections wake sleeping endpoints. Stable supported contacts may
 * sleep after the unified end-of-step evaluation. */
static void wake_if_sleeping(RigidBody *b) {
    if (!b->sleeping) return;
    b->sleeping = false;
    b->rest_frames = 0;
}

static void solve_distance_constraint_velocities(PhysicsWorld *pw) {
    if (pw->constraint_count == 0) return;
    for (u32 ci = 0; ci < PHYSICS_MAX_CONSTRAINTS; ci++) {
        DistanceConstraint *c = &pw->constraints[ci];
        if (!c->active) continue;
        RigidBody *a = physics_body_resolve(pw, c->body_a);
        RigidBody *b = physics_body_resolve(pw, c->body_b);
        if (!a || !b) continue;
        f32 inv_a = a->inv_mass;
        f32 inv_b = b->inv_mass;
        f32 inv_total = inv_a + inv_b;
        if (inv_total <= 0.0f) continue;
        if (c->is_slider) {
            Vec3 axis = quat_rotate_vec3(rigid_orientation(a), c->hinge_axis);
            Vec3 rel = vec3_sub(b->velocity, a->velocity);
            f32 along = vec3_dot(rel, axis);
            Vec3 perp = vec3_sub(rel, vec3_scale(axis, along));
            Vec3 j = vec3_scale(perp, 1.0f / inv_total);
            if (inv_a > 0.0f && vec3_dot(j, j) > 1e-16f) wake_if_sleeping(a);
            if (inv_b > 0.0f && vec3_dot(j, j) > 1e-16f) wake_if_sleeping(b);
            if (inv_a > 0.0f) a->velocity = vec3_add(a->velocity, vec3_scale(j, inv_a));
            if (inv_b > 0.0f) b->velocity = vec3_sub(b->velocity, vec3_scale(j, inv_b));
            continue;
        }
        if (c->is_ball || c->is_hinge || c->is_cone_twist) {
            Vec3 rel = vec3_sub(b->velocity, a->velocity);
            Vec3 j = vec3_scale(rel, 1.0f / inv_total);
            if (inv_a > 0.0f && vec3_dot(j, j) > 1e-16f) wake_if_sleeping(a);
            if (inv_b > 0.0f && vec3_dot(j, j) > 1e-16f) wake_if_sleeping(b);
            if (inv_a > 0.0f) a->velocity = vec3_add(a->velocity, vec3_scale(j, inv_a));
            if (inv_b > 0.0f) b->velocity = vec3_sub(b->velocity, vec3_scale(j, inv_b));
            continue;
        }
        Vec3 d = vec3_sub(b->position, a->position);
        f32 len2 = vec3_dot(d, d);
        if (len2 < 1e-12f) continue;
        Vec3 n = vec3_scale(d, 1.0f / sqrtf(len2));
        f32 rel = vec3_dot(vec3_sub(b->velocity, a->velocity), n);
        f32 j = -rel / inv_total;
        if (inv_a > 0.0f && fabsf(j) > 1e-8f) wake_if_sleeping(a);
        if (inv_b > 0.0f && fabsf(j) > 1e-8f) wake_if_sleeping(b);
        if (inv_a > 0.0f) a->velocity = vec3_sub(a->velocity, vec3_scale(n, j * inv_a));
        if (inv_b > 0.0f) b->velocity = vec3_add(b->velocity, vec3_scale(n, j * inv_b));
    }
}

void physics_body_wake(PhysicsWorld *pw, PhysicsBodyHandle body) {
    RigidBody *b = physics_body_resolve(pw, body);
    if (!b) return;
    b->sleeping = false;
    b->rest_frames = 0;
}

void physics_body_apply_impulse(PhysicsWorld *pw, PhysicsBodyHandle body, Vec3 impulse) {
    if (!physics_vec3_finite(impulse)) return;
    RigidBody *b = physics_body_resolve(pw, body);
    if (!b || b->is_static || b->inv_mass <= 0.0f) return;
    physics_body_wake(pw, body);
    b->velocity.e[0] += impulse.e[0] * b->inv_mass;
    b->velocity.e[1] += impulse.e[1] * b->inv_mass;
    b->velocity.e[2] += impulse.e[2] * b->inv_mass;
    pw->total_impulse_applied += vec3_len(impulse);
}

void physics_push_body(PhysicsWorld *pw, PhysicsBodyHandle body, Vec3 normal, f32 depth) {
    if (!physics_vec3_finite(normal) || !isfinite(depth)) return;
    RigidBody *b = physics_body_resolve(pw, body);
    if (!b || b->inv_mass <= 0.0f) return;
    b->position.e[0] += normal.e[0] * depth;
    b->position.e[1] += normal.e[1] * depth;
    b->position.e[2] += normal.e[2] * depth;
    /* R432 contract: we moved it, so the BVH refit passes (which skip
     * rest_frames > 2) must not keep its stale AABB. */
    b->sleeping = false; b->rest_frames = 0;
}

/* Approach speed (m/s, along the contact normal) below which a contact does
 * not bounce. 3 m/s is a ~0.46 m drop under gravity. */
#define RESTITUTION_VEL_THRESHOLD 3.0f

static void resolve_contact(RigidBody *a, RigidBody *b, Vec3 normal, f32 depth) {
    f32 inv_a = a->inv_mass;
    f32 inv_b = b->inv_mass;
    f32 total_inv_mass = inv_a + inv_b;
    if (total_inv_mass <= 0.0f) return;
    Vec3 initial_rel = vec3_sub(a->velocity, b->velocity);
    if (vec3_dot(initial_rel, initial_rel) <= 1e-12f &&
        ((a->sleeping && b->is_static) || (b->sleeping && a->is_static) ||
         (a->sleeping && b->sleeping))) return;

    /* Precompute reciprocal to replace 3 divisions with multiplications. */
    f32 inv_total = 1.0f / total_inv_mass;

    if (inv_a > 0.0f) {
        wake_if_sleeping(a);
        f32 ratio = inv_a * inv_total;
        a->position.e[0] -= normal.e[0] * depth * ratio;
        a->position.e[1] -= normal.e[1] * depth * ratio;
        a->position.e[2] -= normal.e[2] * depth * ratio;
    }
    if (inv_b > 0.0f) {
        wake_if_sleeping(b);
        f32 ratio = inv_b * inv_total;
        b->position.e[0] += normal.e[0] * depth * ratio;
        b->position.e[1] += normal.e[1] * depth * ratio;
        b->position.e[2] += normal.e[2] * depth * ratio;
    }

    Vec3 rel_vel = vec3_sub(a->velocity, b->velocity);
    f32 vel_along_normal = vec3_dot(rel_vel, normal);
    /* R262 (CORRECTNESS): `normal` points from A to B (physics.h; the position
     * split above moves A by -normal and B by +normal to separate them, which is
     * only correct for an A->B normal). With rel_vel = v_a - v_b, the bodies are
     * APPROACHING along the contact when dot(rel_vel, normal) > 0 (A advancing
     * toward B and/or B advancing toward A), and separating when it is < 0. The
     * normal impulse must be applied on approach and skipped on separation. The
     * guard was inverted (`> 0` → return), so it bailed out exactly when the
     * bodies were closing: the normal impulse and restitution were never applied
     * to a real collision (only the position push ran), so dynamic bodies passed
     * their approach velocity straight through contacts — no stopping, no bounce,
     * no normal momentum exchange. Skip only when already separating. */
    if (vel_along_normal < 0.0f) return;

    f32 e = a->restitution < b->restitution ? a->restitution : b->restitution;
    /* R696: restitution velocity threshold. A body landing at modest speed
     * bounced 3-4 times (rest_frames never advanced past 0 and the demo's
     * falling bodies visibly jittered on the ground: with e = 0.3 each bounce
     * leaves 30% of the approach speed, and gravity re-accelerates it into the
     * next contact). Impacts below RESTITUTION_VEL_THRESHOLD are perfectly
     * inelastic (e = 0); harder impacts keep the full bounce. */
    if (vel_along_normal < RESTITUTION_VEL_THRESHOLD) e = 0.0f;
    f32 j = -(1.0f + e) * vel_along_normal * inv_total;

    Vec3 impulse = vec3_scale(normal, j);
    if (inv_a > 0.0f) {
        a->velocity.e[0] += impulse.e[0] * inv_a;
        a->velocity.e[1] += impulse.e[1] * inv_a;
        a->velocity.e[2] += impulse.e[2] * inv_a;
    }
    if (inv_b > 0.0f) {
        b->velocity.e[0] -= impulse.e[0] * inv_b;
        b->velocity.e[1] -= impulse.e[1] * inv_b;
        b->velocity.e[2] -= impulse.e[2] * inv_b;
    }
}

/* ---- Narrowphase geometry helpers ---- */

/* Bit-exact position-change test for rest detection (CORRECTNESS): the old
 * rule incremented rest_frames whenever speed^2 < 0.0025 (|v| < 0.05 m/s),
 * while integration still advanced p += v*dt every frame. A sustained
 * sub-threshold creep (verified: 0.04 m/s for 60 s = 2.35 m drift) left the
 * BVH leaf frozen forever — both refit passes skip rest_frames > 2 — and the
 * body ghosted through walls. Rest now requires the position to be
 * bit-unchanged this step; that also makes the recomputed AABB bit-identical,
 * so the refit skip is exact rather than heuristic. Truly idle bodies still
 * reach rest: damping (0.98/frame) shrinks v*dt below the float ulp of the
 * position, at which point p stops changing. Supported contacts also require
 * near-zero final speed; non-support contacts with pre-contact motion stay awake. */
static bool vec3_moved(Vec3 a, Vec3 b) {
    return (a.e[0] != b.e[0]) || (a.e[1] != b.e[1]) || (a.e[2] != b.e[2]);
}

static void update_sleep_state(RigidBody *b, Vec3 old_position) {
    f32 speed2 = vec3_dot(b->velocity, b->velocity);
    f32 spin2 = vec3_dot(b->angular_velocity, b->angular_velocity);
    bool supported = b->contact_active && vec3_dot(b->acceleration, b->contact_normal) > 1e-8f;
    bool moving_contact = b->contact_active && !supported && b->contact_speed2 > 1e-8f;
    f32 speed_limit = supported ? 1e-8f : 0.0025f;
    if (!moving_contact && speed2 < speed_limit && spin2 < 0.0025f &&
        !vec3_moved(b->position, old_position)) {
        b->rest_frames++;
        if (b->rest_frames >= 60u) {
            b->sleeping = true;
            b->velocity = vec3(0, 0, 0);
            b->angular_velocity = vec3(0, 0, 0);
        }
    } else {
        b->sleeping = false;
        b->rest_frames = 0;
    }
}

static f32 clampf01(f32 v) {
    if (v < 0.0f) return 0.0f;
    if (v > 1.0f) return 1.0f;
    return v;
}

static Vec3 closest_on_segment(Vec3 a, Vec3 b, Vec3 p, f32 *out_t) {
    Vec3 ab = vec3_sub(b, a);
    f32 denom = vec3_dot(ab, ab);
    f32 inv_denom = (denom > 1e-12f) ? 1.0f / denom : 0.0f;
    f32 t = vec3_dot(vec3_sub(p, a), ab) * inv_denom;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    if (out_t) *out_t = t;
    return vec3_add(a, vec3_scale(ab, t));
}

/* Closest points between segments [p1,q1] and [p2,q2] (Ericson, RTCD). */
static void closest_seg_seg(Vec3 p1, Vec3 q1, Vec3 p2, Vec3 q2, Vec3 *c1, Vec3 *c2) {
    Vec3 d1 = vec3_sub(q1, p1);
    Vec3 d2 = vec3_sub(q2, p2);
    Vec3 r  = vec3_sub(p1, p2);
    f32 a = vec3_dot(d1, d1);
    f32 e = vec3_dot(d2, d2);
    f32 f = vec3_dot(d2, r);
    f32 s, t;
    /* Precompute reciprocals to replace 6 divisions with multiplications. */
    f32 inv_a = (a > 1e-12f) ? 1.0f / a : 0.0f;
    f32 inv_e = (e > 1e-12f) ? 1.0f / e : 0.0f;
    if (a <= 1e-12f && e <= 1e-12f) {
        s = 0.0f; t = 0.0f;
    } else if (a <= 1e-12f) {
        s = 0.0f;
        t = clampf01(f * inv_e);
    } else {
        f32 c = vec3_dot(d1, r);
        if (e <= 1e-12f) {
            t = 0.0f;
            s = clampf01(-c * inv_a);
        } else {
            f32 b = vec3_dot(d1, d2);
            f32 denom = a * e - b * b;
            f32 inv_denom = (denom > 1e-12f) ? 1.0f / denom : 0.0f;
            s = denom > 1e-12f ? clampf01((b * f - c * e) * inv_denom) : 0.0f;
            t = (b * s + f) * inv_e;
            if (t < 0.0f) {
                t = 0.0f;
                s = clampf01(-c * inv_a);
            } else if (t > 1.0f) {
                t = 1.0f;
                s = clampf01((b - c) * inv_a);
            }
        }
    }
    *c1 = vec3_add(p1, vec3_scale(d1, s));
    *c2 = vec3_add(p2, vec3_scale(d2, t));
}

static Vec3 closest_on_aabb(AABB box, Vec3 p) {
    Vec3 r;
    for (int i = 0; i < 3; i++) {
        f32 v = p.e[i];
        if (v < box.min.e[i]) v = box.min.e[i];
        if (v > box.max.e[i]) v = box.max.e[i];
        r.e[i] = v;
    }
    return r;
}

/* Slab test: does segment [a0,a1] intersect the AABB? */
static bool segment_intersects_aabb(Vec3 a0, Vec3 a1, AABB ab) {
    Vec3 d = vec3_sub(a1, a0);
    f32 tmin = 0.0f, tmax = 1.0f;
    for (int i = 0; i < 3; i++) {
        if (fabsf(d.e[i]) < 1e-12f) {
            if (a0.e[i] < ab.min.e[i] || a0.e[i] > ab.max.e[i]) return false;
        } else {
            f32 inv = 1.0f / d.e[i];
            f32 t1 = (ab.min.e[i] - a0.e[i]) * inv;
            f32 t2 = (ab.max.e[i] - a0.e[i]) * inv;
            if (t1 > t2) { f32 tmp = t1; t1 = t2; t2 = tmp; }
            if (t1 > tmin) tmin = t1;
            if (t2 < tmax) tmax = t2;
            if (tmin > tmax) return false;
        }
    }
    return true;
}

static void capsule_segment(const RigidBody *b, Vec3 *bottom, Vec3 *top) {
    Vec3 up = vec3(0, b->half_height, 0);
    *bottom = vec3_sub(b->position, up);
    *top    = vec3_add(b->position, up);
}

static int shape_rank(ShapeType s) {
    return (s == SHAPE_SPHERE) ? 0 : (s == SHAPE_CAPSULE) ? 1 : 2;
}

/* Sphere centered at `c` with radius `r` vs solid box: resolve contact.
 * Returns normal pointing from sphere toward box. */
static bool sphere_vs_box(Vec3 c, f32 r, const RigidBody *box,
                          Vec3 *n, f32 *depth, Vec3 *pt) {
    AABB ab = aabb_from_body(box);
    Vec3 cp = closest_on_aabb(ab, c);
    Vec3 d  = vec3_sub(cp, c);
    f32 dist2 = vec3_dot(d, d);
    if (dist2 > r * r) {
        /* not overlapping unless center is inside the box */
        bool inside = (c.e[0] >= ab.min.e[0] && c.e[0] <= ab.max.e[0] &&
                       c.e[1] >= ab.min.e[1] && c.e[1] <= ab.max.e[1] &&
                       c.e[2] >= ab.min.e[2] && c.e[2] <= ab.max.e[2]);
        if (!inside) return false;
    }
    if (dist2 > 1e-12f) {
        f32 inv = fast_rsqrt(dist2);
        f32 dist = dist2 * inv;
        *n = vec3_scale(d, inv);
        *depth = r - dist;
        *pt = cp;
        return true;
    }
    /* Center inside box: exit along axis of least penetration. `exit_sign` is
     * the direction to push the sphere out; the returned normal (sphere->box)
     * is the opposite so that de-penetration moves the sphere along the exit. */
    f32 best = 1e30f; int axis = 1; f32 exit_sign = 1.0f;
    for (int i = 0; i < 3; i++) {
        f32 pen_min = c.e[i] - ab.min.e[i];   /* exit toward -i */
        f32 pen_max = ab.max.e[i] - c.e[i];   /* exit toward +i */
        if (pen_min < best) { best = pen_min; axis = i; exit_sign = -1.0f; }
        if (pen_max < best) { best = pen_max; axis = i; exit_sign = 1.0f; }
    }
    Vec3 nn = {{0, 0, 0}};
    nn.e[axis] = -exit_sign;
    *n = nn;
    *depth = best + r;
    *pt = c;
    return true;
}

/* Canonical collision with rank(A) <= rank(B). Normal from A toward B. */
static bool collide_ordered(const RigidBody *A, const RigidBody *B,
                            Vec3 *n, f32 *depth, Vec3 *pt) {
    ShapeType sa = A->shape, sb = B->shape;

    if (sa == SHAPE_SPHERE && sb == SHAPE_SPHERE) {
        Vec3 d = vec3_sub(B->position, A->position);
        f32 dist2 = vec3_dot(d, d);
        f32 r = A->radius + B->radius;
        if (dist2 >= r * r) return false;
        f32 inv = fast_rsqrt(dist2 > 1e-12f ? dist2 : 1e-12f);
        f32 dist = dist2 * inv;
        *n = dist2 > 1e-12f ? vec3_scale(d, inv) : vec3(0, 1, 0);
        *depth = r - dist;
        *pt = vec3_add(A->position, vec3_scale(*n, A->radius - *depth * 0.5f));
        return true;
    }
    if (sa == SHAPE_SPHERE && sb == SHAPE_CAPSULE) {
        Vec3 b0, b1; capsule_segment(B, &b0, &b1);
        Vec3 cp = closest_on_segment(b0, b1, A->position, NULL);
        Vec3 d = vec3_sub(cp, A->position);
        f32 dist2 = vec3_dot(d, d);
        f32 r = A->radius + B->radius;
        if (dist2 >= r * r) return false;
        f32 inv = fast_rsqrt(dist2 > 1e-12f ? dist2 : 1e-12f);
        f32 dist = dist2 * inv;
        *n = dist2 > 1e-12f ? vec3_scale(d, inv) : vec3(0, 1, 0);
        *depth = r - dist;
        *pt = vec3_add(A->position, vec3_scale(*n, A->radius));
        return true;
    }
    if (sa == SHAPE_SPHERE && sb == SHAPE_BOX) {
        return sphere_vs_box(A->position, A->radius, B, n, depth, pt);
    }
    if (sa == SHAPE_CAPSULE && sb == SHAPE_CAPSULE) {
        Vec3 a0, a1, b0, b1, c1, c2;
        capsule_segment(A, &a0, &a1);
        capsule_segment(B, &b0, &b1);
        closest_seg_seg(a0, a1, b0, b1, &c1, &c2);
        Vec3 d = vec3_sub(c2, c1);
        f32 dist2 = vec3_dot(d, d);
        f32 r = A->radius + B->radius;
        if (dist2 >= r * r) return false;
        f32 inv = fast_rsqrt(dist2 > 1e-12f ? dist2 : 1e-12f);
        f32 dist = dist2 * inv;
        *n = dist2 > 1e-12f ? vec3_scale(d, inv) : vec3(0, 1, 0);
        *depth = r - dist;
        *pt = vec3_add(c1, vec3_scale(*n, A->radius - *depth * 0.5f));
        return true;
    }
    if (sa == SHAPE_CAPSULE && sb == SHAPE_BOX) {
        Vec3 a0, a1; capsule_segment(A, &a0, &a1);
        AABB ab = aabb_from_body(B);
        f32 r = A->radius;
        /* Whole-capsule MTV (CORRECTNESS): the old path reduced the pair to
         * sphere_vs_box at the single segment point nearest the box centre.
         * When the capsule axis pierces the box ("skewer"), that point's
         * least-penetration face can sit on the wrong side of the mid-plane,
         * and depth = point-exit + r separates only that ONE point — the rest
         * of the capsule stayed overlapped by up to r (measured residual
         * 0.99997 at r=1.0). Compute the MTV over the whole capsule instead:
         * SAT over the 3 box face axes (capsule interval = segment range ± r)
         * plus the radial axis through the closest segment/box points. Each
         * candidate is a valid separation of the FULL capsule (translating by
         * the projection overlap along any axis separates the pair), so the
         * least-depth candidate is the MTV. */
        Vec3 segp  = closest_on_segment(a0, a1, B->position, NULL);
        Vec3 cp    = closest_on_aabb(ab, segp);
        Vec3 segp2 = closest_on_segment(a0, a1, cp, NULL);
        Vec3 cp2   = closest_on_aabb(ab, segp2);
        /* One more refinement pass for edge/corner accuracy. */
        segp2 = closest_on_segment(a0, a1, cp2, NULL);
        cp2   = closest_on_aabb(ab, segp2);
        Vec3 d = vec3_sub(cp2, segp2);
        f32 dist2 = vec3_dot(d, d);

        bool seg_hits_box = segment_intersects_aabb(a0, a1, ab);
        if (!seg_hits_box && dist2 >= r * r) return false;

        f32 best_depth = 1e30f;
        Vec3 best_n = vec3(0, 1, 0);

        /* Box face axes. Exit toward +i moves the capsule along +i, so the
         * capsule->box normal is -i. */
        for (int i = 0; i < 3; i++) {
            f32 lo = a0.e[i] < a1.e[i] ? a0.e[i] : a1.e[i];
            f32 hi = a0.e[i] > a1.e[i] ? a0.e[i] : a1.e[i];
            f32 cap_min = lo - r, cap_max = hi + r;
            if (cap_max < ab.min.e[i] || cap_min > ab.max.e[i]) return false;
            f32 exit_hi = ab.max.e[i] - cap_min;  /* push capsule toward +i */
            f32 exit_lo = cap_max - ab.min.e[i];  /* push capsule toward -i */
            if (exit_hi < best_depth) {
                best_depth = exit_hi;
                best_n = vec3(0, 0, 0);
                best_n.e[i] = -1.0f;
            }
            if (exit_lo < best_depth) {
                best_depth = exit_lo;
                best_n = vec3(0, 0, 0);
                best_n.e[i] = 1.0f;
            }
        }

        /* Radial axis (segment outside the box): direction from the closest
         * box point to the closest segment point — the cap/edge/corner MTV.
         * Skipped for a piercing segment, where it is not a separating axis
         * (depth r - |d| would under-separate exactly like the old bug). */
        if (!seg_hits_box && dist2 > 1e-12f && dist2 < r * r) {
            f32 inv = fast_rsqrt(dist2);
            f32 dist = dist2 * inv;
            f32 rdepth = r - dist;
            if (rdepth < best_depth) {
                best_depth = rdepth;
                best_n = vec3_scale(d, inv);
            }
        }

        if (best_depth >= 1e30f) return false; /* unreachable: intervals overlap */
        *n = best_n;
        *depth = best_depth;
        *pt = cp2;
        return true;
    }
    /* box vs box: AABB MTV (matches legacy behavior). */
    AABB aa = aabb_from_body(A);
    AABB bb = aabb_from_body(B);
    if (!aabb_overlap(aa, bb)) return false;
    Vec3 dep = aabb_overlap_depth(aa, bb);
    f32 abs_d = fabsf(dep.e[0]);
    int axis = 0;
    if (fabsf(dep.e[1]) < abs_d) { abs_d = fabsf(dep.e[1]); axis = 1; }
    if (fabsf(dep.e[2]) < abs_d) { abs_d = fabsf(dep.e[2]); axis = 2; }
    Vec3 nn = {{0, 0, 0}};
    nn.e[axis] = dep.e[axis] > 0 ? 1.0f : -1.0f;
    *n = nn;
    *depth = abs_d;
    *pt = vec3_scale(vec3_add(A->position, B->position), 0.5f);
    return true;
}

bool physics_collide(const RigidBody *a, const RigidBody *b, Contact *out) {
    const RigidBody *A = a, *B = b;
    bool swapped = false;
    if (shape_rank(a->shape) > shape_rank(b->shape)) { A = b; B = a; swapped = true; }

    Vec3 n; f32 depth; Vec3 pt;
    if (!collide_ordered(A, B, &n, &depth, &pt)) return false;
    if (depth <= 0.0f) return false;

    /* collide_ordered returns normal from A(ordered) to B(ordered).
     * Convert to from-a-to-b in the caller's argument order. */
    if (swapped) n = vec3_scale(n, -1.0f);
    if (out) {
        out->normal = n;
        out->depth  = depth;
        out->point  = pt;
        out->body_a = 0;
        out->body_b = 0;
    }
    return true;
}

static void physics_collision_callback(u32 i, u32 j, void *ctx) {
    PhysicsWorld *pw = (PhysicsWorld *)ctx;
    RigidBody *a = &pw->bodies[i];
    RigidBody *b = &pw->bodies[j];

    /* R427: skip static-static pairs — parked (deleted) bodies all sit at the
     * same park position and overlap pairwise, so k parked bodies cost O(k^2)
     * narrowphase per step and inflate the collision stats; no consumer
     * (on_contact is engine/test-only) relies on static-static contacts. */
    if (a->is_static && b->is_static) return;

    Contact contact;
    if (!physics_collide(a, b, &contact)) return;
    contact.body_a = i;
    contact.body_b = j;
    a->contact_active = true;
    b->contact_active = true;
    Vec3 relative_velocity = vec3_sub(a->velocity, b->velocity);
    a->contact_speed2 = vec3_dot(relative_velocity, relative_velocity);
    b->contact_speed2 = a->contact_speed2;
    a->contact_normal = contact.normal;
    b->contact_normal = vec3_scale(contact.normal, -1.0f);

    Vec3 normal = contact.normal;
    f32 abs_depth = contact.depth;
    resolve_contact(a, b, normal, abs_depth);

    if (pw->on_contact) pw->on_contact(&contact, pw->contact_user);

    pw->collision_count++;
    a->collision_count++;
    b->collision_count++;
    pw->total_impulse_axis = vec3_add(pw->total_impulse_axis, vec3_scale(normal, abs_depth));
    Vec3 rel_v = vec3_sub(a->velocity, b->velocity);
    pw->total_collision_speed += rel_v.e[0]*rel_v.e[0] + rel_v.e[1]*rel_v.e[1] + rel_v.e[2]*rel_v.e[2];
    if (a->collision_count + b->collision_count > pw->hot_pair_count) {
        pw->hot_pair_a = i;
        pw->hot_pair_b = j;
        pw->hot_pair_count = a->collision_count + b->collision_count;
    }
    pw->last_collision_pos = vec3_scale(vec3_add(a->position, b->position), 0.5f);
    pw->collision_center = vec3_add(pw->collision_center, pw->last_collision_pos);
    pw->collision_center_count++;
}

/* ---- Continuous collision detection (swept sphere vs AABBs; R435: statics + dynamics) ---- */

static f32 body_bound_radius(const RigidBody *b) {
    switch (b->shape) {
        case SHAPE_SPHERE:
            return b->radius;
        case SHAPE_CAPSULE:
            /* R277 (CORRECTNESS): CCD sweeps the body as a sphere of this radius
             * (static AABBs are expanded by it). A capsule's farthest point from
             * its center is the cap tip at half_height + radius along the axis,
             * matching aabb_from_body's Y extent. Returning only `radius` here
             * under-expanded the swept volume by half_height, so a fast CCD
             * capsule could tunnel through thin static geometry along its axis.
             * A conservative (possibly slightly early) bound is the correct
             * behavior for a tunneling-prevention safety net. */
            return b->half_height + b->radius;
        case SHAPE_BOX:
        default: {
            f32 m = b->half_extent.e[0];
            if (b->half_extent.e[1] > m) m = b->half_extent.e[1];
            if (b->half_extent.e[2] > m) m = b->half_extent.e[2];
            return m;
        }
    }
}

/* R435: slab-method time-of-impact of a point (body radius already folded
 * into `box`) moving from `origin` along `delta` (t in [0,1]). Only counts
 * hits strictly before `t_limit`. Extracted verbatim from the pre-R435
 * ccd_sweep_static inner loop so statics and dynamics share one code path;
 * static-path numerics are unchanged. */
static bool sweep_box_toi(Vec3 origin, Vec3 delta, const f32 inv_dir[3],
                          AABB box, f32 t_limit, f32 *out_t, Vec3 *out_n) {
    f32 tmin = 0.0f, tmax = t_limit;
    int hit_axis = -1; f32 hit_sign = 0.0f;
    for (int a = 0; a < 3; a++) {
        if (fabsf(delta.e[a]) < 1e-8f) {
            if (origin.e[a] < box.min.e[a] || origin.e[a] > box.max.e[a]) return false;
        } else {
            f32 inv = inv_dir[a];
            f32 t1 = (box.min.e[a] - origin.e[a]) * inv;
            f32 t2 = (box.max.e[a] - origin.e[a]) * inv;
            f32 sgn = -1.0f;
            if (t1 > t2) { f32 tmp = t1; t1 = t2; t2 = tmp; sgn = 1.0f; }
            if (t1 > tmin) { tmin = t1; hit_axis = a; hit_sign = sgn; }
            if (t2 < tmax) tmax = t2;
            if (tmin > tmax) return false;
        }
    }
    if (tmin >= 0.0f && tmin < t_limit && hit_axis >= 0) {
        Vec3 n = {{0, 0, 0}};
        n.e[hit_axis] = hit_sign;
        *out_t = tmin;
        *out_n = n;
        return true;
    }
    return false;
}

/* Sweep a point of radius `radius` from `origin` along `delta` (t in [0,1])
 * against every static body (BVH broadphase) and every dynamic body
 * (conservative linear pass). Returns earliest time-of-impact and face normal
 * (pointing out of the obstacle toward the mover). */
static bool ccd_sweep(PhysicsWorld *pw, u32 self, Vec3 origin, Vec3 delta,
                      f32 radius, f32 dt, f32 *out_t, Vec3 *out_n) {
    if (vec3_dot(delta, delta) < 1e-10f) return false;
    f32 best_t = 1.0f;
    bool hit = false;
    Vec3 best_n = {{0, 0, 0}};

    /* Compute swept AABB: union of start/end positions expanded by radius */
    Vec3 end = vec3_add(origin, delta);
    BVHAABB sweep_box;
    sweep_box.min = vec3(
        (origin.e[0] < end.e[0] ? origin.e[0] : end.e[0]) - radius,
        (origin.e[1] < end.e[1] ? origin.e[1] : end.e[1]) - radius,
        (origin.e[2] < end.e[2] ? origin.e[2] : end.e[2]) - radius);
    sweep_box.max = vec3(
        (origin.e[0] > end.e[0] ? origin.e[0] : end.e[0]) + radius,
        (origin.e[1] > end.e[1] ? origin.e[1] : end.e[1]) + radius,
        (origin.e[2] > end.e[2] ? origin.e[2] : end.e[2]) + radius);

    /* R251 (CORRECTNESS): bvh_query_aabb stops writing once its 64 candidate slots
     * fill, silently dropping further overlapping static bodies. If the earliest-TOI
     * blocker is among the dropped candidates, CCD reports no hit and the body
     * tunnels through it. Mirror R239 (char_slide_resolve): use the BVH only when it
     * is built AND the query did not saturate; otherwise fall back to a full scan. */
    /* R418: stack buffer, not static — a function-local static made this
     * non-reentrant (same pattern as physics_sweep_test in character.c). */
    u32 candidates[64];
    bool use_bvh = (pw->bvh.node_count > 0);
    u32 nc = 0;
    if (use_bvh) {
        nc = bvh_query_aabb(&pw->bvh, sweep_box, candidates, 64);
        if (nc >= 64u) use_bvh = false;
    }
    u32 total = use_bvh ? nc : pw->count;

    /* Precompute inverse direction to eliminate 3 divisions per candidate */
    f32 inv_dir[3];
    for (int a = 0; a < 3; a++) {
        inv_dir[a] = (fabsf(delta.e[a]) > 1e-8f) ? (1.0f / delta.e[a]) : 1e30f;
    }

    /* Pass 1: static bodies (BVH broadphase, or full scan on saturation). */
    for (u32 ci = 0; ci < total; ci++) {
        u32 k = use_bvh ? candidates[ci] : ci;
        if (k == self) continue;
        RigidBody *s = &pw->bodies[k];
        if (!s->is_static) continue;

        AABB box = aabb_from_body(s);
        box.min = vec3_sub(box.min, vec3(radius, radius, radius));
        box.max = vec3_add(box.max, vec3(radius, radius, radius));

        f32 t; Vec3 n;
        if (sweep_box_toi(origin, delta, inv_dir, box, best_t, &t, &n)) {
            best_t = t;
            hit = true;
            best_n = n;
        }
    }

    /* R435 — Pass 2: dynamic-vs-dynamic. The pre-integration BVH cannot be
     * queried here (opponents move this frame and the expansion below is
     * velocity-dependent), so dynamic bodies are scanned linearly — CCD bodies
     * are rare and this is a tunneling safety net, not the primary broadphase.
     *
     * Semantics (CONSERVATIVE): the opponent is treated as occupying, for the
     * WHOLE frame, its current AABB swept along its frame displacement
     * (velocity * dt). Real relative motion would let the mover slip past
     * before the opponent arrives, so this can clamp slightly early — but it
     * can never let the mover through. The opponent velocity used is its
     * current value (already-integrated for lower indices, last frame's for
     * later ones); that approximation stays conservative because integration
     * only damps (0.98) and gravity is negligible at CCD speeds.
     *
     * If the mover's ORIGIN is already inside the opponent's swept volume
     * (common in fast head-on pairs), the pair counts as touching at t=0 with
     * the normal opposing the dominant motion axis: the mover holds position
     * this frame and the ordinary contact solver takes over. */
    for (u32 k = 0; k < pw->count; k++) {
        if (k == self) continue;
        RigidBody *s = &pw->bodies[k];
        if (s->is_static) continue;

        AABB box = aabb_from_body(s);
        Vec3 sd = vec3_scale(s->velocity, dt);
        for (int a = 0; a < 3; a++) {
            if (sd.e[a] < 0.0f) box.min.e[a] += sd.e[a];
            else                box.max.e[a] += sd.e[a];
        }
        box.min = vec3_sub(box.min, vec3(radius, radius, radius));
        box.max = vec3_add(box.max, vec3(radius, radius, radius));

        if (origin.e[0] >= box.min.e[0] && origin.e[0] <= box.max.e[0] &&
            origin.e[1] >= box.min.e[1] && origin.e[1] <= box.max.e[1] &&
            origin.e[2] >= box.min.e[2] && origin.e[2] <= box.max.e[2]) {
            if (best_t > 0.0f) {
                best_t = 0.0f;
                hit = true;
                int dom = 0;
                if (fabsf(delta.e[1]) > fabsf(delta.e[dom])) dom = 1;
                if (fabsf(delta.e[2]) > fabsf(delta.e[dom])) dom = 2;
                Vec3 n = {{0, 0, 0}};
                n.e[dom] = delta.e[dom] > 0.0f ? -1.0f : 1.0f;
                best_n = n;
            }
            continue;
        }

        f32 t; Vec3 n;
        if (sweep_box_toi(origin, delta, inv_dir, box, best_t, &t, &n)) {
            best_t = t;
            hit = true;
            best_n = n;
        }
    }
    if (hit) {
        if (out_t) *out_t = best_t;
        if (out_n) *out_n = best_n;
    }
    return hit;
}

/* Integrate a single CCD body, clamping motion at the first hit — static
 * (exact) or dynamic (R435 conservative, see ccd_sweep pass 2). */
static void integrate_body_ccd(PhysicsWorld *pw, u32 idx, f32 dt) {
    RigidBody *b = &pw->bodies[idx];
    Vec3 oldp = b->position;
    b->step_start_position = oldp;

    b->velocity = vec3_add(b->velocity, vec3_scale(b->acceleration, dt));
    b->velocity = vec3_scale(b->velocity, 0.98f);
    Vec3 newp = vec3_add(oldp, vec3_scale(b->velocity, dt));
    Vec3 delta = vec3_sub(newp, oldp);

    f32 t; Vec3 n;
    if (ccd_sweep(pw, idx, oldp, delta, body_bound_radius(b), dt, &t, &n)) {
        f32 tc = t - 0.001f;
        if (tc < 0.0f) tc = 0.0f;
        newp = vec3_add(oldp, vec3_scale(delta, tc));
        f32 vn = vec3_dot(b->velocity, n);
        if (vn < 0.0f) b->velocity = vec3_sub(b->velocity, vec3_scale(n, vn));
    }
    b->position = newp;
}

/* Build the BVH when it is dirty. physics_step calls this every frame, and
 * the query APIs call it so a query issued before the first step does not
 * silently miss every body (the tree starts empty with bvh_dirty set). The
 * BVH is a derived cache of body positions, so this lazy build is logically
 * const even though it writes pw->bvh / pw->bvh_dirty. */
static void physics_ensure_bvh(const PhysicsWorld *pw) {
    if (!pw->bvh_dirty) return;
    PhysicsWorld *m = (PhysicsWorld *)pw; /* lazy init of a derived cache */
    BVHAABB *aabbs = m->_bvh_staging;
    for (u32 i = 0; i < m->count; i++) {
        AABB box = aabb_from_body(&m->bodies[i]);
        aabbs[i].min = box.min;
        aabbs[i].max = box.max;
    }
    bvh_build(&m->bvh, aabbs, m->count);
    m->bvh_dirty = false;
}

void physics_step(PhysicsWorld *pw, f32 dt) {
    if (!pw || !isfinite(dt)) return;
    for (u32 i = 0; i < pw->count; i++) pw->bodies[i].contact_active = false;
    pw->collision_count = 0;
    if (!(dt > 1e-6f)) dt = 1e-6f;
    for (u32 ci = 0; ci < PHYSICS_MAX_CONSTRAINTS; ci++) {
        DistanceConstraint *c = &pw->constraints[ci];
        if (!c->active || !c->is_slider) continue;
        RigidBody *a = physics_body_resolve(pw, c->body_a);
        RigidBody *b = physics_body_resolve(pw, c->body_b);
        if (!a || !b || b->inv_mass <= 0.0f) continue;
        f32 torsion = c->slider_torsion;
        if (torsion < 0.0f) torsion = 0.0f;
        if (torsion > 1.0f) torsion = 1.0f;
        if (torsion == 0.0f) continue;
        Quat qa = rigid_orientation(a);
        Quat qb = rigid_orientation(b);
        Quat rel = quat_mul(quat_inverse(qa), qb);
        Vec3 imag = vec3(rel.e[0], rel.e[1], rel.e[2]);
        f32 vlen = vec3_len(imag);
        f32 angle = 2.0f * atan2f(vlen, rel.e[3]);
        Vec3 axis = vlen > 1e-8f ? quat_rotate_vec3(qa, vec3_scale(imag, 1.0f / vlen)) : vec3(0, 1, 0);
        f32 target_w = -torsion * angle / dt;
        f32 along = vec3_dot(b->angular_velocity, axis);
        if (fabsf(angle) <= 1e-8f && fabsf(along) <= 1e-8f) continue;
        physics_body_wake(pw, c->body_b);
        if (c->slider_damping >= 1.0f) {
            b->angular_velocity = vec3_add(b->angular_velocity, vec3_scale(axis, target_w - along));
        } else {
            f32 k = c->slider_stiffness * torsion;
            f32 damp = c->slider_damping < 0.0f ? 0.0f : c->slider_damping;
            f32 alpha = -k * angle - damp * 2.0f * sqrtf(k) * along;
            b->angular_velocity = vec3_add(b->angular_velocity, vec3_scale(axis, alpha * dt));
        }
    }

    /* BVH broadphase: rebuild/refit BEFORE integration so CCD can query it */
    bool bvh_rebuilt = pw->bvh_dirty;
    physics_ensure_bvh(pw);
    if (!bvh_rebuilt) {
        for (u32 i = 0; i < pw->count; i++) {
            if (pw->bodies[i].is_static) continue; /* static AABB never changes */
            /* Skip BVH refit for resting bodies: rest_frames > 2 now requires
             * the position to have been bit-unchanged for 2+ frames (see the
             * integration loops below), so the stored AABB is bit-identical
             * and skipping the refit is exact. */
            if (pw->bodies[i].rest_frames > 2) continue;
            AABB box = aabb_from_body(&pw->bodies[i]);
            BVHAABB bvh_box;
            bvh_box.min = box.min;
            bvh_box.max = box.max;
            bvh_refit(&pw->bvh, i, bvh_box);
        }
    }

#if SIMD_SSE2
    /* SIMD-optimized integration loop */
    const f32 damping = 0.98f;

    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (b->is_static || b->sleeping) continue;
        if (b->ccd) { integrate_body_ccd(pw, i, dt); continue; }

        b->step_start_position = b->position;

        /* Velocity integration: v += a * dt */
        simd_vec3_add_scaled_sse2(b->velocity.e, b->velocity.e, b->acceleration.e, dt);

        /* Damping: v *= 0.98 */
        simd_vec3_scale_sse2(b->velocity.e, b->velocity.e, damping);

        /* Position integration: p += v * dt */
        simd_vec3_add_scaled_sse2(b->position.e, b->position.e, b->velocity.e, dt);
        integrate_orientation(b, dt);

    }
#else
    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (b->is_static || b->sleeping) continue;
        if (b->ccd) { integrate_body_ccd(pw, i, dt); continue; }

        b->step_start_position = b->position;

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
        integrate_orientation(b, dt);

    }
#endif

    /* R418: refit moved bodies again AFTER integration, before the pair query.
     * The tree was built/refit pre-integration (kept above so integrate_body_ccd
     * can sweep against it), so without this pass bvh_query_pairs tested pairs
     * against last frame's AABBs: a contact that begins during this frame's
     * motion was never pair-tested, letting fast non-CCD bodies tunnel and
     * resolving ordinary contacts a frame late. Same skip policy as the
     * pre-integration refit (statics never move; resting bodies' AABBs are
     * unchanged). bvh_refit is a no-op on an unbuilt tree. */
    for (u32 i = 0; i < pw->count; i++) {
        if (pw->bodies[i].is_static) continue;
        if (pw->bodies[i].rest_frames > 2) continue;
        AABB box = aabb_from_body(&pw->bodies[i]);
        BVHAABB bvh_box;
        bvh_box.min = box.min;
        bvh_box.max = box.max;
        bvh_refit(&pw->bvh, i, bvh_box);
    }

    /* BVH broadphase collision pair query */
    bvh_query_pairs(&pw->bvh, physics_collision_callback, pw);

    /* R435: distance-constraint position projection runs after contact
     * resolution (contacts see a consistent pre-constraint state) and before
     * the kill-floor (which reads final positions). */
    solve_distance_constraints(pw);
    /* R440: velocity-level solve runs once per step, AFTER the position
     * projection so the axis is computed from the corrected (taut)
     * positions. */
    solve_distance_constraint_velocities(pw);

    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (b->is_static || b->sleeping) continue;
        if (b->position.e[1] - b->half_extent.e[1] < -10.0f) {
            b->position.e[1] = -10.0f + b->half_extent.e[1];
            b->velocity.e[1] = -b->velocity.e[1] * b->restitution;
            pw->respawn_count++;
        }
    }
    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (!b->is_static && !b->sleeping) update_sleep_state(b, b->step_start_position);
    }
    for (u32 s = 0; s < pw->post_step_count; s++) {
        pw->post_step_fn[s](pw, pw->post_step_user[s]);
    }
}

bool physics_raycast(const PhysicsWorld *pw, Vec3 origin, Vec3 dir, f32 max_dist, PhysicsBodyHandle *out_body, f32 *out_t) {
    if (!pw) return false;
    /* Reject non-finite queries (NaN/Inf): comparisons against NaN pass every
     * slab test and report a phantom hit at t=0. Same NaN-reject policy as
     * physics_constraint_add_distance / add_ball. */
    for (int i = 0; i < 3; i++) {
        if (!isfinite(origin.e[i]) || !isfinite(dir.e[i])) return false;
    }
    physics_ensure_bvh(pw); /* first query may precede the first step */
    BVHRayHit hit;
    if (bvh_raycast(&pw->bvh, origin, dir, max_dist, &hit)) {
        if (out_body) *out_body = physics_body_handle_from_slot(pw, hit.object_index);
        if (out_t) *out_t = hit.t;
        return true;
    }
    return false;
}
