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

#ifdef __cplusplus
}
#endif

#endif
