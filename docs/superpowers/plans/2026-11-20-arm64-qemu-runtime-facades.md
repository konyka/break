# arm64 QEMU Runtime Facades Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add runtime facade, IO, and reload executables to the arm64 lane for an exact 38-test selection.

**Architecture:** Reuse the three generated executable-target QEMU commands. Change only the existing build target list and CTest regex; no driver, product, or test-source changes are needed.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_runtime_facade`, `test_runtime_io`, and `test_runtime_reload`; previous 35 + 3 = 38.
- Use the exact alternative `test_runtime_(facade|io|reload)$`.
- Preserve the previous 35 tests, runtime_core unit/contract, emulator settings, object checks, timeout, and failure propagation.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Do not claim full arm64 CTest, Lua/ECS, editor/rendering, Snowflake/QUIC, GPU, or physical-device coverage.
- Append documentation evidence without replacing existing history.

---

### Task 1: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-runtime-facades.md`

**Interfaces:**
- Consumes: existing executable-target emulation and 35-test workflow regex.
- Produces: exact 38-test arm64 selection with no driver API changes.

- [ ] **Step 1: Run the RED workflow contract**

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
targets = 'test_runtime_facade test_runtime_io test_runtime_reload'
assert build.rstrip().endswith('test_runtime_core ' + targets), 'missing runtime facade build targets'
assert 'test_runtime_(facade|io|reload)$' in run, 'missing exact runtime facade alternative'
pattern = re.search(r"-R '([^']+)'", run).group(1)
out = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', pattern,
], text=True)
selected = set(re.findall(r'Test\s+#\d+:\s+(\S+)', out))
runtime = {
    'test_runtime_core', 'test_runtime_core_target_contract',
    'test_runtime_facade', 'test_runtime_io', 'test_runtime_reload',
}
assert len(selected) == 38, f'expected 38, got {len(selected)}'
assert {n for n in selected if n.startswith('test_runtime_')} == runtime, selected
print('exact 38-test runtime facade selection contract passed')
PY
```

Expected before editing: FAIL at `missing runtime facade build targets`.
The unmodified native and cross baselines already pass 3/3 with 18/16/34 cases.

- [ ] **Step 2: Apply the minimal workflow edit**

Append exactly:

```text
test_runtime_facade test_runtime_io test_runtime_reload
```

Add this alternative inside the existing outer capture group:

```text
test_runtime_(facade|io|reload)$
```

Do not edit other workflow inputs.

- [ ] **Step 3: Run the GREEN selection contract**

Run Step 1 unchanged. Expected: `exact 38-test runtime facade selection contract
passed`. Also compare the selected names with the explicit previous 35 names
from `.github/workflows/ci.yml` plus the three new names; no other test may be
added or removed.

- [ ] **Step 4: Re-run focused native and cross tests**

```bash
cmake --build build-core-app-net --parallel 6 --target \
  test_runtime_facade test_runtime_io test_runtime_reload
ctest --test-dir build-core-app-net --verbose --no-tests=error \
  -R '^test_runtime_(facade|io|reload)$'
```

In the multiarch Ubuntu container, run the workflow dependency step, then:

```bash
cmake --build build-arm64 --parallel --target \
  test_runtime_facade test_runtime_io test_runtime_reload
ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^test_runtime_(facade|io|reload)$'
```

Require native and cross 3/3, facade 18/18, IO 16/16, reload 34/34, and no skip.

- [ ] **Step 5: Append documentation and commit**

Record the 18/16/34 coverage, exact 38 selection, direct emulation, unchanged
failure semantics, and exclusions. Commit:

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md \
  docs/Implementation_Status.md docs/design/runtime_overview.md \
  docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-runtime-facades.md
git commit -m "ci: run arm64 runtime facade tests"
```

### Task 2: Final verification and remote proof

**Files:**
- Modify after evidence: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: Task 1's exact 38-test workflow.
- Produces: native, clean-container, independent-review, and exact-HEAD remote evidence.

- [ ] **Step 1: Run native full regression**

Run `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure` in
`build-core-app-net`. Require 455 tests, zero failures, and only four established
platform skips. Run `git diff --check`.

- [ ] **Step 2: Run the final clean-container workflow**

Parse the final YAML and execute every `lane-cross-aarch64-linux` run block in a
fresh Ubuntu 24.04 container with `:z` mount and the runner CMake prerequisite.
Require 38/38, facade 18/18, IO 16/16, reload 34/34, every previous summary,
contract and e2e marker, and exactly one existing ptrace setup skip.

- [ ] **Step 3: Review and push**

Request read-only review of exact selection, generated QEMU commands, native
compatibility, failure semantics, and documentation. Fix adopted findings
test-first and rerun affected verification. Fetch/rebase if needed and push
without force.

- [ ] **Step 4: Assert remote evidence and finish the slice**

For the exact pushed HEAD, assert the arm64 job reports `0 tests failed out of
38`, the exact 38 passed-test names, all old/new summaries and contracts, every
existing e2e marker, and exactly one existing ptrace setup skip. Append run/job
URLs, commit, and review result to `docs/Implementation_Status.md`.

```bash
git add docs/Implementation_Status.md
git commit -m "docs: record arm64 runtime facade CI results"
git push origin master
```

Finish with a clean worktree and `HEAD == origin/master`; leave the broader goal
open for other unimplemented capabilities.
