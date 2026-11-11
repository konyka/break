if(POLICY CMP0007)
    cmake_policy(SET CMP0007 NEW)
endif()

if(NOT DEFINED REPOSITORY_ROOT OR "${REPOSITORY_ROOT}" STREQUAL "")
    message(FATAL_ERROR "REPOSITORY_ROOT is required to verify core_app checkout attributes")
endif()

file(READ "${REPOSITORY_ROOT}/.gitattributes" checkout_attributes)
string(REPLACE "\r\n" "\n" checkout_attribute_lines "${checkout_attributes}")
string(REPLACE "\n" ";" checkout_attribute_lines "${checkout_attribute_lines}")
list(FIND checkout_attribute_lines "engine/assets/core_app/* binary" checkout_rule_index)
if(checkout_rule_index EQUAL -1)
    message(FATAL_ERROR
        ".gitattributes must contain the independent line: engine/assets/core_app/* binary")
endif()

function(core_app_checkout_unverified reason)
    message(STATUS "UNVERIFIED: core_app checkout attribute probe skipped: ${reason}")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    message(FATAL_ERROR
        "UNVERIFIED: core_app checkout attribute probe skipped: ${reason}; "
        "cmake < 3.29 cannot exit 77")
endfunction()

if(NOT DEFINED GIT_EXECUTABLE OR NOT GIT_EXECUTABLE)
    core_app_checkout_unverified("Git executable is unavailable")
endif()

set(formal_assets
    engine/assets/core_app/actors.sidecar
    engine/assets/core_app/broken.lua
    engine/assets/core_app/deterministic.scenario
    engine/assets/core_app/director.lua
    engine/assets/core_app/level.banm
    engine/assets/core_app/level.bscn
    engine/assets/core_app/level.fg
    engine/assets/core_app/load_unload.scenario
    engine/assets/core_app/player.lua
    engine/assets/core_app/rollback.scenario
    engine/assets/core_app/tone.wav)
unset(ENV{GIT_DIR})
unset(ENV{GIT_WORK_TREE})
set(ENV{LC_ALL} "C")
execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" rev-parse --git-dir
    RESULT_VARIABLE git_probe_result
    OUTPUT_VARIABLE git_probe_output
    ERROR_VARIABLE git_probe_error)
set(git_probe_log "${git_probe_output}${git_probe_error}")
if(NOT "${git_probe_result}" STREQUAL "0")
    if(NOT EXISTS "${REPOSITORY_ROOT}/.git" AND
            NOT IS_SYMLINK "${REPOSITORY_ROOT}/.git" AND
            "${git_probe_log}" MATCHES
            "fatal: not a git repository \\(or any of the parent directories\\): \\.git")
        core_app_checkout_unverified("${REPOSITORY_ROOT} is not a Git repository")
    endif()
    message(FATAL_ERROR "git rev-parse --git-dir failed: ${git_probe_log}")
endif()

foreach(asset IN LISTS formal_assets)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" check-attr -a -- "${asset}"
        RESULT_VARIABLE attribute_result
        OUTPUT_VARIABLE attribute_output
        ERROR_VARIABLE attribute_error
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(attribute_log "${attribute_output}${attribute_error}")
    if(NOT "${attribute_result}" STREQUAL "0")
        message(FATAL_ERROR "git check-attr failed for ${asset}: ${attribute_log}")
    endif()
    string(FIND "${attribute_log}" "binary: set" binary_position)
    if(binary_position EQUAL -1)
        message(FATAL_ERROR "${asset} does not have binary: set; output=${attribute_log}")
    endif()
    string(FIND "${attribute_log}" "text: set" text_position)
    if(NOT text_position EQUAL -1)
        message(FATAL_ERROR "${asset} unexpectedly has text: set; output=${attribute_log}")
    endif()
endforeach()
message(STATUS "All 11 formal core_app assets have binary checkout attributes")
