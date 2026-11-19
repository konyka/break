# Plan: arm64 register capture and frame recovery

Spec: `docs/superpowers/specs/2026-11-20-crash-arm64-registers-design.md`.

1. **Test first, to find out whether the walk needs changing**: an
   arm64-shaped frame chain through `break_crash_symbolize_record`. It
   passes unchanged, which settles that AAPCS64 and x86-64 share the
   `[fp]`/`[fp+8]` layout and that no unwinder change is needed.
2. **GREEN (capture)**: the `__aarch64__ && __linux__` branch reading
   `uc_mcontext.pc`, `.sp` and `.regs[29]`, with the record's field names
   unchanged because the format is pinned.
3. **Comments**: the handler contract and the symbolize header stop saying
   x86-64 only, and name the two layouts covered.
4. **Mutation**: the arm64 case's last LR zeroed must fail it (so the case
   is not vacuous).
5. **Docs**: `docs/design/crash_symbolization.md`,
   `docs/cross_engine/missing_capabilities.md`, spec Result — each stating
   plainly that the capture branch is unverified here, with no arm64
   compiler or CI lane available.
6. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree for
   the two crash tests, push, CI.
