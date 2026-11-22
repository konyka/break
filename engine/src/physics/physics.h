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

/* Parallel contact solve. physics_step calls the dispatcher with job_count
 * jobs; it must run fn(job_ctx, i) once for every i in [0, job_count), in
 * any order and on any threads, and return only when all jobs are done.
 * Jobs touch disjoint bodies (islands of bodies with mass, solved in the
 * serial pair order) and the world statistics are replayed in pair order,
 * so the step is bit-identical to the serial solve. physics_step calls the
 * dispatcher up to three times per step (integration and refit, pair
 * collection, then the solve), and it
 * must make the jobs' writes visible to the caller before it returns. The
 * solve stays serial while a contact callback is set, for steps with fewer
 * pairs than the world's minimum (default PHYSICS_PARALLEL_MIN_PAIRS, the
 * measured break-even on a 16-thread x86-64 host) or fewer than two
 * islands, and if the scratch buffers cannot be allocated. */
typedef void (*PhysicsJobFn)(void *job_ctx, u32 job_index);
typedef void (*PhysicsParallelForFn)(void *user, PhysicsJobFn fn, void *job_ctx, u32 job_count);
#define PHYSICS_MAX_PARALLEL_JOBS 32u
#define PHYSICS_PARALLEL_MIN_PAIRS 4096u
#define PHYSICS_PARALLEL_MIN_BODIES 8192u
typedef struct PhysicsPairRecord PhysicsPairRecord;
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
    PhysicsParallelForFn parallel_for;
    void                *parallel_user;
    u32                  parallel_max_jobs;
    u32                  parallel_min_pairs;
    u32                  parallel_min_bodies;
    u32                  _last_pair_count;
    PhysicsPairRecord   *_pair_records;
    u32                  _pair_cap;
    PhysicsPairRecord   *_job_pairs[PHYSICS_MAX_PARALLEL_JOBS];
    u32                  _job_pair_cap[PHYSICS_MAX_PARALLEL_JOBS];
    u32                 *_solve_words;
    usize                _solve_words_cap;
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
/* fn = NULL or max_jobs < 2 returns to the serial solve. max_jobs is capped
 * at PHYSICS_MAX_PARALLEL_JOBS. */
void          physics_world_set_parallel_for(PhysicsWorld *pw, PhysicsParallelForFn fn, void *user,
                                             u32 max_jobs);
/* Smallest pair count solved in parallel; 0 restores PHYSICS_PARALLEL_MIN_PAIRS. */
void          physics_world_set_parallel_min_pairs(PhysicsWorld *pw, u32 min_pairs);
/* Integration and the post-integration BVH leaf refit also run on the
 * dispatcher, as one call over disjoint body ranges, when the world holds at
 * least this many bodies and no awake body uses CCD; the step stays
 * bit-identical to the serial one. 0 restores PHYSICS_PARALLEL_MIN_BODIES. */
void          physics_world_set_parallel_min_bodies(PhysicsWorld *pw, u32 min_bodies);
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

/* In-process snapshot of bodies, constraints and world counters, for replay
 * and rollback within one build. Not a wire or on-disk format. Callbacks and
 * post-step hooks are not saved. Saving marks the BVH cache for rebuild, so
 * the saved run and a run restored from the snapshot take the same
 * broadphase path and stay bit-identical under the same inputs.
 * save: returns false when capacity is too small and leaves the buffer
 * untouched; *out_size always receives the required byte count.
 * restore: validates magic, version, layout sizes, body count against the
 * world's capacity and the exact length; on failure the world is unchanged. */
usize         physics_snapshot_size(const PhysicsWorld *pw);
bool          physics_snapshot_save(PhysicsWorld *pw, void *buffer, usize capacity, usize *out_size);
bool          physics_snapshot_restore(PhysicsWorld *pw, const void *buffer, usize size);
/* FNV-1a over each body's position, velocity, orientation, angular velocity
 * and sleep state. Equal states give equal hashes. */
u64           physics_state_hash(const PhysicsWorld *pw);

bool          physics_collide(const RigidBody *a, const RigidBody *b, Contact *out);
AABB  aabb_from_body(const RigidBody *b);
bool  aabb_overlap(AABB a, AABB b);
Vec3  aabb_overlap_depth(AABB a, AABB b);
