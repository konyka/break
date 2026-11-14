# Editor remote RENDER message

**Goal:** A remote client can read the render debugger panel and ask for a viewport shader reload. Today `docs/design/editor_remote.md` §9 lists "Remote render settings and backend switches" as not delivered, and `Implementation_Status.md` ends the remote-protocol entry with "未做：渲染设置的 remote 控制".

**Scope:** read the render rows, and trigger the same shader reload as Ctrl+Shift+R. Backend switches stay out: they need the device and swapchain rebuilt, and the editor has no runtime path for that.

## Wire format

- `BREAK_EDITOR_MSG_RENDER = 21`, registered in the default `break_net` registry like ids 4..20.
- Request: `action/u8`. 0 = query, 1 = request a shader reload. Any other action value: RESULT invalid, nothing happens (like VIEW's unknown mask bits). A payload that is not exactly 1 byte is a protocol error and closes the session without a response (like HISTORY with a payload).
- Response: `reload/u8` (1 = reload queued, 0 = query, or no viewport/reload owner), `rows/u8`, then per row `len/u8 + text`. The rows are the render debugger panel rows (≤ 16 rows of < 96 bytes), so the response stays far below 4096 B.

## Steps (TDD)

- [x] **Step 1: RED tests** in `engine/tests/test_editor_shell.c`:
  1. `remote_render_reports_the_render_debugger_rows`: the test shell with no device answers `reload=0, rows=1, "render: no device"`; with the fake render source and device, the rows match `break_editor_shell_render_row_text`.
  2. `remote_render_reload_without_viewport_reports_zero`: action 1 on the dummy-PAL shell answers `reload=0` and does not touch the doc revision.
  3. `remote_render_rejects_unknown_action_and_size`: action 2 gets RESULT invalid and the session stays open; a 2-byte payload closes the session.
  4. The registry test also covers id 21 and checks that 22 is free.
- [x] **Step 2: Implement.** `break_editor_shell_request_shader_reload` (shared by Ctrl+Shift+R and the remote), the handler, the handler id table, and the registry entry (counts 20/21).
- [x] **Step 3: fuzz.** `fuzz_editor_remote` covers 4..21.
- [x] **Step 4: Verify.** `test_editor_shell`, `ctest -L fuzz`, full normal ctest.
- [x] **Step 5: Docs.** `editor_remote.md` (message table, §8 id range, §9), `editor_render_debugger.md`, `Implementation_Status.md`, this plan.
- [x] **Step 6: Commit and push.** Confirm CI.

## Execution record (2026-11-14)

- The remote tests compile only with Snowflake and crypto. The local Snowflake checkout was not at the pinned commit, so the tree `build-core-integration-remote` uses a detached worktree of the pin (696a1ec5) in `/tmp/snowflake-pin`.
- RED: `BREAK_EDITOR_MSG_RENDER` and `break_editor_shell_request_shader_reload` undeclared. GREEN: `test_editor_shell` 195/195, remote tree editor/net subset 25/25, normal tree 400/400.
- `fuzz_editor_remote` did not link before this change (missing `editor_panel_flow.c`). Fixed in `engine/CMakeLists.txt`. 8 seeds x 20000 messages pass; RENDER accepted 165..213 times per seed.
