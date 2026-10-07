# Native Multi-Grid Design

## Goal

Extend `my_chart` from one implicit plot to N explicit grids (ECharts
`grid[]` equivalent) without regressions and without introducing allocation in
the paint path.

## Key Insight

All 16 draw functions already take `(x, y, w, h)` plot-rect parameters. The
single-plot assumption lives only in:

1. `chart_plot_rect()` — one rect from `CHART_PAD_*` constants;
2. axis-range lookup — `y_min/y_max` + `y2_min/y2_max` on the chart;
3. labels/zoom/hover — shared across all series.

Multi-grid is therefore a data-model + dispatch change, not a rewrite of the
drawing layer.

## Data Model (zero-allocation, fixed capacity)

```c
#define MY_CHART_MAX_GRIDS 4u

typedef struct {
    float left, top, width, height;  /* fractions of widget rect, 0..1 */
    size_t series[MY_CHART_MAX_SERIES];  /* series indices assigned here */
    size_t series_count;
    size_t y_axis_left;   /* axis slot index */
    size_t y_axis_right;
    bool visible;
} my_chart_grid_t;

typedef struct {
    float min, max;
    bool range_set;
} my_chart_axis_t;
```

`my_chart_t` gains `grids[]`, `grid_count`, and a small axis-slot array
(`MY_CHART_MAX_AXES = 8`, two per grid). Capacity matches common ECharts
usage; overflow is rejected up front, never truncated silently.

## Backward Compatibility

`grid_count == 1` (default) keeps today's behavior exactly: grid 0 covers the
legacy padded rect (`CHART_PAD_*`), its axes alias the existing
`y_min/y_max/y2_min/y2_max` fields, and every existing test, adapter
projection, and MVVM binding is untouched. Legacy setters write through to
grid 0 / axis slots 0-1.

## Layout (performance-optimal)

- Grid rects are stored as fractions; resolved into a stack-local array once
  per `on_paint` — O(grids), no heap allocation, cache-friendly.
- Overlapping fractions are allowed by ECharts (span plots); we keep that
  semantic rather than enforcing disjoint rects.
- Series draw order stays declaration order within each grid; grids render in
  index order. No per-frame sorting.

## Axis Ranges

- Automatic range computation is scoped per grid: only that grid's assigned
  visible series contribute.
- Explicit ranges target `(grid, slot)` pairs.
- `chart_axis_range()` lookup takes the axis slot index.

## Option Layer & Adapter

`my_echart_option_input_t` gains an optional `grids` array:

```c
typedef struct {
    float left, top, width, height;
    const size_t* series_indices;
    size_t series_count;
    bool range_set; float y_min, y_max;      /* left axis */
    bool range2_set; float y2_min, y2_max;   /* right axis */
} my_echart_grid_input_t;
```

Validation: fractions finite in 0..1, series indices in range, no series
assigned twice across grids (unless intentionally omitted → grid 0 default),
grid count ≤ `MY_ECHART_MAX_GRIDS`. The adapter extends the atomic snapshot
with grids; series without an explicit assignment default to grid 0.

## MVVM

The existing single-option pointer binding is unchanged — a multi-grid option
flows through the same `MY_VALUE_POINTER` property, adapter apply, and
revision-driven `sync_model` re-projection.

## Interaction

When grids have `link_axis_pointer` enabled, hovering any linked grid draws the
category guide line at the same index across every visible linked grid. The
tooltip text remains anchored to the hovered grid; unlinked grids retain their
independent guide behavior.

- `my_chart_hit_test()` scans visible grids front-to-back (last-declared
  wins on overlap, matching ECharts) and maps to that grid's category axis.
- dataZoom stays chart-global in this phase (cross-grid linking is the
  documented follow-up).

## Delivery Phases (all landed)

1. Phase A — native grid model + fractional layout + backward compat (TDD).
2. Phase B — option/adapter grids + atomic snapshot extension (TDD).
3. Phase C — MVVM multi-grid round-trip through the existing binding (TDD).
4. Phase D — per-grid hit test (last-declared-wins), hover markers and
   tooltip guide rendered on the owning grid, docs, full regression,
   sanitizer, push.

## Interaction (as landed)

Hover markers draw on the rect of the grid owning each series. The pointer move
handler records the hit grid; when `link_axis_pointer` is enabled on that grid,
the category guide line is also rendered on every visible grid with the same
flag. The tooltip text remains on the hovered grid. `chart_grid_at()` scans
visible grids front-to-back and is exposed for host-side use.

## Non-Goals

- Arbitrary axis counts beyond the per-grid left/right axes.
- Arbitrary axis counts per grid beyond left/right (follow-up).
- Per-grid dirty-rect invalidation (widget-level invalidation remains).
