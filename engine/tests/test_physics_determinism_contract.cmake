# Source contract for cross-platform physics determinism.
#
# The golden hashes in test_physics_replay only fail where the platform
# differs (for example glibc 2.44 for atan2f), so a regression could pass on
# the CI hosts. This contract checks the sources directly:
#   1. physics code never calls the platform atan2/atan2f (math_atan2f only),
#   2. fast_rsqrt stays the correctly rounded 1/sqrtf, with no SSE estimate,
#   3. the physics and math sources are compiled with -ffp-contract=off.
if(NOT DEFINED ENGINE_SOURCE_DIR)
    message(FATAL_ERROR "ENGINE_SOURCE_DIR is required")
endif()

set(errors "")
file(GLOB physics_sources "${ENGINE_SOURCE_DIR}/src/physics/*.c" "${ENGINE_SOURCE_DIR}/src/physics/*.h")
foreach(path IN LISTS physics_sources)
    file(READ "${path}" text)
    if(text MATCHES "[^_a-zA-Z0-9]atan2f?[ \t]*\\(")
        string(APPEND errors "${path}: calls the platform atan2; use math_atan2f\n")
    endif()
    if(text MATCHES "_mm_rsqrt|_mm_rcp")
        string(APPEND errors "${path}: uses an approximate SSE reciprocal\n")
    endif()
endforeach()

file(READ "${ENGINE_SOURCE_DIR}/src/math/math.h" math_h)
string(FIND "${math_h}" "static inline f32 fast_rsqrt(f32 x) {\n    return 1.0f / sqrtf(x);\n}" exact_rsqrt)
if(exact_rsqrt EQUAL -1)
    string(APPEND errors "math.h: fast_rsqrt must be exactly 'return 1.0f / sqrtf(x);'\n")
endif()
if(math_h MATCHES "_mm_rsqrt|_mm_rcp")
    string(APPEND errors "math.h: uses an approximate SSE reciprocal\n")
endif()

file(READ "${ENGINE_SOURCE_DIR}/CMakeLists.txt" cmake_text)
foreach(needle IN ITEMS
        "\${CMAKE_CURRENT_SOURCE_DIR}/src/physics/*.c"
        "\${CMAKE_CURRENT_SOURCE_DIR}/src/math/*.c"
        "\${CMAKE_CURRENT_SOURCE_DIR}/tests/test_math.c"
        "APPEND PROPERTY COMPILE_OPTIONS -ffp-contract=off")
    string(FIND "${cmake_text}" "${needle}" at)
    if(at EQUAL -1)
        string(APPEND errors "CMakeLists.txt: missing '${needle}' in the -ffp-contract=off source list\n")
    endif()
endforeach()

if(NOT errors STREQUAL "")
    message(FATAL_ERROR "physics determinism contract failed:\n${errors}")
endif()
message(STATUS "physics determinism contract passed")
