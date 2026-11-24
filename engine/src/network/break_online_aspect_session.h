#ifndef BREAK_ONLINE_ASPECT_SESSION_H
#define BREAK_ONLINE_ASPECT_SESSION_H

#include <network/break_online_aspect.h>
#include <network/break_replication_session.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Every function in this header is owner-thread only. Network callbacks only
 * queue completions in the owned bridge; break_aspect_session_drain is the sole
 * apply entry point and the only place the store may be mutated. */
typedef struct BreakAspectSession BreakAspectSession;

typedef struct BreakAspectSessionConfig {
    BreakAspectStore *store; /* borrowed, owner thread */
    BreakReplicationSessionBridgeConfig bridge;
} BreakAspectSessionConfig;

typedef struct BreakAspectSessionStats {
    size_t applied_packets;
    size_t rejected_packets;
    size_t drained_packets;
    BreakReplicationSessionBridgeStats bridge;
} BreakAspectSessionStats;

BreakAspectSession *break_aspect_session_create(const BreakAspectSessionConfig *config);
void break_aspect_session_destroy(BreakAspectSession *session);
/* Borrowed: owned by the session, valid until break_aspect_session_destroy.
 * Callers use it to register the bridge handler and to send fragments; they
 * must not destroy it separately. */
BreakReplicationSessionBridge *break_aspect_session_bridge(BreakAspectSession *session);
bool break_aspect_session_open(BreakAspectSession *session, BreakConnectionKey connection);
bool break_aspect_session_close(BreakAspectSession *session, BreakConnectionKey connection);
size_t break_aspect_session_tick(BreakAspectSession *session, uint64_t now);
/* Owner-thread only: applies and releases at most max_packets completions in FIFO
 * order. This is the only aspect-session API that calls break_aspect_apply. */
size_t break_aspect_session_drain(BreakAspectSession *session, size_t max_packets);
void break_aspect_session_stats(const BreakAspectSession *session,
                                BreakAspectSessionStats *out_stats);
BreakRuntimeError break_aspect_session_send(BreakAspectSession *session,
                                            BreakConnectionKey connection,
                                            const BreakReplicationFragment *fragment);

#ifdef __cplusplus
}
#endif

#endif
