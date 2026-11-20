# arm64 QEMU Kernel and Flow Tests Design

## Context

The arm64 lane selects exactly 152 tests. The twelve tests registered by the
kernel and flow blocks (`engine/CMakeLists.txt:4944-4981`) remain outside it:
eight `test_break_kernel_*` executables, the host-side
`test_break_kernel_target_contract`, and three `test_break_flow_*` executables.
This slice adds exactly those twelve for a 164-test selection.
`test_break_kernel_lua` is already selected and is unaffected.

## Approaches

1. Extend the lane by name. Recommended: direct executables with generated
   QEMU commands, plus one host contract like other selected contracts.
2. Select by label (`break_kernel`, `break_flow`). Rejected: the lane selects
   by name.
3. Add a separate lane. Rejected: duplicates the multiarch setup.

## Existing Behavior and Baseline

The kernel executables link `break_kernel` (which itself depends on
`break_ecs_replication`); the flow executables link `break_flow`; both add
`pthread m` on Linux. `test_break_kernel_level` writes one sidecar file next to
its per-process `test_tmp()` path and removes it. None fork, start threads, or
use devices.

| Test | Cases | Test | Cases |
|---|---|---|---|
| `test_break_kernel_actor` | 6 | `test_break_kernel_area` | 2 |
| `test_break_kernel_items` | 5 | `test_break_kernel_flow` | 4 |
| `test_break_kernel_weapons` | 16 | `test_break_flow_graph` | 8 |
| `test_break_kernel_actions` | 1 | `test_break_flow_serial` | 6 |
| `test_break_kernel_move` | 1 | `test_break_flow_runtime` | 12 |
| `test_break_kernel_level` | 1 | | |

That is 62 cases in eleven executables. Native focused passes with these
counts. Unmodified cross focused in a clean Ubuntu 24.04 container passes 12/12
with the same counts in 0.73 seconds, so the lane's 600-second guard is not a
concern. No product or test-source change is needed.

## CI Change

Append the eleven executable targets after `test_rule_engine_backward_bindings`
and add:

```text
test_break_kernel_(actor|items|weapons|actions|move|level|area|flow|target_contract)$|test_break_flow_(graph|serial|runtime)$
```

## TDD and Verification

1. Contract against the old workflow: eleven build targets, the exact
   alternative, rejection of derived names; `test_break_kernel_lua` still
   selected; previous 152 plus these twelve = 164. RED.
2. Apply the edits; GREEN on the explicit 164-name set.
3. Focused native with the new `-R`: 12/12.
4. Native full: 456, zero failures, four established skips.
5. Clean-container workflow: 164/164, exactly one ptrace setup skip.
6. Independent review, push, and assert the exact-HEAD remote log with all
   eleven per-test counts.

## Boundaries

A selected 164-test suite, not full arm64 CTest. Three kernel executables
(actions, move, level) have one case each and `test_break_kernel_area` has
two, so their coverage is thin. The target contract
checks build wiring, not arm64 behavior. `test_core_app_lifecycle_script_flow`
and `test_editor_flow` are the only other registry names containing kernel or
flow; they belong to the core_app and editor families and stay out.
