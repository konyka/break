# Design: an arm64 cross-build lane

The previous slice added the `__aarch64__ && __linux__` register capture to
the crash handler and had to ship it unverified: nothing in the repository
compiles for arm64, so the branch is not even type-checked. The same holds
for every other `__aarch64__` path (the Mach-O reader accepts arm64 slices,
the platform layer has arm64 branches), and for any future one.

## Change

`engine/toolchain-aarch64-linux.cmake` (new):

- A cross toolchain in the same style as the existing ones:
  `CMAKE_SYSTEM_NAME Linux`, `CMAKE_SYSTEM_PROCESSOR aarch64`, the
  `aarch64-linux-gnu-` gcc/g++/ar/ranlib, and
  `CMAKE_FIND_ROOT_PATH_MODE_*` set so CMake looks for libraries in the
  sysroot rather than the host's `/usr/lib`.
- The toolchain reads `AARCH64_SYSROOT` when set, so a distro that ships the
  cross libc somewhere other than `/usr/aarch64-linux-gnu` still works.

`.github/workflows/ci.yml`:

- A `lane-cross-aarch64-linux` job that installs
  `gcc-aarch64-linux-gnu`, configures with that toolchain and the headless
  RHI (no GPU, no window system in a cross sysroot), and builds the targets
  that carry architecture-specific code: `break_crash` and the crash tools,
  plus `core` and `engine` so a type error anywhere in the common path is
  caught.
- Build only, no `ctest`: the binaries cannot run on an x86-64 runner, and
  claiming otherwise would be the kind of false evidence the rest of the
  repository's CI design avoids. The lane's statement is "the arm64 code
  compiles and links", which is exactly what was missing.

`docs/Build_Guide.md`:

- A short subsection naming the toolchain file, the one dependency, and the
  fact that the lane is build-only.

## Tests

The lane is the test. Locally it is reproduced by
`cmake -S engine -B build-arm64 --toolchain "$PWD/engine/toolchain-aarch64-linux.cmake"`
when a cross gcc is installed. The toolchain path is absolute because CMake
does not resolve `--toolchain` relative to the checkout root; the relative
form fails first with "Could not find toolchain file". Without a cross gcc,
the absolute form loads the toolchain and then fails on the missing
`aarch64-linux-gnu-gcc`, which is the right failure.

## Out of scope

Running arm64 tests (needs qemu-user or an arm64 runner), the Vulkan or
OpenGL backends under cross-compilation, macOS arm64, Windows on arm64.

## Result

Delivered: the toolchain file, the CI lane, and the Build_Guide subsection.

**What this environment could verify, and what it could not.** There is no
aarch64 cross-compiler or sysroot on this machine (`dnf` has
`gcc-aarch64-linux-gnu` but installing it needs a password that is not
available here), so the lane itself is unrun locally. The relative-path
invocation failed with "Could not find toolchain file"; changing only that
argument to an absolute path made CMake read the toolchain and fail with
"aarch64-linux-gnu-gcc is not a full path and was not found in PATH". The
CI and examples therefore use absolute paths.

**The field names are now verified, which was the point.** The previous
slice's open question was whether `uc_mcontext.pc`, `.sp` and `.regs[29]`
are the right names. A zig distribution on this machine ships the kernel's
aarch64 `asm/sigcontext.h`, and compiling a translation unit against it
with those three field accesses succeeds:

    struct sigcontext { __u64 fault_address; __u64 regs[31];
                        __u64 sp; __u64 pc; __u64 pstate; ... };

so `regs[29]` is x29 (AAPCS64's frame pointer), `sp` and `pc` are named as
used. That is a compiler accepting the real header, not reasoning from the
ABI document. What remains unverified is the rest of the arm64 build (every
other `__aarch64__` path, and the link), which is exactly what the CI lane
is for.
