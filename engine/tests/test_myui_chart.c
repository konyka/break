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
  my_chart_series_t series = {"Revenue", NULL, 0u, 0xE85D75FFu, 0u, false};

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

TEST(chart_hidden_series_excluded_from_auto_range) {
  static const float small_values[] = {1.0f, 2.0f};
  static const float huge_values[] = {1.0f, 1000.0f};
  my_chart_series_t small = {"small", small_values, 2u, 0xE85D75FFu, 0u, false};
  my_chart_series_t huge = {"huge", huge_values, 2u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  float y_min = 0.0f, y_max = 0.0f;

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &small), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &huge), MY_RET_OK);
  ASSERT_EQ(my_chart_get_range(chart, &y_min, &y_max), MY_RET_OK);
  ASSERT_TRUE(y_max >= 1000.0f);
  ASSERT_EQ(my_chart_set_series_visible(chart, 1u, false), MY_RET_OK);
  ASSERT_EQ(my_chart_get_range(chart, &y_min, &y_max), MY_RET_OK);
  ASSERT_TRUE(y_max < 1000.0f);
  my_widget_unref(chart);
}

TEST(chart_manages_mark_points) {
  static const float values[] = {10.0f, 20.0f, 30.0f};
  my_chart_series_t series = {"Revenue", values, 3u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_get_mark_point_count(chart), 0u);
  ASSERT_EQ(my_chart_add_mark_point(chart, 0u, 2u, "peak"), MY_RET_OK);
  ASSERT_EQ(my_chart_get_mark_point_count(chart), 1u);
  ASSERT_EQ(my_chart_add_mark_point(chart, 1u, 0u, "bad"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_add_mark_point(chart, 0u, 3u, "bad"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_clear_mark_points(chart), MY_RET_OK);
  ASSERT_EQ(my_chart_get_mark_point_count(chart), 0u);
  my_widget_unref(chart);
}

TEST(chart_data_zoom_limits_category_window) {
  static const float values[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
  my_chart_series_t series = {"v", values, 5u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  size_t start = 99u, end = 99u;
  my_event_t event;

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_FALSE(my_chart_get_data_zoom(chart, &start, &end));
  ASSERT_EQ(my_chart_set_data_zoom(chart, 3u, 3u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_data_zoom(chart, 1u, 4u), MY_RET_OK);
  ASSERT_TRUE(my_chart_get_data_zoom(chart, &start, &end));
  ASSERT_EQ(start, 1u);
  ASSERT_EQ(end, 4u);

  /* Pointer selection must stay inside the zoom window. */
  event = my_event_init(MY_EVENT_POINTER_MOVE);
  event.u.pointer.x = 44;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  event.u.pointer.x = 306;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 3u);

  ASSERT_EQ(my_chart_clear_data_zoom(chart), MY_RET_OK);
  ASSERT_FALSE(my_chart_get_data_zoom(chart, &start, &end));
  my_widget_unref(chart);
}

TEST(chart_animation_progress_is_deterministic) {
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  ASSERT_NOT_NULL(chart);
  ASSERT_FLOAT_EQ(my_chart_get_animation_progress(chart), 1.0f, 1e-5f);
  ASSERT_EQ(my_chart_set_animation_progress(chart, 0.5f), MY_RET_OK);
  ASSERT_FLOAT_EQ(my_chart_get_animation_progress(chart), 0.5f, 1e-5f);
  ASSERT_EQ(my_chart_set_animation_progress(chart, -0.1f), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_animation_progress(chart, 1.1f), MY_RET_INVALID_PARAMS);
  my_widget_unref(chart);
}

TEST(chart_manages_mark_lines) {
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_get_mark_line_count(chart), 0u);
  ASSERT_EQ(my_chart_add_mark_line(chart, 42.0f, "target", 0xE85D75FFu),
            MY_RET_OK);
  ASSERT_EQ(my_chart_get_mark_line_count(chart), 1u);
  ASSERT_EQ(my_chart_add_mark_line(chart, NAN, "bad", 0u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_clear_mark_lines(chart), MY_RET_OK);
  ASSERT_EQ(my_chart_get_mark_line_count(chart), 0u);
  my_widget_unref(chart);
}

TEST(chart_manages_mark_areas) {
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_get_mark_area_count(chart), 0u);
  ASSERT_EQ(my_chart_add_mark_area(chart, 20.0f, 40.0f, "band", 0x3A86FF44u),
            MY_RET_OK);
  ASSERT_EQ(my_chart_get_mark_area_count(chart), 1u);
  ASSERT_EQ(my_chart_add_mark_area(chart, 40.0f, 20.0f, "bad", 0u),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_add_mark_area(chart, NAN, 20.0f, "bad", 0u),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_clear_mark_areas(chart), MY_RET_OK);
  ASSERT_EQ(my_chart_get_mark_area_count(chart), 0u);
  my_widget_unref(chart);
}

TEST(chart_axis_configuration) {
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_get_grid_line_count(chart), 5u);
  ASSERT_EQ(my_chart_set_grid_line_count(chart, 0u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_grid_line_count(chart, 10u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_grid_line_count(chart, 3u), MY_RET_OK);
  ASSERT_EQ(my_chart_get_grid_line_count(chart), 3u);
  ASSERT_EQ(my_chart_set_axis_title(chart, "USD"), MY_RET_OK);
  ASSERT_EQ(my_chart_set_axis_title(chart, "toolongtoolongtoolongtoolongtoolongtoolongtoolongtoolong"), MY_RET_OK);
  my_widget_unref(chart);
}

TEST(chart_secondary_axis_binding) {
  static const float price[] = {10.0f, 20.0f};
  static const float volume[] = {1000.0f, 2000.0f};
  my_chart_series_t price_series = {"Price", price, 2u, 0xE85D75FFu, 0u, false};
  my_chart_series_t volume_series = {"Volume", volume, 2u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  float lo = 0.0f, hi = 0.0f;

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &price_series), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &volume_series), MY_RET_OK);
  ASSERT_FALSE(my_chart_has_secondary_axis(chart));
  ASSERT_EQ(my_chart_set_series_axis(chart, 1u, 1u), MY_RET_OK);
  ASSERT_EQ(my_chart_get_series_axis(chart, 1u), 1u);
  ASSERT_TRUE(my_chart_has_secondary_axis(chart));
  ASSERT_EQ(my_chart_set_series_axis(chart, 0u, 2u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_get_axis_range(chart, 0u, &lo, &hi), MY_RET_OK);
  ASSERT_TRUE(hi <= 25.0f);
  ASSERT_EQ(my_chart_get_axis_range(chart, 1u, &lo, &hi), MY_RET_OK);
  ASSERT_TRUE(hi >= 2000.0f);
  ASSERT_EQ(my_chart_set_secondary_range(chart, 0.0f, 5000.0f), MY_RET_OK);
  ASSERT_EQ(my_chart_get_axis_range(chart, 1u, &lo, &hi), MY_RET_OK);
  ASSERT_TRUE(hi == 5000.0f);
  my_widget_unref(chart);
}

TEST(chart_series_visibility_controls_tooltip) {
  static const float first_values[] = {10.0f, 20.0f};
  static const float second_values[] = {4.0f, 8.0f};
  my_chart_series_t first = {"Revenue", first_values, 2u, 0xE85D75FFu, 0u, false};
  my_chart_series_t second = {"Orders", second_values, 2u, 0x3A86FFFFu, 0u, false};
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
  my_chart_series_t series = {"Revenue", values, 2u, 0xE85D75FFu, 0u, false};
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
  my_chart_series_t series = {"Revenue", values, 2u, 0xE85D75FFu, 0u, false};
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

TEST(chart_supports_scatter_mode) {
  static const float values[] = {5.0f, 15.0f, 25.0f};
  my_chart_series_t series = {"Points", values, 3u, 0x2A9D8FFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_SCATTER);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t dot_pixels = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] == 0x8Fu && pixels[i + 1u] == 0x9Du &&
        pixels[i + 2u] == 0x2Au && pixels[i + 3u] == 0xFFu) {
      dot_pixels++;
    }
  }
  ASSERT_TRUE(dot_pixels > 10u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_supports_pie_mode) {
  static const float values[] = {25.0f, 35.0f, 40.0f};
  my_chart_series_t series = {"Share", values, 3u, 0x2A9D8FFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_PIE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;
  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  {
    my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);
    event.u.pointer.x = 205;
    event.u.pointer.y = 115;
    ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
    ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  }
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  dump_ppm(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd),
           getenv("MYUI_CHART_PIE_DUMP_PPM"));
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
        pixels[i + 2u] != 0xFFu) colored++;
  }
  ASSERT_TRUE(colored > 1000u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_supports_radar_mode_and_rejects_invalid_data) {
  static const float values[] = {20.0f, 40.0f, 60.0f, 80.0f};
  static const float invalid_values[] = {20.0f, NAN, 60.0f, 80.0f};
  my_chart_series_t series = {"Radar", values, 4u, 0x2A9D8FFFu, 0u, false};
  my_chart_series_t invalid = {"Invalid", invalid_values, 4u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_RADAR);

  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &invalid), MY_RET_INVALID_PARAMS);
  my_widget_unref(chart);
}

TEST(chart_funnel_hover_tracks_bands_and_clears_outside) {
  static const float values[] = {100.0f, 60.0f, 30.0f};
  my_chart_series_t series = {"Funnel", values, 3u, 0x2A9D8FFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_FUNNEL);
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  event.u.pointer.x = 175;
  event.u.pointer.y = 92;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  event.u.pointer.x = 10;
  event.u.pointer.y = 10;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  my_widget_unref(chart);
}

TEST(chart_radar_hover_tracks_spokes_and_clears_outside) {
  static const float values[] = {20.0f, 40.0f, 60.0f, 80.0f};
  my_chart_series_t series = {"Radar", values, 4u, 0x2A9D8FFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_RADAR);
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  event.u.pointer.x = 195;
  event.u.pointer.y = 92;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  event.u.pointer.x = 300;
  event.u.pointer.y = 10;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  my_widget_unref(chart);
}

TEST(chart_supports_funnel_mode) {
  static const float values[] = {100.0f, 70.0f, 40.0f, 20.0f};
  my_chart_series_t series = {"Funnel", values, 4u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_FUNNEL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
        pixels[i + 2u] != 0xFFu) colored++;
  }
  ASSERT_TRUE(colored > 1000u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_supports_heatmap_mode) {
  static const float first[] = {0.0f, 50.0f, 100.0f};
  static const float second[] = {100.0f, 50.0f, 0.0f};
  my_chart_series_t a = {"A", first, 3u, 0x3A86FFFFu, 0u, false};
  my_chart_series_t b = {"B", second, 3u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_HEATMAP);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &a), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &b), MY_RET_OK);
  ASSERT_EQ(my_chart_set_visual_map(chart, 0.0f, 100.0f, 0x0000FFFFu,
                                    0xFF0000FFu), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 1000u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_supports_boxplot_mode) {
  static const float five_number[] = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f};
  my_chart_series_t series = {"Stats", five_number, 5u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_BOXPLOT);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;
  bool has_top_whisker = false;
  bool has_bottom_whisker = false;
  bool has_median = false;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  dump_ppm(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd),
           getenv("MYUI_CHART_BOXPLOT_DUMP_PPM"));
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 500u);
  for (uint32_t x = 100u; x < 240u; x++) {
    size_t top = ((size_t)30u * 320u + x) * 4u;
    size_t bottom = ((size_t)154u * 320u + x) * 4u;
    if (pixels[top] == 0x75u && pixels[top + 1u] == 0x5Du &&
        pixels[top + 2u] == 0xE8u) has_top_whisker = true;
    if (pixels[bottom] == 0x75u && pixels[bottom + 1u] == 0x5Du &&
        pixels[bottom + 2u] == 0xE8u) has_bottom_whisker = true;
  }
  for (uint32_t x = 100u; x < 240u; x++) {
    size_t median = ((size_t)92u * 320u + x) * 4u;
    if (pixels[median] < 0x40u && pixels[median + 1u] < 0x40u &&
        pixels[median + 2u] < 0x40u) has_median = true;
  }
  ASSERT_TRUE(has_top_whisker);
  ASSERT_TRUE(has_bottom_whisker);
  ASSERT_TRUE(has_median);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_paints_radar_polygon_to_software_canvas) {
  static const float values[] = {20.0f, 40.0f, 60.0f, 80.0f};
  my_chart_series_t series = {"Radar", values, 4u, 0x2A9D8FFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_RADAR);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
        pixels[i + 2u] != 0xFFu) colored++;
  }
  ASSERT_TRUE(colored > 1000u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_visual_map_configuration) {
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_SCATTER);
  ASSERT_NOT_NULL(chart);
  ASSERT_FALSE(my_chart_has_visual_map(chart));
  ASSERT_EQ(my_chart_set_visual_map(chart, 0.0f, 100.0f, 0x0000FFFFu,
                                    0xFF0000FFu), MY_RET_OK);
  ASSERT_TRUE(my_chart_has_visual_map(chart));
  ASSERT_EQ(my_chart_set_visual_map(chart, 10.0f, 10.0f, 0u, 0u),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_clear_visual_map(chart), MY_RET_OK);
  ASSERT_FALSE(my_chart_has_visual_map(chart));
  my_widget_unref(chart);
}

TEST(chart_brush_selects_category_window) {
  static const float values[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
  my_chart_series_t series = {"v", values, 5u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_event_t event;
  size_t start = 0u, end = 0u;

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_get_brush(chart, &start, &end), MY_RET_NOT_SUPPORTED);
  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 80;
  event.u.pointer.y = 100;
  event.u.pointer.button = 1u;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  event = my_event_init(MY_EVENT_POINTER_MOVE);
  event.u.pointer.x = 240;
  event.u.pointer.y = 70;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  event = my_event_init(MY_EVENT_POINTER_UP);
  event.u.pointer.x = 240;
  event.u.pointer.y = 70;
  event.u.pointer.button = 1u;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_brush(chart, &start, &end), MY_RET_OK);
  ASSERT_TRUE(start < end);
  ASSERT_EQ(my_chart_clear_brush(chart), MY_RET_OK);
  ASSERT_EQ(my_chart_get_brush(chart, &start, &end), MY_RET_NOT_SUPPORTED);
  my_widget_unref(chart);
}

TEST(chart_accessible_description_and_keyboard_navigation) {
  static const float values[] = {10.0f, 20.0f, 30.0f};
  static const char* labels[] = {"Mon", "Tue", "Wed"};
  my_chart_series_t series = {"Revenue", values, 3u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  char description[256];
  my_event_t event;

  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_title(chart, "Weekly revenue"), MY_RET_OK);
  ASSERT_EQ(my_chart_set_labels(chart, labels, 3u), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_get_accessible_description(chart, description,
                                                sizeof(description)), MY_RET_OK);
  ASSERT_TRUE(strstr(description, "Weekly revenue") != NULL);
  ASSERT_TRUE(strstr(description, "Revenue") != NULL);
  ASSERT_TRUE(strstr(description, "3 categories") != NULL);

  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = MY_KEY_RIGHT;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  event.u.key.key = MY_KEY_RIGHT;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 2u);
  event.u.key.key = MY_KEY_LEFT;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 1u);
  my_widget_unref(chart);
}

TEST(chart_paints_visual_map_legend) {
  static const float values[] = {0.0f, 50.0f, 100.0f};
  my_chart_series_t series = {"v", values, 3u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_SCATTER);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t map_pixels = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_set_visual_map(chart, 0.0f, 100.0f, 0x0000FFFFu,
                                    0xFF0000FFu), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (uint32_t y = 30u; y < 42u; y++) {
    for (uint32_t x = 210u; x < 306u; x++) {
      size_t i = ((size_t)y * 320u + x) * 4u;
      if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
          pixels[i + 2u] != 0xFFu) map_pixels++;
    }
  }
  ASSERT_TRUE(map_pixels > 100u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_stacked_endpoint_matches_segment_geometry) {
  ASSERT_FLOAT_EQ(my_chart_stacked_value_to_y(20.0f, 10.0f, 0.0f, 30.0f,
                                              30.0f, 120.0f),
                  my_chart_value_to_y(30.0f, 0.0f, 30.0f, 30.0f, 120.0f),
                  1e-5f);
}

TEST(chart_stacked_bars_share_category_slot) {
  static const float first_values[] = {10.0f};
  static const float second_values[] = {20.0f};
  my_chart_series_t first = {"A", first_values, 1u, 0xE85D75FFu, 0u, false};
  my_chart_series_t second = {"B", second_values, 1u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_BAR);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t first_min = SIZE_MAX, first_max = 0u;
  size_t second_min = SIZE_MAX, second_max = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &first), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &second), MY_RET_OK);
  ASSERT_EQ(my_chart_set_stacked(chart, true), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (uint32_t y = 30u; y < 154u; y++) {
    for (uint32_t x = 42u; x < 308u; x++) {
      size_t i = ((size_t)y * 320u + x) * 4u;
      if (pixels[i] == 0x75u && pixels[i + 1u] == 0x5Du &&
          pixels[i + 2u] == 0xE8u && pixels[i + 3u] == 0xFFu) {
        if (x < first_min) first_min = x;
        if (x > first_max) first_max = x;
      }
      if (pixels[i] == 0xFFu && pixels[i + 1u] == 0x86u &&
          pixels[i + 2u] == 0x3Au && pixels[i + 3u] == 0xFFu) {
        if (x < second_min) second_min = x;
        if (x > second_max) second_max = x;
      }
    }
  }
  ASSERT_TRUE(first_min != SIZE_MAX && second_min != SIZE_MAX);
  ASSERT_TRUE(first_min == second_min);
  ASSERT_TRUE(first_max == second_max);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_clamps_values_and_formats_hover_tooltip) {
  static const float values[] = {10.0f, 20.0f, 30.0f};
  static const char* labels[] = {"Mon", "Tue", "Wed"};
  my_chart_series_t series = {"Revenue", values, 3u, 0xE85D75FFu, 0u, false};
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
  my_chart_series_t first = {"Revenue", first_values, 2u, 0xE85D75FFu, 0u, false};
  my_chart_series_t second = {"Orders", second_values, 4u, 0x3A86FFFFu, 0u, false};
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
  my_chart_series_t series = {"Load", values, 3u, 0x3A86FFFFu, 0u, false};
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
  my_chart_series_t primary = {"Primary", primary_values, 3u, 0xE85D75FFu, 0u, false};
  my_chart_series_t secondary = {"Secondary", secondary_values, 3u, 0x3A86FFFFu, 0u, false};
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

TEST(chart_paints_mark_point_annotation) {
  static const float values[] = {5.0f, 30.0f, 15.0f};
  my_chart_series_t series = {"Load", values, 3u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t without_mark = 0u;
  size_t with_mark = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] == 0xFFu && pixels[i + 1u] == 0x86u &&
        pixels[i + 2u] == 0x3Au && pixels[i + 3u] == 0xFFu) {
      without_mark++;
    }
  }

  ASSERT_EQ(my_chart_add_mark_point(chart, 0u, 1u, "peak"), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  dump_ppm_if_requested(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd));
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] == 0xFFu && pixels[i + 1u] == 0x86u &&
        pixels[i + 2u] == 0x3Au && pixels[i + 3u] == 0xFFu) {
      with_mark++;
    }
  }
  /* The mark marker square adds series-colored pixels at the annotated point. */
  ASSERT_TRUE(with_mark > without_mark);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_line_series_share_category_positions) {
  static const float long_values[] = {10.0f, 20.0f, 30.0f, 40.0f};
  static const float short_values[] = {15.0f, 25.0f};
  my_chart_series_t long_series = {"Long", long_values, 4u, 0xE85D75FFu, 0u, false};
  my_chart_series_t short_series = {"Short", short_values, 2u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  bool short_at_first = false;
  bool short_at_far_right = false;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &long_series), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &short_series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);

  pixels = my_lcd_mem_get_buffer(lcd);
  /* The short series has a sample at category 1 only. With a shared category
   * axis it must not stretch to the far-right category slot. */
  for (uint32_t y = 30u; y < 154u; y++) {
    for (uint32_t x = 42u; x < 308u; x++) {
      size_t i = ((size_t)y * 320u + x) * 4u;
      bool is_short = pixels[i] == 0xFFu && pixels[i + 1u] == 0x86u &&
                      pixels[i + 2u] == 0x3Au && pixels[i + 3u] == 0xFFu;
      if (!is_short) continue;
      if (x < 130u) short_at_first = true;
      if (x > 290u) short_at_far_right = true;
    }
  }
  ASSERT_TRUE(short_at_first);
  ASSERT_FALSE(short_at_far_right);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_renders_at_supported_viewports) {
  static const float values[] = {5.0f, 30.0f, 15.0f};
  my_chart_series_t series = {"Load", values, 3u, 0x3A86FFFFu, 0u, false};
  const uint32_t sizes[][2] = {{120u, 100u}, {320u, 180u}, {640u, 360u}};
  for (size_t viewport = 0u; viewport < 3u; viewport++) {
    my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
    my_lcd_t* lcd = my_lcd_mem_create(NULL, sizes[viewport][0], sizes[viewport][1],
                                      MY_PIXEL_FORMAT_BGRA8888);
    my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
    size_t non_white = 0u;
    ASSERT_NOT_NULL(chart);
    ASSERT_NOT_NULL(lcd);
    ASSERT_NOT_NULL(canvas);
    chart->rect.w = (int32_t)sizes[viewport][0];
    chart->rect.h = (int32_t)sizes[viewport][1];
    ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
    ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
    chart->vtable->on_paint(chart, canvas);
    ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
    {
      uint8_t* pixels = my_lcd_mem_get_buffer(lcd);
      size_t bytes = (size_t)sizes[viewport][0] * sizes[viewport][1] * 4u;
      for (size_t i = 0u; i < bytes; i += 4u)
        if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
          non_white++;
    }
    ASSERT_TRUE(non_white > 20u);
    my_vgcanvas_destroy(canvas);
    my_lcd_destroy(lcd);
    my_widget_unref(chart);
  }
}

TEST(chart_paints_mark_area) {
  static const float values[] = {10.0f, 20.0f, 30.0f};
  my_chart_series_t series = {"Load", values, 3u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t area_pixels = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  /* Distinctive opaque fill so the band is unambiguous in the framebuffer. */
  ASSERT_EQ(my_chart_add_mark_area(chart, 12.0f, 24.0f, "band", 0xE85D75FFu),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  dump_ppm_if_requested(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd));
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] == 0x75u && pixels[i + 1u] == 0x5Du &&
        pixels[i + 2u] == 0xE8u && pixels[i + 3u] == 0xFFu) {
      area_pixels++;
    }
  }
  ASSERT_TRUE(area_pixels > 100u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_hit_test_is_pure_and_bounded) {
  static const float values[] = {10.0f, 20.0f, 30.0f, 40.0f};
  my_chart_series_t series = {"v", values, 4u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_hit_test(chart, 44, 80), 0u);
  ASSERT_EQ(my_chart_hit_test(chart, 140, 90), 1u);
  ASSERT_EQ(my_chart_hit_test(chart, 306, 100), 3u);
  ASSERT_EQ(my_chart_hit_test(chart, 10, 80), SIZE_MAX);
  ASSERT_EQ(my_chart_hit_test(chart, 400, 80), SIZE_MAX);
  ASSERT_EQ(my_chart_hit_test(chart, 175, 5), SIZE_MAX);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  my_widget_unref(chart);
}

TEST(chart_supports_candlestick_mode) {
  static const float ohlc[] = {10.0f, 15.0f, 8.0f, 12.0f,
                               12.0f, 14.0f, 11.0f, 13.0f,
                               13.0f, 16.0f, 12.5f, 14.5f};
  my_chart_series_t series = {"Candles", ohlc, 12u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_CANDLESTICK);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 200u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_supports_gauge_mode) {
  static const float values[] = {30.0f, 70.0f};
  my_chart_series_t series = {"Gauge", values, 2u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_GAUGE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 200u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_supports_sankey_mode) {
  static const float src[] = {10.0f, 20.0f, 30.0f};
  static const float dst[] = {25.0f, 15.0f, 20.0f};
  my_chart_series_t cols[2] = {
      {"Source", src, 3u, 0xE85D75FFu, 0u, false},
      {"Target", dst, 3u, 0x3A86FFFFu, 0u, false}};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_SANKEY);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &cols[0]), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &cols[1]), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 100u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_supports_parallel_mode) {
  static const float a[] = {1.0f, 5.0f, 3.0f};
  static const float b[] = {2.0f, 4.0f, 1.0f};
  static const float c[] = {3.0f, 2.0f, 2.0f};
  my_chart_series_t axes[3] = {
      {"A", a, 3u, 0xE85D75FFu, 0u, false},
      {"B", b, 3u, 0x3A86FFFFu, 0u, false},
      {"C", c, 3u, 0x2A9D8FFFu, 0u, false}};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_PARALLEL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &axes[0]), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &axes[1]), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 2u, &axes[2]), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 100u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_supports_treemap_mode) {
  static const float values[] = {40.0f, 30.0f, 20.0f, 10.0f};
  my_chart_series_t series = {"Tree", values, 4u, 0xE85D75FFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_TREEMAP);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;
  ASSERT_NOT_NULL(chart); ASSERT_NOT_NULL(lcd); ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 150u);
  my_vgcanvas_destroy(canvas); my_lcd_destroy(lcd); my_widget_unref(chart);
}

TEST(chart_supports_graph_mode) {
  static const float values[] = {5.0f, 8.0f, 3.0f, 6.0f};
  my_chart_series_t series = {"Graph", values, 4u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_GRAPH);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;
  ASSERT_NOT_NULL(chart); ASSERT_NOT_NULL(lcd); ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 150u);
  my_vgcanvas_destroy(canvas); my_lcd_destroy(lcd); my_widget_unref(chart);
}

TEST(chart_supports_calendar_mode) {
  static const float values[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  my_chart_series_t series = {"Cal", values, 14u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_CALENDAR);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;
  ASSERT_NOT_NULL(chart); ASSERT_NOT_NULL(lcd); ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 150u);
  my_vgcanvas_destroy(canvas); my_lcd_destroy(lcd); my_widget_unref(chart);
}

TEST(chart_supports_theme_river_mode) {
  static const float a[] = {3.0f, 5.0f, 2.0f, 4.0f};
  static const float b[] = {2.0f, 4.0f, 3.0f, 1.0f};
  my_chart_series_t bands[2] = {
      {"A", a, 4u, 0xE85D75FFu, 0u, false}, {"B", b, 4u, 0x3A86FFFFu, 0u, false}};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_THEME_RIVER);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  size_t colored = 0u;
  ASSERT_NOT_NULL(chart); ASSERT_NOT_NULL(lcd); ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &bands[0]), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &bands[1]), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu || pixels[i + 2u] != 0xFFu)
      colored++;
  ASSERT_TRUE(colored > 150u);
  my_vgcanvas_destroy(canvas); my_lcd_destroy(lcd); my_widget_unref(chart);
}

static size_t chart_count_color_in_region(const uint8_t* pixels,
                                          uint32_t stride, uint32_t x0,
                                          uint32_t y0, uint32_t x1,
                                          uint32_t y1, uint32_t color) {
  const uint8_t r = (uint8_t)(color >> 24);
  const uint8_t g = (uint8_t)(color >> 16);
  const uint8_t b = (uint8_t)(color >> 8);
  const uint8_t a = (uint8_t)color;
  size_t matched = 0u;
  for (uint32_t y = y0; y < y1; y++) {
    for (uint32_t x = x0; x < x1; x++) {
      const uint8_t* p = pixels + y * stride + x * 4u;
      if (p[0] == b && p[1] == g && p[2] == r && p[3] == a) matched++;
    }
  }
  return matched;
}

TEST(chart_tooltip_flips_left_at_right_edge) {
  static const float values[] = {5.0f, 30.0f, 15.0f, 25.0f};
  my_chart_series_t series = {"Load", values, 4u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);
  uint8_t* pixels;
  size_t total;
  size_t left;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  event.u.pointer.x = 308;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  total = chart_count_color_in_region(pixels, my_lcd_mem_get_stride(lcd),
                                      0u, 0u, 320u, 180u, 0x1F2933FFu);
  left = chart_count_color_in_region(pixels, my_lcd_mem_get_stride(lcd),
                                     0u, 0u, 308u, 180u, 0x1F2933FFu);
  ASSERT_TRUE(total > 100u);
  ASSERT_TRUE(left > 100u);
  ASSERT_EQ(chart_count_color_in_region(pixels, my_lcd_mem_get_stride(lcd),
                                        319u, 0u, 320u, 180u,
                                        0x1F2933FFu), 0u);
  dump_ppm_if_requested(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd));
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_tooltip_stays_right_in_mid_chart) {
  static const float values[] = {5.0f, 30.0f, 15.0f, 25.0f};
  my_chart_series_t series = {"Load", values, 4u, 0x3A86FFFFu, 0u, false};
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);
  uint8_t* pixels;

  ASSERT_NOT_NULL(chart);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320;
  chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  event.u.pointer.x = 130;
  event.u.pointer.y = 80;
  ASSERT_EQ(chart->vtable->on_event(chart, &event), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  ASSERT_TRUE(chart_count_color_in_region(pixels, my_lcd_mem_get_stride(lcd),
                                          131u, 0u, 320u, 180u,
                                          0x1F2933FFu) > 100u);
  dump_ppm_if_requested(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd));
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

TEST(chart_multi_grid_layout_and_assignment) {
  static const float values[] = {1.0f, 2.0f, 3.0f};
  my_chart_series_t series = {"S", values, 3u, 0xE85D75FFu, 0u, false};
  my_chart_grid_desc_t grid;
  float x, y, w, h;
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320; chart->rect.h = 180;

  ASSERT_EQ((size_t)my_chart_get_grid_count(chart), 1u);
  ASSERT_EQ(my_chart_get_grid_rect(chart, 0u, &x, &y, &w, &h), MY_RET_OK);
  ASSERT_TRUE(w > 0.0f && h > 0.0f);

  ASSERT_EQ(my_chart_set_grid_count(chart, 0u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_grid_count(chart, MY_CHART_MAX_GRIDS + 1u),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_grid_count(chart, 2u), MY_RET_OK);
  ASSERT_EQ((size_t)my_chart_get_grid_count(chart), 2u);

  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  memset(&grid, 0, sizeof(grid));
  grid.axis_count = 1u;
  grid.left = 0.1f; grid.top = 0.55f; grid.width = 0.8f; grid.height = 0.35f;
  grid.series_indices[0] = 0u;
  grid.series_count = 1u;
  grid.visible = true;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_OK);
  ASSERT_EQ((size_t)my_chart_get_series_grid(chart, 0u), 1u);

  grid.left = -0.1f;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_INVALID_PARAMS);
  grid.left = 0.1f;
  grid.width = 1.5f;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_INVALID_PARAMS);
  grid.width = NAN;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_INVALID_PARAMS);
  grid.width = 0.8f;
  grid.series_count = MY_CHART_MAX_SERIES + 1u;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_INVALID_PARAMS);
  grid.series_count = 1u;
  grid.series_indices[0] = 99u;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_INVALID_PARAMS);
  grid.series_indices[0] = 0u;
  ASSERT_EQ(my_chart_set_grid(chart, 2u, &grid), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_grid(chart, 1u, NULL), MY_RET_INVALID_PARAMS);

  ASSERT_EQ(my_chart_get_grid_rect(chart, 1u, &x, &y, &w, &h), MY_RET_OK);
  ASSERT_TRUE(w > 0.0f && h > 0.0f);
  ASSERT_EQ(my_chart_get_grid_rect(chart, 2u, &x, &y, &w, &h),
            MY_RET_INVALID_PARAMS);

  ASSERT_EQ(my_chart_set_grid_count(chart, 1u), MY_RET_OK);
  ASSERT_EQ((size_t)my_chart_get_series_grid(chart, 0u), 0u);
  my_widget_unref(chart);
}

TEST(chart_grid_link_flag_validation) {
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_set_grid_link(NULL, 0u, true), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_set_grid_link(chart, MY_CHART_MAX_GRIDS, true),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_chart_get_grid_link(NULL, 0u), false);
  ASSERT_EQ(my_chart_get_grid_link(chart, MY_CHART_MAX_GRIDS), false);
  ASSERT_EQ(my_chart_set_grid_link(chart, 0u, true), MY_RET_OK);
  ASSERT_TRUE(my_chart_get_grid_link(chart, 0u));
  ASSERT_EQ(my_chart_set_grid_link(chart, 0u, false), MY_RET_OK);
  ASSERT_EQ(my_chart_get_grid_link(chart, 0u), false);
  my_widget_unref(chart);
}

TEST(chart_multi_grid_renders_series_in_own_rect) {
  static const float top_values[] = {1.0f, 3.0f, 2.0f};
  static const float bottom_values[] = {2.0f, 1.0f, 3.0f};
  my_chart_series_t top = {"top", top_values, 3u, 0xFF0000FFu, 0u, false};
  my_chart_series_t bottom = {"bottom", bottom_values, 3u, 0x00FF00FFu, 0u, false};
  my_chart_grid_desc_t grid;
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  ASSERT_NOT_NULL(chart); ASSERT_NOT_NULL(lcd); ASSERT_NOT_NULL(canvas);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_legend_visible(chart, false), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &top), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &bottom), MY_RET_OK);
  ASSERT_EQ(my_chart_set_grid_count(chart, 2u), MY_RET_OK);

  memset(&grid, 0, sizeof(grid));
  grid.axis_count = 1u;
  grid.left = 0.05f; grid.top = 0.05f; grid.width = 0.9f; grid.height = 0.4f;
  grid.series_indices[0] = 0u;
  grid.series_count = 1u;
  grid.visible = true;
  ASSERT_EQ(my_chart_set_grid(chart, 0u, &grid), MY_RET_OK);
  grid.top = 0.55f;
  grid.series_indices[0] = 1u;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_OK);

  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  chart->vtable->on_paint(chart, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  dump_ppm_if_requested(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd));
  ASSERT_TRUE(chart_count_color_in_region(pixels, my_lcd_mem_get_stride(lcd), 40u, 10u,
                                          300u, 80u, 0xFF0000FFu) > 30u);
  ASSERT_TRUE(chart_count_color_in_region(pixels, my_lcd_mem_get_stride(lcd), 40u, 100u,
                                          300u, 170u, 0x00FF00FFu) > 30u);
  ASSERT_EQ(chart_count_color_in_region(pixels, my_lcd_mem_get_stride(lcd), 40u, 10u,
                                        300u, 80u, 0x00FF00FFu), 0u);
  ASSERT_EQ(chart_count_color_in_region(pixels, my_lcd_mem_get_stride(lcd), 40u, 100u,
                                        300u, 170u, 0xFF0000FFu), 0u);
  my_vgcanvas_destroy(canvas); my_lcd_destroy(lcd); my_widget_unref(chart);
}

TEST(chart_multi_grid_auto_range_isolated) {
  static const float small_values[] = {1.0f, 10.0f};
  static const float huge_values[] = {100.0f, 1000.0f};
  my_chart_series_t small = {"small", small_values, 2u, 0xE85D75FFu, 0u, false};
  my_chart_series_t huge = {"huge", huge_values, 2u, 0x3A86FFFFu, 0u, false};
  my_chart_grid_desc_t grid;
  float lo, hi;
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  ASSERT_NOT_NULL(chart);
  ASSERT_EQ(my_chart_set_series(chart, 0u, &small), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series(chart, 1u, &huge), MY_RET_OK);
  ASSERT_EQ(my_chart_set_grid_count(chart, 2u), MY_RET_OK);
  memset(&grid, 0, sizeof(grid));
  grid.axis_count = 1u;
  grid.left = 0.05f; grid.top = 0.05f; grid.width = 0.9f; grid.height = 0.4f;
  grid.series_indices[0] = 1u;
  grid.series_count = 1u;
  grid.visible = true;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_OK);

  ASSERT_EQ(my_chart_get_grid_range(chart, 0u, 0u, &lo, &hi), MY_RET_OK);
  ASSERT_TRUE(hi <= 12.0f);
  ASSERT_EQ(my_chart_get_grid_range(chart, 1u, 0u, &lo, &hi), MY_RET_OK);
  ASSERT_TRUE(hi >= 999.0f);
  ASSERT_EQ(my_chart_get_grid_range(chart, 2u, 0u, &lo, &hi),
            MY_RET_INVALID_PARAMS);
  my_widget_unref(chart);
}


TEST(chart_multi_grid_hit_test_resolves_own_grid) {
  static const float values[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
  my_chart_series_t series = {"S", values, 5u, 0xE85D75FFu, 0u, false};
  my_chart_grid_desc_t grid;
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &series), MY_RET_OK);
  ASSERT_EQ(my_chart_set_grid_count(chart, 2u), MY_RET_OK);
  memset(&grid, 0, sizeof(grid));
  grid.axis_count = 1u;
  grid.left = 0.05f; grid.top = 0.05f; grid.width = 0.9f; grid.height = 0.4f;
  grid.series_indices[0] = 0u;
  grid.series_count = 1u;
  grid.visible = true;
  ASSERT_EQ(my_chart_set_grid(chart, 0u, &grid), MY_RET_OK);
  grid.top = 0.55f;
  ASSERT_EQ(my_chart_set_grid(chart, 1u, &grid), MY_RET_OK);

  ASSERT_EQ(chart_grid_at(chart, 100, 40), 0u);
  ASSERT_EQ(chart_grid_at(chart, 100, 140), 1u);
  ASSERT_EQ(chart_grid_at(chart, 100, 90), MY_CHART_NO_GRID);
  ASSERT_EQ(my_chart_hit_test(chart, 100, 40), 1u);
  ASSERT_EQ(my_chart_hit_test(chart, 100, 140), 1u);
  ASSERT_EQ(my_chart_hit_test(chart, 100, 90), SIZE_MAX);
  my_widget_unref(chart);
}

TEST(chart_three_axis_ranges_are_isolated) {
  static const float a[] = {1.0f, 3.0f};
  static const float b[] = {100.0f, 300.0f};
  static const float c[] = {-20.0f, -10.0f};
  my_chart_series_t series[] = {{"A", a, 2u, 0u, 0u, false},
                                {"B", b, 2u, 0u, 0u, false},
                                {"C", c, 2u, 0u, 0u, false}};
  my_chart_grid_desc_t grid;
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  float lo, hi;
  ASSERT_NOT_NULL(chart);
  for (size_t i = 0u; i < 3u; i++)
    ASSERT_EQ(my_chart_set_series(chart, i, &series[i]), MY_RET_OK);
  memset(&grid, 0, sizeof(grid));
  grid.left = 0.1f; grid.top = 0.1f; grid.width = 0.8f; grid.height = 0.8f;
  grid.series_indices[0] = 0u; grid.series_indices[1] = 1u;
  grid.series_indices[2] = 2u; grid.series_count = 3u; grid.visible = true;
  grid.axis_count = 3u;
  ASSERT_EQ(my_chart_set_grid(chart, 0u, &grid), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series_axis(chart, 0u, 0u), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series_axis(chart, 1u, 1u), MY_RET_OK);
  ASSERT_EQ(my_chart_set_series_axis(chart, 2u, 2u), MY_RET_OK);
  ASSERT_EQ(my_chart_get_grid_range(chart, 0u, 1u, &lo, &hi), MY_RET_OK);
  ASSERT_FLOAT_EQ(lo, 100.0f, 1e-6f); ASSERT_FLOAT_EQ(hi, 300.0f, 1e-6f);
  ASSERT_EQ(my_chart_get_grid_range(chart, 0u, 2u, &lo, &hi), MY_RET_OK);
  ASSERT_FLOAT_EQ(lo, -20.0f, 1e-6f); ASSERT_FLOAT_EQ(hi, -10.0f, 1e-6f);
  grid.axis_range_set[2] = true; grid.axis_min[2] = -50.0f;
  grid.axis_max[2] = 50.0f;
  ASSERT_EQ(my_chart_set_grid(chart, 0u, &grid), MY_RET_OK);
  ASSERT_EQ(my_chart_get_grid_range(chart, 0u, 2u, &lo, &hi), MY_RET_OK);
  ASSERT_FLOAT_EQ(lo, -50.0f, 1e-6f); ASSERT_FLOAT_EQ(hi, 50.0f, 1e-6f);
  grid.axis_count = 1u;
  ASSERT_EQ(my_chart_set_grid(chart, 0u, &grid), MY_RET_OK);
  ASSERT_EQ(my_chart_get_series_axis(chart, 2u), 0u);
  grid.axis_count = 0u;
  ASSERT_EQ(my_chart_set_grid(chart, 0u, &grid), MY_RET_INVALID_PARAMS);
  grid.axis_count = 4u;
  ASSERT_EQ(my_chart_set_grid(chart, 0u, &grid), MY_RET_INVALID_PARAMS);
  my_widget_unref(chart);
}

TEST(chart_non_cartesian_tooltip_lists_first_series_only) {
  static const float values[] = {10.0f, 30.0f, 20.0f};
  static const float other[] = {1.0f, 2.0f, 3.0f};
  my_chart_series_t first = {"Alpha", values, 3u, 0xE85D75FFu, 0u, false};
  my_chart_series_t second = {"Beta", other, 3u, 0x3A86FFFFu, 0u, false};
  const my_chart_mode_t modes[] = {MY_CHART_PIE, MY_CHART_FUNNEL,
                                   MY_CHART_RADAR};
  char tooltip[64];
  for (size_t m = 0u; m < 3u; m++) {
    my_widget_t* chart = my_chart_create(NULL, modes[m]);
    ASSERT_NOT_NULL(chart);
    ASSERT_EQ(my_chart_set_series(chart, 0u, &first), MY_RET_OK);
    ASSERT_EQ(my_chart_set_series(chart, 1u, &second), MY_RET_OK);
    ASSERT_EQ(my_chart_set_hover_index(chart, 1u), MY_RET_OK);
    ASSERT_EQ(my_chart_get_tooltip(chart, tooltip, sizeof(tooltip)),
              MY_RET_OK);
    ASSERT_TRUE(strstr(tooltip, "Alpha: 30.00") != NULL);
    ASSERT_TRUE(strstr(tooltip, "Beta") == NULL);
    ASSERT_EQ(my_chart_set_hover_index(chart, SIZE_MAX), MY_RET_OK);
    ASSERT_EQ(my_chart_get_tooltip(chart, tooltip, sizeof(tooltip)),
              MY_RET_NOT_SUPPORTED);
    my_widget_unref(chart);
  }
}

static size_t chart_count_nonwhite(const uint8_t* a, const uint8_t* b,
                                   uint32_t stride) {
  size_t diff = 0u;
  for (uint32_t y = 0u; y < 180u; y++) {
    for (uint32_t x = 0u; x < 320u; x++) {
      const uint8_t* pa = a + y * stride + x * 4u;
      const uint8_t* pb = b + y * stride + x * 4u;
      if (pa[0] != pb[0] || pa[1] != pb[1] || pa[2] != pb[2]) diff++;
    }
  }
  return diff;
}

TEST(chart_renders_series_value_labels) {
  static const float values[] = {10.0f, 30.0f, 20.0f};
  my_chart_series_t labeled = {"Bar", values, 3u, 0x3A86FFFFu, 0u, true};
  my_chart_series_t plain = {"Bar", values, 3u, 0x3A86FFFFu, 0u, false};
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  static uint8_t frame_with[320u * 180u * 4u];
  static uint8_t frame_without[320u * 180u * 4u];
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  {
    my_widget_t* chart = my_chart_create(NULL, MY_CHART_BAR);
    ASSERT_NOT_NULL(chart);
    chart->rect.w = 320;
    chart->rect.h = 180;
    ASSERT_EQ(my_chart_set_legend_visible(chart, false), MY_RET_OK);
    ASSERT_EQ(my_chart_set_series(chart, 0u, &labeled), MY_RET_OK);
    ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
    chart->vtable->on_paint(chart, canvas);
    ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
    pixels = my_lcd_mem_get_buffer(lcd);
    memcpy(frame_with, pixels, sizeof(frame_with));
    ASSERT_TRUE(my_chart_get_series_labels(chart, 0u));
    my_widget_unref(chart);
  }
  {
    my_widget_t* chart = my_chart_create(NULL, MY_CHART_BAR);
    ASSERT_NOT_NULL(chart);
    chart->rect.w = 320;
    chart->rect.h = 180;
    ASSERT_EQ(my_chart_set_legend_visible(chart, false), MY_RET_OK);
    ASSERT_EQ(my_chart_set_series(chart, 0u, &plain), MY_RET_OK);
    ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
    chart->vtable->on_paint(chart, canvas);
    ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
    pixels = my_lcd_mem_get_buffer(lcd);
    memcpy(frame_without, pixels, sizeof(frame_without));
    ASSERT_FALSE(my_chart_get_series_labels(chart, 0u));
    my_widget_unref(chart);
  }
  ASSERT_TRUE(chart_count_nonwhite(frame_with, frame_without,
                                   my_lcd_mem_get_stride(lcd)) > 10u);
  {
    my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
    my_chart_series_t line = {"L", values, 3u, 0xE85D75FFu, 0u, true};
    my_chart_series_t line_plain = {"L", values, 3u, 0xE85D75FFu, 0u, false};
    ASSERT_NOT_NULL(chart);
    chart->rect.w = 320;
    chart->rect.h = 180;
    ASSERT_EQ(my_chart_set_legend_visible(chart, false), MY_RET_OK);
    ASSERT_EQ(my_chart_set_series(chart, 0u, &line), MY_RET_OK);
    ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
    chart->vtable->on_paint(chart, canvas);
    ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
    pixels = my_lcd_mem_get_buffer(lcd);
    memcpy(frame_with, pixels, sizeof(frame_with));
    ASSERT_EQ(my_chart_set_series(chart, 0u, &line_plain), MY_RET_OK);
    ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
    chart->vtable->on_paint(chart, canvas);
    ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
    pixels = my_lcd_mem_get_buffer(lcd);
    memcpy(frame_without, pixels, sizeof(frame_without));
    ASSERT_TRUE(chart_count_nonwhite(frame_with, frame_without,
                                     my_lcd_mem_get_stride(lcd)) > 10u);
    my_widget_unref(chart);
  }
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
}


TEST(chart_treemap_graph_calendar_hover_hit) {
  static const float tvals[] = {60.0f, 30.0f, 10.0f};
  static const float gvals[] = {5.0f, 8.0f, 3.0f, 6.00f};
  static const float cvals[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
  my_event_t ev;
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_TREEMAP);
  my_chart_series_t s = {"S", tvals, 3u, 0u, 0u, false};
  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &s), MY_RET_OK);
  ev = my_event_init(MY_EVENT_POINTER_MOVE);
  ev.u.pointer.button = 1u;
  ev.u.pointer.x = 52;
  ev.u.pointer.y = 90;
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 0u);
  ASSERT_EQ(my_chart_set_series_visible(chart, 0u, false), MY_RET_OK);
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  my_widget_unref(chart);

  chart = my_chart_create(NULL, MY_CHART_GRAPH);
  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &(my_chart_series_t){"G", gvals, 4u, 0u, 0u, false}), MY_RET_OK);
  ev.u.pointer.x = 218; ev.u.pointer.y = 92;
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 0u);
  ASSERT_EQ(my_chart_set_series_visible(chart, 0u, false), MY_RET_OK);
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  ev.u.pointer.x = 10; ev.u.pointer.y = 10;
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  my_widget_unref(chart);

  chart = my_chart_create(NULL, MY_CHART_CALENDAR);
  ASSERT_NOT_NULL(chart);
  chart->rect.w = 320; chart->rect.h = 180;
  ASSERT_EQ(my_chart_set_series(chart, 0u, &(my_chart_series_t){"C", cvals, 8u, 0u, 0u, false}), MY_RET_OK);
  ev.u.pointer.x = 52; ev.u.pointer.y = 40;
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 0u);
  ev.u.pointer.x = 52; ev.u.pointer.y = 100;
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_OK);
  ASSERT_EQ(my_chart_get_hover_index(chart), 7u);
  ASSERT_EQ(my_chart_set_series_visible(chart, 0u, false), MY_RET_OK);
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  ev.u.pointer.x = 315; ev.u.pointer.y = 170;
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  ev.u.pointer.x = 2; ev.u.pointer.y = 175;
  ASSERT_EQ(chart->vtable->on_event(chart, &ev), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_chart_get_hover_index(chart), SIZE_MAX);
  my_widget_unref(chart);
}

TEST_MAIN_BEGIN()
  RUN_TEST(chart_three_axis_ranges_are_isolated);
  RUN_TEST(chart_rejects_invalid_series_and_range);
  RUN_TEST(chart_formats_fractional_axis_ticks);
  RUN_TEST(chart_hidden_series_excluded_from_auto_range);
  RUN_TEST(chart_manages_mark_points);
  RUN_TEST(chart_data_zoom_limits_category_window);
  RUN_TEST(chart_animation_progress_is_deterministic);
  RUN_TEST(chart_manages_mark_lines);
  RUN_TEST(chart_manages_mark_areas);
  RUN_TEST(chart_axis_configuration);
  RUN_TEST(chart_secondary_axis_binding);
  RUN_TEST(chart_series_visibility_controls_tooltip);
  RUN_TEST(chart_legend_click_toggles_series_visibility);
  RUN_TEST(chart_hover_emphasis_is_reported);
  RUN_TEST(chart_supports_stacked_bar_mode);
  RUN_TEST(chart_supports_scatter_mode);
  RUN_TEST(chart_supports_pie_mode);
  RUN_TEST(chart_supports_radar_mode_and_rejects_invalid_data);
  RUN_TEST(chart_funnel_hover_tracks_bands_and_clears_outside);
  RUN_TEST(chart_radar_hover_tracks_spokes_and_clears_outside);
  RUN_TEST(chart_supports_funnel_mode);
  RUN_TEST(chart_supports_heatmap_mode);
  RUN_TEST(chart_supports_boxplot_mode);
  RUN_TEST(chart_paints_radar_polygon_to_software_canvas);
  RUN_TEST(chart_visual_map_configuration);
  RUN_TEST(chart_brush_selects_category_window);
  RUN_TEST(chart_accessible_description_and_keyboard_navigation);
  RUN_TEST(chart_paints_visual_map_legend);
  RUN_TEST(chart_stacked_endpoint_matches_segment_geometry);
  RUN_TEST(chart_stacked_bars_share_category_slot);
  RUN_TEST(chart_clamps_values_and_formats_hover_tooltip);
  RUN_TEST(chart_hover_tooltip_includes_all_series_at_category);
  RUN_TEST(chart_tooltip_flips_left_at_right_edge);
  RUN_TEST(chart_tooltip_stays_right_in_mid_chart);
  RUN_TEST(chart_paints_visible_series_to_software_canvas);
  RUN_TEST(chart_paints_grouped_bar_series_to_software_canvas);
  RUN_TEST(chart_paints_mark_point_annotation);
  RUN_TEST(chart_paints_mark_area);
  RUN_TEST(chart_line_series_share_category_positions);
  RUN_TEST(chart_renders_at_supported_viewports);
  RUN_TEST(chart_hit_test_is_pure_and_bounded);
  RUN_TEST(chart_supports_candlestick_mode);
  RUN_TEST(chart_supports_gauge_mode);
  RUN_TEST(chart_supports_sankey_mode);
  RUN_TEST(chart_supports_parallel_mode);
  RUN_TEST(chart_supports_treemap_mode);
  RUN_TEST(chart_supports_graph_mode);
  RUN_TEST(chart_supports_calendar_mode);
  RUN_TEST(chart_supports_theme_river_mode);
  RUN_TEST(chart_multi_grid_layout_and_assignment);
  RUN_TEST(chart_grid_link_flag_validation);
  RUN_TEST(chart_multi_grid_renders_series_in_own_rect);
  RUN_TEST(chart_multi_grid_auto_range_isolated);
  RUN_TEST(chart_multi_grid_hit_test_resolves_own_grid);
  RUN_TEST(chart_non_cartesian_tooltip_lists_first_series_only);
  RUN_TEST(chart_renders_series_value_labels);
  RUN_TEST(chart_treemap_graph_calendar_hover_hit);
TEST_MAIN_END()
