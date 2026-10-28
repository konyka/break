/* Widget paint rules the editor theme depends on (soft canvas, pixel reads):
 *  - a button's border follows its rounded corners and border_width;
 *  - a plain container paints bg_color only when the theme sets it;
 *  - a label leaves its parent's colour when the theme gives it no bg. */
#include "test_framework.h"

#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/my_css.h"
#include "myui/my_theme.h"
#include "myui/my_widget.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_label.h"

#define W 80u
#define H 40u

typedef struct {
    my_lcd_t *lcd;
    my_vgcanvas_t *vg;
    my_theme_t *theme;
    my_widget_t *root;
} Fx;

static void fx_open(Fx *fx, const char *css) {
    memset(fx, 0, sizeof(*fx));
    fx->lcd = my_lcd_mem_create(NULL, W, H, MY_PIXEL_FORMAT_BGRA8888);
    fx->vg = my_vgcanvas_soft_create(NULL, fx->lcd);
    fx->theme = my_theme_create(NULL);
    ASSERT_TRUE(fx->lcd != NULL && fx->vg != NULL && fx->theme != NULL);
    ASSERT_EQ(my_theme_load_css(fx->theme, css), MY_RET_OK);
    fx->root = my_widget_create(NULL, "root");
    ASSERT_NOT_NULL(fx->root);
    fx->root->theme = fx->theme;
    { my_rect_t r_ = {0, 0, (int32_t)W, (int32_t)H}; (void)my_widget_set_rect(fx->root, &r_); }
}

static void fx_paint(Fx *fx) {
    ASSERT_EQ(my_vgcanvas_begin_frame(fx->vg, NULL), MY_RET_OK);
    /* the window would clear to its bg; use a known colour */
    my_vgcanvas_set_fill_color(fx->vg, my_color_rgb(10, 20, 30));
    (void)my_vgcanvas_fill_rect(fx->vg, &(my_rectf_t){0, 0, (float)W, (float)H});
    my_widget_paint(fx->root, fx->vg);
    ASSERT_EQ(my_vgcanvas_end_frame(fx->vg), MY_RET_OK);
}

/* BGRA8888 -> 0xRRGGBB */
static uint32_t px(Fx *fx, uint32_t x, uint32_t y) {
    const uint8_t *b = my_lcd_mem_get_buffer(fx->lcd);
    uint32_t stride = my_lcd_mem_get_stride(fx->lcd);
    const uint8_t *p = b + (size_t)y * stride + (size_t)x * 4u;
    return ((uint32_t)p[2] << 16) | ((uint32_t)p[1] << 8) | p[0];
}

static void fx_close(Fx *fx) {
    my_widget_unref(fx->root);
    my_theme_destroy(fx->theme);
    my_vgcanvas_destroy(fx->vg);
    my_lcd_destroy(fx->lcd);
}

static my_widget_t *add_button(Fx *fx, const char *text) {
    my_widget_t *b = my_button_create(NULL, text);
    if (b == NULL) return NULL;
    { my_rect_t r_ = {10, 10, 40, 20}; (void)my_widget_set_rect(b, &r_); }
    if (my_widget_add_child(fx->root, b) != MY_RET_OK) {
        my_widget_unref(b);
        return NULL;
    }
    my_widget_unref(b);
    return b;
}

TEST(button_border_follows_rounded_corners) {
    Fx fx;
    fx_open(&fx, "button { background-color: #2b2d30; border-color: #ff0000;"
                 " border-radius: 6px; border-width: 1px; color: #dfe1e5; }");
    (void)add_button(&fx, "");
    fx_paint(&fx);
    /* the outer corner pixel lies outside a 6 px radius: parent colour, no
     * red square-corner border */
    ASSERT_EQ(px(&fx, 10, 10), 0x0a141eu);
    ASSERT_EQ(px(&fx, 49, 29), 0x0a141eu);
    /* the straight edges still carry the border */
    {
        uint32_t top = px(&fx, 30, 10);
        ASSERT_TRUE(((top >> 16) & 0xffu) > 0x80u); /* red-dominant */
    }
    /* inside: the button background */
    ASSERT_EQ(px(&fx, 30, 20), 0x2b2d30u);
    fx_close(&fx);
}

TEST(button_border_width_zero_draws_no_border) {
    Fx fx;
    fx_open(&fx, "button { background-color: #2b2d30; border-color: #ff0000;"
                 " border-radius: 0px; border-width: 0px; }");
    (void)add_button(&fx, "");
    fx_paint(&fx);
    ASSERT_EQ(px(&fx, 30, 10), 0x2b2d30u);
    ASSERT_EQ(px(&fx, 10, 20), 0x2b2d30u);
    fx_close(&fx);
}

TEST(container_paints_bg_only_when_themed) {
    Fx fx;
    my_widget_t *panel;
    fx_open(&fx, "#themed { background-color: #393b40; }");
    panel = my_widget_create(NULL, "themed");
    { my_rect_t r_ = {0, 0, 40, 40}; (void)my_widget_set_rect(panel, &r_); }
    ASSERT_EQ(my_widget_add_child(fx.root, panel), MY_RET_OK);
    my_widget_unref(panel);
    panel = my_widget_create(NULL, "plain");
    { my_rect_t r_ = {40, 0, 40, 40}; (void)my_widget_set_rect(panel, &r_); }
    ASSERT_EQ(my_widget_add_child(fx.root, panel), MY_RET_OK);
    my_widget_unref(panel);
    fx_paint(&fx);
    ASSERT_EQ(px(&fx, 20, 20), 0x393b40u);
    ASSERT_EQ(px(&fx, 60, 20), 0x0a141eu); /* unthemed stays transparent */
    ASSERT_EQ(px(&fx, 2, 2), 0x393b40u);   /* whole themed panel, edges too */
    fx_close(&fx);
}

TEST(label_without_bg_rule_leaves_parent_colour) {
    Fx fx;
    my_widget_t *l;
    fx_open(&fx, "label { color: #dfe1e5; }");
    l = my_label_create(NULL, "");
    { my_rect_t r_ = {0, 0, 80, 40}; (void)my_widget_set_rect(l, &r_); }
    ASSERT_EQ(my_widget_add_child(fx.root, l), MY_RET_OK);
    my_widget_unref(l);
    fx_paint(&fx);
    /* (sampled off-centre: without a font the soft canvas draws a
     * placeholder bar for the text in the middle) */
    ASSERT_EQ(px(&fx, 4, 4), 0x0a141eu);
    fx_close(&fx);
}

TEST(label_with_bg_rule_paints_it) {
    Fx fx;
    my_widget_t *l;
    fx_open(&fx, "label { background-color: #1e1f22; }");
    l = my_label_create(NULL, "");
    { my_rect_t r_ = {0, 0, 80, 40}; (void)my_widget_set_rect(l, &r_); }
    ASSERT_EQ(my_widget_add_child(fx.root, l), MY_RET_OK);
    my_widget_unref(l);
    fx_paint(&fx);
    ASSERT_EQ(px(&fx, 4, 4), 0x1e1f22u);
    fx_close(&fx);
}

TEST_MAIN_BEGIN()
    RUN_TEST(button_border_follows_rounded_corners);
    RUN_TEST(button_border_width_zero_draws_no_border);
    RUN_TEST(container_paints_bg_only_when_themed);
    RUN_TEST(label_without_bg_rule_leaves_parent_colour);
    RUN_TEST(label_with_bg_rule_paints_it);
TEST_MAIN_END()
