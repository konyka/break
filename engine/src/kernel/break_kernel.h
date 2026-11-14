#pragma once
/*
 * Actor kernel for the core-style runtime prototype.
 * One BreakKernel borrows a World, is owned by the creating thread, and is
 * not linked into engine / engine_demo / dxx_break.
 */
#include <core/types.h>
#include <ecs/ecs.h>
#include <math/math.h>
#include <platform/input.h>

#ifdef __cplusplus
extern "C" {
#endif


#define BREAK_KERNEL_HARD_MAX_CLASSES 64u
#define BREAK_KERNEL_HARD_MAX_ACTORS  4096u
#define BREAK_KERNEL_HARD_MAX_ACTIONS 64u
#define BREAK_KERNEL_HARD_MAX_BINDINGS 8u
#define BREAK_KERNEL_HARD_MAX_AREAS   256u
#define BREAK_KERNEL_NAME_CAP         64u
#define BREAK_KERNEL_MAX_CLASS_COMPONENTS 16u
#define BREAK_KERNEL_POSITION_COMPONENT ((ComponentType)0)
#define BREAK_KERNEL_AREA_EVENT_CAP   64u
#define BREAK_KERNEL_AREA_HYSTERESIS  0.25f
#define BREAK_KERNEL_MAX_ITEMS        64u

typedef enum BreakKernelError {
    BREAK_KERNEL_OK = 0,
    BREAK_KERNEL_INVALID,
    BREAK_KERNEL_CLOSED,
    BREAK_KERNEL_OVERLOAD,
    BREAK_KERNEL_OOM,
    BREAK_KERNEL_TIMEOUT,
    BREAK_KERNEL_STALE,
    BREAK_KERNEL_REJECTED,
    BREAK_KERNEL_FAILED
} BreakKernelError;

typedef struct BreakKernel BreakKernel;

typedef struct BreakKernelConfig {
    u32 max_classes; /* 0 => 64, hard cap 64 */
    u32 max_actors;  /* 0 => 4096, hard cap 4096 */
} BreakKernelConfig;

typedef struct BreakKernelItemDesc {
    u32 item_id;     /* 1..64 */
    u32 stack_limit; /* 1..1000000 */
} BreakKernelItemDesc;

typedef struct BreakKernelWeaponDesc {
    u32 weapon_id;         /* 1..64 */
    u32 ammo_item_id;      /* defined item */
    u32 damage;            /* 1..10000, host configured */
    u32 magazine_capacity; /* 1..1000 */
    u32 fire_interval_ticks;
    u32 reload_ticks;      /* >= 1 */
} BreakKernelWeaponDesc;

typedef struct BreakKernelFireIntent {
    Entity shooter;
    u32 weapon_id;
    u32 damage;
    u64 sequence;          /* from 1, monotonic across BreakKernel */
} BreakKernelFireIntent;

#define BREAK_KERNEL_MAX_ENTITY_ACTIONS 4096u

typedef enum BreakKernelEntityActionType {
    BREAK_KERNEL_ENTITY_SET_POSITION = 1,
    BREAK_KERNEL_ENTITY_INVENTORY_ADD = 2
} BreakKernelEntityActionType;

typedef struct BreakKernelEntityAction {
    BreakKernelEntityActionType type;
    Entity entity;
    Vec3 position;
    u32 item_id;
    u32 count;
} BreakKernelEntityAction;

typedef struct BreakKernelClassDesc {
    const char *name;                /* 1..63 bytes, no whitespace */
    const ComponentType *components; /* may be NULL when count is 0 */
    u32 component_count;             /* hard cap 16 */
    const char *lua_module;          /* stored only; NULL allowed */
} BreakKernelClassDesc;

typedef void (*BreakKernelTickFn)(BreakKernel *kernel, Entity entity, f32 dt, void *user);

typedef struct BreakKernelScriptBridge {
    void *user;
    void (*actor_tick)(void *user, const char *module, Entity entity, f32 dt);
    void (*actor_despawn)(void *user, Entity entity);
} BreakKernelScriptBridge;

BreakKernelError break_kernel_set_script_bridge(
    BreakKernel *kernel, const BreakKernelScriptBridge *bridge);

typedef struct BreakKernelSpawn {
    u32 class_id;
    Vec3 position;
} BreakKernelSpawn;

typedef enum BreakKernelBindSource {
    BREAK_KERNEL_BIND_KEY = 1,
    BREAK_KERNEL_BIND_MOUSE_BUTTON,
    BREAK_KERNEL_BIND_MOUSE_AXIS, /* 0 = dx, 1 = dy, 2 = wheel */
    BREAK_KERNEL_BIND_PAD_BUTTON,
    BREAK_KERNEL_BIND_PAD_AXIS
} BreakKernelBindSource;

typedef struct BreakKernelBinding {
    BreakKernelBindSource source;
    i32 code;
    i32 pad;   /* pad sources only; other sources must be 0 */
    f32 scale;
} BreakKernelBinding;

typedef struct BreakKernelActionDesc {
    const char *name;
    const BreakKernelBinding *bindings;
    u32 binding_count; /* hard cap 8 */
} BreakKernelActionDesc;

typedef struct BreakKernelActionValue {
    bool down;
    f32 axis;
} BreakKernelActionValue;

typedef struct BreakKernelMoveInput {
    f32 forward;    /* [-1, 1] */
    f32 strafe;     /* [-1, 1] */
    f32 camera_yaw; /* radians; 0 faces +Z */
    bool jump;
} BreakKernelMoveInput;

typedef struct BreakKernelMoveOutput {
    Vec3 wish; /* world XZ, y = 0, length at most 1 */
    bool jump;
    f32 yaw;
} BreakKernelMoveOutput;

typedef BreakKernelError (*BreakKernelLevelLoadFn)(void *user, World *world, const char *path);
typedef void (*BreakKernelLevelUnloadFn)(void *user, World *world);

typedef struct BreakKernelLevelHooks {
    BreakKernelLevelLoadFn load;
    BreakKernelLevelUnloadFn unload;
    void *user;
} BreakKernelLevelHooks;

typedef enum BreakKernelAreaEvent {
    BREAK_KERNEL_AREA_ENTER = 1,
    BREAK_KERNEL_AREA_LEAVE = 2
} BreakKernelAreaEvent;

typedef struct BreakKernelAreaDesc {
    Vec3 center;
    Vec3 half_extent; /* any component > 0 selects an AABB; all 0 selects a sphere */
    f32 radius;
} BreakKernelAreaDesc;

typedef void (*BreakKernelAreaFn)(u32 area_id, Entity entity, BreakKernelAreaEvent event, void *user);

BreakKernel *break_kernel_create(World *world, const BreakKernelConfig *config);
void       break_kernel_destroy(BreakKernel *kernel);

BreakKernelError break_kernel_register_class(BreakKernel *kernel,
                                         const BreakKernelClassDesc *desc,
                                         u32 *out_class_id);

BreakKernelError break_kernel_spawn(BreakKernel *kernel, const BreakKernelSpawn *spawn, Entity *out_entity);
BreakKernelError break_kernel_despawn(BreakKernel *kernel, Entity entity);
void           break_kernel_set_tick(BreakKernel *kernel, u32 class_id, BreakKernelTickFn fn, void *user);
void           break_kernel_tick(BreakKernel *kernel, f32 dt);

BreakKernelError break_kernel_item_define(BreakKernel *kernel,
                                      const BreakKernelItemDesc *desc);
BreakKernelError break_kernel_inventory_add(BreakKernel *kernel, Entity entity,
                                        u32 item_id, u32 count);
BreakKernelError break_kernel_inventory_count(BreakKernel *kernel, Entity entity,
                                          u32 item_id, u32 *out_count);
BreakKernelError break_kernel_inventory_transfer(BreakKernel *kernel,
                                             Entity from, Entity to,
                                             u32 item_id, u32 count);
BreakKernelError break_kernel_entity_actions_apply(BreakKernel *kernel,
                                               const BreakKernelEntityAction *actions,
                                               u32 count);

BreakKernelError break_kernel_weapon_define(BreakKernel *kernel,
                                        const BreakKernelWeaponDesc *desc);
BreakKernelError break_kernel_weapon_equip(BreakKernel *kernel, Entity entity,
                                       u32 weapon_id);
BreakKernelError break_kernel_weapon_unequip(BreakKernel *kernel, Entity entity);
BreakKernelError break_kernel_weapon_begin_reload(BreakKernel *kernel, Entity entity);
BreakKernelError break_kernel_weapon_tick(BreakKernel *kernel, Entity entity,
                                      u32 elapsed_ticks);
BreakKernelError break_kernel_weapon_fire(BreakKernel *kernel, Entity entity,
                                      BreakKernelFireIntent *out_intent);
BreakKernelError break_kernel_weapon_ammo(const BreakKernel *kernel, Entity entity,
                                      u32 *out_magazine);

BreakKernelError break_kernel_bind_actions(BreakKernel *kernel,
                                       const BreakKernelActionDesc *actions,
                                       u32 count);
BreakKernelError break_kernel_eval_actions(BreakKernel *kernel, const InputState *input,
                                       BreakKernelActionValue *out, u32 cap);

BreakKernelError break_kernel_move_wish(const BreakKernelMoveInput *in, BreakKernelMoveOutput *out);

BreakKernelError break_kernel_level_open(BreakKernel *kernel, const BreakKernelLevelHooks *hooks,
                                     const char *scene_path, const char *actor_sidecar);
BreakKernelError break_kernel_level_close(BreakKernel *kernel);

BreakKernelError break_kernel_area_add(BreakKernel *kernel, const BreakKernelAreaDesc *desc, u32 *out_id);
void           break_kernel_set_area_callback(BreakKernel *kernel, BreakKernelAreaFn fn, void *user);
BreakKernelError break_kernel_area_tick(BreakKernel *kernel);
#ifdef __cplusplus
} /* extern "C" */
#endif
