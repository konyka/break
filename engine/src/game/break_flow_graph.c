#include <game/break_flow_internal.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool valid_type(BreakFlowNodeType type) {
    return type >= BREAK_FLOW_NODE_EVENT && type <= BREAK_FLOW_NODE_BRANCH;
}

static bool math_type(BreakFlowNodeType type) {
    return type >= BREAK_FLOW_NODE_MATH_ADD && type <= BREAK_FLOW_NODE_COMPARE_GREATER;
}

static const char *type_name(BreakFlowNodeType type) {
    static const char *const names[] = {
        "event", "add", "subtract", "multiply", "divide", "less", "equal",
        "greater", "set_position", "add_item", "delay", "sequence", "branch"
    };
    return valid_type(type) ? names[(u32)type - 1u] : "invalid";
}

static BreakFlowError normalize_node(const BreakFlowGraph *graph, u32 id,
                                     const BreakFlowNodeDesc *input,
                                     BreakFlowNodeDesc *out) {
    if (!input || !out || !valid_type(input->type) ||
        !isfinite(input->a) || !isfinite(input->b) || !isfinite(input->c) ||
        input->delay_ticks > BREAK_FLOW_MAX_DELAY_TICKS) {
        return BREAK_FLOW_INVALID;
    }
    *out = *input;
    u32 length = 0u;
    while (length < BREAK_FLOW_NAME_CAP && input->name[length] != '\0') {
        unsigned char ch = (unsigned char)input->name[length];
        if (ch < 32u || ch > 126u) return BREAK_FLOW_INVALID;
        length++;
    }
    if (length == BREAK_FLOW_NAME_CAP) return BREAK_FLOW_INVALID;
    if (length == 0u) {
        int written = snprintf(out->name, sizeof(out->name), "%s_%u",
                               type_name(input->type), id);
        if (written < 0 || (usize)written >= sizeof(out->name)) {
            return BREAK_FLOW_INVALID;
        }
    }
    if (input->type == BREAK_FLOW_NODE_EVENT && input->event_key == 0u) {
        return BREAK_FLOW_INVALID;
    }
    if (input->type == BREAK_FLOW_NODE_DELAY && input->delay_ticks == 0u) {
        return BREAK_FLOW_INVALID;
    }
    if ((input->type == BREAK_FLOW_NODE_ENTITY_SET_POSITION ||
         input->type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM) &&
        (!entity_valid(input->entity) || input->entity.index == 0u ||
         input->entity.index >= ECS_MAX_ENTITIES)) {
        return BREAK_FLOW_INVALID;
    }
    if (input->type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM &&
        (input->item_id == 0u || input->item_id > BREAK_GAME_MAX_ITEMS)) {
        return BREAK_FLOW_INVALID;
    }
    if (graph && input->type == BREAK_FLOW_NODE_EVENT) {
        for (u32 other = 1u; other <= graph->max_nodes; other++) {
            if (other != id && graph->nodes[other].used &&
                graph->nodes[other].desc.type == BREAK_FLOW_NODE_EVENT &&
                graph->nodes[other].desc.event_key == input->event_key) {
                return BREAK_FLOW_REJECTED;
            }
        }
    }
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_validate_node(const BreakFlowGraph *graph, u32 id,
                                        const BreakFlowNodeDesc *desc) {
    BreakFlowNodeDesc normalized;
    return normalize_node(graph, id, desc, &normalized);
}

bool break_flow_port_schema(BreakFlowNodeType type, u32 port,
                            bool *output, BreakFlowPortKind *kind) {
    if (!output || !kind) return false;
    if (type == BREAK_FLOW_NODE_EVENT) {
        if (port == BREAK_FLOW_EVENT_EXEC_OUT) {
            *output = true; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        if (port == BREAK_FLOW_EVENT_VALUE_OUT) {
            *output = true; *kind = BREAK_FLOW_PORT_VALUE; return true;
        }
        return false;
    }
    if (math_type(type)) {
        if (port == BREAK_FLOW_MATH_INPUT_A || port == BREAK_FLOW_MATH_INPUT_B) {
            *output = false; *kind = BREAK_FLOW_PORT_VALUE; return true;
        }
        if (port == BREAK_FLOW_MATH_VALUE_OUT) {
            *output = true; *kind = BREAK_FLOW_PORT_VALUE; return true;
        }
        return false;
    }
    if (type == BREAK_FLOW_NODE_ENTITY_SET_POSITION ||
        type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM) {
        if (port == BREAK_FLOW_EXEC_IN) {
            *output = false; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        if (port == BREAK_FLOW_ACTION_EXEC_OUT) {
            *output = true; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        if (type == BREAK_FLOW_NODE_ENTITY_SET_POSITION &&
            (port == BREAK_FLOW_ACTION_INPUT_X ||
             port == BREAK_FLOW_ACTION_INPUT_Y ||
             port == BREAK_FLOW_ACTION_INPUT_Z)) {
            *output = false; *kind = BREAK_FLOW_PORT_VALUE; return true;
        }
        if (type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM &&
            port == BREAK_FLOW_ACTION_INPUT_COUNT) {
            *output = false; *kind = BREAK_FLOW_PORT_VALUE; return true;
        }
        return false;
    }
    if (type == BREAK_FLOW_NODE_DELAY) {
        if (port == BREAK_FLOW_EXEC_IN) {
            *output = false; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        if (port == BREAK_FLOW_DELAY_EXEC_OUT) {
            *output = true; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        return false;
    }
    if (type == BREAK_FLOW_NODE_SEQUENCE) {
        if (port == BREAK_FLOW_EXEC_IN) {
            *output = false; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        if (port == BREAK_FLOW_SEQUENCE_OUT_0 ||
            port == BREAK_FLOW_SEQUENCE_OUT_1) {
            *output = true; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        return false;
    }
    if (type == BREAK_FLOW_NODE_BRANCH) {
        if (port == BREAK_FLOW_EXEC_IN) {
            *output = false; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        if (port == BREAK_FLOW_BRANCH_TRUE_OUT ||
            port == BREAK_FLOW_BRANCH_FALSE_OUT) {
            *output = true; *kind = BREAK_FLOW_PORT_EXEC; return true;
        }
        if (port == BREAK_FLOW_BRANCH_CONDITION) {
            *output = false; *kind = BREAK_FLOW_PORT_VALUE; return true;
        }
        return false;
    }
    return false;
}

static bool dfs_visit(const BreakFlowGraph *graph, u32 id, u8 *state) {
    if (state[id] == 1u) return false;
    if (state[id] == 2u) return true;
    state[id] = 1u;
    for (u32 i = 1u; i <= graph->max_links; i++) {
        const BreakFlowLink *link = &graph->links[i];
        if (link->used && link->desc.source_node == id &&
            !dfs_visit(graph, link->desc.target_node, state)) {
            return false;
        }
    }
    state[id] = 2u;
    return true;
}

BreakFlowGraph *break_flow_graph_create(const BreakFlowConfig *config) {
    BreakFlowConfig effective = {BREAK_FLOW_HARD_MAX_NODES, BREAK_FLOW_HARD_MAX_LINKS};
    if (config) effective = *config;
    if (!effective.max_nodes || !effective.max_links ||
        effective.max_nodes > BREAK_FLOW_HARD_MAX_NODES ||
        effective.max_links > BREAK_FLOW_HARD_MAX_LINKS) return NULL;
    BreakFlowGraph *g = (BreakFlowGraph *)calloc(1u, sizeof(*g));
    if (!g) return NULL;
    g->max_nodes = effective.max_nodes;
    g->max_links = effective.max_links;
    g->next_node_id = 1u;
    g->next_link_id = 1u;
    g->nodes = (BreakFlowNode *)calloc((size_t)g->max_nodes + 1u, sizeof(*g->nodes));
    g->links = (BreakFlowLink *)calloc((size_t)g->max_links + 1u, sizeof(*g->links));
    g->visit_state = (u8 *)calloc((size_t)g->max_nodes + 1u, 1u);
    if (!g->nodes || !g->links || !g->visit_state) {
        break_flow_graph_destroy(g);
        return NULL;
    }
    return g;
}

void break_flow_graph_destroy(BreakFlowGraph *graph) {
    if (!graph) return;
    free(graph->nodes);
    free(graph->links);
    free(graph->visit_state);
    free(graph);
}

u32 break_flow_graph_node_count(const BreakFlowGraph *graph) {
    return graph ? graph->node_count : 0u;
}

u32 break_flow_graph_link_count(const BreakFlowGraph *graph) {
    return graph ? graph->link_count : 0u;
}

u64 break_flow_graph_revision(const BreakFlowGraph *graph) {
    return graph ? graph->revision : 0u;
}

BreakFlowError break_flow_graph_validate(const BreakFlowGraph *graph) {
    if (!graph || graph->next_node_id == 0u || graph->next_link_id == 0u ||
        graph->next_node_id > graph->max_nodes + 1u ||
        graph->next_link_id > graph->max_links + 1u) {
        return BREAK_FLOW_INVALID;
    }
    u32 nodes = 0u;
    u32 links = 0u;
    u32 max_node = 0u;
    u32 max_link = 0u;
    for (u32 i = 1u; i <= graph->max_nodes; i++) {
        if (!graph->nodes[i].used) continue;
        nodes++;
        max_node = i;
        BreakFlowError valid = break_flow_validate_node(graph, i, &graph->nodes[i].desc);
        if (valid != BREAK_FLOW_OK) return valid;
        if (graph->nodes[i].desc.name[0] == '\0') return BREAK_FLOW_INVALID;
    }
    for (u32 i = 1u; i <= graph->max_links; i++) {
        if (!graph->links[i].used) continue;
        links++;
        max_link = i;
        const BreakFlowLinkDesc *d = &graph->links[i].desc;
        if (d->source_node == 0u || d->source_node > graph->max_nodes ||
            d->target_node == 0u || d->target_node > graph->max_nodes ||
            !graph->nodes[d->source_node].used || !graph->nodes[d->target_node].used) {
            return BREAK_FLOW_STALE;
        }
        bool source_output = false;
        bool target_output = false;
        BreakFlowPortKind source_kind = BREAK_FLOW_PORT_EXEC;
        BreakFlowPortKind target_kind = BREAK_FLOW_PORT_EXEC;
        if (!break_flow_port_schema(graph->nodes[d->source_node].desc.type,
                                    d->source_port, &source_output, &source_kind) ||
            !break_flow_port_schema(graph->nodes[d->target_node].desc.type,
                                    d->target_port, &target_output, &target_kind) ||
            !source_output || target_output || d->kind != source_kind ||
            d->kind != target_kind) {
            return BREAK_FLOW_REJECTED;
        }
        for (u32 k = 1u; k < i; k++) {
            if (!graph->links[k].used) continue;
            const BreakFlowLinkDesc *other = &graph->links[k].desc;
            if ((d->kind == BREAK_FLOW_PORT_EXEC &&
                 d->source_node == other->source_node &&
                 d->source_port == other->source_port) ||
                (d->kind == BREAK_FLOW_PORT_VALUE &&
                 d->target_node == other->target_node &&
                 d->target_port == other->target_port)) {
                return BREAK_FLOW_REJECTED;
            }
        }
    }
    if (nodes != graph->node_count || links != graph->link_count ||
        max_node >= graph->next_node_id || max_link >= graph->next_link_id) {
        return BREAK_FLOW_INVALID;
    }
    u8 state[BREAK_FLOW_HARD_MAX_NODES + 1u];
    memset(state, 0, sizeof(state));
    for (u32 i = 1u; i <= graph->max_nodes; i++) {
        if (graph->nodes[i].used && !dfs_visit(graph, i, state)) {
            return BREAK_FLOW_REJECTED;
        }
    }
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_node_add(BreakFlowGraph *graph,
                                   const BreakFlowNodeDesc *desc, u32 *out_id) {
    if (!graph || !desc || !out_id) return BREAK_FLOW_INVALID;
    BreakFlowNodeDesc normalized;
    BreakFlowError valid = normalize_node(graph, graph->next_node_id, desc, &normalized);
    if (valid != BREAK_FLOW_OK) return valid;
    if (graph->node_count >= graph->max_nodes || graph->next_node_id > graph->max_nodes) {
        return BREAK_FLOW_OVERLOAD;
    }
    u32 id = graph->next_node_id++;
    graph->nodes[id].used = true;
    graph->nodes[id].desc = normalized;
    graph->node_count++;
    graph->revision++;
    *out_id = id;
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_node_remove(BreakFlowGraph *graph, u32 id) {
    if (!graph) return BREAK_FLOW_INVALID;
    if (id == 0u || id > graph->max_nodes || !graph->nodes[id].used) {
        return BREAK_FLOW_STALE;
    }
    memset(&graph->nodes[id], 0, sizeof(graph->nodes[id]));
    graph->node_count--;
    for (u32 i = 1u; i <= graph->max_links; i++) {
        if (graph->links[i].used &&
            (graph->links[i].desc.source_node == id ||
             graph->links[i].desc.target_node == id)) {
            memset(&graph->links[i], 0, sizeof(graph->links[i]));
            graph->link_count--;
        }
    }
    graph->revision++;
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_node_set(BreakFlowGraph *graph, u32 id,
                                   const BreakFlowNodeDesc *desc) {
    if (!graph || !desc) return BREAK_FLOW_INVALID;
    if (id == 0u || id > graph->max_nodes || !graph->nodes[id].used) {
        return BREAK_FLOW_STALE;
    }
    BreakFlowNodeDesc normalized;
    BreakFlowError valid = normalize_node(graph, id, desc, &normalized);
    if (valid != BREAK_FLOW_OK) return valid;
    BreakFlowNodeDesc old = graph->nodes[id].desc;
    graph->nodes[id].desc = normalized;
    valid = break_flow_graph_validate(graph);
    if (valid != BREAK_FLOW_OK) {
        graph->nodes[id].desc = old;
        return valid;
    }
    graph->revision++;
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_node_get(const BreakFlowGraph *graph, u32 id,
                                   BreakFlowNodeDesc *out_desc) {
    if (!graph || !out_desc) return BREAK_FLOW_INVALID;
    if (id == 0u || id > graph->max_nodes || !graph->nodes[id].used) {
        return BREAK_FLOW_STALE;
    }
    *out_desc = graph->nodes[id].desc;
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_node_at(const BreakFlowGraph *graph, u32 ordinal,
                                  u32 *out_id, BreakFlowNodeDesc *out_desc) {
    if (!graph || !out_id || !out_desc) return BREAK_FLOW_INVALID;
    if (ordinal >= graph->node_count) return BREAK_FLOW_STALE;
    for (u32 i = 1u; i <= graph->max_nodes; i++) {
        if (!graph->nodes[i].used) continue;
        if (ordinal == 0u) {
            *out_id = i;
            *out_desc = graph->nodes[i].desc;
            return BREAK_FLOW_OK;
        }
        ordinal--;
    }
    return BREAK_FLOW_STALE;
}

BreakFlowError break_flow_link_add(BreakFlowGraph *graph,
                                   const BreakFlowLinkDesc *desc, u32 *out_id) {
    if (!graph || !desc || !out_id) return BREAK_FLOW_INVALID;
    if (desc->source_node == 0u || desc->source_node > graph->max_nodes ||
        desc->target_node == 0u || desc->target_node > graph->max_nodes ||
        !graph->nodes[desc->source_node].used || !graph->nodes[desc->target_node].used) {
        return BREAK_FLOW_STALE;
    }
    if (graph->link_count >= graph->max_links || graph->next_link_id > graph->max_links) {
        return BREAK_FLOW_OVERLOAD;
    }
    u32 id = graph->next_link_id;
    graph->links[id].used = true;
    graph->links[id].desc = *desc;
    graph->link_count++;
    graph->next_link_id++;
    BreakFlowError valid = break_flow_graph_validate(graph);
    if (valid != BREAK_FLOW_OK) {
        memset(&graph->links[id], 0, sizeof(graph->links[id]));
        graph->link_count--;
        graph->next_link_id--;
        return valid == BREAK_FLOW_STALE ? BREAK_FLOW_REJECTED : valid;
    }
    graph->revision++;
    *out_id = id;
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_link_remove(BreakFlowGraph *graph, u32 id) {
    if (!graph) return BREAK_FLOW_INVALID;
    if (id == 0u || id > graph->max_links || !graph->links[id].used) {
        return BREAK_FLOW_STALE;
    }
    memset(&graph->links[id], 0, sizeof(graph->links[id]));
    graph->link_count--;
    graph->revision++;
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_link_get(const BreakFlowGraph *graph, u32 id,
                                   BreakFlowLinkDesc *out_desc) {
    if (!graph || !out_desc) return BREAK_FLOW_INVALID;
    if (id == 0u || id > graph->max_links || !graph->links[id].used) {
        return BREAK_FLOW_STALE;
    }
    *out_desc = graph->links[id].desc;
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_link_at(const BreakFlowGraph *graph, u32 ordinal,
                                  u32 *out_id, BreakFlowLinkDesc *out_desc) {
    if (!graph || !out_id || !out_desc) return BREAK_FLOW_INVALID;
    if (ordinal >= graph->link_count) return BREAK_FLOW_STALE;
    for (u32 i = 1u; i <= graph->max_links; i++) {
        if (!graph->links[i].used) continue;
        if (ordinal == 0u) {
            *out_id = i;
            *out_desc = graph->links[i].desc;
            return BREAK_FLOW_OK;
        }
        ordinal--;
    }
    return BREAK_FLOW_STALE;
}
