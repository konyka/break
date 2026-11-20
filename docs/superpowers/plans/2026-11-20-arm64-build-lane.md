# Plan: an arm64 cross-build lane

Spec: `docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md`.

1. **GREEN (toolchain)**: `engine/toolchain-aarch64-linux.cmake` with the
   cross tools, a sysroot (overridable by `AARCH64_SYSROOT`) and the
   find-root modes that keep CMake off the host's libraries.
2. **GREEN (CI)**: `lane-cross-aarch64-linux` installs the cross gcc,
   configures with the toolchain and the headless RHI, builds `break_crash`
   and `engine`, and confirms with `objdump -f` that the objects are
   aarch64. Build only, no ctest, with the reason in a comment.
3. **Verify what can be verified here**: the mcontext field names against
   the kernel's own aarch64 `asm/sigcontext.h`, by compiling a translation
   unit that reads `pc`, `sp` and `regs[29]`.
4. **Docs**: `docs/Build_Guide.md` section 1.5,
   `docs/Implementation_Status.md`, `docs/design/crash_symbolization.md`,
   `docs/cross_engine/missing_capabilities.md` (correcting the previous
   slice's "unverified" note to what is now checked), spec Result.
5. **Verification**: YAML parses, full `ctest` in `build-core-app-net`,
   push, then the lane's own result in CI.
