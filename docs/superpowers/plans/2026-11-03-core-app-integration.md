# Core App Integration Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 新增并验收一个真正可玩的 C11 `core_app` 应用，使 Actor/Lua、Flow Graph、键鼠/手柄/触摸、AI、动画/物理、世界呈现和声音命令共享加载→输入→模拟→呈现→保存→卸载生命周期，网络保持独立可选。

**Architecture:** `core_app_runtime` 在 CoreAppThread 独占 ECS/Actor/Lua/Flow/AI/动画/物理可变状态，在帧边界生成不可变 POD 渲染、音频和可选网络快照；`core_app` 主程序实际创建平台窗口/RHI/音频资源并执行场景脚本。离线默认使用 Vulkan 优先的现有 RHI 选择链，CPU record 后端只记录命令；保存采用分文件 staging 加原子 manifest，加载在完整 staging 成功后一次替换当前 level。

**Tech Stack:** C11、现有 ECS/`break_game`/`break_flow`/`break_ai`/`break_lua`/P9 Actor adapter、Runtime Core、RHI（Vulkan 默认、OpenGL 最后降级）、现有 animation/physics/world presenter、miniaudio `AudioSystem`、可选 Snowflake `break_net`、CMake/CTest/`test_framework.h`。

## Global Constraints

- 实施只在 `.worktrees/cry-integration` 的 `cry-integration` 分支进行；每个任务独立提交，不 push、不建 PR、不修改 `master`，也不在其他模块工作树写文件。
- 引擎核心和新增库使用 C11；沿用现有应用/RHI 边界，不引入 UI 框架、脚本语言、包管理器或未经确认的依赖。
- CoreAppThread 独占 World、Actor、AI 查询、行为树、动画和物理的可变状态；Render/Audio/Network 只接收命令、不可变快照或 POD，不接收 World/Lua/RHI 私有所有权指针。
- 不为“并行”强迁现有窗口/RHI 线程模型：真实 GL/Vulkan 提交沿用主线程 RHI 阶段；快照在 present 完成前不可修改。音频与网络 worker 只拥有自己的设备/传输状态。
- 热路径不临时分配内存；容量在 create/load staging 时确定。容量、深度、输入大小和消息数量均有硬上限，超限返回相应 `OVERLOAD`，不静默截断。
- 失败操作事务化：不得留下半创建 Actor、部分 Lua 模块替换、部分 Flow 动作、半个 level 或部分替换资源。保存失败不替换上一份 checkpoint，加载失败不修改当前 level。
- 持久身份使用带 generation 的句柄；Lua、网络和持久化数据不出现 C 指针。异步完成同时核对 request id 与 level/resource generation，迟到结果返回/记录 `STALE` 并释放，不覆盖新资源。
- 沿用各库错误命名，不为文字统一破坏 ABI；应用自有 API 使用 `BreakRuntimeError`。外部非法数据为 `INVALID`，失效身份为 `STALE`，容量满为 `OVERLOAD`，线程归属错误为 `REJECTED`，资源/功能失败为 `FAILED`。
- 新可选库不进入 `engine` 核心；只有新应用目标显式链接所需模块。`engine`、`engine_demo`、`dxx_break` 的链接集合不得因 P12 增加 gameplay/Lua/Flow/Runtime/网络库。
- 默认 `ENGINE_RHI_BACKEND=auto` 且 Vulkan 优先；OpenGL 仅用于创建失败后的最后降级和最终画面对照。显式 Vulkan 证据必须禁止 fallback 并核对实际 backend。
- `engine_rhi_headless` 是 fail-closed stub；不得拿它运行“图形测试”。record/fake 后端只证明 CPU 快照与命令，不称为 GPU 画面、窗口、像素或音频设备证据。
- 音频 record 只证明命令顺序/生命周期；null 设备不证明发声；真实设备运行不自动证明听感。没有实际听测时必须保留该限制。
- 网络默认关闭，无 Snowflake 的构建和离线游玩不得退化；网络回调只校验、复制、入队。线上身份来自认证 Session；客户端不得提交或直接裁定伤害、价格、生命结果。
- 新测试使用 CTest 和 `test_framework.h`，行为测试先观察到目标行为 RED，再写最小实现到 GREEN；编译/链接缺失可以补充记录，但每个任务至少留一项行为 RED。
- 每个任务至少做一项关键行为变异：临时破坏生产条件，确认对应测试 RED，立即恢复并重跑 GREEN；变异不进入提交。
- 所有构建并行度统一 `-j3`；测试生成物写入构建树或 `test_tmp` 路径，不写源树，不提交日志、截图、checkpoint 或 fuzz 输出。
- 本计划当前只提交文档。实施时必须更新实际设计/状态文档；未运行的平台、真实窗口、GPU、音频设备、网络或听测不得写成通过。

---

## 依赖基线与集成约束

P12 是最后的集成任务，不得靠在本分支重实现其他子项目来绕过依赖。开始 Task 1 前，主代理必须先把已定稿、已提交、各自 normal/ASan+UBSan/TSan 通过的 P0–P11 变更合入同一集成基线。只读取到设计、未提交文件或进行中修改都不构成可执行 API。

本计划勘察时观察到的事实如下；它们是合并检查项，不是冻结兼容承诺：

- P1 已在当前基线提供 `break_game` 的 Actor、ActionMap、level sidecar、Area、物品和权威 fire intent。
- P2 的 `break_flow` 已有图、序列化和运行时实现，但编辑器/运行时分支仍在变动；以最终 `break_flow.h` 和测试为准。
- P3 已有动态导航/agent/编组/智能对象实现，仍有进行中的导航并发修改；合入前必须重新确认 owner 规则，不能假设查询可跨线程。
- P4 与 P5 同时触及 `animation.h/.c` 和 ragdoll/IK 边界。最终树必须只有一种 IK/布娃娃互斥合同；不得同时保留 `physics_suspended` 与另一套旁路闸门而不解释所有权。
- P6 已有 `WorldPresenter`/POD 快照实现，真实 GPU 测试仍有进行中改动；最终提交必须包含并运行其真实 Vulkan/OpenGL 测试，而不是只保留 fake RHI。
- P7 的 `InputExtended`/`platform_input_extended()` 仍处于进行中；若最终头文件或平台后端缺失，P12 停止在该集成门，不添加同名 shim。
- P9 文档要求独立 `break_game_lua` adapter，但勘察时尚未形成该目标/公开头。P12 必须消费最终 adapter 的 per-Actor 错误隔离、句柄 acquire/release 和诊断 API，不得在应用里另写一套同名 adapter。
- P8/P10/P11 的独立工作树在勘察时尚无可合入增量。它们仍需按各自计划完成并合入；P12 不虚构大厅、声音事件或 CVar API。本应用的最低声音通道使用已经存在的 `audio.h`，可选网络使用已经存在的 `break_net`/Session API；后续 P8/P10 正式接口合入后只在其真实合同内替换实现。
- `scene_load_binary` 恢复 ECS/Scene CPU 数据与 Entity generation，但不恢复 BreakGame adapter、Lua VM、Flow 待处理队列、AI runtime、GPU 资源或音频源。`asset_scene_restore` 失败后文档要求丢弃该 Scene；集成层必须遵守，不能把“BSCN parse 成功”当成 level 恢复成功。
- `break_game_level_close` 会 despawn 已登记 Actor 并调用 unload hook；hook 不得递归销毁其 BreakGame/World。完整 level 卸载由 `CoreLevel` 所有者按依赖顺序完成。
- `scene_save_binary` 的 geometry reader 失败会跳过网格；因此 P12 的 checkpoint 必须在保存后重新 probe/load 并核对 manifest 中的几何记录，不能把 best-effort writer 当成完整性保证。
- `asset_scene_restore` 可能部分重建后失败；staging Scene 必须立即 `asset_scene_free`，旧 level 保持不动。当前 level 的 GPU 资源只有在 `rhi_device_idle` 成功且不再被快照引用后才能销毁。
- Runtime coordinator 在 sticky `FAILED` 状态不会执行普通 stop 回调；启动失败和运行失败必须走应用的显式 rollback/cleanup 路径，不能依赖一个会被拒绝的 `stop()` 来释放资源。
- Runtime IO 是 process singleton，且有 request/refcount 生命周期；同一进程重载必须先完成/取消并释放旧请求，再开启新 level 资源请求。不得创建第二个 facade 或在旧请求存活时 reinit。

## Files/Interfaces

### 新应用与资产

- Create `engine/apps/core_app/main.c`：真实 `main()`、严格 CLI 解析、退出码、调用 `core_app_run()`；不是库-only 示例。
- Create `engine/apps/core_app/core_app.h/.c`：`CoreApp`/`CoreLevel` 所有权、帧顺序、事务 load/unload、诊断和 checkpoint 入口。
- Create `engine/apps/core_app/scenario.h/.c`：有界确定性输入/生命周期脚本解析和逐 tick 执行。
- Create `engine/apps/core_app/core_app_input.h/.c`：`InputState` + `InputExtended` → ActionMap/触摸 POD 快照，不修改 `InputState` ABI。
- Create `engine/apps/core_app/core_app_simulation.h/.c`：Character/AI/动画/物理/载具/布娃娃顺序和固定步长状态。
- Create `engine/apps/core_app/core_app_render.h/.c`：不可变渲染快照、RHI/record 两种真实消费者、资源代际与延迟销毁。
- Create `engine/apps/core_app/core_app_audio.h/.c`：有界声音命令队列、record/null/device 后端和 source generation。
- Create `engine/apps/core_app/core_app_checkpoint.h/.c`：版本化 manifest、BSCN/Flow/Actor/运行状态侧车、原子保存与 staging load。
- Create `engine/apps/core_app/core_app_network.h/.c`：默认关闭的可选 POD 快照通道；只在 `CORE_APP_ENABLE_NETWORK=ON` 且 `BREAK_ENABLE_SNOWFLAKE=ON` 时编译真实传输实现。
- Create `engine/apps/core_app/core_app_asset_bake.c`：可重复生成最小关卡、Flow、压缩动画、音频和损坏 fixture 的离线工具；生成源树资产只在此显式维护任务发生，测试运行不得重写它们。
- Create `engine/assets/core_app/level.bscn`、`level.fg`、`actors.sidecar`、`director.lua`、`player.lua`、`broken.lua`、`level.banm`、`tone.wav`、`deterministic.scenario`、`load_unload.scenario`、`rollback.scenario`：真实应用读取的固定资产/场景，而非测试硬编码替代品。
- Create `docs/design/core_app_integration.md`：target、操作、数据流、格式、所有权和证据边界。

### 自动化与构建

- Modify `engine/CMakeLists.txt`：顶层 `core_app_runtime`、`core_app`、`core_app_asset_bake`；测试、图形、fuzz 和可选网络 target 按既有条件注册。
- Create `engine/tests/test_core_app_target_contract.cmake`：结构、链接隔离、无测试钩子、无 Snowflake 构建合同。
- Create `engine/tests/test_core_app_assets.c`：真实 BSCN/Flow/BANM/资产内容、版本与容量合同。
- Create `engine/tests/test_core_app_runtime.c`：focused 状态、输入、脚本隔离、AI/动画/物理、资源和 checkpoint 行为；不是最终集成证据的替代品。
- Create `engine/tests/test_core_app_lifecycle.cmake`：通过 `execute_process` 多次启动真实 `core_app`，解析其 canonical trace，并比较确定性重放/保存恢复。
- Create `engine/tests/test_core_app_gpu.cmake` 与 `engine/tests/test_core_app_image.c`：启动真实窗口应用、核对 backend/device、读取真实 screenshot 像素；无设备只能退出 77。
- Create `engine/tests/test_core_app_audio.cmake`：分别运行 record 和真实设备模式；后者要求实际 `AudioSystem` 和设备证据。
- Create `engine/tests/test_core_app_network.cmake` 与 `engine/tests/test_core_app_net_client.c`：只有 Snowflake lane 构建，启动真实应用并用认证 loopback 客户端验证可选通道和越权消息拒绝。
- Create `engine/tests/fuzz_core_app_checkpoint.c`、`engine/tests/fuzz_core_app_scenario.c`：对真实应用解析/staging 路径做确定性变异 fuzz。
- Modify `.github/workflows/ci.yml`：让默认 headless/normal/sanitizer lane 构建并运行新非图形测试，fuzz smoke 显式构建新 target；Snowflake 只留在专用可选 lane。
- Modify `docs/design/cry_style_gameplay.md`、`docs/design/runtime_overview.md`、`docs/Implementation_Status.md`：完成后删除“仍无真实集成/无 GPU/无声音”等过期现状，保留未验证边界和实际证据。
- Create `.superpowers/sdd/core-app-integration-report.md`：每个 RED/GREEN、变异、命令、设备、独立评审发现和剩余限制的事实台账。

### 应用自有稳定接口

```c
#define CORE_APP_FIXED_DT (1.0f / 60.0f)
#define CORE_APP_MAX_SUBSTEPS 8u
#define CORE_APP_MAX_ACTORS 64u
#define CORE_APP_MAX_SCENARIO_BYTES (64u * 1024u)
#define CORE_APP_MAX_SCENARIO_EVENTS 4096u
#define CORE_APP_MAX_AUDIO_COMMANDS 256u
#define CORE_APP_MAX_NET_MESSAGES 64u
#define CORE_APP_MAX_RESOURCE_REQUESTS 64u
#define CORE_APP_CHECKPOINT_VERSION 1u
#define CORE_APP_TRACE_VERSION 1u

typedef struct CoreApp CoreApp;
typedef struct CoreLevel CoreLevel;

typedef enum CoreAppRenderMode {
    CORE_APP_RENDER_RECORD = 0,
    CORE_APP_RENDER_AUTO,
    CORE_APP_RENDER_VULKAN,
    CORE_APP_RENDER_OPENGL
} CoreAppRenderMode;

typedef enum CoreAppAudioMode {
    CORE_APP_AUDIO_RECORD = 0,
    CORE_APP_AUDIO_NULL,
    CORE_APP_AUDIO_DEVICE
} CoreAppAudioMode;

typedef struct CoreAppConfig {
    const char *asset_root;
    const char *scenario_path;
    const char *checkpoint_dir;
    const char *trace_path;
    const char *screenshot_path;
    CoreAppRenderMode render_mode;
    CoreAppAudioMode audio_mode;
    bool fixed_step;
    bool require_device;
    u32 max_frames;
} CoreAppConfig;

typedef struct CoreAppDiagnostics {
    u64 frame_count;
    u64 simulation_ticks;
    u64 actor_ticks;
    u64 actor_script_failures;
    u64 flow_actions;
    u64 render_commands;
    u64 audio_commands;
    u64 audio_overloads;
    u64 stale_completions;
    u64 save_commits;
    u64 load_commits;
    u64 rejected_loads;
    u64 network_messages;
    u64 network_rejects;
} CoreAppDiagnostics;

BreakRuntimeError core_app_run(const CoreAppConfig *config, int *out_exit_code);
BreakRuntimeError core_app_load(CoreApp *app, const char *checkpoint_dir);
BreakRuntimeError core_app_step(CoreApp *app);
BreakRuntimeError core_app_save(CoreApp *app, const char *checkpoint_dir);
BreakRuntimeError core_app_unload(CoreApp *app);
void core_app_destroy(CoreApp *app);
const CoreAppDiagnostics *core_app_diagnostics(const CoreApp *app);
```

`CoreAppConfig.require_device` 对图形模式要求真实所请求 RHI 后端，对 `--audio=device` 要求实际设备初始化成功；测试用 `--require-device` 禁止把环境缺证写成通过。`out_exit_code` 约定：`0` 完整场景成功，`2` 参数/资源/合同失败，`77` 仅表示在创建任何游戏状态之前发现显示/GPU/音频设备不可用。游戏开始后发生的失败不得改成 77。

```c
typedef struct CoreAppRenderCommand {
    u32 kind;             /* FRAME_BEGIN, WORLD_DRAW, SKINNED_DRAW, PRESENT */
    u64 frame_id;
    u64 level_generation;
    u32 object_id;
    u32 resource_index;
    u32 resource_generation;
    u32 instance_count;
} CoreAppRenderCommand;

typedef struct CoreAppAudioCommand {
    u32 kind;             /* LISTENER, PLAY_3D, STOP, SHUTDOWN */
    u64 frame_id;
    u64 level_generation;
    u64 sequence;
    u32 event_id;
    u32 source_index;
    u32 source_generation;
    Vec3 position;
    Vec3 forward;
    Vec3 up;
    f32 volume;
} CoreAppAudioCommand;

BreakRuntimeError core_app_render_record(const CoreAppRenderCommand *command, void *context);
BreakRuntimeError core_app_render_submit_rhi(const CoreAppRenderCommand *command, void *context);
BreakRuntimeError core_app_audio_enqueue(const CoreAppAudioCommand *command, void *context);
BreakRuntimeError core_app_audio_drain_record(u32 budget, void *context);
BreakRuntimeError core_app_audio_pump_device(u32 budget, void *context);

typedef struct CoreAppCheckpointFile {
    u32 kind;
    u64 size;
    u64 hash;
    char name[64];
} CoreAppCheckpointFile;

BreakRuntimeError core_app_checkpoint_write_manifest(const char *directory,
                                                 const CoreAppCheckpointFile *files,
                                                 u32 file_count, u64 generation);
BreakRuntimeError core_app_checkpoint_probe(const char *directory);
u64 core_app_checkpoint_manifest_hash(const char *directory);
```

这些接口是应用真实后端和 checkpoint 边界，不是为未定稿模块编造同名兼容函数。record 后端逐条写 canonical 文本 trace；RHI 后端在有效 render pass 内调用 `world_presenter_submit` 或 skinned draw；device 后端只在 audio owner 线程调用 `audio_play_3d`、`audio_source_*` 和 `audio_system_destroy`。manifest writer 只提交已经写入并验证的文件描述，`core_app_save()` 负责生成这些文件。

### 直接使用的外部接口

- `break_game_create/register_class/spawn/despawn/tick/eval_actions/level_open/level_close/area_*` 使用 `engine/src/game/break_game.h` 的最终签名。
- `break_flow_deserialize`、`break_flow_runtime_create/post/tick/reset/destroy` 使用 `engine/src/game/break_flow.h`；Flow 持久化只保存图资产，延迟队列在 load 后显式 reset，不伪称恢复。
- P9 adapter 只从最终 `break_game_lua` 公开头消费；本计划不预设其函数拼写。集成门要求该头提供 create/destroy、逐 Actor 错误诊断和 despawn release 的真实实现。
- `break_ai_runtime_create/find_path/path_is_current/agent_*`、`break_behavior_tick`、`break_nav_follow_*` 使用最终 `break_ai.h`；所有调用仍在 CoreAppThread。
- `anim_blend_*`、`anim_loco1d_*`、`anim_morph_evaluate_skinned`、`anim_facial_evaluate`、`anim_codec_decode`、`skeleton_apply_local_trs/upload`、`ragdoll_*`、`character_update`、`vehicle_step`、`physics_step` 使用合并后的公共头。
- `world_presentation_snapshot`、`world_presenter_create/submit/destroy` 使用 P6 的 POD 快照；快照提交后不再写其存储。
- `scene_save_binary/scene_load_binary/scene_probe_binary/scene_serial_free`、`asset_scene_restore/asset_scene_free`、`scene_state_save/load` 只由应用集成层调用，不把其指针传入其他库。
- `break_runtime_coordinator_*` 管理正常 stop 阶段；`break_runtime_io_*` 管理资源请求、completion 和释放；启动/失败清理由 `CoreLevel` rollback 补齐。
- `platform_input`、`platform_input_extended`、`rhi_device_create_compiled`、`rhi_device_get_capabilities`、`rhi_runtime_active_backend`、`rhi_frame_begin/end`、`rhi_present`、`rhi_screenshot`、`rhi_device_idle` 使用现有 PAL/RHI 合同。

### 确定性场景文本合同

文件首行必须是 `version 1`，之后每行恰好一个事件；空行和 `#` 注释跳过。总字节不超过 64 KiB、事件不超过 4096、单行不超过 511 字节，路径 token 不超过 255 字节，任何超限整份 `INVALID`，不执行已解析前缀。支持以下精确文法：

```text
<tick> key <name> <0|1>
<tick> touch <source-id> <down|move|up|cancel> <x> <y>
<tick> pad <index> <axis> <value>
<tick> flow <event-key> <value>
<tick> save
<tick> save-to <relative-checkpoint-path>
<tick> load
<tick> load-from <relative-checkpoint-path>
<tick> unload
<tick> screenshot
<tick> quit
```

事件按 `(tick, file_order)` 排序，解析器拒绝 tick 回退、非有限/越界坐标、重复 quit 和未知命令。fixed-step 模式每个 `core_app_step` 恰好一个 1/60 秒 tick；交互模式使用 accumulator，最多 8 个 substep，剩余超额时间计入诊断而不是改变物理步长。`save/load/unload` 只在一个 fixed tick 完成、render/audio 快照提交之前或之后的明确帧边界执行；本计划固定为“simulation 后、下一次 snapshot 构建前”。

### Checkpoint 合同

目录内有 `manifest.game` 和带 save generation 的 `scene_<g>.bscn`、`flow_<g>.fg`、`actors_<g>.sidecar`、`state_<g>.bin`、`runtime_<g>.bin`。manifest 为版本化小端二进制，含精确总长、generation、每文件种类/长度/FNV-1a-64 和相对 basename；FNV 只检损，不作为安全认证。文件先完整写入并重新读取验证，manifest 最后通过 `PlatformAtomicWriter` 提交；失败删除本 generation 新文件，旧 manifest 与其文件不变。

`runtime_<g>.bin` 只保存有所有权的 POD：固定 tick、玩家/敌人 CharacterController、相机、昼夜时间、动态障碍的稳定 id/矩形/alive、背包公开状态和 checkpoint generation。Flow pending queue、Lua VM/stack、AI cache、输入瞬态、RHI handle、音频 source id、网络 connection key 一律不保存。加载重建 AI runtime 并使旧路径失效，重新加载 Lua 源并创建新 host handle，重新创建 GPU/音频资源；网络默认仍关闭。

---

<!-- CORE_APP_COMPLETED_TASKS_1_3_BEGIN -->
### Task 1: 锁定合并基线、应用 target 与进程入口

**Files:**
- Modify: `engine/CMakeLists.txt`
- Create: `engine/apps/game_app/main.c`
- Create: `engine/apps/game_app/game_app.h`
- Create: `engine/apps/game_app/game_app.c`
- Create: `engine/tests/test_game_app_target_contract.cmake`
- Create: `docs/design/game_app_integration.md`

**Interfaces:**
- Consumes: 已定稿且合入的 P0–P11 target/header，尤其 `break_flow` 和 P9 `break_game_lua`。
- Produces: 顶层 `game_app_core`、`game_app`；`GAME_APP_ENABLE_NETWORK=OFF` 默认；严格 CLI 和 `game_app_run()` 入口。baker 由 Task 2 添加。

- [ ] **Step 1: 写 target/CLI 行为 RED**

先写 CMake 合同，要求 target 在 `ENGINE_BUILD_TESTS` 外定义、`game_app` 链接 `game_app_core` 并经 `engine_link_rhi_backend()` 选择 RHI，核心消费者不新增库，生产二进制不含 `*_for_test`/`test_hook`。同一 CMake 测试通过 `execute_process` 启动真实二进制：`--help` 退出 0；未知参数、`--render=headless`、缺值和 `--network` 在未编译网络时退出 2。无参数行为由后续真实生命周期任务验收，本任务不让其假成功。

```cmake
if(NOT cmake_text MATCHES "add_executable\\(game_app apps/game_app/main.c\\)")
    message(FATAL_ERROR "missing real game_app executable")
endif()
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_game|break_flow|break_ai|break_lua|runtime_core|game_app")
        message(FATAL_ERROR "P12 library leaked into legacy consumer: ${line}")
    endif()
endforeach()
execute_process(COMMAND "${GAME_APP}" --help RESULT_VARIABLE help_rc)
if(NOT help_rc EQUAL 0)
    message(FATAL_ERROR "game_app --help failed: ${help_rc}")
endif()
```

- [ ] **Step 2: 运行结构 RED 和行为 RED**

Run:
```bash
cmake -S engine -B build-game-integration-normal -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-game-integration-normal -j3 --target game_app
```
Expected: target 不存在是结构 RED；加入最小 target 后，真实进程的 `--help`/非法参数断言必须因错误退出码或缺失行为而 RED。若 P9 target/header 或任何前置依赖缺席，停止并回报依赖，不写 stub 通过。

- [ ] **Step 3: 最小实现真实 target 与参数解析**

按现有 C11/CTest 惯例添加：

```cmake
option(GAME_APP_ENABLE_NETWORK "Enable the optional authenticated Snowflake channel" OFF)
add_library(game_app_core STATIC
    apps/game_app/game_app.c)
set_property(TARGET game_app_core PROPERTY C_STANDARD 11)
target_include_directories(game_app_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(game_app_core PUBLIC
    engine break_game break_ai break_flow break_lua break_game_lua runtime_core)
add_executable(game_app apps/game_app/main.c)
target_link_libraries(game_app PRIVATE game_app_core m)
engine_link_rhi_backend(game_app)
add_test(NAME test_game_app_target_contract
    COMMAND ${CMAKE_COMMAND}
        -DENGINE_CMAKE=${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
        -DGAME_APP=$<TARGET_FILE:game_app>
        -P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_game_app_target_contract.cmake)
```

`main.c` 使用显式 `--render record|auto|vulkan|opengl`、`--audio record|null|device`、`--assets DIR`、`--scenario PATH`、`--checkpoint DIR`、`--trace PATH`、`--screenshot PATH`、`--fixed-step`、`--frames N`、`--require-device`、`--network` 解析；不接受隐式位置参数。`game_app_run` 本任务只完成 config 验证和明确 `FAILED`，不得返回假成功。

- [ ] **Step 4: 验证 GREEN 和 no-tests target**

Run:
```bash
cmake --build build-game-integration-normal -j3 --target game_app
./build-game-integration-normal/game_app --help
ctest --test-dir build-game-integration-normal -R '^test_game_app_target_contract$' --output-on-failure
cmake -S engine -B build-game-integration-no-tests -DENGINE_BUILD_TESTS=OFF -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-game-integration-no-tests -j3 --target game_app
```
Expected: help 为 0，非法输入为 2，合同 PASS；无测试配置仍产出真实应用。完整场景此时明确 FAILED，不写成可玩。

- [ ] **Step 5: 变异并提交**

临时让 legacy `engine_demo` 链接 `game_app_core`，确认 target contract RED，恢复后 GREEN；再临时把未知参数当成功，确认 CLI 测试 RED 并恢复。

```bash
git add engine/CMakeLists.txt engine/apps/game_app engine/tests/test_game_app_target_contract.cmake docs/design/game_app_integration.md
git commit -m "game: add explicit playable integration target"
```

### Task 2: 可重复关卡、Flow/Lua/动画/声音资产与检查点格式

**Files:**
- Create: `engine/apps/game_app/game_checkpoint.h/.c`
- Create: `engine/apps/game_app/game_asset_bake.c`
- Create: `engine/assets/game_app/` 下列出的全部资产
- Create: `engine/tests/test_game_app_assets.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: `scene_save_binary`、`scene_probe_binary`、`break_flow_serialize`、`anim_codec_encode`、`PlatformAtomicWriter`。
- Produces: checkpoint v1 manifest、可重复 baker、真实固定场景资产。

- [ ] **Step 1: 写资产与 manifest 行为 RED**

测试先调用 baker 到 `test_tmp` 目录，再由真实 readers 打开产物：场景必须含地面、玩家、敌人、一个动态墙、一辆载具和可见/隐藏颜色网格；Actor sidecar 的 index 必须在 BSCN 中存在；Flow 反序列化后包含 enter→delay→add-item；BANM decode 后的 TRS 误差满足 `anim_codec_time_error_bound`/scalar bound；WAV 有合法 RIFF 长度。

manifest 测试写两个连续 generation，篡改第二个 payload 而不改 manifest，probe 必须 `INVALID`；保存第一份时的独立副本仍可打开；中途 writer 失败时同目录旧 manifest 字节不变。

```c
const u8 payload[] = {1u, 2u, 3u, 4u};
GameCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                          .hash = test_fnv1a64(payload, sizeof(payload)),
                          .name = "runtime_1.bin"};
ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
ASSERT_EQ(game_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
u64 before_hash = game_checkpoint_manifest_hash(dir);
ASSERT_EQ(test_copy_checkpoint(dir, backup_dir), 0);
strcpy(file.name, "runtime_2.bin");
ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
ASSERT_EQ(game_checkpoint_write_manifest(dir, &file, 1u, 2u), BREAK_RUNTIME_OK);
ASSERT_TRUE(before_hash != game_checkpoint_manifest_hash(dir));
ASSERT_EQ(test_checkpoint_corrupt_payload_for_fixture(dir, "runtime"), BREAK_RUNTIME_OK);
ASSERT_EQ(game_checkpoint_probe(dir), BREAK_RUNTIME_INVALID);
ASSERT_EQ(game_checkpoint_probe(backup_dir), BREAK_RUNTIME_OK);
```

`test_fnv1a64`、`test_write_checkpoint_file`、`test_copy_checkpoint` 和 `test_checkpoint_corrupt_payload_for_fixture` 都是测试源码局部 helper，不进入生产库。

- [ ] **Step 2: 运行 baker/reader RED**

Run:
```bash
cmake --build build-game-integration-normal -j3 --target game_asset_bake test_game_app_assets
./build-game-integration-normal/test_game_app_assets
```
Expected: 先有资产/manifest 行为断言 RED；若仅是目标缺失，补最小目标后必须继续看到内容或 roundtrip 断言 RED。

- [ ] **Step 3: 实现 baker 与原子 checkpoint**

baker 使用固定数组和固定 seed，按稳定 entity 顺序注册组件，调用 `scene_save_binary` 时提供真实 CPU geometry reader；Flow 用公开序列化 API；动画用公开 codec；声音生成确定性的 44100 Hz 16-bit PCM WAV。写源树正式资产时要求显式 `game_asset_bake --output engine/assets/game_app`，测试一律输出临时目录。

checkpoint 写所有 generation 文件后逐一 probe，再用一个 `PlatformAtomicWriter` 写 manifest。所有长度/hash 计算先检查加法/乘法溢出；basename 只能含 ASCII 字母数字、`_.-`，拒绝 `/`、`\\`、`..` 和绝对路径。读取先验证 manifest 全部记录，再 staging 每个文件。

- [ ] **Step 4: 运行 roundtrip GREEN 与损坏回归**

Run:
```bash
./build-game-integration-normal/game_asset_bake --output /tmp/game-app-assets-check
./build-game-integration-normal/test_game_app_assets
ctest --test-dir build-game-integration-normal -R '^(test_game_app_assets|test_scene_serial|test_break_flow_serial|test_anim_compression)$' --output-on-failure
```
Expected: 全部 PASS；比较两次 baker 输出逐字节相同；损坏 manifest/payload 被拒绝，旧 checkpoint 可继续使用。

- [ ] **Step 5: 变异、生成正式资产并提交**

临时跳过 manifest hash 检查，确认篡改测试 RED；恢复后 GREEN。用最终 baker 生成并检查 `engine/assets/game_app`，将二进制资产纳入同一提交，保证正常 checkout 可直接运行。

```bash
git add engine/apps/game_app/game_checkpoint.c engine/apps/game_app/game_checkpoint.h engine/apps/game_app/game_asset_bake.c engine/assets/game_app engine/tests/test_game_app_assets.c engine/CMakeLists.txt
git commit -m "game: add reproducible playable level assets"
```

### Task 3: 事务式 level 加载/卸载与真实 record 生命周期

**Files:**
- Modify: `engine/apps/game_app/main.c`
- Modify: `engine/apps/game_app/game_app.h/.c`
- Create: `engine/apps/game_app/game_render.h/.c`
- Create: `engine/apps/game_app/game_audio.h/.c`
- Create: `engine/assets/game_app/load_unload.scenario`
- Create: `engine/tests/test_game_app_lifecycle.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Task 2 资产、`BreakRuntimeCoordinator`、`scene_load_binary`、`asset_scene_restore`、`break_game_level_open/close`。
- Produces: `GameLevel` staging/commit、level generation、record render trace、完整可执行生命周期。

- [ ] **Step 1: 写真实主程序生命周期 RED**

CTest script 用 `execute_process(COMMAND "${GAME_APP}" --render=record --audio=record --assets "${ASSET_ROOT}" --fixed-step --scenario "${SCENARIO}" --trace "${WORK}/load.trace")` 启动真实应用，不是调用库 substitute。脚本必须观察到有序 trace：

```text
GAMEAPPTRACE version=1 event=runtime_running
GAMEAPPTRACE version=1 event=level_loaded generation=1
GAMEAPPTRACE version=1 event=frame frame=1 generation=1
GAMEAPPTRACE version=1 event=audio kind=listener generation=1
GAMEAPPTRACE version=1 event=level_unloaded generation=1
GAMEAPPTRACE version=1 event=level_loaded generation=2
GAMEAPPTRACE version=1 event=runtime_stopped
```

测试还启动缺失 BSCN、损坏 Flow、未知 Actor class 和缺失 Lua module 四种进程；每种必须退出 2，不能留下运行中的 worker，且不能出现 `runtime_running` 后的半 level commit。

- [ ] **Step 2: 运行进程并确认行为 RED**

Run:
```bash
cmake --build build-game-integration-normal -j3 --target game_app
ctest --test-dir build-game-integration-normal -R '^test_game_app_lifecycle_load_unload$' --output-on-failure
```
Expected: 真实应用目前未实现加载/主循环，退出 2 或 trace 缺少 `level_loaded/frame/level_unloaded`；记录实际缺失事件，而非只记编译错误。

- [ ] **Step 3: 实现 staging、coordinator 和 record 主循环**

`GameLevel` 聚合 World、Scene、BreakGame、Lua/adapter、Flow、AI、physics、渲染资源和资源请求。加载顺序为：注册组件→CPU BSCN staging→Flow/Lua/actor sidecar 验证→physics/AI/animation 创建→record 资源或 GPU `asset_scene_restore`→全部交叉引用验证→一次赋值 `game->level = candidate`。任一步失败按已初始化标志逆序释放 candidate，当前 level 指针和 generation 不变。

正常 shutdown 注册 network→audio→render→level 的 coordinator 回调：停止 admission/producers、关闭队列、drain、join、render idle、最后销毁 level。启动失败或 sticky FAILED 走独立 `game_app_level_destroy`；不得依赖 FAILED coordinator 的 stop。

record render 不链接 `engine_rhi_headless` 冒充设备；它消费 POD 并输出 frame/resource ids。`game_audio.c` 本任务实现固定容量 record 队列和 listener/stop 命令，供真实生命周期立即使用，Task 9 再添加 device worker 与完整 source 控制。每次成功 load 递增非零 level generation，失败不消耗；卸载使旧 generation 失效。

- [ ] **Step 4: 运行真实生命周期 GREEN 与回归**

Run:
```bash
ctest --test-dir build-game-integration-normal -R '^(test_game_app_lifecycle|test_runtime_core|test_break_game_level|test_scene_serial)' --output-on-failure
```
Expected: 真实进程完整 trace 顺序正确，所有失败 fixture 退出 2，focused 既有测试 PASS，无残留进程。

- [ ] **Step 5: 变异并提交**

临时在 Flow 验证前设置 `game->level = candidate`，用坏 Flow 确认旧 level 被污染的测试 RED；恢复 staging 后 GREEN。

```bash
git add engine/apps/game_app/main.c engine/apps/game_app/game_app.c engine/apps/game_app/game_app.h engine/apps/game_app/game_render.c engine/apps/game_app/game_render.h engine/apps/game_app/game_audio.c engine/apps/game_app/game_audio.h engine/assets/game_app/load_unload.scenario engine/tests/test_game_app_lifecycle.cmake engine/CMakeLists.txt
git commit -m "game: integrate transactional level lifecycle"
```

<!-- CORE_APP_COMPLETED_TASKS_1_3_END -->
### Task 4: ActionMap、触摸/手势/反馈与固定步长玩家控制

**Files:**
- Create: `engine/apps/core_app/scenario.h/.c`
- Create: `engine/apps/core_app/core_app_input.h/.c`
- Create: `engine/apps/core_app/core_app_simulation.h/.c`
- Modify: `engine/apps/core_app/core_app.c`
- Modify: `engine/assets/core_app/deterministic.scenario`
- Create: `engine/tests/test_core_app_runtime.c`
- Modify: `engine/tests/test_core_app_lifecycle.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: `InputState`、`InputExtended`、`break_game_bind_actions/eval_actions/move_wish`、`character_update`。
- Produces: 有界 scenario parser、归一化输入帧、固定 1/60 模拟和键盘/触摸等价路径。

- [ ] **Step 1: 写输入与场景行为 RED**

直接测试解析器：乱序 tick、4097 事件、64 KiB+1、未知命令、NaN 坐标、重复 quit 全部 `INVALID` 且没有部分执行。主程序测试分别用 W 键 180 tick 和触摸上拖 180 tick，玩家都从地面出生点前进超过 2 m，final position 相同到 1e-5；release/cancel 后下一 tick 不再移动。

追加触摸 id 复用和 cancel：同一 OS source id 第二次 down 的 `InputTouchId` generation 不同；cancel 不产生 tap/swipe；无反馈设备返回 `UNSUPPORTED` 但移动照常。Area enter 只请求一次 haptic，命令带 pad generation，断连后旧 request result 为 `STALE`/`DISCONNECTED`。

- [ ] **Step 2: 运行 fixed-step 主程序 RED**

Run:
```bash
cmake --build build-core-integration-normal -j3 --target test_core_app_runtime core_app
./build-core-integration-normal/test_core_app_runtime
ctest --test-dir build-core-integration-normal -R '^test_core_app_lifecycle_input_(key|touch|cancel)$' --output-on-failure
```
Expected: 玩家尚未由 ActionMap/触摸驱动，位移断言或输入 trace RED。

- [ ] **Step 3: 实现输入归一化与玩家模拟**

在 load 时注册 `forward/back/left/right/jump/interact/fire/save/load` 和 pad 绑定。脚本后端维护自己的 `InputState`/`InputExtended` 实例；`InputExtended` 初始化后绝不 memcpy，输出仅复制 touches/gestures 为普通 POD。真实后端从 `platform_input_extended()` 读取同一快照。

固定 tick 先应用该 tick 输入，再 `break_game_eval_actions`，将前进/侧移/yaw/jump 送入 `break_game_move_wish` 和 `character_update`，最后把 `cc.position` 写回 `BREAK_GAME_POSITION_COMPONENT`。交互模式 accumulator 不超 8 步；fixed-step 不读取墙钟决定模拟结果。触摸纵向位移映射到 forward，横向到 strafe；cancel/up 清零。Area callback 只排队 Flow/audio/haptic 事件。

- [ ] **Step 4: 运行键盘/触摸/确定性 GREEN**

Run:
```bash
ctest --test-dir build-core-integration-normal -R '^(test_core_app_runtime|test_core_app_lifecycle_input_|test_input_extended|test_break_game_actions|test_character)' --output-on-failure
```
Expected: 键/触摸位置一致，cancel 无粘滞，重复运行 canonical gameplay trace 逐字节相同；无触摸/反馈设备时离线仍 PASS。

- [ ] **Step 5: 变异并提交**

临时让 touch cancel 保留 active，确认 cancel 测试 RED；恢复后 GREEN。再临时把 fixed dt 换成 `engine.delta_time`，确认两次不同 pacing 的 trace 不再相同的 RED 测试有效，然后恢复。

```bash
git add engine/apps/core_app/scenario.c engine/apps/core_app/scenario.h engine/apps/core_app/core_app_input.c engine/apps/core_app/core_app_input.h engine/apps/core_app/core_app_simulation.c engine/apps/core_app/core_app_simulation.h engine/apps/core_app/core_app.c engine/assets/core_app/deterministic.scenario engine/tests/test_core_app_runtime.c engine/tests/test_core_app_lifecycle.cmake engine/CMakeLists.txt
git commit -m "core_app: drive fixed step play from actions and touch"
```

### Task 5: Actor/Lua 与 Flow Graph 同帧接线、脚本失败隔离

**Files:**
- Create: `engine/apps/core_app/core_app_script.h/.c`
- Modify: `engine/apps/core_app/core_app.c`
- Modify: `engine/assets/core_app/director.lua`
- Modify: `engine/assets/core_app/player.lua`
- Modify: `engine/assets/core_app/broken.lua`
- Modify: `engine/assets/core_app/level.fg`（由 baker 重生成）
- Modify: `engine/apps/core_app/core_app_asset_bake.c`
- Modify: `engine/tests/test_core_app_runtime.c`
- Modify: `engine/tests/test_core_app_lifecycle.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: 最终 P9 `break_game_lua` adapter、稳定 `BreakLuaHostHandle`、`break_flow_runtime_post/tick`、`break_game_entity_actions_apply` 的原子动作语义。
- Produces: 每 Actor `on_actor_tick`、有界诊断、Area→Flow→实体动作链；脚本失败不终止其他 Actor。

- [ ] **Step 1: 写 Actor/Lua/Flow 行为 RED**

固定场景有一个正常 `player.lua` 和一个首 tick 抛错的 `broken.lua`。运行 60 tick 后断言正常 Actor 的 `actor_ticks==60`，坏 Actor 的 `actor_script_failures==60`，应用仍前进且 Flow/物理仍运行；预算 trip 后只禁用对应 module 的后续 hooks，正常 Actor 继续。

Area enter 向 `break_flow_runtime_post(runtime, 1001u, player, 1.0f)` 入队，Flow 在确定的 delay tick 原子添加一个物品。断言只产生一次动作、背包数量从 0 到 1、重复 AREA tick 不重复添加。卸载后旧 Entity/HostHandle/Flow event 均返回或记录 `STALE`，不得写入新 level 的同 index 新 generation Actor。

- [ ] **Step 2: 运行脚本隔离 RED**

Run:
```bash
cmake --build build-core-integration-normal -j3 --target test_core_app_runtime core_app
./build-core-integration-normal/test_core_app_runtime
ctest --test-dir build-core-integration-normal -R '^test_core_app_lifecycle_script_flow$' --output-on-failure
```
Expected: Actor 脚本尚未调用或 Flow 尚未提交动作，正常 tick/item trace 断言 RED。若 adapter 仍缺失，停止并回到 P9 依赖，不在本文件伪造其公开函数。

- [ ] **Step 3: 实现脚本适配和 Flow 调度**

按 P9 最终公开 API 创建/销毁 adapter，让 `break_game_tick` 调用类配置的 `lua_module`。应用只提供模块 source、固定 instruction/memory budget 和诊断接收；Lua 不获得 World/physics/RHI/network 指针。正常 Actor 的脚本错误逐 Actor 记录并继续，不重试同一帧失败调用。

每个 fixed tick 的顺序固定为 `break_game_tick`→`break_flow_runtime_tick`→AI/动画意图→character/vehicle→`physics_step`→姿态写回→Area→新事件留到约定的下一 tick。Flow 动作失败保持图队列和 World 的上游事务语义，应用记 `FAILED` 但不部分补做。加载时不恢复旧 pending Flow queue，显式 reset 并从 checkpoint 的稳定 gameplay 状态重建。

- [ ] **Step 4: 运行 GREEN 和 P2/P9 回归**

Run:
```bash
ctest --test-dir build-core-integration-normal -R '^(test_core_app_runtime|test_core_app_lifecycle_script_flow|test_break_game_flow|test_break_flow_runtime|test_break_lua|test_break_game_actor)' --output-on-failure
```
Expected: 正常/坏 Actor 隔离、Flow 一次动作、stale generation 拒绝及既有测试全 PASS。

- [ ] **Step 5: 变异并提交**

临时让 adapter 首个 Lua 错误中止 `break_game_tick`，确认正常 Actor 后续 tick 测试 RED；恢复。临时删除 Area→Flow post，确认物品不变测试 RED；恢复并重跑。

```bash
git add engine/apps/core_app/core_app_script.c engine/apps/core_app/core_app_script.h engine/apps/core_app/core_app.c engine/apps/core_app/core_app_asset_bake.c engine/assets/core_app engine/tests/test_core_app_runtime.c engine/tests/test_core_app_lifecycle.cmake engine/CMakeLists.txt
git commit -m "core_app: connect actor scripts and flow actions"
```

### Task 6: 动态 AI、动画/变形、固定物理、载具与布娃娃

**Files:**
- Modify: `engine/apps/core_app/core_app_simulation.h/.c`
- Modify: `engine/apps/core_app/core_app_script.c`
- Modify: `engine/apps/core_app/core_app_asset_bake.c`
- Modify: `engine/assets/core_app/level.bscn`、`level.banm`、`deterministic.scenario`（baker 生成）
- Modify: `engine/tests/test_core_app_runtime.c`
- Modify: `engine/tests/test_core_app_lifecycle.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: 最终 P3/P4/P5 API；`physics_raycast` 只作 AI/audio 查询回调，不在 worker 写 World。
- Produces: 实际 enemy chase、nav version 失效、locomotion/morph/facial→skinning 输入、vehicle control、ragdoll pose authority。

- [ ] **Step 1: 写可玩模拟行为 RED**

真实场景脚本依次验证：玩家进入视野后敌人产生非零追逐位移；动态墙 add 后旧 `BreakAiPath` 不再 current，当前版本查询不可达或绕行，remove 后重新可查询；重复场景得到同一 enemy path/position。

动画断言速度从 0 到跑步阈值时 run 权重大于 walk；facial curve 产生 morph 权重，`anim_morph_evaluate_skinned` 改后的 64 字节顶点经 `lod_skin_positions` 得到不同位置，且 normal/UV/joint/weight 保留。载具 enter 后 ActionMap throttle 进入持久 `VehicleControlState`，接地底盘发生位移；exit 失败时 occupied 不变。脚本触发布娃娃后 ragdoll 拥有姿态，IK 不写局部 TRS；停用后恢复原 IK 状态。

- [ ] **Step 2: 运行实际场景 RED**

Run:
```bash
cmake --build build-core-integration-normal -j3 --target test_core_app_runtime core_app
./build-core-integration-normal/test_core_app_runtime
ctest --test-dir build-core-integration-normal -R '^test_core_app_lifecycle_simulation$' --output-on-failure
```
Expected: enemy/path/pose/vehicle/ragdoll 的行为断言至少一项因尚未接线而 RED；不用只链接 `break_ai` 或 engine 作为替代证据。

- [ ] **Step 3: 实现唯一模拟顺序和资源预分配**

load 时烘焙/加载 navmesh、创建 AI runtime、注册 player/enemy agent、分配 animation/morph/skinning scratch、创建物理地面/载具/布娃娃容量。tick 内不扩容：AI 先 sight+behavior+当前版本 path，再 velocity avoidance；输出只形成 movement intent，由 CharacterController/Vehicle 执行。固定 `physics_step(CORE_APP_FIXED_DT)` 后写回 Entity position、骨架局部 TRS 和 wheel contacts。

动画先 blend/locomotion/facial/morph，再 physics；若 ragdoll active，使用合并后唯一的 `ragdoll_write_local_trs`/IK 挂起合同，否则执行 IK。最后 `skeleton_apply_local_trs` 形成实际 skinning matrices。不得让 P4/P5 两套字段各自绕过对方；若最终公共头仍有冲突，回到集成门解决源合同。

- [ ] **Step 4: 运行完整模拟 GREEN 与模块回归**

Run:
```bash
ctest --test-dir build-core-integration-normal -R '^(test_core_app_runtime|test_core_app_lifecycle_simulation|test_break_ai|test_break_nav|test_break_behavior|test_anim_|test_animation|test_ragdoll|test_vehicle|test_physics)' --output-on-failure
```
Expected: 实际应用场景和既有模块测试全 PASS；两次运行 gameplay trace 逐字节一致，非有限值和 stale path 不进入快照。

- [ ] **Step 5: 变异并提交**

分别做一次动态 nav version 检查和 ragdoll/IK 互斥变异，确认对应集成断言 RED；每次恢复后重跑 GREEN。

```bash
git add engine/apps/core_app/core_app_simulation.c engine/apps/core_app/core_app_simulation.h engine/apps/core_app/core_app_script.c engine/apps/core_app/core_app_asset_bake.c engine/assets/core_app engine/tests/test_core_app_runtime.c engine/tests/test_core_app_lifecycle.cmake engine/CMakeLists.txt
git commit -m "core_app: integrate navigation animation and physics"
```

### Task 7: 世界/角色呈现、record 命令与资源 generation

**Files:**
- Modify: `engine/apps/core_app/core_app_render.h/.c`
- Modify: `engine/apps/core_app/core_app.c`
- Modify: `engine/apps/core_app/core_app_simulation.c`
- Modify: `engine/tests/test_core_app_runtime.c`
- Modify: `engine/tests/test_core_app_lifecycle.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: P6 `WorldPresentationInput/WorldFrameSnapshot/WorldPresenter`、`world_stream_want/commit_vfs`、`world_presentation_stream_mesh`、`Skeleton`、RHI frame/snapshot/idle API、Runtime IO。
- Produces: 带 frame id/level generation 的不可变渲染快照、record/RHI 两个消费者、迟完成丢弃与资源延迟销毁。

- [ ] **Step 1: 写命令内容和代际 RED**

record 场景至少提交地面、普通世界对象、V1 stream 对象、可见植被 batch、player skinned mesh 和 enemy skinned mesh。断言普通/stream 使用同一 world pipeline 逻辑，VisArea 隐藏对象没有命令，植被 batch `instance_count>1`，角色 command 的 resource generation 与当前 level 相同，动画前后帧 skinned resource version 改变。

资源测试提交 request A，unload/load 后以 A 的 request id + 旧 generation 完成，必须记 `stale_completions++`、释放 completion、当前资源字节不变；新 generation 的完成才允许 staging/commit。资源容量第 65 个请求返回 `OVERLOAD`，不覆盖任何 live slot。

- [ ] **Step 2: 运行 record 命令 RED**

Run:
```bash
cmake --build build-core-integration-normal -j3 --target test_core_app_runtime core_app
./build-core-integration-normal/test_core_app_runtime
ctest --test-dir build-core-integration-normal -R '^test_core_app_lifecycle_render_record$' --output-on-failure
```
Expected: 缺少 world/skinned/植被命令或 stale completion 仍覆盖资源的断言 RED。

- [ ] **Step 3: 实现不可变快照和实际消费者**

CoreAppThread 用 `world_stream_want` 生成驻留意图，以 `world_stream_commit_vfs` 在 CoreAppThread 提交 ECS 驻留/卸载，再用 `world_presentation_stream_mesh` 迁移 V1 tile 并进入同一 MeshGpu 上传/销毁代际；坏 tile 或上传失败不替换旧驻留资源。随后将 `WorldFrameSnapshot` 与角色 POD 写入双槽之一，标记 frame id、level generation 和资源版本；构建完成后不再写该槽。record 直接输出 canonical command。

真实模式的 skinned pipeline 使用与 `RHICapabilities.shader_variant` 匹配的现有 skinned shader，64 字节顶点缓冲，`RHIPipelineDesc.skinned_vertex=true`、`uses_texel_buffer=true`、`is_instanced=true`；帧内绑定 `skeleton_joint_slot` 的当前/历史姿态并发出 indexed draw。morph 后的 64 字节顶点在 frame begin 前完成 staging upload，不能在 render pass 内改写共享缓冲。随后在同一有效 pass 依次调用 `world_presenter_submit` 和 skinned RHI draw，再 `rhi_frame_end`、screenshot（若请求）、`rhi_present`。沿用现有主线程 GL/Vulkan 上下文，不创建不受支持的跨线程 GL 提交。

GPU/CPU 资源表槽包含 request id、generation、state 和拥有句柄。异步完成先验证 request id/generation，再 staging 完整资源，成功才交换；旧资源延迟到 `rhi_device_idle` 成功且没有快照引用后销毁。失败保留旧资源。record 模式只更新 CPU resource version，不声称发生 GPU upload。

- [ ] **Step 4: 运行 record GREEN 与 P6/RHI 回归**

Run:
```bash
ctest --test-dir build-core-integration-normal -R '^(test_core_app_runtime|test_core_app_lifecycle_render_record|test_world_presentation|test_world_presenter_fake|test_runtime_io|test_scene_serial)' --output-on-failure
```
Expected: record 命令完整、顺序稳定、隐藏对象缺席、旧代际完成被丢弃；这些结果只标 HEADLESS/RECORD，不写 GPU PASS。

- [ ] **Step 5: 变异并提交**

临时删除 level generation 比较，确认迟完成测试 RED；恢复。临时让 VisArea 输入为空时提交全部对象，确认隐藏对象测试 RED；恢复并重跑。

```bash
git add engine/apps/core_app/core_app_render.c engine/apps/core_app/core_app_render.h engine/apps/core_app/core_app.c engine/apps/core_app/core_app_simulation.c engine/tests/test_core_app_runtime.c engine/tests/test_core_app_lifecycle.cmake engine/CMakeLists.txt
git commit -m "core_app: publish versioned world and actor render commands"
```

### Task 8: 保存→继续→卸载→重载与失败完整回滚

**Files:**
- Modify: `engine/apps/core_app/core_app_checkpoint.h/.c`
- Modify: `engine/apps/core_app/core_app.c`
- Modify: `engine/apps/core_app/core_app_render.c`
- Modify: `engine/apps/core_app/core_app_audio.c`
- Create: `engine/assets/core_app/rollback.scenario`
- Modify: `engine/tests/test_core_app_runtime.c`
- Modify: `engine/tests/test_core_app_lifecycle.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Task 2 manifest、Task 3 staging、Task 5–7 所有运行时所有权。
- Produces: 完整 checkpoint 恢复、保存/加载失败旧状态不变、卸载资源清理和 stale 防护。

- [ ] **Step 1: 写全生命周期 RED**

真实应用在 tick 90 保存，继续移动 30 tick，tick 121 unload，tick 122 load。load 后玩家/敌人位置、背包、动态墙 alive、相机和昼夜必须与保存时相同；level generation 增加，RHI/音频/Lua/Flow/AI 对象都是新生命周期，旧输入和迟完成不得泄漏。保存时 trace 写 `state_hash=H`，恢复后第一帧必须再次为 H，再继续模拟的后续 hash 与 uninterrupted 对照相同。

失败矩阵必须逐项执行：截断 BSCN、错误 Flow 引用、错误 Actor generation、错误 manifest hash、GPU/record 资源 staging 失败、保存目录不可创建、第二次 save 中途失败。任何 load 失败都输出 `load_rejected` 并继续使用旧 level；任何 save 失败都不改变旧 manifest，当前游戏继续。最终 unload 后所有 live request/source/render resource 计数为 0。

- [ ] **Step 2: 运行真实 roundtrip/rollback RED**

Run:
```bash
cmake --build build-core-integration-normal -j3 --target test_core_app_runtime core_app
./build-core-integration-normal/test_core_app_runtime
ctest --test-dir build-core-integration-normal -R '^test_core_app_lifecycle_(roundtrip|rollback|save_failure)$' --output-on-failure
```
Expected: 当前只能保存部分状态或失败会替换 level，恢复 hash/旧状态不变断言 RED。

- [ ] **Step 3: 实现完整状态保存与原子切换**

保存只读当前稳定帧，先写 `runtime.bin` 中的有限 POD，再调用 `scene_state_save` 与 BSCN/Flow/Actor writers；验证全部 generation 文件可重新打开、实体/类/generation 和资源记录一致后才提交 manifest。`save_generation` 仅在 manifest 成功后递增，任何失败清理新文件。

加载创建完整候选 `CoreLevel`，包括新 BreakGame/adapter/Lua/Flow/AI/physics/资源请求；将 checkpoint 中动态障碍按稳定 id 顺序重建，旧 nav cache 不继承。候选全部可玩后才 `rhi_device_idle`、交换 level、增加 generation；旧 level 之后按依赖销毁。失败仅销毁 candidate。Flow pending queue 清空，Lua source 重载，输入清零，音频旧 source 先停止且不能 stop 新 source。

- [ ] **Step 4: 运行 roundtrip、失败矩阵与 uninterrupted 对照 GREEN**

Run:
```bash
ctest --test-dir build-core-integration-normal -R '^(test_core_app_runtime|test_core_app_lifecycle_(roundtrip|rollback|save_failure)|test_scene_state|test_scene_serial)' --output-on-failure
```
Expected: 保存/恢复 hash 相同，继续模拟与对照相同；全部损坏输入被拒绝且旧 level 可继续；失败保存旧 manifest 不变，重复 unload 不泄漏。

- [ ] **Step 5: 变异并提交**

临时让 manifest 在 payload 验证前提交，确认失败保存测试 RED；恢复。临时让加载直接覆盖 `app->level`，确认坏 BSCN 污染旧 level 测试 RED；恢复并重跑。

```bash
git add engine/apps/core_app/core_app_checkpoint.c engine/apps/core_app/core_app_checkpoint.h engine/apps/core_app/core_app.c engine/apps/core_app/core_app_render.c engine/apps/core_app/core_app_audio.c engine/assets/core_app/rollback.scenario engine/tests/test_core_app_runtime.c engine/tests/test_core_app_lifecycle.cmake engine/CMakeLists.txt
git commit -m "core_app: make checkpoint restore transactional"
```

### Task 9: 有界音频命令、null/record 降级与真实设备运行

**Files:**
- Modify: `engine/apps/core_app/core_app_audio.h/.c`
- Modify: `engine/apps/core_app/core_app.c`
- Modify: `engine/apps/core_app/core_app_asset_bake.c`
- Modify: `engine/assets/core_app/deterministic.scenario`
- Modify: `engine/tests/test_core_app_runtime.c`
- Create: `engine/tests/test_core_app_audio.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: `AudioSystem`、`audio_play_3d`、`audio_source_set_position/stop`、`audio_get_current_device`、最终 P10 合同（若其改变底层声音事件拥有权）。
- Produces: 256 命令有界队列、source generation、record/null/device 三模式和明确设备证据。

- [ ] **Step 1: 写命令顺序、容量和生命周期 RED**

固定脚本产生 listener→area enter PLAY_3D→position update→unload STOP 的顺序，record trace 逐项核对 frame id/level generation/event id/source generation。连续生成超过 256 个未消费命令时返回 `OVERLOAD` 并增加 `audio_overloads`，游戏位置/AI/保存结果不变；后续 drain 后可继续提交。

卸载后迟到的旧 PLAY/STOP 不得操作新 level source；同 index 新 source 的 generation 不同。device 初始化失败时普通 `--audio=device` 明确降级 null 并记录，离线仍可玩；`--audio=device --require-device` 在创建设备失败时退出 77，但设备创建之后任何资源/播放失败都退出 2。

- [ ] **Step 2: 运行 record 与设备 RED**

Run:
```bash
cmake --build build-core-integration-normal -j3 --target test_core_app_runtime core_app
./build-core-integration-normal/test_core_app_runtime
ctest --test-dir build-core-integration-normal -R '^test_core_app_audio_record$' --output-on-failure
```
Expected: 命令尚未按 generation 排队/停止或容量未执行的断言 RED。真实设备用例只有实际运行后才能标为已执行。

- [ ] **Step 3: 实现音频 owner 与设备泵**

Task 3 的 `CORE_APP_AUDIO_QUEUE_CAPACITY=16` 仅是本阶段 record 临时容量，不视为本 Task 的已完成合同。本 Task 必须把命令队列和 source 槽扩展为 256，并实际执行超过 256 个未消费命令返回 `OVERLOAD`、drain 后恢复的完整容量测试，不能只沿用 16 或只检查常量。

create 时预分配 256 个命令和 source 槽。CoreAppThread 只 enqueue POD；record 在 fixed tick 末有界 drain；device worker 独占 `AudioSystem`，按 budget 调 `audio_play_3d`/source control，音频实时 callback 不做文件 I/O、网络或游戏逻辑。设备路径的资产读取/解码只能发生在非实时设备 owner 的准备路径，不增加实时分配。

shutdown 顺序为停止新命令→关闭队列→有界 drain/停止 sources→join worker→销毁 AudioSystem。source stop 同时验证 level/source generation；失败保留可诊断状态，不越界访问旧槽。普通无设备降级不影响输入/模拟/RHI。

- [ ] **Step 4: 运行 record GREEN 和真实设备证据**

Run:
```bash
ctest --test-dir build-core-integration-normal -R '^(test_core_app_runtime|test_core_app_audio_record|test_audio)$' --output-on-failure
ctest --test-dir build-core-integration-normal -R '^test_core_app_audio_device$' --output-on-failure --verbose
```
Expected: record/现有 audio 测试 PASS；设备用例输出实际 device name、创建/播放/stop/destroy 顺序和 source 状态。77 只记 UNAVAILABLE；设备运行不声称听感通过，实际听测需另行记录。

- [ ] **Step 5: 变异并提交**

临时让 full queue 覆盖最老命令，确认容量/顺序测试 RED；恢复。临时让 source stop 忽略 generation，确认 unload/reload 测试 RED；恢复并重跑。

```bash
git add engine/apps/core_app/core_app_audio.c engine/apps/core_app/core_app_audio.h engine/apps/core_app/core_app.c engine/apps/core_app/core_app_asset_bake.c engine/assets/core_app/deterministic.scenario engine/tests/test_core_app_runtime.c engine/tests/test_core_app_audio.cmake engine/CMakeLists.txt
git commit -m "core_app: route gameplay through bounded audio commands"
```

### Task 10: 独立可选认证网络通道与客户端权威边界

**Files:**
- Create: `engine/apps/core_app/core_app_network.h/.c`
- Modify: `engine/apps/core_app/main.c`
- Modify: `engine/apps/core_app/core_app.c`
- Modify: `engine/CMakeLists.txt`
- Create: `engine/tests/test_core_app_network.cmake`
- Create: `engine/tests/test_core_app_net_client.c`
- Modify: `engine/tests/test_core_app_target_contract.cmake`

**Interfaces:**
- Consumes: 可选 `break_net` reactor、Session、owned message、最终 P8 接口（仅在它合入后消费其真实合同）。
- Produces: 默认 disabled 的网络通道；认证后才发送只读 POD snapshot；任何网络输入都不能直接修改本地 World/生命/伤害。

- [ ] **Step 1: 写离线等价与越权 RED**

无 Snowflake/no-tests 树运行同一 deterministic scenario 两次（编译时不带网络和显式 `--network` 被拒），合法离线 trace 必须逐字节相同；`nm` 检查离线 `core_app` 不含 `break_net_`/`break_session_`/`snow_` 符号。

可选 loopback 用例启动真实 `core_app` 和认证测试客户端，应用参数精确使用 `--network --bind 127.0.0.1:0 --tls-cert "${SNOWFLAKE_SOURCE_DIR}/tests/common/fixtures/ssl/snow_test_cert.pem" --tls-key "${SNOWFLAKE_SOURCE_DIR}/tests/common/fixtures/ssl/snow_test_key.pem" --psk-env CORE_APP_TEST_PSK --port-file "${WORK}/server.port"`。客户端完成 TLS/AUTH 后接收带 schema hash、frame id、level generation 和 Entity index/generation 的 snapshot。客户端发送未知 message id、伪造 damage/health 字段、旧 generation 和未认证消息；应用必须拒绝/关闭或记录分类错误，本地玩家位置、背包和 fire-intent 序号完全不变，离线 tick 继续。网络 outbound 满返回 `OVERLOAD` 并计数，不阻塞/回写 CoreAppThread。

- [ ] **Step 2: 运行无 Snowflake 与可选网络 RED**

Run:
```bash
cmake --build build-core-integration-no-tests -j3 --target core_app
ctest --test-dir build-core-integration-normal -R '^test_core_app_(target_contract|network_offline)$' --output-on-failure
if test -n "$SNOWFLAKE_SOURCE_DIR"; then
  cmake -S engine -B build-core-integration-network -DENGINE_BUILD_TESTS=ON -DCORE_APP_ENABLE_NETWORK=ON -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR="$SNOWFLAKE_SOURCE_DIR" -DENGINE_RHI_BACKEND=auto
  cmake --build build-core-integration-network -j3 --target core_app test_core_app_net_client
  ctest --test-dir build-core-integration-network -R '^test_core_app_network_loopback$' --output-on-failure
fi
```
Expected: 离线合同/真实 snapshot 行为先 RED。没有设置 pinned `SNOWFLAKE_SOURCE_DIR` 时明确记录网络 lane NOT RUN，不将 `if` 未执行写成 PASS。

- [ ] **Step 3: 实现独立通道和认证边界**

只有 `CORE_APP_ENABLE_NETWORK AND BREAK_ENABLE_SNOWFLAKE` 才添加 `core_app_network.c` 的真实传输编译路径并链接 `break_net`。`main.c` 只在该编译路径接受 `--network`、`--bind HOST:PORT`、`--tls-cert PATH`、`--tls-key PATH`、`--psk-env NAME`、`--port-file PATH`，缺少任何一项即退出 2；secret 只从指定环境变量读取，不写 trace。应用网络对象只拥有 reactor/Session/acceptor 和有界 POD 队列；CoreAppThread 每 tick 最多 poll 64 个 event，回调只复制/入队。snapshot 使用固定小端字段和版本，不含指针、伤害结果或客户端权威生命。

只有认证 Session 的 connection key 可作为网络身份；message registry 仅注册明确的 snapshot/control 消息，未知/越权消息 fail closed。发送快照失败只影响网络诊断，禁止回滚或修改本地游戏。停止顺序为停止 admission→停止 reactor producer→drain/close sessions→销毁 transport；离线模式这些对象从不创建。

- [ ] **Step 4: 运行离线 GREEN 与可选 loopback 证据**

Run: 重复 Step 2 全部命令，并在网络树额外运行：
```bash
ctest --test-dir build-core-integration-network -R '^(test_core_app_network_|test_break_net_adapter|test_break_net_tls|test_break_authority)' --output-on-failure
```
Expected: 离线 trace 与无网络构建一致；真实认证客户端收到 snapshot，所有伪造/未认证输入无 gameplay mutation，overload 可观察且离线 tick 不阻塞。

- [ ] **Step 5: 变异并提交**

临时允许未认证 connection 收到 snapshot，确认网络测试 RED；恢复。临时让网络输入直接写 player position，确认权威不变量测试 RED；恢复并重跑离线和网络 lane。

```bash
git add engine/apps/core_app/core_app_network.c engine/apps/core_app/core_app_network.h engine/apps/core_app/main.c engine/apps/core_app/core_app.c engine/CMakeLists.txt engine/tests/test_core_app_network.cmake engine/tests/test_core_app_net_client.c engine/tests/test_core_app_target_contract.cmake
git commit -m "core_app: add optional authenticated snapshot channel"
```

### Task 11: 真实 Vulkan 窗口像素证据与 OpenGL 最终降级/对照

**Files:**
- Modify: `engine/apps/core_app/core_app_render.c`
- Modify: `engine/apps/core_app/main.c`
- Modify: `engine/assets/core_app/rollback.scenario`
- Create: `engine/tests/test_core_app_gpu.cmake`
- Create: `engine/tests/test_core_app_image.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `docs/design/core_app_integration.md`

**Interfaces:**
- Consumes: Task 7 RHI 消费者、现有 Vulkan→OpenGL runtime chain、`rhi_screenshot`、P6 shader/pipeline。
- Produces: 真实窗口/PPM 像素/backend/device/validation 证据；record 结果与 GPU 证据永久分栏。

- [ ] **Step 1: 写真实进程图形 RED**

CTest 分别启动：

`rollback.scenario` 在 tick 30、60、90（save 前）、120（save 后继续移动）和 150（unload/load 后）放置 `screenshot`，从而同一真实进程同时覆盖像素与保存/重载。`--screenshot` 接受且只接受一个 `%u`，应用在每次事件中用当前 tick 替换它；没有 `%u` 时只允许一个 screenshot 事件，避免静默覆盖。

```bash
cmake -E env BREAK_RHI_BACKEND=vulkan BREAK_RHI_NO_FALLBACK=1 BREAK_VK_VALIDATION=1 \
  "$PWD/build-core-integration-normal/core_app" --render=vulkan --require-device --audio=null --fixed-step \
  --scenario "$PWD/engine/assets/core_app/rollback.scenario" \
  --screenshot "$PWD/build-core-integration-normal/core_app_vk_%u.ppm" --trace "$PWD/build-core-integration-normal/core_app_vk.trace"
cmake -E env BREAK_RHI_BACKEND=opengl BREAK_RHI_NO_FALLBACK=1 \
  "$PWD/build-core-integration-normal/core_app" --render=opengl --require-device --audio=null --fixed-step \
  --scenario "$PWD/engine/assets/core_app/rollback.scenario" \
  --screenshot "$PWD/build-core-integration-normal/core_app_gl_%u.ppm" --trace "$PWD/build-core-integration-normal/core_app_gl.trace"
```

应用必须在 trace 写实际 `backend`、`device_name`、frame present 数、validation count 和 save/unload 结果。image test 读取各 tick PPM：地面/玩家/敌人/植被/流式对象都有非背景像素，隐藏黄色网格为 0；移动前后玩家像素质心发生变化，动画两帧角色区域有差异，昼夜帧亮度显著变化，重载后的场景对象与保存时可见。两后端比较允许光栅化误差，但每个语义对象和移动/明暗趋势都必须成立。

- [ ] **Step 2: 在真实设备上观察 RED 或诚实缺证**

Run:
```bash
cmake --build build-core-integration-normal -j3 --target core_app test_core_app_image
ctest --test-dir build-core-integration-normal -R '^test_core_app_gpu_(vk|gl|fallback)$' --output-on-failure --verbose
```
Expected: 若应用还没有完整 RHI draw，真实截图缺对象/趋势而 RED。没有 display/device 时在设备创建前退出 77，报告 UNAVAILABLE；平台已创建而 shader/draw/readback 失败必须 FAIL，不得转成 skip。

- [ ] **Step 3: 修正真实 RHI 路径并保留后端门**

实际设备信息来自 `RHIDeviceInfo`；多后端时用 `rhi_runtime_active_backend()`，单后端用 capabilities.backend 交叉核对。Vulkan 测试强制无 fallback；另用 `BREAK_RHI_FAIL_VULKAN=1` 启动 auto 模式验证创建期最后降级到 OpenGL。成功创建设备后 device loss 不切换后端，按现有 RHI 合同失败退出。

截图只在 acquired frame 内调用 `rhi_screenshot`，RGBA 转顶层向下的 PPM 时做明确 R/B 和行序处理；不在 record 模式生成“截图”。修复所有真实 shader/binding/stride/帧生命周期问题后，检查 Vulkan validation 为 0。

- [ ] **Step 4: 运行 Vulkan、OpenGL 对照和创建失败降级 GREEN**

Run:
```bash
ctest --test-dir build-core-integration-normal -R '^test_core_app_gpu_vk$' --output-on-failure --verbose
ctest --test-dir build-core-integration-normal -R '^test_core_app_gpu_(gl|fallback)$' --output-on-failure --verbose
ctest --test-dir build-core-integration-normal -R '^(test_world_presentation_(vk|gl)|test_rhi_runtime_fallback_)' --output-on-failure
```
Expected: 有设备时全部实际 PASS，保存日志/PPM 路径、backend/device、validation 和像素统计；无设备只保留 UNAVAILABLE，不写“图形通过”。

- [ ] **Step 5: 图形变异并提交**

临时让 Vulkan required 模式接受 OpenGL fallback，确认 backend 门 RED；恢复。临时从提交中移除 enemy draw，确认真实像素测试 RED；恢复并重跑 Vulkan。

```bash
git add engine/apps/core_app/core_app_render.c engine/apps/core_app/main.c engine/assets/core_app/rollback.scenario engine/tests/test_core_app_gpu.cmake engine/tests/test_core_app_image.c engine/CMakeLists.txt docs/design/core_app_integration.md
git commit -m "test: verify playable rendering on real RHI devices"
```

### Task 12: 确定性 fuzz、normal/ASan+UBSan/TSan 与无 Snowflake 验证

**Files:**
- Create: `engine/tests/fuzz_core_app_checkpoint.c`
- Create: `engine/tests/fuzz_core_app_scenario.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `.github/workflows/ci.yml`
- Create: `.superpowers/sdd/core-app-integration-report.md`

**Interfaces:**
- Consumes: 全部真实应用 readers/staging、现有 fuzz smoke 约定。
- Produces: 两个显式 fuzz target、三棵验证树、no-tests/no-Snowflake 真实进程验证。

- [ ] **Step 1: 写 fuzz smoke 和线程/回滚覆盖 RED**

`fuzz_core_app_checkpoint` 以固定 seed 对合法 checkpoint 的 manifest/BSCN/Flow/runtime bytes 做截断、位翻转、计数/长度/代际变异；每次调用真实 probe/load，要求成功或分类失败，均不 crash、不越界、不污染一个同时存活的 sentinel level。`fuzz_core_app_scenario` 对文本长度、tick、坐标、路径和命令做同样变异，部分执行计数必须为 0。

先注册 smoke，但不构建 target 时 CTest 必须是可见 Not Run/失败，不能算 PASS。注册沿用现有显式 fuzz 形式：

```cmake
if(ENGINE_BUILD_FUZZ_SMOKE)
    add_test(NAME fuzz_core_app_checkpoint_smoke
             COMMAND fuzz_core_app_checkpoint 500 31)
    add_test(NAME fuzz_core_app_scenario_smoke
             COMMAND fuzz_core_app_scenario 500 37)
    set_tests_properties(fuzz_core_app_checkpoint_smoke
                         fuzz_core_app_scenario_smoke PROPERTIES LABELS "fuzz")
endif()
```

TSan focused 覆盖 audio producer/consumer、Runtime IO completion、网络 enabled 时的 callback/CoreAppThread poll和 shutdown；普通/ASan 覆盖保存失败与迟完成释放。

- [ ] **Step 2: 运行 fuzz/并发 RED**

Run:
```bash
cmake -S engine -B build-core-integration-asan -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON -DENGINE_BUILD_FUZZ_SMOKE=ON -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-core-integration-asan -j3 --target fuzz_core_app_checkpoint fuzz_core_app_scenario test_core_app_runtime core_app
ctest --test-dir build-core-integration-asan -L fuzz --output-on-failure
```
Expected: 新 fuzz 初始暴露的解析/回滚问题为 RED；如仅因 target 未构建，先构建并重新运行，记录实际行为 RED。修复前不缩减输入边界。

- [ ] **Step 3: 修复 fuzz/所有权问题并完成 normal**

对每个 fuzz/ASan/TSan 发现先保留最小 reproducer 测试，再修复 checked arithmetic、失败所有权或同步源因。随后运行：

```bash
cmake -S engine -B build-core-integration-normal -DENGINE_BUILD_FUZZ_SMOKE=ON
cmake --build build-core-integration-normal -j3
ctest --test-dir build-core-integration-normal -LE 'graphics|fuzz|network|audio_device' --output-on-failure -j3
cmake --build build-core-integration-normal -j3 --target fuzz_scene_serial fuzz_net_packet fuzz_decode_image fuzz_vfs_pak fuzz_asset_gltf fuzz_core_app_checkpoint fuzz_core_app_scenario
ctest --test-dir build-core-integration-normal -L fuzz --output-on-failure
```
Expected: GREEN：所有非图形和显式 fuzz PASS；图形/audio/network 的排除只用于此 CPU lane，最终结果另表列出，不能隐藏。

- [ ] **Step 4: 完成 ASan+UBSan 与 TSan**

Run:
```bash
cmake --build build-core-integration-asan -j3
ctest --test-dir build-core-integration-asan -LE 'graphics|network|audio_device' --output-on-failure
cmake -S engine -B build-core-integration-tsan -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_IPO=OFF -DENGINE_USE_TSAN=ON -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-core-integration-tsan -j3
ctest --test-dir build-core-integration-tsan -LE 'graphics|fuzz|network|audio_device' --output-on-failure
```
Expected: 实际运行通过且无 sanitizer report。若命中仓库既有无关失败，记录精确测试/诊断，不通过新增排除掩盖；P12 新增测试必须全部实际运行。

- [ ] **Step 5: 验证无 Snowflake/no-tests 应用并提交**

Run:
```bash
cmake --build build-core-integration-no-tests -j3 --target core_app
cmake -E chdir engine ../build-core-integration-no-tests/core_app --render=record --audio=record --fixed-step --scenario assets/core_app/deterministic.scenario --checkpoint /tmp/core-app-no-tests-save --trace /tmp/core-app-no-tests.trace
```
Expected: 退出 0，完整 load→input→simulation→record/audio→save→unload→shutdown trace；无 Snowflake 源码也可构建/运行。清理临时输出后 `git status --short` 不含生成物。

```bash
git add engine/tests/fuzz_core_app_checkpoint.c engine/tests/fuzz_core_app_scenario.c engine/CMakeLists.txt .github/workflows/ci.yml .superpowers/sdd/core-app-integration-report.md
git commit -m "test: verify playable integration across build lanes"
```

### Task 13: 文档、独立代码评审与最终交付门

**Files:**
- Modify: `docs/design/core_app_integration.md`
- Modify: `docs/design/cry_style_gameplay.md`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/superpowers/plans/2026-11-03-core-app-integration.md`（仅勾实际完成步骤）
- Modify: `.superpowers/sdd/core-app-integration-report.md`
- Modify only for confirmed P12 findings: 上述应用/测试文件

**Interfaces:**
- Consumes: 全部真实命令输出、设备证据和独立 reviewer 发现。
- Produces: 与实际 target/行为一致的文档、完整证据台账和可审查最终提交。

- [ ] **Step 1: 更新设计/状态文档并写文档合同 RED**

`core_app_integration.md` 写入真实 CLI、target 链接图、固定顺序、checkpoint 字段、generation/失败回滚和 evidence ladder。`cry_style_gameplay.md` 开头不得再写“可玩原型只有 headless、没有声音/网络”来概括新应用；应区分旧 `test_cry_style_prototype` 与新 `core_app`。`runtime_overview.md` 只把实际接入 coordinator 的子系统标为已接入。`Implementation_Status.md` 顶部追加实际测试数、真实设备和未做事项，不复制计划中的预期结果。

先运行文档检查：若 target contract 中的 target/CLI/测试名与文档不一致则 RED；若文档含 `record.*GPU` 等同证据的表述或把未执行 lane 写成 PASS，也必须 RED。

- [ ] **Step 2: 运行最终全套与文档检查**

Run:
```bash
git diff --check
ctest --test-dir build-core-integration-normal -N
./build-core-integration-normal/test_core_app_runtime
ctest --test-dir build-core-integration-normal -R '^test_core_app_' --output-on-failure
```
Expected: GREEN：所有实际注册的 P12 测试均按各自 label 运行；UNAVAILABLE 单独列出，不用全量 PASS 掩盖。核对无旧二进制冒充新源码结果，必要时先重建对应 target。

- [ ] **Step 3: 独立评审并修复发现**

派一名未参与实现的 reviewer，提供完整 branch diff、总体设计 P12/共同约束和本计划。要求实际阅读代码与测试，优先审查：level/save 原子性、Lua/Flow 错误隔离、Entity/resource/source generation、快照不可变、GL/Vulkan 线程与帧边界、音频实时路径、网络认证/客户端权威、测试是否真正执行 `core_app`、文档证据是否夸大。

Critical/Important 必须先添加能复现的 RED，再修复并重跑受影响 normal/sanitizer/graphics/network lane。评审者未运行测试时，报告必须明确“只读评审”，不能把其身份当作测试证据；没有独立 reviewer 时 P12 不得宣称评审门已完成。

- [ ] **Step 4: 最终清洁检查与提交**

Run:
```bash
git diff --check
git status --short
git log --oneline --decorate -15
```
Expected: 无 whitespace error、无变异源码、无构建/log/PPM/checkpoint 生成物；计划只勾已做步骤，报告列出所有命令结果和剩余缺证。最终提交仍在 `cry-integration`，不 push、不改 master。

```bash
git add docs/design/core_app_integration.md docs/design/cry_style_gameplay.md docs/design/runtime_overview.md docs/Implementation_Status.md docs/superpowers/plans/2026-11-03-core-app-integration.md .superpowers/sdd/core-app-integration-report.md
git commit -m "docs: record playable integration evidence"
```

## 完成定义与证据分栏

只有以下条件同时满足，P12 才可标为代码与行为完成：

1. `core_app` 是可执行主程序；CTest 通过真实进程证明加载→输入→模拟→渲染/音频命令→保存→卸载，而非仅链接库或测试 helper。
2. 正常、ASan+UBSan、TSan 的 P12 与相关回归实际 PASS，无 sanitizer report；确定性重放、脚本隔离、失败回滚和 generation 变异证据齐全。
3. record/headless 只进入 CPU/命令证据栏；真实 Vulkan 窗口像素、OpenGL 最终降级/对照、真实音频设备、可选认证网络分别有实际日志。任一环境不可用必须保留 UNAVAILABLE，不以另一栏顶替。
4. 无 Snowflake/no-tests 构建仍可玩；网络关闭、网络满或断连不改变离线模拟和客户端权威边界。
5. target contract、设计/状态文档、独立评审、fuzz smoke 和 `git diff --check` 全部有实际结果；工作树没有测试生成物。
