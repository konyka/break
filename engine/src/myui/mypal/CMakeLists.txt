# mypal — platform-neutral PAL core plus the deterministic dummy port.
# Native host ports are built by the engine integration layer; this target is
# intentionally headless so the reusable myui modules stay window-system free.
add_library(mypal STATIC
  my_pal.c
  my_event.c
  my_pal_media.c
  my_pal_vulkan.c
  my_timer.c
  dummy/my_pal_dummy.c
)

find_package(Threads REQUIRED)

set(MYUI_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/.." CACHE PATH
  "myui source root used by myui public headers")
set(MYUI_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." CACHE PATH
  "engine source root used by myui public headers")
target_include_directories(mypal PUBLIC ${MYUI_SOURCE_DIR} ${MYUI_ENGINE_SOURCE_DIR})
target_link_libraries(mypal PUBLIC myc myr Threads::Threads)
