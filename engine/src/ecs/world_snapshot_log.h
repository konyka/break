#pragma once

#include <ecs/world_snapshot.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Reliable per-epoch broadcast of immutable World snapshots.
 *
 * BreakWorldSnapshotPublication keeps only the latest snapshot, so a slow
 * reader skips the epochs published in between. This log keeps every
 * published snapshot until each registered reader has consumed it: a reader
 * sees epochs 1, 2, 3, ... in order with none skipped.
 *
 * The log is a ring of the last `capacity` snapshots; the oldest one is
 * dropped only when a publish needs its slot. When it is still unread by
 * some reader, publish either refuses the new snapshot (FULL, nothing
 * changes; the producer retries later) or, with evict_slow_readers, evicts
 * the readers still holding it back. An evicted reader no longer holds the
 * log back. Its next read returns LAGGED once; it then continues from the
 * oldest retained epoch and must treat the gap like a fresh baseline (for
 * World replication: a full snapshot instead of a delta).
 *
 * A reader added later starts at the next epoch published after it was
 * added. Epochs start at 1 and never repeat; each published snapshot gets
 * the next one, and its tick must be greater than the previous snapshot's.
 *
 * Thread safety: every call takes one internal mutex, so publish, read and
 * reader management may run on different threads. Leases own their own
 * snapshot reference and stay valid after the log is destroyed. Design:
 * docs/design/ecs_snapshot_replication_aoi.md "可靠的每 epoch 广播". */
typedef struct BreakWorldSnapshotLog BreakWorldSnapshotLog;
typedef u32 BreakWorldSnapshotReaderId;

#define BREAK_WORLD_SNAPSHOT_LOG_MAX_CAPACITY 1024u
#define BREAK_WORLD_SNAPSHOT_LOG_MAX_READERS 256u

typedef struct {
    u64 schema_hash;
    u32 capacity;      /* retained snapshots, 1..BREAK_WORLD_SNAPSHOT_LOG_MAX_CAPACITY */
    u32 max_readers;   /* 1..BREAK_WORLD_SNAPSHOT_LOG_MAX_READERS */
    bool evict_slow_readers;
} BreakWorldSnapshotLogConfig;

typedef enum {
    BREAK_WORLD_SNAPSHOT_LOG_OK = 0,
    BREAK_WORLD_SNAPSHOT_LOG_EMPTY,   /* read: the reader is up to date */
    BREAK_WORLD_SNAPSHOT_LOG_FULL,    /* publish: the oldest snapshot is still unread */
    BREAK_WORLD_SNAPSHOT_LOG_LAGGED,  /* read: the reader was evicted; read again */
    BREAK_WORLD_SNAPSHOT_LOG_INVALID  /* bad argument, schema, tick or reader */
} BreakWorldSnapshotLogResult;

typedef struct {
    BreakWorldSnapshot *snapshot; /* own reference; release with lease_release */
    u64 epoch;
} BreakWorldSnapshotLogLease;

typedef struct {
    u64 published;
    u64 refused_full;
    u64 evicted_readers;
    u64 delivered;
    u32 retained;
    u32 readers;
} BreakWorldSnapshotLogStats;

BreakWorldSnapshotLog *break_world_snapshot_log_create(const BreakWorldSnapshotLogConfig *config);
void break_world_snapshot_log_destroy(BreakWorldSnapshotLog *log);

/* Retains `snapshot` on OK and writes its epoch to *out_epoch (may be NULL).
 * INVALID on NULL, a schema mismatch, a tick of 0 or a tick not greater than
 * the previous snapshot's. */
BreakWorldSnapshotLogResult break_world_snapshot_log_publish(BreakWorldSnapshotLog *log,
                                                             BreakWorldSnapshot *snapshot,
                                                             u64 *out_epoch);

/* False when max_readers are registered or on NULL. */
bool break_world_snapshot_log_add_reader(BreakWorldSnapshotLog *log,
                                         BreakWorldSnapshotReaderId *out_reader);
/* Unread snapshots stop waiting for this reader. False for an unknown id. */
bool break_world_snapshot_log_remove_reader(BreakWorldSnapshotLog *log,
                                            BreakWorldSnapshotReaderId reader);

/* The reader's next epoch in order. OK fills *out_lease; on any other
 * result *out_lease is zeroed. */
BreakWorldSnapshotLogResult break_world_snapshot_log_read(BreakWorldSnapshotLog *log,
                                                          BreakWorldSnapshotReaderId reader,
                                                          BreakWorldSnapshotLogLease *out_lease);
/* Epochs published but not yet read by `reader`; 0 for an unknown id. */
u64 break_world_snapshot_log_backlog(BreakWorldSnapshotLog *log,
                                     BreakWorldSnapshotReaderId reader);

void break_world_snapshot_log_lease_release(BreakWorldSnapshotLogLease *lease);
void break_world_snapshot_log_stats(BreakWorldSnapshotLog *log, BreakWorldSnapshotLogStats *out);

#ifdef __cplusplus
}
#endif
