#pragma once

#include <core/types.h>
#include <runtime/runtime_message.h>
#include <runtime/runtime_profiler.h>
#include <runtime/runtime_queue.h>
#include <runtime/runtime_types.h>

/* Runtime Core message bus (design: docs/design/runtime_message_model.md
 * "消息总线").
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * Contract:
 *  - Kind registry: every published kind must be registered first with the
 *    newest version consumers understand (versions 1..max_version are
 *    accepted) and a per-kind payload budget no larger than
 *    BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD. Unknown kinds and versions are
 *    REJECTED, oversize payloads are OVERLOAD; nothing is delivered and the
 *    rejection is counted.
 *  - Priority: a control kind's copies use the subscriber queues' reserved
 *    control capacity, so shutdown/failure kinds still arrive when data has
 *    filled a queue. Quota: a kind may cap its accepted publishes per tick
 *    (break_runtime_bus_tick), so one chatty producer cannot fill every
 *    subscriber queue.
 *  - Subscribers are named (diagnostics only) and own a bounded
 *    BreakRuntimeQueue that they drain; the bus borrows the queue. A
 *    subscriber lists the kinds it receives; each must be registered.
 *  - publish() copies the view once per subscriber of its kind (each gets
 *    its own owned message, in subscription order) and enqueues it with the
 *    queue's current generation. It never blocks on a subscriber: a full or
 *    closed queue, or a failed copy, drops that subscriber's copy, counts it
 *    on the subscriber and the kind, and the other subscribers still get
 *    theirs. publish() then returns OVERLOAD (backpressure) with
 *    *out_delivered telling how many copies were queued.
 *  - Thread safety: every call may run on any thread. A mutex serializes the
 *    registry and the fan-out, so unsubscribe() returning means the bus no
 *    longer touches that queue; only then may its owner destroy it.
 *    destroy() requires that no other call is in flight.
 *  - Topology export: break_runtime_bus_export_topology writes the kinds,
 *    subscribers, their counters and their queues' stats as one JSON object.
 *
 * Error taxonomy:
 *   INVALID  — NULL argument, malformed kind/name, duplicate kind, empty or
 *              duplicated kind list, payload pointer NULL with size > 0.
 *   REJECTED — unknown kind or version (publish, kind stats), subscription
 *              to an unregistered kind.
 *   OVERLOAD — payload over the kind's budget, the kind's per-tick quota
 *              used up, a registry or subscriber
 *              table that is full, a dropped subscriber copy, an export
 *              buffer that is too small (*out_len gives the needed length).
 *   STALE    — unknown or already removed subscriber id; unregistered kind
 *              (kind_matches).
 *   OOM      — allocation failure at create.
 */

#define BREAK_RUNTIME_BUS_MAX_KINDS 64u
#define BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS 32u
#define BREAK_RUNTIME_BUS_MAX_SUBSCRIBER_KINDS 16u
/* Names are 1..31 characters from [A-Za-z0-9._-]. */
#define BREAK_RUNTIME_BUS_MAX_NAME 31u

typedef struct BreakRuntimeBus BreakRuntimeBus; /* opaque, owned by caller */
struct BreakRuntimeMetrics;                     /* runtime_metrics.h */

typedef struct BreakRuntimeBusKind {
    u16 kind;
    u16 max_version;
    usize max_payload;
    const char *name; /* copied */
    /* Copies carry BREAK_RUNTIME_MESSAGE_FLAG_CONTROL and may use the
     * subscriber queues' reserved control slots; for other kinds the bus
     * clears that flag whatever the publisher set. */
    bool control;
    /* Accepted publishes between two break_runtime_bus_tick calls; 0 means
     * unlimited. Publishes over the quota are OVERLOAD, reach nobody and
     * count as quota_rejects. */
    u32 max_per_tick;
} BreakRuntimeBusKind;

typedef struct BreakRuntimeBusStats {
    u64 unknown_kind_rejects;
} BreakRuntimeBusStats;

typedef struct BreakRuntimeBusKindStats {
    u64 published;       /* accepted publish calls */
    u64 delivered;       /* copies queued, all subscribers */
    u64 dropped;         /* copies dropped, all subscribers */
    u64 version_rejects;
    u64 size_rejects;
    u64 quota_rejects;
} BreakRuntimeBusKindStats;

typedef struct BreakRuntimeBusSubscriberStats {
    u64 delivered;
    u64 dropped;
} BreakRuntimeBusSubscriberStats;

BreakRuntimeError break_runtime_bus_create(BreakRuntimeBus **out_bus);
void break_runtime_bus_destroy(BreakRuntimeBus *bus);

BreakRuntimeError break_runtime_bus_register_kind(BreakRuntimeBus *bus,
                                                  const BreakRuntimeBusKind *kind);

/* Whether `kind` is registered with exactly these parameters (version,
 * budget, name, control, quota): OK when it is, REJECTED when it is
 * registered differently, STALE when it is not registered, INVALID for
 * NULL arguments. Lets several components share one kind safely. */
BreakRuntimeError break_runtime_bus_kind_matches(BreakRuntimeBus *bus,
                                                 const BreakRuntimeBusKind *kind);

/* Whether a publish of `kind` at `version` with a `size`-byte payload would
 * pass the registry checks (registered, version within 1..max_version, size
 * within the budget). Quota and subscriber queues are not considered. False
 * for a NULL bus. */
bool break_runtime_bus_kind_accepts(BreakRuntimeBus *bus, u16 kind, u16 version, usize size);

/* *out_id (optional) receives a nonzero id that is never reused. */
BreakRuntimeError break_runtime_bus_subscribe(BreakRuntimeBus *bus, const char *name,
                                              BreakRuntimeQueue *queue, const u16 *kinds,
                                              u32 kind_count, u32 *out_id);
BreakRuntimeError break_runtime_bus_unsubscribe(BreakRuntimeBus *bus, u32 id);

/* *out_delivered (optional) is set on every return, 0 when nothing was
 * delivered. */
BreakRuntimeError break_runtime_bus_publish(BreakRuntimeBus *bus,
                                            const BreakRuntimeMessageView *view,
                                            u32 *out_delivered);

/* Records every dropped copy and every rejected publish as a profiler
 * event carrying the message's correlation_id, so traces show where a
 * causal chain hit backpressure: "bus.drop" (a subscriber queue was full or
 * closed, or the copy failed), "bus.reject.kind", "bus.reject.version",
 * "bus.reject.size", "bus.reject.quota". Delivered copies record nothing.
 * Recording follows the profiler's hot-path contract (no allocation, no
 * wait); a full profiler ring only counts its own overflow. NULL detaches.
 * The profiler must outlive the attachment. */
BreakRuntimeError break_runtime_bus_attach_profiler(BreakRuntimeBus *bus,
                                                    BreakRuntimeProfiler *profiler);

/* Starts a new quota period for every kind (typically once per frame). */
BreakRuntimeError break_runtime_bus_tick(BreakRuntimeBus *bus);

BreakRuntimeError break_runtime_bus_stats(BreakRuntimeBus *bus, BreakRuntimeBusStats *out_stats);
BreakRuntimeError break_runtime_bus_kind_stats(BreakRuntimeBus *bus, u16 kind,
                                               BreakRuntimeBusKindStats *out_stats);
BreakRuntimeError break_runtime_bus_subscriber_stats(BreakRuntimeBus *bus, u32 id,
                                                     BreakRuntimeBusSubscriberStats *out_stats);

/* NUL-terminated JSON. OVERLOAD with buf[0] = '\0' (capacity > 0) when the
 * buffer is too small; *out_len always receives the length without the NUL. */
BreakRuntimeError break_runtime_bus_export_topology(BreakRuntimeBus *bus, char *buf,
                                                    usize capacity, usize *out_len);

/* Mirrors the bus's current aggregate counters into `metrics` as GAUGES,
 * summed across every registered kind. Gauges (not counters) so re-exporting
 * the same cumulative totals is idempotent and never double-counts. The names
 * are:
 *   bus.published, bus.delivered, bus.dropped, bus.version_rejects,
 *   bus.size_rejects, bus.quota_rejects (summed over kinds),
 *   bus.unknown_kind_rejects (bus-wide), bus.kinds, bus.subscribers (counts).
 * Any error from a metrics set (table full, closed, kind mismatch) is returned
 * and stops the export; a partial set may already have landed. INVALID on a
 * NULL argument. Takes the bus lock briefly; `metrics` may be any registry the
 * caller owns on this (the metrics' owner) thread. */
BreakRuntimeError break_runtime_bus_export_metrics(BreakRuntimeBus *bus,
                                                    struct BreakRuntimeMetrics *metrics);
