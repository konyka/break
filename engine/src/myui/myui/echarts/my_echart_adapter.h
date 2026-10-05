#ifndef MY_ECHART_ADAPTER_H
#define MY_ECHART_ADAPTER_H

#include "myui/echarts/my_echart_option.h"
#include "myui/my_widget.h"

typedef struct my_echart_adapter_t my_echart_adapter_t;

/* Bridge subset: line, bar, and scatter series with one shared stack. */
my_echart_adapter_t* my_echart_adapter_create(
    my_widget_t* chart, const my_allocator_t* allocator);
void my_echart_adapter_destroy(my_echart_adapter_t* adapter);
my_ret_t my_echart_adapter_apply(my_echart_adapter_t* adapter,
                                 const my_echart_option_t* option);

#endif
