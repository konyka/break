#include "test_framework.h"
#include <network/break_online_aspect.h>

#include <math.h>
#include <stdint.h>
#include <string.h>

static BreakAspectStore *make_store(u32 max_objects)
{
    BreakAspectStoreConfig config;
    BreakAspectStore *store = NULL;
    memset(&config, 0, sizeof(config));
    config.max_objects = max_objects;
    config.max_value_bytes = 16u;
    config.max_packet_bytes = 256u;
    if (break_aspect_store_create(&config, &store) != BREAK_RUNTIME_OK) return NULL;
    return store;
}

static bool register_defaults(BreakAspectStore *store)
{
    const BreakAspectSchema schemas[] = {
        {1u, 1u, BREAK_ASPECT_F32, 4u},
        {2u, 1u, BREAK_ASPECT_U32, 4u},
        {3u, 1u, BREAK_ASPECT_BYTES, 16u},
        {4u, 1u, BREAK_ASPECT_I32, 4u}
    };
    usize i;
    for (i = 0u; i < sizeof(schemas) / sizeof(schemas[0]); ++i) {
        if (break_aspect_schema_register(store, &schemas[i]) != BREAK_RUNTIME_OK) return false;
    }
    return true;
}

typedef struct AspectPair {
    BreakAspectStore *authoritative;
    BreakAspectStore *remote;
    BreakOnlineHandle object;
} AspectPair;

static bool make_pair(AspectPair *pair)
{
    memset(pair, 0, sizeof(*pair));
    pair->authoritative = make_store(2u);
    pair->remote = make_store(2u);
    if (!pair->authoritative || !pair->remote ||
        !register_defaults(pair->authoritative) ||
        !register_defaults(pair->remote) ||
        break_aspect_object_create(pair->authoritative, &pair->object) != BREAK_RUNTIME_OK ||
        break_aspect_object_adopt(pair->remote, pair->object) != BREAK_RUNTIME_OK) return false;
    return true;
}

static void destroy_pair(AspectPair *pair)
{
    break_aspect_store_destroy(pair->authoritative);
    break_aspect_store_destroy(pair->remote);
}

TEST(aspect_health_delta_has_hand_derived_mask_and_varint)
{
    AspectPair pair;
    u8 health[64];
    u8 baseline[256];
    usize health_size = 0u;
    usize baseline_size = 0u;
    u32 health_value = 0u;
    f32 position = 0.0f;
    u8 name[8];
    u32 name_size = 0u;
    ASSERT_TRUE(make_pair(&pair));
    ASSERT_EQ(break_aspect_set_u32(pair.authoritative, pair.object, 2u, 300u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_object_revision(pair.authoritative, pair.object), 1u);
    ASSERT_EQ(break_aspect_encode(pair.authoritative, pair.object, UINT64_C(1) << 1u,
                                  BREAK_ASPECT_DIRTY, health, sizeof(health), &health_size),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(health_size, 25u);
    ASSERT_TRUE(memcmp(health, "BRA1", 4u) == 0);
    ASSERT_EQ(health[20], 1u);
    ASSERT_EQ(health[21], BREAK_ASPECT_DIRTY);
    ASSERT_EQ(health[22], 2u);
    ASSERT_EQ(health[23], 0xacu);
    ASSERT_EQ(health[24], 0x02u);
    ASSERT_EQ(break_aspect_set_f32(pair.authoritative, pair.object, 1u, 1.5f),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_set_bytes(pair.authoritative, pair.object, 3u, "abc", 3u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_encode(pair.authoritative, pair.object,
                                  break_aspect_active_mask(pair.authoritative, pair.object),
                                  BREAK_ASPECT_BASELINE,
                                  baseline, sizeof(baseline), &baseline_size),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(baseline_size > health_size);
    ASSERT_EQ(break_aspect_apply(pair.remote, baseline, baseline_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_get_u32(pair.remote, pair.object, 2u, &health_value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(health_value, 300u);
    ASSERT_EQ(break_aspect_get_f32(pair.remote, pair.object, 1u, &position),
              BREAK_RUNTIME_OK);
    ASSERT_FLOAT_EQ(position, 1.5f, 0.0001f);
    ASSERT_EQ(break_aspect_get_bytes(pair.remote, pair.object, 3u,
                                     name, sizeof(name), &name_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(name_size, 3u);
    ASSERT_TRUE(memcmp(name, "abc", 3u) == 0);
    ASSERT_EQ(break_aspect_set_u32(pair.authoritative, pair.object, 2u, 7u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_encode(pair.authoritative, pair.object, UINT64_C(1) << 1u,
                                  BREAK_ASPECT_DIRTY, health, sizeof(health), &health_size),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_apply(pair.remote, health, health_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_get_u32(pair.remote, pair.object, 2u, &health_value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(health_value, 7u);
    ASSERT_EQ(break_aspect_get_bytes(pair.remote, pair.object, 3u,
                                     name, sizeof(name), &name_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(name_size, 3u);
    ASSERT_TRUE(memcmp(name, "abc", 3u) == 0);
    destroy_pair(&pair);
}

TEST(aspect_malformed_delta_never_partially_mutates_remote)
{
    AspectPair pair;
    u8 baseline[256];
    u8 delta[64];
    usize baseline_size = 0u;
    usize delta_size = 0u;
    u32 health = 0u;
    ASSERT_TRUE(make_pair(&pair));
    ASSERT_EQ(break_aspect_set_u32(pair.authoritative, pair.object, 2u, 300u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_set_bytes(pair.authoritative, pair.object, 3u, "abc", 3u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_encode(pair.authoritative, pair.object,
                                  break_aspect_active_mask(pair.authoritative, pair.object),
                                  BREAK_ASPECT_BASELINE,
                                  baseline, sizeof(baseline), &baseline_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_apply(pair.remote, baseline, baseline_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_set_u32(pair.authoritative, pair.object, 2u, 7u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_encode(pair.authoritative, pair.object, UINT64_C(1) << 1u,
                                  BREAK_ASPECT_DIRTY, delta, sizeof(delta), &delta_size),
              BREAK_RUNTIME_OK);
    delta[4] ^= 1u;
    ASSERT_EQ(break_aspect_apply(pair.remote, delta, delta_size), BREAK_RUNTIME_INVALID);
    delta[4] ^= 1u;
    ASSERT_EQ(break_aspect_apply(pair.remote, delta, delta_size + 1u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_aspect_apply(pair.remote, delta, delta_size - 1u), BREAK_RUNTIME_INVALID);
    delta[22] = 16u;
    ASSERT_EQ(break_aspect_apply(pair.remote, delta, delta_size), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_aspect_get_u32(pair.remote, pair.object, 2u, &health), BREAK_RUNTIME_OK);
    ASSERT_EQ(health, 300u);
    ASSERT_EQ(break_aspect_object_revision(pair.remote, pair.object), 2u);
    destroy_pair(&pair);
}

TEST(aspect_stale_object_handle_cannot_access_reused_slot)
{
    BreakAspectStore *store = make_store(1u);
    BreakOnlineHandle first;
    BreakOnlineHandle second;
    BreakOnlineHandle extra;
    BreakAspectSchema late = {5u, 1u, BREAK_ASPECT_U32, 4u};
    ASSERT_NOT_NULL(store);
    ASSERT_TRUE(register_defaults(store));
    ASSERT_EQ(break_aspect_object_create(store, &first), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_object_create(store, &extra), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_aspect_schema_register(store, &late), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_aspect_set_u32(store, first, 2u, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_object_destroy(store, first), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_set_u32(store, first, 2u, 2u), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_aspect_object_create(store, &second), BREAK_RUNTIME_OK);
    ASSERT_EQ(first.index, second.index);
    ASSERT_NEQ(first.generation, second.generation);
    ASSERT_EQ(break_aspect_set_u32(store, first, 2u, 2u), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_aspect_set_u32(store, second, 2u, 2u), BREAK_RUNTIME_OK);
    break_aspect_store_destroy(store);
}

TEST(aspect_signed_float_bytes_and_same_value_rules)
{
    AspectPair pair;
    u8 packet[256];
    usize packet_size = 0u;
    i32 signed_value = 0;
    u32 health = 0u;
    u8 output[2];
    u32 output_size = 99u;
    ASSERT_TRUE(make_pair(&pair));
    ASSERT_EQ(break_aspect_set_i32(pair.authoritative, pair.object, 4u, -1234567),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_set_u32(pair.authoritative, pair.object, 2u, 9u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_set_bytes(pair.authoritative, pair.object, 3u, "xy", 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_encode(pair.authoritative, pair.object,
                                  break_aspect_active_mask(pair.authoritative, pair.object),
                                  BREAK_ASPECT_BASELINE,
                                  packet, sizeof(packet), &packet_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_apply(pair.remote, packet, packet_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_get_i32(pair.remote, pair.object, 4u, &signed_value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(signed_value, -1234567);
    ASSERT_EQ(break_aspect_set_f32(pair.authoritative, pair.object, 1u, NAN),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_aspect_set_bytes(pair.authoritative, pair.object, 3u,
                                     packet, 17u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_aspect_get_bytes(pair.remote, pair.object, 3u,
                                     output, sizeof(output), &output_size), BREAK_RUNTIME_OK);
    ASSERT_EQ(output_size, 2u);
    ASSERT_TRUE(memcmp(output, "xy", 2u) == 0);
    output_size = 99u;
    ASSERT_EQ(break_aspect_get_bytes(pair.remote, pair.object, 3u,
                                     output, 1u, &output_size), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(output_size, 99u);
    ASSERT_EQ(break_aspect_set_u32(pair.authoritative, pair.object, 2u, 9u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_object_revision(pair.authoritative, pair.object), 3u);
    ASSERT_EQ(break_aspect_get_u32(pair.remote, pair.object, 2u, &health), BREAK_RUNTIME_OK);
    ASSERT_EQ(health, 9u);
    destroy_pair(&pair);
}

TEST(aspect_schema_validation_and_output_capacity_are_atomic)
{
    BreakAspectStore *store = make_store(1u);
    BreakAspectSchema duplicate = {1u, 1u, BREAK_ASPECT_F32, 4u};
    BreakAspectSchema bad = {2u, 1u, BREAK_ASPECT_U32, 8u};
    BreakOnlineHandle object;
    u8 packet[4] = {1u, 2u, 3u, 4u};
    usize packet_size = 88u;
    ASSERT_NOT_NULL(store);
    ASSERT_TRUE(register_defaults(store));
    ASSERT_EQ(break_aspect_schema_register(store, &duplicate), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_aspect_schema_register(store, &bad), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_aspect_object_create(store, &object), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_set_u32(store, object, 2u, 300u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_encode(store, object, UINT64_C(1) << 1u,
                                  BREAK_ASPECT_DIRTY, packet, sizeof(packet), &packet_size),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(packet_size, 88u);
    ASSERT_EQ(packet[0], 1u);
    break_aspect_store_destroy(store);
}

TEST_MAIN_BEGIN()
    RUN_TEST(aspect_health_delta_has_hand_derived_mask_and_varint);
    RUN_TEST(aspect_malformed_delta_never_partially_mutates_remote);
    RUN_TEST(aspect_stale_object_handle_cannot_access_reused_slot);
    RUN_TEST(aspect_signed_float_bytes_and_same_value_rules);
    RUN_TEST(aspect_schema_validation_and_output_capacity_are_atomic);
TEST_MAIN_END()
