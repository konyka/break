# Native ECharts Compatibility Matrix

This matrix is the contract for the native C adapter. It is intentionally
versioned by capability, not presented as browser/JavaScript ECharts parity.

## Supported in the current native renderer

| Area | Supported |
|---|---|
| Core model | owned typed option, validation, replace/lazy update, id merge with append + capacity rejection, dataset columns resolved by dimension name (encode) with row-aligned sort and filter transforms |
| Series | line, bar, scatter, pie, radar, funnel, heatmap, boxplot, candlestick, gauge, sankey, parallel (native modes) |
| Cartesian | category labels, grid, fractional ticks, left/right Y axes |
| Bar | grouped, positive/negative stacked, shared category slots |
| Interaction | native MyUI pointer/key events, hover, tooltip, legend selection, brush, dataZoom; adapter-event bridge fills series/data/category indexes via chart hit-test |
| Annotations | markPoint, markLine, markArea (option-level with owned labels + native renderer) |
| Styling | series colors, visualMap interpolation and gradient legend |
| Animation | externally driven deterministic progress and fake-clock scheduler |
| MVVM | owned option pointer binding, explicit sync, property notification sync |
| Components | legend/tooltip visibility, explicit Y range, category dataZoom window, continuous visualMap config |

## Supported only by the native adapter subset

The current renderer adapter accepts every native series type
(line/bar/scatter/pie/radar/funnel/heatmap/boxplot) with finite numeric data,
category labels, title, visibility, Y-axis selection, and one shared bar stack.
Boxplot series require at least five samples. Mixed types, mixed stacks,
non-bar stacks, unsupported axis/component options, and native-capacity
overflow return `MY_RET_NOT_SUPPORTED`.

## Not implemented

- JSON/JavaScript option parsing or a browser runtime;
- dataset transforms beyond row-aligned sort/filter and multi-dimensional
  `encode`;
- multiple grids and arbitrary axis counts;
- full tooltip formatter/trigger/position semantics;
- complete dataZoom/visualMap/brush action payloads and cross-chart linkage;
- native hit-test results in semantic event payloads for every chart type;
- graph, tree, treemap, calendar, themeRiver, and custom series;
- full theme/style/rich-text system and browser ARIA tree;
- native setter-level atomic snapshot commit after a renderer setter failure.

Unsupported entries are rejected or remain explicitly outside the adapter
contract; they must not be silently ignored.
