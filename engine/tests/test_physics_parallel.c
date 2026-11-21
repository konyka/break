#include "test_framework.h"
#include <physics/physics.h>
#include <physics/physics_task.h>
#include <task/task.h>
#include <stdatomic.h>
#include <string.h>

/* The parallel contact solve splits the step's pairs into islands of
 * dynamic bodies and solves islands on different jobs. Every body sees its
 * pairs in the serial order, and world statistics are replayed in pair
 * order, so the result must be bit-identical to the serial solve whatever
 * the job count or the order in which jobs run. */

typedef struct {
    u32 calls;
    u32 jobs;
} InlineDispatch;

static void dispatch_forward(void *user, PhysicsJobFn fn, void *job_ctx, u32 job_count) {
    InlineDispatch *d = (InlineDispatch *)user;
    d->calls++;
    d->jobs += job_count;
    for (u32 i = 0; i < job_count; i++) fn(job_ctx, i);
}

static void dispatch_reverse(void *user, PhysicsJobFn fn, void *job_ctx, u32 job_count) {
    InlineDispatch *d = (InlineDispatch *)user;
    d->calls++;
    d->jobs += job_count;
    for (u32 i = job_count; i > 0; i--) fn(job_ctx, i - 1u);
}

/* A ground slab, a row of separate stacks (many small islands), one wide
 * pile (a large island), spheres and capsules, and a heavy box resting on a
 * mass-zero platform shared by several stacks. */
static PhysicsWorld *build_scene(void) {
    PhysicsWorld *pw = physics_world_create(512);
    if (!pw) return NULL;
    (void)physics_body_create(pw, vec3(0, -1, 0), vec3(60, 1, 60), 0.0f, true, 0);
    for (u32 s = 0; s < 24u; s++) {
        f32 x = -46.0f + (f32)s * 4.0f;
        for (u32 h = 0; h < 5u; h++) {
            f32 y = 0.5f + (f32)h * 0.95f;
            if (h % 2u == 0u) {
                (void)physics_body_create(pw, vec3(x + 0.01f * (f32)h, y, 0), vec3(0.5f, 0.5f, 0.5f),
                                          1.0f + 0.1f * (f32)h, false, 0);
            } else {
                (void)physics_body_create_sphere(pw, vec3(x, y, 0.02f * (f32)s), 0.5f, 0.8f, false, 0);
            }
        }
    }
    for (u32 i = 0; i < 60u; i++) {
        f32 x = -6.0f + (f32)(i % 10u) * 0.9f;
        f32 z = 8.0f + (f32)(i / 10u) * 0.45f;
        f32 y = 0.6f + (f32)(i / 10u) * 0.9f;
        if (i % 3u == 0u) {
            (void)physics_body_create_capsule(pw, vec3(x, y + 0.3f, z), 0.3f, 0.3f, 1.2f, false, 0);
        } else {
            (void)physics_body_create(pw, vec3(x, y, z), vec3(0.45f, 0.45f, 0.45f), 1.0f, false, 0);
        }
    }
    (void)physics_body_create(pw, vec3(20, 3, -10), vec3(6, 0.25f, 2), 0.0f, false, 0);
    for (u32 i = 0; i < 6u; i++) {
        (void)physics_body_create(pw, vec3(15.5f + (f32)i * 1.8f, 3.8f, -10), vec3(0.5f, 0.5f, 0.5f),
                                  2.0f, false, 0);
    }
    return pw;
}

static void kick(PhysicsWorld *pw, u32 step) {
    if (step % 30u != 0u) return;
    for (u32 i = 1; i < pw->count; i += 7u) {
        PhysicsBodyHandle h = {i, pw->bodies[i].generation};
        physics_body_apply_impulse(pw, h, vec3(0.3f, 2.5f, -0.2f * (f32)(i % 3u)));
    }
}

/* Everything the solve writes: bodies (all fields, including contact
 * bookkeeping and collision counts) and the world statistics. */
static bool worlds_equal(const PhysicsWorld *a, const PhysicsWorld *b) {
    if (a->count != b->count) return false;
    if (memcmp(a->bodies, b->bodies, (usize)a->count * sizeof(RigidBody)) != 0) return false;
    if (a->collision_count != b->collision_count || a->respawn_count != b->respawn_count) return false;
    if (memcmp(&a->last_collision_pos, &b->last_collision_pos, sizeof(Vec3)) != 0) return false;
    if (a->hot_pair_a != b->hot_pair_a || a->hot_pair_b != b->hot_pair_b ||
        a->hot_pair_count != b->hot_pair_count) return false;
    if (memcmp(&a->total_collision_speed, &b->total_collision_speed, sizeof(f32)) != 0) return false;
    if (memcmp(&a->collision_center, &b->collision_center, sizeof(Vec3)) != 0) return false;
    if (a->collision_center_count != b->collision_center_count) return false;
    if (memcmp(&a->total_impulse_axis, &b->total_impulse_axis, sizeof(Vec3)) != 0) return false;
    /* the broadphase tree, which the leaf refits write */
    if (a->bvh.node_count != b->bvh.node_count || a->bvh.root != b->bvh.root) return false;
    for (u32 n = 0; n < a->bvh.node_count; n++) {
        if (memcmp(&a->bvh.nodes[n].bounds, &b->bvh.nodes[n].bounds, sizeof(BVHAABB)) != 0) return false;
    }
    return physics_state_hash(a) == physics_state_hash(b);
}

static void run_against_serial(PhysicsParallelForFn fn, void *user, u32 max_jobs, u32 *out_mismatch) {
    PhysicsWorld *serial = build_scene();
    PhysicsWorld *parallel = build_scene();
    *out_mismatch = UINT32_MAX;
    if (!serial || !parallel) {
        *out_mismatch = 0u;
    } else {
        physics_world_set_parallel_for(parallel, fn, user, max_jobs);
        physics_world_set_parallel_min_pairs(parallel, 32u);
        for (u32 step = 0; step < 240u; step++) {
            kick(serial, step);
            kick(parallel, step);
            physics_step(serial, 1.0f / 60.0f);
            physics_step(parallel, 1.0f / 60.0f);
            if (!worlds_equal(serial, parallel)) {
                *out_mismatch = step;
                break;
            }
        }
    }
    physics_world_destroy(serial);
    physics_world_destroy(parallel);
}

TEST(inline_forward_jobs_match_the_serial_solve) {
    InlineDispatch d = {0u, 0u};
    u32 mismatch;
    run_against_serial(dispatch_forward, &d, 8u, &mismatch);
    ASSERT_EQ(mismatch, UINT32_MAX);
    ASSERT_TRUE(d.calls > 200u);
    ASSERT_TRUE(d.jobs > d.calls);
}

TEST(reverse_job_order_matches_the_serial_solve) {
    InlineDispatch d = {0u, 0u};
    u32 mismatch;
    run_against_serial(dispatch_reverse, &d, 16u, &mismatch);
    ASSERT_EQ(mismatch, UINT32_MAX);
    ASSERT_TRUE(d.calls > 200u);
}

TEST(every_job_count_matches_the_serial_solve) {
    static const u32 counts[] = {1u, 2u, 3u, 7u, PHYSICS_MAX_PARALLEL_JOBS};
    for (u32 i = 0; i < sizeof(counts) / sizeof(counts[0]); i++) {
        InlineDispatch d = {0u, 0u};
        u32 mismatch;
        run_against_serial(dispatch_reverse, &d, counts[i], &mismatch);
        ASSERT_EQ(mismatch, UINT32_MAX);
        ASSERT_TRUE(d.jobs <= d.calls * counts[i]);
    }
}

TEST(task_system_workers_match_the_serial_solve) {
    TaskSystem *ts = task_system_create(4);
    ASSERT_NOT_NULL(ts);
    u32 mismatch;
    run_against_serial(physics_task_parallel_for, ts, 8u, &mismatch);
    task_system_destroy(ts);
    ASSERT_EQ(mismatch, UINT32_MAX);
}

static u32 g_contacts;
static void count_contact(const Contact *c, void *user) {
    (void)c;
    (void)user;
    g_contacts++;
}

/* A contact callback may read the world in the middle of the solve, which
 * only the serial order can reproduce, so the solve stays serial. */
TEST(contact_callback_keeps_the_solve_serial) {
    PhysicsWorld *pw = build_scene();
    ASSERT_NOT_NULL(pw);
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(pw, dispatch_forward, &d, 8u);
    physics_world_set_parallel_min_pairs(pw, 32u);
    physics_set_contact_callback(pw, count_contact, NULL);
    g_contacts = 0u;
    for (u32 step = 0; step < 30u; step++) physics_step(pw, 1.0f / 60.0f);
    physics_world_destroy(pw);
    ASSERT_EQ(d.calls, 0u);
    ASSERT_TRUE(g_contacts > 0u);
}

/* The default minimum keeps scenes of a few hundred pairs serial, the pair
 * collection included: the dispatch costs more than it saves there. */
TEST(default_minimum_keeps_this_scene_serial) {
    PhysicsWorld *pw = build_scene();
    ASSERT_NOT_NULL(pw);
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(pw, dispatch_forward, &d, 8u);
    for (u32 step = 0; step < 10u; step++) physics_step(pw, 1.0f / 60.0f);
    ASSERT_TRUE(pw->collision_count > 32u && pw->collision_count < PHYSICS_PARALLEL_MIN_PAIRS);
    physics_world_destroy(pw);
    ASSERT_EQ(d.calls, 0u);
}

/* Few pairs: the dispatch overhead is not worth it and the solve is serial. */
TEST(small_scenes_stay_serial) {
    PhysicsWorld *pw = physics_world_create(8);
    ASSERT_NOT_NULL(pw);
    (void)physics_body_create(pw, vec3(0, -1, 0), vec3(10, 1, 10), 0.0f, true, 0);
    (void)physics_body_create(pw, vec3(0, 0.4f, 0), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(pw, dispatch_forward, &d, 8u);
    physics_world_set_parallel_min_pairs(pw, 32u);
    for (u32 step = 0; step < 30u; step++) physics_step(pw, 1.0f / 60.0f);
    physics_world_destroy(pw);
    ASSERT_EQ(d.calls, 0u);
}

TEST(clearing_the_dispatcher_returns_to_serial) {
    PhysicsWorld *pw = build_scene();
    ASSERT_NOT_NULL(pw);
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(pw, dispatch_forward, &d, 8u);
    physics_world_set_parallel_min_pairs(pw, 32u);
    physics_step(pw, 1.0f / 60.0f);
    u32 calls = d.calls;
    ASSERT_TRUE(calls > 0u);
    physics_world_set_parallel_for(pw, NULL, NULL, 0u);
    for (u32 step = 0; step < 10u; step++) physics_step(pw, 1.0f / 60.0f);
    ASSERT_EQ(d.calls, calls);
    physics_world_set_parallel_for(pw, dispatch_forward, &d, 0u);
    physics_step(pw, 1.0f / 60.0f);
    ASSERT_EQ(d.calls, calls);
    physics_world_destroy(pw);
}

typedef struct {
    u32 pairs[4096][2];
    u32 count;
} PairList;

static void record_pair(u32 a, u32 b, void *ctx) {
    PairList *l = (PairList *)ctx;
    if (l->count < 4096u) {
        l->pairs[l->count][0] = a;
        l->pairs[l->count][1] = b;
    }
    l->count++;
}

/* Running the subtree tasks in order must report exactly the pairs of the
 * full traversal, in the same order, at every split depth. */
TEST(bvh_pair_tasks_concatenate_to_the_full_traversal) {
    PhysicsWorld *pw = build_scene();
    ASSERT_NOT_NULL(pw);
    for (u32 step = 0; step < 20u; step++) physics_step(pw, 1.0f / 60.0f);
    static PairList full;
    static PairList split;
    full.count = 0u;
    bvh_query_pairs(&pw->bvh, record_pair, &full);
    ASSERT_TRUE(full.count > 100u && full.count <= 4096u);
    static BVHPairTask tasks[4096];
    for (u32 depth = 0; depth <= 14u; depth++) {
        u32 n = bvh_pair_tasks(&pw->bvh, depth, tasks, 4096u);
        ASSERT_TRUE(n >= 1u && n <= 4096u);
        split.count = 0u;
        for (u32 t = 0; t < n; t++) bvh_query_pairs_from(&pw->bvh, tasks[t], record_pair, &split);
        ASSERT_EQ(split.count, full.count);
        ASSERT_EQ(memcmp(split.pairs, full.pairs, (usize)full.count * sizeof(full.pairs[0])), 0);
    }
    ASSERT_TRUE(bvh_pair_tasks(&pw->bvh, 14u, tasks, 4u) > 4u);
    physics_world_destroy(pw);
}

/* Above the minimum, pairs are collected on jobs too: two dispatches per
 * step, except the first, which has no previous pair count. */
TEST(collection_and_solve_both_dispatch) {
    PhysicsWorld *pw = build_scene();
    ASSERT_NOT_NULL(pw);
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(pw, dispatch_forward, &d, 4u);
    physics_world_set_parallel_min_pairs(pw, 32u);
    for (u32 step = 0; step < 10u; step++) physics_step(pw, 1.0f / 60.0f);
    physics_world_destroy(pw);
    ASSERT_EQ(d.calls, 19u);
}

typedef struct {
    u32 hits[40];
    i32 worker_seen;
    TaskSystem *ts;
    atomic_bool done;
    i32 job_worker[8];
} AdapterProbe;

static void adapter_job(void *raw, u32 i) {
    AdapterProbe *p = (AdapterProbe *)raw;
    if (i < 40u) p->hits[i]++;
    if (p->ts && i < 8u) p->job_worker[i] = task_worker_id(p->ts);
}

/* Jobs beyond PHYSICS_MAX_PARALLEL_JOBS still run, each exactly once. */
TEST(task_adapter_runs_every_job_once) {
    TaskSystem *ts = task_system_create(4);
    ASSERT_NOT_NULL(ts);
    AdapterProbe p;
    memset(&p, 0, sizeof(p));
    for (u32 round = 0; round < 300u; round++) physics_task_parallel_for(ts, adapter_job, &p, 40u);
    task_system_destroy(ts);
    for (u32 i = 0; i < 40u; i++) ASSERT_EQ(p.hits[i], 300u);
}

static void adapter_from_worker(void *raw) {
    AdapterProbe *p = (AdapterProbe *)raw;
    p->worker_seen = task_worker_id(p->ts);
    physics_task_parallel_for(p->ts, adapter_job, p, 8u);
    atomic_store_explicit(&p->done, true, memory_order_release);
}

/* Called on a worker thread, the jobs run inline on that worker (waiting
 * there would tie up the worker and, with one worker, never finish) and are
 * all done when the call returns. */
TEST(task_adapter_runs_inline_on_a_worker) {
    TaskSystem *ts = task_system_create(2);
    ASSERT_NOT_NULL(ts);
    AdapterProbe p;
    memset(&p, 0, sizeof(p));
    p.worker_seen = -1;
    p.ts = ts;
    atomic_init(&p.done, false);
    /* waiting on the flag instead of task_wait keeps this thread from
     * running the task inline, so it runs on a worker */
    task_submit(ts, adapter_from_worker, &p);
    while (!atomic_load_explicit(&p.done, memory_order_acquire)) platform_thread_yield();
    task_wait(ts);
    task_system_destroy(ts);
    ASSERT_TRUE(p.worker_seen >= 0);
    for (u32 i = 0; i < 8u; i++) {
        ASSERT_EQ(p.hits[i], 1u);
        ASSERT_EQ(p.job_worker[i], p.worker_seen);
    }
}

/* Integration together with the post-integration BVH leaf refit runs on
 * jobs once the world has enough bodies; contacts stay serial here (huge
 * pair minimum), so each step dispatches exactly once, and the world must
 * stay bit-identical to the serial step. */
TEST(parallel_integration_matches_the_serial_step) {
    PhysicsWorld *serial = build_scene();
    PhysicsWorld *parallel = build_scene();
    ASSERT_NOT_NULL(serial);
    ASSERT_NOT_NULL(parallel);
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(parallel, dispatch_reverse, &d, 8u);
    physics_world_set_parallel_min_pairs(parallel, UINT32_MAX);
    physics_world_set_parallel_min_bodies(parallel, 16u);
    u32 mismatch = UINT32_MAX;
    for (u32 step = 0; step < 240u; step++) {
        kick(serial, step);
        kick(parallel, step);
        physics_step(serial, 1.0f / 60.0f);
        physics_step(parallel, 1.0f / 60.0f);
        if (!worlds_equal(serial, parallel)) {
            mismatch = step;
            break;
        }
    }
    physics_world_destroy(serial);
    physics_world_destroy(parallel);
    ASSERT_EQ(mismatch, UINT32_MAX);
    ASSERT_EQ(d.calls, 240u);
    ASSERT_TRUE(d.jobs > d.calls);
}

TEST(parallel_integration_on_task_workers_matches_the_serial_step) {
    TaskSystem *ts = task_system_create(4);
    ASSERT_NOT_NULL(ts);
    PhysicsWorld *serial = build_scene();
    PhysicsWorld *parallel = build_scene();
    u32 mismatch = UINT32_MAX;
    if (serial && parallel) {
        physics_world_set_parallel_for(parallel, physics_task_parallel_for, ts, 8u);
        physics_world_set_parallel_min_pairs(parallel, 32u);
        physics_world_set_parallel_min_bodies(parallel, 16u);
        for (u32 step = 0; step < 240u && mismatch == UINT32_MAX; step++) {
            kick(serial, step);
            kick(parallel, step);
            physics_step(serial, 1.0f / 60.0f);
            physics_step(parallel, 1.0f / 60.0f);
            if (!worlds_equal(serial, parallel)) mismatch = step;
        }
    }
    physics_world_destroy(serial);
    physics_world_destroy(parallel);
    task_system_destroy(ts);
    ASSERT_EQ(mismatch, UINT32_MAX);
}

/* A CCD body sweeps against bodies already integrated this step, so the
 * order matters and integration stays serial while one is awake. */
TEST(awake_ccd_body_keeps_integration_serial) {
    PhysicsWorld *pw = build_scene();
    ASSERT_NOT_NULL(pw);
    PhysicsBodyHandle fast = physics_body_create_sphere(pw, vec3(0, 6, -20), 0.2f, 1.0f, false, 0);
    physics_body_set_ccd(pw, fast, true);
    physics_body_apply_impulse(pw, fast, vec3(0, 0, 40));
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(pw, dispatch_forward, &d, 8u);
    physics_world_set_parallel_min_pairs(pw, UINT32_MAX);
    physics_world_set_parallel_min_bodies(pw, 16u);
    for (u32 step = 0; step < 10u; step++) physics_step(pw, 1.0f / 60.0f);
    physics_world_destroy(pw);
    ASSERT_EQ(d.calls, 0u);
}

/* Fast CCD bodies crossing the stacks keep integration serial while the
 * contact solve stays parallel; the step must match the serial one. */
static void add_ccd_bodies(PhysicsWorld *pw) {
    for (u32 i = 0; i < 6u; i++) {
        PhysicsBodyHandle h = physics_body_create_sphere(pw, vec3(-40.0f + (f32)i * 15.0f, 2.0f, -6), 0.15f,
                                                         0.5f, false, 0);
        physics_body_set_ccd(pw, h, true);
        physics_body_apply_impulse(pw, h, vec3(0.0f, 0.0f, 30.0f + (f32)i));
    }
}

TEST(parallel_refit_with_ccd_matches_the_serial_step) {
    PhysicsWorld *serial = build_scene();
    PhysicsWorld *parallel = build_scene();
    ASSERT_NOT_NULL(serial);
    ASSERT_NOT_NULL(parallel);
    add_ccd_bodies(serial);
    add_ccd_bodies(parallel);
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(parallel, dispatch_reverse, &d, 8u);
    physics_world_set_parallel_min_pairs(parallel, 32u);
    physics_world_set_parallel_min_bodies(parallel, 16u);
    u32 mismatch = UINT32_MAX;
    for (u32 step = 0; step < 240u && mismatch == UINT32_MAX; step++) {
        kick(serial, step);
        kick(parallel, step);
        physics_step(serial, 1.0f / 60.0f);
        physics_step(parallel, 1.0f / 60.0f);
        if (!worlds_equal(serial, parallel)) mismatch = step;
    }
    physics_world_destroy(serial);
    physics_world_destroy(parallel);
    ASSERT_EQ(mismatch, UINT32_MAX);
    ASSERT_TRUE(d.calls > 0u);
}

/* The default minimum keeps a scene of a few hundred bodies serial. */
TEST(default_body_minimum_keeps_this_scene_serial) {
    PhysicsWorld *pw = build_scene();
    ASSERT_NOT_NULL(pw);
    InlineDispatch d = {0u, 0u};
    physics_world_set_parallel_for(pw, dispatch_forward, &d, 8u);
    physics_world_set_parallel_min_pairs(pw, UINT32_MAX);
    ASSERT_TRUE(pw->count < PHYSICS_PARALLEL_MIN_BODIES);
    for (u32 step = 0; step < 10u; step++) physics_step(pw, 1.0f / 60.0f);
    physics_world_destroy(pw);
    ASSERT_EQ(d.calls, 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(inline_forward_jobs_match_the_serial_solve);
    RUN_TEST(reverse_job_order_matches_the_serial_solve);
    RUN_TEST(every_job_count_matches_the_serial_solve);
    RUN_TEST(task_system_workers_match_the_serial_solve);
    RUN_TEST(contact_callback_keeps_the_solve_serial);
    RUN_TEST(default_minimum_keeps_this_scene_serial);
    RUN_TEST(small_scenes_stay_serial);
    RUN_TEST(clearing_the_dispatcher_returns_to_serial);
    RUN_TEST(bvh_pair_tasks_concatenate_to_the_full_traversal);
    RUN_TEST(collection_and_solve_both_dispatch);
    RUN_TEST(task_adapter_runs_every_job_once);
    RUN_TEST(task_adapter_runs_inline_on_a_worker);
    RUN_TEST(parallel_integration_matches_the_serial_step);
    RUN_TEST(parallel_integration_on_task_workers_matches_the_serial_step);
    RUN_TEST(awake_ccd_body_keeps_integration_serial);
    RUN_TEST(parallel_refit_with_ccd_matches_the_serial_step);
    RUN_TEST(default_body_minimum_keeps_this_scene_serial);
TEST_MAIN_END()
