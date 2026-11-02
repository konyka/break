#include <game/break_game_internal.h>

static BreakGameError weapon_error(const BreakGame *game, u32 weapon_id) {
    if (weapon_id == 0 || weapon_id > BREAK_GAME_MAX_ITEMS) {
        return BREAK_GAME_INVALID;
    }
    if (game->weapons[weapon_id].weapon_id == 0) {
        return BREAK_GAME_STALE;
    }
    return BREAK_GAME_OK;
}

static BreakGameError equipped_slot(const BreakGame *game, Entity entity, u32 *out_slot) {
    u32 slot = break_game_actor_slot(game, entity);
    if (slot == UINT32_MAX) {
        return BREAK_GAME_STALE;
    }
    if (game->actors[slot].weapon_id == 0) {
        return BREAK_GAME_REJECTED;
    }
    BreakGameError weapon = weapon_error(game, game->actors[slot].weapon_id);
    if (weapon != BREAK_GAME_OK) {
        return weapon;
    }
    *out_slot = slot;
    return BREAK_GAME_OK;
}

static void clear_weapon(BreakGameActor *actor) {
    actor->weapon_id = 0;
    actor->magazine = 0;
    actor->now_tick = 0;
    actor->next_fire_tick = 0;
    actor->reload_finish_tick = 0;
    actor->reloading = false;
}

void break_game_weapons_on_despawn(BreakGame *game, u32 slot) {
    if (!game || !game->actors || slot >= game->max_actors) {
        return;
    }
    clear_weapon(&game->actors[slot]);
}

BreakGameError break_game_weapon_define(BreakGame *game, const BreakGameWeaponDesc *desc) {
    if (!game || !desc) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    if (desc->weapon_id == 0 || desc->weapon_id > BREAK_GAME_MAX_ITEMS ||
        desc->ammo_item_id == 0 || desc->ammo_item_id > BREAK_GAME_MAX_ITEMS ||
        desc->damage == 0 || desc->damage > 10000u ||
        desc->magazine_capacity == 0 || desc->magazine_capacity > 1000u ||
        desc->reload_ticks == 0) {
        return BREAK_GAME_INVALID;
    }
    if (game->items[desc->ammo_item_id].stack_limit == 0) {
        return BREAK_GAME_STALE;
    }
    if (game->weapons[desc->weapon_id].weapon_id != 0) {
        return BREAK_GAME_REJECTED;
    }
    game->weapons[desc->weapon_id] = *desc;
    return BREAK_GAME_OK;
}

BreakGameError break_game_weapon_equip(BreakGame *game, Entity entity, u32 weapon_id) {
    if (!game) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    BreakGameError weapon = weapon_error(game, weapon_id);
    if (weapon != BREAK_GAME_OK) {
        return weapon;
    }
    u32 slot = break_game_actor_slot(game, entity);
    if (slot == UINT32_MAX) {
        return BREAK_GAME_STALE;
    }
    BreakGameActor *actor = &game->actors[slot];
    if (actor->weapon_id != 0) {
        return BREAK_GAME_REJECTED;
    }
    clear_weapon(actor);
    actor->weapon_id = weapon_id;
    actor->magazine = game->weapons[weapon_id].magazine_capacity;
    return BREAK_GAME_OK;
}

BreakGameError break_game_weapon_unequip(BreakGame *game, Entity entity) {
    if (!game) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    u32 slot = 0;
    BreakGameError equipped = equipped_slot(game, entity, &slot);
    if (equipped != BREAK_GAME_OK) {
        return equipped;
    }
    BreakGameActor *actor = &game->actors[slot];
    if (actor->magazine != 0) {
        u32 ammo_item_id = game->weapons[actor->weapon_id].ammo_item_id;
        BreakGameError added = break_game_items_add_slot(game, slot, ammo_item_id, actor->magazine);
        if (added != BREAK_GAME_OK) {
            return added;
        }
    }
    clear_weapon(actor);
    return BREAK_GAME_OK;
}

static BreakGameError complete_reload(BreakGame *game, u32 slot) {
    BreakGameActor *actor = &game->actors[slot];
    const BreakGameWeaponDesc *weapon = &game->weapons[actor->weapon_id];
    u32 needed = weapon->magazine_capacity - actor->magazine;
    if (needed == 0) {
        actor->reloading = false;
        actor->reload_finish_tick = 0;
        return BREAK_GAME_OK;
    }
    BreakGameError removed = break_game_items_remove_slot(game, slot, weapon->ammo_item_id, needed);
    if (removed != BREAK_GAME_OK) {
        return removed;
    }
    actor->magazine += needed;
    actor->reloading = false;
    actor->reload_finish_tick = 0;
    return BREAK_GAME_OK;
}

BreakGameError break_game_weapon_begin_reload(BreakGame *game, Entity entity) {
    if (!game) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    u32 slot = 0;
    BreakGameError equipped = equipped_slot(game, entity, &slot);
    if (equipped != BREAK_GAME_OK) {
        return equipped;
    }
    BreakGameActor *actor = &game->actors[slot];
    const BreakGameWeaponDesc *weapon = &game->weapons[actor->weapon_id];
    if (actor->reloading) {
        if (actor->now_tick < actor->reload_finish_tick) {
            return BREAK_GAME_REJECTED;
        }
        return complete_reload(game, slot);
    }
    if (actor->magazine >= weapon->magazine_capacity) {
        return BREAK_GAME_REJECTED;
    }
    u32 reserve = 0;
    BreakGameError counted = break_game_inventory_count(game, entity, weapon->ammo_item_id, &reserve);
    if (counted != BREAK_GAME_OK) {
        return counted;
    }
    if (reserve == 0) {
        return BREAK_GAME_REJECTED;
    }
    if (weapon->reload_ticks > UINT32_MAX - actor->now_tick) {
        return BREAK_GAME_OVERLOAD;
    }
    actor->reload_finish_tick = actor->now_tick + weapon->reload_ticks;
    actor->reloading = true;
    return BREAK_GAME_OK;
}

BreakGameError break_game_weapon_tick(BreakGame *game, Entity entity, u32 elapsed_ticks) {
    if (!game || elapsed_ticks == 0) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    u32 slot = 0;
    BreakGameError equipped = equipped_slot(game, entity, &slot);
    if (equipped != BREAK_GAME_OK) {
        return equipped;
    }
    BreakGameActor *actor = &game->actors[slot];
    if (elapsed_ticks > UINT32_MAX - actor->now_tick) {
        return BREAK_GAME_OVERLOAD;
    }
    actor->now_tick += elapsed_ticks;
    if (!actor->reloading || actor->now_tick < actor->reload_finish_tick) {
        return BREAK_GAME_OK;
    }
    return complete_reload(game, slot);
}

BreakGameError break_game_weapon_fire(BreakGame *game, Entity entity, BreakGameFireIntent *out_intent) {
    if (!game || !out_intent) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    u32 slot = 0;
    BreakGameError equipped = equipped_slot(game, entity, &slot);
    if (equipped != BREAK_GAME_OK) {
        return equipped;
    }
    BreakGameActor *actor = &game->actors[slot];
    if (actor->reloading || actor->magazine == 0 || actor->now_tick < actor->next_fire_tick) {
        return BREAK_GAME_REJECTED;
    }
    if (game->fire_sequence == UINT64_MAX) {
        return BREAK_GAME_OVERLOAD;
    }
    const BreakGameWeaponDesc *weapon = &game->weapons[actor->weapon_id];
    if (weapon->fire_interval_ticks > UINT32_MAX - actor->now_tick) {
        return BREAK_GAME_OVERLOAD;
    }
    u32 next_fire_tick = actor->now_tick + weapon->fire_interval_ticks;
    u64 sequence = game->fire_sequence + 1u;
    actor->magazine--;
    actor->next_fire_tick = next_fire_tick;
    game->fire_sequence = sequence;
    out_intent->shooter = entity;
    out_intent->weapon_id = actor->weapon_id;
    out_intent->damage = weapon->damage;
    out_intent->sequence = sequence;
    return BREAK_GAME_OK;
}

BreakGameError break_game_weapon_ammo(const BreakGame *game, Entity entity, u32 *out_magazine) {
    if (!game || !out_magazine) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    u32 slot = 0;
    BreakGameError equipped = equipped_slot(game, entity, &slot);
    if (equipped != BREAK_GAME_OK) {
        return equipped;
    }
    *out_magazine = game->actors[slot].magazine;
    return BREAK_GAME_OK;
}
