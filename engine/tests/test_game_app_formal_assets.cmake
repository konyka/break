foreach(var ENGINE_SOURCE_DIR GIT_EXECUTABLE)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required to verify formal asset tracking")
    endif()
endforeach()

set(expected
    engine/assets/game_app/actors.sidecar
    engine/assets/game_app/broken.lua
    engine/assets/game_app/deterministic.scenario
    engine/assets/game_app/director.lua
    engine/assets/game_app/level.banm
    engine/assets/game_app/level.bscn
    engine/assets/game_app/level.fg
    engine/assets/game_app/load_unload.scenario
    engine/assets/game_app/player.lua
    engine/assets/game_app/rollback.scenario
    engine/assets/game_app/tone.wav)
get_filename_component(repository_root "${ENGINE_SOURCE_DIR}/.." ABSOLUTE)
execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${repository_root}" ls-files -- engine/assets/game_app
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
message(STATUS "All 11 formal game_app assets are tracked, including tone.wav")
