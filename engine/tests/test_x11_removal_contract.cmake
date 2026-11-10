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
    foreach(required_package wayland-client wayland-egl wayland-cursor)
        if(NOT missing_log MATCHES "Package '${required_package}' not found" OR
                NOT missing_log MATCHES "- ${required_package}")
            string(APPEND failures
                "missing-wayland: pkg-config did not identify ${required_package}\n${missing_log}\n")
        endif()
    endforeach()
    if(NOT missing_log MATCHES "_pkg_check_modules_internal" OR
            NOT missing_log MATCHES "CMakeLists.txt:[0-9]+ \\(pkg_check_modules\\)")
        string(APPEND failures
            "missing-wayland: failure did not come from the real pkg_check_modules call\n${missing_log}\n")
    endif()
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
