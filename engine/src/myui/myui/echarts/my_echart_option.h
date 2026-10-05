#ifndef MY_ECHART_OPTION_H
#define MY_ECHART_OPTION_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

#define MY_ECHART_MAX_SERIES 8u
#define MY_ECHART_MAX_TITLE 128u
#define MY_ECHART_MAX_ID 64u

typedef enum my_echart_series_type_t {
  MY_ECHART_LINE = 0,
  MY_ECHART_BAR,
  MY_ECHART_SCATTER,
  MY_ECHART_PIE,
  MY_ECHART_RADAR,
  MY_ECHART_FUNNEL,
  MY_ECHART_HEATMAP,
  MY_ECHART_BOXPLOT
} my_echart_series_type_t;

typedef struct my_echart_series_input_t {
  const char* id;
  const char* name;
  my_echart_series_type_t type;
  const double* data;
  size_t data_count;
  uint32_t color;
  unsigned y_axis_index;
  const char* stack;
  bool show;
} my_echart_series_input_t;

typedef struct my_echart_option_input_t {
  const char* title;
  const char* const* x_axis_data;
  size_t x_axis_count;
  const my_echart_series_input_t* series;
  size_t series_count;
} my_echart_option_input_t;

typedef struct my_echart_series_t {
  char* id;
  char* name;
  my_echart_series_type_t type;
  double* data;
  size_t data_count;
  uint32_t color;
  unsigned y_axis_index;
  char* stack;
  bool show;
} my_echart_series_t;

typedef struct my_echart_option_t {
  const my_allocator_t* allocator;
  char* title;
  char** x_axis_data;
  size_t x_axis_count;
  my_echart_series_t* series;
  size_t series_count;
} my_echart_option_t;

void my_echart_option_init(my_echart_option_t* option,
                           const my_allocator_t* allocator);
void my_echart_option_free(my_echart_option_t* option);
my_ret_t my_echart_option_copy(my_echart_option_t* dst,
                               const my_echart_option_input_t* src,
                               const my_allocator_t* allocator);
my_ret_t my_echart_option_validate(const my_echart_option_input_t* input);

#endif
