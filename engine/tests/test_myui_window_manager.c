#include "test_framework.h"

#include <stdlib.h>

#include "mypal/dummy/my_pal_dummy.h"
#include "mypal/my_event.h"
#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/my_layout.h"
#include "myui/my_window_manager.h"
#include "myui/widgets/my_dialog.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_text_area.h"

static int g_open_count;
static my_window_manager_t* g_hook_wm;
static my_window_t* g_hook_win;
static void* g_hook_ctx;
static void on_open_cb(my_window_manager_t* wm, my_window_t* win, void* ctx) {
  g_open_count++;
  g_hook_wm = wm;
  g_hook_win = win;
  g_hook_ctx = ctx;
}

typedef struct text_area_fail_alloc_t {
  bool fail;
} text_area_fail_alloc_t;

typedef struct text_area_count_alloc_t {
  size_t alloc_calls;
} text_area_count_alloc_t;

static void* text_area_count_alloc(void* ctx, size_t size) {
  text_area_count_alloc_t* state = (text_area_count_alloc_t*)ctx;
  void* ptr = malloc(size);
  if (ptr != NULL) state->alloc_calls++;
  return ptr;
}

static void* text_area_count_calloc(void* ctx, size_t count, size_t size) {
  text_area_count_alloc_t* state = (text_area_count_alloc_t*)ctx;
  void* ptr = calloc(count, size);
  if (ptr != NULL) state->alloc_calls++;
  return ptr;
}

static void* text_area_count_realloc(void* ctx, void* ptr, size_t size) {
  text_area_count_alloc_t* state = (text_area_count_alloc_t*)ctx;
  void* grown = realloc(ptr, size);
  if (grown != NULL && grown != ptr) state->alloc_calls++;
  return grown;
}

static void text_area_count_free(void* ctx, void* ptr) {
  (void)ctx;
  free(ptr);
}

static void* text_area_fail_alloc(void* ctx, size_t size) {
  text_area_fail_alloc_t* state = (text_area_fail_alloc_t*)ctx;
  return state->fail ? NULL : malloc(size);
}

static void* text_area_fail_calloc(void* ctx, size_t count, size_t size) {
  text_area_fail_alloc_t* state = (text_area_fail_alloc_t*)ctx;
  return state->fail ? NULL : calloc(count, size);
}

static void* text_area_fail_realloc(void* ctx, void* ptr, size_t size) {
  text_area_fail_alloc_t* state = (text_area_fail_alloc_t*)ctx;
  return state->fail ? NULL : realloc(ptr, size);
}

static void text_area_fail_free(void* ctx, void* ptr) {
  (void)ctx;
  free(ptr);
}

typedef struct text_area_variable_font_t {
  my_font_t base;
} text_area_variable_font_t;

static my_ret_t text_area_variable_font_measure(my_font_t* font,
                                                const char* text, int32_t size,
                                                int32_t* width, int32_t* height) {
  const char* p = text;
  int32_t total = 0;
  (void)font;
  if (text == NULL || size <= 0 || width == NULL) return MY_RET_INVALID_PARAMS;
  while (*p != '\0') {
    total += *p == 'A' ? 5 : 20;
    p++;
  }
  *width = total;
  if (height != NULL) *height = size;
  return MY_RET_OK;
}

static my_ret_t text_area_variable_font_glyph(my_font_t* font,
                                              uint32_t codepoint, int32_t size,
                                              my_glyph_t* glyph) {
  (void)font;
  if (glyph == NULL || size <= 0) return MY_RET_INVALID_PARAMS;
  memset(glyph, 0, sizeof(*glyph));
  glyph->advance = codepoint == 'A' ? 5 : 20;
  return MY_RET_OK;
}

static int32_t text_area_variable_font_ascent(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static int32_t text_area_variable_font_descent(my_font_t* font, int32_t size) {
  (void)font;
  (void)size;
  return 0;
}

static int32_t text_area_variable_font_line_height(my_font_t* font,
                                                   int32_t size) {
  (void)font;
  return size + 8;
}

static void text_area_variable_font_destroy(my_font_t* font) { (void)font; }

static bool text_area_variable_font_has_glyph(my_font_t* font,
                                              uint32_t codepoint) {
  (void)font;
  return codepoint == 'A' || codepoint == 'B';
}

static const my_font_vtable_t text_area_variable_font_vtable = {
    text_area_variable_font_measure,
    text_area_variable_font_glyph,
    text_area_variable_font_ascent,
    text_area_variable_font_descent,
    text_area_variable_font_line_height,
    text_area_variable_font_destroy,
    text_area_variable_font_has_glyph,
    NULL,
    NULL};

static int g_result = -999;
static int g_main_clicks;
static int g_dialog_clicks;
static int g_user_events;
static void on_result(void* ctx, int32_t result) {
  (void)ctx;
  g_result = result;
}

static void count_click(void* ctx, const char* event, void* data) {
  int* count = (int*)ctx;
  (void)event;
  (void)data;
  (*count)++;
}

static void dispatch_button_click(my_window_manager_t* wm, int32_t x,
                                  int32_t y) {
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = x;
  event.u.pointer.y = y;
  event.u.pointer.button = 1;
  (void)my_window_manager_dispatch_surface_event(wm, &event);
  event.type = MY_EVENT_POINTER_UP;
  (void)my_window_manager_dispatch_surface_event(wm, &event);
}

static void count_user(void* ctx, const char* event, void* data) {
  int* marker = (int*)data;
  (void)event;
  ASSERT_TRUE(marker == &g_user_events);
  (*(int*)ctx)++;
}

static void close_window_from_user_event(void* ctx, const char* event,
                                         void* data) {
  my_window_manager_t* wm = (my_window_manager_t*)ctx;
  (void)event;
  (void)data;
  (void)my_window_manager_close(wm, my_window_manager_top(wm));
}

static void pump(my_pal_t* pal, my_pal_main_loop_t* loop) {
  my_pal_dummy_set_now_ms(pal, 10000);
  (void)my_pal_main_loop_run(loop);
}

typedef struct bubbling_mutation_ctx_t {
  my_widget_t *root;
  my_widget_t *removed_parent;
  my_widget_t *removed_leaf;
  int parent_events;
} bubbling_mutation_ctx_t;

static my_ret_t mutation_leaf_event(my_widget_t *widget,
                                    const my_event_t *event) {
  bubbling_mutation_ctx_t *ctx =
      (bubbling_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)event;
  (void)my_widget_remove_child(ctx->root, ctx->removed_parent);
  return MY_RET_FAIL;
}

static my_ret_t detached_parent_event(my_widget_t *widget,
                                      const my_event_t *event) {
  bubbling_mutation_ctx_t *ctx =
      (bubbling_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)event;
  ctx->parent_events++;
  return MY_RET_OK;
}

static my_ret_t self_removing_leaf_event(my_widget_t *widget,
                                         const my_event_t *event) {
  (void)event;
  (void)my_widget_remove_child(widget->parent, widget);
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_mutation_leaf_vtable = {
    NULL, mutation_leaf_event, NULL, NULL};
static const my_widget_vtable_t s_self_removing_leaf_vtable = {
    NULL, self_removing_leaf_event, NULL, NULL};
static const my_widget_vtable_t s_detached_parent_vtable = {
    NULL, detached_parent_event, NULL, NULL};

typedef struct surface_focus_ctx_t {
  int key_down;
} surface_focus_ctx_t;

static my_ret_t surface_focus_event(my_widget_t *widget,
                                    const my_event_t *event) {
  surface_focus_ctx_t *ctx =
      (surface_focus_ctx_t *)my_widget_get_user_data(widget);
  if (event->type == MY_EVENT_KEY_DOWN) {
    ctx->key_down++;
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_surface_focus_vtable = {
    NULL, surface_focus_event, NULL, NULL};

typedef struct paint_stack_mutation_ctx_t {
  my_window_manager_t *wm;
  my_window_t *window;
  int paint_count;
} paint_stack_mutation_ctx_t;

static void close_window_on_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
  paint_stack_mutation_ctx_t *ctx =
      (paint_stack_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)vg;
  ctx->paint_count++;
  (void)my_window_manager_close(ctx->wm, ctx->window);
}

static void count_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
  paint_stack_mutation_ctx_t *ctx =
      (paint_stack_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)vg;
  ctx->paint_count++;
}

static const my_widget_vtable_t s_close_window_on_paint_vtable = {
    close_window_on_paint, NULL, NULL, NULL};
static const my_widget_vtable_t s_count_paint_vtable = {count_paint, NULL,
                                                         NULL, NULL};

TEST(injected_canvas_inherits_window_scale)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;
  my_vgcanvas_t* canvas;
  my_lcd_t* lcd;
  uint8_t* pixels;
  uint32_t stride;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_scale_factor(pal, 2.0f);
  win = my_window_create(NULL, pal, 100, 50, "hidpi");
  ASSERT_NOT_NULL(win);
  lcd = my_pal_window_get_lcd(win->pal_window);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);

  my_window_set_vgcanvas(win, canvas);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_fill_color(canvas, my_color_rgb(255, 0, 0)),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(canvas, &(my_rectf_t){0, 0, 10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  ASSERT_EQ(pixels[(size_t)15 * stride + (size_t)15 * 4 + 2], 255);

  my_vgcanvas_destroy(canvas);
  my_object_unref((my_object_t*)win);
  my_pal_destroy(pal);
}

TEST(dynamic_scale_reconfigures_injected_canvas_without_resize)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;
  my_vgcanvas_t* canvas;
  my_lcd_t* lcd;
  uint8_t* pixels;
  uint32_t stride;

  ASSERT_NOT_NULL(pal);
  win = my_window_create(NULL, pal, 100, 50, "dynamic-scale");
  ASSERT_NOT_NULL(win);
  /* The injected target deliberately has headroom for the new backing scale. */
  lcd = my_lcd_mem_create(NULL, 200, 100, MY_PIXEL_FORMAT_BGRA8888);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  my_window_set_vgcanvas(win, canvas);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_fill_color(canvas, my_color_rgb(255, 0, 0)),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(canvas, &(my_rectf_t){0, 0, 10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  ASSERT_EQ(pixels[(size_t)15 * stride + (size_t)15 * 4 + 2], 0);

  my_dirty_rects_clear(&win->dirty);
  my_pal_dummy_set_scale_factor(pal, 2.0f);
  ASSERT_TRUE(my_window_refresh_scale(win));
  ASSERT_EQ(win->scale, 2.0f);
  ASSERT_EQ(((my_widget_t*)win)->rect.w, 100);
  ASSERT_EQ(((my_widget_t*)win)->rect.h, 50);
  ASSERT_TRUE(my_dirty_rects_count(&win->dirty) > 0);
  ASSERT_TRUE(!my_window_refresh_scale(win));

  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(canvas, &(my_rectf_t){0, 0, 10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(pixels[(size_t)15 * stride + (size_t)15 * 4 + 2], 255);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_object_unref((my_object_t*)win);
  my_pal_destroy(pal);
}

TEST(floating_plain_widget_does_not_crash_hit_test)
{
  my_widget_t* root = my_widget_create(NULL, "root");
  my_widget_t* overlay = my_widget_create(NULL, "overlay");

  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(overlay);
  ASSERT_EQ(my_widget_set_rect(root, &(my_rect_t){0, 0, 100, 100}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(overlay, &(my_rect_t){10, 10, 40, 40}),
            MY_RET_OK);
  overlay->floating = true;
  ASSERT_EQ(my_widget_add_child(root, overlay), MY_RET_OK);
  ASSERT_TRUE(my_widget_hit_test(root, 20, 20) == root);

  my_widget_unref(overlay);
  my_widget_unref(root);
}

TEST(text_area_grows_capacity_exponentially)
{
  my_widget_t* area = my_text_area_create(NULL);
  char text[257];
  size_t length;
  size_t previous_capacity;

  ASSERT_NOT_NULL(area);
  previous_capacity = ((my_text_area_t*)area)->text_cap;
  memset(text, 'x', sizeof(text) - 1);
  text[sizeof(text) - 1] = '\0';
  for (length = 1; length < sizeof(text); length++) {
    text[length - 1] = 'x';
    text[length] = '\0';
    ASSERT_EQ(my_text_area_set_text(area, text), MY_RET_OK);
    ASSERT_TRUE(((my_text_area_t*)area)->text_cap >= length + 1);
    ASSERT_TRUE(((my_text_area_t*)area)->text_cap >= previous_capacity);
    previous_capacity = ((my_text_area_t*)area)->text_cap;
  }
  ASSERT_TRUE(((my_text_area_t*)area)->text_cap > strlen(text) + 1);
  my_widget_unref(area);
}

TEST(text_area_wrap_rebuilds_after_edit)
{
  my_widget_t* area = my_text_area_create(NULL);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 20, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "ab"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  ASSERT_EQ(my_text_area_set_text(area, "a"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  ASSERT_EQ(my_text_area_set_text(area, "abc\ndef"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 6u);
  my_widget_unref(area);
}

TEST(text_area_wrap_reuses_unchanged_prefix_after_edit)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* prefix;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 20, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa\nbb\ncc"), MY_RET_OK);
  prefix = my_text_area_visual_line_at(area, 0);
  ASSERT_NOT_NULL(prefix);
  ((my_text_area_t*)area)->cursor_row = 1;
  ((my_text_area_t*)area)->cursor_col = 1;
  ((my_text_area_t*)area)->anchor_row = 1;
  ((my_text_area_t*)area)->anchor_col = 1;
  ((my_text_area_t*)area)->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aa\nbxb\ncc");
  ASSERT_TRUE(my_text_area_visual_line_at(area, 0) == prefix);
  my_widget_unref(area);
}

TEST(text_area_line_number_gutter_has_bounded_width)
{
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(area);
  ASSERT_FALSE(my_text_area_line_numbers_enabled(area));
  ASSERT_EQ(my_text_area_content_left(area), 4);
  ASSERT_EQ(my_text_area_set_line_numbers(area, true), MY_RET_OK);
  ASSERT_TRUE(my_text_area_line_numbers_enabled(area));
  ASSERT_TRUE(my_text_area_content_left(area) > 4);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd\ne\nf\ng\nh\ni\nj\n"),
            MY_RET_OK);
  ASSERT_TRUE(my_text_area_content_left(area) >= 20);
  ASSERT_EQ(my_text_area_set_line_numbers(area, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_content_left(area), 4);
  my_widget_unref(area);
}

TEST(text_area_line_numbers_reduce_wrap_width)
{
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcd"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  ASSERT_EQ(my_text_area_set_line_numbers(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  my_widget_unref(area);
}

TEST(text_area_folded_range_hides_only_inner_physical_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nbb\nccc\ndddd"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 2, true), MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_visual_line_count(area), 3u);
  line = my_text_area_visual_line_at(area, 1);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 1u);
  line = my_text_area_visual_line_at(area, 2);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 3u);
  ASSERT_EQ(line->len_cp, 4u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 2, false), MY_RET_OK);
  ASSERT_FALSE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  my_widget_unref(area);
}

TEST(text_area_folded_range_rejects_invalid_or_overlapping_ranges)
{
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd\ne"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 2, 2, true),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_folded_range(area, 3, 9, true),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 2, 4, true),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 4, false),
            MY_RET_INVALID_PARAMS);
  my_widget_unref(area);
}

TEST(text_area_nested_fold_ranges_preserve_containment)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* line;
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd\ne\nf"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, true), MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  line = my_text_area_visual_line_at(area, 1);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 1u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 6u);
  my_widget_unref(area);
}

TEST(text_area_fold_state_yaml_roundtrip_and_transaction)
{
  my_widget_t* area = my_text_area_create(NULL);
  char* yaml = NULL;
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd\ne\nf"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_folds_to_yaml(area, NULL, &yaml), MY_RET_OK);
  ASSERT_NOT_NULL(yaml);
  ASSERT_STR_EQ(yaml, "version: 1\nfolds:\n  - start: 0\n    end: 5\n  - start: 1\n    end: 3\n");
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_folds_from_yaml(area, yaml), MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "folds:\n  - start: 0\n    end: 5\n  - start: 1\n    end: 3\n"),
            MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_folds_from_yaml(area, "version: 2\nfolds:\n"),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "folds:\n  - start: 0\n    end: 99\n"),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "folds:\n  - start: 0\n    end: 3\n    extra: 1\n"),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "folds:\n  - start: 0\n    end: 3\n\nextra: 1\n"),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, false), MY_RET_OK);
  my_mem_free(NULL, yaml);
  yaml = NULL;
  ASSERT_EQ(my_text_area_folds_to_yaml(area, NULL, &yaml), MY_RET_OK);
  ASSERT_STR_EQ(yaml, "version: 1\nfolds:\n");
  my_mem_free(NULL, yaml);
  my_widget_unref(area);
}

TEST(text_area_many_nested_folds_build_visible_rows_once)
{
  my_widget_t* area = my_text_area_create(NULL);
  char* text;
  size_t line_count = 512;
  size_t i;
  ASSERT_NOT_NULL(area);
  text = (char*)malloc(line_count * 2u + 1u);
  ASSERT_NOT_NULL(text);
  for (i = 0; i < line_count; i++) {
    text[i * 2u] = 'x';
    text[i * 2u + 1u] = '\n';
  }
  text[line_count * 2u] = '\0';
  ASSERT_EQ(my_text_area_set_text(area, text), MY_RET_OK);
  free(text);
  for (i = 0; i < 128; i++) {
    ASSERT_EQ(my_text_area_set_folded_range(area, i, line_count - i,
                                            true),
              MY_RET_OK);
  }
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 127));
  my_widget_unref(area);
}

TEST(text_area_folded_range_rebuilds_wrapped_visual_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcd\nefgh\nijkl"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 6u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 1, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  line = my_text_area_visual_line_at(area, 2);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 2u);
  my_widget_unref(area);
}

TEST(text_area_wrap_oom_keeps_previous_cache)
{
  text_area_fail_alloc_t state = {false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 20, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcd"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  state.fail = true;
  ASSERT_EQ(my_text_area_set_wrap(area, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  state.fail = false;
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  my_widget_unref(area);
}

TEST(text_area_folded_rows_remain_hidden_when_visible_cache_ooms)
{
  text_area_fail_alloc_t state = {false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 2, true), MY_RET_OK);
  state.fail = true;
  ASSERT_EQ(my_text_area_visual_line_count(area), 3u);
  line = my_text_area_visual_line_at(area, 1);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 1u);
  line = my_text_area_visual_line_at(area, 2);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 3u);
  my_widget_unref(area);
}

TEST(text_area_justify_cursor_tracks_stretched_space)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 100, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  uint32_t stride;
  size_t y;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 54, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_align(area, MY_TEXT_ALIGN_JUSTIFY), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa bb cc"), MY_RET_OK);
  text_area->cursor_row = 0;
  text_area->cursor_col = 3;
  text_area->focused = true;
  text_area->cursor_visible = true;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  for (y = 3; y < 19; y++) {
    ASSERT_EQ(pixels[y * stride + 34u * 4u], 33u);
  }
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_syntax_is_lazy_and_budgeted)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  my_text_area_t* text_area = (my_text_area_t*)area;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_text_area_set_text(area, "int first;\nint second;\n"),
            MY_RET_OK);
  ASSERT_FALSE(my_text_area_syntax_enabled(area));
  ASSERT_TRUE(text_area->syntax_cache == NULL);
  ASSERT_EQ(my_text_area_set_syntax_language(area, MY_SYNTAX_C_LIKE),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_line_budget(area, 1), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_enabled(area, true), MY_RET_OK);
  ASSERT_TRUE(my_text_area_syntax_enabled(area));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 1));

  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 1));

  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 1));

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_syntax_replacement_invalidates_tokens)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "int first;\nint second;\n"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_language(area, MY_SYNTAX_C_LIKE),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_line_budget(area, 8), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_enabled(area, true), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(text_area->syntax_cache, 8), MY_RET_OK);
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 1));
  text_area->cursor_row = 0;
  text_area->cursor_col = 0;
  text_area->anchor_row = 0;
  text_area->anchor_col = 0;
  text_area->goal_col = 0;
  ASSERT_EQ(my_text_area_set_text(area, "int changed;\nint second;\n"),
            MY_RET_OK);
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 1));
  my_widget_unref(area);
}

TEST(text_area_syntax_key_edit_invalidates_suffix)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "int first;\nint second;\n"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_language(area, MY_SYNTAX_C_LIKE), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_enabled(area, true), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(text_area->syntax_cache, 8), MY_RET_OK);
  text_area->cursor_row = 0;
  text_area->cursor_col = 0;
  text_area->anchor_row = 0;
  text_area->anchor_col = 0;
  text_area->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 1));
  my_widget_unref(area);
}

TEST(window_manager_refreshes_all_window_scales)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* root;
  my_window_t* dialog;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  root = my_window_create(NULL, pal, 200, 120, "root-scale");
  dialog = my_window_create(NULL, pal, 80, 40, "dialog-scale");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(dialog);
  ASSERT_EQ(my_window_manager_open(wm, root), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, dialog), MY_RET_OK);
  my_widget_unref((my_widget_t *)root);
  my_widget_unref((my_widget_t *)dialog);
  my_dirty_rects_clear(&root->dirty);
  my_dirty_rects_clear(&dialog->dirty);

  my_pal_dummy_set_scale_factor(pal, 1.5f);
  ASSERT_TRUE(my_window_manager_refresh_scales(wm));
  ASSERT_EQ(root->scale, 1.5f);
  ASSERT_EQ(dialog->scale, 1.5f);
  ASSERT_TRUE(my_dirty_rects_count(&root->dirty) > 0);
  ASSERT_TRUE(my_dirty_rects_count(&dialog->dirty) > 0);
  ASSERT_TRUE(!my_window_manager_refresh_scales(wm));

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(gpu_backend_request_reports_actual_state)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;

  ASSERT_NOT_NULL(pal);
  win = my_window_create(NULL, pal, 80, 40, "backend");
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);
  ASSERT_EQ(my_window_enable_gpu(win, MY_GPU_GLES2), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);
  ASSERT_EQ(my_window_enable_gpu(win, MY_GPU_VULKAN), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);
  ASSERT_EQ(my_window_enable_gpu(win, MY_GPU_SOFT), MY_RET_OK);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);
  ASSERT_EQ(my_window_enable_gpu(win, (my_gpu_backend_t)99),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);

  my_object_unref((my_object_t*)win);
  my_pal_destroy(pal);
}

TEST(software_canvas_recreates_after_surface_resize)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_lcd_t* old_lcd;
  my_lcd_t* resized_lcd;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_scale_factor(pal, 2.0f);
  loop = my_pal_main_loop_create(pal);
  ASSERT_NOT_NULL(loop);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(wm);
  win = my_window_create(NULL, pal, 80, 40, "resize");
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  my_widget_invalidate(my_window_widget(win), NULL);
  my_window_paint(win);
  ASSERT_NOT_NULL(win->vg);
  old_lcd = my_pal_window_get_lcd(win->pal_window);
  ASSERT_NOT_NULL(old_lcd);
  ASSERT_EQ(my_lcd_get_width(old_lcd), 160);
  ASSERT_EQ(my_lcd_get_height(old_lcd), 80);

  ASSERT_EQ(my_window_manager_resize_surface(wm, 160, 90), MY_RET_OK);
  ASSERT_TRUE(win->vg == NULL);
  resized_lcd = my_pal_window_get_lcd(win->pal_window);
  ASSERT_NOT_NULL(resized_lcd);
  ASSERT_TRUE(resized_lcd != old_lcd);
  ASSERT_EQ(my_lcd_get_width(resized_lcd), 320);
  ASSERT_EQ(my_lcd_get_height(resized_lcd), 180);
  my_window_paint(win);
  ASSERT_NOT_NULL(win->vg);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_snapshot_keeps_removed_window_alive)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 100, 80, "snapshot");
  my_window_t **snapshot = NULL;
  size_t count = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_snapshot_windows(wm, &snapshot, &count),
            MY_RET_OK);
  ASSERT_EQ(count, 1u);
  ASSERT_TRUE(snapshot[0] == win);

  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_window_manager_close(wm, snapshot[0]), MY_RET_OK);
  ASSERT_EQ(my_window_manager_count(wm), 0u);
  ASSERT_TRUE(snapshot[0]->pal_window != NULL);

  my_window_manager_release_snapshot(wm, snapshot, count);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(paint_stack_mutation_stops_current_frame)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *closing = my_window_create(NULL, pal, 100, 80, "closing");
  my_window_t *remaining = my_window_create(NULL, pal, 100, 80, "remaining");
  my_widget_t *closing_child = my_widget_create(NULL, "close-on-paint");
  my_widget_t *remaining_child = my_widget_create(NULL, "count-paint");
  paint_stack_mutation_ctx_t closing_ctx = {wm, closing, 0};
  paint_stack_mutation_ctx_t remaining_ctx = {wm, remaining, 0};

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(closing);
  ASSERT_NOT_NULL(remaining);
  ASSERT_NOT_NULL(closing_child);
  ASSERT_NOT_NULL(remaining_child);
  ASSERT_EQ(my_widget_subclass_init(closing_child,
                                    &s_close_window_on_paint_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(remaining_child, &s_count_paint_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(closing_child, &closing_ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(remaining_child, &remaining_ctx),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(closing_child, &(my_rect_t){0, 0, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(remaining_child, &(my_rect_t){0, 0, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(closing), closing_child),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(remaining), remaining_child),
            MY_RET_OK);
  my_widget_unref(closing_child);
  my_widget_unref(remaining_child);
  ASSERT_EQ(my_window_manager_open(wm, closing), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, remaining), MY_RET_OK);
  my_widget_unref((my_widget_t *)closing);
  my_widget_unref((my_widget_t *)remaining);

  my_pal_dummy_set_now_ms(pal, 10000);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_EQ(closing_ctx.paint_count, 1);
  ASSERT_EQ(remaining_ctx.paint_count, 0);
  ASSERT_EQ(my_window_manager_count(wm), 1u);
  ASSERT_TRUE(my_dirty_rects_count(&remaining->dirty) > 0);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(on_open_hook_fires_once_per_open)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 100, 80, "test");
  int marker = 42;

  my_window_manager_set_on_open(wm, on_open_cb, &marker);
  g_open_count = 0;
  my_window_manager_open(wm, win);
  ASSERT_EQ(g_open_count, 1);
  ASSERT_TRUE(g_hook_wm == wm);
  ASSERT_TRUE(g_hook_win == win);
  ASSERT_TRUE(g_hook_ctx == &marker);

  my_object_unref((my_object_t *)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_lifecycle_and_modal_blocking)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *main_win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *btn = my_button_create(NULL, "ok");
  my_dialog_t *dlg;
  my_event_t e;

  my_widget_set_rect(btn, &(my_rect_t){10, 10, 80, 32});
  my_widget_add_child(my_window_widget(main_win), btn);
  my_widget_unref(btn);

  my_window_manager_open(wm, main_win);
  my_widget_unref((my_widget_t *)main_win);

  dlg = my_dialog_create(NULL, pal, "confirm", 200, 120);
  my_dialog_add_button(dlg, "Yes", 1);
  my_dialog_open(dlg, wm, on_result, NULL);
  ASSERT_EQ(my_window_manager_count(wm), 2);
  ASSERT_TRUE(my_window_manager_top(wm) == dlg->win);
  ASSERT_TRUE(main_win->scrim);

  my_widget_invalidate(my_window_widget(dlg->win), NULL);
  my_window_paint(dlg->win);

  e = my_event_init(MY_EVENT_POINTER_DOWN);
  e.u.pointer.x = 20; e.u.pointer.y = 20; e.u.pointer.button = 1;
  my_pal_dummy_inject_event(pal, main_win->pal_window, &e);
  e = my_event_init(MY_EVENT_POINTER_UP);
  e.u.pointer.x = 20; e.u.pointer.y = 20; e.u.pointer.button = 1;
  my_pal_dummy_inject_event(pal, main_win->pal_window, &e);

  g_result = -999;
  e = my_event_init(MY_EVENT_KEY_DOWN);
  e.u.key.key = MY_KEY_ESCAPE;
  my_pal_dummy_inject_event(pal, dlg->win->pal_window, &e);
  pump(pal, loop);
  ASSERT_EQ(g_result, MY_DIALOG_CANCEL);
  ASSERT_EQ(my_window_manager_count(wm), 1);
  ASSERT_TRUE(!main_win->scrim);

  my_dialog_destroy(dlg);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(shared_surface_routes_input_to_modal)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *main_win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *main_btn = my_button_create(NULL, "main");
  my_dialog_t *dlg;
  my_widget_t *dialog_btn;
  my_event_t e;

  g_main_clicks = 0;
  g_dialog_clicks = 0;
  my_widget_set_rect(main_btn, &(my_rect_t){10, 10, 80, 32});
  my_widget_on(main_btn, "click", count_click, &g_main_clicks);
  my_widget_add_child(my_window_widget(main_win), main_btn);
  my_widget_unref(main_btn);
  ASSERT_EQ(my_window_manager_open(wm, main_win), MY_RET_OK);
  my_widget_unref((my_widget_t *)main_win);

  dlg = my_dialog_create(NULL, pal, "confirm", 200, 120);
  ASSERT_EQ(my_dialog_add_button(dlg, "Yes", 1), MY_RET_OK);
  ASSERT_EQ(my_dialog_open(dlg, wm, on_result, NULL), MY_RET_OK);
  ((my_widget_t*)dlg->win)->rect.x = 100;
  ((my_widget_t*)dlg->win)->rect.y = 90;
  my_widget_relayout((my_widget_t*)dlg->win);
  dialog_btn = my_widget_get_child(dlg->btn_row, 0);
  my_widget_on(dialog_btn, "click", count_click, &g_dialog_clicks);

  e = my_event_init(MY_EVENT_POINTER_DOWN);
  e.u.pointer.x = 110;
  e.u.pointer.y = 100;
  e.u.pointer.button = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &e), MY_RET_OK);
  e = my_event_init(MY_EVENT_POINTER_UP);
  e.u.pointer.x = 110;
  e.u.pointer.y = 100;
  e.u.pointer.button = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &e), MY_RET_OK);
  ASSERT_EQ(g_main_clicks, 0);

  e = my_event_init(MY_EVENT_POINTER_DOWN);
  e.u.pointer.x = ((my_widget_t*)dlg->win)->rect.x + dialog_btn->rect.x + 4;
  e.u.pointer.y = ((my_widget_t*)dlg->win)->rect.y +
                  dlg->btn_row->rect.y + dialog_btn->rect.y + 4;
  e.u.pointer.button = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &e), MY_RET_OK);
  e.type = MY_EVENT_POINTER_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &e), MY_RET_OK);
  ASSERT_EQ(g_dialog_clicks, 1);

  pump(pal, loop);
  my_dialog_destroy(dlg);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(shared_surface_routes_keyboard_to_pointer_window)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *bottom = my_window_create(NULL, pal, 400, 300, "bottom");
  my_window_t *top = my_window_create(NULL, pal, 400, 300, "top");
  my_widget_t *bottom_input = my_widget_create(NULL, "bottom_input");
  my_widget_t *top_input = my_widget_create(NULL, "top_input");
  surface_focus_ctx_t bottom_ctx = {0};
  surface_focus_ctx_t top_ctx = {0};
  my_event_t event;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(bottom);
  ASSERT_NOT_NULL(top);
  ASSERT_NOT_NULL(bottom_input);
  ASSERT_NOT_NULL(top_input);
  ASSERT_EQ(my_widget_subclass_init(bottom_input, &s_surface_focus_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(top_input, &s_surface_focus_vtable),
            MY_RET_OK);
  bottom_input->focusable = true;
  top_input->focusable = true;
  ASSERT_EQ(my_widget_set_user_data(bottom_input, &bottom_ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(top_input, &top_ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(bottom_input, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(top_input, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(bottom), bottom_input),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(top), top_input), MY_RET_OK);
  my_widget_unref(bottom_input);
  my_widget_unref(top_input);
  ASSERT_EQ(my_window_manager_open(wm, bottom), MY_RET_OK);
  my_widget_unref((my_widget_t *)bottom);
  ASSERT_EQ(my_window_manager_open(wm, top), MY_RET_OK);
  my_widget_unref((my_widget_t *)top);
  ASSERT_EQ(my_widget_set_rect(my_window_widget(top),
                               &(my_rect_t){220, 0, 180, 140}),
            MY_RET_OK);
  my_event_dispatcher_set_focus(&top->dispatcher, top_input);

  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(top_ctx.key_down, 1);
  ASSERT_EQ(bottom_ctx.key_down, 0);

  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 230;
  event.u.pointer.y = 10;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event = my_event_init(MY_EVENT_POINTER_UP);
  event.u.pointer.x = 230;
  event.u.pointer.y = 10;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);

  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 20;
  event.u.pointer.y = 20;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(bottom_ctx.key_down, 1);
  ASSERT_EQ(top_ctx.key_down, 1);

  ASSERT_EQ(my_window_manager_close(wm, bottom), MY_RET_OK);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(top_ctx.key_down, 2);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_cooldown_blocks_reentry_and_exposes_progress)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 160, 100, "cooldown");
  my_widget_t *button = my_button_create(NULL, "send");
  int clicks = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 1000), MY_RET_OK);
  ASSERT_FALSE(my_button_is_cooling_down(button));
  ASSERT_EQ(my_button_cooldown_remaining_ms(button), 0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(button), 0.0f, 0.0001f);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}), MY_RET_OK);
  ASSERT_NEQ(my_widget_on(button, "click", count_click, &clicks), 0u);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);

  my_pal_dummy_set_now_ms(pal, 1000);
  dispatch_button_click(wm, 20, 20);
  ASSERT_EQ(clicks, 1);
  ASSERT_TRUE(my_button_is_cooling_down(my_widget_get_child(my_window_widget(win), 0)));
  ASSERT_EQ(my_button_cooldown_remaining_ms(my_widget_get_child(my_window_widget(win), 0)),
            1000u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(
                      my_widget_get_child(my_window_widget(win), 0)),
                  1.0f, 0.0001f);

  my_pal_dummy_set_now_ms(pal, 1500);
  ASSERT_EQ(my_button_set_cooldown(my_widget_get_child(my_window_widget(win), 0),
                                   2000),
            MY_RET_OK);
  dispatch_button_click(wm, 20, 20);
  ASSERT_EQ(clicks, 1);
  ASSERT_EQ(my_button_cooldown_remaining_ms(my_widget_get_child(my_window_widget(win), 0)),
            500u);
  ASSERT_TRUE(my_button_cooldown_progress(
                  my_widget_get_child(my_window_widget(win), 0)) < 1.0f);

  my_pal_dummy_set_now_ms(pal, 2000);
  ASSERT_FALSE(my_button_is_cooling_down(my_widget_get_child(my_window_widget(win), 0)));
  ASSERT_EQ(my_button_cooldown_remaining_ms(my_widget_get_child(my_window_widget(win), 0)),
            0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(
                      my_widget_get_child(my_window_widget(win), 0)),
                  0.0f, 0.0001f);
  dispatch_button_click(wm, 20, 20);
  ASSERT_EQ(clicks, 2);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_cooldown_zero_disables_without_timer)
{
  my_widget_t *button = my_button_create(NULL, "send");

  ASSERT_EQ(my_button_set_cooldown(NULL, 250), MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(my_button_is_cooling_down(NULL));
  ASSERT_EQ(my_button_cooldown_remaining_ms(NULL), 0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(NULL), 0.0f, 0.0001f);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 0), MY_RET_OK);
  ASSERT_FALSE(my_button_is_cooling_down(button));
  ASSERT_EQ(my_button_cooldown_remaining_ms(button), 0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(button), 0.0f, 0.0001f);
  ASSERT_EQ(my_button_set_cooldown(button, 250), MY_RET_OK);
  ASSERT_EQ(my_button_set_cooldown(button, 0), MY_RET_OK);
  ASSERT_FALSE(my_button_is_cooling_down(button));
  my_widget_unref(button);
}

TEST(button_cooldown_timer_tracks_deadline_and_stops)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 160, 100, "cooldown-timer");
  my_widget_t *button = my_button_create(NULL, "send");
  my_button_t *state;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 100), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  state = (my_button_t *)my_widget_get_child(my_window_widget(win), 0);

  my_pal_dummy_set_now_ms(pal, 1000);
  dispatch_button_click(wm, 20, 20);
  ASSERT_TRUE(state->cooldown_timer != 0);
  ASSERT_TRUE(state->cooldown_loop == loop);

  my_pal_dummy_set_now_ms(pal, 1016);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_TRUE(state->cooldown_timer != 0);
  ASSERT_TRUE(my_button_is_cooling_down((my_widget_t *)state));

  my_pal_dummy_set_now_ms(pal, 1100);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_EQ(state->cooldown_timer, 0u);
  ASSERT_TRUE(state->cooldown_loop == NULL);
  ASSERT_FALSE(my_button_is_cooling_down((my_widget_t *)state));

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(surface_resize_preserves_and_recenters_dialog)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *main_win = my_window_create(NULL, pal, 400, 300, "main");
  my_dialog_t *dlg;

  ASSERT_EQ(my_window_manager_open(wm, main_win), MY_RET_OK);
  my_widget_unref((my_widget_t *)main_win);
  dlg = my_dialog_create(NULL, pal, "confirm", 200, 120);
  ASSERT_EQ(my_dialog_open(dlg, wm, NULL, NULL), MY_RET_OK);

  ASSERT_EQ(my_window_manager_resize_surface(wm, 800, 600), MY_RET_OK);
  ASSERT_EQ(((my_widget_t*)main_win)->rect.w, 800);
  ASSERT_EQ(((my_widget_t*)main_win)->rect.h, 600);
  ASSERT_EQ(((my_widget_t*)dlg->win)->rect.w, 200);
  ASSERT_EQ(((my_widget_t*)dlg->win)->rect.h, 120);
  ASSERT_EQ(((my_widget_t*)dlg->win)->rect.x, 300);
  ASSERT_EQ(((my_widget_t*)dlg->win)->rect.y, 240);

  my_dialog_close(dlg, MY_DIALOG_CANCEL);
  pump(pal, loop);
  my_dialog_destroy(dlg);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(back_to_home_clears_window_links_and_scrim)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm;
  my_window_t *home;
  my_window_t *page;

  my_pal_dummy_set_needs_csd(pal, true);
  wm = my_window_manager_create(NULL, pal, loop);
  home = my_window_create(NULL, pal, 400, 300, "home");
  page = my_window_create(NULL, pal, 200, 100, "page");
  ASSERT_EQ(my_window_manager_open(wm, home), MY_RET_OK);
  my_widget_unref((my_widget_t *)home);
  ASSERT_EQ(my_window_manager_open(wm, page), MY_RET_OK);
  my_widget_unref((my_widget_t *)page);
  home->scrim = true;

  ASSERT_EQ(my_window_manager_back_to_home(wm), MY_RET_OK);
  ASSERT_EQ(my_window_manager_count(wm), 1);
  ASSERT_TRUE(!home->scrim);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(auto_paint_toggle_removes_timer)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);

  ASSERT_TRUE(wm->paint_timer_id > 0);
  my_window_manager_set_auto_paint(wm, false);
  ASSERT_EQ(wm->paint_timer_id, 0u);
  my_window_manager_set_auto_paint(wm, true);
  ASSERT_TRUE(wm->paint_timer_id > 0);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(posted_user_event_reaches_top_window)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 200, 100, "main");
  my_event_t event = my_event_init(MY_EVENT_USER);

  g_user_events = 0;
  event.u.user.data = &g_user_events;
  my_widget_on(my_window_widget(win), "user", count_user, &g_user_events);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &event), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1), 1u);
  ASSERT_EQ(g_user_events, 1);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(user_event_can_close_window_during_dispatch)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 200, 100, "main");
  my_event_t event = my_event_init(MY_EVENT_USER);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  my_widget_on(my_window_widget(win), "user", close_window_from_user_event,
               wm);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &event), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1), 1u);
  ASSERT_EQ(my_window_manager_count(wm), 0u);
  ASSERT_TRUE(wm->quit_requested);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(text_widgets_toggle_platform_ime_with_focus)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *edit = my_edit_create(NULL);
  my_widget_t *text_area = my_text_area_create(NULL);
  my_widget_t *button = my_button_create(NULL, "done");
  char surrounding[32];
  int32_t cursor;
  int32_t anchor;

  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), text_area), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(edit);
  my_widget_unref(text_area);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);

  ASSERT_TRUE(!my_pal_dummy_get_ime_enabled(win->pal_window));
  ASSERT_EQ(my_edit_set_text(edit, "a\xE4\xB8\xAD"), MY_RET_OK);
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  ASSERT_TRUE(my_pal_dummy_get_ime_enabled(win->pal_window));
  my_pal_dummy_get_ime_surrounding(win->pal_window, surrounding,
                                   sizeof(surrounding), &cursor, &anchor);
  ASSERT_EQ(strcmp(surrounding, "a\xE4\xB8\xAD"), 0);
  ASSERT_EQ(cursor, 4);
  ASSERT_EQ(anchor, 4);
  my_event_dispatcher_set_focus(&win->dispatcher, button);
  ASSERT_TRUE(!my_pal_dummy_get_ime_enabled(win->pal_window));
  my_event_dispatcher_set_focus(&win->dispatcher, text_area);
  ASSERT_TRUE(my_pal_dummy_get_ime_enabled(win->pal_window));
  my_event_dispatcher_set_focus(&win->dispatcher, NULL);
  ASSERT_TRUE(!my_pal_dummy_get_ime_enabled(win->pal_window));

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(text_area_variable_font_keeps_nonwrap_coordinates_consistent)
{
  text_area_variable_font_t font = {{&text_area_variable_font_vtable}};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 40}), MY_RET_OK);
  my_text_area_set_font(area, (my_font_t*)&font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "AB"), MY_RET_OK);
  event.u.pointer.x = 7;
  event.u.pointer.y = 5;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_col, 1u);
  my_widget_unref(area);
}

TEST(text_area_pointer_hit_test_clamps_vertical_bounds)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 60}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "first\nsecond\nthird"), MY_RET_OK);
  event.u.pointer.x = 5;
  event.u.pointer.y = -30;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  event.u.pointer.y = 100;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 2u);
  my_widget_unref(area);
}

TEST(text_area_pointer_hit_test_uses_font_line_height)
{
  text_area_variable_font_t font = {{&text_area_variable_font_vtable}};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 80}), MY_RET_OK);
  my_text_area_set_font(area, (my_font_t*)&font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc"), MY_RET_OK);
  event.u.pointer.x = 5;
  event.u.pointer.y = 22;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  my_widget_unref(area);
}

TEST(text_area_page_down_moves_by_wrapped_visual_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcdefghij"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 5u);
  text_area->cursor_row = 0;
  text_area->cursor_col = 0;
  text_area->anchor_row = 0;
  text_area->anchor_col = 0;
  text_area->goal_col = 0;
  text_area->focused = true;
  event.u.key.key = MY_KEY_PAGE_DOWN;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 6u);
  my_widget_unref(area);
}

TEST(text_area_page_up_moves_by_wrapped_visual_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcdef\nabcdefghij"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 8u);
  text_area->cursor_row = 1;
  text_area->cursor_col = 2;
  text_area->anchor_row = 1;
  text_area->anchor_col = 2;
  text_area->goal_col = 0;
  text_area->focused = true;
  event.u.key.key = MY_KEY_PAGE_UP;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 2u);
  my_widget_unref(area);
}

TEST(text_area_paint_reuses_line_buffer)
{
  text_area_count_alloc_t state = {0};
  my_allocator_t allocator = {&state, text_area_count_alloc,
                              text_area_count_calloc, text_area_count_realloc,
                              text_area_count_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  size_t before;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcdefghij"), MY_RET_OK);
  text_area->focused = true;
  text_area->cursor_visible = true;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  before = state.alloc_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(state.alloc_calls, before);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_ime_spot_tracks_wrapped_justify_cursor)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "main");
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  int32_t ime_x = 0;
  int32_t ime_y = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){10, 20, 54, 60}),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_align(area, MY_TEXT_ALIGN_JUSTIFY), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa bb cc"), MY_RET_OK);
  text_area->cursor_row = 0;
  text_area->cursor_col = 3;
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), area), MY_RET_OK);
  my_widget_unref(area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  my_pal_dummy_get_ime_spot(win->pal_window, &ime_x, &ime_y);
  ASSERT_EQ(ime_x, 44);
  ASSERT_EQ(ime_y, 39);
  my_event_dispatcher_set_focus(&win->dispatcher, NULL);
  text_area->cursor_col = 6;
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  my_pal_dummy_get_ime_spot(win->pal_window, &ime_x, &ime_y);
  ASSERT_EQ(ime_x, 14);
  ASSERT_EQ(ime_y, 55);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(removing_focused_widget_blurs_and_disables_ime)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *edit = my_edit_create(NULL);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(edit);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  ASSERT_TRUE(((my_edit_t *)edit)->focused);
  ASSERT_TRUE(my_pal_dummy_get_ime_enabled(win->pal_window));

  ASSERT_EQ(my_widget_remove_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_TRUE(win->dispatcher.focused == NULL);
  ASSERT_FALSE(((my_edit_t *)edit)->focused);
  ASSERT_FALSE(my_pal_dummy_get_ime_enabled(win->pal_window));

  my_widget_unref(edit);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(removing_hovered_grabbed_widget_resets_dispatch_state)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *button = my_button_create(NULL, "drag");
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);

  event.u.pointer.x = 20;
  event.u.pointer.y = 20;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(win->dispatcher.hovered == button);
  ASSERT_EQ(my_pal_dummy_get_cursor(win->pal_window), MY_CURSOR_HAND);

  event.type = MY_EVENT_POINTER_DOWN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(win->dispatcher.grabbed == button);
  ASSERT_EQ(my_widget_remove_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_TRUE(win->dispatcher.grabbed == NULL);
  ASSERT_TRUE(win->dispatcher.hovered == NULL);
  ASSERT_FALSE(button->hovered);
  ASSERT_EQ(my_pal_dummy_get_cursor(win->pal_window), MY_CURSOR_ARROW);

  event.type = MY_EVENT_POINTER_MOVE;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event.type = MY_EVENT_POINTER_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);

  my_widget_unref(button);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(event_bubbling_stops_at_removed_ancestor)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *win = my_window_create(NULL, pal, 100, 80, "main");
  my_widget_t *parent = my_widget_create(NULL, "parent");
  my_widget_t *leaf = my_widget_create(NULL, "leaf");
  bubbling_mutation_ctx_t ctx = {(my_widget_t *)win, parent, NULL, 0};
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(leaf);
  ASSERT_EQ(my_widget_subclass_init(parent, &s_detached_parent_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(leaf, &s_mutation_leaf_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(parent, &ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(leaf, &ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(parent, &(my_rect_t){0, 0, 80, 60}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(leaf, &(my_rect_t){0, 0, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)win, parent), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(parent, leaf), MY_RET_OK);

  event.u.pointer.x = 5;
  event.u.pointer.y = 5;
  ASSERT_FALSE(my_event_dispatch(&win->dispatcher, &event));
  ASSERT_EQ(ctx.parent_events, 0);
  ASSERT_TRUE(parent->parent == NULL);
  ASSERT_TRUE(win->dispatcher.grabbed == NULL);

  my_widget_unref(leaf);
  my_widget_unref(parent);
  my_object_unref((my_object_t *)win);
  my_pal_destroy(pal);
}

TEST(event_bubbling_stops_at_self_removed_leaf)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *win = my_window_create(NULL, pal, 100, 80, "main");
  my_widget_t *parent = my_widget_create(NULL, "parent");
  my_widget_t *leaf = my_widget_create(NULL, "leaf");
  bubbling_mutation_ctx_t ctx = {(my_widget_t *)win, NULL, leaf, 0};
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(leaf);
  ASSERT_EQ(my_widget_subclass_init(parent, &s_detached_parent_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(leaf, &s_self_removing_leaf_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(parent, &ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(leaf, &ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(parent, &(my_rect_t){0, 0, 80, 60}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(leaf, &(my_rect_t){0, 0, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)win, parent), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(parent, leaf), MY_RET_OK);

  event.u.pointer.x = 5;
  event.u.pointer.y = 5;
  ASSERT_FALSE(my_event_dispatch(&win->dispatcher, &event));
  ASSERT_EQ(ctx.parent_events, 0);
  ASSERT_TRUE(leaf->parent == NULL);
  ASSERT_TRUE(parent->parent == (my_widget_t *)win);
  ASSERT_TRUE(win->dispatcher.grabbed == NULL);

  my_widget_unref(leaf);
  my_widget_unref(parent);
  my_object_unref((my_object_t *)win);
  my_pal_destroy(pal);
}

TEST(text_widgets_apply_ime_delete_surrounding)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *edit = my_edit_create(NULL);
  my_widget_t *text_area = my_text_area_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_IME_DELETE_SURROUNDING);

  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), text_area), MY_RET_OK);
  my_widget_unref(edit);
  my_widget_unref(text_area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);

  ASSERT_EQ(my_edit_set_text(edit, "ab\xE4\xB8\xAD" "cd"), MY_RET_OK);
  ((my_edit_t *)edit)->cursor = 5;
  ((my_edit_t *)edit)->anchor = 5;
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  event.u.ime.before = 3;
  event.u.ime.after = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(strcmp(my_edit_get_text(edit), "abd"), 0);

  ASSERT_EQ(my_text_area_set_text(text_area, "ab\xE4\xB8\xAD" "cd"),
            MY_RET_OK);
  ((my_text_area_t *)text_area)->cursor_row = 0;
  ((my_text_area_t *)text_area)->cursor_col = 3;
  ((my_text_area_t *)text_area)->anchor_row = 0;
  ((my_text_area_t *)text_area)->anchor_col = 3;
  my_event_dispatcher_set_focus(&win->dispatcher, text_area);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(strcmp(my_text_area_get_text(text_area), "abd"), 0);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(text_widgets_paste_full_clipboard_without_fixed_buffer_limit)
{
  enum { text_length = 8192 };
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *edit = my_edit_create(NULL);
  my_widget_t *text_area = my_text_area_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  char text[text_length + 1];

  memset(text, 'x', text_length);
  text[text_length] = '\0';
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), text_area), MY_RET_OK);
  my_widget_unref(edit);
  my_widget_unref(text_area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_pal_clipboard_set_text(pal, text), MY_RET_OK);

  event.u.key.key = 'v';
  event.u.key.modifiers = MY_KEYMOD_CTRL;
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(strlen(my_edit_get_text(edit)), (size_t)text_length);

  my_event_dispatcher_set_focus(&win->dispatcher, text_area);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(strlen(my_text_area_get_text(text_area)), (size_t)text_length);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST_MAIN_BEGIN()
    RUN_TEST(injected_canvas_inherits_window_scale);
    RUN_TEST(dynamic_scale_reconfigures_injected_canvas_without_resize);
    RUN_TEST(floating_plain_widget_does_not_crash_hit_test);
    RUN_TEST(text_area_grows_capacity_exponentially);
    RUN_TEST(text_area_wrap_rebuilds_after_edit);
    RUN_TEST(text_area_wrap_reuses_unchanged_prefix_after_edit);
    RUN_TEST(text_area_line_number_gutter_has_bounded_width);
    RUN_TEST(text_area_line_numbers_reduce_wrap_width);
    RUN_TEST(text_area_folded_range_hides_only_inner_physical_lines);
    RUN_TEST(text_area_folded_range_rejects_invalid_or_overlapping_ranges);
    RUN_TEST(text_area_nested_fold_ranges_preserve_containment);
    RUN_TEST(text_area_fold_state_yaml_roundtrip_and_transaction);
    RUN_TEST(text_area_many_nested_folds_build_visible_rows_once);
    RUN_TEST(text_area_folded_range_rebuilds_wrapped_visual_lines);
    RUN_TEST(text_area_wrap_oom_keeps_previous_cache);
    RUN_TEST(text_area_folded_rows_remain_hidden_when_visible_cache_ooms);
    RUN_TEST(text_area_justify_cursor_tracks_stretched_space);
    RUN_TEST(text_area_syntax_is_lazy_and_budgeted);
    RUN_TEST(text_area_syntax_replacement_invalidates_tokens);
    RUN_TEST(text_area_syntax_key_edit_invalidates_suffix);
    RUN_TEST(window_manager_refreshes_all_window_scales);
    RUN_TEST(gpu_backend_request_reports_actual_state);
    RUN_TEST(software_canvas_recreates_after_surface_resize);
    RUN_TEST(window_snapshot_keeps_removed_window_alive);
    RUN_TEST(paint_stack_mutation_stops_current_frame);
    RUN_TEST(on_open_hook_fires_once_per_open);
    RUN_TEST(dialog_lifecycle_and_modal_blocking);
    RUN_TEST(shared_surface_routes_input_to_modal);
    RUN_TEST(shared_surface_routes_keyboard_to_pointer_window);
    RUN_TEST(button_cooldown_blocks_reentry_and_exposes_progress);
    RUN_TEST(button_cooldown_zero_disables_without_timer);
    RUN_TEST(button_cooldown_timer_tracks_deadline_and_stops);
    RUN_TEST(surface_resize_preserves_and_recenters_dialog);
    RUN_TEST(back_to_home_clears_window_links_and_scrim);
    RUN_TEST(auto_paint_toggle_removes_timer);
    RUN_TEST(posted_user_event_reaches_top_window);
    RUN_TEST(user_event_can_close_window_during_dispatch);
    RUN_TEST(text_widgets_toggle_platform_ime_with_focus);
    RUN_TEST(text_area_variable_font_keeps_nonwrap_coordinates_consistent);
    RUN_TEST(text_area_pointer_hit_test_clamps_vertical_bounds);
    RUN_TEST(text_area_pointer_hit_test_uses_font_line_height);
    RUN_TEST(text_area_page_down_moves_by_wrapped_visual_lines);
    RUN_TEST(text_area_page_up_moves_by_wrapped_visual_lines);
    RUN_TEST(text_area_paint_reuses_line_buffer);
    RUN_TEST(text_area_ime_spot_tracks_wrapped_justify_cursor);
    RUN_TEST(removing_focused_widget_blurs_and_disables_ime);
    RUN_TEST(removing_hovered_grabbed_widget_resets_dispatch_state);
    RUN_TEST(event_bubbling_stops_at_removed_ancestor);
    RUN_TEST(event_bubbling_stops_at_self_removed_leaf);
    RUN_TEST(text_widgets_apply_ime_delete_surrounding);
    RUN_TEST(text_widgets_paste_full_clipboard_without_fixed_buffer_limit);
TEST_MAIN_END()
