#ifndef BREAK_REPLICATION_WIRE_H
#define BREAK_REPLICATION_WIRE_H

#include "network/break_replication_fragment.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_REPLICATION_WIRE_VERSION 1u
#define BREAK_REPLICATION_WIRE_HEADER_SIZE 40u
#define BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT 1048576u
#define BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE \
    (BREAK_NET_MAX_PAYLOAD_SIZE - BREAK_REPLICATION_WIRE_HEADER_SIZE)

BreakReplicationFragmentResult break_replication_wire_encoded_size(
    const BreakReplicationFragment *fragment, size_t *out_size);
BreakReplicationFragmentResult break_replication_wire_encode(
    const BreakReplicationFragment *fragment,
    uint8_t *out, size_t capacity, size_t *out_size);
/* Successful decode borrows data + BREAK_REPLICATION_WIRE_HEADER_SIZE and
 * preserves the encoded checksum without recomputing FNV-1a. */
BreakReplicationFragmentResult break_replication_wire_decode(
    const void *data, size_t size, BreakReplicationFragment *out_fragment);

#ifdef __cplusplus
}
#endif

#endif
