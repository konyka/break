#ifndef BREAK_REPLICATION_SESSION_H
#define BREAK_REPLICATION_SESSION_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "network/break_net_adapter.h"
#include "network/break_replication_fragment.h"
#include "network/break_session.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Bridges BRFG fragments (default message 0x4009,
 * network/break_replication_wire.h)
 * between a BreakNetReactor/BreakSessionManager and one reassembly pool per
 * open connection. Every call is owner-thread only; the bridge adds no
 * thread, lock or atomic. The session handler only reassembles and queues:
 * completed packets reach the owner through poll_completed, never through a
 * callback. */
typedef struct BreakReplicationSessionBridge BreakReplicationSessionBridge;
typedef uint64_t (*BreakReplicationSessionClockFn)(void *user);

typedef struct BreakReplicationSessionBridgeConfig {
    BreakNetReactor *reactor; /* borrowed, may be NULL for receive-only use */
    size_t max_connections;
    size_t stream_capacity;                  /* 1..64 per connection */
    size_t max_pending_bytes_per_connection; /* 1..16 MiB */
    size_t max_total_pending_bytes;          /* >= connection product */
    size_t max_fragment_bytes;               /* 1..65496 */
    size_t max_fragment_count;               /* 1..1048576 */
    size_t completion_capacity;              /* > 0 */
    size_t max_completion_packet_bytes;      /* 1..16 MiB */
    size_t max_completion_queue_bytes;       /* >= packet cap */
    bool expiry_enabled;
    uint64_t expiry_interval;
    uint64_t expiry_max_idle;
    BreakReplicationSessionClockFn clock; /* required, owner thread only */
    void *clock_user;
    uint16_t message_id; /* 0 selects BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT */
} BreakReplicationSessionBridgeConfig;

typedef struct BreakReplicationSessionCompletion {
    BreakConnectionKey connection;
    uint64_t delta_id;
    uint8_t *payload;
    size_t payload_size;
} BreakReplicationSessionCompletion;

typedef struct BreakReplicationSessionBridgeStats {
    size_t connections;
    size_t pending_bytes;
    size_t completion_count;
    size_t completion_bytes;
    uint64_t rejected_fragments;
    uint64_t duplicate_fragments;
    uint64_t completed_packets;
    uint64_t dropped_completions;
    uint64_t expired_streams;
} BreakReplicationSessionBridgeStats;

/* NULL on an out-of-range field, a missing clock, an overflowing size product
 * or max_connections * max_pending_bytes_per_connection above
 * max_total_pending_bytes, so the pending total is bounded statically. That
 * budget covers pool payload bytes only; stream metadata, the completion
 * scratch and handed-off payloads are outside it, and queued completions are
 * bounded separately by completion_capacity and max_completion_queue_bytes.
 * reactor, clock and clock_user are borrowed and must outlive the bridge. */
BreakReplicationSessionBridge *break_replication_session_bridge_create(
    const BreakReplicationSessionBridgeConfig *config);
/* Frees every pool and every unpolled completion. NULL is a no-op. */
void break_replication_session_bridge_destroy(BreakReplicationSessionBridge *bridge);
/* Creates a fresh pool for a non-zero, not yet open key, applying the expiry
 * schedule when enabled. False on NULL, key 0, a duplicate key or a full
 * connection table. */
bool break_replication_session_connection_open(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection,
    uint64_t expected_base_id);
/* Destroys the connection's pool and frees its unpolled completions, counting
 * each as dropped; other connections keep their queue order. A later open of
 * the same key starts with a fresh high-water. False for an unknown key. */
bool break_replication_session_connection_close(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection);
/* Encodes one fragment in the bridge's 64 KiB scratch and queues it with
 * break_net_reactor_send using the configured message id. CLOSED for a NULL bridge or an
 * unopened key; INVALID for a NULL fragment or reactor, a base other than the
 * connection's expected base, a size or count above the bridge limits, or a
 * codec rejection. Reactor results (OVERLOAD, CLOSED) are returned unchanged
 * and nothing is retried; retry belongs to the caller. */
BreakNetSendResult break_replication_session_send_fragment(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection,
    const BreakReplicationFragment *fragment);
/* Runs pool_tick on every open connection and returns the streams evicted by
 * this call; idle streams expire without traffic. Uses the same time unit as
 * the clock. Zero when expiry is disabled. */
size_t break_replication_session_bridge_tick(BreakReplicationSessionBridge *bridge,
                                             uint64_t now);
/* BreakSessionMessageHandler for the configured message id with the bridge as
 * user_data. False
 * (the session records HANDLER_FAILED and keeps the connection open) for a
 * wrong id/version, an unopened key, malformed wire, a fragment above the
 * bridge limits or a pool rejection (base, checksum, conflict, high-water,
 * budget). True for incomplete, identical duplicate and complete fragments; a
 * completion that exceeds max_completion_packet_bytes or does not fit the
 * queue is freed and counted as dropped, never overwriting older entries.
 * message->data is never retained. */
bool break_replication_session_handle_message(
    BreakConnectionKey connection, const BreakNetOwnedMessage *message,
    void *user_data);
/* Moves up to out_capacity completions in FIFO order to out; ownership of
 * each payload moves with it. 0 for NULL bridge/out or zero capacity. */
size_t break_replication_session_poll_completed(
    BreakReplicationSessionBridge *bridge,
    BreakReplicationSessionCompletion *out, size_t out_capacity);
/* Moves up to out_capacity completions for one open or closed connection key,
 * skipping other keys without changing their FIFO order. Ownership of each
 * selected payload moves to out. */
size_t break_replication_session_poll_completed_for_connection(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection,
    BreakReplicationSessionCompletion *out, size_t out_capacity);
/* Frees the payload and zeroes the completion. NULL is a no-op. */
void break_replication_session_completion_release(
    BreakReplicationSessionCompletion *completion);
/* Snapshot of current sizes plus monotonic counters. out_stats is zeroed
 * first; NULL bridge or out_stats is otherwise a no-op. */
void break_replication_session_bridge_stats(
    const BreakReplicationSessionBridge *bridge,
    BreakReplicationSessionBridgeStats *out_stats);

#ifdef __cplusplus
}
#endif

#endif
