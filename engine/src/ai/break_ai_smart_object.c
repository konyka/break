#include <ai/break_ai_internal.h>
#include <math.h>

static bool smart_entity_equal(Entity a, Entity b) {
    return a.index == b.index && a.generation == b.generation;
}

static bool smart_position_ok(Vec3 position) {
    return isfinite(position.e[0]) && isfinite(position.e[1]) && isfinite(position.e[2]);
}

static BreakNavError smart_object_slot(const BreakAiRuntime *runtime,
                                       BreakAiSmartObjectHandle handle, u32 *out_index) {
    if (handle.index >= runtime->max_smart_objects ||
        !runtime->smart_objects[handle.index].live ||
        runtime->smart_objects[handle.index].generation != handle.generation ||
        handle.generation == 0) {
        return BREAK_NAV_STALE;
    }
    *out_index = handle.index;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_smart_object_add(BreakAiRuntime *runtime, Vec3 position,
                                        BreakAiSmartObjectHandle *out) {
    if (!runtime || !out) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    if (!smart_position_ok(position)) {
        return BREAK_NAV_INVALID;
    }
    u32 free_index = runtime->max_smart_objects;
    for (u32 i = 0; i < runtime->max_smart_objects; i++) {
        if (!runtime->smart_objects[i].live) {
            free_index = i;
            break;
        }
    }
    if (free_index == runtime->max_smart_objects) {
        return BREAK_NAV_OVERLOAD;
    }
    BreakAiSmartObjectSlot *object = &runtime->smart_objects[free_index];
    u32 generation = object->generation == UINT32_MAX ? 1u : object->generation + 1u;
    object->position = position;
    object->owner = ENTITY_NULL;
    object->generation = generation;
    object->live = true;
    out->index = free_index;
    out->generation = generation;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_smart_object_remove(BreakAiRuntime *runtime,
                                           BreakAiSmartObjectHandle handle) {
    if (!runtime) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 index = 0;
    BreakNavError status = smart_object_slot(runtime, handle, &index);
    if (status != BREAK_NAV_OK) {
        return status;
    }
    if (entity_valid(runtime->smart_objects[index].owner)) {
        return BREAK_NAV_REJECTED;
    }
    runtime->smart_objects[index].live = false;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_smart_object_reserve(BreakAiRuntime *runtime,
                                            BreakAiSmartObjectHandle handle,
                                            Entity agent) {
    if (!runtime) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    if (!entity_valid(agent)) {
        return BREAK_NAV_INVALID;
    }
    u32 index = 0;
    BreakNavError status = smart_object_slot(runtime, handle, &index);
    if (status != BREAK_NAV_OK) {
        return status;
    }
    if (break_ai_agent_index(runtime, agent) == UINT32_MAX) {
        return BREAK_NAV_STALE;
    }
    BreakAiSmartObjectSlot *object = &runtime->smart_objects[index];
    if (!entity_valid(object->owner)) {
        object->owner = agent;
        return BREAK_NAV_OK;
    }
    if (smart_entity_equal(object->owner, agent)) {
        return BREAK_NAV_OK;
    }
    return BREAK_NAV_REJECTED;
}

BreakNavError break_ai_smart_object_release(BreakAiRuntime *runtime,
                                            BreakAiSmartObjectHandle handle,
                                            Entity agent) {
    if (!runtime) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    if (!entity_valid(agent)) {
        return BREAK_NAV_INVALID;
    }
    u32 index = 0;
    BreakNavError status = smart_object_slot(runtime, handle, &index);
    if (status != BREAK_NAV_OK) {
        return status;
    }
    if (break_ai_agent_index(runtime, agent) == UINT32_MAX) {
        return BREAK_NAV_STALE;
    }
    BreakAiSmartObjectSlot *object = &runtime->smart_objects[index];
    if (!entity_valid(object->owner) || !smart_entity_equal(object->owner, agent)) {
        return BREAK_NAV_REJECTED;
    }
    object->owner = ENTITY_NULL;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_smart_object_owner(BreakAiRuntime *runtime,
                                          BreakAiSmartObjectHandle handle,
                                          Entity *out_owner) {
    if (!runtime || !out_owner) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 index = 0;
    BreakNavError status = smart_object_slot(runtime, handle, &index);
    if (status != BREAK_NAV_OK) {
        return status;
    }
    *out_owner = runtime->smart_objects[index].owner;
    return BREAK_NAV_OK;
}
