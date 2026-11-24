#include <runtime/runtime_world_session.h>

#include <core/platform_thread.h>

#include <stdlib.h>
#include <string.h>

#define RUNTIME_WORLD_DEFAULT_QUEUE_CAPACITY 64u
#define RUNTIME_WORLD_MAX_QUEUE_CAPACITY 256u
#define RUNTIME_WORLD_DEFAULT_CONNECTIONS 8u
#define RUNTIME_WORLD_MAX_CONNECTIONS 64u

typedef struct {
    u64 key;
    u64 epoch;
} RuntimeWorldConnection;

struct BreakRuntimeWorldSession {
    BreakWorldSession *session;
    BreakRuntimeBus *bus;
    BreakRuntimeQueue *queue;
    PlatformMutex mutex;
    u32 subscriber_id;
    u32 max_connections;
    bool closed;
    u64 next_connection_epoch;
    u64 next_sequence;
    u64 submitted;
    u64 drained;
    u64 applied;
    u64 rejected;
    u64 stale_rejected;
    u64 transport_overloads;
    bool control_pending;
    BreakRuntimeWorldCommand pending_command;
    u64 pending_correlation_id;
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
        return break_world_session_rebaseline(adapter->session, command->level_generation)
                   ? BREAK_RUNTIME_OK
                   : BREAK_RUNTIME_STALE;
    }
    if (command->kind == BREAK_RUNTIME_WORLD_COMMAND_OPEN) {
        u64 epoch;
        if (runtime_world_find_connection(adapter, command->connection_key) !=
            adapter->max_connections) {
            return BREAK_RUNTIME_REJECTED;
        }
        if (command->level_generation != level) return BREAK_RUNTIME_STALE;
        for (slot = 0u; slot < adapter->max_connections; ++slot) {
            if (adapter->connections[slot].key == 0u) break;
        }
        if (slot == adapter->max_connections) return BREAK_RUNTIME_REJECTED;
        if (adapter->next_connection_epoch == 0u) return BREAK_RUNTIME_OVERLOAD;
        epoch = adapter->next_connection_epoch;
        if (!break_world_session_open(adapter->session, command->connection_key)) {
            return BREAK_RUNTIME_REJECTED;
        }
        adapter->connections[slot].key = command->connection_key;
        adapter->connections[slot].epoch = epoch;
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
        memset(&adapter->connections[slot], 0, sizeof(adapter->connections[slot]));
        return BREAK_RUNTIME_OK;
    }
    return runtime_world_send_control(adapter, command, correlation_id);
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
    adapter->max_connections = max_connections;
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

bool break_runtime_world_session_destroy(BreakRuntimeWorldSession *adapter)
{
    BreakRuntimeError result;
    if (!adapter) return true;
    platform_mutex_lock(&adapter->mutex);
    if (adapter->submitted != adapter->drained || adapter->control_pending) {
        platform_mutex_unlock(&adapter->mutex);
        return false;
    }
    result = break_runtime_bus_unsubscribe(adapter->bus, adapter->subscriber_id);
    if (result != BREAK_RUNTIME_OK) {
        platform_mutex_unlock(&adapter->mutex);
        return false;
    }
    adapter->closed = true;
    break_runtime_queue_close(adapter->queue);
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
    BreakRuntimeQueueStats before;
    BreakRuntimeQueueStats after;
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
    memset(&before, 0, sizeof(before));
    memset(&after, 0, sizeof(after));
    (void)break_runtime_queue_stats(adapter->queue, &before);
    result = break_runtime_bus_publish(adapter->bus, &view, NULL);
    (void)break_runtime_queue_stats(adapter->queue, &after);
    if (after.enqueued == before.enqueued + 1u) {
        adapter->submitted++;
        adapter->next_sequence++;
        result = BREAK_RUNTIME_OK;
    } else if (result == BREAK_RUNTIME_OK) {
        result = BREAK_RUNTIME_OVERLOAD;
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
        BreakRuntimeError result;
        u64 correlation_id = 0u;
        result = break_runtime_queue_poll(adapter->queue, &message);
        if (result != BREAK_RUNTIME_OK || !message) break;
        memset(&command, 0, sizeof(command));
        result = break_runtime_message_view(message, &view);
        if (result == BREAK_RUNTIME_OK && view.kind == BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND &&
            view.version == 1u && view.size == sizeof(command)) {
            memcpy(&command, view.data, sizeof(command));
            correlation_id = view.correlation_id;
        } else {
            result = BREAK_RUNTIME_INVALID;
        }
        break_runtime_message_release(message);
        adapter->drained++;
        drained++;
        if (result == BREAK_RUNTIME_OK) result = runtime_world_apply(adapter, &command, correlation_id);
        runtime_world_record_result(adapter, result,
                                    command.kind == BREAK_RUNTIME_WORLD_COMMAND_ACK ||
                                    command.kind == BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL);
        if (first_error == BREAK_RUNTIME_OK && result != BREAK_RUNTIME_OK) first_error = result;
        if (result == BREAK_RUNTIME_OVERLOAD &&
            (command.kind == BREAK_RUNTIME_WORLD_COMMAND_ACK ||
             command.kind == BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL)) {
            adapter->control_pending = true;
            adapter->pending_command = command;
            adapter->pending_correlation_id = correlation_id;
            break;
        }
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
    pending = (usize)(adapter->submitted - adapter->drained) +
              (adapter->control_pending ? 1u : 0u);
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
    out_stats->queued = (usize)(adapter->submitted - adapter->drained);
    out_stats->control_pending = adapter->control_pending;
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
}
