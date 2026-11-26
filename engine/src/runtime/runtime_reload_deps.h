#pragma once

#include <asset/asset_graph.h>
#include <runtime/runtime_reload.h>

/* Dependency-driven hot reload (design: docs/design/runtime_hot_reload.md
 * "依赖驱动的热重载"). Part of the optional `runtime_core` library.
 *
 * The reload coordinator reloads one path at a time. When a texture changes,
 * every material using it, and every scene using those materials, must be
 * rebuilt too, dependencies first. This adapter keeps a path for each asset
 * id of a BreakAssetGraph and, after the coordinator committed a changed
 * asset, requests reloads for everything that depends on it:
 *
 *  - break_runtime_reload_deps_committed(id) takes the graph's rebuild order
 *    (break_asset_graph_dependents) and queues those ids;
 *    break_runtime_reload_deps_committed_path(path) does the same from the
 *    coordinator's commit hook, for the ids recorded with that path;
 *  - break_runtime_reload_deps_pump issues the queued reloads one at a
 *    time, each only when none of its dependencies is still queued, and the
 *    next only after the previous one reached a terminal state, so a
 *    dependent is never rebuilt from a dependency that is still loading;
 *  - a dependent that fails (FAILED_KEEP_OLD, TIMEOUT, OOM, CANCELLED) keeps
 *    its old version and the chain stops there: what depends on it is
 *    skipped, since it would be rebuilt from stale input. The remaining
 *    unrelated ids still go.
 *  - A new commit while a chain runs merges: ids already queued are not
 *    queued twice, and the "no queued dependency" rule orders the union.
 *    An id whose reload is in flight is queued again, since its dependency
 *    changed after that reload started.
 *
 * Owner thread only, like pump_events/commit_owner; the graph and the
 * coordinator are borrowed. */
typedef struct BreakRuntimeReloadDeps BreakRuntimeReloadDeps;

#define BREAK_RUNTIME_RELOAD_DEPS_MAX_ASSETS 4096u

typedef struct BreakRuntimeReloadDepsConfig {
    BreakRuntimeReload *reload;    /* borrowed */
    const BreakAssetGraph *graph;  /* borrowed */
    u32 max_assets;                /* paths and queue entries, 1..MAX_ASSETS */
} BreakRuntimeReloadDepsConfig;

typedef struct BreakRuntimeReloadDepsStats {
    u64 chains;    /* commits that queued at least one dependent */
    u64 requested; /* dependent reloads issued */
    u64 rebuilt;   /* dependents that reached COMMITTED */
    u64 failed;    /* dependents that ended in another terminal state */
    u64 skipped;   /* dependents dropped because something they need failed */
    u32 queued;    /* waiting to be issued */
    bool in_flight;
} BreakRuntimeReloadDepsStats;

BreakRuntimeError break_runtime_reload_deps_create(const BreakRuntimeReloadDepsConfig *config,
                                                   BreakRuntimeReloadDeps **out);
void break_runtime_reload_deps_destroy(BreakRuntimeReloadDeps *deps);

/* Records the VFS path that reloads asset `id`. Replacing a path is OK.
 * OVERLOAD when max_assets paths are recorded; INVALID for id 0 or a path
 * that is NULL, empty or longer than BREAK_RUNTIME_RELOAD_MAX_PATH - 1. */
BreakRuntimeError break_runtime_reload_deps_set_path(BreakRuntimeReloadDeps *deps,
                                                     BreakAssetId id, const char *path);

/* The coordinator committed `id`: queue every asset that depends on it.
 * INVALID when `id` is not in the graph. OVERLOAD (nothing queued) when the
 * dependents do not fit; FAILED when a dependent has no recorded path. */
BreakRuntimeError break_runtime_reload_deps_committed(BreakRuntimeReloadDeps *deps,
                                                      BreakAssetId id);

/* The same for every asset id whose recorded path is `path`, so the
 * coordinator's commit hook can forward each commit as it happens: a path
 * no id records, or whose id is not in the graph, is ignored (OK). The
 * chain's own commits may be forwarded too; their dependents are already
 * queued, so they start no new chain. Every matching id is tried; the first
 * error is returned. INVALID for a NULL or empty path. Owner thread only:
 * the commit hook runs there. */
BreakRuntimeError break_runtime_reload_deps_committed_path(BreakRuntimeReloadDeps *deps,
                                                           const char *path);

/* Advances the chain: polls the in-flight dependent and, once it is
 * terminal, issues the next one. Call every tick after commit_owner.
 * A request the coordinator refuses with OVERLOAD is retried next pump. */
BreakRuntimeError break_runtime_reload_deps_pump(BreakRuntimeReloadDeps *deps);

BreakRuntimeError break_runtime_reload_deps_stats(const BreakRuntimeReloadDeps *deps,
                                                  BreakRuntimeReloadDepsStats *out);
