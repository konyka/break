/* Loopback peer for test_core_app_network_loopback, _late_auth and _voice.
 *
 * Runs next to a real core_app started with --network. Every check here is
 * about the wire: TLS, AUTH-v2, which connections receive snapshots, and
 * which hostile inputs close a connection. Whether hostile input changed
 * the simulation is checked by the CMake driver, which compares the
 * networked trace with an offline run of the same scenario. "late-auth"
 * runs only the delayed-AUTH peer; "single" runs one connection only, so a
 * --trace document names exactly one session; "voice" runs only the voice
 * peer;
 * "voice-relay" runs the two relay peers; "voice-mute" runs the two mute
 * peers; "voice-flood" runs the two rate-limit peers; "aspect" exchanges
 * BRFG/BRA1 packets with the optional aspect transport; "world" exchanges
 * BRWD/BRWC packets with the optional World transport.
 *
 * Usage: test_core_app_net_client PORT_FILE REPORT_FILE
 *        [late-auth|voice|voice-relay|voice-mute|voice-flood|single|aspect|world]
 *        [--trace PATH]
 * The PSK is read from CORE_APP_TEST_PSK (64 hex digits). With --trace the
 * peer writes its own core_app-format trace: one
 * event=network_session_welcome line per accepted welcome, so trace_merge
 * can read the session from the peer's own document instead of being told
 * it (design 2026-11-20-peer-client-trace). */
#define _POSIX_C_SOURCE 200809L
#include "core_app_network.h"

#include <core/clock_offset.h>
#include <core/trace_core_app.h>
#include <crypto/break_crypto.h>
#include <ecs/world_session.h>
#include <network/break_net_envelope.h>
#include <network/break_net_message_registry.h>
#include <network/break_online_aspect.h>
#include <network/break_online_voice.h>
#include <network/break_replication_wire.h>
#include <physics/physics_sync.h>
#include <snow/network_buffer.h>
#include <snow/openssl.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define NET_CLIENT_FRAME_CAPACITY (BREAK_NET_ENVELOPE_HEADER_SIZE + BREAK_NET_MAX_PAYLOAD_SIZE)

static const u8 k_key_id[8] = {'c', 'o', 'r', 'e', 'a', 'p', 'p', '1'};
static u8 g_psk[32];
static u16 g_port;
static FILE *g_report;
static int g_failures;
/* --trace: the peer's own core_app-format trace, written with the same
 * writer core_app uses so the ts_us stamping is identical. */
static FILE *g_trace;
static u32 g_trace_lines;

typedef struct NetClient {
    int fd;
    SnowSslCtx *ctx;
    SnowSsl *ssl;
    SnowNetworkBuffer *plain;
    u32 next_seq;
    u8 server_nonce[16];
    bool skip_server_probe;
    bool auth_sent;
    u32 welcomes;
    u32 bad_welcomes;
    u32 messages_before_welcome;
    u64 session_id;
} NetClient;

static u64 now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000u + (u64)ts.tv_nsec / 1000000u;
}

static void check(bool ok, const char *what) {
    fprintf(g_report, "check %s %s\n", ok ? "pass" : "FAIL", what);
    fflush(g_report);
    if (!ok) g_failures++;
}

static int hex_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static bool read_psk(void) {
    const char *text = getenv("CORE_APP_TEST_PSK");
    if (!text || strlen(text) != 64u) return false;
    for (u32 i = 0u; i < 32u; ++i) {
        int hi = hex_digit(text[2u * i]);
        int lo = hex_digit(text[2u * i + 1u]);
        if (hi < 0 || lo < 0) return false;
        g_psk[i] = (u8)((hi << 4) | lo);
    }
    return true;
}

static bool wait_port(const char *path) {
    u64 deadline = now_ms() + 30000u;
    while (now_ms() < deadline) {
        FILE *file = fopen(path, "rb");
        if (file) {
            unsigned value = 0u;
            int got = fscanf(file, "%u", &value);
            fclose(file);
            if (got == 1 && value > 0u && value <= 65535u) {
                g_port = (u16)value;
                return true;
            }
        }
        struct timespec pause = {0, 20000000L};
        nanosleep(&pause, NULL);
    }
    return false;
}

static bool client_flush(NetClient *c, SnowNetworkBuffer *out) {
    size_t size = SnowNetworkBufferLength(out);
    size_t copied = 0u, off = 0u;
    if (size == 0u) return true;
    u8 *flat = (u8 *)malloc(size);
    if (!flat || SnowNetworkBufferCopyTo(out, flat, size, &copied) != SNOW_OK ||
        copied != size) {
        free(flat);
        return false;
    }
    SnowNetworkBufferClear(out);
    while (off < size) {
        ssize_t n = write(c->fd, flat + off, size - off);
        if (n <= 0) {
            free(flat);
            return false;
        }
        off += (size_t)n;
    }
    free(flat);
    return true;
}

/* 1 = bytes consumed, 0 = nothing within 5 ms, -1 = closed or TLS error. */
static int client_read_burst(NetClient *c, SnowNetworkBuffer *out, bool handshake) {
    u8 buf[4096];
    struct pollfd pfd = {c->fd, POLLIN, 0};
    if (poll(&pfd, 1, 5) <= 0) return 0;
    ssize_t got = read(c->fd, buf, sizeof(buf));
    if (got <= 0) return -1;
    if (handshake) return SnowSslDoHandshake(c->ssl, out, buf, (size_t)got) == 0 ? 1 : -1;
    return SnowSslRead(c->ssl, buf, (size_t)got, c->plain) == 0 ? 1 : -1;
}

static bool client_send_wire(NetClient *c, const u8 *wire, size_t size) {
    SnowNetworkBuffer *out = NULL;
    if (SnowNetworkBufferCreate(&out) != SNOW_OK) return false;
    bool ok = SnowSslWrite(c->ssl, (const char *)wire, size, out) == 0 && client_flush(c, out);
    SnowNetworkBufferDestroy(out);
    return ok;
}

static bool client_send(NetClient *c, u16 id, u16 version, const u8 *payload, size_t size) {
    BreakNetEnvelope env;
    u8 wire[NET_CLIENT_FRAME_CAPACITY];
    size_t wire_size = 0u;
    memset(&env, 0, sizeof(env));
    env.protocol_version = version;
    env.message_id = id;
    env.sequence = c->next_seq++;
    env.payload = payload;
    env.payload_size = size;
    if (break_net_envelope_encode(&env, wire, sizeof(wire), &wire_size) !=
        BREAK_NET_ENVELOPE_OK) {
        return false;
    }
    return client_send_wire(c, wire, wire_size);
}

/* The envelope encoder refuses ids outside the registry, so an unknown id
 * is framed by hand with the documented 18-byte little-endian header. */
static bool client_send_raw_id(NetClient *c, u16 id) {
    u8 wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 4u];
    u32 magic = BREAK_NET_ENVELOPE_MAGIC, seq = c->next_seq++, size = 4u;
    memset(wire, 0, sizeof(wire));
    for (u32 i = 0u; i < 4u; ++i) wire[i] = (u8)(magic >> (8u * i));
    wire[4] = 1u;
    wire[6] = (u8)id;
    wire[7] = (u8)(id >> 8u);
    for (u32 i = 0u; i < 4u; ++i) wire[10u + i] = (u8)(seq >> (8u * i));
    for (u32 i = 0u; i < 4u; ++i) wire[14u + i] = (u8)(size >> (8u * i));
    return client_send_wire(c, wire, sizeof(wire));
}

static u64 now_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000000u + (u64)ts.tv_nsec / 1000u;
}

static u32 g_server_probes_answered;

static bool client_send_clock_reply(NetClient *c, const CoreAppClockProbe *request, u64 t1) {
    CoreAppClockProbe reply;
    u8 wire[CORE_APP_CLOCK_PROBE_BYTES];
    size_t size = 0u;
    return core_app_clock_probe_answer(request, t1, now_us(), &reply) == CORE_APP_SNAPSHOT_OK &&
           core_app_clock_probe_encode(&reply, wire, sizeof(wire), &size) ==
               CORE_APP_SNAPSHOT_OK &&
           client_send(c, CORE_APP_CLOCK_PROBE_MESSAGE_ID, 1u, wire, size);
}

/* Answers a server request with t1 taken at receipt and t2 just before the
 * send. The first request also gets a reply with a far-future t0 before
 * the real one and a duplicate after it; the server must count both as
 * unmatched and never turn them into samples. */
static bool client_answer_server_probe(NetClient *c, const CoreAppClockProbe *request, u64 t1) {
    /* One request is left unanswered on purpose: the server must time it
     * out and keep probing this peer. */
    if (c->skip_server_probe) {
        c->skip_server_probe = false;
        return true;
    }
    if (g_server_probes_answered == 0u) {
        CoreAppClockProbe wrong = *request;
        wrong.t0 += 1000000000000ull;
        if (!client_send_clock_reply(c, &wrong, t1)) return false;
    }
    if (!client_send_clock_reply(c, request, t1)) return false;
    if (g_server_probes_answered == 0u && !client_send_clock_reply(c, request, t1)) return false;
    g_server_probes_answered++;
    return true;
}

/* Reads one envelope into a static frame. Returns 1 on a frame, 0 on
 * timeout, -1 when the server closed the connection. */
static int client_recv(NetClient *c, BreakNetEnvelope *env, u32 timeout_ms) {
    static u8 frame[NET_CLIENT_FRAME_CAPACITY];
    u64 deadline = now_ms() + timeout_ms;
    while (now_ms() < deadline) {
        size_t have = SnowNetworkBufferLength(c->plain);
        if (have >= BREAK_NET_ENVELOPE_HEADER_SIZE) {
            size_t n = 0u;
            if (SnowNetworkBufferGetHeader(c->plain, BREAK_NET_ENVELOPE_HEADER_SIZE, frame,
                                           sizeof(frame), &n) != SNOW_OK) {
                return -1;
            }
            u32 payload = (u32)frame[14] | ((u32)frame[15] << 8u) | ((u32)frame[16] << 16u) |
                          ((u32)frame[17] << 24u);
            size_t need = BREAK_NET_ENVELOPE_HEADER_SIZE + (size_t)payload;
            if (need > sizeof(frame)) return -1;
            if (have >= need) {
                if (SnowNetworkBufferGetHeader(c->plain, need, frame, sizeof(frame), &n) !=
                        SNOW_OK ||
                    n != need || SnowNetworkBufferMoveHeader(c->plain, need) != SNOW_OK) {
                    return -1;
                }
                u64 t1 = now_us();
                if (break_net_envelope_decode(frame, need, env) != BREAK_NET_ENVELOPE_OK) {
                    return -1;
                }
                /* The session welcome is consumed here, whatever the caller
                 * waits for, and must precede every other application
                 * message after AUTH. */
                if (env->message_id == CORE_APP_SESSION_WELCOME_MESSAGE_ID) {
                    u64 id = 0u;
                    if (env->protocol_version != 1u ||
                        core_app_session_welcome_decode((const u8 *)env->payload,
                                                        env->payload_size, &id) !=
                            CORE_APP_SNAPSHOT_OK) {
                        c->bad_welcomes++;
                    } else {
                        if (c->welcomes == 0u) c->session_id = id;
                        c->welcomes++;
                        if (g_trace) {
                            /* names the session trace_merge needs; a
                             * rejected welcome has none to name */
                            if (break_trace_core_app_fprintf(
                                    g_trace,
                                    "COREAPPTRACE version=1"
                                    " event=network_session_welcome session=%llu\n",
                                    (unsigned long long)id) > 0) {
                                g_trace_lines++;
                            }
                            fflush(g_trace);
                        }
                    }
                    continue;
                }
                if (c->auth_sent && c->welcomes == 0u) c->messages_before_welcome++;
                /* Server clock requests are answered here, whatever the
                 * caller waits for, so none is dropped by a helper that
                 * skips other ids. */
                CoreAppClockProbe request;
                if (env->message_id == CORE_APP_CLOCK_PROBE_MESSAGE_ID &&
                    core_app_clock_probe_decode((const u8 *)env->payload, env->payload_size,
                                                &request) == CORE_APP_SNAPSHOT_OK &&
                    request.kind == CORE_APP_CLOCK_PROBE_REQUEST) {
                    if (!client_answer_server_probe(c, &request, t1)) return -1;
                    continue;
                }
                return 1;
            }
        }
        if (client_read_burst(c, NULL, false) < 0) return -1;
    }
    return 0;
}

static void client_close(NetClient *c) {
    if (c->plain) SnowNetworkBufferDestroy(c->plain);
    if (c->ssl) SnowSslFree(c->ssl);
    if (c->ctx) SnowSslCtxFree(c->ctx);
    if (c->fd >= 0) close(c->fd);
    memset(c, 0, sizeof(*c));
    c->fd = -1;
}

/* TCP connect, TLS handshake, then the server CHALLENGE (nonce kept). */
static bool client_open(NetClient *c) {
    struct sockaddr_in address;
    SnowSslCtxOpts opts;
    SnowNetworkBuffer *out = NULL;
    BreakNetEnvelope challenge;
    bool ok = false;
    memset(c, 0, sizeof(*c));
    c->next_seq = 1u;
    c->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (c->fd < 0) return false;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(g_port);
    if (connect(c->fd, (const struct sockaddr *)&address, sizeof(address)) != 0) return false;
    memset(&opts, 0, sizeof(opts));
    c->ctx = SnowSslCtxNew(&opts, NULL);
    c->ssl = c->ctx ? SnowSslNew(c->ctx) : NULL;
    if (!c->ssl || SnowSslInit(c->ssl, false) != SNOW_OK ||
        SnowNetworkBufferCreate(&c->plain) != SNOW_OK ||
        SnowNetworkBufferCreate(&out) != SNOW_OK) {
        goto done;
    }
    if (SnowSslDoHandshake(c->ssl, out, NULL, 0u) != 0 || !client_flush(c, out)) goto done;
    u64 deadline = now_ms() + 10000u;
    while (!SnowSslIsHandshaked(c->ssl) && now_ms() < deadline) {
        if (client_read_burst(c, out, true) < 0 || !client_flush(c, out)) goto done;
    }
    if (!SnowSslIsHandshaked(c->ssl) || client_recv(c, &challenge, 10000u) != 1 ||
        challenge.message_id != BREAK_NET_MESSAGE_ID_CHALLENGE ||
        challenge.protocol_version != 1u || challenge.payload_size != 16u) {
        goto done;
    }
    memcpy(c->server_nonce, challenge.payload, 16u);
    ok = true;
done:
    if (out) SnowNetworkBufferDestroy(out);
    return ok;
}

static bool client_auth(NetClient *c, const u8 psk[32]) {
    u8 payload[56];
    u8 context[40];
    memcpy(payload, k_key_id, 8u);
    for (u32 i = 0u; i < 16u; ++i) payload[8u + i] = (u8)(0x3cu + i);
    memcpy(context, "BRKAUTH2", 8u);
    memcpy(context + 8u, c->server_nonce, 16u);
    memcpy(context + 24u, payload + 8u, 16u);
    if (!break_crypto_hmac_sha256(psk, 32u, context, sizeof(context), payload + 24u)) {
        return false;
    }
    c->auth_sent = true;
    return client_send(c, BREAK_NET_MESSAGE_ID_AUTH, 2u, payload, sizeof(payload));
}

/* Exactly one well-formed welcome, before any other message after AUTH. */
static void check_welcome(const NetClient *c, const char *peer) {
    char what[64];
    snprintf(what, sizeof(what), "%s_session_welcome_first", peer);
    check(c->welcomes == 1u && c->bad_welcomes == 0u && c->messages_before_welcome == 0u &&
              c->session_id != 0u,
          what);
    fprintf(g_report, "session_welcome peer=%s session=%llu welcomes=%u\n", peer,
            (unsigned long long)c->session_id, c->welcomes);
}

/* Waits for the next snapshot; other envelope ids are skipped. */
static int client_next_snapshot(NetClient *c, CoreAppSnapshot *out, u32 timeout_ms) {
    u64 deadline = now_ms() + timeout_ms;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got != 1) return got;
        if (env.message_id != CORE_APP_SNAPSHOT_MESSAGE_ID) continue;
        if (env.protocol_version != CORE_APP_SNAPSHOT_PROTOCOL_VERSION) return -1;
        return core_app_snapshot_decode((const u8 *)env.payload, env.payload_size, out) ==
                       CORE_APP_SNAPSHOT_OK
                   ? 1
                   : -1;
    }
    return 0;
}

/* Waits until the server closes the connection. Fails if a snapshot or a
 * session welcome arrives first, because a rejected peer must never receive
 * one. */
static bool client_closed_without_snapshot(NetClient *c, u32 timeout_ms) {
    u64 deadline = now_ms() + timeout_ms;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (c->welcomes != 0u || c->bad_welcomes != 0u) return false;
        if (got < 0) return true;
        if (got == 1 && (env.message_id == CORE_APP_SNAPSHOT_MESSAGE_ID ||
                         env.message_id == BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT)) {
            return false;
        }
    }
    return false;
}

/* Physics report layout, decoded by hand so the test does not trust
 * physics_sync.c: magic "PSYN" u32, tick u32, hash u64, little-endian. */
#define NET_CLIENT_PHYSICS_REPORT_BYTES 16u
#define NET_CLIENT_PHYSICS_REPORT_MAGIC 0x4e595350u

static u32 le32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8u) | ((u32)p[2] << 16u) | ((u32)p[3] << 24u);
}

static u64 le64(const u8 *p) {
    return (u64)le32(p) | ((u64)le32(p + 4u) << 32u);
}

/* Waits for the next physics report and copies its raw bytes. */
static int client_next_physics_report(NetClient *c, u8 out[NET_CLIENT_PHYSICS_REPORT_BYTES],
                                      u32 timeout_ms) {
    u64 deadline = now_ms() + timeout_ms;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got != 1) return got;
        if (env.message_id != BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT) continue;
        if (env.protocol_version != 1u || env.payload_size != NET_CLIENT_PHYSICS_REPORT_BYTES ||
            le32((const u8 *)env.payload) != NET_CLIENT_PHYSICS_REPORT_MAGIC) {
            return -1;
        }
        memcpy(out, env.payload, NET_CLIENT_PHYSICS_REPORT_BYTES);
        return 1;
    }
    return 0;
}

/* Correction layout, checked by hand: magic "PSNP" u32, tick u32, payload
 * bytes u32, FNV-1a 32 of the payload u32, then the payload. */
#define NET_CLIENT_PHYSICS_CORRECTION_MAGIC 0x504e5350u
#define NET_CLIENT_PHYSICS_CORRECTION_HEADER 16u
/* Delta layout: magic "PSND" u32, tick u32, baseline tick u32, then the
 * rest of a 28-byte header and the runs; physics_sync checks the body. */
#define NET_CLIENT_PHYSICS_DELTA_MAGIC 0x444e5350u
#define NET_CLIENT_PHYSICS_DELTA_HEADER 28u

/* Latest report seen while waiting for a correction, and the correction
 * bytes, kept so the client can restore them into its own world. */
static bool g_report_seen;
static u32 g_report_tick;
static u64 g_report_hash;
static u8 g_correction[BREAK_NET_MAX_PAYLOAD_SIZE];

static int client_next_physics_correction(NetClient *c, u32 *out_tick, size_t *out_bytes,
                                          u32 timeout_ms) {
    u64 deadline = now_ms() + timeout_ms;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got != 1) return got;
        if (env.message_id == BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT &&
            env.payload_size == NET_CLIENT_PHYSICS_REPORT_BYTES) {
            const u8 *r = (const u8 *)env.payload;
            g_report_seen = true;
            g_report_tick = le32(r + 4u);
            g_report_hash = (u64)le32(r + 8u) | ((u64)le32(r + 12u) << 32u);
            continue;
        }
        if (env.message_id != BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_CORRECTION) continue;
        const u8 *p = (const u8 *)env.payload;
        if (env.protocol_version == 1u && env.payload_size >= NET_CLIENT_PHYSICS_DELTA_HEADER &&
            le32(p) == NET_CLIENT_PHYSICS_DELTA_MAGIC) {
            if (env.payload_size > sizeof(g_correction)) return -1;
            memcpy(g_correction, p, env.payload_size);
            *out_tick = le32(p + 4u);
            *out_bytes = env.payload_size;
            return 1;
        }
        if (env.protocol_version != 1u || env.payload_size <= NET_CLIENT_PHYSICS_CORRECTION_HEADER ||
            le32(p) != NET_CLIENT_PHYSICS_CORRECTION_MAGIC ||
            (size_t)le32(p + 8u) != env.payload_size - NET_CLIENT_PHYSICS_CORRECTION_HEADER) {
            return -1;
        }
        u32 h = 2166136261u;
        for (size_t i = NET_CLIENT_PHYSICS_CORRECTION_HEADER; i < env.payload_size; ++i) {
            h ^= p[i];
            h *= 16777619u;
        }
        if (h != le32(p + 12u) || env.payload_size > sizeof(g_correction)) return -1;
        memcpy(g_correction, p, env.payload_size);
        *out_tick = le32(p + 4u);
        *out_bytes = env.payload_size;
        return 1;
    }
    return 0;
}

/* The server sends a correction for tick N right after the report for
 * tick N, so a peer that reads up to a report newer than N has seen every
 * correction it could get. True when a correction arrives first or the
 * connection fails, both wrong for a peer that never desynced. */
/* The client's own world and the snapshot it last restored, which is the
 * baseline a later delta correction is decoded against. */
static PhysicsWorld *g_client_world;
static PhysicsSyncTracker g_client_tracker;
static PhysicsSyncBaseline g_client_held;

/* Restores the received correction (full or delta) into a world of
 * core_app's capacity and checks it reproduces the hash the authority
 * reported for that tick. */
static bool client_apply_correction(const char *label, u32 correction_tick,
                                    size_t correction_bytes) {
    if (!g_client_world) {
        g_client_world = physics_world_create(32u);
        physics_sync_init(&g_client_tracker);
        physics_sync_baseline_init(&g_client_held);
    }
    u32 applied_tick = 0u;
    bool applied = g_client_world && correction_bytes > 0u &&
                   physics_sync_apply_received(&g_client_tracker, g_client_world, &g_client_held,
                                               g_correction, correction_bytes, &applied_tick) &&
                   applied_tick == correction_tick;
    bool converged = applied && g_report_seen && g_report_tick == correction_tick &&
                     physics_state_hash(g_client_world) == g_report_hash;
    fprintf(g_report, "%s_applied tick=%u converged=%d\n", label, applied_tick,
            converged ? 1 : 0);
    return applied;
}

static void client_release_world(void) {
    if (g_client_world) physics_world_destroy(g_client_world);
    g_client_world = NULL;
    physics_sync_baseline_release(&g_client_held);
}

/* Confirms the snapshot this client last restored by reporting its own
 * hash at that tick (which matches the authority), then reports a desync.
 * The repeated desync sent before the first correction can reach the server
 * after it and produce one more full correction, which would move the
 * server's baseline past the tick being confirmed; settling first applies
 * such corrections. The exchange is still retried a bounded number of times.
 * The delta must be smaller than the first full correction and decode
 * against the held snapshot. */
/* Reads until a physics report several ticks newer than the held snapshot
 * arrives with no correction before it. The server sends a correction right
 * after the report for its tick, so by then every correction that earlier
 * desync reports caused has been read and applied, and the held tick is the
 * server's latest baseline for this peer. */
static bool client_settle_corrections(NetClient *c, u32 timeout_ms) {
    u64 deadline = now_ms() + timeout_ms;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got < 0) return false;
        if (got != 1) continue;
        if (env.message_id == BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT &&
            env.payload_size == NET_CLIENT_PHYSICS_REPORT_BYTES) {
            const u8 *r = (const u8 *)env.payload;
            g_report_seen = true;
            g_report_tick = le32(r + 4u);
            g_report_hash = (u64)le32(r + 8u) | ((u64)le32(r + 12u) << 32u);
            if (g_report_tick >= g_client_held.tick + 4u) return true;
            continue;
        }
        if (env.message_id != BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_CORRECTION ||
            env.payload_size > sizeof(g_correction)) {
            continue;
        }
        memcpy(g_correction, env.payload, env.payload_size);
        u32 tick = le32(g_correction + 4u);
        if (!client_apply_correction("physics_extra_correction", tick, env.payload_size)) {
            return false;
        }
    }
    return false;
}

static void client_delta_correction_exchange(NetClient *c, size_t full_bytes) {
    bool is_delta = false;
    u32 attempts = 0u;
    while (!is_delta && attempts < 3u && g_client_world && g_client_held.bytes) {
        ++attempts;
        if (!client_settle_corrections(c, 10000u)) break;
        u8 report[NET_CLIENT_PHYSICS_REPORT_BYTES];
        u32 held_tick = g_client_held.tick;
        if (!physics_sync_encode_report(held_tick, physics_state_hash(g_client_world), report,
                                        sizeof(report)) ||
            !client_send(c, BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, 1u, report,
                         sizeof(report))) {
            break;
        }
        report[8] ^= 0xffu;
        if (!client_send(c, BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, 1u, report,
                         sizeof(report))) {
            break;
        }
        u32 tick = 0u;
        size_t bytes = 0u;
        if (client_next_physics_correction(c, &tick, &bytes, 10000u) != 1) break;
        is_delta = bytes >= NET_CLIENT_PHYSICS_DELTA_HEADER &&
                   le32(g_correction) == NET_CLIENT_PHYSICS_DELTA_MAGIC;
        if (is_delta) {
            fprintf(g_report,
                    "physics_delta_correction tick=%u bytes=%zu full_bytes=%zu baseline=%u"
                    " held=%u attempts=%u\n",
                    tick, bytes, full_bytes, le32(g_correction + 8u), held_tick, attempts);
            check(client_apply_correction("physics_delta_correction", tick, bytes),
                  "a_applied_physics_delta_correction");
        } else if (!client_apply_correction("physics_extra_correction", tick, bytes)) {
            break;
        }
    }
    check(is_delta, "a_received_delta_physics_correction");
}

static bool client_receives_correction_before(NetClient *c, u32 after_tick, u32 timeout_ms) {
    u64 deadline = now_ms() + timeout_ms;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got < 0) return true;
        if (got != 1) continue;
        if (env.message_id == BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_CORRECTION) return true;
        if (env.message_id == BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT &&
            env.payload_size == NET_CLIENT_PHYSICS_REPORT_BYTES &&
            le32((const u8 *)env.payload + 4u) > after_tick) {
            return false;
        }
    }
    return true;
}

static bool send_snapshot(NetClient *c, const CoreAppSnapshot *snapshot, size_t trailing) {
    u8 wire[CORE_APP_SNAPSHOT_MAX_BYTES + 64u];
    size_t size = 0u;
    if (core_app_snapshot_encode(snapshot, wire, sizeof(wire), &size) != CORE_APP_SNAPSHOT_OK) {
        return false;
    }
    memset(wire + size, 0xa5, trailing);
    return client_send(c, CORE_APP_SNAPSHOT_MESSAGE_ID, CORE_APP_SNAPSHOT_PROTOCOL_VERSION, wire,
                       size + trailing);
}
/* Waits for a clock probe reply that echoes t0. Returns 1 with the reply,
 * 0 on timeout, -1 on a close or a malformed probe. */
static int client_next_clock_reply(NetClient *c, u64 t0, CoreAppClockProbe *out, u64 *t3,
                                   u32 timeout_ms) {
    u64 deadline = now_ms() + timeout_ms;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got != 1) return got;
        if (env.message_id != CORE_APP_CLOCK_PROBE_MESSAGE_ID) continue;
        *t3 = now_us();
        if (env.protocol_version != 1u ||
            core_app_clock_probe_decode((const u8 *)env.payload, env.payload_size, out) !=
                CORE_APP_SNAPSHOT_OK) {
            return -1;
        }
        if (out->kind != CORE_APP_CLOCK_PROBE_REPLY) return -1;
        /* t0 values 11..13 belong to malformed probes, which must never be
         * answered. */
        if (out->t0 >= 11u && out->t0 <= 13u) return -1;
        if (out->t0 == t0) return 1;
    }
    return 0;
}

/* Keeps reading (client_recv answers server requests) until the request
 * marked to be skipped has been dropped, `more` requests after it have been
 * answered, and at least `total` have been answered overall. Earlier phases
 * answer probes too, and how many depends on timing, so the skipped request
 * can come after `total` is already reached. */
static bool client_answer_server_probes(NetClient *c, u32 more, u32 total, u32 timeout_ms) {
    u64 deadline = now_ms() + timeout_ms;
    u32 target = 0u;
    bool skipped = false;
    while (now_ms() < deadline) {
        if (!skipped && !c->skip_server_probe) {
            skipped = true;
            target = g_server_probes_answered + more;
            if (target < total) target = total;
        }
        if (skipped && g_server_probes_answered >= target) return true;
        BreakNetEnvelope env;
        if (client_recv(c, &env, (u32)(deadline - now_ms()) + 1u) < 0) return false;
    }
    return false;
}

static bool send_clock_probe(NetClient *c, const CoreAppClockProbe *probe, size_t size) {
    u8 wire[CORE_APP_CLOCK_PROBE_BYTES];
    size_t encoded = 0u;
    CoreAppClockProbe request = *probe;
    u64 t1 = request.t1;
    request.t1 = 0u;
    if (core_app_clock_probe_encode(&request, wire, sizeof(wire), &encoded) !=
        CORE_APP_SNAPSHOT_OK) {
        return false;
    }
    for (u32 i = 0u; i < 8u; ++i) wire[16u + i] = (u8)(t1 >> (8u * i));
    return client_send(c, CORE_APP_CLOCK_PROBE_MESSAGE_ID, 1u, wire, size);
}

/* Malformed probes first (no reply allowed), then four real exchanges fed
 * to the offset estimator. Both ends read CLOCK_MONOTONIC on one machine,
 * so the true offset is 0 and must lie inside the reported error bound. */
static void client_clock_probe_exchange(NetClient *c) {
    CoreAppClockProbe probe = {CORE_APP_CLOCK_PROBE_REQUEST, 0u, 0u, 0u};
    CoreAppClockProbe reply;
    ClockOffsetEstimator estimator;
    u64 t3 = 0u;
    clock_offset_init(&estimator);
    probe.t0 = 11u;
    check(send_clock_probe(c, &probe, CORE_APP_CLOCK_PROBE_BYTES - 1u), "a_sent_short_clock_probe");
    probe.t0 = 12u;
    probe.t1 = 5u;
    check(send_clock_probe(c, &probe, CORE_APP_CLOCK_PROBE_BYTES),
          "a_sent_clock_probe_request_with_t1");
    probe.t1 = 0u;
    CoreAppClockProbe forged_reply = {CORE_APP_CLOCK_PROBE_REPLY, 13u, 20u, 30u};
    u8 forged_wire[CORE_APP_CLOCK_PROBE_BYTES];
    size_t forged_size = 0u;
    check(core_app_clock_probe_encode(&forged_reply, forged_wire, sizeof(forged_wire),
                                      &forged_size) == CORE_APP_SNAPSHOT_OK &&
              client_send(c, CORE_APP_CLOCK_PROBE_MESSAGE_ID, 1u, forged_wire, forged_size),
          "a_sent_clock_probe_reply_to_server");
    bool replies_ok = true;
    for (u32 i = 0u; i < 4u; ++i) {
        probe.t0 = now_us();
        if (!send_clock_probe(c, &probe, CORE_APP_CLOCK_PROBE_BYTES) ||
            client_next_clock_reply(c, probe.t0, &reply, &t3, 10000u) != 1 ||
            reply.t2 < reply.t1) {
            replies_ok = false;
            break;
        }
        ClockOffsetSample sample = {reply.t0, reply.t1, reply.t2, t3};
        replies_ok = replies_ok && clock_offset_add(&estimator, &sample) == CLOCK_OFFSET_OK;
    }
    check(replies_ok, "a_received_clock_probe_replies");
    ClockOffsetEstimate estimate;
    bool estimated = clock_offset_estimate(&estimator, &estimate) == CLOCK_OFFSET_OK;
    check(estimated && estimate.samples == 4u && estimator.rejected == 0u,
          "a_clock_offset_estimated");
    if (estimated) {
        u64 magnitude = estimate.offset_us < 0 ? (u64)(-estimate.offset_us)
                                               : (u64)estimate.offset_us;
        check(magnitude <= estimate.error_us, "a_clock_offset_within_error");
        fprintf(g_report, "clock_offset offset_us=%lld error_us=%llu samples=%u\n",
                (long long)estimate.offset_us, (unsigned long long)estimate.error_us,
                estimate.samples);
    }
    c->skip_server_probe = true;
    check(client_answer_server_probes(c, 2u, 6u, 15000u), "a_answered_server_clock_probes");
    fprintf(g_report, "server_clock_probes_answered=%u\n", g_server_probes_answered);
}

static bool snapshot_shape_ok(const CoreAppSnapshot *s) {
    return s->schema_hash == core_app_snapshot_schema_hash() && s->frame_id > 0u &&
           s->level_generation > 0u && s->entity_count == 2u && s->entities[0].flags == 1u &&
           s->entities[1].flags == 2u && s->entities[0].generation > 0u &&
           s->entities[1].generation > 0u &&
           (s->entities[0].index != s->entities[1].index ||
            s->entities[0].generation != s->entities[1].generation);
}

#define NET_CLIENT_ASPECT_PACKET_BYTES 2048u
#define NET_CLIENT_ASPECT_FRAGMENT_BYTES 17u

typedef struct AspectPeer {
    BreakAspectStore *store;
    BreakReplicationReassemblyPool *pool;
    BreakOnlineHandle handles[2];
    u64 schema_hash;
    u32 applied;
} AspectPeer;

static void aspect_peer_dispose(AspectPeer *peer) {
    break_replication_reassembly_pool_destroy(peer->pool);
    break_aspect_store_destroy(peer->store);
    memset(peer, 0, sizeof(*peer));
}

static bool aspect_peer_init(AspectPeer *peer) {
    static const BreakAspectSchema schemas[] = {
        {1u, 1u, BREAK_ASPECT_U32, 4u},
        {2u, 1u, BREAK_ASPECT_U32, 4u},
        {3u, 1u, BREAK_ASPECT_F32, 4u},
        {4u, 1u, BREAK_ASPECT_F32, 4u},
        {5u, 1u, BREAK_ASPECT_F32, 4u},
        {6u, 1u, BREAK_ASPECT_U32, 4u},
    };
    BreakAspectStoreConfig config = {3u, 16u, NET_CLIENT_ASPECT_PACKET_BYTES};
    memset(peer, 0, sizeof(*peer));
    peer->handles[0] = (BreakOnlineHandle){1u, 1u};
    peer->handles[1] = (BreakOnlineHandle){2u, 1u};
    if (break_aspect_store_create(&config, &peer->store) != BREAK_RUNTIME_OK) return false;
    for (u32 i = 0u; i < sizeof(schemas) / sizeof(schemas[0]); ++i) {
        if (break_aspect_schema_register(peer->store, &schemas[i]) != BREAK_RUNTIME_OK) {
            aspect_peer_dispose(peer);
            return false;
        }
    }
    if (break_aspect_object_adopt(peer->store, peer->handles[0]) != BREAK_RUNTIME_OK ||
        break_aspect_object_adopt(peer->store, peer->handles[1]) != BREAK_RUNTIME_OK) {
        aspect_peer_dispose(peer);
        return false;
    }
    peer->schema_hash = break_aspect_schema_hash(peer->store);
    peer->pool = break_replication_reassembly_pool_create(peer->schema_hash, 8u, 8192u);
    if (!peer->schema_hash || !peer->pool) {
        aspect_peer_dispose(peer);
        return false;
    }
    return true;
}

static bool aspect_peer_accept(AspectPeer *peer, const BreakNetEnvelope *env) {
    BreakReplicationFragment fragment;
    BreakReplicationReassemblyResult result;
    u64 completed_delta = 0u;
    u8 *payload = NULL;
    size_t payload_size = 0u;
    bool applied = false;
    if (env->protocol_version != BREAK_REPLICATION_WIRE_VERSION ||
        break_replication_wire_decode(env->payload, env->payload_size, &fragment) !=
            BREAK_REPLICATION_FRAGMENT_OK ||
        fragment.base_id != peer->schema_hash) {
        return false;
    }
    result = break_replication_reassembly_pool_push_at(
        peer->pool, &fragment, now_ms(), &completed_delta, &payload, &payload_size);
    if (result == BREAK_REPLICATION_REASSEMBLY_INCOMPLETE ||
        result == BREAK_REPLICATION_REASSEMBLY_DUPLICATE) {
        return true;
    }
    if (result != BREAK_REPLICATION_REASSEMBLY_COMPLETE) return false;
    applied = payload && payload_size >= 12u && memcmp(payload, "BRA1", 4u) == 0 &&
              le64(payload + 4u) == peer->schema_hash &&
              break_aspect_apply(peer->store, payload, payload_size) == BREAK_RUNTIME_OK;
    break_replication_reassembly_free(payload);
    if (applied) peer->applied++;
    return applied;
}

static bool aspect_peer_values_match(const AspectPeer *peer, const CoreAppSnapshot *snapshot) {
    if (!snapshot_shape_ok(snapshot) || peer->handles[0].index != 1u ||
        peer->handles[0].generation != 1u || peer->handles[1].index != 2u ||
        peer->handles[1].generation != 1u) {
        return false;
    }
    for (u32 i = 0u; i < 2u; ++i) {
        const CoreAppSnapshotEntity *entity = &snapshot->entities[i];
        u32 unsigned_value = 0u;
        f32 float_value = 0.0f;
        if (break_aspect_get_u32(peer->store, peer->handles[i], 1u, &unsigned_value) !=
                BREAK_RUNTIME_OK ||
            unsigned_value != entity->index ||
            break_aspect_get_u32(peer->store, peer->handles[i], 2u, &unsigned_value) !=
                BREAK_RUNTIME_OK ||
            unsigned_value != entity->generation ||
            break_aspect_get_f32(peer->store, peer->handles[i], 3u, &float_value) !=
                BREAK_RUNTIME_OK ||
            float_value != entity->x ||
            break_aspect_get_f32(peer->store, peer->handles[i], 4u, &float_value) !=
                BREAK_RUNTIME_OK ||
            float_value != entity->y ||
            break_aspect_get_f32(peer->store, peer->handles[i], 5u, &float_value) !=
                BREAK_RUNTIME_OK ||
            float_value != entity->z ||
            break_aspect_get_u32(peer->store, peer->handles[i], 6u, &unsigned_value) !=
                BREAK_RUNTIME_OK ||
            unsigned_value != entity->flags) {
            return false;
        }
    }
    return true;
}

static bool aspect_peer_send_packet(NetClient *c, AspectPeer *peer, u64 delta_id, u64 epoch,
                                    bool mismatch, u32 *sent_fragments, u32 *duplicates) {
    u8 packet[NET_CLIENT_ASPECT_PACKET_BYTES];
    size_t packet_size = 0u;
    BreakReplicationFragment *fragments = NULL;
    size_t fragment_count = 0u;
    bool sent = true;
    if (break_aspect_encode_with_epoch(
            peer->store, peer->handles[0],
            break_aspect_active_mask(peer->store, peer->handles[0]), BREAK_ASPECT_BASELINE,
            epoch, packet, sizeof(packet), &packet_size) != BREAK_RUNTIME_OK) {
        return false;
    }
    if (mismatch && packet_size >= 12u) packet[4] ^= 1u;
    if (break_replication_fragment_payload(
            delta_id, peer->schema_hash, packet, packet_size, NET_CLIENT_ASPECT_FRAGMENT_BYTES,
            &fragments, &fragment_count) != BREAK_REPLICATION_FRAGMENT_OK) {
        return false;
    }
    for (size_t i = fragment_count; i-- > 0u && sent;) {
        u8 wire[BREAK_REPLICATION_WIRE_HEADER_SIZE + NET_CLIENT_ASPECT_FRAGMENT_BYTES];
        size_t wire_size = 0u;
        sent = break_replication_wire_encode(&fragments[i], wire, sizeof(wire), &wire_size) ==
                   BREAK_REPLICATION_FRAGMENT_OK &&
               client_send(c, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT,
                           BREAK_REPLICATION_WIRE_VERSION, wire, wire_size);
        if (sent) (*sent_fragments)++;
        if (sent && !mismatch && i == 1u) {
            wire_size = 0u;
            sent = break_replication_wire_encode(&fragments[i], wire, sizeof(wire),
                                                 &wire_size) ==
                       BREAK_REPLICATION_FRAGMENT_OK &&
                   client_send(c, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT,
                               BREAK_REPLICATION_WIRE_VERSION, wire, wire_size);
            if (sent) (*duplicates)++;
        }
    }
    break_replication_fragments_free(fragments, fragment_count);
    return sent;
}

static void scenario_aspect(void) {
    NetClient a;
    AspectPeer peer;
    CoreAppSnapshot snapshot;
    bool values_match = false;
    bool decode_ok = true;
    u32 valid_fragments = 0u;
    u32 mismatch_fragments = 0u;
    u32 duplicates = 0u;
    memset(&peer, 0, sizeof(peer));
    check(aspect_peer_init(&peer), "aspect_local_store_and_reassembler");
    check(client_open(&a), "aspect_tls_challenge");
    check(client_auth(&a, g_psk), "aspect_auth_sent");
    if (peer.store && peer.pool) {
        u64 deadline = now_ms() + 15000u;
        while (peer.applied < 2u || !values_match) {
            BreakNetEnvelope env;
            int got;
            if (now_ms() >= deadline) break;
            got = client_recv(&a, &env, (u32)(deadline - now_ms()) + 1u);
            if (got < 0) {
                decode_ok = false;
                break;
            }
            if (got == 0) continue;
            if (env.message_id == BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT) {
                if (!aspect_peer_accept(&peer, &env)) {
                    decode_ok = false;
                    break;
                }
            } else if (env.message_id == CORE_APP_SNAPSHOT_MESSAGE_ID && peer.applied >= 2u &&
                       env.protocol_version == CORE_APP_SNAPSHOT_PROTOCOL_VERSION &&
                       core_app_snapshot_decode((const u8 *)env.payload, env.payload_size,
                                                &snapshot) == CORE_APP_SNAPSHOT_OK) {
                values_match = aspect_peer_values_match(&peer, &snapshot);
            }
        }
    }
    check(decode_ok, "aspect_brfg_wire_and_bra1_schema");
    check(peer.applied == 2u, "aspect_received_and_applied_fixed_handles");
    check(values_match, "aspect_applied_values_match_snapshot");
    check_welcome(&a, "aspect");
    if (peer.applied == 2u && values_match) {
        CoreAppClockProbe probe = {CORE_APP_CLOCK_PROBE_REQUEST, 0u, 0u, 0u};
        CoreAppClockProbe reply;
        u64 t3 = 0u;
        check(break_aspect_set_f32(peer.store, peer.handles[0], 3u, 123.5f) == BREAK_RUNTIME_OK,
              "aspect_prepared_inbound_baseline");
        check(aspect_peer_send_packet(&a, &peer, 100u, 2u, false, &valid_fragments,
                                      &duplicates),
              "aspect_sent_out_of_order_and_duplicate_fragments");
        check(aspect_peer_send_packet(&a, &peer, 101u, 3u, true, &mismatch_fragments,
                                      &duplicates),
              "aspect_sent_schema_mismatch_packet");
        probe.t0 = now_us();
        check(send_clock_probe(&a, &probe, CORE_APP_CLOCK_PROBE_BYTES) &&
                  client_next_clock_reply(&a, probe.t0, &reply, &t3, 10000u) == 1,
              "aspect_server_drained_before_close");
    }
    fprintf(g_report,
            "aspect applied=%u values=%d valid_fragments=%u duplicates=%u"
            " mismatch_fragments=%u\n",
            peer.applied, values_match ? 1 : 0, valid_fragments, duplicates,
            mismatch_fragments);
    client_close(&a);
    aspect_peer_dispose(&peer);
}

#define NET_CLIENT_WORLD_PACKET_BYTES 16384u
#define NET_CLIENT_WORLD_FRAGMENT_BYTES 23u
#define NET_CLIENT_WORLD_MAX_FRAGMENTS 64u
#define NET_CLIENT_WORLD_SERVER_WIRE_BYTES (BREAK_REPLICATION_WIRE_HEADER_SIZE + 64u)
#define NET_CLIENT_WORLD_CONNECTION 1u
#define NET_CLIENT_WORLD_SERVER_CONTROLS 3u

typedef struct WorldPeer {
    BreakComponentSchemaRegistry *schemas;
    World *world;
    BreakWorldSession *session;
    u64 level_generation;
    u64 epoch;
    u64 attempts;
    u64 full_attempts;
    u64 delta_attempts;
    u64 target_matches;
    u64 pre_drain_unchanged;
    u64 reversed_fragments;
    u64 duplicate_fragments;
    u64 outbound_full;
    u64 outbound_delta;
    u64 outbound_fragments;
    u64 outbound_duplicates;
    u64 need_full;
    u64 recovered;
    BreakWorldSessionControl server_controls[NET_CLIENT_WORLD_SERVER_CONTROLS];
    u64 server_correlations[NET_CLIENT_WORLD_SERVER_CONTROLS];
    u32 server_control_count;
    u32 correlated_control_count;
    u32 client_control_count;
} WorldPeer;

typedef struct WorldAttempt {
    u64 delta_id;
    u64 base_snapshot_id;
    u64 target_snapshot_id;
    u64 target_tick;
    BreakWorldDeltaWireKind kind;
    usize fragment_count;
    usize wire_sizes[NET_CLIENT_WORLD_MAX_FRAGMENTS];
    u8 wires[NET_CLIENT_WORLD_MAX_FRAGMENTS][NET_CLIENT_WORLD_SERVER_WIRE_BYTES];
} WorldAttempt;

static u64 world_clock(void *user) {
    (void)user;
    return now_ms();
}

static void world_peer_dispose(WorldPeer *peer) {
    break_world_session_destroy(peer->session);
    world_destroy(peer->world);
    break_schema_registry_destroy(peer->schemas);
    peer->session = NULL;
    peer->world = NULL;
    peer->schemas = NULL;
}

static bool world_peer_init(WorldPeer *peer, u64 level_generation) {
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
    BreakWorldSessionConfig config;
    memset(peer, 0, sizeof(*peer));
    peer->level_generation = level_generation;
    peer->schemas = break_schema_registry_create();
    peer->world = world_create();
    if (!peer->schemas || !peer->world) {
        world_peer_dispose(peer);
        return false;
    }
    for (u32 i = 0u; i < sizeof(schemas) / sizeof(schemas[0]); ++i) {
        if (break_schema_register(peer->schemas, &schemas[i]) != BREAK_SCHEMA_OK) {
            world_peer_dispose(peer);
            return false;
        }
        world_register_component(peer->world, schemas[i].component_id, (u32)schemas[i].size);
    }
    memset(&config, 0, sizeof(config));
    config.schemas = peer->schemas;
    config.protocol_version = 1u;
    config.level_generation = level_generation;
    config.bridge.max_connections = 1u;
    config.bridge.stream_capacity = 16u;
    config.bridge.max_pending_bytes_per_connection = NET_CLIENT_WORLD_PACKET_BYTES;
    config.bridge.max_total_pending_bytes = NET_CLIENT_WORLD_PACKET_BYTES;
    config.bridge.max_metadata_bytes_per_connection = NET_CLIENT_WORLD_PACKET_BYTES;
    config.bridge.max_total_metadata_bytes = NET_CLIENT_WORLD_PACKET_BYTES;
    config.bridge.max_fragment_bytes = 64u;
    config.bridge.max_fragment_count = NET_CLIENT_WORLD_MAX_FRAGMENTS;
    config.bridge.completion_capacity = 64u;
    config.bridge.max_completion_packet_bytes = NET_CLIENT_WORLD_PACKET_BYTES;
    config.bridge.max_completion_queue_bytes = 64u * NET_CLIENT_WORLD_PACKET_BYTES;
    config.bridge.clock = world_clock;
    config.packet_byte_limit = NET_CLIENT_WORLD_PACKET_BYTES;
    config.need_full_tick_interval = 1u;
    peer->session = break_world_session_create(&config);
    peer->epoch = break_world_session_stream_epoch(1u, break_schema_hash(peer->schemas),
                                                   level_generation);
    if (!peer->session || !peer->epoch ||
        !break_world_session_open(peer->session, NET_CLIENT_WORLD_CONNECTION)) {
        world_peer_dispose(peer);
        return false;
    }
    return true;
}

static void world_put16(u8 *out, u16 value) {
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void world_put64(u8 *out, u64 value) {
    for (u32 i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (8u * i));
}

static bool world_send_control(NetClient *c, WorldPeer *peer, BreakWorldSessionControlKind kind,
                               const WorldAttempt *attempt) {
    u8 payload[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2];
    bool sent;
    memset(payload, 0, sizeof(payload));
    memcpy(payload, "BRWC", 4u);
    world_put16(payload + 4u, 2u);
    world_put16(payload + 6u, (u16)kind);
    if (kind == BREAK_WORLD_SESSION_CONTROL_ACK) world_put64(payload + 8u, attempt->delta_id);
    world_put64(payload + 16u, attempt->target_snapshot_id);
    world_put64(payload + 24u, attempt->target_tick);
    world_put64(payload + 32u, peer->level_generation);
    sent = client_send(c, BREAK_NET_MESSAGE_ID_WORLD_CONTROL, 2u, payload, sizeof(payload));
    if (sent) peer->client_control_count++;
    return sent;
}

static bool world_decode_control(const BreakNetEnvelope *env, BreakWorldSessionControl *control) {
    const u8 *payload;
    if (env->message_id != BREAK_NET_MESSAGE_ID_WORLD_CONTROL || env->protocol_version != 2u ||
        env->payload_size != BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2) {
        return false;
    }
    payload = (const u8 *)env->payload;
    if (memcmp(payload, "BRWC", 4u) != 0 || payload[4] != 2u || payload[5] != 0u) return false;
    memset(control, 0, sizeof(*control));
    control->kind = (BreakWorldSessionControlKind)((u16)payload[6] | ((u16)payload[7] << 8u));
    control->delta_id = le64(payload + 8u);
    control->target_snapshot_id = le64(payload + 16u);
    control->target_tick = le64(payload + 24u);
    control->level_generation = le64(payload + 32u);
    if (control->kind == BREAK_WORLD_SESSION_CONTROL_NEED_FULL) return control->delta_id == 0u;
    return control->kind == BREAK_WORLD_SESSION_CONTROL_ACK && control->delta_id != 0u &&
           control->target_snapshot_id != 0u;
}

static bool world_control_is_new(const WorldPeer *peer, const BreakWorldSessionControl *control,
                                 u64 correlation_id) {
    for (u32 i = 0u; i < peer->server_control_count; ++i) {
        const BreakWorldSessionControl *seen = &peer->server_controls[i];
        if (peer->server_correlations[i] == correlation_id ||
            (seen->kind == control->kind && seen->delta_id == control->delta_id &&
             seen->target_snapshot_id == control->target_snapshot_id &&
             seen->target_tick == control->target_tick &&
             seen->level_generation == control->level_generation)) {
            return false;
        }
    }
    return true;
}

static bool world_wait_control(NetClient *c, WorldPeer *peer, BreakWorldSessionControlKind kind,
                               u64 delta_id, u64 target_snapshot_id, u64 target_tick) {
    u64 deadline = now_ms() + 10000u;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        BreakWorldSessionControl control;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got < 0) return false;
        if (got == 0 || env.message_id != BREAK_NET_MESSAGE_ID_WORLD_CONTROL) continue;
        if (!world_decode_control(&env, &control)) return false;
        check(env.correlation_id != 0u, "world_server_control_correlation_nonzero");
        check(world_control_is_new(peer, &control, env.correlation_id),
              "world_server_control_and_correlation_unique");
        check(control.kind == kind && control.delta_id == delta_id &&
                  control.target_snapshot_id == target_snapshot_id &&
                  control.target_tick == target_tick &&
                  control.level_generation == peer->level_generation,
              "world_server_control_payload_target_and_level_preserved");
        if (env.correlation_id == 0u ||
            !world_control_is_new(peer, &control, env.correlation_id) ||
            control.kind != kind || control.delta_id != delta_id ||
            control.target_snapshot_id != target_snapshot_id || control.target_tick != target_tick ||
            control.level_generation != peer->level_generation ||
            peer->server_control_count >= NET_CLIENT_WORLD_SERVER_CONTROLS) {
            return false;
        }
        peer->server_controls[peer->server_control_count] = control;
        peer->server_correlations[peer->server_control_count] = env.correlation_id;
        peer->server_control_count++;
        peer->correlated_control_count++;
        return true;
    }
    return false;
}

static bool world_controls_finished(NetClient *c, WorldPeer *peer) {
    CoreAppClockProbe probe = {CORE_APP_CLOCK_PROBE_REQUEST, 0u, 0u, 0u};
    u64 deadline;
    probe.t0 = now_us();
    if (!send_clock_probe(c, &probe, CORE_APP_CLOCK_PROBE_BYTES)) return false;
    deadline = now_ms() + 10000u;
    while (now_ms() < deadline) {
        BreakNetEnvelope env;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got < 0) return false;
        if (got == 0) continue;
        if (env.message_id == BREAK_NET_MESSAGE_ID_WORLD_CONTROL) {
            check(false, "world_no_duplicate_control_after_final_ack");
            return false;
        }
        if (env.message_id == CORE_APP_CLOCK_PROBE_MESSAGE_ID) {
            CoreAppClockProbe reply;
            if (env.protocol_version != 1u ||
                core_app_clock_probe_decode((const u8 *)env.payload, env.payload_size, &reply) !=
                    CORE_APP_SNAPSHOT_OK) {
                return false;
            }
            if (reply.kind == CORE_APP_CLOCK_PROBE_REPLY && reply.t0 == probe.t0) {
                check(peer->server_control_count == NET_CLIENT_WORLD_SERVER_CONTROLS &&
                          peer->correlated_control_count == NET_CLIENT_WORLD_SERVER_CONTROLS &&
                          peer->client_control_count == 1u,
                      "world_exactly_three_correlated_server_controls");
                return peer->server_control_count == NET_CLIENT_WORLD_SERVER_CONTROLS &&
                       peer->correlated_control_count == NET_CLIENT_WORLD_SERVER_CONTROLS &&
                       peer->client_control_count == 1u;
            }
        }
    }
    return false;
}

static bool world_accept_wire(WorldPeer *peer, const u8 *wire, usize wire_size) {
    BreakNetOwnedMessage message;
    memset(&message, 0, sizeof(message));
    message.message_id = BREAK_NET_MESSAGE_ID_WORLD_DELTA;
    message.protocol_version = BREAK_REPLICATION_WIRE_VERSION;
    message.sequence = 1u;
    message.data = (void *)wire;
    message.size = wire_size;
    return break_replication_session_handle_message(
        NET_CLIENT_WORLD_CONNECTION, &message, break_world_session_bridge(peer->session));
}

static bool world_receive_attempt(NetClient *c, WorldPeer *peer, WorldAttempt *attempt) {
    BreakReplicationReassembler *inspector = NULL;
    BreakWorldSnapshot *before = NULL;
    BreakWorldSnapshot *queued = NULL;
    BreakWorldSnapshot *rebuilt = NULL;
    BreakWorldSessionStats stats_before;
    BreakWorldSessionStats stats_after;
    bool seen[NET_CLIENT_WORLD_MAX_FRAGMENTS] = {false};
    u8 *payload = NULL;
    usize payload_size = 0u;
    usize seen_count = 0u;
    u64 baseline_id = 0u;
    u64 baseline_tick = 0u;
    bool complete = false;
    bool ok = true;
    memset(attempt, 0, sizeof(*attempt));
    inspector = break_replication_reassembler_create(peer->epoch);
    ok = inspector != NULL;
    u64 deadline = now_ms() + 15000u;
    while (ok && !complete && now_ms() < deadline) {
        BreakNetEnvelope env;
        BreakReplicationFragment fragment;
        BreakReplicationReassemblyResult result;
        int got = client_recv(c, &env, (u32)(deadline - now_ms()) + 1u);
        if (got < 0) {
            ok = false;
            break;
        }
        if (got == 0) continue;
        if (env.message_id == BREAK_NET_MESSAGE_ID_WORLD_CONTROL) {
            check(false, "world_inbound_control_never_causes_server_control_reply");
            ok = false;
            break;
        }
        if (env.message_id != BREAK_NET_MESSAGE_ID_WORLD_DELTA) continue;
        if (env.protocol_version != BREAK_REPLICATION_WIRE_VERSION ||
            break_replication_wire_decode(env.payload, env.payload_size, &fragment) !=
                BREAK_REPLICATION_FRAGMENT_OK ||
            fragment.base_id != peer->epoch || fragment.fragment_count == 0u ||
            fragment.fragment_count > NET_CLIENT_WORLD_MAX_FRAGMENTS ||
            fragment.fragment_index >= fragment.fragment_count ||
            env.payload_size > NET_CLIENT_WORLD_SERVER_WIRE_BYTES ||
            (attempt->fragment_count != 0u &&
             (attempt->delta_id != fragment.delta_id ||
              attempt->fragment_count != fragment.fragment_count)) ||
            seen[fragment.fragment_index]) {
            ok = false;
            break;
        }
        attempt->delta_id = fragment.delta_id;
        attempt->fragment_count = fragment.fragment_count;
        attempt->wire_sizes[fragment.fragment_index] = env.payload_size;
        memcpy(attempt->wires[fragment.fragment_index], env.payload, env.payload_size);
        seen[fragment.fragment_index] = true;
        seen_count++;
        result = break_replication_reassembler_push(inspector, &fragment, &payload, &payload_size);
        if (result == BREAK_REPLICATION_REASSEMBLY_COMPLETE) {
            complete = seen_count == attempt->fragment_count;
            if (!complete) ok = false;
        } else if (result != BREAK_REPLICATION_REASSEMBLY_INCOMPLETE) {
            ok = false;
        }
    }
    if (ok && complete) {
        BreakWorldDeltaWire message;
        ok = break_world_delta_wire_decode(payload, payload_size, &message) ==
             BREAK_WORLD_DELTA_WIRE_OK;
        if (ok) {
            attempt->kind = message.kind;
            attempt->base_snapshot_id = message.base_snapshot_id;
            attempt->target_snapshot_id = message.target_snapshot_id;
            attempt->target_tick = message.target_tick;
            break_world_delta_wire_clear(&message);
        }
    } else {
        ok = false;
    }
    break_replication_reassembly_free(payload);
    break_replication_reassembler_destroy(inspector);
    check(ok, "world_brwd_reassembly");
    if (!ok) return false;

    break_world_session_stats(peer->session, &stats_before);
    ok = break_world_session_baseline(peer->session, NET_CLIENT_WORLD_CONNECTION, &baseline_id,
                                      &baseline_tick);
    before = break_world_snapshot_build(peer->world, peer->schemas, baseline_tick);
    ok = ok && before != NULL;
    for (usize i = attempt->fragment_count; i-- > 0u && ok;) {
        ok = world_accept_wire(peer, attempt->wires[i], attempt->wire_sizes[i]);
        if (ok && i == attempt->fragment_count - 1u) {
            ok = world_accept_wire(peer, attempt->wires[i], attempt->wire_sizes[i]);
        }
    }
    peer->reversed_fragments += attempt->fragment_count;
    break_world_session_stats(peer->session, &stats_after);
    queued = break_world_snapshot_build(peer->world, peer->schemas, baseline_tick);
    {
        u64 queued_baseline_id = 0u;
        u64 queued_baseline_tick = 0u;
        bool unchanged = ok && queued &&
                         break_world_session_baseline(peer->session, NET_CLIENT_WORLD_CONNECTION,
                                                      &queued_baseline_id,
                                                      &queued_baseline_tick) &&
                         queued_baseline_id == baseline_id && queued_baseline_tick == baseline_tick &&
                         break_world_snapshot_id(queued) == break_world_snapshot_id(before) &&
                         stats_after.applied_packets == stats_before.applied_packets &&
                         stats_after.bridge.completion_count == stats_before.bridge.completion_count + 1u &&
                         stats_after.bridge.duplicate_fragments ==
                             stats_before.bridge.duplicate_fragments + 1u;
        check(unchanged, "world_completion_waits_for_drain_without_mutating_world");
        if (unchanged) peer->pre_drain_unchanged++;
        ok = unchanged;
    }
    if (ok) {
        usize drained = break_world_session_drain(peer->session, NET_CLIENT_WORLD_CONNECTION,
                                                  peer->world, 1u);
        u64 drained_id = 0u;
        u64 drained_tick = 0u;
        rebuilt = break_world_snapshot_build(peer->world, peer->schemas, attempt->target_tick);
        break_world_session_stats(peer->session, &stats_after);
        ok = drained == 1u && rebuilt &&
             break_world_session_baseline(peer->session, NET_CLIENT_WORLD_CONNECTION, &drained_id,
                                          &drained_tick) &&
             drained_id == attempt->target_snapshot_id && drained_tick == attempt->target_tick &&
             break_world_snapshot_id(rebuilt) == attempt->target_snapshot_id &&
             stats_after.applied_packets == stats_before.applied_packets + 1u;
    }
    check(ok, "world_drain_rebuilds_server_target_snapshot");
    if (ok) {
        peer->attempts++;
        peer->target_matches++;
        if (attempt->kind == BREAK_WORLD_DELTA_WIRE_FULL) peer->full_attempts++;
        if (attempt->kind == BREAK_WORLD_DELTA_WIRE_DELTA) peer->delta_attempts++;
    }
    peer->duplicate_fragments = stats_after.bridge.duplicate_fragments;
    break_world_snapshot_release(rebuilt);
    break_world_snapshot_release(queued);
    break_world_snapshot_release(before);
    return ok;
}

static bool world_encode_message(BreakWorldDeltaWire *message, u8 **out_wire, usize *out_size) {
    usize size = 0u;
    u8 *wire;
    bool ok;
    if (break_world_delta_wire_encoded_size(message, &size) != BREAK_WORLD_DELTA_WIRE_OK) {
        free(message->records);
        return false;
    }
    wire = (u8 *)malloc(size);
    if (!wire) {
        free(message->records);
        return false;
    }
    ok = break_world_delta_wire_encode(message, wire, size, &size) == BREAK_WORLD_DELTA_WIRE_OK;
    free(message->records);
    if (!ok) {
        free(wire);
        return false;
    }
    *out_wire = wire;
    *out_size = size;
    return true;
}

static bool world_encode_full(const WorldPeer *peer, const BreakWorldSnapshot *snapshot,
                              u8 **out_wire, usize *out_size) {
    BreakWorldDeltaWire message;
    usize entity_count = break_world_snapshot_entity_count(snapshot);
    usize count = 0u;
    usize slot = 0u;
    memset(&message, 0, sizeof(message));
    for (usize i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        count++;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component, &bytes, &size)) {
                count++;
            }
        }
    }
    if (count > UINT32_MAX) return false;
    message.kind = BREAK_WORLD_DELTA_WIRE_FULL;
    message.schema_hash = break_world_snapshot_schema_hash(snapshot);
    message.level_generation = peer->level_generation;
    message.target_snapshot_id = break_world_snapshot_id(snapshot);
    message.target_tick = break_world_snapshot_tick(snapshot);
    message.record_count = (u32)count;
    message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
    if (count != 0u && !message.records) return false;
    for (usize i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        message.records[slot].kind = BREAK_DELTA_ENTITY_CREATE;
        message.records[slot].entity = entity;
        slot++;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component, &bytes, &size)) {
                message.records[slot].kind = BREAK_DELTA_COMPONENT_ADD;
                message.records[slot].entity = entity;
                message.records[slot].component = component;
                message.records[slot].bytes = bytes;
                message.records[slot].size = size;
                slot++;
            }
        }
    }
    return world_encode_message(&message, out_wire, out_size);
}

static bool world_encode_delta(const WorldPeer *peer, const BreakWorldSnapshot *base,
                               const BreakWorldSnapshot *target, u8 **out_wire, usize *out_size) {
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    BreakWorldDeltaWire message;
    usize count;
    bool ok;
    if (!delta) return false;
    count = break_world_delta_record_count(delta);
    if (count > UINT32_MAX) {
        break_world_delta_release(delta);
        return false;
    }
    memset(&message, 0, sizeof(message));
    message.kind = BREAK_WORLD_DELTA_WIRE_DELTA;
    message.schema_hash = break_world_delta_target_schema_hash(delta);
    message.level_generation = peer->level_generation;
    message.base_snapshot_id = break_world_delta_base_id(delta);
    message.target_snapshot_id = break_world_delta_target_id(delta);
    message.base_tick = break_world_delta_base_tick(delta);
    message.target_tick = break_world_delta_target_tick(delta);
    message.record_count = (u32)count;
    message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
    if (count != 0u && !message.records) {
        break_world_delta_release(delta);
        return false;
    }
    for (usize i = 0u; i < count; ++i) {
        if (!break_world_delta_record_at(delta, i, &message.records[i])) {
            free(message.records);
            break_world_delta_release(delta);
            return false;
        }
    }
    ok = world_encode_message(&message, out_wire, out_size);
    break_world_delta_release(delta);
    return ok;
}

static bool world_send_packet(NetClient *c, WorldPeer *peer, u64 delta_id,
                              const u8 *payload, usize payload_size, bool duplicate) {
    BreakReplicationFragment *fragments = NULL;
    usize fragment_count = 0u;
    bool sent = true;
    if (break_replication_fragment_payload(delta_id, peer->epoch, payload, payload_size,
                                           NET_CLIENT_WORLD_FRAGMENT_BYTES, &fragments,
                                           &fragment_count) != BREAK_REPLICATION_FRAGMENT_OK ||
        fragment_count < 2u || fragment_count > NET_CLIENT_WORLD_MAX_FRAGMENTS) {
        break_replication_fragments_free(fragments, fragment_count);
        return false;
    }
    for (usize i = fragment_count; i-- > 0u && sent;) {
        u8 wire[BREAK_REPLICATION_WIRE_HEADER_SIZE + NET_CLIENT_WORLD_FRAGMENT_BYTES];
        usize wire_size = 0u;
        sent = break_replication_wire_encode(&fragments[i], wire, sizeof(wire), &wire_size) ==
                   BREAK_REPLICATION_FRAGMENT_OK &&
               client_send(c, BREAK_NET_MESSAGE_ID_WORLD_DELTA, BREAK_REPLICATION_WIRE_VERSION,
                           wire, wire_size);
        if (sent) peer->outbound_fragments++;
        if (sent && duplicate && i == fragment_count - 1u) {
            wire_size = 0u;
            sent = break_replication_wire_encode(&fragments[i], wire, sizeof(wire), &wire_size) ==
                       BREAK_REPLICATION_FRAGMENT_OK &&
                   client_send(c, BREAK_NET_MESSAGE_ID_WORLD_DELTA,
                               BREAK_REPLICATION_WIRE_VERSION, wire, wire_size);
            if (sent) peer->outbound_duplicates++;
        }
    }
    break_replication_fragments_free(fragments, fragment_count);
    return sent;
}

static void scenario_world(void) {
    NetClient a;
    WorldPeer peer;
    CoreAppSnapshot snapshot;
    WorldAttempt full;
    WorldAttempt delta;
    BreakWorldSnapshot *base = NULL;
    BreakWorldSnapshot *target = NULL;
    u8 *wire = NULL;
    usize wire_size = 0u;
    bool connected;
    bool authenticated = false;
    bool initialized = false;
    bool got_full = false;
    bool got_delta = false;
    int got = -1;
    memset(&a, 0, sizeof(a));
    memset(&peer, 0, sizeof(peer));
    a.fd = -1;
    connected = client_open(&a);
    check(connected, "world_tls_challenge");
    if (connected) authenticated = client_auth(&a, g_psk);
    check(authenticated, "world_auth_sent");
    if (authenticated) got = client_next_snapshot(&a, &snapshot, 15000u);
    check(got == 1, "world_received_snapshot");
    if (got == 1) {
        check(snapshot_shape_ok(&snapshot), "world_snapshot_fields");
        check_welcome(&a, "world");
        initialized = world_peer_init(&peer, snapshot.level_generation);
    }
    check(initialized, "world_local_session_and_diagnostic_world");
    if (initialized && g_failures == 0) {
        got_full = world_receive_attempt(&a, &peer, &full);
        check(got_full && full.kind == BREAK_WORLD_DELTA_WIRE_FULL,
              "world_received_server_full");
        if (got_full) {
            check(world_send_control(&a, &peer, BREAK_WORLD_SESSION_CONTROL_ACK, &full),
                  "world_acknowledged_server_full_uncorrelated_v2");
            got_delta = world_receive_attempt(&a, &peer, &delta);
            check(got_delta && delta.kind == BREAK_WORLD_DELTA_WIRE_DELTA &&
                      delta.base_snapshot_id == full.target_snapshot_id,
                  "world_tick_published_delta_from_acknowledged_baseline");
        }
    }
    if (got_delta && g_failures == 0) {
        bool sent;
        base = break_world_snapshot_build(peer.world, peer.schemas, delta.target_tick + 10u);
        check(base != NULL, "world_prepared_inbound_full_target");
        sent = base && world_encode_full(&peer, base, &wire, &wire_size);
        check(sent, "world_encoded_inbound_full");
        if (sent) {
            sent = world_send_packet(&a, &peer, 100u, wire, wire_size, true);
            if (sent) peer.outbound_full++;
        }
        check(sent, "world_sent_reversed_duplicate_inbound_full");
        free(wire);
        wire = NULL;
        if (sent) {
            sent = world_wait_control(&a, &peer, BREAK_WORLD_SESSION_CONTROL_ACK, 100u,
                                      break_world_snapshot_id(base),
                                      break_world_snapshot_tick(base));
            check(sent, "world_server_drained_inbound_full_to_diagnostic_target");
        }
        if (!sent) goto report;
    }
    if (got_delta && g_failures == 0) {
        u32 *index = (u32 *)world_get_component(peer.world, (Entity){1u, 1u}, 1u);
        bool sent;
        check(index != NULL, "world_prepared_changed_diagnostic_target");
        if (!index) goto report;
        *index += 1000u;
        target = break_world_snapshot_build(peer.world, peer.schemas,
                                            break_world_snapshot_tick(base) + 10u);
        check(target != NULL, "world_built_changed_target");
        sent = target && world_encode_delta(&peer, base, target, &wire, &wire_size);
        if (sent && wire_size > 24u) wire[24] ^= 1u;
        check(sent && wire_size > 24u, "world_encoded_base_mismatch_delta");
        if (sent) {
            sent = world_send_packet(&a, &peer, 101u, wire, wire_size, false);
            if (sent) peer.outbound_delta++;
        }
        check(sent, "world_sent_base_mismatch_delta");
        free(wire);
        wire = NULL;
        if (sent) {
            sent = world_wait_control(&a, &peer, BREAK_WORLD_SESSION_CONTROL_NEED_FULL, 0u,
                                      break_world_snapshot_id(base),
                                      break_world_snapshot_tick(base));
            check(sent, "world_base_mismatch_requested_full_with_last_good_baseline");
            if (sent) peer.need_full++;
        }
        if (!sent) goto report;
        sent = world_encode_full(&peer, target, &wire, &wire_size);
        check(sent, "world_encoded_recovery_full");
        if (sent) {
            sent = world_send_packet(&a, &peer, 102u, wire, wire_size, false);
            if (sent) peer.outbound_full++;
        }
        check(sent, "world_sent_recovery_full");
        free(wire);
        wire = NULL;
        if (sent) {
            sent = world_wait_control(&a, &peer, BREAK_WORLD_SESSION_CONTROL_ACK, 102u,
                                      break_world_snapshot_id(target),
                                      break_world_snapshot_tick(target));
            check(sent, "world_recovery_full_rebuilt_diagnostic_target");
            if (sent) peer.recovered++;
        }
        if (sent) {
            sent = world_controls_finished(&a, &peer);
            check(sent, "world_server_controls_quiesced_without_duplicates");
        }
    }

report:
    free(wire);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    fprintf(g_report,
            "world_receiver attempts=%llu full=%llu delta=%llu target_matches=%llu pre_drain=%llu"
            " duplicates=%llu reversed=%llu\n",
            (unsigned long long)peer.attempts, (unsigned long long)peer.full_attempts,
            (unsigned long long)peer.delta_attempts, (unsigned long long)peer.target_matches,
            (unsigned long long)peer.pre_drain_unchanged,
            (unsigned long long)peer.duplicate_fragments,
            (unsigned long long)peer.reversed_fragments);
    fprintf(g_report,
            "world_sender full=%llu delta=%llu fragments=%llu duplicates=%llu need_full=%llu"
            " recovered=%llu\n",
            (unsigned long long)peer.outbound_full, (unsigned long long)peer.outbound_delta,
            (unsigned long long)peer.outbound_fragments,
            (unsigned long long)peer.outbound_duplicates, (unsigned long long)peer.need_full,
            (unsigned long long)peer.recovered);
    fprintf(g_report, "world_controls server=%u correlated=%u client_uncorrelated=%u\n",
            peer.server_control_count, peer.correlated_control_count, peer.client_control_count);
    client_close(&a);
    world_peer_dispose(&peer);
}

/* A: authenticated peer. Receives snapshots, then sends hostile snapshots
 * that must only change counters and must not close the session. */
static void scenario_authenticated(void) {
    NetClient a;
    CoreAppSnapshot first, later, forged;
    check(client_open(&a), "a_tls_challenge");
    check(client_auth(&a, g_psk), "a_auth_sent");
    int got = client_next_snapshot(&a, &first, 15000u);
    check(got == 1, "a_received_snapshot");
    check_welcome(&a, "a");
    {
        /* A welcome sent the other way has no handler on the server: it is
         * counted and the session stays open (A keeps working below). */
        u8 welcome[CORE_APP_SESSION_WELCOME_BYTES];
        size_t welcome_size = 0u;
        check(core_app_session_welcome_encode(a.session_id ? a.session_id : 1u, welcome,
                                              sizeof(welcome), &welcome_size) ==
                      CORE_APP_SNAPSHOT_OK &&
                  client_send(&a, CORE_APP_SESSION_WELCOME_MESSAGE_ID, 1u, welcome,
                              welcome_size),
              "a_sent_welcome_to_server");
    }
    if (got == 1) {
        check(snapshot_shape_ok(&first), "a_snapshot_fields");
        fprintf(g_report,
                "snapshot frame=%llu generation=%llu user_index=%u user_generation=%u"
                " chaser_index=%u chaser_generation=%u\n",
                (unsigned long long)first.frame_id, (unsigned long long)first.level_generation,
                first.entities[0].index, first.entities[0].generation, first.entities[1].index,
                first.entities[1].generation);
        forged = first;
        forged.level_generation = first.level_generation + 100u;
        check(send_snapshot(&a, &forged, 0u), "a_sent_stale_generation");
        forged = first;
        forged.schema_hash ^= 0x5a5a5a5au;
        check(send_snapshot(&a, &forged, 0u), "a_sent_forged_schema");
        forged = first;
        forged.entities[0].x = 9999.0f;
        forged.entities[0].z = -9999.0f;
        check(send_snapshot(&a, &forged, 16u), "a_sent_forged_position_with_trailing_bytes");
        /* Current generation and schema, forged position, exact length: the
         * firewall admits it as a diagnostic, and the driver still requires
         * the networked trace to match the offline one. */
        check(send_snapshot(&a, &forged, 0u), "a_sent_admissible_forged_position");
        /* A second authenticated peer that never reports a desync must not
         * receive the correction A asks for. */
        NetClient a2;
        CoreAppSnapshot a2_first;
        check(client_open(&a2), "a2_tls_challenge");
        check(client_auth(&a2, g_psk), "a2_auth_sent");
        check(client_next_snapshot(&a2, &a2_first, 10000u) == 1, "a2_authenticated");
        check_welcome(&a2, "a2");
        check(a2.session_id != a.session_id, "a2_session_differs_from_a");
        /* Echo the authority's own physics report (a match), then the same
         * report with a flipped hash (a desync), then a short payload. */
        u8 report[NET_CLIENT_PHYSICS_REPORT_BYTES];
        got = client_next_physics_report(&a, report, 10000u);
        check(got == 1, "a_received_physics_report");
        if (got == 1) {
            fprintf(g_report, "physics_report tick=%u\n", le32(report + 4u));
            check(client_send(&a, BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, 1u, report,
                              sizeof(report)),
                  "a_sent_matching_physics_report");
            report[8] ^= 0xffu;
            check(client_send(&a, BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, 1u, report,
                              sizeof(report)),
                  "a_sent_desynced_physics_report");
            check(client_send(&a, BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, 1u, report,
                              sizeof(report)),
                  "a_sent_repeated_desynced_physics_report");
            check(client_send(&a, BREAK_NET_MESSAGE_ID_PHYSICS_SYNC_REPORT, 1u, report,
                              sizeof(report) - 1u),
                  "a_sent_short_physics_report");
            u32 correction_tick = 0u;
            size_t correction_bytes = 0u;
            check(client_next_physics_correction(&a, &correction_tick, &correction_bytes,
                                                 10000u) == 1,
                  "a_received_physics_correction");
            fprintf(g_report, "physics_correction tick=%u bytes=%zu\n", correction_tick,
                    correction_bytes);
            check(client_apply_correction("physics_correction", correction_tick,
                                          correction_bytes),
                  "a_applied_physics_correction");
            check(!client_receives_correction_before(&a2, correction_tick, 10000u),
                  "a2_never_receives_correction");
            client_delta_correction_exchange(&a, correction_bytes);
            client_release_world();
        }
        client_clock_probe_exchange(&a);
        client_close(&a2);
        /* Wait for a frame built well after the hostile sends: the outbox
         * may already hold the next few frames, and closing with those
         * hostile bytes still unread by the server would let the RST from
         * close() drop them. */
        bool advanced = false;
        u64 deadline = now_ms() + 10000u;
        while (!advanced && now_ms() < deadline) {
            if (client_next_snapshot(&a, &later, 2000u) != 1) break;
            advanced = later.frame_id >= first.frame_id + 60u &&
                       later.level_generation == first.level_generation &&
                       snapshot_shape_ok(&later) && later.entities[0].x != 9999.0f;
        }
        check(advanced, "a_session_survives_and_frames_advance");
    }
    client_close(&a);
}

/* B: TLS but no AUTH. A snapshot from it is phase-rejected, and it must
 * never receive one. */
static void scenario_unauthenticated(void) {
    NetClient b;
    CoreAppSnapshot snapshot, probe;
    memset(&snapshot, 0, sizeof(snapshot));
    check(client_open(&b), "b_tls_challenge");
    core_app_snapshot_build(&snapshot, 1u, 1u, core_app_snapshot_schema_hash(), NULL, 0u);
    check(send_snapshot(&b, &snapshot, 0u), "b_sent_unauthenticated_snapshot");
    /* 0 means the probe timed out with the connection still open; a closed
     * connection (-1) would also hide a snapshot, so it does not count. */
    check(client_next_snapshot(&b, &probe, 1500u) == 0, "b_never_receives_snapshot_and_stays_open");
    client_close(&b);
}

/* C: an unregistered message id closes the connection. */
static void scenario_unknown_id(void) {
    NetClient c;
    check(client_open(&c), "c_tls_challenge");
    check(client_send_raw_id(&c, 0x7777u), "c_sent_unknown_id");
    check(client_closed_without_snapshot(&c, 5000u), "c_closed_after_unknown_id");
    client_close(&c);
}

/* D: AUTH with the wrong key closes the connection without a snapshot. */
static void scenario_wrong_psk(void) {
    NetClient d;
    u8 wrong[32];
    memcpy(wrong, g_psk, sizeof(wrong));
    wrong[0] ^= 0xffu;
    check(client_open(&d), "d_tls_challenge");
    check(client_auth(&d, wrong), "d_sent_wrong_auth");
    check(client_closed_without_snapshot(&d, 5000u), "d_closed_after_wrong_psk");
    client_close(&d);
}

/* E: TLS but no AUTH and no traffic. The server closes it once the
 * authentication deadline passes. */
static void scenario_auth_deadline(void) {
    NetClient e;
    check(client_open(&e), "e_tls_challenge");
    check(client_closed_without_snapshot(&e, 10000u), "e_closed_after_auth_deadline");
    client_close(&e);
}

/* F: a second authenticated peer at the end. Receiving a snapshot proves
 * the server was still running, so the closures in C, D and E were
 * decisions of a live server and not its shutdown. */
static void scenario_alive_at_end(void) {
    NetClient f;
    CoreAppSnapshot snapshot;
    check(client_open(&f), "f_tls_challenge");
    check(client_auth(&f, g_psk), "f_auth_sent");
    check(client_next_snapshot(&f, &snapshot, 5000u) == 1, "f_server_alive_at_end");
    check_welcome(&f, "f");
    client_close(&f);
}

/* G: TLS, then a pause of about one second, then AUTH. The deadline is
 * measured in wall-clock time, so a server that ticks every millisecond
 * must still accept a peer that authenticates within it. */
static void scenario_late_auth(void) {
    NetClient g;
    CoreAppSnapshot snapshot;
    struct timespec pause = {1, 0};
    check(client_open(&g), "g_tls_challenge");
    nanosleep(&pause, NULL);
    check(client_auth(&g, g_psk), "g_auth_sent_after_pause");
    check(client_next_snapshot(&g, &snapshot, 5000u) == 1, "g_receives_snapshot_after_late_auth");
    check_welcome(&g, "g");
    client_close(&g);
}

/* S: one connection, one session, nothing else. With --trace this produces
 * a document naming exactly one session, which is what trace_merge's
 * self-naming path expects (design 2026-11-20-single-session-peer). */
static void scenario_single(void) {
    NetClient s;
    CoreAppSnapshot snapshot;
    check(client_open(&s), "s_tls_challenge");
    check(client_auth(&s, g_psk), "s_auth_sent");
    check(client_next_snapshot(&s, &snapshot, 15000u) == 1, "s_received_snapshot");
    check_welcome(&s, "s");
    /* the server traces an offset only after enough accepted samples, so
     * answer its probes until it has them */
    check(client_answer_server_probes(&s, 4u, 4u, 20000u), "s_answered_server_probes");
    fprintf(g_report, "single probes_answered=%u\n", g_server_probes_answered);
    client_close(&s);
}

/* V: authenticates, then decodes the server's voice messages through a
 * real BreakVoiceReceiver. Every message must be version 1, BRV2 mono
 * 48 kHz with 480 samples at the exact ADPCM size, in consecutive
 * sequence. */
#define NET_CLIENT_VOICE_FRAMES 30u
#define NET_CLIENT_VOICE_BACK_FRAMES 20u

/* 20 consecutive BRV2 frames (sequences first..first+19) of a 0.25 square
 * tone, then a duplicate of the last one and one frame that claims 16 kHz. */
static void tone_frame_init(BreakVoiceFrame *frame) {
    memset(frame, 0, sizeof(*frame));
    frame->sample_rate = 48000u;
    frame->channels = 1u;
    frame->sample_count = BREAK_VOICE_MAX_SAMPLES;
    for (u32 i = 0u; i < BREAK_VOICE_MAX_SAMPLES; ++i) {
        frame->samples[i] = (i / 24u) % 2u == 0u ? (i16)8191 : (i16)-8191;
    }
}

static bool client_send_tone_burst(NetClient *c, u32 first) {
    BreakVoiceFrame back;
    u8 wire[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u32 wire_size = 0u;
    bool sent = true;
    tone_frame_init(&back);
    for (u32 i = 0u; i < NET_CLIENT_VOICE_BACK_FRAMES && sent; ++i) {
        back.sequence = first + i;
        sent = break_voice_encode_adpcm(&back, wire, sizeof(wire), &wire_size) ==
                   BREAK_RUNTIME_OK &&
               client_send(c, BREAK_NET_MESSAGE_ID_CORE_VOICE, 1u, wire, wire_size);
    }
    sent = sent && client_send(c, BREAK_NET_MESSAGE_ID_CORE_VOICE, 1u, wire, wire_size);
    wire[8] = 0x80u;
    wire[9] = 0x3eu;
    wire[10] = 0u;
    wire[11] = 0u;
    return sent && client_send(c, BREAK_NET_MESSAGE_ID_CORE_VOICE, 1u, wire, wire_size);
}

/* Relay messages one peer received, decoded through its own receiver. */
typedef struct RelayTally {
    BreakVoiceReceiver *receiver;
    u64 expected_source;
    u32 received;
    u32 foreign;
    u32 gaps;
    u32 malformed;
    u32 played;
    u32 next;
    u32 peak;
} RelayTally;

static void relay_tally_add(RelayTally *tally, const BreakNetEnvelope *env) {
    u64 source = 0u;
    const u8 *bytes = NULL;
    size_t size = 0u;
    tally->received++;
    if (env->protocol_version != 1u ||
        core_app_voice_relay_decode((const u8 *)env->payload, env->payload_size, &source,
                                    &bytes, &size) != CORE_APP_SNAPSHOT_OK ||
        size != BREAK_VOICE_ADPCM_SIZE(1u, BREAK_VOICE_MAX_SAMPLES) ||
        memcmp(bytes, "BRV2", 4u) != 0 || le32(bytes + 8u) != 48000u) {
        tally->malformed++;
        return;
    }
    if (source != tally->expected_source) tally->foreign++;
    u32 sequence = le32(bytes + 4u);
    if (sequence != tally->next) tally->gaps++;
    tally->next = sequence + 1u;
    const u64 virtual_ms = (u64)sequence * 10u;
    if (!tally->receiver ||
        break_voice_receiver_push(tally->receiver, bytes, (u32)size) != BREAK_RUNTIME_OK ||
        break_voice_receiver_pump(tally->receiver, 8u, virtual_ms) != BREAK_RUNTIME_OK) {
        tally->malformed++;
        return;
    }
    for (;;) {
        BreakVoicePlayback playback;
        bool ready = false;
        if (break_voice_receiver_pop(tally->receiver, virtual_ms, &playback, &ready) !=
                BREAK_RUNTIME_OK ||
            !ready) {
            break;
        }
        if (playback.concealed) continue;
        tally->played++;
        for (u32 i = 0u; i < playback.sample_count; ++i) {
            i32 sample = playback.samples[i];
            u32 magnitude = (u32)(sample < 0 ? -sample : sample);
            if (magnitude > tally->peak) tally->peak = magnitude;
        }
    }
}

/* Sends a clock probe and reads until its reply, adding every relay
 * message on the way to the tally. The server applies one session's
 * messages in order and sends relays before clock replies, so the reply
 * follows everything this peer sent and every relay queued before it. */
static bool client_barrier(NetClient *c, RelayTally *tally, u32 timeout_ms) {
    CoreAppClockProbe probe = {CORE_APP_CLOCK_PROBE_REQUEST, 0u, 0u, 0u};
    probe.t0 = now_us();
    if (!send_clock_probe(c, &probe, CORE_APP_CLOCK_PROBE_BYTES)) return false;
    u64 deadline = now_ms() + timeout_ms;
    for (;;) {
        u64 now = now_ms();
        if (now >= deadline) return false;
        BreakNetEnvelope env;
        CoreAppClockProbe reply;
        if (client_recv(c, &env, (u32)(deadline - now)) != 1) return false;
        if (env.message_id == CORE_APP_VOICE_RELAY_MESSAGE_ID) {
            relay_tally_add(tally, &env);
            continue;
        }
        if (env.message_id == CORE_APP_CLOCK_PROBE_MESSAGE_ID &&
            core_app_clock_probe_decode((const u8 *)env.payload, env.payload_size, &reply) ==
                CORE_APP_SNAPSHOT_OK &&
            reply.kind == CORE_APP_CLOCK_PROBE_REPLY && reply.t0 == probe.t0) {
            return true;
        }
    }
    return false;
}

static BreakVoiceReceiver *relay_receiver_create(void) {
    BreakVoiceReceiver *receiver = NULL;
    BreakVoiceStreamConfig config;
    memset(&config, 0, sizeof(config));
    config.sample_rate = 48000u;
    config.channels = 1u;
    config.sample_count = BREAK_VOICE_MAX_SAMPLES;
    config.jitter_capacity = 8u;
    config.queue_capacity = 8u;
    return break_voice_receiver_create(NULL, &config, &receiver) == BREAK_RUNTIME_OK ? receiver
                                                                                    : NULL;
}

/* R: two peers. A sends the tone burst; with --voice-relay the server must
 * forward the 20 frames it accepted to B, tagged with A's session, and
 * none back to A. B also sends a relay message to the server, which has no
 * handler for it and must keep B connected. The driver checks the counts
 * against the server's mode. */
static void scenario_voice_relay(void) {
    NetClient a;
    NetClient b;
    CoreAppSnapshot snapshot;
    RelayTally at_a;
    RelayTally at_b;
    memset(&at_a, 0, sizeof(at_a));
    memset(&at_b, 0, sizeof(at_b));
    at_a.receiver = relay_receiver_create();
    at_b.receiver = relay_receiver_create();
    check(at_a.receiver && at_b.receiver, "r_receivers_created");
    check(client_open(&a), "ra_tls_challenge");
    check(client_auth(&a, g_psk), "ra_auth_sent");
    check(client_next_snapshot(&a, &snapshot, 10000u) == 1, "ra_authenticated");
    check_welcome(&a, "ra");
    check(client_open(&b), "rb_tls_challenge");
    check(client_auth(&b, g_psk), "rb_auth_sent");
    check(client_next_snapshot(&b, &snapshot, 10000u) == 1, "rb_authenticated");
    check_welcome(&b, "rb");
    check(a.session_id != b.session_id, "rb_session_differs_from_ra");
    at_a.expected_source = a.session_id;
    at_b.expected_source = a.session_id;
    check(client_send_tone_burst(&a, 0u), "ra_sent_voice_to_server");
    check(client_barrier(&a, &at_a, 10000u), "ra_server_handled_voice");
    {
        static const u8 frame[4] = {'B', 'R', 'V', '2'};
        u8 wire[CORE_APP_VOICE_RELAY_MAX_BYTES];
        size_t size = 0u;
        check(core_app_voice_relay_encode(b.session_id ? b.session_id : 1u, frame,
                                          sizeof(frame), wire, sizeof(wire), &size) ==
                      CORE_APP_SNAPSHOT_OK &&
                  client_send(&b, CORE_APP_VOICE_RELAY_MESSAGE_ID, 1u, wire, size),
              "rb_sent_relay_to_server");
    }
    check(client_barrier(&b, &at_b, 10000u), "rb_session_survives_relay_to_server");
    check(at_a.received == 0u, "ra_never_receives_own_voice");
    fprintf(g_report,
            "voice_relay received=%u foreign=%u gaps=%u malformed=%u played=%u peak=%u"
            " echoed=%u\n",
            at_b.received, at_b.foreign, at_b.gaps, at_b.malformed, at_b.played, at_b.peak,
            at_a.received);
    client_close(&b);
    client_close(&a);
    if (at_a.receiver) break_voice_receiver_destroy(at_a.receiver);
    if (at_b.receiver) break_voice_receiver_destroy(at_b.receiver);
}

static bool client_send_mute(NetClient *c, u64 target, bool muted) {
    u8 wire[CORE_APP_VOICE_MUTE_BYTES];
    size_t size = 0u;
    return core_app_voice_mute_encode(target, muted, wire, sizeof(wire), &size) ==
               CORE_APP_SNAPSHOT_OK &&
           client_send(c, CORE_APP_VOICE_MUTE_MESSAGE_ID, 1u, wire, size);
}

/* M: two peers on a --voice-relay server. B sends a malformed mute, then
 * mutes A twice; A's first burst (sequences 0..19) must not reach B. One
 * unmute clears A (the repeated mute was not stored twice), B then mutes
 * 17 unknown ids (the last is rejected: the list holds 16), and A's
 * second burst (20..39) must reach B in full. */
static void scenario_voice_mute(void) {
    NetClient a;
    NetClient b;
    CoreAppSnapshot snapshot;
    RelayTally at_a;
    RelayTally muted;
    RelayTally unmuted;
    memset(&at_a, 0, sizeof(at_a));
    memset(&muted, 0, sizeof(muted));
    memset(&unmuted, 0, sizeof(unmuted));
    at_a.receiver = relay_receiver_create();
    muted.receiver = relay_receiver_create();
    unmuted.receiver = relay_receiver_create();
    check(at_a.receiver && muted.receiver && unmuted.receiver, "m_receivers_created");
    check(client_open(&a), "ma_tls_challenge");
    check(client_auth(&a, g_psk), "ma_auth_sent");
    check(client_next_snapshot(&a, &snapshot, 10000u) == 1, "ma_authenticated");
    check_welcome(&a, "ma");
    check(client_open(&b), "mb_tls_challenge");
    check(client_auth(&b, g_psk), "mb_auth_sent");
    check(client_next_snapshot(&b, &snapshot, 10000u) == 1, "mb_authenticated");
    check_welcome(&b, "mb");
    at_a.expected_source = a.session_id;
    muted.expected_source = a.session_id;
    unmuted.expected_source = a.session_id;
    unmuted.next = NET_CLIENT_VOICE_BACK_FRAMES;
    {
        u8 wire[CORE_APP_VOICE_MUTE_BYTES];
        size_t size = 0u;
        bool built = core_app_voice_mute_encode(a.session_id ? a.session_id : 1u, true, wire,
                                                sizeof(wire), &size) == CORE_APP_SNAPSHOT_OK;
        wire[4] = 0x03u;
        check(built && client_send(&b, CORE_APP_VOICE_MUTE_MESSAGE_ID, 1u, wire, size),
              "mb_sent_malformed_mute");
    }
    check(client_send_mute(&b, a.session_id, true), "mb_sent_mute");
    check(client_send_mute(&b, a.session_id, true), "mb_sent_repeated_mute");
    check(client_barrier(&b, &muted, 10000u), "mb_server_applied_mute");
    check(client_send_tone_burst(&a, 0u), "ma_sent_first_burst");
    check(client_barrier(&a, &at_a, 10000u), "ma_server_handled_first_burst");
    check(client_barrier(&b, &muted, 10000u), "mb_barrier_after_first_burst");
    check(client_send_mute(&b, a.session_id, false), "mb_sent_unmute");
    {
        /* Ids no peer holds fill the 16-entry list; the 17th is rejected.
         * A is no longer in the list, so its second burst still reaches B. */
        bool sent = true;
        for (u64 i = 0u; i < 17u && sent; ++i) {
            sent = client_send_mute(&b, 1000000u + i, true);
        }
        check(sent, "mb_sent_mutes_past_capacity");
    }
    check(client_barrier(&b, &unmuted, 10000u), "mb_server_applied_unmute");
    check(client_send_tone_burst(&a, NET_CLIENT_VOICE_BACK_FRAMES), "ma_sent_second_burst");
    check(client_barrier(&a, &at_a, 10000u), "ma_server_handled_second_burst");
    check(client_barrier(&b, &unmuted, 10000u), "mb_barrier_after_second_burst");
    check(at_a.received == 0u, "ma_never_receives_own_voice");
    fprintf(g_report, "voice_mute muted_received=%u\n", muted.received);
    fprintf(g_report,
            "voice_unmute received=%u foreign=%u gaps=%u malformed=%u played=%u peak=%u"
            " first=%u echoed=%u\n",
            unmuted.received, unmuted.foreign, unmuted.gaps, unmuted.malformed,
            unmuted.played, unmuted.peak, unmuted.next - unmuted.received, at_a.received);
    client_close(&b);
    client_close(&a);
    if (at_a.receiver) break_voice_receiver_destroy(at_a.receiver);
    if (muted.receiver) break_voice_receiver_destroy(muted.receiver);
    if (unmuted.receiver) break_voice_receiver_destroy(unmuted.receiver);
}

/* F: two peers on a --voice-relay server. A sends 200 consecutive frames
 * as fast as TLS allows, far above the server's voice rate limit. The
 * session must stay open, and B must receive exactly the frames the
 * server relayed (the driver compares the counts with network_stats). */
#define NET_CLIENT_VOICE_FLOOD_FRAMES 200u
static void scenario_voice_flood(void) {
    NetClient a;
    NetClient b;
    CoreAppSnapshot snapshot;
    RelayTally at_a;
    RelayTally at_b;
    memset(&at_a, 0, sizeof(at_a));
    memset(&at_b, 0, sizeof(at_b));
    at_a.receiver = relay_receiver_create();
    at_b.receiver = relay_receiver_create();
    check(at_a.receiver && at_b.receiver, "f_receivers_created");
    check(client_open(&a), "fa_tls_challenge");
    check(client_auth(&a, g_psk), "fa_auth_sent");
    check(client_next_snapshot(&a, &snapshot, 10000u) == 1, "fa_authenticated");
    check_welcome(&a, "fa");
    check(client_open(&b), "fb_tls_challenge");
    check(client_auth(&b, g_psk), "fb_auth_sent");
    check(client_next_snapshot(&b, &snapshot, 10000u) == 1, "fb_authenticated");
    check_welcome(&b, "fb");
    at_a.expected_source = a.session_id;
    at_b.expected_source = a.session_id;
    {
        BreakVoiceFrame frame;
        u8 wire[BREAK_VOICE_MAX_DATAGRAM_SIZE];
        u32 wire_size = 0u;
        bool sent = true;
        tone_frame_init(&frame);
        for (u32 i = 0u; i < NET_CLIENT_VOICE_FLOOD_FRAMES && sent; ++i) {
            frame.sequence = i;
            sent = break_voice_encode_adpcm(&frame, wire, sizeof(wire), &wire_size) ==
                       BREAK_RUNTIME_OK &&
                   client_send(&a, BREAK_NET_MESSAGE_ID_CORE_VOICE, 1u, wire, wire_size);
        }
        check(sent, "fa_sent_voice_flood");
    }
    check(client_barrier(&a, &at_a, 15000u), "fa_session_survives_flood");
    check(client_barrier(&b, &at_b, 15000u), "fb_barrier_after_flood");
    check(at_a.received == 0u, "fa_never_receives_own_voice");
    fprintf(g_report, "voice_flood relayed_received=%u foreign=%u malformed=%u echoed=%u\n",
            at_b.received, at_b.foreign, at_b.malformed, at_a.received);
    client_close(&b);
    client_close(&a);
    if (at_a.receiver) break_voice_receiver_destroy(at_a.receiver);
    if (at_b.receiver) break_voice_receiver_destroy(at_b.receiver);
}

static void scenario_voice(void) {
    NetClient v;
    CoreAppSnapshot snapshot;
    BreakVoiceReceiver *receiver = NULL;
    BreakVoiceStreamConfig config;
    memset(&config, 0, sizeof(config));
    config.sample_rate = 48000u;
    config.channels = 1u;
    config.sample_count = BREAK_VOICE_MAX_SAMPLES;
    config.jitter_delay_ms = 0u;
    config.jitter_capacity = 8u;
    config.queue_capacity = 8u;
    check(break_voice_receiver_create(NULL, &config, &receiver) == BREAK_RUNTIME_OK,
          "v_receiver_created");
    check(client_open(&v), "v_tls_challenge");
    check(client_auth(&v, g_psk), "v_auth_sent");
    check(client_next_snapshot(&v, &snapshot, 10000u) == 1, "v_authenticated");
    check_welcome(&v, "v");
    u32 frames = 0u;
    u32 gaps = 0u;
    u32 malformed = 0u;
    u32 played = 0u;
    u32 next = 0u;
    u32 first = 0u;
    u32 peak = 0u;
    u64 deadline = now_ms() + 15000u;
    while (receiver && frames < NET_CLIENT_VOICE_FRAMES && now_ms() < deadline) {
        BreakNetEnvelope env;
        if (client_recv(&v, &env, (u32)(deadline - now_ms()) + 1u) != 1) break;
        if (env.message_id != BREAK_NET_MESSAGE_ID_CORE_VOICE) continue;
        const u8 *bytes = (const u8 *)env.payload;
        if (env.protocol_version != 1u ||
            env.payload_size != BREAK_VOICE_ADPCM_SIZE(1u, BREAK_VOICE_MAX_SAMPLES) ||
            memcmp(bytes, "BRV2", 4u) != 0 || le32(bytes + 8u) != 48000u ||
            bytes[12] != 1u || bytes[13] != 0u ||
            (u32)bytes[14] + ((u32)bytes[15] << 8u) != BREAK_VOICE_MAX_SAMPLES) {
            malformed++;
            continue;
        }
        u32 sequence = le32(bytes + 4u);
        if (frames == 0u) first = sequence;
        if (frames > 0u && sequence != next) gaps++;
        next = sequence + 1u;
        /* A virtual playout clock driven by the sequence: 10 ms per frame
         * since the first one. Network jitter cannot make the jitter buffer
         * conceal, and a frame the server skipped is concealed once while
         * the frame after it still plays. */
        const u64 virtual_ms = (u64)(sequence - first) * 10u;
        frames++;
        if (break_voice_receiver_push(receiver, bytes, (u32)env.payload_size) !=
                BREAK_RUNTIME_OK ||
            break_voice_receiver_pump(receiver, 8u, virtual_ms) != BREAK_RUNTIME_OK) {
            malformed++;
            continue;
        }
        for (;;) {
            BreakVoicePlayback playback;
            bool ready = false;
            if (break_voice_receiver_pop(receiver, virtual_ms, &playback, &ready) !=
                    BREAK_RUNTIME_OK ||
                !ready) {
                break;
            }
            if (playback.concealed) continue;
            played++;
            for (u32 i = 0u; i < playback.sample_count; ++i) {
                i32 sample = playback.samples[i];
                u32 magnitude = (u32)(sample < 0 ? -sample : sample);
                if (magnitude > peak) peak = magnitude;
            }
        }
    }
    check(frames == NET_CLIENT_VOICE_FRAMES, "v_received_voice_frames");
    check(malformed == 0u, "v_voice_frames_well_formed");
    check(played == frames, "v_voice_frames_decoded");
    /* The other direction: a burst of 20 consecutive BRV2 frames of a 0.25
     * square tone, then a duplicate of the last one and one frame that
     * claims 16 kHz. The server buffers them per session with a 40 ms
     * playout delay, so most of the burst is still buffered when this peer
     * closes and plays only through the tail flush. The last two count as
     * dropped and the session stays open. */
    {
        check(client_send_tone_burst(&v, 0u), "v_sent_voice_to_server");
        /* Nothing acknowledges voice, but the server applies one session's
         * messages in order: a reply to a clock probe sent after the voice
         * proves every voice message was handled before this peer closes. */
        CoreAppClockProbe probe = {CORE_APP_CLOCK_PROBE_REQUEST, 0u, 0u, 0u};
        CoreAppClockProbe reply;
        u64 t3 = 0u;
        probe.t0 = now_us();
        check(send_clock_probe(&v, &probe, CORE_APP_CLOCK_PROBE_BYTES) &&
                  client_next_clock_reply(&v, probe.t0, &reply, &t3, 10000u) == 1,
              "v_server_handled_voice_before_close");
        /* Close at once: most of the burst must still be buffered, so only
         * the tail flush can play it. The reply already shows the session
         * survived the voice. */
    }
    fprintf(g_report, "voice frames=%u gaps=%u malformed=%u played=%u peak=%u\n", frames, gaps,
            malformed, played, peak);
    client_close(&v);
    if (receiver) break_voice_receiver_destroy(receiver);
}

int main(int argc, char **argv) {
    bool late_auth = argc == 4 && strcmp(argv[3], "late-auth") == 0;
    bool voice = argc == 4 && strcmp(argv[3], "voice") == 0;
    bool voice_relay = argc == 4 && strcmp(argv[3], "voice-relay") == 0;
    bool voice_mute = argc == 4 && strcmp(argv[3], "voice-mute") == 0;
    bool voice_flood = argc == 4 && strcmp(argv[3], "voice-flood") == 0;
    bool single = argc == 4 && strcmp(argv[3], "single") == 0;
    bool aspect = argc == 4 && strcmp(argv[3], "aspect") == 0;
    bool world = argc == 4 && strcmp(argv[3], "world") == 0;
    const char *trace_path = NULL;
    /* --trace PATH may follow the arguments above */
    for (int i = 3; i + 1 < argc; ++i) {
        if (strcmp(argv[i], "--trace") == 0) {
            trace_path = argv[i + 1];
            break;
        }
    }
    if (trace_path != NULL) {
        /* the scenario name, when given, is still argv[3] */
        late_auth = argc > 4 && strcmp(argv[3], "late-auth") == 0;
        voice = argc > 4 && strcmp(argv[3], "voice") == 0;
        voice_relay = argc > 4 && strcmp(argv[3], "voice-relay") == 0;
        voice_mute = argc > 4 && strcmp(argv[3], "voice-mute") == 0;
        voice_flood = argc > 4 && strcmp(argv[3], "voice-flood") == 0;
        single = argc > 4 && strcmp(argv[3], "single") == 0;
        aspect = argc > 4 && strcmp(argv[3], "aspect") == 0;
        world = argc > 4 && strcmp(argv[3], "world") == 0;
    } else if (argc != 3 && !late_auth && !voice && !voice_relay && !voice_mute &&
               !voice_flood && !single && !aspect && !world) {
        fprintf(stderr, "usage: test_core_app_net_client PORT_FILE REPORT_FILE"
                        " [late-auth|voice|voice-relay|voice-mute|voice-flood|single|aspect|world]"
                        " [--trace PATH]\n");
        return 2;
    }
    signal(SIGPIPE, SIG_IGN);
    g_report = fopen(argv[2], "wb");
    if (!g_report) return 2;
    if (trace_path != NULL) {
        g_trace = fopen(trace_path, "wb");
        if (!g_trace) return 2;
        /* the same stamping a core_app peer's trace would carry */
        break_trace_core_app_set_clock(now_us);
    }
    check(read_psk(), "psk_from_environment");
    check(wait_port(argv[1]), "port_file_published");
    if (g_failures == 0 && late_auth) {
        scenario_late_auth();
    } else if (g_failures == 0 && voice) {
        scenario_voice();
    } else if (g_failures == 0 && voice_relay) {
        scenario_voice_relay();
    } else if (g_failures == 0 && voice_mute) {
        scenario_voice_mute();
    } else if (g_failures == 0 && voice_flood) {
        scenario_voice_flood();
    } else if (g_failures == 0 && single) {
        scenario_single();
    } else if (g_failures == 0 && aspect) {
        scenario_aspect();
    } else if (g_failures == 0 && world) {
        scenario_world();
    } else if (g_failures == 0) {
        scenario_authenticated();
        scenario_unauthenticated();
        scenario_unknown_id();
        scenario_wrong_psk();
        scenario_auth_deadline();
        scenario_alive_at_end();
    }
    fprintf(g_report, "client trace_lines=%u\n", g_trace_lines);
    fprintf(g_report, "client failures=%d\n", g_failures);
    fclose(g_report);
    if (g_trace) fclose(g_trace);
    return g_failures == 0 ? 0 : 1;
}
