#include "re_internal.h"
#include <string.h>
#include <stdint.h>

/* Cross-stream joins (sub-project C Task C4): the local analog of upstream
 * StreamJoinNode (rust-rule-engine v1.21.4 f80a541 src/rete/stream_join_node.rs).
 * Matched pairs are queued exactly once at record time (upstream
 * process_left/process_right, :104/:140); unmatched outer-join sides are
 * queued exactly once when the watermark passes them (upstream
 * update_watermark, :204). Both exactly-once guarantees hold absent
 * allocation failure: a transient OOM mid-record/mid-update may leave
 * partial state (structurally safe, but an unmatched event could re-emit
 * on the next update). The public header documents every composition
 * decision and divergence. */

static size_t join_per_key_cap(const re_stream_join_t *join) {
    if (join->strategy.kind == RE_STREAM_JOIN_COUNT_WINDOW &&
        join->strategy.count < (uint64_t)RE_STREAM_JOIN_PER_KEY_CAP)
        return (size_t)join->strategy.count;
    return RE_STREAM_JOIN_PER_KEY_CAP;
}

/* upstream is_within_window (:221): COUNT_WINDOW matches every same-key
 * pair (:231); TIME_WINDOW/SESSION_WINDOW bound the absolute distance
 * (uniformly milliseconds locally - upstream compares whole seconds). */
static int join_within_window(const re_stream_join_t *join, uint64_t left_ts,
                              uint64_t right_ts) {
    uint64_t diff = left_ts > right_ts ? left_ts - right_ts : right_ts - left_ts;
    if (join->strategy.kind == RE_STREAM_JOIN_COUNT_WINDOW) return 1;
    if (join->strategy.kind == RE_STREAM_JOIN_TIME_WINDOW)
        return diff <= join->strategy.duration_ms;
    return diff <= join->strategy.gap_ms;
}

/* upstream get_window_duration (:259): COUNT_WINDOW never times out. */
static uint64_t join_window_size(const re_stream_join_t *join) {
    if (join->strategy.kind == RE_STREAM_JOIN_TIME_WINDOW) return join->strategy.duration_ms;
    if (join->strategy.kind == RE_STREAM_JOIN_SESSION_WINDOW) return join->strategy.gap_ms;
    return UINT64_MAX;
}

/* Expired once the watermark has passed the event by more than the window
 * (strictly greater, upstream :267). */
static int join_event_expired(uint64_t watermark_ms, uint64_t timestamp_ms,
                              uint64_t window_size) {
    return watermark_ms > timestamp_ms && watermark_ms - timestamp_ms > window_size;
}

static re_stream_join_key_entry_t *join_key_find(const re_stream_join_t *join, size_t side,
                                                 re_string_t key) {
    size_t index;
    for (index = 0u; index < join->key_count[side]; ++index) {
        re_stream_join_key_entry_t *entry = &join->keys[side][index];
        if (entry->key_size == key.size && memcmp(entry->key, key.data, key.size) == 0)
            return entry;
    }
    return NULL;
}

static re_status_t join_key_create(re_stream_join_t *join, size_t side, re_string_t key,
                                   re_stream_join_key_entry_t **out_entry) {
    re_stream_join_key_entry_t *entry;
    if (join->key_count[side] == (size_t)RE_STREAM_JOIN_MAX_KEYS) return RE_STATUS_LIMIT;
    if (join->key_count[side] == join->key_capacity[side]) {
        size_t capacity = join->key_capacity[side] == 0u ? 8u : join->key_capacity[side] * 2u;
        re_stream_join_key_entry_t *keys;
        if (capacity > (size_t)RE_STREAM_JOIN_MAX_KEYS) capacity = (size_t)RE_STREAM_JOIN_MAX_KEYS;
        keys = re_realloc(&join->allocator, join->keys[side], capacity * sizeof(*keys));
        if (keys == NULL) return RE_STATUS_OUT_OF_MEMORY;
        join->keys[side] = keys;
        join->key_capacity[side] = capacity;
    }
    entry = &join->keys[side][join->key_count[side]];
    memset(entry, 0, sizeof(*entry));
    entry->key = re_alloc(&join->allocator, key.size + 1u);
    if (entry->key == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(entry->key, key.data, key.size);
    entry->key[key.size] = '\0';
    entry->key_size = key.size;
    ++join->key_count[side];
    *out_entry = entry;
    return RE_STATUS_OK;
}

/* Queues one match. The key borrow targets the key entry's owned string,
 * which lives until re_stream_join_destroy (key entries are never evicted),
 * so the borrow outlives any drain. join_timestamp is the later timestamp
 * (upstream :35); the absent side of an unmatched emission carries 0, which
 * makes the max reduce to the present side's own timestamp. */
static re_status_t join_queue_match(re_stream_join_t *join,
                                    const re_stream_join_key_entry_t *key_entry,
                                    uint64_t left_ts, uint64_t right_ts) {
    re_stream_join_match_entry_t *entry;
    if (join->match_count == (size_t)RE_STREAM_JOIN_MATCH_CAP) {
        memmove(join->matches, join->matches + 1u,
                (join->match_count - 1u) * sizeof(*join->matches));
        --join->match_count;
        ++join->dropped;
    }
    if (join->match_count == join->match_capacity) {
        size_t capacity = join->match_capacity == 0u ? 16u : join->match_capacity * 2u;
        re_stream_join_match_entry_t *matches;
        if (capacity > (size_t)RE_STREAM_JOIN_MATCH_CAP) capacity = (size_t)RE_STREAM_JOIN_MATCH_CAP;
        matches = re_realloc(&join->allocator, join->matches, capacity * sizeof(*matches));
        if (matches == NULL) return RE_STATUS_OUT_OF_MEMORY;
        join->matches = matches;
        join->match_capacity = capacity;
    }
    entry = &join->matches[join->match_count++];
    entry->key = key_entry->key;
    entry->key_size = key_entry->key_size;
    entry->left_timestamp_ms = left_ts;
    entry->right_timestamp_ms = right_ts;
    entry->join_timestamp_ms = left_ts > right_ts ? left_ts : right_ts;
    return RE_STATUS_OK;
}

re_status_t re_stream_join_create(re_engine_t *engine,
                                  re_string_t left_name, re_string_t right_name,
                                  re_stream_join_type_t join_type,
                                  re_stream_join_strategy_t strategy,
                                  re_stream_join_t **out_join) {
    re_stream_join_t *join;
    if (engine == NULL || out_join == NULL || left_name.data == NULL || left_name.size == 0u ||
        right_name.data == NULL || right_name.size == 0u ||
        join_type < RE_STREAM_JOIN_INNER || join_type > RE_STREAM_JOIN_FULL_OUTER ||
        (strategy.kind != RE_STREAM_JOIN_TIME_WINDOW && strategy.kind != RE_STREAM_JOIN_COUNT_WINDOW &&
         strategy.kind != RE_STREAM_JOIN_SESSION_WINDOW) ||
        (strategy.kind == RE_STREAM_JOIN_TIME_WINDOW && strategy.duration_ms == 0u) ||
        (strategy.kind == RE_STREAM_JOIN_COUNT_WINDOW && strategy.count == 0u) ||
        (strategy.kind == RE_STREAM_JOIN_SESSION_WINDOW && strategy.gap_ms == 0u))
        return RE_STATUS_INVALID_ARGUMENT;
    *out_join = NULL;
    join = re_alloc(&engine->allocator, sizeof(*join));
    if (join == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(join, 0, sizeof(*join));
    join->allocator = engine->allocator;
    join->join_type = join_type;
    join->strategy = strategy;
    join->left_name = re_alloc(&engine->allocator, left_name.size + 1u);
    join->right_name = re_alloc(&engine->allocator, right_name.size + 1u);
    if (join->left_name == NULL || join->right_name == NULL) {
        re_free(&join->allocator, join->left_name);
        re_free(&join->allocator, join->right_name);
        re_free(&join->allocator, join);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    memcpy(join->left_name, left_name.data, left_name.size);
    join->left_name[left_name.size] = '\0';
    join->left_name_size = left_name.size;
    memcpy(join->right_name, right_name.data, right_name.size);
    join->right_name[right_name.size] = '\0';
    join->right_name_size = right_name.size;
    *out_join = join;
    return RE_STATUS_OK;
}

void re_stream_join_destroy(re_stream_join_t *join) {
    size_t side;
    if (join == NULL) return;
    for (side = 0u; side < 2u; ++side) {
        size_t index;
        for (index = 0u; index < join->key_count[side]; ++index) {
            re_free(&join->allocator, join->keys[side][index].key);
            re_free(&join->allocator, join->keys[side][index].events);
        }
        re_free(&join->allocator, join->keys[side]);
    }
    re_free(&join->allocator, join->matches);
    re_free(&join->allocator, join->left_name);
    re_free(&join->allocator, join->right_name);
    re_free(&join->allocator, join);
}

re_status_t re_stream_join_record(re_stream_join_t *join,
                                  re_stream_join_side_t side,
                                  re_string_t key, uint64_t timestamp_ms,
                                  const re_value_t *value) {
    size_t own;
    size_t opposite;
    size_t index;
    re_status_t status;
    re_stream_join_key_entry_t *own_key;
    re_stream_join_key_entry_t *other_key;
    re_stream_join_event_t *event;
    if (join == NULL || value == NULL || key.data == NULL || key.size == 0u ||
        (side != RE_STREAM_JOIN_LEFT && side != RE_STREAM_JOIN_RIGHT))
        return RE_STATUS_INVALID_ARGUMENT;
    (void)value; /* payload not retained (documented on the declaration). */
    own = side == RE_STREAM_JOIN_LEFT ? 0u : 1u;
    opposite = 1u - own;
    own_key = join_key_find(join, own, key);
    if (own_key == NULL) {
        status = join_key_create(join, own, key, &own_key);
        if (status != RE_STATUS_OK) return status;
    }
    /* Per-key bound: overflow drops the OLDEST buffered event (drop-oldest +
     * counter), the codebase's bounded-everything rule. */
    if (own_key->count == join_per_key_cap(join)) {
        memmove(own_key->events, own_key->events + 1u,
                (own_key->count - 1u) * sizeof(*own_key->events));
        --own_key->count;
        ++join->dropped;
    }
    if (own_key->count == own_key->capacity) {
        size_t capacity = own_key->capacity == 0u ? 8u : own_key->capacity * 2u;
        re_stream_join_event_t *events;
        if (capacity > join_per_key_cap(join)) capacity = join_per_key_cap(join);
        events = re_realloc(&join->allocator, own_key->events, capacity * sizeof(*events));
        if (events == NULL) return RE_STATUS_OUT_OF_MEMORY;
        own_key->events = events;
        own_key->capacity = capacity;
    }
    event = &own_key->events[own_key->count++];
    event->timestamp_ms = timestamp_ms;
    event->matched = 0;
    other_key = join_key_find(join, opposite, key);
    if (other_key == NULL) return RE_STATUS_OK;
    /* One queued match per strategy-satisfying same-key pair (upstream emits
     * a JoinedEvent per pair, :116-129); both sides flag matched so outer
     * joins never report them as unmatched. */
    for (index = 0u; index < other_key->count; ++index) {
        re_stream_join_event_t *other = &other_key->events[index];
        uint64_t left_ts = own == 0u ? timestamp_ms : other->timestamp_ms;
        uint64_t right_ts = own == 0u ? other->timestamp_ms : timestamp_ms;
        if (!join_within_window(join, left_ts, right_ts)) continue;
        status = join_queue_match(join, other_key, left_ts, right_ts);
        if (status != RE_STATUS_OK) return status;
        other->matched = 1;
        event->matched = 1;
    }
    return RE_STATUS_OK;
}

re_status_t re_stream_join_update_watermark(re_stream_join_t *join,
                                            re_stream_join_side_t side,
                                            uint64_t watermark_ms) {
    uint64_t window_size;
    size_t side_index;
    size_t key_index;
    size_t event_index;
    int emit_left;
    int emit_right;
    if (join == NULL || (side != RE_STREAM_JOIN_LEFT && side != RE_STREAM_JOIN_RIGHT))
        return RE_STATUS_INVALID_ARGUMENT;
    /* Watermarks only advance (the window record path's advance rule and
     * upstream's emitted-only-if-advancing, watermark.rs:131); a
     * non-advancing update is an accepted no-op. */
    if (watermark_ms <= join->watermark) return RE_STATUS_OK;
    join->watermark = watermark_ms;
    window_size = join_window_size(join);
    if (window_size == UINT64_MAX) return RE_STATUS_OK; /* COUNT_WINDOW never expires. */
    emit_left = join->join_type == RE_STREAM_JOIN_LEFT_OUTER ||
        join->join_type == RE_STREAM_JOIN_FULL_OUTER;
    emit_right = join->join_type == RE_STREAM_JOIN_RIGHT_OUTER ||
        join->join_type == RE_STREAM_JOIN_FULL_OUTER;
    /* Outer sides emit their expired unmatched events first; the eviction
     * below then removes them, so each event is emitted at most once across
     * all updates (upstream's eager process-time emission plus its
     * evict-then-emit straggler pass, :135/:278, composed to one emission
     * point - documented). */
    for (side_index = 0u; side_index < 2u; ++side_index) {
        if ((side_index == 0u && !emit_left) || (side_index == 1u && !emit_right)) continue;
        for (key_index = 0u; key_index < join->key_count[side_index]; ++key_index) {
            re_stream_join_key_entry_t *key_entry = &join->keys[side_index][key_index];
            for (event_index = 0u; event_index < key_entry->count; ++event_index) {
                re_stream_join_event_t *event = &key_entry->events[event_index];
                re_status_t status;
                if (event->matched ||
                    !join_event_expired(watermark_ms, event->timestamp_ms, window_size))
                    continue;
                status = join_queue_match(join, key_entry,
                    side_index == 0u ? event->timestamp_ms : 0u,
                    side_index == 0u ? 0u : event->timestamp_ms);
                if (status != RE_STATUS_OK) return status;
            }
        }
    }
    /* Evict every expired event from both sides (upstream
     * evict_expired_events, :247, extended from the front-run to the whole
     * deque so out-of-order stragglers cannot linger or re-emit). Key
     * entries stay: their strings back queued-match borrows until destroy. */
    for (side_index = 0u; side_index < 2u; ++side_index) {
        for (key_index = 0u; key_index < join->key_count[side_index]; ++key_index) {
            re_stream_join_key_entry_t *key_entry = &join->keys[side_index][key_index];
            size_t kept = 0u;
            for (event_index = 0u; event_index < key_entry->count; ++event_index) {
                if (!join_event_expired(watermark_ms, key_entry->events[event_index].timestamp_ms,
                                        window_size))
                    key_entry->events[kept++] = key_entry->events[event_index];
            }
            key_entry->count = kept;
        }
    }
    return RE_STATUS_OK;
}

re_status_t re_stream_join_drain(re_stream_join_t *join,
                                 re_stream_join_match_t *out_matches,
                                 size_t capacity, size_t *out_count) {
    size_t total;
    size_t index;
    size_t drain_count;
    if (join == NULL || out_count == NULL || (out_matches == NULL && capacity != 0u))
        return RE_STATUS_INVALID_ARGUMENT;
    total = join->match_count;
    *out_count = total;
    drain_count = total < capacity ? total : capacity;
    for (index = 0u; index < drain_count; ++index) {
        const re_stream_join_match_entry_t *entry = &join->matches[index];
        out_matches[index].key.data = entry->key;
        out_matches[index].key.size = entry->key_size;
        out_matches[index].left_timestamp_ms = entry->left_timestamp_ms;
        out_matches[index].right_timestamp_ms = entry->right_timestamp_ms;
        out_matches[index].join_timestamp_ms = entry->join_timestamp_ms;
    }
    if (drain_count != 0u) {
        memmove(join->matches, join->matches + drain_count,
                (join->match_count - drain_count) * sizeof(*join->matches));
        join->match_count -= drain_count;
    }
    /* The buffer-capacity idiom (re_rule_template_instantiate): the caller
     * sees the total and what fits; an exact fit is RE_STATUS_OK. */
    return total > capacity ? RE_STATUS_LIMIT : RE_STATUS_OK;
}

uint64_t re_stream_join_dropped(const re_stream_join_t *join) {
    return join == NULL ? 0u : join->dropped;
}
