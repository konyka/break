# Editor shortcut parity (2026-11-15)

Goal: close the gap between the Stage 4 shortcut spec and
`break_editor_shell_dispatch_key` (`engine/apps/editor/editor_panels.c`).

Already shipped: Q/W/E/R, F, Ctrl+S/Z/Y/P, Ctrl+Shift+R.
Missing: Ctrl+Shift+P, Ctrl+Shift+L, Ctrl+Shift+D, F5, F6, F7, F8.

## Task A: Ctrl+Shift diagnostic shortcuts

Problem: letter lookup ignores SHIFT, so Ctrl+Shift+P opens the command
palette and Ctrl+Shift+D duplicates the selection.

- Ctrl+Shift+P: select the Profiler page (area 1, tab 0), log
  `profiler: shown`.
- Ctrl+Shift+D: select the Network page (area 1, tab 1), log the remote debug
  state (`remote debug: off` when no remote is attached or it is not running,
  `remote debug: on` otherwise). Remote debugging stays opt-in; the shortcut
  never starts a listener.
- Ctrl+Shift+L: rebuild the Lua console (fresh sandbox state), select the Lua
  page (area 0, tab 1), log `lua: reloaded` (or `lua: reload failed` when the
  new console cannot be created; the panel then degrades as before).
- None of the three may open the palette or change the entity count.
- Every log line is an i18n key with English and Chinese text.

Test (RED first): `ctrl_shift_diagnostic_shortcuts_do_not_fall_through` in
`engine/tests/test_editor_shell.c`.

## Task B: F5-F8 play mode

- F5/F6 enter PLAYING from EDIT and snapshot the document.
- F7 toggles PLAYING/PAUSED.
- F8 restores the snapshot and returns to EDIT.
- Query: `break_editor_shell_play_state`.
- Design details (snapshot storage, undo history across stop) are decided in
  this plan's Task B section before its RED test is written.

## Verification

`cd build-core-app-master && cmake --build . -j16 && ctest -j8 --output-on-failure`,
plus the naming contract tests. Mutation check: drop each new branch and
confirm the test fails.

## Docs

- `docs/design/editor_phase1.md` §4 shortcut table.
- `docs/Implementation_Status.md` status entry.
