#include "test_framework.h"

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/widgets/my_chart.h"

static void dump_ppm(const uint8_t* pixels, uint32_t width, uint32_t height,
                     uint32_t stride, const char* path) {
  FILE* file;
  uint32_t y;
  if (path == NULL) return;
  file = fopen(path, "wb");
  if (file == NULL) return;
  fprintf(file, "P6\n%u %u\n255\n", width, height);
  for (y = 0u; y < height; y++) {
    uint32_t x;
    for (x = 0u; x < width; x++) {
      const uint8_t* pixel = pixels + y * stride + x * 4u;
      uint8_t rgb[3] = {pixel[2], pixel[1], pixel[0]};
      fwrite(rgb, 1u, sizeof(rgb), file);
    }
  }
  fclose(file);
}

static void dump_ppm_if_requested(const uint8_t* pixels, uint32_t width,
                                  uint32_t height, uint32_t stride) {
  dump_ppm(pixels, width, height, stride, getenv("MYUI_CHART_DUMP_PPM"));
}

TEST(chart_rejects_invalid_series_and_range) {
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_chart_series_t series = {"Revenue", NULL, 0u, 0xE85D75FFu};

  ASSERT_NOT_NULL(chart);
  ASSERT_TRUE(my_chart_is_instance(chart));
  ASSERT_EQ(my_chart_set_series(chart, MY_CHART_MAX_SERIES, &series),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_series(chart, 2u, &series), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_series(chart, 0u, NULL), MY_RET_INVALID_PARAMS);
  series.values = (const float[]){NAN};
  series.count = 1u;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_range(chart, 10.0f, 10.0f), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_range(chart, -FLT_MAX, FLT_MAX), MY_RET_OK);
  my_widget_unref(chart);
}

TEST(chart_formats_fractional_axis_ticks) {
  char tick[32];

  ASSERT_EQ(my_chart_format_tick(12.0f, tick, sizeof(tick)), MY_RET_OK);
  ASSERT_TRUE(strcmp(tick, "12") == 0);
  ASSERT_EQ(my_chart_format_tick(1.25f, tick, sizeof(tick)), MY_RET_OK);
  ASSERT_TRUE(strcmp(tick, "1.25") == 0);
  ASSERT_EQ(my_chart_format_tick(-0.5f, tick, sizeof(tick)), MY_RET_OK);
  ASSERT_TRUE(strcmp(tick, "-0.5") == 0);
  ASSERT_EQ(my_chart_format_tick(1.25f, tick, 3u), MY_RET_FAIL);
}

TEST(chart_series_visibility_controls_tooltip) {
  static const float first_values[] = {10.0f, 20.0f};
  static const float second_values[] = {4.0f, 8.0f};
  my_chart_series_t first = {"Revenue", first_values, 2u, 0xE85D75FFu};
  my_chart_series_t second = {"Orders", second_values, 2u, 0x3A86FFFFu};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  char tooltip[128];
  my_event_t event;

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &first), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &second), MY_RET_OK);
  ASSERT_TRUE(my_chart_get_series_visible(chart, 1u));
  ASSERT_EQ(my_chart_set_series_visible(chart, 1u, false), MY_RET_OK);
  ASSERT_FALSE(my_chart_get_series_visible(chart, 1u));
  ASSERT_EQ(my_chart_set_series_visible(chart, 2u, false), MY_RET_INVALID_PARAMS);
  event = my_event_init(MY_EVENT_POINTER_MOVE);
  event.u.pointer.x = 180;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_tooltip(chart, tooltip, sizeof(tooltip)), MY_RET_OK);
  ASSERT_TRUE(strstr(tooltip, "Revenue: 20.00") != NULL);
  ASSERT_TRUE(strstr(tooltip, "Orders") == NULL);
  my_widget_unref(chart);
}

TEST(chart_legend_click_toggles_series_visibility) {
  static const float values[] = {1.0f, 2.0f};
  my_chart_series_t series = {"Revenue", values, 2u, 0xE85D75FFu};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_event_t event;

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 48;
  event.u.pointer.y = 21;
  event.u.pointer.button = 1u;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_FALSE(my_chart_get_series_visible(chart, 0u));
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_TRUE(my_chart_get_series_visible(chart, 0u));
  my_widget_unref(chart);
}

TEST(chart_hover_emphasis_is_reported) {
  static const float values[] = {10.0f, 30.0f};
  my_chart_series_t series = {"Revenue", values, 2u, 0xE85D75FFu};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_event_t event;

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  event = my_event_init(MY_EVENT_POINTER_MOVE);
  event.u.pointer.x = 180;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  my_widget_unref(chart);
}

TEST(chart_supports_stacked_bar_mode) {
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_BAR);
  ASSERT_NOT_NULL(chart);
  ASSERT_FALSE(my_chart_get_stacked(chart));
  ASSERT_EQ(my_chart_set_stacked(chart, true), MY_RET_OK);
  ASSERT_TRUE(my_chart_get_stacked(chart));
  my_widget_unref(chart);
}

TEST(chart_clamps_values_and_formats_hover_tooltip) {
  static const float values[] = {10.0f, 20.0f, 30.0f};
  static const char* labels[] = {"Mon", "Tue", "Wed"};
  my_chart_series_t series = {"Revenue", values, 3u, 0xE85D75FFu};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  char tooltip[64];

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_set_labels(chart, labels, 3u), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_set_range(chart, 10.0f, 30.0f), MY_RET_OK);
  ASSERT_FLOAT_EQ(my_chart_value_to_y(40.0f, 10.0f, 30.0f, 4.0f, 100.0f),
                  4.0f, 1e-5f);
  ASSERT_FLOAT_EQ(my_chart_value_to_y(0.0f, 10.0f, 30.0f, 4.0f, 100.0f),
                  104.0f, 1e-5f);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  chart->rect.w = 320;
  chart->rect.h = 180;
  {
    my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);
    event.u.pointer.x = 180;
    event.u.pointer.y = 80;
    ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  }
  ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  ASSERT_EQ(my_chart_get_tooltip(chart, tooltip, sizeof(tooltip)), MY_RET_OK);
  ASSERT_TRUE(strstr(tooltip, "Tue") != NULL);
  ASSERT_TRUE(strstr(tooltip, "Revenue: 20.00") != NULL);
  {
    my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);
    event.u.pointer.x = 2;
    event.u.pointer.y = 2;
    ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_NOT_SUPPORTED);
    ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  }
  my_widget_unref(chart);
}

TEST(chart_hover_tooltip_includes_all_series_at_category) {
  static const float first_values[] = {10.0f, 20.0f};
  static const float second_values[] = {4.0f, 8.0f, 12.0f, 16.0f};
  my_chart_series_t first = {"Revenue", first_values, 2u, 0xE85D75FFu};
  my_chart_series_t second = {"Orders", second_values, 4u, 0x3A86FFFFu};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  char tooltip[128];
  my_event_t event;

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &first), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &second), MY_RET_OK);
  event = my_event_init(MY_EVENT_POINTER_MOVE);
  event.u.pointer.x = 220;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 2u);
  ASSERT_EQ(my_chart_get_tooltip(chart, tooltip, sizeof(tooltip)), MY_RET_OK);
  ASSERT_TRUE(strstr(tooltip, "Orders: 12.00") != NULL);
  ASSERT_TRUE(strstr(tooltip, "Revenue") == NULL);

  event.u.pointer.x = 140;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  ASSERT_EQ(my_chart_get_tooltip(chart, tooltip, sizeof(tooltip)), MY_RET_OK);
  ASSERT_TRUE(strstr(tooltip, "Revenue: 20.00") != NULL);
  ASSERT_TRUE(strstr(tooltip, "Orders: 8.00") != NULL);
  my_widget_unref(chart);
}

TEST(chart_paints_visible_series_to_software_canvas) {
  static const float values[] = {5.0f, 30.0f, 15.0f};
  my_chart_series_t series = {"Load", values, 3u, 0x3A86FFFFu};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t i;
  size_t non_white = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  {
    my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);
    event.u.pointer.x = 180;
    event.u.pointer.y = 80;
    ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  }
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  dump_ppm_if_requested(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd));
  for (i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
        pixels[i + 2u] != 0xFFu) {
      non_white++;
    }
  }
  ASSERT_TRUE(non_white > 100u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_paints_grouped_bar_series_to_software_canvas) {
  static const float primary_values[] = {10.0f, 24.0f, 16.0f};
  static const float secondary_values[] = {18.0f, 12.0f, 28.0f};
  my_chart_series_t primary = {"Primary", primary_values, 3u, 0xE85D75FFu};
  my_chart_series_t secondary = {"Secondary", secondary_values, 3u,
                                 0x3A86FFFFu};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_BAR);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t primary_pixels = 0u;
  size_t secondary_pixels = 0u;
  uint32_t y;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &primary), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &secondary), MY_RET_OK);
  {
    my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);
    event.u.pointer.x = 180;
    event.u.pointer.y = 80;
    ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  }
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);

  pixels = my_lcd_mem_get_buffer(lcd);
  dump_ppm(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd),
           getenv("MYUI_CHART_BAR_DUMP_PPM"));
  for (y = 30u; y < 154u; y++) {
    uint32_t x;
    for (x = 42u; x < 308u; x++) {
      size_t i = ((size_t)y * 320u + x) * 4u;
      if (pixels[i] == 0x75u && pixels[i + 1u] == 0x5Du &&
          pixels[i + 2u] == 0xE8u && pixels[i + 3u] == 0xFFu) {
        primary_pixels++;
      }
      if (pixels[i] == 0xFFu && pixels[i + 1u] == 0x86u &&
          pixels[i + 2u] == 0x3Au && pixels[i + 3u] == 0xFFu) {
        secondary_pixels++;
      }
    }
  }
  ASSERT_TRUE(primary_pixels > 0u);
  ASSERT_TRUE(secondary_pixels > 0u);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST_MAIN_BEGIN()
  RUN_TEST(chart_rejects_invalid_series_and_range);
  RUN_TEST(chart_formats_fractional_axis_ticks);
  RUN_TEST(chart_series_visibility_controls_tooltip);
  RUN_TEST(chart_legend_click_toggles_series_visibility);
  RUN_TEST(chart_hover_emphasis_is_reported);
  RUN_TEST(chart_supports_stacked_bar_mode);
  RUN_TEST(chart_clamps_values_and_formats_hover_tooltip);
  RUN_TEST(chart_hover_tooltip_includes_all_series_at_category);
  RUN_TEST(chart_paints_visible_series_to_software_canvas);
  RUN_TEST(chart_paints_grouped_bar_series_to_software_canvas);
TEST_MAIN_END()
