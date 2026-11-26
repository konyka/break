#pragma once

#include <ecs/world_session.h>
#include <ecs/world_snapshot_publication.h>
#include <runtime/runtime_bus.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND 0x5753u
#define BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_KIND 0x5754u
#define BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_VERSION 1u

typedef enum {
    BREAK_RUNTIME_WORLD_COMMAND_OPEN = 1,
    BREAK_RUNTIME_WORLD_COMMAND_CLOSE = 2,
    BREAK_RUNTIME_WORLD_COMMAND_REBASELINE = 3,
    BREAK_RUNTIME_WORLD_COMMAND_ACK = 4,
    BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL = 5
} BreakRuntimeWorldCommandKind;

typedef struct {
    u32 kind;
    u32 reserved_zero;
    u64 connection_key;
    u64 connection_epoch;
    u64 level_generation;
    u64 delta_id;
    u64 target_snapshot_id;
    u64 target_tick;
} BreakRuntimeWorldCommand;

BREAK_STATIC_ASSERT(sizeof(BreakRuntimeWorldCommand) == 56u,
                    "BreakRuntimeWorldCommand must be 56 bytes");

typedef struct {
    u64 level_generation;
    u64 reserved_zero;
} BreakRuntimeWorldPublishCurrentNotice;

BREAK_STATIC_ASSERT(sizeof(BreakRuntimeWorldPublishCurrentNotice) == 16u,
                    "BreakRuntimeWorldPublishCurrentNotice must be 16 bytes");

typedef struct BreakRuntimeWorldSession BreakRuntimeWorldSession;

typedef struct {
    BreakWorldSession *session;
    BreakRuntimeBus *bus;
    const char *subscriber_name;
    u32 queue_capacity;
    u32 max_connections;
    BreakWorldSnapshotPublication *publication; /* borrowed; NULL disables */
    u32 publish_connection_budget;              /* 0 = 8; allowed 1..64 */
    /* Both gates require a publication. requires_ready: a new connection is
     * not ready until set_publish_ready(); an unready connection is skipped by
     * fanout, continuation and dirty accounting, and keeps its attempt scalars.
     * waits_for_ack: a connection with no active attempt, a nonempty history
     * and no force_full is held for the current epoch instead of sent. */
    bool publish_requires_ready;
    bool publish_waits_for_ack;
} BreakRuntimeWorldSessionConfig;

typedef struct {
    u64 submitted;       /* successful direct submit calls only */
    u64 drained;         /* direct and external Bus messages actually consumed */
    u64 applied;
    u64 rejected;
    u64 stale_rejected;
    u64 transport_overloads;
    u64 next_sequence;
    usize queued;        /* queue enqueued-dequeued; excludes control_pending */
    bool control_pending;
    u64 publish_overloads;
    u64 publish_terminal;
    bool publish_pending;
} BreakRuntimeWorldSessionStats;

/* submit() and submit_publish_current() validate, copy and enqueue only into
 * this adapter's owned queue; they never fan out through the bus. Only the
 * control kind is registered for external producers: a direct Bus publish
 * delivers an independent copy to every adapter subscribed to that kind.
 * Publish-current notices have no external Bus kind. External control messages
 * increase drained/applied as consumed, never submitted or the adapter-local
 * Runtime sequence.
 *
 * submit(), submit_publish_current(), close(), is_closed(), pending(),
 * connection_epoch() and stats() may run on any thread. drain() is the
 * single-owner entry point and is the
 * only API that may call World Session. External Bus publishers use the bus' normal threading
 * contract and race only with queue admission, never with World calls.
 *
 * pending() is queue enqueued-dequeued plus control_pending and one Boolean
 * publish request/continuation, not submitted-drained. For an unregistered
 * adapter, destroy() first closes
 * admission and unsubscribes, then checks actual pending. A false attempt then
 * leaves drain/stats/epoch queries and a later retry valid, without repeating
 * unsubscribe. A directly registered adapter instead rejects destroy before
 * close/unsubscribe; only its lifecycle destroy callback may release it.
 * Abandon returns that ownership to the caller before a manual destroy.
 *
 * A fail-early destroy may overlap producers/drain only while pending is known
 * to keep it false. Before any destroy call that can succeed, the caller must
 * quiesce every other adapter API call and prevent new calls; success
 * invalidates the adapter. The borrowed bus/session/publication stay
 * caller-owned.
 */
BreakRuntimeWorldSession *break_runtime_world_session_create(
    const BreakRuntimeWorldSessionConfig *config);
bool break_runtime_world_session_destroy(
    BreakRuntimeWorldSession *adapter);
BreakRuntimeError break_runtime_world_session_submit(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldCommand *command,
    u64 correlation_id);
BreakRuntimeError break_runtime_world_session_submit_publish_current(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldPublishCurrentNotice *notice,
    u64 correlation_id);
/* Any thread. INVALID for a NULL adapter or zero key, REJECTED when the
 * adapter was created without publish_requires_ready, STALE when the key is
 * not open or the epoch does not match. Making a connection ready does not
 * publish by itself; submit a publish-current notice afterwards. */
BreakRuntimeError break_runtime_world_session_set_publish_ready(
    BreakRuntimeWorldSession *adapter, u64 connection_key, u64 connection_epoch,
    bool ready);
void break_runtime_world_session_close(
    BreakRuntimeWorldSession *adapter);
bool break_runtime_world_session_is_closed(
    const BreakRuntimeWorldSession *adapter);
BreakRuntimeError break_runtime_world_session_drain(
    BreakRuntimeWorldSession *adapter, usize max_messages,
    usize *out_drained);
usize break_runtime_world_session_pending(
    const BreakRuntimeWorldSession *adapter);
bool break_runtime_world_session_connection_epoch(
    const BreakRuntimeWorldSession *adapter, u64 connection_key,
    u64 *out_epoch);
void break_runtime_world_session_stats(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldSessionStats *out_stats);

/* Per-connection read-only view for diagnosis. The query copies adapter scalars
 * under the adapter mutex; it never calls World Session, publication or queue and
 * never advances the state machine. `publish_dirty` mirrors the adapter-owned terms of
 * the fanout continuation for one connection (false while unready; otherwise retry,
 * saved attempt scalars, then the observed-epoch comparison against completed, terminal
 * and held epochs); it deliberately omits the continuation's Session
 * `attempt_pending` probe, so it answers "this adapter still owes a publication", not
 * "the authoritative World differs" and not "pending() is zero". */
typedef struct {
    u64 connection_key;
    u64 connection_epoch;
    u64 completed_publication_epoch;
    u64 terminal_publication_epoch;
    u64 attempt_publication_epoch;
    u64 attempt_target_snapshot_id;
    u64 attempt_target_tick;
    bool retry_publish;
    bool publish_dirty;
    bool publish_ready;           /* always true without publish_requires_ready */
    u64 held_publication_epoch;   /* epoch last held by publish_waits_for_ack */
} BreakRuntimeWorldConnectionSnapshot;

/* Writes up to `capacity` open connections in ascending slot order and returns the
 * number of open connections, which may exceed `capacity`. A NULL `out_snapshots` or
 * a zero capacity only reports the count. */
usize break_runtime_world_session_connection_snapshots(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldConnectionSnapshot *out_snapshots,
    usize capacity);

/* Adapter-level publish progress for diagnosis: where the publish-current chain has
 * advanced to, how many connections still owe a publication, and whether a request or
 * a cross-drain continuation is outstanding. `dirty_connections` uses exactly the same
 * per-connection criterion as BreakRuntimeWorldConnectionSnapshot.publish_dirty, so the
 * two views cannot disagree. Read-only: copies scalars under the adapter mutex, never
 * calls World Session, publication or queue. */
typedef struct {
    u64 observed_publication_epoch; /* no known epoch in this window; also reset to 0 by
                                     * rebaseline and by an empty/closed publication */
    u32 open_connections;
    u32 dirty_connections;
    bool request_pending;      /* notice consumed, not yet fanned out */
    bool continuation_pending; /* latest drain's recomputed flag; includes Session attempt_pending */
} BreakRuntimeWorldPublishProgress;

/* Returns false with a zeroed output when the adapter (or output) is NULL. */
bool break_runtime_world_session_publish_progress(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldPublishProgress *out_progress);

#ifdef BREAK_RUNTIME_TESTING
void break_runtime_world_session_set_next_connection_epoch_for_test(
    BreakRuntimeWorldSession *adapter, u64 next_epoch);
#endif

#ifdef __cplusplus
}
#endif

#include <runtime/runtime_world_session_lifecycle.h>
