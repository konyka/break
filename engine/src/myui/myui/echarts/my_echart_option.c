#include "myui/echarts/my_echart_option.h"

#include <math.h>
#include <string.h>

static bool valid_string(const char* value) { return value != NULL && value[0] != '\0'; }

static char* copy_string(const my_allocator_t* allocator, const char* value) {
  size_t length;
  char* result;
  if (value == NULL) return NULL;
  length = strlen(value);
  result = (char*)my_mem_alloc(allocator, length + 1u);
  if (result == NULL) return NULL;
  memcpy(result, value, length + 1u);
  return result;
}

void my_echart_option_init(my_echart_option_t* option,
                           const my_allocator_t* allocator) {
  if (option == NULL) return;
  memset(option, 0, sizeof(*option));
  option->allocator = allocator;
}

void my_echart_option_free(my_echart_option_t* option) {
  if (option == NULL) return;
  if (option->series != NULL) {
    for (size_t i = 0u; i < option->series_count; i++) {
      my_mem_free(option->allocator, option->series[i].id);
      my_mem_free(option->allocator, option->series[i].name);
      my_mem_free(option->allocator, option->series[i].stack);
      my_mem_free(option->allocator, option->series[i].data);
    }
  }
  if (option->x_axis_data != NULL) {
    for (size_t i = 0u; i < option->x_axis_count; i++)
      my_mem_free(option->allocator, option->x_axis_data[i]);
  }
  my_mem_free(option->allocator, option->series);
  my_mem_free(option->allocator, option->x_axis_data);
  my_mem_free(option->allocator, option->title);
  memset(option, 0, sizeof(*option));
}

my_ret_t my_echart_option_validate(const my_echart_option_input_t* input) {
  if (input == NULL || input->series_count > MY_ECHART_MAX_SERIES ||
      (input->series_count > 0u && input->series == NULL) ||
      (input->x_axis_count > 0u && input->x_axis_data == NULL))
    return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < input->x_axis_count; i++)
    if (!valid_string(input->x_axis_data[i])) return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < input->series_count; i++) {
    const my_echart_series_input_t* series = &input->series[i];
    if (!valid_string(series->id) || !valid_string(series->name) ||
        series->type < MY_ECHART_LINE || series->type > MY_ECHART_BOXPLOT ||
        (series->data_count > 0u && series->data == NULL) ||
        series->y_axis_index > 1u)
      return MY_RET_INVALID_PARAMS;
    for (size_t j = 0u; j < series->data_count; j++)
      if (!isfinite(series->data[j])) return MY_RET_INVALID_PARAMS;
    for (size_t j = 0u; j < i; j++)
      if (strcmp(series->id, input->series[j].id) == 0) return MY_RET_INVALID_PARAMS;
  }
  if (input->range_set &&
      (!isfinite(input->y_min) || !isfinite(input->y_max) ||
       input->y_max <= input->y_min))
    return MY_RET_INVALID_PARAMS;
  if (input->zoom_set && input->zoom_end <= input->zoom_start)
    return MY_RET_INVALID_PARAMS;
  if (input->visual_map_set &&
      (!isfinite(input->visual_map_min) || !isfinite(input->visual_map_max) ||
       input->visual_map_max <= input->visual_map_min))
    return MY_RET_INVALID_PARAMS;
  return MY_RET_OK;
}

my_ret_t my_echart_option_copy(my_echart_option_t* dst,
                               const my_echart_option_input_t* src,
                               const my_allocator_t* allocator) {
  my_echart_option_t candidate;
  if (my_echart_option_validate(src) != MY_RET_OK || dst == NULL)
    return MY_RET_INVALID_PARAMS;
  my_echart_option_init(&candidate, allocator);
  candidate.title = copy_string(allocator, src->title != NULL ? src->title : "");
  if (candidate.title == NULL) goto oom;
  candidate.x_axis_count = src->x_axis_count;
  if (candidate.x_axis_count > 0u) {
    candidate.x_axis_data = (char**)my_mem_calloc(allocator, candidate.x_axis_count,
                                                   sizeof(char*));
    if (candidate.x_axis_data == NULL) goto oom;
    for (size_t i = 0u; i < candidate.x_axis_count; i++) {
      candidate.x_axis_data[i] = copy_string(allocator, src->x_axis_data[i]);
      if (candidate.x_axis_data[i] == NULL) goto oom;
    }
  }
  candidate.series_count = src->series_count;
  if (candidate.series_count > 0u) {
    candidate.series = (my_echart_series_t*)my_mem_calloc(
        allocator, candidate.series_count, sizeof(*candidate.series));
    if (candidate.series == NULL) goto oom;
    for (size_t i = 0u; i < candidate.series_count; i++) {
      const my_echart_series_input_t* source = &src->series[i];
      my_echart_series_t* target = &candidate.series[i];
      target->id = copy_string(allocator, source->id);
      target->name = copy_string(allocator, source->name);
      target->stack = source->stack != NULL ? copy_string(allocator, source->stack) : NULL;
      target->type = source->type;
      target->data_count = source->data_count;
      target->color = source->color;
      target->y_axis_index = source->y_axis_index;
      target->show = source->show;
      if (target->id == NULL || target->name == NULL ||
          (source->stack != NULL && target->stack == NULL)) goto oom;
      if (target->data_count > 0u) {
        target->data = (double*)my_mem_alloc(allocator,
                                             target->data_count * sizeof(double));
        if (target->data == NULL) goto oom;
        memcpy(target->data, source->data,
               target->data_count * sizeof(double));
      }
    }
  }
  my_echart_option_free(dst);
  candidate.legend_hidden = src->legend_hidden;
  candidate.range_set = src->range_set;
  candidate.y_min = src->y_min;
  candidate.y_max = src->y_max;
  candidate.zoom_set = src->zoom_set;
  candidate.zoom_start = src->zoom_start;
  candidate.zoom_end = src->zoom_end;
  candidate.visual_map_set = src->visual_map_set;
  candidate.visual_map_min = src->visual_map_min;
  candidate.visual_map_max = src->visual_map_max;
  candidate.visual_map_low_color = src->visual_map_low_color;
  candidate.visual_map_high_color = src->visual_map_high_color;
  *dst = candidate;
  return MY_RET_OK;
oom:
  my_echart_option_free(&candidate);
  return MY_RET_OOM;
}
