# mypal — platform-neutral PAL core plus explicit platform port selection.
# Unset or MYUI_PAL=dummy selects the deterministic CPU dummy; native failures
# never silently select it.
if(NOT DEFINED MYUI_PAL OR MYUI_PAL STREQUAL "")
  set(MYUI_PAL dummy)
endif()
if(MYUI_PAL STREQUAL "x11")
  message(FATAL_ERROR "X11 support was removed; use native Wayland")
endif()
set(MYUI_PAL_VALID_VALUES dummy wayland win32 cocoa)
if(NOT MYUI_PAL IN_LIST MYUI_PAL_VALID_VALUES)
  message(FATAL_ERROR
    "Unsupported MYUI_PAL='${MYUI_PAL}'; expected dummy, wayland, win32, or cocoa")
endif()
if(MYUI_PAL STREQUAL "win32" AND NOT WIN32)
  message(FATAL_ERROR "MYUI_PAL=win32 requires a Windows host")
endif()
if(MYUI_PAL STREQUAL "cocoa" AND NOT APPLE)
  message(FATAL_ERROR "MYUI_PAL=cocoa requires an Apple host")
endif()
if(MYUI_PAL STREQUAL "wayland" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(FATAL_ERROR "MYUI_PAL=wayland requires a Linux/Wayland target")
endif()

set(MYUI_PAL_SOURCES dummy/my_pal_dummy.c)
set(MYUI_PAL_DEFINES "")
set(MYUI_PAL_LIBS "")
set(MYUI_PAL_INCLUDES "")

if(MYUI_PAL STREQUAL "wayland")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(MYUI_PAL_WL REQUIRED wayland-client wayland-egl egl)
  find_program(WAYLAND_SCANNER_EXE wayland-scanner REQUIRED)
  find_file(WAYLAND_XDG_SHELL_XML xdg-shell.xml
      PATHS
          "${CMAKE_SYSROOT}/usr/share/wayland-protocols/stable/xdg-shell"
          /usr/share/wayland-protocols/stable/xdg-shell
          /usr/local/share/wayland-protocols/stable/xdg-shell
      NO_DEFAULT_PATH)
  if(NOT WAYLAND_XDG_SHELL_XML)
    message(FATAL_ERROR
        "Could not find xdg-shell.xml; set CMAKE_SYSROOT or install wayland-protocols")
  endif()
  execute_process(
      COMMAND ${WAYLAND_SCANNER_EXE} client-header
              ${WAYLAND_XDG_SHELL_XML}
              ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h
      RESULT_VARIABLE WAYLAND_HEADER_RESULT)
  if(NOT WAYLAND_HEADER_RESULT EQUAL 0)
    message(FATAL_ERROR "wayland-scanner client-header failed")
  endif()
  execute_process(
      COMMAND ${WAYLAND_SCANNER_EXE} public-code
              ${WAYLAND_XDG_SHELL_XML}
              ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c
      RESULT_VARIABLE WAYLAND_CODE_RESULT)
  if(NOT WAYLAND_CODE_RESULT EQUAL 0)
    message(FATAL_ERROR "wayland-scanner public-code failed")
  endif()
  set(MYUI_PAL_SOURCES wayland/my_pal_wayland.c
      ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c)
  set(MYUI_PAL_DEFINES MYUI_PAL_WAYLAND=1)
  set(MYUI_PAL_LIBS ${MYUI_PAL_WL_LIBRARIES})
  list(APPEND MYUI_PAL_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}
      ${MYUI_PAL_WL_INCLUDE_DIRS})
endif()

if(MYUI_PAL STREQUAL "win32" AND WIN32)
  set(MYUI_PAL_SOURCES win32/my_pal_win32.c)
  set(MYUI_PAL_DEFINES MYUI_PAL_WIN32=1)
  set(MYUI_PAL_LIBS gdi32 user32 opengl32)
elseif(MYUI_PAL STREQUAL "cocoa" AND APPLE)
  enable_language(OBJC)
  set(MYUI_PAL_SOURCES cocoa/my_pal_cocoa.m)
  set(MYUI_PAL_DEFINES MYUI_PAL_COCOA=1)
  set(MYUI_PAL_LIBS "-framework Cocoa" "-framework OpenGL")
endif()

add_library(mypal STATIC
  my_pal.c
  my_event.c
  my_pal_media.c
  my_pal_vulkan.c
  my_timer.c
  ${MYUI_PAL_SOURCES}
)
target_compile_definitions(mypal PUBLIC ${MYUI_PAL_DEFINES})
target_link_libraries(mypal PUBLIC ${MYUI_PAL_LIBS})

find_package(Threads REQUIRED)

set(MYUI_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/.." CACHE PATH
  "myui source root used by myui public headers")
set(MYUI_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." CACHE PATH
  "engine source root used by myui public headers")
target_include_directories(mypal PUBLIC ${MYUI_SOURCE_DIR} ${MYUI_ENGINE_SOURCE_DIR})
if(MYUI_PAL_INCLUDES)
  target_include_directories(mypal PUBLIC ${MYUI_PAL_INCLUDES})
endif()
target_link_libraries(mypal PUBLIC myc myr Threads::Threads)
