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
} CoreAppNetTransportConfig;

/* Validates the configuration shape (every field present, bind parses).
 * Reads no secret and opens no socket; start does both. */
CoreAppNetTransport *core_app_net_transport_create(const CoreAppNetTransportConfig *config);
void core_app_net_transport_free(CoreAppNetTransport *transport);

/* Fills hooks bound to the transport. The transport must outlive the run. */
void core_app_net_transport_hooks(CoreAppNetTransport *transport, CoreAppNetworkHooks *out);

/* Parses "HOST:PORT" with a dotted IPv4 host. Exposed for the CLI so a
 * malformed value fails before the runtime starts. */
bool core_app_net_parse_bind(const char *bind, char *host, usize host_capacity, u16 *port);
