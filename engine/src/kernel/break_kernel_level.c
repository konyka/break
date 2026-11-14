#include <kernel/break_kernel_internal.h>
#include <stdio.h>
#include <stdlib.h>

static BreakKernelError read_sidecar(const char *path, char **out_text, size_t *out_len) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return BREAK_KERNEL_FAILED;
    }
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return BREAK_KERNEL_FAILED;
    }
    long end = ftell(file);
    if (end < 0) {
        fclose(file);
        return BREAK_KERNEL_FAILED;
    }
    if ((unsigned long)end > (1ul << 20)) {
        fclose(file);
        return BREAK_KERNEL_OVERLOAD;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return BREAK_KERNEL_FAILED;
    }
    size_t len = (size_t)end;
    char *text = (char *)malloc(len + 1u);
    if (!text) {
        fclose(file);
        return BREAK_KERNEL_OOM;
    }
    size_t got = fread(text, 1, len, file);
    fclose(file);
    if (got != len) {
        free(text);
        return BREAK_KERNEL_FAILED;
    }
    if (memchr(text, '\0', len)) {
        free(text);
        return BREAK_KERNEL_INVALID;
    }
    text[len] = '\0';
    *out_text = text;
    *out_len = len;
    return BREAK_KERNEL_OK;
}

static u32 find_class(const BreakKernel *kernel, const char *name) {
    for (u32 i = 1; i <= kernel->class_count; i++) {
        if (kernel->classes[i].used && strcmp(kernel->classes[i].name, name) == 0) {
            return i;
        }
    }
    return 0;
}

static BreakKernelError parse_sidecar(BreakKernel *kernel, const char *text, BreakKernelAdopted *rows, u32 *out_count) {
    u32 count = 0;
    const char *p = text;
    while (*p) {
        const char *line = p;
        while (*p && *p != '\n') {
            p++;
        }
        size_t len = (size_t)(p - line);
        if (*p == '\n') {
            p++;
        }
        while (len > 0 && (line[len - 1] == '\r' || line[len - 1] == ' ' || line[len - 1] == '\t')) {
            len--;
        }
        size_t start = 0;
        while (start < len && (line[start] == ' ' || line[start] == '\t')) {
            start++;
        }
        if (start == len || line[start] == '#') {
            continue;
        }
        if (count >= BREAK_KERNEL_HARD_MAX_ACTORS) {
            return BREAK_KERNEL_OVERLOAD;
        }
        char buf[512];
        if (len - start >= sizeof(buf)) {
            return BREAK_KERNEL_INVALID;
        }
        memcpy(buf, line + start, len - start);
        buf[len - start] = '\0';
        char *end = NULL;
        unsigned long index = strtoul(buf, &end, 10);
        if (end == buf || (*end != ' ' && *end != '\t')) {
            return BREAK_KERNEL_INVALID;
        }
        while (*end == ' ' || *end == '\t') {
            end++;
        }
        char name[BREAK_KERNEL_NAME_CAP];
        memset(name, 0, sizeof(name));
        if (!break_kernel_copy_name(end, name, false)) {
            return BREAK_KERNEL_INVALID;
        }
        if (index == 0 || index >= kernel->world->entity_count || index >= ECS_MAX_ENTITIES) {
            return BREAK_KERNEL_STALE;
        }
        Entity entity = kernel->world->entities[index];
        if (entity.index != (u32)index || !world_entity_exists(kernel->world, entity)) {
            return BREAK_KERNEL_STALE;
        }
        u32 class_id = find_class(kernel, name);
        if (class_id == 0) {
            return BREAK_KERNEL_FAILED;
        }
        for (u32 i = 0; i < count; i++) {
            if (rows[i].entity.index == entity.index) {
                return BREAK_KERNEL_REJECTED;
            }
        }
        rows[count].entity = entity;
        rows[count].class_id = class_id;
        count++;
    }
    *out_count = count;
    return BREAK_KERNEL_OK;
}

static void rollback_open(BreakKernel *kernel, const BreakKernelLevelHooks *hooks, bool loaded) {
    if (loaded && hooks->unload) {
        hooks->unload(hooks->user, kernel->world);
    }
}

BreakKernelError break_kernel_level_open(BreakKernel *kernel, const BreakKernelLevelHooks *hooks,
                                     const char *scene_path, const char *actor_sidecar) {
    if (!kernel || !hooks || !hooks->load || !scene_path || scene_path[0] == '\0') {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    if (kernel->level_open) {
        return BREAK_KERNEL_REJECTED;
    }
    BreakKernelError loaded = hooks->load(hooks->user, kernel->world, scene_path);
    if (loaded != BREAK_KERNEL_OK) {
        return loaded;
    }
    BreakKernelAdopted *rows = NULL;
    u32 row_count = 0;
    if (actor_sidecar && actor_sidecar[0] != '\0') {
        char *text = NULL;
        size_t len = 0;
        BreakKernelError read = read_sidecar(actor_sidecar, &text, &len);
        if (read != BREAK_KERNEL_OK) {
            rollback_open(kernel, hooks, true);
            return read;
        }
        rows = (BreakKernelAdopted *)calloc(BREAK_KERNEL_HARD_MAX_ACTORS, sizeof(BreakKernelAdopted));
        if (!rows) {
            free(text);
            rollback_open(kernel, hooks, true);
            return BREAK_KERNEL_OOM;
        }
        BreakKernelError parsed = parse_sidecar(kernel, text, rows, &row_count);
        free(text);
        if (parsed != BREAK_KERNEL_OK) {
            free(rows);
            rollback_open(kernel, hooks, true);
            return parsed;
        }
    }
    u32 adopted = 0;
    for (; adopted < row_count; adopted++) {
        BreakKernelError err = break_kernel_adopt(kernel, rows[adopted].entity, rows[adopted].class_id);
        if (err != BREAK_KERNEL_OK) {
            for (u32 i = 0; i < adopted; i++) {
                break_kernel_despawn(kernel, rows[i].entity);
            }
            free(rows);
            rollback_open(kernel, hooks, true);
            return err;
        }
    }
    free(rows);
    kernel->level_hooks = *hooks;
    kernel->level_open = true;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_level_close(BreakKernel *kernel) {
    if (!kernel) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    if (!kernel->level_open) {
        return BREAK_KERNEL_CLOSED;
    }
    BreakKernelLevelHooks hooks = kernel->level_hooks;
    u32 n = 0;
    for (u32 slot = 0; slot < kernel->max_actors; slot++) {
        if (kernel->actors[slot].alive) {
            kernel->tick_snapshot[n++] = slot;
        }
    }
    for (u32 i = 0; i < n; i++) {
        u32 slot = kernel->tick_snapshot[i];
        if (kernel->actors[slot].alive) {
            break_kernel_despawn(kernel, kernel->actors[slot].entity);
        }
    }
    kernel->level_open = false;
    memset(&kernel->level_hooks, 0, sizeof(kernel->level_hooks));
    if (hooks.unload) {
        hooks.unload(hooks.user, kernel->world);
    }
    return BREAK_KERNEL_OK;
}
