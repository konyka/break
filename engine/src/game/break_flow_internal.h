#pragma once

#include <game/break_flow.h>

typedef struct BreakFlowNode {
    bool used;
    BreakFlowNodeDesc desc;
} BreakFlowNode;

typedef struct BreakFlowLink {
    bool used;
    BreakFlowLinkDesc desc;
} BreakFlowLink;

struct BreakFlowGraph {
    u32 max_nodes;
    u32 max_links;
    u32 node_count;
    u32 link_count;
    u32 next_node_id;
    u32 next_link_id;
    u64 revision;
    BreakFlowNode *nodes;
    BreakFlowLink *links;
    u8 *visit_state;
};

BreakFlowError break_flow_validate_node(const BreakFlowGraph *graph, u32 id,
                                        const BreakFlowNodeDesc *desc);
bool break_flow_port_schema(BreakFlowNodeType type, u32 port,
                            bool *output, BreakFlowPortKind *kind);
