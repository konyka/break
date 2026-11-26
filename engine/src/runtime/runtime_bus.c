#include <runtime/runtime_bus.h>

#include <core/platform_thread.h>
#include <runtime/runtime_metrics.h>
#include <runtime/runtime_test_hooks.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The registry, the subscriber table and every counter sit behind one
 * mutex. Publishing holds it across the fan-out, which keeps unsubscribe
 * synchronous (see runtime_bus.h); the queues take their own locks inside,
 * and they never call back into the bus, so the order bus -> queue is the
 * only lock order. */

typedef struct {
    bool used;
    u16 kind;
    u16 max_version;
    usize max_payload;
    bool control;
    u32 max_per_tick;
    u32 tick_published;
    char name[BREAK_RUNTIME_BUS_MAX_NAME + 1u];
    BreakRuntimeBusKindStats stats;
} RuntimeBusKindSlot;

typedef struct {
    u32 id; /* 0 = free */
    char name[BREAK_RUNTIME_BUS_MAX_NAME + 1u];
    BreakRuntimeQueue *queue;
    u16 kinds[BREAK_RUNTIME_BUS_MAX_SUBSCRIBER_KINDS];
    u32 kind_count;
    BreakRuntimeBusSubscriberStats stats;
} RuntimeBusSubscriber;

struct BreakRuntimeBus {
    PlatformMutex mutex;
    RuntimeBusKindSlot kinds[BREAK_RUNTIME_BUS_MAX_KINDS];
    RuntimeBusSubscriber subscribers[BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS];
    u32 next_id;
    BreakRuntimeBusStats stats;
    BreakRuntimeProfiler *profiler; /* optional; leaf lock, safe under mutex */
};

static bool runtime_bus_name_ok(const char *name)
{
    usize n = 0u;
    if (!name) {
        return false;
    }
    for (; name[n] != '\0'; n++) {
        char c = name[n];
        bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '-';
        if (!ok || n >= BREAK_RUNTIME_BUS_MAX_NAME) {
            return false;
        }
    }
    return n > 0u;
}

static RuntimeBusKindSlot *runtime_bus_find_kind(BreakRuntimeBus *bus, u16 kind)
{
    u32 i;
    for (i = 0; i < BREAK_RUNTIME_BUS_MAX_KINDS; i++) {
        if (bus->kinds[i].used && bus->kinds[i].kind == kind) {
            return &bus->kinds[i];
        }
    }
    return NULL;
}

static RuntimeBusSubscriber *runtime_bus_find_subscriber(BreakRuntimeBus *bus, u32 id)
{
    u32 i;
    if (id == 0u) {
        return NULL;
    }
    for (i = 0; i < BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS; i++) {
        if (bus->subscribers[i].id == id) {
            return &bus->subscribers[i];
        }
    }
    return NULL;
}

static bool runtime_bus_wants(const RuntimeBusSubscriber *s, u16 kind)
{
    u32 i;
    for (i = 0; i < s->kind_count; i++) {
        if (s->kinds[i] == kind) {
            return true;
        }
    }
    return false;
}

BreakRuntimeError break_runtime_bus_create(BreakRuntimeBus **out_bus)
{
    BreakRuntimeBus *bus;
    if (!out_bus) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_bus = NULL;
    bus = (BreakRuntimeBus *)break_runtime_test_calloc(sizeof(*bus));
    if (!bus) {
        return BREAK_RUNTIME_OOM;
    }
    platform_mutex_init(&bus->mutex);
    bus->next_id = 1u;
    *out_bus = bus;
    return BREAK_RUNTIME_OK;
}

void break_runtime_bus_destroy(BreakRuntimeBus *bus)
{
    if (!bus) {
        return;
    }
    platform_mutex_destroy(&bus->mutex);
    free(bus);
}

BreakRuntimeError break_runtime_bus_register_kind(BreakRuntimeBus *bus,
                                                  const BreakRuntimeBusKind *kind)
{
    RuntimeBusKindSlot *slot = NULL;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    u32 i;
    if (!bus || !kind || kind->max_version == 0u ||
        kind->max_payload > (usize)BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD ||
        !runtime_bus_name_ok(kind->name)) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    if (runtime_bus_find_kind(bus, kind->kind)) {
        result = BREAK_RUNTIME_INVALID;
    } else {
        for (i = 0; i < BREAK_RUNTIME_BUS_MAX_KINDS && !slot; i++) {
            if (!bus->kinds[i].used) {
                slot = &bus->kinds[i];
            }
        }
        if (!slot) {
            result = BREAK_RUNTIME_OVERLOAD;
        } else {
            memset(slot, 0, sizeof(*slot));
            slot->used = true;
            slot->kind = kind->kind;
            slot->max_version = kind->max_version;
            slot->max_payload = kind->max_payload;
            slot->control = kind->control;
            slot->max_per_tick = kind->max_per_tick;
            strcpy(slot->name, kind->name);
        }
    }
    platform_mutex_unlock(&bus->mutex);
    return result;
}

BreakRuntimeError break_runtime_bus_subscribe(BreakRuntimeBus *bus, const char *name,
                                              BreakRuntimeQueue *queue, const u16 *kinds,
                                              u32 kind_count, u32 *out_id)
{
    RuntimeBusSubscriber *slot = NULL;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    u32 i;
    u32 j;
    if (out_id) {
        *out_id = 0u;
    }
    if (!bus || !queue || !kinds || kind_count == 0u ||
        kind_count > BREAK_RUNTIME_BUS_MAX_SUBSCRIBER_KINDS || !runtime_bus_name_ok(name)) {
        return BREAK_RUNTIME_INVALID;
    }
    for (i = 0; i < kind_count; i++) {
        for (j = 0; j < i; j++) {
            if (kinds[i] == kinds[j]) {
                return BREAK_RUNTIME_INVALID;
            }
        }
    }
    platform_mutex_lock(&bus->mutex);
    for (i = 0; i < kind_count && result == BREAK_RUNTIME_OK; i++) {
        if (!runtime_bus_find_kind(bus, kinds[i])) {
            result = BREAK_RUNTIME_REJECTED;
        }
    }
    for (i = 0; result == BREAK_RUNTIME_OK && i < BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS && !slot; i++) {
        if (bus->subscribers[i].id == 0u) {
            slot = &bus->subscribers[i];
        }
    }
    if (result == BREAK_RUNTIME_OK && !slot) {
        result = BREAK_RUNTIME_OVERLOAD;
    }
    if (result == BREAK_RUNTIME_OK) {
        memset(slot, 0, sizeof(*slot));
        slot->id = bus->next_id++;
        if (bus->next_id == 0u) {
            bus->next_id = 1u;
        }
        strcpy(slot->name, name);
        slot->queue = queue;
        memcpy(slot->kinds, kinds, (usize)kind_count * sizeof(u16));
        slot->kind_count = kind_count;
        if (out_id) {
            *out_id = slot->id;
        }
    }
    platform_mutex_unlock(&bus->mutex);
    return result;
}

BreakRuntimeError break_runtime_bus_unsubscribe(BreakRuntimeBus *bus, u32 id)
{
    RuntimeBusSubscriber *s;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (!bus) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    s = runtime_bus_find_subscriber(bus, id);
    if (!s) {
        result = BREAK_RUNTIME_STALE;
    } else {
        memset(s, 0, sizeof(*s));
    }
    platform_mutex_unlock(&bus->mutex);
    return result;
}

/* Under bus->mutex. The profiler's own mutex is a leaf (it never calls
 * back), so the lock order bus -> profiler cannot deadlock. */
static void runtime_bus_trace(BreakRuntimeBus *bus, const char *event,
                              const BreakRuntimeMessageView *view)
{
    if (bus->profiler) {
        (void)break_runtime_profiler_record_correlated(bus->profiler, event,
                                                       view->correlation_id);
    }
}

BreakRuntimeError break_runtime_bus_publish(BreakRuntimeBus *bus,
                                            const BreakRuntimeMessageView *view,
                                            u32 *out_delivered)
{
    RuntimeBusKindSlot *kind;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    u32 delivered = 0u;
    u32 i;
    if (out_delivered) {
        *out_delivered = 0u;
    }
    if (!bus || !view || (!view->data && view->size > 0u)) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    kind = runtime_bus_find_kind(bus, view->kind);
    if (!kind) {
        bus->stats.unknown_kind_rejects++;
        runtime_bus_trace(bus, "bus.reject.kind", view);
        result = BREAK_RUNTIME_REJECTED;
    } else if (view->version == 0u || view->version > kind->max_version) {
        kind->stats.version_rejects++;
        runtime_bus_trace(bus, "bus.reject.version", view);
        result = BREAK_RUNTIME_REJECTED;
    } else if (view->size > kind->max_payload) {
        kind->stats.size_rejects++;
        runtime_bus_trace(bus, "bus.reject.size", view);
        result = BREAK_RUNTIME_OVERLOAD;
    } else if (kind->max_per_tick != 0u && kind->tick_published >= kind->max_per_tick) {
        kind->stats.quota_rejects++;
        runtime_bus_trace(bus, "bus.reject.quota", view);
        result = BREAK_RUNTIME_OVERLOAD;
    } else {
        BreakRuntimeMessageView copy_view = *view;
        if (kind->control) {
            copy_view.flags |= BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
        } else {
            copy_view.flags &= ~(u32)BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
        }
        kind->tick_published++;
        kind->stats.published++;
        for (i = 0; i < BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS; i++) {
            RuntimeBusSubscriber *s = &bus->subscribers[i];
            BreakRuntimeOwnedMessage *copy = NULL;
            bool queued = false;
            if (s->id == 0u || !runtime_bus_wants(s, view->kind)) {
                continue;
            }
            if (break_runtime_message_copy(&copy_view, &copy) == BREAK_RUNTIME_OK) {
                if (break_runtime_queue_enqueue(s->queue, copy,
                                                break_runtime_queue_generation(s->queue)) ==
                    BREAK_RUNTIME_OK) {
                    queued = true;
                } else {
                    break_runtime_message_release(copy);
                }
            }
            if (queued) {
                s->stats.delivered++;
                kind->stats.delivered++;
                delivered++;
            } else {
                s->stats.dropped++;
                kind->stats.dropped++;
                runtime_bus_trace(bus, "bus.drop", view);
                result = BREAK_RUNTIME_OVERLOAD;
            }
        }
    }
    platform_mutex_unlock(&bus->mutex);
    if (out_delivered) {
        *out_delivered = delivered;
    }
    return result;
}

BreakRuntimeError break_runtime_bus_attach_profiler(BreakRuntimeBus *bus,
                                                    BreakRuntimeProfiler *profiler)
{
    if (!bus) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    bus->profiler = profiler;
    platform_mutex_unlock(&bus->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_bus_tick(BreakRuntimeBus *bus)
{
    u32 i;
    if (!bus) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    for (i = 0; i < BREAK_RUNTIME_BUS_MAX_KINDS; i++) {
        bus->kinds[i].tick_published = 0u;
    }
    platform_mutex_unlock(&bus->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_bus_stats(BreakRuntimeBus *bus, BreakRuntimeBusStats *out_stats)
{
    if (!bus || !out_stats) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    *out_stats = bus->stats;
    platform_mutex_unlock(&bus->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_bus_kind_matches(BreakRuntimeBus *bus,
                                                 const BreakRuntimeBusKind *kind)
{
    RuntimeBusKindSlot *slot;
    BreakRuntimeError result;
    if (!bus || !kind || !kind->name) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    slot = runtime_bus_find_kind(bus, kind->kind);
    if (!slot) {
        result = BREAK_RUNTIME_STALE;
    } else if (slot->max_version == kind->max_version && slot->max_payload == kind->max_payload &&
               slot->control == kind->control && slot->max_per_tick == kind->max_per_tick &&
               strncmp(slot->name, kind->name, sizeof(slot->name)) == 0 &&
               strlen(kind->name) < sizeof(slot->name)) {
        result = BREAK_RUNTIME_OK;
    } else {
        result = BREAK_RUNTIME_REJECTED;
    }
    platform_mutex_unlock(&bus->mutex);
    return result;
}

bool break_runtime_bus_kind_accepts(BreakRuntimeBus *bus, u16 kind, u16 version, usize size)
{
    RuntimeBusKindSlot *slot;
    bool ok;
    if (!bus) {
        return false;
    }
    platform_mutex_lock(&bus->mutex);
    slot = runtime_bus_find_kind(bus, kind);
    ok = slot && version != 0u && version <= slot->max_version && size <= slot->max_payload;
    platform_mutex_unlock(&bus->mutex);
    return ok;
}

BreakRuntimeError break_runtime_bus_kind_stats(BreakRuntimeBus *bus, u16 kind,
                                               BreakRuntimeBusKindStats *out_stats)
{
    RuntimeBusKindSlot *slot;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (!bus || !out_stats) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    slot = runtime_bus_find_kind(bus, kind);
    if (slot) {
        *out_stats = slot->stats;
    } else {
        result = BREAK_RUNTIME_REJECTED;
    }
    platform_mutex_unlock(&bus->mutex);
    return result;
}

BreakRuntimeError break_runtime_bus_subscriber_stats(BreakRuntimeBus *bus, u32 id,
                                                     BreakRuntimeBusSubscriberStats *out_stats)
{
    RuntimeBusSubscriber *s;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (!bus || !out_stats) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&bus->mutex);
    s = runtime_bus_find_subscriber(bus, id);
    if (s) {
        *out_stats = s->stats;
    } else {
        result = BREAK_RUNTIME_STALE;
    }
    platform_mutex_unlock(&bus->mutex);
    return result;
}

typedef struct {
    char *buf;
    usize capacity;
    usize len;
} RuntimeBusWriter;

/* Formats straight into the caller's buffer so a record of any length is
 * either written whole or only measured; w->len always counts the full
 * output, which is what out_len reports when the buffer is too small. */
static void runtime_bus_printf(RuntimeBusWriter *w, const char *fmt, ...)
{
    va_list ap;
    int n;
    char *dst = NULL;
    usize room = 0u;
    if (w->len < w->capacity) {
        dst = w->buf + w->len;
        room = w->capacity - w->len;
    }
    va_start(ap, fmt);
    n = vsnprintf(dst, room, fmt, ap);
    va_end(ap);
    if (n <= 0) {
        return;
    }
    w->len += (usize)n;
}

/* Names passed validation ([A-Za-z0-9._-]), so they need no JSON escaping. */
BreakRuntimeError break_runtime_bus_export_topology(BreakRuntimeBus *bus, char *buf,
                                                    usize capacity, usize *out_len)
{
    RuntimeBusWriter w;
    bool first = true;
    u32 i;
    u32 k;
    if (!bus || !out_len) {
        return BREAK_RUNTIME_INVALID;
    }
    w.buf = buf;
    w.capacity = buf ? capacity : 0u;
    w.len = 0u;
    platform_mutex_lock(&bus->mutex);
    runtime_bus_printf(&w, "{\"unknown_kind_rejects\":%llu,\"kinds\":[",
                       (unsigned long long)bus->stats.unknown_kind_rejects);
    for (i = 0; i < BREAK_RUNTIME_BUS_MAX_KINDS; i++) {
        const RuntimeBusKindSlot *s = &bus->kinds[i];
        if (!s->used) {
            continue;
        }
        runtime_bus_printf(&w,
                           "%s{\"kind\":%u,\"name\":\"%s\",\"max_version\":%u,\"max_payload\":%llu,"
                           "\"control\":%s,\"max_per_tick\":%u,"
                           "\"published\":%llu,\"delivered\":%llu,\"dropped\":%llu,"
                           "\"version_rejects\":%llu,\"size_rejects\":%llu,\"quota_rejects\":%llu}",
                           first ? "" : ",", (unsigned)s->kind, s->name, (unsigned)s->max_version,
                           (unsigned long long)s->max_payload, s->control ? "true" : "false",
                           (unsigned)s->max_per_tick,
                           (unsigned long long)s->stats.published,
                           (unsigned long long)s->stats.delivered,
                           (unsigned long long)s->stats.dropped,
                           (unsigned long long)s->stats.version_rejects,
                           (unsigned long long)s->stats.size_rejects,
                           (unsigned long long)s->stats.quota_rejects);
        first = false;
    }
    runtime_bus_printf(&w, "],\"subscribers\":[");
    first = true;
    for (i = 0; i < BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS; i++) {
        const RuntimeBusSubscriber *s = &bus->subscribers[i];
        BreakRuntimeQueueStats qs;
        if (s->id == 0u) {
            continue;
        }
        memset(&qs, 0, sizeof(qs));
        (void)break_runtime_queue_stats(s->queue, &qs);
        runtime_bus_printf(&w, "%s{\"id\":%u,\"name\":\"%s\",\"kinds\":[", first ? "" : ",",
                           (unsigned)s->id, s->name);
        for (k = 0; k < s->kind_count; k++) {
            runtime_bus_printf(&w, "%s%u", k ? "," : "", (unsigned)s->kinds[k]);
        }
        runtime_bus_printf(&w,
                           "],\"delivered\":%llu,\"dropped\":%llu,\"queue\":{\"enqueued\":%llu,"
                           "\"dequeued\":%llu,\"high_water\":%llu,\"overload_rejects\":%llu}}",
                           (unsigned long long)s->stats.delivered,
                           (unsigned long long)s->stats.dropped,
                           (unsigned long long)qs.enqueued, (unsigned long long)qs.dequeued,
                           (unsigned long long)qs.high_water,
                           (unsigned long long)qs.overload_rejects);
        first = false;
    }
    runtime_bus_printf(&w, "]}");
    platform_mutex_unlock(&bus->mutex);
    *out_len = w.len;
    if (w.len >= w.capacity) {
        if (buf && capacity > 0u) {
            buf[0] = '\0';
        }
        return BREAK_RUNTIME_OVERLOAD;
    }
    buf[w.len] = '\0';
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_bus_export_metrics(BreakRuntimeBus *bus,
                                                    struct BreakRuntimeMetrics *metrics)
{
    struct {
        const char *name;
        u64 value;
    } gauges[9];
    u64 published = 0u, delivered = 0u, dropped = 0u;
    u64 version_rejects = 0u, size_rejects = 0u, quota_rejects = 0u;
    u64 unknown_kind_rejects;
    u32 kinds = 0u, subscribers = 0u;
    u32 i;
    if (!bus || !metrics) {
        return BREAK_RUNTIME_INVALID;
    }
    /* Sum the aggregates under the bus lock, then release it before touching
     * the metrics registry: the registry has its own leaf lock and must never
     * be entered while holding the bus lock. */
    platform_mutex_lock(&bus->mutex);
    unknown_kind_rejects = bus->stats.unknown_kind_rejects;
    for (i = 0; i < BREAK_RUNTIME_BUS_MAX_KINDS; i++) {
        const RuntimeBusKindSlot *s = &bus->kinds[i];
        if (!s->used) {
            continue;
        }
        kinds++;
        published += s->stats.published;
        delivered += s->stats.delivered;
        dropped += s->stats.dropped;
        version_rejects += s->stats.version_rejects;
        size_rejects += s->stats.size_rejects;
        quota_rejects += s->stats.quota_rejects;
    }
    for (i = 0; i < BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS; i++) {
        if (bus->subscribers[i].id != 0u) {
            subscribers++;
        }
    }
    platform_mutex_unlock(&bus->mutex);

    gauges[0].name = "bus.published";            gauges[0].value = published;
    gauges[1].name = "bus.delivered";            gauges[1].value = delivered;
    gauges[2].name = "bus.dropped";              gauges[2].value = dropped;
    gauges[3].name = "bus.version_rejects";      gauges[3].value = version_rejects;
    gauges[4].name = "bus.size_rejects";         gauges[4].value = size_rejects;
    gauges[5].name = "bus.quota_rejects";        gauges[5].value = quota_rejects;
    gauges[6].name = "bus.unknown_kind_rejects"; gauges[6].value = unknown_kind_rejects;
    gauges[7].name = "bus.kinds";                gauges[7].value = kinds;
    gauges[8].name = "bus.subscribers";          gauges[8].value = subscribers;
    for (i = 0; i < 9u; i++) {
        BreakRuntimeError result = break_runtime_metrics_set(
            metrics, gauges[i].name, BREAK_RUNTIME_METRIC_GAUGE, gauges[i].value);
        if (result != BREAK_RUNTIME_OK) {
            return result;
        }
    }
    return BREAK_RUNTIME_OK;
}
