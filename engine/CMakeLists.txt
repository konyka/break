cmake_minimum_required(VERSION 3.20)
project(PureCEngine LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform detection
option(ENGINE_ENABLE_WAYLAND "Enable native Wayland support (Linux only)" OFF)
option(ENGINE_ENABLE_IPO "Enable interprocedural optimization for Release builds when supported" ON)
# myui integration options
option(MYUI_FONT_STB "TrueType fonts via stb_truetype" ON)
option(MYUI_FONT_FREETYPE "Hinted fonts via FreeType when available" ON)
option(MYUI_IMAGE_STB "Image decode via stb_image" ON)
option(MYUI_UI_XML "XML UI loader" ON)
option(MYUI_BIDI "BiDi reorder + Arabic shaping via vendored SheenBidi" ON)

if(UNIX)
    if(APPLE)
        set(ENGINE_PLATFORM "macos")
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

if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
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

# R433: MSVC has no libm — provide an empty interface target so the many
# `target_link_libraries(... m)` below resolve to a no-op on Windows.
if(WIN32)
    add_library(m INTERFACE)
endif()

# R433: shaderc_shared ships no CMake package config; locate it explicitly
# instead of linking the bare name (which fails with unhelpful -l errors).
if(ENGINE_VULKAN OR ENGINE_PLATFORM STREQUAL "macos")
    find_library(SHADERC_LIB NAMES shaderc_shared)
    if(NOT SHADERC_LIB)
        message(FATAL_ERROR
            "shaderc_shared not found — install shaderc (e.g. libshaderc-dev / shaderc) "
            "or configure without -DENGINE_VULKAN=ON")
    endif()
endif()

# Engine library
add_library(engine STATIC
    src/core/log.c
    src/core/shader_io.c
    src/core/alloc.c
    src/core/pool.c
    src/core/string.c
    src/core/profiler.c
    src/platform/input.c
    src/platform/platform_text.c
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
    src/scene/scene_serial.c
    src/scene/scene_state.c
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

# Vendored stb single-header implementations are shared by the engine asset
# pipeline, myui's font/image backends, and the dxx application.
add_library(stb_truetype STATIC external/stb_truetype_impl.c)
target_include_directories(stb_truetype PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)

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
    src/myui/myr/my_line_break.c
    src/myui/mypal/my_timer.c
    src/myui/myui/my_widget.c
    src/myui/myui/my_layout.c
    src/myui/myui/my_event_dispatch.c
    src/myui/myui/my_style.c
    src/myui/myui/my_theme.c
    src/myui/myui/my_animator.c
    src/myui/myui/my_window.c
    src/myui/myui/my_window_manager.c
    src/myui/myui/my_xml.c
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

add_library(myui_core STATIC ${MYUI_CORE_SOURCES})
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
            COMPILE_DEFINITIONS SB_CONFIG_UNITY)
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
        target_compile_definitions(myui_core PUBLIC MYUI_FONT_FREETYPE=1)
        target_link_libraries(myui_core PUBLIC Freetype::Freetype)
    else()
        message(STATUS "myui: FreeType not found; CJK TTC fonts fall back to stb/bitmap")
    endif()
endif()
if(MYUI_IMAGE_STB)
    target_compile_definitions(myui_core PUBLIC MYUI_IMAGE_STB=1)
endif()
if(MYUI_UI_XML)
    target_compile_definitions(myui_core PUBLIC MYUI_UI_XML=1)
endif()

target_link_libraries(myui_core PUBLIC
    m
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
    endif()

    if(ENGINE_VULKAN)
        find_package(Vulkan REQUIRED)
        target_compile_definitions(engine PUBLIC ENGINE_VULKAN=1)
        if(ENGINE_ENABLE_WAYLAND)
            target_link_libraries(engine PRIVATE ${WAYLAND_LIBRARIES} ${XKB_LIBRARIES} ${Vulkan_LIBRARIES} ${SHADERC_LIB} dl pthread)
        else()
            target_link_libraries(engine PRIVATE ${X11_LIBRARIES} ${X11_Xrandr_LIB} ${Vulkan_LIBRARIES} ${SHADERC_LIB} dl pthread)
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

    target_link_libraries(engine PRIVATE user32 kernel32 shell32 imm32)
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
        ${SHADERC_LIB}
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework Metal"
        "-framework IOKit"
    )
endif()

# Executable
add_executable(engine_demo src/main.c)
target_link_libraries(engine_demo PRIVATE engine break_myui m)

# Vulkan test executable
add_executable(test_vulkan src/test_vulkan.c)
# R550-E: keep the VK validation gate live for the integration test in every
# build type. rhi_vk.c is compiled into the engine static lib, so the define
# cannot reach the backend from here; instead it arms the explicit
# rhi_vk_validation_set_enabled(true) call at the top of test_vulkan's main.
target_compile_definitions(test_vulkan PRIVATE ENGINE_VK_VALIDATION=1)
target_link_libraries(test_vulkan PRIVATE engine m)

add_executable(packer tools/packer.c)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(packer PRIVATE -Wno-format-truncation)
endif()
if(ENGINE_PLATFORM STREQUAL "windows")
    target_compile_definitions(packer PRIVATE _WIN32_WINNT=0x0601)
endif()

# Verification tool: mounts a .pak via VFS and compares against source files
add_executable(verify_pak tools/verify_pak.c src/asset/vfs.c src/core/log.c)
target_include_directories(verify_pak PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
if(ENGINE_PLATFORM STREQUAL "windows")
    target_compile_definitions(verify_pak PRIVATE _WIN32_WINNT=0x0601)
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

    add_executable(test_imgui_compat tests/test_imgui_compat.c
        src/ui/imgui_stubs.c
        src/myui/myr/my_vgcanvas_break_rhi.c)
    target_include_directories(test_imgui_compat PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_imgui_compat PRIVATE myui_core engine m)
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
        src/myui/mypal/break/my_pal_break.c)
    target_include_directories(test_myui_break_pal PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_break_pal PRIVATE myui_core engine m)
    add_test(NAME test_myui_break_pal COMMAND test_myui_break_pal)

    add_executable(test_myui_font tests/test_myui_font.c)
    target_include_directories(test_myui_font PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_font PRIVATE myui_core m)
    add_test(NAME test_myui_font COMMAND test_myui_font)

    add_executable(test_myui_mvvm tests/test_myui_mvvm.c)
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
    target_link_libraries(test_myui_vgcanvas_backend PRIVATE myui_core m)
    add_test(NAME test_myui_vgcanvas_backend COMMAND test_myui_vgcanvas_backend)

    add_executable(test_rhi_capabilities tests/test_rhi_capabilities.c
        src/rhi/rhi.c src/core/log.c)
    target_include_directories(test_rhi_capabilities PRIVATE ${TEST_INCLUDE_DIRS})
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(test_rhi_capabilities PRIVATE
            -ffunction-sections -fdata-sections)
        target_link_options(test_rhi_capabilities PRIVATE -Wl,--gc-sections)
    endif()
    add_test(NAME test_rhi_capabilities COMMAND test_rhi_capabilities)

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

    add_executable(test_myui_text_layout tests/test_myui_text_layout.c)
    target_include_directories(test_myui_text_layout PRIVATE
        ${TEST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/myui
    )
    target_link_libraries(test_myui_text_layout PRIVATE myui_core m)
    add_test(NAME test_myui_text_layout COMMAND test_myui_text_layout)

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
    add_test(NAME test_vulkan COMMAND test_vulkan
             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set_tests_properties(test_vulkan PROPERTIES TIMEOUT 180 LABELS graphics)

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
        src/asset/hotreload.c src/core/shader_io.c src/platform/filewatch.c src/core/log.c
        external/stb_image_impl.c)
    target_include_directories(test_hotreload PRIVATE ${TEST_INCLUDE_DIRS})
    # R433: filewatch.c compiles the Win32 backend only under
    # ENGINE_PLATFORM_WINDOWS; without it the #else pulls in <sys/inotify.h>.
    if(ENGINE_PLATFORM STREQUAL "linux")
        target_compile_definitions(test_hotreload PRIVATE ENGINE_PLATFORM_LINUX=1)
    elseif(ENGINE_PLATFORM STREQUAL "windows")
        target_compile_definitions(test_hotreload PRIVATE ENGINE_PLATFORM_WINDOWS=1)
        target_link_libraries(test_hotreload PRIVATE kernel32)
    endif()
    target_link_libraries(test_hotreload PRIVATE m)
    add_test(NAME test_hotreload COMMAND test_hotreload)

    add_executable(test_shader_io tests/test_shader_io.c src/core/shader_io.c src/core/log.c)
    target_include_directories(test_shader_io PRIVATE ${TEST_INCLUDE_DIRS})
    target_link_libraries(test_shader_io PRIVATE m)
    add_test(NAME test_shader_io COMMAND test_shader_io)

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
        src/core/log.c src/math/math.c)
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
        src/core/log.c src/math/math.c)
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
endif()
