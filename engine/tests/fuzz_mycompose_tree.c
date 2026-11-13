/* Length-prefixed mutation fuzzer for the Compose tree builder.
 *
 * The stream is a sequence of records: u8 op, u16 length, payload. A record
 * that runs past the buffer is a truncation and must return a status without
 * reading further. Duplicate keys, depth past MY_COMPOSE_MAX_DEPTH and a node
 * count past MY_COMPOSE_MAX_NODES must also return a status. Nothing here may
 * read or write out of bounds or loop without consuming input.
 *
 * argv[1] = iterations (default 2000), argv[2] = seed. */
#include <myui/mycompose/my_compose_tree.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long rng_state = 0xC0FFEEu;
static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

enum { OP_BEGIN = 1, OP_NODE = 2, OP_PROPERTY = 3, OP_EVENT = 4, OP_END = 5,
       OP_FINALIZE = 6, OP_REMEMBER = 7, OP_RESET = 8 };

static uint32_t read_u16(const uint8_t *p) {
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8);
}

/* Apply one record. Returns how many bytes it consumed, 0 when the record is
 * truncated, or (uint32_t)-1 when the builder itself fails closed. */
static uint32_t apply_record(MyComposeTreeBuilder *builder, const uint8_t *data,
    uint32_t size, MyComposeNodeHandle *stack, uint32_t *depth) {
    uint32_t length;
    MyComposeStatus status = MY_COMPOSE_OK;
    if (size < 3u) return 0u;
    length = read_u16(data + 1u);
    if (length > size - 3u) return 0u;
    switch (data[0]) {
    case OP_BEGIN:
        status = my_compose_tree_builder_begin(builder);
        *depth = 0u;
        break;
    case OP_NODE: {
        char key[MY_COMPOSE_KEY_BYTES + 8u];
        char type[MY_COMPOSE_TYPE_BYTES + 8u];
        MyComposeNodeDesc desc;
        MyComposeNodeHandle out;
        uint32_t key_len = length > 0u ? data[3] % (sizeof(key)) : 0u;
        uint32_t type_len = length > 1u ? data[4] % (sizeof(type)) : 0u;
        memset(&desc, 0, sizeof(desc));
        memset(key, 'k', sizeof(key));
        memset(type, 't', sizeof(type));
        key[key_len < sizeof(key) ? key_len : sizeof(key) - 1u] = '\0';
        type[type_len < sizeof(type) ? type_len : sizeof(type) - 1u] = '\0';
        if (length > 2u && *depth > 0u) {
            uint32_t pick = data[5] % *depth;
            desc.parent = stack[pick];
            desc.key = key;
        }
        desc.type = type_len > 0u ? type : "";
        status = my_compose_tree_builder_node(builder, &desc, &out);
        if (status == MY_COMPOSE_OK && *depth < MY_COMPOSE_MAX_DEPTH + 4u) {
            stack[(*depth)++] = out;
        }
        break;
    }
    case OP_PROPERTY:
    case OP_EVENT:
        if (*depth > 0u && length > 0u) {
            char name[MY_COMPOSE_NAME_BYTES + 4u];
            uint32_t name_len = data[3] % sizeof(name);
            MyComposeValue value;
            memset(name, 'n', sizeof(name));
            name[name_len] = '\0';
            memset(&value, 0, sizeof(value));
            value.type = MY_COMPOSE_VALUE_INT32;
            value.as.int32_value = length > 1u ? (int32_t)data[4] : 0;
            status = data[0] == OP_PROPERTY
                ? my_compose_tree_builder_property(builder, stack[*depth - 1u],
                    name_len > 0u ? name : "", &value)
                : my_compose_tree_builder_event(builder, stack[*depth - 1u],
                    name_len > 0u ? name : "", NULL);
        }
        break;
    case OP_END:
        status = my_compose_tree_builder_end(builder);
        break;
    case OP_FINALIZE:
        status = my_compose_tree_builder_finalize(builder);
        break;
    case OP_REMEMBER:
        if (*depth > 0u) {
            MyComposeRememberOps ops;
            void *slot = NULL;
            uint32_t bytes = length > 1u ? (uint32_t)data[4] : 0u;
            memset(&ops, 0, sizeof(ops));
            status = my_compose_tree_builder_remember(builder, stack[*depth - 1u],
                length % MY_COMPOSE_REMEMBER_SLOTS_PER_NODE,
                length > 2u ? (uint64_t)data[5] : 1u,
                bytes % (MY_COMPOSE_REMEMBER_BYTES + 1u),
                8u, &ops, &slot);
        }
        break;
    case OP_RESET:
        my_compose_tree_builder_destroy(builder);
        return (uint32_t)-2;
    default:
        break;
    }
    (void)status;
    return 3u + length;
}

static int run_stream(const uint8_t *data, uint32_t size) {
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    MyComposeNodeHandle stack[MY_COMPOSE_MAX_DEPTH + 4u];
    uint32_t depth = 0u;
    uint32_t offset = 0u;
    if (builder == NULL) return 2;
    memset(stack, 0, sizeof(stack));
    while (offset < size) {
        uint32_t used = apply_record(builder, data + offset, size - offset,
            stack, &depth);
        if (used == 0u) break;
        if (used == (uint32_t)-2) {
            builder = my_compose_tree_builder_create();
            depth = 0u;
            if (builder == NULL) return 2;
            used = 3u + read_u16(data + offset + 1u);
        }
        offset += used;
    }
    my_compose_tree_builder_destroy(builder);
    return 0;
}

/* A known-good stream must succeed, so the fuzzer is not only hitting
 * rejection paths. */
static int sanity(void) {
    uint8_t stream[64];
    uint32_t n = 0u;
    MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
    MyComposeNodeHandle root;
    MyComposeNodeDesc desc;
    MyComposeStatus status;
    if (builder == NULL) return 2;
    memset(&desc, 0, sizeof(desc));
    desc.type = "@root";
    status = my_compose_tree_builder_begin(builder);
    if (status == MY_COMPOSE_OK) status = my_compose_tree_builder_node(builder, &desc, &root);
    if (status == MY_COMPOSE_OK) status = my_compose_tree_builder_end(builder);
    if (status == MY_COMPOSE_OK) status = my_compose_tree_builder_finalize(builder);
    my_compose_tree_builder_destroy(builder);
    if (status != MY_COMPOSE_OK) {
        fprintf(stderr, "fuzz_mycompose_tree: sanity stream failed %d\n", (int)status);
        return 2;
    }
    stream[n++] = OP_BEGIN; stream[n++] = 0u; stream[n++] = 0u;
    stream[n++] = OP_NODE; stream[n++] = 2u; stream[n++] = 0u;
    stream[n++] = 0u; stream[n++] = 4u;
    return run_stream(stream, n);
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 2000u;
    unsigned it;
    uint8_t stream[4096];
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10);
    if (sanity() != 0) return 2;
    for (it = 0u; it < iters; ++it) {
        uint32_t size = 0u;
        unsigned records = 1u + rnd() % 64u;
        unsigned r;
        for (r = 0u; r < records && size + 8u < sizeof(stream); ++r) {
            uint32_t length = rnd() % 96u;
            stream[size++] = (uint8_t)(1u + rnd() % 8u);
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
    printf("fuzz_mycompose_tree: %u iterations seed ok\n", iters);
    return 0;
}
