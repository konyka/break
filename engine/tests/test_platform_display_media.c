#include "test_framework.h"

#include "platform/platform_display_media.h"

#include <string.h>

static void set_chromaticity(unsigned char *edid, unsigned int red_x,
                             unsigned int red_y, unsigned int green_x,
                             unsigned int green_y, unsigned int blue_x,
                             unsigned int blue_y)
{
    edid[25] = (unsigned char)(((red_x & 3u) << 6) |
                               ((red_y & 3u) << 4) |
                               ((green_x & 3u) << 2) | (green_y & 3u));
    edid[26] = (unsigned char)(((blue_x & 3u) << 6) |
                               ((blue_y & 3u) << 4));
    edid[27] = (unsigned char)(red_x >> 2);
    edid[28] = (unsigned char)(red_y >> 2);
    edid[29] = (unsigned char)(green_x >> 2);
    edid[30] = (unsigned char)(green_y >> 2);
    edid[31] = (unsigned char)(blue_x >> 2);
    edid[32] = (unsigned char)(blue_y >> 2);
}

static void set_checksum(unsigned char *block)
{
    unsigned int sum = 0u;
    unsigned int i;
    for (i = 0u; i < 127u; ++i) sum += block[i];
    block[127] = (unsigned char)(0u - (sum & 0xFFu));
}

static void make_edid(unsigned char *edid, bool rec2020, bool hdr)
{
    memset(edid, 0, hdr ? 256u : 128u);
    edid[0] = 0x00;
    edid[1] = 0xFF;
    edid[2] = 0xFF;
    edid[3] = 0xFF;
    edid[4] = 0xFF;
    edid[5] = 0xFF;
    edid[6] = 0xFF;
    edid[7] = 0x00;
    edid[20] = 0x80;
    edid[126] = hdr ? 1u : 0u;
    if (rec2020) {
        set_chromaticity(edid, 724u, 299u, 174u, 816u, 134u, 47u);
    } else {
        set_chromaticity(edid, 696u, 327u, 271u, 706u, 153u, 61u);
    }
    set_checksum(edid);
    if (hdr) {
        edid[128] = 0x02;
        edid[129] = 0x03;
        edid[130] = 0x08;
        edid[131] = 0x00;
        edid[132] = 0xE3;
        edid[133] = 0x06;
        edid[134] = 0x04;
        edid[255] = 0u;
        {
            unsigned int sum = 0u;
            unsigned int i;
            for (i = 128u; i < 255u; ++i) sum += edid[i];
            edid[255] = (unsigned char)(0u - (sum & 0xFFu));
        }
    }
}

static void set_extension_checksum(unsigned char *extension)
{
    unsigned int sum = 0u;
    unsigned int i;
    for (i = 0u; i < 127u; ++i) sum += extension[i];
    extension[127] = (unsigned char)(0u - (sum & 0xFFu));
}

TEST(edid_recognizes_display_p3_primaries)
{
    unsigned char edid[128];
    u32 capabilities = 0u;
    bool gamut_known = false;
    bool hdr_known = true;

    make_edid(edid, false, false);
    ASSERT_TRUE(platform_display_parse_edid(edid, sizeof(edid), &capabilities,
                                            &gamut_known, &hdr_known));
    ASSERT_TRUE(gamut_known);
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_COLOR_SRGB) != 0u);
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) != 0u);
    ASSERT_EQ((capabilities & PLATFORM_MEDIA_CAP_COLOR_REC2020), 0u);
    ASSERT_FALSE(hdr_known);
}

TEST(edid_recognizes_rec2020_and_hdr_static_metadata)
{
    unsigned char edid[256];
    u32 capabilities = 0u;
    bool gamut_known = false;
    bool hdr_known = false;

    make_edid(edid, true, true);
    ASSERT_TRUE(platform_display_parse_edid(edid, sizeof(edid), &capabilities,
                                            &gamut_known, &hdr_known));
    ASSERT_TRUE(gamut_known);
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_COLOR_SRGB) != 0u);
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) != 0u);
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_COLOR_REC2020) != 0u);
    ASSERT_TRUE(hdr_known);
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_HDR) != 0u);
}

TEST(edid_rejects_bad_base_checksum_without_capabilities)
{
    unsigned char edid[128];
    u32 capabilities = UINT32_MAX;
    bool gamut_known = true;
    bool hdr_known = true;

    make_edid(edid, false, false);
    edid[40] ^= 1u;
    ASSERT_FALSE(platform_display_parse_edid(edid, sizeof(edid),
                                             &capabilities, &gamut_known,
                                             &hdr_known));
    ASSERT_EQ(capabilities, 0u);
    ASSERT_FALSE(gamut_known);
    ASSERT_FALSE(hdr_known);
}

TEST(edid_rejects_truncated_extension_without_using_partial_hdr_data)
{
    unsigned char edid[128];
    u32 capabilities = UINT32_MAX;
    bool gamut_known = false;
    bool hdr_known = true;

    make_edid(edid, false, false);
    edid[126] = 1u;
    set_checksum(edid);
    ASSERT_TRUE(platform_display_parse_edid(edid, sizeof(edid),
                                            &capabilities, &gamut_known,
                                            &hdr_known));
    ASSERT_TRUE(gamut_known);
    ASSERT_FALSE(hdr_known);
    ASSERT_EQ((capabilities & PLATFORM_MEDIA_CAP_HDR), 0u);
}

TEST(edid_accepts_empty_cta_extension)
{
    unsigned char edid[256];
    u32 capabilities = 0u;
    bool gamut_known = false;
    bool hdr_known = true;

    make_edid(edid, false, false);
    edid[126] = 1u;
    edid[128] = 0x02u;
    edid[129] = 0x03u;
    edid[130] = 0u;
    set_extension_checksum(edid + 128u);
    set_checksum(edid);
    ASSERT_TRUE(platform_display_parse_edid(edid, sizeof(edid), &capabilities,
                                            &gamut_known, &hdr_known));
    ASSERT_TRUE(gamut_known);
    ASSERT_FALSE(hdr_known);
    ASSERT_EQ((capabilities & PLATFORM_MEDIA_CAP_HDR), 0u);
}

TEST(edid_rejects_hdr_block_without_static_metadata_descriptor)
{
    unsigned char edid[256];
    u32 capabilities = UINT32_MAX;
    bool gamut_known = false;
    bool hdr_known = true;

    make_edid(edid, false, false);
    edid[126] = 1u;
    edid[128] = 0x02u;
    edid[129] = 0x03u;
    edid[130] = 7u;
    edid[132] = 0xE2u;
    edid[133] = 0x06u;
    edid[134] = 0x04u;
    set_extension_checksum(edid + 128u);
    set_checksum(edid);
    ASSERT_TRUE(platform_display_parse_edid(edid, sizeof(edid), &capabilities,
                                            &gamut_known, &hdr_known));
    ASSERT_TRUE(gamut_known);
    ASSERT_FALSE(hdr_known);
    ASSERT_EQ((capabilities & PLATFORM_MEDIA_CAP_HDR), 0u);
}

TEST(edid_rolls_back_partial_cta_parse)
{
    unsigned char edid[256];
    u32 capabilities = 0u;
    bool gamut_known = false;
    bool hdr_known = false;

    make_edid(edid, false, false);
    edid[126] = 1u;
    edid[128] = 0x02u;
    edid[129] = 0x03u;
    edid[130] = 12u;
    edid[132] = 0xE3u;
    edid[133] = 0x06u;
    edid[134] = 0x04u;
    edid[135] = 0x01u;
    edid[136] = 0xE4u;
    edid[137] = 0x06u;
    edid[138] = 0x04u;
    set_extension_checksum(edid + 128u);
    set_checksum(edid);
    ASSERT_TRUE(platform_display_parse_edid(edid, sizeof(edid), &capabilities,
                                            &gamut_known, &hdr_known));
    ASSERT_TRUE(gamut_known);
    ASSERT_FALSE(hdr_known);
    ASSERT_EQ((capabilities & PLATFORM_MEDIA_CAP_HDR), 0u);
}

TEST(edid_rejects_partial_trailing_block)
{
    unsigned char edid[129];
    u32 capabilities = UINT32_MAX;
    bool gamut_known = true;
    bool hdr_known = true;

    make_edid(edid, false, false);
    edid[128] = 0x02u;
    ASSERT_FALSE(platform_display_parse_edid(edid, sizeof(edid),
                                             &capabilities, &gamut_known,
                                             &hdr_known));
    ASSERT_EQ(capabilities, 0u);
    ASSERT_FALSE(gamut_known);
    ASSERT_FALSE(hdr_known);
}

TEST_MAIN_BEGIN()
    RUN_TEST(edid_recognizes_display_p3_primaries);
    RUN_TEST(edid_recognizes_rec2020_and_hdr_static_metadata);
    RUN_TEST(edid_rejects_bad_base_checksum_without_capabilities);
    RUN_TEST(edid_rejects_truncated_extension_without_using_partial_hdr_data);
    RUN_TEST(edid_accepts_empty_cta_extension);
    RUN_TEST(edid_rejects_hdr_block_without_static_metadata_descriptor);
    RUN_TEST(edid_rolls_back_partial_cta_parse);
    RUN_TEST(edid_rejects_partial_trailing_block);
TEST_MAIN_END()
