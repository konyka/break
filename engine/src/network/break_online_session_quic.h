#pragma once
/* break_online_session_quic — bridge the QUIC authentication state into
 * break_online's lobby/NAT authentication source.
 *
 * The lobby's BreakOnlineAuthSource needs a per-session authenticity proof.
 * On the QUIC transport that proof is the completed CHALLENGE/AUTH-v2
 * handshake (break_net_quic's EVENT_AUTHENTICATED). This adapter maps the
 * lobby's `session` parameter onto the QUIC conn_id and answers from the
 * connection's verified state — no second credential system, no
 * process-global state (unlike the TCP BreakSessionManager seam).
 *
 * The result is that a lobby room create/join/list operation is only
 * accepted from a QUIC-authenticated peer. Voice already flows on the same
 * authenticated connection (break_online_voice_quic); this adapter completes
 * the control plane on the reliable stream. */

#include <network/break_net_quic.h>
#include <network/break_online_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Authentication source backed by a QUIC server. `session` in the lobby's
 * authenticate call is the QUIC conn_id (u64). The identity returned carries
 * session_id = player_id = conn_id. Only EVENT_AUTHENTICATED connections
 * pass; unknown or unauthenticated conn_ids are refused. */
BreakOnlineAuthSource break_online_session_quic_auth(BreakNetQuicServer *server);

/* Convenience: the client's own session handle once it is authenticated.
 * The client has no server-side conn_id; this returns 0 until the client
 * has completed AUTH v2, then 1 (the single-connection id). Used by clients
 * to prove to themselves that the control plane is authenticated. */
u64 break_online_session_quic_client_session(BreakNetQuicClient *client);

#ifdef __cplusplus
} /* extern "C" */
#endif
