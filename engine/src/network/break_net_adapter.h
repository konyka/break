#ifndef BREAK_NET_ADAPTER_H
#define BREAK_NET_ADAPTER_H

#include <stdbool.h>
#include <stdint.h>

#include "network/break_net_events.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakNetReactor BreakNetReactor;
typedef struct BreakNetConnection BreakNetConnection;

typedef enum BreakNetDriveMode {
    BREAK_NET_DRIVE_THREAD = 0,
    BREAK_NET_DRIVE_STEP = 1
} BreakNetDriveMode;

typedef struct BreakNetReactorConfig {
    BreakNetDriveMode drive_mode;
    int logical_index;
    uint32_t max_connections;
    int empty_connection_timeout_ms;
    uint32_t watchdog_interval_ms;
    uint32_t step_timeout_ms;
} BreakNetReactorConfig;

BreakNetReactor *break_net_reactor_create(const BreakNetReactorConfig *config);
void break_net_reactor_destroy(BreakNetReactor *reactor);
bool break_net_reactor_start(BreakNetReactor *reactor);
/* Borrowed caller-owned Snowflake acceptor; valid only before start. */
bool break_net_reactor_set_acceptor(BreakNetReactor *reactor, void *acceptor);

typedef struct BreakNetTlsConfig {
    const char *cert_file;   /* PEM; server cert — required */
    const char *key_file;    /* PEM; matching key — required */
    const char *ca_file;     /* PEM; optional (NULL) — client verification CA */
    int verify_peer;         /* 0 = do not request client certs; 1 = require+verify */
} BreakNetTlsConfig;
/* CREATED state only; copies the strings. TLS is a server-side acceptor mode:
 * with TLS set, EVERY accepted connection must complete a TLS handshake before any
 * envelope parses; handshake failure closes the connection (fail-closed).
 * false on: non-CREATED state, NULL, missing cert/key, snow built without OpenSSL.
 * Also false on verify_peer != 0 with ca_file == NULL: "require+verify" without
 * a CA silently degrades to verify-none in OpenSSL, so it is rejected outright.
 * A second call after a successful one is rejected. */
bool break_net_reactor_set_tls(BreakNetReactor *reactor, const BreakNetTlsConfig *cfg);
bool break_net_reactor_is_tls(const BreakNetReactor *reactor);

typedef struct BreakNetRateLimitConfig {
    uint32_t global_accept_per_sec;   /* token bucket rate; 0 = unlimited */
    uint32_t global_burst;            /* bucket capacity; 0 = unlimited */
    uint32_t per_ip_per_minute;       /* sliding-window accepts per source IP; 0 = unlimited */
} BreakNetRateLimitConfig;
/* CREATED state only. Uses snow ratelimiter/freqlimiter under the admit(ip,port) hook
 * (snow_net_thread_add_acceptor_with_handlers_ex). Per-IP table ≤ 1024 entries;
 * full table → deny NEW IPs (fail-closed, documented), known IPs still measured.
 * All limiter state lives on the network driver thread (limiters are not thread-safe). */
bool break_net_reactor_set_rate_limits(BreakNetReactor *r, const BreakNetRateLimitConfig *cfg);
uint64_t break_net_reactor_admission_denied(const BreakNetReactor *r);   /* observable counter */

bool break_net_reactor_step(BreakNetReactor *reactor, int timeout_ms);
bool break_net_reactor_stop(BreakNetReactor *reactor, uint32_t timeout_ms);
bool break_net_reactor_is_ready(const BreakNetReactor *reactor);

#define BREAK_NET_EVENT_QUEUE_CAPACITY 256u
#define BREAK_NET_OUTBOUND_QUEUE_CAPACITY 256u
#define BREAK_NET_CONNECTION_IDENTITY_CAPACITY 256u

typedef enum BreakNetPollResult {
    BREAK_NET_EVENT_EMPTY = 0,
    BREAK_NET_EVENT_OK = 1
} BreakNetPollResult;

typedef enum BreakNetSendResult {
    BREAK_NET_SEND_OK = 0,
    BREAK_NET_SEND_INVALID,
    BREAK_NET_SEND_OVERLOAD,
    BREAK_NET_SEND_CLOSED
} BreakNetSendResult;

BreakNetPollResult break_net_reactor_poll_event(BreakNetReactor *reactor,
                                                BreakNetEvent *event);
bool break_net_reactor_event_queue_empty(BreakNetReactor *reactor);
BreakNetSendResult break_net_reactor_send(BreakNetReactor *reactor,
                                          uint64_t connection_key,
                                          uint16_t message_id,
                                          uint16_t protocol_version,
                                          const void *data, size_t size);
size_t break_net_reactor_outbound_count(BreakNetReactor *reactor);

/* Server-side close of one connection. Safe from any thread; never blocks.
 * Every send queued for the key BEFORE this call is still written, then the
 * transport closes after its send buffer drains (snow close-after-flush) and
 * the normal CONNECTION_CLOSED event follows. Sends queued after the call
 * return BREAK_NET_SEND_CLOSED. Commands that cannot reach the transport by
 * then (TLS handshake unfinished, send failure) are dropped. Takes effect on
 * the driver thread's next step. Returns true when the close is (or already
 * was) pending; false for NULL/0, a reactor that is not started, or a key
 * with no live connection (unknown, or already closed by the peer).
 * TLS: the socket closes after the encrypted bytes are written, without a
 * TLS close_notify, so strict clients may report an unexpected EOF. */
bool break_net_reactor_close(BreakNetReactor *reactor, uint64_t connection_key);

/* Test-only: returns outbound send attempts made by the reactor driver. */
size_t break_net_reactor_outbound_attempts_for_test(BreakNetReactor *reactor);

/* Test-only: returns the number of copied Snowflake connection identities. */
size_t break_net_reactor_connection_identity_count_for_test(BreakNetReactor *reactor);
/* Test-only: observes that a timed stop retained live lifecycle ownership. */
bool break_net_reactor_stop_pending_for_test(const BreakNetReactor *reactor);
/* Test-only: hold the next step call to make lifecycle races deterministic. */
bool break_net_reactor_step_delay_for_test(BreakNetReactor *reactor, uint32_t delay_ms);

typedef enum BreakNetNewConnectionFailureForTest {
    BREAK_NET_NEW_CONNECTION_FAIL_CONTEXT = 1,
    BREAK_NET_NEW_CONNECTION_FAIL_IDENTITY,
    BREAK_NET_NEW_CONNECTION_FAIL_ADDRESS,
    BREAK_NET_NEW_CONNECTION_FAIL_RECV_CONTEXT
} BreakNetNewConnectionFailureForTest;

typedef enum BreakNetStartFailureForTest {
    BREAK_NET_START_FAIL_NONE = 0,
    BREAK_NET_START_FAIL_SETTER,
    BREAK_NET_START_FAIL_REGISTRATION
} BreakNetStartFailureForTest;

bool break_net_reactor_start_failure_for_test(BreakNetReactor *reactor,
                                              BreakNetStartFailureForTest failure);
int break_net_reactor_state_for_test(const BreakNetReactor *reactor);

/* Test-only: inject one open-callback failure and verify its cleanup contract. */
bool break_net_reactor_new_connection_failure_cleanup_for_test(
    BreakNetReactor *reactor, BreakNetNewConnectionFailureForTest failure);

/* Test-only dequeue helper; ownership transfers to the caller. */
BreakNetPollResult break_net_reactor_poll_outbound_for_test(
    BreakNetReactor *reactor, uint64_t *connection_key, BreakNetOwnedMessage *message);

/* Test-only injection helpers; they exercise the same owned event queue. */
bool break_net_reactor_enqueue_opened_for_test(BreakNetReactor *reactor,
                                               uint64_t connection_key);
bool break_net_reactor_enqueue_message_for_test(BreakNetReactor *reactor,
                                                uint64_t connection_key,
                                                uint16_t message_id,
                                                uint16_t protocol_version,
                                                const void *data, size_t size);
/* Exercises the callback's malformed-frame cleanup path. */
bool break_net_reactor_malformed_packet_cleanup_for_test(BreakNetReactor *reactor);
/* Verifies close defers identity cleanup until the pending send is drained. */
bool break_net_reactor_pending_send_close_contract_for_test(BreakNetReactor *reactor);

#ifdef __cplusplus
}
#endif

#endif /* BREAK_NET_ADAPTER_H */
