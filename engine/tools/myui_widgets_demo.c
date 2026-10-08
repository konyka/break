/**
 * @file myui_widgets_demo.c
 * @brief Headless MyUI widget demo: renders every core widget family to
 *        PPM files and self-checks each frame.
 *
 * Usage: myui_widgets_demo [output_dir]   (default: .)
 */
#include "myr/my_color.h"
#include "myr/my_font.h"
#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/my_widget.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_checkbox.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_list_view.h"
#include "myui/widgets/my_menu.h"
#include "myui/widgets/my_progress_bar.h"
#include "myui/widgets/my_rich_label.h"
#include "myui/widgets/my_scroll_bar.h"
#include "myui/widgets/my_slider.h"
#include "myui/widgets/my_text_area.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static my_font_t* g_font;
static size_t g_colored;

static void dump_ppm(const uint8_t* pixels, uint32_t w, uint32_t h,
                     uint32_t stride, const char* path) {
  FILE* f = fopen(path, "wb");
  uint32_t y;
  if (f == NULL) return;
  (void)fprintf(f, "P6\n%u %u\n255\n", w, h);
  for (y = 0u; y < h; y++) {
    uint32_t x;
    for (x = 0u; x < w; x++) {
      const uint8_t* p = pixels + y * stride + x * 4u;
      uint8_t rgb[3] = {p[2], p[1], p[0]};
      (void)fwrite(rgb, 1u, sizeof(rgb), f);
    }
  }
  (void)fclose(f);
}

static void render_widget(my_widget_t* widget, const char* dir,
                          const char* name) {
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 320u, 180u,
                                    MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  char path[512];
  const uint8_t* pixels;
  size_t i;
  if (lcd == NULL || canvas == NULL) {
    printf("FAIL %s (canvas)\n", name);
    exit(1);
  }
  widget->rect.x = 0;
  widget->rect.y = 0;
  widget->rect.w = 320;
  widget->rect.h = 180;
  if (my_vgcanvas_begin_frame(canvas, NULL) == MY_RET_OK) {
    my_vgcanvas_set_fill_color(canvas, my_color_from_rgba32(0xFFFFFFFFu));
    my_vgcanvas_fill_rect(canvas,
                          &(my_rectf_t){0, 0, 320.0f, 180.0f});
    my_vgcanvas_set_font(canvas, g_font, 13);
    my_widget_paint(widget, canvas);
  }
  (void)my_vgcanvas_end_frame(canvas);
  pixels = my_lcd_mem_get_buffer(lcd);
  g_colored = 0u;
  for (i = 0u; i < 320u * 180u * 4u; i += 4u)
    if (pixels[i] != 0xFFu || pixels[i + 1u] != 0xFFu ||
        pixels[i + 2u] != 0xFFu)
      g_colored++;
  (void)snprintf(path, sizeof(path), "%s/%s.ppm", dir, name);
  dump_ppm(pixels, 320u, 180u, my_lcd_mem_get_stride(lcd), path);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
}

static my_widget_t* host_with(my_widget_t* child, int32_t x, int32_t y,
                              int32_t w, int32_t h) {
  my_widget_t* host = my_widget_create(NULL, "host");
  if (host == NULL) exit(1);
  child->rect.x = x;
  child->rect.y = y;
  child->rect.w = w;
  child->rect.h = h;
  if (my_widget_add_child(host, child) != MY_RET_OK) exit(1);
  return host;
}

static void scene_button(const char* dir) {
  my_widget_t* button = my_button_create(NULL, "Confirm");
  render_widget(host_with(button, 100, 70, 120, 40), dir, "01_button");
}

static void scene_button_variants(const char* dir) {
  my_widget_t* host = my_widget_create(NULL, "host");
  my_widget_t* a = my_button_create(NULL, "Short");
  my_widget_t* b = my_button_create(NULL, "A fairly long button label");
  my_widget_t* c = my_button_create(NULL, "Cooldown");
  if (host == NULL) exit(1);
  a->rect.x = 20; a->rect.y = 20; a->rect.w = 90; a->rect.h = 30;
  b->rect.x = 20; b->rect.y = 60; b->rect.w = 200; b->rect.h = 30;
  c->rect.x = 20; c->rect.y = 100; c->rect.w = 120; c->rect.h = 30;
  (void)my_button_set_cooldown(c, 3000u);
  (void)my_widget_add_child(host, a);
  (void)my_widget_add_child(host, b);
  (void)my_widget_add_child(host, c);
  render_widget(host, dir, "02_button_variants");
}

static void scene_button_animated(const char* dir) {
  uint32_t frame;
  for (frame = 0u; frame < 3u; frame++) {
    my_widget_t* button = my_button_create(NULL, "Send");
    char name[64];
    (void)my_button_set_cooldown(button, 2000u);
    /* Cooldown progress is time-driven; the demo renders the resting
       state which already shows the cooldown affordance. */
    (void)snprintf(name, sizeof(name), "03_button_animated_%u", frame);
    render_widget(host_with(button, 110, 70, 100, 40), dir, name);
  }
}

static void scene_label_align(const char* dir) {
  my_widget_t* host = my_widget_create(NULL, "host");
  my_widget_t* left = my_label_create(NULL, "Left aligned");
  my_widget_t* center = my_label_create(NULL, "Centered");
  my_widget_t* right = my_label_create(NULL, "Right aligned");
  if (host == NULL) exit(1);
  left->rect.x = 10; left->rect.y = 30; left->rect.w = 300; left->rect.h = 20;
  center->rect.x = 10; center->rect.y = 80; center->rect.w = 300;
  center->rect.h = 20;
  right->rect.x = 10; right->rect.y = 130; right->rect.w = 300;
  right->rect.h = 20;
  (void)my_label_set_align(left, MY_TEXT_ALIGN_LEFT);
  (void)my_label_set_align(center, MY_TEXT_ALIGN_CENTER);
  (void)my_label_set_align(right, MY_TEXT_ALIGN_RIGHT);
  (void)my_widget_add_child(host, left);
  (void)my_widget_add_child(host, center);
  (void)my_widget_add_child(host, right);
  render_widget(host, dir, "04_label_align");
}

static void scene_rich_label(const char* dir) {
  my_widget_t* rich = my_rich_label_create(NULL);
  (void)my_rich_label_add_segment(rich, "Normal ", 0x1F2933FFu, false);
  (void)my_rich_label_add_segment(rich, "bold red ", 0xE85D75FFu, true);
  (void)my_rich_label_add_segment(rich, "and blue.", 0x3A86FFFFu, false);
  render_widget(host_with(rich, 20, 70, 280, 40), dir, "05_rich_label");
}

static void scene_checkbox(const char* dir) {
  my_widget_t* host = my_widget_create(NULL, "host");
  my_widget_t* a = my_checkbox_create(NULL, "Unchecked");
  my_widget_t* b = my_checkbox_create(NULL, "Checked");
  my_widget_t* c = my_checkbox_create(NULL, "Mixed");
  if (host == NULL) exit(1);
  a->rect.x = 30; a->rect.y = 30; a->rect.w = 200; a->rect.h = 24;
  b->rect.x = 30; b->rect.y = 78; b->rect.w = 200; b->rect.h = 24;
  c->rect.x = 30; c->rect.y = 126; c->rect.w = 200; c->rect.h = 24;
  (void)my_checkbox_set_checked(b, true);
  (void)my_checkbox_set_mixed(c, true);
  (void)my_widget_add_child(host, a);
  (void)my_widget_add_child(host, b);
  (void)my_widget_add_child(host, c);
  render_widget(host, dir, "06_checkbox_states");
}

static void scene_slider(const char* dir) {
  my_widget_t* host = my_widget_create(NULL, "host");
  my_widget_t* a = my_slider_create(NULL);
  my_widget_t* b = my_slider_create(NULL);
  if (host == NULL) exit(1);
  a->rect.x = 20; a->rect.y = 50; a->rect.w = 280; a->rect.h = 24;
  b->rect.x = 20; b->rect.y = 110; b->rect.w = 280; b->rect.h = 24;
  (void)my_slider_set_range(a, 0.0f, 100.0f);
  (void)my_slider_set_value(a, 30.0f);
  (void)my_slider_set_range(b, 0.0f, 1.0f);
  (void)my_slider_set_step(b, 0.25f);
  (void)my_slider_set_value(b, 0.75f);
  (void)my_widget_add_child(host, a);
  (void)my_widget_add_child(host, b);
  render_widget(host, dir, "07_slider");
}

static void scene_progress(const char* dir) {
  my_widget_t* host = my_widget_create(NULL, "host");
  my_widget_t* bars[3];
  static const float values[3] = {0.15f, 0.55f, 0.95f};
  size_t i;
  if (host == NULL) exit(1);
  for (i = 0u; i < 3u; i++) {
    bars[i] = my_progress_bar_create(NULL);
    bars[i]->rect.x = 20;
    bars[i]->rect.y = (int32_t)(30 + i * 50);
    bars[i]->rect.w = 280;
    bars[i]->rect.h = 18;
    (void)my_progress_bar_set_value(bars[i], values[i]);
    (void)my_widget_add_child(host, bars[i]);
  }
  render_widget(host, dir, "08_progress_bar");
}

static void scene_progress_animated(const char* dir) {
  static const float frames[3] = {0.2f, 0.6f, 1.0f};
  uint32_t frame;
  for (frame = 0u; frame < 3u; frame++) {
    my_widget_t* bar = my_progress_bar_create(NULL);
    char name[64];
    (void)my_progress_bar_set_value(bar, frames[frame]);
    (void)snprintf(name, sizeof(name), "09_progress_animated_%u", frame);
    render_widget(host_with(bar, 20, 80, 280, 20), dir, name);
  }
}

static void scene_edit(const char* dir) {
  my_widget_t* host = my_widget_create(NULL, "host");
  my_widget_t* plain = my_edit_create(NULL);
  my_widget_t* hinted = my_edit_create(NULL);
  my_widget_t* secret = my_edit_create(NULL);
  if (host == NULL) exit(1);
  plain->rect.x = 20; plain->rect.y = 30; plain->rect.w = 280;
  plain->rect.h = 26;
  hinted->rect.x = 20; hinted->rect.y = 76; hinted->rect.w = 280;
  hinted->rect.h = 26;
  secret->rect.x = 20; secret->rect.y = 122; secret->rect.w = 280;
  secret->rect.h = 26;
  (void)my_edit_set_text(plain, "user@example.com");
  (void)my_edit_set_hint(hinted, "search...");
  (void)my_edit_set_text(secret, "hunter2");
  (void)my_edit_set_password(secret, true);
  (void)my_widget_add_child(host, plain);
  (void)my_widget_add_child(host, hinted);
  (void)my_widget_add_child(host, secret);
  render_widget(host, dir, "10_edit");
}

static void scene_text_area(const char* dir) {
  my_widget_t* area = my_text_area_create(NULL);
  (void)my_text_area_set_text(area,
                              "Line one: multi-line editing.\n"
                              "Line two supports wrapping and scrolling.\n"
                              "Line three.");
  render_widget(host_with(area, 20, 30, 280, 120), dir, "11_text_area");
}

static void scene_scroll_bar(const char* dir) {
  my_widget_t* host = my_widget_create(NULL, "host");
  my_widget_t* half = my_scroll_bar_create(NULL);
  my_widget_t* full = my_scroll_bar_create(NULL);
  if (host == NULL) exit(1);
  half->rect.x = 300; half->rect.y = 20; half->rect.w = 12;
  half->rect.h = 140;
  full->rect.x = 306; full->rect.y = 20; full->rect.w = 12;
  full->rect.h = 140;
  (void)my_scroll_bar_set_page_size(half, 50.0f);
  (void)my_scroll_bar_set_value(half, 0.4f);
  (void)my_scroll_bar_set_page_size(full, 30.0f);
  (void)my_scroll_bar_set_value(full, 1.0f);
  (void)my_widget_add_child(host, half);
  (void)my_widget_add_child(host, full);
  render_widget(host, dir, "12_scroll_bar");
}

typedef struct demo_list_t {
  my_list_adapter_t base;
  size_t count;
} demo_list_t;

static size_t demo_list_count(my_list_adapter_t* adapter) {
  return ((demo_list_t*)adapter)->count;
}

static my_widget_t* demo_list_create_row(my_list_adapter_t* adapter) {
  (void)adapter;
  return my_label_create(NULL, "");
}

static void demo_list_bind_row(my_list_adapter_t* adapter,
                               my_widget_t* row, size_t index) {
  char text[64];
  (void)adapter;
  (void)snprintf(text, sizeof(text), "Row %zu - item", index);
  (void)my_label_set_text(row, text);
}

static void scene_list_view(const char* dir) {
  static const my_list_adapter_vtable_t vtable = {
      demo_list_count, demo_list_create_row, demo_list_bind_row, NULL};
  static demo_list_t adapter;
  my_widget_t* list = my_list_view_create(NULL);
  list->rect.x = 0;
  list->rect.y = 0;
  list->rect.w = 300;
  list->rect.h = 160;
  memset(&adapter, 0, sizeof(adapter));
  adapter.base.vtable = &vtable;
  adapter.count = 8u;
  (void)my_list_view_set_row_height(list, 20);
  if (my_list_view_set_adapter(list, &adapter.base) != MY_RET_OK) {
    printf("FAIL list adapter\n");
    exit(1);
  }
  render_widget(host_with(list, 10, 10, 300, 160), dir, "13_list_view");
}

static void scene_mix(const char* dir) {
  my_widget_t* host = my_widget_create(NULL, "panel");
  my_widget_t* title = my_label_create(NULL, "Demo panel");
  my_widget_t* button = my_button_create(NULL, "Apply");
  my_widget_t* check = my_checkbox_create(NULL, "remember");
  my_widget_t* slider = my_slider_create(NULL);
  my_widget_t* progress = my_progress_bar_create(NULL);
  if (host == NULL) exit(1);
  title->rect.x = 20; title->rect.y = 15; title->rect.w = 200;
  title->rect.h = 20;
  button->rect.x = 230; button->rect.y = 12; button->rect.w = 70;
  button->rect.h = 26;
  check->rect.x = 20; check->rect.y = 50; check->rect.w = 150;
  check->rect.h = 22;
  (void)my_checkbox_set_checked(check, true);
  slider->rect.x = 20; slider->rect.y = 90; slider->rect.w = 280;
  slider->rect.h = 22;
  (void)my_slider_set_range(slider, 0.0f, 100.0f);
  (void)my_slider_set_value(slider, 65.0f);
  progress->rect.x = 20; progress->rect.y = 130; progress->rect.w = 280;
  progress->rect.h = 16;
  (void)my_progress_bar_set_value(progress, 0.8f);
  (void)my_widget_add_child(host, title);
  (void)my_widget_add_child(host, button);
  (void)my_widget_add_child(host, check);
  (void)my_widget_add_child(host, slider);
  (void)my_widget_add_child(host, progress);
  render_widget(host, dir, "15_widget_mix");
}

typedef void (*scene_fn)(const char* dir);

int main(int argc, char** argv) {
  static const struct {
    const char* name;
    scene_fn fn;
  } scenes[] = {
      {"01_button", scene_button},
      {"02_button_variants", scene_button_variants},
      {"03_button_animated", scene_button_animated},
      {"04_label_align", scene_label_align},
      {"05_rich_label", scene_rich_label},
      {"06_checkbox_states", scene_checkbox},
      {"07_slider", scene_slider},
      {"08_progress_bar", scene_progress},
      {"09_progress_animated", scene_progress_animated},
      {"10_edit", scene_edit},
      {"11_text_area", scene_text_area},
      {"12_scroll_bar", scene_scroll_bar},
      {"13_list_view", scene_list_view},
      {"15_widget_mix", scene_mix}};
  const char* dir = argc > 1 ? argv[1] : ".";
  /* font candidates per platform (same table as myui_explorer): probe in
   * order — the first font that loads wins; no font = text scenes draw
   * nothing and the smoke check reports it. */
  static const char* font_candidates[] = {
#if defined(_WIN32)
      "C:\\Windows\\Fonts\\arial.ttf",
#elif defined(__APPLE__)
      "/System/Library/Fonts/Supplemental/Arial.ttf",
      "/Library/Fonts/Arial.ttf",
#else
      "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf",
      "/usr/share/fonts/truetype/liberation/LiberationSerif-Regular.ttf",
      /* R697: minimal cloud/WSL images ship DejaVu or Noto instead of
       * the GitHub-runner-preinstalled Liberation set. */
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
      "/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf",
#endif
      NULL};
  size_t fi;
  size_t failures = 0u;
  size_t i;
  size_t begin = argc > 2 ? (size_t)atoi(argv[2]) : 0u;
  size_t end = argc > 3 ? (size_t)atoi(argv[3])
                     : sizeof(scenes) / sizeof(scenes[0]);
  for (fi = 0u; g_font == NULL && font_candidates[fi] != NULL; fi++) {
    g_font = my_font_stb_create(NULL, font_candidates[fi], 4096u);
  }
  for (i = begin; i < end && i < sizeof(scenes) / sizeof(scenes[0]); i++) {
    g_colored = 0u;
    scenes[i].fn(dir);
    if (g_colored < 40u) {
      printf("FAIL %s (%zu colored pixels)\n", scenes[i].name, g_colored);
      failures++;
    } else {
      printf("OK   %s (%zu px)\n", scenes[i].name, g_colored);
    }
  }
  if (failures != 0u) {
    printf("%zu scene(s) FAILED\n", failures);
    return 1;
  }
  printf("all widget scenes rendered\n");
  return 0;
}
