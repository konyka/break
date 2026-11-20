# arm64 QEMU Crash Test Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Extend the existing Linux arm64 CI lane to execute the 37 `test_break_crash` cases under QEMU without weakening its compile/link checks.

**Architecture:** Keep `lane-cross-aarch64-linux` and its Ubuntu multiarch toolchain unchanged apart from installing `qemu-user` and building the existing crash-test target. Run the target binary once with the target filesystem rooted at `/`; retain native x86-64 testing as the broader regression suite.

**Tech Stack:** GitHub Actions YAML, Ubuntu 24.04 multiarch, CMake/Ninja, GCC aarch64 cross toolchain, QEMU user emulation, Python 3 + PyYAML for the CI contract check, Podman for local clean-room verification.

## Global Constraints

- Keep the job key `lane-cross-aarch64-linux` stable.
- Continue to build `break_crash` and `engine`; add `test_break_crash`.
- Run `timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash` exactly once, with no retry, output filtering, or masked exit status.
- Do not add an independent CI job, a full arm64 `ctest`, GPU execution, or a physical-device claim.
- Do not include `test_break_crash_symbolize` in this slice: its target `nm`/`strip` and nested fixture execution require separate work.
- Preserve existing documentation; append current evidence or revise only statements superseded by this change.
- Validate the clean container run, the complete native suite, and the remote arm64 job before reporting this slice complete.

---

### Task 1: CI execution and evidence-boundary documentation

**Files:**
- Modify: `.github/workflows/ci.yml:155-218`
- Modify: `docs/Build_Guide.md:1417-1435`
- Modify: `docs/Implementation_Status.md:1-7` by prepending a new dated section
- Modify: `docs/design/crash_symbolization.md:87-123`
- Modify: `docs/cross_engine/missing_capabilities.md:280`
- Modify: `docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md:35-46,65-77`
- Test: inline Python YAML contract in Steps 1-2 and 4 (no new repository test file)

**Interfaces:**
- Consumes: existing `lane-cross-aarch64-linux` job, the `test_break_crash` CMake target, and Ubuntu's `qemu-aarch64` executable from `qemu-user`.
- Produces: a CI step named `Run the crash tests under QEMU`, with the exact QEMU command in Global Constraints; documentation distinguishes compile/link, emulated runtime, and unverified boundaries.

- [ ] **Step 1: Run the failing CI contract**

Run this from the repository root:

```bash
python3 - <<'PY'
from pathlib import Path
import re
import yaml

workflow = yaml.safe_load(Path('.github/workflows/ci.yml').read_text())
job = workflow['jobs']['lane-cross-aarch64-linux']
assert 'QEMU' in job['name']
steps = job['steps']
install = next(s for s in steps if s.get('name') == 'Install the host and arm64 build dependencies')
assert re.search(r'(?m)(?:^|\s)qemu-user(?:\s|$)', install['run'])
build = next(s for s in steps if s.get('name') == 'Build the arm64 targets')
assert build['run'].strip() == (
    'cmake --build build-arm64 --parallel '
    '--target break_crash engine test_break_crash'
)
architecture = next(s for s in steps if s.get('name') == 'Confirm the objects really are arm64')
index = steps.index(architecture)
run = steps[index + 1]
assert run['name'] == 'Run the crash tests under QEMU'
assert run['run'].strip().splitlines() == [
    'qemu-aarch64 --version',
    'timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash',
]
scripts = '\n'.join(s.get('run', '') for s in steps)
assert 'test_break_crash_symbolize' not in scripts
print('arm64 QEMU CI contract: PASS')
PY
```

Expected: FAIL at `assert 'QEMU' in job['name']`, because the current lane is build-only.

- [ ] **Step 2: Capture the RED result**

Confirm the failure is an assertion from the contract, not missing PyYAML or malformed existing YAML. The exit status must be nonzero and the exception must identify the missing QEMU display-name condition; no product or workflow edit is made before this result.

- [ ] **Step 3: Make the minimal workflow change**

Replace the obsolete build-only comment and display name with:

```yaml
  # Cross-compile the architecture-specific code, then exercise the crash
  # handler on the target architecture with QEMU user emulation. The native
  # suite remains the broader regression net; this is not a full arm64 ctest.
  lane-cross-aarch64-linux:
    name: Linux arm64 cross-build + QEMU crash tests (GCC)
```

Add `qemu-user` to the final continuation line of the install package list:

```yaml
            libgl-dev:arm64 libegl-dev:arm64 libopengl-dev:arm64 \
            libssl-dev:arm64 qemu-user
```

Change the stale configure comment `against real arm64 packages; run nothing.` to `against real arm64 packages; graphics remain compile-only.` Keep the configure command unchanged.

Build all three targets:

```yaml
          cmake --build build-arm64 --parallel --target break_crash engine test_break_crash
```

Immediately after the existing object-architecture step, add:

```yaml
      - name: Run the crash tests under QEMU
        run: |
          qemu-aarch64 --version
          timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash
```

- [ ] **Step 4: Run the contract to verify GREEN**

Run: the complete Python contract from Step 1.

Expected: `arm64 QEMU CI contract: PASS` and exit status 0. This checks the unchanged job key and object-check position, all existing build targets, the new package, and the unmasked QEMU command.

- [ ] **Step 5: Update the build instructions**

Change the section heading to `### 1.5 Linux arm64 交叉构建与 QEMU 崩溃测试`. Preserve the toolchain-path and sysroot warnings. In its explanation and command block, include:

```sh
cmake --build build-arm64 --parallel --target break_crash engine test_break_crash
qemu-aarch64 --version
timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash
```

State that Ubuntu's `qemu-user` package supplies the emulator, `-L /` selects the multiarch target libraries, the 37 cases include real SIGSEGV/SIGABRT capture, and this is neither a full arm64 `ctest` nor OpenGL runtime evidence. Replace the claim that no arm64 test can be run on an x86-64 host with the distinction between direct execution and explicit QEMU execution.

- [ ] **Step 6: Update implementation and crash evidence**

Prepend `## arm64 QEMU 崩溃测试（2026-11-20）` to `docs/Implementation_Status.md`, retaining the prior arm64 section as history. Record the exact target list and command, the RED/GREEN YAML contract, and the already-observed clean-container 37/37 result. State that native-suite and remote-job verification are pending until Steps 8 and Task 2 report their actual results. Explicitly retain these limits: no full arm64 `ctest`, no arm64 `test_break_crash_symbolize`, no GPU or physical-device evidence.

In `docs/design/crash_symbolization.md` §6, add the QEMU command and identify which record/signal/context/recovery/redaction behaviors are exercised. In §7, replace only the superseded statement that no arm64 test executed: point to §6 for the 37-case emulated run and leave the symbolizer suite and physical hardware unverified. Do not claim DWARF CFI or macOS client crash-record validation.

- [ ] **Step 7: Close the stale gap statements**

Append a dated entry to `docs/cross_engine/missing_capabilities.md` naming `lane-cross-aarch64-linux`, the 37 tests, and the still-open arm64 symbolizer and physical-device work. Adjust the prior arm64 entry so it points to this follow-up instead of continuing to request a QEMU crash lane.

In the existing build-lane design, change the OpenGL comment to compile/link-only rather than “runs none of it”; describe the Build Guide as covering the later QEMU addition; narrow Out of scope to other arm64 suites, Vulkan cross-compilation, other arm64 operating systems, and OpenGL runtime. Link `2026-11-20-arm64-qemu-crash-test-design.md` as the follow-up evidence instead of retaining the blanket statement that no arm64 binary was executed.

- [ ] **Step 8: Verify native regression behavior**

Run the existing native build directory's standard commands:

```bash
cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure
```

Working directory: `build-core-app-net`.

Expected: configuration and build succeed; all 455 tests pass, with only the four established platform skips. If integration changes the registered test count, report the actual count and investigate every failure rather than editing the expectation to conceal a failure.

Also run:

```bash
git diff --check
```

Expected: no whitespace errors.

- [ ] **Step 9: Review and commit the implementation**

Inspect `git diff -- .github/workflows/ci.yml docs/Build_Guide.md docs/Implementation_Status.md docs/design/crash_symbolization.md docs/cross_engine/missing_capabilities.md docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md` and `git status --short`. Ensure only this slice and its plan are included, no result is claimed before it was observed, and the RED assertion is not bypassed.

```bash
git add docs/superpowers/plans/2026-11-20-arm64-qemu-crash-test.md \
  .github/workflows/ci.yml docs/Build_Guide.md docs/Implementation_Status.md \
  docs/design/crash_symbolization.md docs/cross_engine/missing_capabilities.md \
  docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md
git commit -m "ci: run arm64 crash tests under QEMU"
```

### Task 2: Clean-room integration and remote verification

**Files:**
- Verify: `.github/workflows/ci.yml`
- Verify: all documentation committed in Task 1
- Create: no repository files

**Interfaces:**
- Consumes: the committed Task 1 workflow and the clean `ubuntu:24.04` image already available locally.
- Produces: clean-room build and 37-case runtime evidence, a pushed `master` commit, and a successful remote arm64 job URL.

- [ ] **Step 1: Execute the workflow scripts in a clean Ubuntu container**

Use Python + PyYAML on the host to extract every `run` block from `lane-cross-aarch64-linux` in order. Start one fresh `docker.io/library/ubuntu:24.04` container, mount the repository at `/workspace` with `:z`, set `GITHUB_WORKSPACE=/workspace`, and execute the original run scripts sequentially using `bash --noprofile --norc -e -o pipefail`. Before those run blocks, provision CMake with `apt-get update && apt-get install -y --no-install-recommends cmake`: the GitHub-hosted runner supplies it, while the clean base image does not. Since the container runs as root and does not need a privilege escalation package, define `sudo() { command "$@"; }` in the execution shell; do not otherwise edit, skip, retry, or filter a CI step.

Run the orchestration as a background command because dependency installation and the full target build take several minutes. Preserve its complete log and exit status. Expected: dependency installation, configure, all three targets, object checks, and `Run the crash tests under QEMU` succeed; the test binary prints 37 passing cases and exits 0.

- [ ] **Step 2: Integrate any remote changes before pushing**

```bash
git fetch origin master
git status --short
git log --oneline --decorate -5
```

If `origin/master` advanced, inspect its changed files and rebase the local commits onto it. If any rebase changes a tested source or workflow file, rerun the affected contract, native suite, and clean-room steps before pushing. Resolve conflicts without discarding either side's independent behavior.

- [ ] **Step 3: Push the verified commits**

```bash
git push origin master
```

Expected: the design, plan, and implementation commits are on the remote main branch; no PR is created.

- [ ] **Step 4: Require the real remote lane to pass**

Find the run for the pushed commit and its arm64 job:

```bash
gh run list --branch master --limit 10
gh run view <run-id> --json jobs,headSha,status,conclusion,url
```

Wait for the actual run and inspect failed logs with `gh run view <run-id> --log-failed` if necessary. Require `Install the host and arm64 build dependencies`, `Build the arm64 targets`, `Confirm the objects really are arm64`, and `Run the crash tests under QEMU` to report success on GitHub. Record the run/job URL and actual result in `docs/Implementation_Status.md` if they were not already available for Task 1; commit and push that documentation-only follow-up.

- [ ] **Step 5: Audit this slice without closing the broader objective**

Confirm the workspace is clean, `HEAD` equals `origin/master`, the remote QEMU step really passed, and the documentation does not equate emulation with full-suite, symbolizer, GPU, or physical-device coverage. Report the delivered evidence and the remaining symbolizer boundary. Keep the broader active goal open for its remaining independent capabilities.
