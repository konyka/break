# GCC cross-compiling to Linux arm64.
#
# Build-only: the binaries do not run on an x86-64 host, so this exists to
# type-check and link the __aarch64__ paths (the crash handler's register
# capture, the Mach-O reader's arm64 slices, the platform layer's arm64
# branches). See docs/superpowers/specs/2026-11-20-arm64-build-lane-design.md.
#
#   cmake -S engine -B build-arm64 \
#       --toolchain /absolute/path/to/engine/toolchain-aarch64-linux.cmake \
#       -DENGINE_RHI_BACKEND=headless
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_AR aarch64-linux-gnu-ar)
set(CMAKE_RANLIB aarch64-linux-gnu-ranlib)

# A distro that puts the cross libc elsewhere can point at it without
# editing this file.
if(DEFINED ENV{AARCH64_SYSROOT})
    set(CMAKE_SYSROOT $ENV{AARCH64_SYSROOT})
elseif(EXISTS /usr/aarch64-linux-gnu)
    set(CMAKE_SYSROOT /usr/aarch64-linux-gnu)
endif()

# Programs come from the host, everything else from the sysroot: without
# this CMake finds the host's /usr/lib and links x86-64 objects.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
