#include "test_framework.h"

#include <float.h>
#include <stdint.h>

#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/echarts/my_echart_adapter.h"
#include "myui/widgets/my_chart.h"

typedef struct fail_alloc_t { size_t calls; size_t fail_at; } fail_alloc_t;

static void* fa_alloc(void* ctx, size_t size) {
  fail_alloc_t* state = (fail_alloc_t*)ctx;
  if (++state->calls == state->fail_at) return NULL;
  return malloc(size);
}
static void* fa_calloc(void* ctx, size_t n, size_t size) {
  void* p;
  fail_alloc_t* state = (fail_alloc_t*)ctx;
  if (++state->calls == state->fail_at) return NULL;
  p = malloc(n * size);
  if (p != NULL) memset(p, 0, n * size);
  return p;
}
static void* fa_realloc(void* ctx, void* ptr, size_t size) {
  fail_alloc_t* state = (fail_alloc_t*)ctx;
  if (++state->calls == state->fail_at) return NULL;
  return realloc(ptr, size);
}
static void fa_free(void* ctx, void* ptr) { (void)ctx; free(ptr); }

static my_echart_option_t make_option(const double* values, size_t count,
                                      const char* title, const char* stack,
                                      my_echart_series_type_t type) {
  my_echart_series_input_t series = {"series", "Series", type, values, count,
                                     0xE85D75FFu, 0u, stack, true};
  my_echart_option_input_t input = {title, NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u};
  my_echart_option_t option;
  my_echart_option_init(&option, NULL);
  if (my_echart_option_copy(&option, &input, NULL) != MY_RET_OK) {
    memset(&option, 0, sizeof(option));
  }
  return option;
}

TEST(echart_adapter_converts_and_retains_values) {
  const double values[] = {1.0, 2.5};
  my_echart_option_t option = make_option(values, 2u, "first", NULL, MY_ECHART_LINE);
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter = my_echart_adapter_create(chart, NULL);
  ASSERT_NOT_NULL(adapter);
  ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_OK);
  my_echart_option_free(&option);
  ASSERT_EQ(((my_chart_t*)chart)->series[0].count, 2u);
  ASSERT_TRUE(fabsf(((my_chart_t*)chart)->series[0].values[0] - 1.0f) < 0.0001f);
  ASSERT_TRUE(fabsf(((my_chart_t*)chart)->series[0].values[1] - 2.5f) < 0.0001f);
  my_echart_adapter_destroy(adapter);
  my_widget_unref(chart);
}

TEST(echart_adapter_rejects_without_mutating) {
  const double values[] = {3.0};
  my_echart_option_t good = make_option(values, 1u, "good", NULL, MY_ECHART_LINE);
  my_echart_option_t bad = make_option(values, 1u, "bad", "stack", MY_ECHART_LINE);
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter = my_echart_adapter_create(chart, NULL);
  ASSERT_EQ(my_echart_adapter_apply(adapter, &good), MY_RET_OK);
  ASSERT_EQ(my_echart_adapter_apply(adapter, &bad), MY_RET_NOT_SUPPORTED);
  ASSERT_TRUE(strcmp(((my_chart_t*)chart)->title, "good") == 0);
  ASSERT_EQ(((my_chart_t*)chart)->series_count, 1u);
  ASSERT_TRUE(fabsf(((my_chart_t*)chart)->series[0].values[0] - 3.0f) < 0.0001f);
  ASSERT_EQ(my_echart_adapter_apply(adapter, &bad), MY_RET_NOT_SUPPORTED);
  ASSERT_TRUE(strcmp(((my_chart_t*)chart)->title, "good") == 0);
  my_echart_adapter_destroy(adapter);
  my_widget_unref(chart);
  my_echart_option_free(&good);
  my_echart_option_free(&bad);
}

TEST(echart_adapter_rejects_mixed_types_and_float_overflow) {
  const double values[] = {1.0};
  my_echart_series_input_t series[2] = {
      {"a", "A", MY_ECHART_LINE, values, 1u, 0u, 0u, NULL, true},
      {"b", "B", MY_ECHART_BAR, values, 1u, 0u, 0u, NULL, true}};
  my_echart_option_input_t input = {"bad", NULL, 0u, series, 2u, false, false, 0.0, 0.0, false, 0u, 0u};
  my_echart_option_t option;
  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter = my_echart_adapter_create(chart, NULL);
  ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_NOT_SUPPORTED);
  option.series[0].data[0] = (double)FLT_MAX * 2.0;
  ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_INVALID_PARAMS);
  my_echart_adapter_destroy(adapter);
  my_widget_unref(chart);
  my_echart_option_free(&option);
}

TEST(echart_adapter_oom_rolls_back) {
  const double values[] = {4.0};
  fail_alloc_t state = {0u, SIZE_MAX};
  const my_allocator_t allocator = {&state, fa_alloc, fa_calloc, fa_realloc, fa_free};
  my_echart_option_t option = make_option(values, 1u, "new", NULL, MY_ECHART_LINE);
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter = my_echart_adapter_create(chart, &allocator);
  ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_OK);
  state.calls = 0u;
  state.fail_at = 2u;
  option.title[0] = 'o';
  ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_OOM);
  ASSERT_TRUE(strcmp(((my_chart_t*)chart)->title, "new") == 0);
  my_echart_adapter_destroy(adapter);
  my_widget_unref(chart);
  my_echart_option_free(&option);
}

TEST(echart_adapter_destroy_keeps_caller_reference_and_renders) {
  const double values[] = {1.0, 2.5, 3.0};
  my_echart_option_t option = make_option(values, 3u, "render", NULL, MY_ECHART_LINE);
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter = my_echart_adapter_create(chart, NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 240u, 160u, MY_PIXEL_FORMAT_ARGB8888);
  my_vgcanvas_t* vg = my_vgcanvas_soft_create(NULL, lcd);
  FILE* artifact;
  /* Per-process OS-temp path: a bare "/tmp/..." resolves against the current
   * drive on Windows (CI's D:\a has no \tmp) and a fixed name races parallel
   * ctest trees (R444). */
  char artifact_path[128];
  ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_OK);
  chart->rect.w = 240; chart->rect.h = 160;
  my_widget_paint(chart, vg);
  ASSERT_TRUE(my_lcd_mem_get_buffer(lcd) != NULL);
  artifact = fopen(test_tmp(artifact_path, sizeof artifact_path,
                            "phase5_echart_adapter.ppm"), "wb");
  ASSERT_NOT_NULL(artifact);
  fprintf(artifact, "P6\n240 160\n255\n");
  for (size_t i = 0u; i < 240u * 160u; i++) {
    const uint8_t* pixel = my_lcd_mem_get_buffer(lcd) + i * 4u;
    fwrite(pixel + 1u, 1u, 3u, artifact);
  }
  fclose(artifact);
  my_echart_adapter_destroy(adapter);
  ASSERT_EQ(((my_chart_t*)chart)->series_count, 0u);
  my_widget_unref(chart);
  my_vgcanvas_destroy(vg);
  lcd->vtable->destroy(lcd);
  my_echart_option_free(&option);
}

TEST(echart_adapter_projects_all_native_series_types) {
  static const double pie_values[] = {25.0, 35.0, 40.0};
  static const double radar_values[] = {20.0, 40.0, 60.0, 80.0};
  static const double funnel_values[] = {100.0, 70.0, 40.0};
  static const double heatmap_values[] = {10.0, 50.0, 90.0};
  static const double boxplot_values[] = {10.0, 20.0, 30.0, 40.0, 50.0};
  struct {
    my_echart_series_type_t type;
    const double* values;
    size_t count;
    my_chart_mode_t expected;
  } cases[] = {
      {MY_ECHART_PIE, pie_values, 3u, MY_CHART_PIE},
      {MY_ECHART_RADAR, radar_values, 4u, MY_CHART_RADAR},
      {MY_ECHART_FUNNEL, funnel_values, 3u, MY_CHART_FUNNEL},
      {MY_ECHART_HEATMAP, heatmap_values, 3u, MY_CHART_HEATMAP},
      {MY_ECHART_BOXPLOT, boxplot_values, 5u, MY_CHART_BOXPLOT}};
  for (size_t i = 0u; i < sizeof(cases) / sizeof(cases[0]); i++) {
    my_echart_series_input_t series = {"s", "Series", cases[i].type,
                                       cases[i].values, cases[i].count,
                                       0u, 0u, NULL, true};
    my_echart_option_input_t input = {"all", NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u};
    my_echart_option_t option;
    my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
    my_echart_adapter_t* adapter;
    my_echart_option_init(&option, NULL);
    ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
    adapter = my_echart_adapter_create(chart, NULL);
    ASSERT_NOT_NULL(adapter);
    ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_OK);
    ASSERT_EQ(((my_chart_t*)chart)->mode, cases[i].expected);
    ASSERT_EQ(((my_chart_t*)chart)->series_count, 1u);
    my_echart_adapter_destroy(adapter);
    my_widget_unref(chart);
    my_echart_option_free(&option);
  }
}

TEST(echart_adapter_rejects_boxplot_without_five_samples) {
  static const double short_values[] = {1.0, 2.0};
  my_echart_series_input_t series = {"s", "Stats", MY_ECHART_BOXPLOT,
                                     short_values, 2u, 0u, 0u, NULL, true};
  my_echart_option_input_t input = {"box", NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u};
  my_echart_option_t option;
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter;
  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  adapter = my_echart_adapter_create(chart, NULL);
  ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_INVALID_PARAMS);
  my_echart_adapter_destroy(adapter);
  my_widget_unref(chart);
  my_echart_option_free(&option);
}

TEST(echart_adapter_projects_component_state) {
  static const double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  my_echart_series_input_t series = {"s", "Series", MY_ECHART_LINE, values,
                                     6u, 0u, 0u, NULL, true};
  my_echart_option_input_t input = {"comp", NULL, 0u, &series, 1u, false, false, 0.0, 0.0, false, 0u, 0u};
  my_echart_option_t option;
  my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
  my_echart_adapter_t* adapter;

  input.legend_hidden = true;
  input.range_set = true;
  input.y_min = -2.5;
  input.y_max = 7.5;
  input.zoom_set = true;
  input.zoom_start = 1u;
  input.zoom_end = 4u;

  my_echart_option_init(&option, NULL);
  ASSERT_EQ(my_echart_option_copy(&option, &input, NULL), MY_RET_OK);
  adapter = my_echart_adapter_create(chart, NULL);
  ASSERT_NOT_NULL(adapter);
  ASSERT_EQ(my_echart_adapter_apply(adapter, &option), MY_RET_OK);
  ASSERT_FALSE(((my_chart_t*)chart)->show_legend);
  ASSERT_TRUE(((my_chart_t*)chart)->range_set);
  ASSERT_FLOAT_EQ(((my_chart_t*)chart)->y_min, -2.5f, 1e-6f);
  ASSERT_FLOAT_EQ(((my_chart_t*)chart)->y_max, 7.5f, 1e-6f);
  ASSERT_TRUE(((my_chart_t*)chart)->zoom_set);
  ASSERT_EQ(((my_chart_t*)chart)->zoom_start, 1u);
  ASSERT_EQ(((my_chart_t*)chart)->zoom_end, 4u);
  my_echart_adapter_destroy(adapter);
  my_widget_unref(chart);
  my_echart_option_free(&option);
}

TEST_MAIN_BEGIN()
  RUN_TEST(echart_adapter_converts_and_retains_values);
  RUN_TEST(echart_adapter_rejects_without_mutating);
  RUN_TEST(echart_adapter_rejects_mixed_types_and_float_overflow);
  RUN_TEST(echart_adapter_oom_rolls_back);
  RUN_TEST(echart_adapter_destroy_keeps_caller_reference_and_renders);
  RUN_TEST(echart_adapter_projects_all_native_series_types);
  RUN_TEST(echart_adapter_rejects_boxplot_without_five_samples);
  RUN_TEST(echart_adapter_projects_component_state);
TEST_MAIN_END()
