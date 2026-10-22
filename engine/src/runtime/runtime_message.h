#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

/* Runtime Core owned messages (design: docs/design/runtime_message_model.md
 * §3.1/§4.3/§5.1, docs/design/runtime_overview.md §6/§8).
 *
 * Part of the formal OPTIONAL `runtime_core` static library: not linked into
 * `engine`, `engine_demo`, or `dxx_break`; consumers opt in.
 *
 * Ownership contract:
 *  - BreakRuntimeMessageView is a BORROWED view, valid only for the duration
 *    of the call it is handed to. It is never stored.
 *  - break_runtime_message_copy() validates the view (kind/version/flags/
 *    sequence metadata plus checked size arithmetic) and produces a freshly
 *    OWNED message: one allocation holding header + payload copy. The owned
 *    message never retains pointers into producer stack, World, Lua,
 *    Snowflake, or UI objects — only the copied bounded bytes.
 *  - break_runtime_message_release() releases an owned message. NULL is a
 *    no-op. In test builds (BREAK_RUNTIME_TESTING) releasing the same message
 *    twice — or a pointer this module never issued — is a contract violation
 *    and aborts with a diagnostic; release() has no return channel, so the
 *    rejection is fail-stop by design.
 *
 * Error taxonomy:
 *   INVALID  — NULL argument, or a view claiming payload bytes (size > 0)
 *              with data == NULL, or arithmetic overflow in the checked size
 *              computation.
 *   OVERLOAD — payload size exceeds the per-message byte budget
 *              (BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD); payloads are never
 *              truncated or implicitly fragmented.
 *   OOM      — allocation failure.
 */

/* Generic per-message payload budget (bytes). Per-kind registry budgets are
 * still design-only; until they exist this single bound applies to every
 * copy. Overridable at compile time like BREAK_NET_MAX_PAYLOAD_SIZE. */
#ifndef BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD
#define BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD (16u * 1024u * 1024u)
#endif

/* Message flag: the message is control-class (shutdown, close watermark,
 * failure latch) and may use a queue's reserved control capacity
 * (runtime_queue.h). Data messages never touch reserved slots. */
#define BREAK_RUNTIME_MESSAGE_FLAG_CONTROL 0x1u

typedef struct BreakRuntimeMessageView {
    u16 kind;
    u16 version;
    u32 flags;
    u64 sequence;
    const void *data;
    usize size;
} BreakRuntimeMessageView;

typedef struct BreakRuntimeOwnedMessage BreakRuntimeOwnedMessage; /* opaque, owned */

/* On success *out_message is a newly owned message; on failure *out_message
 * is set to NULL. `view` stays borrowed and is never retained. */
BreakRuntimeError break_runtime_message_copy(
    const BreakRuntimeMessageView *view,
    BreakRuntimeOwnedMessage **out_message);

/* Releases an owned message. NULL is a no-op. Double release (or a foreign
 * pointer) is a contract violation: test builds abort with a diagnostic. */
void break_runtime_message_release(BreakRuntimeOwnedMessage *message);

/* Borrows a view of an owned message's metadata and payload. The view is
 * valid until the message is released; it is never owned and must not be
 * stored past release. INVALID on NULL arguments. */
BreakRuntimeError break_runtime_message_view(
    const BreakRuntimeOwnedMessage *message,
    BreakRuntimeMessageView *out_view);
