# UE 5.8.3 设计文档项目进度记录

更新时间:2026-10-19。本文件是唯一进度事实来源,恢复工作时先读本文件。

## 项目目标

对 `/home/timeshift/opensource/game_engine/unreal/UnrealEngine-5.8.3-release` 做全量架构分析,
产出《概要设计》《详细设计》文档:架构、类图、线程模型、时序图、流程图、所有接口功能与描述、
数据字典、原型签名,要求不遗漏。输出根:`/home/timeshift/opensource/break/docs/ue5.8.3/`。

关键约定(写章节必须遵守):`tools/CHAPTER_SPEC.md`(硬性原则、X.1~X.11 结构、Mermaid 语法约束、质量自检)。
源码根 $UE=/home/timeshift/opensource/game_engine/unreal/UnrealEngine-5.8.3-release,$E=$UE/Engine。
执行方式约束(用户要求):**额度有限,必须顺序执行(一次只跑一个 agent/一项任务),不并行**。

## 产物结构

- `appendix/api/<Tier>/<Module>[.partNN].md` — 全量符号附录(Tier=Runtime/Developer/Editor/Programs/Plugins/Platforms/CSharp/NoModule)
- `appendix/index/<Tier>__<Module>.tsv.gz` — 符号索引(列:路径\t行号\tkind\tscope\tname\tvisibility)
- `appendix/modules.json` — 模块总表(tier/name/root/headers/symbols/stat/deps/files)
- `appendix/dictionary/` — CVar/模块/插件/Target/Project/Config/UCLASS(config=) 数据字典(已生成 2026-10-19)
- `appendix/api/Shaders/` + `appendix/index/shaders.tsv.gz` — Shader(usf/ush)全量附录
- `appendix/COVERAGE.md` + `coverage.json` — 覆盖率校验报告(已生成)
- `design/NN_*.md` — 详细设计章节(01~32,共 41 个文件，含分篇续稿)
- `00_概要设计.md` — 概要设计主文档(已生成，285 行)
- `README.md` — 详细设计索引与跨章节总图(已生成，178 行)

## 已完成

1. **C++ 头文件全量抽取**:`tools/extract_api.py`(universal-ctags + 自研括号配对/反射宏/文档注释解析)。
   覆盖 Source+Plugins+Platforms 全部 .h/.hpp/.inl(排除 ThirdParty/Tests/Intermediate/Binaries):
   46255 头文件、1448920 符号、2766 模块(含小写 .build.cs 修复)。已知缺口:19 组 SDK/第三方
   无模块头文件归入 NoModule(合理);测试头 460 个按设计排除;已知抽取器缺陷见 §"抽取器已知问题"。
2. **C# 抽取**:`tools/extract_cs.py`,产出 `appendix/api/CSharp/*.md`、`appendix/csharp_files.json`、
   `csharp_summary.json`。经 coverage_check 校验:5719/5719 个文件、类型抽样 1000/1000(2026-10-19)。
3. **详细设计章节 24/25 篇完成**(约 28,000 行;各章含 X.1~X.11 结构与多张 Mermaid 图;
   各章"已知缺口"在其 X.10 小节内):
   - 01_core_foundation.md(1066 行)
   - 02_core_hal_threading.md(1002)
   - 03_coreuobject.md(947)
   - 04_engine_framework.md(1085)
   - 05_world_partition_streaming.md(1062)
   - 06_rhi.md(1133)
   - 07_rendercore_rdg_renderthread.md + _part2(844+458)
   - 08_renderer_deferred_nanite_lumen.md(1051)
   - 09_shader_material_ddc.md(903)
   - 10_slate_umg_input.md(977)
   - 11_networking_replication.md(1151)
   - 12_physics_chaos.md + _part2(935+182)
   - 13_animation.md(1113)
   - 14_audio.md(1006)
   - 15_ai_gameplay_mass.md + _part2(961+364)
   - 16_fx_niagara_geometry_pcg.md(1085)
   - 17_sequencer_media_xr_vp.md(953)
   - 18_launch_engine_loop_modules.md(1233)
   - 19_build_system_uht_uat.md + _part2(907+415)
   - 20_assets_cook_package_io.md(1330)
   - 21_blueprint_kismet_script.md(1246)
   - 22_editor_core.md(997)
   - 23_diagnostics_tracing_testing.md(1019)
   - 25_plugins_catalog_experimental_editor.md + _part2 + _part3(1187+366+1049)
   注:行数以 wc -l 为准,写入时点为 2026-10-19。

## 待办(按此顺序恢复执行,一次一项)

1. ~~补写第 24 章~~ **已完成 2026-10-19**(agent-51):`design/24_plugins_catalog_runtime.md`(891 行)+ _part2(185)
   + _part3(183)+ _part4(1090,774 模块依赖)。覆盖 348 个插件;348 + 第 25 章 547 = 895,差异 0。
   范围调整:任务书目录清单与磁盘不符,Microsoft 实际是 Runtime/Microsoft;另有 12 个一级目录不在任务书也不归第 25 章
   (ChaosCloth 系 6 个、ChaosInsights、ChaosOutfitAsset、ChaosVD、AutomationControllerRpc、IoStoreInsights、
   MassInsights),已并入第 24 章。缺口:核心类是脚本挑的,有 12 个为空;18 个插件 Description 为空;
   35 个模块不在附录里;本地没有 Content/.uasset,内容挂载无法验证;发现 3 处 .uplugin 字段名拼错,
   Projects 不读取这些字段;交叉引用由脚本自动判定。详见该章 24.10。
2. ~~补齐补充抽取器~~ **已完成 2026-10-19**(agent-52):4 个脚本均已实跑,产物如下:
   - `tools/extract_shaders.py` → `appendix/api/Shaders/*.md`(128 个目录文件 + `_REPORT.md`,6.2 MB)、
     `appendix/index/shaders.tsv.gz`(0.6 MB,55,388 条)、`appendix/shaders_summary.json`。覆盖 1693 个文件
     (858 usf + 790 ush + Engine/Shaders 下 45 个共享 .h);入口点 1920 个,已与 C++ 侧 2009 处 IMPLEMENT_* 绑定关联,
     虚拟路径未解析 0 处;硬失败 0 个。
   - `tools/extract_cvars.py` → `appendix/dictionary/cvars.md`(4.4 MB)、`cvars.tsv`(7.6 MB,12,869 处注册,
     12,662 个不同名称)、`cvars_ini.tsv`(1575 行 ini 覆盖)、`cvars_report.json`;另有 278 个 UPROPERTY ConsoleVariable 绑定。
   - `tools/gen_catalog.py` → `appendix/dictionary/{modules,plugins,targets,projects,config,uclass_config}.{md,tsv}`
     及 `plugin_modules.tsv`、`plugin_deps.tsv`、`config_keys.tsv`、`catalog_report.json`(dictionary/ 合计约 20 MB)。
     数量:Build.cs 2747、.uplugin 922(其中 Engine 902)、Target.cs 160(163 个类)、uproject 49、
     Engine ini 348(14,974 个键)、UCLASS(config=) 1330 个。
   - `tools/coverage_check.py` → `appendix/COVERAGE.md` + `coverage.json`。统计全部来自独立的 find/grep 与自写扫描器,
     与各抽取器不共用代码。
   关键命中率:C++ 头文件 99.96%;有声明的头文件被索引 99.95%;反射宏 99.56%;类型抽样 99.85%;
   函数抽样 98.93%(按 Markdown 文本计 99.70%);C# 文件与类型抽样均 100%;Shader 文件 100%、各类探针 ≥99.67%;
   CVar 字面量名称 100%;.uplugin、Build.cs、Target.cs、uproject、ini、UCLASS(config=) 文件级均 100%。
   缺口(详见 COVERAGE.md 的 "Known gaps"):函数抽样低于 99% 全部来自 extract_api.py 的 ctags 缺陷
   (无分号宏行吞掉下一条声明、UPARAM 被记作函数名、`TEnumAsByte<enum E>` 成员丢失、UE_EXPERIMENTAL 前缀、
   PLUGIN_NAME 模板头文件重名覆盖),按规定未修改;运行期拼接的 CVar 名称 184 个保留原式;
   FAutoConsoleVariableRef 有 381 处默认值无法解析(绑定到成员或其他编译单元);37 条 Shader 记录保留原文;
   43 个 .uplugin 含无人读取的字段(EditorOnly/NoRedist/IsExperimental 等)。
   ~~**下一步从待办 2b 开始(第 26 章 26_threading_concurrency_overall.md)。**~~
   原任务书(留档):
   - `tools/extract_shaders.py` → `appendix/api/Shaders/<目录>.md` + `appendix/index/shaders.tsv.gz`
     (E/Shaders 与 E/Plugins/**/Shaders 全部 .usf/.ush 约 1648 个:include/宏/结构/cbuffer/函数/入口点/行号)
   - `tools/extract_cvars.py` → `appendix/dictionary/cvars.md` + cvars.tsv
     (TAutoConsoleVariable/FAutoConsoleVariableRef/FAutoConsoleCommand*/RegisterConsoleVariable/Sink/TaskPriority + ini [ConsoleVariables];括号配对,失败保留原文)
   - `tools/gen_catalog.py` → `appendix/dictionary/{modules,plugins,targets,projects,config,uclass_config}.{md,tsv}`
     (模块 Type/依赖/第三方依赖/所属插件;895 个 .uplugin 全字段;Target.cs;uproject;Config ini;config= 的 UCLASS)
   - `tools/coverage_check.py` → `appendix/COVERAGE.md`:独立 find/grep 校验头文件级、反射宏级、
     类型抽样 2000、函数抽样 3000、C#/Shader/CVar 文件级;<99% 命中要查明原因(修复新脚本,不改 extract_api.py)
2b. **新增横切专题章节(用户 2026-10-19 追加需求,顺序执行,每章一个 agent)**——跨子系统视角,必须基于源码,
    引用已有章节但补其缺失细节:
    - 26_threading_concurrency_overall.md:全引擎线程总表(每条线程:名称/创建点 文件:行/优先级/亲和性/生命周期/
      主循环函数/消费的队列);线程间消息传递机制全表(TaskGraph 任务、ENQUEUE_RENDER_COMMAND、RHI 命令列表、
      FAudioThread::RunCommandOnAudioThread、Chaos Marshaling、AsyncTask(ENamedThreads)、TQueue/TMpscQueue/
      TLockFree*、FEvent/FTaskEvent、委托跨线程、FTSTicker、GameThread 任务 pump 点);互斥模型(各锁类型/
      作用域/读写锁/自旋锁/原子/内存序/无锁结构/FScopeLock 使用约定/死锁规避/线程断言宏 check(IsInGameThread())
      全表);同步点与 fence 总表(FlushRenderingCommands, FFrameEndSync, FRenderCommandFence, GPU fence,
      AudioFence, Physics 同步);每帧多线程并行时序总图。
    - 27_network_io_threads.md:网络收发线程全链路:Socket 层(ISocketSubsystem/BSD socket、阻塞/非阻塞、
      FSocket::RecvFrom)、IpNetDriver 接收线程(FReceiveThreadRunnable / net.IpNetDriverUseReceiveThread)、
      PacketHandler 链、GameThread TickDispatch→收包→Bunch 组装→Channel 分发、TickFlush→发送;HTTP 线程
      (FHttpThread/Curl multi)、WebSocket 线程、UdpMessaging 收发线程(FUdpMessageProcessor)、TcpMessaging、
      Iris 数据流;数据报格式/位流/可靠性/ack/拥塞与带宽(NetSpeed)接口细节;文件 IO 线程(IoDispatcher、
      AsyncFileHandle、PlatformFile 栈)作为 IO 部分。
    - 28_ui_input_threads.md:UI 线程与输入线程:OS 消息泵所在线程、GameThread 上 Slate Tick/Paint、
      Slate 加载屏线程(FSlateLoadingSynchronizationMechanism/MoviePlayer 线程)、SlateRHIRenderer 渲染线程交接、
      输入采集线程(各平台:Windows RawInput/XInput、GameInput、Linux SDL、Android/IOS 输入事件队列与线程转交)、
      输入延迟链路与 GInputLatency、IME/文本输入、触摸/手柄/力反馈接口全表。
    - 29_render_thread_deep.md:渲染线程/RHI 线程/并行翻译/GPU 提交与 Present 的线程交互细节补充(若 07/06 已足,
      做差异补充:并行渲染任务、RHI Submission/Interrupt 线程、Vulkan/D3D12 后端线程、GPU 时间线/fence、
      PSO 编译线程、ShaderCompile 异步线程、Streaming 线程)。
    - 30_diagnostics_interfaces.md:诊断工具接口方式与架构图:Trace(通道/事件/传输/TCP 与文件)、Insights、
      Stats/STAT 命令、CSV Profiler、LLM、MemReport/obj list 等控制台命令、日志、VisualLogger、
      GameplayDebugger、RewindDebugger、ChaosVD、RenderDoc/PIX/Nsight 插件接口、GPU Profiler(RHI breadcrumbs/
      DrawEvent)、崩溃报告、Remote Control(WebSocket/HTTP)、Session Frontend/Messaging、AutomationController,
      每种:接入 API、协议/端口、线程、数据格式、架构图。
    - 31_message_event_mechanisms.md:消息/事件机制总表:委托(单播/多播/动态/TS)、FCoreDelegates/FWorldDelegates/
      FEditorDelegates 全表、UObject 事件、Message Bus(IMessageBus/FMessageEndpoint)、FieldNotification、
      GameplayMessageSubsystem/AsyncMessageSystem、OSS 回调线程、控制台命令系统、Exec 链。
    - ~~32_gap_audit.md~~ **已完成 2026-10-19**:逐章审计 01~31（含横切章）X.10/X.11、源码证据、附录路径、结构/图/TODO、全局风险与补遗；40 文件/32,993 行/425 图/286 条限制，附录 5,177 文件/1,448,920 C++ 符号，C# 5,719 文件/89,219 符号，Shader 1,693 文件/55,388 记录，缺口总数 55（原条目口径 286）。输出 `design/32_gap_audit.md`。
3. ~~概要设计主文档~~ **已完成 2026-10-19**:`00_概要设计.md`,285 行。包含总体分层、关键质量属性、
   启动/帧/网络/资产/诊断流程、线程与同步总表、接口/数据字典索引、01~32 映射、风险与验收标准。
4. ~~详细设计索引~~ **已完成 2026-10-19**:`README.md`,178 行。包含 01~32 导航、附录导航、跨章关系、
   全引擎线程模型总图、启动总时序、运行时一帧总流程。
5. **终检已完成 2026-10-19**:41 个 design 文件/33378 行，覆盖章节 01~32，Mermaid 436 个代码块，
   Markdown 围栏成对；C++ 附录 46255 头/1448920 符号/2388 模块，C#、Shader、CVar、目录字典与
   COVERAGE.md 均存在。结构历史上有两种编号风格:主章节为 `1.1~1.11`，横切专题为 `X.1~X.11`，
   分篇续稿只承接主文件，不重复章节结构。未宣称 Mermaid 由 mmdc 编译通过(环境无 mmdc/graphviz)，
   已做代码围栏、首行类型、路径存在性和占位词扫描。仍有 55 个可操作缺口/286 条原始未确认项，详见 32 章。

## 第 24 章任务书(原样使用)

标题=插件体系与运行时插件目录(第 1 部分)。范围:插件机制(.uplugin 字段全表、FPluginManager 发现/启用、
Content/Config/Shaders 挂载、模块 Type/LoadingPhase、插件依赖、PlatformAllowList、Experimental/Beta 标识,
以 Runtime/Projects 源码与 .uplugin 为准);逐一整理 Plugins 下这些一级目录的全部插件,每个插件一行
(名称/FriendlyName/类别/模块列表及 Type+LoadingPhase/核心类/一句话职责/关键依赖;不得遗漏任何一个 .uplugin;
已深入章节的插件一行+交叉引用):Plugins/2D, AI, AudioGameplay, AudioGameplayVolume, AudioInsights,
AudioInsightsRuntime, AudioModulationInsights, BaseMaterial, BlueprintFileUtils, Bridge, Cameras, Chooser,
CmdLinkServer, Compositing, Compression, Dataflow, DataflowVolumetricPlugin, DerivedDataBuildController,
DiscoveryBeaconReceiver, EnhancedInput, Fab, FastBuildController, GameInputWindows, Importers, Interchange,
JsonBlueprintUtilities, LightWeightInstancesEditor, MemoryUsageQueries, MeshPainting, Messaging, MetaHuman,
Microsoft, MovieScene, Mutable, NetcodeUnitTest, NNE, Online, PCG, PCGInterops, Performance, Portal, Protocols,
RenderGraphInsights, RenderTraceInsights, RPCBase, Runtime(全部子目录约 130 个), ScriptPlugin, Slate,
SubtitlesAndClosedCaptions, Tests, TextureGraph, TraceUtilities, UbaController, VirtualProduction, Web,
WorldMetrics, WorldStreamingInsights, XGEController;输出含插件依赖层次图(flowchart ≤40 节点)、
分类统计表、按字母序全量插件表。信息必须取自 .uplugin 与源码。
注意:第 25 章(Experimental/Editor/Developer/Animation/FX/Media/Online/Enterprise/MetaHuman/Mutable/NNE/Importers)
已完成,交叉引用时用"见第 25 章";25 章报告过 Experimental 287、Editor 52、Developer 48、Animation 38、
FX 11、Media 49、Online 33、Enterprise 12、MetaHuman 9、Mutable 1、NNE 2、Importers 5 个 .uplugin,
全引擎共 895 个,可据此核对第 24 章的数量(895 − 第25章各目录之和 ≈ 第24章应覆盖数)。
章节通用要求:先读 tools/CHAPTER_SPEC.md;结构 X.1~X.11;完成后只报告路径/行数/覆盖/缺口。

## 抽取器已知问题(恢复时参考)

- extract_api.py:枚举成员 doc 抓取用"上一行注释或行尾注释",行尾注释可能漏;#define 展开的原型
  (如 IMPLEMENT_GLOBAL_SHADER 包装的类)不展开;NoModule 19 组为 SDK/第三方,合理。
- extract_api.py 新发现的缺陷(agent-52 用 coverage_check 查实,只报告,未修改):① 不带分号的宏行
  (SLATE_END_ARGS()/RIGVM_METHOD()/DEPRECATED_*_RPC(...) 等)会吞掉下一条声明,索引里记成宏名,共 18,074 行;
  ② 参数中含 UPARAM(...) 的函数被记成 `UPARAM`(857 行),UFUNCTION 也挂在这一行上;③ `TEnumAsByte<enum E>` 成员丢失;
  ④ UE_EXPERIMENTAL(...)/`= T{...}` 初始化之后的成员偶尔丢失;⑤ 两个插件模板的模块都叫 PLUGIN_NAME,
  同名索引互相覆盖,导致 20 个头文件缺失;⑥ `#if 0` 块被当作有效代码。
- 第 8/24/25 章引用的 appendix/dictionary/cvars.md 现已生成,无需回改章节。

## 恢复操作提示

- 章节撰写 agent 提示词模板与 01~25 章任务书全文见本文件与 `tools/CHAPTER_SPEC.md`;
  第 24 章失败 agent 的 id=agent-49(若会话已失效则直接用上方任务书新开 agent,不要依赖 resume)。
- 一切大任务用后台+日志;一次只跑一个 agent;每完成一项,更新本文件的"已完成/待办"。
