if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()
if(NOT DEFINED ENGINE_SOURCE_DIR)
    message(FATAL_ERROR "ENGINE_SOURCE_DIR is required")
endif()

if(NOT DEFINED CMAKE_BIN)
    set(CMAKE_BIN "${CMAKE_COMMAND}")
endif()
if(NOT DEFINED TEST_BINARY_DIR)
    set(TEST_BINARY_DIR "${ENGINE_SOURCE_DIR}/build-rhi-selector-contract")
endif()

set(configure_overrides)
if(DEFINED CMAKE_GENERATOR AND NOT "${CMAKE_GENERATOR}" STREQUAL "")
    list(APPEND configure_overrides -G "${CMAKE_GENERATOR}")
endif()
if(DEFINED CMAKE_C_COMPILER AND NOT "${CMAKE_C_COMPILER}" STREQUAL "")
    list(APPEND configure_overrides "-DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}")
endif()
if(DEFINED CMAKE_MAKE_PROGRAM AND NOT "${CMAKE_MAKE_PROGRAM}" STREQUAL "")
    list(APPEND configure_overrides "-DCMAKE_MAKE_PROGRAM:FILEPATH=${CMAKE_MAKE_PROGRAM}")
endif()
if(DEFINED CMAKE_TOOLCHAIN_FILE AND NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    list(APPEND configure_overrides "-DCMAKE_TOOLCHAIN_FILE:FILEPATH=${CMAKE_TOOLCHAIN_FILE}")
endif()
# The nested configure must follow the host WSI stack: Wayland lanes have
# no X11 development packages (libxrandr), so a default X11 configure
# fails in platform detection before the selector logic under test runs.
# The backend-selection contract is orthogonal to the WSI stack.
if(DEFINED ENGINE_ENABLE_WAYLAND)
    list(APPEND configure_overrides "-DENGINE_ENABLE_WAYLAND:BOOL=${ENGINE_ENABLE_WAYLAND}")
endif()
# macOS configures REQUIRE shaderc + a Vulkan library even for the GL
# selector paths (ENGINE_PLATFORM STREQUAL "macos" branch), and brew's
# MoltenVK keg ships libMoltenVK.dylib with no libvulkan.dylib, so
# discovery fails without the explicit paths the outer lane resolved.
foreach(cache_var Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR OPENSSL_ROOT_DIR)
    if(DEFINED ${cache_var} AND NOT "${${cache_var}}" STREQUAL "")
        list(APPEND configure_overrides "-D${cache_var}=${${cache_var}}")
    endif()
endforeach()
# A MoltenVK-free metal lane has no Vulkan SDK anywhere, yet the nested
# auto/opengl macOS configures hit find_package(Vulkan REQUIRED) in the
# non-metal branch. The contract under test here is selector *resolution*
# (EFFECTIVE value + fail-closed behavior), not Vulkan discovery — real
# discovery is covered where the outer lane resolved genuine paths above.
# Cached vars short-circuit FindVulkan's search; the paths must merely
# EXIST (generate-time validation of the Vulkan::Vulkan imported target)
# and are never compiled against or linked in the nested configure.
if(APPLE AND (NOT DEFINED Vulkan_LIBRARY OR "${Vulkan_LIBRARY}" STREQUAL ""))
    list(APPEND configure_overrides
        "-DVulkan_LIBRARY=${ENGINE_SOURCE_DIR}/CMakeLists.txt"
        "-DVulkan_INCLUDE_DIR=${ENGINE_SOURCE_DIR}/external")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)
foreach(required_text
        "set(ENGINE_RHI_BACKEND \"auto\" CACHE STRING"
        "set_property(CACHE ENGINE_RHI_BACKEND PROPERTY STRINGS auto opengl vulkan metal d3d12)"
        "set(ENGINE_RHI_BACKEND_EFFECTIVE"
        "RHI backend: requested="
        "ENGINE_RHI_BACKEND must be auto, opengl, vulkan, metal, or d3d12"
        "metal backend is UNAVAILABLE on this platform"
        "ENGINE_RHI_BACKEND=d3d12 is UNAVAILABLE on this platform"
        "ENGINE_RHI_BACKEND STREQUAL \"vulkan\""
        "ENGINE_RHI_BACKEND STREQUAL \"opengl\""
        "ENGINE_RHI_BACKEND STREQUAL \"metal\""
        "ENGINE_RHI_BACKEND STREQUAL \"d3d12\""
        "set(ENGINE_RHI_BACKEND_EFFECTIVE \"\${_rhi_backend_effective}\" CACHE INTERNAL")
    string(FIND "${cmake_text}" "${required_text}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "RHI backend selection contract missing: ${required_text}")
    endif()
endforeach()

function(assert_configure_success backend expected_effective)
    set(binary_dir "${TEST_BINARY_DIR}/${backend}")
    # A reused tree keeps its cached ENGINE_VULKAN, which would mask what a
    # fresh `auto` configure resolves to.
    file(REMOVE_RECURSE "${binary_dir}")
    execute_process(
        COMMAND "${CMAKE_BIN}" -S "${ENGINE_SOURCE_DIR}" -B "${binary_dir}"
            ${configure_overrides}
            "-DENGINE_RHI_BACKEND=${backend}"
            -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=dummy
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output)
    if(NOT result EQUAL 0)
        message(FATAL_ERROR
            "RHI selector ${backend} failed to configure:\n${output}\n${error_output}")
    endif()
    file(READ "${binary_dir}/CMakeCache.txt" cache_text)
    string(FIND "${cache_text}"
        "ENGINE_RHI_BACKEND_EFFECTIVE:INTERNAL=${expected_effective}" effective_offset)
    if(effective_offset EQUAL -1)
        message(FATAL_ERROR
            "RHI selector ${backend} did not resolve to ${expected_effective}")
    endif()
endfunction()

assert_configure_success("opengl" "opengl")

# Default backend (maintainer decision 2026-10-26): `auto` resolves to Vulkan
# on Linux and Windows. Vulkan needs the loader headers + shaderc, so `auto`
# degrades to OpenGL (the last-resort fallback) with a visible warning when
# they are missing, while an explicit `vulkan` stays fail-closed. Apple keeps
# its own native path (Metal) and is not part of this rule.
function(configure_auto tag out_result out_text)
    set(binary_dir "${TEST_BINARY_DIR}/auto-${tag}")
    file(REMOVE_RECURSE "${binary_dir}")
    execute_process(
        COMMAND "${CMAKE_BIN}" -S "${ENGINE_SOURCE_DIR}" -B "${binary_dir}"
            ${configure_overrides} ${ARGN}
            -DENGINE_RHI_BACKEND=auto -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=dummy
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output)
    set(effective "")
    if(EXISTS "${binary_dir}/CMakeCache.txt")
        file(STRINGS "${binary_dir}/CMakeCache.txt" effective_line
            REGEX "^ENGINE_RHI_BACKEND_EFFECTIVE:INTERNAL=")
        string(REGEX REPLACE "^[^=]*=" "" effective "${effective_line}")
    endif()
    set(${out_result} "${result}" PARENT_SCOPE)
    set(${out_text} "${effective}|${output}${error_output}" PARENT_SCOPE)
endfunction()

if(APPLE)
    assert_configure_success("auto" "opengl")
else()
    # An explicit vulkan configure tells us whether this host has the deps.
    set(vk_dir "${TEST_BINARY_DIR}/vulkan")
    file(REMOVE_RECURSE "${vk_dir}")
    execute_process(
        COMMAND "${CMAKE_BIN}" -S "${ENGINE_SOURCE_DIR}" -B "${vk_dir}"
            ${configure_overrides}
            -DENGINE_RHI_BACKEND=vulkan -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=dummy
        RESULT_VARIABLE vk_result
        OUTPUT_VARIABLE vk_output
        ERROR_VARIABLE vk_error)

    configure_auto(default auto_result auto_text)
    if(NOT auto_result EQUAL 0)
        message(FATAL_ERROR "auto must configure on every host:\n${auto_text}")
    endif()
    if(vk_result EQUAL 0)
        if(NOT auto_text MATCHES "^vulkan\\|")
            message(FATAL_ERROR
                "auto must default to vulkan when Vulkan is available; got: ${auto_text}")
        endif()
        if(auto_text MATCHES "falling back to OpenGL")
            message(FATAL_ERROR "auto warned about a fallback although Vulkan is available")
        endif()
    else()
        if(NOT auto_text MATCHES "^opengl\\|")
            message(FATAL_ERROR
                "auto must fall back to opengl when Vulkan is unavailable; got: ${auto_text}")
        endif()
        if(NOT auto_text MATCHES "falling back to OpenGL")
            message(FATAL_ERROR "auto fell back to OpenGL silently")
        endif()
    endif()

    # Vulkan hidden from the probe: the fallback is deterministic and loud.
    configure_auto(novulkan nv_result nv_text -DCMAKE_DISABLE_FIND_PACKAGE_Vulkan=ON)
    if(NOT nv_result EQUAL 0)
        message(FATAL_ERROR "auto without Vulkan must still configure:\n${nv_text}")
    endif()
    if(NOT nv_text MATCHES "^opengl\\|" OR NOT nv_text MATCHES "falling back to OpenGL")
        message(FATAL_ERROR
            "auto without Vulkan must fall back to opengl with a warning; got: ${nv_text}")
    endif()

    # Historical switch: an explicit -DENGINE_VULKAN=OFF still means OpenGL.
    configure_auto(legacyoff lo_result lo_text -DENGINE_VULKAN=OFF)
    if(NOT lo_result EQUAL 0 OR NOT lo_text MATCHES "^opengl\\|")
        message(FATAL_ERROR "explicit ENGINE_VULKAN=OFF must keep selecting opengl; got: ${lo_text}")
    endif()
    if(lo_text MATCHES "falling back to OpenGL")
        message(FATAL_ERROR "explicit ENGINE_VULKAN=OFF must not warn about a fallback")
    endif()

    # Explicit vulkan never degrades silently: it either configures to
    # vulkan or fails closed (tested above through vk_result).
    if(vk_result EQUAL 0)
        file(STRINGS "${vk_dir}/CMakeCache.txt" vk_effective
            REGEX "^ENGINE_RHI_BACKEND_EFFECTIVE:INTERNAL=vulkan$")
        if(NOT vk_effective)
            message(FATAL_ERROR "explicit vulkan configured but did not resolve to vulkan")
        endif()
    endif()
endif()

# metal: APPLE 平台必须配置成功且 EFFECTIVE=metal；其他平台必须 FATAL_ERROR
# 且消息恰含 UNAVAILABLE（fail-closed，不得静默回退到其他后端）。
if(APPLE)
    assert_configure_success("metal" "metal")
else()
    execute_process(
        COMMAND "${CMAKE_BIN}" -S "${ENGINE_SOURCE_DIR}" -B "${TEST_BINARY_DIR}/metal"
            ${configure_overrides}
            -DENGINE_RHI_BACKEND=metal -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=dummy
        RESULT_VARIABLE metal_result
        OUTPUT_VARIABLE metal_output
        ERROR_VARIABLE metal_error)
    if(metal_result EQUAL 0)
        message(FATAL_ERROR "metal selector unexpectedly configured on non-APPLE platform")
    endif()
    if(NOT "${metal_output}${metal_error}" MATCHES
           "metal backend is UNAVAILABLE on this platform")
        message(FATAL_ERROR "metal selector failed for an unexpected reason")
    endif()
endif()

# d3d12 is selectable on Windows hosts only; elsewhere it must fail closed
# with an UNAVAILABLE message (no silent fallback to another backend).
if(WIN32)
    assert_configure_success("d3d12" "d3d12")
else()
    execute_process(
        COMMAND "${CMAKE_BIN}" -S "${ENGINE_SOURCE_DIR}" -B "${TEST_BINARY_DIR}/d3d12"
            ${configure_overrides}
            -DENGINE_RHI_BACKEND=d3d12 -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=dummy
        RESULT_VARIABLE d3d12_result
        OUTPUT_VARIABLE d3d12_output
        ERROR_VARIABLE d3d12_error)
    if(d3d12_result EQUAL 0)
        message(FATAL_ERROR "d3d12 selector unexpectedly configured on non-WIN32 platform")
    endif()
    if(NOT "${d3d12_output}${d3d12_error}" MATCHES
           "d3d12 is UNAVAILABLE on this platform")
        message(FATAL_ERROR "d3d12 selector failed for an unexpected reason")
    endif()
endif()
