/* Loopback peer for test_core_app_network_loopback, _late_auth and _voice.
 *
 * Runs next to a real core_app started with --network. Every check here is
 * about the wire: TLS, AUTH-v2, which connections receive snapshots, and
 * which hostile inputs close a connection. Whether hostile input changed
 * the simulation is checked by the CMake driver, which compares the
 * networked trace with an offline run of the same scenario. "late-auth"
 * runs only the delayed-AUTH peer; "voice" runs only the voice peer.
 *
 * Usage: test_core_app_net_client PORT_FILE REPORT_FILE [late-auth|voice]
 * The PSK is read from CORE_APP_TEST_PSK (64 hex digits). */
#define _POSIX_C_SOURCE 200809L
#include "core_app_network.h"

#include <core/clock_offset.h>
#include <crypto/break_crypto.h>
#include <network/break_net_envelope.h>
#include <network/break_net_message_registry.h>
#include <network/break_online_voice.h>
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

/* V: authenticates, then decodes the server's voice messages through a
 * real BreakVoiceReceiver. Every message must be version 1, BRV2 mono
 * 48 kHz with 480 samples at the exact ADPCM size, in consecutive
 * sequence. */
#define NET_CLIENT_VOICE_FRAMES 30u
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
    /* The server only sends voice: one sent the other way has no handler,
     * is counted by the session layer, and the session stays open. */
    {
        BreakVoiceFrame back;
        u8 wire[BREAK_VOICE_MAX_DATAGRAM_SIZE];
        u32 wire_size = 0u;
        memset(&back, 0, sizeof(back));
        back.sequence = 1u;
        back.sample_rate = 48000u;
        back.channels = 1u;
        back.sample_count = BREAK_VOICE_MAX_SAMPLES;
        check(break_voice_encode_adpcm(&back, wire, sizeof(wire), &wire_size) ==
                      BREAK_RUNTIME_OK &&
                  client_send(&v, BREAK_NET_MESSAGE_ID_CORE_VOICE, 1u, wire, wire_size),
              "v_sent_voice_to_server");
        check(client_next_snapshot(&v, &snapshot, 5000u) == 1, "v_session_survives_voice_sent");
    }
    fprintf(g_report, "voice frames=%u gaps=%u malformed=%u played=%u peak=%u\n", frames, gaps,
            malformed, played, peak);
    client_close(&v);
    if (receiver) break_voice_receiver_destroy(receiver);
}

int main(int argc, char **argv) {
    bool late_auth = argc == 4 && strcmp(argv[3], "late-auth") == 0;
    bool voice = argc == 4 && strcmp(argv[3], "voice") == 0;
    if (argc != 3 && !late_auth && !voice) {
        fprintf(stderr,
                "usage: test_core_app_net_client PORT_FILE REPORT_FILE [late-auth|voice]\n");
        return 2;
    }
    signal(SIGPIPE, SIG_IGN);
    g_report = fopen(argv[2], "wb");
    if (!g_report) return 2;
    check(read_psk(), "psk_from_environment");
    check(wait_port(argv[1]), "port_file_published");
    if (g_failures == 0 && late_auth) {
        scenario_late_auth();
    } else if (g_failures == 0 && voice) {
        scenario_voice();
    } else if (g_failures == 0) {
        scenario_authenticated();
        scenario_unauthenticated();
        scenario_unknown_id();
        scenario_wrong_psk();
        scenario_auth_deadline();
        scenario_alive_at_end();
    }
    fprintf(g_report, "client failures=%d\n", g_failures);
    fclose(g_report);
    return g_failures == 0 ? 0 : 1;
}
