#include "platform_display_media.h"

#include <string.h>

#define DISPLAY_EDID_BLOCK_BYTES 128u
#define DISPLAY_EDID_MAX_EXTENSIONS 8u
#define DISPLAY_CHROMATICITY_TOLERANCE 12u

static bool display_edid_block_valid(const unsigned char *block)
{
    unsigned int sum = 0u;
    unsigned int i;

    for (i = 0u; i < DISPLAY_EDID_BLOCK_BYTES; ++i) sum += block[i];
    return (sum & 0xFFu) == 0u;
}

static unsigned int display_edid_chromaticity(const unsigned char *edid,
                                              unsigned int low_index,
                                              unsigned int low_shift,
                                              unsigned int high_index)
{
    return (((unsigned int)edid[low_index] >> low_shift) & 3u) |
           ((unsigned int)edid[high_index] << 2);
}

static bool display_chromaticity_matches(const unsigned int *actual,
                                         const unsigned int *reference)
{
    unsigned int i;
    for (i = 0u; i < 6u; ++i) {
        unsigned int value = actual[i] > reference[i]
                                 ? actual[i] - reference[i]
                                 : reference[i] - actual[i];
        if (value > DISPLAY_CHROMATICITY_TOLERANCE) return false;
    }
    return true;
}

static bool display_parse_hdr_extension(const unsigned char *extension,
                                        u32 *capabilities, bool *hdr_known)
{
    unsigned int end;
    unsigned int position;
    u32 extension_capabilities = 0u;
    bool extension_hdr_known = false;

    if (extension[0] != 0x02u || !display_edid_block_valid(extension))
        return false;
    end = extension[2];
    if (end != 0u && (end < 4u || end > 127u)) return false;
    if (end == 0u) return true;
    position = 4u;
    while (position < end) {
        unsigned int header = extension[position];
        unsigned int tag = header >> 5;
        unsigned int length = header & 0x1Fu;
        if (position + 1u + length > end) return false;
        if (tag == 7u && extension[position + 1u] == 0x06u) {
            if (length < 3u) return false;
            unsigned int eotf = extension[position + 2u];
            extension_hdr_known = true;
            if ((eotf & ((1u << 2) | (1u << 3))) != 0u)
                extension_capabilities |= PLATFORM_MEDIA_CAP_HDR;
        }
        position += 1u + length;
    }
    *capabilities |= extension_capabilities;
    *hdr_known = *hdr_known || extension_hdr_known;
    return true;
}

bool platform_display_parse_edid(const unsigned char *data, usize length,
                                 u32 *capabilities, bool *gamut_known,
                                 bool *hdr_known)
{
    static const unsigned int display_p3[6] = {
        696u, 327u, 271u, 706u, 153u, 61u
    };
    static const unsigned int display_rec2020[6] = {
        724u, 299u, 174u, 816u, 134u, 47u
    };
    unsigned int actual[6];
    unsigned int extension_count;
    unsigned int available_extensions;
    unsigned int i;

    if (capabilities == NULL || gamut_known == NULL || hdr_known == NULL) {
        return false;
    }
    *capabilities = PLATFORM_MEDIA_CAP_COLOR_SRGB;
    *gamut_known = false;
    *hdr_known = false;
    if (data == NULL || length < DISPLAY_EDID_BLOCK_BYTES) return false;
    if ((length - DISPLAY_EDID_BLOCK_BYTES) % DISPLAY_EDID_BLOCK_BYTES != 0u) {
        *capabilities = 0u;
        return false;
    }
    if (memcmp(data, "\x00\xFF\xFF\xFF\xFF\xFF\xFF\x00", 8u) != 0 ||
        !display_edid_block_valid(data)) {
        *capabilities = 0u;
        return false;
    }

    actual[0] = display_edid_chromaticity(data, 25u, 6u, 27u);
    actual[1] = display_edid_chromaticity(data, 25u, 4u, 28u);
    actual[2] = display_edid_chromaticity(data, 25u, 2u, 29u);
    actual[3] = display_edid_chromaticity(data, 25u, 0u, 30u);
    actual[4] = display_edid_chromaticity(data, 26u, 6u, 31u);
    actual[5] = display_edid_chromaticity(data, 26u, 4u, 32u);
    if (display_chromaticity_matches(actual, display_rec2020)) {
        *capabilities |= PLATFORM_MEDIA_CAP_COLOR_P3 |
                         PLATFORM_MEDIA_CAP_COLOR_REC2020;
        *gamut_known = true;
    } else if (display_chromaticity_matches(actual, display_p3)) {
        *capabilities |= PLATFORM_MEDIA_CAP_COLOR_P3;
        *gamut_known = true;
    }

    extension_count = data[126];
    available_extensions = (unsigned int)((length - DISPLAY_EDID_BLOCK_BYTES) /
                                          DISPLAY_EDID_BLOCK_BYTES);
    if (available_extensions > DISPLAY_EDID_MAX_EXTENSIONS)
        available_extensions = DISPLAY_EDID_MAX_EXTENSIONS;
    if (available_extensions > extension_count)
        available_extensions = extension_count;
    for (i = 0u; i < available_extensions; ++i) {
        u32 extension_capabilities = 0u;
        bool extension_hdr_known = false;
        if (display_parse_hdr_extension(
                data + DISPLAY_EDID_BLOCK_BYTES * (i + 1u),
                &extension_capabilities, &extension_hdr_known)) {
            *capabilities |= extension_capabilities;
            *hdr_known = *hdr_known || extension_hdr_known;
        }
    }
    return true;
}
