# Plan C Task 10: offline Metal shader pipeline contract (text-level,
# platform-free). Asserts the pipeline script, the manifest generator, the
# CMake wiring, and the shared FNV/manifest types all exist with the pinned
# contract tokens. Run:
#   cmake -DREPO_ROOT=<repo> -P engine/tests/test_metal_shader_pipeline.cmake
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

# 1. Pipeline script: GLSL -> SPIR-V -> MSL -> air -> metallib.
set(script "${REPO_ROOT}/engine/tools/compile_metal_shaders.sh")
expect_file_contains("${script}" "glslc --target-env=vulkan1.2")
expect_file_contains("${script}" "spirv-cross")
expect_file_contains("${script}" "--msl")
expect_file_contains("${script}" "--rename-entry-point")
expect_file_contains("${script}" "xcrun -sdk")
expect_file_contains("${script}" "metallib")
# Resource remap: binding flattening must be explicit, never silent.
expect_file_contains("${script}" "--msl-decoration-binding")

# 2. Manifest generator: FNV-1a 64 + static table output.
set(gen "${REPO_ROOT}/engine/tools/gen_metal_shader_manifest.c")
expect_file_contains("${gen}" "0xcbf29ce484222325")
expect_file_contains("${gen}" "0x100000001b3")
expect_file_contains("${gen}" "rhi_metal_shader_manifest")

# 3. Shared types in the format header.
set(hdr "${REPO_ROOT}/engine/src/rhi/rhi_metal_format.h")
expect_file_contains("${hdr}" "RHIMetalShaderManifestEntry")
expect_file_contains("${hdr}" "rhi_metal_fnv1a64")

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

# 5. Runtime: manifest lookup in the backend.
set(metal_m "${REPO_ROOT}/engine/src/rhi/rhi_metal.m")
expect_file_contains("${metal_m}" "rhi_metal_fnv1a64")
expect_file_contains("${metal_m}" "rhi_metal_shader_manifest")
expect_file_contains("${metal_m}" "newLibraryWithFile")

if(failures GREATER 0)
    message(FATAL_ERROR "test_metal_shader_pipeline: ${failures} contract violation(s)")
endif()
message(STATUS "test_metal_shader_pipeline: all contract tokens present")
