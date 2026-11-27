#include <runtime/runtime_world_session.h>

#include <core/platform_thread.h>
#include <runtime/runtime_metrics.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUNTIME_WORLD_DEFAULT_QUEUE_CAPACITY 64u
#define RUNTIME_WORLD_MAX_QUEUE_CAPACITY 256u
#define RUNTIME_WORLD_DEFAULT_CONNECTIONS 8u
#define RUNTIME_WORLD_MAX_CONNECTIONS 64u

typedef struct {
    u64 key;
    u64 epoch;
    u64 completed_publication_epoch;
    u64 terminal_publication_epoch;
    u64 attempt_publication_epoch;
    u64 attempt_target_snapshot_id;
    u64 attempt_target_tick;
    u64 held_publication_epoch;
    bool retry_publish;
    bool publish_ready;
    bool has_reader;
    bool log_blocked; /* terminal log result; cleared by the next notice */
    BreakWorldSnapshotReaderId reader;
} RuntimeWorldConnection;

struct BreakRuntimeWorldSession {
    BreakWorldSession *session;
    BreakRuntimeBus *bus;
    BreakWorldSnapshotPublication *publication;
    BreakWorldSnapshotLog *log;
    BreakRuntimeQueue *queue;
    PlatformMutex mutex;
    u32 subscriber_id;
    u32 max_connections;
    u32 publish_connection_budget;
    bool publish_requires_ready;
    bool publish_waits_for_ack;
    BreakWorldSnapshotEntityFilter publish_keep;
    void *(*publish_keep_user_for)(void *ctx, u64 connection_key);
    void *publish_keep_ctx;
    bool closed;
    bool unsubscribed;
    bool lifecycle_bound;
    bool lifecycle_destroying;
    void *lifecycle_binding;
    u64 next_connection_epoch;
    u64 next_sequence;
    u64 submitted;
    u64 drained;
    u64 applied;
    u64 rejected;
    u64 stale_rejected;
    u64 transport_overloads;
    u64 publish_overloads;
    u64 publish_terminal;
    bool control_pending;
    BreakRuntimeWorldCommand pending_command;
    u64 pending_correlation_id;
    bool publish_request;
    bool publish_continuation;
    /* Retained diagnostics / future request-level dedup state: written but not read by
     * the current accounting paths. Kept for existing tests and ABI stability. */
    u64 publish_request_level;
    u64 publish_observed_epoch;
    usize publish_cursor;
    RuntimeWorldConnection connections[];
};

static usize runtime_world_find_connection(const BreakRuntimeWorldSession *adapter, u64 key)
{
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        if (adapter->connections[i].key == key) return i;
    }
    return adapter->max_connections;
}

static bool runtime_world_command_valid(const BreakRuntimeWorldCommand *command)
{
    if (!command || command->reserved_zero != 0u) return false;
    switch (command->kind) {
        case BREAK_RUNTIME_WORLD_COMMAND_OPEN:
            return command->connection_key != 0u && command->connection_epoch == 0u &&
                   command->delta_id == 0u && command->target_snapshot_id == 0u &&
                   command->target_tick == 0u;
        case BREAK_RUNTIME_WORLD_COMMAND_CLOSE:
            return command->connection_key != 0u && command->connection_epoch != 0u &&
                   command->delta_id == 0u && command->target_snapshot_id == 0u &&
                   command->target_tick == 0u;
        case BREAK_RUNTIME_WORLD_COMMAND_REBASELINE:
            return command->connection_key == 0u && command->connection_epoch == 0u &&
                   command->delta_id == 0u && command->target_snapshot_id == 0u &&
                   command->target_tick == 0u;
        case BREAK_RUNTIME_WORLD_COMMAND_ACK:
            return command->connection_key != 0u && command->connection_epoch != 0u &&
                   command->delta_id != 0u && command->target_snapshot_id != 0u;
        case BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL:
            return command->connection_key != 0u && command->connection_epoch != 0u &&
                   command->delta_id == 0u;
        default:
            return false;
    }
}

static void runtime_world_record_result(BreakRuntimeWorldSession *adapter,
                                        BreakRuntimeError result, bool transport)
{
    if (result == BREAK_RUNTIME_OK) {
        adapter->applied++;
    } else if (result == BREAK_RUNTIME_OVERLOAD) {
        if (transport) adapter->transport_overloads++;
    } else {
        adapter->rejected++;
        if (result == BREAK_RUNTIME_STALE) adapter->stale_rejected++;
    }
}

static BreakRuntimeError runtime_world_send_control(BreakRuntimeWorldSession *adapter,
                                                    const BreakRuntimeWorldCommand *command,
                                                    u64 correlation_id)
{
    BreakWorldSessionControl control;
    BreakNetSendResult result;
    memset(&control, 0, sizeof(control));
    control.kind = command->kind == BREAK_RUNTIME_WORLD_COMMAND_ACK
                       ? BREAK_WORLD_SESSION_CONTROL_ACK
                       : BREAK_WORLD_SESSION_CONTROL_NEED_FULL;
    control.delta_id = command->delta_id;
    control.target_snapshot_id = command->target_snapshot_id;
    control.target_tick = command->target_tick;
    control.level_generation = command->level_generation;
    result = break_world_session_send_control_correlated(
        adapter->session, command->connection_key, &control, correlation_id);
    switch (result) {
        case BREAK_NET_SEND_OK:
            return BREAK_RUNTIME_OK;
        case BREAK_NET_SEND_INVALID:
            return BREAK_RUNTIME_INVALID;
        case BREAK_NET_SEND_OVERLOAD:
            return BREAK_RUNTIME_OVERLOAD;
        case BREAK_NET_SEND_CLOSED:
            return BREAK_RUNTIME_CLOSED;
        default:
            return BREAK_RUNTIME_FAILED;
    }
}

static bool runtime_world_publish_pending_locked(const BreakRuntimeWorldSession *adapter)
{
    return adapter->publish_request || adapter->publish_continuation;
}

static void runtime_world_clear_connection_publish(RuntimeWorldConnection *connection)
{
    connection->completed_publication_epoch = 0u;
    connection->terminal_publication_epoch = 0u;
    connection->attempt_publication_epoch = 0u;
    connection->attempt_target_snapshot_id = 0u;
    connection->attempt_target_tick = 0u;
    connection->held_publication_epoch = 0u;
    connection->retry_publish = false;
}

static void runtime_world_clear_publish(BreakRuntimeWorldSession *adapter, bool clear_attempts)
{
    adapter->publish_request = false;
    adapter->publish_continuation = false;
    adapter->publish_request_level = 0u;
    adapter->publish_observed_epoch = 0u;
    adapter->publish_cursor = 0u;
    if (!clear_attempts) return;
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        RuntimeWorldConnection *connection = &adapter->connections[i];
        connection->attempt_publication_epoch = 0u;
        connection->attempt_target_snapshot_id = 0u;
        connection->attempt_target_tick = 0u;
        connection->retry_publish = false;
    }
}

static void runtime_world_drop_reader(BreakRuntimeWorldSession *adapter,
                                      RuntimeWorldConnection *connection)
{
    if (!connection->has_reader) return;
    (void)break_world_snapshot_log_remove_reader(adapter->log, connection->reader);
    connection->has_reader = false;
    connection->reader = 0u;
}

/* A rebaselined level must not receive the old level's unread epochs: the
 * reader is replaced and the new one starts at the next published epoch. A
 * failed add (the log is at max_readers) leaves the connection without a
 * reader; it then receives nothing until it is closed and opened again. */
static void runtime_world_replace_reader(BreakRuntimeWorldSession *adapter,
                                         RuntimeWorldConnection *connection)
{
    BreakWorldSnapshotReaderId reader = 0u;
    if (connection->key == 0u || !adapter->log) return;
    runtime_world_drop_reader(adapter, connection);
    connection->log_blocked = false;
    if (break_world_snapshot_log_add_reader(adapter->log, &reader)) {
        connection->has_reader = true;
        connection->reader = reader;
    }
}

static BreakRuntimeError runtime_world_apply(BreakRuntimeWorldSession *adapter,
                                             const BreakRuntimeWorldCommand *command,
                                             u64 correlation_id)
{
    usize slot;
    u64 level;
    if (!runtime_world_command_valid(command)) return BREAK_RUNTIME_INVALID;
    level = break_world_session_level_generation(adapter->session);
    if (command->kind == BREAK_RUNTIME_WORLD_COMMAND_REBASELINE) {
        if (command->level_generation == 0u || command->level_generation <= level) {
            return BREAK_RUNTIME_STALE;
        }
        if (!break_world_session_rebaseline(adapter->session, command->level_generation)) {
            return BREAK_RUNTIME_STALE;
        }
        for (usize i = 0u; i < adapter->max_connections; ++i) {
            runtime_world_clear_connection_publish(&adapter->connections[i]);
            runtime_world_replace_reader(adapter, &adapter->connections[i]);
        }
        /* Adapter-level request/continuation/cursor/observed epoch only: per-connection
         * attempt scalars are healed by the Session rebaseline and the monotonic epoch,
         * so false avoids duplicating the Session cleanup (dropping only the per-connection
         * clear is an equivalent mutant; this line is the load-bearing one). */
        runtime_world_clear_publish(adapter, false);
        return BREAK_RUNTIME_OK;
    }
    if (command->kind == BREAK_RUNTIME_WORLD_COMMAND_OPEN) {
        u64 epoch;
        BreakWorldSnapshotReaderId reader = 0u;
        if (runtime_world_find_connection(adapter, command->connection_key) !=
            adapter->max_connections) {
            return BREAK_RUNTIME_REJECTED;
        }
        if (command->level_generation != level) return BREAK_RUNTIME_STALE;
        for (slot = 0u; slot < adapter->max_connections; ++slot) {
            if (adapter->connections[slot].key == 0u) break;
        }
        if (slot == adapter->max_connections) return BREAK_RUNTIME_REJECTED;
        if (adapter->next_connection_epoch == 0u) return BREAK_RUNTIME_REJECTED;
        epoch = adapter->next_connection_epoch;
        if (adapter->log &&
            !break_world_snapshot_log_add_reader(adapter->log, &reader)) {
            return BREAK_RUNTIME_REJECTED;
        }
        if (!break_world_session_open(adapter->session, command->connection_key)) {
            if (adapter->log) (void)break_world_snapshot_log_remove_reader(adapter->log, reader);
            return BREAK_RUNTIME_REJECTED;
        }
        runtime_world_clear_connection_publish(&adapter->connections[slot]);
        adapter->connections[slot].has_reader = adapter->log != NULL;
        adapter->connections[slot].log_blocked = false;
        adapter->connections[slot].reader = reader;
        adapter->connections[slot].key = command->connection_key;
        adapter->connections[slot].epoch = epoch;
        adapter->connections[slot].publish_ready = !adapter->publish_requires_ready;
        adapter->next_connection_epoch++;
        return BREAK_RUNTIME_OK;
    }

    slot = runtime_world_find_connection(adapter, command->connection_key);
    if (slot == adapter->max_connections ||
        adapter->connections[slot].epoch != command->connection_epoch) {
        return BREAK_RUNTIME_STALE;
    }
    if (command->level_generation != level) return BREAK_RUNTIME_STALE;
    if (command->kind == BREAK_RUNTIME_WORLD_COMMAND_CLOSE) {
        if (!break_world_session_close(adapter->session, command->connection_key)) {
            return BREAK_RUNTIME_REJECTED;
        }
        runtime_world_clear_connection_publish(&adapter->connections[slot]);
        runtime_world_drop_reader(adapter, &adapter->connections[slot]);
        memset(&adapter->connections[slot], 0, sizeof(adapter->connections[slot]));
        return BREAK_RUNTIME_OK;
    }
    return runtime_world_send_control(adapter, command, correlation_id);
}

static BreakRuntimeError runtime_world_apply_notice(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldPublishCurrentNotice *notice)
{
    if (!notice || notice->reserved_zero != 0u) return BREAK_RUNTIME_INVALID;
    if (notice->level_generation !=
        break_world_session_level_generation(adapter->session)) {
        return BREAK_RUNTIME_STALE;
    }
    adapter->publish_request = true;
    adapter->publish_request_level = notice->level_generation;
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        adapter->connections[i].log_blocked = false;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError runtime_world_retry(BreakRuntimeWorldSession *adapter)
{
    BreakRuntimeError result = runtime_world_send_control(
        adapter, &adapter->pending_command, adapter->pending_correlation_id);
    runtime_world_record_result(adapter, result, true);
    if (result != BREAK_RUNTIME_OVERLOAD) {
        adapter->control_pending = false;
        memset(&adapter->pending_command, 0, sizeof(adapter->pending_command));
        adapter->pending_correlation_id = 0u;
    }
    return result;
}

static bool runtime_world_publish_clean(const RuntimeWorldConnection *connection,
                                        const BreakWorldSessionSenderState *state,
                                        u64 publication_epoch)
{
    return !state->attempt_pending && !connection->retry_publish &&
           connection->attempt_publication_epoch == 0u &&
           connection->attempt_target_snapshot_id == 0u &&
           connection->attempt_target_tick == 0u &&
           (connection->completed_publication_epoch == publication_epoch ||
            connection->terminal_publication_epoch == publication_epoch ||
            connection->held_publication_epoch == publication_epoch);
}

/* The Session has a sent but unacknowledged target and nothing forces a full,
 * so a new target would only grow the history (legacy stop-and-wait rule). */
static bool runtime_world_publish_waits_for_ack(const BreakRuntimeWorldSession *adapter,
                                                const BreakWorldSessionSenderState *state)
{
    return adapter->publish_waits_for_ack && !state->attempt_pending &&
           state->history_count != 0u && !state->force_full;
}

static BreakRuntimeError runtime_world_publish_connection(
    BreakRuntimeWorldSession *adapter, usize slot,
    const BreakWorldSnapshotLease *lease, bool *out_called)
{
    RuntimeWorldConnection *connection = &adapter->connections[slot];
    BreakWorldSessionSenderState before;
    BreakWorldSessionSenderState after;
    BreakNetSendResult sent;
    u64 lease_id = break_world_snapshot_id(lease->snapshot);
    u64 lease_tick = break_world_snapshot_tick(lease->snapshot);
    u64 target_id;
    u64 target_tick;
    bool had_active;
    u64 old_id;
    u64 old_tick;
    bool same_current;
    bool same_saved;
    *out_called = false;
    if (!break_world_session_sender_state(adapter->session, connection->key, &before)) {
        connection->terminal_publication_epoch = lease->publication_epoch;
        connection->retry_publish = false;
        connection->attempt_publication_epoch = 0u;
        connection->attempt_target_snapshot_id = 0u;
        connection->attempt_target_tick = 0u;
        adapter->publish_terminal++;
        return BREAK_RUNTIME_FAILED;
    }
    if (runtime_world_publish_clean(connection, &before, lease->publication_epoch)) {
        return BREAK_RUNTIME_OK;
    }
    if (!connection->retry_publish && runtime_world_publish_waits_for_ack(adapter, &before)) {
        connection->held_publication_epoch = lease->publication_epoch;
        return BREAK_RUNTIME_OK;
    }

    had_active = before.attempt_pending;
    old_id = before.attempt_target_snapshot_id;
    old_tick = before.attempt_target_tick;
    same_saved = had_active && connection->attempt_target_snapshot_id != 0u &&
                 old_id == connection->attempt_target_snapshot_id &&
                 old_tick == connection->attempt_target_tick;

    /* Each connection may receive an AOI-filtered view of the shared target, so
     * its target identity is the filtered view's, reported back here. With no
     * filter configured target_id/target_tick equal the lease's (unchanged
     * behavior). */
    target_id = lease_id;
    target_tick = lease_tick;
    if (adapter->publish_keep) {
        void *keep_user = adapter->publish_keep_user_for
                              ? adapter->publish_keep_user_for(adapter->publish_keep_ctx,
                                                               connection->key)
                              : adapter->publish_keep_ctx;
        sent = break_world_session_publish_snapshot_filtered_id(
            adapter->session, connection->key, lease->snapshot, lease->level_generation,
            adapter->publish_keep, keep_user, &target_id, &target_tick);
    } else {
        sent = break_world_session_publish_snapshot_filtered_id(
            adapter->session, connection->key, lease->snapshot, lease->level_generation,
            NULL, NULL, &target_id, &target_tick);
    }
    same_current = had_active && old_id == target_id && old_tick == target_tick;
    *out_called = true;

    if (sent == BREAK_NET_SEND_OVERLOAD) {
        adapter->publish_overloads++;
        connection->retry_publish = true;
        if (break_world_session_sender_state(adapter->session, connection->key, &after) &&
            after.attempt_pending) {
            bool after_current = after.attempt_target_snapshot_id == target_id &&
                                 after.attempt_target_tick == target_tick;
            connection->attempt_target_snapshot_id = after.attempt_target_snapshot_id;
            connection->attempt_target_tick = after.attempt_target_tick;
            if (!had_active || after_current) {
                connection->attempt_publication_epoch = lease->publication_epoch;
            } else if (!same_saved) {
                connection->attempt_publication_epoch = 0u; /* unknown old attempt */
            } /* same_saved keeps the original attempt epoch, e.g. E1. */
        } else {
            connection->attempt_publication_epoch = 0u;
            connection->attempt_target_snapshot_id = 0u;
            connection->attempt_target_tick = 0u; /* no attempt created yet, keep retry */
        }
        return BREAK_RUNTIME_OVERLOAD;
    }

    if (sent == BREAK_NET_SEND_OK) {
        if (!break_world_session_sender_state(adapter->session, connection->key, &after) ||
            after.attempt_pending) {
            /* The Session contract is that OK ends the active attempt; a
             * violation is treated as a terminal FAILED without a permanent
             * continuation and without faking completed. */
            connection->retry_publish = false;
            connection->attempt_publication_epoch = 0u;
            connection->attempt_target_snapshot_id = 0u;
            connection->attempt_target_tick = 0u;
            connection->terminal_publication_epoch = lease->publication_epoch;
            adapter->publish_terminal++;
            return BREAK_RUNTIME_FAILED;
        }
        if (!had_active || same_current) {
            connection->completed_publication_epoch = lease->publication_epoch;
        } else if (same_saved && connection->attempt_publication_epoch != 0u) {
            connection->completed_publication_epoch = connection->attempt_publication_epoch;
        } /* unknown old attempt: completed stays, current remains dirty. */
        connection->retry_publish = false;
        connection->attempt_publication_epoch = 0u;
        connection->attempt_target_snapshot_id = 0u;
        connection->attempt_target_tick = 0u;
        return BREAK_RUNTIME_OK;
    }

    connection->retry_publish = false;
    connection->attempt_publication_epoch = 0u;
    connection->attempt_target_snapshot_id = 0u;
    connection->attempt_target_tick = 0u;
    connection->terminal_publication_epoch = lease->publication_epoch;
    adapter->publish_terminal++;
    if (sent == BREAK_NET_SEND_INVALID) return BREAK_RUNTIME_INVALID;
    if (sent == BREAK_NET_SEND_CLOSED) return BREAK_RUNTIME_CLOSED;
    return BREAK_RUNTIME_FAILED;
}

static bool runtime_world_recompute_continuation(
    BreakRuntimeWorldSession *adapter, u64 current_epoch)
{
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        const RuntimeWorldConnection *connection = &adapter->connections[i];
        BreakWorldSessionSenderState state;
        if (connection->key == 0u || !connection->publish_ready) continue;
        if (connection->retry_publish ||
            connection->attempt_publication_epoch != 0u ||
            connection->attempt_target_snapshot_id != 0u ||
            connection->attempt_target_tick != 0u) {
            return true;
        }
        if (break_world_session_sender_state(adapter->session, connection->key, &state) &&
            state.attempt_pending) {
            return true;
        }
        if (connection->completed_publication_epoch != current_epoch &&
            connection->terminal_publication_epoch != current_epoch &&
            connection->held_publication_epoch != current_epoch) {
            return true;
        }
    }
    return false;
}

static bool runtime_world_log_eligible(const RuntimeWorldConnection *connection)
{
    return connection->key != 0u && connection->publish_ready && connection->has_reader &&
           !connection->log_blocked;
}

static bool runtime_world_log_continuation(BreakRuntimeWorldSession *adapter)
{
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        const RuntimeWorldConnection *connection = &adapter->connections[i];
        BreakWorldSessionSenderState state;
        if (!runtime_world_log_eligible(connection)) continue;
        if (connection->retry_publish ||
            break_world_snapshot_log_backlog(adapter->log, connection->reader) != 0u) {
            return true;
        }
        if (break_world_session_sender_state(adapter->session, connection->key, &state) &&
            state.attempt_pending) {
            return true;
        }
    }
    return false;
}

/* Log source: each eligible connection drains its own reader in order until
 * it is up to date, its transport is full (OVERLOAD, resumed by the
 * continuation) or the per-drain budget of sent epochs is spent. */
static BreakRuntimeError runtime_world_publish_log(BreakRuntimeWorldSession *adapter)
{
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    u64 level = break_world_session_level_generation(adapter->session);
    u32 budget = adapter->publish_connection_budget;
    u32 calls = 0u;
    usize scanned = 0u;
    adapter->publish_request = false;
    adapter->publish_request_level = 0u;
    if (adapter->publish_cursor >= adapter->max_connections) adapter->publish_cursor = 0u;
    while (scanned < adapter->max_connections && calls < budget) {
        usize slot = adapter->publish_cursor;
        RuntimeWorldConnection *connection = &adapter->connections[slot];
        while (runtime_world_log_eligible(connection) && calls < budget) {
            BreakWorldSessionLogResult sent = break_world_session_publish_from_log(
                adapter->session, connection->key, adapter->log, connection->reader, level,
                NULL);
            if (sent == BREAK_WORLD_SESSION_LOG_IDLE) break;
            calls++;
            if (sent == BREAK_WORLD_SESSION_LOG_SENT) {
                connection->retry_publish = false;
                continue;
            }
            if (sent == BREAK_WORLD_SESSION_LOG_OVERLOAD) {
                adapter->publish_overloads++;
                connection->retry_publish = true;
                if (result == BREAK_RUNTIME_OK) result = BREAK_RUNTIME_OVERLOAD;
                break;
            }
            adapter->publish_terminal++;
            connection->retry_publish = false;
            connection->log_blocked = true;
            if (result == BREAK_RUNTIME_OK) {
                result = sent == BREAK_WORLD_SESSION_LOG_CLOSED ? BREAK_RUNTIME_CLOSED
                                                                : BREAK_RUNTIME_INVALID;
            }
        }
        adapter->publish_cursor = (slot + 1u) % adapter->max_connections;
        scanned++;
    }
    adapter->publish_continuation = runtime_world_log_continuation(adapter);
    return result;
}

static BreakRuntimeError runtime_world_publish_current(
    BreakRuntimeWorldSession *adapter)
{
    BreakWorldSnapshotLease lease;
    BreakWorldSnapshotAcquireResult acquired;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    u32 budget;
    u32 calls = 0u;
    usize scanned = 0u;
    if (!runtime_world_publish_pending_locked(adapter)) return BREAK_RUNTIME_OK;
    if (adapter->log) return runtime_world_publish_log(adapter);

    memset(&lease, 0, sizeof(lease));
    acquired = break_world_snapshot_publication_acquire(adapter->publication, &lease);
    if (acquired == BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY) {
        runtime_world_clear_publish(adapter, true);
        return BREAK_RUNTIME_OK;
    }
    if (acquired == BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED) {
        adapter->publish_terminal++;
        runtime_world_clear_publish(adapter, true);
        return BREAK_RUNTIME_CLOSED;
    }
    if (acquired != BREAK_WORLD_SNAPSHOT_ACQUIRE_OK) {
        adapter->publish_terminal++;
        runtime_world_clear_publish(adapter, true);
        return BREAK_RUNTIME_INVALID;
    }
    if (lease.level_generation != break_world_session_level_generation(adapter->session)) {
        adapter->publish_terminal++;
        runtime_world_clear_publish(adapter, true);
        result = BREAK_RUNTIME_STALE;
        goto release;
    }

    adapter->publish_request = false;
    adapter->publish_request_level = 0u;
    adapter->publish_observed_epoch = lease.publication_epoch;
    budget = adapter->publish_connection_budget < adapter->max_connections
                 ? adapter->publish_connection_budget
                 : adapter->max_connections;
    if (adapter->publish_cursor >= adapter->max_connections) adapter->publish_cursor = 0u;
    while (scanned < adapter->max_connections) {
        usize slot = adapter->publish_cursor;
        RuntimeWorldConnection *connection = &adapter->connections[slot];
        bool called = false;
        if (connection->key == 0u || !connection->publish_ready) {
            /* not eligible: skipped without consuming budget */
        } else if (calls == budget) {
            BreakWorldSessionSenderState state;
            if (!break_world_session_sender_state(adapter->session, connection->key, &state) ||
                !runtime_world_publish_clean(connection, &state, lease.publication_epoch)) {
                break;
            }
        } else {
            BreakRuntimeError connection_result = runtime_world_publish_connection(
                adapter, slot, &lease, &called);
            if (called) calls++;
            if (result == BREAK_RUNTIME_OK && connection_result != BREAK_RUNTIME_OK) {
                result = connection_result;
            }
        }
        adapter->publish_cursor = (slot + 1u) % adapter->max_connections;
        scanned++;
    }
    adapter->publish_continuation = runtime_world_recompute_continuation(
        adapter, lease.publication_epoch);
release:
    break_world_snapshot_lease_release(&lease);
    return result;
}

BreakRuntimeWorldSession *break_runtime_world_session_create(
    const BreakRuntimeWorldSessionConfig *config)
{
    static const BreakRuntimeBusKind kind = {
        BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, 1u, 56u,
        "world_session.control", true, 0u
    };
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeQueueConfig queue_config;
    BreakRuntimeError result;
    const char *subscriber_name;
    u32 capacity;
    u32 max_connections;
    if (!config || !config->session || !config->bus) return NULL;
    if (config->log && (config->publication || config->publish_waits_for_ack ||
                        config->publish_keep)) {
        return NULL;
    }
    if (!config->publication && !config->log &&
        (config->publish_connection_budget != 0u || config->publish_requires_ready ||
         config->publish_waits_for_ack || config->publish_keep)) {
        return NULL;
    }
    /* A per-connection user resolver without a filter is a configuration error. */
    if (!config->publish_keep && config->publish_keep_user_for) return NULL;
    if (config->publish_connection_budget > 64u) return NULL;
    capacity = config->queue_capacity == 0u
                   ? RUNTIME_WORLD_DEFAULT_QUEUE_CAPACITY
                   : config->queue_capacity;
    max_connections = config->max_connections == 0u
                          ? RUNTIME_WORLD_DEFAULT_CONNECTIONS
                          : config->max_connections;
    if (capacity > RUNTIME_WORLD_MAX_QUEUE_CAPACITY ||
        max_connections > RUNTIME_WORLD_MAX_CONNECTIONS) {
        return NULL;
    }
    subscriber_name = config->subscriber_name ? config->subscriber_name : "world_session";
    adapter = (BreakRuntimeWorldSession *)calloc(
        1u, sizeof(*adapter) + (usize)max_connections * sizeof(adapter->connections[0]));
    if (!adapter) return NULL;
    adapter->session = config->session;
    adapter->bus = config->bus;
    adapter->publication = config->publication;
    adapter->log = config->log;
    adapter->max_connections = max_connections;
    adapter->publish_connection_budget = config->publish_connection_budget == 0u
        ? 8u : config->publish_connection_budget;
    adapter->publish_requires_ready = config->publish_requires_ready;
    adapter->publish_waits_for_ack = config->publish_waits_for_ack;
    adapter->publish_keep = config->publish_keep;
    adapter->publish_keep_user_for = config->publish_keep_user_for;
    adapter->publish_keep_ctx = config->publish_keep_ctx;
    adapter->next_connection_epoch = 1u;
    adapter->next_sequence = 1u;
    platform_mutex_init(&adapter->mutex);

    result = break_runtime_bus_kind_matches(config->bus, &kind);
    if (result == BREAK_RUNTIME_STALE) {
        result = break_runtime_bus_register_kind(config->bus, &kind);
    }
    if (result != BREAK_RUNTIME_OK) {
        platform_mutex_destroy(&adapter->mutex);
        free(adapter);
        return NULL;
    }
    queue_config.capacity = capacity;
    queue_config.reserved_control = queue_config.capacity;
    result = break_runtime_queue_create(&queue_config, &adapter->queue);
    if (result == BREAK_RUNTIME_OK) {
        const u16 kinds[1] = {BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND};
        result = break_runtime_bus_subscribe(config->bus, subscriber_name, adapter->queue,
                                             kinds, 1u, &adapter->subscriber_id);
    }
    if (result != BREAK_RUNTIME_OK) {
        break_runtime_queue_destroy(adapter->queue);
        platform_mutex_destroy(&adapter->mutex);
        free(adapter);
        return NULL;
    }
    return adapter;
}

static usize runtime_world_queued_locked(const BreakRuntimeWorldSession *adapter)
{
    BreakRuntimeQueueStats stats;
    if (break_runtime_queue_stats(adapter->queue, &stats) != BREAK_RUNTIME_OK) return 0u;
    return (usize)(stats.enqueued - stats.dequeued);
}

static usize runtime_world_pending_locked(const BreakRuntimeWorldSession *adapter)
{
    return runtime_world_queued_locked(adapter) + (adapter->control_pending ? 1u : 0u) +
           (runtime_world_publish_pending_locked(adapter) ? 1u : 0u);
}

bool break_runtime_world_session_lifecycle_reserve(BreakRuntimeWorldSession *adapter)
{
    bool reserved = false;
    platform_mutex_lock(&adapter->mutex);
    if (!adapter->closed && !adapter->lifecycle_bound && !adapter->lifecycle_destroying) {
        adapter->lifecycle_bound = true;
        reserved = true;
    }
    platform_mutex_unlock(&adapter->mutex);
    return reserved;
}

bool break_runtime_world_session_lifecycle_attach(BreakRuntimeWorldSession *adapter,
                                                  void *binding)
{
    bool attached = false;
    platform_mutex_lock(&adapter->mutex);
    if (!adapter->closed && adapter->lifecycle_bound && !adapter->lifecycle_destroying &&
        adapter->lifecycle_binding == NULL && binding != NULL) {
        adapter->lifecycle_binding = binding;
        attached = true;
    }
    platform_mutex_unlock(&adapter->mutex);
    return attached;
}

void break_runtime_world_session_lifecycle_release(BreakRuntimeWorldSession *adapter,
                                                   const void *binding)
{
    platform_mutex_lock(&adapter->mutex);
    if (adapter->lifecycle_bound && !adapter->lifecycle_destroying &&
        adapter->lifecycle_binding == binding) {
        adapter->lifecycle_bound = false;
        adapter->lifecycle_binding = NULL;
    }
    platform_mutex_unlock(&adapter->mutex);
}

void *break_runtime_world_session_lifecycle_detach(
    BreakRuntimeWorldSession *adapter, BreakRuntimeCoordinator *coordinator)
{
    void *binding = NULL;
    platform_mutex_lock(&adapter->mutex);
    if (adapter->lifecycle_bound && !adapter->lifecycle_destroying &&
        adapter->lifecycle_binding != NULL &&
        break_runtime_coordinator_unregister_subsystem(
            coordinator, adapter->lifecycle_binding)) {
        binding = adapter->lifecycle_binding;
        adapter->lifecycle_bound = false;
        adapter->lifecycle_binding = NULL;
    }
    platform_mutex_unlock(&adapter->mutex);
    return binding;
}

bool break_runtime_world_session_lifecycle_begin_destroy(BreakRuntimeWorldSession *adapter)
{
    bool began = false;
    platform_mutex_lock(&adapter->mutex);
    if (adapter->lifecycle_bound && adapter->lifecycle_binding != NULL &&
        !adapter->lifecycle_destroying) {
        adapter->lifecycle_destroying = true;
        began = true;
    }
    platform_mutex_unlock(&adapter->mutex);
    return began;
}

void break_runtime_world_session_lifecycle_cancel_destroy(BreakRuntimeWorldSession *adapter)
{
    platform_mutex_lock(&adapter->mutex);
    if (adapter->lifecycle_bound) adapter->lifecycle_destroying = false;
    platform_mutex_unlock(&adapter->mutex);
}

bool break_runtime_world_session_destroy(BreakRuntimeWorldSession *adapter)
{
    BreakRuntimeError result;
    if (!adapter) return true;
    platform_mutex_lock(&adapter->mutex);
    if (adapter->lifecycle_bound && !adapter->lifecycle_destroying) {
        platform_mutex_unlock(&adapter->mutex);
        return false;
    }
    if (!adapter->closed) {
        adapter->closed = true;
        break_runtime_queue_close(adapter->queue);
    }
    if (!adapter->unsubscribed) {
        result = break_runtime_bus_unsubscribe(adapter->bus, adapter->subscriber_id);
        if (result != BREAK_RUNTIME_OK && result != BREAK_RUNTIME_STALE) {
            adapter->lifecycle_destroying = false;
            platform_mutex_unlock(&adapter->mutex);
            return false;
        }
        adapter->unsubscribed = true;
    }
    if (runtime_world_pending_locked(adapter) != 0u) {
        adapter->lifecycle_destroying = false;
        platform_mutex_unlock(&adapter->mutex);
        return false;
    }
    adapter->lifecycle_bound = false;
    adapter->lifecycle_destroying = false;
    adapter->lifecycle_binding = NULL;
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        runtime_world_drop_reader(adapter, &adapter->connections[i]);
    }
    platform_mutex_unlock(&adapter->mutex);
    break_runtime_queue_destroy(adapter->queue);
    platform_mutex_destroy(&adapter->mutex);
    free(adapter);
    return true;
}

BreakRuntimeError break_runtime_world_session_submit(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldCommand *command,
    u64 correlation_id)
{
    BreakRuntimeMessageView view;
    BreakRuntimeOwnedMessage *message = NULL;
    BreakRuntimeError result;
    u64 sequence;
    if (!adapter) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&adapter->mutex);
    if (adapter->closed) {
        platform_mutex_unlock(&adapter->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    if (!runtime_world_command_valid(command)) {
        adapter->rejected++;
        platform_mutex_unlock(&adapter->mutex);
        return BREAK_RUNTIME_INVALID;
    }
    if (adapter->next_sequence == 0u) {
        platform_mutex_unlock(&adapter->mutex);
        return BREAK_RUNTIME_OVERLOAD;
    }
    sequence = adapter->next_sequence;
    memset(&view, 0, sizeof(view));
    view.kind = BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND;
    view.version = 1u;
    view.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
    view.sequence = sequence;
    view.correlation_id = correlation_id;
    view.data = command;
    view.size = sizeof(*command);
    result = break_runtime_message_copy(&view, &message);
    if (result == BREAK_RUNTIME_OK) {
        result = break_runtime_queue_enqueue(
            adapter->queue, message, break_runtime_queue_generation(adapter->queue));
        if (result == BREAK_RUNTIME_OK) {
            adapter->submitted++;
            adapter->next_sequence++;
        } else {
            break_runtime_message_release(message);
        }
    }
    platform_mutex_unlock(&adapter->mutex);
    return result;
}

BreakRuntimeError break_runtime_world_session_submit_publish_current(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldPublishCurrentNotice *notice,
    u64 correlation_id)
{
    BreakRuntimeMessageView view;
    BreakRuntimeOwnedMessage *message = NULL;
    BreakRuntimeError result;
    u64 sequence;
    if (!adapter) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&adapter->mutex);
    if (adapter->closed) {
        platform_mutex_unlock(&adapter->mutex);
        return BREAK_RUNTIME_CLOSED;
    }
    if (!adapter->publication && !adapter->log) {
        adapter->rejected++;
        platform_mutex_unlock(&adapter->mutex);
        return BREAK_RUNTIME_REJECTED;
    }
    if (!notice || notice->reserved_zero != 0u) {
        adapter->rejected++;
        platform_mutex_unlock(&adapter->mutex);
        return BREAK_RUNTIME_INVALID;
    }
    if (adapter->next_sequence == 0u) {
        platform_mutex_unlock(&adapter->mutex);
        return BREAK_RUNTIME_OVERLOAD;
    }
    sequence = adapter->next_sequence;
    memset(&view, 0, sizeof(view));
    view.kind = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_KIND;
    view.version = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_VERSION;
    view.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
    view.sequence = sequence;
    view.correlation_id = correlation_id;
    view.data = notice;
    view.size = sizeof(*notice);
    result = break_runtime_message_copy(&view, &message);
    if (result == BREAK_RUNTIME_OK) {
        result = break_runtime_queue_enqueue(
            adapter->queue, message, break_runtime_queue_generation(adapter->queue));
        if (result == BREAK_RUNTIME_OK) {
            adapter->submitted++;
            adapter->next_sequence++;
        } else {
            break_runtime_message_release(message);
        }
    }
    platform_mutex_unlock(&adapter->mutex);
    return result;
}

BreakRuntimeError break_runtime_world_session_set_publish_ready(
    BreakRuntimeWorldSession *adapter, u64 connection_key, u64 connection_epoch,
    bool ready)
{
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    usize slot;
    if (!adapter || connection_key == 0u) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&adapter->mutex);
    if (!adapter->publish_requires_ready) {
        result = BREAK_RUNTIME_REJECTED;
    } else {
        slot = runtime_world_find_connection(adapter, connection_key);
        if (slot == adapter->max_connections ||
            adapter->connections[slot].epoch != connection_epoch) {
            result = BREAK_RUNTIME_STALE;
        } else {
            adapter->connections[slot].publish_ready = ready;
        }
    }
    platform_mutex_unlock(&adapter->mutex);
    return result;
}

void break_runtime_world_session_close(BreakRuntimeWorldSession *adapter)
{
    if (!adapter) return;
    platform_mutex_lock(&adapter->mutex);
    if (!adapter->closed) {
        adapter->closed = true;
        break_runtime_queue_close(adapter->queue);
    }
    platform_mutex_unlock(&adapter->mutex);
}

bool break_runtime_world_session_is_closed(const BreakRuntimeWorldSession *adapter)
{
    bool closed;
    if (!adapter) return true;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    closed = adapter->closed;
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    return closed;
}

BreakRuntimeError break_runtime_world_session_drain(
    BreakRuntimeWorldSession *adapter, usize max_messages,
    usize *out_drained)
{
    BreakRuntimeError first_error = BREAK_RUNTIME_OK;
    usize drained = 0u;
    if (out_drained) *out_drained = 0u;
    if (!adapter) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&adapter->mutex);
    if (max_messages == 0u) {
        platform_mutex_unlock(&adapter->mutex);
        return BREAK_RUNTIME_OK;
    }
    if (adapter->control_pending) {
        first_error = runtime_world_retry(adapter);
        if (first_error != BREAK_RUNTIME_OK) goto done;
    }
    while (drained < max_messages) {
        BreakRuntimeOwnedMessage *message = NULL;
        BreakRuntimeMessageView view;
        BreakRuntimeWorldCommand command;
        BreakRuntimeWorldPublishCurrentNotice notice;
        BreakRuntimeError result;
        u64 correlation_id = 0u;
        bool is_notice = false;
        result = break_runtime_queue_poll(adapter->queue, &message);
        if (result != BREAK_RUNTIME_OK || !message) break;
        memset(&command, 0, sizeof(command));
        memset(&notice, 0, sizeof(notice));
        result = break_runtime_message_view(message, &view);
        if (result == BREAK_RUNTIME_OK &&
            view.kind == BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_KIND &&
            view.version == BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_VERSION &&
            view.size == sizeof(notice)) {
            memcpy(&notice, view.data, sizeof(notice));
            is_notice = true;
        } else if (result == BREAK_RUNTIME_OK &&
                   view.kind == BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND &&
                   view.version == 1u && view.size == sizeof(command)) {
            memcpy(&command, view.data, sizeof(command));
            correlation_id = view.correlation_id;
        } else {
            result = BREAK_RUNTIME_INVALID;
        }
        break_runtime_message_release(message);
        adapter->drained++;
        drained++;
        if (result == BREAK_RUNTIME_OK) {
            result = is_notice
                         ? runtime_world_apply_notice(adapter, &notice)
                         : runtime_world_apply(adapter, &command, correlation_id);
        }
        runtime_world_record_result(adapter, result,
                                    !is_notice &&
                                    (command.kind == BREAK_RUNTIME_WORLD_COMMAND_ACK ||
                                     command.kind == BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL));
        if (first_error == BREAK_RUNTIME_OK && result != BREAK_RUNTIME_OK) first_error = result;
        if (result == BREAK_RUNTIME_OVERLOAD && !is_notice &&
            (command.kind == BREAK_RUNTIME_WORLD_COMMAND_ACK ||
             command.kind == BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL)) {
            adapter->control_pending = true;
            adapter->pending_command = command;
            adapter->pending_correlation_id = correlation_id;
            break;
        }
    }
    if (runtime_world_publish_pending_locked(adapter)) {
        BreakRuntimeError result = runtime_world_publish_current(adapter);
        if (first_error == BREAK_RUNTIME_OK && result != BREAK_RUNTIME_OK) first_error = result;
    }
done:
    if (out_drained) *out_drained = drained;
    platform_mutex_unlock(&adapter->mutex);
    return first_error;
}

usize break_runtime_world_session_pending(const BreakRuntimeWorldSession *adapter)
{
    usize pending;
    if (!adapter) return 0u;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    pending = runtime_world_pending_locked(adapter);
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    return pending;
}

bool break_runtime_world_session_connection_epoch(
    const BreakRuntimeWorldSession *adapter, u64 connection_key,
    u64 *out_epoch)
{
    usize slot;
    bool found;
    if (out_epoch) *out_epoch = 0u;
    if (!adapter || !out_epoch || connection_key == 0u) return false;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    slot = runtime_world_find_connection(adapter, connection_key);
    found = slot != adapter->max_connections;
    if (found) *out_epoch = adapter->connections[slot].epoch;
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    return found;
}

/* Single source of truth for a connection's adapter-owned dirty state; the
 * per-connection snapshot and the adapter-level summary both call it so the two views
 * cannot drift. It deliberately omits Session attempt_pending (see the header note). */
static bool runtime_world_connection_dirty_locked(
    const BreakRuntimeWorldSession *adapter, const RuntimeWorldConnection *connection)
{
    if (!connection->publish_ready) return false;
    return connection->retry_publish ||
           connection->attempt_publication_epoch != 0u ||
           connection->attempt_target_snapshot_id != 0u ||
           connection->attempt_target_tick != 0u ||
           (adapter->publish_observed_epoch != 0u &&
            connection->completed_publication_epoch != adapter->publish_observed_epoch &&
            connection->terminal_publication_epoch != adapter->publish_observed_epoch &&
            connection->held_publication_epoch != adapter->publish_observed_epoch);
}

usize break_runtime_world_session_connection_snapshots(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldConnectionSnapshot *out_snapshots,
    usize capacity)
{
    usize opened = 0u;
    if (!adapter) return 0u;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        const RuntimeWorldConnection *connection = &adapter->connections[i];
        BreakRuntimeWorldConnectionSnapshot snapshot;
        if (connection->key == 0u) continue;
        memset(&snapshot, 0, sizeof(snapshot));
        snapshot.connection_key = connection->key;
        snapshot.connection_epoch = connection->epoch;
        snapshot.completed_publication_epoch = connection->completed_publication_epoch;
        snapshot.terminal_publication_epoch = connection->terminal_publication_epoch;
        snapshot.attempt_publication_epoch = connection->attempt_publication_epoch;
        snapshot.attempt_target_snapshot_id = connection->attempt_target_snapshot_id;
        snapshot.attempt_target_tick = connection->attempt_target_tick;
        snapshot.retry_publish = connection->retry_publish;
        snapshot.publish_dirty = runtime_world_connection_dirty_locked(adapter, connection);
        snapshot.publish_ready = connection->publish_ready;
        snapshot.held_publication_epoch = connection->held_publication_epoch;
        if (out_snapshots && opened < capacity) out_snapshots[opened] = snapshot;
        ++opened;
    }
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    return opened;
}

bool break_runtime_world_session_publish_progress(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldPublishProgress *out_progress)
{
    if (!out_progress) return false;
    memset(out_progress, 0, sizeof(*out_progress));
    if (!adapter) return false;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    out_progress->observed_publication_epoch = adapter->publish_observed_epoch;
    out_progress->request_pending = adapter->publish_request;
    out_progress->continuation_pending = adapter->publish_continuation;
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        const RuntimeWorldConnection *connection = &adapter->connections[i];
        bool dirty;
        if (connection->key == 0u) continue;
        ++out_progress->open_connections;
        dirty = runtime_world_connection_dirty_locked(adapter, connection);
        if (dirty) ++out_progress->dirty_connections;
    }
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    return true;
}

void break_runtime_world_session_stats(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldSessionStats *out_stats)
{
    if (!out_stats) return;
    memset(out_stats, 0, sizeof(*out_stats));
    if (!adapter) return;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    out_stats->submitted = adapter->submitted;
    out_stats->drained = adapter->drained;
    out_stats->applied = adapter->applied;
    out_stats->rejected = adapter->rejected;
    out_stats->stale_rejected = adapter->stale_rejected;
    out_stats->transport_overloads = adapter->transport_overloads;
    out_stats->next_sequence = adapter->next_sequence;
    out_stats->queued = runtime_world_queued_locked(adapter);
    out_stats->control_pending = adapter->control_pending;
    out_stats->publish_overloads = adapter->publish_overloads;
    out_stats->publish_terminal = adapter->publish_terminal;
    out_stats->publish_pending = runtime_world_publish_pending_locked(adapter);
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
}

BreakRuntimeError break_runtime_world_session_export_metrics(
    const BreakRuntimeWorldSession *adapter,
    struct BreakRuntimeMetrics *metrics,
    const char *prefix)
{
    BreakRuntimeWorldSessionStats stats;
    struct {
        const char *suffix;
        u64 value;
    } gauges[11];
    char name[128];
    u32 i;
    if (!adapter || !metrics || !prefix || prefix[0] == '\0') {
        return BREAK_RUNTIME_INVALID;
    }
    break_runtime_world_session_stats(adapter, &stats);
    gauges[0].suffix = "submitted";           gauges[0].value = stats.submitted;
    gauges[1].suffix = "drained";             gauges[1].value = stats.drained;
    gauges[2].suffix = "applied";             gauges[2].value = stats.applied;
    gauges[3].suffix = "rejected";            gauges[3].value = stats.rejected;
    gauges[4].suffix = "stale_rejected";      gauges[4].value = stats.stale_rejected;
    gauges[5].suffix = "transport_overloads"; gauges[5].value = stats.transport_overloads;
    gauges[6].suffix = "queued";              gauges[6].value = (u64)stats.queued;
    gauges[7].suffix = "publish_overloads";   gauges[7].value = stats.publish_overloads;
    gauges[8].suffix = "publish_terminal";    gauges[8].value = stats.publish_terminal;
    gauges[9].suffix = "control_pending";     gauges[9].value = stats.control_pending ? 1u : 0u;
    gauges[10].suffix = "publish_pending";    gauges[10].value = stats.publish_pending ? 1u : 0u;
    for (i = 0; i < 11u; i++) {
        BreakRuntimeError result;
        int n = snprintf(name, sizeof(name), "%s.%s", prefix, gauges[i].suffix);
        if (n < 0) {
            return BREAK_RUNTIME_FAILED;
        }
        /* The registry rejects an over-long name with INVALID; let that be the
         * reported error rather than silently truncating here. */
        result = break_runtime_metrics_set(metrics, name, BREAK_RUNTIME_METRIC_GAUGE,
                                           gauges[i].value);
        if (result != BREAK_RUNTIME_OK) {
            return result;
        }
    }
    return BREAK_RUNTIME_OK;
}

#ifdef BREAK_RUNTIME_TESTING
void break_runtime_world_session_set_next_connection_epoch_for_test(
    BreakRuntimeWorldSession *adapter, u64 next_epoch)
{
    if (!adapter) return;
    platform_mutex_lock(&adapter->mutex);
    adapter->next_connection_epoch = next_epoch;
    platform_mutex_unlock(&adapter->mutex);
}
#endif
