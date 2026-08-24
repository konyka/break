# myui — widget core: widget base, layout, event dispatch, window +
# window manager, built-in widgets.
add_library(myui STATIC
  my_widget.c
  my_layout.c
  my_event_dispatch.c
  my_style.c
  my_theme.c
  my_animator.c
  my_window.c
  my_window_manager.c
  my_undo_stack.c
  my_undo_manager.c
  my_ui_loader.c
  my_widget_class.c
  my_widget_class_builtin.c
  my_image_loader.c
  my_stb_image.c
  widgets/my_button.c
  widgets/my_label.c
  widgets/my_edit.c
  widgets/my_checkbox.c
  widgets/my_slider.c
  widgets/my_progress_bar.c
  widgets/my_list_view.c
  widgets/my_image.c
  widgets/my_text_area.c
  widgets/my_scroll_bar.c
  widgets/my_dialog.c
  widgets/my_menu.c
  widgets/my_rich_label.c
  widgets/my_scroll_view.c
  widgets/my_node.c
  widgets/my_node_view.c
  my_css.c
)

target_include_directories(myui PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(myui PUBLIC myc myr mypal)

if(MYUI_UI_YAML)
  target_compile_definitions(myui PUBLIC MYUI_UI_YAML)
endif()

if(MYUI_IMAGE_STB)
  target_compile_definitions(myui PUBLIC MYUI_IMAGE_STB)
endif()

target_include_directories(myui PRIVATE ${CMAKE_SOURCE_DIR}/3rd)

# third-party single-header libs: relax warnings ONLY for these TUs
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
  set_source_files_properties(my_stb_image.c PROPERTIES
    COMPILE_OPTIONS "-Wno-error;-Wno-pedantic;-Wno-unused-function;-Wno-unused-parameter;-Wno-type-limits")
endif()
