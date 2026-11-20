# arm64 QEMU Lane Time Budget Design

## Context

The arm64 lane runs its 152 selected tests serially under one outer
`timeout 300 ctest ...` guard. The exact-HEAD remote run for the rule-engine
slice (job 136297883692) took 171.23 seconds of CTest time, 57% of that guard.
The per-test sum is 171.03 seconds; `test_break_http` alone takes 66.12 seconds
under QEMU (10.6 seconds natively), followed by `test_break_crash_e2e` (27.24 s)
and `test_break_update_e2e` (14.46 s). The whole job took 4 minutes 45 seconds
against its `timeout-minutes: 25` cap.

The outer guard exists to stop a hung run, not to bound normal work. With 57%
already used, normal variance in the slow network tests, or the next family
slices, could trip it and fail the lane without any test failing.

## Approaches

1. Raise the outer guard to 600 seconds. Recommended: one number, keeps serial
   execution, and a hang still ends at 10 minutes, well inside the 25-minute
   job cap.
2. Run CTest in parallel (`-j`). Rejected: parallel host load is exactly what
   reproduces the known qemu-user fork-then-thread hang in `test_runtime_io`
   (5 of 180 runs at 12-way parallelism, 0 of 60 serial).
3. Split the lane. Rejected for now: doubles the multiarch setup (about 50 s)
   without need at this size.

## Change

Replace `timeout 300 ctest` with `timeout 600 ctest` in the lane run block and
the mirrored `docs/Build_Guide.md` command. Nothing else changes: selection,
per-test CTest `TIMEOUT` properties, and the 25-minute job cap stay as they are.
135 of the 152 selected tests set no CTest timeout and inherit the 1500-second
DartConfiguration default, so the outer guard is the only bound on them.

## TDD and Verification

1. Contract: the run block contains exactly one `timeout 600 ctest`, no
   `timeout 300`, the job keeps `timeout-minutes: 25`, the 152-name selection is
   unchanged, and the guide command matches. RED on the old workflow.
2. Apply the edit; GREEN.
3. Clean-container workflow run: 152/152, exactly one ptrace setup skip.
4. Push and confirm the exact-HEAD remote job succeeds with 152 tests.
