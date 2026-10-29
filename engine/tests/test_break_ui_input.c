#include "test_framework.h"

#include <string.h>

#include "ui/myui_break_input.h"
#include "mypal/my_event.h"
#include "platform/input.h"

TEST(ascii_identity)
{
    ASSERT_EQ(break_ui_map_key('A'), (uint32_t)'A');
    ASSERT_EQ(break_ui_map_key('0'), (uint32_t)'0');
    ASSERT_EQ(break_ui_map_key(32), (uint32_t)32);
    ASSERT_EQ(break_ui_map_key(126), (uint32_t)126);
}

TEST(named_keys)
{
    ASSERT_EQ(break_ui_map_key(256), (uint32_t)MY_KEY_ESCAPE);
    ASSERT_EQ(break_ui_map_key(257), (uint32_t)MY_KEY_RETURN);
    ASSERT_EQ(break_ui_map_key(259), (uint32_t)MY_KEY_TAB);
    ASSERT_EQ(break_ui_map_key(260), (uint32_t)MY_KEY_BACKSPACE);
    ASSERT_EQ(break_ui_map_key(261), (uint32_t)MY_KEY_LEFT);
    ASSERT_EQ(break_ui_map_key(262), (uint32_t)MY_KEY_RIGHT);
    ASSERT_EQ(break_ui_map_key(263), (uint32_t)MY_KEY_UP);
    ASSERT_EQ(break_ui_map_key(264), (uint32_t)MY_KEY_DOWN);
}

TEST(function_and_navigation_keys)
{
    ASSERT_EQ(break_ui_map_key(271), (uint32_t)MY_KEY_F1);
    ASSERT_EQ(break_ui_map_key(282), (uint32_t)MY_KEY_F12);
    ASSERT_EQ(break_ui_map_key(283), (uint32_t)MY_KEY_PAGE_UP);
    ASSERT_EQ(break_ui_map_key(284), (uint32_t)MY_KEY_PAGE_DOWN);
    ASSERT_EQ(break_ui_map_key(285), (uint32_t)MY_KEY_HOME);
    ASSERT_EQ(break_ui_map_key(286), (uint32_t)MY_KEY_END);
    ASSERT_EQ(break_ui_map_key(287), (uint32_t)MY_KEY_INSERT);
    ASSERT_EQ(break_ui_map_key(288), (uint32_t)MY_KEY_DELETE);
}

TEST(unknown_keys)
{
    ASSERT_EQ(break_ui_map_key(0), (uint32_t)MY_KEY_UNKNOWN);
    ASSERT_EQ(break_ui_map_key(511), (uint32_t)MY_KEY_UNKNOWN);
    ASSERT_EQ(break_ui_map_key(300), (uint32_t)MY_KEY_UNKNOWN);
}

TEST(ime_text_keys_use_commit_path_only)
{
    ASSERT_TRUE(break_ui_should_dispatch_key('a', 0, false));
    ASSERT_TRUE(!break_ui_should_dispatch_key('a', 0, true));
    ASSERT_TRUE(!break_ui_should_dispatch_key('A', MY_KEYMOD_SHIFT, true));
    ASSERT_TRUE(break_ui_should_dispatch_key('a', MY_KEYMOD_CTRL, true));
    ASSERT_TRUE(break_ui_should_dispatch_key(261, 0, true));
}

TEST(utf8_byte_offsets_are_codepoint_offsets)
{
    const char *text = "A\xE4\xB8\xAD\xF0\x9F\x99\x82";

    ASSERT_EQ(break_utf8_byte_to_cp(NULL, 4), 0);
    ASSERT_EQ(break_utf8_byte_to_cp(text, -1), 0);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 0), 0);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 1), 1);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 2), 2);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 4), 2);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 8), 3);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 99), 3);
}

TEST(invalid_utf8_always_makes_progress)
{
    const char text[] = "A\x80\xF5" "B";

    ASSERT_EQ(break_utf8_byte_to_cp(text, 1), 1);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 2), 2);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 3), 3);
    ASSERT_EQ(break_utf8_byte_to_cp(text, 4), 4);
}

TEST(utf16_offsets_are_codepoint_offsets)
{
    const uint16_t text[] = {'A', 0x4E2D, 0xD83D, 0xDE42, 'B', 0};

    ASSERT_EQ(break_utf16_units_to_cp(NULL, 4), 0);
    ASSERT_EQ(break_utf16_units_to_cp(text, -1), 0);
    ASSERT_EQ(break_utf16_units_to_cp(text, 0), 0);
    ASSERT_EQ(break_utf16_units_to_cp(text, 2), 2);
    ASSERT_EQ(break_utf16_units_to_cp(text, 3), 3);
    ASSERT_EQ(break_utf16_units_to_cp(text, 4), 3);
    ASSERT_EQ(break_utf16_units_to_cp(text, 5), 4);
    ASSERT_EQ(break_utf16_units_to_cp(text, 99), 4);
}

/* The keyboard pass in break_ui_pump runs before the pointer pass over the
 * same InputState.keys edge table; it must skip the mouse slots entirely
 * (2026-10-28: it recorded their edges first, so no pointer press or
 * release ever reached myui through BreakUI). */
TEST(mouse_and_modifier_slots_are_not_keyboard_keys) {
    u32 i;
    for (i = INPUT_MOUSE_LEFT; i <= INPUT_MOUSE_5; i++) {
        ASSERT_FALSE(break_ui_key_slot_is_keyboard(i));
    }
    ASSERT_FALSE(break_ui_key_slot_is_keyboard(289u));
    ASSERT_FALSE(break_ui_key_slot_is_keyboard(290u));
    ASSERT_TRUE(break_ui_key_slot_is_keyboard('w'));
    ASSERT_TRUE(break_ui_key_slot_is_keyboard(256u));
    ASSERT_TRUE(break_ui_key_slot_is_keyboard(INPUT_MOUSE_5 + 1u));
}

/* Break mouse slots are LEFT=300, RIGHT=301, MIDDLE=302, 303/304 extra;
 * myui numbers buttons 1 = left, 2 = middle, 3 = right (my_event.h). The
 * bridge used slot offset + 1, which swapped right and middle: a right
 * drag in the editor viewport panned instead of orbiting. */
TEST(mouse_slots_map_to_myui_button_numbers) {
    ASSERT_EQ(break_ui_map_mouse_button(INPUT_MOUSE_LEFT), 1u);
    ASSERT_EQ(break_ui_map_mouse_button(INPUT_MOUSE_MIDDLE), 2u);
    ASSERT_EQ(break_ui_map_mouse_button(INPUT_MOUSE_RIGHT), 3u);
    ASSERT_EQ(break_ui_map_mouse_button(INPUT_MOUSE_4), 4u);
    ASSERT_EQ(break_ui_map_mouse_button(INPUT_MOUSE_5), 5u);
    ASSERT_EQ(break_ui_map_mouse_button('w'), 0u);
}

/* Alt was never translated: Alt+drag orbit and Alt+key shortcuts in the
 * editor only worked through synthetic events. Shift 289, Ctrl 290, Alt
 * INPUT_KEY_ALT (316) map to the myui modifier bits; Alt is a modifier,
 * not a typed key. */
static bool g_down[INPUT_MAX_KEYS];
static bool fake_down(void *user, u32 key) {
    (void)user;
    return key < INPUT_MAX_KEYS && g_down[key];
}

TEST(shift_ctrl_alt_slots_map_to_modifier_bits) {
    memset(g_down, 0, sizeof(g_down));
    ASSERT_EQ(break_ui_modifiers_from(fake_down, NULL), 0u);
    g_down[289] = true;
    ASSERT_EQ(break_ui_modifiers_from(fake_down, NULL), (u32)MY_KEYMOD_SHIFT);
    g_down[290] = true;
    g_down[INPUT_KEY_ALT] = true;
    ASSERT_EQ(break_ui_modifiers_from(fake_down, NULL),
              (u32)(MY_KEYMOD_SHIFT | MY_KEYMOD_CTRL | MY_KEYMOD_ALT));
    g_down[289] = g_down[290] = false;
    ASSERT_EQ(break_ui_modifiers_from(fake_down, NULL), (u32)MY_KEYMOD_ALT);
    ASSERT_FALSE(break_ui_key_slot_is_keyboard(INPUT_KEY_ALT));
    ASSERT_EQ(break_ui_modifiers_from(NULL, NULL), 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ascii_identity);
    RUN_TEST(named_keys);
    RUN_TEST(function_and_navigation_keys);
    RUN_TEST(unknown_keys);
    RUN_TEST(ime_text_keys_use_commit_path_only);
    RUN_TEST(utf8_byte_offsets_are_codepoint_offsets);
    RUN_TEST(invalid_utf8_always_makes_progress);
    RUN_TEST(utf16_offsets_are_codepoint_offsets);
    RUN_TEST(mouse_and_modifier_slots_are_not_keyboard_keys);
    RUN_TEST(mouse_slots_map_to_myui_button_numbers);
    RUN_TEST(shift_ctrl_alt_slots_map_to_modifier_bits);
TEST_MAIN_END()
