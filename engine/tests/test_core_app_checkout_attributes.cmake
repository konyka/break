if(POLICY CMP0007)
    cmake_policy(SET CMP0007 NEW)
endif()

if(NOT DEFINED REPOSITORY_ROOT OR "${REPOSITORY_ROOT}" STREQUAL "")
    message(FATAL_ERROR "REPOSITORY_ROOT is required to verify core_app checkout attributes")
endif()

file(READ "${REPOSITORY_ROOT}/.gitattributes" checkout_attributes)
string(REPLACE "\r\n" "\n" checkout_attribute_lines "${checkout_attributes}")
string(REPLACE "\n" ";" checkout_attribute_lines "${checkout_attribute_lines}")
set(required_rules
    "engine/assets/core_app/*.lua text eol=lf"
    "engine/assets/core_app/*.scenario text eol=lf"
    "engine/assets/core_app/actors.sidecar text eol=lf"
    "engine/assets/core_app/level.banm binary"
    "engine/assets/core_app/level.bscn binary"
    "engine/assets/core_app/level.fg binary"
    "engine/assets/core_app/tone.wav binary"
    "engine/assets/core_app/chime.wav binary")
foreach(rule IN LISTS required_rules)
    list(FIND checkout_attribute_lines "${rule}" checkout_rule_index)
    if(checkout_rule_index EQUAL -1)
        message(FATAL_ERROR ".gitattributes must contain the independent line: ${rule}")
    endif()
endforeach()
list(FIND checkout_attribute_lines "engine/assets/core_app/* binary" generic_binary_index)
if(NOT generic_binary_index EQUAL -1)
    message(FATAL_ERROR
        ".gitattributes must not override classified Core App rules with: engine/assets/core_app/* binary")
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

set(text_assets
    engine/assets/core_app/actors.sidecar
    engine/assets/core_app/chaser.lua
    engine/assets/core_app/deterministic.scenario
    engine/assets/core_app/director.lua
    engine/assets/core_app/load_unload.scenario
    engine/assets/core_app/user.lua
    engine/assets/core_app/rollback.scenario)
set(binary_assets
    engine/assets/core_app/chime.wav
    engine/assets/core_app/level.banm
    engine/assets/core_app/level.bscn
    engine/assets/core_app/level.fg
    engine/assets/core_app/tone.wav)
set(formal_assets ${text_assets} ${binary_assets})
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
    include("${CMAKE_CURRENT_LIST_DIR}/test_core_app_git_metadata.cmake")
    core_app_git_metadata_absent("${REPOSITORY_ROOT}" "${git_probe_log}" metadata_absent)
    if(metadata_absent)
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
    list(FIND text_assets "${asset}" text_index)
    list(FIND binary_assets "${asset}" binary_index)
    string(FIND "${attribute_log}" "text: set" text_position)
    string(FIND "${attribute_log}" "binary: set" binary_position)
    if(NOT text_index EQUAL -1)
        string(FIND "${attribute_log}" "eol: lf" eol_position)
        if(text_position EQUAL -1 OR eol_position EQUAL -1)
            message(FATAL_ERROR
                "${asset} must have text: set and eol: lf; output=${attribute_log}")
        endif()
        if(NOT binary_position EQUAL -1)
            message(FATAL_ERROR "${asset} unexpectedly has binary: set; output=${attribute_log}")
        endif()
    elseif(NOT binary_index EQUAL -1)
        if(binary_position EQUAL -1)
            message(FATAL_ERROR "${asset} does not have binary: set; output=${attribute_log}")
        endif()
        if(NOT text_position EQUAL -1)
            message(FATAL_ERROR "${asset} unexpectedly has text: set; output=${attribute_log}")
        endif()
    else()
        message(FATAL_ERROR "internal asset classification missing for ${asset}")
    endif()
endforeach()
message(STATUS "All 12 formal core_app assets have classified checkout attributes")
