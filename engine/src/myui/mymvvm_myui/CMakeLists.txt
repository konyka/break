# mymvvm_myui — MVVM adapter for myui widgets (links myui + mymvvm).
add_library(mymvvm_myui STATIC
  my_widget_target.c
  my_mvvm.c
)

set(MYUI_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/.." CACHE PATH
  "myui source root used by myui public headers")
set(MYUI_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." CACHE PATH
  "engine source root used by myui public headers")
target_include_directories(mymvvm_myui PUBLIC ${MYUI_SOURCE_DIR} ${MYUI_ENGINE_SOURCE_DIR})
target_link_libraries(mymvvm_myui PUBLIC myui mymvvm)
