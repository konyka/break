# Design: core_app network unit and offline tests on arm64 with QEMU

## Context

The arm64 lane selects 31 tests. Two core_app network tests are available in
the current non-Snowflake cross configuration:

- `test_core_app_network`: a direct executable with 25 cases;
- `test_core_app_network_offline`: a host CMake driver that runs the real
  `core_app` twice for deterministic offline traces and inspects its archive
  symbols with the already-forwarded target-aware `NM`.

The unmodified cross baseline passed the direct test 25/25. Offline failed
because its host driver directly executed the arm64 `core_app` (`Exec format`
shell diagnostics). `NETWORK_TRANSPORT=OFF`, `NM=aarch64-linux-gnu-nm`, and
`NM_CAPABLE=TRUE` are already correct; no skip 77 is expected.

Other core_app loopback/voice/start-failure tests are not registered in this
cross configuration because `_core_app_net_transport` requires Snowflake. They
must not be selected by the new regex or counted as skipped/passed.

## Approaches

1. **Add a dedicated core_app runner and exact two-test regex (recommended).**
   Minimal change, native defaults unchanged, no selection of unavailable
   Snowflake scenarios.
2. Enable Snowflake to run all core_app network modes. That is a separate
   dependency project and unnecessary for these two independent tests.
3. Select the `test_core_app_network` prefix indiscriminately. This would add
   every native loopback/voice scenario to the supposed 33-name selection and
   create misleading coverage, so it is rejected.

## Runner change

Forward `"-DCORE_APP_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"` to the offline
registration. In `test_core_app_network.cmake`, prefix every direct `CORE_APP`
launch with that optional CMake list:

- both offline `run_offline` executions;
- the start-failure helper (native behavior unchanged);
- the server `CORE_APP` command in the multi-command network launch.

Do not prefix `NM`, host CMake, `NET_CLIENT`, `TRACE_CONVERT`, or `TRACE_MERGE`
in this slice. Those other target tools belong to the later Snowflake loopback
project and are not needed offline. Empty native runner values preserve direct
execution.

## CI selection

Append `test_core_app_network` and `core_app` to the build command. Add the
single regex alternative:

```text
test_core_app_network(_offline)?
```

It selects exactly the unit and offline tests in both native and cross trees,
not `_loopback`, `_single_session`, voice modes, or `test_core_app_net_transport`.
The exact current selection becomes 33 tests: previous 31 plus these two.

Keep generic names, emulator/environment, `--verbose`, `--no-tests=error`,
300-second outer timeout, packages, job key, and object checks unchanged. No new
skip, dependency, retry, filter, or status mask is added.

## TDD and verification

1. Retain the RED baseline: direct unit 25/25, offline direct-exec failure.
2. Add the optional core_app runner. Native focused two tests must pass with
   direct execution and no new skip.
3. Run the cross focused two before editing CI; require unit 25/25, deterministic
   offline traces, no-network symbol scan, and two-test CTest success.
4. Before CI editing, require the two new targets, exact `(_offline)?`
   alternative, and actual native selection previous 31 + exactly two = 33;
   observe RED on the old build command.
5. Apply only build/regex changes and rerun for GREEN. Confirm native loopback
   and voice names are absent from the selection.
6. Run native full 455 tests with zero failures/four established skips, final
   clean-container 33/33, independent review, and direct `master` push.
7. Assert the real remote arm64 job's 33/33 and 25-case unit summary; record
   offline success and exactly one existing integrity setup skip.

## Documentation and limits

Update the build guide, implementation status, core-app integration design, and
missing-capabilities inventory. Do not claim core_app loopback/voice transport,
Snowflake/QUIC, production deployment, full arm64 CTest, GPU, or physical-device
evidence.
