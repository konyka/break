# arm64 QEMU Profiler and Trace Tools Design

## Context

The arm64 lane currently selects exactly 61 tests. Five diagnostics tests remain
outside it: `test_profiler`, `test_clock_offset`, `test_trace_core_app`,
`test_trace_merge`, and `test_trace_merge_tool`. This slice adds exactly those
five and produces a 66-test selection.

## Approaches

1. Reuse executable-target emulation for four unit tests and add a dedicated
   optional runner only for the target `trace_merge` executable used by the host
   CMake tool driver. This is the recommended minimal change.
2. Emulate the host CMake process or `/bin/sh`. This is rejected because the driver
   and shell are host tools; only `trace_merge` is target code.
3. Exclude the tool test or skip its empty-argument case under QEMU. This is
   rejected because the existing tool contract must remain intact.

## Existing Behavior and Baseline

The four unit tests have direct executable-target registrations and generated
QEMU commands:

- profiler: 28 cases for frames, regions, export, provenance, and thread records;
- clock offset: eight cases for sampling, error bounds, and multi-peer shifts;
- core_app trace: 15 cases for conversion, writer clocks, offset/session readers;
- trace merge core: five cases for labels/PIDs, documents, overflow, and buffers.

The tool test is different: host CMake executes the target `trace_merge` binary
for merge, clock-offset, multi-session, malformed-input, and CLI error cases.
Without adaptation, the four unit tests pass under QEMU but the tool test fails
because its output files are never produced. Native focused execution passes
5/5 in 0.05 seconds.

## Runner Design

Pass the existing emulator only to the tool registration:

```cmake
"-DTRACE_MERGE_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

In `test_trace_merge_tool.cmake`, prefix every direct target-tool launch with
`${TRACE_MERGE_RUNNER}`. This covers the shared `run_tool` helper and the direct
clock-offset/multi-peer/named-session calls.

The empty `--out` argument case intentionally uses host `/bin/sh` because CMake
`execute_process` drops empty arguments. Preserve that behavior by constructing a
POSIX-shell-quoted runner prefix, one single-quoted element per runner argument,
then invoking:

```cmake
/bin/sh -c "${trace_merge_runner_text}\"$0\" --out '' \"$1\"" ...
```

With no runner, the command is byte-for-byte the existing native launch shape.
With QEMU, only the target executable receives emulation; `/bin/sh` remains host.
Runner elements containing whitespace or single quotes must remain one argument.

No timeout, expected exit code, output assertion, or malformed-input check is
relaxed or skipped.

## CI Change

Append these five targets to the existing arm64 build command:

```text
test_profiler test_clock_offset test_trace_core_app test_trace_merge trace_merge
```

Add this locally end-anchored alternative to the existing CTest selection:

```text
test_(profiler|clock_offset|trace_core_app|trace_merge|trace_merge_tool)$
```

The local `$` prevents future derived names from silently entering the selection.
Keep all 61 previous tests, emulator environment, object checks, verbose output,
`--no-tests=error`, 300-second outer timeout, and failure propagation unchanged.

## TDD and Verification

1. Preserve the unmodified cross RED: four unit tests pass and the tool test
   fails because direct target execution does not produce its output.
2. Add the optional runner and require native 5/5 plus cross 5/5. Require 28/8/15/5
   unit summaries and `trace_merge tool contract passed`, including the special
   empty-argument case. Verify a native wrapper whose path contains whitespace
   and a single quote to exercise the shell-prefix boundary.
3. Run a PyYAML/native-selection contract against the old workflow. Require all
   five build targets, the exact alternative, future-prefix rejection, and
   previous 61 plus exactly these five = 66. Observe RED on the old build command.
4. Apply only the CI build-list/selection edits and require the unchanged contract
   to pass with an explicit 66-name expected set.
5. Run native full regression; require 455 tests, zero failures, and only the
   four established platform skips.
6. Execute the final workflow run blocks in a clean Ubuntu 24.04 container with
   the runner CMake prerequisite. Require 66/66, all old/new evidence, and exactly
   one existing QEMU ptrace setup skip.
7. Request independent read-only review, resolve adopted findings test-first,
   push the verified commits, and assert the exact-HEAD remote arm64 job log
   contains the same 66-test selection and all old/new evidence.

## Documentation and Boundaries

Append concise evidence to the build guide, implementation status, runtime
overview, and missing-capabilities inventory without replacing history.

This is a selected 66-test suite, not full arm64 CTest. Live remote sessions,
production debugger authorization, rendering, Snowflake transport scenarios,
QUIC, GPU, and physical devices remain outside this slice unless already covered
by the existing 61 tests.
