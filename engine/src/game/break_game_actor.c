#include <game/break_game_internal.h>

static BreakGameError occupy_slot(BreakGame *game, Entity entity, u32 class_id, u32 *out_slot) {
    if (game->live_count >= game->max_actors || game->free_top == 0) {
        return BREAK_GAME_OVERLOAD;
    }
    if (break_game_actor_slot(game, entity) != UINT32_MAX) {
        return BREAK_GAME_REJECTED;
    }
    if (entity.index >= ECS_MAX_ENTITIES) {
        return BREAK_GAME_FAILED;
    }
    u32 slot = game->free_stack[--game->free_top];
    game->actors[slot].entity = entity;
    game->actors[slot].class_id = class_id;
    game->actors[slot].alive = true;
    game->slot_of[entity.index] = slot;
    game->live_count++;
    *out_slot = slot;
    return BREAK_GAME_OK;
}

static BreakGameError add_class_components(BreakGame *game, Entity entity, const BreakGameClass *cls) {
    for (u32 i = 0; i < cls->component_count; i++) {
        ComponentType id = cls->components[i];
        if (game->world->component_sizes[id] == 0) {
            return BREAK_GAME_INVALID;
        }
        if (!world_add_component(game->world, entity, id)) {
            return BREAK_GAME_FAILED;
        }
    }
    return BREAK_GAME_OK;
}

BreakGameError break_game_adopt(BreakGame *game, Entity entity, u32 class_id) {
    if (class_id == 0 || class_id > game->class_count || !game->classes[class_id].used) {
        return BREAK_GAME_STALE;
    }
    if (!world_entity_exists(game->world, entity)) {
        return BREAK_GAME_STALE;
    }
    if (game->live_count >= game->max_actors) {
        return BREAK_GAME_OVERLOAD;
    }
    BreakGameError added = add_class_components(game, entity, &game->classes[class_id]);
    if (added != BREAK_GAME_OK) {
        return added;
    }
    u32 slot = 0;
    return occupy_slot(game, entity, class_id, &slot);
}

BreakGameError break_game_spawn(BreakGame *game, const BreakGameSpawn *spawn, Entity *out_entity) {
    if (!game || !spawn || !out_entity) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    if (spawn->class_id == 0 || spawn->class_id > game->class_count ||
        !game->classes[spawn->class_id].used) {
        return BREAK_GAME_STALE;
    }
    if (game->live_count >= game->max_actors || game->free_top == 0) {
        return BREAK_GAME_OVERLOAD;
    }
    const BreakGameClass *cls = &game->classes[spawn->class_id];
    for (u32 i = 0; i < cls->component_count; i++) {
        if (game->world->component_sizes[cls->components[i]] == 0) {
            return BREAK_GAME_INVALID;
        }
    }
    Entity entity = world_create_entity(game->world);
    if (!entity_valid(entity)) {
        return BREAK_GAME_FAILED;
    }
    BreakGameError added = add_class_components(game, entity, cls);
    if (added != BREAK_GAME_OK) {
        world_destroy_entity(game->world, entity);
        return added;
    }
    if (game->world->component_sizes[BREAK_GAME_POSITION_COMPONENT] >= sizeof(Vec3)) {
        void *pos = world_get_component(game->world, entity, BREAK_GAME_POSITION_COMPONENT);
        if (pos) {
            memcpy(pos, &spawn->position, sizeof(Vec3));
        }
    }
    u32 slot = 0;
    BreakGameError occupied = occupy_slot(game, entity, spawn->class_id, &slot);
    if (occupied != BREAK_GAME_OK) {
        world_destroy_entity(game->world, entity);
        return occupied;
    }
    *out_entity = entity;
    return BREAK_GAME_OK;
}

BreakGameError break_game_despawn(BreakGame *game, Entity entity) {
    if (!game) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    u32 slot = break_game_actor_slot(game, entity);
    if (slot == UINT32_MAX) {
        return BREAK_GAME_STALE;
    }
    break_game_area_on_despawn(game, slot, entity);
    break_game_weapons_on_despawn(game, slot);
    break_game_items_on_despawn(game, slot);
    world_destroy_entity(game->world, entity);
    game->actors[slot].alive = false;
    game->actors[slot].entity = ENTITY_NULL;
    game->slot_of[entity.index] = UINT32_MAX;
    game->free_stack[game->free_top++] = slot;
    if (game->live_count > 0) {
        game->live_count--;
    }
    return BREAK_GAME_OK;
}

void break_game_set_tick(BreakGame *game, u32 class_id, BreakGameTickFn fn, void *user) {
    if (!game || !break_game_is_owner(game)) {
        return;
    }
    if (class_id == 0 || class_id > game->class_count || !game->classes[class_id].used) {
        return;
    }
    game->classes[class_id].tick = fn;
    game->classes[class_id].tick_user = user;
}

void break_game_tick(BreakGame *game, f32 dt) {
    if (!game || !break_game_is_owner(game)) {
        return;
    }
    u32 n = 0;
    for (u32 slot = 0; slot < game->max_actors; slot++) {
        if (game->actors[slot].alive) {
            game->tick_snapshot[n++] = slot;
        }
    }
    for (u32 i = 0; i < n; i++) {
        u32 slot = game->tick_snapshot[i];
        if (!game->actors[slot].alive) {
            continue;
        }
        BreakGameActor *actor = &game->actors[slot];
        BreakGameClass *cls = &game->classes[actor->class_id];
        if (cls->tick) {
            cls->tick(game, actor->entity, dt, cls->tick_user);
        }
    }
}
