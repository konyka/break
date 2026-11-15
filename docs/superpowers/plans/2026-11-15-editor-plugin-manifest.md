# Editor plugin manifest: discover and load plugins at startup

## Goal
`editor_plugin_host` lets a real `break_plugin` library add palette
commands, but nothing tells the editor which plugins to load. Add a plugin
manifest and a loader that opens one host window per entry, so a startup
path can load every listed plugin and drop the commands of any that fail.

## Constraints
- `break_editor` (and every `editor*` target) must not link `break_system`
  (`test_break_system_target_contract`). The loader therefore never calls
  `break_plugin_*`; the caller passes a load callback. The integration test
  passes an adapter over the real `break_plugin_load`.

## Design
- New `engine/src/editor/editor_plugin_manifest.{h,c}` in `break_editor` and
  `break_editor_test`.
- Text format, one entry per line, `#` comments and blank lines ignored,
  optional trailing `\r`:
  `plugin <build_id> <sha256 hex, 64 chars> <path to end of line>`
  - build_id: 1..63 bytes in 0x21..0x7e (the `break_plugin` token rule).
  - A relative path is joined to `base_dir` with `/`; the result must fit
    1024 bytes (`BREAK_PLUGIN_PATH_CAPACITY`).
  - Unknown keyword, bad token, bad hex, empty path, duplicate path, a NUL
    byte or more than 32 entries fail the whole parse; `error_line` gives the
    1-based line. A failed parse loads nothing.
- `break_editor_plugin_manifest_load_all(manifest, host, load_fn, user,
  report)`: for each entry, `begin_load`, call `load_fn`, `end_load(ok)`.
  The report keeps loaded/failed counts and the owner key of each loaded
  entry (0 for failed), so a shutdown path can `release` them.

## Tests
- `test_editor_plugin_manifest` (break_editor_test only): parse accepts
  comments, CRLF, absolute and relative paths; rejects each bad form with the
  right line; load_all with a fake load_fn that adds a command or fails gives
  the right counts, owners and registry contents.
- `test_editor_plugin_load` gains a manifest test with the real fixtures:
  good plugin, plugin whose registration fails, and an entry with a wrong
  hash. Result: loaded 1, failed 2, one `fixture.hello` command.

## Docs
- Status here, `docs/Implementation_Status.md`,
  `docs/cross_engine/missing_capabilities.md` section 12.

## Status
- RED: `test_editor_plugin_manifest` failed to compile (header missing).
- GREEN: `editor_plugin_manifest.[ch]` added to `break_editor` and
  `break_editor_test`; `ctest -R editor_plugin` 4/4 in `build-core-app-master`.
- Mutation: 15 single-site mutations of `editor_plugin_manifest.c`, all killed
  after adding cases for 0x01/0x7f/0x80 bytes in build ids and paths and a
  non-hex low nibble. The `end_load` return check in `load_all` was dead code
  (end_load cannot fail after a successful begin_load) and was removed.
- Still missing: the `editor` binary does not read a manifest at startup yet.
  `break_system` may not be linked into `editor`, so wiring needs an optional
  loader library or a callback injected from `editor_main.c`. No plugin panel
  and no inspector extension points yet.
