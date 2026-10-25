/* Break scene editor — Stage 4 Phase 1 shell + Phase 2 3D viewport.
 *
 * Thin main: platform + RHI + BreakUI bridge (the dxx_break_main.c
 * precedent), then break_editor_shell_create() builds the whole panel tree
 * into the bridge window. All panel logic lives in editor_panels.c so the
 * headless dummy-PAL tests (test_editor_shell) exercise the same code. The
 * Phase 2 3D viewport renders offscreen between break_ui_frame_begin and
 * break_ui_render on the same command buffer; the panel widget blits the
 * resulting FBO texture during the UI pass.
 *
 * Optional positional argument: scene path used as the Ctrl+S /
 * palette-save target (Phase 1 has no save-as dialog; loading is
 * intentionally not wired to argv — the document model supports it, the
 * shell UI lands it in a later phase).
 *
 * Phase 4 Task 2: the remote session is DEFAULT OFF — it is created only
 * with --remote, which REQUIRES TLS (--remote-cert/--remote-key) and an
 * AUTH-v2 dev PSK (--remote-psk-hex or --remote-psk-file; dev path, not a
 * production credential system), binds 127.0.0.1, and applies the default
 * admission rate limits (flag reference: editor_remote.h). Any invalid
 * remote configuration exits non-zero before a listener exists.
 *
 * Phase 3 Task 3: the profiler PANEL (editor_panel_profiler.c) is a pure
 * view — the PRODUCER side lives here: the app enables the profiler and
 * pumps one frame region around the loop body so the panel has data. */
#include <stdio.h>
#include <string.h>

#include "editor_panels.h"
#include "editor_remote.h"

#include <core/profiler.h>
#include <editor/editor_scene.h>

#include "myui/my_window.h"
#include "myr/my_font.h"
#include "platform/platform.h"
#include "rhi/rhi.h"
#include "ui/myui_break.h"

#define EDITOR_WIN_W 1280u
#define EDITOR_WIN_H 800u

static size_t preferred_fonts(my_font_source_t fonts[3]) {
#if defined(__linux__)
  fonts[0].path = "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc";
  fonts[0].face_index = 0;
  fonts[1].path = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
  fonts[1].face_index = 0;
  return 2;
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

int main(int argc, char **argv) {
  PlatformConfig cfg;
  Platform *platform;
  RHIDevice *device;
  RHIBackend backend;
  BreakUI *ui;
  BreakEditorShell *shell;
  my_font_source_t fonts[3] = {{NULL, 0}};
  size_t font_count;
  u32 w = EDITOR_WIN_W, h = EDITOR_WIN_H;
  u32 drawable_w = EDITOR_WIN_W, drawable_h = EDITOR_WIN_H;
  BreakEditorRemoteCli remote_cli;
  BreakEditorRemote *remote = NULL;
  char remote_err[160];

  /* parsed before any window exists: a bad --remote config exits non-zero
   * without ever opening a listener (fail closed) */
  remote_err[0] = '\0';
  if (!break_editor_remote_cli_parse(argc, argv, &remote_cli, remote_err,
                                     sizeof(remote_err))) {
    fprintf(stderr, "editor: %s\n", remote_err);
    return 2;
  }

  memset(&cfg, 0, sizeof(cfg));
  cfg.width = w;
  cfg.height = h;
  cfg.title = "Break Scene Editor";
  platform = platform_create(&cfg);
  if (platform == NULL) {
    fprintf(stderr, "editor: platform_create failed\n");
    return 1;
  }
  platform_get_logical_size(platform, &w, &h);
  platform_get_drawable_size(platform, &drawable_w, &drawable_h);

#if defined(ENGINE_RHI_BACKEND_METAL)
  backend = RHI_BACKEND_METAL;
#elif defined(ENGINE_VULKAN)
  backend = RHI_BACKEND_VULKAN;
#else
  backend = RHI_BACKEND_OPENGL;
#endif
#if defined(ENGINE_VULKAN) || defined(ENGINE_RHI_BACKEND_METAL)
  device = rhi_device_create(backend, platform_surface_native(platform),
                             platform_display_native(platform), drawable_w,
                             drawable_h);
#else
  device = rhi_device_create(backend, platform_window_native(platform),
                             platform_display_native(platform), drawable_w,
                             drawable_h);
#endif
  if (device == NULL) {
    fprintf(stderr, "editor: rhi_device_create failed\n");
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
    fprintf(stderr, "editor: break_ui_init failed\n");
    return 1;
  }
  break_ui_set_present_partial(ui, true);

  shell = break_editor_shell_create(break_ui_get_window(ui));
  if (shell == NULL) {
    break_ui_destroy(ui);
    rhi_device_destroy(device);
    platform_destroy(platform);
    fprintf(stderr, "editor: break_editor_shell_create failed\n");
    return 1;
  }
  if (remote_cli.scene_path != NULL &&
      !break_editor_shell_set_scene_path(shell, remote_cli.scene_path)) {
    fprintf(stderr, "editor: scene path rejected (cap %u bytes)\n",
            BREAK_EDITOR_SCENE_PATH_CAPACITY);
  }
  if (remote_cli.enabled) {
    BreakEditorRemoteConfig remote_cfg;
    break_editor_remote_cli_to_config(&remote_cli, &remote_cfg);
    remote = break_editor_remote_create(shell, &remote_cfg);
    if (remote == NULL ||
        !break_editor_remote_set_psk(remote, remote_cli.key_id,
                                     remote_cli.psk) ||
        !break_editor_remote_start(remote)) {
      memset(remote_cli.psk, 0, sizeof(remote_cli.psk));
      break_editor_remote_destroy(remote);
      break_editor_shell_destroy(shell);
      break_ui_destroy(ui);
      rhi_device_destroy(device);
      platform_destroy(platform);
      fprintf(stderr, "editor: --remote failed to start (TLS cert/key "
                      "unreadable, port in use, or auth setup failed)\n");
      return 1;
    }
    memset(remote_cli.psk, 0, sizeof(remote_cli.psk));
    break_editor_shell_set_remote(shell, remote);
    fprintf(stderr,
            "editor: remote session (DEV TOOL, TLS + AUTH-v2) listening on "
            "127.0.0.1:%u\n",
            (unsigned)break_editor_remote_port(remote));
  }

  /* Phase 3 Task 3: producer side of the profiler panel (the panel itself
   * is a pure view over profiler_last_frame and never touches state). */
  profiler_set_enabled(true);

  while (platform_poll(platform) != PLATFORM_EVENT_QUIT) {
    RHICmdBuffer *cmd;
    bool skip = false;
    u32 nw = 0, nh = 0;
    u32 lw = 0, lh = 0;
    profiler_begin_frame();
    profiler_push("editor.frame");
    platform_get_drawable_size(platform, &nw, &nh);
    if (nw != 0 && nh != 0 && (nw != drawable_w || nh != drawable_h)) {
      rhi_device_resize(device, nw, nh);
      drawable_w = nw;
      drawable_h = nh;
    }
    break_ui_pump(ui);
    /* Phase 2 Task 3: per-frame viewport housekeeping (per-frame damage for
     * the live 3D view + gizmo/selection reconcile) BEFORE frame_begin's
     * skip decision, so the damage is visible to it. */
    break_editor_shell_tick(shell);
    platform_get_logical_size(platform, &lw, &lh);
    cmd = break_ui_frame_begin(ui, drawable_w, drawable_h, &skip, NULL);
    if (skip) {
      profiler_pop();
      profiler_end_frame();
      continue;
    }
    if (cmd != NULL) {
      /* 3D viewport pass into the SAME command buffer (offscreen FBO), then
       * the retained UI pass whose viewport widget blits the FBO texture. */
      break_editor_shell_render_viewport(shell, device, cmd, (int)drawable_w,
                                         (int)drawable_h, (int)lw, (int)lh);
      break_ui_render(ui, cmd, drawable_w, drawable_h);
      rhi_frame_end(device);
      rhi_present(device);
    }
    profiler_pop();
    profiler_end_frame();
  }

  break_editor_remote_destroy(remote);
  break_editor_shell_destroy(shell);
  break_ui_destroy(ui);
  rhi_device_destroy(device);
  platform_destroy(platform);
  return 0;
}
