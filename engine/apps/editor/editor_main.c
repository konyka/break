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
 * Asset hot reload: the host owns a BreakEditorHotReload (editor_hot_reload.h)
 * that watches the current scene file (the positional path, or the last
 * .bscn loaded from the asset browser) and applies valid external edits to
 * a clean document. It is torn down, with a bounded worker stop, before the
 * shell. Shader shutdown timeout retains the shell, UI, device and platform
 * rather than freeing borrowed state.
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

#include "editor_fonts.h"
#include "editor_hot_reload.h"
#include "editor_panels.h"
#include "editor_remote.h"
#ifdef BREAK_EDITOR_INPUT_SCRIPT
#include "editor_input_driver.h"
#endif

#include <core/profiler.h>
#include <editor/editor_scene.h>

#include "myui/my_window.h"
#include "myr/my_font.h"
#include "platform/platform.h"
#include "rhi/rhi.h"
#include "ui/myui_break.h"

#define EDITOR_WIN_W 1280u
#define EDITOR_WIN_H 800u

int main(int argc, char **argv) {
  PlatformConfig cfg;
  Platform *platform;
  RHIDevice *device;
  BreakUI *ui;
  BreakEditorShell *shell;
  BreakEditorFontChain fonts;
  BreakEditorLang lang = BREAK_EDITOR_LANG_EN_US;
  char lang_err[96];
  u32 w = EDITOR_WIN_W, h = EDITOR_WIN_H;
  u32 drawable_w = EDITOR_WIN_W, drawable_h = EDITOR_WIN_H;
  BreakEditorRemoteCli remote_cli;
  BreakEditorRemote *remote = NULL;
  BreakEditorHotReload *hot_reload = NULL;
  char remote_err[160];
#ifdef BREAK_EDITOR_INPUT_SCRIPT
  /* --input-script <file>: scripted input replay (test builds only) */
  const char *script_path = NULL;
  BreakEditorInputDriver *script = NULL;
  int script_exit = 0;
#endif

  /* --lang <tag> (or BREAK_LANG / LC_ALL / LC_MESSAGES / LANG) selects the
   * UI language; the option is removed before the remote/scene parser runs */
  lang_err[0] = '\0';
  if (!break_editor_cli_take_lang(&argc, argv, &lang, lang_err,
                                  sizeof(lang_err))) {
    fprintf(stderr, "editor: %s\n", lang_err);
    return 2;
  }
  (void)break_editor_i18n_set_lang(lang);
#ifdef BREAK_EDITOR_INPUT_SCRIPT
  if (!break_editor_input_driver_take_cli(&argc, argv, &script_path, lang_err,
                                          sizeof(lang_err))) {
    fprintf(stderr, "editor: %s\n", lang_err);
    return 2;
  }
  if (script_path != NULL) {
    char script_err[160];
    script_err[0] = '\0';
    script = break_editor_input_driver_create(script_path, script_err,
                                              sizeof(script_err));
    if (script == NULL) {
      fprintf(stderr, "editor: %s\n", script_err);
      return 2;
    }
  }
#endif

  /* parsed before any window exists: a bad --remote config exits non-zero
   * without ever opening a listener (fail closed) */
  remote_err[0] = '\0';
  if (!break_editor_remote_cli_parse(argc, argv, &remote_cli, remote_err,
                                     sizeof(remote_err))) {
    fprintf(stderr, "editor: %s\n", remote_err);
    return 2;
  }
#ifndef BREAK_ENABLE_SNOWFLAKE
  if (remote_cli.enabled) {
    break_editor_remote_cli_wipe(&remote_cli);
    fprintf(stderr, "editor: --remote unavailable: this build has no remote "
                    "session support (configure with BREAK_ENABLE_SNOWFLAKE=ON)\n");
    return 2;
  }
#endif

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

  /* Every backend implements the compiled entry; in the multi-backend
   * build it is the runtime chain (vulkan, then the opengl fallback). */
  device = rhi_device_create_compiled(platform_window_native(platform),
                                      platform_surface_native(platform),
                                      platform_display_native(platform),
                                      drawable_w, drawable_h);
  if (device == NULL) {
    fprintf(stderr, "editor: rhi_device_create_compiled failed\n");
    platform_destroy(platform);
    return 1;
  }

  ui = break_ui_create();
  /* vector fonts for the UI language: without them myui falls back to its
   * 8x8 ASCII bitmap font and every non-ASCII character is a placeholder */
  if (break_editor_font_candidates(lang, NULL, true, &fonts) == 0u) {
    fprintf(stderr, "editor: no UI font found; text will use the built-in "
                    "ASCII bitmap font (install Noto Sans CJK or DejaVu Sans)\n");
  } else if (!fonts.has_cjk) {
    fprintf(stderr, "editor: no CJK font found; Chinese text will not render "
                    "(install Noto Sans CJK)\n");
  }
  if (ui == NULL ||
      !break_ui_init_with_fonts(ui, platform, device,
                                fonts.count > 0u ? fonts.sources : NULL,
                                fonts.count, w, h)) {
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
  /* render debugger panel: borrowed device, detached before teardown. Shader
   * reload is viewport-owned; shell teardown stops it before device teardown. */
  break_editor_shell_set_render_device(shell, device);
  /* asset hot reload: host-owned, shell-borrowed; attached BEFORE the scene
   * path so the watcher starts on it. A failure only disables hot reload. */
  hot_reload = break_editor_hot_reload_create(shell);
  if (hot_reload == NULL) {
    fprintf(stderr, "editor: hot reload unavailable (allocation failed)\n");
  } else {
    break_editor_shell_set_hot_reload(shell, hot_reload);
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
      break_editor_remote_cli_wipe(&remote_cli);
      break_editor_remote_destroy(remote);
      break_editor_hot_reload_destroy(hot_reload);
      break_editor_shell_set_render_device(shell, NULL);
      if (!break_editor_shell_destroy(shell)) {
        fprintf(stderr, "editor: --remote failed to start (TLS cert/key "
                        "unreadable, port in use, or auth setup failed)\n");
        fprintf(stderr, "editor: shader reload shutdown timed out; retaining "
                        "bounded process resources instead of freeing them\n");
        return 1;
      }
      break_ui_destroy(ui);
      rhi_device_destroy(device);
      platform_destroy(platform);
      fprintf(stderr, "editor: --remote failed to start (TLS cert/key "
                      "unreadable, port in use, or auth setup failed)\n");
      return 1;
    }
    break_editor_remote_cli_wipe(&remote_cli);
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
#ifdef BREAK_EDITOR_INPUT_SCRIPT
    if (script != NULL && !break_editor_input_driver_frame(script, platform,
                                                           shell)) {
      break; /* the script finished (quit or last command) */
    }
#endif
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
#ifdef BREAK_EDITOR_INPUT_SCRIPT
      break_editor_input_driver_after_frame(script, device, drawable_w,
                                            drawable_h);
#endif
      rhi_present(device);
    }
    profiler_pop();
    profiler_end_frame();
  }

#ifdef BREAK_EDITOR_INPUT_SCRIPT
  script_exit = break_editor_input_driver_exit_code(script);
  break_editor_input_driver_destroy(script);
#endif
  break_editor_remote_destroy(remote);
  break_editor_hot_reload_destroy(hot_reload);
  break_editor_shell_set_render_device(shell, NULL);
  if (!break_editor_shell_destroy(shell)) {
    fprintf(stderr, "editor: shader reload shutdown timed out; retaining "
                    "bounded process resources instead of freeing them\n");
    return 1;
  }
  break_ui_destroy(ui);
  rhi_device_destroy(device);
  platform_destroy(platform);
#ifdef BREAK_EDITOR_INPUT_SCRIPT
  return script_exit;
#else
  return 0;
#endif
}
