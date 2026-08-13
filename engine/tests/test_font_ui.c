/* ==========================================================================
 *  test_font_ui.c — UTF-8 decoding + immediate-mode UI logic (headless).
 *
 *  Links the real imgui.c: the widgets run with a NULL FontRenderer, which
 *  makes every draw call a no-op, so the genuine interaction logic (hit
 *  testing, hot/active state machine, value writes) is exercised without a
 *  GPU device. The font_renderer_* symbols imgui.c references are stubbed
 *  below for the link only — they are never called with font == NULL. The
 *  rendering paths themselves are validated by the demo build.
 * ========================================================================== */

#include "test_framework.h"
#include <ui/utf8.h>
#include <ui/imgui.h>

/* Link-only font renderer stubs (never called: ImUI runs with font == NULL) */
void font_renderer_begin(FontRenderer *fr) { (void)fr; }
void font_renderer_draw(FontRenderer *fr, const char *text, f32 x, f32 y,
                        f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a) {
    (void)fr; (void)text; (void)x; (void)y; (void)screen_w; (void)screen_h;
    (void)r; (void)g; (void)b; (void)a;
}
void font_renderer_draw_rect(FontRenderer *fr, f32 x, f32 y, f32 w, f32 h,
                             f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a) {
    (void)fr; (void)x; (void)y; (void)w; (void)h; (void)screen_w; (void)screen_h;
    (void)r; (void)g; (void)b; (void)a;
}
f32  font_renderer_text_width(const FontRenderer *fr, const char *text) {
    (void)fr; (void)text; return 0.0f;
}
f32  font_renderer_line_height(const FontRenderer *fr) { (void)fr; return 16.0f; }
void font_renderer_end(FontRenderer *fr, RHICmdBuffer *cmd, f32 screen_w, f32 screen_h) {
    (void)fr; (void)cmd; (void)screen_w; (void)screen_h;
}

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

TEST(imui_hidden_reset_no_stale_click)
{
    /* R285: a panel hidden mid-press must not fire a phantom click on reopen. */
    ImUI ui;
    memset(&ui, 0, sizeof(ui));
    const u32 id = 1;

    /* Panel visible: hover then press down over checkbox id=1 -> becomes active. */
    imui_press_logic(id, true, false, false, &ui.hot_id, &ui.active_id);
    imui_press_logic(id, true, true, false, &ui.hot_id, &ui.active_id);
    ASSERT_EQ(ui.active_id, id);
    ui.mouse_prev_down = true; /* imui_end latch at end of that frame */

    /* Sanity — WITHOUT the reset, a release edge on reopen (mouse now up but the
     * stale latch still reads down) would wrongly register a click. */
    {
        u32 hot = ui.hot_id, active = ui.active_id;
        bool stale = imui_press_logic(id, true, /*down*/false,
                                      /*prev*/ui.mouse_prev_down, &hot, &active);
        ASSERT_TRUE(stale);
    }

    /* Panel hidden: mouse released while hidden. Reset keeps the latch fresh
     * and drops the active item. */
    imui_reset_input(&ui, /*mouse_down now*/false);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_FALSE(ui.mouse_prev_down);

    /* Reopen with cursor still over id=1, mouse up -> no phantom click. */
    bool click = imui_press_logic(id, true, ui.mouse_down, ui.mouse_prev_down,
                                  &ui.hot_id, &ui.active_id);
    ASSERT_FALSE(click);
    ASSERT_EQ(ui.active_id, 0u);
}

/* ----------------------------------------------------------------------- */
/*  R437: collapsing header + radio button                                   */
/* ----------------------------------------------------------------------- */

TEST(imui_toggle_logic_click_flips)
{
    bool open = false;

    /* no click -> state and return unchanged */
    ASSERT_FALSE(imui_toggle_logic(false, &open));
    ASSERT_FALSE(open);

    /* click -> flips and reports the new state */
    ASSERT_TRUE(imui_toggle_logic(true, &open));
    ASSERT_TRUE(open);

    /* held/no-click frames keep the state */
    ASSERT_TRUE(imui_toggle_logic(false, &open));
    ASSERT_TRUE(open);

    /* second click flips back */
    ASSERT_FALSE(imui_toggle_logic(true, &open));
    ASSERT_FALSE(open);

    /* NULL open pointer is a safe no-op reporting "collapsed" */
    ASSERT_FALSE(imui_toggle_logic(true, NULL));
    ASSERT_FALSE(imui_toggle_logic(false, NULL));
}

TEST(imui_radio_logic_writes_option)
{
    i32 value = 0;

    /* no click -> value untouched, selected reflects current value */
    ASSERT_TRUE(imui_radio_logic(false, &value, 0));
    ASSERT_FALSE(imui_radio_logic(false, &value, 2));
    ASSERT_EQ(value, 0);

    /* click -> writes the option */
    ASSERT_TRUE(imui_radio_logic(true, &value, 2));
    ASSERT_EQ(value, 2);

    /* repeated click on the same option is idempotent */
    ASSERT_TRUE(imui_radio_logic(true, &value, 2));
    ASSERT_EQ(value, 2);

    /* selecting another option overwrites */
    ASSERT_TRUE(imui_radio_logic(true, &value, 1));
    ASSERT_EQ(value, 1);

    /* NULL value pointer is a safe no-op */
    ASSERT_FALSE(imui_radio_logic(true, NULL, 3));
    ASSERT_EQ(value, 1);
}

/* Drive a real headless frame through the linked imgui.c: the NULL font makes
 * every draw call a no-op, so the genuine widget logic runs. imui_init(NULL)
 * gives pad 6 / row_h 22; the panel is 200 wide at (0,0), so successive
 * widgets land on rows at y = 6 + row*22 with width 188 — call the widgets
 * in row order within each frame, exactly as the demo panel does. */
static void frame_begin(ImUI *ui, f32 mx, f32 my, bool down)
{
    imui_begin(ui, 800.0f, 600.0f, mx, my, down);
    imui_panel(ui, 0.0f, 0.0f, 200.0f, 400.0f);
}
static void frame_end(ImUI *ui) { imui_end(ui, NULL); }

#define UI_ROW_MID(row) (6.0f + (f32)(row) * 22.0f + 4.0f) /* inside row */

TEST(imui_collapsing_header_click_toggles)
{
    ImUI ui;
    imui_init(&ui, NULL);
    bool open = false;

    /* hover + press down over the header (row 0) */
    frame_begin(&ui, 10.0f, UI_ROW_MID(0), false);
    ASSERT_FALSE(imui_collapsing_header(&ui, 1, "hdr", &open));
    frame_end(&ui);
    frame_begin(&ui, 10.0f, UI_ROW_MID(0), true);
    ASSERT_FALSE(imui_collapsing_header(&ui, 1, "hdr", &open));
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 1u);
    ASSERT_FALSE(open);

    /* release over it -> click -> opens */
    frame_begin(&ui, 10.0f, UI_ROW_MID(0), false);
    ASSERT_TRUE(imui_collapsing_header(&ui, 1, "hdr", &open));
    frame_end(&ui);
    ASSERT_TRUE(open);
    ASSERT_EQ(ui.active_id, 0u);

    /* full second click collapses again */
    frame_begin(&ui, 10.0f, UI_ROW_MID(0), true);
    imui_collapsing_header(&ui, 1, "hdr", &open);
    frame_end(&ui);
    frame_begin(&ui, 10.0f, UI_ROW_MID(0), false);
    ASSERT_FALSE(imui_collapsing_header(&ui, 1, "hdr", &open));
    frame_end(&ui);
    ASSERT_FALSE(open);
}

TEST(imui_radio_widget_selects_option)
{
    ImUI ui;
    imui_init(&ui, NULL);
    i32 value = 0;

    /* click the second radio (row 1, option 1) */
    frame_begin(&ui, 10.0f, UI_ROW_MID(1), true);
    imui_radio(&ui, 10, "a", &value, 0);
    bool c1 = imui_radio(&ui, 11, "b", &value, 1);
    frame_end(&ui);
    ASSERT_FALSE(c1);
    ASSERT_EQ(ui.active_id, 11u);

    frame_begin(&ui, 10.0f, UI_ROW_MID(1), false);
    imui_radio(&ui, 10, "a", &value, 0);
    c1 = imui_radio(&ui, 11, "b", &value, 1);
    frame_end(&ui);
    ASSERT_TRUE(c1);
    ASSERT_EQ(value, 1);

    /* NULL value pointer: widget still reports the click, nothing written */
    frame_begin(&ui, 10.0f, UI_ROW_MID(0), true);
    imui_radio(&ui, 10, "a", NULL, 0);
    frame_end(&ui);
    frame_begin(&ui, 10.0f, UI_ROW_MID(0), false);
    ASSERT_TRUE(imui_radio(&ui, 10, "a", NULL, 0));
    frame_end(&ui);
    ASSERT_EQ(value, 1);
}

TEST(imui_header_radio_button_no_crosstalk)
{
    ImUI ui;
    imui_init(&ui, NULL);
    bool open = false;
    i32 value = 0;

    /* press on the header (row 0) */
    frame_begin(&ui, 10.0f, UI_ROW_MID(0), true);
    imui_collapsing_header(&ui, 1, "hdr", &open);
    imui_radio(&ui, 2, "opt", &value, 7);
    imui_button(&ui, 3, "btn");
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 1u);

    /* drag onto the radio (row 1) while holding: radio must not steal active */
    frame_begin(&ui, 10.0f, UI_ROW_MID(1), true);
    imui_collapsing_header(&ui, 1, "hdr", &open);
    imui_radio(&ui, 2, "opt", &value, 7);
    imui_button(&ui, 3, "btn");
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 1u);
    ASSERT_EQ(ui.hot_id, 2u);
    ASSERT_EQ(value, 0);

    /* release over the radio: header press dies outside, radio not clicked */
    frame_begin(&ui, 10.0f, UI_ROW_MID(1), false);
    imui_collapsing_header(&ui, 1, "hdr", &open);
    imui_radio(&ui, 2, "opt", &value, 7);
    imui_button(&ui, 3, "btn");
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_FALSE(open);
    ASSERT_EQ(value, 0);

    /* a fresh full click on the radio selects its option */
    frame_begin(&ui, 10.0f, UI_ROW_MID(1), true);
    imui_collapsing_header(&ui, 1, "hdr", &open);
    imui_radio(&ui, 2, "opt", &value, 7);
    imui_button(&ui, 3, "btn");
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 2u);
    frame_begin(&ui, 10.0f, UI_ROW_MID(1), false);
    imui_collapsing_header(&ui, 1, "hdr", &open);
    imui_radio(&ui, 2, "opt", &value, 7);
    imui_button(&ui, 3, "btn");
    frame_end(&ui);
    ASSERT_EQ(value, 7);
    ASSERT_FALSE(open);

    /* press the button (row 2), drag outside all rows, release: no click,
     * and neither the header state nor the radio value is disturbed */
    frame_begin(&ui, 10.0f, UI_ROW_MID(2), true);
    imui_collapsing_header(&ui, 1, "hdr", &open);
    imui_radio(&ui, 2, "opt", &value, 7);
    imui_button(&ui, 3, "btn");
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 3u);
    frame_begin(&ui, 10.0f, 300.0f, false);
    imui_collapsing_header(&ui, 1, "hdr", &open);
    imui_radio(&ui, 2, "opt", &value, 7);
    ASSERT_FALSE(imui_button(&ui, 3, "btn"));
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_EQ(value, 7);
    ASSERT_FALSE(open);
}

/* ----------------------------------------------------------------------- */
/*  R441: int slider                                                         */
/* ----------------------------------------------------------------------- */

TEST(imui_slider_int_logic_rounds_and_clamps)
{
    /* round half away from zero around each step boundary */
    ASSERT_EQ(imui_slider_int_logic(0.0f,  0, 3), 0);
    ASSERT_EQ(imui_slider_int_logic(0.49f, 0, 3), 0);
    ASSERT_EQ(imui_slider_int_logic(0.5f,  0, 3), 1);
    ASSERT_EQ(imui_slider_int_logic(1.49f, 0, 3), 1);
    ASSERT_EQ(imui_slider_int_logic(1.5f,  0, 3), 2);
    ASSERT_EQ(imui_slider_int_logic(2.49f, 0, 3), 2);
    ASSERT_EQ(imui_slider_int_logic(2.5f,  0, 3), 3);
    ASSERT_EQ(imui_slider_int_logic(3.0f,  0, 3), 3);

    /* clamp beyond the range on both sides */
    ASSERT_EQ(imui_slider_int_logic(-5.0f, 0, 3), 0);
    ASSERT_EQ(imui_slider_int_logic(99.0f, 0, 3), 3);

    /* negative ranges round away from zero too */
    ASSERT_EQ(imui_slider_int_logic(-0.4f, -2, 2), 0);
    ASSERT_EQ(imui_slider_int_logic(-0.5f, -2, 2), -1);
    ASSERT_EQ(imui_slider_int_logic(-1.5f, -2, 2), -2);
    ASSERT_EQ(imui_slider_int_logic(-9.0f, -2, 2), -2);
    ASSERT_EQ(imui_slider_int_logic( 9.0f, -2, 2), 2);

    /* degenerate range min == max collapses to that value */
    ASSERT_EQ(imui_slider_int_logic(0.7f, 2, 2), 2);
}

TEST(imui_slider_int_widget_drag_maps_steps)
{
    ImUI ui;
    imui_init(&ui, NULL);
    i32 value = 1;

    /* press near the "2" position: mapped = (131-6)/188*3 ~= 1.996 -> 2 */
    frame_begin(&ui, 131.0f, UI_ROW_MID(0), true);
    ASSERT_TRUE(imui_slider_int(&ui, 20, "s", &value, 0, 3));
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 20u);
    ASSERT_EQ(value, 2);

    /* drag to the far left edge -> 0 */
    frame_begin(&ui, 6.0f, UI_ROW_MID(0), true);
    ASSERT_TRUE(imui_slider_int(&ui, 20, "s", &value, 0, 3));
    frame_end(&ui);
    ASSERT_EQ(value, 0);

    /* drag past the right end of the track -> clamped to max */
    frame_begin(&ui, 400.0f, UI_ROW_MID(0), true);
    ASSERT_TRUE(imui_slider_int(&ui, 20, "s", &value, 0, 3));
    frame_end(&ui);
    ASSERT_EQ(value, 3);

    /* holding without moving reports no change */
    frame_begin(&ui, 400.0f, UI_ROW_MID(0), true);
    ASSERT_FALSE(imui_slider_int(&ui, 20, "s", &value, 0, 3));
    frame_end(&ui);

    /* release (anywhere) clears active */
    frame_begin(&ui, 400.0f, UI_ROW_MID(0), false);
    ASSERT_FALSE(imui_slider_int(&ui, 20, "s", &value, 0, 3));
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_EQ(value, 3);
}

TEST(imui_slider_int_safe_reject)
{
    ImUI ui;
    imui_init(&ui, NULL);
    i32 value = 2;

    /* NULL value pointer: refuse, no interaction state touched */
    frame_begin(&ui, 100.0f, UI_ROW_MID(0), true);
    ASSERT_FALSE(imui_slider_int(&ui, 20, "s", NULL, 0, 3));
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_EQ(ui.hot_id, 0u);
    ASSERT_EQ(value, 2);

    /* inverted range: refuse, value untouched */
    frame_begin(&ui, 100.0f, UI_ROW_MID(0), true);
    ASSERT_FALSE(imui_slider_int(&ui, 20, "s", &value, 3, 0));
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_EQ(value, 2);
}

TEST(imui_slider_int_float_no_crosstalk)
{
    ImUI ui;
    imui_init(&ui, NULL);
    i32 ivalue = 1;
    f32 fvalue = 5.0f;

    /* press the int slider (row 0), drag down onto the float slider (row 1):
     * the float slider must not steal active and its value stays put */
    frame_begin(&ui, 131.0f, UI_ROW_MID(0), true);
    imui_slider_int(&ui, 20, "i", &ivalue, 0, 3);
    imui_slider_float(&ui, 21, "f", &fvalue, 0.0f, 10.0f);
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 20u);
    ASSERT_EQ(ivalue, 2);

    frame_begin(&ui, 131.0f, UI_ROW_MID(1), true);
    imui_slider_int(&ui, 20, "i", &ivalue, 0, 3);
    imui_slider_float(&ui, 21, "f", &fvalue, 0.0f, 10.0f);
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 20u);
    ASSERT_FLOAT_EQ(fvalue, 5.0f, 1e-4f);

    /* release over the float slider: int drag ends, float still untouched */
    frame_begin(&ui, 131.0f, UI_ROW_MID(1), false);
    imui_slider_int(&ui, 20, "i", &ivalue, 0, 3);
    imui_slider_float(&ui, 21, "f", &fvalue, 0.0f, 10.0f);
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_FLOAT_EQ(fvalue, 5.0f, 1e-4f);

    /* a fresh press-drag on the float slider works and leaves ivalue alone */
    frame_begin(&ui, 6.0f, UI_ROW_MID(1), true);
    imui_slider_int(&ui, 20, "i", &ivalue, 0, 3);
    ASSERT_TRUE(imui_slider_float(&ui, 21, "f", &fvalue, 0.0f, 10.0f));
    frame_end(&ui);
    ASSERT_EQ(ui.active_id, 21u);
    ASSERT_FLOAT_EQ(fvalue, 0.0f, 1e-4f);
    ASSERT_EQ(ivalue, 2);
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
    RUN_TEST(imui_hidden_reset_no_stale_click);
    RUN_TEST(imui_toggle_logic_click_flips);
    RUN_TEST(imui_radio_logic_writes_option);
    RUN_TEST(imui_collapsing_header_click_toggles);
    RUN_TEST(imui_radio_widget_selects_option);
    RUN_TEST(imui_header_radio_button_no_crosstalk);
    RUN_TEST(imui_slider_int_logic_rounds_and_clamps);
    RUN_TEST(imui_slider_int_widget_drag_maps_steps);
    RUN_TEST(imui_slider_int_safe_reject);
    RUN_TEST(imui_slider_int_float_no_crosstalk);
TEST_MAIN_END()
