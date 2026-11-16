# Editor plugin text in the editor language (2026-11-16)

## Goal
Plugin command labels (palette) and inspector section titles were shown in
whatever language the plugin passed to `add_command` / `add_section`. The
editor switches between en-US and zh-CN at runtime, so plugin text stayed
in one language while the rest of the UI changed. This slice lets a plugin
register a label per editor language and read the current language.

## Design
- Registries keep the text given to `add_*` as the source text and one
  optional translation per `BreakEditorLang`:
  - `break_editor_plugin_cmds_set_label(reg, owner, id, lang, label)` and
    `break_editor_plugin_sections_set_title(reg, owner, id, lang, title)`
    add or replace a translation. Only the owner of `id` may translate it
    (another owner gets `NOT_FOUND`). Check order: `INVALID` (NULL registry,
    owner 0), `BAD_LANG` (lang out of range), `BAD_LABEL` / `BAD_TITLE`
    (same rules as add), `NOT_FOUND`.
  - `_label_lang(reg, index, lang)` / `_title_lang(reg, index, lang)`
    return the translation when set, else the source text; NULL for an
    out-of-range index; an out-of-range lang gives the source text.
  - `add` clears the translations of the slot it fills, so a command added
    after `remove_owner` never shows a removed command's translation.
  - `break_editor_plugin_cmds_filter` takes the language and matches the
    label shown in that language or the id (not the source label).
  - New status values are appended: `*_NOT_FOUND`, `*_BAD_LANG`.
- `BreakEditorPluginApi` gets three appended fields (api_version stays 1):
  - `set_command_label(host, id, lang_tag, label)`
  - `set_section_title(host, id, lang_tag, title)`
  - `lang_tag(host)`: the current editor language tag ("en-US" /
    "zh-CN"), never NULL, usable at any time (for example inside a section
    callback to localize the section text).
  Tags go through `break_editor_i18n_parse_lang`, so the plugin ABI does not
  depend on the enum order. The set functions follow the load-window rule:
  outside a window they return `INVALID` before the tag is parsed.
- Shell: palette rows, the palette filter and inspector section titles use
  the current language. A language switch already refreshes the palette and
  rebuilds the inspector, so plugin text follows without new hooks.
- Fixture plugin: registers zh-CN text for its command and section, and its
  section text follows `lang_tag`.

## Tests (TDD)
- `test_editor_plugin_cmds`: `plugin_cmds_translated_labels` (fallback,
  replace, owner check, validation, stale-slot clearing, compaction keeps
  translations); `plugin_cmds_filter` passes a language and checks the
  shown label is what matches.
- `test_editor_plugin_sections`: `plugin_sections_translated_titles`.
- `test_editor_plugin_host`: `plugin_host_translations_need_the_owner_window`
  (window rule before tag parsing, tag forms, other owner refused, detached
  section registry, `lang_tag` follows the language).
- `test_editor_shell`: `plugin_text_follows_the_language` (inspector title
  and palette row and filter switch with `break_editor_shell_set_language`).
- `test_editor_plugin_load`: the real fixture registers zh-CN text; section
  text follows the language.

## Status
- RED: every new case failed against stubs (`set_label` / `set_title`
  returning INVALID, `label_lang` / `title_lang` ignoring the language,
  `lang_tag` returning ""). The real-plugin test was checked separately:
  with `set_command_label` forced to INVALID the fixture refuses to
  register and three `test_editor_plugin_load` cases fail.
- GREEN in `build-core-app-master` and `build-editor-plugins`.
- Mutation: 34 mutations (12 command registry, 11 section registry, 8
  host, 3 shell) all killed. Two survived the first run: the language range
  check written as `(int)lang >= 0 && lang < COUNT` lost its first half
  without any test noticing, because GCC treats the enum as unsigned. It is
  now one unsigned compare, `(u32)lang < (u32)COUNT`. A third survivor (the
  section title path did not need the load window before the registry
  check) is covered by a new host assertion.
- CI on `8bf2ce5b` (the sections slice) failed on MSVC only: C4456, a
  block-local `text` in `test_editor_plugin_load.c` hid the manifest
  buffer. The block's buffer is now `section_text`.
- Full ctest: default tree 412/412, plugins-ON tree 412/412, Snowflake
  network tree 420/420.
- Live, Fedora Wayland, plugins ON, `editor --lang zh-CN --plugin-manifest`
  with the real fixture: `plugins loaded 1, failed 0`. The fixture returns
  false from register unless `set_command_label` returns OK, so a load
  means the zh-CN label was accepted by the running editor.
