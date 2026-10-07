# mypal — platform-neutral PAL core plus the deterministic dummy port.
# Native host ports are built by the engine integration layer; this target is
# intentionally headless so the reusable myui modules stay window-system free.
set(MYUI_PAL_SOURCES dummy/my_pal_dummy.c)
set(MYUI_PAL_DEFINES "")
set(MYUI_PAL_LIBS "")
set(MYUI_PAL_INCLUDES "")

if(MYUI_PAL STREQUAL "wayland")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(MYUI_PAL_WL REQUIRED wayland-client wayland-egl egl)
  find_program(WAYLAND_SCANNER_EXE wayland-scanner REQUIRED)
  execute_process(
      COMMAND ${WAYLAND_SCANNER_EXE} client-header
              /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml
              ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h)
  execute_process(
      COMMAND ${WAYLAND_SCANNER_EXE} public-code
              /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml
              ${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c)
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

if(MYUI_PAL STREQUAL "x11")
  find_package(X11 REQUIRED)
  find_package(PkgConfig QUIET)
  if(PkgConfig_FOUND)
    pkg_check_modules(MYUI_PAL_EGL QUIET egl)
  endif()
  set(MYUI_PAL_SOURCES x11/my_pal_x11.c)
  set(MYUI_PAL_DEFINES MYUI_PAL_X11=1)
  set(MYUI_PAL_LIBS ${X11_LIBRARIES})
  if(MYUI_PAL_EGL_FOUND)
    list(APPEND MYUI_PAL_LIBS ${MYUI_PAL_EGL_LIBRARIES})
  else()
    message(FATAL_ERROR "MYUI_PAL=x11 requires EGL (pkg-config egl)")
  endif()
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
