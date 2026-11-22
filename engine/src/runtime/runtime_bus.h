#pragma once

#include <core/types.h>
#include <runtime/runtime_message.h>
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
