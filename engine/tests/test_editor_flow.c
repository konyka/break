#include "test_framework.h"
#include <editor/editor_cmd.h>
#include <editor/editor_doc.h>
#include <editor/editor_flow.h>
#include <editor/editor_test_hooks.h>
#include <kernel/break_kernel.h>
#include <kernel/break_flow.h>
#include <string.h>

static BreakFlowNodeDesc node(BreakFlowNodeType type) {
    BreakFlowNodeDesc d;
    memset(&d, 0, sizeof(d));
    d.type = type;
    d.event_key = type == BREAK_FLOW_NODE_EVENT ? 9u : 0u;
    return d;
}

TEST(flow_commands_undo_redo_restore_ids_links_and_properties) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakFlowGraph *graph = break_editor_doc_flow_graph(doc);
    ASSERT_NOT_NULL(graph);
    ASSERT_EQ(break_flow_graph_node_count(graph), 0u);
    BreakFlowNodeDesc event = node(BREAK_FLOW_NODE_EVENT);
    u32 event_id = 0u;
    ASSERT_EQ(break_editor_flow_add_node(doc, &event, &event_id), BREAK_FLOW_OK);
    ASSERT_EQ(event_id, 1u);
    u32 sequence_id = 0u;
    BreakFlowNodeDesc sequence = node(BREAK_FLOW_NODE_SEQUENCE);
    ASSERT_EQ(break_editor_flow_add_node(doc, &sequence, &sequence_id), BREAK_FLOW_OK);
    ASSERT_EQ(sequence_id, 2u);
    BreakFlowLinkDesc link = {BREAK_FLOW_PORT_EXEC, event_id,
        BREAK_FLOW_EVENT_EXEC_OUT, sequence_id, BREAK_FLOW_EXEC_IN};
    u32 link_id = 0u;
    ASSERT_EQ(break_editor_flow_connect(doc, &link, &link_id), BREAK_FLOW_OK);
    ASSERT_EQ(link_id, 1u);
    graph = break_editor_doc_flow_graph(doc);
    ASSERT_EQ(break_flow_node_get(graph, sequence_id, &sequence), BREAK_FLOW_OK);
    ASSERT_STR_EQ(sequence.name, "sequence_2");
    memcpy(sequence.name, "ordered", sizeof("ordered"));
    ASSERT_EQ(break_editor_flow_set_node(doc, sequence_id, &sequence), BREAK_FLOW_OK);
    ASSERT_EQ(break_editor_flow_remove_node(doc, event_id), BREAK_FLOW_OK);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 5u);
    graph = break_editor_doc_flow_graph(doc);
    ASSERT_EQ(break_flow_graph_node_count(graph), 1u);
    ASSERT_EQ(break_flow_graph_link_count(graph), 0u);

    ASSERT_TRUE(break_editor_undo(doc));
    graph = break_editor_doc_flow_graph(doc);
    ASSERT_EQ(break_flow_graph_node_count(graph), 2u);
    ASSERT_EQ(break_flow_graph_link_count(graph), 1u);
    ASSERT_EQ(break_flow_node_get(graph, event_id, &event), BREAK_FLOW_OK);
    ASSERT_STR_EQ(event.name, "event_1");
    ASSERT_TRUE(break_editor_undo(doc));
    graph = break_editor_doc_flow_graph(doc);
    ASSERT_EQ(break_flow_node_get(graph, sequence_id, &sequence), BREAK_FLOW_OK);
    ASSERT_STR_EQ(sequence.name, "sequence_2");
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_flow_graph_link_count(break_editor_doc_flow_graph(doc)), 0u);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_flow_graph_node_count(break_editor_doc_flow_graph(doc)), 1u);
    ASSERT_TRUE(break_editor_undo(doc));
    ASSERT_EQ(break_flow_graph_node_count(break_editor_doc_flow_graph(doc)), 0u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 0u);
    ASSERT_EQ(break_editor_cmd_stack_redo_count(stack), 5u);
    for (u32 i = 0u; i < 5u; i++) ASSERT_TRUE(break_editor_redo(doc));
    graph = break_editor_doc_flow_graph(doc);
    ASSERT_EQ(break_flow_graph_node_count(graph), 1u);
    ASSERT_EQ(break_flow_node_get(graph, sequence_id, &sequence), BREAK_FLOW_OK);
    ASSERT_STR_EQ(sequence.name, "ordered");
    event.event_key = 10u;
    ASSERT_EQ(break_editor_flow_add_node(doc, &event, &event_id), BREAK_FLOW_OK);
    ASSERT_EQ(event_id, 3u);
    link.source_node = event_id;
    ASSERT_EQ(break_editor_flow_connect(doc, &link, &link_id), BREAK_FLOW_OK);
    ASSERT_EQ(link_id, 2u);
    break_editor_doc_destroy(doc);
}

TEST(invalid_and_oom_edits_do_not_enter_stack_and_reset_clears_graph) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakFlowNodeDesc event = node(BREAK_FLOW_NODE_EVENT);
    u32 event_id = 0u;
    ASSERT_EQ(break_editor_flow_add_node(doc, &event, &event_id), BREAK_FLOW_OK);
    u32 sequence_id = 0u;
    BreakFlowNodeDesc sequence = node(BREAK_FLOW_NODE_SEQUENCE);
    ASSERT_EQ(break_editor_flow_add_node(doc, &sequence, &sequence_id), BREAK_FLOW_OK);
    BreakEditorCmdStack *stack = break_editor_doc_stack(doc);
    u64 revision = break_editor_cmd_stack_revision(stack);
    BreakFlowLinkDesc bad = {BREAK_FLOW_PORT_EXEC, event_id, 99u,
                             sequence_id, BREAK_FLOW_EXEC_IN};
    u32 link_id = 88u;
    ASSERT_EQ(break_editor_flow_connect(doc, &bad, &link_id), BREAK_FLOW_REJECTED);
    ASSERT_EQ(link_id, 88u);
    ASSERT_EQ(break_editor_cmd_stack_revision(stack), revision);
    event.event_key = 0u;
    ASSERT_EQ(break_editor_flow_set_node(doc, event_id, &event), BREAK_FLOW_INVALID);
    ASSERT_EQ(break_editor_cmd_stack_revision(stack), revision);
    break_editor_test_set_alloc_budget(0u);
    event = node(BREAK_FLOW_NODE_EVENT);
    event.event_key = 11u;
    ASSERT_EQ(break_editor_flow_add_node(doc, &event, &event_id), BREAK_FLOW_OOM);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);
    ASSERT_EQ(break_editor_cmd_stack_revision(stack), revision);
    ASSERT_EQ(break_flow_graph_node_count(break_editor_doc_flow_graph(doc)), 2u);
    ASSERT_TRUE(break_editor_doc_reset(doc));
    ASSERT_EQ(break_flow_graph_node_count(break_editor_doc_flow_graph(doc)), 0u);
    ASSERT_EQ(break_editor_cmd_stack_undo_count(stack), 0u);
    break_editor_doc_destroy(doc);
}

TEST(editor_graph_is_a_real_runtime_consumer_source) {
    World *world = world_create();
    world_register_component(world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    BreakKernelConfig kernel_cfg = {0u, 1u};
    BreakKernel *kernel = break_kernel_create(world, &kernel_cfg);
    ComponentType components[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc cls = {"pawn", components, 1u, NULL};
    u32 class_id = 0u;
    ASSERT_EQ(break_kernel_register_class(kernel, &cls, &class_id), BREAK_KERNEL_OK);
    BreakKernelSpawn spawn = {class_id, {{1.0f, 2.0f, 3.0f}}};
    Entity actor = ENTITY_NULL;
    ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &actor), BREAK_KERNEL_OK);

    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    BreakFlowNodeDesc event = node(BREAK_FLOW_NODE_EVENT);
    event.event_key = 5u;
    u32 event_id = 0u;
    ASSERT_EQ(break_editor_flow_add_node(doc, &event, &event_id), BREAK_FLOW_OK);
    BreakFlowNodeDesc set = node(BREAK_FLOW_NODE_ENTITY_SET_POSITION);
    set.entity = actor;
    set.a = 6.0f; set.b = 7.0f; set.c = 8.0f;
    u32 set_id = 0u;
    ASSERT_EQ(break_editor_flow_add_node(doc, &set, &set_id), BREAK_FLOW_OK);
    BreakFlowLinkDesc link = {BREAK_FLOW_PORT_EXEC, event_id,
        BREAK_FLOW_EVENT_EXEC_OUT, set_id, BREAK_FLOW_EXEC_IN};
    u32 link_id = 0u;
    ASSERT_EQ(break_editor_flow_connect(doc, &link, &link_id), BREAK_FLOW_OK);
    BreakFlowRuntime *runtime = break_flow_runtime_create(
        break_editor_doc_flow_graph(doc), kernel, NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_flow_runtime_post(runtime, 5u, actor, 0.0f), BREAK_FLOW_OK);
    ASSERT_EQ(break_flow_runtime_tick(runtime), BREAK_FLOW_OK);
    const Vec3 *position = (const Vec3 *)world_get_component(
        world, actor, BREAK_KERNEL_POSITION_COMPONENT);
    ASSERT_FLOAT_EQ(position->e[0], 6.0f, 0.0f);
    ASSERT_FLOAT_EQ(position->e[1], 7.0f, 0.0f);
    ASSERT_FLOAT_EQ(position->e[2], 8.0f, 0.0f);
    break_flow_runtime_destroy(runtime);
    break_editor_doc_destroy(doc);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(flow_commands_undo_redo_restore_ids_links_and_properties);
    RUN_TEST(invalid_and_oom_edits_do_not_enter_stack_and_reset_clears_graph);
    RUN_TEST(editor_graph_is_a_real_runtime_consumer_source);
TEST_MAIN_END()
