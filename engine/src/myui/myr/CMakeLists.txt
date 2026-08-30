# myr — rendering abstraction: color/rect/dirty-rects, lcd interface + mem
# backend, vgcanvas interface + software rasterizer backend.
add_library(myr STATIC
  my_dirty_rects.c
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

set(MYUI_THIRD_PARTY_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../external" CACHE PATH
  "myui third-party dependency directory")
target_include_directories(myr PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(myr PRIVATE ${MYUI_THIRD_PARTY_DIR})
target_link_libraries(myr PUBLIC myc)

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
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(GLESV2 QUIET glesv2)
  pkg_check_modules(OPENGL QUIET gl)
endif()
if(GLESV2_FOUND)
  target_compile_definitions(myr PUBLIC MYUI_HAS_GLES2)
  target_include_directories(myr PUBLIC ${GLESV2_INCLUDE_DIRS})
  target_link_libraries(myr PUBLIC ${GLESV2_LIBRARIES})
  message(STATUS "myui: GLES2 backend enabled")
else()
  message(STATUS "myui: GLES2 backend stubbed (glesv2 not found)")
endif()

# optional desktop OpenGL backend support (M25a)
if(OPENGL_FOUND)
  target_compile_definitions(myr PUBLIC MYUI_HAS_GL_DESKTOP)
  target_include_directories(myr PUBLIC ${OPENGL_INCLUDE_DIRS})
  target_link_libraries(myr PUBLIC ${OPENGL_LIBRARIES})
  message(STATUS "myui: desktop OpenGL backend enabled")
else()
  message(STATUS "myui: desktop OpenGL backend stubbed (gl not found)")
endif()

# optional Vulkan backend support (M25b). The SPIR-V .inc files under
# vulkan_shaders/ are checked in; regenerate them explicitly with
# `cmake --build . --target vulkan_shaders_regen` (needs glslangValidator).
if(PkgConfig_FOUND)
  pkg_check_modules(VULKAN QUIET vulkan)
endif()
if(VULKAN_FOUND)
  target_compile_definitions(myr PUBLIC MYUI_HAS_VULKAN)
  target_include_directories(myr PUBLIC ${VULKAN_INCLUDE_DIRS})
  target_link_libraries(myr PUBLIC ${VULKAN_LIBRARIES})
  message(STATUS "myui: Vulkan backend enabled")
else()
  message(STATUS "myui: Vulkan backend stubbed (vulkan not found)")
endif()
find_program(GLSLANG_VALIDATOR glslangValidator)
if(GLSLANG_VALIDATOR)
  add_custom_target(vulkan_shaders_regen
    COMMAND python3 ${CMAKE_SOURCE_DIR}/tools/gen_vulkan_shaders.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Regenerating Vulkan SPIR-V .inc files")
endif()
