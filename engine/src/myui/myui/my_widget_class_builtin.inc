/**
 * @file my_widget_class_builtin.inc
 * @brief Declarative data table of the built-in widget classes (M24a).
 *
 * Pure data, no code: the consumer defines callback macros and expands
 * MYUI_BUILTIN_CLASSES / MYUI_PROPS_* / MYUI_EVENTS_* with them. Two
 * consumers share this file so the mapping exists exactly once:
 *  - src/myui/my_widget_class_builtin.c expands it into static
 *    my_widget_class_t tables;
 *  - tools/ui2c.c expands it to drive code generation (create call
 *    string + ordered property list).
 *
 * X row: X(tag, create_fn, create_str, PROPS_MACRO, EVENTS_MACRO)
 *  - tag:         XML tag / widget->widget_type string;
 *  - create_fn:   library-side factory adapter identifier (takes the
 *                 allocator);
 *  - create_str:  create call as a string, used by ui2c-generated code;
 *  - PROPS_MACRO: P(name, type, set_fn, get_fn) rows in application
 *                 order (NULL set_fn = read-only, NULL get_fn =
 *                 write-only);
 *  - EVENTS_MACRO: E("name") rows (documentation only).
 */
#ifndef MY_WIDGET_CLASS_BUILTIN_INC
#define MY_WIDGET_CLASS_BUILTIN_INC

#define MYUI_PROPS_WIDGET(P)
#define MYUI_EVENTS_WIDGET(E)

#define MYUI_PROPS_BUTTON(P) \
  P("text", MY_PROP_STRING, button_prop_set_text, button_prop_get_text)
#define MYUI_EVENTS_BUTTON(E) E("click")

#define MYUI_PROPS_LABEL(P)                          \
  P("text", MY_PROP_STRING, label_prop_set_text,     \
    label_prop_get_text)                             \
  P("align", MY_PROP_STRING, label_prop_set_align,   \
    label_prop_get_align)
#define MYUI_EVENTS_LABEL(E)

/* application order mirrors the former my_ui_loader make_edit */
#define MYUI_PROPS_EDIT(P)                                    \
  P("hint", MY_PROP_STRING, edit_prop_set_hint, NULL)         \
  P("password", MY_PROP_BOOL, edit_prop_set_password, NULL)   \
  P("readonly", MY_PROP_BOOL, edit_prop_set_readonly, NULL)   \
  P("max_len", MY_PROP_INT, edit_prop_set_max_len, NULL)      \
  P("text", MY_PROP_STRING, edit_prop_set_text, edit_prop_get_text)
#define MYUI_EVENTS_EDIT(E) \
  E("changed")              \
  E("activate")

#define MYUI_PROPS_CHECKBOX(P)                                  \
  P("text", MY_PROP_STRING, checkbox_prop_set_text,             \
    checkbox_prop_get_text)                                     \
  P("checked", MY_PROP_BOOL, checkbox_prop_set_checked,         \
    checkbox_prop_get_checked)                                  \
  P("value", MY_PROP_BOOL, checkbox_prop_set_checked,           \
    checkbox_prop_get_checked)
#define MYUI_EVENTS_CHECKBOX(E) E("changed")

#define MYUI_PROPS_SLIDER(P)                                  \
  P("min", MY_PROP_FLOAT, slider_prop_set_min,                \
    slider_prop_get_min)                                      \
  P("max", MY_PROP_FLOAT, slider_prop_set_max,                \
    slider_prop_get_max)                                      \
  P("step", MY_PROP_FLOAT, slider_prop_set_step, NULL)        \
  P("value", MY_PROP_FLOAT, slider_prop_set_value,            \
    slider_prop_get_value)
#define MYUI_EVENTS_SLIDER(E) E("changed")

#define MYUI_PROPS_PROGRESS_BAR(P) \
  P("value", MY_PROP_FLOAT, progress_bar_prop_set_value, \
    progress_bar_prop_get_value)
#define MYUI_EVENTS_PROGRESS_BAR(E)

/* application order mirrors the former my_ui_loader make_text_area */
#define MYUI_PROPS_TEXT_AREA(P)                                  \
  P("hint", MY_PROP_STRING, text_area_prop_set_hint, NULL)       \
  P("readonly", MY_PROP_BOOL, text_area_prop_set_readonly, NULL) \
  P("wrap", MY_PROP_BOOL, text_area_prop_set_wrap,               \
    text_area_prop_get_wrap)                                     \
  P("align", MY_PROP_STRING, text_area_prop_set_align,           \
    text_area_prop_get_align)                                    \
  P("max_len", MY_PROP_INT, text_area_prop_set_max_len, NULL)    \
  P("text", MY_PROP_STRING, text_area_prop_set_text,             \
    text_area_prop_get_text)
#define MYUI_EVENTS_TEXT_AREA(E) E("changed")

#define MYUI_PROPS_LIST_VIEW(P) \
  P("row_height", MY_PROP_INT, list_view_prop_set_row_height,  \
    list_view_prop_get_row_height)
#define MYUI_EVENTS_LIST_VIEW(E)

#define MYUI_PROPS_IMAGE(P)                             \
  P("src", MY_PROP_STRING, image_prop_set_src, NULL)    \
  P("scale", MY_PROP_STRING, image_prop_set_scale, NULL)
#define MYUI_EVENTS_IMAGE(E)

#define MYUI_PROPS_SCROLL_BAR(P)
#define MYUI_EVENTS_SCROLL_BAR(E) E("changed")

#define MYUI_BUILTIN_CLASSES(X)                                            \
  X("widget", create_widget, "my_widget_create(a, \"container\")",         \
    MYUI_PROPS_WIDGET, MYUI_EVENTS_WIDGET)                                 \
  X("button", create_button, "my_button_create(a, NULL)",                  \
    MYUI_PROPS_BUTTON, MYUI_EVENTS_BUTTON)                                 \
  X("label", create_label, "my_label_create(a, NULL)", MYUI_PROPS_LABEL,   \
    MYUI_EVENTS_LABEL)                                                     \
  X("edit", create_edit, "my_edit_create(a)", MYUI_PROPS_EDIT,             \
    MYUI_EVENTS_EDIT)                                                      \
  X("checkbox", create_checkbox, "my_checkbox_create(a, NULL)",            \
    MYUI_PROPS_CHECKBOX, MYUI_EVENTS_CHECKBOX)                             \
  X("slider", create_slider, "my_slider_create(a)", MYUI_PROPS_SLIDER,     \
    MYUI_EVENTS_SLIDER)                                                    \
  X("progress_bar", create_progress_bar, "my_progress_bar_create(a)",      \
    MYUI_PROPS_PROGRESS_BAR, MYUI_EVENTS_PROGRESS_BAR)                     \
  X("text_area", create_text_area, "my_text_area_create(a)",               \
    MYUI_PROPS_TEXT_AREA, MYUI_EVENTS_TEXT_AREA)                           \
  X("list_view", create_list_view, "my_list_view_create(a)",               \
    MYUI_PROPS_LIST_VIEW, MYUI_EVENTS_LIST_VIEW)                           \
  X("image", create_image, "my_image_create(a)", MYUI_PROPS_IMAGE,         \
    MYUI_EVENTS_IMAGE)                                                     \
  X("scroll_bar", create_scroll_bar, "my_scroll_bar_create(a)",            \
    MYUI_PROPS_SCROLL_BAR, MYUI_EVENTS_SCROLL_BAR)

#endif /* MY_WIDGET_CLASS_BUILTIN_INC */
