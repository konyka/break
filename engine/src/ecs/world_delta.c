#include <ecs/world_delta.h>
#include <ecs/ecs_internal.h>

#include <stdlib.h>
#include <string.h>

#ifdef BREAK_WORLD_DELTA_TESTING
bool break_world_delta_test_mutation_fault(void);
bool break_world_delta_test_final_validation_fault(void);
#endif

typedef struct {
    BreakWorldDeltaRecordKind kind;
    Entity entity;
    ComponentType component;
    usize byte_offset;
    usize size;
} BreakWorldDeltaRecordInternal;

struct BreakWorldDelta {
    u32 references;
    const BreakWorldSnapshot *base;
    const BreakWorldSnapshot *target;
    u64 base_id;
    u64 target_id;
    u64 base_schema_hash;
    u64 target_schema_hash;
    u64 base_tick;
    u64 target_tick;
    BreakWorldDeltaRecordInternal *records;
    usize record_count;
    usize record_capacity;
    u8 *bytes;
    usize byte_count;
    usize byte_capacity;
};

static bool add_record(BreakWorldDelta *delta, BreakWorldDeltaRecordKind kind,
                       Entity entity, ComponentType component, const void *bytes,
                       usize size) {
    if (delta->record_count == delta->record_capacity) {
        if (delta->record_capacity > (usize)-1 / 2u && delta->record_capacity != 0u) return false;
        usize capacity = delta->record_capacity ? delta->record_capacity * 2u : 16u;
        if (capacity > (usize)-1 / sizeof(*delta->records)) return false;
        BreakWorldDeltaRecordInternal *records = realloc(delta->records,
                                                           capacity * sizeof(*records));
        if (!records) return false;
        delta->records = records;
        delta->record_capacity = capacity;
    }
    usize byte_offset = 0u;
    if (size != 0u) {
        if (delta->byte_count > (usize)-1 - size) return false;
        if (delta->byte_count + size > delta->byte_capacity) {
            if (delta->byte_capacity > (usize)-1 / 2u && delta->byte_capacity != 0u) return false;
            usize capacity = delta->byte_capacity ? delta->byte_capacity * 2u : 256u;
            while (capacity < delta->byte_count + size) {
                if (capacity > (usize)-1 / 2u) return false;
                capacity *= 2u;
            }
            u8 *owned = realloc(delta->bytes, capacity);
            if (!owned) return false;
            delta->bytes = owned;
            delta->byte_capacity = capacity;
        }
        byte_offset = delta->byte_count;
        memcpy(delta->bytes + byte_offset, bytes, size);
        delta->byte_count += size;
    }
    delta->records[delta->record_count++] = (BreakWorldDeltaRecordInternal){
        kind, entity, component, byte_offset, size};
    return true;
}

static bool has_component(const BreakWorldSnapshot *snapshot, Entity entity,
                          ComponentType component, const void **bytes, usize *size) {
    return break_world_snapshot_component_bytes(snapshot, entity, component, bytes, size);
}

BreakWorldDelta *break_world_delta_diff(const BreakWorldSnapshot *base,
                                        const BreakWorldSnapshot *target) {
    if (!base || !target) return NULL;
    BreakWorldDelta *delta = calloc(1u, sizeof(*delta));
    if (!delta) return NULL;
    delta->references = 1u;
    delta->base = base;
    delta->target = target;
    delta->base_id = break_world_snapshot_id(base);
    delta->target_id = break_world_snapshot_id(target);
    delta->base_schema_hash = break_world_snapshot_schema_hash(base);
    delta->target_schema_hash = break_world_snapshot_schema_hash(target);
    delta->base_tick = break_world_snapshot_tick(base);
    delta->target_tick = break_world_snapshot_tick(target);
    break_world_snapshot_retain((BreakWorldSnapshot *)base);
    break_world_snapshot_retain((BreakWorldSnapshot *)target);

    usize base_count = break_world_snapshot_entity_count(base);
    usize target_count = break_world_snapshot_entity_count(target);
    for (usize i = 0u; i < target_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(target, i);
        if (!break_world_snapshot_has_entity(base, entity) &&
            !add_record(delta, BREAK_DELTA_ENTITY_CREATE, entity, 0u, NULL, 0u)) goto fail;
    }
    for (usize i = 0u; i < base_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(base, i);
        if (!break_world_snapshot_has_entity(target, entity) &&
            !add_record(delta, BREAK_DELTA_ENTITY_DESTROY, entity, 0u, NULL, 0u)) goto fail;
    }
    for (usize i = 0u; i < target_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(target, i);
        for (ComponentType component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *old_bytes = NULL, *new_bytes = NULL;
            usize old_size = 0u, new_size = 0u;
            bool old_has = has_component(base, entity, component, &old_bytes, &old_size);
            bool new_has = has_component(target, entity, component, &new_bytes, &new_size);
            if (!break_world_snapshot_has_entity(base, entity)) old_has = false;
            if (!old_has && new_has) {
                if (!add_record(delta, BREAK_DELTA_COMPONENT_ADD, entity, component,
                                new_bytes, new_size)) goto fail;
            } else if (old_has && !new_has) {
                if (!add_record(delta, BREAK_DELTA_COMPONENT_REMOVE, entity, component,
                                NULL, 0u)) goto fail;
            } else if (old_has && (old_size != new_size || memcmp(old_bytes, new_bytes, new_size) != 0)) {
                if (!add_record(delta, BREAK_DELTA_COMPONENT_UPDATE, entity, component,
                                new_bytes, new_size)) goto fail;
            }
        }
    }
    return delta;
fail:
    break_world_delta_release(delta);
    return NULL;
}

void break_world_delta_retain(BreakWorldDelta *delta) {
    if (delta) ++delta->references;
}

void break_world_delta_release(BreakWorldDelta *delta) {
    if (!delta || --delta->references != 0u) return;
    break_world_snapshot_release((BreakWorldSnapshot *)delta->target);
    break_world_snapshot_release((BreakWorldSnapshot *)delta->base);
    free(delta->records);
    free(delta->bytes);
    free(delta);
}

u64 break_world_delta_base_id(const BreakWorldDelta *delta) { return delta ? delta->base_id : 0u; }
u64 break_world_delta_target_id(const BreakWorldDelta *delta) { return delta ? delta->target_id : 0u; }
u64 break_world_delta_base_schema_hash(const BreakWorldDelta *delta) {
    return delta ? delta->base_schema_hash : 0u;
}
u64 break_world_delta_target_schema_hash(const BreakWorldDelta *delta) {
    return delta ? delta->target_schema_hash : 0u;
}
u64 break_world_delta_base_tick(const BreakWorldDelta *delta) {
    return delta ? delta->base_tick : 0u;
}
u64 break_world_delta_target_tick(const BreakWorldDelta *delta) {
    return delta ? delta->target_tick : 0u;
}
usize break_world_delta_update_count(const BreakWorldDelta *delta) {
    usize count = 0u;
    if (!delta) return 0u;
    for (usize i = 0u; i < delta->record_count; ++i) {
        if (delta->records[i].kind == BREAK_DELTA_COMPONENT_UPDATE) ++count;
    }
    return count;
}
usize break_world_delta_record_count(const BreakWorldDelta *delta) { return delta ? delta->record_count : 0u; }
bool break_world_delta_record_at(const BreakWorldDelta *delta, usize index,
                                 BreakWorldDeltaRecord *out_record) {
    if (!delta || !out_record || index >= delta->record_count) return false;
    const BreakWorldDeltaRecordInternal *record = &delta->records[index];
    *out_record = (BreakWorldDeltaRecord){
        record->kind,
        record->entity,
        record->component,
        record->size != 0u ? delta->bytes + record->byte_offset : NULL,
        record->size};
    return true;
}

usize break_world_entity_count(const World *world) {
    usize count = 0u;
    if (!world) return 0u;
    for (u32 i = 1u; i < world->entity_count; ++i) {
        if (world_entity_exists((World *)world, world->entities[i])) ++count;
    }
    return count;
}

static bool delta_record_preflight(const World *world, const BreakWorldDelta *delta,
                                   const BreakWorldDeltaRecordInternal *record) {
    if (!world || !delta || !record || record->kind > BREAK_DELTA_COMPONENT_UPDATE) return false;
    if (record->byte_offset > delta->byte_count ||
        record->size > delta->byte_count - record->byte_offset) return false;
    if (record->kind == BREAK_DELTA_ENTITY_CREATE || record->kind == BREAK_DELTA_ENTITY_DESTROY) {
        return record->component == 0u && record->size == 0u;
    }
    if (record->component >= ECS_MAX_COMPONENTS) return false;
    if (record->kind != BREAK_DELTA_COMPONENT_REMOVE && record->size == 0u) return false;
    if (record->kind != BREAK_DELTA_COMPONENT_REMOVE &&
        world->component_sizes[record->component] != record->size) return false;

    const void *target_bytes = NULL;
    const void *base_bytes = NULL;
    usize target_size = 0u;
    usize base_size = 0u;
    bool target_has = break_world_snapshot_component_bytes(
        delta->target, record->entity, record->component, &target_bytes, &target_size);
    bool base_has = break_world_snapshot_component_bytes(
        delta->base, record->entity, record->component, &base_bytes, &base_size);
    if (record->kind == BREAK_DELTA_COMPONENT_ADD ||
        record->kind == BREAK_DELTA_COMPONENT_UPDATE) {
        const u8 *payload = delta->bytes + record->byte_offset;
        if (!target_has || target_size != record->size ||
            memcmp(payload, target_bytes, record->size) != 0) return false;
    }
    if (record->kind == BREAK_DELTA_COMPONENT_ADD) {
        return !base_has && target_has && target_size == record->size;
    }
    if (record->kind == BREAK_DELTA_COMPONENT_REMOVE) {
        return base_has && !target_has;
    }
    return base_has && target_has && target_size == record->size;
}

#ifdef BREAK_WORLD_DELTA_TESTING
#define mutation_fault break_world_delta_test_mutation_fault
#endif

static bool world_matches_snapshot(const World *world, const BreakWorldSnapshot *snapshot) {
    if (!world || !snapshot ||
        break_world_entity_count(world) != break_world_snapshot_entity_count(snapshot)) return false;
    for (usize i = 0u; i < break_world_snapshot_entity_count(snapshot); ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        if (!world_entity_exists((World *)world, entity)) return false;
        for (ComponentType component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *expected = NULL, *actual = NULL;
            usize expected_size = 0u;
            bool expected_has = break_world_snapshot_component_bytes(snapshot, entity, component,
                                                                     &expected, &expected_size);
            actual = world_get_component((World *)world, entity, component);
            if (expected_has != (actual != NULL)) return false;
            if (expected_has && world->component_sizes[component] != expected_size) return false;
            if (expected_has && memcmp(expected, actual, expected_size) != 0) return false;
        }
    }
    return true;
}

static BreakDeltaApplyResult apply_records(World *world, const BreakWorldDelta *delta,
                                           u32 *predicted_generations,
                                           u32 *predicted_free_stack) {
    u32 predicted_free_top = world->free_stack_top;
    u32 predicted_entity_count = world->entity_count;
    if (predicted_free_top != 0u) {
        memcpy(predicted_free_stack, world->free_stack,
               predicted_free_top * sizeof(*predicted_free_stack));
    }
    for (u32 i = 0u; i < predicted_entity_count; ++i) {
        predicted_generations[i] = world->entities[i].generation;
    }
    for (usize i = 0u; i < delta->record_count; ++i) {
        const BreakWorldDeltaRecordInternal *record = &delta->records[i];
        if (record->kind != BREAK_DELTA_ENTITY_DESTROY) continue;
        if (predicted_free_top >= ECS_MAX_ENTITIES || record->entity.index >= predicted_entity_count ||
            predicted_generations[record->entity.index] != record->entity.generation) {
            return BREAK_DELTA_APPLY_FAILED;
        }
        predicted_generations[record->entity.index]++;
        predicted_free_stack[predicted_free_top++] = record->entity.index;
    }
    for (usize i = 0u; i < delta->record_count; ++i) {
        const BreakWorldDeltaRecordInternal *record = &delta->records[i];
        if (record->kind != BREAK_DELTA_ENTITY_CREATE) continue;
        Entity predicted;
        if (predicted_free_top != 0u) {
            u32 index = predicted_free_stack[predicted_free_top - 1u];
            predicted = world->entities[index];
            predicted.generation = predicted_generations[index] + 1u;
            if (predicted.generation == 0u) predicted.generation = 1u;
            --predicted_free_top;
            predicted_generations[index] = predicted.generation;
        } else {
            if (predicted_entity_count >= ECS_MAX_ENTITIES) return BREAK_DELTA_APPLY_FAILED;
            predicted = (Entity){predicted_entity_count++, 1u};
        }
        if (predicted.index != record->entity.index ||
            predicted.generation != record->entity.generation) return BREAK_DELTA_APPLY_FAILED;
    }
    for (usize i = 0u; i < delta->record_count; ++i) {
        const BreakWorldDeltaRecordInternal *record = &delta->records[i];
        if (record->kind == BREAK_DELTA_ENTITY_DESTROY) {
            world_destroy_entity(world, record->entity);
#ifdef BREAK_WORLD_DELTA_TESTING
            if (mutation_fault()) {
                return BREAK_DELTA_APPLY_FAILED;
            }
#endif
        }
    }
    for (usize i = 0u; i < delta->record_count; ++i) {
        const BreakWorldDeltaRecordInternal *record = &delta->records[i];
        if (record->kind == BREAK_DELTA_ENTITY_CREATE) {
            Entity created = world_create_entity(world);
            if (created.index != record->entity.index || created.generation != record->entity.generation) {
                return BREAK_DELTA_APPLY_FAILED;
            }
#ifdef BREAK_WORLD_DELTA_TESTING
            if (mutation_fault()) {
                return BREAK_DELTA_APPLY_FAILED;
            }
#endif
        }
    }
    for (usize i = 0u; i < delta->record_count; ++i) {
        const BreakWorldDeltaRecordInternal *record = &delta->records[i];
        const void *record_bytes = record->size != 0u ? delta->bytes + record->byte_offset : NULL;
        if (record->kind == BREAK_DELTA_COMPONENT_ADD) {
            void *out = world_add_component(world, record->entity, record->component);
            if (!out || record->size != world->component_sizes[record->component]) {
                return BREAK_DELTA_APPLY_FAILED;
            }
            memcpy(out, record_bytes, record->size);
#ifdef BREAK_WORLD_DELTA_TESTING
            if (mutation_fault()) {
                return BREAK_DELTA_APPLY_FAILED;
            }
#endif
        } else if (record->kind == BREAK_DELTA_COMPONENT_REMOVE) {
            world_remove_component(world, record->entity, record->component);
#ifdef BREAK_WORLD_DELTA_TESTING
            if (mutation_fault()) {
                return BREAK_DELTA_APPLY_FAILED;
            }
#endif
        } else if (record->kind == BREAK_DELTA_COMPONENT_UPDATE) {
            void *out = world_get_component(world, record->entity, record->component);
            if (!out || record->size != world->component_sizes[record->component]) {
                return BREAK_DELTA_APPLY_FAILED;
            }
            memcpy(out, record_bytes, record->size);
#ifdef BREAK_WORLD_DELTA_TESTING
            if (mutation_fault()) {
                return BREAK_DELTA_APPLY_FAILED;
            }
#endif
        }
    }
#ifdef BREAK_WORLD_DELTA_TESTING
    if (break_world_delta_test_final_validation_fault()) {
        return BREAK_DELTA_APPLY_FAILED;
    }
#endif
    if (!world_matches_snapshot(world, delta->target)) {
        return BREAK_DELTA_APPLY_FAILED;
    }
    return BREAK_DELTA_OK;
}

static BreakDeltaApplyResult apply_in_place(World *world, const BreakWorldDelta *delta) {
    if (!world || !delta || !delta->base || !delta->target) return BREAK_DELTA_INVALID;
    if (delta->base_schema_hash != delta->target_schema_hash) return BREAK_DELTA_SCHEMA_MISMATCH;
    if (delta->target_tick <= delta->base_tick) return BREAK_DELTA_INVALID;
    if (break_world_snapshot_id(delta->target) == delta->target_id &&
        world_matches_snapshot(world, delta->target)) return BREAK_DELTA_ALREADY_APPLIED;
    if (!world_matches_snapshot(world, delta->base)) return BREAK_DELTA_BASE_MISMATCH;

    usize destroy_count = 0u;
    for (usize i = 0u; i < delta->record_count; ++i) {
        const BreakWorldDeltaRecordInternal *record = &delta->records[i];
        if (!delta_record_preflight(world, delta, record)) return BREAK_DELTA_APPLY_FAILED;
        if (record->kind == BREAK_DELTA_ENTITY_CREATE && record->entity.generation == 0u) {
            return BREAK_DELTA_APPLY_FAILED;
        }
        if (record->kind == BREAK_DELTA_ENTITY_DESTROY) {
            if (!world_entity_exists(world, record->entity)) return BREAK_DELTA_APPLY_FAILED;
            ++destroy_count;
        }
    }

    /* Prediction scratch is heap-allocated and sized by the actual world/delta
     * counts: generations are only ever indexed below world->entity_count, and
     * the free stack grows by exactly one entry per DESTROY record (the
     * ECS_MAX_ENTITIES check in apply_records still bounds the logical top).
     * Failure here precedes any mutation; the caller destroys staging. */
    usize generation_count = world->entity_count != 0u ? world->entity_count : 1u;
    usize free_stack_capacity = (usize)world->free_stack_top + destroy_count;
    if (free_stack_capacity > ECS_MAX_ENTITIES) free_stack_capacity = ECS_MAX_ENTITIES;
    if (free_stack_capacity == 0u) free_stack_capacity = 1u;
    u32 *predicted_generations =
        (u32 *)malloc(generation_count * sizeof(*predicted_generations));
    u32 *predicted_free_stack =
        (u32 *)malloc(free_stack_capacity * sizeof(*predicted_free_stack));
    if (!predicted_generations || !predicted_free_stack) {
        free(predicted_generations);
        free(predicted_free_stack);
        return BREAK_DELTA_APPLY_FAILED;
    }
    BreakDeltaApplyResult result =
        apply_records(world, delta, predicted_generations, predicted_free_stack);
    free(predicted_generations);
    free(predicted_free_stack);
    return result;
}

BreakDeltaApplyResult break_world_delta_apply(World *world, const BreakWorldDelta *delta) {
    if (!world || !delta) return BREAK_DELTA_INVALID;
    World *staging = world_clone_deep(world);
    if (!staging) return BREAK_DELTA_APPLY_FAILED;
    BreakDeltaApplyResult result = apply_in_place(staging, delta);
    if (result != BREAK_DELTA_OK) {
        world_destroy(staging);
        return result;
    }
    if (!world_replace_contents(world, staging)) {
        world_destroy(staging);
        return BREAK_DELTA_APPLY_FAILED;
    }
    return BREAK_DELTA_OK;
}
