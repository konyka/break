# Dynamic AI Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

**Goal:** Extend `break_ai` with transactional dynamic navigation, versioned cached queries, velocity avoidance, deterministic formations, smart-object reservations, and fixed-capacity agents without hot-path allocation.

**Architecture:** A GameThread-owned `BreakAiRuntime` borrows the existing baked mesh and owns fixed-capacity sidecar arrays plus a preallocated A* workspace. Dynamic obstacle counts feed the existing A* implementation; formations and smart objects use the same runtime's generation-checked entities.

**Tech Stack:** C11, existing `BreakNavMesh`/A*, `test_framework.h`, CMake/CTest, ASan+UBSan, TSan.

## Global Constraints

- Work only in `.worktrees/cry-ai` on `cry-wave1-ai`; do not push or create a PR.
- Engine additions are C11. `break_ai` remains renderer/RHI-free and is not linked into `engine`, `engine_demo`, or `dxx_break`.
- All mutable runtime calls are GameThread-owner-only; non-owner calls return `BREAK_NAV_REJECTED`.
- Hot paths perform no heap allocation. Capacity is fixed at creation and hard-limited; excess returns `OVERLOAD`, never silent truncation.
- Every failed mutation is atomic and every failed output-producing call leaves its output unchanged.
- Reuse `break_nav_query.c` A* and `break_nav_follow_wish`; do not create a parallel navigation system.
- Write each behavior test first, observe its expected RED, then implement the minimal GREEN. Build with `-j3`.
- Do not modify `docs/Implementation_Status.md` or unrelated modules.

---

### Task 1: Preallocated shared A* workspace

**Files:**
- Create: `engine/src/ai/break_nav_workspace.c`
- Modify: `engine/src/ai/break_nav_internal.h`
- Modify: `engine/src/ai/break_nav_bake.c`
- Modify: `engine/src/ai/break_nav_query.c`
- Create: `engine/tests/test_break_ai_hot_path_contract.cmake`
- Modify: `engine/CMakeLists.txt`
- Modify: `engine/tests/test_break_ai_target_contract.cmake`

**Interfaces:**
- Produces: `BreakNavWorkspace *break_nav_workspace_create(u32 poly_count)` and `void break_nav_workspace_destroy(BreakNavWorkspace *)`.
- Produces: `BreakNavError break_nav_find_path_workspace(const BreakNavMesh *, BreakNavWorkspace *, const u32 *blocked_counts, Vec3, Vec3, BreakNavPath *)`.
- Preserves: public `break_nav_find_path(const BreakNavMesh *, Vec3, Vec3, BreakNavPath *)` behavior.

- [x] **Step 1: Write the failing hot-path contract**

Read `break_nav_query.c` and reject `malloc(`, `calloc(`, `realloc(`, or `free(` in the query translation unit. Register it as a headless `break_ai` CTest beside the existing target contract.

- [x] **Step 2: Run the contract and confirm RED**

Run: `cmake -S engine -B build-ai -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF && ctest --test-dir build-ai -R '^test_break_ai_hot_path_contract$' --output-on-failure`
Expected: FAIL because the existing A* query allocates and frees six arrays.

- [x] **Step 3: Implement creation-time workspaces**

Move query-array ownership to `BreakNavWorkspace`; allocate it in bake and release it in mesh destroy. Keep the A* neighbor order, heap comparisons, path-point cap, and failure-output behavior unchanged. Accept an optional blocked-count array in the internal entry, rejecting blocked start/end and skipping blocked neighbors.

- [x] **Step 4: Run old tests and contract to confirm GREEN**

Run: `cmake --build build-ai -j3 --target test_break_nav_bake test_break_nav_query test_break_nav_follow test_break_perception test_break_behavior test_break_steer && ctest --test-dir build-ai -R 'break_ai|test_break_nav|test_break_steer|test_break_perception|test_break_behavior' --output-on-failure`
Expected: all focused tests PASS, including the no-allocation source contract.

- [x] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/src/ai engine/tests/test_break_ai_* && git commit -m "ai: preallocate navigation query workspace"
```

### Task 2: Dynamic obstacles, versions, and cached queries

**Files:**
- Create: `engine/src/ai/break_ai_internal.h`
- Create: `engine/src/ai/break_ai_runtime.c`
- Create: `engine/src/ai/break_ai_obstacle.c`
- Create: `engine/src/ai/break_ai_query.c`
- Create: `engine/tests/test_break_ai_dynamic.c`
- Modify: `engine/src/ai/break_ai.h`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Task 1 shared workspace query.
- Produces: `BreakAiRuntime`, `BreakAiRuntimeDesc`, `BreakAiObstacleHandle`, `BreakAiObstacleDesc`, `BreakAiPath` and the dynamic APIs specified in `docs/design/ai_dynamic.md` §3–4.

- [x] **Step 1: Write behavior tests before runtime implementation**

Use a flat 9×9 mesh. Assert this sequence with real path queries:

```c
BreakAiPath old_path;
ASSERT_EQ(break_ai_find_path(ai, left, right, 1u, &old_path), BREAK_NAV_OK);
BreakAiObstacleHandle wall;
ASSERT_EQ(break_ai_obstacle_add(ai, &full_wall, &wall), BREAK_NAV_OK);
ASSERT_EQ(break_ai_nav_version(ai), 2u);
ASSERT_EQ(break_ai_find_path(ai, left, right, 1u, &sentinel), BREAK_NAV_STALE);
ASSERT_EQ(break_ai_find_path(ai, left, right, 2u, &sentinel), BREAK_NAV_FAILED);
ASSERT_FALSE(break_ai_path_is_current(ai, &old_path));
ASSERT_EQ(break_ai_obstacle_remove(ai, wall), BREAK_NAV_OK);
ASSERT_EQ(break_ai_find_path(ai, left, right, 3u, &sentinel), BREAK_NAV_OK);
```

Add separate tests for overlapping walls, obstacle update, invalid rectangles, stale handles, full obstacle capacity, version/output immutability after failure, and a non-owner thread returning `REJECTED`. A one-obstacle runtime must reject a second add with `OVERLOAD` while the first handle remains removable.

- [x] **Step 2: Compile and run to confirm RED**

Run: `cmake --build build-ai -j3 --target test_break_ai_dynamic && ./build-ai/test_break_ai_dynamic`
Expected: initial compile/link failure for the new API; after declarations and minimal stubs, runtime assertions FAIL because obstacles/versioning are not implemented. Record both, but use the assertion RED as behavioral evidence.

- [x] **Step 3: Implement runtime and dynamic query minimally**

Create owner-thread tracking, fixed arrays, per-poly `u32` counters, generation handles, and version-1 initialization. Rasterize rectangles over base-poly centers. Validate all failure conditions before changing counters or versions. Implement exact-key/current-version cache lookup and deterministic replacement; run the shared A* with runtime workspace and blocked counts. Copy results to a local `BreakAiPath` and commit `out` only on success.

- [x] **Step 4: Run dynamic and regression tests to confirm GREEN**

Run: `cmake --build build-ai -j3 --target test_break_ai_dynamic test_break_nav_query && ctest --test-dir build-ai -R '^(test_break_ai_dynamic|test_break_nav_query|test_break_ai_hot_path_contract)$' --output-on-failure`
Expected: all PASS with wall block/reopen, no-path, stale rejection, and capacity atomicity.

- [x] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/src/ai engine/tests/test_break_ai_dynamic.c && git commit -m "ai: add versioned dynamic navigation"
```

### Task 3: Velocity avoidance and fixed-capacity agents

**Files:**
- Create: `engine/src/ai/break_ai_agent.c`
- Create: `engine/tests/test_break_steer_velocity.c`
- Create: `engine/tests/test_break_ai_agents.c`
- Modify: `engine/src/ai/break_ai.h`
- Create: `engine/src/ai/break_steer_velocity.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `BreakSteerAgent`, `BreakAiAgentDesc`, `break_steer_avoid_velocity`, and agent add/update/remove/avoid exactly as designed in §6.

- [x] **Step 1: Write velocity and agent tests**

For a head-on pair, assert the selected velocity differs from desired, stays within max speed, and repeated simulation avoids overlap. Run the same geometry with different neighbor velocity and assert that the chosen velocity responds to relative motion. Assert bit-identical repeated results, `OVERLOAD` for 17 neighbors, and unchanged output for non-finite input.

For a one-agent runtime, add entity `{1,1}`, reject `{2,1}` with `OVERLOAD`, reject duplicate `{1,1}` with `REJECTED`, and verify update/avoid on the original agent still works. Assert unknown generation returns `STALE` and nearest-neighbor selection is deterministic.

- [x] **Step 2: Run tests to confirm RED**

Run: `cmake --build build-ai -j3 --target test_break_steer_velocity test_break_ai_agents && ./build-ai/test_break_steer_velocity && ./build-ai/test_break_ai_agents`
Expected: behavioral assertions FAIL after minimal declarations/stubs; specifically head-on avoidance still returns the desired velocity and agent capacity is not enforced.

- [x] **Step 3: Implement bounded velocity sampling and agents**

Evaluate a fixed candidate array using relative velocity and closest approach within the horizon. Clamp every emitted velocity to `max_speed`; use candidate order for ties. Store agent slots without allocation, and select at most the nearest 16 neighbors with explicit Entity tie-breaking before calling the shared steering function.

- [x] **Step 4: Run steering and old suites to confirm GREEN**

Run: `cmake --build build-ai -j3 --target test_break_steer test_break_steer_velocity test_break_ai_agents && ctest --test-dir build-ai -R '^(test_break_steer|test_break_steer_velocity|test_break_ai_agents)$' --output-on-failure`
Expected: all PASS without changing legacy steer semantics.

- [x] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/src/ai engine/tests/test_break_steer_velocity.c engine/tests/test_break_ai_agents.c && git commit -m "ai: add velocity avoidance and agent registry"
```

### Task 4: Stable formation slots and deterministic following

**Files:**
- Create: `engine/src/ai/break_ai_formation.c`
- Create: `engine/tests/test_break_ai_formation.c`
- Modify: `engine/src/ai/break_ai.h`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: registered agents from Task 3 and existing `break_nav_follow_wish`.
- Produces: `BreakAiFormationHandle` and create/destroy/slots/tick APIs from design §7.

- [x] **Step 1: Write formation tests**

Create leader and two followers in known order. Assert leader slot equals leader position, followers occupy alternating rear wedge slots, repeated calls are bit-identical, and undersized output returns `OVERLOAD` with sentinel arrays unchanged. Integrate follower positions using tick velocities and assert distance to slots decreases without exceeding `max_speed`. Cover duplicate/unknown members, member and formation capacities, stale handles, and agent-removal conflict.

- [x] **Step 2: Run formation tests to confirm RED**

Run: `cmake --build build-ai -j3 --target test_break_ai_formation && ./build-ai/test_break_ai_formation`
Expected: assertions FAIL because slots and deterministic follow are absent, not merely because a target is absent.

- [x] **Step 3: Implement formations**

Validate the complete member list before acquiring a slot. Store members in caller order and derive wedge offsets from normalized XZ leader forward with +X fallback. Reuse the follower's bounded segment step for followers and convert displacement to velocity; return the leader's current velocity at output index zero.

- [x] **Step 4: Run formation and regression tests to confirm GREEN**

Run: `cmake --build build-ai -j3 --target test_break_ai_formation test_break_nav_follow test_break_ai_agents && ctest --test-dir build-ai -R '^(test_break_ai_formation|test_break_nav_follow|test_break_ai_agents)$' --output-on-failure`
Expected: all PASS, including deterministic replay and failure atomicity.

- [x] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/src/ai engine/tests/test_break_ai_formation.c && git commit -m "ai: add deterministic formation following"
```

### Task 5: Smart-object reservations and lifecycle atomicity

**Files:**
- Create: `engine/src/ai/break_ai_smart_object.c`
- Create: `engine/tests/test_break_ai_smart_object.c`
- Modify: `engine/src/ai/break_ai.h`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: generation-checked registered agents.
- Produces: `BreakAiSmartObjectHandle` and add/remove/reserve/release/owner APIs from design §8.

- [x] **Step 1: Write reservation competition tests**

Register two agents and one object. Reserve with A twice and assert both succeed; reserve or release with B and assert `REJECTED` with owner still A. Release A, reserve B, and verify the ownership transfer. Assert a second object add returns `OVERLOAD` in a one-object runtime, reserved object removal and owning-agent removal are rejected, and a removed/recreated object rejects the old generation with `STALE`. Sentinels must remain unchanged on every failed output call.

- [x] **Step 2: Run tests to confirm RED**

Run: `cmake --build build-ai -j3 --target test_break_ai_smart_object && ./build-ai/test_break_ai_smart_object`
Expected: behavioral assertions FAIL because competing reservations overwrite or are not represented.

- [x] **Step 3: Implement fixed-capacity smart objects**

Validate object handle and agent before every mutation. Use `ENTITY_NULL` for a free object, same-owner reserve as an idempotent success, and reject all competing or lifecycle-conflicting operations before changing state. Increment generation on slot reuse.

- [x] **Step 4: Run smart-object and full focused normal tests to confirm GREEN**

Run: `cmake --build build-ai -j3 --target test_break_ai_smart_object && ctest --test-dir build-ai -R 'break_ai|test_break_nav|test_break_steer|test_break_perception|test_break_behavior|test_cry_style_prototype' --output-on-failure`
Expected: all focused tests PASS.

- [x] **Step 5: Commit**

```bash
git add engine/CMakeLists.txt engine/src/ai engine/tests/test_break_ai_smart_object.c && git commit -m "ai: add smart object reservations"
```

### Task 6: Mutation checks, sanitizer lanes, review, and report

**Files:**
- Create: `.superpowers/sdd/ai-dynamic-report.md`
- Modify only if review finds a P3 defect: previously listed AI source/test files.
- Update: `docs/superpowers/plans/2026-11-02-ai-dynamic.md` checkboxes.

- [x] **Step 1: Run required mutation checks**

Temporarily change one guard at a time: expected-version comparison, blocked-neighbor check, competing-reserve rejection, and obstacle-capacity check. Rebuild the matching test with `-j3`, observe the intended assertion RED, restore the exact source, and rebuild GREEN. Never commit a mutant.

- [x] **Step 2: Run normal and sanitizer verification**

```bash
cmake --build build-ai -j3
ctest --test-dir build-ai -R 'break_ai|test_break_nav|test_break_steer|test_break_perception|test_break_behavior|test_cry_style_prototype' --output-on-failure
cmake -S engine -B build-ai-asan -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-ai-asan -j3 --target test_break_nav_bake test_break_nav_query test_break_nav_follow test_break_perception test_break_behavior test_break_steer test_break_ai_dynamic test_break_steer_velocity test_break_ai_agents test_break_ai_formation test_break_ai_smart_object test_cry_style_prototype
ctest --test-dir build-ai-asan -R 'break_ai|test_break_nav|test_break_steer|test_break_perception|test_break_behavior|test_cry_style_prototype' --output-on-failure
cmake -S engine -B build-ai-tsan -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF -DENGINE_USE_TSAN=ON
cmake --build build-ai-tsan -j3 --target test_break_nav_bake test_break_nav_query test_break_nav_follow test_break_perception test_break_behavior test_break_steer test_break_ai_dynamic test_break_steer_velocity test_break_ai_agents test_break_ai_formation test_break_ai_smart_object test_cry_style_prototype
ctest --test-dir build-ai-tsan -R 'break_ai|test_break_nav|test_break_steer|test_break_perception|test_break_behavior|test_cry_style_prototype' --output-on-failure
```

Expected: every focused test PASS with no sanitizer diagnostic.

- [x] **Step 3: Perform read-only self-review and fix findings**

Review the complete branch diff and relevant context. Treat correctness, stale data, atomicity, memory safety, and ownership races as blocking; fix all Critical/Important findings through new RED tests and rerun affected lanes. Record that no independent reviewer was dispatched when the tool is unavailable.

- [x] **Step 4: Check and report**

Run `git diff --check`, inspect `git status --short`, confirm no mutant or build artifact is staged, and record exact commands/results, commit ids, mutation evidence, review findings, and limitations in `.superpowers/sdd/ai-dynamic-report.md`. Commit the final source/report state on `cry-wave1-ai`; do not push.
