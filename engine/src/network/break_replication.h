#ifndef BREAK_REPLICATION_H
#define BREAK_REPLICATION_H

#include "network/break_aoi.h"
#include "network/break_net_adapter.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakReplication BreakReplication;

typedef enum BreakReplicationRecordKind {
    BREAK_REPLICATION_BASELINE = 1,
    BREAK_REPLICATION_DIRTY = 2,
    BREAK_REPLICATION_DESTROY = 3,
    BREAK_REPLICATION_DORMANT = 4
} BreakReplicationRecordKind;

BreakReplication *break_replication_create(BreakNetReactor *reactor,
                                             uint16_t baseline_message_id,
                                             uint16_t dirty_message_id,
                                             uint16_t destroy_message_id,
                                             uint16_t dormant_message_id);
void break_replication_destroy(BreakReplication *replication);
bool break_replication_register(BreakReplication *replication,
                                const BreakReplicationObject *object,
                                const void *payload, size_t payload_size);
bool break_replication_mark_dirty(BreakReplication *replication,
                                  BreakAoIEntityId entity_id,
                                  const void *payload, size_t payload_size);
bool break_replication_connection_open(BreakReplication *replication,
                                        uint64_t connection_key,
                                        size_t bandwidth_budget);
/* Call this after polling BREAK_NET_EVENT_CONNECTION_CLOSED or TRANSPORT_ERROR.
 * The adapter owns transport events; replication owns only its Ghost state. */
bool break_replication_disconnect(BreakReplication *replication,
                                  uint64_t connection_key);
size_t break_replication_connection_count(const BreakReplication *replication);
bool break_replication_sync(BreakReplication *replication,
                            uint64_t connection_key,
                            const BreakAoIResult *aoi);
bool break_replication_sync_budget(BreakReplication *replication,
                                   uint64_t connection_key,
                                   const BreakAoIResult *aoi,
                                   size_t bandwidth_budget);

/* Test-only boundary hook; production callers never set internal versions. */
bool break_replication_test_set_version(BreakReplication *replication,
                                        BreakAoIEntityId entity_id,
                                        uint64_t version);

#ifdef __cplusplus
}
#endif

#endif
