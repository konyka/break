#include "test_framework.h"
#include <animation/anim_compression.h>

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc;
    RHIBuffer buffer = {.index = 1, .generation = 1};
    return buffer;
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buffer) {
    (void)dev; (void)buffer;
}
void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buffer, usize offset,
                              const void *data, usize size) {
    (void)dev; (void)buffer; (void)offset; (void)data; (void)size;
}
u32 rhi_frame_index(RHIDevice *dev) { (void)dev; return 0u; }

static AnimClip g_source;
static AnimClip g_decoded;
static u8 g_bytes[ANIM_CODEC_MAX_BYTES];

static u16 test_read_u16(const u8 *p) {
    return (u16)((u16)p[0] | ((u16)p[1] << 8));
}

static u32 test_read_u32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static void test_write_u16(u8 *p, u16 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8);
}

static void test_write_u32(u8 *p, u32 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8);
    p[2] = (u8)(value >> 16);
    p[3] = (u8)(value >> 24);
}

static void test_write_f32(u8 *p, f32 value) {
    u32 bits;
    memcpy(&bits, &value, sizeof(bits));
    test_write_u32(p, bits);
}

static u32 test_crc32_update(u32 crc, const u8 *data, usize size) {
    for (usize i = 0; i < size; ++i) {
        crc ^= data[i];
        for (u32 bit = 0; bit < 8u; ++bit)
            crc = (crc >> 1) ^ (0xEDB88320u & (u32)-(i32)(crc & 1u));
    }
    return crc;
}

static void test_repair_crc(u8 *bytes) {
    usize size = test_read_u32(bytes + 8);
    u32 crc = test_crc32_update(UINT32_MAX, bytes, 28u);
    crc = test_crc32_update(crc, bytes + ANIM_CODEC_HEADER_BYTES,
                            size - ANIM_CODEC_HEADER_BYTES);
    test_write_u32(bytes + 28, ~crc);
}

static usize test_channel_offset(const u8 *bytes, u32 wanted) {
    usize offset = ANIM_CODEC_HEADER_BYTES;
    for (u32 c = 0; c < wanted; ++c) {
        u32 components = bytes[offset + 2] == ANIM_PATH_ROTATION ? 4u : 3u;
        u32 keys = test_read_u16(bytes + offset + 4);
        offset += ANIM_CODEC_CHANNEL_HEADER_BYTES + keys * (2u + components * 2u);
    }
    return offset;
}

static f32 quaternion_angle(const f32 *a, const f32 *b) {
    f32 dot = fabsf(a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
    if (dot > 1.0f) dot = 1.0f;
    return 2.0f * acosf(dot);
}

static void make_round_trip_clip(void) {
    anim_clip_init(&g_source, 1.0f, true);
    g_source.playing = false;
    const f32 times[2] = {0.0f, 1.0f};
    const f32 translation[2][4] = {
        {-2.0f, 0.25f, 100.0f, 0.0f}, {4.0f, 1.5f, -50.0f, 0.0f}
    };
    anim_clip_add_channel(&g_source, 0u, ANIM_PATH_TRANSLATION, 2u,
                          times, (const f32 *)translation);
    const f32 rotation[2][4] = {
        {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.6f, 0.0f, 0.8f}
    };
    anim_clip_add_channel(&g_source, 1u, ANIM_PATH_ROTATION, 2u,
                          times, (const f32 *)rotation);
    const f32 scale[1][4] = {{0.5f, 2.0f, 4.0f, 0.0f}};
    anim_clip_add_channel(&g_source, 2u, ANIM_PATH_SCALE, 1u,
                          times, (const f32 *)scale);
    anim_clip_add_channel(&g_source, 3u, ANIM_PATH_TRANSLATION, 0u,
                          times, (const f32 *)translation);
}

TEST(codec_round_trip_stays_within_explicit_bounds) {
    make_round_trip_clip();
    usize size = 0u;
    ASSERT_EQ(anim_codec_encoded_size(&g_source, 4u, &size), ANIM_CODEC_OK);
    ASSERT_TRUE(size > 0u && size <= sizeof(g_bytes));
    usize written = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, size, &written), ANIM_CODEC_OK);
    ASSERT_EQ(written, size);
    ASSERT_EQ(anim_codec_decode(g_bytes, written, &g_decoded), ANIM_CODEC_OK);
    ASSERT_EQ(g_decoded.channel_count, 4u);
    ASSERT_FLOAT_EQ(g_decoded.duration, 1.0f, 0.0f);
    ASSERT_TRUE(g_decoded.loop);
    ASSERT_FALSE(g_decoded.playing);
    const f32 time_bound = 1.0f / (2.0f * 65535.0f) + 1e-6f;
    for (u32 c = 0; c < 4u; ++c) {
        const AnimChannel *source = &g_source.channels[c];
        const AnimChannel *decoded = &g_decoded.channels[c];
        ASSERT_EQ(decoded->joint_index, source->joint_index);
        ASSERT_EQ(decoded->path, source->path);
        ASSERT_EQ(decoded->interp, source->interp);
        ASSERT_EQ(decoded->keyframe_count, source->keyframe_count);
        for (u32 k = 0; k < source->keyframe_count; ++k) {
            ASSERT_FLOAT_EQ(decoded->times[k], source->times[k], time_bound);
            if (source->path == ANIM_PATH_ROTATION) {
                ASSERT_TRUE(quaternion_angle(source->values[k], decoded->values[k]) <=
                            ANIM_CODEC_ROTATION_ERROR_BOUND);
            } else {
                f32 min[3] = {source->values[0][0], source->values[0][1], source->values[0][2]};
                f32 max[3] = {min[0], min[1], min[2]};
                for (u32 other = 1; other < source->keyframe_count; ++other)
                    for (u32 a = 0; a < 3u; ++a) {
                        if (source->values[other][a] < min[a]) min[a] = source->values[other][a];
                        if (source->values[other][a] > max[a]) max[a] = source->values[other][a];
                    }
                for (u32 a = 0; a < 3u; ++a) {
                    f32 bound = (max[a] - min[a]) / (2.0f * 65535.0f) + 1e-6f;
                    ASSERT_FLOAT_EQ(decoded->values[k][a], source->values[k][a], bound);
                }
            }
        }
    }
}

TEST(codec_rejects_payload_corruption_without_touching_output) {
    make_round_trip_clip();
    usize size = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, sizeof(g_bytes), &size),
              ANIM_CODEC_OK);
    g_bytes[size - 1u] ^= 1u;
    g_decoded.duration = 123.0f;
    g_decoded.channel_count = 7u;
    ASSERT_EQ(anim_codec_decode(g_bytes, size, &g_decoded), ANIM_CODEC_CORRUPT);
    g_bytes[size - 1u] ^= 1u;
    ASSERT_FLOAT_EQ(g_decoded.duration, 123.0f, 0.0f);
    ASSERT_EQ(g_decoded.channel_count, 7u);
}

TEST(codec_rejects_invalid_source_before_writing) {
    for (u32 test_case = 0; test_case < 6u; ++test_case) {
        make_round_trip_clip();
        if (test_case == 0u) g_source.channels[0].values[0][1] = NAN;
        if (test_case == 1u) g_source.channels[0].times[1] = INFINITY;
        if (test_case == 2u) {
            g_source.channels[0].times[0] = 1.0f;
            g_source.channels[0].times[1] = 0.0f;
        }
        if (test_case == 3u) g_source.channels[0].times[1] = 2.0f;
        if (test_case == 4u) memset(g_source.channels[1].values[1], 0,
                                    sizeof(g_source.channels[1].values[1]));
        if (test_case == 5u) g_source.duration = NAN;
        memset(g_bytes, 0x5a, 64u);
        usize size = 0u;
        ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, sizeof(g_bytes), &size),
                  ANIM_CODEC_INVALID);
        for (u32 i = 0; i < 64u; ++i) ASSERT_EQ(g_bytes[i], 0x5a);
    }
}

TEST(codec_rejects_semantic_corruption_with_valid_crc) {
    for (u32 test_case = 0; test_case < 3u; ++test_case) {
        make_round_trip_clip();
        usize size = 0u;
        ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, sizeof(g_bytes), &size),
                  ANIM_CODEC_OK);
        if (test_case == 0u) {
            usize empty = test_channel_offset(g_bytes, 3u);
            test_write_f32(g_bytes + empty + 8, NAN);
        } else if (test_case == 1u) {
            usize first = test_channel_offset(g_bytes, 0u);
            test_write_f32(g_bytes + first + 8, 1.0f);
            test_write_f32(g_bytes + first + 24, -1.0f);
        } else {
            usize first = test_channel_offset(g_bytes, 0u) + ANIM_CODEC_CHANNEL_HEADER_BYTES;
            test_write_u16(g_bytes + first, ANIM_CODEC_QUANT_STEPS);
            test_write_u16(g_bytes + first + 8, 0u);
        }
        test_repair_crc(g_bytes);
        g_decoded.duration = 123.0f;
        ASSERT_EQ(anim_codec_decode(g_bytes, size, &g_decoded), ANIM_CODEC_CORRUPT);
        ASSERT_FLOAT_EQ(g_decoded.duration, 123.0f, 0.0f);
    }
}

TEST(codec_rejects_every_payload_byte_corruption) {
    make_round_trip_clip();
    usize size = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, sizeof(g_bytes), &size),
              ANIM_CODEC_OK);
    for (usize i = ANIM_CODEC_HEADER_BYTES; i < size; ++i) {
        g_bytes[i] ^= 0x80u;
        ASSERT_EQ(anim_codec_decode(g_bytes, size, &g_decoded), ANIM_CODEC_CORRUPT);
        g_bytes[i] ^= 0x80u;
    }
}

TEST(codec_rejects_bad_version_joints_channels_and_paths) {
    for (u32 test_case = 0; test_case < 5u; ++test_case) {
        make_round_trip_clip();
        usize size = 0u;
        ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, sizeof(g_bytes), &size),
                  ANIM_CODEC_OK);
        AnimCodecResult expected = ANIM_CODEC_CORRUPT;
        if (test_case == 0u) {
            test_write_u16(g_bytes + 4, ANIM_CODEC_VERSION + 1u);
            expected = ANIM_CODEC_VERSION_UNSUPPORTED;
        } else if (test_case == 1u) {
            test_write_u16(g_bytes + ANIM_CODEC_HEADER_BYTES, 4u);
        } else if (test_case == 2u) {
            g_bytes[ANIM_CODEC_HEADER_BYTES + 2] = 255u;
        } else if (test_case == 3u) {
            test_write_u16(g_bytes + 14, SKELETON_MAX_CHANNELS + 1u);
        } else {
            test_write_f32(g_bytes + 16, NAN);
        }
        test_repair_crc(g_bytes);
        ASSERT_EQ(anim_codec_decode(g_bytes, size, &g_decoded), expected);
    }
    make_round_trip_clip();
    g_source.channels[0].joint_index = 4u;
    usize required = 0u;
    ASSERT_EQ(anim_codec_encoded_size(&g_source, 4u, &required), ANIM_CODEC_INVALID);
    make_round_trip_clip();
    g_source.channel_count = SKELETON_MAX_CHANNELS + 1u;
    ASSERT_EQ(anim_codec_encoded_size(&g_source, 4u, &required), ANIM_CODEC_INVALID);
}

TEST(codec_reports_capacity_and_rejects_wrong_lengths) {
    make_round_trip_clip();
    usize size = 0u;
    ASSERT_EQ(anim_codec_encoded_size(&g_source, 4u, &size), ANIM_CODEC_OK);
    memset(g_bytes, 0x5a, size);
    usize required = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, size - 1u, &required),
              ANIM_CODEC_CAPACITY);
    ASSERT_EQ(required, size);
    for (usize i = 0; i < size; ++i) ASSERT_EQ(g_bytes[i], 0x5a);
    ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, size, &required), ANIM_CODEC_OK);
    ASSERT_EQ(anim_codec_decode(g_bytes, size - 1u, &g_decoded), ANIM_CODEC_CORRUPT);
    ASSERT_EQ(anim_codec_decode(g_bytes, size + 1u, &g_decoded), ANIM_CODEC_CORRUPT);
}

TEST(codec_rejects_negative_source_enums_before_writing) {
    for (u32 test_case = 0; test_case < 2u; ++test_case) {
        make_round_trip_clip();
        if (test_case == 0u) g_source.channels[0].path = (AnimPathType)-1;
        else g_source.channels[0].interp = (AnimInterp)-1;
        memset(g_bytes, 0x5a, 64u);
        usize size = 0u;
        ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, sizeof(g_bytes), &size),
                  ANIM_CODEC_INVALID);
        for (u32 i = 0; i < 64u; ++i) ASSERT_EQ(g_bytes[i], 0x5a);
    }
}

TEST(codec_rejects_every_stream_byte_corruption) {
    make_round_trip_clip();
    usize size = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, sizeof(g_bytes), &size),
              ANIM_CODEC_OK);
    for (usize i = 0; i < size; ++i) {
        g_decoded.duration = 123.0f;
        g_decoded.channel_count = 7u;
        g_bytes[i] ^= 0x80u;
        AnimCodecResult result = anim_codec_decode(g_bytes, size, &g_decoded);
        g_bytes[i] ^= 0x80u;
        ASSERT_NEQ(result, ANIM_CODEC_OK);
        ASSERT_FLOAT_EQ(g_decoded.duration, 123.0f, 0.0f);
        ASSERT_EQ(g_decoded.channel_count, 7u);
    }
}

TEST(codec_uses_wide_quantization_at_half_step_boundaries) {
    anim_clip_init(&g_source, 64.0f, false);
    const f32 times[3] = {0.0f, 16.187257766723633f, 64.0f};
    const f32 values[3][4] = {
        {-50.0f, 0.0f, 0.0f, 0.0f},
        {-37.15877151489258f, 0.0f, 0.0f, 0.0f},
        {50.0f, 0.0f, 0.0f, 0.0f}
    };
    anim_clip_add_channel(&g_source, 0u, ANIM_PATH_TRANSLATION, 3u,
                          times, (const f32 *)values);
    usize size = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 1u, g_bytes, sizeof(g_bytes), &size),
              ANIM_CODEC_OK);
    ASSERT_EQ(anim_codec_decode(g_bytes, size, &g_decoded), ANIM_CODEC_OK);
    ASSERT_FLOAT_EQ(g_decoded.channels[0].times[1], 16.186769485473633f, 0.0f);
    ASSERT_FLOAT_EQ(g_decoded.channels[0].values[1][0], -37.1595344543457f, 0.0f);
}

TEST(codec_published_bounds_include_final_f32_rounding) {
    anim_clip_init(&g_source, 0.1f, false);
    const f32 times[3] = {0.0f, 0.03603341802954674f, 0.1f};
    const f32 values[3][4] = {
        {0.0f, 0.0f, 0.0f, 0.0f},
        {0.03603341802954674f, 0.0f, 0.0f, 0.0f},
        {0.1f, 0.0f, 0.0f, 0.0f}
    };
    anim_clip_add_channel(&g_source, 0u, ANIM_PATH_TRANSLATION, 3u,
                          times, (const f32 *)values);
    usize size = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 1u, g_bytes, sizeof(g_bytes), &size),
              ANIM_CODEC_OK);
    ASSERT_EQ(anim_codec_decode(g_bytes, size, &g_decoded), ANIM_CODEC_OK);
    f32 time_error = fabsf(g_decoded.channels[0].times[1] - times[1]);
    f32 value_error = fabsf(g_decoded.channels[0].values[1][0] - values[1][0]);
    ASSERT_TRUE(time_error <= anim_codec_time_error_bound(g_source.duration));
    ASSERT_TRUE(value_error <= anim_codec_scalar_error_bound(
        values[0][0], values[2][0]));
}

TEST(codec_rejects_events_before_writing) {
    make_round_trip_clip();
    anim_clip_add_event(&g_source, 0.5f, "event");
    memset(g_bytes, 0x5a, 64u);
    usize size = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 4u, g_bytes, sizeof(g_bytes), &size),
              ANIM_CODEC_INVALID);
    for (u32 i = 0; i < 64u; ++i) ASSERT_EQ(g_bytes[i], 0x5a);
}

TEST(codec_zero_channel_clip_round_trips) {
    anim_clip_init(&g_source, 0.0f, true);
    g_source.playing = false;
    usize size = 0u;
    ASSERT_EQ(anim_codec_encode(&g_source, 1u, g_bytes, sizeof(g_bytes), &size),
              ANIM_CODEC_OK);
    ASSERT_EQ(size, ANIM_CODEC_HEADER_BYTES);
    ASSERT_EQ(anim_codec_decode(g_bytes, size, &g_decoded), ANIM_CODEC_OK);
    ASSERT_EQ(g_decoded.channel_count, 0u);
    ASSERT_EQ(g_decoded.event_count, 0u);
    ASSERT_FLOAT_EQ(g_decoded.duration, 0.0f, 0.0f);
    ASSERT_TRUE(g_decoded.loop);
    ASSERT_FALSE(g_decoded.playing);
}

TEST_MAIN_BEGIN()
    RUN_TEST(codec_round_trip_stays_within_explicit_bounds);
    RUN_TEST(codec_rejects_payload_corruption_without_touching_output);
    RUN_TEST(codec_rejects_invalid_source_before_writing);
    RUN_TEST(codec_rejects_semantic_corruption_with_valid_crc);
    RUN_TEST(codec_rejects_every_payload_byte_corruption);
    RUN_TEST(codec_rejects_bad_version_joints_channels_and_paths);
    RUN_TEST(codec_reports_capacity_and_rejects_wrong_lengths);
    RUN_TEST(codec_rejects_negative_source_enums_before_writing);
    RUN_TEST(codec_rejects_every_stream_byte_corruption);
    RUN_TEST(codec_uses_wide_quantization_at_half_step_boundaries);
    RUN_TEST(codec_published_bounds_include_final_f32_rounding);
    RUN_TEST(codec_rejects_events_before_writing);
    RUN_TEST(codec_zero_channel_clip_round_trips);
TEST_MAIN_END()
