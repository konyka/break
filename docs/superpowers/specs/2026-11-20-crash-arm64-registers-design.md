
# Design: arm64 register capture and frame recovery

The crash handler reads `RIP/RSP/RBP` from the ucontext only under
`__x86_64__ && __linux__`; everywhere else it writes zeros, which is
documented but means an arm64 Linux crash produces a record with no
registers, no stack window (the window starts at `rsp`) and no frames
(`break_crash_symbolize_record` returns 0 when `rip` is 0). Linux arm64 is a
target the repository builds for, so the record is empty exactly where it is
needed.

## Change

`src/crash/break_crash.c`:

- Under `__aarch64__ && __linux__`, read the three values from
  `uc->uc_mcontext`: `pc` as the instruction pointer, `sp` as the stack
  pointer, and `regs[29]` (the frame pointer, x29) as the frame base. The
  field names stay `rip/rsp/rbp` in the record, since the record format is
  pinned and the roles are the same.
- Every other architecture keeps writing zeros, with the comment narrowed to
  say which two are covered.

`src/crash/break_crash_symbolize.c` / `.h`:

- No code change to the walk: AAPCS64's frame record is
  `[fp] = caller's fp`, `[fp+8] = LR`, the same layout and the same
  little-endian word size the x86-64 walk already reads. The header comment
  stops saying "frames are x86-64" and states the two layouts it covers,
  because a reader checking whether arm64 is supported should not have to
  work that out.

## Tests

`tests/test_break_crash_symbolize.c`:

- A record built with an arm64-shaped frame chain (fp pointing into the
  window, `[fp]` the next fp, `[fp+8]` the return address) recovers the same
  frame sequence the x86-64 case does, which is the statement that the walk
  is architecture-independent. The existing x86-64 cases stay as they are.
- The chain's stop conditions are already covered by the existing cases;
  this adds the positive arm64 case rather than duplicating them.

`tests/test_break_crash.c`:

- The handler path is only reachable on the host architecture, so the
  register capture itself cannot be unit-tested on x86-64. What is testable
  and worth pinning: the record builder and parser round-trip the three
  values whatever they are, which the existing cases already do. The new
  arm64 branch is covered by the symbolize case above plus the CI arm64
  lane if one exists; the spec says so rather than claiming more.

## Out of scope

Windows SEH, macOS arm64 (a different mcontext layout), DWARF or
`.eh_frame` unwinding, a frameless-function fallback.

## Result

Delivered, with one claim the spec made that turned out to be already true
and one verification this environment cannot perform.

**The unwinder needed no change.** The spec suspected the walk was
x86-64-specific; it is not. AAPCS64's frame record is `[fp] = caller's fp`,
`[fp+8] = LR`, the same layout and little-endian word size the existing walk
reads, so one implementation serves both. Rather than assert that in a
comment, the slice adds
`the_walker_follows_an_arm64_frame_pointer_chain_too`: an arm64-shaped chain
(fp = sp+0x40, three records, the last fp zero) recovers pc plus three LRs.
Mutating the last LR to 0 fails it, so the case is not vacuous.
`test_break_crash_symbolize` 44/44.

**The register capture cannot be verified here.** The new branch is
`__aarch64__ && __linux__`, and this machine is x86-64 with no aarch64
cross-compiler and no arm64 CI lane, so the branch is not compiled by any
check available. The field names (`uc_mcontext.pc`, `.sp`, `.regs[29]`) are
glibc's aarch64 `struct sigcontext` layout, and `regs[29]` is x29, the AAPCS64
frame pointer — but that is reasoning from the ABI, not a passing build. The
honest state is: the arm64 record path is written and unverified, and
`missing_capabilities.md` says so. Adding an arm64 build lane is the slice
that would close it.

Everything on the host architecture stays green: `test_break_crash` 37/37
and the full suite unchanged.
