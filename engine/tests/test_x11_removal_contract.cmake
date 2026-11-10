foreach(required_var ENGINE_SOURCE_DIR WORK)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}" "${WORK}/empty-pkgconfig")
set(failures "")
set(common_args
    -DENGINE_BUILD_TESTS=OFF
    -DENGINE_ENABLE_IPO=OFF
    -DENGINE_RHI_BACKEND=opengl
    -DBREAK_ENABLE_SNOWFLAKE=OFF
    -DBREAK_ENABLE_CRYPTO=OFF
    -DBREAK_ENABLE_CRASH=OFF)

function(expect_removed_configuration name)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/${name}"
            ${common_args} ${ARGN}
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(rc EQUAL 0)
        string(APPEND failures "${name}: legacy configuration succeeded\n")
    elseif(NOT "${out}${err}" MATCHES "X11 support was removed; use native Wayland")
        string(APPEND failures
            "${name}: missing removal diagnostic\n${out}${err}\n")
    endif()
    set(failures "${failures}" PARENT_SCOPE)
endfunction()

expect_removed_configuration(no-wayland
    -DENGINE_ENABLE_WAYLAND=OFF -DMYUI_PAL=dummy)
expect_removed_configuration(legacy-pal
    -DENGINE_ENABLE_WAYLAND=ON -DMYUI_PAL=x11)

function(expect_invalid_pal name expected_diagnostic system_name pal)
    if(system_name STREQUAL "Linux")
        set(platform_args -DENGINE_ENABLE_WAYLAND=ON -DENGINE_RHI_BACKEND=opengl)
    elseif(system_name STREQUAL "Darwin")
        set(platform_args -DENGINE_ENABLE_WAYLAND=OFF -DENGINE_RHI_BACKEND=metal)
    else()
        set(platform_args -DENGINE_ENABLE_WAYLAND=OFF -DENGINE_RHI_BACKEND=opengl)
    endif()
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/${name}"
            ${common_args}
            "-DCMAKE_SYSTEM_NAME=${system_name}"
            -DCMAKE_C_COMPILER_WORKS=TRUE -DCMAKE_CXX_COMPILER_WORKS=TRUE
            -DCMAKE_C_ABI_COMPILED=TRUE -DCMAKE_CXX_ABI_COMPILED=TRUE
            ${platform_args} "-DMYUI_PAL=${pal}"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(rc EQUAL 0)
        string(APPEND failures "${name}: invalid PAL ${pal} configured successfully\n")
    elseif(NOT "${out}${err}" MATCHES "${expected_diagnostic}")
        string(APPEND failures
            "${name}: missing diagnostic ${expected_diagnostic}\n${out}${err}\n")
    endif()
    set(failures "${failures}" PARENT_SCOPE)
endfunction()

expect_invalid_pal(unknown-pal "Unsupported MYUI_PAL" Linux not-a-pal)
expect_invalid_pal(win32-on-linux "MYUI_PAL=win32 requires a Windows host" Linux win32)
expect_invalid_pal(cocoa-on-linux "MYUI_PAL=cocoa requires an Apple host" Linux cocoa)
expect_invalid_pal(wayland-on-windows
    "MYUI_PAL=wayland requires a Linux/Wayland target" Windows wayland)
expect_invalid_pal(wayland-on-darwin
    "MYUI_PAL=wayland requires a Linux/Wayland target" Darwin wayland)

execute_process(
    COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/default"
        ${common_args} -DMYUI_PAL=dummy
    RESULT_VARIABLE default_rc OUTPUT_VARIABLE default_out ERROR_VARIABLE default_err)
if(NOT default_rc EQUAL 0)
    string(APPEND failures "default: configure failed\n${default_out}${default_err}\n")
else()
    file(READ "${WORK}/default/CMakeCache.txt" default_cache)
    if(NOT default_cache MATCHES "ENGINE_ENABLE_WAYLAND:BOOL=ON")
        string(APPEND failures "default: native Wayland is not enabled\n")
    endif()
endif()

function(missing_wayland_log_valid log)
    set(valid TRUE)
    foreach(required_package wayland-client wayland-egl wayland-cursor)
        if(NOT log MATCHES "Package '${required_package}'.*not found" OR
                NOT log MATCHES "- ${required_package}")
            set(valid FALSE)
        endif()
    endforeach()
    if(NOT log MATCHES "_pkg_check_modules_internal" OR
            NOT log MATCHES "CMakeLists.txt:[0-9]+ \\(pkg_check_modules\\)")
        set(valid FALSE)
    endif()
    set(missing_log_valid "${valid}" PARENT_SCOPE)
endfunction()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env
        "PKG_CONFIG_PATH=" "PKG_CONFIG_LIBDIR=${WORK}/empty-pkgconfig"
        "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/missing-wayland"
        ${common_args} -DMYUI_PAL=dummy
    RESULT_VARIABLE missing_rc OUTPUT_VARIABLE missing_out ERROR_VARIABLE missing_err)
if(missing_rc EQUAL 0)
    string(APPEND failures
        "missing-wayland: missing development packages fell back to another backend\n")
else()
    set(missing_log "${missing_out}${missing_err}")
    missing_wayland_log_valid("${missing_log}")
    if(NOT missing_log_valid)
        string(APPEND failures
            "missing-wayland: pkg-config did not identify all required packages or the real call stack\n${missing_log}\n")
    endif()
endif()

set(local_missing_log [=[-- Package 'wayland-client' not found
-- Package 'wayland-egl' not found
-- Package 'wayland-cursor' not found
 - wayland-client
 - wayland-egl
 - wayland-cursor
/usr/share/cmake-3.28/Modules/FindPkgConfig.cmake:841 (_pkg_check_modules_internal)
CMakeLists.txt:113 (pkg_check_modules)]=])
set(ci_missing_log [=[-- Package 'wayland-client', required by 'virtual:world', not found
-- Package 'wayland-egl', required by 'virtual:world', not found
-- Package 'wayland-cursor', required by 'virtual:world', not found
 - wayland-client
 - wayland-egl
 - wayland-cursor
/usr/share/cmake-3.28/Modules/FindPkgConfig.cmake:841 (_pkg_check_modules_internal)
CMakeLists.txt:113 (pkg_check_modules)]=])
foreach(variant local ci)
    missing_wayland_log_valid("${${variant}_missing_log}")
    if(NOT missing_log_valid)
        string(APPEND failures
            "missing-wayland: ${variant} stdout/stderr diagnostic form was rejected\n${${variant}_missing_log}\n")
    endif()
endforeach()
missing_wayland_log_valid("Package 'unrelated-package' not found")
if(missing_log_valid)
    string(APPEND failures "missing-wayland: unrelated/missing package diagnostic was accepted\n")
endif()

find_path(HOST_GL_INCLUDE_DIR GL/gl.h PATHS /usr/include /usr/local/include)
find_path(HOST_EGL_INCLUDE_DIR EGL/egl.h PATHS /usr/include /usr/local/include)
find_library(HOST_OPENGL_LIBRARY NAMES OpenGL PATHS /usr/lib64 /usr/lib /usr/lib/x86_64-linux-gnu)
find_library(HOST_EGL_LIBRARY NAMES EGL PATHS /usr/lib64 /usr/lib /usr/lib/x86_64-linux-gnu)
foreach(required_probe HOST_GL_INCLUDE_DIR HOST_EGL_INCLUDE_DIR HOST_OPENGL_LIBRARY HOST_EGL_LIBRARY)
    if(NOT ${required_probe})
        message(FATAL_ERROR "${required_probe} is required for the isolated GL dependency matrix")
    endif()
endforeach()

function(expect_missing_gl_dependency name pal missing_component)
    set(root "${WORK}/${name}-sysroot")
    file(MAKE_DIRECTORY "${root}/usr/include" "${root}/usr/lib" "${root}/usr/lib64"
        "${root}/usr/share")
    file(CREATE_LINK /usr/share/wayland-protocols "${root}/usr/share/wayland-protocols" SYMBOLIC)
    if(missing_component STREQUAL "EGL")
        file(CREATE_LINK "${HOST_GL_INCLUDE_DIR}/GL" "${root}/usr/include/GL" SYMBOLIC)
        foreach(libdir usr/lib usr/lib64)
            file(CREATE_LINK "${HOST_OPENGL_LIBRARY}" "${root}/${libdir}/libOpenGL.so" SYMBOLIC)
        endforeach()
        set(expected_missing "EGL")
    else()
        file(CREATE_LINK "${HOST_EGL_INCLUDE_DIR}/EGL" "${root}/usr/include/EGL" SYMBOLIC)
        foreach(libdir usr/lib usr/lib64)
            file(CREATE_LINK "${HOST_EGL_LIBRARY}" "${root}/${libdir}/libEGL.so" SYMBOLIC)
        endforeach()
        set(expected_missing "OpenGL")
    endif()
    set(toolchain "${WORK}/${name}-toolchain.cmake")
    file(WRITE "${toolchain}"
        "set(CMAKE_FIND_ROOT_PATH \"${root}\")\n"
        "set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)\n"
        "set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)\n"
        "set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)\n"
        "set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)\n")
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/${name}"
            ${common_args} "-DMYUI_PAL=${pal}" "-DCMAKE_TOOLCHAIN_FILE=${toolchain}"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(rc EQUAL 0)
        string(APPEND failures
            "${name}: missing ${missing_component} configured successfully through ${pal}\n")
    elseif(NOT "${out}${err}" MATCHES "Could NOT find OpenGL" OR
            NOT "${out}${err}" MATCHES "missing: [^)]*${expected_missing}")
        string(APPEND failures
            "${name}: failure did not identify missing ${expected_missing}\n${out}${err}\n")
    endif()
    set(failures "${failures}" PARENT_SCOPE)
endfunction()

expect_missing_gl_dependency(dummy-missing-egl dummy EGL)
expect_missing_gl_dependency(dummy-missing-gl dummy OpenGL)
expect_missing_gl_dependency(wayland-missing-egl wayland EGL)
expect_missing_gl_dependency(wayland-missing-gl wayland OpenGL)

execute_process(
    COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/auto-missing-gl"
        ${common_args} -DENGINE_RHI_BACKEND=auto -DMYUI_PAL=dummy
        -DCMAKE_DISABLE_FIND_PACKAGE_OpenGL=TRUE
    RESULT_VARIABLE auto_rc OUTPUT_VARIABLE auto_out ERROR_VARIABLE auto_err)
if(auto_rc EQUAL 0)
    string(APPEND failures "auto-missing-gl: Vulkan/OpenGL fallback chain configured without OpenGL\n")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/vulkan-only-without-gl"
        ${common_args} -DENGINE_RHI_BACKEND=vulkan -DENGINE_RHI_MULTI_BACKEND=OFF
        -DMYUI_PAL=dummy -DCMAKE_DISABLE_FIND_PACKAGE_OpenGL=TRUE
    RESULT_VARIABLE vk_rc OUTPUT_VARIABLE vk_out ERROR_VARIABLE vk_err)
if(NOT vk_rc EQUAL 0)
    string(APPEND failures
        "vulkan-only-without-gl: pure Vulkan configuration incorrectly requires OpenGL\n${vk_out}${vk_err}\n")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/windows-off"
        ${common_args}
        -DCMAKE_SYSTEM_NAME=Windows
        -DCMAKE_C_COMPILER_WORKS=TRUE -DCMAKE_CXX_COMPILER_WORKS=TRUE
        -DCMAKE_C_ABI_COMPILED=TRUE -DCMAKE_CXX_ABI_COMPILED=TRUE
        -DENGINE_ENABLE_WAYLAND=OFF -DMYUI_PAL=dummy
    RESULT_VARIABLE cross_rc OUTPUT_VARIABLE cross_out ERROR_VARIABLE cross_err)
if(NOT cross_rc EQUAL 0)
    string(APPEND failures
        "windows-off: non-Linux ENGINE_ENABLE_WAYLAND=OFF was rejected\n${cross_out}${cross_err}\n")
endif()

foreach(relative_path
        src/platform/window_x11.c
        src/platform/x11_touch.c
        src/platform/x11_touch.h
        tests/test_platform_x11_runtime.c
        tests/test_x11_touch.c)
    if(EXISTS "${ENGINE_SOURCE_DIR}/${relative_path}")
        string(APPEND failures "core file still exists: ${relative_path}\n")
    endif()
endforeach()

file(READ "${ENGINE_SOURCE_DIR}/CMakeLists.txt" cmake_text)
foreach(forbidden_token
        "find_package(X11 REQUIRED)"
        "ENGINE_X11"
        "X11_INCLUDE_DIRS"
        "src/platform/window_x11.c"
        "src/platform/x11_touch.c")
    string(FIND "${cmake_text}" "${forbidden_token}" offset)
    if(NOT offset EQUAL -1)
        string(APPEND failures "core CMake still contains: ${forbidden_token}\n")
    endif()
endforeach()

foreach(probe_spec
        "src/platform/platform_wsi.h|PLATFORM_WSI_BACKEND_X11"
        "src/platform/platform_size.h|platform_size_x11"
        "src/platform/platform_vk_surface.c|VK_KHR_xlib_surface"
        "src/platform/platform_vk_surface.c|vkCreateXlibSurfaceKHR"
        "src/platform/platform_vk_surface_vkabi.h|PVkXlibSurfaceCreateInfo")
    string(REPLACE "|" ";" probe_parts "${probe_spec}")
    list(GET probe_parts 0 relative_path)
    list(GET probe_parts 1 forbidden_token)
    file(READ "${ENGINE_SOURCE_DIR}/${relative_path}" probe_text)
    string(FIND "${probe_text}" "${forbidden_token}" offset)
    if(NOT offset EQUAL -1)
        string(APPEND failures "${relative_path} still contains: ${forbidden_token}\n")
    endif()
endforeach()

if(failures)
    message(FATAL_ERROR "X11 removal contract failed:\n${failures}")
endif()
