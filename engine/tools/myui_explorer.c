#define _POSIX_C_SOURCE 200809L
/**
 * @file myui_explorer.c
 * @brief Interactive MyUI explorer: a live chart driven by real MyUI
 *        widgets, with switchable rendering backends (software / GL) and
 *        window systems (X11 / Wayland).
 *
 * Usage:
 *   myui_explorer [--platform x11|wayland] [--backend soft|gl]
 *   myui_explorer --selftest <dir>   # headless scripted frames
 *   myui_explorer --shot <file.ppm>  # render one frame and exit
 */
#include "explorer_internal.h"
#include "myr/my_color.h"
#include "myr/my_gl_desktop.h"
#include "myr/my_vgcanvas_gles2.h"
#include "myr/my_font.h"
#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/my_widget.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_checkbox.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_progress_bar.h"
#include "myui/widgets/my_slider.h"
#include "myui/widgets/my_chart.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EX_W 960
#define EX_H 560
#define CHART_X 0
#define CHART_Y 0
#define CHART_W 640
#define CHART_H EX_H
#define PANEL_X 648
#define PANEL_Y 8
#define PANEL_W 304

typedef struct {
  my_chart_mode_t mode;
  const char* short_name;
  const char* name;
} mode_entry_t;

static const mode_entry_t k_modes[] = {
    {MY_CHART_LINE, "line", "line"},
    {MY_CHART_BAR, "bar", "bar"},
    {MY_CHART_SCATTER, "sctr", "scatter"},
    {MY_CHART_PIE, "pie", "pie"},
    {MY_CHART_RADAR, "radr", "radar"},
    {MY_CHART_FUNNEL, "funl", "funnel"},
    {MY_CHART_HEATMAP, "heat", "heatmap"},
    {MY_CHART_BOXPLOT, "box", "boxplot"},
    {MY_CHART_CANDLESTICK, "k", "candlestick"},
    {MY_CHART_GAUGE, "gage", "gauge"},
    {MY_CHART_SANKEY, "sank", "sankey"},
    {MY_CHART_PARALLEL, "para", "parallel"},
    {MY_CHART_TREEMAP, "tree", "treemap"},
    {MY_CHART_GRAPH, "grph", "graph"},
    {MY_CHART_CALENDAR, "cal", "calendar"},
    {MY_CHART_THEME_RIVER, "rvr", "themeRiver"}};
#define MODE_COUNT (sizeof(k_modes) / sizeof(k_modes[0]))

typedef struct {
  float base[4][8];
  /* scaled values handed to the chart — the snapshot API borrows the
   * series value pointers, so they must outlive apply_state's frame. */
  float scaled[4][8];
  float scale;
  bool stacked;
  bool labels;
  bool legend;
  float anim;
  size_t zoom_start;
  size_t zoom_end;
  bool zoom_set;
} state_t;

struct app_t {
  state_t st;
  size_t mode;
  my_widget_t* chart;
  my_widget_t* mode_buttons[MODE_COUNT];
  my_widget_t* scale_slider;
  my_widget_t* anim_slider;
  my_widget_t* stacked_box;
  my_widget_t* labels_box;
  my_widget_t* legend_box;
  my_widget_t* random_button;
  my_widget_t* zoom_in;
  my_widget_t* zoom_out;
  my_widget_t* progress;
  my_widget_t* status;
  my_widget_t* panel;
  my_lcd_t* lcd;
  my_vgcanvas_t* vg;
  my_font_t* font;
  my_vgcanvas_t* gl_vg;
  char tooltip[96];
  int closing;
};

static void dump_ppm(const uint8_t* pixels, const char* path);
static void apply_state(app_t* app);
static void render_frame(app_t* app);
static void randomize(app_t* app);
static app_t* app_create(const char* font_path);

static void place(my_widget_t* w, int32_t x, int32_t y, int32_t cw,
                  int32_t ch) {
  w->rect.x = x;
  w->rect.y = y;
  w->rect.w = cw;
  w->rect.h = ch;
}

static void apply_state(app_t* app) {
  static const char* k_names[4] = {"Alpha", "Beta", "Gamma", "Delta"};
  static const char* k_cats[8] = {"Jan", "Feb", "Mar", "Apr",
                                  "May", "Jun", "Jul", "Aug"};
  my_chart_snapshot_t snap;
  my_chart_series_t series[4];
  bool visible[4];
  size_t i;
  for (i = 0u; i < 4u; i++) {
    size_t j;
    for (j = 0u; j < 8u; j++)
      app->st.scaled[i][j] = app->st.base[i][j] * app->st.scale;
    series[i].name = k_names[i];
    series[i].values = app->st.scaled[i];
    series[i].count = 8u;
    series[i].color = 0u;
    series[i].y_axis = (i == 3u && app->mode == 0u) ? 1u : 0u;
    series[i].show_labels = app->st.labels && app->mode <= 2u;
    visible[i] = true;
  }
  memset(&snap, 0, sizeof(snap));
  snap.mode = k_modes[app->mode].mode;
  snap.title = "MyUI explorer - press 1..9/q..v, R, wheel, drag sliders";
  snap.labels = k_cats;
  snap.label_count = 8u;
  snap.series = series;
  snap.series_visible = visible;
  snap.series_count = 4u;
  snap.stacked = app->st.stacked;
  snap.show_legend = app->st.legend;
  snap.tooltip_enabled = true;
  snap.zoom_set = app->st.zoom_set;
  snap.zoom_start = app->st.zoom_start;
  snap.zoom_end = app->st.zoom_end;
  if (my_chart_apply_snapshot(app->chart, &snap) != MY_RET_OK) {
    printf("snapshot failed\n");
    exit(1);
  }
  (void)my_chart_set_animation_progress(app->chart, app->st.anim);
  (void)my_progress_bar_set_value(app->progress, app->st.scale / 2.0f);
  {
    char line[128];
    (void)snprintf(line, sizeof(line), "%s  scale %.2f  anim %.0f%%",
                   k_modes[app->mode].name, (double)app->st.scale,
                   (double)(app->st.anim * 100.0f));
    (void)my_label_set_text(app->status, line);
  }
}

static void render_frame(app_t* app) {
  const uint8_t* pixels;
  (void)my_vgcanvas_begin_frame(app->vg, NULL);
  my_vgcanvas_set_fill_color(app->vg, my_color_from_rgba32(0xF0F2F5FFu));
  my_vgcanvas_fill_rect(app->vg, &(my_rectf_t){0, 0, (float)EX_W,
                                               (float)EX_H});
  my_vgcanvas_set_font(app->vg, app->font, 13);
  place(app->panel, 0, 0, EX_W, EX_H);
  my_widget_paint(app->panel, app->vg);
  app->chart->rect.x = CHART_X;
  app->chart->rect.y = CHART_Y;
  app->chart->rect.w = CHART_W;
  app->chart->rect.h = CHART_H;
  my_widget_paint(app->chart, app->vg);
  (void)my_vgcanvas_end_frame(app->vg);
  pixels = my_lcd_mem_get_buffer(app->lcd);
  if (app->tooltip[0] != '\0') {
    /* tooltip text is drawn by the chart; mirror it into the status area */
  }
  (void)pixels;
}

static void randomize(app_t* app) {
  size_t i, j;
  srand((unsigned)time(NULL));
  for (i = 0u; i < 4u; i++)
    for (j = 0u; j < 8u; j++)
      app->st.base[i][j] = 4.0f + (float)(rand() % 2800) / 100.0f;
}

static const char* font_candidates[] = {
#if defined(_WIN32)
    "C:\\Windows\\Fonts\\arial.ttf",
#elif defined(__APPLE__)
    "/System/Library/Fonts/Supplemental/Arial.ttf",
    "/Library/Fonts/Arial.ttf",
#else
    "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf",
    "/usr/share/fonts/truetype/liberation/LiberationSerif-Regular.ttf",
#endif
    NULL};

static const char* pick_font(void) {
  size_t i;
  FILE* f;
  for (i = 0u; font_candidates[i] != NULL; i++) {
    f = fopen(font_candidates[i], "rb");
    if (f != NULL) {
      fclose(f);
      return font_candidates[i];
    }
  }
  return NULL;
}

static app_t* app_create(const char* font_path) {
  app_t* app = (app_t*)calloc(1u, sizeof(*app));
  size_t i;
  if (app == NULL) exit(1);
  randomize(app);
  app->st.scale = 1.0f;
  app->st.legend = true;
  app->st.anim = 1.0f;
  app->st.zoom_end = 8u;
  app->lcd = my_lcd_mem_create(NULL, EX_W, EX_H, MY_PIXEL_FORMAT_BGRA8888);
  app->vg = my_vgcanvas_soft_create(NULL, app->lcd);
  if (font_path != NULL)
    app->font = my_font_stb_create(NULL, font_path, 4096u);
  app->chart = my_chart_create(NULL, MY_CHART_LINE);
  app->panel = my_widget_create(NULL, "panel");
  if (app->lcd == NULL || app->vg == NULL || app->chart == NULL ||
      app->panel == NULL)
    exit(1);
  for (i = 0u; i < MODE_COUNT; i++) {
    app->mode_buttons[i] = my_button_create(NULL, k_modes[i].short_name);
    place(app->mode_buttons[i], PANEL_X + 8 + (int32_t)(i % 8) * 36,
          PANEL_Y + 30 + (int32_t)(i / 8) * 32, 34, 28);
    (void)my_widget_add_child(app->panel, app->mode_buttons[i]);
  }
  {
    my_widget_t* cap1 = my_label_create(NULL, "data scale");
    my_widget_t* cap2 = my_label_create(NULL, "animation");
    place(cap1, PANEL_X + 8, PANEL_Y + 100, 120, 18);
    place(cap2, PANEL_X + 8, PANEL_Y + 170, 120, 18);
    (void)my_widget_add_child(app->panel, cap1);
    (void)my_widget_add_child(app->panel, cap2);
  }
  app->scale_slider = my_slider_create(NULL);
  place(app->scale_slider, PANEL_X + 8, PANEL_Y + 122, 280, 24);
  (void)my_slider_set_range(app->scale_slider, 0.5f, 2.0f);
  (void)my_slider_set_value(app->scale_slider, 1.0f);
  app->anim_slider = my_slider_create(NULL);
  place(app->anim_slider, PANEL_X + 8, PANEL_Y + 192, 280, 24);
  (void)my_slider_set_range(app->anim_slider, 0.0f, 1.0f);
  (void)my_slider_set_value(app->anim_slider, 1.0f);
  app->stacked_box = my_checkbox_create(NULL, "stacked");
  place(app->stacked_box, PANEL_X + 8, PANEL_Y + 230, 130, 22);
  app->labels_box = my_checkbox_create(NULL, "value labels");
  place(app->labels_box, PANEL_X + 150, PANEL_Y + 230, 140, 22);
  app->legend_box = my_checkbox_create(NULL, "legend");
  place(app->legend_box, PANEL_X + 8, PANEL_Y + 258, 130, 22);
  (void)my_checkbox_set_checked(app->legend_box, true);
  app->random_button = my_button_create(NULL, "Randomize (R)");
  place(app->random_button, PANEL_X + 8, PANEL_Y + 292, 130, 30);
  app->zoom_in = my_button_create(NULL, "Zoom +");
  place(app->zoom_in, PANEL_X + 150, PANEL_Y + 292, 64, 30);
  app->zoom_out = my_button_create(NULL, "Zoom -");
  place(app->zoom_out, PANEL_X + 224, PANEL_Y + 292, 64, 30);
  app->progress = my_progress_bar_create(NULL);
  place(app->progress, PANEL_X + 8, PANEL_Y + 336, 280, 18);
  app->status = my_label_create(NULL, "line");
  place(app->status, PANEL_X + 8, PANEL_Y + 370, 290, 60);
  (void)my_widget_add_child(app->panel, app->scale_slider);
  (void)my_widget_add_child(app->panel, app->anim_slider);
  (void)my_widget_add_child(app->panel, app->stacked_box);
  (void)my_widget_add_child(app->panel, app->labels_box);
  (void)my_widget_add_child(app->panel, app->legend_box);
  (void)my_widget_add_child(app->panel, app->random_button);
  (void)my_widget_add_child(app->panel, app->zoom_in);
  (void)my_widget_add_child(app->panel, app->zoom_out);
  (void)my_widget_add_child(app->panel, app->progress);
  (void)my_widget_add_child(app->panel, app->status);
  apply_state(app);
  return app;
}

static my_widget_t* hit(app_t* app, int32_t x, int32_t y) {
  size_t i;
  my_widget_t* widgets[16 + 9];
  size_t count = 0u;
  for (i = 0u; i < MODE_COUNT; i++) widgets[count++] = app->mode_buttons[i];
  widgets[count++] = app->random_button;
  widgets[count++] = app->zoom_in;
  widgets[count++] = app->zoom_out;
  for (i = 0u; i < count; i++) {
    my_widget_t* w = widgets[i];
    if (x >= w->rect.x && x < w->rect.x + w->rect.w && y >= w->rect.y &&
        y < w->rect.y + w->rect.h)
      return w;
  }
  return NULL;
}

static void on_widget_click(app_t* app, my_widget_t* w) {
  size_t i;
  for (i = 0u; i < MODE_COUNT; i++) {
    if (w == app->mode_buttons[i]) {
      app->mode = i;
      apply_state(app);
      return;
    }
  }
  if (w == app->random_button) {
    randomize(app);
    apply_state(app);
  } else if (w == app->zoom_in) {
    if (!app->st.zoom_set) {
      app->st.zoom_set = true;
      app->st.zoom_start = 1u;
      app->st.zoom_end = 7u;
    } else if (app->st.zoom_start + 1u < app->st.zoom_end) {
      app->st.zoom_start++;
      app->st.zoom_end--;
    }
    apply_state(app);
  } else if (w == app->zoom_out) {
    if (app->st.zoom_set) {
      app->st.zoom_start = app->st.zoom_start > 0u ? app->st.zoom_start - 1u
                                                   : 0u;
      if (app->st.zoom_end < 8u) app->st.zoom_end++;
      if (app->st.zoom_start == 0u && app->st.zoom_end >= 8u)
        app->st.zoom_set = false;
    }
    apply_state(app);
  }
}

static void on_toggle(app_t* app, my_widget_t* box) {
  if (box == app->stacked_box) {
    app->st.stacked = !app->st.stacked;
    (void)my_checkbox_set_checked(box, app->st.stacked);
  } else if (box == app->labels_box) {
    app->st.labels = !app->st.labels;
    (void)my_checkbox_set_checked(box, app->st.labels);
  } else if (box == app->legend_box) {
    app->st.legend = !app->st.legend;
    (void)my_checkbox_set_checked(box, app->st.legend);
  }
  apply_state(app);
}

static my_widget_t* hit_toggle(app_t* app, int32_t x, int32_t y) {
  my_widget_t* boxes[3] = {app->stacked_box, app->labels_box,
                           app->legend_box};
  size_t i;
  for (i = 0u; i < 3u; i++) {
    my_widget_t* w = boxes[i];
    if (x >= w->rect.x && x < w->rect.x + w->rect.w && y >= w->rect.y &&
        y < w->rect.y + w->rect.h)
      return w;
  }
  return NULL;
}

static bool hit_slider(my_widget_t* s, int32_t x, int32_t y) {
  return x >= s->rect.x && x < s->rect.x + s->rect.w && y >= s->rect.y &&
         y < s->rect.y + s->rect.h;
}

static float slider_value_at(my_widget_t* s, int32_t x) {
  float min = 0.0f;
  float max = 1.0f;
  float t;
  /* mirror the public range API via stored state in callers */
  (void)s;
  t = (float)(x - s->rect.x) / (float)(s->rect.w > 0 ? s->rect.w : 1);
  if (t < 0.0f) t = 0.0f;
  if (t > 1.0f) t = 1.0f;
  return min + (max - min) * t;
}

static void pointer(app_t* app, int32_t x, int32_t y, int kind) {
  my_event_t ev;
  my_widget_t* w;
  my_widget_t* box;
  if (x >= CHART_X && x < CHART_X + CHART_W) {
    ev = my_event_init(kind == 0 ? MY_EVENT_POINTER_MOVE
                                 : MY_EVENT_POINTER_DOWN);
    ev.u.pointer.x = x;
    ev.u.pointer.y = y;
    ev.u.pointer.button = 1u;
    (void)app->chart->vtable->on_event(app->chart, &ev);
    if (kind == 0) {
      if (my_chart_get_tooltip(app->chart, app->tooltip,
                               sizeof(app->tooltip)) == MY_RET_OK) {
        /* tooltip mirrored on the chart itself */
      } else {
        app->tooltip[0] = '\0';
      }
    }
    return;
  }
  if (kind != 1) return;
  w = hit(app, x, y);
  if (w != NULL) {
    on_widget_click(app, w);
    return;
  }
  box = hit_toggle(app, x, y);
  if (box != NULL) {
    on_toggle(app, box);
    return;
  }
  if (hit_slider(app->scale_slider, x, y)) {
    float t = slider_value_at(app->scale_slider, x);
    app->st.scale = 0.5f + 1.5f * t;
    (void)my_slider_set_value(app->scale_slider, app->st.scale);
    apply_state(app);
  } else if (hit_slider(app->anim_slider, x, y)) {
    float t = slider_value_at(app->anim_slider, x);
    app->st.anim = t;
    (void)my_slider_set_value(app->anim_slider, t);
    apply_state(app);
  }
}

static void wheel(app_t* app, int32_t delta) {
  if (!app->st.zoom_set) {
    app->st.zoom_set = true;
    app->st.zoom_start = 1u;
    app->st.zoom_end = 7u;
  } else if (delta > 0) {
    if (app->st.zoom_start + 1u < app->st.zoom_end) {
      app->st.zoom_start++;
      app->st.zoom_end--;
    }
  } else {
    app->st.zoom_start =
        app->st.zoom_start > 0u ? app->st.zoom_start - 1u : 0u;
    if (app->st.zoom_end < 8u) app->st.zoom_end++;
    if (app->st.zoom_start == 0u && app->st.zoom_end >= 8u)
      app->st.zoom_set = false;
  }
  apply_state(app);
}

static void key(app_t* app, int k) {
  if (k >= '1' && k <= '9') {
    app->mode = (size_t)(k - '1');
    apply_state(app);
    return;
  }
  if (k == '0') {
    app->mode = 9u;
    apply_state(app);
    return;
  }
  if (k == 's' || k == 'S') {
    render_frame(app);
    dump_ppm(my_lcd_mem_get_buffer(app->lcd),
             "/tmp/myui_explorer_shot.ppm");
    return;
  }
  if (k == 'r' || k == 'R') {
    randomize(app);
    apply_state(app);
  } else if (k == '+' || k == '=') {
    wheel(app, 1);
  } else if (k == '-') {
    wheel(app, -1);
  }
}

static void dump_ppm(const uint8_t* pixels, const char* path) {
  FILE* f = fopen(path, "wb");
  uint32_t y;
  if (f == NULL) return;
  (void)fprintf(f, "P6\n%d %d\n255\n", EX_W, EX_H);
  for (y = 0u; y < EX_H; y++) {
    uint32_t x;
    for (x = 0u; x < EX_W; x++) {
      const uint8_t* p = pixels + y * (EX_W * 4u) + x * 4u;
      uint8_t rgb[3] = {p[2], p[1], p[0]};
      (void)fwrite(rgb, 1u, sizeof(rgb), f);
    }
  }
  (void)fclose(f);
}

static size_t count_colored(app_t* app) {
  const uint8_t* pixels = my_lcd_mem_get_buffer(app->lcd);
  size_t i;
  size_t n = 0u;
  for (i = 0u; i < (size_t)EX_W * EX_H * 4u; i += 4u)
    if (pixels[i] != 0xF0u || pixels[i + 1u] != 0xF2u ||
        pixels[i + 2u] != 0xF5u)
      n++;
  return n;
}

static int run_selftest(const char* dir, const char* font_path) {
  app_t* app = app_create(font_path);
  char path[512];
  size_t failures = 0u;
  static const char* steps[6] = {"01_line", "02_mode_bar", "03_scale",
                                 "04_stacked", "05_random_hover",
                                 "06_zoom"};
  render_frame(app);
  (void)snprintf(path, sizeof(path), "%s/%s.ppm", dir, steps[0]);
  dump_ppm(my_lcd_mem_get_buffer(app->lcd), path);
  on_widget_click(app, app->mode_buttons[1]);
  render_frame(app);
  (void)snprintf(path, sizeof(path), "%s/%s.ppm", dir, steps[1]);
  dump_ppm(my_lcd_mem_get_buffer(app->lcd), path);
  app->st.scale = 2.0f;
  (void)my_slider_set_value(app->scale_slider, 2.0f);
  apply_state(app);
  render_frame(app);
  (void)snprintf(path, sizeof(path), "%s/%s.ppm", dir, steps[2]);
  dump_ppm(my_lcd_mem_get_buffer(app->lcd), path);
  on_toggle(app, app->stacked_box);
  render_frame(app);
  (void)snprintf(path, sizeof(path), "%s/%s.ppm", dir, steps[3]);
  dump_ppm(my_lcd_mem_get_buffer(app->lcd), path);
  randomize(app);
  apply_state(app);
  pointer(app, 320, 200, 0);
  render_frame(app);
  (void)snprintf(path, sizeof(path), "%s/%s.ppm", dir, steps[4]);
  dump_ppm(my_lcd_mem_get_buffer(app->lcd), path);
  wheel(app, 1);
  wheel(app, 1);
  render_frame(app);
  (void)snprintf(path, sizeof(path), "%s/%s.ppm", dir, steps[5]);
  dump_ppm(my_lcd_mem_get_buffer(app->lcd), path);
  if (count_colored(app) < 400u) {
    printf("FAIL selftest frame too empty\n");
    failures++;
  }
  printf(failures == 0u ? "selftest frames written\n" : "selftest FAILED\n");
  return failures == 0u ? 0 : 1;
}

static void gl_paint(app_t* app, my_vgcanvas_t* vg) {
  (void)my_vgcanvas_begin_frame(vg, NULL);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xF0F2F5FFu));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)EX_W, (float)EX_H});
  my_vgcanvas_set_font(vg, app->font, 13);
  place(app->panel, 0, 0, EX_W, EX_H);
  my_widget_paint(app->panel, vg);
  app->chart->rect.x = CHART_X;
  app->chart->rect.y = CHART_Y;
  app->chart->rect.w = CHART_W;
  app->chart->rect.h = CHART_H;
  my_widget_paint(app->chart, vg);
  (void)my_vgcanvas_end_frame(vg);
}

app_t* ex_app_create(void) {
  return app_create(pick_font());
}

void ex_app_destroy(app_t* app) {
  (void)app;  /* process-lifetime app; freed by OS exit */
}

void ex_frame_soft(app_t* app) {
  render_frame(app);
}

void ex_gl_vg_create(app_t* app) {
  if (app->gl_vg != NULL) return;
  app->gl_vg = my_vgcanvas_gles2_create(NULL, EX_W, EX_H);
  if (app->gl_vg == NULL) {
    const my_gl_t* gl = my_gl_desktop_default();
    if (gl != NULL)
      app->gl_vg = my_vgcanvas_gles2_create_with_gl(NULL, EX_W, EX_H, gl);
  }
}

void ex_frame_gl(app_t* app) {
  if (app->gl_vg == NULL) return;
  gl_paint(app, app->gl_vg);
}

const uint8_t* ex_lcd_pixels(app_t* app) {
  return my_lcd_mem_get_buffer(app->lcd);
}

uint32_t ex_lcd_stride(app_t* app) {
  return my_lcd_mem_get_stride(app->lcd);
}

void ex_pointer(app_t* app, int32_t x, int32_t y, int kind) {
  pointer(app, x, y, kind);
}

void ex_wheel(app_t* app, int dir) {
  wheel(app, dir);
}

void ex_key(app_t* app, int ch) {
  key(app, ch);
}


#if !defined(_WIN32) && !defined(__APPLE__) && \
    !defined(EX_EXPLORER_NO_X11) && !defined(EX_EXPLORER_NO_WAYLAND) && \
    !defined(MYUI_PAL_X11) && !defined(MYUI_PAL_WAYLAND)
#define EX_EXPLORER_GLSHOT_OK 1
#endif
#if defined(EX_EXPLORER_GLSHOT_OK)
#include <EGL/egl.h>
#include <GLES2/gl2.h>

static int run_glshot(const char* path, const char* font_path) {
  app_t* app;
  EGLDisplay display;
  EGLConfig config;
  EGLSurface surface;
  EGLContext context;
  EGLint count = 0;
  static const EGLint cfg_attribs[] = {
      EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
      EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE};
  static const EGLint pb_attribs[] = {
      EGL_WIDTH, EX_W, EGL_HEIGHT, EX_H, EGL_NONE};
  static const EGLint ctx_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                       EGL_NONE};
  uint8_t* rgba;
  uint8_t* rgb;
  my_vgcanvas_t* vg;
  uint32_t y;
  display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (display == EGL_NO_DISPLAY || !eglInitialize(display, NULL, NULL)) {
    printf("glshot: EGL init failed\n");
    return 1;
  }
  if (!eglBindAPI(EGL_OPENGL_ES_API) ||
      !eglChooseConfig(display, cfg_attribs, &config, 1, &count) || count < 1) {
    printf("glshot: no pbuffer config\n");
    return 1;
  }
  surface = eglCreatePbufferSurface(display, config, pb_attribs);
  if (surface == EGL_NO_SURFACE) {
    printf("glshot: pbuffer creation failed\n");
    return 1;
  }
  context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctx_attribs);
  if (context == EGL_NO_CONTEXT ||
      !eglMakeCurrent(display, surface, surface, context)) {
    printf("glshot: context failed\n");
    return 1;
  }
  vg = my_vgcanvas_gles2_create(NULL, EX_W, EX_H);
  if (vg == NULL) {
    printf("glshot: gles2 vgcanvas failed\n");
    return 1;
  }
  app = app_create(font_path);
  gl_paint(app, vg);
  rgba = (uint8_t*)malloc((size_t)EX_W * EX_H * 4u);
  rgb = (uint8_t*)malloc((size_t)EX_W * EX_H * 3u);
  if (rgba == NULL || rgb == NULL) return 1;
  glReadPixels(0, 0, EX_W, EX_H, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
  for (y = 0u; y < EX_H; y++) {
    uint32_t src = EX_H - 1u - y; /* GL origin is bottom-left */
    uint32_t x;
    for (x = 0u; x < EX_W; x++) {
      const uint8_t* p = rgba + ((size_t)src * EX_W + x) * 4u;
      uint8_t* q = rgb + ((size_t)y * EX_W + x) * 3u;
      q[0] = p[0];
      q[1] = p[1];
      q[2] = p[2];
    }
  }
  {
    FILE* f = fopen(path, "wb");
    if (f == NULL) return 1;
    (void)fprintf(f, "P6\n%d %d\n255\n", EX_W, EX_H);
    (void)fwrite(rgb, 1u, (size_t)EX_W * EX_H * 3u, f);
    (void)fclose(f);
  }
  printf("glshot written: %s\n", path);
  free(rgba);
  free(rgb);
  return 0;
}
#endif /* EX_EXPLORER_GLSHOT_OK */

#if defined(MYUI_PAL_X11) || defined(MYUI_PAL_WAYLAND)
#include "mypal/my_pal.h"

typedef struct {
  app_t* app;
  my_pal_t* pal;
  my_pal_window_t* win;
  my_pal_gl_t* gl;
  my_lcd_t* lcd;
  my_vgcanvas_t* soft_vg;
} pal_session_t;

static pal_session_t g_pal;
static my_pal_main_loop_t* g_pal_loop;

static my_ret_t pal_handler(void* ctx, my_pal_window_t* window,
                            const my_event_t* event) {
  (void)ctx; (void)window;
  if (event->type == MY_EVENT_POINTER_MOVE ||
      event->type == MY_EVENT_POINTER_DOWN) {
    ex_pointer(g_pal.app, event->u.pointer.x, event->u.pointer.y,
               event->type == MY_EVENT_POINTER_DOWN ? 1 : 0);
  } else if (event->type == MY_EVENT_POINTER_WHEEL) {
    ex_wheel(g_pal.app, event->u.pointer.delta > 0 ? 1 : -1);
  } else if (event->type == MY_EVENT_KEY_DOWN) {
    ex_key(g_pal.app, (int)event->u.key.key);
  } else if (event->type == MY_EVENT_QUIT) {
    g_pal.app->closing = 1;
    if (g_pal_loop != NULL) my_pal_main_loop_quit(g_pal_loop);
    return MY_RET_OK;
  }
  return MY_RET_OK;
}

static void pal_paint_frame(void) {
  if (g_pal.gl != NULL) {
    ex_frame_gl(g_pal.app);
    my_pal_gl_swap_buffers(g_pal.gl);
    return;
  }
  if (g_pal.soft_vg != NULL && g_pal.lcd != NULL) {
    (void)my_vgcanvas_begin_frame(g_pal.soft_vg, NULL);
    my_vgcanvas_set_fill_color(g_pal.soft_vg,
                               my_color_from_rgba32(0xF0F2F5FFu));
    my_vgcanvas_fill_rect(g_pal.soft_vg,
                          &(my_rectf_t){0, 0, (float)EX_W, (float)EX_H});
    my_vgcanvas_set_font(g_pal.soft_vg, g_pal.app->font, 13);
    place(g_pal.app->panel, 0, 0, EX_W, EX_H);
    my_widget_paint(g_pal.app->panel, g_pal.soft_vg);
    g_pal.app->chart->rect.x = CHART_X;
    g_pal.app->chart->rect.y = CHART_Y;
    g_pal.app->chart->rect.w = CHART_W;
    g_pal.app->chart->rect.h = CHART_H;
    my_widget_paint(g_pal.app->chart, g_pal.soft_vg);
    (void)my_vgcanvas_end_frame(g_pal.soft_vg);
    (void)my_lcd_end_frame(g_pal.lcd);
  }
}

static my_ret_t pal_timer(void* ctx) {
  (void)ctx;
  pal_paint_frame();
  return MY_RET_OK;
}

static int run_pal(app_t* app, int gl) {
  my_pal_t* pal = my_pal_create(NULL);
  my_pal_window_t* win;
  if (pal == NULL) {
    printf("my_pal_create failed\n");
    return 1;
  }
  memset(&g_pal, 0, sizeof(g_pal));
  g_pal.app = app;
  g_pal.pal = pal;
  (void)my_pal_set_event_handler(pal, pal_handler, NULL);
  win = my_pal_window_create(pal, EX_W, EX_H,
                             gl ? "MyUI explorer [pal/gl]"
                                : "MyUI explorer [pal/soft]");
  if (win == NULL) {
    my_pal_destroy(pal);
    return 1;
  }
  g_pal.win = win;
  (void)my_pal_window_show(win);
  if (gl) {
    g_pal.gl = my_pal_window_gl_enable(win);
    if (g_pal.gl != NULL && my_pal_gl_make_current(g_pal.gl) == MY_RET_OK)
      ex_gl_vg_create(app);
    if (app->gl_vg == NULL) g_pal.gl = NULL;
  }
  if (g_pal.gl == NULL) {
    g_pal.lcd = my_pal_window_get_lcd(win);
    g_pal.soft_vg = my_vgcanvas_soft_create(NULL, g_pal.lcd);
  }
  g_pal_loop = my_pal_main_loop_create(pal);
  if (g_pal_loop == NULL) return 1;
  (void)my_pal_main_loop_add_timer(g_pal_loop, pal_timer, NULL, 16u);
  while (!app->closing) {
    if (my_pal_main_loop_run(g_pal_loop) != MY_RET_OK) break;
  }
  my_pal_window_destroy(win);
  my_pal_destroy(pal);
  return 0;
}
#endif

#if defined(MYUI_PAL_X11) || defined(MYUI_PAL_WAYLAND)
static int run_palshot(const char* path, const char* font_path) {
  app_t* app = app_create(font_path);
  my_pal_t* pal = my_pal_create(NULL);
  my_pal_window_t* win;
  my_lcd_t* lcd;
  my_vgcanvas_t* vg;
  if (pal == NULL) {
    printf("palshot: my_pal_create failed\n");
    return 1;
  }
  win = my_pal_window_create(pal, EX_W, EX_H, "palshot");
  if (win == NULL) return 1;
  (void)my_pal_window_show(win);
  lcd = my_pal_window_get_lcd(win);
  vg = my_vgcanvas_soft_create(NULL, lcd);
  if (vg == NULL || lcd == NULL) return 1;
  (void)my_vgcanvas_begin_frame(vg, NULL);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xF0F2F5FFu));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)EX_W, (float)EX_H});
  my_vgcanvas_set_font(vg, app->font, 13);
  place(app->panel, 0, 0, EX_W, EX_H);
  my_widget_paint(app->panel, vg);
  app->chart->rect.x = CHART_X;
  app->chart->rect.y = CHART_Y;
  app->chart->rect.w = CHART_W;
  app->chart->rect.h = CHART_H;
  my_widget_paint(app->chart, vg);
  (void)my_vgcanvas_end_frame(vg);
  (void)my_lcd_end_frame(lcd);
  dump_ppm(my_lcd_get_buffer(lcd), path);
  printf("palshot written: %s\n", path);
  my_vgcanvas_destroy(vg);
  my_pal_window_destroy(win);
  my_pal_destroy(pal);
  return 0;
}
#endif

/* ---------------- window-system / backend runners ---------------- */

#if !defined(_WIN32) && !defined(__APPLE__) && \
    !defined(EX_EXPLORER_NO_X11) && !defined(MYUI_PAL_X11) && \
    !defined(MYUI_PAL_WAYLAND)
#define EX_HAVE_X11 1
#if !defined(EX_EXPLORER_NO_WAYLAND)
#define EX_HAVE_EGL_WL 1
#endif
#endif

#if defined(EX_HAVE_X11)
static void nap(void) {
  struct timespec ts = {0, 8000000L};
  nanosleep(&ts, NULL);
}
#endif

static int parse_args(int argc, char** argv, const char** platform,
                      const char** backend, const char* default_platform) {
  int i;
  *platform = default_platform;
  *backend = "soft";
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--platform") == 0 && i + 1 < argc) {
      *platform = argv[++i];
    } else if (strcmp(argv[i], "--backend") == 0 && i + 1 < argc) {
      *backend = argv[++i];
    }
  }
  if (strcmp(*platform, "x11") != 0 && strcmp(*platform, "wayland") != 0 &&
      strcmp(*platform, "win32") != 0 && strcmp(*platform, "cocoa") != 0) {
    printf("unknown platform %s (x11|wayland|win32|cocoa)\n", *platform);
    return 1;
  }
  if (strcmp(*backend, "soft") != 0 && strcmp(*backend, "gl") != 0) {
    printf("unknown backend %s (soft|gl)\n", *backend);
    return 1;
  }
  return 0;
}

#if defined(EX_EXPLORER_GLSHOT_OK)
static int run_glshot(const char* path, const char* font_path);
static int run_wayland_soft(app_t* app, const char* font_path);
static int run_gl(app_t* app, const char* font_path, int wayland);
#endif
#if defined(EX_HAVE_X11) && !defined(MYUI_PAL_X11) && !defined(MYUI_PAL_WAYLAND)
static int run_x11_soft(app_t* app, const char* font_path);
#endif

int main(int argc, char** argv) {
  static const char* default_platform =
#if defined(_WIN32)
      "win32";
#elif defined(__APPLE__)
      "cocoa";
#else
      "x11";
#endif
  const char* font_path = pick_font();
  const char* platform;
  const char* backend;
  int i;
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--selftest") == 0 && i + 1 < argc)
      return run_selftest(argv[i + 1], font_path);
    if (strcmp(argv[i], "--shot") == 0 && i + 1 < argc) {
      app_t* app = app_create(font_path);
      render_frame(app);
      dump_ppm(my_lcd_mem_get_buffer(app->lcd), argv[i + 1]);
      printf("shot written: %s\n", argv[i + 1]);
      return 0;
    }
    if (strcmp(argv[i], "--glshot") == 0 && i + 1 < argc) {
#if defined(EX_EXPLORER_GLSHOT_OK)
      return run_glshot(argv[i + 1], font_path);
#else
      printf("--glshot not supported in this build\n");
      return 1;
#endif
    }
#if defined(MYUI_PAL_X11) || defined(MYUI_PAL_WAYLAND)
    if (strcmp(argv[i], "--palshot") == 0 && i + 1 < argc)
      return run_palshot(argv[i + 1], font_path);
#endif
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      printf("usage: myui_explorer [--platform x11|wayland|win32|cocoa] "
             "[--backend soft|gl] | --selftest <dir> | --shot <file> | "
             "--glshot <file>\n");
      return 0;
    }
  }
  if (parse_args(argc, argv, &platform, &backend, default_platform) != 0)
    return 1;
  {
    app_t* app = app_create(font_path);
    int gl = strcmp(backend, "gl") == 0;
#if defined(MYUI_PAL_X11) || defined(MYUI_PAL_WAYLAND)
    if (strcmp(platform, "x11") == 0 || strcmp(platform, "wayland") == 0)
      return run_pal(app, gl);
    printf("platform %s not supported in this PAL build\n", platform);
    return 1;
#elif defined(_WIN32)
    if (strcmp(platform, "win32") == 0) return ex_run_win32(app, gl);
    printf("platform %s not supported in this build\n", platform);
    return 1;
#elif defined(__APPLE__)
    if (strcmp(platform, "cocoa") == 0) return ex_run_cocoa(app, gl);
    printf("platform %s not supported in this build\n", platform);
    return 1;
#else
#if !defined(EX_HAVE_X11)
    (void)gl;
    (void)app;
    printf("no interactive runner in this build; use --selftest/--shot\n");
    return 1;
#elif defined(EX_HAVE_EGL_WL)
    if (gl) return run_gl(app, font_path, strcmp(platform, "wayland") == 0);
    if (strcmp(platform, "wayland") == 0) return run_wayland_soft(app, font_path);
    return run_x11_soft(app, font_path);
#else
    if (gl || strcmp(platform, "wayland") == 0) {
      printf("platform %s/backend not supported in this build\n", platform);
      return 1;
    }
    return run_x11_soft(app, font_path);
#endif
#endif
  }
}

/* ---------------- X11 + software (XImage blit) ---------------- */
#if defined(EX_HAVE_X11)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#if !(defined(MYUI_PAL_X11) || defined(MYUI_PAL_WAYLAND))
static int run_x11_soft(app_t* app, const char* font_path) {
  Display* dpy;
  Window win;
  XImage* image = NULL;
  GC gc;
  Atom wm_delete;
  int screen;
  (void)font_path;
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
    printf("no X display; try --platform wayland or --selftest\n");
    return 1;
  }
  screen = DefaultScreen(dpy);
  win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen), 0, 0, EX_W, EX_H,
                            0, BlackPixel(dpy, screen), WhitePixel(dpy, screen));
  XStoreName(dpy, win, "MyUI explorer [x11/soft]");
  XSelectInput(dpy, win, ExposureMask | PointerMotionMask |
                             ButtonPressMask | KeyPressMask |
                             StructureNotifyMask);
  wm_delete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(dpy, win, &wm_delete, 1);
  XMapRaised(dpy, win);
  gc = XCreateGC(dpy, win, 0, NULL);
  for (;;) {
    XEvent ev;
    int dirty = 1;
    while (XPending(dpy)) {
      XNextEvent(dpy, &ev);
      if (ev.type == Expose) {
        dirty = 1;
      } else if (ev.type == ClientMessage &&
                 (Atom)ev.xclient.data.l[0] == wm_delete) {
        XCloseDisplay(dpy);
        return 0;
      } else if (ev.type == MotionNotify) {
        pointer(app, ev.xmotion.x, ev.xmotion.y, 0);
        dirty = 1;
      } else if (ev.type == ButtonPress) {
        if (ev.xbutton.button == Button4) wheel(app, 1);
        else if (ev.xbutton.button == Button5) wheel(app, -1);
        else if (ev.xbutton.button == Button1)
          pointer(app, ev.xbutton.x, ev.xbutton.y, 1);
        dirty = 1;
      } else if (ev.type == KeyPress) {
        KeySym k = XLookupKeysym(&ev.xkey, 0);
        if (k >= XK_space && k <= XK_asciitilde) key(app, (int)k);
        else if (k == XK_plus) key(app, '+');
        else if (k == XK_minus) key(app, '-');
        dirty = 1;
      }
    }
    if (dirty) {
      const uint8_t* pixels;
      render_frame(app);
      pixels = my_lcd_mem_get_buffer(app->lcd);
      if (image == NULL)
        image = XCreateImage(dpy, DefaultVisual(dpy, screen), 24, ZPixmap, 0,
                             (char*)pixels, EX_W, EX_H, 32, EX_W * 4);
      XPutImage(dpy, win, gc, image, 0, 0, 0, 0, EX_W, EX_H);
      XFlush(dpy);
    }
    nap();
  }
}
#endif

#endif /* EX_HAVE_X11 */
#if !(defined(MYUI_PAL_X11) || defined(MYUI_PAL_WAYLAND))
/* ---------------- Wayland (shared: input + soft runner) ---------------- */
#if defined(EX_HAVE_EGL_WL)
#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <wayland-egl.h>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "xdg-shell-client-protocol.h"

typedef struct {
  struct wl_display* display;
  struct wl_registry* registry;
  struct wl_compositor* compositor;
  struct wl_shm* shm;
  struct xdg_wm_base* wm_base;
  struct wl_seat* seat;
  struct wl_surface* surface;
  struct xdg_surface* xdg_surface;
  struct xdg_toplevel* toplevel;
  struct wl_buffer* buffer;
  void* shm_data;
  int configured;
  int closed;
} wl_state_t;

typedef struct {
  app_t* app;
  int32_t hot_x;
  int32_t hot_y;
} wl_input_t;

static wl_input_t g_wl_input;

static void wl_registry_global(void* data, struct wl_registry* r,
                               uint32_t name, const char* iface,
                               uint32_t version) {
  wl_state_t* wl = data;
  (void)version;
  if (strcmp(iface, "wl_compositor") == 0)
    wl->compositor = wl_registry_bind(r, name, &wl_compositor_interface, 1);
  else if (strcmp(iface, "wl_shm") == 0)
    wl->shm = wl_registry_bind(r, name, &wl_shm_interface, 1);
  else if (strcmp(iface, "xdg_wm_base") == 0)
    wl->wm_base = wl_registry_bind(r, name, &xdg_wm_base_interface, 1);
  else if (strcmp(iface, "wl_seat") == 0)
    wl->seat = wl_registry_bind(r, name, &wl_seat_interface, 1);
}

static const struct wl_registry_listener wl_registry_listener = {
    .global = wl_registry_global,
    .global_remove = NULL};

static void wm_base_ping(void* data, struct xdg_wm_base* base,
                         uint32_t serial) {
  (void)data;
  xdg_wm_base_pong(base, serial);
}
static const struct xdg_wm_base_listener wm_base_listener = {
    .ping = wm_base_ping};

static void xdg_configure(void* data, struct xdg_surface* surf,
                          uint32_t serial) {
  wl_state_t* wl = data;
  (void)surf;
  xdg_surface_ack_configure(wl->xdg_surface, serial);
  wl->configured = 1;
}
static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_configure};

static void toplevel_configure(void* data, struct xdg_toplevel* t,
                               int32_t width, int32_t height,
                               struct wl_array* states) {
  (void)data; (void)t; (void)width; (void)height; (void)states;
}
static void toplevel_close(void* data, struct xdg_toplevel* t) {
  (void)t;
  ((wl_state_t*)data)->closed = 1;
}
static const struct xdg_toplevel_listener toplevel_listener = {
    .configure = toplevel_configure, .close = toplevel_close};

static void pointer_enter(void* data, struct wl_pointer* p, uint32_t serial,
                          struct wl_surface* s, wl_fixed_t sx, wl_fixed_t sy) {
  (void)p; (void)serial; (void)s;
  g_wl_input.hot_x = wl_fixed_to_int(sx);
  g_wl_input.hot_y = wl_fixed_to_int(sy);
  (void)data;
}
static void pointer_leave(void* data, struct wl_pointer* p, uint32_t serial,
                          struct wl_surface* s) {
  (void)data; (void)p; (void)serial; (void)s;
}
static void pointer_motion(void* data, struct wl_pointer* p, uint32_t time,
                           wl_fixed_t sx, wl_fixed_t sy) {
  (void)data; (void)p; (void)time;
  g_wl_input.hot_x = wl_fixed_to_int(sx);
  g_wl_input.hot_y = wl_fixed_to_int(sy);
  pointer(g_wl_input.app, g_wl_input.hot_x, g_wl_input.hot_y, 0);
}
static void pointer_button(void* data, struct wl_pointer* p, uint32_t serial,
                           uint32_t time, uint32_t button, uint32_t state) {
  (void)data; (void)p; (void)serial; (void)time;
  if (state == WL_POINTER_BUTTON_STATE_PRESSED && button == BTN_LEFT)
    pointer(g_wl_input.app, g_wl_input.hot_x, g_wl_input.hot_y, 1);
}
static void pointer_axis(void* data, struct wl_pointer* p, uint32_t time,
                         uint32_t axis, wl_fixed_t value) {
  (void)data; (void)p; (void)time; (void)axis;
  wheel(g_wl_input.app, wl_fixed_to_int(value) > 0 ? -1 : 1);
}
static const struct wl_pointer_listener pointer_listener = {
    .enter = pointer_enter, .leave = pointer_leave,
    .motion = pointer_motion, .button = pointer_button,
    .axis = pointer_axis};

static void keymap(void* data, struct wl_keyboard* k, uint32_t format,
                   int32_t fd, uint32_t size) {
  (void)data; (void)k; (void)format; (void)fd; (void)size;
}
static void kbd_enter(void* data, struct wl_keyboard* k, uint32_t serial,
                      struct wl_surface* s, struct wl_array* keys) {
  (void)data; (void)k; (void)serial; (void)s; (void)keys;
}
static void kbd_leave(void* data, struct wl_keyboard* k, uint32_t serial,
                      struct wl_surface* s) {
  (void)data; (void)k; (void)serial; (void)s;
}
static void key_event(void* data, struct wl_keyboard* k, uint32_t serial,
                      uint32_t time, uint32_t key_code, uint32_t state) {
  (void)data; (void)k; (void)serial; (void)time;
  if (state == WL_KEYBOARD_KEY_STATE_PRESSED) {
    int ch = 0;
    if (key_code >= KEY_1 && key_code <= KEY_9)
      ch = '1' + (int)(key_code - KEY_1);
    else if (key_code == KEY_0) ch = '0';
    else if (key_code >= KEY_A && key_code <= KEY_Z)
      ch = 'a' + (int)(key_code - KEY_A);
    else if (key_code == KEY_MINUS) ch = '-';
    else if (key_code == KEY_EQUAL) ch = '=';
    if (ch != 0) key(g_wl_input.app, ch);
  }
}
static void kbd_modifiers(void* data, struct wl_keyboard* k, uint32_t serial,
                          uint32_t depressed, uint32_t latched,
                          uint32_t locked, uint32_t group) {
  (void)data; (void)k; (void)serial; (void)depressed; (void)latched;
  (void)locked; (void)group;
}
static void kbd_repeat(void* data, struct wl_keyboard* k, int32_t rate,
                       int32_t delay) {
  (void)data; (void)k; (void)rate; (void)delay;
}
static const struct wl_keyboard_listener keyboard_listener = {
    .keymap = keymap, .enter = kbd_enter, .leave = kbd_leave,
    .key = key_event, .modifiers = kbd_modifiers, .repeat_info = kbd_repeat};

static void seat_capabilities(void* data, struct wl_seat* seat,
                              uint32_t caps) {
  (void)data;
  if ((caps & WL_SEAT_CAPABILITY_POINTER) != 0u) {
    struct wl_pointer* p = wl_seat_get_pointer(seat);
    wl_pointer_add_listener(p, &pointer_listener, NULL);
  }
  if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) != 0u) {
    struct wl_keyboard* kb = wl_seat_get_keyboard(seat);
    wl_keyboard_add_listener(kb, &keyboard_listener, NULL);
  }
}
static const struct wl_seat_listener seat_listener = {
    .capabilities = seat_capabilities};

static void wl_registry_init(wl_state_t* wl) {
  wl->registry = wl_display_get_registry(wl->display);
  wl_registry_add_listener(wl->registry, &wl_registry_listener, wl);
  wl_display_roundtrip(wl->display);
}

static void wl_common_setup(wl_state_t* wl, app_t* app, const char* title) {
  xdg_wm_base_add_listener(wl->wm_base, &wm_base_listener, wl);
  if (wl->seat != NULL) {
    g_wl_input.app = app;
    wl_seat_add_listener(wl->seat, &seat_listener, wl);
  }
  wl->surface = wl_compositor_create_surface(wl->compositor);
  wl->xdg_surface = xdg_wm_base_get_xdg_surface(wl->wm_base, wl->surface);
  xdg_surface_add_listener(wl->xdg_surface, &xdg_surface_listener, wl);
  wl->toplevel = xdg_surface_get_toplevel(wl->xdg_surface);
  xdg_toplevel_add_listener(wl->toplevel, &toplevel_listener, wl);
  xdg_toplevel_set_title(wl->toplevel, title);
  wl_surface_commit(wl->surface);
  while (!wl->configured)
    if (wl_display_dispatch(wl->display) < 0) exit(1);
}

static int wl_shm_buffer(wl_state_t* wl) {
  int fd;
  char name[] = "/tmp/myui-explorer-XXXXXX";
  size_t size = (size_t)EX_W * EX_H * 4u;
  struct wl_shm_pool* pool;
  fd = mkstemp(name);
  if (fd < 0) return 1;
  (void)unlink(name);
  if (ftruncate(fd, (off_t)size) != 0) {
    close(fd);
    return 1;
  }
  wl->shm_data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (wl->shm_data == MAP_FAILED) {
    close(fd);
    return 1;
  }
  pool = wl_shm_create_pool(wl->shm, fd, (int32_t)size);
  wl->buffer = wl_shm_pool_create_buffer(pool, 0, EX_W, EX_H, EX_W * 4,
                                         WL_SHM_FORMAT_XRGB8888);
  wl_shm_pool_destroy(pool);
  close(fd);
  return 0;
}

static int run_wayland_soft(app_t* app, const char* font_path) {
  wl_state_t wl;
  (void)font_path;
  memset(&wl, 0, sizeof(wl));
  wl.display = wl_display_connect(NULL);
  if (wl.display == NULL) {
    printf("no wayland compositor; try --platform x11 or --selftest\n");
    return 1;
  }
  wl_registry_init(&wl);
  if (wl.compositor == NULL || wl.shm == NULL || wl.wm_base == NULL) {
    printf("wayland globals: compositor=%d shm=%d wm_base=%d\n",
           wl.compositor != NULL, wl.shm != NULL, wl.wm_base != NULL);
    return 1;
  }
  wl_common_setup(&wl, app, "MyUI explorer [wayland/soft]");
  if (wl_shm_buffer(&wl) != 0) {
    printf("wayland shm setup failed\n");
    return 1;
  }
  for (;;) {
    wl_display_dispatch_pending(wl.display);
    wl_display_flush(wl.display);
    if (wl.closed) break;
    render_frame(app);
    memcpy(wl.shm_data, my_lcd_mem_get_buffer(app->lcd),
           (size_t)EX_W * EX_H * 4u);
    wl_surface_attach(wl.surface, wl.buffer, 0, 0);
    wl_surface_damage(wl.surface, 0, 0, EX_W, EX_H);
    wl_surface_commit(wl.surface);
    nap();
  }
  return 0;
}

/* ---------------- GL backend (EGL on X11 or Wayland) ---------------- */
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#ifndef EGL_PLATFORM_WAYLAND_KHR
#define EGL_PLATFORM_WAYLAND_KHR 0x31D8
#endif
#ifndef EGL_PLATFORM_X11_KHR
#define EGL_PLATFORM_X11_KHR 0x31D5
#endif

typedef struct {
  EGLDisplay display;
  EGLContext context;
  EGLSurface surface;
} gl_state_t;

static EGLint const k_gl_attribs[] = {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE};

static int gl_context(gl_state_t* gl, void* native_display,
                      void* native_window, EGLenum platform) {
  EGLConfig config;
  EGLint count = 0;
  gl->display = eglGetPlatformDisplay(platform, native_display, NULL);
  if (gl->display == EGL_NO_DISPLAY) return 1;
  if (!eglInitialize(gl->display, NULL, NULL)) return 1;
  if (!eglBindAPI(EGL_OPENGL_ES_API)) return 1;
  if (!eglChooseConfig(gl->display, k_gl_attribs, &config, 1, &count) ||
      count < 1)
    return 1;
  gl->surface = eglCreateWindowSurface(gl->display, config,
                                       (EGLNativeWindowType)native_window,
                                       NULL);
  if (gl->surface == EGL_NO_SURFACE)
    gl->surface = eglCreatePlatformWindowSurface(gl->display, config,
                                                 native_window, NULL);
  if (gl->surface == EGL_NO_SURFACE) return 1;
  {
    static const EGLint ctx_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                         EGL_NONE};
    gl->context = eglCreateContext(gl->display, config, EGL_NO_CONTEXT,
                                   ctx_attribs);
  }
  if (gl->context == EGL_NO_CONTEXT) return 1;
  return eglMakeCurrent(gl->display, gl->surface, gl->surface, gl->context)
             ? 0
             : 1;
}



static int run_gl_x11(app_t* app) {
  Display* dpy;
  Window win;
  Atom wm_delete;
  int screen;
  gl_state_t gl;
  my_vgcanvas_t* vg;
  EGLConfig config;
  EGLint count = 0;
  EGLint visual_id = 0;
  XVisualInfo vi;
  XSetWindowAttributes swa;
  memset(&gl, 0, sizeof(gl));
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
    printf("no X display for GL\n");
    return 1;
  }
  screen = DefaultScreen(dpy);
  gl.display = eglGetPlatformDisplay(EGL_PLATFORM_X11_KHR, (void*)dpy, NULL);
  if (gl.display == EGL_NO_DISPLAY || !eglInitialize(gl.display, NULL, NULL) ||
      !eglBindAPI(EGL_OPENGL_ES_API) ||
      !eglChooseConfig(gl.display, k_gl_attribs, &config, 1, &count) ||
      count < 1) {
    printf("EGL setup failed on X11\n");
    return 1;
  }
  if (eglGetConfigAttrib(gl.display, config, EGL_NATIVE_VISUAL_ID,
                         &visual_id) &&
      XMatchVisualInfo(dpy, screen, (int)visual_id, TrueColor, &vi)) {
    swa.colormap = XCreateColormap(dpy, RootWindow(dpy, screen), vi.visual,
                                   AllocNone);
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask | PointerMotionMask | ButtonPressMask |
                     KeyPressMask;
    win = XCreateWindow(dpy, RootWindow(dpy, screen), 0, 0, EX_W, EX_H, 0,
                        vi.depth, InputOutput, vi.visual,
                        CWColormap | CWBorderPixel | CWEventMask, &swa);
  } else {
    win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen), 0, 0, EX_W, EX_H,
                              0, BlackPixel(dpy, screen),
                              WhitePixel(dpy, screen));
    XSelectInput(dpy, win, ExposureMask | PointerMotionMask |
                               ButtonPressMask | KeyPressMask);
  }
  XStoreName(dpy, win, "MyUI explorer [x11/gl]");
  wm_delete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(dpy, win, &wm_delete, 1);
  XMapRaised(dpy, win);
  XFlush(dpy);
  if (gl_context(&gl, (void*)dpy, (void*)win, EGL_PLATFORM_X11_KHR) != 0) {
    printf("EGL context failed on X11\n");
    return 1;
  }
  vg = my_vgcanvas_gles2_create(NULL, EX_W, EX_H);
  if (vg == NULL) {
    printf("gles2 vgcanvas init failed\n");
    return 1;
  }
  for (;;) {
    XEvent ev;
    int dirty = 1;
    while (XPending(dpy)) {
      XNextEvent(dpy, &ev);
      if (ev.type == ClientMessage &&
          (Atom)ev.xclient.data.l[0] == wm_delete)
        return 0;
      if (ev.type == MotionNotify) {
        pointer(app, ev.xmotion.x, ev.xmotion.y, 0);
        dirty = 1;
      } else if (ev.type == ButtonPress) {
        if (ev.xbutton.button == Button4) wheel(app, 1);
        else if (ev.xbutton.button == Button5) wheel(app, -1);
        else if (ev.xbutton.button == Button1)
          pointer(app, ev.xbutton.x, ev.xbutton.y, 1);
        dirty = 1;
      } else if (ev.type == KeyPress) {
        KeySym k = XLookupKeysym(&ev.xkey, 0);
        if (k >= XK_space && k <= XK_asciitilde) key(app, (int)k);
        dirty = 1;
      }
    }
    if (dirty) {
      gl_paint(app, vg);
      eglSwapBuffers(gl.display, gl.surface);
    }
    nap();
  }
}

static int run_gl_wayland(app_t* app) {
  wl_state_t wl;
  gl_state_t gl;
  my_vgcanvas_t* vg;
  struct wl_egl_window* egl_window;
  memset(&wl, 0, sizeof(wl));
  memset(&gl, 0, sizeof(gl));
  wl.display = wl_display_connect(NULL);
  if (wl.display == NULL) {
    printf("no wayland compositor for GL\n");
    return 1;
  }
  wl_registry_init(&wl);
  if (wl.compositor == NULL || wl.wm_base == NULL || wl.seat == NULL) {
    printf("wayland globals(gl): compositor=%d wm_base=%d seat=%d\n",
           wl.compositor != NULL, wl.wm_base != NULL, wl.seat != NULL);
    return 1;
  }
  wl_common_setup(&wl, app, "MyUI explorer [wayland/gl]");
  egl_window = wl_egl_window_create(wl.surface, EX_W, EX_H);
  if (egl_window == NULL) {
    printf("wl_egl_window creation failed\n");
    return 1;
  }
  if (gl_context(&gl, (void*)wl.display, (void*)egl_window,
                 EGL_PLATFORM_WAYLAND_KHR) != 0) {
    printf("EGL setup failed on wayland\n");
    return 1;
  }
  vg = my_vgcanvas_gles2_create(NULL, EX_W, EX_H);
  if (vg == NULL) {
    printf("gles2 vgcanvas init failed\n");
    return 1;
  }
  for (;;) {
    wl_display_dispatch_pending(wl.display);
    wl_display_flush(wl.display);
    if (wl.closed) break;
    gl_paint(app, vg);
    eglSwapBuffers(gl.display, gl.surface);
    nap();
  }
  return 0;
}

static int run_gl(app_t* app, const char* font_path, int wayland) {
  (void)font_path;
  return wayland ? run_gl_wayland(app) : run_gl_x11(app);
}
#endif
#endif
