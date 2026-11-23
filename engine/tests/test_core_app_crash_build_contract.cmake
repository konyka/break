foreach(var ENGINE_CMAKE CONTRACT_BUILD_ROOT NETWORK_ENABLED NESTED_ENGINE_RHI_BACKEND
        NESTED_CMAKE_GENERATOR NESTED_CMAKE_C_COMPILER)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

get_filename_component(engine_source_dir "${ENGINE_CMAKE}" DIRECTORY)
set(toolchain_defs "-DCMAKE_C_COMPILER=${NESTED_CMAKE_C_COMPILER}")
foreach(cache_var Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
    if(DEFINED ${cache_var} AND NOT "${${cache_var}}" STREQUAL "")
        list(APPEND toolchain_defs "-D${cache_var}=${${cache_var}}")
    endif()
endforeach()
set(contract_timeout 300)
file(REMOVE_RECURSE "${CONTRACT_BUILD_ROOT}")
execute_process(
    COMMAND "${CMAKE_COMMAND}" -G "${NESTED_CMAKE_GENERATOR}"
        -S "${engine_source_dir}" -B "${CONTRACT_BUILD_ROOT}"
        -DENGINE_BUILD_TESTS=OFF -DENGINE_ENABLE_IPO=OFF
        -DENGINE_RHI_BACKEND=${NESTED_ENGINE_RHI_BACKEND} -DBREAK_ENABLE_SNOWFLAKE=OFF
        -DBREAK_ENABLE_CRASH=OFF -DCORE_APP_ENABLE_NETWORK=${NETWORK_ENABLED}
        ${toolchain_defs}
    RESULT_VARIABLE configure_rc
    OUTPUT_VARIABLE configure_out
    ERROR_VARIABLE configure_err
    TIMEOUT ${contract_timeout})
if(NOT configure_rc EQUAL 0)
    message(FATAL_ERROR "BREAK_ENABLE_CRASH=OFF configure failed: ${configure_out}${configure_err}")
endif()
file(STRINGS "${CONTRACT_BUILD_ROOT}/CMakeCache.txt" crash_off_line
    REGEX "^BREAK_ENABLE_CRASH:BOOL=OFF$")
list(LENGTH crash_off_line crash_off_count)
if(NOT crash_off_count EQUAL 1)
    message(FATAL_ERROR "BREAK_ENABLE_CRASH=OFF was not preserved in the independent cache")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" --build "${CONTRACT_BUILD_ROOT}"
        --target core_app --parallel 2
    RESULT_VARIABLE build_rc
    OUTPUT_VARIABLE build_out
    ERROR_VARIABLE build_err
    TIMEOUT ${contract_timeout})
if(NOT build_rc EQUAL 0)
    message(FATAL_ERROR "BREAK_ENABLE_CRASH=OFF core_app build failed: ${build_out}${build_err}")
endif()
file(GLOB_RECURSE core_app_candidates LIST_DIRECTORIES FALSE
    "${CONTRACT_BUILD_ROOT}/core_app" "${CONTRACT_BUILD_ROOT}/core_app.exe")
list(LENGTH core_app_candidates core_app_count)
if(NOT core_app_count EQUAL 1)
    message(FATAL_ERROR "BREAK_ENABLE_CRASH=OFF core_app executable count=${core_app_count}, want=1")
endif()
list(GET core_app_candidates 0 core_app)

set(errors "")
set(off_spool "${CONTRACT_BUILD_ROOT}/off-spool")
execute_process(
    COMMAND "${core_app}" --help
    RESULT_VARIABLE help_rc
    OUTPUT_VARIABLE help_out
    ERROR_VARIABLE help_err
    TIMEOUT 30)
if(NOT help_rc EQUAL 0 OR NOT help_out MATCHES "--crash-context DIR")
    string(APPEND errors "OFF help failed: exit=${help_rc}; stdout=${help_out}; stderr=${help_err}\n")
endif()
execute_process(
    COMMAND "${core_app}" --crash-context "${off_spool}"
    RESULT_VARIABLE unavailable_rc
    OUTPUT_VARIABLE unavailable_out
    ERROR_VARIABLE unavailable_err
    TIMEOUT 30)
if(NOT unavailable_rc EQUAL 2 OR
        NOT unavailable_err MATCHES "--crash-context is unavailable in this build")
    string(APPEND errors
        "OFF option was not explicitly unavailable: exit=${unavailable_rc}; stdout=${unavailable_out}; stderr=${unavailable_err}\n")
endif()
execute_process(
    COMMAND "${core_app}" --crash-context=
    RESULT_VARIABLE empty_rc
    OUTPUT_VARIABLE empty_out
    ERROR_VARIABLE empty_err
    TIMEOUT 30)
if(NOT empty_rc EQUAL 2 OR NOT empty_err MATCHES "--crash-context requires a nonempty directory")
    string(APPEND errors "OFF empty value failed: exit=${empty_rc}; stdout=${empty_out}; stderr=${empty_err}\n")
endif()
if(EXISTS "${off_spool}")
    string(APPEND errors "OFF option created a crash spool\n")
endif()
file(REMOVE_RECURSE "${off_spool}")
if(NOT "${errors}" STREQUAL "")
    message(FATAL_ERROR "core_app OFF build/CLI contract failed:\n${errors}")
endif()
message(STATUS "BREAK_ENABLE_CRASH=OFF configure/build and unavailable CLI contract passed")
