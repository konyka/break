/**
 * @file echarts_demo.c
 * @brief Headless ECharts feature demo: renders every supported feature to
 *        PPM files and self-checks each frame.
 *
 * Usage: echarts_demo [output_dir]   (default: .)
 */
#include "myr/my_font.h"
#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/echarts/my_echart.h"
#include "myui/echarts/my_echart_adapter.h"
#include "myui/echarts/my_echart_animation.h"
#include "myui/echarts/my_echart_event.h"
#include "myui/echarts/my_echart_mvvm.h"
#include "myui/echarts/my_echart_option.h"
#include "myui/echarts/my_echart_option_json.h"
#include "myui/widgets/my_chart.h"
#include "mymvvm/my_view_model.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*scene_fn)(const char* path);

static my_font_t* g_font;
static size_t g_colored;

static void dump_ppm(const uint8_t* pixels, uint32_t w, uint32_t h,
                     uint32_t stride, const char* path) {
  FILE* f = fopen(path, "wb");
  uint32_t y;
  if (f == NULL) return;
  (void)fprintf(f, "P6\n%u %u\n255\n", w, h);
  for (y = 0u; y < h; y++) {
    uint32_t x;
    for (x = 0u; x < w; x++) {
      const uint8_t* p = pixels + y * stride + x * 4u;
      uint8_t rgb[3] = {p[2], p[1], p[0]};
      (void)fwrite(rgb, 1u, sizeof(rgb), f);
    }
  }
  (void)fclose(f);
}

static void render(my_widget_t* chart, const char* dir, const char* name) {
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  char path[512];
  uint8_t* pixels;
  size_t i;
  if (lcd == NULL || canvas == NULL) {
    printf("FAIL %s (canvas)\n", name);
    exit(1);
  }
  chart->rect.w = 320;
  chart->rect.h = 180;
  if (my_vgcanvas_begin_frame(canvas, NULL) == MY_RET_OK) {
    my_vgcanvas_set_font(canvas, g_font, 13);
    chart->vtable->on_paint(chart, canvas);
  }
  (void)my_vgcanvas_end_frame(canvas);
  pixels = my_lcd_mem_get_buffer(lcd);
  g_colored = 0u;
  for (i = 0u; i < 320u * 180u * 4u; i += 4u) {
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
        pixels[i + 2u] != 0xFFu)
      g_colored++;
  }
  (void)snprintf(path, sizeof(path), "%s/%s.ppm", dir, name);
  dump_ppm(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd), path);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(chart);
}

static my_widget_t* chart_with(my_chart_mode_t mode, const float* values,
                               size_t count, const char* name) {
  my_widget_t* chart = my_chart_create(NULL, mode);
  my_chart_series_t series = {name, values, count, 0u, 0u, false};
  if (chart == NULL || my_chart_set_series(chart, 0u, &series) != MY_RET_OK) {
    printf("FAIL setup %s\n", name);
    exit(1);
  }
  return chart;
}

static const char* k_labels[] = {"Mon", "Tue", "Wed", "Thu", "Fri"};
static const float k_five[] = {5.0f, 20.0f, 12.0f, 28.0f, 9.0f};
static const float k_five2[] = {12.0f, 6.0f, 18.0f, 8.0f, 15.0f};

static void scene_line(const char* dir) {
  my_widget_t* c = chart_with(MY_CHART_LINE, k_five, 5u, "line");
  my_chart_series_t s = {"Revenue", k_five, 5u, 0u, 0u, true};
  (void)my_chart_set_title(c, "Line + value labels");
  (void)my_chart_set_labels(c, k_labels, 5u);
  (void)my_chart_set_series(c, 0u, &s);
  render(c, dir, "01_line");
}

static void scene_bar_grouped(const char* dir) {
  my_widget_t* c = my_chart_create(NULL, MY_CHART_BAR);
  my_chart_series_t a = {"Alpha", k_five, 5u, 0u, 0u, false};
  my_chart_series_t b = {"Beta", k_five2, 5u, 0u, 0u, false};
  (void)my_chart_set_series(c, 0u, &a);
  (void)my_chart_set_series(c, 1u, &b);
  (void)my_chart_set_labels(c, k_labels, 5u);
  render(c, dir, "02_bar_grouped");
}

static void scene_bar_stacked(const char* dir) {
  my_widget_t* c = my_chart_create(NULL, MY_CHART_BAR);
  my_chart_series_t a = {"A", k_five, 5u, 0u, 0u, false};
  my_chart_series_t b = {"B", k_five2, 5u, 0u, 0u, false};
  (void)my_chart_set_series(c, 0u, &a);
  (void)my_chart_set_series(c, 1u, &b);
  (void)my_chart_set_stacked(c, true);
  render(c, dir, "03_bar_stacked");
}

static void scene_dual_axis(const char* dir) {
  my_widget_t* c = my_chart_create(NULL, MY_CHART_LINE);
  my_chart_series_t a = {"Left", k_five, 5u, 0u, 0u, false};
  my_chart_series_t b = {"Right", k_five2, 5u, 0u, 1u, false};
  (void)my_chart_set_series(c, 0u, &a);
  (void)my_chart_set_series(c, 1u, &b);
  (void)my_chart_set_range(c, 0.0f, 30.0f);
  (void)my_chart_set_secondary_range(c, 0.0f, 20.0f);
  render(c, dir, "04_dual_axis");
}

static void scene_scatter_visualmap(const char* dir) {
  my_widget_t* c = chart_with(MY_CHART_SCATTER, k_five, 5u, "scat");
  (void)my_chart_set_visual_map(c, 0.0f, 30.0f, 0x3A86FFFFu, 0xE85D75FFu);
  render(c, dir, "05_scatter_visualmap");
}

static void scene_datazoom(const char* dir) {
  my_widget_t* c = chart_with(MY_CHART_LINE, k_five, 5u, "zoomed");
  (void)my_chart_set_labels(c, k_labels, 5u);
  (void)my_chart_set_data_zoom(c, 1u, 3u);
  render(c, dir, "06_datazoom");
}

static void scene_annotations(const char* dir) {
  static const float vals[] = {4.0f, 12.0f, 7.0f, 18.0f, 6.0f};
  my_chart_snapshot_t snap;
  my_chart_series_t series = {"Ann", vals, 5u, 0u, 0u, false};
  static const bool visible[1] = {true};
  static const my_chart_mark_point_t marks[1] = {{0u, 3u, "peak"}};
  static const my_chart_mark_line_state_t lines[1] = {{10.0f, "avg", 0u}};
  static const my_chart_mark_area_state_t areas[1] = {
      {8.0f, 14.0f, "band", 0x3A86FF33u}};
  my_widget_t* c = my_chart_create(NULL, MY_CHART_LINE);
  memset(&snap, 0, sizeof(snap));
  snap.mode = MY_CHART_LINE;
  snap.title = "markPoint / markLine / markArea";
  snap.labels = k_labels;
  snap.label_count = 5u;
  snap.series = &series;
  snap.series_visible = visible;
  snap.series_count = 1u;
  snap.show_legend = true;
  snap.tooltip_enabled = true;
  snap.marks = marks;
  snap.mark_count = 1u;
  snap.lines = lines;
  snap.line_count = 1u;
  snap.areas = areas;
  snap.area_count = 1u;
  if (my_chart_apply_snapshot(c, &snap) != MY_RET_OK) {
    printf("FAIL annotations snapshot\n");
    exit(1);
  }
  render(c, dir, "07_annotations");
}

static void scene_pie_hover(const char* dir) {
  my_widget_t* c = chart_with(MY_CHART_PIE, k_five, 5u, "share");
  (void)my_chart_set_hover_index(c, 2u);
  render(c, dir, "08_pie_hover");
}

static void scene_radar(const char* dir) {
  my_widget_t* c = chart_with(MY_CHART_RADAR, k_five, 5u, "skills");
  (void)my_chart_set_labels(c, k_labels, 5u);
  render(c, dir, "09_radar");
}

static void scene_funnel(const char* dir) {
  static const float vals[] = {100.0f, 60.0f, 40.0f, 25.0f, 10.0f};
  render(chart_with(MY_CHART_FUNNEL, vals, 5u, "stages"), dir, "10_funnel");
}

static void scene_heatmap(const char* dir) {
  static const float vals[] = {1.0f, 5.0f, 3.0f, 4.0f, 2.0f,
                               5.0f, 2.0f, 4.0f, 1.0f, 3.0f};
  render(chart_with(MY_CHART_HEATMAP, vals, 10u, "heat"), dir, "11_heatmap");
}

static void scene_boxplot(const char* dir) {
  static const float vals[] = {1.0f, 4.0f, 6.0f, 8.0f, 12.0f,
                               2.0f, 5.0f, 7.0f, 9.0f, 13.0f};
  render(chart_with(MY_CHART_BOXPLOT, vals, 10u, "boxes"), dir, "12_boxplot");
}

static void scene_candlestick(const char* dir) {
  static const float vals[] = {10.0f, 12.0f, 9.0f, 15.0f, 20.0f, 18.0f,
                               17.0f, 22.0f};
  render(chart_with(MY_CHART_CANDLESTICK, vals, 8u, "price"), dir,
         "13_candlestick");
}

static void scene_gallery(const char* dir) {
  struct {
    const char* name;
    my_chart_mode_t mode;
    const float* values;
    size_t count;
  } items[] = {
      {"14_gauge", MY_CHART_GAUGE, k_five, 5u},
      {"15_sankey", MY_CHART_SANKEY, k_five, 5u},
      {"16_parallel", MY_CHART_PARALLEL, k_five, 5u},
      {"17_treemap", MY_CHART_TREEMAP, k_five, 5u},
      {"18_graph", MY_CHART_GRAPH, k_five, 5u},
      {"19_calendar", MY_CHART_CALENDAR, k_five, 5u},
      {"20_themeriver", MY_CHART_THEME_RIVER, k_five, 5u}};
  size_t i;
  for (i = 0u; i < sizeof(items) / sizeof(items[0]); i++)
    render(chart_with(items[i].mode, items[i].values, items[i].count, "s"),
           dir, items[i].name);
}

static void scene_multigrid(const char* dir) {
  my_widget_t* c = my_chart_create(NULL, MY_CHART_LINE);
  my_chart_series_t top = {"Top", k_five, 5u, 0u, 0u, false};
  my_chart_series_t bottom = {"Bottom", k_five2, 5u, 0u, 0u, false};
  my_chart_grid_desc_t grid;
  (void)my_chart_set_series(c, 0u, &top);
  (void)my_chart_set_series(c, 1u, &bottom);
  (void)my_chart_set_grid_count(c, 2u);
  memset(&grid, 0, sizeof(grid));
  grid.left = 0.05f;
  grid.top = 0.05f;
  grid.width = 0.9f;
  grid.height = 0.4f;
  grid.series_indices[0] = 0u;
  grid.series_count = 1u;
  grid.axis_count = 1u;
  grid.visible = true;
  (void)my_chart_set_grid(c, 0u, &grid);
  grid.top = 0.55f;
  grid.series_indices[0] = 1u;
  (void)my_chart_set_grid(c, 1u, &grid);
  render(c, dir, "21_multigrid");
}

static void scene_multiaxis(const char* dir) {
  static const float a[] = {5.0f, 10.0f, 8.0f};
  static const float b[] = {50.0f, 90.0f, 70.0f};
  static const float d[] = {500.0f, 900.0f, 700.0f};
  my_widget_t* c = my_chart_create(NULL, MY_CHART_LINE);
  my_chart_series_t s0 = {"A", a, 3u, 0u, 0u, false};
  my_chart_series_t s1 = {"B", b, 3u, 0u, 1u, false};
  my_chart_series_t s2 = {"C", d, 3u, 0u, 2u, false};
  my_chart_grid_desc_t grid;
  (void)my_chart_set_series(c, 0u, &s0);
  (void)my_chart_set_series(c, 1u, &s1);
  (void)my_chart_set_series(c, 2u, &s2);
  memset(&grid, 0, sizeof(grid));
  grid.left = 0.05f;
  grid.top = 0.05f;
  grid.width = 0.85f;
  grid.height = 0.85f;
  grid.series_indices[0] = 0u;
  grid.series_indices[1] = 1u;
  grid.series_indices[2] = 2u;
  grid.series_count = 3u;
  grid.axis_count = 3u;
  grid.axis_range_set[0] = true;
  grid.axis_min[0] = 0.0f;
  grid.axis_max[0] = 10.0f;
  grid.axis_range_set[1] = true;
  grid.axis_min[1] = 0.0f;
  grid.axis_max[1] = 100.0f;
  grid.axis_range_set[2] = true;
  grid.axis_min[2] = 0.0f;
  grid.axis_max[2] = 1000.0f;
  grid.visible = true;
  (void)my_chart_set_grid(c, 0u, &grid);
  render(c, dir, "22_multiaxis3");
}

static void scene_linked_grids(const char* dir) {
  my_widget_t* c = my_chart_create(NULL, MY_CHART_LINE);
  my_chart_series_t top = {"Top", k_five, 5u, 0u, 0u, false};
  my_chart_series_t bottom = {"Bottom", k_five2, 5u, 0u, 0u, false};
  my_chart_grid_desc_t grid;
  (void)my_chart_set_series(c, 0u, &top);
  (void)my_chart_set_series(c, 1u, &bottom);
  (void)my_chart_set_grid_count(c, 2u);
  memset(&grid, 0, sizeof(grid));
  grid.left = 0.05f;
  grid.top = 0.05f;
  grid.width = 0.9f;
  grid.height = 0.4f;
  grid.series_indices[0] = 0u;
  grid.series_count = 1u;
  grid.axis_count = 1u;
  grid.link_axis_pointer = true;
  grid.visible = true;
  (void)my_chart_set_grid(c, 0u, &grid);
  grid.top = 0.55f;
  grid.series_indices[0] = 1u;
  (void)my_chart_set_grid(c, 1u, &grid);
  (void)my_chart_set_hover_index(c, 2u);
  render(c, dir, "23_linked_grids");
}

static void scene_group_sync(const char* dir) {
  my_widget_t* a = chart_with(MY_CHART_LINE, k_five, 5u, "A");
  my_widget_t* b = chart_with(MY_CHART_LINE, k_five2, 5u, "B");
  (void)my_chart_group_join(a, 1u);
  (void)my_chart_group_join(b, 1u);
  (void)my_chart_set_data_zoom(a, 1u, 3u);
  (void)my_chart_set_hover_index(a, 1u);
  render(a, dir, "24_group_a");
  render(b, dir, "24_group_b");
}

static void scene_dataset_transform(const char* dir) {
  static const double unsorted[] = {30.0, 10.0, 20.0};
  static const double key[] = {3.0, 1.0, 2.0};
  static const my_echart_dimension_input_t dims[] = {
      {"key", key, 3u}, {"value", unsorted, 3u}};
  my_echart_series_input_t series = {"v", "Sorted", MY_ECHART_BAR, unsorted,
                                     3u, 0u, 0u, NULL, true, NULL, false};
  my_echart_option_input_t input = {"dataset sort", NULL, 0u, &series, 1u,
      false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u,
      NULL, 0u, NULL, 0u, NULL, 0u, dims, 2u,
      MY_ECHART_TRANSFORM_SORT_DESC, "key", MY_ECHART_FILTER_EQ, NULL, 0.0,
      NULL, 0u, false};
  my_echart_option_t option;
  my_widget_t* c = my_chart_create(NULL, MY_CHART_BAR);
  my_echart_adapter_t* adapter;
  my_echart_option_init(&option, NULL);
  if (my_echart_option_copy(&option, &input, NULL) != MY_RET_OK) {
    printf("FAIL dataset copy\n");
    exit(1);
  }
  adapter = my_echart_adapter_create(c, NULL);
  if (adapter == NULL || my_echart_adapter_apply(adapter, &option) != MY_RET_OK) {
    printf("FAIL dataset apply\n");
    exit(1);
  }
  render(c, dir, "25_dataset_sort");
  my_echart_adapter_destroy(adapter);
  my_echart_option_free(&option);
}

static void scene_model_action(const char* dir) {
  static const double vals[] = {4.0, 12.0, 7.0, 18.0, 6.0};
  my_echart_series_input_t series = {"a", "Series A", MY_ECHART_LINE, vals,
                                     5u, 0u, 0u, NULL, true, NULL, false};
  my_echart_option_input_t input = {"action dataZoom", NULL, 0u, &series, 1u,
      false, false, false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u,
      NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u,
      MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0,
      NULL, 0u, false};
  my_echart_model_action_t action;
  my_echart_t* model = my_echart_create(NULL);
  my_widget_t* c = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter;
  if (my_echart_set_option(model, &input, true, false) != MY_RET_OK) {
    printf("FAIL model set option\n");
    exit(1);
  }
  adapter = my_echart_adapter_create(c, NULL);
  if (adapter == NULL ||
      my_echart_adapter_sync_model(adapter, model) != MY_RET_OK) {
    printf("FAIL action sync\n");
    exit(1);
  }
  memset(&action, 0, sizeof(action));
  action.type = MY_ECHART_MODEL_ACTION_DATA_ZOOM;
  action.payload.zoom_start = 1u;
  action.payload.zoom_end = 3u;
  if (my_echart_model_dispatch_action(model, &action) != MY_RET_OK ||
      my_echart_adapter_sync_model(adapter, model) != MY_RET_OK) {
    printf("FAIL action dispatch\n");
    exit(1);
  }
  render(c, dir, "26_model_action");
  my_echart_adapter_destroy(adapter);
  my_echart_destroy(model);
}

static void scene_mvvm(const char* dir) {
  static const double first[] = {5.0f, 10.0f, 8.0f};
  static const double second[] = {12.0f, 4.0f, 9.0f};
  my_echart_series_input_t s = {"v", "Values", MY_ECHART_LINE, first, 3u, 0u,
                                0u, NULL, true, NULL, false};
  my_echart_option_input_t in = {"MVVM", NULL, 0u, &s, 1u, false, false,
      false, 0.0, 0.0, false, 0u, 0u, false, 0.0, 0.0, 0u, 0u,
      NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u, MY_ECHART_TRANSFORM_NONE,
      NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u, false};
  my_echart_option_t o1;
  my_echart_option_t o2;
  my_view_model_t* vm = my_view_model_dummy_create(NULL);
  my_binding_context_t* ctx = my_binding_context_create(NULL, vm);
  my_widget_t* c = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter;
  my_echart_mvvm_binding_t* binding;
  my_value_t value;
  my_echart_option_init(&o1, NULL);
  my_echart_option_init(&o2, NULL);
  in.title = "First";
  if (my_echart_option_copy(&o1, &in, NULL) != MY_RET_OK) exit(1);
  in.title = "Second";
  in.series = &(my_echart_series_input_t){"v", "Values", MY_ECHART_LINE,
                                           second, 3u, 0u, 0u, NULL, true,
                                           NULL, false};
  if (my_echart_option_copy(&o2, &in, NULL) != MY_RET_OK) exit(1);
  adapter = my_echart_adapter_create(c, NULL);
  my_value_init(&value, NULL);
  my_value_set_pointer(&value, &o1);
  (void)my_view_model_set_prop(vm, "option", &value);
  binding = my_echart_mvvm_bind_option(NULL, ctx, adapter, "option");
  if (binding == NULL) {
    printf("FAIL mvvm bind\n");
    exit(1);
  }
  {
    my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u,
                                      MY_PIXEL_FORMAT_BGRA8888);
    my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
    char path[512];
    uint8_t* pixels;
    c->rect.w = 320;
    c->rect.h = 180;
    (void)my_vgcanvas_begin_frame(canvas, NULL);
    my_vgcanvas_set_font(canvas, g_font, 13);
    c->vtable->on_paint(c, canvas);
    (void)my_vgcanvas_end_frame(canvas);
    pixels = my_lcd_mem_get_buffer(lcd);
    g_colored = 0u;
    for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
      if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
          pixels[i + 2u] != 0xFFu)
        g_colored++;
    (void)snprintf(path, sizeof(path), "%s/27_mvvm_first.ppm", dir);
    dump_ppm(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd), path);
    my_value_reset(&value);
    my_value_init(&value, NULL);
    my_value_set_pointer(&value, &o2);
    (void)my_view_model_set_prop(vm, "option", &value);
    (void)my_vgcanvas_begin_frame(canvas, NULL);
    my_vgcanvas_set_font(canvas, g_font, 13);
    c->vtable->on_paint(c, canvas);
    (void)my_vgcanvas_end_frame(canvas);
    (void)snprintf(path, sizeof(path), "%s/27_mvvm_second.ppm", dir);
    dump_ppm(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd), path);
    my_vgcanvas_destroy(canvas);
    my_lcd_destroy(lcd);
  }
  my_echart_mvvm_unbind_option(binding);
  my_value_reset(&value);
  my_echart_adapter_destroy(adapter);
  my_widget_unref(c);
  my_binding_context_destroy(ctx);
  my_view_model_unref(vm);
  my_echart_option_free(&o1);
  my_echart_option_free(&o2);
}

static void scene_json_option(const char* dir) {
  const char* json =
      "{\"title\":{\"text\":\"JSON option\"},"
      "\"xAxis\":{\"data\":[\"A\",\"B\",\"C\"]},"
      "\"yAxis\":{\"min\":0,\"max\":40},"
      "\"legend\":{\"show\":false},"
      "\"series\":[{\"name\":\"Sales\",\"type\":\"bar\","
      "\"data\":[10,30,20],\"label\":{\"show\":true},"
      "\"itemStyle\":{\"color\":\"#3A86FF\"}}]}";
  my_echart_json_doc_t* doc =
      my_echart_json_doc_parse(json, strlen(json), NULL);
  const my_echart_option_input_t* input;
  my_echart_option_t option;
  my_widget_t* c = my_chart_create(NULL, MY_CHART_BAR);
  my_echart_adapter_t* adapter;
  if (doc == NULL || my_echart_json_doc_error(doc) != NULL) {
    printf("FAIL json parse: %s\n",
           doc != NULL ? my_echart_json_doc_error(doc) : "null doc");
    exit(1);
  }
  input = my_echart_json_doc_option(doc);
  my_echart_option_init(&option, NULL);
  if (my_echart_option_copy(&option, input, NULL) != MY_RET_OK) {
    printf("FAIL json copy\n");
    exit(1);
  }
  adapter = my_echart_adapter_create(c, NULL);
  if (adapter == NULL || my_echart_adapter_apply(adapter, &option) != MY_RET_OK) {
    printf("FAIL json apply\n");
    exit(1);
  }
  render(c, dir, "28_json_option");
  my_echart_adapter_destroy(adapter);
  my_echart_option_free(&option);
  my_echart_json_doc_destroy(&doc);
}

static void scene_animation(const char* dir) {
  my_widget_t* c = chart_with(MY_CHART_LINE, k_five, 5u, "anim");
  (void)my_chart_set_animation_progress(c, 0.35f);
  {
    my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u,
                                      MY_PIXEL_FORMAT_BGRA8888);
    my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
    char path[512];
    uint8_t* pixels;
    c->rect.w = 320;
    c->rect.h = 180;
    (void)my_vgcanvas_begin_frame(canvas, NULL);
    my_vgcanvas_set_font(canvas, g_font, 13);
    c->vtable->on_paint(c, canvas);
    (void)my_vgcanvas_end_frame(canvas);
    pixels = my_lcd_mem_get_buffer(lcd);
    g_colored = 0u;
    for (size_t i = 0u; i < 320u * 180u * 4u; i += 4u)
      if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
          pixels[i + 2u] != 0xFFu)
        g_colored++;
    (void)snprintf(path, sizeof(path), "%s/29_animation.ppm", dir);
    dump_ppm(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd), path);
    my_vgcanvas_destroy(canvas);
    my_lcd_destroy(lcd);
    my_widget_unref(c);
  }
}

typedef struct {
  const char* name;
  scene_fn fn;
} scene_entry_t;

int main(int argc, char** argv) {
  static const scene_entry_t scenes[] = {
      {"01_line", scene_line},
      {"02_bar_grouped", scene_bar_grouped},
      {"03_bar_stacked", scene_bar_stacked},
      {"04_dual_axis", scene_dual_axis},
      {"05_scatter_visualmap", scene_scatter_visualmap},
      {"06_datazoom", scene_datazoom},
      {"07_annotations", scene_annotations},
      {"08_pie_hover", scene_pie_hover},
      {"09_radar", scene_radar},
      {"10_funnel", scene_funnel},
      {"11_heatmap", scene_heatmap},
      {"12_boxplot", scene_boxplot},
      {"13_candlestick", scene_candlestick},
      {"gallery", scene_gallery},
      {"21_multigrid", scene_multigrid},
      {"22_multiaxis3", scene_multiaxis},
      {"23_linked_grids", scene_linked_grids},
      {"24_group_sync", scene_group_sync},
      {"25_dataset_sort", scene_dataset_transform},
      {"26_model_action", scene_model_action},
      {"27_mvvm", scene_mvvm},
      {"28_json_option", scene_json_option},
      {"29_animation", scene_animation}};
  const char* dir = argc > 1 ? argv[1] : ".";
  g_font = my_font_stb_create(NULL,
      "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf",
      4096u);
  size_t failures = 0u;
  size_t i;
  for (i = 0u; i < sizeof(scenes) / sizeof(scenes[0]); i++) {
    g_colored = 0u;
    scenes[i].fn(dir);
    if (g_colored < 150u) {
      printf("FAIL %s (%zu colored pixels)\n", scenes[i].name, g_colored);
      failures++;
    } else {
      printf("OK   %s (%zu px)\n", scenes[i].name, g_colored);
    }
  }
  if (failures != 0u) {
    printf("%zu scene(s) FAILED\n", failures);
    return 1;
  }
  printf("all scenes rendered\n");
  return 0;
}
