cmake_minimum_required(VERSION 3.20)
# VERSION 语义（Task 9 semver 规则，docs/rhi_rollback_runbook.md §5）：
#   major = 破坏性变更（如 OpenGL 删除→v2.0.0，保留给删除 release；Task 6 闸门 BLOCKED）；
#   minor = 新后端/新能力；patch = 修复。版本唯一来源本 project() VERSION；
#   tag 名 v<x.y.z> 与之严格相等（契约测试比对；tag 由 maintainer 发布时创建）。
project(PureCEngine VERSION 1.9.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)

# Platform detection
option(ENGINE_ENABLE_WAYLAND "Enable native Wayland support (Linux only)" OFF)
option(ENGINE_ENABLE_IPO "Enable interprocedural optimization for Release builds when supported" ON)
option(RULE_ENGINE_ENABLE_C11_PARALLEL "Enable the optional C11 rule match executor" OFF)
option(RULE_ENGINE_ENABLE_REDIS "Enable native Redis state provider (requires hiredis and a controlled integration service)" OFF)
# MYUI_PAL option anchor
set(MYUI_PAL "dummy" CACHE STRING
    "myui PAL port: dummy | x11 | wayland | win32 | cocoa")

set(RULE_ENGINE_REDIS_SOURCE_DIR "" CACHE PATH
    "Redis source tree or hiredis source directory used to build the native client")
option(ENGINE_ANDROID_NATIVE_WINDOW "Compile Android Vulkan support for supplied ANativeWindow handles" OFF)
# myui integration options
option(MYUI_FONT_STB "TrueType fonts via stb_truetype" ON)
option(MYUI_FONT_FREETYPE "Hinted fonts via FreeType when available" ON)
option(MYUI_IMAGE_STB "Image decode via stb_image" ON)
option(MYUI_UI_YAML "YAML UI loader" ON)
option(MYUI_BIDI "BiDi reorder + Arabic shaping via vendored SheenBidi" ON)
option(MYUI_HARFBUZZ "Optional OpenType shaping through HarfBuzz + FreeType" ON)
option(MYUI_GLES2 "Enable the reusable myui GLES2 backend when available" ON)
option(MYUI_GL_DESKTOP "Enable the reusable myui desktop OpenGL backend when available" ON)
option(MYUI_VULKAN "Enable the reusable myui Vulkan backend when available" OFF)
option(ENGINE_BUILD_TESTS "Build unit tests" ON)
set(ENGINE_RHI_BACKEND "auto" CACHE STRING
    "RHI backend selection: auto | opengl | vulkan | metal | d3d12")
set_property(CACHE ENGINE_RHI_BACKEND PROPERTY STRINGS auto opengl vulkan metal d3d12)
# Task 8: D3D12 debug layer + GPU-based validation switch. Default ON for
# Debug builds so a fresh -DCMAKE_BUILD_TYPE=Debug configure gets validation;
# the cached value sticks afterwards, so -DENGINE_D3D12_DEBUG=OFF overrides
# explicitly. Release defaults OFF (zero debug-layer overhead).
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT DEFINED ENGINE_D3D12_DEBUG)
    set(_engine_d3d12_debug_default ON)
else()
    set(_engine_d3d12_debug_default OFF)
endif()
option(ENGINE_D3D12_DEBUG
    "D3D12 debug layer + GPU-based validation (default ON in Debug)"
    ${_engine_d3d12_debug_default})
set(STREAMLINE_ROOT "" CACHE PATH
    "Optional Streamline SDK root; enables the Windows C++ DLSS adapter")

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(ENGINE_PLATFORM "android")
elseif(CMAKE_SYSTEM_NAME STREQUAL "OHOS")
    set(ENGINE_PLATFORM "harmonyos")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "iOS")
    if(APPLE)
        if(CMAKE_OSX_SYSROOT MATCHES "iphone")
            set(ENGINE_PLATFORM "ios")
        else()
            set(ENGINE_PLATFORM "macos")
        endif()
    else()
        if(ENGINE_ENABLE_WAYLAND)
            find_package(PkgConfig REQUIRED)
            pkg_check_modules(WAYLAND REQUIRED wayland-client wayland-egl wayland-cursor)
            pkg_check_modules(XKB REQUIRED xkbcommon)
            find_program(WAYLAND_SCANNER wayland-scanner REQUIRED)
        else()
            find_package(X11 REQUIRED)
            if(NOT X11_Xrandr_FOUND)
                message(FATAL_ERROR "Xrandr not found (required for multi-monitor support)")
            endif()
            if(X11_Xi_FOUND)
                set(ENGINE_X11_XINPUT2 1)
            endif()
        endif()
        set(ENGINE_PLATFORM "linux")
    endif()
elseif(WIN32)
    set(ENGINE_PLATFORM "windows")
endif()

if(NOT ENGINE_PLATFORM)
    message(FATAL_ERROR
        "Unsupported target platform: configure with a supported Linux, Windows, macOS, iOS, Android, or OHOS toolchain")
endif()

# net_loop backend: platform-optimal event notification mechanism.
#   macOS   -> kqueue        (net_loop_kqueue.c)
#   Linux   -> epoll         (net_loop_epoll.c), or io_uring when
#               ENGINE_NET_IOURING=ON (net_loop_iouring.c, experimental)
#   Windows -> IOCP          (net_loop_iocp.c)
option(ENGINE_NET_IOURING "Use io_uring net_loop backend on Linux (experimental)" OFF)
if(ENGINE_PLATFORM STREQUAL "macos" OR ENGINE_PLATFORM STREQUAL "ios")
    set(NET_LOOP_BACKEND_SRC src/network/net_loop_kqueue.c)
elseif(ENGINE_PLATFORM STREQUAL "windows")
    set(NET_LOOP_BACKEND_SRC src/network/net_loop_iocp.c)
elseif(ENGINE_PLATFORM STREQUAL "android" OR ENGINE_PLATFORM STREQUAL "harmonyos")
    set(NET_LOOP_BACKEND_SRC src/network/net_loop_epoll.c)
elseif(ENGINE_NET_IOURING)
    set(NET_LOOP_BACKEND_SRC src/network/net_loop_iouring.c)
else()
    set(NET_LOOP_BACKEND_SRC src/network/net_loop_epoll.c)
endif()

# === Compiler flags ===
if(MSVC)
    # MSVC-compatible frontends require C mode for this C-only project.
    add_compile_options(/W4 /WX /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/experimental:c11atomics)
    elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
        add_compile_options(/TC)
    endif()
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
    # Clang in GNU mode.
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

if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# Sanitizers
option(ENGINE_USE_ASAN "Enable AddressSanitizer" OFF)
option(ENGINE_USE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)
option(ENGINE_USE_TSAN "Enable ThreadSanitizer" OFF)
option(ENGINE_VULKAN "Use Vulkan backend instead of OpenGL" OFF)
if(NOT ENGINE_RHI_BACKEND STREQUAL "auto" AND
   NOT ENGINE_RHI_BACKEND STREQUAL "opengl" AND
   NOT ENGINE_RHI_BACKEND STREQUAL "vulkan" AND
   NOT ENGINE_RHI_BACKEND STREQUAL "metal" AND
   NOT ENGINE_RHI_BACKEND STREQUAL "d3d12")
    message(FATAL_ERROR
        "ENGINE_RHI_BACKEND must be auto, opengl, vulkan, metal, or d3d12")
endif()
if(ENGINE_RHI_BACKEND STREQUAL "metal" AND NOT APPLE)
    message(FATAL_ERROR
        "metal backend is UNAVAILABLE on this platform (native Metal requires macOS/iOS)")
endif()
if(ENGINE_RHI_BACKEND STREQUAL "vulkan")
    set(ENGINE_VULKAN ON CACHE BOOL "Use Vulkan backend instead of OpenGL" FORCE)
elseif(ENGINE_RHI_BACKEND STREQUAL "opengl")
    set(ENGINE_VULKAN OFF CACHE BOOL "Use Vulkan backend instead of OpenGL" FORCE)
elseif(ENGINE_RHI_BACKEND STREQUAL "d3d12")
    if(NOT WIN32)
        message(FATAL_ERROR
            "ENGINE_RHI_BACKEND=d3d12 is UNAVAILABLE on this platform (Windows only)")
    endif()
    set(ENGINE_VULKAN OFF CACHE BOOL "Use Vulkan backend instead of OpenGL" FORCE)
endif()
if(ENGINE_RHI_BACKEND STREQUAL "metal")
    set(_rhi_backend_effective "metal")
    # metal 不改写 ENGINE_VULKAN（保持 OFF），兼容层语义仅服务 gl/vk。
elseif(ENGINE_RHI_BACKEND STREQUAL "d3d12" AND WIN32)
    set(_rhi_backend_effective "d3d12")
elseif(ENGINE_VULKAN)
    set(_rhi_backend_effective "vulkan")
else()
    set(_rhi_backend_effective "opengl")
endif()
set(ENGINE_RHI_BACKEND_EFFECTIVE "${_rhi_backend_effective}" CACHE INTERNAL
    "Resolved RHI backend for this build" FORCE)
message(STATUS "RHI backend: requested=${ENGINE_RHI_BACKEND}; effective=${ENGINE_RHI_BACKEND_EFFECTIVE}")
if(ENGINE_PLATFORM STREQUAL "android" AND ENGINE_VULKAN)
    find_path(ANDROID_NATIVE_WINDOW_INCLUDE_DIR android/native_window.h)
    if(NOT ENGINE_ANDROID_NATIVE_WINDOW OR NOT ANDROID_NATIVE_WINDOW_INCLUDE_DIR)
        message(FATAL_ERROR
            "ENGINE_VULKAN on Android requires ENGINE_ANDROID_NATIVE_WINDOW=ON and "
            "an NDK android/native_window.h include path (ANativeWindow)")
    endif()
endif()
if(ENGINE_USE_ASAN)
    if(MSVC)
        add_compile_options(/fsanitize=address)
        if(CMAKE_C_COMPILER_ID MATCHES "Clang")
            add_compile_options(/clang:-fno-omit-frame-pointer)
        endif()
    else()
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    endif()
endif()
# R630/R696: Windows Clang ASan binaries need clang_rt.asan_dynamic-<arch>.dll
# beside them — the toolchain dir is never on PATH, so ASan builds only
# ever compiled (never ran) without this copy. One configure-time copy to
# the build root covers every test/fuzz exe in the tree. R696: triggers on
# the ENGINE_USE_ASAN option OR a raw -fsanitize=address in CMAKE_C_FLAGS
# (flag-injected sanitizer builds hit the same DLL requirement).
if(WIN32 AND CMAKE_C_COMPILER_ID MATCHES "Clang" AND NOT MSVC
   AND (ENGINE_USE_ASAN OR CMAKE_C_FLAGS MATCHES "fsanitize=address"))
    execute_process(COMMAND ${CMAKE_C_COMPILER} -print-resource-dir
        OUTPUT_VARIABLE _asan_resource_dir OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(_asan_arch "x86_64")
    else()
        set(_asan_arch "i386")
    endif()
    set(_asan_dll "${_asan_resource_dir}/lib/windows/clang_rt.asan_dynamic-${_asan_arch}.dll")
    if(EXISTS "${_asan_dll}")
        file(COPY "${_asan_dll}" DESTINATION "${CMAKE_BINARY_DIR}")
        message(STATUS "ASan runtime DLL staged: ${_asan_dll}")
    else()
        message(WARNING "ASan runtime DLL not found at ${_asan_dll} — ASan test binaries will not launch")
    endif()
endif()
if(ENGINE_USE_UBSAN)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang" AND NOT MSVC)
        add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer)
        add_link_options(-fsanitize=undefined)
    else()
        message(FATAL_ERROR
            "ENGINE_USE_UBSAN requires GCC or Clang; compiler ${CMAKE_C_COMPILER_ID} is unsupported")
    endif()
endif()
if(ENGINE_USE_TSAN)
    if(MSVC)
        message(FATAL_ERROR
            "ENGINE_USE_TSAN requires GCC or Clang; MSVC is unsupported")
    elseif(NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        message(FATAL_ERROR
            "ENGINE_USE_TSAN requires GCC or Clang; compiler ${CMAKE_C_COMPILER_ID} is unsupported")
    else()
        add_compile_options(-fsanitize=thread -fno-omit-frame-pointer)
        add_link_options(-fsanitize=thread)
    endif()
endif()

# R433: MSVC has no libm — provide an empty interface target so the many
# `target_link_libraries(... m)` below resolve to a no-op on Windows.
if(WIN32)
    add_library(m INTERFACE)
endif()

# R433: shaderc ships no CMake package config on several Linux distributions;
# locate either the shared runtime name or the distro's libshaderc development
# name instead of linking a bare name (which fails with an unhelpful -l error).
# Windows CI installs the pinned LunarG SDK (engine/tools/fetch_vulkan_sdk_windows.cmake);
# its layout is not on the default search path, so honor VULKAN_SDK like
# FindVulkan does.
if(ENGINE_VULKAN OR (ENGINE_PLATFORM STREQUAL "macos" AND
   NOT ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal"))
    find_library(SHADERC_LIB NAMES shaderc_shared shaderc
        HINTS "$ENV{VULKAN_SDK}/Lib" "$ENV{VULKAN_SDK}/lib")
    find_path(SHADERC_INCLUDE_DIR NAMES shaderc/shaderc.h
        HINTS "$ENV{VULKAN_SDK}/Include" "$ENV{VULKAN_SDK}/include")
    if(NOT SHADERC_LIB)
        message(FATAL_ERROR
            "shaderc_shared not found — install shaderc (e.g. libshaderc-dev / shaderc) "
            "or configure without -DENGINE_VULKAN=ON")
    endif()
    if(NOT SHADERC_INCLUDE_DIR)
        message(FATAL_ERROR
            "shaderc headers not found — install shaderc development headers or set SHADERC_INCLUDE_DIR")
    endif()
    find_package(Vulkan REQUIRED)
endif()

# Engine library
set(RHI_CORE_SOURCES
    src/rhi/rhi.c
    src/rhi/rhi_ownership.c
    src/rhi/rhi_validation.c
    src/rhi/rhi_resources.c
    src/rhi/rhi_present_history.c
    src/rhi/rhi_rollout.c)
add_library(engine STATIC
    src/core/log.c
    src/core/shader_io.c
    src/core/alloc.c
    src/core/pool.c
    src/core/string.c
    src/core/profiler.c
    src/platform/input.c
    src/platform/platform_config.c
    src/platform/platform_display_media.c
    src/platform/platform_vk_surface.c
    src/platform/platform_text.c
    src/platform/time.c
    src/platform/filewatch.c
    src/platform/filewatch_backend.c
    src/math/math.c
    ${RHI_CORE_SOURCES}
    src/renderer/camera.c
    src/renderer/cull.c
    src/renderer/render_features.c
    src/renderer/rt_trace.c
    src/renderer/sl_dlss.c
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
    src/renderer/motion_history.c
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
    src/asset/decode_pipeline.c
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
    src/animation/skeleton.c
    src/animation/animation.c
    src/script/script.c
    src/script/script_lua.c
    src/network/network.c
    src/network/packet.c
    src/network/net_replication.c
    ${NET_LOOP_BACKEND_SRC}
    src/scene/scene_serial.c
    src/scene/scene_state.c
    src/engine.c
)
string(TOUPPER "${ENGINE_RHI_BACKEND_EFFECTIVE}" ENGINE_RHI_BACKEND_EFFECTIVE_UPPER)
target_compile_definitions(engine PUBLIC
    ENGINE_RHI_BACKEND_${ENGINE_RHI_BACKEND_EFFECTIVE_UPPER}=1)
# Rollout config: bake config_version into the build; schema enforced by
# test_rhi_rollout_config_contract.
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/assets/rhi_backend_rollout.json" ENGINE_ROLLOUT_JSON)
string(JSON ENGINE_ROLLOUT_CFGVER GET "${ENGINE_ROLLOUT_JSON}" config_version)
target_compile_definitions(engine PUBLIC
    ENGINE_RHI_ROLLOUT_CONFIG_VERSION=${ENGINE_ROLLOUT_CFGVER})

if(WIN32 AND STREAMLINE_ROOT)
    enable_language(CXX)
    add_library(sl_dlss_streamline_adapter STATIC
        src/renderer/sl_dlss_streamline_adapter.cpp)
    target_include_directories(sl_dlss_streamline_adapter PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${STREAMLINE_ROOT}/include)
    target_compile_features(sl_dlss_streamline_adapter PRIVATE cxx_std_14)
    target_compile_definitions(sl_dlss_streamline_adapter PRIVATE
        WIN32_LEAN_AND_MEAN NOMINMAX)
    target_compile_definitions(engine PRIVATE ENGINE_STREAMLINE_CPP_ADAPTER=1)
    target_link_libraries(engine PRIVATE sl_dlss_streamline_adapter)
endif()
if(SHADERC_INCLUDE_DIR)
    # Unconditional-when-found: the include is harmless where shaderc is
    # absent, and guarding it on platform/Vulkan conditions left macOS CI
    # without the -I for rhi_vk.c (fatal 'shaderc/shaderc.h' not found)
    # even though the header and cache value were verified present.
    target_include_directories(engine PRIVATE ${SHADERC_INCLUDE_DIR})
endif()

# Plan C Task 11 legacy: this PUBLIC define used to switch the main.c /
# renderer shader-file #ifdefs so the Metal lane read the *_vk corpus
# (its offline manifest is keyed on those bytes). Plan E deleted every
# consumer — it is now a no-op retained only for build-compat. Shader
# selection follows caps.shader_variant. The native Metal backend consumes
# the offline MSL manifest generated from the Vulkan-layout GLSL corpus, so
# its capabilities select that source set.
if(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")
    target_compile_definitions(engine PUBLIC ENGINE_SHADER_CORPUS_VK=1)
endif()
if(ENGINE_VULKAN OR ENGINE_PLATFORM STREQUAL "macos")
    # rt_trace.c compiles <vulkan/vulkan.h> into the engine target under
    # ENGINE_VULKAN; brew's vulkan-headers keg is not on the default
    # macOS search path (Linux gets /usr/include via libvulkan-dev), so
    # the include dir must reach the engine target explicitly.
    target_include_directories(engine PRIVATE ${Vulkan_INCLUDE_DIRS})
endif()

include(CTest)
if(ENGINE_BUILD_TESTS)
    add_executable(test_platform_compat tests/test_platform_compat.c)
    target_include_directories(test_platform_compat PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_platform_compat PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_platform_compat PRIVATE ENGINE_PLATFORM_MACOS=1)
    elseif(ENGINE_PLATFORM STREQUAL "ios")
        target_compile_definitions(test_platform_compat PRIVATE ENGINE_PLATFORM_IOS=1)
    elseif(ENGINE_PLATFORM STREQUAL "android")
        target_compile_definitions(test_platform_compat PRIVATE ENGINE_PLATFORM_ANDROID=1)
    elseif(ENGINE_PLATFORM STREQUAL "harmonyos")
        target_compile_definitions(test_platform_compat PRIVATE ENGINE_PLATFORM_HARMONYOS=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_platform_compat PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    endif()
    add_test(NAME test_platform_compat COMMAND test_platform_compat)

    foreach(_compat_name IN ITEMS MACOS IOS ANDROID HARMONYOS)
        string(TOLOWER "${_compat_name}" _compat_lower)
        add_executable(test_platform_compat_${_compat_lower}
            tests/test_platform_compat_simulated.c)
        target_include_directories(test_platform_compat_${_compat_lower}
            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
        target_compile_definitions(test_platform_compat_${_compat_lower}
            PRIVATE SIMULATE_${_compat_name}=1)
        add_test(NAME test_platform_compat_${_compat_lower}
            COMMAND test_platform_compat_${_compat_lower})
    endforeach()

    foreach(_wsi_name IN ITEMS X11 WAYLAND WIN32 COCOA ANDROID IOS)
        string(TOLOWER "${_wsi_name}" _wsi_lower)
        add_executable(test_platform_wsi_lifecycle_${_wsi_lower}
            tests/test_platform_wsi_lifecycle.c)
        target_include_directories(test_platform_wsi_lifecycle_${_wsi_lower}
            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${TEST_INCLUDE_DIRS})
        if(NOT _wsi_name STREQUAL "X11")
            target_compile_definitions(test_platform_wsi_lifecycle_${_wsi_lower}
                PRIVATE SIMULATE_${_wsi_name}=1)
        endif()
        add_test(NAME test_platform_wsi_lifecycle_${_wsi_lower}
            COMMAND test_platform_wsi_lifecycle_${_wsi_lower})
    endforeach()
endif()

# glad.c is generated code — suppress pedantic warnings (void* to fn ptr casts)
add_library(glad STATIC external/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)
if(NOT MSVC)
    target_compile_options(glad PRIVATE -Wno-pedantic)
else()
    # MSVC: suppress glad-specific warnings (void* <-> function pointer casts)
    target_compile_options(glad PRIVATE /wd4055 /wd4152)
endif()

# --- RHI backend libraries (multi-backend spec §4.8) ---
# Each backend compiles as its own static library exporting the same rhi_*
# symbol set; an executable links engine plus exactly one backend library via
# engine_link_rhi_backend(). EXCLUDE_FROM_ALL keeps the non-selected backend
# out of the default build (nothing references it). engine_rhi_headless is
# always built: the direct-source RHI contract tests link it unconditionally.
add_library(engine_rhi_opengl STATIC EXCLUDE_FROM_ALL src/rhi/rhi_gl.c)
target_include_directories(engine_rhi_opengl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)
target_link_libraries(engine_rhi_opengl PUBLIC engine PRIVATE glad)

add_library(engine_rhi_headless STATIC src/rhi/rhi_headless.c)
target_include_directories(engine_rhi_headless PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)
# ENGINE_RHI_TEST arms the rhi_test_gl_cache_* hooks consumed by the
# direct-source RHI contract tests that link this library.
target_compile_definitions(engine_rhi_headless PRIVATE ENGINE_RHI_TEST=1)

if(APPLE AND ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")
    enable_language(OBJC)
    add_library(engine_rhi_metal STATIC src/rhi/rhi_metal.m)
    target_include_directories(engine_rhi_metal PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)
    target_compile_definitions(engine_rhi_metal PRIVATE ENGINE_RHI_BACKEND_METAL=1)
    # ENGINE_RHI_TEST arms the rhi_test_metal_set_suspended hook consumed by
    # test_rhi_metal_frame_lifecycle (same precedent as engine_rhi_headless).
    target_compile_definitions(engine_rhi_metal PRIVATE ENGINE_RHI_TEST=1)
    # 系统框架头无法满足 -Werror -pedantic；手动引用计数（见 rhi_metal.m 头注）。
    set_source_files_properties(src/rhi/rhi_metal.m PROPERTIES
        COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-fno-objc-arc")
    target_link_libraries(engine_rhi_metal PRIVATE
        "-framework Metal" "-framework QuartzCore" "-framework Foundation")
    if(ENGINE_PLATFORM STREQUAL "macos")
        target_link_libraries(engine_rhi_metal PRIVATE "-framework Cocoa")
    endif()

    # Plan C Task 10: offline GLSL -> SPIR-V -> MSL -> metallib shader
    # pipeline. Tools are locked at configure time (HINTS cover the brew
    # prefix); a missing tool is an honest FATAL_ERROR, never a silent
    # fallback to runtime compilation.
    find_program(ENGINE_METAL_GLSLC glslc
        HINTS /opt/homebrew/bin /usr/local/bin REQUIRED)
    find_program(ENGINE_METAL_SPIRV_CROSS spirv-cross
        HINTS /opt/homebrew/bin /usr/local/bin REQUIRED)
    find_program(ENGINE_METAL_XCRUN xcrun REQUIRED)
    if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
        set(METAL_SHADER_SDK iphoneos)
    else()
        set(METAL_SHADER_SDK macosx)
    endif()
    add_executable(gen_metal_shader_manifest
        tools/gen_metal_shader_manifest.c)
    target_include_directories(gen_metal_shader_manifest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)

    # M6 handoff (Task 14): the generator above targets the BUILD
    # platform, so an iOS cross-compile cannot run it on the macOS host.
    # Cross-compiling (iOS): host-compile a copy with the system
    # compiler at configure time and use it in the custom command.
    # Native (macOS): use the target as before.
    if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
        set(METAL_SHADER_GEN
            ${CMAKE_CURRENT_BINARY_DIR}/gen_metal_shader_manifest_host)
        execute_process(
            COMMAND cc -O1 -std=c11
                -I${CMAKE_CURRENT_SOURCE_DIR}/src
                -I${CMAKE_CURRENT_SOURCE_DIR}/external
                ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_metal_shader_manifest.c
                -o ${METAL_SHADER_GEN}
            RESULT_VARIABLE metal_gen_host_rc)
        if(NOT metal_gen_host_rc EQUAL 0)
            message(FATAL_ERROR "host gen_metal_shader_manifest build failed")
        endif()
    else()
        set(METAL_SHADER_GEN gen_metal_shader_manifest)
    endif()
    set(METAL_SHADER_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/metal_shaders)
    file(GLOB METAL_SHADER_INPUTS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*_vk.vert
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*_vk.frag
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/particle.vert
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/particle.frag
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/depth_only.vert
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/depth_only.frag
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.comp)
    get_filename_component(ENGINE_METAL_GLSLC_DIR
        ${ENGINE_METAL_GLSLC} DIRECTORY)
    get_filename_component(ENGINE_METAL_SPIRV_CROSS_DIR
        ${ENGINE_METAL_SPIRV_CROSS} DIRECTORY)
    # xcode-select points at CommandLineTools on this host; xcrun metal
    # needs DEVELOPER_DIR=<Xcode>. Bake the configure-time value, falling
    # back to the standard Xcode path.
    if(NOT DEFINED ENGINE_METAL_DEVELOPER_DIR)
        set(ENGINE_METAL_DEVELOPER_DIR "$ENV{DEVELOPER_DIR}")
    endif()
    if(ENGINE_METAL_DEVELOPER_DIR STREQUAL "")
        set(ENGINE_METAL_DEVELOPER_DIR
            "/Applications/Xcode.app/Contents/Developer")
    endif()
    add_custom_command(
        OUTPUT ${METAL_SHADER_OUT_DIR}/engine.metallib
               ${METAL_SHADER_OUT_DIR}/rhi_metal_shader_manifest.c
        COMMAND ${CMAKE_COMMAND} -E env
            "PATH=${ENGINE_METAL_GLSLC_DIR}:${ENGINE_METAL_SPIRV_CROSS_DIR}:$ENV{PATH}"
            "DEVELOPER_DIR=${ENGINE_METAL_DEVELOPER_DIR}"
            sh ${CMAKE_CURRENT_SOURCE_DIR}/tools/compile_metal_shaders.sh
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${METAL_SHADER_OUT_DIR}
            ${METAL_SHADER_SDK}
        COMMAND ${METAL_SHADER_GEN}
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${METAL_SHADER_OUT_DIR}
            ${METAL_SHADER_OUT_DIR}/msl
            ${METAL_SHADER_OUT_DIR}/manifest.lines
            ${METAL_SHADER_OUT_DIR}/rhi_metal_shader_manifest.c
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tools/compile_metal_shaders.sh
            ${CMAKE_CURRENT_SOURCE_DIR}/tools/gen_metal_shader_manifest.c
            ${METAL_SHADER_INPUTS}
        COMMENT "GLSL -> SPIR-V -> MSL -> engine.metallib + manifest"
        VERBATIM)
    add_custom_target(engine_metal_shaders DEPENDS
        ${METAL_SHADER_OUT_DIR}/engine.metallib
        ${METAL_SHADER_OUT_DIR}/rhi_metal_shader_manifest.c)
    add_dependencies(engine_rhi_metal engine_metal_shaders)
    target_sources(engine_rhi_metal PRIVATE
        ${METAL_SHADER_OUT_DIR}/rhi_metal_shader_manifest.c)
endif()

if(ENGINE_VULKAN OR (ENGINE_PLATFORM STREQUAL "macos" AND
   NOT ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal"))
    add_library(engine_rhi_vulkan STATIC EXCLUDE_FROM_ALL src/rhi/rhi_vk.c)
    target_include_directories(engine_rhi_vulkan PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)
    if(SHADERC_INCLUDE_DIR)
        target_include_directories(engine_rhi_vulkan PRIVATE ${SHADERC_INCLUDE_DIR})
    endif()
    target_compile_definitions(engine_rhi_vulkan PRIVATE ENGINE_VULKAN=1)
    target_link_libraries(engine_rhi_vulkan PUBLIC engine
        PRIVATE Vulkan::Vulkan ${SHADERC_LIB})
endif()

# Native D3D12 backend (plan D): Windows-only static library with real
# device/queue/fence init (Task 3). Not EXCLUDE_FROM_ALL — the library
# only exists when d3d12 is the effective backend.
if(WIN32 AND ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "d3d12")
    add_library(engine_rhi_d3d12 STATIC src/rhi/rhi_d3d12.c)
    target_include_directories(engine_rhi_d3d12 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_compile_definitions(engine_rhi_d3d12 PRIVATE ENGINE_RHI_BACKEND_D3D12=1)
    target_link_libraries(engine_rhi_d3d12 PUBLIC engine PRIVATE d3d12 dxgi dxguid)
    if(ENGINE_D3D12_DEBUG)
        target_compile_definitions(engine_rhi_d3d12 PRIVATE ENGINE_D3D12_DEBUG=1)
    endif()
    # Task 8: deploy the locked Agility SDK runtime next to every d3d12
    # executable. D3D12SDKPath=".\" (rhi_d3d12.c) makes d3d12.dll bind
    # D3D12Core.dll from the executable directory, and the debug layer
    # (ENGINE_D3D12_DEBUG) additionally needs d3d12SDKLayers.dll from the
    # same pinned package. Executables (tests included) land in
    # ${CMAKE_BINARY_DIR}, so a single copy covers all consumers.
    set(ENGINE_D3D12_AGILITY_BIN
        "${CMAKE_CURRENT_SOURCE_DIR}/external/d3d12/agility/build/native/bin/x64")
    foreach(_d3d12_redist D3D12Core.dll d3d12SDKLayers.dll)
        if(NOT EXISTS "${ENGINE_D3D12_AGILITY_BIN}/${_d3d12_redist}")
            message(FATAL_ERROR
                "${_d3d12_redist} missing; run cmake -P engine/tools/fetch_d3d12_agility_sdk.cmake")
        endif()
    endforeach()
    add_custom_command(TARGET engine_rhi_d3d12 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ENGINE_D3D12_AGILITY_BIN}/D3D12Core.dll" "${CMAKE_BINARY_DIR}/D3D12Core.dll"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ENGINE_D3D12_AGILITY_BIN}/d3d12SDKLayers.dll" "${CMAKE_BINARY_DIR}/d3d12SDKLayers.dll")
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        # Same Windows-SDK-header exemption set as the legacy test registration.
        if(CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
            set(_d3d12_sdk_quiet "/clang:-Wno-nonportable-include-path;/clang:-Wno-ignored-pragma-intrinsic;/clang:-Wno-pragma-pack;/clang:-Wno-unknown-pragmas;/clang:-Wno-microsoft-anon-tag")
        else()
            # clang in GNU mode does not accept /clang: pass-through options.
            set(_d3d12_sdk_quiet "-Wno-nonportable-include-path;-Wno-ignored-pragma-intrinsic;-Wno-pragma-pack;-Wno-unknown-pragmas;-Wno-microsoft-anon-tag")
        endif()
        set_source_files_properties(src/rhi/rhi_d3d12.c PROPERTIES
            COMPILE_OPTIONS "${_d3d12_sdk_quiet}")
    endif()

    # Task 6: build-time HLSL -> DXIL compilation with the vendored dxc
    # (Task 1 lock; same vendored-first lookup as
    # tests/test_d3d12_shader_compile_gate.cmake). Decision record: HLSL
    # sources are HAND-AUTHORED sidecars next to the GLSL pipelines
    # (shaders/*_hlsl.{vert,frag,comp}), not GLSL translations. The D3D12
    # renderer pipeline list below is asserted against the sidecars — a
    # referenced pipeline without its *_hlsl.* twin fails the build with an
    # explicit list (no silent skip); pipelines are migrated incrementally.
    set(ENGINE_DXC "${CMAKE_CURRENT_SOURCE_DIR}/external/VulkanSDK/Bin/dxc.exe")
    if(NOT EXISTS "${ENGINE_DXC}")
        # find_program is a no-op when the output variable is already set to a
        # non-NOTFOUND value; clear the vendored default first or the search
        # silently keeps a nonexistent path (CI: vendored dxc is local-only).
        unset(ENGINE_DXC)
        find_program(ENGINE_DXC NAMES dxc dxc.exe REQUIRED)
    endif()
    set(ENGINE_D3D12_HLSL_PIPELINES blit myui)
    set(_d3d12_missing_sidecars "")
    foreach(_pipe IN LISTS ENGINE_D3D12_HLSL_PIPELINES)
        foreach(_stage vert frag)
            if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/${_pipe}_hlsl.${_stage}")
                string(APPEND _d3d12_missing_sidecars
                    "\n  shaders/${_pipe}_hlsl.${_stage} (renderer pipeline '${_pipe}')")
            endif()
        endforeach()
    endforeach()
    if(_d3d12_missing_sidecars)
        message(FATAL_ERROR
            "D3D12 HLSL sidecar assertion failed — every renderer-referenced pipeline must have a hand-authored *_hlsl.* twin (no silent skip):${_d3d12_missing_sidecars}")
    endif()
    file(GLOB ENGINE_D3D12_HLSL CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*_hlsl.vert
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*_hlsl.frag
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*_hlsl.comp)
    set(ENGINE_D3D12_DXIL "")
    foreach(_hlsl IN LISTS ENGINE_D3D12_HLSL)
        get_filename_component(_name "${_hlsl}" NAME)
        if(_hlsl MATCHES "\\.vert$")
            set(_profile vs_6_0)
        elseif(_hlsl MATCHES "\\.frag$")
            set(_profile ps_6_0)
        else()
            set(_profile cs_6_0)
        endif()
        set(_dxil "${CMAKE_CURRENT_BINARY_DIR}/shaders_d3d12/${_name}.dxil")
        add_custom_command(
            OUTPUT "${_dxil}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/shaders_d3d12"
            COMMAND "${ENGINE_DXC}" -T ${_profile} -E main -Fo "${_dxil}" "${_hlsl}"
            DEPENDS "${_hlsl}"
            COMMENT "dxc ${_profile}: ${_name}")
        list(APPEND ENGINE_D3D12_DXIL "${_dxil}")
    endforeach()
    add_custom_target(engine_shaders_d3d12 ALL DEPENDS ${ENGINE_D3D12_DXIL})
    add_dependencies(engine_rhi_d3d12 engine_shaders_d3d12)
    # Runtime lookup: HLSL source (text reflection + uniform markers) from
    # the source tree, precompiled DXIL from the build tree. A missing DXIL
    # (precompile skipped/failed) makes rhi_shader_create refuse the shader.
    target_compile_definitions(engine_rhi_d3d12 PRIVATE
        RHI_D3D12_SHADER_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        RHI_D3D12_SHADER_DXIL_DIR="${CMAKE_CURRENT_BINARY_DIR}/shaders_d3d12")
endif()

# Link exactly one RHI backend into a consumer executable. Headless
# contract tests do NOT call this helper; they link engine_rhi_headless.
function(engine_link_rhi_backend target)
    if(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")
        target_link_libraries(${target} PRIVATE engine_rhi_metal)
        if(APPLE)
            # Task 10: engine.metallib must sit beside the executable
            # (rhi_device_create loads it relative to the main bundle).
            add_dependencies(${target} engine_metal_shaders)
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${METAL_SHADER_OUT_DIR}/engine.metallib
                    $<TARGET_FILE_DIR:${target}>/engine.metallib)
        endif()
    elseif(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "d3d12")
        target_link_libraries(${target} PRIVATE engine_rhi_d3d12)
    elseif(ENGINE_PLATFORM STREQUAL "macos" OR
       ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "vulkan")
        target_link_libraries(${target} PRIVATE engine_rhi_vulkan)
    elseif(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "opengl")
        target_link_libraries(${target} PRIVATE engine_rhi_opengl)
    else()
        message(FATAL_ERROR
            "engine_link_rhi_backend: no backend library for ENGINE_RHI_BACKEND_EFFECTIVE=${ENGINE_RHI_BACKEND_EFFECTIVE}")
    endif()
endfunction()

# Vendored Lua 5.4 (external/lua). Built as a single translation unit via
# onelua.c with MAKE_LIB; third-party code so warnings are silenced (it cannot
# satisfy the engine's -Werror -pedantic).
add_library(lua STATIC external/lua/onelua.c)
target_compile_definitions(lua PRIVATE MAKE_LIB)
if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    # iOS has no system(); loslib.c gates it behind LUA_USE_IOS.
    target_compile_definitions(lua PRIVATE LUA_USE_IOS)
endif()
target_include_directories(lua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)
if(MSVC)
    target_compile_options(lua PRIVATE /w)
else()
    target_compile_options(lua PRIVATE -w)
endif()

# Vendored stb single-header implementations are shared by the engine asset
# pipeline, myui's font/image backends, and the dxx application.
add_library(stb_truetype STATIC external/stb_truetype_impl.c)
target_include_directories(stb_truetype PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)
if(NOT WIN32)
    target_link_libraries(stb_truetype PUBLIC m)
endif()

add_library(stb_image STATIC external/stb_image_impl.c)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)

add_library(stb_image_write STATIC external/stb_image_write_impl.c)
target_include_directories(stb_image_write PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)

foreach(stb_target stb_truetype stb_image stb_image_write)
    if(MSVC)
        target_compile_options(${stb_target} PRIVATE /w)
    else()
        target_compile_options(${stb_target} PRIVATE -w)
    endif()
endforeach()

target_link_libraries(engine PRIVATE glad lua stb_image)

set(MYUI_CORE_SOURCES
    src/myui/myc/my_mem.c
    src/myui/myc/my_darray.c
    src/myui/myc/my_str.c
    src/myui/myc/my_emitter.c
    src/myui/myc/my_value.c
    src/myui/myc/my_object.c
    src/myui/myc/myconf/my_conf.c
    src/myui/myc/myconf/my_conf_json.c
    src/myui/myc/myconf/my_conf_bson.c
    src/myui/myc/myconf/my_conf_toml.c
    src/myui/myc/myconf/my_conf_yaml.c
    src/myui/myr/my_dirty_rects.c
    src/myui/myr/my_ui_metrics.c
    src/myui/myr/my_lcd_mem.c
    src/myui/myr/my_vgcanvas_quality_transaction.c
    src/myui/myr/my_vgcanvas_soft.c
    src/myui/myr/my_vgcanvas_gles2.c
    src/myui/myr/my_vgcanvas_vulkan.c
    src/myui/myr/my_vggeometry.c
    src/myui/myr/my_gl_real.c
    src/myui/myr/my_gl_desktop.c
    src/myui/myr/my_font.c
    src/myui/myr/my_font_stb.c
    src/myui/myr/my_font_ft.c
    src/myui/myr/my_bezier.c
    src/myui/myr/my_arabic_shape.c
    src/myui/myr/my_text_layout.c
    src/myui/myr/my_grapheme.c
    src/myui/myr/my_word_break.c
    src/myui/myr/my_text_paragraph.c
    src/myui/myr/my_line_break.c
    src/myui/myr/my_syntax.c
    src/myui/mypal/my_timer.c
    src/myui/mypal/my_event.c
    src/myui/mypal/my_pal_media.c
    src/myui/mypal/my_pal_vulkan.c
    src/myui/myui/my_widget.c
    src/myui/myui/my_layout.c
    src/myui/myui/my_event_dispatch.c
    src/myui/myui/my_ui_command.c
    src/myui/myui/my_style.c
    src/myui/myui/my_theme.c
    src/myui/myui/my_animator.c
    src/myui/myui/my_window.c
    src/myui/myui/my_window_manager.c
    src/myui/myui/my_undo_stack.c
    src/myui/myui/my_undo_manager.c
    src/myui/myui/my_ui_loader.c
    src/myui/myui/my_widget_class.c
    src/myui/myui/my_widget_class_builtin.c
    src/myui/myui/my_image_loader.c
    src/myui/myui/widgets/my_button.c
    src/myui/myui/widgets/my_label.c
    src/myui/myui/widgets/my_edit.c
    src/myui/myui/widgets/my_checkbox.c
    src/myui/myui/widgets/my_slider.c
  src/myui/myui/widgets/my_progress_bar.c
  src/myui/myui/widgets/my_chart.c
  src/myui/myui/widgets/my_chart_group.c
  src/myui/myui/widgets/my_list_view.c
    src/myui/myui/widgets/my_image.c
    src/myui/myui/widgets/my_text_area.c
    src/myui/myui/widgets/my_scroll_bar.c
    src/myui/myui/widgets/my_dialog.c
    src/myui/myui/widgets/my_menu.c
    src/myui/myui/widgets/my_rich_label.c
    src/myui/myui/widgets/my_scroll_view.c
    src/myui/myui/widgets/my_node.c
    src/myui/myui/widgets/my_node_view.c
    src/myui/myui/my_css.c
    src/myui/myui/echarts/my_echart_event.c
     src/myui/myui/echarts/my_echart_option.c
     src/myui/myui/echarts/my_echart_option_json.c
    src/myui/myui/echarts/my_echart_adapter.c
    src/myui/myui/echarts/my_echart.c
    src/myui/myui/echarts/my_echart_animation.c
    src/myui/mymvvm/my_view_model.c
    src/myui/mymvvm/my_view_model_array.c
    src/myui/mymvvm/my_value_converter.c
    src/myui/mymvvm/my_value_validator.c
    src/myui/mymvvm/my_binding_rule.c
    src/myui/mymvvm/my_binding_context.c
    src/myui/mymvvm/my_data_binding.c
    src/myui/mymvvm/my_command_binding.c
    src/myui/mymvvm/my_items_binding.c
    src/myui/mymvvm/my_condition_binding.c
    src/myui/mymvvm/my_navigator.c
    src/myui/mymvvm_myui/my_widget_target.c
    src/myui/mymvvm_myui/my_mvvm.c
)

if(MYUI_BIDI)
    list(APPEND MYUI_CORE_SOURCES external/SheenBidi/Source/SheenBidi.c)
endif()

# MYUI_PAL x11 engine integration: compile the PAL dispatcher and the
# real port into myui_core so in-tree consumers (myui_explorer) can use
# my_pal_create() with a live desktop port.
if(MYUI_PAL STREQUAL "x11")
    list(APPEND MYUI_CORE_SOURCES src/myui/mypal/my_pal.c
        src/myui/mypal/dummy/my_pal_dummy.c
        src/myui/mypal/x11/my_pal_x11.c)
elseif(MYUI_PAL STREQUAL "win32" AND WIN32)
    list(APPEND MYUI_CORE_SOURCES src/myui/mypal/my_pal.c
        src/myui/mypal/dummy/my_pal_dummy.c
        src/myui/mypal/win32/my_pal_win32.c)
elseif(MYUI_PAL STREQUAL "cocoa" AND APPLE)
    enable_language(OBJC)
    list(APPEND MYUI_CORE_SOURCES src/myui/mypal/my_pal.c
        src/myui/mypal/dummy/my_pal_dummy.c
        src/myui/mypal/cocoa/my_pal_cocoa.m)
elseif(MYUI_PAL STREQUAL "wayland")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ENGINE_PAL_WL REQUIRED wayland-client wayland-egl egl)
    find_program(ENGINE_WAYLAND_SCANNER wayland-scanner REQUIRED)
    find_file(ENGINE_WAYLAND_XDG_SHELL_XML xdg-shell.xml
        PATHS
            "${CMAKE_SYSROOT}/usr/share/wayland-protocols/stable/xdg-shell"
            /usr/share/wayland-protocols/stable/xdg-shell
            /usr/local/share/wayland-protocols/stable/xdg-shell
        NO_DEFAULT_PATH)
    if(NOT ENGINE_WAYLAND_XDG_SHELL_XML)
        message(FATAL_ERROR
            "Could not find xdg-shell.xml; set CMAKE_SYSROOT or install wayland-protocols")
    endif()
    execute_process(
        COMMAND ${ENGINE_WAYLAND_SCANNER} client-header
                ${ENGINE_WAYLAND_XDG_SHELL_XML}
                ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h
        RESULT_VARIABLE ENGINE_WAYLAND_HEADER_RESULT)
    if(NOT ENGINE_WAYLAND_HEADER_RESULT EQUAL 0)
        message(FATAL_ERROR "wayland-scanner client-header failed")
    endif()
    execute_process(
        COMMAND ${ENGINE_WAYLAND_SCANNER} public-code
                ${ENGINE_WAYLAND_XDG_SHELL_XML}
                ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c
        RESULT_VARIABLE ENGINE_WAYLAND_CODE_RESULT)
    if(NOT ENGINE_WAYLAND_CODE_RESULT EQUAL 0)
        message(FATAL_ERROR "wayland-scanner public-code failed")
    endif()
    list(APPEND MYUI_CORE_SOURCES src/myui/mypal/my_pal.c
        src/myui/mypal/dummy/my_pal_dummy.c
        src/myui/mypal/wayland/my_pal_wayland.c
        ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c)
endif()

add_library(myui_core STATIC ${MYUI_CORE_SOURCES})
if(MYUI_PAL STREQUAL "x11")
    target_compile_definitions(myui_core PUBLIC MYUI_PAL_X11=1)
    target_link_libraries(myui_core PUBLIC ${X11_LIBRARIES} EGL)
elseif(MYUI_PAL STREQUAL "win32" AND WIN32)
    list(APPEND MYUI_CORE_SOURCES src/myui/mypal/my_pal.c
        src/myui/mypal/dummy/my_pal_dummy.c
        src/myui/mypal/win32/my_pal_win32.c)
elseif(MYUI_PAL STREQUAL "cocoa" AND APPLE)
    enable_language(OBJC)
    list(APPEND MYUI_CORE_SOURCES src/myui/mypal/my_pal.c
        src/myui/mypal/dummy/my_pal_dummy.c
        src/myui/mypal/cocoa/my_pal_cocoa.m)
elseif(MYUI_PAL STREQUAL "wayland")
    target_compile_definitions(myui_core PUBLIC MYUI_PAL_WAYLAND=1)
    target_include_directories(myui_core PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
        ${ENGINE_PAL_WL_INCLUDE_DIRS})
    target_link_libraries(myui_core PUBLIC ${ENGINE_PAL_WL_LIBRARIES})
elseif(MYUI_PAL STREQUAL "win32" AND WIN32)
    target_compile_definitions(myui_core PUBLIC MYUI_PAL_WIN32=1)
    target_link_libraries(myui_core PUBLIC gdi32 user32 opengl32)
elseif(MYUI_PAL STREQUAL "cocoa" AND APPLE)
    target_compile_definitions(myui_core PUBLIC MYUI_PAL_COCOA=1)
    target_link_libraries(myui_core PUBLIC "-framework Cocoa"
        "-framework OpenGL")
endif()
target_include_directories(myui_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
if(MYUI_BIDI)
    target_include_directories(myui_core PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/SheenBidi/Headers
        ${CMAKE_CURRENT_SOURCE_DIR}/external/SheenBidi/Source
    )
    target_compile_definitions(myui_core PUBLIC MYUI_BIDI=1)
    if(MSVC)
        set_source_files_properties(external/SheenBidi/Source/SheenBidi.c PROPERTIES
            COMPILE_DEFINITIONS SB_CONFIG_UNITY
            COMPILE_OPTIONS "/wd4100;/wd4189")
    else()
        set_source_files_properties(external/SheenBidi/Source/SheenBidi.c PROPERTIES
            COMPILE_DEFINITIONS SB_CONFIG_UNITY
            COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-Wno-unused-function;-Wno-unused-parameter;-Wno-implicit-fallthrough;-Wno-unused-value")
    endif()
endif()

if(MYUI_FONT_STB)
    target_compile_definitions(myui_core PUBLIC MYUI_FONT_STB=1)
endif()
if(MYUI_FONT_FREETYPE)
    find_package(Freetype QUIET)
    if(Freetype_FOUND)
        set(MYUI_FREETYPE_FOUND ON)
        target_compile_definitions(myui_core PUBLIC MYUI_FONT_FREETYPE=1)
        target_link_libraries(myui_core PUBLIC Freetype::Freetype)
    else()
        message(STATUS "myui: FreeType not found; CJK TTC fonts fall back to stb/bitmap")
    endif()
endif()
if(MYUI_HARFBUZZ AND MYUI_FREETYPE_FOUND)
    # Prefer native CMake package targets so Windows/macOS builds do not
    # require pkg-config; retain pkg-config as a portable fallback.
    find_package(harfbuzz CONFIG QUIET)
    if(harfbuzz_FOUND AND TARGET harfbuzz::harfbuzz)
        target_compile_definitions(myui_core PUBLIC MYUI_FONT_HARFBUZZ=1)
        target_link_libraries(myui_core PUBLIC harfbuzz::harfbuzz)
    else()
        find_package(PkgConfig QUIET)
        if(PkgConfig_FOUND)
            pkg_check_modules(HARFBUZZ QUIET IMPORTED_TARGET harfbuzz)
        endif()
        if(HARFBUZZ_FOUND AND TARGET PkgConfig::HARFBUZZ)
            target_compile_definitions(myui_core PUBLIC MYUI_FONT_HARFBUZZ=1)
            target_link_libraries(myui_core PUBLIC PkgConfig::HARFBUZZ)
        else()
            message(STATUS "myui: HarfBuzz not found; OpenType shaping disabled")
        endif()
    endif()
endif()
if(MYUI_IMAGE_STB)
    target_compile_definitions(myui_core PUBLIC MYUI_IMAGE_STB=1)
endif()
if(MYUI_UI_YAML)
    target_compile_definitions(myui_core PUBLIC MYUI_UI_YAML=1)
endif()

# Keep the in-tree aggregate aligned with the reusable myui project. Backend
# discovery remains conditional so disabled backends add no headers or link
# dependencies to consumers.
if(MYUI_GLES2 AND ENGINE_PLATFORM STREQUAL "linux")
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(MYUI_GLESV2 QUIET IMPORTED_TARGET glesv2)
    endif()
    if(MYUI_GLESV2_FOUND AND TARGET PkgConfig::MYUI_GLESV2)
        target_compile_definitions(myui_core PUBLIC MYUI_HAS_GLES2=1)
        target_link_libraries(myui_core PUBLIC PkgConfig::MYUI_GLESV2)
    endif()
elseif(MYUI_GLES2 AND WIN32)
    # Stock Windows toolchains ship no GLES2 SDK (only GL 1.1 headers and
    # opengl32). Define the backend only when both the header and an import
    # library are actually discoverable — the same honest-discovery policy
    # as the standalone myr build; otherwise my_gl_real.c stays a stub.
    find_path(MYUI_GLES2_INCLUDE_DIR NAMES GLES2/gl2.h)
    find_library(MYUI_GLES2_LIBRARY NAMES GLESv2 opengles32)
    if(MYUI_GLES2_INCLUDE_DIR AND MYUI_GLES2_LIBRARY)
        target_compile_definitions(myui_core PUBLIC MYUI_HAS_GLES2=1)
        target_include_directories(myui_core PUBLIC ${MYUI_GLES2_INCLUDE_DIR})
        target_link_libraries(myui_core PUBLIC ${MYUI_GLES2_LIBRARY})
        message(STATUS "myui: GLES2 backend enabled (native SDK discovery)")
    else()
        message(STATUS "myui: GLES2 backend stubbed (GLES2/gl2.h not found)")
    endif()
endif()

if(MYUI_GL_DESKTOP AND ENGINE_PLATFORM STREQUAL "linux")
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(MYUI_OPENGL QUIET IMPORTED_TARGET gl)
    endif()
    if(MYUI_OPENGL_FOUND AND TARGET PkgConfig::MYUI_OPENGL)
        target_compile_definitions(myui_core PUBLIC MYUI_HAS_GL_DESKTOP=1)
        target_link_libraries(myui_core PUBLIC PkgConfig::MYUI_OPENGL)
    endif()
elseif(MYUI_GL_DESKTOP AND WIN32)
    target_compile_definitions(myui_core PUBLIC MYUI_HAS_GL_DESKTOP=1)
    target_link_libraries(myui_core PUBLIC opengl32)
endif()

set(MYUI_VULKAN_ENABLED ${MYUI_VULKAN})
if(ENGINE_VULKAN OR (ENGINE_PLATFORM STREQUAL "macos" AND
   NOT ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal"))
    set(MYUI_VULKAN_ENABLED ON)
endif()
if(MYUI_VULKAN_ENABLED)
    if(NOT TARGET Vulkan::Vulkan)
        find_package(Vulkan REQUIRED)
    endif()
    target_compile_definitions(myui_core PUBLIC MYUI_HAS_VULKAN=1)
    target_link_libraries(myui_core PUBLIC Vulkan::Vulkan)
endif()

target_link_libraries(myui_core PUBLIC
    m
    Threads::Threads
    stb_truetype
    stb_image
    stb_image_write
)

# BreakUI adapter: myui PAL + RHI vgcanvas + application-facing bridge.
add_library(break_myui STATIC
    src/myui/mypal/break/my_pal_break.c
    src/myui/myr/my_vgcanvas_break_rhi.c
    src/ui/myui_break_input.c
    src/ui/myui_break_damage.c
    src/ui/myui_break.c
    src/ui/debug_ui.c
    src/ui/imgui_stubs.c
)
target_include_directories(break_myui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
target_link_libraries(break_myui PUBLIC myui_core engine m)

# duanxianxia myui application core. The break-aware executable is added in
# apps/duanxianxia after the bridge is initialized.
add_library(dxx_core STATIC
    apps/duanxianxia/dxx_data.c
    apps/duanxianxia/dxx_theme.c
    apps/duanxianxia/dxx_app.c
    apps/duanxianxia/views/nav_item.c
    apps/duanxianxia/views/topbar.c
    apps/duanxianxia/views/index_strip.c
    apps/duanxianxia/views/footer.c
    apps/duanxianxia/views/stock_item.c
    apps/duanxianxia/views/ztpool.c
    apps/duanxianxia/views/live_panels.c
    apps/duanxianxia/views/placeholder.c
    apps/duanxianxia/views/auth.c
    apps/duanxianxia/views/qx_chart.c
    apps/duanxianxia/views/qx_stats.c
)
target_include_directories(dxx_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/apps/duanxianxia
)
target_link_libraries(dxx_core PUBLIC myui_core stb_image_write m)

# Break-aware duanxianxia demo executable.
add_executable(dxx_break apps/duanxianxia/dxx_break_main.c)
target_include_directories(dxx_break PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/apps/duanxianxia
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
target_link_libraries(dxx_break PRIVATE dxx_core break_myui engine m)
engine_link_rhi_backend(dxx_break)

if(ENGINE_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ENGINE_IPO_SUPPORTED OUTPUT ENGINE_IPO_ERROR)
    if(ENGINE_IPO_SUPPORTED)
        set_property(TARGET engine PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
    else()
        message(STATUS "IPO/LTO disabled: ${ENGINE_IPO_ERROR}")
    endif()
endif()

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

if(ENGINE_PLATFORM STREQUAL "linux")
    target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
    if(ENGINE_NET_IOURING)
        target_compile_definitions(engine PRIVATE ENGINE_NET_IOURING=1)
    endif()

    if(ENGINE_ENABLE_WAYLAND)
        # Generate xdg-shell protocol bindings
        execute_process(
            COMMAND pkg-config --variable=pkgdatadir wayland-protocols
            OUTPUT_VARIABLE WAYLAND_PROTOCOLS_DIR
            RESULT_VARIABLE WAYLAND_PROTOCOLS_PKG_CONFIG_RESULT
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        # R433: fail configure with a clear message instead of generating
        # bindings from an empty WAYLAND_PROTOCOLS_DIR.
        if(NOT WAYLAND_PROTOCOLS_PKG_CONFIG_RESULT EQUAL 0 OR NOT WAYLAND_PROTOCOLS_DIR)
            message(FATAL_ERROR
                "wayland-protocols not found via pkg-config (required for ENGINE_ENABLE_WAYLAND)")
        endif()
        set(XDG_SHELL_XML "${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml")
        set(REL_PTR_XML "${WAYLAND_PROTOCOLS_DIR}/unstable/relative-pointer/relative-pointer-unstable-v1.xml")
        set(PTR_CONSTRAINTS_XML "${WAYLAND_PROTOCOLS_DIR}/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml")
        set(TEXT_INPUT_V3_XML "${WAYLAND_PROTOCOLS_DIR}/unstable/text-input/text-input-unstable-v3.xml")
        set(CURSOR_SHAPE_V1_XML "${WAYLAND_PROTOCOLS_DIR}/staging/cursor-shape/cursor-shape-v1.xml")
        set(TABLET_V2_XML "${WAYLAND_PROTOCOLS_DIR}/unstable/tablet/tablet-unstable-v2.xml")
        # R443: xdg-output for logical position / human-readable output names.
        set(XDG_OUTPUT_XML "${WAYLAND_PROTOCOLS_DIR}/unstable/xdg-output/xdg-output-unstable-v1.xml")
        set(FRACTIONAL_SCALE_V1_XML "${WAYLAND_PROTOCOLS_DIR}/staging/fractional-scale/fractional-scale-v1.xml")
        set(VIEWPORTER_XML "${WAYLAND_PROTOCOLS_DIR}/stable/viewporter/viewporter.xml")

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

        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/text-input-unstable-v3-client-protocol.h
                   ${CMAKE_CURRENT_BINARY_DIR}/text-input-unstable-v3-protocol.c
            COMMAND ${WAYLAND_SCANNER} client-header ${TEXT_INPUT_V3_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/text-input-unstable-v3-client-protocol.h
            COMMAND ${WAYLAND_SCANNER} private-code ${TEXT_INPUT_V3_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/text-input-unstable-v3-protocol.c
            DEPENDS ${TEXT_INPUT_V3_XML}
            COMMENT "Generating text-input-unstable-v3 Wayland protocol bindings"
        )

        if(EXISTS ${CURSOR_SHAPE_V1_XML} AND EXISTS ${TABLET_V2_XML})
            add_custom_command(
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cursor-shape-v1-client-protocol.h
                       ${CMAKE_CURRENT_BINARY_DIR}/cursor-shape-v1-protocol.c
                COMMAND ${WAYLAND_SCANNER} client-header ${CURSOR_SHAPE_V1_XML}
                        ${CMAKE_CURRENT_BINARY_DIR}/cursor-shape-v1-client-protocol.h
                COMMAND ${WAYLAND_SCANNER} private-code ${CURSOR_SHAPE_V1_XML}
                        ${CMAKE_CURRENT_BINARY_DIR}/cursor-shape-v1-protocol.c
                DEPENDS ${CURSOR_SHAPE_V1_XML}
                COMMENT "Generating cursor-shape-v1 Wayland protocol bindings"
            )
            target_compile_definitions(engine PRIVATE ENGINE_WAYLAND_CURSOR_SHAPE=1)
            set(WAYLAND_CURSOR_SHAPE_PROTOCOL_SOURCE
                ${CMAKE_CURRENT_BINARY_DIR}/cursor-shape-v1-protocol.c)
            add_custom_command(
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/tablet-unstable-v2-protocol.c
                COMMAND ${WAYLAND_SCANNER} private-code ${TABLET_V2_XML}
                        ${CMAKE_CURRENT_BINARY_DIR}/tablet-unstable-v2-protocol.c
                DEPENDS ${TABLET_V2_XML}
                COMMENT "Generating tablet-unstable-v2 Wayland protocol bindings"
            )
            set(WAYLAND_TABLET_PROTOCOL_SOURCE
                ${CMAKE_CURRENT_BINARY_DIR}/tablet-unstable-v2-protocol.c)
        else()
            message(STATUS "cursor-shape-v1 unavailable; using standard Wayland cursor buffers")
        endif()

        # R443: xdg-output-unstable-v1 bindings (multi-output enumeration).
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xdg-output-unstable-v1-client-protocol.h
                   ${CMAKE_CURRENT_BINARY_DIR}/xdg-output-unstable-v1-protocol.c
            COMMAND ${WAYLAND_SCANNER} client-header ${XDG_OUTPUT_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/xdg-output-unstable-v1-client-protocol.h
            COMMAND ${WAYLAND_SCANNER} private-code ${XDG_OUTPUT_XML}
                    ${CMAKE_CURRENT_BINARY_DIR}/xdg-output-unstable-v1-protocol.c
            DEPENDS ${XDG_OUTPUT_XML}
            COMMENT "Generating xdg-output-unstable-v1 Wayland protocol bindings"
        )

        if(EXISTS ${FRACTIONAL_SCALE_V1_XML} AND EXISTS ${VIEWPORTER_XML})
            add_custom_command(
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fractional-scale-v1-client-protocol.h
                       ${CMAKE_CURRENT_BINARY_DIR}/fractional-scale-v1-protocol.c
                COMMAND ${WAYLAND_SCANNER} client-header ${FRACTIONAL_SCALE_V1_XML}
                        ${CMAKE_CURRENT_BINARY_DIR}/fractional-scale-v1-client-protocol.h
                COMMAND ${WAYLAND_SCANNER} private-code ${FRACTIONAL_SCALE_V1_XML}
                        ${CMAKE_CURRENT_BINARY_DIR}/fractional-scale-v1-protocol.c
                DEPENDS ${FRACTIONAL_SCALE_V1_XML}
                COMMENT "Generating fractional-scale-v1 Wayland protocol bindings"
            )
            add_custom_command(
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/viewporter-client-protocol.h
                       ${CMAKE_CURRENT_BINARY_DIR}/viewporter-protocol.c
                COMMAND ${WAYLAND_SCANNER} client-header ${VIEWPORTER_XML}
                        ${CMAKE_CURRENT_BINARY_DIR}/viewporter-client-protocol.h
                COMMAND ${WAYLAND_SCANNER} private-code ${VIEWPORTER_XML}
                        ${CMAKE_CURRENT_BINARY_DIR}/viewporter-protocol.c
                DEPENDS ${VIEWPORTER_XML}
                COMMENT "Generating viewporter Wayland protocol bindings"
            )
            target_compile_definitions(engine PRIVATE ENGINE_WAYLAND_FRACTIONAL_SCALE=1)
            set(WAYLAND_FRACTIONAL_SCALE_PROTOCOL_SOURCES
                ${CMAKE_CURRENT_BINARY_DIR}/fractional-scale-v1-protocol.c
                ${CMAKE_CURRENT_BINARY_DIR}/viewporter-protocol.c)
        else()
            message(STATUS "fractional-scale-v1 unavailable; using integer Wayland buffer scales")
        endif()

        target_sources(engine PRIVATE
            src/platform/window_wayland.c
            src/platform/gamepad_linux.c
            ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c
            ${CMAKE_CURRENT_BINARY_DIR}/relative-pointer-unstable-v1-protocol.c
            ${CMAKE_CURRENT_BINARY_DIR}/pointer-constraints-unstable-v1-protocol.c
            ${CMAKE_CURRENT_BINARY_DIR}/text-input-unstable-v3-protocol.c
            ${WAYLAND_CURSOR_SHAPE_PROTOCOL_SOURCE}
            ${WAYLAND_TABLET_PROTOCOL_SOURCE}
            ${CMAKE_CURRENT_BINARY_DIR}/xdg-output-unstable-v1-protocol.c
            ${WAYLAND_FRACTIONAL_SCALE_PROTOCOL_SOURCES}
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
        if(ENGINE_X11_XINPUT2)
            target_compile_definitions(engine PRIVATE ENGINE_X11_XINPUT2=1)
        endif()
    endif()

    if(ENGINE_VULKAN)
        find_package(Vulkan REQUIRED)
        target_compile_definitions(engine PUBLIC ENGINE_VULKAN=1)
        if(ENGINE_ENABLE_WAYLAND)
            target_link_libraries(engine PRIVATE ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} dl pthread)
        else()
            set(ENGINE_X11_LIBS ${X11_LIBRARIES} ${X11_Xrandr_LIB})
            if(X11_Xi_FOUND)
                list(APPEND ENGINE_X11_LIBS ${X11_Xi_LIB})
            endif()
            target_link_libraries(engine PRIVATE ${ENGINE_X11_LIBS} dl pthread)
        endif()
    else()
        if(ENGINE_ENABLE_WAYLAND)
            target_link_libraries(engine PRIVATE ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} dl pthread)
        else()
            set(ENGINE_X11_LIBS ${X11_LIBRARIES} ${X11_Xrandr_LIB})
            if(X11_Xi_FOUND)
                list(APPEND ENGINE_X11_LIBS ${X11_Xi_LIB})
            endif()
            target_link_libraries(engine PRIVATE ${ENGINE_X11_LIBS} dl pthread)
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
    endif()
    target_link_libraries(engine PRIVATE gdi32)

    target_link_libraries(engine PRIVATE user32 kernel32 shell32 imm32 advapi32)
    # XInput (gamepad) is loaded dynamically at runtime — no import lib needed.
    # Winsock2 for network module; mswsock for the IOCP net_loop backend
    target_link_libraries(engine PRIVATE ws2_32 mswsock)

elseif(ENGINE_PLATFORM STREQUAL "macos")
    # The window is a Cocoa NSWindow whose content layer is a CAMetalLayer
    # (Objective-C source), regardless of the selected RHI backend.
    enable_language(OBJC)
    if(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")
        # Native Metal backend: no MoltenVK — neither the Vulkan SDK nor
        # shaderc is required, and ENGINE_VULKAN stays off.
        target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_MACOS=1)
    else()
        # macOS reuses the Vulkan backend via MoltenVK.
        find_package(Vulkan REQUIRED)
        target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_MACOS=1 ENGINE_VULKAN=1)
    endif()
    target_sources(engine PRIVATE src/platform/window_cocoa.m)

    # Cocoa/QuartzCore headers cannot satisfy the engine's -Werror -pedantic.
    # Manual reference counting (no ARC) so Obj-C handles can live in the C
    # Platform struct without __strong qualifiers.
    set_source_files_properties(src/platform/window_cocoa.m PROPERTIES
        COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-fno-objc-arc")

    # CoreServices/CoreFoundation and libdispatch headers are system-provided
    # and can trip the engine's -Werror -pedantic policy on newer SDKs.
    set_source_files_properties(src/platform/filewatch.c PROPERTIES
        COMPILE_OPTIONS "-Wno-error;-Wno-pedantic")

    target_link_libraries(engine PRIVATE
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework IOKit"
        "-framework CoreServices"
        "-framework CoreFoundation"
    )
elseif(ENGINE_PLATFORM STREQUAL "ios" OR ENGINE_PLATFORM STREQUAL "android" OR
       ENGINE_PLATFORM STREQUAL "harmonyos")
    target_sources(engine PRIVATE src/platform/window_mobile.c)
    if(ENGINE_PLATFORM STREQUAL "ios")
        target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_IOS=1)
        # miniaudio's iOS path (MA_APPLE_MOBILE) includes AVFoundation,
        # which is Objective-C-only; compile audio.c as ObjC on iOS.
        enable_language(OBJC)
        set_source_files_properties(src/audio/audio.c PROPERTIES
            LANGUAGE OBJC
            COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-fno-objc-arc")
        target_link_libraries(engine PRIVATE
            "-framework AVFoundation" "-framework AudioToolbox"
            "-framework CoreAudio" "-framework CoreFoundation")
    elseif(ENGINE_PLATFORM STREQUAL "android")
        target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_ANDROID=1)
        if(ENGINE_ANDROID_NATIVE_WINDOW)
            target_compile_definitions(engine PUBLIC ENGINE_ANDROID_NATIVE_WINDOW=1)
            target_include_directories(engine PRIVATE ${ANDROID_NATIVE_WINDOW_INCLUDE_DIR})
        endif()
    else()
        target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_HARMONYOS=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "harmonyos")
        message(FATAL_ERROR
            "ENGINE_VULKAN on ${ENGINE_PLATFORM} requires a supplied native surface implementation; none is present")
    elseif(NOT ENGINE_VULKAN AND NOT (APPLE AND ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal"))
        message(FATAL_ERROR
            "Graphics support on ${ENGINE_PLATFORM} requires ENGINE_VULKAN=ON and a native surface host (native Metal is also accepted)")
    elseif(ENGINE_VULKAN)
        find_package(Vulkan REQUIRED)
        find_library(SHADERC_LIB NAMES shaderc_shared shaderc REQUIRED)
        target_compile_definitions(engine PUBLIC ENGINE_VULKAN=1)
        target_link_libraries(engine PRIVATE dl)
        if(ENGINE_PLATFORM STREQUAL "android")
            target_link_libraries(engine PRIVATE android)
        endif()
    endif()
endif()

# Backend-side platform libraries (moved off engine, which no longer
# compiles any backend source).
if(ENGINE_PLATFORM STREQUAL "linux")
    if(ENGINE_ENABLE_WAYLAND)
        target_link_libraries(engine_rhi_opengl PRIVATE
            ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} GL EGL dl pthread)
        if(TARGET engine_rhi_vulkan)
            target_link_libraries(engine_rhi_vulkan PRIVATE
                ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} dl pthread)
        endif()
    else()
        target_link_libraries(engine_rhi_opengl PRIVATE
            ${ENGINE_X11_LIBS} GL dl pthread)
        if(TARGET engine_rhi_vulkan)
            target_link_libraries(engine_rhi_vulkan PRIVATE
                ${ENGINE_X11_LIBS} dl pthread)
        endif()
    endif()
elseif(ENGINE_PLATFORM STREQUAL "windows")
    target_link_libraries(engine_rhi_opengl PRIVATE opengl32)
elseif(ENGINE_PLATFORM STREQUAL "macos")
    if(TARGET engine_rhi_vulkan)
        target_link_libraries(engine_rhi_vulkan PRIVATE
            "-framework Cocoa" "-framework QuartzCore" "-framework Metal"
            "-framework IOKit")
    endif()
elseif(ENGINE_PLATFORM STREQUAL "ios" OR ENGINE_PLATFORM STREQUAL "android" OR
       ENGINE_PLATFORM STREQUAL "harmonyos")
    if(TARGET engine_rhi_vulkan)
        target_link_libraries(engine_rhi_vulkan PRIVATE dl)
        if(ENGINE_PLATFORM STREQUAL "android")
            target_link_libraries(engine_rhi_vulkan PRIVATE android)
        endif()
    endif()
endif()

# Executable
add_executable(engine_demo src/main.c)
target_link_libraries(engine_demo PRIVATE engine break_myui m)
engine_link_rhi_backend(engine_demo)
# main() holds ~4.4 MB of renderer/subsystem structs as locals, sized
# against the Linux default 8 MB stack; the MSVC-family linker default
# reserve is 1 MB, which faults during the prologue stack probe on
# Windows. Match the Linux reserve (virtual only; pages commit on
# demand, zero runtime cost).
if(WIN32)
    if(CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC" OR MSVC)
        target_link_options(engine_demo PRIVATE "/STACK:8388608")
    elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
        target_link_options(engine_demo PRIVATE "-Wl,/STACK:8388608")
    endif()
    # MinGW (GNU ld) is left untouched: its flag syntax differs and the
    # MinGW native/cross builds remain unverified pending validation.
endif()

if(ENGINE_BUILD_TESTS)
    # Vulkan test executable
    add_executable(test_vulkan src/test_vulkan.c tests/rhi_oracle.c)
    # R550-E: keep the VK validation gate live for the integration test in every
    # build type. rhi_vk.c is compiled into engine_rhi_vulkan, so the define
    # cannot reach the backend from here; instead it arms the explicit
    # rhi_vk_validation_set_enabled(true) call at the top of test_vulkan's main.
    target_compile_definitions(test_vulkan PRIVATE ENGINE_VK_VALIDATION=1)
    if(MSVC)
        target_compile_options(test_vulkan PRIVATE /wd4702)
    endif()
    target_link_libraries(test_vulkan PRIVATE engine m)
    engine_link_rhi_backend(test_vulkan)
endif()

add_executable(packer tools/packer.c)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(packer PRIVATE -Wno-format-truncation)
endif()
if(ENGINE_PLATFORM STREQUAL "windows")
    target_compile_definitions(packer PRIVATE _WIN32_WINNT=0x0601)
endif()

# Rule-engine core: C99-only and independent of engine graphics, UI, and Lua.
add_library(rule_engine_core STATIC
    src/rule_engine/allocator.c src/rule_engine/facts.c src/rule_engine/values.c
    src/rule_engine/parser.c src/rule_engine/ir.c src/rule_engine/ir_validate.c src/rule_engine/engine.c src/rule_engine/extensions.c
    src/rule_engine/builtins.c
    src/rule_engine/transactions.c
    src/rule_engine/tumbling_session.c src/rule_engine/memory_provider.c
     src/rule_engine/stream_correlation.c src/rule_engine/stream_analytics.c src/rule_engine/stream_join.c src/rule_engine/ir_eval.c
     src/rule_engine/stream_eval.c
     src/rule_engine/tms.c
    src/rule_engine/rete.c src/rule_engine/advanced.c src/rule_engine/backward.c
     src/rule_engine/backward_machine.c
      src/rule_engine/backward_machine_context.c
      src/rule_engine/backward_machine_bind.c
       src/rule_engine/backward_machine_goal.c src/rule_engine/query.c
     src/rule_engine/proof_graph.c
     src/rule_engine/query_exec.c
    src/rule_engine/executor.c src/rule_engine/templates.c src/rule_engine/agenda.c)
set_property(TARGET rule_engine_core PROPERTY C_STANDARD 99)
target_include_directories(rule_engine_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
if(NOT MSVC)
    target_link_libraries(rule_engine_core PUBLIC m)
endif()
if(RULE_ENGINE_ENABLE_REDIS)
    set(_rule_engine_hiredis_source_dir "")
    set(_rule_engine_hiredis_target "")
    if(RULE_ENGINE_REDIS_SOURCE_DIR)
        if(EXISTS "${RULE_ENGINE_REDIS_SOURCE_DIR}/deps/hiredis/hiredis.h")
            set(_rule_engine_hiredis_source_dir "${RULE_ENGINE_REDIS_SOURCE_DIR}/deps/hiredis")
        elseif(EXISTS "${RULE_ENGINE_REDIS_SOURCE_DIR}/hiredis.h")
            set(_rule_engine_hiredis_source_dir "${RULE_ENGINE_REDIS_SOURCE_DIR}")
        else()
            message(FATAL_ERROR
                "RULE_ENGINE_REDIS_SOURCE_DIR must be a Redis source tree or hiredis source directory")
        endif()
        add_library(rule_engine_hiredis STATIC
            ${_rule_engine_hiredis_source_dir}/alloc.c
            ${_rule_engine_hiredis_source_dir}/async.c
            ${_rule_engine_hiredis_source_dir}/hiredis.c
            ${_rule_engine_hiredis_source_dir}/net.c
            ${_rule_engine_hiredis_source_dir}/read.c
            ${_rule_engine_hiredis_source_dir}/sds.c
            ${_rule_engine_hiredis_source_dir}/sockcompat.c)
        set_property(TARGET rule_engine_hiredis PROPERTY C_STANDARD 99)
        target_include_directories(rule_engine_hiredis PUBLIC
            ${_rule_engine_hiredis_source_dir}/..
            ${_rule_engine_hiredis_source_dir})
        if(WIN32)
            target_link_libraries(rule_engine_hiredis PUBLIC ws2_32 crypt32)
        endif()
        set(_rule_engine_hiredis_target rule_engine_hiredis)
        message(STATUS "Redis source detected at ${_rule_engine_hiredis_source_dir}; building bundled hiredis")
    else()
        find_path(HIREDIS_INCLUDE_DIR hiredis/hiredis.h)
        find_library(HIREDIS_LIBRARY NAMES hiredis)
    endif()
    if(_rule_engine_hiredis_target OR (HIREDIS_INCLUDE_DIR AND HIREDIS_LIBRARY))
        set(RULE_ENGINE_HAS_HIREDIS ON)
        target_sources(rule_engine_core PRIVATE src/rule_engine/redis_provider.c)
        target_compile_definitions(rule_engine_core PRIVATE RE_HAS_HIREDIS)
        if(_rule_engine_hiredis_target)
            target_include_directories(rule_engine_core PRIVATE ${_rule_engine_hiredis_source_dir}/..)
            target_link_libraries(rule_engine_core PRIVATE ${_rule_engine_hiredis_target})
        else()
            target_include_directories(rule_engine_core PRIVATE ${HIREDIS_INCLUDE_DIR})
            target_link_libraries(rule_engine_core PRIVATE ${HIREDIS_LIBRARY})
        endif()
        if(WIN32)
            # hiredis's socket calls need Winsock2 on the link line. PRIVATE on
            # the static rule_engine_core still propagates to its consumers
            # (e.g. test_rule_engine_stream_ext) via the link-only interface.
            target_link_libraries(rule_engine_core PRIVATE ws2_32)
        endif()
        if(_rule_engine_hiredis_target)
            message(STATUS "Redis client enabled from ${_rule_engine_hiredis_source_dir}")
        else()
            message(STATUS "Redis client detected at ${HIREDIS_INCLUDE_DIR}; native Redis state provider enabled")
        endif()
    else()
        # Documented boundary: a missing client disables the option; there is
        # no silent fallback to another provider.
        message(STATUS "RULE_ENGINE_ENABLE_REDIS requested but hiredis not found - option disabled (no fallback)")
        set(RULE_ENGINE_ENABLE_REDIS OFF CACHE BOOL
            "Enable native Redis state provider (requires hiredis and a controlled integration service)" FORCE)
    endif()
endif()
if(RULE_ENGINE_ENABLE_C11_PARALLEL)
    include(CheckIncludeFile)
    check_include_file(threads.h RULE_ENGINE_HAS_THREADS_H)
    if(NOT RULE_ENGINE_HAS_THREADS_H)
        message(FATAL_ERROR "RULE_ENGINE_ENABLE_C11_PARALLEL requires C11 <threads.h>")
    endif()
    set_source_files_properties(src/rule_engine/executor.c PROPERTIES C_STANDARD 11)
    if(MSVC)
        set_source_files_properties(src/rule_engine/executor.c PROPERTIES COMPILE_OPTIONS "/std:c11")
    endif()
    target_compile_definitions(rule_engine_core PRIVATE RE_ENABLE_C11_PARALLEL=1)
endif()

# Rule-engine baseline benchmark. Timing-sensitive by design; build and run it
# manually rather than registering it as a CTest test.
add_executable(rule_engine_bench tools/rule_engine_bench.c)
set_property(TARGET rule_engine_bench PROPERTY C_STANDARD 99)
target_link_libraries(rule_engine_bench PRIVATE rule_engine_core)

# Compile-only public ABI consumer; no graphics or Lua dependency.
add_library(rule_engine_c99_consumer OBJECT tests/rule_engine_c99_consumer.c)
set_property(TARGET rule_engine_c99_consumer PROPERTY C_STANDARD 99)
target_include_directories(rule_engine_c99_consumer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Verification tool: mounts a .pak via VFS and compares against source files
add_executable(verify_pak tools/verify_pak.c src/asset/vfs.c src/core/log.c)
target_include_directories(verify_pak PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
if(ENGINE_PLATFORM STREQUAL "windows")
    target_compile_definitions(verify_pak PRIVATE _WIN32_WINNT=0x0601)
endif()

# Strict, allocation-free verifier for Unicode LineBreakTest-compatible files.
add_executable(verify_myui_line_break tools/verify_myui_line_break.c)
target_include_directories(verify_myui_line_break PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
)
target_link_libraries(verify_myui_line_break PRIVATE myui_core)

# Headless ECharts feature demo: renders every supported feature to PPM.
add_executable(echarts_demo tools/echarts_demo.c
    src/myui/myui/echarts/my_echart_mvvm.c)
target_include_directories(echarts_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
)
target_link_libraries(echarts_demo PRIVATE myui_core m Threads::Threads)
add_test(NAME echarts_demo_smoke COMMAND echarts_demo ${CMAKE_CURRENT_BINARY_DIR})

# Headless core-widget demo: buttons, labels, inputs, sliders, and more.
add_executable(myui_widgets_demo tools/myui_widgets_demo.c)
target_include_directories(myui_widgets_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
)
target_link_libraries(myui_widgets_demo PRIVATE myui_core m Threads::Threads)
add_test(NAME myui_widgets_demo_smoke COMMAND myui_widgets_demo ${CMAKE_CURRENT_BINARY_DIR})

# Interactive explorer: live chart driven by real widgets with switchable
# backends (software / GL) and window systems (X11 / Wayland), plus a
# headless --selftest mode that renders a scripted interaction sequence.
if(NOT WIN32 AND NOT APPLE)
find_program(WAYLAND_SCANNER wayland-scanner)
find_package(PkgConfig QUIET)
# The explorer always offers the X11 runner on Linux-class hosts; the
# engine only searches X11 itself in its x11 platform branch, so look
# here too (ENGINE_ENABLE_WAYLAND=ON leaves X11_LIBRARIES unset).
find_package(X11 QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(EX_WAYLAND QUIET wayland-client wayland-egl egl glesv2)
endif()
endif()
if(NOT WIN32 AND NOT APPLE AND WAYLAND_SCANNER AND EX_WAYLAND_FOUND)
  set(EX_EXPLORER_PLATFORMS "x11+wayland, soft+gl")
  execute_process(
      COMMAND ${WAYLAND_SCANNER} client-header
              /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml
              ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h)
  execute_process(
      COMMAND ${WAYLAND_SCANNER} public-code
              /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml
              ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c)
  set(EX_EXPLORER_SOURCES tools/myui_explorer.c
      ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c)
  set(EX_EXPLORER_DEFS "")
  set(EX_EXPLORER_LIBS ${EX_WAYLAND_LIBRARIES} ${X11_LIBRARIES})
  set(EX_EXPLORER_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
      ${CMAKE_CURRENT_BINARY_DIR} ${EX_WAYLAND_INCLUDE_DIRS}
      ${X11_INCLUDE_DIR})
else()
  set(EX_EXPLORER_PLATFORMS "x11 only, soft only (wayland/EGL dev pkgs missing)")
  set(EX_EXPLORER_SOURCES tools/myui_explorer.c)
  set(EX_EXPLORER_DEFS EX_EXPLORER_NO_WAYLAND=1)
  set(EX_EXPLORER_LIBS ${X11_LIBRARIES})
  set(EX_EXPLORER_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
      ${X11_INCLUDE_DIR})
endif()
if(NOT WIN32 AND NOT APPLE AND NOT X11_FOUND)
  # Headless-only explorer: selftest/--shot still work, the interactive
  # runners report "not supported in this build".
  list(APPEND EX_EXPLORER_DEFS EX_EXPLORER_NO_X11=1)
endif()
if(WIN32)
  list(APPEND EX_EXPLORER_SOURCES tools/ex_platform_win32.c)
  list(APPEND EX_EXPLORER_LIBS gdi32 user32 opengl32)
elseif(APPLE)
  list(APPEND EX_EXPLORER_SOURCES tools/ex_platform_macos.m)
  list(APPEND EX_EXPLORER_LIBS "-framework Cocoa" "-framework OpenGL")
  # Same policy as src/platform/window_cocoa.m: Cocoa/OpenGL headers
  # (deprecated NSOpenGL included) cannot satisfy -Werror -pedantic, and
  # the file uses manual reference counting.
  set_source_files_properties(tools/ex_platform_macos.m PROPERTIES
      COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-Wno-deprecated-declarations;-fno-objc-arc")
endif()
if(NOT WIN32 AND NOT APPLE AND WAYLAND_SCANNER AND EX_WAYLAND_FOUND)
  # wayland-scanner output is generated code — exempt from -Werror
  # -pedantic like the other generated/system sources.
  set_source_files_properties(
      ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c PROPERTIES
      COMPILE_OPTIONS "-Wno-error;-Wno-pedantic")
endif()
add_executable(myui_explorer ${EX_EXPLORER_SOURCES})
target_include_directories(myui_explorer PRIVATE ${EX_EXPLORER_INCLUDES})
target_compile_definitions(myui_explorer PRIVATE ${EX_EXPLORER_DEFS})
target_link_libraries(myui_explorer PRIVATE myui_core m Threads::Threads
    ${EX_EXPLORER_LIBS})
message(STATUS "myui_explorer platforms: ${EX_EXPLORER_PLATFORMS}")
add_test(NAME myui_explorer_selftest COMMAND myui_explorer --selftest
    ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME myui_explorer_selftest_deterministic
    COMMAND ${CMAKE_COMMAND}
        -DEXPLORER=$<TARGET_FILE:myui_explorer>
        -DRUN_A=${CMAKE_CURRENT_BINARY_DIR}/explorer-det-a
        -DRUN_B=${CMAKE_CURRENT_BINARY_DIR}/explorer-det-b
        -P ${CMAKE_CURRENT_SOURCE_DIR}/tools/explorer_determinism_check.cmake)

# The demo/explorer tools are process-lifetime by design (resources held
# until OS exit); keep LeakSanitizer from reading that as a failure.
set_tests_properties(myui_widgets_demo_smoke myui_explorer_selftest
    myui_explorer_selftest_deterministic
    PROPERTIES ENVIRONMENT "ASAN_OPTIONS=detect_leaks=0")

# Strict, bounded verifier for versioned SA dictionary golden corpora.
add_executable(verify_myui_sa_dictionary tools/verify_myui_sa_dictionary.c)
target_include_directories(verify_myui_sa_dictionary PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
)
target_link_libraries(verify_myui_sa_dictionary PRIVATE myui_core)

# --- Unit Tests ---
if(ENGINE_BUILD_TESTS)
    enable_testing()

    set(TEST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)

    # Focused rule-engine ABI and behavior tests, independent of graphics/Lua.
    add_executable(test_rule_engine tests/test_rule_engine.c)
    set_property(TARGET test_rule_engine PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine PRIVATE rule_engine_core)
    if(RULE_ENGINE_ENABLE_REDIS AND RULE_ENGINE_HAS_HIREDIS)
        target_compile_definitions(test_rule_engine PRIVATE RE_HAS_HIREDIS)
    endif()
    add_test(NAME test_rule_engine COMMAND test_rule_engine)

    add_executable(test_rule_engine_transactions tests/test_rule_engine_transactions.c)
    set_property(TARGET test_rule_engine_transactions PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_transactions PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_transactions PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_transactions COMMAND test_rule_engine_transactions)

    add_executable(test_rule_engine_tms tests/test_rule_engine_tms.c)
    set_property(TARGET test_rule_engine_tms PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_tms PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_tms PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_tms COMMAND test_rule_engine_tms)

    add_executable(test_rule_engine_grl_semantics tests/test_rule_engine_grl_semantics.c)
    set_property(TARGET test_rule_engine_grl_semantics PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_grl_semantics PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_grl_semantics PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_grl_semantics COMMAND test_rule_engine_grl_semantics)

    add_executable(test_rule_engine_ir tests/test_rule_engine_ir.c)
    set_property(TARGET test_rule_engine_ir PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_ir PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_ir PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_ir COMMAND test_rule_engine_ir)

    add_executable(test_rule_engine_forall_limits tests/test_rule_engine_forall_limits.c)
    set_property(TARGET test_rule_engine_forall_limits PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_forall_limits PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_forall_limits PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_forall_limits COMMAND test_rule_engine_forall_limits)

    add_executable(test_rule_engine_rete_incremental tests/test_rule_engine_rete_incremental.c)
    set_property(TARGET test_rule_engine_rete_incremental PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_rete_incremental PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_rete_incremental PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_rete_incremental COMMAND test_rule_engine_rete_incremental)

    add_executable(test_rule_engine_agenda tests/test_rule_engine_agenda.c)
    set_property(TARGET test_rule_engine_agenda PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_agenda PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_agenda PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_agenda COMMAND test_rule_engine_agenda)

    add_executable(test_rule_engine_backward tests/test_rule_engine_backward.c)
    set_property(TARGET test_rule_engine_backward PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_backward PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_backward PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_backward COMMAND test_rule_engine_backward)

    add_executable(test_rule_engine_backward_ext tests/test_rule_engine_backward_ext.c)
    set_property(TARGET test_rule_engine_backward_ext PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_backward_ext PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_backward_ext PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_backward_ext COMMAND test_rule_engine_backward_ext)

    add_executable(test_rule_engine_grl_surface tests/test_rule_engine_grl_surface.c)
    set_property(TARGET test_rule_engine_grl_surface PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_grl_surface PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_grl_surface PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_grl_surface COMMAND test_rule_engine_grl_surface)

    add_executable(test_rule_engine_plugin_parity tests/test_rule_engine_plugin_parity.c)
    set_property(TARGET test_rule_engine_plugin_parity PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_plugin_parity PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_plugin_parity PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_plugin_parity COMMAND test_rule_engine_plugin_parity)

    add_executable(test_rule_engine_example_coverage tests/test_rule_engine_example_coverage.c)
    set_property(TARGET test_rule_engine_example_coverage PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_example_coverage PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_example_coverage PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_example_coverage COMMAND test_rule_engine_example_coverage)

    add_executable(test_rule_engine_query_blocks tests/test_rule_engine_query_blocks.c)
    set_property(TARGET test_rule_engine_query_blocks PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_query_blocks PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_query_blocks PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_query_blocks COMMAND test_rule_engine_query_blocks)

    add_executable(test_rule_engine_stream_ext tests/test_rule_engine_stream_ext.c)
    set_property(TARGET test_rule_engine_stream_ext PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_stream_ext PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_stream_ext PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_stream_ext COMMAND test_rule_engine_stream_ext)
    # Mirror the rule_engine_core condition: the test sees RE_HAS_HIREDIS
    # exactly when the native adapter was compiled into the library.
    if(RULE_ENGINE_ENABLE_REDIS AND RULE_ENGINE_HAS_HIREDIS)
        target_compile_definitions(test_rule_engine_stream_ext PRIVATE RE_HAS_HIREDIS)
    endif()

    add_executable(test_rule_engine_stream_grl tests/test_rule_engine_stream_grl.c)
    set_property(TARGET test_rule_engine_stream_grl PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_stream_grl PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_stream_grl PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_stream_grl COMMAND test_rule_engine_stream_grl)

    add_executable(test_rule_engine_stream_eval tests/test_rule_engine_stream_eval.c)
    set_property(TARGET test_rule_engine_stream_eval PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_stream_eval PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_stream_eval PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_stream_eval COMMAND test_rule_engine_stream_eval)

    add_executable(test_rule_engine_backward_deep_chain tests/test_rule_engine_backward_deep_chain.c)
    set_property(TARGET test_rule_engine_backward_deep_chain PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_backward_deep_chain PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_backward_deep_chain PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_backward_deep_chain COMMAND test_rule_engine_backward_deep_chain)

     add_executable(test_backward_machine_structure tests/test_backward_machine_structure.c)
    set_property(TARGET test_backward_machine_structure PROPERTY C_STANDARD 99)
    target_include_directories(test_backward_machine_structure PRIVATE ${TEST_INCLUDE_DIRS})
    target_compile_definitions(test_backward_machine_structure PRIVATE
        TEST_SOURCE_ROOT="${CMAKE_CURRENT_SOURCE_DIR}"
    )
    target_link_libraries(test_backward_machine_structure PRIVATE rule_engine_core)
     add_test(NAME test_backward_machine_structure COMMAND test_backward_machine_structure)

     add_executable(test_backward_machine_context tests/test_backward_machine_context.c)
     set_property(TARGET test_backward_machine_context PROPERTY C_STANDARD 99)
     target_include_directories(test_backward_machine_context PRIVATE ${TEST_INCLUDE_DIRS})
     target_link_libraries(test_backward_machine_context PRIVATE rule_engine_core)
     add_test(NAME test_backward_machine_context COMMAND test_backward_machine_context)

    add_executable(test_rule_engine_backward_bindings tests/test_rule_engine_backward_bindings.c)
    set_property(TARGET test_rule_engine_backward_bindings PROPERTY C_STANDARD 99)
    target_include_directories(test_rule_engine_backward_bindings PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_rule_engine_backward_bindings PRIVATE rule_engine_core)
    add_test(NAME test_rule_engine_backward_bindings COMMAND test_rule_engine_backward_bindings)


    add_executable(rule_engine_fuzz_smoke tests/rule_engine_fuzz_smoke.c)
    set_property(TARGET rule_engine_fuzz_smoke PROPERTY C_STANDARD 99)
    target_include_directories(rule_engine_fuzz_smoke PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(rule_engine_fuzz_smoke PRIVATE rule_engine_core)
    add_test(NAME rule_engine_fuzz_smoke COMMAND rule_engine_fuzz_smoke)
    set_tests_properties(rule_engine_fuzz_smoke PROPERTIES TIMEOUT 20 LABELS hardening)

    if(RULE_ENGINE_ENABLE_C11_PARALLEL)
        add_executable(test_rule_engine_executor_stress tests/test_rule_engine_executor_stress.c)
        set_property(TARGET test_rule_engine_executor_stress PROPERTY C_STANDARD 99)
        target_include_directories(test_rule_engine_executor_stress PRIVATE ${TEST_INCLUDE_DIRS})
        target_link_libraries(test_rule_engine_executor_stress PRIVATE rule_engine_core)
        add_test(NAME test_rule_engine_executor_stress COMMAND test_rule_engine_executor_stress)
        set_tests_properties(test_rule_engine_executor_stress PROPERTIES TIMEOUT 20 LABELS hardening)
    else()
        message(STATUS "C11 executor stress target disabled; set RULE_ENGINE_ENABLE_C11_PARALLEL=ON when <threads.h> is available")
    endif()

    # test_math: only needs math.c (vec3/quat are inline in header)
    add_executable(test_math tests/test_math.c src/math/math.c)
    target_include_directories(test_math PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_math PRIVATE m)
    add_test(NAME test_math COMMAND test_math)

    # myui integration unit tests: key mapping, shared geometry, and the
    # window-manager event bridge used by BreakUI.
    add_executable(test_break_ui_input tests/test_break_ui_input.c
        src/ui/myui_break_input.c src/platform/platform_text.c)
    target_include_directories(test_break_ui_input PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    add_test(NAME test_break_ui_input COMMAND test_break_ui_input)

    add_executable(test_platform_text tests/test_platform_text.c
        src/platform/platform_text.c)
    target_include_directories(test_platform_text PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_platform_text COMMAND test_platform_text)

    add_executable(test_platform_config tests/test_platform_config.c
        src/platform/platform_config.c)
    target_include_directories(test_platform_config PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_platform_config COMMAND test_platform_config)

    foreach(_mobile_name IN ITEMS IOS ANDROID HARMONYOS)
        string(TOLOWER "${_mobile_name}" _mobile_lower)
        add_executable(test_platform_mobile_layer_${_mobile_lower}
            tests/test_platform_mobile.c
            src/platform/window_mobile.c
            src/platform/input.c
            src/platform/platform_config.c)
        target_include_directories(test_platform_mobile_layer_${_mobile_lower}
            PRIVATE ${TEST_INCLUDE_DIRS})
        target_compile_definitions(test_platform_mobile_layer_${_mobile_lower}
            PRIVATE ENGINE_PLATFORM_${_mobile_name}=1)
        add_test(NAME test_platform_mobile_layer_${_mobile_lower}
            COMMAND test_platform_mobile_layer_${_mobile_lower})
    endforeach()

    add_executable(test_platform_display_media tests/test_platform_display_media.c
        src/platform/platform_display_media.c)
    target_include_directories(test_platform_display_media PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_platform_display_media COMMAND test_platform_display_media)

    add_executable(test_engine_lifecycle tests/test_engine_lifecycle.c)
    target_include_directories(test_engine_lifecycle PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_engine_lifecycle PRIVATE engine m)
    engine_link_rhi_backend(test_engine_lifecycle)
    add_test(NAME test_engine_lifecycle COMMAND test_engine_lifecycle)

    add_executable(test_platform_null_safety tests/test_platform_null_safety.c)
    target_include_directories(test_platform_null_safety PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_platform_null_safety PRIVATE engine m)
    engine_link_rhi_backend(test_platform_null_safety)
    add_test(NAME test_platform_null_safety COMMAND test_platform_null_safety)

    # Header-only WSI lifecycle contract; intentionally headless and engine-free.
    add_executable(test_platform_wsi_lifecycle tests/test_platform_wsi_lifecycle.c)
    target_include_directories(test_platform_wsi_lifecycle PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_platform_wsi_lifecycle COMMAND test_platform_wsi_lifecycle)
    set_tests_properties(test_platform_wsi_lifecycle PROPERTIES
        LABELS "headless;platform_contract")

    # Header-only Vulkan probe/negotiation pure functions (rhi_vk_probe.h);
    # intentionally headless and engine-free.
    add_executable(test_rhi_vk_probe tests/test_rhi_vk_probe.c)
    target_include_directories(test_rhi_vk_probe PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_rhi_vk_probe COMMAND test_rhi_vk_probe)
    set_tests_properties(test_rhi_vk_probe PROPERTIES
        LABELS "headless;platform_contract")

    if(ENGINE_PLATFORM STREQUAL "linux" AND NOT ENGINE_ENABLE_WAYLAND)
        add_executable(test_platform_x11_runtime tests/test_platform_x11_runtime.c)
        target_include_directories(test_platform_x11_runtime PRIVATE ${TEST_INCLUDE_DIRS})
        if(ENGINE_X11_XINPUT2)
            target_compile_definitions(test_platform_x11_runtime PRIVATE ENGINE_X11_XINPUT2=1)
        endif()
        target_link_libraries(test_platform_x11_runtime PRIVATE engine m)
        engine_link_rhi_backend(test_platform_x11_runtime)
        add_test(NAME test_platform_x11_runtime COMMAND test_platform_x11_runtime)
        set_tests_properties(test_platform_x11_runtime PROPERTIES
            LABELS "graphics;platform_runtime" SKIP_RETURN_CODE 77)
        if(NOT ENGINE_VULKAN)
            add_executable(test_rhi_x11_runtime tests/test_rhi_x11_runtime.c)
            target_include_directories(test_rhi_x11_runtime PRIVATE ${TEST_INCLUDE_DIRS})
            target_link_libraries(test_rhi_x11_runtime PRIVATE engine m)
            engine_link_rhi_backend(test_rhi_x11_runtime)
            add_test(NAME test_rhi_x11_runtime COMMAND test_rhi_x11_runtime)
            set_tests_properties(test_rhi_x11_runtime PROPERTIES
                LABELS "graphics;platform_runtime" SKIP_RETURN_CODE 77)
        endif()
    endif()

    if(ENGINE_PLATFORM STREQUAL "linux" AND ENGINE_ENABLE_WAYLAND)
        add_executable(test_platform_wayland_runtime tests/test_platform_wayland_runtime.c)
        target_include_directories(test_platform_wayland_runtime PRIVATE
            ${TEST_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS})
        target_link_libraries(test_platform_wayland_runtime PRIVATE engine m
            ${WAYLAND_LIBRARIES})
        engine_link_rhi_backend(test_platform_wayland_runtime)
        add_test(NAME test_platform_wayland_runtime
            COMMAND test_platform_wayland_runtime)
        set_tests_properties(test_platform_wayland_runtime PROPERTIES
            LABELS platform_runtime SKIP_RETURN_CODE 77)
    endif()

    if(ENGINE_PLATFORM STREQUAL "windows")
    add_executable(test_platform_win32_runtime tests/test_platform_win32_runtime.c)
    target_include_directories(test_platform_win32_runtime PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_platform_win32_runtime PRIVATE engine m)
    engine_link_rhi_backend(test_platform_win32_runtime)
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        target_compile_options(test_platform_win32_runtime PRIVATE
            -Wno-missing-field-initializers)
    endif()
        add_test(NAME test_platform_win32_runtime COMMAND test_platform_win32_runtime)
        set_tests_properties(test_platform_win32_runtime PROPERTIES LABELS platform_runtime)
    endif()

    if(ENGINE_PLATFORM STREQUAL "macos")
        add_executable(test_platform_cocoa_runtime tests/test_platform_cocoa_runtime.c)
        target_include_directories(test_platform_cocoa_runtime PRIVATE ${TEST_INCLUDE_DIRS})
        target_link_libraries(test_platform_cocoa_runtime PRIVATE engine m)
        engine_link_rhi_backend(test_platform_cocoa_runtime)
        add_test(NAME test_platform_cocoa_runtime COMMAND test_platform_cocoa_runtime)
        set_tests_properties(test_platform_cocoa_runtime PROPERTIES LABELS platform_runtime)
    endif()

    add_executable(test_imgui_compat tests/test_imgui_compat.c
        src/ui/imgui_stubs.c
        src/myui/myr/my_vgcanvas_break_rhi.c)
    target_include_directories(test_imgui_compat PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_imgui_compat PRIVATE myui_core engine m)
    engine_link_rhi_backend(test_imgui_compat)
    add_test(NAME test_imgui_compat COMMAND test_imgui_compat)

    add_executable(test_break_ui_damage tests/test_break_ui_damage.c
        src/ui/myui_break_damage.c
        src/myui/mypal/dummy/my_pal_dummy.c)
    target_include_directories(test_break_ui_damage PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_break_ui_damage PRIVATE myui_core m)
    add_test(NAME test_break_ui_damage COMMAND test_break_ui_damage)

    if(MYUI_PAL STREQUAL "wayland")
    add_executable(test_mypal_wayland tests/test_mypal_wayland.c)
    target_include_directories(test_mypal_wayland PRIVATE
        ${TEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_mypal_wayland PRIVATE myui_core m
        ${ENGINE_PAL_WL_LIBRARIES} Threads::Threads)
    add_test(NAME test_mypal_wayland COMMAND test_mypal_wayland)
    set_tests_properties(test_mypal_wayland PROPERTIES
        LABELS "graphics;platform_runtime" SKIP_RETURN_CODE 77)
endif()

if(MYUI_PAL STREQUAL "x11")
    add_executable(test_mypal_x11 tests/test_mypal_x11.c)
    target_include_directories(test_mypal_x11 PRIVATE
        ${TEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_mypal_x11 PRIVATE myui_core m
        ${X11_LIBRARIES} EGL Threads::Threads)
    add_test(NAME test_mypal_x11 COMMAND test_mypal_x11)
    set_tests_properties(test_mypal_x11 PROPERTIES
        LABELS "graphics;platform_runtime" SKIP_RETURN_CODE 77)
endif()

    add_executable(test_myui_vggeometry tests/test_myui_vggeometry.c)
    target_include_directories(test_myui_vggeometry PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_vggeometry PRIVATE myui_core m)
    add_test(NAME test_myui_vggeometry COMMAND test_myui_vggeometry)

    add_executable(test_myui_window_manager tests/test_myui_window_manager.c
        src/myui/mypal/dummy/my_pal_dummy.c)
    target_include_directories(test_myui_window_manager PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_window_manager PRIVATE myui_core m)
    add_test(NAME test_myui_window_manager COMMAND test_myui_window_manager)

    add_executable(test_myui_break_pal tests/test_myui_break_pal.c
        src/myui/mypal/break/my_pal_break.c
        src/myui/mypal/dummy/my_pal_dummy.c)
    target_include_directories(test_myui_break_pal PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_break_pal PRIVATE myui_core engine m
        Threads::Threads)
    engine_link_rhi_backend(test_myui_break_pal)
    add_test(NAME test_myui_break_pal COMMAND test_myui_break_pal)

    add_executable(test_myui_font tests/test_myui_font.c)
    target_include_directories(test_myui_font PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_font PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_font COMMAND test_myui_font)

    add_executable(test_myui_chart tests/test_myui_chart.c)
    target_include_directories(test_myui_chart PRIVATE ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_chart PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_chart COMMAND test_myui_chart)

    add_executable(test_myui_chart_group tests/test_myui_chart_group.c)
    target_include_directories(test_myui_chart_group PRIVATE ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_chart_group PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_chart_group COMMAND test_myui_chart_group)

    add_executable(test_myui_edit tests/test_myui_edit.c)
    target_include_directories(test_myui_edit PRIVATE ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_edit PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_edit COMMAND test_myui_edit)

    add_executable(test_myui_echart_option tests/test_myui_echart_option.c)
    target_include_directories(test_myui_echart_option PRIVATE
        ${TEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_echart_option PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_echart_option COMMAND test_myui_echart_option)
    add_executable(test_myui_echart_option_json tests/test_myui_echart_option_json.c)
    target_include_directories(test_myui_echart_option_json PRIVATE
        ${TEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_link_libraries(test_myui_echart_option_json PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_echart_option_json COMMAND test_myui_echart_option_json)
    add_executable(test_myui_echart tests/test_myui_echart.c)
    target_include_directories(test_myui_echart PRIVATE ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_echart PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_echart COMMAND test_myui_echart)
    add_executable(test_myui_echart_event tests/test_myui_echart_event.c)
    target_include_directories(test_myui_echart_event PRIVATE ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_echart_event PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_echart_event COMMAND test_myui_echart_event)
    add_executable(test_myui_echart_animation tests/test_myui_echart_animation.c)
    target_include_directories(test_myui_echart_animation PRIVATE ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_echart_animation PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_echart_animation COMMAND test_myui_echart_animation)
    add_executable(test_myui_echart_adapter tests/test_myui_echart_adapter.c)
    target_include_directories(test_myui_echart_adapter PRIVATE ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_echart_adapter PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_echart_adapter COMMAND test_myui_echart_adapter)
    add_executable(test_myui_echart_mvvm tests/test_myui_echart_mvvm.c
        src/myui/myui/echarts/my_echart_mvvm.c)
    target_include_directories(test_myui_echart_mvvm PRIVATE ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui)
    target_link_libraries(test_myui_echart_mvvm PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_echart_mvvm COMMAND test_myui_echart_mvvm)

    add_executable(test_font_shader_contract tests/test_font_shader_contract.c)
    target_include_directories(test_font_shader_contract PRIVATE ${TEST_INCLUDE_DIRS})
    target_compile_definitions(test_font_shader_contract PRIVATE
        TEST_SOURCE_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")
    add_test(NAME test_font_shader_contract COMMAND test_font_shader_contract)

    add_executable(test_myui_mvvm tests/test_myui_mvvm.c
        src/myui/mypal/dummy/my_pal_dummy.c)
    target_include_directories(test_myui_mvvm PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_mvvm PRIVATE myui_core m)
    add_test(NAME test_myui_mvvm COMMAND test_myui_mvvm)

    add_executable(test_myui_vgcanvas_backend
        tests/test_myui_vgcanvas_backend.c)
    target_include_directories(test_myui_vgcanvas_backend PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_vgcanvas_backend PRIVATE myui_core m Threads::Threads)
    add_test(NAME test_myui_vgcanvas_backend COMMAND test_myui_vgcanvas_backend)

    # Win32 headless contract for the desktop GL WGL pointer resolution.
    if(ENGINE_PLATFORM STREQUAL "windows")
        add_executable(test_myui_gl_desktop_win32
            tests/test_myui_gl_desktop_win32.c)
        target_include_directories(test_myui_gl_desktop_win32 PRIVATE
            ${TEST_INCLUDE_DIRS}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
        )
        target_link_libraries(test_myui_gl_desktop_win32 PRIVATE myui_core m)
        add_test(NAME test_myui_gl_desktop_win32
            COMMAND test_myui_gl_desktop_win32)

        # Real WGL context end-to-end smoke; needs a GL ICD, so headless
        # CI excludes it via the graphics label (test_vulkan precedent).
        add_executable(test_myui_gl_desktop_runtime
            tests/test_myui_gl_desktop_runtime.c)
        target_include_directories(test_myui_gl_desktop_runtime PRIVATE
            ${TEST_INCLUDE_DIRS}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
        )
        target_link_libraries(test_myui_gl_desktop_runtime PRIVATE myui_core m)
        add_test(NAME test_myui_gl_desktop_runtime
            COMMAND test_myui_gl_desktop_runtime)
        set_tests_properties(test_myui_gl_desktop_runtime PROPERTIES
            LABELS graphics)
    endif()

    add_executable(test_rhi_rollout_log tests/test_rhi_rollout_log.c
        src/rhi/rhi_rollout.c src/core/log.c)
    target_include_directories(test_rhi_rollout_log PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_rhi_rollout_log COMMAND test_rhi_rollout_log)
    set_tests_properties(test_rhi_rollout_log PROPERTIES LABELS "headless;platform_contract")
    add_test(NAME test_rhi_rollout_config_contract
        COMMAND ${CMAKE_COMMAND}
            -DROLLOUT_JSON=${CMAKE_CURRENT_SOURCE_DIR}/assets/rhi_backend_rollout.json
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_rollout_config_contract.cmake)
    set_tests_properties(test_rhi_rollout_config_contract PROPERTIES
        LABELS "headless;platform_contract")
    add_test(NAME test_rhi_rollback_runbook_contract
        COMMAND ${CMAKE_COMMAND}
            -DRUNBOOK=${CMAKE_CURRENT_SOURCE_DIR}/../docs/rhi_rollback_runbook.md
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_rollback_runbook_contract.cmake)
    set_tests_properties(test_rhi_rollback_runbook_contract PROPERTIES
        LABELS "headless;platform_contract")
    add_test(NAME test_rhi_opengl_compat_fallback_contract
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -DRHI_C=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi.c
            -DROLLOUT_C=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_rollout.c
            -DROLLOUT_JSON=${CMAKE_CURRENT_SOURCE_DIR}/assets/rhi_backend_rollout.json
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_opengl_compat_fallback_contract.cmake)
    set_tests_properties(test_rhi_opengl_compat_fallback_contract PROPERTIES
        LABELS "headless;platform_contract")
    add_test(NAME test_no_hidden_gl_fallback
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
            -DWHITELIST=${CMAKE_CURRENT_SOURCE_DIR}/tests/gl_fallback_whitelist.txt
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_no_hidden_gl_fallback.cmake)
    set_tests_properties(test_no_hidden_gl_fallback PROPERTIES
        LABELS "headless;platform_contract")
    add_executable(test_rhi_capabilities tests/test_rhi_capabilities.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_compile_definitions(test_rhi_capabilities PRIVATE ENGINE_RHI_TEST=1)
    target_include_directories(test_rhi_capabilities PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rhi_capabilities PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rhi_capabilities PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rhi_capabilities PRIVATE ENGINE_PLATFORM_MACOS=1)
        target_compile_definitions(test_rhi_capabilities PRIVATE ENGINE_VULKAN=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_include_directories(test_rhi_capabilities PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_rhi_capabilities PRIVATE
                ENGINE_PLATFORM_WAYLAND=1)
        endif()
        if(ENGINE_VULKAN)
            target_compile_definitions(test_rhi_capabilities PRIVATE ENGINE_VULKAN=1)
        endif()
    endif()
    target_link_libraries(test_rhi_capabilities PRIVATE engine_rhi_headless m)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(test_rhi_capabilities PRIVATE
            -ffunction-sections -fdata-sections)
    endif()
    if(NOT APPLE)
        # macOS ld has no --gc-sections; dead-code stripping is the default.
        target_link_options(test_rhi_capabilities PRIVATE -Wl,--gc-sections)
    endif()
    add_test(NAME test_rhi_capabilities COMMAND test_rhi_capabilities)
    set_tests_properties(test_rhi_capabilities PROPERTIES
        LABELS "headless;platform_contract")

    add_executable(test_rhi_oracle tests/test_rhi_oracle.c tests/rhi_oracle.c
        src/core/log.c)
    target_include_directories(test_rhi_oracle PRIVATE ${TEST_INCLUDE_DIRS})
    # rhi_oracle_capture_presented references rhi_screenshot; the headless
    # backend resolves it (same pattern as the RHI contract tests above).
    target_link_libraries(test_rhi_oracle PRIVATE engine_rhi_headless m)
    add_test(NAME test_rhi_oracle COMMAND test_rhi_oracle)

    add_executable(test_rhi_fault_injection tests/test_rhi_fault_injection.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_compile_definitions(test_rhi_fault_injection PRIVATE ENGINE_RHI_TEST=1)
    target_include_directories(test_rhi_fault_injection PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rhi_fault_injection PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rhi_fault_injection PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rhi_fault_injection PRIVATE ENGINE_PLATFORM_MACOS=1)
        target_compile_definitions(test_rhi_fault_injection PRIVATE ENGINE_VULKAN=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_include_directories(test_rhi_fault_injection PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_rhi_fault_injection PRIVATE
                ENGINE_PLATFORM_WAYLAND=1)
        endif()
        if(ENGINE_VULKAN)
            target_compile_definitions(test_rhi_fault_injection PRIVATE ENGINE_VULKAN=1)
        endif()
    endif()
    target_link_libraries(test_rhi_fault_injection PRIVATE engine_rhi_headless m)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(test_rhi_fault_injection PRIVATE
            -ffunction-sections -fdata-sections)
    endif()
    if(NOT APPLE)
        # macOS ld has no --gc-sections; dead-code stripping is the default.
        target_link_options(test_rhi_fault_injection PRIVATE -Wl,--gc-sections)
    endif()
    add_test(NAME test_rhi_fault_injection COMMAND test_rhi_fault_injection)
    set_tests_properties(test_rhi_fault_injection PROPERTIES
        LABELS "headless;platform_contract")

    if(ENGINE_VULKAN)
        add_executable(test_rhi_vk_alloc_fault tests/test_rhi_vk_alloc_fault.c)
        target_include_directories(test_rhi_vk_alloc_fault PRIVATE ${TEST_INCLUDE_DIRS})
        target_link_libraries(test_rhi_vk_alloc_fault PRIVATE engine m)
        # rhi_vk.c（含 rhi_device_create 与 rhi_vk_set_alloc_failure_for_test）
        # 编在 engine_rhi_vulkan；test_vulkan 同先例。
        engine_link_rhi_backend(test_rhi_vk_alloc_fault)
        add_test(NAME test_rhi_vk_alloc_fault COMMAND test_rhi_vk_alloc_fault)
        set_tests_properties(test_rhi_vk_alloc_fault PROPERTIES
            LABELS graphics SKIP_RETURN_CODE 77 TIMEOUT 60)
        # Plan C Task 11: golden dump of VK push-constant uniform byte
        # offsets (pasted into test_rhi_metal_resources.c).
        add_executable(test_rhi_push_offset_dump
            tests/test_rhi_push_offset_dump.c)
        target_include_directories(test_rhi_push_offset_dump PRIVATE
            ${TEST_INCLUDE_DIRS})
        target_link_libraries(test_rhi_push_offset_dump PRIVATE engine m)
        engine_link_rhi_backend(test_rhi_push_offset_dump)
        add_test(NAME test_rhi_push_offset_dump
            COMMAND test_rhi_push_offset_dump)
        set_tests_properties(test_rhi_push_offset_dump PROPERTIES
            LABELS graphics SKIP_RETURN_CODE 77 TIMEOUT 60)
    endif()

    add_executable(test_rhi_wsi_attach tests/test_rhi_wsi_attach.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_compile_definitions(test_rhi_wsi_attach PRIVATE ENGINE_RHI_TEST=1)
    target_include_directories(test_rhi_wsi_attach PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rhi_wsi_attach PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rhi_wsi_attach PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rhi_wsi_attach PRIVATE ENGINE_PLATFORM_MACOS=1)
        target_compile_definitions(test_rhi_wsi_attach PRIVATE ENGINE_VULKAN=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_include_directories(test_rhi_wsi_attach PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_rhi_wsi_attach PRIVATE
                ENGINE_PLATFORM_WAYLAND=1)
        endif()
        if(ENGINE_VULKAN)
            target_compile_definitions(test_rhi_wsi_attach PRIVATE ENGINE_VULKAN=1)
        endif()
    endif()
    target_link_libraries(test_rhi_wsi_attach PRIVATE engine_rhi_headless m)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(test_rhi_wsi_attach PRIVATE
            -ffunction-sections -fdata-sections)
    endif()
    if(NOT APPLE)
        target_link_options(test_rhi_wsi_attach PRIVATE -Wl,--gc-sections)
    endif()
    add_test(NAME test_rhi_wsi_attach COMMAND test_rhi_wsi_attach)
    set_tests_properties(test_rhi_wsi_attach PROPERTIES
        LABELS "headless;platform_contract")

    add_executable(test_rhi_error_contract tests/test_rhi_error_contract.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_RHI_TEST=1)
    target_include_directories(test_rhi_error_contract PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_PLATFORM_MACOS=1)
        target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_VULKAN=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_include_directories(test_rhi_error_contract PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_rhi_error_contract PRIVATE
                ENGINE_PLATFORM_WAYLAND=1)
        endif()
        if(ENGINE_VULKAN)
            target_compile_definitions(test_rhi_error_contract PRIVATE ENGINE_VULKAN=1)
        endif()
    endif()
    target_link_libraries(test_rhi_error_contract PRIVATE engine_rhi_headless m)
    add_test(NAME test_rhi_error_contract COMMAND test_rhi_error_contract)
    set_tests_properties(test_rhi_error_contract PROPERTIES
        LABELS "headless;platform_contract")

    add_executable(test_rhi_frame_lifecycle_contract
        tests/test_rhi_frame_lifecycle_contract.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_compile_definitions(test_rhi_frame_lifecycle_contract
        PRIVATE ENGINE_RHI_TEST=1)
    target_include_directories(test_rhi_frame_lifecycle_contract
        PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rhi_frame_lifecycle_contract
            PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rhi_frame_lifecycle_contract
            PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rhi_frame_lifecycle_contract
            PRIVATE ENGINE_PLATFORM_MACOS=1 ENGINE_VULKAN=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_include_directories(test_rhi_frame_lifecycle_contract PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_rhi_frame_lifecycle_contract
                PRIVATE ENGINE_PLATFORM_WAYLAND=1)
        endif()
        if(ENGINE_VULKAN)
            target_compile_definitions(test_rhi_frame_lifecycle_contract
                PRIVATE ENGINE_VULKAN=1)
        endif()
    endif()
    target_link_libraries(test_rhi_frame_lifecycle_contract PRIVATE engine_rhi_headless m)
    add_test(NAME test_rhi_frame_lifecycle_contract
        COMMAND test_rhi_frame_lifecycle_contract)
    set_tests_properties(test_rhi_frame_lifecycle_contract PROPERTIES
        LABELS "headless;platform_contract")
    add_executable(test_rhi_native tests/test_rhi_native.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_include_directories(test_rhi_native PRIVATE ${TEST_INCLUDE_DIRS})
    target_compile_definitions(test_rhi_native PRIVATE ENGINE_RHI_TEST=1)
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rhi_native PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rhi_native PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rhi_native PRIVATE ENGINE_PLATFORM_MACOS=1 ENGINE_VULKAN=1)
    endif()
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_include_directories(test_rhi_native PRIVATE
            ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
        if(ENGINE_ENABLE_WAYLAND)
            target_compile_definitions(test_rhi_native PRIVATE
                ENGINE_PLATFORM_WAYLAND=1)
        endif()
        if(ENGINE_VULKAN)
            target_compile_definitions(test_rhi_native PRIVATE ENGINE_VULKAN=1)
        endif()
    endif()
    target_link_libraries(test_rhi_native PRIVATE engine_rhi_headless m)
    add_test(NAME test_rhi_native COMMAND test_rhi_native)
    set_tests_properties(test_rhi_native PROPERTIES
        LABELS "headless;platform_contract")

    add_executable(test_rhi_tlas_instance_encode
        tests/test_rhi_tlas_instance_encode.c src/rhi/rhi_validation.c)
    target_include_directories(test_rhi_tlas_instance_encode PRIVATE
        ${TEST_INCLUDE_DIRS})
    add_test(NAME test_rhi_tlas_instance_encode
        COMMAND test_rhi_tlas_instance_encode)
    set_tests_properties(test_rhi_tlas_instance_encode PROPERTIES
        LABELS "headless;platform_contract")

    add_executable(test_myui_layout tests/test_myui_layout.c)
    target_include_directories(test_myui_layout PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_layout PRIVATE myui_core m)
    add_test(NAME test_myui_layout COMMAND test_myui_layout)

    add_executable(test_myui_css tests/test_myui_css.c)
    target_include_directories(test_myui_css PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_css PRIVATE myui_core m)
    add_test(NAME test_myui_css COMMAND test_myui_css)

    if(MYUI_UI_YAML)
        add_executable(test_myui_loader tests/test_myui_loader.c
            src/myui/mypal/dummy/my_pal_dummy.c)
        target_include_directories(test_myui_loader PRIVATE
            ${TEST_INCLUDE_DIRS}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
        )
        target_link_libraries(test_myui_loader PRIVATE myui_core m)
        add_test(NAME test_myui_loader COMMAND test_myui_loader)
    else()
        add_executable(test_myui_loader_disabled tests/test_myui_loader_disabled.c)
        target_include_directories(test_myui_loader_disabled PRIVATE
            ${TEST_INCLUDE_DIRS}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
        )
        target_link_libraries(test_myui_loader_disabled PRIVATE myui_core m)
        add_test(NAME test_myui_loader_disabled COMMAND test_myui_loader_disabled)
    endif()

    add_executable(test_myui_text_layout tests/test_myui_text_layout.c)
    target_include_directories(test_myui_text_layout PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_text_layout PRIVATE myui_core m)
    add_test(NAME test_myui_text_layout COMMAND test_myui_text_layout)

    add_executable(test_myui_metrics tests/test_myui_metrics.c)
    target_include_directories(test_myui_metrics PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_metrics PRIVATE myui_core m)
    add_test(NAME test_myui_metrics COMMAND test_myui_metrics)

    add_executable(test_myui_syntax tests/test_myui_syntax.c)
    target_include_directories(test_myui_syntax PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_syntax PRIVATE myui_core m)
    add_test(NAME test_myui_syntax COMMAND test_myui_syntax)
    add_test(NAME verify_myui_line_break_valid
        COMMAND verify_myui_line_break
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_line_break_verifier_valid.txt)
    add_test(NAME verify_myui_line_break_rejects_mismatch
        COMMAND verify_myui_line_break
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_line_break_verifier_invalid.txt)
    set_tests_properties(verify_myui_line_break_rejects_mismatch
        PROPERTIES WILL_FAIL TRUE)
    add_test(NAME verify_myui_line_break_rejects_malformed
        COMMAND verify_myui_line_break
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_line_break_verifier_malformed.txt)
    set_tests_properties(verify_myui_line_break_rejects_malformed
        PROPERTIES WILL_FAIL TRUE)
    add_test(NAME verify_myui_sa_dictionary_valid
        COMMAND verify_myui_sa_dictionary
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_sa_dictionary_valid.yaml)
    add_test(NAME verify_myui_sa_dictionary_rejects_invalid
        COMMAND verify_myui_sa_dictionary
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_sa_dictionary_invalid.yaml)
    set_tests_properties(verify_myui_sa_dictionary_rejects_invalid
        PROPERTIES WILL_FAIL TRUE)
    add_test(NAME verify_myui_sa_dictionary_rejects_invalid_scalar
        COMMAND verify_myui_sa_dictionary
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_sa_dictionary_rejects_invalid_scalar.yaml)
    set_tests_properties(verify_myui_sa_dictionary_rejects_invalid_scalar
        PROPERTIES WILL_FAIL TRUE)
    add_test(NAME verify_myui_sa_dictionary_rejects_invalid_locale
        COMMAND verify_myui_sa_dictionary
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_sa_dictionary_rejects_invalid_locale.yaml)
    set_tests_properties(verify_myui_sa_dictionary_rejects_invalid_locale
        PROPERTIES WILL_FAIL TRUE)
    add_test(NAME verify_myui_sa_dictionary_rejects_mismatch
        COMMAND verify_myui_sa_dictionary
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_sa_dictionary_rejects_mismatch.yaml)
    set_tests_properties(verify_myui_sa_dictionary_rejects_mismatch
        PROPERTIES WILL_FAIL TRUE)
    add_test(NAME verify_myui_sa_dictionary_rejects_malformed
        COMMAND verify_myui_sa_dictionary
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/myui_sa_dictionary_rejects_malformed.yaml)
    set_tests_properties(verify_myui_sa_dictionary_rejects_malformed
        PROPERTIES WILL_FAIL TRUE)

    add_test(NAME test_myr_dependency_config
        COMMAND ${CMAKE_COMMAND}
            -DMYR_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/myr/CMakeLists.txt
            -DMYUI_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/myui/CMakeLists.txt
            -DMYC_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/myc/CMakeLists.txt
            -DMYMVVM_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/mymvvm/CMakeLists.txt
            -DMYMVVM_UI_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/mymvvm_myui/CMakeLists.txt
            -DMYPAL_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/mypal/CMakeLists.txt
            -DMYR_VULKAN_C=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/myr/my_vgcanvas_vulkan.c
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_myr_dependency_config.cmake)
    # macOS 上 engine configure 恒要求 shaderc+Vulkan（molten-vk 无
    # libvulkan.dylib，自动发现必败），把外层已解析的路径透传给嵌套
    # configure；其他平台这些变量未定义/为空时不传。
    set(_rhi_selector_toolchain_defs)
    foreach(_rhi_def Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
        if(DEFINED ${_rhi_def} AND NOT "${${_rhi_def}}" STREQUAL "")
            list(APPEND _rhi_selector_toolchain_defs "-D${_rhi_def}=${${_rhi_def}}")
        endif()
    endforeach()
    add_test(NAME test_rhi_backend_selection
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -DENGINE_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
            -DTEST_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}/rhi-selector-contract
            -DENGINE_ENABLE_WAYLAND=${ENGINE_ENABLE_WAYLAND}
            ${_rhi_selector_toolchain_defs}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_backend_selection.cmake)
    add_test(NAME test_locked_dependencies
        COMMAND ${CMAKE_COMMAND}
            -DLOCK_JSON=${CMAKE_CURRENT_SOURCE_DIR}/external/locked_dependencies.json
            -DEXTERNAL_DIR=${CMAKE_CURRENT_SOURCE_DIR}/external
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_locked_dependencies.cmake)
    set_tests_properties(test_locked_dependencies PROPERTIES
        LABELS "headless;platform_contract")
    add_test(NAME test_clean_room_build_contract
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_clean_room_build_contract.cmake)
    set_tests_properties(test_clean_room_build_contract PROPERTIES
        LABELS "headless;platform_contract")
    # Receipt contract (plan F task 7): generate the sample receipt at
    # configure time so the schema validator is self-contained in every
    # build tree (docs/rhi_benchmark_receipt_schema.md).
    execute_process(
        COMMAND ${CMAKE_COMMAND}
            -DOUT=${CMAKE_CURRENT_BINARY_DIR}/sample_receipt.json
            -DPLATFORM=windows -DBACKEND=vulkan
            -DEVIDENCE_LEVEL=GPU_RUNTIME -DRUNNER=local
            "-DCOMMAND_STR=ctest -L graphics"
            -DGPU=(fill) -DDRIVER_VERSION=(fill) -DCPU=(fill) -DRAM=(fill)
            -DBUILD_CONFIG=Debug
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tools/make_evidence_receipt.cmake
        RESULT_VARIABLE _receipt_sample_rc)
    if(_receipt_sample_rc EQUAL 0)
        add_test(NAME test_evidence_receipt_schema
            COMMAND ${CMAKE_COMMAND}
                -DRECEIPT=${CMAKE_CURRENT_BINARY_DIR}/sample_receipt.json
                -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_evidence_receipt_schema.cmake)
        set_tests_properties(test_evidence_receipt_schema PROPERTIES
            LABELS "headless;platform_contract")
    else()
        message(WARNING "sample receipt generation failed (rc=${_receipt_sample_rc}); "
                "test_evidence_receipt_schema not registered")
    endif()
    add_test(NAME test_release_package_contract
        COMMAND ${CMAKE_COMMAND}
            -DPACKAGER=${CMAKE_CURRENT_SOURCE_DIR}/tools/package_release.sh
            -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_release_package_contract.cmake)
    set_tests_properties(test_release_package_contract PROPERTIES
        LABELS "headless;platform_contract;release_gate")
    option(RHI_EVIDENCE_REQUIRE_LOCAL_FROZEN
        "Require local frozen RHI evidence files in test_rhi_evidence_register" OFF)
    add_test(NAME test_rhi_evidence_register
        COMMAND ${CMAKE_COMMAND}
            -DREPO_ROOT=${CMAKE_CURRENT_SOURCE_DIR}/..
            -DEVIDENCE_DOC=${CMAKE_CURRENT_SOURCE_DIR}/../docs/rhi_backend_evidence.md
            -DRHI_EVIDENCE_REQUIRE_LOCAL_FROZEN=${RHI_EVIDENCE_REQUIRE_LOCAL_FROZEN}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_evidence_register.cmake)
    set_tests_properties(test_rhi_evidence_register PROPERTIES
        LABELS "platform_contract")
    add_test(NAME test_rhi_header_neutral
        COMMAND ${CMAKE_COMMAND}
            -DRHI_PUBLIC_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi.h
            -DRHI_VULKAN_NATIVE_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_native_vulkan.h
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_header_neutral.cmake)
    set_tests_properties(test_rhi_header_neutral PROPERTIES
        LABELS "platform_contract")
    add_test(NAME test_d3d12_sdk_lock
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_d3d12_sdk_lock.cmake)
    set_tests_properties(test_d3d12_sdk_lock PROPERTIES LABELS "headless;platform_contract")
    add_test(NAME test_d3d12_dependency_gate
        COMMAND ${CMAKE_COMMAND}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_d3d12_dependency_gate.cmake)
    # SKIP_REGULAR_EXPRESSION covers cmake < 3.29 hosts (no cmake_language
    # EXIT): the script's FATAL_ERROR fallback exits 1 but still prints the
    # UNAVAILABLE line, which ctest maps to SKIP. On cmake >= 3.29 the
    # SKIP_RETURN_CODE 77 path handles every skip site.
    set_tests_properties(test_d3d12_dependency_gate PROPERTIES
        SKIP_RETURN_CODE 77 SKIP_REGULAR_EXPRESSION "UNAVAILABLE"
        LABELS "platform_contract")
    add_test(NAME test_d3d12_shader_compile_gate
        COMMAND ${CMAKE_COMMAND}
            -DCMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_d3d12_shader_compile_gate.cmake)
    set_tests_properties(test_d3d12_shader_compile_gate PROPERTIES
        SKIP_RETURN_CODE 77 LABELS "platform_contract")
    add_executable(test_d3d12_lifetime_hresult_contract
        tests/test_d3d12_lifetime_hresult_contract.c)
    target_include_directories(test_d3d12_lifetime_hresult_contract PRIVATE
        ${TEST_INCLUDE_DIRS})
    add_test(NAME test_d3d12_lifetime_hresult_contract
        COMMAND test_d3d12_lifetime_hresult_contract)
    set_tests_properties(test_d3d12_lifetime_hresult_contract PROPERTIES
        LABELS "headless;platform_contract")
    if(WIN32 AND ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "d3d12")
        add_executable(test_d3d12_native_failure
            tests/test_d3d12_native_failure.c)
        target_include_directories(test_d3d12_native_failure PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)
        target_link_libraries(test_d3d12_native_failure PRIVATE
            engine_rhi_d3d12 d3d12 dxgi dxguid)
        if(CMAKE_C_COMPILER_ID MATCHES "Clang")
            if(CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
                set(_d3d12_sdk_quiet "/clang:-Wno-nonportable-include-path;/clang:-Wno-ignored-pragma-intrinsic;/clang:-Wno-pragma-pack;/clang:-Wno-unknown-pragmas;/clang:-Wno-microsoft-anon-tag")
            else()
                # clang in GNU mode does not accept /clang: pass-through options.
                set(_d3d12_sdk_quiet "-Wno-nonportable-include-path;-Wno-ignored-pragma-intrinsic;-Wno-pragma-pack;-Wno-unknown-pragmas;-Wno-microsoft-anon-tag")
            endif()
            set_source_files_properties(tests/test_d3d12_native_failure.c PROPERTIES
                COMPILE_OPTIONS "${_d3d12_sdk_quiet}")
        endif()
        add_test(NAME test_d3d12_native_failure COMMAND test_d3d12_native_failure)
        set_tests_properties(test_d3d12_native_failure PROPERTIES
            LABELS "headless;platform_contract")
        # Task 3: real-device contract. Exit 77 on hosts without a D3D12
        # adapter (CI), so SKIP_RETURN_CODE keeps those lanes green; on a
        # GPU host the assertions run against a live device (GPU_RUNTIME).
        add_executable(test_d3d12_device_contract
            tests/test_d3d12_device_contract.c)
        target_include_directories(test_d3d12_device_contract PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)
        target_link_libraries(test_d3d12_device_contract PRIVATE
            engine_rhi_d3d12 d3d12 dxgi dxguid)
        add_test(NAME test_d3d12_device_contract
            COMMAND test_d3d12_device_contract)
        set_tests_properties(test_d3d12_device_contract PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime")
        # Task 4: swapchain + frame-lifecycle contract on a live device.
        # Same SKIP 77 policy as the Task 3 device contract.
        add_executable(test_d3d12_swapchain_contract
            tests/test_d3d12_swapchain_contract.c)
        target_include_directories(test_d3d12_swapchain_contract PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)
        target_link_libraries(test_d3d12_swapchain_contract PRIVATE
            engine_rhi_d3d12 d3d12 dxgi dxguid)
        add_test(NAME test_d3d12_swapchain_contract
            COMMAND test_d3d12_swapchain_contract)
        set_tests_properties(test_d3d12_swapchain_contract PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime")
        # Task 5: committed-resource roundtrips (buffer staging upload +
        # readback, texture upload + readback) and the shared indirect ABI
        # rule on a live device. Same SKIP 77 policy as the Task 3/4
        # contracts. The sentinel HWND needs the test-only fallback-window
        # opt-in (Task 4 review gate), injected via ENVIRONMENT here so the
        # test source itself stays hermetic.
        add_executable(test_d3d12_pipeline_contract
            tests/test_d3d12_pipeline_contract.c)
        target_include_directories(test_d3d12_pipeline_contract PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)
        target_link_libraries(test_d3d12_pipeline_contract PRIVATE
            engine_rhi_d3d12 d3d12 dxgi dxguid)
        if(CMAKE_C_COMPILER_ID MATCHES "Clang")
            # The test includes rhi_d3d12.h (Windows SDK headers) for the
            # descriptor-allocator regression probes — same exemption set
            # as test_d3d12_native_failure.
            if(CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
                set(_d3d12_sdk_quiet "/clang:-Wno-nonportable-include-path;/clang:-Wno-ignored-pragma-intrinsic;/clang:-Wno-pragma-pack;/clang:-Wno-unknown-pragmas;/clang:-Wno-microsoft-anon-tag")
            else()
                set(_d3d12_sdk_quiet "-Wno-nonportable-include-path;-Wno-ignored-pragma-intrinsic;-Wno-pragma-pack;-Wno-unknown-pragmas;-Wno-microsoft-anon-tag")
            endif()
            set_source_files_properties(tests/test_d3d12_pipeline_contract.c PROPERTIES
                COMPILE_OPTIONS "${_d3d12_sdk_quiet}")
        endif()
        add_test(NAME test_d3d12_pipeline_contract
            COMMAND test_d3d12_pipeline_contract)
        set_tests_properties(test_d3d12_pipeline_contract PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime"
            ENVIRONMENT "BREAK_D3D12_TEST_FALLBACK_HWND=1")
        # Task 6: shader pipeline contract — hand-authored HLSL sidecars,
        # build-time dxc DXIL, root-constant push mapping with the
        # VK-parity byte-offset uniform location. Same SKIP 77 policy as
        # the Task 3/4/5 contracts (real device required, GPU_RUNTIME).
        add_executable(test_d3d12_shader_contract
            tests/test_d3d12_shader_contract.c)
        target_include_directories(test_d3d12_shader_contract PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)
        target_link_libraries(test_d3d12_shader_contract PRIVATE
            engine_rhi_d3d12 d3d12 dxgi dxguid)
        add_dependencies(test_d3d12_shader_contract engine_shaders_d3d12)
        add_test(NAME test_d3d12_shader_contract
            COMMAND test_d3d12_shader_contract)
        set_tests_properties(test_d3d12_shader_contract PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime"
            ENVIRONMENT "BREAK_D3D12_TEST_FALLBACK_HWND=1")
        # Task 7: DXR contract -- AS create is fail-closed below
        # raytracing tier 1.0 (fail-closed half runs, then SKIP 77); on a
        # DXR adapter the BLAS create + device-address path runs against
        # the live device (GPU_RUNTIME). Same SKIP 77 policy and
        # fallback-window opt-in as the Task 3-6 contracts.
        add_executable(test_d3d12_dxr_contract
            tests/test_d3d12_dxr_contract.c)
        target_include_directories(test_d3d12_dxr_contract PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)
        target_link_libraries(test_d3d12_dxr_contract PRIVATE
            engine_rhi_d3d12 d3d12 dxgi dxguid)
        add_test(NAME test_d3d12_dxr_contract
            COMMAND test_d3d12_dxr_contract)
        set_tests_properties(test_d3d12_dxr_contract PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime"
            ENVIRONMENT "BREAK_D3D12_TEST_FALLBACK_HWND=1")
        # Task 8: WARP-forced runtime floor for the windows-d3d12 lane.
        # ENGINE_D3D12_WARP=1 forces the WARP adapter so GPU-less runners
        # get a deterministic software GPU-runtime floor; the test asserts
        # the device identity honestly reports WARP (Microsoft Basic Render
        # Driver) instead of masquerading as hardware. The sentinel HWND
        # needs the test-only fallback-window opt-in, same as the Task 3-7
        # contracts. WARP receipts are recorded with gpu=WARP and never
        # upgrade the evidence level past GPU-runtime.
        add_executable(test_d3d12_warp_runtime
            tests/test_d3d12_warp_runtime.c)
        target_include_directories(test_d3d12_warp_runtime PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)
        target_link_libraries(test_d3d12_warp_runtime PRIVATE
            engine_rhi_d3d12 d3d12 dxgi dxguid)
        add_test(NAME test_d3d12_warp_runtime
            COMMAND test_d3d12_warp_runtime)
        set_tests_properties(test_d3d12_warp_runtime PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime"
            ENVIRONMENT "ENGINE_D3D12_WARP=1;BREAK_D3D12_TEST_FALLBACK_HWND=1")
    endif()
    add_test(NAME test_rhi_backend_internal_contract
        COMMAND ${CMAKE_COMMAND}
            -DRHI_INTERNAL_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_backend_internal.h
            -DRHI_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi.c
            -DRHI_OWNERSHIP_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_ownership.c
             -DRHI_VALIDATION_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_validation.c
             -DRHI_RESOURCES_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_resources.c
             -DRHI_PRESENT_HISTORY_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_present_history.c
             -DRHI_RT_TRACE_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/rt_trace.c
             -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -DRHI_GL_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_gl.c
            -DRHI_VK_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_vk.c
            -DRHI_HEADLESS_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_headless.c
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_backend_internal_contract.cmake)
    add_test(NAME test_renderer_backend_token_gate
        COMMAND ${CMAKE_COMMAND} -DENGINE_SRC=${CMAKE_CURRENT_SOURCE_DIR}/src
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_renderer_backend_token_gate.cmake)
    set_tests_properties(test_renderer_backend_token_gate PROPERTIES LABELS headless)
    add_test(NAME test_rhi_metal_ownership
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rhi_metal_ownership.cmake)
    set_tests_properties(test_rhi_metal_ownership PROPERTIES LABELS "headless;platform_contract")
    # Plan C Task 3: Metal pixel-format mapping layer — pure C11, platform-free
    # header; runs on any host (the ordinal->MTLPixelFormat pinning lives in
    # rhi_metal.m via _Static_assert and is compile-checked on macOS only).
    add_executable(test_rhi_metal_format_mapping
        tests/test_rhi_metal_format_mapping.c
        src/core/shader_io.c src/core/log.c)
    target_include_directories(test_rhi_metal_format_mapping PRIVATE
        ${TEST_INCLUDE_DIRS})
    # Task 10: FNV hash vectors run everywhere; the GLSL<->MSL
    # reflection consistency cases read the engine/shaders sources
    # plus the pipeline-generated MSL (metal build only).
    target_compile_definitions(test_rhi_metal_format_mapping PRIVATE
        ENGINE_SHADER_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    if(APPLE AND ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")
        target_compile_definitions(test_rhi_metal_format_mapping PRIVATE
            ENGINE_METAL_SHADER_MSL_DIR="${METAL_SHADER_OUT_DIR}/msl")
        add_dependencies(test_rhi_metal_format_mapping engine_metal_shaders)
    endif()
    add_test(NAME test_rhi_metal_format_mapping
        COMMAND test_rhi_metal_format_mapping)
    set_tests_properties(test_rhi_metal_format_mapping PROPERTIES
        LABELS "headless;platform_contract")
    # Plan C Task 3: real-device contract on a live Metal device. The
    # CAMetalLayer is created offscreen (no window); exit 77 = SKIP when
    # Metal is unavailable (GPU-less runner) or the build is not macOS+metal.
    # Task 4: RHI_CORE_SOURCES are compiled directly into the test (same
    # pattern as the headless RHI contract tests) so ENGINE_RHI_TEST arms the
    # rhi_test_set_device_status injection hook without relinking engine.
    if(APPLE AND ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "metal")
        add_executable(test_rhi_metal_device_contract
            tests/test_rhi_metal_device_contract.c tests/metal_test_layer.m
            ${RHI_CORE_SOURCES} src/core/log.c)
        target_include_directories(test_rhi_metal_device_contract PRIVATE
            ${TEST_INCLUDE_DIRS})
        target_compile_definitions(test_rhi_metal_device_contract PRIVATE
            ENGINE_RHI_BACKEND_METAL=1 ENGINE_RHI_TEST=1)
        if(ENGINE_PLATFORM STREQUAL "macos")
            target_compile_definitions(test_rhi_metal_device_contract PRIVATE
                ENGINE_PLATFORM_MACOS=1)
        endif()
        # Manual reference counting, same policy as src/platform/window_cocoa.m.
        set_source_files_properties(tests/metal_test_layer.m PROPERTIES
            COMPILE_OPTIONS "-fno-objc-arc")
        target_link_libraries(test_rhi_metal_device_contract PRIVATE
            m "-framework QuartzCore" "-framework Metal")
        engine_link_rhi_backend(test_rhi_metal_device_contract)
        add_test(NAME test_rhi_metal_device_contract
            COMMAND test_rhi_metal_device_contract)
        set_tests_properties(test_rhi_metal_device_contract PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime")
        # Plan C Task 5: frame lifecycle contract (acquire/present/resize,
        # two-slot pacing index sequence) on a live Metal device, same
        # offscreen-layer and direct-RHI_CORE_SOURCES pattern as above.
        add_executable(test_rhi_metal_frame_lifecycle
            tests/test_rhi_metal_frame_lifecycle.c tests/metal_test_layer.m
            ${RHI_CORE_SOURCES} src/core/log.c)
        target_include_directories(test_rhi_metal_frame_lifecycle PRIVATE
            ${TEST_INCLUDE_DIRS})
        target_compile_definitions(test_rhi_metal_frame_lifecycle PRIVATE
            ENGINE_RHI_BACKEND_METAL=1 ENGINE_RHI_TEST=1)
        if(ENGINE_PLATFORM STREQUAL "macos")
            target_compile_definitions(test_rhi_metal_frame_lifecycle PRIVATE
                ENGINE_PLATFORM_MACOS=1)
        endif()
        target_link_libraries(test_rhi_metal_frame_lifecycle PRIVATE
            m "-framework QuartzCore" "-framework Metal")
        engine_link_rhi_backend(test_rhi_metal_frame_lifecycle)
        add_test(NAME test_rhi_metal_frame_lifecycle
            COMMAND test_rhi_metal_frame_lifecycle)
        set_tests_properties(test_rhi_metal_frame_lifecycle PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime")
        # Plan C Task 7: resource contract (buffers/textures/samplers/
        # cubemaps/arrays, R587-R602 + R624 byte contracts) on a live Metal
        # device, same offscreen-layer and direct-RHI_CORE_SOURCES pattern.
        add_executable(test_rhi_metal_resources
            tests/test_rhi_metal_resources.c tests/metal_test_layer.m
            ${RHI_CORE_SOURCES} src/core/log.c src/core/shader_io.c)
        target_include_directories(test_rhi_metal_resources PRIVATE
            ${TEST_INCLUDE_DIRS})
        # Task 10: the manifest end-to-end case reads real GLSL from
        # the source tree.
        target_compile_definitions(test_rhi_metal_resources PRIVATE
            ENGINE_SHADER_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders")
        target_compile_definitions(test_rhi_metal_resources PRIVATE
            ENGINE_RHI_BACKEND_METAL=1 ENGINE_RHI_TEST=1)
        if(ENGINE_PLATFORM STREQUAL "macos")
            target_compile_definitions(test_rhi_metal_resources PRIVATE
                ENGINE_PLATFORM_MACOS=1)
        endif()
        target_link_libraries(test_rhi_metal_resources PRIVATE
            m "-framework QuartzCore" "-framework Metal")
        engine_link_rhi_backend(test_rhi_metal_resources)
        add_test(NAME test_rhi_metal_resources
            COMMAND test_rhi_metal_resources)
        set_tests_properties(test_rhi_metal_resources PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime")
        # Plan C Task 13: consumer smoke (dxx_break/engine_demo/myui)
        # under the metal backend. engine_demo needs a window service;
        # SKIP_RETURN_CODE 77 covers SSH/CI runners without one.
        add_test(NAME test_macos_metal_consumer_smoke
            COMMAND ${CMAKE_COMMAND}
                -DBUILD_DIR=${CMAKE_CURRENT_BINARY_DIR}
                -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
                -DMETAL_LANE=1
                -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_macos_metal_consumer_smoke.cmake)
        set_tests_properties(test_macos_metal_consumer_smoke PROPERTIES
            SKIP_RETURN_CODE 77 LABELS "graphics;platform_runtime")
    endif()
    add_test(NAME test_platform_vk_surface_contract
        COMMAND ${CMAKE_COMMAND}
            -DRHI_VK_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_vk.c
            -DVK_SURFACE_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_vk_surface.c
            -DVK_SURFACE_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_vk_surface.h
            -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_platform_vk_surface_contract.cmake)
    set_tests_properties(test_platform_vk_surface_contract PROPERTIES
        LABELS "platform_contract")
    # Plan C Task 14: CI lane separation contract (text-level).
    add_test(NAME test_ci_lane_separation
        COMMAND ${CMAKE_COMMAND}
            -DCI_YML=${CMAKE_CURRENT_SOURCE_DIR}/../.github/workflows/ci.yml
            -DEVIDENCE_MD=${CMAKE_CURRENT_SOURCE_DIR}/../docs/rhi_backend_evidence.md
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_ci_lane_separation.cmake)
    set_tests_properties(test_ci_lane_separation PROPERTIES
        LABELS "platform_contract")
    # Plan C Task 10: offline Metal shader pipeline contract (text-level,
    # platform-free; the real pipeline run is macOS-only).
    add_test(NAME test_metal_shader_pipeline
        COMMAND ${CMAKE_COMMAND}
            -DREPO_ROOT=${CMAKE_CURRENT_SOURCE_DIR}/..
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_metal_shader_pipeline.cmake)
    set_tests_properties(test_metal_shader_pipeline PROPERTIES
        LABELS "platform_contract")
    add_test(NAME test_vulkan_isolation_gates
        COMMAND ${CMAKE_COMMAND}
            -DTEST_VULKAN_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/test_vulkan.c
            -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            -DCI_WORKFLOW=${CMAKE_CURRENT_SOURCE_DIR}/../.github/workflows/ci.yml
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_vulkan_isolation_gates.cmake)
    set_tests_properties(test_vulkan_isolation_gates PROPERTIES
        LABELS "platform_contract")
    add_test(NAME test_platform_wsi_wiring_contract
        COMMAND ${CMAKE_COMMAND}
            -DPLATFORM_H=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform.h
            -DWSI_H=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_wsi.h
            -DWIN32_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_win32.c
            -DX11_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_x11.c
            -DWAYLAND_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_wayland.c
            -DCOCOA_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_cocoa.m
            -DMOBILE_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_mobile.c
            -DRHI_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi.c
            -DRHI_INTERNAL_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/rhi/rhi_backend_internal.h
            -DMAIN_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_platform_wsi_wiring_contract.cmake)
    set_tests_properties(test_platform_wsi_wiring_contract PROPERTIES
        LABELS "platform_contract")
    if(TARGET Vulkan::Vulkan)
        add_executable(test_platform_vk_surface_abi
            tests/test_platform_vk_surface_abi.c)
        target_include_directories(test_platform_vk_surface_abi PRIVATE
            ${TEST_INCLUDE_DIRS})
        target_link_libraries(test_platform_vk_surface_abi PRIVATE Vulkan::Vulkan)
        if(ENGINE_PLATFORM STREQUAL "linux")
            target_compile_definitions(test_platform_vk_surface_abi PRIVATE
                ENGINE_PLATFORM_LINUX=1)
            target_include_directories(test_platform_vk_surface_abi PRIVATE
                ${X11_INCLUDE_DIRS} ${WAYLAND_INCLUDE_DIRS})
            if(ENGINE_ENABLE_WAYLAND)
                target_compile_definitions(test_platform_vk_surface_abi PRIVATE
                    ENGINE_PLATFORM_WAYLAND=1)
                target_link_libraries(test_platform_vk_surface_abi PRIVATE
                    ${WAYLAND_LIBRARIES})
            endif()
        elseif(ENGINE_PLATFORM STREQUAL "windows")
            target_compile_definitions(test_platform_vk_surface_abi PRIVATE
                ENGINE_PLATFORM_WINDOWS=1)
        elseif(ENGINE_PLATFORM STREQUAL "macos")
            target_compile_definitions(test_platform_vk_surface_abi PRIVATE
                ENGINE_PLATFORM_MACOS=1)
        endif()
        add_test(NAME test_platform_vk_surface_abi
            COMMAND test_platform_vk_surface_abi)
        set_tests_properties(test_platform_vk_surface_abi PROPERTIES
            LABELS "headless;platform_contract")
    endif()
    add_test(NAME test_myui_subproject_config
        COMMAND ${CMAKE_COMMAND}
            -DMYUI_ROOT_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/CMakeLists.txt
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_myui_subproject_config.cmake)
    # Vulkan SDK >= 1.4.321 renamed glslangValidator to glslang; accept both.
    find_program(MYUI_GLSLANG_VALIDATOR NAMES glslangValidator glslang)
    if(MYUI_GLSLANG_VALIDATOR)
        add_test(NAME test_myui_vulkan_shader_generator
            COMMAND ${CMAKE_COMMAND}
                -DCMAKE_BIN=${CMAKE_COMMAND}
                -DGLSLANG_VALIDATOR=${MYUI_GLSLANG_VALIDATOR}
                -DGENERATOR=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/myr/vulkan_shaders/generate_includes.cmake
                -DSHADER_DIR=${CMAKE_CURRENT_SOURCE_DIR}/src/myui/myr/vulkan_shaders
                -DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/myui-vulkan-generator-test
                -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_myui_vulkan_shader_generator.cmake)
    endif()
    add_test(NAME test_redis_dependency_config
        COMMAND ${CMAKE_COMMAND}
            -DENGINE_CMAKE=${CMAKE_CURRENT_LIST_FILE}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_redis_dependency_config.cmake)

    # R434: test_shadow: CSM texel snapping — header-only csm.h, only needs math.c
    add_executable(test_shadow tests/test_shadow.c src/math/math.c)
    target_include_directories(test_shadow PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_shadow PRIVATE m)
    add_test(NAME test_shadow COMMAND test_shadow)

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

    # test_task_singleton: validates the documented process-wide TaskSystem ownership.
    add_executable(test_task_singleton tests/test_task_singleton.c src/task/task.c src/core/log.c)
    target_include_directories(test_task_singleton PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_task_singleton PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
        target_link_libraries(test_task_singleton PRIVATE pthread m)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_task_singleton PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_task_singleton PRIVATE kernel32)
    endif()
    add_test(NAME test_task_singleton COMMAND test_task_singleton)

    # test_lod: needs lod.c + math.c
    add_executable(test_lod tests/test_lod.c src/renderer/lod.c src/math/math.c)
    target_include_directories(test_lod PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_lod PRIVATE m)
    add_test(NAME test_lod COMMAND test_lod)

    # test_async_loader: needs async_loader.c + vfs.c + log.c
    add_executable(test_async_loader tests/test_async_loader.c
        src/asset/async_loader.c src/asset/decode_pipeline.c src/asset/vfs.c src/core/log.c
        external/stb_image_impl.c)
    target_include_directories(test_async_loader PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_async_loader PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
        target_link_libraries(test_async_loader PRIVATE pthread m)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_async_loader PRIVATE ENGINE_PLATFORM_WINDOWS=1 _CRT_SECURE_NO_WARNINGS)
        target_link_libraries(test_async_loader PRIVATE kernel32)
    endif()
    add_test(NAME test_async_loader COMMAND test_async_loader)

    # test_ecs: needs ecs.c + log.c
    add_executable(test_ecs tests/test_ecs.c src/ecs/ecs.c src/core/log.c)
    target_include_directories(test_ecs PRIVATE ${TEST_INCLUDE_DIRS})
    if(NOT ENGINE_PLATFORM STREQUAL "windows")
        target_link_libraries(test_ecs PRIVATE m)
    endif()
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
    if(ENGINE_PLATFORM STREQUAL "linux" OR ENGINE_PLATFORM STREQUAL "android" OR
       ENGINE_PLATFORM STREQUAL "harmonyos")
        target_compile_definitions(test_network PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=200112L)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_network PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_network PRIVATE ws2_32)
    endif()
    add_test(NAME test_network COMMAND test_network)

    # test_net_loop: platform-optimal event loop (kqueue/epoll/IOCP).
    # Backend source is selected the same way the engine target does it.
    add_executable(test_net_loop tests/test_net_loop.c
        src/network/network.c src/platform/time.c ${NET_LOOP_BACKEND_SRC})
    target_include_directories(test_net_loop PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux" OR ENGINE_PLATFORM STREQUAL "android" OR
       ENGINE_PLATFORM STREQUAL "harmonyos")
        target_compile_definitions(test_net_loop PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=200112L)
        target_compile_definitions(test_net_loop PRIVATE ENGINE_NET_LOOP_TESTING=1)
        target_link_libraries(test_net_loop PRIVATE pthread)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_net_loop PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_net_loop PRIVATE ws2_32 mswsock)
    elseif(ENGINE_PLATFORM STREQUAL "macos" OR ENGINE_PLATFORM STREQUAL "ios")
        target_compile_definitions(test_net_loop PRIVATE ENGINE_PLATFORM_MACOS=1)
        target_compile_definitions(test_net_loop PRIVATE ENGINE_NET_LOOP_TESTING=1)
        target_link_libraries(test_net_loop PRIVATE pthread)
    endif()
    if(ENGINE_NET_IOURING AND ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_net_loop PRIVATE ENGINE_NET_IOURING=1)
    endif()
    add_test(NAME test_net_loop COMMAND test_net_loop)

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

    # R389: mutation fuzzer for the replication receive path (remote input).
    # Same usage as fuzz_scene_serial / fuzz_vfs_pak: EXCLUDE_FROM_ALL, build
    # explicitly and run by hand under ASan/UBSan.
    add_executable(fuzz_net_packet EXCLUDE_FROM_ALL tests/fuzz_net_packet.c
        src/network/net_replication.c src/network/packet.c src/network/network.c
        src/platform/time.c src/core/log.c)
    target_include_directories(fuzz_net_packet PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(fuzz_net_packet PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=200112L)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(fuzz_net_packet PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(fuzz_net_packet PRIVATE ws2_32)
    endif()

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

    # test_pbr_math: CPU reference Cook-Torrance PBR (header-only, R579)
    add_executable(test_pbr_math tests/test_pbr_math.c)
    target_include_directories(test_pbr_math PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_pbr_math PRIVATE m)
    add_test(NAME test_pbr_math COMMAND test_pbr_math)

    # test_pool: fixed-size block allocator
    add_executable(test_pool tests/test_pool.c src/core/pool.c src/core/log.c)
    target_include_directories(test_pool PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_pool PRIVATE m)
    add_test(NAME test_pool COMMAND test_pool)

    # test_mipmap_stream: streaming residency/eviction over async loader + VFS
    add_executable(test_mipmap_stream tests/test_mipmap_stream.c
        src/asset/mipmap_stream.c src/asset/async_loader.c src/asset/decode_pipeline.c src/asset/vfs.c
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
    # Only registered where it exercises the compiled backend: on metal/d3d12
    # builds it would request the OpenGL backend, which those backends reject
    # by design, and the guaranteed failure would turn the graphics-label rc
    # into an UNAVAILABLE evidence receipt. Those backends have their own
    # graphics contracts (test_rhi_metal_*, test_d3d12_*).
    if(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "vulkan" OR
       ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "opengl")
        add_test(NAME test_vulkan COMMAND test_vulkan
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        set_tests_properties(test_vulkan PROPERTIES TIMEOUT 180 LABELS graphics)
    endif()

    # rhi_swapchain_bench: swapchain frame benchmark producing a benchmark
    # receipt JSON (docs/rhi_benchmark_receipt_schema.md). SKIP_RETURN_CODE 77
    # marks runners without a display/GPU as skipped instead of failed.
    add_executable(rhi_swapchain_bench tools/rhi_swapchain_bench.c)
    target_include_directories(rhi_swapchain_bench PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(rhi_swapchain_bench PRIVATE engine m)
    engine_link_rhi_backend(rhi_swapchain_bench)
    # D3D12 lane: the backend macro is PRIVATE to engine_rhi_d3d12, so the
    # bench tool needs its own copy to pick the d3d12 create branch.
    if(ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL "d3d12")
        target_compile_definitions(rhi_swapchain_bench PRIVATE ENGINE_RHI_BACKEND_D3D12=1)
    endif()
    add_test(NAME rhi_swapchain_bench
        COMMAND rhi_swapchain_bench ${CMAKE_CURRENT_BINARY_DIR}/rhi_receipt_local.json)
    set_tests_properties(rhi_swapchain_bench PROPERTIES
        LABELS "graphics;benchmark" SKIP_RETURN_CODE 77 TIMEOUT 120)

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

    # R393: companion scene_state.bin save/load (extracted from main.c).
    add_executable(test_scene_state tests/test_scene_state.c
        src/scene/scene_state.c src/physics/physics.c src/physics/bvh.c
        src/math/math.c src/core/log.c)
    target_include_directories(test_scene_state PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_scene_state PRIVATE m)
    add_test(NAME test_scene_state COMMAND test_scene_state)

    # R393: hotreload shader read_file bounds (RHI stubs in test).
    add_executable(test_hotreload tests/test_hotreload.c
        src/asset/hotreload.c src/core/shader_io.c src/platform/filewatch.c
        src/platform/filewatch_backend.c src/core/log.c
        external/stb_image_impl.c)
    target_include_directories(test_hotreload PRIVATE ${TEST_INCLUDE_DIRS})
    # R433: filewatch.c compiles the Win32 backend only under
    # ENGINE_PLATFORM_WINDOWS; without it the #else pulls in <sys/inotify.h>.
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_hotreload PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_hotreload PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_hotreload PRIVATE kernel32)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_hotreload PRIVATE ENGINE_PLATFORM_MACOS=1)
        # filewatch.c FSEvents backend needs CoreServices/CoreFoundation.
        set_source_files_properties(src/platform/filewatch.c PROPERTIES
            COMPILE_OPTIONS "-Wno-error;-Wno-pedantic")
        target_link_libraries(test_hotreload PRIVATE
            "-framework CoreServices" "-framework CoreFoundation")
    endif()
    target_link_libraries(test_hotreload PRIVATE m)
    add_test(NAME test_hotreload COMMAND test_hotreload)

    add_executable(test_shader_io tests/test_shader_io.c src/core/shader_io.c src/core/log.c)
    target_include_directories(test_shader_io PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_shader_io PRIVATE m)
    add_test(NAME test_shader_io COMMAND test_shader_io)
    set_tests_properties(test_shader_io PROPERTIES
        LABELS "headless;platform_contract")

    add_executable(test_render_features tests/test_render_features.c
        src/renderer/render_features.c)
    target_include_directories(test_render_features PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_render_features PRIVATE m)
    add_test(NAME test_render_features COMMAND test_render_features)
    set_tests_properties(test_render_features PROPERTIES
        LABELS "headless;platform_contract")

    if(WIN32)
        add_executable(test_sl_dlss tests/test_sl_dlss.c src/renderer/sl_dlss.c)
        target_include_directories(test_sl_dlss PRIVATE ${TEST_INCLUDE_DIRS})
        add_test(NAME test_sl_dlss COMMAND test_sl_dlss)
    endif()

    add_executable(test_rt_trace tests/test_rt_trace.c src/renderer/rt_trace.c
        ${RHI_CORE_SOURCES} src/core/log.c)
    target_include_directories(test_rt_trace PRIVATE ${TEST_INCLUDE_DIRS})
    target_compile_definitions(test_rt_trace PRIVATE ENGINE_RHI_TEST=1)
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_rt_trace PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_rt_trace PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    elseif(ENGINE_PLATFORM STREQUAL "macos")
        target_compile_definitions(test_rt_trace PRIVATE ENGINE_PLATFORM_MACOS=1)
    endif()
    target_link_libraries(test_rt_trace PRIVATE engine_rhi_headless m)
    add_test(NAME test_rt_trace COMMAND test_rt_trace)
    set_tests_properties(test_rt_trace PROPERTIES
        LABELS "headless;platform_contract")

    # R387: mutation fuzzer for the BSCN/JSON loaders. Not registered as a test
    # (it is long-running and randomized); build it and run by hand under
    # ASan/UBSan, e.g. `./fuzz_scene_serial 25000 <seed>`.
    add_executable(fuzz_scene_serial EXCLUDE_FROM_ALL tests/fuzz_scene_serial.c
        src/scene/scene_serial.c src/ecs/ecs.c src/math/math.c src/core/log.c)
    target_include_directories(fuzz_scene_serial PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(fuzz_scene_serial PRIVATE m)

    # test_vfs: needs vfs.c + log.c
    add_executable(test_vfs tests/test_vfs.c src/asset/vfs.c src/core/log.c)
    target_include_directories(test_vfs PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_vfs PRIVATE m)
    add_test(NAME test_vfs COMMAND test_vfs)

    # R390: glTF loader input validation. Every attribute loop runs before the
    # first rhi_buffer_create, so the malformed-model cases reproduce headlessly
    # with the test's link-only RHI stubs.
    add_executable(test_asset_gltf tests/test_asset_gltf.c
        src/asset/asset.c src/asset/vfs.c src/animation/skeleton.c
        src/core/log.c src/math/math.c
        # R615: asset_scene_restore composes scene_serial.c's manifest
        # rebuild, which needs the ECS world for its loaders.
        src/scene/scene_serial.c src/ecs/ecs.c)
    target_include_directories(test_asset_gltf PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_asset_gltf PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    endif()
    target_link_libraries(test_asset_gltf PRIVATE stb_image m)
    add_test(NAME test_asset_gltf COMMAND test_asset_gltf)

    # R391: mutation fuzzer for the glTF loader. Same usage as the other fuzz_*
    # targets: EXCLUDE_FROM_ALL, run by hand under ASan/UBSan. Takes an optional
    # GLB seed path (default engine/assets/test.glb, relative to the repo root).
    add_executable(fuzz_asset_gltf EXCLUDE_FROM_ALL tests/fuzz_asset_gltf.c
        src/asset/asset.c src/asset/vfs.c src/animation/skeleton.c
        src/core/log.c src/math/math.c
        # R623: asset.c's R615 restore path references scene_serial.c's
        # manifest rebuild, which needs the ECS world (test_asset_gltf's
        # link line already carries both).
        src/scene/scene_serial.c src/ecs/ecs.c)
    target_include_directories(fuzz_asset_gltf PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(fuzz_asset_gltf PRIVATE m)

    # R392: mutation fuzzer for decode_pipeline (stbi + mip chain). Same usage
    # as the other fuzz_* targets: EXCLUDE_FROM_ALL, run by hand under ASan/UBSan.
    add_executable(fuzz_decode_image EXCLUDE_FROM_ALL tests/fuzz_decode_image.c
        src/asset/decode_pipeline.c src/core/log.c external/stb_image_impl.c)
    target_include_directories(fuzz_decode_image PRIVATE ${TEST_INCLUDE_DIRS})
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(fuzz_decode_image PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
        target_link_libraries(fuzz_decode_image PRIVATE pthread m)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(fuzz_decode_image PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(fuzz_decode_image PRIVATE kernel32)
    endif()

    # R388: mutation fuzzer for the PAK mount path. Same usage as
    # fuzz_scene_serial: build explicitly and run by hand under ASan/UBSan.
    add_executable(fuzz_vfs_pak EXCLUDE_FROM_ALL tests/fuzz_vfs_pak.c
        src/asset/vfs.c src/core/log.c)
    target_include_directories(fuzz_vfs_pak PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(fuzz_vfs_pak PRIVATE m)

    # R630: fuzz smoke — bounded deterministic runs of the manual fuzzers.
    # Labeled "fuzz" so default runs skip them (like "graphics"); the
    # ASan/UBSan CI job builds the targets explicitly and runs them under
    # sanitizers (the R623 "manual sanitizer evidence" boundary, automated).
    # Args are (iters, seed[, seed file]); scratch paths are pid-unique.
    add_test(NAME fuzz_scene_serial_smoke COMMAND fuzz_scene_serial 500 7)
    add_test(NAME fuzz_net_packet_smoke   COMMAND fuzz_net_packet 2000 11)
    add_test(NAME fuzz_decode_image_smoke COMMAND fuzz_decode_image 2000 13)
    add_test(NAME fuzz_vfs_pak_smoke      COMMAND fuzz_vfs_pak 2000 17)
    add_test(NAME fuzz_asset_gltf_smoke   COMMAND fuzz_asset_gltf 800 23
             "${CMAKE_SOURCE_DIR}/assets/test.glb")
    set_tests_properties(fuzz_scene_serial_smoke fuzz_net_packet_smoke
        fuzz_decode_image_smoke fuzz_vfs_pak_smoke fuzz_asset_gltf_smoke
        PROPERTIES LABELS "fuzz")

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
    if(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_cmd_buffer PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_cmd_buffer PRIVATE kernel32)
    endif()
    target_link_libraries(test_cmd_buffer PRIVATE m)
    add_test(NAME test_cmd_buffer COMMAND test_cmd_buffer)

    # test_profiler: needs profiler.c + time.c
    add_executable(test_profiler tests/test_profiler.c
        src/core/profiler.c src/platform/time.c)
    target_include_directories(test_profiler PRIVATE ${TEST_INCLUDE_DIRS})
    # R433: was unconditional ENGINE_PLATFORM_LINUX/_POSIX_C_SOURCE — broke
    # Windows/macOS builds; mirror the per-platform pattern used by test_task.
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_profiler PRIVATE ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_profiler PRIVATE ENGINE_PLATFORM_WINDOWS=1)
    endif()
    target_link_libraries(test_profiler PRIVATE m)
    add_test(NAME test_profiler COMMAND test_profiler)

    # test_lighting: needs lighting.c + math.c + log.c + RHI stubs
    add_executable(test_lighting tests/test_lighting.c
        src/renderer/lighting.c src/core/shader_io.c src/math/math.c src/core/log.c tests/rhi_stubs.c)
    target_include_directories(test_lighting PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_lighting PRIVATE m)
    add_test(NAME test_lighting COMMAND test_lighting)

    # test_occlusion_visibility: needs occlusion_cull.c + log.c + RHI stubs
    add_executable(test_occlusion_visibility tests/test_occlusion_visibility.c
        src/renderer/occlusion_cull.c src/core/shader_io.c src/core/log.c tests/rhi_stubs.c)
    target_include_directories(test_occlusion_visibility PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_occlusion_visibility PRIVATE m)
    add_test(NAME test_occlusion_visibility COMMAND test_occlusion_visibility)

    # R434: test_ibl — logic-level IBL bake-chain tests; ibl.c only, the fake
    # backend (RHI stubs + log capture) lives inside the test file itself.
    add_executable(test_ibl tests/test_ibl.c src/renderer/ibl.c)
    target_include_directories(test_ibl PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_ibl PRIVATE m)
    add_test(NAME test_ibl COMMAND test_ibl)

    # Per-object motion history contract: dense slot lookup, first-frame
    # invalidation, and generation-safe ID reuse.
    add_executable(test_motion_history tests/test_motion_history.c
        src/renderer/motion_history.c src/math/math.c)
    target_include_directories(test_motion_history PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_motion_history PRIVATE m)
    add_test(NAME test_motion_history COMMAND test_motion_history)

    # test_terrain: CPU-side terrain height sampling/modify/erode
    add_executable(test_terrain tests/test_terrain.c
        src/renderer/terrain.c src/core/shader_io.c src/math/math.c src/core/log.c tests/rhi_stubs.c)
    target_include_directories(test_terrain PRIVATE ${TEST_INCLUDE_DIRS})
    # R433: was unconditionally ENGINE_VULKAN=1 regardless of the configured
    # backend; the test is CPU-side (RHI stubs), so follow the option instead.
    if(ENGINE_VULKAN)
        target_compile_definitions(test_terrain PRIVATE ENGINE_VULKAN=1)
    endif()
    target_link_libraries(test_terrain PRIVATE m)
    add_test(NAME test_terrain COMMAND test_terrain)

    # test_indirect_draw: R482 grouped-upload validation (prefix sum > max_draws
    # must be rejected) — CPU-side; RHI buffer uploads are no-op stubs.
    add_executable(test_indirect_draw tests/test_indirect_draw.c
        src/renderer/indirect_draw.c src/core/shader_io.c src/core/log.c tests/rhi_stubs.c)
    target_include_directories(test_indirect_draw PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_indirect_draw PRIVATE m)
    add_test(NAME test_indirect_draw COMMAND test_indirect_draw)

    # test_particles: CPU-side fallback command construction for the GPU particle path
    add_executable(test_particles tests/test_particles.c)
    target_include_directories(test_particles PRIVATE ${TEST_INCLUDE_DIRS})
    add_test(NAME test_particles COMMAND test_particles)

    # test_input: input state machine & tracking
    add_executable(test_input tests/test_input.c
        src/platform/input.c)
    target_include_directories(test_input PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_input PRIVATE m)
    add_test(NAME test_input COMMAND test_input)

    # test_filewatch_backend: platform-agnostic backend selection policy.
    add_executable(test_filewatch_backend tests/test_filewatch_backend.c
        src/platform/filewatch_backend.c)
    target_include_directories(test_filewatch_backend PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_filewatch_backend PRIVATE m)
    add_test(NAME test_filewatch_backend COMMAND test_filewatch_backend)

    # R443: test_wayland — pure wl_output enumeration logic (wayland_output.h
    # is header-only and wayland-free), runs headless on any platform.
    add_executable(test_wayland tests/test_wayland.c)
    target_include_directories(test_wayland PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_wayland PRIVATE m)
    add_test(NAME test_wayland COMMAND test_wayland)

    add_executable(test_monitor_selection tests/test_monitor_selection.c)
    target_include_directories(test_monitor_selection PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_monitor_selection PRIVATE m)
    add_test(NAME test_monitor_selection COMMAND test_monitor_selection)

    # Plan B Task 2: logical-vs-drawable size semantics are locked into the
    # header-only platform_size.h helpers; the unit test runs headless and the
    # cmake contract test pins the four window backends to consume them.
    add_executable(test_platform_size_semantics
        tests/test_platform_size_semantics.c)
    target_include_directories(test_platform_size_semantics PRIVATE
        ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_platform_size_semantics PRIVATE m)
    add_test(NAME test_platform_size_semantics
        COMMAND test_platform_size_semantics)

    add_test(NAME test_platform_size_contract
        COMMAND ${CMAKE_COMMAND}
            -DSIZE_HEADER=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_size.h
            -DWIN32_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_win32.c
            -DX11_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_x11.c
            -DWAYLAND_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_wayland.c
            -DCOCOA_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window_cocoa.m
            -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_platform_size_contract.cmake)
    set_tests_properties(test_platform_size_contract PROPERTIES
        LABELS "platform_contract")
endif()
