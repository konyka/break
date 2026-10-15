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

file(READ "${ENGINE_CMAKE}" cmake_text)
foreach(required_text
        "set(ENGINE_RHI_BACKEND \"auto\" CACHE STRING"
        "set_property(CACHE ENGINE_RHI_BACKEND PROPERTY STRINGS auto opengl vulkan metal)"
        "set(ENGINE_RHI_BACKEND_EFFECTIVE"
        "RHI backend: requested="
        "ENGINE_RHI_BACKEND must be auto, opengl, vulkan, or metal"
        "metal backend is UNAVAILABLE on this platform"
        "ENGINE_RHI_BACKEND STREQUAL \"vulkan\""
        "ENGINE_RHI_BACKEND STREQUAL \"opengl\""
        "ENGINE_RHI_BACKEND STREQUAL \"metal\""
        "set(ENGINE_RHI_BACKEND_EFFECTIVE \"\${_rhi_backend_effective}\" CACHE INTERNAL")
    string(FIND "${cmake_text}" "${required_text}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "RHI backend selection contract missing: ${required_text}")
    endif()
endforeach()

foreach(forbidden_backend "d3d12")
    if(cmake_text MATCHES "ENGINE_RHI_BACKEND[ \t]*STREQUAL[ \t]*\"${forbidden_backend}\"")
        message(FATAL_ERROR "unimplemented backend selector admitted: ${forbidden_backend}")
    endif()
endforeach()

function(assert_configure_success backend expected_effective)
    set(binary_dir "${TEST_BINARY_DIR}/${backend}")
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

assert_configure_success("auto" "opengl")
assert_configure_success("opengl" "opengl")

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

execute_process(
    COMMAND "${CMAKE_BIN}" -S "${ENGINE_SOURCE_DIR}" -B "${TEST_BINARY_DIR}/d3d12"
        ${configure_overrides}
        -DENGINE_RHI_BACKEND=d3d12 -DENGINE_BUILD_TESTS=OFF -DMYUI_PAL=dummy
    RESULT_VARIABLE d3d12_result
    OUTPUT_VARIABLE d3d12_output
    ERROR_VARIABLE d3d12_error)
if(d3d12_result EQUAL 0)
    message(FATAL_ERROR "unimplemented backend selector unexpectedly configured: d3d12")
endif()
if(NOT "${d3d12_output}${d3d12_error}" MATCHES
       "ENGINE_RHI_BACKEND must be auto, opengl, vulkan, or metal")
    message(FATAL_ERROR "d3d12 selector failed for an unexpected reason")
endif()
