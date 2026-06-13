/* ==========================================================================
 *  test_font_ui.c — UTF-8 decoding + immediate-mode UI logic (headless).
 *
 *  Only the pure pieces are exercised here: the UTF-8 decoder and the inline
 *  hit-testing / state-machine helpers from imgui.h. The rendering paths need
 *  a GPU device and are validated by the demo build, not by this unit test.
 * ========================================================================== */

#include "test_framework.h"
#include <ui/utf8.h>
#include <ui/imgui.h>

/* ----------------------------------------------------------------------- */
/*  UTF-8 decoding                                                          */
/* ----------------------------------------------------------------------- */

TEST(utf8_ascii)
{
    u32 cp = 0;
    u32 n = utf8_decode("A", &cp);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(cp, (u32)'A');
}

TEST(utf8_two_byte)
{
    /* U+00E9 'é' = 0xC3 0xA9 */
    u32 cp = 0;
    u32 n = utf8_decode("\xC3\xA9", &cp);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(cp, 0x00E9u);
}

TEST(utf8_three_byte)
{
    /* U+20AC '€' = 0xE2 0x82 0xAC */
    u32 cp = 0;
    u32 n = utf8_decode("\xE2\x82\xAC", &cp);
    ASSERT_EQ(n, 3u);
    ASSERT_EQ(cp, 0x20ACu);
}

TEST(utf8_four_byte)
{
    /* U+1F600 grinning face = 0xF0 0x9F 0x98 0x80 */
    u32 cp = 0;
    u32 n = utf8_decode("\xF0\x9F\x98\x80", &cp);
    ASSERT_EQ(n, 4u);
    ASSERT_EQ(cp, 0x1F600u);
}

TEST(utf8_invalid_lead)
{
    /* lone continuation byte */
    u32 cp = 0;
    u32 n = utf8_decode("\x80", &cp);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(cp, (u32)UTF8_REPLACEMENT);
}

TEST(utf8_truncated)
{
    /* 2-byte lead with no continuation (string ends) */
    u32 cp = 0;
    u32 n = utf8_decode("\xC3", &cp);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(cp, (u32)UTF8_REPLACEMENT);
}

TEST(utf8_overlong)
{
    /* 0xC0 0x80 is an overlong encoding of NUL — must be rejected */
    u32 cp = 0;
    u32 n = utf8_decode("\xC0\x80", &cp);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(cp, (u32)UTF8_REPLACEMENT);
}

TEST(utf8_surrogate_rejected)
{
    /* U+D800 encoded as 3 bytes 0xED 0xA0 0x80 is an invalid scalar value */
    u32 cp = 0;
    u32 n = utf8_decode("\xED\xA0\x80", &cp);
    ASSERT_EQ(n, 1u);
    ASSERT_EQ(cp, (u32)UTF8_REPLACEMENT);
}

TEST(utf8_strlen_mixed)
{
    /* "hé€" = h(1) + U+00E9(2) + U+20AC(3) = 3 codepoints, 6 bytes */
    const char *s = "h\xC3\xA9\xE2\x82\xAC";
    ASSERT_EQ(utf8_strlen(s), (usize)3);
}

TEST(utf8_iterate_never_stuck)
{
    /* Decoding always advances by >= 1 even on garbage input */
    const char *s = "\xFF\xFE\x80\x80";
    usize total = 0;
    while (*s) {
        u32 cp;
        u32 n = utf8_decode(s, &cp);
        ASSERT_TRUE(n >= 1u);
        s += n;
        total += n;
        if (total > 64) break; /* guard against an infinite loop bug */
    }
    ASSERT_EQ(total, (usize)4);
}

/* ----------------------------------------------------------------------- */
/*  IMGUI pure helpers                                                      */
/* ----------------------------------------------------------------------- */

TEST(imui_hit_inside_outside)
{
    ASSERT_TRUE(imui_hit(15.0f, 25.0f, 10.0f, 20.0f, 100.0f, 30.0f));
    ASSERT_FALSE(imui_hit(5.0f, 25.0f, 10.0f, 20.0f, 100.0f, 30.0f));   /* left  */
    ASSERT_FALSE(imui_hit(15.0f, 55.0f, 10.0f, 20.0f, 100.0f, 30.0f));  /* below */
    /* right/bottom edges are exclusive */
    ASSERT_FALSE(imui_hit(110.0f, 25.0f, 10.0f, 20.0f, 100.0f, 30.0f));
}

TEST(imui_slider_map_range)
{
    /* track [100, 300], value range [0, 10] */
    ASSERT_FLOAT_EQ(imui_slider_map(100.0f, 100.0f, 200.0f, 0.0f, 10.0f), 0.0f, 1e-4f);
    ASSERT_FLOAT_EQ(imui_slider_map(200.0f, 100.0f, 200.0f, 0.0f, 10.0f), 5.0f, 1e-4f);
    ASSERT_FLOAT_EQ(imui_slider_map(300.0f, 100.0f, 200.0f, 0.0f, 10.0f), 10.0f, 1e-4f);
    /* clamps below / above the track */
    ASSERT_FLOAT_EQ(imui_slider_map(50.0f,  100.0f, 200.0f, 0.0f, 10.0f), 0.0f, 1e-4f);
    ASSERT_FLOAT_EQ(imui_slider_map(400.0f, 100.0f, 200.0f, 0.0f, 10.0f), 10.0f, 1e-4f);
}

TEST(imui_slider_norm_clamped)
{
    ASSERT_FLOAT_EQ(imui_slider_norm(5.0f, 0.0f, 10.0f), 0.5f, 1e-4f);
    ASSERT_FLOAT_EQ(imui_slider_norm(-3.0f, 0.0f, 10.0f), 0.0f, 1e-4f);
    ASSERT_FLOAT_EQ(imui_slider_norm(99.0f, 0.0f, 10.0f), 1.0f, 1e-4f);
    /* degenerate range */
    ASSERT_FLOAT_EQ(imui_slider_norm(5.0f, 4.0f, 4.0f), 0.0f, 1e-4f);
}

TEST(imui_press_full_click)
{
    u32 hot = 0, active = 0;
    const u32 id = 42;

    /* hover only */
    ASSERT_FALSE(imui_press_logic(id, true, false, false, &hot, &active));
    ASSERT_EQ(hot, id);
    ASSERT_EQ(active, 0u);

    /* press down (edge) -> becomes active, no click yet */
    ASSERT_FALSE(imui_press_logic(id, true, true, false, &hot, &active));
    ASSERT_EQ(active, id);

    /* held -> still active */
    ASSERT_FALSE(imui_press_logic(id, true, true, true, &hot, &active));
    ASSERT_EQ(active, id);

    /* release over widget -> click! */
    ASSERT_TRUE(imui_press_logic(id, true, false, true, &hot, &active));
    ASSERT_EQ(active, 0u);
}

TEST(imui_press_release_outside_no_click)
{
    u32 hot = 0, active = 0;
    const u32 id = 7;

    imui_press_logic(id, true, true, false, &hot, &active);  /* press inside */
    ASSERT_EQ(active, id);
    /* move out and release -> no click, active cleared */
    ASSERT_FALSE(imui_press_logic(id, false, false, true, &hot, &active));
    ASSERT_EQ(active, 0u);
}

TEST(imui_press_started_outside_no_click)
{
    u32 hot = 0, active = 0;
    const u32 id = 9;

    /* press began while not hovering -> never becomes active */
    ASSERT_FALSE(imui_press_logic(id, false, true, false, &hot, &active));
    ASSERT_EQ(active, 0u);
    /* drag into widget while still holding (no new press edge) */
    ASSERT_FALSE(imui_press_logic(id, true, true, true, &hot, &active));
    ASSERT_EQ(active, 0u);
    /* release over widget -> still no click (was never active) */
    ASSERT_FALSE(imui_press_logic(id, true, false, true, &hot, &active));
}

TEST(imui_press_ids_independent)
{
    u32 hot = 0, active = 0;

    /* widget A grabs active on press */
    imui_press_logic(1, true, true, false, &hot, &active);
    ASSERT_EQ(active, 1u);
    /* widget B cannot steal active while A holds it */
    bool b_click = imui_press_logic(2, true, true, true, &hot, &active);
    ASSERT_FALSE(b_click);
    ASSERT_EQ(active, 1u);
}

/* ----------------------------------------------------------------------- */
/*  Main                                                                    */
/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(utf8_ascii);
    RUN_TEST(utf8_two_byte);
    RUN_TEST(utf8_three_byte);
    RUN_TEST(utf8_four_byte);
    RUN_TEST(utf8_invalid_lead);
    RUN_TEST(utf8_truncated);
    RUN_TEST(utf8_overlong);
    RUN_TEST(utf8_surrogate_rejected);
    RUN_TEST(utf8_strlen_mixed);
    RUN_TEST(utf8_iterate_never_stuck);
    RUN_TEST(imui_hit_inside_outside);
    RUN_TEST(imui_slider_map_range);
    RUN_TEST(imui_slider_norm_clamped);
    RUN_TEST(imui_press_full_click);
    RUN_TEST(imui_press_release_outside_no_click);
    RUN_TEST(imui_press_started_outside_no_click);
    RUN_TEST(imui_press_ids_independent);
TEST_MAIN_END()
