#pragma once

#include <kernel/break_kernel.h>

#define BREAK_FLOW_HARD_MAX_NODES 256u
#define BREAK_FLOW_HARD_MAX_LINKS 1024u
#define BREAK_FLOW_HARD_MAX_EVENTS 4096u
#define BREAK_FLOW_HARD_MAX_ACTIONS 4096u
#define BREAK_FLOW_HARD_MAX_BUDGET 4096u
#define BREAK_FLOW_NAME_CAP 32u
#define BREAK_FLOW_MAX_DELAY_TICKS 65535u
#define BREAK_FLOW_SERIAL_VERSION 1u

typedef enum BreakFlowError {
    BREAK_FLOW_OK = 0,
    BREAK_FLOW_INVALID,
    BREAK_FLOW_CLOSED,
    BREAK_FLOW_OVERLOAD,
    BREAK_FLOW_OOM,
    BREAK_FLOW_TIMEOUT,
    BREAK_FLOW_STALE,
    BREAK_FLOW_REJECTED,
    BREAK_FLOW_FAILED
} BreakFlowError;

typedef enum BreakFlowNodeType {
    BREAK_FLOW_NODE_EVENT = 1,
    BREAK_FLOW_NODE_MATH_ADD,
    BREAK_FLOW_NODE_MATH_SUBTRACT,
    BREAK_FLOW_NODE_MATH_MULTIPLY,
    BREAK_FLOW_NODE_MATH_DIVIDE,
    BREAK_FLOW_NODE_COMPARE_LESS,
    BREAK_FLOW_NODE_COMPARE_EQUAL,
    BREAK_FLOW_NODE_COMPARE_GREATER,
    BREAK_FLOW_NODE_ENTITY_SET_POSITION,
    BREAK_FLOW_NODE_ENTITY_ADD_ITEM,
    BREAK_FLOW_NODE_DELAY,
    BREAK_FLOW_NODE_SEQUENCE,
    BREAK_FLOW_NODE_BRANCH
} BreakFlowNodeType;

typedef enum BreakFlowPortKind {
    BREAK_FLOW_PORT_EXEC = 1,
    BREAK_FLOW_PORT_VALUE = 2
} BreakFlowPortKind;

enum {
    BREAK_FLOW_EXEC_IN = 0,
    BREAK_FLOW_EVENT_EXEC_OUT = 1,
    BREAK_FLOW_EVENT_VALUE_OUT = 2,
    BREAK_FLOW_MATH_INPUT_A = 0,
    BREAK_FLOW_MATH_INPUT_B = 1,
    BREAK_FLOW_MATH_VALUE_OUT = 2,
    BREAK_FLOW_ACTION_EXEC_OUT = 1,
    BREAK_FLOW_ACTION_INPUT_X = 2,
    BREAK_FLOW_ACTION_INPUT_Y = 3,
    BREAK_FLOW_ACTION_INPUT_Z = 4,
    BREAK_FLOW_ACTION_INPUT_COUNT = 2,
    BREAK_FLOW_DELAY_EXEC_OUT = 1,
    BREAK_FLOW_SEQUENCE_OUT_0 = 1,
    BREAK_FLOW_SEQUENCE_OUT_1 = 2,
    BREAK_FLOW_BRANCH_TRUE_OUT = 1,
    BREAK_FLOW_BRANCH_FALSE_OUT = 2,
    BREAK_FLOW_BRANCH_CONDITION = 3
};

typedef struct BreakFlowNodeDesc {
    BreakFlowNodeType type;
    char name[BREAK_FLOW_NAME_CAP];
    u32 event_key;
    Entity entity;
    u32 item_id;
    u32 delay_ticks;
    f32 a;
    f32 b;
    f32 c;
} BreakFlowNodeDesc;

typedef struct BreakFlowLinkDesc {
    BreakFlowPortKind kind;
    u32 source_node;
    u32 source_port;
    u32 target_node;
    u32 target_port;
} BreakFlowLinkDesc;

typedef struct BreakFlowConfig {
    u32 max_nodes;
    u32 max_links;
} BreakFlowConfig;

typedef struct BreakFlowGraph BreakFlowGraph;
typedef struct BreakFlowRuntime BreakFlowRuntime;

BreakFlowGraph *break_flow_graph_create(const BreakFlowConfig *config);
void break_flow_graph_destroy(BreakFlowGraph *graph);
u32 break_flow_graph_node_count(const BreakFlowGraph *graph);
u32 break_flow_graph_link_count(const BreakFlowGraph *graph);
u64 break_flow_graph_revision(const BreakFlowGraph *graph);
BreakFlowError break_flow_graph_validate(const BreakFlowGraph *graph);

BreakFlowError break_flow_node_add(BreakFlowGraph *graph,
                                   const BreakFlowNodeDesc *desc, u32 *out_id);
BreakFlowError break_flow_node_remove(BreakFlowGraph *graph, u32 id);
BreakFlowError break_flow_node_set(BreakFlowGraph *graph, u32 id,
                                   const BreakFlowNodeDesc *desc);
BreakFlowError break_flow_node_get(const BreakFlowGraph *graph, u32 id,
                                   BreakFlowNodeDesc *out_desc);
BreakFlowError break_flow_node_at(const BreakFlowGraph *graph, u32 ordinal,
                                  u32 *out_id, BreakFlowNodeDesc *out_desc);

BreakFlowError break_flow_link_add(BreakFlowGraph *graph,
                                   const BreakFlowLinkDesc *desc, u32 *out_id);
BreakFlowError break_flow_link_remove(BreakFlowGraph *graph, u32 id);
BreakFlowError break_flow_link_get(const BreakFlowGraph *graph, u32 id,
                                   BreakFlowLinkDesc *out_desc);
BreakFlowError break_flow_link_at(const BreakFlowGraph *graph, u32 ordinal,
                                  u32 *out_id, BreakFlowLinkDesc *out_desc);

BreakFlowError break_flow_serialized_size(const BreakFlowGraph *graph,
                                          usize *out_size);
BreakFlowError break_flow_serialize(const BreakFlowGraph *graph, void *out,
                                    usize capacity, usize *out_written);
BreakFlowError break_flow_deserialize(const void *bytes, usize length,
                                      BreakFlowGraph **out_graph);

typedef struct BreakFlowRuntimeConfig {
    u32 max_events;
    u32 max_actions;
    u32 node_budget;
} BreakFlowRuntimeConfig;

BreakFlowRuntime *break_flow_runtime_create(BreakFlowGraph *graph, BreakKernel *kernel,
                                            const BreakFlowRuntimeConfig *config);
void break_flow_runtime_destroy(BreakFlowRuntime *runtime);
BreakFlowError break_flow_runtime_check_owner(const BreakFlowRuntime *runtime);
BreakFlowError break_flow_runtime_reset(BreakFlowRuntime *runtime);
BreakFlowError break_flow_runtime_post(BreakFlowRuntime *runtime, u32 event_key,
                                       Entity entity, f32 value);
BreakFlowError break_flow_runtime_tick(BreakFlowRuntime *runtime);
u32 break_flow_runtime_pending_count(const BreakFlowRuntime *runtime);
u64 break_flow_runtime_now_tick(const BreakFlowRuntime *runtime);
u64 break_flow_runtime_next_sequence(const BreakFlowRuntime *runtime);
