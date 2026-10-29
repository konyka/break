#pragma once
/* Per-connection application-message rate limit: two token buckets, one in
 * messages and one in bytes, refilled from an injected millisecond clock.
 *
 * The transport already limits admission (accepted connections per second
 * and per IP, docs/design/transport_security.md); this covers what a single
 * admitted connection may send afterwards. A message is admitted only if
 * BOTH buckets hold enough (1 message token and `bytes` byte tokens); a
 * refused message costs nothing. Refill is exact: tokens are kept in
 * thousandths, so a rate that is not a multiple of 1000/s loses no
 * remainder between calls. A clock that goes backwards refills nothing.
 * A message larger than the byte burst is never admissible (callers should
 * cap message size below it). Pure C, no allocation, one owner. */

#include <core/types.h>

typedef enum BreakMsgRateResult {
    BREAK_MSG_RATE_OK = 0,
    BREAK_MSG_RATE_MESSAGES, /* message bucket empty */
    BREAK_MSG_RATE_BYTES,    /* byte bucket short */
    BREAK_MSG_RATE_INVALID   /* NULL limiter */
} BreakMsgRateResult;

typedef struct BreakMsgRate {
    u64 msg_milli, msg_cap_milli; /* tokens x 1000 */
    u64 byte_milli, byte_cap_milli;
    u32 msg_per_sec, byte_per_sec;
    u64 last_ms;
    u64 denied;
} BreakMsgRate;

/* All four limits must be non-zero; buckets start full at now_ms. */
bool break_msg_rate_init(BreakMsgRate *r, u32 msg_per_sec, u32 msg_burst,
                         u32 byte_per_sec, u32 byte_burst, u64 now_ms);
BreakMsgRateResult break_msg_rate_admit(BreakMsgRate *r, u32 bytes, u64 now_ms);
u32 break_msg_rate_messages_available(const BreakMsgRate *r);
u64 break_msg_rate_denied(const BreakMsgRate *r);
