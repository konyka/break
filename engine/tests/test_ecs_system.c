/* ==========================================================================
 *  test_ecs_system.c — ECS task-parallel system scheduler tests.
 * ========================================================================== */

#include "test_framework.h"
#include <ecs/ecs.h>
#include <ecs/ecs_system.h>
#include <task/task.h>

#define COMP_POSITION 1
#define COMP_VELOCITY 2
#define COMP_TAG      3

typedef struct { float x, y, z; } Position;
typedef struct { float vx, vy, vz; } Velocity;
typedef struct { int counted; } Tag;

/* System: integrate position by velocity (per-chunk). */
static void sys_integrate(EcsChunkView *v, void *user) {
    float dt = *(float *)user;
    Position *pos = (Position *)ecs_chunk_column(v, COMP_POSITION);
    Velocity *vel = (Velocity *)ecs_chunk_column(v, COMP_VELOCITY);
    if (!pos || !vel) return;
    for (u32 i = 0; i < v->count; i++) {
        pos[i].x += vel[i].vx * dt;
        pos[i].y += vel[i].vy * dt;
        pos[i].z += vel[i].vz * dt;
    }
}

/* System: count touched entities atomically (verifies all chunks visited). */
#include <stdatomic.h>
static _Atomic int g_visited;
static void sys_count(EcsChunkView *v, void *user) {
    (void)user;
    atomic_fetch_add(&g_visited, (int)v->count);
}

static World *make_world_with_entities(int n_pv, int n_p_only) {
    World *w = world_create();
    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));
    world_register_component(w, COMP_TAG, sizeof(Tag));
    for (int i = 0; i < n_pv; i++) {
        Entity e = world_create_entity(w);
        Position *p = (Position *)world_add_component(w, e, COMP_POSITION);
        p->x = (float)i; p->y = 0; p->z = 0;
        Velocity *vel = (Velocity *)world_add_component(w, e, COMP_VELOCITY);
        vel->vx = 1.0f; vel->vy = 2.0f; vel->vz = 3.0f;
    }
    for (int i = 0; i < n_p_only; i++) {
        Entity e = world_create_entity(w);
        Position *p = (Position *)world_add_component(w, e, COMP_POSITION);
        p->x = -1.0f;
    }
    return w;
}

/* ---- parallel-for visits every matching entity exactly once ---- */
TEST(ecs_parallel_for_visits_all) {
    World *w = make_world_with_entities(500, 100);
    TaskSystem *ts = task_system_create(4);
    ASSERT_NOT_NULL(ts);

    atomic_store(&g_visited, 0);
    ComponentType types[] = { COMP_POSITION, COMP_VELOCITY };
    ecs_parallel_for(w, ts, types, 2, sys_count, NULL);
    ASSERT_EQ(atomic_load(&g_visited), 500);

    task_system_destroy(ts);
    world_destroy(w);
}

/* ---- serial mode (ts == NULL) also visits all ---- */
TEST(ecs_parallel_for_serial) {
    World *w = make_world_with_entities(123, 7);
    atomic_store(&g_visited, 0);
    ComponentType types[] = { COMP_POSITION, COMP_VELOCITY };
    ecs_parallel_for(w, NULL, types, 2, sys_count, NULL);
    ASSERT_EQ(atomic_load(&g_visited), 123);
    world_destroy(w);
}

/* ---- system mutates component data correctly under parallel dispatch ---- */
TEST(ecs_parallel_for_mutates_data) {
    const int N = 2000;
    World *w = make_world_with_entities(N, 0);
    /* Keep entity handles to verify after. */
    TaskSystem *ts = task_system_create(0); /* auto */
    ASSERT_NOT_NULL(ts);

    float dt = 0.5f;
    ComponentType types[] = { COMP_POSITION, COMP_VELOCITY };
    ecs_parallel_for(w, ts, types, 2, sys_integrate, &dt);

    /* Re-iterate and verify pos.y == vy*dt for all P+V entities. */
    Query *q = world_query(w, types, 2);
    int checked = 0;
    for (u32 ai = 0; ai < q->match_count; ai++) {
        for (Chunk *c = q->matching[ai]->chunks; c; c = c->next) {
            EcsChunkView v = { w, q->matching[ai], c, c->count };
            Position *p = (Position *)ecs_chunk_column(&v, COMP_POSITION);
            for (u32 i = 0; i < c->count; i++) {
                ASSERT_FLOAT_EQ(p[i].y, 2.0f * dt, 1e-4f);
                ASSERT_FLOAT_EQ(p[i].z, 3.0f * dt, 1e-4f);
                checked++;
            }
        }
    }
    query_done(q);
    ASSERT_EQ(checked, N);

    task_system_destroy(ts);
    world_destroy(w);
}

/* ---- scheduler runs registered systems in order ---- */
static _Atomic int g_order_idx;
static int g_order[4];
static void sys_order_a(EcsChunkView *v, void *user) {
    (void)v; (void)user;
    int idx = atomic_fetch_add(&g_order_idx, 1);
    if (idx < 4) g_order[idx] = 1;
}
static void sys_order_b(EcsChunkView *v, void *user) {
    (void)v; (void)user;
    int idx = atomic_fetch_add(&g_order_idx, 1);
    if (idx < 4) g_order[idx] = 2;
}

TEST(ecs_scheduler_runs_systems) {
    World *w = make_world_with_entities(10, 0); /* single chunk -> single invocation each */
    TaskSystem *ts = task_system_create(2);

    EcsScheduler sched;
    ecs_scheduler_init(&sched);
    ComponentType types[] = { COMP_POSITION, COMP_VELOCITY };
    ASSERT_TRUE(ecs_system_register(&sched, "A", types, 2, sys_order_a, NULL, false));
    ASSERT_TRUE(ecs_system_register(&sched, "B", types, 2, sys_order_b, NULL, false));
    ASSERT_EQ(ecs_scheduler_system_count(&sched), 2u);

    atomic_store(&g_order_idx, 0);
    g_order[0] = g_order[1] = 0;
    ecs_scheduler_run(&sched, w, ts);

    /* System A must have run before system B (sequential ordering). */
    ASSERT_EQ(g_order[0], 1);
    ASSERT_EQ(g_order[1], 2);

    task_system_destroy(ts);
    world_destroy(w);
}

/* ---- empty query does not crash ---- */
TEST(ecs_parallel_for_empty) {
    World *w = world_create();
    world_register_component(w, COMP_TAG, sizeof(Tag));
    TaskSystem *ts = task_system_create(2);
    atomic_store(&g_visited, 0);
    ComponentType types[] = { COMP_TAG };
    ecs_parallel_for(w, ts, types, 1, sys_count, NULL);
    ASSERT_EQ(atomic_load(&g_visited), 0);
    task_system_destroy(ts);
    world_destroy(w);
}

/* ---- nested dispatch: a system callback that dispatches again ----
 * The parallel job pool is a single shared static buffer; a nested
 * ecs_parallel_for used to overwrite entries the outer call's workers hadn't
 * dequeued yet (outer jobs ran with the inner call's fn/view/user or were
 * lost). Nested calls must fall back to the serial path and both levels must
 * produce correct results. */
static World      *g_nested_inner_world;
static TaskSystem *g_nested_ts;
static _Atomic int g_outer_visited;
static _Atomic int g_outer_calls;
static _Atomic int g_inner_visited;

static void sys_nested_inner(EcsChunkView *v, void *user) {
    (void)user;
    atomic_fetch_add(&g_inner_visited, (int)v->count);
}

static void sys_nested_outer(EcsChunkView *v, void *user) {
    (void)user;
    atomic_fetch_add(&g_outer_calls, 1);
    atomic_fetch_add(&g_outer_visited, (int)v->count);
    ComponentType inner_types[] = { COMP_TAG };
    ecs_parallel_for(g_nested_inner_world, g_nested_ts, inner_types, 1,
                     sys_nested_inner, NULL);
}

TEST(ecs_parallel_for_nested_dispatch) {
    /* 2000 P+V entities: chunk capacity is ~582, so several outer jobs. */
    World *outer_w = make_world_with_entities(2000, 0);
    World *inner_w = world_create();
    world_register_component(inner_w, COMP_TAG, sizeof(Tag));
    const int INNER_N = 64;
    for (int i = 0; i < INNER_N; i++) {
        Entity e = world_create_entity(inner_w);
        world_add_component(inner_w, e, COMP_TAG);
    }
    g_nested_inner_world = inner_w;

    TaskSystem *ts = task_system_create(4);
    ASSERT_NOT_NULL(ts);
    g_nested_ts = ts;

    atomic_store(&g_outer_visited, 0);
    atomic_store(&g_outer_calls, 0);
    atomic_store(&g_inner_visited, 0);
    ComponentType types[] = { COMP_POSITION, COMP_VELOCITY };
    ecs_parallel_for(outer_w, ts, types, 2, sys_nested_outer, NULL);

    /* Every outer entity visited exactly once... */
    ASSERT_EQ(atomic_load(&g_outer_visited), 2000);
    /* ...and each outer chunk invocation ran one complete inner pass. */
    ASSERT_TRUE(atomic_load(&g_outer_calls) > 1); /* multi-job: pool in use */
    ASSERT_EQ(atomic_load(&g_inner_visited),
              INNER_N * atomic_load(&g_outer_calls));

    task_system_destroy(ts);
    world_destroy(inner_w);
    world_destroy(outer_w);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ecs_parallel_for_visits_all);
    RUN_TEST(ecs_parallel_for_serial);
    RUN_TEST(ecs_parallel_for_mutates_data);
    RUN_TEST(ecs_scheduler_runs_systems);
    RUN_TEST(ecs_parallel_for_empty);
    RUN_TEST(ecs_parallel_for_nested_dispatch);
TEST_MAIN_END()
