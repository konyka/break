# myui reusable subproject.
# Include this directory from any host project instead of adding individual
# modules and relying on the host's source-root layout.
cmake_minimum_required(VERSION 3.20)
project(myui LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(MYUI_FONT_STB "Enable stb_truetype font backend" ON)
option(MYUI_FONT_FREETYPE "Enable FreeType font backend when available" ON)
option(MYUI_IMAGE_STB "Enable stb_image image backend" ON)
option(MYUI_UI_YAML "Enable YAML UI loader" ON)
option(MYUI_BIDI "Enable BiDi and Arabic shaping" ON)
option(MYUI_HARFBUZZ "Enable HarfBuzz shaping when FreeType is available" ON)
option(MYUI_GLES2 "Enable the GLES2 rendering backend when available" ON)
option(MYUI_GL_DESKTOP "Enable the desktop OpenGL rendering backend when available" ON)
option(MYUI_VULKAN "Enable the Vulkan rendering backend when available" OFF)

set(MYUI_THIRD_PARTY_DIR "${CMAKE_CURRENT_LIST_DIR}/../../external" CACHE PATH
  "myui third-party dependency directory")

add_subdirectory(myc)
add_subdirectory(myr)
add_subdirectory(mypal)
add_subdirectory(myui)
add_subdirectory(mymvvm)
add_subdirectory(mymvvm_myui)
