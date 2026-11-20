# arm64 QEMU RHI Core Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add RenderGraph and four headless RHI core tests to the arm64 lane for an exact 61-test selection.

**Architecture:** Reuse five generated executable-target QEMU commands over headless/stubbed RHI paths. Change only the build target list and two locally anchored CTest alternatives.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_render_graph`, `test_rhi_dispatch`, `test_rhi_capabilities`, `test_rhi_error_contract`, and `test_rhi_frame_lifecycle_contract`; previous 56 + 5 = 61.
- Use `test_render_graph$` and `test_rhi_(dispatch|capabilities|error_contract|frame_lifecycle_contract)$`.
- Preserve all previous 56 tests, emulator settings, object checks, timeout, and failure propagation.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Do not claim full arm64 CTest, runtime rollout/WSI/shader tools, real OpenGL/Vulkan, visual parity, GPU, or physical-device coverage.
- Append documentation evidence without replacing existing history.

---

### Task 1: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/rhi_runtime_backend.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-rhi-core.md`

**Interfaces:**
- Consumes: existing executable-target emulation and 56-test workflow regex.
- Produces: exact 61-test arm64 selection with no driver API changes.

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
targets = ('test_render_graph test_rhi_dispatch test_rhi_capabilities '
           'test_rhi_error_contract test_rhi_frame_lifecycle_contract')
assert build.rstrip().endswith('test_hotreload ' + targets), 'missing RHI build targets'
rhi_alt = 'test_rhi_(dispatch|capabilities|error_contract|frame_lifecycle_contract)$'
assert 'test_render_graph$' in run, 'missing anchored render graph test'
assert rhi_alt in run, 'missing exact RHI alternative'
pattern = re.search(r"-R '([^']+)'", run).group(1)
for name in ('test_render_graph_extra', 'test_rhi_dispatch_extra',
             'test_rhi_capabilities_extra', 'test_rhi_error_contract_extra',
             'test_rhi_frame_lifecycle_contract_extra'):
    assert not re.search(pattern, name), f'unexpected selection: {name}'
out = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', pattern,
], text=True)
selected = set(re.findall(r'Test\s+#\d+:\s+(\S+)', out))
rhi = {
    'test_render_graph', 'test_rhi_dispatch', 'test_rhi_capabilities',
    'test_rhi_error_contract', 'test_rhi_frame_lifecycle_contract',
}
assert len(selected) == 61, f'expected 61, got {len(selected)}'
assert rhi <= selected, 'missing RHI selections'
print('exact 61-test RHI selection and anchor contract passed')
PY
```

Expected before editing: FAIL at `missing RHI build targets`. The unmodified
native and cross baselines already pass 5/5 with 44 dispatch checks and 59/7/5/22
case summaries.

- [ ] **Step 2: Apply the minimal workflow edit**

Append exactly the five targets shown in Step 1 and add these alternatives inside
the existing outer capture group:

```text
test_render_graph$
test_rhi_(dispatch|capabilities|error_contract|frame_lifecycle_contract)$
```

Do not add a global end anchor or edit other workflow inputs.

- [ ] **Step 3: Run the GREEN selection contract**

Run Step 1 unchanged. Expected: `exact 61-test RHI selection and anchor contract
passed`. Compare the selected names with an explicit set containing the previous
56 and exactly these five; no other name may be added or removed.

- [ ] **Step 4: Re-run focused native and cross tests**

```bash
cmake --build build-core-app-net --parallel 6 --target \
  test_render_graph test_rhi_dispatch test_rhi_capabilities \
  test_rhi_error_contract test_rhi_frame_lifecycle_contract
ctest --test-dir build-core-app-net --verbose --no-tests=error \
  -R '^(test_render_graph$|test_rhi_(dispatch|capabilities|error_contract|frame_lifecycle_contract)$)'
```

In the multiarch Ubuntu container, run the workflow dependency step, then the
same build targets and CTest regex against `build-arm64`.

Require native and cross 5/5, 44 dispatch checks, capabilities/error/frame/
render-graph summaries 59/7/5/22, and no skip.

- [ ] **Step 5: Append documentation and commit**

Record the five targets, 44 dispatch checks and case counts, exact 61 selection,
local anchors, headless/stub boundary, and unchanged failure semantics. Commit:

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md \
  docs/Implementation_Status.md docs/design/rhi_runtime_backend.md \
  docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-rhi-core.md
git commit -m "ci: run arm64 RHI core tests"
```

### Task 2: Final verification and remote proof

**Files:**
- Modify after evidence: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: Task 1's exact 61-test workflow.
- Produces: native, clean-container, independent-review, and exact-HEAD remote evidence.

- [ ] **Step 1: Run native full regression**

Run `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure` in
`build-core-app-net`. Require 455 tests, zero failures, and only four established
platform skips. Run `git diff --check`.

- [ ] **Step 2: Run the final clean-container workflow**

Parse the final YAML and execute every `lane-cross-aarch64-linux` run block in a
fresh Ubuntu 24.04 container with `:z` mount and the runner CMake prerequisite.
Require 61/61, 44 dispatch checks, 59/7/5/22 summaries, every previous summary/
contract/e2e marker, and exactly one existing ptrace setup skip.

- [ ] **Step 3: Review and push**

Request read-only review of exact selection, local anchors, generated QEMU
commands, native compatibility, failure semantics, and documentation. Fix adopted
findings test-first and rerun affected verification. Fetch/rebase if needed;
rerun affected tests when selected inputs change, then push without force.

- [ ] **Step 4: Assert remote evidence and finish the slice**

For the exact pushed HEAD, assert the arm64 job reports `0 tests failed out of
61`, the exact 61 passed-test names, all old/new summaries and contracts, every
existing e2e marker, and exactly one existing ptrace setup skip. Append run/job
URLs, commit, and review result to `docs/Implementation_Status.md`.

```bash
git add docs/Implementation_Status.md
git commit -m "docs: record arm64 RHI core CI results"
git push origin master
```

Finish with a clean worktree and `HEAD == origin/master`; leave the broader goal
open for other unimplemented capabilities.
