#include <ecs/world_snapshot_publication.h>

#include <core/platform_thread.h>
#include <stdint.h>
#include <stdlib.h>

struct BreakWorldSnapshotPublication {
    BreakWorldSnapshotPublicationConfig config;
    PlatformMutex mutex;
    BreakWorldSnapshot *current;
    u64 current_level;
    u64 current_tick;
    u64 publication_epoch;
    bool closed;
};

BreakWorldSnapshotPublication *break_world_snapshot_publication_create(
    const BreakWorldSnapshotPublicationConfig *config) {
    if (!config) return NULL;
    BreakWorldSnapshotPublication *publication = calloc(1u, sizeof(*publication));
    if (!publication) return NULL;
    publication->config = *config;
    publication->current_level = config->level_generation;
    platform_mutex_init(&publication->mutex);
    return publication;
}

void break_world_snapshot_publication_destroy(
    BreakWorldSnapshotPublication *publication) {
    if (!publication) return;
    break_world_snapshot_publication_close(publication);
    platform_mutex_destroy(&publication->mutex);
    free(publication);
}

bool break_world_snapshot_publication_publish(
    BreakWorldSnapshotPublication *publication,
    BreakWorldSnapshot *snapshot, u64 level_generation) {
    if (!publication || !snapshot) return false;
    u64 tick = break_world_snapshot_tick(snapshot);
    if (tick == 0u ||
        break_world_snapshot_schema_hash(snapshot) != publication->config.schema_hash) {
        return false;
    }

    BreakWorldSnapshot *old = NULL;
    platform_mutex_lock(&publication->mutex);
    if (publication->closed || publication->publication_epoch == UINT64_MAX ||
        level_generation < publication->current_level ||
        (publication->current && level_generation == publication->current_level &&
         tick <= publication->current_tick)) {
        platform_mutex_unlock(&publication->mutex);
        return false;
    }

    break_world_snapshot_retain(snapshot);
    old = publication->current;
    publication->current = snapshot;
    publication->current_level = level_generation;
    publication->current_tick = tick;
    publication->publication_epoch++;
    platform_mutex_unlock(&publication->mutex);
    break_world_snapshot_release(old);
    return true;
}

BreakWorldSnapshotAcquireResult break_world_snapshot_publication_acquire(
    BreakWorldSnapshotPublication *publication,
    BreakWorldSnapshotLease *out_lease) {
    if (!publication || !out_lease) return BREAK_WORLD_SNAPSHOT_ACQUIRE_INVALID;

    platform_mutex_lock(&publication->mutex);
    if (publication->closed) {
        platform_mutex_unlock(&publication->mutex);
        return BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED;
    }
    if (!publication->current) {
        platform_mutex_unlock(&publication->mutex);
        return BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY;
    }

    break_world_snapshot_retain(publication->current);
    out_lease->snapshot = publication->current;
    out_lease->level_generation = publication->current_level;
    out_lease->publication_epoch = publication->publication_epoch;
    platform_mutex_unlock(&publication->mutex);
    return BREAK_WORLD_SNAPSHOT_ACQUIRE_OK;
}

void break_world_snapshot_publication_close(
    BreakWorldSnapshotPublication *publication) {
    if (!publication) return;
    platform_mutex_lock(&publication->mutex);
    BreakWorldSnapshot *old = publication->current;
    publication->current = NULL;
    publication->closed = true;
    platform_mutex_unlock(&publication->mutex);
    break_world_snapshot_release(old);
}

void break_world_snapshot_lease_release(BreakWorldSnapshotLease *lease) {
    if (!lease) return;
    break_world_snapshot_release(lease->snapshot);
    lease->snapshot = NULL;
    lease->level_generation = 0u;
    lease->publication_epoch = 0u;
}
