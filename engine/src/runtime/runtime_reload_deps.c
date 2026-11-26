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
    BreakAssetId in_flight_id;
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
    if (!deps->paths || !deps->queue || !deps->scratch) {
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

/* Every pending asset's dependents fit in max_assets: it was listed among
 * the dependents of a committed asset, which were checked to fit, and its own
 * dependents are a subset of those. */
BreakRuntimeError break_runtime_reload_deps_committed(BreakRuntimeReloadDeps *deps,
                                                      BreakAssetId id) {
    u32 count = 0u;
    u32 added = 0u;
    BreakAssetGraphResult r;
    if (!deps || !break_asset_graph_contains(deps->graph, id)) return BREAK_RUNTIME_INVALID;
    r = break_asset_graph_dependents(deps->graph, id, deps->scratch, deps->max_assets, &count);
    if (r == BREAK_ASSET_GRAPH_OVERLOAD) return BREAK_RUNTIME_OVERLOAD;
    if (r != BREAK_ASSET_GRAPH_OK) return BREAK_RUNTIME_FAILED;
    for (u32 i = 0u; i < count; ++i) {
        if (!find_path(deps, deps->scratch[i])) return BREAK_RUNTIME_FAILED;
        if (!in_list(deps->queue, deps->queued, deps->scratch[i])) added++;
    }
    /* Unreachable guard: queued ids are distinct and each has one of at most
     * max_assets recorded paths. Kept so the queue write below stays bounded
     * if that invariant ever changes. */
    if (deps->queued + added > deps->max_assets) return BREAK_RUNTIME_OVERLOAD;
    /* An asset already in flight is queued again: its dependency changed
     * after its reload started. */
    for (u32 i = 0u; i < count; ++i) {
        if (!in_list(deps->queue, deps->queued, deps->scratch[i]))
            deps->queue[deps->queued++] = deps->scratch[i];
    }
    if (added > 0u) deps->stats.chains++;
    return BREAK_RUNTIME_OK;
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
        r = break_runtime_reload_deps_committed(deps, deps->paths[i].id);
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
            deps->stats.rebuilt++;
        } else {
            finish_failed(deps, deps->in_flight_id);
        }
        deps->in_flight = 0u;
        deps->in_flight_id = 0u;
    }
    while (next_ready(deps, &index)) {
        BreakAssetId id = deps->queue[index];
        BreakRuntimeReloadRequest request = 0u;
        BreakRuntimeError r =
            break_runtime_reload_request(deps->reload, find_path(deps, id)->path, &request);
        if (r == BREAK_RUNTIME_OVERLOAD) return BREAK_RUNTIME_OK; /* retry next pump */
        remove_queued(deps, index);
        deps->stats.requested++;
        if (r != BREAK_RUNTIME_OK) {
            finish_failed(deps, id);
            continue;
        }
        deps->in_flight = request;
        deps->in_flight_id = id;
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
