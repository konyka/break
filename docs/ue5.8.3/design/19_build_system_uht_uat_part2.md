# 19 构建与工具链(续)——19.6~19.11

## 19.6 关键流程

### 19.6.1 Build.bat → UBT 全流程

```mermaid
flowchart TD
    A["Build.bat 目标 平台 配置 额外参数"]
    B["单实例文件锁 LockFile"]
    C["GetDotnetPath.bat 定位 dotnet"]
    D{"UnrealBuildTool.dll 存在?"}
    E["dotnet build + publish UnrealBuildTool.csproj"]
    F["dotnet UnrealBuildTool.dll 参数"]
    G["UnrealBuildTool.Main"]
    H["GlobalOptions 解析 -Mode 与全局参数"]
    I{"Mode 指定?"}
    J["默认 BuildMode 快速路径"]
    K["GetModes 反射 IToolMode 实现"]
    L["XmlConfig.ReadConfigFiles + ApplyTo"]
    M["FileMetadataPrefetch.QueueEngineDirectory"]
    N["UEBuildPlatform.RegisterPlatforms 反射 UEBuildPlatformFactory"]
    O["GlobalSingleInstanceMutex.Acquire 单实例互斥"]
    P["Mode.ExecuteAsync"]
    A-->B-->C-->D
    D-- 否 -->E-->F
    D-- 是 -->F
    F-->G-->H-->I
    I-- 未指定 -->J
    I-- 指定 -->K
    J-->L
    K-->L
    L-->M-->N-->O-->P
```

BuildMode 内部(P 为入口后的展开):

```mermaid
flowchart TD
    S0["TargetDescriptor.ParseCommandLine"]
    S1{"有 -Rebuild 目标?"}
    S2["CleanMode.Clean"]
    S3["ExecutorFactory.PrecreateExecutor 提前建 UBA"]
    S4{"RemoteMac 处理 Apple 平台?"}
    S5["RemoteMac.Build 远程编译并返回"]
    S6["SourceFileWorkingSet.Create 工作集"]
    S7["CreateMakefiles 分组并行两阶段"]
    S8["按 pass 调 BuildAsync"]
    S9["Deploy bDeployAfterCompile 时"]
    S10["保存缓存 FileHashCache MetadataCache CppDependencyCache"]
    S0-->S1
    S1-- 是 -->S2-->S3
    S1-- 否 -->S3
    S3-->S4
    S4-- 是 -->S5-->S10
    S4-- 否 -->S6-->S7-->S8-->S9-->S10
```

### 19.6.2 Makefile 生命周期(stateDiagram)

```mermaid
stateDiagram-v2
    [*] --> Loading : TargetMakefile.Load
    Loading --> Valid : IsValidForSourceFiles 通过
    Loading --> Rebuild : 文件缺失或源码/配置/环境变更
    Valid --> Rebuild : PreBuildScripts 执行后再校验失败
    Rebuild --> Phase1 : PreBuildSetup + BuildMakefile1
    Phase1 --> CodeGen : RunCodeGen 生成头与 UHT Task
    CodeGen --> Phase2 : WaitCodeGen 条件满足
    Phase2 --> Saving : BuildMakefile2 完整动作图
    Saving --> [*] : makefile.Save 异步落盘
    Valid --> [*] : 直接进入动作执行
```

触发 Rebuild(失效)的判据(TargetMakefile.cs 与 BuildMode.cs:1092-1113):makefile 文件缺失/版本不同、`TargetMakefile.IsValidForSourceFiles` 检查的源文件时间戳与工作集状态、`ConfigValueTracker` 记录的 ini 值变化、`AdditionalArguments` 变化、`ExternalMetadata` 变化、UBT/UHT 程序集指纹(`.uhtpath`)变化。

### 19.6.3 UHT 解析与生成管线(flowchart,步骤序号即 UhtSession.Run 调用序)

```mermaid
flowchart TD
    M["StepReadManifestFile 读 JSON manifest"]
    PM["StepPrepareModules 建 UhtModule 输出目录"]
    PH["StepPrepareHeaders 建 UhtHeaderFile 类型索引"]
    PA["StepParseHeaders 并行解析头文件"]
    IC["StepWriteInputCache 输入缓存写"]
    TT["StepPopulateTypeTable 填 UObject 等内建类"]
    R1["StepResolveInvalidCheck"]
    R2["StepBindSuperAndBases 绑定基类"]
    RC["RecursiveStructCheck 递归结构检查"]
    R3["StepResolveBases"]
    R4["StepResolveProperties 属性类型解析"]
    R5["StepResolveFinal"]
    R6["StepResolveValidate specifier 校验表"]
    CR["StepCollectReferences"]
    LM["StepLinkModules"]
    TS["TopologicalSortHeaderFiles 头拓扑排序"]
    EX["StepExport CodeGen Json Stats"]
    M-->PM-->PH-->PA-->IC-->TT-->R1-->R2-->RC-->R3-->R4-->R5-->R6-->CR-->LM-->TS-->EX
```

解析单元的并发:StepParseHeaders/各 Resolve 步骤经 `ForEachHeader(action, allowGoWide)` 执行,GoWide 时 `Parallel2.ForEach(_headerFiles, …)`(UhtSession.cs:1525-1554);错误经 `Try/TryHeader` 捕获为 UhtMessage,`HasErrors` 后续步骤整体跳过。

### 19.6.4 UAT BuildCookRun 各阶段与拉起的进程

```mermaid
flowchart TD
    U["RunUAT.bat BuildCookRun -project -platform -config"]
    P0["AutomationToolDriver.Program.Main 编译脚本模块"]
    BCR["BuildCookRun.ExecuteBuild"]
    SP["SetupParams 构建 ProjectParams + 平台 SetupParams"]
    B["Project.Build 组 Agenda"]
    UB["UnrealBuild.Build 拉起 dotnet UnrealBuildTool.dll"]
    C["Project.Cook"]
    CK["CommandUtils.RunCommandlet UnrealEditor-Cmd -run=Cook"]
    BYC["可选 BYOCcooker远程 cooker 进程"]
    ST["Project.CopyBuildToStagingDirectory"]
    PK["Project.Package 平台 GetPlatformParams"]
    UP["UnrealPak.exe IasTool 等打包"]
    AR["Project.Archive"]
    DP["Project.Deploy 平台部署"]
    RN["Project.Run 设备运行"]
    GF["Project.GetFile 拉回产物"]
    SUB{"-Submit?"}
    P4["P4.CreateChange + Submit"]
    U-->P0-->BCR-->SP-->B-->UB
    B-->C-->CK
    CK-->BYC
    C-->ST-->PK-->UP-->AR-->DP-->RN-->GF-->SUB
    SUB-- 是 -->P4
```

### 19.6.5 执行器选择与 UBA 执行流

```mermaid
flowchart TD
    E0["ActionGraph.ExecuteActionsAsync"]
    E1{"已有预建 executor?"}
    E2["ExecutorFactory.GetExecutor"]
    E3["遍历 RemoteExecutorPriority XGE SNDBS FASTBuild UBA"]
    E4{"可用且动作数 >= minActionsForRemote?"}
    E5["返回该执行器"]
    E6["GetUBAExecutor 兜底"]
    R1["XGE 生成 xge XML 提交 Incredibuild"]
    R2["SNDBS Scalable Build 服务"]
    R3["FASTBuild 生成 fdb bff"]
    U0["UBAExecutor.ExecuteActionsAsync"]
    U1["初始化 IServer IStorageServer ISessionServer ICacheClient"]
    U2["IScheduler.CreateScheduler(session cache config NumParallelProcesses)"]
    U3["ContentAddressableActionResultStore 结果缓存"]
    U4["scheduler.Start + 逐 action EnqueueProcess"]
    U5{"完成回调 ProcessExecutionType"}
    U6["Cache 命中直接产出"]
    U7["Remote 远程执行 失败按策略 RerunLocal"]
    U8["Local detour 本地执行 可重试"]
    U9["Native 不经 detour 直跑"]
    U10{"scheduler.IsEmpty?"}
    U11["统计与 PrintSummary PostTelemetryEvent"]
    E0-->E1
    E1-- 否 -->E2-->E3-->E4
    E4-- 是 -->E5
    E4-- 否 -->E6
    E1-- 是 -->U0
    E5-->R1
    E5-->R2
    E5-->R3
    E5-->U0
    E6-->U0
    U0-->U1-->U2-->U3-->U4-->U5
    U5-->U6
    U5-->U7
    U5-->U8
    U5-->U9
    U6-->U10
    U7-->U10
    U8-->U10
    U9-->U10
    U10-- 否 -->U4
    U10-- 是 -->U11
```

远程失败回退本地的具体规则(UBAExecutor.cs:941-998):无输出、exit 0xC0000005/0xC0000409/0xC0000602、日志含 ` C1001: `/`clang frontend command failed`/`cannot overwrite the original file`、9000-9999 UBA 错误码、或 `bForcedRetryRemote` → `ProcessFinishedResponse.RerunLocal`;本地失败在 `bAllowRetry && (bForcedRetry || 9000-9999)` 时先 detour 重试(≤3 次),再 `RerunNative`。

### 19.6.6 Live Coding / 热重载路径

```mermaid
flowchart TD
    L0["编辑器 Live Coding 控制台 Ctrl Alt F11"]
    L1["UBT -Mode=Build HotReloadMode=LiveCoding(由编辑器传入 -LiveCoding)"]
    L2["HotReload.Setup 处理既有 patch 状态"]
    L3{"HotReloadMode != Disabled?"}
    L4["HotReload.PatchActionsForTarget 追加 LiveCoding 动作与符号重定向"]
    L5["重评估过期 GatherAllOutdatedActions + Link"]
    L6["UBAExecutor 禁缓存 bForceNoCache"]
    L7["编辑器进程内重载新 DLL(LiveCodingConsole)"]
    L8{"常规构建而会话活跃?"}
    L9["HotReload.CheckForLiveCodingSessionActive 报错阻止"]
    L0-->L1-->L2-->L3
    L3-- 是 -->L4-->L5-->L6-->L7
    L3-- 否 -->L8
    L8-- 是 -->L9
    L8-- 否 -->L5
```

依据:System/HotReload.cs:221/270/612;BuildMode.cs:694-725 的 HotReload 分支与 LiveCoding 动作重评估;UBAExecutor.cs:601-606(HotReloadMode 时 `UBAConfig.bForceNoCache`)。

### 19.6.7 工程文件生成(-Mode=GenerateProjectFiles)

流程(GenerateProjectFilesMode.cs:67 起):解析 `-ProjectFiles -Project=… -Game` 参数 → `UEBuildTarget.Create` 逐目标建 makefile(仅元数据,`bSkipBuild`)→ `ProjectFileGenerator.Current` 聚合模块/目标/插件 → 按 `-VS2022/-VSCode/-Rider/-Xcode/-Makefile/-CMake/-CLion/-KDevelop/-QMake/-CodeLite/-Eddie/-AndroidStudio/-VSWorkspace` 选生成器写盘(PlatformProjectGeneratorCollection 挂平台专属文件,如 AndroidStudioProjectFileGenerator/WindowsProjectGenerator)。Rider 生成 `ToolchainInfo`(ProjectFiles/Rider/ToolchainInfo.cs)供其工具链探测;VS 生成 VCProject(.vcxproj)与解决方案(VisualStudioSolutionBuilder)。

## 19.7 时序图

### 19.7.1 Build.bat → UBT → UHT(进程内)→ UBA 编译链接

```mermaid
sequenceDiagram
    participant U as "用户 Build.bat"
    participant B as "Build.bat 脚本"
    participant M as "UnrealBuildTool.Main"
    participant BM as "BuildMode"
    participant UT as "UEBuildTarget"
    participant UX as "UHTExecution"
    participant HS as "UhtSession EpicGames.UHT"
    participant AG as "ActionGraph"
    participant UB as "UBAExecutor IScheduler"
    participant CC as "本地 远程编译进程"
    U->>B: UnrealEditor Win64 Development
    B->>B: GetDotnetPath 定位 dotnet 检查 UBT.dll
    B->>M: dotnet UnrealBuildTool.dll 参数
    M->>M: 解析全局参数 XmlConfig RegisterPlatforms 取互斥
    M->>BM: Mode.ExecuteAsync
    BM->>BM: TargetDescriptor.ParseCommandLine
    BM->>UT: CreateRulesObject + new UEBuildTarget
    UT->>UT: BuildMakefile1 收集 UHTModuleInfo
    UT->>UX: ExecuteHeaderToolIfNecessary 返回 Task
    note over UX: 与 BuildMakefile2 并行
    UX->>UX: 增量判定 uhtsettings uhtpath 时间戳
    UX->>UX: WriteUHTManifest 写 JSON manifest
    UX->>HS: UnrealHeaderToolMode ExecuteAsync Session.Run
    HS->>HS: ParseHeaders Resolve Export 生成 generated.h gen.cpp
    HS-->>UX: FilesWritten 计数
    UT->>UT: BuildMakefile2 SharedPCH Unity Compile Link 动作
    UT-->>BM: TargetMakefile Save
    BM->>UT: WaitCodeGen 等待并复位缓存
    BM->>AG: Link + GatherAllOutdatedActions
    AG->>AG: ActionHistory 比对命令行与时间戳
    BM->>UB: ExecuteActionsAsync(precreated UBAExecutor)
    UB->>CC: EnqueueProcess detour 本地或远程
    CC-->>UB: 进程完成回调 Remote Local Native Cache
    UB-->>AG: 全部完成 true
    AG-->>BM: 输出 Output binary 路径
    BM-->>M: 0
    M-->>B: 退出码
    B-->>U: 完成
```

### 19.7.2 UAT BuildCookRun:Build/Cook/Stage/Package/Run 跨进程交互

```mermaid
sequenceDiagram
    participant U as "RunUAT.bat"
    participant P as "AutomationTool Program"
    participant BC as "BuildCookRun 脚本"
    participant PR as "Project 命令组"
    participant UBT as "dotnet UnrealBuildTool.dll"
    participant ED as "UnrealEditor-Cmd 进程"
    participant SC as "平台 Stage 部署脚本"
    participant DV as "目标设备"
    U->>P: BuildCookRun -project -platform -config -cook -stage -pak -run
    P->>P: 编译脚本模块 反射 Automation.ProcessAsync
    P->>BC: ExecuteBuild
    BC->>PR: SetupParams 后 DoBuildCookRun
    PR->>UBT: RunUBT 目标列表 Editor Client Server 程序
    UBT-->>PR: 退出码 0
    PR->>ED: RunCommandlet -run=Cook -TargetPlatform=...
    ED-->>PR: Cook 完成 Saved Logs
    PR->>ED: 可选 DDC ResavePackages 等命令行
    PR->>SC: CopyBuildToStagingDirectory StageFiles
    SC->>SC: 按 TargetReceipt 与 BuildProducts 拷贝
    PR->>SC: Package(UnrealPak IoStoreOnDemand 工具)
    PR->>SC: Deploy(平台 Automation)
    SC->>DV: 安装或复制
    PR->>DV: Run(如 -Run 可执行 + 参数)
    DV-->>PR: 运行结果与日志
    PR-->>BC: 完成
    BC-->>P: ExitCode
    P-->>U: 汇总日志与 ExitCode
```

### 19.7.3 BuildGraph 作业经 Horde 分发执行

```mermaid
sequenceDiagram
    participant CL as "CI 客户端 HordeCmd 或 Web"
    participant HS as "HordeServer ASP.NET"
    participant AG as "HordeAgent WorkerService"
    participant JD as "JobDriver DriverApp"
    participant PE as "PerforceExecutor 物化"
    participant BG as "BuildGraph 执行器"
    participant UBA as "UBA 远程编译池"
    CL->>HS: 提交 Job(模板+参数)
    HS->>AG: 调度分片(Lease)
    AG->>JD: SessionFactory 创建会话
    JD->>PE: 物化工作区(Perforce 快照或 CAS)
    PE-->>JD: 就绪工作区
    JD->>BG: 运行 BuildGraph 节点
    BG->>UBA: EnqueueProcess 远程动作
    UBA-->>BG: 动作结果(缓存或远程或本地)
    BG-->>JD: 节点产物/Badge/报告
    JD-->>HS: 上传 Artifacts 与日志
    HS-->>CL: 状态与结果
```

### 19.7.4 UGS:同步与 CIS 编译入口

```mermaid
sequenceDiagram
    participant U as "开发者"
    participant G as "UnrealGameSync Program"
    participant MS as "MetadataServer"
    participant P4 as "Perforce"
    participant UB as "dotnet UnrealBuildTool.dll"
    participant ED as "UnrealEditor"
    U->>G: 选择 CL 与项目
    G->>P4: Sync(预编译二进制或源码)
    G->>MS: 读写用户选项/项目开关
    G->>UB: 需要 CIS 编译时 UBT 生成工程或直接编译
    UB-->>G: 成功产出编辑器二进制
    G->>ED: 启动编辑器(附加 -CI 等参数)
    ED-->>G: 退出回收补丁
```

UGS 主程序为 WinForms(Program.cs,Launcher.cs 承载),可配置为从 Horde/共享缓存取预编译产物(ArtifactDownload.cs),并通过 AutomationServer 与编辑器内 UI 通信;UnrealGameSyncCmd 为命令行版。

## 19.8 线程模型与同步

UBT/UAT/UHT 均为 .NET 进程;此处"主线程"= 执行 Main/ExecuteAsync 的线程,其余为线程池(Parallel2 底层是 ThreadPool 的并行循环,Shared/EpicGames.Build/System/Parallel2.cs)。

| 位置 | 线程 | 同步原语/依据 |
|---|---|---|
| UnrealBuildTool.Main | 主线程 | `SingleInstanceMutex.Acquire/GlobalSingleInstanceMutex.AcquireNowOrThrow`(UnrealBuildTool.cs:442-449);`Log.EnableThreaded()`(:278)把日志写线程化 |
| CreateMakefiles 规则装配 | Parallel2.For 工作线程,helperCount = `bParallelMakefileGeneration ? -1 : 0`(BuildMode.cs:1120) | `lock(sourceFileMetadataCaches)`(:1181)、`lock(appNameTargetGroups)`(:1207);每线程创建 TargetRules,跨线程共享 RulesAssembly |
| makefile 预加载 | `Task.Run(LoadMakefile)`(BuildMode.cs:1163) | `preLoadedMakefiles` 字典 + lock(:1298-1316) |
| makefile 保存 | `Task.Run(makefile.Save)`(:1447-1451) | `ConcurrentDictionary<FileReference,Task> lastSaveMakefileTasks`(:1254);异常路径 Task.WaitAll 保证落盘 |
| UHT 执行 | `Task(runTask)` 在 ThreadPool;与 BuildMakefile2 并行(UEBuildTarget.cs:3032) | `runTask.Start()` + `ContinueWith(…, TaskScheduler.Current)` 写时间戳(UHTExecution.cs:1532-1545);`WaitCodeGen` 在 join 点 Wait(:3049-3069) |
| Binary/模块编译动作生成 | `Parallel2.ForEach(Binaries, …)`(UEBuildTarget.cs:3142-3147) | MakefileBuilder(TargetMakefileBuilder)串行化写入(IActionGraphBuilder) |
| 过期判定 | `Parallel2.ForEach(Actions, …)`(ActionGraph.cs:927-931) | `ConcurrentDictionary<LinkedAction,bool> OutdatedActions`;生产者-消费者闭包传播在 IsActionOutdatedDueToPrerequisites |
| 依赖计数 | 多线程 | `Interlocked.Increment/Exchange`(LinkedAction.IncrementDependentCount,Action.cs:859-868) |
| 执行 | 主线程 await ExecuteActionsAsync;UBA 原生 Scheduler 自有线程 | `CancellationTokenSource _cancellationSource`(UBAExecutor.cs:610/666);`ConcurrentBag<Task> resultStoreTasks`(:914);`lock(_sessionLock)`(:671) |
| 结果缓存写 | 后台 Task | ContentAddressableActionResultStore 经 IStorageProvider 事务流(Storage/IStorageProvider.cs) |
| 日志聚合 | 执行器回调线程 | `lock(Parser)` 的 WriteToolOutput/FlushToolOutput(ActionExecutor.cs:82-93) |
| UHT GoWide | Parallel2.ForEach per header(UhtSession.cs:1541-1546) | `_namespaces` 为 ConcurrentDictionary(:1625);错误计数 `Interlocked.CompareExchange/Increment`(UhtCounter :643-656);Export 输出 `Parallel2.ForEach(saves, RenameSource)`(:522-535) |
| UAT | 脚本主线程顺序执行各阶段 | 子进程经 ProcessUtils 异步 IProcessResult;`ProcessSingleton.RunSingleInstanceAsync` 保证同分支单实例(Program.cs:468);备注 `[STAThread]` 被显式禁止(Main 注释) |
| Horde Agent | 每会话独立执行线程 | ASP.NET/ASP.NET Core 托管;JobDriver 内 Executor 串行消费消息队列 |
| 构建机互斥 | 跨进程 | Build.bat 自身文件锁(Build.bat:18-33 `%tmp%` lock 文件重试)与 UBT GlobalSingleInstanceMutex 双层 |

跨线程数据所有权约定:TargetRules/ModuleRules 对象只在创建它的 makefile 线程上构造与消费;FileItem/DirectoryItem 的缓存信息由 `FileMetadataPrefetch`(System/FileMetadataPrefetch.cs)后台线程预热、`ResetCachedInfo()` 在 UHT/执行器写文件后复位(BuildMode.cs:578-582,846-852);`UnrealBuildTool.InitialEnvironment` 在 Main 早期快照(BuildMode.cs:122-126)。

## 19.9 配置与扩展点

本域无运行时 CVar;配置面由 XML/ini/命令行/环境变量/规则属性/插件六类构成。

### 19.9.1 BuildConfiguration.xml(XmlConfig 体系)

- 位置优先级:引擎/项目/用户目录下的 `UnrealBuildTool/BuildConfiguration.xml`(XmlConfig.ReadConfigFiles 带缓存,Configuration/Xml/XmlConfig.cs;入口 UnrealBuildTool.cs:323-335)。
- 可配置项即 `BuildConfiguration`(Configuration/BuildConfiguration.cs)与各执行器类上标 `[XmlConfigFile]` 的字段(如 XGE.cs:47-71 的 XGE 段)。执行器优先顺序 `RemoteExecutorPriority` 默认 `[XGE, SNDBS, FASTBuild, UBA]`(:47)。
- 命令行可覆盖:`Arguments.ApplyTo(BuildConfiguration)`(BuildMode.cs:153)。

### 19.9.2 UHT ini 与命令行

- `Engine/Programs/UnrealHeaderTool/Config/DefaultEngine.ini` 的 `[UnrealHeaderTool]` 段:TypeRedirects/MetadataRedirects、StructsWithNoPrefix、StructsWithTPrefix、Units、DelegateParameterCountStrings、DefaultGeneratedCodeVersion、NativePointerMemberBehavior(Engine/EnginePlugin/NonEngine 三级)、ObjectPtrMemberBehavior、MissingGeneratedHeaderIncludeBehavior、EnumUnderlyingTypeNotSet、AreRigVMUObjectPropertiesEnabled、ShowDeprecations、DocumentationPolicies、DefaultDocumentationPolicy(Modes/UnrealHeaderToolMode.cs:277-298;UhtConfigImpl)。
- 项目级 `/Script/Engine.ValkyrieMetaData` 段(ProjectSpecificConfigs,:304-322)。
- UHT 命令行(UnrealHeaderToolMode.UhtGlobalOptions):`-WarningsAsErrors -NoGoWide -WriteRef -VerifyRef -FailIfGeneratedCodeChanges -NoOutput -IncludeDebugOutput -NoDefaultExporters -EnableAllCodeGen -EnableInputCache(Read/Write) -ReportEmptyHeaders -<ExporterName>/-no<ExporterName>`(:527-603)。UBT 侧由 BuildConfiguration.bForceHeaderGeneration/bEnableUHTInputCache/bFailIfGeneratedCodeChanges 注入(UHTExecution.cs:1390,1441-1444,2868-2870)。

### 19.9.3 规则与脚本扩展

- **TargetRules/ModuleRules 属性**即第一扩展面(19.5.7/19.5.8 全表);平台子规则(WindowsTargetRules 等)通过 TargetRules 暴露。
- **平台扩展**:Engine/Platforms/<Platform>/Source 下的规则子类(ModuleRules.SubclassRules/PlatformDirectory,ModuleRules.cs:630-641)与 UBT Platform/ 下对应实现。
- **脚本模块**:UAT `*.Automation.csproj`(Program.cs MainProc 编译加载,`-ScriptsForProject=-ScriptDir=-AutomationProject=` 控制范围);项目可放自己的 Automation 脚本目录。
- **BuildGraph**:XML 定义 `<Option>/<Group>/<Node>/<Aggregate>/<Badge>/<Agent>` + 内嵌脚本(表达式由 BgInterpreter 执行);70 种内建 Task(AutomationTool/BuildGraph/Tasks/),Horde 上以 Agent 分组并行。
- **ubtplugin/uhplugin**:`.ubtplugin`(编译入 UBT)与 `.uhplugin`(编译入 UHT)程序集插件,Makefile.UbtPlugins/EnabledUhtPlugins 跟踪(TargetMakefile.cs:275-287),UHT 侧经 UhtTables.CheckForAttributes 扫描 `[UnrealHeaderTool]` 程序集扩充 specifier/导出器表(UhtTables.cs:75 起)。

### 19.9.4 Horde/UBA 配置

- HordeServer/HordeAgent/JobDriver 各自 `appsettings.json`(+Development/Local/Production 变体)与 ServerSettings/AgentSettings/DriverSettings;Horde 作业模板(gocloud schema)在 HordeServer/Configuration。BuildHorde.xml 是 Horde 自举 BuildGraph。
- UBA:UnrealBuildAcceleratorConfig/CacheConfig/HordeConfig(Executors/UnrealBuildAccelerator/*.cs,均 [XmlConfigFile]):bForceNoCache、bDisableRemote、bWriteToDisk、bAllowDetour、缓存服务地址、Horde 协调器等;`GetAppliedConfig(targetDescriptors)` 合并目标 `-EnableUBA…` 参数。环境变量如 `UBT_EXTRA_ARGS`(UnrealBuildTool.cs:154-158)、`UnrealBuildTool_SessionId`、`UnrealBuildTool_TMP`(:392-427)。

### 19.9.5 BatchFiles 环境开关

GetDotnetPath.bat 定位 .NET SDK(Build.bat 依赖);RunUAT.bat/RunUBT.sh 组装 `-ScriptsForProject` 等参数;`-NoCompile/-Compile/-CompileOnly` 控制 UAT 脚本编译;`-BuildMachine -P4 -NoP4 -Submit` 等全局参数(Program.cs:288-315)。

## 19.10 已知限制/未确认项

- **未在源码中确认/未深入**:SNDBS/XGE/FASTBuild 仅读了工厂与常量,未逐行核对其与外部服务的协议实现;Gauntlet 只核实了目录结构与 TestExecutor 存在,未展开断言/设备租用细节;UnrealSwarm/UnrealLightmass 间消息协议、Unsync 的块同步算法、BuildPatchTool 的 chunk 算法未展开(超出本章重点)。
- **UHT 属性类型表**未逐项列出 43 个 `Types/Properties/*.cs` 的语义(篇幅所限),仅给出容器(UhtPropertyTypeTable)与清单位置。
- **ModuleRules/TargetRules 表**为"全部关键属性"而非 100% 逐属性:两文件合计 6100+ 行,含大量平台子规则(WindowsTargetRules、AndroidTargetRules 等位于 TargetRules.cs 与各平台文件),仅 WindowsTargetRules 以入口形式提及;完整枚举以附录 CSharp/TargetRules.md、ModuleRules.md 为准。
- TargetRules 行号区间个别为估算(同一属性组内以首行标注),已尽量逐条核对;若与源码有 1-2 行偏差以源码为准。
- Horde Server 的具体 API 路由/数据库 schema 未逐个列出;UBA 原生层(UbaSessionServer/UbaScheduler)只给出组件面与调用关系,未深入其协议帧格式。
- `Engine/Programs/UnrealHeaderTool` 的 C++ 程序本体在 5.8.3 源码树中不存在(仅 Config),`Source/Programs/` 下亦无 UnrealHeaderTool 目录;UnrealFrontend/UnrealInsights 属于壳程序,其内部命令分发表未展开。
- 附录 `Programs/ShaderCompileWorker.md` 等个别程序在 Programs 附录目录未见对应文件(如 ShaderCompileWorker),已在 X.11 用跨附录说明;若附录后续补齐可直接替换引用。

## 19.11 附录索引(续)

见主文件 `19_build_system_uht_uat.md` 的 19.11 节;补充:

- UBT 测试:`appendix/api/CSharp/UnrealBuildTool.Tests` 相关、`NoModule` 段的 `BuildPatchTool`(CSharp/NoProject__Source__Programs__BuildPatchTool.md)。
- 平台 C# 规则:`appendix/api/CSharp/Android.Automation.md`、`Apple.Automation.md`、`TVOS.Automation.md`、`VisionOS.Automation.md`、`Win.Automation.md`、`SteamDeck.Automation.md`、`Linux.Automation.md`(如存在)、`IOS.Automation.md`。
- Horde 周边:`appendix/api/CSharp/EpicGames.Horde.md`(服务器客户端共库)、`HordeAgent.md`、`Agent.md`、`AgentInterface.md`、`RemoteWorker.md`、`RemoteClient.md`。
- UGS 周边:`appendix/api/CSharp/UnrealGameSync.md`、`UnrealGameSyncCmd.md`、`UnrealGameSyncShared.md`、`UnrealGameSyncAutomation.md`、`UGSCore.md`、`SlateUGS.md`(Programs)、`PostBadgeStatus.md`。
- UAT 脚本全集:`appendix/api/CSharp/AutomationScripts.Automation.md`、`AutomationUtils.Automation.md`、`Gauntlet.Automation.md`、`BuildGraph.Automation.md` 及各 `*.Automation.md`。






