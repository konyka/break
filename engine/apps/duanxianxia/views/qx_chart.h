/**
 * @file qx_chart.h
 * @brief duanxianxia clone: self-drawn chart widget (M15) — line chart
 * (intraday curve) and bar chart (rise/fall distribution). The site uses
 * echarts; this is a vgcanvas approximation (docs/apps/duanxianxia.md).
 */
#ifndef DXX_QX_CHART_H
#define DXX_QX_CHART_H

#include "myui/my_widget.h"

typedef enum dxx_chart_mode_t {
  DXX_CHART_LINE = 0, /**< polyline + grid + axis ticks */
  DXX_CHART_BAR       /**< signed buckets: red up / green down */
} dxx_chart_mode_t;

my_widget_t* dxx_chart_create(const my_allocator_t* allocator,
                              dxx_chart_mode_t mode);

/**
 * @brief Set the plotted series (points borrowed — must outlive the
 * chart; the static snapshot tables qualify). ymin/ymax fix the value
 * range (bar mode: symmetric ±max(|ymin|,|ymax|) around the center
 * axis). Triggers a repaint.
 */
void dxx_chart_set_series(my_widget_t* chart, const char* name,
                          const float* points, int count, float ymin,
                          float ymax);

/** @brief Set bucket labels for bar mode (borrowed). */
void dxx_chart_set_labels(my_widget_t* chart, const char* const* labels);

/** @brief Current series name (NULL when never set). */
const char* dxx_chart_get_series_name(my_widget_t* chart);

#endif /* DXX_QX_CHART_H */
