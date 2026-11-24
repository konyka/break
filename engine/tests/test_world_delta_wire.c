#include "test_framework.h"
#include <ecs/ecs_internal.h>
#include <ecs/world_delta_wire.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define COMP_VALUE 11u
#define COMP_EXTRA 12u
#define COMP_THIRD 13u
#define TEST_LEVEL 7u
#define RICH_LEVEL UINT64_C(0xf123456789abcde0)

#define WIRE_KIND_OFFSET 6u
#define WIRE_BASE_ID_OFFSET 24u
#define WIRE_TARGET_ID_OFFSET 32u
#define WIRE_BASE_TICK_OFFSET 40u
#define WIRE_TARGET_TICK_OFFSET 48u
#define WIRE_COUNT_OFFSET 56u
#define WIRE_RECORDS_OFFSET 60u
#define GOLDEN_SECOND_RECORD_OFFSET 77u
#define GOLDEN_SECOND_COMPONENT_OFFSET 86u
#define GOLDEN_SECOND_SIZE_OFFSET 90u

typedef struct {
    u32 value;
} Value;

typedef struct {
    u64 value;
} Extra;

typedef struct {
    u16 low;
    u16 high;
} Third;

typedef struct {
    BreakComponentSchemaRegistry *schemas;
    World *base_world;
    World *target_world;
    BreakWorldSnapshot *base;
    BreakWorldSnapshot *target;
    BreakWorldDelta *delta;
    BreakWorldDeltaWire delta_message;
    BreakWorldDeltaWire full_message;
} Fixture;

static const u8 golden_payload[] = {0xdeu, 0xadu, 0xbeu, 0xefu};
static const u8 golden_wire[] = {
    0x42u, 0x52u, 0x57u, 0x44u, 0x01u, 0x00u, 0x01u, 0x00u,
    0x88u, 0x77u, 0x66u, 0x55u, 0x44u, 0x33u, 0x22u, 0x11u,
    0x00u, 0xffu, 0xeeu, 0xddu, 0xccu, 0xbbu, 0xaau, 0x99u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x08u, 0x07u, 0x06u, 0x05u, 0x04u, 0x03u, 0x02u, 0x01u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x02u, 0x00u, 0x00u, 0x00u,
    0x00u,
    0x44u, 0x33u, 0x22u, 0x11u, 0x88u, 0x77u, 0x66u, 0x55u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x02u,
    0x44u, 0x33u, 0x22u, 0x11u, 0x88u, 0x77u, 0x66u, 0x55u,
    0x44u, 0x33u, 0x22u, 0x11u, 0x04u, 0x00u, 0x00u, 0x00u,
    0xdeu, 0xadu, 0xbeu, 0xefu
};

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

static bool bytes_are(const u8 *bytes, usize size, u8 value) {
    for (usize i = 0u; i < size; ++i) {
        if (bytes[i] != value) return false;
    }
    return true;
}

static bool message_is_zero(const BreakWorldDeltaWire *message) {
    BreakWorldDeltaWire zero;
    memset(&zero, 0, sizeof(zero));
    return memcmp(message, &zero, sizeof(zero)) == 0;
}

static BreakWorldDeltaWire golden_message(void) {
    static BreakWorldDeltaRecord records[2];
    BreakWorldDeltaWire message;
    memset(&message, 0, sizeof(message));
    memset(records, 0, sizeof(records));
    records[0].kind = BREAK_DELTA_ENTITY_CREATE;
    records[0].entity = (Entity){0x11223344u, 0x55667788u};
    records[1].kind = BREAK_DELTA_COMPONENT_ADD;
    records[1].entity = records[0].entity;
    records[1].component = 0x11223344u;
    records[1].bytes = golden_payload;
    records[1].size = sizeof(golden_payload);
    message.kind = BREAK_WORLD_DELTA_WIRE_FULL;
    message.schema_hash = UINT64_C(0x1122334455667788);
    message.level_generation = UINT64_C(0x99aabbccddeeff00);
    message.target_snapshot_id = UINT64_C(0x0102030405060708);
    message.target_tick = 2u;
    message.record_count = 2u;
    message.records = records;
    return message;
}

static bool register_component(BreakComponentSchemaRegistry *schemas, u32 id,
                               usize size, usize alignment, u32 version) {
    BreakComponentSchema schema;
    memset(&schema, 0, sizeof(schema));
    schema.component_id = id;
    schema.version = version;
    schema.size = size;
    schema.alignment = alignment;
    schema.flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES;
    return break_schema_register(schemas, &schema) == BREAK_SCHEMA_OK;
}

static bool add_value(World *world, Entity entity, u32 value) {
    Value *component = (Value *)world_add_component(world, entity, COMP_VALUE);
    if (!component) return false;
    component->value = value;
    return true;
}

static bool add_extra(World *world, Entity entity, u64 value) {
    Extra *component = (Extra *)world_add_component(world, entity, COMP_EXTRA);
    if (!component) return false;
    component->value = value;
    return true;
}

static bool add_third(World *world, Entity entity, u16 low, u16 high) {
    Third *component = (Third *)world_add_component(world, entity, COMP_THIRD);
    if (!component) return false;
    component->low = low;
    component->high = high;
    return true;
}

static bool message_from_delta(const BreakWorldDelta *delta, u64 level_generation,
                               BreakWorldDeltaWire *out_message) {
    BreakWorldDeltaWire message;
    usize count = break_world_delta_record_count(delta);
    memset(&message, 0, sizeof(message));
    if (count > UINT32_MAX) return false;
    message.kind = BREAK_WORLD_DELTA_WIRE_DELTA;
    message.schema_hash = break_world_delta_target_schema_hash(delta);
    message.level_generation = level_generation;
    message.base_snapshot_id = break_world_delta_base_id(delta);
    message.target_snapshot_id = break_world_delta_target_id(delta);
    message.base_tick = break_world_delta_base_tick(delta);
    message.target_tick = break_world_delta_target_tick(delta);
    message.record_count = (u32)count;
    if (count != 0u) {
        message.records = calloc(count, sizeof(*message.records));
        if (!message.records) return false;
        for (usize i = 0u; i < count; ++i) {
            if (!break_world_delta_record_at(delta, i, &message.records[i])) {
                free(message.records);
                return false;
            }
        }
    }
    *out_message = message;
    return true;
}

static bool message_from_snapshot(const BreakWorldSnapshot *snapshot, u64 level_generation,
                                  BreakWorldDeltaWire *out_message) {
    BreakWorldDeltaWire message;
    usize entity_count = break_world_snapshot_entity_count(snapshot);
    usize count = 0u;
    usize slot = 0u;
    memset(&message, 0, sizeof(message));
    for (usize i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        ++count;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component,
                                                      &bytes, &size)) {
                ++count;
            }
        }
    }
    if (count > UINT32_MAX) return false;
    message.kind = BREAK_WORLD_DELTA_WIRE_FULL;
    message.schema_hash = break_world_snapshot_schema_hash(snapshot);
    message.level_generation = level_generation;
    message.target_snapshot_id = break_world_snapshot_id(snapshot);
    message.target_tick = break_world_snapshot_tick(snapshot);
    message.record_count = (u32)count;
    if (count != 0u) {
        message.records = calloc(count, sizeof(*message.records));
        if (!message.records) return false;
    }
    for (usize i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        message.records[slot].kind = BREAK_DELTA_ENTITY_CREATE;
        message.records[slot].entity = entity;
        ++slot;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component,
                                                      &bytes, &size)) {
                message.records[slot].kind = BREAK_DELTA_COMPONENT_ADD;
                message.records[slot].entity = entity;
                message.records[slot].component = component;
                message.records[slot].bytes = bytes;
                message.records[slot].size = size;
                ++slot;
            }
        }
    }
    *out_message = message;
    return true;
}

static bool fixture_init(Fixture *fixture) {
    Entity first;
    Entity second;
    Entity third;
    memset(fixture, 0, sizeof(*fixture));
    fixture->schemas = break_schema_registry_create();
    if (!fixture->schemas ||
        !register_component(fixture->schemas, COMP_VALUE, sizeof(Value), _Alignof(Value), 1u) ||
        !register_component(fixture->schemas, COMP_EXTRA, sizeof(Extra), _Alignof(Extra), 2u)) {
        return false;
    }
    fixture->base_world = world_create();
    fixture->target_world = world_create();
    if (!fixture->base_world || !fixture->target_world) return false;
    world_register_component(fixture->base_world, COMP_VALUE, sizeof(Value));
    world_register_component(fixture->base_world, COMP_EXTRA, sizeof(Extra));
    world_register_component(fixture->target_world, COMP_VALUE, sizeof(Value));
    world_register_component(fixture->target_world, COMP_EXTRA, sizeof(Extra));

    first = world_create_entity(fixture->base_world);
    second = world_create_entity(fixture->base_world);
    third = world_create_entity(fixture->base_world);
    if (!add_value(fixture->base_world, first, 10u) ||
        !add_value(fixture->base_world, second, 20u) ||
        !add_extra(fixture->base_world, second, 200u) ||
        !add_value(fixture->base_world, third, 30u)) {
        return false;
    }

    first = world_create_entity(fixture->target_world);
    second = world_create_entity(fixture->target_world);
    third = world_create_entity(fixture->target_world);
    if (!add_value(fixture->target_world, first, 11u) ||
        !add_extra(fixture->target_world, first, 101u) ||
        !add_value(fixture->target_world, second, 20u) ||
        !add_value(fixture->target_world, third, 30u)) {
        return false;
    }
    world_destroy_entity(fixture->target_world, third);
    third = world_create_entity(fixture->target_world);
    if (third.index != 3u || third.generation != 3u ||
        !add_value(fixture->target_world, third, 40u)) {
        return false;
    }

    fixture->base = break_world_snapshot_build(fixture->base_world, fixture->schemas, 10u);
    fixture->target = break_world_snapshot_build(fixture->target_world, fixture->schemas, 20u);
    if (!fixture->base || !fixture->target) return false;
    fixture->delta = break_world_delta_diff(fixture->base, fixture->target);
    if (!fixture->delta ||
        !message_from_delta(fixture->delta, TEST_LEVEL, &fixture->delta_message) ||
        !message_from_snapshot(fixture->target, TEST_LEVEL, &fixture->full_message)) {
        return false;
    }
    return true;
}

static void fixture_destroy(Fixture *fixture) {
    free(fixture->full_message.records);
    free(fixture->delta_message.records);
    break_world_delta_release(fixture->delta);
    break_world_snapshot_release(fixture->target);
    break_world_snapshot_release(fixture->base);
    world_destroy(fixture->target_world);
    world_destroy(fixture->base_world);
    break_schema_registry_destroy(fixture->schemas);
    memset(fixture, 0, sizeof(*fixture));
}

static bool rich_fixture_init(Fixture *fixture) {
    Entity entities[4];
    memset(fixture, 0, sizeof(*fixture));
    fixture->schemas = break_schema_registry_create();
    if (!fixture->schemas ||
        !register_component(fixture->schemas, COMP_VALUE, sizeof(Value), _Alignof(Value), 1u) ||
        !register_component(fixture->schemas, COMP_EXTRA, sizeof(Extra), _Alignof(Extra), 2u) ||
        !register_component(fixture->schemas, COMP_THIRD, sizeof(Third), _Alignof(Third), 3u)) {
        return false;
    }
    fixture->base_world = world_create();
    fixture->target_world = world_create();
    if (!fixture->base_world || !fixture->target_world) return false;
    world_register_component(fixture->base_world, COMP_VALUE, sizeof(Value));
    world_register_component(fixture->base_world, COMP_EXTRA, sizeof(Extra));
    world_register_component(fixture->base_world, COMP_THIRD, sizeof(Third));
    world_register_component(fixture->target_world, COMP_VALUE, sizeof(Value));
    world_register_component(fixture->target_world, COMP_EXTRA, sizeof(Extra));
    world_register_component(fixture->target_world, COMP_THIRD, sizeof(Third));

    for (u32 i = 0u; i < 4u; ++i) entities[i] = world_create_entity(fixture->base_world);
    if (!add_value(fixture->base_world, entities[0], 10u) ||
        !add_extra(fixture->base_world, entities[0], 100u) ||
        !add_third(fixture->base_world, entities[0], 1u, 2u) ||
        !add_value(fixture->base_world, entities[1], 20u) ||
        !add_value(fixture->base_world, entities[2], 30u) ||
        !add_extra(fixture->base_world, entities[2], 300u) ||
        !add_third(fixture->base_world, entities[2], 3u, 4u) ||
        !add_value(fixture->base_world, entities[3], 40u) ||
        !add_third(fixture->base_world, entities[3], 5u, 6u)) {
        return false;
    }

    for (u32 i = 0u; i < 4u; ++i) entities[i] = world_create_entity(fixture->target_world);
    if (!add_value(fixture->target_world, entities[0], 11u) ||
        !add_third(fixture->target_world, entities[0], 7u, 8u) ||
        !add_value(fixture->target_world, entities[1], 20u) ||
        !add_extra(fixture->target_world, entities[1], 200u) ||
        !add_third(fixture->target_world, entities[1], 9u, 10u) ||
        !add_value(fixture->target_world, entities[2], 30u) ||
        !add_extra(fixture->target_world, entities[2], 300u) ||
        !add_third(fixture->target_world, entities[2], 3u, 4u) ||
        !add_value(fixture->target_world, entities[3], 40u) ||
        !add_third(fixture->target_world, entities[3], 5u, 6u)) {
        return false;
    }
    world_destroy_entity(fixture->target_world, entities[2]);
    entities[2] = world_create_entity(fixture->target_world);
    if (entities[2].index != 3u || entities[2].generation != 3u ||
        !add_value(fixture->target_world, entities[2], 33u) ||
        !add_extra(fixture->target_world, entities[2], 333u) ||
        !add_third(fixture->target_world, entities[2], 11u, 12u)) {
        return false;
    }

    fixture->base = break_world_snapshot_build(fixture->base_world, fixture->schemas,
                                                UINT64_C(0x8000000000000000));
    fixture->target = break_world_snapshot_build(fixture->target_world, fixture->schemas,
                                                  UINT64_C(0x8000000000000001));
    if (!fixture->base || !fixture->target) return false;
    fixture->delta = break_world_delta_diff(fixture->base, fixture->target);
    if (!fixture->delta ||
        !message_from_delta(fixture->delta, RICH_LEVEL, &fixture->delta_message) ||
        !message_from_snapshot(fixture->target, RICH_LEVEL, &fixture->full_message)) {
        return false;
    }
    return true;
}

static bool messages_equal(const BreakWorldDeltaWire *a, const BreakWorldDeltaWire *b) {
    if (a->kind != b->kind || a->schema_hash != b->schema_hash ||
        a->level_generation != b->level_generation ||
        a->base_snapshot_id != b->base_snapshot_id ||
        a->target_snapshot_id != b->target_snapshot_id || a->base_tick != b->base_tick ||
        a->target_tick != b->target_tick || a->record_count != b->record_count) {
        return false;
    }
    for (u32 i = 0u; i < a->record_count; ++i) {
        const BreakWorldDeltaRecord *left = &a->records[i];
        const BreakWorldDeltaRecord *right = &b->records[i];
        if (left->kind != right->kind || left->entity.index != right->entity.index ||
            left->entity.generation != right->entity.generation ||
            left->component != right->component || left->size != right->size) {
            return false;
        }
        if (left->size != 0u && memcmp(left->bytes, right->bytes, left->size) != 0) return false;
    }
    return true;
}

static bool encode_alloc(const BreakWorldDeltaWire *message, u8 **out_wire, usize *out_size) {
    u8 *wire;
    usize size = 0u;
    *out_wire = NULL;
    *out_size = 0u;
    if (break_world_delta_wire_encoded_size(message, &size) != BREAK_WORLD_DELTA_WIRE_OK) {
        return false;
    }
    wire = (u8 *)malloc(size ? size : 1u);
    if (!wire) return false;
    if (break_world_delta_wire_encode(message, wire, size, &size) != BREAK_WORLD_DELTA_WIRE_OK) {
        free(wire);
        return false;
    }
    *out_wire = wire;
    *out_size = size;
    return true;
}

static bool canonical_reencoding(const void *initial, usize size, u32 rounds) {
    u8 *first = (u8 *)malloc(size ? size : 1u);
    u8 *second = (u8 *)malloc(size ? size : 1u);
    const u8 *current = (const u8 *)initial;
    u8 *next = first;
    bool ok = true;
    if (!first || !second) {
        free(second);
        free(first);
        return false;
    }
    for (u32 round = 0u; round < rounds; ++round) {
        BreakWorldDeltaWire decoded;
        usize encoded_size = 0u;
        memset(&decoded, 0, sizeof(decoded));
        if (break_world_delta_wire_decode(current, size, &decoded) != BREAK_WORLD_DELTA_WIRE_OK) {
            ok = false;
            break;
        }
        if (break_world_delta_wire_encode(&decoded, next, size, &encoded_size) !=
                BREAK_WORLD_DELTA_WIRE_OK ||
            encoded_size != size || memcmp(next, current, size) != 0) {
            break_world_delta_wire_clear(&decoded);
            ok = false;
            break;
        }
        break_world_delta_wire_clear(&decoded);
        current = next;
        next = (current == first) ? second : first;
    }
    free(second);
    free(first);
    return ok;
}

static void check_decode_rejection(const void *data, usize size,
                                   BreakWorldDeltaWireResult expected) {
    BreakWorldDeltaWire decoded;
    BreakWorldDeltaWireResult actual;
    memset(&decoded, 0xa5, sizeof(decoded));
    actual = break_world_delta_wire_decode(data, size, &decoded);
    if (actual != expected) {
        printf("  decode result %d, expected %d, size %llu\n", (int)actual, (int)expected,
               (unsigned long long)size);
    }
    ASSERT_EQ(actual, expected);
    ASSERT_TRUE(message_is_zero(&decoded));
    break_world_delta_wire_clear(&decoded);
}

static void check_encode_rejection(const BreakWorldDeltaWire *message,
                                   BreakWorldDeltaWireResult expected) {
    u8 out[128];
    usize size = 99u;
    memset(out, 0xa5, sizeof(out));
    ASSERT_EQ(break_world_delta_wire_encoded_size(message, &size), expected);
    ASSERT_EQ(size, 0u);
    size = 99u;
    ASSERT_EQ(break_world_delta_wire_encode(message, out, sizeof(out), &size), expected);
    ASSERT_EQ(size, 0u);
    ASSERT_TRUE(bytes_are(out, sizeof(out), 0xa5u));
}

static void check_delta_rebuild_rejection(Fixture *fixture,
                                          const BreakWorldDeltaWire *message,
                                          const BreakComponentSchemaRegistry *schemas,
                                          u64 level, BreakWorldDeltaWireResult expected) {
    BreakWorldSnapshot *before = break_world_snapshot_build(
        fixture->base_world, fixture->schemas, break_world_snapshot_tick(fixture->base));
    BreakWorldSnapshot *after = NULL;
    BreakWorldSnapshot *rebuilt = (BreakWorldSnapshot *)(uintptr_t)1u;
    ASSERT_NOT_NULL(before);
    ASSERT_EQ(break_world_delta_wire_rebuild(message, fixture->base_world, fixture->base,
                                             schemas, level, &rebuilt),
              expected);
    ASSERT_TRUE(rebuilt == NULL);
    after = break_world_snapshot_build(fixture->base_world, fixture->schemas,
                                       break_world_snapshot_tick(fixture->base));
    ASSERT_NOT_NULL(after);
    ASSERT_EQ(break_world_snapshot_id(after), break_world_snapshot_id(before));
    break_world_snapshot_release(after);
    break_world_snapshot_release(before);
}

TEST(world_delta_wire_golden_full_layout_and_round_trip) {
    BreakWorldDeltaWire message = golden_message();
    BreakWorldDeltaWire decoded;
    u8 out[sizeof(golden_wire)];
    u8 input_copy[sizeof(golden_wire)];
    usize size = 0u;

    ASSERT_EQ(sizeof(golden_wire), 98u);
    ASSERT_EQ(BREAK_WORLD_DELTA_WIRE_HEADER_SIZE, 60u);
    ASSERT_EQ(break_world_delta_wire_encoded_size(&message, &size), BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(size, sizeof(golden_wire));
    memset(out, 0xa5, sizeof(out));
    ASSERT_EQ(break_world_delta_wire_encode(&message, out, sizeof(out), &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(size, sizeof(golden_wire));
    ASSERT_TRUE(memcmp(out, golden_wire, sizeof(golden_wire)) == 0);
    memcpy(input_copy, out, sizeof(out));
    memset(&decoded, 0xa5, sizeof(decoded));
    ASSERT_EQ(break_world_delta_wire_decode(out, size, &decoded), BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_TRUE(messages_equal(&message, &decoded));
    ASSERT_EQ(decoded.records[1].bytes, out + 94u);
    ASSERT_TRUE(memcmp(out, input_copy, sizeof(out)) == 0);
    break_world_delta_wire_clear(&decoded);
    ASSERT_TRUE(message_is_zero(&decoded));
}

TEST(world_delta_wire_unaligned_decode_borrows_input) {
    union {
        u64 alignment;
        u8 bytes[sizeof(golden_wire) + 1u];
    } storage;
    BreakWorldDeltaWire decoded;
    memset(&storage, 0, sizeof(storage));
    memcpy(storage.bytes + 1u, golden_wire, sizeof(golden_wire));
    ASSERT_EQ(break_world_delta_wire_decode(storage.bytes + 1u, sizeof(golden_wire), &decoded),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(decoded.schema_hash, UINT64_C(0x1122334455667788));
    ASSERT_EQ(decoded.records[0].entity.index, 0x11223344u);
    ASSERT_EQ(decoded.records[0].entity.generation, 0x55667788u);
    ASSERT_EQ(decoded.records[1].component, 0x11223344u);
    ASSERT_EQ(decoded.records[1].bytes, storage.bytes + 1u + 94u);
    break_world_delta_wire_clear(&decoded);
}

TEST(world_delta_wire_full_rebuilds_snapshot_from_empty_base) {
    Fixture fixture;
    BreakWorldDeltaWire decoded;
    BreakWorldSnapshot *rebuilt = NULL;
    u8 *wire = NULL;
    u8 *wire_copy = NULL;
    usize size = 0u;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(fixture.full_message.record_count, 7u);
    ASSERT_EQ(break_world_delta_wire_encoded_size(&fixture.full_message, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    wire = malloc(size);
    wire_copy = malloc(size);
    ASSERT_NOT_NULL(wire);
    ASSERT_NOT_NULL(wire_copy);
    ASSERT_EQ(break_world_delta_wire_encode(&fixture.full_message, wire, size, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    memcpy(wire_copy, wire, size);
    ASSERT_EQ(break_world_delta_wire_decode(wire, size, &decoded), BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(break_world_delta_wire_rebuild(&decoded, NULL, NULL, fixture.schemas,
                                             TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_NOT_NULL(rebuilt);
    ASSERT_EQ(break_world_snapshot_id(rebuilt), break_world_snapshot_id(fixture.target));
    ASSERT_EQ(break_world_snapshot_tick(rebuilt), 20u);
    ASSERT_EQ(break_world_snapshot_entity_count(rebuilt), 3u);
    ASSERT_TRUE(break_world_snapshot_has_entity(rebuilt, (Entity){3u, 3u}));
    ASSERT_TRUE(memcmp(wire, wire_copy, size) == 0);
    break_world_snapshot_release(rebuilt);
    break_world_delta_wire_clear(&decoded);
    free(wire_copy);
    free(wire);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_delta_round_trip_rebuilds_all_record_kinds) {
    Fixture fixture;
    BreakWorldDeltaWire decoded;
    BreakWorldSnapshot *rebuilt = NULL;
    BreakWorldSnapshot *caller_after = NULL;
    u8 *wire = NULL;
    usize size = 0u;
    bool kinds[5] = {false, false, false, false, false};
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(fixture.delta_message.record_count, 6u);
    for (u32 i = 0u; i < fixture.delta_message.record_count; ++i) {
        kinds[fixture.delta_message.records[i].kind] = true;
    }
    for (u32 i = 0u; i < 5u; ++i) ASSERT_TRUE(kinds[i]);
    ASSERT_EQ(break_world_delta_wire_encoded_size(&fixture.delta_message, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    wire = malloc(size);
    ASSERT_NOT_NULL(wire);
    ASSERT_EQ(break_world_delta_wire_encode(&fixture.delta_message, wire, size, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(break_world_delta_wire_decode(wire, size, &decoded), BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_TRUE(messages_equal(&fixture.delta_message, &decoded));
    ASSERT_EQ(break_world_delta_wire_rebuild(&decoded, fixture.base_world, fixture.base,
                                             fixture.schemas, TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_NOT_NULL(rebuilt);
    ASSERT_EQ(break_world_snapshot_id(rebuilt), break_world_snapshot_id(fixture.target));
    ASSERT_EQ(((Value *)world_get_component(fixture.base_world, (Entity){1u, 1u}, COMP_VALUE))->value,
              10u);
    ASSERT_TRUE(world_get_component(fixture.base_world, (Entity){1u, 1u}, COMP_EXTRA) == NULL);
    ASSERT_TRUE(world_entity_exists(fixture.base_world, (Entity){3u, 1u}));
    ASSERT_FALSE(world_entity_exists(fixture.base_world, (Entity){3u, 3u}));
    caller_after = break_world_snapshot_build(fixture.base_world, fixture.schemas, 10u);
    ASSERT_NOT_NULL(caller_after);
    ASSERT_EQ(break_world_snapshot_id(caller_after), break_world_snapshot_id(fixture.base));
    break_world_snapshot_release(caller_after);
    break_world_snapshot_release(rebuilt);
    break_world_delta_wire_clear(&decoded);
    free(wire);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_decode_rejects_magic_version_and_kind) {
    u8 wire[sizeof(golden_wire)];
    for (usize i = 0u; i < 4u; ++i) {
        memcpy(wire, golden_wire, sizeof(wire));
        wire[i] ^= 1u;
        check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    }
    memcpy(wire, golden_wire, sizeof(wire));
    wire[4] = 2u;
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    wire[5] = 1u;
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    wire[WIRE_KIND_OFFSET] = 0u;
    wire[WIRE_KIND_OFFSET + 1u] = 0u;
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    wire[WIRE_KIND_OFFSET] = 3u;
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    wire[WIRE_RECORDS_OFFSET] = 5u;
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    check_decode_rejection(NULL, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_EQ(break_world_delta_wire_decode(golden_wire, sizeof(golden_wire), NULL),
              BREAK_WORLD_DELTA_WIRE_INVALID);
}

TEST(world_delta_wire_decode_rejects_every_truncation_and_trailing_bytes) {
    u8 wire[sizeof(golden_wire) + 1u];
    for (usize size = 0u; size < sizeof(golden_wire); ++size) {
        check_decode_rejection(golden_wire, size, BREAK_WORLD_DELTA_WIRE_INVALID);
    }
    memcpy(wire, golden_wire, sizeof(golden_wire));
    wire[sizeof(golden_wire)] = 0u;
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    wire[sizeof(golden_wire)] = 0x7fu;
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_TRUE(memcmp(wire, golden_wire, sizeof(golden_wire)) == 0);
}

TEST(world_delta_wire_decode_enforces_count_and_byte_limits) {
    u8 wire[sizeof(golden_wire)];
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + WIRE_COUNT_OFFSET, 0u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + WIRE_COUNT_OFFSET, 1u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + WIRE_COUNT_OFFSET, 3u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + WIRE_COUNT_OFFSET, BREAK_WORLD_DELTA_WIRE_MAX_RECORD_COUNT + 1u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + GOLDEN_SECOND_SIZE_OFFSET, BREAK_WORLD_DELTA_WIRE_MAX_BYTES);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + GOLDEN_SECOND_SIZE_OFFSET, UINT32_MAX);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
    check_decode_rejection(golden_wire, (usize)BREAK_WORLD_DELTA_WIRE_MAX_BYTES + 1u,
                           BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
}

TEST(world_delta_wire_decode_rejects_invalid_record_shapes) {
    u8 wire[sizeof(golden_wire)];
    memcpy(wire, golden_wire, sizeof(wire));
    memset(wire + WIRE_RECORDS_OFFSET + 1u, 0, 8u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + GOLDEN_SECOND_COMPONENT_OFFSET, 0u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + WIRE_RECORDS_OFFSET + 9u, 1u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + WIRE_RECORDS_OFFSET + 13u, 1u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + GOLDEN_SECOND_SIZE_OFFSET, 0u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + GOLDEN_SECOND_SIZE_OFFSET, 3u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put32(wire + GOLDEN_SECOND_SIZE_OFFSET, 5u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
}

TEST(world_delta_wire_full_requires_zero_base_and_ordered_ticks) {
    u8 wire[sizeof(golden_wire)];
    memcpy(wire, golden_wire, sizeof(wire));
    put64(wire + WIRE_BASE_ID_OFFSET, 1u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put64(wire + WIRE_BASE_TICK_OFFSET, 1u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    put64(wire + WIRE_TARGET_TICK_OFFSET, 0u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    wire[WIRE_KIND_OFFSET] = BREAK_WORLD_DELTA_WIRE_DELTA;
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    wire[WIRE_KIND_OFFSET] = BREAK_WORLD_DELTA_WIRE_DELTA;
    put64(wire + WIRE_BASE_ID_OFFSET, 1u);
    put64(wire + WIRE_BASE_TICK_OFFSET, 2u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
    memcpy(wire, golden_wire, sizeof(wire));
    wire[WIRE_KIND_OFFSET] = BREAK_WORLD_DELTA_WIRE_DELTA;
    put64(wire + WIRE_BASE_ID_OFFSET, 1u);
    put64(wire + WIRE_BASE_TICK_OFFSET, 3u);
    check_decode_rejection(wire, sizeof(wire), BREAK_WORLD_DELTA_WIRE_INVALID);
}

TEST(world_delta_wire_encode_validation_clears_size_and_preserves_output) {
    BreakWorldDeltaWire message = golden_message();
    u8 out[sizeof(golden_wire)];
    usize size = 99u;
    check_encode_rejection(NULL, BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_EQ(break_world_delta_wire_encoded_size(&message, NULL),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_EQ(break_world_delta_wire_encode(&message, NULL, sizeof(out), &size),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_EQ(size, 0u);
    size = 99u;
    ASSERT_EQ(break_world_delta_wire_encode(&message, out, sizeof(out), NULL),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_EQ(size, 99u);
    memset(out, 0xa5, sizeof(out));
    ASSERT_EQ(break_world_delta_wire_encode(&message, out, sizeof(out) - 1u, &size),
              BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
    ASSERT_EQ(size, 0u);
    ASSERT_TRUE(bytes_are(out, sizeof(out), 0xa5u));

    message.base_snapshot_id = 1u;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.base_tick = 1u;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.target_tick = 0u;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.records[0].entity = ENTITY_NULL;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.records[1].component = 0u;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.records[1].size = 0u;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.records[1].bytes = NULL;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.records[0].kind = (BreakWorldDeltaRecordKind)5;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.record_count = BREAK_WORLD_DELTA_WIRE_MAX_RECORD_COUNT + 1u;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
    message = golden_message();
    message.records = NULL;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_INVALID);
    message = golden_message();
    message.records[1].size = BREAK_WORLD_DELTA_WIRE_MAX_BYTES;
    check_encode_rejection(&message, BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
}

TEST(world_delta_wire_rebuild_rejects_target_hash_and_payload_tampering) {
    Fixture fixture;
    BreakWorldDeltaWire message;
    BreakWorldDeltaRecord records[6];
    u32 changed_value = 12u;
    ASSERT_TRUE(fixture_init(&fixture));
    message = fixture.delta_message;
    message.target_snapshot_id ^= 1u;
    check_delta_rebuild_rejection(&fixture, &message, fixture.schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_TARGET_MISMATCH);

    message = fixture.delta_message;
    memcpy(records, fixture.delta_message.records, sizeof(records));
    message.records = records;
    for (u32 i = 0u; i < message.record_count; ++i) {
        if (records[i].kind == BREAK_DELTA_COMPONENT_UPDATE) {
            records[i].bytes = &changed_value;
            break;
        }
    }
    check_delta_rebuild_rejection(&fixture, &message, fixture.schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_TARGET_MISMATCH);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_rebuild_rejects_base_schema_level_and_tick_mismatches) {
    Fixture fixture;
    BreakWorldDeltaWire message;
    BreakComponentSchemaRegistry *changed_schemas;
    BreakWorldSnapshot *rebuilt = (BreakWorldSnapshot *)(uintptr_t)1u;
    ASSERT_TRUE(fixture_init(&fixture));
    message = fixture.delta_message;
    message.base_snapshot_id ^= 1u;
    check_delta_rebuild_rejection(&fixture, &message, fixture.schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH);
    message = fixture.delta_message;
    message.base_tick = 9u;
    check_delta_rebuild_rejection(&fixture, &message, fixture.schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH);
    message = fixture.delta_message;
    message.target_tick = 19u;
    check_delta_rebuild_rejection(&fixture, &message, fixture.schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_TARGET_MISMATCH);
    message = fixture.delta_message;
    message.schema_hash ^= 1u;
    check_delta_rebuild_rejection(&fixture, &message, fixture.schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_SCHEMA_MISMATCH);
    check_delta_rebuild_rejection(&fixture, &fixture.delta_message, fixture.schemas,
                                  TEST_LEVEL + 1u, BREAK_WORLD_DELTA_WIRE_LEVEL_MISMATCH);

    changed_schemas = break_schema_registry_create();
    ASSERT_NOT_NULL(changed_schemas);
    ASSERT_TRUE(register_component(changed_schemas, COMP_VALUE, sizeof(Value), _Alignof(Value), 9u));
    ASSERT_TRUE(register_component(changed_schemas, COMP_EXTRA, sizeof(Extra), _Alignof(Extra), 2u));
    check_delta_rebuild_rejection(&fixture, &fixture.delta_message, changed_schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_SCHEMA_MISMATCH);
    break_schema_registry_destroy(changed_schemas);

    ASSERT_EQ(break_world_delta_wire_rebuild(&fixture.delta_message, fixture.target_world,
                                             fixture.base, fixture.schemas, TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH);
    ASSERT_TRUE(rebuilt == NULL);
    rebuilt = (BreakWorldSnapshot *)(uintptr_t)1u;
    ASSERT_EQ(break_world_delta_wire_rebuild(&fixture.delta_message, fixture.base_world,
                                             fixture.target, fixture.schemas, TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH);
    ASSERT_TRUE(rebuilt == NULL);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_rebuild_rejects_invalid_application_without_mutation) {
    Fixture fixture;
    BreakWorldDeltaWire message;
    BreakWorldDeltaRecord records[6];
    ASSERT_TRUE(fixture_init(&fixture));
    message = fixture.delta_message;
    memcpy(records, fixture.delta_message.records, sizeof(records));
    message.records = records;
    for (u32 i = 0u; i < message.record_count; ++i) {
        if (records[i].kind == BREAK_DELTA_ENTITY_CREATE) {
            records[i].entity.generation = 9u;
            break;
        }
    }
    check_delta_rebuild_rejection(&fixture, &message, fixture.schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_APPLY_FAILED);
    message = fixture.delta_message;
    message.base_snapshot_id = 1u;
    message.kind = BREAK_WORLD_DELTA_WIRE_FULL;
    check_delta_rebuild_rejection(&fixture, &message, fixture.schemas, TEST_LEVEL,
                                  BREAK_WORLD_DELTA_WIRE_INVALID);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_clear_and_null_rebuild_arguments_are_safe) {
    Fixture fixture;
    BreakWorldSnapshot *rebuilt = (BreakWorldSnapshot *)(uintptr_t)1u;
    break_world_delta_wire_clear(NULL);
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(break_world_delta_wire_rebuild(NULL, fixture.base_world, fixture.base,
                                             fixture.schemas, TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_TRUE(rebuilt == NULL);
    rebuilt = (BreakWorldSnapshot *)(uintptr_t)1u;
    ASSERT_EQ(break_world_delta_wire_rebuild(&fixture.delta_message, NULL, fixture.base,
                                             fixture.schemas, TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH);
    ASSERT_TRUE(rebuilt == NULL);
    ASSERT_EQ(break_world_delta_wire_rebuild(&fixture.delta_message, fixture.base_world,
                                             fixture.base, fixture.schemas, TEST_LEVEL, NULL),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    fixture_destroy(&fixture);
}


TEST(world_delta_wire_full_rebuilds_sparse_entity_indices) {
    Fixture fixture;
    World *world;
    Entity first, second, third;
    BreakWorldSnapshot *snapshot;
    BreakWorldDeltaWire message;
    BreakWorldDeltaWire decoded;
    BreakWorldSnapshot *rebuilt = NULL;
    u8 *wire = NULL;
    usize size = 0u;
    ASSERT_TRUE(fixture_init(&fixture));
    world = world_create();
    ASSERT_NOT_NULL(world);
    world_register_component(world, COMP_VALUE, sizeof(Value));
    first = world_create_entity(world);
    second = world_create_entity(world);
    third = world_create_entity(world);
    ASSERT_EQ(first.index, 1u);
    ASSERT_EQ(second.index, 2u);
    ASSERT_EQ(third.index, 3u);
    world_destroy_entity(world, second);
    ASSERT_TRUE(add_value(world, first, 5u));
    ASSERT_TRUE(add_value(world, third, 7u));
    snapshot = break_world_snapshot_build(world, fixture.schemas, 20u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_EQ(break_world_snapshot_entity_count(snapshot), 2u);
    ASSERT_TRUE(message_from_snapshot(snapshot, TEST_LEVEL, &message));
    ASSERT_EQ(break_world_delta_wire_encoded_size(&message, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    wire = (u8 *)malloc(size);
    ASSERT_NOT_NULL(wire);
    ASSERT_EQ(break_world_delta_wire_encode(&message, wire, size, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(break_world_delta_wire_decode(wire, size, &decoded),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(break_world_delta_wire_rebuild(&decoded, NULL, NULL, fixture.schemas,
                                             TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_NOT_NULL(rebuilt);
    ASSERT_EQ(break_world_snapshot_id(rebuilt), break_world_snapshot_id(snapshot));
    break_world_snapshot_release(rebuilt);
    break_world_delta_wire_clear(&decoded);
    free(wire);
    break_world_snapshot_release(snapshot);
    free(message.records);
    world_destroy(world);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_rejects_negative_record_kind) {
    Fixture fixture;
    BreakWorldDeltaWire message = golden_message();
    BreakWorldSnapshot *rebuilt = NULL;
    u8 out[64];
    usize size = 0u;
    message.records[0].kind = (BreakWorldDeltaRecordKind)-1;
    ASSERT_EQ(break_world_delta_wire_encoded_size(&message, &size),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_EQ(size, 0u);
    ASSERT_EQ(break_world_delta_wire_encode(&message, out, sizeof(out), &size),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_EQ(size, 0u);
    ASSERT_TRUE(fixture_init(&fixture));
    fixture.delta_message.records[0].kind = (BreakWorldDeltaRecordKind)-1;
    ASSERT_EQ(break_world_delta_wire_rebuild(&fixture.delta_message, NULL, fixture.base,
                                             fixture.schemas, TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_TRUE(rebuilt == NULL);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_rejects_remove_record_with_payload) {
    Fixture fixture;
    BreakWorldDeltaWire decoded;
    u8 *wire = NULL;
    usize size = 0u;
    usize offset = WIRE_RECORDS_OFFSET;
    bool found = false;
    ASSERT_TRUE(fixture_init(&fixture));
    for (u32 i = 0u; i < fixture.delta_message.record_count; ++i) {
        BreakWorldDeltaRecord *record = &fixture.delta_message.records[i];
        if (!found && record->kind == BREAK_DELTA_COMPONENT_REMOVE) {
            found = true;
            break;
        }
        offset += 17u + record->size;
    }
    ASSERT_TRUE(found);
    ASSERT_EQ(break_world_delta_wire_encoded_size(&fixture.delta_message, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    wire = (u8 *)malloc(size);
    ASSERT_NOT_NULL(wire);
    ASSERT_EQ(break_world_delta_wire_encode(&fixture.delta_message, wire, size, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    put32(wire + offset + 13u, 4u);
    ASSERT_EQ(break_world_delta_wire_decode(wire, size, &decoded),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_TRUE(message_is_zero(&decoded));
    free(wire);
    for (u32 i = 0u; i < fixture.delta_message.record_count; ++i) {
        if (fixture.delta_message.records[i].kind == BREAK_DELTA_COMPONENT_REMOVE) {
            fixture.delta_message.records[i].size = 4u;
            break;
        }
    }
    size = 0u;
    ASSERT_EQ(break_world_delta_wire_encoded_size(&fixture.delta_message, &size),
              BREAK_WORLD_DELTA_WIRE_INVALID);
    ASSERT_EQ(size, 0u);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_multi_entity_component_full_delta_are_canonical) {
    Fixture fixture;
    BreakWorldDeltaWire decoded;
    BreakWorldSnapshot *rebuilt = NULL;
    u8 *delta_wire = NULL;
    u8 *full_wire = NULL;
    usize delta_size = 0u;
    usize full_size = 0u;
    bool kinds[5] = {false, false, false, false, false};
    ASSERT_TRUE(rich_fixture_init(&fixture));
    ASSERT_EQ(fixture.delta_message.record_count, 10u);
    ASSERT_EQ(fixture.full_message.record_count, 14u);
    for (u32 i = 0u; i < fixture.delta_message.record_count; ++i) {
        kinds[fixture.delta_message.records[i].kind] = true;
    }
    for (u32 i = 0u; i < 5u; ++i) ASSERT_TRUE(kinds[i]);

    ASSERT_TRUE(encode_alloc(&fixture.delta_message, &delta_wire, &delta_size));
    ASSERT_EQ(break_world_delta_wire_decode(delta_wire, delta_size, &decoded),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(break_world_delta_wire_rebuild(&decoded, fixture.base_world, fixture.base,
                                             fixture.schemas, RICH_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_NOT_NULL(rebuilt);
    ASSERT_EQ(break_world_snapshot_id(rebuilt), break_world_snapshot_id(fixture.target));
    ASSERT_EQ(break_world_snapshot_tick(rebuilt), UINT64_C(0x8000000000000001));
    ASSERT_EQ(break_world_snapshot_entity_count(rebuilt), 4u);
    ASSERT_TRUE(canonical_reencoding(delta_wire, delta_size, 8u));
    ASSERT_EQ(((Value *)world_get_component(fixture.base_world, (Entity){1u, 1u}, COMP_VALUE))->value,
              10u);
    break_world_snapshot_release(rebuilt);
    break_world_delta_wire_clear(&decoded);

    ASSERT_TRUE(encode_alloc(&fixture.full_message, &full_wire, &full_size));
    rebuilt = NULL;
    ASSERT_EQ(break_world_delta_wire_decode(full_wire, full_size, &decoded),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(break_world_delta_wire_rebuild(&decoded, NULL, NULL, fixture.schemas,
                                             RICH_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_NOT_NULL(rebuilt);
    ASSERT_EQ(break_world_snapshot_id(rebuilt), break_world_snapshot_id(fixture.target));
    ASSERT_TRUE(canonical_reencoding(full_wire, full_size, 8u));
    break_world_snapshot_release(rebuilt);
    break_world_delta_wire_clear(&decoded);
    free(full_wire);
    free(delta_wire);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_wide_u64_fields_survive_repeated_round_trips) {
    static const u8 expected_base_id[] = {
        0x01u, 0x00u, 0x00u, 0x00u, 0x01u, 0x00u, 0x00u, 0x80u
    };
    static const u8 expected_target_id[] = {
        0xefu, 0xcdu, 0xabu, 0x89u, 0x67u, 0x45u, 0x23u, 0xf1u
    };
    static const u8 expected_base_tick[] = {
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u
    };
    static const u8 expected_target_tick[] = {
        0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u
    };
    BreakWorldDeltaWire message = golden_message();
    BreakWorldDeltaWire decoded;
    u8 *wire = NULL;
    usize size = 0u;
    message.kind = BREAK_WORLD_DELTA_WIRE_DELTA;
    message.base_snapshot_id = UINT64_C(0x8000000100000001);
    message.target_snapshot_id = UINT64_C(0xf123456789abcdef);
    message.base_tick = UINT64_C(0x8000000000000000);
    message.target_tick = UINT64_C(0x8000000000000001);
    ASSERT_TRUE(encode_alloc(&message, &wire, &size));
    ASSERT_EQ(size, sizeof(golden_wire));
    ASSERT_TRUE(memcmp(wire + WIRE_BASE_ID_OFFSET, expected_base_id, 8u) == 0);
    ASSERT_TRUE(memcmp(wire + WIRE_TARGET_ID_OFFSET, expected_target_id, 8u) == 0);
    ASSERT_TRUE(memcmp(wire + WIRE_BASE_TICK_OFFSET, expected_base_tick, 8u) == 0);
    ASSERT_TRUE(memcmp(wire + WIRE_TARGET_TICK_OFFSET, expected_target_tick, 8u) == 0);
    ASSERT_EQ(break_world_delta_wire_decode(wire, size, &decoded), BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(decoded.schema_hash, UINT64_C(0x1122334455667788));
    ASSERT_EQ(decoded.level_generation, UINT64_C(0x99aabbccddeeff00));
    ASSERT_EQ(decoded.base_snapshot_id, UINT64_C(0x8000000100000001));
    ASSERT_EQ(decoded.target_snapshot_id, UINT64_C(0xf123456789abcdef));
    ASSERT_EQ(decoded.base_tick, UINT64_C(0x8000000000000000));
    ASSERT_EQ(decoded.target_tick, UINT64_C(0x8000000000000001));
    break_world_delta_wire_clear(&decoded);
    ASSERT_TRUE(canonical_reencoding(wire, size, 16u));
    free(wire);
}

TEST(world_delta_wire_empty_record_full_message_rebuilds_empty_snapshot) {
    Fixture fixture;
    World *empty_world;
    BreakWorldSnapshot *empty;
    BreakWorldDeltaWire message;
    BreakWorldDeltaWire decoded;
    BreakWorldSnapshot *rebuilt = NULL;
    u8 *wire = NULL;
    usize size = 0u;
    ASSERT_TRUE(fixture_init(&fixture));
    empty_world = world_create();
    ASSERT_NOT_NULL(empty_world);
    empty = break_world_snapshot_build(empty_world, fixture.schemas, UINT64_C(0x100000000));
    ASSERT_NOT_NULL(empty);
    ASSERT_TRUE(message_from_snapshot(empty, TEST_LEVEL, &message));
    ASSERT_EQ(message.record_count, 0u);
    ASSERT_TRUE(message.records == NULL);
    ASSERT_TRUE(encode_alloc(&message, &wire, &size));
    ASSERT_EQ(size, BREAK_WORLD_DELTA_WIRE_HEADER_SIZE);
    ASSERT_EQ(break_world_delta_wire_decode(wire, size, &decoded), BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(decoded.record_count, 0u);
    ASSERT_TRUE(decoded.records == NULL);
    ASSERT_EQ(break_world_delta_wire_rebuild(&decoded, NULL, NULL, fixture.schemas,
                                             TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_NOT_NULL(rebuilt);
    ASSERT_EQ(break_world_snapshot_entity_count(rebuilt), 0u);
    ASSERT_EQ(break_world_snapshot_id(rebuilt), break_world_snapshot_id(empty));
    ASSERT_TRUE(canonical_reencoding(wire, size, 8u));
    break_world_snapshot_release(rebuilt);
    break_world_delta_wire_clear(&decoded);
    free(wire);
    break_world_snapshot_release(empty);
    world_destroy(empty_world);
    fixture_destroy(&fixture);
}

TEST(world_delta_wire_maximum_size_record_round_trips_exactly) {
    const usize payload_size = (usize)BREAK_WORLD_DELTA_WIRE_MAX_BYTES -
                               BREAK_WORLD_DELTA_WIRE_HEADER_SIZE -
                               BREAK_WORLD_DELTA_WIRE_RECORD_HEADER_SIZE;
    BreakWorldDeltaWire message = golden_message();
    u8 *payload = (u8 *)malloc(payload_size + 1u);
    u8 *wire = (u8 *)malloc((usize)BREAK_WORLD_DELTA_WIRE_MAX_BYTES + 1u);
    usize size = 99u;
    ASSERT_NOT_NULL(payload);
    ASSERT_NOT_NULL(wire);
    for (usize i = 0u; i < payload_size; ++i) payload[i] = (u8)(i ^ (i >> 8u));
    payload[payload_size] = 0x5au;
    message.record_count = 1u;
    message.records = &message.records[1];
    message.records[0].bytes = payload;
    message.records[0].size = payload_size + 1u;
    ASSERT_EQ(break_world_delta_wire_encoded_size(&message, &size),
              BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
    ASSERT_EQ(size, 0u);
    memset(wire, 0xa5, 32u);
    size = 99u;
    ASSERT_EQ(break_world_delta_wire_encode(&message, wire,
                                            (usize)BREAK_WORLD_DELTA_WIRE_MAX_BYTES + 1u, &size),
              BREAK_WORLD_DELTA_WIRE_OVER_LIMIT);
    ASSERT_EQ(size, 0u);
    ASSERT_TRUE(bytes_are(wire, 32u, 0xa5u));

    message.records[0].size = payload_size;
    ASSERT_EQ(break_world_delta_wire_encoded_size(&message, &size), BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(size, BREAK_WORLD_DELTA_WIRE_MAX_BYTES);
    ASSERT_EQ(break_world_delta_wire_encode(&message, wire,
                                            BREAK_WORLD_DELTA_WIRE_MAX_BYTES, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(size, BREAK_WORLD_DELTA_WIRE_MAX_BYTES);
    ASSERT_EQ(wire[WIRE_COUNT_OFFSET], 1u);
    free(payload);
    ASSERT_TRUE(canonical_reencoding(wire, size, 3u));
    free(wire);
}


TEST(world_delta_wire_full_rebuilds_shuffled_create_order) {
    Fixture fixture;
    World *world;
    Entity first, second, third;
    BreakWorldSnapshot *snapshot;
    BreakWorldDeltaWire message;
    BreakWorldDeltaWire decoded;
    BreakWorldSnapshot *rebuilt = NULL;
    BreakWorldDeltaRecord swap;
    u32 first_create = UINT32_MAX;
    u32 second_create = UINT32_MAX;
    u8 *wire = NULL;
    usize size = 0u;
    ASSERT_TRUE(fixture_init(&fixture));
    world = world_create();
    ASSERT_NOT_NULL(world);
    world_register_component(world, COMP_VALUE, sizeof(Value));
    first = world_create_entity(world);
    second = world_create_entity(world);
    third = world_create_entity(world);
    ASSERT_EQ(first.index, 1u);
    ASSERT_EQ(second.index, 2u);
    ASSERT_EQ(third.index, 3u);
    world_destroy_entity(world, second);
    ASSERT_TRUE(add_value(world, first, 5u));
    ASSERT_TRUE(add_value(world, third, 7u));
    snapshot = break_world_snapshot_build(world, fixture.schemas, 20u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(message_from_snapshot(snapshot, TEST_LEVEL, &message));
    for (u32 i = 0u; i < message.record_count; ++i) {
        if (message.records[i].kind != BREAK_DELTA_ENTITY_CREATE) continue;
        if (first_create == UINT32_MAX) {
            first_create = i;
        } else {
            second_create = i;
            break;
        }
    }
    ASSERT_TRUE(first_create != UINT32_MAX && second_create != UINT32_MAX);
    ASSERT_EQ(message.records[first_create].entity.index, 1u);
    ASSERT_EQ(message.records[second_create].entity.index, 3u);
    swap = message.records[first_create];
    message.records[first_create] = message.records[second_create];
    message.records[second_create] = swap;
    ASSERT_EQ(break_world_delta_wire_encoded_size(&message, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    wire = (u8 *)malloc(size);
    ASSERT_NOT_NULL(wire);
    ASSERT_EQ(break_world_delta_wire_encode(&message, wire, size, &size),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(break_world_delta_wire_decode(wire, size, &decoded),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_EQ(break_world_delta_wire_rebuild(&decoded, NULL, NULL, fixture.schemas,
                                             TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_OK);
    ASSERT_NOT_NULL(rebuilt);
    ASSERT_EQ(break_world_snapshot_id(rebuilt), break_world_snapshot_id(snapshot));
    break_world_snapshot_release(rebuilt);
    break_world_delta_wire_clear(&decoded);
    free(wire);
    break_world_snapshot_release(snapshot);
    free(message.records);
    world_destroy(world);
    fixture_destroy(&fixture);
}


TEST(world_delta_wire_full_rejects_over_capacity_creates_before_sorting) {
    Fixture fixture;
    BreakWorldDeltaWire message = golden_message();
    BreakWorldSnapshot *rebuilt = NULL;
    const u32 count = (u32)ECS_MAX_ENTITIES;
    ASSERT_TRUE(fixture_init(&fixture));
    message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
    ASSERT_NOT_NULL(message.records);
    message.record_count = count;
    message.level_generation = TEST_LEVEL;
    message.schema_hash = break_world_snapshot_schema_hash(fixture.target);
    for (u32 i = 0u; i < count; ++i) {
        message.records[i].kind = BREAK_DELTA_ENTITY_CREATE;
        message.records[i].entity.index = count - i;
        message.records[i].entity.generation = 1u;
    }
    ASSERT_EQ(break_world_delta_wire_rebuild(&message, NULL, NULL, fixture.schemas,
                                             TEST_LEVEL, &rebuilt),
              BREAK_WORLD_DELTA_WIRE_APPLY_FAILED);
    ASSERT_TRUE(rebuilt == NULL);
    free(message.records);
    fixture_destroy(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(world_delta_wire_golden_full_layout_and_round_trip);
    RUN_TEST(world_delta_wire_unaligned_decode_borrows_input);
    RUN_TEST(world_delta_wire_full_rebuilds_snapshot_from_empty_base);
    RUN_TEST(world_delta_wire_delta_round_trip_rebuilds_all_record_kinds);
    RUN_TEST(world_delta_wire_decode_rejects_magic_version_and_kind);
    RUN_TEST(world_delta_wire_decode_rejects_every_truncation_and_trailing_bytes);
    RUN_TEST(world_delta_wire_decode_enforces_count_and_byte_limits);
    RUN_TEST(world_delta_wire_decode_rejects_invalid_record_shapes);
    RUN_TEST(world_delta_wire_full_requires_zero_base_and_ordered_ticks);
    RUN_TEST(world_delta_wire_encode_validation_clears_size_and_preserves_output);
    RUN_TEST(world_delta_wire_rebuild_rejects_target_hash_and_payload_tampering);
    RUN_TEST(world_delta_wire_rebuild_rejects_base_schema_level_and_tick_mismatches);
    RUN_TEST(world_delta_wire_rebuild_rejects_invalid_application_without_mutation);
    RUN_TEST(world_delta_wire_clear_and_null_rebuild_arguments_are_safe);
    RUN_TEST(world_delta_wire_full_rebuilds_sparse_entity_indices);
    RUN_TEST(world_delta_wire_rejects_negative_record_kind);
    RUN_TEST(world_delta_wire_rejects_remove_record_with_payload);
    RUN_TEST(world_delta_wire_full_rebuilds_shuffled_create_order);
    RUN_TEST(world_delta_wire_full_rejects_over_capacity_creates_before_sorting);
    RUN_TEST(world_delta_wire_multi_entity_component_full_delta_are_canonical);
    RUN_TEST(world_delta_wire_wide_u64_fields_survive_repeated_round_trips);
    RUN_TEST(world_delta_wire_empty_record_full_message_rebuilds_empty_snapshot);
    RUN_TEST(world_delta_wire_maximum_size_record_round_trips_exactly);
TEST_MAIN_END()
