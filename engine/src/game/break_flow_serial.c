#include <game/break_flow_internal.h>

#include <stdlib.h>
#include <string.h>

#define FLOW_HEADER_SIZE 48u
#define FLOW_NODE_SIZE 80u
#define FLOW_LINK_SIZE 24u

static const u8 k_magic[8] = {'B', 'R', 'E', 'A', 'K', 'F', 'G', 0u};

static void put32(u8 *p, u32 v) {
    p[0] = (u8)v;
    p[1] = (u8)(v >> 8);
    p[2] = (u8)(v >> 16);
    p[3] = (u8)(v >> 24);
}

static u32 get32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) |
           ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static void put_float(u8 *p, f32 value) {
    u32 bits;
    memcpy(&bits, &value, sizeof(bits));
    put32(p, bits);
}

static f32 get_float(const u8 *p) {
    u32 bits = get32(p);
    f32 value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

static usize graph_size(const BreakFlowGraph *graph) {
    return FLOW_HEADER_SIZE + (usize)graph->node_count * FLOW_NODE_SIZE +
           (usize)graph->link_count * FLOW_LINK_SIZE;
}

BreakFlowError break_flow_serialized_size(const BreakFlowGraph *graph,
                                          usize *out_size) {
    if (!graph || !out_size) return BREAK_FLOW_INVALID;
    BreakFlowError valid = break_flow_graph_validate(graph);
    if (valid != BREAK_FLOW_OK) return valid;
    *out_size = graph_size(graph);
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_serialize(const BreakFlowGraph *graph, void *out,
                                    usize capacity, usize *out_written) {
    if (!graph || !out || !out_written) return BREAK_FLOW_INVALID;
    BreakFlowError valid = break_flow_graph_validate(graph);
    if (valid != BREAK_FLOW_OK) return valid;
    usize needed = graph_size(graph);
    if (capacity < needed) return BREAK_FLOW_OVERLOAD;
    u8 *bytes = (u8 *)out;
    memset(bytes, 0, needed);
    memcpy(bytes, k_magic, sizeof(k_magic));
    put32(bytes + 8u, BREAK_FLOW_SERIAL_VERSION);
    put32(bytes + 12u, FLOW_HEADER_SIZE);
    put32(bytes + 16u, (u32)needed);
    put32(bytes + 20u, graph->max_nodes);
    put32(bytes + 24u, graph->max_links);
    put32(bytes + 28u, graph->node_count);
    put32(bytes + 32u, graph->link_count);
    put32(bytes + 36u, graph->next_node_id);
    put32(bytes + 40u, graph->next_link_id);
    usize pos = FLOW_HEADER_SIZE;
    for (u32 i = 1u; i <= graph->max_nodes; i++) {
        if (!graph->nodes[i].used) continue;
        const BreakFlowNodeDesc *d = &graph->nodes[i].desc;
        u8 *record = bytes + pos;
        put32(record, i);
        put32(record + 4u, (u32)d->type);
        usize name_len = 0u;
        while (name_len < BREAK_FLOW_NAME_CAP && d->name[name_len] != '\0') name_len++;
        put32(record + 8u, (u32)name_len);
        memcpy(record + 12u, d->name, name_len);
        put32(record + 44u, d->event_key);
        put32(record + 48u, d->entity.index);
        put32(record + 52u, d->entity.generation);
        put32(record + 56u, d->item_id);
        put32(record + 60u, d->delay_ticks);
        put_float(record + 64u, d->a);
        put_float(record + 68u, d->b);
        put_float(record + 72u, d->c);
        pos += FLOW_NODE_SIZE;
    }
    for (u32 i = 1u; i <= graph->max_links; i++) {
        if (!graph->links[i].used) continue;
        const BreakFlowLinkDesc *d = &graph->links[i].desc;
        u8 *record = bytes + pos;
        put32(record, i);
        put32(record + 4u, (u32)d->kind);
        put32(record + 8u, d->source_node);
        put32(record + 12u, d->source_port);
        put32(record + 16u, d->target_node);
        put32(record + 20u, d->target_port);
        pos += FLOW_LINK_SIZE;
    }
    *out_written = pos;
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_deserialize(const void *input, usize length,
                                      BreakFlowGraph **out_graph) {
    if (!out_graph) return BREAK_FLOW_INVALID;
    *out_graph = NULL;
    if (!input || length < FLOW_HEADER_SIZE) return BREAK_FLOW_INVALID;
    const u8 *bytes = (const u8 *)input;
    if (memcmp(bytes, k_magic, sizeof(k_magic)) != 0 ||
        get32(bytes + 8u) != BREAK_FLOW_SERIAL_VERSION ||
        get32(bytes + 12u) != FLOW_HEADER_SIZE ||
        get32(bytes + 16u) != length || get32(bytes + 44u) != 0u) {
        return BREAK_FLOW_INVALID;
    }
    u32 max_nodes = get32(bytes + 20u);
    u32 max_links = get32(bytes + 24u);
    u32 node_count = get32(bytes + 28u);
    u32 link_count = get32(bytes + 32u);
    u32 next_node = get32(bytes + 36u);
    u32 next_link = get32(bytes + 40u);
    if (max_nodes == 0u || max_nodes > BREAK_FLOW_HARD_MAX_NODES ||
        max_links == 0u || max_links > BREAK_FLOW_HARD_MAX_LINKS ||
        node_count > max_nodes || link_count > max_links ||
        next_node == 0u || next_node > max_nodes + 1u ||
        next_link == 0u || next_link > max_links + 1u) {
        return BREAK_FLOW_INVALID;
    }
    u64 expected = FLOW_HEADER_SIZE + (u64)node_count * FLOW_NODE_SIZE +
                   (u64)link_count * FLOW_LINK_SIZE;
    if (expected != length) return BREAK_FLOW_INVALID;
    BreakFlowConfig cfg = {max_nodes, max_links};
    BreakFlowGraph *graph = break_flow_graph_create(&cfg);
    if (!graph) return BREAK_FLOW_OOM;
    usize pos = FLOW_HEADER_SIZE;
    u32 last_id = 0u;
    bool valid = true;
    for (u32 n = 0u; n < node_count && valid; n++) {
        const u8 *record = bytes + pos;
        u32 id = get32(record);
        u32 type = get32(record + 4u);
        u32 name_len = get32(record + 8u);
        if (id <= last_id || id > max_nodes || type < BREAK_FLOW_NODE_EVENT ||
            type > BREAK_FLOW_NODE_BRANCH || name_len == 0u ||
            name_len >= BREAK_FLOW_NAME_CAP || get32(record + 76u) != 0u) {
            valid = false;
            break;
        }
        BreakFlowNodeDesc d;
        memset(&d, 0, sizeof(d));
        d.type = (BreakFlowNodeType)type;
        for (u32 i = 0u; i < BREAK_FLOW_NAME_CAP; i++) {
            u8 ch = record[12u + i];
            if (i < name_len) {
                if (ch < 32u || ch > 126u) valid = false;
                d.name[i] = (char)ch;
            } else if (ch != 0u) {
                valid = false;
            }
        }
        if (!valid) break;
        d.event_key = get32(record + 44u);
        d.entity.index = get32(record + 48u);
        d.entity.generation = get32(record + 52u);
        d.item_id = get32(record + 56u);
        d.delay_ticks = get32(record + 60u);
        d.a = get_float(record + 64u);
        d.b = get_float(record + 68u);
        d.c = get_float(record + 72u);
        graph->nodes[id].used = true;
        graph->nodes[id].desc = d;
        graph->node_count++;
        last_id = id;
        pos += FLOW_NODE_SIZE;
    }
    last_id = 0u;
    for (u32 n = 0u; n < link_count && valid; n++) {
        const u8 *record = bytes + pos;
        u32 id = get32(record);
        u32 kind = get32(record + 4u);
        if (id <= last_id || id > max_links ||
            (kind != BREAK_FLOW_PORT_EXEC && kind != BREAK_FLOW_PORT_VALUE)) {
            valid = false;
            break;
        }
        BreakFlowLinkDesc d;
        d.kind = (BreakFlowPortKind)kind;
        d.source_node = get32(record + 8u);
        d.source_port = get32(record + 12u);
        d.target_node = get32(record + 16u);
        d.target_port = get32(record + 20u);
        graph->links[id].used = true;
        graph->links[id].desc = d;
        graph->link_count++;
        last_id = id;
        pos += FLOW_LINK_SIZE;
    }
    graph->next_node_id = next_node;
    graph->next_link_id = next_link;
    if (!valid || pos != length || break_flow_graph_validate(graph) != BREAK_FLOW_OK) {
        break_flow_graph_destroy(graph);
        return BREAK_FLOW_INVALID;
    }
    *out_graph = graph;
    return BREAK_FLOW_OK;
}
