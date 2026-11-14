if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

if(NOT cmake_text MATCHES "add_library\\(break_kernel STATIC")
    message(FATAL_ERROR "missing formal target break_kernel")
endif()

string(FIND "${cmake_text}" "add_library(break_ecs_replication STATIC" ecs_pos)
string(FIND "${cmake_text}" "add_library(break_kernel STATIC" kernel_pos)
if(ecs_pos LESS 0 OR kernel_pos LESS 0 OR kernel_pos LESS ecs_pos)
    message(FATAL_ERROR "break_kernel must be defined after break_ecs_replication")
endif()

string(SUBSTRING "${cmake_text}" ${ecs_pos} -1 after_ecs)
string(FIND "${after_ecs}" "if(ENGINE_BUILD_TESTS)" tests_rel)
if(tests_rel LESS 0)
    message(FATAL_ERROR "no ENGINE_BUILD_TESTS block found after break_ecs_replication")
endif()
math(EXPR tests_pos "${ecs_pos} + ${tests_rel}")
if(kernel_pos GREATER tests_pos)
    message(FATAL_ERROR "break_kernel must be defined at top level, not inside ENGINE_BUILD_TESTS")
endif()

foreach(src IN ITEMS
        src/kernel/break_kernel.c
        src/kernel/break_kernel_actor.c
        src/kernel/break_kernel_items.c
        src/kernel/break_kernel_weapons.c
        src/kernel/break_kernel_actions.c
        src/kernel/break_kernel_move.c
        src/kernel/break_kernel_level.c
        src/kernel/break_kernel_area.c)
    string(FIND "${cmake_text}" "${src}" src_pos)
    if(src_pos LESS 0 OR src_pos LESS kernel_pos)
        message(FATAL_ERROR "${src} is not owned by break_kernel")
    endif()
endforeach()

if(NOT cmake_text MATCHES "target_link_libraries\\(break_kernel PUBLIC break_ecs_replication")
    message(FATAL_ERROR "break_kernel does not link break_ecs_replication PUBLIC")
endif()

string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_kernel")
        message(FATAL_ERROR "break_kernel leaked into a consumer link line: ${line}")
    endif()
endforeach()

if(cmake_text MATCHES "BREAK_KERNEL_TESTING")
    message(FATAL_ERROR "break_kernel production sources must not carry a test-hook define")
endif()

if(NOT cmake_text MATCHES "add_library\\(break_kernel_lua STATIC src/kernel/break_kernel_lua.c")
    message(FATAL_ERROR "missing optional break_kernel_lua target")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(break_kernel_lua PUBLIC break_kernel break_lua")
    message(FATAL_ERROR "break_kernel_lua must be the Lua/kernel adapter")
endif()
if(cmake_text MATCHES "target_link_libraries\\(break_kernel [^\n]*break_lua")
    message(FATAL_ERROR "break_kernel core must not depend on Lua")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(break_kernel_lua_test PUBLIC break_kernel break_lua_test")
    message(FATAL_ERROR "break_kernel_lua_test must use break_lua_test")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_break_kernel_lua PRIVATE break_kernel_lua_test")
    message(FATAL_ERROR "missing break_kernel_lua focused test link")
endif()
