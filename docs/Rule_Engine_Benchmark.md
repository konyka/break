# Rule Engine Benchmark Baseline

`engine/tools/rule_engine_bench.c` is a small, deterministic baseline for the
implemented rule-engine core (condition matching, action assignment, and
callback notification). It is a manually run C99 executable, not a CTest
test, because elapsed time is sensitive to the host, scheduler, compiler, and
build configuration.

Build and run it from an engine build tree:

```text
cmake --build engine/build --target rule_engine_bench
engine/build/rule_engine_bench
```

For multi-config generators use `engine/build/Debug/rule_engine_bench.exe`.
The focused behavior evidence is `ctest --test-dir engine/build -R
test_rule_engine --output-on-failure`, not the timing output.

The benchmark reports `elapsed_seconds`, `run_count`, and workload counters for
two fixed cases:

- `sparse`: one matching boolean fact and one missing fact across two rules;
- `dense`: four populated boolean facts across five rules, with one missing
  fact to retain a sparse lookup in the denser rule set.

Each case performs 100 cold `re_program_load`/destroy cycles and 10,000 warm
`re_engine_run` calls after one program installation and fact setup. `clock()`
is used for portable process CPU elapsed time; no benchmark numbers are
committed or treated as performance claims. Compare runs only when compiler,
build type, machine, and workload are recorded alongside the output.

This is a baseline for profiling decisions, not an optimization result. It does
not imply RETE, JIT, SIMD, concurrency, or optimal performance.

The repository has no bounded rule-engine fuzz driver or fuzz-specific CMake
convention beyond manual `EXCLUDE_FROM_ALL` mutation fuzzers for larger engine
subsystems. A rule-engine fuzz smoke target is therefore deferred until the
core has a dedicated input-mutation harness and bounded seed/iteration
contract; no deferred upstream feature is implemented here.
