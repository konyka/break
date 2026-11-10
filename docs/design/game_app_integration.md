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

当前证据仅为 Linux CPU 构建、configure 和真实进程 CLI。没有运行游戏场景、真实 Vulkan/OpenGL 窗口、音频设备或网络；record/headless 也不能解释为 GPU 画面。后续任务必须分别提供这些证据。

## P12 Task 2：离线资产与 checkpoint v1

### 固定关卡与 baker

`game_asset_bake --output DIR` 是独立 C11 离线工具；目标在 `ENGINE_BUILD_TESTS=OFF` 时也存在。它不调用 `game_app_run()`，不创建 RHI 设备、音频设备、网络或跨线程所有权。源树正式资产只由该命令显式生成，测试使用 per-process 临时目录。

`level.bscn` 由真实 `scene_save_binary` 写出并由 `scene_probe_binary`/`scene_load_binary` 回读。固定实体顺序为 Ground、Player、Enemy、DynamicWall、Vehicle、VisibleColor、HiddenColor；`actors.sidecar` 逐行使用 P1 已有的 `entity-index class-name` 格式。七个实体共享一份真实 CPU cube 几何（24 vertices、36 indices），通过 `SerializeOptions.read_mesh_geometry` 交给 BSCN writer；没有 GPU readback。七个节点使用各自的变换和颜色材质，隐藏颜色节点保留 mesh/material 引用但初始 `has_mesh=false`。场景实体和 Flow 目标只保存 `(index, generation)`，没有持久化 C 指针。

`level.fg` 由 `break_flow_serialize` 生成，包含 enter → delay(30 ticks) → add-item 的两条 exec link。`director.lua` 和 `player.lua` 可由真实 `break_lua` 加载，`broken.lua` 是明确的语法错误 fixture；本任务不建立游戏 VM 生命周期。`level.banm` 由 `anim_codec_encode` 生成，含 translation/rotation/scale 三个通道，测试用 `anim_codec_decode`、`anim_codec_time_error_bound`、`anim_codec_scalar_error_bound` 和旋转误差界验收。`tone.wav` 是固定 seed 的 44100 Hz、mono、16-bit PCM，4410 个样本；没有音频设备或听测证据。

三个 `.scenario` 文件是版本化固定输入资产，由同一 baker 生成；场景脚本解析和生命周期执行属于后续任务，本任务没有声称它们已运行。

### checkpoint v1 格式与事务

`manifest.game` 为显式小端二进制：40 字节头加每条 88 字节记录。头依次是固定 8 字节 `GAMECKPT`（无额外 NUL）、version=1、header_bytes=40、exact_total_size(u64)、generation(u64)、file_count(u32)、reserved(u32)。记录依次是 kind(u32)、name_length(u32)、size(u64)、FNV-1a-64(u64)、64 字节以 NUL 结尾并零填充的 basename。FNV 只用于损坏检测，不是安全认证。

每代 1..16 个文件，每文件最多 64 MiB，basename 最多 63 字节且只允许 ASCII 字母数字、`_.-`；路径分隔符、绝对路径、`..`、`.` 和 `manifest.game` 均被拒绝。容量或长度超限返回 `BREAK_RUNTIME_OVERLOAD`，不静默截断。读取先验证完整 manifest 和所有记录，再逐文件以固定 4096 字节缓冲 staging 校验精确长度和 hash，无需按 payload 大小分配。

调用者先以新 generation 名写 payload，避免覆盖旧 manifest 引用的文件。`game_checkpoint_write_manifest_ex` 先重新读取并校验所有新 payload，再用一个 `PlatformAtomicWriter` 提交 manifest。write、file-fsync、close 或 rename 在目标替换前失败时返回 `BREAK_RUNTIME_FAILED`，结果为 `GAME_CHECKPOINT_COMMIT_NOT_COMMITTED`，旧 manifest 不变，并按既有安全规则清理新 payload。rename 成功后 directory open/fsync 失败时返回逻辑 `BREAK_RUNTIME_OK`，结果为 `GAME_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN`，新 manifest 与 payload 保留，不执行恢复 rename。旧 `game_checkpoint_write_manifest` 保留逻辑提交 API，OK 也可能表示 unknown；需要 durability 区分的调用必须使用 `_ex`。`game_checkpoint_probe` 不修改任何 World/Level；真实运行状态反序列化、资源重建和事务 load 属于后续任务。

### 已执行的 Task 2 证据

Linux 上 `test_game_app_assets` 为 9/9，通过两回 baker 逐字节比较、BSCN+P1 sidecar、Flow、BANM、WAV、Lua、manifest 格式、payload/manifest 损坏、非法名称/容量和 RLIMIT_FSIZE 中途写失败回滚。相关 `test_scene_serial`、`test_break_flow_serial`、`test_anim_compression`、`test_break_game_level`、`test_platform_fs_write`、`test_break_lua_module` 与新增测试合计 7/7 通过。

生产变异临时删除 payload hash 比较后，篡改用例如期失败（8 通过、1 失败）；恢复后 9/9。正式 `engine/assets/game_app` 的 11 个文件均由最终 baker 生成，并与第二回独立输出逐 `cmp` 一致。关键 SHA-256 为：`level.bscn` `85c1f349f8fc50fd916d3aa74797c337ee34d2c5ae65f723d10df2def6e0537e`，`level.fg` `9be4ca42a7bbd0e3ccd7f663a9d372b15b0daaaaeac08a8f876e15d0a57fb473`，`level.banm` `f3181920a4cdf26267b0aaeefb29664b9fae582ddaef9d39558403e236788873`，`tone.wav` `f0e63c5eb3adef364e73e3113573b104a372bad25425819684ee1d0a695e2682`。

这些证据仅为 Linux CPU/文件系统证据。未运行 Windows 写路径、真实游戏循环、GPU、音频设备、听测或网络；`game_app_run()` 对合法配置仍按 Task 1 合同返回 `BREAK_RUNTIME_FAILED`。

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

正式 `engine/assets/game_app` 的 11 个文件均由最终 baker 生成，fresh 第二回逐字节一致。未运行 Windows/NTFS 实机、真实游戏主循环、GPU、音频设备/听测或网络；这些结果不构成崩溃持久性证明。

### 全量与交付验证补充

完整 `cmake --build build-game-integration-normal -j3` 成功，`ctest --test-dir build-game-integration-normal -j3 -LE 'graphics|fuzz' -E 'fuzz' --output-on-failure` 为 346/346 通过；`test_d3d12_dependency_gate`、`test_game_app_nm_missing`、`test_game_app_nm_unsupported` 按既有合同跳过。`ENGINE_BUILD_TESTS=OFF` 的 `build-game-integration-no-tests` 成功构建 `game_app` 与 `game_asset_bake`，no-tests baker 的 11 个输出与正式资产逐文件一致；`test_game_app_target_contract` 再次通过，两个 nm negative-path 仍按合同跳过。

master 的 X11 removal 合同和 C++20 public API/QUIC 相关测试均包含在上述全量结果中，没有为 Task 2 回退或排除这些既有行为。


## P12 Task 3：事务式 level 与 record 生命周期（2026-11-10）

本节是当前生命周期状态；上方 Task 1 的“合法配置始终 FAILED”和 Task 2 的“主循环尚未运行”仅保留为当时历史。同步 master `737ccc8b4227f2d53039119caf1a2b6066e2871e` 的独立 merge 为 `30c9285d9605ff07157f8563cda60279082f6269`，也是本任务 review BASE。合并没有冲突，X11 移除、CI 修复、Task 2 命名/资产/checkpoint 三态协议及双方文档均保留。

### 所有权与加载事务

`game_app --render=record --audio=record --fixed-step` 现在执行真实场景文件。主线程即 GameThread，独占 `World`、`BreakGame`、Lua/adapter、Flow、AI 和 physics 的可变状态；Runtime IO worker 只通过 VFS 返回有界字节，不接触这些对象。render/audio 分别只消费固定大小的 `GameRender*`/`GameAudio*` POD 快照与命令。

每次 load 都分配独立 `GameLevel` candidate，顺序为：注册 ECS 组件并创建 World → Runtime IO 读取 BSCN、`scene_load_binary_memory` 在 candidate World/Scene 上完成 CPU staging → Flow 反序列化/实体引用验证、两个正式 Lua module 加载和 adapter 创建 → `break_game_level_open` 验证正式 actor sidecar 并 adopt → physics ground/player body → 4x4 CPU navmesh、AI runtime/Enemy agent → BANM decode → record resource POD staging → World/Scene/Flow/resource 交叉引用。只有全部成功后才执行一次 `game->level = candidate` 并递增非零 u64 generation。

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

这些证据仅是 Linux CPU/record 生命周期证据。没有输入/玩家模拟、GPU `asset_scene_restore`、窗口或像素、音频设备/听测、网络、完整 checkpoint 状态恢复或完整 device worker；Windows 和其他平台未运行。VFS 的 16 mount 上限和 Runtime IO/VFS 路径上限仍是当前有界配置，超长路径或超过 mount 预算会明确拒绝 load。
