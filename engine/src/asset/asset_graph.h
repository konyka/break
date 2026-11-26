#pragma once
/* Asset dependency graph.
 *
 * Each asset is a node named by its content id (u64, non-zero) and lists the
 * assets it needs, for example a material its textures and shaders, a scene
 * its meshes and materials. The graph answers the three questions an asset
 * chain needs:
 *
 *  - load order: break_asset_graph_load_order lists everything a root needs,
 *    dependencies before dependents, each asset once;
 *  - integrity: a dependency on an id that was never declared is MISSING, a
 *    dependency loop is CYCLE, both reported with the offending ids;
 *  - invalidation: break_asset_graph_dependents lists every asset that
 *    (directly or transitively) depends on a changed one, so a hot reload
 *    rebuilds exactly those, dependencies first.
 *
 * An id may also be marked external: it belongs to another World or package
 * (cross-World asset dependency) and is resolved through a callback instead
 * of being declared here. An external id that the callback cannot resolve
 * is MISSING.
 *
 * Bounded (capacity nodes, max_edges dependencies in total), allocation at
 * create only, not thread-safe: one owner. Design:
 * docs/design/runtime_asset_streaming.md "资产依赖图". */
#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef u64 BreakAssetId; /* 0 = none */

#define BREAK_ASSET_GRAPH_MAX_NODES 65536u
#define BREAK_ASSET_GRAPH_MAX_EDGES (1u << 20)

typedef enum BreakAssetGraphResult {
    BREAK_ASSET_GRAPH_OK = 0,
    BREAK_ASSET_GRAPH_INVALID,   /* bad argument, id 0, self dependency, duplicate dependency */
    BREAK_ASSET_GRAPH_EXISTS,    /* the id is already declared */
    BREAK_ASSET_GRAPH_NOT_FOUND, /* the id is not declared */
    BREAK_ASSET_GRAPH_MISSING,   /* a reachable dependency is neither declared nor resolvable */
    BREAK_ASSET_GRAPH_CYCLE,     /* a reachable dependency loop */
    BREAK_ASSET_GRAPH_OVERLOAD,  /* node or edge capacity, or the output buffer, is too small */
    BREAK_ASSET_GRAPH_IN_USE     /* remove: other assets still depend on it */
} BreakAssetGraphResult;

/* Resolves an external id (see break_asset_graph_add_external). Returns
 * true when the other World or package provides it. */
typedef bool (*BreakAssetGraphResolveFn)(void *user, u32 world_key, BreakAssetId id);

typedef struct BreakAssetGraphConfig {
    u32 capacity;  /* nodes, 1..BREAK_ASSET_GRAPH_MAX_NODES */
    u32 max_edges; /* dependencies in total, 1..BREAK_ASSET_GRAPH_MAX_EDGES */
    BreakAssetGraphResolveFn resolve; /* may be NULL: no external id resolves */
    void *resolve_user;
} BreakAssetGraphConfig;

typedef struct BreakAssetGraph BreakAssetGraph;

BreakAssetGraphResult break_asset_graph_create(const BreakAssetGraphConfig *config,
                                               BreakAssetGraph **out);
void break_asset_graph_destroy(BreakAssetGraph *graph);

/* Declares `id` with its dependencies (which need not be declared yet).
 * INVALID for id 0, a dependency of 0, on itself, or listed twice. */
BreakAssetGraphResult break_asset_graph_add(BreakAssetGraph *graph, BreakAssetId id,
                                            const BreakAssetId *deps, u32 dep_count);
/* Declares `id` as provided by World or package `world_key`; it has no
 * dependencies of its own here. */
BreakAssetGraphResult break_asset_graph_add_external(BreakAssetGraph *graph, BreakAssetId id,
                                                     u32 world_key);
/* Replaces the dependency list of a declared asset (an edited material).
 * On any failure the old list is kept. */
BreakAssetGraphResult break_asset_graph_set_deps(BreakAssetGraph *graph, BreakAssetId id,
                                                 const BreakAssetId *deps, u32 dep_count);
/* Removes a declared asset. IN_USE while another declared asset lists it. */
BreakAssetGraphResult break_asset_graph_remove(BreakAssetGraph *graph, BreakAssetId id);
bool break_asset_graph_contains(const BreakAssetGraph *graph, BreakAssetId id);

/* Everything `root` needs, root last, dependencies before dependents, each
 * once. On MISSING or CYCLE *out_count is 0 and *out_problem (may be NULL)
 * is the missing id or an id on the loop. OVERLOAD when `capacity` is too
 * small; *out_count is then the size needed. External ids are listed (the
 * caller loads them from their World) but not expanded. */
BreakAssetGraphResult break_asset_graph_load_order(const BreakAssetGraph *graph,
                                                   BreakAssetId root, BreakAssetId *out,
                                                   u32 capacity, u32 *out_count,
                                                   BreakAssetId *out_problem);

/* Every declared asset that depends on `changed`, directly or not, in an
 * order that rebuilds dependencies before dependents (each one after every
 * listed asset it depends on); `changed` itself is not listed. A loop among
 * the dependents is broken arbitrarily, since load_order reports it.
 * OVERLOAD like load_order. */
BreakAssetGraphResult break_asset_graph_dependents(const BreakAssetGraph *graph,
                                                   BreakAssetId changed, BreakAssetId *out,
                                                   u32 capacity, u32 *out_count);

typedef struct BreakAssetGraphStats {
    u32 nodes;
    u32 external;
    u32 edges;
} BreakAssetGraphStats;

void break_asset_graph_stats(const BreakAssetGraph *graph, BreakAssetGraphStats *out);

#ifdef __cplusplus
}
#endif
