# arm64 QEMU ECS Replication Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add ECS core, system scheduling, replication, and target-contract tests to the arm64 lane for an exact 42-test selection.

**Architecture:** Reuse three generated executable-target QEMU commands and one host-CMake source contract. Change only the build target list and locally anchored CTest alternatives.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_ecs`, `test_ecs_system`, `test_ecs_replication`, and `test_replication_target_contract`; previous 38 + 4 = 42.
- Use `test_ecs(_system|_replication)?$` and `test_replication_target_contract$` with local end anchors.
- Preserve all previous 38 tests, emulator settings, object checks, timeout, and failure propagation.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Do not claim full arm64 CTest, Lua/world streaming, editor/rendering, Snowflake/QUIC, GPU, or physical-device coverage.
- Append documentation evidence without replacing existing history.

---

### Task 1: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/ecs_snapshot_replication_aoi.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-ecs-replication.md`

**Interfaces:**
- Consumes: existing executable-target emulation and 38-test workflow regex.
- Produces: exact 42-test arm64 selection with no driver API changes.

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
targets = 'test_ecs test_ecs_system test_ecs_replication'
assert build.rstrip().endswith('test_runtime_reload ' + targets), 'missing ECS build targets'
assert 'test_ecs(_system|_replication)?$' in run, 'missing exact ECS alternative'
assert 'test_replication_target_contract$' in run, 'missing anchored replication contract'
pattern = re.search(r"-R '([^']+)'", run).group(1)
for name in ('test_ecs_system_extra', 'test_ecs_replication_extra',
             'test_replication_target_contract_extra'):
    assert not re.search(pattern, name), f'unexpected future-prefix selection: {name}'
out = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', pattern,
], text=True)
selected = set(re.findall(r'Test\s+#\d+:\s+(\S+)', out))
ecs = {
    'test_ecs', 'test_ecs_system', 'test_ecs_replication',
    'test_replication_target_contract',
}
assert len(selected) == 42, f'expected 42, got {len(selected)}'
assert ecs <= selected, 'missing ECS selections'
print('exact 42-test ECS selection and anchor contract passed')
PY
```

Expected before editing: FAIL at `missing ECS build targets`. The unmodified
native and cross baselines already pass 4/4 with 45/6/35 cases and the contract.

- [ ] **Step 2: Apply the minimal workflow edit**

Append exactly:

```text
test_ecs test_ecs_system test_ecs_replication
```

Add these alternatives inside the existing outer capture group:

```text
test_ecs(_system|_replication)?$
test_replication_target_contract$
```

Do not add a global end anchor or edit other workflow inputs.

- [ ] **Step 3: Run the GREEN selection contract**

Run Step 1 unchanged. Expected: `exact 42-test ECS selection and anchor contract
passed`. Compare the selected names with an explicit set containing the previous
38 and exactly these four; no other name may be added or removed.

- [ ] **Step 4: Re-run focused native and cross tests**

```bash
cmake --build build-core-app-net --parallel 6 --target \
  test_ecs test_ecs_system test_ecs_replication
ctest --test-dir build-core-app-net --verbose --no-tests=error \
  -R '^(test_ecs(_system|_replication)?$|test_replication_target_contract$)'
```

In the multiarch Ubuntu container, run the workflow dependency step, then:

```bash
cmake --build build-arm64 --parallel --target \
  test_ecs test_ecs_system test_ecs_replication
ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^(test_ecs(_system|_replication)?$|test_replication_target_contract$)'
```

Require native and cross 4/4, ECS 45/45, system 6/6, replication 35/35, formal
target contract success, and no skip.

- [ ] **Step 5: Append documentation and commit**

Record the 45/6/35 coverage, host-only contract, exact 42 selection, local
anchors, and unchanged failure semantics. Commit:

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md \
  docs/Implementation_Status.md docs/design/ecs_snapshot_replication_aoi.md \
  docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-ecs-replication.md
git commit -m "ci: run arm64 ECS replication tests"
```

### Task 2: Final verification and remote proof

**Files:**
- Modify after evidence: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: Task 1's exact 42-test workflow.
- Produces: native, clean-container, independent-review, and exact-HEAD remote evidence.

- [ ] **Step 1: Run native full regression**

Run `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure` in
`build-core-app-net`. Require 455 tests, zero failures, and only four established
platform skips. Run `git diff --check`.

- [ ] **Step 2: Run the final clean-container workflow**

Parse the final YAML and execute every `lane-cross-aarch64-linux` run block in a
fresh Ubuntu 24.04 container with `:z` mount and the runner CMake prerequisite.
Require 42/42, ECS 45/45, system 6/6, replication 35/35, the formal target
contract, every previous summary/contract/e2e marker, and exactly one existing
ptrace setup skip.

- [ ] **Step 3: Review and push**

Request read-only review of exact selection, local anchors, host/target boundary,
native compatibility, failure semantics, and documentation. Fix adopted findings
test-first and rerun affected verification. Fetch/rebase if needed and push
without force.

- [ ] **Step 4: Assert remote evidence and finish the slice**

For the exact pushed HEAD, assert the arm64 job reports `0 tests failed out of
42`, the exact 42 passed-test names, all old/new summaries and contracts, every
existing e2e marker, and exactly one existing ptrace setup skip. Append run/job
URLs, commit, and review result to `docs/Implementation_Status.md`.

```bash
git add docs/Implementation_Status.md
git commit -m "docs: record arm64 ECS replication CI results"
git push origin master
```

Finish with a clean worktree and `HEAD == origin/master`; leave the broader goal
open for other unimplemented capabilities.
