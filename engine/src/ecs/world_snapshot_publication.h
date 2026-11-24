#pragma once

#include <ecs/world_snapshot.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakWorldSnapshotPublication BreakWorldSnapshotPublication;

typedef struct {
    u64 schema_hash;
    u64 level_generation;
} BreakWorldSnapshotPublicationConfig;

typedef struct {
    BreakWorldSnapshot *snapshot;
    u64 level_generation;
    u64 publication_epoch;
} BreakWorldSnapshotLease;

typedef enum {
    BREAK_WORLD_SNAPSHOT_ACQUIRE_OK = 0,
    BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY,
    BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED,
    BREAK_WORLD_SNAPSHOT_ACQUIRE_INVALID
} BreakWorldSnapshotAcquireResult;

BreakWorldSnapshotPublication *break_world_snapshot_publication_create(
    const BreakWorldSnapshotPublicationConfig *config);
void break_world_snapshot_publication_destroy(
    BreakWorldSnapshotPublication *publication);
bool break_world_snapshot_publication_publish(
    BreakWorldSnapshotPublication *publication,
    BreakWorldSnapshot *snapshot, u64 level_generation);
BreakWorldSnapshotAcquireResult break_world_snapshot_publication_acquire(
    BreakWorldSnapshotPublication *publication,
    BreakWorldSnapshotLease *out_lease);
void break_world_snapshot_publication_close(
    BreakWorldSnapshotPublication *publication);
void break_world_snapshot_lease_release(BreakWorldSnapshotLease *lease);

#ifdef __cplusplus
}
#endif
