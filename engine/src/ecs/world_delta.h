#pragma once

#include <ecs/ecs.h>
#include <ecs/world_snapshot.h>
#include <core/types.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakWorldDelta BreakWorldDelta;

typedef enum {
    BREAK_DELTA_OK = 0,
    BREAK_DELTA_INVALID,
    BREAK_DELTA_BASE_MISMATCH,
    BREAK_DELTA_SCHEMA_MISMATCH,
    BREAK_DELTA_APPLY_FAILED,
    BREAK_DELTA_ALREADY_APPLIED
} BreakDeltaApplyResult;

typedef enum {
    BREAK_DELTA_ENTITY_CREATE = 0,
    BREAK_DELTA_ENTITY_DESTROY,
    BREAK_DELTA_COMPONENT_ADD,
    BREAK_DELTA_COMPONENT_REMOVE,
    BREAK_DELTA_COMPONENT_UPDATE
} BreakWorldDeltaRecordKind;

typedef struct {
    BreakWorldDeltaRecordKind kind;
    Entity entity;
    ComponentType component;
    const void *bytes;
    usize size;
} BreakWorldDeltaRecord;

BreakWorldDelta *break_world_delta_diff(const BreakWorldSnapshot *base,
                                        const BreakWorldSnapshot *target);
void break_world_delta_retain(BreakWorldDelta *delta);
void break_world_delta_release(BreakWorldDelta *delta);

u64 break_world_delta_base_id(const BreakWorldDelta *delta);
u64 break_world_delta_target_id(const BreakWorldDelta *delta);
u64 break_world_delta_base_schema_hash(const BreakWorldDelta *delta);
u64 break_world_delta_target_schema_hash(const BreakWorldDelta *delta);
u64 break_world_delta_base_tick(const BreakWorldDelta *delta);
u64 break_world_delta_target_tick(const BreakWorldDelta *delta);
usize break_world_delta_update_count(const BreakWorldDelta *delta);
usize break_world_delta_record_count(const BreakWorldDelta *delta);
bool break_world_delta_record_at(const BreakWorldDelta *delta, usize index,
                                 BreakWorldDeltaRecord *out_record);

usize break_world_entity_count(const World *world);

BreakDeltaApplyResult break_world_delta_apply(World *world,
                                              const BreakWorldDelta *delta);

#ifdef BREAK_WORLD_DELTA_TESTING
void break_world_delta_test_fail_after_mutation(usize mutation_count);
void break_world_delta_test_fail_final_validation(bool enabled);
#endif

#ifdef __cplusplus
}
#endif
