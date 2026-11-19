# Core App 真实集成

日期：2026-11-06

## 语音处理链接线边界（2026-11-18）

`audio_voice_processor` 已提供经过逐位参考验证的五级采集处理库，但 `core_app` 尚未创建或调用它。后续接入仍需单独完成：真实播放参考的延迟对齐、`AudioCapture` owner 生命周期、处理后 PCM 的分帧/编码和网络发送。库级测试不构成真实设备、生产管线或听感证据。设计见 `docs/superpowers/specs/2026-11-18-audio-voice-processor-design.md`。

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

固定步内的顺序改为：`break_kernel_tick` → `break_flow_runtime_tick` → `core_app_simulation_tick` → `break_kernel_area_tick` → 位置 trace → 处理本 tick 累计的 Area enter → haptic → `event=actors` trace。AI、动画和 `physics_step` 仍由 Task 6 接入，本任务不把它们算作已实现。

`event=actors` 记录 User 和 Chaser 的脚本计数、用户物品数和 Flow pending 数：

```text
event=actors tick=<n> generation=<g> user_ticks=<n> user_failures=<n> \
    chaser_ticks=<n> chaser_failures=<n> items=<n> flow_pending=<n>
```

### 脚本

`stage_lua` 以 `instruction_budget = 1000000`、`memory_budget = 8 MiB` 创建 runtime，并加载 `director`、`user`、`chaser`。User 类绑定 `user`，Chaser 类绑定 `chaser`。`user.lua` 的 `on_actor_tick` 只累加 `state.ticks`；`chaser.lua` 可以加载，但 `on_actor_tick` 每次都 `error`。一个 actor 的错误只记入 `break_kernel_lua_last_fault` 和该 actor 的 `failures`，不阻止同 tick 的其他 actor。

`break_kernel_lua_actor_stats(adapter, entity, out)` 返回该 actor 的 `ticks`、`failures`、`skipped`、`last_error` 和 `disabled`。despawn 清零计数，之后查询旧 entity 返回 `BREAK_LUA_STALE`，复用同 index 的新 generation 从 0 开始。一次调用使 `break_lua_runtime_budget_trip_count` 增加时，adapter 只禁用这个 module：它的所有 actor 之后记入 `skipped`，其他 module 继续运行。普通 Lua 错误不会禁用 module。

### Flow

烘焙的 `level.fg` 事件键从 1 改为 1001，add-item 节点的数量字段 `a` 明确为 1（之前是 0，运行时会以 `BREAK_FLOW_INVALID` 拒绝）。用户前方 Area 的 enter 调用 `break_flow_runtime_post(flow, 1001, user, 1.0)`，trace 记 `event=flow kind=post key=1001 … tick=<n>`。延迟 30 tick 后动作把物品 1 加到 User，trace 记 `event=item … entity=2 item=1 count=1`。`break_flow_runtime_tick` 的非 OK 结果记 `event=flow kind=tick_failed … status=<n>`，本 tick 的其余步骤继续。Flow runtime 在失败时把队列和 `now_tick` 回滚到该次调用之前，所以同一事件会在下一个应用 tick 被再次尝试，应用自己不另做补偿。

替换关卡或卸载时，应用先 trace `event=flow kind=discarded generation=<g> pending=<n>`（pending 为 0 则不记），再销毁该 generation 的 Flow runtime。新关卡不继承旧队列，所以旧事件不能作用到同 index 的新 generation。

### 验证

- `test_break_kernel_lua` 4/4：原有的失败隔离和缺失 hook 用例，加上 60 tick 的 per-actor 计数、despawn 后 STALE、预算 trip 只禁用一个 module。
- `test_core_app_assets` 23/23：事件键 1001、add-item 数量 1、`user` 的 `on_actor_tick` 返回 OK、`chaser` 可加载但 `on_actor_tick` 返回 `BREAK_LUA_FAILED` 且不影响再次调用 `user`。
- 真实进程 `test_core_app_lifecycle_script_flow`：持续行走时 tick 30 投递且 `flow_pending=1`、物品仍为 0，tick 61 物品变为 1 且 pending 归零，tick 180 仍为 1；User 180 次成功、Chaser 180 次失败。中途卸载报告 `discarded pending=1` 且全程没有 `event=item`；第二关卡在 tick 42 从 0 开始计数，到 tick 99 物品仍为 0，也没有新的投递（用户停在原地，不再进入 Area）。
- 变异：任何 Lua 错误都禁用 module 时 `test_break_kernel_lua` 为 2/4；首个错误跳过后续 actor 时 `script_flow` 失败；删除 Area→Flow 投递时 `script_flow` 失败。三处恢复后 `cmp` 确认字节一致。
- 回归：普通非图形 374 项入选，370 PASS，4 个既有文档化 SKIP，0 FAIL。ASan+UBSan focused 8/8，TSan 6/6，均无 sanitizer 报告。

### 限制

AI、动画和 `physics_step` 没有接入，tick 顺序里这三步仍是空位。Flow 动作失败只记 trace；重试来自 Flow runtime 的回滚，应用不另做补偿。证据仍是 Linux CPU/record，没有真实窗口、手柄或 GPU。

## P12 Task 6（slice 1）：追踪者的视野、行为树、当前版本路径与动态墙（2026-11-13）

### 每 tick 顺序

固定步内的顺序扩展为：`break_kernel_tick` → `break_flow_runtime_tick` → `core_app_simulation_tick` → `app_tick_chaser` → `break_kernel_area_tick` → 位置 trace → Area enter 处理 → haptic → `event=actors` trace → `event=sim` trace。追踪者的移动意图由行为树产生，由 `CharacterController` 执行；应用自身不直接写世界位置。

### 导航场与 AI 接线

`stage_ai` 把导航高度场从 4x4 扩到 8x8（cell 1.0，`origin_x/origin_z = -1.0`），`break_nav_bake_heightfield` 的结果作为 `BreakAiRuntime` 的输入，并给场景实体 index 3 注册半径 0.4、最大速度 3 的 agent。加载期不再寻路：寻路只发生在 tick 内。

### 视野

`stage_simulation` 在用户实体周围注册一个半尺寸 (6, 3, 6) 的 Area 作为 `sight_area`；`app_area_event` 命中该区域时置 `target_in_sight`，命中 `trigger_area` 时保留 Task 5 的 Flow 触发计数。每 tick 用 `break_sight_query` 做一次射线检测：眼睛取自身位置，前向 (-0.7071, 0, -0.7071)，距离 12，半角 1.2 rad；遮挡回调只在命中动态墙刚体时判定为不可见，地面命中不遮挡。命中后写入 `BreakBlackboard` 的 `seen`、`last_seen` 和 `target`。

### 行为树与当前版本路径

每 tick 构建 SELECTOR 根 + CHASE 叶的行为树，`break_behavior_tick` 读取黑板与 `BreakNavFollower` 给出 `wish` 位移。除首次寻路外，只有当 `break_ai_nav_version` 与上次记录的版本不同才重新寻路；查询使用当前版本号，因此动态墙 add/remove 之后旧路径立即失效（`break_ai_path_is_current` 返回假）并在下一次 tick 用新版本重建。`BREAK_NAV_FAILED`（目标不可达）被容忍，不中断该 tick。

### 动态墙

当 `target_in_sight` 成立且尚未加墙时，`break_ai_obstacle_add` 加入矩形 (1, 1, 4, 2)，同时 `physics_body_create` 建立对应的静态刚体（质量 0）。追踪者的位置进入 x < 1.0 且 z < 1.5 的区域后，`break_ai_obstacle_remove` 移除障碍，nav 版本再次递增，路径重新可查询，追踪者继续接近目标。移除只撤掉导航障碍，刚体保留，视线遮挡仍以它为准。

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

每个固定步的顺序变为：`break_kernel_tick` → `break_flow_runtime_tick` → `app_tick_vehicle` → 用户未乘车时 `core_app_simulation_tick` → `app_tick_chaser` → `physics_step` → 乘车时把用户放到底盘位置 → `event=vehicle` trace → `break_kernel_area_tick` → 其余 trace。`physics_step` 由此第一次进入应用的固定步。

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
- `save` 用 `break_kernel_inventory_count` 记录数量，trace 多一个 `items=<u>` 字段。
- `load` 只允许补足：当前数量大于保存数量时以 `REJECTED` 拒绝；小于时用 `break_kernel_inventory_add` 补差。这一步和其他校验一样，在修改用户与追踪者之前完成。
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

`scene_state_save`（物理体等场景运行态）没有写进 checkpoint（车辆和布娃娃后来已补上），动态墙由 runtime 标志重建，后经确认与直跑等价；错误 Actor generation 与 GPU/record 资源 staging 失败两项失败矩阵用例未做。

### 补充：失效 Actor 行与 render 资源 staging 失败（2026-11-14）

上面两项失败矩阵用例已补到 `test_core_app_lifecycle_roundtrip`（矩阵代码在 `engine/tests/test_core_app_lifecycle.cmake` 的 `SIM_MODE=roundtrip` 分支）。实现未改。

| 用例 | 改动 | 期望 |
|---|---|---|
| stale_actor | `actors_1.sidecar` 中 `2 User` 改为 `99 User` | `load_rejected stage=actor` |
| render_resource | `scene_1.bscn` RESOURCES chunk 第一个资源的 guid 写成 0 | `load_rejected stage=render` |

两项同样同步更新 manifest 的长度和哈希，并沿用矩阵的其余断言：没有 `event=load`、没有构建 generation 2、当前关卡在 tick 39 → 41 继续前进、运行正常停止。

- “错误 Actor generation”的含义：sidecar 每行只有“实体序号 类名”，不带 generation。实体的代际由 `parse_sidecar`（`engine/src/kernel/break_kernel_level.c`）按候选关卡自己的 world 核对，序号越界或槽位不是存活实体就返回 `BREAK_KERNEL_STALE`；`break_kernel_adopt` 再用 `world_entity_exists` 检查一次。用例让 sidecar 指向本代 world 不存在的实体。
- render staging：BSCN 没有内容校验和，guid 为 0 的资源能通过解码，由 `core_app_render_stage_level` 以 `INVALID` 拒绝。这是 record 资源表的 staging；GPU 上传失败走的是 commit 阶段的 `gpu_upload`，属于运行时致命错误，不在失败矩阵内。
- 变异：
  - `core_app_render_stage_level` 不检查 `id == 0`，render_resource 判红。
  - 只去掉 `parse_sidecar` 的越界和存活判定时没有判红，因为 `break_kernel_adopt` 的存活检查仍会拒绝，这是等价变异。两处判定同时去掉后，stale_actor 判红：拒绝阶段变成 `stage=state`。
- `test_core_app_lifecycle` 12/12 通过；ASan+UBSan 与 TSan 树的 `test_core_app_` 中，非 GPU 用例全部通过。GPU 用例（`test_core_app_gpu_*`，标签 `gpu`）在 sanitizer 树中失败，与本节无关：ASan 报 swapchain 重建路径 `vk_retire_push`（`engine/src/rhi/rhi_vk.c`）分配的退役记录泄漏，TSan 报的竞争位于 Vulkan validation layer 内部线程。这两项作为下一项单独处理。

### 补充：GPU 用例在 sanitizer 树中通过（2026-11-14）

上一段记下的 sanitizer 树 GPU 失败已经处理，计划见 `docs/superpowers/plans/2026-11-14-core-app-gpu-sanitizer-lanes.md`。

- 引擎缺陷：`vk_retire_collect_budget`（`engine/src/rhi/rhi_vk.c`）在 `retired_count == 0` 时提前返回，所以帧内回收把计数降到 0 以后，`vk_shutdown` 的全量回收不会释放 `retired` 数组本身。启动时 `rhi_set_vsync` 重建 swapchain 会分配这个数组（64 项，1536 字节），之后每次运行都泄漏。修复后，全量回收在数组仍存在时继续执行，并释放数组。
- 第三方 suppression 只加在 `test_core_app_gpu_*` 上，并且只在 Linux 的 sanitizer 树中生效：
  - ASan：`VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1`，`LSAN_OPTIONS` 指向 `engine/tests/core_app_gpu_lsan.supp`（`libnvidia-glcore.so`、`libnvidia-glsi.so`、`libEGL_nvidia.so`），并设置 `fast_unwind_on_malloc=0`。OpenGL 走 glvnd 时，NVIDIA 的 GL 模块在退出前已被卸载，泄漏栈顶只显示 unknown module；改用慢速回溯后才能回溯到仍处于映射状态的 `libEGL_nvidia.so` 帧。
  - TSan：`TSAN_OPTIONS` 指向 `engine/tests/core_app_gpu_tsan.supp`，只匹配 `libVkLayer_khronos_validation.so`。报告中的竞争发生在 validation layer 自己的队列线程与 `DestroyFence` 之间。Debug 构建默认打开 validation。
- 验证：ASan+UBSan 与 TSan 树的 GPU 用例都是 3/3，trace 中有 `result=ready` 和 `frames=64 screenshots=1`。撤掉引擎修复后，Vulkan 用例在 suppression 下仍判红，报告 `vk_retire_push` 的 1536 字节泄漏，说明 suppression 没有掩盖引擎代码。
- 边界：CI 仍用 `-LE "graphics|fuzz|gpu"` 排除这些用例，本节的证据只来自本机（Intel UHD TGL GT1 + NVIDIA 驱动并存）。

### 补充：车辆物理运行态进 checkpoint（2026-11-14）

上面“仍未做”中的场景物理运行态，本节补上车辆部分，计划见 `docs/superpowers/plans/2026-11-14-core-app-checkpoint-vehicle-state.md`。`main.c` 的 `scene_state_save` 保存相机、太阳角，以及按槽位顺序排列的全部刚体，和分代 checkpoint 不是同一种格式，这里不直接复用。

- 发现：之前读档会按场景重建车辆，底盘回到出生点，乘坐状态丢失。用户在车里时存档，读档后 `occupied=0`，轨迹和不中断的运行不一致。
- `runtime_<g>.bin` 升到版本 3，正文从 68 字节扩到 124 字节，偏移 68 起依次是：底盘 position（12 字节）、velocity（12）、orientation（16，4×f32）、angular_velocity（12）、rest_frames（4）。标志新增三位：`VEHICLE_OCCUPIED`（16）、`VEHICLE_SLEEPING`（32）、`INTERACT_DOWN`（64）。保存交互键的按住状态，是因为不保存时，存档那一刻按着的 E 会在读档后再触发一次上车或下车。控制量（throttle/steer/brake）不保存，因为 `vehicle_step` 每个 tick 都按输入重写。版本 2 的文件按版本号拒绝。
- 解码要求车辆字段全部是有限值，orientation 的长度平方必须在 (0.5, 2) 之内；不满足返回 `INVALID`，结果为 `load_rejected stage=checkpoint`。`app_apply_state` 解析底盘句柄（失效返回 STALE，结果为 `stage=state`），写回位置（同时写 `step_start_position`）、速度、朝向、角速度、静止帧数和休眠标志，以及 `vehicle.occupied` 和 `interact_was_down`。`state_hash` 覆盖新的正文，roundtrip 的哈希相等断言因此也覆盖车辆字段。
- 验证（`test_core_app_lifecycle_roundtrip`）：
  - 新增 `vehicle_continuation`：同一输入序列（走到车旁、tick 40 上车、tick 43 按住 W、tick 60 存档）跑两次，一次直跑到 tick 99，一次在 tick 61 读档后跑到 tick 100。读档后 tick 61 为 `occupied=1 throttle=1`，之后 40 个 tick 的 vehicle 行和 user 行与直跑逐字一致。改代码前这三条断言都判红。
  - 失败矩阵新增 `vehicle_nan`（底盘 position.x 写入 NaN）和 `vehicle_quat`（orientation 全写 0），两项都同步更新 manifest，期望 `stage=checkpoint`。
- 变异：不写回 occupied、不写回 position、去掉 position 的有限值检查、去掉四元数长度检查，四处都判红，恢复后 `cmp` 确认与备份逐字节一致。
- lifecycle 在 ASan+UBSan 与 TSan 树中各 12/12，normal 树非 fuzz 全量 400/400。
- 仍未做：布娃娃骨骼刚体不保存（R 键状态不进存档，读档后布娃娃为未激活）。动态墙仍由标志重建。（布娃娃已在下一小节补上；动态墙经确认按标志重建即等价，见“动态墙读档等价性”小节。）

### 补充：布娃娃运行态进 checkpoint（2026-11-14）

计划见 `docs/superpowers/plans/2026-11-14-core-app-checkpoint-ragdoll-state.md`。

- 发现：版本 3 不保存布娃娃。R 键激活后存档，读档得到的是未激活的链条，IK 立即重新求解，轨迹与不中断的运行不同。
- `runtime_<g>.bin` 升到版本 4，正文从 124 字节扩到 496 字节，文件总长 512 字节。新标志 `RAGDOLL_ACTIVE`（128）。偏移 124 起是 3 个关节的 pose 矩阵（每个 64 字节，按列主序 `c*16 + r*4` 排列）；偏移 316 + j×60 起是第 j 块骨骼刚体：position（+0）、velocity（+12）、orientation（+24，4×f32）、angular_velocity（+40）、rest_frames（+52）、body_flags（+56，bit0 = sleeping）。版本 3 的文件按版本号拒绝。
- 保存：`app_tick_ragdoll` 在布娃娃激活前把链条的 `current_pose` 复制到 `CoreLevel.ragdoll_pose`；`app_capture_state` 在激活时置标志，要求骨骼数为 3，复制 pose，并经 `physics_body_resolve` 逐块复制刚体状态。未激活时整段写 0。
- 解码：pose 和所有向量分量必须是有限值；四元数长度平方在 (0.5, 2) 之内的检查只在 `RAGDOLL_ACTIVE` 置位时做，所以未激活时的全零段能通过；`body_flags` 大于 1 时拒绝。失败一律 `INVALID`，结果为 `load_rejected stage=checkpoint`。
- 读档：`app_apply_state` 在车辆写回之后执行。候选关卡里布娃娃已激活时返回 `REJECTED`；否则把 pose 写回链条和 `ragdoll_pose`，调用 `ragdoll_activate`（失败返回 `FAILED`），再逐块写回 position（同时写 `step_start_position`）、velocity、orientation、angular_velocity、rest_frames 和 sleeping。`state_hash` 覆盖新正文。
- 不保存的部分：骨骼之间的约束没有 warm-start 冲量，由 `ragdoll_activate` 在读档时重建即可；contact 字段每个物理步都会清零。
- 验证（`test_core_app_lifecycle_roundtrip`）：
  - 新增 `ragdoll_continuation`：tick 10 按 R、tick 30 存档，一次直跑到 tick 69，一次 tick 31 读档后跑到 tick 70，两次都在存档后再按一次 R 收起布娃娃。读档后 tick 31 为 `ragdoll=1 solved=0 owned=1`，tick 30..69 与 31..70 的 ik、user、ragdoll 行逐字一致。改代码前判红。
  - 失败矩阵新增 `ragdoll_nan`（第二个 pose 矩阵的平移 x 写入 NaN）和 `ragdoll_quat`（置 `RAGDOLL_ACTIVE`，三块骨骼四元数全写 0），期望 `stage=checkpoint`。vehicle 两项的长度检查同步改为 512。
- 变异：不写回 pose、不写回骨骼刚体、去掉四元数长度检查、去掉 pose 有限值检查，四处都判红，恢复后 `cmp` 确认与备份逐字节一致。
- lifecycle 在 ASan+UBSan 与 TSan 树中各 12/12，normal 树非 fuzz 全量 400/400。
- 动态墙的处理见下一小节。

### 补充：动态墙读档等价性（2026-11-14）

计划见 `docs/superpowers/plans/2026-11-14-core-app-checkpoint-wall-state.md`。

- 结论：墙不需要额外的存档字段。墙由一个导航障碍和一个质量为 0 的静态刚体组成，刚体没有速度、休眠或接触累积，位置和形状固定；障碍只有在场和已移除两种状态。`WALL_ADDED`/`WALL_REMOVED` 两个标志就是它的全部运行态，`app_apply_state` 按标志以相同参数执行 add/remove，结果与 tick 路径一致。`runtime_<g>.bin` 保持版本 4。
- 验证（`test_core_app_lifecycle_roundtrip` 新增 `wall_continuation`）：
  - 原 continuation 在 tick 91 读档，此时墙已在场；断言读档后 tick 92 为 `nav_version=2 path_current=1`。
  - 新增一对运行，tick 380 存档，此时墙已加入并已移除（tick 379 为 `nav_version=3`）。一次直跑到 tick 439，一次在 tick 381 读档后跑到 tick 440，两次的 60 条 sim 行和 60 条 user 行逐字一致。
- 变异：让 `app_apply_state` 跳过加墙、跳过移墙，两处都判红；恢复后 `cmp` 确认与备份逐字节一致。

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
<tick> audio-device [<device name, rest of line>]   # 2026-11-19 补充，见文末「运行中切换播放设备」
<tick> level [asset-root]
```

tick 是不带符号的十进制，范围 1..1048576，且不得回退；`quit` 恰好出现一次，并且必须是最后一个事件。上限为 64 KiB、4096 个事件、每行 511 字节、路径 255 字节。任何违规都使整份文件 `INVALID`，输出结构清空，不执行已解析的前缀。事件数组在堆上按需扩容，不再使用约 1 MB 的栈对象。

`level [asset-root]` 是对计划文法的补充：计划中的 `load`/`load-from` 表示 Task 8 的 checkpoint 恢复，资产关卡加载需要一个独立命令。三个正式 scenario 由 baker 按新文法重新生成。当前 `core_app_run` 只执行 `key`、`touch`、`pad`、`level`、`unload` 和 `quit`，并要求 `fixed-dt-ns` 等于 16666667；`flow`、`save`、`load`、`screenshot` 等由 Task 5、8、11 接入，在此之前出现时以 `stage=scenario` 拒绝，不会被静默忽略。

### 输入与模拟

`core_app_input` 拥有自己的 `InputState` 和 `InputExtended`，`InputExtended` 初始化后不再复制。每个 tick 先推进按键边沿和触摸帧状态，再应用该 tick 的事件；对外只导出 POD 帧，包含按键、触摸点、手势和 haptic 状态。

`core_app_simulation` 在创建时绑定 9 个动作：forward、back、left、right、jump、interact、fire、save、load。键盘使用 W/S/A/D、空格、E、鼠标左键、F5、F9，手柄使用左摇杆和按钮。每个 tick 依次执行：`break_kernel_eval_actions`；把活动触摸映射成虚拟摇杆（纵向位移除以 0.1 作为 forward，横向作为 strafe，钳制到 [-1, 1]，release/cancel 的触摸不计入）；`break_kernel_move_wish`（yaw 为 0）；`character_update(CORE_APP_FIXED_DT)`；最后把位置写回 `BREAK_KERNEL_POSITION_COMPONENT`。模拟结果不读取墙钟。`core_app_accumulator_advance` 每次最多产生 8 个 substep，超出的时间计入 `dropped_ns`，不改变步长；由于应用目前只支持 fixed-step，它暂时只有单元测试。

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

启动有三种模式：`core_app_audio_start`（record，写 trace）、`core_app_audio_start_null`（无 trace sink，drain 只消费状态）、`core_app_audio_start_device`。设备路径（Task 9 slice 2 起）打开默认播放设备；只打开到 miniaudio Null 后端或没有设备时如实报告 `event=audio mode=device result=unavailable backend=<名称> fallback=null|none`：普通 `--audio=device` 降级为 null 泵并计数 `device_fallbacks`，`--audio=device --require-device` 返回 `BREAK_RUNTIME_UNAVAILABLE` 并让进程以退出码 77 结束。`core_app_run` 的 drain 调用点统一走 `app_audio_drain`，按已启动模式分派 record/null。

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

256 条满队列的进程级压力用例。设备的打开、探测播放与关闭已在 Task 9 slice 2 补上，命令队列驱动设备已在 slice 3 补上，关卡播放事件已在 slice 4 补上，device 模式的独立音频 owner 线程已在 slice 5 补上。record/null 路径的证据是单元与真实进程 trace，不是听感验证。

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

### 认证传输（2026-11-15）

只有 `CORE_APP_ENABLE_NETWORK=ON` 且 `BREAK_ENABLE_SNOWFLAKE=ON` 时，CMake 才编译 `apps/core_app/core_app_net_transport.c`、链接 `break_net` 并定义 `CORE_APP_NET_TRANSPORT=1`。这条路径要求 `BREAK_ENABLE_CRYPTO=ON`（AUTH-v2 需要 HMAC），否则配置期 `FATAL_ERROR`。其他组合定义 `CORE_APP_NET_TRANSPORT=0`，离线 `core_app` 不含任何 `break_net_`/`break_session_`/`snow_`/`Snow*` 符号（`test_core_app_network_offline` 用 `nm` 检查）。

命令行（仅 transport 构建接受，help 也只在该构建列出）：

```text
core_app --network --bind HOST:PORT --tls-cert PATH --tls-key PATH --psk-env NAME --port-file PATH
         [--net-poll-ms 0..100]
```

- 缺任一项退出 2：`--network requires --bind, --tls-cert, --tls-key, --psk-env and --port-file`；
- 给了这些参数但没有 `--network`：`network options require --network`；
- `HOST:PORT` 非法：主机必须是点分十进制 IPv4，`localhost:0` 这类非数字主机和 65536 这类端口都退出 2，`invalid --bind value`；
- `--net-poll-ms` 是每 tick 等待 reactor 的毫秒数，默认 0（不阻塞 tick）。只接受 1 到 3 位十进制数字且值不超过 100（`00` 合法，`0001` 和 `101` 不合法），否则退出 2：`--net-poll-ms requires 0..100`；
- PSK 只从 `--psk-env` 指定的环境变量读取，必须是 64 位 hex，不写入 trace；全零 key 视为未设置，启动以 `stage=psk` 拒绝；key id 固定为 `coreapp1`；
- 监听成功后用 `platform_atomic_writer_*` 把实际端口写入 `--port-file`（`--bind 127.0.0.1:0` 因此可用于测试），进程退出时删除该文件。

运行时：`CoreAppNetworkHooks` 把传输对象挂到 `core_app` 生命周期。`network_start` 阶段位于 audio 之后、coordinator 之前；每 tick 在 audio listener 之后最多处理 64 个 reactor 事件（等待 `--net-poll-ms`，最多 8 个连接），并只向已认证会话发送 snapshot（user `flags=1`，chaser `flags=2`）。`SEND_DRAINED` 只是流控通知，直接释放，不交给会话层。连接打开 3000 ms 内仍未认证即关闭，计入 `auth_timeouts`，空闲的 TLS 对端因此不能占满连接槽。期限按单调时钟（`time_microseconds()`，POSIX 上为 `CLOCK_MONOTONIC`，Windows 上为 QPC）计算，与 tick 无关：record 车道默认不限速，1500 tick 只需约 0.05 s，按 tick 计的期限（原先 180 tick）在这种情况下只有几毫秒。

发送前的防护：只有 reactor 事件队列为空时才发送，并且目标槽必须满足：未在关闭中、会话状态为 `AUTHENTICATED`、会话层报告的 session id 等于该槽认证时记录的 id。connection key 随传输槽复用，队列里还没处理的 close 事件对应的 key 可能已经分配给一个未认证的新连接；这两条检查防止新连接收到旧会话的 snapshot。这一竞态没有进程级复现，只靠代码审查和上述条件保证。收到的 snapshot 只进入 `core_app_snapshot_admit` 并改变计数，decode 失败或带尾部字节计为 `decode_failed`；网络输入从不写回仿真。

停止顺序：stop admission → stop producers → drain → destroy（drain 每轮等待 1 ms，最多 8 轮）。`app_rollback` 在 audio 之前调用这四个钩子。`net_destroy` 幂等：只有已经进入监听状态时才写一行 `event=network_stats`；只要 reactor 存在就调用 stop，不管启动失败停在哪个阶段（已启动的 reactor 上 `break_net_reactor_destroy` 不做任何事，acceptor 也不能在 reactor 仍持有它时销毁）。stop 成功后依次销毁 session manager、reactor、acceptor。stop 超时时写 `event=network result=stop_timeout`，有意保留 reactor 和 acceptor（泄漏），置 `leaked` 并返回 `TIMEOUT`；之后再调用 destroy 直接返回 `TIMEOUT`，不再触碰仍被泄漏 reactor 持有的 acceptor。`core_app_net_transport_free` 在 destroy 返回非 `OK` 时不释放内存（运行中的 reactor 或全局 auth 回调仍指向它）。随后清除 auth 回调；清除失败时保留 PSK（全局回调仍指向它）并返回 `FAILED`，成功时清零 PSK。最后删除 port file。

启动阶段依次为 `psk`、`reactor`、`bind`、`tls`、`acceptor`、`auth`、`listen`、`port_file`。任一阶段失败写 `event=network result=rejected stage=<阶段>`，走同一清理路径，进程退出 2。

消息注册表新增 `BREAK_NET_MESSAGE_ID_CORE_SNAPSHOT = 0x4001`（v1..1，`AUTHENTICATED` phase，`IDEMPOTENT`，payload 上限 `32 + 64 × 24` 字节）。transport 用 `#error`/`_Static_assert` 锁定 id 和上限与 `core_app_network.h` 一致。

SIGPIPE：transport 构建在 `--network` 生效时调用 `signal(SIGPIPE, SIG_IGN)`，对端关闭后的写入返回 `EPIPE`，由会话层计数，进程不会被杀。离线进程不改信号处理。修复前 loopback 约 1/7 失败（`server=SIGPIPE`），修复后连续 15 次通过。

`event=network_stats` 字段按顺序为：`opened`、`closed`、`refused`（停止接入后或无空槽时被拒的连接）、`authenticated`、`snapshots_sent`、`send_overloads`、`send_closed`、`outbox_overloads`（tick 侧 outbox 满）、`auth_timeouts`、`decode_failed`、`admitted`、`rejected_unknown`、`rejected_unauthenticated`、`rejected_schema`、`rejected_stale`，以及会话层的 `session_applied`、`session_phase_rejected`、`session_invalid`、`session_handler_failed`。

### 测试

- `test_core_app_network_offline`（所有构建）：同一 scenario 离线跑两次，SHA256 相同；trace 无 network 行；无 transport 时 `nm` 扫描为 0 个网络符号。`nm` 读不了的二进制格式（`_core_app_nm_capable` 为假，即 MSVC/Clang 的 Windows PE）走 UNVERIFIED 并以 77 跳过，与其他 nm 合同一致。此前 Windows 车道在这里报 `nm output lacks core_app_run`。
- `test_core_app_network_loopback`（transport 构建且非 WIN32；客户端使用 POSIX socket）：真实 `core_app`（`--net-poll-ms 16`）与 `test_core_app_net_client` 并发运行，scenario 为 `engine/tests/data/core_app_network_loopback.scenario`（1500 tick）。客户端场景：
  - A：认证后收到 snapshot，再发旧 generation、伪造 schema、伪造位置加 16 字节尾部，以及一条可被 admit 的伪造位置包，会话不断、帧号继续增加；
  - B：不认证就发 snapshot，永远收不到 snapshot，连接保持打开；
  - C：未知 id `0x7777`，连接被关闭；
  - D：错误 PSK，连接被关闭；
  - E：只完成 TLS、不发 AUTH，认证期限到后被服务器关闭；
  - F：第二个认证对端到最后仍能收到 snapshot，证明 C/D/E 的关闭是服务器针对单个连接的动作，不是整体停止。
  - A 发完敌意包后，要等到帧号比第一帧至少大 60 的 snapshot 才关闭。原先只等下一帧，outbox 里可能已有敌意包到达前生成的帧，A 关闭时服务器还没读到最后那条可 admit 的包，`close()` 引发的 RST 会把它丢掉：连跑 9 次出现 1 次 `admitted=0`。

  驱动脚本断言 trace 不含 secret、`authenticated==2`、`opened>=6`、`snapshots_sent>=2`、`auth_timeouts>=1`、`admitted>=1`、各拒绝计数至少 1、`session_handler_failed>=2`，退出后不残留 port file，并且过滤 network 行后与离线 trace 逐字节相同，snapshot generation 等于 `level_loaded` generation。本机一次运行的 stats：`opened=6 closed=6 authenticated=2 snapshots_sent=6 auth_timeouts=1 decode_failed=1 admitted=1 rejected_schema=1 rejected_stale=1 session_applied=15 session_phase_rejected=1 session_invalid=0 session_handler_failed=2`。
- `test_core_app_network_start_failure`（transport 构建且非 WIN32）：缺 PSK 环境变量与全零 PSK（`stage=psk`）、坏证书（`stage=tls`）、port file 指向不存在的目录（`stage=port_file`）。每项断言 rc=2、无 Sanitizer 输出、无 `listening` 与 `network_stats` 行、不留 port file。
- `test_core_app_network_late_auth`（注册条件同 loopback）：服务器 `--net-poll-ms 1`，scenario `engine/tests/data/core_app_network_late_auth.scenario`（6000 tick），客户端以 `late-auth` 模式只运行场景 G：完成 TLS 后静默 1 s 再发 AUTH，必须收到 snapshot；驱动脚本断言 `authenticated==1`、`auth_timeouts==0`。按 tick 计期限时 RED（`g_receives_snapshot_after_late_auth` FAIL），改为毫秒期限后通过。
- `test_core_app_target_contract` 覆盖 `--net-poll-ms 101` 与 `0001` 的错误文本，并要求 `00` 不被当作 CLI 错误（参数解析接受后，因缺少 `--scenario`/`--fixed-step` 在 config 阶段以 `stage=config unsupported lifecycle configuration` 退出 2）。
- 变异：去掉“只发给已认证会话”检查 → B/C/D 三项 FAIL；把对端 snapshot 位置写进 user → `network input changed the simulation`；`net_destroy` 只在 started/listening 时调用 stop → ASan 树 start_failure 的 port_file 用例 rc=1 并报 LeakSanitizer 泄漏。三处恢复后 `cmp` 一致。评审修复前的 RED：loopback 因 `--net-poll-ms` 未知报 `unknown or malformed argument`，start_failure 报 `zero_psk: rc=0, want 2`。

### 边界

- OVERLOAD 在进程级触发不到：reactor 队列容量 256 且每 tick 都会 drain，只由 outbox 单元测试（容量 8 满后 OVER_LIMIT 且计数）和 `network_stats` 可观察性覆盖。
- CI 当前没有开启 `CORE_APP_ENABLE_NETWORK` + `BREAK_ENABLE_SNOWFLAKE` 的 job，loopback 只在本地 Fedora 网络树、ASan 树和 TSan 树验证。
- 之前典型运行中 `session_invalid` 为 16，来源是交给会话层的 `SEND_DRAINED` 事件；现在跳过该事件，值为 0。

### 物理状态哈希报告（2026-11-15）

`CoreAppNetworkHooks.tick` 新增参数 `u64 physics_hash`，由 `app_network_publish` 传入 `physics_state_hash(level->physics)`（`physics_step` 之后）。transport 持有一个 `PhysicsSyncTracker`：每个 producing tick 先 `physics_sync_record(tick, hash)`；tick 不递增导致记录被拒时（例如关卡重载后 tick 重新开始）重置 tracker 和 desync 标记再记录。随后编码一份 16 字节报告，在 snapshot 之后、同样等事件队列为空时，发给每个 `net_slot_sendable` 的槽（id `0x4002`，v1）。未认证连接收不到报告。

对端发来的 `0x4002` 由 `net_on_physics_report` 处理：`physics_sync_decode_report` 失败计 `physics_decode_failed` 并返回 false（会话层记为 handler_failed，连接不关闭）；否则 `physics_sync_check` 的结果计入 `physics_matched` / `physics_desynced` / `physics_unknown`。第一次 DESYNC 写一行 `COREAPPTRACE version=1 event=network_physics_sync result=desync tick=N`，之后的 DESYNC 只计数。处理函数不持有关卡指针，报告不会修改物理世界；修正包 `0x4003` 的发送还没接入。

`event=network_stats` 在原有字段之后追加 `physics_reports_sent`、`physics_matched`、`physics_desynced`、`physics_unknown`、`physics_decode_failed`。

测试：loopback 场景 A 在发完敌意 snapshot 后读取下一份报告（客户端按 PSYN/tick/hash 布局手工解码，不依赖 `physics_sync.c`），原样回发一次（MATCH），翻转哈希后发两次（DESYNC），再发 15 字节载荷（解码失败）。驱动脚本断言 `physics_reports_sent>=2`、`physics_matched>=1`、`physics_desynced>=2`、`physics_decode_failed>=1`，desync 行恰好一行且 tick 等于客户端收到的报告 tick，离线 trace 对比仍逐字节相同（`event=network` 前缀的行被过滤）。本机一次运行：`physics_reports_sent=64 physics_matched=1 physics_desynced=1 physics_unknown=0 physics_decode_failed=1`（重复 DESYNC 测试加入前）。9 项变异全部被捕获。验证树为 `build-core-app-net`（Snowflake + CRYPTO + `CORE_APP_ENABLE_NETWORK=ON`，全量 414/414）；CI 仍没有开启该组合的 job。
- 发送前的 key 复用防护（队列为空才发送、session id 必须一致）没有进程级复现。
- PSK 环境变量在 start 读取后立即从进程环境删除，见下方「PSK 读取后删除环境变量」。

### 补充：PSK 读取后删除环境变量（2026-11-15）

- 新函数 `core_app_net_take_secret_env(name, out, size)` 位于 `core_app_network`（带单元测试的库），替换 transport 内原来的 `net_hex_decode(getenv(...))`。它要求值恰好是 `2*size` 位 hex（大小写均可）且不全为 0，解码后无论成功与否都调用 `unsetenv`（Windows 为 `_putenv_s(name, "")`）删除该变量；失败时用 volatile 写把 `out` 清零。之后的 `getenv` 和子进程都看不到这个密钥。
- 时机是 `net_start` 的 `psk` 阶段，也就是读取的同时删除，而不是等到退出。这样即使进程异常终止，运行期间也不会再有代码读到它。
- 边界：内核在 exec 时给出的初始环境块（`/proc/<pid>/environ`）不会被改写；同用户的其他进程仍能从那里读到启动时的值。这和 editor `--remote` 推荐用文件传 PSK 的理由相同。
- 测试：`test_core_app_network` 新增 2 项（共 12 项），覆盖正确值解码并删除变量、再次调用失败，以及全零、63 位、65 位、非 hex 四种坏值都返回失败、删除变量并清零输出，参数为空时失败。先链接 RED（未定义符号），再 GREEN。变异：只在成功时删除变量，坏值用例判红（`getenv(...) == NULL is false`），恢复后 `cmp` 一致。network 树 `test_core_app_network*` 5/5（含 loopback、late_auth、start_failure），ASan 树 3/3，libFuzzer network 1/1，normal 树 `-L core_app` 非 GPU 31/31。

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

fuzz corpus 不落盘、无 libFuzzer 结构感知；`fuzz_core_app_network` 未做（snapshot 编解码已有确定性单元测试覆盖边界，但没有对应变异 fuzzer；已在 2026-11-14 补上，见下一小节）。Task 11 的真实 GPU 像素证据不在本步。

### 补充：`fuzz_core_app_network`（2026-11-14）

新增 `engine/tests/fuzz_core_app_network.c`，只链接 `core_app_network m`，参数为迭代次数和 seed，同一 seed 输出逐位一致。

每轮先用 `core_app_snapshot_build` 生成 0..64 个实体的快照（坐标有 1/4 概率取 NaN、±Inf、非规格化数或 -0 的位型），用 `core_app_snapshot_encode` 编码，再以 7/8 概率做五类变异之一：翻转任意字节；截断到任意长度；改写偏移 28 的 count（0、1、63、64、65、`UINT32_MAX` 或随机值）；改写 magic、version 或 header_bytes；尾部追加最多 64 个随机字节。变异后的字节复制到恰好 `size` 字节的堆块再解码，越界读会被 ASan 抓到。

断言：

- 解码结果与独立的参考模型一致：size<32 → TRUNCATED；magic 不符 → BAD_MAGIC；version≠1 或 header_bytes≠32 → BAD_VERSION；count>64 → OVER_LIMIT；size<32+24·count → TRUNCATED；其余 → OK。
- 拒绝时 `out` 与调用前填入的 0xA5 哨兵逐字节相同。`core_app_network.h` 的 decode 注释已写明这一约定。
- 接受时重新编码的字节等于 payload 的前 `needed` 字节（尾部垃圾被忽略，不被解释）。
- 接受的快照送入随机初始化的 inbox（authenticated、admission id、peer schema 各自随机）调用 1..4 次 `core_app_snapshot_admit`，结果与参考模型（unauth → unknown message → schema → stale → admitted）一致，五个计数之和等于调用次数。
- 再推入长期存在的 outbox，与影子环形队列比较：容量 8，`enqueued+dropped` 等于推入次数，弹出按 FIFO 返回 frame_id。

注册为 `fuzz_core_app_network_smoke`（2000 次，seed 41，`fuzz` 标签）。CI 的 ASan fuzz 列表和两个 “Build fuzz targets” 步骤都已加入该目标；`test_wayland_ci_migration_contract` 现在要求三个 core_app fuzz 目标在 ci.yml 中各出现至少 3 次，改 ci.yml 前该契约 RED。

证据：

- seed 41：`accepted=1050 rejected=950 admitted=138 truncated=399 bad_magic=115 bad_version=182 over_limit=254 enqueued=1018 dropped=32`；50000 次 seed 7 通过。
- ASan+UBSan 树 20000 次无报告。
- 三处变异都判红：去掉 decode 的 `size < needed` 检查（第 0 轮）；去掉 header_bytes 检查（第 31 轮）；admit 跳过 generation 检查（第 12 轮）。
- normal 树全量非 fuzz 400 项通过。

仍未做：没有落盘 corpus，也没有 libFuzzer 覆盖率引导；fuzzer 不经过真实 socket 或 `break_net` 会话层。（落盘 corpus 已在下一小节补上。）

### 补充：`fuzz_core_app_network` 落盘 corpus（2026-11-14）

计划见 `docs/superpowers/plans/2026-11-14-fuzz-core-app-network-corpus.md`。

- 仓库新增 `engine/tests/data/core_app_network_corpus/`，17 个 `.bin` 文件，每个是一份 snapshot 线上字节。文件名前缀是期望的解码结果：`ok`（空、1 个、64 个实体、NaN/Inf/非规格化坐标、尾部多 16 字节）、`truncated`（0 字节、头少 1 字节、实体少 1 字节、满载少一个实体、count=1 但没有实体）、`bad_magic`、`bad_version`（version 0、version 2、header_bytes 31）、`over_limit`（count 65、count `UINT32_MAX`）。
- `fuzz_core_app_network --emit-corpus <dir>` 用固定构造重新生成这些文件，不用随机数；重新生成的结果与仓库中的文件逐字节相同。
- `fuzz_core_app_network --replay <file>...` 逐个检查：解码结果等于文件名前缀，也等于参考模型；拒绝时 `out` 保持 0xA5 哨兵；接受时重新编码等于 payload 前 `needed` 字节，`schema_hash` 等于当前布局的哈希（布局变化后必须重新生成 corpus），并且认证 inbox 在 generation 相同时 ADMITTED、不同时 STALE_LEVEL。前缀未知或五种结果有任何一种缺失都失败，避免目录为空时假通过。
- CMake 在 `ENGINE_BUILD_FUZZ_SMOKE=ON` 下用 `file(GLOB CONFIGURE_DEPENDS)` 把文件作为参数注册 `fuzz_core_app_network_corpus`（`fuzz` 标签）。目录通过参数传入，不依赖 dirent，Windows 通道也能跑。CI 已构建该 target 并运行 `-L fuzz`，ci.yml 不需要改。

证据：

- RED：目录为空时测试失败（`corpus has no 'ok' file`）。
- GREEN：`replayed=17 ok=5 truncated=5 bad_magic=2 bad_version=3 over_limit=2`。
- 变异：去掉 decode 的 `size < needed` 检查，`truncated-count_without_entities` 判红；去掉 header_bytes 检查，`bad_version-header_bytes` 判红。恢复后通过，源文件与备份逐字节一致。
- normal 树：非 fuzz 400/400（4 个既有 SKIP），fuzz 11/11。ASan+UBSan 树：三个 core_app fuzz target 共 4 项全部通过，无报告。

仍未做：libFuzzer 覆盖率引导与结构感知变异；checkpoint 和 scenario fuzzer 还没有落盘 corpus（scenario 已在下一小节补上）。

### 补充：`fuzz_core_app_scenario` 落盘 corpus 与 pad 范围修复（2026-11-14）

计划见 `docs/superpowers/plans/2026-11-14-fuzz-core-app-scenario-corpus.md`。

- 仓库新增 `engine/tests/data/core_app_scenario_corpus/`，40 个 `.scenario` 文件，前缀 `accept-`（10 个）或 `reject-`（30 个）写明期望的解析结果。覆盖：全部命令、CRLF、注释与空行、无结尾换行、tick 上限 1048576、同 tick 多事件、u64 最大 seed；恰好 4096 事件与 4097 事件；恰好 511 字节行与 512 字节行；超过 64 KiB；NUL 与控制字节；quit 之后的事件、重复 quit、缺 quit；tick 为 0、超限、倒退；`..` 与绝对路径；touch 越界、NaN、未知 phase；pad 序号与轴越界；flow key 溢出与值越界；key 状态与键名非法；多余字段与未知命令。
- `fuzz_core_app_scenario --emit-corpus <dir>` 用固定文本重新生成，结果与仓库文件逐字节相同。`--replay <file>...` 经真实 `core_app_scenario_load` 读文件：reject 必须返回 INVALID 且 `event_count == 0`、`events == NULL`；accept 必须返回 OK，事件数 1..4096，最后一个事件是 QUIT，tick 单调不减且在 1..1048576 内。前缀未知或缺少任一前缀都失败。注册为 `fuzz_core_app_scenario_corpus`（`fuzz` 标签）。`.gitattributes` 把该目录标为 binary，CRLF 与控制字节样例在任何平台检出都不变。
- **真实缺陷**：`decimal_u64` 的溢出判断 `value > (limit - digit) / 10` 在 `digit > limit` 时无符号下溢，因此单个数字超过上限也被接受：`pad 4 …` 与 `pad 0 6 …` 原本解析成功，违反上方文法 `pad <0-3> <axis 0-5>`。`core_app_input.c` 在使用前还会按 `INPUT_MAX_PADS`/`INPUT_MAX_AXES` 再检查，所以没有越界访问，但应用会把一份不合法的文档当成合法。修复为先判断 `digit > limit`。`test_core_app_runtime` 新增 `scenario_rejects_pad_index_and_axis_beyond_limit`，修复前判红，修复后 49/49。

证据：

- RED：目录为空时测试失败；生成后 `reject-pad_axis` 判红，暴露上述缺陷。GREEN：`replayed=40 accept=10 reject=30`。
- 变异（每次恢复后源文件与备份逐字节一致）：撤销 digit 修复，`reject-pad_axis` 判红；允许 quit 之后的事件，`reject-event_after_quit` 判红；去掉 4096 事件上限，`reject-over_max_events` 判红；允许 `..` 路径，`reject-parent_path` 判红。
- normal 树：非 fuzz 400/400，fuzz 12/12。ASan+UBSan 树：三个 core_app fuzz target 与 `test_core_app_runtime` 共 6 项通过，无报告。TSan 树：`test_core_app_runtime` 49/49，无报告。

仍未做：checkpoint fuzzer 的落盘 corpus；libFuzzer 覆盖率引导。（checkpoint corpus 已在下一小节补上。）

### 补充：`fuzz_core_app_checkpoint` 落盘 corpus（2026-11-14）

计划见 `docs/superpowers/plans/2026-11-14-fuzz-core-app-checkpoint-corpus.md`。

- 仓库新增 `engine/tests/data/core_app_checkpoint_corpus/`，39 个 `.core` 文件，每个是一份 `manifest.core` 字节。文件名前缀写明期望结果：
  - `ok-`（4 个）：基本 4 条记录、generation 为 u64 最大值、RUNTIME 排在第一条、只有 RUNTIME 一条。probe 与 find(RUNTIME) 都返回 OK，find 返回的 generation、kind、size、hash、name 与样例字节中的 RUNTIME 记录一致。
  - `nofind-`（3 个）：缺 RUNTIME、两条记录都是 RUNTIME kind、RUNTIME 记录改成未知 kind 99。probe 返回 OK，find(RUNTIME) 返回 INVALID。
  - `invalid-`（28 个）：magic、version、header_bytes、size 字段（含高 32 位）、保留字、generation 为 0、count 为 0、count 与长度不符、截断一字节、name_len 为 0、偏短、偏长、名字填充非 0、kind 为 0、payload 哈希错、payload 大小错、payload 文件不存在、名字以 `.` 结尾、含 `..`、`/`、`\`、空格、名字为 `MANIFEST.CORE`、大小写不同的重名、完全相同的重名、不足 40 字节、空文件。probe 与 find 都返回 INVALID。
  - `overload-`（4 个）：count 为 17、name_len 为 64、payload 大小超过 64 MiB、文件超过 1448 字节。probe 与 find 都返回 OVERLOAD。
- `fuzz_core_app_checkpoint --emit-corpus <dir>` 用测试内独立的编码器生成样例，不调用生产 writer，所以 corpus 固定的是磁盘格式本身。重新生成的结果与仓库文件逐字节相同。
- `fuzz_core_app_checkpoint --replay <file>...` 在临时目录写入 fuzzer 固定的 4 个 payload（scene、flow、actors、runtime），把每个样例复制成 `manifest.core` 后调用真实的 `core_app_checkpoint_probe` 与 `core_app_checkpoint_find`。全部样例跑完后检查 4 个 payload 字节未变，再删除临时目录。前缀未知或四种前缀缺任何一种都失败。注册为 `fuzz_core_app_checkpoint_corpus`（`fuzz` 标签）。`.gitattributes` 把该目录标为 binary。
- 随机变异模式结束时现在会删除 `valid`、`sentinel` 和根临时目录。之前只删 `manifest.core`，每次运行都在构建目录里留下一个 `fuzz_core_app_ckpt_<pid>` 目录。

证据：

- RED：目录为空时测试失败。GREEN：`replayed=39 ok=4 nofind=3 invalid=28 overload=4`。
- 变异（每次恢复后源文件与备份逐字节一致）：去掉 `duplicate_name` 检查，第一版 corpus 没有判红。原因是大小写不同的重名样例让第二条记录指向不存在的文件，在 payload 校验处就被拒绝了。补上 `invalid-name_duplicate_exact`（同一 payload 以同名列出两次）后判红。去掉保留字检查，`invalid-reserved_word` 判红；find 不拒绝重复 kind，`nofind-duplicate_runtime_kind` 判红；去掉 payload 哈希比较，`invalid-payload_hash` 判红。
- normal 树：非 fuzz 400/400，fuzz 13/13。ASan+UBSan 树：三个 core_app fuzz target 共 6 项通过，无报告。

仍未做：libFuzzer 覆盖率引导。

### 补充：libFuzzer 覆盖率引导（2026-11-15）

- `engine/tests/fuzz_core_app_network.c` 把逐 payload 的检查提取为 `check_payload`：精确大小的堆拷贝、与参考模型比较 decode 结果、拒绝时 `out` 不变、接受时重新编码逐字节一致并以 live/stale 各过一次准入防火墙。`--replay` 与 libFuzzer 入口共用它。
- 以 `CORE_APP_LIBFUZZER=1` 编译时文件导出 `LLVMFuzzerTestOneInput`（不含 `main`），任何检查失败即 `abort()`。新选项 `ENGINE_BUILD_LIBFUZZER`（默认 OFF，仅 Clang）构建 `libfuzz_core_app_network`，注册 `libfuzz_core_app_network_run`（标签 `fuzz;libfuzzer`）：`-runs=200000 -seed=1 -max_len=2048`，种子为已提交 corpus，新输入写入构建树。
- CI 新增 `lane-libfuzzer-linux-clang`（clang-18 + ASan/UBSan），失败时上传 `crash-*`/`leak-*`/`timeout-*`。镜像加装 `libclang-rt-18-dev`，候选 smoke 链接并运行一个空 fuzzer。

证据：

- RED：加入 `-fsanitize=fuzzer` 后链接失败（`multiple definition of main`、`undefined reference to LLVMFuzzerTestOneInput`）。GREEN：本机 clang 22.1.8，种子 16 个文件，`INITED cov: 53 ft: 72`，200000 次约 1 s 完成。
- 变异：把 decode 的截断判断放宽一个实体（`size + CORE_APP_SNAPSHOT_ENTITY_BYTES < needed`），未加载种子 corpus 的 libFuzzer 运行报 `heap-buffer-overflow` 并退出 1。恢复后源文件与备份 `cmp` 一致。
- normal 树 `fuzz_core_app_network_smoke`、`_corpus` 2/2；CI 合同 10/10（`test_ci_image_contract` 与 `test_ci_image_fix2` 的使用方数量改为 11，并要求新车道与镜像 smoke 存在）。

仍未做：结构感知变异（自定义 mutator）。scenario 与 checkpoint 的入口见下两节。

### 补充：scenario 解析器的 libFuzzer 入口与被测模块插桩（2026-11-15）

- `engine/tests/fuzz_core_app_scenario.c` 新增 `check_accepted`：接受的场景必须有事件、不超过 `CORE_APP_SCENARIO_MAX_EVENTS`、`has_quit` 且最后一个事件是 QUIT，tick 在 1..`CORE_APP_SCENARIO_MAX_TICK` 内且不递减。`parse_and_check`（变异运行与 libFuzzer）和 `--replay` 共用它，所以变异运行现在也检查 tick 顺序，之前只检查事件上限。
- `CORE_APP_LIBFUZZER=1` 时导出 `LLVMFuzzerTestOneInput`：把输入拷到精确大小的堆缓冲区（不补 NUL，size 为 0 也分配），检查失败即 `abort()`。目标 `libfuzz_core_app_scenario`，测试 `libfuzz_core_app_scenario_run`：`-runs=200000 -seed=1 -max_len=70000`（大于 64 KiB 上限，能走到大小拒绝路径），种子为 `tests/data/core_app_scenario_corpus`。
- 修正：两个 libFuzzer 目标都把被测源文件直接编进目标（`apps/core_app/scenario.c`、`apps/core_app/core_app_network.c`），不再链接 `core_app_runtime`/`core_app_network` 归档。归档是用普通选项编译的，没有 `-fsanitize=fuzzer` 的覆盖插桩，上一节的 `cov: 53` 只统计了测试文件本身。改后 `nm` 显示两个被测 .o 都含 `__sancov` 符号。
- CI 车道 `lane-libfuzzer-linux-clang` 同时构建两个目标，`ctest -L libfuzzer` 跑两项。

证据：

- RED：只加 CMake 目标时链接失败（`multiple definition of main`、`undefined reference to LLVMFuzzerTestOneInput`）。
- GREEN（clang 22，ASan/UBSan）：scenario `INITED cov: 349 ft: 790`，200000 次后 `cov: 386 ft: 1566`，约 9 s；network 改为插桩后 `INITED cov: 226`，`DONE ft: 716`。
- 变异：把 `scenario.c` 的 tick 递减判断改成恒假（`... && tick == 0u`），libFuzzer 报 `fuzz_core_app_scenario: parse: event 1 has tick 4` 并 `deadly signal`。恢复后 `git diff` 为空，重跑 4/4。
- normal 树与 ASan 树 `fuzz_core_app_{scenario,network}_{smoke,corpus}` 各 4/4；CI 合同 10/10。

仍未做：结构感知变异。checkpoint 的入口见下一节。

### 补充：checkpoint 读取器的 libFuzzer 入口（2026-11-15）

- `engine/tests/fuzz_core_app_checkpoint.c` 新增 `check_manifest`：把输入写成 `manifest.core`，放在四个固定载荷旁边，调用 `core_app_checkpoint_probe` 与 `core_app_checkpoint_find(RUNTIME)`，检查对任何输入都成立的不变量：
  - probe 与 find 只返回 OK、INVALID、OVERLOAD，出现 FAILED（文件 IO 失败）视为缺陷；
  - probe 不是 OK 时，find 返回同一个错误；
  - probe 是 OK 时，find 不会是 OVERLOAD；find 是 INVALID 时，manifest 字节里 RUNTIME 记录必须不是恰好一条（缺失或重复）；
  - find 是 OK 时，manifest 字节里恰好一条 RUNTIME 记录，且 find 返回的 kind、size、hash、name 与 generation 和它一致（沿用 `check_found_record`）。
- `--replay` 复用 `check_manifest`，再按文件名前缀（ok/nofind/invalid/overload）精确比较结果，因此回放现在也检查上面的不变量。
- `CORE_APP_LIBFUZZER=1` 时导出 `LLVMFuzzerTestOneInput`：首个输入时在工作目录建 `fuzz_core_app_ckpt_<pid>/libfuzz/` 并写入四个载荷，之后复用；每个输入拷到精确大小的堆缓冲区再检查，失败即 `abort()`；每 256 个输入重读一次载荷，读取器若改写载荷即 `abort()`；`atexit` 删除临时目录。
- 目标 `libfuzz_core_app_checkpoint` 把 `apps/core_app/core_app_checkpoint.c`、`src/platform/platform_fs.c`、`src/core/log.c` 直接编进目标（都带覆盖插桩，后两者只依赖 libc）。测试 `libfuzz_core_app_checkpoint_run`：`-runs=50000 -seed=1 -max_len=2048`（大于 1448 字节的 manifest 上限，能走到 OVERLOAD），种子为 `tests/data/core_app_checkpoint_corpus` 的 39 个文件，`WORKING_DIRECTORY` 为构建树。CI 车道 `lane-libfuzzer-linux-clang` 同时构建三个目标。

证据：

- RED：只加 CMake 目标时链接失败（`multiple definition of main`、`undefined reference to LLVMFuzzerTestOneInput`）。
- GREEN（clang 22，ASan/UBSan）：50000 次 `DONE cov: 338 ft: 776`，约 2 s；结束后构建树不残留 `fuzz_core_app_ckpt_*`。另跑 400000 次，RSS 稳定在约 412 MB，没有持续增长。
- 变异：让 `core_app_checkpoint_find` 不再拒绝重复 kind（`if (found && kind == 0u)`），libFuzzer 报 `find OK with 2 RUNTIME records` 并 `deadly signal`。恢复后 `git diff` 为空。
- libfuzzer 树 `ctest -L libfuzzer` 3/3；normal 与 ASan 树 `fuzz_core_app_{checkpoint,scenario,network}_{smoke,corpus}` 各 6/6；CI 合同 10/10。

仍未做：结构感知变异；载荷文件本身不参与 libFuzzer 变异（固定四个载荷，只变异 manifest）。

### 补充：stop 超时 `leaked` 路径的单元测试（2026-11-15）

- 新增 `test_core_app_net_transport`（仅在 transport 编译且非 Windows 时构建）。它把 `core_app_net_transport.c`、`platform_fs.c`、`time.c` 直接编进测试，并链接 `break_net_test`，以便使用 `break_net_reactor_step_delay_for_test`。
- transport 新增两个只在 `CORE_APP_NET_TRANSPORT_TESTING` 下编译的函数：
  - `core_app_net_transport_reactor_for_test` 返回当前 reactor；
  - `core_app_net_transport_reclaim_for_test` 在阻塞的 step 返回后停止并销毁保留的 reactor 和 acceptor，然后释放 transport。
  正式 `core_app` 不定义这两个宏，`nm` 中 `_for_test` 符号数为 0。生产行为没有改动，stop 超时仍为 1000 ms。
- 测试流程：用 Snowflake fixture 证书在 `127.0.0.1:0` 启动 transport，给下一次 step 注入 1500 ms 延迟，在另一线程调用 `break_net_reactor_step`，主线程调 `destroy`。断言如下：
  - 返回 `TIMEOUT`；
  - trace 中有 `event=network result=stop_timeout`；
  - port file 已删除；
  - reactor 指针保留且 `stop_pending`；
  - 第二次 `destroy` 仍返回 `TIMEOUT`；
  - `core_app_net_transport_free` 不释放内存。
  step 线程 join 后，由 reclaim 清理，因此 ASan 不报泄漏。
- 并发安全：`net_destroy` 在 stop 超时后才销毁 session manager。正在运行的 step 只调用 `break_net_drain_outbound` 和 `SnowNetThreadStep`，不回调 manager（manager 只在 `net_pump` 中被读取，而 `net_pump` 运行在调用 destroy 的同一线程）。TSan 树运行该测试没有报告。

证据：

- RED：只加测试与声明时链接失败（`undefined reference to core_app_net_transport_reactor_for_test`）。
- GREEN：network 树 1/1，约 1.5 s；ASan 与 TSan 树各 1/1。
- 变异各自判红，恢复后 `cmp` 一致：不置 `leaked`；改掉 `stop_timeout` trace；超时时保留 port file；超时返回 `OK`。
- network 树 `core_app|break_net|break_session` 41/41（3 项按设计 Skipped）；normal 树 CI 合同、release config 与 `test_core_app_network` 12/12。

## Core App Task 11（slice 1）：真实窗口设备通道、截图写盘与截图事件（2026-11-14）

### 变化

新增 `engine/apps/core_app/core_app_gpu.c/.h`，只链接进 `core_app` 可执行文件，`core_app_runtime` 的七个源文件契约不变。record lane 完全不触碰它，所以无显示器的机器仍是合法的 record 宿主。

- `--render=vulkan|opengl` 现在被接受（`--render=record` 仍是默认）。`--screenshot` 只在 GPU lane 允许，record lane 传它会明确退出 2。
- `core_app_gpu_create` 走 `platform_create` → 平台原生窗口/surface → `rhi_device_create`，读 `rhi_device_get_info` 与 `rhi_runtime_active_backend` 记录真实 `backend`/`device`。设备或窗口缺失时返回 `UNAVAILABLE`，trace 写 `event=gpu result=unavailable`；`--require-device` 时进程以环境不可用收场而不是假装成功。
- 每帧在 `app_publish_world` 之后经 `core_app_gpu_render` 提交：`rhi_frame_begin` → 清屏 → `world_presenter_submit` → `rhi_frame_end` →（可选）`rhi_screenshot` → `rhi_present`。截图把 RGBA8 明确翻成顶层向下并做 R/B 直接写入（RHI 已是 RGBA 顺序，因此只翻行序），写标准 P6 PPM；路径含 `%u` 时替换为帧号，否则只允许单次截图。
- 场景 `screenshot` 事件现在被接受：GPU lane 下一次渲染写图；无设备时写 `event=screenshot_rejected stage=device` 而不让运行失败。
- 关闭顺序：GPU 在 `runtime_stopped` 之前 `rhi_device_idle` → 销毁 presenter → 销毁设备 → 销毁平台，并写 `event=gpu result=stopped frames=N screenshots=M`；`app_rollback` 同样先销毁 GPU。

### 本机真实设备证据（Intel UHD Graphics TGL GT1，Vulkan 1.4）

```
COREAPPTRACE version=1 event=gpu result=ready backend=vulkan device=Intel(R) UHD Graphics (TGL GT1) width=320 height=240
COREAPPTRACE version=1 event=gpu backend=vulkan device=Intel(R) UHD Graphics (TGL GT1) frame=1 generation=1 draws=8 instances=3
...
COREAPPTRACE version=1 event=gpu result=stopped frames=N screenshots=1
```

截图落到 320×240 PPM（230415 字节），真实设备创建、帧提交、截图读回、PPM 写盘均成功。

## Core App Task 11（slice 2）：真实网格上传、双后端对照与像素证据（2026-11-14）

### 变化

- 关卡提交时，GPU lane 为本关卡每个可见网格调用 `core_app_gpu_upload_mesh`：场景顶点布局（pos3+normal3+uv2，32 字节）恰好等于 `MeshVertex`，因此按 stride 直接拷入 `MeshBuffer` 上传；句柄写入 `WorldObject.gpu/draw`，并记录到关卡自己的 `gpu_meshes[]`。植被原型同样上传 `scene->mesh_geometry[0]`，否则实例化绘制会绑定无效索引缓冲。
- 设备句柄归关卡所有：`CoreLevel` 保存 `mesh_device`，销毁关卡时先释放网格；回滚与成功路径都调整为先销毁/卸载关卡再销毁设备，避免使用已销毁设备的句柄。
- record-only 校验（`draws[i].gpu.vertex.generation == 关卡代际`）在 GPU lane 不再适用，因为真实句柄里没有这个字段；GPU lane 跳过该检查，证据改由 `event=gpu` 提供。
- GPU lane 提交的是对象-only 的 snapshot 副本（`instance_count=0`、`batch_count=0`）：record snapshot 里的植被批次携带的是 record 假句柄，真实后端会在实例化绘制上撞到无效缓冲（OpenGL 直接 SIGSEGV）。
- 创建设备后立即 `rhi_set_vsync(device, false)`。应用自己按固定步长驱动循环；再让交换链节流会让主机循环阻塞在 present 上（实测 GL 卡在第 4 帧）。
- 截图必须发生在 `rhi_frame_begin` 与 `rhi_frame_end` 之间，因此提前分配读回缓冲，清屏/绘制后立即 `rhi_screenshot`，再 `rhi_frame_end`、写 PPM、`rhi_present`。

### 验证

新增 `test_core_app_gpu_vulkan` 与 `test_core_app_gpu_opengl`（标签 `gpu`，`RUN_SERIAL`，超时 420s）。它们只在构建实际选择了对应后端时注册（`ENGINE_RHI_BACKEND_EFFECTIVE` 为该后端或 `ENGINE_RHI_MULTI_BACKEND_ACTIVE`），并在 CI 的 headless 套件里通过 `-LE "graphics|fuzz|gpu"` 排除——没有 GPU 的 runner 不应把“设备不存在”测成失败。本地用 `ctest -L gpu` 显式运行。每个用例：真实 `core_app --render=<backend> --require-device`，断言 trace 有 `event=gpu result=ready backend=<b> device=...`、存在 `draws>0` 的帧、`event=gpu result=stopped frames=N screenshots=1`，再用 Python 解析 PPM 头与像素数，要求除最频繁颜色外还有其它像素。设备/显示器缺失时 `--require-device` 退出 77，用例报 UNAVAILABLE 跳过而不是判 PASS；设备已创建后的失败一律 FAIL。`test_core_app_gpu_opengl` 还与该次构建中 vulkan 的截图比较绘制采样数，作为跨后端不变量。

本机实测（Intel UHD TGL GT1）：

| 后端 | device | 帧 | PPM | 采样 |
|---|---|---|---|---|
| vulkan | Intel(R) UHD Graphics (TGL GT1) | 64 | 921615 B | 背景 (13,15,20)，drawn_samples=101 |
| opengl | Mesa Intel(R) UHD Graphics (TGL GT1) | 64 | 921615 B | 同上，两后端一致 |

640×480 全帧统计：两后端都是 3797 个非背景像素、同背景色。Vulkan validation（`BREAK_VK_VALIDATION=1`）VUID 计数为 0（此前 slice 1 有两条未绑定缓冲告警）。

变异：把 GPU snapshot 的 `draw_count` 置 0，`test_core_app_gpu_vulkan` 以 “no frame with draws was rendered” 变红；恢复后转绿。

### 仍未做

`scene_state_save`、GPU 侧真实骨架蒙皮绘制（创建期降级已在 slice 3 补上）、以及“用户/追踪者/植被各自语义像素”的分项断言。当前证据是“设备真实、几何真实到达目标、两后端一致”，不是逐对象影像回归。

## Core App Task 13（slice 1）：独立评审发现的缺陷与修复（2026-11-14）

一次独立评审（只读、逐提交）指出两处真实缺陷，均已修复并加回归测试：

1. **顶点步长错位**。场景网格契约是 32 字节（pos3+normal3+uv2），而渲染器的 `MeshVertex` 是 36 字节（多 `material`）。slice 2 的上传按 32 字节拷入 `MeshVertex` 数组，导致第二个顶点起全部错位。修复：新增纯函数 `core_app_mesh_convert_vertices`（`core_app_mesh.c/.h`），逐字段转换并把 `material` 置 0；`test_core_app_mesh` 三个用例覆盖字段顺序、容量溢出不写、空源。变异“步长改用 `sizeof(MeshVertex)`”被第一个用例杀死。修复后同一场景的绘制像素从 3797 变为 6240，`draws` 从 8 变为 6。
2. **stream 对象仍带 record 假句柄**。`rhi_handle_valid` 只检查 `generation != 0`，所以 record 假句柄能通过校验并在真实后端绑定错误缓冲。修复：GPU lane 构造对象-only snapshot 时剔除 `stream` 绘制，`draws` 由 8 降为 6。

同时修正两处对外契约：

- GPU 设备不可用（`stage=gpu_start` 返回 `UNAVAILABLE`）此前仍以退出码 2 收场，现与音频设备一致走 77；真实设备已创建后的失败仍一律退出 2。变异“截图恒失败”被 `test_core_app_gpu_vulkan` 判为 FAIL（exited 2），证明失败没有被误报成 skip。
- `core_app_gpu.h` 不再引用 `rhi_runtime.h`；后端名改从 `RHIDeviceInfo.backend` 读取。原写法在单后端嵌套构建里产生 `undefined reference to rhi_runtime_active_backend`，使 `test_core_app_contract_compat` 与 `test_core_app_ctest_config_contract` 失败。

本轮修复后：`test_core_app_mesh` 3/3、GPU 两用例通过、`test_core_app_gpu`/`naming`/`target` 契约 5/5；全量含 GPU 405/405。

## Core App Task 9 补充：满队列多生产者压测（2026-11-14）

Task 9 原边界写的“256 条满队列的进程级压测未做”，本节补上进程内多线程部分。`core_app_audio.c` 未改。

- 用例 `audio_owner_thread_survives_concurrent_full_queue_producers`（`test_core_app_runtime`）：FAKE 后端加 owner 线程；4 个生产者线程各以自己的 generation（1..4）入队 4096 条 LISTENER，遇到 `OVERLOAD` 就计数、`platform_thread_yield` 后重试同一条；主线程同时调用 2000 次不等待的 `core_app_audio_drain_device(&audio, 0)`。
- 断言：
  - `device_listener_updates == 16384`，命令不丢也不重复执行。
  - `audio.overloads` 等于各生产者看到的 OVERLOAD 次数之和。
  - `device_calls_off_owner == 0`。
  - trace 中 listener 行恰好 16384 行，sequence 依次为 1..16384（FIFO，序号在锁内分配），每个 generation 各 4096 行。
- 本机 20 次运行中 OVERLOAD 次数为 53432–114181；绑到单核（`taskset -c 0`）时为 57。两种情况下队列都被真正打满。
- 变异：满队列时只计一半 overload，判红（计数不等）；owner 模式 enqueue 不加锁，判红（命令丢失）；owner 出队的 head/count 更新移到锁外，判红（命令丢失）。
- TSan 树连跑 10 次零报告，ASan+UBSan 树 48/48。

同一提交修复 `audio_owner_thread_keeps_the_stale_stop_check` 的时序依赖。CI run 43570966229 的 Windows MinGW 任务报 `stale_commands != 1u`。原用例先入队 STOP(1)，再入队抢占槽位的 PLAY_3D(9)。STOP 在入队时就解析出槽位；如果 owner 在 PLAY_3D 入队前先消费了 STOP，槽位仍属于第 1 代，STOP 是合法的，结果取决于调度。本机在两次入队之间插入 20000 次 yield 可稳定复现。修复后先入队 PLAY_3D(9) 再入队 STOP(1)：STOP 入队时第 1 代已经没有槽位，无论 owner 何时消费都判为 stale。“STOP 先解析槽位、随后槽位被抢占”的情形仍由同步 drain 的 `audio_device_stale_stop_never_reaches_a_reclaimed_slot` 覆盖。插入 yield 后新顺序 48/48；去掉 `sound_admit` 的代际判定后该用例仍判红；本机连跑 300 次无失败。

仍未做：经过 `core_app` 进程、真实设备的满队列压测；应用每 tick 产生的命令数远低于 256，没有自然路径能撞满队列。

## Core App Task 9（slice 6）：按事件选择声音资源（2026-11-14）

### 交付

- `core_app_audio.h` 新增 `CoreAppAudioSound`，取值为 `NONE`、`CHASER`、`ITEM`，另有 `CORE_APP_AUDIO_SOUND_COUNT`。`CoreAppAudioCommand` 和 `CoreAppAudioSlot` 各增加一个 `sound` 字段。
- 新接口 `core_app_audio_enqueue_sound(audio, kind, generation, sound, position)`：
  - `LISTENER` 只能配 `NONE`，`PLAY_3D`、`POSITION`、`STOP` 只能配 `CHASER` 或 `ITEM`。
  - 不合规的组合返回 `INVALID`，不入队，也不占用 sequence。
  - 原有的 `enqueue` 和 `enqueue_at` 签名不变：LISTENER 用 `NONE`，其余命令用 `CHASER`。
- 声源按 `(generation, sound)` 寻址。`PLAY_3D` 为该组合占用一个槽位，`POSITION` 和 `STOP` 只作用于同一组合的槽位。因此同一关卡可以同时播放追踪者循环声和拾取声，`STOP item` 不会停掉追踪者声源。
- `sound_path` 改为 `sound_paths[3]`：`CHASER` 播放 `<root>/tone.wav`，`ITEM` 播放 `<root>/chime.wav`，`NONE` 为空。设备探测音仍用 `tone.wav`。
- 设备每次成功播放都按 sound 计数，记在 `device_plays_by_sound[]`。`result=stopped` 行在 `evictions=` 之后、`owner_thread=` 之前加入 ` item_plays=N`。
- trace 行末尾加 ` sound=none|chaser|item`。
- 应用侧：
  - 背包物品数增加时（Flow 延迟 30 tick 后，在 tick 61 加物品），在用户当前位置入队一次 `PLAY_3D sound=item`，并设置 `CoreLevel.item_sound_live`。
  - 卸载和切关统一走 `app_audio_stop_level`。它对 chaser 声源始终发一条 `STOP`（没有槽位的 STOP 会按 stale 丢弃）；item 声源只在已播放时发 `STOP`。随后按实际入队条数 drain。
- 资产：baker 新增 `bake_chime`，确定性生成 44100 Hz、单声道、PCM16 的方波，共 2205 个样本（50 ms），周期 40 个样本，振幅 ±8192。正式资产从 11 个增加到 12 个，`.gitattributes` 和 `.gitignore` 都登记了 `chime.wav binary`。

### 验证

- RED：`test_core_app_runtime` 新增 3 个用例（双声源互不干扰、sound 与 kind 不匹配时拒绝、设备按事件播放对应文件），实现前编译失败。资产测试新增 `chime_wav_is_canonical_44100_hz_mono_pcm16`。formal、naming、checkout、baker、compat 五个契约都改为 12 个资产。lifecycle 要求 script_walk 恰好一条 `source=2 sound=item` 的 PLAY_3D，script_discard 在拾取前卸载，所以 item 计数为 0。
- GREEN：normal 树全量中，除提交前必然失败的两个 HEAD archive 契约外全部通过。真实 PulseAudio 设备的 trace 为 `plays=2 moves=49 stops=2 item_plays=1`（场景改为 tick 80 才卸载，因此会经过 tick 61 的拾取）。TSan 下 `test_core_app_runtime` 零报告。
- 变异检查：ITEM 改用 `tone.wav`、claim 只按 generation 匹配、拾取时不入队，三处变异都被测试判红。

### 边界

- 仍然没有听感验证，进程测试只证明设备打开并播放了被选中的文件。
- 拾取声不随用户移动：只发 PLAY_3D，不发 POSITION。
- slice 2–5 中“声源固定使用 `tone.wav`”和“11 个正式资产”的描述是当时状态，保持原文不改。

## Core App Task 9（slice 5）：音频 owner 线程（2026-11-14）

### 交付

- `--audio=device` 接上真实设备后，`core_app_audio_start_device_backend` 启动一个独立的音频 owner 线程。启动之后的每一次 `AudioSystem` 调用（listener、play_3d、位置、停止、探测等待与 `audio_system_destroy`）都在这个线程上执行。
- 线程、mutex 和两个条件变量放在 `core_app_audio.c` 私有的堆块 `CoreAppAudioOwner` 里，`CoreAppAudio` 只多一个不透明的 `owner` 指针，头文件不引入平台线程头。线程原语来自 `engine/src/core/platform_thread.h`。
- 生产侧（应用主线程）：`core_app_audio_enqueue_at` 在锁内做原有的准入、溢出和槽位分配，然后唤醒 owner。`core_app_audio_drain_device` 在 owned 模式下只唤醒 owner 并返回 owner 的第一个错误，帧不等待设备。
- owner 循环：锁内弹出一条命令，做代际检查和 STOP 的槽位回收；锁外调用设备并写 trace 行。只有收到停止请求且队列为空才退出，退出时执行原有的关闭步骤，并写 `result=stopped` 行。出错后剩余命令只出队，不再调用设备。
- `core_app_audio_join` 设置停止标志、唤醒并 join 线程；`core_app_audio_destroy` 返回 owner 的关闭结果并释放堆块。`core_app.c` 未改：协调器的停止顺序（停准入、停生产、关队列、drain、join、destroy）已满足要求。
- 新增 `core_app_audio_flush`（等待队列清空且没有正在处理的命令；无 owner 时有积压返回 TIMEOUT）和 `core_app_audio_start_system_owned`。`core_app_audio_start_system` 保持同步，原有 FAKE 单测不变。
- 证据计数 `device_calls_on_owner`/`device_calls_off_owner`；`result=stopped` 行末尾追加 ` owner_thread=0|1`（关闭步骤是否在 owner 线程上执行）。

### 边界

- record 与 null 模式仍由应用主线程同步 drain，record trace 内容与顺序不变。
- device 模式下 trace 行由 owner 线程写入，与主线程写的帧行之间的交错顺序不再固定；进程测试只断言计数与 `owner_thread=1`，不断言行序。
- 声源仍固定为 `tone.wav`，没有按事件选择资源，也没有听感验证。

### 验证

- RED：`test_core_app_runtime` 新增 5 个用例在实现前编译失败（缺 `core_app_audio_start_system_owned`、`core_app_audio_flush`、`owner` 与计数字段）；`test_core_app_audio_device.cmake` 新增 `owner_thread=1` 断言。
- GREEN：`test_core_app_runtime` 44/44，连跑 20 次无失败；真实设备（PulseAudio）trace：`listener_updates=58 plays=1 moves=10 stops=1 evictions=0 owner_thread=1`；normal 树全量 400/400。
- TSan 树 `test_core_app_runtime` 连跑 10 次零报告，`core_app|audio` 中只有本机 GPU 用例失败（Mesa/VVL，与本改动无关）；ASan 树 `core_app|audio` 同样只有 3 个 GPU 用例失败。

## Core App Task 9（slice 4）：关卡声音事件（2026-11-14）

### 变化

- `CoreLevel` 增加 `sound_live`。`app_tick_level` 处理第一个 Area enter 时，以追踪者当前位置入队一条 `PLAY_3D`（本关卡 generation），并置 `sound_live`。同一关卡再次进入 Area 不再开新声源。
- `sound_live` 之后的每个 tick，在处理 Area enter 之前入队 `POSITION`，位置为追踪者在本 tick 移动后的位置，所以声源跟随追踪者。
- 声源的结束沿用已有路径：卸载与切关时入队本 generation 的 `STOP`，它按代际找到同一个槽位并停止该声源。新关卡从 `sound_live=false` 开始，不会继承旧声源。
- 帧末 drain 的预算从 1 改为 `CORE_APP_AUDIO_QUEUE_CAPACITY`（256）。一个 tick 现在最多产生 LISTENER、POSITION、PLAY_3D 三条命令，预算 1 会留下积压并让 drain 返回 TIMEOUT。
- record 模式 trace 新增 `event=audio kind=play_3d|position …` 行；位置本身仍不写入 trace，相同场景的 record 输出仍逐字节确定。

### 第三方修复

ASan/TSan 在 `test_audio` 的 `play_3d_source_reports_failure_as_zero` 中报告 miniaudio 0.11.25 的 heap-use-after-free：`ma_resource_manager_data_buffer_node_acquire` 在失败路径 `ma_free` 节点后又读 `pDataBufferNode->isDataOwnedByResourceManager`。已把上游 0.11.26 对 `done:` 块的修复（先读出该字段，释放后置 NULL）回港到 `engine/external/miniaudio.h`，其余代码仍为 0.11.25。

### 边界

`AudioSystem` 仍由应用主线程持有，没有独立 owner 线程（slice 5 起 device 模式改由独立 owner 线程持有）。声源固定使用 `tone.wav`，没有按事件选择资源，也没有听感验证。

### 验证

- RED：`test_core_app_lifecycle_script_flow` 新增断言在实现前失败（`script_discard: stop=-1`，record trace 中没有 play_3d/position）。
- GREEN：
  - script_walk：tick 30 的 Flow post 之后恰好 1 条 `play_3d generation=1 source=1`，之后 150 条 `position`（tick 31..180）；
  - script_discard：10 条 `position`（tick 31..40），1 条 `stop generation=1 source=1`，且在 `level_unloaded generation=1` 之前；generation 2 没有任何声音命令。
- `test_core_app_audio_device` 场景改为前进 40 tick、卸载、重载、60 tick 退出，要求 `plays=1`、`moves>=5`、`stops>=1`、`listener_updates>=40`。本机 PulseAudio 实测 `listener_updates=58 plays=1 moves=10 stops=1`。
- `test_audio` 在 ASan 树中由 heap-use-after-free 变为通过。

## Core App Task 9（slice 3）：命令队列驱动音频设备（2026-11-14）

### 变化

- `CoreAppAudioCommand` 增加 `position`。新入口 `core_app_audio_enqueue_at(audio, kind, generation, position)`：LISTENER 用作听者位置，PLAY_3D/POSITION 用作声源位置，STOP 忽略。旧的 `core_app_audio_enqueue` 以原点调用它。
- 新增 `core_app_audio_drain_device`：每条命令先过与 record 相同的代际检查，通过后再调用设备：
  - LISTENER → `audio_set_listener`；
  - PLAY_3D → `audio_play_3d_source(asset_root/tone.wav, position)`，句柄存入 `device_sources[slot-1]`；
  - POSITION → `audio_source_set_position`；
  - STOP → `audio_stop` 并清空句柄。
  代际不符的 POSITION/STOP 只计 `stale_commands`，从不触达设备。
- 槽位满后 PLAY_3D 复用槽位时，先 `audio_stop` 被挤出的旧句柄并计 `device_evictions`，避免设备上残留无人可寻址的声源。
- 引擎新增 `audio_play_3d_source`：与 `audio_play_3d` 相同，但返回句柄（失败返回 0）。`audio_play_3d` 改为调用它并丢弃句柄，现有调用方不变。
- 新增 `core_app_audio_start_system`：接管一个已创建的 `AudioSystem`，不播放探测音，单测用它注入 FAKE 系统。
- `core_app_run` 的 `app_audio_drain` 在设备模式且系统存在时走 `drain_device`。每个固定 tick 的 LISTENER 现在带用户位置（`core_app_simulation_user_position`）。位置不写入 trace，record 运行的 trace 保持逐字节不变。
- 关闭时的 `result=stopped` 行增加 `failures listener_updates plays moves stops evictions` 计数。销毁 `AudioSystem` 会释放所有仍在槽位里的声源。

### 边界

slice 3 时关卡只产生 LISTENER 与卸载时的 STOP，真实进程里 `plays=0`；slice 4（上一节）起 Area enter 产生 PLAY_3D/POSITION。PLAY_3D/POSITION/STOP/挤出路径的设备证据来自 FAKE 系统单测。`AudioSystem` 仍由应用主线程持有，没有独立 owner 线程（slice 5 起 device 模式改由独立 owner 线程持有）。

### 验证

- `test_audio` 24/24（+2）：`audio_play_3d_source` 返回可停止的句柄；路径缺失或参数为 NULL 时返回 0。
- `test_core_app_runtime` 39/39（+4）：
  - FAKE 系统上 listener 位置、play/move/stop 计数与句柄一一对应；
  - 槽位复用时挤出源被停止；
  - 槽位在 STOP 排出前被新代际回收时，旧 STOP 不停新源；
  - 无设备时 `drain_device` 返回 INVALID。
- `test_core_app_audio_device` 额外要求 30 tick 的运行里 `listener_updates >= 20` 且 `failures == 0`。本机 PulseAudio 实测 `listener_updates=29 failures=0`。
- 变异（均已恢复）：
  - 不停挤出源 → `device_evictions` 断言变红；
  - 代际不符仍触达设备 → 回收槽位用例 `device_stops != 0` 变红；
  - listener 不调设备 → 位置断言变红；
  - `app_audio_drain` 不走设备分支 → 进程级用例以 “drove the device listener only 0 times” 变红。
- 恢复后全量 408/408。

## Core App Task 9（slice 2）：真实音频播放设备（2026-11-14）

### 变化

- 引擎 `audio.h` 新增两个只读查询：`audio_system_backend_name`（miniaudio 实际打开的后端名，如 `PulseAudio`、`ALSA`、`WASAPI`、`Null`；FAKE 系统报 `fake`，NULL 指针报 `none`）与 `audio_system_device_name`（播放设备名，无设备时写 `none` 并返回 false）。
- `core_app_audio_start_device(audio, trace, require_device, asset_root)` 用 `AUDIO_BACKEND_DEFAULT` 打开默认播放设备。后端名是 `Null`、`fake` 或 `none` 时不算设备：销毁系统，写 `result=unavailable backend=<名称> fallback=null|none`，required 时返回 UNAVAILABLE（进程退出 77），optional 时降级为 null 泵。
- 打开到真实后端后，以 0.25 音量播放一次 `asset_root/tone.wav` 作为探测源，写 `result=ready backend=<后端> device=<设备> probe_source=<id>`。`tone.wav` 无法播放时返回 FAILED，不降级。
- `core_app_audio_destroy`（停机最后一步，在 join 之后）最多轮询 400×5 ms 等探测音结束，记录游标秒数，停止源并销毁 `AudioSystem`，写 `result=stopped backend=<后端> probe_complete=0|1 probe_seconds=<s>`。
- `core_app_audio_start_device_backend` 是同一合同、显式传引擎后端的入口，单测用 NULL/FAKE 确定性地走 unavailable 分支。
- config 校验不再拒绝 `--audio=device --require-device`。

### 边界

- `AudioSystem` 由应用主线程持有，不是独立 owner 线程；miniaudio 自己的设备线程只运行它的混音回调。slice 5 起 device 模式改由独立 owner 线程持有。
- slice 2 时命令队列只更新槽位与 trace；slice 3（下一节）起 drain 会调用 `AudioSystem`。关卡目前仍不产生 PLAY_3D。
- 不包含听感验证。

### 验证

- `test_audio` 22/22：后端名（Null/fake/none）与设备名（Null 设备有名、FAKE 与 NULL 无名）5 个新用例。
- `test_core_app_runtime` 35/35：两条既有设备用例改为强制 Null 后端，并断言 trace 里的 `backend=Null`；新增 FAKE 后端用例断言 `backend=fake fallback=none`。
- 新增 `test_core_app_audio_device`（标签 `audio_device`，`SKIP_RETURN_CODE 77` 与 `SKIP_REGULAR_EXPRESSION "CORE_APP_AUDIO_DEVICE_UNAVAILABLE"`，CI 的 headless 套件经 `-LE` 排除）：以 `--render=record --audio=device --require-device` 运行真实进程，要求非 Null 后端、非空设备名、`probe_seconds > 0`，以及 trace 顺序 ready → `runtime_running` → stopped → `runtime_stopped`。
- 本机实测：`backend=PulseAudio device=内置音频 模拟立体声 probe_complete=1 probe_seconds=0.100`。
- 变异：把 Null 当作设备时 `test_core_app_runtime` 3 条用例变红；探测源播放后立即停止时进程级用例以 “the device never played the probe (cursor 0.000s)” 变红。恢复后全量 408/408。
- cmake < 3.29 的主机（clean-room lane 用 3.28.3）没有 `cmake_language(EXIT)`，脚本因此在跳过点先打印 `CORE_APP_AUDIO_DEVICE_UNAVAILABLE` 再失败；`SKIP_REGULAR_EXPRESSION` 只匹配该 token（产品代码从不输出它），所以“已打开设备后又退出 77”仍是硬失败。用一个桩进程验过两条路径：无设备 → Skipped，ready 后退出 77 → Failed。

## Core App Task 11（slice 3）：创建期 Vulkan→OpenGL 降级（2026-11-14）

### 变化

- `--render=auto` 进入 GPU lane（此前在 config 阶段被拒绝），对应 `CORE_APP_GPU_AUTO`。它调用 `rhi_device_create_compiled`，走编译期链：多后端构建中是 Vulkan 优先、Vulkan 创建失败时以 OpenGL 作最后降级；单后端构建中就是那一个后端。
- `--render=vulkan|opengl` 保持显式语义：调用 `rhi_device_create(backend, ...)`，不会降级。GPU 测试对显式后端额外设置 `BREAK_RHI_BACKEND=<b>` 与 `BREAK_RHI_NO_FALLBACK=1`，并断言 trace 里的 `backend=` 就是请求的那个。
- 设备创建成功后的 device loss 不切换后端，仍按 RHI 合同失败退出。

### 验证

新增 `test_core_app_gpu_fallback`（标签 `gpu`，只在 `ENGINE_RHI_MULTI_BACKEND_ACTIVE` 时注册）：以 `BREAK_RHI_FAIL_VULKAN=1 core_app --render=auto --require-device` 运行，要求：

1. trace 出现 `event=gpu result=ready backend=opengl device=...`；
2. 进程输出含 `RHIEVT {"event":"fallback","backend":"vulkan",...}`，证明链确实先拒绝了 Vulkan；
3. 进程输出含 `RHIEVT {"event":"backend_selected","backend":"opengl","reason":"config-fallback",...}`；
4. 与显式用例相同的 draws、干净关闭与 PPM 像素检查。

本机实测（Intel UHD TGL GT1）：Vulkan entry 被钩子跳过，OpenGL（Mesa）以 `config-fallback` 选中，640×480 捕获、`drawn_samples=172`。

变异：测试侧去掉 `BREAK_RHI_FAIL_VULKAN` 时用例以 “no real opengl device was created for --render=auto” 变红（链直接选中 Vulkan）；实现侧让 `auto` 改走显式 Vulkan 时同样变红。两处恢复后 GPU 三个用例全绿，全量 407/407。

## Core App Task 13（slice 2）：交付门与证据总览（2026-11-14）

### 累计交付

| Task | 内容 | 提交 |
|---|---|---|
| 8 slice 3 | 场景/Flow/Actor 侧车进 checkpoint，失败矩阵 | `12bd170b` |
| 9 | 256 条有界音频命令、代际槽、record/null/device 三模式 | `8bedf0d6` |
| 10 | snapshot 编解码、schema hash、权威防火墙 inbox、有界 outbox | `c632aaf6` |
| 12 | checkpoint/scenario 两个确定性 fuzz target、三棵验证树 | `064f018d` |
| 11 slice 1 | 真实设备通道、帧提交、截图写盘、`screenshot` 事件 | `7d9fe204` |
| 11 slice 2 | 真实网格上传、双后端对照、像素证据 | `5baa2b24` |
| 13 slice 1 | 独立评审：顶点步长与 stream 假句柄修复 | `6f40829e` |
| 13 slice 2 | 设备创建失败报 UNAVAILABLE（CI 暴露） | `392edfa1` |

### 验证矩阵

| 树 | 结果 |
|---|---|
| 普通构建全量（含 GPU lane） | 405/405 |
| ASan + UBSan（core_app + fuzz） | 16/16，无报告 |
| TSan（core_app） | 14/14，无报告 |
| fuzz lane（9 个 smoke） | 9/9 |
| no-tests 真实进程 | 完整生命周期，退出 0 |
| Vulkan validation | VUID 计数 0 |
| 真实设备 | Intel UHD TGL GT1；Vulkan 与 Mesa GL 各 64 帧、背景色与绘制像素一致 |

### 命名

新增的 `core_app_gpu.*`、`core_app_mesh.*`、`core_app_network.*`、两个 fuzz 源、`test_core_app_gpu.cmake`、`test_core_app_mesh.c` 均通过命名契约扫描；标识符、文件名、注释与提交信息都不含命名契约禁止的历史领域词与角色词。

### 仍未做

真实网络传输（TLS/Session/reactor 接线与 loopback 客户端）、关卡声音事件（PLAY_3D/POSITION 的产生方）、GPU 侧骨架蒙皮、逐对象影像回归。创建期降级用例已在 Task 11 slice 3 补上，设备音频的打开/探测/关闭与命令队列驱动设备已在 Task 9 slice 2–3 补上。这些在计划里属于后续 Task，不在本轮交付范围，也未在文档中宣称完成。

以下区域完整保留 Core App Task 1 命名边界及 2026-11-06 至 2026-11-13 已执行设计、命令和证据原文。历史名称只按上述当前映射理解，不把历史命令当作当前可执行路径。

<!-- CORE_APP_HISTORY_BEGIN -->
## Core App Task 1 命名边界（2026-11-11）

本步只迁移尚未进入 master 的 P12 应用及真实引用，应用、target、接口、测试和 11 个正式资产路径统一使用 `core_app`/`CoreApp`/`CORE_APP` 体系；P0–P11 公共 API/ABI 与链接关系不变。数据格式在本步不变：`CORECKPT`、`manifest.core`、`COREAPPTRACE` 和 `core-app-scenario 1` 仅作为既有格式声明/使用暂时保留，Task 2 将一次性迁移并拒绝旧格式，本步不增加双格式兼容路径。命名合同中的上述格式豁免与既有兼容 API、原型字符串、当前工作树/分支名均按精确字面量审计，历史报告不进入扫描。

# Application App 真实集成

日期：2026-11-06

## 当前状态

P12 Task 1 已建立独立 `core_app` 可执行应用及 `core_app_runtime` 静态库，并交付严格命令行入口和真实进程合同测试。完整关卡、输入、模拟、渲染、音频命令、checkpoint 和卸载生命周期尚未实现；当前 `core_app_run()` 对合法配置明确返回 `BREAK_RUNTIME_FAILED`，真实诊断含 `runtime returned FAILED`，进程退出 2，不以空壳返回成功。

## Target 与依赖边界

- `core_app_runtime` 是顶层 C11 静态库，独立于 `ENGINE_BUILD_TESTS`，当前拥有 `apps/core_app/core_app.c`。
- `core_app` 是真实可执行目标，拥有 `apps/core_app/main.c`，链接 `core_app_runtime` 并经 `engine_link_rhi_backend(core_app)` 使用现有 RHI 选择链。
- `core_app_runtime` 显式链接 `engine`、`break_kernel`、`break_ai`、`break_flow`、`break_lua`、`break_kernel_lua` 和 `runtime_core`。
- `engine`、`engine_demo`、`dxx_break` 不链接上述新增集成层。Actor/Lua 适配器使用 `engine/src/kernel/break_kernel_lua.h`；世界呈现 API 位于 `engine/src/renderer/world_presentation.h`。
- `CORE_APP_ENABLE_NETWORK` 默认 `OFF`，CMake 始终把数值 `0` 或 `1` 传给 `core_app` 的同名预处理条件。OFF 时 `--network` 被真实进程拒绝；ON 时该选项可以进入运行时，但本任务仍只返回 `BREAK_RUNTIME_FAILED`，没有网络实现或伪成功。（Task 10 之后：NETWORK=ON 而 SNOWFLAKE=OFF 的构建仍是这一行为；NETWORK 与 SNOWFLAKE 都开启时走认证传输，见 Task 10「认证传输」。）

配置末尾直接检查实际 target 的 `LINK_LIBRARIES`：锁定 `core_app_runtime` 依赖、legacy consumer 的直接链接集合和网络 0/1 定义。多行命令与变量展开因此由实际 target property 验收，而不是只扫描命令首行。合同还实际执行 `ENGINE_BUILD_TESTS=OFF` configure，防止 target 被移入测试作用域。

## 命令行合同

```text
core_app --help
core_app [--render record|auto|vulkan|opengl]
         [--audio record|null|device]
         [--voice off|fake|device] [--voice-null-capture]
         [--assets DIR] [--scenario PATH] [--checkpoint DIR]
         [--trace PATH] [--screenshot PATH]
         [--fixed-step] [--frames N] [--require-device] [--network]
```

带值选项同时接受 `--name value` 和 `--name=value`。默认资产目录为 `assets/core_app`，渲染为 `auto`，音频为 `device`。`--frames` 的精确词法是先满足 `[0-9]+`，再检查数值范围 1..4294967295；前导空白、`+`、负数、0、非数字、空值和溢出均退出 2，并报告 `--frames requires a positive 32-bit integer`。未知参数、非法枚举、缺值和 `--help` 后额外参数也退出 2，并使用各自的 CLI 错误诊断。

`--help` 单独使用退出 0 并输出 `Usage: core_app` 及全部选项。合法默认配置、完整 record 配置和合法 `--frames 4294967295` 都必须到达运行时并报告 `runtime returned FAILED`；不得提前落入 CLI 错误或 `BREAK_RUNTIME_INVALID`。后续真实设备不可用证据码 77 将在对应图形/音频任务接入，本任务不伪造该证据。

## 验证

`test_core_app_target_contract` 检查 configure-time target/链接边界，执行真实 no-tests configure，并启动真实进程覆盖帮助、运行时 FAILED、非法类别、network OFF/ON 和全部数字边界；有能力的 `nm` 扫描还必须找到 `core_app_run`，再排除 `_for_test`/`test_hook`。

nm 扫描仅对非 Windows 或 MinGW 且实际支持 `--defined-only` 的工具/二进制格式启用。无 NM、不支持该参数或无法识别输出格式时返回 77 并标记 `UNVERIFIED`，不输出完整合同 PASS。`test_core_app_nm_missing` 与 `test_core_app_nm_unsupported` 分别锁定这两条路径；CTest 中显示为 Skipped，而不是符号扫描通过。

从工作树根运行：

```bash
cmake -S engine -B build-core-integration-normal \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-core-integration-normal -j3 --target core_app
ctest --test-dir build-core-integration-normal \
  -R '^test_core_app_(target_contract|nm_missing|nm_unsupported)$' \
  --output-on-failure

cmake -S engine -B build-core-integration-no-tests \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=OFF \
  -DENGINE_ENABLE_IPO=OFF -DENGINE_RHI_BACKEND=auto \
  -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-core-integration-no-tests -j3 --target core_app
```

网络开关的 ON 配置可独立验证，但仍不提供网络：

```bash
cmake -S engine -B build-core-integration-network-flag \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF \
  -DCORE_APP_ENABLE_NETWORK=ON
cmake --build build-core-integration-network-flag -j3 --target core_app
ctest --test-dir build-core-integration-network-flag \
  -R '^test_core_app_target_contract$' --output-on-failure
```

当前证据仅为 Linux CPU 构建、configure 和真实进程 CLI。没有运行真实场景、真实 Vulkan/OpenGL 窗口、音频设备或网络；record/headless 也不能解释为 GPU 画面。后续任务必须分别提供这些证据。

## P12 Task 2：离线资产与 checkpoint v1

### 固定关卡与 baker

`core_app_asset_bake --output DIR` 是独立 C11 离线工具；目标在 `ENGINE_BUILD_TESTS=OFF` 时也存在。它不调用 `core_app_run()`，不创建 RHI 设备、音频设备、网络或跨线程所有权。源树正式资产只由该命令显式生成，测试使用 per-process 临时目录。

`level.bscn` 由真实 `scene_save_binary` 写出并由 `scene_probe_binary`/`scene_load_binary` 回读。固定实体顺序为 Ground、User、Chaser、DynamicWall、Vehicle、VisibleColor、HiddenColor；`actors.sidecar` 逐行使用 P1 已有的 `entity-index class-name` 格式。七个实体共享一份真实 CPU cube 几何（24 vertices、36 indices），通过 `SerializeOptions.read_mesh_geometry` 交给 BSCN writer；没有 GPU readback。七个节点使用各自的变换和颜色材质，隐藏颜色节点保留 mesh/material 引用但初始 `has_mesh=false`。场景实体和 Flow 目标只保存 `(index, generation)`，没有持久化 C 指针。

`level.fg` 由 `break_flow_serialize` 生成，包含 enter → delay(30 ticks) → add-item 的两条 exec link。`director.lua` 和 `user.lua` 可由真实 `break_lua` 加载，`chaser.lua` 是明确的语法错误 fixture；本任务不建立运行时 VM 生命周期。`level.banm` 由 `anim_codec_encode` 生成，含 translation/rotation/scale 三个通道，测试用 `anim_codec_decode`、`anim_codec_time_error_bound`、`anim_codec_scalar_error_bound` 和旋转误差界验收。`tone.wav` 是固定 seed 的 44100 Hz、mono、16-bit PCM，4410 个样本；没有音频设备或听测证据。

三个 `.scenario` 文件是版本化固定输入资产，由同一 baker 生成；场景脚本解析和生命周期执行属于后续任务，本任务没有声称它们已运行。

### checkpoint v1 格式与事务

`manifest.core` 为显式小端二进制：40 字节头加每条 88 字节记录。头依次是固定 8 字节 `CORECKPT`（无额外 NUL）、version=1、header_bytes=40、exact_total_size(u64)、generation(u64)、file_count(u32)、reserved(u32)。记录依次是 kind(u32)、name_length(u32)、size(u64)、FNV-1a-64(u64)、64 字节以 NUL 结尾并零填充的 basename。FNV 只用于损坏检测，不是安全认证。

每代 1..16 个文件，每文件最多 64 MiB，basename 最多 63 字节且只允许 ASCII 字母数字、`_.-`；路径分隔符、绝对路径、`..`、`.` 和 `manifest.core` 均被拒绝。容量或长度超限返回 `BREAK_RUNTIME_OVERLOAD`，不静默截断。读取先验证完整 manifest 和所有记录，再逐文件以固定 4096 字节缓冲 staging 校验精确长度和 hash，无需按 payload 大小分配。

调用者先以新 generation 名写 payload，避免覆盖旧 manifest 引用的文件。`core_app_checkpoint_write_manifest_ex` 先重新读取并校验所有新 payload，再用一个 `PlatformAtomicWriter` 提交 manifest。write、file-fsync、close 或 rename 在目标替换前失败时返回 `BREAK_RUNTIME_FAILED`，结果为 `CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED`，旧 manifest 不变，并按既有安全规则清理新 payload。rename 成功后 directory open/fsync 失败时返回逻辑 `BREAK_RUNTIME_OK`，结果为 `CORE_APP_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN`，新 manifest 与 payload 保留，不执行恢复 rename。旧 `core_app_checkpoint_write_manifest` 保留逻辑提交 API，OK 也可能表示 unknown；需要 durability 区分的调用必须使用 `_ex`。`core_app_checkpoint_probe` 不修改任何 World/Level；真实运行状态反序列化、资源重建和事务 load 属于后续任务。

### 已执行的 Task 2 证据

Linux 上 `test_core_app_assets` 为 9/9，通过两回 baker 逐字节比较、BSCN+P1 sidecar、Flow、BANM、WAV、Lua、manifest 格式、payload/manifest 损坏、非法名称/容量和 RLIMIT_FSIZE 中途写失败回滚。相关 `test_scene_serial`、`test_break_flow_serial`、`test_anim_compression`、`test_break_kernel_level`、`test_platform_fs_write`、`test_break_lua_module` 与新增测试合计 7/7 通过。

生产变异临时删除 payload hash 比较后，篡改用例如期失败（8 通过、1 失败）；恢复后 9/9。正式 `engine/assets/core_app` 的 11 个文件均由最终 baker 生成，并与第二回独立输出逐 `cmp` 一致。关键 SHA-256 为：`level.bscn` `85c1f349f8fc50fd916d3aa74797c337ee34d2c5ae65f723d10df2def6e0537e`，`level.fg` `9be4ca42a7bbd0e3ccd7f663a9d372b15b0daaaaeac08a8f876e15d0a57fb473`，`level.banm` `f3181920a4cdf26267b0aaeefb29664b9fae582ddaef9d39558403e236788873`，`tone.wav` `f0e63c5eb3adef364e73e3113573b104a372bad25425819684ee1d0a695e2682`。

这些证据仅为 Linux CPU/文件系统证据。未运行 Windows 写路径、真实运行时循环、GPU、音频设备、听测或网络；`core_app_run()` 对合法配置仍按 Task 1 合同返回 `BREAK_RUNTIME_FAILED`。

### 最终回归补充（2026-11-09）

完整构建使用 `cmake --build build-core-integration-normal -j3` 成功。任务的非图形验收命令为 `ctest --test-dir build-core-integration-normal -j3 -LE 'graphics|fuzz' -E 'fuzz' --output-on-failure`，结果 330/330 通过；`test_d3d12_dependency_gate`、`test_core_app_nm_missing`、`test_core_app_nm_unsupported` 三个测试按各自既有合同跳过，未把跳过写成设备或符号扫描通过。

曾先用名称过滤 `-E 'graphics|fuzz'` 运行 341 项；该方式不排除 `graphics` 标签，因而执行了图形/平台测试，并出现既有 `test_platform_x11_runtime` 的 `start_fullscreen window does not cover the monitor` 一项失败。本任务未修改该 X11 行为，也不将此运行计为非图形通过证据；正确标签过滤后的 330 项结果才是上述验收结果。

`ENGINE_BUILD_TESTS=OFF` 的独立构建树已成功构建 `core_app` 和 `core_app_asset_bake`，该 baker 的 11 个输出也与源树正式资产逐字节一致。`test_core_app_target_contract` 再次通过；两个 nm negative-path 测试仍按合同跳过。合法 `core_app` 配置的真实进程仍返回 FAILED/退出 2，未被资产交付改成伪成功。

## P12 Task 2 独立评审 fix round 1

### 正式资产追踪与读取

根目录 `.gitignore` 仅对 `engine/assets/core_app/tone.wav` 增加例外，避免通用 `*.wav` 规则继续漏掉正式资产。`test_core_app_formal_asset_tracking` 对 Git 索引要求恰好 11 个指定路径；`test_core_app_assets` 另要求正式目录恰好含这 11 个非空文件，并与 fresh baker 输出逐字节一致。BSCN、Flow、BANM、WAV 和 Lua reader 测试现在读取正式目录，而不是只读临时 baker 输出。`CORE_APP_FORMAL_ASSET_DIR` 测试环境变量可把同一套 reader/比较测试指向干净 Git archive 的解压目录。

### basename 长度与规范化别名

63 字节 basename 合法；API 中 64 字节无 NUL 的名称和磁盘记录 `name_length>=64` 都返回 `BREAK_RUNTIME_OVERLOAD`，非法字符、内嵌 NUL、非零 padding 等结构损坏仍为 `BREAK_RUNTIME_INVALID`。

为保证同一 checkpoint 在大小写敏感与不敏感文件系统间移动时仍不破坏旧代，v1 采用保守的统一规则，而不是按当前宿主改变接受策略：保留名、重复名和旧 payload 名都按 ASCII 大小写折叠比较；`MANIFEST.CORE` 等保留名变体被拒绝；尾随点被拒绝，避免 Windows 规范化别名；新记录与旧 manifest 中 payload 的大小写变体或尾随点变体也被拒绝。该策略会在大小写敏感系统上额外拒绝一些本来可共存的名称，是有意的可移植性格式约束。Linux 用例验证的是该格式策略，不是 Windows/NTFS 实机行为。

### 当前 checkpoint 提交与 durability 协议

`PlatformAtomicCommitResult` 区分 `SUCCESS_DURABLE`、`NOT_COMMITTED_TARGET_UNCHANGED` 和 `RENAMED_DURABILITY_UNKNOWN`；旧 `platform_atomic_writer_commit()` 仅对第一种返回 true，保持 bool 兼容。write、file-fsync、close 或 rename 在目标替换前失败时，checkpoint 返回 `BREAK_RUNTIME_FAILED`，旧 manifest 不变并安全清理新 payload，实际 rename 次数为 0。

rename 成功后 directory open/fsync 失败时，新 manifest 已经可见。checkpoint 返回逻辑 `BREAK_RUNTIME_OK` 和 `CORE_APP_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN`，保留新 manifest 与 payload，不执行恢复 rename，并发出 fsync 警告。独立旧备份只用于恢复证据，不改变同目录提交结果。`CORE_APP_CHECKPOINT_COMMIT_DURABLE` 仅表示平台要求的步骤完成，不声称掉电、崩溃或硬件故障下持久性已保证。

故障测试只在 `test_core_app_assets` 和 `test_platform_fs_write` 的 Linux 测试进程内使用 linker wrappers 注入 write、file-fsync、rename 和 directory-fsync 失败，同时检查返回状态、实际 rename 次数、manifest 字节/generation、payload 和 probe；生产代码没有 test hook。

已执行的新套件为 18/18，覆盖恢复成功、恢复写失败、损坏旧 manifest、名称边界和规范化别名；资产/FS/Flow/动画/P1/Lua 定向集合为 8/8。生产变异临时无视恢复结果并无条件清理，恢复写失败用例如期从 18/18 降为 17/18，恢复后回到 18/18。Windows 实机、GPU、音频设备、听测和网络仍未验证。

### fix round 1 最终验证

完整 `cmake --build build-core-integration-normal -j3` 成功，`ctest --test-dir build-core-integration-normal -j3 -LE 'graphics|fuzz' -E 'fuzz' --output-on-failure` 为 331/331 通过，三个既有 D3D12/nm 合同测试按规则跳过。`ENGINE_BUILD_TESTS=OFF` 下 `core_app` 和 `core_app_asset_bake` 构建成功，no-tests baker 的 11 个输出与正式资产一致；`test_core_app_target_contract` 通过，两个 nm negative-path 测试仍按合同跳过。

提交前从 Git 索引执行 `git write-tree`，对该干净 tree 的 `engine/assets/core_app` 做 `git archive`，确认恰好 11 个路径且包含 8864 字节 `tone.wav`，解压到全新临时目录后以 `CORE_APP_FORMAL_ASSET_DIR` 指向归档资产。完整 18/18 再次通过，其中正式目录与 fresh baker 比较以及 BSCN/Flow/BANM/WAV/Lua readers 均实际读取归档文件，而不是当前源树。

## 同步、命名迁移与 fix round 2（2026-11-10）

### master 同步与命名边界

实施前 WIP diff 保存在 `.superpowers/sdd/2026-11-03-core-app-integration/task-2-fix2-before-master.diff`，独立 stash 为 `cef5784afeb52a37b1064d417a3fedc742e15162`。同步 merge 为 `0f2b137384fdc41f44509cc5a40b26c098213007`，双亲分别是 Task 2 fix1 与 master `ffdd2e865ec1e34568588404e69ae8c1716cafb4`；X11 移除、C++20/QUIC 和 Task 1/2 改动均保留，既有其它 stash 未使用或删除。

应用、核心库、baker、目录和测试现使用 `core_app`、`core_app_runtime`、`core_app_asset_bake`、`test_core_app_*`；checkpoint 文件/API/类型使用 `core_app_checkpoint`/`CoreAppCheckpoint*`。资产位于 `engine/assets/core_app`，设计文档为 `docs/design/core_app_integration.md`，新结果只使用 `build-core-integration-*`。P12 计划 Task 1–13 的后续 `scenario`、`core_app_input`、`core_app_simulation`、`core_app_render`、`core_app_audio`、`core_app_network`、`core_app_script` 名称同步更新。P0–P11 的 `break_kernel`、`BreakRuntimeError`、`test_core_style_prototype` 等既有公共名称未迁移。

`test_core_app_naming_contract` 防止新集成源码、资产、目标、测试和当前设计/计划重新引入旧前缀；只对明确的 P0 既有测试/文档引用豁免。`manifest.core` 的 magic 为固定 8 字节 `CORECKPT`，reader 只接受该标识，不双格式兼容。scenario 首行同步为 `core-app-scenario 1`，正式文件由重命名后的真实 baker 重新生成。

### 可区分提交结果

`PlatformAtomicCommitResult` 区分 `SUCCESS_DURABLE`、`NOT_COMMITTED_TARGET_UNCHANGED` 和 `RENAMED_DURABILITY_UNKNOWN`。旧 `platform_atomic_writer_commit()` 保留 bool 兼容，只在 `SUCCESS_DURABLE` 时返回 true；需要区分 rename 后状态的调用方使用 `platform_atomic_writer_commit_status()`，writer 仍在所有结果下被消费。POSIX 记录 rename 是否实际发生，Win32 保留 `MoveFileEx(WRITE_THROUGH)` 分支，未以 POSIX 证据代替 Windows 实机验证。

`core_app_checkpoint_write_manifest_ex()` 额外返回 `CoreAppCheckpointCommitResult`。只有 rename 前的失败返回普通 `BREAK_RUNTIME_FAILED`，保持旧 manifest 并按既有安全规则清理新 payload。rename 已成功而 directory open/fsync 失败时，不恢复新 manifest，不删除新 payload，返回逻辑 `BREAK_RUNTIME_OK` 和 `CORE_APP_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN`，同时发出明确 fsync 警告。旧 `core_app_checkpoint_write_manifest()` 保留逻辑提交 API，OK 也可能表示 unknown；需要 durability 区分的调用必须使用 `_ex`。`CORE_APP_CHECKPOINT_COMMIT_DURABLE` 仅表示平台要求的 file/directory 步骤完成，不声称任意崩溃、掉电或硬件故障下持久性已证明。

真实故障矩阵同时检查返回值、实际 rename 次数、manifest 字节/generation、旧新 payload 和 probe：write/file-fsync/rename 失败为 FAILED+NOT_COMMITTED，directory-fsync 失败为逻辑 OK+UNKNOWN；旧 manifest 损坏时的独立备份仍可用。rename 后没有恢复 writer 或第二次恢复 rename。

### 已执行的迁移后证据

新构建树的真实 `core_app` CLI/target、资产、命名和 reader focused 集合为 12/12（两个 nm negative-path 按既有合同跳过），`test_core_app_assets` 为 20/20，`test_platform_fs_write` 为 11/11。ASan+UBSan 和 TSan focused 均 4/4，无 sanitizer 报告。旧 scenario 数据标识曾使正式目录与 fresh baker 比较出现 19/20，使用最终 `core_app_asset_bake` 重生成后恢复 20/20。生产变异把 unknown 错映射为 FAILED，三个 rename 后协议用例按预期降为 17/20；恢复后再次 20/20。

正式 `engine/assets/core_app` 的 11 个文件均由最终 baker 生成，fresh 第二回逐字节一致。未运行 Windows/NTFS 实机、真实运行时主循环、GPU、音频设备/听测或网络；这些结果不构成崩溃持久性证明。

### 全量与交付验证补充

完整 `cmake --build build-core-integration-normal -j3` 成功，`ctest --test-dir build-core-integration-normal -j3 -LE 'graphics|fuzz' -E 'fuzz' --output-on-failure` 为 346/346 通过；`test_d3d12_dependency_gate`、`test_core_app_nm_missing`、`test_core_app_nm_unsupported` 按既有合同跳过。`ENGINE_BUILD_TESTS=OFF` 的 `build-core-integration-no-tests` 成功构建 `core_app` 与 `core_app_asset_bake`，no-tests baker 的 11 个输出与正式资产逐文件一致；`test_core_app_target_contract` 再次通过，两个 nm negative-path 仍按合同跳过。

master 的 X11 removal 合同和 C++20 public API/QUIC 相关测试均包含在上述全量结果中，没有为 Task 2 回退或排除这些既有行为。


## P12 Task 3：事务式 level 与 record 生命周期（2026-11-10）

本节是当前生命周期状态；上方 Task 1 的“合法配置始终 FAILED”和 Task 2 的“主循环尚未运行”仅保留为当时历史。同步 master `737ccc8b4227f2d53039119caf1a2b6066e2871e` 的独立 merge 为 `30c9285d9605ff07157f8563cda60279082f6269`，也是本任务 review BASE。合并没有冲突，X11 移除、CI 修复、Task 2 命名/资产/checkpoint 三态协议及双方文档均保留。

### 所有权与加载事务

`core_app --render=record --audio=record --fixed-step` 现在执行真实场景文件。主线程即 LogicThread，独占 `World`、`BreakKernel`、Lua/adapter、Flow、AI 和 physics 的可变状态；Runtime IO worker 只通过 VFS 返回有界字节，不接触这些对象。render/audio 分别只消费固定大小的 `CoreAppRender*`/`CoreAppAudio*` POD 快照与命令。

每次 load 都分配独立 `CoreLevel` candidate，顺序为：注册 ECS 组件并创建 World → Runtime IO 读取 BSCN、`scene_load_binary_memory` 在 candidate World/Scene 上完成 CPU staging → Flow 反序列化/实体引用验证、两个正式 Lua module 加载和 adapter 创建 → `break_kernel_level_open` 验证正式 actor sidecar 并 adopt → physics ground/user body → 8x8 CPU navmesh、AI runtime/Chaser agent → BANM decode → record resource POD staging → World/Scene/Flow/resource 交叉引用。只有全部成功后才执行一次 `application->level = candidate` 并递增非零 u64 generation。

candidate 的任一模态资源或验证失败都走统一逆序销毁，不修改当前 level 指针或 `next_generation`。已有 level 时 replacement 失败会写 `load_rejected` 并继续旧 level；没有已提交 level 的启动失败退出 2。显式 unload 先使当前指针失效，再销毁旧 generation。正常 replacement 成功时也先完成 candidate，再提交新代并释放旧代。

`break_kernel_level_open` 的 load hook 不重复读取 BSCN：它只确认先前 `scene_load_binary_memory` 已填充同一 candidate 的 World/Scene。这样 P1 的 sidecar/adopt/close 生命周期是真实执行路径，同时避免第二次替换 World。

### Runtime IO 与 shutdown

整个进程只调用一次 `break_runtime_io_init`。BSCN completion 的字节被 Scene 复制后先释放 request，再进行后续 staging 或下一次 VFS mount/load；旧 request 不跨 level 保留。正常 shutdown 按 network→audio→render→level 注册 coordinator 回调：关闭 admission/producers 和 audio queue、drain、join、render idle/destroy，level drain 后执行一次 Runtime IO shutdown，确认 `active=0`，最后销毁 level/VFS。network 本任务只有生命周期占位，没有传输实现。

启动失败或 coordinator sticky FAILED 不调用 coordinator stop；`app_rollback` 显式执行 audio drain/join/destroy、render idle/destroy、candidate/current level destroy、Runtime IO shutdown 和 VFS destroy。失败 trace 写 `runtime_failed`，不会伪写正常 `runtime_stopped`。

### record 边界与场景

`core_app_render.c` 只记录 BSCN manifest 的非零 resource id、generation 和 frame id；没有 RHI device、GPU restore 或 `engine_rhi_headless` 链接。Task 1 已存在的 `core_app` 目标仍按配置链接 Vulkan/OpenGL runtime，但 record 路径不创建设备，不能解释为 GPU 证据。`core_app_audio.c` 是 16 项固定容量 FIFO，记录 listener/stop 的命令顺序；没有声卡 worker、source 控制或听测。

Task 2 的正式 `load_unload.scenario` 无需修改：frame 1 load、frame 2 unload、frame 3 load、frame 4 unload、frame 5 end。实际 trace 包含有序的 runtime_running → level_loaded 1 → frame 1 → audio listener 1 → level_unloaded 1 → level_loaded 2 → runtime_stopped，也记录第二代 frame/unload 和最终 `io_stopped active=0`。场景 parser 是 Task 3 内部的有界生命周期子集，另外允许 `load ROOT` 以测试跨资产 root 的失败 replacement；Task 4 的输入/移动语义不在此实现。

热帧路径只做固定数组 POD 拷贝、固定 FIFO 操作和 trace 输出，没有堆分配。堆分配限于进程启动和 level staging，固定上限为 64 个 scenario step、64 个 render resource、16 个 audio command、4 个 Runtime IO request 和 1 个 IO worker。

### 验证与限制

真实进程 CTest 先对 stub 观察到退出 2 和完整事件缺失，再对实现 GREEN。正常流程、缺失 BSCN、损坏 Flow、未知 Actor class、缺失 Lua module、以及“有效 load → 坏 Flow replacement → 旧 generation frame 2”均由 `test_core_app_lifecycle_load_unload` 启动真实 `core_app`，没有库 substitute。四个启动失败均退出 2，有各自 stage 诊断，没有 level/frame commit，并以 `io_stopped active=0` 结束。

生产变异曾在 Flow 验证前插入 `application->level = candidate`；正常与 replacement 进程发生段错误，失败 fixture 也无法保持合同，测试按预期 RED。删除该变异行后恢复 GREEN。focused Runtime/BreakKernel/Scene 回归 5/5、core_app 既有合同 6/6（两个 nm negative-path 按合同跳过）、全量非图形 348/348 通过。ASan+UBSan 和 TSan 生命周期各 1/1 通过；no-tests 的 `core_app`/`core_app_asset_bake` 均构建成功。

这些证据仅是 Linux CPU/record 生命周期证据。没有输入/用户模拟、GPU `asset_scene_restore`、窗口或像素、音频设备/听测、网络、完整 checkpoint 状态恢复或完整 device worker；Windows 和其他平台未运行。VFS 的 16 mount 上限和 Runtime IO/VFS 路径上限仍是当前有界配置，超长路径或超过 mount 预算会明确拒绝 load。


## P12 Task 3 独立评审 fix round 1/5（2026-11-10）

本轮只修复 Task 3 的事务、Runtime IO/VFS 和真实进程测试，不改变 Task 4+ 范围。评审 BASE 为 `da5d475aa97823c01de2e90af351ad17b4ab2bff`；两个 Critical、三个 Important 和两个 Minor 均按下述机制闭合。

### mount namespace 与 candidate 一致性

应用拥有的 VFS 只用于 candidate BSCN，且始终只有一个 DIR mount slot。每次 `stage_bscn` 在提交新 request 前清空上一 candidate 的 DIR namespace，再 mount 本次 `asset_root`；不会从新 root 回退到旧 root。上一 level 的 World/Scene/record resource 已全部 CPU staging，不依赖旧 mount，因此丢弃旧 namespace 不影响已提交 level，也不会累积 16 个 mount。应用不允许其他 mount 类型或多 slot 状态进入该路径。

真实测试先 load good，再执行 17 次缺失 BSCN replacement，最后再次 load good。17 次都以 generation 1 reject，旧 level 持续逐帧，最后一次以 generation 2 成功 replacement，覆盖失败配额和 valid→valid 分支。修复前同一 fixture 连续错误提交到 generation 15，随后才因 mount 上限拒绝。

### commit 尾部与双代所有权

`core_app_level_load` 现在分别返回 `committed` 和 `runtime_fatal`。所有 staging 阶段失败（包括 render/crossref）在已有 level 时统一写 `load_rejected` 并继续旧代；只有无旧代可回退时才终止。commit 后的 audio/drain/trace/render 错误写 `runtime_fault stage=commit`，不会再写 `load_rejected` 或继续下一帧。

成功 replacement 在指针/generation 提交期间把 previous 保存在 `CoreApp.retired_level`，直到实际销毁后才清空。rollback 分别清理 current 和 retired，覆盖 commit 尾部任意失败点。`level_destroyed` 只在实际销毁已提交 level 后记录；成功 replacement、commit 尾部和 sticky shutdown 测试都要求每个 generation 恰好出现一次。销毁前保存 generation，避免事件读取已释放对象。

Linux 测试用独立 `LD_PRELOAD` 库对 `level_unloaded` trace 的一次 `fflush` 注入 EIO。实际 trace 为 `runtime_fault commit → destroyed 2 → destroyed 1 → io_stopped active=0 → runtime_failed`，没有伪 reject/伪停止。对 `io_stopped` 注入同类错误则覆盖 coordinator callback 进入 sticky FAILED 后的应用级显式 rollback。

### IO timeout quiescence

首次 `wait_completion` 的 TIMEOUT 不再直接允许后续 mount，也不使用只统计 caller request 的 `stats.active` 误判 worker 已停止。代码对同一个 request 再做一次有界等待；真实 completion 只在 worker 的 VFS read 完成后发布，因此消费 completion、释放 message/request 并记录 `io_quiesced` 后，后续 mount 才安全。第二次等待失败或 quiescence trace 失败属于 runtime fatal，candidate 清理后由 shutdown/join 收尾，不再继续 scenario。

测试的 preload `fread` 在 timeout replacement 的 BSCN 上延迟 6 秒，scenario 随后再次 load good。修复前 TSan 实际报告主线程 mount 与 IO worker `vfs_open` 的数据竞争；修复后普通和 TSan 均完成 reject→旧代 frame→generation 2 replacement→正常停止。生产代码没有 test hook，测试库不替换 application/runtime 库。

### 其他覆盖与 Minor

- 将正式 BSCN 的 `MESH_DATA` chunk 标为未知类型，保留可解析 Scene 但缺少 geometry，真实触发 crossref reject；旧 generation 继续，不再因 stage 特判退出进程。
- 成功 valid→valid replacement、17 次 mount reject、commit 尾部、sticky FAILED、IO timeout、crossref 均进入同一个真实进程 CTest，因此 ASan+UBSan/TSan 执行相同路径而非只跑旧主路径。
- 删除未使用的 `old_request`；`retired_level` 具有明确所有权。
- `CORE_APP_AUDIO_QUEUE_CAPACITY=16` 仍仅为 Task 3 临时 record 容量。源码注释和 Task 9 计划均明确：Task 9 必须扩展为 256，并实际测试超过 256 个未消费命令的 OVERLOAD 与 drain 后恢复，不能把 16 当成最终常量。

mount 清空、commit 分类和第二次 completion 等待分别做了独立生产变异；三者都取得针对性 RED 后恢复 GREEN。最终全量非图形为 348/348，no-tests 的 `core_app`/`core_app_asset_bake` 构建成功，ASan+UBSan 和 TSan 的完整 lifecycle 各 1/1，无 sanitizer 报告。证据仍限 Linux CPU/record；LD_PRELOAD 故障注入在非 Linux 平台标为 UNVERIFIED，不声称跨平台覆盖。

## P12 剩余验证登记关闭（2026-11-15）

### 有界 IO 等待的故障结果

- `stage_bscn` 第一次 5 s completion 等待超时后再等一次。第二次等待失败，或 `io_quiesced` trace 写入失败，都会设置 `runtime_fatal`，主循环随后写 `runtime_fault stage=bscn` 并以 2 退出，不会降级为 `load_rejected`。
- `io_quiesced_eio` 用 `CORE_APP_TEST_FAIL_QUIESCED_FLUSH` 在 `io_quiesced` 行后注入 `fflush` `EIO`。`io_second_wait_fail` 让读取阻塞 25 s，超过两次等待和 5 s shutdown 的总和。
- `break_runtime_io_shutdown` 超时返回 `BREAK_RUNTIME_TIMEOUT`，facade 保持 STOPPING，不释放任何对象。因此 `core_app_stop_io` 不写 `io_stopped active=0`，测试断言 trace 中没有这一行。

### Baker 的 Flow 身份与端口

`test_core_app_assets` 断言 add-item 节点的目标实体正好是 `{2, 1}`（sidecar 中的 `User`），并断言两条 exec link 的 source port 依次为 `BREAK_FLOW_EVENT_EXEC_OUT`、`BREAK_FLOW_DELAY_EXEC_OUT`。

### 物理修正包（2026-11-15）

`CoreAppNetworkHooks` 新增两个可选钩子 `physics_correction_wanted` 和 `physics_correction`。对端报告 DESYNC 时，transport 把该连接的槽标为 `correction_pending`。`app_network_publish` 在 `tick` 之后询问 `physics_correction_wanted`，为真时按 `physics_sync_correction_size` 分配缓冲、`physics_sync_encode_correction` 编码当前物理世界，再交给 `physics_correction`（字节只在调用期间借用，调用后释放）。超过 `CORE_APP_PHYSICS_CORRECTION_MAX_BYTES`（64 KiB，与网络载荷上限用 `_Static_assert` 锁定）的修正不编码。transport 只发给仍在等待且可发送的槽（id `0x4003`，v1），发送成功或连接已关闭时清除标记，OVERLOAD 时保留到下一 tick。同一 tick 前的多次 DESYNC 合并为一次修正。`network_stats` 末尾追加 `physics_corrections_sent`。

测试：loopback 场景 A 在发出 DESYNC 报告后等待 `0x4003`，客户端手工校验 PSNP 魔数、长度字段和 FNV-1a 校验和；新增第二个认证对端 A2，它从不报告 desync，读到比修正 tick 更新的报告之前不得收到修正。驱动脚本断言 `authenticated==3`、`physics_corrections_sent>=1` 且不超过 `physics_desynced`，离线 trace 对比仍逐字节相同。本机一次运行：修正 10644 字节，`physics_desynced=2`，`physics_corrections_sent=1`。8 项变异全部被捕获（其中「不标记 pending」因未使用变量在编译期失败，同一行为由「wanted 恒为假」变异在运行期覆盖）。

### trace 转换为 break.trace（2026-11-15）

`core/trace_core_app.h` 的 `break_trace_core_app_to_chrome` 读取 `--trace` 写出的文本，生成 Chrome trace-event JSON：每条有效 `COREAPPTRACE version=1` 行变为 `cat=core_app`、`ph=i` 的事件，`name` 取 `event=` 的值，`ts` 为序号，其余字段进 `args`。文本格式本身没有改变。不合格的行（前缀错误、版本不是 1、缺 `event=`、字段没有 `=`、空键、重复键、超过 32 个字段）被跳过并计入 `skipped`。

补充（2026-11-16）：行内可带可选字段 `ts_us=<微秒>`（规范十进制、最多 18 位）。有该字段时它成为事件的 `ts`，不再进入 `args`，并计入 `BreakTraceCoreAppReport.timestamped`；`ts_us` 不是规范十进制时整行跳过。没有 `ts_us` 的行仍以序号为 `ts`，旧 trace 转换结果逐字节不变。约定生产方要么每行都写 `ts_us`，要么都不写。见 `docs/superpowers/plans/2026-11-16-core-app-trace-timestamps.md`。

补充（2026-11-16）：`core_app --trace-timestamps`（需要 `--trace`）让每条 trace 行在 `COREAPPTRACE version=1 ` 之后带 `ts_us=<单调时钟微秒>`，配合 `--trace-json` 得到真实时间轴。core_app 的全部写入点（`app_trace`、渲染、音频、GPU、网络传输）都经 `core/trace_core_app.h` 的 `break_trace_core_app_fprintf` / `vfprintf` / `write`；时钟由 `break_trace_core_app_set_clock` 进程级设置，默认未设置时直接调用 `vfprintf`，输出与 libc 调用和以前完全一致。时钟是本机单调时钟，同一台机器上多个进程的 trace 可直接由 `trace_merge` 对齐；不同机器之间仍需时钟对齐。见 `docs/superpowers/plans/2026-11-16-core-app-trace-ts-writer.md`。

补充（2026-11-16）：`core/clock_offset.h` 提供不同机器之间的时钟偏移估计。一个样本是 NTP 式的四个微秒时间戳（A 发送 t0、B 接收 t1、B 回复 t2、A 接收 t3），`offset = floor(((t1-t0)+(t2-t3))/2)` 为 B 减 A，`delay = (t3-t0)-(t2-t1)`。t2 < t1、往返短于 B 的停留时间（含 t3 < t0）或时间戳超过 2^61 的样本被拒绝并计数。估计器保留最近 8 个样本，取 delay 最小者（相同时取最新），误差上界 `ceil(delay/2)`，无论两个方向如何分配延迟都成立。`clock_offset_merge_shifts` 把偏移换算成 `trace_merge --offset-us` 所需的两个非负平移量。探测包在 core_app 会话协议上的收发尚未实现。见 `docs/superpowers/plans/2026-11-16-clock-offset-estimator.md`。

补充（2026-11-16）：探测包线格式。消息 `0x4004`（`BREAK_NET_MESSAGE_ID_CLOCK_PROBE`）只在 AUTHENTICATED 阶段接受，载荷恰好 32 字节，小端：`[0]` u32 magic `CLKP`（`0x504b4c43`）、`[4]` u8 kind（1 请求 / 2 回复）、`[5..7]` 保留须为 0、`[8]` t0、`[16]` t1、`[24]` t2（微秒）。`core_app_clock_probe_decode` 依次报告 TRUNCATED/OVER_LIMIT（长度不是 32）、BAD_MAGIC、BAD_VERSION（kind 非法）、INVALID（保留字节非 0，或请求带了 t1/t2），失败时不写输出。`core_app_clock_probe_encode` 对非法 kind 或带 t1/t2 的请求返回 INVALID，容量不足返回 OVER_LIMIT，失败不碰缓冲区。`core_app_clock_probe_answer` 只接受请求且要求 t2 >= t1，回复回显 t0。A 端用 `t0, t1, t2` 加本地接收时间 t3 即可喂给 `clock_offset_add`。见 `docs/superpowers/plans/2026-11-16-clock-probe-wire.md`。

补充（2026-11-16）：服务端应答时钟探测。transport 为 `0x4004` 注册处理函数，进入处理函数时先取 `t1 = time_microseconds()`，解码失败或收到的不是请求时 `clock_probe_decode_failed` 加一并返回失败（会话层计为 handler_failed，连接不关闭）。合法请求按连接槽保存（同一 tick 内只保留最新一个），`net_send_pending` 在发送前取 `t2 = time_microseconds()` 组装回复，因此停留时间包含等待下一 tick 的时间，不影响偏移估计的正确性，只放大误差界。槽不可发送时丢弃待答请求，连接关闭时清除。`network_stats` 末尾追加 `clock_probes_answered` 和 `clock_probe_decode_failed`。loopback 测试中对端 A 先发 31 字节探测、带 t1 的请求和一个回复（三者都不得被应答），再发 4 个请求并把回复喂给 `ClockOffsetEstimator`；两端在同一台机器上读 CLOCK_MONOTONIC，真实偏移为 0，测试要求估计值在 `error_us` 之内（本机一次运行 `offset_us=8 error_us=71`），驱动脚本要求 `clock_probes_answered == 4`、`clock_probe_decode_failed >= 3`。见 `docs/superpowers/plans/2026-11-16-clock-probe-responder.md`。

补充（2026-11-16）：服务端主动探测。每个连接槽有一个 `ClockOffsetEstimator` 和至多一个未答请求。`net_send_pending` 在 producing 且事件队列为空时，对每个可发送槽每 8 个 tick 发一个请求（t0 取发送前的 `time_microseconds()`）；32 个 tick 无回复则丢弃并计入 `clock_probes_lost`。间隔和超时按 tick 计而不是墙钟，因为无窗口运行时 1500 tick 只需约 0.1 秒。处理函数收到 REPLY 时先取 t3，t0 与未答请求一致才成为样本（`clock_replies_matched`），否则计入 `clock_replies_unmatched` 并返回失败；样本被估计器拒绝时计入 `clock_samples_rejected`。估计器首次积累 4 个样本时写一行 `COREAPPTRACE version=1 event=network_clock_offset session=<id> offset_us=<对端减服务端> error_us=<误差界> samples=4`，该行以 `event=network` 开头，离线对比时被过滤。loopback 测试中对端 A 应答服务端请求，故意留一个不答、发一个 t0 错误的回复和一个重复回复；驱动脚本要求 `clock_probes_sent>=4`、`clock_replies_matched>=4`、`clock_replies_unmatched>=3`、`clock_probes_lost>=1`、`clock_samples_rejected==0`，trace 中恰好一行 `network_clock_offset` 且 `|offset_us| <= error_us`。把该偏移交给 `trace_merge` 见下一段。见 `docs/superpowers/plans/2026-11-16-clock-probe-initiator.md`。

补充（2026-11-16）：`trace_merge --clock-offset SERVER_TRACE` 从服务端文本 trace 读取偏移。`break_trace_core_app_clock_offset`（`core/trace_core_app.h`）用转换器的同一行解析器扫描合法行，只看事件为 `network_clock_offset` 的行：恰好一行且 `offset_us` 为可带负号的规范十进制（无前导零、无 `-0`、无 `+`、至多 18 位）、`error_us` 为规范十进制时返回 OK；没有该行返回 NOT_FOUND，多行（多个对端）返回 AMBIGUOUS，字段缺失或格式不规范返回 MALFORMED，输出只在 OK 时写入。工具要求恰好两个输入（第 1 个为服务端 JSON，第 2 个为对端 JSON），不能与 `--offset-us` 同用；偏移经 `clock_offset_merge_shifts` 换算成两个非负平移量，分别作用于两个输入，并在 stdout 打印 `trace_merge: clock offset offset_us=N error_us=M`。读取或解析失败退出 1，用法错误退出 2。多个对端时仍需手动用 `--offset-us`。见 `docs/superpowers/plans/2026-11-16-trace-merge-clock-offset.md`。

补充（2026-11-17）：多个对端的自动对齐。`trace_merge --clock-offset SERVER_TRACE SERVER.json --session N PEER.json [--session M PEER2.json ...]`：`--session` 只作用于下一个输入，第 1 个输入是服务端，不能带 `--session`；一旦使用，其余每个输入都必须带，且必须与 `--clock-offset` 同用；不带 `--session` 时保持原来的两输入用法。每个对端的偏移由 `break_trace_core_app_clock_offset_for_session` 读取：只统计 `session=` 为规范十进制（无符号、无前导零、不超过 u64）且等于 N 的 `network_clock_offset` 行，其他会话的行（即使格式错误）被忽略；时钟行缺少规范 `session` 时返回 MALFORMED，同一会话多行返回 AMBIGUOUS。平移量由 `clock_offset_merge_shifts_many`（`core/clock_offset.h`）计算：offset_i 为对端 i 减服务端，base = max(0, max offset_i)，服务端平移 base，对端 i 平移 base − offset_i，全部非负且放在同一时间轴上；单个对端时与 `clock_offset_merge_shifts` 结果相同。stdout 对每个对端打印 `trace_merge: clock offset session=N offset_us=... error_us=...`，失败信息带 `for session N`。见 `docs/superpowers/plans/2026-11-17-trace-merge-multi-peer.md`。

`core_app --trace-json PATH`（需同时给出 `--trace`）在运行结束后调用上述转换并写出 JSON；写入失败时退出码为 2。

## 补充（2026-11-17）：物理增量修正包

`physics_sync` 新增增量修正包（magic `0x444e5350`，"PSND"）。完整修正包每次都带整个 `physics_snapshot_save` 负载；增量包只带相对一个双方都持有的基线快照发生变化的字节。

- 头部 28 字节：tick、基线 tick、基线字节数、基线 FNV-1a 32、目标字节数、目标 FNV-1a 32。之后是若干区段 `(offset u32, len u32, bytes)`。
- 基线按目标长度零扩展或截断，所以 body 数量变化时也能编码；目标只增长时，新增部分的零字节不需要发送。
- 编码端把不超过 8 字节（一个区段头的大小）的未变化间隙并入相邻区段，避免区段头开销超过它节省的字节。
- `physics_sync_delta_ticks` 只读两个 tick，接收方据此选择基线。
- `physics_sync_decode_delta` 依次校验 magic、基线校验和、目标容量、每个区段（非空、升序、不重叠、在目标范围内、不越过包尾，偏移和长度按 64 位相加防止回绕），最后校验重建结果的校验和。基线字节数字段只作说明，长度不同的基线校验和必然不同。
- `physics_sync_apply_delta` 在调用方提供的 scratch 缓冲区里重建快照，校验通过并且 `physics_snapshot_restore` 成功后才重置 tracker；任何失败都不改世界、tracker 和 `*out_tick`，与完整修正包一致。

core_app 还没有接入增量包：权威端需要为每个对端保存最近确认的基线，并决定发送增量还是完整包。这是下一个切片。

## 补充（2026-11-17）：core_app 发送增量物理修正

transport 为每个连接槽保存一个 `PhysicsSyncBaseline`：这个对端最近一次成功发送的修正对应的快照及其 tick。规则如下：

- 对端回报某 tick 的 MATCH，且该 tick 不早于基线 tick 时，基线标为已确认。已应用修正的对端会匹配，丢掉修正的对端会保持分歧，永远不会确认。
- `net_physics_correction` 先用 `physics_sync_correction_payload` 从 core_app 交来的完整包中取出快照，再逐槽调用 `physics_sync_baseline_encode`：基线已确认且增量严格更小时发增量包，否则发完整包。
- 发送成功后，把该快照存为新的基线，确认标记清零。所以对端如果丢了基线，在下一次确认之前最多只会收到一个增量包。
- 连接关闭、槽复用和 transport 销毁时都会释放基线。
- `network_stats` 末尾追加 `physics_delta_corrections_sent`，它也计入 `physics_corrections_sent`。

接收端使用 `physics_sync_apply_received`：按 magic 分派完整包或增量包。增量包按自己持有的基线解码，分配目标缓冲区之前先用世界容量限制目标长度。成功后，恢复的快照成为新的持有基线；失败时世界、tracker 和基线都不变。

loopback 场景 A 收到第一个完整修正（本机 10644 字节）后，用自己世界的哈希回报持有基线的 tick（与权威端一致，属于 MATCH），再发一次 desync。第二个修正必须是增量包（本机 28 字节）、基线 tick 等于客户端持有的 tick，并且应用后与权威端回报的哈希一致。

场景 A 先发了两次 desync，第一个修正发出前它们会合并；但第二次可能在第一个修正发出之后才被处理，于是再触发一个针对未确认基线的完整修正。所以客户端最多重试 3 轮：收到额外的完整包就应用并重新确认。驱动脚本要求额外完整包也收敛，而且 `physics_delta_corrections_sent` 恰好为 1。

变异测试：transport 的 4 项中 3 项被捕获。存活的 1 项删掉了完整包解析失败时的提前返回；这种情况下快照为 NULL，`physics_sync_baseline_encode` 同样拒绝，两者行为等价。`physics_sync` 的 19 项中 18 项被捕获。存活的 1 项把接收端的目标长度上限放宽一个 body，这个上限只约束分配大小，超长目标随后也会被解码和 `physics_snapshot_restore` 拒绝，同样等价。

## 补充（2026-11-17）：认证 trace 行带会话号，loopback 稳定性修正

服务端认证成功时写的行改为 `network_session result=authenticated session=S tick=N`。`S` 与 `network_clock_offset session=S` 使用同一个 `break_session_manager_session_id`。这样只看服务端 trace 就能列出所有认证过的会话，并把时钟偏移对应到其中一个，`trace_merge --session` 的取值有了依据。

驱动脚本（loopback 与 late_auth）新增断言：
- 每条认证行都带规范的十进制 `session=`；
- 会话号互不重复；
- 认证行条数等于 `network_stats` 的 `authenticated`；
- loopback 中唯一一条 `network_clock_offset` 的会话号属于已认证会话。

改格式前两个用例都失败（RED），改后通过。

为排查稳定性，本次把 loopback 连续跑了 20 多次，发现两处与时序有关的偶发失败，都在测试客户端，已修正：
- `a_answered_server_clock_probes`：原来要求累计应答 6 次服务端时钟探测，但前面各阶段已经应答了多少次取决于时序。跳过的那一次可能出现在累计已满 6 次之后，于是判定失败。现在改为：等到跳过的请求出现后，再应答 2 次，并且累计不少于 6 次。
- `a_received_delta_physics_correction`：第一次修正前重复发出的 desync 可能晚到，每次都触发一个新的完整修正，把服务端基线移到客户端正在确认的 tick 之后。三轮重试都可能落空。现在每轮先读到比持有基线新 4 个 tick 的报告，并在此之前应用途中收到的所有修正，确认的就是服务端最新的基线。修改后连续 15 次通过，每次都在第 1 轮拿到增量包。

## 补充（2026-11-17）：服务端告知对端会话号

认证成功后，服务端给对端发一条会话欢迎消息 `0x4005`（`BREAK_NET_MESSAGE_ID_SESSION_WELCOME`，v1，只在 AUTHENTICATED 阶段接受，`IDEMPOTENT`）。载荷恰好 16 字节，小端：`[0]` u32 magic `SESW`（`0x57534553`）、`[4]` u32 保留须为 0、`[8]` u64 会话号（非 0）。会话号与服务端 trace 里 `network_session result=authenticated session=S` 和 `network_clock_offset session=S` 的 `S` 相同，对端把它写进自己的 trace，`trace_merge --session S PEER.json` 就不再需要人工对应。

- `core_app_session_welcome_encode`：会话号为 0 或指针为 NULL 返回 INVALID，容量不足返回 OVER_LIMIT，失败不碰缓冲区。
- `core_app_session_welcome_decode`：长度不足返回 TRUNCATED，超长返回 OVER_LIMIT，magic 错返回 BAD_MAGIC，保留字节非 0 或会话号为 0 返回 INVALID，失败不写输出。
- transport：每个连接槽有 `welcomed` 标志。`net_send_pending` 先发欢迎，再发时钟应答、时钟请求、snapshot、物理报告；在欢迎发出之前该槽不算可发送（`net_slot_sendable` 要求 `welcomed`），所以欢迎是对端认证后收到的第一条应用消息。发送失败时下一次 pump 重试。槽复用、关闭、销毁时清零。`network_stats` 末尾追加 `session_welcomes_sent`。
- 服务端不为 `0x4005` 注册处理函数。对端发来的欢迎消息被会话层计为 `handler_failed`，连接不关闭。

loopback 测试：对端 A、A2、F（late_auth 模式下为 G）各自恰好收到一条合法欢迎，且在任何其他应用消息之前；A 与 A2 的会话号不同；被拒绝的对端（未认证、未知 id、错误 PSK、认证超时）收不到欢迎。A 还向服务端发一条欢迎，之后会话仍可用。驱动脚本要求 `session_welcomes_sent` 等于 `authenticated`，客户端报告里的每个会话号都是服务端 trace 里的已认证会话，且互不重复。见 `docs/superpowers/plans/2026-11-17-session-welcome.md`。

变异测试 16 项，加上一项组合变异：
- 编解码 8 项全部被捕获。
- transport 中“不发欢迎”“重复发送”“不计数”“会话号错误”被捕获。
- 槽复用时和关闭时的两处清零单独去掉都不变红，两者互为冗余；同时去掉时被捕获（复用槽的新对端收不到欢迎）。
- 去掉 `net_slot_sendable` 对 `welcomed` 的要求不变红：欢迎在同一次 pump 中最先发出，只有欢迎发送失败（过载）时顺序才会被打乱，loopback 不会出现这种情况。
- 把“槽已认证且会话号一致”放宽为“槽非空”不变红：未认证槽的会话号为 0，编码器拒绝 0，所以仍然不会发出。这两条是纵深防御，没有测试单独钉住。

本机 loopback 与 late_auth 连续 12 次通过。

仍缺：core_app 运行时本身还没有作为客户端运行，所以没有哪个发布二进制会把会话号写进对端 trace；目前只有测试客户端读取它。



## Core App 语音 PCM 泵（2026-11-18）

`core_app_voice.{h,c}` 已进入正式 `core_app_runtime`。本节描述组件本身；它在 `core_app.c` 中的 CLI 与协调器接线见下文「Core App 语音通道」（2026-11-18 补充，早先本节写的“尚未由 core_app.c 调用”已不再成立）。组件固定 48 kHz 单声道、480 帧/包，使用真实采集、播放参考、`AudioVoiceAligner` 和 `AudioVoiceProcessor`，通过 16 项 SPSC 队列把 `BreakVoiceFrame` 交给消费者。手动与 worker 驱动共用 pump；worker 仅使用 reference 专用接口，不直接调用 mixer、网络或模拟状态。

生命周期顺序是 create → reference/capture start → worker，停止时先 join worker，再停 capture/reference，队列不清空。`worker_ready` 握手发布线程 id，外部 pump 在 worker 活跃时返回 REJECTED。满队丢最新包且 sequence 继续推进；统计包含 produced/dropped 和采集/参考 overrun。

`test_core_app_voice` 以 FAKE 设备完成独立处理链逐样本对照、容量/序号、分别缺输入和真实 worker 启停，普通、ASan+UBSan、TSan 均 5/5。九个变异（含队列 relaxed 发布与跳过 join）均判红。

仍缺：CLI 与协调器生命周期、网络 hook/编码/发送、设备丢失恢复、处理尾部排空、漂移补偿及真实声学验证。不得把该组件称为已完成在线语音。

## Core App 语音通道（2026-11-18）

`core_app --voice off|fake|device` 把上节的 `CoreAppVoice` 接入真实可执行程序。默认 `off`，现有 trace 逐字节不变。设计与计划见 `docs/superpowers/specs/2026-11-18-core-app-voice-lane-design.md`、`docs/superpowers/plans/2026-11-18-core-app-voice-lane.md`。

- **fake**：通道自带一个 FAKE 播放 `AudioSystem` 作参考源，采集也是 FAKE。CoreAppThread 每个固定 tick 注入 800 帧 440 Hz、幅度 0.25 的正弦，渲染 800 帧 FAKE 播放，再手动 `pump(4)`。没有 worker 线程，所以 record trace 保持确定性。
- **device**：必须同时给 `--audio=device`，否则 CLI 退出 2。通道借用已打开播放设备的 `AudioSystem`，采集用默认设备并启动 worker。播放通道已降级为 null、采集打不开或启动失败（组件把 `AUDIO_FAILED` 映射为 `BREAK_RUNTIME_UNAVAILABLE`），或采集只落到 miniaudio Null 后端时，trace 写 `event=voice mode=device result=unavailable reason=playback|capture fallback=none|off`：带 `--require-device` 时退出 77，否则通道关闭、运行继续。其他启动错误按普通启动失败处理。`--voice-null-capture` 强制 Null 采集后端，用来在有麦克风的主机上测试这条分支；它只能和 `--voice=device` 一起使用，否则 CLI 退出 2。FAKE 模式的启动错误即使是 UNAVAILABLE 也按 FAILED 处理，不会变成 77。
- **ready 行**：`event=voice mode=<m> result=ready frames=480 capture=<name>`，FAKE 为 `capture=fake`。设备名中的空格、制表符和换行替换成 `_`，因为 trace 按空格分字段；拿不到名字时写 `none`。
- **每个 tick**：所有模式都在音频 drain 之后弹出全部队列帧，检查序号是否逐一递增（不连续计入 `sequence_gaps`），并记录绝对值峰值。DEVICE 模式还检查 worker 错误：worker 在运行中出错（例如采集丢失）时写 `result=failed reason=worker`，以 `stage=voice`、`BREAK_RUNTIME_FAILED` 结束运行，不映射为 77，因为启动时设备是存在的。
- **协调器**：子系统 `voice` 位于 index 1（容量改为 5，audio、render、level 依次后移）。`stop_producers` 停止组件并 join worker（UNAVAILABLE 转为 FAILED），`drain` 弹出剩余帧，`join` 写 `stopped` 行并销毁组件与私有 FAKE 播放。销毁必须放在 join 阶段：audio 的 owner 线程在 audio 自己的 join 回调里关闭借出的设备，而 voice 的 index 更小、先执行。把销毁挪到 destroy 阶段会在 ASan 设备测试中报 heap-use-after-free。启动失败的 rollback 也按 voice 先于 audio 的顺序执行。
- **stopped 行**：`produced consumed dropped sequence_gaps peak capture_overruns reference_overruns`，位于 `runtime_running` 之后、`runtime_stopped` 之前。

测试：

- `test_core_app_voice_lane`（headless）：fake 100 tick，要求 produced≥160、consumed==produced、dropped=0、gaps=0、peak>0、两种 overrun 为 0、ready/stopped 顺序正确；两次运行 trace 逐字节一致；不带 `--voice` 时无 `event=voice`；非法取值、`--voice=device --audio=record`、以及不带 `--voice=device` 的 `--voice-null-capture` 都退出 2，且 stderr 必须是 CLI 诊断而不是 `runtime returned`。这是接线冒烟检查：FAKE 参考静音时处理链近似直通，不衡量回声消除质量。
- `test_core_app_voice_device`（`audio_device`，跳过码 77）：真实设备，要求 capture 名不为 none、produced≥1、consumed==produced、gaps≤dropped，且 voice stopped 先于 audio stopped。本机 PulseAudio「内置音频 模拟立体声」通过。
- `test_core_app_voice_null`（`audio_device`，跳过码 77）：强制 Null 采集，带 `--require-device` 退出 77 且 `fallback=none`，不带时退出 0 且 `fallback=off`，两种情况都不出现 ready 或 stopped 行。没有播放设备的主机上 trace 先出现 `event=audio mode=device result=unavailable`，此时测试报告跳过而不是失败。
- `test_core_app_voice` 第 7 项：采集设备无法启动时 start 与 start_threaded 返回 UNAVAILABLE（先 RED 后 GREEN）。
- TSan：真实 PulseAudio 设备在 libpulse 内部有竞争（栈顶是 libtsan 的 memcpy/recvmsg 拦截器，调用方为 `pa_*`）。`tests/core_app_audio_device_tsan.supp` 只用 `called_from_lib:libpulsecommon-*.so` 与 `called_from_lib:libpulse.so.0`；实测不加 suppress 和改用 `race_top` 都仍报告。
- TSan 补充（2026-11-18）：`test_core_app_voice_null` 虽然采集是 Null 后端，但播放仍打开真实 PulseAudio 设备，在 TSan 树里以同样的 libpulse 竞争失败（未改动的 HEAD 也一样）。现在它与 `test_core_app_audio_device`、`test_core_app_voice_device` 共用这份 suppress 文件，TSan 下 6 项相关测试全部通过。

残余风险：CI 没有音频设备，借用设备的关闭顺序只由本机 ASan 设备测试覆盖（voice/audio 顺序调换的变异只在本机判红）；voice 仍 live 时的 rollback 路径未测。仍缺：编码与通过网络 hook 发送、处理尾部排空、漂移补偿、设备丢失自动恢复和真实声学验收。

## 补充（2026-11-18）：语音帧经网络发送

设计与计划见 `docs/superpowers/specs/2026-11-18-core-app-voice-send-design.md`、`docs/superpowers/plans/2026-11-18-core-app-voice-send.md`。上节「仍缺」里的“编码与通过网络 hook 发送”由此交付（只覆盖服务端发往对端）。

- **消息**：`0x4006` `BREAK_NET_MESSAGE_ID_CORE_VOICE`，v1，只在 AUTHENTICATED 阶段接受，`IDEMPOTENT`，上限 `BREAK_NET_CORE_VOICE_MAX_PAYLOAD`（976 B，一帧 480 样本 BRV1）。载荷是一帧 `break_online_voice.h` 格式；core_app 发 BRV2（IMA ADPCM），单声道 480 样本为 `BREAK_VOICE_ADPCM_SIZE(1, 480)` = 260 B。注册表 count 27 / 26。
- **hook**：`CoreAppNetworkHooks` 新增可选 `voice_frame(user, frame)`，传一帧 PCM（`BreakVoiceFrame *`，只在调用期间借出，没有返回值）。为 NULL 时行为不变，`start` 校验不要求它。编码在传输层做，所以运行时库不链接编解码器。
- **调用点**：`app_voice_consume`（CoreAppThread，每个 tick 和 voice drain）弹出每帧后统计序号与峰值，再在网络子系统 live 时把 PCM 帧交给 hook。没有 hook 时不调用，离线 trace 不变。
- **传输**：`net_voice_frame` 先检查 `started && producing` 且 reactor 事件队列为空，不满足时整帧丢弃并计 `voice_frames_skipped`（不编码）；满足时用 `break_voice_encode_adpcm` 编成 BRV2（单声道 480 样本 260 B）发给每个已欢迎的存活连接。NULL 帧也计为 `voice_frames_invalid`。语音是实时数据，不排队、不重发。编码失败（上游缺陷）计 `voice_frames_invalid` 并丢弃。发送结果计入 `voice_frames_sent`（按对端计）、`send_overloads`、`send_closed`。`network_stats` 末尾追加 `voice_frames_sent=N voice_frames_skipped=M voice_frames_invalid=X`。
- **顺序**：network 是 index 0，在每个阶段都先于 voice（index 1）。network `stop_producers` 之后 voice drain 弹出的帧只会被计为 skipped；network destroy 之后 `app_network()` 返回 NULL，hook 不再被调用。
- **服务端只发不收**：对端发来的 `0x4006` 没有处理函数，会话层计为 `handler_failed`，连接不关闭。voice 模式测试覆盖：对端回发一条语音后仍能收到下一个 snapshot（`v_session_survives_voice_sent`）。`session_handler_failed` 本身不作判据，因为其他流量已经会让它大于 1。
- **链接**：编码器只在传输层使用，因此 `core_app_runtime` 的链接列表保持不变（`_core_app_runtime_expected` 仍是 HEAD 版本），只有 `core_app` 在启用传输时额外链接 `break_online`。这样离线 `core_app` 和 `core_app_asset_bake` 都不会被传递拉到 `break_crypto`/libcrypto。`net_recvfrom` 由 engine 的 `network.c` 在最终链接时提供。离线合同测试除了 `break_net_`/`break_session_`/snow，还检查二进制里没有 `break_voice_`/`break_crypto_` 符号（已确认 `readelf -d core_app | grep libcrypto` 为空）。

验证：

- `test_break_session`：`0x4006` 的字段与 count（先 RED：宏未定义）。
- `test_core_app_network_voice`（transport 构建、非 WIN32）：真实 core_app `--voice=fake --network` 跑 loopback 场景，对端 V 认证后收 30 条语音消息，逐条检查 v1、`BRV2`、48000 Hz、单声道、480 样本、恰好 260 B、序号连续，再经真实 `BreakVoiceReceiver` 解码。客户端用按序号驱动的虚拟播放时钟（`(sequence - first) × 10 ms`），网络抖动不会触发补帧；服务端跳过的帧会被补一次，其后的帧照常播放。要求报告 `voice frames=30 malformed=0 played=30`、`gaps <= voice_frames_skipped`（传输层按设计会丢弃来不及发送的帧，例如时钟回复还在排队时）、峰值 ≥ 4000（0.25 幅度音调约 8191，实测 8208），`voice_frames_sent >= 30`，voice ready/stopped 行正常，且非 network trace 与离线 `--voice=fake` 运行逐行相同。先 RED（收到 0 帧）后 GREEN。
- `test_core_app_net_transport` 新增 `voice_frame_counts_invalid_and_skipped_frames`：生产中传 NULL 与 `sample_count=0` 得 invalid=2，`stop_producers` 后两帧得 skipped=2。删掉跳过检查的变异判红。
- `test_break_online_voice` 新增 `voice_sequence_clock_conceals_a_skipped_frame_and_plays_the_next`：序号 7、8、10、11 在序号时钟下播放 4 帧、补 1 帧（序号 9）。
- 变异：删掉 hook 调用、改发 BRV1，都让 `test_core_app_network_voice` 失败。

仍缺：服务端接收与混音对端语音、按对端路由或静音、真实对端上的抖动与漂移处理、尾部排空、设备恢复、Opus。

## 补充（2026-11-18）：服务端接收对端语音

设计与计划见 `docs/superpowers/specs/2026-11-18-core-app-voice-receive-design.md`、`docs/superpowers/plans/2026-11-18-core-app-voice-receive.md`。上节「仍缺」里的“服务端接收对端语音”和“尾部排空”由此交付（只接收与统计，不混音、不转发）。

- **处理函数**：`net_start` 为 `0x4006` 注册 `net_on_voice`。它在 CoreAppThread（会话层 poll）上运行，会话层已保证只有 AUTHENTICATED 阶段的消息能到达。找不到槽位或槽位正在关闭时返回 false（会话层计 `handler_failed`）。这里不用 `net_slot_live`：`authenticated[slot]` 要等本批事件处理完后的 `net_sync_sessions` 才置位，和 AUTH 同一批到达的语音会被误拒。空载荷计入 `voice_frames_dropped` 并返回 true。其余情况把载荷推入该连接的 `BreakVoiceReceiver` 并立刻 pump 一次，所以接收器的 inbox 最多只存一条。
- **每连接抖动缓冲**：接收器在该连接第一条语音到达时创建：48 kHz、单声道、480 样本，`jitter_delay_ms = 40`，`jitter_capacity = 64`（接收器上限，TLS 是有序流，突发到达的帧不会溢出），`queue_capacity = 4`。创建失败时这条消息被拒绝，下一条重试。
- **播放**：`net_tick` 在 `net_pump` 之后按单调时钟弹出到期帧，每个槽位每 tick 最多 16 帧，只要 tick 不超过 160 ms 就能跟上一路 10 ms 帧流；服务端更慢时会落后，接收器随后计 overload。上限的作用是：如果对端发来序号跳得很远的一帧，接收器不会在一次循环里补出中间所有缺失帧。播放出的帧只更新 `voice_peak`（最大绝对样本值），补帧计入 `voice_frames_concealed`。对端语音不会到达关卡、模拟、音频设备或语音通道。
- **尾部排空**：连接关闭或传输出错时释放槽位，`net_destroy` 也会释放所有槽位，都在输出统计之前完成。释放时先用 `now = UINT64_MAX` 弹出剩余帧（最多 128 帧），对端关闭前发出的帧按序播放或补帧，然后把接收器统计加到总数里，再销毁接收器。排空上限没覆盖到的已接收帧（例如对端在播放开始前送来序号相差很远的两帧）计入 dropped。释放必须在创建接收器的线程（传输层所属线程）上进行，否则接收器拒绝 stats 和 destroy。
- **统计**：`network_stats` 末尾追加 `voice_frames_received`（接收器 accepted）、`voice_frames_played`、`voice_frames_concealed`、`voice_frames_dropped`（invalid + duplicate + stale + overload）和 `voice_peak`。格式错误、格式不符、重复、过期或溢出的帧只计数，连接保持打开。统计行缓冲从 1024 扩到 1536 字节。

验证：

- `test_break_online_voice` 新增 `voice_pop_at_max_time_flushes_buffered_frames_in_order`：40 ms 延迟下缓冲 3 帧，`now = 0` 时没有帧到期；之后用 `UINT64_MAX` 按序弹出 5、6、7，都不是补帧，然后没有剩余帧。这条测试固定了尾部排空依赖的接收器行为。
- `test_core_app_network_voice`：对端 V 解码完服务端的 30 帧后，一次性回发 20 帧 0.25 幅度方波 BRV2（序号 0..19），再发序号 19 的重复帧和一帧声明 16 kHz 的帧，然后发一个时钟探测。同一会话的消息按序处理，所以探测回复证明服务端已经处理完全部语音，对端收到回复后立即关闭。由于 40 ms 播放延迟，对端关闭时大部分帧还在缓冲里，只能靠尾部排空播放。driver 要求 `voice_frames_received=20 voice_frames_played=20 voice_frames_concealed=0 voice_frames_dropped=2`、`voice_peak >= 4000`（实测 9334），并且非 network trace 仍与离线运行一致。
- 先 RED（统计里没有新字段）后 GREEN。第一版测试按 10 ms 间隔发送且没有屏障，只统计到 1 帧丢弃，因为对端关闭时服务端还没读到最后一条消息。之后加了时钟探测屏障，并改为突发发送。
- `test_core_app_net_transport` 的统计行断言加上五个新字段（全部为 0）。
- 变异：不注册处理函数、去掉尾部排空、不更新峰值，三者都让 `test_core_app_network_voice` 失败。

仍缺：混音或播放对端语音、对端之间转发、按对端静音、漂移补偿、语音专用限速（目前只有会话层通用限速）、采集设备恢复、Opus。

## 补充（2026-11-18）：语音采集设备自动恢复

设计与计划见 `docs/superpowers/specs/2026-11-18-core-app-voice-recovery-design.md`、`docs/superpowers/plans/2026-11-18-core-app-voice-recovery.md`。前几节「仍缺」里的“设备恢复”由此交付（只覆盖采集设备）。

- **组件**：`CoreAppVoiceConfig.reopen_interval_ms` / `max_reopen_failures`。`max_reopen_failures = 0` 时行为不变。否则 `core_app_voice_pump` 发现采集丢失时，每次调用最多尝试一次 `audio_capture_reopen(capture, NULL)`（重开默认输入），两次尝试至少间隔 `reopen_interval_ms`（单调时钟）。成功：`capture_recoveries++`，连续失败计数清零，丢弃丢失期间渲染的播放参考（没有对应的采集，留着会让回声消除错位），重置 voice processor，同一次调用继续处理。失败：`capture_reopen_failures++`，未到上限时 pump 返回 OK 且不出包；连续失败达到上限后返回 UNAVAILABLE，worker 以该错误退出（与原行为一致）。
- **线程**：`audio_capture_reopen` 是 owner 线程调用。threaded 模式只有 worker 调 pump，所以由 worker 重开；manual 模式由泵线程重开。设备回调仍只写环形缓冲和 lost 标志。
- **core_app**：device 模式配置 100 ms 间隔、50 次（约 5 s）。fake 模式不启用（其采集不会丢失）。voice `result=stopped` 行末尾追加 `capture_recoveries=N capture_reopen_failures=M`；`test_core_app_voice_lane.cmake` 要求 fake 模式两者为 0，`test_core_app_voice_device.cmake` 接受任意值。设备 lane 只有在恢复用尽后才以 `reason=worker` 失败。
- **测试钩子**：`AUDIO_CAPTURE_EVENT_REOPEN_REFUSED`（FAKE/NULL 后端）让下一次 reopen 返回 FAILED 且保持丢失状态，每个事件只拒绝一次；DEFAULT 后端返回 REJECTED。

验证：

- `test_audio_capture` 新增 `a_refused_reopen_keeps_the_device_lost_once_per_event`（先 RED：枚举未定义）：FAKE 两次拒绝后第三次成功；拒绝事件本身不算丢失也不算 reroute；NULL 设备拒绝一次后重开并恢复实时采集。
- `test_core_app_voice` 新增五项（先 RED：配置与统计字段不存在）：丢失期间渲染 3 包参考后恢复，积压降到一包以下且序号连续；两次拒绝后第三次恢复、恢复后计数清零（再拒绝三次才 UNAVAILABLE，累计 failures=5）；10 s 间隔内不重试；worker 在运行中恢复且 worker error 保持 OK。原有 `worker_error_and_capture_backend_are_visible_while_running`（未启用恢复）仍得到 UNAVAILABLE。
- 新增 `a_reopened_capture_processes_like_a_fresh_pipeline`：重开后第一包与新建 aligner + processor 处理同一输入逐样本一致；去掉 processor 重置或去掉旧采集帧丢弃都会失败。
- 变异：不调用 reopen（3 项失败）、恢复后不清零（1 项）、不丢弃积压（1 项）。

仍缺：按名称切换到其他输入设备、播放参考设备恢复、漂移补偿、真实声学验证、Opus。

## 补充（2026-11-18）：播放设备自动恢复

设计与计划见 `docs/superpowers/specs/2026-11-18-core-app-playback-recovery-design.md`、`docs/superpowers/plans/2026-11-18-core-app-playback-recovery.md`。上一节「仍缺」里的“播放参考设备恢复”由此交付。

- **AudioSystem**：新增 `audio_system_lost`、`audio_system_reopen`、`audio_system_simulate_event`（`AUDIO_SYSTEM_EVENT_DEVICE_LOST`、`AUDIO_SYSTEM_EVENT_REOPEN_REFUSED`，仅 FAKE/NULL）。模拟丢失事件，或真实设备持续处于非 started 状态至少 250 ms（`AUDIO_DEVICE_LOSS_GRACE_US`，用于容忍 PulseAudio 挂起、WASAPI 重路由等后端自行停启），才算丢失；不再依赖 stop 通知。重开在同一块内存里关闭旧设备、以相同声道数和采样率打开默认输出并启动；后端已自行重启的设备不动、不计恢复。声源、总线、听者和播放参考环都在 node graph 里，不受影响。`audio_system_recoveries` 返回真正替换设备的次数。
- **上下文归属**：`audio_system_create_ex` 现在为所有设备后端自建并持有 context（以前只有 NULL 后端这样做）。默认后端原来由设备持有 context，而 engine 和 resource manager 一直引用该 context 的 log，重开时会被一起释放。创建时按 `ma_get_enabled_backends` 顺序逐个尝试后端（与 miniaudio 自身回退一致），iOS 上 context 使用 playback session category。
- **core_app**：device 模式 start 时设为 100 ms × 50 次。同步 drain 在处理命令前检查一次；有 owner 线程时，owner 在应用每条命令前检查。丢失期间命令照常送到系统，设备恢复后，期间启动的声源会继续播放。连续拒绝达到上限后 drain（或 owner 错误）为 `BREAK_RUNTIME_FAILED`，与其他设备错误一样让当帧失败。`max_reopen_failures = 0` 时第一次丢失就失败。
- **trace**：device 模式 `result=stopped` 行在 `owner_thread` 之后追加 `device_recoveries=N device_reopen_failures=M`。`test_core_app_audio_device.cmake` 要求这两个字段。
- **语音通道**：参考环属于系统，重开不会释放它，但重开期间参考帧中断。voice pump 每次先比较 `audio_system_recoveries`，变化时丢弃超出参考积压的最旧采集帧并 reset processor，避免回声消除把新采集与旧参考配对。`CoreAppVoiceStats.playback_recoveries` 计数，voice `result=stopped` 行在 `capture_reopen_failures` 之后追加 `playback_recoveries=N`（fake 合同要求 0）。
- **阻塞代价**：每次重开尝试会阻塞 owner 线程，时长等于后端打开设备的耗时；100 ms × 50 次约 5 s 只是下限，期间队列满时生产方收到 OVERLOAD。

验证：

- `test_audio` 共 36 项，新增七项（先 RED：API 未定义）：NULL 后端丢失后重开，参考环重新收到帧；NULL 设备停止超过宽限期后判定丢失并重开；后端自行重启的设备不判丢失、不重开；重开失败关闭的设备不报告名称；FAKE 两次拒绝后第三次成功；参数校验；真实默认输出重开后继续渲染（无后端主机跳过）。
- `test_core_app_voice` 共 13 项，新增 `a_playback_reopen_drops_capture_that_has_no_reference`。
- `test_core_app_runtime` 新增四项（先 RED：字段不存在）：同步 drain 恢复；两次拒绝后恢复、恢复后计数清零，再拒绝三次第三次 drain 返回 FAILED；10 s 间隔内不重试；owner 线程恢复且所有设备调用仍在 owner 上。原有四条 stopped 行断言追加两个字段。
- 变异：不调用 reopen（3 项失败）、恢复后不清零（1 项）、忽略间隔（1 项）；pump 不跟随播放重开（`test_core_app_voice` 失败）；reopen 不跳过已启动设备（`a_device_restarted_by_the_backend_is_not_lost_or_reopened` 失败）。
- `build-core-app-net` 全量 446/446；ASan+UBSan 与 TSan 树中 9 项音频/语音测试全部通过；真实 PulseAudio 合同输出 `device_recoveries=0 device_reopen_failures=0`。

仍缺：按名称切换输出或输入设备、漂移补偿、真实声学验证、对端语音混音与转发、Opus。


## 补充（2026-11-18）：按名称选择音频设备

设计与计划见 `docs/superpowers/specs/2026-11-18-named-audio-devices-design.md`、`docs/superpowers/plans/2026-11-18-named-audio-devices.md`。上一节「仍缺」里的“按名称切换输出或输入设备”由此交付。

- **AudioSystem**：`audio_system_list_devices(backend, out, capacity)` 与采集列表同一约定（NULL 后端为 "NULL Playback Device"，FAKE 为 0）。`audio_system_create_named` 空串等同 NULL；FAKE 带名称、名称不存在为 REJECTED，打开失败为 FAILED，`*out` 只在成功时写入。`audio_system_switch_device` 先分配并初始化新设备（停止状态），失败或模拟拒绝时释放新设备、旧设备继续播放并返回 FAILED；成功后关闭旧设备、替换、启动并计一次恢复。名称 ≥ 128 字节为 REJECTED。`audio_system_reopen` 打开已选名称，名称消失时打开默认并保留选择。
- **语音**：`CoreAppVoiceConfig.capture_device_name` 在 create 时复制。采集恢复时先重开该名称；返回 REJECTED（设备已移除）时同一次尝试改开默认输入，不计拒绝。
- **core_app**：`core_app_audio_start_device_named`，原有 start 函数传 NULL。`CoreAppConfig.audio_device_name`、`voice_capture_device_name`；CLI `--audio-device NAME`（需 `--audio=device`）、`--voice-capture-device NAME`（需 `--voice=device`，与 `--voice-null-capture` 冲突）。未知名称写 `COREAPPTRACE version=1 event=audio mode=device result=rejected reason=device_name`（或 `event=voice ...`），返回 REJECTED，即使没有 `--require-device` 也不降级为 null，最终 exit 2（不是 77）。
- **合同**：`test_core_app_named_device.cmake` 在任何主机上检查未知播放名称（两种 require 组合）exit 2 与 rejected 行、两个 CLI 依赖错误；有播放设备时再检查未知采集名称，并从默认 ready 行解析设备名、按名称重开，要求 ready 行为同一设备；无设备时报告跳过。

验证：`test_audio` 47 项（含名称长度一致拒绝、切换启动失败恢复旧设备、旧设备也启动失败时由 reopen 修复、无 context 的 reopen、按选择重开）、`test_core_app_voice` 14 项、`test_core_app_runtime` 55 项，新增项均先 RED。变异判红（见 spec Result）。本机 PulseAudio "内置音频 模拟立体声" 按名称重开成功。

补充：
- `audio_system_switch_device` 的启动失败不再留下未播放的设备：关闭新设备、还原选择，在同一块内存重开旧设备（名称或默认）后返回 FAILED，旧输出继续播放，不计恢复。旧设备也打不开或启动不了时，设备块仍留在 engine 上（清零或已打开未启动），之后的 `audio_system_reopen` 能修复，`engine->pDevice` 不会变成 NULL。
- `create_named` 与 `switch_device` 对 ≥128 字节的名称给出同样的 REJECTED，不再静默截断。
- `audio_reopen_device` 在 `context_initialized` 为假时不查名称，直接开默认设备。
- rejected trace 行写入失败时返回 FAILED（与 ready 行一致），不再 exit 2 却没有原因行。

仍缺：运行中通过命令或 UI 切换设备、漂移补偿、对端语音混音与转发、按对端静音、Opus、真实声学验证。

## 补充（2026-11-19）：服务端语音转发

- **协议**：`0x4007` core_app voice relay，服务端发往对端，v1..1，`AUTHENTICATED`，`IDEMPOTENT`，上限 `BREAK_NET_CORE_VOICE_RELAY_MAX_PAYLOAD` = 992 B。小端布局：`[0]` u32 magic `0x594C5256`（"VRLY"），`[4]` u32 保留 0，`[8]` u64 来源会话号（非零，即来源对端在 welcome 中收到的号），`[16]` 来源发来的原样帧（1..976 B，一帧 BRV1 或 BRV2）。`core_app_voice_relay_decode` 只检查长度、magic、保留字段和来源号，返回指向载荷内的帧指针，不解析帧；失败时不写输出。transport 用 `#error` / `_Static_assert` 绑定 id、总上限和帧上限与注册表一致。单独用新 id 而不复用 `0x4006`，因为不同来源的序号互相独立，客户端需要按来源分开抖动缓冲。
- **服务端**：`--voice-relay`（`CoreAppNetTransportConfig.voice_relay`）默认关闭，属于网络选项，没有 `--network` 时报 "network options require --network"。`net_on_voice` 在 push/pump 前后读取接收器 stats，只有 `accepted` 增加时才把帧复制进 32 项转发环；来源号取 `break_session_manager_session_id`，因为语音可能与 AUTH 同批应用，此时槽位自己的 session id 还没记录。处理函数本身不发送；`net_send_pending` 在事件队列为空时，于 welcome 之后、时钟回复之前，把每帧编码一次，发给每个 `net_slot_sendable` 且会话号不等于来源的槽位。每次成功发给一个接收方计一次 `voice_frames_relayed`（3 个对端时 20 帧计 40），overload / closed 计入已有计数；环满、编码失败或销毁时仍在环中的帧计 `voice_relay_dropped`。服务端自身抖动缓冲判为 overload（64 槽已满）或 stale（播放开始后才到）的合法帧不转发，尽管接收方有自己的缓冲；排队时尚未 welcome 的对端被 welcome 后仍会收到环中最多 32 帧旧帧。服务端不为 `0x4007` 注册处理函数：对端发来的 `0x4007` 记为 `handler_failed`，连接保持。
- **确定性**：转发只改 transport 状态，非网络 trace 与离线运行一致；编解码是纯字节打包，离线构建不引入语音编解码或 crypto（已有 nm 检查）。
- **合同**：`test_core_app_network.cmake` 新增 MODE=voice_relay（服务端加 `--voice-relay`）和 MODE=voice_relay_off。对端 A、B 认证；A 发 20 帧音调、1 帧重复、1 帧错误采样率，再用时钟探测作屏障；B 发一条 `0x4007` 给服务端后用时钟探测作屏障，途中统计转发消息并用真实接收器解码。开启时要求 B 收到 `received=20 foreign=0 gaps=0 malformed=0 played=20`、peak ≥ 4000，A 收到 0 条，`voice_frames_relayed=20`；关闭时 B 收到 0 条，`voice_frames_relayed=0`。两种模式都要求 `authenticated=2`、`voice_frames_received=20`、`voice_frames_dropped=2`、`voice_relay_dropped=0`、`session_handler_failed ≥ 1`，以及非网络 trace 与离线一致。

验证：全量 449/449；开启网络传输的 ASan+UBSan 树（`build-voice-relay-asan`）中网络相关 11 项通过。变异（不排除来源、不受开关控制、不看 accepted 计数）分别使 voice_relay、voice_relay_off、voice_relay 判红。

仍缺：对端语音混音、按对端静音、语音专用限速、漂移补偿、运行中通过命令切换设备、Opus、真实声学验证。

## 补充（2026-11-19）：按用户屏蔽语音

- **协议**：`0x4008` core_app voice mute，对端发往服务端，v1..1，`AUTHENTICATED`，`IDEMPOTENT`，恰好 `BREAK_NET_CORE_VOICE_MUTE_PAYLOAD` = 16 B。小端布局：`[0]` u32 magic `0x54554D56`（"VMUT"），`[4]` u32 flags（bit 0 = 屏蔽，0 = 取消屏蔽，其余位必须为 0），`[8]` u64 目标会话号（非零，与转发头里的来源号相同）。decode 检查长度、magic、未知 flag 位和零目标，失败时不写输出。transport 用 `#error` / `_Static_assert` 绑定 id 和大小。
- **服务端**：`net_on_voice_mute` 在 CoreAppThread 上运行。槽位不存在或正在关闭时返回 false（会话层计 `handler_failed`）；载荷过短、magic 错误、含未知 flag 位或目标为零时计 `voice_mute_rejected`，连接保持；超过 16 字节的载荷在会话层的 payload 上限检查处就关闭连接，到不了处理函数。每个解码成功的请求计 `voice_mute_requests`。每个槽位最多保存 `CORE_APP_NET_VOICE_MUTE_CAPACITY` = 16 个来源号：屏蔽时不存在才加入，取消屏蔽时移除，两者都幂等；列表已满时再屏蔽新来源计 `voice_mute_rejected`。会话号不复用，已离开的用户的号留在列表里无害。槽位释放（连接关闭或传输错误）和复用时清空列表，新连接不会继承屏蔽。`net_send_voice_relay` 对列表中含该帧来源的接收方跳过发送并计 `voice_frames_muted`（每个被跳过的接收方计一次）；屏蔽在发送时检查，因此也作用于转发环中已排队的帧。未开 `--voice-relay` 时屏蔽请求照常处理，只改计数。
- **合同**：`test_core_app_network.cmake` MODE=voice_mute（服务端加 `--voice-relay`）。B 发一条 flags=3 的畸形请求，再屏蔽 A 两次，用时钟探测作屏障；A 发第一组（序号 0..19 加 1 帧重复、1 帧错误采样率）并作屏障，B 的屏障途中不得收到转发；B 取消屏蔽一次（重复屏蔽没有存两份），再屏蔽 17 个不存在的会话号（第 17 个因列表已满被拒），然后作屏障；A 发第二组（序号 20..39）并作屏障，B 必须收到 20 条、来源为 A、从 20 开始连续、全部解码、peak ≥ 4000。服务端要求 `voice_frames_received=40`、`voice_frames_dropped=4`、`voice_frames_relayed=20`、`voice_frames_muted=20`、`voice_mute_requests=20`、`voice_mute_rejected=2`、`voice_relay_dropped=0`，非网络 trace 与离线一致。

验证：全量 450/450；`build-voice-relay-asan`（ASan+UBSan，网络开启）相关 12 项通过。变异（转发忽略屏蔽、取消屏蔽不移除、解码不查未知 flag 位）都使 voice_mute 判红。

仍缺：对端语音混音、语音专用限速、漂移补偿、运行中通过命令切换设备、Opus、真实声学验证。

## 补充（2026-11-19）：语音限速

- **限额**：`CORE_APP_NET_VOICE_RATE_PER_SEC` = 120 帧/秒（一路 10 ms 语音 100 帧/秒，加 20% 抖动余量），`CORE_APP_NET_VOICE_RATE_BURST` = 64 帧（与抖动缓冲容量相同）。字节桶为每秒 120 × 976 B、突发 64 × 976 B，任何合法帧都不会先触发字节限制。时钟用 transport 的 `time_microseconds() / 1000`，与抖动缓冲一致。
- **服务端**：每个槽位一个 `BreakMsgRate`（`src/network/break_msg_rate.h`）和就绪标志。`net_on_voice` 在槽位检查与空载荷检查之后、接收器 push 之前初始化（第一条语音时）并检查限速；超限时计 `voice_frames_rate_limited` 并返回 true，帧不进入接收器，因此不计入 received、dropped，也不会被转发。`net_voice_release` 复位就绪标志，连接关闭或复用后桶重新装满。会话层的 `break_session_manager_set_message_rate` 保持关闭，因为它会同时限制快照、物理和时钟消息，而这些消息的速率不同。`network_stats` 追加 `voice_frames_rate_limited`。突发上限 64 帧大于 32 项的转发环：一次 pump 内集中到达的 64 帧最多转发 32 帧，其余计 `voice_relay_dropped`；按 100 帧/秒正常到达的语音流不会这样集中。
- **合同**：`test_core_app_network.cmake` MODE=voice_flood（服务端加 `--voice-relay`）。A 以 TLS 能达到的最快速度连续发 200 帧，然后 A 和 B 各用时钟探测作屏障。要求 `voice_frames_rate_limited ≥ 1`、`voice_frames_received ≥ 64`、received + rate_limited ≤ 200 且 received + dropped + rate_limited ≥ 200、`voice_frames_relayed ≥ 1` 且 relayed + relay_dropped ≤ received，B 收到的转发数恰好等于 `voice_frames_relayed`，A 收不到自己的帧，非网络 trace 与离线一致。voice、voice_relay、voice_relay_off、voice_mute 合同要求 `voice_frames_rate_limited=0`。

验证：本机一次运行为 received=64、rate_limited=136、relayed=64，B 收到 64 条。全量 451/451；`build-voice-relay-asan` 相关 13 项通过。变异（不检查限速、每条消息都重置限速器）都使 voice_flood 判红。

仍缺：对端语音混音、漂移补偿、运行中通过命令切换设备、Opus、真实声学验证。

## 补充（2026-11-19）：网络合同的验证范围

`test_core_app_network_*`（loopback、late_auth、voice、voice_relay、voice_relay_off、voice_mute、voice_flood、start_failure）只在 `_core_app_net_transport AND NOT WIN32` 时注册（`engine/CMakeLists.txt`），而 `CORE_APP_ENABLE_NETWORK` 默认关闭，`.github/workflows` 中没有任何 lane 打开它或 `BREAK_ENABLE_SNOWFLAKE`。所以远程 CI 的绿灯不覆盖这些网络合同，它们只在本机开启网络的构建树（`build-core-app-net`，以及 ASan+UBSan 的 `build-voice-relay-asan`）中运行。增加 CI lane 需要能拉取固定提交的 Snowflake 源码，而 `konyka/snowflake` 是私有仓库：没有凭据时匿名克隆和 API 都被拒绝。需要仓库所有者添加只读 deploy key 或 token 作为 Actions secret，之后才能加一个 Linux lane（`-DBREAK_ENABLE_SNOWFLAKE=ON -DCORE_APP_ENABLE_NETWORK=ON -DBREAK_ENABLE_CRYPTO=ON -DSNOWFLAKE_SOURCE_DIR=...`，运行 `ctest -L network`）。

## 补充（2026-11-19）：运行中切换播放设备

- **scenario 文法**：`<tick> audio-device <name>` 与 `<tick> audio-device`。名称取命令后一个空格之后的整行，因此可以含空格（如 "NULL Playback Device"）；长度 1..`CORE_APP_SCENARIO_DEVICE_NAME_MAX`（127）字节，不能以空格开头或结尾，不能含 0x00–0x1F 或 0x7F，否则整个 scenario 无效。没有名称表示切回默认设备。新事件类型 `CORE_APP_SCENARIO_AUDIO_DEVICE`，名称存入 `event.path`。`app_scenario_supported` 接受它。
- **音频层**：`core_app_audio_request_device(audio, name)` 排入 `CORE_APP_AUDIO_SWITCH_DEVICE` 命令（`CoreAppAudioCommand.device_name`，容量 128）。只有 device 模式且系统已打开时接受；record / null 模式和 ≥128 字节的名称返回 REJECTED，队列满返回 OVERLOAD，停止接收后返回 CLOSED，这些情况都不入队。命令不带 generation，不经过 slot 检查。owner 线程（或没有 owner 时调用 drain 的线程）调用 `audio_system_switch_device`：OK 计 `device_switches` 并更新记录的设备名，写 `event=audio_device result=switched device=<name>|default`；REJECTED 计 `device_switch_rejected`，写 `result=rejected reason=device_name`；其余结果计 `device_switch_failures`，写 `result=failed`。只有 trace 写入失败才让 drain 失败；切换失败后若没有设备在播放，由已有的播放设备自动恢复处理。切换调用计入 `device_calls_on_owner` / `device_calls_off_owner`。
- **core_app**：scenario 事件调用该请求；请求被拒时写 `event=audio_device result=rejected tick=N reason=mode|overload|closed` 并继续运行。
- **trace**：device 模式 `result=stopped` 行在 `device_reopen_failures` 之后追加 `device_switches=N device_switch_rejected=M device_switch_failures=K`。
- **合同**：`test_core_app_named_device.cmake` 在任何主机上检查 record 模式下 `audio-device no such speaker` 被拒（`reason=mode`）且 exit 0；有播放设备时运行切到默认设备名称、切到未知名称、切回默认的 scenario，要求三行按顺序出现、stopped 行为 `device_switches=2 device_switch_rejected=1 device_switch_failures=0`、exit 0。

- **评审后的修改**：switched 行里名称中的空白（空格、制表符、换行）替换成 `_`，让 trace 仍按空格切分；合同比较前对 ready 行的名称做同样替换。切换成功后把 `consecutive_reopen_failures` 清零，避免旧的重开失败计数影响新设备。请求参数无效（NULL audio 等）时 core_app 写 `reason=invalid`。`fuzz_core_app_scenario` 的替换表加入 6 条 audio-device 变体（带空格名称、无名称、首尾空格、控制字符、超长名称）。
- **已知限制**：ready 行的 `device=<name>` 仍原样输出，名称含空格时按空格切分会截断。这是按名称选择设备时就有的格式，named_device 合同依赖原样名称，本切片不改。

验证：`test_core_app_runtime` 59 项、`test_core_app_named_device`（本机 PulseAudio 运行中切换成功）；全量 451/451；ASan+UBSan 与 TSan 树相关 10 项通过。变异（未知名称当作切换、record 模式接受、切换不在 owner 线程）都判红。

仍缺：运行中切换采集设备、UI 或控制台入口、对端语音混音、漂移补偿、Opus、真实声学验证。
