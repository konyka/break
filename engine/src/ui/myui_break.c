#include "ui/myui_break.h"
#include "ui/myui_break_input.h"

#include <stdlib.h>
#include <string.h>

#include "core/shader_io.h"
#include "mypal/break/my_pal_break.h"
#include "mypal/my_event.h"
#include "myr/my_vgcanvas_break_rhi.h"
#include "myui/my_window.h"
#include "myui/my_window_manager.h"
#include "platform/input.h"
#include "platform/platform_text.h"
#include "ui/myui_break_damage.h"

struct BreakUI {
  Platform *platform;
  RHIDevice *device;
  my_pal_t *pal;
  my_pal_main_loop_t *loop;
  my_window_manager_t *wm;
  my_vgcanvas_t *vg;
  my_window_t *window;
  my_font_t *font;
  RHIOffscreenFBO surface_fbo;
  RHIPipeline composite_pipeline;
  RHISampler composite_sampler;
  u32 font_size;
  u32 logical_width, logical_height;
  u32 width, height; /* drawable pixels */
  u8 prev_keys[INPUT_MAX_KEYS];
  f32 prev_mouse_x, prev_mouse_y;
  f32 prev_scroll_x, prev_scroll_y;
  bool prev_has_mouse;
  bool surface_valid;
  my_dirty_rects_t *dirty_snapshots;
  size_t dirty_snapshot_capacity;
};

static char *break_ui_read_shader(const char *path, usize *out_len) {
  static const char *prefixes[] = {"", "engine/", "../engine/",
                                    "../../engine/"};
  const char *env = getenv("BREAK_SHADER_DIR");
  size_t i;
  if (env != NULL && env[0] != '\0') {
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", env, path);
    {
      char *source = shader_read_file(full_path, out_len);
      if (source != NULL) return source;
    }
  }
  for (i = 0; i < sizeof(prefixes) / sizeof(prefixes[0]); i++) {
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s%s", prefixes[i], path);
    {
      char *source = shader_read_file(full_path, out_len);
      if (source != NULL) return source;
    }
  }
  return NULL;
}

static RHIPipeline break_ui_create_composite_pipeline(RHIDevice *device) {
  usize vertex_len = 0;
  usize fragment_len = 0;
  char *vertex_source;
  char *fragment_source;
  RHIShader vertex_shader;
  RHIShader fragment_shader;
  RHIPipeline pipeline;
  RHIPipelineDesc desc;
#ifdef ENGINE_VULKAN
  vertex_source = break_ui_read_shader("shaders/post_vk.vert", &vertex_len);
  fragment_source =
      break_ui_read_shader("shaders/post_tex_vk.frag", &fragment_len);
#else
  vertex_source = break_ui_read_shader("shaders/post.vert", &vertex_len);
  fragment_source =
      break_ui_read_shader("shaders/post_tex.frag", &fragment_len);
#endif
  if (vertex_source == NULL || fragment_source == NULL) {
    free(vertex_source);
    free(fragment_source);
    return RHI_HANDLE_NULL;
  }
  vertex_shader =
      rhi_shader_create(device, vertex_source, vertex_len, false);
  fragment_shader =
      rhi_shader_create(device, fragment_source, fragment_len, true);
  free(vertex_source);
  free(fragment_source);
  if (!rhi_handle_valid(vertex_shader) || !rhi_handle_valid(fragment_shader)) {
    if (rhi_handle_valid(vertex_shader))
      rhi_shader_destroy(device, vertex_shader);
    if (rhi_handle_valid(fragment_shader))
      rhi_shader_destroy(device, fragment_shader);
    return RHI_HANDLE_NULL;
  }
  memset(&desc, 0, sizeof(desc));
  desc.vert = vertex_shader;
  desc.frag = fragment_shader;
  desc.no_vertex_input = true;
  desc.uses_textures = true;
  desc.depth_write_disable = true;
  desc.disable_culling = true;
  pipeline = rhi_pipeline_create(device, &desc);
  rhi_shader_destroy(device, vertex_shader);
  rhi_shader_destroy(device, fragment_shader);
  return pipeline;
}

static bool break_ui_create_surface_resources(BreakUI *ui, u32 width,
                                              u32 height) {
  RHISamplerDesc sampler_desc;
  ui->surface_fbo = rhi_offscreen_fbo_create_fmt(
      ui->device, width, height, RHI_FORMAT_R8G8B8A8_UNORM);
  if (!rhi_handle_valid(ui->surface_fbo.fb)) {
    return false;
  }
  if (!rhi_handle_valid(ui->composite_pipeline)) {
    ui->composite_pipeline = break_ui_create_composite_pipeline(ui->device);
  }
  if (!rhi_handle_valid(ui->composite_sampler)) {
    memset(&sampler_desc, 0, sizeof(sampler_desc));
    sampler_desc.min_filter = RHI_FILTER_LINEAR;
    sampler_desc.mag_filter = RHI_FILTER_LINEAR;
    sampler_desc.wrap_u = RHI_WRAP_CLAMP_TO_EDGE;
    sampler_desc.wrap_v = RHI_WRAP_CLAMP_TO_EDGE;
    sampler_desc.wrap_w = RHI_WRAP_CLAMP_TO_EDGE;
    ui->composite_sampler = rhi_sampler_create(ui->device, &sampler_desc);
  }
  if (!rhi_handle_valid(ui->composite_pipeline) ||
      !rhi_handle_valid(ui->composite_sampler)) {
    return false;
  }
  ui->surface_valid = false;
  return true;
}

static void break_ui_destroy_surface_resources(BreakUI *ui) {
  if (rhi_handle_valid(ui->surface_fbo.fb)) {
    rhi_offscreen_fbo_destroy(ui->device, &ui->surface_fbo);
  }
  if (rhi_handle_valid(ui->composite_pipeline)) {
    rhi_pipeline_destroy(ui->device, ui->composite_pipeline);
    ui->composite_pipeline = RHI_HANDLE_NULL;
  }
  if (rhi_handle_valid(ui->composite_sampler)) {
    rhi_sampler_destroy(ui->device, ui->composite_sampler);
    ui->composite_sampler = RHI_HANDLE_NULL;
  }
  ui->surface_valid = false;
}

static bool break_ui_ensure_dirty_snapshots(BreakUI *ui, size_t count) {
  my_dirty_rects_t *snapshots;
  if (ui == NULL) {
    return false;
  }
  if (count <= ui->dirty_snapshot_capacity) {
    return true;
  }
  snapshots = (my_dirty_rects_t *)realloc(
      ui->dirty_snapshots, count * sizeof(my_dirty_rects_t));
  if (snapshots == NULL) {
    return false;
  }
  ui->dirty_snapshots = snapshots;
  ui->dirty_snapshot_capacity = count;
  return true;
}

static void break_ui_invalidate_all_windows(my_window_manager_t *wm) {
  size_t i;
  if (wm == NULL) {
    return;
  }
  for (i = 0; i < my_darray_size(wm->windows); i++) {
    my_window_t *win = (my_window_t *)my_darray_get(wm->windows, i);
    my_widget_invalidate((my_widget_t *)win, NULL);
  }
}

static uint8_t break_modifiers(InputState *input) {
  uint8_t mods = 0;
  if (input_key_down(input, 289)) mods |= MY_KEYMOD_SHIFT;
  if (input_key_down(input, 290)) mods |= MY_KEYMOD_CTRL;
  return mods;
}

static void send_event(BreakUI *ui, my_event_t event) {
  if (ui->wm != NULL) {
    (void)my_window_manager_dispatch_surface_event(ui->wm, &event);
  } else {
    (void)my_window_on_pal_event(ui->window, &event);
  }
}

static void pump_keys(BreakUI *ui, InputState *input) {
  u32 i;
  uint8_t modifiers = break_modifiers(input);
  bool ime_enabled = platform_ime_is_enabled(ui->platform);
  for (i = 0; i < INPUT_MAX_KEYS; i++) {
    uint8_t now = input->keys[i];
    uint8_t prev = ui->prev_keys[i];
    if (now == prev) continue;
    ui->prev_keys[i] = now;
    if (i >= 300 && i <= 304) continue;
    if (i == 289 || i == 290) continue;
    if (!break_ui_should_dispatch_key((i32)i, modifiers, ime_enabled)) {
      continue;
    }
    if (now == 3) {
      uint32_t key = break_ui_map_key((i32)i);
      if (key != MY_KEY_UNKNOWN) {
        my_event_t e = my_event_init(MY_EVENT_KEY_DOWN);
        e.u.key.key = key;
        e.u.key.modifiers = modifiers;
        send_event(ui, e);
      }
    } else if (now == 1) {
      uint32_t key = break_ui_map_key((i32)i);
      if (key != MY_KEY_UNKNOWN) {
        my_event_t e = my_event_init(MY_EVENT_KEY_UP);
        e.u.key.key = key;
        e.u.key.modifiers = modifiers;
        send_event(ui, e);
      }
    }
  }
}

static void pump_mouse(BreakUI *ui, InputState *input) {
  float scale = platform_get_input_scale(ui->platform);
  float mouse_x;
  float mouse_y;
  uint8_t mods = break_modifiers(input);
  if (scale <= 0.0f) scale = 1.0f;
  mouse_x = input->mouse_x / scale;
  mouse_y = input->mouse_y / scale;
  if (!ui->prev_has_mouse) {
    ui->prev_has_mouse = input->has_mouse_pos;
    ui->prev_mouse_x = mouse_x;
    ui->prev_mouse_y = mouse_y;
  }
  if (input->has_mouse_pos &&
      (mouse_x != ui->prev_mouse_x || mouse_y != ui->prev_mouse_y ||
       !ui->prev_has_mouse)) {
    my_event_t e = my_event_init(MY_EVENT_POINTER_MOVE);
    e.u.pointer.x = (int32_t)mouse_x;
    e.u.pointer.y = (int32_t)mouse_y;
    e.u.pointer.modifiers = mods;
    send_event(ui, e);
    ui->prev_mouse_x = mouse_x;
    ui->prev_mouse_y = mouse_y;
    ui->prev_has_mouse = true;
  }
  for (u32 i = 0; i < 5; i++) {
    u32 key = INPUT_MOUSE_LEFT + i;
    uint8_t now = input->keys[key];
    uint8_t prev = ui->prev_keys[key];
    if (now == prev) continue;
    ui->prev_keys[key] = now;
    if (now == 3 || now == 1) {
      my_event_t e = my_event_init(now == 3 ? MY_EVENT_POINTER_DOWN
                                             : MY_EVENT_POINTER_UP);
      e.u.pointer.x = (int32_t)mouse_x;
      e.u.pointer.y = (int32_t)mouse_y;
      e.u.pointer.button = (uint8_t)(i + 1);
      e.u.pointer.modifiers = mods;
      send_event(ui, e);
    }
  }
  if (input->scroll_dx != 0.0f || input->scroll_dy != 0.0f) {
    if (input->scroll_dx != ui->prev_scroll_x ||
        input->scroll_dy != ui->prev_scroll_y) {
      my_event_t e = my_event_init(MY_EVENT_POINTER_WHEEL);
      e.u.pointer.x = (int32_t)mouse_x;
      e.u.pointer.y = (int32_t)mouse_y;
      e.u.pointer.delta = (int32_t)(input->scroll_dy != 0.0f
                                         ? input->scroll_dy
                                         : input->scroll_dx);
      e.u.pointer.modifiers = mods;
      send_event(ui, e);
    }
    ui->prev_scroll_x = input->scroll_dx;
    ui->prev_scroll_y = input->scroll_dy;
  }
}

/* BreakUI on-open hook: the shared RHI vgcanvas is borrowed, so every
 * window the manager opens paints into the same buffer (paint order =
 * stack order, bottom first). Dialogs also inherit the main font and are
 * centered over the window below (Break PAL move is a no-op). */
static void break_ui_on_window_open(struct my_window_manager_t *wm,
                                    struct my_window_t *win, void *ctx) {
  BreakUI *ui = (BreakUI *)ctx;
  size_t n;
  (void)wm;
  if (ui == NULL || win == NULL) {
    return;
  }
  my_window_set_vgcanvas(win, ui->vg);
  if (ui->font != NULL) {
    my_window_set_font(win, ui->font, ui->font_size);
  }
  n = my_darray_size(wm->windows);
  if (win->modal && n >= 2) {
    my_window_t *below = (my_window_t *)my_darray_get(wm->windows, n - 2);
    my_widget_t *below_root = (my_widget_t *)below;
    my_widget_t *root = (my_widget_t *)win;
    my_rect_t bounds = root->rect;
    bounds.x = below_root->rect.x + (below_root->rect.w - root->rect.w) / 2;
    bounds.y = below_root->rect.y + (below_root->rect.h - root->rect.h) / 2;
    (void)my_widget_set_rect(root, &bounds);
    (void)my_pal_window_move(win->pal_window, bounds.x, bounds.y);
  }
}

static void pump_text(BreakUI *ui) {
  PlatformTextEvent events[8];
  u32 n = platform_poll_text(ui->platform, events, 8);
  for (u32 i = 0; i < n; i++) {
    my_event_t e;
    if (events[i].type == PLATFORM_TEXT_COMMIT) {
      e = my_event_init(MY_EVENT_IME_COMMIT);
      e.u.ime.text = platform_text_event_utf8(&events[i]);
      e.u.ime.cursor = events[i].cursor;
      send_event(ui, e);
    } else if (events[i].type == PLATFORM_TEXT_DELETE_SURROUNDING) {
      e = my_event_init(MY_EVENT_IME_DELETE_SURROUNDING);
      e.u.ime.before = events[i].before;
      e.u.ime.after = events[i].after;
      send_event(ui, e);
    } else {
      e = my_event_init(MY_EVENT_IME_PREEDIT);
      e.u.ime.text = platform_text_event_utf8(&events[i]);
      e.u.ime.cursor = events[i].cursor;
      send_event(ui, e);
    }
    platform_text_event_destroy(&events[i]);
  }
}

bool break_ui_init_with_fonts(BreakUI *ui, Platform *platform,
                              RHIDevice *device,
                              const my_font_source_t *font_sources,
                              size_t font_source_count, u32 width,
                              u32 height) {
  if (ui == NULL || platform == NULL || device == NULL || width == 0 ||
      height == 0) {
    return false;
  }
  memset(ui, 0, sizeof(*ui));
  ui->platform = platform;
  ui->device = device;
  ui->logical_width = width;
  ui->logical_height = height;
  platform_get_drawable_size(platform, &ui->width, &ui->height);
  if (ui->width == 0 || ui->height == 0) {
    ui->width = width;
    ui->height = height;
  }
  ui->pal = my_pal_break_create(NULL, platform, device);
  if (ui->pal == NULL) {
    break_ui_shutdown(ui);
    return false;
  }
  ui->loop = my_pal_main_loop_create(ui->pal);
  if (ui->loop == NULL) {
    break_ui_shutdown(ui);
    return false;
  }
  ui->window = my_window_create(NULL, ui->pal, (int32_t)width, (int32_t)height,
                                "break-ui");
  if (ui->window == NULL) {
    break_ui_shutdown(ui);
    return false;
  }
  ui->vg = my_vgcanvas_break_rhi_create(NULL, device, ui->width, ui->height);
  if (ui->vg == NULL) {
    break_ui_shutdown(ui);
    return false;
  }
  if (!break_ui_create_surface_resources(ui, ui->width, ui->height)) {
    break_ui_shutdown(ui);
    return false;
  }
  my_window_set_vgcanvas(ui->window, ui->vg);
  if (font_sources != NULL && font_source_count > 0) {
    ui->font = my_font_create_chain_ex(NULL, font_sources, font_source_count,
                                       256);
  }
  if (ui->font == NULL) {
    ui->font = my_font_bitmap_create(NULL);
  }
  if (ui->font != NULL) {
    my_window_set_font(ui->window, ui->font, 16);
    ui->font_size = 16;
  }
  ui->wm = my_window_manager_create(NULL, ui->pal, ui->loop);
  if (ui->wm == NULL) {
    break_ui_shutdown(ui);
    return false;
  }
  my_window_manager_set_auto_paint(ui->wm, false);
  my_window_manager_set_on_open(ui->wm, break_ui_on_window_open, ui);
  if (my_window_manager_open(ui->wm, ui->window) != MY_RET_OK) {
    break_ui_shutdown(ui);
    return false;
  }
  return true;
}

bool break_ui_init(BreakUI *ui, Platform *platform, RHIDevice *device,
                   const char *font_path, u32 width, u32 height) {
  my_font_source_t source;

  if (font_path == NULL) {
    return break_ui_init_with_fonts(ui, platform, device, NULL, 0, width,
                                    height);
  }
  source.path = font_path;
  source.face_index = 0;
  return break_ui_init_with_fonts(ui, platform, device, &source, 1, width,
                                  height);
}

void break_ui_shutdown(BreakUI *ui) {
  if (ui == NULL) return;
  if (ui->wm != NULL) {
    my_window_manager_destroy(ui->wm);
    ui->wm = NULL;
  }
  if (ui->window != NULL) {
    my_object_unref((void *)ui->window);
    ui->window = NULL;
  }
  if (ui->vg != NULL) {
    my_vgcanvas_destroy(ui->vg);
    ui->vg = NULL;
  }
  free(ui->dirty_snapshots);
  ui->dirty_snapshots = NULL;
  ui->dirty_snapshot_capacity = 0;
  break_ui_destroy_surface_resources(ui);
  if (ui->font != NULL) {
    my_font_destroy(ui->font);
    ui->font = NULL;
  }
  if (ui->loop != NULL) {
    my_pal_main_loop_destroy(ui->loop);
    ui->loop = NULL;
  }
  if (ui->pal != NULL) {
    my_pal_destroy(ui->pal);
    ui->pal = NULL;
  }
}

void break_ui_pump(BreakUI *ui) {
  InputState *input;
  if (ui == NULL || ui->platform == NULL || ui->window == NULL) return;
  (void)my_pal_break_pump(ui->loop);
  input = platform_input(ui->platform);
  pump_keys(ui, input);
  pump_mouse(ui, input);
  pump_text(ui);
}

void break_ui_render(BreakUI *ui, RHICmdBuffer *cmd, u32 width, u32 height) {
  u32 logical_width = 0;
  u32 logical_height = 0;
  bool drawable_changed;
  bool logical_changed;
  /* The injected canvas is resized here; windows only receive the layout
   * resize event and never destroy or resize the shared RHI target. */
  if (ui == NULL || ui->window == NULL || ui->vg == NULL || cmd == NULL) return;
  platform_get_logical_size(ui->platform, &logical_width, &logical_height);
  if (logical_width == 0 || logical_height == 0) {
    logical_width = ui->logical_width;
    logical_height = ui->logical_height;
  }
  drawable_changed = width != ui->width || height != ui->height;
  logical_changed = logical_width != ui->logical_width ||
                    logical_height != ui->logical_height;
  if (drawable_changed) {
    ui->width = width;
    ui->height = height;
    my_vgcanvas_break_rhi_resize(ui->vg, width, height);
    if (rhi_handle_valid(ui->surface_fbo.fb)) {
      rhi_offscreen_fbo_destroy(ui->device, &ui->surface_fbo);
    }
    if (!break_ui_create_surface_resources(ui, width, height)) {
      return;
    }
  }
  if (logical_changed) {
    ui->logical_width = logical_width;
    ui->logical_height = logical_height;
    {
      my_event_t e = my_event_init(MY_EVENT_RESIZE);
      e.u.resize.w = (int32_t)logical_width;
      e.u.resize.h = (int32_t)logical_height;
      if (ui->wm != NULL) {
        (void)my_window_manager_resize_surface(ui->wm, (int32_t)logical_width,
                                               (int32_t)logical_height);
      } else {
        (void)my_window_on_pal_event(ui->window, &e);
      }
    }
  }
  if (ui->wm != NULL) {
    (void)my_window_manager_refresh_scales(ui->wm);
  } else {
    (void)my_window_refresh_scale(ui->window);
  }
  my_vgcanvas_break_rhi_set_cmd(ui->vg, cmd);
  if (ui->wm != NULL) {
    my_window_t** windows = NULL;
    size_t n = 0;
    uint64_t epoch;
    my_dirty_rects_t damage;
    size_t i;
    if (my_window_manager_snapshot_windows(ui->wm, &windows, &n) !=
        MY_RET_OK) {
      return;
    }
    if (n == 0) {
      ui->surface_valid = false;
      my_window_manager_release_snapshot(ui->wm, windows, n);
      goto composite_surface;
    }
    epoch = my_window_manager_windows_epoch(ui->wm);
    for (i = 0; i < n; i++) {
      if (my_window_prepare_layout(windows[i]) != MY_RET_OK) {
        my_window_manager_release_snapshot(ui->wm, windows, n);
        return;
      }
      if (my_window_manager_windows_epoch(ui->wm) != epoch) {
        ui->surface_valid = false;
        break_ui_invalidate_all_windows(ui->wm);
        my_window_manager_release_snapshot(ui->wm, windows, n);
        goto composite_surface;
      }
    }
    break_ui_collect_surface_damage_for_windows(windows, n, &damage);
    if (my_dirty_rects_count(&damage) > 0) {
      if (!break_ui_ensure_dirty_snapshots(ui, n)) {
        my_window_manager_release_snapshot(ui->wm, windows, n);
        return;
      }
      break_ui_expand_surface_damage_for_windows(windows, n, &damage);
      for (i = 0; i < n; i++) {
        ui->dirty_snapshots[i] = windows[i]->dirty;
      }
      if (ui->surface_valid) {
        rhi_offscreen_fbo_bind_load(cmd, &ui->surface_fbo);
      } else {
        rhi_offscreen_fbo_bind(cmd, &ui->surface_fbo);
        rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 0.0f);
      }
      if (my_vgcanvas_begin_frame(ui->vg,
                                  my_dirty_rects_get(&damage, 0)) == MY_RET_OK) {
        bool frame_ok = true;
        for (i = 0; i < n; i++) {
          if (my_window_manager_windows_epoch(ui->wm) != epoch ||
              my_window_record_dirty(windows[i]) != MY_RET_OK) {
            frame_ok = false;
            break;
          }
        }
        if (my_window_manager_windows_epoch(ui->wm) != epoch ||
            my_vgcanvas_end_frame(ui->vg) != MY_RET_OK) {
          frame_ok = false;
        }
        if (frame_ok) {
          ui->surface_valid = true;
        } else {
          break_ui_restore_surface_dirty_for_windows(windows, n,
                                                     ui->dirty_snapshots);
          ui->surface_valid = false;
          break_ui_invalidate_all_windows(ui->wm);
        }
      } else {
        break_ui_restore_surface_dirty_for_windows(windows, n,
                                                   ui->dirty_snapshots);
        ui->surface_valid = false;
        break_ui_invalidate_all_windows(ui->wm);
      }
      rhi_offscreen_fbo_unbind(cmd, width, height);
    }
    my_window_manager_release_snapshot(ui->wm, windows, n);
  } else {
    my_window_paint(ui->window);
  }
composite_surface:
  if (ui->surface_valid) {
    rhi_cmd_bind_pipeline(cmd, ui->composite_pipeline);
    rhi_cmd_bind_texture(cmd, ui->surface_fbo.color_tex,
                         ui->composite_sampler, 0);
    rhi_cmd_draw(cmd, 3, 1);
  }
}

void *break_ui_window(BreakUI *ui) {
  return ui != NULL ? my_window_widget(ui->window) : NULL;
}

BreakUI *break_ui_create(void) {
  return (BreakUI *)calloc(1, sizeof(BreakUI));
}

void break_ui_destroy(BreakUI *ui) {
  if (ui == NULL) return;
  break_ui_shutdown(ui);
  free(ui);
}

struct my_window_t *break_ui_get_window(BreakUI *ui) {
  return ui != NULL ? ui->window : NULL;
}

struct my_window_manager_t *break_ui_get_window_manager(BreakUI *ui) {
  return ui != NULL ? ui->wm : NULL;
}

struct my_pal_t *break_ui_get_pal(BreakUI *ui) {
  return ui != NULL ? ui->pal : NULL;
}

struct my_pal_main_loop_t *break_ui_get_loop(BreakUI *ui) {
  return ui != NULL ? ui->loop : NULL;
}
