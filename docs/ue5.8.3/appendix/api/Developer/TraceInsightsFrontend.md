# Developer / TraceInsightsFrontend

- module root: `Source/Developer/TraceInsightsFrontend`
- headers: 16; symbols: 744
- symbol kinds: class=25, delegate=2, enum=7, enumerator=27, function=143, macro=5, member=231, namespace=38, prototype=257, struct=6, typedef=3
- PrivateDependencyModuleNames: AutomationController, AutomationWindow, AutomationWorker, Engine, SessionServices
- PublicDependencyModuleNames: AppFramework, ApplicationCore, AutomationDriver, Core, CoreUObject, DesktopPlatform, InputCore, Slate, SlateCore, Sockets, TraceAnalysis, TraceInsightsCore, TraceServices, WorkspaceMenuStructure

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/Common/InsightsAutomationController.h` (Private)


#### class `UE::Insights::FInsightsAutomationController`  
`class FInsightsAutomationController : public TSharedFromThis<FInsightsAutomationController>`  
_L18-52_
- inherits: `TSharedFromThis<FInsightsAutomationController>`
- L28 _public prototype_ `virtual ~FInsightsAutomationController();`
- L30 _public prototype_ `virtual void Initialize();`
- L32 _public prototype_ `bool Tick(float DeltaTime);`
- L34 _public function_ `void SetAutoQuit(bool InAutoQuit)`
- L35 _public function_ `bool GetAutoQuit() const`
- L37 _public prototype_ `void RunTests(const FString& InCmd);`
- L41 _private member_ `FTickerDelegate OnTick;` — The delegate to be invoked when this manager ticks.
- L44 _private member_ `FTSTicker::FDelegateHandle OnTickHandle;` — Handle to the registered OnTick.
- L46 _private member_ `FString CommandToExecute;`
- L48 _private member_ `bool bAutoQuit = false;`
- L49 _private member_ `ETestsState RunningTestsState = ETestsState::NotStarted;`
- L51 _private member_ `static const TCHAR* AutoQuitMsgOnComplete;`

#### enum `UE::Insights::FInsightsAutomationController::ETestsState`  
`enum class ETestsState`  
_L20-25_
- L22 _public enumerator_ `NotStarted`
- L23 _public enumerator_ `Running`
- L24 _public enumerator_ `Finished`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRACEINSIGHTSFRONTEND_API`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(InsightsAutomationController, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(InsightsAutomationController, Log, All);`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/InsightsFrontendSettings.h` (Private)


#### class `UE::Insights::FInsightsFrontendSettings`  
`class FInsightsFrontendSettings`  
_L14-126_
- desc: Contains all settings for the Unreal Insights, accessible through the main manager.
- L17 _public function_ `FInsightsFrontendSettings(bool bInIsDefault = false) : bIsEditing(false) , bIsDefault(bInIsDefault) , bAutoConnect(true) , bAutoStartAnalysis(false)`
- L29 _public prototype_ `~FInsightsFrontendSettings() = default;`
- L31 _public function_ `void LoadFromConfig()`
- L44 _public function_ `void SaveToConfig()`
- L54 _public function_ `void EnterEditMode()`
- L59 _public function_ `void ExitEditMode()`
- L64 _public function_ `const bool IsEditing() const`
- L69 _public function_ `const FInsightsFrontendSettings& GetDefaults() const`
- L74 _public function_ `void ResetToDefaults()`
- L81 _public function_ `bool IsAutoConnectEnabled() const`
- L82 _public function_ `void SetAutoConnect(bool bOnOff)`
- L83 _public function_ `void SetAndSaveAutoConnect(bool bOnOff)`
- L85 _public function_ `bool IsAutoStartAnalysisEnabled() const`
- L86 _public function_ `void SetAutoStartAnalysis(bool bOnOff)`
- L87 _public function_ `void SetAndSaveAutoStartAnalysis(bool bOnOff)`
- L89 _public function_ `FString GetAutoStartAnalysisPlatform() const`
- L90 _public function_ `void SetAutoStartAnalysisPlatform(const FString& Value)`
- L91 _public function_ `void SetAndSaveAutoStartAnalysisPlatform(const FString& Value)`
- L93 _public function_ `FString GetAutoStartAnalysisAppName() const`
- L94 _public function_ `void SetAutoStartAnalysisAppName(const FString& Value)`
- L95 _public function_ `void SetAndSaveAutoStartAnalysisAppName(const FString& Value)`
- L101 _private member_ `static FInsightsFrontendSettings Defaults;` — Contains default settings.
- L104 _private member_ `FString SettingsIni;` — Setting filename ini.
- L107 _private member_ `bool bIsEditing;` — Whether profiler settings is in edit mode.
- L110 _private member_ `bool bIsDefault;` — Whether this instance contains defaults.
- L116 _private member_ `bool bAutoConnect;` — Whether Insights should signal to the Editor to auto connect and start tracing when Insights is running
- L119 _private member_ `bool bAutoStartAnalysis;` — Whether Insights should auto start analysis when a new live trace in received.
- L122 _private member_ `FString AutoStartAnalysisPlatform;` — If specified, auto-start analysis will be enabled only for live trace sessions with this specified Platform.
- L125 _private member_ `FString AutoStartAnalysisAppName;` — If specified, auto-start analysis will be enabled only for live trace sessions with this specified App Name.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L79 _macro_ `#define SET_AND_SAVE(Option, Value) { if (Option != Value) { Option = Value; SaveToConfig(); } }`

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/StoreService/DiagnosticsSessionAnalyzer.h` (Private)


#### struct `UE::Insights::FDiagnosticsSessionAnalyzer`  
`struct FDiagnosticsSessionAnalyzer : public UE::Trace::IAnalyzer`  
_L13-35_
- inherits: `UE::Trace::IAnalyzer`
- L15 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L16 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle, const FOnEventContext& Context) override;`
- L24 _public member_ `FString Platform;`
- L25 _public member_ `FString AppName;`
- L26 _public member_ `FString ProjectName;`
- L27 _public member_ `FString BuildVersion;`
- L28 _public member_ `FString Branch;`
- L29 _public member_ `FString EngineVersion;`
- L30 _public member_ `FString CommandLine;`
- L31 _public member_ `FString VFSPaths;`
- L32 _public member_ `uint32 Changelist = 0;`
- L33 _public member_ `EBuildConfiguration ConfigurationType = EBuildConfiguration::Unknown;`
- L34 _public member_ `EBuildTargetType TargetType = EBuildTargetType::Unknown;`

#### enum `UE::Insights::FDiagnosticsSessionAnalyzer::(anonymous)`  
``  
_L19-22_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L20 _enumerator_ `RouteId_Session` (scope `UE::Insights::FDiagnosticsSessionAnalyzer::__anon65abce390103`)
- L21 _enumerator_ `RouteId_Session2` (scope `UE::Insights::FDiagnosticsSessionAnalyzer::__anon65abce390103`)

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/StoreService/StoreBrowser.h` (Private)


#### struct `UE::Insights::FStoreBrowserTraceInfo`  
`struct FStoreBrowserTraceInfo`  
_L23-58_
- L25 _public member_ `uint32 TraceId = 0;`
- L27 _public member_ `uint64 ChangeSerial = 0;`
- L29 _public member_ `FString Name;`
- L30 _public member_ `FString Uri;`
- L32 _public member_ `FDateTime Timestamp = 0;`
- L33 _public member_ `uint64 Size = 0;`
- L35 _public member_ `FString Platform;`
- L36 _public member_ `FString AppName;`
- L37 _public member_ `FString ProjectName;`
- L38 _public member_ `FString BuildVersion;`
- L39 _public member_ `FString Branch;`
- L40 _public member_ `FString EngineVersion;`
- L41 _public member_ `FString CommandLine;`
- L42 _public member_ `FString VFSPaths;`
- L43 _public member_ `uint32 Changelist;`
- L44 _public member_ `EBuildConfiguration ConfigurationType = EBuildConfiguration::Unknown;`
- L45 _public member_ `EBuildTargetType TargetType = EBuildTargetType::Unknown;`
- L47 _public member_ `bool bIsLive = false;`
- L48 _public member_ `std::atomic<uint8> MetadataUpdateCount = 1;`
- L50 _public member_ `uint32 IpAddress = 0;`
- L52 _public prototype_ `FStoreBrowserTraceInfo() = default;`
- L54 _public function_ `static FDateTime ConvertTimestamp(uint64 InTimestamp)`

#### class `UE::Insights::FStoreBrowser`  
`class FStoreBrowser : public FRunnable`  
_L62-153_
- inherits: `FRunnable`
- L67 _public prototype_ `explicit FStoreBrowser(TSharedRef<UE::Trace::FStoreConnection> InTraceStoreConnection);`
- L68 _public prototype_ `virtual ~FStoreBrowser();`
- L73 _public prototype_ `virtual bool Init() override;`
- L74 _public prototype_ `virtual uint32 Run() override;`
- L75 _public prototype_ `virtual void Stop() override;`
- L76 _public prototype_ `virtual void Exit() override;`
- L95 _public function_ `bool IsRunning() const`
- L96 _public function_ `EConnectionStatus GetConnectionStatus() const`
- L98 _public function_ `bool AreSettingsLocked() const`
- L99 _public function_ `void LockSettings()`
- L100 _public function_ `void UnlockSettings()`
- L101 _public function_ `uint32 GetSettingsChangeSerial() const`
- L102 _public function_ `const FString& GetHost() const`
- L103 _public function_ `const FString& GetVersion() const`
- L104 _public function_ `uint32 GetRecorderPort() const`
- L105 _public function_ `uint32 GetStorePort() const`
- L106 _public function_ `const FString& GetStoreDirectory() const`
- L107 _public function_ `const TArray<FString>& GetWatchDirectories() const`
- L109 _public function_ `bool AreTracesLocked() const`
- L110 _public function_ `void LockTraces()`
- L111 _public function_ `void UnlockTraces()`
- L112 _public function_ `uint32 GetTracesChangeSerial() const`
- L113 _public function_ `const TArray<TSharedPtr<FStoreBrowserTraceInfo>>& GetTraces() const`
- L114 _public function_ `const TMap<uint32, TSharedPtr<FStoreBrowserTraceInfo>>& GetTraceMap() const`
- L116 _public prototype_ `void Refresh();`
- L119 _private prototype_ `void UpdateTraces();`
- L120 _private prototype_ `void ResetTraces();`
- L122 _private prototype_ `void UpdateMetadata(TSharedPtr<FStoreBrowserTraceInfo> TraceInfoPtr);`
- L126 _private member_ `std::atomic<bool> bRunning = false;` — Thread safe bool for stopping the thread
- L129 _private member_ `FRunnableThread* Thread = nullptr;` — Thread for continuously updating and caching info about trace store.
- L131 _private member_ `TSharedRef<UE::Trace::FStoreConnection> TraceStoreConnection;`
- L132 _private member_ `std::atomic<EConnectionStatus> ConnectionStatus = EConnectionStatus::Connecting;`
- L134 _private member_ `uint32 StoreChangeSerial = 0;`
- L135 _private member_ `uint32 StoreSettingsChangeSerial = 0;`
- L137 _private member_ `mutable FCriticalSection SettingsCriticalSection;`
- L138 _private member_ `std::atomic<bool> bSettingsLocked = false;` — for debugging, to ensure Get*() methods for settings are only called between Lock() - Unlock() calls.
- L139 _private member_ `uint32 SettingsChangeSerial = 0;`
- L140 _private member_ `FString Host;`
- L141 _private member_ `FString Version;`
- L142 _private member_ `uint32 StorePort;`
- L143 _private member_ `uint32 RecorderPort;`
- L144 _private member_ `FString StoreDirectory;`
- L145 _private member_ `TArray<FString> WatchDirectories;`
- L147 _private member_ `mutable FCriticalSection TracesCriticalSection;`
- L148 _private member_ `std::atomic<bool> bTracesLocked = false;` — for debugging, to ensure Get*() methods for traces are only called between Lock() - Unlock() calls.
- L149 _private member_ `uint32 TracesChangeSerial = 0;`
- L150 _private member_ `TArray<TSharedPtr<FStoreBrowserTraceInfo>> Traces;`
- L151 _private member_ `TMap<uint32, TSharedPtr<FStoreBrowserTraceInfo>> TraceMap;`
- L152 _private member_ `TMap<uint32, TSharedPtr<FStoreBrowserTraceInfo>> LiveTraceMap;`

#### enum `UE::Insights::FStoreBrowser::EConnectionStatus`  
`enum class EConnectionStatus : uint8`  
_L80-93_
- L83 _public enumerator_ `Connecting = 0` — Attempting connection
- L86 _public enumerator_ `SecondsToReconnectStart` — Values between (start,end) is interpreted as number of seconds until next reconnection attempt
- L87 _public enumerator_ `SecondsToReconnectEnd = 0xfd`
- L90 _public enumerator_ `NoConnection = 0xfe` — No connection could be made, no more reconnection attempts are made.
- L92 _public enumerator_ `Connected = 0xff` — Connection is active

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Trace` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/TraceInsightsFrontendModule.h` (Private)


#### class `UE::Insights::FTraceInsightsFrontendModule`  
`class FTraceInsightsFrontendModule : public ITraceInsightsFrontendModule`  
_L26-106_
- inherits: `ITraceInsightsFrontendModule`
- L29 _public function_ `FTraceInsightsFrontendModule() : VersionWidgetVM(MakeShared<FVersionWidget>())`
- L33 _public prototype_ `virtual ~FTraceInsightsFrontendModule() = default;`
- L38 _public prototype_ `virtual void StartupModule() override;`
- L39 _public prototype_ `virtual void ShutdownModule() override;`
- L41 _public function_ `virtual bool SupportsDynamicReloading() override`
- L49 _public prototype_ `virtual bool ConnectToStore(const TCHAR* InStoreHost, uint32 InStorePort = 0) override;`
- L51 _public prototype_ `virtual void CreateFrontendWindow(const FCreateFrontendWindowParams& Params) override;`
- L53 _public function_ `virtual TSharedPtr<STraceStoreWindow> GetTraceStoreWindow() const override`
- L54 _public function_ `virtual TSharedPtr<SConnectionWindow> GetConnectionWindow() const override`
- L56 _public prototype_ `virtual void RunAutomationTests(const FString& InCmd) override;`
- L60 _public prototype_ `FInsightsFrontendSettings& GetSettings();`
- L63 _private prototype_ `void RegisterTabSpawners();`
- L64 _private prototype_ `void UnregisterTabSpawners();`
- L67 _private prototype_ `TSharedRef<SDockTab> SpawnTraceStoreTab(const FSpawnTabArgs& Args);` — Called to spawn the Trace Store major tab.
- L70 _private prototype_ `void OnTraceStoreTabClosed(TSharedRef<SDockTab> TabBeingClosed);` — Callback called when the Trace Store major tab is closed.
- L73 _private prototype_ `TSharedRef<SDockTab> SpawnConnectionTab(const FSpawnTabArgs& Args);` — Called to spawn the Connection major tab.
- L76 _private prototype_ `void OnConnectionTabClosed(TSharedRef<SDockTab> TabBeingClosed);` — Callback called when the Connection major tab is closed.
- L80 _private member_ `TSharedPtr<FInsightsFrontendSettings> Settings;` — An instance of the main settings.
- L82 _private member_ `FCreateFrontendWindowParams CreateWindowParams;`
- L84 _private member_ `TSharedPtr<FTabManager::FLayout> PersistentLayout;`
- L85 _private member_ `static FString LayoutIni;`
- L87 _private member_ `TSharedPtr<UE::Trace::FStoreConnection> TraceStoreConnection;`
- L90 _private member_ `TWeakPtr<STraceStoreWindow> TraceStoreWindow;` — A weak pointer to the Trace Store window.
- L93 _private member_ `TWeakPtr<SConnectionWindow> ConnectionWindow;` — A weak pointer to the Connection window.
- L95 _private member_ `bool bIsMainTabSet = false;`
- L97 _private member_ `TSharedPtr<UE::Insights::FInsightsAutomationController> InsightsAutomationController;`
- L100 _private member_ `FTickerDelegate OnTick;` — The delegate to be invoked when this ticks.
- L103 _private member_ `FTSTicker::FDelegateHandle OnTickHandle;` — Handle to the registered OnTick.
- L105 _private member_ `TSharedRef<FVersionWidget> VersionWidgetVM;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Trace` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/ViewModels/TraceSetFilter.h` (Private)


#### class `UE::Insights::TTraceSetFilter`  
`template<typename TSetType> class TTraceSetFilter : public IFilter<const FTraceViewModel&>, public TSharedFromThis< TTraceSetFilter<TSetType> >`  
_L24-63_
- inherits: `IFilter<constFTraceViewModel&>,TSharedFromThis<TTraceSetFilter<TSetType>>`
- L27 _public prototype_ `TTraceSetFilter();`
- L28 _public prototype_ `virtual ~TTraceSetFilter() = default;`
- L30 _public typedef_ `typedef const FTraceViewModel& ItemType;`
- L33 _public prototype_ `DECLARE_DERIVED_EVENT(TTraceSetFilter, IFilter<ItemType>::FChangedEvent, FChangedEvent);` — Broadcasts anytime the restrictions of the Filter changes.
- L34 _public function_ `virtual FChangedEvent& OnChanged() override`
- L37 _public function_ `virtual bool PassesFilter(const FTraceViewModel& InTrace) const override` — Returns whether the specified Trace passes the Filter's restrictions.
- L42 _public function_ `bool IsEmpty() const`
- L44 _public function_ `void Reset()`
- L46 _public prototype_ `virtual void BuildMenu(FMenuBuilder& InMenuBuilder, class STraceStoreWindow& InWindow);`
- L49 _protected function_ `virtual void AddDefaultValues(TArray<TSetType>& InOutDefaultValues) const`
- L50 _protected prototype_ `virtual TSetType GetFilterValueForTrace(const FTraceViewModel& InTrace) const = 0;`
- L51 _protected prototype_ `virtual FText ValueToText(const TSetType Value) const = 0;`
- L55 _protected member_ `FChangedEvent ChangedEvent;` — The event that fires whenever new search terms are provided
- L58 _protected member_ `TSet<TSetType> FilterSet;` — The set of values used to filter
- L60 _protected member_ `FText ToggleAllActionLabel;`
- L61 _protected member_ `FText ToggleAllActionTooltip;`
- L62 _protected member_ `FText UndefinedValueLabel;`

#### class `UE::Insights::FTraceFilterByStringSet`  
`class FTraceFilterByStringSet : public TTraceSetFilter<FString>`  
_L67-74_
- inherits: `TTraceSetFilter<FString>`
- L70 _protected function_ `virtual FText ValueToText(const FString InValue) const override`

#### class `UE::Insights::FTraceFilterByPlatform`  
`class FTraceFilterByPlatform : public FTraceFilterByStringSet`  
_L78-88_
- inherits: `FTraceFilterByStringSet`
- L81 _public prototype_ `FTraceFilterByPlatform();`
- L84 _protected function_ `virtual FString GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`

#### class `UE::Insights::FTraceFilterByAppName`  
`class FTraceFilterByAppName : public FTraceFilterByStringSet`  
_L92-102_
- inherits: `FTraceFilterByStringSet`
- L95 _public prototype_ `FTraceFilterByAppName();`
- L98 _protected function_ `virtual FString GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`

#### class `UE::Insights::FTraceFilterByBuildConfig`  
`class FTraceFilterByBuildConfig : public TTraceSetFilter<uint8>`  
_L106-122_
- inherits: `TTraceSetFilter<uint8>`
- L109 _public prototype_ `FTraceFilterByBuildConfig();`
- L112 _protected function_ `virtual uint8 GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`
- L117 _protected function_ `virtual FText ValueToText(const uint8 InValue) const override`

#### class `UE::Insights::FTraceFilterByBuildTarget`  
`class FTraceFilterByBuildTarget : public TTraceSetFilter<uint8>`  
_L126-142_
- inherits: `TTraceSetFilter<uint8>`
- L129 _public prototype_ `FTraceFilterByBuildTarget();`
- L132 _protected function_ `virtual uint8 GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`
- L137 _protected function_ `virtual FText ValueToText(const uint8 InValue) const override`

#### class `UE::Insights::FTraceFilterByBuildVersion`  
`class FTraceFilterByBuildVersion : public FTraceFilterByStringSet`  
_L146-156_
- inherits: `FTraceFilterByStringSet`
- L149 _public prototype_ `FTraceFilterByBuildVersion();`
- L152 _protected function_ `virtual FString GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`

#### class `UE::Insights::FTraceFilterByBranch`  
`class FTraceFilterByBranch : public FTraceFilterByStringSet`  
_L160-170_
- inherits: `FTraceFilterByStringSet`
- L163 _public prototype_ `FTraceFilterByBranch();`
- L166 _protected function_ `virtual FString GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`

#### class `UE::Insights::FTraceFilterByChangelist`  
`class FTraceFilterByChangelist : public TTraceSetFilter<uint8>`  
_L174-204_
- inherits: `TTraceSetFilter<uint8>`
- L186 _public prototype_ `FTraceFilterByChangelist();`
- L189 _protected prototype_ `virtual void AddDefaultValues(TArray<uint8>& InOutDefaultValues) const override;`
- L191 _protected function_ `virtual uint8 GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`
- L203 _protected prototype_ `virtual FText ValueToText(const uint8 InValue) const override;`

#### enum `UE::Insights::FTraceFilterByChangelist::EChangelistCategory`  
`enum class EChangelistCategory : uint8`  
_L177-183_
- L179 _public enumerator_ `Zero` — CL 0
- L180 _public enumerator_ `NotZero`
- L182 _public enumerator_ `InvalidOrMax`

#### class `UE::Insights::FTraceFilterByEngineVersion`  
`class FTraceFilterByEngineVersion : public FTraceFilterByStringSet`  
_L208-218_
- inherits: `FTraceFilterByStringSet`
- L211 _public prototype_ `FTraceFilterByEngineVersion();`
- L214 _protected function_ `virtual FString GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`

#### class `UE::Insights::FTraceFilterBySize`  
`class FTraceFilterBySize : public TTraceSetFilter<uint8>`  
_L222-264_
- inherits: `TTraceSetFilter<uint8>`
- L237 _public prototype_ `FTraceFilterBySize();`
- L240 _protected prototype_ `virtual void AddDefaultValues(TArray<uint8>& InOutDefaultValues) const override;`
- L242 _protected function_ `virtual uint8 GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`
- L263 _protected prototype_ `virtual FText ValueToText(const uint8 InValue) const override;`

#### enum `UE::Insights::FTraceFilterBySize::ESizeCategory`  
`enum class ESizeCategory : uint8`  
_L225-234_
- L227 _public enumerator_ `Empty` — 0 bytes
- L228 _public enumerator_ `Small` — < 1 MiB
- L229 _public enumerator_ `Medium` — < 1 GiB
- L230 _public enumerator_ `Large` — >= 1 GiB
- L233 _public enumerator_ `InvalidOrMax`

#### class `UE::Insights::FTraceFilterByStatus`  
`class FTraceFilterByStatus : public TTraceSetFilter<bool>`  
_L268-282_
- inherits: `TTraceSetFilter<bool>`
- L271 _public prototype_ `FTraceFilterByStatus();`
- L274 _protected prototype_ `virtual void AddDefaultValues(TArray<bool>& InOutDefaultValues) const override;`
- L276 _protected function_ `virtual bool GetFilterValueForTrace(const FTraceViewModel& InTrace) const override`
- L281 _protected prototype_ `virtual FText ValueToText(const bool InValue) const override;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Insights` (scope `UE`)
- L33 _delegate_ `DECLARE_DERIVED_EVENT(TTraceSetFilter, IFilter<ItemType>::FChangedEvent, FChangedEvent);` — Broadcasts anytime the restrictions of the Filter changes.

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/ViewModels/TraceViewModel.h` (Private)


#### class `UE::Insights::FTraceViewModel`  
`class FTraceViewModel`  
_L19-143_
- L22 _public member_ `static constexpr uint32 InvalidTraceId = 0;`
- L25 _public prototype_ `FTraceViewModel() = default;`
- L27 _public function_ `uint64 GetChangeSerial() const`
- L28 _public function_ `void SetChangeSerial(uint64 InChangeSerial)`
- L30 _public function_ `uint32 GetId() const`
- L31 _public function_ `bool HasValidId() const`
- L32 _public function_ `void SetId(uint32 InId)`
- L34 _public function_ `uint64 GetSize() const`
- L35 _public function_ `void SetSize(uint64 InSize)`
- L37 _public function_ `FDateTime GetTimestamp() const`
- L38 _public function_ `void SetTimestamp(const FDateTime& InTimestamp)`
- L40 _public function_ `const FText& GetNameText() const`
- L41 _public function_ `const FString& GetName() const`
- L42 _public function_ `void SetName(const FString& InName)`
- L43 _public function_ `bool HasSameName(const FTraceViewModel& Other) const`
- L45 _public function_ `const FText& GetUriText() const`
- L46 _public function_ `const FString& GetUri() const`
- L47 _public function_ `void SetUri(const FString& InUri)`
- L48 _public function_ `bool HasSameUri(const FTraceViewModel& Other) const`
- L50 _public function_ `const FText& GetPlatformText() const`
- L51 _public function_ `const FString& GetPlatform() const`
- L52 _public function_ `void SetPlatform(const FString& InPlatform)`
- L54 _public function_ `const FText& GetAppNameText() const`
- L55 _public function_ `const FString& GetAppName() const`
- L56 _public function_ `void SetAppName(const FString& InAppName)`
- L58 _public function_ `EBuildConfiguration GetBuildConfiguration() const`
- L59 _public function_ `void SetBuildConfiguration(EBuildConfiguration InBuildConfiguration)`
- L61 _public function_ `EBuildTargetType GetBuildTarget() const`
- L62 _public function_ `void SetBuildTarget(EBuildTargetType InBuildTarget)`
- L64 _public function_ `const FText& GetBuildVersionText() const`
- L65 _public function_ `const FString& GetBuildVersion() const`
- L66 _public function_ `void SetBuildVersion(const FString& InBuildVersion)`
- L68 _public function_ `const FText& GetBuildBranchText() const`
- L69 _public function_ `const FString& GetBuildBranch() const`
- L70 _public function_ `void SetBuildBranch(const FString& InBuildBranch)`
- L72 _public function_ `uint32 GetChangelist() const`
- L73 _public function_ `void SetChangelist(uint32 InChangelist)`
- L75 _public function_ `const FText& GetEngineVersionText() const`
- L76 _public function_ `const FString& GetEngineVersion() const`
- L77 _public function_ `uint64 GetEngineVersionNumber() const`
- L78 _public prototype_ `void SetEngineVersion(const FString& InEngineVersion);`
- L80 _public function_ `const FText& GetCommandLineText() const`
- L81 _public function_ `const FString& GetCommandLine() const`
- L82 _public prototype_ `void SetCommandLine(const FString& InCommandLine);`
- L84 _public function_ `const FText& GetVFSPathsText() const`
- L85 _public function_ `const FString& GetVFSPaths() const`
- L86 _public prototype_ `void SetVFSPaths(const FString& InVFSPaths);`
- L88 _public function_ `bool IsLive() const`
- L89 _public function_ `void SetIsLive(bool bOnOff)`
- L91 _public function_ `bool IsMetadataUpdated() const`
- L92 _public function_ `void SetIsMetadataUpdated(bool bOnOff)`
- L94 _public function_ `bool IsRenaming() const`
- L95 _public function_ `void StartRenaming()`
- L96 _public function_ `void StopRenaming()`
- L97 _public function_ `TSharedPtr<SEditableTextBox> GetRenameTextBox() const&`
- L98 _public function_ `void SetRenameTextBox(TWeakPtr<SEditableTextBox> InRenameTextBox)`
- L100 _public function_ `const FSlateColor& GetDirectoryColor() const`
- L101 _public function_ `void SetDirectoryColor(const FSlateColor& InColor)`
- L103 _public function_ `const uint32 GetIpAddress() const`
- L104 _public function_ `void SetIpAddress(uint32 InIpAddress)`
- L106 _public function_ `static FDateTime ConvertTimestamp(uint64 InTimestamp)`
- L111 _public prototype_ `static FText AnsiStringViewToText(const FAnsiStringView& AnsiStringView);`
- L114 _private member_ `uint64 ChangeSerial = 0;`
- L115 _private member_ `uint64 EngineVersionNumber = 0;` — only used for sorting
- L116 _private member_ `uint32 TraceId = InvalidTraceId;`
- L117 _private member_ `uint32 Changelist = 0;`
- L118 _private member_ `uint64 Size = 0;`
- L119 _private member_ `FDateTime Timestamp = 0;`
- L121 _private member_ `FText NameText;`
- L122 _private member_ `FText UriText;`
- L123 _private member_ `FText PlatformText;`
- L124 _private member_ `FText AppNameText;`
- L125 _private member_ `FText BuildVersionText;`
- L126 _private member_ `FText BranchText;`
- L127 _private member_ `FText EngineVersionText;`
- L128 _private member_ `FText CommandLineText;`
- L129 _private member_ `FText VFSPathsText;`
- L131 _private member_ `FSlateColor DirectoryColor;`
- L133 _private member_ `uint32 IpAddress = 0;`
- L135 _private member_ `EBuildConfiguration ConfigurationType = EBuildConfiguration::Unknown;`
- L136 _private member_ `EBuildTargetType TargetType = EBuildTargetType::Unknown;`
- L138 _private member_ `bool bIsLive = false;`
- L139 _private member_ `bool bIsMetadataUpdated = false;`
- L140 _private member_ `bool bIsRenaming = false;`
- L142 _private member_ `TWeakPtr<SEditableTextBox> RenameTextBox;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/Widgets/SConnectionWindow.h` (Private)


#### class `UE::Insights::SConnectionWindow`  
`class SConnectionWindow : public SCompoundWidget`  
_L28-68_
- inherits: `SCompoundWidget`
- desc: Implements the Connection window.
- L31 _public prototype_ `SConnectionWindow();`
- L32 _public prototype_ `virtual ~SConnectionWindow();`
- L34 _public function_ `SLATE_BEGIN_ARGS(SConnectionWindow)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<UE::Trace::FStoreConnection> InTraceStoreConnection);`
- L41 _private prototype_ `TSharedRef<SWidget> ConstructConnectPanel();`
- L42 _private prototype_ `FReply StartUnrealInsightsDirectTrace_OnClicked();`
- L43 _private prototype_ `FReply Connect_OnClicked();`
- L46 _private member_ `TSharedPtr<UE::Trace::FStoreConnection> TraceStoreConnection;`
- L48 _private member_ `TSharedPtr<SEditableTextBox> DirectTracePortTextBox;`
- L49 _private member_ `TSharedPtr<SEditableTextBox> DirectTraceAdditionalParamsTextBox;`
- L50 _private member_ `TSharedPtr<SEditableTextBox> TraceRecorderAddressTextBox;`
- L51 _private member_ `TSharedPtr<SEditableTextBox> RunningInstanceAddressTextBox;`
- L52 _private member_ `TSharedPtr<SEditableTextBox> ChannelsTextBox;`
- L54 _private member_ `TSharedPtr<SCheckBox> AutoQuitCheckBox;`
- L55 _private member_ `TSharedPtr<SCheckBox> WaitForSymbolResolverCheckBox;`
- L56 _private member_ `TSharedPtr<SCheckBox> DisableFramerateThrottleCheckBox;`
- L57 _private member_ `TSharedPtr<SCheckBox> InsightsTestCheckBox;`
- L58 _private member_ `TSharedPtr<SCheckBox> NoUICheckBox;`
- L59 _private member_ `TSharedPtr<SCheckBox> DebugToolsCheckBox;`
- L62 _private member_ `TSharedPtr<SNotificationList> NotificationList;` — Widget for the non-intrusive notifications.
- L64 _private member_ `FGraphEventRef ConnectTask;`
- L66 _private member_ `std::atomic<bool> bIsConnecting = false;`
- L67 _private member_ `std::atomic<bool> bIsConnectedSuccessfully = false;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Trace` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/Widgets/STraceDirectoryItem.h` (Private)


#### enum `UE::Insights::ETraceDirOperations`  
`enum class ETraceDirOperations : uint8`  
_L22-28_
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `ModifyStore = 1 << 0`
- L26 _public enumerator_ `Delete = 1 << 1`
- L27 _public enumerator_ `Explore = 1 << 2`

#### struct `UE::Insights::FTraceDirectoryModel`  
`struct FTraceDirectoryModel`  
_L34-45_
- desc: View model for a source of traces. This could be the trace store default directory or an additional monitored directory.
- L36 _public function_ `FTraceDirectoryModel(FString&& InPath, const FName& InColor, ETraceDirOperations InOperations) : Path(MoveTemp(InPath)), Color(InColor), Operations(InOperations)`
- L40 _public member_ `FString Path;` — Path to directory
- L42 _public member_ `FName Color;` — Assigned color
- L44 _public member_ `ETraceDirOperations Operations;` — Supported operations

#### class `UE::Insights::STraceDirectoryItem`  
`class STraceDirectoryItem : public SCompoundWidget`  
_L49-76_
- inherits: `SCompoundWidget`
- L52 _public function_ `SLATE_BEGIN_ARGS(STraceDirectoryItem)`
- L53 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FTraceDirectoryModel> InClientItem, STraceStoreWindow* InWindow);`
- L58 _private prototype_ `TSharedRef<SWidget> ConstructOperations();`
- L60 _private prototype_ `FSlateColor GetColor() const;`
- L62 _private prototype_ `bool CanModifyStore() const;`
- L63 _private prototype_ `FReply OnModifyStore();`
- L64 _private prototype_ `FText ModifyStoreTooltip() const;`
- L66 _private prototype_ `bool CanExplore() const;`
- L67 _private prototype_ `FReply OnExplore();`
- L69 _private prototype_ `bool CanDelete() const;`
- L70 _private prototype_ `FReply OnDelete();`
- L73 _private member_ `bool bInOperation = false;`
- L74 _private member_ `STraceStoreWindow* Window = nullptr;`
- L75 _private member_ `TSharedPtr<FTraceDirectoryModel> Model;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Insights` (scope `UE`)
- L29 _prototype_ `ENUM_CLASS_FLAGS(ETraceDirOperations);` (scope `UE::Insights`)

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/Widgets/STraceListRow.h` (Private)


#### struct `UE::Insights::FTraceListColumns`  
`struct FTraceListColumns`  
_L24-39_
- L26 _public member_ `static const FName Date;`
- L27 _public member_ `static const FName Name;`
- L28 _public member_ `static const FName Uri;`
- L29 _public member_ `static const FName Platform;`
- L30 _public member_ `static const FName AppName;`
- L31 _public member_ `static const FName BuildConfig;`
- L32 _public member_ `static const FName BuildTarget;`
- L33 _public member_ `static const FName BuildVersion;`
- L34 _public member_ `static const FName BuildBranch;`
- L35 _public member_ `static const FName Changelist;`
- L36 _public member_ `static const FName EngineVersion;`
- L37 _public member_ `static const FName Size;`
- L38 _public member_ `static const FName Status;`

#### class `UE::Insights::STraceListRow`  
`class STraceListRow : public SMultiColumnTableRow<TSharedPtr<FTraceViewModel>>, public ILazyToolTipCreator`  
_L43-96_
- inherits: `SMultiColumnTableRow<TSharedPtr<FTraceViewModel>>,ILazyToolTipCreator`
- L45 _private function_ `SLATE_BEGIN_ARGS(STraceListRow)`
- L49 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FTraceViewModel> InTrace, TSharedRef<STraceStoreWindow> InParentWidget, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L51 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L53 _public prototype_ `bool IsRenaming() const;`
- L54 _public prototype_ `void RenameTextBox_OnValueCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L55 _public prototype_ `void Rename(FTraceViewModel& Trace, const FText& InText);`
- L57 _public prototype_ `FText GetTraceIndexAndId() const;`
- L58 _public prototype_ `FText GetTraceName() const;`
- L59 _public prototype_ `FSlateColor GetTraceTextColor() const;`
- L60 _public prototype_ `FText GetTraceNameHighlightText() const;`
- L61 _public prototype_ `FText GetTraceUri() const;`
- L62 _public prototype_ `FSlateColor GetColorForPath() const;`
- L63 _public prototype_ `FText GetTracePlatform() const;`
- L64 _public prototype_ `FText GetTraceAppName() const;`
- L65 _public prototype_ `FText GetTraceEngineVersion() const;`
- L66 _public prototype_ `FText GetTraceBuildVersion() const;`
- L67 _public prototype_ `FText GetTraceBranch() const;`
- L68 _public prototype_ `FText GetTraceChangelist() const;`
- L69 _public prototype_ `EVisibility TraceChangelistVisibility() const;`
- L70 _public prototype_ `FText GetTraceBuildConfiguration() const;`
- L71 _public prototype_ `FText GetTraceBuildTarget() const;`
- L72 _public prototype_ `FText GetTraceCommandLine() const;`
- L73 _public prototype_ `FText GetTraceCommandLineHighlightText() const;`
- L74 _public prototype_ `FText GetTraceVFSPaths() const;`
- L75 _public prototype_ `FText GetTraceTimestamp() const;`
- L76 _public prototype_ `FText GetTraceTimestampForTooltip() const;`
- L77 _public prototype_ `FText GetTraceSize() const;`
- L78 _public prototype_ `FText GetTraceSizeForTooltip() const;`
- L79 _public prototype_ `FSlateColor GetColorBySize() const;`
- L80 _public prototype_ `FText GetTraceStatus() const;`
- L81 _public prototype_ `FText GetTraceStatusForTooltip() const;`
- L82 _public prototype_ `TSharedPtr<IToolTip> GetTraceTooltip() const;`
- L85 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTooltip() const override;` — ILazyToolTipCreator
- L88 _private prototype_ `void AddGridPanelRow(TSharedPtr<SGridPanel> Grid, int32 Row, const FText& InHeaderText, typename TAttribute<FText>::FGetter::template TConstMethodPtr<STraceListRow> InValueTextFn, typename TAttribute<FText>::FGetter::template TConstMethodPtr<STraceListRow> InHighlightTextFn = nullptr, typename TAttribute<EVisibility>::FGetter::template TConstMethodPtr<STraceListRow> InVisibilityFn = nullptr) const;`
- L94 _private member_ `TWeakPtr<FTraceViewModel> WeakTrace;`
- L95 _private member_ `TWeakPtr<STraceStoreWindow> WeakParentWidget;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsFrontend/Private/InsightsFrontend/Widgets/STraceStoreWindow.h` (Private)


#### class `UE::Insights::STraceStoreWindow`  
`class STraceStoreWindow : public SCompoundWidget`  
_L71-489_
- inherits: `SCompoundWidget`
- desc: Implements the Trace Store window.
- L77 _public prototype_ `STraceStoreWindow();`
- L78 _public prototype_ `virtual ~STraceStoreWindow();`
- L80 _public function_ `SLATE_BEGIN_ARGS(STraceStoreWindow)`
- L81 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<UE::Trace::FStoreConnection> InTraceStoreConnection);`
- L88 _public prototype_ `FInsightsFrontendSettings& GetSettings();`
- L89 _public prototype_ `const FInsightsFrontendSettings& GetSettings() const;`
- L91 _public prototype_ `void OpenSettings();`
- L92 _public prototype_ `void CloseSettings();`
- L96 _public prototype_ `void GetExtraCommandLineParams(FString& OutParams) const;`
- L98 _public function_ `void SetEnableAutomaticTesting(bool InValue)`
- L99 _public function_ `bool GetEnableAutomaticTesting() const`
- L101 _public function_ `void SetEnableDebugTools(bool InValue)`
- L102 _public function_ `bool GetEnableDebugTools() const`
- L104 _public function_ `void SetStartProcessWithStompMalloc(bool InValue)`
- L105 _public function_ `bool GetStartProcessWithStompMalloc() const`
- L107 _public function_ `void SetDisableFramerateThrottle(bool InValue)`
- L108 _public function_ `bool GetDisableFramerateThrottle() const`
- L110 _public function_ `void SetDeleteTraceConfirmationWindowVisibility(bool bIsVisible)`
- L114 _public prototype_ `void OnFilterChanged();`
- L115 _public prototype_ `const TArray<TSharedPtr<FTraceViewModel>>& GetAllAvailableTraces() const;`
- L117 _public function_ `bool HasValidTraceStoreConnection() const`
- L118 _public function_ `UE::Trace::FStoreConnection& GetTraceStoreConnection()`
- L119 _public prototype_ `bool IsConnected() const;`
- L122 _private prototype_ `TSharedRef<SWidget> ConstructFiltersToolbar();`
- L123 _private prototype_ `TSharedRef<SWidget> ConstructSessionsPanel();`
- L124 _private prototype_ `TSharedRef<SWidget> ConstructLoadPanel();`
- L125 _private prototype_ `FText GetConnectionStatusTooltip() const;`
- L126 _private prototype_ `const FSlateBrush* GetConnectionStatusIcon() const;`
- L127 _private prototype_ `EVisibility VisibleIfConnected() const;`
- L128 _private prototype_ `EVisibility VisibleIfNotConnected() const;`
- L129 _private prototype_ `EVisibility HiddenIfNotConnected() const;`
- L130 _private prototype_ `TSharedRef<SWidget> ConstructTraceStoreDirectoryPanel();`
- L131 _private prototype_ `TSharedRef<SWidget> ConstructAutoStartPanel();`
- L134 _private prototype_ `TSharedRef<ITableRow> TraceList_OnGenerateRow(TSharedPtr<FTraceViewModel> InTrace, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a new row for the Traces list view.
- L136 _private prototype_ `TSharedPtr<SWidget> TraceList_GetMenuContent();`
- L138 _private prototype_ `bool CanRenameSelectedTrace() const;`
- L139 _private prototype_ `void RenameSelectedTrace();`
- L141 _private prototype_ `bool CanDeleteSelectedTraces() const;`
- L142 _private prototype_ `void DeleteSelectedTraces();`
- L143 _private prototype_ `bool DeleteTrace(const TSharedPtr<FTraceViewModel>& TraceToDelete);`
- L145 _private prototype_ `bool CanCopyTraceId() const;`
- L146 _private prototype_ `void CopyTraceId();`
- L148 _private prototype_ `bool CanCopyFullPath() const;`
- L149 _private prototype_ `void CopyFullPath();`
- L151 _private prototype_ `bool CanOpenContainingFolder() const;`
- L152 _private prototype_ `void OpenContainingFolder();`
- L154 _private prototype_ `bool HasAnyLiveTrace() const;`
- L159 _private prototype_ `void ShowSplashScreenOverlay();`
- L160 _private prototype_ `void TickSplashScreenOverlay(const float InDeltaTime);`
- L161 _private prototype_ `float SplashScreenOverlayOpacity() const;`
- L163 _private prototype_ `EVisibility SplashScreenOverlay_Visibility() const;`
- L164 _private prototype_ `FSlateColor SplashScreenOverlay_ColorAndOpacity() const;`
- L165 _private prototype_ `FSlateColor SplashScreenOverlay_TextColorAndOpacity() const;`
- L166 _private prototype_ `FText GetSplashScreenOverlayText() const;`
- L170 _private prototype_ `bool Open_IsEnabled() const;`
- L171 _private prototype_ `FReply Open_OnClicked();`
- L178 _private prototype_ `bool ShowOpenTraceFileDialog(FString& OutTraceFile) const;` — Shows the open file dialog for choosing a trace file. @param OutTraceFile - The chosen trace file, if successful @return True, if successful.
- L180 _private prototype_ `void OpenTraceFile();`
- L181 _private prototype_ `void OpenTraceFile(const FString& InTraceFile);`
- L183 _private prototype_ `void OpenTraceSession(TSharedPtr<FTraceViewModel> InTrace);`
- L184 _private prototype_ `void OpenTraceSession(uint32 InTraceId);`
- L189 _private prototype_ `TSharedRef<SWidget> MakeTraceListMenu();`
- L191 _private prototype_ `TSharedRef<SWidget> MakePlatformColumnHeaderMenu();`
- L192 _private prototype_ `TSharedRef<SWidget> MakePlatformFilterMenu();`
- L193 _private prototype_ `void BuildPlatformFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L195 _private prototype_ `TSharedRef<SWidget> MakeAppNameColumnHeaderMenu();`
- L196 _private prototype_ `TSharedRef<SWidget> MakeAppNameFilterMenu();`
- L197 _private prototype_ `void BuildAppNameFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L199 _private prototype_ `TSharedRef<SWidget> MakeBuildConfigColumnHeaderMenu();`
- L200 _private prototype_ `TSharedRef<SWidget> MakeBuildConfigFilterMenu();`
- L201 _private prototype_ `void BuildBuildConfigFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L203 _private prototype_ `TSharedRef<SWidget> MakeBuildTargetColumnHeaderMenu();`
- L204 _private prototype_ `TSharedRef<SWidget> MakeBuildTargetFilterMenu();`
- L205 _private prototype_ `void BuildBuildTargetFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L207 _private prototype_ `TSharedRef<SWidget> MakeBuildVersionColumnHeaderMenu();`
- L208 _private prototype_ `TSharedRef<SWidget> MakeBuildVersionFilterMenu();`
- L209 _private prototype_ `void BuildBuildVersionFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L211 _private prototype_ `TSharedRef<SWidget> MakeBranchColumnHeaderMenu();`
- L212 _private prototype_ `TSharedRef<SWidget> MakeBranchFilterMenu();`
- L213 _private prototype_ `void BuildBranchFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L215 _private prototype_ `TSharedRef<SWidget> MakeChangelistColumnHeaderMenu();`
- L216 _private prototype_ `TSharedRef<SWidget> MakeChangelistFilterMenu();`
- L217 _private prototype_ `void BuildChangelistFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L219 _private prototype_ `TSharedRef<SWidget> MakeEngineVersionColumnHeaderMenu();`
- L220 _private prototype_ `TSharedRef<SWidget> MakeEngineVersionFilterMenu();`
- L221 _private prototype_ `void BuildEngineVersionFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L223 _private prototype_ `TSharedRef<SWidget> MakeSizeColumnHeaderMenu();`
- L224 _private prototype_ `TSharedRef<SWidget> MakeSizeFilterMenu();`
- L225 _private prototype_ `void BuildSizeFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L227 _private prototype_ `TSharedRef<SWidget> MakeStatusColumnHeaderMenu();`
- L228 _private prototype_ `TSharedRef<SWidget> MakeStatusFilterMenu();`
- L229 _private prototype_ `void BuildStatusFilterSubMenu(FMenuBuilder& InMenuBuilder);`
- L231 _private prototype_ `FReply RefreshTraces_OnClicked();`
- L232 _private prototype_ `FSlateColor GetColorByPath(const FString& Uri);`
- L234 _private prototype_ `void RefreshTraceList();`
- L235 _private prototype_ `void UpdateTrace(FTraceViewModel& InOutTrace, const FStoreBrowserTraceInfo& InSourceTrace);`
- L236 _private prototype_ `void OnTraceListChanged();`
- L238 _private prototype_ `TSharedPtr<FTraceViewModel> GetSingleSelectedTrace() const;`
- L240 _private prototype_ `void TraceList_OnSelectionChanged(TSharedPtr<FTraceViewModel> InTrace, ESelectInfo::Type SelectInfo);`
- L241 _private prototype_ `void TraceList_OnMouseButtonDoubleClick(TSharedPtr<FTraceViewModel> InTrace);`
- L246 _private prototype_ `ECheckBoxState AutoStart_IsChecked() const;`
- L247 _private prototype_ `void AutoStart_OnCheckStateChanged(ECheckBoxState NewState);`
- L252 _private prototype_ `ECheckBoxState AutoConnect_IsChecked() const;`
- L253 _private prototype_ `void AutoConnect_OnCheckStateChanged(ECheckBoxState NewState);`
- L258 _private prototype_ `FText GetTraceStoreDirectory() const;`
- L259 _private prototype_ `FReply ExploreTraceStoreDirectory_OnClicked();`
- L261 _private prototype_ `FString GetStoreDirectory() const;`
- L263 _private prototype_ `bool CanChangeStoreSettings() const;`
- L265 _private prototype_ `TSharedRef<ITableRow> TraceDirs_OnGenerateRow(TSharedPtr<FTraceDirectoryModel> Item, const TSharedRef<STableViewBase>& Owner);`
- L267 _private prototype_ `FReply StoreSettingsArea_Toggle() const;`
- L268 _private prototype_ `const FSlateBrush* StoreSettingsToggle_Icon() const;`
- L270 _private prototype_ `FReply AddWatchDir_Clicked();`
- L277 _private prototype_ `EActiveTimerReturnType UpdateActiveDuration(double InCurrentTime, float InDeltaTime);` — Updates the amount of time the profiler has been active.
- L286 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Ticks this widget.  Override in derived classes, but always call the parent implementation. @param  AllottedGeometry The space allotted for this widget @param  InCurrentTime  Current absolute real time @param  InDeltaTime  Real time passed since last tick
- L294 _private prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — The system will use this event to notify a widget that the cursor has entered it. This event is NOT bubbled. @param MyGeometry The Geometry of the widget receiving the event @param MouseEvent Information about the input event
- L301 _private prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;` — The system will use this event to notify a widget that the cursor has left it. This event is NOT bubbled. @param MouseEvent Information about the input event
- L311 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Called after a key is pressed when this widget has focus @param MyGeometry The Geometry of the widget receiving the event @param  InKeyEvent  Key event @return  Returns whether the event was handled, along with other possible actions
- L321 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Called when the user is dropping something onto a widget; terminates drag and drop. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L331 _private prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Called during drag and drop when the mouse is being dragged over a widget. @param MyGeometry      The geometry of the widget receiving the event. @param DragDropEvent   The drag and drop event. @return A reply that indicated whether this event was handled.
- L334 _private prototype_ `bool CoreTick(float DeltaTime);` — Updates this class, done through FCoreTicker. Updates also when the page is not visible, unlike the Tick() function
- L339 _private prototype_ `void FilterByNameSearchBox_OnTextChanged(const FText& InFilterText);`
- L341 _private function_ `FText GetFilterStatsText() const`
- L343 _private prototype_ `void CreateFilters();`
- L352 _private prototype_ `void HandleItemToStringArray(const FTraceViewModel& InTrace, TArray<FString>& OutSearchStrings) const;` — Populates OutSearchStrings with the strings that should be used in searching. @param GroupOrStatNodePtr - the group and stat node to get a text description from. @param OutSearchStrings   - an array of strings to use in searching.
- L354 _private prototype_ `void UpdateFiltering();`
- L356 _private prototype_ `void UpdateFilterStatsText();`
- L361 _private prototype_ `EColumnSortMode::Type GetSortModeForColumn(const FName ColumnId) const;`
- L362 _private prototype_ `void OnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L364 _private prototype_ `void UpdateSorting();`
- L368 _private prototype_ `void UpdateTraceListView();`
- L370 _private prototype_ `void ShowSuccessMessage(FText& InMessage);`
- L371 _private prototype_ `void ShowFailMessage(FText& InMessage);`
- L373 _private prototype_ `void EnableAutoConnect();`
- L374 _private prototype_ `void DisableAutoConnect();`
- L376 _private prototype_ `void AutoStartPlatformFilterBox_OnValueCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L377 _private prototype_ `void AutoStartAppNameFilterBox_OnValueCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L380 _private member_ `FTickerDelegate OnTick;`
- L381 _private member_ `FTSTicker::FDelegateHandle OnTickHandle;`
- L384 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;` — The handle to the active update duration tick
- L387 _private member_ `float DurationActive = 0.0f;` — The number of seconds the profiler has been active
- L392 _private member_ `TSharedPtr<SVerticalBox> MainContentPanel;`
- L395 _private member_ `TSharedPtr<SNotificationList> NotificationList;` — Widget for the non-intrusive notifications.
- L398 _private member_ `SOverlay::FOverlaySlot* OverlaySettingsSlot = nullptr;` — Overlay slot which contains the profiler settings widget.
- L402 _private member_ `TSharedPtr<UE::Trace::FStoreConnection> TraceStoreConnection;`
- L403 _private member_ `TUniquePtr<FStoreBrowser> StoreBrowser;`
- L404 _private member_ `uint32 SettingsChangeSerial = 0;`
- L405 _private member_ `uint32 TracesChangeSerial = 0;`
- L407 _private member_ `TArray<TSharedPtr<FTraceDirectoryModel>> StoreDirectoryModel;`
- L408 _private member_ `TArray<TSharedPtr<FTraceDirectoryModel>> WatchDirectoriesModel;`
- L410 _private member_ `TArray<TSharedPtr<FTraceViewModel>> TraceViewModels;` — all available trace view models
- L411 _private member_ `TArray<TSharedPtr<FTraceViewModel>> FilteredTraceViewModels;` — the filtered list of trace view models
- L412 _private member_ `TMap<uint32, TSharedPtr<FTraceViewModel>> TraceViewModelMap;`
- L414 _private member_ `TSharedPtr<SEditableTextBox> StoreDirTextBox;`
- L415 _private member_ `TSharedPtr<SEditableTextBox> StoreHostTextBox;`
- L416 _private member_ `TSharedPtr<STableViewBase> StoreDirListView;`
- L417 _private member_ `TSharedPtr<SScrollBox> StoreSettingsArea;`
- L418 _private member_ `TSharedPtr<STableViewBase> WatchDirsListView;`
- L419 _private member_ `TSharedPtr<SListView<TSharedPtr<FTraceViewModel>>> TraceListView;`
- L421 _private member_ `bool bIsUserSelectedTrace = false;`
- L424 _private member_ `bool bIsDeleteTraceConfirmWindowVisible = true;` — Parameter that controls the visibility of the confirmation window in case the trace is deleted.
- L429 _private member_ `TSharedPtr<FTraceViewModelFilterCollection> Filters;`
- L431 _private member_ `bool bSearchByCommandLine = false;`
- L432 _private member_ `TSharedPtr<SSearchBox> FilterByNameSearchBox;`
- L433 _private member_ `TSharedPtr<FTraceTextFilter> FilterByName;`
- L435 _private member_ `TSharedPtr<FTraceFilterByPlatform> FilterByPlatform;`
- L436 _private member_ `TSharedPtr<FTraceFilterByAppName> FilterByAppName;`
- L437 _private member_ `TSharedPtr<FTraceFilterByBuildConfig> FilterByBuildConfig;`
- L438 _private member_ `TSharedPtr<FTraceFilterByBuildTarget> FilterByBuildTarget;`
- L439 _private member_ `TSharedPtr<FTraceFilterByBuildVersion> FilterByBuildVersion;`
- L440 _private member_ `TSharedPtr<FTraceFilterByBranch> FilterByBranch;`
- L441 _private member_ `TSharedPtr<FTraceFilterByChangelist> FilterByChangelist;`
- L442 _private member_ `TSharedPtr<FTraceFilterByEngineVersion> FilterByEngineVersion;`
- L443 _private member_ `TSharedPtr<FTraceFilterBySize> FilterBySize;`
- L444 _private member_ `TSharedPtr<FTraceFilterByStatus> FilterByStatus;`
- L446 _private member_ `bool bFilterStatsTextIsDirty = true;`
- L447 _private member_ `FText FilterStatsText;`
- L452 _private member_ `FName SortColumn;`
- L453 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::None;`
- L458 _private member_ `TArray<uint32> AutoStartedSessions;` — tracks sessions that were auto started (in order to not start them again)
- L460 _private member_ `TSharedPtr<SSearchBox> AutoStartPlatformFilter;`
- L461 _private member_ `TSharedPtr<SSearchBox> AutoStartAppNameFilter;`
- L462 _private member_ `EBuildConfiguration AutoStartConfigurationTypeFilter = EBuildConfiguration::Unknown;`
- L463 _private member_ `EBuildTargetType AutoStartTargetTypeFilter = EBuildTargetType::Unknown;`
- L467 _private member_ `FString SplashScreenOverlayTraceFile;`
- L468 _private member_ `float SplashScreenOverlayFadeTime = 0.0f;`
- L470 _private member_ `mutable FString OpenTraceFileDefaultDirectory;`
- L472 _private member_ `bool bEnableAutomaticTesting = false;`
- L473 _private member_ `bool bEnableDebugTools = false;`
- L474 _private member_ `bool bStartProcessWithStompMalloc = false;`
- L476 _private member_ `bool bDisableFramerateThrottle = false;`
- L477 _private member_ `bool bSetKeyboardFocusOnNextTick = false;`
- L479 _private member_ `TArray<FTraceServerControl> ServerControls;`
- L482 _private member_ `void* AutoConnectEvent = nullptr;`
- L484 _private member_ `sem_t* AutoConnectEvent = SEM_FAILED;`
- L487 _private member_ `static FName LogListingName;`
- L488 _private member_ `TSharedRef<FTableImporter> TableImporter;`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Trace` (scope `UE`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace Insights` (scope `UE`)
- L63 _typedef_ `typedef TFilterCollection<const FTraceViewModel&> FTraceViewModelFilterCollection;` (scope `UE::Insights`) — The filter collection - used for updating the list of trace sessions.
- L66 _typedef_ `typedef TTextFilter<const FTraceViewModel&> FTraceTextFilter;` (scope `UE::Insights`) — The text based filter - used for updating the list of trace sessions.

### `Source/Developer/TraceInsightsFrontend/Public/InsightsFrontend/Common/InsightsFrontendStyle.h` (Public)


#### class `UE::Insights::FInsightsFrontendStyle`  
`class FInsightsFrontendStyle`  
_L21-79_
- L24 _public prototype_ `static void Initialize();`
- L25 _public prototype_ `static void Shutdown();`
- L27 _public prototype_ `static FName GetStyleSetName();`
- L28 _public prototype_ `static const ISlateStyle& Get();`
- L30 _public function_ `static const FLinearColor& GetColor(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L35 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L40 _public function_ `static const FSlateBrush* GetOutlineBrush(EHorizontalAlignment HAlign)`
- L76 _private prototype_ `static TSharedRef<FInsightsFrontendStyle::FStyle> Create();`
- L78 _private member_ `static TSharedPtr<FInsightsFrontendStyle::FStyle> StyleInstance;`

#### class `UE::Insights::FInsightsFrontendStyle::FStyle`  
`class FStyle : public FSlateStyleSet`  
_L56-73_
- inherits: `FSlateStyleSet`
- L59 _public prototype_ `FStyle(const FName& InStyleSetName);`
- L61 _public prototype_ `void Initialize();`
- L63 _public prototype_ `void SyncParentStyles();`
- L67 _public member_ `FTextBlockStyle NormalText;` — Styles inherited from the parent style
- L68 _public member_ `FButtonStyle Button;`
- L69 _public member_ `FSlateColor SelectorColor;`
- L70 _public member_ `FSlateColor SelectionColor;`
- L71 _public member_ `FSlateColor SelectionColor_Inactive;`
- L72 _public member_ `FSlateColor SelectionColor_Pressed;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACEINSIGHTSFRONTEND_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsFrontend/Public/InsightsFrontend/Common/Log.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInsightsFrontend, Verbose, All);`

### `Source/Developer/TraceInsightsFrontend/Public/InsightsFrontend/Config.h` (Public)
_(no declarations extracted)_

### `Source/Developer/TraceInsightsFrontend/Public/InsightsFrontend/ITraceInsightsFrontendModule.h` (Public)


#### struct `UE::Insights::FCreateFrontendWindowParams`  
`struct FCreateFrontendWindowParams`  
_L16-23_
- desc: Contains parameters that are passed to the CreateSessionBrowser function to control specific behaviors.
- L18 _public member_ `bool bAllowDebugTools = false;`
- L19 _public member_ `bool bInitializeTesting = false;`
- L20 _public member_ `bool bStartProcessWithStompMalloc = false;`
- L21 _public member_ `bool bDisableFramerateThrottle = false;`
- L22 _public member_ `bool bAutoQuit = false;`

#### struct `UE::Insights::FInsightsFrontendTabs`  
`struct FInsightsFrontendTabs`  
_L25-29_
- L27 _public member_ `static const FName TraceStoreTabId;`
- L28 _public member_ `static const FName ConnectionTabId;`

#### class `ITraceInsightsFrontendModule`  
`class ITraceInsightsFrontendModule : public IModuleInterface`  
_L37-53_
- inherits: `IModuleInterface`
- desc: Interface for TraceInsightsCore module.
- L40 _public prototype_ `virtual ~ITraceInsightsFrontendModule() = default;`
- L42 _public prototype_ `virtual bool ConnectToStore(const TCHAR* InStoreHost, uint32 InStorePort = 0) = 0;`
- L44 _public prototype_ `virtual void CreateFrontendWindow(const UE::Insights::FCreateFrontendWindowParams& Params) = 0;`
- L46 _public prototype_ `virtual TSharedPtr<UE::Insights::STraceStoreWindow> GetTraceStoreWindow() const = 0;`
- L47 _public prototype_ `virtual TSharedPtr<UE::Insights::SConnectionWindow> GetConnectionWindow() const = 0;`
- L52 _public prototype_ `virtual void RunAutomationTests(const FString& InCmd) = 0;` — Called to run automation tests in Unreal Insights.

#### Free symbols / members of external scopes

- L10 _macro_ `#define INSIGHTS_ENABLE_AUTOMATION !WITH_EDITOR`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Insights` (scope `UE`)

### `Source/Developer/TraceInsightsFrontend/Public/InsightsFrontend/StoreService/TraceServerControl.h` (Public)


#### class `UE::Insights::FTraceServerControl`  
`class FTraceServerControl`  
_L23-74_
- L26 _public prototype_ `FTraceServerControl(const TCHAR* Host, uint32 Port = 0, FName StyleSet = NAME_None);`
- L27 _public prototype_ `~FTraceServerControl();`
- L29 _public prototype_ `void MakeMenu(FMenuBuilder& Builder);`
- L41 _private prototype_ `bool ChangeState(EState Expected, EState ChangeTo, uint32 Attempts = 1);`
- L43 _private prototype_ `void TriggerStatusUpdate();`
- L44 _private prototype_ `void UpdateStatus();`
- L45 _private prototype_ `void ResetStatus();`
- L47 _private function_ `bool CanServerBeStarted() const`
- L48 _private function_ `bool CanServerBeStopped() const`
- L49 _private function_ `bool AreControlsEnabled() const`
- L50 _private function_ `bool IsSponsored() const`
- L52 _private prototype_ `void OnStart_Clicked();`
- L53 _private prototype_ `void OnStop_Clicked();`
- L54 _private prototype_ `void OnSponsored_Changed();`
- L56 _private member_ `std::atomic<EState> State = EState::NotConnected;`
- L58 _private member_ `std::atomic<bool> bCanServerBeStarted = false;`
- L59 _private member_ `std::atomic<bool> bCanServerBeStopped = false;`
- L60 _private member_ `std::atomic<bool> bSponsored = false;`
- L61 _private member_ `std::atomic<bool> bIsCancelRequested = false;`
- L63 _private member_ `FCriticalSection AsyncTaskLock;`
- L64 _private member_ `FCriticalSection StringsLock;`
- L65 _private member_ `FString StatusString;`
- L67 _private member_ `FString Host;`
- L68 _private member_ `uint32 Port = 0;`
- L69 _private member_ `FName StyleSet;`
- L70 _private member_ `bool bIsLocalHost = false;`
- L71 _private member_ `TUniquePtr<UE::Trace::FStoreClient> Client;`

#### enum `UE::Insights::FTraceServerControl::EState`  
`enum class EState : uint8`  
_L32-39_
- L34 _public enumerator_ `NotConnected`
- L35 _public enumerator_ `Connecting`
- L36 _public enumerator_ `Connected`
- L37 _public enumerator_ `CheckStatus`
- L38 _public enumerator_ `Command`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TRACEINSIGHTSFRONTEND_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Trace` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Insights` (scope `UE`)
