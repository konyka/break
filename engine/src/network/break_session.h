#ifndef BREAK_SESSION_H
#define BREAK_SESSION_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "network/break_net_events.h"
#include "network/break_net_message_registry.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakSessionManager BreakSessionManager;
typedef struct BreakNetReactor BreakNetReactor;
typedef uint64_t BreakConnectionKey;
typedef uint64_t BreakSessionId;

#ifdef BREAK_ENABLE_CRYPTO
#include "core/types.h"

typedef BreakSessionManager BreakSession;
/* CHALLENGE payload (message_id=3, v1): server_nonce[16]. AUTH v2 payload
 * (message_id=1, version 2, 56 bytes): key_id[8] || client_nonce[16] || tag[32],
 * where tag = HMAC-SHA256(psk, "BRKAUTH2" || server_nonce || client_nonce). */
typedef bool (*BreakNetAuthKeyFn)(void *user, const u8 key_id[8], u8 out_psk[32]);
/* Process-wide because the pinned interface has no manager parameter. Changes
 * are accepted only while every session is NEW and no authentication message
 * operation is active; NULL clears the configuration. An operation pins its
 * snapshot and callback through its first state transition and final dispatch.
 * The callback resolves key_id, so provisioning and rollover stay app-side.
 * The built-in CHALLENGE client helper requests the all-zero key_id. */
bool break_session_set_auth(BreakNetAuthKeyFn fn, void *user);
/* Test-only hook at the pinned snapshot point, before the first transition. */
typedef void (*BreakSessionAuthTestHook)(void *user);
void break_session_auth_set_test_hook_for_test(BreakSessionAuthTestHook hook,
                                               void *user);
/* Optional session expiry (0 = no expiry, default); authenticated sessions
 * older than max_age_seconds enter CLOSING at the next GameThread poll. */
void break_session_set_max_age(BreakSession *s, u32 max_age_seconds);
#endif

typedef enum BreakSessionState {
    BREAK_SESSION_NEW = 0,
    BREAK_SESSION_AUTHENTICATING,
    BREAK_SESSION_AUTHENTICATED,
    BREAK_SESSION_CLOSING,
    BREAK_SESSION_CLOSED,
    BREAK_SESSION_UNKNOWN
} BreakSessionState;

typedef enum BreakSessionEvent {
    BREAK_SESSION_EVENT_AUTHENTICATED = 0
} BreakSessionEvent;

typedef enum BreakSessionApplyResult {
    BREAK_SESSION_APPLY_OK = 0,
    BREAK_SESSION_APPLY_UNKNOWN,
    BREAK_SESSION_APPLY_STALE,
    BREAK_SESSION_APPLY_INVALID,
    BREAK_SESSION_APPLY_PHASE_REJECTED,
    BREAK_SESSION_APPLY_DUPLICATE,
    BREAK_SESSION_APPLY_HANDLER_FAILED
} BreakSessionApplyResult;

typedef struct BreakSessionApplyStats {
    uint64_t applied;
    uint64_t unknown;
    uint64_t stale;
    uint64_t invalid;
    uint64_t phase_rejected;
    uint64_t duplicate;
    uint64_t handler_failed;
} BreakSessionApplyStats;

typedef bool (*BreakSessionMessageHandler)(BreakConnectionKey connection,
                                           const BreakNetOwnedMessage *message,
                                           void *user_data);

typedef struct BreakSessionConfig {
    size_t max_sessions;
    BreakSessionId first_session_id;
    /* Borrowed immutable registry; it must outlive the manager. */
    const BreakNetMessageRegistry *registry;
} BreakSessionConfig;

/* The manager is GameThread-owned and not thread-safe. */
BreakSessionManager *break_session_manager_create(const BreakSessionConfig *config);
void break_session_manager_destroy(BreakSessionManager *manager);
/* Advances close finalization and configured expiry without polling the reactor.
 * max_events bounds CLOSED finalization, not the capacity-bounded expiry scan. */
size_t break_session_manager_poll(BreakSessionManager *manager, uint32_t max_events);
bool break_session_manager_bind(BreakSessionManager *manager, BreakConnectionKey connection);
bool break_session_manager_begin_auth(BreakSessionManager *manager, BreakConnectionKey connection);
bool break_session_manager_auth_succeeded(BreakSessionManager *manager,
                                          BreakConnectionKey connection);
bool break_session_manager_close(BreakSessionManager *manager,
                                  BreakConnectionKey connection, uint32_t reason);
bool break_session_manager_transition(BreakSessionManager *manager,
                                      BreakConnectionKey connection,
                                      BreakSessionState state);
bool break_session_manager_apply_event(BreakSessionManager *manager,
                                        BreakConnectionKey connection,
                                        BreakSessionEvent event);
/* Applies one adapter event; payload is borrowed for handler duration only.
 * Registry-rejected messages record INVALID and enter CLOSING. */
bool break_session_manager_apply_adapter_event(BreakSessionManager *manager,
                                                const BreakNetEvent *event);
/* Borrowed reactor; it must outlive detach (not currently exposed) or manager destroy. */
bool break_session_manager_attach_reactor(BreakSessionManager *manager,
                                          BreakNetReactor *reactor);
/* handler and user_data are borrowed; the handler is called only on the GameThread. */
bool break_session_manager_set_message_handler(BreakSessionManager *manager,
                                               uint16_t message_id,
                                               BreakSessionMessageHandler handler,
                                               void *user_data);
/* Polls the borrowed reactor on the GameThread and applies up to max_events. */
size_t break_session_manager_poll_adapter(BreakSessionManager *manager,
                                           uint32_t max_events);
BreakSessionState break_session_manager_state(const BreakSessionManager *manager,
                                               BreakConnectionKey connection);
BreakSessionId break_session_manager_session_id(const BreakSessionManager *manager,
                                                BreakConnectionKey connection);
BreakSessionApplyResult break_session_manager_last_result(
    const BreakSessionManager *manager);
void break_session_manager_apply_stats(const BreakSessionManager *manager,
                                       BreakSessionApplyStats *stats);

#ifdef __cplusplus
}
#endif

#endif
