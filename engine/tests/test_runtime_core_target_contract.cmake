if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

# runtime_core is a formal top-level static library...
if(NOT cmake_text MATCHES "add_library\\(runtime_core STATIC")
    message(FATAL_ERROR "missing formal target runtime_core")
endif()

# ...defined outside the test block (independent of ENGINE_BUILD_TESTS).
string(FIND "${cmake_text}" "add_library(runtime_core STATIC" runtime_core_pos)
string(FIND "${cmake_text}" "if(ENGINE_BUILD_TESTS)" first_tests_block_pos)
if(runtime_core_pos LESS 0 OR first_tests_block_pos LESS 0 OR
   runtime_core_pos GREATER first_tests_block_pos)
    message(FATAL_ERROR "runtime_core must be defined before the first ENGINE_BUILD_TESTS block")
endif()

# ...owning the coordinator and formal facade translation units (and nothing
# from outside src/runtime/).
string(FIND "${cmake_text}" "add_library(engine STATIC" engine_target_pos)
foreach(runtime_src
        src/runtime/runtime_coordinator.c
        src/runtime/runtime_message.c
        src/runtime/runtime_queue.c
        src/runtime/runtime_task.c
        src/runtime/runtime_thread.c
        src/runtime/runtime_io.c
        src/runtime/runtime_reload.c
        src/runtime/runtime_profiler.c)
    string(FIND "${cmake_text}" "${runtime_src}" runtime_src_pos)
    if(runtime_src_pos LESS runtime_core_pos OR runtime_src_pos GREATER engine_target_pos)
        message(FATAL_ERROR "${runtime_src} is not owned by runtime_core")
    endif()
endforeach()

# engine, engine_demo, and dxx_break must not link runtime_core. Their
# target_link_libraries calls are single-line in this file, so a line-level
# scan is exact for the current style.
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "runtime_core")
        message(FATAL_ERROR "runtime_core leaked into a consumer link line: ${line}")
    endif()
endforeach()

# The focused test links the formal target instead of re-owning sources.
if(NOT cmake_text MATCHES "add_executable\\(test_runtime_core tests/test_runtime_core.c")
    message(FATAL_ERROR "missing test_runtime_core executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_runtime_core PRIVATE runtime_core")
    message(FATAL_ERROR "test_runtime_core does not link runtime_core")
endif()

# The IO/thread facade focused test links the test-only variant (hooked)
# rather than the production target.
if(NOT cmake_text MATCHES "add_executable\\(test_runtime_io tests/test_runtime_io.c")
    message(FATAL_ERROR "missing test_runtime_io executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_runtime_io PRIVATE runtime_core_test")
    message(FATAL_ERROR "test_runtime_io does not link runtime_core_test")
endif()

# The reload/profiler focused test links the test-only variant (hooked)
# rather than the production target.
if(NOT cmake_text MATCHES "add_executable\\(test_runtime_reload tests/test_runtime_reload.c")
    message(FATAL_ERROR "missing test_runtime_reload executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_runtime_reload PRIVATE runtime_core_test")
    message(FATAL_ERROR "test_runtime_reload does not link runtime_core_test")
endif()

message(STATUS "runtime_core target contract passed")
