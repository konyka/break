/* break_online_voice_quic — voice over the QUIC datagram channel
 * (docs/design/quic_datagram.md). */

#include "network/break_online_voice_quic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------ send */

static bool voice_quic_send_frame(BreakNetQuicServer *server,
                                  BreakNetQuicConn *conn,
                                  BreakNetQuicClient *client,
                                  const BreakVoiceFrame *frame,
                                  bool use_adpcm) {
    u8 payload[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 size = 0u;
    BreakRuntimeError err = use_adpcm
                                ? break_voice_encode_adpcm(frame, payload,
                                                           sizeof(payload), &size)
                                : break_voice_encode(frame, payload,
                                                     sizeof(payload), &size);
    if (err != BREAK_RUNTIME_OK || size == 0u) {
        return false;
    }
    if (size > BREAK_NET_QUIC_MAX_DATAGRAM_PAYLOAD) {
        return false; /* oversize: fail closed before touching the network */
    }
    if (client != NULL) {
        return break_net_quic_client_datagram_send(client,
                                                   BREAK_VOICE_QUIC_MSG_TYPE,
                                                   payload, size);
    }
    if (conn != NULL && server != NULL) {
        return break_net_quic_datagram_send(server, conn,
                                            BREAK_VOICE_QUIC_MSG_TYPE, payload,
                                            size);
    }
    return false;
}

bool break_voice_quic_send(BreakNetQuicClient *client,
                           const BreakVoiceFrame *frame, bool use_adpcm) {
    if (client == NULL || frame == NULL) {
        return false;
    }
    return voice_quic_send_frame(NULL, NULL, client, frame, use_adpcm);
}

bool break_voice_quic_send_server(BreakNetQuicServer *server,
                                  BreakNetQuicConn *conn,
                                  const BreakVoiceFrame *frame, bool use_adpcm) {
    if (server == NULL || conn == NULL || frame == NULL) {
        return false;
    }
    return voice_quic_send_frame(server, conn, NULL, frame, use_adpcm);
}

/* --------------------------------------------------------------- receive */

/* Shared datagram handler: only voice-typed datagrams reach the receiver;
 * everything else is ignored (the channel is shared with other app types). */
static bool voice_quic_on_datagram(BreakNetQuicConn *conn, u8 type,
                                   u64 sequence, const u8 *payload,
                                   u32 payload_len, void *user) {
    BreakVoiceReceiver *receiver = (BreakVoiceReceiver *)user;
    (void)conn;
    (void)sequence; /* the voice frame carries its own sequence inside BRV */
    if (receiver == NULL || type != BREAK_VOICE_QUIC_MSG_TYPE) {
        return true; /* not voice: ignore, do not kill the connection */
    }
    return break_voice_receiver_push(receiver, payload, payload_len) ==
           BREAK_RUNTIME_OK;
}

void break_voice_quic_attach_receiver(BreakNetQuicClient *client,
                                      BreakVoiceReceiver *receiver) {
    if (client == NULL) {
        return;
    }
    break_net_quic_client_set_datagram_handler(client, voice_quic_on_datagram,
                                               receiver);
}

void break_voice_quic_attach_receiver_server(BreakNetQuicServer *server,
                                             BreakVoiceReceiver *receiver) {
    if (server == NULL) {
        return;
    }
    break_net_quic_server_set_datagram_handler(server, voice_quic_on_datagram,
                                               receiver);
}
