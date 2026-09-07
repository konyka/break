# mymvvm — MVVM core, GUI-free (depends only on myc).
add_library(mymvvm STATIC
  my_view_model.c
  my_view_model_array.c
  my_value_converter.c
  my_value_validator.c
  my_binding_rule.c
  my_binding_context.c
  my_data_binding.c
  my_command_binding.c
  my_items_binding.c
  my_condition_binding.c
  my_navigator.c
)

set(MYUI_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/.." CACHE PATH
  "myui source root used by myui public headers")
set(MYUI_ENGINE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." CACHE PATH
  "engine source root used by myui public headers")
target_include_directories(mymvvm PUBLIC ${MYUI_SOURCE_DIR} ${MYUI_ENGINE_SOURCE_DIR})
target_link_libraries(mymvvm PUBLIC myc)
