#include "network/break_online_aspect_session.h"

#include <stdlib.h>
#include <string.h>

struct BreakAspectSession {
    BreakReplicationSessionBridge *bridge;
    BreakAspectStore *store;
    size_t applied_packets;
    size_t rejected_packets;
    size_t drained_packets;
};

BreakAspectSession *break_aspect_session_create(const BreakAspectSessionConfig *config)
{
    BreakAspectSession *session;
    if (!config || !config->store) return NULL;
    session = (BreakAspectSession *)calloc(1u, sizeof(*session));
    if (!session) return NULL;
    session->bridge = break_replication_session_bridge_create(&config->bridge);
    if (!session->bridge) {
        free(session);
        return NULL;
    }
    session->store = config->store;
    return session;
}

void break_aspect_session_destroy(BreakAspectSession *session)
{
    if (!session) return;
    break_replication_session_bridge_destroy(session->bridge);
    free(session);
}

BreakReplicationSessionBridge *break_aspect_session_bridge(BreakAspectSession *session)
{
    return session ? session->bridge : NULL;
}

bool break_aspect_session_open(BreakAspectSession *session, BreakConnectionKey connection)
{
    uint64_t expected_base;
    if (!session) return false;
    expected_base = break_aspect_schema_hash(session->store);
    if (!expected_base) return false;
    return break_replication_session_connection_open(session->bridge, connection,
                                                      expected_base);
}

bool break_aspect_session_close(BreakAspectSession *session, BreakConnectionKey connection)
{
    if (!session) return false;
    return break_replication_session_connection_close(session->bridge, connection);
}

size_t break_aspect_session_tick(BreakAspectSession *session, uint64_t now)
{
    if (!session) return 0u;
    return break_replication_session_bridge_tick(session->bridge, now);
}

size_t break_aspect_session_drain(BreakAspectSession *session, size_t max_packets)
{
    size_t drained = 0u;
    if (!session || max_packets == 0u) return 0u;
    while (drained < max_packets) {
        BreakReplicationSessionCompletion completion;
        if (break_replication_session_poll_completed(session->bridge, &completion, 1u) != 1u)
            break;
        if (break_aspect_apply(session->store, completion.payload,
                               completion.payload_size) == BREAK_RUNTIME_OK) {
            session->applied_packets++;
        } else {
            session->rejected_packets++;
        }
        session->drained_packets++;
        drained++;
        break_replication_session_completion_release(&completion);
    }
    return drained;
}

void break_aspect_session_stats(const BreakAspectSession *session,
                                BreakAspectSessionStats *out_stats)
{
    if (!out_stats) return;
    memset(out_stats, 0, sizeof(*out_stats));
    if (!session) return;
    out_stats->applied_packets = session->applied_packets;
    out_stats->rejected_packets = session->rejected_packets;
    out_stats->drained_packets = session->drained_packets;
    break_replication_session_bridge_stats(session->bridge, &out_stats->bridge);
}

BreakRuntimeError break_aspect_session_send(BreakAspectSession *session,
                                            BreakConnectionKey connection,
                                            const BreakReplicationFragment *fragment)
{
    BreakNetSendResult result;
    if (!session) return BREAK_RUNTIME_CLOSED;
    result = break_replication_session_send_fragment(session->bridge, connection, fragment);
    switch (result) {
    case BREAK_NET_SEND_OK:
        return BREAK_RUNTIME_OK;
    case BREAK_NET_SEND_INVALID:
        return BREAK_RUNTIME_INVALID;
    case BREAK_NET_SEND_OVERLOAD:
        return BREAK_RUNTIME_OVERLOAD;
    case BREAK_NET_SEND_CLOSED:
        return BREAK_RUNTIME_CLOSED;
    default:
        return BREAK_RUNTIME_FAILED;
    }
}
