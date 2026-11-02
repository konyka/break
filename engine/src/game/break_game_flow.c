#include <game/break_game_internal.h>

#include <math.h>

#define INVENTORY_STRIDE (BREAK_GAME_MAX_ITEMS + 1u)

static size_t inventory_index(u32 slot, u32 item_id) {
    return (size_t)slot * INVENTORY_STRIDE + item_id;
}

BreakGameError break_game_entity_actions_apply(BreakGame *game,
                                               const BreakGameEntityAction *actions,
                                               u32 count) {
    if (!game || (count > 0u && !actions)) return BREAK_GAME_INVALID;
    if (!break_game_is_owner(game)) return BREAK_GAME_REJECTED;
    if (count > BREAK_GAME_MAX_ENTITY_ACTIONS) return BREAK_GAME_OVERLOAD;
    for (u32 i = 0u; i < count; i++) {
        const BreakGameEntityAction *action = &actions[i];
        u32 slot = break_game_actor_slot(game, action->entity);
        if (slot == UINT32_MAX) return BREAK_GAME_STALE;
        if (action->type == BREAK_GAME_ENTITY_SET_POSITION) {
            if (!isfinite(action->position.e[0]) ||
                !isfinite(action->position.e[1]) ||
                !isfinite(action->position.e[2])) {
                return BREAK_GAME_INVALID;
            }
            if (game->world->component_sizes[BREAK_GAME_POSITION_COMPONENT] < sizeof(Vec3) ||
                !world_get_component(game->world, action->entity,
                                     BREAK_GAME_POSITION_COMPONENT)) {
                return BREAK_GAME_FAILED;
            }
        } else if (action->type == BREAK_GAME_ENTITY_INVENTORY_ADD) {
            if (action->item_id == 0u || action->item_id > BREAK_GAME_MAX_ITEMS ||
                action->count == 0u) {
                return BREAK_GAME_INVALID;
            }
            u32 limit = game->items[action->item_id].stack_limit;
            if (limit == 0u) return BREAK_GAME_STALE;
            u64 total = game->inventories[inventory_index(slot, action->item_id)];
            for (u32 k = 0u; k < i; k++) {
                const BreakGameEntityAction *prior = &actions[k];
                if (prior->type == BREAK_GAME_ENTITY_INVENTORY_ADD &&
                    prior->item_id == action->item_id &&
                    break_game_actor_slot(game, prior->entity) == slot) {
                    total += prior->count;
                }
            }
            total += action->count;
            if (total > limit) return BREAK_GAME_OVERLOAD;
        } else {
            return BREAK_GAME_INVALID;
        }
    }
    for (u32 i = 0u; i < count; i++) {
        const BreakGameEntityAction *action = &actions[i];
        u32 slot = break_game_actor_slot(game, action->entity);
        if (action->type == BREAK_GAME_ENTITY_SET_POSITION) {
            void *position = world_get_component(game->world, action->entity,
                                                 BREAK_GAME_POSITION_COMPONENT);
            memcpy(position, &action->position, sizeof(action->position));
        } else {
            game->inventories[inventory_index(slot, action->item_id)] += action->count;
        }
    }
    return BREAK_GAME_OK;
}
