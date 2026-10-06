# ECharts Native MVVM Bridge

The Phase 5 bridge binds one owned normalized option pointer through a named
MyUI view-model property. It performs an explicit synchronous initial apply and
`my_echart_mvvm_sync()` refresh. It intentionally does not reinterpret scalar
`my_value_t` values as chart options or invent thread-safety semantics.
