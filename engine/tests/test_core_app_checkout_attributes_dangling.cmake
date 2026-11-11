foreach(var REPOSITORY_ROOT CHECKOUT_CONTRACT WORK)
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
file(MAKE_DIRECTORY "${fixture}")
configure_file("${repository_root}/.gitattributes" "${fixture}/.gitattributes" COPYONLY)

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

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env
        "GIT_CEILING_DIRECTORIES=${repository_root}"
        "${CMAKE_COMMAND}"
        "-DREPOSITORY_ROOT=${fixture}"
        "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
        -P "${CHECKOUT_CONTRACT}"
    RESULT_VARIABLE contract_result
    OUTPUT_VARIABLE contract_output
    ERROR_VARIABLE contract_error)
set(contract_log "${contract_output}${contract_error}")
if("${contract_result}" STREQUAL "0")
    message(FATAL_ERROR "dangling .git metadata unexpectedly passed: ${contract_log}")
endif()
if("${contract_result}" STREQUAL "77")
    message(FATAL_ERROR "dangling .git metadata returned skip code 77: ${contract_log}")
endif()
string(FIND "${contract_log}" "UNVERIFIED:" unverified_position)
if(NOT unverified_position EQUAL -1)
    message(FATAL_ERROR "dangling .git metadata printed UNVERIFIED: ${contract_log}")
endif()
string(FIND "${contract_log}" "git rev-parse --git-dir failed:" failure_position)
if(failure_position EQUAL -1)
    message(FATAL_ERROR
        "dangling .git metadata failed for an unexpected reason: ${contract_log}")
endif()
message(STATUS "Dangling .git metadata failed without UNVERIFIED as required")
