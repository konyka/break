/* break_online_session_quic — bridge QUIC auth state into break_online's
 * authentication source. */

#include "network/break_online_session_quic.h"

/* The lobby calls this with the conn_id as `session`. Only a live,
 * AUTHENTICATED connection passes; unknown or unauthenticated ids refuse. */
static bool quic_authenticate(void *user, u64 session,
                              BreakOnlineIdentity *out_identity) {
    BreakNetQuicServer *server = (BreakNetQuicServer *)user;
    BreakNetQuicConn *conn;
    if (server == NULL || out_identity == NULL || session == 0u) {
        return false;
    }
    conn = break_net_quic_server_conn(server, (u32)session);
    if (conn == NULL || !break_net_quic_conn_is_authenticated(conn)) {
        return false;
    }
    out_identity->session_id = session;
    out_identity->player_id = session;
    return true;
}

BreakOnlineAuthSource break_online_session_quic_auth(BreakNetQuicServer *server) {
    BreakOnlineAuthSource source;
    source.user = server;
    source.authenticate = quic_authenticate;
    source.session_key = NULL;
    return source;
}

u64 break_online_session_quic_client_session(BreakNetQuicClient *client) {
    if (client == NULL || !break_net_quic_client_handshake_done(client) ||
        break_net_quic_client_failed(client)) {
        return 0u;
    }
    /* The client completed AUTH v2 by calling
     * break_net_quic_client_authenticate; there is no server-side
     * confirmation in v1, so the client-side session handle is simply
     * "handshake done and not failed". */
    return 1u;
}
