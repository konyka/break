/* Length-prefixed mutation fuzzer for the Compose store intent path.
 *
 * Records: u8 op, u16 length, payload. Truncated records stop the stream.
 * Repeated intent keys, payloads past the message cap and more intents than
 * the FIFO holds must return a status. The reducer and effect executor here
 * only touch the bytes the store handed them.
 *
 * argv[1] = iterations (default 2000), argv[2] = seed. */
#include <myui/mycompose/my_compose_store.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0xA11CEu;
static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

enum { OP_DISPATCH = 1, OP_REDUCE = 2, OP_EFFECTS = 3, OP_COMPLETE = 4 };

typedef struct FuzzState {
    uint32_t clicks;
    uint32_t reduced;
    uint8_t last[16];
} FuzzState;

static MyComposeStatus reduce(void *context, const MyComposeIntent *intent,
    const void *current, uint32_t current_size, void *candidate,
    uint32_t *candidate_size, MyComposeEffectBatch *batch) {
    FuzzState next;
    uint32_t *calls = (uint32_t *)context;
    if (calls != NULL) (*calls)++;
    if (intent == NULL || current == NULL || candidate == NULL ||
        candidate_size == NULL || current_size != sizeof(FuzzState) ||
        *candidate_size < sizeof(FuzzState)) {
        return MY_COMPOSE_INVALID;
    }
    memcpy(&next, current, sizeof(next));
    next.reduced++;
    if (intent->type == 1u) next.clicks++;
    if (intent->payload_size > 0u && intent->payload != NULL) {
        uint32_t n = intent->payload_size < sizeof(next.last)
            ? intent->payload_size : (uint32_t)sizeof(next.last);
        memcpy(next.last, intent->payload, n);
    }
    memcpy(candidate, &next, sizeof(next));
    *candidate_size = (uint32_t)sizeof(next);
    if (batch != NULL && intent->type == 2u) {
        uint8_t payload[4] = {1u, 2u, 3u, 4u};
        MyComposeStatus status = my_compose_effect_batch_append(batch, 9u,
            payload, sizeof(payload));
        if (status != MY_COMPOSE_OK) return status;
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus execute(void *context, const MyComposeEffect *effect) {
    uint32_t *calls = (uint32_t *)context;
    if (calls != NULL) (*calls)++;
    if (effect == NULL) return MY_COMPOSE_INVALID;
    if (effect->payload_size == 1u) return MY_COMPOSE_PENDING;
    return MY_COMPOSE_OK;
}

static int run_stream(const uint8_t *data, uint32_t size) {
    FuzzState initial;
    MyComposeStore *store;
    uint32_t reduce_calls = 0u;
    uint32_t effect_calls = 0u;
    uint32_t offset = 0u;
    memset(&initial, 0, sizeof(initial));
    store = my_compose_store_create(&initial, (uint32_t)sizeof(initial), NULL,
        &reduce_calls, reduce, &effect_calls, execute);
    if (store == NULL) return 2;
    while (offset < size) {
        uint32_t length;
        if (size - offset < 3u) break;
        length = (uint32_t)data[offset + 1u] | ((uint32_t)data[offset + 2u] << 8);
        if (length > size - offset - 3u) break;
        switch (data[offset]) {
        case OP_DISPATCH: {
            MyComposeIntent intent;
            uint8_t payload[MY_COMPOSE_MESSAGE_BYTES + 8u];
            memset(&intent, 0, sizeof(intent));
            memset(payload, 0, sizeof(payload));
            intent.type = length > 0u ? data[offset + 3u] : 0u;
            intent.payload_size = length > 1u
                ? (uint32_t)data[offset + 4u] * 4u : 0u;
            if (intent.payload_size > sizeof(payload)) {
                intent.payload_size = (uint32_t)sizeof(payload);
            }
            if (length > 5u) {
                uint32_t copy = length - 5u;
                if (copy > intent.payload_size) copy = intent.payload_size;
                memcpy(payload, data + offset + 8u, copy);
            }
            intent.payload = intent.payload_size > 0u ? payload : NULL;
            (void)my_compose_store_dispatch(store, &intent);
            break;
        }
        case OP_REDUCE:
            (void)my_compose_store_reduce(store);
            break;
        case OP_EFFECTS:
            (void)my_compose_store_dispatch_effects(store);
            break;
        case OP_COMPLETE:
            (void)my_compose_store_reap(store);
            break;
        default:
            break;
        }
        offset += 3u + length;
    }
    my_compose_store_destroy(store);
    return 0;
}

static int sanity(void) {
    FuzzState initial;
    const void *raw = NULL;
    uint32_t size = 0u;
    MyComposeStore *store;
    MyComposeIntent intent;
    memset(&initial, 0, sizeof(initial));
    memset(&intent, 0, sizeof(intent));
    intent.type = 1u;
    store = my_compose_store_create(&initial, (uint32_t)sizeof(initial), NULL,
        NULL, reduce, NULL, execute);
    if (store == NULL) return 2;
    if (my_compose_store_dispatch(store, &intent) != MY_COMPOSE_OK ||
        my_compose_store_reduce(store) != MY_COMPOSE_OK ||
        my_compose_store_state(store, &raw, &size) != MY_COMPOSE_OK ||
        size != sizeof(FuzzState) ||
        ((const FuzzState *)raw)->clicks != 1u) {
        fprintf(stderr, "fuzz_mycompose_intent: sanity dispatch failed\n");
        my_compose_store_destroy(store);
        return 2;
    }
    my_compose_store_destroy(store);
    return 0;
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 2000u;
    unsigned it;
    uint8_t stream[8192];
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10);
    if (sanity() != 0) return 2;
    for (it = 0u; it < iters; ++it) {
        uint32_t size = 0u;
        unsigned records = 1u + rnd() % 96u;
        unsigned r;
        for (r = 0u; r < records && size + 8u < sizeof(stream); ++r) {
            uint32_t length = rnd() % 320u;
            stream[size++] = (uint8_t)(1u + rnd() % 4u);
            stream[size++] = (uint8_t)(length & 0xFFu);
            stream[size++] = (uint8_t)((length >> 8) & 0xFFu);
            while (length > 0u && size < sizeof(stream)) {
                stream[size++] = (uint8_t)(rnd() & 0xFFu);
                length--;
            }
        }
        if (rnd() % 5u == 0u && size > 4u) size = (uint32_t)(rnd() % size);
        if (run_stream(stream, size) != 0) return 2;
    }
    printf("fuzz_mycompose_intent: %u iterations seed ok\n", iters);
    return 0;
}
