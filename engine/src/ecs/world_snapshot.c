#include <ecs/world_snapshot.h>

#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

#define SNAPSHOT_HASH_OFFSET UINT64_C(1469598103934665603)
#define SNAPSHOT_HASH_PRIME  UINT64_C(1099511628211)

typedef struct {
    u32 component;
    usize offset;
    usize size;
} SnapshotComponent;

typedef struct {
    Entity entity;
    SnapshotComponent *components;
    u32 component_count;
} SnapshotEntity;

struct BreakWorldSnapshot {
    _Atomic u32 references;
    u64 tick;
    u64 id;
    u64 hash;
    u64 schema_hash;
    SnapshotEntity *entities;
    usize entity_count;
    u8 *bytes;
    usize byte_count;
};

static u64 hash_bytes(u64 hash, const void *data, usize size) {
    const u8 *bytes = (const u8 *)data;
    for (usize i = 0u; i < size; ++i) {
        hash ^= bytes[i];
        hash *= SNAPSHOT_HASH_PRIME;
    }
    return hash;
}

static bool schema_supports_snapshot(const BreakComponentSchema *schema) {
    if (!schema || schema->size == 0u) return false;
    if ((schema->flags & BREAK_SCHEMA_FLAG_POINTER_CONTAINING) != 0u) return false;
    if ((schema->flags & BREAK_SCHEMA_FLAG_RESOURCE_REFERENCE) != 0u) return false;
    if ((schema->flags & BREAK_SCHEMA_FLAG_DERIVED_CACHE) != 0u) return false;
    return (schema->flags & BREAK_SCHEMA_FLAG_RAW_BYTES) != 0u &&
           (schema->flags & BREAK_SCHEMA_FLAG_DETERMINISTIC_POD) != 0u;
}

static void snapshot_destroy(BreakWorldSnapshot *snapshot) {
    if (!snapshot) return;
    for (usize i = 0u; i < snapshot->entity_count; ++i) {
        free(snapshot->entities[i].components);
    }
    free(snapshot->entities);
    free(snapshot->bytes);
    free(snapshot);
}

static SnapshotEntity *find_entity(BreakWorldSnapshot *snapshot, Entity entity) {
    usize low = 0u;
    usize high = snapshot ? snapshot->entity_count : 0u;
    while (low < high) {
        usize middle = low + (high - low) / 2u;
        Entity candidate = snapshot->entities[middle].entity;
        if (candidate.index < entity.index ||
            (candidate.index == entity.index && candidate.generation < entity.generation)) {
            low = middle + 1u;
        } else {
            high = middle;
        }
    }
    if (snapshot && low < snapshot->entity_count &&
        snapshot->entities[low].entity.index == entity.index &&
        snapshot->entities[low].entity.generation == entity.generation) {
        return &snapshot->entities[low];
    }
    return NULL;
}

BreakWorldSnapshot *break_world_snapshot_build(
    World *world, const BreakComponentSchemaRegistry *schemas, u64 tick) {
    if (!world || !schemas) return NULL;

    usize live_count = 0u;
    usize byte_count = 0u;
    for (u32 index = 1u; index < world->entity_count; ++index) {
        Entity entity = world->entities[index];
        if (!world_entity_exists(world, entity)) continue;
        ++live_count;
    }

    /* Validate the complete live archetype set, including components not queried
     * by the snapshot, before allocating a partially usable snapshot. */
    for (u32 ai = 0u; ai < world->archetype_count; ++ai) {
        Archetype *archetype = &world->archetypes[ai];
        if (archetype->total_count == 0u) continue;
        for (u32 ci = 0u; ci < archetype->key.count; ++ci) {
            ComponentType component = archetype->key.ids[ci];
            const BreakComponentSchema *schema = break_schema_lookup(schemas, component);
            if (!schema_supports_snapshot(schema) ||
                component >= ECS_MAX_COMPONENTS ||
                schema->size != world->component_sizes[component]) return NULL;
        }
    }

    for (u32 index = 1u; index < world->entity_count; ++index) {
        Entity entity = world->entities[index];
        if (!world_entity_exists(world, entity)) continue;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const BreakComponentSchema *schema = break_schema_lookup(schemas, component);
            if (!schema_supports_snapshot(schema)) continue;
            if (world_get_component(world, entity, component)) {
                if (byte_count > (usize)-1 - schema->size) return NULL;
                byte_count += schema->size;
            }
        }
    }

    BreakWorldSnapshot *snapshot = calloc(1u, sizeof(*snapshot));
    if (!snapshot) return NULL;
    atomic_init(&snapshot->references, 1u);
    snapshot->tick = tick;
    snapshot->entity_count = live_count;
    snapshot->byte_count = byte_count;
    snapshot->entities = calloc(live_count ? live_count : 1u, sizeof(*snapshot->entities));
    snapshot->bytes = malloc(byte_count ? byte_count : 1u);
    if (!snapshot->entities || !snapshot->bytes) {
        snapshot_destroy(snapshot);
        return NULL;
    }

    usize entity_slot = 0u;
    usize byte_offset = 0u;
    for (u32 index = 1u; index < world->entity_count; ++index) {
        Entity entity = world->entities[index];
        if (!world_entity_exists(world, entity)) continue;
        SnapshotEntity *stored = &snapshot->entities[entity_slot++];
        stored->entity = entity;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const BreakComponentSchema *schema = break_schema_lookup(schemas, component);
            if (!schema_supports_snapshot(schema)) continue;
            const void *source = world_get_component(world, entity, component);
            if (!source) continue;
            SnapshotComponent *components = realloc(
                stored->components, (stored->component_count + 1u) * sizeof(*components));
            if (!components) {
                snapshot_destroy(snapshot);
                return NULL;
            }
            stored->components = components;
            components[stored->component_count++] =
                (SnapshotComponent){component, byte_offset, schema->size};
            memcpy(snapshot->bytes + byte_offset, source, schema->size);
            byte_offset += schema->size;
        }
    }

    u64 hash = SNAPSHOT_HASH_OFFSET;
    hash = hash_bytes(hash, &snapshot->tick, sizeof(snapshot->tick));
    u64 schema_hash = break_schema_hash(schemas);
    snapshot->schema_hash = schema_hash;
    hash = hash_bytes(hash, &schema_hash, sizeof(schema_hash));
    for (usize i = 0u; i < snapshot->entity_count; ++i) {
        SnapshotEntity *entity = &snapshot->entities[i];
        hash = hash_bytes(hash, &entity->entity, sizeof(entity->entity));
        for (u32 j = 0u; j < entity->component_count; ++j) {
            SnapshotComponent *component = &entity->components[j];
            hash = hash_bytes(hash, &component->component, sizeof(component->component));
            hash = hash_bytes(hash, snapshot->bytes + component->offset, component->size);
        }
    }
    snapshot->hash = hash;
    snapshot->id = hash;
    return snapshot;
}

void break_world_snapshot_retain(BreakWorldSnapshot *snapshot) {
    if (snapshot) atomic_fetch_add_explicit(&snapshot->references, 1u, memory_order_relaxed);
}

void break_world_snapshot_release(BreakWorldSnapshot *snapshot) {
    if (!snapshot) return;
    if (atomic_fetch_sub_explicit(&snapshot->references, 1u, memory_order_acq_rel) == 1u) {
        snapshot_destroy(snapshot);
    }
}

u64 break_world_snapshot_tick(const BreakWorldSnapshot *snapshot) {
    return snapshot ? snapshot->tick : 0u;
}

u64 break_world_snapshot_id(const BreakWorldSnapshot *snapshot) {
    return snapshot ? snapshot->id : 0u;
}

u64 break_world_snapshot_hash(const BreakWorldSnapshot *snapshot) {
    return snapshot ? snapshot->hash : 0u;
}

u64 break_world_snapshot_schema_hash(const BreakWorldSnapshot *snapshot) {
    return snapshot ? snapshot->schema_hash : 0u;
}

usize break_world_snapshot_entity_count(const BreakWorldSnapshot *snapshot) {
    return snapshot ? snapshot->entity_count : 0u;
}

Entity break_world_snapshot_entity_at(const BreakWorldSnapshot *snapshot, usize index) {
    if (!snapshot || index >= snapshot->entity_count) return ENTITY_NULL;
    return snapshot->entities[index].entity;
}

bool break_world_snapshot_has_entity(const BreakWorldSnapshot *snapshot, Entity entity) {
    return snapshot && find_entity((BreakWorldSnapshot *)snapshot, entity) != NULL;
}

bool break_world_snapshot_component_bytes(const BreakWorldSnapshot *snapshot,
                                           Entity entity, ComponentType component,
                                           const void **out_bytes, usize *out_size) {
    if (!snapshot || !out_bytes || !out_size) return false;
    SnapshotEntity *stored = find_entity((BreakWorldSnapshot *)snapshot, entity);
    if (!stored) return false;
    for (u32 i = 0u; i < stored->component_count; ++i) {
        SnapshotComponent *record = &stored->components[i];
        if (record->component == component) {
            *out_bytes = snapshot->bytes + record->offset;
            *out_size = record->size;
            return true;
        }
    }
    return false;
}
