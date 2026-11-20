# arm64 QEMU Headless World Tests Design

## Context

The arm64 lane selects exactly 164 tests. All fifteen tests labelled
`headless;world` remain outside it. This slice adds exactly those fifteen for a
179-test selection. The two `graphics;world` tests (`test_mesh_gpu_gl`,
`test_world_presentation_gl`) need a GPU context and stay out.

## Approaches

1. Extend the lane by name. Recommended: all fifteen are direct executables
   with generated QEMU commands.
2. Select by label (`-L world -LE graphics`). Rejected: the lane selects by
   name, and mixing `-L` with the existing `-R` would change selection
   semantics for every earlier test.
3. Add a separate lane. Rejected: duplicates the multiarch setup.

## Existing Behavior and Baseline

| Test | Cases | Links |
|---|---|---|
| `test_vegetation`, `test_time_of_day`, `test_visarea`, `test_world_stream` | 1 each | one renderer source + `math.c`, `m` (`engine/CMakeLists.txt:5723`) |
| `test_decal`, `test_voxel`, `test_road` | 1 each | one renderer source + `math.c`, `m` |
| `test_mesh_stage` | 1 | `m` |
| `test_mesh_buffer` | 3 | `m` |
| `test_mesh_gpu` | 1 | `engine_rhi_headless`, `m` |
| `test_world_mesh_fake` | 4 | fake RHI (`tests/world_fake_rhi.c`), `m` |
| `test_world_presentation` | 5 | `m` |
| `test_world_presenter_fake` | 5 | fake RHI, `m` |
| `test_world_stream_job` | 1 | task system (one worker), `pthread m` |
| `test_world_stream_world` | 2 | `pthread m`; writes files under its `test_tmp()` root |

That is 29 cases. None fork or use a GPU or device. Native focused passes all
fifteen with these counts. Unmodified cross focused in a clean Ubuntu 24.04
container passes 15/15 with the same counts in 0.29 seconds. No product or
test-source change is needed.

## CI Change

Append the fifteen executable targets after `test_break_flow_runtime` and add:

```text
test_(vegetation|time_of_day|visarea|decal|voxel|road)$|test_world_(stream(_job|_world)?|mesh_fake|presentation|presenter_fake)$|test_mesh_(stage|buffer|gpu)$
```

The `$` on each part rejects `test_mesh_gpu_gl` and
`test_world_presentation_gl`.

## TDD and Verification

1. Contract against the old workflow: fifteen build targets, the exact
   alternative, rejection of the two `_gl` tests and derived names; previous
   164 plus these fifteen = 179. RED.
2. Apply the edits; GREEN on the explicit 179-name set.
3. Focused native with the new `-R`: 15/15.
4. Native full: 456, zero failures, four established skips.
5. Clean-container workflow: 179/179, exactly one ptrace setup skip.
6. Independent review, push, and assert the exact-HEAD remote log with all
   fifteen per-test counts.

## Boundaries

A selected 179-test suite, not full arm64 CTest. GPU presentation
(`*_gl`) and real-device rendering remain outside it. Ten of the fifteen
executables have a single case, so a failure inside one reports as one case.
