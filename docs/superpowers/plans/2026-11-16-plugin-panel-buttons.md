# Buttons on plugin panels (2026-11-16)

## Goal
Plugin panels on the "Plugins" page of the bottom tool window show a title
and read-only text. They have no controls
(`docs/cross_engine/missing_capabilities.md` §12, "插件面板内的交互控件").
This slice lets a plugin put buttons on its panels; a click runs a plugin
callback on the doc, like a palette command.

## Design
- Registry (`editor_plugin_panels.h`): each panel holds up to
  `BREAK_EDITOR_PLUGIN_PANEL_BUTTONS_MAX` (4) buttons in add order.
  - `break_editor_plugin_panels_add_button(reg, owner, panel_id, button_id,
    label, fn, user)`. Checks in order: INVALID (NULL registry, owner 0,
    NULL fn), BAD_ID (button id, same rules as a panel id), BAD_TITLE
    (label, same rules as a title), NOT_FOUND (no panel `panel_id` owned by
    `owner`), DUPLICATE (button id already on that panel), FULL (4 buttons).
    Any rejection changes nothing. `fn` is `BreakEditorPluginPanelButtonFn`
    (`bool fn(void *user, BreakEditorDoc *doc)`): the click may edit the doc
    through doc commands, so it gets the non-const doc.
  - `break_editor_plugin_panels_set_button_label(reg, owner, panel_id,
    button_id, lang, label)`: INVALID, BAD_LANG, BAD_TITLE, NOT_FOUND
    (panel or button), like `set_title`.
  - `..._button_count(reg, index)`, `..._button_id(reg, index, b)`,
    `..._button_label(reg, index, b, lang)` (add-time label when the
    language has none), `..._press(reg, index, b, doc)` (false without a
    call for a bad index; otherwise the callback's result).
  - `remove_owner` removes the buttons with their panel.
- Plugin API: `add_panel_button` and `set_panel_button_label` appended to
  `BreakEditorPluginApi` (struct_size grows; same load-window and owner rules
  as `add_panel`).
- Shell: after a shown panel's text, a row named
  `editor-plugin-panel-buttons-<panel id>` with one button per entry named
  `editor-plugin-panel-button-<panel id>.<button id>`, labelled in the
  current language. A click runs `press` with the shell doc; false logs
  `BREAK_EDITOR_TR_LOG_PLUGIN_BUTTON_FAILED_FMT` ("plugin button
  '<panel id>.<button id>' failed"). Either way
  the shell refreshes (`editor_shell_refresh_all` + the Plugins page), so
  doc edits show at once. A panel with no buttons gets no row.
  The page is rebuilt by refresh, so a click context must not point into a
  destroyed widget: contexts live in a fixed shell pool
  (16 panels x 4 buttons) indexed by registry position.

## TDD
- `test_editor_plugin_panels`: add/label/press rules, ordering, owner
  checks, remove_owner drops buttons, NULL handling.
- `test_editor_plugin_host`: the two API entries follow the window and
  owner rules.
- `test_editor_shell`: the Plugins page shows the row and buttons in the
  current language; a click runs the callback with the shell doc, an edit
  made by it shows in the outliner, and a failing callback logs.
- RED with stubs; GREEN; mutation run; ASan+UBSan.

## Status
Done.
- RED: the new tests failed on the stubs (`test_editor_plugin_panels` 5/7,
  `test_editor_plugin_host` 6/7, `test_editor_shell` 155/156) while the old
  tests passed.
- GREEN: `test_editor_plugin_panels` 7/7, `test_editor_plugin_host` 7/7,
  `test_editor_shell` 156/156, `test_editor_i18n` 8/8.
- Mutation run: 37 mutations. The first pass left 4 alive; the host window
  check, the click-context reset and the panel index got new assertions,
  and the per-button `memset` was dropped as redundant (`panels_add` clears
  the whole slot and buttons are never removed alone). Rerun: 0 survivors.
- ASan+UBSan: no reports on the four tests.
- A click rebuilds the page and so destroys the clicked button; the myui
  emitter defers its own disposal while it is emitting
  (`my_emitter_destroy`), the same path the inspector add/remove buttons
  already use.
