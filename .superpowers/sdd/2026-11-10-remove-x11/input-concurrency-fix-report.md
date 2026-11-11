# Input concurrency timeout fix report

Status: DONE (local branch only; no merge and no push).

## Root cause

The fourth-round Linux Clang/LLD Release log (`/tmp/remove-x11-final/ci4-linux-clang.log:2776-2798`) failed only at `test_input_extended.c:494`, the main consumer's `++guard < 1000000u` assertion in `haptic_multithreaded_producers_only_queue_commands`.

`InputExtended` has no asynchronous haptic worker. Producers submit and retrieve commands, while the main test thread must call `input_extended_haptic_pump()` to execute them. Before the fix:

- the main thread called pump continuously even when it executed no commands;
- each producer spun while its result was `PENDING` or the bounded queue was `OVERLOAD`;
- on a single CPU or a constrained Release schedule, these loops could starve the threads that had to make progress.

This is test scheduling starvation, not a demonstrated memory-order, queue-close, command-loss, or producer-finalization bug. The acquire/release `done` protocol and all haptic queue code are unchanged. A debugger altered scheduling enough to make the same test pass, so it was not used as evidence of a production fix.

## Deterministic RED

The unmodified test failed at the same guard when restricted to one CPU:

```bash
taskset -c 0 ./build-input-concurrency-clang-release/test_input_extended
```

A dedicated `test_input_extended_single_cpu` CTest was then added. It pins the process to the first CPU in its existing affinity mask and fails explicitly if affinity setup fails. Before the synchronization fix:

```bash
cmake --build build-input-concurrency-clang-release -j3 --target test_input_extended_single_cpu
ctest --test-dir build-input-concurrency-clang-release --output-on-failure --timeout 60 -R '^test_input_extended_single_cpu$'
```

Result: FAIL at `++guard < 1000000u`, matching the CI assertion. This is the committed deterministic regression rather than relying on multi-core repetition alone.

## Minimal GREEN

Only test synchronization changed:

- a producer yields with `platform_thread_yield()` only while its result is `PENDING` or the queue is `OVERLOAD`;
- the main thread records `fake.count` around each pump and yields only when no command executed;
- the one-million guard, all four producers x 64 requests, every result, and `haptic_count == 0` assertions remain intact;
- no arbitrary sleep, larger guard, removed assertion, or production queue change was introduced.

After the change:

```bash
cmake --build build-input-concurrency-clang-release -j3 --target test_input_extended_single_cpu test_input_extended
ctest --test-dir build-input-concurrency-clang-release --output-on-failure --timeout 60 -R '^test_input_extended(_single_cpu)?$'
```

Result: 2/2 PASS.

High-frequency Release verification:

```bash
ctest --test-dir build-input-concurrency-clang-release --output-on-failure --timeout 120 --repeat until-fail:100 -R '^test_input_extended(_single_cpu)?$'
```

Result: both targets completed all 100 iterations, 0 failures.

## Synchronization mutation

`build-input-concurrency-mutations/verify_no_yield.py` replaces all three conditional yields with no-ops in a build-tree copy, compiles it with Clang `-O2` and the single-CPU definition, and requires the original guard failure.

```bash
python3 build-input-concurrency-mutations/verify_no_yield.py
```

Result: `no-yield mutation: expected FAIL at guard; fixed source passes single-CPU CTest`. The source-tree fixed test then passed the Release repetition above. No mutated source was committed.

## Input-focused regression

The focused set was `test_input`, `test_input_extended`, `test_input_extended_single_cpu`, `test_gamepad_linux_feedback`, `test_gamepad_win_feedback_portable`, `test_win32_touch`, and `test_wayland_touch`.

- Normal Debug: 7/7 PASS.
- ASan+UBSan with `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1` and `UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`: 7/7 PASS, no findings.
- TSan with `TSAN_OPTIONS=halt_on_error=1`: 7/7 PASS, no races.

The same regex was used in each build tree:

```text
^(test_input|test_input_extended|test_input_extended_single_cpu|test_gamepad_linux_feedback|test_gamepad_win_feedback_portable|test_win32_touch|test_wayland_touch)$
```

## Full CI-like Release and non-graphics regression

Configuration matched the failing lane's Clang/LLD, Release, IPO, and OpenGL choices:

```bash
cmake -S engine -B build-input-ci4-clang-release -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-clang-linux.cmake" -DCMAKE_BUILD_TYPE=Release -DENGINE_ENABLE_IPO=ON -DENGINE_RHI_BACKEND=opengl
cmake --build build-input-ci4-clang-release -j3
ctest --test-dir build-input-ci4-clang-release -LE 'graphics|fuzz' -j3 --output-on-failure --timeout 120
```

Results:

- full build succeeded;
- 341 selected non-graphics tests: 340 PASS, 0 FAIL;
- the only non-passing entry was the existing platform-dependent `test_d3d12_dependency_gate` SKIP.

## Windows compile check

Zig `x86_64-windows-gnu` cross-compiled `test_input_extended`, `test_gamepad_win_feedback`, and `test_win32_touch` with `-j3`. `test_input_extended.exe` is an x86-64 PE32+ executable. No PE executable was run because no native Windows runtime was available.

## Limitations

- Remote GitHub Actions and native Windows/macOS scheduling were not rerun locally; the next native CI still has to confirm them.
- Windows evidence is cross-compilation only, not native execution.
- One hundred Release repetitions do not prove every possible interleaving; the meaningful evidence is the deterministic single-CPU RED, the minimal conditional-yield GREEN, the no-yield mutation, and sanitizer verification.
- No physical input hardware or haptic device behavior changed or was required for this test-only scheduling fix.
