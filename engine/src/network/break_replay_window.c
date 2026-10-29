#include "network/break_replay_window.h"

void break_replay_window_init(BreakReplayWindow *w) {
    if (w == NULL) return;
    w->highest = 0u;
    w->bitmap = 0u;
}

BreakReplayResult break_replay_window_check(const BreakReplayWindow *w, u64 seq) {
    u64 age;
    if (w == NULL || seq == 0u) return BREAK_REPLAY_INVALID;
    if (seq > w->highest) return BREAK_REPLAY_OK;
    age = w->highest - seq;
    if (age >= BREAK_REPLAY_WINDOW_SIZE) return BREAK_REPLAY_TOO_OLD;
    return (w->bitmap >> age) & 1u ? BREAK_REPLAY_DUPLICATE : BREAK_REPLAY_OK;
}

BreakReplayResult break_replay_window_check_and_mark(BreakReplayWindow *w,
                                                     u64 seq) {
    BreakReplayResult r = break_replay_window_check(w, seq);
    if (r != BREAK_REPLAY_OK) return r;
    if (seq > w->highest) {
        u64 shift = seq - w->highest;
        /* shifting a u64 by >= 64 is undefined: an old window just clears */
        w->bitmap = shift >= BREAK_REPLAY_WINDOW_SIZE ? 0u : w->bitmap << shift;
        w->bitmap |= 1u;
        w->highest = seq;
    } else {
        w->bitmap |= (u64)1u << (w->highest - seq);
    }
    return BREAK_REPLAY_OK;
}

u64 break_replay_window_highest(const BreakReplayWindow *w) {
    return w != NULL ? w->highest : 0u;
}
