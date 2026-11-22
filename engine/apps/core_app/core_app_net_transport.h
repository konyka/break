#pragma once

/* Authenticated snapshot transport for core_app.
 *
 * Compiled into the executable only when CORE_APP_ENABLE_NETWORK and
 * BREAK_ENABLE_SNOWFLAKE are both on. It owns one STEP-mode reactor, one
 * session manager and one acceptor, all driven from the CoreAppThread
 * through CoreAppNetworkHooks. TLS and AUTH-v2 are mandatory: there is no
 * plaintext or unauthenticated path. Only AUTHENTICATED sessions receive
 * snapshots. Peer snapshots go through core_app_snapshot_admit and only
 * change counters; the transport has no pointer to the level.
 */

#include "core_app.h"

typedef struct CoreAppNetTransport CoreAppNetTransport;

typedef struct CoreAppNetTransportConfig {
    const char *bind;      /* "HOST:PORT"; PORT 0 picks an ephemeral port */
    const char *tls_cert;  /* PEM server certificate */
    const char *tls_key;   /* PEM server key */
    const char *psk_env;   /* environment variable holding 64 hex digits */
    const char *port_file; /* receives the bound port after start; removed on exit */
    u32 poll_ms;           /* per-tick socket wait, 0..100; 0 never blocks the tick */
    bool voice_relay;      /* forward accepted peer voice to every other peer */
} CoreAppNetTransportConfig;

/* Validates the configuration shape (every field present, bind parses).
 * Reads no secret and opens no socket; start does both. */
CoreAppNetTransport *core_app_net_transport_create(const CoreAppNetTransportConfig *config);
/* Destroys and frees the transport. When the destroy fails (the reactor did
 * not stop, or the global auth hook could not be cleared) the memory is
 * leaked on purpose, because live code still points at it. */
void core_app_net_transport_free(CoreAppNetTransport *transport);

/* Fills hooks bound to the transport. The transport must outlive the run. */
void core_app_net_transport_hooks(CoreAppNetTransport *transport, CoreAppNetworkHooks *out);

/* Network events on the runtime message bus (design:
 * docs/design/runtime_message_model.md "网络事件接入总线"). After attach,
 * every event the reactor produces (queued, or dropped because the reactor
 * queue was full) is published as one message of kind
 * CORE_APP_NET_EVENT_KIND on the thread that steps the reactor. The
 * payload is a CoreAppNetEventNotice in little-endian order
 * (CORE_APP_NET_EVENT_SIZE bytes) and the message carries the event's
 * correlation id; the event payload itself never goes on the bus, the
 * transport still handles it. Publishing never waits: a full subscriber
 * queue drops that copy and the event counts as undelivered. attach
 * registers the kind as a control kind unless it is registered already
 * with the same parameters (REJECTED otherwise), and is REJECTED while the
 * transport runs; NULL detaches. The bus must outlive the run. */
#define CORE_APP_NET_EVENT_VERSION 1u
#define CORE_APP_NET_EVENT_SIZE 40u

typedef struct {
    u32 type;            /* BreakNetEventType */
    u32 reason;
    u64 connection_key;
    u64 correlation_id;  /* MESSAGE_RECEIVED only */
    u64 payload_size;    /* MESSAGE_RECEIVED only */
    u16 message_id;      /* MESSAGE_RECEIVED only */
    bool queued;         /* false: the reactor queue was full */
} CoreAppNetEventNotice;

typedef struct {
    u64 published;    /* notices delivered to at least one subscriber */
    u64 undelivered;  /* notices at least one subscriber missed */
} CoreAppNetEventStats;

struct BreakRuntimeBus;
BreakRuntimeError core_app_net_transport_attach_bus(CoreAppNetTransport *transport,
                                                    struct BreakRuntimeBus *bus);
BreakRuntimeError core_app_net_transport_event_stats(CoreAppNetTransport *transport,
                                                     CoreAppNetEventStats *out);
/* False for a wrong size or a nonzero reserved byte. */
bool core_app_net_event_notice_decode(const void *data, usize size, CoreAppNetEventNotice *out);

#ifdef CORE_APP_NET_TRANSPORT_TESTING
typedef struct BreakNetReactor BreakNetReactor;
/* Test-only (test_core_app_net_transport): the live reactor, or NULL. */
BreakNetReactor *core_app_net_transport_reactor_for_test(CoreAppNetTransport *transport);
/* Test-only: after the step that blocked the stop has returned, stops and
 * destroys the reactor and the acceptor a timed-out destroy kept, then frees
 * the transport. Returns false if the reactor still does not stop. */
bool core_app_net_transport_reclaim_for_test(CoreAppNetTransport *transport);
#endif

/* Parses "HOST:PORT" with a dotted IPv4 host. Exposed for the CLI so a
 * malformed value fails before the runtime starts. */
bool core_app_net_parse_bind(const char *bind, char *host, usize host_capacity, u16 *port);
