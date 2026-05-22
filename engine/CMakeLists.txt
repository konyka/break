cmake_minimum_required(VERSION 3.20)
project(PureCEngine LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform detection
if(UNIX)
    if(APPLE)
        set(ENGINE_PLATFORM "macos")
    else()
        find_package(X11 REQUIRED)
        set(ENGINE_PLATFORM "linux")
    endif()
elseif(WIN32)
    set(ENGINE_PLATFORM "windows")
endif()

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /WX /utf-8)
else()
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

# Sanitizers
option(ENGINE_USE_ASAN "Enable AddressSanitizer" OFF)
option(ENGINE_VULKAN "Use Vulkan backend instead of OpenGL" OFF)
if(ENGINE_USE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

# Engine library
add_library(engine STATIC
    src/core/log.c
    src/core/alloc.c
    src/core/string.c
    src/core/profiler.c
    src/platform/input.c
    src/platform/time.c
    src/platform/window_x11.c
    src/platform/filewatch.c
    src/math/math.c
    src/rhi/rhi.c
    src/renderer/camera.c
    src/renderer/cull.c
    src/renderer/skybox.c
    src/renderer/particles.c
    src/renderer/terrain.c
    src/renderer/lighting.c
    src/renderer/post_process.c
    src/renderer/ssao.c
    src/renderer/taa.c
    src/renderer/ssr.c
    src/renderer/gpucull.c
    src/renderer/dof.c
    src/renderer/cinematic.c
    src/renderer/volumetric.c
    src/renderer/tonemap.c
    src/renderer/fxaa.c
    src/renderer/ssgi.c
    src/renderer/lens_flare.c
    src/renderer/sharpen.c
    src/renderer/motion_blur.c
    src/renderer/contact_shadow.c
    src/renderer/sss.c
    src/asset/asset.c
    src/asset/hotreload.c
    src/asset/vfs.c
    src/ecs/ecs.c
    src/task/task.c
    src/physics/physics.c
    src/physics/character.c
    src/audio/audio.c
    src/ui/debug_ui.c
    src/ui/font.c
    src/animation/skeleton.c
    src/script/script.c
    src/engine.c
)

# glad.c is generated code — suppress pedantic warnings (void* to fn ptr casts)
add_library(glad STATIC external/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)
target_compile_options(glad PRIVATE -Wno-pedantic)

target_link_libraries(engine PRIVATE glad)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

if(ENGINE_PLATFORM STREQUAL "linux")
    target_compile_definitions(engine PUBLIC ENGINE_PLATFORM_LINUX=1 _POSIX_C_SOURCE=199309L)
    target_include_directories(engine PRIVATE ${X11_INCLUDE_DIRS})
    if(ENGINE_VULKAN)
        find_package(Vulkan REQUIRED)
        target_compile_definitions(engine PUBLIC ENGINE_VULKAN=1)
        target_link_libraries(engine PRIVATE ${X11_LIBRARIES} ${Vulkan_LIBRARIES} shaderc_shared dl pthread)
    else()
        target_link_libraries(engine PRIVATE ${X11_LIBRARIES} GL dl pthread)
    endif()
endif()

# Executable
add_executable(engine_demo src/main.c)
target_link_libraries(engine_demo PRIVATE engine m)

# Vulkan test executable
add_executable(test_vulkan src/test_vulkan.c)
target_link_libraries(test_vulkan PRIVATE engine m)

add_executable(packer tools/packer.c)
target_compile_options(packer PRIVATE -Wno-format-truncation)
