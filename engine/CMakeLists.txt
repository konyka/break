cmake_minimum_required(VERSION 3.20)
project(PureCEngine LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform detection
option(ENGINE_ENABLE_WAYLAND "Enable native Wayland support (Linux only)" OFF)

if(UNIX)
    if(APPLE)
        set(ENGINE_PLATFORM "macos")
    else()
        if(ENGINE_ENABLE_WAYLAND)
            find_package(PkgConfig REQUIRED)
            pkg_check_modules(WAYLAND REQUIRED wayland-client wayland-egl)
            pkg_check_modules(XKB REQUIRED xkbcommon)
            find_program(WAYLAND_SCANNER wayland-scanner REQUIRED)
        else()
            find_package(X11 REQUIRED)
            if(NOT X11_Xrandr_FOUND)
                message(FATAL_ERROR "Xrandr not found (required for multi-monitor support)")
            endif()
        endif()
        set(ENGINE_PLATFORM "linux")
    endif()
elseif(WIN32)
    set(ENGINE_PLATFORM "windows")
endif()

# === Compiler flags ===
if(MSVC)
    # Microsoft Visual C++ (cl.exe)
    add_compile_options(/W4 /WX /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
    # Clang (Linux/Windows clang-cl/clang)
    add_compile_options(-Wall -Wextra -Werror -pedantic)
    # Clang does not produce format-truncation warnings; no special handling needed.
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    # GCC
    add_compile_options(-Wall -Wextra -Werror -pedantic)
    # GCC version-specific flags
    if(CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL "7.0")
        # GCC 7+ warnings are governed by -Werror; no extra suppression here.
    endif()
else()
    message(WARNING "Unknown C compiler: ${CMAKE_C_COMPILER_ID}, applying minimal flags")
    add_compile_options(-Wall)
endif()

# Sanitizers
option(ENGINE_USE_ASAN "Enable AddressSanitizer" OFF)
option(ENGINE_VULKAN "Use Vulkan backend instead of OpenGL" OFF)
if(ENGINE_USE_ASAN)
    if(MSVC)
        add_compile_options(/fsanitize=address)
    else()
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    endif()
endif()

# Engine library
add_library(engine STATIC
    src/core/log.c
    src/core/alloc.c
    src/core/pool.c
    src/core/string.c
    src/core/profiler.c
    src/platform/input.c
    src/platform/time.c
    src/platform/filewatch.c
    src/math/math.c
    src/rhi/rhi.c
    src/renderer/camera.c
    src/renderer/cull.c
    src/renderer/skybox.c
    src/renderer/particles.c
    src/renderer/terrain.c
src/renderer/water.c
    src/renderer/lighting.c
    src/renderer/post_process.c
    src/renderer/ssao.c
    src/renderer/taa.c
    src/renderer/ssr.c
    src/renderer/gpucull.c
    src/renderer/occlusion_cull.c
    src/renderer/frustum_cull.c
    src/renderer/indirect_draw.c
    src/renderer/dof.c
    src/renderer/cinematic.c
    src/renderer/volumetric.c
    src/renderer/tonemap.c
    src/renderer/fxaa.c
    src/renderer/ssgi.c
    src/renderer/lens_flare.c
    src/renderer/sharpen.c
    src/renderer/motion_blur.c
    src/renderer/forward_velocity.c
    src/renderer/contact_shadow.c
    src/renderer/point_shadow.c
    src/renderer/sss.c
    src/renderer/upscale.c
    src/renderer/color_grade.c
    src/renderer/god_rays.c
src/renderer/debug_viz.c
src/renderer/lens_effects.c
    src/renderer/lod.c
    src/renderer/ibl.c
    src/renderer/render_graph.c
    src/renderer/cmd_buffer.c
    src/renderer/combined_post_process.c
    src/renderer/deferred.c
    src/asset/asset.c
    src/asset/async_loader.c
    src/asset/hotreload.c
    src/asset/vfs.c
    src/asset/mipmap_stream.c
    src/ecs/ecs.c
    src/ecs/ecs_system.c
    src/task/task.c
    src/physics/physics.c
    src/physics/bvh.c
    src/physics/character.c
    src/audio/audio.c
    src/audio/audio_stream.c
    src/ui/debug_ui.c
    src/ui/font.c
    src/ui/utf8.c
    src/ui/imgui.c
    src/animation/skeleton.c
    src/animation/animation.c
    src/script/script.c
    src/script/script_lua.c
    src/network/network.c
    src/network/packet.c
    src/network/net_replication.c
    src/scene/scene_serial.c
    src/engine.c
)

# glad.c is generated code — suppress pedantic warnings (void* to fn ptr casts)
add_library(glad STATIC external/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)
if(NOT MSVC)
    target_compile_options(glad PRIVATE -Wno-pedantic)
else()
    # MSVC: suppress glad-specific warnings (void* <-> function pointer casts)
    target_compile_options(glad PRIVATE /wd4055 /wd4152)
endif()

# Vendored Lua 5.4 (external/lua). Built as a single translation unit via
# onelua.c with MAKE_LIB; third-party code so warnings are silenced (it cannot
# satisfy the engine's -Werror -pedantic).
add_library(lua STATIC external/lua/onelua.c)
target_compile_definitions(lua PRIVATE MAKE_LIB)
target_include_directories(lua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)
if(MSVC)
    target_compile_options(lua PRIVATE /w)
else()
    target_compile_options(lua PRIVATE -w)
endif()

target_link_libraries(engine PRIVATE glad lua)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

if(ENGINE_PLATFORM STREQUAL "linux")
    target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)

    if(ENGINE_ENABLE_WAYLAND)
        # Generate xdg-shell protocol bindings
        execute_process(
            COMMAND pkg-config --variable=pkgdatadir wayland-protocols
            OUTPUT_VARIABLE WAYLAND_PROTOCOLS_DIR
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(XDG_SHELL_XML "${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml")
        set(REL_PTR_XML "${WAYLAND_PROTOCOLS_DIR}/unstable/relative-pointer/relative-pointer-unstable-v1.xml")
        set(PTR_CONSTRAINTS_XML "${WAYLAND_PROTOCOLS_DIR}/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml")

        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h
                   ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c
            COMMAND ${WAYLAND_SCANNER} client-header ${XDG_SHELL_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h
            COMMAND ${WAYLAND_SCANNER} private-code ${XDG_SHELL_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c
            DEPENDS ${XDG_SHELL_XML}
            COMMENT "Generating xdg-shell Wayland protocol bindings"
        )

        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/relative-pointer-unstable-v1-client-protocol.h
                   ${CMAKE_CURRENT_BINARY_DIR}/relative-pointer-unstable-v1-protocol.c
            COMMAND ${WAYLAND_SCANNER} client-header ${REL_PTR_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/relative-pointer-unstable-v1-client-protocol.h
            COMMAND ${WAYLAND_SCANNER} private-code ${REL_PTR_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/relative-pointer-unstable-v1-protocol.c
            DEPENDS ${REL_PTR_XML}
            COMMENT "Generating relative-pointer-unstable-v1 Wayland protocol bindings"
        )

        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/pointer-constraints-unstable-v1-client-protocol.h
                   ${CMAKE_CURRENT_BINARY_DIR}/pointer-constraints-unstable-v1-protocol.c
            COMMAND ${WAYLAND_SCANNER} client-header ${PTR_CONSTRAINTS_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/pointer-constraints-unstable-v1-client-protocol.h
            COMMAND ${WAYLAND_SCANNER} private-code ${PTR_CONSTRAINTS_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/pointer-constraints-unstable-v1-protocol.c
            DEPENDS ${PTR_CONSTRAINTS_XML}
            COMMENT "Generating pointer-constraints-unstable-v1 Wayland protocol bindings"
        )

        target_sources(engine PRIVATE
            src/platform/window_wayland.c
            src/platform/gamepad_linux.c
            ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c
            ${CMAKE_CURRENT_BINARY_DIR}/relative-pointer-unstable-v1-protocol.c
            ${CMAKE_CURRENT_BINARY_DIR}/pointer-constraints-unstable-v1-protocol.c
        )
        target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_WAYLAND=1)
        target_include_directories(engine PRIVATE
            ${CMAKE_CURRENT_BINARY_DIR}
            ${WAYLAND_INCLUDE_DIRS}
            ${XKB_INCLUDE_DIRS}
        )
    else()
        target_sources(engine PRIVATE
            src/platform/window_x11.c
            src/platform/gamepad_linux.c
        )
        target_include_directories(engine PRIVATE ${X11_INCLUDE_DIRS})
    endif()

    if(ENGINE_VULKAN)
        find_package(Vulkan REQUIRED)
        target_compile_definitions(engine PUBLIC ENGINE_VULKAN=1)
        if(ENGINE_ENABLE_WAYLAND)
            target_link_libraries(engine PRIVATE ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} ${Vulkan_LIBRARIES} shaderc_shared dl pthread)
        else()
            target_link_libraries(engine PRIVATE ${X11_LIBRARIES} ${X11_Xrandr_LIB} ${Vulkan_LIBRARIES} shaderc_shared dl pthread)
        endif()
    else()
        if(ENGINE_ENABLE_WAYLAND)
            target_link_libraries(engine PRIVATE ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} GL EGL dl pthread)
        else()
            target_link_libraries(engine PRIVATE ${X11_LIBRARIES} ${X11_Xrandr_LIB} GL dl pthread)
        endif()
    endif()

elseif(ENGINE_PLATFORM STREQUAL "windows")
    target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_WINDOWS=1 _WIN32_WINNT=0x0601)
    target_sources(engine PRIVATE
        src/platform/window_win32.c
        src/platform/gamepad_win.c
    )

    if(ENGINE_VULKAN)
        find_package(Vulkan REQUIRED)
        target_compile_definitions(engine PUBLIC ENGINE_VULKAN=1)
        target_link_libraries(engine PRIVATE Vulkan::Vulkan)
    else()
        target_link_libraries(engine PRIVATE opengl32 gdi32)
    endif()

    target_link_libraries(engine PRIVATE user32 kernel32 shell32)
    # XInput (gamepad) is loaded dynamically at runtime — no import lib needed.
    # Winsock2 for network module
    target_link_libraries(engine PRIVATE ws2_32)

elseif(ENGINE_PLATFORM STREQUAL "macos")
    # macOS reuses the Vulkan backend via MoltenVK; the window is a Cocoa
    # NSWindow whose content layer is a CAMetalLayer (Objective-C source).
    enable_language(OBJC)
    find_package(Vulkan REQUIRED)
    target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_MACOS=1 ENGINE_VULKAN=1)
    target_sources(engine PRIVATE src/platform/window_cocoa.m)

    # Cocoa/QuartzCore headers cannot satisfy the engine's -Werror -pedantic.
    # Manual reference counting (no ARC) so Obj-C handles can live in the C
    # Platform struct without __strong qualifiers.
    set_source_files_properties(src/platform/window_cocoa.m PROPERTIES
        COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-fno-objc-arc")

    target_link_libraries(engine PRIVATE
        ${Vulkan_LIBRARIES}
        shaderc_shared
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework IOKit"
    )
endif()

# Executable
add_executable(engine_demo src/main.c)
target_link_libraries(engine_demo PRIVATE engine m)

# Vulkan test executable
add_executable(test_vulkan src/test_vulkan.c)
target_link_libraries(test_vulkan PRIVATE engine m)

add_executable(packer tools/packer.c)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(packer PRIVATE -Wno-format-truncation)
endif()

# --- Unit Tests ---
option(ENGINE_BUILD_TESTS "Build unit tests" ON)
if(ENGINE_BUILD_TESTS)
    enable_testing()

    set(TEST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)

    # test_math: only needs math.c (vec3/quat are inline in header)
    add_executable(test_math tests/test_math.c src/math/math.c)
    target_include_directories(test_math PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_math PRIVATE m)
    add_test(NAME test_math COMMAND test_math)

    # test_task: needs task.c + log.c
    add_executable(test_task tests/test_task.c src/task/task.c src/core/log.c)
    target_include_directories(test_task PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_task PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
        target_link_libraries(test_task PRIVATE pthread m)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_task PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_task PRIVATE kernel32)
    endif()
    add_test(NAME test_task COMMAND test_task)

    # test_lod: needs lod.c + math.c
    add_executable(test_lod tests/test_lod.c src/renderer/lod.c src/math/math.c)
    target_include_directories(test_lod PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_lod PRIVATE m)
    add_test(NAME test_lod COMMAND test_lod)

    # test_async_loader: needs async_loader.c + vfs.c + log.c
    add_executable(test_async_loader tests/test_async_loader.c
        src/asset/async_loader.c src/asset/vfs.c src/core/log.c
        external/stb_image_impl.c)
    target_include_directories(test_async_loader PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_async_loader PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
        target_link_libraries(test_async_loader PRIVATE pthread m)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_async_loader PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_async_loader PRIVATE kernel32)
    endif()
    add_test(NAME test_async_loader COMMAND test_async_loader)

    # test_ecs: needs ecs.c + log.c
    add_executable(test_ecs tests/test_ecs.c src/ecs/ecs.c src/core/log.c)
    target_include_directories(test_ecs PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_ecs PRIVATE m)
    add_test(NAME test_ecs COMMAND test_ecs)

    # test_ecs_system: needs ecs.c + ecs_system.c + task.c + log.c
    add_executable(test_ecs_system tests/test_ecs_system.c
        src/ecs/ecs.c src/ecs/ecs_system.c src/task/task.c src/core/log.c)
    target_include_directories(test_ecs_system PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_ecs_system PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
        target_link_libraries(test_ecs_system PRIVATE pthread m)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_ecs_system PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_ecs_system PRIVATE kernel32)
    endif()
    add_test(NAME test_ecs_system COMMAND test_ecs_system)

    # test_render_graph: needs render_graph.c + log.c
    add_executable(test_render_graph tests/test_render_graph.c
        src/renderer/render_graph.c src/core/log.c src/math/math.c)
    target_include_directories(test_render_graph PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_render_graph PRIVATE m)
    add_test(NAME test_render_graph COMMAND test_render_graph)

    # test_packet: needs packet.c (no other deps)
    add_executable(test_packet tests/test_packet.c src/network/packet.c)
    target_include_directories(test_packet PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_packet PRIVATE m)
    add_test(NAME test_packet COMMAND test_packet)

    # test_network: needs network.c (BSD sockets / Winsock)
    add_executable(test_network tests/test_network.c src/network/network.c)
    target_include_directories(test_network PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_network PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=200112L)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_network PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_network PRIVATE ws2_32)
    endif()
    add_test(NAME test_network COMMAND test_network)

    # test_net_replication: transform snapshot broadcast over UDP loopback
    add_executable(test_net_replication tests/test_net_replication.c
        src/network/net_replication.c src/network/packet.c src/network/network.c
        src/platform/time.c)
    target_include_directories(test_net_replication PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_net_replication PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=200112L)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_net_replication PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_net_replication PRIVATE ws2_32)
    endif()
    add_test(NAME test_net_replication COMMAND test_net_replication)

    # test_string: needs string.c (no other deps)
    add_executable(test_string tests/test_string.c src/core/string.c)
    target_include_directories(test_string PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_string PRIVATE m)
    add_test(NAME test_string COMMAND test_string)

    # test_alloc: needs alloc.c + log.c
    add_executable(test_alloc tests/test_alloc.c src/core/alloc.c src/core/log.c)
    target_include_directories(test_alloc PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_alloc PRIVATE m)
    add_test(NAME test_alloc COMMAND test_alloc)

    # test_pool: fixed-size block allocator
    add_executable(test_pool tests/test_pool.c src/core/pool.c src/core/log.c)
    target_include_directories(test_pool PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_pool PRIVATE m)
    add_test(NAME test_pool COMMAND test_pool)

    # test_font_ui: UTF-8 decoding + immediate-mode UI logic (headless, no RHI)
    add_executable(test_font_ui tests/test_font_ui.c src/ui/utf8.c src/core/log.c)
    target_include_directories(test_font_ui PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_font_ui PRIVATE m)
    add_test(NAME test_font_ui COMMAND test_font_ui)

    # test_mipmap_stream: streaming residency/eviction over async loader + VFS
    add_executable(test_mipmap_stream tests/test_mipmap_stream.c
        src/asset/mipmap_stream.c src/asset/async_loader.c src/asset/vfs.c
        src/platform/time.c src/core/log.c external/stb_image_impl.c)
    target_include_directories(test_mipmap_stream PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_mipmap_stream PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
        target_link_libraries(test_mipmap_stream PRIVATE pthread m)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_mipmap_stream PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_mipmap_stream PRIVATE kernel32)
    endif()
    add_test(NAME test_mipmap_stream COMMAND test_mipmap_stream)

    # test_audio: 3D distance attenuation model (headless, inline-only, no device)
    add_executable(test_audio tests/test_audio.c)
    target_include_directories(test_audio PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_audio PRIVATE m)
    add_test(NAME test_audio COMMAND test_audio)

    # test_vulkan: full backend integration + golden-image regression (VK + GL).
    # Runs from the source dir so it can find shaders/ and committed golden images.
    add_test(NAME test_vulkan COMMAND test_vulkan
             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set_tests_properties(test_vulkan PROPERTIES TIMEOUT 180)

    # test_physics: needs physics.c + bvh.c + math.c + log.c
    add_executable(test_physics tests/test_physics.c
        src/physics/physics.c src/physics/bvh.c src/math/math.c src/core/log.c)
    target_include_directories(test_physics PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_physics PRIVATE m)
    add_test(NAME test_physics COMMAND test_physics)

    # test_script: needs script.c + log.c
    add_executable(test_script tests/test_script.c src/script/script.c src/core/log.c)
    target_include_directories(test_script PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_script PRIVATE m)
    add_test(NAME test_script COMMAND test_script)

    # test_script_lua: real Lua 5.4 + ECS/physics bindings
    add_executable(test_script_lua tests/test_script_lua.c
        src/script/script_lua.c src/ecs/ecs.c src/physics/physics.c
        src/physics/bvh.c src/math/math.c src/core/log.c)
    target_include_directories(test_script_lua PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_script_lua PRIVATE lua m)
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_script_lua PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_script_lua PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    endif()
    add_test(NAME test_script_lua COMMAND test_script_lua)

    # test_character: needs character.c + physics.c + bvh.c + math.c + log.c
    add_executable(test_character tests/test_character.c
        src/physics/character.c src/physics/physics.c src/physics/bvh.c src/math/math.c src/core/log.c)
    target_include_directories(test_character PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_character PRIVATE m)
    add_test(NAME test_character COMMAND test_character)

    # test_animation: needs animation.c + skeleton.c + log.c + math.c
    add_executable(test_animation tests/test_animation.c
        src/animation/animation.c src/animation/skeleton.c src/math/math.c src/core/log.c)
    target_include_directories(test_animation PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_animation PRIVATE m)
    add_test(NAME test_animation COMMAND test_animation)

    # test_scene_serial: needs scene_serial.c + ecs.c + log.c + math.c
    add_executable(test_scene_serial tests/test_scene_serial.c
        src/scene/scene_serial.c src/ecs/ecs.c src/math/math.c src/core/log.c)
    target_include_directories(test_scene_serial PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_scene_serial PRIVATE m)
    add_test(NAME test_scene_serial COMMAND test_scene_serial)

    # test_vfs: needs vfs.c + log.c
    add_executable(test_vfs tests/test_vfs.c src/asset/vfs.c src/core/log.c)
    target_include_directories(test_vfs PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_vfs PRIVATE m)
    add_test(NAME test_vfs COMMAND test_vfs)

    # test_camera_frustum: needs camera.c + cull.c + frustum_cull.c + math.c
    add_executable(test_camera_frustum tests/test_camera_frustum.c
        src/renderer/camera.c src/renderer/cull.c src/renderer/frustum_cull.c src/math/math.c)
    target_include_directories(test_camera_frustum PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_camera_frustum PRIVATE m)
    add_test(NAME test_camera_frustum COMMAND test_camera_frustum)

    # test_cmd_buffer: needs cmd_buffer.c + log.c + RHI stubs (recording only, no submit)
    add_executable(test_cmd_buffer tests/test_cmd_buffer.c
        src/renderer/cmd_buffer.c src/core/log.c tests/rhi_stubs.c)
    target_include_directories(test_cmd_buffer PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_cmd_buffer PRIVATE m)
    add_test(NAME test_cmd_buffer COMMAND test_cmd_buffer)

    # test_profiler: needs profiler.c + time.c
    add_executable(test_profiler tests/test_profiler.c
        src/core/profiler.c src/platform/time.c)
    target_include_directories(test_profiler PRIVATE ${TEST_INCLUDE_DIRS})
    target_compile_definitions(test_profiler PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
    target_link_libraries(test_profiler PRIVATE m)
    add_test(NAME test_profiler COMMAND test_profiler)

    # test_lighting: needs lighting.c + math.c + log.c + RHI stubs
    add_executable(test_lighting tests/test_lighting.c
        src/renderer/lighting.c src/math/math.c src/core/log.c tests/rhi_stubs.c)
    target_include_directories(test_lighting PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_lighting PRIVATE m)
    add_test(NAME test_lighting COMMAND test_lighting)

    # test_occlusion_visibility: needs occlusion_cull.c + log.c + RHI stubs
    add_executable(test_occlusion_visibility tests/test_occlusion_visibility.c
        src/renderer/occlusion_cull.c src/core/log.c tests/rhi_stubs.c)
    target_include_directories(test_occlusion_visibility PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_occlusion_visibility PRIVATE m)
    add_test(NAME test_occlusion_visibility COMMAND test_occlusion_visibility)

    # test_terrain: CPU-side terrain height sampling/modify/erode
    add_executable(test_terrain tests/test_terrain.c
        src/renderer/terrain.c src/math/math.c src/core/log.c tests/rhi_stubs.c)
    target_include_directories(test_terrain PRIVATE ${TEST_INCLUDE_DIRS})
    target_compile_definitions(test_terrain PRIVATE ENGINE_VULKAN=1)
    target_link_libraries(test_terrain PRIVATE m)
    add_test(NAME test_terrain COMMAND test_terrain)

    # test_input: input state machine & tracking
    add_executable(test_input tests/test_input.c
        src/platform/input.c)
    target_include_directories(test_input PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_input PRIVATE m)
    add_test(NAME test_input COMMAND test_input)
endif()
