# Design: run the crash tests on arm64 with QEMU

## Context

`lane-cross-aarch64-linux` now cross-compiles `break_crash` and `engine` and
checks the object architecture. It does not execute target code. The missing
evidence is whether Linux arm64 signal delivery, `ucontext` register capture,
spool recovery and redaction work together.

A Ubuntu 24.04 container with the same multiarch layout has already run the
arm64 `test_break_crash` twice under `qemu-aarch64 -L /`: all 37 tests passed,
including real SIGSEGV and SIGABRT record capture. This is the narrow runtime
gap this design closes.

## Approaches

1. **Extend the existing lane with `test_break_crash` (recommended).** Install
   `qemu-user`, build the test beside the existing targets and run it once.
   This reuses the compiler, sysroot and target libraries without a second
   dependency-install job.
2. A separate QEMU job with build artifacts. This separates build and runtime
   evidence but duplicates artifact handling and makes the crash test wait for
   another job; the existing lane already has everything needed.
3. Run all tests, or all crash-related tests, under QEMU. The full suite is
   outside this evidence gap. In particular, `test_break_crash_symbolize`
   invokes target tools and executes newly built arm64 fixture programs from
   inside the emulated test; nested target execution and target `nm`/`strip`
   setup belong to a separate design.

## Change

Keep the job key `lane-cross-aarch64-linux` stable and make its display name
say that it includes QEMU crash tests.

In the existing dependency step, add the host package `qemu-user`. In the
build step, add `test_break_crash` to the existing target list; `break_crash`
and `engine` continue to be built, so this adds runtime evidence without
replacing compile/link coverage.

After the object-architecture check, add a step equivalent to:

```sh
qemu-aarch64 --version
timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash
```

`-L /` matches the Ubuntu multiarch target filesystem already used by the
configure step. `timeout` turns a hung emulator or test into a failed job.
The test's own exit status is unmasked: any failed assertion fails the lane.
No output filtering or retry converts a failure into success.

## Evidence and limits

The new evidence is an emulated Linux arm64 execution of record construction,
bounded spool behavior, real signal capture, context blobs, recovery upload
and redaction. It directly exercises the `uc_mcontext.pc`, `.sp` and
`.regs[29]` path on an aarch64 process.

It is not physical-hardware evidence, a full arm64 `ctest`, or GPU validation.
The original slice did not run `test_break_crash_symbolize`; its nested
execution and target-tool requirements were deferred rather than silently
skipped. The follow-up
[arm64 symbolizer design](2026-11-20-arm64-qemu-symbolizer-test-design.md)
adds that suite explicitly. The existing native x86-64 suite remains
responsible for the broader regression net.

## Documentation

Update `docs/Build_Guide.md`, `docs/Implementation_Status.md`,
`docs/design/crash_symbolization.md` and
`docs/cross_engine/missing_capabilities.md` to distinguish:

- arm64 compile/link evidence for `break_crash` and `engine`;
- QEMU arm64 runtime evidence for `test_break_crash`;
- the originally unrun arm64 symbolizer suite and physical-device testing.

The current documents also record the follow-up symbolizer delivery instead
of continuing to list it as missing.

Update the existing arm64 build-lane spec's out-of-scope statement so it no
longer claims that all arm64 test execution is deferred.

## Verification

The configuration change is test-driven at the CI contract level: before the
change, a YAML assertion requiring a QEMU crash-test step fails. After the
change, the same assertion passes. Then execute the exact CI run scripts in a
clean Ubuntu 24.04 container, including the 37 arm64 tests and the existing
engine build. Run the native full suite after integration, push to `master`, and require the remote arm64 job to report success.
