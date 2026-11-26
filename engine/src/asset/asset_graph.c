#include "asset/asset_graph.h"

#include <stdlib.h>
#include <string.h>

/* Nodes live in a fixed array; an open-addressed table maps ids to node
 * slots. Each node's dependency list is a contiguous run in a per-node
 * allocation drawn from a shared edge budget. Traversals are iterative with
 * an explicit stack, so depth is bounded by capacity, not by the C stack. */

#define SLOT_EMPTY 0xffffffffu
#define SLOT_TOMB 0xfffffffeu

enum { MARK_NONE = 0, MARK_OPEN = 1, MARK_DONE = 2 };

typedef struct {
    BreakAssetId id;
    BreakAssetId *deps;
    u32 dep_count;
    u32 world_key;
    bool used;
    bool external;
} Node;

typedef struct {
    u32 node;
    u32 next; /* next dependency (or dependent scan position) to visit */
} Frame;

struct BreakAssetGraph {
    u32 capacity;
    u32 max_edges;
    u32 edges;
    u32 nodes_used;
    u32 external;
    BreakAssetGraphResolveFn resolve;
    void *resolve_user;
    Node *nodes;
    u32 *table; /* table_size entries: node index, SLOT_EMPTY or SLOT_TOMB */
    u32 table_size;
    u32 *free_nodes;
    u32 free_count;
    u8 *marks;   /* per node, traversal scratch */
    Frame *stack;
    /* reverse edges for break_asset_graph_dependents, rebuilt per call:
     * the dependents of node i are rev[rev_start[i] .. rev_start[i + 1]) */
    u32 *rev_start; /* capacity + 1 */
    u32 *rev;       /* max_edges */
};

static u32 hash_id(BreakAssetId id) {
    id ^= id >> 33;
    id *= 0xff51afd7ed558ccdull;
    id ^= id >> 33;
    return (u32)id;
}

/* The table slot holding `id`, or SLOT_EMPTY. */
static u32 lookup(const BreakAssetGraph *g, BreakAssetId id) {
    u32 mask = g->table_size - 1u;
    u32 at = hash_id(id) & mask;
    for (u32 probe = 0u; probe < g->table_size; ++probe) {
        u32 entry = g->table[at];
        if (entry == SLOT_EMPTY) return SLOT_EMPTY;
        if (entry != SLOT_TOMB && g->nodes[entry].id == id) return at;
        at = (at + 1u) & mask;
    }
    return SLOT_EMPTY;
}

static Node *find(const BreakAssetGraph *g, BreakAssetId id) {
    u32 at = lookup(g, id);
    return at == SLOT_EMPTY ? NULL : &g->nodes[g->table[at]];
}

static void table_insert(BreakAssetGraph *g, BreakAssetId id, u32 node) {
    u32 mask = g->table_size - 1u;
    u32 at = hash_id(id) & mask;
    while (g->table[at] != SLOT_EMPTY && g->table[at] != SLOT_TOMB) at = (at + 1u) & mask;
    g->table[at] = node;
}

BreakAssetGraphResult break_asset_graph_create(const BreakAssetGraphConfig *config,
                                               BreakAssetGraph **out) {
    BreakAssetGraph *g;
    u32 table_size = 1u;
    if (out) *out = NULL;
    if (!config || !out || config->capacity == 0u ||
        config->capacity > BREAK_ASSET_GRAPH_MAX_NODES || config->max_edges == 0u ||
        config->max_edges > BREAK_ASSET_GRAPH_MAX_EDGES) {
        return BREAK_ASSET_GRAPH_INVALID;
    }
    while (table_size < config->capacity * 2u) table_size <<= 1u;
    g = (BreakAssetGraph *)calloc(1u, sizeof(*g));
    if (!g) return BREAK_ASSET_GRAPH_OVERLOAD;
    g->nodes = (Node *)calloc(config->capacity, sizeof(*g->nodes));
    g->table = (u32 *)malloc(table_size * sizeof(*g->table));
    g->free_nodes = (u32 *)malloc(config->capacity * sizeof(*g->free_nodes));
    g->marks = (u8 *)calloc(config->capacity, sizeof(*g->marks));
    g->stack = (Frame *)malloc(config->capacity * sizeof(*g->stack));
    g->rev_start = (u32 *)malloc((config->capacity + 1u) * sizeof(*g->rev_start));
    g->rev = (u32 *)malloc(config->max_edges * sizeof(*g->rev));
    if (!g->nodes || !g->table || !g->free_nodes || !g->marks || !g->stack || !g->rev_start ||
        !g->rev) {
        break_asset_graph_destroy(g);
        return BREAK_ASSET_GRAPH_OVERLOAD;
    }
    memset(g->table, 0xff, table_size * sizeof(*g->table));
    for (u32 i = 0u; i < config->capacity; ++i) g->free_nodes[i] = config->capacity - 1u - i;
    g->free_count = config->capacity;
    g->table_size = table_size;
    g->capacity = config->capacity;
    g->max_edges = config->max_edges;
    g->resolve = config->resolve;
    g->resolve_user = config->resolve_user;
    *out = g;
    return BREAK_ASSET_GRAPH_OK;
}

void break_asset_graph_destroy(BreakAssetGraph *graph) {
    if (!graph) return;
    if (graph->nodes) {
        for (u32 i = 0u; i < graph->capacity; ++i) free(graph->nodes[i].deps);
    }
    free(graph->nodes);
    free(graph->table);
    free(graph->free_nodes);
    free(graph->marks);
    free(graph->stack);
    free(graph->rev_start);
    free(graph->rev);
    free(graph);
}

static bool deps_valid(BreakAssetId id, const BreakAssetId *deps, u32 dep_count) {
    if (dep_count != 0u && !deps) return false;
    for (u32 i = 0u; i < dep_count; ++i) {
        if (deps[i] == 0u || deps[i] == id) return false;
        for (u32 j = 0u; j < i; ++j) {
            if (deps[j] == deps[i]) return false;
        }
    }
    return true;
}

static BreakAssetGraphResult declare(BreakAssetGraph *g, BreakAssetId id,
                                     const BreakAssetId *deps, u32 dep_count, bool external,
                                     u32 world_key) {
    Node *node;
    u32 slot;
    BreakAssetId *copy = NULL;
    if (!g || id == 0u || !deps_valid(id, deps, dep_count)) return BREAK_ASSET_GRAPH_INVALID;
    if (find(g, id)) return BREAK_ASSET_GRAPH_EXISTS;
    if (g->free_count == 0u || dep_count > g->max_edges - g->edges) return BREAK_ASSET_GRAPH_OVERLOAD;
    if (dep_count != 0u) {
        copy = (BreakAssetId *)malloc(dep_count * sizeof(*copy));
        if (!copy) return BREAK_ASSET_GRAPH_OVERLOAD;
        memcpy(copy, deps, dep_count * sizeof(*copy));
    }
    slot = g->free_nodes[--g->free_count];
    node = &g->nodes[slot];
    node->id = id;
    node->deps = copy;
    node->dep_count = dep_count;
    node->external = external;
    node->world_key = world_key;
    node->used = true;
    table_insert(g, id, slot);
    g->nodes_used++;
    g->edges += dep_count;
    if (external) g->external++;
    return BREAK_ASSET_GRAPH_OK;
}

BreakAssetGraphResult break_asset_graph_add(BreakAssetGraph *graph, BreakAssetId id,
                                            const BreakAssetId *deps, u32 dep_count) {
    return declare(graph, id, deps, dep_count, false, 0u);
}

BreakAssetGraphResult break_asset_graph_add_external(BreakAssetGraph *graph, BreakAssetId id,
                                                     u32 world_key) {
    return declare(graph, id, NULL, 0u, true, world_key);
}

BreakAssetGraphResult break_asset_graph_set_deps(BreakAssetGraph *graph, BreakAssetId id,
                                                 const BreakAssetId *deps, u32 dep_count) {
    Node *node;
    BreakAssetId *copy = NULL;
    if (!graph || id == 0u || !deps_valid(id, deps, dep_count)) return BREAK_ASSET_GRAPH_INVALID;
    node = find(graph, id);
    if (!node) return BREAK_ASSET_GRAPH_NOT_FOUND;
    if (node->external) return BREAK_ASSET_GRAPH_INVALID;
    if (dep_count > graph->max_edges - (graph->edges - node->dep_count))
        return BREAK_ASSET_GRAPH_OVERLOAD;
    if (dep_count != 0u) {
        copy = (BreakAssetId *)malloc(dep_count * sizeof(*copy));
        if (!copy) return BREAK_ASSET_GRAPH_OVERLOAD;
        memcpy(copy, deps, dep_count * sizeof(*copy));
    }
    graph->edges = graph->edges - node->dep_count + dep_count;
    free(node->deps);
    node->deps = copy;
    node->dep_count = dep_count;
    return BREAK_ASSET_GRAPH_OK;
}

static bool depends_on(const Node *node, BreakAssetId id) {
    for (u32 i = 0u; i < node->dep_count; ++i) {
        if (node->deps[i] == id) return true;
    }
    return false;
}

BreakAssetGraphResult break_asset_graph_remove(BreakAssetGraph *graph, BreakAssetId id) {
    u32 at;
    Node *node;
    if (!graph) return BREAK_ASSET_GRAPH_INVALID;
    at = lookup(graph, id);
    if (at == SLOT_EMPTY) return BREAK_ASSET_GRAPH_NOT_FOUND;
    for (u32 i = 0u; i < graph->capacity; ++i) {
        if (graph->nodes[i].used && depends_on(&graph->nodes[i], id)) return BREAK_ASSET_GRAPH_IN_USE;
    }
    node = &graph->nodes[graph->table[at]];
    graph->edges -= node->dep_count;
    graph->nodes_used--;
    if (node->external) graph->external--;
    free(node->deps);
    graph->free_nodes[graph->free_count++] = graph->table[at];
    memset(node, 0, sizeof(*node));
    graph->table[at] = SLOT_TOMB;
    return BREAK_ASSET_GRAPH_OK;
}

bool break_asset_graph_contains(const BreakAssetGraph *graph, BreakAssetId id) {
    return graph && find(graph, id) != NULL;
}

static u32 node_index(const BreakAssetGraph *g, const Node *node) {
    return (u32)(node - g->nodes);
}

BreakAssetGraphResult break_asset_graph_load_order(const BreakAssetGraph *graph,
                                                   BreakAssetId root, BreakAssetId *out,
                                                   u32 capacity, u32 *out_count,
                                                   BreakAssetId *out_problem) {
    BreakAssetGraph *g = (BreakAssetGraph *)graph;
    BreakAssetGraphResult result = BREAK_ASSET_GRAPH_OK;
    const Node *start;
    u32 depth = 0u;
    u32 count = 0u;
    if (out_count) *out_count = 0u;
    if (out_problem) *out_problem = 0u;
    if (!g || !out || !out_count) return BREAK_ASSET_GRAPH_INVALID;
    start = find(g, root);
    if (!start) {
        if (out_problem) *out_problem = root;
        return BREAK_ASSET_GRAPH_NOT_FOUND;
    }
    memset(g->marks, MARK_NONE, g->capacity);
    g->stack[depth].node = node_index(g, start);
    g->stack[depth].next = 0u;
    g->marks[g->stack[depth].node] = MARK_OPEN;
    depth++;
    while (depth != 0u && result == BREAK_ASSET_GRAPH_OK) {
        Frame *top = &g->stack[depth - 1u];
        Node *node = &g->nodes[top->node];
        if (node->external) {
            if (!g->resolve || !g->resolve(g->resolve_user, node->world_key, node->id)) {
                if (out_problem) *out_problem = node->id;
                result = BREAK_ASSET_GRAPH_MISSING;
                break;
            }
        } else if (top->next < node->dep_count) {
            BreakAssetId dep = node->deps[top->next++];
            Node *child = find(g, dep);
            u32 index;
            if (!child) {
                if (out_problem) *out_problem = dep;
                result = BREAK_ASSET_GRAPH_MISSING;
                break;
            }
            index = node_index(g, child);
            if (g->marks[index] == MARK_OPEN) {
                if (out_problem) *out_problem = dep;
                result = BREAK_ASSET_GRAPH_CYCLE;
                break;
            }
            if (g->marks[index] == MARK_NONE) {
                g->marks[index] = MARK_OPEN;
                g->stack[depth].node = index;
                g->stack[depth].next = 0u;
                depth++;
            }
            continue;
        }
        g->marks[top->node] = MARK_DONE;
        if (count < capacity) out[count] = node->id;
        count++;
        depth--;
    }
    if (result != BREAK_ASSET_GRAPH_OK) return result;
    *out_count = count;
    return count > capacity ? BREAK_ASSET_GRAPH_OVERLOAD : BREAK_ASSET_GRAPH_OK;
}

/* Two passes. First, mark every node that reaches `changed` (a breadth
 * search over reverse edges, using the frame stack as a queue). Then emit
 * the marked nodes in dependency order: a post-order walk over forward
 * edges restricted to the marked set lists a node after all of its marked
 * dependencies. */
BreakAssetGraphResult break_asset_graph_dependents(const BreakAssetGraph *graph,
                                                   BreakAssetId changed, BreakAssetId *out,
                                                   u32 capacity, u32 *out_count) {
    enum { MARK_IN_SET = 3, MARK_EMITTED = 4, MARK_WALKING = 5 };
    BreakAssetGraph *g = (BreakAssetGraph *)graph;
    const Node *start;
    u32 head = 0u;
    u32 tail = 0u;
    u32 count = 0u;
    u32 origin;
    if (out_count) *out_count = 0u;
    if (!g || !out || !out_count) return BREAK_ASSET_GRAPH_INVALID;
    start = find(g, changed);
    if (!start) return BREAK_ASSET_GRAPH_NOT_FOUND;
    origin = node_index(g, start);
    /* counting sort of the forward edges by their target */
    memset(g->rev_start, 0, (g->capacity + 1u) * sizeof(*g->rev_start));
    for (u32 i = 0u; i < g->capacity; ++i) {
        const Node *node = &g->nodes[i];
        for (u32 d = 0u; node->used && d < node->dep_count; ++d) {
            const Node *target = find(g, node->deps[d]);
            if (target) g->rev_start[node_index(g, target) + 1u]++;
        }
    }
    for (u32 i = 0u; i < g->capacity; ++i) g->rev_start[i + 1u] += g->rev_start[i];
    for (u32 i = 0u; i < g->capacity; ++i) g->stack[i].next = g->rev_start[i];
    for (u32 i = 0u; i < g->capacity; ++i) {
        const Node *node = &g->nodes[i];
        for (u32 d = 0u; node->used && d < node->dep_count; ++d) {
            const Node *target = find(g, node->deps[d]);
            if (target) g->rev[g->stack[node_index(g, target)].next++] = i;
        }
    }
    memset(g->marks, MARK_NONE, g->capacity);
    g->marks[origin] = MARK_EMITTED; /* never listed, never walked into */
    g->stack[tail++].node = origin;
    while (head != tail) {
        u32 at = g->stack[head++].node;
        for (u32 r = g->rev_start[at]; r < g->rev_start[at + 1u]; ++r) {
            u32 i = g->rev[r];
            if (g->marks[i] != MARK_NONE) continue;
            g->marks[i] = MARK_IN_SET;
            g->stack[tail++].node = i;
        }
    }
    for (u32 root = 0u; root < g->capacity; ++root) {
        u32 depth = 0u;
        if (g->marks[root] != MARK_IN_SET) continue;
        g->marks[root] = MARK_WALKING;
        g->stack[0].node = root;
        g->stack[0].next = 0u;
        depth = 1u;
        while (depth != 0u) {
            Frame *top = &g->stack[depth - 1u];
            Node *node = &g->nodes[top->node];
            if (top->next < node->dep_count) {
                Node *child = find(g, node->deps[top->next++]);
                u32 index;
                if (!child) continue;
                index = node_index(g, child);
                if (g->marks[index] != MARK_IN_SET) continue; /* outside the set, done, or on the path */
                g->marks[index] = MARK_WALKING;
                g->stack[depth].node = index;
                g->stack[depth].next = 0u;
                depth++;
                continue;
            }
            g->marks[top->node] = MARK_EMITTED;
            if (count < capacity) out[count] = node->id;
            count++;
            depth--;
        }
    }
    *out_count = count;
    return count > capacity ? BREAK_ASSET_GRAPH_OVERLOAD : BREAK_ASSET_GRAPH_OK;
}

void break_asset_graph_stats(const BreakAssetGraph *graph, BreakAssetGraphStats *out) {
    if (!graph || !out) return;
    out->nodes = graph->nodes_used;
    out->external = graph->external;
    out->edges = graph->edges;
}
