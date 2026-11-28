#include "network/break_identity_rate.h"

#include <stdlib.h>
#include <string.h>

typedef struct BreakIdentityRateSlot {
    u8 identity[8];
    bool used;
    u64 last_ms;
    BreakMsgRate rate;
} BreakIdentityRateSlot;

struct BreakIdentityRate {
    BreakIdentityRateConfig config;
    BreakIdentityRateSlot *slots;
    size_t count;
    u64 denied;
};

BreakIdentityRate *break_identity_rate_create(const BreakIdentityRateConfig *config)
{
    BreakIdentityRate *rate;
    BreakMsgRate probe;
    if (config == NULL || config->max_identities == 0u ||
        config->max_identities > BREAK_IDENTITY_RATE_MAX_IDENTITIES ||
        !break_msg_rate_init(&probe, config->msg_per_sec, config->msg_burst,
                             config->byte_per_sec, config->byte_burst, 0u)) {
        return NULL;
    }
    rate = (BreakIdentityRate *)calloc(1u, sizeof(*rate));
    if (rate == NULL) return NULL;
    rate->slots = (BreakIdentityRateSlot *)calloc(config->max_identities,
                                                  sizeof(*rate->slots));
    if (rate->slots == NULL) {
        free(rate);
        return NULL;
    }
    rate->config = *config;
    return rate;
}

void break_identity_rate_destroy(BreakIdentityRate *rate)
{
    if (rate == NULL) return;
    free(rate->slots);
    free(rate);
}

/* The slot of `identity`, a free or idle slot claimed for it, or NULL when
 * every slot holds an identity active within idle_ms. */
static BreakIdentityRateSlot *break_identity_rate_slot(BreakIdentityRate *rate,
                                                       const u8 identity[8],
                                                       u64 now_ms)
{
    BreakIdentityRateSlot *free_slot = NULL;
    BreakIdentityRateSlot *idle_slot = NULL;
    const BreakIdentityRateConfig *c = &rate->config;
    u32 i;
    for (i = 0u; i < c->max_identities; i++) {
        BreakIdentityRateSlot *slot = &rate->slots[i];
        if (!slot->used) {
            if (free_slot == NULL) free_slot = slot;
            continue;
        }
        if (memcmp(slot->identity, identity, 8u) == 0) return slot;
        if (idle_slot == NULL && now_ms >= slot->last_ms &&
            now_ms - slot->last_ms >= c->idle_ms) {
            idle_slot = slot;
        }
    }
    if (free_slot == NULL) free_slot = idle_slot;
    if (free_slot == NULL) return NULL;
    if (!free_slot->used) rate->count++;
    free_slot->used = true;
    memcpy(free_slot->identity, identity, 8u);
    (void)break_msg_rate_init(&free_slot->rate, c->msg_per_sec, c->msg_burst,
                              c->byte_per_sec, c->byte_burst, now_ms);
    return free_slot;
}

BreakMsgRateResult break_identity_rate_admit(BreakIdentityRate *rate,
                                             const u8 identity[8], u32 bytes,
                                             u64 now_ms)
{
    BreakIdentityRateSlot *slot;
    BreakMsgRateResult result;
    if (rate == NULL || identity == NULL) return BREAK_MSG_RATE_INVALID;
    slot = break_identity_rate_slot(rate, identity, now_ms);
    if (slot == NULL) {
        rate->denied++;
        return BREAK_IDENTITY_RATE_FULL;
    }
    slot->last_ms = now_ms;
    result = break_msg_rate_admit(&slot->rate, bytes, now_ms);
    if (result != BREAK_MSG_RATE_OK) rate->denied++;
    return result;
}

size_t break_identity_rate_count(const BreakIdentityRate *rate)
{
    return rate != NULL ? rate->count : 0u;
}

u64 break_identity_rate_denied(const BreakIdentityRate *rate)
{
    return rate != NULL ? rate->denied : 0u;
}
