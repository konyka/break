# Plan C Task 10: offline Metal shader pipeline contract (text-level,
# platform-free). Asserts the pipeline script, the manifest generator, the
# CMake wiring, and the shared FNV/manifest types all exist with the pinned
# contract tokens. Run:
#   cmake -DREPO_ROOT=<repo> -P engine/tests/test_metal_shader_pipeline.cmake
cmake_policy(SET CMP0054 NEW)
if(NOT DEFINED REPO_ROOT)
    message(FATAL_ERROR "REPO_ROOT is required")
endif()

set(failures 0)
function(expect_file_contains path token)
    if(NOT EXISTS "${path}")
        message(WARNING "MISSING FILE: ${path}")
        math(EXPR failures "${failures} + 1")
        set(failures "${failures}" PARENT_SCOPE)
        return()
    endif()
    file(READ "${path}" content)
    string(FIND "${content}" "${token}" pos)
    if(pos EQUAL -1)
        message(WARNING "MISSING TOKEN in ${path}: ${token}")
        math(EXPR failures "${failures} + 1")
        set(failures "${failures}" PARENT_SCOPE)
    endif()
endfunction()

# 1. Pipeline script: GLSL -> SPIR-V -> MSL -> air -> metallib, with the
# Task 11 runtime define-injection variant enumeration.
set(script "${REPO_ROOT}/engine/tools/compile_metal_shaders.sh")
expect_file_contains("${script}" "glslc --target-env=vulkan1.2")
expect_file_contains("${script}" "spirv-cross")
expect_file_contains("${script}" "--msl")
expect_file_contains("${script}" "--rename-entry-point")
expect_file_contains("${script}" "xcrun -sdk")
expect_file_contains("${script}" "metallib")
# Resource remap: binding flattening must be explicit, never silent.
expect_file_contains("${script}" "--msl-decoration-binding")
# Task 11: runtime define variants (shader_inject_define call sites).
expect_file_contains("${script}" "inject_defines")
expect_file_contains("${script}" "FORWARD_MRT")
expect_file_contains("${script}" "HAS_IBL,HAS_POINT_SHADOW,FORWARD_MRT")
expect_file_contains("${script}" "CLUSTERED_ARR")
expect_file_contains("${script}" "variants/")

# M3: every define name injected at runtime (main.c + renderer call sites)
# must be enumerated by the VARIANTS table — a new call site without a
# variant row fails this contract.
foreach(src_file
        "${REPO_ROOT}/engine/src/main.c"
        "${REPO_ROOT}/engine/src/renderer/deferred.c"
        "${REPO_ROOT}/engine/src/renderer/particles.c"
        "${REPO_ROOT}/engine/src/renderer/skybox.c"
        "${REPO_ROOT}/engine/src/renderer/terrain.c"
        "${REPO_ROOT}/engine/src/renderer/water.c")
    if(NOT EXISTS "${src_file}")
        message(WARNING "MISSING inject-call-site source: ${src_file}")
        math(EXPR failures "${failures} + 1")
        continue()
    endif()
    file(READ "${src_file}" src_text)
    string(REGEX MATCHALL "(shader|defrd)_inject_define\\([^\"]*\"[A-Z_]+\"" inject_hits "${src_text}")
    foreach(hit ${inject_hits})
        string(REGEX MATCH "\"[A-Z_]+\"$" def_tok "${hit}")
        string(REGEX REPLACE "\"" "" def_tok "${def_tok}")
        expect_file_contains("${script}" "${def_tok}")
    endforeach()
endforeach()

# 2. Manifest generator: shares the header's FNV-1a 64 (no private copy)
# and emits the static table.
set(gen "${REPO_ROOT}/engine/tools/gen_metal_shader_manifest.c")
expect_file_contains("${gen}" "rhi/rhi_metal_format.h")
expect_file_contains("${gen}" "rhi_metal_fnv1a64")
expect_file_contains("${gen}" "rhi_metal_shader_manifest")

# 3. Shared types + the single FNV definition in the format header.
set(hdr "${REPO_ROOT}/engine/src/rhi/rhi_metal_format.h")
expect_file_contains("${hdr}" "RHIMetalShaderManifestEntry")
expect_file_contains("${hdr}" "rhi_metal_fnv1a64")
expect_file_contains("${hdr}" "0xcbf29ce484222325")
expect_file_contains("${hdr}" "0x100000001b3")

# 4. CMake wiring: tools locked, custom command, target chain, manifest
# compiled into the backend library, metallib copied beside consumers.
set(eng_cmake "${REPO_ROOT}/engine/CMakeLists.txt")
expect_file_contains("${eng_cmake}" "compile_metal_shaders.sh")
expect_file_contains("${eng_cmake}" "gen_metal_shader_manifest")
expect_file_contains("${eng_cmake}" "add_custom_command")
expect_file_contains("${eng_cmake}" "engine_metal_shaders")
expect_file_contains("${eng_cmake}" "rhi_metal_shader_manifest.c")
expect_file_contains("${eng_cmake}" "engine.metallib")
expect_file_contains("${eng_cmake}" "find_program")
expect_file_contains("${eng_cmake}" "CMAKE_OSX_SYSROOT MATCHES \"[Ss]imulator\"")
expect_file_contains("${eng_cmake}" "set(METAL_SHADER_SDK iphonesimulator)")

# 5. Runtime: manifest lookup in the backend.
set(metal_m "${REPO_ROOT}/engine/src/rhi/rhi_metal.m")
expect_file_contains("${metal_m}" "rhi_metal_fnv1a64")
expect_file_contains("${metal_m}" "rhi_metal_shader_manifest")
expect_file_contains("${metal_m}" "newLibraryWithFile")

if(failures GREATER 0)
    message(FATAL_ERROR "test_metal_shader_pipeline: ${failures} contract violation(s)")
endif()
message(STATUS "test_metal_shader_pipeline: all contract tokens present")
