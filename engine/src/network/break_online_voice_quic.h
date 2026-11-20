#pragma once
/* break_online_voice_quic — voice over the QUIC datagram channel
 * (docs/design/quic_datagram.md).
 *
 * Moves the existing BRV-encoded voice path off raw UDP sockets onto the
 * authenticated, encrypted, congestion-controlled QUIC datagram channel.
 * The wire payload is the unchanged BRV1/BRV2 frame (the voice sequence
 * number stays inside it); the QUIC datagram sequence is a separate
 * transport-level counter used only for replay-window dedup.
 *
 * Sending: break_voice_encode[_adpcm] -> break_net_quic_datagram_send.
 * Receiving: the QUIC datagram callback -> break_voice_receiver_push.
 *
 * The channel must be authenticated before any voice flows (the datagram
 * gate drops unauthenticated traffic). Both directions are fail-closed:
 * oversize frames, unauthenticated sends, and replayed datagrams are
 * refused without touching the network or the receiver. */

#include <network/break_net_quic.h>
#include <network/break_online_voice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The datagram's type field for voice frames. Application payloads with
 * other types are not voice and are never pushed to the receiver. */
#define BREAK_VOICE_QUIC_MSG_TYPE 1u

/* Encode `frame` (BRV1 or BRV2 per `use_adpcm`) and send it as one QUIC
 * datagram to the given peer. Returns false when the datagram was not sent
 * (oversize, congestion, not authenticated, or the peer disabled datagrams);
 * the frame is dropped in that case, matching the unreliable semantics. */
bool break_voice_quic_send(BreakNetQuicClient *client,
                           const BreakVoiceFrame *frame, bool use_adpcm);
bool break_voice_quic_send_server(BreakNetQuicServer *server,
                                  BreakNetQuicConn *conn,
                                  const BreakVoiceFrame *frame, bool use_adpcm);

/* Attach `receiver` to the endpoint's datagram channel: every datagram whose
 * type is BREAK_VOICE_QUIC_MSG_TYPE is pushed into the receiver's inbox.
 * Other types are ignored. The receiver is borrowed and must outlive the
 * endpoint. */
void break_voice_quic_attach_receiver(BreakNetQuicClient *client,
                                      BreakVoiceReceiver *receiver);
void break_voice_quic_attach_receiver_server(BreakNetQuicServer *server,
                                             BreakVoiceReceiver *receiver);

#ifdef __cplusplus
} /* extern "C" */
#endif
