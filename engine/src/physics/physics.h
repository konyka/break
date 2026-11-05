#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/bvh.h>

typedef struct {
    Vec3 min;
    Vec3 max;
} AABB;

typedef struct PhysicsBodyHandle {
    u32 index;
    u32 generation;
} PhysicsBodyHandle;

typedef struct PhysicsConstraintHandle {
    u32 index;
    u32 generation;
} PhysicsConstraintHandle;

#define PHYSICS_BODY_HANDLE_INVALID ((PhysicsBodyHandle){UINT32_MAX, 0u})
#define PHYSICS_CONSTRAINT_HANDLE_INVALID ((PhysicsConstraintHandle){UINT32_MAX, 0u})

static inline bool physics_body_handle_is_valid(PhysicsBodyHandle h) {
    return h.index != UINT32_MAX && h.generation != 0u;
}
static inline bool physics_constraint_handle_is_valid(PhysicsConstraintHandle h) {
    return h.index != UINT32_MAX && h.generation != 0u;
}
static inline bool physics_body_handle_equal(PhysicsBodyHandle a, PhysicsBodyHandle b) {
    return a.index == b.index && a.generation == b.generation;
}
static inline bool physics_constraint_handle_equal(PhysicsConstraintHandle a, PhysicsConstraintHandle b) {
    return a.index == b.index && a.generation == b.generation;
}

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
    Vec3  half_extent;
    f32   mass;
    f32   inv_mass;
    f32   restitution;
    bool  is_static;
    u32   spawn_frame;
    u32   generation;
    bool  retired;
    Vec3  spawn_pos;
    u32   rest_frames;
    bool  sleeping;
    bool  contact_active;
    Vec3  contact_normal;
    f32   contact_speed2;
    u32   collision_count;
    ShapeType shape;
    f32   radius;
    f32   half_height;
    bool  ccd;
    /* Zero orientation is identity. A zero inertia axis is infinite and
     * does not integrate. Static bodies ignore angular velocity. */
    Quat  orientation;
    Vec3  angular_velocity;
    Vec3  inertia_diag;
    Vec3  step_start_position;
} RigidBody;

/* Slot indices in a Contact are valid only for the current physics_step. */
typedef struct {
    Vec3  point;
    Vec3  normal;
    f32   depth;
    u32   body_a;
    u32   body_b;
} Contact;

typedef void (*PhysicsContactFn)(const Contact *c, void *user);
typedef struct PhysicsWorld PhysicsWorld;
typedef void (*PhysicsPostStepFn)(PhysicsWorld *pw, void *user);
#define PHYSICS_MAX_POST_STEPS 16u
#define PHYSICS_MAX_CONSTRAINTS 64

typedef struct {
    PhysicsBodyHandle body_a;
    PhysicsBodyHandle body_b;
    u32  generation;
    bool retired;
    f32  rest_length;
    bool active;
    Vec3 offset_a;
    Vec3 offset_b;
    bool is_ball;
    bool is_hinge;
    bool is_slider;
    Vec3 hinge_axis;
    f32  limit_min;
    f32  limit_max;
    f32  slider_torsion;
    f32  slider_damping;
    f32  slider_stiffness;
    bool is_cone_twist;
    Vec3 cone_axis_b;
    Quat reference_a;
    Quat reference_b;
    f32  swing_min;
    f32  swing_max;
    f32  twist_min;
    f32  twist_max;
} DistanceConstraint;

typedef struct PhysicsWorld {
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
    f32        total_collision_speed;
    Vec3       collision_center;
    u32        collision_center_count;
    Vec3       total_impulse_axis;
    BVH        bvh;
    bool       bvh_dirty;
    PhysicsContactFn on_contact;
    void            *contact_user;
    BVHAABB        *_bvh_staging;
    u32             _bvh_staging_cap;
    DistanceConstraint constraints[PHYSICS_MAX_CONSTRAINTS];
    u32                constraint_count;
    PhysicsPostStepFn  post_step_fn[PHYSICS_MAX_POST_STEPS];
    void              *post_step_user[PHYSICS_MAX_POST_STEPS];
    u32                post_step_count;
    u32                transaction_depth;
} PhysicsWorld;

static inline bool physics_body_is_parked(const RigidBody *b) {
    return b && b->spawn_frame == UINT32_MAX;
}

PhysicsWorld *physics_world_create(u32 max_bodies);
void          physics_world_destroy(PhysicsWorld *pw);
PhysicsBodyHandle physics_body_create(PhysicsWorld *pw, Vec3 pos, Vec3 half_ext, f32 mass, bool is_static, u32 frame);
PhysicsBodyHandle physics_body_create_sphere(PhysicsWorld *pw, Vec3 pos, f32 radius, f32 mass, bool is_static, u32 frame);
PhysicsBodyHandle physics_body_create_capsule(PhysicsWorld *pw, Vec3 pos, f32 radius, f32 half_height, f32 mass, bool is_static, u32 frame);
void          physics_body_set_ccd(PhysicsWorld *pw, PhysicsBodyHandle body, bool enable);
void          physics_body_apply_impulse(PhysicsWorld *pw, PhysicsBodyHandle body, Vec3 impulse);
void          physics_body_wake(PhysicsWorld *pw, PhysicsBodyHandle body);
void          physics_push_body(PhysicsWorld *pw, PhysicsBodyHandle body, Vec3 normal, f32 depth);
void          physics_body_park(PhysicsWorld *pw, PhysicsBodyHandle body);
PhysicsBodyHandle physics_body_revive(PhysicsWorld *pw, PhysicsBodyHandle body, f32 mass, bool is_static, u32 frame);
RigidBody    *physics_body_resolve(PhysicsWorld *pw, PhysicsBodyHandle body);
void          physics_set_contact_callback(PhysicsWorld *pw, PhysicsContactFn fn, void *user);
bool          physics_add_post_step(PhysicsWorld *pw, PhysicsPostStepFn fn, void *user);
PhysicsConstraintHandle physics_constraint_add_distance(PhysicsWorld *pw, PhysicsBodyHandle body_a, PhysicsBodyHandle body_b, f32 rest_length);
PhysicsConstraintHandle physics_constraint_add_ball(PhysicsWorld *pw, PhysicsBodyHandle body_a, PhysicsBodyHandle body_b, Vec3 anchor_a, Vec3 anchor_b);

typedef struct PhysicsPose {
    Quat orientation;
    Vec3 angular_velocity;
    Vec3 inertia_diag;
} PhysicsPose;

void          physics_body_set_pose(PhysicsWorld *pw, PhysicsBodyHandle body, const PhysicsPose *pose);

typedef struct HingeDesc {
    PhysicsBodyHandle body_a;
    PhysicsBodyHandle body_b;
    Vec3 anchor_local_a;
    Vec3 anchor_local_b;
    Vec3 axis_local_a;
    f32 limit_min;
    f32 limit_max;
} HingeDesc;

PhysicsConstraintHandle physics_constraint_add_hinge(PhysicsWorld *pw, const HingeDesc *desc);

typedef struct SliderDesc {
    PhysicsBodyHandle body_a;
    PhysicsBodyHandle body_b;
    Vec3 anchor_local_a;
    Vec3 anchor_local_b;
    Vec3 axis_local_a;
    f32 limit_min;
    f32 limit_max;
} SliderDesc;

PhysicsConstraintHandle physics_constraint_add_slider(PhysicsWorld *pw, const SliderDesc *desc);

typedef struct ConeTwistDesc {
    PhysicsBodyHandle body_a;
    PhysicsBodyHandle body_b;
    Vec3 anchor_local_a;
    Vec3 anchor_local_b;
    Vec3 axis_local_a;
    Vec3 axis_local_b;
    f32 swing_min;
    f32 swing_max;
    f32 twist_min;
    f32 twist_max;
} ConeTwistDesc;

PhysicsConstraintHandle physics_constraint_add_cone_twist(PhysicsWorld *pw, const ConeTwistDesc *desc);
void          physics_constraint_set_slider_torsion(PhysicsWorld *pw, PhysicsConstraintHandle constraint, f32 torsion);
void          physics_constraint_set_slider_damping(PhysicsWorld *pw, PhysicsConstraintHandle constraint, f32 damping);
void          physics_constraint_set_slider_stiffness(PhysicsWorld *pw, PhysicsConstraintHandle constraint, f32 stiffness);
void          physics_constraint_remove(PhysicsWorld *pw, PhysicsConstraintHandle constraint);
u32           physics_constraint_count(const PhysicsWorld *pw);
void          physics_step(PhysicsWorld *pw, f32 dt);
bool          physics_raycast(const PhysicsWorld *pw, Vec3 origin, Vec3 dir, f32 max_dist, PhysicsBodyHandle *out_body, f32 *out_t);

bool          physics_collide(const RigidBody *a, const RigidBody *b, Contact *out);
AABB  aabb_from_body(const RigidBody *b);
bool  aabb_overlap(AABB a, AABB b);
Vec3  aabb_overlap_depth(AABB a, AABB b);
