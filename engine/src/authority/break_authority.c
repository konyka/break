#include <authority/break_authority.h>

#include <network/break_msg_rate.h>
#include <network/break_replay_window.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    u64 id; /* 0 = free slot */
    i64 balance;
    i32 health;
    u32 items[BREAK_AUTHORITY_MAX_ITEMS + 1u];
    BreakReplayWindow window;
    BreakMsgRate rate;
} AuthSession;

struct BreakAuthority {
    u32 capacity;
    i64 price[BREAK_AUTHORITY_MAX_ITEMS + 1u];
    AuthSession sessions[1]; /* capacity entries */
};

BreakAuthority *break_authority_create(u32 max_sessions) {
    BreakAuthority *a;
    if (max_sessions == 0u || max_sessions > BREAK_AUTHORITY_MAX_SESSIONS) {
        return NULL;
    }
    a = (BreakAuthority *)calloc(1u, sizeof(*a) + (usize)(max_sessions - 1u) * sizeof(AuthSession));
    if (a != NULL) {
        a->capacity = max_sessions;
    }
    return a;
}

void break_authority_destroy(BreakAuthority *a) {
    free(a);
}

bool break_authority_define_item(BreakAuthority *a, u32 item_id, i64 price) {
    if (a == NULL || item_id == 0u || item_id > BREAK_AUTHORITY_MAX_ITEMS || price <= 0 ||
        a->price[item_id] != 0) {
        return false;
    }
    a->price[item_id] = price;
    return true;
}

i64 break_authority_item_price(const BreakAuthority *a, u32 item_id) {
    if (a == NULL || item_id == 0u || item_id > BREAK_AUTHORITY_MAX_ITEMS) {
        return 0;
    }
    return a->price[item_id];
}

static AuthSession *find(BreakAuthority *a, u64 id) {
    if (a == NULL || id == 0u) {
        return NULL;
    }
    for (u32 i = 0u; i < a->capacity; i++) {
        if (a->sessions[i].id == id) {
            return &a->sessions[i];
        }
    }
    return NULL;
}

bool break_authority_open_session(BreakAuthority *a, u64 session_id, i64 initial_balance) {
    AuthSession *free_slot = NULL;
    if (a == NULL || session_id == 0u || initial_balance < 0 || find(a, session_id) != NULL) {
        return false;
    }
    for (u32 i = 0u; i < a->capacity; i++) {
        if (a->sessions[i].id == 0u) {
            free_slot = &a->sessions[i];
            break;
        }
    }
    if (free_slot == NULL) {
        return false;
    }
    memset(free_slot, 0, sizeof(*free_slot));
    free_slot->id = session_id;
    free_slot->balance = initial_balance;
    free_slot->health = BREAK_AUTHORITY_START_HEALTH;
    break_replay_window_init(&free_slot->window);
    /* the bucket is created lazily at the first intent: its clock origin is
     * the caller's first timestamp, which this library cannot know here */
    return true;
}

void break_authority_close_session(BreakAuthority *a, u64 session_id) {
    AuthSession *s = find(a, session_id);
    if (s != NULL) {
        memset(s, 0, sizeof(*s));
    }
}

static const AuthSession *find_const(const BreakAuthority *a, u64 id) {
    return find((BreakAuthority *)(uintptr_t)a, id);
}

i64 break_authority_balance(const BreakAuthority *a, u64 session_id) {
    const AuthSession *s = find_const(a, session_id);
    return s != NULL ? s->balance : -1;
}

i32 break_authority_health(const BreakAuthority *a, u64 session_id) {
    const AuthSession *s = find_const(a, session_id);
    return s != NULL ? s->health : -1;
}

u32 break_authority_item_count(const BreakAuthority *a, u64 session_id, u32 item_id) {
    const AuthSession *s = find_const(a, session_id);
    if (s == NULL || item_id == 0u || item_id > BREAK_AUTHORITY_MAX_ITEMS) {
        return 0u;
    }
    return s->items[item_id];
}

BreakAuthVerdict break_authority_grant_server(BreakAuthority *a, u64 session_id, i64 amount) {
    AuthSession *s;
    if (a == NULL || amount < 0) {
        return BAUTH_DENIED_INVALID;
    }
    s = find(a, session_id);
    if (s == NULL) {
        return BAUTH_DENIED_NO_SESSION;
    }
    if (amount > INT64_MAX - s->balance) {
        return BAUTH_DENIED_LIMIT;
    }
    s->balance += amount;
    return BAUTH_OK;
}

/* Sequence, then rate. A sequence that passes is marked used only after the
 * rate bucket also admits the intent: a rate refusal leaves the number free. */
static BreakAuthVerdict admit(AuthSession *s, u64 sequence, u64 now_us) {
    BreakReplayResult r;
    u64 now_ms = now_us / 1000u;
    if (sequence == 0u) {
        return BAUTH_DENIED_INVALID;
    }
    if (s->window.highest != 0u && sequence > s->window.highest &&
        sequence - s->window.highest > BREAK_AUTHORITY_MAX_GAP) {
        return BAUTH_DENIED_GAP;
    }
    r = break_replay_window_check(&s->window, sequence);
    if (r == BREAK_REPLAY_DUPLICATE || r == BREAK_REPLAY_TOO_OLD) {
        return BAUTH_DENIED_REPLAY;
    }
    if (r != BREAK_REPLAY_OK) {
        return BAUTH_DENIED_INVALID;
    }
    if (s->rate.msg_per_sec == 0u) {
        if (!break_msg_rate_init(&s->rate, BREAK_AUTHORITY_RATE_PER_SEC,
                                 BREAK_AUTHORITY_RATE_BURST, 1000000u, 1000000u, now_ms)) {
            return BAUTH_DENIED_INVALID;
        }
    }
    if (break_msg_rate_admit(&s->rate, 1u, now_ms) != BREAK_MSG_RATE_OK) {
        return BAUTH_DENIED_RATE;
    }
    (void)break_replay_window_check_and_mark(&s->window, sequence);
    return BAUTH_OK;
}

BreakAuthVerdict break_authority_intent_spend(BreakAuthority *a, u64 session_id, u64 sequence,
                                              u32 item_id, u32 qty, u64 now_us) {
    AuthSession *s;
    BreakAuthVerdict v;
    i64 price, cost;
    if (a == NULL) {
        return BAUTH_DENIED_INVALID;
    }
    s = find(a, session_id);
    if (s == NULL) {
        return BAUTH_DENIED_NO_SESSION;
    }
    v = admit(s, sequence, now_us);
    if (v != BAUTH_OK) {
        return v;
    }
    if (qty == 0u || qty > BREAK_AUTHORITY_MAX_QTY) {
        return BAUTH_DENIED_LIMIT;
    }
    price = break_authority_item_price(a, item_id);
    if (price == 0) {
        return BAUTH_DENIED_INVALID;
    }
    if (price > INT64_MAX / (i64)qty) {
        return BAUTH_DENIED_INVALID; /* price * qty would wrap */
    }
    cost = price * (i64)qty;
    if (cost > s->balance) {
        return BAUTH_DENIED_FUNDS;
    }
    if (s->items[item_id] > UINT32_MAX - qty) {
        return BAUTH_DENIED_LIMIT;
    }
    s->balance -= cost;
    s->items[item_id] += qty;
    return BAUTH_OK;
}

BreakAuthVerdict break_authority_intent_attack(BreakAuthority *a, u64 session_id, u64 sequence,
                                               u64 target_session, u64 now_us) {
    AuthSession *s, *t;
    BreakAuthVerdict v;
    if (a == NULL) {
        return BAUTH_DENIED_INVALID;
    }
    s = find(a, session_id);
    if (s == NULL) {
        return BAUTH_DENIED_NO_SESSION;
    }
    v = admit(s, sequence, now_us);
    if (v != BAUTH_OK) {
        return v;
    }
    if (target_session == session_id || s->health <= 0) {
        return BAUTH_DENIED_INVALID;
    }
    t = find(a, target_session);
    if (t == NULL) {
        return BAUTH_DENIED_NO_SESSION;
    }
    if (t->health <= 0) {
        return BAUTH_DENIED_INVALID;
    }
    t->health -= BREAK_AUTHORITY_ATTACK_DAMAGE;
    if (t->health < 0) {
        t->health = 0;
    }
    return BAUTH_OK;
}

static u64 rd64(const u8 *p) {
    u64 v = 0u;
    for (int i = 7; i >= 0; i--) {
        v = (v << 8) | p[i];
    }
    return v;
}

static u32 rd32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

bool break_authority_decode_intent(const u8 *p, usize n, BreakAuthIntent *out) {
    if (p == NULL || out == NULL || n != 17u) {
        return false;
    }
    memset(out, 0, sizeof(*out));
    out->kind = p[0];
    out->sequence = rd64(p + 1);
    if (out->sequence == 0u) {
        return false;
    }
    if (p[0] == BREAK_AUTH_INTENT_SPEND) {
        out->item_id = rd32(p + 9);
        out->qty = rd32(p + 13);
        return true;
    }
    if (p[0] == BREAK_AUTH_INTENT_ATTACK) {
        out->target_session = rd64(p + 9);
        return true;
    }
    return false;
}

BreakAuthVerdict break_authority_apply(BreakAuthority *a, u64 session_id,
                                       const BreakAuthIntent *intent, u64 now_us) {
    if (a == NULL || intent == NULL) {
        return BAUTH_DENIED_INVALID;
    }
    if (intent->kind == BREAK_AUTH_INTENT_SPEND) {
        return break_authority_intent_spend(a, session_id, intent->sequence, intent->item_id,
                                            intent->qty, now_us);
    }
    if (intent->kind == BREAK_AUTH_INTENT_ATTACK) {
        return break_authority_intent_attack(a, session_id, intent->sequence,
                                             intent->target_session, now_us);
    }
    return BAUTH_DENIED_INVALID;
}
