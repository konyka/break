add_library(dxx_core STATIC
  dxx_data.c
  dxx_theme.c
  views/nav_item.c
  views/topbar.c
  views/index_strip.c
  views/footer.c
  views/stock_item.c
  views/ztpool.c
  views/live_panels.c
  views/placeholder.c
  views/auth.c
  views/qx_chart.c
  views/qx_stats.c
)
target_include_directories(dxx_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(dxx_core PRIVATE ${CMAKE_SOURCE_DIR}/3rd)
target_link_libraries(dxx_core PUBLIC myui mypal myr myc mymvvm mymvvm_myui)

if(MYUI_BUILD_DEMOS)
  add_executable(dxx main.c)
  target_link_libraries(dxx PRIVATE dxx_core myui mymvvm mymvvm_myui)
  target_include_directories(dxx PRIVATE ${CMAKE_SOURCE_DIR}/3rd)
endif()
