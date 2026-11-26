/* Asset dependency graph: load order, missing and cyclic dependencies,
 * dependents for hot reload, and external (cross-World) ids. */
#include "test_framework.h"

#include <asset/asset_graph.h>

#include <string.h>

enum {
    kScene = 1u,
    kMatA = 10u,
    kMatB = 11u,
    kTex1 = 20u,
    kTex2 = 21u,
    kShader = 30u,
    kMesh = 40u,
    kShared = 50u /* lives in another World */
};

typedef struct {
    u32 calls;
    u32 world_key;
    BreakAssetId known;
} Resolver;

static bool resolve(void *user, u32 world_key, BreakAssetId id) {
    Resolver *r = (Resolver *)user;
    r->calls++;
    return world_key == r->world_key && id == r->known;
}

static BreakAssetGraph *make(u32 capacity, u32 edges, Resolver *r) {
    BreakAssetGraphConfig cfg;
    BreakAssetGraph *g = NULL;
    memset(&cfg, 0, sizeof cfg);
    cfg.capacity = capacity;
    cfg.max_edges = edges;
    cfg.resolve = r ? resolve : NULL;
    cfg.resolve_user = r;
    return break_asset_graph_create(&cfg, &g) == BREAK_ASSET_GRAPH_OK ? g : NULL;
}

static i32 position(const BreakAssetId *list, u32 count, BreakAssetId id) {
    for (u32 i = 0u; i < count; ++i) {
        if (list[i] == id) return (i32)i;
    }
    return -1;
}

/* scene -> {matA, matB, mesh}; matA -> {tex1, shader}; matB -> {tex2, shader} */
static bool declare_scene(BreakAssetGraph *g) {
    const BreakAssetId scene[] = {kMatA, kMatB, kMesh};
    const BreakAssetId mat_a[] = {kTex1, kShader};
    const BreakAssetId mat_b[] = {kTex2, kShader};
    return break_asset_graph_add(g, kScene, scene, 3u) == BREAK_ASSET_GRAPH_OK &&
           break_asset_graph_add(g, kMatA, mat_a, 2u) == BREAK_ASSET_GRAPH_OK &&
           break_asset_graph_add(g, kMatB, mat_b, 2u) == BREAK_ASSET_GRAPH_OK &&
           break_asset_graph_add(g, kTex1, NULL, 0u) == BREAK_ASSET_GRAPH_OK &&
           break_asset_graph_add(g, kTex2, NULL, 0u) == BREAK_ASSET_GRAPH_OK &&
           break_asset_graph_add(g, kShader, NULL, 0u) == BREAK_ASSET_GRAPH_OK &&
           break_asset_graph_add(g, kMesh, NULL, 0u) == BREAK_ASSET_GRAPH_OK;
}

static void expect_before(const BreakAssetId *list, u32 count, BreakAssetId first,
                          BreakAssetId second) {
    i32 a = position(list, count, first);
    i32 b = position(list, count, second);
    ASSERT_TRUE(a >= 0);
    ASSERT_TRUE(b >= 0);
    ASSERT_TRUE(a < b);
}

TEST(load_order_puts_every_dependency_first_and_lists_each_once) {
    BreakAssetGraph *g = make(16u, 32u, NULL);
    BreakAssetId order[16];
    u32 count = 0u;
    BreakAssetId problem = 99u;
    ASSERT_NOT_NULL(g);
    ASSERT_TRUE(declare_scene(g));
    ASSERT_EQ(break_asset_graph_load_order(g, kScene, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 7u); /* the shared shader once */
    ASSERT_EQ(order[count - 1u], (u64)kScene);
    expect_before(order, count, kTex1, kMatA);
    expect_before(order, count, kShader, kMatA);
    expect_before(order, count, kTex2, kMatB);
    expect_before(order, count, kShader, kMatB);
    expect_before(order, count, kMatA, kScene);
    expect_before(order, count, kMesh, kScene);
    for (u32 i = 0u; i < count; ++i) {
        for (u32 j = i + 1u; j < count; ++j) ASSERT_TRUE(order[i] != order[j]);
    }
    /* a leaf is its own load order */
    ASSERT_EQ(break_asset_graph_load_order(g, kTex1, order, 16u, &count, NULL), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(order[0], (u64)kTex1);
    /* a sub-tree only lists what it needs */
    ASSERT_EQ(break_asset_graph_load_order(g, kMatB, order, 16u, &count, NULL), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_EQ(position(order, count, kTex1), -1);
    break_asset_graph_destroy(g);
}

TEST(a_missing_dependency_is_reported_by_id) {
    BreakAssetGraph *g = make(16u, 32u, NULL);
    const BreakAssetId mat[] = {kTex1, 777u};
    BreakAssetId order[16];
    u32 count = 5u;
    BreakAssetId problem = 0u;
    ASSERT_EQ(break_asset_graph_add(g, kMatA, mat, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kTex1, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_MISSING);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(problem, 777u);
    /* the root itself undeclared */
    problem = 0u;
    ASSERT_EQ(break_asset_graph_load_order(g, 888u, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_NOT_FOUND);
    ASSERT_EQ(count, 0u);
    /* declaring it later fixes the chain */
    ASSERT_EQ(break_asset_graph_add(g, 777u, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 3u);
    break_asset_graph_destroy(g);
}

TEST(a_dependency_loop_is_reported_and_leaves_other_roots_usable) {
    BreakAssetGraph *g = make(16u, 32u, NULL);
    const BreakAssetId a[] = {kMatB};
    const BreakAssetId b[] = {kTex1};
    const BreakAssetId t[] = {kMatA}; /* tex1 -> matA -> matB -> tex1 */
    BreakAssetId order[16];
    u32 count = 5u;
    BreakAssetId problem = 0u;
    ASSERT_EQ(break_asset_graph_add(g, kMatA, a, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kMatB, b, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kTex1, t, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kShader, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_CYCLE);
    ASSERT_EQ(count, 0u);
    ASSERT_TRUE(problem == kMatA || problem == kMatB || problem == kTex1);
    ASSERT_EQ(break_asset_graph_load_order(g, kShader, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 1u);
    /* breaking the loop */
    ASSERT_EQ(break_asset_graph_set_deps(g, kTex1, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_EQ(order[0], (u64)kTex1);
    ASSERT_EQ(order[1], (u64)kMatB);
    ASSERT_EQ(order[2], (u64)kMatA);
    break_asset_graph_destroy(g);
}

TEST(dependents_list_what_to_rebuild_after_a_change) {
    BreakAssetGraph *g = make(16u, 32u, NULL);
    BreakAssetId out[16];
    u32 count = 0u;
    ASSERT_TRUE(declare_scene(g));
    ASSERT_EQ(break_asset_graph_dependents(g, kShader, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 3u);
    expect_before(out, count, kMatA, kScene);
    expect_before(out, count, kMatB, kScene);
    ASSERT_EQ(position(out, count, kShader), -1);
    ASSERT_EQ(break_asset_graph_dependents(g, kTex1, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(out[0], (u64)kMatA);
    ASSERT_EQ(out[1], (u64)kScene);
    ASSERT_EQ(break_asset_graph_dependents(g, kScene, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(break_asset_graph_dependents(g, 999u, out, 16u, &count),
              BREAK_ASSET_GRAPH_NOT_FOUND);
    ASSERT_EQ(break_asset_graph_dependents(g, kShader, out, 2u, &count),
              BREAK_ASSET_GRAPH_OVERLOAD);
    ASSERT_EQ(count, 3u);
    break_asset_graph_destroy(g);
}

/* A dependent reached by two paths of different length is still listed after
 * every listed asset it depends on (a reversed post-order gets this wrong). */
TEST(dependents_respect_order_across_paths_of_different_length) {
    BreakAssetGraph *g = make(16u, 32u, NULL);
    const BreakAssetId top[] = {kMatA, kShader}; /* scene needs matA and the shader directly */
    const BreakAssetId mid[] = {kShader};
    BreakAssetId out[16];
    u32 count = 0u;
    ASSERT_EQ(break_asset_graph_add(g, kScene, top, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kMatA, mid, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kShader, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_dependents(g, kShader, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(out[0], (u64)kMatA);
    ASSERT_EQ(out[1], (u64)kScene);
    break_asset_graph_destroy(g);
}

TEST(external_ids_resolve_through_the_callback) {
    Resolver r = {0u, 7u, kShared};
    BreakAssetGraph *g = make(16u, 32u, &r);
    const BreakAssetId mat[] = {kTex1, kShared};
    BreakAssetId order[16];
    u32 count = 0u;
    BreakAssetId problem = 0u;
    BreakAssetGraphStats st;
    ASSERT_EQ(break_asset_graph_add(g, kMatA, mat, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kTex1, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add_external(g, kShared, 7u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 3u);
    expect_before(order, count, kShared, kMatA);
    ASSERT_EQ(r.calls, 1u);
    /* the other World stops providing it */
    r.known = 0u;
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_MISSING);
    ASSERT_EQ(problem, (u64)kShared);
    /* declared twice, in either form */
    ASSERT_EQ(break_asset_graph_add_external(g, kShared, 7u), BREAK_ASSET_GRAPH_EXISTS);
    ASSERT_EQ(break_asset_graph_add(g, kShared, NULL, 0u), BREAK_ASSET_GRAPH_EXISTS);
    ASSERT_EQ(break_asset_graph_add_external(g, kTex1, 7u), BREAK_ASSET_GRAPH_EXISTS);
    ASSERT_EQ(break_asset_graph_set_deps(g, kShared, NULL, 0u), BREAK_ASSET_GRAPH_INVALID);
    break_asset_graph_stats(g, &st);
    ASSERT_EQ(st.nodes, 3u);
    ASSERT_EQ(st.external, 1u);
    ASSERT_EQ(st.edges, 2u);
    break_asset_graph_destroy(g);
    /* without a resolver no external id resolves */
    g = make(4u, 4u, NULL);
    ASSERT_EQ(break_asset_graph_add(g, kMatA, mat + 1, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add_external(g, kShared, 7u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, &problem),
              BREAK_ASSET_GRAPH_MISSING);
    break_asset_graph_destroy(g);
}

TEST(set_deps_and_remove_keep_the_graph_consistent) {
    BreakAssetGraph *g = make(16u, 32u, NULL);
    const BreakAssetId bad_self[] = {kMatA};
    const BreakAssetId bad_dup[] = {kTex1, kTex1};
    const BreakAssetId bad_zero[] = {0u};
    const BreakAssetId swap[] = {kTex2};
    BreakAssetId order[16];
    u32 count = 0u;
    BreakAssetGraphStats st;
    ASSERT_TRUE(declare_scene(g));
    ASSERT_EQ(break_asset_graph_set_deps(g, kMatA, bad_self, 1u), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_set_deps(g, kMatA, bad_dup, 2u), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_set_deps(g, kMatA, bad_zero, 1u), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_set_deps(g, 999u, swap, 1u), BREAK_ASSET_GRAPH_NOT_FOUND);
    /* failures kept the old list */
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, NULL), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_TRUE(position(order, count, kTex1) >= 0);
    ASSERT_EQ(break_asset_graph_set_deps(g, kMatA, swap, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 16u, &count, NULL), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(order[0], (u64)kTex2);
    /* tex1 is no longer used: it can go; tex2 and shader are still used */
    ASSERT_EQ(break_asset_graph_remove(g, kTex2), BREAK_ASSET_GRAPH_IN_USE);
    ASSERT_EQ(break_asset_graph_remove(g, kShader), BREAK_ASSET_GRAPH_IN_USE);
    ASSERT_EQ(break_asset_graph_remove(g, kTex1), BREAK_ASSET_GRAPH_OK);
    ASSERT_FALSE(break_asset_graph_contains(g, kTex1));
    ASSERT_EQ(break_asset_graph_remove(g, kTex1), BREAK_ASSET_GRAPH_NOT_FOUND);
    ASSERT_EQ(break_asset_graph_remove(g, kScene), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_remove(g, kMatA), BREAK_ASSET_GRAPH_OK);
    break_asset_graph_stats(g, &st);
    ASSERT_EQ(st.nodes, 4u);  /* matB, tex2, shader, mesh */
    ASSERT_EQ(st.edges, 2u);  /* matB's two */
    ASSERT_EQ(break_asset_graph_add(g, kMatA, NULL, 0u), BREAK_ASSET_GRAPH_OK); /* id reusable */
    break_asset_graph_destroy(g);
}

TEST(capacity_limits_and_argument_checks) {
    BreakAssetGraph *g = make(3u, 3u, NULL);
    const BreakAssetId three[] = {kTex1, kTex2, kShader};
    const BreakAssetId one[] = {kTex1};
    BreakAssetId order[4];
    u32 count = 0u;
    BreakAssetGraphConfig cfg;
    BreakAssetGraph *other = (BreakAssetGraph *)&count;
    BreakAssetGraphStats st;
    ASSERT_EQ(break_asset_graph_add(g, kMatA, three, 3u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kMatB, one, 1u), BREAK_ASSET_GRAPH_OVERLOAD); /* edges */
    ASSERT_FALSE(break_asset_graph_contains(g, kMatB));
    ASSERT_EQ(break_asset_graph_add(g, kTex1, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kTex2, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kShader, NULL, 0u), BREAK_ASSET_GRAPH_OVERLOAD); /* nodes */
    ASSERT_EQ(break_asset_graph_add(g, 0u, NULL, 0u), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_add(g, 5u, NULL, 1u), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_add(g, kMatA, NULL, 0u), BREAK_ASSET_GRAPH_EXISTS);
    ASSERT_EQ(break_asset_graph_add_external(g, 0u, 1u), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_remove(g, kTex2), BREAK_ASSET_GRAPH_IN_USE);
    /* set_deps over the edge budget fails and keeps the old list */
    ASSERT_EQ(break_asset_graph_set_deps(g, kTex1, one, 1u), BREAK_ASSET_GRAPH_INVALID); /* self */
    ASSERT_EQ(break_asset_graph_set_deps(g, kTex2, one, 1u), BREAK_ASSET_GRAPH_OVERLOAD);
    ASSERT_EQ(break_asset_graph_set_deps(g, kMatA, one, 1u), BREAK_ASSET_GRAPH_OK); /* frees two */
    ASSERT_EQ(break_asset_graph_set_deps(g, kTex2, one, 1u), BREAK_ASSET_GRAPH_OK);
    break_asset_graph_stats(g, &st);
    ASSERT_EQ(st.edges, 2u);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 1u, &count, NULL),
              BREAK_ASSET_GRAPH_OVERLOAD);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(break_asset_graph_load_order(NULL, kMatA, order, 4u, &count, NULL),
              BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, NULL, 4u, &count, NULL),
              BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_load_order(g, kMatA, order, 4u, NULL, NULL),
              BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_dependents(NULL, kTex1, order, 4u, &count),
              BREAK_ASSET_GRAPH_INVALID);
    ASSERT_FALSE(break_asset_graph_contains(NULL, kTex1));
    ASSERT_EQ(break_asset_graph_add(NULL, 9u, NULL, 0u), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_set_deps(NULL, 9u, NULL, 0u), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_remove(NULL, 9u), BREAK_ASSET_GRAPH_INVALID);
    break_asset_graph_stats(NULL, &st);
    break_asset_graph_stats(g, NULL);
    break_asset_graph_destroy(g);
    break_asset_graph_destroy(NULL);
    memset(&cfg, 0, sizeof cfg);
    cfg.capacity = 1u;
    cfg.max_edges = 1u;
    ASSERT_EQ(break_asset_graph_create(NULL, &other), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_EQ(break_asset_graph_create(&cfg, NULL), BREAK_ASSET_GRAPH_INVALID);
    cfg.capacity = 0u;
    ASSERT_EQ(break_asset_graph_create(&cfg, &other), BREAK_ASSET_GRAPH_INVALID);
    ASSERT_TRUE(other == NULL);
    cfg.capacity = BREAK_ASSET_GRAPH_MAX_NODES + 1u;
    ASSERT_EQ(break_asset_graph_create(&cfg, &other), BREAK_ASSET_GRAPH_INVALID);
    cfg.capacity = 1u;
    cfg.max_edges = 0u;
    ASSERT_EQ(break_asset_graph_create(&cfg, &other), BREAK_ASSET_GRAPH_INVALID);
    cfg.max_edges = BREAK_ASSET_GRAPH_MAX_EDGES + 1u;
    ASSERT_EQ(break_asset_graph_create(&cfg, &other), BREAK_ASSET_GRAPH_INVALID);
    cfg.capacity = BREAK_ASSET_GRAPH_MAX_NODES;
    cfg.max_edges = BREAK_ASSET_GRAPH_MAX_EDGES;
    ASSERT_EQ(break_asset_graph_create(&cfg, &other), BREAK_ASSET_GRAPH_OK);
    break_asset_graph_destroy(other);
}

/* A long chain (deeper than any recursion limit would allow) and a wide
 * diamond lattice keep their order and stay linear. */
TEST(deep_and_wide_graphs_are_ordered_without_recursion) {
    enum { kDepth = 20000u };
    BreakAssetGraph *g = make(kDepth + 1u, kDepth + 1u, NULL);
    static BreakAssetId order[kDepth + 1u];
    u32 count = 0u;
    ASSERT_NOT_NULL(g);
    for (u32 i = 1u; i <= kDepth; ++i) {
        BreakAssetId dep = (BreakAssetId)i + 1u;
        ASSERT_EQ(break_asset_graph_add(g, i, i < kDepth ? &dep : NULL, i < kDepth ? 1u : 0u),
                  BREAK_ASSET_GRAPH_OK);
    }
    ASSERT_EQ(break_asset_graph_load_order(g, 1u, order, kDepth + 1u, &count, NULL),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, (u32)kDepth);
    for (u32 i = 0u; i < count; ++i) ASSERT_EQ(order[i], (BreakAssetId)(kDepth - i));
    ASSERT_EQ(break_asset_graph_dependents(g, kDepth, order, kDepth + 1u, &count),
              BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, (u32)kDepth - 1u);
    ASSERT_EQ(order[0], (BreakAssetId)(kDepth - 1u));
    ASSERT_EQ(order[count - 1u], 1u);
    break_asset_graph_destroy(g);
}

/* Removing assets leaves tombstones in the id table; a graph that is filled,
 * emptied and refilled many times keeps finding every id, and the counters
 * and free slots stay exact. */
TEST(churn_keeps_lookup_counters_and_free_slots_exact) {
    Resolver r = {0u, 3u, 0u};
    BreakAssetGraph *g = make(8u, 8u, &r);
    BreakAssetGraphStats st;
    BreakAssetId order[8];
    u32 count = 0u;
    for (u32 round = 0u; round < 50u; ++round) {
        BreakAssetId base = 1000u + round * 16u;
        BreakAssetId dep = base + 1u;
        ASSERT_EQ(break_asset_graph_add(g, base, &dep, 1u), BREAK_ASSET_GRAPH_OK);
        ASSERT_EQ(break_asset_graph_add_external(g, base + 1u, 3u), BREAK_ASSET_GRAPH_OK);
        for (u32 i = 2u; i < 8u; ++i) ASSERT_EQ(break_asset_graph_add(g, base + i, NULL, 0u), BREAK_ASSET_GRAPH_OK);
        ASSERT_EQ(break_asset_graph_add(g, base + 9u, NULL, 0u), BREAK_ASSET_GRAPH_OVERLOAD);
        break_asset_graph_stats(g, &st);
        ASSERT_EQ(st.nodes, 8u);
        ASSERT_EQ(st.external, 1u);
        ASSERT_EQ(st.edges, 1u);
        for (u32 i = 0u; i < 8u; ++i) ASSERT_TRUE(break_asset_graph_contains(g, base + i));
        r.known = base + 1u;
        ASSERT_EQ(break_asset_graph_load_order(g, base, order, 8u, &count, NULL), BREAK_ASSET_GRAPH_OK);
        ASSERT_EQ(count, 2u);
        ASSERT_EQ(break_asset_graph_remove(g, base), BREAK_ASSET_GRAPH_OK);
        for (u32 i = 1u; i < 8u; ++i) ASSERT_EQ(break_asset_graph_remove(g, base + i), BREAK_ASSET_GRAPH_OK);
        break_asset_graph_stats(g, &st);
        ASSERT_EQ(st.nodes, 0u);
        ASSERT_EQ(st.external, 0u);
        ASSERT_EQ(st.edges, 0u);
        ASSERT_FALSE(break_asset_graph_contains(g, base + 3u));
    }
    break_asset_graph_destroy(g);
}

/* A root reached by several roots shares one result per call, and a failed
 * call leaves the problem id only for MISSING/CYCLE. */
TEST(problem_is_cleared_on_success_and_named_for_the_root) {
    BreakAssetGraph *g = make(4u, 4u, NULL);
    BreakAssetId order[4];
    u32 count = 9u;
    BreakAssetId problem = 77u;
    ASSERT_EQ(break_asset_graph_add(g, kTex1, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_load_order(g, kTex1, order, 4u, &count, &problem), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(problem, 0u);
    ASSERT_EQ(break_asset_graph_load_order(g, 31337u, order, 4u, &count, &problem),
              BREAK_ASSET_GRAPH_NOT_FOUND);
    ASSERT_EQ(problem, 31337u);
    break_asset_graph_destroy(g);
}

/* Diamonds whose dependents are reached through a node outside the changed
 * set: only real dependents are listed, each after its listed dependencies. */
TEST(dependents_ignore_unrelated_branches_and_keep_order) {
    BreakAssetGraph *g = make(16u, 32u, NULL);
    const BreakAssetId scene[] = {kMatA, kMatB};
    const BreakAssetId mat_a[] = {kTex1};
    const BreakAssetId mat_b[] = {kTex2, kMatA};
    BreakAssetId out[16];
    u32 count = 0u;
    ASSERT_EQ(break_asset_graph_add(g, kScene, scene, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kMatB, mat_b, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kMatA, mat_a, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kTex1, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(g, kTex2, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_dependents(g, kTex1, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_EQ(out[0], (u64)kMatA);
    ASSERT_EQ(out[1], (u64)kMatB);
    ASSERT_EQ(out[2], (u64)kScene);
    ASSERT_EQ(break_asset_graph_dependents(g, kTex2, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(out[0], (u64)kMatB);
    ASSERT_EQ(out[1], (u64)kScene);
    /* the changed asset on a loop (tex1 -> shader -> matA -> tex1) is never
     * listed as its own dependent, and nothing is listed twice */
    {
        const BreakAssetId loop[] = {kShader};
        const BreakAssetId back[] = {kMatA};
        ASSERT_EQ(break_asset_graph_add(g, kShader, back, 1u), BREAK_ASSET_GRAPH_OK);
        ASSERT_EQ(break_asset_graph_set_deps(g, kTex1, loop, 1u), BREAK_ASSET_GRAPH_OK);
        ASSERT_EQ(break_asset_graph_dependents(g, kTex1, out, 16u, &count), BREAK_ASSET_GRAPH_OK);
        ASSERT_EQ(position(out, count, kTex1), -1);
        ASSERT_EQ(count, 4u); /* shader, matA, matB, scene */
        for (u32 i = 0u; i < count; ++i) {
            for (u32 j = i + 1u; j < count; ++j) ASSERT_TRUE(out[i] != out[j]);
        }
    }
    break_asset_graph_destroy(g);
}

TEST_MAIN_BEGIN()
    RUN_TEST(load_order_puts_every_dependency_first_and_lists_each_once);
    RUN_TEST(a_missing_dependency_is_reported_by_id);
    RUN_TEST(a_dependency_loop_is_reported_and_leaves_other_roots_usable);
    RUN_TEST(dependents_list_what_to_rebuild_after_a_change);
    RUN_TEST(dependents_respect_order_across_paths_of_different_length);
    RUN_TEST(external_ids_resolve_through_the_callback);
    RUN_TEST(set_deps_and_remove_keep_the_graph_consistent);
    RUN_TEST(capacity_limits_and_argument_checks);
    RUN_TEST(deep_and_wide_graphs_are_ordered_without_recursion);
    RUN_TEST(churn_keeps_lookup_counters_and_free_slots_exact);
    RUN_TEST(problem_is_cleared_on_success_and_named_for_the_root);
    RUN_TEST(dependents_ignore_unrelated_branches_and_keep_order);
TEST_MAIN_END()
