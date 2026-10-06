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
  unsigned last_synced_revision;
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
  my_echart_series_input_t* series_inputs = NULL;
  my_echart_mark_point_input_t* point_inputs = NULL;
  my_echart_mark_line_input_t* line_inputs = NULL;
  my_echart_mark_area_input_t* area_inputs = NULL;
  my_echart_option_input_t input;
  my_ret_t ret;
  candidate = (my_echart_adapter_payload_t*)my_mem_calloc(
      adapter->allocator, 1u, sizeof(*candidate));
  if (candidate == NULL) return MY_RET_OOM;
  my_echart_option_init(&candidate->option, adapter->allocator);

  series_inputs = (my_echart_series_input_t*)my_mem_calloc(
      adapter->allocator, source->series_count ? source->series_count : 1u,
      sizeof(*series_inputs));
  point_inputs = (my_echart_mark_point_input_t*)my_mem_calloc(
      adapter->allocator,
      source->mark_point_count ? source->mark_point_count : 1u,
      sizeof(*point_inputs));
  line_inputs = (my_echart_mark_line_input_t*)my_mem_calloc(
      adapter->allocator,
      source->mark_line_count ? source->mark_line_count : 1u,
      sizeof(*line_inputs));
  area_inputs = (my_echart_mark_area_input_t*)my_mem_calloc(
      adapter->allocator,
      source->mark_area_count ? source->mark_area_count : 1u,
      sizeof(*area_inputs));
  if (series_inputs == NULL || point_inputs == NULL || line_inputs == NULL ||
      area_inputs == NULL) {
    ret = MY_RET_OOM;
    goto done;
  }
  for (size_t i = 0u; i < source->series_count; i++) {
    const my_echart_series_t* s = &source->series[i];
    series_inputs[i] = (my_echart_series_input_t){
        s->id, s->name, s->type, s->data, s->data_count, s->color,
        s->y_axis_index, s->stack, s->show};
  }
  for (size_t i = 0u; i < source->mark_point_count; i++)
    point_inputs[i] = (my_echart_mark_point_input_t){
        source->mark_points[i].series_index,
        source->mark_points[i].category_index, source->mark_points[i].label};
  for (size_t i = 0u; i < source->mark_line_count; i++)
    line_inputs[i] = (my_echart_mark_line_input_t){
        source->mark_lines[i].value, source->mark_lines[i].label,
        source->mark_lines[i].color};
  for (size_t i = 0u; i < source->mark_area_count; i++)
    area_inputs[i] = (my_echart_mark_area_input_t){
        source->mark_areas[i].y_min, source->mark_areas[i].y_max,
        source->mark_areas[i].label, source->mark_areas[i].color};

  input = (my_echart_option_input_t){
      source->title, (const char* const*)source->x_axis_data,
      source->x_axis_count, series_inputs, source->series_count,
      source->legend_hidden, source->tooltip_hidden, source->range_set,
      source->y_min, source->y_max,
      source->zoom_set, source->zoom_start, source->zoom_end,
      source->visual_map_set, source->visual_map_min, source->visual_map_max,
      source->visual_map_low_color, source->visual_map_high_color,
      point_inputs, source->mark_point_count, line_inputs,
      source->mark_line_count, area_inputs, source->mark_area_count};
  ret = my_echart_option_copy(&candidate->option, &input, adapter->allocator);
  if (ret == MY_RET_OK) {
    for (size_t i = 0u; i < candidate->option.series_count; i++) {
      const my_echart_series_t* s = &candidate->option.series[i];
      if (s->data_count == 0u) continue;
      candidate->values[i] = (float*)my_mem_alloc(
          adapter->allocator, s->data_count * sizeof(float));
      if (candidate->values[i] == NULL) { ret = MY_RET_OOM; break; }
      for (size_t j = 0u; j < s->data_count; j++)
        candidate->values[i][j] = (float)s->data[j];
    }
  }
done:
  my_mem_free(adapter->allocator, series_inputs);
  my_mem_free(adapter->allocator, point_inputs);
  my_mem_free(adapter->allocator, line_inputs);
  my_mem_free(adapter->allocator, area_inputs);
  if (ret != MY_RET_OK) { payload_free(adapter, candidate); return ret; }
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
    my_chart_clear_mark_points(adapter->chart);
    my_chart_clear_mark_lines(adapter->chart);
    my_chart_clear_mark_areas(adapter->chart);
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
    my_chart_mark_point_t marks[MY_ECHART_MAX_MARK_POINTS] = {{0}};
    my_chart_mark_line_state_t lines[MY_ECHART_MAX_MARK_LINES] = {{0}};
    my_chart_mark_area_state_t areas[MY_ECHART_MAX_MARK_AREAS] = {{0}};
    for (size_t i = 0u; i < candidate->option.mark_point_count; i++)
      marks[i] = (my_chart_mark_point_t){
          candidate->option.mark_points[i].series_index,
          candidate->option.mark_points[i].category_index,
          candidate->option.mark_points[i].label};
    for (size_t i = 0u; i < candidate->option.mark_line_count; i++)
      lines[i] = (my_chart_mark_line_state_t){
          (float)candidate->option.mark_lines[i].value,
          candidate->option.mark_lines[i].label,
          candidate->option.mark_lines[i].color};
    for (size_t i = 0u; i < candidate->option.mark_area_count; i++)
      areas[i] = (my_chart_mark_area_state_t){
          (float)candidate->option.mark_areas[i].y_min,
          (float)candidate->option.mark_areas[i].y_max,
          candidate->option.mark_areas[i].label,
          candidate->option.mark_areas[i].color};
    {
    my_chart_snapshot_t snapshot = {
        mode, candidate->option.title,
        (const char* const*)candidate->option.x_axis_data,
        candidate->option.x_axis_count, native_series, visible,
        candidate->option.series_count, stacked,
        !candidate->option.legend_hidden, !candidate->option.tooltip_hidden,
        candidate->option.range_set, (float)candidate->option.y_min,
        (float)candidate->option.y_max,
        candidate->option.zoom_set, candidate->option.zoom_start,
        candidate->option.zoom_end,
        candidate->option.visual_map_set, (float)candidate->option.visual_map_min,
        (float)candidate->option.visual_map_max,
        candidate->option.visual_map_low_color,
        candidate->option.visual_map_high_color,
        marks, candidate->option.mark_point_count, lines,
        candidate->option.mark_line_count, areas,
        candidate->option.mark_area_count};
    ret = my_chart_apply_snapshot(adapter->chart, &snapshot);
    if (ret != MY_RET_OK) { payload_free(adapter, candidate); return ret; }
    }
  }
  old = adapter->payload;
  adapter->payload = candidate;
  if (old != NULL) payload_free(adapter, old);
  return MY_RET_OK;
}

my_ret_t my_echart_adapter_sync_model(my_echart_adapter_t* adapter,
                                      my_echart_t* model) {
  my_ret_t ret;
  if (adapter == NULL || model == NULL) return MY_RET_INVALID_PARAMS;
  if (my_echart_revision(model) == adapter->last_synced_revision) return MY_RET_OK;
  ret = my_echart_adapter_apply(adapter, my_echart_get_option(model));
  if (ret != MY_RET_OK) return ret;
  adapter->last_synced_revision = my_echart_revision(model);
  return MY_RET_OK;
}

static my_echart_event_type_t bridge_event_type(const my_event_t* event) {
  if (event->type == MY_EVENT_POINTER_DOWN) return MY_ECHART_EVENT_POINTER_DOWN;
  if (event->type == MY_EVENT_POINTER_MOVE) return MY_ECHART_EVENT_POINTER_MOVE;
  if (event->type == MY_EVENT_POINTER_UP) return MY_ECHART_EVENT_POINTER_UP;
  if (event->type == MY_EVENT_POINTER_WHEEL) return MY_ECHART_EVENT_WHEEL;
  if (event->type == MY_EVENT_KEY_DOWN && event->u.key.key == MY_KEY_LEFT)
    return MY_ECHART_EVENT_KEY_LEFT;
  if (event->type == MY_EVENT_KEY_DOWN && event->u.key.key == MY_KEY_RIGHT)
    return MY_ECHART_EVENT_KEY_RIGHT;
  return MY_ECHART_EVENT_ANY;
}

my_ret_t my_echart_adapter_event(my_echart_adapter_t* adapter,
                                 const my_event_t* native,
                                 my_echart_event_t* out) {
  my_echart_event_type_t type;
  if (adapter == NULL || native == NULL || out == NULL)
    return MY_RET_INVALID_PARAMS;
  type = bridge_event_type(native);
  if (type == MY_ECHART_EVENT_ANY) return MY_RET_NOT_FOUND;
  out->type = type;
  out->time_ms = native->time_ms;
  out->x = 0;
  out->y = 0;
  out->delta = 0;
  out->button = 0u;
  out->series_index = MY_ECHART_INDEX_NONE;
  out->data_index = MY_ECHART_INDEX_NONE;
  out->category_index = MY_ECHART_INDEX_NONE;
  if (native->type == MY_EVENT_KEY_DOWN) {
    out->modifiers = native->u.key.modifiers;
    return MY_RET_OK;
  }
  out->x = native->u.pointer.x;
  out->y = native->u.pointer.y;
  out->delta = native->u.pointer.delta;
  out->button = native->u.pointer.button;
  out->modifiers = native->u.pointer.modifiers;
  if (adapter->chart != NULL && my_chart_is_instance(adapter->chart)) {
    int32_t local_x = native->u.pointer.x;
    int32_t local_y = native->u.pointer.y;
    size_t category;
    my_widget_global_to_local(adapter->chart, &local_x, &local_y);
    category = my_chart_hit_test(adapter->chart, local_x, local_y);
    if (category != MY_ECHART_INDEX_NONE) {
      const my_chart_t* chart = (const my_chart_t*)adapter->chart;
      out->category_index = category;
      out->data_index = category;
      for (size_t i = 0u; i < chart->series_count; i++) {
        if (chart->series_visible[i] && chart->series[i].values != NULL &&
            category < chart->series[i].count) {
          out->series_index = i;
          break;
        }
      }
    }
  }
  return MY_RET_OK;
}
