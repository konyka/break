# MyUI ECharts Usage Guide

This guide shows how to use every supported ECharts feature through the
MyUI native C engine, with runnable snippets. All snippets are exercised
end-to-end by the demo program (`engine/tools/echarts_demo.c`).

## Interactive explorer (live, adjustable data)

```sh
cmake --build build --target myui_explorer --parallel 2
./build/myui_explorer                                    # x11 + software
./build/myui_explorer --platform wayland --backend gl    # wayland + GLES2
./build/myui_explorer --platform x11 --backend gl        # x11 + EGL/GLES2
./build/myui_explorer --platform wayland --backend soft  # wayland + wl_shm
./build/myui_explorer --selftest dir  # headless scripted frames
./build/myui_explorer --shot out.ppm  # render one frame and exit
```

`--platform` picks the window system (x11 | wayland) and `--backend` the
rendering path (soft | gl): software renders into a CPU framebuffer
(XImage blit on X11, a wl_shm buffer pool on Wayland); gl creates an EGL
window surface with a GLES2 context and drives the engine's
`my_vgcanvas_gles2` hardware backend directly. All four combinations are
verified live; the build falls back to x11+soft-only when the Wayland/EGL
development packages are absent.

The left pane is a live `my_chart`; the right pane is a real MyUI widget
panel that drives it in real time:

- 16 type buttons switch the chart mode instantly;
- the *data scale* slider rescales all series; the *animation* slider
  scrubs the deterministic animation;
- checkboxes toggle stacked bars, value labels, and the legend;
- *Randomize* regenerates the 4x8 dataset; *Zoom +/-* (or the mouse
  wheel over the chart) narrows the dataZoom window;
- hover the chart for tooltips and the axis guide; click legend entries
  to toggle series (built-in chart behavior);
- keys: `1..9/0` quick mode switch, `R` randomize, `+/-` zoom, `S` dump
  the current frame to `/tmp/myui_explorer_shot.ppm`.

## Run the demo

```sh
cmake -S engine -B build -DENGINE_BUILD_TESTS=ON -DENGINE_VULKAN=OFF
cmake --build build --target echarts_demo --parallel 2
mkdir -p /tmp/scenes && ./build/echarts_demo /tmp/scenes
```

The demo renders every feature below to numbered PPM files (320x180) and
self-checks each frame; it exits non-zero if any scene renders empty.

## Three ways to drive a chart

1. **Native widget API** — direct, zero-allocation, borrowed data.
2. **ECharts option model** — owned option with validation, merge, actions,
   and revision-driven projection through an adapter.
3. **JSON** — parse a real ECharts option subset into an owned document.

All three render through the same `my_chart` widget on any vgcanvas.

### 1. Native widget

```c
#include "myui/widgets/my_chart.h"

my_widget_t* chart = my_chart_create(NULL, MY_CHART_LINE);
my_chart_series_t s = {"Revenue", values, 5u, 0u, 0u, false}; /* last: labels */
const char* labels[] = {"Mon","Tue","Wed","Thu","Fri"};
my_chart_set_labels(chart, labels, 5u);
my_chart_set_series(chart, 0u, &s);
chart->vtable->on_paint(chart, vg);   /* host paints via its canvas */
```

Series colors default to the palette; pass a color to override. The sixth
series field (`show_labels`) draws the value at each point (line/scatter) or
above each bar.

### 2. Option model + adapter

```c
my_echart_option_input_t in = {0};     /* borrowed input */
in.title = "Dashboard";
in.series = &(my_echart_series_input_t){
    "a", "Sales", MY_ECHART_BAR, values, 5, 0, 0, NULL, true, NULL, false};
in.series_count = 1;
my_echart_option_t owned;
my_echart_option_init(&owned, NULL);
my_echart_option_copy(&owned, &in, NULL);      /* validate + deep copy */
my_echart_adapter_t* adapter = my_echart_adapter_create(chart, NULL);
my_echart_adapter_apply(adapter, &owned);      /* atomic projection */
```

`my_echart_set_option(model, &in, not_merge, lazy_update)` drives the same
owned model with replace / id-merge / lazy-flush semantics; dispatch model
actions and call `my_echart_adapter_sync_model` to re-project on revision
change.

### 3. JSON option

```c
const char* json =
    "{\"title\":{\"text\":\"JSON option\"},"
    "\"xAxis\":{\"data\":[\"A\",\"B\",\"C\"]},"
    "\"series\":[{\"name\":\"Sales\",\"type\":\"bar\","
    "\"data\":[10,30,20],\"label\":{\"show\":true}}]}";
my_echart_json_doc_t* doc = my_echart_json_doc_parse(json, strlen(json), NULL);
if (doc != NULL && my_echart_json_doc_error(doc) == NULL) {
  my_echart_option_copy(&owned, my_echart_json_doc_option(doc), NULL);
  my_echart_adapter_apply(adapter, &owned);
}
my_echart_json_doc_destroy(&doc);      /* frees every owned buffer */
```

Supported JSON keys: `title.text`, `xAxis.data`, `series[]` (all 16 types,
`data`, `encode` single or multi-dimension, `label.show`, `yAxisIndex`,
`color`, `itemStyle.color`, `stack`, `show`), `legend.show`, `tooltip.show`,
`yAxis.min/max`, `dataZoom[0].startValue/endValue`, `visualMap` with
`inRange.color`, `grid[]` with percent or fraction rects, per-grid
`axisCount` + `yAxis` ranges, series-level `markPoint`/`markLine`/`markArea`,
top-level `dataset.source` (column-object) and `transform` (sort/filter).

## Feature snippets

### All 16 chart types

`MY_CHART_LINE, BAR, SCATTER, PIE, RADAR, FUNNEL, HEATMAP, BOXPLOT,
CANDLESTICK, GAUGE, SANKEY, PARALLEL, TREEMAP, GRAPH, CALENDAR,
THEME_RIVER` — pass the mode to `my_chart_create` (or the matching
`MY_ECHART_*` type string in JSON: e.g. `"themeRiver"`, `"k"` for
candlestick). Candlestick consumes 4 consecutive values per candle;
boxplot 5 per box.

### Grouped / stacked bars

```c
my_chart_set_stacked(chart, true);   /* stacked; omit for grouped */
```

### Dual Y axis (and up to 3 axes per grid)

```c
my_chart_series_t right = {"%", vals, 5u, 0u, 1u, false}; /* axis 1 */
my_chart_set_series_axis(chart, 1u, 1u);
my_chart_set_range(chart, 0.0f, 30.0f);
my_chart_set_secondary_range(chart, 0.0f, 100.0f);
```

For a third axis, declare a grid with `axis_count = 3` (see demo scene 22);
axis 0 is drawn left, further axes in right-side columns.

### dataZoom window

```c
my_chart_set_data_zoom(chart, 1u, 3u);   /* categories [1,3) */
my_chart_clear_data_zoom(chart);
```

### visualMap

```c
my_chart_set_visual_map(chart, 0.0f, 100.0f, 0x3A86FFFFu, 0xE85D75FFu);
```

Scatter/heatmap points interpolate between the low and high colors.

### Annotations

`markPoint`, `markLine`, and `markArea` are committed through
`my_chart_apply_snapshot` (native) or the option fields (model/JSON):

```c
static const my_chart_mark_point_t marks[] = {{0u, 3u, "peak"}};
snapshot.marks = marks; snapshot.mark_count = 1u;
```

### Multi-grid layout

```c
my_chart_set_grid_count(chart, 2u);
my_chart_grid_desc_t grid = {0};
grid.left = 0.05f; grid.top = 0.05f; grid.width = 0.9f; grid.height = 0.4f;
grid.series_indices[0] = 0u; grid.series_count = 1u;
grid.axis_count = 1u; grid.visible = true;
my_chart_set_grid(chart, 0u, &grid);
```

Each grid resolves its rect from fractions of the widget, keeps series
assignment, per-axis explicit or automatic ranges, and its own hit test
(`chart_grid_at`, `my_chart_hit_test`).

### Linked axis pointers

Set `grid.link_axis_pointer = true` on the grids you want linked; hovering
any of them draws the category guide line on all linked grids.

### Connected chart groups

```c
my_chart_group_join(chart_a, 1u);
my_chart_group_join(chart_b, 1u);
my_chart_set_data_zoom(chart_a, 1u, 3u);  /* also applied to chart_b */
```

dataZoom set/clear and hover enter/leave propagate to group members; chart
destruction auto-leaves the registry.

### Dataset + transforms + encode

```c
static const my_echart_dimension_input_t dims[] = {
    {"key", key, 3u}, {"value", value, 3u}};
in.dataset = dims; in.dataset_count = 2u;
in.transform = MY_ECHART_TRANSFORM_SORT_DESC;
in.transform_dimension = "key";
```

JSON series can bind with `"encode":{"y":"value"}` or
`"encode":{"y":["open","close","low","high"]}` (row-interleaved for
candlestick/boxplot).

### Model actions

```c
my_echart_model_action_t a = {0};
a.type = MY_ECHART_MODEL_ACTION_DATA_ZOOM;   /* or BRUSH_SELECT,
                                                VISUAL_MAP_RANGE,
                                                DATA_ZOOM_RESET,
                                                LEGEND_* */
a.payload.zoom_start = 1u; a.payload.zoom_end = 3u;
my_echart_model_dispatch_action(model, &a);
my_echart_adapter_sync_model(adapter, model);  /* re-projects on revision */
```

Event-layer actions (`my_echart_dispatch_action`) auto-drive an attached
model via `my_echart_event_adapter_attach_model`.

### MVVM binding

```c
my_view_model_t* vm = my_view_model_dummy_create(NULL);
my_binding_context_t* ctx = my_binding_context_create(NULL, vm);
my_value_t v; my_value_init(&v, NULL);
my_value_set_pointer(&v, &owned_option);
my_view_model_set_prop(vm, "option", &v);
my_echart_mvvm_binding_t* b =
    my_echart_mvvm_bind_option(NULL, ctx, adapter, "option");
/* setting "option" again re-projects automatically */
```

### Animation

```c
my_chart_set_animation_progress(chart, 0.35f);  /* deterministic frame */
```

Drive progress from any ticker; values, bars, and stacks interpolate.

### Tooltips

Hover a chart (`my_chart_set_hover_index` or pointer events) and read
`my_chart_get_tooltip(chart, buf, sizeof(buf))`. The tooltip box flips
left/up near widget edges. Non-cartesian modes (pie/funnel/radar) report
the first visible series; cartesian modes list every series at the hovered
category.

## Where to look next

- Capability contract and remaining boundaries:
  `docs/myui_echart_compat_matrix.md`
- Multi-grid design: `docs/myui_chart_multigrid_design.md`
- Adapter internals: `docs/myui_echart_adapter.md`
- MVVM: `docs/myui_echart_mvvm.md`
