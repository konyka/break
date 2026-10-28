# Unreal Engine 5.8.3 inventory

## 简介

本文是跨引擎 inventory 阶段 1 的 Unreal 列，基线为本仓库记录的 **Unreal Engine 5.8.3 release**。目标不是复述 UE 的全部 32 章，而是按跨引擎设计固定的 17 个模块，逐项记录可核验能力，并给出与 Break 的比较边界。

UE 证据主要来自本仓库的 [`docs/ue5.8.3/README.md`](../ue5.8.3/README.md)、对应专题设计文档和 [`32_gap_audit.md`](../ue5.8.3/design/32_gap_audit.md)。这些文档将 Unreal 源码根记录为 `/home/timeshift/opensource/game_engine/unreal/UnrealEngine-5.8.3-release`，引擎相对路径以 `$E=Engine/` 表示。本文不把章节标题、模块名或 API 索引自动等同于完整 runtime 行为。

## 证据口径

- **源码优先**：优先引用专题文档中已定位的 C++/C#/Shader 路径；其次引用该专题的本地设计文档；导航和审计文档用于确认范围与限制。
- **状态含义**：`已核验` 表示本地 UE 资料中有明确接口、实现路径或流程证据；`部分核验` 表示只确认了入口/模块/静态路径，不能推出全平台或产品行为；`资料不足` 表示当前资料没有足够证据，本文不推测。
- **Break 口径**：Break 只引用当前 [`Implementation_Status.md`](../Implementation_Status.md)、[`Architecture_Overview.md`](../Architecture_Overview.md) 和明确源码路径。focused/test-only API 不写成正式 runtime；编译存在不写成运行时完成。
- **统一顺序**：以下 17 节固定为：模块系统、ECS/entity、world/scene、tasks、threads/messages、networking、UI/input、rendering/RHI、physics、audio、assets/hot reload、editor、diagnostics/remote debugging、crash upload、online update、security/anti-cheat、large-world/streaming。

## 1. 模块系统

- **范围**：核心模块、插件描述、模块加载相位、目标构建和启动依赖。
- **已知能力**：UE 使用 `FModuleManager`/`IModuleInterface`，插件由 `FPluginManager` 和 `.uplugin` 描述驱动；UBT/TargetRules 决定目标启用、禁用和构建插件，启动链由 `FEngineLoop` 组织。
- **证据/来源**：[`18_launch_engine_loop_modules.md`](../ue5.8.3/design/18_launch_engine_loop_modules.md)、[`24_plugins_catalog_runtime.md`](../ue5.8.3/design/24_plugins_catalog_runtime.md)、[`19_build_system_uht_uat.md`](../ue5.8.3/design/19_build_system_uht_uat.md)、[`README.md` 第 18/19/24/25 章](../ue5.8.3/README.md)。
- **比较 Break**：Break 的模块边界是目录、头文件和 CMake target；[`Architecture_Overview.md`](../Architecture_Overview.md) 记录 `engine/`、`framework/`、`platform/` 分层。Break 没有 UE 式插件/UBT/UHT 证据；不要把 CMake 静态库等同为动态模块热加载。

## 2. ECS/entity

- **范围**：对象/实体生命周期、组件、反射/序列化对象模型及批量实体框架。
- **已知能力**：UE 的 `UObject`/`UClass`/`UPROPERTY` 提供对象、反射、GC 和序列化基础；`AActor`/`UActorComponent` 构成 Engine gameplay entity 形态；Mass Entity 提供 chunk/data-oriented 的实体框架。
- **证据/来源**：[`03_coreuobject.md`](../ue5.8.3/design/03_coreuobject.md)、[`04_engine_framework.md`](../ue5.8.3/design/04_engine_framework.md)、[`15_ai_gameplay_mass.md`](../ue5.8.3/design/15_ai_gameplay_mass.md)。`32_gap_audit.md` 明确指出 UObject 边缘语义、Mass 默认值和 observer 协议仍有未核验项。
- **比较 Break**：Break 的 ECS、snapshot/delta/schema/AoI 事实见 [`Architecture_Overview.md` ECS 边界](../Architecture_Overview.md#ecs-snapshot--replication--aoi-边界) 及 `engine/src/ecs/`；这些 focused sources 当前直接编入测试 target，不在正式 `engine` static library。两者实体模型、反射/GC 与 replication 语义不可直接等价。

## 3. world/scene

- **范围**：World、Level、Actor 场景组织、场景生命周期和世界数据层。
- **已知能力**：`UEngine`、`UWorld`、`ULevel`、Actor/Component 组成世界运行框架；World Partition、Data Layer、Level Instance 和 streaming generation 负责大场景组织与加载。
- **证据/来源**：[`04_engine_framework.md`](../ue5.8.3/design/04_engine_framework.md)、[`05_world_partition_streaming.md`](../ue5.8.3/design/05_world_partition_streaming.md)。`32_gap_audit.md` 将 WorldPartition/HLOD 内部、DataLayer 复制影响和生成器算法列为仍无法确认。
- **比较 Break**：Break 的架构文档列出 renderer/ECS/asset/physics，但没有由当前状态文档证明 UE 式 World/Level/Actor runtime。`engine/src/renderer/` 和 `engine/src/ecs/` 只能作为局部模块证据，不能推断完整场景管理。

## 4. tasks

- **范围**：任务图、异步任务、并行执行、等待和任务依赖。
- **已知能力**：UE 同时记录 TaskGraph、`UE::Tasks`、LowLevelTasks、线程池和异步任务接口；任务可与渲染、物理、动画、音频、IO 等子系统交接。
- **证据/来源**：[`02_core_hal_threading.md`](../ue5.8.3/design/02_core_hal_threading.md)、[`26_threading_concurrency_overall.md`](../ue5.8.3/design/26_threading_concurrency_overall.md)、[`31_message_event_mechanisms.md`](../ue5.8.3/design/31_message_event_mechanisms.md)。具体 worker 数量、平台 affinity 和部分 runtime 默认值为 `资料不足`。
- **比较 Break**：Break 的 `engine/src/task/task.h`/`task.c` 是进程内单实例 TaskSystem；`Architecture_Overview.md` 明确记录 worker、wait 和自等待约束。不能以接口存在推断两边调度器的吞吐、优先级或执行顺序相同。

## 5. threads/messages

- **范围**：Game/Render/RHI/Audio/IO 线程、队列、事件、委托和消息总线。
- **已知能力**：UE 有 GT/RT/RHI 等渲染线程链、`TQueue`、delegate、Message Bus、FieldNotification、Ticker/Timer/Promise 等事件与回调入口。
- **证据/来源**：[`26_threading_concurrency_overall.md`](../ue5.8.3/design/26_threading_concurrency_overall.md)、[`29_render_thread_deep.md`](../ue5.8.3/design/29_render_thread_deep.md)、[`31_message_event_mechanisms.md`](../ue5.8.3/design/31_message_event_mechanisms.md)。跨平台 callback 线程、内存可见性、取消和完整 wire 语义在审计中多处标为 `资料不足`。
- **比较 Break**：Break 的网络回调不得访问 GameThread/ECS/World/Lua/UI/RHI；Session 是 GameThread-only，具体约束见 [`Architecture_Overview.md` Snowflake 边界](../Architecture_Overview.md#snowflake-c11-网络适配器边界)。不要把 Break 的有界 queue 与 UE Message Bus 的功能/可靠性直接类比。

## 6. networking

- **范围**：socket/IO、NetDriver、连接、复制、可靠性、预测和网络消息。
- **已知能力**：UE 提供 `ISocketSubsystem`、`UNetDriver`、Actor replication、Iris replication、PacketHandler、NetworkPrediction，以及 HTTP/Messaging 等扩展面。
- **证据/来源**：[`11_networking_replication.md`](../ue5.8.3/design/11_networking_replication.md)、[`27_network_io_threads.md`](../ue5.8.3/design/27_network_io_threads.md)、[`24_plugins_catalog_runtime_part4.md`](../ue5.8.3/design/24_plugins_catalog_runtime_part4.md) 中 NetworkPrediction 条目。Oodle/Reliability、Iris 内部协议、平台后端、WebSocket/SSL、Replay 和 MultiServer 细节为 `资料不足`。
- **比较 Break**：Break 当前有 18-byte envelope、bounded adapter queues、Session 状态机和真实 loopback focused 证据；`break_net` 只在测试+Snowflake 配置生成，正式 demo 不链接它。ECS replication/AoI 仍与正式 runtime/session integration 分离，不能宣称 UE 级网络栈。

## 7. UI/input

- **范围**：窗口消息泵、输入设备、Slate/UMG、文本、IME、焦点和手柄。
- **已知能力**：UE 的 `FSlateApplication`/`SWidget`/UMG 提供 Slate widget 树、用户控件、输入路由、焦点和绘制；Enhanced Input、IME、剪贴板、触摸和手柄有专门入口。
- **证据/来源**：[`10_slate_umg_input.md`](../ue5.8.3/design/10_slate_umg_input.md)、[`28_ui_input_threads.md`](../ue5.8.3/design/28_ui_input_threads.md)。非 Windows 平台实现、HarfBuzz/ICU 内部和部分输入 callback 线程仍为 `资料不足`。
- **比较 Break**：Break 的 `engine/src/ui/` 是调试 UI/字体渲染，输入和窗口由 `engine/src/platform/` 提供；`Architecture_Overview.md` 记录 UI 必须在所属主循环线程执行。Break 不具备 UE Slate/UMG 的产品级 widget/editor 体系证据。

## 8. rendering/RHI

- **范围**：RHI、渲染线程、RenderCore/RDG、shader/material、renderer 和后端。
- **已知能力**：UE 5.8.3 有 `FRHICommandList`/`FRHIResource`、RenderCore/RDG、RenderThread、延迟 renderer，以及 Nanite/Lumen/VSM 等 renderer 方向；后端包含 Vulkan、D3D12、Metal、OpenGL/Null 等平台域。
- **证据/来源**：[`06_rhi.md`](../ue5.8.3/design/06_rhi.md)、[`07_rendercore_rdg_renderthread.md`](../ue5.8.3/design/07_rendercore_rdg_renderthread.md)、[`08_renderer_deferred_nanite_lumen.md`](../ue5.8.3/design/08_renderer_deferred_nanite_lumen.md)、[`29_render_thread_deep.md`](../ue5.8.3/design/29_render_thread_deep.md)。Metal 深度、barrier/cache 算法、部分 shader/material 内部为 `资料不足`。
- **比较 Break**：Break 的 RHI 后端状态和证据等级见 [`Architecture_Overview.md` 平台支持](../Architecture_Overview.md#平台支持)；当前模型为编译期单后端静态库，GL deprecated，Vulkan/Metal/D3D12 各有不同 runtime 收据。不能用 UE 的后端名推断 Break 已支持同一 feature。

## 9. physics

- **范围**：刚体、碰撞、solver、角色/车辆、布料、破坏和 physics thread。
- **已知能力**：UE 以 Chaos/PhysicsCore 为主，包含 `FPhysicsSolver`、`FPBDRigidsSolver`、BodyInstance、碰撞、车辆、布料和破坏相关模块。
- **证据/来源**：[`12_physics_chaos.md`](../ue5.8.3/design/12_physics_chaos.md)、[`12_physics_chaos_part2.md`](../ue5.8.3/design/12_physics_chaos_part2.md)、[`26_threading_concurrency_overall.md`](../ue5.8.3/design/26_threading_concurrency_overall.md)。solver 内部算法、线程默认值、ChaosVD/Mover/cloth 细节和 headless runtime 为 `资料不足`。
- **比较 Break**：Break 架构只明确列出 `engine/src/physics/` 物理模块，当前文档没有提供与 Chaos solver 同层次的实现/运行证据。模块目录存在不等于角色、破坏、布料或并行 solver 已交付。

## 10. audio

- **范围**：AudioDevice、Mixer、音频线程、MetaSound、submix、平台设备和插件 DSP。
- **已知能力**：UE 有 `FAudioDevice`、`FAudioThread`、`FMixerDevice`、Audio Mixer、Submix、MetaSound 和平台 audio modules。
- **证据/来源**：[`14_audio.md`](../ue5.8.3/design/14_audio.md)、[`26_threading_concurrency_overall.md`](../ue5.8.3/design/26_threading_concurrency_overall.md)。`IAudioTaskQueue` 的现行替代路径已在审计中修正为 `IAudioTask`/`FAsyncTask`；平台优先级、双缓冲泵、插件 DSP 和 Quartz 细节为 `资料不足`。
- **比较 Break**：Break 的 `engine/src/audio/` 基于 miniaudio，架构文档确认设备枚举/选择 API，但没有 UE MetaSound/submix/音频图的证据。不可把 miniaudio 设备 API写成完整 audio production stack。

## 11. assets/hot reload

- **范围**：对象/资产注册、异步 IO、cook/package、shader/derived data、热重载和虚拟化。
- **已知能力**：UE 有 AssetRegistry、异步 package/object load、IoDispatcher、Pak/IoStore、Cook、Derived Data Cache、Interchange 和 virtualization 相关模块；编辑器/开发流程支持资源变更与派生数据处理。
- **证据/来源**：[`03_coreuobject.md`](../ue5.8.3/design/03_coreuobject.md)、[`09_shader_material_ddc.md`](../ue5.8.3/design/09_shader_material_ddc.md)、[`20_assets_cook_package_io.md`](../ue5.8.3/design/20_assets_cook_package_io.md)。Zen/StorageServer 协议、CookOnTheFly 字段、编译器/第三方 codec 和完整热重载行为为 `资料不足`。
- **比较 Break**：Break 的 `engine/src/asset/` 包含 asset/hotreload/vfs，架构文档将文件监视列为 inotify/kqueue/FSEvents 驱动的开发期热重载。Break 没有 UE Cook/IoStore/Zen 产品链证据；目录/API 不能替代端到端 package/cook 验证。

## 12. editor

- **范围**：UnrealEd、Level Editor、Content Browser、属性编辑、PIE、事务和编辑器工具。
- **已知能力**：UE 提供 `UUnrealEdEngine`、LevelEditor、ContentBrowser、PropertyEditor、AssetEditorToolkit、事务/Undo、PIE 和大量 editor modules/plugins。
- **证据/来源**：[`22_editor_core.md`](../ue5.8.3/design/22_editor_core.md)、[`24_plugins_catalog_runtime_part4.md`](../ue5.8.3/design/24_plugins_catalog_runtime_part4.md)。审计已确认职责类为 `UEdMode` 而非 `UEditorModeBase`；Concert、EditorDomain/Zen、Commandlet 完整执行和部分插件行为为 `资料不足`。
- **比较 Break**：Break 的架构层有 application/framework 和待创建的编辑器文档，但当前状态没有 UE 级 editor runtime。`engine_demo`/`dxx_break` 是 demo/runtime 目标，不应被写成内容编辑器或 PIE。

## 13. diagnostics/remote debugging

- **范围**：日志、Stats/CSV、Trace/Insights、Profiler、自动化测试、远程控制和调试通道。
- **已知能力**：UE 有 `UE::Trace`/TraceLog、UnrealTraceServer、UnrealInsights、Stats/CSV、日志、AutomationTestFramework、Remote Control、Session/Messaging 和 GPU/Chaos 等诊断入口。
- **证据/来源**：[`23_diagnostics_tracing_testing.md`](../ue5.8.3/design/23_diagnostics_tracing_testing.md)、[`30_diagnostics_interfaces.md`](../ue5.8.3/design/30_diagnostics_interfaces.md)、[`32_gap_audit.md`](../ue5.8.3/design/32_gap_audit.md)。TraceServer/Insights 完整 wire/storage、Remote Control 端口/TLS、VisualLogger schema、Windows dump 和工具后端为 `资料不足`。
- **比较 Break**：Break 有 core log/alloc/profiler、RHI 收据和 CTest/sanitizer 证据；`Architecture_Overview.md` 记录 profiler provenance sidecar/Chrome trace。当前没有 UE Insights/Remote Control 等产品级远程调试协议证据，不能由 profiler API 名称推断兼容能力。

## 14. crash upload

- **范围**：崩溃捕获、上下文/转储、报告客户端、服务端接收与上传。
- **已知能力**：UE 诊断资料确认 Crash/CrashReportClient 属于 Launch/诊断体系，并有 Unix 崩溃处理和报告流程入口。
- **证据/来源**：[`23_diagnostics_tracing_testing.md`](../ue5.8.3/design/23_diagnostics_tracing_testing.md) 的崩溃章节、[`30_diagnostics_interfaces.md`](../ue5.8.3/design/30_diagnostics_interfaces.md)、[`18_launch_engine_loop_modules.md`](../ue5.8.3/design/18_launch_engine_loop_modules.md)。完整平台 dump 字段、上传协议、服务端、隐私/重试策略为 `资料不足`。
- **比较 Break**：当前 Break 状态文档和架构概览没有证明正式 crash upload client/server。日志、CTest 失败报告、sanitizer 输出或 profiler sidecar 不等于崩溃上传能力；因此 Break 侧按未交付处理。

## 15. online update

- **范围**：在线补丁、BuildPatch、版本/manifest、下载、安装和回滚。
- **已知能力**：UE 资料能确认 BuildPatch/相关 online update 入口属于工具/插件与资产交付域，但本次 inventory 未确认完整产品服务链。
- **证据/来源**：[`11_networking_replication.md`](../ue5.8.3/design/11_networking_replication.md) 的审计限制、[`20_assets_cook_package_io.md`](../ue5.8.3/design/20_assets_cook_package_io.md)、[`32_gap_audit.md`](../ue5.8.3/design/32_gap_audit.md)。服务端、manifest 协议、签名、差分、安装原子性和回滚均为 `资料不足`，不可从模块名推测。
- **比较 Break**：[`Implementation_Status.md`](../Implementation_Status.md) 明确指出 online update 未实现；当前网络 Session/adapter 只覆盖 bounded transport/session 语义，不是更新系统。

## 16. security/anti-cheat

- **范围**：认证、加密、权限、反作弊、完整性、平台安全和在线服务安全边界。
- **已知能力**：UE 资料可确认网络 PacketHandler/加密组件及若干 online/plugin 接口存在；不能据此确认完整反作弊产品或部署策略。
- **证据/来源**：[`11_networking_replication.md`](../ue5.8.3/design/11_networking_replication.md)、[`27_network_io_threads.md`](../ue5.8.3/design/27_network_io_threads.md)、[`30_diagnostics_interfaces.md`](../ue5.8.3/design/30_diagnostics_interfaces.md)。DTLS 类名已被审计修正为 `FEncryptionComponent`/PacketHandler 方向；反作弊、密钥生命周期、远程证明和服务端安全协议为 `资料不足`。
- **比较 Break**：Break 状态明确：fragment checksum 只是完整性校验而非加密认证，cryptographic authentication、anti-cheat 和正式 security integration 未实现。Session 的 envelope/version/registry 检查不能升级为反作弊或身份认证后端。

## 17. large-world/streaming

- **范围**：World Partition、cell/region、关卡/资产 streaming、HLOD、Data Layer、大世界坐标和运行时加载调度。
- **已知能力**：UE 有 World Partition、streaming levels、Data Layers、Level Instances、HLOD/生成和相关 runtime/editor 管线；其设计目标覆盖大世界分区与按需加载。
- **证据/来源**：[`05_world_partition_streaming.md`](../ue5.8.3/design/05_world_partition_streaming.md)、[`04_engine_framework.md`](../ue5.8.3/design/04_engine_framework.md)、[`32_gap_audit.md`](../ue5.8.3/design/32_gap_audit.md)。WorldPartition/HLOD 内部、生成算法、Landscape/Foliage/InstancedActors 存储、DataLayer replication 和 streaming runtime 实测均有 `资料不足` 限制。
- **比较 Break**：Break 架构概览列出 ECS/renderer/asset，但当前状态没有分布式 Cell service、large-world coordinate 或正式 streaming runtime 的完成证据；ECS AoI 的空间网格是 focused API，不能等同 UE World Partition。

## 与 Break 的比较边界

1. 本文比较的是可核验的模块职责和证据等级，不比较未经统一基准的性能、代码量或产品成熟度。
2. UE 侧以本仓库的 5.8.3 资料为准；缺少源码、运行条件、第三方服务或目标平台证据时保留 `资料不足`。章节覆盖不代表完整实现覆盖。
3. Break 侧以当前 [`Implementation_Status.md`](../Implementation_Status.md) 和 [`Architecture_Overview.md`](../Architecture_Overview.md) 为准，必要时追到 `engine/src/`、`engine/tests/`。当前工作树已有用户改动；本文不据此修改或重述未核验的源码行为。
4. Break 的 focused/test-only API、headless/compiled/native-surface 等状态必须与正式 runtime 分开。尤其网络、ECS replication/AoI、D3D12 和 profiler 的证据都带有文档中明确的边界。
5. 本文件只负责 Unreal inventory；CryENGINE、BW191 的逐项能力、四列矩阵和缺口分组由对应阶段文档负责。

## 来源与限制

- 主要导航：[`docs/ue5.8.3/README.md`](../ue5.8.3/README.md)、[`docs/ue5.8.3/PROGRESS.md`](../ue5.8.3/PROGRESS.md)。
- UE 专题：[`01_core_foundation.md`](../ue5.8.3/design/01_core_foundation.md)、[`02_core_hal_threading.md`](../ue5.8.3/design/02_core_hal_threading.md)、[`03_coreuobject.md`](../ue5.8.3/design/03_coreuobject.md)、[`04_engine_framework.md`](../ue5.8.3/design/04_engine_framework.md)、[`05_world_partition_streaming.md`](../ue5.8.3/design/05_world_partition_streaming.md)、[`06_rhi.md`](../ue5.8.3/design/06_rhi.md)、[`10_slate_umg_input.md`](../ue5.8.3/design/10_slate_umg_input.md)、[`11_networking_replication.md`](../ue5.8.3/design/11_networking_replication.md)、[`12_physics_chaos.md`](../ue5.8.3/design/12_physics_chaos.md)、[`14_audio.md`](../ue5.8.3/design/14_audio.md)、[`18_launch_engine_loop_modules.md`](../ue5.8.3/design/18_launch_engine_loop_modules.md)、[`19_build_system_uht_uat.md`](../ue5.8.3/design/19_build_system_uht_uat.md)、[`20_assets_cook_package_io.md`](../ue5.8.3/design/20_assets_cook_package_io.md)、[`22_editor_core.md`](../ue5.8.3/design/22_editor_core.md)、[`23_diagnostics_tracing_testing.md`](../ue5.8.3/design/23_diagnostics_tracing_testing.md)、[`26_threading_concurrency_overall.md`](../ue5.8.3/design/26_threading_concurrency_overall.md)、[`27_network_io_threads.md`](../ue5.8.3/design/27_network_io_threads.md)、[`28_ui_input_threads.md`](../ue5.8.3/design/28_ui_input_threads.md)、[`29_render_thread_deep.md`](../ue5.8.3/design/29_render_thread_deep.md)、[`30_diagnostics_interfaces.md`](../ue5.8.3/design/30_diagnostics_interfaces.md)、[`31_message_event_mechanisms.md`](../ue5.8.3/design/31_message_event_mechanisms.md)、[`32_gap_audit.md`](../ue5.8.3/design/32_gap_audit.md)。
- Break 事实来源：[`docs/Implementation_Status.md`](../Implementation_Status.md)、[`docs/Architecture_Overview.md`](../Architecture_Overview.md)、`engine/src/`、`engine/tests/`。
- 限制：本文没有重新构建 Unreal、运行其 editor/runtime、抓取第三方服务协议或验证所有平台宏；UE 资料中已列出的审计限制保留为 `资料不足`，不以常识补全。
