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
The focused behavior evidence is the `test_rule_engine` executable and the
separately registered backward, transaction, RETE, fuzz-smoke, C99, and
optional executor-stress targets. Run the rule-engine group through
`ctest --test-dir engine/build -R test_rule_engine|test_backward_machine|rule_engine_fuzz_smoke
--output-on-failure`; the timing output is not a correctness gate.

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

## Hardening gate

The bounded smoke target runs 256 seeded parser/evaluator, window, and provider
mutations. The C11 executor stress target runs 64 iterations without sleeps.

```text
cmake --build engine/build --target rule_engine_fuzz_smoke
ctest --test-dir engine/build -R rule_engine_fuzz_smoke --output-on-failure
cmake -S engine -B engine/build-hardening -G Ninja -DRULE_ENGINE_ENABLE_C11_PARALLEL=ON -DENGINE_ENABLE_IPO=OFF
cmake --build engine/build-hardening --target test_rule_engine_executor_stress
ctest --test-dir engine/build-hardening -R 'test_rule_engine_executor_stress|test_rule_engine' --output-on-failure
```

When `<threads.h>` is unavailable, the stress target is not created; that is an
unavailable gate, not a pass. `test_rule_engine` also compares serial and
parallel callback traces deterministically.

ASan/UBSan presets are available through `engine/CMakePresets.json` where the
active compiler supports them. The benchmark threshold format is
`case.metric=max_seconds` in `engine/scripts/rule_engine_bench_thresholds.txt`.

```text
cmake -DBENCH=engine/build/rule_engine_bench -DTHRESHOLD=engine/scripts/rule_engine_bench_thresholds.txt -DRUNS=3 -P engine/scripts/rule_engine_bench_regression.cmake
```

Thresholds are conservative smoke limits, not portable performance claims.
Redis remains disabled by default; enabling it compiles the native adapter only
when hiredis headers and a library are discovered. This check does not claim a
live integration service.
