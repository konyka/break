# myui ECharts renderer adapter

`my_echart_adapter_t` is a small ownership bridge from a normalized
`my_echart_option_t` to the existing typed `my_chart_t` widget. It is not a
full ECharts implementation.

The supported subset is:

- line, bar, scatter, pie, radar, funnel, heatmap, and boxplot series;
- one or more series of one shared type;
- finite double values converted to finite `float` values within `FLT_MAX`;
- category labels, title, visibility, and left/right axis selection;
- bar options where every series uses the same non-empty stack name;
- boxplot series carrying at least five samples
  (`min/Q1/median/Q3/max`);
- legend visibility (`legend_hidden`) and tooltip visibility
  (`tooltip_hidden`), an explicit Y range, a category `dataZoom` window, and a
  continuous `visualMap` (min/max with low/high colors), all committed through
  the same atomic snapshot;
- `markPoint`, `markLine`, and `markArea` annotations with deep-copied
  labels and bounded counts matching the native renderer limits.

Mixed series types, mixed stack names, stacks on non-bar charts, and other
ECharts series/configuration features are rejected with
`MY_RET_NOT_SUPPORTED`; they are not silently discarded.

The adapter retains the chart widget, deep-copies the normalized option, and
owns converted float buffers for as long as the chart borrows them. Applying
an option stages and validates all allocations and conversions before changing
the native widget. Invalid input and out-of-memory failures leave the prior
chart/model unchanged. Destroying the adapter first detaches borrowed labels
and series, then releases the owned payload and widget reference.
