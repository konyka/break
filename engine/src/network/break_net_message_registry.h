#ifndef BREAK_NET_MESSAGE_REGISTRY_H
#define BREAK_NET_MESSAGE_REGISTRY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_NET_PROTOCOL_VERSION 1u
#define BREAK_NET_MESSAGE_ID_AUTH 1u
#define BREAK_NET_MESSAGE_ID_PING 2u
#define BREAK_NET_MESSAGE_ID_CHALLENGE 3u
/* core_app read-only snapshot (engine/apps/core_app/core_app_network.h).
 * AUTHENTICATED phase only; the payload limit equals
 * CORE_APP_SNAPSHOT_MAX_BYTES (32-byte header + 64 entities x 24 bytes). */
#define BREAK_NET_MESSAGE_ID_CORE_SNAPSHOT 0x4001u
#define BREAK_NET_CORE_SNAPSHOT_MAX_PAYLOAD (32u + 64u * 24u)
/* physics_sync (engine/src/physics/physics_sync.h), AUTHENTICATED only.
 * A report is exactly PHYSICS_SYNC_REPORT_BYTES; a correction is either a
 * 16-byte header plus a full physics snapshot ("PSNP") or a delta against a
 * snapshot the peer already holds ("PSND"), bounded by the global payload
 * cap. */
#define BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT 0x4002u
#define BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_CORRECTION 0x4003u
#define BREAK_NET_PHYSICS_SYNC_REPORT_PAYLOAD 16u
/* core_app clock probe (engine/apps/core_app/core_app_network.h),
 * AUTHENTICATED only; every probe is exactly 32 bytes. */
#define BREAK_NET_MESSAGE_ID_CLOCK_PROBE 0x4004u
#define BREAK_NET_CLOCK_PROBE_PAYLOAD 32u
/* core_app session welcome (engine/apps/core_app/core_app_network.h): the
 * server tells an authenticated peer its session number; exactly 16 bytes. */
#define BREAK_NET_MESSAGE_ID_SESSION_WELCOME 0x4005u
#define BREAK_NET_SESSION_WELCOME_PAYLOAD 16u
/* core_app voice (engine/apps/core_app/core_app.h voice_frame hook), sent
 * server to peer, AUTHENTICATED only. One BRV1 or BRV2 frame
 * (network/break_online_voice.h); the limit is one full BRV1 frame. */
#define BREAK_NET_MESSAGE_ID_CORE_VOICE 0x4006u
#define BREAK_NET_CORE_VOICE_MAX_PAYLOAD (16u + 480u * 2u)
/* core_app voice relay (engine/apps/core_app/core_app_network.h), sent
 * server to peer, AUTHENTICATED only: a 16-byte header naming the source
 * session, then one voice frame as the source sent it. */
#define BREAK_NET_MESSAGE_ID_CORE_VOICE_RELAY 0x4007u
#define BREAK_NET_CORE_VOICE_RELAY_MAX_PAYLOAD (16u + BREAK_NET_CORE_VOICE_MAX_PAYLOAD)
/* core_app voice mute (engine/apps/core_app/core_app_network.h), sent peer
 * to server, AUTHENTICATED only: mute or unmute one source session in the
 * relay to this peer; exactly 16 bytes. */
#define BREAK_NET_MESSAGE_ID_CORE_VOICE_MUTE 0x4008u
#define BREAK_NET_CORE_VOICE_MUTE_PAYLOAD 16u
/* Replication fragment (network/break_replication_session.h), AUTHENTICATED
 * only: one BRFG v1 fragment (network/break_replication_wire.h), bounded by
 * the global payload cap. */
#define BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT 0x4009u
/* World snapshot/delta BRFG payloads (BRWD) and their reserved control stream.
 * Both are AUTHENTICATED only and bounded by the global payload cap. */
#define BREAK_NET_MESSAGE_ID_WORLD_DELTA 0x400au
#define BREAK_NET_MESSAGE_ID_WORLD_CONTROL 0x400bu
/* Client prediction (network/break_prediction_wire.h), AUTHENTICATED only:
 * a client input batch ("BRPI", peer to server) and a server snapshot
 * ("BRPS", server to peer). Each limit is the largest message the decoder
 * can accept (a 64 KiB batch; a 16 KiB state), so the envelope refuses
 * anything larger first. Batches overlap by design, so
 * duplicates are idempotent; the server-side inbox applies each input once. */
#define BREAK_NET_MESSAGE_ID_PREDICTION_INPUT 0x400cu
#define BREAK_NET_MESSAGE_ID_PREDICTION_SNAPSHOT 0x400du
#define BREAK_NET_PREDICTION_INPUT_MAX_PAYLOAD (64u * 1024u)
#define BREAK_NET_PREDICTION_SNAPSHOT_MAX_PAYLOAD (20u + 16u * 1024u)
#define BREAK_NET_MESSAGE_ID_MAX 65535u
#define BREAK_NET_REGISTRY_MAX_MESSAGES 64u
#define BREAK_NET_MAX_PAYLOAD_SIZE (64u * 1024u)

typedef enum BreakNetMessagePhase {
    BREAK_NET_MESSAGE_PHASE_ANY = 0,
    BREAK_NET_MESSAGE_PHASE_AUTHENTICATING,
    BREAK_NET_MESSAGE_PHASE_AUTHENTICATED
} BreakNetMessagePhase;

typedef enum BreakNetDuplicatePolicy {
    BREAK_NET_DUPLICATE_REJECT = 0,
    BREAK_NET_DUPLICATE_IDEMPOTENT = 1
} BreakNetDuplicatePolicy;

typedef struct BreakNetMessageDefinition {
    uint16_t message_id;
    uint16_t minimum_version;
    uint16_t maximum_version;
    size_t payload_limit;
    BreakNetMessagePhase phase;
    BreakNetDuplicatePolicy duplicate_policy;
} BreakNetMessageDefinition;

typedef struct BreakNetMessageRegistry {
    BreakNetMessageDefinition definitions[BREAK_NET_REGISTRY_MAX_MESSAGES];
    size_t count;
} BreakNetMessageRegistry;

void break_net_message_registry_init(BreakNetMessageRegistry *registry);
bool break_net_message_registry_register(BreakNetMessageRegistry *registry,
                                          const BreakNetMessageDefinition *definition);
const BreakNetMessageDefinition *break_net_message_registry_lookup(
    const BreakNetMessageRegistry *registry, uint16_t message_id);
bool break_net_message_definition_supports_version(
    const BreakNetMessageDefinition *definition, uint16_t version);

const BreakNetMessageRegistry *break_net_message_registry_default(void);

#ifdef __cplusplus
}
#endif

#endif
