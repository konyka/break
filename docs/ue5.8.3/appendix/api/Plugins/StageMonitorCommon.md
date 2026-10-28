# Plugins / StageMonitorCommon

- module root: `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorCommon`
- headers: 2; symbols: 66
- symbol kinds: class=1, enum=1, enumerator=5, externvar=1, function=5, member=36, namespace=1, prototype=9, struct=7
- PrivateDependencyModuleNames: CoreUObject, Engine, GameplayTags, VPRoles, VPUtilities
- PublicDependencyModuleNames: Core, DeveloperSettings, StageDataCore

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorCommon/Public/StageMonitorUtils.h` (Public)


#### enum `EStageMonitorNodeStatus`  
`enum class EStageMonitorNodeStatus`  
_L12-19_
- reflection: `UENUM()`
- L14 _public enumerator_ `Unknown`
- L15 _public enumerator_ `LoadingMap`
- L16 _public enumerator_ `Ready`
- L17 _public enumerator_ `HotReload`
- L18 _public enumerator_ `AssetCompiling`

#### struct `FFramePerformanceProviderMessage`  
`struct FFramePerformanceProviderMessage : public FStageProviderPeriodicMessage`  
_L27-101_
- reflection: `USTRUCT()`
- inherits: `FStageProviderPeriodicMessage`
- desc: Message containing information about frame timings. Sent at regular intervals
- L33 _public prototype_ `FFramePerformanceProviderMessage() = default;`
- L35 _public function_ `FFramePerformanceProviderMessage(EStageMonitorNodeStatus InStatus, float GameThreadTime, float GameThreadWaitTime, float RenderThreadTime, float RenderThreadWaitTime, float GPUTime, float IdleTime, uint64 CPUMem, uint64 GPUMem, int32 InAssetsToCompile) : Status(InStatus) , GameThreadMS(GameThreadTime) , GameThreadWaitMS(GameThreadWaitTime) , RenderThreadMS(RenderThreadTime) , RenderThreadWaitMS(RenderThreadWaitTime) , GPU_MS(GPUTime) , IdleTimeMS(IdleTime) , CPU_MEM(CPUMem) , GPU_MEM(GPUMem) , CompilationTasksRemaining(InAssetsToCompile)`
- L56 _public member_ `EStageMonitorNodeStatus Status = EStageMonitorNodeStatus::Unknown;` — `UPROPERTY(VisibleAnywhere, Category = "Performance")` — Average FrameRate read from GAverageFPS
- L60 _public member_ `FString AssetInStatus;` — `UPROPERTY(VisibleAnywhere, Category = "Performance")` — Full path name of the asset involved in the status. This will be empty for Ready, Shader Compiles, and Unknown states
- L64 _public member_ `float AverageFPS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Performance")` — Average FrameRate read from GAverageFPS
- L68 _public member_ `float GameThreadMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Performance", meta = (Unit = "ms"))` — Current GameThread time read from GGameThreadTime in milliseconds
- L72 _public member_ `float GameThreadWaitMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Performance", meta = (Unit = "ms"))` — Current GameThread wait time read from GGameThreadWaitTime in milliseconds
- L76 _public member_ `float RenderThreadMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Performance", meta = (Unit = "ms"))` — Current RenderThread time read from GRenderThreadTime in milliseconds
- L80 _public member_ `float RenderThreadWaitMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Performance", meta = (Unit = "ms"))` — Current RenderThread wait time read from GRenderThreadWaitTime in milliseconds
- L84 _public member_ `float GPU_MS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Performance", meta = (Unit = "ms"))` — Current GPU time read from RHIGetGPUFrameCycles() in milliseconds
- L88 _public member_ `float IdleTimeMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Performance", meta = (Unit = "ms"))` — Idle time (slept) in milliseconds during last frame
- L92 _public member_ `uint64 CPU_MEM = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Performance")` — Current CPU Memory Usage (Physical) in bytes
- L96 _public member_ `uint64 GPU_MEM = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Performance")` — Current GPU Memory Usage (Physical) in bytes
- L100 _public member_ `int32 CompilationTasksRemaining = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Performance")` — Number of asynchronous compilation tasks currently in progress.

#### Free symbols / members of external scopes

- L50 _externvar_ `extern float GAverageFPS;` (scope `FFramePerformanceProviderMessage::FFramePerformanceProviderMessage`)
- L104 _namespace_ `namespace StageMonitorUtils`
- L106 _prototype_ `FStageInstanceDescriptor GetInstanceDescriptor();` (scope `StageMonitorUtils`)

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorCommon/Public/StageMonitoringSettings.h` (Public)


#### struct `FStageMessageTypeWrapper`  
`struct FStageMessageTypeWrapper`  
_L18-40_
- reflection: `USTRUCT()`
- desc: Wrapper structure holding a message type static struct. Used with a customization to generate a filtered list
- L23 _public prototype_ `FStageMessageTypeWrapper() = default;`
- L24 _public function_ `FStageMessageTypeWrapper(FName Type) : MessageType(Type)`
- L28 _public function_ `bool operator==(const FStageMessageTypeWrapper& Other) const`
- L29 _public function_ `bool operator==(const FName Other) const`
- L34 _public member_ `FName MessageType;` — `UPROPERTY(config, EditAnywhere, Category = "Stage Message")` — Name of StaticStruct message type

#### struct `FStageDataExportSettings`  
`struct FStageDataExportSettings`  
_L46-62_
- reflection: `USTRUCT()`
- desc: Settings associated to file exporter
- L57 _public member_ `bool bKeepOnlyLastPeriodMessage = true;` — `UPROPERTY(config, EditAnywhere, Category = "Export")` — Save only the last instance of periodic message types True by default to reduce file size
- L61 _public member_ `TArray<FStageMessageTypeWrapper> ExcludedMessageTypes;` — `UPROPERTY(config, EditAnywhere, Category = "Export")` — Message types to exclude from session when exporting

#### struct `FStageFramePerformanceSettings`  
`struct FStageFramePerformanceSettings`  
_L68-77_
- reflection: `USTRUCT()`
- desc: Settings related to FramePerformance messages
- L76 _public member_ `float UpdateInterval = 0.2f;` — `UPROPERTY(config, EditAnywhere, Category = "Frame Performance", meta = (Unit = "s"))` — Target FPS we're aiming for.

#### struct `FStageHitchDetectionSettings`  
`struct FStageHitchDetectionSettings`  
_L83-103_
- reflection: `USTRUCT()`
- desc: Settings related to HitchDetection messages
- L98 _public member_ `bool bEnableHitchDetection = false;` — `UPROPERTY(config, EditAnywhere, Category = "Hitch Detection")` — Whether or not hitch detection should be enabled @note: This uses stat data. To avoid having on-screen message GAreScreenMessagesEnabled = false or -ExecCmds="DISABLEALLSCREENMESSAGES" on command line will turn them off. For more accurate hitch detection, use genlock which will have better missed frames information
- L102 _public member_ `FFrameRate MinimumFrameRate = FFrameRate(24, 1);` — `UPROPERTY(config, EditAnywhere, Category = "Hitch Detection")` — Target FPS we're aiming for.

#### struct `FStageDataProviderSettings`  
`struct FStageDataProviderSettings`  
_L109-133_
- reflection: `USTRUCT()`
- desc: Settings associated to DataProviders
- L117 _public member_ `bool bUseRoleFiltering = false;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (InlineEditConditionToggle))` — If true, DataProvider will only start if machine has a role contained in SupportedRoles
- L121 _public member_ `FGameplayTagContainer SupportedRoles;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (EditCondition = "bUseRoleFiltering"))` — If checked, VP Role of this instance must be part of these roles to have the monitor operational
- L124 _public member_ `TMap<FStageMessageTypeWrapper, FGameplayTagContainer> MessageTypeRoleExclusion;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")`
- L128 _public member_ `FStageFramePerformanceSettings FramePerformanceSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — Settings about Frame Performance messaging
- L132 _public member_ `FStageHitchDetectionSettings HitchDetectionSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — Settings about Hitch detection

#### struct `FStageMonitorSettings`  
`struct FStageMonitorSettings`  
_L139-178_
- reflection: `USTRUCT()`
- desc: Settings for StageMonitor
- L144 _public prototype_ `FStageMonitorSettings();`
- L147 _public prototype_ `bool ShouldAutoStartOnLaunch() const;` — Returns true if Monitor should start on launch. Can be overriden through commandline
- L155 _public member_ `bool bUseRoleFiltering = false;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (InlineEditConditionToggle))` — If true, Monitor will only autostart if machine has a role contained in SupportedRoles Once in editor, you can always start a monitor manually independently of the roles.
- L159 _public member_ `FGameplayTagContainer SupportedRoles;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (EditCondition = "bUseRoleFiltering"))` — If checked, VP Role of this instance must be part of these roles to have the monitor operational
- L163 _public member_ `float DiscoveryMessageInterval = 2.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (Units = "s"))` — Interval between each discovery signal sent by Monitors
- L171 _protected member_ `bool bAutoStart = false;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — Whether we should start monitoring on launch. @note It may be overriden via the command line, "-StageMonitorAutoStart=1 and via command line in editor"
- L177 _protected member_ `TOptional<bool> bCommandLineAutoStart;` — Override AutoStart project settings through command line. ie. "-StageMonitorAutoStart=1"

#### class `UStageMonitoringSettings`  
`class UStageMonitoringSettings : public UDeveloperSettings`  
_L185-247_
- reflection: `UCLASS(config=Game)`
- inherits: `UDeveloperSettings`
- desc: Settings for the StageMonitoring plugin modules. Data Provider, Monitor and shared settings are contained here to centralize access through project settings
- L190 _public prototype_ `UStageMonitoringSettings();`
- L193 _public prototype_ `virtual FName GetCategoryName() const;`
- L195 _public prototype_ `virtual FText GetSectionText() const override;`
- L201 _public prototype_ `int32 GetStageSessionId() const;` — Returns current SessionId either based on settings or overriden by commandline
- L207 _public member_ `bool bUseSessionId = true;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — If true, Stage monitor will only listen to Stage Providers with same sessionId
- L215 _protected member_ `int32 StageSessionId = INDEX_NONE;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — The projects Stage SessionId to differentiate data sent over network. @note It may be overriden via the command line, "-StageSessionId=1"
- L221 _public member_ `float TimeoutInterval = 10.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta=(Unit="s"))` — Interval threshold between message reception before dropping out a provider or a monitor
- L225 _public member_ `FStageMonitorSettings MonitorSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Monitor Settings")` — Settings for monitors
- L229 _public member_ `FStageDataProviderSettings ProviderSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Provider Settings")` — Settings for Data Providers
- L233 _public member_ `FStageDataExportSettings ExportSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Export Settings")` — Settings for Data Providers
- L240 _public member_ `TOptional<int32> CommandLineSessionId;` — The current SessionId in a virtual production context read from the command line. ie. "-StageSessionId=1"
- L246 _public member_ `FName CommandLineFriendlyName;` — A friendly name for that instance given through command line (-StageFriendlyName=) to identify it when monitoring. If none, by default it will be filled with MachineName:ProcessId

#### Free symbols / members of external scopes

- L36 _function_ `friend uint32 GetTypeHash(const FStageMessageTypeWrapper& TypeWrapper)`
