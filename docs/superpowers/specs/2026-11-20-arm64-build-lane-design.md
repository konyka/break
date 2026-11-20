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
  target find root rather than the host's `/usr/lib`.
- Debian/Ubuntu's `/usr/aarch64-linux-gnu` is only a `CMAKE_FIND_ROOT_PATH`;
  the cross GCC already knows its target libc. It must not be passed as
  `--sysroot`, which makes the linker prefix the absolute paths in `libc.so`
  a second time. `AARCH64_SYSROOT` remains an opt-in override for toolchains
  that actually need an explicit compiler sysroot.

`.github/workflows/ci.yml`:

- A `lane-cross-aarch64-linux` job that installs the cross GCC and real
  arm64 Wayland/xkbcommon/OpenGL/EGL/OpenSSL development packages through
  Ubuntu 24.04 multiarch. Host packages supply `wayland-scanner` and the
  architecture-independent protocol XML. `PKG_CONFIG_LIBDIR` selects the
  arm64 pkg-config directories plus the protocol directory.
- Multiarch installs those target packages under `/usr`, so the job sets
  `AARCH64_SYSROOT=/`. This is different from the invalid standalone
  `/usr/aarch64-linux-gnu` sysroot: the former matches the installed target
  filesystem, while the latter double-prefixes cross libc linker paths.
- Linux has no `ENGINE_RHI_BACKEND=headless` selector. The lane explicitly
  compiles the OpenGL path and runs none of it. It builds `break_crash` and
  `engine`, then checks the resulting object architecture with `objdump`.
- Build only, no `ctest`: the binaries cannot run on an x86-64 runner, and
  claiming otherwise would be the kind of false evidence the rest of the
  repository's CI design avoids. The lane's statement is "the arm64 code
  compiles and links", which is exactly what was missing.

`docs/Build_Guide.md`:

- A subsection naming the toolchain file, the real target dependencies, the
  multiarch environment and the fact that the lane is build-only.

## Tests

The lane is the test. Locally it is reproduced by
`cmake -S engine -B build-arm64 --toolchain "$PWD/engine/toolchain-aarch64-linux.cmake"`
when the cross toolchain and target dependencies are installed. The toolchain
path is absolute because CMake does not resolve `--toolchain` relative to the
checkout root; the relative form fails first with "Could not find toolchain
file". Without a cross gcc, the absolute form loads the toolchain and then
fails on the missing `aarch64-linux-gnu-gcc`, which is the right failure.

The complete dependency/configuration/build/object-check sequence was also
run in an Ubuntu 24.04 container. It built all 176 steps for `break_crash`
and `engine`, produced `libengine.a`, and reported
`elf64-littleaarch64` for `break_crash.c.o`. Earlier variants reproduced the
relative-toolchain failure and the incorrect sysroot's three libc linker
errors before the fixes.

## Out of scope

Running arm64 tests (needs qemu-user or an arm64 runner), the Vulkan backend
under cross-compilation, macOS arm64, Windows on arm64, and any claim of
OpenGL runtime validation. The OpenGL path here is compile/link evidence
only.

## Result

Delivered: the toolchain file, the CI lane, and the Build_Guide subsection.
The complete build is verified in the Ubuntu 24.04 container; the remote CI
lane consumes the same configuration for continuous verification. No arm64
binary was executed.

**The field names are verified independently as well.** The previous slice's
open question was whether `uc_mcontext.pc`, `.sp` and `.regs[29]` are the
right names. A zig distribution on this machine ships the kernel's aarch64
`asm/sigcontext.h`, and compiling a translation unit against it with those
three field accesses succeeds:

    struct sigcontext { __u64 fault_address; __u64 regs[31];
                        __u64 sp; __u64 pc; __u64 pstate; ... };

so `regs[29]` is x29 (AAPCS64's frame pointer), `sp` and `pc` are named as
used. That is a compiler accepting the real header, not reasoning from the
ABI document.
