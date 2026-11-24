#pragma once

#include <ecs/world_delta.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_WORLD_DELTA_WIRE_VERSION 1u
#define BREAK_WORLD_DELTA_WIRE_HEADER_SIZE 60u
#define BREAK_WORLD_DELTA_WIRE_RECORD_HEADER_SIZE 17u
#define BREAK_WORLD_DELTA_WIRE_MAX_RECORD_COUNT 1048576u
#define BREAK_WORLD_DELTA_WIRE_MAX_BYTES (64u * 1024u * 1024u)

typedef enum {
    BREAK_WORLD_DELTA_WIRE_FULL = 1,
    BREAK_WORLD_DELTA_WIRE_DELTA = 2
} BreakWorldDeltaWireKind;

typedef enum {
    BREAK_WORLD_DELTA_WIRE_OK = 0,
    BREAK_WORLD_DELTA_WIRE_INVALID,
    BREAK_WORLD_DELTA_WIRE_OVER_LIMIT,
    BREAK_WORLD_DELTA_WIRE_BASE_MISMATCH,
    BREAK_WORLD_DELTA_WIRE_SCHEMA_MISMATCH,
    BREAK_WORLD_DELTA_WIRE_LEVEL_MISMATCH,
    BREAK_WORLD_DELTA_WIRE_TARGET_MISMATCH,
    BREAK_WORLD_DELTA_WIRE_APPLY_FAILED
} BreakWorldDeltaWireResult;

typedef struct {
    BreakWorldDeltaWireKind kind;
    u64 schema_hash;
    u64 level_generation;
    u64 base_snapshot_id;
    u64 target_snapshot_id;
    u64 base_tick;
    u64 target_tick;
    u32 record_count;
    BreakWorldDeltaRecord *records;
} BreakWorldDeltaWire;

BreakWorldDeltaWireResult break_world_delta_wire_encoded_size(
    const BreakWorldDeltaWire *message, usize *out_size);
BreakWorldDeltaWireResult break_world_delta_wire_encode(
    const BreakWorldDeltaWire *message, u8 *out, usize capacity, usize *out_size);
/* Decoded records own their record array but borrow each payload from data.
 * Call clear to release the record array; data must outlive the decoded message. */
BreakWorldDeltaWireResult break_world_delta_wire_decode(
    const void *data, usize size, BreakWorldDeltaWire *out_message);
void break_world_delta_wire_clear(BreakWorldDeltaWire *message);

/* Rebuilds into a private staging world and never mutates world. Delta rebuilds
 * require world and base to describe the wire base; full rebuilds ignore both. */
BreakWorldDeltaWireResult break_world_delta_wire_rebuild(
    const BreakWorldDeltaWire *message, World *world, const BreakWorldSnapshot *base,
    const BreakComponentSchemaRegistry *schemas, u64 level_generation,
    BreakWorldSnapshot **out_target);

#ifdef __cplusplus
}
#endif
