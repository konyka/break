#include <game/break_game_internal.h>
#include <stdlib.h>

bool break_game_is_owner(const BreakGame *game) {
    return game && platform_thread_id_equal(game->owner, platform_thread_current_id());
}

u32 break_game_actor_slot(const BreakGame *game, Entity entity) {
    if (!game || entity.index == 0 || entity.index >= ECS_MAX_ENTITIES) {
        return UINT32_MAX;
    }
    u32 slot = game->slot_of[entity.index];
    if (slot >= game->max_actors) {
        return UINT32_MAX;
    }
    if (!game->actors[slot].alive) {
        return UINT32_MAX;
    }
    if (game->actors[slot].entity.index != entity.index ||
        game->actors[slot].entity.generation != entity.generation) {
        return UINT32_MAX;
    }
    return slot;
}

bool break_game_copy_name(const char *src, char *dst, bool allow_empty) {
    if (!src) {
        return allow_empty;
    }
    u32 n = 0;
    while (src[n] != '\0') {
        unsigned char c = (unsigned char)src[n];
        if (n >= BREAK_GAME_NAME_CAP - 1u || c <= ' ' || c == '#') {
            return false;
        }
        n++;
    }
    if (n == 0) {
        return allow_empty;
    }
    memcpy(dst, src, n);
    dst[n] = '\0';
    return true;
}

static void break_game_free(BreakGame *game) {
    if (!game) {
        return;
    }
    free(game->classes);
    free(game->actors);
    free(game->inventories);
    free(game->free_stack);
    free(game->slot_of);
    free(game->tick_snapshot);
    free(game->inside);
    free(game);
}

BreakGame *break_game_create(World *world, const BreakGameConfig *config) {
    if (!world) {
        return NULL;
    }
    u32 max_classes = BREAK_GAME_HARD_MAX_CLASSES;
    u32 max_actors = BREAK_GAME_HARD_MAX_ACTORS;
    if (config) {
        if (config->max_classes != 0) {
            max_classes = config->max_classes;
        }
        if (config->max_actors != 0) {
            max_actors = config->max_actors;
        }
    }
    if (max_classes > BREAK_GAME_HARD_MAX_CLASSES || max_actors > BREAK_GAME_HARD_MAX_ACTORS ||
        max_classes == 0 || max_actors == 0) {
        return NULL;
    }

    size_t inventory_stride = (size_t)BREAK_GAME_MAX_ITEMS + 1u;
    if ((size_t)max_actors > SIZE_MAX / inventory_stride) {
        return NULL;
    }
    size_t inventory_count = (size_t)max_actors * inventory_stride;
    if (inventory_count > SIZE_MAX / sizeof(u32)) {
        return NULL;
    }

    BreakGame *game = (BreakGame *)calloc(1, sizeof(BreakGame));
    if (!game) {
        return NULL;
    }
    game->world = world;
    game->owner = platform_thread_current_id();
    game->max_classes = max_classes;
    game->max_actors = max_actors;
    game->classes = (BreakGameClass *)calloc((size_t)max_classes + 1u, sizeof(BreakGameClass));
    game->actors = (BreakGameActor *)calloc(max_actors, sizeof(BreakGameActor));
    game->inventories = (u32 *)calloc(inventory_count, sizeof(u32));
    game->free_stack = (u32 *)calloc(max_actors, sizeof(u32));
    game->slot_of = (u32 *)malloc(sizeof(u32) * ECS_MAX_ENTITIES);
    game->tick_snapshot = (u32 *)calloc(max_actors, sizeof(u32));
    game->inside = (u8 *)calloc((size_t)BREAK_GAME_HARD_MAX_AREAS * (size_t)max_actors, 1);
    if (!game->classes || !game->actors || !game->inventories || !game->free_stack ||
        !game->slot_of || !game->tick_snapshot || !game->inside) {
        break_game_free(game);
        return NULL;
    }
    memset(game->slot_of, 0xFF, sizeof(u32) * ECS_MAX_ENTITIES);
    for (u32 i = 0; i < max_actors; i++) {
        game->free_stack[i] = max_actors - 1u - i;
    }
    game->free_top = max_actors;
    return game;
}

void break_game_destroy(BreakGame *game) {
    if (!game || !break_game_is_owner(game)) {
        return;
    }
    break_game_free(game);
}

BreakGameError break_game_register_class(BreakGame *game, const BreakGameClassDesc *desc, u32 *out_class_id) {
    if (!game || !desc || !out_class_id) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    char name[BREAK_GAME_NAME_CAP];
    char lua_module[BREAK_GAME_NAME_CAP];
    memset(name, 0, sizeof(name));
    memset(lua_module, 0, sizeof(lua_module));
    if (!break_game_copy_name(desc->name, name, false)) {
        return BREAK_GAME_INVALID;
    }
    if (desc->lua_module && !break_game_copy_name(desc->lua_module, lua_module, false)) {
        return BREAK_GAME_INVALID;
    }
    if (desc->component_count > BREAK_GAME_MAX_CLASS_COMPONENTS) {
        return BREAK_GAME_INVALID;
    }
    if (desc->component_count > 0 && !desc->components) {
        return BREAK_GAME_INVALID;
    }
    for (u32 i = 0; i < desc->component_count; i++) {
        if (desc->components[i] >= ECS_MAX_COMPONENTS) {
            return BREAK_GAME_INVALID;
        }
    }
    for (u32 i = 1; i <= game->class_count; i++) {
        if (game->classes[i].used && strcmp(game->classes[i].name, name) == 0) {
            return BREAK_GAME_REJECTED;
        }
    }
    if (game->class_count >= game->max_classes) {
        return BREAK_GAME_OVERLOAD;
    }
    u32 id = game->class_count + 1u;
    BreakGameClass *cls = &game->classes[id];
    memset(cls, 0, sizeof(*cls));
    memcpy(cls->name, name, sizeof(name));
    memcpy(cls->lua_module, lua_module, sizeof(lua_module));
    cls->component_count = desc->component_count;
    if (desc->component_count > 0) {
        memcpy(cls->components, desc->components, desc->component_count * sizeof(ComponentType));
    }
    cls->used = true;
    game->class_count = id;
    *out_class_id = id;
    return BREAK_GAME_OK;
}
