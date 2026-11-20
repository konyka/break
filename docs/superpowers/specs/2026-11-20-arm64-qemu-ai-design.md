# arm64 QEMU AI Tests Design

## Context

The arm64 lane selects exactly 94 tests. The fourteen tests registered by the
`break_ai` block (`engine/CMakeLists.txt:5690-5705`) remain outside it. This slice
adds exactly those fourteen for a 108-test selection.

## Approaches

1. Extend the existing lane by name with the twelve executables and the two
   CMake-script contracts. Recommended: reuses the generated commands.
2. Select by the `break_ai` label. Rejected: the lane selects by name, and the
   label also covers `test_core_style_prototype`, which belongs to another family.
3. Add a separate lane. Rejected: duplicates the multiarch setup.

## Existing Behavior and Baseline

Twelve executables come from one `foreach` and link only `break_ai`:

| Test | Cases |
|---|---|
| `test_break_nav_bake` | 3 |
| `test_break_nav_query` | 3 |
| `test_break_nav_query_concurrent` | 2 |
| `test_break_nav_follow` | 1 |
| `test_break_perception` | 1 |
| `test_break_behavior` | 1 |
| `test_break_steer` | 1 |
| `test_break_ai_dynamic` | 6 |
| `test_break_steer_velocity` | 6 |
| `test_break_ai_agents` | 2 |
| `test_break_ai_formation` | 5 |
| `test_break_ai_smart_object` | 3 |

`test_break_ai_target_contract` and `test_break_ai_hot_path_contract` run host
`cmake -P` scripts over source files; they check target wiring and hot-path
rules, not arm64 behavior, and are included because the lane already runs other
host-side target contracts.

Unmodified cross focused execution in a clean Ubuntu 24.04 container passes all
14 with the counts above (CTest 0.37 seconds); `test_break_nav_query_concurrent`
runs real threads under QEMU. Native focused also passes. No product or
test-source change is needed.

## CI Change

Append the twelve executable targets after `test_anim_aim` and add:

```text
test_break_(nav_(bake|query|query_concurrent|follow)|perception|behavior|steer(_velocity)?|ai_(dynamic|agents|formation|smart_object|target_contract|hot_path_contract))$
```

The `$` binds the whole group, so derived names are rejected.

## TDD and Verification

1. Contract against the old workflow: twelve build targets, the exact
   alternative, rejection of derived names and `test_core_style_prototype`, and
   previous 94 plus these fourteen = 108. Observe RED.
2. Apply the edits; require GREEN on the explicit 108-name set.
3. Focused native and cross: 14/14 with the counts above.
4. Native full: 455, zero failures, four established skips.
5. Clean-container workflow: 108/108, exactly one ptrace setup skip.
6. Independent review, push, and assert the exact-HEAD remote log with every
   per-test count.

## Boundaries

A selected 108-test suite, not full arm64 CTest. Navmesh assets from real
levels, large-crowd performance, and editor AI tools remain outside it. Four
executables have a single case each: nav follow, perception, behavior, and steer.
