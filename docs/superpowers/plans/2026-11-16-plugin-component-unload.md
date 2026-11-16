# Plugin unload removes its component types (2026-11-16)

## Goal
A plugin can register editable component types through the plugin host
(`add_component`). A failed load drops them, but a release before unload
keeps them until the editor exits
(`docs/cross_engine/missing_capabilities.md` §12). This slice removes a
released plugin's types when no live entity uses them.

## Design
- `bool break_editor_doc_unregister_component(BreakEditorDoc *doc, u32 id)`
  in `editor_components.h`: removes one registered (non built-in) type from
  any registry position and keeps the order of the rest. False, nothing
  changed, for a NULL doc, a built-in id (Transform, Light), an id that is
  not registered, or a type a live entity has. Like
  `break_editor_doc_truncate_components`, the World keeps the type's size
  until the next reset, and undo history may re-add its bytes, which the
  registry-gated APIs then ignore.
  Entries after the removed one move down; their default bytes live inside
  the entry, so the default pointer is moved with them.
- Plugin host: records `{owner, component_id}` for every type registered
  through `add_component` (at most the registry capacity).
  - `end_load(false)` releases the owner, which unregisters the window's
    types (no entity can have them yet), then truncates to the window's
    start count as before.
  - `release(owner)` unregisters each of the owner's types; every removed
    type counts in the return value like a command, section or panel. A type
    still on a live entity stays registered and stays recorded, so a later
    `release` of the same owner can remove it.
  - `set_doc` to another doc forgets the records, so a release never removes
    a type from a doc the plugin did not register it in.
- The editor already releases every plugin on exit
  (`break_editor_plugin_loader_destroy`), before the doc is destroyed.

## TDD
- `test_editor_components`: `unregister_component_keeps_order_and_defaults`
  (rejections change nothing; removing a middle entry keeps the others'
  order, fields and default bytes; a type on a live entity is refused until
  the component is removed; the World size rule still applies).
- `test_editor_plugin_host`: `plugin_host_components_follow_the_window`
  changes from "release keeps types" to "release removes unused types, keeps
  used ones, a second release removes them once unused"; a new check that
  `set_doc` forgets the records.
- RED with a stub that returns false; GREEN; mutation run; ASan+UBSan.

## Status
Done.
- RED: with a stub returning false, `unregister_component_keeps_order_and_defaults`
  failed at its first removal and `plugin_host_components_follow_the_window`
  at the first release that should return 1; the other tests passed.
- GREEN: `test_editor_components` 27/27, `test_editor_plugin_host` 6/6, and
  the 11 plugin/component ctest entries pass; ASan+UBSan clean.
- 17 mutants (`/tmp/mut_plugin_unreg.py`): all caught. A first version kept
  a separate record-dropping path in `end_load(false)`; mutation showed it
  was redundant (release already drops those records), so it was removed.
  Clearing the vacated tail entry is not observable through the API
  (entries past the count are never read) and is kept only as hygiene.
