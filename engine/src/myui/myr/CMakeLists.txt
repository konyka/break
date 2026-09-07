# myr — rendering abstraction: color/rect/dirty-rects, lcd interface + mem
# backend, vgcanvas interface + software rasterizer backend.
option(MYUI_GLES2 "Enable the GLES2 rendering backend when available" ON)
option(MYUI_GL_DESKTOP "Enable the desktop OpenGL rendering backend when available" ON)
option(MYUI_VULKAN "Enable the Vulkan rendering backend when available" OFF)

add_library(myr STATIC
  my_dirty_rects.c
  my_ui_metrics.c
  my_lcd_mem.c
  my_vgcanvas_quality_transaction.c
  my_vgcanvas_soft.c
  my_vgcanvas_gles2.c
  my_vgcanvas_vulkan.c
  my_vggeometry.c
  my_gl_real.c
  my_gl_desktop.c
  my_font.c
  my_font_stb.c
  my_font_ft.c
  my_bezier.c
  my_stb_truetype.c
  my_arabic_shape.c
  my_text_layout.c
  my_text_paragraph.c
  my_line_break.c
  my_syntax.c
)

find_package(Threads REQUIRED)

set(MYUI_THIRD_PARTY_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../external" CACHE PATH
  "myui third-party dependency directory")
set(MYUI_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/.." CACHE PATH
  "myui source root used by myui public headers")
set(MYUI_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." CACHE PATH
  "engine source root used by myui public headers")
target_include_directories(myr PUBLIC ${MYUI_SOURCE_DIR} ${MYUI_ENGINE_SOURCE_DIR})
target_include_directories(myr PRIVATE ${MYUI_THIRD_PARTY_DIR})
target_link_libraries(myr PUBLIC myc Threads::Threads)

# FreeType backend (M16): hinted glyphs; auto-OFF when freetype2 is absent
if(MYUI_FONT_FREETYPE)
  find_package(Freetype QUIET)
  if(Freetype_FOUND)
    set(MYUI_FREETYPE_FOUND ON)
    target_compile_definitions(myr PUBLIC MYUI_FONT_FREETYPE)
    target_link_libraries(myr PUBLIC Freetype::Freetype)
  else()
    message(STATUS "myui: freetype2 not found, MYUI_FONT_FREETYPE forced OFF")
  endif()
endif()

# HarfBuzz is optional and only valid with the FreeType face backend. Prefer a
# native CMake target, then use an imported pkg-config target as fallback.
if(MYUI_HARFBUZZ AND MYUI_FREETYPE_FOUND)
  find_package(harfbuzz CONFIG QUIET)
  if(harfbuzz_FOUND AND TARGET harfbuzz::harfbuzz)
    target_compile_definitions(myr PUBLIC MYUI_FONT_HARFBUZZ)
    target_link_libraries(myr PUBLIC harfbuzz::harfbuzz)
  else()
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
      pkg_check_modules(HARFBUZZ QUIET IMPORTED_TARGET harfbuzz)
    endif()
    if(HARFBUZZ_FOUND AND TARGET PkgConfig::HARFBUZZ)
      target_compile_definitions(myr PUBLIC MYUI_FONT_HARFBUZZ)
      target_link_libraries(myr PUBLIC PkgConfig::HARFBUZZ)
    else()
      message(STATUS "myui: HarfBuzz not found; OpenType shaping disabled")
    endif()
  endif()
endif()

# third-party single-header lib: relax warnings ONLY for this TU
# (stb_truetype is not -pedantic clean; the project's own bar is unchanged)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
  set_source_files_properties(my_stb_truetype.c PROPERTIES
    COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-Wno-unused-function")
endif()

if(MYUI_FONT_STB)
  target_compile_definitions(myr PUBLIC MYUI_FONT_STB)
endif()

# BiDi reorder + Arabic shaping (M11a): vendored SheenBidi unity TU,
# same warning relaxation as stb (third-party code, Apache-2.0)
if(MYUI_BIDI)
  set(SHEENBIDI_DIR ${MYUI_THIRD_PARTY_DIR}/SheenBidi)
  target_sources(myr PRIVATE ${SHEENBIDI_DIR}/Source/SheenBidi.c)
  target_compile_definitions(myr PUBLIC MYUI_BIDI)
  target_include_directories(myr PRIVATE
    ${SHEENBIDI_DIR}/Headers ${SHEENBIDI_DIR}/Source)
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    set_source_files_properties(${SHEENBIDI_DIR}/Source/SheenBidi.c
      PROPERTIES COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-Wno-unused-function;-Wno-unused-parameter;-Wno-implicit-fallthrough;-Wno-unused-value"
      COMPILE_DEFINITIONS SB_CONFIG_UNITY)
  else()
    set_source_files_properties(${SHEENBIDI_DIR}/Source/SheenBidi.c
      PROPERTIES COMPILE_DEFINITIONS SB_CONFIG_UNITY)
  endif()
endif()

# math library for the software rasterizer (floorf/ceilf/sqrtf)
if(NOT MSVC)
  target_link_libraries(myr PUBLIC m)
endif()

# optional GLES2 backend support (real GL table; mock tests work without it)
if(MYUI_GLES2 OR MYUI_GL_DESKTOP OR MYUI_VULKAN)
  find_package(PkgConfig QUIET)
endif()
if(MYUI_GLES2 AND PkgConfig_FOUND)
  pkg_check_modules(GLESV2 QUIET IMPORTED_TARGET glesv2)
endif()
if(MYUI_GLES2 AND GLESV2_FOUND AND TARGET PkgConfig::GLESV2)
  target_compile_definitions(myr PUBLIC MYUI_HAS_GLES2)
  target_link_libraries(myr PUBLIC PkgConfig::GLESV2)
  message(STATUS "myui: GLES2 backend enabled")
else()
  if(NOT MYUI_GLES2)
    message(STATUS "myui: GLES2 backend disabled")
  else()
    find_path(MYUI_GLES2_INCLUDE_DIR NAMES GLES2/gl2.h)
    find_library(MYUI_GLES2_LIBRARY NAMES GLESv2 opengles32)
    if(MYUI_GLES2_INCLUDE_DIR AND MYUI_GLES2_LIBRARY)
      target_compile_definitions(myr PUBLIC MYUI_HAS_GLES2)
      target_include_directories(myr PUBLIC ${MYUI_GLES2_INCLUDE_DIR})
      target_link_libraries(myr PUBLIC ${MYUI_GLES2_LIBRARY})
      message(STATUS "myui: GLES2 backend enabled (native SDK discovery)")
    else()
      message(STATUS "myui: GLES2 backend stubbed (glesv2 not found)")
    endif()
  endif()
endif()

# optional desktop OpenGL backend support (M25a)
if(MYUI_GL_DESKTOP)
  find_package(OpenGL QUIET)
endif()
if(MYUI_GL_DESKTOP AND OpenGL_FOUND AND TARGET OpenGL::GL)
  target_compile_definitions(myr PUBLIC MYUI_HAS_GL_DESKTOP)
  target_link_libraries(myr PUBLIC OpenGL::GL)
  message(STATUS "myui: desktop OpenGL backend enabled")
else()
  if(NOT MYUI_GL_DESKTOP)
    message(STATUS "myui: desktop OpenGL backend disabled")
  else()
    message(STATUS "myui: desktop OpenGL backend stubbed (gl not found)")
  endif()
endif()

# optional Vulkan backend support (M25b). The SPIR-V .inc files under
# vulkan_shaders/ are checked in; regenerate them explicitly with
# `cmake --build . --target vulkan_shaders_regen` (needs glslangValidator).
if(MYUI_VULKAN)
  find_package(Vulkan QUIET)
  if(NOT Vulkan_FOUND AND PkgConfig_FOUND)
    pkg_check_modules(VULKAN QUIET IMPORTED_TARGET vulkan)
  endif()
endif()
if(MYUI_VULKAN AND Vulkan_FOUND AND TARGET Vulkan::Vulkan)
  target_compile_definitions(myr PUBLIC MYUI_HAS_VULKAN)
  target_link_libraries(myr PUBLIC Vulkan::Vulkan)
  message(STATUS "myui: Vulkan backend enabled")
elseif(MYUI_VULKAN AND VULKAN_FOUND AND TARGET PkgConfig::VULKAN)
  target_compile_definitions(myr PUBLIC MYUI_HAS_VULKAN)
  target_link_libraries(myr PUBLIC PkgConfig::VULKAN)
  message(STATUS "myui: Vulkan backend enabled")
else()
  if(MYUI_VULKAN)
    message(STATUS "myui: Vulkan backend stubbed (vulkan not found)")
  else()
    message(STATUS "myui: Vulkan backend disabled")
  endif()
endif()

if(MYUI_VULKAN)
  set(MYUI_VULKAN_SHADER_DIR "${CMAKE_CURRENT_LIST_DIR}/vulkan_shaders" CACHE PATH
    "myui Vulkan GLSL shader directory")
  find_program(GLSLANG_VALIDATOR glslangValidator)
  if(GLSLANG_VALIDATOR)
    add_custom_target(vulkan_shaders_regen
      COMMAND ${CMAKE_COMMAND}
        -DGLSLANG_VALIDATOR=${GLSLANG_VALIDATOR}
        -DSHADER_DIR=${MYUI_VULKAN_SHADER_DIR}
        -DOUTPUT_DIR=${MYUI_VULKAN_SHADER_DIR}
        -P ${MYUI_VULKAN_SHADER_DIR}/generate_includes.cmake
      COMMENT "Regenerating Vulkan SPIR-V .inc files")
  else()
    message(STATUS
      "myui: Vulkan shader regeneration unavailable (glslangValidator not found); checked-in SPIR-V remains usable")
  endif()
endif()
