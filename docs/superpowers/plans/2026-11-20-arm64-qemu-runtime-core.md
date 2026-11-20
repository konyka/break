# arm64 QEMU Runtime Core Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add runtime_core's nine unit cases and its target contract to the arm64 lane for an exact 35-test selection.

**Architecture:** Reuse executable-target emulation for the unit test and run the existing source-structure contract on host CMake. Change only the existing arm64 build target list and exact CTest selection; no product or test-source change is needed.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_runtime_core` and `test_runtime_core_target_contract`; previous 33 + 2 = 35.
- Use the exact alternative `test_runtime_core($|_target_contract)`; do not select runtime IO, reload, facade, or other runtime tests.
- Preserve all previous 33 tests, emulator settings, object checks, timeout, and failure propagation.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Do not claim full arm64 CTest, Lua/ECS, Snowflake/QUIC, GPU, or physical-device coverage.
- Append documentation evidence; do not replace existing history.

---

### Task 1: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-runtime-core.md`

**Interfaces:**
- Consumes: existing `CMAKE_CROSSCOMPILING_EMULATOR` and 33-test workflow regex.
- Produces: exact 35-test arm64 selection with no driver API changes.

- [ ] **Step 1: Run the RED workflow contract**

Run this from the repository root:

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
assert build.rstrip().endswith('test_core_app_network core_app test_runtime_core'), 'missing runtime_core build target'
assert 'test_runtime_core($|_target_contract)' in run, 'missing exact runtime_core alternative'
pattern = re.search(r"-R '([^']+)'", run).group(1)
out = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', pattern,
], text=True)
selected = set(re.findall(r'Test\s+#\d+:\s+(\S+)', out))
runtime = {'test_runtime_core', 'test_runtime_core_target_contract'}
assert runtime <= selected, 'runtime tests not selected'
assert len(selected) == 35, f'expected 35, got {len(selected)}'
assert not any(n.startswith('test_runtime_') and n not in runtime for n in selected), selected
print('exact 35-test runtime_core selection contract passed')
PY
```

Expected: FAIL at `missing runtime_core build target` before the workflow edit.
The two focused baselines already pass: native and cross 2/2, nine unit cases,
and `runtime_core target contract passed`.

- [ ] **Step 2: Apply the minimal workflow edit**

Append one target to the existing build command:

```text
test_runtime_core
```

Add one alternative inside the existing outer capture group:

```text
test_runtime_core($|_target_contract)
```

Do not edit any other workflow input.

- [ ] **Step 3: Run the GREEN workflow contract**

Run the Step 1 command unchanged. Expected: `exact 35-test runtime_core
selection contract passed`. Additionally inspect the selected names and require
all previous 33 plus the two runtime_core names, with no other runtime-prefixed
name.

- [ ] **Step 4: Re-run focused native and cross tests**

Native:

```bash
cmake --build build-core-app-net --parallel 6 --target test_runtime_core
ctest --test-dir build-core-app-net --verbose --no-tests=error \
  -R '^test_runtime_core($|_target_contract)$'
```

Cross in the Ubuntu multiarch container after running the workflow dependency
step:

```bash
cmake --build build-arm64 --parallel --target test_runtime_core
ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^test_runtime_core($|_target_contract)$'
```

Require 2/2, nine unit cases, the target contract, and no skip in both trees.

- [ ] **Step 5: Append documentation and commit**

Record the nine lifecycle-coordinator cases, host-only target contract, exact
35-test selection, exclusions, and unchanged emulator/timeout semantics. Commit:

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md \
  docs/Implementation_Status.md docs/design/runtime_overview.md \
  docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-runtime-core.md
git commit -m "ci: run arm64 runtime core tests"
```

### Task 2: Final verification and remote proof

**Files:**
- Modify after evidence: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: Task 1's exact 35-test workflow.
- Produces: native, clean-container, independent-review, and exact-HEAD remote evidence.

- [ ] **Step 1: Run native full regression**

```bash
cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure
```

Run in `build-core-app-net`; require 455 tests, zero failures, and only the four
established platform skips. Run `git diff --check`.

- [ ] **Step 2: Run the final clean-container workflow**

Parse the final YAML and execute every `lane-cross-aarch64-linux` run block in a
fresh Ubuntu 24.04 container with `:z` mount and the runner CMake prerequisite.
Require 35/35, nine runtime_core cases, `runtime_core target contract passed`,
all previous summaries/contracts/e2e, and exactly one existing ptrace setup skip.

- [ ] **Step 3: Review and push**

Request a read-only review of exact selection, host/target boundaries, native
compatibility, and documentation. Fix any adopted finding test-first and rerun
affected verification. Fetch `origin/master`, rebase without conflict if needed,
rerun affected tests if selected inputs change, then push without force.

- [ ] **Step 4: Assert the remote log and record evidence**

Find the CI run for the exact pushed HEAD and the job named `Linux arm64
cross-build + QEMU tests (GCC)`. Assert `0 tests failed out of 35`, the exact 35
passed-test names, all old/new summaries, both contracts, all existing e2e
markers, and exactly one existing ptrace setup skip. Append run/job URLs, commit,
and review result to `docs/Implementation_Status.md`.

```bash
git add docs/Implementation_Status.md
git commit -m "docs: record arm64 runtime core CI results"
git push origin master
```

Finish with a clean worktree and `HEAD == origin/master`; leave the broader goal
open for other unimplemented capabilities.
