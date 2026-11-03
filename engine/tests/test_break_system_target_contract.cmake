if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

if(NOT cmake_text MATCHES "add_library\\(break_system STATIC")
    message(FATAL_ERROR "missing formal target break_system")
endif()

string(FIND "${cmake_text}" "add_library(break_system STATIC" system_pos)
string(FIND "${cmake_text}" "if(ENGINE_BUILD_TESTS)" tests_pos)
if(system_pos LESS 0 OR tests_pos LESS 0 OR system_pos GREATER tests_pos)
    message(FATAL_ERROR "break_system must exist independently of ENGINE_BUILD_TESTS")
endif()

foreach(src IN ITEMS
        src/system/break_cvar.c
        src/system/break_xml.c
        src/system/break_plugin.c
        src/platform/platform_dynamic.c)
    string(FIND "${cmake_text}" "${src}" src_pos)
    if(src_pos LESS 0 OR src_pos LESS system_pos)
        message(FATAL_ERROR "${src} is not owned by break_system")
    endif()
endforeach()

if(NOT cmake_text MATCHES "set_property\\(TARGET break_system PROPERTY C_STANDARD 11\\)")
    message(FATAL_ERROR "break_system does not pin C11")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(break_system PUBLIC break_integrity \\$\\{CMAKE_DL_LIBS\\}\\)")
    message(FATAL_ERROR "break_system must reuse break_integrity and the platform dl library")
endif()

string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break|editor)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_system")
        message(FATAL_ERROR "break_system leaked into a core consumer: ${line}")
    endif()
endforeach()

if(NOT cmake_text MATCHES "add_library\\(\\$\\{target_name\\} SHARED")
    message(FATAL_ERROR "test plugin helper must build real SHARED libraries")
endif()
foreach(plugin IN ITEMS a b bad_abi register_fail no_entry)
    if(NOT cmake_text MATCHES "break_system_add_test_plugin\\(break_system_test_plugin_${plugin}")
        message(FATAL_ERROR "missing real SHARED fixture ${plugin}")
    endif()
endforeach()

foreach(test_name IN ITEMS test_break_cvar test_break_xml test_break_plugin test_break_system_target_contract)
    if(NOT cmake_text MATCHES "add_test\\(NAME ${test_name}")
        message(FATAL_ERROR "missing ${test_name} registration")
    endif()
endforeach()

if(cmake_text MATCHES "BREAK_SYSTEM_TESTING")
    message(FATAL_ERROR "production break_system must not use test hooks")
endif()
