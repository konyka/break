#include <physics/physics.h>
#include <core/log.h>
#include <math/simd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* SSE detection and fast_rsqrt provided by math.h via simd.h */

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
    usize pw_bytes     = sizeof(PhysicsWorld);
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
    bvh_destroy(&pw->bvh);
    /* Single free: bodies and _bvh_staging are within the same block as pw */
    free(pw);
}

u32 physics_body_create(PhysicsWorld *pw, Vec3 pos, Vec3 half_ext, f32 mass, bool is_static, u32 frame) {
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
    b->inv_mass = (is_static || mass <= 0.0f) ? 0.0f : (1.0f / mass);
    b->restitution = 0.3f;
    b->is_static = is_static;
    b->spawn_frame = frame;
    b->spawn_pos = pos;
    b->rest_frames = 0;
    b->collision_count = 0;
    pw->bvh_dirty = true;
    return id;
}

u32 physics_body_create_sphere(PhysicsWorld *pw, Vec3 pos, f32 radius, f32 mass, bool is_static, u32 frame) {
    u32 id = physics_body_create(pw, pos, vec3(radius, radius, radius), mass, is_static, frame);
    if (id < pw->count) {
        RigidBody *b = &pw->bodies[id];
        b->shape  = SHAPE_SPHERE;
        b->radius = radius;
    }
    return id;
}

u32 physics_body_create_capsule(PhysicsWorld *pw, Vec3 pos, f32 radius, f32 half_height, f32 mass, bool is_static, u32 frame) {
    u32 id = physics_body_create(pw, pos, vec3(radius, half_height + radius, radius), mass, is_static, frame);
    if (id < pw->count) {
        RigidBody *b = &pw->bodies[id];
        b->shape       = SHAPE_CAPSULE;
        b->radius      = radius;
        b->half_height = half_height;
    }
    return id;
}

void physics_body_set_ccd(PhysicsWorld *pw, u32 body_id, bool enable) {
    if (body_id >= pw->count) return;
    pw->bodies[body_id].ccd = enable;
}

void physics_set_contact_callback(PhysicsWorld *pw, PhysicsContactFn fn, void *user) {
    if (!pw) return;
    pw->on_contact   = fn;
    pw->contact_user = user;
}

void physics_body_apply_impulse(PhysicsWorld *pw, u32 body_id, Vec3 impulse) {
    if (body_id >= pw->count) return;
    RigidBody *b = &pw->bodies[body_id];
    if (b->is_static || b->inv_mass <= 0.0f) return;
    b->velocity.e[0] += impulse.e[0] * b->inv_mass;
    b->velocity.e[1] += impulse.e[1] * b->inv_mass;
    b->velocity.e[2] += impulse.e[2] * b->inv_mass;
    pw->total_impulse_applied += vec3_len(impulse);
}

static void resolve_contact(RigidBody *a, RigidBody *b, Vec3 normal, f32 depth) {
    f32 inv_a = a->inv_mass;
    f32 inv_b = b->inv_mass;
    f32 total_inv_mass = inv_a + inv_b;
    if (total_inv_mass <= 0.0f) return;

    /* Precompute reciprocal to replace 3 divisions with multiplications. */
    f32 inv_total = 1.0f / total_inv_mass;

    if (inv_a > 0.0f) {
        f32 ratio = inv_a * inv_total;
        a->position.e[0] -= normal.e[0] * depth * ratio;
        a->position.e[1] -= normal.e[1] * depth * ratio;
        a->position.e[2] -= normal.e[2] * depth * ratio;
    }
    if (inv_b > 0.0f) {
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
        /* Two-step closest approximation: seg->box center, refine. */
        Vec3 segp = closest_on_segment(a0, a1, B->position, NULL);
        Vec3 cp   = closest_on_aabb(ab, segp);
        Vec3 segp2 = closest_on_segment(a0, a1, cp, NULL);
        Vec3 cp2   = closest_on_aabb(ab, segp2);
        Vec3 d = vec3_sub(cp2, segp2);
        f32 dist2 = vec3_dot(d, d);
        if (dist2 >= A->radius * A->radius) {
            bool inside = (segp2.e[0] >= ab.min.e[0] && segp2.e[0] <= ab.max.e[0] &&
                           segp2.e[1] >= ab.min.e[1] && segp2.e[1] <= ab.max.e[1] &&
                           segp2.e[2] >= ab.min.e[2] && segp2.e[2] <= ab.max.e[2]);
            if (!inside) return false;
        }
        return sphere_vs_box(segp2, A->radius, B, n, depth, pt);
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

    Contact contact;
    if (!physics_collide(a, b, &contact)) return;
    contact.body_a = i;
    contact.body_b = j;

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

/* ---- Continuous collision detection (swept sphere vs static AABBs) ---- */

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

/* Sweep a point of radius `radius` from `origin` along `delta` (t in [0,1])
 * against every static body. Returns earliest time-of-impact and face normal
 * (pointing out of the box toward the mover).
 * Uses BVH broadphase to avoid O(N) linear scan. */
static bool ccd_sweep_static(PhysicsWorld *pw, u32 self, Vec3 origin, Vec3 delta,
                             f32 radius, f32 *out_t, Vec3 *out_n) {
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
    static u32 candidates[64];
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

    for (u32 ci = 0; ci < total; ci++) {
        u32 k = use_bvh ? candidates[ci] : ci;
        if (k == self) continue;
        RigidBody *s = &pw->bodies[k];
        if (!s->is_static) continue;

        AABB box = aabb_from_body(s);
        box.min = vec3_sub(box.min, vec3(radius, radius, radius));
        box.max = vec3_add(box.max, vec3(radius, radius, radius));

        f32 tmin = 0.0f, tmax = best_t;
        int hit_axis = -1; f32 hit_sign = 0.0f;
        bool valid = true;
        for (int a = 0; a < 3; a++) {
            if (fabsf(delta.e[a]) < 1e-8f) {
                if (origin.e[a] < box.min.e[a] || origin.e[a] > box.max.e[a]) { valid = false; break; }
            } else {
                f32 inv = inv_dir[a];
                f32 t1 = (box.min.e[a] - origin.e[a]) * inv;
                f32 t2 = (box.max.e[a] - origin.e[a]) * inv;
                f32 sgn = -1.0f;
                if (t1 > t2) { f32 tmp = t1; t1 = t2; t2 = tmp; sgn = 1.0f; }
                if (t1 > tmin) { tmin = t1; hit_axis = a; hit_sign = sgn; }
                if (t2 < tmax) tmax = t2;
                if (tmin > tmax) { valid = false; break; }
            }
        }
        if (valid && tmin >= 0.0f && tmin < best_t && hit_axis >= 0) {
            best_t = tmin;
            hit = true;
            Vec3 n = {{0, 0, 0}};
            n.e[hit_axis] = hit_sign;
            best_n = n;
        }
    }
    if (hit) {
        if (out_t) *out_t = best_t;
        if (out_n) *out_n = best_n;
    }
    return hit;
}

/* Integrate a single CCD body, clamping motion at the first static hit. */
static void integrate_body_ccd(PhysicsWorld *pw, u32 idx, f32 dt) {
    RigidBody *b = &pw->bodies[idx];
    Vec3 oldp = b->position;

    b->velocity = vec3_add(b->velocity, vec3_scale(b->acceleration, dt));
    b->velocity = vec3_scale(b->velocity, 0.98f);
    Vec3 newp = vec3_add(oldp, vec3_scale(b->velocity, dt));
    Vec3 delta = vec3_sub(newp, oldp);

    f32 t; Vec3 n;
    if (ccd_sweep_static(pw, idx, oldp, delta, body_bound_radius(b), &t, &n)) {
        f32 tc = t - 0.001f;
        if (tc < 0.0f) tc = 0.0f;
        newp = vec3_add(oldp, vec3_scale(delta, tc));
        f32 vn = vec3_dot(b->velocity, n);
        if (vn < 0.0f) b->velocity = vec3_sub(b->velocity, vec3_scale(n, vn));
    }
    b->position = newp;

    f32 spd2 = vec3_dot(b->velocity, b->velocity);
    if (spd2 < 0.0025f) b->rest_frames++;
    else b->rest_frames = 0;
}

void physics_step(PhysicsWorld *pw, f32 dt) {
    pw->collision_count = 0;

    /* BVH broadphase: rebuild/refit BEFORE integration so CCD can query it */
    if (pw->bvh_dirty) {
        BVHAABB *aabbs = pw->_bvh_staging;
        for (u32 i = 0; i < pw->count; i++) {
            AABB box = aabb_from_body(&pw->bodies[i]);
            aabbs[i].min = box.min;
            aabbs[i].max = box.max;
        }
        bvh_build(&pw->bvh, aabbs, pw->count);
        pw->bvh_dirty = false;
    } else {
        for (u32 i = 0; i < pw->count; i++) {
            if (pw->bodies[i].is_static) continue; /* static AABB never changes */
            /* Skip BVH refit for resting bodies: rest_frames > 2 means position
             * hasn't changed meaningfully for 2+ frames, so AABB is unchanged.
             * Eliminates O(depth) tree walk per resting body. */
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
    const f32 rest_threshold = 0.0025f;
    
    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (b->is_static) continue;
        if (b->ccd) { integrate_body_ccd(pw, i, dt); continue; }

        /* Velocity integration: v += a * dt */
        simd_vec3_add_scaled_sse2(b->velocity.e, b->velocity.e, b->acceleration.e, dt);
        
        /* Damping: v *= 0.98 */
        simd_vec3_scale_sse2(b->velocity.e, b->velocity.e, damping);
        
        /* Position integration: p += v * dt */
        simd_vec3_add_scaled_sse2(b->position.e, b->position.e, b->velocity.e, dt);
        
        /* Rest detection using SIMD dot product */
        f32 spd2 = simd_vec3_dot_sse2(b->velocity.e, b->velocity.e);
        if (spd2 < rest_threshold) b->rest_frames++;
        else b->rest_frames = 0;
    }
#else
    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (b->is_static) continue;
        if (b->ccd) { integrate_body_ccd(pw, i, dt); continue; }

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

        f32 spd2 = b->velocity.e[0]*b->velocity.e[0] + b->velocity.e[1]*b->velocity.e[1] + b->velocity.e[2]*b->velocity.e[2];
        if (spd2 < 0.0025f) b->rest_frames++;
        else b->rest_frames = 0;
    }
#endif

    /* BVH broadphase collision pair query */
    bvh_query_pairs(&pw->bvh, physics_collision_callback, pw);

    for (u32 i = 0; i < pw->count; i++) {
        RigidBody *b = &pw->bodies[i];
        if (b->is_static) continue;
        if (b->position.e[1] - b->half_extent.e[1] < -10.0f) {
            b->position.e[1] = -10.0f + b->half_extent.e[1];
            b->velocity.e[1] = -b->velocity.e[1] * b->restitution;
            pw->respawn_count++;
        }
    }
}

bool physics_raycast(const PhysicsWorld *pw, Vec3 origin, Vec3 dir, f32 max_dist, u32 *out_body, f32 *out_t) {
    BVHRayHit hit;
    if (bvh_raycast(&pw->bvh, origin, dir, max_dist, &hit)) {
        if (out_body) *out_body = hit.object_index;
        if (out_t) *out_t = hit.t;
        return true;
    }
    return false;
}
