# Plan: an arm64 cross-build lane

Spec: `docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md`.

1. **GREEN (toolchain)**: `engine/toolchain-aarch64-linux.cmake` with the
   cross tools, a target find root (with an opt-in `AARCH64_SYSROOT`
   override) and the find-root modes that keep CMake off the host's
   libraries. Debian/Ubuntu's cross libc directory is not passed as the
   compiler sysroot.
2. **GREEN (CI)**: `lane-cross-aarch64-linux` installs the cross GCC and
   real arm64 Wayland/xkbcommon/OpenGL/OpenSSL packages with Ubuntu 24.04
   multiarch, configures the explicit OpenGL path with the matching sysroot
   and pkg-config roots, builds `break_crash` and `engine`, and confirms
   with `objdump -f` that the objects are aarch64. Build only, no ctest,
   with the reason in a comment.
3. **Verify what can be verified here**: the mcontext field names against
   the kernel's own aarch64 `asm/sigcontext.h`, by compiling a translation
   unit that reads `pc`, `sp` and `regs[29]`; reproduce the full lane in an
   Ubuntu 24.04 container and check the built object architecture.
4. **Docs**: `docs/Build_Guide.md` section 1.5,
   `docs/Implementation_Status.md`, `docs/design/crash_symbolization.md`,
   `docs/cross_engine/missing_capabilities.md` (correcting the previous
   slice's "unverified" note to what is now checked), spec Result.
5. **Verification**: YAML parses, full `ctest` in `build-core-app-net`,
   push, then the lane's own result in CI.
