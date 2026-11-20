# arm64 QEMU HTTP and Update Suite Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the seven HTTP/online-update tests to the existing arm64 crash selection, producing one verified 14-test CTest CI lane.

**Architecture:** Reuse the configured cross emulator for executable targets and forward optional nested runners/host `CMAKE_NM` to CMake-driven tools and contracts. Native empty runners and all existing assertions remain unchanged.

**Tech Stack:** CMake/CTest, C11, OpenSSL, GCC aarch64 cross binutils, QEMU user emulation, GitHub Actions YAML, Python 3 + PyYAML, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_break_update`, `test_break_update_client`, `test_break_http`, `test_break_manifest_tool`, `test_break_update_target_contract`, `test_break_http_target_contract`, and `test_break_update_e2e`.
- Preserve every manifest/signature/Range/resume/TLS/export assertion and the explicit `linux-x86-64` fixture string.
- Emulate only target programs, never host CMake, shell utilities, or `nm`.
- No new job, binfmt registration, retries, output filtering, masked statuses, or full-suite/physical-device claims.
- Native empty runner values preserve direct execution.

---

### Task 1: Update-family nested runners and archive tools

**Files:**
- Modify: `engine/CMakeLists.txt:2821-2827,7128-7140,8174-8180,8217-8227`
- Modify: `engine/tests/test_break_manifest_tool.cmake:19-27`
- Modify: `engine/tests/test_break_update_target_contract.cmake:346-371`
- Modify: `engine/tests/test_break_update_e2e.cmake:23-31,61-110`
- Test: native and arm64 seven-test update/HTTP selection

**Interfaces:**
- Consumes: existing `CMAKE_CROSSCOMPILING_EMULATOR`, `CMAKE_NM`, and target paths.
- Produces: optional `TARGET_RUNNER` for manifest/update-e2e drivers and `UPDATE_CONTRACT_RUNNER` for the generated update link check; target-aware NM inputs.

- [ ] **Step 1: Preserve the RED evidence**

Retain the unmodified baseline: update 21/21, update client 44/44, HTTP 72/72; manifest and update e2e fail at direct target execution; update and HTTP contracts fail at `nm` discovery. Do not weaken any check.

- [ ] **Step 2: Forward CMake inputs**

Add after `VERIFY` in the manifest test registration and after `CLIENT` in update e2e:

```cmake
                "-DTARGET_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Add after `UPDATE_CONTRACT_CC`:

```cmake
                -DUPDATE_CONTRACT_NM=${CMAKE_NM}
                "-DUPDATE_CONTRACT_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Add after `ENGINE_CMAKE` in the HTTP contract registration:

```cmake
                -DNM=${CMAKE_NM}
```

- [ ] **Step 3: Prefix only target process launches**

In both manifest and update-e2e `run` helpers, use:

```cmake
    execute_process(COMMAND ${TARGET_RUNNER} ${ARGN} RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
```

All current calls in those helpers execute target `TOOL` or `VERIFY`. In update-e2e `client`, use:

```cmake
    execute_process(COMMAND ${TARGET_RUNNER} "${CLIENT}" "${root}" "https://localhost:${port}" "${ca}" "${PUB}" "${step}" ${ARGN}
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
```

At the start of update-e2e `start_server`, derive a quoted shell prefix:

```cmake
    set(target_runner_text "")
    foreach(target_runner_arg IN LISTS TARGET_RUNNER)
        string(REPLACE "'" "'\"'\"'" quoted_target_runner_arg "${target_runner_arg}")
        string(APPEND target_runner_text "'${quoted_target_runner_arg}' ")
    endforeach()
```

Prefix only the existing server shell command:

```cmake
        "${target_runner_text}'${SERVER}' --root '${root}' --cert '${CERT}' --key '${KEY}' --port 0 --print-port --log '${log}' ${extra} > '${port_file}' 2> '${WORK}/${tag}.err' & echo $! > '${pid_file}'"
```

In the update contract, change only the generated executable launch:

```cmake
execute_process(
    COMMAND ${UPDATE_CONTRACT_RUNNER} "${link_exe}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err)
```

- [ ] **Step 4: Verify native empty-runner compatibility**

From `build-core-app-net`:

```bash
cmake .
cmake --build . --parallel 6 --target test_break_update test_break_update_client test_break_http break_manifest_tool break_manifest_verify break_update_server break_update_e2e
ctest --verbose --no-tests=error -R '^(test_break_update|test_break_http|test_break_manifest_tool)'
```

Expected: exactly seven tests pass, including 21/44/72, `break_manifest_tool OK`, both contracts, and `break_update_e2e OK`.

- [ ] **Step 5: Prove the cross seven-test family before CI changes**

In the Ubuntu multiarch container with the existing emulator-configured `build-arm64`, build the seven targets from Step 4 and run:

```sh
ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^(test_break_update|test_break_http|test_break_manifest_tool)'
```

Use a fresh `docker.io/library/ubuntu:24.04`, `/workspace:z`, the workflow dependency block, and the runner-provided CMake prerequisite. Expected: seven tests pass with the same case/tool/e2e summaries. Investigate actual failures without filtering or skipping.

- [ ] **Step 6: Commit the verified harness**

```bash
git add engine/CMakeLists.txt engine/tests/test_break_manifest_tool.cmake \
  engine/tests/test_break_update_target_contract.cmake engine/tests/test_break_update_e2e.cmake
git commit -m "test: support emulated update tools"
```

### Task 2: Unified 14-test CI and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:155-230`
- Modify: `docs/Build_Guide.md:1417-1455`
- Modify: `docs/Implementation_Status.md:1-20` by prepending a dated section
- Modify: `docs/design/update_transport.md`
- Modify: `docs/cross_engine/missing_capabilities.md:280-285`
- Test: inline YAML and actual native CTest selection

**Interfaces:**
- Consumes: Task 1's seven additional targets and nested runner inputs.
- Produces: one 14-test crash/update/HTTP CTest step and bounded documentation.

- [ ] **Step 1: Run the failing CI contract**

```bash
python3 - <<'PY'
from pathlib import Path
import subprocess
import yaml

job = yaml.safe_load(Path('.github/workflows/ci.yml').read_text())['jobs']['lane-cross-aarch64-linux']
assert 'crash/update' in job['name']
steps = job['steps']
build = next(s for s in steps if s.get('name') == 'Build the arm64 targets')['run']
assert build.strip() == ('cmake --build build-arm64 --parallel --target '
    'break_crash engine test_break_crash test_break_crash_symbolize '
    'test_break_crash_cluster test_break_crash_upload_http '
    'break_crash_server break_crash_report break_crash_e2e '
    'test_break_update test_break_update_client test_break_http '
    'break_manifest_tool break_manifest_verify break_update_server break_update_e2e')
run = next(s for s in steps if s.get('name') == 'Run the crash and update tests under QEMU')['run']
assert "  -R '^(test_break_crash|test_break_update|test_break_http|test_break_manifest_tool)'" in run.splitlines()
assert 'timeout 300 ctest --test-dir build-arm64 --verbose --no-tests=error \\' in run.splitlines()
assert '|| true' not in run
regex = '^(test_break_crash|test_break_update|test_break_http|test_break_manifest_tool)'
listing = subprocess.check_output(['ctest', '--test-dir', 'build-core-app-net', '-N', '-R', regex], text=True)
selected = {line.split(': ', 1)[1] for line in listing.splitlines() if ': test_break_' in line}
assert selected == {
    'test_break_crash', 'test_break_crash_target_contract', 'test_break_crash_symbolize',
    'test_break_crash_cluster', 'test_break_crash_upload_http',
    'test_break_crash_server_target_contract', 'test_break_crash_e2e',
    'test_break_update', 'test_break_update_client', 'test_break_update_target_contract',
    'test_break_update_e2e', 'test_break_http', 'test_break_http_target_contract',
    'test_break_manifest_tool',
}
print('arm64 crash/update CI contract: PASS')
PY
```

Expected: FAIL on the old display name before any workflow edit.

- [ ] **Step 2: Apply the minimal workflow edit**

Set the display name to `Linux arm64 cross-build + QEMU crash/update tests (GCC)` and the step name to `Run the crash and update tests under QEMU`. Append the seven new targets to the existing build command in the contract's exact order. Replace only the CTest regex line with:

```yaml
            -R '^(test_break_crash|test_break_update|test_break_http|test_break_manifest_tool)'
```

Keep the emulator configuration, environment overrides, timeout, object checks, and job key unchanged. Update comments to include HTTP/update coverage.

- [ ] **Step 3: Verify contract GREEN and native full regression**

Rerun Step 1; expected: `arm64 crash/update CI contract: PASS`. From `build-core-app-net`, run:

```bash
cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure
```

Expected: 455 registered tests, zero failures, four established platform skips. Run `git diff --check`.

- [ ] **Step 4: Update evidence and limitations**

Document the seven additional tests and unified 14-name selection in the build guide and `docs/design/update_transport.md`. Include 21/44/72, manifest tool success, both contracts, and update e2e's real TLS/Range/resume/tamper/no-CA checks. Explain host cross `nm` and target-only runner prefixes.

Prepend `arm64 crash/update 十四项 CTest（2026-11-20）` to implementation status with the RED baseline, native/cross seven-test proof, CI RED/GREEN, and full native result; mark clean final and remote evidence pending until observed. Add a missing-capabilities entry distinguishing selected 14-test coverage from a full arm64 suite and retaining production update-service, HTTP/2, proxy, revocation/pinning, GPU, and physical-device limitations.

- [ ] **Step 5: Commit**

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md docs/Implementation_Status.md \
  docs/design/update_transport.md docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-update-suite.md
git commit -m "ci: run arm64 HTTP and update tests"
```

### Task 3: Final clean-room, review, and remote proof

**Files:**
- Verify: all Task 1/2 changes
- Modify after observed results: `docs/Implementation_Status.md`
- Create: no new source/test files

**Interfaces:**
- Consumes: committed 16-target, 14-test workflow.
- Produces: direct `master` integration and real remote evidence.

- [ ] **Step 1: Integrate and run final CI scripts**

Fetch `origin/master`; rebase if needed without discarding independent work and rerun affected verification. Execute every arm64 workflow `run` block in a fresh Ubuntu container with `/workspace:z`, runner CMake provisioning, the root `sudo` shell function, and `bash --noprofile --norc -e -o pipefail`. Require 16 targets, object checks, exactly 14 tests, all crash summaries, 21/44/72, both new contracts, manifest success, and update e2e success. Preserve the full log.

- [ ] **Step 2: Request read-only review and address findings**

Review the complete diff against the design/plan, focusing on target-only emulation, CMake list quoting, unchanged assertions, exact 14-name selection, and honest limits. Fix Critical/Important findings with failing tests first; verify minor fixes that are adopted.

- [ ] **Step 3: Push and require the remote arm64 job**

Push normally, find the CI run for the exact HEAD, and wait only for its arm64 job. Read the completed job log and assert `0 tests failed out of 14`, all previous crash summaries, 21/44/72, manifest/contract/e2e success, and expected optional skips. Do not treat container success as remote success.

- [ ] **Step 4: Record and audit**

Add run/job URLs, commit, 14-test result, and exact case summaries to implementation status; commit observed evidence as `docs: record arm64 update suite CI results` and push normally. Finish with a clean tree and `HEAD == origin/master`. Keep the broader goal open for other subsystems.
