# core_app P12 remaining verification register closure (2026-11-15)

Source: `docs/Implementation_Status.md` "2026-11-11 P12 remaining verification register".

## Task A: bounded IO wait fault injection

- [x] Preload: `CORE_APP_TEST_FAIL_QUIESCED_FLUSH` fails the `fflush` after the `event=io_quiesced` trace line with `EIO`.
- [x] `run_fault_app` accepts an optional extra `VAR=value` environment entry (ARGV6).
- [x] `io_quiesced_eio`: slow BSCN read (6 s) + quiesced flush failure must exit 2 with `runtime_fault stage=bscn`, no `load_rejected ... stage=bscn`, and no later frame.
- [x] `io_second_wait_fail`: a worker blocked longer than the whole process lifetime makes the second bounded wait fail; exit 2, `runtime_fault stage=bscn`, no `io_quiesced`, and no `io_stopped active=0` (a blocked worker is never reported as joined).
- [x] Mutation check: dropping `*runtime_fatal = true` in either `stage_bscn` branch turns the matching case red.

## Task B: baker identity assertions

- [x] Explicit assertions for the Flow subject identity field and the exec-link source port in the asset bake test.

## Docs

- [x] Append a 2026-11-15 closure note under the register in `docs/Implementation_Status.md`, plus a section in `docs/design/core_app_integration.md`.
