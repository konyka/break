# Design: the complete crash test family on arm64 with QEMU

## Context

The arm64 lane currently builds four targets and directly runs
`test_break_crash` (37 cases) and `test_break_crash_symbolize` (45 cases). The
native `crash` label contains six tests, including
`test_break_crash_target_contract`; the related server archive contract is a
seventh test outside that label.

An unmodified Ubuntu 24.04 multiarch/QEMU diagnostic built the remaining
binaries and produced this baseline:

- `test_break_crash_cluster`: 26/26 passed under direct QEMU execution.
- `test_break_crash_upload_http`: 8/8 passed, including its real loopback TLS
  test server and spool retry behavior.
- `test_break_crash_target_contract`: failed because its host-side script could
  not find a suitable `nm`; after export inspection it also compiles and runs a
  new target-architecture link-check executable.
- `test_break_crash_server_target_contract`: failed for the same missing `nm`.
- `test_break_crash_e2e`: failed before setup because the host CMake driver
  directly executed the arm64 client as a shell script.

The remaining gap is therefore harness plumbing, not another ELF parser or
network feature. The goal is to execute all six `crash`-label tests plus the
server contract without weakening their checks.

## Approaches

1. **Use CMake's cross emulator and one complete CTest selection
   (recommended).** Configure `CMAKE_CROSSCOMPILING_EMULATOR` only in the CI
   cross build. Pass the same optional runner into host-driven nested tests,
   pass `CMAKE_NM` into both archive contracts, and replace the two direct
   executable commands with one verbose seven-test CTest selection.
2. Add separate hand-written QEMU commands for every binary and every CMake
   driver. This avoids changing the configure command but duplicates paths and
   runner settings, makes omissions more likely, and leaves the generated CTest
   registrations unusable for cross execution.
3. Register binfmt handlers globally. This hides execution but requires host
   privileges and still does not select the cross `nm`; it is unnecessary and
   less explicit.

## Cross configuration

Extend the existing CI Configure command with:

```sh
'-DCMAKE_CROSSCOMPILING_EMULATOR=/usr/bin/qemu-aarch64;-L;/'
```

The toolchain file remains generic and does not hardcode QEMU or a sysroot.
CMake uses this list for tests registered with executable targets. The value is
also forwarded to host-side CMake scripts that launch target programs
indirectly. Native builds leave it unset, producing empty optional prefixes and
preserving direct execution.

The existing `AARCH64_SYSROOT=/`, multiarch `PKG_CONFIG_LIBDIR`, OpenGL
compile-only configuration, job key, packages, and object checks stay unchanged.

## Archive contracts

For `test_break_crash_target_contract`, add these test-registration inputs:

```cmake
-DCRASH_CONTRACT_NM=${CMAKE_NM}
"-DCRASH_CONTRACT_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Its existing `find_program(CRASH_CONTRACT_NM ...)` retains native fallback
semantics when no override is supplied. Prefix only the final generated
`crash_link_check` execution with `CRASH_CONTRACT_RUNNER`; compilation still
uses the existing configured `CRASH_CONTRACT_CC`. Export counts, exact symbol
lists, no-link requirements, golden bytes, spool checks, and all return-code
assertions remain unchanged.

For `test_break_crash_server_target_contract`, pass:

```cmake
-DNM=${CMAKE_NM}
```

No target program is executed by that script. Its four archive inspections and
source-contract checks remain unchanged.

Both `nm` values name host binutils programs that understand the selected
archive format. They are not target executables and must not be prefixed with
QEMU.

## End-to-end driver

Add optional `TARGET_RUNNER`, a CMake list, to
`engine/tests/test_break_crash_e2e.cmake`. Forward it from the test registration
with:

```cmake
"-DTARGET_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Apply it as follows:

- `client`: `execute_process(COMMAND ${TARGET_RUNNER} "${CLIENT}" ...)`;
- `report`: the same prefix before `"${REPORT}"`;
- direct `run(TRUE "${CLIENT}" ...)` calls: expand the runner list before the
  client path;
- `start_server`: shell-quote each list element separately (including embedded
  single quotes) solely for its existing quoted shell launch, then launch
  `"${SERVER}"` through that prefix. Element boundaries and whitespace must be
  preserved.

Do not prefix the host CMake process, shell utilities, file operations, or
`nm`. Do not change ports, certificate checks, HTTP assertions, retry counts,
record rejection cases, regression reporting, or server cleanup. The existing
root-only skip for the unwritable-statistics case remains explicit; local root
containers and the non-root remote runner may therefore exercise different
case-11 paths, which must be recorded rather than hidden.

No production source or public API changes are planned. The existing
`break_crash_e2e` target already uses `-O0` and `-fno-omit-frame-pointer`;
if real arm64 execution exposes a fixture-specific issue, it must be diagnosed
from the actual record and instructions as in the symbolizer slice, not hidden
by reducing the server-log assertions.

## Unified CI test execution

Build these nine targets so every selected test and host-driven tool exists:

```text
break_crash engine test_break_crash test_break_crash_symbolize
test_break_crash_cluster test_break_crash_upload_http
break_crash_server break_crash_report break_crash_e2e
```

Retain `qemu-aarch64 --version`, then replace the two direct test commands with:

```sh
BREAK_TEST_NM=aarch64-linux-gnu-nm \
BREAK_TEST_READELF=aarch64-linux-gnu-readelf \
BREAK_TEST_STRIP=aarch64-linux-gnu-strip \
BREAK_TEST_RUNNER='qemu-aarch64 -L /' \
timeout 300 ctest --test-dir build-arm64 --verbose --no-tests=error \
  -R '^test_break_crash'
```

The selection must contain exactly seven tests:

1. `test_break_crash`;
2. `test_break_crash_target_contract`;
3. `test_break_crash_symbolize`;
4. `test_break_crash_cluster`;
5. `test_break_crash_upload_http`;
6. `test_break_crash_server_target_contract`;
7. `test_break_crash_e2e`.

The first, third, fourth, and fifth use CMake's executable-target emulator.
The two contracts and the end-to-end test run their host CMake drivers with the
explicit tool/runner inputs above. `--no-tests=error` prevents an empty
selection from passing. Verbose mode preserves the real 37/45/26/8 summaries
and contract/e2e status messages. Individual CTest timeouts and the outer
300-second limit remain active; no retry, output filtering, or status masking
is allowed.

## TDD and verification

1. Retain the observed baseline: 26/26 and 8/8 pass, both contracts fail at the
   `nm` gate, and e2e fails at direct target execution.
2. Add optional runner/tool plumbing without changing native defaults. Run the
   native focused tests to prove direct behavior remains intact.
3. Configure a cross tree with the exact emulator list and execute the intended
   seven-test CTest command before editing CI. Require all seven tests to pass;
   inspect actual case summaries and e2e privilege-dependent behavior.
4. Run a YAML contract before the workflow edit and require it to fail on the
   missing emulator/build/CTest configuration. After the minimal CI edit, the
   same contract must pass and must enumerate all nine targets and seven test
   names.
5. Run the complete native `build-core-app-net` suite after integration. It must
   retain 455 registered tests with zero failures and the four established
   platform skips.
6. Execute the final CI scripts in a clean Ubuntu 24.04 container, push directly
   to `master`, and require the remote arm64 job's real seven-test selection to
   succeed. Record exact local and remote privilege-dependent e2e behavior.

## Documentation and limits

Update the build guide, implementation status, crash-symbolization design, and
missing-capabilities inventory with complete crash-family evidence. Earlier
specs remain historical and may link this follow-up where their boundaries are
superseded.

This is still not a full arm64 `ctest`: only the seven named crash tests are
selected. It provides no GPU or physical-device evidence and does not implement
minidump/PE, Windows SEH, DWARF CFI, production crash-service deployment, or
other engine subsystems.
