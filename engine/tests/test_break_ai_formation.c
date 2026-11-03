#include "test_framework.h"
#include <ai/break_ai.h>
#include <float.h>

typedef struct FormationFixture {
    f32 heights[16];
    BreakNavMesh *mesh;
    BreakAiRuntime *ai;
} FormationFixture;

static bool formation_fixture_init(FormationFixture *fixture, u32 max_agents, u32 max_formations) {
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
    desc.max_agents = max_agents;
    desc.max_formations = max_formations;
    fixture->ai = break_ai_runtime_create(fixture->mesh, &desc);
    return fixture->ai != NULL;
}

static void formation_fixture_destroy(FormationFixture *fixture) {
    break_ai_runtime_destroy(fixture->ai);
    break_nav_mesh_destroy(fixture->mesh);
}

static Entity formation_entity(u32 index) {
    Entity entity;
    entity.index = index;
    entity.generation = 1;
    return entity;
}

static BreakAiAgentDesc formation_agent(Vec3 position, Vec3 velocity) {
    BreakAiAgentDesc desc;
    desc.position = position;
    desc.velocity = velocity;
    desc.radius = 0.5f;
    desc.max_speed = 2.0f;
    return desc;
}

static void add_three_agents(FormationFixture *fixture) {
    BreakAiAgentDesc desc = formation_agent(vec3(5, 0, 5), vec3(1, 0, 0));
    break_ai_agent_add(fixture->ai, formation_entity(1), &desc);
    desc = formation_agent(vec3(5, 0, 5), vec3(0, 0, 0));
    break_ai_agent_add(fixture->ai, formation_entity(2), &desc);
    break_ai_agent_add(fixture->ai, formation_entity(3), &desc);
}

static BreakAiFormationHandle create_three(FormationFixture *fixture) {
    Entity members[3];
    members[0] = formation_entity(1);
    members[1] = formation_entity(2);
    members[2] = formation_entity(3);
    BreakAiFormationHandle handle;
    BreakNavError status = break_ai_formation_create(fixture->ai, members, 3, 2.0f, &handle);
    if (status != BREAK_NAV_OK) {
        handle.index = UINT32_MAX;
        handle.generation = UINT32_MAX;
    }
    return handle;
}

TEST(formation_slots_are_stable_wedge_positions) {
    FormationFixture fixture;
    ASSERT_TRUE(formation_fixture_init(&fixture, 3, 1));
    add_three_agents(&fixture);
    BreakAiFormationHandle handle = create_three(&fixture);
    ASSERT_NEQ(handle.generation, UINT32_MAX);
    Vec3 slots[3];
    u32 count = 0;
    ASSERT_EQ(break_ai_formation_slots(fixture.ai, handle, vec3(5, 0, 5), vec3(1, 0, 0),
                                       slots, 3, &count), BREAK_NAV_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_FLOAT_EQ(slots[0].e[0], 5.0f, 1.0e-6);
    ASSERT_FLOAT_EQ(slots[0].e[2], 5.0f, 1.0e-6);
    ASSERT_FLOAT_EQ(slots[1].e[0], 3.0f, 1.0e-6);
    ASSERT_FLOAT_EQ(slots[1].e[2], 3.0f, 1.0e-6);
    ASSERT_FLOAT_EQ(slots[2].e[0], 3.0f, 1.0e-6);
    ASSERT_FLOAT_EQ(slots[2].e[2], 7.0f, 1.0e-6);
    Vec3 repeated[3];
    u32 repeated_count = 0;
    ASSERT_EQ(break_ai_formation_slots(fixture.ai, handle, vec3(5, 0, 5), vec3(0, 0, 0),
                                       repeated, 3, &repeated_count), BREAK_NAV_OK);
    ASSERT_EQ(memcmp(slots, repeated, sizeof(slots)), 0);
    ASSERT_EQ(repeated_count, count);

    Vec3 too_small[2];
    memset(too_small, 0x47, sizeof(too_small));
    Vec3 before[2];
    memcpy(before, too_small, sizeof(before));
    u32 sentinel_count = 99;
    ASSERT_EQ(break_ai_formation_slots(fixture.ai, handle, vec3(5, 0, 5), vec3(1, 0, 0),
                                       too_small, 2, &sentinel_count), BREAK_NAV_OVERLOAD);
    ASSERT_EQ(memcmp(too_small, before, sizeof(too_small)), 0);
    ASSERT_EQ(sentinel_count, 99u);
    formation_fixture_destroy(&fixture);
}

TEST(formation_tick_replays_and_followers_converge_within_speed_limit) {
    FormationFixture fixture;
    ASSERT_TRUE(formation_fixture_init(&fixture, 3, 1));
    add_three_agents(&fixture);
    BreakAiFormationHandle handle = create_three(&fixture);
    ASSERT_NEQ(handle.generation, UINT32_MAX);
    Vec3 first[3];
    Vec3 second[3];
    u32 first_count = 0;
    u32 second_count = 0;
    ASSERT_EQ(break_ai_formation_tick(fixture.ai, handle, 0.1f, first, 3, &first_count), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_formation_tick(fixture.ai, handle, 0.1f, second, 3, &second_count), BREAK_NAV_OK);
    ASSERT_EQ(first_count, 3u);
    ASSERT_EQ(second_count, 3u);
    ASSERT_EQ(memcmp(first, second, sizeof(first)), 0);
    ASSERT_FLOAT_EQ(first[0].e[0], 1.0f, 1.0e-6);
    for (u32 i = 1; i < 3; i++) {
        ASSERT_TRUE(sqrtf(first[i].e[0] * first[i].e[0] + first[i].e[2] * first[i].e[2]) <=
                    2.0f + 1.0e-5f);
    }

    Vec3 positions[3];
    positions[0] = vec3(5, 0, 5);
    positions[1] = vec3(5, 0, 5);
    positions[2] = vec3(5, 0, 5);
    for (u32 step = 0; step < 60; step++) {
        Vec3 velocities[3];
        u32 count = 0;
        ASSERT_EQ(break_ai_formation_tick(fixture.ai, handle, 0.1f, velocities, 3, &count), BREAK_NAV_OK);
        for (u32 i = 1; i < 3; i++) {
            positions[i].e[0] += velocities[i].e[0] * 0.1f;
            positions[i].e[2] += velocities[i].e[2] * 0.1f;
            BreakAiAgentDesc desc = formation_agent(positions[i], velocities[i]);
            ASSERT_EQ(break_ai_agent_update(fixture.ai, formation_entity(i + 1), &desc), BREAK_NAV_OK);
        }
    }
    Vec3 slots[3];
    u32 count = 0;
    ASSERT_EQ(break_ai_formation_slots(fixture.ai, handle, positions[0], vec3(1, 0, 0),
                                       slots, 3, &count), BREAK_NAV_OK);
    for (u32 i = 1; i < 3; i++) {
        f32 dx = positions[i].e[0] - slots[i].e[0];
        f32 dz = positions[i].e[2] - slots[i].e[2];
        ASSERT_TRUE(sqrtf(dx * dx + dz * dz) <= 0.06f);
    }
    formation_fixture_destroy(&fixture);
}

TEST(formation_validation_capacity_and_lifecycle_are_atomic) {
    FormationFixture fixture;
    ASSERT_TRUE(formation_fixture_init(&fixture, 4, 1));
    add_three_agents(&fixture);
    BreakAiAgentDesc desc = formation_agent(vec3(6, 0, 5), vec3(0, 0, 0));
    ASSERT_EQ(break_ai_agent_add(fixture.ai, formation_entity(4), &desc), BREAK_NAV_OK);
    Entity duplicate[2];
    duplicate[0] = formation_entity(1);
    duplicate[1] = formation_entity(1);
    BreakAiFormationHandle output;
    memset(&output, 0x38, sizeof(output));
    BreakAiFormationHandle before = output;
    ASSERT_EQ(break_ai_formation_create(fixture.ai, duplicate, 2, 2.0f, &output), BREAK_NAV_INVALID);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    Entity unknown[2];
    unknown[0] = formation_entity(1);
    unknown[1] = formation_entity(9);
    ASSERT_EQ(break_ai_formation_create(fixture.ai, unknown, 2, 2.0f, &output), BREAK_NAV_STALE);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);

    BreakAiFormationHandle first = create_three(&fixture);
    ASSERT_NEQ(first.generation, UINT32_MAX);
    Entity other[1] = {formation_entity(4)};
    ASSERT_EQ(break_ai_formation_create(fixture.ai, other, 1, 2.0f, &output), BREAK_NAV_OVERLOAD);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    ASSERT_EQ(break_ai_agent_remove(fixture.ai, formation_entity(2)), BREAK_NAV_REJECTED);
    ASSERT_EQ(break_ai_formation_destroy(fixture.ai, first), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_formation_destroy(fixture.ai, first), BREAK_NAV_STALE);
    Vec3 slots[3];
    u32 count = 0;
    ASSERT_EQ(break_ai_formation_slots(fixture.ai, first, vec3(5, 0, 5), vec3(1, 0, 0),
                                       slots, 3, &count), BREAK_NAV_STALE);
    ASSERT_EQ(break_ai_agent_remove(fixture.ai, formation_entity(2)), BREAK_NAV_OK);
    formation_fixture_destroy(&fixture);
}

TEST(formation_slots_normalize_extreme_finite_forward) {
    FormationFixture fixture;
    ASSERT_TRUE(formation_fixture_init(&fixture, 3, 1));
    add_three_agents(&fixture);
    BreakAiFormationHandle handle = create_three(&fixture);
    ASSERT_NEQ(handle.generation, UINT32_MAX);
    Vec3 slots[3];
    u32 count = 0;
    ASSERT_EQ(break_ai_formation_slots(fixture.ai, handle, vec3(0, 0, 0),
                                       vec3(FLT_MAX, 0, 0), slots, 3, &count), BREAK_NAV_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_FLOAT_EQ(slots[1].e[0], -2.0f, 1.0e-6);
    ASSERT_FLOAT_EQ(slots[1].e[2], -2.0f, 1.0e-6);
    ASSERT_FLOAT_EQ(slots[2].e[0], -2.0f, 1.0e-6);
    ASSERT_FLOAT_EQ(slots[2].e[2], 2.0f, 1.0e-6);
    formation_fixture_destroy(&fixture);
}

TEST(formation_rejects_33_members_without_consuming_a_slot) {
    FormationFixture fixture;
    ASSERT_TRUE(formation_fixture_init(&fixture, 33, 1));
    Entity members[33];
    for (u32 i = 0; i < 33; i++) {
        members[i] = formation_entity(i + 1);
        BreakAiAgentDesc desc = formation_agent(vec3((f32)i, 0, 0), vec3(0, 0, 0));
        ASSERT_EQ(break_ai_agent_add(fixture.ai, members[i], &desc), BREAK_NAV_OK);
    }
    BreakAiFormationHandle output;
    memset(&output, 0x64, sizeof(output));
    BreakAiFormationHandle before = output;
    ASSERT_EQ(break_ai_formation_create(fixture.ai, members, 33, 2.0f, &output),
              BREAK_NAV_OVERLOAD);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    ASSERT_EQ(break_ai_formation_create(fixture.ai, members, 1, 2.0f, &output), BREAK_NAV_OK);
    ASSERT_EQ(output.index, 0u);
    ASSERT_EQ(output.generation, 1u);
    formation_fixture_destroy(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(formation_slots_are_stable_wedge_positions);
    RUN_TEST(formation_tick_replays_and_followers_converge_within_speed_limit);
    RUN_TEST(formation_validation_capacity_and_lifecycle_are_atomic);
    RUN_TEST(formation_slots_normalize_extreme_finite_forward);
    RUN_TEST(formation_rejects_33_members_without_consuming_a_slot);
TEST_MAIN_END()
