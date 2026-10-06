# Native ECharts Compatibility Layer

The compatibility layer is being built in TDD phases above the existing
`my_chart` renderer. Phase 0/1 provides a typed, owned option foundation; it
does not claim JSON parsing or complete ECharts parity.

## Current foundation

- `my_echart_option_input_t` is a borrowed input description.
- `my_echart_option_t` owns a deep-copied normalized model.
- Validation rejects duplicate series IDs, unsupported types, invalid axis
  indexes, missing required strings/data, and non-finite numeric samples.
- Failed copies leave an existing destination option unchanged.

## Phase 2: setOption

`my_echart_set_option()` now supports replace (`not_merge=true`) and a
deterministic lazy-update mode. Lazy updates remain invisible through
`my_echart_get_option()` until `my_echart_flush()` is called. Merge mode updates
existing series by stable `id` and appends unknown ids up to
`MY_ECHART_MAX_SERIES`; option-level title and set component state (range,
zoom, visualMap, legend visibility) are taken from the incoming option, while
annotations are retained from the current model. Series removal and
`replaceMerge` remain reserved for later phases.

## Phase 3: native event/action adapter

`my_echart_event_adapter_t` maps MyUI pointer down/move/up, wheel, and left/right
key events to stable semantic chart events. Event payloads preserve native
coordinates, time, button/modifiers, and reserved series/data/category indexes.
`my_chart_hit_test()` offers a pure chart-local category lookup (plot-bounded,
zoom-aware, no hover mutation) that controllers can use to fill those index
payloads. `my_echart_adapter_event()` composes that bridge end to end: it maps
one delivered MyUI native event to a semantic payload and fills
series/data/category indexes from the adapter's chart (local-coordinate
hit-test, first visible series with data at the category; indexes stay
`MY_ECHART_INDEX_NONE` outside the plot, for key events, or when no visible
series has data there).
The adapter also exposes explicit `highlight`, `legendSelect`, `dataZoom`,
`brush`, `showTip`, and `hideTip` action payloads through removable callback
subscriptions. Subscription removal is safe during dispatch, and destroying an
adapter prevents later callbacks; destruction from a callback is deferred until
the active dispatch unwinds.

This phase is a native event/action adapter only. It does not integrate with a
renderer, hit-test chart data, or claim full ECharts parity.

## Phase 4: deterministic animation

`my_echart_animation_t` provides fake-clock progress from `0` to `1` without
owning a timer. Callers pass the progress to `my_chart_set_animation_progress`
from their MyUI/window-manager animation callback. This keeps animation tests
deterministic while allowing a real timer to drive production rendering.

## Remaining phases

1. Fake-clock animation scheduling.
2. Adapter from normalized options to `my_chart`.
3. Dataset/encode, multi-grid/multi-axis, and additional series options.

Unsupported options will return deterministic errors rather than being silently
ignored. The adapter uses MyUI native events and does not introduce a browser or
JavaScript runtime.

## Visual verification gate

The deterministic software-canvas chart suite renders representative line
fixtures at `120x100`, `320x180`, and `640x360`. It asserts non-empty semantic
geometry in each viewport; text rasterization is not compared by exact hash.
OpenGL/Vulkan tests remain separate smoke gates. Full pixel goldens require
reviewed, checked-in fixtures and are not replaced by an optional environment
variable dump.

## Atomic projection boundary

The current adapter stages owned option data and float conversion before native
projection, rejects unsupported/mixed configurations, and preserves the prior
chart state on validation/OOM failures. A future native snapshot commit API is
required before claiming setter-level atomicity for every possible renderer
failure.
