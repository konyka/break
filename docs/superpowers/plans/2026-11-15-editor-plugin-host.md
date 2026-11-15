# Editor plugin host bridge

## Goal

Let a plugin loaded through `system/break_plugin.h` add commands to the
editor's plugin command registry (`editor_plugin_cmds`), and make sure its
commands are gone before its library is closed.

## Constraint

`test_break_system_target_contract` forbids linking `break_system` into the
`editor` executable. The bridge therefore lives in `break_editor` and never
calls `break_plugin_*`; the caller that owns the plugin manager wraps each
load and unload.

## Design

`engine/src/editor/editor_plugin_host.{h,c}`:

- `BreakEditorPluginApi { struct_size, api_version, host, add_command }`.
  The host passes `break_editor_plugin_host_api(host)` as the `plugin_user`
  of `break_plugin_create`; a plugin's `register_fn` casts its argument,
  checks `struct_size` and `api_version`, and calls `add_command`.
- `begin_load(host)` opens a load window and returns a fresh non-zero owner
  key (0 when a window is already open or host is NULL). `add_command`
  outside a window returns `BREAK_EDITOR_PLUGIN_CMD_INVALID`.
- `end_load(host, loaded)` closes the window. When `loaded` is false (the
  load failed, including a failed `register_fn`), the owner's commands are
  removed. Returns false when no window was open.
- `release(host, owner)` removes the owner's commands; call it before
  `break_plugin_unload`.

## Tests

- `test_editor_plugin_host` (always built): API fields, window rules, owner
  keys, failed-load cleanup, release, NULL handling.
- `test_editor_plugin_load` (Linux/Windows, when `break_system` exists):
  loads a real fixture plugin with a verified SHA-256, runs its command from
  the registry, unloads it after `release`; a second fixture adds a command
  and then fails registration, and the command must not remain.

## Verification

RED, GREEN, mutation run over `editor_plugin_host.c`, full ctest.

## Status

Done. `editor_plugin_host.{h,c}` is in `break_editor` and `break_editor_test`
and does not call `break_plugin_*`, so `test_break_system_target_contract`
still holds.

- `test_editor_plugin_host` 2/2: API fields, load window rules, distinct
  owner keys, failed-load cleanup, release, NULL handling.
- `test_editor_plugin_load` 2/2 (Linux/Windows, needs `break_system`): two
  real shared-library fixtures from `tests/fixtures/editor_test_plugin.c`.
  One adds `fixture.hello`, which runs from the registry and is gone after
  release + unload. The other adds a command and then fails registration;
  `break_plugin_load` returns FAILED and the command is not left behind.
- Mutation run over `editor_plugin_host.c`: first pass 1 of 14 survived. It
  was a redundant `loading_owner == 0` check in `add_command`; the registry
  already rejects owner 0, so the check was removed. Second pass: 13 of 13
  killed.

Still open: the editor executable does not create a plugin manager or load
plugins at startup (it may not link `break_system`); plugin panels and
inspector extensions.
