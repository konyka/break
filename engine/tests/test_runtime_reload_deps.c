/* Dependency-driven hot reload: after a changed asset commits, everything
 * that depends on it is reloaded through the real coordinator, dependencies
 * first and one at a time; a failed dependent keeps its old version and
 * stops what depends on it. */
#include "test_framework.h"
#include <asset/vfs.h>
#include <core/platform_thread.h>
#include <runtime/runtime_reload_deps.h>

#include <stdio.h>
#include <string.h>
#if !defined(_WIN32)
#include <sys/stat.h>
#include <sys/types.h>
#endif

enum { kScene = 1u, kMatA = 10u, kMatB = 11u, kTex = 20u, kShader = 30u, kOther = 40u };

static char g_dir[512];
static const char *const k_files[] = {"scene.bin", "mat_a.bin", "mat_b.bin", "tex.bin",
                                      "shader.bin", "other.bin", "bad_mat.bin"};

typedef struct {
    char order[16][32]; /* committed paths, in commit order */
    u32 count;
    u32 validated;
} Probe;

static Probe g_probe;
/* when set, the commit hook forwards each commit, like an owner would */
static BreakRuntimeReloadDeps *g_hook_deps;
static BreakRuntimeError g_hook_result;

static BreakRuntimeError probe_validate(const char *path, const void *bytes, usize size,
                                        void *user) {
    (void)bytes;
    (void)size;
    (void)user;
    g_probe.validated++;
    return strstr(path, "bad") ? BREAK_RUNTIME_FAILED : BREAK_RUNTIME_OK;
}

static BreakRuntimeError probe_commit(const char *path, const void *bytes, usize size,
                                      void *user) {
    (void)bytes;
    (void)size;
    (void)user;
    if (g_probe.count < 16u) {
        snprintf(g_probe.order[g_probe.count], sizeof(g_probe.order[0]), "%s", path);
        g_probe.count++;
    }
    if (g_hook_deps) g_hook_result = break_runtime_reload_deps_committed_path(g_hook_deps, path);
    return BREAK_RUNTIME_OK;
}

static VFS *fixture_setup(void) {
    VFS *vfs;
    test_tmp(g_dir, sizeof(g_dir), "rtreload_deps");
    TEST_MKDIR(g_dir);
    for (usize i = 0; i < sizeof(k_files) / sizeof(k_files[0]); ++i) {
        char file[640];
        FILE *fp;
        snprintf(file, sizeof(file), "%s/%s", g_dir, k_files[i]);
        fp = fopen(file, "wb");
        if (!fp) return NULL;
        fputs("asset", fp);
        fclose(fp);
    }
    vfs = vfs_create();
    if (!vfs || !vfs_mount_dir(vfs, g_dir)) return NULL;
    return vfs;
}

static void fixture_remove(void) {
    for (usize i = 0; i < sizeof(k_files) / sizeof(k_files[0]); ++i) {
        char file[640];
        snprintf(file, sizeof(file), "%s/%s", g_dir, k_files[i]);
        (void)remove(file);
    }
    (void)TEST_RMDIR(g_dir);
}

typedef struct {
    VFS *vfs;
    BreakRuntimeReload *reload;
    BreakAssetGraph *graph;
    BreakRuntimeReloadDeps *deps;
} Fx;

/* scene -> {matA, matB}; matA -> {tex, shader}; matB -> {shader}; other alone */
static u32 g_request_capacity; /* 0: the coordinator default */

static bool fx_init(Fx *fx, u32 max_assets) {
    BreakRuntimeReloadConfig rc;
    BreakAssetGraphConfig gc;
    BreakRuntimeReloadDepsConfig dc;
    const BreakAssetId scene[] = {kMatA, kMatB};
    const BreakAssetId mat_a[] = {kTex, kShader};
    const BreakAssetId mat_b[] = {kShader};
    memset(fx, 0, sizeof(*fx));
    memset(&g_probe, 0, sizeof(g_probe));
    fx->vfs = fixture_setup();
    if (!fx->vfs) return false;
    memset(&rc, 0, sizeof(rc));
    rc.vfs = fx->vfs;
    rc.hooks.validate = probe_validate;
    rc.hooks.commit = probe_commit;
    rc.request_capacity = g_request_capacity;
    if (break_runtime_reload_create(&rc, &fx->reload) != BREAK_RUNTIME_OK) return false;
    memset(&gc, 0, sizeof(gc));
    gc.capacity = 16u;
    gc.max_edges = 16u;
    if (break_asset_graph_create(&gc, &fx->graph) != BREAK_ASSET_GRAPH_OK ||
        break_asset_graph_add(fx->graph, kScene, scene, 2u) != BREAK_ASSET_GRAPH_OK ||
        break_asset_graph_add(fx->graph, kMatA, mat_a, 2u) != BREAK_ASSET_GRAPH_OK ||
        break_asset_graph_add(fx->graph, kMatB, mat_b, 1u) != BREAK_ASSET_GRAPH_OK ||
        break_asset_graph_add(fx->graph, kTex, NULL, 0u) != BREAK_ASSET_GRAPH_OK ||
        break_asset_graph_add(fx->graph, kShader, NULL, 0u) != BREAK_ASSET_GRAPH_OK ||
        break_asset_graph_add(fx->graph, kOther, NULL, 0u) != BREAK_ASSET_GRAPH_OK) {
        return false;
    }
    memset(&dc, 0, sizeof(dc));
    dc.reload = fx->reload;
    dc.graph = fx->graph;
    dc.max_assets = max_assets;
    if (break_runtime_reload_deps_create(&dc, &fx->deps) != BREAK_RUNTIME_OK) return false;
    return break_runtime_reload_deps_set_path(fx->deps, kScene, "scene.bin") == BREAK_RUNTIME_OK &&
           break_runtime_reload_deps_set_path(fx->deps, kMatA, "mat_a.bin") == BREAK_RUNTIME_OK &&
           break_runtime_reload_deps_set_path(fx->deps, kMatB, "mat_b.bin") == BREAK_RUNTIME_OK &&
           break_runtime_reload_deps_set_path(fx->deps, kTex, "tex.bin") == BREAK_RUNTIME_OK &&
           break_runtime_reload_deps_set_path(fx->deps, kShader, "shader.bin") == BREAK_RUNTIME_OK &&
           break_runtime_reload_deps_set_path(fx->deps, kOther, "other.bin") == BREAK_RUNTIME_OK;
}

static void fx_dispose(Fx *fx) {
    g_hook_deps = NULL;
    break_runtime_reload_deps_destroy(fx->deps);
    if (fx->reload) {
        (void)break_runtime_reload_shutdown(fx->reload, 2000u);
        break_runtime_reload_destroy(fx->reload);
    }
    break_asset_graph_destroy(fx->graph);
    if (fx->vfs) vfs_destroy(fx->vfs);
    fixture_remove();
}

/* Drives the coordinator and the chain until nothing is queued or in flight. */
static bool run_until_idle(Fx *fx) {
    for (u32 spin = 0u; spin < 200000u; ++spin) {
        BreakRuntimeReloadDepsStats st;
        u32 commits = 0u;
        (void)break_runtime_reload_commit_owner(fx->reload, 16u, &commits);
        if (break_runtime_reload_deps_pump(fx->deps) != BREAK_RUNTIME_OK) return false;
        if (break_runtime_reload_deps_stats(fx->deps, &st) != BREAK_RUNTIME_OK) return false;
        if (st.queued == 0u && !st.in_flight) return true;
        platform_thread_yield();
    }
    return false;
}

static i32 committed_at(const char *path) {
    for (u32 i = 0u; i < g_probe.count; ++i) {
        if (strcmp(g_probe.order[i], path) == 0) return (i32)i;
    }
    return -1;
}

TEST(a_changed_texture_rebuilds_its_material_then_the_scene) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 2u);
    ASSERT_STR_EQ(g_probe.order[0], "mat_a.bin");
    ASSERT_STR_EQ(g_probe.order[1], "scene.bin");
    ASSERT_EQ(committed_at("mat_b.bin"), -1);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.chains, 1u);
    ASSERT_EQ(st.requested, 2u);
    ASSERT_EQ(st.rebuilt, 2u);
    ASSERT_EQ(st.failed, 0u);
    fx_dispose(&fx);
}

TEST(a_shared_dependency_rebuilds_each_dependent_once_in_order) {
    Fx fx;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 3u);
    ASSERT_TRUE(committed_at("mat_a.bin") >= 0);
    ASSERT_TRUE(committed_at("mat_b.bin") >= 0);
    ASSERT_EQ(committed_at("scene.bin"), 2);
    fx_dispose(&fx);
}

TEST(a_failed_dependent_keeps_its_old_version_and_stops_what_needs_it) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    /* matB now loads from a file the validator refuses */
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatB, "bad_mat.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_TRUE(committed_at("mat_a.bin") >= 0);
    ASSERT_EQ(committed_at("bad_mat.bin"), -1);
    ASSERT_EQ(committed_at("scene.bin"), -1); /* it needs the failed matB */
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.failed, 1u);
    ASSERT_EQ(st.skipped, 1u);
    ASSERT_EQ(st.rebuilt, 1u);
    fx_dispose(&fx);
}

TEST(only_one_dependent_is_in_flight_at_a_time) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    BreakRuntimeReloadStats rs;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_pump(fx.deps), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_pump(fx.deps), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_TRUE(st.in_flight);
    ASSERT_EQ(st.requested, 1u);
    ASSERT_EQ(st.queued, 2u);
    ASSERT_EQ(break_runtime_reload_stats(fx.reload, &rs), BREAK_RUNTIME_OK);
    ASSERT_EQ(rs.requested, 1u);
    ASSERT_TRUE(run_until_idle(&fx));
    fx_dispose(&fx);
}

TEST(a_new_commit_during_a_chain_merges_without_duplicates) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_pump(fx.deps), BREAK_RUNTIME_OK); /* matA in flight */
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    /* matA (in flight, then again since the shader changed after it started),
     * matB, scene once at the end */
    ASSERT_EQ(committed_at("scene.bin"), (i32)g_probe.count - 1);
    ASSERT_TRUE(committed_at("mat_b.bin") >= 0);
    for (u32 i = 0u; i + 1u < g_probe.count; ++i) ASSERT_TRUE(strcmp(g_probe.order[i], "scene.bin") != 0);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.chains, 2u);
    ASSERT_EQ(st.failed, 0u);
    fx_dispose(&fx);
}

/* The coordinator is full: the dependent stays queued and is issued once a
 * slot frees, instead of being dropped as failed. */
TEST(a_refused_request_is_retried_on_a_later_pump) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    BreakRuntimeReloadRequest busy = 0u;
    g_request_capacity = 1u;
    ASSERT_TRUE(fx_init(&fx, 16u));
    g_request_capacity = 0u;
    /* occupy the only slot until commit_owner runs */
    ASSERT_EQ(break_runtime_reload_request(fx.reload, "other.bin", &busy), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_pump(fx.deps), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.requested, 0u);
    ASSERT_EQ(st.queued, 2u);
    ASSERT_FALSE(st.in_flight);
    ASSERT_EQ(st.failed, 0u);
    {
        /* the slot frees only once the owner of the busy request consumes it */
        BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
        for (u32 spin = 0u; spin < 200000u && state != BREAK_RUNTIME_RELOAD_COMMITTED; ++spin) {
            u32 commits = 0u;
            (void)break_runtime_reload_commit_owner(fx.reload, 16u, &commits);
            ASSERT_EQ(break_runtime_reload_poll(fx.reload, busy, &state), BREAK_RUNTIME_OK);
            if (state != BREAK_RUNTIME_RELOAD_COMMITTED) platform_thread_yield();
        }
        ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_COMMITTED);
    }
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(committed_at("other.bin"), 0);
    ASSERT_EQ(committed_at("mat_a.bin"), 1);
    ASSERT_EQ(committed_at("scene.bin"), 2);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.rebuilt, 2u);
    ASSERT_EQ(st.failed, 0u);
    fx_dispose(&fx);
}

TEST(validation_paths_and_capacity) {
    Fx fx;
    BreakRuntimeReloadDepsConfig dc;
    BreakRuntimeReloadDeps *other = (BreakRuntimeReloadDeps *)&fx;
    BreakRuntimeReloadDepsStats st;
    char long_path[BREAK_RUNTIME_RELOAD_MAX_PATH + 1u];
    ASSERT_TRUE(fx_init(&fx, 6u));
    memset(long_path, 'a', sizeof(long_path) - 1u);
    long_path[sizeof(long_path) - 1u] = '\0';
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 0u, "x.bin"), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kTex, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kTex, ""), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kTex, long_path), BREAK_RUNTIME_INVALID);
    long_path[BREAK_RUNTIME_RELOAD_MAX_PATH - 1u] = '\0';
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kTex, long_path), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kTex, "tex.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 99u, "x.bin"), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, 99u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kOther), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.chains, 0u); /* nothing depends on it */
    ASSERT_EQ(st.queued, 0u);
    ASSERT_EQ(break_runtime_reload_deps_committed(NULL, kTex), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_pump(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_stats(NULL, &st), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_set_path(NULL, kTex, "x"), BREAK_RUNTIME_INVALID);
    memset(&dc, 0, sizeof(dc));
    ASSERT_EQ(break_runtime_reload_deps_create(NULL, &other), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(other == NULL);
    dc.reload = fx.reload;
    dc.graph = fx.graph;
    dc.max_assets = 0u;
    ASSERT_EQ(break_runtime_reload_deps_create(&dc, &other), BREAK_RUNTIME_INVALID);
    dc.max_assets = BREAK_RUNTIME_RELOAD_DEPS_MAX_ASSETS + 1u;
    ASSERT_EQ(break_runtime_reload_deps_create(&dc, &other), BREAK_RUNTIME_INVALID);
    dc.max_assets = 4u;
    dc.reload = NULL;
    ASSERT_EQ(break_runtime_reload_deps_create(&dc, &other), BREAK_RUNTIME_INVALID);
    dc.reload = fx.reload;
    dc.graph = NULL;
    ASSERT_EQ(break_runtime_reload_deps_create(&dc, &other), BREAK_RUNTIME_INVALID);
    dc.graph = fx.graph;
    ASSERT_EQ(break_runtime_reload_deps_create(&dc, NULL), BREAK_RUNTIME_INVALID);
    dc.max_assets = BREAK_RUNTIME_RELOAD_DEPS_MAX_ASSETS;
    ASSERT_EQ(break_runtime_reload_deps_create(&dc, &other), BREAK_RUNTIME_OK);
    break_runtime_reload_deps_destroy(other);
    break_runtime_reload_deps_destroy(NULL);
    fx_dispose(&fx);
}

TEST(a_dependent_without_a_path_fails_the_commit_and_queues_nothing) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    BreakAssetGraphConfig gc;
    ASSERT_TRUE(fx_init(&fx, 16u));
    (void)gc;
    {
        const BreakAssetId deps[] = {kTex};
        ASSERT_EQ(break_asset_graph_add(fx.graph, 77u, deps, 1u), BREAK_ASSET_GRAPH_OK);
    }
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_FAILED);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 0u);
    ASSERT_EQ(st.chains, 0u);
    fx_dispose(&fx);
}

TEST(more_dependents_than_fit_is_overload) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 6u));
    /* six paths recorded; a queue of 6 holds the shader's 3 dependents twice
     * over, so overload needs a graph wider than max_assets: chain 1..8 */
    for (u32 i = 0u; i < 8u; ++i) {
        BreakAssetId dep = 100u + i;
        ASSERT_EQ(break_asset_graph_add(fx.graph, 101u + i, &dep, 1u), BREAK_ASSET_GRAPH_OK);
    }
    ASSERT_EQ(break_asset_graph_add(fx.graph, 100u, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, 100u), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 0u);
    fx_dispose(&fx);
}

/* Drives file events too: the chain starts from the commit hook alone. */
static bool run_events_until_idle(Fx *fx) {
    for (u32 spin = 0u; spin < 200000u; ++spin) {
        BreakRuntimeReloadDepsStats st;
        BreakRuntimeReloadStats rs;
        u32 n = 0u;
        (void)break_runtime_reload_pump_events(fx->reload, 16u, &n);
        (void)break_runtime_reload_commit_owner(fx->reload, 16u, &n);
        if (break_runtime_reload_deps_pump(fx->deps) != BREAK_RUNTIME_OK) return false;
        if (break_runtime_reload_deps_stats(fx->deps, &st) != BREAK_RUNTIME_OK) return false;
        if (break_runtime_reload_stats(fx->reload, &rs) != BREAK_RUNTIME_OK) return false;
        if (st.queued == 0u && !st.in_flight && rs.active == 0u && g_probe.count > 0u) return true;
        platform_thread_yield();
    }
    return false;
}

TEST(a_watched_file_change_starts_the_chain_from_the_commit_hook) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    g_hook_deps = fx.deps;
    ASSERT_EQ(break_runtime_reload_notify_file_event(fx.reload, "tex.bin"), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_events_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 3u);
    ASSERT_STR_EQ(g_probe.order[0], "tex.bin");
    ASSERT_STR_EQ(g_probe.order[1], "mat_a.bin");
    ASSERT_STR_EQ(g_probe.order[2], "scene.bin");
    ASSERT_EQ(g_hook_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    /* the chain's own commits of mat_a and scene start no further chain */
    ASSERT_EQ(st.chains, 1u);
    ASSERT_EQ(st.requested, 2u);
    ASSERT_EQ(st.rebuilt, 2u);
    fx_dispose(&fx);
}

TEST(committed_path_ignores_unknown_paths_and_rejects_bad_arguments) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, "untracked.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, "other.bin"), BREAK_RUNTIME_OK);
    /* a recorded path whose id is not in the graph */
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 55u, "orphan.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, "orphan.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.chains, 0u);
    ASSERT_EQ(st.queued, 0u);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, "shader.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.chains, 1u);
    ASSERT_EQ(st.queued, 3u);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(NULL, "tex.bin"), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, ""), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(run_until_idle(&fx));
    fx_dispose(&fx);
}

/* Two ids reloading from one file are both treated as changed. */
TEST(every_id_sharing_the_committed_path_starts_its_chain) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kShader, "tex.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, "tex.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.chains, 2u);
    ASSERT_EQ(st.queued, 3u); /* mat_a, mat_b, scene once each */
    ASSERT_TRUE(run_until_idle(&fx));
    fx_dispose(&fx);
}

/* One id sharing the path fails; the others still queue and the first error
 * is reported. */
TEST(a_failing_id_on_a_shared_path_does_not_stop_the_others) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    const BreakAssetId on_tex[] = {kTex};
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_asset_graph_add(fx.graph, 77u, on_tex, 1u), BREAK_ASSET_GRAPH_OK); /* no path */
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kShader, "tex.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, "tex.bin"), BREAK_RUNTIME_FAILED);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.chains, 1u);
    ASSERT_EQ(st.queued, 3u); /* the shader's dependents */
    ASSERT_TRUE(run_until_idle(&fx));
    fx_dispose(&fx);
}

/* matA and matB live inside the scene file: the first issued reload of
 * scene.bin covers them all, so the file is loaded once. */
TEST(dependents_sharing_a_file_ride_on_one_reload) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatA, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatB, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 1u);
    ASSERT_STR_EQ(g_probe.order[0], "scene.bin");
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.requested, 1u);
    ASSERT_EQ(st.coalesced, 2u);
    ASSERT_EQ(st.rebuilt, 3u);
    fx_dispose(&fx);
}

/* A same-file dependent that still waits on another file's queued reload
 * cannot ride: it is reloaded again after that file. */
TEST(a_same_file_dependent_waiting_on_another_file_does_not_ride) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    /* matA in scene.bin; matB in its own file; scene needs both */
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatA, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(committed_at("scene.bin") >= 0, true);
    ASSERT_EQ(committed_at("mat_b.bin") >= 0, true);
    /* the last commit is scene.bin, after mat_b */
    ASSERT_STR_EQ(g_probe.order[g_probe.count - 1u], "scene.bin");
    ASSERT_TRUE(committed_at("mat_b.bin") < (i32)g_probe.count - 1);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.failed, 0u);
    ASSERT_EQ(st.rebuilt, 3u);
    fx_dispose(&fx);
}

/* When the shared reload fails, every rider keeps its old version and what
 * depends on any of them is skipped. */
TEST(a_failed_shared_reload_fails_its_riders_too) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    const BreakAssetId on_mat_b[] = {kMatB};
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_asset_graph_add(fx.graph, 90u, on_mat_b, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 90u, "other.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatA, "bad_mat.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatB, "bad_mat.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 0u);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.requested, 1u);
    ASSERT_EQ(st.coalesced, 1u);
    ASSERT_EQ(st.failed, 2u);
    ASSERT_EQ(st.skipped, 2u); /* the scene and asset 90 */
    ASSERT_EQ(st.rebuilt, 0u);
    fx_dispose(&fx);
}

/* The forwarded commit of a shared file names every rider; what they need
 * among themselves came with that same commit, so nothing is queued again. */
TEST(a_forwarded_shared_commit_does_not_requeue_its_riders) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatA, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatB, "scene.bin"), BREAK_RUNTIME_OK);
    g_hook_deps = fx.deps;
    ASSERT_EQ(break_runtime_reload_notify_file_event(fx.reload, "shader.bin"), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_events_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 2u);
    ASSERT_STR_EQ(g_probe.order[0], "shader.bin");
    ASSERT_STR_EQ(g_probe.order[1], "scene.bin");
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.chains, 1u);
    ASSERT_EQ(st.requested, 1u);
    ASSERT_EQ(st.rebuilt, 3u);
    fx_dispose(&fx);
}

/* An external commit of a file that holds several ids already brought every
 * one of them: a dependent recorded with that same file is not reloaded
 * again. */
TEST(a_committed_file_does_not_requeue_ids_it_already_reloaded) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatA, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatB, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 0u);
    ASSERT_EQ(st.chains, 0u);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 0u);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.requested, 0u);
    fx_dispose(&fx);
}

/* A same-file dependent that waits on a dependent in another file is still
 * reloaded, after that file: the commit predates the other file's rebuild. */
TEST(a_same_file_dependent_waiting_on_another_file_is_still_requeued) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    /* the shader lives in the scene file; both materials need it */
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kShader, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed_path(fx.deps, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 3u);
    ASSERT_EQ(st.chains, 1u);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 3u);
    ASSERT_STR_EQ(g_probe.order[2], "scene.bin");
    fx_dispose(&fx);
}

/* Excluding same-file ids is only for commits forwarded by path: committing
 * an id directly still queues every dependent. */
TEST(committing_an_id_directly_queues_same_file_dependents) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatA, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kMatA), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 1u);
    ASSERT_TRUE(run_until_idle(&fx));
    fx_dispose(&fx);
}

/* Once a ride is over its riders are forgotten: a later change of one of
 * them requeues the others that depend on it. */
TEST(a_later_change_of_a_former_rider_requeues_its_dependents) {
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, kMatA, "scene.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 1u); /* matA and the scene in one reload */
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kMatA), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 1u);
    ASSERT_TRUE(run_until_idle(&fx));
    fx_dispose(&fx);
}

TEST(a_dependency_loop_among_dependents_does_not_stall_the_chain) {
    /* matA and matB come to need each other (a loop the graph reports through
     * load_order). Each is queued and blocks the other under the "no queued
     * dependency" rule; the chain must still finish: the loop is dropped
     * without loading anything, and a later unrelated chain still runs. */
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    const BreakAssetId mat_a[] = {kTex, kShader, kMatB};
    const BreakAssetId mat_b[] = {kShader, kMatA};
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_asset_graph_set_deps(fx.graph, kMatA, mat_a, 3u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_set_deps(fx.graph, kMatB, mat_b, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(committed_at("mat_a.bin"), -1);
    ASSERT_EQ(committed_at("mat_b.bin"), -1);
    ASSERT_EQ(committed_at("scene.bin"), -1);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 0u);
    ASSERT_EQ(st.requested, 0u);
    /* the first loop member found is failed; the other one and the scene
     * depend on it and are skipped */
    ASSERT_EQ(st.failed, 1u);
    ASSERT_EQ(st.skipped, 2u);
    ASSERT_EQ(st.rebuilt, 0u);
    /* an unrelated chain still runs afterwards */
    {
        const BreakAssetId other_user[] = {kOther};
        ASSERT_EQ(break_asset_graph_add(fx.graph, 0x77u, other_user, 1u), BREAK_ASSET_GRAPH_OK);
        ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 0x77u, "mat_b.bin"),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kOther), BREAK_RUNTIME_OK);
        ASSERT_TRUE(run_until_idle(&fx));
        ASSERT_TRUE(committed_at("mat_b.bin") >= 0);
    }
    fx_dispose(&fx);
}

TEST(a_dependency_loop_downstream_lets_the_ready_part_finish_first) {
    /* tex -> matA -> {scene <-> 0x66 loop}: matA is rebuilt; the loop behind
     * it is dropped only once nothing else can go. */
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    const BreakAssetId scene[] = {kMatA, kMatB, 0x66u};
    const BreakAssetId loop_node[] = {kScene};
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_asset_graph_add(fx.graph, 0x66u, loop_node, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_set_deps(fx.graph, kScene, scene, 3u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 0x66u, "other.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(committed_at("mat_a.bin"), 0);
    ASSERT_EQ(committed_at("scene.bin"), -1);
    ASSERT_EQ(committed_at("other.bin"), -1);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.rebuilt, 1u);
    ASSERT_EQ(st.failed + st.skipped, 2u);
    fx_dispose(&fx);
}

TEST(a_loop_broken_while_the_chain_runs_is_rebuilt) {
    /* The loop is only dropped once nothing else can go: an edit that breaks
     * it while matA is still loading lets scene and 0x66 be rebuilt. */
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    const BreakAssetId scene[] = {kMatA, kMatB, 0x66u};
    const BreakAssetId loop_node[] = {kScene};
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_asset_graph_add(fx.graph, 0x66u, loop_node, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_set_deps(fx.graph, kScene, scene, 3u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 0x66u, "other.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_pump(fx.deps), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_TRUE(st.in_flight);
    ASSERT_EQ(st.queued, 2u);
    ASSERT_EQ(break_asset_graph_set_deps(fx.graph, kScene, scene, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(committed_at("mat_a.bin"), 0);
    ASSERT_EQ(committed_at("scene.bin"), 1);
    ASSERT_EQ(committed_at("other.bin"), 2);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.rebuilt, 3u);
    ASSERT_EQ(st.failed + st.skipped, 0u);
    fx_dispose(&fx);
}

TEST(only_loop_members_are_failed_what_waits_on_them_is_skipped) {
    /* A merged commit can queue a dependent of the loop ahead of it: it is
     * not on the loop, so it is skipped, not failed. */
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    const BreakAssetId scene[] = {kMatA, kMatB, 0x66u};
    const BreakAssetId loop_node[] = {kScene};
    const BreakAssetId waiter[] = {kOther, kScene};
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_asset_graph_add(fx.graph, 0x66u, loop_node, 1u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_set_deps(fx.graph, kScene, scene, 3u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(fx.graph, 0x88u, waiter, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 0x66u, "other.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_path(fx.deps, 0x88u, "shader.bin"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kOther), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_OK);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(committed_at("mat_a.bin"), 0);
    ASSERT_EQ(committed_at("shader.bin"), -1);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.rebuilt, 1u);
    ASSERT_EQ(st.failed, 1u);
    ASSERT_EQ(st.skipped, 2u);
    fx_dispose(&fx);
}

TEST(set_graph_rebinds_and_drops_queued_ids_the_new_graph_lacks) {
    /* The owner rebuilt its graph (a reloaded scene): the deps object moves
     * to the new one. Queued ids still declared keep their place; ids the new
     * graph lacks are dropped as skipped. */
    Fx fx;
    BreakRuntimeReloadDepsStats st;
    BreakAssetGraph *next = NULL;
    BreakAssetGraphConfig gc;
    const BreakAssetId mat_a[] = {kTex, kShader};
    ASSERT_TRUE(fx_init(&fx, 16u));
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kShader), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 3u);
    /* the new graph has no matB and no scene */
    memset(&gc, 0, sizeof(gc));
    gc.capacity = 8u;
    gc.max_edges = 8u;
    ASSERT_EQ(break_asset_graph_create(&gc, &next), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(next, kMatA, mat_a, 2u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(next, kTex, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_asset_graph_add(next, kShader, NULL, 0u), BREAK_ASSET_GRAPH_OK);
    ASSERT_EQ(break_runtime_reload_deps_set_graph(fx.deps, next), BREAK_RUNTIME_OK);
    /* the old graph may go now */
    break_asset_graph_destroy(fx.graph);
    fx.graph = next;
    ASSERT_EQ(break_runtime_reload_deps_stats(fx.deps, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 1u);
    ASSERT_EQ(st.skipped, 2u);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 1u);
    ASSERT_STR_EQ(g_probe.order[0], "mat_a.bin");
    /* later commits use the new graph */
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kTex), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_deps_committed(fx.deps, kScene), BREAK_RUNTIME_INVALID);
    ASSERT_TRUE(run_until_idle(&fx));
    ASSERT_EQ(g_probe.count, 2u);
    ASSERT_EQ(break_runtime_reload_deps_set_graph(NULL, next), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_deps_set_graph(fx.deps, NULL), BREAK_RUNTIME_INVALID);
    fx_dispose(&fx);
}

TEST_MAIN_BEGIN()
    RUN_TEST(a_changed_texture_rebuilds_its_material_then_the_scene);
    RUN_TEST(a_shared_dependency_rebuilds_each_dependent_once_in_order);
    RUN_TEST(a_failed_dependent_keeps_its_old_version_and_stops_what_needs_it);
    RUN_TEST(only_one_dependent_is_in_flight_at_a_time);
    RUN_TEST(a_new_commit_during_a_chain_merges_without_duplicates);
    RUN_TEST(a_refused_request_is_retried_on_a_later_pump);
    RUN_TEST(validation_paths_and_capacity);
    RUN_TEST(a_dependent_without_a_path_fails_the_commit_and_queues_nothing);
    RUN_TEST(more_dependents_than_fit_is_overload);
    RUN_TEST(a_watched_file_change_starts_the_chain_from_the_commit_hook);
    RUN_TEST(committed_path_ignores_unknown_paths_and_rejects_bad_arguments);
    RUN_TEST(every_id_sharing_the_committed_path_starts_its_chain);
    RUN_TEST(a_failing_id_on_a_shared_path_does_not_stop_the_others);
    RUN_TEST(dependents_sharing_a_file_ride_on_one_reload);
    RUN_TEST(a_same_file_dependent_waiting_on_another_file_does_not_ride);
    RUN_TEST(a_failed_shared_reload_fails_its_riders_too);
    RUN_TEST(a_forwarded_shared_commit_does_not_requeue_its_riders);
    RUN_TEST(a_committed_file_does_not_requeue_ids_it_already_reloaded);
    RUN_TEST(a_same_file_dependent_waiting_on_another_file_is_still_requeued);
    RUN_TEST(committing_an_id_directly_queues_same_file_dependents);
    RUN_TEST(a_later_change_of_a_former_rider_requeues_its_dependents);
    RUN_TEST(a_dependency_loop_among_dependents_does_not_stall_the_chain);
    RUN_TEST(a_dependency_loop_downstream_lets_the_ready_part_finish_first);
    RUN_TEST(a_loop_broken_while_the_chain_runs_is_rebuilt);
    RUN_TEST(only_loop_members_are_failed_what_waits_on_them_is_skipped);
    RUN_TEST(set_graph_rebinds_and_drops_queued_ids_the_new_graph_lacks);
TEST_MAIN_END()
