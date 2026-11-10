foreach(var ENGINE_SOURCE_DIR REPOSITORY_ROOT PLAN_FILE DESIGN_FILE)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

set(required_files
    "${ENGINE_SOURCE_DIR}/apps/game_app/main.c"
    "${ENGINE_SOURCE_DIR}/apps/game_app/game_app.c"
    "${ENGINE_SOURCE_DIR}/apps/game_app/game_app.h"
    "${ENGINE_SOURCE_DIR}/apps/game_app/game_checkpoint.c"
    "${ENGINE_SOURCE_DIR}/apps/game_app/game_checkpoint.h"
    "${ENGINE_SOURCE_DIR}/apps/game_app/game_asset_bake.c"
    "${ENGINE_SOURCE_DIR}/tests/test_game_app_assets.c"
    "${ENGINE_SOURCE_DIR}/tests/test_game_app_target_contract.cmake"
    "${ENGINE_SOURCE_DIR}/tests/test_game_app_formal_assets.cmake"
    "${REPOSITORY_ROOT}/.gitignore"
    "${PLAN_FILE}"
    "${DESIGN_FILE}")
foreach(path IN LISTS required_files)
    if(NOT EXISTS "${path}")
        message(FATAL_ERROR "required game_app naming migration file is missing: ${path}")
    endif()
endforeach()

file(GLOB app_sources "${ENGINE_SOURCE_DIR}/apps/game_app/*.c" "${ENGINE_SOURCE_DIR}/apps/game_app/*.h")
set(scan_files
    ${app_sources}
    "${ENGINE_SOURCE_DIR}/CMakeLists.txt"
    "${ENGINE_SOURCE_DIR}/tests/test_game_app_assets.c"
    "${ENGINE_SOURCE_DIR}/tests/test_game_app_target_contract.cmake"
    "${ENGINE_SOURCE_DIR}/tests/test_game_app_formal_assets.cmake"
    "${REPOSITORY_ROOT}/.gitignore"
    "${PLAN_FILE}"
    "${DESIGN_FILE}")
set(errors "")
foreach(path IN LISTS scan_files)
    file(READ "${path}" text)
    string(REPLACE "test_cry_style_prototype" "" text "${text}")
    string(REPLACE "cry_style_gameplay.md" "" text "${text}")
    foreach(forbidden IN ITEMS "cry_" "CRY_" "manifest.cry" "CRYCKPT" "CRYTRACE"
            "build-cry-integration-" "assets/cry_game" "apps/cry_game"
            "test_cry_game" "fuzz_cry_game")
        if("${text}" MATCHES "${forbidden}")
            string(APPEND errors "${path}: forbidden ${forbidden}\n")
        endif()
    endforeach()
    if("${text}" MATCHES "Cry(Game|Level|Render|Audio|Checkpoint|Manifest)")
        string(APPEND errors "${path}: forbidden legacy type prefix ${CMAKE_MATCH_0}\n")
    endif()
endforeach()
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "game_app naming contract failed:\n${errors}")
endif()

file(READ "${DESIGN_FILE}" design_text)
file(READ "${PLAN_FILE}" plan_text)
set(documentation_errors "")
if("${design_text}" MATCHES "^# Cry Game")
    string(APPEND documentation_errors "design title still uses Cry Game\n")
endif()
if("${plan_text}" MATCHES "^# Cry Game")
    string(APPEND documentation_errors "plan title still uses Cry Game\n")
endif()
string(FIND "${design_text}" "GAMECKPT\\0" magic_nul_index)
if(NOT magic_nul_index EQUAL -1)
    string(APPEND documentation_errors "magic must be exactly 8-byte GAMECKPT without NUL\n")
endif()
if("${design_text}" MATCHES "用于提交失败后的恢复|checkpoint 不再忽略恢复结果|这些路径仍返回")
    string(APPEND documentation_errors "design mixes the superseded recovery protocol\n")
endif()
if("${plan_text}" MATCHES "game_checkpoint_corrupt_payload_for_fixture")
    string(APPEND documentation_errors "plan helper must use test_checkpoint_corrupt_payload_for_fixture\n")
endif()
if(NOT documentation_errors STREQUAL "")
    message(FATAL_ERROR "game_app documentation contract failed:\n${documentation_errors}")
endif()

file(READ "${ENGINE_SOURCE_DIR}/apps/game_app/game_checkpoint.c" checkpoint_source)
string(FIND "${checkpoint_source}" "{'G', 'A', 'M', 'E', 'C', 'K', 'P', 'T'}" magic_index)
if(magic_index LESS 0)
    message(FATAL_ERROR "checkpoint data magic was not migrated to GAMECKPT")
endif()
file(READ "${ENGINE_SOURCE_DIR}/apps/game_app/game_checkpoint.h" checkpoint_header)
if(NOT checkpoint_header MATCHES "manifest.game")
    message(FATAL_ERROR "checkpoint manifest filename was not migrated to manifest.game")
endif()
message(STATUS "game_app naming and data-format contract passed")
