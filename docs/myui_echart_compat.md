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
existing series by stable `id`; adding/removing series and richer component
merging are reserved for the next adapter phases.

## Phase 3: native event/action adapter

`my_echart_event_adapter_t` maps MyUI pointer down/move/up, wheel, and left/right
key events to stable semantic chart events. Event payloads preserve native
coordinates, time, button/modifiers, and reserved series/data/category indexes.
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
