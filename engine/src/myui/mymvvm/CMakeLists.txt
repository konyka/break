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

target_include_directories(mymvvm PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mymvvm PUBLIC myc)
