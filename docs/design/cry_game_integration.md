# Cry Game 真实集成

日期：2026-11-06

## 当前状态

P12 Task 1 已建立独立 `cry_game` 可执行应用及 `cry_game_core` 静态库，并交付严格命令行入口和真实进程合同测试。完整关卡、输入、模拟、渲染、音频命令、checkpoint 和卸载生命周期尚未实现；当前 `cry_game_run()` 对合法配置明确返回 `BREAK_RUNTIME_FAILED`，真实诊断含 `runtime returned FAILED`，进程退出 2，不以空壳返回成功。

## Target 与依赖边界

- `cry_game_core` 是顶层 C11 静态库，独立于 `ENGINE_BUILD_TESTS`，当前拥有 `apps/cry_game/cry_game.c`。
- `cry_game` 是真实可执行目标，拥有 `apps/cry_game/main.c`，链接 `cry_game_core` 并经 `engine_link_rhi_backend(cry_game)` 使用现有 RHI 选择链。
- `cry_game_core` 显式链接 `engine`、`break_game`、`break_ai`、`break_flow`、`break_lua`、`break_game_lua` 和 `runtime_core`。
- `engine`、`engine_demo`、`dxx_break` 不链接上述新增集成层。Actor/Lua 适配器使用 `engine/src/game/break_game_lua.h`；世界呈现 API 位于 `engine/src/renderer/world_presentation.h`。
- `CRY_GAME_ENABLE_NETWORK` 默认 `OFF`，CMake 始终把数值 `0` 或 `1` 传给 `cry_game` 的同名预处理条件。OFF 时 `--network` 被真实进程拒绝；ON 时该选项可以进入运行时，但本任务仍只返回 `BREAK_RUNTIME_FAILED`，没有网络实现或伪成功。

配置末尾直接检查实际 target 的 `LINK_LIBRARIES`：锁定 `cry_game_core` 依赖、legacy consumer 的直接链接集合和网络 0/1 定义。多行命令与变量展开因此由实际 target property 验收，而不是只扫描命令首行。合同还实际执行 `ENGINE_BUILD_TESTS=OFF` configure，防止 target 被移入测试作用域。

## 命令行合同

```text
cry_game --help
cry_game [--render record|auto|vulkan|opengl]
         [--audio record|null|device]
         [--assets DIR] [--scenario PATH] [--checkpoint DIR]
         [--trace PATH] [--screenshot PATH]
         [--fixed-step] [--frames N] [--require-device] [--network]
```

带值选项同时接受 `--name value` 和 `--name=value`。默认资产目录为 `assets/cry_game`，渲染为 `auto`，音频为 `device`。`--frames` 的精确词法是先满足 `[0-9]+`，再检查数值范围 1..4294967295；前导空白、`+`、负数、0、非数字、空值和溢出均退出 2，并报告 `--frames requires a positive 32-bit integer`。未知参数、非法枚举、缺值和 `--help` 后额外参数也退出 2，并使用各自的 CLI 错误诊断。

`--help` 单独使用退出 0 并输出 `Usage: cry_game` 及全部选项。合法默认配置、完整 record 配置和合法 `--frames 4294967295` 都必须到达运行时并报告 `runtime returned FAILED`；不得提前落入 CLI 错误或 `BREAK_RUNTIME_INVALID`。后续真实设备不可用证据码 77 将在对应图形/音频任务接入，本任务不伪造该证据。

## 验证

`test_cry_game_target_contract` 检查 configure-time target/链接边界，执行真实 no-tests configure，并启动真实进程覆盖帮助、运行时 FAILED、非法类别、network OFF/ON 和全部数字边界；有能力的 `nm` 扫描还必须找到 `cry_game_run`，再排除 `_for_test`/`test_hook`。

nm 扫描仅对非 Windows 或 MinGW 且实际支持 `--defined-only` 的工具/二进制格式启用。无 NM、不支持该参数或无法识别输出格式时返回 77 并标记 `UNVERIFIED`，不输出完整合同 PASS。`test_cry_game_nm_missing` 与 `test_cry_game_nm_unsupported` 分别锁定这两条路径；CTest 中显示为 Skipped，而不是符号扫描通过。

从工作树根运行：

```bash
cmake -S engine -B build-cry-integration-normal \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-cry-integration-normal -j3 --target cry_game
ctest --test-dir build-cry-integration-normal \
  -R '^test_cry_game_(target_contract|nm_missing|nm_unsupported)$' \
  --output-on-failure

cmake -S engine -B build-cry-integration-no-tests \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=OFF \
  -DENGINE_ENABLE_IPO=OFF -DENGINE_RHI_BACKEND=auto \
  -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-cry-integration-no-tests -j3 --target cry_game
```

网络开关的 ON 配置可独立验证，但仍不提供网络：

```bash
cmake -S engine -B build-cry-integration-network-flag \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF \
  -DCRY_GAME_ENABLE_NETWORK=ON
cmake --build build-cry-integration-network-flag -j3 --target cry_game
ctest --test-dir build-cry-integration-network-flag \
  -R '^test_cry_game_target_contract$' --output-on-failure
```

当前证据仅为 Linux CPU 构建、configure 和真实进程 CLI。没有运行游戏场景、真实 Vulkan/OpenGL 窗口、音频设备或网络；record/headless 也不能解释为 GPU 画面。后续任务必须分别提供这些证据。

## P12 Task 2：离线资产与 checkpoint v1

### 固定关卡与 baker

`cry_game_bake --output DIR` 是独立 C11 离线工具；目标在 `ENGINE_BUILD_TESTS=OFF` 时也存在。它不调用 `cry_game_run()`，不创建 RHI 设备、音频设备、网络或跨线程所有权。源树正式资产只由该命令显式生成，测试使用 per-process 临时目录。

`level.bscn` 由真实 `scene_save_binary` 写出并由 `scene_probe_binary`/`scene_load_binary` 回读。固定实体顺序为 Ground、Player、Enemy、DynamicWall、Vehicle、VisibleColor、HiddenColor；`actors.sidecar` 逐行使用 P1 已有的 `entity-index class-name` 格式。七个实体共享一份真实 CPU cube 几何（24 vertices、36 indices），通过 `SerializeOptions.read_mesh_geometry` 交给 BSCN writer；没有 GPU readback。七个节点使用各自的变换和颜色材质，隐藏颜色节点保留 mesh/material 引用但初始 `has_mesh=false`。场景实体和 Flow 目标只保存 `(index, generation)`，没有持久化 C 指针。

`level.fg` 由 `break_flow_serialize` 生成，包含 enter → delay(30 ticks) → add-item 的两条 exec link。`director.lua` 和 `player.lua` 可由真实 `break_lua` 加载，`broken.lua` 是明确的语法错误 fixture；本任务不建立游戏 VM 生命周期。`level.banm` 由 `anim_codec_encode` 生成，含 translation/rotation/scale 三个通道，测试用 `anim_codec_decode`、`anim_codec_time_error_bound`、`anim_codec_scalar_error_bound` 和旋转误差界验收。`tone.wav` 是固定 seed 的 44100 Hz、mono、16-bit PCM，4410 个样本；没有音频设备或听测证据。

三个 `.scenario` 文件是版本化固定输入资产，由同一 baker 生成；场景脚本解析和生命周期执行属于后续任务，本任务没有声称它们已运行。

### checkpoint v1 格式与事务

`manifest.cry` 为显式小端二进制：40 字节头加每条 88 字节记录。头依次是 8 字节 `CRYCKPT\0`、version=1、header_bytes=40、exact_total_size(u64)、generation(u64)、file_count(u32)、reserved(u32)。记录依次是 kind(u32)、name_length(u32)、size(u64)、FNV-1a-64(u64)、64 字节以 NUL 结尾并零填充的 basename。FNV 只用于损坏检测，不是安全认证。

每代 1..16 个文件，每文件最多 64 MiB，basename 最多 63 字节且只允许 ASCII 字母数字、`_.-`；路径分隔符、绝对路径、`..`、`.` 和 `manifest.cry` 均被拒绝。容量或长度超限返回 `BREAK_RUNTIME_OVERLOAD`，不静默截断。读取先验证完整 manifest 和所有记录，再逐文件以固定 4096 字节缓冲 staging 校验精确长度和 hash，无需按 payload 大小分配。

调用者先以新 generation 名写 payload，避免覆盖旧 manifest 引用的文件。`cry_checkpoint_write_manifest` 先重新读取并校验所有新 payload，再用一个 `PlatformAtomicWriter` 提交 manifest。校验、打开、写入或提交失败时不提交新代；可安全识别为本代的新文件会删除，旧 manifest 引用的同名文件不会删除。写前保留旧 manifest 字节，用于提交失败后的恢复。`cry_checkpoint_probe` 不修改任何 World/Level；真实运行状态反序列化、资源重建和事务 load 属于后续任务。

### 已执行的 Task 2 证据

Linux 上 `test_cry_game_assets` 为 9/9，通过两回 baker 逐字节比较、BSCN+P1 sidecar、Flow、BANM、WAV、Lua、manifest 格式、payload/manifest 损坏、非法名称/容量和 RLIMIT_FSIZE 中途写失败回滚。相关 `test_scene_serial`、`test_break_flow_serial`、`test_anim_compression`、`test_break_game_level`、`test_platform_fs_write`、`test_break_lua_module` 与新增测试合计 7/7 通过。

生产变异临时删除 payload hash 比较后，篡改用例如期失败（8 通过、1 失败）；恢复后 9/9。正式 `engine/assets/cry_game` 的 11 个文件均由最终 baker 生成，并与第二回独立输出逐 `cmp` 一致。关键 SHA-256 为：`level.bscn` `85c1f349f8fc50fd916d3aa74797c337ee34d2c5ae65f723d10df2def6e0537e`，`level.fg` `9be4ca42a7bbd0e3ccd7f663a9d372b15b0daaaaeac08a8f876e15d0a57fb473`，`level.banm` `f3181920a4cdf26267b0aaeefb29664b9fae582ddaef9d39558403e236788873`，`tone.wav` `f0e63c5eb3adef364e73e3113573b104a372bad25425819684ee1d0a695e2682`。

这些证据仅为 Linux CPU/文件系统证据。未运行 Windows 写路径、真实游戏循环、GPU、音频设备、听测或网络；`cry_game_run()` 对合法配置仍按 Task 1 合同返回 `BREAK_RUNTIME_FAILED`。

### 最终回归补充（2026-11-09）

完整构建使用 `cmake --build build-cry-integration-normal -j3` 成功。任务的非图形验收命令为 `ctest --test-dir build-cry-integration-normal -j3 -LE 'graphics|fuzz' -E 'fuzz' --output-on-failure`，结果 330/330 通过；`test_d3d12_dependency_gate`、`test_cry_game_nm_missing`、`test_cry_game_nm_unsupported` 三个测试按各自既有合同跳过，未把跳过写成设备或符号扫描通过。

曾先用名称过滤 `-E 'graphics|fuzz'` 运行 341 项；该方式不排除 `graphics` 标签，因而执行了图形/平台测试，并出现既有 `test_platform_x11_runtime` 的 `start_fullscreen window does not cover the monitor` 一项失败。本任务未修改该 X11 行为，也不将此运行计为非图形通过证据；正确标签过滤后的 330 项结果才是上述验收结果。

`ENGINE_BUILD_TESTS=OFF` 的独立构建树已成功构建 `cry_game` 和 `cry_game_bake`，该 baker 的 11 个输出也与源树正式资产逐字节一致。`test_cry_game_target_contract` 再次通过；两个 nm negative-path 测试仍按合同跳过。合法 `cry_game` 配置的真实进程仍返回 FAILED/退出 2，未被资产交付改成伪成功。
