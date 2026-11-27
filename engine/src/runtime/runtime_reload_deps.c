#include "runtime/runtime_reload_deps.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
    BreakAssetId id;
    char path[BREAK_RUNTIME_RELOAD_MAX_PATH];
} PathEntry;

struct BreakRuntimeReloadDeps {
    BreakRuntimeReload *reload;
    const BreakAssetGraph *graph;
    u32 max_assets;
    PathEntry *paths;
    u32 path_count;
    BreakAssetId *queue; /* rebuild order, head first */
    u32 queued;
    BreakAssetId *scratch;
    BreakAssetId *walk;
    u8 *mark;
    BreakAssetId *riders; /* every id the in-flight reload covers */
    u32 rider_count;
    BreakRuntimeReloadRequest in_flight;
    BreakRuntimeReloadDepsStats stats;
};

BreakRuntimeError break_runtime_reload_deps_create(const BreakRuntimeReloadDepsConfig *config,
                                                   BreakRuntimeReloadDeps **out) {
    BreakRuntimeReloadDeps *deps;
    if (out) *out = NULL;
    if (!config || !out || !config->reload || !config->graph || config->max_assets == 0u ||
        config->max_assets > BREAK_RUNTIME_RELOAD_DEPS_MAX_ASSETS) {
        return BREAK_RUNTIME_INVALID;
    }
    deps = (BreakRuntimeReloadDeps *)calloc(1u, sizeof(*deps));
    if (!deps) return BREAK_RUNTIME_OOM;
    deps->paths = (PathEntry *)calloc(config->max_assets, sizeof(*deps->paths));
    deps->queue = (BreakAssetId *)calloc(config->max_assets, sizeof(*deps->queue));
    deps->scratch = (BreakAssetId *)calloc(config->max_assets, sizeof(*deps->scratch));
    deps->walk = (BreakAssetId *)calloc(config->max_assets, sizeof(*deps->walk));
    deps->mark = (u8 *)calloc(config->max_assets, sizeof(*deps->mark));
    deps->riders = (BreakAssetId *)calloc(config->max_assets, sizeof(*deps->riders));
    if (!deps->paths || !deps->queue || !deps->scratch || !deps->walk || !deps->mark || !deps->riders) {
        break_runtime_reload_deps_destroy(deps);
        return BREAK_RUNTIME_OOM;
    }
    deps->reload = config->reload;
    deps->graph = config->graph;
    deps->max_assets = config->max_assets;
    *out = deps;
    return BREAK_RUNTIME_OK;
}

void break_runtime_reload_deps_destroy(BreakRuntimeReloadDeps *deps) {
    if (!deps) return;
    free(deps->paths);
    free(deps->queue);
    free(deps->scratch);
    free(deps->walk);
    free(deps->mark);
    free(deps->riders);
    free(deps);
}

static PathEntry *find_path(BreakRuntimeReloadDeps *deps, BreakAssetId id) {
    for (u32 i = 0u; i < deps->path_count; ++i) {
        if (deps->paths[i].id == id) return &deps->paths[i];
    }
    return NULL;
}

BreakRuntimeError break_runtime_reload_deps_set_path(BreakRuntimeReloadDeps *deps,
                                                     BreakAssetId id, const char *path) {
    PathEntry *entry;
    usize len;
    if (!deps || id == 0u || !path) return BREAK_RUNTIME_INVALID;
    len = strlen(path);
    if (len == 0u || len >= BREAK_RUNTIME_RELOAD_MAX_PATH) return BREAK_RUNTIME_INVALID;
    entry = find_path(deps, id);
    if (!entry) {
        if (deps->path_count == deps->max_assets) return BREAK_RUNTIME_OVERLOAD;
        entry = &deps->paths[deps->path_count++];
        entry->id = id;
    }
    memcpy(entry->path, path, len + 1u);
    return BREAK_RUNTIME_OK;
}

static bool in_list(const BreakAssetId *list, u32 count, BreakAssetId id) {
    for (u32 i = 0u; i < count; ++i) {
        if (list[i] == id) return true;
    }
    return false;
}

/* After a commit of the file `same_file`, marks (deps->mark[i] = 1) the
 * dependents in scratch[0..count) that must still be reloaded: those in
 * another file, and those in the same file that depend on one in another
 * file (that one is rebuilt after the commit, so the file must be reloaded
 * again after it). The rest came with the commit itself. Dependents are
 * transitive, so the dependents of a listed id are all listed too and fit. */
static void mark_needed(BreakRuntimeReloadDeps *deps, u32 count, const char *same_file) {
    for (u32 i = 0u; i < count; ++i) {
        deps->mark[i] = (u8)(strcmp(find_path(deps, deps->scratch[i])->path, same_file) != 0);
    }
    for (u32 j = 0u; j < count; ++j) {
        u32 walked = 0u;
        if (strcmp(find_path(deps, deps->scratch[j])->path, same_file) == 0) continue;
        if (break_asset_graph_dependents(deps->graph, deps->scratch[j], deps->walk,
                                         deps->max_assets, &walked) != BREAK_ASSET_GRAPH_OK) {
            continue;
        }
        for (u32 i = 0u; i < count; ++i) {
            if (!deps->mark[i] && in_list(deps->walk, walked, deps->scratch[i])) deps->mark[i] = 1u;
        }
    }
}

/* Every pending asset's dependents fit in max_assets: it was listed among
 * the dependents of a committed asset, which were checked to fit, and its own
 * dependents are a subset of those. `same_file` is the committed file for a
 * commit forwarded by path, NULL for a direct one. */
static BreakRuntimeError committed_impl(BreakRuntimeReloadDeps *deps, BreakAssetId id,
                                        const char *same_file) {
    u32 count = 0u;
    u32 added = 0u;
    bool riding;
    BreakAssetGraphResult r;
    if (!deps || !break_asset_graph_contains(deps->graph, id)) return BREAK_RUNTIME_INVALID;
    r = break_asset_graph_dependents(deps->graph, id, deps->scratch, deps->max_assets, &count);
    if (r == BREAK_ASSET_GRAPH_OVERLOAD) return BREAK_RUNTIME_OVERLOAD;
    if (r != BREAK_ASSET_GRAPH_OK) return BREAK_RUNTIME_FAILED;
    for (u32 i = 0u; i < count; ++i) {
        if (!find_path(deps, deps->scratch[i])) return BREAK_RUNTIME_FAILED;
    }
    if (same_file) {
        mark_needed(deps, count, same_file);
    } else {
        memset(deps->mark, 1, count);
    }
    for (u32 i = 0u; i < count; ++i) {
        if (deps->mark[i] && !in_list(deps->queue, deps->queued, deps->scratch[i])) added++;
    }
    /* Unreachable guard: queued ids are distinct and each has one of at most
     * max_assets recorded paths. Kept so the queue write below stays bounded
     * if that invariant ever changes. */
    if (deps->queued + added > deps->max_assets) return BREAK_RUNTIME_OVERLOAD;
    /* An asset already in flight is queued again: its dependency changed
     * after its reload started. Except when both ride on the same reload:
     * that one commit already brought the dependency's new version. */
    riding = in_list(deps->riders, deps->rider_count, id);
    for (u32 i = 0u; i < count; ++i) {
        if (!deps->mark[i] || in_list(deps->queue, deps->queued, deps->scratch[i])) continue;
        if (riding && in_list(deps->riders, deps->rider_count, deps->scratch[i])) {
            added--;
            continue;
        }
        deps->queue[deps->queued++] = deps->scratch[i];
    }
    if (added > 0u) deps->stats.chains++;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_reload_deps_committed(BreakRuntimeReloadDeps *deps,
                                                      BreakAssetId id) {
    return committed_impl(deps, id, NULL);
}

BreakRuntimeError break_runtime_reload_deps_committed_path(BreakRuntimeReloadDeps *deps,
                                                           const char *path) {
    BreakRuntimeError first = BREAK_RUNTIME_OK;
    if (!deps || !path || path[0] == '\0') return BREAK_RUNTIME_INVALID;
    for (u32 i = 0u; i < deps->path_count; ++i) {
        BreakRuntimeError r;
        if (strcmp(deps->paths[i].path, path) != 0 ||
            !break_asset_graph_contains(deps->graph, deps->paths[i].id)) {
            continue;
        }
        r = committed_impl(deps, deps->paths[i].id, path);
        if (r != BREAK_RUNTIME_OK && first == BREAK_RUNTIME_OK) first = r;
    }
    return first;
}

static void remove_queued(BreakRuntimeReloadDeps *deps, u32 index) {
    memmove(deps->queue + index, deps->queue + index + 1u,
            (deps->queued - index - 1u) * sizeof(*deps->queue));
    deps->queued--;
}

/* A failed asset keeps its old version, so nothing queued that depends on
 * it may be rebuilt from it. */
static void finish_failed(BreakRuntimeReloadDeps *deps, BreakAssetId id) {
    u32 count = 0u;
    deps->stats.failed++;
    if (break_asset_graph_dependents(deps->graph, id, deps->scratch, deps->max_assets, &count) !=
        BREAK_ASSET_GRAPH_OK) {
        return;
    }
    for (u32 i = 0u; i < deps->queued;) {
        if (in_list(deps->scratch, count, deps->queue[i])) {
            remove_queued(deps, i);
            deps->stats.skipped++;
        } else {
            ++i;
        }
    }
}

/* The first queued asset none of whose dependencies is still queued. */
static bool next_ready(BreakRuntimeReloadDeps *deps, u32 *out_index) {
    for (u32 i = 0u; i < deps->queued; ++i) {
        bool blocked = false;
        for (u32 j = 0u; j < deps->queued && !blocked; ++j) {
            u32 count = 0u;
            if (j == i) continue; /* an asset is never its own dependent; saves a walk */
            if (break_asset_graph_dependents(deps->graph, deps->queue[j], deps->scratch,
                                             deps->max_assets, &count) != BREAK_ASSET_GRAPH_OK) {
                continue;
            }
            blocked = in_list(deps->scratch, count, deps->queue[i]);
        }
        if (!blocked) {
            *out_index = i;
            return true;
        }
    }
    return false;
}

static bool depends_on(BreakRuntimeReloadDeps *deps, BreakAssetId dependent, BreakAssetId on) {
    u32 count = 0u;
    if (break_asset_graph_dependents(deps->graph, on, deps->scratch, deps->max_assets, &count) !=
        BREAK_ASSET_GRAPH_OK) {
        return false;
    }
    return in_list(deps->scratch, count, dependent);
}

/* The issued reload of queue[index] loads its whole file, so every queued id
 * recorded with the same path rides on it, unless it still waits for a
 * queued id in another file (that one's new version would be missed). One
 * pass is enough: dependents are transitive, so an id waiting on a dropped
 * rider also waits on whatever that rider waits on, which is not riding. */
static void take_riders(BreakRuntimeReloadDeps *deps, u32 index) {
    const char *path = find_path(deps, deps->queue[index])->path;
    for (u32 i = 0u; i < deps->queued; ++i) {
        deps->mark[i] = (u8)(strcmp(find_path(deps, deps->queue[i])->path, path) == 0);
    }
    for (u32 i = 0u; i < deps->queued; ++i) {
        if (!deps->mark[i]) continue;
        for (u32 j = 0u; j < deps->queued; ++j) {
            if (!deps->mark[j] && depends_on(deps, deps->queue[i], deps->queue[j])) {
                deps->mark[i] = 0u;
                break;
            }
        }
    }
    for (u32 i = deps->queued; i-- > 0u;) {
        if (!deps->mark[i]) continue;
        deps->riders[deps->rider_count++] = deps->queue[i];
        remove_queued(deps, i);
    }
    deps->stats.coalesced += deps->rider_count - 1u;
}

/* Nothing queued is ready: every queued asset waits on another queued one,
 * which only a dependency loop does (the graph reports it through
 * load_order). Two queued assets that each depend on the other lie on one
 * loop and can never be rebuilt from a settled dependency, so they keep
 * their old versions and what needs them is skipped, as for a failure.
 * dependents() never lists an asset itself, hence the pairwise test. */
static void drop_loop_members(BreakRuntimeReloadDeps *deps) {
    for (u32 i = 0u; i < deps->queued;) {
        BreakAssetId id = deps->queue[i];
        bool on_loop = false;
        for (u32 j = 0u; j < deps->queued && !on_loop; ++j) {
            on_loop = j != i && depends_on(deps, id, deps->queue[j]) &&
                      depends_on(deps, deps->queue[j], id);
        }
        if (on_loop) {
            remove_queued(deps, i);
            finish_failed(deps, id);
            i = 0u; /* finish_failed may have removed entries before i */
        } else {
            ++i;
        }
    }
}

BreakRuntimeError break_runtime_reload_deps_pump(BreakRuntimeReloadDeps *deps) {
    u32 index = 0u;
    if (!deps) return BREAK_RUNTIME_INVALID;
    if (deps->in_flight != 0u) {
        BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
        BreakRuntimeError r = break_runtime_reload_poll(deps->reload, deps->in_flight, &state);
        if (r == BREAK_RUNTIME_OK && (state == BREAK_RUNTIME_RELOAD_LOADING ||
                                      state == BREAK_RUNTIME_RELOAD_VALIDATING)) {
            return BREAK_RUNTIME_OK;
        }
        if (r == BREAK_RUNTIME_OK && state == BREAK_RUNTIME_RELOAD_COMMITTED) {
            deps->stats.rebuilt += deps->rider_count;
        } else {
            for (u32 i = 0u; i < deps->rider_count; ++i) finish_failed(deps, deps->riders[i]);
        }
        deps->in_flight = 0u;
        deps->rider_count = 0u;
    }
    if (deps->queued > 0u && !next_ready(deps, &index)) drop_loop_members(deps);
    while (next_ready(deps, &index)) {
        BreakAssetId id = deps->queue[index];
        BreakRuntimeReloadRequest request = 0u;
        BreakRuntimeError r =
            break_runtime_reload_request(deps->reload, find_path(deps, id)->path, &request);
        if (r == BREAK_RUNTIME_OVERLOAD) return BREAK_RUNTIME_OK; /* retry next pump */
        deps->stats.requested++;
        if (r != BREAK_RUNTIME_OK) {
            remove_queued(deps, index);
            finish_failed(deps, id);
            continue;
        }
        take_riders(deps, index);
        deps->in_flight = request;
        break;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_reload_deps_stats(const BreakRuntimeReloadDeps *deps,
                                                  BreakRuntimeReloadDepsStats *out) {
    if (!deps || !out) return BREAK_RUNTIME_INVALID;
    *out = deps->stats;
    out->queued = deps->queued;
    out->in_flight = deps->in_flight != 0u;
    return BREAK_RUNTIME_OK;
}
