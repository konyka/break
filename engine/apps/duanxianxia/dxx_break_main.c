/**
 * @file dxx_break_main.c
 * @brief Break RHI executable for the duanxianxia myui application.
 *
 * Owns the Break Platform and RHI device; BreakUI owns the myui PAL, loop,
 * RHI vgcanvas and root window. The dxx_app module composes the home page.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "dxx_app.h"
#include "myr/my_font.h"
#include "myui/my_window.h"
#include "myui/my_window_manager.h"
#include "platform/platform.h"
#include "rhi/rhi.h"
#include "ui/myui_break.h"

#define DXX_WIN_W 1320
#define DXX_WIN_H 900

static int32_t configured_font_face(void) {
  const char *value = getenv("BREAK_MYUI_FONT_FACE");
  char *end = NULL;
  long index;

  if (value == NULL || value[0] == '\0') {
    return 0;
  }
  errno = 0;
  index = strtol(value, &end, 10);
  if (errno != 0 || end == value || *end != '\0' || index < 0 ||
      index > INT32_MAX) {
    fprintf(stderr, "dxx: ignoring invalid BREAK_MYUI_FONT_FACE=%s\n", value);
    return 0;
  }
  return (int32_t)index;
}

static size_t preferred_fonts(my_font_source_t fonts[3]) {
  const char *env = getenv("BREAK_MYUI_FONT");
  if (env != NULL && env[0] != '\0') {
    fonts[0].path = env;
    fonts[0].face_index = configured_font_face();
    return 1;
  }
#if defined(ENGINE_PLATFORM_LINUX)
  fonts[0].path =
      "/usr/share/fonts/google-noto-sans-cjk-vf-fonts/NotoSansCJK-VF.ttc";
  fonts[0].face_index = 2; /* Noto Sans CJK SC within the TTC. */
  fonts[1].path = "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc";
  fonts[1].face_index = 2;
  fonts[2].path =
      "/usr/share/fonts/google-droid-sans-fonts/DroidSansFallbackFull.ttf";
  fonts[2].face_index = 0;
  return 3;
#elif defined(ENGINE_PLATFORM_WINDOWS)
  fonts[0].path = "C:/Windows/Fonts/msyh.ttc";
  fonts[0].face_index = 0;
  fonts[1].path = "C:/Windows/Fonts/simsun.ttc";
  fonts[1].face_index = 0;
  return 2;
#elif defined(ENGINE_PLATFORM_MACOS)
  fonts[0].path = "/System/Library/Fonts/PingFang.ttc";
  fonts[0].face_index = 0;
  fonts[1].path = "/System/Library/Fonts/STHeiti Light.ttc";
  fonts[1].face_index = 0;
  return 2;
#else
  (void)fonts;
  return 0;
#endif
}

int main(void) {
  PlatformConfig cfg;
  Platform *platform;
  RHIDevice *device;
  RHIBackend backend;
  BreakUI *ui;
  my_window_manager_t *wm;
  dxx_app_t *app;
  my_font_source_t fonts[3] = {{NULL, 0}};
  size_t font_count;
  u32 w = DXX_WIN_W, h = DXX_WIN_H;
  u32 drawable_w = DXX_WIN_W, drawable_h = DXX_WIN_H;

  memset(&cfg, 0, sizeof(cfg));
  cfg.width = w;
  cfg.height = h;
  cfg.title = "短线侠";
  platform = platform_create(&cfg);
  if (platform == NULL) {
    fprintf(stderr, "dxx: platform_create failed\n");
    return 1;
  }
  platform_get_logical_size(platform, &w, &h);
  platform_get_drawable_size(platform, &drawable_w, &drawable_h);

#ifdef ENGINE_VULKAN
  backend = RHI_BACKEND_VULKAN;
  device = rhi_device_create(backend, platform_surface_native(platform),
                             platform_display_native(platform), drawable_w,
                             drawable_h);
#else
  backend = RHI_BACKEND_OPENGL;
  device = rhi_device_create(backend, platform_window_native(platform),
                             platform_display_native(platform), drawable_w,
                             drawable_h);
#endif
  if (device == NULL) {
    fprintf(stderr, "dxx: rhi_device_create failed\n");
    platform_destroy(platform);
    return 1;
  }

  ui = break_ui_create();
  font_count = preferred_fonts(fonts);
  if (ui == NULL ||
      !break_ui_init_with_fonts(ui, platform, device,
                                font_count > 0 ? fonts : NULL, font_count, w,
                                h)) {
    break_ui_destroy(ui);
    rhi_device_destroy(device);
    platform_destroy(platform);
    fprintf(stderr, "dxx: break_ui_init failed\n");
    return 1;
  }

  wm = break_ui_get_window_manager(ui);

  app = dxx_app_create(wm, break_ui_get_window(ui), NULL, w, h);
  if (app == NULL) {
    break_ui_destroy(ui);
    rhi_device_destroy(device);
    platform_destroy(platform);
    fprintf(stderr, "dxx: dxx_app_create failed\n");
    return 1;
  }
  /* dxx_app_create already applies the font; it is valid without a font
   * argument because the bridge owns the window's default font. */
  (void)app;


  while (platform_poll(platform) != PLATFORM_EVENT_QUIT) {
    RHICmdBuffer *cmd;
    u32 nw = 0, nh = 0;
    platform_get_drawable_size(platform, &nw, &nh);
    if (nw != 0 && nh != 0 && (nw != drawable_w || nh != drawable_h)) {
      rhi_device_resize(device, nw, nh);
      drawable_w = nw;
      drawable_h = nh;
    }
    break_ui_pump(ui);
    cmd = rhi_frame_begin(device);
    if (cmd != NULL) {
      break_ui_render(ui, cmd, drawable_w, drawable_h);
      rhi_frame_end(device);
      rhi_present(device);
    }
  }

  dxx_app_destroy(app);
  break_ui_destroy(ui);
  rhi_device_destroy(device);
  platform_destroy(platform);
  return 0;
}
