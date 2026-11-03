#include <ai/break_ai_internal.h>
#include <math.h>

static bool query_vec_ok(Vec3 value) {
    return isfinite(value.e[0]) && isfinite(value.e[1]) && isfinite(value.e[2]);
}

static bool query_vec_equal(Vec3 a, Vec3 b) {
    return a.e[0] == b.e[0] && a.e[1] == b.e[1] && a.e[2] == b.e[2];
}

BreakNavError break_ai_find_path(BreakAiRuntime *runtime, Vec3 start, Vec3 end,
                                 u32 expected_version, BreakAiPath *out) {
    if (!runtime || !out) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    if (expected_version != runtime->nav_version) {
        return BREAK_NAV_STALE;
    }
    if (!query_vec_ok(start) || !query_vec_ok(end)) {
        return BREAK_NAV_INVALID;
    }
    for (u32 i = 0; i < runtime->max_cached_paths; i++) {
        const BreakAiCacheEntry *entry = &runtime->cache[i];
        if (entry->valid && entry->nav_version == runtime->nav_version &&
            query_vec_equal(entry->start, start) && query_vec_equal(entry->end, end)) {
            *out = entry->result;
            return BREAK_NAV_OK;
        }
    }
    BreakAiPath result;
    BreakNavError status = break_nav_find_path_workspace(runtime->mesh, runtime->workspace,
                                                         runtime->blocked_counts,
                                                         start, end, &result.path);
    if (status != BREAK_NAV_OK) {
        return status;
    }
    result.nav_version = runtime->nav_version;
    if (runtime->max_cached_paths > 0) {
        BreakAiCacheEntry *entry = &runtime->cache[runtime->cache_next];
        entry->start = start;
        entry->end = end;
        entry->result = result;
        entry->nav_version = runtime->nav_version;
        entry->valid = true;
        runtime->cache_next = (runtime->cache_next + 1u) % runtime->max_cached_paths;
    }
    *out = result;
    return BREAK_NAV_OK;
}

bool break_ai_path_is_current(const BreakAiRuntime *runtime, const BreakAiPath *path) {
    return break_ai_is_owner(runtime) && path && path->nav_version != 0 &&
           path->nav_version == runtime->nav_version;
}
