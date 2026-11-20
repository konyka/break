# GCC cross-compiling to Linux arm64.
#
# The CI uses this toolchain for compile/link checks and explicitly runs
# selected headless service and security tests with QEMU. It type-checks the
# __aarch64__ paths (the crash handler's register capture, the Mach-O
# reader's arm64 slices, and the platform layer's arm64 branches).
# See docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md.
#
#   cmake -S engine -B build-arm64 \
#       --toolchain /absolute/path/to/engine/toolchain-aarch64-linux.cmake \
#       -DENGINE_RHI_BACKEND=opengl
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_AR aarch64-linux-gnu-ar)
set(CMAKE_RANLIB aarch64-linux-gnu-ranlib)

# An explicit sysroot is opt-in for toolchains that need one. Debian and
# Ubuntu's cross GCC already knows its target libc: /usr/aarch64-linux-gnu is
# a CMake find root there, not a compiler sysroot. Passing it to --sysroot
# makes the linker prefix the absolute paths in libc.so a second time.
if(DEFINED ENV{AARCH64_SYSROOT})
    set(CMAKE_SYSROOT "$ENV{AARCH64_SYSROOT}")
    set(CMAKE_FIND_ROOT_PATH "$ENV{AARCH64_SYSROOT}")
elseif(EXISTS /usr/aarch64-linux-gnu)
    set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)
endif()

# Programs come from the host, everything else from the target find root:
# without this CMake finds the host's /usr/lib and links x86-64 objects.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
