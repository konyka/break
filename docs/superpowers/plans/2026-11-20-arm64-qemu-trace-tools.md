# arm64 QEMU Trace Tools Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add profiler, clock offset, trace core/merge, and the real trace_merge tool contract to the arm64 lane for an exact 66-test selection.

**Architecture:** Use existing executable-target emulation for four unit tests. Add a dedicated optional `TRACE_MERGE_RUNNER` for target-tool launches inside the host CMake driver, including POSIX-quoted runner arguments for the shell-based empty-argument case.

**Tech Stack:** CMake/CTest, POSIX shell, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly five tests; previous 61 + 5 = 66.
- Use `test_(profiler|clock_offset|trace_core_app|trace_merge|trace_merge_tool)$` with a local end anchor.
- Emulate only the target `trace_merge`, never host CMake or `/bin/sh`.
- Preserve every exit-code/output assertion, timeout, and the empty-argument case.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Do not claim live remote authorization, full arm64 CTest, rendering, Snowflake/QUIC, GPU, or physical-device coverage.

---

### Task 1: Target-tool runner

**Files:**
- Modify: `engine/CMakeLists.txt:8002-8007`
- Modify: `engine/tests/test_trace_merge_tool.cmake`

**Interfaces:**
- Consumes: `CMAKE_CROSSCOMPILING_EMULATOR` list.
- Produces: optional `TRACE_MERGE_RUNNER` list; empty means direct native execution.

- [ ] **Step 1: Preserve RED and native control**

The unmodified cross focused run must remain four passing unit tests and a failed
`test_trace_merge_tool`; native focused is 5/5. Do not mask the missing output or
skip the tool test.

- [ ] **Step 2: Forward the runner at registration**

Add immediately after `TRACE_MERGE`:

```cmake
"-DTRACE_MERGE_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

- [ ] **Step 3: Prefix every target launch**

In the driver, change the shared helper and the three direct clock/session calls
from:

```cmake
execute_process(COMMAND "${TRACE_MERGE}" ...
```

to:

```cmake
execute_process(COMMAND ${TRACE_MERGE_RUNNER} "${TRACE_MERGE}" ...
```

Near the top, build the shell prefix:

```cmake
set(trace_merge_runner_text "")
foreach(trace_merge_runner_arg IN LISTS TRACE_MERGE_RUNNER)
    string(REPLACE "'" "'\"'\"'" quoted_trace_merge_runner_arg "${trace_merge_runner_arg}")
    string(APPEND trace_merge_runner_text "'${quoted_trace_merge_runner_arg}' ")
endforeach()
```

For the host-shell empty-argument case, use:

```cmake
execute_process(COMMAND /bin/sh -c
    "${trace_merge_runner_text}\"$0\" --out '' \"$1\""
    "${TRACE_MERGE}" "${WORK}/a.json" ...
```

Keep the existing result variables, timeout, and assertions unchanged.

- [ ] **Step 4: Verify native and cross focused tests**

Build `test_profiler test_clock_offset test_trace_core_app test_trace_merge
trace_merge`, then run:

```bash
ctest --verbose --no-tests=error \
  -R '^test_(profiler|clock_offset|trace_core_app|trace_merge|trace_merge_tool)$'
```

Require native and cross 5/5, unit summaries 28/8/15/5, and `trace_merge tool
contract passed`. Exercise a native runner wrapper whose own path contains both
whitespace and a single quote; the complete tool contract must still pass.

- [ ] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/tests/test_trace_merge_tool.cmake
git commit -m "test: support emulated trace merge tool"
```

### Task 2: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-trace-tools.md`

- [ ] **Step 1: Run the RED CI contract**

```bash
python3 - <<'PY'
from pathlib import Path
import re
import subprocess
import yaml

w = yaml.safe_load(Path('.github/workflows/ci.yml').read_text())
steps = w['jobs']['lane-cross-aarch64-linux']['steps']
build = next(s['run'] for s in steps if s.get('name') == 'Build the arm64 targets')
run = next(s['run'] for s in steps if s.get('name') == 'Run selected tests under QEMU')
targets = ('test_profiler test_clock_offset test_trace_core_app '
           'test_trace_merge trace_merge')
assert build.rstrip().endswith('test_rhi_frame_lifecycle_contract ' + targets), 'missing trace build targets'
alternative = 'test_(profiler|clock_offset|trace_core_app|trace_merge|trace_merge_tool)$'
assert alternative in run, 'missing exact trace alternative'
pattern = re.search(r"-R '([^']+)'", run).group(1)
for name in ('test_profiler_extra', 'test_clock_offset_extra',
             'test_trace_core_app_extra', 'test_trace_merge_extra',
             'test_trace_merge_tool_extra'):
    assert not re.search(pattern, name), f'unexpected selection: {name}'
out = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', pattern,
], text=True)
selected = set(re.findall(r'Test\s+#\d+:\s+(\S+)', out))
trace = {
    'test_profiler', 'test_clock_offset', 'test_trace_core_app',
    'test_trace_merge', 'test_trace_merge_tool',
}
assert len(selected) == 66, f'expected 66, got {len(selected)}'
assert trace <= selected, 'missing trace selections'
print('exact 66-test trace selection and anchor contract passed')
PY
```

Expected: FAIL at `missing trace build targets` before editing CI.

- [ ] **Step 2: Apply the minimal CI edit**

Append the five targets and add the exact alternative shown in Step 1. Keep all
other workflow inputs unchanged.

- [ ] **Step 3: Run GREEN and append docs**

Run Step 1 unchanged, then compare the actual selection with an explicit previous
61 + five = 66 set. Record runner scope, shell quoting, unit counts, tool contract,
exact 66 selection, and exclusions. Commit as `ci: run arm64 trace tool tests`.

### Task 3: Final verification and remote proof

- [ ] **Step 1:** In `build-core-app-net`, run `cmake . && make -j6 && ctest -j4
  --timeout 240 --output-on-failure`; require 455 tests, zero failures, and four
  established platform skips. Run `git diff --check`.
- [ ] **Step 2:** Execute the final workflow run blocks in a clean Ubuntu 24.04
  container with `:z` and runner CMake. Require 66/66, 28/8/15/5, tool contract,
  all old summaries/contracts/e2e, and exactly one existing ptrace setup skip.
- [ ] **Step 3:** Request read-only review of all launch sites, shell quoting,
  native compatibility, exact selection, and docs. Fix adopted findings test-first.
  Fetch/rebase if needed, rerun affected inputs, and push without force.
- [ ] **Step 4:** Assert the exact-HEAD remote job reports `0 tests failed out of
  66`, exact 66 names, all old/new evidence, and one existing ptrace setup skip.
  Append URLs/commit/review to `docs/Implementation_Status.md`, commit as `docs:
  record arm64 trace tool CI results`, push, and finish clean with the broader
  goal open.
