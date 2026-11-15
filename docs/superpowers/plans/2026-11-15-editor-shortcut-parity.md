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

Design (decided 2026-11-15):

- There is no in-memory BSCN writer, and `break_editor_doc_load_bytes` clears
  the undo history, so a reload-based snapshot would erase the user's
  history. Play mode instead uses a history mark.
- B1 (library, `editor_cmd.h`): `break_editor_history_mark(doc, &mark)`
  records the undo cursor, the dirty flag, and three stack counters (pushes,
  drop-oldest drops, clears). `break_editor_history_rewind(doc, &mark)` moves
  the cursor back to the mark with undo/redo. If commands were pushed after
  the mark, it then discards the redo tail (play-time commands), and it
  restores the dirty flag. It returns `LOST` with nothing changed when the
  stack was cleared (load / new scene / hot reload) or drop-oldest removed
  play-time commands, and `FAILED` when an undo/redo step fails.
  Tests: `test_editor_cmd.c`.
- B2 (shell): `BreakEditorPlayState` EDIT / PLAYING / PAUSED with
  `break_editor_shell_play_state` and `break_editor_shell_play_frames`.
  - F5: EDIT -> PLAYING (marks history).
  - F6: same, but only when a current scene path is set; otherwise logs
    `play: no current scene` and stays in EDIT.
  - F7: PLAYING <-> PAUSED.
  - F8: rewind and return to EDIT; logs `play: stopped` or
    `play: stopped, changes kept (history lost)`.
  - While PLAYING, shell tick advances the play frame counter; PAUSED does
    not.
  - Ctrl+S and Ctrl+N are refused outside EDIT (`play: stop first`).
  - The status bar shows the play state.
  Tests: `test_editor_shell.c`.
- Out of scope: launching the scene in a separate core_app process.

## Verification

`cd build-core-app-master && cmake --build . -j16 && ctest -j8 --output-on-failure`,
plus the naming contract tests. Mutation check: drop each new branch and
confirm the test fails.

## Docs

- `docs/design/editor_phase1.md` §4 shortcut table.
- `docs/Implementation_Status.md` status entry.

## Status (2026-11-15)

Task A and Task B are delivered. See `docs/Implementation_Status.md`
("Editor Ctrl+Shift diagnostic shortcuts" and "Editor play mode (F5–F8)").
