#pragma once
/* ==========================================================================
 *  break_authority — Stage 5 subproject 5: the server-side reference engine
 *  for "the client is never authoritative" (docs/design/server_authority.md,
 *  security_threat_model.md section 3).
 *
 *  Intents come in, the server's own ledgers decide, a fixed verdict comes
 *  out. The wire carries only the player's request:
 *    SPEND  : which item and how many  -> the server prices it
 *    ATTACK : which target             -> the server decides the damage
 *  There is no field for a balance, a price, a damage value or a result, so
 *  there is nothing for a client to lie about. Balances, item counts and
 *  health change only inside this library.
 *
 *  Identity: every call that acts for a player takes the session id as an
 *  ARGUMENT. It comes from the authenticated transport (the connection's
 *  session), never from the payload; break_authority_decode_intent has no
 *  session field and rejects any payload with extra bytes.
 *
 *  Order of checks per intent (cheapest, least-trusting first; a denied
 *  intent changes no ledger):
 *    session exists -> sequence (zero, window, gap, replay) -> rate ->
 *    argument ranges -> ledger rules.
 *  A sequence number is marked used when the intent passes the sequence
 *  check and is REFUSED BY RATE only after the check: a rate-denied intent
 *  does not burn its number (it can be retried later); every other denial
 *  after the sequence check does consume it, so a rejected intent cannot be
 *  replayed. Arithmetic is checked: price*qty and balance changes never
 *  wrap, a balance never goes below 0, health stays in [0, START_HEALTH].
 *
 *  Reuses break_replay_window (per-session sequence window) and
 *  break_msg_rate (per-session intent bucket, injected clock). The library
 *  has no clock, no I/O, no threads (one owner) and allocates only in
 *  create. It is not a game: item prices and kinds are the caller's table.
 * ========================================================================== */

#include <core/types.h>

#define BREAK_AUTHORITY_MAX_SESSIONS 4096u
#define BREAK_AUTHORITY_MAX_ITEMS 64u         /* item ids 1..64 */
#define BREAK_AUTHORITY_MAX_QTY 100u          /* per intent */
#define BREAK_AUTHORITY_MAX_GAP 1024u         /* highest accepted jump ahead */
#define BREAK_AUTHORITY_RATE_BURST 20u        /* intents at one instant */
#define BREAK_AUTHORITY_RATE_PER_SEC 10u      /* sustained intents per second */
#define BREAK_AUTHORITY_START_HEALTH 100
#define BREAK_AUTHORITY_ATTACK_DAMAGE 7       /* server-side weapon table (one weapon) */

typedef enum BreakAuthVerdict {
    BAUTH_OK = 0,
    BAUTH_DENIED_REPLAY,     /* sequence already used or too old to tell apart */
    BAUTH_DENIED_GAP,        /* sequence jumps further ahead than allowed */
    BAUTH_DENIED_RATE,       /* intent bucket empty (the number is NOT burnt) */
    BAUTH_DENIED_INVALID,    /* malformed: sequence 0, unknown item, self/dead target, bad grant */
    BAUTH_DENIED_FUNDS,      /* not enough balance */
    BAUTH_DENIED_LIMIT,      /* quantity out of range, or a grant would overflow */
    BAUTH_DENIED_NO_SESSION  /* the session (or the target's session) is not open */
} BreakAuthVerdict;

typedef struct BreakAuthority BreakAuthority;

/* max_sessions in 1..BREAK_AUTHORITY_MAX_SESSIONS, else NULL. */
BreakAuthority *break_authority_create(u32 max_sessions);
void break_authority_destroy(BreakAuthority *a); /* NULL is a no-op */

/* The item table is the server's: id 1..MAX_ITEMS, price > 0, defined once
 * (no silent re-pricing). false for a bad id/price, a redefinition or NULL. */
bool break_authority_define_item(BreakAuthority *a, u32 item_id, i64 price);
i64 break_authority_item_price(const BreakAuthority *a, u32 item_id); /* 0 = undefined */

/* Session ids are non-zero and unique among open sessions; the initial
 * balance is >= 0. A closed session's id can be reused with a fresh ledger. */
bool break_authority_open_session(BreakAuthority *a, u64 session_id, i64 initial_balance);
void break_authority_close_session(BreakAuthority *a, u64 session_id);

/* SERVER-ONLY entry (rewards, purchases settled elsewhere): there is no
 * intent that reaches it. amount >= 0; a result above INT64_MAX is refused. */
BreakAuthVerdict break_authority_grant_server(BreakAuthority *a, u64 session_id, i64 amount);

BreakAuthVerdict break_authority_intent_spend(BreakAuthority *a, u64 session_id, u64 sequence,
                                              u32 item_id, u32 qty, u64 now_us);
BreakAuthVerdict break_authority_intent_attack(BreakAuthority *a, u64 session_id, u64 sequence,
                                               u64 target_session, u64 now_us);

/* Read-only views. Unknown session: balance -1, health -1, item count 0. */
i64 break_authority_balance(const BreakAuthority *a, u64 session_id);
i32 break_authority_health(const BreakAuthority *a, u64 session_id);
u32 break_authority_item_count(const BreakAuthority *a, u64 session_id, u32 item_id);

/* ---- wire intents ---------------------------------------------------------
 *  SPEND  (17 bytes): kind u8 = 1, sequence u64 LE, item_id u32 LE, qty u32 LE
 *  ATTACK (17 bytes): kind u8 = 2, sequence u64 LE, target_session u64 LE
 *  Exact length, no session field, sequence != 0. Anything else fails. */
enum { BREAK_AUTH_INTENT_SPEND = 1, BREAK_AUTH_INTENT_ATTACK = 2 };

typedef struct BreakAuthIntent {
    u8 kind;
    u64 sequence;
    u32 item_id, qty;       /* SPEND */
    u64 target_session;     /* ATTACK */
} BreakAuthIntent;

bool break_authority_decode_intent(const u8 *p, usize n, BreakAuthIntent *out);
/* Applies a decoded intent for `session_id` (the transport's identity). */
BreakAuthVerdict break_authority_apply(BreakAuthority *a, u64 session_id,
                                       const BreakAuthIntent *intent, u64 now_us);
