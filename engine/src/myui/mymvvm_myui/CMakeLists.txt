# mymvvm_myui — MVVM adapter for myui widgets (links myui + mymvvm).
add_library(mymvvm_myui STATIC
  my_widget_target.c
  my_mvvm.c
)

target_include_directories(mymvvm_myui PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mymvvm_myui PUBLIC myui mymvvm)
