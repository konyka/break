foreach(var ENGINE_SOURCE_DIR GIT_EXECUTABLE)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required to verify formal asset tracking")
    endif()
endforeach()

set(expected
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
get_filename_component(repository_root "${ENGINE_SOURCE_DIR}/.." ABSOLUTE)
unset(ENV{GIT_DIR})
unset(ENV{GIT_WORK_TREE})
set(ENV{LC_ALL} "C")
execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${repository_root}" rev-parse --git-dir
    RESULT_VARIABLE git_probe_result
    OUTPUT_VARIABLE git_probe_output
    ERROR_VARIABLE git_probe_error)
set(git_probe_log "${git_probe_output}${git_probe_error}")
if(NOT git_probe_result EQUAL 0)
    if(NOT EXISTS "${repository_root}/.git" AND
            NOT IS_SYMLINK "${repository_root}/.git" AND
            "${git_probe_log}" MATCHES "fatal: not a git repository \\(or any of the parent directories\\): \\.git")
        message(STATUS "CORE_APP_TRACKING_UNVERIFIED: ${repository_root} is not a Git repository")
        if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
            cmake_language(EXIT 77)
        endif()
        message(FATAL_ERROR "UNVERIFIED: core_app tracking requires Git metadata; this CMake cannot emit skip code 77")
    endif()
    message(FATAL_ERROR "git rev-parse --git-dir failed: ${git_probe_log}")
endif()
execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${repository_root}" ls-files -- engine/assets/core_app
    RESULT_VARIABLE git_result
    OUTPUT_VARIABLE tracked_output
    ERROR_VARIABLE git_error
    OUTPUT_STRIP_TRAILING_WHITESPACE)
if(NOT git_result EQUAL 0)
    message(FATAL_ERROR "git ls-files failed: ${git_error}")
endif()
string(REPLACE "\n" ";" tracked "${tracked_output}")
if(NOT "${tracked}" STREQUAL "${expected}")
    list(LENGTH tracked tracked_count)
    list(LENGTH expected expected_count)
    message(FATAL_ERROR
        "formal asset tracking mismatch: ${tracked_count} tracked, ${expected_count} required\n"
        "tracked=${tracked}\nexpected=${expected}")
endif()
message(STATUS "All 11 formal core_app assets are tracked, including tone.wav")
