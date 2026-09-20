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
