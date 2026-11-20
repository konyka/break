# arm64 QEMU Security Suite Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add six security/cryptography tests to the arm64 lane, producing a unified 20-test selection with one explicitly documented QEMU ptrace-setup skip.

**Architecture:** Reuse executable-target emulation and add optional nested runners/NM inputs to keygen and archive contracts. Native ptrace-positive behavior remains strict; only the traced setup's observed QEMU `ENOSYS`/exit-90 path may skip.

**Tech Stack:** CMake/CTest, C11, OpenSSL, ptrace, GCC aarch64 cross binutils, QEMU user emulation, GitHub Actions YAML, Python 3 + PyYAML, Podman Ubuntu 24.04.

## Global Constraints

- Add crypto, crypto contract, keygen, integrity, authority, and authority contract; exact current total 20 tests.
- Preserve all keyring permissions/limits/atomicity/concurrency, exact exports, trust boundaries, and native ptrace assertions.
- Skip only exit 90 from `PTRACE_TRACEME` when `BREAK_TEST_QEMU_USER` is exactly `1`; exit 91 and all product-result failures remain red.
- Emulate only target programs, never host shell/CMake/nm.
- No hidden skip, retries, filtering, binfmt, status masking, or full-suite/physical-device claims.

---

### Task 1: Security drivers and explicit emulator boundary

**Files:**
- Modify: `engine/CMakeLists.txt:2835-2843,7075-7086,8305-8313`
- Modify: `engine/tests/test_break_keygen.cmake:12-27,164-198`
- Modify: `engine/tests/test_break_crypto_target_contract.cmake:203-225`
- Modify: `engine/tests/test_break_integrity.c:99-117`
- Test: native and cross six-test security selection

**Interfaces:**
- Consumes: existing emulator, `CMAKE_NM`, keygen path, contract compiler/archive paths.
- Produces: keygen `TARGET_RUNNER`, crypto `CRYPTO_CONTRACT_RUNNER`/NM, authority NM, and one strict QEMU-only setup skip.

- [ ] **Step 1: Preserve RED evidence**

Retain crypto 20/20, authority 14/14, integrity 7/8, keygen direct-exec failure, two contract NM failures, and the target trace `PTRACE_TRACEME = -1 ENOSYS`, child exit 90. Do not alter the product debugger check.

- [ ] **Step 2: Forward CMake inputs**

Add after `KEYGEN` in keygen registration:

```cmake
                "-DTARGET_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Add after `CRYPTO_CONTRACT_CC`:

```cmake
                -DCRYPTO_CONTRACT_NM=${CMAKE_NM}
                "-DCRYPTO_CONTRACT_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Add after `ENGINE_CMAKE` in authority contract registration:

```cmake
                -DNM=${CMAKE_NM}
```

- [ ] **Step 3: Prefix all keygen target launches**

After `set(RING ...)`, create a safely quoted shell prefix:

```cmake
set(target_runner_text "")
foreach(target_runner_arg IN LISTS TARGET_RUNNER)
    string(REPLACE "'" "'\"'\"'" quoted_target_runner_arg "${target_runner_arg}")
    string(APPEND target_runner_text "'${quoted_target_runner_arg}' ")
endforeach()
```

Use direct CMake list expansion in the helper:

```cmake
    execute_process(COMMAND ${TARGET_RUNNER} "${KEYGEN}" ${ARGN}
                    RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
```

In the RLIMIT shell command, use `exec ${target_runner_text}'${KEYGEN}' ...`; in the concurrent loop, replace each direct `'${KEYGEN}'` launch with `${target_runner_text}'${KEYGEN}'`. Host shell utilities stay native.

- [ ] **Step 4: Prefix only the crypto generated executable**

```cmake
execute_process(
    COMMAND ${CRYPTO_CONTRACT_RUNNER} "${link_exe}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err)
```

- [ ] **Step 5: Add the exact QEMU-only setup skip**

Immediately after the first successful `waitpid` in the traced test, before `WIFSTOPPED` assertions:

```c
        if (WIFEXITED(status) && WEXITSTATUS(status) == 90) {
            const char *qemu_user = getenv("BREAK_TEST_QEMU_USER");
            if (qemu_user != NULL && strcmp(qemu_user, "1") == 0) {
                printf("skipped (QEMU user has no PTRACE_TRACEME) ");
                return;
            }
        }
```

All other statuses continue into existing assertions. Native and exit-91 behavior remain unchanged.

- [ ] **Step 6: Verify native strict behavior**

From `build-core-app-net`:

```bash
cmake .
cmake --build . --parallel 6 --target test_break_crypto test_break_integrity test_break_authority break_keygen
ctest --verbose --no-tests=error -R '^(test_break_crypto|test_break_keygen|test_break_integrity|test_break_authority)'
```

Expected: six tests pass, crypto 20/20, integrity 8/8 with no skip text, authority 14/14, keygen and both contracts succeed. RLIMIT/concurrency and ptrace-positive setup execute natively.

- [ ] **Step 7: Prove cross behavior before CI changes**

Build the same four targets in the emulator-configured Ubuntu cross tree and run:

```sh
BREAK_TEST_QEMU_USER=1 \
ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^(test_break_crypto|test_break_keygen|test_break_integrity|test_break_authority)'
```

Expected: six tests pass; crypto 20/20, authority 14/14, integrity 8/8 with exactly one `QEMU user has no PTRACE_TRACEME` setup skip, keygen and contracts succeed. No exit-91 skip is permitted.

- [ ] **Step 8: Commit**

```bash
git add engine/CMakeLists.txt engine/tests/test_break_keygen.cmake \
  engine/tests/test_break_crypto_target_contract.cmake engine/tests/test_break_integrity.c
git commit -m "test: support emulated security tests"
```

### Task 2: Unified 20-test CI and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:155-230`
- Modify: `docs/Build_Guide.md`, `docs/Implementation_Status.md`
- Modify: `docs/design/client_integrity.md`, `docs/design/server_authority.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Test: YAML and actual native CTest selection

**Interfaces:**
- Consumes: four new targets and Task 1's explicit environment boundary.
- Produces: generic QEMU job/step names and one exact 20-test selection.

- [ ] **Step 1: Run failing CI contract**

Assert all of the following with PyYAML and `ctest -N` on `build-core-app-net`:
- job name `Linux arm64 cross-build + QEMU tests (GCC)`;
- step name `Run selected tests under QEMU`;
- build command is the previous 16 targets followed by `test_break_crypto test_break_integrity test_break_authority break_keygen`;
- run lines include `BREAK_TEST_QEMU_USER=1 \\` and the eight-alternative regex from the design;
- no `|| true`;
- actual native selection equals the previous 14 names plus the six new names, size 20.

Expected: RED on the old display name before workflow editing.

- [ ] **Step 2: Apply minimal workflow changes**

Use the generic names above, append the four targets in that order, add `BREAK_TEST_QEMU_USER=1 \\` after `BREAK_TEST_RUNNER`, and use:

```yaml
            -R '^(test_break_crash|test_break_update|test_break_http|test_break_manifest_tool|test_break_crypto|test_break_keygen|test_break_integrity|test_break_authority)'
```

Keep emulator configuration, timeout, packages, job key, and object checks unchanged. Update comments to selected headless service/security coverage.

- [ ] **Step 3: Verify GREEN and full native regression**

Rerun the complete contract; expected 20 names and PASS. Then:

```bash
cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure
```

From `build-core-app-net`; expected 455 tests, zero failures, four established platform skips. Run `git diff --check`.

- [ ] **Step 4: Update docs**

Document the 20-name selection, crypto 20/20, authority 14/14, keygen hardening/concurrency, contracts, and the precise integrity QEMU-only setup skip. Native ptrace-positive execution must be distinguished from emulated 8/8. Explain that all current security-label tests are included but this is not full arm64 CTest. Prepend implementation-status evidence and update missing capabilities without claiming client integrity as an authorization input or physical-device proof.

- [ ] **Step 5: Commit**

```bash
git add .github/workflows/ci.yml docs/Build_Guide.md docs/Implementation_Status.md \
  docs/design/client_integrity.md docs/design/server_authority.md \
  docs/cross_engine/missing_capabilities.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-security-suite.md
git commit -m "ci: run arm64 security tests"
```

### Task 3: Final verification and remote proof

**Files:** verify all changes; modify implementation status only with observed remote evidence.

- [ ] **Step 1: Integrate and run final clean container**

Fetch/rebase if needed without discarding independent changes. Execute every arm64 workflow run block in a fresh Ubuntu container with runner CMake provisioning. Require 20 targets, object checks, 20 tests, all old/new summaries, keygen/contracts, and exactly one explicit integrity setup skip. Preserve complete logs.

- [ ] **Step 2: Independent review**

Review target-only emulation, shell quoting, exact selection, native strictness, and the skip's exit-90/value-1 guard. Fix Critical/Important findings test-first and verify adopted minor fixes.

- [ ] **Step 3: Push and assert remote evidence**

Push normally and wait for the exact HEAD's arm64 job. Assert `0 tests failed out of 20`, every previous 14-test summary, crypto 20/20, authority 14/14, integrity 8/8 with one explicit skip, keygen and both contracts. Confirm the skip message count is one and no native-like ptrace-positive claim is made.

- [ ] **Step 4: Record and audit**

Add run/job URLs and exact evidence to implementation status, commit as `docs: record arm64 security suite CI results`, and push. Finish clean with `HEAD == origin/master`; keep the broader goal open.
