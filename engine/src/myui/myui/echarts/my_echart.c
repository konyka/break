#include "myui/echarts/my_echart.h"

#include <string.h>

struct my_echart_t {
  const my_allocator_t* allocator;
  my_echart_option_t current;
  my_echart_option_t pending;
  bool has_pending;
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
        chart->current.title, (const char* const*)chart->current.x_axis_data,
        chart->current.x_axis_count, NULL, 0u};
    my_echart_series_input_t* series = (my_echart_series_input_t*)
        my_mem_calloc(chart->allocator, chart->current.series_count,
                      sizeof(*series));
    if (series == NULL) return MY_RET_OOM;
    base.series_count = chart->current.series_count;
    for (size_t i = 0u; i < base.series_count; i++) {
      const my_echart_series_t* s = &chart->current.series[i];
      series[i] = (my_echart_series_input_t){s->id, s->name, s->type, s->data,
                                             s->data_count, s->color,
                                             s->y_axis_index, s->stack, s->show};
    }
    base.series = series;
    my_ret_t result = my_echart_option_copy(&candidate, &base, chart->allocator);
    my_mem_free(chart->allocator, series);
    if (result != MY_RET_OK) { my_echart_option_free(&candidate); return result; }
    for (size_t i = 0u; i < input->series_count; i++) {
      const my_echart_series_input_t* incoming = &input->series[i];
      size_t found = candidate.series_count;
      for (size_t j = 0u; j < candidate.series_count; j++)
        if (same_id(candidate.series[j].id, incoming->id)) { found = j; break; }
      if (found == candidate.series_count) { my_echart_option_free(&candidate); return MY_RET_INVALID_PARAMS; }
      my_echart_series_t replacement = {0};
      my_echart_option_input_t one = {NULL, NULL, 0u, incoming, 1u};
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
  return MY_RET_OK;
}

const my_echart_option_t* my_echart_get_option(const my_echart_t* chart) {
  return chart != NULL ? &chart->current : NULL;
}
