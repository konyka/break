# Design: security and cryptography tests on arm64 with QEMU

## Context

Fourteen crash/HTTP/update tests already run in the arm64 lane. Six remaining
security/cryptography tests extend that selection to 20:

- `test_break_crypto` (20 cases);
- `test_break_crypto_target_contract` (archive inspection plus generated link check);
- `test_break_keygen` (host CMake driver, including RLIMIT and concurrency);
- `test_break_integrity` (8 cases);
- `test_break_authority` (14 cases);
- `test_break_authority_target_contract` (two archive inspections).

The unmodified cross/QEMU baseline passed crypto 20/20 and authority 14/14.
Integrity passed seven cases and failed only `a_traced_process_reports_the_debugger_bit`.
Keygen failed when the host shell directly executed its arm64 binary; both
contracts failed at missing `nm`.

QEMU target-syscall tracing established the integrity cause precisely:
`PTRACE_TRACEME` returns `-1 ENOSYS` (errno 38), the child exits 90, and the
parent sees an exit rather than `WIFSTOPPED`. The product debugger check is not
on that failing path. Native ptrace-positive coverage must remain mandatory.

## Approaches

1. **Reuse runner/NM inputs and isolate the emulator-only ptrace setup gap
   (recommended).** Keep native tests strict, make only the known QEMU setup
   failure conditional, and preserve all product-result failures.
2. Exclude the integrity executable entirely. This would discard seven valid
   arm64 cases and is not acceptable.
3. Claim the ptrace-positive case passed without executing it, or weaken native
   behavior. Both create false evidence and are rejected.

## Runner and archive plumbing

Add four build targets: `test_break_crypto`, `test_break_integrity`,
`test_break_authority`, and `break_keygen`. The three test executables use the
existing `CMAKE_CROSSCOMPILING_EMULATOR` automatically.

Forward `"-DTARGET_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"` to keygen. Its
normal `keygen` helper uses direct CMake list expansion. Also create a
shell-quoted prefix by independently escaping each runner element, and apply it
to the two direct shell launches: the RLIMIT_FSIZE `exec` and the concurrent
12-process loop. Host `ls`, `chmod`, `head`, and shell control remain native.
Key permissions, no-overwrite rules, ring limits, symlink handling, short-write
atomicity, and concurrency assertions stay unchanged.

For the crypto contract, forward `CRYPTO_CONTRACT_NM=${CMAKE_NM}` and
`CRYPTO_CONTRACT_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}`. Prefix only the
generated `crypto_link_check` executable. For the authority contract, forward
`NM=${CMAKE_NM}`; it executes no target program. Exact exports, no-link rules,
and the authority/integrity trust boundary remain intact.

## Explicit QEMU-only ptrace setup skip

In the traced-child test, after the first `waitpid`, detect only this exact
condition:

- `WIFEXITED(status)` is true;
- `WEXITSTATUS(status) == 90`, the existing child code for `PTRACE_TRACEME`
  setup failure;
- `BREAK_TEST_QEMU_USER=1` is explicitly present in the test environment.

Then print `skipped (QEMU user has no PTRACE_TRACEME)` and return from that one
case. The child has already exited, so no continue/wait cleanup is needed.

Without the explicit environment value, behavior is unchanged and native setup
failures remain red. Exit 91 (the product returned the wrong debugger signal),
unexpected exits, `PTRACE_CONT` failures, and all later assertions remain red.
The normal no-tracer case and all file/module integrity cases still execute on
arm64. CI and documentation must report this one setup skip; an 8/8 named-case
summary is not evidence that ptrace-positive behavior ran under QEMU.

## Unified 20-test CI selection

Add `BREAK_TEST_QEMU_USER=1` to the existing CTest environment and extend the
regex to:

```sh
-R '^(test_break_crash|test_break_update|test_break_http|test_break_manifest_tool|test_break_crypto|test_break_keygen|test_break_integrity|test_break_authority)'
```

The exact current selection is the previous 14 plus the six named tests: 20.
Build 20 targets total (16 existing plus four new). Use generic display names
`Linux arm64 cross-build + QEMU tests (GCC)` and `Run selected tests under QEMU`
so later evidence expansion does not require misleading subsystem-specific
names. Keep the job key, emulator configuration, 300-second outer timeout, and
all existing test inputs unchanged.

`--no-tests=error` remains mandatory. No retry, output filtering, global binfmt,
or masked status is added.

## TDD and verification

1. Retain the baseline and `ENOSYS`/exit-90 trace as RED evidence.
2. Add the runner/NM plumbing and explicit setup skip. Native focused six tests
   must pass with the ptrace-positive case actually executing (no skip message).
3. Run the cross focused six before editing CI. Require crypto 20/20, authority
   14/14, integrity 8/8 with exactly the one explicit QEMU setup skip, keygen
   success, and both contracts. Assert that no exit-91 skip exists.
4. Run a YAML + actual native-selection contract before the workflow edit;
   require RED on the old display name/missing targets/20-test regex and GREEN
   afterward with exactly 20 selected names.
5. Run the complete native suite after integration: 455 tests, zero failures,
   four established platform skips. Confirm native keygen RLIMIT/concurrency and
   ptrace-positive behavior still execute.
6. Run final CI scripts in a clean Ubuntu container, request read-only review,
   push directly to `master`, and assert the real remote arm64 job's 20/20
   result and all old/new case summaries. Record the one QEMU ptrace setup skip
   and do not call it positive runtime evidence.

## Documentation and limits

Update the build guide, implementation status, client-integrity and server-
authority designs, and missing-capabilities inventory. The combined selection
covers every current `security`-label test plus the additional crypto/update/
crash tests, but it is still not a full arm64 CTest run.

No GPU or physical-device evidence is provided. Client anti-debugging remains
an auxiliary signal, never an authorization input. Production authority
persistence/provisioning, Windows support, and other subsystem gaps remain open.
