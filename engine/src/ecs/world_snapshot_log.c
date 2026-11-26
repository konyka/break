#include <ecs/world_snapshot_log.h>

#include <core/platform_thread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    bool used;
    bool lagged;
    u64 next; /* next epoch to read */
} Reader;

/* Epochs are consecutive, so the retained ones are
 * [next_epoch - retained, next_epoch) and epoch e lives in ring[e % capacity]. */
struct BreakWorldSnapshotLog {
    BreakWorldSnapshotLogConfig config;
    PlatformMutex mutex;
    BreakWorldSnapshot **ring;
    Reader *readers;
    u64 next_epoch;
    u64 last_tick;
    u32 retained;
    BreakWorldSnapshotLogStats stats;
};

static u64 oldest_epoch(const BreakWorldSnapshotLog *log) {
    return log->next_epoch - log->retained;
}

static Reader *find_reader(BreakWorldSnapshotLog *log, BreakWorldSnapshotReaderId reader) {
    if (reader >= log->config.max_readers || !log->readers[reader].used) return NULL;
    return &log->readers[reader];
}

BreakWorldSnapshotLog *break_world_snapshot_log_create(const BreakWorldSnapshotLogConfig *config) {
    BreakWorldSnapshotLog *log;
    if (!config || config->capacity == 0u ||
        config->capacity > BREAK_WORLD_SNAPSHOT_LOG_MAX_CAPACITY || config->max_readers == 0u ||
        config->max_readers > BREAK_WORLD_SNAPSHOT_LOG_MAX_READERS) {
        return NULL;
    }
    log = (BreakWorldSnapshotLog *)calloc(1u, sizeof(*log));
    if (!log) return NULL;
    log->ring = (BreakWorldSnapshot **)calloc(config->capacity, sizeof(*log->ring));
    log->readers = (Reader *)calloc(config->max_readers, sizeof(*log->readers));
    if (!log->ring || !log->readers) {
        free(log->ring);
        free(log->readers);
        free(log);
        return NULL;
    }
    log->config = *config;
    log->next_epoch = 1u;
    platform_mutex_init(&log->mutex);
    return log;
}

void break_world_snapshot_log_destroy(BreakWorldSnapshotLog *log) {
    if (!log) return;
    for (u32 i = 0u; i < log->config.capacity; ++i) {
        if (log->ring[i]) break_world_snapshot_release(log->ring[i]);
    }
    platform_mutex_destroy(&log->mutex);
    free(log->ring);
    free(log->readers);
    free(log);
}

/* Frees the oldest slot for a publish. Returns false (FULL) when a reader
 * still needs it and slow readers are not evicted. */
static bool make_room(BreakWorldSnapshotLog *log) {
    u64 oldest;
    u32 slot;
    if (log->retained < log->config.capacity) return true;
    oldest = oldest_epoch(log);
    /* without eviction no reader is ever lagged, so `next` is always current */
    for (u32 i = 0u; i < log->config.max_readers && !log->config.evict_slow_readers; ++i) {
        const Reader *r = &log->readers[i];
        if (r->used && r->next <= oldest) return false;
    }
    for (u32 i = 0u; i < log->config.max_readers; ++i) {
        Reader *r = &log->readers[i];
        if (r->used && !r->lagged && r->next <= oldest) {
            r->lagged = true;
            log->stats.evicted_readers++;
        }
    }
    slot = (u32)(oldest % log->config.capacity);
    break_world_snapshot_release(log->ring[slot]);
    log->ring[slot] = NULL;
    log->retained--;
    return true;
}

BreakWorldSnapshotLogResult break_world_snapshot_log_publish(BreakWorldSnapshotLog *log,
                                                             BreakWorldSnapshot *snapshot,
                                                             u64 *out_epoch) {
    BreakWorldSnapshotLogResult result = BREAK_WORLD_SNAPSHOT_LOG_OK;
    u64 tick;
    if (!log || !snapshot) return BREAK_WORLD_SNAPSHOT_LOG_INVALID;
    tick = break_world_snapshot_tick(snapshot);
    if (break_world_snapshot_schema_hash(snapshot) != log->config.schema_hash)
        return BREAK_WORLD_SNAPSHOT_LOG_INVALID;
    platform_mutex_lock(&log->mutex);
    /* last_tick starts at 0, so this also refuses tick 0 */
    if (tick <= log->last_tick || log->next_epoch == UINT64_MAX) {
        result = BREAK_WORLD_SNAPSHOT_LOG_INVALID;
    } else if (!make_room(log)) {
        log->stats.refused_full++;
        result = BREAK_WORLD_SNAPSHOT_LOG_FULL;
    } else {
        break_world_snapshot_retain(snapshot);
        log->ring[log->next_epoch % log->config.capacity] = snapshot;
        log->retained++;
        log->last_tick = tick;
        if (out_epoch) *out_epoch = log->next_epoch;
        log->next_epoch++;
        log->stats.published++;
    }
    platform_mutex_unlock(&log->mutex);
    return result;
}

bool break_world_snapshot_log_add_reader(BreakWorldSnapshotLog *log,
                                         BreakWorldSnapshotReaderId *out_reader) {
    bool added = false;
    if (!log || !out_reader) return false;
    platform_mutex_lock(&log->mutex);
    for (u32 i = 0u; i < log->config.max_readers; ++i) {
        Reader *r = &log->readers[i];
        if (r->used) continue;
        r->used = true; /* free slots are zeroed: lagged is false */
        r->next = log->next_epoch;
        *out_reader = i;
        added = true;
        break;
    }
    platform_mutex_unlock(&log->mutex);
    return added;
}

bool break_world_snapshot_log_remove_reader(BreakWorldSnapshotLog *log,
                                            BreakWorldSnapshotReaderId reader) {
    Reader *r;
    if (!log) return false;
    platform_mutex_lock(&log->mutex);
    r = find_reader(log, reader);
    if (r) memset(r, 0, sizeof(*r));
    platform_mutex_unlock(&log->mutex);
    return r != NULL;
}

BreakWorldSnapshotLogResult break_world_snapshot_log_read(BreakWorldSnapshotLog *log,
                                                          BreakWorldSnapshotReaderId reader,
                                                          BreakWorldSnapshotLogLease *out_lease) {
    BreakWorldSnapshotLogResult result = BREAK_WORLD_SNAPSHOT_LOG_OK;
    Reader *r;
    if (out_lease) memset(out_lease, 0, sizeof(*out_lease));
    if (!log || !out_lease) return BREAK_WORLD_SNAPSHOT_LOG_INVALID;
    platform_mutex_lock(&log->mutex);
    r = find_reader(log, reader);
    if (!r) {
        result = BREAK_WORLD_SNAPSHOT_LOG_INVALID;
    } else if (r->lagged) {
        r->lagged = false;
        r->next = oldest_epoch(log);
        result = BREAK_WORLD_SNAPSHOT_LOG_LAGGED;
    } else if (r->next == log->next_epoch) {
        result = BREAK_WORLD_SNAPSHOT_LOG_EMPTY;
    } else {
        BreakWorldSnapshot *snapshot = log->ring[r->next % log->config.capacity];
        break_world_snapshot_retain(snapshot);
        out_lease->snapshot = snapshot;
        out_lease->epoch = r->next;
        r->next++;
        log->stats.delivered++;
    }
    platform_mutex_unlock(&log->mutex);
    return result;
}

u64 break_world_snapshot_log_backlog(BreakWorldSnapshotLog *log,
                                     BreakWorldSnapshotReaderId reader) {
    u64 backlog = 0u;
    const Reader *r;
    if (!log) return 0u;
    platform_mutex_lock(&log->mutex);
    r = find_reader(log, reader);
    if (r) backlog = log->next_epoch - (r->lagged ? oldest_epoch(log) : r->next);
    platform_mutex_unlock(&log->mutex);
    return backlog;
}

void break_world_snapshot_log_lease_release(BreakWorldSnapshotLogLease *lease) {
    if (!lease) return;
    if (lease->snapshot) break_world_snapshot_release(lease->snapshot);
    lease->snapshot = NULL;
    lease->epoch = 0u;
}

void break_world_snapshot_log_stats(BreakWorldSnapshotLog *log, BreakWorldSnapshotLogStats *out) {
    if (!log || !out) return;
    platform_mutex_lock(&log->mutex);
    *out = log->stats;
    out->retained = log->retained;
    out->readers = 0u;
    for (u32 i = 0u; i < log->config.max_readers; ++i) {
        if (log->readers[i].used) out->readers++;
    }
    platform_mutex_unlock(&log->mutex);
}
