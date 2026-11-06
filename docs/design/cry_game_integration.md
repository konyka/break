# Cry Game 真实集成

日期：2026-11-06

## 当前状态

P12 Task 1 已建立独立 `cry_game` 可执行应用及 `cry_game_core` 静态库，并交付严格命令行入口和真实进程合同测试。完整关卡、输入、模拟、渲染、音频命令、checkpoint 和卸载生命周期尚未实现；当前 `cry_game_run()` 对合法配置明确返回 `BREAK_RUNTIME_FAILED`，进程退出 2，不以空壳返回成功。

## Target 与依赖边界

- `cry_game_core` 是顶层 C11 静态库，独立于 `ENGINE_BUILD_TESTS`，当前拥有 `apps/cry_game/cry_game.c`。
- `cry_game` 是真实可执行目标，拥有 `apps/cry_game/main.c`，链接 `cry_game_core` 并经 `engine_link_rhi_backend(cry_game)` 使用现有 RHI 选择链。
- `cry_game_core` 显式链接 `engine`、`break_game`、`break_ai`、`break_flow`、`break_lua`、`break_game_lua` 和 `runtime_core`。
- `engine`、`engine_demo`、`dxx_break` 不链接上述新增集成层。Actor/Lua 适配器使用 `engine/src/game/break_game_lua.h`；世界呈现 API 位于 `engine/src/renderer/world_presentation.h`。
- `CRY_GAME_ENABLE_NETWORK` 默认 `OFF`。本任务没有网络实现；未启用网络时 `--network` 被真实进程拒绝。

## 命令行合同

```text
cry_game --help
cry_game [--render record|auto|vulkan|opengl]
         [--audio record|null|device]
         [--assets DIR] [--scenario PATH] [--checkpoint DIR]
         [--trace PATH] [--screenshot PATH]
         [--fixed-step] [--frames N] [--require-device] [--network]
```

带值选项同时接受 `--name value` 和 `--name=value`。默认资产目录为 `assets/cry_game`，渲染为 `auto`，音频为 `device`。`--frames` 只接受 1..4294967295 的十进制整数。未知参数、空值、非法枚举、缺值和 `--help` 后额外参数均退出 2。`--help` 单独使用退出 0 并输出 `Usage: cry_game` 及全部选项。

合法配置目前进入 `cry_game_run()`，随后因生命周期尚未实现退出 2；无参数调用同样不得返回 0。后续真实设备不可用证据码 77 将在对应图形/音频任务接入，本任务不伪造该证据。

## 验证

`test_cry_game_target_contract` 同时检查 CMake target/链接边界和真实进程行为，覆盖帮助、未知参数、`--render=headless`、缺值、network-off、未实现不伪成功、全部带值选项及多余帮助参数；有 `nm` 时扫描生产二进制的 `_for_test`/`test_hook` 符号。

从工作树根运行：

```bash
cmake -S engine -B build-cry-integration-normal \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-cry-integration-normal -j3 --target cry_game
ctest --test-dir build-cry-integration-normal \
  -R '^test_cry_game_target_contract$' --output-on-failure

cmake -S engine -B build-cry-integration-no-tests \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=OFF \
  -DENGINE_ENABLE_IPO=OFF -DENGINE_RHI_BACKEND=auto \
  -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-cry-integration-no-tests -j3 --target cry_game
```

当前证据仅为 Linux CPU 构建和真实进程 CLI。没有运行游戏场景、真实 Vulkan/OpenGL 窗口、音频设备或网络；record/headless 也不能解释为 GPU 画面。后续任务必须分别提供这些证据。
