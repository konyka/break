# myui Chart Widget

`my_chart` is a native `myui` widget inspired by the useful parts of ECharts:
borrowed data series, line/bar modes, automatic or explicit Y ranges, labels,
legends, pointer-driven hover state, and a compact tooltip.

## Basic usage

```c
#include "myui/widgets/my_chart.h"

static const float revenue[] = {10.0f, 18.0f, 15.0f, 26.0f};
static const char* days[] = {"Mon", "Tue", "Wed", "Thu"};
my_chart_series_t series = {"Revenue", revenue, 4u, 0xE85D75FFu};
my_widget_t* chart = my_chart_create(allocator, MY_CHART_LINE);

my_chart_set_title(chart, "Weekly revenue");
my_chart_set_labels(chart, days, 4u);
my_chart_set_series(chart, 0u, &series);
my_chart_set_range(chart, 0.0f, 30.0f);
```

Series values, names, and labels are borrowed. They must remain valid for the
lifetime of the chart. The widget supports up to `MY_CHART_MAX_SERIES` series
for both modes. Line mode overlays series in declaration order; bar mode lays
series out as grouped bars per category and draws values around the zero axis.
Line and bar modes share one category axis: series with different lengths keep
their samples aligned to the same category positions instead of stretching to
the full plot width.
Call `my_chart_set_stacked(chart, true)` for stacked bar mode. Positive values
stack upward from zero and negative values stack downward; line charts ignore
this flag. The automatic range includes the positive and negative stack totals.
All segments in one category share the same horizontal bar slot; grouped mode
remains the default when stacking is disabled.
Hover markers on stacked bars follow the visible segment endpoint rather than
the raw unstacked value.
Static annotations use `my_chart_add_mark_point()`, which anchors a borrowed
label to one series category sample (ECharts `markPoint` equivalent). Up to
`MY_CHART_MAX_MARK_POINTS` marks are stored; `my_chart_clear_mark_points()`
removes them and `my_chart_get_mark_point_count()` reports the active count.
Mark points on stacked bars follow the same visible segment endpoint as hover
markers.
`my_chart_set_data_zoom(chart, start, end)` restricts the rendered category
window to `[start, end)` (ECharts `dataZoom` equivalent); `end` must be greater
than `start`. `my_chart_clear_data_zoom()` restores the full range and
`my_chart_get_data_zoom()` reports whether a window is active. The Y range,
legends, and tooltip contents continue to use the full data set, while line,
bar, hover, and mark-point geometry are clipped to the window.
`my_chart_add_mark_line(chart, value, label, color)` draws a horizontal
reference line at a Y value (ECharts `markLine` equivalent), with an optional
borrowed label and color; up to `MY_CHART_MAX_MARK_LINES` lines are stored.
`my_chart_clear_mark_lines()` removes them and
`my_chart_get_mark_line_count()` reports the active count. Lines outside the
visible Y range are skipped.
Axis configuration matches ECharts `yAxis.name` / `yAxis.splitNumber`:
`my_chart_set_axis_title()` draws a Y-axis label and
`my_chart_set_grid_line_count()` sets the horizontal grid line count
(2..8, default 5); `my_chart_get_grid_line_count()` reports the effective
value.
Secondary Y axis (ECharts dual-axis) is available via
`my_chart_set_series_axis(chart, index, 0|1)`; `0` binds the left axis and `1`
the right axis. `my_chart_has_secondary_axis()` reports whether any series is
bound to the right axis, and the right axis draws its own tick labels.
`my_chart_get_axis_range()` returns the effective range per axis and
`my_chart_set_secondary_range()` fixes an explicit right-axis range. Series on
different axes are scaled independently while sharing the same category axis.
`my_chart_add_mark_area(chart, y_min, y_max, label, color)` paints a shaded
Y-band (ECharts `markArea` equivalent) behind the series, with an optional
borrowed label and ARGB color; `y_max` must be greater than `y_min`. Up to
`MY_CHART_MAX_MARK_AREAS` bands are stored; `my_chart_clear_mark_areas()` and
`my_chart_get_mark_area_count()` manage the active set.
Chart types are selected with `my_chart_create(allocator, mode)`:
`MY_CHART_LINE`, `MY_CHART_BAR`, `MY_CHART_SCATTER`, `MY_CHART_PIE`,
`MY_CHART_RADAR`, `MY_CHART_FUNNEL`, `MY_CHART_HEATMAP`, or
`MY_CHART_BOXPLOT`
`MY_CHART_RADAR` (ECharts `series.type` equivalents). Scatter draws one filled
point per category sample and honors
series visibility, zoom, and secondary-axis bindings like line mode.
Pie uses the first visible series as positive slice weights, approximates each
sector with a backend-neutral polygon path, and honors visibility and animation
progress. Non-positive slices are skipped; all-zero data produces no sectors.
Radar uses labels as polygon axes and each visible series as a filled data
polygon; it reuses the configured Y range, animation progress, and visualMap
colors.
Funnel uses the first visible series as positive stage weights and draws
centered trapezoid stages that narrow toward the final stage; labels are drawn
inside each stage when provided and animation progress scales stage widths.
Heatmap uses each visible series as a row and each value index as a column;
visualMap colors the cells, and short rows leave trailing cells empty.
Boxplot uses the first five values of each visible series as
`min/Q1/median/Q3/max` and draws whiskers, an interquartile box, and a median
stroke for each series.
Rendering progress is deterministic and externally driven with
`my_chart_set_animation_progress(chart, progress)`, where `0` renders values
from the zero baseline and `1` renders final values. The default is `1`; a
window-manager or `my_animator` callback can update progress and invalidate the
widget without the chart owning a timer. `my_chart_get_animation_progress()`
reports the current value.
`my_chart_set_visual_map(chart, min, max, low_color, high_color)` enables a
linear ECharts `visualMap`-style color interpolation for data values. It is
applied to line/scatter strokes and points, bars, and their annotations;
`my_chart_clear_visual_map()` restores each series' configured color.
An enabled visualMap also renders a compact continuous gradient legend with
its low/high numeric labels in the plot header.
Brush selection is available for Cartesian charts: drag with the left pointer
button across the plot to select a category interval, query it with
`my_chart_get_brush()`, and clear it with `my_chart_clear_brush()`. The selected
window is rendered as a translucent overlay; pie charts use sector hover rather
than brush selection.
For accessibility integrations, `my_chart_get_accessible_description()` returns
a bounded summary containing the title, chart type, series count, category count,
and series names. Focused Cartesian charts also support Left/Right key
navigation across categories, updating the same hover/tooltip state used by
pointer interaction.
Series must be added contiguously starting at index `0`; attempting to create a
hole in the series array is rejected.
Series values must be finite; `my_chart_set_series()` rejects `NaN` and
infinite samples. Explicit ranges must be finite and strictly increasing.

For grouped bars, add series contiguously and keep the category index aligned
across series. A shorter series simply omits its bar in later categories; the
automatic range still considers every supplied finite value.

Pointer movement over the plot selects the nearest category across the longest
series. Applications can read `my_chart_get_hover_index()` or
`my_chart_get_tooltip()` to integrate a custom overlay. The tooltip includes
every series that has a value at the selected category, formatted as a
comma-separated list, prefixed by the matching X-axis label when one is
available; the built-in paint path also shows a compact tooltip.
The selected data items receive a dark-and-light marker emphasis in the plot,
so the active category remains visible even when several series overlap.
Series visibility can be controlled independently with
`my_chart_set_series_visible()` or by clicking a legend entry. Hidden series
are removed from rendering, automatic ranges, and tooltip values; their
legend entry remains dimmed so it can be clicked again, matching ECharts
legend selection behavior.
The built-in plot includes horizontal grid lines, Y labels, X labels, and
explicit X/Y axis strokes. Hover state is cleared when the widget receives a
`hover_leave` event.

Y-axis ticks preserve up to four fractional digits and trim trailing zeroes;
for example, an explicit range produces labels such as `1.25`, `0.5`, and
`-0.5` instead of rounding all ticks to integers.

## Verification

The contract and interaction tests are registered as `test_myui_chart`:

```bash
cmake -S engine -B engine/build-ui-chart -DENGINE_BUILD_TESTS=ON
cmake --build engine/build-ui-chart --target test_myui_chart
ctest --test-dir engine/build-ui-chart -R '^test_myui_chart$' --output-on-failure
```

The software canvas and native X11/RHI test suites should also be run before a
release. The widget intentionally uses the backend-neutral `my_vgcanvas` API,
so the same chart code is shared by software, OpenGL, and Vulkan UI paths.

Set `MYUI_CHART_DUMP_PPM=/tmp/chart.ppm` while running `test_myui_chart` to
inspect the line-chart software render. Set
`MYUI_CHART_BAR_DUMP_PPM=/tmp/chart-bars.ppm` to capture the grouped-bar
regression frame used for visual verification.
