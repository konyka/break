#include <kernel/break_kernel_internal.h>

static BreakKernelError occupy_slot(BreakKernel *kernel, Entity entity, u32 class_id, u32 *out_slot) {
    if (kernel->live_count >= kernel->max_actors || kernel->free_top == 0) {
        return BREAK_KERNEL_OVERLOAD;
    }
    if (break_kernel_actor_slot(kernel, entity) != UINT32_MAX) {
        return BREAK_KERNEL_REJECTED;
    }
    if (entity.index >= ECS_MAX_ENTITIES) {
        return BREAK_KERNEL_FAILED;
    }
    u32 slot = kernel->free_stack[--kernel->free_top];
    kernel->actors[slot].entity = entity;
    kernel->actors[slot].class_id = class_id;
    kernel->actors[slot].alive = true;
    kernel->slot_of[entity.index] = slot;
    kernel->live_count++;
    *out_slot = slot;
    return BREAK_KERNEL_OK;
}

static BreakKernelError add_class_components(BreakKernel *kernel, Entity entity, const BreakKernelClass *cls) {
    for (u32 i = 0; i < cls->component_count; i++) {
        ComponentType id = cls->components[i];
        if (kernel->world->component_sizes[id] == 0) {
            return BREAK_KERNEL_INVALID;
        }
        if (!world_add_component(kernel->world, entity, id)) {
            return BREAK_KERNEL_FAILED;
        }
    }
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_adopt(BreakKernel *kernel, Entity entity, u32 class_id) {
    if (class_id == 0 || class_id > kernel->class_count || !kernel->classes[class_id].used) {
        return BREAK_KERNEL_STALE;
    }
    if (!world_entity_exists(kernel->world, entity)) {
        return BREAK_KERNEL_STALE;
    }
    if (kernel->live_count >= kernel->max_actors) {
        return BREAK_KERNEL_OVERLOAD;
    }
    BreakKernelError added = add_class_components(kernel, entity, &kernel->classes[class_id]);
    if (added != BREAK_KERNEL_OK) {
        return added;
    }
    u32 slot = 0;
    return occupy_slot(kernel, entity, class_id, &slot);
}

BreakKernelError break_kernel_spawn(BreakKernel *kernel, const BreakKernelSpawn *spawn, Entity *out_entity) {
    if (!kernel || !spawn || !out_entity) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    if (spawn->class_id == 0 || spawn->class_id > kernel->class_count ||
        !kernel->classes[spawn->class_id].used) {
        return BREAK_KERNEL_STALE;
    }
    if (kernel->live_count >= kernel->max_actors || kernel->free_top == 0) {
        return BREAK_KERNEL_OVERLOAD;
    }
    const BreakKernelClass *cls = &kernel->classes[spawn->class_id];
    for (u32 i = 0; i < cls->component_count; i++) {
        if (kernel->world->component_sizes[cls->components[i]] == 0) {
            return BREAK_KERNEL_INVALID;
        }
    }
    Entity entity = world_create_entity(kernel->world);
    if (!entity_valid(entity)) {
        return BREAK_KERNEL_FAILED;
    }
    BreakKernelError added = add_class_components(kernel, entity, cls);
    if (added != BREAK_KERNEL_OK) {
        world_destroy_entity(kernel->world, entity);
        return added;
    }
    if (kernel->world->component_sizes[BREAK_KERNEL_POSITION_COMPONENT] >= sizeof(Vec3)) {
        void *pos = world_get_component(kernel->world, entity, BREAK_KERNEL_POSITION_COMPONENT);
        if (pos) {
            memcpy(pos, &spawn->position, sizeof(Vec3));
        }
    }
    u32 slot = 0;
    BreakKernelError occupied = occupy_slot(kernel, entity, spawn->class_id, &slot);
    if (occupied != BREAK_KERNEL_OK) {
        world_destroy_entity(kernel->world, entity);
        return occupied;
    }
    *out_entity = entity;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_despawn(BreakKernel *kernel, Entity entity) {
    if (!kernel) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    u32 slot = break_kernel_actor_slot(kernel, entity);
    if (slot == UINT32_MAX) {
        return BREAK_KERNEL_STALE;
    }
    if (kernel->script_bridge_used && kernel->script_bridge.actor_despawn) {
        kernel->script_bridge.actor_despawn(kernel->script_bridge.user, entity);
    }
    break_kernel_area_on_despawn(kernel, slot, entity);
    break_kernel_weapons_on_despawn(kernel, slot);
    break_kernel_items_on_despawn(kernel, slot);
    world_destroy_entity(kernel->world, entity);
    kernel->actors[slot].alive = false;
    kernel->actors[slot].entity = ENTITY_NULL;
    kernel->slot_of[entity.index] = UINT32_MAX;
    kernel->free_stack[kernel->free_top++] = slot;
    if (kernel->live_count > 0) {
        kernel->live_count--;
    }
    return BREAK_KERNEL_OK;
}

void break_kernel_set_tick(BreakKernel *kernel, u32 class_id, BreakKernelTickFn fn, void *user) {
    if (!kernel || !break_kernel_is_owner(kernel)) {
        return;
    }
    if (class_id == 0 || class_id > kernel->class_count || !kernel->classes[class_id].used) {
        return;
    }
    kernel->classes[class_id].tick = fn;
    kernel->classes[class_id].tick_user = user;
}

BreakKernelError break_kernel_set_script_bridge(
    BreakKernel *kernel, const BreakKernelScriptBridge *bridge) {
    if (!kernel) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    if (!bridge) {
        memset(&kernel->script_bridge, 0, sizeof(kernel->script_bridge));
        kernel->script_bridge_used = false;
        return BREAK_KERNEL_OK;
    }
    if (!bridge->actor_tick) {
        return BREAK_KERNEL_INVALID;
    }
    if (kernel->script_bridge_used) {
        return BREAK_KERNEL_REJECTED;
    }
    kernel->script_bridge = *bridge;
    kernel->script_bridge_used = true;
    return BREAK_KERNEL_OK;
}

void break_kernel_tick(BreakKernel *kernel, f32 dt) {
    if (!kernel || !break_kernel_is_owner(kernel)) {
        return;
    }
    u32 n = 0;
    for (u32 slot = 0; slot < kernel->max_actors; slot++) {
        if (kernel->actors[slot].alive) {
            kernel->tick_snapshot[n++] = slot;
        }
    }
    for (u32 i = 0; i < n; i++) {
        u32 slot = kernel->tick_snapshot[i];
        if (!kernel->actors[slot].alive) {
            continue;
        }
        BreakKernelActor *actor = &kernel->actors[slot];
        BreakKernelClass *cls = &kernel->classes[actor->class_id];
        Entity entity = actor->entity;
        if (cls->tick) {
            cls->tick(kernel, entity, dt, cls->tick_user);
        }
        if (break_kernel_actor_slot(kernel, entity) == slot &&
            cls->lua_module[0] != '\0' && kernel->script_bridge_used &&
            kernel->script_bridge.actor_tick) {
            kernel->script_bridge.actor_tick(kernel->script_bridge.user,
                                           cls->lua_module, entity, dt);
        }
    }
}
