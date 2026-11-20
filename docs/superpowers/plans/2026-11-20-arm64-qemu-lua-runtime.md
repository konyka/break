# arm64 QEMU Lua Runtime Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the nine Stage 3 Lua executable tests and their target contract to the arm64 lane for an exact 52-test selection.

**Architecture:** Reuse nine generated executable-target QEMU commands and one host-CMake source contract. Change only the build target list and two locally anchored CTest alternatives.

**Tech Stack:** CMake/CTest, vendored Lua, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly the ten `break_lua`-labelled tests; previous 42 + 10 = 52.
- Use `test_break_lua_(runtime|module|value|binding|handle|table|debug|ecs_apply|target_contract)$` and `test_break_kernel_lua$`.
- Do not select legacy `test_script_lua` or any future derived prefix.
- Preserve all previous 42 tests, emulator settings, object checks, timeout, and failure propagation.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Do not claim full arm64 CTest, LuaJIT, editor/rendering, world streaming, Snowflake/QUIC, GPU, or physical-device coverage.
- Append documentation evidence without replacing existing history.

---

### Task 1: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/lua_runtime.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-lua-runtime.md`

**Interfaces:**
- Consumes: existing executable-target emulation and 42-test workflow regex.
- Produces: exact 52-test arm64 selection with no driver API changes.

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
targets = ('test_break_lua_runtime test_break_lua_module test_break_lua_value '
           'test_break_lua_binding test_break_lua_handle test_break_lua_table '
           'test_break_lua_debug test_break_kernel_lua test_break_lua_ecs_apply')
assert build.rstrip().endswith('test_ecs_replication ' + targets), 'missing Lua build targets'
lua_alt = 'test_break_lua_(runtime|module|value|binding|handle|table|debug|ecs_apply|target_contract)$'
assert lua_alt in run, 'missing exact Lua alternative'
assert 'test_break_kernel_lua$' in run, 'missing anchored kernel Lua test'
pattern = re.search(r"-R '([^']+)'", run).group(1)
for name in ('test_break_lua_runtime_extra', 'test_break_lua_target_contract_extra',
             'test_break_kernel_lua_extra', 'test_script_lua'):
    assert not re.search(pattern, name), f'unexpected selection: {name}'
out = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', pattern,
], text=True)
selected = set(re.findall(r'Test\s+#\d+:\s+(\S+)', out))
lua = {
    'test_break_lua_runtime', 'test_break_lua_module', 'test_break_lua_value',
    'test_break_lua_binding', 'test_break_lua_handle', 'test_break_lua_table',
    'test_break_lua_debug', 'test_break_kernel_lua', 'test_break_lua_ecs_apply',
    'test_break_lua_target_contract',
}
assert len(selected) == 52, f'expected 52, got {len(selected)}'
assert lua <= selected, 'missing Lua selections'
print('exact 52-test Lua selection and anchor contract passed')
PY
```

Expected before editing: FAIL at `missing Lua build targets`. The unmodified
native and cross baselines already pass 10/10 with 126 cases and the contract.

- [ ] **Step 2: Apply the minimal workflow edit**

Append exactly the nine targets shown in Step 1 and add these alternatives inside
the existing outer capture group:

```text
test_break_lua_(runtime|module|value|binding|handle|table|debug|ecs_apply|target_contract)$
test_break_kernel_lua$
```

Do not add a global end anchor or edit other workflow inputs.

- [ ] **Step 3: Run the GREEN selection contract**

Run Step 1 unchanged. Expected: `exact 52-test Lua selection and anchor contract
passed`. Compare the selected names with an explicit set containing the previous
42 and exactly these ten; no other name may be added or removed.

- [ ] **Step 4: Re-run focused native and cross tests**

```bash
cmake --build build-core-app-net --parallel 6 --target \
  test_break_lua_runtime test_break_lua_module test_break_lua_value \
  test_break_lua_binding test_break_lua_handle test_break_lua_table \
  test_break_lua_debug test_break_kernel_lua test_break_lua_ecs_apply
ctest --test-dir build-core-app-net --verbose --no-tests=error \
  -R '^(test_break_lua_(runtime|module|value|binding|handle|table|debug|ecs_apply|target_contract)$|test_break_kernel_lua$)'
```

In the multiarch Ubuntu container, run the workflow dependency step, then the
same build targets and CTest regex against `build-arm64`.

Require native and cross 10/10; runtime/module/value/binding/handle/table/debug/
kernel/ECS-apply summaries 9/24/34/33/4/5/9/4/4; target contract success; no skip.

- [ ] **Step 5: Append documentation and commit**

Record the 126-case coverage, host-only contract, exact 52 selection, local
anchors, legacy compatibility exclusion, and unchanged failure semantics. Commit:

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md \
  docs/Implementation_Status.md docs/design/lua_runtime.md \
  docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-lua-runtime.md
git commit -m "ci: run arm64 Lua runtime tests"
```

### Task 2: Final verification and remote proof

**Files:**
- Modify after evidence: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: Task 1's exact 52-test workflow.
- Produces: native, clean-container, independent-review, and exact-HEAD remote evidence.

- [ ] **Step 1: Run native full regression**

Run `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure` in
`build-core-app-net`. Require 455 tests, zero failures, and only four established
platform skips. Run `git diff --check`.

- [ ] **Step 2: Run the final clean-container workflow**

Parse the final YAML and execute every `lane-cross-aarch64-linux` run block in a
fresh Ubuntu 24.04 container with `:z` mount and the runner CMake prerequisite.
Require 52/52, all nine Lua summaries, the Lua target contract, every previous
summary/contract/e2e marker, and exactly one existing ptrace setup skip.

- [ ] **Step 3: Review and push**

Request read-only review of exact selection, local anchors, host/target boundary,
native compatibility, failure semantics, and documentation. Fix adopted findings
test-first and rerun affected verification. Fetch/rebase if needed and push
without force.

- [ ] **Step 4: Assert remote evidence and finish the slice**

For the exact pushed HEAD, assert the arm64 job reports `0 tests failed out of
52`, the exact 52 passed-test names, all old/new summaries and contracts, every
existing e2e marker, and exactly one existing ptrace setup skip. Append run/job
URLs, commit, and review result to `docs/Implementation_Status.md`.

```bash
git add docs/Implementation_Status.md
git commit -m "docs: record arm64 Lua runtime CI results"
git push origin master
```

Finish with a clean worktree and `HEAD == origin/master`; leave the broader goal
open for other unimplemented capabilities.
