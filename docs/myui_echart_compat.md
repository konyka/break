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

## Planned phases

1. `setOption` replace/merge/lazy-update semantics.
2. MyUI native pointer/key events mapped to semantic chart events/actions.
3. Fake-clock animation scheduling.
4. Adapter from normalized options to `my_chart`.
5. Dataset/encode, multi-grid/multi-axis, and additional series options.

Unsupported options will return deterministic errors rather than being silently
ignored. The adapter uses MyUI native events and does not introduce a browser or
JavaScript runtime.
