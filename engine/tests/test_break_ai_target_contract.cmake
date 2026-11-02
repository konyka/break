if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

if(NOT cmake_text MATCHES "add_library\\(break_ai STATIC")
    message(FATAL_ERROR "missing formal target break_ai")
endif()

string(FIND "${cmake_text}" "add_library(break_ai STATIC" ai_pos)
string(FIND "${cmake_text}" "if(ENGINE_BUILD_TESTS)" tests_pos)
if(ai_pos LESS 0 OR tests_pos LESS 0 OR ai_pos GREATER tests_pos)
    message(FATAL_ERROR "break_ai must be a top-level target")
endif()

foreach(src IN ITEMS
        src/ai/break_nav_bake.c
        src/ai/break_nav_workspace.c
        src/ai/break_nav_query.c
        src/ai/break_ai_runtime.c
        src/ai/break_ai_obstacle.c
        src/ai/break_ai_query.c
        src/ai/break_ai_agent.c
        src/ai/break_steer_velocity.c
        src/ai/break_nav_follow.c
        src/ai/break_perception.c
        src/ai/break_behavior.c
        src/ai/break_steer.c)
    string(FIND "${cmake_text}" "${src}" src_pos)
    if(src_pos LESS 0 OR src_pos LESS ai_pos)
        message(FATAL_ERROR "${src} is not owned by break_ai")
    endif()
endforeach()

if(cmake_text MATCHES "renderer/terrain.h")
    string(FIND "${cmake_text}" "src/ai/" ai_src)
    string(FIND "${cmake_text}" "renderer/terrain.h" terrain_pos)
    if(terrain_pos GREATER ai_src AND terrain_pos LESS tests_pos)
        message(FATAL_ERROR "break_ai must not reference renderer/terrain.h")
    endif()
endif()

string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_ai")
        message(FATAL_ERROR "break_ai leaked into a consumer link line: ${line}")
    endif()
endforeach()
