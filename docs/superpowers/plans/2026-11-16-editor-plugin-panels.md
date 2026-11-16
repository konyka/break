# Editor plugin panels (2026-11-16)

## Goal
Plugins can add commands, inspector sections and component types, but they
cannot show anything that is not tied to the selected entity (build output,
a validation report, statistics over the whole scene). This slice adds a
"Plugins" page to the bottom tool window where each plugin panel shows a
title and a block of read-only text, refreshed while the page is visible.

## Design
- `engine/src/editor/editor_plugin_panels.[ch]`: a bounded registry in the
  shape of `editor_plugin_sections` (capacity 1..16, owner keys, id
  `[a-z0-9_.]` 1..63 bytes, title 1..95 bytes, per-language titles, a
  text callback `bool fn(void *user, const BreakEditorDoc *doc, char *out,
  usize cap)` with cap `BREAK_EDITOR_PLUGIN_PANEL_TEXT_CAPACITY` = 1024).
  `render` always terminates the text and clears it when the callback
  declines.
- Plugin API: appended `add_panel(host, id, title, fn, user)` and
  `set_panel_title(host, id, lang_tag, title)`, same window and owner
  rules as sections; `release` and a failed load remove panels too.
- Shell: the bottom tool window gets a fourth tab, "Plugins" / "插件"
  (`BREAK_EDITOR_TR_TAB_PLUGINS`), page `editor-plugins-panel`. The page
  holds one title label `editor-plugin-panel-title-<id>` and one text label
  `editor-plugin-panel-<id>` per panel that accepts, rebuilt by
  `break_editor_shell_refresh_plugin_panels` and from the tick at most
  every 250 ms while the page is visible. With no panels the page shows
  one translated hint label `editor-plugins-empty`.
- Settings: `bottom_tab` accepts 0..3 (was 0..2) so the page is restored.
- Fixture plugin: one panel whose text counts the doc's entities.

## Tests (TDD)
- `test_editor_plugin_panels`: registry bounds, validation, order,
  remove_owner, translations, render truncation/termination/decline.
- `test_editor_plugin_host`: `add_panel` / `set_panel_title` window rules.
- `test_editor_shell`: the fourth tab selects the page; panel labels in
  registry order, declined panels absent, text refreshed, the empty hint,
  language switch, bottom_tab 3 restored from settings.
- `test_editor_settings`: bottom_tab 3 round trip, 4 rejected.
- `test_editor_i18n`: the new key is translated (existing coverage test).
- `test_editor_plugin_load`: the real fixture adds its panel.

## Status
- RED: the registry tests failed against stubs (create returning NULL), the
  host test against `add_panel` returning INVALID, the shell test against a
  NULL panel accessor and a 3-tab bottom strip, the settings test against
  the old `bottom_tab` bound of 3, and `test_editor_i18n` against the two
  new keys before the tables had them.
- GREEN in `build-core-app-master` and `build-editor-plugins`.
- The fixture first counted entities with `break_editor_doc_entity_count`.
  That left an undefined symbol, and `break_plugin` loads with `RTLD_NOW`,
  so the load failed. Plugins must reach the editor only through the API
  table; the fixture panel now reports its own render count.
- Mutation: 53 mutations (31 registry, 7 host, 13 shell, 2 settings) all
  killed. Two survived the first run: clearing the text of a declining
  panel (the test callback wrote nothing before declining; it now writes
  partial text first) and the tick condition (no test drove the tick
  across the 250 ms throttle; an injectable clock,
  `break_editor_shell_set_plugin_panels_clock_for_test`, now pins it).
- Full ctest: default tree 413/413, plugins-ON tree 413/413, Snowflake
  network tree 421/421 (one new test,
  `test_editor_plugin_panels`).
- Live, Fedora Wayland, plugins ON, `editor --lang zh-CN --plugin-manifest`
  with the real fixture: `plugins loaded 1, failed 0`; the fixture adds
  `fixture.panel` during that load. The page content was not inspected on
  screen; `test_editor_shell` covers the widget tree.
