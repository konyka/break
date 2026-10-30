#pragma once
/* BreakEditorRemote — Stage 4 scene editor Phase 4: the remote session host
 * (Task 1 core + Task 2 TLS/CHALLENGE/AUTH-v2 wiring). Owns a STEP-mode BreakNetReactor (the shell thread
 * drives it explicitly from break_editor_remote_tick — the shell thread IS
 * the GameThread, so every protocol handler runs on the doc/Lua/command
 * owner thread by construction; there is no cross-thread dispatch), a
 * BreakSessionManager attached to that reactor, and a bounded connection
 * table. The editor wire messages (ids 4..13, editor/editor_protocol.h)
 * live in the break_net default registry's free id space (4..19) because
 * the envelope codec only consults the default registry.
 *
 * Security posture (Phase 4 plan Global Constraints): the remote session is
 * DEFAULT OFF — the shell never creates one on its own; a host (tests, or
 * editor_main's --remote flag) creates and starts it explicitly. The real
 * remote path is use_tls=true: TLS transport + CHALLENGE/AUTH-v2 (the PSK
 * seam below); start fails closed on missing/unreadable cert/key or a
 * missing PSK. use_tls=false is the documented TEST-ONLY plaintext seam: it
 * auto-marks sessions AUTHENTICATED on open (loopback-first, never reachable
 * from editor_main).
 *
 * Fail closed: any unknown message id / malformed payload / oversize frame
 * is rejected by the envelope codec or the handler and closes the session;
 * an editor command on a session that is not AUTHENTICATED closes it with
 * zero doc effect (the editor ids are PHASE_ANY in the default registry, so
 * the host enforces authorization — PHASE_AUTHENTICATED would only reject,
 * not close). A handler-side command failure on a well-formed payload
 * answers BREAK_EDITOR_MSG_RESULT with a non-ok status instead. Session
 * close is the break_session CLOSING watermark (later frames are stale and
 * dropped), and the host then closes the transport too
 * (break_net_reactor_close: responses already queued are flushed first).
 * A connection that is still not authenticated auth_timeout_ms after it
 * was first seen is closed the same way (10 s under --remote).
 *
 * Threading: single-owner-thread convention, same as the shell/document —
 * create/start/tick/destroy all run on the shell thread. The reactor's STEP
 * mode guarantees no network callbacks on any other thread. */

#include <core/types.h>

#include "editor_panels.h"

typedef struct BreakEditorRemote BreakEditorRemote;

typedef struct BreakEditorRemoteConfig {
    const char *bind_host;          /* "127.0.0.1" default; documented loopback-first */
    uint16_t bind_port;             /* 0 = ephemeral (tests); actual port readable via accessor */
    uint32_t max_connections;       /* ≤ 32 */
    bool use_tls;                   /* false only for tests/dev (documented) */
    const char *tls_cert_file, *tls_key_file, *tls_ca_file;  /* required when use_tls */
    int tls_verify_peer;
    uint32_t rate_global_per_sec, rate_global_burst, rate_per_ip_per_minute; /* 0 = unlimited */
    /* A connection that has not authenticated this long after it was first
     * seen is closed (transport included). 0 = no deadline (tests only;
     * --remote always sets BREAK_EDITOR_REMOTE_DEFAULT_AUTH_TIMEOUT_MS). */
    uint32_t auth_timeout_ms;
} BreakEditorRemoteConfig;

/* NULL shell or invalid config (over-cap max_connections) => NULL. */
BreakEditorRemote *break_editor_remote_create(BreakEditorShell *shell, const BreakEditorRemoteConfig *cfg);
void break_editor_remote_destroy(BreakEditorRemote *r);
bool break_editor_remote_start(BreakEditorRemote *r);    /* fail-closed; false on config/startup error */
void break_editor_remote_tick(BreakEditorRemote *r);     /* shell thread, once per frame */
bool break_editor_remote_is_running(const BreakEditorRemote *r);
uint16_t break_editor_remote_port(const BreakEditorRemote *r);
uint64_t break_editor_remote_admission_denied(const BreakEditorRemote *r);
uint32_t break_editor_remote_connection_count(const BreakEditorRemote *r);
/* Test accessor: bounded snapshot of {connection_key, session_id, state} rows. */
uint32_t break_editor_remote_connections_snapshot(const BreakEditorRemote *r,
                                                  uint64_t *out_keys, uint32_t *out_states, uint32_t capacity);
/* Test accessors: poll_count pins the per-frame tick wiring (exactly one
 * poll_adapter call per tick); session_id exposes the manager's stable
 * per-connection id for snapshot rows (0 when unknown). */
u64 break_editor_remote_poll_count(const BreakEditorRemote *r);
u64 break_editor_remote_session_id(const BreakEditorRemote *r, u64 connection_key);
#ifdef BREAK_EDITOR_SHELL_TESTING
/* Test-only accessor (test builds only). */
void *break_editor_remote_manager_for_test(BreakEditorRemote *r);
#endif

/* Phase 4 Task 3: READ-ONLY diagnostics accessors for the network panel
 * (editor_panel_network.c). None of them steps the reactor, drains events,
 * sends, closes, or transitions a session; NULL remote => zero/false.
 * The stats struct mirrors BreakSessionApplyStats field-for-field so the
 * panel needs no break_session header (it reaches the network only through
 * this surface). */
typedef struct BreakEditorRemoteSessionStats {
    uint64_t applied;
    uint64_t unknown;
    uint64_t stale;
    uint64_t invalid;
    uint64_t phase_rejected;
    uint64_t duplicate;
    uint64_t handler_failed;
    uint64_t rate_limited;
} BreakEditorRemoteSessionStats;
/* Copies break_session_manager_apply_stats; false (and *out zeroed) when
 * the remote or its manager is absent. */
bool break_editor_remote_session_stats(const BreakEditorRemote *r,
                                       BreakEditorRemoteSessionStats *out);
bool break_editor_remote_is_tls(const BreakEditorRemote *r);  /* reactor TLS mode */
/* Server-side transport closes the host has issued (fail-closed sessions and
 * auth-deadline evictions), and how many of them were auth-deadline
 * evictions. 0 for NULL. */
u64 break_editor_remote_server_closes(const BreakEditorRemote *r);
u64 break_editor_remote_auth_timeouts(const BreakEditorRemote *r);
u64 break_editor_remote_outbound_count(const BreakEditorRemote *r); /* queued sends */
/* Static name for a BreakSessionState value ("AUTHENTICATED", ...);
 * "UNKNOWN" for anything out of range. */
const char *break_editor_remote_state_name(uint32_t state);

/* Phase 4 Task 2: CHALLENGE/AUTH-v2 PSK seam (DEV PATH, NON-PRODUCTION —
 * one static key_id -> 32-byte PSK pair supplied by the host, e.g. from
 * --remote-psk-hex / --remote-psk-file; no provisioning, rotation, or
 * revocation exists). Copies both arrays; accepted only before start.
 * start installs it as the process-global break_session_set_auth domain
 * (one TLS remote per process; a second one fails start) and destroy
 * clears it and wipes the key copies. use_tls=true without a PSK fails
 * start: there is no unauthenticated TLS command path. */
bool break_editor_remote_set_psk(BreakEditorRemote *r, const uint8_t key_id[8],
                                 const uint8_t psk[32]);

/* Keyring (2026-10-30): up to 8 per-device key_id -> PSK pairs. set_psk
 * replaces the ring with its one key; add_key appends (also while running),
 * refusing a duplicate key id or a full ring. revoke_key removes a key:
 * new AUTH with it fails, and every session that authenticated with it is
 * closed (session and transport) immediately; sessions on other keys are
 * untouched. Key bytes are wiped on revoke and destroy. Provisioning
 * (distributing keys to devices) stays outside the editor. */
bool break_editor_remote_add_key(BreakEditorRemote *r, const uint8_t key_id[8],
                                 const uint8_t psk[32]);
bool break_editor_remote_revoke_key(BreakEditorRemote *r,
                                    const uint8_t key_id[8]);
uint32_t break_editor_remote_key_count(const BreakEditorRemote *r);
/* Re-reads a keyring file (same format as --remote-keyring-file) and
 * applies the difference: keys not listed, or listed with a different
 * secret, are revoked (their sessions closed); new keys are added;
 * unchanged keys keep their sessions. A malformed or unreadable file
 * returns false and changes nothing. Shell thread only. */
bool break_editor_remote_reload_keyring(BreakEditorRemote *r, const char *path);

/* ---------------- editor_main --remote flag plumbing ----------------
 * DEFAULT OFF: without --remote no remote is created and nothing listens.
 *   --remote                 enable (binds 127.0.0.1 — loopback only)
 *   --remote-port N          default BREAK_EDITOR_REMOTE_DEFAULT_PORT
 *   --remote-cert F --remote-key F [--remote-ca F]   TLS is REQUIRED;
 *                            --remote-ca also requires+verifies client certs
 *   --remote-psk-hex <64 hex> | --remote-psk-file F (exactly 32 raw bytes)
 *   [--remote-key-id-hex <16 hex>]                   default all-zero id
 * Missing TLS files or PSK, a malformed value, an unknown --remote-* flag,
 * or any --remote-* option without --remote fails the parse (fail closed).
 * The first non --remote* argument stays the optional scene path.
 * Default admission rate limits: global 20 accepts/s (burst 40), 120 accepts
 * per source IP per minute. A connection that has not authenticated within
 * 10 s is closed. */
#define BREAK_EDITOR_REMOTE_DEFAULT_PORT 47700u
#define BREAK_EDITOR_REMOTE_DEFAULT_RATE_PER_SEC 20u
#define BREAK_EDITOR_REMOTE_DEFAULT_RATE_BURST 40u
#define BREAK_EDITOR_REMOTE_DEFAULT_RATE_PER_IP_PER_MIN 120u
#define BREAK_EDITOR_REMOTE_DEFAULT_AUTH_TIMEOUT_MS 10000u

typedef struct BreakEditorRemoteCli {
    bool enabled;
    uint16_t port;
    const char *cert_file, *key_file, *ca_file; /* borrowed from argv */
    bool has_psk;
    uint8_t psk[32];
    uint8_t key_id[8];
    /* --remote-keyring-file: every key of the file (key_count > 0; the
     * single psk/key_id fields are then unused). */
    struct {
        uint8_t key_id[8];
        uint8_t psk[32];
    } keys[8];
    uint32_t key_count;
    const char *keyring_path;                   /* borrowed from argv */
    const char *scene_path;                     /* borrowed from argv */
} BreakEditorRemoteCli;

/* false + a NUL-terminated message in err (when err_cap > 0) on any error. */
bool break_editor_remote_cli_parse(int argc, char **argv,
                                   BreakEditorRemoteCli *out, char *err,
                                   size_t err_cap);
/* Hands the parsed key(s) to the remote: set_psk for --remote-psk-*, or
 * set_psk(first) + add_key(rest) for --remote-keyring-file. */
bool break_editor_remote_cli_install_keys(const BreakEditorRemoteCli *cli,
                                          BreakEditorRemote *r);
/* Wipes the parsed PSK (a volatile store the optimizer keeps); call it as
 * soon as the PSK has been handed to break_editor_remote_set_psk. */
void break_editor_remote_cli_wipe(BreakEditorRemoteCli *cli);
/* TLS-required, loopback-bound config with the default rate limits; the
 * strings stay borrowed from the cli (argv) storage. */
void break_editor_remote_cli_to_config(const BreakEditorRemoteCli *cli,
                                       BreakEditorRemoteConfig *out);
