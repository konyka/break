foreach(var ENGINE_SOURCE_DIR REPOSITORY_ROOT PLAN_FILE DESIGN_FILE GIT_EXECUTABLE)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()
get_filename_component(NON_GIT_REPOSITORY_ROOT "${REPOSITORY_ROOT}" ABSOLUTE)

set(required_files
    "${ENGINE_SOURCE_DIR}/apps/core_app/main.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app.h"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_audio.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_audio.h"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_gpu.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_gpu.h"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_mesh.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_mesh.h"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_gpu.cmake"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_mesh.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_network.c"
    "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_network.h"
    "${ENGINE_SOURCE_DIR}/tests/test_core_app_network.c"
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
    "${NON_GIT_REPOSITORY_ROOT}/.gitignore"
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
    "${NON_GIT_REPOSITORY_ROOT}/docs/design/game_app_integration.md"
    "${NON_GIT_REPOSITORY_ROOT}/docs/superpowers/plans/2026-11-03-cry-game-integration.md")
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
    apps/core_app/core_app_checkpoint.c
    apps/core_app/scenario.c
    apps/core_app/core_app_input.c
    apps/core_app/core_app_simulation.c)]=])
string(FIND "${cmake_text}" "${runtime_sources}" runtime_sources_index)
if(runtime_sources_index LESS 0)
    message(FATAL_ERROR "core_app_runtime must use exactly the seven core_app runtime sources")
endif()
foreach(required_cmake IN ITEMS
        "engine_link_rhi_backend(core_app)"
        "target_link_libraries(core_app PRIVATE core_app_runtime core_app_network m)"
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
    engine/assets/core_app/chaser.lua
    engine/assets/core_app/deterministic.scenario
    engine/assets/core_app/director.lua
    engine/assets/core_app/level.banm
    engine/assets/core_app/level.bscn
    engine/assets/core_app/level.fg
    engine/assets/core_app/load_unload.scenario
    engine/assets/core_app/rollback.scenario
    engine/assets/core_app/tone.wav
    engine/assets/core_app/user.lua)
file(GLOB app_sources "${ENGINE_SOURCE_DIR}/apps/core_app/*.c" "${ENGINE_SOURCE_DIR}/apps/core_app/*.h")
file(GLOB test_sources "${ENGINE_SOURCE_DIR}/tests/test_core_app_*.c" "${ENGINE_SOURCE_DIR}/tests/test_core_app_*.cmake")
list(REMOVE_ITEM test_sources "${ENGINE_SOURCE_DIR}/tests/test_core_app_naming_contract.cmake")
set(scan_files
    ${app_sources}
    ${test_sources}
    "${ENGINE_SOURCE_DIR}/CMakeLists.txt"
    "${ENGINE_SOURCE_DIR}/tests/test_editor_scene.c"
    "${NON_GIT_REPOSITORY_ROOT}/.gitignore"
    "${NON_GIT_REPOSITORY_ROOT}/docs/design/editor_phase1.md"
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
    # Established pre-P12 contract strings and this existing worktree/branch only.
    string(REPLACE "core_style_runtime.md" "" text "${text}")
    string(REPLACE ".worktrees/cry-integration" "" text "${text}")
    string(REPLACE [=[`cry-integration`]=] "" text "${text}")
    foreach(legacy_format IN ITEMS "GAMECKPT" "manifest.game" "MANIFEST.GAME"
            "GAMEAPPTRACE" "game-app-scenario")
        string(FIND "${text}" "${legacy_format}" legacy_format_index)
        if(NOT legacy_format_index LESS 0)
            string(APPEND errors "${path}: legacy data format ${legacy_format} is forbidden\n")
        endif()
    endforeach()
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
    # Neutral-role wording: the runtime addresses the controlled unit as
    # "user" and the pursuing unit as "chaser"; the legacy actor/gameplay
    # vocabulary must not reappear in code, assets, traces, or documents.
    foreach(forbidden IN ITEMS "player" "Player" "PLAYER" "enemy" "Enemy" "ENEMY" "玩家" "敌人" "游戏")
        string(FIND "${text}" "${forbidden}" forbidden_index)
        if(NOT forbidden_index LESS 0)
            string(APPEND errors "${path}: forbidden role wording ${forbidden}\n")
        endif()
    endforeach()
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
string(FIND "${current_design_text}" "CORECKPT" magic_index)
if(magic_index LESS 0)
    message(FATAL_ERROR "current design must specify the exact 8-byte CORECKPT magic")
endif()
if("${current_design_text}" MATCHES "用于提交失败后的恢复|checkpoint 不再忽略恢复结果|这些路径仍返回")
    message(FATAL_ERROR "design mixes the superseded recovery protocol")
endif()
if("${current_plan_text}" MATCHES "core_app_checkpoint_corrupt_payload_for_fixture")
    message(FATAL_ERROR "plan helper must use test_checkpoint_corrupt_payload_for_fixture")
endif()

file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_checkpoint.c" checkpoint_source)
string(FIND "${checkpoint_source}" "{'C', 'O', 'R', 'E', 'C', 'K', 'P', 'T'}" magic_index)
if(magic_index LESS 0)
    message(FATAL_ERROR "checkpoint writer must use the CORECKPT data magic")
endif()
string(FIND "${checkpoint_header}"
    "#define CORE_APP_CHECKPOINT_MANIFEST_NAME \"manifest.core\"" manifest_name_index)
if(manifest_name_index LESS 0)
    message(FATAL_ERROR "CORE_APP_CHECKPOINT_MANIFEST_NAME must be exactly manifest.core")
endif()
file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app.c" app_source)
file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/scenario.c" scenario_source)
string(FIND "${scenario_source}" "strcmp(buffer, \"core-app-scenario 1\")" scenario_header_index)
if(NOT app_source MATCHES "COREAPPTRACE" OR scenario_header_index LESS 0)
    message(FATAL_ERROR "application must use COREAPPTRACE and the scenario parser must require core-app-scenario 1")
endif()
unset(ENV{GIT_DIR})
unset(ENV{GIT_WORK_TREE})
set(ENV{LC_ALL} "C")
execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${REPOSITORY_ROOT}" rev-parse --git-dir
    RESULT_VARIABLE git_probe_result
    OUTPUT_VARIABLE git_probe_output
    ERROR_VARIABLE git_probe_error)
set(git_probe_log "${git_probe_output}${git_probe_error}")
if(NOT git_probe_result EQUAL 0)
    include("${CMAKE_CURRENT_LIST_DIR}/test_core_app_git_metadata.cmake")
    core_app_git_metadata_absent("${REPOSITORY_ROOT}" "${git_probe_log}" metadata_absent)
    if(metadata_absent)
        message(STATUS "CORE_APP_TRACKING_UNVERIFIED: ${REPOSITORY_ROOT} is not a Git repository")
        if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
            cmake_language(EXIT 77)
        endif()
        message(FATAL_ERROR "UNVERIFIED: core_app tracking requires Git metadata; this CMake cannot emit skip code 77")
    endif()
    message(FATAL_ERROR "git rev-parse --git-dir failed: ${git_probe_log}")
endif()
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
message(STATUS "core_app naming, target, interface, and 11-asset contract passed")
