#include "network/break_session.h"
#include "network/break_net_adapter.h"
#include "network/break_net_message_registry.h"

#include <limits.h>
#include <stdlib.h>

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
};

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
        entry->state = state;
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
    return break_session_manager_transition(manager, connection,
                                             BREAK_SESSION_AUTHENTICATED);
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
            manager->entries[i].state = BREAK_SESSION_CLOSED;
            ++closed;
        }
    }
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
