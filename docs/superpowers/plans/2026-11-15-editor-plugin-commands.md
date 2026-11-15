# Editor plugin command registry

## Goal

First slice of the editor plugin system: a bounded registry where plugins
(loaded through `engine/src/system/break_plugin.h`) contribute commands that
the command palette (Ctrl+P) can list and run. This slice is the registry
only; wiring it into `engine/apps/editor/editor_panels.c` is the next slice.

## Design

`engine/src/editor/editor_plugin_cmds.{h,c}`, added to `break_editor` and
`break_editor_test`.

- `BreakEditorPluginCmds *break_editor_plugin_cmds_create(u32 capacity)`;
  capacity 0 or above `BREAK_EDITOR_PLUGIN_CMDS_MAX` (256) gives NULL.
- `break_editor_plugin_cmds_add(reg, owner, id, label, fn, user)`.
  `owner` is a non-zero plugin key (for example the plugin handle index + 1).
  `id` is `[a-z0-9_.]`, 1–63 bytes; `label` is 1–95 bytes of printable text
  without control bytes. Duplicate ids, a full registry, NULL fn or invalid
  text are rejected with distinct statuses and change nothing.
- `break_editor_plugin_cmds_remove_owner(reg, owner)` drops every command of
  one plugin (called before `break_plugin_unload`) and returns the count.
  Order of the remaining commands is preserved.
- `count`, `label(index)`, `id(index)`, `find(id)`.
- `filter(reg, text, out, cap)`: case-insensitive ASCII substring match on
  label or id, in registration order, bounded by `cap`.
- `execute(reg, index, doc)` calls the callback with `(user, doc)` and
  returns its bool result; an out-of-range index returns false without a
  call.

## Tests (`test_editor_plugin_cmds`)

1. Create bounds and NULL handling.
2. Add, find, label/id lookup and execute pass the user pointer and doc.
3. Rejections: duplicate id, bad id characters, empty and over-long id and
   label, control bytes in label, NULL fn, owner 0, full registry.
4. remove_owner removes only that owner's commands and keeps order.
5. filter matches label or id case-insensitively and respects `cap`.

## Verification

RED, GREEN, mutation run over `editor_plugin_cmds.c`, full ctest.

## Status

Registry done. `test_editor_plugin_cmds` 5/5. Mutation run over
`editor_plugin_cmds.c`: first pass 3 of 45 survived. Two were redundant
checks and were removed: the `owner == 0` early return in `remove_owner`
(owner 0 can never be registered) and the `p[i] != '\0'` test in the
substring loop (the case-folded compare already stops at the haystack NUL
because the needle byte is never NUL inside the loop). The third was a
missing out-of-range test for `owner()`; tests for index == count were added
for `owner`, `id`, `label` and `execute`. Second pass: 43 of 43 killed.

Next slice: list and run these commands from the command palette in
`engine/apps/editor/editor_panels.c`, and register plugin commands from the
`break_plugin` register callback.

## Status（第二步：命令面板接入）

Done. The editor shell owns a 64-entry `BreakEditorPluginCmds`
(`break_editor_shell_plugin_cmds`). `break_editor_shell_palette_set_filter`
appends matching plugin commands after the built-in and recent rows
(`PAL_PLUGIN_0 + registry index`); the row text is the plugin label; Enter
or a row click runs the callback with the shell's doc. A callback that
returns false logs the new translated line
`BREAK_EDITOR_TR_LOG_PLUGIN_CMD_FAILED_FMT` ("plugin command '%s' failed" /
"插件命令 '%s' 执行失败").

Test `palette_lists_and_runs_plugin_commands` in `test_editor_shell`
(150/150): plugin rows are listed, filtered by label or id, run with the
doc, report failure, and disappear after `remove_owner`. `test_editor_i18n`
8/8 checks the new key in both languages. Mutation run over the new shell
code: 10 of 10 killed.

Still open: calling the registry from the `break_plugin` register and
unregister callbacks when the editor loads a plugin.
