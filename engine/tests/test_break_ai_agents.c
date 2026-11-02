#include "test_framework.h"
#include <ai/break_ai.h>

typedef struct AgentFixture {
    f32 heights[16];
    BreakNavMesh *mesh;
    BreakAiRuntime *ai;
} AgentFixture;

static bool agent_fixture_init(AgentFixture *fixture, u32 max_agents) {
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
    fixture->ai = break_ai_runtime_create(fixture->mesh, &desc);
    return fixture->ai != NULL;
}

static void agent_fixture_destroy(AgentFixture *fixture) {
    break_ai_runtime_destroy(fixture->ai);
    break_nav_mesh_destroy(fixture->mesh);
}

static BreakAiAgentDesc agent_desc(f32 x, f32 z, f32 vx) {
    BreakAiAgentDesc desc;
    desc.position = vec3(x, 0.0f, z);
    desc.velocity = vec3(vx, 0.0f, 0.0f);
    desc.radius = 0.5f;
    desc.max_speed = 2.0f;
    return desc;
}

static Entity agent_entity(u32 index) {
    Entity entity;
    entity.index = index;
    entity.generation = 1;
    return entity;
}

TEST(agent_capacity_duplicate_and_stale_failures_are_atomic) {
    AgentFixture fixture;
    ASSERT_TRUE(agent_fixture_init(&fixture, 1));
    Entity first = agent_entity(1);
    Entity second = agent_entity(2);
    BreakAiAgentDesc desc = agent_desc(1.0f, 1.0f, 1.0f);
    ASSERT_EQ(break_ai_agent_add(fixture.ai, first, &desc), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_agent_add(fixture.ai, first, &desc), BREAK_NAV_REJECTED);
    ASSERT_EQ(break_ai_agent_add(fixture.ai, second, &desc), BREAK_NAV_OVERLOAD);
    desc.position = vec3(2.0f, 0.0f, 2.0f);
    ASSERT_EQ(break_ai_agent_update(fixture.ai, first, &desc), BREAK_NAV_OK);
    Entity stale = first;
    stale.generation = 2;
    ASSERT_EQ(break_ai_agent_update(fixture.ai, stale, &desc), BREAK_NAV_STALE);
    Vec3 output;
    ASSERT_EQ(break_ai_agent_avoid(fixture.ai, first, vec3(4, 0, 0), 1.0f, &output), BREAK_NAV_OK);
    ASSERT_TRUE(sqrtf(output.e[0] * output.e[0] + output.e[2] * output.e[2]) <= 2.0f + 1.0e-5f);
    ASSERT_EQ(break_ai_agent_remove(fixture.ai, stale), BREAK_NAV_STALE);
    ASSERT_EQ(break_ai_agent_remove(fixture.ai, first), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_agent_remove(fixture.ai, first), BREAK_NAV_STALE);
    ASSERT_EQ(break_ai_agent_add(fixture.ai, second, &desc), BREAK_NAV_OK);
    agent_fixture_destroy(&fixture);
}

TEST(agent_neighbor_selection_is_independent_of_registration_order) {
    AgentFixture forward;
    AgentFixture reverse;
    ASSERT_TRUE(agent_fixture_init(&forward, 18));
    ASSERT_TRUE(agent_fixture_init(&reverse, 18));
    Entity self = agent_entity(100);
    BreakAiAgentDesc self_desc = agent_desc(0.0f, 0.0f, 2.0f);
    ASSERT_EQ(break_ai_agent_add(forward.ai, self, &self_desc), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_agent_add(reverse.ai, self, &self_desc), BREAK_NAV_OK);
    for (u32 i = 0; i < 17; i++) {
        BreakAiAgentDesc desc = agent_desc((f32)i + 2.0f, 0.0f, -1.0f);
        ASSERT_EQ(break_ai_agent_add(forward.ai, agent_entity(i + 1), &desc), BREAK_NAV_OK);
    }
    for (u32 i = 17; i-- > 0;) {
        BreakAiAgentDesc desc = agent_desc((f32)i + 2.0f, 0.0f, -1.0f);
        ASSERT_EQ(break_ai_agent_add(reverse.ai, agent_entity(i + 1), &desc), BREAK_NAV_OK);
    }
    Vec3 a;
    Vec3 b;
    ASSERT_EQ(break_ai_agent_avoid(forward.ai, self, vec3(2, 0, 0), 1.0f, &a), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_agent_avoid(reverse.ai, self, vec3(2, 0, 0), 1.0f, &b), BREAK_NAV_OK);
    ASSERT_EQ(memcmp(&a, &b, sizeof(a)), 0);
    agent_fixture_destroy(&forward);
    agent_fixture_destroy(&reverse);
}

TEST_MAIN_BEGIN()
    RUN_TEST(agent_capacity_duplicate_and_stale_failures_are_atomic);
    RUN_TEST(agent_neighbor_selection_is_independent_of_registration_order);
TEST_MAIN_END()
