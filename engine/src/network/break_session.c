#include "network/break_session.h"
#include "network/break_net_adapter.h"
#include "network/break_net_message_registry.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#ifdef BREAK_ENABLE_CRYPTO
#include "crypto/break_crypto.h"
#include <stdatomic.h>
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#include <time.h>
extern int clock_gettime(int, struct timespec *);
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
#endif
#endif

#define BREAK_SESSION_DEFAULT_MAX 64u

typedef struct BreakSessionEntry {
    BreakConnectionKey connection;
    BreakSessionId id;
    BreakSessionState state;
    bool used;
    bool auth_seen;
    bool ping_seen;
    uint32_t ping_sequence;
    bool message_seen[BREAK_NET_REGISTRY_MAX_MESSAGES];
    uint32_t message_sequences[BREAK_NET_REGISTRY_MAX_MESSAGES];
#ifdef BREAK_ENABLE_CRYPTO
    u8 server_nonce[16];
    bool server_nonce_valid;
    u64 authenticated_at_us;
#endif
} BreakSessionEntry;

typedef struct BreakSessionHandlerEntry {
    BreakSessionMessageHandler handler;
    void *user_data;
} BreakSessionHandlerEntry;

struct BreakSessionManager {
    size_t capacity;
    size_t count;
    BreakSessionId next_id;
    BreakSessionEntry *entries;
    BreakNetReactor *reactor;
    const BreakNetMessageRegistry *registry;
    BreakSessionHandlerEntry handlers[BREAK_NET_MESSAGE_ID_MAX + 1u];
    BreakSessionApplyResult last_result;
    BreakSessionApplyStats stats;
#ifdef BREAK_ENABLE_CRYPTO
    u32 max_age_seconds;
    bool auth_operation_active;
#endif
};

#ifdef BREAK_ENABLE_CRYPTO
static atomic_flag break_session_auth_lock = ATOMIC_FLAG_INIT;
static BreakNetAuthKeyFn break_session_auth_fn;
static void *break_session_auth_user;
static size_t break_session_non_new_count;
static size_t break_session_auth_operation_count;

extern bool break_net_reactor_auth_server_nonce_for_session(
    BreakNetReactor *reactor, uint64_t connection_key, u8 out_nonce[16]);
bool break_session_auth_configured_internal(void);

static void break_session_auth_lock_acquire(void)
{
    while (atomic_flag_test_and_set_explicit(&break_session_auth_lock,
                                             memory_order_acquire)) {
    }
}

static void break_session_auth_lock_release(void)
{
    atomic_flag_clear_explicit(&break_session_auth_lock, memory_order_release);
}

bool break_session_auth_configured_internal(void)
{
    bool configured;
    break_session_auth_lock_acquire();
    configured = break_session_auth_fn != NULL;
    break_session_auth_lock_release();
    return configured;
}

bool break_session_set_auth(BreakNetAuthKeyFn fn, void *user)
{
    bool accepted;
    break_session_auth_lock_acquire();
    accepted = break_session_non_new_count == 0u &&
               break_session_auth_operation_count == 0u;
    if (accepted) {
        break_session_auth_fn = fn;
        break_session_auth_user = fn != NULL ? user : NULL;
    }
    break_session_auth_lock_release();
    return accepted;
}

static BreakSessionAuthTestHook break_session_auth_test_hook;
static void *break_session_auth_test_hook_user;

void break_session_auth_set_test_hook_for_test(BreakSessionAuthTestHook hook,
                                               void *user)
{
    break_session_auth_test_hook = hook;
    break_session_auth_test_hook_user = user;
}

static bool break_session_auth_operation_begin(BreakSessionManager *manager,
                                               BreakNetAuthKeyFn *fn, void **user)
{
    break_session_auth_lock_acquire();
    ++break_session_auth_operation_count;
    manager->auth_operation_active = true;
    *fn = break_session_auth_fn;
    *user = break_session_auth_user;
    break_session_auth_lock_release();
    if (break_session_auth_test_hook != NULL) {
        break_session_auth_test_hook(break_session_auth_test_hook_user);
    }
    return *fn != NULL;
}

static void break_session_auth_operation_end(BreakSessionManager *manager)
{
    if (!manager->auth_operation_active) return;
    manager->auth_operation_active = false;
    break_session_auth_lock_acquire();
    if (break_session_auth_operation_count != 0u) {
        --break_session_auth_operation_count;
    }
    break_session_auth_lock_release();
}

static void break_session_state_store(BreakSessionEntry *entry, BreakSessionState state)
{
    bool account = (entry->state == BREAK_SESSION_NEW && state != BREAK_SESSION_NEW) ||
                   (entry->state != BREAK_SESSION_CLOSED && state == BREAK_SESSION_CLOSED);
    if (account) break_session_auth_lock_acquire();
    entry->state = state;
    if (account) {
        if (state == BREAK_SESSION_CLOSED) {
            if (break_session_non_new_count != 0u) --break_session_non_new_count;
        } else {
            ++break_session_non_new_count;
        }
        break_session_auth_lock_release();
    }
}

static u64 break_session_monotonic_us(void)
{
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    return (u64)GetTickCount64() * UINT64_C(1000);
#else
    struct timespec now;
    if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) return 0u;
    return (u64)now.tv_sec * UINT64_C(1000000) + (u64)now.tv_nsec / UINT64_C(1000);
#endif
}

void break_session_set_max_age(BreakSession *s, u32 max_age_seconds)
{
    if (s != NULL) s->max_age_seconds = max_age_seconds;
}
#else
static void break_session_state_store(BreakSessionEntry *entry, BreakSessionState state)
{
    entry->state = state;
}
#endif

static BreakSessionEntry *find_entry(BreakSessionManager *manager,
                                     BreakConnectionKey connection)
{
    size_t i;
    for (i = 0u; i < manager->capacity; ++i) {
        if (manager->entries[i].used && manager->entries[i].connection == connection) {
            return &manager->entries[i];
        }
    }
    return NULL;
}

static const BreakSessionEntry *find_const_entry(const BreakSessionManager *manager,
                                                 BreakConnectionKey connection)
{
    size_t i;
    for (i = 0u; i < manager->capacity; ++i) {
        if (manager->entries[i].used && manager->entries[i].connection == connection) {
            return &manager->entries[i];
        }
    }
    return NULL;
}

BreakSessionManager *break_session_manager_create(const BreakSessionConfig *config)
{
    BreakSessionManager *manager;
    size_t capacity = BREAK_SESSION_DEFAULT_MAX;
    BreakSessionId first_id = 1u;

    if (config != NULL) {
        if (config->max_sessions != 0u) {
            capacity = config->max_sessions;
        }
        if (config->first_session_id != 0u) {
            first_id = config->first_session_id;
        }
    }
    if (capacity > SIZE_MAX / sizeof(BreakSessionEntry) ||
        (config != NULL && config->registry != NULL &&
         config->registry->count > BREAK_NET_REGISTRY_MAX_MESSAGES)) {
        return NULL;
    }
    manager = (BreakSessionManager *)calloc(1u, sizeof(*manager));
    if (manager == NULL) {
        return NULL;
    }
    manager->entries = (BreakSessionEntry *)calloc(capacity, sizeof(*manager->entries));
    if (manager->entries == NULL) {
        free(manager);
        return NULL;
    }
    manager->capacity = capacity;
    manager->next_id = first_id;
    manager->registry = config != NULL && config->registry != NULL
                            ? config->registry : break_net_message_registry_default();
    return manager;
}

void break_session_manager_destroy(BreakSessionManager *manager)
{
    if (manager != NULL) {
#ifdef BREAK_ENABLE_CRYPTO
        size_t i;
        size_t non_new = 0u;
        for (i = 0u; i < manager->capacity; ++i) {
            if (manager->entries[i].used &&
                manager->entries[i].state != BREAK_SESSION_NEW &&
                manager->entries[i].state != BREAK_SESSION_CLOSED) {
                ++non_new;
            }
        }
        break_session_auth_lock_acquire();
        if (break_session_non_new_count >= non_new) {
            break_session_non_new_count -= non_new;
        } else {
            break_session_non_new_count = 0u;
        }
        break_session_auth_lock_release();
#endif
        free(manager->entries);
        free(manager);
    }
}

bool break_session_manager_bind(BreakSessionManager *manager, BreakConnectionKey connection)
{
    size_t i;
    if (manager == NULL || connection == 0u || find_entry(manager, connection) != NULL) {
        return false;
    }
    if (manager->count == manager->capacity ||
        (manager->next_id == UINT64_MAX && manager->count != 0u)) {
        return false;
    }
    for (i = 0u; i < manager->capacity; ++i) {
        if (!manager->entries[i].used) {
            manager->entries[i].used = true;
            manager->entries[i].connection = connection;
            manager->entries[i].id = manager->next_id;
            if (manager->next_id != UINT64_MAX) {
                ++manager->next_id;
            }
            manager->entries[i].state = BREAK_SESSION_NEW;
            ++manager->count;
            return true;
        }
    }
    return false;
}

bool break_session_manager_transition(BreakSessionManager *manager,
                                      BreakConnectionKey connection,
                                      BreakSessionState state)
{
    BreakSessionEntry *entry;
    if (manager == NULL || state == BREAK_SESSION_UNKNOWN) {
        return false;
    }
    entry = find_entry(manager, connection);
    if (entry == NULL || entry->state == BREAK_SESSION_CLOSED) {
        return false;
    }
    if ((entry->state == BREAK_SESSION_NEW &&
         (state == BREAK_SESSION_AUTHENTICATING || state == BREAK_SESSION_CLOSING)) ||
        (entry->state == BREAK_SESSION_AUTHENTICATING &&
         (state == BREAK_SESSION_AUTHENTICATED || state == BREAK_SESSION_CLOSING)) ||
        (entry->state == BREAK_SESSION_AUTHENTICATED && state == BREAK_SESSION_CLOSING) ||
        (entry->state == BREAK_SESSION_CLOSING && state == BREAK_SESSION_CLOSED)) {
        break_session_state_store(entry, state);
        return true;
    }
    return false;
}

bool break_session_manager_begin_auth(BreakSessionManager *manager, BreakConnectionKey connection)
{
    return break_session_manager_transition(manager, connection,
                                             BREAK_SESSION_AUTHENTICATING);
}

bool break_session_manager_auth_succeeded(BreakSessionManager *manager,
                                          BreakConnectionKey connection)
{
    bool transitioned = break_session_manager_transition(manager, connection,
                                                          BREAK_SESSION_AUTHENTICATED);
#ifdef BREAK_ENABLE_CRYPTO
    if (transitioned) {
        BreakSessionEntry *entry = find_entry(manager, connection);
        entry->authenticated_at_us = break_session_monotonic_us();
    }
#endif
    return transitioned;
}

bool break_session_manager_close(BreakSessionManager *manager,
                                  BreakConnectionKey connection, uint32_t reason)
{
    (void)reason;
    return break_session_manager_transition(manager, connection, BREAK_SESSION_CLOSING);
}

bool break_session_manager_apply_event(BreakSessionManager *manager,
                                       BreakConnectionKey connection,
                                       BreakSessionEvent event)
{
    if (event != BREAK_SESSION_EVENT_AUTHENTICATED) {
        return false;
    }
    return break_session_manager_auth_succeeded(manager, connection);
}

static bool break_session_record(BreakSessionManager *manager,
                                 BreakSessionApplyResult result)
{
#ifdef BREAK_ENABLE_CRYPTO
    break_session_auth_operation_end(manager);
#endif
    manager->last_result = result;
    switch (result) {
    case BREAK_SESSION_APPLY_OK: ++manager->stats.applied; break;
    case BREAK_SESSION_APPLY_UNKNOWN: ++manager->stats.unknown; break;
    case BREAK_SESSION_APPLY_STALE: ++manager->stats.stale; break;
    case BREAK_SESSION_APPLY_INVALID: ++manager->stats.invalid; break;
    case BREAK_SESSION_APPLY_PHASE_REJECTED: ++manager->stats.phase_rejected; break;
    case BREAK_SESSION_APPLY_DUPLICATE: ++manager->stats.duplicate; break;
    case BREAK_SESSION_APPLY_HANDLER_FAILED: ++manager->stats.handler_failed; break;
    }
    return result == BREAK_SESSION_APPLY_OK;
}

#ifdef BREAK_ENABLE_CRYPTO
static bool break_session_auth_fail(BreakSessionManager *manager,
                                    BreakConnectionKey connection,
                                    BreakSessionApplyResult result)
{
    (void)break_session_manager_close(manager, connection, 0u);
    return break_session_record(manager, result);
}

static bool break_session_auth_tag(BreakNetAuthKeyFn fn, void *user,
                                   const u8 key_id[8], const u8 server_nonce[16],
                                   const u8 client_nonce[16], u8 out_tag[32])
{
    u8 psk[32];
    u8 context[40];
    bool ok;
    memcpy(context, "BRKAUTH2", 8u);
    memcpy(context + 8u, server_nonce, 16u);
    memcpy(context + 24u, client_nonce, 16u);
    ok = fn(user, key_id, psk) &&
         break_crypto_hmac_sha256(psk, sizeof(psk), context, sizeof(context), out_tag);
    memset(psk, 0, sizeof(psk));
    memset(context, 0, sizeof(context));
    return ok;
}

static bool break_session_auth_tag_equal(const u8 left[32], const u8 right[32])
{
    u8 difference = 0u;
    size_t i;
    for (i = 0u; i < 32u; ++i) difference |= (u8)(left[i] ^ right[i]);
    return difference == 0u;
}

static bool break_session_auth_v2_received(
    BreakSessionManager *manager, BreakSessionEntry *entry,
    const BreakNetEvent *event, size_t definition_index,
    BreakNetAuthKeyFn fn, void *user)
{
    const u8 *payload = (const u8 *)event->message.data;
    u8 expected_tag[32];
    if (event->message.protocol_version != 2u || event->message.size != 56u ||
        payload == NULL || !entry->server_nonce_valid) {
        return break_session_auth_fail(manager, event->connection_key,
                                       BREAK_SESSION_APPLY_HANDLER_FAILED);
    }
    if (entry->state == BREAK_SESSION_NEW &&
        !break_session_manager_begin_auth(manager, event->connection_key)) {
        return break_session_auth_fail(manager, event->connection_key,
                                       BREAK_SESSION_APPLY_INVALID);
    }
    if (entry->state != BREAK_SESSION_AUTHENTICATING ||
        !break_session_auth_tag(fn, user, payload, entry->server_nonce,
                                payload + 8u, expected_tag) ||
        !break_session_auth_tag_equal(expected_tag, payload + 24u)) {
        return break_session_auth_fail(manager, event->connection_key,
                                       BREAK_SESSION_APPLY_HANDLER_FAILED);
    }
    entry->message_seen[definition_index] = true;
    entry->message_sequences[definition_index] = event->message.sequence;
    entry->auth_seen = true;
    if (!break_session_manager_auth_succeeded(manager, event->connection_key)) {
        return break_session_auth_fail(manager, event->connection_key,
                                       BREAK_SESSION_APPLY_INVALID);
    }
    return break_session_record(manager, BREAK_SESSION_APPLY_OK);
}

static bool break_session_challenge_received(
    BreakSessionManager *manager, BreakSessionEntry *entry,
    const BreakNetEvent *event, size_t definition_index,
    BreakNetAuthKeyFn fn, void *user)
{
    static const u8 zero_key_id[8] = {0u};
    u8 client_nonce[16];
    u8 payload[56];
    if (event->message.protocol_version != 1u || event->message.size != 16u ||
        event->message.data == NULL || entry->server_nonce_valid ||
        entry->state != BREAK_SESSION_NEW ||
        !break_session_manager_begin_auth(manager, event->connection_key)) {
        return break_session_auth_fail(manager, event->connection_key,
                                       BREAK_SESSION_APPLY_HANDLER_FAILED);
    }
    memset(payload, 0, sizeof(payload));
    if (!break_crypto_random(client_nonce, sizeof(client_nonce)) ||
        !break_session_auth_tag(fn, user, zero_key_id,
                                (const u8 *)event->message.data,
                                client_nonce, payload + 24u)) {
        return break_session_auth_fail(manager, event->connection_key,
                                       BREAK_SESSION_APPLY_HANDLER_FAILED);
    }
    memcpy(payload + 8u, client_nonce, sizeof(client_nonce));
    if (break_net_reactor_send(manager->reactor, event->connection_key,
                               BREAK_NET_MESSAGE_ID_AUTH, 2u,
                               payload, sizeof(payload)) != BREAK_NET_SEND_OK) {
        return break_session_auth_fail(manager, event->connection_key,
                                       BREAK_SESSION_APPLY_HANDLER_FAILED);
    }
    entry->message_seen[definition_index] = true;
    entry->message_sequences[definition_index] = event->message.sequence;
    return break_session_record(manager, BREAK_SESSION_APPLY_OK);
}
#endif

bool break_session_manager_apply_adapter_event(BreakSessionManager *manager,
                                                const BreakNetEvent *event)
{
    BreakSessionEntry *entry;
    const BreakNetMessageDefinition *definition;
    BreakSessionHandlerEntry *handler;
    bool handled;
    if (manager == NULL || event == NULL || event->connection_key == 0u) {
        return false;
    }
    entry = find_entry(manager, event->connection_key);
    switch (event->type) {
    case BREAK_NET_EVENT_CONNECTION_OPENED:
        if (entry != NULL) {
            return break_session_record(manager,
                                        entry->state == BREAK_SESSION_CLOSING ||
                                                entry->state == BREAK_SESSION_CLOSED
                                            ? BREAK_SESSION_APPLY_STALE
                                            : BREAK_SESSION_APPLY_DUPLICATE);
        }
        handled = break_session_manager_bind(manager, event->connection_key);
#ifdef BREAK_ENABLE_CRYPTO
        if (handled) {
            entry = find_entry(manager, event->connection_key);
            entry->server_nonce_valid = break_session_auth_configured_internal() &&
                break_net_reactor_auth_server_nonce_for_session(
                    manager->reactor, event->connection_key, entry->server_nonce);
        }
#endif
        return break_session_record(manager, handled ? BREAK_SESSION_APPLY_OK :
                                     BREAK_SESSION_APPLY_INVALID);
    case BREAK_NET_EVENT_CONNECTION_CLOSED:
    case BREAK_NET_EVENT_TRANSPORT_ERROR:
        handled = break_session_manager_close(manager, event->connection_key, event->reason);
        return break_session_record(manager, handled ? BREAK_SESSION_APPLY_OK :
                                     (entry == NULL ? BREAK_SESSION_APPLY_UNKNOWN :
                                      BREAK_SESSION_APPLY_STALE));
    case BREAK_NET_EVENT_MESSAGE_RECEIVED:
        if (entry == NULL) return break_session_record(manager, BREAK_SESSION_APPLY_UNKNOWN);
        if (entry->state == BREAK_SESSION_CLOSING || entry->state == BREAK_SESSION_CLOSED) {
            return break_session_record(manager, BREAK_SESSION_APPLY_STALE);
        }
        definition = break_net_message_registry_lookup(
            manager->registry, event->message.message_id);
        if (definition == NULL || !break_net_message_definition_supports_version(
                definition, event->message.protocol_version) ||
            event->message.size > definition->payload_limit) {
            (void)break_session_manager_close(manager, event->connection_key, 0u);
            return break_session_record(manager, BREAK_SESSION_APPLY_INVALID);
        }
        if ((definition->phase == BREAK_NET_MESSAGE_PHASE_AUTHENTICATING &&
             entry->state != BREAK_SESSION_AUTHENTICATING) ||
            (definition->phase == BREAK_NET_MESSAGE_PHASE_AUTHENTICATED &&
             entry->state != BREAK_SESSION_AUTHENTICATED)) {
            return break_session_record(manager, BREAK_SESSION_APPLY_PHASE_REJECTED);
        }
        {
            size_t definition_index = (size_t)(definition - manager->registry->definitions);
            if (definition_index >= BREAK_NET_REGISTRY_MAX_MESSAGES) {
                return break_session_record(manager, BREAK_SESSION_APPLY_INVALID);
            }
            if (entry->message_seen[definition_index] &&
                (definition->duplicate_policy == BREAK_NET_DUPLICATE_REJECT ||
                 event->message.sequence == entry->message_sequences[definition_index])) {
                if (definition->duplicate_policy == BREAK_NET_DUPLICATE_IDEMPOTENT) {
                    return break_session_record(manager, BREAK_SESSION_APPLY_OK);
                }
                return break_session_record(manager, BREAK_SESSION_APPLY_DUPLICATE);
            }
#ifdef BREAK_ENABLE_CRYPTO
            {
                BreakNetAuthKeyFn auth_fn;
                void *auth_user;
                bool auth_configured = false;
                if (event->message.message_id == BREAK_NET_MESSAGE_ID_AUTH ||
                    event->message.message_id == BREAK_NET_MESSAGE_ID_CHALLENGE) {
                    auth_configured = break_session_auth_operation_begin(
                        manager, &auth_fn, &auth_user);
                }
                if (event->message.message_id == BREAK_NET_MESSAGE_ID_CHALLENGE &&
                    auth_configured) {
                    return break_session_challenge_received(
                        manager, entry, event, definition_index, auth_fn, auth_user);
                }
                if (event->message.message_id == BREAK_NET_MESSAGE_ID_AUTH &&
                    (auth_configured || event->message.protocol_version == 2u)) {
                    if (!auth_configured) {
                        return break_session_auth_fail(manager, event->connection_key,
                                                       BREAK_SESSION_APPLY_INVALID);
                    }
                    return break_session_auth_v2_received(
                        manager, entry, event, definition_index, auth_fn, auth_user);
                }
            }
#endif
            if (event->message.message_id == BREAK_NET_MESSAGE_ID_AUTH &&
                entry->state == BREAK_SESSION_NEW &&
                !break_session_manager_begin_auth(manager, event->connection_key)) {
                return break_session_record(manager, BREAK_SESSION_APPLY_INVALID);
            }
            handler = &manager->handlers[event->message.message_id];
            if (handler->handler == NULL ||
                !handler->handler(event->connection_key, &event->message, handler->user_data)) {
                if (event->message.message_id == BREAK_NET_MESSAGE_ID_AUTH) {
                    (void)break_session_manager_close(manager, event->connection_key, 0u);
                }
                return break_session_record(manager, BREAK_SESSION_APPLY_HANDLER_FAILED);
            }
            entry->message_seen[definition_index] = true;
            entry->message_sequences[definition_index] = event->message.sequence;
        }
        if (event->message.message_id == BREAK_NET_MESSAGE_ID_AUTH) {
            entry->auth_seen = true;
            (void)break_session_manager_auth_succeeded(manager, event->connection_key);
        }
        return break_session_record(manager, BREAK_SESSION_APPLY_OK);
    case BREAK_NET_EVENT_SEND_DRAINED:
    default:
        return break_session_record(manager, BREAK_SESSION_APPLY_INVALID);
    }
}

bool break_session_manager_attach_reactor(BreakSessionManager *manager,
                                          BreakNetReactor *reactor)
{
    if (manager == NULL || reactor == NULL || manager->reactor != NULL) {
        return false;
    }
    manager->reactor = reactor;
    return true;
}

bool break_session_manager_set_message_handler(BreakSessionManager *manager,
                                               uint16_t message_id,
                                               BreakSessionMessageHandler handler,
                                               void *user_data)
{
    if (manager == NULL || message_id == 0u || handler == NULL ||
        break_net_message_registry_lookup(manager->registry, message_id) == NULL) {
        return false;
    }
    manager->handlers[message_id].handler = handler;
    manager->handlers[message_id].user_data = user_data;
    return true;
}

size_t break_session_manager_poll_adapter(BreakSessionManager *manager,
                                           uint32_t max_events)
{
    BreakNetEvent event;
    size_t processed = 0u;
    if (manager == NULL || manager->reactor == NULL || max_events == 0u) {
        return 0u;
    }
    while (processed < (size_t)max_events &&
           break_net_reactor_poll_event(manager->reactor, &event) == BREAK_NET_EVENT_OK) {
        (void)break_session_manager_apply_adapter_event(manager, &event);
        break_net_event_release(&event);
        ++processed;
    }
    if (break_net_reactor_event_queue_empty(manager->reactor)) {
        (void)break_session_manager_poll(manager, max_events);
    }
    return processed;
}

size_t break_session_manager_poll(BreakSessionManager *manager, uint32_t max_events)
{
    size_t i;
    size_t closed = 0u;
    if (manager == NULL || max_events == 0u) {
        return 0u;
    }
    for (i = 0u; i < manager->capacity && closed < (size_t)max_events; ++i) {
        if (manager->entries[i].used &&
            manager->entries[i].state == BREAK_SESSION_CLOSING) {
            break_session_state_store(&manager->entries[i], BREAK_SESSION_CLOSED);
            ++closed;
        }
    }
#ifdef BREAK_ENABLE_CRYPTO
    if (manager->max_age_seconds != 0u) {
        u64 now = break_session_monotonic_us();
        u64 max_age_us = (u64)manager->max_age_seconds * UINT64_C(1000000);
        for (i = 0u; i < manager->capacity; ++i) {
            BreakSessionEntry *entry = &manager->entries[i];
            if (entry->used && entry->state == BREAK_SESSION_AUTHENTICATED &&
                now >= entry->authenticated_at_us &&
                now - entry->authenticated_at_us > max_age_us) {
                break_session_state_store(entry, BREAK_SESSION_CLOSING);
            }
        }
    }
#endif
    return closed;
}

BreakSessionState break_session_manager_state(const BreakSessionManager *manager,
                                               BreakConnectionKey connection)
{
    const BreakSessionEntry *entry;
    if (manager == NULL) {
        return BREAK_SESSION_UNKNOWN;
    }
    entry = find_const_entry(manager, connection);
    return entry == NULL ? BREAK_SESSION_UNKNOWN : entry->state;
}

BreakSessionId break_session_manager_session_id(const BreakSessionManager *manager,
                                                BreakConnectionKey connection)
{
    const BreakSessionEntry *entry;
    if (manager == NULL) {
        return 0u;
    }
    entry = find_const_entry(manager, connection);
    return entry == NULL ? 0u : entry->id;
}

BreakSessionApplyResult break_session_manager_last_result(
    const BreakSessionManager *manager)
{
    return manager == NULL ? BREAK_SESSION_APPLY_INVALID : manager->last_result;
}

void break_session_manager_apply_stats(const BreakSessionManager *manager,
                                       BreakSessionApplyStats *stats)
{
    if (stats != NULL) {
        *stats = manager == NULL ? (BreakSessionApplyStats){0} : manager->stats;
    }
}
