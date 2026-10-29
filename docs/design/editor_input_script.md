# Editor scripted input replay (2026-10-28)

Design: `docs/superpowers/specs/2026-10-28-editor-input-script-design.md`.

## Why

Synthetic X input does not reach the editor on this host: under Xwayland with Mutter, XTEST pointer motion arrives at an X11 window but button and key events do not (`.superpowers/sdd/2026-10-28-editor-input-script/live/xt_probe.py` received FocusIn/Enter/Motion and no ButtonPress/KeyPress). Earlier live checks therefore drove the editor through gdb calls and never exercised the input path.

## What it is

- `apps/editor/editor_input_script.{h,c}`: parser + player. The player writes the platform `InputState` once per frame, before `break_ui_pump`, with the same edge values the platform uses (3 pressed, 1 released). Everything after that is production code: BreakUI key/pointer mapping and modifiers, myui hit testing and focus, widget handlers, editor shortcuts, the viewport pick and gizmo drag.
- `apps/editor/editor_input_driver.{h,c}`: `--input-script <file>` for the editor; resolves `move_to <widget>[@<row text>] [fx fy]` through the live widget tree, answers `expect`, writes `screenshot` as binary PPM (top-down rows) after `rhi_frame_end`, exits 0 when every step passed and 3 otherwise.
- Commands: `wait`, `move`, `move_to`, `down`/`up`/`click <left|right|middle>`, `key`/`keydown`/`keyup <name>`, `chord <mod>+...+<key>`, `scroll`, `screenshot`, `expect`, `quit`. Checks: `entities`, `selected`, `tool`, `undo`, `palette`, `preview_reloads`, `pos_x_above`/`pos_x_below` (selected entity's Transform x), `log_contains`, `print` (diagnostic line). Bounds: 512 commands, 256-byte lines, 64 KiB file.
- Build: `-DBREAK_EDITOR_INPUT_SCRIPT=ON` (default OFF). `test_release_config_contract` fails if a shipped `editor` contains `break_editor_input_script_*` or `break_editor_input_driver_*` symbols (checked: it fails on an ON build).

## What it found

The first run clicked "Add" and nothing happened, on both backends. `break_ui_pump` runs `pump_keys` over the whole `InputState.keys` table before `pump_mouse`; `pump_keys` recorded the edge of the mouse slots (300..304) in `prev_keys` before skipping them, so `pump_mouse` always compared against an already updated value and never sent `MY_EVENT_POINTER_DOWN`/`UP`. Since the myui integration (`023fee7c`, 2026-08-21) mouse clicks through BreakUI could not have worked in the editor or in `dxx_break` (both call `break_ui_pump`); keyboard input and pointer motion were unaffected. Fixed in `myui_break.c`: the keyboard pass asks `break_ui_key_slot_is_keyboard` first and leaves the mouse and modifier slots alone; `test_break_ui_input` pins the predicate (red before, green after). `test_editor_shell` did not catch it because it emits myui events directly.

## Evidence

`.superpowers/sdd/2026-10-28-editor-input-script/live/full.txt`, run on NVK Vulkan and Mesa OpenGL (X11 via Xwayland), from a directory holding a 48x24 red PNG; exit 0 on both, i.e. every expectation held:

1. click the toolbar "Add": 1 entity, selected; click the inspector "Add" for Transform: undo depth 2;
2. click empty viewport space: selection cleared; click the viewport centre: the entity is picked again;
3. `W`: translate tool; drag the gizmo X handle from 56% to 70% of the viewport width: Transform x > 0.2 (0.748), undo depth 3, status `gizmo translate x`; the viewport region of the screenshots changes where the cube and gizmo moved;
4. `Ctrl+Z`: x back to 0, undo 2; `Ctrl+Y`: x > 0.2 again;
5. `Ctrl+P`: palette open; `Escape`: closed;
6. click the `pic.png` row in the asset browser: preview reload 1, console `image preview: loaded 48x24`, red pixels in the preview area of the screenshot.

`smoke.txt` also covers the outliner row click, two toolbar adds with undo/redo, and `W`/`E`/`R` tool switching.

Arguments are whitespace-separated; a token may be double-quoted to contain spaces, e.g. `move_to "editor-palette-list@Language: 中文 (Chinese)" 0.5 0.1` (needed for English palette row labels). A row whose centre is scrolled outside the list's visible rect cannot be clicked — use the fx/fy fractions to aim at the visible part.

## Notes

If the X server's vsync present path stalls (seen on this host: `glxgears` at about 1.4 FPS), the OpenGL backend waits in `glXSwapBuffers` and a script times out; run with `vblank_mode=0`.

`expect log_contains` matches the translated console text, and the editor picks its language from the locale (`LANG` etc.). The scripts in the evidence directory expect English lines, so pass `--lang en-US` (checked: `full.txt` exits 0 under `LANG=zh_CN.UTF-8` with the flag, and fails at the `log_contains` step without it).

## Not covered

IME text, typing into edit fields, drag-and-drop, right/middle-button camera drags (commands exist, not scripted yet), multi-window, recording scripts from real input, Windows/macOS. The window still needs a running display; this is a developer/live tool, not a CI lane.
