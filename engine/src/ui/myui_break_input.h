/**
 * @file myui_break_input.h
 * @brief Platform-key to myui-key mapping used by the BreakUI bridge.
 */
#ifndef MYUI_BREAK_INPUT_H
#define MYUI_BREAK_INPUT_H

#include "core/types.h"

/** @brief Translate a Break InputState key index to a myui key code. */
uint32_t break_ui_map_key(i32 key);

/** @brief Whether a physical key should still be dispatched while IME is on. */
bool break_ui_should_dispatch_key(i32 key, uint8_t modifiers,
                                  bool ime_enabled);

/**
 * @brief Number of UTF-8 codepoints before @a byte (clamped).
 *
 * IME transports report preedit cursor positions in platform-specific
 * units: Wayland text-input-v3 uses BYTE offsets while myui's
 * MY_EVENT_IME_PREEDIT expects a caret in codepoints.
 */
i32 break_utf8_byte_to_cp(const char* s, i32 byte);

/** @brief Number of Unicode codepoints before a UTF-16 unit offset. */
i32 break_utf16_units_to_cp(const uint16_t* s, i32 units);

#endif /* MYUI_BREAK_INPUT_H */
