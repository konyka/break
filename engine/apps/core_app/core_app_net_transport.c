#include "core_app_net_transport.h"

#include <ecs/world_session.h>
#include <network/break_net_adapter.h>
#include <network/break_net_events.h>
#include <network/break_net_message_registry.h>
#include <network/break_msg_rate.h>
#include <network/break_online_aspect_replication.h>
#include <network/break_online_aspect_session.h>
#include <network/break_online_voice.h>
#include <network/break_session.h>
#include <physics/physics_sync.h>
#include <platform/platform_fs.h>
#include <core/clock_offset.h>
#include <core/trace_core_app.h>
#include <platform/time.h>
#include <runtime/runtime_bus.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BREAK_ENABLE_CRYPTO
#error "the core_app transport requires AUTH-v2 (BREAK_ENABLE_CRYPTO)"
#endif

#if CORE_APP_SNAPSHOT_MESSAGE_ID != BREAK_NET_MESSAGE_ID_CORE_SNAPSHOT
#error "core_app snapshot id must match the default message registry"
#endif
#if CORE_APP_CLOCK_PROBE_MESSAGE_ID != BREAK_NET_MESSAGE_ID_CLOCK_PROBE
#error "core_app clock probe id must match the default message registry"
#endif
#if CORE_APP_SESSION_WELCOME_MESSAGE_ID != BREAK_NET_MESSAGE_ID_SESSION_WELCOME
#error "core_app session welcome id must match the default message registry"
#endif
_Static_assert(CORE_APP_SESSION_WELCOME_BYTES == BREAK_NET_SESSION_WELCOME_PAYLOAD,
               "core_app session welcome size must match the registry payload limit");
_Static_assert(CORE_APP_CLOCK_PROBE_BYTES == BREAK_NET_CLOCK_PROBE_PAYLOAD,
               "core_app clock probe size must match the registry payload limit");
_Static_assert(CORE_APP_SNAPSHOT_MAX_BYTES == BREAK_NET_CORE_SNAPSHOT_MAX_PAYLOAD,
               "core_app snapshot size must match the registry payload limit");
_Static_assert(CORE_APP_PHYSICS_CORRECTION_MAX_BYTES == BREAK_NET_MAX_PAYLOAD_SIZE,
               "core_app correction cap must match the net payload cap");
_Static_assert(PHYSICS_SYNC_REPORT_BYTES == BREAK_NET_PHYSICS_SYNC_REPORT_PAYLOAD,
               "physics report size must match the registry payload limit");
_Static_assert(BREAK_NET_CORE_VOICE_MAX_PAYLOAD == BREAK_VOICE_MAX_DATAGRAM_SIZE,
               "core_app voice limit must be one full BRV1 frame");
#if CORE_APP_VOICE_RELAY_MESSAGE_ID != BREAK_NET_MESSAGE_ID_CORE_VOICE_RELAY
#error "core_app voice relay id must match the default message registry"
#endif
_Static_assert(CORE_APP_VOICE_RELAY_MAX_BYTES == BREAK_NET_CORE_VOICE_RELAY_MAX_PAYLOAD,
               "core_app voice relay size must match the registry payload limit");
_Static_assert(CORE_APP_VOICE_RELAY_MAX_FRAME_BYTES == BREAK_NET_CORE_VOICE_MAX_PAYLOAD,
               "a relayed frame must fit one core_app voice message");
#if CORE_APP_VOICE_MUTE_MESSAGE_ID != BREAK_NET_MESSAGE_ID_CORE_VOICE_MUTE
#error "core_app voice mute id must match the default message registry"
#endif
_Static_assert(CORE_APP_VOICE_MUTE_BYTES == BREAK_NET_CORE_VOICE_MUTE_PAYLOAD,
               "core_app voice mute size must match the registry payload limit");

#define CORE_APP_NET_MAX_CONNECTIONS 8u
#define CORE_APP_NET_EVENTS_PER_TICK 64u
#define CORE_APP_NET_DRAIN_STEP_MS 1
#define CORE_APP_NET_MAX_POLL_MS 100u
/* A connection that has not authenticated this long after it opened is
 * closed, so idle TLS peers cannot hold every slot. Measured on the
 * monotonic clock: the tick rate depends on --net-poll-ms and on whether
 * the output paces frames, so a tick count is no deadline a peer can meet. */
#define CORE_APP_NET_AUTH_DEADLINE_MS 3000u
/* Server-initiated clock probes: one outstanding request per peer, sent
 * every INTERVAL_TICKS ticks and dropped after TIMEOUT_TICKS ticks without
 * a reply. Both are counted in ticks, not wall time, because a headless
 * run may advance many ticks per millisecond. The offset is traced once
 * the estimator holds TRACE_SAMPLES samples. */
#define CORE_APP_NET_CLOCK_PROBE_INTERVAL_TICKS 8u
#define CORE_APP_NET_CLOCK_PROBE_TIMEOUT_TICKS 32u
#define CORE_APP_NET_CLOCK_OFFSET_TRACE_SAMPLES 4u
#define CORE_APP_NET_PATH_CAPACITY 512u
/* Peer voice: one jitter buffer per connection, created on its first voice
 * message. The buffer holds the receiver maximum, so a burst queued on the
 * ordered TLS stream does not overflow it. Pops are capped per call: a frame
 * with a far later sequence would otherwise make the receiver conceal every
 * missing frame before it in one loop. The per-tick cap keeps up with one
 * 10 ms frame stream only while ticks take at most 160 ms; a slower server
 * falls behind and the receiver then counts overloads. */
#define CORE_APP_NET_VOICE_DELAY_MS 40u
#define CORE_APP_NET_VOICE_JITTER_FRAMES 64u
#define CORE_APP_NET_VOICE_QUEUE 4u
#define CORE_APP_NET_VOICE_POPS_PER_TICK 16u
#define CORE_APP_NET_VOICE_FLUSH_POPS 128u
/* Accepted frames waiting for net_send_pending to relay them. Sends wait
 * until the event queue is empty, like every other send; a burst larger
 * than the ring is dropped and counted. */
#define CORE_APP_NET_VOICE_RELAY_QUEUE 32u
/* Source sessions one peer muted. Session ids are never reused, so an id
 * of a peer that left stays harmless until the slot is released. */
#define CORE_APP_NET_VOICE_MUTE_CAPACITY 16u
/* Voice a single connection may send: one 10 ms stream is 100 frames/s,
 * plus 20% for jitter; the burst equals the jitter buffer. The byte bucket
 * allows the same number of full BRV1 frames, so the frame bucket binds. */
#define CORE_APP_NET_VOICE_RATE_PER_SEC 120u
#define CORE_APP_NET_VOICE_RATE_BURST 64u
#define CORE_APP_ASPECT_OBJECT_COUNT 2u
#define CORE_APP_ASPECT_STORE_OBJECTS 3u
#define CORE_APP_ASPECT_PACKET_BYTES 2048u
#define CORE_APP_ASPECT_FRAGMENT_BYTES 512u
#define CORE_APP_ASPECT_MAX_FRAGMENTS 16u
#define CORE_APP_ASPECT_BANDWIDTH_BUDGET 16384u
#define CORE_APP_ASPECT_DRAIN_BUDGET 64u
#define CORE_APP_ASPECT_STREAM_CAPACITY 16u
#define CORE_APP_ASPECT_PENDING_BYTES 16384u
#define CORE_APP_ASPECT_COMPLETION_CAPACITY 64u
#define CORE_APP_ASPECT_EXPIRY_INTERVAL_MS 10u
#define CORE_APP_ASPECT_EXPIRY_IDLE_MS 50u
#define CORE_APP_WORLD_OBJECT_COUNT 2u
#define CORE_APP_WORLD_PACKET_BYTES 16384u
#define CORE_APP_WORLD_FRAGMENT_BYTES 64u
#define CORE_APP_WORLD_MAX_FRAGMENTS 64u
#define CORE_APP_WORLD_DRAIN_BUDGET 1u
#define CORE_APP_WORLD_STREAM_CAPACITY 16u
#define CORE_APP_WORLD_PENDING_BYTES 16384u
#define CORE_APP_WORLD_COMPLETION_CAPACITY 64u

static const u8 k_core_app_net_key_id[8] = {'c', 'o', 'r', 'e', 'a', 'p', 'p', '1'};

typedef struct CoreAppNetStats {
    u64 opened;
    u64 closed;
    u64 refused;
    u64 authenticated;
    u64 snapshots_sent;
    u64 send_overloads;
    u64 send_closed;
    u64 outbox_overloads;
    u64 auth_timeouts;
    u64 decode_failed;
    u64 physics_reports_sent;
    u64 physics_matched;
    u64 physics_desynced;
    u64 physics_unknown;
    u64 physics_decode_failed;
    u64 physics_corrections_sent;
    u64 physics_delta_corrections_sent;
    u64 clock_probes_answered;
    u64 clock_probe_decode_failed;
    u64 clock_probes_sent;
    u64 clock_replies_matched;
    u64 clock_replies_unmatched;
    u64 clock_probes_lost;
    u64 clock_samples_rejected;
    u64 session_welcomes_sent;
    u64 voice_frames_sent;
    u64 voice_frames_skipped;
    u64 voice_frames_invalid;
    u64 voice_frames_received;
    u64 voice_frames_played;
    u64 voice_frames_concealed;
    u64 voice_frames_dropped;
    u64 voice_peak;
    u64 voice_frames_relayed;
    u64 voice_relay_dropped;
    u64 voice_mute_requests;
    u64 voice_mute_rejected;
    u64 voice_frames_muted;
    u64 voice_frames_rate_limited;
} CoreAppNetStats;

typedef struct CoreAppNetAspectStats {
    u64 opened;
    u64 closed;
    u64 sent_fragments;
} CoreAppNetAspectStats;

typedef struct CoreAppNetWorldStats {
    u64 opened;
    u64 closed;
    u64 sent_fragments;
    u64 terminal_errors;
} CoreAppNetWorldStats;

typedef struct CoreAppNetRelayFrame {
    BreakSessionId source;
    u32 size;
    u8 bytes[CORE_APP_VOICE_RELAY_MAX_FRAME_BYTES];
} CoreAppNetRelayFrame;

/* Probes this server sends to one peer. */
typedef struct CoreAppNetClockState {
    ClockOffsetEstimator estimator;
    u64 outstanding_t0;
    u32 last_probe_tick;
    bool probed;
    bool outstanding;
    bool traced;
} CoreAppNetClockState;

struct CoreAppNetTransport {
    char host[64];
    u16 port;
    char tls_cert[CORE_APP_NET_PATH_CAPACITY];
    char tls_key[CORE_APP_NET_PATH_CAPACITY];
    char psk_env[128];
    char port_file[CORE_APP_NET_PATH_CAPACITY];
    u8 psk[32];
    u32 poll_ms;
    u32 current_tick;
    FILE *trace;
    BreakNetReactor *reactor;
    BreakRuntimeBus *bus;
    u64 events_published;
    u64 events_undelivered;
    BreakSessionManager *manager;
    SnowAcceptor *acceptor;
    bool started;
    bool listening;
    bool port_file_written;
    bool auth_installed;
    bool admission_open;
    bool producing;
    bool leaked;
    u64 live_generation;
    BreakConnectionKey keys[CORE_APP_NET_MAX_CONNECTIONS];
    bool authenticated[CORE_APP_NET_MAX_CONNECTIONS];
    bool welcomed[CORE_APP_NET_MAX_CONNECTIONS];
    bool closing[CORE_APP_NET_MAX_CONNECTIONS];
    bool correction_pending[CORE_APP_NET_MAX_CONNECTIONS];
    PhysicsSyncBaseline physics_baselines[CORE_APP_NET_MAX_CONNECTIONS];
    bool clock_probe_pending[CORE_APP_NET_MAX_CONNECTIONS];
    CoreAppClockProbe clock_probes[CORE_APP_NET_MAX_CONNECTIONS];
    CoreAppNetClockState clock[CORE_APP_NET_MAX_CONNECTIONS];
    BreakSessionId session_ids[CORE_APP_NET_MAX_CONNECTIONS];
    u64 opened_us[CORE_APP_NET_MAX_CONNECTIONS];
    BreakVoiceReceiver *voice_receivers[CORE_APP_NET_MAX_CONNECTIONS];
    BreakMsgRate voice_rates[CORE_APP_NET_MAX_CONNECTIONS];
    bool voice_rate_ready[CORE_APP_NET_MAX_CONNECTIONS];
    BreakSessionId voice_mutes[CORE_APP_NET_MAX_CONNECTIONS][CORE_APP_NET_VOICE_MUTE_CAPACITY];
    u32 voice_mute_count[CORE_APP_NET_MAX_CONNECTIONS];
    bool voice_relay;
    u32 relay_head;
    u32 relay_count;
    CoreAppNetRelayFrame relay_queue[CORE_APP_NET_VOICE_RELAY_QUEUE];
    u8 relay_wire[CORE_APP_VOICE_RELAY_MAX_BYTES];
    CoreAppSnapshot scratch_snapshot;
    u8 scratch_wire[CORE_APP_SNAPSHOT_MAX_BYTES];
    CoreAppSnapshotInbox inbox;
    CoreAppSnapshotOutbox outbox;
    PhysicsSyncTracker physics;
    u8 physics_report[PHYSICS_SYNC_REPORT_BYTES];
    bool physics_report_pending;
    bool physics_desync_traced;
    bool aspect_replication;
    BreakAspectStore *aspect_authoritative;
    BreakAspectStore *aspect_inbound;
    BreakSpatialIndex *aspect_index;
    BreakAspectReplication *aspect_replication_state;
    BreakAspectSession *aspect_session;
    BreakOnlineHandle aspect_objects[CORE_APP_ASPECT_OBJECT_COUNT];
    bool aspect_open[CORE_APP_NET_MAX_CONNECTIONS];
    BreakAoIScope aspect_scopes[CORE_APP_NET_MAX_CONNECTIONS];
    BreakAoIResult aspect_aoi[CORE_APP_NET_MAX_CONNECTIONS];
    CoreAppNetAspectStats aspect_stats;
    bool world_replication;
    BreakComponentSchemaRegistry *world_schemas;
    World *world_authoritative;
    World *world_diagnostic;
    BreakWorldSession *world_session;
    Entity world_objects[CORE_APP_WORLD_OBJECT_COUNT];
    bool world_open[CORE_APP_NET_MAX_CONNECTIONS];
    bool world_control_pending[CORE_APP_NET_MAX_CONNECTIONS];
    BreakWorldSessionControl world_controls[CORE_APP_NET_MAX_CONNECTIONS];
    bool world_force_full[CORE_APP_NET_MAX_CONNECTIONS];
    bool world_level_initialized;
    u64 world_level_generation;
    CoreAppNetWorldStats world_stats;
    CoreAppNetStats stats;
};

static void net_wipe(void *p, usize size) {
    volatile u8 *bytes = (volatile u8 *)p;
    while (size--) *bytes++ = 0u;
}

static bool net_copy(char *out, usize capacity, const char *value) {
    if (!value || value[0] == '\0') return false;
    usize length = strlen(value);
    if (length >= capacity) return false;
    memcpy(out, value, length + 1u);
    return true;
}

bool core_app_net_parse_bind(const char *bind, char *host, usize host_capacity, u16 *port) {
    if (!bind || !host || !port || host_capacity == 0u) return false;
    const char *colon = strrchr(bind, ':');
    if (!colon || colon == bind) return false;
    usize host_length = (usize)(colon - bind);
    if (host_length >= host_capacity) return false;
    u32 dots = 0u, digits = 0u, octet = 0u;
    for (usize i = 0u; i < host_length; ++i) {
        char c = bind[i];
        if (c == '.') {
            if (digits == 0u) return false;
            dots++;
            digits = 0u;
            octet = 0u;
        } else if (c >= '0' && c <= '9') {
            octet = octet * 10u + (u32)(c - '0');
            if (++digits > 3u || octet > 255u) return false;
        } else {
            return false;
        }
    }
    if (dots != 3u || digits == 0u) return false;
    const char *p = colon + 1;
    if (*p == '\0') return false;
    u32 value = 0u;
    for (; *p; ++p) {
        if (*p < '0' || *p > '9') return false;
        value = value * 10u + (u32)(*p - '0');
        if (value > 65535u) return false;
    }
    memcpy(host, bind, host_length);
    host[host_length] = '\0';
    *port = (u16)value;
    return true;
}

/* AUTH-v2 key lookup. The session layer calls it on this thread while it
 * verifies the HMAC; only the configured key id resolves. */
static bool net_auth_key(void *user, const u8 key_id[8], u8 out_psk[32]) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    if (!t || memcmp(key_id, k_core_app_net_key_id, 8u) != 0) return false;
    memcpy(out_psk, t->psk, 32u);
    return true;
}

static void net_trace(CoreAppNetTransport *t, const char *text) {
    if (t->trace) {
        (void)break_trace_core_app_write(t->trace, text);
        fflush(t->trace);
    }
}

static void net_release_baselines(CoreAppNetTransport *t) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        physics_sync_baseline_release(&t->physics_baselines[i]);
    }
}

/* Plays the slot's buffered peer voice that is due at now_ms. Played frames
 * only raise the peak counter; nothing reaches the level or a device. */
static void net_voice_play(CoreAppNetTransport *t, u32 slot, u64 now_ms, u32 max_pops) {
    BreakVoiceReceiver *receiver = t->voice_receivers[slot];
    if (!receiver) return;
    for (u32 n = 0u; n < max_pops; ++n) {
        BreakVoicePlayback playback;
        bool ready = false;
        if (break_voice_receiver_pop(receiver, now_ms, &playback, &ready) != BREAK_RUNTIME_OK ||
            !ready) {
            return;
        }
        if (playback.concealed) {
            t->stats.voice_frames_concealed++;
            continue;
        }
        t->stats.voice_frames_played++;
        for (u32 i = 0u; i < playback.sample_count; ++i) {
            i32 sample = playback.samples[i];
            u64 magnitude = (u64)(sample < 0 ? -sample : sample);
            if (magnitude > t->stats.voice_peak) t->stats.voice_peak = magnitude;
        }
    }
}

/* Tail flush: whatever the peer sent before it closed still plays, in
 * order, then the receiver's counts join the totals. Frames the capped
 * flush could not reach count as dropped, so received always equals played
 * plus what is counted dropped among accepted frames. Must run on the
 * thread that created the receiver (this transport's owner thread): the
 * receiver refuses stats and destroy from any other. */
static void net_voice_release(CoreAppNetTransport *t, u32 slot) {
    BreakVoiceReceiver *receiver = t->voice_receivers[slot];
    BreakVoiceReceiverStats stats;
    t->voice_rate_ready[slot] = false;
    if (!receiver) return;
    net_voice_play(t, slot, UINT64_MAX, CORE_APP_NET_VOICE_FLUSH_POPS);
    memset(&stats, 0, sizeof(stats));
    if (break_voice_receiver_stats(receiver, &stats) == BREAK_RUNTIME_OK) {
        t->stats.voice_frames_received += stats.accepted;
        t->stats.voice_frames_dropped +=
            stats.invalid + stats.duplicate + stats.stale + stats.overload;
        if (stats.accepted > stats.played) {
            t->stats.voice_frames_dropped += stats.accepted - stats.played;
        }
    }
    break_voice_receiver_destroy(receiver);
    t->voice_receivers[slot] = NULL;
}

static void net_voice_release_all(CoreAppNetTransport *t) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) net_voice_release(t, i);
}

static u64 net_aspect_clock(void *user) {
    (void)user;
    return time_microseconds() / 1000u;
}

static BreakRuntimeError net_aspect_send(void *user, u64 connection_id,
                                         const BreakReplicationFragment *fragment) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    BreakRuntimeError result = break_aspect_session_send(t->aspect_session, connection_id, fragment);
    if (result == BREAK_RUNTIME_OK) t->aspect_stats.sent_fragments++;
    return result;
}

static bool net_aspect_store_create(BreakAspectStore **out) {
    static const BreakAspectSchema schemas[] = {
        {1u, 1u, BREAK_ASPECT_U32, 4u},
        {2u, 1u, BREAK_ASPECT_U32, 4u},
        {3u, 1u, BREAK_ASPECT_F32, 4u},
        {4u, 1u, BREAK_ASPECT_F32, 4u},
        {5u, 1u, BREAK_ASPECT_F32, 4u},
        {6u, 1u, BREAK_ASPECT_U32, 4u},
    };
    BreakAspectStoreConfig config = {
        CORE_APP_ASPECT_STORE_OBJECTS, 16u, CORE_APP_ASPECT_PACKET_BYTES};
    *out = NULL;
    if (break_aspect_store_create(&config, out) != BREAK_RUNTIME_OK) return false;
    for (u32 i = 0u; i < sizeof(schemas) / sizeof(schemas[0]); ++i) {
        if (break_aspect_schema_register(*out, &schemas[i]) != BREAK_RUNTIME_OK) return false;
    }
    return true;
}

static bool net_aspect_create(CoreAppNetTransport *t) {
    BreakAspectReplicationConfig replication_config;
    BreakAspectSessionConfig session_config;
    BreakReplicationObject desc;
    BreakOnlineHandle reserved;
    if (!net_aspect_store_create(&t->aspect_authoritative) ||
        !net_aspect_store_create(&t->aspect_inbound)) {
        return false;
    }
    t->aspect_index = break_spatial_index_create(16.0f);
    if (!t->aspect_index ||
        break_aspect_object_create(t->aspect_authoritative, &reserved) != BREAK_RUNTIME_OK ||
        reserved.index != 0u) {
        return false;
    }
    memset(&replication_config, 0, sizeof(replication_config));
    replication_config.max_connections = CORE_APP_NET_MAX_CONNECTIONS;
    replication_config.max_objects = CORE_APP_ASPECT_STORE_OBJECTS;
    replication_config.max_packet_bytes = CORE_APP_ASPECT_PACKET_BYTES;
    replication_config.max_fragments = CORE_APP_ASPECT_MAX_FRAGMENTS;
    replication_config.send = net_aspect_send;
    replication_config.send_user = t;
    if (break_aspect_replication_create(&replication_config, t->aspect_authoritative,
                                        t->aspect_index, &t->aspect_replication_state) !=
        BREAK_RUNTIME_OK) {
        return false;
    }
    memset(&desc, 0, sizeof(desc));
    desc.flags = BREAK_AOI_OBJECT_ALWAYS_RELEVANT;
    for (u32 i = 0u; i < CORE_APP_ASPECT_OBJECT_COUNT; ++i) {
        desc.priority = i;
        if (break_aspect_object_register(t->aspect_replication_state, &desc,
                                         &t->aspect_objects[i]) != BREAK_RUNTIME_OK ||
            t->aspect_objects[i].index != i + 1u || t->aspect_objects[i].generation != 1u ||
            break_aspect_object_adopt(t->aspect_inbound, t->aspect_objects[i]) !=
                BREAK_RUNTIME_OK) {
            return false;
        }
    }
    memset(&session_config, 0, sizeof(session_config));
    session_config.store = t->aspect_inbound;
    session_config.bridge.reactor = t->reactor;
    session_config.bridge.max_connections = CORE_APP_NET_MAX_CONNECTIONS;
    session_config.bridge.stream_capacity = CORE_APP_ASPECT_STREAM_CAPACITY;
    session_config.bridge.max_pending_bytes_per_connection = CORE_APP_ASPECT_PENDING_BYTES;
    session_config.bridge.max_total_pending_bytes =
        CORE_APP_NET_MAX_CONNECTIONS * CORE_APP_ASPECT_PENDING_BYTES;
    session_config.bridge.max_fragment_bytes = CORE_APP_ASPECT_FRAGMENT_BYTES;
    session_config.bridge.max_fragment_count = CORE_APP_ASPECT_MAX_FRAGMENTS;
    session_config.bridge.completion_capacity = CORE_APP_ASPECT_COMPLETION_CAPACITY;
    session_config.bridge.max_completion_packet_bytes = CORE_APP_ASPECT_PACKET_BYTES;
    session_config.bridge.max_completion_queue_bytes =
        CORE_APP_ASPECT_COMPLETION_CAPACITY * CORE_APP_ASPECT_PACKET_BYTES;
    session_config.bridge.expiry_enabled = true;
    session_config.bridge.expiry_interval = CORE_APP_ASPECT_EXPIRY_INTERVAL_MS;
    session_config.bridge.expiry_max_idle = CORE_APP_ASPECT_EXPIRY_IDLE_MS;
    session_config.bridge.clock = net_aspect_clock;
    session_config.bridge.clock_user = t;
    t->aspect_session = break_aspect_session_create(&session_config);
    return t->aspect_session != NULL;
}

static void net_aspect_close(CoreAppNetTransport *t, u32 slot) {
    if (t->aspect_open[slot]) {
        (void)break_aspect_replication_disconnect(t->aspect_replication_state, t->keys[slot]);
        (void)break_aspect_session_close(t->aspect_session, t->keys[slot]);
        t->aspect_open[slot] = false;
        t->aspect_stats.closed++;
    }
    break_aoi_result_clear(&t->aspect_aoi[slot]);
    break_aoi_scope_clear(&t->aspect_scopes[slot]);
}

static void net_aspect_close_all(CoreAppNetTransport *t) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) net_aspect_close(t, i);
}

static void net_aspect_destroy(CoreAppNetTransport *t) {
    net_aspect_close_all(t);
    break_aspect_replication_destroy(t->aspect_replication_state);
    break_aspect_session_destroy(t->aspect_session);
    break_spatial_index_destroy(t->aspect_index);
    break_aspect_store_destroy(t->aspect_inbound);
    break_aspect_store_destroy(t->aspect_authoritative);
    t->aspect_replication_state = NULL;
    t->aspect_session = NULL;
    t->aspect_index = NULL;
    t->aspect_inbound = NULL;
    t->aspect_authoritative = NULL;
    memset(t->aspect_objects, 0, sizeof(t->aspect_objects));
}

static void net_aspect_tick_drain(CoreAppNetTransport *t, u64 now_ms) {
    if (!t->aspect_session) return;
    (void)break_aspect_session_tick(t->aspect_session, now_ms);
    (void)break_aspect_session_drain(t->aspect_session, CORE_APP_ASPECT_DRAIN_BUDGET);
}

static bool net_aspect_update_object(CoreAppNetTransport *t, u32 index,
                                     const CoreAppSnapshotEntity *entity) {
    BreakOnlineHandle handle = t->aspect_objects[index];
    BreakReplicationObject object;
    if (break_aspect_replication_set_u32(t->aspect_replication_state, handle, 1u,
                                         entity->index) != BREAK_RUNTIME_OK ||
        break_aspect_replication_set_u32(t->aspect_replication_state, handle, 2u,
                                         entity->generation) != BREAK_RUNTIME_OK ||
        break_aspect_replication_set_f32(t->aspect_replication_state, handle, 3u,
                                         entity->x) != BREAK_RUNTIME_OK ||
        break_aspect_replication_set_f32(t->aspect_replication_state, handle, 4u,
                                         entity->y) != BREAK_RUNTIME_OK ||
        break_aspect_replication_set_f32(t->aspect_replication_state, handle, 5u,
                                         entity->z) != BREAK_RUNTIME_OK ||
        break_aspect_replication_set_u32(t->aspect_replication_state, handle, 6u,
                                         entity->flags) != BREAK_RUNTIME_OK) {
        return false;
    }
    memset(&object, 0, sizeof(object));
    object.entity_id = break_aspect_aoi_id(handle);
    object.position[0] = entity->x;
    object.position[1] = entity->y;
    object.position[2] = entity->z;
    object.flags = BREAK_AOI_OBJECT_ALWAYS_RELEVANT;
    object.priority = index;
    return break_spatial_index_insert(t->aspect_index, &object);
}

static void net_aspect_update(CoreAppNetTransport *t, const CoreAppSnapshotEntity *entities,
                              u32 entity_count) {
    if (!t->aspect_replication_state || !entities || entity_count != CORE_APP_ASPECT_OBJECT_COUNT)
        return;
    for (u32 i = 0u; i < CORE_APP_ASPECT_OBJECT_COUNT; ++i) {
        if (!net_aspect_update_object(t, i, &entities[i])) return;
    }
}

static bool net_aspect_open(CoreAppNetTransport *t, u32 slot, BreakConnectionKey key) {
    if (!t->aspect_replication) return true;
    if (!break_aspect_session_open(t->aspect_session, key)) return false;
    if (break_aspect_connection_open(t->aspect_replication_state, key,
                                     CORE_APP_ASPECT_BANDWIDTH_BUDGET,
                                     CORE_APP_ASPECT_FRAGMENT_BYTES) != BREAK_RUNTIME_OK) {
        (void)break_aspect_session_close(t->aspect_session, key);
        break_aoi_result_clear(&t->aspect_aoi[slot]);
        break_aoi_scope_clear(&t->aspect_scopes[slot]);
        return false;
    }
    t->aspect_open[slot] = true;
    t->aspect_stats.opened++;
    return true;
}

static bool net_world_on_control(BreakConnectionKey connection,
                                 const BreakNetOwnedMessage *message, void *user);

static BreakWorldSession *net_world_session_create(CoreAppNetTransport *t,
                                                   u64 level_generation) {
    BreakWorldSessionConfig config;
    memset(&config, 0, sizeof(config));
    config.schemas = t->world_schemas;
    config.protocol_version = 1u;
    config.level_generation = level_generation;
    config.bridge.reactor = t->reactor;
    config.bridge.max_connections = CORE_APP_NET_MAX_CONNECTIONS;
    config.bridge.stream_capacity = CORE_APP_WORLD_STREAM_CAPACITY;
    config.bridge.max_pending_bytes_per_connection = CORE_APP_WORLD_PENDING_BYTES;
    config.bridge.max_total_pending_bytes =
        CORE_APP_NET_MAX_CONNECTIONS * CORE_APP_WORLD_PENDING_BYTES;
    config.bridge.max_fragment_bytes = CORE_APP_WORLD_FRAGMENT_BYTES;
    config.bridge.max_fragment_count = CORE_APP_WORLD_MAX_FRAGMENTS;
    config.bridge.completion_capacity = CORE_APP_WORLD_COMPLETION_CAPACITY;
    config.bridge.max_completion_packet_bytes = CORE_APP_WORLD_PACKET_BYTES;
    config.bridge.max_completion_queue_bytes =
        CORE_APP_WORLD_COMPLETION_CAPACITY * CORE_APP_WORLD_PACKET_BYTES;
    config.bridge.expiry_enabled = true;
    config.bridge.expiry_interval = CORE_APP_ASPECT_EXPIRY_INTERVAL_MS;
    config.bridge.expiry_max_idle = CORE_APP_ASPECT_EXPIRY_IDLE_MS;
    config.bridge.clock = net_aspect_clock;
    config.bridge.clock_user = t;
    config.packet_byte_limit = CORE_APP_WORLD_PACKET_BYTES;
    return break_world_session_create(&config);
}

static bool net_world_register_handlers(CoreAppNetTransport *t) {
    return break_session_manager_set_message_handler(
               t->manager, BREAK_NET_MESSAGE_ID_WORLD_DELTA,
               break_replication_session_handle_message,
               break_world_session_bridge(t->world_session)) &&
           break_session_manager_set_message_handler(
               t->manager, BREAK_NET_MESSAGE_ID_WORLD_CONTROL,
               net_world_on_control, t);
}

static bool net_world_create(CoreAppNetTransport *t) {
    static const BreakComponentSchema schemas[] = {
        {1u, 1u, sizeof(u32), _Alignof(u32),
         BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES, NULL, NULL},
        {2u, 1u, sizeof(u32), _Alignof(u32),
         BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES, NULL, NULL},
        {3u, 1u, sizeof(f32), _Alignof(f32),
         BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES, NULL, NULL},
        {4u, 1u, sizeof(f32), _Alignof(f32),
         BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES, NULL, NULL},
        {5u, 1u, sizeof(f32), _Alignof(f32),
         BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES, NULL, NULL},
        {6u, 1u, sizeof(u32), _Alignof(u32),
         BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES, NULL, NULL},
    };
    t->world_schemas = break_schema_registry_create();
    t->world_authoritative = world_create();
    t->world_diagnostic = world_create();
    if (!t->world_schemas || !t->world_authoritative || !t->world_diagnostic) return false;
    for (u32 i = 0u; i < sizeof(schemas) / sizeof(schemas[0]); ++i) {
        if (break_schema_register(t->world_schemas, &schemas[i]) != BREAK_SCHEMA_OK) return false;
        world_register_component(t->world_authoritative, schemas[i].component_id,
                                 (u32)schemas[i].size);
        world_register_component(t->world_diagnostic, schemas[i].component_id,
                                 (u32)schemas[i].size);
    }
    for (u32 i = 0u; i < CORE_APP_WORLD_OBJECT_COUNT; ++i) {
        t->world_objects[i] = world_create_entity(t->world_authoritative);
        if (t->world_objects[i].index != i + 1u || t->world_objects[i].generation != 1u) {
            return false;
        }
    }
    t->world_session = net_world_session_create(t, 0u);
    return t->world_session != NULL;
}

static bool net_world_initialize_level(CoreAppNetTransport *t, u64 level_generation) {
    BreakWorldSession *previous;
    BreakWorldSession *replacement;
    if (!t->world_replication || t->world_level_initialized) return true;
    replacement = net_world_session_create(t, level_generation);
    if (!replacement) return false;
    previous = t->world_session;
    t->world_session = replacement;
    if (!net_world_register_handlers(t)) {
        t->world_session = previous;
        break_world_session_destroy(replacement);
        (void)net_world_register_handlers(t);
        return false;
    }
    break_world_session_destroy(previous);
    t->world_level_generation = level_generation;
    t->world_level_initialized = true;
    return true;
}

static void net_world_close(CoreAppNetTransport *t, u32 slot) {
    if (t->world_open[slot]) {
        (void)break_world_session_close(t->world_session, t->keys[slot]);
        t->world_open[slot] = false;
        t->world_stats.closed++;
    }
    t->world_control_pending[slot] = false;
    t->world_force_full[slot] = false;
    memset(&t->world_controls[slot], 0, sizeof(t->world_controls[slot]));
}

static void net_world_close_all(CoreAppNetTransport *t) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) net_world_close(t, i);
}

static void net_world_destroy(CoreAppNetTransport *t) {
    net_world_close_all(t);
    break_world_session_destroy(t->world_session);
    world_destroy(t->world_diagnostic);
    world_destroy(t->world_authoritative);
    break_schema_registry_destroy(t->world_schemas);
    t->world_session = NULL;
    t->world_diagnostic = NULL;
    t->world_authoritative = NULL;
    t->world_schemas = NULL;
    t->world_level_initialized = false;
    t->world_level_generation = 0u;
    memset(t->world_objects, 0, sizeof(t->world_objects));
}

static bool net_world_set_component(World *world, Entity entity, ComponentType component,
                                    const void *bytes) {
    void *value = world_add_component(world, entity, component);
    if (!value) return false;
    memcpy(value, bytes, sizeof(u32));
    return true;
}

static void net_world_update(CoreAppNetTransport *t, const CoreAppSnapshotEntity *entities,
                             u32 entity_count) {
    if (!t->world_authoritative || !entities || entity_count != CORE_APP_WORLD_OBJECT_COUNT) {
        return;
    }
    for (u32 i = 0u; i < CORE_APP_WORLD_OBJECT_COUNT; ++i) {
        const CoreAppSnapshotEntity *entity = &entities[i];
        Entity handle = t->world_objects[i];
        if (!net_world_set_component(t->world_authoritative, handle, 1u, &entity->index) ||
            !net_world_set_component(t->world_authoritative, handle, 2u, &entity->generation) ||
            !net_world_set_component(t->world_authoritative, handle, 3u, &entity->x) ||
            !net_world_set_component(t->world_authoritative, handle, 4u, &entity->y) ||
            !net_world_set_component(t->world_authoritative, handle, 5u, &entity->z) ||
            !net_world_set_component(t->world_authoritative, handle, 6u, &entity->flags)) {
            return;
        }
    }
}

static bool net_world_open(CoreAppNetTransport *t, u32 slot, BreakConnectionKey key) {
    if (!t->world_replication) return true;
    if (!t->world_level_initialized || !break_world_session_open(t->world_session, key)) {
        return false;
    }
    t->world_open[slot] = true;
    t->world_stats.opened++;
    return true;
}

static BreakNetSendResult net_world_publish_slot(CoreAppNetTransport *t, u32 slot) {
    BreakWorldSessionSenderState state;
    BreakWorldSessionStats before;
    BreakWorldSessionStats after;
    BreakNetSendResult result;
    usize outbound_before;
    usize outbound_after;
    if (!t->world_open[slot] || !t->world_level_initialized) return BREAK_NET_SEND_CLOSED;
    if (!break_world_session_sender_state(t->world_session, t->keys[slot], &state)) {
        return BREAK_NET_SEND_CLOSED;
    }
    if (!state.attempt_pending && state.history_count != 0u && !t->world_force_full[slot]) {
        return BREAK_NET_SEND_OK;
    }
    break_world_session_stats(t->world_session, &before);
    outbound_before = break_net_reactor_outbound_count(t->reactor);
    result = break_world_session_publish(t->world_session, t->keys[slot],
                                         t->world_authoritative, t->current_tick);
    outbound_after = break_net_reactor_outbound_count(t->reactor);
    if (outbound_after >= outbound_before) {
        t->world_stats.sent_fragments += outbound_after - outbound_before;
    }
    break_world_session_stats(t->world_session, &after);
    if (result == BREAK_NET_SEND_OK &&
        after.published_full_packets > before.published_full_packets) {
        t->world_force_full[slot] = false;
    } else if (result != BREAK_NET_SEND_OK && result != BREAK_NET_SEND_OVERLOAD) {
        t->world_stats.terminal_errors++;
    }
    return result;
}

static void net_world_tick_drain(CoreAppNetTransport *t, u64 now_ms) {
    if (!t->world_session || !t->world_level_initialized) return;
    (void)break_replication_session_bridge_tick(break_world_session_bridge(t->world_session),
                                                now_ms);
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        BreakNetSendResult sent;
        if (!t->world_open[i]) continue;
        (void)break_world_session_drain(t->world_session, t->keys[i], t->world_diagnostic,
                                        CORE_APP_WORLD_DRAIN_BUDGET);
        if (!t->world_control_pending[i]) {
            t->world_control_pending[i] = break_world_session_poll_control(
                t->world_session, t->keys[i], &t->world_controls[i]);
        }
        if (!t->world_control_pending[i]) continue;
        sent = break_world_session_send_control(t->world_session, t->keys[i],
                                                &t->world_controls[i]);
        if (sent == BREAK_NET_SEND_OK) {
            t->world_control_pending[i] = false;
        } else if (sent != BREAK_NET_SEND_OVERLOAD) {
            t->world_control_pending[i] = false;
            t->world_stats.terminal_errors++;
        }
    }
}

static int net_slot_find(const CoreAppNetTransport *t, BreakConnectionKey key) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->keys[i] == key && key != 0u) return (int)i;
    }
    return -1;
}

static bool net_world_on_control(BreakConnectionKey connection,
                                 const BreakNetOwnedMessage *message, void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    BreakWorldSessionStats before;
    BreakWorldSessionStats after;
    bool handled;
    int slot;
    if (!t || !t->world_session) return false;
    break_world_session_stats(t->world_session, &before);
    handled = break_world_session_handle_control(connection, message, t->world_session);
    if (!handled) return false;
    break_world_session_stats(t->world_session, &after);
    if (after.acknowledged_packets == before.acknowledged_packets) {
        slot = net_slot_find(t, connection);
        if (slot >= 0) t->world_force_full[slot] = true;
    }
    return true;
}

static int net_slot_add(CoreAppNetTransport *t, BreakConnectionKey key) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->keys[i] == 0u) {
            t->keys[i] = key;
            t->authenticated[i] = false;
            t->welcomed[i] = false;
            t->closing[i] = false;
            t->correction_pending[i] = false;
            physics_sync_baseline_release(&t->physics_baselines[i]);
            t->clock_probe_pending[i] = false;
            memset(&t->clock[i], 0, sizeof(t->clock[i]));
            clock_offset_init(&t->clock[i].estimator);
            t->session_ids[i] = 0u;
            t->voice_mute_count[i] = 0u;
            t->opened_us[i] = time_microseconds();
            return (int)i;
        }
    }
    return -1;
}

/* Peer snapshots only reach the authority firewall. The handler has no
 * pointer to the level, and its result only changes counters. A payload
 * with bytes past the declared entities is a decode failure. */
static bool net_on_snapshot(BreakConnectionKey connection, const BreakNetOwnedMessage *message,
                            void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    CoreAppSnapshot *peer = &t->scratch_snapshot;
    memset(peer, 0, sizeof(*peer));
    if (core_app_snapshot_decode((const u8 *)message->data, message->size, peer) !=
            CORE_APP_SNAPSHOT_OK ||
        message->size != CORE_APP_SNAPSHOT_HEADER_BYTES +
                             (usize)peer->entity_count * CORE_APP_SNAPSHOT_ENTITY_BYTES) {
        t->stats.decode_failed++;
        return false;
    }
    t->inbox.authenticated = break_session_manager_state(t->manager, connection) ==
                             BREAK_SESSION_AUTHENTICATED;
    (void)core_app_snapshot_admit(&t->inbox, message->message_id, peer, t->live_generation);
    t->inbox.authenticated = false;
    return true;
}

/* Peer physics reports only change counters and, on the first desync, one
 * trace line. The world is never touched from here. */
static bool net_on_physics_report(BreakConnectionKey connection,
                                  const BreakNetOwnedMessage *message, void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    u32 tick = 0u;
    u64 hash = 0u;
    if (!physics_sync_decode_report((const u8 *)message->data, message->size, &tick, &hash)) {
        t->stats.physics_decode_failed++;
        return false;
    }
    PhysicsSyncVerdict verdict = physics_sync_check(&t->physics, tick, hash);
    if (verdict == PHYSICS_SYNC_MATCH) {
        t->stats.physics_matched++;
        int slot = net_slot_find(t, connection);
        if (slot >= 0) physics_sync_baseline_confirm(&t->physics_baselines[slot], tick);
    } else if (verdict == PHYSICS_SYNC_DESYNC) {
        t->stats.physics_desynced++;
        int slot = net_slot_find(t, connection);
        if (slot >= 0) t->correction_pending[slot] = true;
        if (!t->physics_desync_traced) {
            char line[128];
            t->physics_desync_traced = true;
            snprintf(line, sizeof(line),
                     "COREAPPTRACE version=1 event=network_physics_sync result=desync"
                     " tick=%u\n", tick);
            net_trace(t, line);
        }
    } else {
        t->stats.physics_unknown++;
    }
    return true;
}

/* A reply that echoes the outstanding t0 becomes one estimator sample;
 * the offset is traced once, when the window first holds enough samples. */
static bool net_on_clock_reply(CoreAppNetTransport *t, int slot, const CoreAppClockProbe *reply,
                               u64 t3) {
    CoreAppNetClockState *clock = &t->clock[slot];
    if (!clock->outstanding || reply->t0 != clock->outstanding_t0) {
        t->stats.clock_replies_unmatched++;
        return false;
    }
    ClockOffsetSample sample = {reply->t0, reply->t1, reply->t2, t3};
    ClockOffsetEstimate estimate;
    clock->outstanding = false;
    t->stats.clock_replies_matched++;
    if (clock_offset_add(&clock->estimator, &sample) != CLOCK_OFFSET_OK) {
        t->stats.clock_samples_rejected++;
    }
    if (!clock->traced && clock_offset_estimate(&clock->estimator, &estimate) == CLOCK_OFFSET_OK &&
        estimate.samples >= CORE_APP_NET_CLOCK_OFFSET_TRACE_SAMPLES) {
        char line[192];
        clock->traced = true;
        snprintf(line, sizeof(line),
                 "COREAPPTRACE version=1 event=network_clock_offset session=%llu"
                 " offset_us=%lld error_us=%llu samples=%u\n",
                 (unsigned long long)t->session_ids[slot], (long long)estimate.offset_us,
                 (unsigned long long)estimate.error_us, estimate.samples);
        net_trace(t, line);
    }
    return true;
}

/* Requests are stored per connection with their receive time t1 and
 * answered in net_send_pending so t2 is the actual send time; replies feed
 * this server's own estimate. t1/t3 are read before decoding. */
static bool net_on_clock_probe(BreakConnectionKey connection,
                               const BreakNetOwnedMessage *message, void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    u64 t1 = time_microseconds();
    CoreAppClockProbe probe;
    if (core_app_clock_probe_decode((const u8 *)message->data, message->size, &probe) !=
        CORE_APP_SNAPSHOT_OK) {
        t->stats.clock_probe_decode_failed++;
        return false;
    }
    int slot = net_slot_find(t, connection);
    if (slot < 0) return false;
    if (probe.kind == CORE_APP_CLOCK_PROBE_REPLY) return net_on_clock_reply(t, slot, &probe, t1);
    probe.t1 = t1;
    t->clock_probes[slot] = probe;
    t->clock_probe_pending[slot] = true;
    return true;
}

static void net_close_slot(CoreAppNetTransport *t, u32 i) {
    t->authenticated[i] = false;
    if (t->closing[i]) return;
    net_aspect_close(t, i);
    net_world_close(t, i);
    t->closing[i] = true;
    (void)break_session_manager_close(t->manager, t->keys[i], 0u);
    (void)break_net_reactor_close(t->reactor, t->keys[i]);
}

static void net_sync_sessions(CoreAppNetTransport *t, u32 tick) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        BreakConnectionKey key = t->keys[i];
        if (key == 0u || t->closing[i]) continue;
        BreakSessionState state = break_session_manager_state(t->manager, key);
        if (state == BREAK_SESSION_AUTHENTICATED && !t->authenticated[i]) {
            char line[160];
            t->authenticated[i] = true;
            t->session_ids[i] = break_session_manager_session_id(t->manager, key);
            t->stats.authenticated++;
            snprintf(line, sizeof(line),
                     "COREAPPTRACE version=1 event=network_session result=authenticated"
                     " session=%llu tick=%u\n",
                     (unsigned long long)t->session_ids[i], tick);
            net_trace(t, line);
        } else if (state == BREAK_SESSION_CLOSING || state == BREAK_SESSION_CLOSED ||
                   state == BREAK_SESSION_UNKNOWN) {
            net_close_slot(t, i);
        } else if (!t->authenticated[i] &&
                   time_microseconds() - t->opened_us[i] >=
                       (u64)CORE_APP_NET_AUTH_DEADLINE_MS * 1000u) {
            t->stats.auth_timeouts++;
            net_close_slot(t, i);
        }
    }
}

static void net_pump(CoreAppNetTransport *t, int timeout_ms, u32 *budget, u32 tick) {
    BreakNetEvent event;
    (void)break_net_reactor_step(t->reactor, timeout_ms);
    while (*budget > 0u && break_net_reactor_poll_event(t->reactor, &event) == BREAK_NET_EVENT_OK) {
        (*budget)--;
        if (event.type == BREAK_NET_EVENT_SEND_DRAINED) {
            /* Flow-control notice only; the session layer has no use for it. */
            break_net_event_release(&event);
            continue;
        }
        if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED) {
            int slot = -1;
            if (!t->admission_open || net_slot_find(t, event.connection_key) >= 0 ||
                (slot = net_slot_add(t, event.connection_key)) < 0) {
                t->stats.refused++;
                (void)break_net_reactor_close(t->reactor, event.connection_key);
                break_net_event_release(&event);
                continue;
            }
            if (!net_aspect_open(t, (u32)slot, event.connection_key) ||
                !net_world_open(t, (u32)slot, event.connection_key)) {
                net_world_close(t, (u32)slot);
                net_aspect_close(t, (u32)slot);
                t->keys[slot] = 0u;
                t->closing[slot] = false;
                physics_sync_baseline_release(&t->physics_baselines[slot]);
                t->stats.refused++;
                (void)break_net_reactor_close(t->reactor, event.connection_key);
                break_net_event_release(&event);
                continue;
            }
            t->stats.opened++;
        }
        (void)break_session_manager_apply_adapter_event(t->manager, &event);
        if (event.type == BREAK_NET_EVENT_CONNECTION_CLOSED ||
            event.type == BREAK_NET_EVENT_TRANSPORT_ERROR) {
            int slot = net_slot_find(t, event.connection_key);
            if (slot >= 0) {
                net_voice_release(t, (u32)slot);
                net_aspect_close(t, (u32)slot);
                net_world_close(t, (u32)slot);
                t->keys[slot] = 0u;
                t->authenticated[slot] = false;
                t->welcomed[slot] = false;
                t->closing[slot] = false;
                t->session_ids[slot] = 0u;
                t->voice_mute_count[slot] = 0u;
                t->correction_pending[slot] = false;
                physics_sync_baseline_release(&t->physics_baselines[slot]);
                t->clock_probe_pending[slot] = false;
                t->stats.closed++;
            }
        }
        break_net_event_release(&event);
    }
    if (break_net_reactor_event_queue_empty(t->reactor)) {
        (void)break_session_manager_poll(t->manager, 32u);
    }
    net_sync_sessions(t, tick);
}

/* A slot may receive a snapshot only while its key still names the session
 * that authenticated. Connection keys are reused with transport slots, so a
 * close still waiting in the event queue could otherwise let a new,
 * unauthenticated connection inherit the old key. */
static bool net_slot_live(const CoreAppNetTransport *t, u32 i) {
    BreakConnectionKey key = t->keys[i];
    return key != 0u && t->authenticated[i] && !t->closing[i] &&
           break_session_manager_state(t->manager, key) == BREAK_SESSION_AUTHENTICATED &&
           break_session_manager_session_id(t->manager, key) == t->session_ids[i];
}

/* Everything else waits for the welcome, so it is the first application
 * message a peer receives after AUTH. */
static bool net_slot_sendable(const CoreAppNetTransport *t, u32 i) {
    return t->welcomed[i] && net_slot_live(t, i);
}

static BreakRuntimeError net_aspect_sync_slot(CoreAppNetTransport *t, u32 slot) {
    BreakAoIResult *aoi = &t->aspect_aoi[slot];
    BreakAoIScope *scope = &t->aspect_scopes[slot];
    BreakAoIEntityId ids[CORE_APP_ASPECT_OBJECT_COUNT];
    usize count;
    BreakRuntimeError result;
    if (!break_aoi_compute(t->aspect_index, NULL, 0u, scope, aoi)) return BREAK_RUNTIME_FAILED;
    result = break_aspect_replication_sync_default(t->aspect_replication_state, t->keys[slot], aoi);
    if (result != BREAK_RUNTIME_OK) return result;
    count = aoi->enter_count + aoi->stay_count;
    if (count > CORE_APP_ASPECT_OBJECT_COUNT) return BREAK_RUNTIME_FAILED;
    for (usize i = 0u; i < aoi->enter_count; ++i) ids[i] = aoi->enter[i];
    for (usize i = 0u; i < aoi->stay_count; ++i) ids[aoi->enter_count + i] = aoi->stay[i];
    if (!break_aoi_scope_assign(scope, ids, count)) return BREAK_RUNTIME_FAILED;
    return BREAK_RUNTIME_OK;
}

static void net_aspect_sync_sendable(CoreAppNetTransport *t) {
    if (!t->aspect_replication_state) return;
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->aspect_open[i] && net_slot_sendable(t, i)) (void)net_aspect_sync_slot(t, i);
    }
}

/* Copies a frame the receiver accepted so net_send_pending can relay it.
 * The source is the session manager's id for the connection: voice can be
 * applied in the same batch as AUTH, before net_sync_sessions records the
 * slot's own id. */
static void net_voice_relay_queue(CoreAppNetTransport *t, BreakConnectionKey connection,
                                  const void *data, usize size) {
    BreakSessionId source = break_session_manager_session_id(t->manager, connection);
    if (source == 0u || size == 0u || size > CORE_APP_VOICE_RELAY_MAX_FRAME_BYTES) return;
    if (t->relay_count >= CORE_APP_NET_VOICE_RELAY_QUEUE) {
        t->stats.voice_relay_dropped++;
        return;
    }
    u32 tail = (t->relay_head + t->relay_count) % CORE_APP_NET_VOICE_RELAY_QUEUE;
    CoreAppNetRelayFrame *entry = &t->relay_queue[tail];
    entry->source = source;
    entry->size = (u32)size;
    memcpy(entry->bytes, data, size);
    t->relay_count++;
}

static bool net_voice_muted(const CoreAppNetTransport *t, u32 slot, BreakSessionId source) {
    for (u32 i = 0u; i < t->voice_mute_count[slot]; ++i) {
        if (t->voice_mutes[slot][i] == source) return true;
    }
    return false;
}

/* Sends every queued frame to each sendable slot except its source, so
 * voice_frames_relayed counts one per recipient. A peer welcomed after a
 * frame was queued still receives it. Only called from net_send_pending,
 * after the event queue is empty. */
static void net_send_voice_relay(CoreAppNetTransport *t) {
    while (t->relay_count > 0u) {
        const CoreAppNetRelayFrame *entry = &t->relay_queue[t->relay_head];
        usize size = 0u;
        bool encoded = core_app_voice_relay_encode(entry->source, entry->bytes, entry->size,
                                                   t->relay_wire, sizeof(t->relay_wire),
                                                   &size) == CORE_APP_SNAPSHOT_OK;
        for (u32 i = 0u; encoded && i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
            if (!net_slot_sendable(t, i) || t->session_ids[i] == entry->source) continue;
            if (net_voice_muted(t, i, entry->source)) {
                t->stats.voice_frames_muted++;
                continue;
            }
            BreakNetSendResult sent = break_net_reactor_send(
                t->reactor, t->keys[i], CORE_APP_VOICE_RELAY_MESSAGE_ID, 1u, t->relay_wire,
                size);
            if (sent == BREAK_NET_SEND_OK) t->stats.voice_frames_relayed++;
            else if (sent == BREAK_NET_SEND_OVERLOAD) t->stats.send_overloads++;
            else t->stats.send_closed++;
        }
        if (!encoded) t->stats.voice_relay_dropped++;
        t->relay_head = (t->relay_head + 1u) % CORE_APP_NET_VOICE_RELAY_QUEUE;
        t->relay_count--;
    }
}

/* A peer mutes or unmutes one source session in the relay to itself. Both
 * are idempotent. A payload that does not decode, or a mute when the list
 * is full, is counted and keeps the session open. */
static bool net_on_voice_mute(BreakConnectionKey connection, const BreakNetOwnedMessage *message,
                              void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    int slot = net_slot_find(t, connection);
    if (slot < 0 || t->closing[slot]) return false;
    u64 target = 0u;
    bool muted = false;
    if (core_app_voice_mute_decode((const u8 *)message->data, message->size, &target, &muted) !=
        CORE_APP_SNAPSHOT_OK) {
        t->stats.voice_mute_rejected++;
        return true;
    }
    t->stats.voice_mute_requests++;
    BreakSessionId *list = t->voice_mutes[slot];
    u32 *count = &t->voice_mute_count[slot];
    for (u32 i = 0u; i < *count; ++i) {
        if (list[i] != target) continue;
        if (!muted) list[i] = list[--*count];
        return true;
    }
    if (!muted) return true;
    if (*count >= CORE_APP_NET_VOICE_MUTE_CAPACITY) {
        t->stats.voice_mute_rejected++;
        return true;
    }
    list[(*count)++] = target;
    return true;
}

/* Peer voice is decoded into the connection's jitter buffer at once, so the
 * receiver's inbox never holds more than this one message. The session
 * layer already admits 0x4006 only after AUTH; a slot that is closing (or
 * that no longer exists) refuses it. A frame over the connection's voice
 * rate limit is counted and dropped before it is decoded or relayed.
 * Malformed, duplicate and stale frames are counted by the receiver and
 * keep the session open. */
static bool net_on_voice(BreakConnectionKey connection, const BreakNetOwnedMessage *message,
                         void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    int slot = net_slot_find(t, connection);
    if (slot < 0 || t->closing[slot]) return false;
    if (message->size == 0u) {
        t->stats.voice_frames_dropped++;
        return true;
    }
    const u64 now_ms = time_microseconds() / 1000u;
    if (!t->voice_rate_ready[slot]) {
        t->voice_rate_ready[slot] = break_msg_rate_init(
            &t->voice_rates[slot], CORE_APP_NET_VOICE_RATE_PER_SEC,
            CORE_APP_NET_VOICE_RATE_BURST,
            CORE_APP_NET_VOICE_RATE_PER_SEC * BREAK_NET_CORE_VOICE_MAX_PAYLOAD,
            CORE_APP_NET_VOICE_RATE_BURST * BREAK_NET_CORE_VOICE_MAX_PAYLOAD, now_ms);
        if (!t->voice_rate_ready[slot]) return false;
    }
    if (break_msg_rate_admit(&t->voice_rates[slot], (u32)message->size, now_ms) !=
        BREAK_MSG_RATE_OK) {
        t->stats.voice_frames_rate_limited++;
        return true;
    }
    if (!t->voice_receivers[slot]) {
        BreakVoiceStreamConfig config;
        memset(&config, 0, sizeof(config));
        config.sample_rate = 48000u;
        config.channels = 1u;
        config.sample_count = BREAK_VOICE_MAX_SAMPLES;
        config.jitter_delay_ms = CORE_APP_NET_VOICE_DELAY_MS;
        config.jitter_capacity = CORE_APP_NET_VOICE_JITTER_FRAMES;
        config.queue_capacity = CORE_APP_NET_VOICE_QUEUE;
        if (break_voice_receiver_create(NULL, &config, &t->voice_receivers[slot]) !=
            BREAK_RUNTIME_OK) {
            return false;
        }
    }
    BreakVoiceReceiver *receiver = t->voice_receivers[slot];
    BreakVoiceReceiverStats before;
    BreakVoiceReceiverStats after;
    if (break_voice_receiver_stats(receiver, &before) != BREAK_RUNTIME_OK ||
        break_voice_receiver_push(receiver, message->data, (u32)message->size) !=
            BREAK_RUNTIME_OK ||
        break_voice_receiver_pump(receiver, 1u, now_ms) != BREAK_RUNTIME_OK) {
        return false;
    }
    if (t->voice_relay && break_voice_receiver_stats(receiver, &after) == BREAK_RUNTIME_OK &&
        after.accepted > before.accepted) {
        net_voice_relay_queue(t, connection, message->data, message->size);
    }
    return true;
}

/* Tells each newly authenticated peer the session number this server's
 * trace names it by. A send that fails is retried on the next pump. */
static void net_send_welcomes(CoreAppNetTransport *t) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->welcomed[i] || !net_slot_live(t, i)) continue;
        u8 wire[CORE_APP_SESSION_WELCOME_BYTES];
        usize size = 0u;
        if (core_app_session_welcome_encode(t->session_ids[i], wire, sizeof(wire), &size) !=
            CORE_APP_SNAPSHOT_OK) {
            continue;
        }
        BreakNetSendResult sent = break_net_reactor_send(
            t->reactor, t->keys[i], CORE_APP_SESSION_WELCOME_MESSAGE_ID, 1u, wire, size);
        if (sent == BREAK_NET_SEND_OK) {
            t->welcomed[i] = true;
            t->stats.session_welcomes_sent++;
        } else if (sent == BREAK_NET_SEND_OVERLOAD) {
            t->stats.send_overloads++;
        } else {
            t->stats.send_closed++;
        }
    }
}

static void net_send_clock_replies(CoreAppNetTransport *t) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (!t->clock_probe_pending[i]) continue;
        t->clock_probe_pending[i] = false;
        if (!net_slot_sendable(t, i)) continue;
        CoreAppClockProbe request = t->clock_probes[i];
        CoreAppClockProbe reply;
        u8 wire[CORE_APP_CLOCK_PROBE_BYTES];
        usize size = 0u;
        u64 t1 = request.t1;
        request.t1 = 0u;
        if (core_app_clock_probe_answer(&request, t1, time_microseconds(), &reply) !=
                CORE_APP_SNAPSHOT_OK ||
            core_app_clock_probe_encode(&reply, wire, sizeof(wire), &size) !=
                CORE_APP_SNAPSHOT_OK) {
            continue;
        }
        BreakNetSendResult sent = break_net_reactor_send(
            t->reactor, t->keys[i], CORE_APP_CLOCK_PROBE_MESSAGE_ID, 1u, wire, size);
        if (sent == BREAK_NET_SEND_OK) t->stats.clock_probes_answered++;
        else if (sent == BREAK_NET_SEND_OVERLOAD) t->stats.send_overloads++;
        else t->stats.send_closed++;
    }
}

/* One outstanding request per peer. A request unanswered for TIMEOUT_TICKS
 * is dropped; the next one is sent once INTERVAL_TICKS have passed. A tick
 * counter that went backwards (a new level) counts as elapsed. */
static void net_send_clock_requests(CoreAppNetTransport *t) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (!net_slot_sendable(t, i)) continue;
        CoreAppNetClockState *clock = &t->clock[i];
        u32 tick = t->current_tick;
        bool restarted = tick < clock->last_probe_tick;
        u32 elapsed = restarted ? UINT32_MAX : tick - clock->last_probe_tick;
        if (clock->outstanding) {
            if (elapsed < CORE_APP_NET_CLOCK_PROBE_TIMEOUT_TICKS) continue;
            clock->outstanding = false;
            t->stats.clock_probes_lost++;
        }
        if (clock->probed && elapsed < CORE_APP_NET_CLOCK_PROBE_INTERVAL_TICKS) continue;
        u64 now = time_microseconds();
        CoreAppClockProbe request = {CORE_APP_CLOCK_PROBE_REQUEST, now, 0u, 0u};
        u8 wire[CORE_APP_CLOCK_PROBE_BYTES];
        usize size = 0u;
        if (core_app_clock_probe_encode(&request, wire, sizeof(wire), &size) !=
            CORE_APP_SNAPSHOT_OK) {
            continue;
        }
        BreakNetSendResult sent = break_net_reactor_send(
            t->reactor, t->keys[i], CORE_APP_CLOCK_PROBE_MESSAGE_ID, 1u, wire, size);
        if (sent == BREAK_NET_SEND_OK) {
            clock->outstanding = true;
            clock->outstanding_t0 = now;
            clock->last_probe_tick = tick;
            clock->probed = true;
            t->stats.clock_probes_sent++;
        } else if (sent == BREAK_NET_SEND_OVERLOAD) {
            t->stats.send_overloads++;
        } else {
            t->stats.send_closed++;
        }
    }
}

static void net_send_pending(CoreAppNetTransport *t) {
    CoreAppSnapshot *snapshot = &t->scratch_snapshot;
    u8 *wire = t->scratch_wire;
    /* Unprocessed events may include a close for a key that a new
     * connection already reuses; hold snapshots until the queue is empty. */
    if (!break_net_reactor_event_queue_empty(t->reactor)) return;
    net_send_welcomes(t);
    net_aspect_sync_sendable(t);
    net_send_voice_relay(t);
    net_send_clock_replies(t);
    if (t->producing) net_send_clock_requests(t);
    while (core_app_snapshot_outbox_pop(&t->outbox, snapshot)) {
        usize size = 0u;
        if (core_app_snapshot_encode(snapshot, wire, CORE_APP_SNAPSHOT_MAX_BYTES, &size) !=
            CORE_APP_SNAPSHOT_OK) {
            continue;
        }
        for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
            if (!net_slot_sendable(t, i)) continue;
            BreakNetSendResult sent = break_net_reactor_send(
                t->reactor, t->keys[i], CORE_APP_SNAPSHOT_MESSAGE_ID,
                CORE_APP_SNAPSHOT_PROTOCOL_VERSION, wire, size);
            if (sent == BREAK_NET_SEND_OK) t->stats.snapshots_sent++;
            else if (sent == BREAK_NET_SEND_OVERLOAD) t->stats.send_overloads++;
            else t->stats.send_closed++;
        }
    }
    if (!t->physics_report_pending) return;
    t->physics_report_pending = false;
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (!net_slot_sendable(t, i)) continue;
        BreakNetSendResult sent = break_net_reactor_send(
            t->reactor, t->keys[i], BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, 1u,
            t->physics_report, sizeof(t->physics_report));
        if (sent == BREAK_NET_SEND_OK) t->stats.physics_reports_sent++;
        else if (sent == BREAK_NET_SEND_OVERLOAD) t->stats.send_overloads++;
        else t->stats.send_closed++;
    }
}

static BreakRuntimeError net_write_port_file(CoreAppNetTransport *t, u16 port) {
    char text[16];
    int length = snprintf(text, sizeof(text), "%u\n", (unsigned)port);
    PlatformAtomicWriter *writer = platform_atomic_writer_open(t->port_file);
    if (!writer) return BREAK_RUNTIME_FAILED;
    if (length <= 0 || !platform_atomic_writer_write(writer, text, (usize)length)) {
        platform_atomic_writer_abort(writer);
        return BREAK_RUNTIME_FAILED;
    }
    PlatformAtomicCommitResult committed = platform_atomic_writer_commit_status(writer);
    if (committed != PLATFORM_ATOMIC_SUCCESS_DURABLE &&
        committed != PLATFORM_ATOMIC_RENAMED_DURABILITY_UNKNOWN) {
        return BREAK_RUNTIME_FAILED;
    }
    /* The reader only needs the file to exist; durability does not matter. */
    t->port_file_written = true;
    return BREAK_RUNTIME_OK;
}

static const BreakRuntimeBusKind k_net_event_kind = {
    CORE_APP_NET_EVENT_KIND, CORE_APP_NET_EVENT_VERSION, CORE_APP_NET_EVENT_SIZE,
    "core_app.net.event", true, 0u};

static void net_put(u8 *p, u64 v, u32 bytes) {
    for (u32 i = 0u; i < bytes; ++i) p[i] = (u8)(v >> (8u * i));
}

static u64 net_get(const u8 *p, u32 bytes) {
    u64 v = 0u;
    for (u32 i = 0u; i < bytes; ++i) v |= (u64)p[i] << (8u * i);
    return v;
}

/* Reactor event hook: runs on the stepping thread with no reactor lock. */
static void net_on_reactor_event(void *user, const BreakNetEventInfo *info) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    u8 payload[CORE_APP_NET_EVENT_SIZE] = {0};
    BreakRuntimeMessageView view;
    u32 delivered = 0u;
    if (!t->bus) return;
    net_put(payload, (u64)info->type, 4u);
    net_put(payload + 4, info->reason, 4u);
    net_put(payload + 8, info->connection_key, 8u);
    net_put(payload + 16, info->correlation_id, 8u);
    net_put(payload + 24, (u64)info->payload_size, 8u);
    net_put(payload + 32, info->message_id, 2u);
    payload[34] = info->queued ? 1u : 0u;
    memset(&view, 0, sizeof(view));
    view.kind = CORE_APP_NET_EVENT_KIND;
    view.version = CORE_APP_NET_EVENT_VERSION;
    view.correlation_id = info->correlation_id;
    view.data = payload;
    view.size = sizeof(payload);
    if (break_runtime_bus_publish(t->bus, &view, &delivered) != BREAK_RUNTIME_OK) {
        t->events_undelivered++;
    }
    if (delivered > 0u) t->events_published++;
}

bool core_app_net_event_notice_decode(const void *data, usize size, CoreAppNetEventNotice *out) {
    const u8 *p = (const u8 *)data;
    if (!data || !out || size != CORE_APP_NET_EVENT_SIZE) return false;
    if (p[34] > 1u) return false;
    for (u32 i = 35u; i < CORE_APP_NET_EVENT_SIZE; ++i)
        if (p[i] != 0u) return false;
    out->type = (u32)net_get(p, 4u);
    out->reason = (u32)net_get(p + 4, 4u);
    out->connection_key = net_get(p + 8, 8u);
    out->correlation_id = net_get(p + 16, 8u);
    out->payload_size = net_get(p + 24, 8u);
    out->message_id = (u16)net_get(p + 32, 2u);
    out->queued = p[34] == 1u;
    return true;
}

BreakRuntimeError core_app_net_transport_attach_bus(CoreAppNetTransport *transport,
                                                    BreakRuntimeBus *bus) {
    if (!transport) return BREAK_RUNTIME_INVALID;
    if (transport->started || transport->reactor) return BREAK_RUNTIME_REJECTED;
    if (bus) {
        const BreakRuntimeError registered = break_runtime_bus_register_kind(bus, &k_net_event_kind);
        if (registered == BREAK_RUNTIME_INVALID &&
            break_runtime_bus_kind_matches(bus, &k_net_event_kind) != BREAK_RUNTIME_OK) {
            return BREAK_RUNTIME_REJECTED;
        }
        if (registered != BREAK_RUNTIME_OK && registered != BREAK_RUNTIME_INVALID) return registered;
    }
    transport->bus = bus;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_net_transport_event_stats(CoreAppNetTransport *transport,
                                                     CoreAppNetEventStats *out) {
    if (!transport || !out) return BREAK_RUNTIME_INVALID;
    out->published = transport->events_published;
    out->undelivered = transport->events_undelivered;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError net_destroy(void *user);

static BreakRuntimeError net_start(void *user, FILE *trace) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    if (!t || t->started || t->reactor) return BREAK_RUNTIME_INVALID;
    BreakNetReactorConfig reactor_config;
    BreakSessionConfig session_config;
    BreakNetTlsConfig tls;
    SnowEndpoint *endpoint = NULL;
    SnowStatus status = SNOW_OK;
    const char *stage = "psk";
    t->trace = trace;
    if (!core_app_net_take_secret_env(t->psk_env, t->psk, sizeof(t->psk))) goto fail;
    stage = "reactor";
    memset(&reactor_config, 0, sizeof(reactor_config));
    reactor_config.drive_mode = BREAK_NET_DRIVE_STEP;
    reactor_config.max_connections = CORE_APP_NET_MAX_CONNECTIONS;
    t->reactor = break_net_reactor_create(&reactor_config);
    if (t->reactor && t->bus && !break_net_reactor_set_event_hook(t->reactor, net_on_reactor_event, t))
        goto fail;
    memset(&session_config, 0, sizeof(session_config));
    session_config.max_sessions = CORE_APP_NET_MAX_CONNECTIONS;
    session_config.first_session_id = 1u;
    t->manager = t->reactor ? break_session_manager_create(&session_config) : NULL;
    if (!t->manager || !break_session_manager_attach_reactor(t->manager, t->reactor) ||
        !break_session_manager_set_message_handler(t->manager, CORE_APP_SNAPSHOT_MESSAGE_ID,
                                                   net_on_snapshot, t) ||
        !break_session_manager_set_message_handler(
            t->manager, BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, net_on_physics_report, t) ||
        !break_session_manager_set_message_handler(t->manager, CORE_APP_CLOCK_PROBE_MESSAGE_ID,
                                                   net_on_clock_probe, t) ||
        !break_session_manager_set_message_handler(t->manager, BREAK_NET_MESSAGE_ID_CORE_VOICE,
                                                   net_on_voice, t) ||
        !break_session_manager_set_message_handler(
            t->manager, BREAK_NET_MESSAGE_ID_CORE_VOICE_MUTE, net_on_voice_mute, t)) {
        goto fail;
    }
    stage = "aspect";
    if (t->aspect_replication &&
        (!net_aspect_create(t) ||
         !break_session_manager_set_message_handler(
             t->manager, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT,
             break_replication_session_handle_message,
             break_aspect_session_bridge(t->aspect_session)))) {
        goto fail;
    }
    stage = "world";
    if (t->world_replication && (!net_world_create(t) || !net_world_register_handlers(t))) {
        goto fail;
    }
    stage = "bind";
    if (SnowEndpointCreate(&endpoint) != SNOW_OK) goto fail;
    status = SnowEndpointSetHost(endpoint, t->host);
    if (status == SNOW_OK) status = SnowEndpointSetPort(endpoint, (int)t->port);
    if (status == SNOW_OK) status = SnowAcceptorCreate(endpoint, &t->acceptor);
    SnowEndpointDestroy(endpoint);
    if (status != SNOW_OK || SnowAcceptorBind(t->acceptor, 8) != SNOW_OK) goto fail;
    stage = "tls";
    memset(&tls, 0, sizeof(tls));
    tls.cert_file = t->tls_cert;
    tls.key_file = t->tls_key;
    if (!break_net_reactor_set_tls(t->reactor, &tls)) goto fail;
    stage = "acceptor";
    if (!break_net_reactor_set_acceptor(t->reactor, t->acceptor)) goto fail;
    stage = "auth";
    if (!break_session_set_auth(net_auth_key, t)) goto fail;
    t->auth_installed = true;
    stage = "listen";
    if (!break_net_reactor_start(t->reactor)) goto fail;
    stage = "port_file";
    if (net_write_port_file(t, (u16)SnowEndpointPort(SnowAcceptorEndpoint(t->acceptor))) !=
        BREAK_RUNTIME_OK) {
        goto fail;
    }
    t->started = true;
    t->listening = true;
    t->admission_open = true;
    t->producing = true;
    net_trace(t, "COREAPPTRACE version=1 event=network result=listening tls=1 auth=v2\n");
    return BREAK_RUNTIME_OK;
fail:
    {
        char line[128];
        snprintf(line, sizeof(line),
                 "COREAPPTRACE version=1 event=network result=rejected stage=%s\n", stage);
        net_trace(t, line);
    }
    (void)net_destroy(t);
    return BREAK_RUNTIME_FAILED;
}

static void net_tick(void *user, u32 tick, u64 level_generation,
                     const CoreAppSnapshotEntity *entities, u32 entity_count, u64 physics_hash) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    if (!t || !t->started) return;
    t->live_generation = level_generation;
    t->current_tick = tick;
    if (t->world_replication && !t->world_level_initialized &&
        !net_world_initialize_level(t, level_generation)) {
        t->world_stats.terminal_errors++;
    }
    if (t->producing) {
        net_aspect_update(t, entities, entity_count);
        net_world_update(t, entities, entity_count);
        /* A level reload may restart ticks; start a fresh history then. */
        if (!physics_sync_record(&t->physics, tick, physics_hash)) {
            physics_sync_init(&t->physics);
            t->physics_desync_traced = false;
            (void)physics_sync_record(&t->physics, tick, physics_hash);
        }
        t->physics_report_pending = physics_sync_encode_report(
            tick, physics_hash, t->physics_report, sizeof(t->physics_report));
        CoreAppSnapshot *snapshot = &t->scratch_snapshot;
        if (core_app_snapshot_build(snapshot, tick, level_generation,
                                    core_app_snapshot_schema_hash(), entities,
                                    entity_count) == CORE_APP_SNAPSHOT_OK &&
            core_app_snapshot_outbox_push(&t->outbox, snapshot) == CORE_APP_SNAPSHOT_OVER_LIMIT) {
            t->stats.outbox_overloads++;
        }
    }
    u32 budget = CORE_APP_NET_EVENTS_PER_TICK;
    net_pump(t, (int)t->poll_ms, &budget, tick);
    const u64 now_ms = time_microseconds() / 1000u;
    net_aspect_tick_drain(t, now_ms);
    net_world_tick_drain(t, now_ms);
    if (t->producing && break_net_reactor_event_queue_empty(t->reactor)) {
        for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
            if (t->world_open[i] && net_slot_sendable(t, i)) {
                (void)net_world_publish_slot(t, i);
            }
        }
    }
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        net_voice_play(t, i, now_ms, CORE_APP_NET_VOICE_POPS_PER_TICK);
    }
    net_send_pending(t);
}

static BreakRuntimeError net_stop_admission(void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    if (!t) return BREAK_RUNTIME_INVALID;
    t->admission_open = false;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError net_stop_producers(void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    if (!t) return BREAK_RUNTIME_INVALID;
    t->producing = false;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError net_drain(void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    if (!t) return BREAK_RUNTIME_INVALID;
    if (!t->started) return BREAK_RUNTIME_OK;
    net_send_pending(t);
    net_aspect_tick_drain(t, time_microseconds() / 1000u);
    net_world_tick_drain(t, time_microseconds() / 1000u);
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->keys[i] != 0u) net_close_slot(t, i);
    }
    for (u32 round = 0u; round < 8u; ++round) {
        u32 budget = CORE_APP_NET_EVENTS_PER_TICK;
        net_pump(t, CORE_APP_NET_DRAIN_STEP_MS, &budget, t->current_tick);
        net_aspect_tick_drain(t, time_microseconds() / 1000u);
        net_world_tick_drain(t, time_microseconds() / 1000u);
        bool open = false;
        for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) open = open || t->keys[i] != 0u;
        if (!open && break_net_reactor_event_queue_empty(t->reactor)) break;
    }
    return BREAK_RUNTIME_OK;
}

static void net_trace_aspect_stats(CoreAppNetTransport *t) {
    BreakAspectSessionStats aspect;
    char line[512];
    if (!t->aspect_replication || !t->aspect_session) return;
    break_aspect_session_stats(t->aspect_session, &aspect);
    snprintf(line, sizeof(line),
             "COREAPPTRACE version=1 event=network_aspect_stats opened=%" PRIu64
             " closed=%" PRIu64 " applied=%zu rejected=%zu drained=%zu"
             " sent_fragments=%" PRIu64 " queue_depth=%zu dropped=%" PRIu64
             " duplicates=%" PRIu64 " pending_bytes=%zu\n",
             t->aspect_stats.opened, t->aspect_stats.closed, aspect.applied_packets,
             aspect.rejected_packets, aspect.drained_packets, t->aspect_stats.sent_fragments,
             aspect.bridge.completion_count, aspect.bridge.dropped_completions,
             aspect.bridge.duplicate_fragments, aspect.bridge.pending_bytes);
    net_trace(t, line);
}

static void net_trace_world_stats(CoreAppNetTransport *t) {
    BreakWorldSessionStats world;
    char line[512];
    if (!t->world_replication || !t->world_session) return;
    break_world_session_stats(t->world_session, &world);
    snprintf(line, sizeof(line),
             "COREAPPTRACE version=1 event=network_world_stats opened=%" PRIu64
             " closed=%" PRIu64 " applied=%zu need_full=%zu rejected=%zu"
             " full_publishes=%zu delta_publishes=%zu sent_fragments=%" PRIu64
             " queue_depth=%zu dropped=%" PRIu64 "\n",
             t->world_stats.opened, t->world_stats.closed, world.applied_packets,
             world.need_full_packets, world.rejected_packets, world.published_full_packets,
             world.published_delta_packets, t->world_stats.sent_fragments,
             world.bridge.completion_count,
             t->world_stats.terminal_errors + world.bridge.dropped_completions);
    net_trace(t, line);
}

static void net_trace_stats(CoreAppNetTransport *t) {
    BreakSessionApplyStats session;
    memset(&session, 0, sizeof(session));
    if (t->manager) break_session_manager_apply_stats(t->manager, &session);
    char line[1536];
    snprintf(line, sizeof(line),
             "COREAPPTRACE version=1 event=network_stats opened=%" PRIu64 " closed=%" PRIu64
             " refused=%" PRIu64 " authenticated=%" PRIu64 " snapshots_sent=%" PRIu64
             " send_overloads=%" PRIu64 " send_closed=%" PRIu64 " outbox_overloads=%" PRIu64
             " auth_timeouts=%" PRIu64 " decode_failed=%" PRIu64
             " admitted=%" PRIu64 " rejected_unknown=%" PRIu64
             " rejected_unauthenticated=%" PRIu64 " rejected_schema=%" PRIu64
             " rejected_stale=%" PRIu64 " session_applied=%" PRIu64
             " session_phase_rejected=%" PRIu64 " session_invalid=%" PRIu64
             " session_handler_failed=%" PRIu64 " physics_reports_sent=%" PRIu64
             " physics_matched=%" PRIu64 " physics_desynced=%" PRIu64
             " physics_unknown=%" PRIu64 " physics_decode_failed=%" PRIu64
             " physics_corrections_sent=%" PRIu64 " clock_probes_answered=%" PRIu64
             " clock_probe_decode_failed=%" PRIu64 " clock_probes_sent=%" PRIu64
             " clock_replies_matched=%" PRIu64 " clock_replies_unmatched=%" PRIu64
             " clock_probes_lost=%" PRIu64 " clock_samples_rejected=%" PRIu64
             " physics_delta_corrections_sent=%" PRIu64 " session_welcomes_sent=%" PRIu64
             " voice_frames_sent=%" PRIu64 " voice_frames_skipped=%" PRIu64
             " voice_frames_invalid=%" PRIu64 " voice_frames_received=%" PRIu64
             " voice_frames_played=%" PRIu64 " voice_frames_concealed=%" PRIu64
             " voice_frames_dropped=%" PRIu64 " voice_peak=%" PRIu64
             " voice_frames_relayed=%" PRIu64 " voice_relay_dropped=%" PRIu64
             " voice_mute_requests=%" PRIu64 " voice_mute_rejected=%" PRIu64
             " voice_frames_muted=%" PRIu64 " voice_frames_rate_limited=%" PRIu64 "\n",
             t->stats.opened, t->stats.closed, t->stats.refused, t->stats.authenticated,
             t->stats.snapshots_sent, t->stats.send_overloads, t->stats.send_closed,
             t->stats.outbox_overloads, t->stats.auth_timeouts, t->stats.decode_failed, t->inbox.accepted_snapshots,
             t->inbox.rejected_unknown_message, t->inbox.rejected_unauthenticated,
             t->inbox.rejected_schema, t->inbox.rejected_stale_level, (u64)session.applied,
             (u64)session.phase_rejected, (u64)session.invalid, (u64)session.handler_failed,
             t->stats.physics_reports_sent, t->stats.physics_matched,
             t->stats.physics_desynced, t->stats.physics_unknown,
             t->stats.physics_decode_failed, t->stats.physics_corrections_sent,
             t->stats.clock_probes_answered, t->stats.clock_probe_decode_failed,
             t->stats.clock_probes_sent, t->stats.clock_replies_matched,
             t->stats.clock_replies_unmatched, t->stats.clock_probes_lost,
             t->stats.clock_samples_rejected, t->stats.physics_delta_corrections_sent,
             t->stats.session_welcomes_sent, t->stats.voice_frames_sent,
             t->stats.voice_frames_skipped, t->stats.voice_frames_invalid,
             t->stats.voice_frames_received, t->stats.voice_frames_played,
             t->stats.voice_frames_concealed, t->stats.voice_frames_dropped,
             t->stats.voice_peak, t->stats.voice_frames_relayed,
             t->stats.voice_relay_dropped, t->stats.voice_mute_requests,
             t->stats.voice_mute_rejected, t->stats.voice_frames_muted,
             t->stats.voice_frames_rate_limited);
    net_trace(t, line);
    net_trace_aspect_stats(t);
    net_trace_world_stats(t);
    if (t->bus) {
        snprintf(line, sizeof(line),
                 "COREAPPTRACE version=1 event=network_bus net_events_published=%" PRIu64
                 " net_events_undelivered=%" PRIu64 "\n",
                 t->events_published, t->events_undelivered);
        net_trace(t, line);
    }
}

/* Idempotent. The reactor is stopped whenever it exists, whatever state a
 * failed start left it in: break_net_reactor_destroy is a no-op on a
 * started reactor, and the acceptor must not die while a live reactor still
 * holds it. If the stop fails, both are kept (leaked on purpose), the
 * result says so, and every later call returns TIMEOUT without touching
 * them again. */
static BreakRuntimeError net_destroy(void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (!t) return BREAK_RUNTIME_INVALID;
    if (t->leaked) return BREAK_RUNTIME_TIMEOUT;
    net_voice_release_all(t);
    net_aspect_close_all(t);
    net_world_close_all(t);
    t->stats.voice_relay_dropped += t->relay_count;
    t->relay_count = 0u;
    if (t->listening) net_trace_stats(t);
    t->listening = false;
    t->started = false;
    t->admission_open = false;
    t->producing = false;
    bool reactor_stopped = !t->reactor || break_net_reactor_stop(t->reactor, 1000u);
    if (t->manager) break_session_manager_destroy(t->manager);
    t->manager = NULL;
    net_aspect_destroy(t);
    net_world_destroy(t);
    if (reactor_stopped) {
        if (t->reactor) break_net_reactor_destroy(t->reactor);
        if (t->acceptor) SnowAcceptorDestroy(t->acceptor);
        t->acceptor = NULL;
        t->reactor = NULL;
    } else {
        net_trace(t, "COREAPPTRACE version=1 event=network result=stop_timeout\n");
        t->leaked = true;
        result = BREAK_RUNTIME_TIMEOUT;
    }
    if (t->auth_installed) {
        if (break_session_set_auth(NULL, NULL)) {
            t->auth_installed = false;
        } else {
            /* The global auth hook still points at t; keep the PSK readable
             * only through it and report the failure. */
            result = BREAK_RUNTIME_FAILED;
        }
    }
    if (t->port_file_written) {
        (void)remove(t->port_file);
        t->port_file_written = false;
    }
    memset(t->keys, 0, sizeof(t->keys));
    memset(t->authenticated, 0, sizeof(t->authenticated));
    memset(t->welcomed, 0, sizeof(t->welcomed));
    memset(t->closing, 0, sizeof(t->closing));
    memset(t->session_ids, 0, sizeof(t->session_ids));
    net_release_baselines(t);
    if (!t->auth_installed) net_wipe(t->psk, sizeof(t->psk));
    t->trace = NULL;
    return result;
}

CoreAppNetTransport *core_app_net_transport_create(const CoreAppNetTransportConfig *config) {
    if (!config) return NULL;
    CoreAppNetTransport *t = (CoreAppNetTransport *)calloc(1u, sizeof(*t));
    if (!t) return NULL;
    if (!core_app_net_parse_bind(config->bind, t->host, sizeof(t->host), &t->port) ||
        !net_copy(t->tls_cert, sizeof(t->tls_cert), config->tls_cert) ||
        !net_copy(t->tls_key, sizeof(t->tls_key), config->tls_key) ||
        !net_copy(t->psk_env, sizeof(t->psk_env), config->psk_env) ||
        !net_copy(t->port_file, sizeof(t->port_file), config->port_file) ||
        config->poll_ms > CORE_APP_NET_MAX_POLL_MS) {
        free(t);
        return NULL;
    }
    core_app_snapshot_inbox_init(&t->inbox, false, CORE_APP_SNAPSHOT_MESSAGE_ID,
                                 core_app_snapshot_schema_hash());
    core_app_snapshot_outbox_init(&t->outbox);
    physics_sync_init(&t->physics);
    t->poll_ms = config->poll_ms;
    t->voice_relay = config->voice_relay;
    t->aspect_replication = config->aspect_replication;
    t->world_replication = config->world_replication;
    return t;
}

/* A failed destroy leaves a running reactor or the global auth hook
 * pointing at the transport, so the memory is leaked on purpose instead
 * of freed under them. */
void core_app_net_transport_free(CoreAppNetTransport *transport) {
    if (!transport) return;
    if (net_destroy(transport) != BREAK_RUNTIME_OK) return;
    free(transport);
}

#ifdef CORE_APP_NET_TRANSPORT_TESTING
bool core_app_net_transport_aspect_for_test(CoreAppNetTransport *transport,
                                            CoreAppNetAspectTestView *out) {
    if (!out) return false;
    memset(out, 0, sizeof(*out));
    if (!transport) return false;
    out->enabled = transport->aspect_replication;
    out->authoritative = transport->aspect_authoritative;
    out->inbound = transport->aspect_inbound;
    out->spatial_index = transport->aspect_index;
    out->replication = transport->aspect_replication_state;
    out->session = transport->aspect_session;
    out->created = out->authoritative && out->inbound && out->spatial_index &&
                   out->replication && out->session;
    memcpy(out->objects, transport->aspect_objects, sizeof(out->objects));
    out->opened = transport->aspect_stats.opened;
    out->closed = transport->aspect_stats.closed;
    out->sent_fragments = transport->aspect_stats.sent_fragments;
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (transport->aspect_open[i]) out->open_count++;
        out->scope_count += transport->aspect_scopes[i].count;
    }
    return true;
}

BreakRuntimeError core_app_net_transport_aspect_sync_for_test(CoreAppNetTransport *transport,
                                                              u64 key) {
    int slot;
    if (!transport || !transport->aspect_replication || !transport->aspect_session)
        return BREAK_RUNTIME_INVALID;
    slot = net_slot_find(transport, key);
    if (slot < 0 || !transport->aspect_open[slot]) return BREAK_RUNTIME_CLOSED;
    return net_aspect_sync_slot(transport, (u32)slot);
}

bool core_app_net_transport_world_for_test(CoreAppNetTransport *transport,
                                           CoreAppNetWorldTestView *out) {
    if (!out) return false;
    memset(out, 0, sizeof(*out));
    if (!transport) return false;
    out->enabled = transport->world_replication;
    out->schemas = transport->world_schemas;
    out->authoritative = transport->world_authoritative;
    out->diagnostic = transport->world_diagnostic;
    out->session = transport->world_session;
    out->created = out->schemas && out->authoritative && out->diagnostic && out->session;
    memcpy(out->objects, transport->world_objects, sizeof(out->objects));
    out->level_generation = transport->world_level_generation;
    out->opened = transport->world_stats.opened;
    out->closed = transport->world_stats.closed;
    out->sent_fragments = transport->world_stats.sent_fragments;
    out->terminal_errors = transport->world_stats.terminal_errors;
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (transport->world_open[i]) out->open_count++;
    }
    return true;
}

BreakNetSendResult core_app_net_transport_world_publish_for_test(CoreAppNetTransport *transport,
                                                                 u64 key) {
    int slot;
    if (!transport || !transport->world_replication || !transport->world_session) {
        return BREAK_NET_SEND_INVALID;
    }
    slot = net_slot_find(transport, key);
    if (slot < 0) return BREAK_NET_SEND_CLOSED;
    return net_world_publish_slot(transport, (u32)slot);
}

bool core_app_net_transport_world_control_for_test(CoreAppNetTransport *transport, u64 key,
                                                   const BreakNetOwnedMessage *message) {
    if (!transport || !transport->world_replication || !transport->world_session) return false;
    return net_world_on_control(key, message, transport);
}

BreakNetReactor *core_app_net_transport_reactor_for_test(CoreAppNetTransport *transport) {
    return transport ? transport->reactor : NULL;
}

bool core_app_net_transport_reclaim_for_test(CoreAppNetTransport *transport) {
    if (!transport) return false;
    if (transport->reactor && !break_net_reactor_stop(transport->reactor, 1000u)) return false;
    if (transport->reactor) break_net_reactor_destroy(transport->reactor);
    if (transport->acceptor) SnowAcceptorDestroy(transport->acceptor);
    net_aspect_destroy(transport);
    net_world_destroy(transport);
    net_release_baselines(transport);
    free(transport);
    return true;
}
#endif

/* True while an authenticated peer that reported a desync still waits for
 * a correction. */
static bool net_physics_correction_wanted(void *user) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    if (!t || !t->started || !t->producing) return false;
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->correction_pending[i] && net_slot_sendable(t, i)) return true;
    }
    return false;
}

/* Sends one correction to every waiting peer. Several desync reports before
 * the next tick collapse into this single correction. A peer that confirmed
 * the snapshot of its previous correction gets a delta against it when that
 * is smaller; the sent snapshot becomes its new, unconfirmed baseline. */
static void net_physics_correction(void *user, u32 tick, const u8 *data, usize size) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    const u8 *snapshot = NULL;
    usize snapshot_size = 0u;
    if (!t || !t->started || !data || size > BREAK_NET_MAX_PAYLOAD_SIZE) return;
    if (!break_net_reactor_event_queue_empty(t->reactor)) return;
    if (!physics_sync_correction_payload(data, size, &snapshot, &snapshot_size)) return;
    u8 *packet = (u8 *)malloc(size);
    if (!packet) return;
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (!t->correction_pending[i] || !net_slot_sendable(t, i)) continue;
        usize packet_size = 0u;
        bool delta = false;
        if (!physics_sync_baseline_encode(&t->physics_baselines[i], tick, snapshot, snapshot_size,
                                          packet, size, &packet_size, &delta)) {
            continue;
        }
        BreakNetSendResult sent =
            break_net_reactor_send(t->reactor, t->keys[i],
                                   BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_CORRECTION, 1u, packet,
                                   packet_size);
        if (sent == BREAK_NET_SEND_OK) {
            t->stats.physics_corrections_sent++;
            if (delta) t->stats.physics_delta_corrections_sent++;
            t->correction_pending[i] = false;
            (void)physics_sync_baseline_store(&t->physics_baselines[i], tick, snapshot,
                                              snapshot_size);
        } else if (sent == BREAK_NET_SEND_OVERLOAD) {
            t->stats.send_overloads++;
        } else {
            t->stats.send_closed++;
            t->correction_pending[i] = false;
        }
    }
    free(packet);
}

/* Encodes one voice frame as BRV2 and sends it to every welcomed peer, now
 * or never: a frame that cannot go out (producers stopped, events pending,
 * overload) is dropped, because a late voice frame is useless. A frame that
 * does not encode is a defect upstream and is counted as invalid. */
static void net_voice_frame(void *user, const BreakVoiceFrame *frame) {
    CoreAppNetTransport *t = (CoreAppNetTransport *)user;
    if (!t) return;
    if (!frame) {
        t->stats.voice_frames_invalid++;
        return;
    }
    if (!t->started || !t->producing || !break_net_reactor_event_queue_empty(t->reactor)) {
        t->stats.voice_frames_skipped++;
        return;
    }
    u8 wire[BREAK_NET_CORE_VOICE_MAX_PAYLOAD] = {0};
    u32 size = 0u;
    if (break_voice_encode_adpcm(frame, wire, (u32)sizeof(wire), &size) != BREAK_RUNTIME_OK) {
        t->stats.voice_frames_invalid++;
        return;
    }
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (!net_slot_sendable(t, i)) continue;
        BreakNetSendResult sent = break_net_reactor_send(
            t->reactor, t->keys[i], BREAK_NET_MESSAGE_ID_CORE_VOICE, 1u, wire, size);
        if (sent == BREAK_NET_SEND_OK) t->stats.voice_frames_sent++;
        else if (sent == BREAK_NET_SEND_OVERLOAD) t->stats.send_overloads++;
        else t->stats.send_closed++;
    }
}

static BreakRuntimeError net_attach_bus(void *user, BreakRuntimeBus *bus) {
    return core_app_net_transport_attach_bus((CoreAppNetTransport *)user, bus);
}

void core_app_net_transport_hooks(CoreAppNetTransport *transport, CoreAppNetworkHooks *out) {
    if (!out) return;
    memset(out, 0, sizeof(*out));
    if (!transport) return;
    out->user = transport;
    out->start = net_start;
    out->tick = net_tick;
    out->stop_admission = net_stop_admission;
    out->stop_producers = net_stop_producers;
    out->drain = net_drain;
    out->destroy = net_destroy;
    out->physics_correction_wanted = net_physics_correction_wanted;
    out->physics_correction = net_physics_correction;
    out->voice_frame = net_voice_frame;
    out->attach_bus = net_attach_bus;
}
