# Scene Temp Path Truncation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Prevent the two independent scene fixtures in `failed_load_keeps_previous_scene` from collapsing onto one file under a long Windows TEMP path.

**Architecture:** Make a fixture-local change only: enlarge both path buffers and assert distinct paths before any file write. Do not alter shared helpers or product behavior.

**Tech Stack:** C11, Windows/POSIX stdio, CMake/CTest.

## Global Constraints

- C11 and repository/Google naming; no compatibility-engine prefixes, retired domain vocabulary, or role labels.
- Only `engine/tests/test_scene_serial.c` changes. No product code, file format, dependency, `test_tmp`, or `test_tmp_root` change.
- `pa` and `pb` become 512 bytes. `strcmp(pa, pb) != 0` must pass before the first save; colliding paths must never reach file I/O.
- Keep the actual Windows RED before modification. Do not introduce a shared `abort()` that would break earlier 64-byte callers.
- Default Vulkan remains primary; OpenGL remains fallback/image comparison. Linux uses native Wayland only.
- Append documentation, review and re-review fixes, then push `master` directly without a PR.

---

### Task 1: Scene fixture path regression

**Files:**
- Modify: `engine/tests/test_scene_serial.c`

**Interfaces:**
- Consumes: existing `test_tmp(char *buf, size_t cap, const char *name)` and scene save/load APIs.
- Produces: no API or shared-helper change.

- [ ] **Step 1: Preserve the current Windows RED**

On the current master, run `test_scene_serial` on Windows and preserve the failure at the first `scene_load_binary(wd, &dst, pa)` in `failed_load_keeps_previous_scene`. The earlier temporary diagnostic has already shown `keep_len=63,63 equal=1`, proving that the 64-byte buffers truncate both names to the same path; the diagnostic source change has been reverted.

- [ ] **Step 2: Apply the minimal fixture change**

Change only the two declarations in `failed_load_keeps_previous_scene` to `pa[512]` and `pb[512]`, then add immediately before `SerializeOptions opts`:

```c
ASSERT_TRUE(strcmp(pa, pb) != 0);
```

This assertion precedes every save/corruption/load call and cannot be satisfied by the colliding old fixture on the affected host.

- [ ] **Step 3: Verify GREEN on Windows and focused consumers**

On Windows:

```cmd
cmake --build build-d3d12 --target test_scene_serial --parallel 4
ctest --test-dir build-d3d12 -C Debug --output-on-failure -R ^test_scene_serial$
```

Expected: `test_scene_serial` 122/122, with the distinct-path assertion before any save and no failure at the first load of A.

On Linux, run:

```bash
cmake --build build-scene-temp --parallel 3 --target \
  test_scene_serial test_runtime_io test_runtime_reload test_core_app_diagnostics
ctest --test-dir build-scene-temp --output-on-failure \
  -R '^(test_scene_serial|test_runtime_io|test_runtime_reload|test_core_app_diagnostics)$'
```

Expected: all four CTest entries pass, with no shared helper or product diff.

- [ ] **Step 4: Commit after task review**

```bash
git add engine/tests/test_scene_serial.c
git commit -m "test(scene): isolate long temporary fixture paths"
```

### Task 2: Documentation, review, validation, and delivery

**Files:**
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

- [ ] **Step 1: Append the root cause and exact evidence**

Document the 63-byte collision, B overwriting A, the 512-byte fixture fix, pre-I/O distinct assertion, Windows 121/122→122/122, and unchanged product/file-format boundary. Keep shared `test_tmp` truncation and qemu-user/Windows platform issues separate.

- [ ] **Step 2: Run complete validation**

Run full Vulkan and OpenGL suites plus ASan+UBSan and TSan focused tests. Keep conditional skips visible. On Windows, rerun the complete scene suite and relevant consumers; do not infer unrelated Windows platform/GPU tests are fixed.

- [ ] **Step 3: Independent review and fixes**

Review buffer sizing, assertion order, normal path behavior, proof of the original collision, and whether shared-helper changes are correctly excluded. Fix every Critical/Important through RED/GREEN and scoped re-review.

- [ ] **Step 4: Synchronize, push, and verify remote**

```bash
git diff --check
git fetch origin
git rebase origin/master
git push origin HEAD:master
```

Re-run affected tests after any rebase. Verify final CI, windows-d3d12, arm64 selection and Proton ancestry. Append actual run IDs/outcomes and leave a clean `master` checkout with no temporary worktree.
