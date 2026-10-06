#ifndef MY_ECHART_H
#define MY_ECHART_H

#include "myui/echarts/my_echart_option.h"

typedef struct my_echart_t my_echart_t;

typedef enum my_echart_model_action_type_t {
  MY_ECHART_MODEL_ACTION_LEGEND_SELECT = 0,
  MY_ECHART_MODEL_ACTION_LEGEND_UNSELECT,
  MY_ECHART_MODEL_ACTION_LEGEND_TOGGLE_SELECT
} my_echart_model_action_type_t;

typedef struct my_echart_model_action_t {
  my_echart_model_action_type_t type;
  const char* series_id;
} my_echart_model_action_t;

my_echart_t* my_echart_create(const my_allocator_t* allocator);
void my_echart_destroy(my_echart_t* chart);
my_ret_t my_echart_set_option(my_echart_t* chart,
                              const my_echart_option_input_t* input,
                              bool not_merge, bool lazy_update);
my_ret_t my_echart_flush(my_echart_t* chart);
my_ret_t my_echart_remove_series(my_echart_t* chart, const char* series_id);
const my_echart_option_t* my_echart_get_option(const my_echart_t* chart);
unsigned my_echart_revision(const my_echart_t* chart);
my_ret_t my_echart_model_dispatch_action(my_echart_t* chart,
                                         const my_echart_model_action_t* action);

#endif
