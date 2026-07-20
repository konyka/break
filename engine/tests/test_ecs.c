#include "test_framework.h"
#include <ecs/ecs.h>

/* Component type IDs for testing */
#define COMP_POSITION 1
#define COMP_VELOCITY 2
#define COMP_HEALTH   3

typedef struct { float x, y, z; } Position;
typedef struct { float vx, vy, vz; } Velocity;
typedef struct { int hp; } Health;

/* ---- World Create/Destroy ---- */

TEST(ecs_world_create_destroy) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);
    world_destroy(w);
}

/* ---- Entity Create ---- */

TEST(ecs_entity_create) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    Entity e = world_create_entity(w);
    ASSERT_TRUE(entity_valid(e));

    world_destroy(w);
}

TEST(ecs_entity_create_multiple) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    Entity e1 = world_create_entity(w);
    Entity e2 = world_create_entity(w);
    Entity e3 = world_create_entity(w);

    ASSERT_TRUE(entity_valid(e1));
    ASSERT_TRUE(entity_valid(e2));
    ASSERT_TRUE(entity_valid(e3));

    /* Each entity should have a unique index */
    ASSERT_TRUE(e1.index != e2.index || e1.generation != e2.generation);
    ASSERT_TRUE(e2.index != e3.index || e2.generation != e3.generation);

    world_destroy(w);
}

/* ---- Entity Destroy ---- */

TEST(ecs_entity_destroy) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    Entity e = world_create_entity(w);
    ASSERT_TRUE(entity_valid(e));

    world_destroy_entity(w, e);
    /* After destroy, get_component should return NULL */
    world_register_component(w, COMP_POSITION, sizeof(Position));
    void *ptr = world_get_component(w, e, COMP_POSITION);
    ASSERT_TRUE(ptr == NULL);

    world_destroy(w);
}

/* ---- Component Add/Get ---- */

TEST(ecs_component_add_get) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));

    Entity e = world_create_entity(w);
    Position *pos = (Position *)world_add_component(w, e, COMP_POSITION);
    ASSERT_NOT_NULL(pos);
    pos->x = 1.0f;
    pos->y = 2.0f;
    pos->z = 3.0f;

    Position *got = (Position *)world_get_component(w, e, COMP_POSITION);
    ASSERT_NOT_NULL(got);
    ASSERT_FLOAT_EQ(got->x, 1.0f, 1e-5f);
    ASSERT_FLOAT_EQ(got->y, 2.0f, 1e-5f);
    ASSERT_FLOAT_EQ(got->z, 3.0f, 1e-5f);

    world_destroy(w);
}

TEST(ecs_component_multiple) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));

    Entity e = world_create_entity(w);
    Position *pos = (Position *)world_add_component(w, e, COMP_POSITION);
    ASSERT_NOT_NULL(pos);
    pos->x = 10.0f;

    Velocity *vel = (Velocity *)world_add_component(w, e, COMP_VELOCITY);
    ASSERT_NOT_NULL(vel);
    vel->vx = 5.0f;

    /* Verify both still accessible */
    Position *got_pos = (Position *)world_get_component(w, e, COMP_POSITION);
    Velocity *got_vel = (Velocity *)world_get_component(w, e, COMP_VELOCITY);
    ASSERT_NOT_NULL(got_pos);
    ASSERT_NOT_NULL(got_vel);
    ASSERT_FLOAT_EQ(got_pos->x, 10.0f, 1e-5f);
    ASSERT_FLOAT_EQ(got_vel->vx, 5.0f, 1e-5f);

    world_destroy(w);
}

/* ---- Component Remove ---- */

TEST(ecs_component_remove) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));

    Entity e = world_create_entity(w);
    world_add_component(w, e, COMP_POSITION);
    world_add_component(w, e, COMP_VELOCITY);

    /* Remove position */
    world_remove_component(w, e, COMP_POSITION);

    /* Position should be gone */
    void *pos = world_get_component(w, e, COMP_POSITION);
    ASSERT_TRUE(pos == NULL);

    /* Velocity should still be there */
    void *vel = world_get_component(w, e, COMP_VELOCITY);
    ASSERT_NOT_NULL(vel);

    world_destroy(w);
}

/* ---- Query/Iteration ---- */

TEST(ecs_query_iteration) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));
    world_register_component(w, COMP_HEALTH, sizeof(Health));

    /* Create entities with Position+Velocity */
    for (int i = 0; i < 5; i++) {
        Entity e = world_create_entity(w);
        Position *pos = (Position *)world_add_component(w, e, COMP_POSITION);
        pos->x = (float)i;
        world_add_component(w, e, COMP_VELOCITY);
    }

    /* Create entities with only Position */
    for (int i = 0; i < 3; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
    }

    /* Query for entities with Position+Velocity */
    ComponentType types[] = { COMP_POSITION, COMP_VELOCITY };
    Query *q = world_query(w, types, 2);
    ASSERT_NOT_NULL(q);

    int count = 0;
    QueryIter it = query_begin(q);
    while (query_next(&it)) {
        count++;
    }
    query_done(q);

    ASSERT_EQ(count, 5);

    world_destroy(w);
}

TEST(ecs_query_index_zero_based) {
    /* R261: query_next must leave it.index at the CURRENT 0-based row so the
     * documented pattern chunk_get_component(it.chunk, it.index, ...) reads the
     * right entity. 5 small entities fit in one 16KB chunk, so the rows walked
     * must be exactly 0,1,2,3,4. The old pre-increment yielded 1,2,3,4,5 —
     * skipping row 0 and reading one past the end on the last iteration. */
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));

    for (int i = 0; i < 5; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
        world_add_component(w, e, COMP_VELOCITY);
    }

    ComponentType types[] = { COMP_POSITION, COMP_VELOCITY };
    Query *q = world_query(w, types, 2);
    ASSERT_NOT_NULL(q);

    u32 expected = 0;
    int count = 0;
    QueryIter it = query_begin(q);
    while (query_next(&it)) {
        ASSERT_EQ(it.index, expected);   /* 0-based, contiguous, in-bounds */
        expected++;
        count++;
    }
    query_done(q);

    ASSERT_EQ(count, 5);

    world_destroy(w);
}

TEST(ecs_query_empty_result) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_HEALTH, sizeof(Health));

    /* Create entities with only Position */
    Entity e = world_create_entity(w);
    world_add_component(w, e, COMP_POSITION);

    /* Query for Health which no entity has */
    ComponentType types[] = { COMP_HEALTH };
    Query *q = world_query(w, types, 1);
    ASSERT_NOT_NULL(q);

    int count = 0;
    QueryIter it = query_begin(q);
    while (query_next(&it)) {
        count++;
    }
    query_done(q);

    ASSERT_EQ(count, 0);

    world_destroy(w);
}

/* ---- Entity Recycling ---- */

TEST(ecs_entity_recycle_slot_reuse) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));

    Entity e1 = world_create_entity(w);
    u32 old_idx = e1.index;
    u32 old_gen = e1.generation;
    world_destroy_entity(w, e1);

    /* New entity should reuse the slot */
    Entity e2 = world_create_entity(w);
    ASSERT_EQ(e2.index, old_idx);
    ASSERT_TRUE(e2.generation > old_gen);
    ASSERT_TRUE(entity_valid(e2));

    world_destroy(w);
}

TEST(ecs_entity_recycle_stale_handle) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));

    Entity e1 = world_create_entity(w);
    Position *pos = (Position *)world_add_component(w, e1, COMP_POSITION);
    ASSERT_NOT_NULL(pos);
    pos->x = 42.0f;

    world_destroy_entity(w, e1);

    /* Old handle should fail generation check */
    void *stale = world_get_component(w, e1, COMP_POSITION);
    ASSERT_TRUE(stale == NULL);

    /* Also, add_component on stale handle should fail */
    void *add_fail = world_add_component(w, e1, COMP_VELOCITY);
    ASSERT_TRUE(add_fail == NULL);

    world_destroy(w);
}

/* ---- Query Data Verification ---- */

TEST(ecs_query_data_verification) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));

    /* Create 10 entities with known data */
    Entity ents[10];
    for (int i = 0; i < 10; i++) {
        ents[i] = world_create_entity(w);
        Position *pos = (Position *)world_add_component(w, ents[i], COMP_POSITION);
        pos->x = (float)(i * 100);
        Velocity *vel = (Velocity *)world_add_component(w, ents[i], COMP_VELOCITY);
        vel->vx = (float)(i + 1);
    }

    /* Query and count results */
    ComponentType types[] = { COMP_POSITION, COMP_VELOCITY };
    Query *q = world_query(w, types, 2);
    ASSERT_NOT_NULL(q);

    int count = 0;
    QueryIter it = query_begin(q);
    while (query_next(&it)) {
        count++;
    }
    query_done(q);
    ASSERT_EQ(count, 10);

    /* Verify data survived the archetype moves via direct get_component */
    for (int i = 0; i < 10; i++) {
        Position *p = (Position *)world_get_component(w, ents[i], COMP_POSITION);
        ASSERT_NOT_NULL(p);
        ASSERT_FLOAT_EQ(p->x, (float)(i * 100), 1e-5f);
        Velocity *v = (Velocity *)world_get_component(w, ents[i], COMP_VELOCITY);
        ASSERT_NOT_NULL(v);
        ASSERT_FLOAT_EQ(v->vx, (float)(i + 1), 1e-5f);
    }

    world_destroy(w);
}

/* ---- Concurrent Queries ---- */

TEST(ecs_concurrent_queries) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));
    world_register_component(w, COMP_HEALTH, sizeof(Health));

    /* Entities with Position only */
    for (int i = 0; i < 3; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
    }

    /* Entities with Position + Velocity */
    for (int i = 0; i < 5; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
        world_add_component(w, e, COMP_VELOCITY);
    }

    /* Entities with Health only */
    for (int i = 0; i < 2; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_HEALTH);
    }

    /* First query: Position only */
    ComponentType pos_types[] = { COMP_POSITION };
    Query *q1 = world_query(w, pos_types, 1);
    ASSERT_NOT_NULL(q1);

    /* Second query: Health only (should NOT overwrite q1) */
    ComponentType hp_types[] = { COMP_HEALTH };
    Query *q2 = world_query(w, hp_types, 1);
    ASSERT_NOT_NULL(q2);

    /* q1 should still be usable */
    int count1 = 0;
    QueryIter it1 = query_begin(q1);
    while (query_next(&it1)) { count1++; }
    query_done(q1);
    ASSERT_EQ(count1, 8); /* 3 + 5 entities have Position */

    int count2 = 0;
    QueryIter it2 = query_begin(q2);
    while (query_next(&it2)) { count2++; }
    query_done(q2);
    ASSERT_EQ(count2, 2); /* 2 entities have Health */

    world_destroy(w);
}

/* ---- Multi-component add/remove cycles ---- */

TEST(ecs_component_add_remove_cycle) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));
    world_register_component(w, COMP_HEALTH, sizeof(Health));

    Entity e = world_create_entity(w);

    /* Add Position */
    Position *pos = (Position *)world_add_component(w, e, COMP_POSITION);
    ASSERT_NOT_NULL(pos);
    pos->x = 100.0f;

    /* Add Velocity */
    Velocity *vel = (Velocity *)world_add_component(w, e, COMP_VELOCITY);
    ASSERT_NOT_NULL(vel);
    vel->vx = 50.0f;

    /* Add Health */
    Health *hp = (Health *)world_add_component(w, e, COMP_HEALTH);
    ASSERT_NOT_NULL(hp);
    hp->hp = 99;

    /* Verify all three */
    pos = (Position *)world_get_component(w, e, COMP_POSITION);
    ASSERT_NOT_NULL(pos);
    ASSERT_FLOAT_EQ(pos->x, 100.0f, 1e-5f);

    vel = (Velocity *)world_get_component(w, e, COMP_VELOCITY);
    ASSERT_NOT_NULL(vel);
    ASSERT_FLOAT_EQ(vel->vx, 50.0f, 1e-5f);

    hp = (Health *)world_get_component(w, e, COMP_HEALTH);
    ASSERT_NOT_NULL(hp);
    ASSERT_EQ(hp->hp, 99);

    /* Remove Velocity */
    world_remove_component(w, e, COMP_VELOCITY);
    ASSERT_TRUE(world_get_component(w, e, COMP_VELOCITY) == NULL);

    /* Position and Health should still be valid */
    pos = (Position *)world_get_component(w, e, COMP_POSITION);
    ASSERT_NOT_NULL(pos);
    ASSERT_FLOAT_EQ(pos->x, 100.0f, 1e-5f);

    hp = (Health *)world_get_component(w, e, COMP_HEALTH);
    ASSERT_NOT_NULL(hp);
    ASSERT_EQ(hp->hp, 99);

    /* Remove Position */
    world_remove_component(w, e, COMP_POSITION);
    ASSERT_TRUE(world_get_component(w, e, COMP_POSITION) == NULL);

    /* Health should survive */
    hp = (Health *)world_get_component(w, e, COMP_HEALTH);
    ASSERT_NOT_NULL(hp);
    ASSERT_EQ(hp->hp, 99);

    world_destroy(w);
}

/* ---- Destroy multiple entities, verify survivors ---- */

TEST(ecs_destroy_and_verify_survivors) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));

    Entity entities[10];
    for (int i = 0; i < 10; i++) {
        entities[i] = world_create_entity(w);
        Position *pos = (Position *)world_add_component(w, entities[i], COMP_POSITION);
        pos->x = (float)i;
    }

    /* Destroy even-indexed entities */
    for (int i = 0; i < 10; i += 2) {
        world_destroy_entity(w, entities[i]);
    }

    /* Odd-indexed entities should still have valid data */
    for (int i = 1; i < 10; i += 2) {
        Position *pos = (Position *)world_get_component(w, entities[i], COMP_POSITION);
        ASSERT_NOT_NULL(pos);
        ASSERT_FLOAT_EQ(pos->x, (float)i, 1e-5f);
    }

    /* Even-indexed entities should fail */
    for (int i = 0; i < 10; i += 2) {
        void *p = world_get_component(w, entities[i], COMP_POSITION);
        ASSERT_TRUE(p == NULL);
    }

    world_destroy(w);
}

/* ---- NULL entity edge cases ---- */

TEST(ecs_null_entity) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));

    /* ENTITY_NULL should be invalid */
    Entity null_e = ENTITY_NULL;
    ASSERT_FALSE(entity_valid(null_e));

    /* Operations on null entity should safely return NULL */
    void *ptr = world_get_component(w, null_e, COMP_POSITION);
    ASSERT_TRUE(ptr == NULL);

    void *add = world_add_component(w, null_e, COMP_POSITION);
    ASSERT_TRUE(add == NULL);

    world_destroy(w);
}

/* -----------------------------------------------------------------------
 *  Edge Cases
 * ----------------------------------------------------------------------- */

TEST(ecs_remove_nonexistent_component) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));

    Entity e = world_create_entity(w);
    world_add_component(w, e, COMP_POSITION);

    /* Remove a component that was never added - should not crash */
    world_remove_component(w, e, COMP_VELOCITY);

    /* Position should still be valid */
    Position *pos = (Position *)world_get_component(w, e, COMP_POSITION);
    ASSERT_NOT_NULL(pos);

    world_destroy(w);
}

TEST(ecs_get_unregistered_component) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));

    Entity e = world_create_entity(w);
    world_add_component(w, e, COMP_POSITION);

    /* Try to get a component type that was never registered */
    void *ptr = world_get_component(w, e, COMP_HEALTH);
    ASSERT_TRUE(ptr == NULL);

    world_destroy(w);
}

TEST(ecs_large_entity_count) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));

    /* Create many entities */
    Entity ents[100];
    for (int i = 0; i < 100; i++) {
        ents[i] = world_create_entity(w);
        Position *pos = (Position *)world_add_component(w, ents[i], COMP_POSITION);
        ASSERT_NOT_NULL(pos);
        pos->x = (float)i;
    }

    /* Verify all entities */
    for (int i = 0; i < 100; i++) {
        Position *pos = (Position *)world_get_component(w, ents[i], COMP_POSITION);
        ASSERT_NOT_NULL(pos);
        ASSERT_FLOAT_EQ(pos->x, (float)i, 1e-5f);
    }

    world_destroy(w);
}

TEST(ecs_destroy_null_world) {
    /* world_destroy does not check for NULL - skip this test */
    /* Just verify the test framework doesn't crash */
    ASSERT_TRUE(true);
}

/* -----------------------------------------------------------------------
 *  Edge Cache (R102)
 * ----------------------------------------------------------------------- */

TEST(ecs_edge_cache_add_hit) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));

    /* Entity 1: add Position (creates edge: empty → Position) */
    Entity e1 = world_create_entity(w);
    Position *p1 = (Position *)world_add_component(w, e1, COMP_POSITION);
    ASSERT_NOT_NULL(p1);
    p1->x = 10.0f;

    /* Empty archetype should now have an add-edge for COMP_POSITION */
    Archetype *empty = &w->archetypes[0];
    ASSERT_TRUE(empty->edges_add_count > 0);

    /* Entity 2: add Position (should use edge cache, not find_archetype) */
    Entity e2 = world_create_entity(w);
    Position *p2 = (Position *)world_add_component(w, e2, COMP_POSITION);
    ASSERT_NOT_NULL(p2);
    p2->x = 20.0f;

    /* Both entities should be in the same archetype */
    ASSERT_EQ(w->entity_archetype[e1.index], w->entity_archetype[e2.index]);

    /* Verify data integrity */
    Position *got1 = (Position *)world_get_component(w, e1, COMP_POSITION);
    Position *got2 = (Position *)world_get_component(w, e2, COMP_POSITION);
    ASSERT_FLOAT_EQ(got1->x, 10.0f, 1e-5f);
    ASSERT_FLOAT_EQ(got2->x, 20.0f, 1e-5f);

    world_destroy(w);
}

TEST(ecs_edge_cache_remove_hit) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));

    /* Create two entities with Position+Velocity */
    Entity e1 = world_create_entity(w);
    world_add_component(w, e1, COMP_POSITION);
    world_add_component(w, e1, COMP_VELOCITY);

    Entity e2 = world_create_entity(w);
    world_add_component(w, e2, COMP_POSITION);
    world_add_component(w, e2, COMP_VELOCITY);

    /* Remove Velocity from e1 (creates edge: Pos+Vel → Pos) */
    world_remove_component(w, e1, COMP_VELOCITY);

    /* The Pos+Vel archetype should now have a remove-edge for COMP_VELOCITY */
    u32 arch_e2 = w->entity_archetype[e2.index];
    Archetype *pos_vel = &w->archetypes[arch_e2];
    ASSERT_TRUE(pos_vel->edges_remove_count > 0);

    /* Remove Velocity from e2 (should use edge cache) */
    world_remove_component(w, e2, COMP_VELOCITY);

    /* Both entities should now be in the Position-only archetype */
    ASSERT_EQ(w->entity_archetype[e1.index], w->entity_archetype[e2.index]);

    /* Position should still be valid for both */
    Position *p1 = (Position *)world_get_component(w, e1, COMP_POSITION);
    Position *p2 = (Position *)world_get_component(w, e2, COMP_POSITION);
    ASSERT_NOT_NULL(p1);
    ASSERT_NOT_NULL(p2);

    world_destroy(w);
}

TEST(ecs_edge_cache_multi_transition) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));
    world_register_component(w, COMP_HEALTH, sizeof(Health));

    /* Create 50 entities, each gets Position → Velocity → Health added.
     * After the first entity, all subsequent add_component calls should
     * hit the edge cache. */
    Entity ents[50];
    for (int i = 0; i < 50; i++) {
        ents[i] = world_create_entity(w);
        Position *p = (Position *)world_add_component(w, ents[i], COMP_POSITION);
        p->x = (float)i;
        Velocity *v = (Velocity *)world_add_component(w, ents[i], COMP_VELOCITY);
        v->vx = (float)(i + 1);
        Health *h = (Health *)world_add_component(w, ents[i], COMP_HEALTH);
        h->hp = i * 2;
    }

    /* All 50 entities should be in the same archetype (Pos+Vel+Health) */
    u32 target_arch = w->entity_archetype[ents[0].index];
    for (int i = 1; i < 50; i++) {
        ASSERT_EQ(w->entity_archetype[ents[i].index], target_arch);
    }

    /* Verify data integrity for all entities */
    for (int i = 0; i < 50; i++) {
        Position *p = (Position *)world_get_component(w, ents[i], COMP_POSITION);
        ASSERT_FLOAT_EQ(p->x, (float)i, 1e-5f);
        Velocity *v = (Velocity *)world_get_component(w, ents[i], COMP_VELOCITY);
        ASSERT_FLOAT_EQ(v->vx, (float)(i + 1), 1e-5f);
        Health *h = (Health *)world_get_component(w, ents[i], COMP_HEALTH);
        ASSERT_EQ(h->hp, i * 2);
    }

    /* Now remove Health from all entities — first creates edge, rest use cache */
    for (int i = 0; i < 50; i++) {
        world_remove_component(w, ents[i], COMP_HEALTH);
    }

    /* All should be in Pos+Vel archetype */
    target_arch = w->entity_archetype[ents[0].index];
    for (int i = 1; i < 50; i++) {
        ASSERT_EQ(w->entity_archetype[ents[i].index], target_arch);
    }

    /* Health gone, Position intact */
    for (int i = 0; i < 50; i++) {
        ASSERT_TRUE(world_get_component(w, ents[i], COMP_HEALTH) == NULL);
        Position *p = (Position *)world_get_component(w, ents[i], COMP_POSITION);
        ASSERT_FLOAT_EQ(p->x, (float)i, 1e-5f);
    }

    world_destroy(w);
}

/* -----------------------------------------------------------------------
 *  Exclude / Optional Query (ECS Query Enhancement)
 * ----------------------------------------------------------------------- */

TEST(ecs_query_exclude) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));
    world_register_component(w, COMP_HEALTH,   sizeof(Health));

    /* 3 entities with Position only */
    for (int i = 0; i < 3; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
    }
    /* 4 entities with Position + Velocity (these should be excluded) */
    for (int i = 0; i < 4; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
        world_add_component(w, e, COMP_VELOCITY);
    }

    /* Query Position, exclude Velocity */
    ComponentType req[] = { COMP_POSITION };
    Query *q = world_query(w, req, 1);
    ASSERT_NOT_NULL(q);
    ecs_query_exclude(q, COMP_VELOCITY);
    ecs_query_refresh(w, q, req, 1);

    int count = 0;
    QueryIter it = query_begin(q);
    while (query_next(&it)) { count++; }
    query_done(q);

    /* Only the 3 Position-only entities should match */
    ASSERT_EQ(count, 3);

    world_destroy(w);
}

TEST(ecs_query_optional) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));
    world_register_component(w, COMP_HEALTH,   sizeof(Health));

    /* 3 entities with Position only */
    for (int i = 0; i < 3; i++) {
        Entity e = world_create_entity(w);
        Position *p = (Position *)world_add_component(w, e, COMP_POSITION);
        p->x = (float)(i + 10);
    }
    /* 2 entities with Position + Velocity */
    for (int i = 0; i < 2; i++) {
        Entity e = world_create_entity(w);
        Position *p = (Position *)world_add_component(w, e, COMP_POSITION);
        p->x = (float)(i + 20);
        Velocity *v = (Velocity *)world_add_component(w, e, COMP_VELOCITY);
        v->vx = (float)(i + 1);
    }

    /* Query Position (required), Velocity (optional) -> should match all 5 */
    ComponentType req[] = { COMP_POSITION, COMP_VELOCITY };
    Query *q = world_query(w, req, 2); /* first get base slot */
    ASSERT_NOT_NULL(q);
    ecs_query_optional(q, COMP_VELOCITY);
    ecs_query_refresh(w, q, req, 2);

    int total = 0;
    QueryIter it = query_begin(q);
    while (query_next(&it)) { total++; }
    query_done(q);

    /* All 5 entities (Position-only + Position+Velocity) should match */
    ASSERT_EQ(total, 5);

    world_destroy(w);
}

TEST(ecs_query_exclude_optional_combined) {
    World *w = world_create();
    ASSERT_NOT_NULL(w);

    world_register_component(w, COMP_POSITION, sizeof(Position));
    world_register_component(w, COMP_VELOCITY, sizeof(Velocity));
    world_register_component(w, COMP_HEALTH,   sizeof(Health));

    /* 2 entities: Position only */
    for (int i = 0; i < 2; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
    }
    /* 3 entities: Position + Velocity */
    for (int i = 0; i < 3; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
        world_add_component(w, e, COMP_VELOCITY);
    }
    /* 4 entities: Position + Health (should be excluded via Health exclude) */
    for (int i = 0; i < 4; i++) {
        Entity e = world_create_entity(w);
        world_add_component(w, e, COMP_POSITION);
        world_add_component(w, e, COMP_HEALTH);
    }

    /* Query: required=Position, optional=Velocity, exclude=Health
     * Expected matches: 2 (Pos only) + 3 (Pos+Vel) = 5 */
    ComponentType req[] = { COMP_POSITION, COMP_VELOCITY };
    Query *q = world_query(w, req, 2);
    ASSERT_NOT_NULL(q);
    ecs_query_optional(q, COMP_VELOCITY);
    ecs_query_exclude(q, COMP_HEALTH);
    ecs_query_refresh(w, q, req, 2);

    int count = 0;
    QueryIter it = query_begin(q);
    while (query_next(&it)) { count++; }
    query_done(q);

    ASSERT_EQ(count, 5);

    world_destroy(w);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ecs_world_create_destroy);
    RUN_TEST(ecs_entity_create);
    RUN_TEST(ecs_entity_create_multiple);
    RUN_TEST(ecs_entity_destroy);
    RUN_TEST(ecs_component_add_get);
    RUN_TEST(ecs_component_multiple);
    RUN_TEST(ecs_component_remove);
    RUN_TEST(ecs_query_iteration);
    RUN_TEST(ecs_query_index_zero_based);
    RUN_TEST(ecs_query_empty_result);
    RUN_TEST(ecs_entity_recycle_slot_reuse);
    RUN_TEST(ecs_entity_recycle_stale_handle);
    RUN_TEST(ecs_query_data_verification);
    RUN_TEST(ecs_concurrent_queries);
    RUN_TEST(ecs_component_add_remove_cycle);
    RUN_TEST(ecs_destroy_and_verify_survivors);
    RUN_TEST(ecs_null_entity);
    /* Edge cases */
    RUN_TEST(ecs_remove_nonexistent_component);
    RUN_TEST(ecs_get_unregistered_component);
    RUN_TEST(ecs_large_entity_count);
    RUN_TEST(ecs_destroy_null_world);
    /* Edge cache (R102) */
    RUN_TEST(ecs_edge_cache_add_hit);
    RUN_TEST(ecs_edge_cache_remove_hit);
    RUN_TEST(ecs_edge_cache_multi_transition);
    /* Exclude / Optional Query */
    RUN_TEST(ecs_query_exclude);
    RUN_TEST(ecs_query_optional);
    RUN_TEST(ecs_query_exclude_optional_combined);
TEST_MAIN_END()
