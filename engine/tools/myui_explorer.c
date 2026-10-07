#define _POSIX_C_SOURCE 199309L
/**
 * @file myui_explorer.c
 * @brief Interactive MyUI explorer: a live chart driven by real MyUI
 *        widgets (buttons, sliders, checkboxes, progress bar, labels).
 *
 * Run on an X11 display for live interaction, or with --selftest <dir>
 * to render a scripted interaction sequence to PPM frames.
 */
#include "myr/my_color.h"
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

#include <X11/Xlib.h>
#include <X11/Xutil.h>

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
  float scale;
  bool stacked;
  bool labels;
  bool legend;
  float anim;
  size_t zoom_start;
  size_t zoom_end;
  bool zoom_set;
} state_t;

typedef struct {
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
  char tooltip[96];
} app_t;

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
  float values[4][8];
  for (i = 0u; i < 4u; i++) {
    size_t j;
    for (j = 0u; j < 8u; j++)
      values[i][j] = app->st.base[i][j] * app->st.scale;
    series[i].name = k_names[i];
    series[i].values = values[i];
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

static void key(app_t* app, KeySym k) {
  if (k >= XK_1 && k <= XK_9) {
    size_t idx = (size_t)(k - XK_1);
    if (idx < MODE_COUNT) {
      app->mode = idx;
      apply_state(app);
    }
    return;
  }
  if (k == XK_0) {
    app->mode = 9u;
    apply_state(app);
    return;
  }
  if (k == XK_s || k == XK_S) {
    render_frame(app);
    dump_ppm(my_lcd_mem_get_buffer(app->lcd),
             "/tmp/myui_explorer_shot.ppm");
    return;
  }
  if (k == XK_r || k == XK_R) {
    randomize(app);
    apply_state(app);
  } else if (k == XK_plus || k == XK_equal) {
    wheel(app, 1);
  } else if (k == XK_minus) {
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

int main(int argc, char** argv) {
  const char* font_path =
      "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf";
  if (argc > 2 && strcmp(argv[1], "--selftest") == 0)
    return run_selftest(argv[2], font_path);
  if (argc > 2 && strcmp(argv[1], "--shot") == 0) {
    app_t* app = app_create(font_path);
    render_frame(app);
    dump_ppm(my_lcd_mem_get_buffer(app->lcd), argv[2]);
    printf("shot written: %s\n", argv[2]);
    return 0;
  }
  {
    Display* dpy = XOpenDisplay(NULL);
    Window win;
    XImage* image;
    GC gc;
    Atom wm_delete;
    app_t* app;
    int screen;
    if (dpy == NULL) {
      printf("no X display; use --selftest <dir>\n");
      return 1;
    }
    app = app_create(font_path);
    screen = DefaultScreen(dpy);
    win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen), 0, 0, EX_W, EX_H,
                              0, BlackPixel(dpy, screen),
                              WhitePixel(dpy, screen));
    XStoreName(dpy, win, "MyUI explorer");
    XSelectInput(dpy, win, ExposureMask | PointerMotionMask |
                               ButtonPressMask | KeyPressMask |
                               StructureNotifyMask);
    wm_delete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(dpy, win, &wm_delete, 1);
    XMapRaised(dpy, win);
    gc = XCreateGC(dpy, win, 0, NULL);
    image = NULL;
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
          if (ev.xbutton.button == Button4) {
            wheel(app, 1);
          } else if (ev.xbutton.button == Button5) {
            wheel(app, -1);
          } else if (ev.xbutton.button == Button1) {
            pointer(app, ev.xbutton.x, ev.xbutton.y, 1);
          }
          dirty = 1;
        } else if (ev.type == KeyPress) {
          KeySym k = XLookupKeysym(&ev.xkey, 0);
          key(app, k);
          dirty = 1;
        }
      }
      if (dirty) {
        const uint8_t* pixels;
        render_frame(app);
        pixels = my_lcd_mem_get_buffer(app->lcd);
        if (image == NULL) {
          image = XCreateImage(dpy, DefaultVisual(dpy, screen), 24, ZPixmap,
                               0, (char*)pixels, EX_W, EX_H, 32, EX_W * 4);
        }
        XPutImage(dpy, win, gc, image, 0, 0, 0, 0, EX_W, EX_H);
        XFlush(dpy);
        dirty = 0;
      }
      {
        struct timespec ts = {0, 8000000L};
        nanosleep(&ts, NULL);
      }
    }
  }
}
