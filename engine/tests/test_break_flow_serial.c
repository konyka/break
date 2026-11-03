#include "test_framework.h"
#include <game/break_flow.h>
#include <stdint.h>
#include <string.h>

#define HEADER_SIZE 48u
#define NODE_SIZE 80u
#define LINK_SIZE 24u

static void put32(u8 *p, u32 v) {
    p[0] = (u8)v;
    p[1] = (u8)(v >> 8);
    p[2] = (u8)(v >> 16);
    p[3] = (u8)(v >> 24);
}

static BreakFlowNodeDesc desc(BreakFlowNodeType type) {
    BreakFlowNodeDesc d;
    memset(&d, 0, sizeof(d));
    d.type = type;
    d.event_key = type == BREAK_FLOW_NODE_EVENT ? 42u : 0u;
    d.delay_ticks = type == BREAK_FLOW_NODE_DELAY ? 2u : 0u;
    d.entity.index = 7u;
    d.entity.generation = 9u;
    d.item_id = 3u;
    d.a = 2.5f;
    d.b = -3.0f;
    return d;
}

static bool add(BreakFlowGraph *g, BreakFlowNodeType type, u32 *id) {
    BreakFlowNodeDesc d = desc(type);
    return break_flow_node_add(g, &d, id) == BREAK_FLOW_OK;
}

static bool add_link(BreakFlowGraph *g, u32 sn, u32 sp, u32 tn, u32 tp,
                 BreakFlowPortKind kind, u32 *id) {
    BreakFlowLinkDesc d = {kind, sn, sp, tn, tp};
    return break_flow_link_add(g, &d, id) == BREAK_FLOW_OK;
}

static usize fixture(BreakFlowGraph **out, u8 bytes[512]) {
    BreakFlowConfig cfg = {8u, 16u};
    BreakFlowGraph *g = break_flow_graph_create(&cfg);
    u32 event = 0, math = 0, branch = 0, edge = 0;
    if (!g || !add(g, BREAK_FLOW_NODE_EVENT, &event) ||
        !add(g, BREAK_FLOW_NODE_MATH_ADD, &math) ||
        !add(g, BREAK_FLOW_NODE_BRANCH, &branch) ||
        !add_link(g, event, BREAK_FLOW_EVENT_VALUE_OUT, math,
              BREAK_FLOW_MATH_INPUT_A, BREAK_FLOW_PORT_VALUE, &edge) ||
        !add_link(g, math, BREAK_FLOW_MATH_VALUE_OUT, branch,
              BREAK_FLOW_BRANCH_CONDITION, BREAK_FLOW_PORT_VALUE, &edge)) {
        break_flow_graph_destroy(g);
        return 0u;
    }
    usize len = 0u;
    if (break_flow_serialize(g, bytes, 512u, &len) != BREAK_FLOW_OK) len = 0u;
    if (len == 0u) break_flow_graph_destroy(g);
    *out = len ? g : NULL;
    return len;
}

static void expect_invalid(const u8 *bytes, usize len) {
    BreakFlowGraph *loaded = (BreakFlowGraph *)(uintptr_t)1u;
    ASSERT_EQ(break_flow_deserialize(bytes, len, &loaded), BREAK_FLOW_INVALID);
    ASSERT_TRUE(loaded == NULL);
}

TEST(round_trip_preserves_ids_ports_properties_and_next_ids) {
    BreakFlowGraph *original = NULL;
    u8 bytes[512];
    usize len = fixture(&original, bytes);
    ASSERT_TRUE(len > HEADER_SIZE);
    BreakFlowGraph *loaded = NULL;
    ASSERT_EQ(break_flow_deserialize(bytes, len, &loaded), BREAK_FLOW_OK);
    ASSERT_NOT_NULL(loaded);
    ASSERT_EQ(break_flow_graph_node_count(loaded), 3u);
    ASSERT_EQ(break_flow_graph_link_count(loaded), 2u);
    for (u32 i = 0; i < 3u; i++) {
        u32 a_id = 0, b_id = 0;
        BreakFlowNodeDesc a, b;
        ASSERT_EQ(break_flow_node_at(original, i, &a_id, &a), BREAK_FLOW_OK);
        ASSERT_EQ(break_flow_node_at(loaded, i, &b_id, &b), BREAK_FLOW_OK);
        ASSERT_EQ(a_id, b_id);
        ASSERT_EQ(a.type, b.type);
        ASSERT_EQ(a.event_key, b.event_key);
        ASSERT_EQ(a.entity.index, b.entity.index);
        ASSERT_EQ(a.entity.generation, b.entity.generation);
        ASSERT_EQ(a.item_id, b.item_id);
        ASSERT_EQ(a.delay_ticks, b.delay_ticks);
        ASSERT_STR_EQ(a.name, b.name);
        ASSERT_TRUE(memcmp(&a.a, &b.a, sizeof(f32) * 3u) == 0);
    }
    BreakFlowLinkDesc edge;
    u32 edge_id = 0;
    ASSERT_EQ(break_flow_link_at(loaded, 1u, &edge_id, &edge), BREAK_FLOW_OK);
    ASSERT_EQ(edge.source_node, 2u);
    ASSERT_EQ(edge.source_port, BREAK_FLOW_MATH_VALUE_OUT);
    ASSERT_EQ(edge.target_node, 3u);
    ASSERT_EQ(edge.target_port, BREAK_FLOW_BRANCH_CONDITION);
    break_flow_graph_destroy(loaded);
    break_flow_graph_destroy(original);

    BreakFlowGraph *holes = break_flow_graph_create(NULL);
    u32 id = 0;
    ASSERT_TRUE(add(holes, BREAK_FLOW_NODE_SEQUENCE, &id));
    ASSERT_EQ(break_flow_node_remove(holes, id), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_serialize(holes, bytes, sizeof(bytes), &len), BREAK_FLOW_OK);
    loaded = NULL;
    ASSERT_EQ(break_flow_deserialize(bytes, len, &loaded), BREAK_FLOW_OK);
    ASSERT_TRUE(add(loaded, BREAK_FLOW_NODE_SEQUENCE, &id));
    ASSERT_EQ(id, 2u);
    break_flow_graph_destroy(loaded);
    break_flow_graph_destroy(holes);
}

TEST(serialization_capacity_is_checked_without_success_length) {
    BreakFlowGraph *original = NULL;
    u8 bytes[512];
    usize len = fixture(&original, bytes);
    ASSERT_TRUE(len > 0u);
    u8 small[16];
    memset(small, 0xA5, sizeof(small));
    usize written = 777u;
    ASSERT_EQ(break_flow_serialize(original, small, sizeof(small), &written),
              BREAK_FLOW_OVERLOAD);
    ASSERT_EQ(written, 777u);
    usize required = 0u;
    ASSERT_EQ(break_flow_serialized_size(original, &required), BREAK_FLOW_OK);
    ASSERT_EQ(required, len);
    break_flow_graph_destroy(original);
}

TEST(header_length_version_count_and_truncation_are_rejected) {
    BreakFlowGraph *original = NULL;
    u8 bytes[512];
    usize len = fixture(&original, bytes);
    ASSERT_TRUE(len > 0u);
    u8 bad[513];
    memcpy(bad, bytes, len);
    put32(bad + 8u, BREAK_FLOW_SERIAL_VERSION + 1u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 12u, HEADER_SIZE - 4u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 16u, (u32)len - 1u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 20u, 0u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 28u, BREAK_FLOW_HARD_MAX_NODES + 1u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 32u, BREAK_FLOW_HARD_MAX_LINKS + 1u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 36u, 1u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 40u, 1u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 36u, 1u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + 44u, 1u);
    expect_invalid(bad, len);
    expect_invalid(bytes, len - 1u);
    memcpy(bad, bytes, len);
    bad[len] = 0u;
    expect_invalid(bad, len + 1u);
    break_flow_graph_destroy(original);
}

TEST(node_records_validate_identity_names_types_and_ranges) {
    BreakFlowGraph *original = NULL;
    u8 bytes[512];
    usize len = fixture(&original, bytes);
    ASSERT_TRUE(len > 0u);
    u8 bad[512];
    memcpy(bad, bytes, len);
    put32(bad + HEADER_SIZE, 0u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + HEADER_SIZE + NODE_SIZE, 1u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + HEADER_SIZE + 4u, 0u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + HEADER_SIZE + 8u, 0u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    bad[HEADER_SIZE + 12u] = 1u;
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + HEADER_SIZE + 44u, 0u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + HEADER_SIZE + 64u, 0x7fc00000u);
    expect_invalid(bad, len);
    break_flow_graph_destroy(original);

    BreakFlowGraph *delay_graph = break_flow_graph_create(NULL);
    u32 delay = 0;
    ASSERT_TRUE(add(delay_graph, BREAK_FLOW_NODE_DELAY, &delay));
    ASSERT_EQ(break_flow_serialize(delay_graph, bytes, sizeof(bytes), &len), BREAK_FLOW_OK);
    put32(bytes + HEADER_SIZE + 60u, 0u);
    expect_invalid(bytes, len);
    break_flow_graph_destroy(delay_graph);
}

TEST(entity_handle_indices_are_range_validated) {
    BreakFlowGraph *g = break_flow_graph_create(NULL);
    u32 action = 0u;
    ASSERT_TRUE(add(g, BREAK_FLOW_NODE_ENTITY_SET_POSITION, &action));
    u8 bytes[512];
    usize len = 0u;
    ASSERT_EQ(break_flow_serialize(g, bytes, sizeof(bytes), &len), BREAK_FLOW_OK);
    put32(bytes + HEADER_SIZE + 48u, 0u);
    expect_invalid(bytes, len);
    put32(bytes + HEADER_SIZE + 48u, ECS_MAX_ENTITIES);
    expect_invalid(bytes, len);
    break_flow_graph_destroy(g);
}

TEST(link_references_ports_and_cycles_are_rejected) {
    BreakFlowGraph *original = NULL;
    u8 bytes[512];
    usize len = fixture(&original, bytes);
    ASSERT_TRUE(len > 0u);
    const usize links = HEADER_SIZE + 3u * NODE_SIZE;
    u8 bad[512];
    memcpy(bad, bytes, len);
    put32(bad + links + 8u, 99u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + links + 16u, 99u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + links + 20u, 99u);
    expect_invalid(bad, len);
    memcpy(bad, bytes, len);
    put32(bad + links + LINK_SIZE, 1u);
    expect_invalid(bad, len);
    break_flow_graph_destroy(original);

    BreakFlowGraph *g = break_flow_graph_create(NULL);
    u32 a = 0, b = 0, c = 0, edge = 0;
    ASSERT_TRUE(add(g, BREAK_FLOW_NODE_DELAY, &a));
    ASSERT_TRUE(add(g, BREAK_FLOW_NODE_DELAY, &b));
    ASSERT_TRUE(add(g, BREAK_FLOW_NODE_DELAY, &c));
    ASSERT_TRUE(add_link(g, a, BREAK_FLOW_DELAY_EXEC_OUT, b, BREAK_FLOW_EXEC_IN,
                     BREAK_FLOW_PORT_EXEC, &edge));
    ASSERT_TRUE(add_link(g, c, BREAK_FLOW_DELAY_EXEC_OUT, a, BREAK_FLOW_EXEC_IN,
                     BREAK_FLOW_PORT_EXEC, &edge));
    ASSERT_EQ(break_flow_serialize(g, bytes, sizeof(bytes), &len), BREAK_FLOW_OK);
    put32(bytes + HEADER_SIZE + 3u * NODE_SIZE + LINK_SIZE + 8u, b);
    expect_invalid(bytes, len);
    break_flow_graph_destroy(g);
}

TEST_MAIN_BEGIN()
    RUN_TEST(round_trip_preserves_ids_ports_properties_and_next_ids);
    RUN_TEST(serialization_capacity_is_checked_without_success_length);
    RUN_TEST(header_length_version_count_and_truncation_are_rejected);
    RUN_TEST(node_records_validate_identity_names_types_and_ranges);
    RUN_TEST(entity_handle_indices_are_range_validated);
    RUN_TEST(link_references_ports_and_cycles_are_rejected);
TEST_MAIN_END()
