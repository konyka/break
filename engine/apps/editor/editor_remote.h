#pragma once
/* BreakEditorRemote — Stage 4 scene editor Phase 4 Task 1: the remote
 * session host core. Owns a STEP-mode BreakNetReactor (the shell thread
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
 * Task 2's --remote flag plumbing) creates and starts it explicitly.
 * use_tls=false is the documented TEST/DEV plaintext seam only; TLS +
 * CHALLENGE/AUTH-v2 wiring is Task 2 scope (the config fields exist now so
 * the interface is verbatim-stable). The Task 1 plaintext seam auto-marks
 * sessions AUTHENTICATED on open (dev seam — documented, loopback-first);
 * use_tls=true without cert/key fails start (fail closed).
 *
 * Fail closed: any unknown message id / malformed payload / oversize frame
 * is rejected by the envelope codec or the handler and closes the
 * connection; a handler-side command failure answers
 * BREAK_EDITOR_MSG_RESULT with a non-ok status instead.
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
/* Test-only accessors for diagnostics. */
void *break_editor_remote_manager_for_test(BreakEditorRemote *r);
