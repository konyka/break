#include "core_app_net_transport.h"

#include <network/break_net_adapter.h>
#include <network/break_net_events.h>
#include <network/break_net_message_registry.h>
#include <network/break_session.h>
#include <physics/physics_sync.h>
#include <platform/platform_fs.h>
#include <platform/time.h>
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
_Static_assert(CORE_APP_SNAPSHOT_MAX_BYTES == BREAK_NET_CORE_SNAPSHOT_MAX_PAYLOAD,
               "core_app snapshot size must match the registry payload limit");
_Static_assert(PHYSICS_SYNC_REPORT_BYTES == BREAK_NET_PHYSICS_SYNC_REPORT_PAYLOAD,
               "physics report size must match the registry payload limit");

#define CORE_APP_NET_MAX_CONNECTIONS 8u
#define CORE_APP_NET_EVENTS_PER_TICK 64u
#define CORE_APP_NET_DRAIN_STEP_MS 1
#define CORE_APP_NET_MAX_POLL_MS 100u
/* A connection that has not authenticated this long after it opened is
 * closed, so idle TLS peers cannot hold every slot. Measured on the
 * monotonic clock: the tick rate depends on --net-poll-ms and on whether
 * the output paces frames, so a tick count is no deadline a peer can meet. */
#define CORE_APP_NET_AUTH_DEADLINE_MS 3000u
#define CORE_APP_NET_PATH_CAPACITY 512u

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
} CoreAppNetStats;

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
    bool closing[CORE_APP_NET_MAX_CONNECTIONS];
    BreakSessionId session_ids[CORE_APP_NET_MAX_CONNECTIONS];
    u64 opened_us[CORE_APP_NET_MAX_CONNECTIONS];
    CoreAppSnapshot scratch_snapshot;
    u8 scratch_wire[CORE_APP_SNAPSHOT_MAX_BYTES];
    CoreAppSnapshotInbox inbox;
    CoreAppSnapshotOutbox outbox;
    PhysicsSyncTracker physics;
    u8 physics_report[PHYSICS_SYNC_REPORT_BYTES];
    bool physics_report_pending;
    bool physics_desync_traced;
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
        fputs(text, t->trace);
        fflush(t->trace);
    }
}

static int net_slot_find(const CoreAppNetTransport *t, BreakConnectionKey key) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->keys[i] == key && key != 0u) return (int)i;
    }
    return -1;
}

static int net_slot_add(CoreAppNetTransport *t, BreakConnectionKey key) {
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->keys[i] == 0u) {
            t->keys[i] = key;
            t->authenticated[i] = false;
            t->closing[i] = false;
            t->session_ids[i] = 0u;
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
    (void)connection;
    if (!physics_sync_decode_report((const u8 *)message->data, message->size, &tick, &hash)) {
        t->stats.physics_decode_failed++;
        return false;
    }
    PhysicsSyncVerdict verdict = physics_sync_check(&t->physics, tick, hash);
    if (verdict == PHYSICS_SYNC_MATCH) {
        t->stats.physics_matched++;
    } else if (verdict == PHYSICS_SYNC_DESYNC) {
        t->stats.physics_desynced++;
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

static void net_close_slot(CoreAppNetTransport *t, u32 i) {
    t->authenticated[i] = false;
    if (t->closing[i]) return;
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
                     " tick=%u\n", tick);
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
            if (!t->admission_open || net_slot_find(t, event.connection_key) >= 0 ||
                net_slot_add(t, event.connection_key) < 0) {
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
                t->keys[slot] = 0u;
                t->authenticated[slot] = false;
                t->closing[slot] = false;
                t->session_ids[slot] = 0u;
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
static bool net_slot_sendable(const CoreAppNetTransport *t, u32 i) {
    BreakConnectionKey key = t->keys[i];
    return key != 0u && t->authenticated[i] && !t->closing[i] &&
           break_session_manager_state(t->manager, key) == BREAK_SESSION_AUTHENTICATED &&
           break_session_manager_session_id(t->manager, key) == t->session_ids[i];
}

static void net_send_pending(CoreAppNetTransport *t) {
    CoreAppSnapshot *snapshot = &t->scratch_snapshot;
    u8 *wire = t->scratch_wire;
    /* Unprocessed events may include a close for a key that a new
     * connection already reuses; hold snapshots until the queue is empty. */
    if (!break_net_reactor_event_queue_empty(t->reactor)) return;
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
    memset(&session_config, 0, sizeof(session_config));
    session_config.max_sessions = CORE_APP_NET_MAX_CONNECTIONS;
    session_config.first_session_id = 1u;
    t->manager = t->reactor ? break_session_manager_create(&session_config) : NULL;
    if (!t->manager || !break_session_manager_attach_reactor(t->manager, t->reactor) ||
        !break_session_manager_set_message_handler(t->manager, CORE_APP_SNAPSHOT_MESSAGE_ID,
                                                   net_on_snapshot, t) ||
        !break_session_manager_set_message_handler(
            t->manager, BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, net_on_physics_report, t)) {
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
    if (t->producing) {
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
    for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) {
        if (t->keys[i] != 0u) net_close_slot(t, i);
    }
    for (u32 round = 0u; round < 8u; ++round) {
        u32 budget = CORE_APP_NET_EVENTS_PER_TICK;
        net_pump(t, CORE_APP_NET_DRAIN_STEP_MS, &budget, t->current_tick);
        bool open = false;
        for (u32 i = 0u; i < CORE_APP_NET_MAX_CONNECTIONS; ++i) open = open || t->keys[i] != 0u;
        if (!open && break_net_reactor_event_queue_empty(t->reactor)) break;
    }
    return BREAK_RUNTIME_OK;
}

static void net_trace_stats(CoreAppNetTransport *t) {
    BreakSessionApplyStats session;
    memset(&session, 0, sizeof(session));
    if (t->manager) break_session_manager_apply_stats(t->manager, &session);
    char line[1024];
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
             " physics_unknown=%" PRIu64 " physics_decode_failed=%" PRIu64 "\n",
             t->stats.opened, t->stats.closed, t->stats.refused, t->stats.authenticated,
             t->stats.snapshots_sent, t->stats.send_overloads, t->stats.send_closed,
             t->stats.outbox_overloads, t->stats.auth_timeouts, t->stats.decode_failed, t->inbox.accepted_snapshots,
             t->inbox.rejected_unknown_message, t->inbox.rejected_unauthenticated,
             t->inbox.rejected_schema, t->inbox.rejected_stale_level, (u64)session.applied,
             (u64)session.phase_rejected, (u64)session.invalid, (u64)session.handler_failed,
             t->stats.physics_reports_sent, t->stats.physics_matched,
             t->stats.physics_desynced, t->stats.physics_unknown,
             t->stats.physics_decode_failed);
    net_trace(t, line);
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
    if (t->listening) net_trace_stats(t);
    t->listening = false;
    t->started = false;
    t->admission_open = false;
    t->producing = false;
    bool reactor_stopped = !t->reactor || break_net_reactor_stop(t->reactor, 1000u);
    if (t->manager) break_session_manager_destroy(t->manager);
    t->manager = NULL;
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
    memset(t->closing, 0, sizeof(t->closing));
    memset(t->session_ids, 0, sizeof(t->session_ids));
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
BreakNetReactor *core_app_net_transport_reactor_for_test(CoreAppNetTransport *transport) {
    return transport ? transport->reactor : NULL;
}

bool core_app_net_transport_reclaim_for_test(CoreAppNetTransport *transport) {
    if (!transport) return false;
    if (transport->reactor && !break_net_reactor_stop(transport->reactor, 1000u)) return false;
    if (transport->reactor) break_net_reactor_destroy(transport->reactor);
    if (transport->acceptor) SnowAcceptorDestroy(transport->acceptor);
    free(transport);
    return true;
}
#endif

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
}
