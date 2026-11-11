foreach(var ENGINE_SOURCE_DIR REPOSITORY_ROOT PLAN_FILE DESIGN_FILE GIT_EXECUTABLE)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

set(required_files
    "${ENGINE_SOURCE_DIR}/apps/core_app/main.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app.h"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_audio.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_audio.h"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_render.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_render.h"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_checkpoint.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_checkpoint.h"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_asset_bake.c"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_assets.c"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_lifecycle.cmake"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_lifecycle_preload.c"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_nm_filter.cmake"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_nm_symbol_missing.cmake"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_naming_contract.cmake"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_target_contract.cmake"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_formal_assets.cmake"
    "${REPOSITORY_ROOT}/.gitignore"
    "${PLAN_FILE}"
    "${DESIGN_FILE}")
foreach(path IN LISTS required_files)
    if(NOT EXISTS "${path}")
        message(FATAL_ERROR "missing core_app migration file: ${path}")
    endif()
endforeach()

set(legacy_paths
    "${ENGINE_SOURCE_DIR}/apps/game_app"
    "${ENGINE_SOURCE_DIR}/assets/game_app"
    "${REPOSITORY_ROOT}/docs/design/game_app_integration.md"
    "${REPOSITORY_ROOT}/docs/superpowers/plans/2026-11-03-cry-game-integration.md")
file(GLOB legacy_tests "${ENGINE_SOURCE_DIR}/tests/test_game_app_*")
list(APPEND legacy_paths ${legacy_tests})
foreach(path IN LISTS legacy_paths)
    if(EXISTS "${path}")
        message(FATAL_ERROR "legacy application path still exists: ${path}")
    endif()
endforeach()

file(READ "${ENGINE_SOURCE_DIR}/CMakeLists.txt" cmake_text)
set(runtime_sources [=[add_library(core_app_runtime STATIC
    apps/core_app/core_app.c
    apps/core_app/core_app_audio.c
    apps/core_app/core_app_render.c
    apps/core_app/core_app_checkpoint.c)]=])
string(FIND "${cmake_text}" "${runtime_sources}" runtime_sources_index)
if(runtime_sources_index LESS 0)
    message(FATAL_ERROR "core_app_runtime must use exactly the four renamed runtime sources")
endif()
foreach(required_cmake IN ITEMS
        "engine_link_rhi_backend(core_app)"
        "target_link_libraries(core_app PRIVATE core_app_runtime m)"
        "target_link_libraries(core_app_asset_bake PRIVATE core_app_runtime m)")
    string(FIND "${cmake_text}" "${required_cmake}" required_cmake_index)
    if(required_cmake_index LESS 0)
        message(FATAL_ERROR "missing core_app target contract: ${required_cmake}")
    endif()
endforeach()
if("${cmake_text}" MATCHES "core_app_core")
    message(FATAL_ERROR "core_app_core is forbidden; use core_app_runtime")
endif()

file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app.h" app_header)
foreach(required_interface IN ITEMS
        "typedef struct CoreAppConfig CoreAppConfig;"
        "typedef struct CoreApp CoreApp;"
        "BreakRuntimeError core_app_run(const CoreAppConfig *config, int *out_exit_code);")
    string(FIND "${app_header}" "${required_interface}" interface_index)
    if(interface_index LESS 0)
        message(FATAL_ERROR "missing core_app public interface: ${required_interface}")
    endif()
endforeach()
file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_render.h" render_header)
if(NOT render_header MATCHES "BreakRuntimeError core_app_render_start\\(CoreAppRender \\*render, FILE \\*trace\\)")
    message(FATAL_ERROR "missing core_app_render_start interface")
endif()
file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_audio.h" audio_header)
if(NOT audio_header MATCHES "BreakRuntimeError core_app_audio_start\\(CoreAppAudio \\*audio, FILE \\*trace\\)")
    message(FATAL_ERROR "missing core_app_audio_start interface")
endif()
file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_checkpoint.h" checkpoint_header)
if(NOT checkpoint_header MATCHES "BreakRuntimeError core_app_checkpoint_probe\\(const char \\*directory\\)")
    message(FATAL_ERROR "missing core_app_checkpoint_probe interface")
endif()

set(expected_assets
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
execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" ls-files -- engine/assets/core_app
    RESULT_VARIABLE git_result
    OUTPUT_VARIABLE tracked_output
    ERROR_VARIABLE git_error
    OUTPUT_STRIP_TRAILING_WHITESPACE)
if(NOT git_result EQUAL 0)
    message(FATAL_ERROR "git ls-files failed: ${git_error}")
endif()
string(REPLACE "\n" ";" tracked_assets "${tracked_output}")
if(NOT "${tracked_assets}" STREQUAL "${expected_assets}")
    list(LENGTH tracked_assets tracked_count)
    list(LENGTH expected_assets expected_count)
    message(FATAL_ERROR
        "core_app asset tracking mismatch: ${tracked_count} tracked, ${expected_count} required\n"
        "tracked=${tracked_assets}\nexpected=${expected_assets}")
endif()

file(GLOB app_sources "${ENGINE_SOURCE_DIR}/apps/core_app/*.c" "${ENGINE_SOURCE_DIR}/apps/core_app/*.h")
file(GLOB test_sources "${ENGINE_SOURCE_DIR}/tests/test_core_app_*.c" "${ENGINE_SOURCE_DIR}/tests/test_core_app_*.cmake")
list(REMOVE_ITEM test_sources "${ENGINE_SOURCE_DIR}/tests/test_core_app_naming_contract.cmake")
set(scan_files
    ${app_sources}
    ${test_sources}
    "${ENGINE_SOURCE_DIR}/CMakeLists.txt"
    "${ENGINE_SOURCE_DIR}/tests/test_editor_scene.c"
    "${REPOSITORY_ROOT}/.gitignore"
    "${REPOSITORY_ROOT}/docs/design/editor_phase1.md"
    "${PLAN_FILE}"
    "${DESIGN_FILE}")
set(errors "")
foreach(path IN LISTS scan_files)
    file(READ "${path}" text)
    if("${path}" STREQUAL "${DESIGN_FILE}")
        set(history_marker "<!-- CORE_APP_HISTORY_BEGIN -->")
        string(REGEX MATCHALL "${history_marker}" history_markers "${text}")
        list(LENGTH history_markers history_marker_count)
        if(NOT history_marker_count EQUAL 1)
            message(FATAL_ERROR "current design requires exactly one explicit history marker")
        endif()
        string(FIND "${text}" "${history_marker}" history_begin)
        string(SUBSTRING "${text}" 0 "${history_begin}" current_design_text)
        set(text "${current_design_text}")
    elseif("${path}" STREQUAL "${PLAN_FILE}")
        set(history_begin_marker "<!-- CORE_APP_COMPLETED_TASKS_1_3_BEGIN -->")
        set(history_end_marker "<!-- CORE_APP_COMPLETED_TASKS_1_3_END -->")
        string(REGEX MATCHALL "${history_begin_marker}" history_begin_markers "${text}")
        string(REGEX MATCHALL "${history_end_marker}" history_end_markers "${text}")
        list(LENGTH history_begin_markers history_begin_count)
        list(LENGTH history_end_markers history_end_count)
        if(NOT history_begin_count EQUAL 1 OR NOT history_end_count EQUAL 1)
            message(FATAL_ERROR "current plan requires one explicit Task 1--3 history boundary")
        endif()
        string(FIND "${text}" "${history_begin_marker}" history_begin)
        string(FIND "${text}" "${history_end_marker}" history_end)
        if(history_begin LESS 0 OR history_end LESS history_begin)
            message(FATAL_ERROR "current plan Task 1--3 history markers are out of order")
        endif()
        string(SUBSTRING "${text}" 0 "${history_begin}" current_plan_prefix)
        string(LENGTH "${history_end_marker}" history_end_marker_length)
        math(EXPR current_suffix_begin "${history_end} + ${history_end_marker_length}")
        string(SUBSTRING "${text}" "${current_suffix_begin}" -1 current_plan_suffix)
        set(current_plan_text "${current_plan_prefix}${current_plan_suffix}")
        set(text "${current_plan_text}")
    endif()
    # P0--P11 compatibility API: names and link relationships are unchanged.
    string(REPLACE "game/break_game" "" text "${text}")
    string(REPLACE "game/break_flow" "" text "${text}")
    string(REPLACE "break_game" "" text "${text}")
    string(REPLACE "BreakGame" "" text "${text}")
    string(REPLACE "BREAK_GAME" "" text "${text}")
    string(REPLACE "foreach(game_test IN ITEMS actor items weapons actions move level area flow)" "" text "${text}")
    string(REPLACE "\${game_test}" "" text "${text}")
    string(REPLACE "GAME_TEST_WRAP_FS" "" text "${text}")
    # Only the existing break_game CTest iterator declaration/expansions and
    # the pre-P12 test_platform_fs_write macro are exempt here.
    # Established pre-P12 prototype contract strings and this existing worktree/branch only.
    string(REPLACE "test_cry_style_prototype" "" text "${text}")
    string(REPLACE "cry_style_gameplay.md" "" text "${text}")
    string(REPLACE ".worktrees/cry-integration" "" text "${text}")
    string(REPLACE "\`cry-integration\`" "" text "${text}")
    # Task 1 temporary data-format literals; Task 2 removes these exemptions.
    string(REPLACE "GAMECKPT" "" text "${text}")
    string(REPLACE "manifest.game" "" text "${text}")
    string(REPLACE "MANIFEST.GAME" "" text "${text}")
    string(REPLACE "GAMEAPPTRACE" "" text "${text}")
    string(REPLACE "game-app-scenario" "" text "${text}")
    foreach(forbidden IN ITEMS "game_app" "GameApp" "GAME_APP" "game_" "Game[A-Z]" "GAME_"
            "cry_" "Cry[A-Z]" "CRY_" "core_app_core" "build-cry-integration-" "build-game-integration-")
        if("${text}" MATCHES "${forbidden}")
            string(APPEND errors "${path}: forbidden ${forbidden}: ${CMAKE_MATCH_0}\n")
        endif()
    endforeach()
    foreach(forbidden IN ITEMS "game" "Game" "GAME" "cry" "Cry" "CRY")
        if("${text}" MATCHES "(^|[^A-Za-z0-9_])${forbidden}([^A-Za-z0-9_]|$)")
            string(APPEND errors "${path}: forbidden legacy domain token ${forbidden}\n")
        endif()
    endforeach()
    if("${text}" MATCHES "[A-Za-z0-9_]+_game([^A-Za-z0-9_]|$)")
        string(APPEND errors "${path}: forbidden legacy domain suffix ${CMAKE_MATCH_0}\n")
    endif()
endforeach()
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "core_app naming contract failed:\n${errors}")
endif()

if(NOT "${current_design_text}" MATCHES "^# Core App")
    message(FATAL_ERROR "current design title must use Core App")
endif()
if(NOT "${current_plan_text}" MATCHES "^# Core App Integration")
    message(FATAL_ERROR "current plan title must use Core App Integration")
endif()
if("${current_plan_text}" MATCHES "### Task [123]:")
    message(FATAL_ERROR "completed Task 1--3 content leaked into the current plan scan")
endif()
if(NOT "${current_plan_text}" MATCHES "### Task 4:")
    message(FATAL_ERROR "current plan is missing the Task 4--13 section")
endif()
foreach(module IN ITEMS core_app_input core_app_simulation core_app_network core_app_script)
    if(NOT current_plan_text MATCHES "${module}")
        message(FATAL_ERROR "current plan is missing ${module}")
    endif()
endforeach()
string(FIND "${current_design_text}" "GAMECKPT\\0" magic_nul_index)
if(NOT magic_nul_index EQUAL -1)
    message(FATAL_ERROR "magic must remain the exact 8-byte GAMECKPT without NUL in Task 1")
endif()
if("${current_design_text}" MATCHES "用于提交失败后的恢复|checkpoint 不再忽略恢复结果|这些路径仍返回")
    message(FATAL_ERROR "design mixes the superseded recovery protocol")
endif()
if("${current_plan_text}" MATCHES "core_app_checkpoint_corrupt_payload_for_fixture")
    message(FATAL_ERROR "plan helper must use test_checkpoint_corrupt_payload_for_fixture")
endif()

file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_checkpoint.c" checkpoint_source)
string(FIND "${checkpoint_source}" "{'G', 'A', 'M', 'E', 'C', 'K', 'P', 'T'}" magic_index)
if(magic_index LESS 0)
    message(FATAL_ERROR "Task 1 must preserve the GAMECKPT data magic")
endif()
if(NOT checkpoint_header MATCHES "manifest.game")
    message(FATAL_ERROR "Task 1 must preserve manifest.game")
endif()
file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app.c" app_source)
if(NOT app_source MATCHES "GAMEAPPTRACE" OR NOT app_source MATCHES "game-app-scenario")
    message(FATAL_ERROR "Task 1 must preserve GAMEAPPTRACE and game-app-scenario")
endif()
message(STATUS "core_app naming, target, interface, and 11-asset contract passed")
