# arm64 QEMU PAL and Task Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add four PAL tests and two task-system tests to the arm64 lane for an exact 72-test selection.

**Architecture:** Reuse six generated executable-target QEMU commands. Change only the build target list and one locally anchored CTest alternative.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_platform_config`, `test_platform_null_safety`, `test_platform_fs_write`, `test_platform_size_semantics`, `test_task`, and `test_task_singleton`; previous 66 + 6 = 72.
- Use `test_(platform_config|platform_null_safety|platform_fs_write|platform_size_semantics|task|task_singleton)$`.
- Preserve all previous 66 tests, emulator settings, object checks, timeout, and failure propagation.
- Add no dependency, skip, retry, status mask, assertion relaxation, or X11 content.
- Do not claim full arm64 CTest, WSI/window integration, mobile/device backends, editor/rendering, Snowflake/QUIC, GPU, or physical-device coverage.
- Append documentation evidence without replacing existing history.

---

### Task 1: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/runtime_thread_model.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-pal-task.md`

**Interfaces:**
- Consumes: existing executable-target emulation and 66-test workflow regex.
- Produces: exact 72-test arm64 selection with no driver API changes.

- [ ] **Step 1: Run the RED workflow and anchor contract**

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
targets = ('test_platform_config test_platform_null_safety test_platform_fs_write '
           'test_platform_size_semantics test_task test_task_singleton')
assert build.rstrip().endswith('trace_merge ' + targets), 'missing PAL/task build targets'
alternative = 'test_(platform_config|platform_null_safety|platform_fs_write|platform_size_semantics|task|task_singleton)$'
assert alternative in run, 'missing exact PAL/task alternative'
pattern = re.search(r"-R '([^']+)'", run).group(1)
for name in ('test_platform_config_extra', 'test_platform_null_safety_extra',
             'test_platform_fs_write_extra', 'test_platform_size_semantics_extra',
             'test_task_extra', 'test_task_singleton_extra'):
    assert not re.search(pattern, name), f'unexpected selection: {name}'
out = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', pattern,
], text=True)
selected = set(re.findall(r'Test\s+#\d+:\s+(\S+)', out))
pal_task = {
    'test_platform_config', 'test_platform_null_safety', 'test_platform_fs_write',
    'test_platform_size_semantics', 'test_task', 'test_task_singleton',
}
assert len(selected) == 72, f'expected 72, got {len(selected)}'
assert pal_task <= selected, 'missing PAL/task selections'
print('exact 72-test PAL/task selection and anchor contract passed')
PY
```

Expected before editing: FAIL at `missing PAL/task build targets`. The unmodified
native and cross baselines already pass 6/6 with 10/1/11/3/16/1 cases.

- [ ] **Step 2: Apply the minimal workflow edit**

Append exactly the six targets shown in Step 1 and add its exact alternative
inside the existing outer capture group. Do not add a global end anchor or edit
other workflow inputs.

- [ ] **Step 3: Run the GREEN selection contract**

Run Step 1 unchanged. Expected: `exact 72-test PAL/task selection and anchor
contract passed`. Compare the selected names with an explicit set containing the
previous 66 and exactly these six; no other name may be added or removed.

- [ ] **Step 4: Re-run focused native and cross tests**

```bash
cmake --build build-core-app-net --parallel 6 --target \
  test_platform_config test_platform_null_safety test_platform_fs_write \
  test_platform_size_semantics test_task test_task_singleton
ctest --test-dir build-core-app-net --verbose --no-tests=error \
  -R '^test_(platform_config|platform_null_safety|platform_fs_write|platform_size_semantics|task|task_singleton)$'
```

In the multiarch Ubuntu container, run the workflow dependency step, then the
same build targets and CTest regex against `build-arm64`.

Require native and cross 6/6, config/null/fs-write/size/task/singleton summaries
10/1/11/3/16/1, and no skip.

- [ ] **Step 5: Append documentation and commit**

Record the six targets and case counts, exact 72 selection, local anchor,
unchanged failure semantics, no-X11 constraint, and exclusions. Commit:

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md \
  docs/Implementation_Status.md docs/design/runtime_thread_model.md \
  docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-pal-task.md
git commit -m "ci: run arm64 PAL task tests"
```

### Task 2: Final verification and remote proof

**Files:**
- Modify after evidence: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: Task 1's exact 72-test workflow.
- Produces: native, clean-container, independent-review, and exact-HEAD remote evidence.

- [ ] **Step 1: Run native full regression**

Run `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure` in
`build-core-app-net`. Require 455 tests, zero failures, and only four established
platform skips. Run `git diff --check`.

- [ ] **Step 2: Run the final clean-container workflow**

Parse the final YAML and execute every `lane-cross-aarch64-linux` run block in a
fresh Ubuntu 24.04 container with `:z` mount and the runner CMake prerequisite.
Require 72/72, 10/1/11/3/16/1 summaries, every previous summary/contract/e2e
marker, and exactly one existing ptrace setup skip.

- [ ] **Step 3: Review and push**

Request read-only review of exact selection, local anchor, generated QEMU
commands, native compatibility, failure semantics, no-X11 constraint, and docs.
Fix adopted findings test-first and rerun affected verification. Fetch/rebase if
needed; rerun affected tests when selected inputs change, then push without force.

- [ ] **Step 4: Assert remote evidence and finish the slice**

For the exact pushed HEAD, assert the arm64 job reports `0 tests failed out of
72`, the exact 72 passed-test names, all old/new summaries and contracts, every
existing e2e marker, and exactly one existing ptrace setup skip. Append run/job
URLs, commit, and review result to `docs/Implementation_Status.md`.

```bash
git add docs/Implementation_Status.md
git commit -m "docs: record arm64 PAL task CI results"
git push origin master
```

Finish with a clean worktree and `HEAD == origin/master`; leave the broader goal
open for other unimplemented capabilities.
