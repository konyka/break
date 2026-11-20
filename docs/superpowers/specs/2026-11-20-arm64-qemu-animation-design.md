# arm64 QEMU Animation Tests Design

## Context

The arm64 lane selects exactly 86 tests. The eight registered animation tests
remain outside it: `test_animation`, `test_anim_pose_authority`,
`test_anim_morph`, `test_anim_facial`, `test_anim_compression`,
`test_anim_locomotion`, `test_skeleton_socket`, and `test_anim_aim`. This slice
adds exactly those eight for a 94-test selection.

## Approaches

1. Extend the existing lane with the eight direct executable tests and one new
   locally anchored alternative. Recommended: it reuses the generated QEMU
   commands.
2. Select by the `animation` CTest label. Rejected: the lane selects by name, and
   `test_animation` has no label.
3. Add a separate lane. Rejected: it duplicates the multiarch setup.

## Existing Behavior and Baseline

All eight are direct executable registrations (`engine/CMakeLists.txt:7568-7622`)
that link only animation, math, log, and LOD CPU sources (`test_anim_morph` also
links `meshopt_c`). They need no GPU, window system, or device.

| Test | Cases |
|---|---|
| `test_animation` | 37 |
| `test_anim_pose_authority` | 2 |
| `test_anim_morph` | 10 |
| `test_anim_facial` | 8 |
| `test_anim_compression` | 13 |
| `test_anim_locomotion` | 1 |
| `test_skeleton_socket` | 1 |
| `test_anim_aim` | 1 |

Unmodified native focused execution passes 8/8; unmodified cross focused
execution in a clean Ubuntu 24.04 container passes 8/8 with the same case counts
(CTest 0.17 seconds). No product or test-source change is needed.

## CI Change

Append the eight targets to the arm64 build command after `test_character`, and
add this alternative without editing earlier ones:

```text
test_(animation|anim_(pose_authority|morph|facial|compression|locomotion|aim)|skeleton_socket)$
```

The outer `^(` anchor keeps `test_myui_echart_animation` out; the `$` binds the
whole group so derived names such as `test_animation_extra` are rejected.

## TDD and Verification

1. Selection contract against the old workflow: require the eight build targets,
   the exact alternative, rejection of derived names, and previous 86 plus these
   eight = 94. Observe RED.
2. Apply the build-list and regex edits; require GREEN on the explicit 94-name set.
3. Re-run native and cross focused; require 8/8 and the case counts above.
4. Native full regression: 455 tests, zero failures, four established skips.
5. Clean-container workflow run blocks: 94/94 and exactly one ptrace setup skip.
6. Independent read-only review, push, and assert the exact-HEAD remote log.

## Boundaries

This is a selected 94-test suite, not full arm64 CTest. GPU skinning, rendering,
retargeting assets, and cross-architecture bit-exact animation playback remain
outside it. Locomotion, socket, and aim each have a single case, so a failure
there reports as one case regardless of how many checks it contains.
