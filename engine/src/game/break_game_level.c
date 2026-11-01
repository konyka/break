#include <game/break_game_internal.h>
#include <stdio.h>
#include <stdlib.h>

static BreakGameError read_sidecar(const char *path, char **out_text, size_t *out_len) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return BREAK_GAME_FAILED;
    }
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return BREAK_GAME_FAILED;
    }
    long end = ftell(file);
    if (end < 0) {
        fclose(file);
        return BREAK_GAME_FAILED;
    }
    if ((unsigned long)end > (1ul << 20)) {
        fclose(file);
        return BREAK_GAME_OVERLOAD;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return BREAK_GAME_FAILED;
    }
    size_t len = (size_t)end;
    char *text = (char *)malloc(len + 1u);
    if (!text) {
        fclose(file);
        return BREAK_GAME_OOM;
    }
    size_t got = fread(text, 1, len, file);
    fclose(file);
    if (got != len) {
        free(text);
        return BREAK_GAME_FAILED;
    }
    if (memchr(text, '\0', len)) {
        free(text);
        return BREAK_GAME_INVALID;
    }
    text[len] = '\0';
    *out_text = text;
    *out_len = len;
    return BREAK_GAME_OK;
}

static u32 find_class(const BreakGame *game, const char *name) {
    for (u32 i = 1; i <= game->class_count; i++) {
        if (game->classes[i].used && strcmp(game->classes[i].name, name) == 0) {
            return i;
        }
    }
    return 0;
}

static BreakGameError parse_sidecar(BreakGame *game, const char *text, BreakGameAdopted *rows, u32 *out_count) {
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
        if (count >= BREAK_GAME_HARD_MAX_ACTORS) {
            return BREAK_GAME_OVERLOAD;
        }
        char buf[512];
        if (len - start >= sizeof(buf)) {
            return BREAK_GAME_INVALID;
        }
        memcpy(buf, line + start, len - start);
        buf[len - start] = '\0';
        char *end = NULL;
        unsigned long index = strtoul(buf, &end, 10);
        if (end == buf || (*end != ' ' && *end != '\t')) {
            return BREAK_GAME_INVALID;
        }
        while (*end == ' ' || *end == '\t') {
            end++;
        }
        char name[BREAK_GAME_NAME_CAP];
        memset(name, 0, sizeof(name));
        if (!break_game_copy_name(end, name, false)) {
            return BREAK_GAME_INVALID;
        }
        if (index == 0 || index >= game->world->entity_count || index >= ECS_MAX_ENTITIES) {
            return BREAK_GAME_STALE;
        }
        Entity entity = game->world->entities[index];
        if (entity.index != (u32)index || !world_entity_exists(game->world, entity)) {
            return BREAK_GAME_STALE;
        }
        u32 class_id = find_class(game, name);
        if (class_id == 0) {
            return BREAK_GAME_FAILED;
        }
        for (u32 i = 0; i < count; i++) {
            if (rows[i].entity.index == entity.index) {
                return BREAK_GAME_REJECTED;
            }
        }
        rows[count].entity = entity;
        rows[count].class_id = class_id;
        count++;
    }
    *out_count = count;
    return BREAK_GAME_OK;
}

static void rollback_open(BreakGame *game, const BreakGameLevelHooks *hooks, bool loaded) {
    if (loaded && hooks->unload) {
        hooks->unload(hooks->user, game->world);
    }
}

BreakGameError break_game_level_open(BreakGame *game, const BreakGameLevelHooks *hooks,
                                     const char *scene_path, const char *actor_sidecar) {
    if (!game || !hooks || !hooks->load || !scene_path || scene_path[0] == '\0') {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    if (game->level_open) {
        return BREAK_GAME_REJECTED;
    }
    BreakGameError loaded = hooks->load(hooks->user, game->world, scene_path);
    if (loaded != BREAK_GAME_OK) {
        return loaded;
    }
    BreakGameAdopted *rows = NULL;
    u32 row_count = 0;
    if (actor_sidecar && actor_sidecar[0] != '\0') {
        char *text = NULL;
        size_t len = 0;
        BreakGameError read = read_sidecar(actor_sidecar, &text, &len);
        if (read != BREAK_GAME_OK) {
            rollback_open(game, hooks, true);
            return read;
        }
        rows = (BreakGameAdopted *)calloc(BREAK_GAME_HARD_MAX_ACTORS, sizeof(BreakGameAdopted));
        if (!rows) {
            free(text);
            rollback_open(game, hooks, true);
            return BREAK_GAME_OOM;
        }
        BreakGameError parsed = parse_sidecar(game, text, rows, &row_count);
        free(text);
        if (parsed != BREAK_GAME_OK) {
            free(rows);
            rollback_open(game, hooks, true);
            return parsed;
        }
    }
    u32 adopted = 0;
    for (; adopted < row_count; adopted++) {
        BreakGameError err = break_game_adopt(game, rows[adopted].entity, rows[adopted].class_id);
        if (err != BREAK_GAME_OK) {
            for (u32 i = 0; i < adopted; i++) {
                break_game_despawn(game, rows[i].entity);
            }
            free(rows);
            rollback_open(game, hooks, true);
            return err;
        }
    }
    free(rows);
    game->level_hooks = *hooks;
    game->level_open = true;
    return BREAK_GAME_OK;
}

BreakGameError break_game_level_close(BreakGame *game) {
    if (!game) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    if (!game->level_open) {
        return BREAK_GAME_CLOSED;
    }
    BreakGameLevelHooks hooks = game->level_hooks;
    u32 n = 0;
    for (u32 slot = 0; slot < game->max_actors; slot++) {
        if (game->actors[slot].alive) {
            game->tick_snapshot[n++] = slot;
        }
    }
    for (u32 i = 0; i < n; i++) {
        u32 slot = game->tick_snapshot[i];
        if (game->actors[slot].alive) {
            break_game_despawn(game, game->actors[slot].entity);
        }
    }
    game->level_open = false;
    memset(&game->level_hooks, 0, sizeof(game->level_hooks));
    if (hooks.unload) {
        hooks.unload(hooks.user, game->world);
    }
    return BREAK_GAME_OK;
}
