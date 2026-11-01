if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

if(NOT cmake_text MATCHES "add_library\\(break_game STATIC")
    message(FATAL_ERROR "missing formal target break_game")
endif()

string(FIND "${cmake_text}" "add_library(break_ecs_replication STATIC" ecs_pos)
string(FIND "${cmake_text}" "add_library(break_game STATIC" game_pos)
if(ecs_pos LESS 0 OR game_pos LESS 0 OR game_pos LESS ecs_pos)
    message(FATAL_ERROR "break_game must be defined after break_ecs_replication")
endif()

string(SUBSTRING "${cmake_text}" ${ecs_pos} -1 after_ecs)
string(FIND "${after_ecs}" "if(ENGINE_BUILD_TESTS)" tests_rel)
if(tests_rel LESS 0)
    message(FATAL_ERROR "no ENGINE_BUILD_TESTS block found after break_ecs_replication")
endif()
math(EXPR tests_pos "${ecs_pos} + ${tests_rel}")
if(game_pos GREATER tests_pos)
    message(FATAL_ERROR "break_game must be defined at top level, not inside ENGINE_BUILD_TESTS")
endif()

foreach(src IN ITEMS
        src/game/break_game.c
        src/game/break_game_actor.c
        src/game/break_game_actions.c
        src/game/break_game_move.c
        src/game/break_game_level.c
        src/game/break_game_area.c)
    string(FIND "${cmake_text}" "${src}" src_pos)
    if(src_pos LESS 0 OR src_pos LESS game_pos)
        message(FATAL_ERROR "${src} is not owned by break_game")
    endif()
endforeach()

if(NOT cmake_text MATCHES "target_link_libraries\\(break_game PUBLIC break_ecs_replication")
    message(FATAL_ERROR "break_game does not link break_ecs_replication PUBLIC")
endif()

string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_game")
        message(FATAL_ERROR "break_game leaked into a consumer link line: ${line}")
    endif()
endforeach()

if(cmake_text MATCHES "BREAK_GAME_TESTING")
    message(FATAL_ERROR "break_game production sources must not carry a test-hook define")
endif()
