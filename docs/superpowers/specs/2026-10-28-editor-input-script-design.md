# Editor scripted input replay — design (2026-10-28)

## 1. Problem

The TODO ledger keeps "editor manual interaction validation" open: live smokes so far drive the editor through gdb calls at the shell tick, because synthetic input does not reach the window on this host. Measured: under Xwayland with Mutter, an XTEST motion event reaches a plain X11 window, but XTEST button and key events do not (the probe window received FocusIn/Enter/Motion and no ButtonPress/KeyPress). So nothing has exercised the real path pointer/key -> platform `InputState` -> `break_ui_pump` -> myui dispatcher -> widget/shortcut handlers.

## 2. Approach

A test-only input script that writes into the real `InputState` before `break_ui_pump` reads it. Everything after that point is the production path: BreakUI's edge detection, key mapping, modifier handling, myui hit testing, focus, widget handlers, editor shortcuts and the gizmo drag state machine.

Rejected: injecting myui events directly (skips BreakUI's mapping and the editor's key routing, which is where previous bugs were); uinput (needs root and a device node); a Wayland virtual-pointer client (the editor runs on X11 here and Mutter does not expose the protocol to clients by default).

## 3. Units

- `engine/apps/editor/editor_input_script.{h,c}`: parser + player, pure apart from writing an `InputState *`. Text format, one command per line, `#` comments:
  - `wait <frames>`
  - `move <x> <y>` (logical pixels, window coordinates)
  - `move_to <widget-name> [<fx> <fy>]` (widget-relative fraction, default 0.5 0.5; resolved each time through a caller-supplied lookup so layout changes are honoured)
  - `down <left|right|middle>`, `up <...>`, `click <...>` (down, one frame, up)
  - `key <name>` (press one frame then release), `keydown`, `keyup`; names: `a`-`z`, `0`-`9`, `space`, `escape`, `enter`, `tab`, `backspace`, `left`, `right`, `up`, `down`, `delete`, `f1`-`f12`, `shift`, `ctrl`
  - `chord <mod>+...+<key>` (e.g. `ctrl+shift+r`): modifiers down, key pressed, all released
  - `scroll <dy>`
  - `screenshot <file>` and `expect <check> ...`: delegated to caller callbacks (the player does not know the editor)
  - `quit`
  Bounds: 512 commands, 256-byte lines, coordinates within +-16384, frames <= 100000. Parse errors report the line number and reject the whole script.
- One command advances per frame; `wait` holds for N frames. Pressed/released states use the same 3/1 edge values the platform writes, so BreakUI sees ordinary transitions.
- `editor_main.c`: `--input-script <file>` (only when built with `BREAK_EDITOR_INPUT_SCRIPT=1`). Each frame, after `platform_poll` and before `break_ui_pump`, the player steps. `move_to` resolves widgets via `my_widget_find_descendant` and `my_widget_local_to_global`; `expect` checks a fixed set of editor facts (`entities <n>`, `selected <name|none>`, `tool <q|w|e|r>`, `preview_reloads <n>`, `log_contains <text>`); a failed expectation prints the line and exits 3 at the end; `screenshot` uses the existing `rhi_screenshot` path; `quit` ends the loop with exit 0 (or 3 on any failed expectation).
- CMake option `BREAK_EDITOR_INPUT_SCRIPT` (default OFF). The release contract keeps the shipped `editor` free of the player (`break_editor_input_script_` symbols are forbidden).

## 4. Testing

- `test_editor_input_script` (new, headless): parse every command; reject unknown commands, bad numbers, out-of-range values, over-long lines and too many commands with the right line number; play against a plain `InputState` and check the exact per-frame key/mouse values for click, chord, key, wait, move_to through a stub lookup; screenshot/expect/quit reach the callbacks once.
- Live: a script that clicks the outliner "Add" button, selects the entity in the outliner, switches tools with W/E/R, drags the gizmo in the viewport, undoes with Ctrl+Z, opens the command palette with Ctrl+P and escapes, clicks an image in the asset browser; with `expect` lines after each step. Run on Vulkan and OpenGL.

## 5. Not delivered

IME text input, drag-and-drop, multi-window, recording scripts from real input, Windows/macOS runs.
