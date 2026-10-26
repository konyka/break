/* ==========================================================================
 *  test_screen_keymap.c — QNX Screen key-symbol -> engine key-code mapping.
 *
 *  The mapping itself is a pure inline function over raw integer symbols
 *  (no QNX headers needed), so the same tests run on every host lane and on
 *  the QNX target. window_screen.c static-asserts that the mirrored
 *  constants stay equal to <sys/keycodes.h>.
 * ========================================================================== */

#include "test_framework.h"
#include <platform/screen_keymap.h>

TEST(keymap_printable_letters_digits_punct)
{
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'a'), (i32)'a');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'q'), (i32)'q');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'z'), (i32)'z');
    /* Uppercase normalizes to the engine's lowercase slot (x11 parity). */
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'A'), (i32)'a');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'Z'), (i32)'z');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'0'), (i32)'0');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'9'), (i32)'9');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)' '), 32);
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'-'), (i32)'-');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'='), (i32)'=');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'['), (i32)'[');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)']'), (i32)']');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'/'), (i32)'/');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'\\'), (i32)'\\');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'`'), (i32)'`');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)';'), (i32)';');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'\''), (i32)'\'');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)','), (i32)',');
    ASSERT_EQ(screen_keymap_sym_to_engine((u32)'.'), (i32)'.');
}

TEST(keymap_non_printables_match_engine_codes)
{
    /* Engine key codes are the ones x11_key_to_index produces
     * (window_x11.c:462-524): ESC 256, RET 257, TAB 259, BKSP 260,
     * arrows 261-264, F1-F12 271-282, PgUp 283 .. Menu 295,
     * Shift 289 / Ctrl 290. */
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x1B)), 256);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x0D)), 257);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x09)), 259);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x08)), 260);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x51)), 261);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x53)), 262);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x52)), 263);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x54)), 264);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xBE)), 271);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xC9)), 282);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x55)), 283);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x56)), 284);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x50)), 285);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x57)), 286);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x63)), 287);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xFF)), 288);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xE1)), 289);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xE2)), 289);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xE3)), 290);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xE4)), 290);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x13)), 291);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x14)), 292);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x7F)), 293);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xE5)), 294);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x67)), 295);
}

TEST(keymap_rejects_unknown)
{
    ASSERT_EQ(screen_keymap_sym_to_engine(0u), -1);
    ASSERT_EQ(screen_keymap_sym_to_engine(0x1234u), -1);
    /* Unmapped private-area/consumer codes must not alias engine codes. */
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0x00)), -1);
    ASSERT_EQ(screen_keymap_sym_to_engine(SCREEN_KEYMAP_PC(0xCA)), -1);
}

TEST(keymap_pc_keys_base_matches_qnx_unicode_plan)
{
    /* KEYCODE_PC_KEYS = UNICODE_PRIVATE_USE_AREA_FIRST(0xE000) + 0x1000. */
    ASSERT_EQ(SCREEN_KEYMAP_PC_KEYS, 0xF000u);
}

int main(void)
{
    RUN_TEST(keymap_printable_letters_digits_punct);
    RUN_TEST(keymap_non_printables_match_engine_codes);
    RUN_TEST(keymap_rejects_unknown);
    RUN_TEST(keymap_pc_keys_base_matches_qnx_unicode_plan);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
