#include "test_framework.h"
#include <core/platform_thread.h>
#include <game/break_flow.h>
#include <string.h>

typedef struct {
    World *world;
    BreakGame *game;
    BreakFlowGraph *graph;
    Entity actor;
} Fixture;

static bool fixture_make(Fixture *f) {
    memset(f, 0, sizeof(*f));
    f->world = world_create();
    if (!f->world) return false;
    world_register_component(f->world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    BreakGameConfig game_cfg = {0u, 2u};
    f->game = break_game_create(f->world, &game_cfg);
    if (!f->game) return false;
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc cls = {"pawn", comps, 1u, NULL};
    u32 class_id = 0u;
    BreakGameSpawn spawn;
    spawn.position = vec3(1.0f, 2.0f, 3.0f);
    if (break_game_register_class(f->game, &cls, &class_id) != BREAK_GAME_OK) return false;
    spawn.class_id = class_id;
    if (break_game_spawn(f->game, &spawn, &f->actor) != BREAK_GAME_OK) return false;
    BreakGameItemDesc item = {3u, 10u};
    if (break_game_item_define(f->game, &item) != BREAK_GAME_OK) return false;
    f->graph = break_flow_graph_create(NULL);
    return f->graph != NULL;
}

static void fixture_destroy(Fixture *f) {
    break_flow_graph_destroy(f->graph);
    break_game_destroy(f->game);
    world_destroy(f->world);
}

static BreakFlowNodeDesc node(BreakFlowNodeType type) {
    BreakFlowNodeDesc d;
    memset(&d, 0, sizeof(d));
    d.type = type;
    d.event_key = type == BREAK_FLOW_NODE_EVENT ? 5u : 0u;
    d.delay_ticks = type == BREAK_FLOW_NODE_DELAY ? 2u : 0u;
    return d;
}

static u32 add(Fixture *f, BreakFlowNodeDesc d) {
    u32 id = 0u;
    if (break_flow_node_add(f->graph, &d, &id) != BREAK_FLOW_OK) return 0u;
    return id;
}

static bool edge(Fixture *f, BreakFlowPortKind kind, u32 sn, u32 sp,
                 u32 tn, u32 tp) {
    BreakFlowLinkDesc d = {kind, sn, sp, tn, tp};
    u32 id = 0u;
    return break_flow_link_add(f->graph, &d, &id) == BREAK_FLOW_OK;
}

static Vec3 position(const Fixture *f) {
    const Vec3 *p = (const Vec3 *)world_get_component(
        f->world, f->actor, BREAK_GAME_POSITION_COMPONENT);
    return p ? *p : vec3(-999.0f, -999.0f, -999.0f);
}

static bool build_math_action_graph(Fixture *f) {
    BreakFlowNodeDesc d = node(BREAK_FLOW_NODE_EVENT);
    u32 event = add(f, d);
    d = node(BREAK_FLOW_NODE_MATH_MULTIPLY);
    d.b = 4.0f;
    u32 math = add(f, d);
    u32 sequence = add(f, node(BREAK_FLOW_NODE_SEQUENCE));
    d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    d.entity = f->actor;
    d.b = 4.0f;
    d.c = 5.0f;
    u32 set = add(f, d);
    d = node(BREAK_FLOW_NODE_ENTITY_ADD_ITEM);
    d.entity = f->actor;
    d.item_id = 3u;
    u32 add_item = add(f, d);
    return event && math && sequence && set && add_item &&
        edge(f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
             sequence, BREAK_FLOW_EXEC_IN) &&
        edge(f, BREAK_FLOW_PORT_EXEC, sequence, BREAK_FLOW_SEQUENCE_OUT_0,
             set, BREAK_FLOW_EXEC_IN) &&
        edge(f, BREAK_FLOW_PORT_EXEC, sequence, BREAK_FLOW_SEQUENCE_OUT_1,
             add_item, BREAK_FLOW_EXEC_IN) &&
        edge(f, BREAK_FLOW_PORT_VALUE, event, BREAK_FLOW_EVENT_VALUE_OUT,
             math, BREAK_FLOW_MATH_INPUT_A) &&
        edge(f, BREAK_FLOW_PORT_VALUE, math, BREAK_FLOW_MATH_VALUE_OUT,
             set, BREAK_FLOW_ACTION_INPUT_X) &&
        edge(f, BREAK_FLOW_PORT_VALUE, math, BREAK_FLOW_MATH_VALUE_OUT,
             add_item, BREAK_FLOW_ACTION_INPUT_COUNT);
}

TEST(event_math_and_sequence_drive_real_entity_actions) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    ASSERT_TRUE(build_math_action_graph(&f));
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 2.5f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    Vec3 p = position(&f);
    ASSERT_FLOAT_EQ(p.e[0], 10.0f, 0.0f);
    ASSERT_FLOAT_EQ(p.e[1], 4.0f, 0.0f);
    ASSERT_FLOAT_EQ(p.e[2], 5.0f, 0.0f);
    u32 count = 0u;
    ASSERT_EQ(break_game_inventory_count(f.game, f.actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 10u);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 0u);
    ASSERT_EQ(break_flow_runtime_now_tick(runtime), 1u);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST(all_arithmetic_nodes_produce_hand_computed_results) {
    const f32 expected[4] = {6.5f, -1.5f, 10.0f, 0.625f};
    for (u32 i = 0u; i < 4u; i++) {
        Fixture f;
        ASSERT_TRUE(fixture_make(&f));
        u32 event = add(&f, node(BREAK_FLOW_NODE_EVENT));
        BreakFlowNodeDesc d = node((BreakFlowNodeType)(BREAK_FLOW_NODE_MATH_ADD + i));
        d.b = 4.0f;
        u32 math = add(&f, d);
        d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
        d.entity = f.actor;
        u32 set = add(&f, d);
        ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
                         set, BREAK_FLOW_EXEC_IN));
        ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, event, BREAK_FLOW_EVENT_VALUE_OUT,
                         math, BREAK_FLOW_MATH_INPUT_A));
        ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, math, BREAK_FLOW_MATH_VALUE_OUT,
                         set, BREAK_FLOW_ACTION_INPUT_X));
        BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
        ASSERT_NOT_NULL(runtime);
        ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 2.5f), BREAK_FLOW_OK);
        ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
        ASSERT_FLOAT_EQ(position(&f).e[0], expected[i], 0.000001f);
        break_flow_runtime_destroy(runtime);
        fixture_destroy(&f);
    }
}

TEST(comparison_and_branch_select_true_then_false) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    u32 event = add(&f, node(BREAK_FLOW_NODE_EVENT));
    BreakFlowNodeDesc d = node(BREAK_FLOW_NODE_COMPARE_LESS);
    d.b = 10.0f;
    u32 compare = add(&f, d);
    u32 branch = add(&f, node(BREAK_FLOW_NODE_BRANCH));
    d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    d.entity = f.actor;
    d.a = 7.0f;
    u32 yes = add(&f, d);
    d.a = 9.0f;
    u32 no = add(&f, d);
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
                     branch, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, event, BREAK_FLOW_EVENT_VALUE_OUT,
                     compare, BREAK_FLOW_MATH_INPUT_A));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, compare, BREAK_FLOW_MATH_VALUE_OUT,
                     branch, BREAK_FLOW_BRANCH_CONDITION));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, branch, BREAK_FLOW_BRANCH_TRUE_OUT,
                     yes, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, branch, BREAK_FLOW_BRANCH_FALSE_OUT,
                     no, BREAK_FLOW_EXEC_IN));
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 5.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    ASSERT_FLOAT_EQ(position(&f).e[0], 7.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_reset(runtime), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 15.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    ASSERT_FLOAT_EQ(position(&f).e[0], 9.0f, 0.0f);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST(equal_and_greater_comparisons_cover_true_and_false_branches) {
    const struct {
        BreakFlowNodeType type;
        f32 value;
        f32 expected;
    } cases[4] = {
        {BREAK_FLOW_NODE_COMPARE_EQUAL, 5.0f, 7.0f},
        {BREAK_FLOW_NODE_COMPARE_EQUAL, 6.0f, 9.0f},
        {BREAK_FLOW_NODE_COMPARE_GREATER, 6.0f, 7.0f},
        {BREAK_FLOW_NODE_COMPARE_GREATER, 5.0f, 9.0f}
    };
    for (u32 i = 0u; i < 4u; i++) {
        Fixture f;
        ASSERT_TRUE(fixture_make(&f));
        u32 event = add(&f, node(BREAK_FLOW_NODE_EVENT));
        BreakFlowNodeDesc d = node(cases[i].type);
        d.b = 5.0f;
        u32 compare = add(&f, d);
        u32 branch = add(&f, node(BREAK_FLOW_NODE_BRANCH));
        d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
        d.entity = f.actor;
        d.a = 7.0f;
        u32 yes = add(&f, d);
        d.a = 9.0f;
        u32 no = add(&f, d);
        ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
                         branch, BREAK_FLOW_EXEC_IN));
        ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, event, BREAK_FLOW_EVENT_VALUE_OUT,
                         compare, BREAK_FLOW_MATH_INPUT_A));
        ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, compare, BREAK_FLOW_MATH_VALUE_OUT,
                         branch, BREAK_FLOW_BRANCH_CONDITION));
        ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, branch, BREAK_FLOW_BRANCH_TRUE_OUT,
                         yes, BREAK_FLOW_EXEC_IN));
        ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, branch, BREAK_FLOW_BRANCH_FALSE_OUT,
                         no, BREAK_FLOW_EXEC_IN));
        BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
        ASSERT_NOT_NULL(runtime);
        ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, cases[i].value), BREAK_FLOW_OK);
        ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
        ASSERT_FLOAT_EQ(position(&f).e[0], cases[i].expected, 0.0f);
        break_flow_runtime_destroy(runtime);
        fixture_destroy(&f);
    }
}

TEST(delay_waits_two_ticks_and_event_queue_is_bounded) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    u32 event = add(&f, node(BREAK_FLOW_NODE_EVENT));
    u32 delay = add(&f, node(BREAK_FLOW_NODE_DELAY));
    BreakFlowNodeDesc d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    d.entity = f.actor;
    d.a = 7.0f; d.b = 8.0f; d.c = 9.0f;
    u32 set = add(&f, d);
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
                     delay, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, delay, BREAK_FLOW_DELAY_EXEC_OUT,
                     set, BREAK_FLOW_EXEC_IN));
    BreakFlowRuntimeConfig cfg = {1u, 4u, 32u};
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, &cfg);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 0.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 0.0f), BREAK_FLOW_OVERLOAD);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    ASSERT_FLOAT_EQ(position(&f).e[0], 1.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 1u);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    ASSERT_FLOAT_EQ(position(&f).e[0], 1.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    Vec3 p = position(&f);
    ASSERT_FLOAT_EQ(p.e[0], 7.0f, 0.0f);
    ASSERT_FLOAT_EQ(p.e[1], 8.0f, 0.0f);
    ASSERT_FLOAT_EQ(p.e[2], 9.0f, 0.0f);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST(node_budget_resumes_across_frames_without_partial_node_actions) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    ASSERT_TRUE(build_math_action_graph(&f));
    BreakFlowRuntimeConfig cfg = {16u, 8u, 2u};
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, &cfg);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 1.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_TIMEOUT);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 2u);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_TIMEOUT);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 1u);
    ASSERT_FLOAT_EQ(position(&f).e[0], 4.0f, 0.0f);
    u32 count = 99u;
    ASSERT_EQ(break_game_inventory_count(f.game, f.actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    ASSERT_EQ(break_game_inventory_count(f.game, f.actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 4u);
    ASSERT_EQ(break_flow_runtime_now_tick(runtime), 3u);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST(action_failure_restores_world_queue_tick_and_graph_edit_requires_reset) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    u32 event = add(&f, node(BREAK_FLOW_NODE_EVENT));
    u32 sequence = add(&f, node(BREAK_FLOW_NODE_SEQUENCE));
    BreakFlowNodeDesc d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    d.entity = f.actor;
    d.a = 8.0f;
    u32 set = add(&f, d);
    d = node(BREAK_FLOW_NODE_ENTITY_ADD_ITEM);
    d.entity = f.actor;
    d.item_id = 3u;
    d.a = 11.0f;
    u32 add_item = add(&f, d);
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
                     sequence, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, sequence, BREAK_FLOW_SEQUENCE_OUT_0,
                     set, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, sequence, BREAK_FLOW_SEQUENCE_OUT_1,
                     add_item, BREAK_FLOW_EXEC_IN));
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 0.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OVERLOAD);
    ASSERT_FLOAT_EQ(position(&f).e[0], 1.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 1u);
    ASSERT_EQ(break_flow_runtime_now_tick(runtime), 0u);
    ASSERT_TRUE(add(&f, node(BREAK_FLOW_NODE_SEQUENCE)) != 0u);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_REJECTED);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 1u);
    ASSERT_EQ(break_flow_runtime_reset(runtime), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 0u);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST(divide_by_zero_is_atomic_and_returns_failure) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    u32 event = add(&f, node(BREAK_FLOW_NODE_EVENT));
    BreakFlowNodeDesc d = node(BREAK_FLOW_NODE_MATH_DIVIDE);
    d.b = 0.0f;
    u32 math = add(&f, d);
    d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    d.entity = f.actor;
    d.a = 9.0f;
    u32 set = add(&f, d);
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
                     set, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, math, BREAK_FLOW_MATH_VALUE_OUT,
                     set, BREAK_FLOW_ACTION_INPUT_X));
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 2.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_FAILED);
    ASSERT_FLOAT_EQ(position(&f).e[0], 1.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 1u);
    ASSERT_EQ(break_flow_runtime_now_tick(runtime), 0u);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST(delay_continuations_preserve_fifo_with_following_events) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    u32 event = add(&f, node(BREAK_FLOW_NODE_EVENT));
    BreakFlowNodeDesc d = node(BREAK_FLOW_NODE_DELAY);
    d.delay_ticks = 1u;
    u32 delay = add(&f, d);
    d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    d.entity = f.actor;
    u32 set = add(&f, d);
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
                     delay, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, delay, BREAK_FLOW_DELAY_EXEC_OUT,
                     set, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, event, BREAK_FLOW_EVENT_VALUE_OUT,
                     set, BREAK_FLOW_ACTION_INPUT_X));
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 1.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 2.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_next_sequence(runtime), 3u);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    /* EXEC targets take 3/4; the two delay continuations take 5/6. */
    ASSERT_EQ(break_flow_runtime_next_sequence(runtime), 7u);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 3.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_next_sequence(runtime), 8u);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    ASSERT_FLOAT_EQ(position(&f).e[0], 2.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 1u);
    u64 after_second = break_flow_runtime_next_sequence(runtime);
    ASSERT_TRUE(after_second > 8u);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    ASSERT_FLOAT_EQ(position(&f).e[0], 3.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 0u);
    ASSERT_EQ(break_flow_runtime_now_tick(runtime), 3u);
    ASSERT_TRUE(break_flow_runtime_next_sequence(runtime) > after_second);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST(failed_sequence_restores_sequence_and_retry_has_no_duplicates_or_loss) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    u32 event = add(&f, node(BREAK_FLOW_NODE_EVENT));
    u32 sequence = add(&f, node(BREAK_FLOW_NODE_SEQUENCE));
    BreakFlowNodeDesc d = node(BREAK_FLOW_NODE_ENTITY_ADD_ITEM);
    d.entity = f.actor;
    d.item_id = 3u;
    d.a = 1.0f;
    u32 add_item = add(&f, d);
    d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    d.entity = f.actor;
    u32 set = add(&f, d);
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_EXEC_OUT,
                     sequence, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, sequence, BREAK_FLOW_SEQUENCE_OUT_0,
                     add_item, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, sequence, BREAK_FLOW_SEQUENCE_OUT_1,
                     set, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, event, BREAK_FLOW_EVENT_VALUE_OUT,
                     set, BREAK_FLOW_ACTION_INPUT_X));
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_game_inventory_add(f.game, f.actor, 3u, 10u), BREAK_GAME_OK);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 1.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 2.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OVERLOAD);
    u32 count = 0u;
    ASSERT_EQ(break_game_inventory_count(f.game, f.actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 10u);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 2u);
    ASSERT_EQ(break_flow_runtime_now_tick(runtime), 0u);
    ASSERT_EQ(break_flow_runtime_next_sequence(runtime), 3u);

    BreakGameSpawn spawn = {1u, {{0.0f, 0.0f, 0.0f}}};
    Entity other = ENTITY_NULL;
    ASSERT_EQ(break_game_spawn(f.game, &spawn, &other), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_transfer(f.game, f.actor, other, 3u, 5u), BREAK_GAME_OK);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 3.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_next_sequence(runtime), 4u);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    ASSERT_EQ(break_game_inventory_count(f.game, f.actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 8u);
    ASSERT_FLOAT_EQ(position(&f).e[0], 3.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 0u);
    ASSERT_EQ(break_flow_runtime_now_tick(runtime), 1u);
    ASSERT_EQ(break_flow_runtime_next_sequence(runtime), 13u);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST(invalid_event_value_source_rolls_back_entire_tick) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    u32 event_a = add(&f, node(BREAK_FLOW_NODE_EVENT));
    BreakFlowNodeDesc d = node(BREAK_FLOW_NODE_EVENT);
    d.event_key = 7u;
    u32 event_b = add(&f, d);
    u32 sequence = add(&f, node(BREAK_FLOW_NODE_SEQUENCE));
    d = node(BREAK_FLOW_NODE_ENTITY_ADD_ITEM);
    d.entity = f.actor;
    d.item_id = 3u;
    d.a = 1.0f;
    u32 add_item = add(&f, d);
    d = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    d.entity = f.actor;
    u32 set = add(&f, d);
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, event_a, BREAK_FLOW_EVENT_EXEC_OUT,
                     sequence, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, sequence, BREAK_FLOW_SEQUENCE_OUT_0,
                     add_item, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_EXEC, sequence, BREAK_FLOW_SEQUENCE_OUT_1,
                     set, BREAK_FLOW_EXEC_IN));
    ASSERT_TRUE(edge(&f, BREAK_FLOW_PORT_VALUE, event_b, BREAK_FLOW_EVENT_VALUE_OUT,
                     set, BREAK_FLOW_ACTION_INPUT_X));
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, f.actor, 8.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_FAILED);
    u32 count = 99u;
    ASSERT_EQ(break_game_inventory_count(f.game, f.actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_FLOAT_EQ(position(&f).e[0], 1.0f, 0.0f);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 1u);
    ASSERT_EQ(break_flow_runtime_now_tick(runtime), 0u);
    ASSERT_EQ(break_flow_runtime_next_sequence(runtime), 2u);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

typedef struct {
    BreakFlowRuntime *runtime;
    Entity actor;
    BreakFlowError post;
    BreakFlowError tick;
    BreakFlowError reset;
} ThreadProbe;

static PLATFORM_THREAD_RET call_off_thread(PLATFORM_THREAD_ARG arg) {
    ThreadProbe *probe = (ThreadProbe *)arg;
    probe->post = break_flow_runtime_post(probe->runtime, 5u, probe->actor, 1.0f);
    probe->tick = break_flow_runtime_tick(probe->runtime);
    probe->reset = break_flow_runtime_reset(probe->runtime);
    return PLATFORM_THREAD_RETURN;
}

TEST(non_owner_thread_cannot_mutate_runtime) {
    Fixture f;
    ASSERT_TRUE(fixture_make(&f));
    ASSERT_TRUE(add(&f, node(BREAK_FLOW_NODE_EVENT)) != 0u);
    BreakFlowRuntime *runtime = break_flow_runtime_create(f.graph, f.game, NULL);
    ASSERT_NOT_NULL(runtime);
    ThreadProbe probe;
    memset(&probe, 0, sizeof(probe));
    probe.runtime = runtime;
    probe.actor = f.actor;
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, call_off_thread, &probe));
    platform_thread_join(thread);
    ASSERT_EQ(probe.post, BREAK_FLOW_REJECTED);
    ASSERT_EQ(probe.tick, BREAK_FLOW_REJECTED);
    ASSERT_EQ(probe.reset, BREAK_FLOW_REJECTED);
    ASSERT_EQ(break_flow_runtime_pending_count(runtime), 0u);
    break_flow_runtime_destroy(runtime);
    fixture_destroy(&f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(event_math_and_sequence_drive_real_entity_actions);
    RUN_TEST(all_arithmetic_nodes_produce_hand_computed_results);
    RUN_TEST(comparison_and_branch_select_true_then_false);
    RUN_TEST(equal_and_greater_comparisons_cover_true_and_false_branches);
    RUN_TEST(delay_waits_two_ticks_and_event_queue_is_bounded);
    RUN_TEST(node_budget_resumes_across_frames_without_partial_node_actions);
    RUN_TEST(action_failure_restores_world_queue_tick_and_graph_edit_requires_reset);
    RUN_TEST(divide_by_zero_is_atomic_and_returns_failure);
    RUN_TEST(delay_continuations_preserve_fifo_with_following_events);
    RUN_TEST(failed_sequence_restores_sequence_and_retry_has_no_duplicates_or_loss);
    RUN_TEST(invalid_event_value_source_rolls_back_entire_tick);
    RUN_TEST(non_owner_thread_cannot_mutate_runtime);
TEST_MAIN_END()
