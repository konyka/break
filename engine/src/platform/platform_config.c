#include <platform/platform.h>

static bool platform_title_utf8_valid(const char *text, usize length)
{
    const unsigned char *bytes = (const unsigned char *)text;
    usize offset = 0;

    while (offset < length) {
        unsigned char first = bytes[offset++];
        usize remaining = length - offset;

        if (first <= 0x7Fu) continue;
        if (first >= 0xC2u && first <= 0xDFu) {
            if (remaining < 1u || bytes[offset] < 0x80u || bytes[offset] > 0xBFu) {
                return false;
            }
            offset += 1u;
            continue;
        }
        if (first >= 0xE0u && first <= 0xEFu) {
            if (remaining < 2u || bytes[offset] < 0x80u || bytes[offset] > 0xBFu ||
                bytes[offset + 1u] < 0x80u || bytes[offset + 1u] > 0xBFu ||
                (first == 0xE0u && bytes[offset] < 0xA0u) ||
                (first == 0xEDu && bytes[offset] >= 0xA0u)) return false;
            offset += 2u;
            continue;
        }
        if (first < 0xF0u || first > 0xF4u ||
            remaining < 3u || bytes[offset] < 0x80u || bytes[offset] > 0xBFu ||
            bytes[offset + 1u] < 0x80u || bytes[offset + 1u] > 0xBFu ||
            bytes[offset + 2u] < 0x80u || bytes[offset + 2u] > 0xBFu ||
            (first == 0xF0u && bytes[offset] < 0x90u) ||
            (first == 0xF4u && bytes[offset] >= 0x90u)) return false;
        offset += 3u;
    }
    return true;
}

bool platform_config_valid(const PlatformConfig *cfg)
{
    usize title_length = 0;

    if (cfg == NULL || cfg->title == NULL || cfg->title[0] == '\0') return false;
    while (title_length < PLATFORM_MAX_WINDOW_TITLE_BYTES &&
           cfg->title[title_length] != '\0') {
        title_length++;
    }
    if (title_length == PLATFORM_MAX_WINDOW_TITLE_BYTES) return false;
    if (!platform_title_utf8_valid(cfg->title, title_length)) return false;
    if (cfg->width == 0 || cfg->height == 0) return false;
    if (cfg->width > PLATFORM_MAX_WINDOW_DIMENSION ||
        cfg->height > PLATFORM_MAX_WINDOW_DIMENSION) return false;
    return true;
}
