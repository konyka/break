#include "network/break_net_adapter.h"
#include "network/break_net_envelope.h"
#include "network/break_net_protocol.h"
#ifdef BREAK_ENABLE_CRYPTO
#include "crypto/break_crypto.h"
#endif

#include "core/platform_thread.h"

#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(PLATFORM_THREAD_POSIX)
#include <errno.h>
#include <time.h>
extern int nanosleep(const struct timespec *, struct timespec *);
#endif

#include <snow/connection.h>
#include <snow/net_thread.h>
#include <snow/network_buffer.h>
#include <snow/openssl.h>
#include <snow/recv_context.h>
#include <snow/send_context.h>
#include <snow/socket.h>
#include <snow/ratelimiter.h>
#include <snow/freqlimiter.h>

enum BreakNetState {
    BREAK_NET_STATE_CREATED,
    BREAK_NET_STATE_STARTING,
    BREAK_NET_STATE_STARTED,
    BREAK_NET_STATE_STOPPING,
    BREAK_NET_STATE_STOPPED,
    BREAK_NET_STATE_FAILED
};

#define BREAK_NET_ADDRESS_TEXT_CAPACITY 108u
#define BREAK_NET_ADMISSION_IP_CAPACITY 1024u

typedef struct BreakNetAdmissionIpEntry {
    char ip[BREAK_NET_ADDRESS_TEXT_CAPACITY];
    snow_freqlimiter_t *limiter;
} BreakNetAdmissionIpEntry;

typedef struct BreakNetAdmissionState {
    BreakNetRateLimitConfig config;
    snow_ratelimiter_t *global;
    BreakNetAdmissionIpEntry per_ip[BREAK_NET_ADMISSION_IP_CAPACITY];
    _Atomic uint64_t denied;
} BreakNetAdmissionState;

typedef struct BreakNetOutboundCommand {
    uint64_t connection_key;
    BreakNetOwnedMessage message;
} BreakNetOutboundCommand;

typedef struct BreakNetConnectionContext {
    BreakNetEnvelopeContext envelope;
    /* TLS mode only: decrypted-stream accumulator the parser frames envelopes
     * from.  Created lazily on the first post-handshake decrypt; parser-only
     * object (driver thread), destroyed when the context dies in on_closed. */
    snow_network_buffer_t *tls_plain;
} BreakNetConnectionContext;

typedef struct BreakNetConnectionIdentity {
    uint64_t key;
    uint32_t uid;
    int fd;
    int thread_index;
    uint16_t port;
    char ip[BREAK_NET_ADDRESS_TEXT_CAPACITY];
    snow_recv_context_t *send_recv;
    size_t pending_send_count;
    uint32_t outbound_sequence;
    bool closing;
    bool valid;
#ifdef BREAK_ENABLE_CRYPTO
    u8 auth_server_nonce[16];
    bool auth_server_nonce_valid;
#endif
    /* TLS mode only (both NULL in plaintext mode).  `ssl` is the per-connection
     * server-role session; `tls_scratch` is the drain-side ciphertext buffer.
     * Both are released ONLY through the identity lifecycle (release_if_drained
     * / abort / reactor-destroy sweep), so an ssl handle outlives a close for
     * exactly as long as the identity's deferred release demands — SSL free
     * waits for pending_send_count to clear, same as send_recv.
     *
     * Threading contract: every snow_ssl_t touch — do_handshake/read inside
     * break_net_parser, write inside break_net_drain_outbound, free in the
     * identity lifecycle — happens on the reactor's single driver thread.
     * THREAD mode runs break_net_drain_outbound + snow_net_thread_step (which
     * fires every connection callback) on break_net_reactor_thread_main; STEP
     * mode runs both inside break_net_reactor_step behind the step_driver
     * flag.  The snow_ssl_t single-thread contract is satisfied by
     * construction; no per-handle locking exists or is needed. */
    snow_ssl_t *ssl;
    snow_network_buffer_t *tls_scratch;
} BreakNetConnectionIdentity;

#ifdef BREAK_ENABLE_CRYPTO
bool break_session_auth_configured_internal(void);
bool break_net_reactor_auth_server_nonce_for_session(
    BreakNetReactor *reactor, uint64_t connection_key, u8 out_nonce[16]);
#endif

static bool break_net_event_push(BreakNetReactor *reactor, BreakNetEvent *event);
static void break_net_reactor_fail(BreakNetReactor *reactor);
static BreakNetConnectionIdentity *break_net_identity_find(BreakNetReactor *reactor,
                                                            uint64_t key);
static BreakNetConnectionIdentity *break_net_identity_alloc(BreakNetReactor *reactor,
                                                            uint64_t key);

static void break_net_drain_outbound(BreakNetReactor *reactor);
static void break_net_identity_release_if_drained(BreakNetConnectionIdentity *identity);
static void break_net_identity_abort(BreakNetConnectionIdentity *identity);
static void break_net_identity_mark_closed(BreakNetConnectionIdentity *identity);
static void break_net_identity_mark_send_drained(BreakNetConnectionIdentity *identity);
static void break_net_identity_on_closed(BreakNetReactor *reactor, uint64_t key);
static void break_net_identity_on_send_drained(BreakNetReactor *reactor, uint64_t key);
static void break_net_admission_destroy(BreakNetAdmissionState *admission);
static bool break_net_admission_admit(void *admit_ud, const char *ip, uint16_t port);
static unsigned int break_net_new_connection_failure_for_test;
static BreakNetStartFailureForTest break_net_start_failure_for_test;

struct BreakNetReactor {
    BreakNetReactorConfig config;
    snow_net_thread_t *snow_thread;
    snow_acceptor_t *acceptor;
    enum BreakNetState state;
    atomic_flag step_driver;
    PlatformMutex lifecycle_mutex;
    PlatformCond lifecycle_cond;
    bool step_active;
    uint32_t step_delay_ms_for_test;
    PlatformThread host_thread;
    bool host_thread_valid;
    bool stop_cleanup_in_progress;
    bool start_in_progress;
    atomic_bool host_ready;
    atomic_bool host_active;
    atomic_bool host_exited;
    PlatformMutex queue_mutex;
    BreakNetEvent events[BREAK_NET_EVENT_QUEUE_CAPACITY];
    size_t event_head;
    size_t event_count;
    BreakNetOutboundCommand outbound[BREAK_NET_OUTBOUND_QUEUE_CAPACITY];
    size_t outbound_head;
    size_t outbound_count;
    size_t outbound_attempts;
    BreakNetConnectionIdentity identities[BREAK_NET_CONNECTION_IDENTITY_CAPACITY];
    /* TLS acceptor mode (CREATED-state configuration; immutable once start
     * publishes it).  tls_ctx != NULL means TLS is required on every accepted
     * connection.  The strings are owned copies of BreakNetTlsConfig; the ctx
     * is owned and must outlive every derived snow_ssl_t, so it is freed in
     * break_net_reactor_destroy AFTER the identity sweep. */
    snow_ssl_ctx_t *tls_ctx;
    char *tls_cert_file;
    char *tls_key_file;
    char *tls_ca_file;
    int tls_verify_peer;
    /* Admission rate limiting (CREATED-state configuration; immutable once
     * start publishes it).  NULL means every admit is allowed.  Owned by the
     * network driver thread after start; config/counter reads are synchronized
     * through lifecycle_mutex. */
    BreakNetAdmissionState *admission;
};

/* Frame exactly one envelope off a PLAINTEXT buffer (the wire buffer in
 * plaintext mode, the decrypted accumulator in TLS mode).  This is the
 * pre-TLS parser body, extracted unchanged: plaintext-mode wire behavior is
 * byte-identical to before. */
static snow_nb_packet_t break_net_parse_plaintext_frame(
    snow_network_buffer_t *buffer, snow_connection_t *connection,
    BreakNetEnvelopeContext *envelope_context)
{
    uint8_t header[BREAK_NET_ENVELOPE_HEADER_SIZE];
    size_t available;
    size_t frame_size;
    uint32_t payload_size;
    BreakNetEnvelope envelope;
    available = snow_network_buffer_length(buffer);
    if (available < BREAK_NET_ENVELOPE_HEADER_SIZE) return SNOW_NB_PACKET_LESS;
    if (snow_network_buffer_get_header(buffer, sizeof(header), header,
                                       sizeof(header), &available) != SNOW_OK) {
        return SNOW_NB_PACKET_ERR;
    }
    payload_size = (uint32_t)header[14] |
                   ((uint32_t)header[15] << 8u) |
                   ((uint32_t)header[16] << 16u) |
                   ((uint32_t)header[17] << 24u);
    if (payload_size > BREAK_NET_MAX_PAYLOAD_SIZE) {
        return SNOW_NB_PACKET_ERR;
    }
    frame_size = BREAK_NET_ENVELOPE_HEADER_SIZE + (size_t)payload_size;
    if (snow_network_buffer_length(buffer) < frame_size) return SNOW_NB_PACKET_LESS;
    {
        unsigned char *frame_header = malloc(frame_size);
        if (frame_header == NULL || snow_network_buffer_copy_to(buffer, frame_header,
                                                                  frame_size, &available) != SNOW_OK) {
            free(frame_header);
            return SNOW_NB_PACKET_ERR;
        }
        if (break_net_envelope_decode_with_context(envelope_context,
                                                   frame_header, frame_size, &envelope) != BREAK_NET_ENVELOPE_OK) {
            free(frame_header);
            return SNOW_NB_PACKET_ERR;
        }
        free(frame_header);
    }
    {
        void *frame = malloc(frame_size);
        snow_recv_context_t *context = NULL;
        if (frame == NULL || snow_network_buffer_copy_to(buffer, frame, frame_size,
                                                          &available) != SNOW_OK ||
            snow_recv_context_make_for_packet(connection, frame, frame_size, 0,
                                              &context) != SNOW_OK ||
            snow_connection_push_recv(connection, context) != SNOW_OK) {
            free(frame);
            snow_recv_context_free(context);
            return SNOW_NB_PACKET_ERR;
        }
        free(frame);
    }
    if (snow_network_buffer_move_header(buffer, frame_size) != SNOW_OK) {
        return SNOW_NB_PACKET_ERR;
    }
    return SNOW_NB_PACKET_FULL;
}

/* Ship handshake/alert ciphertext produced by snow_ssl_do_handshake to the
 * peer.  queue_mutex is NOT held across snow_connection_send: the eager
 * direct-send path can fire on_send_drained synchronously, and that handler
 * takes queue_mutex.  The send context references identity->send_recv
 * (non-owning); snow's drain/free paths only ever read the embedded payload
 * copy, so this reinjection does not join the pending_send_count accounting —
 * documented in the Task 2 report. */
static void break_net_tls_reinject(BreakNetReactor *reactor,
                                   snow_connection_t *connection,
                                   snow_network_buffer_t *out)
{
    size_t size = snow_network_buffer_length(out);
    size_t copied = 0u;
    uint8_t *flat;
    snow_recv_context_t *send_recv = NULL;
    snow_send_context_t *send = NULL;
    if (size == 0u) return;
    platform_mutex_lock(&reactor->queue_mutex);
    {
        BreakNetConnectionIdentity *identity =
            break_net_identity_find(reactor, (uint64_t)snow_connection_uid(connection));
        if (identity != NULL && !identity->closing) {
            send_recv = identity->send_recv;
        }
    }
    platform_mutex_unlock(&reactor->queue_mutex);
    if (send_recv == NULL) return;
    flat = (uint8_t *)malloc(size);
    if (flat == NULL) return;
    if (snow_network_buffer_copy_to(out, flat, size, &copied) != SNOW_OK ||
        copied != size ||
        snow_send_context_create_with(&send, send_recv, SNOW_SEND_CMD_DATA,
                                      flat, size) != SNOW_OK) {
        free(flat);
        snow_send_context_free(send);
        return;
    }
    free(flat);
    if (snow_connection_send(connection, send) != SNOW_OK) {
        snow_send_context_free(send);
    }
}

/* TLS-mode inbound split.  Consumes the whole ciphertext burst from the wire
 * buffer first (so the transceiver's FULL-advance invariant always holds),
 * then: pre-handshake, feed snow_ssl_do_handshake (reply ciphertext
 * re-injected; failure -> ERR -> fail-closed close); post-handshake (or right
 * after a completing burst — OpenSSL keeps surplus app ciphertext in the
 * rbio), decrypt via snow_ssl_read into the per-connection plaintext
 * accumulator and frame envelopes off it through the unchanged plaintext
 * path. */
static snow_nb_packet_t break_net_parser_tls(BreakNetReactor *reactor,
                                             snow_network_buffer_t *buffer,
                                             snow_connection_t *connection,
                                             BreakNetConnectionContext *connection_context)
{
    snow_ssl_t *ssl;
    uint8_t *cipher = NULL;
    size_t available = snow_network_buffer_length(buffer);
    size_t copied = 0u;

    if (connection_context == NULL) return SNOW_NB_PACKET_ERR;
    platform_mutex_lock(&reactor->queue_mutex);
    {
        BreakNetConnectionIdentity *identity =
            break_net_identity_find(reactor, (uint64_t)snow_connection_uid(connection));
        ssl = identity != NULL ? identity->ssl : NULL;
    }
    platform_mutex_unlock(&reactor->queue_mutex);
    if (ssl == NULL) return SNOW_NB_PACKET_ERR;

    if (available != 0u) {
        cipher = (uint8_t *)malloc(available);
        if (cipher == NULL ||
            snow_network_buffer_copy_to(buffer, cipher, available, &copied) != SNOW_OK ||
            copied != available ||
            snow_network_buffer_move_header(buffer, available) != SNOW_OK) {
            free(cipher);
            return SNOW_NB_PACKET_ERR;
        }
    }
    if (!snow_ssl_is_handshaked(ssl)) {
        snow_network_buffer_t *out = NULL;
        int handshake_result;
        if (snow_network_buffer_create(&out) != SNOW_OK) {
            free(cipher);
            return SNOW_NB_PACKET_ERR;
        }
        handshake_result = snow_ssl_do_handshake(ssl, out, cipher, available);
        free(cipher);
        cipher = NULL;
        available = 0u;
        break_net_tls_reinject(reactor, connection, out);
        snow_network_buffer_destroy(out);
        if (handshake_result != 0) return SNOW_NB_PACKET_ERR;
        if (!snow_ssl_is_handshaked(ssl)) return SNOW_NB_PACKET_LESS;
    }
    if (connection_context->tls_plain == NULL &&
        snow_network_buffer_create(&connection_context->tls_plain) != SNOW_OK) {
        free(cipher);
        return SNOW_NB_PACKET_ERR;
    }
    if (snow_ssl_read(ssl, cipher, available, connection_context->tls_plain) != 0) {
        free(cipher);
        return SNOW_NB_PACKET_ERR;
    }
    free(cipher);
    /* The snow wrapper also appends every decrypted byte to its internal
     * recv_buf (snow_ssl_drain_decrypted); we consume via `out` only, so
     * drain the transcript here or it grows unboundedly for the connection's
     * lifetime (peer-controlled). */
    {
        snow_network_buffer_t *wrapper_recv = snow_ssl_recv_buffer(ssl);
        if (wrapper_recv != NULL &&
            snow_network_buffer_move_header(
                wrapper_recv, snow_network_buffer_length(wrapper_recv)) != SNOW_OK) {
            return SNOW_NB_PACKET_ERR;
        }
    }
    /* Frame every complete envelope currently buffered in tls_plain and
     * pop it into a BreakNetEvent IMMEDIATELY (no recv_queue staging):
     * one ciphertext burst can carry many envelopes, but snow's drive
     * loop only fires on_packet for the tail entry pushed after a FULL
     * return (snow_connection_tx.c:210-245) and stops once the wire
     * buffer is empty (snow_transceiver.c:627-629) — staged siblings
     * would sit until the next burst.  The FULL-advance invariant
     * (:652-655) compares the wire buffer across ONE parser call, so the
     * final call of a burst consumes the last ciphertext while reporting
     * LESS; intermediate FULLs each consumed ciphertext. */
    for (;;) {
        snow_nb_packet_t result =
            break_net_parse_plaintext_frame(connection_context->tls_plain,
                                            connection,
                                            &connection_context->envelope);
        snow_recv_context_t *entry;
        if (result != SNOW_NB_PACKET_FULL) return result;
        entry = snow_connection_pop_recv(connection);
        if (entry == NULL) return SNOW_NB_PACKET_ERR;  /* push without queue */
        {
            const void *data = NULL;
            size_t size = 0u;
            BreakNetEvent event = {0};
            BreakNetMessageView view;
            BreakNetEnvelope envelope;
            snow_recv_context_buffer(entry, &data, &size);
            event.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
            event.connection_key = (uint64_t)snow_connection_uid(connection);
            if (break_net_envelope_decode((const uint8_t *)data, size, &envelope) ==
                    BREAK_NET_ENVELOPE_OK &&
                break_net_message_view_init(&view, envelope.message_id,
                                            envelope.protocol_version, envelope.sequence,
                                            envelope.payload, envelope.payload_size) == BREAK_NET_MESSAGE_OK &&
                break_net_message_copy(&event.message, &view) == BREAK_NET_MESSAGE_OK) {
                if (!break_net_event_push(reactor, &event)) {
                    break_net_event_release(&event);
                }
            } else {
                break_net_event_release(&event);
            }
        }
        snow_recv_context_free(entry);
        if (snow_network_buffer_empty(connection_context->tls_plain)) {
            /* Nothing more can be framed until new ciphertext arrives;
             * report LESS so the drive loop terminates on this burst. */
            return SNOW_NB_PACKET_LESS;
        }
    }
}

static snow_nb_packet_t break_net_parser(snow_network_buffer_t *buffer,
                                         snow_connection_t *connection,
                                         void *ud)
{
    BreakNetReactor *reactor = (BreakNetReactor *)ud;
    BreakNetConnectionContext *connection_context =
        (BreakNetConnectionContext *)snow_connection_user(connection);
    if (reactor == NULL || reactor->tls_ctx == NULL) {
        return break_net_parse_plaintext_frame(buffer, connection,
            connection_context != NULL ? &connection_context->envelope : NULL);
    }
    return break_net_parser_tls(reactor, buffer, connection, connection_context);
}

static void break_net_on_new_connection(snow_connection_t *connection, void *ud)
{
    BreakNetReactor *reactor = (BreakNetReactor *)ud;
    BreakNetConnectionContext *context =
        (BreakNetConnectionContext *)calloc(1u, sizeof(*context));
    BreakNetEvent event = {0};
    uint64_t connection_key = (uint64_t)snow_connection_uid(connection);
#ifdef BREAK_ENABLE_CRYPTO
    u8 auth_nonce[16];
    bool auth_nonce_valid = false;
#endif
    if (context == NULL || break_net_new_connection_failure_for_test == 1) {
        free(context);
        break_net_new_connection_failure_for_test = 0;
        break_net_reactor_fail(reactor);
        return;
    }
    platform_mutex_lock(&reactor->queue_mutex);
    {
        BreakNetConnectionIdentity *identity =
            break_net_new_connection_failure_for_test == 2
                ? NULL
                : break_net_identity_alloc(reactor, connection_key);
        snow_socket_addr_t *addr = NULL;
        if (identity == NULL || break_net_new_connection_failure_for_test == 3 ||
            snow_socket_addr_alloc(&addr) != SNOW_OK ||
            snow_socket_addr_from_inet(addr, snow_connection_ip(connection),
                                       snow_connection_port(connection)) != SNOW_OK ||
            snow_socket_addr_to_string(addr, identity->ip, sizeof(identity->ip)) != SNOW_OK ||
            break_net_new_connection_failure_for_test == 4 ||
            snow_recv_context_create(&identity->send_recv,
                0, snow_connection_uid(connection), addr, snow_connection_fd(connection),
                NULL, false, SNOW_CLOSE_CLIENT, 0) != SNOW_OK) {
            snow_socket_addr_free(addr);
            break_net_identity_abort(identity);
            platform_mutex_unlock(&reactor->queue_mutex);
            free(context);
            break_net_reactor_fail(reactor);
            return;
        }
        identity->uid = snow_connection_uid(connection);
        identity->fd = snow_connection_fd(connection);
        identity->thread_index = snow_net_thread_index(
            (const snow_net_thread_t *)snow_connection_net_thread(connection));
        identity->port = snow_connection_port(connection);
        /* TLS acceptor mode: every accepted connection gets its server-role
         * snow_ssl_t before any I/O callback can fire; the parser refuses to
         * frame envelopes until the handshake completes.  tls_ctx is immutable
         * after CREATED, so this read needs no lock (creation is ordered before
         * break_net_reactor_start, which publishes the configuration to the
         * driver thread via the host-thread spawn / step_driver flag). */
        if (reactor->tls_ctx != NULL) {
            identity->ssl = snow_ssl_new(reactor->tls_ctx);
            if (identity->ssl == NULL ||
                snow_ssl_init(identity->ssl, true) != SNOW_OK ||
                snow_network_buffer_create(&identity->tls_scratch) != SNOW_OK) {
                snow_socket_addr_free(addr);
                break_net_identity_abort(identity);
                platform_mutex_unlock(&reactor->queue_mutex);
                free(context);
                break_net_reactor_fail(reactor);
                return;
            }
        }
#ifdef BREAK_ENABLE_CRYPTO
        if (break_session_auth_configured_internal()) {
            if (!break_crypto_random(identity->auth_server_nonce, 16u)) {
                snow_socket_addr_free(addr);
                break_net_identity_abort(identity);
                platform_mutex_unlock(&reactor->queue_mutex);
                free(context);
                break_net_reactor_fail(reactor);
                return;
            }
            identity->auth_server_nonce_valid = true;
            memcpy(auth_nonce, identity->auth_server_nonce, 16u);
            auth_nonce_valid = true;
        }
#endif
        snow_socket_addr_free(addr);
    }
    platform_mutex_unlock(&reactor->queue_mutex);
#ifdef BREAK_ENABLE_CRYPTO
    /* break_net_reactor_send takes queue_mutex itself, so the CHALLENGE must
     * be queued only after the identity updates above are unlocked; keeping
     * it inside that lock self-deadlocks the accept path. */
    if (auth_nonce_valid &&
        break_net_reactor_send(reactor, connection_key,
                               BREAK_NET_MESSAGE_ID_CHALLENGE, 1u,
                               auth_nonce, 16u) != BREAK_NET_SEND_OK) {
        break_net_reactor_fail(reactor);
        free(context);
        return;
    }
#endif
    snow_connection_set_user(connection, context);
    event.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    event.connection_key = connection_key;
    (void)break_net_event_push(reactor, &event);
}

static void break_net_on_packet(snow_connection_t *connection,
                                snow_recv_context_t *context, void *ud)
{
    BreakNetReactor *reactor = (BreakNetReactor *)ud;
    /* `context` is only the hook's tail-entry hint; drain the whole queue
     * from the front (snow's fwd hook fires at most once per complete
     * package — snow_connection_tx.c:210-245).  TLS mode stages nothing
     * here (break_net_parser_tls converts frames to events directly), so
     * in practice the queue holds at most the plaintext path's one entry. */
    (void)context;
    for (;;) {
        snow_recv_context_t *entry = snow_connection_pop_recv(connection);
        const void *data = NULL;
        size_t size = 0u;
        BreakNetEvent event = {0};
        BreakNetMessageView view;
        BreakNetEnvelope envelope;
        if (entry == NULL) return;
        snow_recv_context_buffer(entry, &data, &size);
        event.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
        event.connection_key = (uint64_t)snow_connection_uid(connection);
        if (break_net_envelope_decode((const uint8_t *)data, size, &envelope) !=
                BREAK_NET_ENVELOPE_OK ||
            break_net_message_view_init(&view, envelope.message_id,
                                        envelope.protocol_version, envelope.sequence,
                                        envelope.payload, envelope.payload_size) != BREAK_NET_MESSAGE_OK ||
            break_net_message_copy(&event.message, &view) != BREAK_NET_MESSAGE_OK) {
            break_net_event_release(&event);
            snow_recv_context_free(entry);
            return;
        }
        if (!break_net_event_push(reactor, &event)) {
            break_net_event_release(&event);
        }
        snow_recv_context_free(entry);
    }
}

static void break_net_on_send_drained(snow_connection_t *connection, void *ud)
{
    BreakNetReactor *reactor = (BreakNetReactor *)ud;
    BreakNetEvent event = {0};
    event.type = BREAK_NET_EVENT_SEND_DRAINED;
    event.connection_key = (uint64_t)snow_connection_uid(connection);
    (void)break_net_event_push(reactor, &event);
    break_net_identity_on_send_drained(reactor, (uint64_t)snow_connection_uid(connection));
}

static void break_net_on_closed(snow_connection_t *connection, snow_close_t reason,
                                const char *error, void *ud)
{
    BreakNetReactor *reactor = (BreakNetReactor *)ud;
    BreakNetEvent event = {0};
    event.type = error != NULL ? BREAK_NET_EVENT_TRANSPORT_ERROR : BREAK_NET_EVENT_CONNECTION_CLOSED;
    event.connection_key = (uint64_t)snow_connection_uid(connection);
    event.reason = (uint32_t)reason;
    (void)break_net_event_push(reactor, &event);
    break_net_identity_on_closed(reactor, (uint64_t)snow_connection_uid(connection));
    {
        BreakNetConnectionContext *context =
            (BreakNetConnectionContext *)snow_connection_user(connection);
        if (context != NULL) {
            snow_network_buffer_destroy(context->tls_plain);
            free(context);
        }
    }
    snow_connection_set_user(connection, NULL);
}

static bool break_net_wait_for_step_exit(BreakNetReactor *reactor, uint32_t timeout_ms)
{
#if defined(PLATFORM_THREAD_POSIX)
    struct timespec deadline;
    if (timespec_get(&deadline, TIME_UTC) != TIME_UTC) return false;
    deadline.tv_sec += (time_t)(timeout_ms / 1000u);
    deadline.tv_nsec += (long)(timeout_ms % 1000u) * 1000000L;
    if (deadline.tv_nsec >= 1000000000L) {
        deadline.tv_sec++;
        deadline.tv_nsec -= 1000000000L;
    }
    while (reactor->step_active) {
        int result = pthread_cond_timedwait(&reactor->lifecycle_cond,
                                            &reactor->lifecycle_mutex, &deadline);
        if (result == ETIMEDOUT) break;
        if (result != 0) return false;
    }
#else
    ULONGLONG deadline = GetTickCount64() + (ULONGLONG)timeout_ms;
    while (reactor->step_active) {
        ULONGLONG now = GetTickCount64();
        DWORD remaining = now >= deadline ? 0u : (DWORD)(deadline - now);
        if (!SleepConditionVariableCS(&reactor->lifecycle_cond,
                                      &reactor->lifecycle_mutex, remaining)) {
            if (GetLastError() == ERROR_TIMEOUT) break;
            return false;
        }
    }
#endif
    return !reactor->step_active;
}

static bool break_net_wait_for_host_exit(BreakNetReactor *reactor, uint32_t timeout_ms)
{
#if defined(PLATFORM_THREAD_POSIX)
    struct timespec deadline;
    if (timespec_get(&deadline, TIME_UTC) != TIME_UTC) return false;
    deadline.tv_sec += (time_t)(timeout_ms / 1000u);
    deadline.tv_nsec += (long)(timeout_ms % 1000u) * 1000000L;
    if (deadline.tv_nsec >= 1000000000L) {
        deadline.tv_sec++;
        deadline.tv_nsec -= 1000000000L;
    }
    while (!atomic_load_explicit(&reactor->host_exited, memory_order_acquire)) {
        int result = pthread_cond_timedwait(&reactor->lifecycle_cond,
                                            &reactor->lifecycle_mutex, &deadline);
        if (result == ETIMEDOUT) break;
        if (result != 0) return false;
    }
    return atomic_load_explicit(&reactor->host_exited, memory_order_acquire);
#else
    ULONGLONG deadline = GetTickCount64() + (ULONGLONG)timeout_ms;
    while (!atomic_load_explicit(&reactor->host_exited, memory_order_acquire)) {
        ULONGLONG now = GetTickCount64();
        DWORD remaining = now >= deadline ? 0u : (DWORD)(deadline - now);
        if (!SleepConditionVariableCS(&reactor->lifecycle_cond,
                                      &reactor->lifecycle_mutex, remaining)) {
            if (GetLastError() == ERROR_TIMEOUT) break;
            return false;
        }
    }
    return atomic_load_explicit(&reactor->host_exited, memory_order_acquire);
#endif
}

static BreakNetConnectionIdentity *break_net_identity_find(BreakNetReactor *reactor,
                                                            uint64_t key)
{
    size_t i;
    for (i = 0u; i < BREAK_NET_CONNECTION_IDENTITY_CAPACITY; ++i) {
        if (reactor->identities[i].valid && reactor->identities[i].key == key)
            return &reactor->identities[i];
    }
    return NULL;
}

#ifdef BREAK_ENABLE_CRYPTO
bool break_net_reactor_auth_server_nonce_for_session(
    BreakNetReactor *reactor, uint64_t connection_key, u8 out_nonce[16])
{
    BreakNetConnectionIdentity *identity;
    bool available = false;
    if (reactor == NULL || connection_key == 0u || out_nonce == NULL) return false;
    platform_mutex_lock(&reactor->queue_mutex);
    identity = break_net_identity_find(reactor, connection_key);
    if (identity != NULL && identity->auth_server_nonce_valid) {
        memcpy(out_nonce, identity->auth_server_nonce, 16u);
        available = true;
    }
    platform_mutex_unlock(&reactor->queue_mutex);
    return available;
}
#endif

static void break_net_identity_release_if_drained(BreakNetConnectionIdentity *identity)
{
    if (identity != NULL && identity->closing && identity->pending_send_count == 0u) {
        snow_recv_context_free(identity->send_recv);
        snow_ssl_free(identity->ssl);
        snow_network_buffer_destroy(identity->tls_scratch);
        memset(identity, 0, sizeof(*identity));
    }
}

static void break_net_identity_abort(BreakNetConnectionIdentity *identity)
{
    if (identity != NULL) {
        snow_recv_context_free(identity->send_recv);
        snow_ssl_free(identity->ssl);
        snow_network_buffer_destroy(identity->tls_scratch);
        memset(identity, 0, sizeof(*identity));
    }
}

static void break_net_identity_mark_closed(BreakNetConnectionIdentity *identity)
{
    if (identity != NULL) {
        identity->closing = true;
        break_net_identity_release_if_drained(identity);
    }
}

static void break_net_identity_mark_send_drained(BreakNetConnectionIdentity *identity)
{
    if (identity != NULL) {
        identity->pending_send_count = 0u;
        break_net_identity_release_if_drained(identity);
    }
}

static void break_net_identity_on_closed(BreakNetReactor *reactor, uint64_t key)
{
    platform_mutex_lock(&reactor->queue_mutex);
    break_net_identity_mark_closed(break_net_identity_find(reactor, key));
    platform_mutex_unlock(&reactor->queue_mutex);
}

static void break_net_identity_on_send_drained(BreakNetReactor *reactor, uint64_t key)
{
    platform_mutex_lock(&reactor->queue_mutex);
    break_net_identity_mark_send_drained(break_net_identity_find(reactor, key));
    platform_mutex_unlock(&reactor->queue_mutex);
}

/* TLS-mode outbound: encrypt the freshly encoded envelope via the
 * connection's snow_ssl_t into the per-identity scratch buffer, then build
 * the send context from the ciphertext.  Runs under queue_mutex from
 * break_net_drain_outbound on the driver thread; snow_ssl_write over memory
 * BIOs cannot re-enter the adapter, so the lock is safe to hold. */
static snow_status_t break_net_tls_send_context_create(snow_send_context_t **out,
                                                       BreakNetConnectionIdentity *identity,
                                                       const uint8_t *encoded,
                                                       size_t encoded_size)
{
    uint8_t *wire;
    size_t wire_size;
    size_t copied = 0u;
    snow_status_t status;
    snow_network_buffer_clear(identity->tls_scratch);
    if (snow_ssl_write(identity->ssl, (const char *)encoded, encoded_size,
                       identity->tls_scratch) != 0) {
        return SNOW_ERR_INVAL;
    }
    wire_size = snow_network_buffer_length(identity->tls_scratch);
    wire = (uint8_t *)malloc(wire_size);
    if (wire == NULL) {
        return SNOW_ERR_NOMEM;
    }
    if (snow_network_buffer_copy_to(identity->tls_scratch, wire, wire_size,
                                    &copied) == SNOW_OK &&
        copied == wire_size) {
        status = snow_send_context_create_with(out, identity->send_recv,
                                               SNOW_SEND_CMD_DATA, wire, wire_size);
    } else {
        status = SNOW_ERR_INVAL;
    }
    free(wire);
    return status;
}

static void break_net_outbound_remove_at(BreakNetReactor *reactor, size_t index)
{
    /* Shift successors left starting at `index`.  The move source bound must
     * be the last ACTIVE slot: with a full ring, (head + count) % capacity
     * == head and a one-past-end bound would skip the shift entirely when
     * removing the head — leaving a zeroed hole at the head and orphaning
     * the tail command (lost send + leaked payload). */
    size_t last = (reactor->outbound_head + reactor->outbound_count - 1u) %
                  BREAK_NET_OUTBOUND_QUEUE_CAPACITY;
    size_t current = index;

    break_net_message_release(&reactor->outbound[current].message);
    while (current != last) {
        size_t next = (current + 1u) % BREAK_NET_OUTBOUND_QUEUE_CAPACITY;
        reactor->outbound[current] = reactor->outbound[next];
        current = next;
    }
    memset(&reactor->outbound[current], 0, sizeof(reactor->outbound[current]));
    reactor->outbound_count--;
}

static bool break_net_outbound_key_failed(const uint64_t *failed_keys,
                                          size_t failed_count, uint64_t key)
{
    size_t i;
    for (i = 0u; i < failed_count; ++i) {
        if (failed_keys[i] == key) return true;
    }
    return false;
}

static void break_net_drain_outbound(BreakNetReactor *reactor)
{
    /* N2: keys whose head command failed (encode / send-context / pipe send)
     * during THIS drain call; their queued successors are skipped so a later
     * same-connection command can never overtake a failed one.  Other keys
     * keep flowing.  Bounded by the queue capacity. */
    uint64_t failed_keys[BREAK_NET_OUTBOUND_QUEUE_CAPACITY];
    size_t failed_count = 0u;

    for (;;) {
        size_t scanned = 0u;
        size_t index;
        bool made_progress = false;

        platform_mutex_lock(&reactor->queue_mutex);
        if (reactor->outbound_count == 0u) {
            platform_mutex_unlock(&reactor->queue_mutex);
            return;
        }
        index = reactor->outbound_head;
        while (scanned < reactor->outbound_count) {
            BreakNetOutboundCommand *command = &reactor->outbound[index];
            BreakNetConnectionIdentity *identity;
            BreakNetEnvelope envelope = {0};
            uint8_t encoded[BREAK_NET_ENVELOPE_MAX_SIZE];
            size_t encoded_size = 0u;
            snow_send_context_t *send = NULL;
            snow_status_t status;

            if (break_net_outbound_key_failed(failed_keys, failed_count,
                                              command->connection_key)) {
                scanned++;
                index = (index + 1u) % BREAK_NET_OUTBOUND_QUEUE_CAPACITY;
                continue;
            }
            reactor->outbound_attempts++;
            identity = break_net_identity_find(reactor, command->connection_key);
            if (identity == NULL || identity->send_recv == NULL || identity->closing) {
                break_net_outbound_remove_at(reactor, index);
                made_progress = true;
                break;
            }
            /* TLS: a command blocked by an unfinished handshake (or a failed
             * send) must not freeze other connections.  Inspect each queued
             * command at its actual ring index instead of rotating the head:
             * removing a later ready command shifts the remaining entries
             * left, preserving both the ring invariant and per-connection
             * FIFO order.  Each scan is bounded by the current queue count. */
            if (identity->ssl != NULL && !snow_ssl_is_handshaked(identity->ssl)) {
                scanned++;
                index = (index + 1u) % BREAK_NET_OUTBOUND_QUEUE_CAPACITY;
                continue;
            }
            if (command->message.sequence == 0u &&
                identity->outbound_sequence != UINT32_MAX) {
                command->message.sequence = ++identity->outbound_sequence;
            }
            envelope.protocol_version = command->message.protocol_version;
            envelope.message_id = command->message.message_id;
            envelope.sequence = command->message.sequence;
            envelope.payload = command->message.data;
            envelope.payload_size = command->message.size;
            status = command->message.sequence != 0u &&
                     break_net_envelope_encode(&envelope, encoded, sizeof(encoded), &encoded_size) ==
                         BREAK_NET_ENVELOPE_OK
                         ? SNOW_OK
                         : SNOW_ERR_INVAL;
            if (status == SNOW_OK) {
                status = identity->ssl == NULL
                             ? snow_send_context_create_with(&send, identity->send_recv,
                                                             SNOW_SEND_CMD_DATA, encoded, encoded_size)
                             : break_net_tls_send_context_create(&send, identity, encoded, encoded_size);
            }
            if (status == SNOW_OK) status = snow_net_thread_send(reactor->snow_thread, send);
            if (status == SNOW_OK) {
                send = NULL;
                identity->pending_send_count++;
                break_net_outbound_remove_at(reactor, index);
                made_progress = true;
            } else if (failed_count < BREAK_NET_OUTBOUND_QUEUE_CAPACITY) {
                /* Command stays queued; mark the key so later same-connection
                 * commands are not attempted (FIFO), then keep scanning other
                 * connections.  Permanent failures (e.g. an unregistered
                 * message id that only envelope encode rejects) retry once per
                 * drain call at worst. */
                failed_keys[failed_count++] = command->connection_key;
            }
            snow_send_context_free(send);
            if (made_progress) break;
            scanned++;
            index = (index + 1u) % BREAK_NET_OUTBOUND_QUEUE_CAPACITY;
        }
        platform_mutex_unlock(&reactor->queue_mutex);
        if (!made_progress) return;
    }
}

static BreakNetConnectionIdentity *break_net_identity_alloc(BreakNetReactor *reactor,
                                                            uint64_t key)
{
    size_t i;
    for (i = 0u; i < BREAK_NET_CONNECTION_IDENTITY_CAPACITY; ++i) {
        if (!reactor->identities[i].valid) {
            memset(&reactor->identities[i], 0, sizeof(reactor->identities[i]));
            reactor->identities[i].key = key;
            reactor->identities[i].valid = true;
            return &reactor->identities[i];
        }
    }
    return NULL;
}

static bool break_net_reactor_config_valid(const BreakNetReactorConfig *config)
{
    return config != NULL &&
           (config->drive_mode == BREAK_NET_DRIVE_STEP ||
            config->drive_mode == BREAK_NET_DRIVE_THREAD) &&
           config->logical_index >= 0 &&
           config->max_connections <= BREAK_NET_CONNECTION_IDENTITY_CAPACITY;
}

static void break_net_reactor_fail(BreakNetReactor *reactor)
{
    platform_mutex_lock(&reactor->lifecycle_mutex);
    reactor->state = BREAK_NET_STATE_FAILED;
    platform_cond_broadcast(&reactor->lifecycle_cond);
    platform_mutex_unlock(&reactor->lifecycle_mutex);
}

static void break_net_reactor_start_failure_cleanup(BreakNetReactor *reactor)
{
    if (reactor->snow_thread != NULL) {
        snow_net_thread_terminate(reactor->snow_thread);
        snow_net_thread_destroy(reactor->snow_thread);
        reactor->snow_thread = NULL;
    }
    platform_mutex_lock(&reactor->lifecycle_mutex);
    reactor->start_in_progress = false;
    reactor->state = BREAK_NET_STATE_FAILED;
    platform_cond_broadcast(&reactor->lifecycle_cond);
    platform_mutex_unlock(&reactor->lifecycle_mutex);
}

static void break_net_reactor_publish_ready(BreakNetReactor *reactor)
{
    platform_mutex_lock(&reactor->lifecycle_mutex);
    atomic_store_explicit(&reactor->host_ready, true, memory_order_release);
    platform_cond_broadcast(&reactor->lifecycle_cond);
    platform_mutex_unlock(&reactor->lifecycle_mutex);
}

static PLATFORM_THREAD_RET break_net_reactor_thread_main(PLATFORM_THREAD_ARG arg)
{
    BreakNetReactor *reactor = (BreakNetReactor *)arg;
    snow_status_t status;

    atomic_store_explicit(&reactor->host_active, true, memory_order_release);
    break_net_drain_outbound(reactor);
    status = snow_net_thread_step(reactor->snow_thread,
                                  (int)reactor->config.step_timeout_ms);
    if (status == SNOW_OK) {
        break_net_reactor_publish_ready(reactor);
        for (;;) {
            break_net_drain_outbound(reactor);
            status = snow_net_thread_step(reactor->snow_thread,
                                          (int)reactor->config.step_timeout_ms);
            if (status != SNOW_OK) {
                break;
            }
            platform_mutex_lock(&reactor->lifecycle_mutex);
            if (reactor->state == BREAK_NET_STATE_STOPPING ||
                reactor->state == BREAK_NET_STATE_FAILED) {
                platform_mutex_unlock(&reactor->lifecycle_mutex);
                break;
            }
            platform_mutex_unlock(&reactor->lifecycle_mutex);
        }
    }

    platform_mutex_lock(&reactor->lifecycle_mutex);
    atomic_store_explicit(&reactor->host_active, false, memory_order_release);
    atomic_store_explicit(&reactor->host_exited, true, memory_order_release);
    if (status != SNOW_OK && reactor->state != BREAK_NET_STATE_STOPPING) {
        reactor->state = BREAK_NET_STATE_FAILED;
    }
    platform_cond_broadcast(&reactor->lifecycle_cond);
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    return PLATFORM_THREAD_RETURN;
}

BreakNetReactor *break_net_reactor_create(const BreakNetReactorConfig *config)
{
    BreakNetReactor *reactor;

    if (!break_net_reactor_config_valid(config)) {
        return NULL;
    }
    reactor = (BreakNetReactor *)calloc(1, sizeof(*reactor));
    if (reactor == NULL) {
        return NULL;
    }
    reactor->config = *config;
    reactor->state = BREAK_NET_STATE_CREATED;
    atomic_flag_clear(&reactor->step_driver);
    platform_mutex_init(&reactor->lifecycle_mutex);
    platform_cond_init(&reactor->lifecycle_cond);
    platform_mutex_init(&reactor->queue_mutex);
    return reactor;
}

bool break_net_reactor_set_acceptor(BreakNetReactor *reactor, void *acceptor)
{
    bool accepted = false;
    if (reactor == NULL || acceptor == NULL) return false;
    platform_mutex_lock(&reactor->lifecycle_mutex);
    if (reactor->state == BREAK_NET_STATE_CREATED) {
        reactor->acceptor = (snow_acceptor_t *)acceptor;
        accepted = true;
    }
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    return accepted;
}

static char *break_net_tls_strdup(const char *s)
{
    size_t size = strlen(s) + 1u;
    char *copy = (char *)malloc(size);
    if (copy != NULL) memcpy(copy, s, size);
    return copy;
}

bool break_net_reactor_set_tls(BreakNetReactor *reactor, const BreakNetTlsConfig *cfg)
{
    snow_ssl_ctx_opts_t opts;
    snow_ssl_ctx_t *ctx;
    char *cert_copy;
    char *key_copy;
    char *ca_copy = NULL;

    if (reactor == NULL || cfg == NULL ||
        cfg->cert_file == NULL || cfg->key_file == NULL) {
        return false;
    }
    /* verify_peer without a CA is VERIFY_NONE in disguise (OpenSSL ignores
     * SSL_VERIFY_FAIL_IF_NO_PEER_CERT unless SSL_VERIFY_PEER is set, and
     * PEER is only armed by ca_file); reject instead of silently degrading. */
    if (cfg->verify_peer != 0 && cfg->ca_file == NULL) {
        return false;
    }
    memset(&opts, 0, sizeof(opts));
    opts.cert_file = cfg->cert_file;
    opts.key_file = cfg->key_file;
    opts.ca_file = cfg->ca_file;
    opts.verify_peer = cfg->verify_peer != 0;
    platform_mutex_lock(&reactor->lifecycle_mutex);
    if (reactor->state != BREAK_NET_STATE_CREATED || reactor->tls_ctx != NULL) {
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return false;
    }
    /* The factory loads + cross-checks the PEM pair (mismatched key fails
     * closed) and returns NULL when snow is built without OpenSSL. */
    ctx = snow_ssl_ctx_new(&opts, NULL);
    if (ctx == NULL) {
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return false;
    }
    cert_copy = break_net_tls_strdup(cfg->cert_file);
    key_copy = break_net_tls_strdup(cfg->key_file);
    if (cfg->ca_file != NULL) ca_copy = break_net_tls_strdup(cfg->ca_file);
    if (cert_copy == NULL || key_copy == NULL ||
        (cfg->ca_file != NULL && ca_copy == NULL)) {
        free(cert_copy);
        free(key_copy);
        free(ca_copy);
        snow_ssl_ctx_free(ctx);
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return false;
    }
    reactor->tls_ctx = ctx;
    reactor->tls_cert_file = cert_copy;
    reactor->tls_key_file = key_copy;
    reactor->tls_ca_file = ca_copy;
    reactor->tls_verify_peer = cfg->verify_peer;
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    return true;
}

bool break_net_reactor_is_tls(const BreakNetReactor *reactor)
{
    bool tls;
    if (reactor == NULL) {
        return false;
    }
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&reactor->lifecycle_mutex);
    tls = reactor->tls_ctx != NULL;
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&reactor->lifecycle_mutex);
    return tls;
}

static void break_net_admission_destroy(BreakNetAdmissionState *admission)
{
    size_t i;
    if (admission == NULL) return;
    snow_ratelimiter_free(admission->global);
    for (i = 0u; i < BREAK_NET_ADMISSION_IP_CAPACITY; ++i) {
        snow_freqlimiter_free(admission->per_ip[i].limiter);
    }
    free(admission);
}

static bool break_net_admission_is_enabled(const BreakNetRateLimitConfig *config)
{
    return config->global_accept_per_sec != 0u || config->global_burst != 0u ||
           config->per_ip_per_minute != 0u;
}

static bool break_net_admission_config_valid(const BreakNetRateLimitConfig *config)
{
    if (!break_net_admission_is_enabled(config)) return true;
    if ((config->global_accept_per_sec != 0u) != (config->global_burst != 0u)) {
        return false;
    }
    return true;
}

static bool break_net_admission_admit(void *admit_ud, const char *ip, uint16_t port)
{
    BreakNetAdmissionState *admission = (BreakNetAdmissionState *)admit_ud;
    size_t first_free = BREAK_NET_ADMISSION_IP_CAPACITY;
    size_t i;
    bool allowed = true;
    (void)port;

    if (admission == NULL) return true;
    if (ip == NULL) {
        atomic_fetch_add_explicit(&admission->denied, UINT64_C(1), memory_order_relaxed);
        return false;
    }
    if (admission->global != NULL &&
        !snow_ratelimiter_try_acquire(admission->global, 1u)) {
        allowed = false;
    }
    if (allowed && admission->config.per_ip_per_minute != 0u) {
        for (i = 0u; i < BREAK_NET_ADMISSION_IP_CAPACITY; ++i) {
            BreakNetAdmissionIpEntry *entry = &admission->per_ip[i];
            if (entry->limiter == NULL) {
                if (first_free == BREAK_NET_ADMISSION_IP_CAPACITY) first_free = i;
                continue;
            }
            if (strncmp(entry->ip, ip, sizeof(entry->ip)) == 0) {
                allowed = snow_freqlimiter_allow(entry->limiter);
                goto done;
            }
        }
        if (first_free != BREAK_NET_ADMISSION_IP_CAPACITY) {
            BreakNetAdmissionIpEntry *entry = &admission->per_ip[first_free];
            entry->limiter = snow_freqlimiter_new(
                admission->config.per_ip_per_minute, UINT64_C(60000));
            if (entry->limiter == NULL) {
                atomic_fetch_add_explicit(&admission->denied, UINT64_C(1),
                                          memory_order_relaxed);
                return false;
            }
            snprintf(entry->ip, sizeof(entry->ip), "%s", ip);
            allowed = snow_freqlimiter_allow(entry->limiter);
        } else {
            /* Table full: fail closed for NEW IPs only.  Known IPs still get
             * measured instead of being mistaken for new ones. */
            allowed = false;
        }
    }

done:
    if (!allowed) {
        atomic_fetch_add_explicit(&admission->denied, UINT64_C(1),
                                  memory_order_relaxed);
    }
    return allowed;
}

bool break_net_reactor_set_rate_limits(BreakNetReactor *r,
                                        const BreakNetRateLimitConfig *cfg)
{
    BreakNetAdmissionState *admission = NULL;
    bool accepted = false;
    if (r == NULL || cfg == NULL || !break_net_admission_config_valid(cfg)) {
        return false;
    }
    if (break_net_admission_is_enabled(cfg)) {
        size_t i;
        admission = (BreakNetAdmissionState *)calloc(1u, sizeof(*admission));
        if (admission == NULL) return false;
        admission->config = *cfg;
        if (cfg->global_accept_per_sec != 0u) {
            admission->global = snow_ratelimiter_new(
                (double)cfg->global_accept_per_sec, cfg->global_burst);
            if (admission->global == NULL) {
                break_net_admission_destroy(admission);
                return false;
            }
        }
        for (i = 0u; i < BREAK_NET_ADMISSION_IP_CAPACITY; ++i) {
            admission->per_ip[i].limiter = NULL;
        }
    }
    platform_mutex_lock(&r->lifecycle_mutex);
    if (r->state == BREAK_NET_STATE_CREATED && r->admission == NULL) {
        r->admission = admission;
        accepted = true;
    }
    platform_mutex_unlock(&r->lifecycle_mutex);
    if (!accepted) break_net_admission_destroy(admission);
    return accepted;
}

uint64_t break_net_reactor_admission_denied(const BreakNetReactor *r)
{
    BreakNetAdmissionState *admission;
    if (r == NULL) return 0u;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&r->lifecycle_mutex);
    admission = r->admission;
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&r->lifecycle_mutex);
    return admission == NULL ? 0u
                             : atomic_load_explicit(&admission->denied,
                                                    memory_order_relaxed);
}

void break_net_reactor_destroy(BreakNetReactor *reactor)
{
    bool can_destroy;

    if (reactor == NULL) {
        return;
    }
    platform_mutex_lock(&reactor->lifecycle_mutex);
    can_destroy = reactor->state != BREAK_NET_STATE_STARTING &&
                  reactor->state != BREAK_NET_STATE_STARTED &&
                  reactor->state != BREAK_NET_STATE_STOPPING &&
                  !reactor->start_in_progress && !reactor->host_thread_valid;
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    if (!can_destroy) {
        return;
    }
    if (reactor->snow_thread != NULL) {
        snow_net_thread_destroy(reactor->snow_thread);
        reactor->snow_thread = NULL;
    }
    platform_mutex_lock(&reactor->queue_mutex);
    {
        size_t i;
        for (i = 0u; i < BREAK_NET_CONNECTION_IDENTITY_CAPACITY; ++i) {
            snow_recv_context_free(reactor->identities[i].send_recv);
            snow_ssl_free(reactor->identities[i].ssl);
            snow_network_buffer_destroy(reactor->identities[i].tls_scratch);
            memset(&reactor->identities[i], 0, sizeof(reactor->identities[i]));
        }
    }
    while (reactor->event_count != 0u) {
        break_net_event_release(&reactor->events[reactor->event_head]);
        reactor->event_head = (reactor->event_head + 1u) % BREAK_NET_EVENT_QUEUE_CAPACITY;
        reactor->event_count--;
    }
    while (reactor->outbound_count != 0u) {
        break_net_message_release(&reactor->outbound[reactor->outbound_head].message);
        reactor->outbound_head = (reactor->outbound_head + 1u) % BREAK_NET_OUTBOUND_QUEUE_CAPACITY;
        reactor->outbound_count--;
    }
    platform_mutex_unlock(&reactor->queue_mutex);
    break_net_admission_destroy(reactor->admission);
    /* Every derived snow_ssl_t died in the identity sweep above; the ctx may
     * go now (snow_ssl_ctx_free requires no live handles). */
    snow_ssl_ctx_free(reactor->tls_ctx);
    free(reactor->tls_cert_file);
    free(reactor->tls_key_file);
    free(reactor->tls_ca_file);
    platform_mutex_destroy(&reactor->queue_mutex);
    platform_cond_destroy(&reactor->lifecycle_cond);
    platform_mutex_destroy(&reactor->lifecycle_mutex);
    free(reactor);
}

bool break_net_reactor_start_failure_for_test(BreakNetReactor *reactor,
                                              BreakNetStartFailureForTest failure)
{
    bool result;
    if (reactor == NULL || failure == BREAK_NET_START_FAIL_NONE) return false;
    break_net_start_failure_for_test = failure;
    result = break_net_reactor_start(reactor);
    break_net_start_failure_for_test = BREAK_NET_START_FAIL_NONE;
    return result;
}

int break_net_reactor_state_for_test(const BreakNetReactor *reactor)
{
    int state;
    if (reactor == NULL) return -1;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&reactor->lifecycle_mutex);
    state = (int)reactor->state;
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&reactor->lifecycle_mutex);
    return state;
}

bool break_net_reactor_start(BreakNetReactor *reactor)
{
    snow_status_t status;

    if (reactor == NULL) {
        return false;
    }
    platform_mutex_lock(&reactor->lifecycle_mutex);
    if (reactor->state != BREAK_NET_STATE_CREATED || reactor->start_in_progress) {
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return false;
    }
    reactor->start_in_progress = true;
    reactor->stop_cleanup_in_progress = false;
    atomic_store_explicit(&reactor->host_exited, false, memory_order_release);
    reactor->state = BREAK_NET_STATE_STARTING;
    platform_mutex_unlock(&reactor->lifecycle_mutex);

    if (snow_net_thread_create(reactor->config.logical_index,
                               &reactor->snow_thread) != SNOW_OK) {
        break_net_reactor_start_failure_cleanup(reactor);
        return false;
    }
    if (reactor->acceptor == NULL) {
        break_net_reactor_start_failure_cleanup(reactor);
        return false;
    }
    status = break_net_start_failure_for_test == BREAK_NET_START_FAIL_SETTER
                 ? SNOW_ERR_INVAL
                 : snow_net_thread_set_max_conn(reactor->snow_thread,
                                                reactor->config.max_connections);
    if (status == SNOW_OK) {
        status = snow_net_thread_set_empty_timeout(
            reactor->snow_thread, reactor->config.empty_connection_timeout_ms);
    }
    if (status == SNOW_OK) {
        status = snow_net_thread_set_watchdog_interval_ms(
            reactor->snow_thread, reactor->config.watchdog_interval_ms);
    }
    if (status == SNOW_OK) {
        snow_conn_handlers_t handlers = {0};
        handlers.parser = break_net_parser;
        handlers.on_new_connection = break_net_on_new_connection;
        handlers.on_packet = break_net_on_packet;
        handlers.on_send_drained = break_net_on_send_drained;
        handlers.on_closed = break_net_on_closed;
        status = break_net_start_failure_for_test == BREAK_NET_START_FAIL_REGISTRATION
                     ? SNOW_ERR_INVAL
                     : snow_net_thread_add_acceptor_with_handlers_ex(
                           reactor->snow_thread, reactor->acceptor, handlers, reactor,
                           reactor->admission != NULL ? break_net_admission_admit : NULL,
                           reactor->admission);
    }
    if (status != SNOW_OK) {
        break_net_reactor_start_failure_cleanup(reactor);
        return false;
    }

    platform_mutex_lock(&reactor->lifecycle_mutex);
    if (reactor->state != BREAK_NET_STATE_STARTING) {
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        snow_net_thread_destroy(reactor->snow_thread);
        reactor->snow_thread = NULL;
        platform_mutex_lock(&reactor->lifecycle_mutex);
        reactor->start_in_progress = false;
        reactor->state = BREAK_NET_STATE_STOPPED;
        platform_cond_broadcast(&reactor->lifecycle_cond);
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return false;
    }
    reactor->state = BREAK_NET_STATE_STARTED;
    if (reactor->config.drive_mode == BREAK_NET_DRIVE_STEP) {
        reactor->start_in_progress = false;
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return break_net_reactor_step(reactor, 0);
    }
    reactor->host_thread_valid = platform_thread_create(
        &reactor->host_thread, break_net_reactor_thread_main, reactor);
    if (!reactor->host_thread_valid) {
        reactor->state = BREAK_NET_STATE_FAILED;
        reactor->start_in_progress = false;
        platform_cond_broadcast(&reactor->lifecycle_cond);
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return false;
    }
    platform_mutex_unlock(&reactor->lifecycle_mutex);

    platform_mutex_lock(&reactor->lifecycle_mutex);
    while (!atomic_load_explicit(&reactor->host_ready, memory_order_acquire) &&
           reactor->state == BREAK_NET_STATE_STARTED) {
        platform_cond_wait(&reactor->lifecycle_cond, &reactor->lifecycle_mutex);
    }
    status = atomic_load_explicit(&reactor->host_ready, memory_order_acquire)
                 ? SNOW_OK
                 : SNOW_ERR_INVAL;
    reactor->start_in_progress = false;
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    return status == SNOW_OK;
}

bool break_net_reactor_step(BreakNetReactor *reactor, int timeout_ms)
{
    snow_status_t status;
    uint32_t delay_ms;
    snow_net_thread_t *snow_thread;

    if (reactor == NULL || reactor->config.drive_mode != BREAK_NET_DRIVE_STEP ||
        timeout_ms < 0) {
        return false;
    }
    if (atomic_flag_test_and_set(&reactor->step_driver)) {
        return false;
    }
    platform_mutex_lock(&reactor->lifecycle_mutex);
    if (reactor->state != BREAK_NET_STATE_STARTED || reactor->snow_thread == NULL) {
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        atomic_flag_clear(&reactor->step_driver);
        return false;
    }
    reactor->step_active = true;
    delay_ms = reactor->step_delay_ms_for_test;
    reactor->step_delay_ms_for_test = 0u;
    snow_thread = reactor->snow_thread;
    platform_mutex_unlock(&reactor->lifecycle_mutex);

    if (delay_ms != 0u) {
#if defined(PLATFORM_THREAD_POSIX)
        struct timespec delay = {(time_t)(delay_ms / 1000u),
                                 (long)(delay_ms % 1000u) * 1000000L};
        nanosleep(&delay, NULL);
#else
        Sleep((DWORD)delay_ms);
#endif
    }
    break_net_drain_outbound(reactor);
    status = snow_net_thread_step(snow_thread, timeout_ms);
    platform_mutex_lock(&reactor->lifecycle_mutex);
    reactor->step_active = false;
    platform_cond_broadcast(&reactor->lifecycle_cond);
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    atomic_flag_clear(&reactor->step_driver);
    if (status != SNOW_OK) {
        break_net_reactor_fail(reactor);
        return false;
    }
    return true;
}

bool break_net_reactor_stop(BreakNetReactor *reactor, uint32_t timeout_ms)
{
    bool join_thread = false;
    bool do_terminate = false;

    if (reactor == NULL) return false;
    platform_mutex_lock(&reactor->lifecycle_mutex);
    for (;;) {
        if (reactor->state == BREAK_NET_STATE_STOPPED) {
            platform_mutex_unlock(&reactor->lifecycle_mutex);
            return true;
        }
        if (reactor->state == BREAK_NET_STATE_CREATED) {
            reactor->state = BREAK_NET_STATE_STOPPED;
            platform_cond_broadcast(&reactor->lifecycle_cond);
            platform_mutex_unlock(&reactor->lifecycle_mutex);
            return true;
        }
        if (reactor->state != BREAK_NET_STATE_STARTED &&
            reactor->state != BREAK_NET_STATE_FAILED &&
            reactor->state != BREAK_NET_STATE_STOPPING) {
            platform_mutex_unlock(&reactor->lifecycle_mutex);
            return false;
        }
        if (reactor->state != BREAK_NET_STATE_STOPPING) {
            reactor->state = BREAK_NET_STATE_STOPPING;
            do_terminate = true;
        }
        if (reactor->host_thread_valid && !reactor->stop_cleanup_in_progress) {
            reactor->stop_cleanup_in_progress = true;
            join_thread = true;
            break;
        }
        if (!reactor->host_thread_valid) break;
        if (!break_net_wait_for_host_exit(reactor, timeout_ms)) {
            platform_mutex_unlock(&reactor->lifecycle_mutex);
            return false;
        }
        if (reactor->stop_cleanup_in_progress) continue;
        reactor->stop_cleanup_in_progress = true;
        join_thread = true;
        break;
    }
    platform_mutex_unlock(&reactor->lifecycle_mutex);

    if (do_terminate && reactor->snow_thread != NULL)
        snow_net_thread_terminate(reactor->snow_thread);

    platform_mutex_lock(&reactor->lifecycle_mutex);
    if (reactor->step_active && !break_net_wait_for_step_exit(reactor, timeout_ms)) {
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return false;
    }
    platform_mutex_unlock(&reactor->lifecycle_mutex);

    if (join_thread) {
        platform_mutex_lock(&reactor->lifecycle_mutex);
        if (!atomic_load_explicit(&reactor->host_exited, memory_order_acquire)) {
            if (!break_net_wait_for_host_exit(reactor, timeout_ms)) {
                reactor->stop_cleanup_in_progress = false;
                platform_cond_broadcast(&reactor->lifecycle_cond);
                platform_mutex_unlock(&reactor->lifecycle_mutex);
                return false;
            }
        }
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        platform_thread_join(reactor->host_thread);
    }
    if (reactor->snow_thread != NULL) {
        snow_net_thread_destroy(reactor->snow_thread);
        reactor->snow_thread = NULL;
    }
    platform_mutex_lock(&reactor->lifecycle_mutex);
    reactor->host_thread_valid = false;
    reactor->stop_cleanup_in_progress = false;
    reactor->state = BREAK_NET_STATE_STOPPED;
    platform_cond_broadcast(&reactor->lifecycle_cond);
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    return true;
}

bool break_net_reactor_is_ready(const BreakNetReactor *reactor)
{
    bool ready;
    if (reactor == NULL) {
        return false;
    }
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&reactor->lifecycle_mutex);
    if (reactor->config.drive_mode == BREAK_NET_DRIVE_THREAD) {
        ready = atomic_load_explicit(&reactor->host_ready, memory_order_acquire);
    } else {
        ready = reactor->state == BREAK_NET_STATE_STARTED &&
                reactor->snow_thread != NULL &&
                snow_net_thread_is_ready(reactor->snow_thread);
    }
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&reactor->lifecycle_mutex);
    return ready;
}

static bool break_net_event_push(BreakNetReactor *reactor, BreakNetEvent *event)
{
    size_t index;
    if (reactor == NULL || event == NULL) return false;
    platform_mutex_lock(&reactor->queue_mutex);
    if (reactor->event_count == BREAK_NET_EVENT_QUEUE_CAPACITY) {
        platform_mutex_unlock(&reactor->queue_mutex);
        return false;
    }
    index = (reactor->event_head + reactor->event_count) % BREAK_NET_EVENT_QUEUE_CAPACITY;
    reactor->events[index] = *event;
    memset(event, 0, sizeof(*event));
    reactor->event_count++;
    platform_mutex_unlock(&reactor->queue_mutex);
    return true;
}

BreakNetPollResult break_net_reactor_poll_event(BreakNetReactor *reactor,
                                                BreakNetEvent *event)
{
    if (reactor == NULL || event == NULL) return BREAK_NET_EVENT_EMPTY;
    memset(event, 0, sizeof(*event));
    platform_mutex_lock(&reactor->queue_mutex);
    if (reactor->event_count == 0u) {
        platform_mutex_unlock(&reactor->queue_mutex);
        return BREAK_NET_EVENT_EMPTY;
    }
    *event = reactor->events[reactor->event_head];
    memset(&reactor->events[reactor->event_head], 0, sizeof(*event));
    reactor->event_head = (reactor->event_head + 1u) % BREAK_NET_EVENT_QUEUE_CAPACITY;
    reactor->event_count--;
    platform_mutex_unlock(&reactor->queue_mutex);
    return BREAK_NET_EVENT_OK;
}

bool break_net_reactor_event_queue_empty(BreakNetReactor *reactor)
{
    bool empty;
    if (reactor == NULL) return true;
    platform_mutex_lock(&reactor->queue_mutex);
    empty = reactor->event_count == 0u;
    platform_mutex_unlock(&reactor->queue_mutex);
    return empty;
}

bool break_net_reactor_enqueue_opened_for_test(BreakNetReactor *reactor,
                                               uint64_t connection_key)
{
    BreakNetEvent event = {0};
    event.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    event.connection_key = connection_key;
    if (!break_net_event_push(reactor, &event)) return false;
    return true;
}

bool break_net_reactor_pending_send_close_contract_for_test(BreakNetReactor *reactor)
{
    BreakNetConnectionIdentity *identity;
    snow_socket_addr_t *addr = NULL;
    bool deferred;
    bool released;
    if (reactor == NULL || snow_socket_addr_alloc(&addr) != SNOW_OK ||
        snow_socket_addr_from_inet(addr, "127.0.0.1", 1u) != SNOW_OK) {
        snow_socket_addr_free(addr);
        return false;
    }
    platform_mutex_lock(&reactor->queue_mutex);
    identity = break_net_identity_alloc(reactor, UINT64_C(0xffff));
    if (identity != NULL &&
        snow_recv_context_create(&identity->send_recv, 0u, UINT32_C(0xffff), addr, 1,
                                 NULL, false, SNOW_CLOSE_CLIENT, 0) == SNOW_OK) {
        identity->pending_send_count = 1u;
        break_net_identity_mark_closed(identity);
        deferred = identity->valid && identity->send_recv != NULL;
        break_net_identity_mark_send_drained(identity);
        released = !identity->valid && identity->send_recv == NULL;
    } else {
        deferred = false;
        released = false;
        if (identity != NULL) memset(identity, 0, sizeof(*identity));
    }
    platform_mutex_unlock(&reactor->queue_mutex);
    snow_socket_addr_free(addr);
    return deferred && released;
}

bool break_net_reactor_new_connection_failure_cleanup_for_test(
    BreakNetReactor *reactor, BreakNetNewConnectionFailureForTest failure)
{
    snow_connection_t *connection = NULL;
    bool cleaned;
    bool reusable;
    if (reactor == NULL || failure < BREAK_NET_NEW_CONNECTION_FAIL_CONTEXT ||
        failure > BREAK_NET_NEW_CONNECTION_FAIL_RECV_CONTEXT ||
        snow_connection_create_tcp(&connection, 0, "127.0.0.1", 1) != SNOW_OK) {
        return false;
    }
    break_net_new_connection_failure_for_test = (unsigned int)failure;
    break_net_on_new_connection(connection, reactor);
    cleaned = break_net_reactor_connection_identity_count_for_test(reactor) == 0u;
    break_net_new_connection_failure_for_test = 0u;
    break_net_on_new_connection(connection, reactor);
    reusable = break_net_reactor_connection_identity_count_for_test(reactor) == 1u;
    platform_mutex_lock(&reactor->queue_mutex);
    break_net_identity_abort(break_net_identity_find(
        reactor, (uint64_t)snow_connection_uid(connection)));
    platform_mutex_unlock(&reactor->queue_mutex);
    free(snow_connection_user(connection));
    snow_connection_set_user(connection, NULL);
    snow_connection_free(connection);
    return cleaned && reusable;
}

bool break_net_reactor_malformed_packet_cleanup_for_test(BreakNetReactor *reactor)
{
    snow_connection_t *connection = NULL;
    snow_recv_context_t *context = NULL;
    unsigned char malformed[BREAK_NET_ENVELOPE_HEADER_SIZE] = {0};
    bool empty;
    if (reactor == NULL || snow_connection_create_tcp(&connection, 0,
                                                       "127.0.0.1", 1) != SNOW_OK) {
        return false;
    }
    if (snow_recv_context_make_for_packet(connection, malformed, sizeof(malformed),
                                          0, &context) != SNOW_OK ||
        snow_connection_push_recv(connection, context) != SNOW_OK) {
        snow_recv_context_free(context);
        snow_connection_free(connection);
        return false;
    }
    break_net_on_packet(connection, context, reactor);
    empty = snow_connection_recv_queue_size(connection) == 0u;
    snow_connection_free(connection);
    return empty;
}

bool break_net_reactor_enqueue_message_for_test(BreakNetReactor *reactor,
                                                uint64_t connection_key,
                                                uint16_t message_id,
                                                uint16_t protocol_version,
                                                const void *data, size_t size)
{
    BreakNetEvent event = {0};
    BreakNetMessageView view;
    if (break_net_message_view_init(&view, message_id, protocol_version, 0u,
                                    data, size) != BREAK_NET_MESSAGE_OK) return false;
    if (break_net_message_copy(&event.message, &view) != BREAK_NET_MESSAGE_OK) return false;
    event.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    event.connection_key = connection_key;
    if (!break_net_event_push(reactor, &event)) {
        break_net_event_release(&event);
        return false;
    }
    return true;
}

BreakNetSendResult break_net_reactor_send(BreakNetReactor *reactor,
                                          uint64_t connection_key,
                                          uint16_t message_id,
                                          uint16_t protocol_version,
                                          const void *data, size_t size)
{
    BreakNetMessageView view;
    size_t index;
    if (reactor == NULL || (size != 0u && data == NULL)) return BREAK_NET_SEND_INVALID;
    if (break_net_message_view_init(&view, message_id, protocol_version, 0u,
                                    data, size) != BREAK_NET_MESSAGE_OK) return BREAK_NET_SEND_INVALID;
    platform_mutex_lock(&reactor->lifecycle_mutex);
    if (reactor->state != BREAK_NET_STATE_STARTED) {
        platform_mutex_unlock(&reactor->lifecycle_mutex);
        return BREAK_NET_SEND_CLOSED;
    }
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    platform_mutex_lock(&reactor->queue_mutex);
    if (reactor->outbound_count == BREAK_NET_OUTBOUND_QUEUE_CAPACITY) {
        platform_mutex_unlock(&reactor->queue_mutex);
        return BREAK_NET_SEND_OVERLOAD;
    }
    index = (reactor->outbound_head + reactor->outbound_count) % BREAK_NET_OUTBOUND_QUEUE_CAPACITY;
    memset(&reactor->outbound[index], 0, sizeof(reactor->outbound[index]));
    if (break_net_message_copy(&reactor->outbound[index].message, &view) != BREAK_NET_MESSAGE_OK) {
        platform_mutex_unlock(&reactor->queue_mutex);
        return BREAK_NET_SEND_INVALID;
    }
    reactor->outbound[index].connection_key = connection_key;
    reactor->outbound_count++;
    platform_mutex_unlock(&reactor->queue_mutex);
    return BREAK_NET_SEND_OK;
}

size_t break_net_reactor_outbound_count(BreakNetReactor *reactor)
{
    size_t count;
    if (reactor == NULL) return 0u;
    platform_mutex_lock(&reactor->queue_mutex);
    count = reactor->outbound_count;
    platform_mutex_unlock(&reactor->queue_mutex);
    return count;
}

size_t break_net_reactor_outbound_attempts_for_test(BreakNetReactor *reactor)
{
    size_t attempts;
    if (reactor == NULL) return 0u;
    platform_mutex_lock(&reactor->queue_mutex);
    attempts = reactor->outbound_attempts;
    platform_mutex_unlock(&reactor->queue_mutex);
    return attempts;
}

size_t break_net_reactor_connection_identity_count_for_test(BreakNetReactor *reactor)
{
    size_t count = 0u;
    size_t i;
    if (reactor == NULL) return 0u;
    platform_mutex_lock(&reactor->queue_mutex);
    for (i = 0u; i < BREAK_NET_CONNECTION_IDENTITY_CAPACITY; ++i)
        if (reactor->identities[i].valid) count++;
    platform_mutex_unlock(&reactor->queue_mutex);
    return count;
}

bool break_net_reactor_stop_pending_for_test(const BreakNetReactor *reactor)
{
    bool pending;
    if (reactor == NULL) return false;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&reactor->lifecycle_mutex);
    pending = reactor->state == BREAK_NET_STATE_STOPPING &&
              (reactor->host_thread_valid || reactor->snow_thread != NULL);
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&reactor->lifecycle_mutex);
    return pending;
}

bool break_net_reactor_step_delay_for_test(BreakNetReactor *reactor, uint32_t delay_ms)
{
    bool accepted = false;
    if (reactor == NULL || reactor->config.drive_mode != BREAK_NET_DRIVE_STEP) return false;
    platform_mutex_lock(&reactor->lifecycle_mutex);
    if (reactor->state == BREAK_NET_STATE_STARTED && !reactor->step_active) {
        reactor->step_delay_ms_for_test = delay_ms;
        accepted = true;
    }
    platform_mutex_unlock(&reactor->lifecycle_mutex);
    return accepted;
}

BreakNetPollResult break_net_reactor_poll_outbound_for_test(
    BreakNetReactor *reactor, uint64_t *connection_key, BreakNetOwnedMessage *message)
{
    BreakNetOutboundCommand *command;
    if (reactor == NULL || connection_key == NULL || message == NULL) {
        return BREAK_NET_EVENT_EMPTY;
    }
    memset(message, 0, sizeof(*message));
    platform_mutex_lock(&reactor->queue_mutex);
    if (reactor->outbound_count == 0u) {
        platform_mutex_unlock(&reactor->queue_mutex);
        return BREAK_NET_EVENT_EMPTY;
    }
    command = &reactor->outbound[reactor->outbound_head];
    *connection_key = command->connection_key;
    *message = command->message;
    memset(command, 0, sizeof(*command));
    reactor->outbound_head = (reactor->outbound_head + 1u) % BREAK_NET_OUTBOUND_QUEUE_CAPACITY;
    reactor->outbound_count--;
    platform_mutex_unlock(&reactor->queue_mutex);
    return BREAK_NET_EVENT_OK;
}
