#include "test_framework.h"
#include <kernel/break_flow.h>
#include <stdint.h>
#include <string.h>

static BreakFlowNodeDesc node_desc(BreakFlowNodeType type) {
    BreakFlowNodeDesc d;
    memset(&d, 0, sizeof(d));
    d.type = type;
    if (type == BREAK_FLOW_NODE_EVENT) d.event_key = 1u;
    if (type == BREAK_FLOW_NODE_DELAY) d.delay_ticks = 1u;
    return d;
}

static u32 add_node(BreakFlowGraph *g, BreakFlowNodeType type) {
    BreakFlowNodeDesc d = node_desc(type);
    u32 id = 0;
    if (break_flow_node_add(g, &d, &id) != BREAK_FLOW_OK) return 0u;
    return id;
}

static BreakFlowLinkDesc link_desc(BreakFlowPortKind kind, u32 sn, u32 sp,
                                   u32 tn, u32 tp) {
    BreakFlowLinkDesc d;
    d.kind = kind;
    d.source_node = sn;
    d.source_port = sp;
    d.target_node = tn;
    d.target_port = tp;
    return d;
}

TEST(stable_ids_survive_delete_and_iteration_is_sorted) {
    BreakFlowConfig cfg = {3u, 4u};
    BreakFlowGraph *g = break_flow_graph_create(&cfg);
    ASSERT_NOT_NULL(g);
    u32 a = add_node(g, BREAK_FLOW_NODE_EVENT);
    u32 b = add_node(g, BREAK_FLOW_NODE_SEQUENCE);
    ASSERT_EQ(a, 1u);
    ASSERT_EQ(b, 2u);
    ASSERT_EQ(break_flow_node_remove(g, a), BREAK_FLOW_OK);
    u32 c = add_node(g, BREAK_FLOW_NODE_DELAY);
    ASSERT_EQ(c, 3u);
    ASSERT_EQ(break_flow_graph_node_count(g), 2u);
    u32 id = 0;
    BreakFlowNodeDesc out;
    ASSERT_EQ(break_flow_node_at(g, 0u, &id, &out), BREAK_FLOW_OK);
    ASSERT_EQ(id, b);
    ASSERT_EQ(out.type, BREAK_FLOW_NODE_SEQUENCE);
    ASSERT_EQ(break_flow_node_at(g, 1u, &id, &out), BREAK_FLOW_OK);
    ASSERT_EQ(id, c);
    ASSERT_EQ(break_flow_node_at(g, 2u, &id, &out), BREAK_FLOW_STALE);
    ASSERT_EQ(break_flow_node_remove(g, b), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_node_remove(g, c), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_node_add(g, &out, &id), BREAK_FLOW_OVERLOAD);
    break_flow_graph_destroy(g);
}

TEST(explicit_ports_reject_bad_direction_kind_and_duplicate_input) {
    BreakFlowGraph *g = break_flow_graph_create(NULL);
    ASSERT_NOT_NULL(g);
    u32 event = add_node(g, BREAK_FLOW_NODE_EVENT);
    u32 math = add_node(g, BREAK_FLOW_NODE_MATH_ADD);
    u32 action = add_node(g, BREAK_FLOW_NODE_BRANCH);
    BreakFlowLinkDesc d = link_desc(BREAK_FLOW_PORT_VALUE, event,
        BREAK_FLOW_EVENT_VALUE_OUT, math, BREAK_FLOW_MATH_INPUT_A);
    u32 link = 0;
    ASSERT_EQ(break_flow_link_add(g, &d, &link), BREAK_FLOW_OK);
    ASSERT_EQ(link, 1u);
    u64 revision = break_flow_graph_revision(g);
    d = link_desc(BREAK_FLOW_PORT_VALUE, math, BREAK_FLOW_MATH_VALUE_OUT,
                  math, BREAK_FLOW_MATH_INPUT_A);
    ASSERT_EQ(break_flow_link_add(g, &d, &link), BREAK_FLOW_REJECTED);
    d = link_desc(BREAK_FLOW_PORT_VALUE, event, BREAK_FLOW_EVENT_VALUE_OUT,
                  math, BREAK_FLOW_MATH_INPUT_A);
    ASSERT_EQ(break_flow_link_add(g, &d, &link), BREAK_FLOW_REJECTED);
    d = link_desc(BREAK_FLOW_PORT_EXEC, event, BREAK_FLOW_EVENT_VALUE_OUT,
                  action, BREAK_FLOW_EXEC_IN);
    ASSERT_EQ(break_flow_link_add(g, &d, &link), BREAK_FLOW_REJECTED);
    d = link_desc(BREAK_FLOW_PORT_VALUE, event, BREAK_FLOW_EVENT_VALUE_OUT,
                  action, BREAK_FLOW_EXEC_IN);
    ASSERT_EQ(break_flow_link_add(g, &d, &link), BREAK_FLOW_REJECTED);
    d = link_desc(BREAK_FLOW_PORT_VALUE, event, 99u, math,
                  BREAK_FLOW_MATH_INPUT_B);
    ASSERT_EQ(break_flow_link_add(g, &d, &link), BREAK_FLOW_REJECTED);
    ASSERT_EQ(break_flow_graph_link_count(g), 1u);
    ASSERT_EQ(break_flow_graph_revision(g), revision);
    break_flow_graph_destroy(g);
}

TEST(cycle_rejection_is_atomic_for_exec_and_value_edges) {
    BreakFlowGraph *g = break_flow_graph_create(NULL);
    ASSERT_NOT_NULL(g);
    u32 a = add_node(g, BREAK_FLOW_NODE_MATH_ADD);
    u32 b = add_node(g, BREAK_FLOW_NODE_MATH_MULTIPLY);
    BreakFlowLinkDesc d = link_desc(BREAK_FLOW_PORT_VALUE, a,
        BREAK_FLOW_MATH_VALUE_OUT, b, BREAK_FLOW_MATH_INPUT_A);
    u32 id = UINT32_MAX;
    ASSERT_EQ(break_flow_link_add(g, &d, &id), BREAK_FLOW_OK);
    u64 revision = break_flow_graph_revision(g);
    d = link_desc(BREAK_FLOW_PORT_VALUE, b, BREAK_FLOW_MATH_VALUE_OUT,
                  a, BREAK_FLOW_MATH_INPUT_A);
    id = UINT32_MAX;
    ASSERT_EQ(break_flow_link_add(g, &d, &id), BREAK_FLOW_REJECTED);
    ASSERT_EQ(id, UINT32_MAX);
    ASSERT_EQ(break_flow_graph_link_count(g), 1u);
    ASSERT_EQ(break_flow_graph_revision(g), revision);

    u32 delay = add_node(g, BREAK_FLOW_NODE_DELAY);
    u32 other_delay = add_node(g, BREAK_FLOW_NODE_DELAY);
    d = link_desc(BREAK_FLOW_PORT_EXEC, delay, BREAK_FLOW_DELAY_EXEC_OUT,
                  other_delay, BREAK_FLOW_EXEC_IN);
    ASSERT_EQ(break_flow_link_add(g, &d, &id), BREAK_FLOW_OK);
    d = link_desc(BREAK_FLOW_PORT_EXEC, other_delay, BREAK_FLOW_DELAY_EXEC_OUT,
                  delay, BREAK_FLOW_EXEC_IN);
    ASSERT_EQ(break_flow_link_add(g, &d, &id), BREAK_FLOW_REJECTED);
    ASSERT_EQ(break_flow_graph_link_count(g), 2u);
    break_flow_graph_destroy(g);
}

TEST(node_update_and_remove_preserve_graph_invariants) {
    BreakFlowGraph *g = break_flow_graph_create(NULL);
    ASSERT_NOT_NULL(g);
    u32 event = add_node(g, BREAK_FLOW_NODE_EVENT);
    BreakFlowNodeDesc other_desc = node_desc(BREAK_FLOW_NODE_EVENT);
    other_desc.event_key = 2u;
    u32 other = 0u;
    ASSERT_EQ(break_flow_node_add(g, &other_desc, &other), BREAK_FLOW_OK);
    u32 seq = add_node(g, BREAK_FLOW_NODE_SEQUENCE);
    BreakFlowLinkDesc d = link_desc(BREAK_FLOW_PORT_EXEC, event,
        BREAK_FLOW_EVENT_EXEC_OUT, seq, BREAK_FLOW_EXEC_IN);
    u32 link = 0;
    ASSERT_EQ(break_flow_link_add(g, &d, &link), BREAK_FLOW_OK);
    BreakFlowNodeDesc desc;
    ASSERT_EQ(break_flow_node_get(g, other, &desc), BREAK_FLOW_OK);
    desc.event_key = 1u;
    u64 revision = break_flow_graph_revision(g);
    ASSERT_EQ(break_flow_node_set(g, other, &desc), BREAK_FLOW_REJECTED);
    ASSERT_EQ(break_flow_graph_revision(g), revision);
    desc = node_desc(BREAK_FLOW_NODE_MATH_ADD);
    ASSERT_EQ(break_flow_node_set(g, seq, &desc), BREAK_FLOW_REJECTED);
    ASSERT_EQ(break_flow_node_remove(g, event), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_graph_link_count(g), 0u);
    ASSERT_EQ(break_flow_link_remove(g, link), BREAK_FLOW_STALE);
    ASSERT_EQ(break_flow_graph_validate(g), BREAK_FLOW_OK);
    break_flow_graph_destroy(g);
}

TEST(capacities_and_input_ranges_fail_closed) {
    BreakFlowConfig bad = {BREAK_FLOW_HARD_MAX_NODES + 1u, 1u};
    ASSERT_TRUE(break_flow_graph_create(&bad) == NULL);
    BreakFlowConfig cfg = {1u, 1u};
    BreakFlowGraph *g = break_flow_graph_create(&cfg);
    ASSERT_NOT_NULL(g);
    BreakFlowNodeDesc d = node_desc(BREAK_FLOW_NODE_EVENT);
    d.event_key = 0u;
    u32 id = 99u;
    ASSERT_EQ(break_flow_node_add(g, &d, &id), BREAK_FLOW_INVALID);
    ASSERT_EQ(id, 99u);
    d.event_key = 1u;
    ASSERT_EQ(break_flow_node_add(g, &d, &id), BREAK_FLOW_OK);
    d.event_key = 2u;
    ASSERT_EQ(break_flow_node_add(g, &d, &id), BREAK_FLOW_OVERLOAD);
    d.type = BREAK_FLOW_NODE_DELAY;
    d.delay_ticks = 0u;
    ASSERT_EQ(break_flow_node_set(g, id, &d), BREAK_FLOW_INVALID);
    break_flow_graph_destroy(g);
}

TEST(zero_config_fields_use_independent_defaults) {
    BreakFlowConfig both_zero = {0u, 0u};
    BreakFlowGraph *g = break_flow_graph_create(&both_zero);
    ASSERT_NOT_NULL(g);
    u32 id = add_node(g, BREAK_FLOW_NODE_SEQUENCE);
    ASSERT_EQ(id, 1u);
    break_flow_graph_destroy(g);

    BreakFlowConfig nodes_default = {0u, 1u};
    g = break_flow_graph_create(&nodes_default);
    ASSERT_NOT_NULL(g);
    break_flow_graph_destroy(g);
    BreakFlowConfig links_default = {1u, 0u};
    g = break_flow_graph_create(&links_default);
    ASSERT_NOT_NULL(g);
    id = add_node(g, BREAK_FLOW_NODE_SEQUENCE);
    ASSERT_EQ(id, 1u);
    BreakFlowNodeDesc d = node_desc(BREAK_FLOW_NODE_SEQUENCE);
    ASSERT_EQ(break_flow_node_add(g, &d, &id), BREAK_FLOW_OVERLOAD);
    break_flow_graph_destroy(g);

    BreakFlowConfig bad_nodes = {0u, BREAK_FLOW_HARD_MAX_LINKS + 1u};
    ASSERT_TRUE(break_flow_graph_create(&bad_nodes) == NULL);
    BreakFlowConfig bad_links = {BREAK_FLOW_HARD_MAX_NODES + 1u, 0u};
    ASSERT_TRUE(break_flow_graph_create(&bad_links) == NULL);
}

TEST(link_capacity_overflow_preserves_count_revision_and_next_id) {
    BreakFlowConfig cfg = {4u, 2u};
    BreakFlowGraph *g = break_flow_graph_create(&cfg);
    ASSERT_NOT_NULL(g);
    BreakFlowNodeDesc event = node_desc(BREAK_FLOW_NODE_EVENT);
    u32 first_event = 0u, second_event = 0u;
    ASSERT_EQ(break_flow_node_add(g, &event, &first_event), BREAK_FLOW_OK);
    event.event_key = 2u;
    ASSERT_EQ(break_flow_node_add(g, &event, &second_event), BREAK_FLOW_OK);
    u32 first_sequence = add_node(g, BREAK_FLOW_NODE_SEQUENCE);
    u32 second_sequence = add_node(g, BREAK_FLOW_NODE_SEQUENCE);
    BreakFlowLinkDesc d = link_desc(BREAK_FLOW_PORT_EXEC, first_event,
        BREAK_FLOW_EVENT_EXEC_OUT, first_sequence, BREAK_FLOW_EXEC_IN);
    u32 id = 0u;
    ASSERT_EQ(break_flow_link_add(g, &d, &id), BREAK_FLOW_OK);
    ASSERT_EQ(id, 1u);
    d = link_desc(BREAK_FLOW_PORT_EXEC, second_event,
        BREAK_FLOW_EVENT_EXEC_OUT, second_sequence, BREAK_FLOW_EXEC_IN);
    ASSERT_EQ(break_flow_link_add(g, &d, &id), BREAK_FLOW_OK);
    ASSERT_EQ(id, 2u);
    u64 revision = break_flow_graph_revision(g);
    u8 before[1024], after[1024];
    usize before_len = 0u, after_len = 0u;
    ASSERT_EQ(break_flow_serialize(g, before, sizeof(before), &before_len), BREAK_FLOW_OK);
    d = link_desc(BREAK_FLOW_PORT_EXEC, first_sequence,
        BREAK_FLOW_SEQUENCE_OUT_0, second_sequence, BREAK_FLOW_EXEC_IN);
    id = 777u;
    ASSERT_EQ(break_flow_link_add(g, &d, &id), BREAK_FLOW_OVERLOAD);
    ASSERT_EQ(id, 777u);
    ASSERT_EQ(break_flow_graph_link_count(g), 2u);
    ASSERT_EQ(break_flow_graph_revision(g), revision);
    ASSERT_EQ(break_flow_serialize(g, after, sizeof(after), &after_len), BREAK_FLOW_OK);
    ASSERT_EQ(after_len, before_len);
    ASSERT_TRUE(memcmp(before, after, before_len) == 0);
    break_flow_graph_destroy(g);
}

TEST(deepest_value_chain_validates_and_rejects_cycle_atomically) {
    BreakFlowGraph *g = break_flow_graph_create(NULL);
    ASSERT_NOT_NULL(g);
    for (u32 i = 0u; i < BREAK_FLOW_HARD_MAX_NODES; i++) {
        ASSERT_EQ(add_node(g, BREAK_FLOW_NODE_MATH_ADD), i + 1u);
    }
    for (u32 i = 2u; i <= BREAK_FLOW_HARD_MAX_NODES; i++) {
        BreakFlowLinkDesc d = link_desc(BREAK_FLOW_PORT_VALUE, i - 1u,
            BREAK_FLOW_MATH_VALUE_OUT, i, BREAK_FLOW_MATH_INPUT_A);
        u32 id = 0u;
        ASSERT_EQ(break_flow_link_add(g, &d, &id), BREAK_FLOW_OK);
    }
    ASSERT_EQ(break_flow_graph_node_count(g), BREAK_FLOW_HARD_MAX_NODES);
    ASSERT_EQ(break_flow_graph_link_count(g), BREAK_FLOW_HARD_MAX_NODES - 1u);
    ASSERT_EQ(break_flow_graph_validate(g), BREAK_FLOW_OK);
    u64 revision = break_flow_graph_revision(g);
    BreakFlowLinkDesc cycle = link_desc(BREAK_FLOW_PORT_VALUE,
        BREAK_FLOW_HARD_MAX_NODES, BREAK_FLOW_MATH_VALUE_OUT,
        1u, BREAK_FLOW_MATH_INPUT_A);
    u32 id = 999u;
    ASSERT_EQ(break_flow_link_add(g, &cycle, &id), BREAK_FLOW_REJECTED);
    ASSERT_EQ(id, 999u);
    ASSERT_EQ(break_flow_graph_link_count(g), BREAK_FLOW_HARD_MAX_NODES - 1u);
    ASSERT_EQ(break_flow_graph_revision(g), revision);
    break_flow_graph_destroy(g);
}

TEST_MAIN_BEGIN()
    RUN_TEST(link_capacity_overflow_preserves_count_revision_and_next_id);
    RUN_TEST(deepest_value_chain_validates_and_rejects_cycle_atomically);
    RUN_TEST(zero_config_fields_use_independent_defaults);
    RUN_TEST(stable_ids_survive_delete_and_iteration_is_sorted);
    RUN_TEST(explicit_ports_reject_bad_direction_kind_and_duplicate_input);
    RUN_TEST(cycle_rejection_is_atomic_for_exec_and_value_edges);
    RUN_TEST(node_update_and_remove_preserve_graph_invariants);
    RUN_TEST(capacities_and_input_ranges_fail_closed);
TEST_MAIN_END()
