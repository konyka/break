#include <ai/break_ai_internal.h>
#include <stdlib.h>

bool break_ai_is_owner(const BreakAiRuntime *runtime) {
    return runtime && platform_thread_id_equal(runtime->owner, platform_thread_current_id());
}

BreakAiRuntime *break_ai_runtime_create(BreakNavMesh *mesh, const BreakAiRuntimeDesc *desc) {
    if (!mesh || !desc || desc->max_obstacles > BREAK_AI_MAX_OBSTACLES ||
        desc->max_agents > BREAK_AI_MAX_AGENTS ||
        desc->max_cached_paths > BREAK_AI_MAX_CACHED_PATHS ||
        desc->max_smart_objects > BREAK_AI_MAX_SMART_OBJECTS ||
        desc->max_formations > BREAK_AI_MAX_FORMATIONS) {
        return NULL;
    }
    BreakAiRuntime *runtime = (BreakAiRuntime *)calloc(1, sizeof(BreakAiRuntime));
    if (!runtime) {
        return NULL;
    }
    runtime->mesh = mesh;
    runtime->owner = platform_thread_current_id();
    runtime->nav_version = 1;
    runtime->max_obstacles = desc->max_obstacles;
    runtime->max_cached_paths = desc->max_cached_paths;
    runtime->workspace = break_nav_workspace_create(mesh->poly_count);
    if (mesh->poly_count > 0) {
        runtime->blocked_counts = (u32 *)calloc(mesh->poly_count, sizeof(u32));
    }
    if (desc->max_obstacles > 0) {
        runtime->obstacles = (BreakAiObstacleSlot *)calloc(desc->max_obstacles,
                                                           sizeof(BreakAiObstacleSlot));
    }
    if (desc->max_cached_paths > 0) {
        runtime->cache = (BreakAiCacheEntry *)calloc(desc->max_cached_paths,
                                                     sizeof(BreakAiCacheEntry));
    }
    if (!runtime->workspace || (mesh->poly_count > 0 && !runtime->blocked_counts) ||
        (desc->max_obstacles > 0 && !runtime->obstacles) ||
        (desc->max_cached_paths > 0 && !runtime->cache)) {
        break_ai_runtime_destroy(runtime);
        return NULL;
    }
    return runtime;
}

void break_ai_runtime_destroy(BreakAiRuntime *runtime) {
    if (!runtime || !break_ai_is_owner(runtime)) {
        return;
    }
    break_nav_workspace_destroy(runtime->workspace);
    free(runtime->blocked_counts);
    free(runtime->obstacles);
    free(runtime->cache);
    free(runtime);
}

u32 break_ai_nav_version(const BreakAiRuntime *runtime) {
    if (!break_ai_is_owner(runtime)) {
        return 0;
    }
    return runtime->nav_version;
}
