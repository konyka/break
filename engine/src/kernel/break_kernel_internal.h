#pragma once
#include <kernel/break_kernel.h>
#include <core/platform_thread.h>
#include <string.h>

typedef struct BreakKernelClass {
    char name[BREAK_KERNEL_NAME_CAP];
    char lua_module[BREAK_KERNEL_NAME_CAP];
    ComponentType components[BREAK_KERNEL_MAX_CLASS_COMPONENTS];
    u32 component_count;
    bool used;
    BreakKernelTickFn tick;
    void *tick_user;
} BreakKernelClass;

typedef struct BreakKernelActor {
    Entity entity;
    u32 class_id;
    bool alive;
    u32 weapon_id;
    u32 magazine;
    u32 now_tick;
    u32 next_fire_tick;
    u32 reload_finish_tick;
    bool reloading;
} BreakKernelActor;

typedef struct BreakKernelAction {
    char name[BREAK_KERNEL_NAME_CAP];
    BreakKernelBinding bindings[BREAK_KERNEL_HARD_MAX_BINDINGS];
    u32 binding_count;
} BreakKernelAction;

typedef struct BreakKernelArea {
    BreakKernelAreaDesc desc;
    bool aabb;
    bool used;
} BreakKernelArea;

typedef struct BreakKernelAdopted {
    Entity entity;
    u32 class_id;
} BreakKernelAdopted;

struct BreakKernel {
    World *world;
    PlatformThreadId owner;
    u32 max_classes;
    u32 max_actors;
    BreakKernelClass *classes; /* index 0 unused; ids are 1..max_classes */
    u32 class_count;
    BreakKernelActor *actors;
    BreakKernelItemDesc items[BREAK_KERNEL_MAX_ITEMS + 1u];
    BreakKernelWeaponDesc weapons[BREAK_KERNEL_MAX_ITEMS + 1u];
    u64 fire_sequence;
    u32 *inventories; /* actor_slot * (BREAK_KERNEL_MAX_ITEMS + 1) + item_id */
    u32 *free_stack;
    u32 free_top;
    u32 live_count;
    u32 *slot_of; /* ECS_MAX_ENTITIES, UINT32_MAX = empty */
    u32 *tick_snapshot;
    BreakKernelAction actions[BREAK_KERNEL_HARD_MAX_ACTIONS];
    u32 action_count;
    bool level_open;
    BreakKernelLevelHooks level_hooks;
    BreakKernelArea areas[BREAK_KERNEL_HARD_MAX_AREAS];
    u32 area_count;
    u8 *inside; /* area_count stride is max_actors */
    BreakKernelAreaFn area_fn;
    void *area_user;
    BreakKernelScriptBridge script_bridge;
    bool script_bridge_used;
};

bool break_kernel_is_owner(const BreakKernel *kernel);
u32 break_kernel_actor_slot(const BreakKernel *kernel, Entity entity);
bool break_kernel_copy_name(const char *src, char *dst, bool allow_empty);

void break_kernel_area_on_despawn(BreakKernel *kernel, u32 slot, Entity entity);
void break_kernel_items_on_despawn(BreakKernel *kernel, u32 slot);
void break_kernel_weapons_on_despawn(BreakKernel *kernel, u32 slot);
BreakKernelError break_kernel_items_add_slot(BreakKernel *kernel, u32 slot,
                                         u32 item_id, u32 count);
BreakKernelError break_kernel_items_remove_slot(BreakKernel *kernel, u32 slot,
                                            u32 item_id, u32 count);

BreakKernelError break_kernel_adopt(BreakKernel *kernel, Entity entity, u32 class_id);
