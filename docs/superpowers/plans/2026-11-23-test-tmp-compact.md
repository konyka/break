# Test Temp Compact Fallback Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Eliminate silent temp-path collisions without changing the TEMP root or making existing long-path tests abort unnecessarily.

**Architecture:** Keep normal `test_tmp` formatting. Only final-path truncation may replace a basename without a parent directory with a compact FNV-1a hash plus PID inside the original TEMP root. Windows `norm` overflow, parent-containing names, and unrepresentable results fail explicitly.

**Tech Stack:** C11, Windows/POSIX stdio, fork/waitpid, CMake/CTest.

## Global Constraints

- C11 and repository/Google naming; no compatibility-engine prefixes, retired domain vocabulary, or role labels.
- Only test infrastructure changes: `test_framework.h`, `test_fork_deadline.c`, `test_scene_serial.c`, `test_async_loader.c`, `test_tmp_abort.c`, `test_tmp_abort.cmake`, and their CMake registration.
- Normal paths remain byte-identical. Fallback is `<original-temp-root>/break_<8-lowercase-hex>_<pid>` and requires at least 32 bytes including NUL.
- Windows `norm` overflow never enters fallback: `test_tmp` and `test_tmp_root()` both print `TEST PATH TRUNCATED` and abort before I/O.
- Never fall back to `./`, and never hash a name containing `/` or `\`.
- `cap < 32`, negative `snprintf` results, parent-containing truncated names, or an overflowing fallback print `TEST PATH TRUNCATED` and abort before file I/O.
- Hash uses `const unsigned char *` iteration, `unsigned long hash` with `%08lx`, FNV-1a constants `2166136261UL` and `16777619UL`, and masks to `0xffffffffUL` on every update.
- Every new behavior gets a real RED first. Test children are reaped with the existing bounded helper.
- Default Vulkan remains primary; OpenGL remains fallback/image comparison. Linux uses native Wayland only.
- Append documentation, review and re-review fixes, then push `master` directly without a PR.

---

### Task 1: Compact leaf fallback and regression coverage

**Files:**
- Modify: `engine/tests/test_framework.h`
- Modify: `engine/tests/test_fork_deadline.c`
- Modify: `engine/tests/test_scene_serial.c`
- Modify: `engine/tests/test_async_loader.c`
- Create: `engine/tests/test_tmp_abort.c`
- Create: `engine/tests/test_tmp_abort.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: existing `test_tmp`, `test_tmp_root`, and `test_waitpid_deadline`.
- Produces: unchanged public signatures and TEMP root semantics; two Windows overflow test entries.

- [ ] **Step 1: Add four failing POSIX tests and dynamic-cap Windows/VFS regressions**

In `test_fork_deadline.c`, add and register inside the existing POSIX region:

```c
TEST(tmp_rejects_truncated_path) {
    int status = 0;
    pid_t pid = fork();
    if (pid == 0) {
        char path[31];
        (void)test_tmp(path, sizeof(path),
                       "same_prefix_with_a_very_long_suffix_a");
        _exit(0);
    }
    ASSERT_TRUE(pid > 0);
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 5000u), pid);
    ASSERT_TRUE(WIFSIGNALED(status));
    ASSERT_EQ(WTERMSIG(status), SIGABRT);
}

TEST(tmp_truncation_uses_distinct_compact_fallbacks) {
    char first[32];
    char second[32];
    char expected[64];
    (void)test_tmp(first, sizeof(first),
                   "same_prefix_with_a_very_long_suffix_a");
    (void)test_tmp(second, sizeof(second),
                   "same_prefix_with_a_very_long_suffix_b");
    ASSERT_TRUE(strcmp(first, second) != 0);
    snprintf(expected, sizeof(expected), "/tmp/break_8073d8d7_%d",
             (int)TEST_GETPID());
    ASSERT_TRUE(strcmp(first, expected) == 0);
    snprintf(expected, sizeof(expected), "/tmp/break_8173da6a_%d",
             (int)TEST_GETPID());
    ASSERT_TRUE(strcmp(second, expected) == 0);
    snprintf(expected, sizeof(expected), "/tmp/break_x_%d",
             (int)TEST_GETPID());
    (void)test_tmp(first, sizeof(first), "x");
    ASSERT_TRUE(strcmp(first, expected) == 0);
}
```

Add child-process cases named `tmp_rejects_truncated_parent_path` and `tmp_rejects_truncated_backslash_parent_path`, using a 32-byte buffer and long names `parent_with_a_long_suffix/file` and `parent_with_a_long_suffix\\file`. Each child calls `test_tmp` and `_exit(0)` on the old helper; the parent uses `test_waitpid_deadline` and requires SIGABRT. These cases prove hashing never erases parent semantics.

Expected RED: the first child and both parent-path children exit 0, while the distinct-fallback case produces identical truncated strings. The normal short-name assertion passes on both implementations.

In `test_scene_serial.c`, add and register `temp_long_names_use_distinct_fallbacks`. Under `_WIN32`, compute the capacity rather than assuming a fixed root/PID length:

```c
char pid_text[16];
int pid_digits = snprintf(pid_text, sizeof(pid_text), "%d", (int)TEST_GETPID());
size_t cap = strlen(test_tmp_root()) + 17u + (unsigned)pid_digits;
if (cap < 32u) cap = 32u;
```

Use that capacity with a sufficiently large local buffer and the two 37-byte names above. Require distinct paths whose basenames begin with `break_`, and require `strlen(path) < cap`. `R + 17 + P` includes the root slash, `break_`, eight hash digits, PID separator, PID digits, and NUL; the path without NUL has length `R + 16 + P`, which is strictly less than the clamped capacity. The old full long-name form needs another 29 bytes and therefore truncates on this capacity. Do not modify TEMP or print it. Other platforms keep their existing conditional behavior and are not claimed as Windows evidence.

In `test_async_loader.c`, add `async_loader_compact_path_roundtrip`. Use the same capacity formula and `test_tmp` with the first long name. Before any file I/O, require the basename to equal an independently built `break_8073d8d7_<pid>` string. Then create the file with one known byte, mount `test_tmp_root()`, request that exact basename through the real async loader, and require one callback with that byte before removal. This proves fallback I/O rather than only string shape.

Create `test_tmp_abort.c` with a mode argument:

```c
#include "test_framework.h"

int main(int argc, char **argv) {
    char path[128];
    if (argc > 1 && strcmp(argv[1], "tmp") == 0) {
        (void)test_tmp(path, sizeof(path), "x");
    } else {
        (void)test_tmp_root();
    }
    (void)g_test_count;
    (void)g_test_pass;
    (void)g_test_fail;
    return 0;
}
```

Create `test_tmp_abort.cmake` to set TEMP to 600 ASCII characters and execute the probe with `tmp` or `root`. Require `"${result}"` not string-equal to `"0"` and require `TEST PATH TRUNCATED` in stderr, so an arbitrary crash cannot pass. Set a 30-second process timeout and never print TEMP. The old implementation returns 0 in both modes, producing RED. Register both entries only on Windows.

- [ ] **Step 2: Implement the compact leaf fallback and norm guards**

In `test_tmp`, after Windows normalization, immediately reject `tmp[i] != '\0'` with the shared marker and abort. Add the same check to `test_tmp_root`; never use a truncated norm as a root.

After the normal `snprintf`, first reject `written < 0`, then use compact fallback only when `(size_t)written >= cap`. Compact fallback must:

1. Reject `name` containing `/` or `\` with the marker and abort; never erase parent semantics.
2. Require `cap >= 32`, then compute masked 32-bit FNV-1a using `const unsigned char *` and `unsigned long` with `%08lx`.
3. Write `<original-temp-root>/break_<hash>_<pid>` with `snprintf`. POSIX uses `/tmp`; Windows uses the normalized TEMP root, never `./`.
4. Reject a negative result or `(size_t)written >= cap`; otherwise return `buf` normally.

Keep normal path formatting and `test_tmp_root` semantics unchanged. The fallback is checked rather than assumed to fit every root/cap combination.

- [ ] **Step 3: Verify GREEN locally and on Windows**

Run on Linux:

```bash
cmake --build build-test-tmp --parallel 3 --target \
  test_fork_deadline test_scene_serial test_async_loader \
  test_runtime_io test_runtime_reload test_core_app_diagnostics
./build-test-tmp/test_fork_deadline
ctest --test-dir build-test-tmp --output-on-failure \
  -R '^(test_fork_deadline|test_scene_serial|test_async_loader|test_runtime_io|test_runtime_reload|test_core_app_diagnostics)$'
```

Expected: `test_fork_deadline` 14/14, `test_async_loader` 19/19, and all six CTest entries pass. On Windows, run the complete `test_scene_serial`, requiring 123/123, plus the async loader and both overflow probes. Also run `test_mipmap_stream`, `test_editor_scene`, `test_runtime_io`, `test_runtime_reload`, and `test_core_app_diagnostics`, checking root mounts and the existing nonexistent-parent case.

- [ ] **Step 4: Commit after task review**

```bash
git add engine/CMakeLists.txt engine/tests/test_framework.h \
  engine/tests/test_fork_deadline.c engine/tests/test_scene_serial.c \
  engine/tests/test_async_loader.c engine/tests/test_tmp_abort.c \
  engine/tests/test_tmp_abort.cmake
git commit -m "test(temp): add compact paths for long temporary names"
```

### Task 2: Documentation, independent review, validation, and delivery

**Files:**
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

- [ ] **Step 1: Append the root cause and exact evidence**

Document the two truncation layers, root-preserving leaf fallback, norm guards, 32-byte minimum, dynamic capacity formula, parent-path rejection, deterministic RED/GREEN, and actual VFS/overflow-probe evidence. Do not claim unrelated qemu-user or Windows platform/GPU issues are fixed.

- [ ] **Step 2: Run complete validation**

Run full Vulkan and OpenGL suites plus ASan+UBSan and TSan focused tests. On Windows, rerun `test_scene_serial`, async loader, both overflow probes, and all relevant consumers. Keep conditional skips visible and never convert them into executed passes.

- [ ] **Step 3: Independent review and fixes**

Review 32-bit hash consistency, `cap` arithmetic, norm guards, root preservation, parent semantics, no-I/O-before-abort, dynamic-cap proof, child reaping, and real VFS fallback reads. Fix every Critical/Important through RED/GREEN and scoped re-review.

- [ ] **Step 4: Synchronize, push, and verify remote**

```bash
git diff --check
git fetch origin
git rebase origin/master
git push origin HEAD:master
```

Re-run affected tests after any rebase. Verify final CI, windows-d3d12, arm64 selection and Proton ancestry. Append actual run IDs/outcomes and leave a clean `master` checkout with no temporary worktree.
