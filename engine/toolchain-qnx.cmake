# QNX SDP cross toolchain (QNX 7.1 / 8.0, qcc/q++ frontends).
#
# Source the QNX SDP environment first so QNX_HOST and QNX_TARGET are set
# (e.g. `source /opt/qnx800/qnxsdp-env.sh`), then configure:
#
#   cmake -S engine -B engine/build-qnx \
#         -DCMAKE_TOOLCHAIN_FILE=toolchain-qnx.cmake \
#         -DCMAKE_BUILD_TYPE=Release -DQNX_ARCH=aarch64le
#
# QNX_ARCH selects the Neutrino target: aarch64le (default), x86_64, armle.
#
# This is a headless configuration: the engine, net_loop (poll backend),
# task system, and myui (dummy PAL offscreen) compile for the target;
# window/graphics stays fail-closed until a Screen WSI integration exists
# (docs/qnx_compat.md).

set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_VERSION 1)

if(NOT QNX_ARCH)
    set(QNX_ARCH "aarch64le")
endif()

if(NOT DEFINED ENV{QNX_HOST} OR NOT DEFINED ENV{QNX_TARGET})
    message(FATAL_ERROR
        "QNX SDP not detected: source the SDP environment so QNX_HOST and QNX_TARGET are set (QNX SDP 7.1+)")
endif()

set(QNX_HOST_DIR "$ENV{QNX_HOST}")
set(QNX_TARGET_DIR "$ENV{QNX_TARGET}")

find_program(QNX_QCC qcc HINTS "${QNX_HOST_DIR}/usr/bin" REQUIRED)
find_program(QNX_QPP q++ HINTS "${QNX_HOST_DIR}/usr/bin" REQUIRED)

set(CMAKE_C_COMPILER "${QNX_QCC}")
set(CMAKE_CXX_COMPILER "${QNX_QPP}")
# -Vgcc_nto<arch> selects the gcc-fronted mode of qcc for the target arch.
set(CMAKE_C_FLAGS_INIT "-Vgcc_nto${QNX_ARCH}")
set(CMAKE_CXX_FLAGS_INIT "-Vgcc_nto${QNX_ARCH} -lang-c++")
set(CMAKE_SYSROOT "${QNX_TARGET_DIR}")

set(CMAKE_FIND_ROOT_PATH "${QNX_TARGET_DIR}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
