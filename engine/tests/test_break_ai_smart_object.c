#include "test_framework.h"
#include <ai/break_ai.h>

typedef struct SmartFixture {
    f32 heights[16];
    BreakNavMesh *mesh;
    BreakAiRuntime *ai;
} SmartFixture;

static bool smart_fixture_init(SmartFixture *fixture, u32 max_objects) {
    memset(fixture, 0, sizeof(*fixture));
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = fixture->heights;
    field.width = 4;
    field.depth = 4;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    fixture->mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    if (!fixture->mesh) {
        return false;
    }
    BreakAiRuntimeDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.max_agents = 2;
    desc.max_smart_objects = max_objects;
    fixture->ai = break_ai_runtime_create(fixture->mesh, &desc);
    if (!fixture->ai) {
        return false;
    }
    for (u32 i = 1; i <= 2; i++) {
        Entity entity;
        entity.index = i;
        entity.generation = 1;
        BreakAiAgentDesc agent;
        agent.position = vec3((f32)i, 0.0f, 1.0f);
        agent.velocity = vec3(0, 0, 0);
        agent.radius = 0.5f;
        agent.max_speed = 2.0f;
        if (break_ai_agent_add(fixture->ai, entity, &agent) != BREAK_NAV_OK) {
            return false;
        }
    }
    return true;
}

static void smart_fixture_destroy(SmartFixture *fixture) {
    break_ai_runtime_destroy(fixture->ai);
    break_nav_mesh_destroy(fixture->mesh);
}

static Entity smart_entity(u32 index) {
    Entity entity;
    entity.index = index;
    entity.generation = 1;
    return entity;
}

static void assert_owner(BreakAiRuntime *ai, BreakAiSmartObjectHandle object, Entity expected) {
    Entity owner;
    ASSERT_EQ(break_ai_smart_object_owner(ai, object, &owner), BREAK_NAV_OK);
    ASSERT_EQ(owner.index, expected.index);
    ASSERT_EQ(owner.generation, expected.generation);
}

TEST(smart_object_competition_release_and_stale_generation) {
    SmartFixture fixture;
    ASSERT_TRUE(smart_fixture_init(&fixture, 1));
    Entity a = smart_entity(1);
    Entity b = smart_entity(2);
    BreakAiSmartObjectHandle object;
    ASSERT_EQ(break_ai_smart_object_add(fixture.ai, vec3(2, 0, 2), &object), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_smart_object_reserve(fixture.ai, object, a), BREAK_NAV_OK);
    assert_owner(fixture.ai, object, a);
    ASSERT_EQ(break_ai_smart_object_reserve(fixture.ai, object, a), BREAK_NAV_OK);
    assert_owner(fixture.ai, object, a);
    ASSERT_EQ(break_ai_smart_object_reserve(fixture.ai, object, b), BREAK_NAV_REJECTED);
    assert_owner(fixture.ai, object, a);
    ASSERT_EQ(break_ai_smart_object_release(fixture.ai, object, b), BREAK_NAV_REJECTED);
    assert_owner(fixture.ai, object, a);
    ASSERT_EQ(break_ai_smart_object_remove(fixture.ai, object), BREAK_NAV_REJECTED);
    ASSERT_EQ(break_ai_agent_remove(fixture.ai, a), BREAK_NAV_REJECTED);
    assert_owner(fixture.ai, object, a);

    ASSERT_EQ(break_ai_smart_object_release(fixture.ai, object, a), BREAK_NAV_OK);
    assert_owner(fixture.ai, object, ENTITY_NULL);
    ASSERT_EQ(break_ai_smart_object_reserve(fixture.ai, object, b), BREAK_NAV_OK);
    assert_owner(fixture.ai, object, b);
    ASSERT_EQ(break_ai_smart_object_release(fixture.ai, object, b), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_smart_object_remove(fixture.ai, object), BREAK_NAV_OK);
    Entity output = a;
    Entity before = output;
    ASSERT_EQ(break_ai_smart_object_owner(fixture.ai, object, &output), BREAK_NAV_STALE);
    ASSERT_EQ(output.index, before.index);
    ASSERT_EQ(output.generation, before.generation);

    BreakAiSmartObjectHandle replacement;
    ASSERT_EQ(break_ai_smart_object_add(fixture.ai, vec3(3, 0, 3), &replacement), BREAK_NAV_OK);
    ASSERT_EQ(replacement.index, object.index);
    ASSERT_NEQ(replacement.generation, object.generation);
    ASSERT_EQ(break_ai_smart_object_reserve(fixture.ai, object, a), BREAK_NAV_STALE);
    assert_owner(fixture.ai, replacement, ENTITY_NULL);
    smart_fixture_destroy(&fixture);
}

TEST(smart_object_capacity_and_invalid_add_do_not_consume_slots) {
    SmartFixture fixture;
    ASSERT_TRUE(smart_fixture_init(&fixture, 1));
    BreakAiSmartObjectHandle output;
    memset(&output, 0x71, sizeof(output));
    BreakAiSmartObjectHandle before = output;
    ASSERT_EQ(break_ai_smart_object_add(fixture.ai, vec3(NAN, 0, 0), &output), BREAK_NAV_INVALID);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    BreakAiSmartObjectHandle first;
    ASSERT_EQ(break_ai_smart_object_add(fixture.ai, vec3(1, 0, 1), &first), BREAK_NAV_OK);
    ASSERT_EQ(first.index, 0u);
    ASSERT_EQ(break_ai_smart_object_add(fixture.ai, vec3(2, 0, 2), &output), BREAK_NAV_OVERLOAD);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    Entity stale = smart_entity(2);
    stale.generation = 2;
    ASSERT_EQ(break_ai_smart_object_reserve(fixture.ai, first, stale), BREAK_NAV_STALE);
    assert_owner(fixture.ai, first, ENTITY_NULL);
    ASSERT_EQ(break_ai_smart_object_reserve(fixture.ai, first, smart_entity(1)), BREAK_NAV_OK);
    assert_owner(fixture.ai, first, smart_entity(1));
    smart_fixture_destroy(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(smart_object_competition_release_and_stale_generation);
    RUN_TEST(smart_object_capacity_and_invalid_add_do_not_consume_slots);
TEST_MAIN_END()
