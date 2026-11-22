#pragma once

#include <core/types.h>
#include <runtime/runtime_message.h>
#include <runtime/runtime_types.h>

/* PAL/MainLoop notices on the runtime message bus (design:
 * docs/design/runtime_message_model.md "PAL/MainLoop 接入总线").
 *
 * The platform layer stays free of runtime_core: the main loop reads its
 * facts from the platform once per frame (drawable size, close request, WSI
 * state, content scale) and hands them to an observer, which publishes one
 * notice per change. Owners on other threads (asset streaming, the renderer
 * owner, a remote session) learn about window changes from their own queue
 * instead of reading platform state they do not own.
 *
 * OWNER THREAD: the observer belongs to the main loop thread; observe and
 * destroy are called there. Publishing never waits: a full subscriber queue
 * drops that copy and the observer counts it in stats.dropped. The tracked
 * state always follows the latest facts, delivered or not, so a dropped
 * notice is never re-sent and the next notice is relative to the last
 * observation. */

#define BREAK_RUNTIME_MAINLOOP_NOTICE_KIND 0x4C4Du /* 'M' | 'L'<<8 */
#define BREAK_RUNTIME_MAINLOOP_NOTICE_VERSION 1u
#define BREAK_RUNTIME_MAINLOOP_NOTICE_SIZE 24u

typedef enum BreakRuntimeMainLoopNoticeType {
    /* the window asked to close; once per request (a request that stays
     * pending is not repeated; one made after a cancel is) */
    BREAK_RUNTIME_MAINLOOP_CLOSE_REQUESTED = 1,
    /* a = drawable width, b = drawable height (0x0 while minimised) */
    BREAK_RUNTIME_MAINLOOP_RESIZED = 2,
    /* a = new PlatformWsiState, b = previous one */
    BREAK_RUNTIME_MAINLOOP_WSI_CHANGED = 3,
    /* a = content scale in thousandths (1.5 -> 1500) */
    BREAK_RUNTIME_MAINLOOP_SCALE_CHANGED = 4
} BreakRuntimeMainLoopNoticeType;

typedef struct BreakRuntimeMainLoopNotice {
    u32 type; /* BreakRuntimeMainLoopNoticeType */
    u32 a;
    u32 b;
    u64 frame;
} BreakRuntimeMainLoopNotice;

/* What the main loop saw this frame. */
typedef struct BreakRuntimeMainLoopFacts {
    u64 frame;
    u32 drawable_width;
    u32 drawable_height;
    f32 content_scale; /* finite, >= 0 */
    u32 wsi_state;     /* PlatformWsiState */
    bool close_requested;
} BreakRuntimeMainLoopFacts;

typedef struct BreakRuntimeMainLoopStats {
    u64 observed;  /* accepted observe calls */
    u64 published; /* notices delivered to at least one subscriber */
    u64 dropped;   /* notices no subscriber received */
} BreakRuntimeMainLoopStats;

typedef struct BreakRuntimeMainLoop BreakRuntimeMainLoop; /* opaque */
struct BreakRuntimeBus;

/* Registers the notice kind as a control kind; OK when it is already
 * registered with the same parameters, REJECTED when registered otherwise. */
BreakRuntimeError break_runtime_mainloop_register_kind(struct BreakRuntimeBus *bus);

/* Registers the kind (see above) and creates an observer that publishes on
 * `bus`, which must outlive it. The first observe reports the initial
 * size, WSI state and scale. */
BreakRuntimeError break_runtime_mainloop_create(struct BreakRuntimeBus *bus,
                                                BreakRuntimeMainLoop **out_mainloop);
void break_runtime_mainloop_destroy(BreakRuntimeMainLoop *mainloop);

/* Publishes, in this order, close request, resize, WSI change and scale
 * change, each only when it differs from the previous observation.
 * INVALID for NULL arguments or a negative/non-finite scale. */
BreakRuntimeError break_runtime_mainloop_observe(BreakRuntimeMainLoop *mainloop,
                                                 const BreakRuntimeMainLoopFacts *facts);
BreakRuntimeError break_runtime_mainloop_stats(const BreakRuntimeMainLoop *mainloop,
                                               BreakRuntimeMainLoopStats *out_stats);

/* Strict decode: kind, version, size and a known type. */
BreakRuntimeError break_runtime_mainloop_notice_view(const BreakRuntimeOwnedMessage *message,
                                                     BreakRuntimeMainLoopNotice *out_notice);
