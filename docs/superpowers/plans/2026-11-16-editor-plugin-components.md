# Editor plugin component types (2026-11-16)

## Goal
Plugins can add palette commands and read-only inspector sections, but they
cannot add data the user edits. The inspector already edits two built-in
component types (Transform, Light) with undo, save and load. This slice
lets a plugin register its own editable component type, so its fields get
the same inspector rows, undo, BSCN save/load, Lua access and remote
protocol support as the built-in types, without new UI code.

## Design
- `editor_components.h`: `break_editor_doc_register_component(doc, desc)`
  with `BreakEditorComponentDesc { component_id, display_name, size,
  fields, field_count, default_bytes }`.
  - Rules: `component_id` in 66..119 (64 and 65 are built in, 120 is the
    world streaming tile component, the ECS cap is 128); not already
    registered; `display_name` 1..31 bytes without control bytes and not
    used by another type (Lua and the remote protocol look types up by
    it); `size` 4..256 (the command snapshot cap), a multiple of 4, and
    equal to the size the doc's World already has for the id (the ECS
    keeps the first size); 1..9 fields, each with a name of 1..31 bytes, a
    known type, an offset that is a multiple of 4 and lies inside `size`,
    and no two fields at the same offset or with the same name;
    `default_bytes` NULL (all zero) or `size` bytes, copied into the doc.
  - Status enum `BreakEditorComponentRegStatus`: OK, INVALID, BAD_ID,
    DUPLICATE, BAD_NAME, BAD_SIZE, BAD_FIELD, FULL. Any rejection changes
    nothing.
  - The registry keeps registered types across `break_editor_doc_reset`
    and scene load (both rebuild the built-in entries today), so a plugin
    type survives "new scene" and "open scene".
  - `break_editor_doc_truncate_components(doc, count)` drops the newest
    registered types back to `count`, refusing when `count` is below the
    built-in entries or a dropped type is on a live entity. The host uses
    it to roll back a failed load. Plugin types otherwise stay for the
    editor session, also after the plugin unloads: the registry copied
    everything it needs.
- Plugin API: appended `add_component(host, desc)`; same load-window rule;
  INVALID while the host has no doc attached
  (`break_editor_plugin_host_set_doc`, ignored while a window is open).
  `end_load(false)` truncates the doc back to its count at `begin_load`;
  `release` keeps component types.
- Shell / editor main: attach the shell's doc to the plugin host before
  loading the manifest.
- Fixture plugin: registers a two-field component (`level` f32, `active`
  bool) and the load test edits it through the doc API.

## Tests (TDD)
- `test_editor_components`: registration bounds and every rejection,
  inspector info, get/set/undo on a plugin field, add/remove component
  undo with default bytes, survives reset and save/load round trip.
- `test_editor_plugin_host`: `add_component` window and doc rules.
- `test_editor_shell`: a registered type shows add/remove rows and field
  edits in the inspector.
- `test_editor_plugin_load`: the real fixture registers its component.

## Status
- RED: every new case failed against stubs (`register_component` returning
  INVALID, `truncate` returning false, `add_component` returning INVALID).
- GREEN in `build-core-app-master` and `build-editor-plugins`; the shell
  needed no change: the inspector already builds rows from the registry.
- Mutation: 36 mutations (31 registry, 5 host) all killed. Two survived the
  first run and were equivalent: `size < 4` versus `size < 1` (sizes are
  multiples of 4) and `count >= component_count` versus `>` in truncate.
  Both checks were rewritten to the simpler form (`size == 0`,
  `count > component_count`) so no redundant branch is left. Two
  mutations failed to build under `-Werror` and were rewritten with `&& 0`.
- `test_editor_lua`: `set_record_targets_a_registered_component` shows
  `brk.ecs.set` finds a registered type by display name and that unwritten
  fields keep the registered defaults. No code change was needed (the
  console already resolves names through the registry), so this case
  passed on first run; it guards the behavior rather than driving it.
- Full ctest: default tree 412/412, plugins-ON tree 412/412, Snowflake
  network tree 420/420.
- Live, Fedora Wayland, plugins ON: the editor loads the fixture
  (`plugins loaded 1, failed 0`) with the shell doc attached; the fixture
  registers `FixtureStats` during that load.
