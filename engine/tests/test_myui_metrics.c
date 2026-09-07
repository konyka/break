#include "test_framework.h"

#include "myr/my_ui_metrics.h"
#include "myr/my_vgcanvas.h"

typedef struct metrics_fake_canvas_t {
  my_vgcanvas_t base;
  bool fail_begin;
  bool fail_end;
  bool fail_draw;
  unsigned draw_count;
} metrics_fake_canvas_t;

static my_ret_t metrics_fake_begin(my_vgcanvas_t* vg, const my_rect_t* dirty) {
  metrics_fake_canvas_t* canvas = (metrics_fake_canvas_t*)vg;
  (void)dirty;
  return canvas->fail_begin ? MY_RET_FAIL : MY_RET_OK;
}

static my_ret_t metrics_fake_end(my_vgcanvas_t* vg) {
  metrics_fake_canvas_t* canvas = (metrics_fake_canvas_t*)vg;
  return canvas->fail_end ? MY_RET_FAIL : MY_RET_OK;
}

static my_ret_t metrics_fake_fill_rect(my_vgcanvas_t* vg,
                                       const my_rectf_t* rect) {
  metrics_fake_canvas_t* canvas = (metrics_fake_canvas_t*)vg;
  (void)rect;
  if (canvas->fail_draw) return MY_RET_FAIL;
  canvas->draw_count++;
  return MY_RET_OK;
}

static my_ret_t metrics_fake_stroke_rect(my_vgcanvas_t* vg,
                                         const my_rectf_t* rect) {
  return metrics_fake_fill_rect(vg, rect);
}

static my_ret_t metrics_fake_fill(my_vgcanvas_t* vg) {
  return metrics_fake_fill_rect(vg, NULL);
}

static my_ret_t metrics_fake_stroke(my_vgcanvas_t* vg) {
  return metrics_fake_fill_rect(vg, NULL);
}

static my_ret_t metrics_fake_text(my_vgcanvas_t* vg, const char* text, float x,
                                  float y) {
  (void)text;
  (void)x;
  (void)y;
  return metrics_fake_fill_rect(vg, NULL);
}

static my_ret_t metrics_fake_image(my_vgcanvas_t* vg, const uint8_t* rgba,
                                   int32_t w, int32_t h,
                                   const my_rectf_t* dst,
                                   const my_color_t* bg) {
  (void)rgba;
  (void)w;
  (void)h;
  (void)dst;
  (void)bg;
  return metrics_fake_fill_rect(vg, NULL);
}

static const my_vgcanvas_vtable_t metrics_fake_vtable = {
    .begin_frame = metrics_fake_begin,
    .end_frame = metrics_fake_end,
    .fill_rect = metrics_fake_fill_rect,
    .stroke_rect = metrics_fake_stroke_rect,
    .fill = metrics_fake_fill,
    .stroke = metrics_fake_stroke,
    .draw_text = metrics_fake_text,
    .draw_image = metrics_fake_image};

TEST(metrics_disabled_does_not_record)
{
  my_ui_frame_metrics_sample_t sample;

  memset(&g_myui_metrics, 0, sizeof(g_myui_metrics));
  my_ui_metrics_set_enabled(false);
  my_ui_metrics_begin_frame();
  my_ui_metrics_record_draw_call();
  my_ui_metrics_record_layout_pass();
  my_ui_metrics_record_damage(100u);
  my_ui_metrics_record_atlas_miss();
  my_ui_metrics_record_image_cache_miss();
  my_ui_metrics_record_fallback();
  my_ui_metrics_end_frame();
  ASSERT_FALSE(my_ui_metrics_get_last(&sample));
}

TEST(metrics_frame_records_and_resets_counters)
{
  my_ui_frame_metrics_sample_t sample;

  memset(&g_myui_metrics, 0, sizeof(g_myui_metrics));
  my_ui_metrics_set_enabled(true);
  my_ui_metrics_begin_frame();
  my_ui_metrics_record_draw_call();
  my_ui_metrics_record_draw_call();
  my_ui_metrics_record_layout_pass();
  my_ui_metrics_record_damage(400u);
  my_ui_metrics_record_damage(600u);
  my_ui_metrics_record_atlas_miss();
  my_ui_metrics_record_image_cache_miss();
  my_ui_metrics_record_fallback();
  my_ui_metrics_end_frame();
  ASSERT_TRUE(my_ui_metrics_get_last(&sample));
  ASSERT_EQ(sample.draw_calls, 2u);
  ASSERT_EQ(sample.layout_passes, 1u);
  ASSERT_EQ(sample.damage_rects, 2u);
  ASSERT_EQ(sample.damage_area_pixels, 1000u);
  ASSERT_EQ(sample.atlas_misses, 1u);
  ASSERT_EQ(sample.image_cache_misses, 1u);
  ASSERT_EQ(sample.fallbacks, 1u);

  my_ui_metrics_begin_frame();
  my_ui_metrics_end_frame();
  ASSERT_TRUE(my_ui_metrics_get_last(&sample));
  ASSERT_EQ(sample.draw_calls, 0u);
  ASSERT_EQ(sample.damage_area_pixels, 0u);
}

TEST(metrics_counters_saturate_without_wrap)
{
  my_ui_frame_metrics_sample_t sample;

  memset(&g_myui_metrics, 0, sizeof(g_myui_metrics));
  my_ui_metrics_set_enabled(true);
  my_ui_metrics_begin_frame();
  g_myui_metrics.current.draw_calls = UINT64_MAX;
  g_myui_metrics.current.damage_area_pixels = UINT64_MAX - 5u;
  my_ui_metrics_record_draw_call();
  my_ui_metrics_record_damage(10u);
  my_ui_metrics_end_frame();
  ASSERT_TRUE(my_ui_metrics_get_last(&sample));
  ASSERT_EQ(sample.draw_calls, UINT64_MAX);
  ASSERT_EQ(sample.damage_area_pixels, UINT64_MAX);
}

TEST(metrics_nested_canvas_frames_publish_once)
{
  my_ui_frame_metrics_sample_t sample;

  memset(&g_myui_metrics, 0, sizeof(g_myui_metrics));
  my_ui_metrics_set_enabled(true);
  my_ui_metrics_begin_frame();
  my_ui_metrics_record_draw_call();
  my_ui_metrics_begin_frame();
  my_ui_metrics_record_draw_call();
  my_ui_metrics_end_frame();
  ASSERT_FALSE(my_ui_metrics_get_last(&sample));
  my_ui_metrics_end_frame();
  ASSERT_TRUE(my_ui_metrics_get_last(&sample));
  ASSERT_EQ(sample.draw_calls, 2u);
}

TEST(metrics_canvas_wrappers_count_only_successful_operations)
{
  metrics_fake_canvas_t canvas = {0};
  my_ui_frame_metrics_sample_t sample;
  uint8_t pixel[4] = {0};
  my_rectf_t rect = {0, 0, 2, 2};

  canvas.base.vtable = &metrics_fake_vtable;
  memset(&g_myui_metrics, 0, sizeof(g_myui_metrics));
  my_ui_metrics_set_enabled(true);
  ASSERT_EQ(my_vgcanvas_begin_frame(&canvas.base, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(&canvas.base, &rect), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_stroke_rect(&canvas.base, &rect), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill(&canvas.base), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_stroke(&canvas.base), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_text(&canvas.base, "x", 0, 0), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_image(&canvas.base, pixel, 1, 1, &rect, NULL),
            MY_RET_OK);
  canvas.fail_draw = true;
  ASSERT_EQ(my_vgcanvas_fill_rect(&canvas.base, &rect), MY_RET_FAIL);
  ASSERT_EQ(my_vgcanvas_fill_rect(&canvas.base,
                                  &(my_rectf_t){NAN, 0, 1, 1}),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_end_frame(&canvas.base), MY_RET_OK);
  ASSERT_TRUE(my_ui_metrics_get_last(&sample));
  ASSERT_EQ(canvas.draw_count, 6u);
  ASSERT_EQ(sample.draw_calls, 6u);
}

TEST(metrics_canvas_end_failure_discards_nested_frame)
{
  metrics_fake_canvas_t canvas = {0};
  my_ui_frame_metrics_sample_t sample;
  my_rectf_t rect = {0, 0, 1, 1};

  canvas.base.vtable = &metrics_fake_vtable;
  memset(&g_myui_metrics, 0, sizeof(g_myui_metrics));
  my_ui_metrics_set_enabled(true);
  ASSERT_EQ(my_vgcanvas_begin_frame(&canvas.base, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(&canvas.base, &rect), MY_RET_OK);
  canvas.fail_end = true;
  ASSERT_EQ(my_vgcanvas_end_frame(&canvas.base), MY_RET_FAIL);
  ASSERT_FALSE(my_ui_metrics_get_last(&sample));
  canvas.fail_end = false;
  ASSERT_EQ(my_vgcanvas_begin_frame(&canvas.base, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(&canvas.base), MY_RET_OK);
  ASSERT_TRUE(my_ui_metrics_get_last(&sample));
  ASSERT_EQ(sample.draw_calls, 0u);
}

TEST_MAIN_BEGIN()
  RUN_TEST(metrics_disabled_does_not_record);
  RUN_TEST(metrics_frame_records_and_resets_counters);
  RUN_TEST(metrics_counters_saturate_without_wrap);
  RUN_TEST(metrics_nested_canvas_frames_publish_once);
  RUN_TEST(metrics_canvas_wrappers_count_only_successful_operations);
  RUN_TEST(metrics_canvas_end_failure_discards_nested_frame);
TEST_MAIN_END()
