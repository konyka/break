#pragma once
/*
 * Gameplay kernel for a Cry-style playable prototype.
 * One BreakGame borrows a World, is owned by the creating thread, and is
 * not linked into engine / engine_demo / dxx_break.
 */
#include <core/types.h>
#include <ecs/ecs.h>
#include <math/math.h>
#include <platform/input.h>

#define BREAK_GAME_HARD_MAX_CLASSES 64u
#define BREAK_GAME_HARD_MAX_ACTORS  4096u
#define BREAK_GAME_HARD_MAX_ACTIONS 64u
#define BREAK_GAME_HARD_MAX_BINDINGS 8u
#define BREAK_GAME_HARD_MAX_AREAS   256u
#define BREAK_GAME_NAME_CAP         64u
#define BREAK_GAME_MAX_CLASS_COMPONENTS 16u
#define BREAK_GAME_POSITION_COMPONENT ((ComponentType)0)
#define BREAK_GAME_AREA_EVENT_CAP   64u
#define BREAK_GAME_AREA_HYSTERESIS  0.25f
#define BREAK_GAME_MAX_ITEMS        64u

typedef enum BreakGameError {
    BREAK_GAME_OK = 0,
    BREAK_GAME_INVALID,
    BREAK_GAME_CLOSED,
    BREAK_GAME_OVERLOAD,
    BREAK_GAME_OOM,
    BREAK_GAME_TIMEOUT,
    BREAK_GAME_STALE,
    BREAK_GAME_REJECTED,
    BREAK_GAME_FAILED
} BreakGameError;

typedef struct BreakGame BreakGame;

typedef struct BreakGameConfig {
    u32 max_classes; /* 0 => 64, hard cap 64 */
    u32 max_actors;  /* 0 => 4096, hard cap 4096 */
} BreakGameConfig;

typedef struct BreakGameItemDesc {
    u32 item_id;     /* 1..64 */
    u32 stack_limit; /* 1..1000000 */
} BreakGameItemDesc;

typedef struct BreakGameWeaponDesc {
    u32 weapon_id;         /* 1..64 */
    u32 ammo_item_id;      /* defined item */
    u32 damage;            /* 1..10000, host configured */
    u32 magazine_capacity; /* 1..1000 */
    u32 fire_interval_ticks;
    u32 reload_ticks;      /* >= 1 */
} BreakGameWeaponDesc;

typedef struct BreakGameFireIntent {
    Entity shooter;
    u32 weapon_id;
    u32 damage;
    u64 sequence;          /* from 1, monotonic across BreakGame */
} BreakGameFireIntent;

typedef struct BreakGameClassDesc {
    const char *name;                /* 1..63 bytes, no whitespace */
    const ComponentType *components; /* may be NULL when count is 0 */
    u32 component_count;             /* hard cap 16 */
    const char *lua_module;          /* stored only; NULL allowed */
} BreakGameClassDesc;

typedef void (*BreakGameTickFn)(BreakGame *game, Entity entity, f32 dt, void *user);

typedef struct BreakGameScriptBridge {
    void *user;
    void (*actor_tick)(void *user, const char *module, Entity entity, f32 dt);
    void (*actor_despawn)(void *user, Entity entity);
} BreakGameScriptBridge;

BreakGameError break_game_set_script_bridge(
    BreakGame *game, const BreakGameScriptBridge *bridge);

typedef struct BreakGameSpawn {
    u32 class_id;
    Vec3 position;
} BreakGameSpawn;

typedef enum BreakGameBindSource {
    BREAK_GAME_BIND_KEY = 1,
    BREAK_GAME_BIND_MOUSE_BUTTON,
    BREAK_GAME_BIND_MOUSE_AXIS, /* 0 = dx, 1 = dy, 2 = wheel */
    BREAK_GAME_BIND_PAD_BUTTON,
    BREAK_GAME_BIND_PAD_AXIS
} BreakGameBindSource;

typedef struct BreakGameBinding {
    BreakGameBindSource source;
    i32 code;
    i32 pad;   /* pad sources only; other sources must be 0 */
    f32 scale;
} BreakGameBinding;

typedef struct BreakGameActionDesc {
    const char *name;
    const BreakGameBinding *bindings;
    u32 binding_count; /* hard cap 8 */
} BreakGameActionDesc;

typedef struct BreakGameActionValue {
    bool down;
    f32 axis;
} BreakGameActionValue;

typedef struct BreakGameMoveInput {
    f32 forward;    /* [-1, 1] */
    f32 strafe;     /* [-1, 1] */
    f32 camera_yaw; /* radians; 0 faces +Z */
    bool jump;
} BreakGameMoveInput;

typedef struct BreakGameMoveOutput {
    Vec3 wish; /* world XZ, y = 0, length at most 1 */
    bool jump;
    f32 yaw;
} BreakGameMoveOutput;

typedef BreakGameError (*BreakGameLevelLoadFn)(void *user, World *world, const char *path);
typedef void (*BreakGameLevelUnloadFn)(void *user, World *world);

typedef struct BreakGameLevelHooks {
    BreakGameLevelLoadFn load;
    BreakGameLevelUnloadFn unload;
    void *user;
} BreakGameLevelHooks;

typedef enum BreakGameAreaEvent {
    BREAK_GAME_AREA_ENTER = 1,
    BREAK_GAME_AREA_LEAVE = 2
} BreakGameAreaEvent;

typedef struct BreakGameAreaDesc {
    Vec3 center;
    Vec3 half_extent; /* any component > 0 selects an AABB; all 0 selects a sphere */
    f32 radius;
} BreakGameAreaDesc;

typedef void (*BreakGameAreaFn)(u32 area_id, Entity entity, BreakGameAreaEvent event, void *user);

BreakGame *break_game_create(World *world, const BreakGameConfig *config);
void       break_game_destroy(BreakGame *game);

BreakGameError break_game_register_class(BreakGame *game,
                                         const BreakGameClassDesc *desc,
                                         u32 *out_class_id);

BreakGameError break_game_spawn(BreakGame *game, const BreakGameSpawn *spawn, Entity *out_entity);
BreakGameError break_game_despawn(BreakGame *game, Entity entity);
void           break_game_set_tick(BreakGame *game, u32 class_id, BreakGameTickFn fn, void *user);
void           break_game_tick(BreakGame *game, f32 dt);

BreakGameError break_game_item_define(BreakGame *game,
                                      const BreakGameItemDesc *desc);
BreakGameError break_game_inventory_add(BreakGame *game, Entity entity,
                                        u32 item_id, u32 count);
BreakGameError break_game_inventory_count(BreakGame *game, Entity entity,
                                          u32 item_id, u32 *out_count);
BreakGameError break_game_inventory_transfer(BreakGame *game,
                                             Entity from, Entity to,
                                             u32 item_id, u32 count);

BreakGameError break_game_weapon_define(BreakGame *game,
                                        const BreakGameWeaponDesc *desc);
BreakGameError break_game_weapon_equip(BreakGame *game, Entity entity,
                                       u32 weapon_id);
BreakGameError break_game_weapon_unequip(BreakGame *game, Entity entity);
BreakGameError break_game_weapon_begin_reload(BreakGame *game, Entity entity);
BreakGameError break_game_weapon_tick(BreakGame *game, Entity entity,
                                      u32 elapsed_ticks);
BreakGameError break_game_weapon_fire(BreakGame *game, Entity entity,
                                      BreakGameFireIntent *out_intent);
BreakGameError break_game_weapon_ammo(const BreakGame *game, Entity entity,
                                      u32 *out_magazine);

BreakGameError break_game_bind_actions(BreakGame *game,
                                       const BreakGameActionDesc *actions,
                                       u32 count);
BreakGameError break_game_eval_actions(BreakGame *game, const InputState *input,
                                       BreakGameActionValue *out, u32 cap);

BreakGameError break_game_move_wish(const BreakGameMoveInput *in, BreakGameMoveOutput *out);

BreakGameError break_game_level_open(BreakGame *game, const BreakGameLevelHooks *hooks,
                                     const char *scene_path, const char *actor_sidecar);
BreakGameError break_game_level_close(BreakGame *game);

BreakGameError break_game_area_add(BreakGame *game, const BreakGameAreaDesc *desc, u32 *out_id);
void           break_game_set_area_callback(BreakGame *game, BreakGameAreaFn fn, void *user);
BreakGameError break_game_area_tick(BreakGame *game);
