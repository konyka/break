#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/bvh.h>

typedef struct {
    Vec3 min;
    Vec3 max;
} AABB;

/* Collision shape. Default 0 = box (backward compatible with {0} init). */
typedef enum {
    SHAPE_BOX     = 0,
    SHAPE_SPHERE  = 1,
    SHAPE_CAPSULE = 2,  /* upright (Y axis); segment half-length = half_height */
} ShapeType;

typedef struct {
    Vec3  position;
    Vec3  velocity;
    Vec3  acceleration;
    Vec3  half_extent;   /* box: half-size; also used for broadphase */
    f32   mass;
    f32   inv_mass;       /* pre-computed 1/mass (0 for static) */
    f32   restitution;
    bool  is_static;
    u32   spawn_frame;
    Vec3  spawn_pos;
    u32   rest_frames;
    u32   collision_count;
    /* --- shape (Round 6) --- */
    ShapeType shape;      /* box / sphere / capsule */
    f32   radius;         /* sphere & capsule radius */
    f32   half_height;    /* capsule: half segment length along Y (excludes caps) */
    bool  ccd;            /* continuous collision detection: swept vs static
                           * AABBs and (R435, conservative) dynamic bodies */
} RigidBody;

typedef struct {
    Vec3  point;
    Vec3  normal;   /* from body_a toward body_b */
    f32   depth;
    u32   body_a;
    u32   body_b;
} Contact;

/* Per-contact callback invoked during physics_step for every resolved pair. */
typedef void (*PhysicsContactFn)(const Contact *c, void *user);

/* R435: distance constraint — fixed-capacity array embedded in PhysicsWorld
 * (same style as bodies; no per-step allocation). Position-projected only. */
#define PHYSICS_MAX_CONSTRAINTS 64

typedef struct {
    u32  body_a;
    u32  body_b;
    f32  rest_length;
    bool active;      /* slot occupied (world calloc zero-init = free) */
} DistanceConstraint;

typedef struct {
    RigidBody *bodies;
    u32        count;
    u32        capacity;
    u32        collision_count;
    u32        respawn_count;
    f32        total_impulse_applied;
    Vec3       last_collision_pos;
    u32        hot_pair_a;
    u32        hot_pair_b;
    u32        hot_pair_count;
    f32        total_collision_speed;     /* RMS impact speed (read via sqrt) */
    Vec3       collision_center;
    u32        collision_center_count;
    Vec3       total_impulse_axis;
    BVH        bvh;
    bool       bvh_dirty;
    PhysicsContactFn on_contact;
    void            *contact_user;
    /* Persistent BVH staging buffer (avoids per-step malloc) */
    BVHAABB        *_bvh_staging;
    u32             _bvh_staging_cap;
    /* R435: fixed-capacity distance constraints (embedded, calloc-zeroed) */
    DistanceConstraint constraints[PHYSICS_MAX_CONSTRAINTS];
    u32                constraint_count;   /* active slots */
} PhysicsWorld;

/* R376/R377: Del parks with spawn_frame=UINT32_MAX (tombstone for create reuse). */
static inline bool physics_body_is_parked(const RigidBody *b) {
    return b && b->spawn_frame == UINT32_MAX;
}

PhysicsWorld *physics_world_create(u32 max_bodies);
void          physics_world_destroy(PhysicsWorld *pw);
u32           physics_body_create(PhysicsWorld *pw, Vec3 pos, Vec3 half_ext, f32 mass, bool is_static, u32 frame);
u32           physics_body_create_sphere(PhysicsWorld *pw, Vec3 pos, f32 radius, f32 mass, bool is_static, u32 frame);
u32           physics_body_create_capsule(PhysicsWorld *pw, Vec3 pos, f32 radius, f32 half_height, f32 mass, bool is_static, u32 frame);
void          physics_body_set_ccd(PhysicsWorld *pw, u32 body_id, bool enable);
void          physics_body_apply_impulse(PhysicsWorld *pw, u32 body_id, Vec3 impulse);
/* R376/R379/R380: park/revive tombstone slots (Del/N-clear). Used by main and scene_state. */
void          physics_body_park(PhysicsWorld *pw, u32 pid);
void          physics_body_revive(RigidBody *rb, f32 mass, bool is_static, u32 frame);
void          physics_set_contact_callback(PhysicsWorld *pw, PhysicsContactFn fn, void *user);
/* R435: distance constraints. add returns UINT32_MAX when the fixed array is
 * full or a body id is invalid (R352 convention); remove is idempotent. */
u32           physics_constraint_add_distance(PhysicsWorld *pw, u32 body_a, u32 body_b, f32 rest_length);
void          physics_constraint_remove(PhysicsWorld *pw, u32 constraint_id);
u32           physics_constraint_count(const PhysicsWorld *pw);
void          physics_step(PhysicsWorld *pw, f32 dt);
bool          physics_raycast(const PhysicsWorld *pw, Vec3 origin, Vec3 dir, f32 max_dist, u32 *out_body, f32 *out_t);

/* Narrowphase: compute contact (normal from a->b, depth, point) between any two
 * shapes. Returns false if not overlapping. */
bool          physics_collide(const RigidBody *a, const RigidBody *b, Contact *out);

AABB  aabb_from_body(const RigidBody *b);
bool  aabb_overlap(AABB a, AABB b);
Vec3  aabb_overlap_depth(AABB a, AABB b);
