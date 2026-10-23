if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

# break_editor is a formal top-level static library...
if(NOT cmake_text MATCHES "add_library\\(break_editor STATIC")
    message(FATAL_ERROR "missing formal target break_editor")
endif()

# ...defined after the break_lua target and before the next
# ENGINE_BUILD_TESTS block that follows it, i.e. at top level (independent
# of ENGINE_BUILD_TESTS).
string(FIND "${cmake_text}" "add_library(break_lua STATIC" break_lua_pos)
string(FIND "${cmake_text}" "add_library(break_editor STATIC" break_editor_pos)
if(break_lua_pos LESS 0 OR break_editor_pos LESS 0 OR break_editor_pos LESS break_lua_pos)
    message(FATAL_ERROR "break_editor must be defined after the break_lua target")
endif()
string(SUBSTRING "${cmake_text}" ${break_lua_pos} -1 after_break_lua_text)
string(FIND "${after_break_lua_text}" "if(ENGINE_BUILD_TESTS)" next_tests_block_rel)
if(next_tests_block_rel LESS 0)
    message(FATAL_ERROR "no ENGINE_BUILD_TESTS block found after the break_lua target")
endif()
math(EXPR next_tests_block_pos "${break_lua_pos} + ${next_tests_block_rel}")
if(break_editor_pos GREATER next_tests_block_pos)
    message(FATAL_ERROR "break_editor must be defined at top level, not inside an ENGINE_BUILD_TESTS block")
endif()

# ...owning its five translation units (first mention of each editor source
# is inside the add_library(break_editor ...) call; the test-only variant
# repeats them later inside the tests block). scene_serial.c is additionally
# compiled inline by the engine target and test_scene_serial (accepted
# existing pattern), so for it only membership in the break_editor block is
# checked, not first mention.
string(FIND "${cmake_text}" "src/editor/editor_doc.c" doc_src_pos)
string(FIND "${cmake_text}" "src/editor/editor_cmd.c" cmd_src_pos)
string(FIND "${cmake_text}" "add_library(stb_truetype STATIC" stb_pos)
if(doc_src_pos LESS break_editor_pos OR
   (stb_pos GREATER break_editor_pos AND doc_src_pos GREATER stb_pos))
    message(FATAL_ERROR "src/editor/editor_doc.c is not owned by break_editor")
endif()
if(cmd_src_pos LESS break_editor_pos OR
   (stb_pos GREATER break_editor_pos AND cmd_src_pos GREATER stb_pos))
    message(FATAL_ERROR "src/editor/editor_cmd.c is not owned by break_editor")
endif()

# ...linking break_ecs_replication PUBLIC (which owns ecs.c and log.c)...
if(NOT cmake_text MATCHES "target_link_libraries\\(break_editor PUBLIC break_ecs_replication")
    message(FATAL_ERROR "break_editor does not link break_ecs_replication PUBLIC")
endif()

# ...compiling exactly one copy of scene_serial.c (Task 2: no formal library
# owns it; the engine target's and test_scene_serial's inline copies are the
# accepted existing pattern) and never compiling ecs.c itself
# (break_ecs_replication owns it).
string(REGEX MATCH "add_library\\(break_editor STATIC[^)]*\\)" break_editor_block "${cmake_text}")
if(NOT break_editor_block)
    message(FATAL_ERROR "could not isolate the break_editor add_library block")
endif()
if(break_editor_block MATCHES "ecs\\.c")
    message(FATAL_ERROR "break_editor must not compile ecs.c (break_ecs_replication owns it)")
endif()
if(NOT break_editor_block MATCHES "src/editor/editor_scene\\.c")
    message(FATAL_ERROR "break_editor does not own src/editor/editor_scene.c")
endif()
if(NOT break_editor_block MATCHES "src/editor/editor_components\\.c")
    message(FATAL_ERROR "break_editor does not own src/editor/editor_components.c")
endif()
if(NOT break_editor_block MATCHES "src/scene/scene_serial\\.c")
    message(FATAL_ERROR "break_editor does not own exactly one src/scene/scene_serial.c copy")
endif()

# engine, engine_demo, and dxx_break must not link break_editor. Their
# target_link_libraries calls are single-line in this file, so a line-level
# scan is exact for the current style.
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_editor")
        message(FATAL_ERROR "break_editor leaked into a consumer link line: ${line}")
    endif()
endforeach()

# The focused tests link the test-only variant (BREAK_EDITOR_TESTING=1
# hooks) rather than the production target; the production archive stays
# hook-free. The variant compiles the same five translation units and links
# the same break_ecs_replication.
if(NOT cmake_text MATCHES "add_library\\(break_editor_test STATIC src/editor/editor_doc.c src/editor/editor_cmd.c src/editor/editor_scene.c src/editor/editor_components.c src/scene/scene_serial.c")
    message(FATAL_ERROR "missing test-only break_editor_test variant over all break_editor sources")
endif()
if(NOT cmake_text MATCHES "target_compile_definitions\\(break_editor_test PRIVATE BREAK_EDITOR_TESTING=1")
    message(FATAL_ERROR "break_editor_test does not define BREAK_EDITOR_TESTING=1")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(break_editor_test PUBLIC break_ecs_replication")
    message(FATAL_ERROR "break_editor_test does not link break_ecs_replication PUBLIC")
endif()
if(NOT cmake_text MATCHES "add_executable\\(test_editor_doc tests/test_editor_doc.c")
    message(FATAL_ERROR "missing test_editor_doc executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_editor_doc PRIVATE break_editor_test")
    message(FATAL_ERROR "test_editor_doc does not link break_editor_test")
endif()
if(NOT cmake_text MATCHES "add_executable\\(test_editor_cmd tests/test_editor_cmd.c")
    message(FATAL_ERROR "missing test_editor_cmd executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_editor_cmd PRIVATE break_editor_test")
    message(FATAL_ERROR "test_editor_cmd does not link break_editor_test")
endif()
if(NOT cmake_text MATCHES "add_executable\\(test_editor_scene tests/test_editor_scene.c")
    message(FATAL_ERROR "missing test_editor_scene executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_editor_scene PRIVATE break_editor_test")
    message(FATAL_ERROR "test_editor_scene does not link break_editor_test")
endif()
if(NOT cmake_text MATCHES "add_executable\\(test_editor_components tests/test_editor_components.c")
    message(FATAL_ERROR "missing test_editor_components executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_editor_components PRIVATE break_editor_test")
    message(FATAL_ERROR "test_editor_components does not link break_editor_test")
endif()

# Task 4: the editor shell executable is a formal top-level target linking
# break_editor. break_editor must be listed FIRST on its link line: both
# libbreak_editor.a and libengine.a carry scene_serial.o, static archives
# only pull members to resolve still-undefined symbols, and editor_panels.o
# reaches scene_serial through break_editor's editor_scene.o — with this
# order the engine copy is never pulled (verified on the built binary with
# nm: exactly one scene_save_binary definition, zero undefined references).
if(NOT cmake_text MATCHES "add_executable\\(editor apps/editor/editor_main.c")
    message(FATAL_ERROR "missing formal editor executable target")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(editor PRIVATE break_editor break_myui engine m")
    message(FATAL_ERROR "editor must link break_editor before break_myui/engine (scene_serial single-owner link order)")
endif()
if(NOT cmake_text MATCHES "engine_link_rhi_backend\\(editor\\)")
    message(FATAL_ERROR "editor does not go through engine_link_rhi_backend")
endif()

message(STATUS "break_editor target contract passed")
