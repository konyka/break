#include <kernel/break_kernel_internal.h>
#include <stdlib.h>

bool break_kernel_is_owner(const BreakKernel *kernel) {
    return kernel && platform_thread_id_equal(kernel->owner, platform_thread_current_id());
}

u32 break_kernel_actor_slot(const BreakKernel *kernel, Entity entity) {
    if (!kernel || entity.index == 0 || entity.index >= ECS_MAX_ENTITIES) {
        return UINT32_MAX;
    }
    u32 slot = kernel->slot_of[entity.index];
    if (slot >= kernel->max_actors) {
        return UINT32_MAX;
    }
    if (!kernel->actors[slot].alive) {
        return UINT32_MAX;
    }
    if (kernel->actors[slot].entity.index != entity.index ||
        kernel->actors[slot].entity.generation != entity.generation) {
        return UINT32_MAX;
    }
    return slot;
}

bool break_kernel_copy_name(const char *src, char *dst, bool allow_empty) {
    if (!src) {
        return allow_empty;
    }
    u32 n = 0;
    while (src[n] != '\0') {
        unsigned char c = (unsigned char)src[n];
        if (n >= BREAK_KERNEL_NAME_CAP - 1u || c <= ' ' || c == '#') {
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

static void break_kernel_free(BreakKernel *kernel) {
    if (!kernel) {
        return;
    }
    free(kernel->classes);
    free(kernel->actors);
    free(kernel->inventories);
    free(kernel->free_stack);
    free(kernel->slot_of);
    free(kernel->tick_snapshot);
    free(kernel->inside);
    free(kernel);
}

BreakKernel *break_kernel_create(World *world, const BreakKernelConfig *config) {
    if (!world) {
        return NULL;
    }
    u32 max_classes = BREAK_KERNEL_HARD_MAX_CLASSES;
    u32 max_actors = BREAK_KERNEL_HARD_MAX_ACTORS;
    if (config) {
        if (config->max_classes != 0) {
            max_classes = config->max_classes;
        }
        if (config->max_actors != 0) {
            max_actors = config->max_actors;
        }
    }
    if (max_classes > BREAK_KERNEL_HARD_MAX_CLASSES || max_actors > BREAK_KERNEL_HARD_MAX_ACTORS ||
        max_classes == 0 || max_actors == 0) {
        return NULL;
    }

    size_t inventory_stride = (size_t)BREAK_KERNEL_MAX_ITEMS + 1u;
    if ((size_t)max_actors > SIZE_MAX / inventory_stride) {
        return NULL;
    }
    size_t inventory_count = (size_t)max_actors * inventory_stride;
    if (inventory_count > SIZE_MAX / sizeof(u32)) {
        return NULL;
    }

    BreakKernel *kernel = (BreakKernel *)calloc(1, sizeof(BreakKernel));
    if (!kernel) {
        return NULL;
    }
    kernel->world = world;
    kernel->owner = platform_thread_current_id();
    kernel->max_classes = max_classes;
    kernel->max_actors = max_actors;
    kernel->classes = (BreakKernelClass *)calloc((size_t)max_classes + 1u, sizeof(BreakKernelClass));
    kernel->actors = (BreakKernelActor *)calloc(max_actors, sizeof(BreakKernelActor));
    kernel->inventories = (u32 *)calloc(inventory_count, sizeof(u32));
    kernel->free_stack = (u32 *)calloc(max_actors, sizeof(u32));
    kernel->slot_of = (u32 *)malloc(sizeof(u32) * ECS_MAX_ENTITIES);
    kernel->tick_snapshot = (u32 *)calloc(max_actors, sizeof(u32));
    kernel->inside = (u8 *)calloc((size_t)BREAK_KERNEL_HARD_MAX_AREAS * (size_t)max_actors, 1);
    if (!kernel->classes || !kernel->actors || !kernel->inventories || !kernel->free_stack ||
        !kernel->slot_of || !kernel->tick_snapshot || !kernel->inside) {
        break_kernel_free(kernel);
        return NULL;
    }
    memset(kernel->slot_of, 0xFF, sizeof(u32) * ECS_MAX_ENTITIES);
    for (u32 i = 0; i < max_actors; i++) {
        kernel->free_stack[i] = max_actors - 1u - i;
    }
    kernel->free_top = max_actors;
    return kernel;
}

void break_kernel_destroy(BreakKernel *kernel) {
    if (!kernel || !break_kernel_is_owner(kernel)) {
        return;
    }
    break_kernel_free(kernel);
}

BreakKernelError break_kernel_register_class(BreakKernel *kernel, const BreakKernelClassDesc *desc, u32 *out_class_id) {
    if (!kernel || !desc || !out_class_id) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    char name[BREAK_KERNEL_NAME_CAP];
    char lua_module[BREAK_KERNEL_NAME_CAP];
    memset(name, 0, sizeof(name));
    memset(lua_module, 0, sizeof(lua_module));
    if (!break_kernel_copy_name(desc->name, name, false)) {
        return BREAK_KERNEL_INVALID;
    }
    if (desc->lua_module && !break_kernel_copy_name(desc->lua_module, lua_module, false)) {
        return BREAK_KERNEL_INVALID;
    }
    if (desc->component_count > BREAK_KERNEL_MAX_CLASS_COMPONENTS) {
        return BREAK_KERNEL_INVALID;
    }
    if (desc->component_count > 0 && !desc->components) {
        return BREAK_KERNEL_INVALID;
    }
    for (u32 i = 0; i < desc->component_count; i++) {
        if (desc->components[i] >= ECS_MAX_COMPONENTS) {
            return BREAK_KERNEL_INVALID;
        }
    }
    for (u32 i = 1; i <= kernel->class_count; i++) {
        if (kernel->classes[i].used && strcmp(kernel->classes[i].name, name) == 0) {
            return BREAK_KERNEL_REJECTED;
        }
    }
    if (kernel->class_count >= kernel->max_classes) {
        return BREAK_KERNEL_OVERLOAD;
    }
    u32 id = kernel->class_count + 1u;
    BreakKernelClass *cls = &kernel->classes[id];
    memset(cls, 0, sizeof(*cls));
    memcpy(cls->name, name, sizeof(name));
    memcpy(cls->lua_module, lua_module, sizeof(lua_module));
    cls->component_count = desc->component_count;
    if (desc->component_count > 0) {
        memcpy(cls->components, desc->components, desc->component_count * sizeof(ComponentType));
    }
    cls->used = true;
    kernel->class_count = id;
    *out_class_id = id;
    return BREAK_KERNEL_OK;
}
