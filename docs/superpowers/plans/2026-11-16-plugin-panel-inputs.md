# Text inputs on plugin panels (2026-11-16)

## Goal
Plugin panels can show text and buttons
(`2026-11-16-plugin-panel-buttons.md`). The last missing control listed in
`docs/cross_engine/missing_capabilities.md` §12 is a text input. This slice
lets a plugin put single-line inputs on its panels; Enter submits the text
to a plugin callback on the doc.

## Design
- Registry (`editor_plugin_panels.h`): each panel holds up to
  `BREAK_EDITOR_PLUGIN_PANEL_INPUTS_MAX` (2) inputs in add order. Each
  input has an id, a hint (shown while empty, translatable), a draft text
  of at most `BREAK_EDITOR_PLUGIN_PANEL_INPUT_CAPACITY` (1024) bytes
  including the terminator, and a submit callback
  `bool fn(void *user, BreakEditorDoc *doc, const char *text)`.
  - `break_editor_plugin_panels_add_input(reg, owner, panel_id, input_id,
    hint, fn, user)`: same check order as `add_button` (INVALID, BAD_ID,
    BAD_TITLE for the hint, NOT_FOUND, DUPLICATE, FULL). Ids are unique
    per kind: an input may share an id with a button.
  - `break_editor_plugin_panels_set_input_hint(reg, owner, panel_id,
    input_id, lang, hint)`: like `set_button_label`.
  - `..._input_count`, `..._input_id`, `..._input_hint(lang)` (add-time hint
    as fallback), `..._input_text` (draft, "" at first).
  - `..._set_input_text(reg, index, i, text)`: false for a bad index, NULL
    text, text that does not fit or has control bytes; the draft is then
    unchanged.
  - `..._submit(reg, index, i, doc)`: runs the callback with the draft;
    false without a call for a bad index.
- Plugin API: `add_panel_input` and `set_panel_input_hint` appended to
  `BreakEditorPluginApi`, same rules as the button entries.
- Shell: after a shown panel's text and before its button row, one edit
  per input named `editor-plugin-panel-input-<panel id>.<input id>`, with
  the hint in the current language, the draft as text and a 255-codepoint
  limit (4 bytes each fits the 1024-byte draft). "changed" stores the
  draft; "activate" (Enter) stores it, submits, logs a false result with
  `BREAK_EDITOR_TR_LOG_PLUGIN_INPUT_FAILED_FMT` and rebuilds the views and
  the page. Click contexts live in a fixed pool (16 panels x 2 inputs).
- The timed refresh (tick, every 250 ms while visible) skips the rebuild
  while the focused widget is inside the Plugins page, so typing is not
  interrupted; explicit refreshes still rebuild.

## TDD
- `test_editor_plugin_panels`: add/hint/text/submit rules and ordering,
  owner checks, draft bounds, remove_owner moves inputs with their panel.
- `test_editor_plugin_host`: the two API entries follow the window and
  owner rules.
- `test_editor_shell`: edits appear with hint and draft; "changed" stores
  the draft, which survives a rebuild; Enter submits with the shell doc;
  a false result is logged; the tick does not rebuild while an input has
  focus and does after focus leaves.
- RED with stubs; GREEN; mutation run; ASan+UBSan.

## Status
Done.
- RED: the new tests failed on the stubs (`test_editor_plugin_panels` 7/9,
  `test_editor_plugin_host` 7/8, `test_editor_shell` 156/157) while the old
  tests passed.
- GREEN: `test_editor_plugin_panels` 9/9, `test_editor_plugin_host` 8/8,
  `test_editor_shell` 157/157, `test_editor_i18n` 8/8.
- Mutation run: 48 mutations. The first pass left 4 alive (panel bound of
  the input accessors, input count bound, click-context reset and panel
  index); new assertions read the slot past the end after remove_owner and
  use an input on a second panel across 40 rebuilds. Rerun: 0 survivors.
- ASan+UBSan: no reports on the four tests.
- Removing a focused widget clears the dispatcher focus, so after Enter the
  shell looks the rebuilt edit up by name and focuses it again.
