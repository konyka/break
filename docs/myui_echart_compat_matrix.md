# Native ECharts Compatibility Matrix

This matrix is the contract for the native C adapter. It is intentionally
versioned by capability, not presented as browser/JavaScript ECharts parity.

## Supported in the current native renderer

| Area | Supported |
|---|---|
| Core model | owned typed option, validation, replace/lazy update, id merge with append + capacity rejection, dataset columns resolved by dimension name (encode) with row-aligned sort and filter transforms |
| Series | all 16 native modes: line, bar, scatter, pie, radar, funnel, heatmap, boxplot, candlestick, gauge, sankey, parallel, treemap, graph, calendar, themeRiver |
| Cartesian | category labels, grid, fractional ticks, 1-3 Y axes per grid (axis 0 left, additional axes right-offset), up to 4 grids, per-grid series assignment/ranges/hit-test |
| Bar | grouped, positive/negative stacked, shared category slots |
| Interaction | native MyUI pointer/key events, hover, tooltip, legend selection, brush, dataZoom, linked multi-grid axis pointers, and connected-chart dataZoom groups; adapter-event bridge fills series/data/category indexes via chart hit-test and pie/funnel/radar hover payloads |
| Annotations | markPoint, markLine, markArea (option-level with owned labels + native renderer) |
| Styling | series colors, series value labels (label.show on cartesian modes), visualMap interpolation and gradient legend |
| Animation | externally driven deterministic progress and fake-clock scheduler |
| MVVM | owned option pointer binding, explicit sync, property notification sync |
| JSON input | owning parser for the supported option subset: title, axes, series (inline data, single- or multi-dimension dataset encode, label show), legend/tooltip, dataZoom, visualMap, annotations, dataset transforms, and multi-grid layout |
| Components | legend/tooltip visibility, explicit Y range, category dataZoom window with slider rendering/drag, continuous visualMap config, model-level dataZoom/visualMap/brush actions, event actions auto-drive an attached model |

## Supported only by the native adapter subset

The current renderer adapter accepts every native series type
(line/bar/scatter/pie/radar/funnel/heatmap/boxplot) with finite numeric data,
category labels, title, visibility, Y-axis selection, and one shared bar stack.
Boxplot series require at least five samples. Mixed types, mixed stacks,
non-bar stacks, unsupported axis/component options, and native-capacity
overflow return `MY_RET_NOT_SUPPORTED`.

## Not implemented

- dataset transforms beyond row-aligned sort/filter;
- full tooltip formatter/trigger/position semantics;
- complete dataZoom/visualMap/brush action payloads beyond the supported model
  subset;
- native hit-test results in semantic event payloads for every chart type;
- JavaScript expression-driven option semantics, browser runtime, and custom
  series callbacks;
- full theme/style/rich-text system and browser ARIA tree;
- native setter-level atomic snapshot commit after a renderer setter failure.

Unsupported entries are rejected or remain explicitly outside the adapter
contract; they must not be silently ignored.
