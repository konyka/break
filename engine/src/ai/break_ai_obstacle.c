#include <ai/break_ai_internal.h>
#include <math.h>
#include <string.h>

static bool obstacle_desc_ok(const BreakAiObstacleDesc *desc) {
    return desc && isfinite(desc->min_x) && isfinite(desc->min_z) &&
           isfinite(desc->max_x) && isfinite(desc->max_z) &&
           desc->min_x <= desc->max_x && desc->min_z <= desc->max_z;
}

static bool obstacle_covers(const BreakAiObstacleDesc *desc, Vec3 center) {
    return center.e[0] >= desc->min_x && center.e[0] <= desc->max_x &&
           center.e[2] >= desc->min_z && center.e[2] <= desc->max_z;
}

static u32 obstacle_affected_count(const BreakAiRuntime *runtime,
                                   const BreakAiObstacleDesc *desc) {
    u32 count = 0;
    for (u32 i = 0; i < runtime->mesh->poly_count; i++) {
        if (obstacle_covers(desc, runtime->mesh->polys[i].center)) {
            count++;
        }
    }
    return count;
}

static void obstacle_apply(BreakAiRuntime *runtime, const BreakAiObstacleDesc *desc,
                           bool block) {
    for (u32 i = 0; i < runtime->mesh->poly_count; i++) {
        if (!obstacle_covers(desc, runtime->mesh->polys[i].center)) {
            continue;
        }
        if (block) {
            runtime->blocked_counts[i]++;
        } else {
            runtime->blocked_counts[i]--;
        }
    }
}

static BreakNavError obstacle_slot(const BreakAiRuntime *runtime,
                                   BreakAiObstacleHandle handle, u32 *out_index) {
    if (handle.index >= runtime->max_obstacles ||
        !runtime->obstacles[handle.index].live ||
        runtime->obstacles[handle.index].generation != handle.generation ||
        handle.generation == 0) {
        return BREAK_NAV_STALE;
    }
    *out_index = handle.index;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_obstacle_add(BreakAiRuntime *runtime, const BreakAiObstacleDesc *desc,
                                    BreakAiObstacleHandle *out) {
    if (!runtime || !desc || !out) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    if (!obstacle_desc_ok(desc)) {
        return BREAK_NAV_INVALID;
    }
    u32 free_index = runtime->max_obstacles;
    for (u32 i = 0; i < runtime->max_obstacles; i++) {
        if (!runtime->obstacles[i].live) {
            free_index = i;
            break;
        }
    }
    if (free_index == runtime->max_obstacles) {
        return BREAK_NAV_OVERLOAD;
    }
    if (obstacle_affected_count(runtime, desc) == 0) {
        return BREAK_NAV_FAILED;
    }
    if (runtime->nav_version == UINT32_MAX) {
        return BREAK_NAV_REJECTED;
    }
    BreakAiObstacleSlot *slot = &runtime->obstacles[free_index];
    u32 generation = slot->generation == UINT32_MAX ? 1u : slot->generation + 1u;
    obstacle_apply(runtime, desc, true);
    slot->desc = *desc;
    slot->generation = generation;
    slot->live = true;
    runtime->nav_version++;
    out->index = free_index;
    out->generation = generation;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_obstacle_update(BreakAiRuntime *runtime, BreakAiObstacleHandle handle,
                                       const BreakAiObstacleDesc *desc) {
    if (!runtime || !desc) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 index = 0;
    BreakNavError slot_status = obstacle_slot(runtime, handle, &index);
    if (slot_status != BREAK_NAV_OK) {
        return slot_status;
    }
    if (!obstacle_desc_ok(desc)) {
        return BREAK_NAV_INVALID;
    }
    BreakAiObstacleSlot *slot = &runtime->obstacles[index];
    if (memcmp(&slot->desc, desc, sizeof(*desc)) == 0) {
        return BREAK_NAV_OK;
    }
    if (obstacle_affected_count(runtime, desc) == 0) {
        return BREAK_NAV_FAILED;
    }
    if (runtime->nav_version == UINT32_MAX) {
        return BREAK_NAV_REJECTED;
    }
    obstacle_apply(runtime, &slot->desc, false);
    obstacle_apply(runtime, desc, true);
    slot->desc = *desc;
    runtime->nav_version++;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_obstacle_remove(BreakAiRuntime *runtime, BreakAiObstacleHandle handle) {
    if (!runtime) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 index = 0;
    BreakNavError slot_status = obstacle_slot(runtime, handle, &index);
    if (slot_status != BREAK_NAV_OK) {
        return slot_status;
    }
    if (runtime->nav_version == UINT32_MAX) {
        return BREAK_NAV_REJECTED;
    }
    BreakAiObstacleSlot *slot = &runtime->obstacles[index];
    obstacle_apply(runtime, &slot->desc, false);
    slot->live = false;
    runtime->nav_version++;
    return BREAK_NAV_OK;
}
