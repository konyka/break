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

/* Drive a headless frame the way the widgets do: the test links no imgui.c
 * (it would drag in the GPU font renderer), so we replicate each widget's
 * exact call sequence — hit test, imui_press_logic, then the R437 helper —
 * against the ImUI state fields directly, matching the imui_press_* tests. */
static void r437_begin(ImUI *ui, f32 mx, f32 my, bool down)
{
    ui->mouse_x = mx;
    ui->mouse_y = my;
    ui->mouse_down = down;
    ui->hot_id = 0;
}
static void r437_end(ImUI *ui) { ui->mouse_prev_down = ui->mouse_down; }

/* Row geometry mirrors imgui.c: panel pad 6, row_h 22, widget height 18. */
#define R437_ROW_Y(row) (6.0f + (f32)(row) * 22.0f)
#define R437_ROW_H 18.0f

/* exact logic of imui_collapsing_header (imgui.c) minus rendering */
static bool r437_header(ImUI *ui, u32 id, int row, bool *open)
{
    bool hovered = imui_hit(ui->mouse_x, ui->mouse_y, 6.0f, R437_ROW_Y(row), 188.0f, R437_ROW_H);
    bool clicked = imui_press_logic(id, hovered, ui->mouse_down, ui->mouse_prev_down,
                                    &ui->hot_id, &ui->active_id);
    return imui_toggle_logic(clicked, open);
}

/* exact logic of imui_radio (imgui.c) minus rendering */
static bool r437_radio(ImUI *ui, u32 id, int row, i32 *value, i32 option)
{
    bool hovered = imui_hit(ui->mouse_x, ui->mouse_y, 6.0f, R437_ROW_Y(row), 188.0f, 14.0f);
    bool clicked = imui_press_logic(id, hovered, ui->mouse_down, ui->mouse_prev_down,
                                    &ui->hot_id, &ui->active_id);
    imui_radio_logic(clicked, value, option);
    return clicked;
}

/* exact logic of imui_button (imgui.c) minus rendering */
static bool r437_button(ImUI *ui, u32 id, int row)
{
    bool hovered = imui_hit(ui->mouse_x, ui->mouse_y, 6.0f, R437_ROW_Y(row), 188.0f, R437_ROW_H);
    return imui_press_logic(id, hovered, ui->mouse_down, ui->mouse_prev_down,
                            &ui->hot_id, &ui->active_id);
}

#define R437_MID(row) (R437_ROW_Y(row) + 4.0f) /* a point inside the row */

TEST(imui_collapsing_header_click_toggles)
{
    ImUI ui;
    memset(&ui, 0, sizeof(ui));
    bool open = false;

    /* hover + press down over the header (row 0) */
    r437_begin(&ui, 10.0f, R437_MID(0), false);
    ASSERT_FALSE(r437_header(&ui, 1, 0, &open));
    r437_end(&ui);
    r437_begin(&ui, 10.0f, R437_MID(0), true);
    ASSERT_FALSE(r437_header(&ui, 1, 0, &open));
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 1u);
    ASSERT_FALSE(open);

    /* release over it -> click -> opens */
    r437_begin(&ui, 10.0f, R437_MID(0), false);
    ASSERT_TRUE(r437_header(&ui, 1, 0, &open));
    r437_end(&ui);
    ASSERT_TRUE(open);
    ASSERT_EQ(ui.active_id, 0u);

    /* full second click collapses again */
    r437_begin(&ui, 10.0f, R437_MID(0), true);
    r437_header(&ui, 1, 0, &open);
    r437_end(&ui);
    r437_begin(&ui, 10.0f, R437_MID(0), false);
    ASSERT_FALSE(r437_header(&ui, 1, 0, &open));
    r437_end(&ui);
    ASSERT_FALSE(open);
}

TEST(imui_radio_widget_selects_option)
{
    ImUI ui;
    memset(&ui, 0, sizeof(ui));
    i32 value = 0;

    /* click the second radio (row 1, option 1) */
    r437_begin(&ui, 10.0f, R437_MID(1), true);
    r437_radio(&ui, 10, 0, &value, 0);
    bool c1 = r437_radio(&ui, 11, 1, &value, 1);
    r437_end(&ui);
    ASSERT_FALSE(c1);
    ASSERT_EQ(ui.active_id, 11u);

    r437_begin(&ui, 10.0f, R437_MID(1), false);
    r437_radio(&ui, 10, 0, &value, 0);
    c1 = r437_radio(&ui, 11, 1, &value, 1);
    r437_end(&ui);
    ASSERT_TRUE(c1);
    ASSERT_EQ(value, 1);

    /* NULL value pointer: widget still reports the click, nothing written */
    r437_begin(&ui, 10.0f, R437_MID(0), true);
    r437_radio(&ui, 10, 0, NULL, 0);
    r437_end(&ui);
    r437_begin(&ui, 10.0f, R437_MID(0), false);
    ASSERT_TRUE(r437_radio(&ui, 10, 0, NULL, 0));
    r437_end(&ui);
    ASSERT_EQ(value, 1);
}

TEST(imui_header_radio_button_no_crosstalk)
{
    ImUI ui;
    memset(&ui, 0, sizeof(ui));
    bool open = false;
    i32 value = 0;

    /* press on the header (row 0) */
    r437_begin(&ui, 10.0f, R437_MID(0), true);
    r437_header(&ui, 1, 0, &open);
    r437_radio(&ui, 2, 1, &value, 7);
    r437_button(&ui, 3, 2);
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 1u);

    /* drag onto the radio (row 1) while holding: radio must not steal active */
    r437_begin(&ui, 10.0f, R437_MID(1), true);
    r437_header(&ui, 1, 0, &open);
    r437_radio(&ui, 2, 1, &value, 7);
    r437_button(&ui, 3, 2);
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 1u);
    ASSERT_EQ(ui.hot_id, 2u);
    ASSERT_EQ(value, 0);

    /* release over the radio: header press dies outside, radio not clicked */
    r437_begin(&ui, 10.0f, R437_MID(1), false);
    r437_header(&ui, 1, 0, &open);
    r437_radio(&ui, 2, 1, &value, 7);
    r437_button(&ui, 3, 2);
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_FALSE(open);
    ASSERT_EQ(value, 0);

    /* a fresh full click on the radio selects its option */
    r437_begin(&ui, 10.0f, R437_MID(1), true);
    r437_header(&ui, 1, 0, &open);
    r437_radio(&ui, 2, 1, &value, 7);
    r437_button(&ui, 3, 2);
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 2u);
    r437_begin(&ui, 10.0f, R437_MID(1), false);
    r437_header(&ui, 1, 0, &open);
    r437_radio(&ui, 2, 1, &value, 7);
    r437_button(&ui, 3, 2);
    r437_end(&ui);
    ASSERT_EQ(value, 7);
    ASSERT_FALSE(open);

    /* press the button (row 2), drag outside all rows, release: no click,
     * and neither the header state nor the radio value is disturbed */
    r437_begin(&ui, 10.0f, R437_MID(2), true);
    r437_header(&ui, 1, 0, &open);
    r437_radio(&ui, 2, 1, &value, 7);
    r437_button(&ui, 3, 2);
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 3u);
    r437_begin(&ui, 10.0f, 300.0f, false);
    r437_header(&ui, 1, 0, &open);
    r437_radio(&ui, 2, 1, &value, 7);
    ASSERT_FALSE(r437_button(&ui, 3, 2));
    r437_end(&ui);
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

/* exact logic of imui_slider_int (imgui.c) minus rendering — track width and
 * row geometry mirror the widget (pad 6, panel_w 200 -> w 188, h 16) */
static bool r441_slider_int(ImUI *ui, u32 id, int row, i32 *value, i32 minv, i32 maxv)
{
    if (!value || minv > maxv) return false; /* R441: safe reject */
    bool hovered = imui_hit(ui->mouse_x, ui->mouse_y, 6.0f, R437_ROW_Y(row), 188.0f, 16.0f);
    bool changed = false;
    bool pressed_now = ui->mouse_down && !ui->mouse_prev_down;
    if (hovered) ui->hot_id = id;
    if (ui->active_id == id) {
        if (ui->mouse_down) {
            f32 mapped = imui_slider_map(ui->mouse_x, 6.0f, 188.0f, (f32)minv, (f32)maxv);
            i32 nv = imui_slider_int_logic(mapped, minv, maxv);
            if (nv != *value) { *value = nv; changed = true; }
        } else {
            ui->active_id = 0;
        }
    } else if (hovered && pressed_now && ui->active_id == 0) {
        ui->active_id = id;
        f32 mapped = imui_slider_map(ui->mouse_x, 6.0f, 188.0f, (f32)minv, (f32)maxv);
        i32 nv = imui_slider_int_logic(mapped, minv, maxv);
        if (nv != *value) { *value = nv; changed = true; }
    }
    return changed;
}

/* exact logic of imui_slider_float (imgui.c) minus rendering */
static bool r441_slider_float(ImUI *ui, u32 id, int row, f32 *value, f32 minv, f32 maxv)
{
    bool hovered = imui_hit(ui->mouse_x, ui->mouse_y, 6.0f, R437_ROW_Y(row), 188.0f, 16.0f);
    bool changed = false;
    bool pressed_now = ui->mouse_down && !ui->mouse_prev_down;
    if (hovered) ui->hot_id = id;
    if (ui->active_id == id) {
        if (ui->mouse_down) {
            if (value) {
                f32 nv = imui_slider_map(ui->mouse_x, 6.0f, 188.0f, minv, maxv);
                if (nv != *value) { *value = nv; changed = true; }
            }
        } else {
            ui->active_id = 0;
        }
    } else if (hovered && pressed_now && ui->active_id == 0) {
        ui->active_id = id;
        if (value) {
            f32 nv = imui_slider_map(ui->mouse_x, 6.0f, 188.0f, minv, maxv);
            if (nv != *value) { *value = nv; changed = true; }
        }
    }
    return changed;
}

TEST(imui_slider_int_widget_drag_maps_steps)
{
    ImUI ui;
    memset(&ui, 0, sizeof(ui));
    i32 value = 1;

    /* press near the "2" position: mapped = (131-6)/188*3 ~= 1.996 -> 2 */
    r437_begin(&ui, 131.0f, R437_MID(0), true);
    ASSERT_TRUE(r441_slider_int(&ui, 20, 0, &value, 0, 3));
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 20u);
    ASSERT_EQ(value, 2);

    /* drag to the far left edge -> 0 */
    r437_begin(&ui, 6.0f, R437_MID(0), true);
    ASSERT_TRUE(r441_slider_int(&ui, 20, 0, &value, 0, 3));
    r437_end(&ui);
    ASSERT_EQ(value, 0);

    /* drag past the right end of the track -> clamped to max */
    r437_begin(&ui, 400.0f, R437_MID(0), true);
    ASSERT_TRUE(r441_slider_int(&ui, 20, 0, &value, 0, 3));
    r437_end(&ui);
    ASSERT_EQ(value, 3);

    /* holding without moving reports no change */
    r437_begin(&ui, 400.0f, R437_MID(0), true);
    ASSERT_FALSE(r441_slider_int(&ui, 20, 0, &value, 0, 3));
    r437_end(&ui);

    /* release (anywhere) clears active */
    r437_begin(&ui, 400.0f, R437_MID(0), false);
    ASSERT_FALSE(r441_slider_int(&ui, 20, 0, &value, 0, 3));
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_EQ(value, 3);
}

TEST(imui_slider_int_safe_reject)
{
    ImUI ui;
    memset(&ui, 0, sizeof(ui));
    i32 value = 2;

    /* NULL value pointer: refuse, no interaction state touched */
    r437_begin(&ui, 100.0f, R437_MID(0), true);
    ASSERT_FALSE(r441_slider_int(&ui, 20, 0, NULL, 0, 3));
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_EQ(ui.hot_id, 0u);
    ASSERT_EQ(value, 2);

    /* inverted range: refuse, value untouched */
    r437_begin(&ui, 100.0f, R437_MID(0), true);
    ASSERT_FALSE(r441_slider_int(&ui, 20, 0, &value, 3, 0));
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_EQ(value, 2);
}

TEST(imui_slider_int_float_no_crosstalk)
{
    ImUI ui;
    memset(&ui, 0, sizeof(ui));
    i32 ivalue = 1;
    f32 fvalue = 5.0f;

    /* press the int slider (row 0), drag down onto the float slider (row 1):
     * the float slider must not steal active and its value stays put */
    r437_begin(&ui, 131.0f, R437_MID(0), true);
    r441_slider_int(&ui, 20, 0, &ivalue, 0, 3);
    r441_slider_float(&ui, 21, 1, &fvalue, 0.0f, 10.0f);
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 20u);
    ASSERT_EQ(ivalue, 2);

    r437_begin(&ui, 131.0f, R437_MID(1), true);
    r441_slider_int(&ui, 20, 0, &ivalue, 0, 3);
    r441_slider_float(&ui, 21, 1, &fvalue, 0.0f, 10.0f);
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 20u);
    ASSERT_FLOAT_EQ(fvalue, 5.0f, 1e-4f);

    /* release over the float slider: int drag ends, float still untouched */
    r437_begin(&ui, 131.0f, R437_MID(1), false);
    r441_slider_int(&ui, 20, 0, &ivalue, 0, 3);
    r441_slider_float(&ui, 21, 1, &fvalue, 0.0f, 10.0f);
    r437_end(&ui);
    ASSERT_EQ(ui.active_id, 0u);
    ASSERT_FLOAT_EQ(fvalue, 5.0f, 1e-4f);

    /* a fresh press-drag on the float slider works and leaves ivalue alone */
    r437_begin(&ui, 6.0f, R437_MID(1), true);
    r441_slider_int(&ui, 20, 0, &ivalue, 0, 3);
    ASSERT_TRUE(r441_slider_float(&ui, 21, 1, &fvalue, 0.0f, 10.0f));
    r437_end(&ui);
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
