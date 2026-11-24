#ifndef BREAK_REPLICATION_FRAGMENT_H
#define BREAK_REPLICATION_FRAGMENT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "network/break_net_message.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum BreakReplicationFragmentResult {
    BREAK_REPLICATION_FRAGMENT_OK = 0,
    BREAK_REPLICATION_FRAGMENT_INVALID,
    BREAK_REPLICATION_FRAGMENT_OVER_LIMIT,
    BREAK_REPLICATION_FRAGMENT_OUT_OF_MEMORY
} BreakReplicationFragmentResult;

typedef struct BreakReplicationFragment {
    uint64_t delta_id;
    uint64_t base_id;
    uint32_t fragment_index;
    uint32_t fragment_count;
    uint32_t checksum;
    const uint8_t *data;
    size_t size;
} BreakReplicationFragment;

BreakReplicationFragmentResult break_replication_fragment_payload(
    uint64_t delta_id, uint64_t base_id, const void *payload, size_t payload_size,
    size_t fragment_payload_size, BreakReplicationFragment **fragments, size_t *fragment_count);
BreakReplicationFragmentResult break_replication_fragment_payload_into(
    uint64_t delta_id, uint64_t base_id, const void *payload, size_t payload_size,
    size_t fragment_payload_size, BreakReplicationFragment *out_fragments,
    size_t fragment_capacity, size_t *out_fragment_count);
/* Delta payloads are non-empty and every fragment is at most the transport limit. */
void break_replication_fragments_free(BreakReplicationFragment *fragments, size_t fragment_count);

#ifndef BREAK_REPLICATION_MAX_REASSEMBLY_SIZE
#define BREAK_REPLICATION_MAX_REASSEMBLY_SIZE (16u * 1024u * 1024u)
#endif

typedef enum BreakReplicationReassemblyResult {
    BREAK_REPLICATION_REASSEMBLY_INCOMPLETE = 0,
    BREAK_REPLICATION_REASSEMBLY_COMPLETE,
    BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT,
    BREAK_REPLICATION_REASSEMBLY_INVALID,
    BREAK_REPLICATION_REASSEMBLY_BASE_MISMATCH,
    BREAK_REPLICATION_REASSEMBLY_CHECKSUM_MISMATCH,
    BREAK_REPLICATION_REASSEMBLY_DUPLICATE,
    BREAK_REPLICATION_REASSEMBLY_CONFLICT,
    BREAK_REPLICATION_REASSEMBLY_OUT_OF_MEMORY
} BreakReplicationReassemblyResult;

typedef struct BreakReplicationReassembler BreakReplicationReassembler;
BreakReplicationReassembler *break_replication_reassembler_create(uint64_t expected_base_id);
void break_replication_reassembler_destroy(BreakReplicationReassembler *reassembler);
BreakReplicationReassemblyResult break_replication_reassembler_push(
    BreakReplicationReassembler *reassembler, const BreakReplicationFragment *fragment,
    uint8_t **payload, size_t *payload_size);
/* push with the caller's monotonic time (any unit): an accepted fragment,
 * including an identical duplicate, refreshes the pending stream's activity.
 * Rejected fragments never do. Results match push. A stream started by plain
 * push stays untimed (expire leaves it alone) until push_at starts a new one;
 * plain push on a timed stream accepts fragments without refreshing it. */
BreakReplicationReassemblyResult break_replication_reassembler_push_at(
    BreakReplicationReassembler *reassembler, const BreakReplicationFragment *fragment,
    uint64_t now, uint8_t **payload, size_t *payload_size);
/* Drops a pending incomplete stream idle for at least max_idle (a time
 * before the last activity counts as no idle time) and returns true. The
 * high-water stays: older deltas remain CONFLICT, and a late fragment of the
 * dropped delta starts it over as after a completion. False for NULL, when
 * nothing is pending, or for an untimed stream. */
bool break_replication_reassembler_expire(BreakReplicationReassembler *reassembler,
                                          uint64_t now, uint64_t max_idle);
/* Payload bytes held by the pending stream, excluding the per-fragment
 * bookkeeping; 0 for NULL or none. */
size_t break_replication_reassembler_pending_bytes(
    const BreakReplicationReassembler *reassembler);
void break_replication_reassembly_free(void *payload);
void break_replication_reassembler_reset(BreakReplicationReassembler *reassembler);

#define BREAK_REPLICATION_REASSEMBLY_POOL_MAX_STREAMS 64u
typedef struct BreakReplicationReassemblyPool BreakReplicationReassemblyPool;
/* Owner-thread only. Active streams share max_pending_bytes; exhausting either
 * stream slots or that byte budget rejects new payload with OVER_LIMIT without
 * disturbing active streams. New deltas below the highest completed delta
 * return CONFLICT, while an equal delta may restart and active older streams
 * may still complete. */
BreakReplicationReassemblyPool *break_replication_reassembly_pool_create(
    uint64_t expected_base_id, size_t stream_capacity, size_t max_pending_bytes);
void break_replication_reassembly_pool_destroy(BreakReplicationReassemblyPool *pool);
BreakReplicationReassemblyResult break_replication_reassembly_pool_push_at(
    BreakReplicationReassemblyPool *pool, const BreakReplicationFragment *fragment,
    uint64_t now, uint64_t *completed_delta_id,
    uint8_t **payload, size_t *payload_size);
/* Expire every timed idle stream independently and advance the retired
 * high-water; active older streams remain usable. */
size_t break_replication_reassembly_pool_expire(
    BreakReplicationReassemblyPool *pool, uint64_t now, uint64_t max_idle);
/* Set or replace the owner-thread expiry policy and clear its schedule epoch.
 * The first tick checks immediately; later ticks run once when interval has
 * elapsed. Zero interval makes every tick due, and zero max_idle expires every
 * timed pending stream on a due tick. */
void break_replication_reassembly_pool_set_expiry_schedule(
    BreakReplicationReassemblyPool *pool, uint64_t interval, uint64_t max_idle);
/* Disable automatic expiry and clear its epoch without dropping any stream. */
void break_replication_reassembly_pool_disable_expiry_schedule(
    BreakReplicationReassemblyPool *pool);
/* Run one due expiry pass and return its eviction count. Clock rollback and a
 * not-yet-due or disabled schedule return zero without advancing the epoch. */
size_t break_replication_reassembly_pool_tick(
    BreakReplicationReassemblyPool *pool, uint64_t now);
size_t break_replication_reassembly_pool_pending_streams(
    const BreakReplicationReassemblyPool *pool);
size_t break_replication_reassembly_pool_pending_bytes(
    const BreakReplicationReassemblyPool *pool);
/* Restore fresh-pool stream state while preserving creation and expiry policy;
 * the expiry schedule epoch is cleared. */
void break_replication_reassembly_pool_reset(BreakReplicationReassemblyPool *pool);
/* Reset stream state and replace the expected base on the pool and every fixed
 * slot without reallocating. NULL is a no-op. */
void break_replication_reassembly_pool_rebaseline(
    BreakReplicationReassemblyPool *pool, uint64_t expected_base_id);

#ifdef __cplusplus
}
#endif

#endif
