#pragma once
/* Anti-replay window for application messages (RFC 4303 §3.4.3 style).
 *
 * The transport already enforces strict per-connection ordering and a
 * handshake-bound nonce; this window covers the remaining gap named in
 * docs/design/transport_security.md: authenticated application messages on
 * an unordered or reconnecting path, where each 64-bit sequence number must
 * be accepted at most once and late arrivals within the last
 * BREAK_REPLAY_WINDOW_SIZE numbers are still allowed.
 *
 * Sequence 0 is reserved (never sent), so a fresh window has highest = 0.
 * check() only answers; check_and_mark() answers and, on OK, records the
 * number. Callers verify the message's authenticity between the two (check
 * → MAC/AEAD verify → check_and_mark), so a forged packet cannot burn a
 * sequence number. The window is per (sender, key) — reset it with init
 * whenever the key changes. Pure C, no allocation, no locking (one owner). */

#include <core/types.h>

#define BREAK_REPLAY_WINDOW_SIZE 64u

typedef enum BreakReplayResult {
    BREAK_REPLAY_OK = 0,
    BREAK_REPLAY_DUPLICATE, /* already accepted */
    BREAK_REPLAY_TOO_OLD,   /* older than the window: cannot be told apart */
    BREAK_REPLAY_INVALID    /* NULL window or sequence 0 */
} BreakReplayResult;

typedef struct BreakReplayWindow {
    u64 highest; /* largest accepted sequence (0 = none yet) */
    u64 bitmap;  /* bit i: highest - i was accepted */
} BreakReplayWindow;

void break_replay_window_init(BreakReplayWindow *w);
BreakReplayResult break_replay_window_check(const BreakReplayWindow *w, u64 seq);
BreakReplayResult break_replay_window_check_and_mark(BreakReplayWindow *w,
                                                     u64 seq);
u64 break_replay_window_highest(const BreakReplayWindow *w);
