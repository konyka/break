foreach(var REPOSITORY_ROOT CHECKOUT_CONTRACT FORMAL_ASSET_CONTRACT NAMING_CONTRACT
        ENGINE_SOURCE_DIR PLAN_FILE DESIGN_FILE WORK)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required for the dangling .git regression")
    endif()
endforeach()

function(core_app_dangling_unverified reason)
    message(STATUS "UNVERIFIED: core_app dangling .git fixture skipped: ${reason}")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    message(FATAL_ERROR
        "UNVERIFIED: core_app dangling .git fixture skipped: ${reason}; "
        "cmake < 3.29 cannot exit 77")
endfunction()

if(NOT DEFINED GIT_EXECUTABLE OR NOT GIT_EXECUTABLE)
    core_app_dangling_unverified("Git executable is unavailable")
endif()

get_filename_component(repository_root "${REPOSITORY_ROOT}" ABSOLUTE)
get_filename_component(work "${WORK}" ABSOLUTE)
file(REMOVE_RECURSE "${work}")
set(fixture "${work}/repository")
file(MAKE_DIRECTORY "${fixture}/engine" "${fixture}/docs/design")
configure_file("${repository_root}/.gitattributes" "${fixture}/.gitattributes" COPYONLY)
configure_file("${repository_root}/.gitignore" "${fixture}/.gitignore" COPYONLY)
configure_file("${repository_root}/docs/design/editor_phase1.md"
    "${fixture}/docs/design/editor_phase1.md" COPYONLY)

set(missing_target "${work}/definitely-missing-git-target")
file(CREATE_LINK "${missing_target}" "${fixture}/.git" SYMBOLIC
    RESULT symlink_result)
if(NOT "${symlink_result}" STREQUAL "0")
    core_app_dangling_unverified("symlink creation failed: ${symlink_result}")
endif()
if(NOT IS_SYMLINK "${fixture}/.git" OR EXISTS "${fixture}/.git")
    message(FATAL_ERROR
        "fixture must be a dangling .git symlink: IS_SYMLINK/EXISTS precondition failed")
endif()
message(STATUS "Dangling .git fixture confirmed: IS_SYMLINK=TRUE EXISTS=FALSE")

set_property(GLOBAL PROPERTY CORE_APP_DANGLING_ERRORS "")
function(run_dangling_contract name contract)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E env
            "GIT_CEILING_DIRECTORIES=${repository_root}"
            "${CMAKE_COMMAND}" ${ARGN}
            "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
            -P "${contract}"
        RESULT_VARIABLE contract_result
        OUTPUT_VARIABLE contract_output
        ERROR_VARIABLE contract_error)
    set(contract_log "${contract_output}${contract_error}")
    set(contract_failure "")
    if("${contract_result}" STREQUAL "0")
        string(APPEND contract_failure
            "${name}: dangling .git metadata unexpectedly passed\n${contract_log}\n")
    elseif("${contract_result}" STREQUAL "77")
        string(APPEND contract_failure
            "${name}: dangling .git metadata returned skip code 77\n${contract_log}\n")
    endif()
    foreach(token IN ITEMS "UNVERIFIED:" "CORE_APP_TRACKING_UNVERIFIED")
        string(FIND "${contract_log}" "${token}" token_position)
        if(NOT token_position EQUAL -1)
            string(APPEND contract_failure
                "${name}: dangling .git metadata printed ${token}\n${contract_log}\n")
        endif()
    endforeach()
    string(FIND "${contract_log}" "git rev-parse --git-dir failed:" failure_position)
    if(failure_position EQUAL -1)
        string(APPEND contract_failure
            "${name}: dangling .git metadata failed for an unexpected reason\n${contract_log}\n")
    endif()
    if(contract_failure)
        get_property(errors GLOBAL PROPERTY CORE_APP_DANGLING_ERRORS)
        string(APPEND errors "${contract_failure}")
        set_property(GLOBAL PROPERTY CORE_APP_DANGLING_ERRORS "${errors}")
    else()
        message(STATUS "${name}: dangling .git metadata failed without UNVERIFIED as required")
    endif()
endfunction()

run_dangling_contract(checkout "${CHECKOUT_CONTRACT}"
    "-DREPOSITORY_ROOT=${fixture}")
run_dangling_contract(formal_assets "${FORMAL_ASSET_CONTRACT}"
    "-DENGINE_SOURCE_DIR=${fixture}/engine")
run_dangling_contract(naming "${NAMING_CONTRACT}"
    "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
    "-DREPOSITORY_ROOT=${fixture}"
    "-DPLAN_FILE=${PLAN_FILE}"
    "-DDESIGN_FILE=${DESIGN_FILE}")
get_property(errors GLOBAL PROPERTY CORE_APP_DANGLING_ERRORS)
if(errors)
    message(FATAL_ERROR "dangling .git contract failures:\n${errors}")
endif()
