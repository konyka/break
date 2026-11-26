#include <ecs/net_entity_map.h>

#include <stdlib.h>

/* A dense table of live bindings; release swaps the last slot in. Lookups are
 * linear, which is fine for the bounded capacity and the LogicThread-only
 * use (bindings change at spawn, despawn and World moves, not per frame). */
typedef struct NetEntityBinding {
    BreakNetEntityId id;
    u32 world_key;
    Entity entity;
} NetEntityBinding;

struct BreakNetEntityMap {
    NetEntityBinding *slots;
    u32 capacity;
    u32 count;
    u64 next_id; /* 0 = exhausted */
    u64 conflicts;
    u64 overloads;
};

static i64 find_id(const BreakNetEntityMap *map, BreakNetEntityId id) {
    for (u32 i = 0u; i < map->count; ++i)
        if (map->slots[i].id == id) return (i64)i;
    return -1;
}

static i64 find_place(const BreakNetEntityMap *map, u32 world_key, Entity entity) {
    for (u32 i = 0u; i < map->count; ++i) {
        const NetEntityBinding *b = &map->slots[i];
        if (b->world_key == world_key && b->entity.index == entity.index &&
            b->entity.generation == entity.generation)
            return (i64)i;
    }
    return -1;
}

bool break_net_entity_map_create(const BreakNetEntityMapConfig *config, BreakNetEntityMap **out) {
    BreakNetEntityMap *map;
    if (!out) return false;
    *out = NULL;
    if (!config || config->capacity == 0u ||
        config->capacity > BREAK_NET_ENTITY_MAP_MAX_CAPACITY || config->first_id == 0u)
        return false;
    map = (BreakNetEntityMap *)calloc(1u, sizeof(*map));
    if (!map) return false;
    map->slots = (NetEntityBinding *)calloc(config->capacity, sizeof(*map->slots));
    if (!map->slots) {
        free(map);
        return false;
    }
    map->capacity = config->capacity;
    map->next_id = config->first_id;
    *out = map;
    return true;
}

void break_net_entity_map_destroy(BreakNetEntityMap *map) {
    if (!map) return;
    free(map->slots);
    free(map);
}

/* Shared admission for bind_new/adopt; the caller has validated arguments. */
static BreakNetEntityResult admit(BreakNetEntityMap *map, BreakNetEntityId id, u32 world_key,
                                  Entity entity) {
    if (find_id(map, id) >= 0 || find_place(map, world_key, entity) >= 0) {
        map->conflicts++;
        return BREAK_NET_ENTITY_CONFLICT;
    }
    if (map->count == map->capacity) {
        map->overloads++;
        return BREAK_NET_ENTITY_OVERLOAD;
    }
    map->slots[map->count].id = id;
    map->slots[map->count].world_key = world_key;
    map->slots[map->count].entity = entity;
    map->count++;
    return BREAK_NET_ENTITY_OK;
}

BreakNetEntityResult break_net_entity_map_bind_new(BreakNetEntityMap *map, u32 world_key,
                                                   Entity entity, BreakNetEntityId *out_id) {
    BreakNetEntityResult r;
    BreakNetEntityId id;
    if (out_id) *out_id = 0u;
    if (!map || !out_id || !entity_valid(entity)) return BREAK_NET_ENTITY_INVALID;
    if (map->next_id == 0u) return BREAK_NET_ENTITY_EXHAUSTED;
    id = map->next_id;
    r = admit(map, id, world_key, entity);
    if (r != BREAK_NET_ENTITY_OK) return r;
    map->next_id = id + 1u; /* wraps to 0 after UINT64_MAX: exhausted */
    *out_id = id;
    return BREAK_NET_ENTITY_OK;
}

BreakNetEntityResult break_net_entity_map_adopt(BreakNetEntityMap *map, BreakNetEntityId id,
                                                u32 world_key, Entity entity) {
    BreakNetEntityResult r;
    if (!map || id == 0u || !entity_valid(entity)) return BREAK_NET_ENTITY_INVALID;
    r = admit(map, id, world_key, entity);
    if (r != BREAK_NET_ENTITY_OK) return r;
    if (map->next_id != 0u && id >= map->next_id) map->next_id = id + 1u; /* 0 = exhausted */
    return BREAK_NET_ENTITY_OK;
}

BreakNetEntityResult break_net_entity_map_rebind(BreakNetEntityMap *map, BreakNetEntityId id,
                                                 u32 world_key, Entity entity) {
    i64 at;
    i64 occupant;
    if (!map || id == 0u || !entity_valid(entity)) return BREAK_NET_ENTITY_INVALID;
    at = find_id(map, id);
    if (at < 0) return BREAK_NET_ENTITY_NOT_FOUND;
    occupant = find_place(map, world_key, entity);
    if (occupant >= 0 && occupant != at) {
        map->conflicts++;
        return BREAK_NET_ENTITY_CONFLICT;
    }
    map->slots[at].world_key = world_key;
    map->slots[at].entity = entity;
    return BREAK_NET_ENTITY_OK;
}

BreakNetEntityResult break_net_entity_map_release(BreakNetEntityMap *map, BreakNetEntityId id) {
    i64 at;
    if (!map || id == 0u) return BREAK_NET_ENTITY_INVALID;
    at = find_id(map, id);
    if (at < 0) return BREAK_NET_ENTITY_NOT_FOUND;
    map->slots[at] = map->slots[map->count - 1u];
    map->count--;
    return BREAK_NET_ENTITY_OK;
}

BreakNetEntityResult break_net_entity_map_entity(const BreakNetEntityMap *map, BreakNetEntityId id,
                                                 u32 *out_world_key, Entity *out_entity) {
    i64 at;
    if (!map || id == 0u || !out_world_key || !out_entity) return BREAK_NET_ENTITY_INVALID;
    at = find_id(map, id);
    if (at < 0) return BREAK_NET_ENTITY_NOT_FOUND;
    *out_world_key = map->slots[at].world_key;
    *out_entity = map->slots[at].entity;
    return BREAK_NET_ENTITY_OK;
}

BreakNetEntityResult break_net_entity_map_id(const BreakNetEntityMap *map, u32 world_key,
                                             Entity entity, BreakNetEntityId *out_id) {
    i64 at;
    if (out_id) *out_id = 0u;
    if (!map || !out_id || !entity_valid(entity)) return BREAK_NET_ENTITY_INVALID;
    at = find_place(map, world_key, entity);
    if (at < 0) return BREAK_NET_ENTITY_NOT_FOUND;
    *out_id = map->slots[at].id;
    return BREAK_NET_ENTITY_OK;
}

BreakNetEntityResult break_net_entity_map_stats(const BreakNetEntityMap *map,
                                                BreakNetEntityMapStats *out_stats) {
    if (!map || !out_stats) return BREAK_NET_ENTITY_INVALID;
    out_stats->bound = map->count;
    out_stats->next_id = map->next_id;
    out_stats->conflicts = map->conflicts;
    out_stats->overloads = map->overloads;
    return BREAK_NET_ENTITY_OK;
}

bool break_net_entity_scope_keep(void *user, const struct BreakWorldSnapshot *snapshot,
                                 Entity entity) {
    const BreakNetEntityScope *scope = (const BreakNetEntityScope *)user;
    BreakNetEntityId id = 0u;
    (void)snapshot;
    if (!scope || !scope->map || !snapshot) return false;
    if (break_net_entity_map_id(scope->map, scope->world_key, entity, &id) !=
        BREAK_NET_ENTITY_OK) {
        return false;
    }
    for (usize i = 0u; i < scope->count; ++i) {
        if (scope->ids && scope->ids[i] == id) return true;
    }
    return false;
}
