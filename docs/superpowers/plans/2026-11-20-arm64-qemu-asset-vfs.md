# arm64 QEMU Asset VFS Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add VFS, async loader, filewatch backend, and hot-reload tests to the arm64 lane for an exact 56-test selection.

**Architecture:** Reuse four generated executable-target QEMU commands. Change only the build target list and one locally anchored CTest alternative.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_vfs`, `test_async_loader`, `test_filewatch_backend`, and `test_hotreload`; previous 52 + 4 = 56.
- Use `test_(vfs|async_loader|filewatch_backend|hotreload)$` with a local end anchor.
- Preserve all previous 52 tests, emulator settings, object checks, timeout, and failure propagation.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Do not claim full arm64 CTest, material/scene textures, glTF/world streaming, editor/rendering, LuaJIT, Snowflake/QUIC, GPU, or physical-device coverage.
- Append documentation evidence without replacing existing history.

---

### Task 1: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/runtime_asset_streaming.md`
- Modify: `docs/design/runtime_hot_reload.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-asset-vfs.md`

**Interfaces:**
- Consumes: existing executable-target emulation and 52-test workflow regex.
- Produces: exact 56-test arm64 selection with no driver API changes.

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
targets = 'test_vfs test_async_loader test_filewatch_backend test_hotreload'
assert build.rstrip().endswith('test_break_lua_ecs_apply ' + targets), 'missing asset/VFS build targets'
alternative = 'test_(vfs|async_loader|filewatch_backend|hotreload)$'
assert alternative in run, 'missing exact asset/VFS alternative'
pattern = re.search(r"-R '([^']+)'", run).group(1)
for name in ('test_vfs_extra', 'test_async_loader_extra',
             'test_filewatch_backend_extra', 'test_hotreload_extra'):
    assert not re.search(pattern, name), f'unexpected selection: {name}'
out = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', pattern,
], text=True)
selected = set(re.findall(r'Test\s+#\d+:\s+(\S+)', out))
assets = {'test_vfs', 'test_async_loader', 'test_filewatch_backend', 'test_hotreload'}
assert len(selected) == 56, f'expected 56, got {len(selected)}'
assert assets <= selected, 'missing asset/VFS selections'
print('exact 56-test asset/VFS selection and anchor contract passed')
PY
```

Expected before editing: FAIL at `missing asset/VFS build targets`. The
unmodified native and cross baselines already pass 4/4 with 17/7/36/26 cases.

- [ ] **Step 2: Apply the minimal workflow edit**

Append exactly the four targets shown in Step 1 and add this alternative inside
the existing outer capture group:

```text
test_(vfs|async_loader|filewatch_backend|hotreload)$
```

Do not add a global end anchor or edit other workflow inputs.

- [ ] **Step 3: Run the GREEN selection contract**

Run Step 1 unchanged. Expected: `exact 56-test asset/VFS selection and anchor
contract passed`. Compare the selected names with an explicit set containing the
previous 52 and exactly these four; no other name may be added or removed.

- [ ] **Step 4: Re-run focused native and cross tests**

```bash
cmake --build build-core-app-net --parallel 6 --target \
  test_vfs test_async_loader test_filewatch_backend test_hotreload
ctest --test-dir build-core-app-net --verbose --no-tests=error \
  -R '^test_(vfs|async_loader|filewatch_backend|hotreload)$'
```

In the multiarch Ubuntu container, run the workflow dependency step, then the
same build targets and CTest regex against `build-arm64`.

Require native and cross 4/4; async loader/hotreload/VFS/filewatch summaries
17/7/36/26; no skip.

- [ ] **Step 5: Append documentation and commit**

Record the four targets and case counts, exact 56 selection, local anchor,
unchanged failure semantics, and exclusions. Commit:

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md \
  docs/Implementation_Status.md docs/design/runtime_asset_streaming.md \
  docs/design/runtime_hot_reload.md docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-asset-vfs.md
git commit -m "ci: run arm64 asset VFS tests"
```

### Task 2: Final verification and remote proof

**Files:**
- Modify after evidence: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: Task 1's exact 56-test workflow.
- Produces: native, clean-container, independent-review, and exact-HEAD remote evidence.

- [ ] **Step 1: Run native full regression**

Run `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure` in
`build-core-app-net`. Require 455 tests, zero failures, and only four established
platform skips. Run `git diff --check`.

- [ ] **Step 2: Run the final clean-container workflow**

Parse the final YAML and execute every `lane-cross-aarch64-linux` run block in a
fresh Ubuntu 24.04 container with `:z` mount and the runner CMake prerequisite.
Require 56/56, async loader/hotreload/VFS/filewatch 17/7/36/26, every previous
summary/contract/e2e marker, and exactly one existing ptrace setup skip.

- [ ] **Step 3: Review and push**

Request read-only review of exact selection, local anchor, generated QEMU
commands, native compatibility, failure semantics, and documentation. Fix adopted
findings test-first and rerun affected verification. Fetch/rebase if needed and
push without force.

- [ ] **Step 4: Assert remote evidence and finish the slice**

For the exact pushed HEAD, assert the arm64 job reports `0 tests failed out of
56`, the exact 56 passed-test names, all old/new summaries and contracts, every
existing e2e marker, and exactly one existing ptrace setup skip. Append run/job
URLs, commit, and review result to `docs/Implementation_Status.md`.

```bash
git add docs/Implementation_Status.md
git commit -m "docs: record arm64 asset VFS CI results"
git push origin master
```

Finish with a clean worktree and `HEAD == origin/master`; leave the broader goal
open for other unimplemented capabilities.
