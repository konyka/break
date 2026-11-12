foreach(var ENGINE_SOURCE_DIR REPOSITORY_ROOT PLAN_FILE DESIGN_FILE GIT_EXECUTABLE
        CORE_APP NETWORK_ENABLED CTEST_EXECUTABLE WORK NESTED_ENGINE_RHI_BACKEND
        NESTED_CMAKE_GENERATOR)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()
if(NOT DEFINED NESTED_CTEST_CONFIG)
    message(FATAL_ERROR "NESTED_CTEST_CONFIG is required")
endif()
set(nested_ctest_config_args)
if(NOT "${NESTED_CTEST_CONFIG}" STREQUAL "")
    list(APPEND nested_ctest_config_args -C "${NESTED_CTEST_CONFIG}")
endif()
if(NESTED_CMAKE_GENERATOR MATCHES "Visual Studio|Xcode|Multi-Config" AND
        "${NESTED_CTEST_CONFIG}" STREQUAL "")
    message(FATAL_ERROR "a multi-config nested CTest requires NESTED_CTEST_CONFIG")
endif()
set(nested_configure_defs "-DENGINE_RHI_BACKEND=${NESTED_ENGINE_RHI_BACKEND}")
set(nested_ctest_defs "\"-DNESTED_ENGINE_RHI_BACKEND=${NESTED_ENGINE_RHI_BACKEND}\"")
foreach(cache_var Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
    if(DEFINED ${cache_var} AND NOT "${${cache_var}}" STREQUAL "")
        list(APPEND nested_configure_defs "-D${cache_var}=${${cache_var}}")
        string(APPEND nested_ctest_defs " \"-D${cache_var}=${${cache_var}}\"")
    endif()
endforeach()
if(NOT EXISTS "${REPOSITORY_ROOT}/.git")
    message(FATAL_ERROR "core_app compatibility contract requires a real Git checkout")
endif()

set_property(GLOBAL PROPERTY CORE_APP_COMPAT_ERRORS "")
function(record_error text)
    get_property(errors GLOBAL PROPERTY CORE_APP_COMPAT_ERRORS)
    string(APPEND errors "${text}\n")
    set_property(GLOBAL PROPERTY CORE_APP_COMPAT_ERRORS "${errors}")
endfunction()

function(run_case name expectation)
    execute_process(
        COMMAND ${ARGN}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error
        TIMEOUT 180)
    set(log "${output}${error}")
    set_property(GLOBAL PROPERTY CORE_APP_COMPAT_LAST_LOG "${log}")
    if(expectation STREQUAL "PASS" AND NOT "${result}" STREQUAL "0")
        record_error("${name}: exit=${result}, expected PASS\n${log}")
    elseif(expectation STREQUAL "FAIL" AND
            ("${result}" STREQUAL "0" OR "${result}" STREQUAL "77"))
        record_error("${name}: exit=${result}, expected FAIL\n${log}")
    endif()
endfunction()

function(expect_log_contains name text)
    get_property(log GLOBAL PROPERTY CORE_APP_COMPAT_LAST_LOG)
    string(FIND "${log}" "${text}" index)
    if(index LESS 0)
        record_error("${name}: missing '${text}'\n${log}")
    endif()
endfunction()

function(expect_log_lacks name text)
    get_property(log GLOBAL PROPERTY CORE_APP_COMPAT_LAST_LOG)
    string(FIND "${log}" "${text}" index)
    if(NOT index LESS 0)
        record_error("${name}: unexpectedly contained '${text}'\n${log}")
    endif()
endfunction()

function(expect_nested_ctest_complete name)
    expect_log_lacks(${name} "Not Run")
    expect_log_lacks(${name} "NOT_AVAILABLE")
endfunction()

function(expect_tracking_skips name expected)
    get_property(log GLOBAL PROPERTY CORE_APP_COMPAT_LAST_LOG)
    string(REGEX MATCHALL "CORE_APP_TRACKING_UNVERIFIED" matches "${log}")
    list(LENGTH matches count)
    if(NOT count EQUAL expected)
        record_error("${name}: tracking skip count=${count}, expected=${expected}\n${log}")
    endif()
endfunction()

function(prepare_index index_file)
    file(REMOVE "${index_file}")
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E env "GIT_INDEX_FILE=${index_file}"
            "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" read-tree HEAD
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error)
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "failed to prepare temporary Git index: ${output}${error}")
    endif()
endfunction()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")
set(archive_root "${WORK}/source")
set(archive_tar "${WORK}/source.tar")
file(MAKE_DIRECTORY "${archive_root}")
execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" archive
        --format=tar "--output=${archive_tar}" HEAD
    RESULT_VARIABLE archive_result
    OUTPUT_VARIABLE archive_output
    ERROR_VARIABLE archive_error)
if(NOT archive_result EQUAL 0)
    message(FATAL_ERROR "git archive HEAD failed: ${archive_output}${archive_error}")
endif()
execute_process(
    COMMAND "${CMAKE_COMMAND}" -E tar xf "${archive_tar}"
    WORKING_DIRECTORY "${archive_root}"
    RESULT_VARIABLE extract_result
    OUTPUT_VARIABLE extract_output
    ERROR_VARIABLE extract_error)
if(NOT extract_result EQUAL 0)
    message(FATAL_ERROR "HEAD archive extraction failed: ${extract_output}${extract_error}")
endif()
if(EXISTS "${archive_root}/.git")
    message(FATAL_ERROR "HEAD archive unexpectedly contains Git metadata")
endif()

set(archive_engine "${archive_root}/engine")
foreach(relative_path IN ITEMS
        CMakeLists.txt
        tests/test_core_app_target_contract.cmake
        tests/test_core_app_nested_contract.cmake
        tests/test_core_app_formal_assets.cmake
        tests/test_core_app_naming_contract.cmake
        tests/test_core_app_contract_compat.cmake)
    configure_file("${ENGINE_SOURCE_DIR}/${relative_path}"
        "${archive_engine}/${relative_path}" COPYONLY)
endforeach()
if(NESTED_ENGINE_RHI_BACKEND STREQUAL "d3d12")
    function(expect_archive_agility_hashes context)
        foreach(dll_name IN ITEMS D3D12Core.dll d3d12SDKLayers.dll)
            set(relative "external/d3d12/agility/build/native/bin/x64/${dll_name}")
            set(source "${ENGINE_SOURCE_DIR}/${relative}")
            set(destination "${archive_engine}/${relative}")
            if(NOT EXISTS "${source}")
                message(FATAL_ERROR "real parent Agility input is missing: ${source}")
            endif()
            if(NOT EXISTS "${destination}")
                message(FATAL_ERROR "staged Agility destination is missing (${context}): ${destination}")
            endif()
            file(SHA256 "${source}" source_hash)
            file(SHA256 "${destination}" destination_hash)
            if(NOT "${source_hash}" STREQUAL "${destination_hash}")
                message(FATAL_ERROR "staged Agility hash mismatch (${context}): ${relative}")
            endif()
        endforeach()
    endfunction()
    foreach(dll_name IN ITEMS D3D12Core.dll d3d12SDKLayers.dll)
        set(relative "external/d3d12/agility/build/native/bin/x64/${dll_name}")
        set(source "${ENGINE_SOURCE_DIR}/${relative}")
        set(destination "${archive_engine}/${relative}")
        if(NOT EXISTS "${source}")
            message(FATAL_ERROR "real parent Agility input is missing: ${source}")
        endif()
        configure_file("${source}" "${destination}" COPYONLY)
    endforeach()
    expect_archive_agility_hashes("after staging")
endif()
set(archive_plan "${archive_root}/docs/superpowers/plans/2026-11-03-core-app-integration.md")
set(archive_design "${archive_root}/docs/design/core_app_integration.md")
set(formal_contract "${ENGINE_SOURCE_DIR}/tests/test_core_app_formal_assets.cmake")
set(naming_contract "${ENGINE_SOURCE_DIR}/tests/test_core_app_naming_contract.cmake")
set(target_contract "${archive_engine}/tests/test_core_app_target_contract.cmake")

run_case(real_formal PASS "${CMAKE_COMMAND}"
    "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
    -P "${formal_contract}")
expect_log_contains(real_formal "All 11 formal core_app assets are tracked, including tone.wav")
run_case(real_naming PASS "${CMAKE_COMMAND}"
    "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DREPOSITORY_ROOT=${REPOSITORY_ROOT}"
    "-DPLAN_FILE=${PLAN_FILE}"
    "-DDESIGN_FILE=${DESIGN_FILE}"
    "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
    -P "${naming_contract}")
expect_log_contains(real_naming "core_app naming, target, interface, and 11-asset contract passed")

run_case(formal_git_error PASS "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" rev-parse --git-dir)
run_case(formal_git_error FAIL "${CMAKE_COMMAND}"
    "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DGIT_EXECUTABLE=${CMAKE_COMMAND}"
    -P "${formal_contract}")
expect_log_contains(formal_git_error "git rev-parse --git-dir failed:")
expect_log_lacks(formal_git_error "CORE_APP_TRACKING_UNVERIFIED")
run_case(naming_git_error FAIL "${CMAKE_COMMAND}"
    "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DREPOSITORY_ROOT=${REPOSITORY_ROOT}"
    "-DPLAN_FILE=${PLAN_FILE}"
    "-DDESIGN_FILE=${DESIGN_FILE}"
    "-DGIT_EXECUTABLE=${CMAKE_COMMAND}"
    -P "${naming_contract}")
expect_log_contains(naming_git_error "git rev-parse --git-dir failed:")
expect_log_lacks(naming_git_error "CORE_APP_TRACKING_UNVERIFIED")

set(missing_index "${WORK}/missing.index")
prepare_index("${missing_index}")
execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env "GIT_INDEX_FILE=${missing_index}"
        "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" rm --cached --ignore-unmatch
        -- engine/assets/core_app/tone.wav
    RESULT_VARIABLE missing_result
    OUTPUT_VARIABLE missing_output
    ERROR_VARIABLE missing_error)
if(NOT missing_result EQUAL 0)
    message(FATAL_ERROR "failed to create missing-asset index: ${missing_output}${missing_error}")
endif()
run_case(formal_missing_asset FAIL "${CMAKE_COMMAND}" -E env "GIT_INDEX_FILE=${missing_index}"
    "${CMAKE_COMMAND}" "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}" -P "${formal_contract}")
expect_log_contains(formal_missing_asset "formal asset tracking mismatch: 10 tracked, 11 required")
run_case(naming_missing_asset FAIL "${CMAKE_COMMAND}" -E env "GIT_INDEX_FILE=${missing_index}"
    "${CMAKE_COMMAND}" "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DREPOSITORY_ROOT=${REPOSITORY_ROOT}" "-DPLAN_FILE=${PLAN_FILE}"
    "-DDESIGN_FILE=${DESIGN_FILE}" "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
    -P "${naming_contract}")
expect_log_contains(naming_missing_asset "core_app asset tracking mismatch: 10 tracked, 11 required")

set(extra_index "${WORK}/extra.index")
prepare_index("${extra_index}")
execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" rev-parse
        HEAD:engine/assets/core_app/tone.wav
    RESULT_VARIABLE blob_result
    OUTPUT_VARIABLE blob
    ERROR_VARIABLE blob_error
    OUTPUT_STRIP_TRAILING_WHITESPACE)
if(NOT blob_result EQUAL 0)
    message(FATAL_ERROR "failed to read asset blob: ${blob_error}")
endif()
execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env "GIT_INDEX_FILE=${extra_index}"
        "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" update-index --add
        --cacheinfo "100644,${blob},engine/assets/core_app/compat_extra.sidecar"
    RESULT_VARIABLE extra_result
    OUTPUT_VARIABLE extra_output
    ERROR_VARIABLE extra_error)
if(NOT extra_result EQUAL 0)
    message(FATAL_ERROR "failed to create extra-asset index: ${extra_output}${extra_error}")
endif()
run_case(formal_extra_asset FAIL "${CMAKE_COMMAND}" -E env "GIT_INDEX_FILE=${extra_index}"
    "${CMAKE_COMMAND}" "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}" -P "${formal_contract}")
expect_log_contains(formal_extra_asset "formal asset tracking mismatch: 12 tracked, 11 required")
expect_log_lacks(formal_extra_asset "CORE_APP_TRACKING_UNVERIFIED")
run_case(naming_extra_asset FAIL "${CMAKE_COMMAND}" -E env "GIT_INDEX_FILE=${extra_index}"
    "${CMAKE_COMMAND}" "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DREPOSITORY_ROOT=${REPOSITORY_ROOT}" "-DPLAN_FILE=${PLAN_FILE}"
    "-DDESIGN_FILE=${DESIGN_FILE}" "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
    -P "${naming_contract}")
expect_log_contains(naming_extra_asset "core_app asset tracking mismatch: 12 tracked, 11 required")
expect_log_lacks(naming_extra_asset "CORE_APP_TRACKING_UNVERIFIED")

if(UNIX)
    execute_process(COMMAND id -u RESULT_VARIABLE id_result OUTPUT_VARIABLE id_output
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(id_result EQUAL 0 AND NOT id_output STREQUAL "0")
        set(permission_formal_root "${WORK}/permission-formal")
        set(permission_naming_blocked "${archive_root}/permission-blocked")
        set(permission_naming_root "${permission_naming_blocked}/..")
        file(MAKE_DIRECTORY "${permission_formal_root}/engine")
        file(MAKE_DIRECTORY "${permission_naming_blocked}")
        set(permission_fixture "${WORK}/permission-fixture")
        set(permission_build "${WORK}/permission-build")
        file(MAKE_DIRECTORY "${permission_fixture}")
        set(permission_source "${permission_fixture}/CMakeLists.txt")
        file(WRITE "${permission_source}" "cmake_minimum_required(VERSION 3.25)\n")
        file(APPEND "${permission_source}" "project(core_app_permission_compat NONE)\nenable_testing()\n")
        file(APPEND "${permission_source}"
            "add_test(NAME test_core_app_formal_permission COMMAND \"${CMAKE_COMMAND}\"\n")
        file(APPEND "${permission_source}"
            "  \"-DENGINE_SOURCE_DIR=${permission_formal_root}/engine\" \"-DGIT_EXECUTABLE=${GIT_EXECUTABLE}\"\n")
        file(APPEND "${permission_source}" "  -P \"${formal_contract}\")\n")
        file(APPEND "${permission_source}"
            "add_test(NAME test_core_app_naming_permission COMMAND \"${CMAKE_COMMAND}\"\n")
        file(APPEND "${permission_source}"
            "  \"-DENGINE_SOURCE_DIR=${archive_engine}\" \"-DREPOSITORY_ROOT=${permission_naming_root}\"\n")
        file(APPEND "${permission_source}"
            "  \"-DPLAN_FILE=${archive_plan}\" \"-DDESIGN_FILE=${archive_design}\"\n")
        file(APPEND "${permission_source}"
            "  \"-DGIT_EXECUTABLE=${GIT_EXECUTABLE}\" -P \"${archive_engine}/tests/test_core_app_naming_contract.cmake\")\n")
        file(APPEND "${permission_source}"
            "set_tests_properties(test_core_app_formal_permission test_core_app_naming_permission\n")
        file(APPEND "${permission_source}"
            "  PROPERTIES SKIP_RETURN_CODE 77 SKIP_REGULAR_EXPRESSION \"CORE_APP_TRACKING_UNVERIFIED\")\n")
        run_case(permission_fixture_configure PASS "${CMAKE_COMMAND}"
            -S "${permission_fixture}" -B "${permission_build}"
            -G "${NESTED_CMAKE_GENERATOR}")
        file(CHMOD "${permission_formal_root}" PERMISSIONS OWNER_READ OWNER_WRITE)
        file(CHMOD "${permission_naming_blocked}" PERMISSIONS OWNER_READ OWNER_WRITE)
        run_case(permission_git_probe FAIL "${CMAKE_COMMAND}" -E env
            --unset=GIT_DIR --unset=GIT_WORK_TREE
            "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "LC_ALL=C"
            "${GIT_EXECUTABLE}" -C "${permission_formal_root}" rev-parse --git-dir)
        expect_log_contains(permission_git_probe "cannot change to")
        run_case(formal_permission FAIL "${CMAKE_COMMAND}" -E env
            "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CTEST_EXECUTABLE}"
            --test-dir "${permission_build}" ${nested_ctest_config_args}
            -R "^test_core_app_formal_permission$" -V)
        expect_log_contains(formal_permission "cannot change to")
        expect_log_contains(formal_permission "git rev-parse --git-dir failed:")
        expect_log_lacks(formal_permission "CORE_APP_TRACKING_UNVERIFIED")
        run_case(naming_permission FAIL "${CMAKE_COMMAND}" -E env
            "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CTEST_EXECUTABLE}"
            --test-dir "${permission_build}" ${nested_ctest_config_args}
            -R "^test_core_app_naming_permission$" -V)
        expect_log_contains(naming_permission "cannot change to")
        expect_log_contains(naming_permission "git rev-parse --git-dir failed:")
        expect_log_lacks(naming_permission "CORE_APP_TRACKING_UNVERIFIED")
        file(CHMOD "${permission_formal_root}" PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
        file(CHMOD "${permission_naming_blocked}" PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    endif()
endif()

file(MAKE_DIRECTORY "${archive_root}/.git/objects" "${archive_root}/.git/refs")
file(WRITE "${archive_root}/.git/HEAD" "not a valid HEAD\n")
set(corrupt_fixture "${WORK}/corrupt-fixture")
set(corrupt_build "${WORK}/corrupt-build")
file(MAKE_DIRECTORY "${corrupt_fixture}")
set(corrupt_source "${corrupt_fixture}/CMakeLists.txt")
file(WRITE "${corrupt_source}" "cmake_minimum_required(VERSION 3.25)\n")
file(APPEND "${corrupt_source}" "project(core_app_corrupt_compat NONE)\nenable_testing()\n")
file(APPEND "${corrupt_source}"
    "add_test(NAME test_core_app_formal_corrupt COMMAND \"${CMAKE_COMMAND}\"\n")
file(APPEND "${corrupt_source}"
    "  \"-DENGINE_SOURCE_DIR=${archive_engine}\" \"-DGIT_EXECUTABLE=${GIT_EXECUTABLE}\"\n")
file(APPEND "${corrupt_source}" "  -P \"${formal_contract}\")\n")
file(APPEND "${corrupt_source}"
    "add_test(NAME test_core_app_naming_corrupt COMMAND \"${CMAKE_COMMAND}\"\n")
file(APPEND "${corrupt_source}"
    "  \"-DENGINE_SOURCE_DIR=${archive_engine}\" \"-DREPOSITORY_ROOT=${archive_root}\"\n")
file(APPEND "${corrupt_source}"
    "  \"-DPLAN_FILE=${archive_plan}\" \"-DDESIGN_FILE=${archive_design}\"\n")
file(APPEND "${corrupt_source}"
    "  \"-DGIT_EXECUTABLE=${GIT_EXECUTABLE}\" -P \"${archive_engine}/tests/test_core_app_naming_contract.cmake\")\n")
file(APPEND "${corrupt_source}"
    "set_tests_properties(test_core_app_formal_corrupt test_core_app_naming_corrupt\n")
file(APPEND "${corrupt_source}"
    "  PROPERTIES SKIP_RETURN_CODE 77 SKIP_REGULAR_EXPRESSION \"CORE_APP_TRACKING_UNVERIFIED\")\n")
run_case(corrupt_fixture_configure PASS "${CMAKE_COMMAND}"
    -S "${corrupt_fixture}" -B "${corrupt_build}"
    -G "${NESTED_CMAKE_GENERATOR}")
run_case(corrupt_git_probe FAIL "${CMAKE_COMMAND}" -E env
    --unset=GIT_DIR --unset=GIT_WORK_TREE
    "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "LC_ALL=C"
    "${GIT_EXECUTABLE}" -C "${archive_root}" rev-parse --git-dir)
expect_log_contains(corrupt_git_probe
    "fatal: not a git repository (or any of the parent directories): .git")
run_case(formal_corrupt FAIL "${CMAKE_COMMAND}" -E env
    "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CTEST_EXECUTABLE}"
    --test-dir "${corrupt_build}" ${nested_ctest_config_args}
    -R "^test_core_app_formal_corrupt$" -V)
expect_log_contains(formal_corrupt "fatal: not a git repository")
expect_log_contains(formal_corrupt "git rev-parse --git-dir failed:")
expect_log_lacks(formal_corrupt "CORE_APP_TRACKING_UNVERIFIED")
expect_nested_ctest_complete(formal_corrupt)
run_case(naming_corrupt FAIL "${CMAKE_COMMAND}" -E env
    "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CTEST_EXECUTABLE}"
    --test-dir "${corrupt_build}" ${nested_ctest_config_args}
    -R "^test_core_app_naming_corrupt$" -V)
expect_log_contains(naming_corrupt "fatal: not a git repository")
expect_log_contains(naming_corrupt "git rev-parse --git-dir failed:")
expect_log_lacks(naming_corrupt "CORE_APP_TRACKING_UNVERIFIED")
expect_nested_ctest_complete(naming_corrupt)
file(REMOVE_RECURSE "${archive_root}/.git")

if(NESTED_ENGINE_RHI_BACKEND STREQUAL "d3d12")
    expect_archive_agility_hashes("before D3D12Core gate mutation")
    set(missing_core_relative "external/d3d12/agility/build/native/bin/x64/D3D12Core.dll")
    set(missing_core_source "${ENGINE_SOURCE_DIR}/${missing_core_relative}")
    set(missing_core_destination "${archive_engine}/${missing_core_relative}")
    file(REMOVE "${missing_core_destination}")
    set(missing_core_build "${WORK}/archive-missing-core-build")
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E env
            "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CMAKE_COMMAND}"
            -S "${archive_engine}" -B "${missing_core_build}"
            -G "${NESTED_CMAKE_GENERATOR}"
            -DENGINE_BUILD_TESTS=ON -DENGINE_ENABLE_IPO=OFF
            -DBREAK_ENABLE_SNOWFLAKE=OFF ${nested_configure_defs}
        RESULT_VARIABLE missing_core_result
        OUTPUT_VARIABLE missing_core_output
        ERROR_VARIABLE missing_core_error
        TIMEOUT 180)
    configure_file("${missing_core_source}" "${missing_core_destination}" COPYONLY)
    expect_archive_agility_hashes("after D3D12Core gate mutation restoration")
    set(missing_core_log "${missing_core_output}${missing_core_error}")
    if("${missing_core_result}" STREQUAL "0" OR "${missing_core_result}" STREQUAL "77")
        record_error("archive_d3d12_missing_core: exit=${missing_core_result}, expected FAIL\n${missing_core_log}")
    endif()
    string(FIND "${missing_core_log}" "D3D12Core.dll missing" missing_core_diagnostic_index)
    if(missing_core_diagnostic_index LESS 0)
        record_error("archive_d3d12_missing_core: missing 'D3D12Core.dll missing'\n${missing_core_log}")
    endif()
    if(NOT "${missing_core_result}" STREQUAL "0" AND
            NOT "${missing_core_result}" STREQUAL "77" AND
            NOT missing_core_diagnostic_index LESS 0)
        message(STATUS "archive_d3d12_missing_core: D3D12Core.dll missing rejected; restored; SHA-256 verified")
    endif()
endif()

set(archive_build "${WORK}/archive-build")
run_case(archive_configure PASS "${CMAKE_COMMAND}" -E env
    "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CMAKE_COMMAND}"
    -S "${archive_engine}" -B "${archive_build}"
    -G "${NESTED_CMAKE_GENERATOR}"
    -DENGINE_BUILD_TESTS=ON -DENGINE_ENABLE_IPO=OFF
    -DBREAK_ENABLE_SNOWFLAKE=OFF ${nested_configure_defs})
if(NESTED_ENGINE_RHI_BACKEND STREQUAL "d3d12")
    expect_archive_agility_hashes("after archive configure")
endif()
if(EXISTS "${archive_build}/CMakeCache.txt")
    file(STRINGS "${archive_build}/CMakeCache.txt" archive_backend
        REGEX "^ENGINE_RHI_BACKEND:STRING=")
    if(NOT archive_backend STREQUAL "ENGINE_RHI_BACKEND:STRING=${NESTED_ENGINE_RHI_BACKEND}")
        record_error("archive backend '${archive_backend}' did not follow '${NESTED_ENGINE_RHI_BACKEND}'")
    endif()
    if(NOT NESTED_ENGINE_RHI_BACKEND STREQUAL "auto")
        file(STRINGS "${archive_build}/CMakeCache.txt" archive_effective
            REGEX "^ENGINE_RHI_BACKEND_EFFECTIVE:INTERNAL=")
        if(NOT archive_effective STREQUAL
                "ENGINE_RHI_BACKEND_EFFECTIVE:INTERNAL=${NESTED_ENGINE_RHI_BACKEND}")
            record_error("archive effective backend '${archive_effective}' did not follow '${NESTED_ENGINE_RHI_BACKEND}'")
        endif()
    endif()
endif()
if(EXISTS "${archive_build}/CTestTestfile.cmake")
    file(READ "${archive_build}/CTestTestfile.cmake" archive_ctest)
    foreach(test_name IN ITEMS test_core_app_nm_missing test_core_app_nm_unsupported
            test_core_app_formal_asset_tracking test_core_app_naming_contract)
        string(REGEX MATCH
            "set_tests_properties\\([^\n]*${test_name}[^\n]*SKIP_REGULAR_EXPRESSION \"UNVERIFIED: core_app symbol scan skipped:\\|CORE_APP_TRACKING_UNVERIFIED\""
            skip_property "${archive_ctest}")
        if(NOT skip_property)
            record_error("${test_name}: missing old-CMake skip regular expression")
        endif()
    endforeach()
    run_case(archive_tracking PASS "${CMAKE_COMMAND}" -E env
        "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CTEST_EXECUTABLE}"
        --test-dir "${archive_build}" ${nested_ctest_config_args}
        -R "^test_core_app_(formal_asset_tracking|naming_contract)$" -V)
    expect_tracking_skips(archive_tracking 2)
    expect_log_lacks(archive_tracking "All 11 formal core_app assets are tracked, including tone.wav")
    expect_log_lacks(archive_tracking "core_app naming, target, interface, and 11-asset contract passed")
    expect_nested_ctest_complete(archive_tracking)
endif()

string(CONCAT legacy_domain "c" "ry")
set(backtick [=[`]=])
string(CONCAT exact_exemption "${backtick}" "${legacy_domain}" "-integration" "${backtick}")
string(CONCAT bracket_exemption "string(REPLACE [=[" "${exact_exemption}"
    "]=] \"\" text \"\${text}\")")
file(READ "${naming_contract}" naming_contract_text)
string(FIND "${naming_contract_text}" "${bracket_exemption}" bracket_exemption_index)
if(bracket_exemption_index LESS 0)
    record_error("naming contract: exact backtick exemption must use a bracket argument")
endif()
file(APPEND "${archive_engine}/apps/core_app/core_app.c" "\n${exact_exemption}\n")
if(EXISTS "${archive_build}/CTestTestfile.cmake")
    run_case(archive_exact_exemption PASS "${CMAKE_COMMAND}" -E env
        "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CTEST_EXECUTABLE}"
        --test-dir "${archive_build}" ${nested_ctest_config_args}
        -R "^test_core_app_naming_contract$" -V)
    expect_tracking_skips(archive_exact_exemption 1)
    expect_log_lacks(archive_exact_exemption "core_app naming contract failed")
    expect_log_lacks(archive_exact_exemption "core_app naming, target, interface, and 11-asset contract passed")
    expect_nested_ctest_complete(archive_exact_exemption)
endif()

function(run_naming_mutation name mutation expected_error)
    configure_file("${ENGINE_SOURCE_DIR}/apps/core_app/core_app.c"
        "${archive_engine}/apps/core_app/core_app.c" COPYONLY)
    file(APPEND "${archive_engine}/apps/core_app/core_app.c" "\n${mutation}\n")
    run_case(${name} FAIL "${CMAKE_COMMAND}" -E env
        "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CMAKE_COMMAND}"
        "-DENGINE_SOURCE_DIR=${archive_engine}" "-DREPOSITORY_ROOT=${archive_root}"
        "-DPLAN_FILE=${archive_plan}" "-DDESIGN_FILE=${archive_design}"
        "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
        -P "${archive_engine}/tests/test_core_app_naming_contract.cmake")
    expect_log_contains(${name} "${expected_error}")
    expect_log_lacks(${name} "CORE_APP_TRACKING_UNVERIFIED")
endfunction()
run_naming_mutation(standalone_domain_violation "${legacy_domain}"
    "forbidden legacy domain token ${legacy_domain}")
string(CONCAT extended_integration "${backtick}" "${legacy_domain}" "-integration2" "${backtick}")
run_naming_mutation(extended_integration_violation "${extended_integration}"
    "forbidden legacy domain token ${legacy_domain}")
configure_file("${ENGINE_SOURCE_DIR}/apps/core_app/core_app.c"
    "${archive_engine}/apps/core_app/core_app.c" COPYONLY)

set(nm_fixture "${WORK}/nm-fixture")
file(MAKE_DIRECTORY "${nm_fixture}")
set(nm_ctest_source "${nm_fixture}/CMakeLists.txt")
file(WRITE "${nm_ctest_source}" "cmake_minimum_required(VERSION 3.25)\n")
file(APPEND "${nm_ctest_source}" "project(core_app_nm_compat NONE)\nenable_testing()\n")
foreach(test_name IN ITEMS test_core_app_nm_missing test_core_app_nm_unsupported)
    if(test_name STREQUAL "test_core_app_nm_missing")
        set(nm_arguments "\"-DNM=\" \"-DNM_CAPABLE=FALSE\"")
    else()
        set(nm_arguments "\"-DNM=${CMAKE_COMMAND}\" \"-DNM_CAPABLE=TRUE\"")
    endif()
    string(APPEND nm_arguments " ${nested_ctest_defs}")
    file(APPEND "${nm_ctest_source}"
        "add_test(NAME ${test_name} COMMAND \"${CMAKE_COMMAND}\"\n")
    file(APPEND "${nm_ctest_source}"
        "  \"-DENGINE_CMAKE=${archive_engine}/CMakeLists.txt\" \"-DCORE_APP=${CORE_APP}\"\n")
    file(APPEND "${nm_ctest_source}"
        "  \"-DNETWORK_ENABLED=${NETWORK_ENABLED}\" \"-DCONTRACT_BUILD_ROOT=${WORK}/${test_name}\"\n")
    file(APPEND "${nm_ctest_source}"
        "  ${nm_arguments} -P \"${target_contract}\")\n")
endforeach()
set(bad_engine "${WORK}/bad-engine")
file(MAKE_DIRECTORY "${bad_engine}")
file(WRITE "${bad_engine}/CMakeLists.txt"
    "engine_link_rhi_backend(core_app)\nmessage(FATAL_ERROR \"core_app nested configure sentinel\")\n")
foreach(test_name IN ITEMS test_core_app_nested_error test_core_app_cli_error)
    if(test_name STREQUAL "test_core_app_nested_error")
        set(case_engine "${bad_engine}/CMakeLists.txt")
        set(case_executable "${CORE_APP}")
    else()
        set(case_engine "${archive_engine}/CMakeLists.txt")
        set(case_executable "${WORK}/missing-core-app")
    endif()
    file(APPEND "${nm_ctest_source}"
        "add_test(NAME ${test_name} COMMAND \"${CMAKE_COMMAND}\"\n")
    file(APPEND "${nm_ctest_source}"
        "  \"-DENGINE_CMAKE=${case_engine}\" \"-DCORE_APP=${case_executable}\"\n")
    file(APPEND "${nm_ctest_source}"
        "  \"-DNETWORK_ENABLED=${NETWORK_ENABLED}\" \"-DCONTRACT_BUILD_ROOT=${WORK}/${test_name}\"\n")
    file(APPEND "${nm_ctest_source}"
        "  \"-DNM=\" \"-DNM_CAPABLE=FALSE\" ${nested_ctest_defs} -P \"${target_contract}\")\n")
endforeach()
file(APPEND "${nm_ctest_source}"
    "set_tests_properties(test_core_app_nm_missing test_core_app_nm_unsupported\n")
file(APPEND "${nm_ctest_source}"
    "  test_core_app_nested_error test_core_app_cli_error PROPERTIES SKIP_RETURN_CODE 77\n")
file(APPEND "${nm_ctest_source}"
    "  SKIP_REGULAR_EXPRESSION \"UNVERIFIED: core_app symbol scan skipped:|CORE_APP_TRACKING_UNVERIFIED\")\n")
set(nm_build "${WORK}/nm-build")
run_case(nm_fixture_configure PASS "${CMAKE_COMMAND}" -S "${nm_fixture}" -B "${nm_build}"
    -G "${NESTED_CMAKE_GENERATOR}")
run_case(nm_compat_skips PASS "${CMAKE_COMMAND}" -E env
    "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CTEST_EXECUTABLE}"
    --test-dir "${nm_build}" ${nested_ctest_config_args}
    -R "^test_core_app_nm_(missing|unsupported)$" -V)
get_property(nm_log GLOBAL PROPERTY CORE_APP_COMPAT_LAST_LOG)
string(REGEX MATCHALL "UNVERIFIED: core_app symbol scan skipped:" nm_skip_matches "${nm_log}")
list(LENGTH nm_skip_matches nm_skip_count)
if(NOT nm_skip_count EQUAL 2)
    record_error("nm_compat_skips: symbol skip count=${nm_skip_count}, expected=2\n${nm_log}")
endif()
expect_nested_ctest_complete(nm_compat_skips)
foreach(test_name IN ITEMS test_core_app_nested_error test_core_app_cli_error)
    run_case(${test_name} FAIL "${CMAKE_COMMAND}" -E env
        "GIT_CEILING_DIRECTORIES=${REPOSITORY_ROOT}" "${CTEST_EXECUTABLE}"
        --test-dir "${nm_build}" ${nested_ctest_config_args} -R "^${test_name}$" -V)
    expect_log_contains(${test_name} "core_app contract failed before skip:")
    expect_log_lacks(${test_name} "UNVERIFIED: core_app symbol scan skipped:")
    if(test_name STREQUAL "test_core_app_nested_error")
        expect_log_contains(${test_name} "no-tests target/scope configure failed:")
    endif()
    expect_nested_ctest_complete(${test_name})
endforeach()

get_property(errors GLOBAL PROPERTY CORE_APP_COMPAT_ERRORS)
if(errors STREQUAL "")
    message(STATUS "nested CTest fixtures formal_corrupt, naming_corrupt, archive_tracking, archive_exact_exemption, test_core_app_nm_missing, test_core_app_nm_unsupported, test_core_app_nested_error, test_core_app_cli_error: no test was unavailable or unrun")
endif()
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "core_app compatibility contract failed:\n${errors}")
endif()
message(STATUS "core_app compatibility contract passed")
