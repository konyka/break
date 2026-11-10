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

    if(NOT DEFINED TARGET_SYSTEM_NAME)
        set(TARGET_SYSTEM_NAME "${CMAKE_HOST_SYSTEM_NAME}")
    endif()
    set(target_args "-DCMAKE_SYSTEM_NAME=${TARGET_SYSTEM_NAME}")
    if(DEFINED ZIG_EXECUTABLE)
        string(TOLOWER "${TARGET_SYSTEM_NAME}" target_lower)
        if(TARGET_SYSTEM_NAME STREQUAL "Windows")
            set(zig_target x86_64-windows-gnu)
        elseif(TARGET_SYSTEM_NAME STREQUAL "Darwin")
            set(zig_target x86_64-macos)
        else()
            message(FATAL_ERROR "No Zig target mapping for ${TARGET_SYSTEM_NAME}")
        endif()
        set(zig_cc "${WORK}/zig-${target_lower}-cc.sh")
        set(zig_ar "${WORK}/zig-${target_lower}-ar.sh")
        set(zig_ranlib "${WORK}/zig-${target_lower}-ranlib.sh")
        file(WRITE "${zig_cc}"
            "#!/usr/bin/env bash\nexec \"${ZIG_EXECUTABLE}\" cc -target ${zig_target} \"$@\"\n")
        file(WRITE "${zig_ar}"
            "#!/usr/bin/env bash\nexec \"${ZIG_EXECUTABLE}\" ar \"$@\"\n")
        file(WRITE "${zig_ranlib}"
            "#!/usr/bin/env bash\nexec \"${ZIG_EXECUTABLE}\" ranlib \"$@\"\n")
        file(CHMOD "${zig_cc}" "${zig_ar}" "${zig_ranlib}" PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
        list(APPEND target_args
            "-DCMAKE_C_COMPILER=${zig_cc}"
            "-DCMAKE_OBJC_COMPILER=${zig_cc}"
            "-DCMAKE_AR=${zig_ar}"
            "-DCMAKE_RANLIB=${zig_ranlib}"
            "-DCMAKE_SYSTEM_PROCESSOR=x86_64")
    endif()

    set(common_args
        ${target_args}
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

    function(configure_probe name)
        execute_process(
            COMMAND "${CMAKE_COMMAND}" -S "${WORK}/host" -B "${WORK}/${name}"
                ${common_args} ${ARGN}
            RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
        set(probe_log "${out}${err}" PARENT_SCOPE)
        set(probe_rc "${rc}" PARENT_SCOPE)
    endfunction()

    function(expect_configure_failure name expected_diagnostic)
        configure_probe("${name}" ${ARGN})
        if(probe_rc EQUAL 0)
            string(APPEND failures "${name}: legacy/invalid PAL configuration succeeded\n")
        else()
            string(FIND "${probe_log}" "${expected_diagnostic}" diagnostic_offset)
            if(diagnostic_offset EQUAL -1)
                string(APPEND failures
                    "${name}: missing diagnostic: ${expected_diagnostic}\n${probe_log}\n")
            endif()
        endif()
        set(failures "${failures}" PARENT_SCOPE)
    endfunction()

    function(expect_configure_success name)
        configure_probe("${name}" ${ARGN})
        if(NOT probe_rc EQUAL 0)
            string(APPEND failures "${name}: configure failed\n${probe_log}\n")
        endif()
        set(failures "${failures}" PARENT_SCOPE)
    endfunction()

    function(expect_build_success name target)
        configure_probe("${name}" ${ARGN})
        if(NOT probe_rc EQUAL 0)
            string(APPEND failures "${name}: configure failed\n${probe_log}\n")
        else()
            execute_process(
                COMMAND "${CMAKE_COMMAND}" --build "${WORK}/${name}"
                    --target "${target}" -j3
                RESULT_VARIABLE build_rc OUTPUT_VARIABLE build_out ERROR_VARIABLE build_err)
            if(NOT build_rc EQUAL 0)
                string(APPEND failures "${name}: build failed\n${build_out}${build_err}\n")
            endif()
        endif()
        set(failures "${failures}" PARENT_SCOPE)
    endfunction()

    function(expect_probe_success name expected_output)
        if(DEFINED ZIG_EXECUTABLE)
            expect_build_success("${name}" mypal ${ARGN})
        else()
            expect_build_success("${name}" pal_probe ${ARGN})
            if(NOT EXISTS "${WORK}/${name}/pal_probe" AND
                    NOT EXISTS "${WORK}/${name}/pal_probe.exe")
                string(APPEND failures "${name}: pal_probe was not built\n")
            elseif(TARGET_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
                if(EXISTS "${WORK}/${name}/pal_probe.exe")
                    set(probe_exe "${WORK}/${name}/pal_probe.exe")
                else()
                    set(probe_exe "${WORK}/${name}/pal_probe")
                endif()
                execute_process(
                    COMMAND "${CMAKE_COMMAND}" -E env
                        WAYLAND_DISPLAY=task2-no-such-compositor
                        "${probe_exe}"
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

    if(TARGET_SYSTEM_NAME STREQUAL "Linux")
        expect_probe_success(wayland-no-fallback
            "PASS: Wayland creation failed without dummy fallback" -DMYUI_PAL=wayland)
        expect_configure_failure(win32-wrong-platform
            "MYUI_PAL=win32 requires a Windows host" -DMYUI_PAL=win32)
        expect_configure_failure(cocoa-wrong-platform
            "MYUI_PAL=cocoa requires an Apple host" -DMYUI_PAL=cocoa)
    elseif(TARGET_SYSTEM_NAME STREQUAL "Windows")
        expect_configure_failure(wayland-wrong-platform
            "MYUI_PAL=wayland requires a Linux/Wayland target" -DMYUI_PAL=wayland)
        expect_configure_failure(cocoa-wrong-platform
            "MYUI_PAL=cocoa requires an Apple host" -DMYUI_PAL=cocoa)
        if(NATIVE_PAL_CONFIGURE_ONLY)
            expect_configure_success(win32-native -DMYUI_PAL=win32)
        else()
            expect_build_success(win32-native mypal -DMYUI_PAL=win32)
        endif()
    elseif(TARGET_SYSTEM_NAME STREQUAL "Darwin")
        expect_configure_failure(wayland-wrong-platform
            "MYUI_PAL=wayland requires a Linux/Wayland target" -DMYUI_PAL=wayland)
        expect_configure_failure(win32-wrong-platform
            "MYUI_PAL=win32 requires a Windows host" -DMYUI_PAL=win32)
        if(NATIVE_PAL_CONFIGURE_ONLY)
            expect_configure_success(cocoa-native -DMYUI_PAL=cocoa)
        else()
            expect_build_success(cocoa-native mypal -DMYUI_PAL=cocoa)
        endif()
    else()
        string(APPEND failures "unsupported PAL test target: ${TARGET_SYSTEM_NAME}\n")
    endif()

    if(failures)
        message(FATAL_ERROR "myui standalone PAL configuration contract failed:\n${failures}")
    endif()
    message(STATUS "myui standalone PAL configuration contract OK for ${TARGET_SYSTEM_NAME}")
endif()
