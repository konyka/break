#include "myui/echarts/my_echart_adapter.h"
#include "myui/widgets/my_chart.h"

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

typedef struct my_echart_adapter_payload_t {
  my_echart_option_t option;
  float* values[MY_CHART_MAX_SERIES];
} my_echart_adapter_payload_t;

struct my_echart_adapter_t {
  my_widget_t* chart;
  const my_allocator_t* allocator;
  my_echart_adapter_payload_t* payload;
};

static my_chart_mode_t mode_for(my_echart_series_type_t type) {
  switch (type) {
    case MY_ECHART_LINE: return MY_CHART_LINE;
    case MY_ECHART_BAR: return MY_CHART_BAR;
    case MY_ECHART_SCATTER: return MY_CHART_SCATTER;
    case MY_ECHART_PIE: return MY_CHART_PIE;
    case MY_ECHART_RADAR: return MY_CHART_RADAR;
    case MY_ECHART_FUNNEL: return MY_CHART_FUNNEL;
    case MY_ECHART_HEATMAP: return MY_CHART_HEATMAP;
    case MY_ECHART_BOXPLOT: return MY_CHART_BOXPLOT;
    default: return (my_chart_mode_t)-1;
  }
}

static void payload_free(my_echart_adapter_t* adapter,
                         my_echart_adapter_payload_t* payload) {
  if (payload == NULL) return;
  for (size_t i = 0u; i < MY_CHART_MAX_SERIES; i++)
    my_mem_free(adapter->allocator, payload->values[i]);
  my_echart_option_free(&payload->option);
  my_mem_free(adapter->allocator, payload);
}

static my_ret_t validate_option(const my_echart_option_t* option,
                                my_chart_mode_t* mode, bool* stacked) {
  const char* stack = NULL;
  if (option == NULL || mode == NULL || stacked == NULL ||
      option->series_count == 0u || option->series_count > MY_CHART_MAX_SERIES ||
      option->title == NULL || strlen(option->title) >= sizeof(((my_chart_t*)0)->title) ||
      (option->x_axis_count > 0u && option->x_axis_data == NULL) ||
      option->x_axis_count > UINT32_MAX || option->series == NULL)
    return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < option->x_axis_count; i++) {
    if (option->x_axis_data[i] == NULL || option->x_axis_data[i][0] == '\0')
      return MY_RET_INVALID_PARAMS;
  }
  *mode = mode_for(option->series[0].type);
  if ((int)*mode < 0) return MY_RET_NOT_SUPPORTED;
  for (size_t i = 0u; i < option->series_count; i++) {
    const my_echart_series_t* series = &option->series[i];
    if (mode_for(series->type) != *mode || series->name == NULL ||
        series->name[0] == '\0' || series->data_count > UINT32_MAX ||
        (series->data_count > 0u && series->data == NULL) ||
        series->y_axis_index > 1u)
      return mode_for(series->type) != *mode ? MY_RET_NOT_SUPPORTED
                                             : MY_RET_INVALID_PARAMS;
    if (series->stack != NULL && series->stack[0] == '\0')
      return MY_RET_INVALID_PARAMS;
    /* Boxplot series render min/Q1/median/Q3/max; fewer samples are invalid. */
    if (series->type == MY_ECHART_BOXPLOT && series->data_count < 5u)
      return MY_RET_INVALID_PARAMS;
    if (i == 0u) stack = series->stack;
    else if ((stack == NULL) != (series->stack == NULL) ||
             (stack != NULL && strcmp(stack, series->stack) != 0))
      return MY_RET_NOT_SUPPORTED;
    for (size_t j = 0u; j < series->data_count; j++)
      if (!isfinite(series->data[j]) || series->data[j] < -FLT_MAX ||
          series->data[j] > FLT_MAX)
        return MY_RET_INVALID_PARAMS;
  }
  if (stack != NULL && *mode != MY_CHART_BAR) return MY_RET_NOT_SUPPORTED;
  *stacked = stack != NULL;
  return MY_RET_OK;
}

static my_ret_t stage_payload(my_echart_adapter_t* adapter,
                              const my_echart_option_t* source,
                              my_echart_adapter_payload_t** result) {
  my_echart_adapter_payload_t* candidate;
  my_chart_mode_t mode;
  bool stacked;
  size_t title_length;
  my_ret_t ret = validate_option(source, &mode, &stacked);
  if (ret != MY_RET_OK) return ret;
  candidate = (my_echart_adapter_payload_t*)my_mem_calloc(
      adapter->allocator, 1u, sizeof(*candidate));
  if (candidate == NULL) return MY_RET_OOM;
  my_echart_option_init(&candidate->option, adapter->allocator);
  title_length = strlen(source->title);
  candidate->option.title = (char*)my_mem_alloc(adapter->allocator, title_length + 1u);
  if (candidate->option.title == NULL) ret = MY_RET_OOM;
  else {
    memcpy(candidate->option.title, source->title, title_length + 1u);
    candidate->option.x_axis_count = source->x_axis_count;
    candidate->option.series_count = source->series_count;
    if (source->x_axis_count > 0u) {
      candidate->option.x_axis_data = (char**)my_mem_calloc(
          adapter->allocator, source->x_axis_count, sizeof(char*));
      if (candidate->option.x_axis_data == NULL) ret = MY_RET_OOM;
    }
    candidate->option.series = (my_echart_series_t*)my_mem_calloc(
        adapter->allocator, source->series_count, sizeof(*candidate->option.series));
    if (candidate->option.series == NULL) ret = MY_RET_OOM;
  }
  for (size_t i = 0u; ret == MY_RET_OK && i < source->x_axis_count; i++) {
    size_t length = strlen(source->x_axis_data[i]);
    candidate->option.x_axis_data[i] = (char*)my_mem_alloc(adapter->allocator, length + 1u);
    if (candidate->option.x_axis_data[i] == NULL) { ret = MY_RET_OOM; break; }
    memcpy(candidate->option.x_axis_data[i], source->x_axis_data[i], length + 1u);
  }
  for (size_t i = 0u; ret == MY_RET_OK && i < source->series_count; i++) {
    const my_echart_series_t* src = &source->series[i];
    my_echart_series_t* dst = &candidate->option.series[i];
    size_t length = strlen(src->name);
    dst->name = (char*)my_mem_alloc(adapter->allocator, length + 1u);
    if (dst->name == NULL) { ret = MY_RET_OOM; break; }
    memcpy(dst->name, src->name, length + 1u);
    if (src->id != NULL) {
      length = strlen(src->id);
      dst->id = (char*)my_mem_alloc(adapter->allocator, length + 1u);
      if (dst->id == NULL) { ret = MY_RET_OOM; break; }
      memcpy(dst->id, src->id, length + 1u);
    }
    if (src->stack != NULL) {
      length = strlen(src->stack);
      dst->stack = (char*)my_mem_alloc(adapter->allocator, length + 1u);
      if (dst->stack == NULL) { ret = MY_RET_OOM; break; }
      memcpy(dst->stack, src->stack, length + 1u);
    }
    dst->type = src->type;
    dst->data_count = src->data_count;
    dst->color = src->color;
    dst->y_axis_index = src->y_axis_index;
    dst->show = src->show;
    if (src->data_count > 0u) {
      candidate->values[i] = (float*)my_mem_alloc(
          adapter->allocator, src->data_count * sizeof(float));
      if (candidate->values[i] == NULL) { ret = MY_RET_OOM; break; }
      dst->data = (double*)my_mem_alloc(adapter->allocator,
                                        src->data_count * sizeof(double));
      if (dst->data == NULL) { ret = MY_RET_OOM; break; }
      for (size_t j = 0u; j < src->data_count; j++) {
        dst->data[j] = src->data[j];
        candidate->values[i][j] = (float)src->data[j];
      }
    }
  }
  if (ret != MY_RET_OK) { payload_free(adapter, candidate); return ret; }
  candidate->option.legend_hidden = source->legend_hidden;
  candidate->option.range_set = source->range_set;
  candidate->option.y_min = source->y_min;
  candidate->option.y_max = source->y_max;
  candidate->option.zoom_set = source->zoom_set;
  candidate->option.zoom_start = source->zoom_start;
  candidate->option.zoom_end = source->zoom_end;
  candidate->option.visual_map_set = source->visual_map_set;
  candidate->option.visual_map_min = source->visual_map_min;
  candidate->option.visual_map_max = source->visual_map_max;
  candidate->option.visual_map_low_color = source->visual_map_low_color;
  candidate->option.visual_map_high_color = source->visual_map_high_color;
  (void)mode;
  (void)stacked;
  *result = candidate;
  return MY_RET_OK;
}

my_echart_adapter_t* my_echart_adapter_create(my_widget_t* chart,
                                               const my_allocator_t* allocator) {
  my_echart_adapter_t* adapter;
  if (!my_chart_is_instance(chart)) return NULL;
  adapter = (my_echart_adapter_t*)my_mem_calloc(allocator, 1u, sizeof(*adapter));
  if (adapter == NULL) return NULL;
  adapter->chart = my_widget_ref(chart);
  adapter->allocator = allocator;
  return adapter;
}

void my_echart_adapter_destroy(my_echart_adapter_t* adapter) {
  if (adapter == NULL) return;
  if (adapter->payload != NULL) {
    my_chart_set_labels(adapter->chart, NULL, 0u);
    my_chart_clear_series(adapter->chart);
    payload_free(adapter, adapter->payload);
  }
  my_widget_unref(adapter->chart);
  my_mem_free(adapter->allocator, adapter);
}

my_ret_t my_echart_adapter_apply(my_echart_adapter_t* adapter,
                                 const my_echart_option_t* option) {
  my_echart_adapter_payload_t* candidate = NULL;
  my_echart_adapter_payload_t* old;
  my_chart_mode_t mode;
  bool stacked;
  my_ret_t ret;
  if (adapter == NULL || option == NULL || adapter->chart == NULL)
    return MY_RET_INVALID_PARAMS;
  ret = validate_option(option, &mode, &stacked);
  if (ret != MY_RET_OK) return ret;
  ret = stage_payload(adapter, option, &candidate);
  if (ret != MY_RET_OK) return ret;
  /* All allocations/conversions are complete; commit is one native state swap. */
  my_chart_series_t native_series[MY_CHART_MAX_SERIES] = {0};
  bool visible[MY_CHART_MAX_SERIES] = {false};
  for (size_t i = 0u; i < candidate->option.series_count; i++) {
    const my_echart_series_t* series = &candidate->option.series[i];
    native_series[i] = (my_chart_series_t){series->name, candidate->values[i],
                                           series->data_count, series->color,
                                           (unsigned char)series->y_axis_index};
    visible[i] = series->show;
  }
  {
    my_chart_snapshot_t snapshot = {
        mode, candidate->option.title,
        (const char* const*)candidate->option.x_axis_data,
        candidate->option.x_axis_count, native_series, visible,
        candidate->option.series_count, stacked,
        !candidate->option.legend_hidden,
        candidate->option.range_set, (float)candidate->option.y_min,
        (float)candidate->option.y_max,
        candidate->option.zoom_set, candidate->option.zoom_start,
        candidate->option.zoom_end,
        candidate->option.visual_map_set, (float)candidate->option.visual_map_min,
        (float)candidate->option.visual_map_max,
        candidate->option.visual_map_low_color,
        candidate->option.visual_map_high_color};
    ret = my_chart_apply_snapshot(adapter->chart, &snapshot);
    if (ret != MY_RET_OK) { payload_free(adapter, candidate); return ret; }
  }
  old = adapter->payload;
  adapter->payload = candidate;
  if (old != NULL) payload_free(adapter, old);
  return MY_RET_OK;
}
