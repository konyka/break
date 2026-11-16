# Editor plugin loader (2026-11-16)

## Goal
`editor --plugin-manifest PATH` validates the manifest in every build. This
slice makes the editor actually load the listed plugins, so their commands
show up in the command palette, without letting `break_system` into the
default editor.

## Constraints
- `test_break_system_target_contract` forbids `break_system` on any
  `target_link_libraries(editor ...)` line. That stays true: the editor
  links an intermediate library, `break_editor_plugin_loader`, and only when
  the CMake option `BREAK_EDITOR_PLUGINS` (default OFF) is set.
- The contract test now also checks that the option exists with default OFF,
  and that the only editor link to the loader sits inside
  `if(BREAK_EDITOR_PLUGINS)`.
- Plugins load after the shell exists (the shell owns the command registry)
  and unload before the shell is destroyed.

## Design
- `engine/src/editor/editor_plugin_loader.[ch]`:
  - `break_editor_plugin_loader_create(host)` owns a `BreakPluginManager`
    with capacity `BREAK_EDITOR_PLUGIN_MANIFEST_MAX` (32), passing the
    host's `BreakEditorPluginApi` as the plugin user pointer.
  - `_load_manifest(loader, manifest, report)` runs
    `break_editor_plugin_manifest_load_all` with `break_plugin_load` as the
    callback and records the owner key of each plugin that loaded. Several
    manifests may be loaded into one loader.
  - `_count(loader)` gives the number of loaded plugins.
  - `_destroy(loader)` removes every plugin's commands, then
    `break_plugin_destroy` unloads the libraries newest first.
- `editor_main.c` (`#ifdef BREAK_EDITOR_PLUGINS`): creates a plugin host over
  `break_editor_shell_plugin_cmds(shell)`, loads the manifest, prints each
  failed entry and `plugins loaded N, failed M`. At shutdown it destroys the
  loader and the host before the shell.

## Tests (TDD)
- `test_editor_plugin_load` (Linux/Windows, real shared fixtures): new
  `loader_loads_a_manifest_and_unloads_on_destroy` and
  `loader_rejects_null_arguments`. On Linux the test also checks
  `/proc/self/maps` for the sealed memfd mapping
  (`memfd:break-verified-plugin`) before and after destroy, so it proves the
  library is unloaded, not only that the commands are gone.
- `test_editor_plugin_manifest_cli` takes `-DPLUGINS=${BREAK_EDITOR_PLUGINS}`
  and expects the matching stderr note.
- `test_break_system_target_contract` covers the option rules.

## Status
- RED: the two loader cases failed against stubs (`loader is NULL`).
- GREEN in `build-core-app-master` (plugins OFF) and `build-editor-plugins`
  (`-DBREAK_EDITOR_PLUGINS=ON`): `test_editor_plugin_load` 5/5,
  `test_editor_plugin_manifest_cli` and the target contract pass.
- Mutation: 9 loader mutations killed. The first version had a bound check
  and a pending-handle table that were unreachable (the manager's capacity
  already stops a 33rd load, and destroy unloads without handles). They were
  removed, and `_destroy` now returns void. The `/proc/self/maps` check was
  added to kill the "skip break_plugin_destroy" mutation. 4 CMake variants
  (option default ON, link outside the `if`, a second link, a direct
  `break_system` link) all fail the contract test.
- Live, Fedora Wayland, plugins ON: a manifest with the good fixture and the
  failing fixture prints `plugin editor-test-plugin-fail failed to load` and
  `plugins loaded 1, failed 1`.
- Still missing: plugin panels and inspector extension points; no CI job
  builds with `BREAK_EDITOR_PLUGINS=ON` yet; on macOS `test_editor_plugin_load`
  is not registered (break_plugin is Linux/Windows only).
