# Editor plugin inspector sections (2026-11-16)

## Goal
Plugins could add palette commands only. This slice adds the first
inspector extension point: a plugin registers a read-only section that the
inspector shows for the selected entity.

## Design
- `engine/src/editor/editor_plugin_sections.[ch]`: a bounded registry
  (capacity 1..64), in the same shape as `editor_plugin_cmds`. Each section
  has a non-zero owner key, an id of `[a-z0-9_.]` (1..63 bytes), a title of
  1..95 bytes without control bytes, and a callback
  `bool fn(user, const BreakEditorDoc *, BreakEditorEntityId, char *out, usize cap)`.
  The doc is const: sections only read, edits go through commands.
  `describe` always NUL-terminates `out[cap - 1]` (even when the callback
  overruns its terminator) and clears `out` when the callback declines.
- `BreakEditorPluginApi` gets an appended field `add_section`. The struct
  only grows at the end; `api_version` stays 1. The host attaches a registry
  with `break_editor_plugin_host_set_sections`. Without one, `add_section`
  returns INVALID. Sections share the owner key of the load window, so a
  failed load and `release` drop them together with the commands.
- The shell owns a section registry (`break_editor_shell_plugin_sections`).
  `shell_rebuild_inspector` appends, after the component rows, a title label
  `editor-plugin-section-title-<id>` and a text label
  `editor-plugin-section-<id>` for every section that accepts the selected
  entity. Text is capped at 256 bytes.
- `editor_main.c` (`BREAK_EDITOR_PLUGINS`) attaches the shell registry to
  the plugin host before loading the manifest.

## Tests (TDD)
- `test_editor_plugin_sections` (4): create bounds, validation and order,
  `remove_owner`, `describe` truncation, termination and decline.
- `test_editor_plugin_host`: new `plugin_host_sections_follow_owner_keys`.
- `test_editor_shell`: new `inspector_shows_plugin_sections` (two shown
  sections after the built-in rows in registry order, a declining section
  absent, text refreshed on rebuild, removal by owner).
- `test_editor_plugin_load`: the real fixture plugin also adds
  `fixture.section`; the failing fixture's section is dropped; destroy
  clears it.

## Status
- RED: every new case failed against stubs (NULL registry, `add_section`
  returning INVALID, shell accessor returning NULL).
- GREEN in `build-core-app-master` and `build-editor-plugins`.
- Mutation: 20 registry, 6 host and 6 inspector mutations killed. One
  inspector mutation (title looked up at index 0) survived until a second
  shown section at index 2 was added to the shell test.
- Live, Fedora Wayland, plugins ON: the fixture plugin loads
  (`plugins loaded 1, failed 0`).
- Still missing: editable plugin fields in the inspector, dockable plugin
  panels, and sections in languages other than the plugin's own text (the
  title is not passed through `break_editor_tr`).
