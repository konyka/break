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
  if (option->mark_points != NULL)
    for (size_t i = 0u; i < option->mark_point_count; i++)
      my_mem_free(option->allocator, option->mark_points[i].label);
  if (option->mark_lines != NULL)
    for (size_t i = 0u; i < option->mark_line_count; i++)
      my_mem_free(option->allocator, option->mark_lines[i].label);
  if (option->grids != NULL)
    for (size_t i = 0u; i < option->grid_count; i++)
      my_mem_free(option->allocator, option->grids[i].series_indices);
  my_mem_free(option->allocator, option->grids);
  if (option->mark_areas != NULL)
    for (size_t i = 0u; i < option->mark_area_count; i++)
      my_mem_free(option->allocator, option->mark_areas[i].label);
  my_mem_free(option->allocator, option->mark_points);
  my_mem_free(option->allocator, option->mark_lines);
  my_mem_free(option->allocator, option->mark_areas);
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
        series->type < MY_ECHART_LINE || series->type > MY_ECHART_THEME_RIVER ||
        (series->data_count > 0u && series->data == NULL) ||
        series->y_axis_index >= MY_ECHART_MAX_AXES_PER_GRID)
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
  if (input->mark_point_count > MY_ECHART_MAX_MARK_POINTS ||
      (input->mark_point_count > 0u && input->mark_points == NULL) ||
      input->mark_line_count > MY_ECHART_MAX_MARK_LINES ||
      (input->mark_line_count > 0u && input->mark_lines == NULL) ||
      input->mark_area_count > MY_ECHART_MAX_MARK_AREAS ||
      (input->mark_area_count > 0u && input->mark_areas == NULL))
    return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < input->mark_line_count; i++)
    if (!isfinite(input->mark_lines[i].value)) return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < input->mark_area_count; i++)
    if (!isfinite(input->mark_areas[i].y_min) ||
        !isfinite(input->mark_areas[i].y_max) ||
        input->mark_areas[i].y_max <= input->mark_areas[i].y_min)
      return MY_RET_INVALID_PARAMS;
  if (input->dataset_count > 0u && input->dataset == NULL)
    return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < input->dataset_count; i++) {
    const my_echart_dimension_input_t* dim = &input->dataset[i];
    if (!valid_string(dim->name) ||
        (dim->count > 0u && dim->values == NULL))
      return MY_RET_INVALID_PARAMS;
    for (size_t j = 0u; j < dim->count; j++)
      if (!isfinite(dim->values[j])) return MY_RET_INVALID_PARAMS;
    for (size_t j = 0u; j < i; j++)
      if (strcmp(dim->name, input->dataset[j].name) == 0)
        return MY_RET_INVALID_PARAMS;
  }
  for (size_t i = 0u; i < input->series_count; i++) {
    const my_echart_series_input_t* series = &input->series[i];
    bool resolves = false;
    if (series->dataset_dimension == NULL) continue;
    if (series->dataset_dimension[0] == '\0') return MY_RET_INVALID_PARAMS;
    for (size_t j = 0u; j < input->dataset_count; j++) {
      if (strcmp(series->dataset_dimension, input->dataset[j].name) == 0) {
        resolves = true;
        break;
      }
    }
    if (!resolves) return MY_RET_INVALID_PARAMS;
  }
  if (input->transform != MY_ECHART_TRANSFORM_NONE) {
    bool key_found = false;
    size_t key_count = 0u;
    if (input->transform == MY_ECHART_TRANSFORM_FILTER) {
      if (input->filter_dimension == NULL ||
          input->filter_dimension[0] == '\0' ||
          input->filter_op < MY_ECHART_FILTER_EQ ||
          input->filter_op > MY_ECHART_FILTER_LE)
        return MY_RET_INVALID_PARAMS;
      for (size_t i = 0u; i < input->dataset_count; i++) {
        if (input->dataset[i].count != input->dataset[0].count)
          return MY_RET_INVALID_PARAMS;
        if (strcmp(input->filter_dimension, input->dataset[i].name) == 0)
          key_found = true;
      }
      if (!key_found) return MY_RET_INVALID_PARAMS;
      return MY_RET_OK;
    }
    if (input->transform_dimension == NULL ||
        input->transform_dimension[0] == '\0')
      return MY_RET_INVALID_PARAMS;
    for (size_t i = 0u; i < input->dataset_count; i++) {
      if (input->dataset[i].count != input->dataset[0].count)
        return MY_RET_INVALID_PARAMS;
      if (strcmp(input->transform_dimension, input->dataset[i].name) == 0) {
        key_found = true;
        key_count = input->dataset[i].count;
      }
    }
    if (!key_found) return MY_RET_INVALID_PARAMS;
    if (key_count == 0u) return MY_RET_INVALID_PARAMS;
  }
  if (input->grid_count > MY_ECHART_MAX_GRIDS ||
      (input->grid_count > 0u && input->grids == NULL))
    return MY_RET_INVALID_PARAMS;
  for (size_t i = 0u; i < input->grid_count; i++) {
    const my_echart_grid_input_t* grid = &input->grids[i];
    if (!isfinite(grid->left) || !isfinite(grid->top) ||
        !isfinite(grid->width) || !isfinite(grid->height) ||
        grid->left < 0.0 || grid->top < 0.0 ||
        grid->width <= 0.0 || grid->height <= 0.0 ||
        grid->left + grid->width > 1.0 + 1e-9 ||
        grid->top + grid->height > 1.0 + 1e-9)
      return MY_RET_INVALID_PARAMS;
    if (grid->series_count > input->series_count)
      return MY_RET_INVALID_PARAMS;
    if (grid->series_count > 0u && grid->series_indices == NULL)
      return MY_RET_INVALID_PARAMS;
    for (size_t j = 0u; j < grid->series_count; j++) {
      if (grid->series_indices[j] >= input->series_count)
        return MY_RET_INVALID_PARAMS;
      for (size_t k = 0u; k < i; k++)
        for (size_t m = 0u; m < input->grids[k].series_count; m++)
          if (input->grids[k].series_indices[m] == grid->series_indices[j])
            return MY_RET_INVALID_PARAMS;
    }
    if (grid->axis_count == 0u ||
        grid->axis_count > MY_ECHART_MAX_AXES_PER_GRID)
      return MY_RET_INVALID_PARAMS;
    for (size_t a = 0u; a < grid->axis_count; a++)
      if (grid->axis_range_set[a] &&
          (!isfinite(grid->axis_min[a]) || !isfinite(grid->axis_max[a]) ||
           grid->axis_max[a] <= grid->axis_min[a]))
        return MY_RET_INVALID_PARAMS;
    for (size_t j = 0u; j < grid->series_count; j++)
      if (input->series[grid->series_indices[j]].y_axis_index >=
          grid->axis_count)
        return MY_RET_INVALID_PARAMS;
  }
  return MY_RET_OK;
}

my_ret_t my_echart_option_copy(my_echart_option_t* dst,
                               const my_echart_option_input_t* src,
                               const my_allocator_t* allocator) {
  my_echart_option_t candidate;
  size_t* row_order = NULL;
  size_t row_count = 0u;
  if (my_echart_option_validate(src) != MY_RET_OK || dst == NULL)
    return MY_RET_INVALID_PARAMS;
  my_echart_option_init(&candidate, allocator);
  if (src->transform == MY_ECHART_TRANSFORM_FILTER) {
    const my_echart_dimension_input_t* key = NULL;
    for (size_t i = 0u; i < src->dataset_count; i++)
      if (strcmp(src->filter_dimension, src->dataset[i].name) == 0) {
        key = &src->dataset[i];
        break;
      }
    row_order = (size_t*)my_mem_alloc(allocator, key->count * sizeof(*row_order));
    if (row_order == NULL) return MY_RET_OOM;
    for (size_t i = 0u; i < key->count; i++) {
      double v = key->values[i];
      bool keep = src->filter_op == MY_ECHART_FILTER_EQ ? v == src->filter_value
                   : src->filter_op == MY_ECHART_FILTER_NE ? v != src->filter_value
                   : src->filter_op == MY_ECHART_FILTER_GT ? v > src->filter_value
                   : src->filter_op == MY_ECHART_FILTER_GE ? v >= src->filter_value
                   : src->filter_op == MY_ECHART_FILTER_LT ? v < src->filter_value
                                                           : v <= src->filter_value;
      if (keep) row_order[row_count++] = i;
    }
  } else if (src->transform != MY_ECHART_TRANSFORM_NONE) {
    const my_echart_dimension_input_t* key = NULL;
    for (size_t i = 0u; i < src->dataset_count; i++)
      if (strcmp(src->transform_dimension, src->dataset[i].name) == 0) {
        key = &src->dataset[i];
        break;
      }
    row_order = (size_t*)my_mem_alloc(allocator, key->count * sizeof(*row_order));
    if (row_order == NULL) return MY_RET_OOM;
    row_count = key->count;
    for (size_t i = 0u; i < key->count; i++) row_order[i] = i;
    for (size_t i = 1u; i < key->count; i++) {
      size_t row = row_order[i];
      size_t j = i;
      while (j > 0u) {
        bool swap = src->transform == MY_ECHART_TRANSFORM_SORT_ASC
                        ? key->values[row_order[j - 1u]] > key->values[row]
                        : key->values[row_order[j - 1u]] < key->values[row];
        if (!swap) break;
        row_order[j] = row_order[j - 1u];
        j--;
      }
      row_order[j] = row;
    }
  }
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
      const double* data = source->data;
      size_t data_count = source->data_count;
      if (source->dataset_dimension != NULL) {
        for (size_t j = 0u; j < src->dataset_count; j++) {
          if (strcmp(source->dataset_dimension, src->dataset[j].name) == 0) {
            data = src->dataset[j].values;
            data_count = src->dataset[j].count;
            break;
          }
        }
        if (row_order != NULL) data_count = row_count;
      }
      target->id = copy_string(allocator, source->id);
      target->name = copy_string(allocator, source->name);
      target->stack = source->stack != NULL ? copy_string(allocator, source->stack) : NULL;
      target->type = source->type;
      target->data_count = data_count;
      target->color = source->color;
      target->y_axis_index = source->y_axis_index;
      target->show = source->show;
      if (target->id == NULL || target->name == NULL ||
          (source->stack != NULL && target->stack == NULL)) goto oom;
      if (data_count > 0u) {
        target->data = (double*)my_mem_alloc(allocator,
                                             data_count * sizeof(double));
        if (target->data == NULL) goto oom;
        if (row_order != NULL) {
          for (size_t j = 0u; j < data_count; j++)
            target->data[j] = data[row_order[j]];
        } else {
          memcpy(target->data, data, data_count * sizeof(double));
        }
      }
    }
  }
  my_echart_option_free(dst);
  candidate.mark_point_count = src->mark_point_count;
  if (candidate.mark_point_count > 0u) {
    candidate.mark_points = (my_echart_mark_point_t*)my_mem_calloc(
        allocator, candidate.mark_point_count, sizeof(*candidate.mark_points));
    if (candidate.mark_points == NULL) goto oom;
    for (size_t i = 0u; i < candidate.mark_point_count; i++) {
      candidate.mark_points[i].series_index = src->mark_points[i].series_index;
      candidate.mark_points[i].category_index =
          src->mark_points[i].category_index;
      if (src->mark_points[i].label != NULL) {
        candidate.mark_points[i].label =
            copy_string(allocator, src->mark_points[i].label);
        if (candidate.mark_points[i].label == NULL) goto oom;
      }
    }
  }
  candidate.mark_line_count = src->mark_line_count;
  if (candidate.mark_line_count > 0u) {
    candidate.mark_lines = (my_echart_mark_line_t*)my_mem_calloc(
        allocator, candidate.mark_line_count, sizeof(*candidate.mark_lines));
    if (candidate.mark_lines == NULL) goto oom;
    for (size_t i = 0u; i < candidate.mark_line_count; i++) {
      candidate.mark_lines[i].value = src->mark_lines[i].value;
      candidate.mark_lines[i].color = src->mark_lines[i].color;
      if (src->mark_lines[i].label != NULL) {
        candidate.mark_lines[i].label =
            copy_string(allocator, src->mark_lines[i].label);
        if (candidate.mark_lines[i].label == NULL) goto oom;
      }
    }
  }
  candidate.mark_area_count = src->mark_area_count;
  if (candidate.mark_area_count > 0u) {
    candidate.mark_areas = (my_echart_mark_area_t*)my_mem_calloc(
        allocator, candidate.mark_area_count, sizeof(*candidate.mark_areas));
    if (candidate.mark_areas == NULL) goto oom;
    for (size_t i = 0u; i < candidate.mark_area_count; i++) {
      candidate.mark_areas[i].y_min = src->mark_areas[i].y_min;
      candidate.mark_areas[i].y_max = src->mark_areas[i].y_max;
      candidate.mark_areas[i].color = src->mark_areas[i].color;
      if (src->mark_areas[i].label != NULL) {
        candidate.mark_areas[i].label =
            copy_string(allocator, src->mark_areas[i].label);
        if (candidate.mark_areas[i].label == NULL) goto oom;
      }
    }
  }
  candidate.legend_hidden = src->legend_hidden;
  candidate.tooltip_hidden = src->tooltip_hidden;
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
  candidate.grid_count = src->grid_count;
  if (candidate.grid_count > 0u) {
    candidate.grids = (my_echart_grid_t*)my_mem_calloc(
        allocator, candidate.grid_count, sizeof(*candidate.grids));
    if (candidate.grids == NULL) goto oom;
    for (size_t i = 0u; i < candidate.grid_count; i++) {
      candidate.grids[i].left = src->grids[i].left;
      candidate.grids[i].top = src->grids[i].top;
      candidate.grids[i].width = src->grids[i].width;
      candidate.grids[i].height = src->grids[i].height;
    memcpy(candidate.grids[i].axis_range_set, src->grids[i].axis_range_set,
           sizeof(candidate.grids[i].axis_range_set));
    memcpy(candidate.grids[i].axis_min, src->grids[i].axis_min,
           sizeof(candidate.grids[i].axis_min));
    memcpy(candidate.grids[i].axis_max, src->grids[i].axis_max,
           sizeof(candidate.grids[i].axis_max));
    candidate.grids[i].axis_count = src->grids[i].axis_count;
    candidate.grids[i].link_axis_pointer = src->grids[i].link_axis_pointer;
      candidate.grids[i].series_count = src->grids[i].series_count;
      if (candidate.grids[i].series_count > 0u) {
        candidate.grids[i].series_indices = (size_t*)my_mem_alloc(
            allocator,
            candidate.grids[i].series_count * sizeof(size_t));
        if (candidate.grids[i].series_indices == NULL) goto oom;
        memcpy(candidate.grids[i].series_indices, src->grids[i].series_indices,
               candidate.grids[i].series_count * sizeof(size_t));
      }
    }
  }
  my_mem_free(allocator, row_order);
  *dst = candidate;
  return MY_RET_OK;
oom:
  my_mem_free(allocator, row_order);
  my_echart_option_free(&candidate);
  return MY_RET_OOM;
}
