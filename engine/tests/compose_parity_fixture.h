#ifndef COMPOSE_PARITY_FIXTURE_H
#define COMPOSE_PARITY_FIXTURE_H

#include <myui/mycompose/my_compose_runtime.h>
#include <myui/mycompose/my_compose_store.h>
#include <myui/mycompose/my_compose_tree.h>

#include <stdbool.h>
#include <stdint.h>

#define COMPOSE_PARITY_INTENT_TYPE 41u
#define COMPOSE_PARITY_EVENT_TYPE 91u
#define COMPOSE_PARITY_EFFECT_TYPE 700u
#define COMPOSE_PARITY_AMOUNT 7u
#define COMPOSE_PARITY_DIFF_BYTES 16384u

typedef struct ComposeParityResult {
    MyComposeStatus status;
    uint32_t diff_frames;
    uint32_t diff_counts[2];
    uint32_t diff_size;
    char diff[COMPOSE_PARITY_DIFF_BYTES];
    uint32_t state_count;
    uint32_t effect_calls;
    uint32_t effect_type;
    uint32_t effect_payload_size;
    uint8_t effect_payload[4];
    int32_t property_value;
    uint32_t style_value;
    uint32_t event_type;
    uint32_t event_payload_size;
    uint8_t event_payload[4];
} ComposeParityResult;

#ifdef __cplusplus
extern "C" {
#endif

MyComposeStatus ComposeParityRunC(ComposeParityResult *result);
void ComposeParityCanonicalDiff(ComposeParityResult *result,
    const MyComposeDiff *diff);

#ifdef __cplusplus
}
#endif

#if defined(MY_COMPOSE_PARITY_FIXTURE_IMPLEMENTATION) && !defined(__cplusplus)

#include <stdio.h>
#include <string.h>

typedef struct ComposeParityCContext {
    ComposeParityResult *result;
} ComposeParityCContext;

static MyComposeNodeHandle ComposeParityZeroHandle(void) {
    MyComposeNodeHandle handle = {0u, 0u};
    return handle;
}

static MyComposeStatus ComposeParityAddNode(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle parent, const char *key, const char *type,
    MyComposeNodeHandle *out) {
    MyComposeNodeDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.parent = parent;
    desc.key = key;
    desc.type = type;
    return my_compose_tree_builder_node(builder, &desc, out);
}

static MyComposeStatus ComposeParityReduce(void *opaque,
    const MyComposeIntent *intent, const void *current, uint32_t current_size,
    void *candidate, uint32_t *candidate_size, MyComposeEffectBatch *batch) {
    const uint32_t *state = (const uint32_t *)current;
    uint32_t *next = (uint32_t *)candidate;
    uint32_t amount = 0u;
    (void)opaque;
    if (current_size != sizeof(*state) || *candidate_size != sizeof(*next) ||
        intent->type != COMPOSE_PARITY_INTENT_TYPE ||
        intent->payload_size != sizeof(amount) || intent->payload == NULL) {
        return MY_COMPOSE_INVALID;
    }
    memcpy(&amount, intent->payload, sizeof(amount));
    *next = *state + amount;
    return my_compose_effect_batch_append(batch, COMPOSE_PARITY_EFFECT_TYPE,
        &amount, (uint32_t)sizeof(amount));
}

static MyComposeStatus ComposeParityExecute(void *opaque,
    const MyComposeEffect *effect) {
    ComposeParityCContext *context = (ComposeParityCContext *)opaque;
    ComposeParityResult *result = context->result;
    result->effect_calls++;
    result->effect_type = effect->type;
    result->effect_payload_size = effect->payload_size;
    if (effect->payload_size != sizeof(result->effect_payload) ||
        effect->payload == NULL) {
        return MY_COMPOSE_INVALID;
    }
    memcpy(result->effect_payload, effect->payload,
        sizeof(result->effect_payload));
    return MY_COMPOSE_OK;
}

static MyComposeStatus ComposeParityProperty(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle owner, const char *name, MyComposeValue value) {
    return my_compose_tree_builder_property(builder, owner, name, &value);
}

static MyComposeStatus ComposeParityBuildC(MyComposeTreeBuilder *builder,
    uint32_t state, bool second, MyComposeNodeHandle *out_a) {
    MyComposeNodeHandle root;
    MyComposeNodeHandle row;
    MyComposeNodeHandle column;
    MyComposeNodeHandle stack;
    MyComposeNodeHandle a;
    MyComposeNodeHandle b;
    MyComposeValue value;
    MyComposeIntent event;
    uint32_t event_payload = state;
    MyComposeStatus status = my_compose_tree_builder_begin(builder);
    if (status != MY_COMPOSE_OK) return status;
    status = ComposeParityAddNode(builder, ComposeParityZeroHandle(), NULL,
        "@root", &root);
    if (status != MY_COMPOSE_OK) return status;
    status = ComposeParityAddNode(builder, root, "row", "@row", &row);
    if (status != MY_COMPOSE_OK) return status;
    status = ComposeParityAddNode(builder, row, "column", "@column", &column);
    if (status != MY_COMPOSE_OK) return status;
    status = ComposeParityAddNode(builder, column, "stack", "@stack", &stack);
    if (status != MY_COMPOSE_OK) return status;
    if (second) {
        status = ComposeParityAddNode(builder, stack, "b", "label", &b);
        if (status != MY_COMPOSE_OK) return status;
        status = ComposeParityAddNode(builder, stack, "a", "edit", &a);
    } else {
        status = ComposeParityAddNode(builder, stack, "a", "button", &a);
        if (status != MY_COMPOSE_OK) return status;
        status = ComposeParityAddNode(builder, stack, "b", "label", &b);
    }
    if (status != MY_COMPOSE_OK) return status;
    memset(&value, 0, sizeof(value));
    value.type = MY_COMPOSE_VALUE_INT32;
    value.as.int32_value = (int32_t)state;
    status = ComposeParityProperty(builder, a, "count", value);
    if (status != MY_COMPOSE_OK) return status;
    memset(&value, 0, sizeof(value));
    value.type = MY_COMPOSE_VALUE_COLOR;
    value.as.color = 0x11223344u;
    status = ComposeParityProperty(builder, a, "style:bg_color", value);
    if (status != MY_COMPOSE_OK) return status;
    memset(&event, 0, sizeof(event));
    event.type = COMPOSE_PARITY_EVENT_TYPE;
    event.payload_size = (uint32_t)sizeof(event_payload);
    event.payload = (const uint8_t *)&event_payload;
    status = my_compose_tree_builder_event(builder, a, "click", &event);
    if (status != MY_COMPOSE_OK) return status;
    status = my_compose_tree_builder_end(builder);
    if (status != MY_COMPOSE_OK) return status;
    status = my_compose_tree_builder_finalize(builder);
    if (status != MY_COMPOSE_OK) return status;
    *out_a = a;
    return MY_COMPOSE_OK;
}

void ComposeParityCanonicalDiff(ComposeParityResult *result,
    const MyComposeDiff *diff) {
    uint32_t i;
    if (result == NULL || diff == NULL || result->diff_frames >= 2u) return;
    result->diff_counts[result->diff_frames] = diff->count;
    result->diff_frames++;
    for (i = 0u; i < diff->count; ++i) {
        const MyComposeDiffOp *op = &diff->ops[i];
        int written = snprintf(result->diff + result->diff_size,
            COMPOSE_PARITY_DIFF_BYTES - result->diff_size,
            "%u:%u,%u,%u,%u,%u,%u,%u,%u,%s\n", result->diff_frames - 1u,
            (unsigned)op->type, (unsigned)op->node.index,
            (unsigned)op->node.generation, (unsigned)op->parent.index,
            (unsigned)op->parent.generation, (unsigned)op->from_index,
            (unsigned)op->to_index, op->on_event ? 1u : 0u,
            op->name != NULL ? op->name : "-");
        if (written < 0 || (uint32_t)written >=
            COMPOSE_PARITY_DIFF_BYTES - result->diff_size) {
            result->status = MY_COMPOSE_OVERLOAD;
            return;
        }
        result->diff_size += (uint32_t)written;
    }
}

MyComposeStatus ComposeParityRunC(ComposeParityResult *result) {
    uint32_t initial = 0u;
    uint32_t amount = COMPOSE_PARITY_AMOUNT;
    MyComposeIntent intent;
    MyComposeTreeBuilder *builder;
    MyComposeStore *store;
    ComposeParityCContext context;
    MyComposeNodeHandle a = {0u, 0u};
    MyComposeValue property;
    MyComposeIntent event;
    const void *state = NULL;
    uint32_t state_size = 0u;
    if (result == NULL) return MY_COMPOSE_INVALID;
    memset(result, 0, sizeof(*result));
    context.result = result;
    builder = my_compose_tree_builder_create();
    store = my_compose_store_create(&initial, (uint32_t)sizeof(initial), NULL,
        NULL, ComposeParityReduce, &context, ComposeParityExecute);
    if (builder == NULL || store == NULL) {
        my_compose_tree_builder_destroy(builder);
        my_compose_store_destroy(store);
        return MY_COMPOSE_OVERLOAD;
    }
    result->status = ComposeParityBuildC(builder, initial, false, &a);
    if (result->status == MY_COMPOSE_OK) {
        ComposeParityCanonicalDiff(result, my_compose_tree_builder_diff(builder));
        memset(&intent, 0, sizeof(intent));
        intent.type = COMPOSE_PARITY_INTENT_TYPE;
        intent.payload_size = (uint32_t)sizeof(amount);
        intent.payload = (const uint8_t *)&amount;
        result->status = my_compose_store_dispatch(store, &intent);
    }
    if (result->status == MY_COMPOSE_OK) {
        result->status = my_compose_store_reduce(store);
    }
    if (result->status == MY_COMPOSE_OK) {
        result->status = my_compose_store_dispatch_effects(store);
    }
    if (result->status == MY_COMPOSE_OK) {
        result->status = my_compose_store_state(store, &state, &state_size);
    }
    if (result->status == MY_COMPOSE_OK && state_size == sizeof(initial)) {
        result->state_count = *(const uint32_t *)state;
        result->status = ComposeParityBuildC(builder, result->state_count, true,
            &a);
    } else if (result->status == MY_COMPOSE_OK) {
        result->status = MY_COMPOSE_FAILED;
    }
    if (result->status == MY_COMPOSE_OK) {
        ComposeParityCanonicalDiff(result, my_compose_tree_builder_diff(builder));
        result->status = my_compose_tree_builder_get_property(builder, a,
            "count", &property);
    }
    if (result->status == MY_COMPOSE_OK) {
        result->property_value = property.as.int32_value;
        result->status = my_compose_tree_builder_get_property(builder, a,
            "style:bg_color", &property);
    }
    if (result->status == MY_COMPOSE_OK) {
        result->style_value = property.as.color;
        result->status = my_compose_tree_builder_get_event(builder, a, "click",
            &event);
    }
    if (result->status == MY_COMPOSE_OK) {
        result->event_type = event.type;
        result->event_payload_size = event.payload_size;
        if (event.payload_size != sizeof(result->event_payload) ||
            event.payload == NULL) {
            result->status = MY_COMPOSE_INVALID;
        } else {
            memcpy(result->event_payload, event.payload,
                sizeof(result->event_payload));
        }
    }
    my_compose_tree_builder_destroy(builder);
    my_compose_store_destroy(store);
    return result->status;
}

#if defined(MY_COMPOSE_PARITY_FIXTURE_MAIN)
#include "test_framework.h"

TEST(c_fixture_produces_independent_canonical_results) {
    ComposeParityResult result;
    uint32_t payload = 0u;
    ASSERT_EQ(ComposeParityRunC(&result), MY_COMPOSE_OK);
    ASSERT_EQ(result.diff_frames, 2u);
    ASSERT_EQ(result.diff_counts[0], 6u);
    ASSERT_EQ(result.diff_counts[1], 2u);
    ASSERT_EQ(result.state_count, COMPOSE_PARITY_AMOUNT);
    ASSERT_EQ(result.effect_calls, 1u);
    ASSERT_EQ(result.effect_type, COMPOSE_PARITY_EFFECT_TYPE);
    ASSERT_EQ(result.effect_payload_size, 4u);
    memcpy(&payload, result.effect_payload, sizeof(payload));
    ASSERT_EQ(payload, COMPOSE_PARITY_AMOUNT);
    ASSERT_EQ(result.property_value, (int32_t)COMPOSE_PARITY_AMOUNT);
    ASSERT_EQ(result.style_value, 0x11223344u);
    ASSERT_EQ(result.event_type, COMPOSE_PARITY_EVENT_TYPE);
    memcpy(&payload, result.event_payload, sizeof(payload));
    ASSERT_EQ(payload, COMPOSE_PARITY_AMOUNT);
    ASSERT_NOT_NULL(strstr(result.diff, "0:0,0,1,0,0,4294967295,0,0,-\n"));
    ASSERT_NOT_NULL(strstr(result.diff, "1:3,"));
    ASSERT_NOT_NULL(strstr(result.diff, "1:0,"));
}

int main(void) {
    RUN_TEST(c_fixture_produces_independent_canonical_results);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
        g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
#endif

#endif
#endif
