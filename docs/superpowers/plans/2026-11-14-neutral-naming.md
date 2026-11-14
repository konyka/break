# Neutral Naming Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Remove the words "game", "玩家" and "敌人" from the repository's own code, build files and current docs. Remove the `cry` prefix from the repository's own names.

**Architecture:** First add a repository-level naming contract test (`test_repo_naming_contract`). It scans tracked files and fails on forbidden words. Then complete the renames in order: kernel module, remaining code identifiers and comments, pad input, docs. After each step the contract's exemption list gets shorter. When every step is done, only system SDK names and third-party reference material remain exempt.

**Tech Stack:** C11, C++20 header checks, CMake 3.25+ script-mode tests, `git mv`.

## Global Constraints

- Naming follows the existing repository conventions: `break_<module>_<verb>` functions, `Break<Module><Noun>` types, `BREAK_<MODULE>_<NAME>` macros. Files use snake_case. This matches the Google C/C++ style of lowercase file names and descriptive names.
- The words `game`, `Game` and `GAME` must not appear in code, build files or current docs, and neither may `玩家` or `敌人`. Use `user`, `chaser`, `user A`/`user B`, `application` or `kernel` instead.
- Names must not use the `cry`/`Cry`/`CRY` prefix. `crypto` is a different word and is not affected.
- Exemptions, and only these: system SDK names that cannot be changed (`XINPUT_GAMEPAD*`, Linux `BTN_GAMEPAD`, Windows `XINPUT_GAMEPAD` struct); `docs/ue5.8.3/**` (the real Unreal Engine API names it quotes); `engine/external/**` and `third_party/**`; the original names of external projects (`CryENGINE`, `T3DGameR1`, the BW191 docs) in the cross-engine comparison docs. Historical ledgers under `.superpowers/` stay unchanged.
- Do not overwrite existing docs. Update terms in place, move file names with `git mv`, and update links.
- Behavior and the BSCN/Flow/checkpoint data formats stay byte-for-byte the same. The Flow magic `BREAKFG` is not a forbidden word and stays.

## New names (Task 1)

| Old | New |
|---|---|
| `engine/src/game/` | `engine/src/kernel/` |
| `break_game*.c/h` | `break_kernel*.c/h` |
| `break_game_*` functions, `break_game` target | `break_kernel_*`, `break_kernel` |
| `BreakGame*` types | `BreakKernel*` |
| `BREAK_GAME_*` macros | `BREAK_KERNEL_*` |
| `break_game_lua` target/header/`BreakGameLua*` | `break_kernel_lua` / `BreakKernelLua*` |
| `test_break_game_<x>`, label `break_game` | `test_break_kernel_<x>`, label `break_kernel` |
| `test_cry_style_prototype` | `test_core_style_prototype` |
| `game/break_flow*.c/h` | `kernel/break_flow*.c/h` (Flow names unchanged) |
| test locals `make_game`/`destroy_game`/`game_test`/`f.game`/`game_cfg`/`game_pos`/`game_level`/`map_game_error` | `make_kernel`/`destroy_kernel`/`kernel_test`/`f.kernel`/`kernel_cfg`/`kernel_pos`/`kernel_level`/`map_kernel_error` |
| `GAME_TEST_WRAP_FS` | `KERNEL_TEST_WRAP_FS` |

## New names (Task 3, pad input)

| Old | New |
|---|---|
| `engine/src/platform/gamepad_linux.c/h`, `gamepad_win.c` | `pad_linux.c/h`, `pad_win.c` |
| `GamepadState`/`GamepadDevice`/`GamepadSystem`/`GamepadSystemWin` | `PadState`/`PadDevice`/`PadSystem`/`PadSystemWin` |
| `gamepad_init`/`gamepad_poll`/`gamepad_shutdown`/`gamepad_feedback_poll` | `pad_init`/`pad_poll`/`pad_shutdown`/`pad_feedback_poll` |
| `GAMEPAD_BTN_*`/`GAMEPAD_AXIS_*`/`INPUT_MAX_GAMEPADS` | `PAD_BTN_*`/`PAD_AXIS_*`/`INPUT_MAX_PADS` |
| `g_gamepad_sys`, `gamepads` fields, `fd_is_gamepad`, `evdev_btn_to_gamepad` | `g_pad_sys`, `pads`, `fd_is_pad`, `evdev_btn_to_pad` |
| `test_gamepad_*`, `GAMEPAD_WIN_PORTABLE_TEST` | `test_pad_*`, `PAD_WIN_PORTABLE_TEST` |

Before Task 3 starts, check `git grep -w -E "pad|PadState|PAD_BTN"` to confirm the new names do not collide with existing locals.

---

### Task 1: Repository naming contract and kernel module rename

**Files:**
- Create: `engine/tests/test_repo_naming_contract.cmake`
- Modify: `engine/CMakeLists.txt` (register test; rename targets/sources/tests)
- Move: `engine/src/game/*` → `engine/src/kernel/*`, `engine/tests/test_break_game_*` → `test_break_kernel_*`, `engine/tests/test_cry_style_prototype.c` → `test_core_style_prototype.c`
- Modify: every consumer listed by `git grep -l -E "break_game|BreakGame|BREAK_GAME|game/break_"` under `engine/`
- Modify: `engine/tests/test_core_app_naming_contract.cmake` (drop the `break_game` exemptions)

**Interfaces:**
- Produces: the `BreakKernel*` API (same signatures as before with the new prefix), target `break_kernel`, target `break_kernel_lua`, and the contract test `test_repo_naming_contract`, which takes `-DREPOSITORY_ROOT -DSTAGE=<n>`.

- [x] **Step 1: Write the contract test.** It walks fixed roots with `file(GLOB_RECURSE)` (no Git needed, so the clean-room export also works, and `build-*` directories are never entered), drops the exempt paths, and reads each text file. The contract file itself and this plan quote the forbidden words and are exempt. It rejects `[Gg]ame|GAME|玩家|敌人` and the prefix pattern `(^|[^A-Za-z])(cry_|Cry[A-Z]|CRY_)`. Before matching it removes the exempt tokens (`XINPUT_GAMEPAD[A-Z_]*`, `BTN_GAMEPAD`, `CryENGINE`, `T3DGameR1`). `STAGE` controls which scan scopes are active: 1 = `engine/src/kernel` and `engine/src/game` paths plus every `break_game` token in `engine/`; 2 = all of `engine/` except pad files; 3 = `engine/` including pad; 4 = add `docs/` (except `docs/ue5.8.3`), `README.md` and `CMakeLists.txt`. Every task raises the `STAGE` registered in CMake.
- [x] **Step 2: Register it with `STAGE=1`** (label `headless;platform_contract`). Run `ctest -R test_repo_naming_contract`. Expected: FAIL, with `engine/src/game/break_game.h` listed.
- [x] **Step 3: Rename the files with `git mv`.** Then use `sed` to replace whole-word `break_game`→`break_kernel`, `BreakGame`→`BreakKernel`, `BREAK_GAME`→`BREAK_KERNEL` and `game/break_`→`kernel/break_` in `engine/`, plus the local names from the table above. Rename `test_cry_style_prototype`→`test_core_style_prototype`. Change the CMake comment "Gameplay kernel" to "Actor kernel".
- [x] **Step 4: Remove the `break_game` exemption lines** from `test_core_app_naming_contract.cmake`.
- [x] **Step 5: Build `build-core-integration-normal`.** Run `ctest -R "naming_contract|break_kernel|break_flow|core_style|core_app|editor_flow|public_api"` first, then the full `ctest -j8`. Expected: all pass, with the same test count as before (399).
- [x] **Step 6: Commit** with the message `refactor: rename the actor kernel from break_game to break_kernel`.

> 2026-11-14 执行记录：Task 1 提交 `4f18a145`。RED 为 stage 1 契约列出 `engine/src/game` 与 `break_game` 目标；改名后 normal 树全量 400/400（新增本契约一项）。`test_core_app_naming_contract` 原先豁免 `break_game` 的行已删除；core_app 计划/设计文档的当前段落同步改为 `break_kernel`，历史段落未改。

### Task 2: Remaining code wording

**Files:** comments and strings in `engine/src/{editor,network,runtime,renderer,authority,crash,platform}`, `engine/src/main.c`, `engine/apps/editor/editor_remote.h`, and the `engine/tests` files listed by `git grep -n -i game -- engine | grep -v -i gamepad`.

- [x] **Step 1: Raise the contract to `STAGE=2`.** Expected: FAIL, listing `editor_scene.c`, `break_session.h`, `test_break_crash_cluster.c` and others.
- [x] **Step 2: Replace the wording.** "GameThread" → "logic thread". "game-side chunks"/"kept game chunks" → "application chunks". "game loader" → "application loader". "gameplay" → "action keys"/"interaction". The crash test's module name `"game"` → `"app"`. Rename `path_longer_than_63_is_cut_like_the_game_loader_and_stays_in_bounds` → `path_longer_than_63_is_cut_like_the_scene_loader_and_stays_in_bounds`. Rename `non_game_thread_is_rejected_without_mutation` → `non_logic_thread_is_rejected_without_mutation`.
- [x] **Step 3: Run the full ctest.** Expected: all pass.
- [x] **Step 4: Commit** with the message `refactor: describe engine threads and chunks without the legacy domain word`.

> 2026-11-14 执行记录：Task 2 提交 `4f0f2198`。RED 为 stage 2 契约列出 15 个文件（`break_session.h`、`editor_scene.c`、`test_break_crash_cluster.c` 等）；替换后 stage 2 扫描 1308 个文件全部通过，normal 树全量 400/400。契约在 stage 3 之前跳过路径含 `gamepad`/`xinput` 的文件，`gamepad_linux.c` 的注释留到 Task 3。`editor_remote.h` 实际位于 `engine/apps/editor/`。

### Task 3: Pad input names

- [x] **Step 1: Raise the contract to `STAGE=3`.** Expected: FAIL on `gamepad_linux.c`.
- [x] **Step 2: Rename files and identifiers** per the Task 3 table, leaving only the SDK names.
- [x] **Step 3: Run the full ctest.** Then build the `fake_windows` portable test (`test_pad_win_feedback_portable`). Expected: all pass.
- [x] **Step 4: Commit** with the message `refactor: name controller input pad instead of the legacy device word`.

> 2026-11-14 执行记录：Task 3 提交 `45157387`。RED 为 stage 3 契约列出 35 处；`gamepad_linux.c/h`、`gamepad_win.c` 改为 `pad_linux.c/h`、`pad_win.c`，`InputState.gamepads` 改为 `pads`，其余按上表改名。SDK 名 `XINPUT_GAMEPAD*`、`BTN_GAMEPAD` 以及 XInput 结构体成员 `Gamepad`（`st.Gamepad`、`XINPUT_GAMEPAD Gamepad;`）列入契约豁免。stage 3 扫描 1308 个文件通过，normal 树全量 400/400，含 `test_pad_win_feedback_portable`。另修复：CI 镜像中的 CMake 在 `-P` 模式下默认使用旧策略，导致 `IN_LIST` 报错（bfb9a1c8 的 Linux 通道全部因此失败）；契约脚本加入 `cmake_policy(VERSION 3.20)`。

### Task 4: Current docs

- [ ] **Step 1: Raise the contract to `STAGE=4`.** Expected: FAIL listing docs.
- [ ] **Step 2: Rename doc files with `git mv`.** `docs/design/gameplay_items_weapons.md` → `items_weapons.md`, `docs/design/online_gameplay_network.md` → `online_session_network.md`, and the files under `docs/superpowers/plans|specs` whose names contain `game`/`cry` (replace `cry-style-gameplay` with `core-style-actions`, and so on). Update every link.
- [ ] **Step 3: Update terms in the doc bodies.** 玩家 → 用户 / 用户 A、B; 敌人 → 追踪者; game → 应用/逻辑. Third-party names in the cross-engine docs stay inside backticks and are covered by the exempt-token list.
- [ ] **Step 4: Run the full ctest**, including the doc link/contract tests.
- [ ] **Step 5: Commit, push to `master`, and confirm CI passes on every lane.**

## Verification

- Full ctest in `build-core-integration-normal` passes. The core_app/kernel tests in `build-core-integration-asan` pass. The CI and windows-d3d12 workflows pass.
- After Task 4, `git grep -I -n -i -E "game|玩家|敌人" -- . ':!docs/ue5.8.3' ':!engine/external' ':!third_party' ':!.superpowers'` prints only the exempt tokens.
