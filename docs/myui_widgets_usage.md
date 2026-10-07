# MyUI Core Widgets Usage Guide

Runnable snippets for every core widget. All snippets mirror scenes in
`engine/tools/myui_widgets_demo.c`.

## Run the demo

```sh
cmake -S engine -B build -DENGINE_BUILD_TESTS=ON -DENGINE_VULKAN=OFF
cmake --build build --target myui_widgets_demo --parallel 2
mkdir -p /tmp/widgets && ./build/myui_widgets_demo /tmp/widgets
```

Renders one 320x180 PPM per scene and self-checks each frame.

## Fonts in headless scenes

Text rendering requires a loaded font. The soft vgcanvas treats
`set_font(NULL, size)` as size-only (no default face), so headless hosts
load one explicitly and pass it to `my_vgcanvas_set_font` before painting
(the demo loads Liberation Serif from the system font path). Chart-internal
text (axis ticks, legend, tooltip) still routes through the widget's own
`set_font(NULL, ...)` calls; injecting a face there is a tracked follow-up.

## Widgets

### Button

```c
my_widget_t* b = my_button_create(NULL, "Confirm");
b->rect = (my_rect_t){100, 70, 120, 40};
my_button_set_cooldown(b, 3000u);      /* click cooldown affordance */
bool cooling = my_button_is_cooling_down(b);
float p = my_button_cooldown_progress(b);
```

Variants scene: short / long labels / cooldown button side by side.
Animated buttons use the cooldown progress or drive properties through
`my_animator_animate` with a pal-backed main loop (see `my_animator.h`;
the headless demo renders the resting cooldown frame).

### Label and rich label

```c
my_widget_t* l = my_label_create(NULL, "Left aligned");
my_label_set_align(l, MY_TEXT_ALIGN_CENTER);   /* LEFT/CENTER/RIGHT */

my_widget_t* rich = my_rich_label_create(NULL);
my_rich_label_add_segment(rich, "Normal ", 0x1F2933FFu, false);
my_rich_label_add_segment(rich, "bold red ", 0xE85D75FFu, true);
my_rich_label_add_segment(rich, "and blue.", 0x3A86FFFFu, false);
my_rich_label_clear(rich);
```

### Checkbox (tri-state)

```c
my_widget_t* c = my_checkbox_create(NULL, "remember");
my_checkbox_set_checked(c, true);
my_checkbox_set_mixed(c, true);   /* third state */
bool on = my_checkbox_get_checked(c);
```

### Slider

```c
my_widget_t* s = my_slider_create(NULL);
my_slider_set_range(s, 0.0f, 100.0f);
my_slider_set_step(s, 5.0f);
my_slider_set_value(s, 65.0f);
float v = my_slider_get_value(s);
```

### Progress bar

```c
my_widget_t* p = my_progress_bar_create(NULL);
my_progress_bar_set_value(p, 0.8f);
```

Animated fill: drive `set_value` from any ticker (the demo renders three
deterministic frames at 0.2 / 0.6 / 1.0).

### Edit (single line)

```c
my_widget_t* e = my_edit_create(NULL);
my_edit_set_text(e, "user@example.com");
my_edit_set_hint(e, "search...");
my_edit_set_password(e, true);
my_edit_set_readonly(e, false);
const char* text = my_edit_get_text(e);
```

### Text area (multi-line)

```c
my_widget_t* a = my_text_area_create(NULL);
my_text_area_set_text(a, "line one\nline two");
my_text_area_set_hint(a, "notes...");
my_text_area_set_max_len(a, 512u);
my_text_area_set_readonly(a, true);
```

### Scroll bar

```c
my_widget_t* sb = my_scroll_bar_create(NULL);
my_scroll_bar_set_page_size(sb, 50.0f);
my_scroll_bar_set_value(sb, 0.4f);
```

Pair with `my_scroll_view_set_scroll_bar(sv, sb)` when hosting content.

### List view (adapter pattern)

```c
static size_t my_count(my_list_adapter_t* a) { return 8u; }
static my_widget_t* my_create_row(my_list_adapter_t* a) {
  return my_label_create(NULL, "");
}
static void my_bind_row(my_list_adapter_t* a, my_widget_t* row, size_t i) {
  my_label_set_text(row, "Row");   /* bind data index -> row */
}
static const my_list_adapter_vtable_t vtable = {
    my_count, my_create_row, my_bind_row, NULL /* variable height */};

my_widget_t* list = my_list_view_create(NULL);
list->rect.w = 300; list->rect.h = 160;    /* size BEFORE adapter */
my_list_view_set_row_height(list, 20);
my_list_view_set_adapter(list, &adapter_base);
my_list_view_refresh(list);
```

Rows are created lazily for the visible viewport and recycled. The MVVM
items binding installs an adapter automatically for view-model arrays.

### Menu and dialog

`my_menu_create` / `my_menu_add_item` / `my_menu_add_submenu` build popup
menus; `my_dialog_create` / `my_dialog_add_button` build dialogs. Both are
popup overlays that a window manager hosts (`my_menu_popup`,
`my_dialog_open`), so the headless demo does not render them; drive them
from a windowed host (see `my_window_manager.h`).

### Composing panels

`my_widget_add_child(parent, child)` takes ownership of one reference;
`my_widget_paint(root, vg)` translates, clips, paints the subtree, and
cascades to children — hosts are plain `my_widget_create` containers.

## Where to look next

- ECharts charts: `docs/myui_echart_usage.md` and `echarts_demo`.
- Layout system: `docs/myui_integration.md`.
