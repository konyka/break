#include "network/break_msg_rate.h"

bool break_msg_rate_init(BreakMsgRate *r, u32 msg_per_sec, u32 msg_burst,
                         u32 byte_per_sec, u32 byte_burst, u64 now_ms) {
    if (r == NULL || msg_per_sec == 0u || msg_burst == 0u ||
        byte_per_sec == 0u || byte_burst == 0u) {
        return false;
    }
    r->msg_per_sec = msg_per_sec;
    r->byte_per_sec = byte_per_sec;
    r->msg_cap_milli = (u64)msg_burst * 1000u;
    r->byte_cap_milli = (u64)byte_burst * 1000u;
    r->msg_milli = r->msg_cap_milli;
    r->byte_milli = r->byte_cap_milli;
    r->last_ms = now_ms;
    r->denied = 0u;
    return true;
}

/* tokens += elapsed_ms * rate (thousandths), saturating at cap */
static u64 refill(u64 tokens, u64 cap, u64 elapsed_ms, u32 rate) {
    u64 room = cap - tokens;
    if (elapsed_ms >= room / rate + 1u) return cap; /* would exceed: full */
    tokens += elapsed_ms * rate;
    return tokens > cap ? cap : tokens;
}

BreakMsgRateResult break_msg_rate_admit(BreakMsgRate *r, u32 bytes, u64 now_ms) {
    u64 need_bytes;
    if (r == NULL) return BREAK_MSG_RATE_INVALID;
    if (now_ms > r->last_ms) {
        u64 dt = now_ms - r->last_ms;
        r->msg_milli = refill(r->msg_milli, r->msg_cap_milli, dt, r->msg_per_sec);
        r->byte_milli = refill(r->byte_milli, r->byte_cap_milli, dt, r->byte_per_sec);
        r->last_ms = now_ms;
    }
    need_bytes = (u64)bytes * 1000u;
    if (r->msg_milli < 1000u) {
        r->denied++;
        return BREAK_MSG_RATE_MESSAGES;
    }
    if (r->byte_milli < need_bytes) {
        r->denied++;
        return BREAK_MSG_RATE_BYTES;
    }
    r->msg_milli -= 1000u;
    r->byte_milli -= need_bytes;
    return BREAK_MSG_RATE_OK;
}

u32 break_msg_rate_messages_available(const BreakMsgRate *r) {
    return r != NULL ? (u32)(r->msg_milli / 1000u) : 0u;
}

u64 break_msg_rate_denied(const BreakMsgRate *r) {
    return r != NULL ? r->denied : 0u;
}
