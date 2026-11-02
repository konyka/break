#include <game/break_game_internal.h>

#define BREAK_GAME_MAX_STACK 1000000u
#define BREAK_GAME_INVENTORY_STRIDE (BREAK_GAME_MAX_ITEMS + 1u)

static BreakGameError item_error(const BreakGame *game, u32 item_id) {
    if (item_id == 0 || item_id > BREAK_GAME_MAX_ITEMS) {
        return BREAK_GAME_INVALID;
    }
    if (game->items[item_id].stack_limit == 0) {
        return BREAK_GAME_STALE;
    }
    return BREAK_GAME_OK;
}

static size_t inventory_index(u32 slot, u32 item_id) {
    return (size_t)slot * BREAK_GAME_INVENTORY_STRIDE + item_id;
}

void break_game_items_on_despawn(BreakGame *game, u32 slot) {
    if (!game || !game->inventories || slot >= game->max_actors) {
        return;
    }
    memset(game->inventories + inventory_index(slot, 0), 0,
           BREAK_GAME_INVENTORY_STRIDE * sizeof(*game->inventories));
}

BreakGameError break_game_item_define(BreakGame *game, const BreakGameItemDesc *desc) {
    if (!game || !desc) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    if (desc->item_id == 0 || desc->item_id > BREAK_GAME_MAX_ITEMS ||
        desc->stack_limit == 0 || desc->stack_limit > BREAK_GAME_MAX_STACK) {
        return BREAK_GAME_INVALID;
    }
    if (game->items[desc->item_id].stack_limit != 0) {
        return BREAK_GAME_REJECTED;
    }
    game->items[desc->item_id] = *desc;
    return BREAK_GAME_OK;
}

BreakGameError break_game_inventory_add(BreakGame *game, Entity entity, u32 item_id, u32 count) {
    if (!game || count == 0) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    BreakGameError item = item_error(game, item_id);
    if (item != BREAK_GAME_OK) {
        return item;
    }
    u32 slot = break_game_actor_slot(game, entity);
    if (slot == UINT32_MAX) {
        return BREAK_GAME_STALE;
    }
    size_t index = inventory_index(slot, item_id);
    u32 old_count = game->inventories[index];
    u32 limit = game->items[item_id].stack_limit;
    if (old_count > limit || count > limit - old_count) {
        return BREAK_GAME_OVERLOAD;
    }
    game->inventories[index] = old_count + count;
    return BREAK_GAME_OK;
}

BreakGameError break_game_inventory_count(BreakGame *game, Entity entity, u32 item_id, u32 *out_count) {
    if (!game || !out_count) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    BreakGameError item = item_error(game, item_id);
    if (item != BREAK_GAME_OK) {
        return item;
    }
    u32 slot = break_game_actor_slot(game, entity);
    if (slot == UINT32_MAX) {
        return BREAK_GAME_STALE;
    }
    *out_count = game->inventories[inventory_index(slot, item_id)];
    return BREAK_GAME_OK;
}

BreakGameError break_game_inventory_transfer(BreakGame *game, Entity from, Entity to,
                                             u32 item_id, u32 count) {
    if (!game || count == 0 || (from.index == to.index && from.generation == to.generation)) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    BreakGameError item = item_error(game, item_id);
    if (item != BREAK_GAME_OK) {
        return item;
    }
    u32 from_slot = break_game_actor_slot(game, from);
    u32 to_slot = break_game_actor_slot(game, to);
    if (from_slot == UINT32_MAX || to_slot == UINT32_MAX) {
        return BREAK_GAME_STALE;
    }
    size_t from_index = inventory_index(from_slot, item_id);
    size_t to_index = inventory_index(to_slot, item_id);
    u32 from_count = game->inventories[from_index];
    u32 to_count = game->inventories[to_index];
    u32 limit = game->items[item_id].stack_limit;
    if (from_count < count || to_count > limit || count > limit - to_count) {
        return BREAK_GAME_OVERLOAD;
    }
    game->inventories[from_index] = from_count - count;
    game->inventories[to_index] = to_count + count;
    return BREAK_GAME_OK;
}
