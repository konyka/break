# Native ECharts Compatibility Matrix

This matrix is the contract for the native C adapter. It is intentionally
versioned by capability, not presented as browser/JavaScript ECharts parity.

## Supported in the current native renderer

| Area | Supported |
|---|---|
| Core model | owned typed option, validation, replace/lazy update, basic id merge |
| Series | line, bar, scatter, pie, radar, funnel, heatmap, boxplot |
| Cartesian | category labels, grid, fractional ticks, left/right Y axes |
| Bar | grouped, positive/negative stacked, shared category slots |
| Interaction | native MyUI pointer/key events, hover, tooltip, legend selection, brush, dataZoom |
| Annotations | markPoint, markLine, markArea |
| Styling | series colors, visualMap interpolation and gradient legend |
| Animation | externally driven deterministic progress and fake-clock scheduler |
| MVVM | owned option pointer binding, explicit sync, property notification sync |

## Supported only by the native adapter subset

The current renderer adapter accepts line/bar/scatter, finite numeric data,
category labels, title, visibility, Y-axis selection, and one shared bar stack.
Mixed types, mixed stacks, non-bar stacks, unsupported axis/component options,
and native-capacity overflow return `MY_RET_NOT_SUPPORTED`.

## Not implemented

- JSON/JavaScript option parsing or a browser runtime;
- dataset/dimensions/encode/transform;
- multiple grids and arbitrary axis counts;
- full tooltip formatter/trigger/position semantics;
- complete dataZoom/visualMap/brush action payloads and cross-chart linkage;
- native hit-test results in semantic event payloads for every chart type;
- candlestick, graph, sankey, tree, treemap, parallel, gauge, calendar,
  themeRiver, and custom series;
- full theme/style/rich-text system and browser ARIA tree;
- native setter-level atomic snapshot commit after a renderer setter failure.

Unsupported entries are rejected or remain explicitly outside the adapter
contract; they must not be silently ignored.
