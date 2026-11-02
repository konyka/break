#pragma once
#include <game/break_game.h>
#include <core/platform_thread.h>
#include <string.h>

typedef struct BreakGameClass {
    char name[BREAK_GAME_NAME_CAP];
    char lua_module[BREAK_GAME_NAME_CAP];
    ComponentType components[BREAK_GAME_MAX_CLASS_COMPONENTS];
    u32 component_count;
    bool used;
    BreakGameTickFn tick;
    void *tick_user;
} BreakGameClass;

typedef struct BreakGameActor {
    Entity entity;
    u32 class_id;
    bool alive;
} BreakGameActor;

typedef struct BreakGameAction {
    char name[BREAK_GAME_NAME_CAP];
    BreakGameBinding bindings[BREAK_GAME_HARD_MAX_BINDINGS];
    u32 binding_count;
} BreakGameAction;

typedef struct BreakGameArea {
    BreakGameAreaDesc desc;
    bool aabb;
    bool used;
} BreakGameArea;

typedef struct BreakGameAdopted {
    Entity entity;
    u32 class_id;
} BreakGameAdopted;

struct BreakGame {
    World *world;
    PlatformThreadId owner;
    u32 max_classes;
    u32 max_actors;
    BreakGameClass *classes; /* index 0 unused; ids are 1..max_classes */
    u32 class_count;
    BreakGameActor *actors;
    BreakGameItemDesc items[BREAK_GAME_MAX_ITEMS + 1u];
    u32 *inventories; /* actor_slot * (BREAK_GAME_MAX_ITEMS + 1) + item_id */
    u32 *free_stack;
    u32 free_top;
    u32 live_count;
    u32 *slot_of; /* ECS_MAX_ENTITIES, UINT32_MAX = empty */
    u32 *tick_snapshot;
    BreakGameAction actions[BREAK_GAME_HARD_MAX_ACTIONS];
    u32 action_count;
    bool level_open;
    BreakGameLevelHooks level_hooks;
    BreakGameArea areas[BREAK_GAME_HARD_MAX_AREAS];
    u32 area_count;
    u8 *inside; /* area_count stride is max_actors */
    BreakGameAreaFn area_fn;
    void *area_user;
};

bool break_game_is_owner(const BreakGame *game);
u32 break_game_actor_slot(const BreakGame *game, Entity entity);
bool break_game_copy_name(const char *src, char *dst, bool allow_empty);

void break_game_area_on_despawn(BreakGame *game, u32 slot, Entity entity);
void break_game_items_on_despawn(BreakGame *game, u32 slot);

BreakGameError break_game_adopt(BreakGame *game, Entity entity, u32 class_id);
