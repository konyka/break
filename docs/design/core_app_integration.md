# Core App 真实集成

日期：2026-11-06

## Core App Task 2 数据格式与命名边界（2026-11-11）

本步在 Task 1 命名边界上一次性迁移 P12 数据格式：checkpoint magic 为固定 8 字节 `CORECKPT`（无额外 NUL），manifest 文件名为 `manifest.core`，trace 首字段为 `COREAPPTRACE version=1`，scenario 首行为 `core-app-scenario 1`。reader 只接受这些新标识并拒绝旧标识，不存在双格式或旧格式回退。manifest 的字段宽度、序列化偏移、FNV-1a-64、generation、错误码、三态提交结果与原子提交语义不变；事务加载、mount 隔离、commit fatal、IO quiescence、sticky FAILED 和逆序销毁行为不变。

当前映射为：可执行应用 `core_app`、静态库 `core_app_runtime`、离线 baker `core_app_asset_bake`；应用、测试和资产根目录分别为 `engine/apps/core_app`、`engine/tests/test_core_app_*`、`engine/assets/core_app`；新构建目录为 `build-core-integration-*`，测试环境变量采用 `CORE_APP_*`。runtime 的 configure-time `SOURCES` property 必须恰好等于 `core_app.c`、`core_app_audio.c`、`core_app_render.c`、`core_app_checkpoint.c` 四个新源文件，不能通过追加 `target_sources` 绕过。

真实 nm 支持且返回成功时，输出缺少 `core_app_run` 是合同 FAIL，不是 SKIP；`test_core_app_nm_symbol_missing` 用真实二进制和只过滤该符号的 wrapper 锁定这一负例。仅 NM 缺失或工具/格式不支持时沿用两个原 nm SKIP 合同。

合同先在 Task 1 实现上取得预期 RED：assets 为 18/22，旧 scenario 实际退出 0，旧 trace 与旧 manifest/magic 被接受。最小迁移后 focused 4/4 通过，`test_core_app_assets` 为 22/22。临时恢复旧 magic 后 assets 降为 20/22 且命名合同失败；恢复新 magic 后 assets/naming/lifecycle 3/3 再次通过。

最终 baker 以同一 `--output` 接口分别生成空构建目录和正式目录，11 个文件逐字节一致；BSCN+sidecar、Flow、BANM、WAV 和 Lua 均由真实 readers 验证。HEAD archive 独立配置/构建后，Core App 9 项入选为 6 PASS、3 个 nm 合同 SKIP、0 失败。普通和 ASan+UBSan 非图形/非 fuzz 均为 351 项入选、347 PASS、4 个文档化 SKIP、0 失败；TSan lifecycle 为 1/1，no-tests 完整构建仍生成三个应用 target。所有构建和并行 CTest 使用 `-j3`，完整命令、hash 和变异记录见 `.superpowers/sdd/2026-11-11-core-app-naming/task-2-report.md`。

本步验证仍为 Linux CPU/record 证据；record/null 不构成 GPU、声卡或听测证据，native GPU/声卡/听测、网络、非 Linux runtime 和远程 CI 未验证。Task 3 的第二次 bounded IO wait 失败与 `io_quiesced` trace EIO 注入仍未覆盖；Task 9 的 256 项声音 FIFO、过载和 drain recovery 未提前实现，当前仍为 16 项 record FIFO；baker 的 Flow user identity 与 exec-link source port 专项断言仍留在后续台账。

## 跨平台合同补充（2026-11-11）

Core App nested 测试现在传递父配置的有效后端与非空真实 `Vulkan_LIBRARY`、`Vulkan_INCLUDE_DIR`、`SHADERC_LIB`、`SHADERC_INCLUDE_DIR`，wrapped 第二跳使用同一组定义。只有错误集合恰好为缺少 `core_app_run` 时才产生 `CORE_APP_NM_ONLY_MISSING_SYMBOL`；nested configure 失败与缺符号文本同时出现仍是 FAIL。原生 macOS Metal run `43004390668` 的 job `130468130703` 实际通过 assets 17/17 和 Core App 9 项合同的 6 PASS＋3 个明确 nm SKIP；target、nested、wrapped、compat、正式资产与命名均执行通过，不构成 GPU 运行证据。

reserved-manifest-alias 用例不再于 writer 调用前预写 alias payload。POSIX 使用 `link` 与 `stat` 的 device/inode 身份检查覆盖真实文件别名，保留调用前哈希并增加完整 manifest 字节比较；`BREAK_RUNTIME_INVALID`、probe 成功和原 `runtime_1.bin` 断言均保留，checkpoint writer 未修改。原生 APFS 的修复后 assets 为 17/17。独立变异 run `43004881342` 的 macOS job `130469756286` 恢复旧预写后在同一旧哈希断言处得到 16 PASS＋1 FAIL，验证了原生 RED 与恢复 GREEN 的因果关系。Windows 与 D3D12 的剩余失败不在这两节中宣称已修复。

## 合并前历史：Windows 进程启动与资产检出（2026-11-11）

本节仅保留合并前方案与当时证据，完整命令外层引用和 generic binary 均不是最终实现。

Windows 测试启动 baker 时，`system()` 的完整命令在 `_WIN32` 下使用 `""<exe>" --output "<output>""`，exe 与输出路径分别引用，完整字符串再包一层引号；非 Windows 保留原格式。原始格式和反斜杠变体在真实 probe 中失败，完整命令外层引用成功并生成 `level.bscn`，因此未采用无空格路径才能工作的无引号方案。原始返回、A/B 短路与诊断保持原合同。baker 生成、PAL、序列化和公共 API 未因此改变。

正式资产使用 `engine/assets/core_app/* binary`，避免 Git 在 Windows checkout 将文本 LF 改写为 CRLF。原生哈希证明七个文本文件曾被逐行增加一个字节，而 BSCN/BANM/FG/WAV 与 baker 完全一致；未通过归一化或重写资产掩盖差异。`test_core_app_checkout_attributes` 对全部 11 个正式资产执行真实 `git check-attr`，悬空 `.git` symlink 在 `rev-parse` 失败时必须 FAIL，只有真实无元数据或 Git 工具缺失才允许明确 UNVERIFIED。

原生 run `43041968171` 的 Windows job `130595842235` 实际得到 direct baker 退出 0、assets **16/16**、完整 diagnostics 通过，probe outcome/final gate 为 success；macOS job `130595841519` 也通过。当前本机非图形为 **357 项入选、353 PASS、4 个文档化 SKIP、0 FAIL**，所有构建和并行 CTest 使用 `-j3`。D3D12 compat 的 generator/`-C` 配置与真实 Agility 归档暂存仍按独立计划执行，sanitizer、no-tests、fuzz 和最终 master CI 不在本节中宣称完成。

## 最终同步行为与验收记录（2026-11-12）

最终实现中，Windows 以 `_spawnv(_P_WAIT)` 直接启动真实 baker，executable 与 output 参数分别按 CRT 规则引用，并保留 A/B slot、`launch.command` 与原始 `launch.spawnv` 返回诊断；POSIX 仍使用 `system()` 和 `launch.system`。七个文本资产分别由 Lua、scenario、actors.sidecar 规则指定 `text eol=lf`，`level.banm`、`level.bscn`、`level.fg`、`tone.wav` 四个二进制资产显式指定 `binary`。checkout 合同对全部 11 个资产逐一执行真实 `git check-attr -a` 分类检查，不再采用 generic binary。

控制器提供的原生 run `43138732673` 记录 direct baker 退出 0、assets **17/17**、完整 diagnostics 与最终 gate success；Windows job `130920254174` 和 macOS job `130920254617` 均成功。原生 run `43138732792` 的 job `130920254336` 记录 compat **1/1**、WARP runtime **1/1**，push-constant gate、Agility deployment 和七个 D3D12-labelled 测试均在 WARP runner 上通过。WARP 是软件光栅化证据，不是独立显卡或真实 GPU 驱动证明。

原始 `43138732792` 日志没有直接显示 `D3D12Core.dll missing` 文本，因此后续仅在临时 validation 分支增加受真实断言门控的证据输出。独立临时提交 `73e1e267` 的 run `43150345368`、job `130957761304` 现已明确记录 `D3D12Core.dll missing rejected; restored; SHA-256 verified`，八个嵌套夹具无未运行项，compat **1/1**、WARP runtime **1/1** 和 Agility 部署通过；CPU run `43150345348` 的 Windows/macOS 均成功。临时辅助实现及其 workflow 不合入 master，WARP 仍不是独立显卡证明。最终交付提交的 Windows/D3D12 复跑仍由 controller 验收。

终审修复 `253ce949` 的普通与 ASan+UBSan `detect_leaks=1` 非图形均为 **358 selected、354 PASS、4 个文档化 SKIP、0 FAIL**；TSan focused 为 7/7、assets 为 23/23，no-tests 完整构建通过且注册测试为 0，五个显式 fuzz smoke 全部通过。`45fe548d` 仅修改 CMake 测试脚本，使 intentional no-NM 真实传播到 archived configure，并在实际验证后转发 SKIP 证据；其完整普通非图形同为 358/354/4/0。两项 scoped 复审均 PASS，无遗留 Critical/Important。所有构建和并行 CTest 使用 `-j3`；完整命令、RED/GREEN、变异和既有 Lua `tmpnam` 警告另记于 final-review-fix-report。

最终 CPU run `43155806374` 的 macOS job `130975331228` 揭示了 CTest 成功摘要格式回归：archived nested 的自身成功 marker 和 1/1 Passed 均真实出现，摘要却是 `100% tests passed out of 1`，导致只接受 `100% tests passed, 0 tests failed out of 1` 的 compat 单独失败。macOS assets 为 **18/18**；同 run 的 Windows job `130975330900` 已记录 direct baker exit 0、assets **17/17** 和 diagnostics/probe success。实际 archived 断言现在通过共享精确整行 predicate 仅接受这两种成功格式，零测试、多测试、失败、未运行及 `out of 10` 前缀陷阱均拒绝；本地 CMake 3.28.3 的另一种格式只作对照，不用于猜测 macOS CTest 版本。修正后的原生 Windows/macOS/D3D12 复跑仍由 controller 获取，本节不提前宣称通过。

最终 D3D12 run `43155806382`、job `130975331060` 进一步证明工具链传播是独立根因：parent 明确使用 `C:/Program Files/LLVM/bin/clang.exe`，新 archived target build 却实际使用 `C:/mingw64/bin/cc.exe`，并在 MinGW D3D12 headers 上编译失败，不能归为上一项摘要格式问题，也不能删除归档构建或改成 SKIP。现在 parent 的 `NESTED_CMAKE_C_COMPILER` 沿现有显式链条进入 archived configure 和 target/nm 第二跳，实际 configure 同步接收 `CMAKE_C_COMPILER`；archive 与 positive/wrapped no-tests cache 以 REALPATH 断言真实 parent 路径，防止用另一编译器假绿。两种 CTest 成功格式、intentional no-NM、Agility DLL/hash、backend、Vulkan/shaderc 和 generator/config 均保留。修正后的原生 D3D12/WARP 复跑仍由 controller 获取，本节不提前宣称通过。

### 修正后的最终原生验收

临时集成 `0ce1c8a8` 包含最终交付 `501dacf6` 与 CTest 格式修复，并已通过独立 scoped 集成复审。CPU run `43162667419` 的 Windows job `130997246369` 实测 direct baker exit 0、assets **17/17**、diagnostics/probe success；macOS job `130997246678` 实测 assets **18/18**，九项 Core App 合同为 **6 PASS＋3 个既有 nm SKIP、0 FAIL**，包含 compat。成功步骤使用 `--output-on-failure`，不打印 archived nested 原始摘要；这里不虚构观察到的格式，实际 compat predicate 已验证捕获日志。

D3D12 run `43162667434`、job `130997246493` 的完整日志显示 archive 与第二跳均接收 `NESTED_CMAKE_C_COMPILER=C:/Program Files/LLVM/bin/clang.exe`，实际 cache 断言与归档构建均通过，不再落入 MinGW 工具链。`D3D12Core.dll missing rejected; restored; SHA-256 verified`、八夹具无未运行、compat **1/1**、WARP runtime **1/1**、Agility 部署和七个 D3D12-labelled 测试均通过。此前待验收表述由这些新结果更新；临时 workflow、process probe 与插桩均不合入 master，WARP 仍不证明独立显卡。本地 master 合并结果及主 CI 另行验收。

主 CI run `43164552740` 的 clean-room job `131003571447` 在真实无 `.git` 的导出树上暴露了另一种标准 Git 诊断：`fatal: not a git repository (or any parent up to mount point /)`，后接 `Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set).`。formal、checkout、naming 因旧的单一 parent-directories 文本假设而错误 FAIL，dangling 仍正确拒绝；352 selected 中其余 349 项通过。三个真实 probe 现在共用同一判定：仅当 `<root>/.git` 的 `EXISTS=FALSE`、`IS_SYMLINK=FALSE` 且完整诊断等于该 alternate 文本或原标准文本时才 UNVERIFIED；权限、unsafe ownership、工具执行错误、corrupt/invalid HEAD 和 dangling 均保持 nonzero/non77 且无 UNVERIFIED。修正后的 fresh full CI 与 D3D12 run 仍由 controller 获取，本节不提前宣称通过。

### master 最终验收

合并提交 `a9c25224` 的主工作树完整构建通过，非图形为 **358 selected、354 PASS、4 个文档化 SKIP、0 FAIL**。主 CI run `43186135276` 的全部可执行 job 成功；macOS Cocoa job `131073643195` 的 `test_break_online_nat` 实际通过。clean-room job `131073947704` 为 **352 selected、0 FAIL**，三个缺库合同按预期 UNVERIFIED/SKIP，dangling 仍 fail-closed。D3D12 run `43186135119`、job `131073642817` 的 headless、WARP runtime **1/1**、push-constant、Agility 部署和七个 D3D12-labelled 测试均成功。此前待验收表述由这些新 run 更新；硬件专用 lane 的调度跳过不视为通过或硬件证明，WARP 仍不证明独立显卡。

第二次 bounded IO wait 失败与 `io_quiesced` trace EIO 注入、256 项音频 FIFO/过载/drain recovery、Flow user identity 与 exec-link source-port 永久断言仍留在后续台账；Compose 和 P12 Task 4–13 不在本批次中宣称实现。

## P12 Task 5：Actor/Lua 与 Flow 同帧接线（2026-11-13）

### 每 tick 顺序

固定步内的顺序改为：`break_game_tick` → `break_flow_runtime_tick` → `core_app_simulation_tick` → `break_game_area_tick` → 位置 trace → 处理本 tick 累计的 Area enter → haptic → `event=actors` trace。AI、动画和 `physics_step` 仍由 Task 6 接入，本任务不把它们算作已实现。

`event=actors` 记录 User 和 Chaser 的脚本计数、用户物品数和 Flow pending 数：

```text
event=actors tick=<n> generation=<g> user_ticks=<n> user_failures=<n> \
    chaser_ticks=<n> chaser_failures=<n> items=<n> flow_pending=<n>
```

### 脚本

`stage_lua` 以 `instruction_budget = 1000000`、`memory_budget = 8 MiB` 创建 runtime，并加载 `director`、`user`、`chaser`。User 类绑定 `user`，Chaser 类绑定 `chaser`。`user.lua` 的 `on_actor_tick` 只累加 `state.ticks`；`chaser.lua` 可以加载，但 `on_actor_tick` 每次都 `error`。一个 actor 的错误只记入 `break_game_lua_last_fault` 和该 actor 的 `failures`，不阻止同 tick 的其他 actor。

`break_game_lua_actor_stats(adapter, entity, out)` 返回该 actor 的 `ticks`、`failures`、`skipped`、`last_error` 和 `disabled`。despawn 清零计数，之后查询旧 entity 返回 `BREAK_LUA_STALE`，复用同 index 的新 generation 从 0 开始。一次调用使 `break_lua_runtime_budget_trip_count` 增加时，adapter 只禁用这个 module：它的所有 actor 之后记入 `skipped`，其他 module 继续运行。普通 Lua 错误不会禁用 module。

### Flow

烘焙的 `level.fg` 事件键从 1 改为 1001，add-item 节点的数量字段 `a` 明确为 1（之前是 0，运行时会以 `BREAK_FLOW_INVALID` 拒绝）。用户前方 Area 的 enter 调用 `break_flow_runtime_post(flow, 1001, user, 1.0)`，trace 记 `event=flow kind=post key=1001 … tick=<n>`。延迟 30 tick 后动作把物品 1 加到 User，trace 记 `event=item … entity=2 item=1 count=1`。`break_flow_runtime_tick` 的非 OK 结果记 `event=flow kind=tick_failed … status=<n>`，本 tick 的其余步骤继续。Flow runtime 在失败时把队列和 `now_tick` 回滚到该次调用之前，所以同一事件会在下一个应用 tick 被再次尝试，应用自己不另做补偿。

替换关卡或卸载时，应用先 trace `event=flow kind=discarded generation=<g> pending=<n>`（pending 为 0 则不记），再销毁该 generation 的 Flow runtime。新关卡不继承旧队列，所以旧事件不能作用到同 index 的新 generation。

### 验证

- `test_break_game_lua` 4/4：原有的失败隔离和缺失 hook 用例，加上 60 tick 的 per-actor 计数、despawn 后 STALE、预算 trip 只禁用一个 module。
- `test_core_app_assets` 23/23：事件键 1001、add-item 数量 1、`user` 的 `on_actor_tick` 返回 OK、`chaser` 可加载但 `on_actor_tick` 返回 `BREAK_LUA_FAILED` 且不影响再次调用 `user`。
- 真实进程 `test_core_app_lifecycle_script_flow`：持续行走时 tick 30 投递且 `flow_pending=1`、物品仍为 0，tick 61 物品变为 1 且 pending 归零，tick 180 仍为 1；User 180 次成功、Chaser 180 次失败。中途卸载报告 `discarded pending=1` 且全程没有 `event=item`；第二关卡在 tick 42 从 0 开始计数，到 tick 99 物品仍为 0，也没有新的投递（用户停在原地，不再进入 Area）。
- 变异：任何 Lua 错误都禁用 module 时 `test_break_game_lua` 为 2/4；首个错误跳过后续 actor 时 `script_flow` 失败；删除 Area→Flow 投递时 `script_flow` 失败。三处恢复后 `cmp` 确认字节一致。
- 回归：普通非图形 374 项入选，370 PASS，4 个既有文档化 SKIP，0 FAIL。ASan+UBSan focused 8/8，TSan 6/6，均无 sanitizer 报告。

### 限制

AI、动画和 `physics_step` 没有接入，tick 顺序里这三步仍是空位。Flow 动作失败只记 trace；重试来自 Flow runtime 的回滚，应用不另做补偿。证据仍是 Linux CPU/record，没有真实窗口、手柄或 GPU。

## P12 Task 6（slice 1）：追踪者的视野、行为树、当前版本路径与动态墙（2026-11-13）

### 每 tick 顺序

固定步内的顺序扩展为：`break_game_tick` → `break_flow_runtime_tick` → `core_app_simulation_tick` → `app_tick_chaser` → `break_game_area_tick` → 位置 trace → Area enter 处理 → haptic → `event=actors` trace → `event=sim` trace。追踪者的移动意图由行为树产生，由 `CharacterController` 执行；应用自身不直接写世界位置。

### 导航场与 AI 接线

`stage_ai` 把导航高度场从 4x4 扩到 8x8（cell 1.0，`origin_x/origin_z = -1.0`），`break_nav_bake_heightfield` 的结果作为 `BreakAiRuntime` 的输入，并给场景实体 index 3 注册半径 0.4、最大速度 3 的 agent。加载期不再寻路：寻路只发生在 tick 内。

### 视野

`stage_simulation` 在用户实体周围注册一个半尺寸 (6, 3, 6) 的 Area 作为 `sight_area`；`app_area_event` 命中该区域时置 `target_in_sight`，命中 `trigger_area` 时保留 Task 5 的 Flow 触发计数。每 tick 用 `break_sight_query` 做一次射线检测：眼睛取自身位置，前向 (-0.7071, 0, -0.7071)，距离 12，半角 1.2 rad；遮挡回调只在命中动态墙刚体时判定为不可见，地面命中不遮挡。命中后写入 `BreakBlackboard` 的 `seen`、`last_seen` 和 `target`。

### 行为树与当前版本路径

每 tick 构建 SELECTOR 根 + CHASE 叶的行为树，`break_behavior_tick` 读取黑板与 `BreakNavFollower` 给出 `wish` 位移。除首次寻路外，只有当 `break_ai_nav_version` 与上次记录的版本不同才重新寻路；查询使用当前版本号，因此动态墙 add/remove 之后旧路径立即失效（`break_ai_path_is_current` 返回假）并在下一次 tick 用新版本重建。`BREAK_NAV_FAILED`（目标不可达）被容忍，不中断该 tick。

### 动态墙

当 `target_in_sight` 成立且尚未加墙时，`break_ai_obstacle_add` 加入矩形 (1, 1, 4, 2)，同时 `physics_body_create` 建立对应的动态刚体。追踪者的位置进入 x < 1.0 且 z < 1.5 的区域后，`break_ai_obstacle_remove` 移除障碍，nav 版本再次递增，路径重新可查询，追踪者继续接近目标。

### trace

```text
event=sim tick=<n> generation=<g> chaser_x=<f> chaser_z=<f> nav_version=<u> path_current=<0|1>
```

### 验证

- 真实进程 `test_core_app_lifecycle_simulation`（600 tick）：tick 1 的路径是当前版本（`path_current=1`，nav 版本 1）；tick 2 加墙后版本前进且路径过期（`path_current=0`）；tick 200 重新寻路后 `path_current=1` 且 z 已向目标下降；tick 500 版本再次前进（墙已移除）、路径当前、z 继续下降、x < 0.5。同一场景重复运行两次，全部 `event=sim` 行逐字节一致。
- 变异（改代码 → 断言必须红 → 恢复）：去掉 `break_ai_obstacle_remove` → 报“tick 500 nav version 未前进”；寻路时传旧版本号 → 失败；跳过加墙分支 → 报“tick 2 版本未前进”。
- 证据仍限 Linux CPU/record：没有真实窗口、手柄、GPU 或音频设备。

### 限制

本 slice 只覆盖追踪者的感知、决策、寻路与移动；locomotion/morph/facial→skinning、载具进出与 throttle、布娃娃与 IK 互斥仍属 Task 6 后续 slice。导航场是静态高度场烘焙，动态障碍只通过 `break_ai_obstacle_*` 影响可达性，不重建网格。

## P12 Task 6（slice 2a）：按水平速度混合步行与跑步（2026-11-13）

### 接线

`stage_simulation` 初始化一维 locomotion：阈值 0 对应步行剪辑 0，阈值 4 对应跑步剪辑 1，混合写进 `AnimBlendState` 的前两层。每个固定步在用户位置 trace 之后，用相邻 tick 的水平位移除以 `CORE_APP_FIXED_DT` 得到速度，竖直位移不计入。`anim_loco1d_apply` 把权重大的样本放在主层、小的放在次层，trace 按 `clip_index` 取值，不按层号取值。

### trace

```text
event=loco tick=<n> generation=<g> speed=<f> walk_weight=<f> run_weight=<f>
```

### 验证

- 真实进程 `test_core_app_lifecycle_locomotion`：按住 W 时跑步权重超过步行权重；tick 1 无位移，`speed=0 walk_weight=1 run_weight=0`；只按空格跳跃时跑步权重保持 0。
- 变异：跑步阈值改到 100 → “run weight never exceeded walk weight”红；速度改回三维 → “a vertical jump raised the run weight”红。两处均已恢复并复测。

### 限制

本 slice 只接一维速度混合，不接 morph、facial 或 skinning。scenario 文法为此新增 `key space`，对应键码 32；其余单字符键不变。

## P12 Task 6（slice 2b）：表情曲线 → morph → 蒙皮（2026-11-13）

### 接线

`stage_simulation` 建一个单顶点 `AnimMorphSet`，目标 `lift` 的位移为 (0, 2, 0)；`AnimFacialLibrary` 里的表情 `lift` 有一条曲线，在 0 s 到 1 s 之间把权重从 0 线性升到 1。绑定顶点是 64 字节的 `SkinnedVertex`，位置为原点，权重 (1, 0, 0, 0)。三者都在加载期分配，tick 内不扩容。

每个固定步在 locomotion trace 之后依次执行：`anim_facial_evaluate`（时间为 tick × `CORE_APP_FIXED_DT`，上限 1 s）→ `anim_morph_evaluate_skinned`（变形后的 64 字节顶点，法线、UV、关节和权重原样保留）→ `lod_skin_positions`（单关节蒙皮矩阵，平移 x = 3）。

### trace

```text
event=facial tick=<n> generation=<g> x=<f> y=<f>
```

### 验证

- 真实进程 `test_core_app_lifecycle_facial`（scenario 在 tick 30 退出，最后一次模拟是 tick 29）：tick 1 的 y 小于 0.1；tick 29 的 y 在 (0.9, 1.0] 内；tick 29 的 x 在 [2.9, 3.1] 内，证明蒙皮矩阵作用在变形后的顶点上。断言按数值区间比较，不依赖 `%.9g` 的字符串形式。
- 变异：把 morph 位移改成 0 → “expression did not lift the skinned vertex, y1=0 y29=0”红，恢复后通过。
- lifecycle 8/8。

### 限制

这是一条单顶点、单关节的接线证据，不是正式资产：关卡 BSCN 里还没有蒙皮网格或骨骼，表情和 morph 目标在应用内构造。把 `level.bscn` 换成带蒙皮网格的资产、由 `skeleton_apply_local_trs` 产生真实蒙皮矩阵，留给后续 slice 与 Task 7 的渲染接线。

## P12 Task 6（slice 3）：载具上车、油门与下车（2026-11-13）

### 接线

`stage_physics` 的物理世界容量从 16 提到 32，并在场景节点 4（Vehicle，位置 (-4, 0.75, 2)）上方 0.25 m 处 `vehicle_create`，加载期先空载推进 120 个固定步让悬挂落稳。`core_app_level_destroy` 在销毁物理世界前调用 `vehicle_destroy`。

每个固定步的顺序变为：`break_game_tick` → `break_flow_runtime_tick` → `app_tick_vehicle` → 用户未乘车时 `core_app_simulation_tick` → `app_tick_chaser` → `physics_step` → 乘车时把用户放到底盘位置 → `event=vehicle` trace → `break_game_area_tick` → 其余 trace。`physics_step` 由此第一次进入应用的固定步。

`app_tick_vehicle` 读取 interact 动作（E 键或手柄西键），只在按下的那一 tick 触发：未乘车时，用户与底盘的水平距离不超过 3 m 才调用 `vehicle_enter`；已乘车时调用 `vehicle_exit`，成功后用新增的 `core_app_simulation_place_user` 把角色控制器和 ECS 位置放到下车点，并清零速度。乘车期间 forward 映射为油门、strafe 映射为转向，不乘车时三项控制都为 0，每个固定步都调用 `vehicle_step`。

### trace

```text
event=vehicle_enter tick=<n> generation=<g> ok=<0|1>
event=vehicle_exit tick=<n> generation=<g> ok=<0|1>
event=vehicle tick=<n> generation=<g> occupied=<0|1> throttle=<f> grounded=<0..4> x=<f> z=<f>
```

### 验证

- 真实进程 `test_core_app_lifecycle_vehicle`（90 tick）：tick 1 在出生点按 E，距离约 4.5 m，上车被拒绝；按 A 走到 x ≈ -2.55 后 tick 40 上车成功；按住 E 的下一 tick 不会再次切换；按住 W 时 tick 60 油门为 1、四轮着地、底盘 z 增大，用户位置与底盘一致；松开 W 后 tick 74 油门为 0；tick 76 下车成功，用户落在底盘右侧 x ≈ -2.3。
- 变异：油门不映射、去掉按键边沿检测、去掉距离检查、乘车时不移动用户，四处都让断言变红，恢复后通过。
- lifecycle 9/9；ASan+UBSan 9/9、TSan 9/9，无 sanitizer 报告；`test_vehicle`、命名合同、资产与 runtime 测试通过。

### 限制

载具只有底盘刚体，没有渲染接线，也没有把场景节点 4 的变换跟随底盘更新。下车点仍由 `vehicle_exit` 的侧向 sweep 决定，被挡住时返回 `ok=0`，用户留在车上。

## P12 Task 6（slice 4）：布娃娃与 IK 互斥（2026-11-13）

### 接线

`stage_physics` 在创建载具之后建一条三关节链（世界位置 (6, 3, -4)、(6, 2, -4)、(6, 1, -4)，父子依次相连，逆绑定矩阵为对应平移的逆），并给 `IKSystem` 设置一个两骨 IK 目标 (6.6, 1.6, -4)，权重 1。骨架不绑定 RHI 设备，只用于 CPU 姿态。

每个固定步在 `event=vehicle` trace 之后调用 `app_tick_ragdoll`：R 键按下的那一 tick 切换布娃娃（未激活时 `ragdoll_activate(&chain, &ik)`，激活时 `ragdoll_deactivate`）。布娃娃激活期间由 `ragdoll_write_local_trs` 从刚体读出局部姿态；未激活时恢复绑定姿态。随后统一调用 `anim_ik_solve_unless_ragdoll`，布娃娃激活时它不修改姿态并返回 false。`ragdoll_activate` 通过 `anim_ik_physics_acquire` 持有 IK，`ragdoll_deactivate` 释放，因此即使调用方忘了传标志，`anim_ik_solve` 也会因为持有计数而跳过。

`core_app` 现在显式链接 `engine`，排在 RHI 后端库之前：布娃娃会拉入 `skeleton.o`，后者引用 `rhi_buffer_*`，只有 engine 在后端库前面时这些符号才能解析（与 `engine_demo` 的链接顺序一致）。

### trace

```text
event=ragdoll tick=<n> generation=<g> active=<0|1> ok=<0|1>
event=ik tick=<n> generation=<g> ragdoll=<0|1> solved=<0|1> owned=<u> tip_x=<f> tip_y=<f>
```

### 验证

- 真实进程 `test_core_app_lifecycle_ragdoll`（90 tick）：tick 5 IK 求解、末端 x ≈ 6.6；tick 10 按 R 激活布娃娃，按住期间不会再次切换；tick 11 起 IK 不求解且持有计数为 1，tick 40 末端 y 已从约 1.6 降到约 0.57；布娃娃激活期间没有任何一行 `ragdoll=1 solved=1`；tick 60 再按 R 解除，tick 61 IK 恢复求解、末端回到 x ≈ 6.6、持有计数为 0。
- 变异：IK 忽略布娃娃标志、布娃娃不持有 IK、去掉按键边沿检测、姿态不由布娃娃驱动，四处都让断言变红，恢复后通过。
- lifecycle 10/10；ASan+UBSan 12/12、TSan 12/12（含 `test_ragdoll`、`test_core_app_runtime`），无 sanitizer 报告；普通构建非图形全量 379/379。

### 限制

关节链是应用内构造的，不是正式资产，也没有渲染。布娃娃只在三关节链上演示所有权互斥，没有接到用户的角色控制器。

## P12 Task 7（slice 1）：record 模式的世界快照（2026-11-13）

### 接线

加载流程在 `crossref` 之后新增 `presentation` 阶段（`stage_presentation`），失败时以 `stage=presentation` 拒绝候选关卡，旧关卡不变。该阶段：

- 用 `scene_rebuild_materials_from_manifest` 从 BSCN 资源清单重建材质（BSCN 只保存清单，不保存 `Material` 数组），`core_app_level_destroy` 负责释放；
- 为 7 个场景节点各建一个 `WorldObject`（id = 节点序号 + 1），顶点/索引数取 `scene.mesh_geometry`（无设备加载时 `scene.meshes` 为空）；`has_mesh` 为假的节点 7（HiddenColor）不进入 VisArea 的 outdoor 列表；
- 用 `world_presentation_stream_mesh` 迁移一块 4 顶点的 V1 stream tile（平移到 (6, 0, -6)），作为对象 100，`stream=true`；
- 用 `vegetation_build` 在 2×2 密度图上生成 3 个植被实例，原型 1 个 LOD。

每个 tick 在 `core_app_render_record_frame` 之后调用 `app_publish_world`：相机跟在用户后上方，昼夜由 `time_of_day_eval(tick × 1/60, 2 s)` 计算，`world_presentation_snapshot` 写入两个快照槽之一（按 tick 奇偶交替），写完不再修改，再由 `core_app_render_record_world` 输出一行 canonical trace。

### record 句柄

record 模式没有 GPU，但 `world_presentation_snapshot` 要求句柄有效。因此每个对象的 vertex/index 句柄是 `{对象 id, level generation}`，只用来在 trace 里标识资源及其代际，从不交给 RHI 设备。`core_app_render_record_world` 拒绝 generation 与当前关卡不符的句柄（`STALE`），所以卸载后重载的关卡不能发布旧代际的对象。这些结果只属于 CPU/record 证据，不是 GPU 证据。

### trace

```text
event=render kind=world frame=<n> generation=<g> draws=<u> stream=<u> batches=<u> instances=<u> objects=<id,...> sun_y=<f>
```

### 验证

- 真实进程 `test_core_app_lifecycle_render_record`（tick 1 加载、30 卸载、31 重载、60 退出）：两个关卡各 29 帧，共 58 行世界快照；frame 1 为 `draws=7 stream=1 batches=1 instances=3 objects=1,2,3,4,5,6,100`；任何帧都不含隐藏对象 7；frame 31 起 generation 为 2，frame 30/31 不出现 generation 1；`sun_y` 从 frame 1 的约 -1 升到 frame 29 的约 -0.05。
- 变异：隐藏对象进入可见列表、重载关卡沿用 generation 1 句柄、不发布世界快照、昼夜时间冻结，四处都让断言变红，恢复后通过。
- lifecycle 11/11；ASan+UBSan 14/14、TSan 14/14（含 `test_world_presentation`），无 sanitizer 报告；非图形全量 380/380。

### 限制

本 slice 只做 record 世界快照。角色 skinned 命令、Runtime IO 迟到完成的 `STALE` 丢弃、第 65 个资源请求的 `OVERLOAD`，以及真实 RHI 消费者（`world_presenter_submit`）仍未做，分别留给 Task 7 slice 2 和 Task 11。

## P12 Task 7（slice 2a）：资源表的代际与容量合同（2026-11-13）

### 接口

`core_app_render.h` 新增固定容量的 `CoreAppResourceTable`：64 个槽（`CORE_APP_RESOURCE_SLOTS`），每槽最多 256 字节（`CORE_APP_RESOURCE_MAX_BYTES`），在 create 时随表一起分配，tick 内不扩容。每槽记录 request id、level generation、状态（EMPTY/PENDING/LIVE）、版本号和拥有的字节。

- `core_app_resource_request`：取第一个空槽，分配新的非零 request id，状态置为 PENDING。没有空槽时返回 `OVERLOAD`，`overloads` 加 1，输出参数和所有槽都不变。
- `core_app_resource_reload`：对 LIVE 槽发起一次重载，换新 request id，旧字节在完成前保持可用。
- `core_app_resource_complete`：只有槽正在等待、request id 与 generation 都匹配时才接受。不匹配返回 `STALE`，`stale_completions` 加 1，槽不变。字节先完整复制到 staging，校验通过后才替换并递增版本；长度超限返回 `INVALID`，旧的 LIVE 字节和版本保持不变。
- `core_app_resource_retire_generation`：卸载时清空属于该 generation 的全部槽，同一槽之后可以被新 generation 复用。

### 验证

- `test_core_app_runtime` 新增三个用例：卸载后重载，旧请求 A 的完成和新请求带旧 generation 的完成都返回 `STALE`，新槽保持 PENDING、字节为空，只有新 generation 的完成才写入；重载时 staging 失败，旧字节和版本 1 保持不变；64 个槽占满后第 65 个请求返回 `OVERLOAD`，64 个槽逐字节不变。
- 行为 RED：先用不做事的桩实现编译，三个用例都在断言处失败，之后才写实现。
- 变异：完成时不比较 generation、容量满时覆盖第 0 个槽、staging 失败时清空旧字节，三处都让对应用例变红，恢复后通过。
- `test_core_app_` 26/26；ASan+UBSan 与 TSan 下 `test_core_app_runtime` 和全部 lifecycle 各 12/12，无 sanitizer 报告。

### 限制

这是资源表本身的合同测试，表还没有接到 `CoreLevel` 的加载/卸载和 Runtime IO 完成路径上，也没有在真实进程 trace 里体现。角色 skinned 命令也还未做。两者留给 Task 7 slice 2b。

## P12 Task 7（slice 2b）：资源表接入关卡生命周期与角色 skinned 命令（2026-11-13）

### 接线

`CoreApp` 持有一张 `CoreAppResourceTable` 和一个 8 项的延迟完成队列（`CoreAppIoCompletion`）。队列模拟异步 IO：提交时复制字节并记下到期 tick（当前 tick + 2），每个 tick 开头 `app_io_drain` 把到期项交给 `core_app_resource_complete`，并写 `event=resource kind=complete` trace（`result=ok|stale|invalid`）。`STALE` 只记录不报错，其他失败结束运行。

- 关卡提交成功后，`app_request_skins` 为两个角色（对象 0 = 用户的表情变形顶点，对象 1 = 追踪者位置）各申请一个槽并提交首个上传。
- 每个 tick 在世界快照之后调用 `app_publish_skins`：槽为 LIVE 且 generation 等于当前关卡时，才输出 `event=render kind=skinned`；PENDING 的槽不出命令。当前姿态字节与槽内字节不同、且没有进行中的重载时，用 `core_app_resource_reload` 发起一次新上传。旧字节在完成前继续使用，版本号只在完成时递增。
- 卸载（`core_app_unload_level`）和替换关卡（提交新关卡时销毁旧关卡）都会先调用 `core_app_resource_retire_generation` 清空旧 generation 的槽。之后到期的旧完成，因为 request id 或 generation 不匹配而被丢弃。

### trace

```text
event=resource kind=complete tick=<n> slot=<u> request=<u> generation=<g> result=<ok|stale|invalid>
event=render kind=skinned frame=<n> generation=<g> object=<0|1> slot=<u> resource_generation=<g> version=<u>
```

### 验证

- 真实进程 `test_core_app_lifecycle_render_record`（tick 1 加载，tick 30 先卸载再加载，tick 100 退出）：
  - 两个槽在 tick 30 各收到一次 generation 1 的 `result=stale`，出现在 `level_loaded generation=2` 之后；
  - 每个 skinned 命令的 `resource_generation` 都等于关卡 generation，共 100 条以上；
  - frame 1 和 frame 30 没有 skinned 命令，因为资源还在 PENDING；
  - frame 2 用户对象 version 1；重载后 frame 31 复用槽 0，从 version 1 重新开始；
  - 动画期间 version 递增（frame 35 → 40），表情曲线结束后保持不变（frame 90 = 95）。
- 变异：卸载不清 generation、姿态变化后不重新上传、PENDING 时也发 skinned 命令，三处都让断言变红，恢复后通过。
- lifecycle 11/11、`test_core_app_` 26/26；ASan+UBSan 13/13、TSan 13/13，无 sanitizer 报告；非图形全量 380/380。

### 限制

延迟完成队列是应用内的确定性模拟，没有经过 Runtime IO 的 worker 线程；skinned 命令只是 record trace，没有 RHI skinned pipeline 或 GPU 上传（Task 11）。字节内容是 64 字节变形顶点和追踪者位置，不是正式蒙皮网格资产。

## P12 Task 8（slice 1）：运行时 POD checkpoint、加载拒绝与保存失败（2026-11-13）

### 接线

`--checkpoint DIR` 现在被接受。场景中的 `save`/`load` 事件只在给了 checkpoint 目录时有效，否则整份场景在启动时被拒。事件在 tick 开头、模拟之前处理，因此 tick N 的 `save` 记录的是 tick N-1 结束时的状态。

- `save`：`app_capture_state` 读取用户位置/速度、追踪者位置/速度、黑板 last_seen 和四个标志（墙已加、墙已移除、目标进入视野、已看见）。`runtime_<g>.bin` 是 80 字节的小端文件：8 字节 `CORERUN1`、版本、正文长度、64 字节正文，经 `PlatformAtomicWriter` 写入；随后 `core_app_checkpoint_write_manifest_ex` 提交 manifest（kind = `CORE_APP_CHECKPOINT_RUNTIME`）。manifest 提交成功后 `save_generation` 才递增，上一代 runtime 文件被删除。任何一步失败都写 `event=save ... result=failed`，删除本代新文件，运行继续，旧 manifest 不变。
- `load`：新函数 `core_app_checkpoint_find` 读取 manifest、逐个校验 payload 的长度和 FNV-1a，并返回唯一的 runtime 记录。文件再按 manifest 长度/哈希核对一次，然后解码；非有限值、未知标志位、“墙已移除但未添加”都返回 `INVALID`。校验全部通过后才调用 `app_apply_state` 修改当前关卡：恢复用户位置和速度（`core_app_simulation_restore_user`）、按标志补加或移除动态墙（旧导航缓存不继承，路径和跟随器清零，nav version 重新读取）、重建追踪者角色控制器并同步 AI agent。任何失败都写 `event=load_rejected ... stage=checkpoint|state`，当前关卡继续运行。
- 当前 checkpoint 只保存 runtime POD。Flow pending 队列、Lua VM、AI 缓存、输入瞬态和资源槽都不保存；加载前的 `level` 事件已经重建了它们。

### trace

```text
event=save tick=<n> generation=<g> save_generation=<s> result=ok state_hash=<hex> user_x=<f> user_z=<f> chaser_x=<f> chaser_z=<f>
event=save tick=<n> generation=<g> save_generation=<s> result=failed
event=load tick=<n> generation=<g> save_generation=<s> result=ok state_hash=<hex> ...
event=load_rejected tick=<n> generation=<g> stage=<checkpoint|state>
```

### 验证

真实进程 `test_core_app_lifecycle_roundtrip` 包含三段：

- roundtrip：tick 2 按住 W，tick 90 保存，tick 120 松开，tick 121 卸载，tick 122 重新加载，tick 123 加载 checkpoint。断言包括：
  - 保存记录的用户和追踪者坐标与 tick 89 的 trace 一致；
  - 保存后用户继续移动；tick 122 的新关卡与保存状态不同；
  - tick 123 加载到 generation 2，`state_hash` 和四个坐标与保存时逐字相同；
  - tick 124 追踪者从恢复的位置继续（x < 3.3、z < 3.8，新关卡出生点约为 4,4），用户 z 在 7–8 之间；
  - `manifest.core` 和 `runtime_1.bin` 存在。
- load_corrupt：在同一目录把 `runtime_1.bin` 改坏后加载，写 `load_rejected stage=checkpoint`，没有 `event=load`，用户在 tick 39 → 41 之间继续前进。
- save_fail：checkpoint 路径是一个普通文件，保存写 `result=failed`，tick 11 模拟继续，那个文件内容不变。

变异：加载不恢复用户、加载保留新关卡的追踪者、保存失败时结束运行、加载被拒时修改用户位置，四处都让断言变红，恢复后通过。其中“保留新追踪者”第一次与测试修改并行执行而误报存活，按顺序重跑后被杀死。

`test_core_app_` 27/27；ASan+UBSan 14/14、TSan 14/14，无 sanitizer 报告；非图形全量 381/381。

### 限制

本 slice 只覆盖 runtime POD。BSCN/Flow/Actor/scene_state 侧车、背包、相机和昼夜时间还没有进 checkpoint；“加载创建完整候选关卡后再交换”目前由场景里先 `level` 再 `load` 两步完成，而不是 `load` 单独完成。uninterrupted 对照、第二次保存中途失败、错误 Actor generation 等失败矩阵项仍未做。

## P12 Task 8（slice 2a）：背包进 checkpoint，第二次保存失败保留上一份（2026-11-13）

### 变化

- `runtime_<g>.bin` 升到版本 2，正文 68 字节，在标志之后加 4 字节的背包物品 1 数量。版本 1 的文件现在按 `INVALID` 拒绝。
- `save` 用 `break_game_inventory_count` 记录数量，trace 多一个 `items=<u>` 字段。
- `load` 只允许补足：当前数量大于保存数量时以 `REJECTED` 拒绝；小于时用 `break_game_inventory_add` 补差。这一步和其他校验一样，在修改用户与追踪者之前完成。
- 第二次保存失败时（例如 `runtime_2.bin` 位置已有同名目录），上一代 `runtime_1.bin` 和 manifest 保持不变，`save_generation` 不递增；之后的 `load` 恢复第一次保存的状态。

### 验证

- roundtrip：tick 62 Flow 拾取 1 个物品，tick 90 保存 `items=1`；卸载、重新加载后背包为 0，加载 checkpoint 后 tick 124 的 actors 行为 `items=1`，并且加载后没有新的 `event=item`（数量不是 Flow 重新触发得到的）。
- second_save：tick 20 保存成功，tick 40 因目录占位而失败，trace 为 `save_generation=1 result=failed`；tick 60 加载得到 tick 20 的 `state_hash`；`runtime_1.bin` 仍在，占位目录也没被动。
- 变异：加载不补背包、保存时写 0、保存失败时删除上一代文件，三处都让断言变红，恢复后通过。
- `test_core_app_` 27/27；ASan+UBSan 14/14、TSan 14/14，无 sanitizer 报告；非图形全量 381/381。

### 仍未做

BSCN/Flow/Actor/scene_state 侧车、相机、昼夜时间；uninterrupted 对照；错误 Actor generation、截断 BSCN、错误 Flow 引用等失败矩阵项。

## P12 Task 8（slice 2b）：与不中断运行的对照（2026-11-13）

### 做法

同一份场景跑两次：A 在 tick 90 保存后一直跑到 tick 149；B 在 tick 90 保存、tick 91 立刻加载，一直跑到 tick 150。B 因为加载多占一个 tick，所以比较的是 A 的 tick k 和 B 的 tick k+1（k = 90..149）的 trace 正文（去掉 tick 和 generation）。

### 发现与修复

第一次对照时，用户、载具、IK、表情都逐字一致，但 locomotion 在加载后的第一帧不同：A 的速度 5.1、跑步权重 1，B 的速度 0、步行权重 1。原因是 `app_apply_state` 把 `previous_user_position_valid` 置为 false，加载后第一帧的速度因此算成 0。现在加载会把上一帧位置设成恢复的用户位置并标记为有效。修复后 user/vehicle/loco/facial/ik 60 行全部逐字一致。

追踪者不逐字一致。加载会丢弃旧路径和跟随器游标（这是计划要求的“旧 nav cache 不继承”），并在下一 tick 按当前 nav version 重新寻路，所以轨迹会分叉；60 tick 后两次运行相差约 0.55 m。测试对追踪者只断言：加载后每一 tick 都有当前版本的路径（`path_current=1`），并且 tick 92 → 150 之间 z 继续减小。

### 验证

- `test_core_app_lifecycle_roundtrip` 新增 continuation 段：B 在 tick 91 加载成功；五类事件各 60 行，与 A 逐字一致；追踪者有当前路径并持续接近。
- 变异：加载时不保留上一帧用户位置，continuation 段报告 loco 不一致，恢复后通过。
- `test_core_app_` 27/27；ASan+UBSan 14/14、TSan 14/14，无 sanitizer 报告；非图形全量 381/381。

### 仍未做

相机和昼夜目前由 tick 推导（相机跟随用户，昼夜按 tick），不是独立状态，所以没有单独保存；只有将来它们变成可变状态时才需要进 checkpoint。BSCN/Flow/Actor/scene_state 侧车，以及错误 Actor generation、截断 BSCN、错误 Flow 引用等失败矩阵项仍未做。

## P12 Task 8（slice 2c）：load 自己构建候选关卡再交换（2026-11-13）

### 变化

`core_app_level_load` 拆成两步：`core_app_level_stage` 从 BSCN 起逐阶段构建候选关卡（到 presentation 为止，不触碰当前关卡），`core_app_level_commit` 负责交换、停旧关卡音频、退役旧 generation 的资源槽、写 level_loaded 并申请 skin 槽。场景里的 `level` 事件仍然是 stage + commit。

`load` 现在不再修改当前关卡：

1. 读取 manifest、校验 payload 哈希并解码 runtime 文件；失败写 `load_rejected stage=checkpoint`。
2. 用上一次成功加载关卡的资产根（没有则用 `--assets`）构建新的候选关卡；构建失败写 `load_rejected stage=<阶段>`，候选被销毁。
3. 把保存的状态写进候选（`app_apply_state`）；失败写 `load_rejected stage=state`，候选被销毁。
4. 以上都成功才 commit：候选得到新的 generation，旧关卡按正常卸载顺序退出。

因此当前没有关卡时也能 `load`，失败的加载对当前关卡没有任何影响。

### 验证

- roundtrip：tick 123 的加载构建 generation 3，并在报告前卸载 generation 2；tick 150 再次加载同一份 checkpoint，构建 generation 4，`state_hash` 相同。
- cold_load：tick 40 保存后卸载，tick 41 没有关卡在运行；tick 42 加载构建 generation 2，用户位置等于保存值。
- load_corrupt：坏文件被拒，没有构建 generation 2，当前关卡继续前进。
- continuation、second_save 改为期望加载产生新 generation，其余断言不变。
- 变异：候选不写入保存状态、加载被拒时扰动当前关卡、直接修改当前关卡而不建候选，三处都让断言变红，恢复后通过。其中第二处第一次因隐式声明编译失败，结果作废，换成可编译写法重做。
- `test_core_app_` 27/27；ASan+UBSan 14/14、TSan 14/14，无 sanitizer 报告；非图形全量 381/381。

### 仍未做

BSCN/Flow/Actor/scene_state 侧车；错误 Actor generation、截断 BSCN、错误 Flow 引用等失败矩阵项（构建阶段的失败已经走同一条 `load_rejected stage=<阶段>` 路径，但还没有针对 checkpoint 加载的专门用例）。

## P12 Task 8（slice 3）：场景、Flow、Actor 文件进 checkpoint 与失败矩阵（2026-11-13）

### 变化

- 关卡构建时保留实际读入的字节：BSCN（来自 Runtime IO 完成消息）、`level.fg`、`actors.sidecar`。`CoreAppLevelSource` 描述每份文件的目录和文件名，`core_app_level_stage` 按它构建，场景里的 `level` 事件仍从资产目录读 `level.bscn` / `level.fg` / `actors.sidecar`。
- `save` 写四个 payload：`scene_<g>.bscn`、`flow_<g>.fg`、`actors_<g>.sidecar`、`runtime_<g>.bin`，各自经原子写入，再由一份 manifest 一次提交（kind 分别为 SCENE、FLOW、ACTORS、RUNTIME）。任何一步失败都删除本代已写的文件，旧 manifest 和上一代文件不动；成功后删除上一代的四个文件。
- `load` 先用 `core_app_checkpoint_find` 取出四条记录（每次都校验 manifest 里全部 payload 的长度和哈希），再从 checkpoint 目录构建候选关卡：场景、Flow、Actor 文件来自 checkpoint，Lua、动画和音频仍来自资产目录。因此资产目录里的 `level.bscn`、`level.fg`、`actors.sidecar` 被删除后，checkpoint 仍能单独重建关卡。

### 验证

`test_core_app_lifecycle_roundtrip` 新增或扩展：

- roundtrip：checkpoint 目录含四个 payload，三份侧车与加载时的资产 SHA-256 相同。
- 失败矩阵：每项都从同一份有效 checkpoint 复制出一个目录，用 Python 改坏其中一份文件；除最后一项外同时更新 manifest 的长度和哈希，使它通过 manifest 校验、在构建阶段失败：

  | 用例 | 改动 | 期望 |
  |---|---|---|
  | truncated_scene | `scene_1.bscn` 截到 64 字节 | `load_rejected stage=bscn` |
  | bad_flow | `flow_1.fg` 换成非法内容 | `load_rejected stage=flow` |
  | unknown_actor | `actors_1.sidecar` 中 `2 User` 改为 `2 UnknownUser` | `load_rejected stage=actor` |
  | manifest_hash | 截断 `scene_1.bscn`，manifest 不改 | `load_rejected stage=checkpoint` |

  每项都断言没有 `event=load`、没有构建 generation 2、当前关卡在 tick 39 → 41 继续前进、运行正常停止。
- second_save：第二次保存失败后，`runtime_1.bin` 和 `scene_1.bscn` 仍在，`scene_2.bscn`、`flow_2.fg`、`actors_2.sidecar` 没有残留。
- standalone：从资产副本运行并保存，删除副本里的场景、Flow、Actor 文件，再用 `1 load` 启动，checkpoint 重建 generation 1，`state_hash` 与用户位置等于保存值。
- 变异：find 不校验 payload、加载忽略 checkpoint 里的文件、保存失败不清理新文件，三处都让断言变红，恢复后通过。另一处“不经 manifest 查找、按 generation 拼场景文件名”没有被杀死：runtime 记录的查找已经校验 manifest 中全部 payload，损坏的场景文件仍在 checkpoint 阶段被拒，这是等价变异。
- `test_core_app_` 27/27；ASan+UBSan 14/14、TSan 14/14，无 sanitizer 报告；非图形全量 381/381。

### 仍未做

`scene_state_save`（物理体等场景运行态）没有写进 checkpoint，动态墙仍由 runtime 标志重建；错误 Actor generation 与 GPU/record 资源 staging 失败两项失败矩阵用例未做。

## P12 Task 4：ActionMap、触摸与固定步长用户控制（2026-11-13）

Task 2 节记录的 `SOURCES` 合同在本任务扩展为七个文件：原四个加 `scenario.c`、`core_app_input.c`、`core_app_simulation.c`，命名合同同步检查。

### scenario 文法

`engine/apps/core_app/scenario.h/.c` 取代 Task 3 的 `frame N load|unload|end` 子集。首行固定为 `core-app-scenario 1`，随后是 `seed N` 和非零 `fixed-dt-ns N`，之后每行一个事件：

```text
<tick> key <a-z|0-9|space> <0|1>
<tick> touch <source-id> <down|move|up|cancel> <x> <y>    # x、y ∈ [0, 1]
<tick> pad <0-3> <axis 0-5> <value ∈ [-1, 1]>
<tick> flow <event-key> <value>
<tick> save | load | unload | screenshot | quit
<tick> save-to <relative-path> | load-from <relative-path>
<tick> level [asset-root]
```

tick 是不带符号的十进制，范围 1..1048576，且不得回退；`quit` 恰好出现一次，并且必须是最后一个事件。上限为 64 KiB、4096 个事件、每行 511 字节、路径 255 字节。任何违规都使整份文件 `INVALID`，输出结构清空，不执行已解析的前缀。事件数组在堆上按需扩容，不再使用约 1 MB 的栈对象。

`level [asset-root]` 是对计划文法的补充：计划中的 `load`/`load-from` 表示 Task 8 的 checkpoint 恢复，资产关卡加载需要一个独立命令。三个正式 scenario 由 baker 按新文法重新生成。当前 `core_app_run` 只执行 `key`、`touch`、`pad`、`level`、`unload` 和 `quit`，并要求 `fixed-dt-ns` 等于 16666667；`flow`、`save`、`load`、`screenshot` 等由 Task 5、8、11 接入，在此之前出现时以 `stage=scenario` 拒绝，不会被静默忽略。

### 输入与模拟

`core_app_input` 拥有自己的 `InputState` 和 `InputExtended`，`InputExtended` 初始化后不再复制。每个 tick 先推进按键边沿和触摸帧状态，再应用该 tick 的事件；对外只导出 POD 帧，包含按键、触摸点、手势和 haptic 状态。

`core_app_simulation` 在创建时绑定 9 个动作：forward、back、left、right、jump、interact、fire、save、load。键盘使用 W/S/A/D、空格、E、鼠标左键、F5、F9，手柄使用左摇杆和按钮。每个 tick 依次执行：`break_game_eval_actions`；把活动触摸映射成虚拟摇杆（纵向位移除以 0.1 作为 forward，横向作为 strafe，钳制到 [-1, 1]，release/cancel 的触摸不计入）；`break_game_move_wish`（yaw 为 0）；`character_update(CORE_APP_FIXED_DT)`；最后把位置写回 `BREAK_GAME_POSITION_COMPONENT`。模拟结果不读取墙钟。`core_app_accumulator_advance` 每次最多产生 8 个 substep，超出的时间计入 `dropped_ns`，不改变步长；由于应用目前只支持 fixed-step，它暂时只有单元测试。

### 关卡接线与 trace

`stage_simulation` 位于 physics 之后、AI 之前。它给 User（实体 index 2，对应场景节点 1）添加位置组件，脚底高度取节点中心减去半高。原来代表用户的 70 kg 动态 box 已删除，角色控制器是用户唯一的碰撞体，否则控制器会把自己的 box 推开。用户出生点前方 3 m 处有一个 AABB Area。Area 回调只累加计数（上限 8，溢出另计）；tick 结束后由主循环为 pad 0 请求一次 haptic。没有手柄时，trace 记录 `status=disconnected request=0`，移动不受影响。

Task 4 当时每个 tick 的顺序为：开始输入帧 → 应用本 tick 事件（遇到 `quit` 则结束）→ 模拟 → Area → `event=user tick=… x=… y=… z=…`（`%.9g`）→ `event=haptic …` → render record → audio listener。

### 验证

- `test_core_app_runtime` 共 22 项：解析器拒绝 tick 回退、tick 0 和超限 tick、4097 个事件（tick 从 1 开始，恰好 4096 个事件为 OK）、64 KiB+1、未知命令、NaN 坐标、重复 quit 和 quit 之后的事件；解析 `level`；三个正式 scenario 都能解析；输入覆盖触摸 id 复用后 generation 改变、cancel 不产生手势、按键按住与释放，以及 haptic 的 DISCONNECTED/UNSUPPORTED/排队后断开不执行、执行时携带 pad generation、换 serial 重连后旧请求为 STALE；`core_app_input_snapshot` 复制平台触摸且不修改源，ABI 版本或结构大小不符时 INVALID；模拟覆盖键盘与触摸位置一致、release/cancel 后停止、两次运行逐位相同、8 ms 与 33 ms 墙钟步进结果逐位相同，以及 accumulator 计算。每组都先在 stub 上取得 RED。
- 真实进程 CTest `test_core_app_lifecycle_input_key`、`_touch`、`_cancel`（key 模式另把 `deterministic.scenario` 运行两次并要求 trace 完全相同）：W 键 180 tick 与触摸上拖 180 tick 在 tick 180 的 trace 都是 `x=0 y=6.51925802e-08 z=15.3000059`；release/cancel 后 tick 10、11、20 的 x 和 z 不变（z=0.850000143）；Area haptic 恰好记录一次 disconnected。同一 `deterministic.scenario` 运行两次，trace 逐字节相同。
- 生产变异全部被杀死，恢复后用 `cmp` 确认字节一致：cancel 映射为 MOVE 时单元测试 13/15、进程级 cancel 用例失败；固定 dt 改为墙钟时 14/15；UNSUPPORTED 映射为 OK 时 9/10；Area enter 不计数时进程级 key/touch 用例失败；删除 4096 事件上限时单元测试 21/22。
- 回归：普通构建非图形 373 项入选，369 PASS，4 个既有文档化 SKIP（D3D12 dependency gate 与 3 个 nm 合同），0 FAIL。ASan+UBSan focused 10/10，TSan runtime+lifecycle 5/5，均无 sanitizer 报告。

### 限制

证据仍是 Linux CPU/record。没有真实 Wayland 键盘或触摸注入，没有手柄硬件或 haptic 执行，没有 GPU 和音频设备。`core_app_input_snapshot(InputState, InputExtended, frame)` 已提供从 `platform_input()`/`platform_input_extended()` 一次复制 POD 快照的入口，并校验 ABI 版本与结构大小（单元测试覆盖），但 record 模式没有窗口，`core_app_run` 尚未调用它；真实窗口后端接线与交互模式 accumulator 主循环要等 Task 11，本任务不宣称已实现。Haptic 请求的任何非 INVALID 结果只写入 trace，不终止运行；应用尚未执行 haptic pump，因为没有真实手柄后端。

## Core App Task 9：有界音频命令、null/record/device 三模式与代际隔离（2026-11-14）

### 变化

`CoreAppAudio` 从 Task 3 的 16 条 record 占位队列扩展为本任务合同：命令队列 256 条、source 槽 8 个，命令种类为 `LISTENER`、`PLAY_3D`、`POSITION`、`STOP`。入队只复制 POD 并推进序号，队列满返回 `BREAK_RUNTIME_OVERLOAD` 且计数 `overloads`，不覆盖最老命令；drain 后同一队列可再次入队。

source 槽带 generation。只有 `PLAY_3D` 认领槽位；`POSITION` 和 `STOP` 只按本代 generation 查找已有槽位，查不到即视为上一代遗留命令，计入 `stale_commands` 且不写 trace、不触碰任何槽。`STOP` 成功消费后释放该槽，使同一 index 在下一代可以被重新认领。这样“关卡 1 的迟到 STOP”永远不会停掉关卡 2 复用同 index 的 source。

启动有三种模式：`core_app_audio_start`（record，写 trace）、`core_app_audio_start_null`（无 trace sink，drain 只消费状态）、`core_app_audio_start_device`。设备路径当前没有编译进来的设备后端，因此如实报告 `event=audio mode=device result=unavailable fallback=null|none`：普通 `--audio=device` 降级为 null 泵并计数 `device_fallbacks`，`--audio=device --require-device` 返回 `BREAK_RUNTIME_UNAVAILABLE` 并让进程以退出码 77 结束。`core_app_run` 的 drain 调用点统一走 `app_audio_drain`，按已启动模式分派 record/null。

`BREAK_RUNTIME_UNAVAILABLE` 是新增的运行时错误值，语义是“可选外部设施缺失”，与“设施存在但行为异常”的 `BREAK_RUNTIME_FAILED` 区分；`break_runtime_error_name` 同步给出该名字。

### 验证

`test_core_app_runtime` 新增 8 项：

| 用例 | 断言 |
|---|---|
| `audio_queue_admits_two_hundred_fifty_six_commands` | 容量恰为 256，256 条全部 OK 且 `overloads=0` |
| `audio_full_queue_reports_overload_and_keeps_oldest` | 第 257 条 OVERLOAD、`overloads=1`、队头序号仍为 1；drain 1 条后可再入队 |
| `audio_record_trace_keeps_command_order_and_generation` | listener→play_3d→position→stop 的 `sequence` 与 `source` 逐行吻合 |
| `audio_source_generation_rejects_late_stop_for_new_level` | 同代 STOP 释放槽；下一代复用同 index；旧代 STOP 计入 `stale_commands` 且不动新代槽 |
| `audio_shutdown_drains_and_refuses_new_commands` | 关闭 admission 后入队 CLOSED；未 drain 时 join TIMEOUT；drain 后 join/destroy OK |
| `audio_null_mode_accepts_commands_without_a_trace` | null 模式无 trace 也能完整走完入队→drain→停止 |
| `audio_device_mode_reports_unavailable_and_degrades_to_null` | 可选设备不可用时降级 null、`device_fallbacks=1`、trace 记录 fallback |
| `audio_device_required_mode_fails_when_no_device_exists` | 必需设备不可用时返回 UNAVAILABLE 且不降级 |

真实进程用例 `test_core_app_lifecycle_load_unload` 的音频断言同步为带 `sequence`/`source` 的完整行。设备路径没有启用 `test_core_app_audio_device` 的专用 CTest：本机没有音频设备，新增该用例只会得到 UNAVAILABLE，因此不把环境缺失写成 PASS。

### 仍未做

设备后端（真实 `AudioSystem` 的 owner 线程与 `audio_play_3d` 调用）、`tone.wav` 的关卡播放事件、256 条满队列的进程级压力用例。record/null 路径的证据是单元与真实进程 trace，不是听感验证。

## Core App Task 10：可选认证网络通道的边界层与客户端权威防火墙（2026-11-14）

### 变化

新增独立的 `core_app_network` 静态库（`engine/apps/core_app/core_app_network.c`），不改动被契约固定为七个源文件的 `core_app_runtime`。该库提供一条默认关闭的 snapshot 通道的“无状态两半”：

- **出站 snapshot**：固定小端布局，32 字节头（magic `CSNP`、version、header_bytes、frame_id、level_generation、schema_hash、entity_count）+ 每实体 24 字节（index、generation、x、y、z、flags）。`core_app_snapshot_encode` 在容量不足时不写任何字节；`core_app_snapshot_decode` 先按声明数量与 payload 长度校验再索引，未知 magic/version 直接拒绝。`core_app_snapshot_schema_hash` 对字段布局做 FNV-1a，布局不同的对端在解释任何字段前就被拒。
- **权威防火墙**：`core_app_snapshot_inbox_admit` 只把对端消息当作诊断数据消费，从不返回仿真可应用的值。未认证、未知 message id、schema 不符、level generation 与本地实时值不一致的 snapshot 分别计数并丢弃；它不持有任何关卡指针。
- **有界出站**：`core_app_snapshot_outbox` 容量 8，满则计数 `dropped` 并丢弃最年轻的一帧，绝不阻塞或回滚调用方的帧。

`core_app` 现链接 `core_app_network`（命名契约与链接契约同步更新）。`--network` 的编译开关 `CORE_APP_ENABLE_NETWORK` 仍默认关闭，真实传输路径（reactor/Session/TLS/acceptor）不在本步。

### 验证

`test_core_app_network` 10/10：

| 用例 | 断言 |
|---|---|
| `snapshot_build_rejects_entity_count_over_capacity` | 超过 64 实体返回 OVER_LIMIT |
| `snapshot_roundtrip_preserves_fields` | 字段逐位往返，编码长度等于 32+n*24 |
| `snapshot_encode_rejects_small_buffer_without_writing` | 缓冲不足时返回 OVER_LIMIT 且不写缓冲、不改 `out_size` |
| `snapshot_decode_rejects_bad_magic` | 改 magic 返回 BAD_MAGIC |
| `snapshot_decode_rejects_unknown_version` | 改 version 返回 BAD_VERSION |
| `snapshot_decode_rejects_truncated_and_over_limit_payloads` | 缺一字节 TRUNCATED；声明数量超容量 OVER_LIMIT |
| `snapshot_schema_hash_is_stable_and_layout_sensitive` | 两次调用一致且非 0 |
| `snapshot_inbox_drops_unauthenticated_and_unknown_messages` | 未认证/未知消息分别计数且 `accepted_snapshots=0` |
| `snapshot_inbox_drops_schema_mismatch_and_stale_level` | schema 不符、generation 过期分别计数，匹配时恰好接受一次 |
| `snapshot_outbox_is_bounded_and_counts_drops` | 容量 8 满后 OVER_LIMIT 且 `dropped=1`，FIFO 弹出顺序正确 |

变异：让 inbox 放行未认证消息被 `snapshot_inbox_drops_unauthenticated_and_unknown_messages` 杀死。

### 仍未做

真实 TLS/Session/reactor 传输接线、真实认证客户端 loopback 用例、`--network --bind/--tls-cert/--tls-key/--psk-env/--port-file` 的应用参数与 acceptor 生命周期。这些需要 `CORE_APP_ENABLE_NETWORK=ON` 且 `BREAK_ENABLE_SNOWFLAKE=ON` 的独立构建树；当前 `core_app` 在无网络构建下 `--network` 明确退出 2。本步只交付与传输无关、可离线验证的边界层，不宣称已打通真实网络。

## Core App Task 12：确定性 fuzz、三棵验证树与 no-tests 真实进程（2026-11-14）

### 变化

新增两个显式 fuzz target（`EXCLUDE_FROM_ALL`，只在 fuzz lane 构建）：

- `fuzz_core_app_checkpoint`：经真实 writer 造出一份有效 checkpoint，每轮从干净状态重建 `valid` 与 `sentinel` 两棵树，对 manifest 做五类变异（截断、单比特翻转、4 字节全 1、清零连续区、随机字节）。每次变异后调用真实 `core_app_checkpoint_probe`，接受则再走 `core_app_checkpoint_find`；同时断言 `sentinel` 目录字节不变且仍能 probe，证明被拒的变异不会污染无关 state。200 次固定 seed 得到 `accepted=45 rejected=155`，重复运行逐位一致。
- `fuzz_core_app_scenario`：对合法 scenario 文本做四类变异（整行替换为敌意变体、任意字节截断、控制字符注入、追加数字），每次调用真实解析器。断言解析成功时事件数不超过上限，解析失败时 `event_count == 0`（拒绝的文档不得留下部分事件）。

fuzz smoke 在 `ENGINE_BUILD_FUZZ_SMOKE=ON` 下注册为 `fuzz_core_app_checkpoint_smoke`（200 次，seed 31）与 `fuzz_core_app_scenario_smoke`（500 次，seed 37），同其余七个 fuzz smoke 一样带 `fuzz` 标签。

### 验证

- 普通树 fuzz lane：9/9 PASS（新增两项 + 既有七项）。
- ASan+UBSan 树：`fuzz_core_app` 两项 + `test_core_app_runtime`、`test_core_app_network` 与 12 项 lifecycle 共 16/16 PASS，无 sanitizer 报告。
- TSan 树：`test_core_app_runtime`、`test_core_app_network`、lifecycle 全绿，无 TSan 报告。
- no-tests 树：`core_app` 在无测试构建下仍可构建并跑完整个生命周期。

### 仍未做

fuzz corpus 不落盘、无 libFuzzer 结构感知；`fuzz_core_app_network` 未做（snapshot 编解码已有确定性单元测试覆盖边界，但没有对应变异 fuzzer）。Task 11 的真实 GPU 像素证据不在本步。

以下区域完整保留 Core App Task 1 命名边界及 2026-11-06 至 2026-11-13 已执行设计、命令和证据原文。历史名称只按上述当前映射理解，不把历史命令当作当前可执行路径。

<!-- CORE_APP_HISTORY_BEGIN -->
## Core App Task 1 命名边界（2026-11-11）

本步只迁移尚未进入 master 的 P12 应用及真实引用，应用、target、接口、测试和 11 个正式资产路径统一使用 `core_app`/`CoreApp`/`CORE_APP` 体系；P0–P11 公共 API/ABI 与链接关系不变。数据格式在本步不变：`GAMECKPT`、`manifest.game`、`GAMEAPPTRACE` 和 `game-app-scenario 1` 仅作为既有格式声明/使用暂时保留，Task 2 将一次性迁移并拒绝旧格式，本步不增加双格式兼容路径。命名合同中的上述格式豁免与既有兼容 API、原型字符串、当前工作树/分支名均按精确字面量审计，历史报告不进入扫描。

# Game App 真实集成

日期：2026-11-06

## 当前状态

P12 Task 1 已建立独立 `game_app` 可执行应用及 `game_app_core` 静态库，并交付严格命令行入口和真实进程合同测试。完整关卡、输入、模拟、渲染、音频命令、checkpoint 和卸载生命周期尚未实现；当前 `game_app_run()` 对合法配置明确返回 `BREAK_RUNTIME_FAILED`，真实诊断含 `runtime returned FAILED`，进程退出 2，不以空壳返回成功。

## Target 与依赖边界

- `game_app_core` 是顶层 C11 静态库，独立于 `ENGINE_BUILD_TESTS`，当前拥有 `apps/game_app/game_app.c`。
- `game_app` 是真实可执行目标，拥有 `apps/game_app/main.c`，链接 `game_app_core` 并经 `engine_link_rhi_backend(game_app)` 使用现有 RHI 选择链。
- `game_app_core` 显式链接 `engine`、`break_game`、`break_ai`、`break_flow`、`break_lua`、`break_game_lua` 和 `runtime_core`。
- `engine`、`engine_demo`、`dxx_break` 不链接上述新增集成层。Actor/Lua 适配器使用 `engine/src/game/break_game_lua.h`；世界呈现 API 位于 `engine/src/renderer/world_presentation.h`。
- `GAME_APP_ENABLE_NETWORK` 默认 `OFF`，CMake 始终把数值 `0` 或 `1` 传给 `game_app` 的同名预处理条件。OFF 时 `--network` 被真实进程拒绝；ON 时该选项可以进入运行时，但本任务仍只返回 `BREAK_RUNTIME_FAILED`，没有网络实现或伪成功。

配置末尾直接检查实际 target 的 `LINK_LIBRARIES`：锁定 `game_app_core` 依赖、legacy consumer 的直接链接集合和网络 0/1 定义。多行命令与变量展开因此由实际 target property 验收，而不是只扫描命令首行。合同还实际执行 `ENGINE_BUILD_TESTS=OFF` configure，防止 target 被移入测试作用域。

## 命令行合同

```text
game_app --help
game_app [--render record|auto|vulkan|opengl]
         [--audio record|null|device]
         [--assets DIR] [--scenario PATH] [--checkpoint DIR]
         [--trace PATH] [--screenshot PATH]
         [--fixed-step] [--frames N] [--require-device] [--network]
```

带值选项同时接受 `--name value` 和 `--name=value`。默认资产目录为 `assets/game_app`，渲染为 `auto`，音频为 `device`。`--frames` 的精确词法是先满足 `[0-9]+`，再检查数值范围 1..4294967295；前导空白、`+`、负数、0、非数字、空值和溢出均退出 2，并报告 `--frames requires a positive 32-bit integer`。未知参数、非法枚举、缺值和 `--help` 后额外参数也退出 2，并使用各自的 CLI 错误诊断。

`--help` 单独使用退出 0 并输出 `Usage: game_app` 及全部选项。合法默认配置、完整 record 配置和合法 `--frames 4294967295` 都必须到达运行时并报告 `runtime returned FAILED`；不得提前落入 CLI 错误或 `BREAK_RUNTIME_INVALID`。后续真实设备不可用证据码 77 将在对应图形/音频任务接入，本任务不伪造该证据。

## 验证

`test_game_app_target_contract` 检查 configure-time target/链接边界，执行真实 no-tests configure，并启动真实进程覆盖帮助、运行时 FAILED、非法类别、network OFF/ON 和全部数字边界；有能力的 `nm` 扫描还必须找到 `game_app_run`，再排除 `_for_test`/`test_hook`。

nm 扫描仅对非 Windows 或 MinGW 且实际支持 `--defined-only` 的工具/二进制格式启用。无 NM、不支持该参数或无法识别输出格式时返回 77 并标记 `UNVERIFIED`，不输出完整合同 PASS。`test_game_app_nm_missing` 与 `test_game_app_nm_unsupported` 分别锁定这两条路径；CTest 中显示为 Skipped，而不是符号扫描通过。

从工作树根运行：

```bash
cmake -S engine -B build-game-integration-normal \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-game-integration-normal -j3 --target game_app
ctest --test-dir build-game-integration-normal \
  -R '^test_game_app_(target_contract|nm_missing|nm_unsupported)$' \
  --output-on-failure

cmake -S engine -B build-game-integration-no-tests \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=OFF \
  -DENGINE_ENABLE_IPO=OFF -DENGINE_RHI_BACKEND=auto \
  -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-game-integration-no-tests -j3 --target game_app
```

网络开关的 ON 配置可独立验证，但仍不提供网络：

```bash
cmake -S engine -B build-game-integration-network-flag \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF \
  -DGAME_APP_ENABLE_NETWORK=ON
cmake --build build-game-integration-network-flag -j3 --target game_app
ctest --test-dir build-game-integration-network-flag \
  -R '^test_game_app_target_contract$' --output-on-failure
```

当前证据仅为 Linux CPU 构建、configure 和真实进程 CLI。没有运行真实场景、真实 Vulkan/OpenGL 窗口、音频设备或网络；record/headless 也不能解释为 GPU 画面。后续任务必须分别提供这些证据。

## P12 Task 2：离线资产与 checkpoint v1

### 固定关卡与 baker

`game_asset_bake --output DIR` 是独立 C11 离线工具；目标在 `ENGINE_BUILD_TESTS=OFF` 时也存在。它不调用 `game_app_run()`，不创建 RHI 设备、音频设备、网络或跨线程所有权。源树正式资产只由该命令显式生成，测试使用 per-process 临时目录。

`level.bscn` 由真实 `scene_save_binary` 写出并由 `scene_probe_binary`/`scene_load_binary` 回读。固定实体顺序为 Ground、User、Chaser、DynamicWall、Vehicle、VisibleColor、HiddenColor；`actors.sidecar` 逐行使用 P1 已有的 `entity-index class-name` 格式。七个实体共享一份真实 CPU cube 几何（24 vertices、36 indices），通过 `SerializeOptions.read_mesh_geometry` 交给 BSCN writer；没有 GPU readback。七个节点使用各自的变换和颜色材质，隐藏颜色节点保留 mesh/material 引用但初始 `has_mesh=false`。场景实体和 Flow 目标只保存 `(index, generation)`，没有持久化 C 指针。

`level.fg` 由 `break_flow_serialize` 生成，包含 enter → delay(30 ticks) → add-item 的两条 exec link。`director.lua` 和 `user.lua` 可由真实 `break_lua` 加载，`chaser.lua` 是明确的语法错误 fixture；本任务不建立运行时 VM 生命周期。`level.banm` 由 `anim_codec_encode` 生成，含 translation/rotation/scale 三个通道，测试用 `anim_codec_decode`、`anim_codec_time_error_bound`、`anim_codec_scalar_error_bound` 和旋转误差界验收。`tone.wav` 是固定 seed 的 44100 Hz、mono、16-bit PCM，4410 个样本；没有音频设备或听测证据。

三个 `.scenario` 文件是版本化固定输入资产，由同一 baker 生成；场景脚本解析和生命周期执行属于后续任务，本任务没有声称它们已运行。

### checkpoint v1 格式与事务

`manifest.game` 为显式小端二进制：40 字节头加每条 88 字节记录。头依次是固定 8 字节 `GAMECKPT`（无额外 NUL）、version=1、header_bytes=40、exact_total_size(u64)、generation(u64)、file_count(u32)、reserved(u32)。记录依次是 kind(u32)、name_length(u32)、size(u64)、FNV-1a-64(u64)、64 字节以 NUL 结尾并零填充的 basename。FNV 只用于损坏检测，不是安全认证。

每代 1..16 个文件，每文件最多 64 MiB，basename 最多 63 字节且只允许 ASCII 字母数字、`_.-`；路径分隔符、绝对路径、`..`、`.` 和 `manifest.game` 均被拒绝。容量或长度超限返回 `BREAK_RUNTIME_OVERLOAD`，不静默截断。读取先验证完整 manifest 和所有记录，再逐文件以固定 4096 字节缓冲 staging 校验精确长度和 hash，无需按 payload 大小分配。

调用者先以新 generation 名写 payload，避免覆盖旧 manifest 引用的文件。`game_checkpoint_write_manifest_ex` 先重新读取并校验所有新 payload，再用一个 `PlatformAtomicWriter` 提交 manifest。write、file-fsync、close 或 rename 在目标替换前失败时返回 `BREAK_RUNTIME_FAILED`，结果为 `GAME_CHECKPOINT_COMMIT_NOT_COMMITTED`，旧 manifest 不变，并按既有安全规则清理新 payload。rename 成功后 directory open/fsync 失败时返回逻辑 `BREAK_RUNTIME_OK`，结果为 `GAME_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN`，新 manifest 与 payload 保留，不执行恢复 rename。旧 `game_checkpoint_write_manifest` 保留逻辑提交 API，OK 也可能表示 unknown；需要 durability 区分的调用必须使用 `_ex`。`game_checkpoint_probe` 不修改任何 World/Level；真实运行状态反序列化、资源重建和事务 load 属于后续任务。

### 已执行的 Task 2 证据

Linux 上 `test_game_app_assets` 为 9/9，通过两回 baker 逐字节比较、BSCN+P1 sidecar、Flow、BANM、WAV、Lua、manifest 格式、payload/manifest 损坏、非法名称/容量和 RLIMIT_FSIZE 中途写失败回滚。相关 `test_scene_serial`、`test_break_flow_serial`、`test_anim_compression`、`test_break_game_level`、`test_platform_fs_write`、`test_break_lua_module` 与新增测试合计 7/7 通过。

生产变异临时删除 payload hash 比较后，篡改用例如期失败（8 通过、1 失败）；恢复后 9/9。正式 `engine/assets/game_app` 的 11 个文件均由最终 baker 生成，并与第二回独立输出逐 `cmp` 一致。关键 SHA-256 为：`level.bscn` `85c1f349f8fc50fd916d3aa74797c337ee34d2c5ae65f723d10df2def6e0537e`，`level.fg` `9be4ca42a7bbd0e3ccd7f663a9d372b15b0daaaaeac08a8f876e15d0a57fb473`，`level.banm` `f3181920a4cdf26267b0aaeefb29664b9fae582ddaef9d39558403e236788873`，`tone.wav` `f0e63c5eb3adef364e73e3113573b104a372bad25425819684ee1d0a695e2682`。

这些证据仅为 Linux CPU/文件系统证据。未运行 Windows 写路径、真实运行时循环、GPU、音频设备、听测或网络；`game_app_run()` 对合法配置仍按 Task 1 合同返回 `BREAK_RUNTIME_FAILED`。

### 最终回归补充（2026-11-09）

完整构建使用 `cmake --build build-game-integration-normal -j3` 成功。任务的非图形验收命令为 `ctest --test-dir build-game-integration-normal -j3 -LE 'graphics|fuzz' -E 'fuzz' --output-on-failure`，结果 330/330 通过；`test_d3d12_dependency_gate`、`test_game_app_nm_missing`、`test_game_app_nm_unsupported` 三个测试按各自既有合同跳过，未把跳过写成设备或符号扫描通过。

曾先用名称过滤 `-E 'graphics|fuzz'` 运行 341 项；该方式不排除 `graphics` 标签，因而执行了图形/平台测试，并出现既有 `test_platform_x11_runtime` 的 `start_fullscreen window does not cover the monitor` 一项失败。本任务未修改该 X11 行为，也不将此运行计为非图形通过证据；正确标签过滤后的 330 项结果才是上述验收结果。

`ENGINE_BUILD_TESTS=OFF` 的独立构建树已成功构建 `game_app` 和 `game_asset_bake`，该 baker 的 11 个输出也与源树正式资产逐字节一致。`test_game_app_target_contract` 再次通过；两个 nm negative-path 测试仍按合同跳过。合法 `game_app` 配置的真实进程仍返回 FAILED/退出 2，未被资产交付改成伪成功。

## P12 Task 2 独立评审 fix round 1

### 正式资产追踪与读取

根目录 `.gitignore` 仅对 `engine/assets/game_app/tone.wav` 增加例外，避免通用 `*.wav` 规则继续漏掉正式资产。`test_game_app_formal_asset_tracking` 对 Git 索引要求恰好 11 个指定路径；`test_game_app_assets` 另要求正式目录恰好含这 11 个非空文件，并与 fresh baker 输出逐字节一致。BSCN、Flow、BANM、WAV 和 Lua reader 测试现在读取正式目录，而不是只读临时 baker 输出。`GAME_APP_FORMAL_ASSET_DIR` 测试环境变量可把同一套 reader/比较测试指向干净 Git archive 的解压目录。

### basename 长度与规范化别名

63 字节 basename 合法；API 中 64 字节无 NUL 的名称和磁盘记录 `name_length>=64` 都返回 `BREAK_RUNTIME_OVERLOAD`，非法字符、内嵌 NUL、非零 padding 等结构损坏仍为 `BREAK_RUNTIME_INVALID`。

为保证同一 checkpoint 在大小写敏感与不敏感文件系统间移动时仍不破坏旧代，v1 采用保守的统一规则，而不是按当前宿主改变接受策略：保留名、重复名和旧 payload 名都按 ASCII 大小写折叠比较；`MANIFEST.GAME` 等保留名变体被拒绝；尾随点被拒绝，避免 Windows 规范化别名；新记录与旧 manifest 中 payload 的大小写变体或尾随点变体也被拒绝。该策略会在大小写敏感系统上额外拒绝一些本来可共存的名称，是有意的可移植性格式约束。Linux 用例验证的是该格式策略，不是 Windows/NTFS 实机行为。

### 当前 checkpoint 提交与 durability 协议

`PlatformAtomicCommitResult` 区分 `SUCCESS_DURABLE`、`NOT_COMMITTED_TARGET_UNCHANGED` 和 `RENAMED_DURABILITY_UNKNOWN`；旧 `platform_atomic_writer_commit()` 仅对第一种返回 true，保持 bool 兼容。write、file-fsync、close 或 rename 在目标替换前失败时，checkpoint 返回 `BREAK_RUNTIME_FAILED`，旧 manifest 不变并安全清理新 payload，实际 rename 次数为 0。

rename 成功后 directory open/fsync 失败时，新 manifest 已经可见。checkpoint 返回逻辑 `BREAK_RUNTIME_OK` 和 `GAME_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN`，保留新 manifest 与 payload，不执行恢复 rename，并发出 fsync 警告。独立旧备份只用于恢复证据，不改变同目录提交结果。`GAME_CHECKPOINT_COMMIT_DURABLE` 仅表示平台要求的步骤完成，不声称掉电、崩溃或硬件故障下持久性已保证。

故障测试只在 `test_game_app_assets` 和 `test_platform_fs_write` 的 Linux 测试进程内使用 linker wrappers 注入 write、file-fsync、rename 和 directory-fsync 失败，同时检查返回状态、实际 rename 次数、manifest 字节/generation、payload 和 probe；生产代码没有 test hook。

已执行的新套件为 18/18，覆盖恢复成功、恢复写失败、损坏旧 manifest、名称边界和规范化别名；资产/FS/Flow/动画/P1/Lua 定向集合为 8/8。生产变异临时无视恢复结果并无条件清理，恢复写失败用例如期从 18/18 降为 17/18，恢复后回到 18/18。Windows 实机、GPU、音频设备、听测和网络仍未验证。

### fix round 1 最终验证

完整 `cmake --build build-game-integration-normal -j3` 成功，`ctest --test-dir build-game-integration-normal -j3 -LE 'graphics|fuzz' -E 'fuzz' --output-on-failure` 为 331/331 通过，三个既有 D3D12/nm 合同测试按规则跳过。`ENGINE_BUILD_TESTS=OFF` 下 `game_app` 和 `game_asset_bake` 构建成功，no-tests baker 的 11 个输出与正式资产一致；`test_game_app_target_contract` 通过，两个 nm negative-path 测试仍按合同跳过。

提交前从 Git 索引执行 `git write-tree`，对该干净 tree 的 `engine/assets/game_app` 做 `git archive`，确认恰好 11 个路径且包含 8864 字节 `tone.wav`，解压到全新临时目录后以 `GAME_APP_FORMAL_ASSET_DIR` 指向归档资产。完整 18/18 再次通过，其中正式目录与 fresh baker 比较以及 BSCN/Flow/BANM/WAV/Lua readers 均实际读取归档文件，而不是当前源树。

## 同步、命名迁移与 fix round 2（2026-11-10）

### master 同步与命名边界

实施前 WIP diff 保存在 `.superpowers/sdd/2026-11-03-cry-game-integration/task-2-fix2-before-master.diff`，独立 stash 为 `cef5784afeb52a37b1064d417a3fedc742e15162`。同步 merge 为 `0f2b137384fdc41f44509cc5a40b26c098213007`，双亲分别是 Task 2 fix1 与 master `ffdd2e865ec1e34568588404e69ae8c1716cafb4`；X11 移除、C++20/QUIC 和 Task 1/2 改动均保留，既有其它 stash 未使用或删除。

应用、核心库、baker、目录和测试现使用 `game_app`、`game_app_core`、`game_asset_bake`、`test_game_app_*`；checkpoint 文件/API/类型使用 `game_checkpoint`/`GameCheckpoint*`。资产位于 `engine/assets/game_app`，设计文档为 `docs/design/game_app_integration.md`，新结果只使用 `build-game-integration-*`。P12 计划 Task 1–13 的后续 `scenario`、`game_input`、`game_simulation`、`game_render`、`game_audio`、`game_network`、`game_script` 名称同步更新。P0–P11 的 `break_game`、`BreakRuntimeError`、`test_cry_style_prototype` 等既有公共名称未迁移。

`test_game_app_naming_contract` 防止新集成源码、资产、目标、测试和当前设计/计划重新引入旧前缀；只对明确的 P0 既有测试/文档引用豁免。`manifest.game` 的 magic 为固定 8 字节 `GAMECKPT`，reader 只接受该标识，不双格式兼容。scenario 首行同步为 `game-app-scenario 1`，正式文件由重命名后的真实 baker 重新生成。

### 可区分提交结果

`PlatformAtomicCommitResult` 区分 `SUCCESS_DURABLE`、`NOT_COMMITTED_TARGET_UNCHANGED` 和 `RENAMED_DURABILITY_UNKNOWN`。旧 `platform_atomic_writer_commit()` 保留 bool 兼容，只在 `SUCCESS_DURABLE` 时返回 true；需要区分 rename 后状态的调用方使用 `platform_atomic_writer_commit_status()`，writer 仍在所有结果下被消费。POSIX 记录 rename 是否实际发生，Win32 保留 `MoveFileEx(WRITE_THROUGH)` 分支，未以 POSIX 证据代替 Windows 实机验证。

`game_checkpoint_write_manifest_ex()` 额外返回 `GameCheckpointCommitResult`。只有 rename 前的失败返回普通 `BREAK_RUNTIME_FAILED`，保持旧 manifest 并按既有安全规则清理新 payload。rename 已成功而 directory open/fsync 失败时，不恢复新 manifest，不删除新 payload，返回逻辑 `BREAK_RUNTIME_OK` 和 `GAME_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN`，同时发出明确 fsync 警告。旧 `game_checkpoint_write_manifest()` 保留逻辑提交 API，OK 也可能表示 unknown；需要 durability 区分的调用必须使用 `_ex`。`GAME_CHECKPOINT_COMMIT_DURABLE` 仅表示平台要求的 file/directory 步骤完成，不声称任意崩溃、掉电或硬件故障下持久性已证明。

真实故障矩阵同时检查返回值、实际 rename 次数、manifest 字节/generation、旧新 payload 和 probe：write/file-fsync/rename 失败为 FAILED+NOT_COMMITTED，directory-fsync 失败为逻辑 OK+UNKNOWN；旧 manifest 损坏时的独立备份仍可用。rename 后没有恢复 writer 或第二次恢复 rename。

### 已执行的迁移后证据

新构建树的真实 `game_app` CLI/target、资产、命名和 reader focused 集合为 12/12（两个 nm negative-path 按既有合同跳过），`test_game_app_assets` 为 20/20，`test_platform_fs_write` 为 11/11。ASan+UBSan 和 TSan focused 均 4/4，无 sanitizer 报告。旧 scenario 数据标识曾使正式目录与 fresh baker 比较出现 19/20，使用最终 `game_asset_bake` 重生成后恢复 20/20。生产变异把 unknown 错映射为 FAILED，三个 rename 后协议用例按预期降为 17/20；恢复后再次 20/20。

正式 `engine/assets/game_app` 的 11 个文件均由最终 baker 生成，fresh 第二回逐字节一致。未运行 Windows/NTFS 实机、真实运行时主循环、GPU、音频设备/听测或网络；这些结果不构成崩溃持久性证明。

### 全量与交付验证补充

完整 `cmake --build build-game-integration-normal -j3` 成功，`ctest --test-dir build-game-integration-normal -j3 -LE 'graphics|fuzz' -E 'fuzz' --output-on-failure` 为 346/346 通过；`test_d3d12_dependency_gate`、`test_game_app_nm_missing`、`test_game_app_nm_unsupported` 按既有合同跳过。`ENGINE_BUILD_TESTS=OFF` 的 `build-game-integration-no-tests` 成功构建 `game_app` 与 `game_asset_bake`，no-tests baker 的 11 个输出与正式资产逐文件一致；`test_game_app_target_contract` 再次通过，两个 nm negative-path 仍按合同跳过。

master 的 X11 removal 合同和 C++20 public API/QUIC 相关测试均包含在上述全量结果中，没有为 Task 2 回退或排除这些既有行为。


## P12 Task 3：事务式 level 与 record 生命周期（2026-11-10）

本节是当前生命周期状态；上方 Task 1 的“合法配置始终 FAILED”和 Task 2 的“主循环尚未运行”仅保留为当时历史。同步 master `737ccc8b4227f2d53039119caf1a2b6066e2871e` 的独立 merge 为 `30c9285d9605ff07157f8563cda60279082f6269`，也是本任务 review BASE。合并没有冲突，X11 移除、CI 修复、Task 2 命名/资产/checkpoint 三态协议及双方文档均保留。

### 所有权与加载事务

`game_app --render=record --audio=record --fixed-step` 现在执行真实场景文件。主线程即 GameThread，独占 `World`、`BreakGame`、Lua/adapter、Flow、AI 和 physics 的可变状态；Runtime IO worker 只通过 VFS 返回有界字节，不接触这些对象。render/audio 分别只消费固定大小的 `GameRender*`/`GameAudio*` POD 快照与命令。

每次 load 都分配独立 `GameLevel` candidate，顺序为：注册 ECS 组件并创建 World → Runtime IO 读取 BSCN、`scene_load_binary_memory` 在 candidate World/Scene 上完成 CPU staging → Flow 反序列化/实体引用验证、两个正式 Lua module 加载和 adapter 创建 → `break_game_level_open` 验证正式 actor sidecar 并 adopt → physics ground/user body → 8x8 CPU navmesh、AI runtime/Chaser agent → BANM decode → record resource POD staging → World/Scene/Flow/resource 交叉引用。只有全部成功后才执行一次 `game->level = candidate` 并递增非零 u64 generation。

candidate 的任一模态资源或验证失败都走统一逆序销毁，不修改当前 level 指针或 `next_generation`。已有 level 时 replacement 失败会写 `load_rejected` 并继续旧 level；没有已提交 level 的启动失败退出 2。显式 unload 先使当前指针失效，再销毁旧 generation。正常 replacement 成功时也先完成 candidate，再提交新代并释放旧代。

`break_game_level_open` 的 load hook 不重复读取 BSCN：它只确认先前 `scene_load_binary_memory` 已填充同一 candidate 的 World/Scene。这样 P1 的 sidecar/adopt/close 生命周期是真实执行路径，同时避免第二次替换 World。

### Runtime IO 与 shutdown

整个进程只调用一次 `break_runtime_io_init`。BSCN completion 的字节被 Scene 复制后先释放 request，再进行后续 staging 或下一次 VFS mount/load；旧 request 不跨 level 保留。正常 shutdown 按 network→audio→render→level 注册 coordinator 回调：关闭 admission/producers 和 audio queue、drain、join、render idle/destroy，level drain 后执行一次 Runtime IO shutdown，确认 `active=0`，最后销毁 level/VFS。network 本任务只有生命周期占位，没有传输实现。

启动失败或 coordinator sticky FAILED 不调用 coordinator stop；`game_rollback` 显式执行 audio drain/join/destroy、render idle/destroy、candidate/current level destroy、Runtime IO shutdown 和 VFS destroy。失败 trace 写 `runtime_failed`，不会伪写正常 `runtime_stopped`。

### record 边界与场景

`game_render.c` 只记录 BSCN manifest 的非零 resource id、generation 和 frame id；没有 RHI device、GPU restore 或 `engine_rhi_headless` 链接。Task 1 已存在的 `game_app` 目标仍按配置链接 Vulkan/OpenGL runtime，但 record 路径不创建设备，不能解释为 GPU 证据。`game_audio.c` 是 16 项固定容量 FIFO，记录 listener/stop 的命令顺序；没有声卡 worker、source 控制或听测。

Task 2 的正式 `load_unload.scenario` 无需修改：frame 1 load、frame 2 unload、frame 3 load、frame 4 unload、frame 5 end。实际 trace 包含有序的 runtime_running → level_loaded 1 → frame 1 → audio listener 1 → level_unloaded 1 → level_loaded 2 → runtime_stopped，也记录第二代 frame/unload 和最终 `io_stopped active=0`。场景 parser 是 Task 3 内部的有界生命周期子集，另外允许 `load ROOT` 以测试跨资产 root 的失败 replacement；Task 4 的输入/移动语义不在此实现。

热帧路径只做固定数组 POD 拷贝、固定 FIFO 操作和 trace 输出，没有堆分配。堆分配限于进程启动和 level staging，固定上限为 64 个 scenario step、64 个 render resource、16 个 audio command、4 个 Runtime IO request 和 1 个 IO worker。

### 验证与限制

真实进程 CTest 先对 stub 观察到退出 2 和完整事件缺失，再对实现 GREEN。正常流程、缺失 BSCN、损坏 Flow、未知 Actor class、缺失 Lua module、以及“有效 load → 坏 Flow replacement → 旧 generation frame 2”均由 `test_game_app_lifecycle_load_unload` 启动真实 `game_app`，没有库 substitute。四个启动失败均退出 2，有各自 stage 诊断，没有 level/frame commit，并以 `io_stopped active=0` 结束。

生产变异曾在 Flow 验证前插入 `game->level = candidate`；正常与 replacement 进程发生段错误，失败 fixture 也无法保持合同，测试按预期 RED。删除该变异行后恢复 GREEN。focused Runtime/BreakGame/Scene 回归 5/5、game_app 既有合同 6/6（两个 nm negative-path 按合同跳过）、全量非图形 348/348 通过。ASan+UBSan 和 TSan 生命周期各 1/1 通过；no-tests 的 `game_app`/`game_asset_bake` 均构建成功。

这些证据仅是 Linux CPU/record 生命周期证据。没有输入/用户模拟、GPU `asset_scene_restore`、窗口或像素、音频设备/听测、网络、完整 checkpoint 状态恢复或完整 device worker；Windows 和其他平台未运行。VFS 的 16 mount 上限和 Runtime IO/VFS 路径上限仍是当前有界配置，超长路径或超过 mount 预算会明确拒绝 load。


## P12 Task 3 独立评审 fix round 1/5（2026-11-10）

本轮只修复 Task 3 的事务、Runtime IO/VFS 和真实进程测试，不改变 Task 4+ 范围。评审 BASE 为 `da5d475aa97823c01de2e90af351ad17b4ab2bff`；两个 Critical、三个 Important 和两个 Minor 均按下述机制闭合。

### mount namespace 与 candidate 一致性

应用拥有的 VFS 只用于 candidate BSCN，且始终只有一个 DIR mount slot。每次 `game_stage_bscn` 在提交新 request 前清空上一 candidate 的 DIR namespace，再 mount 本次 `asset_root`；不会从新 root 回退到旧 root。上一 level 的 World/Scene/record resource 已全部 CPU staging，不依赖旧 mount，因此丢弃旧 namespace 不影响已提交 level，也不会累积 16 个 mount。应用不允许其他 mount 类型或多 slot 状态进入该路径。

真实测试先 load good，再执行 17 次缺失 BSCN replacement，最后再次 load good。17 次都以 generation 1 reject，旧 level 持续逐帧，最后一次以 generation 2 成功 replacement，覆盖失败配额和 valid→valid 分支。修复前同一 fixture 连续错误提交到 generation 15，随后才因 mount 上限拒绝。

### commit 尾部与双代所有权

`game_app_level_load` 现在分别返回 `committed` 和 `runtime_fatal`。所有 staging 阶段失败（包括 render/crossref）在已有 level 时统一写 `load_rejected` 并继续旧代；只有无旧代可回退时才终止。commit 后的 audio/drain/trace/render 错误写 `runtime_fault stage=commit`，不会再写 `load_rejected` 或继续下一帧。

成功 replacement 在指针/generation 提交期间把 previous 保存在 `GameApp.retired_level`，直到实际销毁后才清空。rollback 分别清理 current 和 retired，覆盖 commit 尾部任意失败点。`level_destroyed` 只在实际销毁已提交 level 后记录；成功 replacement、commit 尾部和 sticky shutdown 测试都要求每个 generation 恰好出现一次。销毁前保存 generation，避免事件读取已释放对象。

Linux 测试用独立 `LD_PRELOAD` 库对 `level_unloaded` trace 的一次 `fflush` 注入 EIO。实际 trace 为 `runtime_fault commit → destroyed 2 → destroyed 1 → io_stopped active=0 → runtime_failed`，没有伪 reject/伪停止。对 `io_stopped` 注入同类错误则覆盖 coordinator callback 进入 sticky FAILED 后的应用级显式 rollback。

### IO timeout quiescence

首次 `wait_completion` 的 TIMEOUT 不再直接允许后续 mount，也不使用只统计 caller request 的 `stats.active` 误判 worker 已停止。代码对同一个 request 再做一次有界等待；真实 completion 只在 worker 的 VFS read 完成后发布，因此消费 completion、释放 message/request 并记录 `io_quiesced` 后，后续 mount 才安全。第二次等待失败或 quiescence trace 失败属于 runtime fatal，candidate 清理后由 shutdown/join 收尾，不再继续 scenario。

测试的 preload `fread` 在 timeout replacement 的 BSCN 上延迟 6 秒，scenario 随后再次 load good。修复前 TSan 实际报告主线程 mount 与 IO worker `vfs_open` 的数据竞争；修复后普通和 TSan 均完成 reject→旧代 frame→generation 2 replacement→正常停止。生产代码没有 test hook，测试库不替换 game/runtime 库。

### 其他覆盖与 Minor

- 将正式 BSCN 的 `MESH_DATA` chunk 标为未知类型，保留可解析 Scene 但缺少 geometry，真实触发 crossref reject；旧 generation 继续，不再因 stage 特判退出进程。
- 成功 valid→valid replacement、17 次 mount reject、commit 尾部、sticky FAILED、IO timeout、crossref 均进入同一个真实进程 CTest，因此 ASan+UBSan/TSan 执行相同路径而非只跑旧主路径。
- 删除未使用的 `old_request`；`retired_level` 具有明确所有权。
- `GAME_AUDIO_QUEUE_CAPACITY=16` 仍仅为 Task 3 临时 record 容量。源码注释和 Task 9 计划均明确：Task 9 必须扩展为 256，并实际测试超过 256 个未消费命令的 OVERLOAD 与 drain 后恢复，不能把 16 当成最终常量。

mount 清空、commit 分类和第二次 completion 等待分别做了独立生产变异；三者都取得针对性 RED 后恢复 GREEN。最终全量非图形为 348/348，no-tests 的 `game_app`/`game_asset_bake` 构建成功，ASan+UBSan 和 TSan 的完整 lifecycle 各 1/1，无 sanitizer 报告。证据仍限 Linux CPU/record；LD_PRELOAD 故障注入在非 Linux 平台标为 UNVERIFIED，不声称跨平台覆盖。
