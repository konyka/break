foreach(required_var ENGINE_SOURCE_DIR BREAK_SOURCE_DIR)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

set(failures "")
foreach(relative_path
        engine/src/myui/mypal/x11/my_pal_x11.c
        engine/src/myui/mypal/x11/my_pal_x11.h
        engine/tests/test_mypal_x11.c
        engine/tests/test_rhi_x11_runtime.c
        platform/linux/hello_engine_xcb.c
        platform/linux/hello_engine_xcb_opengl.cc)
    if(EXISTS "${BREAK_SOURCE_DIR}/${relative_path}")
        string(APPEND failures "legacy file still exists: ${relative_path}\n")
    endif()
endforeach()

file(GLOB_RECURSE production_sources LIST_DIRECTORIES false
    "${ENGINE_SOURCE_DIR}/src/*.c"
    "${ENGINE_SOURCE_DIR}/src/*.h"
    "${ENGINE_SOURCE_DIR}/tools/*.c"
    "${ENGINE_SOURCE_DIR}/tools/*.h")
list(APPEND production_sources "${ENGINE_SOURCE_DIR}/external/glad.c")
foreach(source_path IN LISTS production_sources)
    file(READ "${source_path}" source_text)
    foreach(forbidden_token XOpenDisplay glXCreateContext my_pal_x11 MYUI_PAL_X11)
        string(FIND "${source_text}" "${forbidden_token}" offset)
        if(NOT offset EQUAL -1)
            file(RELATIVE_PATH relative_path "${BREAK_SOURCE_DIR}" "${source_path}")
            string(APPEND failures
                "production source contains ${forbidden_token}: ${relative_path}\n")
        endif()
    endforeach()
endforeach()

foreach(probe_spec
        "src/rhi/rhi.h|GLX"
        "src/myui/myr/my_gl_desktop.h|GLX"
        "src/myui/myr/my_gl_desktop.c|GLX"
        "src/rhi/rhi_gl.c|GLX"
        "src/rhi/rhi_gl.c|glX"
        "src/rhi/rhi_gl.c|X11/"
        "external/glad.c|PFNGLXGETPROCADDRESSPROC_PRIVATE"
        "external/glad.c|glXGetProcAddressARB"
        "src/myui/myr/my_vgcanvas_vulkan.c|VK_KHR_xlib_surface"
        "tools/myui_explorer.c|EX_HAVE_X11"
        "tools/myui_explorer.c|EX_EXPLORER_NO_X11"
        "tools/myui_explorer.c|run_x11"
        "tools/myui_explorer.c|XImage"
        "tools/myui_explorer.c|EGL_PLATFORM_X11"
        "tools/myui_explorer.c|--platform x11")
    string(REPLACE "|" ";" probe_parts "${probe_spec}")
    list(GET probe_parts 0 relative_path)
    list(GET probe_parts 1 forbidden_token)
    file(READ "${ENGINE_SOURCE_DIR}/${relative_path}" probe_text)
    string(FIND "${probe_text}" "${forbidden_token}" offset)
    if(NOT offset EQUAL -1)
        string(APPEND failures "${relative_path} still contains: ${forbidden_token}\n")
    endif()
endforeach()

file(READ "${ENGINE_SOURCE_DIR}/tools/myui_explorer.c" explorer_text)
foreach(required_token
        run_wayland_soft
        run_gl_wayland
        run_glshot
        EGL_PLATFORM_WAYLAND_KHR
        "no wayland compositor; use --selftest/--shot")
    string(FIND "${explorer_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        string(APPEND failures "explorer is missing Wayland/headless behavior: ${required_token}\n")
    endif()
endforeach()

file(READ "${ENGINE_SOURCE_DIR}/tools/rhi_swapchain_bench.c" bench_text)
string(FIND "${bench_text}" "\"linux-wayland\"" wayland_receipt_offset)
if(wayland_receipt_offset EQUAL -1)
    string(APPEND failures "swapchain bench does not identify its linux-wayland receipt\n")
endif()

file(READ "${ENGINE_SOURCE_DIR}/tests/test_rhi_wayland_runtime.c" runtime_text)
foreach(required_token
        wayland_runtime_available
        rhi_frame_begin_damage
        RHI_FORMAT_R16G16B16A16_SFLOAT
        "memcmp(readback[f], faces[f]"
        "PASS backend=opengl"
        "UNAVAILABLE backend=opengl")
    string(FIND "${runtime_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        string(APPEND failures "Wayland runtime coverage is missing: ${required_token}\n")
    endif()
endforeach()
foreach(runtime_probe XOpenDisplay "X11/")
    string(FIND "${runtime_text}" "${runtime_probe}" offset)
    if(NOT offset EQUAL -1)
        string(APPEND failures "Wayland runtime retains X11 probe: ${runtime_probe}\n")
    endif()
endforeach()

file(READ "${ENGINE_SOURCE_DIR}/tests/test_world_presentation_gpu.c" world_text)
foreach(required_token
        "submit_stats.object_draws != 2u"
        "day_stats.red < 50u"
        "day_stats.green < 50u"
        "day_stats.blue < 50u"
        "day_stats.magenta < 50u"
        "night_stats.luminance * 4u >= day_stats.luminance")
    string(FIND "${world_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        string(APPEND failures "world GPU assertion was weakened: ${required_token}\n")
    endif()
endforeach()
file(READ "${ENGINE_SOURCE_DIR}/tests/test_mesh_gpu_gl.c" mesh_text)
string(FIND "${mesh_text}" "px[0] < 200u" mesh_pixel_offset)
if(mesh_pixel_offset EQUAL -1)
    string(APPEND failures "mesh GPU center-pixel assertion was weakened\n")
endif()

set(cmake_inputs "${ENGINE_SOURCE_DIR}/CMakeLists.txt")
file(GLOB_RECURSE nested_cmake_inputs LIST_DIRECTORIES false
    "${ENGINE_SOURCE_DIR}/src/CMakeLists.txt"
    "${ENGINE_SOURCE_DIR}/src/*.cmake"
    "${ENGINE_SOURCE_DIR}/tools/CMakeLists.txt"
    "${ENGINE_SOURCE_DIR}/tools/*.cmake"
    "${BREAK_SOURCE_DIR}/platform/CMakeLists.txt"
    "${BREAK_SOURCE_DIR}/platform/*.cmake")
list(APPEND cmake_inputs ${nested_cmake_inputs})
list(REMOVE_DUPLICATES cmake_inputs)
foreach(cmake_path IN LISTS cmake_inputs)
    file(READ "${cmake_path}" cmake_text)
    string(REGEX REPLACE "#[^\r\n]*" "" cmake_text "${cmake_text}")
    file(RELATIVE_PATH relative_path "${BREAK_SOURCE_DIR}" "${cmake_path}")
    if(cmake_text MATCHES "find_package[ \t\r\n]*\\([ \t\r\n]*X11([ \t\r\n)]|$)")
        string(APPEND failures "X11 package lookup remains in ${relative_path}\n")
    endif()
    if(cmake_text MATCHES "\\$\\{X11_[^}]*\\}|X11::|-lX11|libX11|X11\\.lib")
        string(APPEND failures "X11 library variable/link form remains in ${relative_path}\n")
    endif()
    string(REGEX MATCHALL "target_link_libraries[ \t\r\n]*\\([^)]*\\)" link_blocks
        "${cmake_text}")
    foreach(link_block IN LISTS link_blocks)
        if(link_block MATCHES "(^|[ \t\r\n(])X11([ \t\r\n)]|$)")
            string(APPEND failures "raw X11 link item remains in ${relative_path}\n")
        endif()
    endforeach()
endforeach()

if(failures)
    message(FATAL_ERROR "GLX/X11 integration removal contract failed:\n${failures}")
endif()
