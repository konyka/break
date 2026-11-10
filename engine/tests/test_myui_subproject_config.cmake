if(NOT DEFINED MYUI_ROOT_CMAKE)
    message(FATAL_ERROR "MYUI_ROOT_CMAKE is required")
endif()

file(READ "${MYUI_ROOT_CMAKE}" myui_root_cmake)

foreach(required_text
        "project(myui LANGUAGES C)"
        "CMAKE_C_STANDARD 11"
        "CMAKE_C_STANDARD_REQUIRED ON"
        "CMAKE_C_EXTENSIONS OFF"
        "MYUI_FONT_STB"
        "MYUI_FONT_FREETYPE"
        "MYUI_IMAGE_STB"
        "MYUI_UI_YAML"
        "MYUI_BIDI"
        "MYUI_HARFBUZZ"
        "MYUI_GLES2"
        "MYUI_GL_DESKTOP"
        "MYUI_VULKAN"
        "add_subdirectory(myc)"
        "add_subdirectory(myr)"
        "add_subdirectory(mypal)"
        "add_subdirectory(myui)"
        "add_subdirectory(mymvvm)"
        "add_subdirectory(mymvvm_myui)"
        "MYUI_THIRD_PARTY_DIR")
    string(FIND "${myui_root_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "myui subproject contract missing: ${required_text}")
    endif()
endforeach()

if(myui_root_cmake MATCHES "CMAKE_SOURCE_DIR")
    message(FATAL_ERROR "myui subproject must not depend on CMAKE_SOURCE_DIR")
endif()

string(FIND "${myui_root_cmake}" "add_subdirectory(myc)" myc_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(myr)" myr_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(mypal)" mypal_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(myui)" myui_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(mymvvm)" mymvvm_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(mymvvm_myui)" mymvvm_ui_offset)
if(NOT myc_offset LESS myr_offset OR
   NOT myr_offset LESS mypal_offset OR
   NOT mypal_offset LESS myui_offset OR
   NOT myui_offset LESS mymvvm_offset OR
   NOT mymvvm_offset LESS mymvvm_ui_offset)
    message(FATAL_ERROR "myui subproject dependency order is invalid")
endif()

if(DEFINED MYUI_ROOT_DIR AND DEFINED WORK)
    file(REMOVE_RECURSE "${WORK}")
    file(MAKE_DIRECTORY "${WORK}/host")
    file(WRITE "${WORK}/host/CMakeLists.txt"
        "cmake_minimum_required(VERSION 3.20)\n"
        "project(myui_pal_probe LANGUAGES C)\n"
        "set(CMAKE_C_STANDARD 11)\n"
        "set(CMAKE_C_STANDARD_REQUIRED ON)\n"
        "set(CMAKE_C_EXTENSIONS OFF)\n"
        "add_subdirectory(\"${MYUI_ROOT_DIR}\" \"\${CMAKE_CURRENT_BINARY_DIR}/myui\")\n"
        "add_executable(pal_probe pal_probe.c)\n"
        "target_link_libraries(pal_probe PRIVATE mypal)\n")
    file(WRITE "${WORK}/host/pal_probe.c" [=[
#include "mypal/my_pal.h"
#include <stdio.h>

void my_ui_command_dispatch_context_enter(my_pal_main_loop_t* loop) {
  (void)loop;
}

void my_ui_command_dispatch_context_leave(my_pal_main_loop_t* loop) {
  (void)loop;
}

int main(void) {
  my_pal_t* pal = my_pal_create(NULL);
#ifdef MYUI_PAL_WAYLAND
  if (pal != NULL) {
    printf("FAIL: Wayland creation returned a fallback PAL\n");
    my_pal_destroy(pal);
    return 1;
  }
  printf("PASS: Wayland creation failed without dummy fallback\n");
  return 0;
#else
  my_pal_window_t* win;
  if (pal == NULL) {
    printf("FAIL: dummy PAL was not created\n");
    return 1;
  }
  win = my_pal_window_create(pal, 32, 24, "dummy probe");
  if (win == NULL) {
    printf("FAIL: dummy CPU window was not created\n");
    my_pal_destroy(pal);
    return 1;
  }
  my_pal_window_destroy(win);
  my_pal_destroy(pal);
  printf("PASS: explicit dummy CPU window\n");
  return 0;
#endif
}
]=])

    set(common_args
        -DMYUI_FONT_STB=OFF
        -DMYUI_FONT_FREETYPE=OFF
        -DMYUI_IMAGE_STB=OFF
        -DMYUI_UI_YAML=OFF
        -DMYUI_BIDI=OFF
        -DMYUI_HARFBUZZ=OFF
        -DMYUI_GLES2=OFF
        -DMYUI_GL_DESKTOP=OFF
        -DMYUI_VULKAN=OFF)
    set(failures "")

    function(expect_configure_failure name expected_diagnostic)
        execute_process(
            COMMAND "${CMAKE_COMMAND}" -S "${WORK}/host" -B "${WORK}/${name}"
                ${common_args} ${ARGN}
            RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
        if(rc EQUAL 0)
            string(APPEND failures "${name}: legacy/invalid PAL configuration succeeded\n")
        else()
            string(FIND "${out}${err}" "${expected_diagnostic}" diagnostic_offset)
            if(diagnostic_offset EQUAL -1)
                string(APPEND failures
                    "${name}: missing diagnostic: ${expected_diagnostic}\n${out}${err}\n")
            endif()
        endif()
        set(failures "${failures}" PARENT_SCOPE)
    endfunction()

    function(expect_probe_success name expected_output)
        execute_process(
            COMMAND "${CMAKE_COMMAND}" -S "${WORK}/host" -B "${WORK}/${name}"
                ${common_args} ${ARGN}
            RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
        if(NOT rc EQUAL 0)
            string(APPEND failures "${name}: configure failed\n${out}${err}\n")
        else()
            execute_process(
                COMMAND "${CMAKE_COMMAND}" --build "${WORK}/${name}"
                    --target pal_probe -j3
                RESULT_VARIABLE build_rc OUTPUT_VARIABLE build_out ERROR_VARIABLE build_err)
            if(NOT build_rc EQUAL 0)
                string(APPEND failures "${name}: build failed\n${build_out}${build_err}\n")
            else()
                execute_process(
                    COMMAND "${CMAKE_COMMAND}" -E env
                        WAYLAND_DISPLAY=task2-no-such-compositor
                        "${WORK}/${name}/pal_probe"
                    RESULT_VARIABLE run_rc OUTPUT_VARIABLE run_out ERROR_VARIABLE run_err)
                string(FIND "${run_out}${run_err}" "${expected_output}" output_offset)
                if(NOT run_rc EQUAL 0 OR output_offset EQUAL -1)
                    string(APPEND failures
                        "${name}: runtime boundary failed\n${run_out}${run_err}\n")
                endif()
            endif()
        endif()
        set(failures "${failures}" PARENT_SCOPE)
    endfunction()

    expect_configure_failure(legacy-x11
        "X11 support was removed; use native Wayland" -DMYUI_PAL=x11)
    expect_configure_failure(unknown-pal
        "Unsupported MYUI_PAL" -DMYUI_PAL=not-a-pal)
    expect_probe_success(default-dummy "PASS: explicit dummy CPU window")
    expect_probe_success(explicit-dummy "PASS: explicit dummy CPU window"
        -DMYUI_PAL=dummy)
    expect_probe_success(wayland-no-fallback
        "PASS: Wayland creation failed without dummy fallback" -DMYUI_PAL=wayland)

    if(failures)
        message(FATAL_ERROR "myui standalone PAL configuration contract failed:\n${failures}")
    endif()
endif()
