#include <ecs/world_delta_wire.h>
#include <ecs/ecs_internal.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void put16(u8 *p, u16 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8u);
}

static void put32(u8 *p, u32 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8u);
    p[2] = (u8)(value >> 16u);
    p[3] = (u8)(value >> 24u);
}

static void put64(u8 *p, u64 value) {
    put32(p, (u32)value);
    put32(p + 4u, (u32)(value >> 32u));
}

static u16 get16(const u8 *p) {
    return (u16)p[0] | ((u16)p[1] << 8u);
}

static u32 get32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8u) |
           ((u32)p[2] << 16u) | ((u32)p[3] << 24u);
}

static u64 get64(const u8 *p) {
    return (u64)get32(p) | ((u64)get32(p + 4u) << 32u);
}

static u64 entity_handle(Entity entity) {
    return (u64)entity.index | ((u64)entity.generation << 32u);
}

static Entity handle_entity(u64 handle) {
    Entity entity = {(u32)handle, (u32)(handle >> 32u)};
    return entity;
}

static BreakWorldDeltaWireResult validate_header(const BreakWorldDeltaWire *message) {
    if (!message) return BREAK_WORLD_DELTA_WIRE_INVALID;
    if (message->kind != BREAK_WORLD_DELTA_WIRE_FULL &&
        message->kind != BREAK_WORLD_DELTA_WIRE_DELTA) {
        return BREAK_WORLD_DELTA_WIRE_INVALID;
    }
    if (message->target_tick <= message->base_tick) return BREAK_WORLD_DELTA_WIRE_INVALID;
    if (message->kind == BREAK_WORLD_DELTA_WIRE_FULL) {
        if (message->base_snapshot_id != 0u || message->base_tick != 0u) {
            return BREAK_WORLD_DELTA_WIRE_INVALID;
        }
    } else if (message->base_snapshot_id == 0u) {
        return BREAK_WORLD_DELTA_WIRE_INVALID;
    }
    if (message->record_count > BREAK_WORLD_DELTA_WIRE_MAX_RECORD_COUNT) {
        return BREAK_WORLD_DELTA_WIRE_OVER_LIMIT;
    }
    return BREAK_WORLD_DELTA_WIRE_OK;
}

static BreakWorldDeltaWireResult validate_record(const BreakWorldDeltaWire *message,
                                                  const BreakWorldDeltaRecord *record) {
    if (!record || entity_handle(record->entity) == 0u) {
        return BREAK_WORLD_DELTA_WIRE_INVALID;
    }
    switch (record->kind) {
    case BREAK_DELTA_ENTITY_CREATE:
    case BREAK_DELTA_ENTITY_DESTROY:
    case BREAK_DELTA_COMPONENT_ADD:
    case BREAK_DELTA_COMPONENT_REMOVE:
    case BREAK_DELTA_COMPONENT_UPDATE:
        break;
    default:
        return BREAK_WORLD_DELTA_WIRE_INVALID;
    }
    if (message->kind == BREAK_WORLD_DELTA_WIRE_FULL &&
        record->kind != BREAK_DELTA_ENTITY_CREATE &&
        record->kind != BREAK_DELTA_COMPONENT_ADD) {
        return BREAK_WORLD_DELTA_WIRE_INVALID;
    }
    if (record->kind == BREAK_DELTA_ENTITY_CREATE ||
        record->kind == BREAK_DELTA_ENTITY_DESTROY) {
        if (record->component != 0u || record->size != 0u) {
            return BREAK_WORLD_DELTA_WIRE_INVALID;
        }
        return BREAK_WORLD_DELTA_WIRE_OK;
    }
    if (record->component == 0u) return BREAK_WORLD_DELTA_WIRE_INVALID;
    if (record->kind == BREAK_DELTA_COMPONENT_REMOVE) {
        return record->size == 0u ? BREAK_WORLD_DELTA_WIRE_OK : BREAK_WORLD_DELTA_WIRE_INVALID;
    }
    if (record->size == 0u || !record->bytes) return BREAK_WORLD_DELTA_WIRE_INVALID;
    return BREAK_WORLD_DELTA_WIRE_OK;
}

static BreakWorldDeltaWireResult validate_message(const BreakWorldDeltaWire *message,
                                                   usize *out_size) {
    BreakWorldDeltaWireResult result = validate_header(message);
    usize total = BREAK_WORLD_DELTA_WIRE_HEADER_SIZE;
    if (result != BREAK_WORLD_DELTA_WIRE_OK) return result;
    if (message->record_count != 0u && !message->records) return BREAK_WORLD_DELTA_WIRE_INVALID;
    for (u32 i = 0u; i < message->record_count; ++i) {
        const BreakWorldDeltaRecord *record = &message->records[i];
        result = validate_record(message, record);
        if (result != BREAK_WORLD_DELTA_WIRE_OK) return result;
        if (total > (usize)BREAK_WORLD_DELTA_WIRE_MAX_BYTES -
                        BREAK_WORLD_DELTA_WIRE_RECORD_HEADER_SIZE) {
            return BREAK_WORLD_DELTA_WIRE_OVER_LIMIT;
        }
        total += BREAK_WORLD_DELTA_WIRE_RECORD_HEADER_SIZE;
        if (record->size > (usize)BREAK_WORLD_DELTA_WIRE_MAX_BYTES - total) {
            return BREAK_WORLD_DELTA_WIRE_OVER_LIMIT;
        }
        total += record->size;
    }
    if (out_size) *out_size = total;
    return BREAK_WORLD_DELTA_WIRE_OK;
}

BreakWorldDeltaWireResult break_world_delta_wire_encoded_size(
    const BreakWorldDeltaWire *message, usize *out_size) {
    usize size = 0u;
    BreakWorldDeltaWireResult result;
    if (out_size) *out_size = 0u;
    if (!out_size) return BREAK_WORLD_DELTA_WIRE_INVALID;
    result = validate_message(message, &size);
    if (result != BREAK_WORLD_DELTA_WIRE_OK) return result;
    *out_size = size;
    return BREAK_WORLD_DELTA_WIRE_OK;
}

BreakWorldDeltaWireResult break_world_delta_wire_encode(
    const BreakWorldDeltaWire *message, u8 *out, usize capacity, usize *out_size) {
    usize size = 0u;
    usize offset = BREAK_WORLD_DELTA_WIRE_HEADER_SIZE;
    BreakWorldDeltaWireResult result;
    if (out_size) *out_size = 0u;
    if (!out || !out_size) return BREAK_WORLD_DELTA_WIRE_INVALID;
    result = validate_message(message, &size);
    if (result != BREAK_WORLD_DELTA_WIRE_OK) return result;
    if (capacity < size) return BREAK_WORLD_DELTA_WIRE_OVER_LIMIT;

    memcpy(out, "BRWD", 4u);
    put16(out + 4u, BREAK_WORLD_DELTA_WIRE_VERSION);
    put16(out + 6u, (u16)message->kind);
    put64(out + 8u, message->schema_hash);
    put64(out + 16u, message->level_generation);
    put64(out + 24u, message->base_snapshot_id);
    put64(out + 32u, message->target_snapshot_id);
    put64(out + 40u, message->base_tick);
    put64(out + 48u, message->target_tick);
    put32(out + 56u, message->record_count);
    for (u32 i = 0u; i < message->record_count; ++i) {
        const BreakWorldDeltaRecord *record = &message->records[i];
        out[offset] = (u8)record->kind;
        put64(out + offset + 1u, entity_handle(record->entity));
        put32(out + offset + 9u, record->component);
        put32(out + offset + 13u, (u32)record->size);
        offset += BREAK_WORLD_DELTA_WIRE_RECORD_HEADER_SIZE;
        if (record->size != 0u) {
            memcpy(out + offset, record->bytes, record->size);
            offset += record->size;
        }
    }
    *out_size = size;
    return BREAK_WORLD_DELTA_WIRE_OK;
}

BreakWorldDeltaWireResult break_world_delta_wire_decode(
    const void *data, usize size, BreakWorldDeltaWire *out_message) {
    const u8 *bytes = (const u8 *)data;
    BreakWorldDeltaWire decoded;
    BreakWorldDeltaWireResult result = BREAK_WORLD_DELTA_WIRE_INVALID;
    usize offset = BREAK_WORLD_DELTA_WIRE_HEADER_SIZE;
    if (out_message) memset(out_message, 0, sizeof(*out_message));
    if (!data || !out_message) return BREAK_WORLD_DELTA_WIRE_INVALID;
    if (size > BREAK_WORLD_DELTA_WIRE_MAX_BYTES) return BREAK_WORLD_DELTA_WIRE_OVER_LIMIT;
    if (size < BREAK_WORLD_DELTA_WIRE_HEADER_SIZE) return BREAK_WORLD_DELTA_WIRE_INVALID;
    if (memcmp(bytes, "BRWD", 4u) != 0 ||
        get16(bytes + 4u) != BREAK_WORLD_DELTA_WIRE_VERSION) {
        return BREAK_WORLD_DELTA_WIRE_INVALID;
    }

    memset(&decoded, 0, sizeof(decoded));
    decoded.kind = (BreakWorldDeltaWireKind)get16(bytes + 6u);
    decoded.schema_hash = get64(bytes + 8u);
    decoded.level_generation = get64(bytes + 16u);
    decoded.base_snapshot_id = get64(bytes + 24u);
    decoded.target_snapshot_id = get64(bytes + 32u);
    decoded.base_tick = get64(bytes + 40u);
    decoded.target_tick = get64(bytes + 48u);
    decoded.record_count = get32(bytes + 56u);
    result = validate_header(&decoded);
    if (result != BREAK_WORLD_DELTA_WIRE_OK) return result;
    if (decoded.record_count > (size - BREAK_WORLD_DELTA_WIRE_HEADER_SIZE) /
                                   BREAK_WORLD_DELTA_WIRE_RECORD_HEADER_SIZE) {
        return BREAK_WORLD_DELTA_WIRE_INVALID;
    }
    if (decoded.record_count != 0u) {
        decoded.records = calloc(decoded.record_count, sizeof(*decoded.records));
        if (!decoded.records) return BREAK_WORLD_DELTA_WIRE_OVER_LIMIT;
    }

    for (u32 i = 0u; i < decoded.record_count; ++i) {
        BreakWorldDeltaRecord *record = &decoded.records[i];
        u32 payload_size;
        if (size - offset < BREAK_WORLD_DELTA_WIRE_RECORD_HEADER_SIZE) {
            result = BREAK_WORLD_DELTA_WIRE_INVALID;
            goto fail;
        }
        record->kind = (BreakWorldDeltaRecordKind)bytes[offset];
        record->entity = handle_entity(get64(bytes + offset + 1u));
        record->component = get32(bytes + offset + 9u);
        payload_size = get32(bytes + offset + 13u);
        offset += BREAK_WORLD_DELTA_WIRE_RECORD_HEADER_SIZE;
        if ((usize)payload_size > (usize)BREAK_WORLD_DELTA_WIRE_MAX_BYTES - offset) {
            result = BREAK_WORLD_DELTA_WIRE_OVER_LIMIT;
            goto fail;
        }
        if ((usize)payload_size > size - offset) {
            result = BREAK_WORLD_DELTA_WIRE_INVALID;
            goto fail;
        }
        record->size = payload_size;
        record->bytes = payload_size != 0u ? bytes + offset : NULL;
        result = validate_record(&decoded, record);
        if (result != BREAK_WORLD_DELTA_WIRE_OK) goto fail;
        offset += payload_size;
    }
    if (offset != size) {
        result = BREAK_WORLD_DELTA_WIRE_INVALID;
        goto fail;
    }
    *out_message = decoded;
    return BREAK_WORLD_DELTA_WIRE_OK;

fail:
    free(decoded.records);
    return result;
}

void break_world_delta_wire_clear(BreakWorldDeltaWire *message) {
    if (!message) return;
    free(message->records);
    memset(message, 0, sizeof(*message));
}

static bool register_schema_components(World *world,
                                       const BreakComponentSchemaRegistry *schemas) {
    for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
        const BreakComponentSchema *schema = break_schema_lookup(schemas, component);
        if (!schema) continue;
        if (schema->size == 0u || schema->size > UINT32_MAX) return false;
        world_register_component(world, component, (u32)schema->size);
    }
    return true;
}

static bool push_placeholder(Entity **items, u32 *count, u32 *capacity, Entity entity) {
    Entity *grown;
    if (*count == *capacity) {
        u32 next = *capacity == 0u ? 8u : *capacity * 2u;
        grown = (Entity *)realloc(*items, next * sizeof(*grown));
        if (!grown) return false;
        *items = grown;
        *capacity = next;
    }
    (*items)[(*count)++] = entity;
    return true;
}

static Entity create_full_entity(World *world, Entity expected,
                                 Entity **placeholders, u32 *count, u32 *capacity) {
    Entity created;
    if (expected.index == 0u || expected.generation == 0u) return ENTITY_NULL;
    for (;;) {
        created = world_create_entity(world);
        if (created.index == 0u && created.generation == 0u) return created;
        if (created.index > expected.index) return ENTITY_NULL;
        if (created.index == expected.index) break;
        if (!push_placeholder(placeholders, count, capacity, created)) return ENTITY_NULL;
    }
    if (created.generation != expected.generation) {
        world_destroy_entity(world, created);
        world->entities[created.index].generation = expected.generation - 1u;
        created = world_create_entity(world);
    }
    if (created.index != expected.index || created.generation != expected.generation) {
        return ENTITY_NULL;
    }
    return created;
}

static bool create_entities(World *world, const BreakWorldDeltaWire *message, bool full) {
    Entity *placeholders = NULL;
    u32 count = 0u;
    u32 capacity = 0u;
    bool ok = true;
    for (u32 i = 0u; i < message->record_count && ok; ++i) {
        const BreakWorldDeltaRecord *record = &message->records[i];
        Entity created;
        if (record->kind != BREAK_DELTA_ENTITY_CREATE) continue;
        if (record->entity.index == 0u || record->entity.generation == 0u) {
            ok = false;
            break;
        }
        created = full ? create_full_entity(world, record->entity, &placeholders,
                                            &count, &capacity)
                       : world_create_entity(world);
        if (created.index != record->entity.index ||
            created.generation != record->entity.generation) {
            ok = false;
        }
    }
    for (u32 i = 0u; i < count; ++i) {
        world_destroy_entity(world, placeholders[i]);
    }
    free(placeholders);
    return ok;
}

static bool apply_records(World *world, const BreakWorldDeltaWire *message, bool full) {
    for (u32 i = 0u; i < message->record_count; ++i) {
        const BreakWorldDeltaRecord *record = &message->records[i];
        if (record->kind != BREAK_DELTA_ENTITY_DESTROY) continue;
        if (record->entity.index == 0u || record->entity.generation == 0u ||
            !world_entity_exists(world, record->entity)) {
            return false;
        }
        world_destroy_entity(world, record->entity);
    }
    if (!create_entities(world, message, full)) return false;
    for (u32 i = 0u; i < message->record_count; ++i) {
        const BreakWorldDeltaRecord *record = &message->records[i];
        void *component;
        if (record->kind == BREAK_DELTA_ENTITY_CREATE ||
            record->kind == BREAK_DELTA_ENTITY_DESTROY) {
            continue;
        }
        if (record->component >= ECS_MAX_COMPONENTS || record->entity.index == 0u ||
            record->entity.generation == 0u ||
            !world_entity_exists(world, record->entity)) {
            return false;
        }
        if (record->kind == BREAK_DELTA_COMPONENT_REMOVE) {
            component = world_get_component(world, record->entity, record->component);
            if (!component) return false;
            world_remove_component(world, record->entity, record->component);
            continue;
        }
        if (world->component_sizes[record->component] != record->size) return false;
        if (record->kind == BREAK_DELTA_COMPONENT_ADD) {
            if (world_get_component(world, record->entity, record->component)) return false;
            component = world_add_component(world, record->entity, record->component);
        } else if (record->kind == BREAK_DELTA_COMPONENT_UPDATE) {
            component = world_get_component(world, record->entity, record->component);
        } else {
            return false;
        }
        if (!component) return false;
        memcpy(component, record->bytes, record->size);
    }
    return true;
}

BreakWorldDeltaWireResult break_world_delta_wire_rebuild(
    const BreakWorldDeltaWire *message, World *world, const BreakWorldSnapshot *base,
    const BreakComponentSchemaRegistry *schemas, u64 level_generation,
    BreakWorldSnapshot **out_target) {
    BreakWorldDeltaWireResult result;
    BreakWorldSnapshot *current = NULL;
    BreakWorldSnapshot *target = NULL;
    World *staging = NULL;
    bool full;
    if (out_target) *out_target = NULL;
    if (!out_target) return BREAK_WORLD_DELTA_WIRE_INVALID;
    result = validate_message(message, NULL);
    if (result != BREAK_WORLD_DELTA_WIRE_OK) return result;
    if (!schemas) return BREAK_WORLD_DELTA_WIRE_INVALID;
    if (message->level_generation != level_generation) {
        return BREAK_WORLD_DELTA_WIRE_LEVEL_MISMATCH;
    }
    if (break_schema_hash(schemas) != message->schema_hash) {
        return BREAK_WORLD_DELTA_WIRE_SCHEMA_MISMATCH;
    }
    full = message->kind == BREAK_WORLD_DELTA_WIRE_FULL;
    if (full) {
        staging = world_create();
        if (!staging || !register_schema_components(staging, schemas)) {
            result = BREAK_WORLD_DELTA_WIRE_APPLY_FAILED;
            goto done;
        }
    } else {
        if (!world || !base) return BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH;
        if (break_world_snapshot_schema_hash(base) != message->schema_hash) {
            return BREAK_WORLD_DELTA_WIRE_SCHEMA_MISMATCH;
        }
        if (break_world_snapshot_id(base) != message->base_snapshot_id ||
            break_world_snapshot_tick(base) != message->base_tick) {
            return BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH;
        }
        current = break_world_snapshot_build(world, schemas, message->base_tick);
        if (!current || break_world_snapshot_id(current) != message->base_snapshot_id) {
            result = BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH;
            goto done;
        }
        staging = world_clone_deep(world);
        if (!staging) {
            result = BREAK_WORLD_DELTA_WIRE_APPLY_FAILED;
            goto done;
        }
    }
    if (!apply_records(staging, message, full)) {
        result = BREAK_WORLD_DELTA_WIRE_APPLY_FAILED;
        goto done;
    }
    target = break_world_snapshot_build(staging, schemas, message->target_tick);
    if (!target) {
        result = BREAK_WORLD_DELTA_WIRE_APPLY_FAILED;
        goto done;
    }
    if (break_world_snapshot_id(target) != message->target_snapshot_id) {
        result = BREAK_WORLD_DELTA_WIRE_TARGET_MISMATCH;
        goto done;
    }
    *out_target = target;
    target = NULL;
    result = BREAK_WORLD_DELTA_WIRE_OK;

done:
    break_world_snapshot_release(target);
    break_world_snapshot_release(current);
    world_destroy(staging);
    return result;
}
