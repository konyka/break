if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

# break_lua is a formal top-level static library...
if(NOT cmake_text MATCHES "add_library\\(break_lua STATIC")
    message(FATAL_ERROR "missing formal target break_lua")
endif()

# ...defined after the vendored lua target and before the next
# ENGINE_BUILD_TESTS block that follows it, i.e. at top level (independent
# of ENGINE_BUILD_TESTS).
string(FIND "${cmake_text}" "add_library(lua STATIC" lua_pos)
string(FIND "${cmake_text}" "add_library(break_lua STATIC" break_lua_pos)
if(lua_pos LESS 0 OR break_lua_pos LESS 0 OR break_lua_pos LESS lua_pos)
    message(FATAL_ERROR "break_lua must be defined after the vendored lua target")
endif()
string(SUBSTRING "${cmake_text}" ${lua_pos} -1 after_lua_text)
string(FIND "${after_lua_text}" "if(ENGINE_BUILD_TESTS)" next_tests_block_rel)
if(next_tests_block_rel LESS 0)
    message(FATAL_ERROR "no ENGINE_BUILD_TESTS block found after the lua target")
endif()
math(EXPR next_tests_block_pos "${lua_pos} + ${next_tests_block_rel}")
if(break_lua_pos GREATER next_tests_block_pos)
    message(FATAL_ERROR "break_lua must be defined at top level, not inside an ENGINE_BUILD_TESTS block")
endif()

# ...owning its facade translation unit (first mention is inside the
# add_library(break_lua ...) call).
string(FIND "${cmake_text}" "src/script/break_lua_runtime.c" runtime_src_pos)
string(FIND "${cmake_text}" "add_library(stb_truetype STATIC" stb_pos)
if(runtime_src_pos LESS break_lua_pos OR
   (stb_pos GREATER break_lua_pos AND runtime_src_pos GREATER stb_pos))
    message(FATAL_ERROR "src/script/break_lua_runtime.c is not owned by break_lua")
endif()

# ...linking the vendored Lua target PUBLIC.
if(NOT cmake_text MATCHES "target_link_libraries\\(break_lua PUBLIC lua")
    message(FATAL_ERROR "break_lua does not link lua PUBLIC")
endif()

# engine, engine_demo, and dxx_break must not link break_lua. Their
# target_link_libraries calls are single-line in this file, so a line-level
# scan is exact for the current style.
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_lua")
        message(FATAL_ERROR "break_lua leaked into a consumer link line: ${line}")
    endif()
endforeach()

# The focused test links the test-only variant (BREAK_LUA_TESTING=1 hooks)
# rather than the production target; the production archive stays hook-free.
if(NOT cmake_text MATCHES "add_library\\(break_lua_test STATIC")
    message(FATAL_ERROR "missing test-only break_lua_test variant")
endif()
if(NOT cmake_text MATCHES "target_compile_definitions\\(break_lua_test PRIVATE BREAK_LUA_TESTING=1")
    message(FATAL_ERROR "break_lua_test does not define BREAK_LUA_TESTING=1")
endif()
if(NOT cmake_text MATCHES "add_executable\\(test_break_lua_runtime tests/test_break_lua_runtime.c")
    message(FATAL_ERROR "missing test_break_lua_runtime executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_break_lua_runtime PRIVATE break_lua_test")
    message(FATAL_ERROR "test_break_lua_runtime does not link break_lua_test")
endif()

message(STATUS "break_lua target contract passed")
