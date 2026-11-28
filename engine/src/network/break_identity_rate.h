#pragma once
/* Per-identity application-message rate limit: one pair of break_msg_rate
 * token buckets (messages and bytes) per authenticated identity, shared by
 * every connection that identity opens.
 *
 * The per-connection limit (break_session_manager_set_message_rate) gives a
 * new connection full buckets, so a client could raise its rate by
 * reconnecting. This table keys the buckets by the 8-byte identity the
 * transport authenticated (for AUTH v2, the key_id), so the budget is kept
 * across reconnects.
 *
 * The table is fixed-size and fails closed: when every slot is taken by an
 * identity active within idle_ms, a new identity is refused
 * (BREAK_IDENTITY_RATE_FULL) instead of evicting a live one, so a flood of
 * fresh identities cannot reset anyone's limit. A slot whose identity has
 * sent nothing for idle_ms is reused. One owner, no locks; the clock is
 * injected (monotonic milliseconds). */

#include <core/types.h>

#include <network/break_msg_rate.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_IDENTITY_RATE_MAX_IDENTITIES 4096u
/* Returned when the table is full of active identities. */
#define BREAK_IDENTITY_RATE_FULL ((BreakMsgRateResult)100)

typedef struct BreakIdentityRateConfig {
    u32 msg_per_sec;
    u32 msg_burst;
    u32 byte_per_sec;
    u32 byte_burst;
    u32 max_identities; /* 1..BREAK_IDENTITY_RATE_MAX_IDENTITIES */
    u64 idle_ms;        /* a slot idle this long may be reused */
} BreakIdentityRateConfig;

typedef struct BreakIdentityRate BreakIdentityRate;

/* NULL for a NULL config, a zero limit or an out-of-range max_identities. */
BreakIdentityRate *break_identity_rate_create(const BreakIdentityRateConfig *config);
void break_identity_rate_destroy(BreakIdentityRate *rate);

/* Admit one message of `bytes` from `identity` at now_ms. A refused message
 * costs nothing. BREAK_MSG_RATE_INVALID for a NULL table or identity. */
BreakMsgRateResult break_identity_rate_admit(BreakIdentityRate *rate,
                                             const u8 identity[8], u32 bytes,
                                             u64 now_ms);
/* Identities currently holding a slot (including idle ones not yet reused). */
size_t break_identity_rate_count(const BreakIdentityRate *rate);
/* Messages refused by a bucket or by a full table. */
u64 break_identity_rate_denied(const BreakIdentityRate *rate);

#ifdef __cplusplus
} /* extern "C" */
#endif
