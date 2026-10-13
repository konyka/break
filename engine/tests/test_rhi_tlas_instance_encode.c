#include "test_framework.h"

#include <rhi/rhi.h>

TEST(tlas_instance_encode_rejects_invalid_boundaries)
{
    u8 record[RHI_TLAS_INSTANCE_SIZE + 1u];
    RHITLASInstanceDesc desc = {0};

    memset(record, 0xA5, sizeof(record));
    ASSERT_FALSE(rhi_tlas_instance_encode(NULL, sizeof(record), 1u, &desc));
    ASSERT_FALSE(rhi_tlas_instance_encode(record, RHI_TLAS_INSTANCE_SIZE - 1u,
                                           1u, &desc));
    ASSERT_FALSE(rhi_tlas_instance_encode(record, sizeof(record), 0u, &desc));
    ASSERT_FALSE(rhi_tlas_instance_encode(record, sizeof(record), 1u, NULL));
}

TEST(tlas_instance_encode_writes_the_serialized_record)
{
    static const f32 transform[12] = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
    };
    const u32 custom_index = 0xAB123456u;
    const u32 sbt_offset = 0xCD654321u;
    const u64 address = UINT64_C(0x0123456789ABCDEF);
    RHITLASInstanceDesc desc = {0};
    u8 record[RHI_TLAS_INSTANCE_SIZE + 1u];
    u32 packed0 = 0u;
    u32 packed1 = 0u;
    u64 written_address = 0u;

    memcpy(desc.transform, transform, sizeof(transform));
    desc.instance_custom_index = custom_index;
    desc.instance_mask = 0xEFu;
    desc.sbt_record_offset = sbt_offset;
    desc.instance_flags = 0x1234u;
    memset(record, 0xA5, sizeof(record));

    ASSERT_TRUE(rhi_tlas_instance_encode(record, sizeof(record), address, &desc));
    ASSERT_EQ(memcmp(record, transform, sizeof(transform)), 0);
    memcpy(&packed0, record + 48u, sizeof(packed0));
    memcpy(&packed1, record + 52u, sizeof(packed1));
    memcpy(&written_address, record + 56u, sizeof(written_address));
    ASSERT_EQ(packed0, (custom_index & 0x00FFFFFFu) | (0xEFu << 24));
    ASSERT_EQ(packed1, (sbt_offset & 0x00FFFFFFu) | (0x34u << 24));
    ASSERT_EQ(written_address, address);
    ASSERT_EQ(record[64], 0xA5u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(tlas_instance_encode_rejects_invalid_boundaries);
    RUN_TEST(tlas_instance_encode_writes_the_serialized_record);
TEST_MAIN_END()
