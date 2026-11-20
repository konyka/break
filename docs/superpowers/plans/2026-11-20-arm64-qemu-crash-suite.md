# arm64 QEMU Crash Suite Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Run all six `crash`-label tests plus the crash server archive contract on Linux arm64 with one explicit QEMU/CTest CI selection.

**Architecture:** Configure CMake's cross emulator for executable-target tests and forward the same optional runner to host-driven contracts/e2e scripts. Select target-aware `CMAKE_NM` for archive inspection; native builds retain empty runner prefixes and direct execution.

**Tech Stack:** CMake/CTest, C11 test fixtures, GCC aarch64 cross binutils, QEMU user emulation, GitHub Actions YAML, Python 3 + PyYAML, Podman Ubuntu 24.04.

## Global Constraints

- Select exactly `test_break_crash`, `test_break_crash_target_contract`, `test_break_crash_symbolize`, `test_break_crash_cluster`, `test_break_crash_upload_http`, `test_break_crash_server_target_contract`, and `test_break_crash_e2e`.
- Preserve all assertions, export lists, TLS checks, retry counts, and expected crash-signal handling.
- Native defaults remain direct execution and host `nm`.
- Do not install binfmt handlers, filter results, retry tests, mask CI statuses, or claim a full arm64 CTest/GPU/physical-device run.
- Record the root-only unwritable-statistics skip separately for local containers and the remote runner.

---

### Task 1: Cross-aware nested test drivers

**Files:**
- Modify: `engine/CMakeLists.txt:7177-7187,8238-8278`
- Modify: `engine/tests/test_break_crash_target_contract.cmake:394-419`
- Modify: `engine/tests/test_break_crash_e2e.cmake:27-86,203-209,250-256,386`
- Test: native and arm64 `ctest -R '^test_break_crash'`

**Interfaces:**
- Consumes: existing `CMAKE_NM`, `CMAKE_CROSSCOMPILING_EMULATOR`, configured cross compiler, and target executable paths.
- Produces: optional `CRASH_CONTRACT_RUNNER` and `TARGET_RUNNER` CMake lists; `CRASH_CONTRACT_NM`/`NM` tool overrides; unchanged native behavior.

- [ ] **Step 1: Preserve the observed RED baseline**

Use the already recorded unmodified diagnostic: cluster 26/26, upload 8/8, both contracts fail at their `nm` gates, and e2e fails when the host shell directly interprets the arm64 client. Do not change assertions or install generic host binutils to conceal these failures.

- [ ] **Step 2: Forward tools and runners in CMake test registrations**

Add to `test_break_crash_target_contract` after `CRASH_CONTRACT_CC`:

```cmake
                -DCRASH_CONTRACT_NM=${CMAKE_NM}
                "-DCRASH_CONTRACT_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Add to `test_break_crash_server_target_contract` after `ENGINE_CMAKE`:

```cmake
                -DNM=${CMAKE_NM}
```

Add to `test_break_crash_e2e` after `CLIENT`:

```cmake
                "-DTARGET_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Quoted runner definitions preserve semicolon lists as one argument. Empty native values remain valid.

- [ ] **Step 3: Prefix the generated contract executable**

In `test_break_crash_target_contract.cmake`, change only the final execution:

```cmake
execute_process(
    COMMAND ${CRASH_CONTRACT_RUNNER} "${link_exe}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err)
```

The compiler, archive checks, link command, and return-code checks stay unchanged.

- [ ] **Step 4: Prefix e2e client/report/server target processes**

Use these exact command forms.

`client`:

```cmake
    execute_process(COMMAND ${TARGET_RUNNER} "${CLIENT}" ${ARGN}
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
```

`report`:

```cmake
    execute_process(COMMAND ${TARGET_RUNNER} "${REPORT}" "${stats}" ${ARGN}
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
```

At the beginning of `start_server`, derive a shell prefix from the CMake list:

```cmake
    set(target_runner_text "")
    if(TARGET_RUNNER)
        string(REPLACE ";" " " target_runner_text "${TARGET_RUNNER}")
        string(APPEND target_runner_text " ")
    endif()
```

Use it only in the existing server launch:

```cmake
        "${target_runner_text}'${SERVER}' --symbols '${WORK}/symbols' --stats '${stats}' --cert '${CERT}' --key '${KEY}' --port 0 --print-port --log '${log}' ${extra} > '${port_file}' 2> '${WORK}/${tag}.err' & echo $! > '${pid_file}'"
```

Change the six direct client `run` calls to these exact forms:

```cmake
run(TRUE ${TARGET_RUNNER} "${CLIENT}" forge "${WORK}/signal0.bin" "${BUILD}" 0)
run(TRUE ${TARGET_RUNNER} "${CLIENT}" forge "${WORK}/signal99.bin" "${BUILD}" 99)
run(TRUE ${TARGET_RUNNER} "${CLIENT}" forge "${WORK}/unreg.bin" "unreg-build" 11)
run(TRUE ${TARGET_RUNNER} "${CLIENT}" rebuild "${SENT_REC}" "${WORK}/old_again.bin" "${BUILD}")
run(TRUE ${TARGET_RUNNER} "${CLIENT}" rebuild "${SENT_REC}" "${WORK}/later.bin" "${LATER}")
run(TRUE ${TARGET_RUNNER} "${CLIENT}" spool-put "${WORK}/spool10" "${WORK}/unreg.bin")
```

Do not prefix host CMake, shell utilities, or file operations.

- [ ] **Step 5: Verify native defaults across all seven tests**

Run from `build-core-app-net`:

```bash
cmake .
cmake --build . --parallel 6 --target break_crash engine test_break_crash test_break_crash_symbolize test_break_crash_cluster test_break_crash_upload_http break_crash_server break_crash_report break_crash_e2e
ctest --verbose --no-tests=error -R '^test_break_crash'
```

Expected: exactly seven tests pass; 37/45/26/8 case summaries remain successful, both contracts pass, and e2e prints `break_crash_e2e OK`. Native host LLVM subchecks continue to run.

- [ ] **Step 6: Prove the intended cross configuration before editing CI**

In a fresh Ubuntu container, install the existing workflow dependencies and runner-provided CMake, then execute this exact configure/build/test sequence from `/workspace`:

```sh
export AARCH64_SYSROOT=/
export PKG_CONFIG_LIBDIR=/usr/lib/aarch64-linux-gnu/pkgconfig:/usr/aarch64-linux-gnu/lib/pkgconfig:/usr/share/pkgconfig
cmake -S engine -B build-arm64 -G Ninja \
  --toolchain /workspace/engine/toolchain-aarch64-linux.cmake \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=opengl \
  '-DCMAKE_CROSSCOMPILING_EMULATOR=/usr/bin/qemu-aarch64;-L;/'
cmake --build build-arm64 --parallel --target break_crash engine test_break_crash test_break_crash_symbolize test_break_crash_cluster test_break_crash_upload_http break_crash_server break_crash_report break_crash_e2e
BREAK_TEST_NM=aarch64-linux-gnu-nm \
BREAK_TEST_READELF=aarch64-linux-gnu-readelf \
BREAK_TEST_STRIP=aarch64-linux-gnu-strip \
BREAK_TEST_RUNNER='qemu-aarch64 -L /' \
timeout 300 ctest --test-dir build-arm64 --verbose --no-tests=error -R '^test_break_crash'
```

Mount the repository with `:z`, define `sudo() { command "$@"; }`, and use `bash --noprofile --norc -e -o pipefail`. Provision CMake with `apt-get update && apt-get install -y --no-install-recommends cmake` before the original dependency block. Expected: exactly seven tests pass. Preserve all case summaries and record that a root container prints the existing case-11 skip; investigate any other failure without weakening checks.

- [ ] **Step 7: Commit the independently verified harness**

```bash
git add engine/CMakeLists.txt engine/tests/test_break_crash_target_contract.cmake engine/tests/test_break_crash_e2e.cmake
git commit -m "test: support emulated nested crash tests"
```

### Task 2: Unified CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:193-232`
- Modify: `docs/Build_Guide.md:1417-1450`
- Modify: `docs/Implementation_Status.md:1-18` by prepending a dated section
- Modify: `docs/design/crash_symbolization.md:116-145`
- Modify: `docs/cross_engine/missing_capabilities.md:280-284`
- Test: inline YAML + real native CTest selection contract

**Interfaces:**
- Consumes: Task 1's optional runner/tool inputs and nine build targets.
- Produces: one seven-test CTest CI command and documentation that distinguishes crash-family coverage from a full arm64 suite.

- [ ] **Step 1: Run the failing CI contract**

```bash
python3 - <<'PY'
from pathlib import Path
import subprocess
import yaml

job = yaml.safe_load(Path('.github/workflows/ci.yml').read_text())['jobs']['lane-cross-aarch64-linux']
steps = job['steps']
configure = next(s for s in steps if s.get('name') == 'Configure')['run']
assert "'-DCMAKE_CROSSCOMPILING_EMULATOR=/usr/bin/qemu-aarch64;-L;/'" in configure
build = next(s for s in steps if s.get('name') == 'Build the arm64 targets')['run']
assert build.strip() == ('cmake --build build-arm64 --parallel --target '
    'break_crash engine test_break_crash test_break_crash_symbolize '
    'test_break_crash_cluster test_break_crash_upload_http '
    'break_crash_server break_crash_report break_crash_e2e')
run = next(s for s in steps if s.get('name') == 'Run the crash tests under QEMU')['run']
assert run.strip().splitlines() == [
    'qemu-aarch64 --version',
    'BREAK_TEST_NM=aarch64-linux-gnu-nm \\',
    'BREAK_TEST_READELF=aarch64-linux-gnu-readelf \\',
    'BREAK_TEST_STRIP=aarch64-linux-gnu-strip \\',
    "BREAK_TEST_RUNNER='qemu-aarch64 -L /' \\",
    'timeout 300 ctest --test-dir build-arm64 --verbose --no-tests=error \\',
    "  -R '^test_break_crash'",
]
assert '|| true' not in run
listing = subprocess.check_output([
    'ctest', '--test-dir', 'build-core-app-net', '-N', '-R', '^test_break_crash'
], text=True)
selected = {line.split(': ', 1)[1] for line in listing.splitlines()
            if ': test_break_crash' in line}
assert selected == {
    'test_break_crash', 'test_break_crash_target_contract',
    'test_break_crash_symbolize', 'test_break_crash_cluster',
    'test_break_crash_upload_http', 'test_break_crash_server_target_contract',
    'test_break_crash_e2e',
}
print('arm64 complete crash CI contract: PASS')
PY
```

Expected: FAIL on the missing emulator configuration before any workflow edit.

- [ ] **Step 2: Apply the minimal workflow change**

Append to Configure, retaining the existing OpenGL argument and adding its continuation slash:

```yaml
            -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=opengl \
            '-DCMAKE_CROSSCOMPILING_EMULATOR=/usr/bin/qemu-aarch64;-L;/'
```

Use this exact build command:

```yaml
          cmake --build build-arm64 --parallel --target break_crash engine test_break_crash test_break_crash_symbolize test_break_crash_cluster test_break_crash_upload_http break_crash_server break_crash_report break_crash_e2e
```

Replace the QEMU step's old direct test commands with:

```yaml
          qemu-aarch64 --version
          BREAK_TEST_NM=aarch64-linux-gnu-nm \
          BREAK_TEST_READELF=aarch64-linux-gnu-readelf \
          BREAK_TEST_STRIP=aarch64-linux-gnu-strip \
          BREAK_TEST_RUNNER='qemu-aarch64 -L /' \
          timeout 300 ctest --test-dir build-arm64 --verbose --no-tests=error \
            -R '^test_break_crash'
```

Update the explanatory comment to say the complete crash family runs; do not change the job key, packages, sysroot, or object checks.

- [ ] **Step 3: Verify contract GREEN and the full native suite**

Rerun Step 1's complete contract; expected: `arm64 complete crash CI contract: PASS`. Then run from `build-core-app-net`:

```bash
cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure
```

Expected: 455 registered tests, zero failures, four established platform skips. Run `git diff --check`; expected: no errors.

- [ ] **Step 4: Update current evidence and boundaries**

Document the seven-test selection, nine targets, CMake emulator, target-aware contract `nm`, and nested e2e runner in `docs/Build_Guide.md` and `docs/design/crash_symbolization.md`. Include 37/45/26/8 summaries, both contracts, and e2e's 11 scenarios. State the actual root-container case-11 skip and leave remote non-root behavior pending until observed.

Prepend `arm64 crash 七项 CTest（2026-11-20）` to `docs/Implementation_Status.md`, recording the RED baseline, native default compatibility, cross seven-test result, YAML RED/GREEN, and native full-suite result. Add a dated missing-capabilities entry: the crash label and server contract now run under QEMU, while a full arm64 suite, GPU, physical hardware, minidump/PE, Windows symbolization, and production deployment remain open.

- [ ] **Step 5: Review and commit**

Check that all seven tests are selected and no direct test was dropped without appearing in CTest. Stage only this slice:

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md docs/Implementation_Status.md \
  docs/design/crash_symbolization.md docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-crash-suite.md
git commit -m "ci: run the complete crash suite on arm64"
```

### Task 3: Final integration and remote proof

**Files:**
- Verify: all Task 1/2 changes
- Modify after observed results: `docs/Implementation_Status.md`
- Create: no new source/test files

**Interfaces:**
- Consumes: committed unified seven-test workflow.
- Produces: final clean-container and remote evidence on `master`.

- [ ] **Step 1: Integrate remote changes**

```bash
git fetch origin master
git status --short
git log --oneline --decorate -5
```

Rebase if necessary without discarding independent changes. Repeat affected native/cross/contract verification if tested inputs change; never force-push.

- [ ] **Step 2: Run final CI scripts in a clean container**

Extract all `run` blocks from `lane-cross-aarch64-linux` with PyYAML and execute them in order in a new `docker.io/library/ubuntu:24.04` container. Mount `/workspace:z`, set `GITHUB_WORKSPACE=/workspace`, provision the runner's CMake prerequisite, define the root `sudo` shell function, and use `bash --noprofile --norc -e -o pipefail`. Run in the background with complete logs. Require all nine targets, object checks, exactly seven selected tests, 37/45/26/8 summaries, both contract success messages, and e2e success. Record the root case-11 skip and remove only generated QEMU core files.

- [ ] **Step 3: Push and require the real arm64 job**

```bash
git push origin master
gh api --method GET repos/konyka/break/actions/runs \
  -f head_sha="$(git rev-parse HEAD)" -f per_page=20 \
  --jq '.workflow_runs[] | select(.name == "CI") | {id, head_sha, status, conclusion, html_url}'
```

Find the arm64 job and wait for that job only. Require Configure, Build, object checks, and the QEMU CTest step to succeed. Read its log using `gh api --allow-escape-sequences repos/konyka/break/actions/jobs/<job-id>/logs`; require `7/7` CTest success and the actual 37/45/26/8 summaries. Check whether the remote non-root runner executes e2e case 11 rather than printing the root skip.

- [ ] **Step 4: Record evidence and audit**

Add actual run/job URLs, commit, seven-test result, case summaries, and privilege-dependent e2e behavior to `docs/Implementation_Status.md`. Commit only observed evidence as `docs: record arm64 crash suite CI results` and push normally. Finish with a clean tree and `HEAD == origin/master`; keep the broader goal open for non-crash capabilities.
