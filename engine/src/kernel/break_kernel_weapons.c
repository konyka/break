#include <kernel/break_kernel_internal.h>

static BreakKernelError weapon_error(const BreakKernel *kernel, u32 weapon_id) {
    if (weapon_id == 0 || weapon_id > BREAK_KERNEL_MAX_ITEMS) {
        return BREAK_KERNEL_INVALID;
    }
    if (kernel->weapons[weapon_id].weapon_id == 0) {
        return BREAK_KERNEL_STALE;
    }
    return BREAK_KERNEL_OK;
}

static BreakKernelError equipped_slot(const BreakKernel *kernel, Entity entity, u32 *out_slot) {
    u32 slot = break_kernel_actor_slot(kernel, entity);
    if (slot == UINT32_MAX) {
        return BREAK_KERNEL_STALE;
    }
    if (kernel->actors[slot].weapon_id == 0) {
        return BREAK_KERNEL_REJECTED;
    }
    BreakKernelError weapon = weapon_error(kernel, kernel->actors[slot].weapon_id);
    if (weapon != BREAK_KERNEL_OK) {
        return weapon;
    }
    *out_slot = slot;
    return BREAK_KERNEL_OK;
}

static void clear_weapon(BreakKernelActor *actor) {
    actor->weapon_id = 0;
    actor->magazine = 0;
    actor->now_tick = 0;
    actor->next_fire_tick = 0;
    actor->reload_finish_tick = 0;
    actor->reloading = false;
}

static void clear_equipment(BreakKernelActor *actor) {
    actor->weapon_id = 0;
    actor->magazine = 0;
    actor->reload_finish_tick = 0;
    actor->reloading = false;
}

void break_kernel_weapons_on_despawn(BreakKernel *kernel, u32 slot) {
    if (!kernel || !kernel->actors || slot >= kernel->max_actors) {
        return;
    }
    clear_weapon(&kernel->actors[slot]);
}

BreakKernelError break_kernel_weapon_define(BreakKernel *kernel, const BreakKernelWeaponDesc *desc) {
    if (!kernel || !desc) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    if (desc->weapon_id == 0 || desc->weapon_id > BREAK_KERNEL_MAX_ITEMS ||
        desc->ammo_item_id == 0 || desc->ammo_item_id > BREAK_KERNEL_MAX_ITEMS ||
        desc->damage == 0 || desc->damage > 10000u ||
        desc->magazine_capacity == 0 || desc->magazine_capacity > 1000u ||
        desc->reload_ticks == 0) {
        return BREAK_KERNEL_INVALID;
    }
    if (kernel->items[desc->ammo_item_id].stack_limit == 0) {
        return BREAK_KERNEL_STALE;
    }
    if (kernel->weapons[desc->weapon_id].weapon_id != 0) {
        return BREAK_KERNEL_REJECTED;
    }
    kernel->weapons[desc->weapon_id] = *desc;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_weapon_equip(BreakKernel *kernel, Entity entity, u32 weapon_id) {
    if (!kernel) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    BreakKernelError weapon = weapon_error(kernel, weapon_id);
    if (weapon != BREAK_KERNEL_OK) {
        return weapon;
    }
    u32 slot = break_kernel_actor_slot(kernel, entity);
    if (slot == UINT32_MAX) {
        return BREAK_KERNEL_STALE;
    }
    BreakKernelActor *actor = &kernel->actors[slot];
    if (actor->weapon_id != 0) {
        return BREAK_KERNEL_REJECTED;
    }
    clear_equipment(actor);
    actor->weapon_id = weapon_id;
    actor->magazine = 0;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_weapon_unequip(BreakKernel *kernel, Entity entity) {
    if (!kernel) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    u32 slot = 0;
    BreakKernelError equipped = equipped_slot(kernel, entity, &slot);
    if (equipped != BREAK_KERNEL_OK) {
        return equipped;
    }
    BreakKernelActor *actor = &kernel->actors[slot];
    if (actor->magazine != 0) {
        u32 ammo_item_id = kernel->weapons[actor->weapon_id].ammo_item_id;
        BreakKernelError added = break_kernel_items_add_slot(kernel, slot, ammo_item_id, actor->magazine);
        if (added != BREAK_KERNEL_OK) {
            return added;
        }
    }
    clear_equipment(actor);
    return BREAK_KERNEL_OK;
}

static BreakKernelError complete_reload(BreakKernel *kernel, u32 slot, u32 now_tick) {
    BreakKernelActor *actor = &kernel->actors[slot];
    const BreakKernelWeaponDesc *weapon = &kernel->weapons[actor->weapon_id];
    u32 needed = weapon->magazine_capacity - actor->magazine;
    if (needed == 0) {
        actor->now_tick = now_tick;
        actor->reloading = false;
        actor->reload_finish_tick = 0;
        return BREAK_KERNEL_OK;
    }
    BreakKernelError removed = break_kernel_items_remove_slot(kernel, slot, weapon->ammo_item_id, needed);
    if (removed != BREAK_KERNEL_OK) {
        return removed;
    }
    actor->now_tick = now_tick;
    actor->magazine += needed;
    actor->reloading = false;
    actor->reload_finish_tick = 0;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_weapon_begin_reload(BreakKernel *kernel, Entity entity) {
    if (!kernel) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    u32 slot = 0;
    BreakKernelError equipped = equipped_slot(kernel, entity, &slot);
    if (equipped != BREAK_KERNEL_OK) {
        return equipped;
    }
    BreakKernelActor *actor = &kernel->actors[slot];
    const BreakKernelWeaponDesc *weapon = &kernel->weapons[actor->weapon_id];
    if (actor->reloading) {
        if (actor->now_tick < actor->reload_finish_tick) {
            return BREAK_KERNEL_REJECTED;
        }
        return complete_reload(kernel, slot, actor->now_tick);
    }
    if (actor->magazine >= weapon->magazine_capacity) {
        return BREAK_KERNEL_REJECTED;
    }
    u32 reserve = 0;
    BreakKernelError counted = break_kernel_inventory_count(kernel, entity, weapon->ammo_item_id, &reserve);
    if (counted != BREAK_KERNEL_OK) {
        return counted;
    }
    if (reserve == 0) {
        return BREAK_KERNEL_REJECTED;
    }
    if (weapon->reload_ticks > UINT32_MAX - actor->now_tick) {
        return BREAK_KERNEL_OVERLOAD;
    }
    actor->reload_finish_tick = actor->now_tick + weapon->reload_ticks;
    actor->reloading = true;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_weapon_tick(BreakKernel *kernel, Entity entity, u32 elapsed_ticks) {
    if (!kernel || elapsed_ticks == 0) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    u32 slot = 0;
    BreakKernelError equipped = equipped_slot(kernel, entity, &slot);
    if (equipped != BREAK_KERNEL_OK) {
        return equipped;
    }
    BreakKernelActor *actor = &kernel->actors[slot];
    if (elapsed_ticks > UINT32_MAX - actor->now_tick) {
        return BREAK_KERNEL_OVERLOAD;
    }
    u32 now_tick = actor->now_tick + elapsed_ticks;
    if (!actor->reloading || now_tick < actor->reload_finish_tick) {
        actor->now_tick = now_tick;
        return BREAK_KERNEL_OK;
    }
    return complete_reload(kernel, slot, now_tick);
}

BreakKernelError break_kernel_weapon_fire(BreakKernel *kernel, Entity entity, BreakKernelFireIntent *out_intent) {
    if (!kernel || !out_intent) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    u32 slot = 0;
    BreakKernelError equipped = equipped_slot(kernel, entity, &slot);
    if (equipped != BREAK_KERNEL_OK) {
        return equipped;
    }
    BreakKernelActor *actor = &kernel->actors[slot];
    if (actor->reloading || actor->magazine == 0 || actor->now_tick < actor->next_fire_tick) {
        return BREAK_KERNEL_REJECTED;
    }
    if (kernel->fire_sequence == UINT64_MAX) {
        return BREAK_KERNEL_OVERLOAD;
    }
    const BreakKernelWeaponDesc *weapon = &kernel->weapons[actor->weapon_id];
    if (weapon->fire_interval_ticks > UINT32_MAX - actor->now_tick) {
        return BREAK_KERNEL_OVERLOAD;
    }
    u32 next_fire_tick = actor->now_tick + weapon->fire_interval_ticks;
    u64 sequence = kernel->fire_sequence + 1u;
    actor->magazine--;
    actor->next_fire_tick = next_fire_tick;
    kernel->fire_sequence = sequence;
    out_intent->shooter = entity;
    out_intent->weapon_id = actor->weapon_id;
    out_intent->damage = weapon->damage;
    out_intent->sequence = sequence;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_weapon_ammo(const BreakKernel *kernel, Entity entity, u32 *out_magazine) {
    if (!kernel || !out_magazine) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    u32 slot = 0;
    BreakKernelError equipped = equipped_slot(kernel, entity, &slot);
    if (equipped != BREAK_KERNEL_OK) {
        return equipped;
    }
    *out_magazine = kernel->actors[slot].magazine;
    return BREAK_KERNEL_OK;
}
