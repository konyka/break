# Core App 命名迁移设计

日期：2026-11-10

## 目标

落实用户最新命名要求：本轮新增的 Cry 对照集成不使用 `cry/Cry/CRY`，也不再使用 `game/Game/GAME` 作为文件、类型、函数、变量、常量、target、测试或当前描述的名称。P12 统一迁移为 `core_app` 领域命名，遵守现有 C11/C++20 风格与 Google 一致性。

## 范围

只迁移尚未合入 master 的 P12 集成层及其当前计划、资产、测试和文档。既有 P0–P11 公共 API/ABI（`break_game`、`BreakGame*`、`BREAK_GAME_*`、`break_flow`、`break_ai`、`break_game_lua`、`runtime_core`）不在本项目中重命名；如需全仓公共 API 迁移，必须另开兼容项目。历史报告继续记录旧名称，当前生产与说明不使用旧名称。

## 命名方案

- 应用与库：`core_app`、`core_app_runtime`、`core_app_asset_bake`。
- 路径：`engine/apps/core_app`、`engine/assets/core_app`、`docs/design/core_app_integration.md`。
- 文件：`core_app.[ch]`、`core_app_audio.[ch]`、`core_app_render.[ch]`、`core_app_checkpoint.[ch]`、`core_app_asset_bake.c`；后续模块使用 `core_app_input`、`core_app_simulation`、`core_app_network`、`core_app_script`。
- 类型：`CoreApp`、`CoreLevel`、`CoreAppConfig`、`CoreAppDiagnostics`、`CoreAppCheckpoint*`、`CoreAppRender*`、`CoreAppAudio*`。
- 函数和变量：`core_app_*`、`core_app_checkpoint_*`、`core_app_render_*`、`core_app_audio_*`；局部 `game` 变量改为 `app` 或具体职责名称。
- 宏：`CORE_APP_*`、`CORE_APP_RENDER_*`、`CORE_APP_AUDIO_*`、`CORE_APP_CHECKPOINT_*`。
- 测试：`test_core_app_*`；构建目录 `build-core-integration-*`；CTest 与环境变量同步迁移。
- 计划改名为 `2026-11-03-core-app-integration.md`，新 SDD workspace 记录旧 workspace 的历史路径，旧台账不删除。

`core_app_runtime` 避免与既有 `runtime_core` 混淆，不采用重复的 `core_app_core`。

## 数据格式

当前 P12 尚未进入 master，也没有兼容旧 checkpoint 的承诺。一次性迁移 `GAMECKPT` 为固定 8 字节 `CORECKPT`、`manifest.game` 为 `manifest.core`、`GAMEAPPTRACE` 为 `COREAPPTRACE`、`game-app-scenario 1` 为 `core-app-scenario 1`。reader 只接受新格式，不静默接受双格式。由最终 baker 重新生成全部正式资产，真实 readers 验证。

## 风格

- C 文件、函数、变量和参数使用 lower_snake_case；类型和枚举使用 PascalCase；宏与编译期常量使用 UPPER_SNAKE_CASE。
- C++ 封装使用现有 `breakxx` namespace、PascalCase 类型/方法、`kMax...` 常量、尾部 `_` 成员、move-only RAII 和 `[[nodiscard]]`，不引入另一套 API 风格。
- 不为了消除单词而进行无意义缩写；`core_app` 表示当前集成应用边界，不建立泛化的“核心框架”。

## 验证

1. 新命名合同扫描集成源码、target、测试和当前文档，拒绝旧代码标识；历史说明与既有 P0–P11 API 明确豁免。
2. 先运行当前真实 CLI、资产、checkpoint、生命周期测试并取得迁移行为 RED，再完成迁移到 GREEN；不能只靠文本替换或编译。
3. 正式 11 资产与 fresh baker 逐字节一致，HEAD archive 的 BSCN/Flow/BANM/WAV/Lua readers 全部通过。
4. checkpoint 三态、mount 隔离、commit fatal、IO quiescence、sticky FAILED 等 Task 3 行为保持；执行普通、ASan+UBSan、TSan 的真实进程回归。
5. no-tests、target/link、命名、全量非图形和 `git diff --check` 通过；独立规格与质量评审无未解决 Critical/Important。
6. 迁移验收后才继续后续 Task。GPU、音频设备、网络和听测仍按各自任务单独验证，不因改名而声称完成。
