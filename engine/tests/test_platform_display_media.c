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
    unsigned char edid[256] = {0}; /* make_edid(hdr=false) clears only block 0 */
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
    unsigned char edid[256] = {0}; /* make_edid(hdr=false) clears only block 0 */
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
    unsigned char edid[256] = {0}; /* make_edid(hdr=false) clears only block 0 */
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

#if defined(__linux__)
#include <stdio.h>
#include <sys/stat.h>

static void drm_write(const char *root, const char *entry, const unsigned char *data,
                      size_t size)
{
    char path[700];
    FILE *fp;
    snprintf(path, sizeof(path), "%s/%s", root, entry);
    ASSERT_EQ(TEST_MKDIR(path), 0);
    snprintf(path, sizeof(path), "%s/%s/edid", root, entry);
    fp = fopen(path, "wb");
    ASSERT_NOT_NULL(fp);
    if (size > 0u) ASSERT_EQ(fwrite(data, 1u, size, fp), size);
    fclose(fp);
}

static void drm_remove(const char *root, const char *entry)
{
    char path[700];
    snprintf(path, sizeof(path), "%s/%s/edid", root, entry);
    remove(path);
    snprintf(path, sizeof(path), "%s/%s", root, entry);
    TEST_RMDIR(path);
}

/* A Wayland output name (xdg_output) is the DRM connector name; its EDID is
 * <root>/card<N>-<connector>/edid. */
TEST(drm_edid_reads_the_named_connector)
{
    char root[512];
    unsigned char p3[128];
    unsigned char rec[256];
    u32 capabilities = 0u;
    bool gamut_known = false;
    bool hdr_known = false;

    test_tmp(root, sizeof(root), "drm_edid");
    ASSERT_EQ(TEST_MKDIR(root), 0);
    make_edid(p3, false, false);
    make_edid(rec, true, true);
    drm_write(root, "card1-eDP-1", p3, sizeof(p3));
    drm_write(root, "card0-DP-10", rec, sizeof(rec));
    drm_write(root, "card0-DP-1x", rec, sizeof(rec));

    ASSERT_TRUE(platform_display_read_connector_edid(root, "eDP-1", &capabilities,
                                                     &gamut_known, &hdr_known));
    ASSERT_TRUE(gamut_known);
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) != 0u);
    ASSERT_EQ((capabilities & PLATFORM_MEDIA_CAP_COLOR_REC2020), 0u);
    ASSERT_FALSE(hdr_known);

    ASSERT_TRUE(platform_display_read_connector_edid(root, "DP-10", &capabilities,
                                                     &gamut_known, &hdr_known));
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_COLOR_REC2020) != 0u);
    ASSERT_TRUE(hdr_known);
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_HDR) != 0u);

    /* "DP-1" matches neither card0-DP-10 nor card0-DP-1x */
    capabilities = UINT32_MAX;
    gamut_known = true;
    hdr_known = true;
    ASSERT_FALSE(platform_display_read_connector_edid(root, "DP-1", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_EQ(capabilities, 0u);
    ASSERT_FALSE(gamut_known);
    ASSERT_FALSE(hdr_known);

    drm_remove(root, "card1-eDP-1");
    drm_remove(root, "card0-DP-10");
    drm_remove(root, "card0-DP-1x");
    TEST_RMDIR(root);
}

/* A disconnected connector has an empty edid file; a bad or partial one is
 * rejected like any other EDID; a name that could leave the root is refused. */
TEST(drm_edid_rejects_empty_invalid_and_unsafe_input)
{
    char root[512];
    unsigned char edid[129];
    u32 capabilities = UINT32_MAX;
    bool gamut_known = true;
    bool hdr_known = true;

    test_tmp(root, sizeof(root), "drm_edid_bad");
    ASSERT_EQ(TEST_MKDIR(root), 0);
    make_edid(edid, false, false);
    drm_write(root, "card0-HDMI-A-1", edid, 0u);
    drm_write(root, "card0-DP-2", edid, sizeof(edid));
    edid[40] ^= 1u;
    drm_write(root, "card0-DP-3", edid, 128u);

    ASSERT_FALSE(platform_display_read_connector_edid(root, "HDMI-A-1", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_EQ(capabilities, 0u);
    ASSERT_FALSE(gamut_known);
    ASSERT_FALSE(hdr_known);
    ASSERT_FALSE(platform_display_read_connector_edid(root, "DP-2", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_EQ(capabilities, 0u);
    ASSERT_FALSE(platform_display_read_connector_edid(root, "DP-3", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_EQ(capabilities, 0u);

    ASSERT_FALSE(platform_display_read_connector_edid(root, "", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid(root, "../x", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid(root, "DP-2/..", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid(NULL, "DP-2", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid(root, NULL, &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid(root, "DP-2", NULL,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid("/nonexistent-drm-root", "DP-2",
                                                      &capabilities, &gamut_known,
                                                      &hdr_known));
    ASSERT_EQ(capabilities, 0u);

    drm_remove(root, "card0-HDMI-A-1");
    drm_remove(root, "card0-DP-2");
    drm_remove(root, "card0-DP-3");
    TEST_RMDIR(root);
}

/* Only "card<digits>-<name>" entries match: an empty connector does not
 * match "card0-", and entries without the card number or the dash do not
 * match either, even with a valid EDID inside. */
TEST(drm_edid_matches_only_well_formed_connector_entries)
{
    char root[512];
    unsigned char edid[128];
    u32 capabilities = UINT32_MAX;
    bool gamut_known = true;
    bool hdr_known = true;

    test_tmp(root, sizeof(root), "drm_edid_names");
    ASSERT_EQ(TEST_MKDIR(root), 0);
    make_edid(edid, false, false);
    drm_write(root, "card0-", edid, sizeof(edid));
    drm_write(root, "card-DP-11", edid, sizeof(edid));
    drm_write(root, "card0xDP-12", edid, sizeof(edid));
    drm_write(root, "disk0-DP-13", edid, sizeof(edid));
    ASSERT_FALSE(platform_display_read_connector_edid(root, "", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid(root, "DP-11", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid(root, "DP-12", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_FALSE(platform_display_read_connector_edid(root, "DP-13", &capabilities,
                                                      &gamut_known, &hdr_known));
    ASSERT_EQ(capabilities, 0u);
    ASSERT_FALSE(gamut_known);
    ASSERT_FALSE(hdr_known);
    drm_remove(root, "card0-");
    drm_remove(root, "card-DP-11");
    drm_remove(root, "card0xDP-12");
    drm_remove(root, "disk0-DP-13");
    TEST_RMDIR(root);
}

/* An EDID file longer than the parser's bound is read up to the base block
 * plus the parser's extension limit, so a huge file is never read whole. */
TEST(drm_edid_reads_at_most_the_bounded_prefix)
{
    char root[512];
    static unsigned char big[128u * 64u];
    u32 capabilities = 0u;
    bool gamut_known = false;
    bool hdr_known = false;

    test_tmp(root, sizeof(root), "drm_edid_big");
    ASSERT_EQ(TEST_MKDIR(root), 0);
    memset(big, 0xAB, sizeof(big));
    make_edid(big, true, true);
    drm_write(root, "card2-DP-7", big, sizeof(big));
    ASSERT_TRUE(platform_display_read_connector_edid(root, "DP-7", &capabilities,
                                                     &gamut_known, &hdr_known));
    ASSERT_TRUE((capabilities & PLATFORM_MEDIA_CAP_HDR) != 0u);
    drm_remove(root, "card2-DP-7");
    TEST_RMDIR(root);
}
/* The window may span several outputs: wide gamut or HDR is reported only
 * when every one of them is known to have it; a connector without a usable
 * EDID contributes nothing, so nothing is claimed. */
TEST(drm_outputs_media_reports_only_what_every_output_has)
{
    char root[512];
    unsigned char p3[128];
    unsigned char rec[256];
    const char *both[2] = {"eDP-1", "DP-10"};
    const char *wide[1] = {"DP-10"};
    const char *missing[2] = {"DP-10", "DP-9"};
    u32 caps = UINT32_MAX;
    u32 known = UINT32_MAX;

    test_tmp(root, sizeof(root), "drm_outputs");
    ASSERT_EQ(TEST_MKDIR(root), 0);
    make_edid(p3, false, false);
    make_edid(rec, true, true);
    drm_write(root, "card1-eDP-1", p3, sizeof(p3));
    drm_write(root, "card0-DP-10", rec, sizeof(rec));

    {
        /* a NULL name is skipped, not treated as an output without EDID */
        const char *with_null[2] = {NULL, "DP-10"};
        platform_display_outputs_media(root, with_null, 2u, &caps, &known);
        ASSERT_EQ(caps, (u32)(PLATFORM_MEDIA_CAP_COLOR_P3 | PLATFORM_MEDIA_CAP_COLOR_REC2020 |
                              PLATFORM_MEDIA_CAP_HDR));
    }
    platform_display_outputs_media(root, wide, 1u, &caps, &known);
    ASSERT_EQ(caps, (u32)(PLATFORM_MEDIA_CAP_COLOR_P3 | PLATFORM_MEDIA_CAP_COLOR_REC2020 |
                          PLATFORM_MEDIA_CAP_HDR));
    ASSERT_EQ(known, (u32)(PLATFORM_MEDIA_KNOWN_COLOR_GAMUT | PLATFORM_MEDIA_KNOWN_HDR));

    platform_display_outputs_media(root, both, 2u, &caps, &known);
    ASSERT_EQ(caps, (u32)PLATFORM_MEDIA_CAP_COLOR_P3);
    ASSERT_EQ(known, (u32)PLATFORM_MEDIA_KNOWN_COLOR_GAMUT);

    platform_display_outputs_media(root, missing, 2u, &caps, &known);
    ASSERT_EQ(caps, 0u);
    ASSERT_EQ(known, 0u);

    /* an sRGB-only output: gamut is not known there, so it is not claimed */
    {
        unsigned char srgb[256] = {0};
        const char *mixed[2] = {"DP-10", "DP-20"};
        make_edid(srgb, false, true);
        set_chromaticity(srgb, 655u, 338u, 307u, 614u, 154u, 61u);
        set_checksum(srgb);
        /* SDR-only EOTF: HDR is known and absent */
        srgb[134] = 0x01u;
        set_extension_checksum(srgb + 128u);
        drm_write(root, "card0-DP-20", srgb, sizeof(srgb));
        platform_display_outputs_media(root, mixed, 2u, &caps, &known);
        ASSERT_EQ(caps, 0u);
        ASSERT_EQ(known, (u32)PLATFORM_MEDIA_KNOWN_HDR);
        drm_remove(root, "card0-DP-20");
    }

    caps = known = UINT32_MAX;
    platform_display_outputs_media(root, both, 0u, &caps, &known);
    ASSERT_EQ(caps, 0u);
    ASSERT_EQ(known, 0u);
    platform_display_outputs_media(root, NULL, 2u, &caps, &known);
    ASSERT_EQ(caps, 0u);
    ASSERT_EQ(known, 0u);
    platform_display_outputs_media(root, both, 2u, NULL, &known);
    platform_display_outputs_media(root, both, 2u, &caps, NULL);

    drm_remove(root, "card1-eDP-1");
    drm_remove(root, "card0-DP-10");
    TEST_RMDIR(root);
}
#endif

TEST_MAIN_BEGIN()
    RUN_TEST(edid_recognizes_display_p3_primaries);
    RUN_TEST(edid_recognizes_rec2020_and_hdr_static_metadata);
    RUN_TEST(edid_rejects_bad_base_checksum_without_capabilities);
    RUN_TEST(edid_rejects_truncated_extension_without_using_partial_hdr_data);
    RUN_TEST(edid_accepts_empty_cta_extension);
    RUN_TEST(edid_rejects_hdr_block_without_static_metadata_descriptor);
    RUN_TEST(edid_rolls_back_partial_cta_parse);
    RUN_TEST(edid_rejects_partial_trailing_block);
#if defined(__linux__)
    RUN_TEST(drm_edid_reads_the_named_connector);
    RUN_TEST(drm_edid_rejects_empty_invalid_and_unsafe_input);
    RUN_TEST(drm_edid_matches_only_well_formed_connector_entries);
    RUN_TEST(drm_edid_reads_at_most_the_bounded_prefix);
    RUN_TEST(drm_outputs_media_reports_only_what_every_output_has);
#endif
TEST_MAIN_END()
