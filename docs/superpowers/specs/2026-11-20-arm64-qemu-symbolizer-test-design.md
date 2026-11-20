# Design: arm64 ELF symbolization and its QEMU test

## Context

The arm64 lane now runs all 37 `test_break_crash` cases, but it does not build
or run `test_break_crash_symbolize`. An unmodified diagnostic build under the
same Ubuntu 24.04 multiarch/QEMU environment produced 28 passes and 16 failures
out of 44 cases. Native x86-64 execution produced 44 passes, including both
optional LLVM Mach-O toolchain checks.

The 16 emulated failures have three distinct causes:

1. `elf_from_bytes` accepts only `EM_X86_64`. Real arm64 fixtures are rejected
   before their section and symbol tables are read. This is a missing product
   capability, not merely a test environment problem.
2. ELF oracle commands hardcode `nm`, `readelf`, and `strip`. Those names are
   absent or do not describe the selected target in the minimal cross-build
   environment, although `aarch64-linux-gnu-nm`,
   `aarch64-linux-gnu-readelf`, and `aarch64-linux-gnu-strip` are already
   installed with the cross toolchain.
3. `crash_child` directly executes its newly compiled arm64 binary. The outer
   test is explicitly run by QEMU, but no binfmt registration exists for this
   nested target execution.

These causes belong to one end-to-end capability: reading arm64 ELF symbols
and proving real arm64 crash-record symbolization.

## Approaches

1. **Whitelist AArch64 ELF and inject test tools explicitly (recommended).**
   Add one native regression case for the common ELF64 symbol-table layout,
   retain the existing machine whitelist, and let the test read tool/runner
   overrides from its environment. Native defaults remain `nm`, `readelf`,
   `strip`, and direct execution. The CI step supplies cross binutils and
   `qemu-aarch64 -L /` for both the outer test and its child fixtures.
2. Install and register binfmt handlers on the runner. This would hide nested
   execution configuration, but changes host-global state, depends on runner
   privileges, and still does not fix the ELF machine rejection or tool
   selection.
3. Rewrite fixtures so their headers claim x86-64 or avoid executing them.
   That would make the harness greener while leaving real arm64 symbolization
   broken. It is not acceptable evidence.

## Product change

In `engine/src/crash/break_crash_symbolize.c`, accept exactly `EM_X86_64` and
`EM_AARCH64` for 64-bit little-endian ELF input. Both architectures use the
same `Elf64_Ehdr`, `Elf64_Shdr`, and `Elf64_Sym` layout for the operations this
reader performs. No other machine is implicitly accepted: the existing
`e_machine none` rejection and all size, bounds, section, string-table, symbol,
and build-ID checks remain unchanged.

No public interface or record format changes. `ET_EXEC`/`ET_DYN` address
handling is shared. AAPCS64 frame-pointer traversal was implemented earlier;
this slice connects real AArch64 ELF symbols to that existing traversal.

## Native regression

Add one case to `engine/tests/test_break_crash_symbolize.c` that:

- builds the existing known-symbol fixture and gets `leaf`'s address from the
  independent `nm` oracle;
- changes only `e_machine` to `EM_AARCH64`, writes the image, opens it with
  `break_elf_symbols_open`, and resolves `leaf` at the same address;
- confirms an address inside that function resolves with the same offset;
- leaves all other bytes unchanged.

The case fails before the product change because the reader returns `NULL`.
The existing invalid-machine mutation continues to pin rejection of machines
outside the whitelist. The real, compiler-generated AArch64 executable and
crash chain are verified by the QEMU run rather than claimed from this
header-level native test.

The executable consequently contains 45 named cases; the number of CTest
registrations does not change.

## AArch64 leaf-frame requirement discovered during verification

The first run with explicit tools reached 43/45: both real crash-chain cases
resolved `outer` where `mid` was expected. Disassembly showed that AArch64 GCC
omitted the faulting leaf function's `x29` frame despite
`-fno-omit-frame-pointer`; `mid` and `outer` had normal frames. The raw record
started at the caller's frame and its first return address was in `outer`.
The direct caller address remained only in `x30`, which the pinned record
format does not store.

This is the documented no-frame-pointer limitation, not a reason to weaken the
assertions or invent a frame. The fixture now calls a noinline `prepare_leaf`
before faulting. That call makes the faulting function non-leaf, so the
compiler emits its frame and the existing record contains enough evidence for
the asserted `leaf -> mid -> outer -> main` chain. No production record-field
or unwinder change is made for this fixture requirement. The following QEMU
run passed all 45 named cases; the two optional real LLVM Mach-O subchecks
reported their existing tool-absence skips.

## Test tool and nested-runner overrides

Add a small test-local setting helper. A nonempty environment value wins;
an unset or empty value selects the existing default:

| Environment variable | Default | Purpose |
|---|---|---|
| `BREAK_TEST_NM` | `nm` | Independent ELF symbol address/size oracle |
| `BREAK_TEST_READELF` | `readelf` | ELF section/build-ID oracle |
| `BREAK_TEST_STRIP` | `strip` | Produce stripped ELF fixtures |
| `BREAK_TEST_RUNNER` | empty | Command prefix for newly built crash fixtures |

Apply the first three only to GNU ELF oracle/strip commands. Keep `llvm-nm`,
`clang`, `ld64.lld`, and `llvm-lipo` unchanged: they are a separate optional
Mach-O toolchain path, not interchangeable with GNU cross binutils.

Prefix only the child fixture execution with `BREAK_TEST_RUNNER`. Compiler,
shell, file-management, and host-oracle commands are not emulated as a group.
The existing intentional `; true` after a crashing child remains: signal exit
is expected, and the following spool-count/record-read checks are the actual
assertions. The outer CI commands retain unmasked exit statuses.

Update the stale fixture comment that says the compiler is always a host
compiler; it is the configured test compiler, which may be a cross compiler.

## CI change

Extend the existing `lane-cross-aarch64-linux`; do not add another job. Build
`break_crash`, `engine`, `test_break_crash`, and
`test_break_crash_symbolize`. Keep the 37-case crash-test command unchanged,
then run the symbolizer executable once:

```sh
BREAK_TEST_NM=aarch64-linux-gnu-nm \
BREAK_TEST_READELF=aarch64-linux-gnu-readelf \
BREAK_TEST_STRIP=aarch64-linux-gnu-strip \
BREAK_TEST_RUNNER='qemu-aarch64 -L /' \
timeout 240 qemu-aarch64 -L / ./build-arm64/test_break_crash_symbolize
```

The cross binutils are host programs that read AArch64 files; they do not need
to be arm64 executables. The runner prefix is inherited by the test's shell
children and explicitly launches each new arm64 crash fixture with the same
multiarch filesystem root as the outer test.

No retries, `|| true`, test filtering, or blanket binfmt registration. A build
failure, timeout, failed assertion, or missing required ELF tool fails the job.
The two LLVM Mach-O toolchain subchecks retain their existing conditional skip
behavior when those optional tools are absent; their synthetic Mach-O checks
still run, and native verification covers the real LLVM tools when available.

## Documentation

Update the build guide, implementation status, crash-symbolization design,
and missing-capabilities inventory to distinguish:

- native header-level AArch64 ELF coverage plus real x86-64 coverage;
- 37 QEMU crash-handler cases and 45 QEMU symbolizer cases;
- any optional LLVM subcheck skips reported by the actual QEMU log;
- the remaining absence of a full arm64 `ctest`, GPU execution, and
  physical-device evidence.

Narrow the two earlier arm64 specs' deferred-symbolizer statements by linking
this follow-up while preserving their original scope and results. Update the
cross toolchain's stale build-only introductory comment. Do not overwrite
unrelated historical documentation.

## Verification

1. Run the new native AArch64 ELF case before the product edit and observe its
   failure; run the complete native symbolizer executable after the edit.
2. Retain the recorded unmodified QEMU result: 28 passed, 16 failed. After the
   product edit but before harness overrides, use the emulated run to isolate
   the remaining tool/runner failures.
3. Apply the test-local overrides and run the real cross-compiled symbolizer
   under QEMU with the exact intended environment. Require all 45 named cases
   to report success, while recording any optional LLVM subcheck skips.
4. Extend the YAML contract to require the fourth build target, both QEMU
   commands, all four environment overrides, and no masked status.
5. Execute the resulting CI run scripts in a clean Ubuntu 24.04 container and
   run the complete native `build-core-app-net` suite after remote integration.
6. Push directly to `master` and require the actual remote arm64 job and both
   QEMU steps to succeed. Record the run/job URL and exact remote summaries.

## Out of scope

A full emulated CTest run, other ELF architectures, DWARF CFI, Windows SEH/PE,
physical arm64 hardware, GPU execution, and production crash-service deployment
remain outside this slice.
