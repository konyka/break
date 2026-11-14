# Repository naming contract.
#
# Scans the repository's own sources, build files and current docs and fails
# on the legacy domain word, its Chinese role words, and the legacy engine
# prefix. STAGE widens the scope as each rename step lands:
#   1  kernel module names under engine/
#   2  every word under engine/ except the controller input files
#   3  every word under engine/
#   4  engine/ plus the current docs, README.md and the root CMakeLists.txt
# Walks the tree with file(GLOB_RECURSE), so it needs no Git metadata.

cmake_policy(VERSION 3.20)

foreach(var REPOSITORY_ROOT STAGE)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()
get_filename_component(root "${REPOSITORY_ROOT}" ABSOLUTE)

set(extensions c h cpp hpp cc mm m cmake txt lua md scenario json yml yaml glsl hlsl
    metal py sh toml in)
set(globs "")
set(scan_roots engine/src engine/apps engine/tests engine/assets engine/tools)
foreach(scan_root IN LISTS scan_roots)
    foreach(ext IN LISTS extensions)
        list(APPEND globs "${root}/${scan_root}/*.${ext}")
    endforeach()
endforeach()
list(APPEND globs "${root}/engine/CMakeLists.txt")
if(STAGE GREATER_EQUAL 4)
    list(APPEND globs "${root}/docs/*.md" "${root}/README.md" "${root}/CMakeLists.txt")
endif()
file(GLOB_RECURSE files LIST_DIRECTORIES false ${globs})

# This contract and the core_app contract quote the words they reject.
set(self_exempt
    "${root}/engine/tests/test_repo_naming_contract.cmake"
    "${root}/engine/tests/test_core_app_naming_contract.cmake"
    "${root}/docs/superpowers/plans/2026-11-14-neutral-naming.md")
# Controller input keeps its old names until stage 3.
set(pad_regex "(gamepad|Gamepad|GAMEPAD)")

if(EXISTS "${root}/engine/src/game")
    set(errors "engine/src/game: legacy module directory still exists\n")
else()
    set(errors "")
endif()
foreach(path IN LISTS files)
    if(path IN_LIST self_exempt)
        continue()
    endif()
    file(RELATIVE_PATH rel "${root}" "${path}")
    if(rel MATCHES "^(engine/external|third_party|docs/ue5\\.8\\.3)/")
        continue()
    endif()
    if(STAGE LESS 3 AND rel MATCHES "(gamepad|xinput)")
        continue()
    endif()
    file(READ "${path}" text)
    # Names owned by system SDKs and by external projects.
    string(REGEX REPLACE "XINPUT_GAMEPAD[A-Z_]*( Gamepad;)?|\\.Gamepad|BTN_GAMEPAD|CryENGINE|T3DGameR1" "" text "${text}")
    set(scan_path "${rel}")
    if(STAGE LESS 3)
        string(REGEX REPLACE "${pad_regex}" "" text "${text}")
        string(REGEX REPLACE "${pad_regex}" "" scan_path "${scan_path}")
    endif()
    if(STAGE EQUAL 1)
        set(patterns "break_game" "BreakGame" "BREAK_GAME" "game/break_" "cry_style")
    else()
        set(patterns "[Gg]ame" "GAME" "玩家" "敌人")
    endif()
    foreach(pattern IN LISTS patterns)
        if(scan_path MATCHES "${pattern}")
            string(APPEND errors "${rel}: file name contains ${CMAKE_MATCH_0}\n")
        endif()
        if(text MATCHES "[^\n]*${pattern}[^\n]*")
            string(APPEND errors "${rel}: ${CMAKE_MATCH_0}\n")
        endif()
    endforeach()
    if(text MATCHES "[^\n]*(^|[^A-Za-z])(cry_|Cry[A-Z]|CRY_)[^\n]*")
        string(APPEND errors "${rel}: legacy prefix: ${CMAKE_MATCH_0}\n")
    endif()
endforeach()

if(NOT errors STREQUAL "")
    message(FATAL_ERROR "naming contract stage ${STAGE} failed:\n${errors}")
endif()
list(LENGTH files file_count)
message(STATUS "naming contract stage ${STAGE}: ${file_count} files clean")
