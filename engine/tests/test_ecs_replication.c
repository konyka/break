#include "test_framework.h"
#include <ecs/ecs.h>
#include <ecs/replication_schema.h>
#include <ecs/world_snapshot.h>
#include <ecs/world_delta.h>
#include <network/break_aoi.h>

#include <float.h>
#include <stdint.h>
#include <string.h>

#define COMP_POSITION 11u
#define COMP_HEALTH   12u
#define COMP_POINTER  13u

typedef struct {
    float x;
    float y;
    float z;
} Position;

typedef struct {
    int hp;
} Health;

typedef struct {
    void *resource;
} PointerComponent;

static BreakComponentSchemaRegistry *make_schemas(void) {
    return break_schema_registry_create();
}

static void register_position(BreakComponentSchemaRegistry *schemas) {
    BreakComponentSchema schema = {
        .component_id = COMP_POSITION,
        .version = 1u,
        .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    ASSERT_EQ(break_schema_register(schemas, &schema), BREAK_SCHEMA_OK);
}

static World *make_world_with_position(float x) {
    World *world = world_create();
    if (!world) return NULL;
    world_register_component(world, COMP_POSITION, sizeof(Position));
    Entity entity = world_create_entity(world);
    Position *position = (Position *)world_add_component(world, entity, COMP_POSITION);
    if (!position) {
        world_destroy(world);
        return NULL;
    }
    position->x = x;
    position->y = 2.0f;
    position->z = 3.0f;
    return world;
}

TEST(schema_registration_accepts_valid_schema_and_supports_lookup) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    BreakComponentSchema schema = {
        .component_id = COMP_POSITION,
        .version = 7u,
        .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };

    ASSERT_EQ(break_schema_register(schemas, &schema), BREAK_SCHEMA_OK);
    const BreakComponentSchema *found = break_schema_lookup(schemas, COMP_POSITION);
    ASSERT_NOT_NULL(found);
    ASSERT_EQ(found->component_id, COMP_POSITION);
    ASSERT_EQ(found->version, 7u);
    ASSERT_EQ(found->size, sizeof(Position));
    ASSERT_EQ(found->alignment, _Alignof(Position));
    ASSERT_EQ(found->flags, schema.flags);

    break_schema_registry_destroy(schemas);
}

TEST(schema_registration_rejects_duplicate_component_id) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    BreakComponentSchema schema = {
        .component_id = COMP_POSITION,
        .version = 1u,
        .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };

    ASSERT_EQ(break_schema_register(schemas, &schema), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_register(schemas, &schema), BREAK_SCHEMA_DUPLICATE);

    break_schema_registry_destroy(schemas);
}

TEST(schema_registration_rejects_out_of_range_component_id) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    BreakComponentSchema schema = {
        .component_id = ECS_MAX_COMPONENTS,
        .version = 1u,
        .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    ASSERT_EQ(break_schema_register(schemas, &schema), BREAK_SCHEMA_INVALID_ARGUMENT);
    ASSERT_TRUE(break_schema_lookup(schemas, ECS_MAX_COMPONENTS) == NULL);
    break_schema_registry_destroy(schemas);
}

TEST(schema_registration_rejects_zero_size_and_invalid_alignment) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    BreakComponentSchema zero_size = {
        .component_id = COMP_POSITION,
        .version = 1u,
        .size = 0u,
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    BreakComponentSchema bad_alignment = zero_size;
    bad_alignment.component_id = COMP_HEALTH;
    bad_alignment.size = sizeof(Health);
    bad_alignment.alignment = 3u;

    ASSERT_EQ(break_schema_register(schemas, &zero_size), BREAK_SCHEMA_INVALID_SIZE);
    ASSERT_EQ(break_schema_register(schemas, &bad_alignment), BREAK_SCHEMA_INVALID_ALIGNMENT);
    ASSERT_TRUE(break_schema_lookup(schemas, COMP_POSITION) == NULL);
    ASSERT_TRUE(break_schema_lookup(schemas, COMP_HEALTH) == NULL);

    break_schema_registry_destroy(schemas);
}

TEST(schema_registration_rejects_pointer_component_as_raw_bytes) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    BreakComponentSchema schema = {
        .component_id = COMP_POINTER,
        .version = 1u,
        .size = sizeof(PointerComponent),
        .alignment = _Alignof(PointerComponent),
        .flags = BREAK_SCHEMA_FLAG_POINTER_CONTAINING | BREAK_SCHEMA_FLAG_RAW_BYTES
    };

    ASSERT_EQ(break_schema_register(schemas, &schema), BREAK_SCHEMA_UNSUPPORTED_POLICY);
    ASSERT_TRUE(break_schema_lookup(schemas, COMP_POINTER) == NULL);

    break_schema_registry_destroy(schemas);
}

TEST(schema_hash_is_stable_for_same_registration_order_and_changes_on_schema_change) {
    BreakComponentSchemaRegistry *first = make_schemas();
    BreakComponentSchemaRegistry *second = make_schemas();
    BreakComponentSchema position = {
        .component_id = COMP_POSITION,
        .version = 1u,
        .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    BreakComponentSchema health = {
        .component_id = COMP_HEALTH,
        .version = 2u,
        .size = sizeof(Health),
        .alignment = _Alignof(Health),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };

    ASSERT_EQ(break_schema_register(first, &position), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_register(first, &health), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_register(second, &position), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_register(second, &health), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_hash(first), break_schema_hash(second));

    health.version++;
    BreakComponentSchemaRegistry *changed = make_schemas();
    ASSERT_EQ(break_schema_register(changed, &position), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_register(changed, &health), BREAK_SCHEMA_OK);
    ASSERT_NEQ(break_schema_hash(first), break_schema_hash(changed));

    break_schema_registry_destroy(changed);
    break_schema_registry_destroy(second);
    break_schema_registry_destroy(first);
}

TEST(snapshot_contains_generation_aware_entity_identity) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *world = world_create();
    ASSERT_NOT_NULL(world);
    world_register_component(world, COMP_POSITION, sizeof(Position));
    Entity old_entity = world_create_entity(world);
    ASSERT_NOT_NULL(world_add_component(world, old_entity, COMP_POSITION));
    world_destroy_entity(world, old_entity);
    Entity current_entity = world_create_entity(world);
    ASSERT_NOT_NULL(world_add_component(world, current_entity, COMP_POSITION));
    ASSERT_EQ(current_entity.index, old_entity.index);
    ASSERT_NEQ(current_entity.generation, old_entity.generation);

    BreakWorldSnapshot *snapshot = break_world_snapshot_build(world, schemas, 4u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_EQ(break_world_snapshot_entity_count(snapshot), 1u);
    Entity stored = break_world_snapshot_entity_at(snapshot, 0u);
    ASSERT_EQ(stored.index, current_entity.index);
    ASSERT_EQ(stored.generation, current_entity.generation);
    ASSERT_TRUE(!break_world_snapshot_has_entity(snapshot, old_entity));
    ASSERT_TRUE(break_world_snapshot_has_entity(snapshot, current_entity));

    break_world_snapshot_release(snapshot);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_deep_copy_is_immune_to_world_mutation) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *world = make_world_with_position(10.0f);
    Entity entity = world_create_entity(world);
    Position *position = (Position *)world_add_component(world, entity, COMP_POSITION);
    ASSERT_NOT_NULL(position);
    position->x = 11.0f;

    BreakWorldSnapshot *snapshot = break_world_snapshot_build(world, schemas, 5u);
    ASSERT_NOT_NULL(snapshot);
    const void *bytes = NULL;
    usize size = 0u;
    ASSERT_TRUE(break_world_snapshot_component_bytes(snapshot, entity, COMP_POSITION,
                                                     &bytes, &size));
    ASSERT_EQ(size, sizeof(Position));
    Position copied = {0};
    memcpy(&copied, bytes, sizeof(copied));

    position->x = 99.0f;
    ASSERT_TRUE(break_world_snapshot_component_bytes(snapshot, entity, COMP_POSITION,
                                                     &bytes, &size));
    ASSERT_FLOAT_EQ(((const Position *)bytes)->x, copied.x, 1e-6f);

    break_world_snapshot_release(snapshot);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_entity_order_and_hash_are_deterministic) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *first_world = world_create();
    World *second_world = world_create();
    world_register_component(first_world, COMP_POSITION, sizeof(Position));
    world_register_component(second_world, COMP_POSITION, sizeof(Position));
    for (int i = 0; i < 3; i++) {
        Entity first_entity = world_create_entity(first_world);
        Entity second_entity = world_create_entity(second_world);
        Position *first_position = (Position *)world_add_component(first_world, first_entity,
                                                                     COMP_POSITION);
        Position *second_position = (Position *)world_add_component(second_world, second_entity,
                                                                      COMP_POSITION);
        first_position->x = second_position->x = (float)(20 - i);
    }

    BreakWorldSnapshot *first = break_world_snapshot_build(first_world, schemas, 9u);
    BreakWorldSnapshot *second = break_world_snapshot_build(second_world, schemas, 9u);
    ASSERT_NOT_NULL(first);
    ASSERT_NOT_NULL(second);
    ASSERT_EQ(break_world_snapshot_entity_count(first), 3u);
    ASSERT_EQ(break_world_snapshot_entity_at(first, 0u).index, 1u);
    ASSERT_EQ(break_world_snapshot_entity_at(first, 1u).index, 2u);
    ASSERT_EQ(break_world_snapshot_entity_at(first, 2u).index, 3u);
    ASSERT_EQ(break_world_snapshot_hash(first), break_world_snapshot_hash(second));

    break_world_snapshot_release(second);
    break_world_snapshot_release(first);
    world_destroy(second_world);
    world_destroy(first_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_retain_release_keeps_reader_alive_until_final_release) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *world = make_world_with_position(7.0f);
    BreakWorldSnapshot *snapshot = break_world_snapshot_build(world, schemas, 12u);
    ASSERT_NOT_NULL(snapshot);
    break_world_snapshot_retain(snapshot);
    break_world_snapshot_release(snapshot);

    ASSERT_EQ(break_world_snapshot_entity_count(snapshot), 1u);
    break_world_snapshot_release(snapshot);
    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_rejects_unregistered_or_unsupported_component_bytes) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    World *world = world_create();
    world_register_component(world, COMP_POINTER, sizeof(PointerComponent));
    Entity entity = world_create_entity(world);
    PointerComponent *component = (PointerComponent *)world_add_component(world, entity,
                                                                            COMP_POINTER);
    ASSERT_NOT_NULL(component);
    component->resource = (void *)(uintptr_t)0x1234u;

    BreakWorldSnapshot *snapshot = break_world_snapshot_build(world, schemas, 13u);
    ASSERT_TRUE(snapshot == NULL);

    world_destroy(world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_classifies_entity_and_component_changes) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 2u);
    BreakWorldDelta *delta;

    ASSERT_NOT_NULL(base);
    ASSERT_NOT_NULL(target);
    delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);
    ASSERT_EQ(break_world_delta_base_id(delta), break_world_snapshot_id(base));
    ASSERT_EQ(break_world_delta_target_id(delta), break_world_snapshot_id(target));
    ASSERT_TRUE(break_world_delta_update_count(delta) >= 1u);

    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(schema_hash_is_canonical_across_registration_order) {
    BreakComponentSchemaRegistry *first = make_schemas();
    BreakComponentSchemaRegistry *second = make_schemas();
    BreakComponentSchema position = {
        .component_id = COMP_POSITION,
        .version = 1u,
        .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    BreakComponentSchema health = {
        .component_id = COMP_HEALTH,
        .version = 2u,
        .size = sizeof(Health),
        .alignment = _Alignof(Health),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };

    ASSERT_EQ(break_schema_register(first, &health), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_register(first, &position), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_register(second, &position), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_register(second, &health), BREAK_SCHEMA_OK);
    ASSERT_EQ(break_schema_hash(first), break_schema_hash(second));

    break_schema_registry_destroy(second);
    break_schema_registry_destroy(first);
}

TEST(snapshot_delta_rejects_malformed_component_without_mutation) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    World *apply_world = make_world_with_position(1.0f);
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);
    apply_world->component_sizes[COMP_POSITION] = sizeof(Position) - 1u;

    ASSERT_EQ(break_world_delta_apply(apply_world, delta), BREAK_DELTA_BASE_MISMATCH);
    ASSERT_EQ(break_world_entity_count(apply_world), 1u);
    Position *position = (Position *)world_get_component(apply_world,
                                                           (Entity){1u, 1u}, COMP_POSITION);
    ASSERT_NOT_NULL(position);
    ASSERT_FLOAT_EQ(position->x, 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(position->y, 2.0f, 1e-6f);
    ASSERT_FLOAT_EQ(position->z, 3.0f, 1e-6f);

    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(apply_world);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_apply_is_idempotent_after_success) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);

    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_OK);
    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_ALREADY_APPLIED);

    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_apply_simulates_destroy_before_create_reuse) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    Entity target_old = (Entity){1u, 1u};
    world_destroy_entity(target_world, target_old);
    Entity target_new = world_create_entity(target_world);
    ASSERT_EQ(target_new.index, target_old.index);
    ASSERT_NEQ(target_new.generation, target_old.generation);
    Position *target_position = (Position *)world_add_component(target_world, target_new, COMP_POSITION);
    ASSERT_NOT_NULL(target_position);
    target_position->x = 3.0f;
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);

    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_OK);
    ASSERT_TRUE(world_entity_exists(base_world, target_new));
    ASSERT_TRUE(!world_entity_exists(base_world, target_old));

    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_rejects_tampered_payload_before_mutation) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);
    for (usize i = 0u; i < break_world_delta_record_count(delta); ++i) {
        BreakWorldDeltaRecord record = {0};
        ASSERT_TRUE(break_world_delta_record_at(delta, i, &record));
        if (record.kind == BREAK_DELTA_COMPONENT_UPDATE) {
            ((u8 *)record.bytes)[0] ^= 0x7fu;
            break;
        }
    }

    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_APPLY_FAILED);
    Position *position = (Position *)world_get_component(base_world, (Entity){1u, 1u}, COMP_POSITION);
    ASSERT_NOT_NULL(position);
    ASSERT_FLOAT_EQ(position->x, 1.0f, 1e-6f);

    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_rejects_non_increasing_tick_before_mutation) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 5u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 5u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);
    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_INVALID);
    ASSERT_FLOAT_EQ(((Position *)world_get_component(base_world, (Entity){1u, 1u}, COMP_POSITION))->x,
                    1.0f, 1e-6f);
    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_rejects_schema_mismatch_before_mutation) {
    BreakComponentSchemaRegistry *base_schemas = make_schemas();
    BreakComponentSchemaRegistry *target_schemas = make_schemas();
    register_position(base_schemas);
    BreakComponentSchema changed = {
        .component_id = COMP_POSITION, .version = 2u, .size = sizeof(Position),
        .alignment = _Alignof(Position),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    ASSERT_EQ(break_schema_register(target_schemas, &changed), BREAK_SCHEMA_OK);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, base_schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, target_schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);

    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_SCHEMA_MISMATCH);
    ASSERT_FLOAT_EQ(((Position *)world_get_component(base_world, (Entity){1u, 1u}, COMP_POSITION))->x,
                    1.0f, 1e-6f);

    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(target_schemas);
    break_schema_registry_destroy(base_schemas);
}

TEST(snapshot_delta_rolls_back_when_mutation_fault_is_injected) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);
    break_world_delta_test_fail_after_mutation(1u);

    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_APPLY_FAILED);
    ASSERT_FLOAT_EQ(((Position *)world_get_component(base_world, (Entity){1u, 1u}, COMP_POSITION))->x,
                    1.0f, 1e-6f);
    ASSERT_EQ(break_world_entity_count(base_world), 1u);
    break_world_delta_test_fail_after_mutation(0u);

    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_rolls_back_archetype_migration_after_fault) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    BreakComponentSchema health_schema = {
        .component_id = COMP_HEALTH, .version = 1u, .size = sizeof(Health),
        .alignment = _Alignof(Health),
        .flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES
    };
    ASSERT_EQ(break_schema_register(schemas, &health_schema), BREAK_SCHEMA_OK);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    world_register_component(base_world, COMP_HEALTH, sizeof(Health));
    world_register_component(target_world, COMP_HEALTH, sizeof(Health));
    Health *health = (Health *)world_add_component(target_world, (Entity){1u, 1u}, COMP_HEALTH);
    ASSERT_NOT_NULL(health);
    health->hp = 99;
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);
    break_world_delta_test_fail_after_mutation(1u);

    u32 original_archetype_count = base_world->archetype_count;
    u32 original_cache_version = base_world->cache_version;
    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_APPLY_FAILED);
    break_world_delta_test_fail_after_mutation(0u);
    ASSERT_EQ(base_world->archetype_count, original_archetype_count);
    ASSERT_EQ(base_world->cache_version, original_cache_version);
    ASSERT_TRUE(world_get_component(base_world, (Entity){1u, 1u}, COMP_HEALTH) == NULL);
    Health *after = (Health *)world_add_component(base_world, (Entity){1u, 1u}, COMP_HEALTH);
    ASSERT_NOT_NULL(after);
    after->hp = 7;
    world_remove_component(base_world, (Entity){1u, 1u}, COMP_HEALTH);
    ASSERT_TRUE(world_get_component(base_world, (Entity){1u, 1u}, COMP_HEALTH) == NULL);

    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_rolls_back_after_final_validation_failure) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *base_world = make_world_with_position(1.0f);
    World *target_world = make_world_with_position(2.0f);
    BreakWorldSnapshot *base = break_world_snapshot_build(base_world, schemas, 1u);
    BreakWorldSnapshot *target = break_world_snapshot_build(target_world, schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    ASSERT_NOT_NULL(delta);
    break_world_delta_test_fail_final_validation(true);
    ASSERT_EQ(break_world_delta_apply(base_world, delta), BREAK_DELTA_APPLY_FAILED);
    break_world_delta_test_fail_final_validation(false);
    ASSERT_FLOAT_EQ(((Position *)world_get_component(base_world, (Entity){1u, 1u}, COMP_POSITION))->x,
                    1.0f, 1e-6f);
    break_world_delta_release(delta);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    world_destroy(target_world);
    world_destroy(base_world);
    break_schema_registry_destroy(schemas);
}

TEST(snapshot_delta_rejects_wrong_base_before_world_mutation) {
    BreakComponentSchemaRegistry *schemas = make_schemas();
    register_position(schemas);
    World *first_world = make_world_with_position(1.0f);
    World *second_world = make_world_with_position(2.0f);
    World *apply_world = make_world_with_position(99.0f);
    BreakWorldSnapshot *first = break_world_snapshot_build(first_world, schemas, 1u);
    BreakWorldSnapshot *second = break_world_snapshot_build(second_world, schemas, 2u);
    BreakWorldDelta *delta = break_world_delta_diff(first, second);
    ASSERT_NOT_NULL(delta);
    ASSERT_EQ(break_world_delta_apply(apply_world, delta), BREAK_DELTA_BASE_MISMATCH);
    ASSERT_EQ(break_world_entity_count(apply_world), 1u);

    break_world_delta_release(delta);
    break_world_snapshot_release(second);
    break_world_snapshot_release(first);
    world_destroy(apply_world);
    world_destroy(second_world);
    world_destroy(first_world);
    break_schema_registry_destroy(schemas);
}

TEST(aoi_returns_deterministic_enter_stay_leave_sets) {
    BreakSpatialIndex *index = break_spatial_index_create(8.0f);
    BreakWitness witness = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                           {0.0f, 0.0f, 0.0f}, 10.0f, 0u, 1u};
    BreakReplicationObject object = {0x11u, 0x22u, {5.0f, 0.0f, 0.0f}, 0u, 0u};
    BreakAoIScope previous = {0};
    BreakAoIResult result = {0};

    ASSERT_NOT_NULL(index);
    ASSERT_TRUE(break_spatial_index_insert(index, &object));
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, &previous, &result));
    ASSERT_EQ(result.enter_count, 1u);
    ASSERT_EQ(result.enter[0], object.entity_id);
    break_aoi_result_clear(&result);
    ASSERT_TRUE(break_aoi_scope_assign(&previous, &object.entity_id, 1u));

    witness.position[0] = 100.0f;
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, &previous, &result));
    ASSERT_EQ(result.leave_count, 1u);
    ASSERT_EQ(result.leave[0], object.entity_id);
    break_aoi_result_clear(&result);
    break_aoi_scope_clear(&previous);
    break_spatial_index_destroy(index);
}

TEST(aoi_leave_sorts_by_priority_then_id) {
    BreakSpatialIndex *index = break_spatial_index_create(8.0f);
    BreakWitness witness = {{100.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                           {0.0f, 0.0f, 0.0f}, 1.0f, 0u, 1u};
    BreakReplicationObject low = {1u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 1u};
    BreakReplicationObject high_id = {3u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 5u};
    BreakReplicationObject high = {2u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 5u};
    BreakAoIEntityId previous_ids[] = {low.entity_id, high_id.entity_id, high.entity_id};
    BreakAoIScope previous = {0};
    BreakAoIResult result = {0};

    ASSERT_NOT_NULL(index);
    ASSERT_TRUE(break_spatial_index_insert(index, &low));
    ASSERT_TRUE(break_spatial_index_insert(index, &high_id));
    ASSERT_TRUE(break_spatial_index_insert(index, &high));
    ASSERT_TRUE(break_aoi_scope_assign(&previous, previous_ids, 3u));
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, &previous, &result));
    ASSERT_EQ(result.enter_count, 0u);
    ASSERT_EQ(result.stay_count, 0u);
    ASSERT_EQ(result.leave_count, 3u);
    ASSERT_EQ(result.leave[0], high.entity_id);
    ASSERT_EQ(result.leave[1], high_id.entity_id);
    ASSERT_EQ(result.leave[2], low.entity_id);

    break_aoi_result_clear(&result);
    break_aoi_scope_clear(&previous);
    break_spatial_index_destroy(index);
}

TEST(aoi_unions_multiple_witnesses_and_sorts_by_priority_then_id) {
    BreakSpatialIndex *index = break_spatial_index_create(8.0f);
    BreakWitness witnesses[2] = {
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 2.0f, 0u, 9u},
        {{20.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 2.0f, 0u, 9u}
    };
    BreakReplicationObject low = {3u, 0u, {20.0f, 0.0f, 0.0f}, 0u, 1u};
    BreakReplicationObject high = {9u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 5u};
    BreakAoIResult result = {0};

    ASSERT_TRUE(break_spatial_index_insert(index, &low));
    ASSERT_TRUE(break_spatial_index_insert(index, &high));
    ASSERT_TRUE(break_aoi_compute(index, witnesses, 2u, NULL, &result));
    ASSERT_EQ(result.enter_count, 2u);
    ASSERT_EQ(result.enter[0], 9u);
    ASSERT_EQ(result.enter[1], 3u);
    break_aoi_result_clear(&result);
    break_spatial_index_destroy(index);
}

TEST(aoi_always_relevant_does_not_bypass_owner_only_and_deduplicates_scope) {
    BreakSpatialIndex *index = break_spatial_index_create(8.0f);
    BreakWitness witness = {{100.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 1.0f, 0u, 1u};
    BreakReplicationObject owner_only = {7u, 2u, {0.0f, 0.0f, 0.0f}, BREAK_AOI_OBJECT_ALWAYS_RELEVANT | BREAK_AOI_OBJECT_OWNER_ONLY, 0u};
    BreakReplicationObject dormant = {8u, 1u, {100.0f, 0.0f, 0.0f}, BREAK_AOI_OBJECT_DORMANT, 0u};
    BreakAoIEntityId duplicate_ids[] = {7u, 7u, 8u};
    BreakAoIScope previous = {0};
    BreakAoIResult result = {0};

    ASSERT_TRUE(break_spatial_index_insert(index, &owner_only));
    ASSERT_TRUE(break_spatial_index_insert(index, &dormant));
    ASSERT_TRUE(break_aoi_scope_assign(&previous, duplicate_ids, 3u));
    ASSERT_EQ(previous.count, 2u);
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, &previous, &result));
    ASSERT_EQ(result.enter_count, 0u);
    ASSERT_EQ(result.stay_count, 0u);
    ASSERT_EQ(result.leave_count, 2u);
    ASSERT_EQ(result.leave[0], 7u);
    ASSERT_EQ(result.leave[1], 8u);
    break_aoi_result_clear(&result);
    break_aoi_scope_clear(&previous);
    break_spatial_index_destroy(index);
}

TEST(aoi_duplicate_witness_hits_emit_one_candidate_and_equal_priority_uses_id) {
    BreakSpatialIndex *index = break_spatial_index_create(4.0f);
    BreakWitness witnesses[2] = {
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 10.0f, 0u, 1u},
        {{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 10.0f, 0u, 1u}
    };
    BreakReplicationObject first = {2u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 4u};
    BreakReplicationObject second = {1u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 4u};
    BreakAoIResult result = {0};
    ASSERT_TRUE(break_spatial_index_insert(index, &first));
    ASSERT_TRUE(break_spatial_index_insert(index, &second));
    ASSERT_TRUE(break_aoi_compute(index, witnesses, 2u, NULL, &result));
    ASSERT_EQ(result.enter_count, 2u);
    ASSERT_EQ(result.enter[0], 1u);
    ASSERT_EQ(result.enter[1], 2u);
    break_aoi_result_clear(&result);
    break_spatial_index_destroy(index);
}

TEST(aoi_rejects_non_finite_and_negative_inputs) {
    BreakReplicationObject object = {1u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 0u};
    BreakWitness witness = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 1.0f, 0u, 1u};
    BreakAoIResult result = {0};
    BreakSpatialIndex *index = break_spatial_index_create(1.0f);
    ASSERT_TRUE(index != NULL);
    object.position[0] = NAN;
    ASSERT_FALSE(break_spatial_index_insert(index, &object));
    object.position[0] = 0.0f;
    witness.radius = -1.0f;
    ASSERT_FALSE(break_aoi_compute(index, &witness, 1u, NULL, &result));
    witness.radius = INFINITY;
    ASSERT_FALSE(break_aoi_compute(index, &witness, 1u, NULL, &result));
    witness.radius = 1.0f;
    witness.enter_hysteresis = -1.0f;
    ASSERT_FALSE(break_aoi_compute(index, &witness, 1u, NULL, &result));
    break_aoi_result_clear(&result);
    break_spatial_index_destroy(index);
}

TEST(aoi_update_moves_object_between_grid_cells) {
    BreakSpatialIndex *index = break_spatial_index_create(1.0f);
    BreakWitness witness = {{10.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 0.25f, 0u, 1u};
    BreakReplicationObject object = {55u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 0u};
    BreakAoIResult result = {0};
    ASSERT_TRUE(break_spatial_index_insert(index, &object));
    object.position[0] = 10.0f;
    ASSERT_TRUE(break_spatial_index_insert(index, &object));
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, NULL, &result));
    ASSERT_EQ(result.enter_count, 1u);
    ASSERT_EQ(result.enter[0], object.entity_id);
    break_aoi_result_clear(&result);
    break_spatial_index_destroy(index);
}

TEST(aoi_remove_non_last_entry_keeps_swapped_entry_queryable) {
    BreakSpatialIndex *index = break_spatial_index_create(1.0f);
    BreakWitness witness = {{20.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.5f, 0u, 1u};
    BreakReplicationObject removed = {60u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 0u};
    BreakReplicationObject kept = {61u, 0u, {20.0f, 0.0f, 0.0f}, 0u, 0u};
    BreakAoIResult result = {0};
    ASSERT_TRUE(break_spatial_index_insert(index, &removed));
    ASSERT_TRUE(break_spatial_index_insert(index, &kept));
    ASSERT_TRUE(break_spatial_index_remove(index, removed.entity_id));
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, NULL, &result));
    ASSERT_EQ(result.enter_count, 1u);
    ASSERT_EQ(result.enter[0], kept.entity_id);
    break_aoi_result_clear(&result);
    break_spatial_index_destroy(index);
}

TEST(aoi_rejects_invalid_shape_and_safe_extreme_sphere) {
    BreakSpatialIndex *index = break_spatial_index_create(1.0e30f);
    BreakReplicationObject object = {56u, 0u, {0.0f, 0.0f, 0.0f}, 0u, 0u};
    BreakWitness witness = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, FLT_MAX, 0u, 1u};
    BreakAoIResult result = {0};
    ASSERT_TRUE(break_spatial_index_insert(index, &object));
    witness.shape = (BreakAoIShape)99;
    ASSERT_FALSE(break_aoi_compute(index, &witness, 1u, NULL, &result));
    witness.shape = BREAK_AOI_SHAPE_SPHERE;
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, NULL, &result));
    ASSERT_EQ(result.enter_count, 1u);
    break_aoi_result_clear(&result);
    break_spatial_index_destroy(index);
}

TEST(aoi_hysteresis_leave_margin_keeps_previous_scope_across_candidate_cells) {
    BreakSpatialIndex *index = break_spatial_index_create(4.0f);
    BreakWitness witness = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0u, 1u};
    BreakReplicationObject object = {5u, 0u, {5.0f, 0.0f, 0.0f}, 0u, 0u};
    BreakAoIScope previous = {0};
    BreakAoIResult result = {0};

    witness.shape = BREAK_AOI_SHAPE_AABB;
    witness.half_extents[0] = 1.0f;
    witness.half_extents[1] = 1.0f;
    witness.half_extents[2] = 1.0f;
    witness.enter_hysteresis = 0.0f;
    witness.leave_hysteresis = 5.0f;
    ASSERT_TRUE(break_spatial_index_insert(index, &object));
    ASSERT_TRUE(break_aoi_scope_assign(&previous, &object.entity_id, 1u));
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, &previous, &result));
    ASSERT_EQ(result.enter_count, 0u);
    ASSERT_EQ(result.stay_count, 1u);
    ASSERT_EQ(result.stay[0], object.entity_id);
    ASSERT_EQ(result.leave_count, 0u);

    break_aoi_result_clear(&result);
    break_aoi_scope_clear(&previous);
    break_spatial_index_destroy(index);
}

TEST(aoi_zero_witness_always_relevant_requires_owner_for_owner_only) {
    BreakSpatialIndex *index = break_spatial_index_create(4.0f);
    BreakReplicationObject always = {6u, 99u, {100.0f, 0.0f, 0.0f}, BREAK_AOI_OBJECT_ALWAYS_RELEVANT, 0u};
    BreakReplicationObject owner_only = {7u, 99u, {100.0f, 0.0f, 0.0f}, BREAK_AOI_OBJECT_ALWAYS_RELEVANT | BREAK_AOI_OBJECT_OWNER_ONLY, 0u};
    BreakAoIResult result = {0};

    ASSERT_TRUE(break_spatial_index_insert(index, &always));
    ASSERT_TRUE(break_spatial_index_insert(index, &owner_only));
    ASSERT_TRUE(break_aoi_compute(index, NULL, 0u, NULL, &result));
    ASSERT_EQ(result.enter_count, 1u);
    ASSERT_EQ(result.enter[0], always.entity_id);
    ASSERT_EQ(result.stay_count, 0u);
    ASSERT_EQ(result.leave_count, 0u);

    break_aoi_result_clear(&result);
    break_spatial_index_destroy(index);
}

TEST(aoi_supports_shape_candidates_and_hysteresis) {
    BreakSpatialIndex *index = break_spatial_index_create(4.0f);
    BreakWitness witness = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 5.0f, 0u, 1u};
    BreakReplicationObject object = {4u, 0u, {5.5f, 0.0f, 0.0f}, 0u, 0u};
    BreakAoIScope previous = {0};
    BreakAoIResult result = {0};

    witness.shape = BREAK_AOI_SHAPE_AABB;
    witness.half_extents[0] = 6.0f;
    witness.half_extents[1] = 1.0f;
    witness.half_extents[2] = 1.0f;
    witness.enter_hysteresis = 0.0f;
    witness.leave_hysteresis = 2.0f;
    ASSERT_TRUE(break_spatial_index_insert(index, &object));
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, &previous, &result));
    ASSERT_EQ(result.enter_count, 1u);
    break_aoi_result_clear(&result);
    ASSERT_TRUE(break_aoi_scope_assign(&previous, &object.entity_id, 1u));
    witness.position[0] = 7.0f;
    ASSERT_TRUE(break_aoi_compute(index, &witness, 1u, &previous, &result));
    ASSERT_EQ(result.stay_count, 1u);
    break_aoi_result_clear(&result);
    break_aoi_scope_clear(&previous);
    break_spatial_index_destroy(index);
}

TEST_MAIN_BEGIN()
    RUN_TEST(snapshot_delta_classifies_entity_and_component_changes);
    RUN_TEST(schema_hash_is_canonical_across_registration_order);
    RUN_TEST(snapshot_delta_rejects_malformed_component_without_mutation);
    RUN_TEST(snapshot_delta_apply_is_idempotent_after_success);
    RUN_TEST(snapshot_delta_apply_simulates_destroy_before_create_reuse);
    RUN_TEST(snapshot_delta_rejects_tampered_payload_before_mutation);
    RUN_TEST(snapshot_delta_rejects_non_increasing_tick_before_mutation);
    RUN_TEST(snapshot_delta_rejects_schema_mismatch_before_mutation);
    RUN_TEST(snapshot_delta_rolls_back_when_mutation_fault_is_injected);
    RUN_TEST(snapshot_delta_rolls_back_archetype_migration_after_fault);
    RUN_TEST(snapshot_delta_rolls_back_after_final_validation_failure);
    RUN_TEST(snapshot_delta_rejects_wrong_base_before_world_mutation);
    RUN_TEST(aoi_returns_deterministic_enter_stay_leave_sets);
    RUN_TEST(aoi_leave_sorts_by_priority_then_id);
    RUN_TEST(aoi_unions_multiple_witnesses_and_sorts_by_priority_then_id);
    RUN_TEST(aoi_always_relevant_does_not_bypass_owner_only_and_deduplicates_scope);
    RUN_TEST(aoi_duplicate_witness_hits_emit_one_candidate_and_equal_priority_uses_id);
    RUN_TEST(aoi_rejects_non_finite_and_negative_inputs);
    RUN_TEST(aoi_update_moves_object_between_grid_cells);
    RUN_TEST(aoi_remove_non_last_entry_keeps_swapped_entry_queryable);
    RUN_TEST(aoi_rejects_invalid_shape_and_safe_extreme_sphere);
    RUN_TEST(aoi_supports_shape_candidates_and_hysteresis);
    RUN_TEST(aoi_hysteresis_leave_margin_keeps_previous_scope_across_candidate_cells);
    RUN_TEST(aoi_zero_witness_always_relevant_requires_owner_for_owner_only);
    RUN_TEST(schema_registration_rejects_out_of_range_component_id);
    RUN_TEST(schema_registration_accepts_valid_schema_and_supports_lookup);
    RUN_TEST(schema_registration_rejects_duplicate_component_id);
    RUN_TEST(schema_registration_rejects_zero_size_and_invalid_alignment);
    RUN_TEST(schema_registration_rejects_pointer_component_as_raw_bytes);
    RUN_TEST(schema_hash_is_stable_for_same_registration_order_and_changes_on_schema_change);
    RUN_TEST(snapshot_contains_generation_aware_entity_identity);
    RUN_TEST(snapshot_deep_copy_is_immune_to_world_mutation);
    RUN_TEST(snapshot_entity_order_and_hash_are_deterministic);
    RUN_TEST(snapshot_retain_release_keeps_reader_alive_until_final_release);
    RUN_TEST(snapshot_rejects_unregistered_or_unsupported_component_bytes);
TEST_MAIN_END()
