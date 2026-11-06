#pragma once

#include <core/types.h>

static bool break_system_utf8_valid(const char *text, usize length) {
    const u8 *bytes = (const u8 *)text;
    usize offset = 0u;
    while (offset < length) {
        u8 first = bytes[offset++];
        usize remaining = length - offset;
        if (first <= 0x7Fu) continue;
        if (first >= 0xC2u && first <= 0xDFu) {
            if (remaining < 1u || bytes[offset] < 0x80u || bytes[offset] > 0xBFu)
                return false;
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
        if (first < 0xF0u || first > 0xF4u || remaining < 3u ||
            bytes[offset] < 0x80u || bytes[offset] > 0xBFu ||
            bytes[offset + 1u] < 0x80u || bytes[offset + 1u] > 0xBFu ||
            bytes[offset + 2u] < 0x80u || bytes[offset + 2u] > 0xBFu ||
            (first == 0xF0u && bytes[offset] < 0x90u) ||
            (first == 0xF4u && bytes[offset] >= 0x90u)) return false;
        offset += 3u;
    }
    return true;
}
