#include "myui/echarts/my_echart.h"

#include <string.h>

struct my_echart_t {
  const my_allocator_t* allocator;
  my_echart_option_t current;
  my_echart_option_t pending;
  bool has_pending;
  unsigned revision;
};

my_echart_t* my_echart_create(const my_allocator_t* allocator) {
  my_echart_t* chart = (my_echart_t*)my_mem_calloc(allocator, 1u, sizeof(*chart));
  if (chart == NULL) return NULL;
  chart->allocator = allocator;
  my_echart_option_init(&chart->current, allocator);
  my_echart_option_init(&chart->pending, allocator);
  return chart;
}

void my_echart_destroy(my_echart_t* chart) {
  if (chart == NULL) return;
  my_echart_option_free(&chart->current);
  my_echart_option_free(&chart->pending);
  my_mem_free(chart->allocator, chart);
}

static bool same_id(const char* a, const char* b) {
  return a != NULL && b != NULL && strcmp(a, b) == 0;
}

my_ret_t my_echart_set_option(my_echart_t* chart,
                              const my_echart_option_input_t* input,
                              bool not_merge, bool lazy_update) {
  my_echart_option_t candidate;
  if (chart == NULL || input == NULL) return MY_RET_INVALID_PARAMS;
  my_echart_option_init(&candidate, chart->allocator);
  if (not_merge || chart->current.series_count == 0u) {
    if (my_echart_option_copy(&candidate, input, chart->allocator) != MY_RET_OK)
      return MY_RET_INVALID_PARAMS;
  } else {
    my_echart_option_input_t base = {
        input->title != NULL ? input->title : chart->current.title,
        (const char* const*)chart->current.x_axis_data,
        chart->current.x_axis_count, NULL, 0u,
        input->legend_hidden, input->tooltip_hidden,
        input->range_set ? true : chart->current.range_set,
        input->range_set ? input->y_min : chart->current.y_min,
        input->range_set ? input->y_max : chart->current.y_max,
        input->zoom_set ? true : chart->current.zoom_set,
        input->zoom_set ? input->zoom_start : chart->current.zoom_start,
        input->zoom_set ? input->zoom_end : chart->current.zoom_end,
        input->visual_map_set ? true : chart->current.visual_map_set,
        input->visual_map_set ? input->visual_map_min
                              : chart->current.visual_map_min,
        input->visual_map_set ? input->visual_map_max
                              : chart->current.visual_map_max,
        input->visual_map_set ? input->visual_map_low_color
                              : chart->current.visual_map_low_color,
        input->visual_map_set ? input->visual_map_high_color
                              : chart->current.visual_map_high_color,
                                      NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u,
                                      MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
    my_echart_series_input_t* series = (my_echart_series_input_t*)
        my_mem_calloc(chart->allocator, chart->current.series_count,
                      sizeof(*series));
    my_echart_mark_point_input_t* points = chart->current.mark_point_count > 0u
        ? (my_echart_mark_point_input_t*)my_mem_calloc(
              chart->allocator, chart->current.mark_point_count, sizeof(*points))
        : NULL;
    my_echart_mark_line_input_t* lines = chart->current.mark_line_count > 0u
        ? (my_echart_mark_line_input_t*)my_mem_calloc(
              chart->allocator, chart->current.mark_line_count, sizeof(*lines))
        : NULL;
    my_echart_mark_area_input_t* areas = chart->current.mark_area_count > 0u
        ? (my_echart_mark_area_input_t*)my_mem_calloc(
              chart->allocator, chart->current.mark_area_count, sizeof(*areas))
        : NULL;
    if (series == NULL ||
        (chart->current.mark_point_count > 0u && points == NULL) ||
        (chart->current.mark_line_count > 0u && lines == NULL) ||
        (chart->current.mark_area_count > 0u && areas == NULL)) {
      my_mem_free(chart->allocator, series);
      my_mem_free(chart->allocator, points);
      my_mem_free(chart->allocator, lines);
      my_mem_free(chart->allocator, areas);
      return MY_RET_OOM;
    }
    base.series_count = chart->current.series_count;
    for (size_t i = 0u; i < base.series_count; i++) {
      const my_echart_series_t* s = &chart->current.series[i];
      series[i] = (my_echart_series_input_t){s->id, s->name, s->type, s->data,
                                             s->data_count, s->color,
                                             s->y_axis_index, s->stack, s->show,
                                             NULL};
    }
    for (size_t i = 0u; i < chart->current.mark_point_count; i++)
      points[i] = (my_echart_mark_point_input_t){
          chart->current.mark_points[i].series_index,
          chart->current.mark_points[i].category_index,
          chart->current.mark_points[i].label};
    for (size_t i = 0u; i < chart->current.mark_line_count; i++)
      lines[i] = (my_echart_mark_line_input_t){
          chart->current.mark_lines[i].value,
          chart->current.mark_lines[i].label,
          chart->current.mark_lines[i].color};
    for (size_t i = 0u; i < chart->current.mark_area_count; i++)
      areas[i] = (my_echart_mark_area_input_t){
          chart->current.mark_areas[i].y_min,
          chart->current.mark_areas[i].y_max,
          chart->current.mark_areas[i].label,
          chart->current.mark_areas[i].color};
    base.series = series;
    base.mark_points = points;
    base.mark_point_count = chart->current.mark_point_count;
    base.mark_lines = lines;
    base.mark_line_count = chart->current.mark_line_count;
    base.mark_areas = areas;
    base.mark_area_count = chart->current.mark_area_count;
    my_ret_t result = my_echart_option_copy(&candidate, &base, chart->allocator);
    my_mem_free(chart->allocator, series);
    my_mem_free(chart->allocator, points);
    my_mem_free(chart->allocator, lines);
    my_mem_free(chart->allocator, areas);
    if (result != MY_RET_OK) { my_echart_option_free(&candidate); return result; }
    for (size_t i = 0u; i < input->series_count; i++) {
      const my_echart_series_input_t* incoming = &input->series[i];
      size_t found = candidate.series_count;
      for (size_t j = 0u; j < candidate.series_count; j++)
        if (same_id(candidate.series[j].id, incoming->id)) { found = j; break; }
      if (found == candidate.series_count) {
        my_echart_series_t* grown;
        if (candidate.series_count >= MY_ECHART_MAX_SERIES) {
          my_echart_option_free(&candidate);
          return MY_RET_INVALID_PARAMS;
        }
        grown = (my_echart_series_t*)my_mem_realloc(
            chart->allocator, candidate.series,
            (candidate.series_count + 1u) * sizeof(*grown));
        if (grown == NULL) { my_echart_option_free(&candidate); return MY_RET_OOM; }
        memset(&grown[candidate.series_count], 0, sizeof(*grown));
        candidate.series = grown;
        found = candidate.series_count;
        candidate.series_count++;
      }
      my_echart_series_t replacement = {0};
      my_echart_option_input_t one = {NULL, NULL, 0u, incoming, 1u,
                                      input->legend_hidden, input->tooltip_hidden,
                                      input->range_set,
                                      input->y_min, input->y_max,
                                      input->zoom_set, input->zoom_start,
                                      input->zoom_end, input->visual_map_set,
                                      input->visual_map_min,
                                      input->visual_map_max,
                                      input->visual_map_low_color,
                                      input->visual_map_high_color,
        NULL, 0u, NULL, 0u, NULL, 0u, NULL, 0u,
        MY_ECHART_TRANSFORM_NONE, NULL, MY_ECHART_FILTER_EQ, NULL, 0.0, NULL, 0u};
      my_echart_option_t temp;
      my_echart_option_init(&temp, chart->allocator);
      if (my_echart_option_copy(&temp, &one, chart->allocator) != MY_RET_OK) {
        my_echart_option_free(&candidate); return MY_RET_OOM;
      }
      replacement = temp.series[0];
      temp.series[0].id = NULL; temp.series[0].name = NULL;
      temp.series[0].stack = NULL; temp.series[0].data = NULL;
      my_echart_option_free(&temp);
      my_mem_free(candidate.allocator, candidate.series[found].id);
      my_mem_free(candidate.allocator, candidate.series[found].name);
      my_mem_free(candidate.allocator, candidate.series[found].stack);
      my_mem_free(candidate.allocator, candidate.series[found].data);
      candidate.series[found] = replacement;
    }
  }
  if (lazy_update) {
    my_echart_option_free(&chart->pending);
    chart->pending = candidate;
    chart->has_pending = true;
  } else {
    my_echart_option_free(&chart->current);
    chart->current = candidate;
    chart->has_pending = false;
    chart->revision++;
  }
  return MY_RET_OK;
}

my_ret_t my_echart_flush(my_echart_t* chart) {
  if (chart == NULL) return MY_RET_INVALID_PARAMS;
  if (!chart->has_pending) return MY_RET_OK;
  my_echart_option_free(&chart->current);
  chart->current = chart->pending;
  my_echart_option_init(&chart->pending, chart->allocator);
  chart->has_pending = false;
  chart->revision++;
  return MY_RET_OK;
}

const my_echart_option_t* my_echart_get_option(const my_echart_t* chart) {
  return chart != NULL ? &chart->current : NULL;
}

unsigned my_echart_revision(const my_echart_t* chart) {
  return chart != NULL ? chart->revision : 0u;
}

my_ret_t my_echart_remove_series(my_echart_t* chart, const char* series_id) {
  my_echart_option_t* option;
  size_t found;
  if (chart == NULL || series_id == NULL || series_id[0] == '\0')
    return MY_RET_INVALID_PARAMS;
  option = &chart->current;
  found = option->series_count;
  for (size_t i = 0u; i < option->series_count; i++)
    if (strcmp(option->series[i].id, series_id) == 0) { found = i; break; }
  if (found == option->series_count) return MY_RET_NOT_FOUND;
  {
    my_echart_series_t* victim = &option->series[found];
    my_mem_free(option->allocator, victim->id);
    my_mem_free(option->allocator, victim->name);
    my_mem_free(option->allocator, victim->stack);
    my_mem_free(option->allocator, victim->data);
    memmove(&option->series[found], &option->series[found + 1u],
            (option->series_count - found - 1u) * sizeof(*option->series));
  }
  option->series_count--;
  chart->revision++;
  return MY_RET_OK;
}

my_ret_t my_echart_model_dispatch_action(my_echart_t* chart,
                                         const my_echart_model_action_t* action) {
  my_echart_option_t* option;
  if (chart == NULL || action == NULL || action->series_id == NULL)
    return MY_RET_INVALID_PARAMS;
  option = &chart->current;
  for (size_t i = 0u; i < option->series_count; i++) {
    my_echart_series_t* series = &option->series[i];
    if (strcmp(series->id, action->series_id) != 0) continue;
    if (action->type == MY_ECHART_MODEL_ACTION_LEGEND_SELECT) series->show = true;
    else if (action->type == MY_ECHART_MODEL_ACTION_LEGEND_UNSELECT) series->show = false;
    else if (action->type == MY_ECHART_MODEL_ACTION_LEGEND_TOGGLE_SELECT) series->show = !series->show;
    else return MY_RET_NOT_SUPPORTED;
    chart->revision++;
    return MY_RET_OK;
  }
  return MY_RET_NOT_FOUND;
}
