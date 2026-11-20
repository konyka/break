# arm64 ELF Symbolization and QEMU Test Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Accept Linux AArch64 ELF symbol tables and run the complete crash-symbolizer test executable on arm64 under QEMU, including real nested crash fixtures.

**Architecture:** Keep the existing ELF reader and public interfaces, extending only its machine whitelist to the two supported ELF64 layouts. Keep native test defaults unchanged while allowing explicit environment overrides for GNU ELF tools and the nested fixture runner; the existing arm64 CI job supplies those overrides and runs both crash test executables.

**Tech Stack:** C11, ELF64, CMake/Ninja, GCC aarch64 cross toolchain and binutils, QEMU user emulation, GitHub Actions YAML, Python 3 + PyYAML contract checks, Podman Ubuntu 24.04 clean-room verification.

## Global Constraints

- Accept exactly `EM_X86_64` and `EM_AARCH64`; preserve every existing ELF bounds and format check.
- Keep native defaults `nm`, `readelf`, `strip`, and direct fixture execution.
- Override only GNU ELF tool commands; do not replace the optional LLVM Mach-O toolchain.
- Build all four targets: `break_crash engine test_break_crash test_break_crash_symbolize`.
- Keep the existing 37-case QEMU command and add one unmasked symbolizer command with a 240-second timeout.
- Do not install binfmt handlers, filter test results, retry failed tests, or append `|| true` to CI.
- Record optional LLVM subcheck skips exactly; do not claim a full arm64 `ctest`, GPU run, or physical-device result.
- Preserve existing documents, updating only superseded statements and adding current evidence.

---

### Task 1: AArch64 ELF symbol-table support

**Files:**
- Modify: `engine/tests/test_break_crash_symbolize.c:132-162,1900-1947`
- Modify: `engine/src/crash/break_crash_symbolize.c:106-119`
- Test: `build-core-app-net/test_break_crash_symbolize`

**Interfaces:**
- Consumes: existing `BreakElfSymbols`, `break_elf_symbols_open`, `break_elf_symbols_lookup`, `build_fixture`, `nm_addr`, `read_all`, and `write_bytes`.
- Produces: ELF64 input acceptance for `EM_AARCH64`; no new public function or changed signature.

- [ ] **Step 1: Add the failing native regression case**

Insert this test after `resolves_every_function_of_a_real_binary_against_nm`:

```c
TEST(an_aarch64_elf_uses_the_same_symbol_table_layout) {
    char exe[400], arm64[400];
    u8 *b;
    size_t n;
    u64 addr = 0, off = 99;
    Elf64_Ehdr eh;
    BreakElfSymbols *s;
    char name[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    path_in(exe, sizeof(exe), "fixture");
    path_in(arm64, sizeof(arm64), "fixture_arm64");
    ASSERT_TRUE(build_fixture(exe, ""));
    ASSERT_TRUE(nm_addr(exe, "leaf", &addr));
    b = read_all(exe, &n);
    ASSERT_NOT_NULL(b);
    memcpy(&eh, b, sizeof(eh));
    eh.e_machine = EM_AARCH64;
    memcpy(b, &eh, sizeof(eh));
    ASSERT_TRUE(write_bytes(arm64, b, n));
    s = break_elf_symbols_open(arm64);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(break_elf_symbols_lookup(s, addr, name, sizeof(name), &off));
    ASSERT_STR_EQ(name, "leaf");
    ASSERT_EQ(off, 0u);
    ASSERT_TRUE(break_elf_symbols_lookup(s, addr + 1u, name, sizeof(name), &off));
    ASSERT_STR_EQ(name, "leaf");
    ASSERT_EQ(off, 1u);
    break_elf_symbols_destroy(s);
    free(b);
}
```

Register it immediately after the existing first case in `TEST_MAIN_BEGIN()`:

```c
    RUN_TEST(resolves_every_function_of_a_real_binary_against_nm);
    RUN_TEST(an_aarch64_elf_uses_the_same_symbol_table_layout);
```

- [ ] **Step 2: Build and observe RED**

Run from `build-core-app-net`:

```bash
cmake --build . --parallel 6 --target test_break_crash_symbolize && ./test_break_crash_symbolize
```

Expected: the build succeeds, the new case fails at `ASSERT_NOT_NULL(s)` because `EM_AARCH64` is rejected, and the summary reports 44 passes, 1 failure, 45 total. This is the product regression test; no source reader edit is allowed before observing it.

- [ ] **Step 3: Make the minimal reader change**

Replace only the machine conjunct in `elf_from_bytes`:

```c
        eh.e_version != EV_CURRENT ||
        (eh.e_machine != EM_X86_64 && eh.e_machine != EM_AARCH64) ||
        eh.e_shentsize != sizeof(Elf64_Shdr) || eh.e_shnum == 0u || eh.e_shnum > SYM_MAX_SECTIONS ||
```

Do not broaden this to arbitrary machines and do not alter address conversion, symbol filtering, or allocation behavior.

- [ ] **Step 4: Verify the complete native symbolizer executable**

Run:

```bash
cmake --build . --parallel 6 --target test_break_crash_symbolize && ./test_break_crash_symbolize
```

Working directory: `build-core-app-net`.

Expected: `45 passed, 0 failed, 45 total`; the pre-existing `e_machine none` mutation remains rejected and both real LLVM Mach-O checks run with the host tools.

- [ ] **Step 5: Commit the independently tested product change**

```bash
git add engine/src/crash/break_crash_symbolize.c engine/tests/test_break_crash_symbolize.c
git commit -m "crash: read aarch64 ELF symbol tables"
```

### Task 2: Explicit test tools and CI execution

**Files:**
- Modify: `engine/tests/test_break_crash_symbolize.c:1-104,194-266,483-562`
- Modify: `.github/workflows/ci.yml:155-226`
- Modify: `engine/toolchain-aarch64-linux.cmake:1-10`
- Modify: `docs/Build_Guide.md:1417-1439`
- Modify: `docs/Implementation_Status.md:1-16` by prepending a dated section
- Modify: `docs/design/crash_symbolization.md:20-35,87-140`
- Modify: `docs/cross_engine/missing_capabilities.md:280-282`
- Modify: `docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md:67-87`
- Modify: `docs/superpowers/specs/2026-11-20-arm64-qemu-crash-test-design.md:24-28,52-76`
- Test: real arm64 `test_break_crash_symbolize` under QEMU and the inline YAML contract below

**Interfaces:**
- Consumes: Task 1's AArch64 ELF reader and the existing `BREAK_TEST_CC` configured compiler.
- Produces: `static const char *test_setting(const char *name, const char *fallback)` local to the test; environment controls `BREAK_TEST_NM`, `BREAK_TEST_READELF`, `BREAK_TEST_STRIP`, and `BREAK_TEST_RUNNER`; a second CI QEMU command.

- [ ] **Step 1: Isolate the remaining emulated failures after the reader fix**

Run this from the repository root. It selects the existing install/configure scripts, adds only the runner-provided CMake prerequisite and the diagnostic build/test commands, and preserves the test's failing exit status:

```bash
python3 - <<'PY'
from pathlib import Path
import os
import subprocess
import yaml

test_command = 'timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash_symbolize'
workflow = yaml.safe_load(Path('.github/workflows/ci.yml').read_text())
steps = workflow['jobs']['lane-cross-aarch64-linux']['steps']
selected = {'Install the host and arm64 build dependencies', 'Configure'}
scripts = [step['run'] for step in steps if step.get('name') in selected]
script = (
    'apt-get update && apt-get install -y --no-install-recommends cmake\n'
    'sudo() { command "$@"; }\n'
    + '\n'.join(scripts)
    + '\ncmake --build build-arm64 --parallel --target test_break_crash_symbolize\n'
    + test_command + '\n'
)
command = [
    'podman', 'run', '--rm',
    '-v', f'{Path.cwd()}:/workspace:z', '-w', '/workspace',
    '-e', 'GITHUB_WORKSPACE=/workspace', 'docker.io/library/ubuntu:24.04',
    'bash', '--noprofile', '--norc', '-e', '-o', 'pipefail', '-c', script,
]
raise SystemExit(subprocess.run(command, env=dict(os.environ, GITHUB_WORKSPACE='/workspace')).returncode)
PY
```

Expected: nonzero status; the former `s is NULL` machine-rejection failures are gone, while hardcoded GNU tool and direct nested fixture failures remain. Record the actual summary rather than deriving it from the old 28/16 result.

- [ ] **Step 2: Add the test-local override helper**

Update the introductory fixture comment to say `configured test compiler`, not `host compiler`. After `run`, add:

```c
static const char *test_setting(const char *name, const char *fallback) {
    const char *value = getenv(name);
    return value && value[0] ? value : fallback;
}
```

No production header, global mutable tool state, or command-line parser is needed.

- [ ] **Step 3: Route every GNU ELF oracle through its override**

Use these exact command constructions, retaining the existing surrounding parsing and assertions.

`nm_addr`:

```c
    snprintf(cmd, sizeof(cmd), "%s '%s' 2>/dev/null | awk '$3==\"%s\" {print $1}'",
             test_setting("BREAK_TEST_NM", "nm"), exe, sym);
```

`nm_size`:

```c
    snprintf(cmd, sizeof(cmd), "%s -S '%s' 2>/dev/null | awk '$4==\"%s\" {print $2}'",
             test_setting("BREAK_TEST_NM", "nm"), exe, sym);
```

Rename `run_quiet_nm_has_symtab` to `run_quiet_readelf_has_symtab`, update its sole caller, and construct:

```c
    snprintf(cmd, sizeof(cmd), "%s -S '%s' 2>/dev/null | grep -q ' .symtab '",
             test_setting("BREAK_TEST_READELF", "readelf"), path);
```

The stripped executable case:

```c
    snprintf(cmd, sizeof(cmd), "%s '%s'", test_setting("BREAK_TEST_STRIP", "strip"), exe);
```

The GNU build-ID case:

```c
    snprintf(cmd, sizeof(cmd), "%s -n '%s' 2>/dev/null | awk '/Build ID/ {print $3}'",
             test_setting("BREAK_TEST_READELF", "readelf"), exe);
```

The stripped shared-object case:

```c
    snprintf(cmd, sizeof(cmd), "%s -O0 -g0 -fPIC -shared -o '%s' '%s' 2>/dev/null && %s '%s'",
             BREAK_TEST_CC, so, src, test_setting("BREAK_TEST_STRIP", "strip"), so);
```

Its `.dynsym` oracle:

```c
        snprintf(c2, sizeof(c2), "%s -D '%s' 2>/dev/null | awk '$3==\"outer\" {print $1}'",
                 test_setting("BREAK_TEST_NM", "nm"), so);
```

Do not change `llvm_nm_rel`, `llvm_nm_arch`, `clang`, `ld64.lld`, or `llvm-lipo` commands.

- [ ] **Step 4: Prefix only nested crash fixture execution**

In `crash_child`, retain compilation, spool setup, the intentional signal-tolerant child invocation, and all subsequent record assertions. Replace only its execution formatting:

```c
    snprintf(cmd, sizeof(cmd), "%s '%s' '%s' >/dev/null 2>&1; true",
             test_setting("BREAK_TEST_RUNNER", ""), exe_path, spool);
```

An empty native prefix leaves a valid direct command. The CI prefix explicitly runs each newly compiled arm64 fixture under QEMU.

- [ ] **Step 5: Verify the intended QEMU environment before editing CI**

Use the complete Python orchestration in Step 1, replacing only its `test_command` assignment with this exact value:

```python
test_command = """BREAK_TEST_NM=aarch64-linux-gnu-nm \\
BREAK_TEST_READELF=aarch64-linux-gnu-readelf \\
BREAK_TEST_STRIP=aarch64-linux-gnu-strip \\
BREAK_TEST_RUNNER='qemu-aarch64 -L /' \\
timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash_symbolize"""
```

The orchestration still builds `test_break_crash_symbolize` in the configured arm64 tree before running this command.

Expected: exit 0 and `45 passed, 0 failed, 45 total`. Preserve and inspect the full output; explicitly record whether either optional real LLVM Mach-O subcheck prints `skipped`. If an assertion fails, investigate that actual architecture behavior rather than filtering or skipping the case.

Also rerun the native executable from `build-core-app-net`; expected: 45/45 with default tools and direct fixture execution.

- [ ] **Step 6: Run the failing CI contract**

Run:

```bash
python3 - <<'PY'
from pathlib import Path
import yaml

job = yaml.safe_load(Path('.github/workflows/ci.yml').read_text())['jobs']['lane-cross-aarch64-linux']
steps = job['steps']
build = next(s for s in steps if s.get('name') == 'Build the arm64 targets')
assert build['run'].strip() == (
    'cmake --build build-arm64 --parallel --target '
    'break_crash engine test_break_crash test_break_crash_symbolize'
)
run = next(s for s in steps if s.get('name') == 'Run the crash tests under QEMU')
assert run['run'].strip().splitlines() == [
    'qemu-aarch64 --version',
    'timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash',
    'BREAK_TEST_NM=aarch64-linux-gnu-nm \\',
    'BREAK_TEST_READELF=aarch64-linux-gnu-readelf \\',
    'BREAK_TEST_STRIP=aarch64-linux-gnu-strip \\',
    "BREAK_TEST_RUNNER='qemu-aarch64 -L /' \\",
    'timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash_symbolize',
]
assert '|| true' not in run['run']
print('arm64 symbolizer CI contract: PASS')
PY
```

Expected: FAIL on the old three-target build command. This check comes after the real test-environment proof but before the workflow implementation, so it independently pins CI delivery.

- [ ] **Step 7: Add the fourth target and exact QEMU command**

Set the build step to:

```yaml
          cmake --build build-arm64 --parallel --target break_crash engine test_break_crash test_break_crash_symbolize
```

Append to the existing QEMU step without changing its first two lines:

```yaml
          BREAK_TEST_NM=aarch64-linux-gnu-nm \
          BREAK_TEST_READELF=aarch64-linux-gnu-readelf \
          BREAK_TEST_STRIP=aarch64-linux-gnu-strip \
          BREAK_TEST_RUNNER='qemu-aarch64 -L /' \
          timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash_symbolize
```

Update the job's explanatory comment to say both crash record handling and ELF/frame symbolization run under QEMU; do not change its key, runner, packages, configure command, or object checks.

- [ ] **Step 8: Verify the CI contract GREEN and native defaults**

Rerun the complete Python contract from Step 6; expected: `arm64 symbolizer CI contract: PASS` and exit 0. Then run:

```bash
cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure
```

Working directory: `build-core-app-net`. Expected: build success and 455 registered tests with zero failures, retaining only the four established platform skips. Run `git diff --check`; expected: no errors.

- [ ] **Step 9: Update documentation and stale comments**

In `engine/toolchain-aarch64-linux.cmake`, replace the build-only introduction with a statement that the toolchain cross-compiles arm64 paths and the CI explicitly runs selected tests through QEMU; keep all toolchain settings unchanged.

In `docs/Build_Guide.md`, add the fourth target and the full symbolizer environment/command. Explain host cross binutils versus the nested target runner and the optional LLVM subchecks. In `docs/design/crash_symbolization.md`, document the ELF machine whitelist, change the named-case count to 45, add the real arm64 symbolizer run, and remove the current statement that this suite is unrun. Preserve all unimplemented minidump/PE, DWARF CFI, production-service, and physical-device limitations.

Prepend an `arm64 ELF 符号化与 QEMU 测试（2026-11-20）` implementation-status entry containing the native RED/GREEN, old QEMU 28/16 diagnostic, actual intermediate result, final 45-case result with optional skips, and native full-suite result. Remote evidence remains pending until Task 3 observes it.

Update `docs/cross_engine/missing_capabilities.md` so arm64 ELF reading and the QEMU symbolizer lane are delivered, while production collection, minidump, Windows symbolization, and physical devices remain open. Narrow both earlier arm64 specs' out-of-scope/result language by linking the new symbolizer design; preserve their original 37-case history.

- [ ] **Step 10: Review and commit**

Inspect the full diff and status. Only Task 2 files and this plan may be uncommitted; Task 1 is already committed. Check that no LLVM tool name was replaced, no assertion was removed, and no pending result is described as observed.

```bash
git add engine/tests/test_break_crash_symbolize.c .github/workflows/ci.yml \
  engine/toolchain-aarch64-linux.cmake docs/Build_Guide.md \
  docs/Implementation_Status.md docs/design/crash_symbolization.md \
  docs/cross_engine/missing_capabilities.md \
  docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md \
  docs/superpowers/specs/2026-11-20-arm64-qemu-crash-test-design.md \
  docs/superpowers/plans/2026-11-20-arm64-qemu-symbolizer-test.md
git commit -m "ci: run arm64 symbolization tests under QEMU"
```

### Task 3: Integrated clean-room and remote proof

**Files:**
- Verify: all Task 1 and Task 2 files
- Modify after observed remote results: `docs/Implementation_Status.md`
- Create: no new source or test files

**Interfaces:**
- Consumes: the committed four-target CI workflow and test overrides.
- Produces: integrated native and clean-container results, a direct `master` push, and a successful remote arm64 job with both QEMU summaries.

- [ ] **Step 1: Integrate remote changes**

```bash
git fetch origin master
git status --short
git log --oneline --decorate -5
```

If remote advanced, inspect its files and rebase without discarding independent behavior. If the rebase changes any tested source or workflow input, repeat the affected native, QEMU, and YAML checks before continuing.

- [ ] **Step 2: Execute the final CI scripts in a clean container**

Run this orchestration from the repository root as a background task:

```bash
python3 - <<'PY'
from pathlib import Path
import os
import subprocess
import yaml

workflow = yaml.safe_load(Path('.github/workflows/ci.yml').read_text())
steps = workflow['jobs']['lane-cross-aarch64-linux']['steps']
scripts = [step['run'] for step in steps if 'run' in step]
script = (
    'apt-get update && apt-get install -y --no-install-recommends cmake\n'
    'sudo() { command "$@"; }\n'
    + '\n'.join(scripts)
)
command = [
    'podman', 'run', '--rm',
    '-v', f'{Path.cwd()}:/workspace:z', '-w', '/workspace',
    '-e', 'GITHUB_WORKSPACE=/workspace', 'docker.io/library/ubuntu:24.04',
    'bash', '--noprofile', '--norc', '-e', '-o', 'pipefail', '-c', script,
]
raise SystemExit(subprocess.run(command, env=dict(os.environ, GITHUB_WORKSPACE='/workspace')).returncode)
PY
```

This starts a new container with the repository mounted at `/workspace:z`, provisions only the GitHub-runner CMake prerequisite, and executes every original CI run block in order without editing or filtering it.

Run this as a background task and preserve its complete output. Require all four targets, the object checks, the 37/37 crash summary, and the 45/45 symbolizer summary. Record optional LLVM subcheck skips exactly and remove only QEMU core files generated by the tests from the working tree.

- [ ] **Step 3: Push and identify the exact run**

```bash
git push origin master
gh api --method GET repos/konyka/break/actions/runs \
  -f head_sha="$(git rev-parse HEAD)" -f per_page=20 \
  --jq '.workflow_runs[] | select(.name == "CI") | {id, head_sha, status, conclusion, html_url}'
```

Do not create a PR. If the push is rejected because remote advanced, return to Step 1; never force-push.

- [ ] **Step 4: Require the remote arm64 job and both real test summaries**

Find the job named `Linux arm64 cross-build + QEMU crash tests (GCC)` with `gh run view <run-id> --json jobs`. Wait for that job, not for unrelated platform jobs. Require its install, configure, build, object-check, and QEMU steps to be successful. Read the completed job log through:

```bash
gh api --allow-escape-sequences repos/konyka/break/actions/jobs/<job-id>/logs
```

Require one `37 passed, 0 failed, 37 total` summary and one `45 passed, 0 failed, 45 total` summary. If it fails, inspect the full relevant log and return to the corresponding TDD task instead of treating container success as remote success.

- [ ] **Step 5: Record the remote evidence and push the documentation follow-up**

Add the actual run/job URLs, commit, step conclusions, 37/37 and 45/45 summaries, and any optional LLVM subcheck skips to the current `docs/Implementation_Status.md` section. Run `git diff --check`, commit only that evidence with `docs: record arm64 symbolization CI results`, and push normally.

- [ ] **Step 6: Audit the slice and retain the larger goal**

Confirm `git status --short` is empty and `HEAD` equals `origin/master`. Verify the docs claim only selected emulated tests, not a full arm64 suite or physical-device evidence. Report the delivered product and CI capability plus remaining limits; do not mark the broader active objective complete.
