# Plugins / AudioInsights

- module root: `Plugins/AudioInsights/Source/AudioInsights`
- headers: 79; symbols: 3103
- symbol kinds: class=86, delegate=47, enum=24, enumerator=96, externvar=39, function=368, macro=41, member=865, namespace=229, prototype=1168, struct=80, typedef=18, variable=42
- PrivateDependencyModuleNames: AudioMixerCore, AudioWidgetsCore, BuildSettings, CoreUObject, DeveloperSettings, InputCore, OutputLog, SessionServices, Slate, SlateCore, Sockets, ToolMenus, TraceAnalysis, TraceLog, UnrealEd
- PublicDependencyModuleNames: Core, Engine, RewindDebuggerRuntimeInterface, ToolWidgets, TraceInsights, TraceServices

### `Plugins/AudioInsights/Source/AudioInsights/Private/AssetEditorCommands.h` (Private)


#### class `UE::Audio::Insights::FAssetEditorCommands`  
`class FAssetEditorCommands : public TCommands<FAssetEditorCommands>`  
_L11-24_
- inherits: `TCommands<FAssetEditorCommands>`
- L14 _public prototype_ `FAssetEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public function_ `TSharedPtr<const FUICommandInfo> GetBrowseCommand() const`
- L19 _public function_ `TSharedPtr<const FUICommandInfo> GetEditCommand() const`
- L22 _private member_ `TSharedPtr<FUICommandInfo> Browse;`
- L23 _private member_ `TSharedPtr<FUICommandInfo> Edit;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/AudioEventLogEditorCommands.h` (Private)


#### class `UE::Audio::Insights::FAudioEventLogEditorCommands`  
`class FAudioEventLogEditorCommands : public TCommands<FAudioEventLogEditorCommands>`  
_L11-26_
- inherits: `TCommands<FAudioEventLogEditorCommands>`
- L14 _public prototype_ `FAudioEventLogEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public function_ `TSharedPtr<const FUICommandInfo> GetBrowseCommand() const`
- L19 _public function_ `TSharedPtr<const FUICommandInfo> GetEditCommand() const`
- L20 _public function_ `TSharedPtr<const FUICommandInfo> GetResetInspectTimestampCommand() const`
- L23 _private member_ `TSharedPtr<FUICommandInfo> Browse;`
- L24 _private member_ `TSharedPtr<FUICommandInfo> Edit;`
- L25 _private member_ `TSharedPtr<FUICommandInfo> ResetInspectTimestampEventLog;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/AudioInsightsComponent.h` (Private)


#### class `UE::Audio::Insights::FAudioInsightsComponent`  
`class FAudioInsightsComponent : public IInsightsComponent, public TSharedFromThis<FAudioInsightsComponent>`  
_L14-54_
- inherits: `IInsightsComponent,TSharedFromThis<FAudioInsightsComponent>`
- desc: The component that makes Audio Insights available inside Unreal Insights.
- L17 _public prototype_ `FAudioInsightsComponent() = default;`
- L18 _public prototype_ `virtual ~FAudioInsightsComponent();`
- L20 _public prototype_ `static TSharedPtr<FAudioInsightsComponent> CreateInstance();`
- L23 _public prototype_ `virtual void Initialize(IUnrealInsightsModule& InsightsModule) override;` — IInsightsComponent overrides
- L24 _public prototype_ `virtual void Shutdown() override;`
- L25 _public prototype_ `virtual void RegisterMajorTabs(IUnrealInsightsModule& InsightsModule) override;`
- L26 _public prototype_ `virtual void UnregisterMajorTabs() override;`
- L28 _public prototype_ `bool GetIsLiveSession() const;`
- L29 _public prototype_ `bool IsSessionAnalysisComplete() const;`
- L30 _public function_ `bool GetIsEditorTrace() const`
- L32 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTabSpawn);`
- L33 _public member_ `FOnTabSpawn OnTabSpawn;`
- L35 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSessionAnalysisCompleted);`
- L36 _public member_ `FOnSessionAnalysisCompleted OnSessionAnalysisCompleted;`
- L39 _private prototype_ `bool CanSpawnTab(const FSpawnTabArgs& Args) const;`
- L40 _private prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args);`
- L42 _private prototype_ `void OnSessionAnalysisCompletedEvent();`
- L44 _private prototype_ `bool Tick(float DeltaTime);`
- L46 _private member_ `bool bIsInitialized = false;`
- L47 _private member_ `bool bIsEditorTrace = false;`
- L48 _private member_ `bool bCanSpawnTab = false;`
- L50 _private member_ `FTickerDelegate OnTick;`
- L51 _private member_ `FTSTicker::FDelegateHandle OnTickHandle;`
- L53 _private member_ `inline static TSharedPtr<FAudioInsightsComponent> Instance;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTabSpawn);`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSessionAnalysisCompleted);`

### `Plugins/AudioInsights/Source/AudioInsights/Private/AudioInsightsModule.h` (Private)


#### class `UE::Audio::Insights::FAudioInsightsModule`  
`class FAudioInsightsModule final : public IAudioInsightsModule`  
_L25-85_
- inherits: `IAudioInsightsModule`
- L28 _public prototype_ `FAudioInsightsModule() = default;`
- L29 _public prototype_ `virtual ~FAudioInsightsModule() = default;`
- L31 _public prototype_ `FAudioInsightsModule(const FAudioInsightsModule&) = delete;`
- L32 _public prototype_ `FAudioInsightsModule& operator=(const FAudioInsightsModule&) = delete;`
- L33 _public prototype_ `FAudioInsightsModule(FAudioInsightsModule&&) = delete;`
- L34 _public prototype_ `FAudioInsightsModule& operator=(FAudioInsightsModule&&) = delete;`
- L36 _public prototype_ `virtual void StartupModule() override;`
- L37 _public prototype_ `virtual void ShutdownModule() override;`
- L38 _public prototype_ `virtual void RegisterDashboardViewFactory(TSharedRef<IDashboardViewFactory> InDashboardFactory) override;`
- L39 _public prototype_ `virtual void UnregisterDashboardViewFactory(FName InName) override;`
- L40 _public prototype_ `virtual void RegisterEventLogCategories(const TMap<FString, TSet<FString>>& InCategoriesToEvents) override;`
- L41 _public prototype_ `virtual void RegisterEventLogDisplayNames(const TMap<FString, FText>& InDisplayNames) override;`
- L43 _public prototype_ `virtual ::Audio::FDeviceId GetDeviceId() const override;`
- L45 _public prototype_ `static bool IsModuleLoaded();`
- L46 _public prototype_ `static FAudioInsightsModule& GetChecked();`
- L47 _public prototype_ `static FAudioInsightsModule* GetModulePtr();`
- L48 _public prototype_ `virtual IAudioInsightsTraceModule& GetTraceModule() override;`
- L49 _public prototype_ `virtual class FAudioInsightsCacheManager& GetCacheManager() override;`
- L52 _public function_ `TSharedPtr<FAudioInsightsComponent> GetAudioInsightsComponent()`
- L55 _public function_ `FAudioInsightsTimingViewExtender& GetTimingViewExtender()`
- L56 _public function_ `const FAudioInsightsTimingViewExtender& GetTimingViewExtender() const`
- L59 _public function_ `FAudioInsightsDetailsSelectionManager& GetDetailsSelectionManager() override`
- L62 _public prototype_ `TSharedRef<FDashboardFactory> GetDashboardFactory();`
- L63 _public prototype_ `const TSharedRef<FDashboardFactory> GetDashboardFactory() const;`
- L65 _public prototype_ `virtual TSharedRef<SDockTab> CreateDashboardTabWidget(const FSpawnTabArgs& Args) override;`
- L68 _private member_ `TSharedPtr<FDashboardFactory> DashboardFactory;`
- L70 _private member_ `TSharedPtr<FAudioEventLogDashboardViewFactory> EventLogViewFactory;`
- L72 _private member_ `TUniquePtr<FTraceModule> TraceModule;`
- L73 _private member_ `TUniquePtr<FRewindDebuggerAudioInsightsRuntime> RewindDebuggerExtension;`
- L74 _private member_ `TUniquePtr<class FAudioInsightsCacheManager> CacheManager;`
- L77 _private member_ `TSharedPtr<FAudioInsightsComponent> AudioInsightsComponent;`
- L80 _private member_ `FAudioInsightsTimingViewExtender AudioInsightsTimingViewExtender;`
- L83 _private member_ `FAudioInsightsDetailsSelectionManager DetailsSelectionManager;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/Providers/AudioBusTraceProvider.h` (Private)


#### class `UE::Audio::Insights::FAudioBusTraceProvider`  
`class FAudioBusTraceProvider : public TDeviceDataMapTraceProvider<uint32, TSharedPtr<FAudioBusDashboardEntry>>, public TSharedFromThis<FAudioBusTraceProvider>`  
_L16-71_
- inherits: `TDeviceDataMapTraceProvider<uint32,TSharedPtr<FAudioBusDashboardEntry>>,TSharedFromThis<FAudioBusTraceProvider>`
- L19 _public prototype_ `FAudioBusTraceProvider();`
- L20 _public prototype_ `virtual ~FAudioBusTraceProvider();`
- L22 _public prototype_ `static FName GetName_Static();`
- L24 _public prototype_ `virtual UE::Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) override;`
- L26 _public prototype_ `void RequestEntriesUpdate();`
- L28 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnAudioBusChanged, const uint32 );`
- L29 _public member_ `FOnAudioBusChanged OnAudioBusAdded;`
- L30 _public member_ `FOnAudioBusChanged OnAudioBusRemoved;`
- L31 _public member_ `FOnAudioBusChanged OnAudioBusStarted;`
- L33 _public prototype_ `DECLARE_DELEGATE(FOnAudioBusListUpdated);`
- L34 _public member_ `FOnAudioBusListUpdated OnAudioBusListUpdated;`
- L36 _public prototype_ `DECLARE_DELEGATE(FOnTimeMarkerUpdated);`
- L37 _public member_ `FOnTimeMarkerUpdated OnTimeMarkerUpdated;`
- L40 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioBusNameResolved, uint32 );`
- L41 _public member_ `FOnAudioBusNameResolved OnAudioBusNameResolved;`
- L43 _public prototype_ `FString GetResolvedBusName(const ::Audio::FDeviceId InDeviceId, const uint32 InAudioBusId, const FString& InFallbackName) const;`
- L47 _protected prototype_ `virtual void OnTraceChannelsEnabled() override;`
- L50 _private prototype_ `virtual bool ProcessMessages() override;`
- L53 _private prototype_ `virtual void OnTimeControlMethodReset() override;`
- L55 _private prototype_ `void HandleOnAudioBusAssetAdded(const FString& InAssetPath);`
- L56 _private prototype_ `void HandleOnAudioBusAssetRemoved(const FString& InAssetPath);`
- L57 _private prototype_ `void HandleOnAudioBusAssetListUpdated(const TArray<FString>& InAssetPaths);`
- L60 _private prototype_ `bool ApplyAssetEntryToAllDevices(const FString& InAssetPath, const TObjectPtr<UAudioBus> InAudioBus, const uint32 InAudioBusId);` — Returns true if any existing entry's Name was upgraded to InAssetPath.
- L63 _private prototype_ `virtual void OnTimingViewTimeMarkerChanged(double TimeMarker) override;`
- L65 _private member_ `FAudioBusMessages TraceMessages;`
- L68 _private member_ `TAssetProvider<UAudioBus> AudioBusAssetProvider;`
- L69 _private member_ `bool bAssetsUpdated = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Audio` (scope `UE`)
- L14 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAudioBusChanged, const uint32 );`
- L33 _delegate_ `DECLARE_DELEGATE(FOnAudioBusListUpdated);`
- L36 _delegate_ `DECLARE_DELEGATE(FOnTimeMarkerUpdated);`
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioBusNameResolved, uint32 );`

### `Plugins/AudioInsights/Source/AudioInsights/Private/Providers/AudioEventLogTraceProvider.h` (Private)


#### class `UE::Audio::Insights::FAudioEventLogTraceProvider`  
`class FAudioEventLogTraceProvider : public TDeviceDataMapTraceProvider<uint32, TSharedPtr<FAudioEventLogDashboardEntry>> , public TSharedFromThis<FAudioEventLogTraceProvider>`  
_L9-50_
- inherits: `TDeviceDataMapTraceProvider<uint32,TSharedPtr<FAudioEventLogDashboardEntry>>,TSharedFromThis<FAudioEventLogTraceProvider>`
- L14 _public prototype_ `FAudioEventLogTraceProvider();`
- L15 _public prototype_ `virtual ~FAudioEventLogTraceProvider();`
- L17 _public prototype_ `virtual UE::Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) override;`
- L19 _public prototype_ `static FName GetName_Static();`
- L21 _public prototype_ `virtual void ClearActiveAudioDeviceEntries() override;`
- L24 _protected prototype_ `virtual bool IsMessageProcessingPaused() const override;`
- L25 _protected function_ `virtual void OnTraceChannelsEnabled() override`
- L28 _private prototype_ `virtual bool ProcessMessages() override;`
- L29 _private prototype_ `virtual bool ProcessManuallyUpdatedEntries() override;`
- L31 _private prototype_ `TSharedPtr<FAudioEventLogDashboardEntry> CreateNewEntry(const FAudioEventLogMessage& Msg);`
- L33 _private prototype_ `void OnCacheChunkOverwritten(const double NewCacheStartTimestamp);`
- L34 _private prototype_ `double GetAboutToBeDeletedFromCacheTimeThreshold() const;`
- L36 _private member_ `FAudioEventLogMessages TraceMessages;`
- L46 _private member_ `TMap<uint32, FActorInformation> PlayOrderToActorInfoMap;`
- L48 _private member_ `double CacheStartTimestamp = 0.0;`
- L49 _private member_ `bool bCacheChunksUpdated = false;`

#### struct `UE::Audio::Insights::FAudioEventLogTraceProvider::FActorInformation`  
`struct FActorInformation`  
_L38-44_
- L40 _public member_ `const FString ActorLabel;`
- L41 _public member_ `const FName ActorIconName;`
- L42 _public member_ `const FString AudioComponentName;`
- L43 _public member_ `const ::Audio::FDeviceId AudioDeviceId = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Audio` (scope `UE`)
- L7 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/Providers/AudioMeterProvider.h` (Private)


#### struct `UE::Audio::Insights::FAudioMeterInfo`  
`struct FAudioMeterInfo`  
_L14-18_
- L16 _public member_ `int32 NumChannels = 0;`
- L17 _public member_ `TArray<float> EnvelopeValues;`

#### class `UE::Audio::Insights::FAudioMeterProvider`  
`class FAudioMeterProvider`  
_L20-31_
- L23 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnAddAudioMeter, const uint32 , const TSharedRef<FAudioMeterInfo>& , const FText& , const FSlateColor& );`
- L24 _public member_ `inline static FOnAddAudioMeter OnAddAudioMeter;`
- L26 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRemoveAudioMeter, const uint32 );`
- L27 _public member_ `inline static FOnRemoveAudioMeter OnRemoveAudioMeter;`
- L29 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnUpdateAudioMeterInfo, const uint32 , const TSharedRef<FAudioMeterInfo>& , const FText& );`
- L30 _public member_ `inline static FOnUpdateAudioMeterInfo OnUpdateAudioMeterInfo;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Audio` (scope `UE`)
- L12 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L23 _delegate_ `DECLARE_DELEGATE_FourParams(FOnAddAudioMeter, const uint32 , const TSharedRef<FAudioMeterInfo>& , const FText& , const FSlateColor& );`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRemoveAudioMeter, const uint32 );`
- L29 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnUpdateAudioMeterInfo, const uint32 , const TSharedRef<FAudioMeterInfo>& , const FText& );`

### `Plugins/AudioInsights/Source/AudioInsights/Private/Providers/OutputMeterTraceProvider.h` (Private)


#### class `UE::Audio::Insights::FOutputMeterTraceProvider`  
`class FOutputMeterTraceProvider : public TDeviceDataMapTraceProvider<uint32, TSharedPtr<FOutputMeterDashboardEntry>> , public TSharedFromThis<FOutputMeterTraceProvider>`  
_L9-30_
- inherits: `TDeviceDataMapTraceProvider<uint32,TSharedPtr<FOutputMeterDashboardEntry>>,TSharedFromThis<FOutputMeterTraceProvider>`
- L14 _public function_ `FOutputMeterTraceProvider() : TDeviceDataMapTraceProvider<uint32, TSharedPtr<FOutputMeterDashboardEntry>>(GetName_Static())`
- L19 _public prototype_ `virtual ~FOutputMeterTraceProvider() = default;`
- L21 _public prototype_ `virtual UE::Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) override;`
- L23 _public prototype_ `static FName GetName_Static();`
- L26 _private prototype_ `virtual bool ProcessMessages() override;`
- L27 _private prototype_ `virtual void OnTimingViewTimeMarkerChanged(double TimeMarker) override;`
- L29 _private member_ `FOutputMeterMessages TraceMessages;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Audio` (scope `UE`)
- L7 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/Providers/SignalFlowTraceProvider.h` (Private)


#### class `UE::Audio::Insights::FSignalFlowTraceProvider`  
`class FSignalFlowTraceProvider : public TDeviceDataMapTraceProvider<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>, public TSharedFromThis<FSignalFlowTraceProvider>`  
_L10-68_
- inherits: `TDeviceDataMapTraceProvider<FSignalFlowEntryKey,TSharedPtr<FSignalFlowDashboardEntry>>,TSharedFromThis<FSignalFlowTraceProvider>`
- L13 _public prototype_ `FSignalFlowTraceProvider();`
- L14 _public prototype_ `virtual ~FSignalFlowTraceProvider() = default;`
- L16 _public prototype_ `static FName GetName_Static();`
- L18 _public prototype_ `virtual UE::Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) override;`
- L19 _public prototype_ `virtual void Reset() override;`
- L21 _public prototype_ `void BindDelegates();`
- L23 _public function_ `void SetConnectionWiresAreAnimated(const bool bInAnimated)`
- L25 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRequestGraphRefresh);`
- L26 _public member_ `FOnRequestGraphRefresh OnRequestGraphRefresh;`
- L28 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnResetGraph);`
- L29 _public member_ `FOnResetGraph OnResetGraph;`
- L32 _private prototype_ `virtual bool ProcessMessages() override;`
- L33 _private prototype_ `virtual void OnTimingViewTimeMarkerChanged(double TimeMarker) override;`
- L35 _private prototype_ `void CollectSendInfoForTimestamp(const FSignalFlowEntryKey& EntryKey, TSharedPtr<FSignalFlowDashboardEntry>* Entry, const FAudioInsightsCacheManager& CacheManager, const double TimeMarker, const double RangeCheckStart);`
- L36 _private prototype_ `void CollectParamsForTimestamp(const FAudioInsightsCacheManager& CacheManager, const TSet<FSignalFlowEntryKey>& ActiveEntries, const double TimeMarker);`
- L38 _private prototype_ `virtual void OnTimeControlMethodReset() override;`
- L40 _private prototype_ `TSharedPtr<FSignalFlowDashboardEntry>* CreateEntry(const IAudioCachedMessage& Msg, const ::Audio::FDeviceId DeviceID, const ESignalFlowEntryType EntryType, const uint32 NodeID, TSet<FSignalFlowEntryKey>* OutActiveEntriesTracker = nullptr);`
- L41 _private prototype_ `TSharedPtr<FSignalFlowDashboardEntry>* CreateAudioDeviceEntry(const IAudioCachedMessage& Msg, const ::Audio::FDeviceId DeviceID, TSet<FSignalFlowEntryKey>* OutActiveEntriesTracker = nullptr);`
- L42 _private prototype_ `TSharedPtr<FSignalFlowDashboardEntry>* CreateOwnerEntry(const FSoundWaveStartMessage& Msg, TSet<FSignalFlowEntryKey>* OutActiveEntriesTracker = nullptr);`
- L43 _private prototype_ `TSharedPtr<FSignalFlowDashboardEntry>* CreateSoundSourceEntry(const FSoundWaveStartMessage& Msg, TSet<FSignalFlowEntryKey>* OutActiveEntriesTracker = nullptr);`
- L44 _private prototype_ `TSharedPtr<FSignalFlowDashboardEntry>* CreateAudioBusEntry(const FAudioBusStartMessage& Msg, TSet<FSignalFlowEntryKey>* OutActiveEntriesTracker = nullptr);`
- L45 _private prototype_ `TSharedPtr<FSignalFlowDashboardEntry>* CreateSubmixEntry(const FSubmixMessageBase& Msg, TSet<FSignalFlowEntryKey>* OutActiveEntriesTracker = nullptr);`
- L47 _private prototype_ `void ProcessNewBusEntry(const FAudioBusStartMessage& Msg, TSharedPtr<FSignalFlowDashboardEntry>* OutEntry, TSet<FSignalFlowEntryKey>& OutNewBuses);`
- L48 _private prototype_ `void ProcessNewSubmixEntry(const FSubmixLoadedMessage& Msg, TSharedPtr<FSignalFlowDashboardEntry>* OutEntry);`
- L49 _private prototype_ `void ProcessNewSoundwaveEntry(const FSoundWaveStartMessage& Msg, TSharedPtr<FSignalFlowDashboardEntry>* OutEntry, TSet<FSignalFlowEntryKey>* OutActiveEntriesTracker = nullptr);`
- L50 _private prototype_ `void ProcessStopMessage(const ::Audio::FDeviceId DeviceID, const double MsgTimestamp, TSharedPtr<FSignalFlowDashboardEntry>* OutEntry, TSet<FSignalFlowEntryKey>& OutRemovedKeys);`
- L52 _private prototype_ `void ProcessOutputSendMessage(TSharedPtr<FSignalFlowDashboardEntry>* OutEntry, const FSignalFlowEntryKey& OutputEntryKey, const float SendLevel);`
- L53 _private prototype_ `void ProcessBusPatchWriterMessage(const FBusPatchWriterConnectedMessage& Msg, TSharedPtr<FSignalFlowDashboardEntry>* OutEntry);`
- L54 _private prototype_ `void ProcessBusPatchReaderMessage(const FBusPatchReaderConnectedMessage& Msg, TSharedPtr<FSignalFlowDashboardEntry>* OutEntry);`
- L55 _private prototype_ `void ProcessMultiChannelEnvelopeMessage(TSharedPtr<FSignalFlowDashboardEntry>* OutEntry, const TArray<float>& EnvelopeValues);`
- L57 _private prototype_ `void LinkInput(const FSignalFlowDashboardEntry& Entry, const FSignalFlowEntryKey& OutputKey, const ::Audio::FDeviceId DeviceID);`
- L58 _private prototype_ `void TidyConnections(const TSet<FSignalFlowEntryKey>& RemovedKeys, const TSet<FSignalFlowEntryKey>& NewBuses);`
- L61 _private prototype_ `void HandleOnAudioBusNameResolved(const uint32 InAudioBusId);`
- L64 _private member_ `FSignalFlowMessages TraceMessages;`
- L66 _private member_ `bool bForceGraphRefresh = false;`
- L67 _private member_ `bool bAnimateWires = true;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Audio` (scope `UE`)
- L8 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRequestGraphRefresh);`
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnResetGraph);`

### `Plugins/AudioInsights/Source/AudioInsights/Private/Providers/SoundTraceProvider.h` (Private)


#### class `UE::Audio::Insights::FSoundTraceProvider`  
`class FSoundTraceProvider : public TDeviceDataMapTraceProvider<ESoundDashboardEntryType, TSharedPtr<FSoundDashboardEntry>> , public TSharedFromThis<FSoundTraceProvider>`  
_L19-87_
- inherits: `TDeviceDataMapTraceProvider<ESoundDashboardEntryType,TSharedPtr<FSoundDashboardEntry>>,TSharedFromThis<FSoundTraceProvider>`
- L24 _public prototype_ `FSoundTraceProvider();`
- L25 _public prototype_ `virtual ~FSoundTraceProvider();`
- L27 _public prototype_ `static FName GetName_Static();`
- L29 _public prototype_ `virtual UE::Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) override;`
- L31 _public prototype_ `virtual bool ProcessMessages() override;`
- L32 _public prototype_ `virtual bool ProcessManuallyUpdatedEntries() override;`
- L34 _public function_ `void SetDashboardTimeoutTime(const double InTimeOutTime)`
- L36 _public function_ `bool HasCachedPinnedEntries() const`
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnProcessPlotData);`
- L39 _public member_ `FOnProcessPlotData OnProcessPlotData;`
- L42 _private prototype_ `void GetOrCreateActiveSoundEntry(const FSoundStartMessage& Msg, TSharedPtr<FSoundDashboardEntry>& OutReturnedSoundEntry);`
- L43 _private prototype_ `void CreateAndGetActiveSoundEntryIfNotFound(const FSoundStartMessage& Msg, TSharedPtr<FSoundDashboardEntry>& OutReturnedSoundEntry);`
- L44 _private prototype_ `void GetActiveSoundEntryFromIDs(const uint32 PlayOrderID, TSharedPtr<FSoundDashboardEntry>& OutSoundEntry);`
- L45 _private prototype_ `void RemoveActiveSoundEntry(TSharedPtr<FSoundDashboardEntry> OutEntry);`
- L47 _private prototype_ `void UpdateAggregateActiveSoundData();`
- L48 _private prototype_ `void CollectAggregateData(FSoundDashboardEntry& ActiveSoundEntry);`
- L50 _private prototype_ `virtual void OnTimingViewTimeMarkerChanged(double TimeMarker) override;`
- L51 _private prototype_ `virtual void OnTimeControlMethodReset() override;`
- L53 _private prototype_ `void CollectParamsForTimestamp(const FAudioInsightsCacheManager& CacheManager, const double TimeMarker);`
- L55 _private prototype_ `void CacheIsPlottingFlagRecursive(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry);`
- L56 _private prototype_ `void CachePinnedFlagRecursive(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry);`
- L57 _private prototype_ `void ResetDataBuffersRecursive(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry);`
- L59 _private prototype_ `void RestoreCachedStateForEntry(FSoundDashboardEntry& OutEntry);`
- L61 _private member_ `FSoundMessages TraceMessages;`
- L75 _private member_ `TMap<uint32, SoundEntryKeys> ActiveSoundToEntryKeysMap;`
- L76 _private member_ `TArray<SoundMessageIDs> EntriesTimingOut;`
- L77 _private member_ `TSet<uint32> SoundsStoppedBeforeStart;`
- L78 _private member_ `TSet<uint64> PlottingSoundEntries;`
- L79 _private member_ `TMap<uint64, FLinearColor> PlottingEntryColors;`
- L80 _private member_ `TSet<uint64> PinnedSoundEntries;`
- L82 _private member_ `double DashboardTimeoutTime = 3.0;`
- L85 _private member_ `FDelegateHandle OnReadSettingsHandle;`

#### struct `UE::Audio::Insights::FSoundTraceProvider::SoundEntryKeys`  
`struct SoundEntryKeys`  
_L63-67_
- L65 _public member_ `const ESoundDashboardEntryType EntryType;`
- L66 _public member_ `const ::Audio::FDeviceId DeviceId;`

#### struct `UE::Audio::Insights::FSoundTraceProvider::SoundMessageIDs`  
`struct SoundMessageIDs`  
_L69-73_
- L71 _public member_ `const ::Audio::FDeviceId DeviceId;`
- L72 _public member_ `const uint32 ActiveSoundPlayOrder;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnProcessPlotData);`

### `Plugins/AudioInsights/Source/AudioInsights/Private/Providers/SubmixTraceProvider.h` (Private)


#### class `UE::Audio::Insights::FSubmixTraceProvider`  
`class FSubmixTraceProvider : public TDeviceDataMapTraceProvider<uint32, TSharedPtr<FSubmixDashboardEntry>>, public TSharedFromThis<FSubmixTraceProvider>`  
_L16-60_
- inherits: `TDeviceDataMapTraceProvider<uint32,TSharedPtr<FSubmixDashboardEntry>>,TSharedFromThis<FSubmixTraceProvider>`
- L19 _public prototype_ `FSubmixTraceProvider();`
- L20 _public prototype_ `virtual ~FSubmixTraceProvider();`
- L22 _public prototype_ `static FName GetName_Static();`
- L24 _public prototype_ `virtual UE::Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) override;`
- L25 _public prototype_ `void RequestEntriesUpdate();`
- L27 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSubmixChanged, const uint32 );`
- L28 _public member_ `FOnSubmixChanged OnSubmixAdded;`
- L29 _public member_ `FOnSubmixChanged OnSubmixRemoved;`
- L30 _public member_ `FOnSubmixChanged OnSubmixLoaded;`
- L32 _public prototype_ `DECLARE_DELEGATE(FOnSubmixListUpdated);`
- L33 _public member_ `FOnSubmixListUpdated OnSubmixListUpdated;`
- L35 _public prototype_ `DECLARE_DELEGATE(FOnTimeMarkerUpdated);`
- L36 _public member_ `FOnTimeMarkerUpdated OnTimeMarkerUpdated;`
- L39 _protected prototype_ `virtual void OnTraceChannelsEnabled() override;`
- L42 _private prototype_ `virtual bool ProcessMessages() override;`
- L45 _private prototype_ `virtual void OnTimeControlMethodReset() override;`
- L47 _private prototype_ `void HandleOnSubmixAssetAdded(const FString& InAssetPath);`
- L48 _private prototype_ `void HandleOnSubmixAssetRemoved(const FString& InAssetPath);`
- L49 _private prototype_ `void HandleOnSubmixAssetListUpdated(const TArray<FString>& InAssetPaths);`
- L52 _private prototype_ `virtual void OnTimingViewTimeMarkerChanged(double TimeMarker) override;`
- L54 _private member_ `FSubmixMessages TraceMessages;`
- L57 _private member_ `TAssetProvider<USoundSubmix> SubmixAssetProvider;`
- L58 _private member_ `bool bAssetsUpdated = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Audio` (scope `UE`)
- L14 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSubmixChanged, const uint32 );`
- L32 _delegate_ `DECLARE_DELEGATE(FOnSubmixListUpdated);`
- L35 _delegate_ `DECLARE_DELEGATE(FOnTimeMarkerUpdated);`

### `Plugins/AudioInsights/Source/AudioInsights/Private/Providers/VirtualLoopTraceProvider.h` (Private)


#### class `UE::Audio::Insights::FVirtualLoopTraceProvider`  
`class FVirtualLoopTraceProvider : public TDeviceDataMapTraceProvider<uint32, TSharedPtr<FVirtualLoopDashboardEntry>> , public TSharedFromThis<FVirtualLoopTraceProvider>`  
_L10-33_
- inherits: `TDeviceDataMapTraceProvider<uint32,TSharedPtr<FVirtualLoopDashboardEntry>>,TSharedFromThis<FVirtualLoopTraceProvider>`
- L15 _public function_ `FVirtualLoopTraceProvider() : TDeviceDataMapTraceProvider<uint32, TSharedPtr<FVirtualLoopDashboardEntry>>(GetName_Static())`
- L21 _public prototype_ `virtual ~FVirtualLoopTraceProvider() = default;`
- L22 _public prototype_ `virtual UE::Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) override;`
- L24 _public prototype_ `static FName GetName_Static();`
- L27 _private prototype_ `virtual void OnTimingViewTimeMarkerChanged(double TimeMarker) override;`
- L28 _private prototype_ `void CollectParamsForTimestamp(const double InTimeMarker);`
- L30 _private prototype_ `virtual bool ProcessMessages() override;`
- L32 _private member_ `FVirtualLoopMessages TraceMessages;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Audio` (scope `UE`)
- L8 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/SignalFlowEditorCommands.h` (Private)


#### class `UE::Audio::Insights::FSignalFlowEditorCommands`  
`class FSignalFlowEditorCommands : public TCommands<FSignalFlowEditorCommands>`  
_L11-44_
- inherits: `TCommands<FSignalFlowEditorCommands>`
- L14 _public prototype_ `FSignalFlowEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L19 _public function_ `TSharedPtr<const FUICommandInfo> GetToggleHorizontalViewCommand() const` — Toggles
- L20 _public function_ `TSharedPtr<const FUICommandInfo> GetJustifyEdgeCommand() const`
- L21 _public function_ `TSharedPtr<const FUICommandInfo> GetJustifyCenterCommand() const`
- L22 _public function_ `TSharedPtr<const FUICommandInfo> GetShowNodeDetailsCommand() const`
- L23 _public function_ `TSharedPtr<const FUICommandInfo> GetPauseOnSelectCommand() const`
- L24 _public function_ `TSharedPtr<const FUICommandInfo> GetToggleAnimateWiresCommand() const`
- L27 _public function_ `TSharedPtr<const FUICommandInfo> GetCenterViewCommand() const` — Actions
- L28 _public function_ `TSharedPtr<const FUICommandInfo> GetResetTimestampPauseCommand() const`
- L32 _private member_ `TSharedPtr<FUICommandInfo> ToggleHorizontalView;` — Toggles
- L34 _private member_ `TSharedPtr<FUICommandInfo> JustifyEdge;`
- L35 _private member_ `TSharedPtr<FUICommandInfo> JustifyCenter;`
- L37 _private member_ `TSharedPtr<FUICommandInfo> ShowNodeDetails;`
- L38 _private member_ `TSharedPtr<FUICommandInfo> PauseOnSelect;`
- L39 _private member_ `TSharedPtr<FUICommandInfo> ToggleAnimateWires;`
- L42 _private member_ `TSharedPtr<FUICommandInfo> CenterView;` — Actions
- L43 _private member_ `TSharedPtr<FUICommandInfo> ResetTimestampPause;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/SoundDashboardCommands.h` (Private)


#### class `UE::Audio::Insights::FSoundDashboardCommands`  
`class FSoundDashboardCommands : public TCommands<FSoundDashboardCommands>`  
_L11-40_
- inherits: `TCommands<FSoundDashboardCommands>`
- L14 _public prototype_ `FSoundDashboardCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public function_ `TSharedPtr<const FUICommandInfo> GetPinCommand() const`
- L19 _public function_ `TSharedPtr<const FUICommandInfo> GetUnpinCommand() const`
- L20 _public function_ `TSharedPtr<const FUICommandInfo> GetBrowseCommand() const`
- L21 _public function_ `TSharedPtr<const FUICommandInfo> GetEditCommand() const`
- L22 _public function_ `TSharedPtr<const FUICommandInfo> GetViewFullTreeCommand() const`
- L23 _public function_ `TSharedPtr<const FUICommandInfo> GetViewActiveSoundsCommand() const`
- L24 _public function_ `TSharedPtr<const FUICommandInfo> GetViewFlatList() const`
- L25 _public function_ `TSharedPtr<const FUICommandInfo> GetAutoExpandCategoriesCommand() const`
- L26 _public function_ `TSharedPtr<const FUICommandInfo> GetAutoExpandEverythingCommand() const`
- L27 _public function_ `TSharedPtr<const FUICommandInfo> GetAutoExpandNothingCommand() const`
- L30 _private member_ `TSharedPtr<FUICommandInfo> Pin;`
- L31 _private member_ `TSharedPtr<FUICommandInfo> Unpin;`
- L32 _private member_ `TSharedPtr<FUICommandInfo> Browse;`
- L33 _private member_ `TSharedPtr<FUICommandInfo> Edit;`
- L34 _private member_ `TSharedPtr<FUICommandInfo> ViewFullTree;`
- L35 _private member_ `TSharedPtr<FUICommandInfo> ViewActiveSounds;`
- L36 _private member_ `TSharedPtr<FUICommandInfo> ViewFlatList;`
- L37 _private member_ `TSharedPtr<FUICommandInfo> AutoExpandCategories;`
- L38 _private member_ `TSharedPtr<FUICommandInfo> AutoExpandEverything;`
- L39 _private member_ `TSharedPtr<FUICommandInfo> AutoExpandNothing;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/SoundPlotsWidgetCommands.h` (Private)


#### class `UE::Audio::Insights::FSoundPlotsWidgetCommands`  
`class FSoundPlotsWidgetCommands : public TCommands<FSoundPlotsWidgetCommands>`  
_L11-22_
- inherits: `TCommands<FSoundPlotsWidgetCommands>`
- L14 _public prototype_ `FSoundPlotsWidgetCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public function_ `TSharedPtr<const FUICommandInfo> GetResetInspectTimestampCommand() const`
- L21 _private member_ `TSharedPtr<FUICommandInfo> ResetInspectTimestampPlots;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Private/Views/SSignalFlowGraphStyle.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Audio` (scope `UE`)
- L16 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L20 _namespace_ `namespace SSignalFlowGraphStyle` (scope `UE::Audio::Insights`)
- L22 _prototype_ `const FSlateRoundedBoxBrush& GetNodeRoundedBoxBrush();` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L23 _prototype_ `float GetNodeMaxHeight(const int32 NumParamsVisible, const bool bShowNodeDetails, const float ZoomScaleFactor);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L24 _prototype_ `float NormalizedToNodePadding(const float NormalizedValue);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L25 _prototype_ `float NodePaddingToNormalized(const float PixelPadding);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L26 _prototype_ `FSlateColor GetNodeAccentColor(const ESignalFlowEntryType NodeType);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L27 _prototype_ `FLinearColor GetConnectionColor(const ESignalFlowEntryType ReceiverEntryType, const float AmplitudeValue, const float WireSplineAmplitudePowerFactor, const bool bIsSourceBusConnection, const bool bIsSendLabelHovered = false);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L28 _prototype_ `FVector2d GetSplineStartDirection(const EOrientation Orientation, const bool bIsSourceBusConnection, const float ZoomScaleFactor);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L29 _prototype_ `FVector2d GetSplineEndDirection(const EOrientation Orientation, const bool bIsSourceBusConnection, const float ZoomScaleFactor);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L30 _prototype_ `TOptional<float> GetNodeDetailParamValue(const TSharedPtr<FSignalFlowDashboardEntry>& Entry, const ESignalFlowNodeDetailParam ParamType);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L31 _prototype_ `TOptional<FString> GetNodeDetailParamStringValue(const TSharedPtr<FSignalFlowDashboardEntry>& Entry, const ESignalFlowNodeDetailParam ParamType);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L32 _prototype_ `FSlateColor GetNodeDetailParamColor(const ESignalFlowNodeDetailParam ParamType);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L33 _prototype_ `FText GetNodeDetailDisplayName(const ESignalFlowNodeDetailParam ParamType);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L34 _prototype_ `const FNumberFormattingOptions* GetNodeDetailNumberFormat(const ESignalFlowNodeDetailParam ParamType);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L36 _variable_ `constexpr float GraphMinPadding = 400.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L37 _variable_ `constexpr float NodeMaxWidth = 256.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L39 _variable_ `constexpr float NodeRoundedBrushRadius = 12.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L41 _variable_ `constexpr float SplineRadiusFlowingForwards = 80.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L42 _variable_ `constexpr float SplineRadiusFlowingBackwards = 600.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L43 _variable_ `constexpr float SplineThicknessScalarMin = 0.5f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L44 _variable_ `constexpr float SplineThicknessDefault = 4.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L45 _variable_ `constexpr float SplineAnimatedWireThickness = 4.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L46 _variable_ `constexpr float SplineThicknessMin = 1.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L47 _variable_ `constexpr float SplineAnimPointsPerUnit = 0.175f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L48 _variable_ `constexpr float BackwardSplineAnimPointsPerUnit = 0.325f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L50 _variable_ `constexpr float SelectedNodeBorderThickness = 3.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L51 _variable_ `constexpr float NodeBorderThickness = 2.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L53 _variable_ `constexpr float NodeFilteredOutByTextDimming = 0.3f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L54 _variable_ `constexpr float NonHighlightedPathAlphaFactor = 0.15f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L55 _variable_ `constexpr float HoveredWireThicknessMultiplier = 2.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L56 _variable_ `constexpr float HoveredWireHeightMultiplier = 1.25f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L57 _variable_ `constexpr float SendLabelHoverRadius = 12.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L59 _variable_ `constexpr float NodeBorderPadding = 12.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L60 _variable_ `constexpr float NodeDetailVerticalPadding = 8.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L61 _variable_ `constexpr float NodeDetailIndentationPadding = 20.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L62 _variable_ `constexpr float LargeBetweenNodesDefaultPadding = 128.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L63 _variable_ `constexpr float SmallBetweenNodesDefaultPadding = 8.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L64 _variable_ `constexpr float MinNodePadding = 0.25f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L65 _variable_ `constexpr float MaxNodePadding = 500.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L67 _variable_ `constexpr float SendLabelVerticalWidth = 20.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L68 _variable_ `constexpr float SendLabelPadding = 8.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L70 _variable_ `constexpr float AnimationSpeed = 15.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L71 _variable_ `constexpr float DefaultZoomScale = 1.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L72 _variable_ `constexpr float ZoomStepFactor = 0.1f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L73 _variable_ `constexpr float MinZoomScale = 0.125f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L74 _variable_ `constexpr float MaxZoomScale = 2.0f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L75 _variable_ `constexpr float ScrollAnimInRangeThreshold = (1.e-2f);` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)
- L77 _variable_ `constexpr float MuteSoloLowerAlpha = 0.6f;` (scope `UE::Audio::Insights::SSignalFlowGraphStyle`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsConstants.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Audio` (scope `UE`)
- L6 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L8 _variable_ `inline const ANSICHAR* AudioLoggerName = "Au` (scope `UE::Audio::Insights`)
- L9 _variable_ `inline const ANSICHAR* TimestampFieldName = "Ti` (scope `UE::Audio::Insights`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsDashboardAssetCommands.h` (Public)


#### class `UE::Audio::Insights::FDashboardAssetCommands`  
`class FDashboardAssetCommands : public TCommands<FDashboardAssetCommands>`  
_L18-48_
- inherits: `TCommands<FDashboardAssetCommands>`
- L21 _public prototype_ `FDashboardAssetCommands();`
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public prototype_ `virtual void AddAssetCommands(FToolBarBuilder& OutToolbarBuilder) const;`
- L27 _public prototype_ `virtual TSharedPtr<const FUICommandInfo> GetBrowserSyncCommand() const;`
- L28 _public prototype_ `virtual TSharedPtr<const FUICommandInfo> GetOpenCommand() const;`
- L29 _public prototype_ `virtual TSharedPtr<const FUICommandInfo> GetSaveCommand() const;`
- L30 _public prototype_ `virtual TSharedPtr<const FUICommandInfo> GetSaveAllCommand() const;`
- L31 _public prototype_ `virtual TSharedPtr<const FUICommandInfo> GetTraceBookmarkCommand() const;`
- L35 _private member_ `TSharedPtr<FUICommandInfo> BrowserSync;` — Selects the sound in the content browser.
- L38 _private member_ `TSharedPtr<FUICommandInfo> Open;` — Opens the sound asset in respective editor(s).
- L41 _private member_ `TSharedPtr<FUICommandInfo> Save;` — Saves the selected asset.
- L44 _private member_ `TSharedPtr<FUICommandInfo> SaveAll;` — Saves all dirty assets.
- L47 _private member_ `TSharedPtr<FUICommandInfo> CreateTraceBookmark;` — Places a bookmark inside a trace file.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Audio` (scope `UE`)
- L11 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Audio` (scope `UE`)
- L16 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsDashboardFactory.h` (Public)


#### class `UE::Audio::Insights::FDashboardFactory`  
`class FDashboardFactory : public IDashboardFactory, public TSharedFromThis<FDashboardFactory>`  
_L15-58_
- inherits: `IDashboardFactory,TSharedFromThis<FDashboardFactory>`
- L18 _public prototype_ `FDashboardFactory() = default;`
- L19 _public prototype_ `virtual ~FDashboardFactory() = default;`
- L21 _public prototype_ `TSharedRef<SDockTab> MakeDockTabWidget(const FSpawnTabArgs& Args);`
- L23 _public prototype_ `static TSharedRef<SWidget> CreateDocumentationButtonWidget();`
- L25 _public prototype_ `virtual void RegisterViewFactory(TSharedRef<IDashboardViewFactory> InFactory) override;`
- L26 _public prototype_ `virtual void UnregisterViewFactory(FName InDashboardName) override;`
- L27 _public prototype_ `virtual ::Audio::FDeviceId GetDeviceId() const override;`
- L30 _private prototype_ `TSharedRef<SWidget> MakeMenuBarWidget();`
- L31 _private prototype_ `TSharedRef<SWidget> MakeMainToolbarWidget();`
- L32 _private prototype_ `TSharedRef<SWidget> MakeCacheSnapshotButtonWidget();`
- L33 _private prototype_ `TSharedRef<SWidget> MakeBookmarkButtonWidget();`
- L35 _private prototype_ `TSharedPtr<FTabManager::FLayout> GetDefaultTabLayout();`
- L37 _private prototype_ `void RegisterTabSpawners();`
- L38 _private prototype_ `void UnregisterTabSpawners();`
- L41 _private prototype_ `TSharedRef<SWidget> MakeEnableTracesOverlay();`
- L42 _private prototype_ `TSharedRef<SWidget> MakeEnableTracesButton();`
- L43 _private prototype_ `FReply ToggleAutoEnableAudioTraces();`
- L45 _private prototype_ `void CreateTraceBookmark();`
- L47 _private member_ `TSharedPtr<FToolbarWidgets> ToolbarWidgets;`
- L49 _private member_ `TSharedPtr<FTabManager> DashboardTabManager;`
- L50 _private member_ `TSharedPtr<FWorkspaceItem> DashboardWorkspace;`
- L51 _private member_ `TSharedPtr<FTabManager::FLayout> TabLayout;`
- L53 _private member_ `static constexpr ::Audio::FDeviceId ActiveDeviceId = 1;` — The default audio device id in standalone
- L55 _private member_ `int32 BookmarkIndex = 0;`
- L57 _private member_ `TMap<FName, TSharedPtr<IDashboardViewFactory>> DashboardViewFactories;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Audio` (scope `UE`)
- L13 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsDataSource.h` (Public)


#### class `UE::Audio::Insights::IDashboardDataViewEntry`  
`class IDashboardDataViewEntry : public TSharedFromThis<IDashboardDataViewEntry>`  
_L11-17_
- inherits: `TSharedFromThis<IDashboardDataViewEntry>`
- L14 _public prototype_ `virtual ~IDashboardDataViewEntry() = default;`
- L16 _public prototype_ `virtual bool IsValid() const = 0;`

#### class `UE::Audio::Insights::IDashboardDataTreeViewEntry`  
`class IDashboardDataTreeViewEntry : public TSharedFromThis<IDashboardDataTreeViewEntry>`  
_L25-40_
- inherits: `TSharedFromThis<IDashboardDataTreeViewEntry>`
- L28 _public prototype_ `virtual ~IDashboardDataTreeViewEntry() = default;`
- L30 _public prototype_ `virtual bool IsValid() const = 0;`
- L31 _public prototype_ `virtual uint64 GetEntryID() const = 0;`
- L32 _public prototype_ `virtual const FText& GetDisplayName() const = 0;`
- L33 _public prototype_ `virtual const FLinearColor& GetEntryColor() const = 0;`
- L34 _public prototype_ `virtual void SetEntryColor(const FLinearColor& Color) = 0;`
- L35 _public prototype_ `virtual bool HasSetInitExpansion() const = 0;`
- L36 _public prototype_ `virtual void ResetHasSetInitExpansion() = 0;`
- L38 _public member_ `TArray<TSharedPtr<IDashboardDataTreeViewEntry>> Children;`
- L39 _public member_ `bool bIsExpanded = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Audio` (scope `UE`)
- L7 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L9 _typedef_ `using FDataPoint = TPair<double, float>;` (scope `UE::Audio::Insights`) — (Timestamp, Value)
- L20 _function_ `template <typename T> const T& CastEntry(const IDashboardDataViewEntry& InData)` (scope `UE::Audio::Insights`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsDetailsSelectionManager.h` (Public)


#### class `UE::Audio::Insights::FAudioInsightsDetailsSelectionManager`  
`class FAudioInsightsDetailsSelectionManager`  
_L14-27_
- L17 _public prototype_ `void SetSelectedAsset(TObjectPtr<UObject> InAsset);`
- L18 _public prototype_ `void ClearSelection();`
- L20 _public prototype_ `TWeakObjectPtr<UObject> GetSelectedAsset() const;`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAssetSelectionChanged, TObjectPtr<UObject> );`
- L23 _public member_ `FOnAssetSelectionChanged OnAssetSelectionChanged;`
- L26 _private member_ `TWeakObjectPtr<UObject> SelectedAsset;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Audio` (scope `UE`)
- L12 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAssetSelectionChanged, TObjectPtr<UObject> );`

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioInsights, Log, All);`

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsSettings.h` (Public)


#### class `UAudioInsightsSettings`  
`class UAudioInsightsSettings : public UDeveloperSettings`  
_L14-50_
- reflection: `UCLASS(MinimalAPI, config = AudioInsights)`
- inherits: `UDeveloperSettings`
- L21 _public member_ `FCacheSettings CacheSettings;` — `UPROPERTY(EditAnywhere, config, Category = Cache, meta = (ShowOnlyInnerProperties))` — Settings for the Cache
- L25 _public member_ `FLoudnessMeterSettings OutputMeterSettings;` — `UPROPERTY(config)` — Settings for the Output Meters (only visible via settings cog)
- L29 _public member_ `FOutputMeterDashboardSettings OutputMeterDashboardSettings;` — `UPROPERTY(config)` — Settings for the Output Meter dashboard tab (not visible to the user)
- L31 _public prototype_ `static FString GetAudioInsightsConfigFilename();`
- L34 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public prototype_ `void SaveCacheSettings();`
- L41 _private function_ `FName GetContainerName() const override`
- L42 _private function_ `FName GetCategoryName() const override`
- L43 _private function_ `FName GetSectionName() const override`
- L46 _private prototype_ `FText GetSectionText() const override;`
- L49 _private prototype_ `void SavePropertyToConfigFile(const FProperty* const PropertyToSave);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOINSIGHTS_API`

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsStyle.h` (Public)


#### class `UE::Audio::Insights::FSlateStyle`  
`class FSlateStyle final : public FSlateStyleSet`  
_L18-359_
- inherits: `FSlateStyleSet`
- L21 _public prototype_ `static FSlateStyle& Get();`
- L23 _public function_ `static FName GetStyleName()`
- L29 _public function_ `const FNumberFormattingOptions* GetAmpFloatFormat() const`
- L39 _public function_ `const FNumberFormattingOptions* GetLinearAmplitudeFloatFormat() const`
- L49 _public function_ `const FNumberFormattingOptions* GetLinearVolumeFloatFormat() const`
- L59 _public function_ `const FNumberFormattingOptions* GetDefaultFloatFormat() const`
- L68 _public function_ `const FNumberFormattingOptions* GetDistanceFloatFormat() const`
- L77 _public function_ `const FNumberFormattingOptions* GetFreqFloatFormat() const`
- L87 _public function_ `const FNumberFormattingOptions* GetPitchFloatFormat() const`
- L97 _public function_ `const FNumberFormattingOptions* GetTimeFormat() const`
- L106 _public function_ `const FNumberFormattingOptions* GetShortTimeFormat() const`
- L115 _public function_ `const FNumberFormattingOptions* GetRelativeRenderCostFormat() const`
- L125 _public function_ `const FNumberFormattingOptions* GetMemoryFormat() const`
- L134 _public function_ `const FNumberFormattingOptions* GetSendLevelFormat() const`
- L143 _public function_ `FText FormatSecondsAsTime(float InTimeSec) const`
- L148 _public prototype_ `FText FormatTimestamp(const double InSeconds) const;`
- L150 _public function_ `FText FormatMillisecondsAsTime(float InTimeMS) const`
- L155 _public function_ `FText FormatMemoryAsMegabytes(const float InMemoryMB) const`
- L160 _public function_ `float GetSearchBoxMaxHeight() const`
- L165 _public function_ `FSlateIcon CreateIcon(FName InName) const`
- L170 _public function_ `const FSlateBrush& GetBrushEnsured(FName InName) const`
- L190 _public prototype_ `TSharedRef<SBox> CreateButtonContentWidget(const FName& IconName = FName(), const FText& Label = FText::GetEmpty(), const FName& TextStyle = TEXT("ButtonText"), const float HeightOverride = 16.`
- L191 _public prototype_ `TSharedRef<SBox> CreateToggleButtonContent(const FName& IconName, const FName& TextStyle, TFunction<FSlateColor()> ColorFunction, TFunction<FText()> TextFunction, const float HeightOverride = 16.0f) const;`
- L193 _public function_ `FSlateStyle() : FSlateStyleSet(GetStyleName())`
- L355 _public function_ `~FSlateStyle()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "AudioInsights"`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Audio` (scope `UE`)
- L16 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsTimingViewExtender.h` (Public)


#### enum `UE::Audio::Insights::ECacheAndProcess`  
`enum class ECacheAndProcess`  
_L27-32_
- desc: How the cache manage handles new incoming messages Cache - will save the incoming message inside the cache to be retrievable later Process - sends the message to the Audio Insights providers to be processed and displayed in the UI
- L29 _public enumerator_ `Latest = 0` — Cache and process all new messages
- L30 _public enumerator_ `CacheLatestNoProcess` — Cache new messages but do not process them
- L31 _public enumerator_ `None` — Do not cache or process any new messages

#### enum `UE::Audio::Insights::ESystemControllingTimeMarker`  
`enum class ESystemControllingTimeMarker`  
_L34-40_
- L36 _public enumerator_ `EventLog = 0`
- L37 _public enumerator_ `PlotsWidget`
- L38 _public enumerator_ `SignalFlow`
- L39 _public enumerator_ `External`

#### class `UE::Audio::Insights::FAudioInsightsTimingViewExtender`  
`class FAudioInsightsTimingViewExtender final : public UE::Insights::Timing::ITimingViewExtender`  
_L42-101_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- L47 _public function_ `ECacheAndProcess GetMessageCacheAndProcessingStatus() const` — AudioInsights API:
- L48 _public function_ `TOptional<ESystemControllingTimeMarker> TryGetSystemControllingTimeMarker() const`
- L50 _public prototype_ `double GetCurrentTraceDurationSeconds() const;`
- L52 _public prototype_ `void PauseTimeMarker(const double InTimestamp, const ESystemControllingTimeMarker InControllingSystem, TOptional<TRange<double>> InPlottingRange = TOptional<TRange<double>>());`
- L53 _public prototype_ `void ResumeTimeMarker();`
- L55 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimingViewTimeMarkerChanged, double );`
- L56 _public member_ `FOnTimingViewTimeMarkerChanged OnTimingViewTimeMarkerChanged;`
- L58 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTimeControlMethodReset);`
- L59 _public member_ `FOnTimeControlMethodReset OnTimeControlMethodReset;`
- L62 _public member_ `static constexpr double MaxPlottingHistorySeconds = 5.0;` — Move to AudioInsightsConstants
- L63 _public member_ `static constexpr double PlottingMarginSeconds = 0.2;`
- L66 _public prototype_ `void StopProcessingNewMessages();` — AudioInsights Internal:
- L67 _public prototype_ `void StopCachingAndProcessingNewMessages();`
- L68 _public prototype_ `TRange<double> GetPlottingRange() const;`
- L70 _public prototype_ `void BindToTraceModule(FTraceModule& InTraceModule);`
- L71 _public prototype_ `void UnbindFromTraceModule(FTraceModule& InTraceModule);`
- L73 _public prototype_ `void BindToCacheManager(FAudioInsightsCacheManager& InCacheManager);`
- L74 _public prototype_ `void UnbindFromCacheManager(FAudioInsightsCacheManager& InCacheManager);`
- L78 _private prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;` — Insights::ITimingViewExtender interface
- L79 _private prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L80 _private prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L82 _private prototype_ `void OnTimeMarkerChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double InTimeMarker);`
- L83 _private prototype_ `void OnAnalysisStarting(const double Timestamp);`
- L85 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L86 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingView = nullptr;`
- L88 _private prototype_ `void SetPausedTimeMarker(const double InTimeMarker);`
- L89 _private prototype_ `void ApplyStopCacheWhenPausedBehaviour();`
- L90 _private prototype_ `void OnCacheChunkOverwritten(const double NewCacheStartTimestamp);`
- L92 _private member_ `ECacheAndProcess CacheAndProcessMessageStatus = ECacheAndProcess::Latest;`
- L93 _private member_ `TOptional<ESystemControllingTimeMarker> SystemControllingTime;`
- L94 _private member_ `TRange<double> PlottingRange { 0.0, MaxPlottingHistorySeconds };`
- L95 _private member_ `double TraceDurationSeconds = 0.0;`
- L96 _private member_ `double PausedTimeMarker = 0.0;`
- L97 _private member_ `bool bUserInputDetected = false;`
- L99 _private member_ `FDelegateHandle OnAnalysisStartingHandle;`
- L100 _private member_ `FDelegateHandle OnCacheChunkOverwrittenHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L11 _namespace_ `namespace Insights`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Audio` (scope `UE`)
- L19 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimingViewTimeMarkerChanged, double );`
- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTimeControlMethodReset);`

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsToolbarWidgets.h` (Public)


#### class `UE::Audio::Insights::FToolbarWidgets`  
`class FToolbarWidgets final`  
_L14-55_
- L17 _public prototype_ `FToolbarWidgets();`
- L18 _public prototype_ `~FToolbarWidgets();`
- L20 _public prototype_ `TSharedRef<SWidget> MakeCacheLabelWidget();`
- L21 _public prototype_ `TSharedRef<SWidget> MakeCachePauseButtonWidget();`
- L22 _public prototype_ `TSharedRef<SWidget> MakeCacheStopButtonWidget();`
- L23 _public prototype_ `TSharedRef<SWidget> MakeCacheResumeButtonWidget();`
- L24 _public prototype_ `TSharedRef<SWidget> MakeCacheFollowButtonWidget();`
- L25 _public prototype_ `TSharedRef<SWidget> MakeCacheCurrentTimestampWidget();`
- L26 _public prototype_ `TSharedRef<SWidget> MakeCacheBeginTimestampWidget();`
- L27 _public prototype_ `TSharedRef<SWidget> MakeCacheEndTimestampWidget();`
- L28 _public prototype_ `TSharedRef<SWidget> MakeCacheSizeAndDurationWidget();`
- L29 _public prototype_ `TSharedRef<SWidget> MakeCacheNudgeBackButtonWidget();`
- L30 _public prototype_ `TSharedRef<SWidget> MakeCacheTimelineRulerWidget();`
- L31 _public prototype_ `TSharedRef<SWidget> MakeCacheNudgeForwardButtonWidget();`
- L32 _public prototype_ `TSharedRef<SWidget> MakeCacheSettingsButtonWidget();`
- L35 _private prototype_ `void InitializeDelegates();`
- L36 _private prototype_ `void DeinitializeDelegates();`
- L38 _private prototype_ `TSharedRef<SWidget> MakeCacheSettingsMenuContent();`
- L40 _private prototype_ `double GetCurrentRelativeTime() const;`
- L41 _private prototype_ `void OnAnalysisStarting(const double Timestamp);`
- L42 _private prototype_ `void OnTimingViewTimeMarkerChanged(double InTimeMarker);`
- L43 _private prototype_ `void OnTimeControlMethodReset();`
- L45 _private member_ `bool bIsPaused = false;`
- L46 _private member_ `bool bTimelineAutoScroll = true;`
- L47 _private member_ `bool bTimelineViewRangeSetByUser = false;`
- L48 _private member_ `double BeginTimestamp = 0.0;`
- L49 _private member_ `double PausedTimeMarker = 0.0;`
- L50 _private member_ `TRange<double> TimelineViewRange = TRange<double>(0.0, 10.0);`
- L52 _private member_ `FDelegateHandle OnAnalysisStartingHandle;`
- L53 _private member_ `FDelegateHandle OnTimingViewTimeMarkerChangedHandle;`
- L54 _private member_ `FDelegateHandle OnTimeControlMethodResetHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Audio` (scope `UE`)
- L12 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsTraceModule.h` (Public)


#### enum `UE::Audio::Insights::ETraceMode`  
`enum class ETraceMode : uint8`  
_L19-24_
- L21 _public enumerator_ `Monitoring = 0`
- L22 _public enumerator_ `Recording`
- L23 _public enumerator_ `None`

#### class `UE::Audio::Insights::FRewindDebuggerAudioInsightsRuntime`  
`class FRewindDebuggerAudioInsightsRuntime : public IRewindDebuggerRuntimeExtension`  
_L26-30_
- inherits: `IRewindDebuggerRuntimeExtension`
- L29 _public prototype_ `virtual void RecordingStarted() override;`

#### class `UE::Audio::Insights::FTraceModule`  
`class FTraceModule : public IAudioInsightsTraceModule`  
_L32-120_
- inherits: `IAudioInsightsTraceModule`
- L35 _public prototype_ `FTraceModule();`
- L36 _public prototype_ `virtual ~FTraceModule();`
- L39 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L40 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L41 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L42 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L43 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L47 _public function_ `template <typename TraceProviderType> TSharedPtr<TraceProviderType> FindAudioTraceProvider() const`
- L52 _public prototype_ `virtual void AddTraceProvider(TSharedPtr<FTraceProviderBase> TraceProvider) override;`
- L54 _public prototype_ `virtual void StartTraceAnalysis(const bool bInOnlyTraceAudioChannels, const ETraceMode InTraceMode) override;`
- L55 _public prototype_ `virtual bool IsTraceAnalysisActive() const override;`
- L56 _public prototype_ `virtual void StopTraceAnalysis() override;`
- L57 _public prototype_ `virtual void OnOnlyTraceAudioChannelsStateChanged(const bool bOnlyTraceAudioChannels) override;`
- L59 _public prototype_ `virtual bool AudioChannelsCanBeManuallyEnabled() const override;`
- L61 _public prototype_ `virtual void ExecuteConsoleCommand(const FString& InCommandStr) const override;`
- L63 _public prototype_ `virtual void SaveCacheSnapshot() override;`
- L65 _public prototype_ `virtual ETraceMode GetTraceMode() const override;`
- L68 _public prototype_ `virtual void InitializeSessionInfo(const TraceServices::FSessionInfo& SessionInfo) override;`
- L69 _public prototype_ `virtual void RequestChannelUpdate() override;`
- L70 _public prototype_ `virtual void ResetTicker() override;`
- L71 _public prototype_ `virtual bool TraceControllerIsAvailable() const override;`
- L73 _public function_ `virtual bool IsAudioInsightsTrace() const override`
- L76 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnalysisStarting, const double );`
- L77 _public member_ `FOnAnalysisStarting OnAnalysisStarting;`
- L80 _private prototype_ `static const FName GetName();`
- L82 _private prototype_ `static void DisableAllTraceChannels();`
- L83 _private prototype_ `bool EnableAudioInsightsTraceChannels();`
- L85 _private prototype_ `void DisableAudioInsightsTraceChannels() const;`
- L87 _private prototype_ `void CacheCurrentlyEnabledTraceChannels();`
- L88 _private prototype_ `void RestoreCachedChannels() const;`
- L91 _private prototype_ `bool IsSessionInfoAvailable() const;`
- L92 _private prototype_ `bool GetAudioTracesAreEnabled() const;`
- L93 _private prototype_ `void SendDiscoveryRequestToTraceController() const;`
- L94 _private prototype_ `void OnSessionsUpdated();`
- L96 _private prototype_ `bool Tick(float DeltaTime);`
- L98 _private prototype_ `void OnTraceStopped(FTraceAuxiliary::EConnectionType InTraceType, const FString& InTraceDestination);`
- L101 _private member_ `TMap<FName, TSharedPtr<FTraceProviderBase>> TraceProviders;`
- L102 _private member_ `TArray<FString> ChannelsToRestore;`
- L103 _private member_ `FRewindDebuggerAudioInsightsRuntime RewindDebugger;`
- L105 _private member_ `ETraceMode CurrentTraceMode = ETraceMode::None;`
- L107 _private member_ `bool bTraceAnalysisHasStarted = false;`
- L108 _private member_ `bool bAudioTraceChannelsEnabled = false;`
- L109 _private member_ `bool bIsAudioInsightsTrace = false;`
- L112 _private member_ `FGuid InstanceID;`
- L114 _private member_ `FTickerDelegate OnTick;`
- L115 _private member_ `FTSTicker::FDelegateHandle OnTickHandle;`
- L117 _private member_ `const TArray<FString> AudioChannels;`
- L118 _private member_ `const TArray<FString> EmptyArray;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnalysisStarting, const double );`

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsTraceProviderBase.h` (Public)


#### class `UE::Audio::Insights::FTraceProviderBase`  
`class FTraceProviderBase : public TraceServices::IProvider, public TraceServices::IEditableProvider`  
_L27-191_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- L30 _public prototype_ `FTraceProviderBase() = delete;`
- L31 _public prototype_ `explicit FTraceProviderBase(FName InName);`
- L33 _public prototype_ `virtual ~FTraceProviderBase();`
- L35 _public prototype_ `virtual Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) = 0;`
- L36 _public prototype_ `FName GetName() const;`
- L38 _public function_ `virtual void Reset()`
- L44 _public function_ `virtual void OnTraceChannelsEnabled()`
- L50 _public function_ `virtual bool ProcessMessages()`
- L56 _public function_ `virtual bool ProcessManuallyUpdatedEntries()`
- L61 _public function_ `uint64 GetLastUpdateId() const`
- L66 _public function_ `bool IsUpdated() const`
- L71 _public function_ `bool ShouldForceUpdate() const`
- L76 _public function_ `void ResetShouldForceUpdate()`
- L82 _public function_ `virtual void InitSessionCachedMessages(TraceServices::IAnalysisSession& InSession)`
- L85 _public function_ `virtual void OnTimingViewTimeMarkerChanged(double TimeMarker)`
- L86 _public function_ `virtual void OnTimeControlMethodReset()`
- L88 _public prototype_ `ECacheAndProcess GetMessageCacheAndProcessingStatus() const;`
- L89 _public prototype_ `void ResetMessageProcessType();`
- L176 _protected function_ `uint64 GetLastMessageId() const`
- L181 _protected prototype_ `virtual bool IsMessageProcessingPaused() const;`
- L183 _protected member_ `uint64 LastUpdateId = 0;`
- L184 _protected member_ `bool bForceUpdate = false;`
- L187 _private member_ `std::atomic<uint64> LastMessageId { 0 };`
- L188 _private member_ `FName Name;`

#### class `UE::Audio::Insights::FTraceProviderBase::FTraceAnalyzerBase`  
`class FTraceAnalyzerBase : public Trace::IAnalyzer`  
_L92-174_
- inherits: `Trace::IAnalyzer`
- L95 _public prototype_ `FTraceAnalyzerBase(TSharedRef<FTraceProviderBase> InProvider);`
- L96 _public prototype_ `virtual ~FTraceAnalyzerBase() = default;`
- L98 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L101 _protected prototype_ `virtual bool OnEventSuccess(uint16 RouteId, EStyle Style, const FOnEventContext& Context);`
- L102 _protected prototype_ `virtual bool OnEventFailure(uint16 RouteId, EStyle Style, const FOnEventContext& Context);`
- L105 _protected prototype_ `virtual bool OnHandleEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) = 0;` — Override in derived to handle incoming trace messages
- L107 _protected prototype_ `bool ShouldIgnoreNewEvents() const;`
- L108 _protected prototype_ `virtual bool ShouldProcessNewEvents() const;`
- L111 _protected function_ `template <typename TProviderType> TProviderType& GetProvider()`
- L117 _protected function_ `template <typename TProviderType> const TProviderType& GetProvider() const`
- L124 _protected function_ `template <TIsCacheableMessage T> void CacheMessage(const FOnEventContext& Context, TAnalyzerMessageQueue<T>& OutMessageQueue)` — Will cache a message, and add it to the provided OutMessageQueue for processing
- L133 _protected function_ `template <TIsCacheableMessage T> void AddMessageToQueue(const FOnEventContext& Context, TAnalyzerMessageQueue<T>& OutMessageQueue)` — If processing is enabled, will add a message to the provided OutMessageQueue for processing, but will not cache it.
- L142 _private prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L144 _private prototype_ `bool HandleChannelAnnounceEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context);`
- L145 _private prototype_ `bool HandleChannelToggleEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context);`
- L148 _private function_ `template <TIsCacheableMessage T> void AddMessageToCache(TSharedPtr<T>&& Message, TAnalyzerMessageQueue<T>& OutMessageQueue)`
- L159 _private member_ `TSharedRef<FTraceProviderBase> Provider;`
- L167 _private member_ `FAudioInsightsCacheManager& CacheManager;`
- L169 _private member_ `TOptional<uint32> AudioChannelID;`
- L170 _private member_ `TOptional<uint32> AudioMixerChannelID;`
- L172 _private member_ `bool bAudioChannelIsEnabled = false;`
- L173 _private member_ `bool bAudioMixerChannelIsEnabled = false;`

#### enum `UE::Audio::Insights::FTraceProviderBase::FTraceAnalyzerBase::(anonymous)`  
``  
_L162-165_

#### class `UE::Audio::Insights::TDeviceDataMapTraceProvider`  
`template<typename EntryKey, typename EntryType > class TDeviceDataMapTraceProvider : public FTraceProviderBase`  
_L194-438_
- inherits: `FTraceProviderBase`
- L197 _public typedef_ `using KeyType = EntryKey;`
- L198 _public typedef_ `using ValueType = EntryType;`
- L200 _public typedef_ `using FDeviceData = TSortedMap<EntryKey, EntryType>;`
- L201 _public typedef_ `using FEntryPair = TPair<EntryKey, EntryType>;`
- L203 _public function_ `TDeviceDataMapTraceProvider(FName InName) : FTraceProviderBase(InName) #if WITH_EDITOR , bIsTraceActive(FTraceAuxiliary::IsConnected()) #endif`
- L231 _public function_ `virtual ~TDeviceDataMapTraceProvider()`
- L240 _public function_ `const TMap<::Audio::FDeviceId, FDeviceData>& GetDeviceDataMap() const`
- L245 _public function_ `::Audio::FDeviceId GetFilteredAudioDeviceID() const`
- L255 _public function_ `const FDeviceData* FindFilteredDeviceData() const`
- L261 _public function_ `virtual void ClearActiveAudioDeviceEntries()`
- L274 _protected typedef_ `using Super = TDeviceDataMapTraceProvider<EntryKey, EntryType>;`
- L276 _protected member_ `TMap<::Audio::FDeviceId, FDeviceData> DeviceDataMap;`
- L278 _protected function_ `virtual void Reset() override`
- L284 _protected function_ `virtual void OnTraceChannelsEnabled() override`
- L291 _protected function_ `template <typename TMsgType> void ProcessMessageQueue( TAnalyzerMessageQueue<TMsgType>& InQueue, TFunctionRef<EntryType*(const TMsgType&)> GetEntry, TFunctionRef<void(const TMsgType&, EntryType*)> ProcessEntry)`
- L309 _protected function_ `EntryType* FindDeviceEntry(::Audio::FDeviceId InDeviceId, const EntryKey& InKey)`
- L319 _protected function_ `const EntryType* FindDeviceEntry(::Audio::FDeviceId InDeviceId, const EntryKey& InKey) const`
- L329 _protected function_ `FDeviceData* FindFilteredDeviceData()`
- L341 _protected function_ `EntryType& FindOrAddDeviceEntry(::Audio::FDeviceId InDeviceId, const EntryKey& InKey)`
- L348 _protected function_ `bool RemoveDeviceEntry(::Audio::FDeviceId InDeviceId, const EntryKey& InKey)`
- L366 _protected function_ `void UpdateDeviceEntry(::Audio::FDeviceId InDeviceId, const EntryKey& InKey, TFunctionRef<void(EntryType&)> InEntryMutator)`
- L373 _protected function_ `const uint32 GetAudioDeviceIdFromDeviceDataMap() const`
- L393 _private function_ `void RegisterDelegates()`
- L400 _private function_ `void UnregisterDelegates()`
- L407 _private function_ `void OnTraceStarted(FTraceAuxiliary::EConnectionType InTraceType, const FString& InTraceDestination)`
- L412 _private function_ `void OnTraceStopped(FTraceAuxiliary::EConnectionType InTraceType, const FString& InTraceDestination)`
- L417 _private function_ `void OnAudioDeviceCreated(::Audio::FDeviceId InDeviceId)`
- L434 _private member_ `bool bIsTraceActive = false;`
- L437 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Audio` (scope `UE`)
- L23 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L163 _enumerator_ `RouteID_ChannelAnnounce = TNumericLimits<uint16>::Max() - 1u` (scope `UE::Audio::Insights::FTraceProviderBase::FTraceAnalyzerBase::__anonb11c20cf0103`)
- L164 _enumerator_ `RouteID_ChannelToggle = TNumericLimits<uint16>::Max()` (scope `UE::Audio::Insights::FTraceProviderBase::FTraceAnalyzerBase::__anonb11c20cf0103`)
- L210 _function_ `` (scope `UE::Audio::Insights::TDeviceDataMapTraceProvider::TDeviceDataMapTraceProvider`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsUtils.h` (Public)


#### class `UE::Audio::Insights::AudioInsightsUtils`  
`class AudioInsightsUtils`  
_L11-49_
- L14 _public function_ `static FText ConvertToDecibelsText(const float InAmplitude)`
- L29 _public function_ `static FString ResolveObjectDisplayName(const FString& InObjectPath)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Cache/AudioCachedMessageChunk.h` (Public)


#### class `UE::Audio::Insights::FAudioCachedMessageChunk`  
`class FAudioCachedMessageChunk`  
_L13-98_
- L16 _public typedef_ `using TCachePagedArray = TraceServices::TPagedArray<TSharedPtr<class IAudioCachedMessage>>;`
- L18 _public function_ `FAudioCachedMessageChunk(TraceServices::FSlabAllocator& InAllocator, const uint32 InChunkSize) : Allocator(InAllocator) , MaxChunkSize(InChunkSize)`
- L23 _public prototype_ `virtual ~FAudioCachedMessageChunk() = default;`
- L25 _public prototype_ `void AddMessageToChunk(const TSharedPtr<class IAudioCachedMessage> Message);`
- L26 _public prototype_ `void ClearChunk();`
- L28 _public prototype_ `uint32 GetCurrentChunkSize() const;`
- L29 _public prototype_ `bool IsChunkFull() const;`
- L30 _public prototype_ `bool HasAnyData() const;`
- L32 _public prototype_ `const TMap<FName, TSharedPtr<TCachePagedArray>>& GetAllChunkMessages() const;`
- L34 _public prototype_ `bool TimestampIsInChunkRange(const double Timestamp) const;`
- L35 _public prototype_ `double GetChunkTimeRangeStart() const;`
- L36 _public prototype_ `double GetChunkTimeRangeEnd() const;`
- L43 _public function_ `template<TIsCacheableMessage T, typename Predicate> const T* FindClosestMessageByPredicate(const FName& MessageID, const double Timestamp, Predicate Pred) const` — Finds the closest message to a specific timestamp and where predicate returns true. Will iterate backwards from param Timestamp until the first message of type MessageID is found @param Predicate: A callable that returns a BooleanTestable value. E.g. [](const T& InMessage){ return InMessage.GetID() == 10; }
- L76 _public function_ `template<TIsCacheableMessage T> T* FindClosestMessage(const FName& MessageID, const double Timestamp, const uint64 ID = INDEX_NONE) const` — Finds the closest message to a specific timestamp Will iterate backwards from param Timestamp until the first message of type MessageID is found Param ID can be overriden to filter the results further
- L87 _private member_ `static constexpr double INVALID_TIMESTAMP = -1.0;`
- L89 _private member_ `TMap<FName, TSharedPtr<TCachePagedArray>> Messages;`
- L91 _private member_ `double RangeStartTimestamp = INVALID_TIMESTAMP;`
- L92 _private member_ `double RangeEndTimestamp = INVALID_TIMESTAMP;`
- L94 _private member_ `TraceServices::FSlabAllocator& Allocator;`
- L96 _private member_ `uint32 CurrentChunkSize = 0u;`
- L97 _private member_ `const uint32 MaxChunkSize = 0u;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Audio` (scope `UE`)
- L11 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L54 _function_ `` (scope `UE::Audio::Insights::FAudioCachedMessageChunk::FindClosestMessageByPredicate`)
- L81 _function_ `` (scope `UE::Audio::Insights::FAudioCachedMessageChunk::FindClosestMessage`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Cache/AudioInsightsCacheManager.h` (Public)


#### class `UE::Audio::Insights::FAudioInsightsCache`  
`class FAudioInsightsCache`  
_L20-51_
- desc: Helper class that manages the cache container The cache may or may not be limited in size based on the bLimitCacheSize flag - In Editor, the cache size is always limited, behaving like a circular buffer - In Standalone, when connected to a live session (either via direct or live trace), the cache size is limited, behaving like a circular buffer - In Standalone, when loading in a .utrace file, the cache will grow to hold all of the trace file data in memory
- L23 _public prototype_ `FAudioInsightsCache();`
- L24 _public prototype_ `virtual ~FAudioInsightsCache();`
- L26 _public function_ `FAudioCachedMessageChunk& operator[](uint32 Index)`
- L31 _public function_ `const FAudioCachedMessageChunk& operator[](uint32 Index) const`
- L36 _public prototype_ `void ResetCache(TraceServices::FSlabAllocator& Allocator, const uint32 InNumChunks);`
- L37 _public prototype_ `void ReserveNewChunks(TraceServices::FSlabAllocator& Allocator, const uint32 NumToReserve);`
- L39 _public prototype_ `uint32 Capacity() const;`
- L40 _public prototype_ `uint32 GetNextIndex(uint32 ReadIndex) const;`
- L41 _public prototype_ `uint32 GetPreviousIndex(uint32 ReadIndex) const;`
- L45 _private prototype_ `void InitCacheIsLimited();`
- L46 _private prototype_ `void OnSessionChangedEvent();`
- L49 _private member_ `TArray<TUniquePtr<FAudioCachedMessageChunk>> Cache;`
- L50 _private member_ `bool bLimitCacheSize = false;`

#### class `UE::Audio::Insights::FAudioInsightsCacheManager`  
`class FAudioInsightsCacheManager`  
_L53-287_
- L56 _public prototype_ `FAudioInsightsCacheManager();`
- L57 _public prototype_ `virtual ~FAudioInsightsCacheManager();`
- L59 _public prototype_ `void AddMessageToCache(TSharedPtr<IAudioCachedMessage> Message);`
- L60 _public prototype_ `void ClearCache();`
- L62 _public prototype_ `float GetCacheDuration() const;`
- L63 _public prototype_ `double GetCacheStartTimeStamp() const;`
- L64 _public prototype_ `double GetCacheEndTimeStamp() const;`
- L67 _public prototype_ `uint32 GetUsedCacheSize() const;` — Returns the total used memory size of the cache in bytes
- L70 _public prototype_ `uint32 GetMaxCacheSize() const;` — Returns the maximum memory size of the cache in bytes
- L73 _public prototype_ `uint32 GetNumChunks() const;` — Returns the maximum number of chunks inside the cache
- L76 _public prototype_ `uint32 GetNumUsedChunks() const;` — Returns the number of chunks with data present inside the cache
- L80 _public prototype_ `TOptional<uint32> TryGetNumChunksFromStartForTimestamp(const double Timestamp) const;` — Tries to find the number of chunks from the start of the cache for a specific timestamp, where lower indexed chunks contain older messages If the timestamp does not exist within the current cache, the returned result will be unset
- L84 _public prototype_ `const FAudioCachedMessageChunk* const GetChunk(const uint32 NumChunksFromStart) const;` — Returns a chunk by index relative to the start of the cache e.g. NumChunksFromStart = 0u will return the chunk with the earliest messages in the cache
- L87 _public prototype_ `bool IsTimestampMarkedForDeletion(const double Timestamp) const;` — Returns true if the cache is full and the timestamp falls within the oldest chunk (next to be overwritten)
- L91 _public function_ `const TMap<FName, TSharedPtr<const IAudioCachedMessage>>& GetMessageTypeRegistry() const` — Returns one representative message per FName, collected as messages flow into the cache. Used by the cache trace writer to discover and declare events without iterating all chunks.
- L100 _public function_ `template<TIsCacheableMessage T, typename Predicate> const T* FindClosestMessageByPredicate(const FName& MessageID, const double Timestamp, Predicate Pred, const double BackOutTimestamp = -1.0) const` — Find the closest message to a timestamp in the cache for a specific message type and where predicate returns true. Will look backwards from the chosen timestamp until a message is found @param Predicate: A callable that returns a BooleanTestable value. E.g. [](const T& InMessage){ return InMessage.GetID() == 10; } @param BackOutTimestamp: When iterating backwards, if a chunk is detected with an end timestamp less than the backout timestamp, the search is canceled and this returns nullptr
- L157 _public function_ `template<TIsCacheableMessage T> const T* FindClosestMessage(const FName& MessageID, const double Timestamp, const uint64 ID = INDEX_NONE, const double BackOutTimestamp = -1.0) const` — Find the closest message to a timestamp in the cache for a specific message type Will look backwards from the chosen timestamp until a message is found @param ID: When overloaded, the search algorithm will only return messages that have a matching ID. If left at INDEX_NONE, the search algorithm will return the closest message irrespective of ID @param BackOutTimestamp: When iterating backwards, if a chunk is detected with an end timestamp less than the backout timestamp, the search is canceled and this returns nullptr
- L173 _public function_ `template<TIsCacheableMessage T> void IterateOverRange(const FName& MessageID, const double Start, const double End, TFunctionRef<void(const T& Message)> OnMessageFunc, const uint64 ID = INDEX_NONE) const` — Iterates the cache over a chosen timestamp range for a specific message ID Will stop iterating if the end of the cache is reached @param ID: When overloaded, the search algorithm will only return messages that have a matching ID. If left at INDEX_NONE, the search algorithm will return all matching messages irrespective of ID
- L243 _public function_ `template<TIsCacheableMessage T> void IterateTo(const FName& MessageID, const double End, TFunctionRef<void(const T& Message)> OnMessageFunc, const uint64 ID = INDEX_NONE) const` — Iterates over the cache from the start to a chosen timestamp for a specific message ID Will stop iterating if the end of the cache is reached
- L251 _public function_ `template<TIsCacheableMessage T> void IterateFrom(const FName& MessageID, const double Start, TFunctionRef<void(const T& Message)> OnMessageFunc, const uint64 ID = INDEX_NONE) const` — Iterates over the cache from a chosen timestamp to the end of the cache for a specific message ID
- L258 _public function_ `template<TIsCacheableMessage T> void IterateOverAll(const FName& MessageID, TFunctionRef<void(const T& Message)> OnMessageFunc, const uint64 ID = INDEX_NONE) const` — Iterates over the entire cache for a specific message ID
- L264 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnChunkOverwritten, double );`
- L265 _public member_ `FOnChunkOverwritten OnChunkOverwritten;`
- L268 _private prototype_ `void CreateCache();`
- L269 _private prototype_ `void OnCacheSizeSettingsChanged();`
- L271 _private prototype_ `void ProcessPendingMessages(float DeltaTime);`
- L273 _private member_ `TraceServices::FSlabAllocator Allocator;`
- L275 _private member_ `FAudioInsightsCache Cache;`
- L276 _private member_ `TAnalyzerMessageQueue<TSharedPtr<IAudioCachedMessage>> NewMessageQueue;`
- L277 _private member_ `TMap<FName, TSharedPtr<const IAudioCachedMessage>> MessageTypeRegistry;`
- L280 _private member_ `uint32 NumChunks = 0u;` — Number of chunks in the cache. Each chunk is 1 MB, so NumChunks == CacheSizeMB.
- L282 _private member_ `uint32 WriteIndex = 0u;`
- L283 _private member_ `uint32 StartIndex = 0u;`
- L285 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L286 _private member_ `FDelegateHandle CacheSettingsChangedHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Audio` (scope `UE`)
- L13 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L162 _function_ `` (scope `UE::Audio::Insights::FAudioInsightsCacheManager::FindClosestMessage`)
- L264 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnChunkOverwritten, double );`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Cache/IAudioCachedMessage.h` (Public)


#### class `UE::Audio::Insights::IAudioCachedMessage`  
`class IAudioCachedMessage`  
_L10-25_
- L13 _public prototype_ `virtual ~IAudioCachedMessage() = default;`
- L15 _public prototype_ `virtual uint32 GetSizeOf() const = 0;`
- L16 _public prototype_ `virtual uint64 GetID() const = 0;`
- L17 _public prototype_ `virtual const FName GetMessageName() const = 0;`
- L22 _public function_ `virtual FCacheWriteHandler GetCacheWriteHandler() const` — Override to return a declare/write handler pair so this message type is included when exporting the Audio Insights cache to a custom .utrace file. See existing implementations in AudioInsights/Private/Messages/ for examples.
- L24 _public member_ `double Timestamp = 0.0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Audio` (scope `UE`)
- L8 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L31 _prototype_ `&& requires (const UE::Trace::IAnalyzer::FOnEventContext& Context)`

### `Plugins/AudioInsights/Source/AudioInsights/Public/IAudioInsightsDashboardFactory.h` (Public)


#### class `UE::Audio::Insights::IDashboardFactory`  
`class IDashboardFactory`  
_L11-19_
- L14 _public prototype_ `virtual ~IDashboardFactory() = default;`
- L16 _public prototype_ `virtual void RegisterViewFactory(TSharedRef<IDashboardViewFactory> InFactory) = 0;`
- L17 _public prototype_ `virtual void UnregisterViewFactory(FName InDashboardName) = 0;`
- L18 _public prototype_ `virtual ::Audio::FDeviceId GetDeviceId() const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/IAudioInsightsModule.h` (Public)


#### class `IAudioInsightsModule`  
`class IAudioInsightsModule : public IAudioInsightsModuleInterface`  
_L25-55_
- inherits: `IAudioInsightsModuleInterface`
- L28 _public prototype_ `virtual void RegisterDashboardViewFactory(TSharedRef<UE::Audio::Insights::IDashboardViewFactory> InDashboardFactory) = 0;`
- L29 _public prototype_ `virtual void UnregisterDashboardViewFactory(FName InName) = 0;`
- L31 _public prototype_ `virtual ::Audio::FDeviceId GetDeviceId() const = 0;`
- L33 _public prototype_ `virtual IAudioInsightsTraceModule& GetTraceModule() override;`
- L35 _public prototype_ `virtual UE::Audio::Insights::FAudioInsightsCacheManager& GetCacheManager() override;`
- L37 _public prototype_ `virtual UE::Audio::Insights::FAudioInsightsTimingViewExtender& GetTimingViewExtender() override;`
- L40 _public prototype_ `virtual UE::Audio::Insights::FAudioInsightsDetailsSelectionManager& GetDetailsSelectionManager() override;`
- L43 _public prototype_ `virtual TSharedRef<SDockTab> CreateDashboardTabWidget(const FSpawnTabArgs& Args) = 0;`
- L45 _public prototype_ `static bool IsModuleLoaded();`
- L47 _public prototype_ `static bool IsLiveSession();`
- L49 _public prototype_ `static IAudioInsightsModule& GetChecked();`
- L52 _public prototype_ `static IAudioInsightsModule& GetEditorChecked();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Audio` (scope `UE`)
- L16 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/IAudioInsightsModuleInterface.h` (Public)


#### class `IAudioInsightsModuleInterface`  
`class IAudioInsightsModuleInterface : public IModuleInterface`  
_L23-47_
- inherits: `IModuleInterface`
- L26 _public prototype_ `virtual void RegisterDashboardViewFactory(TSharedRef<UE::Audio::Insights::IDashboardViewFactory> InDashboardFactory) = 0;`
- L27 _public prototype_ `virtual void UnregisterDashboardViewFactory(FName InName) = 0;`
- L32 _public prototype_ `virtual void RegisterEventLogCategories(const TMap<FString, TSet<FString>>& InCategoriesToEvents) = 0;` — Allows external plug-ins to batch-define events and categories for the Audio Insights Event Log. Best called from StartupModule. Categories and events are merged across callers; duplicates are skipped. Event names should match the strings you pass to Audio::Trace::EventLog::SendEvent.
- L36 _public prototype_ `virtual void RegisterEventLogDisplayNames(const TMap<FString, FText>& InDisplayNames) = 0;` — Allows external plug-ins to provide localized display names for their custom event types and categories. Maps event/category ID strings to localized FText. Call after RegisterEventLogCategories.
- L38 _public prototype_ `virtual ::Audio::FDeviceId GetDeviceId() const = 0;`
- L40 _public prototype_ `virtual IAudioInsightsTraceModule& GetTraceModule() = 0;`
- L41 _public prototype_ `virtual UE::Audio::Insights::FAudioInsightsCacheManager& GetCacheManager() = 0;`
- L42 _public prototype_ `virtual UE::Audio::Insights::FAudioInsightsTimingViewExtender& GetTimingViewExtender() = 0;`
- L45 _public prototype_ `virtual UE::Audio::Insights::FAudioInsightsDetailsSelectionManager& GetDetailsSelectionManager() = 0;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/IAudioInsightsTraceModule.h` (Public)


#### class `IAudioInsightsTraceModule`  
`class IAudioInsightsTraceModule : public TraceServices::IModule`  
_L18-45_
- inherits: `TraceServices::IModule`
- L21 _public prototype_ `virtual void AddTraceProvider(TSharedPtr<UE::Audio::Insights::FTraceProviderBase> TraceProvider) = 0;`
- L23 _public prototype_ `virtual void StartTraceAnalysis(const bool bInOnlyTraceAudioChannels, const UE::Audio::Insights::ETraceMode InTraceMode) = 0;`
- L24 _public prototype_ `virtual bool IsTraceAnalysisActive() const = 0;`
- L25 _public prototype_ `virtual void StopTraceAnalysis() = 0;`
- L27 _public prototype_ `virtual void OnOnlyTraceAudioChannelsStateChanged(const bool bOnlyTraceAudioChannels) = 0;`
- L29 _public prototype_ `virtual bool AudioChannelsCanBeManuallyEnabled() const = 0;`
- L31 _public prototype_ `virtual void ExecuteConsoleCommand(const FString& InCommandStr) const = 0;`
- L33 _public prototype_ `virtual void SaveCacheSnapshot() = 0;`
- L35 _public prototype_ `virtual UE::Audio::Insights::ETraceMode GetTraceMode() const = 0;`
- L38 _public prototype_ `virtual void InitializeSessionInfo(const TraceServices::FSessionInfo& SessionInfo) = 0;`
- L39 _public prototype_ `virtual void RequestChannelUpdate() = 0;`
- L40 _public prototype_ `virtual void ResetTicker() = 0;`
- L41 _public prototype_ `virtual bool TraceControllerIsAvailable() const = 0;`
- L43 _public prototype_ `virtual bool IsAudioInsightsTrace() const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Audio` (scope `UE`)
- L7 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L13 _namespace_ `namespace TraceServices`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/AnalyzerMessageQueue.h` (Public)


#### struct `UE::Audio::Insights::TAnalyzerMessageQueue`  
`template <typename T> struct TAnalyzerMessageQueue`  
_L12-96_
- L14 _public member_ `static constexpr double MaxHistoryLimitSec = 5.0;`
- L16 _public function_ `explicit TAnalyzerMessageQueue(const double InHistoryLimitSec = 5.0) : HistoryLimitSec(FMath::Clamp(InHistoryLimitSec, UE_DOUBLE_KINDA_SMALL_NUMBER, MaxHistoryLimitSec))`
- L21 _public prototype_ `virtual ~TAnalyzerMessageQueue() = default;`
- L23 _public function_ `bool IsEmpty() const`
- L28 _public function_ `TArray<T> DequeueAll()`
- L48 _public function_ `void Enqueue(T&& InMessage)`
- L93 _protected member_ `double HistoryLimitSec = 0.0;`
- L94 _protected member_ `TMpscQueue<TimestampedMessage> Data;`
- L95 _protected member_ `mutable FCriticalSection AccessCritSec;`

#### struct `UE::Audio::Insights::TAnalyzerMessageQueue::TimestampedMessage`  
`struct TimestampedMessage`  
_L78-90_
- L80 _public prototype_ `TimestampedMessage() = default;`
- L82 _public function_ `TimestampedMessage(T&& InMessage) : Message(MoveTemp(InMessage)) , TimestampWhenCreated(FPlatformTime::Seconds())`
- L88 _public member_ `T Message;`
- L89 _public member_ `double TimestampWhenCreated = 0.0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/AudioBusTraceMessages.h` (Public)


#### enum `UE::Audio::Insights::EAudioBusType`  
`enum class EAudioBusType : uint8`  
_L26-31_
- L28 _public enumerator_ `AssetBased`
- L29 _public enumerator_ `CodeGenerated`
- L30 _public enumerator_ `None`

#### struct `UE::Audio::Insights::FAudioBusMessageBase`  
`struct FAudioBusMessageBase : public IAudioCachedMessage`  
_L33-42_
- inherits: `IAudioCachedMessage`
- L35 _public prototype_ `FAudioBusMessageBase() = default;`
- L36 _public prototype_ `FAudioBusMessageBase(const UE::Trace::IAnalyzer::FOnEventContext& InContext);`
- L38 _public function_ `virtual uint64 GetID() const override`
- L41 _public member_ `uint32 AudioBusId = INDEX_NONE;`

#### struct `UE::Audio::Insights::FAudioBusStartMessage`  
`struct FAudioBusStartMessage : public FAudioBusMessageBase`  
_L44-56_
- inherits: `FAudioBusMessageBase`
- L46 _public prototype_ `FAudioBusStartMessage() = default;`
- L47 _public prototype_ `FAudioBusStartMessage(const UE::Trace::IAnalyzer::FOnEventContext& InContext);`
- L49 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L50 _public function_ `virtual const FName GetMessageName() const override`
- L51 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L53 _public member_ `FString Name;`
- L54 _public member_ `int32 NumChannels = 0;`
- L55 _public member_ `EAudioBusType AudioBusType = EAudioBusType::None;`

#### struct `UE::Audio::Insights::FAudioBusHasActivityMessage`  
`struct FAudioBusHasActivityMessage : public FAudioBusMessageBase`  
_L58-68_
- inherits: `FAudioBusMessageBase`
- L60 _public prototype_ `FAudioBusHasActivityMessage() = default;`
- L61 _public prototype_ `FAudioBusHasActivityMessage(const UE::Trace::IAnalyzer::FOnEventContext& InContext);`
- L63 _public function_ `virtual uint32 GetSizeOf() const override`
- L64 _public function_ `virtual const FName GetMessageName() const override`
- L65 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L67 _public member_ `bool bHasActivity = false;`

#### struct `UE::Audio::Insights::FAudioBusEnvelopeFollowerEnabledMessage`  
`struct FAudioBusEnvelopeFollowerEnabledMessage : public FAudioBusMessageBase`  
_L70-80_
- inherits: `FAudioBusMessageBase`
- L72 _public prototype_ `FAudioBusEnvelopeFollowerEnabledMessage() = default;`
- L73 _public prototype_ `FAudioBusEnvelopeFollowerEnabledMessage(const UE::Trace::IAnalyzer::FOnEventContext& InContext);`
- L75 _public function_ `virtual uint32 GetSizeOf() const override`
- L76 _public function_ `virtual const FName GetMessageName() const override`
- L77 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L79 _public member_ `bool bEnvelopeFollowerEnabled = false;`

#### struct `UE::Audio::Insights::FAudioBusEnvelopeValuesMessage`  
`struct FAudioBusEnvelopeValuesMessage : public FAudioBusMessageBase`  
_L82-92_
- inherits: `FAudioBusMessageBase`
- L84 _public prototype_ `FAudioBusEnvelopeValuesMessage() = default;`
- L85 _public prototype_ `FAudioBusEnvelopeValuesMessage(const UE::Trace::IAnalyzer::FOnEventContext& InContext);`
- L87 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L88 _public function_ `virtual const FName GetMessageName() const override`
- L89 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L91 _public member_ `TArray<float> EnvelopeValues;`

#### struct `UE::Audio::Insights::FAudioBusStopMessage`  
`struct FAudioBusStopMessage : public FAudioBusMessageBase`  
_L94-102_
- inherits: `FAudioBusMessageBase`
- L96 _public prototype_ `FAudioBusStopMessage() = default;`
- L97 _public prototype_ `FAudioBusStopMessage(const UE::Trace::IAnalyzer::FOnEventContext& InContext);`
- L99 _public function_ `virtual uint32 GetSizeOf() const override`
- L100 _public function_ `virtual const FName GetMessageName() const override`
- L101 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### class `UE::Audio::Insights::FAudioBusMessages`  
`class FAudioBusMessages`  
_L104-113_
- L106 _private member_ `TAnalyzerMessageQueue<FAudioBusStartMessage> StartMessages;`
- L107 _private member_ `TAnalyzerMessageQueue<FAudioBusHasActivityMessage> HasActivityMessages;`
- L108 _private member_ `TAnalyzerMessageQueue<FAudioBusEnvelopeFollowerEnabledMessage> EnvelopeFollowerEnabledMessages;`
- L109 _private member_ `TAnalyzerMessageQueue<FAudioBusEnvelopeValuesMessage> EnvelopeValuesMessages;`
- L110 _private member_ `TAnalyzerMessageQueue<FAudioBusStopMessage> StopMessages;`

#### struct `UE::Audio::Insights::FAudioBusDashboardEntry`  
`struct FAudioBusDashboardEntry : public IObjectDashboardEntry`  
_L115-139_
- inherits: `IObjectDashboardEntry`
- L117 _public prototype_ `FAudioBusDashboardEntry();`
- L118 _public prototype_ `FAudioBusDashboardEntry(FAudioBusDashboardEntry& Other);` — // Copy constructor - make sure we take a deep copy of FAudioMeterInfo
- L120 _public prototype_ `virtual ~FAudioBusDashboardEntry() = default;`
- L122 _public prototype_ `FAudioBusDashboardEntry& operator=(const FAudioBusDashboardEntry& Other);`
- L124 _public function_ `virtual FText GetDisplayName() const override`
- L125 _public function_ `virtual FString GetObjectPath() const override`
- L126 _public function_ `virtual const UObject* GetObject() const override`
- L127 _public function_ `virtual UObject* GetObject() override`
- L128 _public function_ `virtual bool IsValid() const override`
- L130 _public member_ `uint32 AudioBusId = INDEX_NONE;`
- L131 _public member_ `double Timestamp = 0.0;`
- L133 _public member_ `TSharedRef<FAudioMeterInfo> AudioMeterInfo;`
- L135 _public member_ `FString Name;`
- L136 _public member_ `bool bHasActivity = false;`
- L137 _public member_ `bool bEnvelopeFollowerEnabled = false;`
- L138 _public member_ `EAudioBusType AudioBusType = EAudioBusType::None;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Audio` (scope `UE`)
- L15 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L17 _namespace_ `namespace AudioBusMessageNames` (scope `UE::Audio::Insights`)
- L19 _externvar_ `extern const FName Start;` (scope `UE::Audio::Insights::AudioBusMessageNames`)
- L20 _externvar_ `extern const FName HasActivity;` (scope `UE::Audio::Insights::AudioBusMessageNames`)
- L21 _externvar_ `extern const FName EnvelopeFollowerEnabled;` (scope `UE::Audio::Insights::AudioBusMessageNames`)
- L22 _externvar_ `extern const FName EnvelopeValues;` (scope `UE::Audio::Insights::AudioBusMessageNames`)
- L23 _externvar_ `extern const FName Stop;` (scope `UE::Audio::Insights::AudioBusMessageNames`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/AudioEventLogTraceMessages.h` (Public)


#### enum `UE::Audio::Insights::EAudioEventLogSoundCategory`  
`enum class EAudioEventLogSoundCategory : uint8`  
_L13-21_
- L15 _public enumerator_ `None`
- L16 _public enumerator_ `MetaSound`
- L17 _public enumerator_ `SoundCue`
- L18 _public enumerator_ `ProceduralSource`
- L19 _public enumerator_ `SoundWave`
- L20 _public enumerator_ `SoundCueTemplate`

#### enum `UE::Audio::Insights::EAudioEventCacheState`  
`enum class EAudioEventCacheState : uint8`  
_L23-27_
- L25 _public enumerator_ `Cached`
- L26 _public enumerator_ `NextToBeDeleted`

#### struct `UE::Audio::Insights::FAudioEventLogMessage`  
`struct FAudioEventLogMessage : public IAudioCachedMessage`  
_L29-51_
- inherits: `IAudioCachedMessage`
- L31 _public prototype_ `FAudioEventLogMessage() = default;`
- L32 _public prototype_ `FAudioEventLogMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L34 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L35 _public function_ `virtual uint64 GetID() const override`
- L36 _public prototype_ `virtual const FName GetMessageName() const override;`
- L37 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L40 _public member_ `uint32 MessageID = INDEX_NONE;`
- L41 _public member_ `uint32 PlayOrder = INDEX_NONE;`
- L43 _public member_ `FString EventName;`
- L44 _public member_ `FString AssetPath;`
- L45 _public member_ `FString ActorLabel;`
- L46 _public member_ `FString ActorIconName;`
- L47 _public member_ `FString AudioComponentName;`
- L48 _public member_ `FString CategoryName;`
- L50 _public member_ `EAudioEventLogSoundCategory CategoryType;`

#### class `UE::Audio::Insights::FAudioEventLogDashboardEntry`  
`class FAudioEventLogDashboardEntry : public FSoundAssetDashboardEntry`  
_L53-75_
- inherits: `FSoundAssetDashboardEntry`
- L56 _public prototype_ `FAudioEventLogDashboardEntry() = default;`
- L57 _public prototype_ `virtual ~FAudioEventLogDashboardEntry() = default;`
- L59 _public function_ `virtual bool IsValid() const override`
- L64 _public member_ `uint32 MessageID = INDEX_NONE;`
- L66 _public member_ `FString EventName;`
- L67 _public member_ `FString ActorLabel;`
- L68 _public member_ `FName ActorIconName;`
- L69 _public member_ `FString AudioComponentName;`
- L70 _public member_ `FString CategoryName;`
- L72 _public member_ `EAudioEventLogSoundCategory Category = EAudioEventLogSoundCategory::None;`
- L73 _public member_ `EAudioEventCacheState CachedState = EAudioEventCacheState::Cached;`
- L74 _public member_ `bool bCacheStatusIsDirty = false;`

#### class `UE::Audio::Insights::FAudioEventLogMessages`  
`class FAudioEventLogMessages`  
_L77-82_
- L79 _private member_ `TAnalyzerMessageQueue<FAudioEventLogMessage> AudioEventLogMessages;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Audio` (scope `UE`)
- L11 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/BookmarkTraceMessages.h` (Public)


#### struct `UE::Audio::Insights::FBookmarkTraceMessage`  
`struct FBookmarkTraceMessage : public IAudioCachedMessage`  
_L15-25_
- inherits: `IAudioCachedMessage`
- L17 _public prototype_ `FBookmarkTraceMessage(double InTimestamp, const FString& InLabel);`
- L19 _public function_ `virtual uint64 GetID() const override`
- L20 _public function_ `virtual const FName GetMessageName() const override`
- L21 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L22 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L24 _public member_ `FString Label;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Audio` (scope `UE`)
- L8 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L10 _namespace_ `namespace BookmarkMessageNames` (scope `UE::Audio::Insights`)
- L12 _externvar_ `extern const FName Bookmark;` (scope `UE::Audio::Insights::BookmarkMessageNames`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/OutputMeterTraceMessages.h` (Public)


#### struct `UE::Audio::Insights::FOutputMeterMessageBase`  
`struct FOutputMeterMessageBase : public IAudioCachedMessage`  
_L19-28_
- inherits: `IAudioCachedMessage`
- L21 _public prototype_ `FOutputMeterMessageBase() = default;`
- L22 _public prototype_ `FOutputMeterMessageBase(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L24 _public function_ `virtual uint64 GetID() const override`
- L27 _public member_ `uint32 SubmixId = INDEX_NONE;`

#### struct `UE::Audio::Insights::FOutputMeterMainSubmixLoadedMessage`  
`struct FOutputMeterMainSubmixLoadedMessage : public FOutputMeterMessageBase`  
_L30-38_
- inherits: `FOutputMeterMessageBase`
- L32 _public prototype_ `FOutputMeterMainSubmixLoadedMessage() = default;`
- L33 _public prototype_ `FOutputMeterMainSubmixLoadedMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L35 _public function_ `virtual const FName GetMessageName() const override`
- L36 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L37 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FOutputMeterMainSubmixAlivePingMessage`  
`struct FOutputMeterMainSubmixAlivePingMessage : public FOutputMeterMainSubmixLoadedMessage`  
_L40-48_
- inherits: `FOutputMeterMainSubmixLoadedMessage`
- L42 _public prototype_ `FOutputMeterMainSubmixAlivePingMessage() = default;`
- L43 _public prototype_ `FOutputMeterMainSubmixAlivePingMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L45 _public function_ `virtual const FName GetMessageName() const override`
- L46 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L47 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FOutputMeterTruePeakMessage`  
`struct FOutputMeterTruePeakMessage : public FOutputMeterMessageBase`  
_L50-60_
- inherits: `FOutputMeterMessageBase`
- L52 _public prototype_ `FOutputMeterTruePeakMessage() = default;`
- L53 _public prototype_ `FOutputMeterTruePeakMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L55 _public function_ `virtual const FName GetMessageName() const override`
- L56 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L57 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L59 _public member_ `float TruePeakMaxValueDb = MIN_VOLUME_DECIBELS;`

#### struct `UE::Audio::Insights::FOutputMeterLKFSValuesMessage`  
`struct FOutputMeterLKFSValuesMessage : public FOutputMeterMessageBase`  
_L62-76_
- inherits: `FOutputMeterMessageBase`
- L64 _public prototype_ `FOutputMeterLKFSValuesMessage() = default;`
- L65 _public prototype_ `FOutputMeterLKFSValuesMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L67 _public function_ `virtual const FName GetMessageName() const override`
- L68 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L69 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L71 _public member_ `float LongTermLoudness = MIN_VOLUME_DECIBELS;`
- L72 _public member_ `float ShortTermLoudness = MIN_VOLUME_DECIBELS;`
- L73 _public member_ `float MomentaryLoudness = MIN_VOLUME_DECIBELS;`
- L74 _public member_ `float LoudnessRangeLowerBound = 0.0f;`
- L75 _public member_ `float LoudnessRangeUpperBound = 0.0f;`

#### class `UE::Audio::Insights::FOutputMeterDashboardEntry`  
`class FOutputMeterDashboardEntry : public IDashboardDataViewEntry`  
_L78-100_
- inherits: `IDashboardDataViewEntry`
- L81 _public prototype_ `FOutputMeterDashboardEntry() = default;`
- L82 _public prototype_ `virtual ~FOutputMeterDashboardEntry() = default;`
- L84 _public function_ `virtual bool IsValid() const override`
- L90 _public member_ `double Timestamp = 0.0;`
- L91 _public member_ `uint32 SubmixId = static_cast<uint32>(INDEX_NONE);`
- L93 _public member_ `float TruePeakMaxValueDb = MIN_VOLUME_DECIBELS;`
- L95 _public member_ `float LongTermLoudness = MIN_VOLUME_DECIBELS;`
- L96 _public member_ `float ShortTermLoudness = MIN_VOLUME_DECIBELS;`
- L97 _public member_ `float MomentaryLoudness = MIN_VOLUME_DECIBELS;`
- L98 _public member_ `float LoudnessRangeLowerBound = 0.0f;`
- L99 _public member_ `float LoudnessRangeUpperBound = 0.0f;`

#### class `UE::Audio::Insights::FOutputMeterMessages`  
`class FOutputMeterMessages`  
_L102-110_
- L104 _private member_ `TAnalyzerMessageQueue<FOutputMeterMainSubmixLoadedMessage> MainSubmixLoadedMessages;`
- L105 _private member_ `TAnalyzerMessageQueue<FOutputMeterMainSubmixAlivePingMessage> MainSubmixAlivePingMessages;`
- L106 _private member_ `TAnalyzerMessageQueue<FOutputMeterTruePeakMessage> TruePeakMessages;`
- L107 _private member_ `TAnalyzerMessageQueue<FOutputMeterLKFSValuesMessage> LKFSValuesMessages;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L11 _namespace_ `namespace OutputMeterMessageNames` (scope `UE::Audio::Insights`)
- L13 _externvar_ `extern const FName MainSubmixLoaded;` (scope `UE::Audio::Insights::OutputMeterMessageNames`)
- L14 _externvar_ `extern const FName MainSubmixAlivePing;` (scope `UE::Audio::Insights::OutputMeterMessageNames`)
- L15 _externvar_ `extern const FName TruePeak;` (scope `UE::Audio::Insights::OutputMeterMessageNames`)
- L16 _externvar_ `extern const FName LKFSValues;` (scope `UE::Audio::Insights::OutputMeterMessageNames`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/SignalFlowEntryKey.h` (Public)


#### enum `UE::Audio::Insights::ESignalFlowEntryType`  
`enum class ESignalFlowEntryType : int32`  
_L13-24_
- desc: Which render stage does this node belong to. This enum is in the order the render stages occur - from root to audio device
- L15 _public enumerator_ `OwnerObject = 0`
- L16 _public enumerator_ `SoundSource`
- L17 _public enumerator_ `AudioBus`
- L18 _public enumerator_ `Submix`
- L19 _public enumerator_ `AudioDevice`
- L22 _public enumerator_ `InvalidLow = TNumericLimits<int32>::Lowest()`
- L23 _public enumerator_ `InvalidMax = TNumericLimits<int32>::Max()`

#### enum `UE::Audio::Insights::ESignalFlowNodeDetailParam`  
`enum class ESignalFlowNodeDetailParam : uint8`  
_L26-42_
- L28 _public enumerator_ `Amplitude = 0u`
- L29 _public enumerator_ `Volume`
- L30 _public enumerator_ `Pitch`
- L31 _public enumerator_ `LPFFreq`
- L32 _public enumerator_ `HPFFreq`
- L33 _public enumerator_ `Priority`
- L34 _public enumerator_ `Distance`
- L35 _public enumerator_ `Attenuation`
- L36 _public enumerator_ `RelativeRenderCost`
- L37 _public enumerator_ `AudioComponentName`
- L38 _public enumerator_ `SendOutputVolume`
- L41 _public enumerator_ `MAX`

#### struct `UE::Audio::Insights::FSignalFlowEntryKey`  
`struct FSignalFlowEntryKey`  
_L44-82_
- L46 _public prototype_ `FSignalFlowEntryKey() = default;`
- L47 _public function_ `FSignalFlowEntryKey(const ::Audio::FDeviceId InDeviceID, const ESignalFlowEntryType InEntryType, const uint32 InEntryID) : DeviceID(InDeviceID) , EntryType(InEntryType) , EntryID(InEntryID)`
- L59 _public function_ `bool operator==(const FSignalFlowEntryKey& InOther) const`
- L64 _public function_ `bool operator<(const FSignalFlowEntryKey& InOther) const`
- L80 _public member_ `ESignalFlowEntryType EntryType = ESignalFlowEntryType::SoundSource;`
- L81 _public member_ `uint32 EntryID = INDEX_NONE;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L54 _function_ `friend uint32 GetTypeHash(const FSignalFlowEntryKey& Key)` (scope `UE::Audio::Insights`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/SignalFlowTraceMessages.h` (Public)


#### struct `UE::Audio::Insights::FSignalFlowMessageBase`  
`struct FSignalFlowMessageBase : public IAudioCachedMessage`  
_L25-31_
- inherits: `IAudioCachedMessage`
- L27 _public prototype_ `FSignalFlowMessageBase() = default;`
- L28 _public prototype_ `FSignalFlowMessageBase(const Trace::IAnalyzer::FOnEventContext& InContext);`

#### struct `UE::Audio::Insights::FSignalFlowSendMessageBase`  
`struct FSignalFlowSendMessageBase : public FSignalFlowMessageBase`  
_L33-48_
- inherits: `FSignalFlowMessageBase`
- L35 _public prototype_ `FSignalFlowSendMessageBase() = default;`
- L36 _public prototype_ `FSignalFlowSendMessageBase(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L38 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L46 _public member_ `uint32 SenderID = INDEX_NONE;`
- L47 _public member_ `TArray<FSendInfoPair> SendInfos;`

#### struct `UE::Audio::Insights::FSignalFlowSendMessageBase::FSendInfoPair`  
`struct FSendInfoPair`  
_L40-44_
- L42 _public member_ `uint32 ReceiverID = INDEX_NONE;`
- L43 _public member_ `float SendLevel = 0.0f;`

#### struct `UE::Audio::Insights::FSoundToBusSendMessage`  
`struct FSoundToBusSendMessage : public FSignalFlowSendMessageBase`  
_L50-61_
- inherits: `FSignalFlowSendMessageBase`
- L52 _public prototype_ `FSoundToBusSendMessage() = default;`
- L53 _public function_ `FSoundToBusSendMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSignalFlowSendMessageBase(InContext)`
- L58 _public function_ `virtual uint64 GetID() const override`
- L59 _public function_ `virtual const FName GetMessageName() const override`
- L60 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FBusPatchWriterConnectedMessage`  
`struct FBusPatchWriterConnectedMessage : public FSignalFlowSendMessageBase`  
_L63-74_
- inherits: `FSignalFlowSendMessageBase`
- L65 _public prototype_ `FBusPatchWriterConnectedMessage() = default;`
- L66 _public function_ `FBusPatchWriterConnectedMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSignalFlowSendMessageBase(InContext)`
- L71 _public function_ `virtual uint64 GetID() const override`
- L72 _public function_ `virtual const FName GetMessageName() const override`
- L73 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FBusPatchReaderConnectedMessage`  
`struct FBusPatchReaderConnectedMessage : public FSignalFlowSendMessageBase`  
_L76-87_
- inherits: `FSignalFlowSendMessageBase`
- L78 _public prototype_ `FBusPatchReaderConnectedMessage() = default;`
- L79 _public function_ `FBusPatchReaderConnectedMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSignalFlowSendMessageBase(InContext)`
- L84 _public function_ `virtual uint64 GetID() const override`
- L85 _public function_ `virtual const FName GetMessageName() const override`
- L86 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FSoundToSubmixSendMessage`  
`struct FSoundToSubmixSendMessage : public FSignalFlowSendMessageBase`  
_L89-100_
- inherits: `FSignalFlowSendMessageBase`
- L91 _public prototype_ `FSoundToSubmixSendMessage() = default;`
- L92 _public function_ `FSoundToSubmixSendMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSignalFlowSendMessageBase(InContext)`
- L97 _public function_ `virtual uint64 GetID() const override`
- L98 _public function_ `virtual const FName GetMessageName() const override`
- L99 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FSubmixToSubmixSendMessage`  
`struct FSubmixToSubmixSendMessage : public FSignalFlowMessageBase`  
_L102-116_
- inherits: `FSignalFlowMessageBase`
- L104 _public prototype_ `FSubmixToSubmixSendMessage() = default;`
- L105 _public prototype_ `FSubmixToSubmixSendMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L107 _public function_ `virtual uint64 GetID() const override`
- L108 _public function_ `virtual const FName GetMessageName() const override`
- L109 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L110 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L112 _public member_ `uint32 SenderID = INDEX_NONE;`
- L113 _public member_ `uint32 ReceiverID = INDEX_NONE;`
- L114 _public member_ `float SendLevel = 0.0f;`
- L115 _public member_ `bool bIsFinalStage = false;`

#### class `UE::Audio::Insights::FSignalFlowMessages`  
`class FSignalFlowMessages`  
_L118-151_
- L120 _private member_ `TAnalyzerMessageQueue<FSoundWaveStartMessage> SoundWaveStartMessages;`
- L121 _private member_ `TAnalyzerMessageQueue<FSoundWaveIsAlivePingMessage> SoundWaveIsAlivePingMessages;`
- L122 _private member_ `TAnalyzerMessageQueue<FSoundWaveStopMessage> SoundWaveStopMessages;`
- L123 _private member_ `TAnalyzerMessageQueue<FSoundStopMessage> SoundStopMessages;`
- L124 _private member_ `TAnalyzerMessageQueue<FAudioBusStartMessage> BusStartMessages;`
- L125 _private member_ `TAnalyzerMessageQueue<FAudioBusStartMessage> BusIsAlivePingMessages;`
- L126 _private member_ `TAnalyzerMessageQueue<FAudioBusStopMessage> BusStopMessages;`
- L127 _private member_ `TAnalyzerMessageQueue<FSubmixLoadedMessage> SubmixLoadedMessages;`
- L128 _private member_ `TAnalyzerMessageQueue<FSubmixAlivePingMessage> SubmixAliveMessages;`
- L129 _private member_ `TAnalyzerMessageQueue<FSubmixUnloadedMessage> SubmixUnloadedMessages;`
- L131 _private member_ `TAnalyzerMessageQueue<FSoundToBusSendMessage> SoundToBusSendMessages;`
- L132 _private member_ `TAnalyzerMessageQueue<FBusPatchWriterConnectedMessage> BusPatchWriterConnectedMessages;`
- L133 _private member_ `TAnalyzerMessageQueue<FBusPatchReaderConnectedMessage> BusPatchReaderConnectedMessages;`
- L134 _private member_ `TAnalyzerMessageQueue<FSoundToSubmixSendMessage> SoundToSubmixSendMessages;`
- L135 _private member_ `TAnalyzerMessageQueue<FSubmixToSubmixSendMessage> SubmixToSubmixSendMessages;`
- L137 _private member_ `TAnalyzerMessageQueue<FSoundEnvelopeMessage> SoundEnvelopeMessages;`
- L138 _private member_ `TAnalyzerMessageQueue<FSoundVolumeMessage> SoundVolumeMessages;`
- L139 _private member_ `TAnalyzerMessageQueue<FSoundPitchMessage> SoundPitchMessages;`
- L140 _private member_ `TAnalyzerMessageQueue<FSoundLPFFreqMessage> SoundLPFFreqMessages;`
- L141 _private member_ `TAnalyzerMessageQueue<FSoundHPFFreqMessage> SoundHPFFreqMessages;`
- L142 _private member_ `TAnalyzerMessageQueue<FSoundPriorityMessage> SoundPriorityMessages;`
- L143 _private member_ `TAnalyzerMessageQueue<FSoundDistanceMessage> SoundDistanceMessages;`
- L144 _private member_ `TAnalyzerMessageQueue<FSoundDistanceAttenuationMessage> SoundAttenuationMessages;`
- L145 _private member_ `TAnalyzerMessageQueue<FSoundRelativeRenderCostMessage> SoundRelativeRenderCostMessages;`
- L147 _private member_ `TAnalyzerMessageQueue<FAudioBusEnvelopeValuesMessage> AudioBusEnvelopeMessages;`
- L148 _private member_ `TAnalyzerMessageQueue<FSubmixEnvelopeValuesMessage> SubmixEnvelopeMessages;`

#### struct `UE::Audio::Insights::FSignalFlowOutputData`  
`struct FSignalFlowOutputData`  
_L153-156_
- L155 _public member_ `TOptional<float> SendLevel;`

#### struct `UE::Audio::Insights::FSignalFlowDashboardEntry`  
`struct FSignalFlowDashboardEntry : public IObjectDashboardEntry`  
_L158-212_
- inherits: `IObjectDashboardEntry`
- L160 _public prototype_ `FSignalFlowDashboardEntry();`
- L161 _public prototype_ `virtual ~FSignalFlowDashboardEntry() = default;`
- L163 _public function_ `virtual FText GetDisplayName() const override`
- L169 _public function_ `virtual FString GetObjectPath() const override`
- L170 _public function_ `virtual const UObject* GetObject() const override`
- L171 _public function_ `virtual UObject* GetObject() override`
- L172 _public function_ `virtual bool IsValid() const override`
- L174 _public function_ `FSignalFlowEntryKey GetSignalFlowEntryKey() const`
- L176 _public prototype_ `void WriteNewAmplitudeValue(const float Value);`
- L177 _public prototype_ `void ResetDataBuffers();`
- L178 _public prototype_ `bool IsEntryAmplitudeWindowSilent() const;`
- L181 _public member_ `ESignalFlowEntryType EntryType = ESignalFlowEntryType::SoundSource;`
- L182 _public member_ `uint32 SignalFlowNodeID = INDEX_NONE;`
- L183 _public member_ `double Timestamp = 0.0;`
- L185 _public member_ `FString Name;`
- L186 _public member_ `FName IconName = NAME_None;`
- L188 _public member_ `TSet<FSignalFlowEntryKey> Inputs;`
- L189 _public member_ `TSortedMap<FSignalFlowEntryKey, FSignalFlowOutputData> Outputs;`
- L191 _public member_ `TOptional<FSignalFlowEntryKey> LinkedSourceBus;`
- L192 _public member_ `TSet<FSignalFlowEntryKey> LinkedSoundSources;`
- L194 _public member_ `TSet<FSignalFlowEntryKey> LinkedBusPatchInputs;` — Entries that send bus patch connections to this entry
- L195 _public member_ `TSet<FSignalFlowEntryKey> LinkedBusPatchOutputs;` — Entries that this entry sends bus patch connections to
- L197 _public member_ `TCircularBuffer<float> AmplitudeDataRange;`
- L198 _public member_ `int32 AmplitudeWriteIndex = 0;`
- L199 _public member_ `uint32 NumConsecutiveSilentAmplitudeValues = 0u;`
- L201 _public member_ `TOptional<float> Amplitude;`
- L202 _public member_ `TOptional<float> Volume;`
- L203 _public member_ `TOptional<float> Pitch;`
- L204 _public member_ `TOptional<float> LPFFreq;`
- L205 _public member_ `TOptional<float> HPFFreq;`
- L206 _public member_ `TOptional<float> Priority;`
- L207 _public member_ `TOptional<float> Distance;`
- L208 _public member_ `TOptional<float> Attenuation;`
- L209 _public member_ `TOptional<float> RelativeRenderCost;`
- L211 _public member_ `TOptional<FString> AudioComponentName;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Audio` (scope `UE`)
- L14 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L16 _namespace_ `namespace SignalFlowMessageNames` (scope `UE::Audio::Insights`)
- L18 _externvar_ `extern const FName SoundWaveToBusSend;` (scope `UE::Audio::Insights::SignalFlowMessageNames`)
- L19 _externvar_ `extern const FName SoundWaveToSubmixSend;` (scope `UE::Audio::Insights::SignalFlowMessageNames`)
- L20 _externvar_ `extern const FName SubmixToSubmixSend;` (scope `UE::Audio::Insights::SignalFlowMessageNames`)
- L21 _externvar_ `extern const FName BusPatchWriterConnected;` (scope `UE::Audio::Insights::SignalFlowMessageNames`)
- L22 _externvar_ `extern const FName BusPatchReaderConnected;` (scope `UE::Audio::Insights::SignalFlowMessageNames`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/SoundTraceMessages.h` (Public)


#### enum `UE::Audio::Insights::ESoundDashboardEntryType`  
`enum class ESoundDashboardEntryType : uint8`  
_L21-30_
- L23 _public enumerator_ `None`
- L24 _public enumerator_ `MetaSound`
- L25 _public enumerator_ `SoundCue`
- L26 _public enumerator_ `ProceduralSource`
- L27 _public enumerator_ `SoundWave`
- L28 _public enumerator_ `SoundCueTemplate`
- L29 _public enumerator_ `Pinned`

#### struct `UE::Audio::Insights::FSoundMessageBase`  
`struct FSoundMessageBase : public IAudioCachedMessage`  
_L68-74_
- inherits: `IAudioCachedMessage`
- desc: Trace messages
- L70 _public prototype_ `FSoundMessageBase() = default;`
- L71 _public prototype_ `FSoundMessageBase(const Trace::IAnalyzer::FOnEventContext& InContext);`

#### struct `UE::Audio::Insights::FSoundParameterMessage`  
`struct FSoundParameterMessage : public FSoundMessageBase`  
_L76-91_
- inherits: `FSoundMessageBase`
- L78 _public prototype_ `FSoundParameterMessage() = default;`
- L80 _public function_ `FSoundParameterMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSoundMessageBase(InContext)`
- L87 _public function_ `virtual uint64 GetID() const override`
- L89 _public member_ `uint32 WaveInstancePlayOrder = INDEX_NONE;`
- L90 _public member_ `uint32 ActiveSoundPlayOrder = INDEX_NONE;`

#### struct `UE::Audio::Insights::FSoundStartMessage`  
`struct FSoundStartMessage : public FSoundMessageBase`  
_L93-108_
- inherits: `FSoundMessageBase`
- L95 _public prototype_ `FSoundStartMessage() = default;`
- L96 _public prototype_ `FSoundStartMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L98 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L99 _public function_ `virtual const FName GetMessageName() const override`
- L100 _public function_ `virtual uint64 GetID() const override`
- L101 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L103 _public member_ `FString Name;`
- L104 _public member_ `ESoundDashboardEntryType EntryType;`
- L105 _public member_ `FString ActorLabel;`
- L106 _public member_ `FString AudioComponentName;`
- L107 _public member_ `uint32 ActiveSoundPlayOrder = INDEX_NONE;`

#### struct `UE::Audio::Insights::FSoundIsAlivePingMessage`  
`struct FSoundIsAlivePingMessage : public FSoundStartMessage`  
_L110-120_
- inherits: `FSoundStartMessage`
- L112 _public prototype_ `FSoundIsAlivePingMessage() = default;`
- L113 _public function_ `FSoundIsAlivePingMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSoundStartMessage(InContext)`
- L118 _public function_ `virtual const FName GetMessageName() const override`
- L119 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FSoundWaveStartMessage`  
`struct FSoundWaveStartMessage : public FSoundStartMessage`  
_L122-144_
- inherits: `FSoundStartMessage`
- L124 _public prototype_ `FSoundWaveStartMessage() = default;`
- L126 _public function_ `FSoundWaveStartMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSoundStartMessage(InContext)`
- L136 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L137 _public function_ `virtual const FName GetMessageName() const override`
- L138 _public function_ `virtual uint64 GetID() const override`
- L139 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L141 _public member_ `uint32 WaveInstancePlayOrder = INDEX_NONE;`
- L142 _public member_ `FString ActorIconName;`
- L143 _public member_ `int32 SourceBusID = INDEX_NONE;`

#### struct `UE::Audio::Insights::FSoundWaveIsAlivePingMessage`  
`struct FSoundWaveIsAlivePingMessage : public FSoundWaveStartMessage`  
_L146-156_
- inherits: `FSoundWaveStartMessage`
- L148 _public prototype_ `FSoundWaveIsAlivePingMessage() = default;`
- L149 _public function_ `FSoundWaveIsAlivePingMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSoundWaveStartMessage(InContext)`
- L154 _public function_ `virtual const FName GetMessageName() const override`
- L155 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FSoundStopMessage`  
`struct FSoundStopMessage : public FSoundMessageBase`  
_L158-173_
- inherits: `FSoundMessageBase`
- L160 _public prototype_ `FSoundStopMessage() = default;`
- L161 _public function_ `FSoundStopMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSoundMessageBase(InContext)`
- L167 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L168 _public function_ `virtual const FName GetMessageName() const override`
- L169 _public function_ `virtual uint64 GetID() const override`
- L170 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L172 _public member_ `uint32 ActiveSoundPlayOrder = INDEX_NONE;`

#### struct `UE::Audio::Insights::FSoundWaveStopMessage`  
`struct FSoundWaveStopMessage : public FSoundMessageBase`  
_L175-193_
- inherits: `FSoundMessageBase`
- L177 _public prototype_ `FSoundWaveStopMessage() = default;`
- L179 _public function_ `FSoundWaveStopMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSoundMessageBase(InContext)`
- L186 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L187 _public function_ `virtual const FName GetMessageName() const override`
- L188 _public function_ `virtual uint64 GetID() const override`
- L189 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L191 _public member_ `uint32 WaveInstancePlayOrder = INDEX_NONE;`
- L192 _public member_ `uint32 ActiveSoundPlayOrder = INDEX_NONE;`

#### class `UE::Audio::Insights::FSoundMessages`  
`class FSoundMessages`  
_L225-242_
- desc: Trace message queues
- L228 _public member_ `TAnalyzerMessageQueue<FSoundStartMessage> ActiveSoundStartMessages;`
- L229 _public member_ `TAnalyzerMessageQueue<FSoundWaveStartMessage> SoundWaveStartMessages;`
- L230 _public member_ `TAnalyzerMessageQueue<FSoundIsAlivePingMessage> ActiveSoundIsAlivePingMessages;`
- L231 _public member_ `TAnalyzerMessageQueue<FSoundWaveIsAlivePingMessage> SoundWaveIsAlivePingMessages;`
- L232 _public member_ `TAnalyzerMessageQueue<FSoundPriorityMessage> PriorityMessages;`
- L233 _public member_ `TAnalyzerMessageQueue<FSoundDistanceMessage> DistanceMessages;`
- L234 _public member_ `TAnalyzerMessageQueue<FSoundDistanceAttenuationMessage> DistanceAttenuationMessages;`
- L235 _public member_ `TAnalyzerMessageQueue<FSoundHPFFreqMessage> HPFFreqMessages;`
- L236 _public member_ `TAnalyzerMessageQueue<FSoundLPFFreqMessage> LPFFreqMessages;`
- L237 _public member_ `TAnalyzerMessageQueue<FSoundEnvelopeMessage> AmplitudeMessages;`
- L238 _public member_ `TAnalyzerMessageQueue<FSoundVolumeMessage> VolumeMessages;`
- L239 _public member_ `TAnalyzerMessageQueue<FSoundPitchMessage> PitchMessages;`
- L240 _public member_ `TAnalyzerMessageQueue<FSoundRelativeRenderCostMessage> RelativeRenderCostMessages;`
- L241 _public member_ `TAnalyzerMessageQueue<FSoundStopMessage> StopMessages;`

#### class `UE::Audio::Insights::FSoundDashboardEntry`  
`class FSoundDashboardEntry : public IObjectTreeDashboardEntry`  
_L247-350_
- inherits: `IObjectTreeDashboardEntry`
- L250 _public prototype_ `FSoundDashboardEntry();`
- L251 _public prototype_ `virtual ~FSoundDashboardEntry() = default;`
- L253 _public function_ `virtual TObjectPtr<UObject> GetObject() override`
- L254 _public function_ `virtual const TObjectPtr<UObject> GetObject() const override`
- L256 _public function_ `void SetName(const FString& InName)`
- L267 _public function_ `virtual const FText& GetDisplayName() const override`
- L272 _public function_ `const FName& GetDisplayFName() const`
- L277 _public function_ `const FString& GetDisplayNameStr() const`
- L282 _public function_ `virtual const FLinearColor& GetEntryColor() const override`
- L287 _public function_ `virtual void SetEntryColor(const FLinearColor& Color) override`
- L292 _public function_ `virtual bool IsValid() const override`
- L293 _public function_ `virtual uint64 GetEntryID() const override`
- L295 _public function_ `virtual bool HasSetInitExpansion() const override`
- L296 _public function_ `virtual void ResetHasSetInitExpansion() override`
- L298 _public prototype_ `void ResetDataBuffers(const uint32 DataPointsCapacity);`
- L308 _public member_ `uint32 WaveInstancePlayOrder = INDEX_NONE;`
- L309 _public member_ `uint32 ActiveSoundPlayOrder = INDEX_NONE;`
- L310 _public member_ `double Timestamp = 0.0;`
- L311 _public member_ `double TimeoutTimestamp = INVALID_TIMEOUT;`
- L312 _public member_ `FText CategoryName;`
- L313 _public member_ `FLinearColor EntryColor = FColor::MakeRandomColor();`
- L314 _public member_ `ESoundDashboardEntryType EntryType = ESoundDashboardEntryType::None;`
- L315 _public member_ `EPinnedEntryType PinnedEntryType = EPinnedEntryType::None;`
- L316 _public member_ `bool bIsCategory = false;`
- L317 _public member_ `bool bHasSetInitExpansion = false;`
- L318 _public member_ `bool bIsVisible = false;`
- L319 _public member_ `bool bIsPlotActive = false;`
- L320 _public member_ `bool bForceKeepEntryAlive = false;`
- L332 _public member_ `float PriorityDataPoint = 0.0f;`
- L333 _public member_ `float DistanceDataPoint = 0.0f;`
- L334 _public member_ `float DistanceAttenuationDataPoint = 0.0f;`
- L335 _public member_ `float LPFFreqDataPoint = 20000.0f;`
- L336 _public member_ `float HPFFreqDataPoint = 0.0f;`
- L337 _public member_ `float AmplitudeDataPoint = MIN_VOLUME_DECIBELS;`
- L338 _public member_ `float VolumeDataPoint = 0.0f;`
- L339 _public member_ `float PitchDataPoint = 1.0f;`
- L340 _public member_ `float RelativeRenderCostDataPoint = 0.0f;`
- L342 _public member_ `FText ActorLabel;`
- L343 _public member_ `FText AudioComponentName;`
- L346 _private member_ `FString FullName;`
- L347 _private member_ `FName DisplayName;`
- L348 _private member_ `FString DisplayNameStr;`
- L349 _private member_ `FText DisplayNameText;`

#### enum `UE::Audio::Insights::FSoundDashboardEntry::EPinnedEntryType`  
`enum class EPinnedEntryType : uint8`  
_L300-305_
- L302 _public enumerator_ `None = 0`
- L303 _public enumerator_ `PinnedCopy`
- L304 _public enumerator_ `HiddenOriginalEntry`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L19 _variable_ `static constexpr double INVALID_TIMEOUT = -1.0;` (scope `UE::Audio::Insights`)
- L32 _namespace_ `namespace SoundClassNames` (scope `UE::Audio::Insights`)
- L34 _variable_ `const FString MetaSoundSource = TEXT("Met` (scope `UE::Audio::Insights::SoundClassNames`)
- L35 _variable_ `const FString SoundWaveProcedural = TEXT("Sou` (scope `UE::Audio::Insights::SoundClassNames`)
- L36 _variable_ `const FString SoundCue = TEXT("Sou` (scope `UE::Audio::Insights::SoundClassNames`)
- L37 _variable_ `const FString SoundWave = TEXT("Sou` (scope `UE::Audio::Insights::SoundClassNames`)
- L38 _variable_ `const FString SoundCueTemplate = TEXT("Sou` (scope `UE::Audio::Insights::SoundClassNames`)
- L41 _namespace_ `namespace SoundMessageNames` (scope `UE::Audio::Insights`)
- L43 _externvar_ `extern const FName SoundStart;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L44 _externvar_ `extern const FName SoundIsAlivePing;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L45 _externvar_ `extern const FName SoundWaveStart;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L46 _externvar_ `extern const FName SoundWaveIsAlivePing;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L47 _externvar_ `extern const FName SoundStop;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L48 _externvar_ `extern const FName SoundWaveStop;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L50 _externvar_ `extern const FName PriorityParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L51 _externvar_ `extern const FName DistanceParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L52 _externvar_ `extern const FName DistanceAttenuationParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L53 _externvar_ `extern const FName HPFFreqParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L54 _externvar_ `extern const FName LPFFreqParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L55 _externvar_ `extern const FName EnvelopeParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L56 _externvar_ `extern const FName PitchParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L57 _externvar_ `extern const FName VolumeParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L58 _externvar_ `extern const FName RelativeRenderCostParam;` (scope `UE::Audio::Insights::SoundMessageNames`)
- L61 _namespace_ `namespace SoundMessageUtils` (scope `UE::Audio::Insights`)
- L63 _prototype_ `uint64 GeneratePlayOrderUniqueID(const uint32 ActiveSoundPlayOrder, const uint32 WaveInstancePlayOrder);` (scope `UE::Audio::Insights::SoundMessageUtils`)
- L64 _prototype_ `bool IsPriorityValueSetToMax(const float PriorityValue);` (scope `UE::Audio::Insights::SoundMessageUtils`)
- L195 _macro_ `#define DEFINE_SOUND_PARAM_MESSAGE(ClassName, MessageName, ParamName, Type, Default) \`
- L245 _typedef_ `using FDataPoint = TPair<double, float>;` (scope `UE::Audio::Insights`) — Dashboard entry

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/SubmixTraceMessages.h` (Public)


#### struct `UE::Audio::Insights::FSubmixMessageBase`  
`struct FSubmixMessageBase : public IAudioCachedMessage`  
_L27-37_
- inherits: `IAudioCachedMessage`
- L29 _public prototype_ `FSubmixMessageBase() = default;`
- L30 _public prototype_ `FSubmixMessageBase(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L32 _public function_ `virtual uint64 GetID() const override`
- L33 _public function_ `virtual uint32 GetSizeOf() const override`
- L36 _public member_ `uint32 SubmixId = INDEX_NONE;`

#### struct `UE::Audio::Insights::FSubmixLoadedMessage`  
`struct FSubmixLoadedMessage : public FSubmixMessageBase`  
_L39-51_
- inherits: `FSubmixMessageBase`
- L41 _public prototype_ `FSubmixLoadedMessage() = default;`
- L42 _public prototype_ `FSubmixLoadedMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L44 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L45 _public function_ `virtual const FName GetMessageName() const override`
- L46 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L48 _public member_ `FString Name;`
- L49 _public member_ `int32 NumChannels = 0;`
- L50 _public member_ `bool bIsMainSubmix = false;`

#### struct `UE::Audio::Insights::FSubmixAlivePingMessage`  
`struct FSubmixAlivePingMessage : public FSubmixLoadedMessage`  
_L53-63_
- inherits: `FSubmixLoadedMessage`
- L55 _public prototype_ `FSubmixAlivePingMessage() = default;`
- L56 _public function_ `FSubmixAlivePingMessage(const Trace::IAnalyzer::FOnEventContext& InContext) : FSubmixLoadedMessage(InContext)`
- L61 _public function_ `virtual const FName GetMessageName() const override`
- L62 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FSubmixHasActivityMessage`  
`struct FSubmixHasActivityMessage : public FSubmixMessageBase`  
_L65-75_
- inherits: `FSubmixMessageBase`
- L67 _public prototype_ `FSubmixHasActivityMessage() = default;`
- L68 _public prototype_ `FSubmixHasActivityMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L70 _public function_ `virtual uint32 GetSizeOf() const override`
- L71 _public function_ `virtual const FName GetMessageName() const override`
- L72 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L74 _public member_ `bool bHasActivity = false;`

#### struct `UE::Audio::Insights::FSubmixEnvelopeFollowerEnabledMessage`  
`struct FSubmixEnvelopeFollowerEnabledMessage : public FSubmixMessageBase`  
_L77-87_
- inherits: `FSubmixMessageBase`
- L79 _public prototype_ `FSubmixEnvelopeFollowerEnabledMessage() = default;`
- L80 _public prototype_ `FSubmixEnvelopeFollowerEnabledMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L82 _public function_ `virtual uint32 GetSizeOf() const override`
- L83 _public function_ `virtual const FName GetMessageName() const override`
- L84 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L86 _public member_ `bool bEnvelopeFollowerEnabled = false;`

#### struct `UE::Audio::Insights::FSubmixEnvelopeValuesMessage`  
`struct FSubmixEnvelopeValuesMessage : public FSubmixMessageBase`  
_L89-99_
- inherits: `FSubmixMessageBase`
- L91 _public prototype_ `FSubmixEnvelopeValuesMessage() = default;`
- L92 _public prototype_ `FSubmixEnvelopeValuesMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L94 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L95 _public function_ `virtual const FName GetMessageName() const override`
- L96 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L98 _public member_ `TArray<float> EnvelopeValues;`

#### struct `UE::Audio::Insights::FSubmixUnloadedMessage`  
`struct FSubmixUnloadedMessage : public FSubmixMessageBase`  
_L101-109_
- inherits: `FSubmixMessageBase`
- L103 _public prototype_ `FSubmixUnloadedMessage() = default;`
- L104 _public prototype_ `FSubmixUnloadedMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L106 _public function_ `virtual uint32 GetSizeOf() const override`
- L107 _public function_ `virtual const FName GetMessageName() const override`
- L108 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### class `UE::Audio::Insights::FSubmixMessages`  
`class FSubmixMessages`  
_L111-121_
- L113 _private member_ `TAnalyzerMessageQueue<FSubmixLoadedMessage> LoadedMessages;`
- L114 _private member_ `TAnalyzerMessageQueue<FSubmixAlivePingMessage> AlivePingMessages;`
- L115 _private member_ `TAnalyzerMessageQueue<FSubmixHasActivityMessage> HasActivityMessages;`
- L116 _private member_ `TAnalyzerMessageQueue<FSubmixEnvelopeFollowerEnabledMessage> EnvelopeFollowerEnabledMessages;`
- L117 _private member_ `TAnalyzerMessageQueue<FSubmixEnvelopeValuesMessage> EnvelopeValuesMessages;`
- L118 _private member_ `TAnalyzerMessageQueue<FSubmixUnloadedMessage> UnloadedMessages;`

#### struct `UE::Audio::Insights::FSubmixDashboardEntry`  
`struct FSubmixDashboardEntry : public IObjectDashboardEntry`  
_L123-149_
- inherits: `IObjectDashboardEntry`
- L125 _public prototype_ `FSubmixDashboardEntry();`
- L126 _public prototype_ `FSubmixDashboardEntry(FSubmixDashboardEntry& Other);` — Copy constructor - make sure we take a deep copy of FAudioMeterInfo
- L128 _public prototype_ `virtual ~FSubmixDashboardEntry() = default;`
- L130 _public prototype_ `FSubmixDashboardEntry& operator=(const FSubmixDashboardEntry& Other);`
- L132 _public function_ `virtual FText GetDisplayName() const override`
- L133 _public function_ `virtual FString GetObjectPath() const override`
- L134 _public function_ `virtual const UObject* GetObject() const override`
- L135 _public function_ `virtual UObject* GetObject() override`
- L136 _public function_ `virtual bool IsValid() const override`
- L138 _public function_ `bool IsMainSubmix() const`
- L140 _public member_ `uint32 SubmixId = INDEX_NONE;`
- L141 _public member_ `double Timestamp = 0.0;`
- L143 _public member_ `TSharedRef<FAudioMeterInfo> AudioMeterInfo;`
- L145 _public member_ `FString Name;`
- L146 _public member_ `bool bHasActivity = false;`
- L147 _public member_ `bool bEnvelopeFollowerEnabled = false;`
- L148 _public member_ `bool bIsMainSubmix = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Audio` (scope `UE`)
- L15 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L17 _namespace_ `namespace SubmixMessageNames` (scope `UE::Audio::Insights`)
- L19 _externvar_ `extern const FName Loaded;` (scope `UE::Audio::Insights::SubmixMessageNames`)
- L20 _externvar_ `extern const FName IsAlivePing;` (scope `UE::Audio::Insights::SubmixMessageNames`)
- L21 _externvar_ `extern const FName HasActivity;` (scope `UE::Audio::Insights::SubmixMessageNames`)
- L22 _externvar_ `extern const FName EnvelopeFollowerEnabled;` (scope `UE::Audio::Insights::SubmixMessageNames`)
- L23 _externvar_ `extern const FName EnvelopeValues;` (scope `UE::Audio::Insights::SubmixMessageNames`)
- L24 _externvar_ `extern const FName Unloaded;` (scope `UE::Audio::Insights::SubmixMessageNames`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Messages/VirtualLoopTraceMessages.h` (Public)


#### struct `UE::Audio::Insights::FVirtualLoopMessageBase`  
`struct FVirtualLoopMessageBase : public IAudioCachedMessage`  
_L25-34_
- inherits: `IAudioCachedMessage`
- L27 _public prototype_ `FVirtualLoopMessageBase() = default;`
- L28 _public prototype_ `FVirtualLoopMessageBase(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L30 _public function_ `virtual uint64 GetID() const override`
- L33 _public member_ `uint32 PlayOrder = INDEX_NONE;`

#### struct `UE::Audio::Insights::FVirtualLoopVirtualizeMessage`  
`struct FVirtualLoopVirtualizeMessage : public FVirtualLoopMessageBase`  
_L36-47_
- inherits: `FVirtualLoopMessageBase`
- L38 _public prototype_ `FVirtualLoopVirtualizeMessage() = default;`
- L39 _public prototype_ `FVirtualLoopVirtualizeMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L41 _public function_ `virtual const FName GetMessageName() const override`
- L42 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L43 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L45 _public member_ `FString Name;`
- L46 _public member_ `uint64 ComponentId = TNumericLimits<uint64>::Max();`

#### struct `UE::Audio::Insights::FVirtualLoopStopOrRealizeMessage`  
`struct FVirtualLoopStopOrRealizeMessage : public FVirtualLoopMessageBase`  
_L49-57_
- inherits: `FVirtualLoopMessageBase`
- L51 _public prototype_ `FVirtualLoopStopOrRealizeMessage() = default;`
- L52 _public prototype_ `FVirtualLoopStopOrRealizeMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L54 _public function_ `virtual const FName GetMessageName() const override`
- L55 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L56 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`

#### struct `UE::Audio::Insights::FVirtualLoopUpdateMessage`  
`struct FVirtualLoopUpdateMessage : public FVirtualLoopMessageBase`  
_L59-79_
- inherits: `FVirtualLoopMessageBase`
- L61 _public prototype_ `FVirtualLoopUpdateMessage() = default;`
- L62 _public prototype_ `FVirtualLoopUpdateMessage(const Trace::IAnalyzer::FOnEventContext& InContext);`
- L64 _public function_ `virtual const FName GetMessageName() const override`
- L65 _public prototype_ `virtual uint32 GetSizeOf() const override;`
- L66 _public prototype_ `virtual FCacheWriteHandler GetCacheWriteHandler() const override;`
- L68 _public member_ `float TimeVirtualized = 0.0f;`
- L69 _public member_ `float PlaybackTime = 0.0f;`
- L70 _public member_ `float UpdateInterval = 0.0f;`
- L72 _public member_ `double LocationX = 0.0;`
- L73 _public member_ `double LocationY = 0.0;`
- L74 _public member_ `double LocationZ = 0.0;`
- L76 _public member_ `double RotatorPitch = 0.0;`
- L77 _public member_ `double RotatorYaw = 0.0;`
- L78 _public member_ `double RotatorRoll = 0.0;`

#### class `UE::Audio::Insights::FVirtualLoopDashboardEntry`  
`class FVirtualLoopDashboardEntry : public FSoundAssetDashboardEntry`  
_L81-101_
- inherits: `FSoundAssetDashboardEntry`
- L84 _public prototype_ `FVirtualLoopDashboardEntry() = default;`
- L85 _public prototype_ `virtual ~FVirtualLoopDashboardEntry() = default;`
- L87 _public function_ `virtual bool IsValid() const override`
- L92 _public member_ `uint32 PlayOrder = static_cast<uint32>(INDEX_NONE);`
- L93 _public member_ `uint64 ComponentId = TNumericLimits<uint64>::Max();`
- L95 _public member_ `float TimeVirtualized = 0.0f;`
- L96 _public member_ `float PlaybackTime = 0.0f;`
- L97 _public member_ `float UpdateInterval = 0.0f;`
- L99 _public member_ `FVector Location = FVector::ZeroVector;`
- L100 _public member_ `FRotator Rotator = FRotator::ZeroRotator;`

#### class `UE::Audio::Insights::FVirtualLoopMessages`  
`class FVirtualLoopMessages`  
_L103-110_
- L105 _private member_ `TAnalyzerMessageQueue<FVirtualLoopVirtualizeMessage> VirtualizeMessages;`
- L106 _private member_ `TAnalyzerMessageQueue<FVirtualLoopStopOrRealizeMessage> StopOrRealizeMessages;`
- L107 _private member_ `TAnalyzerMessageQueue<FVirtualLoopUpdateMessage> UpdateMessages;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Audio` (scope `UE`)
- L16 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L18 _namespace_ `namespace VirtualLoopMessageNames` (scope `UE::Audio::Insights`)
- L20 _externvar_ `extern const FName Virtualize;` (scope `UE::Audio::Insights::VirtualLoopMessageNames`)
- L21 _externvar_ `extern const FName StopOrRealize;` (scope `UE::Audio::Insights::VirtualLoopMessageNames`)
- L22 _externvar_ `extern const FName Update;` (scope `UE::Audio::Insights::VirtualLoopMessageNames`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Providers/AssetProvider.h` (Public)


#### class `UE::Audio::Insights::TAssetProvider`  
`template <typename TAsset> class TAssetProvider`  
_L18-162_
- L21 _public function_ `TAssetProvider()`
- L35 _public function_ `virtual ~TAssetProvider()`
- L50 _public function_ `void RequestEntriesUpdate()`
- L55 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetAdded, const FString& );`
- L56 _public member_ `FOnAssetAdded OnAssetAdded;`
- L58 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetRemoved, const FString& );`
- L59 _public member_ `FOnAssetRemoved OnAssetRemoved;`
- L61 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetListUpdated, const TArray<FString>& );`
- L62 _public member_ `FOnAssetListUpdated OnAssetListUpdated;`
- L65 _private function_ `void UpdateAssetNames()`
- L90 _private function_ `void AddAssetPath(const FString& InAssetPath, const bool bInShouldNotify)`
- L109 _private function_ `void RemoveAssetPath(const FString& InAssetPath)`
- L118 _private function_ `void HandleOnAssetAdded(const FAssetData& InAssetData)`
- L127 _private function_ `void HandleOnAssetRemoved(const FAssetData& InAssetData)`
- L135 _private function_ `void HandleOnFilesLoaded()`
- L141 _private function_ `void HandleOnActiveAudioDeviceCreated(::Audio::FDeviceId InDeviceId)`
- L146 _private function_ `void HandleOnActiveAudioDeviceDestroyed(::Audio::FDeviceId InDeviceId)`
- L154 _private function_ `void HandleOnTraceStarted(FTraceAuxiliary::EConnectionType TraceType, const FString& TraceDestination)`
- L159 _private member_ `bool bAreFilesLoaded = false;`
- L161 _private member_ `TArray<FString> AssetPaths;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Audio` (scope `UE`)
- L15 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L55 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetAdded, const FString& );`
- L58 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetRemoved, const FString& );`
- L61 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetListUpdated, const TArray<FString>& );`
- L83 _function_ `` (scope `UE::Audio::Insights::TAssetProvider::UpdateAssetNames`)
- L94 _function_ `` (scope `UE::Audio::Insights::TAssetProvider::AddAssetPath`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Settings/AudioEventLogSettings.h` (Public)


#### struct `FAudioEventLogCustomEvents`  
`struct FAudioEventLogCustomEvents`  
_L18-28_
- reflection: `USTRUCT()`
- desc: FAudioEventLogCustomEvents Custom event types that can be filtered by in the Event Log
- L27 _public member_ `TSet<FString> EventNames;` — `UPROPERTY(EditAnywhere, config, Category = EventLog, meta = (DisplayName = "Custom event names"))` — The names of any custom events that can be sent to the Event Log. This should match the event name used to send the event to the Event Log.

#### struct `FAudioEventLogVisibleColumns`  
`struct FAudioEventLogVisibleColumns : public FVisibleColumnsSettings`  
_L35-70_
- reflection: `USTRUCT()`
- inherits: `FVisibleColumnsSettings`
- desc: FAudioEventLogVisibleColumns Control which columns are visible in the Audio Event Log tab.
- L40 _public member_ `bool bCacheStatus = true;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L43 _public member_ `bool bMessageID = false;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L46 _public member_ `bool bTimestamp = true;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L49 _public member_ `bool bPlayOrder = true;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L52 _public member_ `bool bEvent = true;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L55 _public member_ `bool bAsset = true;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L58 _public member_ `bool bActor = true;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L61 _public member_ `bool bAudioComponent = false;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L64 _public member_ `bool bCategory = true;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)`
- L66 _public function_ `virtual const FProperty* FindProperty(const FName& PropertyName) const override`

#### struct `FAudioEventLogSettings`  
`struct FAudioEventLogSettings`  
_L73-105_
- reflection: `USTRUCT()`
- L79 _public member_ `TSet<FString> EventFilters;` — `UPROPERTY(config, meta = (HideInDetailPanel))` — Which event types are being filtered by in the Event Log - hidden in the Editor Preferences
- L86 _public member_ `TMap<FString, FAudioEventLogCustomEvents> CustomCategoriesToEvents;` — `UPROPERTY(EditAnywhere, config, Category = EventLog, meta = (DisplayName = "Custom Event Log categories"))` — Categories for custom events being sent to the Audio Insights Event Log. These categories and events will appear in the event filter menu.
- L90 _public member_ `FAudioEventLogVisibleColumns VisibleColumns;` — `UPROPERTY(EditAnywhere, config, Category = EventLog)` — Visibility of columns in the Event Log tab
- L93 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadEventLogSettings, const FAudioEventLogSettings&);`
- L94 _public member_ `static FOnReadEventLogSettings OnReadSettings;`
- L96 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWriteEventLogSettings, FAudioEventLogSettings&);`
- L97 _public member_ `static FOnWriteEventLogSettings OnWriteSettings;`
- L99 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRequestReadEventLogSettings);`
- L100 _public member_ `static FOnRequestReadEventLogSettings OnRequestReadSettings;`
- L102 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRequestWriteEventLogSettings);`
- L103 _public member_ `static FOnRequestWriteEventLogSettings OnRequestWriteSettings;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "AudioInsights"`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadEventLogSettings, const FAudioEventLogSettings&);`
- L96 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWriteEventLogSettings, FAudioEventLogSettings&);`
- L99 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRequestReadEventLogSettings);`
- L102 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRequestWriteEventLogSettings);`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Settings/CacheSettings.h` (Public)


#### enum `EStopCacheWhenPausedBehaviour`  
`enum class EStopCacheWhenPausedBehaviour : uint8`  
_L15-25_
- reflection: `UENUM()`
- desc: EStopCacheWhenPausedBehaviour Controls whether the cache stops collecting new data when paused.
- L18 _public enumerator_ `WhenMarkedForDeletion UMETA(DisplayName = "When marked for deletion")` — Stops caching new data when the cache playhead is paused in the cache region marked for deletion.
- L21 _public enumerator_ `Always UMETA(DisplayName = "Always")` — Always stops caching new data when paused.
- L24 _public enumerator_ `Never UMETA(DisplayName = "Never")` — Never stops caching new data. When the cache playhead is paused in the cache region being deleted, the cache will resume.

#### struct `FCacheSettings`  
`struct FCacheSettings`  
_L28-72_
- reflection: `USTRUCT()`
- L32 _public member_ `static constexpr uint32 MinCacheSizeMB = 8u;`
- L33 _public member_ `static constexpr uint32 MaxCacheSizeMB = 512u;`
- L34 _public member_ `static constexpr uint32 DefaultCacheSizeMB = 32u;`
- L36 _public member_ `static constexpr float MinNudgeStepSeconds = 0.1f;`
- L37 _public member_ `static constexpr float MaxNudgeStepSeconds = 5.0f;`
- L38 _public member_ `static constexpr float DefaultNudgeStepSeconds = 0.5f;`
- L40 _public member_ `static constexpr EStopCacheWhenPausedBehaviour DefaultStopCacheWhenPausedBehaviour = EStopCacheWhenPausedBehaviour::WhenMarkedForDeletion;`
- L44 _public member_ `bool bShowCacheStats = true;` — `UPROPERTY(EditAnywhere, config, Category = Cache)` — Whether to show cache stats in the Audio Insights toolbar.
- L50 _public member_ `EStopCacheWhenPausedBehaviour StopCacheWhenPausedBehaviour = DefaultStopCacheWhenPausedBehaviour;` — `UPROPERTY(EditAnywhere, config, Category = Cache, meta = ( DisplayName = "Stop Cache When Paused", ToolTip = "Controls whether the cache stops collecting new data when paused."))` — When the time marker is paused, controls whether the cache also stops collecting new data.
- L59 _public member_ `uint32 CacheSizeMB = DefaultCacheSizeMB;` — `UPROPERTY(EditAnywhere, config, Category = Cache, meta = ( DisplayName = "Cache Size", ToolTip = "Maximum cache size in megabytes (default: 32). Changing this value will reset the current cache.", ClampMin = "8", UIMin = "8", ClampMax = "512", UIMax = "512", Units = "Megabytes"))` — Maximum cache size. Changing this value will reset the current cache.
- L68 _public member_ `float NudgeStepSeconds = DefaultNudgeStepSeconds;` — `UPROPERTY(EditAnywhere, config, Category = Cache, meta = ( DisplayName = "Cache Nudge Step", ToolTip = "Amount in seconds the cache playhead moves when nudged back or forward (default: 0.5).", ClampMin = "0.1", UIMin = "0.1", ClampMax = "5.0", UIMax = "5.0", Units = "Seconds"))` — Amount the cache playhead moves when nudged back or forward.
- L70 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCacheSizeSettingsChanged);`
- L71 _public member_ `static FOnCacheSizeSettingsChanged OnCacheSizeSettingsChanged;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCacheSizeSettingsChanged);`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Settings/OutputMeterDashboardSettings.h` (Public)


#### struct `FOutputMeterDashboardSettings`  
`struct FOutputMeterDashboardSettings`  
_L7-22_
- reflection: `USTRUCT()`
- L12 _public member_ `float LoudnessMetersSlotSize = 0.75f;` — `UPROPERTY(config)`
- L15 _public member_ `float RMSMeterSlotSize = 0.25f;` — `UPROPERTY(config)`
- L18 _public member_ `bool bLoudnessMetersCollapsed = false;` — `UPROPERTY(config)`
- L21 _public member_ `bool bRMSMeterCollapsed = false;` — `UPROPERTY(config)`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Settings/SignalFlowSettings.h` (Public)


#### enum `ESignalFlowJustification`  
`enum class ESignalFlowJustification : uint8`  
_L20-27_
- reflection: `UENUM(BlueprintType)`
- desc: ESignalFlowJustification Where the nodes in the signal flow graph are aligned
- L23 _public enumerator_ `Edge UMETA(DisplayName = "Edge")` — Position nodes towards one edge of the graph
- L26 _public enumerator_ `Center UMETA(DisplayName = "Center")` — Position nodes around the center of the graph

#### struct `FSignalFlowNodeDetailFilterSettings`  
`struct FSignalFlowNodeDetailFilterSettings`  
_L30-84_
- reflection: `USTRUCT()`
- L34 _public prototype_ `bool GetParameterIsVisible(const UE::Audio::Insights::ESignalFlowNodeDetailParam Param) const;`
- L35 _public prototype_ `int32 GetNumVisibleParams(const TSet<UE::Audio::Insights::ESignalFlowNodeDetailParam>& IgnoredParams = TSet<UE::Audio::Insights::ESignalFlowNodeDetailParam>()) const;`
- L36 _public prototype_ `ECheckBoxState GetShowAllNodeDetailFiltersCheckboxState() const;`
- L38 _public prototype_ `void ToggleEnableAllNodeDetailFilters();`
- L39 _public prototype_ `void SetParameterVisibility(const UE::Audio::Insights::ESignalFlowNodeDetailParam Param, const bool bIsVisible);`
- L43 _public member_ `bool bAmplitude = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of amplitude parameters.
- L47 _public member_ `bool bVolume = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of volume parameters.
- L51 _public member_ `bool bPitch = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of pitch parameters.
- L55 _public member_ `bool bLPFFreq = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of low pass filter frequency parameters.
- L59 _public member_ `bool bHPFFreq = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of high pass filter frequency parameters.
- L63 _public member_ `bool bPriority = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of priority parameters.
- L67 _public member_ `bool bDistance = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of distance parameters.
- L71 _public member_ `bool bDistanceOcclusionAttenuation = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of distance/occlusion attenuation parameters.
- L75 _public member_ `bool bRelativeRenderCost = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of relative render cost parameters.
- L79 _public member_ `bool bAudioComponentName = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of audio component name on sound source nodes.
- L83 _public member_ `bool bSendOutputVolume = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of send output volume parameters on node output pins.

#### struct `FSignalFlowEntryTypeListExpansionSettings`  
`struct FSignalFlowEntryTypeListExpansionSettings`  
_L87-119_
- reflection: `USTRUCT()`
- L93 _public member_ `bool bShowActiveOwnerObjects = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles expansion of the left hand Active Owner Objects menu.
- L97 _public member_ `bool bShowActiveSources = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles expansion of the left hand Active Sources menu.
- L101 _public member_ `bool bShowActiveBuses = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles expansion of the left hand Active Buses menu.
- L105 _public member_ `bool bShowActiveSubmixes = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles expansion of the left hand Active Submixes menu.
- L109 _public member_ `float OwnerObjectsSlotSize = 1.0f;` — `UPROPERTY(config)` — Internal settings: persisted height ratios for the category splitter slots
- L112 _public member_ `float SourcesSlotSize = 2.5f;` — `UPROPERTY(config)`
- L115 _public member_ `float BusesSlotSize = 1.0f;` — `UPROPERTY(config)`
- L118 _public member_ `float SubmixesSlotSize = 1.5f;` — `UPROPERTY(config)`

#### struct `FSignalFlowSettings`  
`struct FSignalFlowSettings`  
_L122-191_
- reflection: `USTRUCT()`
- L128 _public member_ `EAudioAmplitudeDisplayMode AmplitudeDisplayMode = EAudioAmplitudeDisplayMode::Decibels;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow, meta = (DisplayName = "Amp (Peak) Display Mode"))` — Toggles between decibel/linear scales when displaying amplitude (peak) values inside the signal flow graph.
- L132 _public member_ `bool bHorizontalFlow = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles between horizontally/vertically orienting the Signal Flow graph.
- L136 _public member_ `bool bPauseGraphOnSelect = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles pausing the graph at the current timestamp when selecting a node.
- L140 _public member_ `ESignalFlowJustification GraphJustification = ESignalFlowJustification::Edge;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow, meta = (DisplayName = "Graph Justification"))` — Where the nodes in the signal flow graph are aligned
- L144 _public member_ `bool bShowNodeDetails = false;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles visibility of node details.
- L148 _public member_ `FSignalFlowNodeDetailFilterSettings NodeDetailFilters;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Which parameter types are visible in the Signal Flow graph when Node Details is enabled
- L152 _public member_ `FSignalFlowEntryTypeListExpansionSettings ActiveEntryMenuExpansionSettings;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow, meta = (DisplayName = "Active Entry Menu Expansion"))` — Expansion settings for the Active Entry menus on the left hand side of the Signal Flow Tab
- L156 _public member_ `bool bAnimateWires = true;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow)` — Toggles whether connection wire animations driven by amplitude envelope values are enabled in the Signal Flow graph.
- L160 _public member_ `float WireSplineAmplitudePowerFactor = 0.4f;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow, meta = (UIMin = "0.1", UIMax = "1.0", ClampMin = "0.1", ClampMax = "1.0"))` — Power factor applied to amplitude values when drawing animated signal flow connection wires. Controls how much additional weight is applied to quieter nodes.
- L164 _public member_ `float WireSplineMaxThicknessScalar = 14.0f;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow, meta = (UIMin = "1.0", UIMax = "40.0", ClampMin = "1.0", ClampMax = "40.0"))` — The maximum thickness multiplier applied to animated signal flow connection wires when a node is at high amplitudes.
- L168 _public member_ `float GraphWidthRatio = 0.8f;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow, meta = (UIMin = "0.25", UIMax = "1.0", ClampMin = "0.25", ClampMax = "1.0"))` — Ratio of the horizontal space allocated to the Signal Flow graph (vs. the selection panel on the left).
- L172 _public member_ `float LargeNodePadding = 128.0f;` — `UPROPERTY(config, meta = (ClampMin = "0.25", ClampMax = "500.0"))` — Padding applied between nodes along the flow direction of the Signal Flow graph.
- L176 _public member_ `float SmallNodePadding = 8.0f;` — `UPROPERTY(config, meta = (ClampMin = "0.25", ClampMax = "500.0"))` — Padding applied between nodes perpendicular to the flow direction of the Signal Flow graph.
- L179 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadSignalFlowSettings, const FSignalFlowSettings&);`
- L180 _public member_ `static FOnReadSignalFlowSettings OnReadSettings;`
- L182 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWriteSignalFlowSettings, FSignalFlowSettings&);`
- L183 _public member_ `static FOnWriteSignalFlowSettings OnWriteSettings;`
- L185 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRequestReadSignalFlowSettings);`
- L186 _public member_ `static FOnRequestReadSignalFlowSettings OnRequestReadSettings;`
- L188 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRequestWriteSignalFlowSettings);`
- L189 _public member_ `static FOnRequestWriteSignalFlowSettings OnRequestWriteSettings;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "AudioInsights"`
- L179 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadSignalFlowSettings, const FSignalFlowSettings&);`
- L182 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWriteSignalFlowSettings, FSignalFlowSettings&);`
- L185 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRequestReadSignalFlowSettings);`
- L188 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRequestWriteSignalFlowSettings);`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Settings/SoundDashboardSettings.h` (Public)


#### enum `EAudioAmplitudeDisplayMode`  
`enum class EAudioAmplitudeDisplayMode : uint8`  
_L19-26_
- reflection: `UENUM(BlueprintType)`
- desc: EAudioAmplitudeDisplayMode The units that audio amplitude and volume values are displayed in
- L22 _public enumerator_ `Decibels UMETA(DisplayName = "dB")` — Displays amplitude values in decibels.
- L25 _public enumerator_ `Linear UMETA(DisplayName = "Linear")` — Displays amplitude values in linear scale.

#### enum `ESoundDashboardTreeViewingOptions`  
`enum class ESoundDashboardTreeViewingOptions : uint8`  
_L33-43_
- reflection: `UENUM(BlueprintType)`
- desc: ESoundDashboardTreeViewingOptions Change how sounds are organized within the Sound Dashboard tab in Audio Insights.
- L36 _public enumerator_ `FullTree UMETA(DisplayName = "Tree View")` — Organize sounds into categories.
- L39 _public enumerator_ `ActiveSounds UMETA(DisplayName = "Active Sounds")` — Organize sounds into Active Sounds.
- L42 _public enumerator_ `FlatList UMETA(DisplayName = "Flat List")` — Display sounds as individual waves in a flat list.

#### enum `ESoundDashboardAutoExpandOptions`  
`enum class ESoundDashboardAutoExpandOptions : uint8`  
_L50-60_
- reflection: `UENUM(BlueprintType)`
- desc: ESoundDashboardAutoExpandOptions Control whether new sounds entering the Sound Dashboard are auto-expanded/collapsed by default.
- L53 _public enumerator_ `Categories UMETA(DisplayName = "Categories")` — Auto-expand new categories.
- L56 _public enumerator_ `Everything UMETA(DisplayName = "Everything")` — Auto-expand all new categories and sounds.
- L59 _public enumerator_ `Nothing UMETA(DisplayName = "Nothing")` — Don't auto-expand anything.

#### struct `FSoundDashboardVisibleColumns`  
`struct FSoundDashboardVisibleColumns : public FVisibleColumnsSettings`  
_L63-122_
- reflection: `USTRUCT()`
- inherits: `FVisibleColumnsSettings`
- L68 _public member_ `bool bMute = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L71 _public member_ `bool bSolo = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L74 _public member_ `bool bPlot = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L77 _public member_ `bool bName = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L80 _public member_ `bool bPlayOrder = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L83 _public member_ `bool bPriority = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L86 _public member_ `bool bDistance = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L89 _public member_ `bool bDistanceAttenuation = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L92 _public member_ `bool bAmplitude = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (DisplayName = "Amp (Peak)"))`
- L95 _public member_ `bool bVolume = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L98 _public member_ `bool bLPFFreq = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (DisplayName = "LPF Freq"))`
- L101 _public member_ `bool bHPFFreq = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (DisplayName = "HPF Freq"))`
- L104 _public member_ `bool bPitch = true;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L107 _public member_ `bool bRelativeRenderCost = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L110 _public member_ `bool bActorLabel = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L113 _public member_ `bool bAudioComponentName = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L116 _public member_ `bool bCategory = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L118 _public function_ `virtual const FProperty* FindProperty(const FName& PropertyName) const override`

#### struct `FSoundPlotsDashboardPlotRanges`  
`struct FSoundPlotsDashboardPlotRanges`  
_L125-191_
- reflection: `USTRUCT()`
- L131 _public member_ `bool bUseCustomAmplitude_dBRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L134 _public member_ `FFloatInterval Amplitude_dB = { MIN_VOLUME_DECIBELS, 0.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomAmplitude_dBRange", UIMin = "-160", UIMax = "0", ClampMin = "-160", ClampMax = "24", DisplayName = "Amplitude (dB)"))`
- L138 _public member_ `bool bUseCustomAmplitude_LinearRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L141 _public member_ `FFloatInterval Amplitude_Linear = { 0.0f, 1.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomAmplitude_LinearRange", UIMin = "0", UIMax = "1", ClampMin = "-16", ClampMax = "16", DisplayName = "Amplitude (Linear)"))`
- L145 _public member_ `bool bUseCustomVolumeRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L148 _public member_ `FFloatInterval Volume = { 0.0f, 1.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomVolumeRange", UIMin = "0", UIMax = "4", ClampMin = "0", ClampMax = "4"))`
- L152 _public member_ `bool bUseCustomDistanceRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L155 _public member_ `FFloatInterval Distance = { 0.0f, 10000.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomDistanceRange", UIMin = "0", UIMax = "10000", ClampMin = "0", ClampMax = "100000"))`
- L159 _public member_ `bool bUseCustomDistanceAttenuationRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L162 _public member_ `FFloatInterval DistanceAttenuation = { 0.0f, 1.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomDistanceAttenuationRange", UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L166 _public member_ `bool bUseCustomPitchRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L169 _public member_ `FFloatInterval Pitch = { 0.125f, 4.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomPitchRange", UIMin = "0.125", UIMax = "4", ClampMin = "0", ClampMax = "32", Units = "Multiplier"))`
- L173 _public member_ `bool bUseCustomPriorityRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L176 _public member_ `FFloatInterval Priority = { 0.0f, 100.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomPriorityRange", UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "100"))`
- L180 _public member_ `bool bUseCustomLPFFreqRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L183 _public member_ `FFloatInterval LPFFreq = { 20.0f, 20000.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomLPFFreqRange", UIMin = "20", UIMax = "20000", DisplayName = "LPF Freq", ClampMin = "0", ClampMax = "48000", Units = "Hertz"))`
- L187 _public member_ `bool bUseCustomHPFFreqRange = false;` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (InlineEditConditionToggle))`
- L190 _public member_ `FFloatInterval HPFFreq = { 20.0f, 20000.0f };` — `UPROPERTY(EditAnywhere, config, Category = "SoundDashboard|CustomPlotRanges", meta = (EditCondition = "bUseCustomHPFFreqRange", UIMin = "20", UIMax = "20000", DisplayName = "HPF Freq", ClampMin = "0", ClampMax = "48000", Units = "Hertz"))`

#### struct `FSoundDashboardSettings`  
`struct FSoundDashboardSettings`  
_L194-232_
- reflection: `USTRUCT()`
- L199 _public member_ `EAudioAmplitudeDisplayMode AmplitudeDisplayMode = EAudioAmplitudeDisplayMode::Decibels;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (DisplayName = "Amp (Peak) Display Mode"))`
- L202 _public member_ `ESoundDashboardTreeViewingOptions TreeViewMode = ESoundDashboardTreeViewingOptions::FullTree;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (DisplayName = "View"))`
- L205 _public member_ `ESoundDashboardAutoExpandOptions AutoExpandMode = ESoundDashboardAutoExpandOptions::Categories;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (DisplayName = "Auto-Expand"))`
- L208 _public member_ `bool bShowStoppedSounds = false;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (DisplayName = "Show Stopped Sounds"))`
- L211 _public member_ `float StoppedSoundTimeoutTime = 3.0f;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (ClampMin = "0", DisplayName = "Recently Stopped Sounds Timeout"))`
- L214 _public member_ `FSoundDashboardVisibleColumns VisibleColumns;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard)`
- L217 _public member_ `FSoundPlotsDashboardPlotRanges DefaultPlotRanges;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (ShowOnlyInnerProperties))`
- L220 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadSoundDashboardSettings, const FSoundDashboardSettings&);`
- L221 _public member_ `static FOnReadSoundDashboardSettings OnReadSettings;`
- L223 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWriteSoundDashboardSettings, FSoundDashboardSettings&);`
- L224 _public member_ `static FOnWriteSoundDashboardSettings OnWriteSettings;`
- L226 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRequestReadSoundDashboardSettings);`
- L227 _public member_ `static FOnRequestReadSoundDashboardSettings OnRequestReadSettings;`
- L229 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRequestWriteSoundDashboardSettings);`
- L230 _public member_ `static FOnRequestWriteSoundDashboardSettings OnRequestWriteSettings;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "AudioInsights"`
- L220 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReadSoundDashboardSettings, const FSoundDashboardSettings&);`
- L223 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWriteSoundDashboardSettings, FSoundDashboardSettings&);`
- L226 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRequestReadSoundDashboardSettings);`
- L229 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRequestWriteSoundDashboardSettings);`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Settings/VisibleColumnsSettings.h` (Public)


#### struct `FVisibleColumnsSettings`  
`struct FVisibleColumnsSettings`  
_L20-32_
- reflection: `USTRUCT()`
- desc: FVisibleColumnsSettings Helper struct for adding visible column settings to an Audio Insights dashboard Used in conjunction with FVisibleColumnsSettingsMenu to populate a menu with enable/disable checkboxes for the columns in a table/tree Inherit from this in a USTRUCT that contains boolean UPROPERTIES for each column in the table, with names matching the column IDs with a 'b' prefix e.g. Table : | Column01 | Column02 | Column03 | USTRUCT : bColumn01, bColumn02, bColumn03
- L24 _public prototype_ `virtual ~FVisibleColumnsSettings() = default;`
- L26 _public prototype_ `virtual bool GetIsVisible(const FName& ColumnId) const;`
- L27 _public prototype_ `virtual void SetIsVisible(const FName& ColumnId, const bool bIsVisible);`
- L31 _public function_ `virtual const FProperty* FindProperty(const FName& PropertyName) const` — Override in derived class to enable finding properties by name in the derived USTRUCT E.g. return StaticStruct()->FindPropertyByName(PropertyName);

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOINSIGHTS_API`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Settings/VisibleColumnsSettingsMenu.h` (Public)


#### class `UE::Audio::Insights::FVisibleColumnsSettingsMenu`  
`template<TIsVisibleColumnsSettingsType T> class FVisibleColumnsSettingsMenu : public TSharedFromThis<FVisibleColumnsSettingsMenu<T>>`  
_L23-65_
- inherits: `TSharedFromThis<FVisibleColumnsSettingsMenu<T>>`
- desc: FVisibleColumnsSettingsMenu Helper class for creating a settings sub-menu for the visibility of columns in a table Requires a settings USTRUCT that inherits from FVisibleColumnsSettings to be passed in on construction.
- L31 _public function_ `FVisibleColumnsSettingsMenu(TSharedRef<SHeaderRow> InHeaderRowWidget, const T& InVisibleColumnSettings) : HeaderRowWidget(InHeaderRowWidget) , VisibleColumnSettings(InVisibleColumnSettings)` — Constructor @param 	InHeaderRowWidget			Header Row widget from the table (SListView, STreeView, etc.) @param 	InVisibleColumnSettings		A USTRUCT that inherits from FVisibleColumnsSettings, typically to be stored in the Editor Preferences
- L37 _public prototype_ `virtual ~FVisibleColumnsSettingsMenu() = default;`
- L40 _public prototype_ `void BuildVisibleColumnsMenuContent(FMenuBuilder& OutMenuBuilder);` — Pass in a FMenuBuilder object to populate a sub-menu with visible columns settings
- L43 _public prototype_ `void OnHiddenColumnsListChanged();` — Call from SHeaderRow::OnHiddenColumnsListChanged callback to update the settings when the column visibility is changed from the header row
- L46 _public prototype_ `void ReadFromSettings(const T& InVisibleColumnSettings);` — Call to cache/write the current column visibility settings from/to editor preferences
- L47 _public prototype_ `void WriteToSettings(T& OutVisibleColumnSettings);`
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVisibleColumnsSettingsUpdated);` — Delegate that notifies when the cached VisibleColumnSettings have been updated
- L51 _public member_ `FOnVisibleColumnsSettingsUpdated OnVisibleColumnsSettingsUpdated;`
- L54 _private prototype_ `void ToggleColumnVisibility(FName ColumnId);`
- L55 _private prototype_ `void ToggleAllColumnsVisibility();`
- L57 _private prototype_ `void UpdateColumnVisabilityFromSettings(const FVisibleColumnsSettings& InVisibleColumnSettings);`
- L59 _private prototype_ `ECheckBoxState GetIsColumnVisibleCheckedState(FName ColumnId) const;`
- L60 _private prototype_ `ECheckBoxState GetToggleAllColumnsVisibilityCheckState() const;`
- L61 _private prototype_ `FText GetToggleAllColumnsVisibilityText() const;`
- L63 _private member_ `TWeakPtr<SHeaderRow> HeaderRowWidget;`
- L64 _private member_ `TOptional<T> VisibleColumnSettings;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Audio` (scope `UE`)
- L15 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVisibleColumnsSettingsUpdated);` — Delegate that notifies when the cached VisibleColumnSettings have been updated

### `Plugins/AudioInsights/Source/AudioInsights/Public/Settings/VisibleColumnsSettingsMenu.inl` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L12 _function_ `template<TIsVisibleColumnsSettingsType T> inline void FVisibleColumnsSettingsMenu<T>::BuildVisibleColumnsMenuContent(FMenuBuilder& OutMenuBuilder)` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L28 _function_ `FExecuteAction::CreateSP(this, &FVisibleColumnsSettingsMenu::ToggleAllColumnsVisibility), FCanExecuteAction::CreateLambda([]() { return true; }), FGetActionCheckState::CreateSP(this, &FVisibleColumnsSettingsMenu::GetToggleAllColumnsVisibilityCheckState) ), NAME_None, EUserInterfaceActionType::ToggleButton );` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu::BuildVisibleColumnsMenuContent`)
- L45 _function_ `FExecuteAction::CreateSP(this, &FVisibleColumnsSettingsMenu::ToggleColumnVisibility, Column.ColumnId), FCanExecuteAction::CreateLambda([]() { return true; }), FGetActionCheckState::CreateSP(this, &FVisibleColumnsSettingsMenu::GetIsColumnVisibleCheckedState, Column.ColumnId) ), NAME_None, EUserInterfaceActionType::ToggleButton );` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu::BuildVisibleColumnsMenuContent`)
- L55 _function_ `template<TIsVisibleColumnsSettingsType T> inline void FVisibleColumnsSettingsMenu<T>::OnHiddenColumnsListChanged()` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L73 _function_ `template<TIsVisibleColumnsSettingsType T> void FVisibleColumnsSettingsMenu<T>::ReadFromSettings(const T& InVisibleColumnSettings)` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L93 _function_ `template<TIsVisibleColumnsSettingsType T> void FVisibleColumnsSettingsMenu<T>::WriteToSettings(T& OutVisibleColumnSettings)` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L109 _function_ `template<TIsVisibleColumnsSettingsType T> inline void FVisibleColumnsSettingsMenu<T>::ToggleColumnVisibility(FName ColumnId)` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L122 _function_ `template<TIsVisibleColumnsSettingsType T> inline void FVisibleColumnsSettingsMenu<T>::ToggleAllColumnsVisibility()` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L150 _function_ `template<TIsVisibleColumnsSettingsType T> inline void FVisibleColumnsSettingsMenu<T>::UpdateColumnVisabilityFromSettings(const FVisibleColumnsSettings& InVisibleColumnSettings)` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L169 _function_ `template<TIsVisibleColumnsSettingsType T> inline ECheckBoxState FVisibleColumnsSettingsMenu<T>::GetIsColumnVisibleCheckedState(FName ColumnId) const` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L176 _function_ `template<TIsVisibleColumnsSettingsType T> inline ECheckBoxState FVisibleColumnsSettingsMenu<T>::GetToggleAllColumnsVisibilityCheckState() const` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)
- L185 _function_ `const bool bAnyColumnsVisible = Algo::AnyOf(Columns, [](const SHeaderRow::FColumn& Column) { return Column.bIsVisible; });` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu::GetToggleAllColumnsVisibilityCheckState`)
- L186 _function_ `const bool bAnyColumnsInvisible = Algo::AnyOf(Columns, [](const SHeaderRow::FColumn& Column) { return !Column.bIsVisible; });` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu::GetToggleAllColumnsVisibilityCheckState`)
- L203 _function_ `template<TIsVisibleColumnsSettingsType T> inline FText FVisibleColumnsSettingsMenu<T>::GetToggleAllColumnsVisibilityText() const` (scope `UE::Audio::Insights::FVisibleColumnsSettingsMenu`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/TraceWriter/AudioInsightsCacheTraceWriter.h` (Public)


#### class `UE::Audio::Insights::FAudioInsightsCacheTraceWriter`  
`class FAudioInsightsCacheTraceWriter`  
_L18-22_
- L21 _public prototype_ `static bool WriteCacheToFile(const FAudioInsightsCacheManager& InCacheManager, const FString& InFilePath);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Trace` (scope `UE`)
- L12 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Audio` (scope `UE`)
- L14 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/TraceWriter/CacheWriteHandler.h` (Public)


#### struct `UE::Audio::Insights::FCacheWriteHandler`  
`struct FCacheWriteHandler`  
_L15-24_
- L17 _public typedef_ `using FDeclareEventFunc = TFunction<uint32(UE::Trace::FTraceWriter& Writer)>;`
- L18 _public typedef_ `using FWriteEventFunc = TFunction<void(UE::Trace::FTraceWriter& Writer, uint32 EventId, const IAudioCachedMessage& Message, uint64 TimestampCycles)>;`
- L20 _public member_ `FDeclareEventFunc DeclareEvent;`
- L21 _public member_ `FWriteEventFunc WriteEvent;`
- L23 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Trace` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Audio` (scope `UE`)
- L11 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/AssetEditorContextMenuHelper.h` (Public)


#### class `UE::Audio::Insights::FAssetEditorContextMenuHelper`  
`class FAssetEditorContextMenuHelper`  
_L20-41_
- desc: Helper for adding editor-only commands to the context menu of an Audio Insights dashboard
- L23 _public prototype_ `FAssetEditorContextMenuHelper();`
- L25 _public prototype_ `TSharedPtr<SWidget> ContructContextMenuOptions();`
- L26 _public prototype_ `bool ProcessCommandBindings(const FKeyEvent& InKeyEvent) const;`
- L28 _public prototype_ `void SetAssetEntry(const TSharedPtr<IObjectDashboardEntry>& InEntry);`
- L29 _public prototype_ `void ResetAssetEntry();`
- L32 _private prototype_ `void BindCommands();`
- L34 _private prototype_ `bool BrowseToAsset() const;`
- L35 _private prototype_ `bool OpenAsset() const;`
- L37 _private prototype_ `TObjectPtr<UObject> GetEditableAsset() const;`
- L39 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L40 _private member_ `TWeakPtr<IObjectDashboardEntry> Entry;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Audio` (scope `UE`)
- L15 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/AudioBusDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::FAudioBusDashboardViewFactory`  
`class FAudioBusDashboardViewFactory : public FTraceObjectTableDashboardViewFactory`  
_L14-73_
- inherits: `FTraceObjectTableDashboardViewFactory`
- L17 _public prototype_ `FAudioBusDashboardViewFactory();`
- L18 _public prototype_ `virtual ~FAudioBusDashboardViewFactory();`
- L20 _public prototype_ `virtual FName GetName() const override;`
- L21 _public prototype_ `virtual FText GetDisplayName() const override;`
- L22 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L23 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L24 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L34 _protected prototype_ `TSharedRef<SWidget> MakeAudioBusTypeFilterWidget();`
- L36 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(TSharedRef<IDashboardDataViewEntry> InRowData, const FName& InColumnName) override;`
- L37 _protected prototype_ `virtual void ProcessEntries(FTraceTableDashboardViewFactory::EProcessReason Reason) override;`
- L38 _protected prototype_ `virtual const TMap<FName, FTraceTableDashboardViewFactory::FColumnData>& GetColumns() const override;`
- L40 _protected prototype_ `void RebuildAudioMeters() const;`
- L41 _protected prototype_ `bool ShouldUpdateAudioMeter(const FAudioBusDashboardEntry& InAudioBusDashboardEntry) const;`
- L42 _protected prototype_ `void UpdateAudioMeters() const;`
- L43 _protected prototype_ `void ReactivateAudioMeters();`
- L45 _protected prototype_ `void SetAudioBusEnvelopeFollowerEnabled(const FAudioBusDashboardEntry& InAudioBusDashboardEntry, const bool bInEnabled);`
- L47 _protected prototype_ `virtual void SortTable() override;`
- L49 _protected prototype_ `void FilterByAudioBusName();`
- L50 _protected prototype_ `void FilterByAudioBusType();`
- L52 _protected prototype_ `void HandleOnAudioBusAdded(const uint32 InAudioBusId);`
- L53 _protected prototype_ `void HandleOnAudioBusRemoved(const uint32 InAudioBusId);`
- L54 _protected prototype_ `void HandleOnAudioBusStarted(const uint32 InAudioBusId);`
- L56 _protected prototype_ `void HandleOnTimeMarkerUpdated();`
- L57 _protected prototype_ `void HandleOnTimeControlMethodReset();`
- L59 _protected prototype_ `void RequestListRefresh();`
- L61 _protected member_ `TSharedPtr<FAudioBusTraceProvider> AudioBusProvider;`
- L63 _protected member_ `TSet<uint32> CheckedAudioBuses;`
- L64 _protected member_ `TSet<uint32> PendingToReactivateAudioBusIds;`
- L66 _protected member_ `bool bShouldRebuildAudioMeters = false;`
- L67 _protected member_ `bool bListRefreshed = false;`
- L68 _protected member_ `bool bShouldReactivateAudioMeters = false;`
- L70 _protected typedef_ `using FComboboxSelectionItem = TPair<EAudioBusTypeComboboxSelection, FText>;`
- L71 _protected member_ `TArray<TSharedPtr<FComboboxSelectionItem>> AudioBusTypes;`
- L72 _protected member_ `TSharedPtr<FComboboxSelectionItem> SelectedAudioBusType;`

#### enum `UE::Audio::Insights::FAudioBusDashboardViewFactory::EAudioBusTypeComboboxSelection`  
`enum class EAudioBusTypeComboboxSelection : uint8`  
_L27-32_
- L29 _public enumerator_ `AssetBased`
- L30 _public enumerator_ `CodeGenerated`
- L31 _public enumerator_ `All`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/AudioEventLogDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::FAudioEventLogFilter`  
`class FAudioEventLogFilter : public FGenericFilter<FEventLogFilterID>`  
_L19-49_
- inherits: `FGenericFilter<FEventLogFilterID>`
- L22 _public function_ `FAudioEventLogFilter ( const FEventLogFilterID InFilterID, const FString& InName, const FText& InDisplayName, const FName& InIconName, const FText& InToolTipText, FLinearColor InColor, TSharedPtr<FFilterCategory> InCategory ) : FGenericFilter<FEventLogFilterID>(InCategory, InName, InDisplayName, FGenericFilter<FEventLogFilterID>::FOnItemFiltered()) , FilterID(InFilterID)`
- L40 _public function_ `bool IsActive() const`
- L41 _public function_ `FEventLogFilterID GetFilterID() const`
- L44 _private function_ `virtual void ActiveStateChanged(bool bActive) override`
- L45 _private function_ `virtual bool PassesFilter(FEventLogFilterID InItem) const override`
- L47 _private member_ `const FEventLogFilterID FilterID;`
- L48 _private member_ `bool bIsActive = false;`

#### class `UE::Audio::Insights::FAudioEventLogDashboardViewFactory`  
`class FAudioEventLogDashboardViewFactory : public FTraceObjectTableDashboardViewFactory`  
_L51-157_
- inherits: `FTraceObjectTableDashboardViewFactory`
- L54 _public prototype_ `FAudioEventLogDashboardViewFactory();`
- L55 _public prototype_ `virtual ~FAudioEventLogDashboardViewFactory();`
- L57 _public prototype_ `static const TMap<FString, TSet<FString>> GetInitEventTypeFilters();`
- L59 _public prototype_ `void RegisterExternalEventTypes(const TMap<FString, TSet<FString>>& InCategoriesToEvents);`
- L60 _public prototype_ `void RegisterExternalDisplayNames(const TMap<FString, FText>& InDisplayNames);`
- L62 _public prototype_ `virtual FName GetName() const override;`
- L63 _public prototype_ `virtual FText GetDisplayName() const override;`
- L64 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L65 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L67 _public prototype_ `virtual FReply OnDataRowKeyInput(const FGeometry& Geometry, const FKeyEvent& KeyEvent) const override;`
- L68 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L69 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(TSharedRef<IDashboardDataViewEntry> InRowData, const FName& Column) override;`
- L70 _public prototype_ `virtual void RefreshFilteredEntriesListView() override;`
- L73 _protected prototype_ `virtual void ProcessEntries(FTraceTableDashboardViewFactory::EProcessReason Reason) override;`
- L74 _protected prototype_ `virtual const TMap<FName, FTraceTableDashboardViewFactory::FColumnData>& GetColumns() const override;`
- L76 _protected prototype_ `virtual void SortTable() override;`
- L77 _protected prototype_ `virtual bool IsColumnSortable(const FName& ColumnId) const override;`
- L78 _protected prototype_ `void OnHiddenColumnsListChanged() override;`
- L80 _protected prototype_ `virtual TSharedPtr<SWidget> CreateFilterBarButtonWidget() override;`
- L81 _protected prototype_ `virtual TSharedRef<SWidget> CreateFilterBarWidget() override;`
- L83 _protected prototype_ `virtual TSharedRef<SWidget> CreateSettingsButtonWidget() override;`
- L84 _protected prototype_ `virtual TSharedRef<SWidget> OnGetSettingsMenuContent() override;`
- L85 _protected prototype_ `virtual FText OnGetSettingsMenuToolTip() override;`
- L87 _protected prototype_ `virtual TSharedPtr<SWidget> OnConstructContextMenu() override;`
- L89 _protected prototype_ `virtual void OnSelectionChanged(TSharedPtr<IDashboardDataViewEntry> SelectedItem, ESelectInfo::Type SelectInfo) override;`
- L90 _protected function_ `virtual bool ClearSelectionOnClick() const override`
- L91 _protected function_ `virtual bool EnableHorizontalScrollBox() const override`
- L92 _protected prototype_ `virtual void OnListViewScrolled(double InScrollOffset) override;`
- L93 _protected prototype_ `virtual void OnFinishedScrolling();`
- L94 _protected prototype_ `virtual const FTableRowStyle* GetRowStyle() const override;`
- L97 _protected function_ `virtual TSharedRef<SWidget> MakeAssetMenuBar() const override`
- L101 _private prototype_ `void OnAnalysisStarting(const double Timestamp);`
- L103 _private prototype_ `void UpdateCustomEventLogFilters(const IDashboardDataViewEntry& Entry);`
- L104 _private prototype_ `TSharedRef<FAudioEventLogFilter> CreateNewEventFilterType(const TSharedPtr<FFilterCategory>& FilterCategory, const FString& EventType);`
- L105 _private prototype_ `const TSharedPtr<FFilterCategory>& FindOrAddFilterCategory(const FString& CategoryName);`
- L106 _private prototype_ `bool PassesEventTypeFilter(const FEventLogFilterID EventLogID) const;`
- L108 _private prototype_ `void BuildVisibleColumnsMenuContent(FMenuBuilder& MenuBuilder);`
- L110 _private prototype_ `void SortByPredicate(TFunctionRef<bool(const class FAudioEventLogDashboardEntry&, const class FAudioEventLogDashboardEntry&)> Predicate);`
- L113 _private prototype_ `void OnReadEditorSettings(const FAudioEventLogSettings& InSettings);`
- L114 _private prototype_ `void OnWriteEditorSettings(FAudioEventLogSettings& OutSettings);`
- L116 _private prototype_ `void RemoveDeletedCustomEvents(const TMap<FString, FAudioEventLogCustomEvents>& CustomEventsFromSettings);`
- L117 _private prototype_ `void AddNewCustomEvents(const TMap<FString, FAudioEventLogCustomEvents>& CustomEventsFromSettings);`
- L119 _private prototype_ `void RefreshFilterBarFromSettings(const TSet<FString>& EventFilters);`
- L122 _private prototype_ `void OnTimingViewTimeMarkerChanged(double InTimeMarker);`
- L123 _private prototype_ `void OnTimeControlMethodReset();`
- L125 _private prototype_ `void BindCommands();`
- L126 _private prototype_ `void ClearInspectState();`
- L127 _private prototype_ `void ResetInspectTimestamp();`
- L129 _private prototype_ `void ClearActiveAudioDeviceEntries();`
- L131 _private prototype_ `void OnUpdateAutoScroll();`
- L133 _private prototype_ `double GetTimestampRelativeToAnalysisStart(const double Timestamp) const;`
- L135 _private member_ `TSharedPtr<FAudioEventLogTraceProvider> AudioEventLogTraceProvider;`
- L137 _private member_ `TSharedPtr<SWidget> DashboardWidget;`
- L138 _private member_ `TSharedPtr<SAudioFilterBar<FEventLogFilterID>> FilterBar;`
- L140 _private member_ `TSharedPtr<SWidget> SettingsAreaWidget;`
- L142 _private member_ `TMap<FString, TSharedPtr<FFilterCategory>> FilterCategories;`
- L143 _private member_ `TMap<FString, FEventLogFilterID> EventFilterTypes;`
- L145 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L146 _private member_ `TSharedPtr<FVisibleColumnsSettingsMenu<FAudioEventLogVisibleColumns>> VisibleColumnsSettingsMenu;`
- L148 _private member_ `TWeakPtr<IDashboardDataViewEntry> FocusedItem;`
- L150 _private member_ `const TMap<FString, TSet<FString>> InitEventTypeFilters;`
- L151 _private member_ `TMap<FString, FAudioEventLogCustomEvents> CachedCustomEventSettings;`
- L152 _private member_ `TMap<FString, TSet<FString>> ExternalEventTypeFilters;`
- L153 _private member_ `TMap<FString, FText> ExternalDisplayNames;`
- L155 _private member_ `double BeginTimestamp = 0.0;`
- L156 _private member_ `bool bAutoScroll = true;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Audio` (scope `UE`)
- L13 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L17 _typedef_ `using FEventLogFilterID = int32;` (scope `UE::Audio::Insights`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/AudioMetersPanelDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::FAudioMetersPanelDashboardViewFactory`  
`class FAudioMetersPanelDashboardViewFactory : public IDashboardViewFactory, public TSharedFromThis<FAudioMetersPanelDashboardViewFactory>`  
_L17-39_
- inherits: `IDashboardViewFactory,TSharedFromThis<FAudioMetersPanelDashboardViewFactory>`
- L20 _public prototype_ `FAudioMetersPanelDashboardViewFactory();`
- L21 _public prototype_ `virtual ~FAudioMetersPanelDashboardViewFactory();`
- L23 _public prototype_ `virtual FName GetName() const override;`
- L24 _public prototype_ `virtual FText GetDisplayName() const override;`
- L25 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L26 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L30 _private prototype_ `void HandleOnAddAudioMeter(const uint32 InEntryId, const TSharedRef<FAudioMeterInfo>& InAudioMeterInfo, const FText& InName, const FSlateColor& InNameColor);`
- L31 _private prototype_ `void HandleOnRemoveAudioMeter(const uint32 InEntryId);`
- L32 _private prototype_ `void HandleOnUpdateAudioMeterInfo(const uint32 InEntryId, const TSharedRef<FAudioMeterInfo>& InAudioMeterInfo, const FText& InName);`
- L34 _private prototype_ `void AddAudioMeterView(const TSharedRef<SAudioMeterView>& InAudioMeterView);`
- L36 _private member_ `TSharedPtr<SScrollBox> AudioMeterWidgetsScrollBox;`
- L37 _private member_ `TSharedPtr<SHorizontalBox> AudioMeterWidgetsContainer;`
- L38 _private member_ `TMap<uint32, TSharedRef<SAudioMeterView>> AudioMeterViews;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Audio` (scope `UE`)
- L12 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/DashboardViewFactory.h` (Public)


#### enum `UE::Audio::Insights::EDefaultDashboardTabStack`  
`enum class EDefaultDashboardTabStack : uint8`  
_L19-28_
- L21 _public enumerator_ `Viewport`
- L22 _public enumerator_ `Log`
- L23 _public enumerator_ `Analysis`
- L24 _public enumerator_ `AudioMeters`
- L25 _public enumerator_ `Plots`
- L26 _public enumerator_ `OutputMetering`
- L27 _public enumerator_ `AudioAnalyzerRack`

#### class `UE::Audio::Insights::IDashboardViewFactory`  
`class IDashboardViewFactory`  
_L30-40_
- L33 _public prototype_ `virtual ~IDashboardViewFactory() = default;`
- L35 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const = 0;`
- L36 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L37 _public prototype_ `virtual FName GetName() const = 0;`
- L38 _public prototype_ `virtual FSlateIcon GetIcon() const = 0;`
- L39 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) = 0;`

#### class `UE::Audio::Insights::FTraceDashboardViewFactoryBase`  
`class FTraceDashboardViewFactoryBase : public IDashboardViewFactory`  
_L42-96_
- inherits: `IDashboardViewFactory`
- L45 _public prototype_ `FTraceDashboardViewFactoryBase();`
- L46 _public prototype_ `virtual ~FTraceDashboardViewFactoryBase();`
- L48 _public function_ `const TArray<TSharedPtr<FTraceProviderBase>>& GetProviders() const`
- L54 _public function_ `template <typename ProviderType> TSharedPtr<ProviderType> FindProvider(bool bEnsureIfMissing = true) const`
- L80 _protected prototype_ `virtual void Tick(float InElapsed);`
- L82 _protected function_ `virtual void ProcessEntries(EProcessReason Reason)`
- L83 _protected function_ `virtual void RefreshFilteredEntriesListView()`
- L86 _protected function_ `virtual void UpdateDebugDraw(const float DeltaTime)`
- L89 _protected member_ `TArray<TSharedPtr<FTraceProviderBase>> Providers;`
- L91 _protected member_ `EProcessReason UpdateFilterReason = EProcessReason::None;`
- L92 _protected member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L95 _private member_ `TMap<FName, uint64> UpdateIds;`

#### enum `UE::Audio::Insights::FTraceDashboardViewFactoryBase::EProcessReason`  
`enum class EProcessReason : uint8`  
_L73-78_
- L75 _public enumerator_ `None`
- L76 _public enumerator_ `FilterUpdated`
- L77 _public enumerator_ `EntriesUpdated`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/LogDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::FLogDashboardViewFactory`  
`class FLogDashboardViewFactory : public IDashboardViewFactory`  
_L20-49_
- inherits: `IDashboardViewFactory`
- L23 _public prototype_ `FLogDashboardViewFactory();`
- L24 _public prototype_ `~FLogDashboardViewFactory();`
- L26 _public prototype_ `virtual FName GetName() const override;`
- L27 _public prototype_ `virtual FText GetDisplayName() const override;`
- L28 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L29 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L30 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L48 _private member_ `FLogCategoryCollector CategoryCollector;`

#### struct `UE::Audio::Insights::FLogDashboardViewFactory::FLogCategoryCollector`  
`struct FLogCategoryCollector : public FOutputDevice`  
_L33-46_
- inherits: `FOutputDevice`
- L35 _public prototype_ `FLogCategoryCollector();`
- L36 _public prototype_ `~FLogCategoryCollector();`
- L38 _public prototype_ `FDefaultCategorySelectionMap GetCollectedCategories() const;`
- L40 _public prototype_ `virtual bool IsMemoryOnly() const override;`
- L41 _public prototype_ `virtual void Serialize(const TCHAR* InMsg, ELogVerbosity::Type Verbosity, const FName& InCategory) override;`
- L44 _private member_ `mutable FCriticalSection CollectionCritSec;`
- L45 _private member_ `FDefaultCategorySelectionMap CollectedCategories;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L15 _macro_ `#define LOCTEXT_NAMESPACE "AudioInsights"`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Audio` (scope `UE`)
- L18 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/OutputMeterDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::FOutputMeterDashboardViewFactory`  
`class FOutputMeterDashboardViewFactory : public FTraceDashboardViewFactoryBase, public TSharedFromThis<FOutputMeterDashboardViewFactory>`  
_L23-102_
- inherits: `FTraceDashboardViewFactoryBase,TSharedFromThis<FOutputMeterDashboardViewFactory>`
- L26 _public prototype_ `FOutputMeterDashboardViewFactory(TSharedRef<FSubmixDashboardViewFactory> SubmixDashboard);`
- L27 _public prototype_ `virtual ~FOutputMeterDashboardViewFactory();`
- L29 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L30 _public prototype_ `virtual FText GetDisplayName() const override;`
- L31 _public prototype_ `virtual FName GetName() const override;`
- L32 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L33 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L55 _private prototype_ `FLoudnessMeterSettings& GetLoudnessMeterSettings() const;`
- L57 _private prototype_ `FOutputMeterDashboardSettings& GetOutputMeterDashboardSettings();`
- L58 _private prototype_ `void SaveOutputMeterDashboardSettings();`
- L60 _private prototype_ `void InitLoudnessMeterWidgetView();`
- L62 _private prototype_ `void UpdateDataViewEntries();`
- L63 _private prototype_ `void UpdateAudioMeterInfo();`
- L64 _private prototype_ `void UpdateLoudnessValues();`
- L66 _private prototype_ `virtual void ProcessEntries(FTraceDashboardViewFactoryBase::EProcessReason Reason) override;`
- L68 _private prototype_ `TArray<FAudioMeterChannelInfo> GetAudioMeterChannelInfo() const;`
- L70 _private prototype_ `FTimespan GetAnalysisTime() const;`
- L71 _private prototype_ `FReply HandleResetButtonClicked();`
- L73 _private prototype_ `void OnLoudnessMeterExpansionChanged(const bool bIsExpanded);`
- L74 _private prototype_ `void OnChannelMeterExpansionChanged(const bool bIsExpanded);`
- L75 _private prototype_ `void OnSplitterFinishedResizing();`
- L77 _private member_ `TSharedPtr<FOutputMeterTraceProvider> OutputMeterProvider;`
- L78 _private member_ `TArray<TSharedPtr<IDashboardDataViewEntry>> DataViewEntries;`
- L81 _private member_ `TSharedPtr<const FSubmixTraceProvider> SubmixProvider;` — Audio meter related members
- L82 _private member_ `TOptional<uint64> ProcessedUpdateId;`
- L83 _private member_ `TUniquePtr<FAudioMeterInfo> AudioMeterInfo;`
- L86 _private member_ `AudioWidgetsCore::FLoudnessMeterWidgetView LoudnessMeterWidgetView;` — Loudness meters related members
- L87 _private member_ `bool bIsLoudnessMeterInitialized = false;`
- L90 _private member_ `TSharedPtr<SSplitter> ContentSplitter;` — Layout splitter for collapse/expand support
- L92 _private member_ `FLoudnessMeterResults LoudnessMeterResults;`
- L93 _private member_ `FLoudnessMeterMaxResults LoudnessMeterMaxResults;`
- L95 _private member_ `double AnalysisStartTimestamp = 0.0;`
- L96 _private member_ `double LatestTimestamp = 0.0;`
- L97 _private member_ `bool bWasReceivingData = false;`

#### struct `UE::Audio::Insights::FOutputMeterDashboardViewFactory::FLoudnessMeterResults`  
`struct FLoudnessMeterResults`  
_L36-45_
- L38 _public member_ `float LongTermLoudness = MIN_VOLUME_DECIBELS;`
- L39 _public member_ `float ShortTermLoudness = MIN_VOLUME_DECIBELS;`
- L40 _public member_ `float MomentaryLoudness = MIN_VOLUME_DECIBELS;`
- L41 _public member_ `float LoudnessRangeLowerBound = 0.0f;`
- L42 _public member_ `float LoudnessRangeUpperBound = 0.0f;`
- L44 _public member_ `float TruePeakDb = MIN_VOLUME_DECIBELS;`

#### struct `UE::Audio::Insights::FOutputMeterDashboardViewFactory::FLoudnessMeterMaxResults`  
`struct FLoudnessMeterMaxResults`  
_L47-53_
- L49 _public member_ `float ShortTermLoudness = MIN_VOLUME_DECIBELS;`
- L50 _public member_ `float MomentaryLoudness = MIN_VOLUME_DECIBELS;`
- L52 _public member_ `float TruePeakDb = MIN_VOLUME_DECIBELS;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Audio` (scope `UE`)
- L15 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SAudioCurveView.h` (Public)


#### class `SAudioCurveView`  
`class SAudioCurveView : public SCompoundWidget`  
_L16-150_
- inherits: `SCompoundWidget`
- desc: Loosely based on SCurveTimelineView TODO move this to a more general place like the Audio Widgets plugin once it's further developed
- L20 _public typedef_ `using FCurvePoint = TPair<double, float>;` — A curve point is a (double XValue, float YValue) pair
- L31 _public function_ `SLATE_BEGIN_ARGS(SAudioCurveView) : _ViewRange(TRange<double>(0,5)) , _AutoRangeYAxis(false) , _YMargin(0.05f) , _HorizontalAxisIncrement(0.5) , _GridLineColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.25f)) , _AxesLabelColor(FLinearColor::White) , _DesiredSize(FVector2D(100.f,100.f)) , _AdditionalToolTipText(FText::GetEmpty())`
- L42 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View X axis range (in value space)
- L44 _public prototype_ `SLATE_ATTRIBUTE(bool, AutoRangeYAxis);`
- L47 _public prototype_ `SLATE_ATTRIBUTE(float, YMargin);` — Margin for Y axis, as a 0 - 0.5f proportion, for the space each of above and below the data range. (ex. 0.05 means a 5% margin on the top and bottom, with 90% of the widget's vertical size corresponding to the data range).
- L50 _public prototype_ `SLATE_ATTRIBUTE(double, HorizontalAxisIncrement);` — X axis increment for grid lines.
- L52 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, GridLineColor);`
- L54 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, AxesLabelColor);`
- L57 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, DesiredSize);` — Desired widget size
- L60 _public prototype_ `SLATE_ATTRIBUTE(FText, AdditionalToolTipText);` — Additional text displayed below the standard tooltip
- L63 _public prototype_ `SLATE_EVENT(FOnScrubPositionChanged, OnScrubPositionChanged);` — Called when user clicks/drags on the widget. Only returns when there is a valid crosshair position
- L66 _public prototype_ `SLATE_EVENT(FOnKeyDown, OnKeyDown);` — Called when user presses a key when the widget is in focus
- L68 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L77 _public prototype_ `void SetYValueFormattingOptions(const FNumberFormattingOptions InValueFormattingOptions);`
- L78 _public prototype_ `void SetYAxisRange(const FFloatInterval& InRange);`
- L79 _public prototype_ `void SetCurvesPointData(TSharedPtr<TMap<uint64, TArray<FCurvePoint>>> InCurvesPointData);`
- L80 _public prototype_ `void SetCurvesMetadata(TSharedPtr<TMap<uint64, FCurveMetadata>> InMetadataPerCurve);`
- L82 _public function_ `FFloatInterval GetYAxisRange() const`
- L84 _public function_ `FText GetCurveToolTipXValueText() const`
- L85 _public function_ `FText GetCurveToolTipYValueText() const`
- L86 _public function_ `FText GetCurveToolTipDisplayNameText() const`
- L89 _public prototype_ `float ValueToLocalY(const FVector2f AllottedLocalSize, const float Value) const;` — Helper functions for converting between widget local Y position and a given data value (within DataRange).
- L90 _public prototype_ `float LocalYToValue(const FVector2f AllottedLocalSize, const float LocalY) const;`
- L93 _public prototype_ `void UpdateYDataRangeFromTimestampRange(const double InLowerBoundTimestamp, const double InUpperBoundTimestamp);`
- L98 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L99 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L100 _protected prototype_ `virtual FReply OnPreviewMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L101 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L102 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L103 _protected prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L104 _protected prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& Geometry, const FKeyEvent& KeyEvent) override;`
- L105 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L107 _protected prototype_ `int32 PaintCurves(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L108 _protected prototype_ `int32 PaintGridLines(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled, const SSimpleTimeSlider::FScrubRangeToScreen& RangeToScreen) const;`
- L109 _protected prototype_ `int32 PaintCrosshair(const FGeometry& MyGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const SSimpleTimeSlider::FScrubRangeToScreen& RangeToScreen) const;`
- L110 _protected prototype_ `int32 PaintYAxisLabels(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L111 _protected prototype_ `void UpdateCurveToolTip(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L112 _protected prototype_ `void UpdateYDataRange();`
- L113 _protected prototype_ `TSharedRef<SToolTip> CreateCurveTooltip();`
- L115 _protected prototype_ `void BroadcastScrubPosition();`
- L117 _protected member_ `TAttribute<TRange<double>> ViewRange;`
- L118 _protected member_ `TAttribute<bool> AutoRangeYAxis;`
- L119 _protected member_ `TAttribute<float> YMargin;`
- L120 _protected member_ `TAttribute<double> HorizontalAxisIncrement;`
- L121 _protected member_ `TAttribute<FLinearColor> GridLineColor;`
- L122 _protected member_ `TAttribute<FLinearColor> AxesLabelColor;`
- L123 _protected member_ `TAttribute<FVector2D> DesiredSize;`
- L124 _protected member_ `TAttribute<FText> AdditionalToolTipText;`
- L126 _protected member_ `FOnScrubPositionChanged OnScrubPositionChanged;`
- L127 _protected member_ `FOnKeyDown OnKeyDownHandler;`
- L130 _protected member_ `TSharedPtr<TMap<uint64, TArray<FCurvePoint>>> PointDataPerCurve;` — Point data and metadata, keyed by curve id
- L131 _protected member_ `TSharedPtr<TMap<uint64, FCurveMetadata>> MetadataPerCurve;`
- L133 _protected member_ `FFloatInterval YDataRange;` — Y axis data range in value space
- L136 _protected member_ `FText CurveToolTipXValueText;` — Tooltip text
- L137 _protected member_ `FText CurveToolTipYValueText;`
- L138 _protected member_ `FText CurveToolTipDisplayNameText;`
- L141 _protected member_ `FNumberFormattingOptions XValueFormattingOptions;` — Tooltip and axis text formatting
- L142 _protected member_ `FNumberFormattingOptions YValueFormattingOptions;`
- L144 _protected member_ `ESlateDrawEffect LineDrawEffects;`
- L145 _protected member_ `uint32 NumHorizontalGridLines;`
- L146 _protected member_ `FSlateFontInfo LabelFont;`
- L148 _protected member_ `TOptional<FCurvePoint> CrosshairPosition;`
- L149 _protected member_ `bool bIsMouseDragging = false;`

#### struct `SAudioCurveView::FCurveMetadata`  
`struct FCurveMetadata`  
_L24-29_
- L26 _public member_ `FLinearColor CurveColor;`
- L27 _public member_ `FText DisplayName;`
- L28 _public member_ `float PlotThickness = 1.0f;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnScrubPositionChanged, double, float) struct FCurveMetadata { FLinearColor CurveColor; FText DisplayName; float PlotThickness = 1.0f; };`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SAudioFilterBar.h` (Public)


#### class `UE::Audio::Insights::SAudioFilterBar`  
`template<typename EnumType> class SAudioFilterBar : public SBasicFilterBar<EnumType>`  
_L11-131_
- inherits: `SBasicFilterBar<EnumType>`
- L14 _public typedef_ `using FOnFilterChanged = typename SBasicFilterBar<EnumType>::FOnFilterChanged;`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAudioFilterBar) : _UseSectionsForCategories(true)`
- L19 _public function_ `SLATE_ARGUMENT(TArray<TSharedRef<FFilterBase<EnumType>>>, CustomFilters) SLATE_ARGUMENT(bool, UseSectionsForCategories) SLATE_EVENT(SAudioFilterBar<EnumType>::FOnFilterChanged, OnFilterChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L37 _public function_ `void DeleteCategory(const TSharedRef<FFilterCategory> InCategory)`
- L42 _public function_ `void DeleteFromFilter(const TSharedRef<FFilterBase<EnumType>> InFilter)`
- L49 _protected function_ `virtual TSharedRef<SWidget> MakeAddFilterMenu() override`
- L87 _protected function_ `void PopulateAddFilterMenu(UToolMenu* InMenu)`
- L93 _protected function_ `void PopulateCustomFilters(UToolMenu* InMenu)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Audio` (scope `UE`)
- L8 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L68 _function_ `` (scope `UE::Audio::Insights::SAudioFilterBar::MakeAddFilterMenu`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SAudioMeterView.h` (Public)


#### class `UE::Audio::Insights::SAudioMeterView`  
`class SAudioMeterView : public SCompoundWidget`  
_L14-33_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAudioMeterView) : _NameText(FText::GetEmpty()) , _NameTextColor(FSlateColor(FColor::White))`
- L21 _public prototype_ `SLATE_ARGUMENT(FText, NameText) SLATE_ARGUMENT(FSlateColor, NameTextColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAudioMeterInfo>& InAudioMeterInfo);`
- L27 _public prototype_ `void SetAudioMeterChannelInfo(const TSharedRef<FAudioMeterInfo>& InAudioMeterInfo);`
- L28 _public prototype_ `void SetName(const FText& InName);`
- L31 _protected member_ `TSharedPtr<SAudioMeterWidget> AudioMeterWidget;`
- L32 _protected member_ `FText NameText;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Audio` (scope `UE`)
- L10 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SSignalFlowGraph.h` (Public)


#### class `UE::Audio::Insights::SSignalFlowScrollBox`  
`class SSignalFlowScrollBox final : public SScrollBox`  
_L31-41_
- inherits: `SScrollBox`
- L34 _public function_ `void ResetAnimatingScroll()`

#### class `UE::Audio::Insights::SSignalFlowGraph`  
`class SSignalFlowGraph : public SCompoundWidget`  
_L43-270_
- inherits: `SCompoundWidget`
- L46 _public function_ `SLATE_BEGIN_ARGS(SSignalFlowGraph) : _ListSource(nullptr) , _NodeDetailFilterSettings(nullptr) , _GraphJustification(ESignalFlowJustification::Edge) , _ShowNodeDetails(false) , _DisplayAmpPeakInDb(true) , _AnimateWires(true) , _HighlightPathActive(false) , _LargeNodePadding(128.0f) , _SmallNodePadding(8.0f)`
- L59 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<ISignalFlowNode>>*, ListSource) SLATE_ARGUMENT(FSignalFlowNodeDetailFilterSettings*, NodeDetailFilterSettings) SLATE_ATTRIBUTE(TSharedPtr<FSignalFlowDashboardEntry>, SelectedItem) SLATE_ATTRIBUTE(TSharedPtr<FSignalFlowDashboardEntry>, HighlightedItem) SLATE_ATTRIBUTE(TSharedPtr<FSignalFlowDashboardEntry>, ActiveAudioDeviceEntry) SLATE_ATTRIBUTE(TSharedPtr<FSignalFlowDashboardEntry>, FocusedItem) SLATE_ATTRIBUTE(TWeakPtr<SSignalFlowScrollBox>, HorizontalScrollBox) SLATE_ATTRIBUTE(TWeakPtr<SSignalFlowScrollBox>, VerticalScrollBox) SLATE_ATTRIBUTE(ESignalFlowJustification, GraphJustification) SLATE_ATTRIBUTE(bool, ShowNodeDetails) SLATE_ATTRIBUTE(bool, DisplayAmpPeakInDb) SLATE_ATTRIBUTE(bool, AnimateWires) SLATE_ATTRIBUTE(bool, HighlightPathActive) SLATE_ATTRIBUTE(float, LargeNodePadding) SLATE_ATTRIBUTE(float, SmallNodePadding) SLATE_EVENT(FOnSignalFlowNodeSelected, OnNodeSelected) SLATE_EVENT(FIsEntryFilteredOutByText, IsEntryFilteredOutByText) SLATE_EVENT(FIsInHighlightedPath, IsInHighlightedPath) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L83 _public function_ `void SetHorizontalScrollBox(const TWeakPtr<SSignalFlowScrollBox> ScrollBox)`
- L84 _public function_ `void SetVerticalScrollBox(const TWeakPtr<SSignalFlowScrollBox> ScrollBox)`
- L86 _public prototype_ `void RefreshGraph();`
- L87 _public prototype_ `void ResetGraph();`
- L89 _public prototype_ `void ToggleOrientation();`
- L90 _public function_ `EOrientation GetGraphOrientation() const`
- L92 _public prototype_ `void SetWireAnimationSettings(const float AmpPowerFactor, const float WireThicknessScalarMax);`
- L94 _public prototype_ `void ResetZoom();`
- L96 _public prototype_ `TSharedPtr<SSignalFlowGraphNode> FindNodeWidget(const FSignalFlowEntryKey& NodeEntryKey) const;`
- L98 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L99 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L101 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L102 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L103 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L104 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L105 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L106 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L109 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float InLayoutScaleMultiplier) const override;`
- L112 _private prototype_ `int32 OnPaintConnections(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L114 _private prototype_ `int32 PaintConnectionToNode(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const TSharedPtr<FSignalFlowDashboardEntry>& SenderEntry, const SSignalFlowGraphNode& SenderNode, const SSignalFlowGraphNode& ReceiverNode, const FBox2D& LocalBoundsBox, const FVector2D& ViewportPosInGraph, const FVector2D& CursorPosInViewport, const float SendLevel, const int32 SendLabelIndex, const bool bIsSourceBusConnection, const bool bHighlightPathModeActive) const;`
- L128 _private prototype_ `int32 AnimateWire(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const TSharedPtr<FSignalFlowDashboardEntry>& Entry, const ESignalFlowEntryType ReceiverEntryType, const FVector2D& ConnectionStartPos, const FVector2D& ConnectionEndPos, const float SendLevel, const bool bIsSourceBusConnection, const bool bIsSendLabelHovered = false) const;`
- L139 _private prototype_ `void CollectAmplitudeConnectionPoints(const float Amplitude, const FVector2D& ConnectionStartPos, const FVector2D& StartDirection, const FVector2D& ConnectionEndPos, const FVector2D& EndDirection, const float Prop, TArray<FVector2D>& OutTopPoints, TArray<FVector2D>& OutBottomPoints, FVector2D& OutLastPoint, const float HeightMultiplier = 1.0f) const;`
- L161 _private prototype_ `FGraphLimits GetGraphWidthLimits() const;`
- L162 _private prototype_ `float GetNodeGraphSlotWidth() const;`
- L163 _private prototype_ `float GetNodeGraphSlotHeight() const;`
- L165 _private prototype_ `void CreateGraphNodes(TSet<FSignalFlowEntryKey>& OutRemainingNodeKeys, const FGraphLimits& GraphWidthLimits, TArray<struct TreeDepthPair>& OutTreeDepthStructure);`
- L166 _private prototype_ `void CreateSendLabels();`
- L167 _private prototype_ `void CleanUpOldWidgets(const TSet<FSignalFlowEntryKey>& NodeKeysToRemove);`
- L169 _private prototype_ `void MaintainOldViewportPosition(const FVector2D& OriginalSize, const FGraphLimits& NewGraphWidthLimits, const TArray<struct TreeDepthPair>& NewTreeDepthOrder);`
- L171 _private prototype_ `FVector2D ComputeNodePositionInGraph(const SSignalFlowGraphNode& Node) const;`
- L173 _private prototype_ `void UpdateContentPadding(const FGraphLimits& GraphWidthLimits, const TArray<struct TreeDepthPair>& TreeDepthOrder);`
- L174 _private prototype_ `void ApplyContentPaddingAndCompensateScroll(const TSharedPtr<SSignalFlowScrollBox>& InHorizontalScrollBox, const TSharedPtr<SSignalFlowScrollBox>& InVerticalScrollBox);`
- L175 _private prototype_ `void DetectAndHandleViewportResize();`
- L176 _private prototype_ `FVector2D GetRawContentSize(const FGraphLimits& GraphWidthLimits, const TArray<struct TreeDepthPair>& TreeDepthOrder) const;`
- L178 _private prototype_ `void CreateGraphNode(const TSharedPtr<ISignalFlowNode>& Node, const float MinXPos, const float MaxXPos, const int32 DepthTracker, TSet<FSignalFlowEntryKey>& OutRemainingNodeKeys);`
- L186 _private prototype_ `TSharedPtr<SSignalFlowGraphNode> FindRealNode(const FSignalFlowEntryKey& EntryKey, const ENodeConnectionType ConnectionType) const;`
- L187 _private prototype_ `TOptional<FSignalFlowEntryKey> FindRealNodeKey(const FSignalFlowEntryKey& EntryKey, const ENodeConnectionType ConnectionType) const;`
- L195 _private prototype_ `EAnimationResult AnimateScrollTo(const TSharedRef<SScrollBox>& ScrollBox, const FVector2D& ScrollToPos, const float DeltaTime);`
- L198 _private prototype_ `void OnRequestedContextMenu(const FPointerEvent& MouseEvent, const TSharedPtr<FSignalFlowDashboardEntry> Entry);`
- L201 _private member_ `TSharedPtr<SCanvas> Canvas;`
- L203 _private member_ `TMap<FSignalFlowEntryKey, TSharedPtr<SSignalFlowGraphNode>> NodeWidgets;`
- L211 _private member_ `TMap<FSignalFlowEntryKey, FConnectedNodeKeys> DummyToRealConnectionKeys;`
- L213 _private member_ `TArray<TSharedPtr<ISignalFlowNode>>* ListSource = nullptr;`
- L214 _private member_ `FSignalFlowNodeDetailFilterSettings* NodeDetailFilterSettings = nullptr;`
- L216 _private member_ `TAttribute<TSharedPtr<FSignalFlowDashboardEntry>> SelectedItem;`
- L217 _private member_ `TAttribute<TSharedPtr<FSignalFlowDashboardEntry>> HighlightedItem;`
- L218 _private member_ `TAttribute<TSharedPtr<FSignalFlowDashboardEntry>> ActiveAudioDeviceEntry;`
- L219 _private member_ `TAttribute<TSharedPtr<FSignalFlowDashboardEntry>> FocusedItem;`
- L220 _private member_ `TAttribute<ESignalFlowJustification> GraphJustification;`
- L221 _private member_ `TAttribute<bool> ShowNodeDetails;`
- L222 _private member_ `TAttribute<bool> DisplayAmpPeakInDb;`
- L223 _private member_ `TAttribute<bool> AnimateWires;`
- L224 _private member_ `TAttribute<bool> HighlightPathActive;`
- L226 _private member_ `TAttribute<TWeakPtr<SSignalFlowScrollBox>> HorizontalScrollBox;`
- L227 _private member_ `TAttribute<TWeakPtr<SSignalFlowScrollBox>> VerticalScrollBox;`
- L229 _private member_ `FOnSignalFlowNodeSelected OnNodeSelected;`
- L230 _private member_ `FIsEntryFilteredOutByText IsEntryFilteredOutByText;`
- L231 _private member_ `FIsInHighlightedPath IsInHighlightedPath;`
- L234 _private member_ `TSharedPtr<IMenu> GraphContextMenu;`
- L235 _private member_ `FAssetEditorContextMenuHelper AssetContextMenuHelper;`
- L238 _private member_ `EOrientation Orientation = EOrientation::Orient_Horizontal;`
- L240 _private member_ `FGraphLimits CachedGraphWidthLimits;`
- L241 _private member_ `TArray<struct TreeDepthPair> CachedTreeDepthPairs;`
- L242 _private member_ `int32 MaxNumNodeOutputsInGraph = 0;`
- L244 _private member_ `TAttribute<float> LargeNodePadding;`
- L245 _private member_ `TAttribute<float> SmallNodePadding;`
- L247 _private member_ `float ZoomScaleFactor = 0.5f;`
- L248 _private member_ `float WireSplineAmplitudePowerFactor = 0.4f;`
- L249 _private member_ `float WireSplineThicknessScalarMax = 14.0f;`
- L254 _private member_ `FVector2D ContentPadding = FVector2D::ZeroVector;` — Dynamic padding (in unzoomed graph space) applied symmetrically to inflate desired size so there is always enough scroll range for MaintainOldViewportPosition to work even when the graph content is smaller than the viewport.
- L259 _private member_ `TOptional<FVector2D> CachedViewportSize;` — Last-seen viewport size of the wrapping scroll box. Compared each tick so we can react to splitter drags / window resizes and keep padding in sync with the viewport. Unset until the first tick where the scroll box reports a non-zero size.
- L262 _private member_ `mutable TArray<FVector2D> AnimateWireTopPoints;` — Reusable scratch buffers for AnimateWire to avoid per-wire heap allocation each paint.
- L263 _private member_ `mutable TArray<FVector2D> AnimateWireBottomPoints;`
- L265 _private prototype_ `bool IsCursorNearSendLabel(const FVector2D& CursorPosInViewport, const FVector2D& SendLabelPos) const;`
- L267 _private member_ `bool bNeedsRefresh = false;`
- L268 _private member_ `bool bAnimateZoom = false;`
- L269 _private member_ `bool bIsDraggingToMove = false;`

#### struct `UE::Audio::Insights::SSignalFlowGraph::FGraphLimits`  
`struct FGraphLimits`  
_L150-159_
- L152 _public member_ `float MinPos = TNumericLimits<float>::Max();`
- L153 _public member_ `float MaxPos = TNumericLimits<float>::Lowest();`
- L155 _public function_ `bool IsValid() const`

#### enum `UE::Audio::Insights::SSignalFlowGraph::ENodeConnectionType`  
`enum class ENodeConnectionType : uint8`  
_L180-184_
- L182 _public enumerator_ `Input`
- L183 _public enumerator_ `Output`

#### enum `UE::Audio::Insights::SSignalFlowGraph::EAnimationResult`  
`enum class EAnimationResult : uint8`  
_L189-193_
- L191 _public enumerator_ `InProgress`
- L192 _public enumerator_ `Complete`

#### struct `UE::Audio::Insights::SSignalFlowGraph::FConnectedNodeKeys`  
`struct FConnectedNodeKeys`  
_L205-209_
- L207 _public member_ `FSignalFlowEntryKey RealInputKey;`
- L208 _public member_ `FSignalFlowEntryKey RealOutputKey;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Audio` (scope `UE`)
- L23 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsEntryFilteredOutByText, const FSignalFlowDashboardEntry&);`
- L28 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsEntryFilteredOutByText, const FSignalFlowDashboardEntry&);` (scope `UE::Audio::Insights`)
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsInHighlightedPath, const FSignalFlowEntryKey&);`
- L29 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsInHighlightedPath, const FSignalFlowEntryKey&);` (scope `UE::Audio::Insights`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SSignalFlowGraphNode.h` (Public)


#### class `UE::Audio::Insights::SSignalFlowGraphNode`  
`class SSignalFlowGraphNode : public SCompoundWidget`  
_L27-179_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SSignalFlowGraphNode) : _Entry(nullptr), _NodeDetailFilterSettings(nullptr), _DisplayName(), _PositionInGraph(FVector2d::ZeroVector), _XPos(0.0f), _YPos(0.0f), _ZoomScaleFactor(1.0f), _IsSelected(false), _ShowNodeDetails(false), _IsFilteredOutByText(false), _DisplayAmpPeakInDb(true), #if WITH_EDITOR _GraphIsDraggingToMove(false), #endif`
- L49 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSignalFlowDashboardEntry>, Entry) SLATE_ARGUMENT(FSignalFlowNodeDetailFilterSettings*, NodeDetailFilterSettings) SLATE_ARGUMENT(FText, DisplayName) SLATE_ATTRIBUTE(FVector2d, PositionInGraph) SLATE_ATTRIBUTE(float, XPos) SLATE_ATTRIBUTE(float, YPos) SLATE_ATTRIBUTE(float, ZoomScaleFactor) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_ATTRIBUTE(bool, IsHighlighted) SLATE_ATTRIBUTE(bool, ShowNodeDetails) SLATE_ATTRIBUTE(bool, IsFilteredOutByText) SLATE_ATTRIBUTE(bool, DisplayAmpPeakInDb) #if WITH_EDITOR SLATE_ATTRIBUTE(bool, GraphIsDraggingToMove) #endif`
- L81 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L84 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L87 _public prototype_ `virtual FVector2D ComputeDesiredSize(float InLayoutScaleMultiplier) const override;`
- L89 _public prototype_ `FVector2D GetLocalInputPos() const;`
- L90 _public prototype_ `FVector2D GetLocalCenteredOutputPos() const;`
- L91 _public prototype_ `FVector2D GetLocalSendLabelPos(const FSignalFlowEntryKey& ReceiverEntryKey, const int32 LabelIndex) const;`
- L92 _public prototype_ `int32 GetNumSendLabels() const;`
- L94 _public prototype_ `void UpdateNodeLayout();`
- L95 _public prototype_ `FVector2D GetCachedPositionInGraph() const;`
- L97 _public prototype_ `void SetSendLabelWidgets(const TSet<FSignalFlowEntryKey>& ReceiverEntryKeys);`
- L98 _public prototype_ `void RemoveSendLabelWidget(const FSignalFlowEntryKey& ReceiverEntryKey);`
- L99 _public prototype_ `bool ContainsSendLabel(const FSignalFlowEntryKey& ReceiverEntryKey) const;`
- L101 _public function_ `const FSignalFlowEntryKey& GetNodeEntryKey() const`
- L102 _public function_ `const TSharedPtr<FSignalFlowDashboardEntry> GetEntry() const`
- L105 _public function_ `FName GetAssetFName() const`
- L108 _public function_ `float GetXPos() const`
- L109 _public function_ `float GetYPos() const`
- L111 _public function_ `void SetXPos(const float Pos)`
- L112 _public function_ `void SetYPos(const float Pos)`
- L115 _private prototype_ `void CreateSendLabelWidget(const FSignalFlowEntryKey& ReceiverEntryKey);`
- L117 _private prototype_ `TSharedRef<SHorizontalBox> CreateNodeName(const SSignalFlowGraphNode::FArguments& InArgs);`
- L118 _private prototype_ `TSharedRef<SVerticalBox> CreateNodeDetails() const;`
- L119 _private prototype_ `TSharedRef<SHorizontalBox> CreateNodeDetailsRow(const ESignalFlowNodeDetailParam ParamType) const;`
- L120 _private prototype_ `TSharedRef<SVerticalBox> CreateSendOutputsVerticalContainer();`
- L121 _private prototype_ `TSharedRef<SHorizontalBox> CreateSendOutputsHorizontalContainer();`
- L123 _private prototype_ `bool NodeDetailsExpanderArrowIsEnabled() const;`
- L124 _private prototype_ `bool SendLabelsAreVisible() const;`
- L127 _private prototype_ `void ToggleMute();`
- L128 _private prototype_ `void ToggleSolo();`
- L136 _private prototype_ `FMuteSoloStates GetMuteSoloState() const;`
- L137 _private prototype_ `bool IsMuteSoloAvailableForNode() const;`
- L140 _private member_ `TSharedPtr<FSignalFlowDashboardEntry> Entry;`
- L141 _private member_ `TAttribute<FVector2d> PositionInGraph;`
- L142 _private member_ `TAttribute<float> XPos;`
- L143 _private member_ `TAttribute<float> YPos;`
- L144 _private member_ `TAttribute<float> ZoomScaleFactor;`
- L145 _private member_ `TAttribute<bool> IsSelected;`
- L146 _private member_ `TAttribute<bool> IsHighlighted;`
- L147 _private member_ `TAttribute<bool> ShowNodeDetails;`
- L148 _private member_ `TAttribute<bool> IsFilteredOutByText;`
- L149 _private member_ `TAttribute<bool> DisplayAmpPeakInDb;`
- L150 _private member_ `TAttribute<EOrientation> GraphOrientation;`
- L152 _private member_ `TMap<FSignalFlowEntryKey, TSharedRef<class SSignalFlowGraphSendLabel>> SendLabels;`
- L154 _private member_ `FOnSignalFlowNodeSelected OnNodeSelected;`
- L157 _private member_ `FOnSignalFlowNodeContextMenuOpened OnOpenContextMenu;`
- L158 _private member_ `TAttribute<bool> GraphIsDraggingToMove;`
- L162 _private member_ `FName AssetFName;`
- L163 _private member_ `FString AssetString;`
- L164 _private member_ `TAttribute<bool> IsDirectlySoloed;`
- L167 _private member_ `FVector2d CachedPositionInGraph = FVector2d::Zero();`
- L168 _private member_ `FSignalFlowEntryKey NodeEntryKey;`
- L170 _private member_ `FSignalFlowNodeDetailFilterSettings* NodeDetailFilterSettings = nullptr;`
- L172 _private member_ `TSharedPtr<SBorder> SelectedNodeBorder;`
- L173 _private member_ `TSharedPtr<SBorder> NodeBorder;`
- L174 _private member_ `TSharedPtr<SHorizontalBox> NodeLabelHorizontalBox;`
- L175 _private member_ `TSharedPtr<SVerticalBox> SendLevelsVerticalBox;`
- L176 _private member_ `TSharedPtr<SHorizontalBox> SendLevelsHorizontalBox;`
- L178 _private member_ `bool bNodeDetailsAreExpanded = true;`

#### struct `UE::Audio::Insights::SSignalFlowGraphNode::FMuteSoloStates`  
`struct FMuteSoloStates`  
_L130-134_
- L132 _public member_ `bool bIsMuted = false;`
- L133 _public member_ `bool bIsSoloed = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L9 _macro_ `#define MUTE_SOLO_ENABLED (WITH_EDITOR && ENABLE_AUDIO_DEBUG)`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSignalFlowNodeSelected, TSharedPtr<FSignalFlowDashboardEntry>);`
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSignalFlowNodeSelected, TSharedPtr<FSignalFlowDashboardEntry>);` (scope `UE::Audio::Insights`)
- L24 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSignalFlowNodeContextMenuOpened, const FPointerEvent&, const TSharedPtr<FSignalFlowDashboardEntry>);`
- L24 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSignalFlowNodeContextMenuOpened, const FPointerEvent&, const TSharedPtr<FSignalFlowDashboardEntry>);` (scope `UE::Audio::Insights`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SSignalFlowGraphSendLabel.h` (Public)


#### class `UE::Audio::Insights::SSignalFlowGraphSendLabel`  
`class SSignalFlowGraphSendLabel : public SCompoundWidget`  
_L15-49_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SSignalFlowGraphSendLabel) : _ReceiverEntryType(ESignalFlowEntryType::AudioDevice), _SendLevel(), _GraphOrientation(EOrientation::Orient_Vertical), _ZoomScaleFactor(1.0f)`
- L26 _public prototype_ `SLATE_ARGUMENT(ESignalFlowEntryType, ReceiverEntryType) SLATE_ATTRIBUTE(TOptional<float>, SendLevel) SLATE_ATTRIBUTE(EOrientation, GraphOrientation) SLATE_ATTRIBUTE(float, ZoomScaleFactor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L36 _public prototype_ `virtual FVector2D ComputeDesiredSize(float InLayoutScaleMultiplier) const override;`
- L38 _public prototype_ `bool ValueIsSet() const;`
- L41 _private prototype_ `TSharedRef<STextBlock> CreateOutputLabelText(const FText& ToolTipText) const;`
- L42 _private prototype_ `TSharedRef<SOverlay> CreatePinIconWidget(const FText& ToolTipText, const ESignalFlowEntryType ReceiverEntryType);`
- L44 _private member_ `TAttribute<TOptional<float>> SendLevel;`
- L45 _private member_ `TAttribute<EOrientation> GraphOrientation;`
- L46 _private member_ `TAttribute<float> ZoomScaleFactor;`
- L48 _private member_ `TSharedPtr<SImage> OutputPinImage;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Audio` (scope `UE`)
- L13 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SignalFlowDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::SSignalFlowDashboard`  
`class SSignalFlowDashboard : public SVerticalBox`  
_L29-39_
- inherits: `SVerticalBox`
- L32 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L33 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L35 _public function_ `void SetOnKeyDownHandler(FOnKeyDown Handler)`
- L38 _private member_ `FOnKeyDown OnKeyDownHandler;`

#### class `UE::Audio::Insights::FSignalFlowDashboardViewFactory`  
`class FSignalFlowDashboardViewFactory : public FTraceDashboardViewFactoryBase, public TSharedFromThis<FSignalFlowDashboardViewFactory>`  
_L41-246_
- inherits: `FTraceDashboardViewFactoryBase,TSharedFromThis<FSignalFlowDashboardViewFactory>`
- L44 _public prototype_ `FSignalFlowDashboardViewFactory();`
- L45 _public prototype_ `virtual ~FSignalFlowDashboardViewFactory();`
- L47 _public prototype_ `virtual FName GetName() const override;`
- L48 _public prototype_ `virtual FText GetDisplayName() const override;`
- L49 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L50 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L51 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L53 _public prototype_ `FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L54 _public prototype_ `void Reset();`
- L71 _private prototype_ `const FTableRowStyle* GetRowStyle() const;`
- L73 _private prototype_ `void BindCommands();`
- L75 _private prototype_ `TSharedRef<SWidget> CreateToolbar();`
- L76 _private prototype_ `TSharedRef<SWidget> CreateToolbarSettingsMenu();`
- L77 _private prototype_ `TSharedRef<SWidget> CreateToolbarToggleControls();`
- L78 _private prototype_ `TSharedRef<SWidget> CreateToolbarButtonActions();`
- L79 _private prototype_ `TSharedRef<SWidget> CreateToolbarIndicators();`
- L81 _private prototype_ `TSharedRef<SWidget> CreateToolbarClearMuteSoloButton();`
- L84 _private prototype_ `TSharedRef<SWidget> OnGetSettingsMenuContent();`
- L85 _private prototype_ `void BuildJustificationMenuContent(FMenuBuilder& OutMenuBuilder);`
- L86 _private prototype_ `void BuildNodeDetailFiltersMenuContent(FMenuBuilder& OutMenuBuilder);`
- L87 _private prototype_ `void CreateAmpDisplayModeToggle(FMenuBuilder& OutMenuBuilder);`
- L88 _private prototype_ `void CreateNodePaddingControls(FMenuBuilder& OutMenuBuilder);`
- L89 _private prototype_ `void CreateNodePaddingSpinBox(FMenuBuilder& OutMenuBuilder, const FText& Label, const FText& Tooltip, float& OutValue);`
- L91 _private prototype_ `FReply ScrollGraphViewToSelectedNode(const bool bResetZoom);`
- L92 _private prototype_ `void ToggleGraphOrientation();`
- L93 _private prototype_ `void ToggleShowNodeDetails();`
- L94 _private prototype_ `void TogglePauseGraphEnabled();`
- L95 _private prototype_ `void ToggleEnableAllNodeDetailFilters();`
- L96 _private prototype_ `void ToggleAnimateWires();`
- L97 _private prototype_ `void SetJustification(const ESignalFlowJustification Justification);`
- L99 _private prototype_ `bool CanPauseTimestamp() const;`
- L100 _private prototype_ `bool IsTimestampPaused() const;`
- L101 _private prototype_ `void ResetPauseTimestamp();`
- L103 _private prototype_ `TSharedPtr<FSignalFlowDashboardEntry> GetFilteredAudioDeviceEntry() const;`
- L105 _private prototype_ `TSharedRef<SWidget> CreateSelectionPanel();`
- L106 _private prototype_ `TSharedRef<SWidget> CreateGraphSection();`
- L108 _private prototype_ `void OnMainSplitterFinishedResizing();`
- L109 _private prototype_ `void OnCategorySplitterFinishedResizing();`
- L111 _private prototype_ `TSharedRef<SWidget> CreateSelectableList(const FText& HeadingText, const TArray<TSharedPtr<FSignalFlowDashboardEntry>>& ListSource, const ESignalFlowEntryType EntryType, TSharedPtr<SListView<TSharedPtr<FSignalFlowDashboardEntry>>>& OutListView);`
- L112 _private prototype_ `TSharedPtr<SListView<TSharedPtr<FSignalFlowDashboardEntry>>> GetSelectableList(const ESignalFlowEntryType EntryType);`
- L113 _private prototype_ `bool GetSelectableListIsExpanded(const ESignalFlowEntryType EntryType) const;`
- L114 _private prototype_ `void SetSelectableListIsExpanded(const ESignalFlowEntryType EntryType, const bool bIsExpanded);`
- L115 _private prototype_ `void SetSelectableListSlotSize(const ESignalFlowEntryType EntryType, const bool bIsExpanded, float& OutSlotSize);`
- L116 _private prototype_ `void ApplyAllCategorySlotSizes();`
- L118 _private prototype_ `void SetSearchBoxFilterText(const FText& NewText);`
- L120 _private prototype_ `void OnListSelectionChanged(TSharedPtr<FSignalFlowDashboardEntry> InSelectedItem, ESelectInfo::Type SelectInfo);`
- L121 _private prototype_ `void OnSelectionChanged(TSharedPtr<FSignalFlowDashboardEntry> InSelectedItem, ESelectInfo::Type SelectInfo, const bool bCenterViewAfterSelection = false);`
- L122 _private prototype_ `void SetNewSelection(const TSharedPtr<FSignalFlowDashboardEntry>& InSelectedItem, const bool bCenterViewAfterSelection = false);`
- L124 _private prototype_ `void SetHighlightedItem(const TSharedPtr<FSignalFlowDashboardEntry>& InHighlightedItem);`
- L125 _private prototype_ `void RecomputeHighlightedPathKeys(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData);`
- L126 _private prototype_ `void ClearListHighlights();`
- L128 _private prototype_ `virtual void ProcessEntries(EProcessReason Reason) override;`
- L129 _private prototype_ `void BuildSelectionMenus(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, const EProcessReason Reason);`
- L130 _private prototype_ `bool IsEntryFilteredOutByText(const FSignalFlowDashboardEntry& Entry) const;`
- L132 _private prototype_ `virtual void RefreshFilteredEntriesListView() override;`
- L133 _private prototype_ `void OnRequestGraphRefresh();`
- L134 _private prototype_ `void SendSelectedNodeDestroyedNotification();`
- L135 _private prototype_ `void CreateFilteredNodeGraph(const FSignalFlowTraceProvider& Provider, TSharedPtr<FSignalFlowDashboardEntry> FilterFromEntry, const bool bAddAllNodes);`
- L137 _private prototype_ `void AddAllNodesToGraph();`
- L138 _private prototype_ `void AddFilteredInputsRecursive(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSharedPtr<FSignalFlowDashboardEntry> Entry, TSharedPtr<FSignalFlowDashboardEntry> ChildEntry, int32 TreeDepth, TSet<FSignalFlowEntryKey>& OutExistingEntryKeys, TSet<FSignalFlowEntryKey>* OutPathKeys = nullptr);`
- L139 _private prototype_ `void AddFilteredOutputs(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSharedPtr<FSignalFlowDashboardEntry> Entry, int32 TreeDepth, TSet<FSignalFlowEntryKey>& OutExistingEntryKeys, TSet<FSignalFlowEntryKey>* OutPathKeys = nullptr);`
- L140 _private prototype_ `void AddFilteredOutputsRecursive(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSharedPtr<FSignalFlowDashboardEntry> Entry, TSharedPtr<FSignalFlowDashboardEntry> ParentEntry, int32 TreeDepth, TSet<FSignalFlowEntryKey>& OutExistingEntryKeys, TSet<FSignalFlowEntryKey>* OutPathKeys = nullptr);`
- L142 _private prototype_ `void AddFilteredLinkedSourceBus(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSharedPtr<FSignalFlowDashboardEntry> Entry, ISignalFlowNode* const OutEntryNode, TSet<FSignalFlowEntryKey>& OutExistingEntryKeys, TSet<FSignalFlowEntryKey>* OutPathKeys = nullptr);`
- L143 _private prototype_ `void AddFilteredLinkedSources(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSharedPtr<FSignalFlowDashboardEntry> Entry, ISignalFlowNode* const OutEntryNode, TSet<FSignalFlowEntryKey>& OutExistingEntryKeys, TSet<FSignalFlowEntryKey>* OutPathKeys = nullptr);`
- L144 _private prototype_ `void AddFilteredLinkedBusPatchInputs(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSharedPtr<FSignalFlowDashboardEntry> Entry, ISignalFlowNode* const OutEntryNode, TSet<FSignalFlowEntryKey>& OutExistingEntryKeys, TSet<FSignalFlowEntryKey>* OutPathKeys = nullptr);`
- L145 _private prototype_ `void AddFilteredLinkedBusPatchOutputs(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSharedPtr<FSignalFlowDashboardEntry> Entry, ISignalFlowNode* const OutEntryNode, TSet<FSignalFlowEntryKey>& OutExistingEntryKeys, TSet<FSignalFlowEntryKey>* OutPathKeys = nullptr);`
- L146 _private prototype_ `void AddFilteredLinkedEntries(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSharedPtr<FSignalFlowDashboardEntry> Entry, const TSet<FSignalFlowEntryKey>& LinkedEntryKeys, TArray<FSignalFlowEntryKey>* OutFilteredLinkedEntries, TFunctionRef<void(ISignalFlowNode&)> LinkBackFunction, TSet<FSignalFlowEntryKey>& OutExistingEntryKeys, TSet<FSignalFlowEntryKey>* OutPathKeys = nullptr);`
- L148 _private prototype_ `void CleanUpFilteredEntries(const TSet<FSignalFlowEntryKey>& EntriesToRemove);`
- L150 _private prototype_ `void AddMissingNodesToGraph(const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSet<FSignalFlowEntryKey>& OutEntriesMarkedToDelete);`
- L151 _private prototype_ `void AddMissingNodeByOutputs(const FSignalFlowDashboardEntry& Entry, const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSet<FSignalFlowEntryKey>& OutEntriesMarkedToDelete);`
- L152 _private prototype_ `void AddMissingNodeByInputs(const FSignalFlowDashboardEntry& Entry, const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, TSet<FSignalFlowEntryKey>& OutEntriesMarkedToDelete);`
- L153 _private prototype_ `void GetNextInputsInGraphRecursive(const FSignalFlowDashboardEntry& Entry, const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, const TSet<FSignalFlowEntryKey>& EntriesMarkedToDelete, TArray<TSharedPtr<FSignalFlowDashboardEntry>>& OutNextInputs) const;`
- L154 _private prototype_ `void GetNextOutputsInGraphRecursive(const FSignalFlowDashboardEntry& Entry, const TSortedMap<FSignalFlowEntryKey, TSharedPtr<FSignalFlowDashboardEntry>>& DeviceData, const TSet<FSignalFlowEntryKey>& EntriesMarkedToDelete, TArray<TSharedPtr<FSignalFlowDashboardEntry>>& OutNextOutputs) const;`
- L155 _private prototype_ `bool EntryIsInGraph(const FSignalFlowEntryKey& EntryKey, const TSet<FSignalFlowEntryKey>& EntriesMarkedToDelete) const;`
- L157 _private prototype_ `void CalculateFilteredGraphDepthStructure(TOptional<FSignalFlowEntryKey>& OutRootEntryKey, TArray<TreeDepthPair>& OutSortedTreeDepths) const;`
- L159 _private prototype_ `void CreateDummyInputs(const TArray<TreeDepthPair>& TreeDepthStructure);`
- L160 _private prototype_ `TSharedPtr<FDummyConnectionNode> CreateDummyConnectionNode(const TSharedPtr<FSignalFlowEntryNode>& InputNode, const TSharedPtr<ISignalFlowNode>& OutputNode, const TreeDepthPair& TreeDepthPair, const FSignalFlowEntryKey& ConnectionOutputNodeKey);`
- L162 _private prototype_ `void AssignNodeOrderRecursive(TSharedPtr<ISignalFlowNode> OutNode, const int32 Depth, int32& OutNodeProcessingOrder);`
- L163 _private prototype_ `void SortNodeInputs(TSharedPtr<ISignalFlowNode> OutNode);`
- L164 _private prototype_ `TreeDepthPair GetRealTreeDepthForNode(const TSharedPtr<ISignalFlowNode>& Node) const;`
- L165 _private prototype_ `void GetBranchMinTimestampAndTreeDepthRecursive(const TArray<FSignalFlowEntryKey>& NodeKeys, TreeDepthPair& OutMinTreeDepth, double& OutMinTimestamp) const;`
- L166 _private prototype_ `bool NodeIsOwnerOrSound(const ISignalFlowNode& Node) const;`
- L168 _private prototype_ `void FixUnassignedNodeOrders();`
- L169 _private prototype_ `void SortNodeOrder();`
- L171 _private prototype_ `void CalcXPositions(const TSharedPtr<ISignalFlowNode>& GraphRootNode);`
- L172 _private prototype_ `void CalcXPositionsForRows(const TArray<TArray<int32>>& NodeIndexRows, const EOrientation GraphOrientation, int32& OutGraphWidth);`
- L173 _private prototype_ `void CompactRealNodeXPositions();`
- L174 _private prototype_ `void MaintainFocusedNodeXPos(const TSharedPtr<ISignalFlowNode>& FallbackNode);`
- L175 _private prototype_ `void PositionRowEquidistant(const TArray<int32>& NodeIndexRow);`
- L177 _private prototype_ `void CalcXPositionForNode(const TSharedPtr<ISignalFlowNode>& Node, const TArray<FSignalFlowEntryKey>& NodesToPositionRelativeTo, const int32 NodeIndexInRow, const TArray<TSharedPtr<ISignalFlowNode>>& PrevPositionedNodesInRow);`
- L178 _private prototype_ `void AlignNodeTowardsEdge(const TSharedPtr<ISignalFlowNode>& Node, const int32 NodeIndexInRow);`
- L179 _private prototype_ `void AlignNodeTowardsCenter(const TSharedPtr<ISignalFlowNode>& Node, const TArray<FSignalFlowEntryKey>& NodesToPositionRelativeTo, const TArray<TSharedPtr<ISignalFlowNode>>& PrevPositionedNodesInRow);`
- L182 _private prototype_ `void OnReadEditorSettings(const FSignalFlowSettings& InSettings);`
- L183 _private prototype_ `void OnWriteEditorSettings(FSignalFlowSettings& OutSettings);`
- L184 _private prototype_ `TSharedPtr<SWidget> OnConstructContextMenu();`
- L188 _private prototype_ `bool IsReadingTraceFile() const;`
- L191 _private member_ `TSharedPtr<FSignalFlowTraceProvider> SignalFlowProvider;`
- L192 _private member_ `TSharedPtr<SSignalFlowDashboard> DashboardWidget;`
- L194 _private member_ `TSharedPtr<SSplitter> CategorySplitter;`
- L196 _private member_ `TSharedPtr<SListView<TSharedPtr<FSignalFlowDashboardEntry>>> ActiveOwnerObjectsListView;`
- L197 _private member_ `TArray<TSharedPtr<FSignalFlowDashboardEntry>> ActiveOwnerObjects;`
- L199 _private member_ `TSharedPtr<SListView<TSharedPtr<FSignalFlowDashboardEntry>>> ActiveSourcesListView;`
- L200 _private member_ `TArray<TSharedPtr<FSignalFlowDashboardEntry>> ActiveSources;`
- L202 _private member_ `TSharedPtr<SListView<TSharedPtr<FSignalFlowDashboardEntry>>> ActiveBusesListView;`
- L203 _private member_ `TArray<TSharedPtr<FSignalFlowDashboardEntry>> ActiveBuses;`
- L205 _private member_ `TSharedPtr<SListView<TSharedPtr<FSignalFlowDashboardEntry>>> ActiveSubmixesListView;`
- L206 _private member_ `TArray<TSharedPtr<FSignalFlowDashboardEntry>> ActiveSubmixes;`
- L208 _private member_ `TSortedMap<FSignalFlowEntryKey, TSharedPtr<ISignalFlowNode>> FilteredEntries;`
- L209 _private member_ `TSet<FSignalFlowEntryKey> HighlightedPathKeys;`
- L210 _private member_ `TArray<TSharedPtr<ISignalFlowNode>> FilteredGraphNodes;`
- L211 _private member_ `TSharedPtr<SSplitter> MainSplitter;`
- L212 _private member_ `TSharedPtr<SSignalFlowGraph> GraphWidgetContents;`
- L214 _private member_ `TSharedPtr<SSignalFlowScrollBox> GraphHorizontalScrollBox;`
- L215 _private member_ `TSharedPtr<SSignalFlowScrollBox> GraphVerticalScrollBox;`
- L217 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L219 _private member_ `TSharedPtr<FSignalFlowDashboardEntry> SelectedItem;`
- L220 _private member_ `TSharedPtr<FSignalFlowDashboardEntry> HighlightedItem;`
- L221 _private member_ `FString SearchBoxFilterText;`
- L223 _private member_ `FSignalFlowNodeDetailFilterSettings NodeDetailFilters;`
- L224 _private member_ `FSignalFlowEntryTypeListExpansionSettings ActiveEntryMenuExpansionSettings;`
- L226 _private member_ `ESignalFlowJustification GraphJustification = ESignalFlowJustification::Edge;`
- L227 _private member_ `TOptional<FSignalFlowEntryKey> XPosFocusNodeEntryKey;`
- L229 _private member_ `static constexpr int32 MainSplitterSelectionPanelSlotIndex = 0;`
- L230 _private member_ `static constexpr int32 MainSplitterGraphSectionSlotIndex = 1;`
- L231 _private member_ `float GraphWidthRatio = 0.8f;`
- L232 _private member_ `float LargeNodePadding = 128.0f;`
- L233 _private member_ `float SmallNodePadding = 8.0f;`
- L235 _private member_ `bool bGraphRequiresRefresh = false;`
- L236 _private member_ `bool bAutoFocusAfterGraphRefresh = false;`
- L237 _private member_ `bool bShowNodeDetails = false;`
- L238 _private member_ `bool bPauseGraphOnSelect = false;`
- L239 _private member_ `bool bDisplayAmpPeakInDb = true;`
- L240 _private member_ `bool bAnimateWires = true;`
- L241 _private member_ `bool bSentSelectedNodeDestroyedNotification = false;`
- L244 _private member_ `FAssetEditorContextMenuHelper AssetContextMenuHelper;`

#### struct `UE::Audio::Insights::FSignalFlowDashboardViewFactory::SRowWidget`  
`struct SRowWidget : public STableRow<TSharedPtr<FSignalFlowDashboardEntry>>`  
_L57-69_
- inherits: `STableRow<TSharedPtr<FSignalFlowDashboardEntry>>`
- L59 _public function_ `SLATE_BEGIN_ARGS(SRowWidget) : _Style(nullptr)`
- L63 _public prototype_ `SLATE_STYLE_ARGUMENT(FTableRowStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FSignalFlowDashboardEntry> InData);`
- L68 _public member_ `TSharedPtr<FSignalFlowDashboardEntry> RowEntry;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Audio` (scope `UE`)
- L19 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SignalFlowNodes.h` (Public)


#### struct `UE::Audio::Insights::TreeDepthPair`  
`struct TreeDepthPair`  
_L18-62_
- desc: TreeDepthPair - Simple helper used to manage tree depth inside the signal flow graph LayerID - the layer the node sits in TreeDepth - what row inside the layer the node sits in
- L20 _public member_ `ESignalFlowEntryType LayerID = ESignalFlowEntryType::OwnerObject;`
- L21 _public member_ `int32 TreeDepth = 0;`
- L23 _public function_ `bool operator==(const TreeDepthPair& Other) const`
- L28 _public function_ `bool operator<(const TreeDepthPair& Other) const`
- L38 _public function_ `bool operator>(const TreeDepthPair& Other) const`
- L48 _public function_ `bool operator<=(const TreeDepthPair& Other) const`
- L53 _public function_ `bool operator>=(const TreeDepthPair& Other) const`

#### class `UE::Audio::Insights::ISignalFlowNode`  
`class ISignalFlowNode`  
_L66-112_
- desc: ISignalFlowNode : Class that holds data on a node's position, order, inputs, outputs etc. Specifically holds data on the filtered nodes in the graph
- L69 _public prototype_ `ISignalFlowNode() = delete;`
- L70 _public function_ `ISignalFlowNode(const int32 InTreeDepth, const ESignalFlowEntryType InTreeDepthLayerGroup, const double InTimestamp) : TreeDepthPair({ InTreeDepthLayerGroup, InTreeDepth }) , Timestamp(InTimestamp)`
- L76 _public prototype_ `virtual ~ISignalFlowNode() = default;`
- L78 _public prototype_ `virtual FSignalFlowEntryKey GetEntryKey() const = 0;`
- L79 _public prototype_ `virtual bool IsRealNode() const = 0;`
- L81 _public function_ `void SetTreeDepth(const ESignalFlowEntryType InTreeDepthLayerGroup, const int32 InTreeDepth)`
- L82 _public function_ `const TreeDepthPair& GetTreeDepth() const`
- L83 _public function_ `TreeDepthPair& GetTreeDepth()`
- L85 _public function_ `void SetNodeOrderID(const int32 InNodeOrderID)`
- L86 _public prototype_ `void ResetOrderID();`
- L87 _public function_ `int32 GetNodeOrderID() const`
- L88 _public function_ `int32 GetPreviousNodeOrderID() const`
- L89 _public function_ `bool NodeOrderIsValid() const`
- L91 _public function_ `double GetTimestamp() const`
- L93 _public member_ `TArray<FSignalFlowEntryKey> FilteredInputs;`
- L94 _public member_ `TArray<FSignalFlowEntryKey> FilteredOutputs;`
- L96 _public member_ `TArray<FSignalFlowEntryKey> FilteredLinkedSoundSources;`
- L97 _public member_ `TOptional<FSignalFlowEntryKey> FilteredLinkedSourceBus;`
- L99 _public member_ `TArray<FSignalFlowEntryKey> FilteredLinkedBusPatchInputs;` — Entries that send bus patch connections to this node
- L100 _public member_ `TArray<FSignalFlowEntryKey> FilteredLinkedBusPatchOutputs;` — Entries that this node sends bus patch connections to
- L102 _public member_ `float XPos = 0.0f;`
- L105 _private member_ `static constexpr int32 INVALID_NODE_ORDER_ID = -1;`
- L107 _private member_ `TreeDepthPair TreeDepthPair;`
- L108 _private member_ `int32 NodeOrderID = INVALID_NODE_ORDER_ID;`
- L109 _private member_ `int32 PreviousNodeOrderID = INVALID_NODE_ORDER_ID;`
- L111 _private member_ `const double Timestamp = 0.0;`

#### class `UE::Audio::Insights::FSignalFlowEntryNode`  
`class FSignalFlowEntryNode : public ISignalFlowNode`  
_L115-130_
- inherits: `ISignalFlowNode`
- desc: FSignalFlowEntryNode : A node with a valid entry - directly maps to a FSignalFlowDashboardEntry created inside FSignalFlowTraceProvider
- L118 _public prototype_ `FSignalFlowEntryNode() = delete;`
- L119 _public function_ `FSignalFlowEntryNode(TSharedPtr<FSignalFlowDashboardEntry> InEntry, const int32 InTreeDepth, const ESignalFlowEntryType InTreeDepthLayerGroup, const double InTimestamp) : ISignalFlowNode(InTreeDepth, InTreeDepthLayerGroup, InTimestamp) , Entry(InEntry)`
- L125 _public prototype_ `virtual FSignalFlowEntryKey GetEntryKey() const override;`
- L127 _public function_ `virtual bool IsRealNode() const override`
- L129 _public member_ `TSharedPtr<FSignalFlowDashboardEntry> Entry;`

#### class `UE::Audio::Insights::FDummyConnectionNode`  
`class FDummyConnectionNode : public ISignalFlowNode`  
_L134-152_
- inherits: `ISignalFlowNode`
- desc: FDummyConnectionNode : A fake invisible node placed between the input and output of two other nodes Used to help position and order real nodes whilst avoiding nodes getting in each other's way and crossing connections
- L137 _public prototype_ `FDummyConnectionNode() = delete;`
- L138 _public function_ `FDummyConnectionNode(const FSignalFlowEntryKey& InEntryKey, const int32 InTreeDepth, const ESignalFlowEntryType InTreeDepthLayerGroup, const double InTimestamp) : ISignalFlowNode(InTreeDepth, InTreeDepthLayerGroup, InTimestamp) , EntryKey(InEntryKey)`
- L144 _public function_ `virtual FSignalFlowEntryKey GetEntryKey() const override`
- L145 _public function_ `virtual bool IsRealNode() const override`
- L147 _public member_ `FSignalFlowEntryKey ConnectionInputKey;`
- L148 _public member_ `FSignalFlowEntryKey ConnectionOutputKey;`
- L151 _private member_ `const FSignalFlowEntryKey EntryKey;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Audio` (scope `UE`)
- L11 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L58 _function_ `friend int32 GetTypeHash(const TreeDepthPair& Key)` (scope `UE::Audio::Insights`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SoundDashboardViewFactory.h` (Public)


#### enum `UE::Audio::Insights::ESoundDashboardFilterFlags`  
`enum class ESoundDashboardFilterFlags : uint32`  
_L20-29_
- L22 _public enumerator_ `None = 0`
- L23 _public enumerator_ `MetaSound = 1 << 0`
- L24 _public enumerator_ `SoundCue = 1 << 1`
- L25 _public enumerator_ `ProceduralSource = 1 << 2`
- L26 _public enumerator_ `SoundWave = 1 << 3`
- L27 _public enumerator_ `SoundCueTemplate = 1 << 4`
- L28 _public enumerator_ `Pinned = 1 << 5`

#### enum `UE::Audio::Insights::EMuteSoloMode`  
`enum class EMuteSoloMode : uint8`  
_L34-38_
- L36 _public enumerator_ `Mute`
- L37 _public enumerator_ `Solo`

#### class `UE::Audio::Insights::FSoundDashboardFilter`  
`class FSoundDashboardFilter : public FGenericFilter<ESoundDashboardFilterFlags>`  
_L41-68_
- inherits: `FGenericFilter<ESoundDashboardFilterFlags>`
- L44 _public function_ `FSoundDashboardFilter(ESoundDashboardFilterFlags InFlags, const FString& InName, const FText& InDisplayName, const FName& InIconName, const FText& InToolTipText, FLinearColor InColor, TSharedPtr<FFilterCategory> InCategory) : FGenericFilter<ESoundDashboardFilterFlags>(InCategory, InName, InDisplayName, FGenericFilter<ESoundDashboardFilterFlags>::FOnItemFiltered()) , Flags(InFlags)`
- L59 _public function_ `bool IsActive() const`
- L60 _public function_ `ESoundDashboardFilterFlags GetFlags() const`
- L63 _private function_ `virtual void ActiveStateChanged(bool bActive) override`
- L64 _private function_ `virtual bool PassesFilter(ESoundDashboardFilterFlags InItem) const override`
- L66 _private member_ `ESoundDashboardFilterFlags Flags;`
- L67 _private member_ `bool bIsActive = false;`

#### class `UE::Audio::Insights::FPinnedSoundEntryWrapper`  
`class FPinnedSoundEntryWrapper`  
_L75-100_
- desc: Helper class for pinned items in the dashboard tree - Contains a weak handle to the original entry (OriginalDataEntry) which is updated from the trace provider - Copies updated params to PinnedSectionEntry for display
- L78 _public prototype_ `FPinnedSoundEntryWrapper() = delete;`
- L79 _public prototype_ `FPinnedSoundEntryWrapper(const TSharedPtr<IDashboardDataTreeViewEntry>& OriginalEntry);`
- L81 _public function_ `TSharedPtr<IDashboardDataTreeViewEntry> GetPinnedSectionEntry() const`
- L82 _public function_ `TSharedPtr<IDashboardDataTreeViewEntry> GetOriginalDataEntry() const`
- L84 _public prototype_ `TSharedPtr<FPinnedSoundEntryWrapper> AddChildEntry(const TSharedPtr<IDashboardDataTreeViewEntry> Child);`
- L86 _public prototype_ `void UpdateParams();`
- L88 _public prototype_ `void CleanUp();`
- L89 _public prototype_ `void MarkToDelete();`
- L91 _public prototype_ `bool EntryIsValid() const;`
- L93 _public prototype_ `TSharedPtr<IDashboardDataTreeViewEntry> FindOriginalEntryInChildren(const TSharedPtr<IDashboardDataTreeViewEntry>& RootPinnedEntry);`
- L95 _public member_ `TArray<TSharedPtr<FPinnedSoundEntryWrapper>> PinnedWrapperChildren;`
- L98 _private member_ `TSharedPtr<IDashboardDataTreeViewEntry> PinnedSectionEntry;`
- L99 _private member_ `TWeakPtr<IDashboardDataTreeViewEntry> OriginalDataEntry;`

#### class `UE::Audio::Insights::FSoundDashboardViewFactory`  
`class FSoundDashboardViewFactory : public FTraceTreeDashboardViewFactory`  
_L102-270_
- inherits: `FTraceTreeDashboardViewFactory`
- L105 _public prototype_ `FSoundDashboardViewFactory();`
- L106 _public prototype_ `virtual ~FSoundDashboardViewFactory();`
- L108 _public prototype_ `virtual FName GetName() const override;`
- L109 _public prototype_ `virtual FText GetDisplayName() const override;`
- L110 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L111 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L112 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L113 _public prototype_ `virtual void ProcessEntries(FTraceTreeDashboardViewFactory::EProcessReason Reason) override;`
- L115 _public prototype_ `TMap<FName, FSoundPlotsWidgetView::FPlotColumnInfo> GetPlotColumnInfo();`
- L117 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnProcessPlotData, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& , const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& , const bool );`
- L118 _public member_ `FOnProcessPlotData OnProcessPlotData;`
- L120 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePlotVisibility, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& );`
- L121 _public member_ `FOnUpdatePlotVisibility OnUpdatePlotVisibility;`
- L123 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePlotSelection, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& );`
- L124 _public member_ `FOnUpdatePlotSelection OnUpdatePlotSelection;`
- L127 _private prototype_ `void BindCommands();`
- L129 _private prototype_ `virtual TSharedPtr<SWidget> GetFilterBarWidget() override;`
- L130 _private prototype_ `virtual TSharedPtr<SWidget> GetFilterBarButtonWidget() override;`
- L132 _private prototype_ `virtual void SetSearchBoxFilterText(const FText& NewText) override;`
- L134 _private prototype_ `bool IsRootItem(const TSharedRef<IDashboardDataTreeViewEntry>& InEntry) const;`
- L136 _private prototype_ `TSharedRef<SWidget> GenerateWidgetForRootColumn(const TSharedRef<FTraceTreeDashboardViewFactory::SRowWidget>& InRowWidget, const TSharedRef<IDashboardDataTreeViewEntry>& InRowData, const FName& InColumn, const FText& InValueText);`
- L137 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const TSharedRef<FTraceTreeDashboardViewFactory::SRowWidget>& InRowWidget, const TSharedRef<IDashboardDataTreeViewEntry>& InRowData, const FName& InColumn) override;`
- L139 _private prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<IDashboardDataTreeViewEntry> Item, const TSharedRef<STableViewBase>& OwnerTable) override;`
- L141 _private prototype_ `virtual TSharedPtr<SWidget> OnConstructContextMenu() override;`
- L142 _private prototype_ `virtual void OnSelectionChanged(TSharedPtr<IDashboardDataTreeViewEntry> SelectedItem, ESelectInfo::Type SelectInfo) override;`
- L143 _private prototype_ `virtual FReply OnDataRowKeyInput(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) const override;`
- L145 _private prototype_ `virtual const TMap<FName, FTraceTreeDashboardViewFactory::FHeaderRowColumnData>& GetHeaderRowColumns() const override;`
- L146 _private prototype_ `virtual void OnHiddenColumnsListChanged() override;`
- L147 _private prototype_ `virtual const TMap<FName, FTraceTreeDashboardViewFactory::FColumnData>& GetColumns() const override;`
- L149 _private prototype_ `virtual void SortTable() override;`
- L150 _private prototype_ `virtual bool IsColumnSortable(const FName& ColumnId) const override;`
- L151 _private function_ `virtual TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& GetTreeItemsSource() override`
- L152 _private prototype_ `virtual bool ResetTreeData() override;`
- L154 _private function_ `virtual int32 GetDisplayedTreeDepth() const override`
- L155 _private prototype_ `virtual bool ShouldAutoExpand(const TSharedPtr<IDashboardDataTreeViewEntry>& Item) const override;`
- L157 _private prototype_ `void ChangeTreeViewingMode(const ESoundDashboardTreeViewingOptions SelectedMode, const bool bUpdateEditorSettings = true);`
- L158 _private prototype_ `void BuildViewOptionsMenuContent(FMenuBuilder& MenuBuilder);`
- L160 _private prototype_ `void ChangeAutoExpandMode(const ESoundDashboardAutoExpandOptions SelectedMode, const bool bUpdateEditorSettings = true);`
- L161 _private prototype_ `void RefreshExpansionChecks(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry);`
- L162 _private prototype_ `void BuildAutoExpandMenuContent(FMenuBuilder& MenuBuilder);`
- L163 _private prototype_ `void BuildVisibleColumnsMenuContent(FMenuBuilder& MenuBuilder);`
- L165 _private prototype_ `void FilterText();`
- L166 _private prototype_ `void RecursiveSort(TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& OutTree, TFunctionRef<bool(const FSoundDashboardEntry&, const FSoundDashboardEntry&)> Predicate);`
- L167 _private prototype_ `void SortByPredicate(TFunctionRef<bool(const FSoundDashboardEntry&, const FSoundDashboardEntry&)> Predicate);`
- L169 _private prototype_ `TSharedRef<SWidget> OnGetSettingsMenuContent();`
- L170 _private prototype_ `TSharedRef<SWidget> MakeSettingsButtonWidget();`
- L172 _private prototype_ `void UpdateMaxStoppedSoundTimeout();`
- L175 _private prototype_ `void OnReadEditorSettings(const FSoundDashboardSettings& Settings);`
- L176 _private prototype_ `void OnWriteEditorSettings(FSoundDashboardSettings& Settings);`
- L178 _private prototype_ `TSharedRef<SWidget> MakeMuteSoloWidget();`
- L180 _private prototype_ `TSharedRef<SWidget> CreateMuteSoloButton(const TSharedRef<FTraceTreeDashboardViewFactory::SRowWidget>& InRowWidget, const TSharedRef<IDashboardDataTreeViewEntry>& InRowData, const FName& InColumn, TFunction<void(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& )> MuteSoloToggleFunc, TFunctionRef<bool(const IDashboardDataTreeViewEntry& , const bool )> IsMuteSoloFunc);`
- L186 _private prototype_ `void ToggleMuteSoloEntries(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& InEntries, const EMuteSoloMode InMuteSoloMode);`
- L187 _private prototype_ `void MuteSoloFilteredEntries();`
- L189 _private prototype_ `TArray<TObjectPtr<UObject>> GetSelectedEditableAssets() const;`
- L192 _private prototype_ `void OnTimingViewTimeMarkerChanged(double InTimeMarker);`
- L193 _private prototype_ `void HandleOnTimeControlMethodReset();`
- L195 _private prototype_ `TSharedRef<SWidget> MakeShowPlotWidget();`
- L197 _private prototype_ `TSharedRef<SWidget> CreateShowPlotColumnButton(const TSharedRef<FTraceTreeDashboardViewFactory::SRowWidget>& InRowWidget, const TSharedRef<IDashboardDataTreeViewEntry>& InRowData, const FName& InColumn, TFunction<void(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& , const bool )> ShowPlotToggleFunc, TFunctionRef<bool(const IDashboardDataTreeViewEntry& )> IsPlotActiveFunc);`
- L203 _private prototype_ `void ToggleShowPlotEntries(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& InEntries, const bool bShowPlot, const bool bIgnoreCategories = false);`
- L204 _private prototype_ `void SetShowPlotRecursive(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry, const bool bShowPlot);`
- L205 _private prototype_ `void SetShowPlot(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry, const bool bShowPlot);`
- L206 _private prototype_ `void CleanUpParentPlotEnabledStates(const TSet<uint32>& ActiveSoundsToggledOff);`
- L208 _private prototype_ `void SetShowPlotVisibleRecursive(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry);`
- L209 _private prototype_ `void PlotFilteredEntries();`
- L210 _private prototype_ `void ResetPlots();`
- L211 _private prototype_ `void BroadcastPlotUpdate();`
- L212 _private prototype_ `void ProcessPlotData();`
- L214 _private prototype_ `bool SelectedItemsIncludesAnAsset() const;`
- L215 _private prototype_ `bool SelectionIncludesUnpinnedItem() const;`
- L216 _private prototype_ `void ClearSelection();`
- L218 _private prototype_ `void PinSound();`
- L219 _private prototype_ `void UnpinSound();`
- L221 _private prototype_ `void PinSelectedItems(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& SelectedItems);`
- L222 _private prototype_ `void UnpinSelectedItems(const TSharedPtr<FPinnedSoundEntryWrapper>& PinnedWrapperEntry, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& SelectedItems, const bool bSelectionContainsAssets);`
- L224 _private prototype_ `void RecreatePinnedEntries(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry);`
- L226 _private prototype_ `void MarkBranchAsPinned(const TSharedPtr<IDashboardDataTreeViewEntry> Entry, const bool bIsPinned);`
- L227 _private prototype_ `void InitPinnedItemEntries();`
- L228 _private prototype_ `void CreatePinnedEntry(TSharedPtr<IDashboardDataTreeViewEntry> Entry);`
- L229 _private prototype_ `void UpdatePinnedSection();`
- L230 _private prototype_ `void RebuildPinnedSection();`
- L233 _private prototype_ `void BrowseSoundAsset() const;`
- L234 _private prototype_ `void OpenSoundAsset() const;`
- L237 _private member_ `static constexpr ESoundDashboardFilterFlags AllFilterFlags = ESoundDashboardFilterFlags::MetaSound | ESoundDashboardFilterFlags::SoundCue | ESoundDashboardFilterFlags::ProceduralSource | ESoundDashboardFilterFlags::SoundWave | ESoundDashboardFilterFlags::SoundCueTemplate | ESoundDashboardFilterFlags::Pinned;`
- L245 _private member_ `TSharedPtr<FPinnedSoundEntryWrapper> PinnedItemEntries;`
- L246 _private member_ `TArray<TSharedPtr<IDashboardDataTreeViewEntry>> FullTree;`
- L248 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L249 _private member_ `TSharedPtr<SWidget> SoundsFilterBar;`
- L250 _private member_ `TSharedPtr<SWidget> SoundsFilterBarButton;`
- L252 _private member_ `ESoundDashboardTreeViewingOptions TreeViewingMode = ESoundDashboardTreeViewingOptions::FullTree;`
- L253 _private member_ `ESoundDashboardAutoExpandOptions AutoExpandMode = ESoundDashboardAutoExpandOptions::Categories;`
- L254 _private member_ `ESoundDashboardFilterFlags SelectedFilterFlags = AllFilterFlags;`
- L256 _private member_ `float RecentlyStoppedSoundTimeout = 3.0f;`
- L258 _private member_ `bool bIsPinnedCategoryFilterEnabled = true;`
- L259 _private member_ `bool bPinnedSectionNeedsRebuild = false;`
- L260 _private member_ `bool bShowRecentlyStoppedSounds = false;`
- L261 _private member_ `bool bTreeViewModeChanged = false;`
- L262 _private member_ `bool bDisplayAmpPeakInDb = true;`
- L263 _private member_ `bool bIsMuteFilteredMode = false;`
- L264 _private member_ `bool bIsSoloFilteredMode = false;`
- L265 _private member_ `bool bIsPlotFilteredMode = false;`
- L267 _private member_ `TSharedPtr<FVisibleColumnsSettingsMenu<FSoundDashboardVisibleColumns>> VisibleColumnsSettingsMenu;`
- L268 _private member_ `TOptional<FSoundDashboardVisibleColumns> InitVisibleColumnSettings;`
- L269 _private member_ `FSoundPlotsDashboardPlotRanges DefaultPlotRanges;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Audio` (scope `UE`)
- L16 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(ESoundDashboardFilterFlags);` (scope `UE::Audio::Insights`)
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnProcessPlotData, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& , const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& , const bool );`
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePlotVisibility, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& );`
- L123 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePlotSelection, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& );`

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SoundPlotsDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::FSoundPlotsDashboardViewFactory`  
`class FSoundPlotsDashboardViewFactory : public IDashboardViewFactory, public TSharedFromThis<FSoundPlotsDashboardViewFactory>`  
_L15-40_
- inherits: `IDashboardViewFactory,TSharedFromThis<FSoundPlotsDashboardViewFactory>`
- L18 _public prototype_ `virtual ~FSoundPlotsDashboardViewFactory() = default;`
- L20 _public prototype_ `virtual FName GetName() const override;`
- L21 _public prototype_ `virtual FText GetDisplayName() const override;`
- L22 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L23 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L24 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L26 _public prototype_ `void InitPlots(const TSharedRef<FSoundDashboardViewFactory> SoundsDashboard);`
- L29 _private member_ `TSharedPtr<FSoundPlotsWidgetView> PlotsWidget;`
- L31 _private prototype_ `void ProcessPlotData(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& DataViewEntries, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& SelectedEntries, const bool bForceUpdate = false);`
- L33 _private prototype_ `void UpdatePlotVisibility(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& DataViewEntries);`
- L34 _private prototype_ `void UpdatePlotSelection(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& SelectedEntries);`
- L36 _private member_ `FDelegateHandle OnUpdatePlotVisibility;`
- L37 _private member_ `FDelegateHandle OnUpdatePlotSelection;`
- L39 _private member_ `FDelegateHandle OnProcessPlotData;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Audio` (scope `UE`)
- L10 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SoundPlotsWidgetView.h` (Public)


#### class `UE::Audio::Insights::FSoundPlotsWidgetView`  
`class FSoundPlotsWidgetView : public TSharedFromThis<FSoundPlotsWidgetView>`  
_L16-151_
- inherits: `TSharedFromThis<FSoundPlotsWidgetView>`
- L34 _public prototype_ `FSoundPlotsWidgetView(TMap<FName, FSoundPlotsWidgetView::FPlotColumnInfo>&& InColumnInfo, const TFunction<bool(const IDashboardDataTreeViewEntry& InEntry)> InIsPlotEnabledForEntryFunc);`
- L35 _public prototype_ `virtual ~FSoundPlotsWidgetView();`
- L37 _public prototype_ `TSharedRef<SWidget> MakeWidget();`
- L38 _public prototype_ `void ProcessPlotData(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& DataViewEntries, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& SelectedEntries, const bool bForceUpdate = false);`
- L39 _public prototype_ `void UpdatePlotVisibility(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& DataViewEntries);`
- L41 _public prototype_ `void UpdatePlotSelection(const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& SelectedEntries);`
- L44 _private typedef_ `using FPlotCurvePoint = SAudioCurveView::FCurvePoint;`
- L45 _private typedef_ `using FPointDataPerCurveMap = TMap<uint64, TArray<FPlotCurvePoint>>;` — Map of source id to data point array
- L46 _private typedef_ `using FLatestTimestampPerCurveMap = TMap<uint64, double>;` — Map of source id to most recent timestamp associated with any data
- L47 _private typedef_ `using FPlotCurveMetadata = SAudioCurveView::FCurveMetadata;`
- L49 _private prototype_ `void OnAnalysisStarting(const double Timestamp);`
- L51 _private prototype_ `void OnPIEStarted(bool bSimulating);`
- L52 _private prototype_ `void OnPIEStopped(bool bSimulating);`
- L53 _private prototype_ `void OnPIEPaused(bool bSimulating);`
- L54 _private prototype_ `void OnPIEResumed(bool bSimulating);`
- L56 _private prototype_ `void OnTraceStopped(FTraceAuxiliary::EConnectionType InTraceType, const FString& InTraceDestination);`
- L58 _private prototype_ `void OnAudioInsightsComponentTabSpawn();`
- L59 _private prototype_ `void OnSessionAnalysisCompleted();`
- L62 _private prototype_ `void OnTimingViewTimeMarkerChanged(double InTimeMarker);`
- L63 _private prototype_ `void OnTimeControlMethodReset();`
- L65 _private prototype_ `FReply OnHandleKeyDown(const FGeometry& Geometry, const FKeyEvent& KeyEvent);`
- L67 _private prototype_ `TSharedRef<SWidget> MakePlotsWidget();`
- L68 _private prototype_ `void ConstructPlotsWidgetContents();`
- L69 _private prototype_ `void BindCommands();`
- L70 _private prototype_ `void ResetInspectTimestamp();`
- L72 _private prototype_ `void CollectDataRecursive(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& SelectedEntries, bool& bOutHasNewMetadata);`
- L73 _private prototype_ `void ResetPlots();`
- L75 _private prototype_ `void UpdatePlotVisibilityRecursive(const TSharedPtr<IDashboardDataTreeViewEntry>& Entry);`
- L77 _private prototype_ `void UpdatePlot();`
- L80 _private prototype_ `const TFunction<const ::Audio::TCircularAudioBuffer<FDataPoint>& (const IDashboardDataTreeViewEntry& InEntry)> GetPlotColumnDataFunc(const FName& ColumnName);` — Column information used by plot widgets, keyed by column name. These keys should be a subset of the keys in GetColumns().
- L81 _private prototype_ `const TFunction<float (const float)> GetPlotColumnUnitConversionFunc(const FName& ColumnName);`
- L82 _private prototype_ `const FNumberFormattingOptions* GetPlotColumnNumberFormat(const FName& ColumnName);`
- L83 _private prototype_ `FFloatInterval GetPlotColumnCustomizedOrDefaultYRange(const FName& ColumnName);`
- L84 _private prototype_ `const FText GetPlotColumnDisplayName(const FName& ColumnName);`
- L85 _private prototype_ `FText GetAdditionalTooltipText() const;`
- L87 _private prototype_ `TOptional<float> GetPlotColumnYRangeFloatMetaData(const FName& ColumnName, const FName& MetaDataKey);`
- L88 _private prototype_ `TOptional<FFloatInterval> GetPlotColumnCustomizedYRange(const FName& ColumnName);`
- L89 _private prototype_ `bool GetPlotColumnUseCustomYRange(const FName& ColumnName);`
- L90 _private prototype_ `void SetPlotColumnUseCustomYRange(const FName& ColumnName, bool bUseCustomYRange);`
- L91 _private prototype_ `void SetPlotColumnCustomYRangeMin(const FName& ColumnName, float Value, TOptional<ETextCommit::Type> CommitType = NullOpt);`
- L92 _private prototype_ `void SetPlotColumnCustomYRangeMax(const FName& ColumnName, float Value, TOptional<ETextCommit::Type> CommitType = NullOpt);`
- L93 _private prototype_ `void SetTimestampFromCurveView(const double Timestamp);`
- L95 _private prototype_ `TRange<double> GetViewRange();`
- L97 _private prototype_ `bool GetIsPlotEnabledForEntry(const IDashboardDataTreeViewEntry& InEntry) const;`
- L100 _private member_ `TMap<FName, TSharedPtr<FPointDataPerCurveMap>> PlotWidgetCurveIdToPointDataMapPerColumn;` — Curve points per timestamp per source id per column name
- L104 _private member_ `TMap<FName, TSharedPtr<FLatestTimestampPerCurveMap>> ColumnNameToLatestTimestamp;` — Map to track the latest timestamp for each column's data points. Used to avoid adding duplicate data to the plot if this widget view is updated at a higher rate than the data is received
- L107 _private member_ `TSharedPtr<TMap<uint64, FPlotCurveMetadata>> PlotWidgetMetadataPerCurve;` — SourceId to metadata for the corresponding curve
- L110 _private member_ `TArray<FName> ColumnNames;` — Column names for plot selector widget
- L113 _private member_ `const TMap<FName, FSoundPlotsWidgetView::FPlotColumnInfo> ColumnInfo;` — Func to access column data from the dashboard using this Plots view
- L116 _private member_ `const TFunction<bool(const IDashboardDataTreeViewEntry& InEntry)> IsPlotEnabledForEntryFunc;` — Func to enquire whether plotting is enabled for an entry
- L118 _private member_ `double BeginTimestamp = TNumericLimits<double>::Max();`
- L119 _private member_ `double CurrentTimestamp = TNumericLimits<double>::Lowest();`
- L121 _private member_ `TRange<double> CurrentRange { TNumericLimits<double>::Lowest(), TNumericLimits<double>::Lowest() };`
- L132 _private member_ `EGameState GameState = EGameState::Stopped;`
- L134 _private member_ `TSharedPtr<SAudioCurveView> PlotWidget;`
- L135 _private member_ `TSharedPtr<SComboBox<FName>> ComboBox;`
- L136 _private member_ `FName SelectedPlotColumnName;`
- L138 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L141 _private member_ `double PreviousTime = 0.0;`
- L142 _private member_ `double CurrentRangeUpperBound = 0.0;`
- L145 _private member_ `bool bTimeMarkerMoved = false;`
- L148 _private member_ `bool bIsTraceActive = false;`
- L149 _private member_ `bool bIsPIEPaused = false;`

#### struct `UE::Audio::Insights::FSoundPlotsWidgetView::FPlotColumnInfo`  
`struct FPlotColumnInfo`  
_L21-32_
- desc: Main information about what data is being plotted in this widget, along with functions to gather information. This data is passed into the constructor of this widget in a TMap of Column name -> Plot Column Info
- L23 _public member_ `const FText ColumnDisplayName;`
- L24 _public member_ `const TFunction<const ::Audio::TCircularAudioBuffer<FDataPoint>& (const IDashboardDataTreeViewEntry& InData)> DataFunc;`
- L25 _public member_ `const TFunction<float(const float)> UnitConversionFunc;`
- L26 _public member_ `const TFunction<const FNumberFormattingOptions*()> GetFormatOptionsFunc;`
- L27 _public member_ `const TFunction<const FProperty*()> GetYRangePropertyFunc;`
- L28 _public member_ `const TFunction<bool()> GetUseCustomYRangeFunc;`
- L29 _public member_ `const TFunction<void(bool)> SetUseCustomYRangeFunc;`
- L30 _public member_ `const TFunction<FFloatInterval()> GetCustomYRangeFunc;`
- L31 _public member_ `const TFunction<void(const FFloatInterval&, TOptional<ETextCommit::Type>)> SetCustomYRangeFunc;`

#### enum `UE::Audio::Insights::FSoundPlotsWidgetView::EGameState`  
`enum class EGameState : uint8`  
_L123-130_
- L125 _public enumerator_ `Running`
- L126 _public enumerator_ `Stopped`
- L127 _public enumerator_ `Paused`
- L128 _public enumerator_ `LoadingTraceFile`
- L129 _public enumerator_ `ControlledByTimemarker`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Audio` (scope `UE`)
- L14 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/SubmixDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::FSubmixDashboardViewFactory`  
`class FSubmixDashboardViewFactory : public FTraceObjectTableDashboardViewFactory`  
_L14-58_
- inherits: `FTraceObjectTableDashboardViewFactory`
- L17 _public prototype_ `FSubmixDashboardViewFactory();`
- L18 _public prototype_ `virtual ~FSubmixDashboardViewFactory();`
- L20 _public prototype_ `virtual FName GetName() const override;`
- L21 _public prototype_ `virtual FText GetDisplayName() const override;`
- L22 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L23 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L24 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L26 _public prototype_ `static void SendSubmixEnvelopeFollowerCVar(const bool bEnableEnvelopeFollower, const FSubmixDashboardEntry& SubmixDashboardEntry);`
- L29 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(TSharedRef<IDashboardDataViewEntry> InRowData, const FName& InColumnName) override;`
- L30 _protected prototype_ `virtual void ProcessEntries(FTraceTableDashboardViewFactory::EProcessReason Reason) override;`
- L31 _protected prototype_ `virtual const TMap<FName, FTraceTableDashboardViewFactory::FColumnData>& GetColumns() const override;`
- L33 _protected prototype_ `void RebuildAudioMeters() const;`
- L34 _protected prototype_ `bool ShouldUpdateAudioMeter(const FSubmixDashboardEntry& InSubmixDashboardEntry) const;`
- L35 _protected prototype_ `void UpdateAudioMeters() const;`
- L36 _protected prototype_ `void ReactivateAudioMeters();`
- L38 _protected prototype_ `void SetSubmixEnvelopeFollowerEnabled(const FSubmixDashboardEntry& InSubmixDashboardEntry, const bool bInEnabled);`
- L40 _protected prototype_ `virtual void SortTable() override;`
- L42 _protected prototype_ `void HandleOnSubmixAdded(const uint32 InSubmixId);`
- L43 _protected prototype_ `void HandleOnSubmixRemoved(const uint32 InSubmixId);`
- L44 _protected prototype_ `void HandleOnSubmixLoaded(const uint32 InSubmixId);`
- L45 _protected prototype_ `void HandleOnTimeMarkerUpdated();`
- L46 _protected prototype_ `void HandleOnTimeControlMethodReset();`
- L48 _protected prototype_ `void RequestListRefresh();`
- L50 _protected member_ `TSharedPtr<FSubmixTraceProvider> SubmixProvider;`
- L52 _protected member_ `TSet<uint32> CheckedSubmixes;`
- L53 _protected member_ `TSet<uint32> PendingToReactivateSubmixIds;`
- L55 _protected member_ `bool bShouldRebuildAudioMeters = false;`
- L56 _protected member_ `bool bListRefreshed = false;`
- L57 _protected member_ `bool bShouldReactivateAudioMeters = false;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/TableDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::SScrollableListView`  
`template <typename ItemType> class SScrollableListView : public SListView<ItemType>`  
_L19-36_
- inherits: `SListView<ItemType>`
- L22 _public function_ `void Construct(const typename SListView<ItemType>::FArguments& InArgs)`
- L27 _public function_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMouseWheel);`
- L35 _public member_ `FOnMouseWheel OnMouseWheelDetected;`

#### class `UE::Audio::Insights::IObjectDashboardEntry`  
`class IObjectDashboardEntry : public IDashboardDataViewEntry`  
_L38-47_
- inherits: `IDashboardDataViewEntry`
- L41 _public prototype_ `virtual ~IObjectDashboardEntry() = default;`
- L43 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L44 _public function_ `virtual FString GetObjectPath() const`
- L45 _public prototype_ `virtual const UObject* GetObject() const = 0;`
- L46 _public prototype_ `virtual UObject* GetObject() = 0;`

#### struct `UE::Audio::Insights::FSoundAssetDashboardEntry`  
`struct FSoundAssetDashboardEntry : public IObjectDashboardEntry`  
_L49-64_
- inherits: `IObjectDashboardEntry`
- L51 _public prototype_ `virtual ~FSoundAssetDashboardEntry() = default;`
- L53 _public prototype_ `virtual FText GetDisplayName() const override;`
- L54 _public function_ `virtual FString GetObjectPath() const override`
- L55 _public prototype_ `virtual const UObject* GetObject() const override;`
- L56 _public prototype_ `virtual UObject* GetObject() override;`
- L57 _public prototype_ `virtual bool IsValid() const override;`
- L60 _public member_ `uint32 PlayOrder = INDEX_NONE;`
- L61 _public member_ `uint64 ComponentId = TNumericLimits<uint64>::Max();`
- L62 _public member_ `double Timestamp = 0.0;`
- L63 _public member_ `FString Name;`

#### class `UE::Audio::Insights::FTraceTableDashboardViewFactory`  
`class FTraceTableDashboardViewFactory : public FTraceDashboardViewFactoryBase, public TSharedFromThis<FTraceTableDashboardViewFactory>`  
_L66-240_
- inherits: `FTraceDashboardViewFactoryBase,TSharedFromThis<FTraceTableDashboardViewFactory>`
- L69 _public prototype_ `FTraceTableDashboardViewFactory();`
- L70 _public prototype_ `virtual ~FTraceTableDashboardViewFactory() = default;`
- L89 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(TSharedRef<IDashboardDataViewEntry> InRowData, const FName& Column);`
- L90 _public prototype_ `virtual FReply OnDataRowKeyInput(const FGeometry& Geometry, const FKeyEvent& KeyEvent) const;`
- L91 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L92 _public prototype_ `virtual void RefreshFilteredEntriesListView() override;`
- L96 _protected function_ `template<typename TableProviderType> bool FilterEntries(TFunctionRef<bool(const IDashboardDataViewEntry&)> IsFiltered)`
- L142 _protected function_ `template <typename TDataViewEntry> void SortByPredicate(TFunctionRef<bool(const TDataViewEntry&, const TDataViewEntry&)> Predicate)`
- L166 _protected function_ `virtual bool IsDebugDrawEnabled() const`
- L167 _protected function_ `virtual void DebugDraw(float InElapsed, const TArray<TSharedPtr<IDashboardDataViewEntry>>& InSelectedItems, ::Audio::FDeviceId InAudioDeviceId) const`
- L185 _protected prototype_ `virtual const TMap<FName, FColumnData>& GetColumns() const = 0;`
- L187 _protected prototype_ `const FText& GetSearchFilterText() const;`
- L189 _protected prototype_ `virtual void SortTable() = 0;`
- L190 _protected function_ `virtual bool IsColumnSortable(const FName& ColumnId) const`
- L192 _protected function_ `virtual void OnHiddenColumnsListChanged()`
- L194 _protected function_ `virtual TSharedPtr<SWidget> CreateFilterBarButtonWidget()`
- L195 _protected function_ `virtual TSharedRef<SWidget> CreateFilterBarWidget()`
- L197 _protected prototype_ `virtual TSharedRef<SWidget> CreateSettingsButtonWidget();`
- L198 _protected function_ `virtual TSharedRef<SWidget> OnGetSettingsMenuContent()`
- L199 _protected function_ `virtual FText OnGetSettingsMenuToolTip()`
- L201 _protected prototype_ `virtual TSharedPtr<SWidget> OnConstructContextMenu();`
- L202 _protected prototype_ `virtual void OnSelectionChanged(TSharedPtr<IDashboardDataViewEntry> SelectedItem, ESelectInfo::Type SelectInfo);`
- L203 _protected function_ `virtual bool ClearSelectionOnClick() const`
- L205 _protected function_ `virtual bool EnableHorizontalScrollBox() const`
- L206 _protected function_ `virtual void OnListViewScrolled(double InScrollOffset)`
- L207 _protected function_ `virtual void OnFinishedScrolling()`
- L209 _protected function_ `virtual const FTableRowStyle* GetRowStyle() const`
- L210 _protected prototype_ `virtual FSlateColor GetRowColor(const TSharedPtr<IDashboardDataViewEntry>& InRowDataPtr);`
- L212 _protected member_ `FDelegateHandle OnEntriesUpdatedHandle;`
- L214 _protected member_ `TArray<TSharedPtr<IDashboardDataViewEntry>> DataViewEntries;`
- L216 _protected member_ `TSharedPtr<SWidget> DashboardWidget;`
- L217 _protected member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L218 _protected member_ `TSharedPtr<SScrollableListView<TSharedPtr<IDashboardDataViewEntry>>> FilteredEntriesListView;`
- L219 _protected member_ `TSharedPtr<SWidget> FilterBarButton;`
- L220 _protected member_ `TSharedPtr<SSearchBox> SearchBoxWidget;`
- L222 _protected member_ `FName SortByColumn;`
- L223 _protected member_ `EColumnSortMode::Type SortMode = EColumnSortMode::None;`
- L227 _private prototype_ `virtual void UpdateDebugDraw(const float DeltaTime) override;`
- L230 _private prototype_ `TSharedRef<SHeaderRow> MakeHeaderRowWidget();`
- L231 _private prototype_ `void SetSearchBoxFilterText(const FText& NewText);`
- L233 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName InColumnId) const;`
- L234 _private prototype_ `void RequestSort();`
- L235 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId, const EColumnSortMode::Type InSortMode);`
- L237 _private prototype_ `TSharedRef<SWidget> CreateHorizontalScrollBox();`
- L239 _private member_ `FText SearchBoxFilterText;`

#### struct `UE::Audio::Insights::FTraceTableDashboardViewFactory::SRowWidget`  
`struct SRowWidget : public SMultiColumnTableRow<TSharedPtr<IDashboardDataViewEntry>>`  
_L73-86_
- inherits: `SMultiColumnTableRow<TSharedPtr<IDashboardDataViewEntry>>`
- L75 _public function_ `SLATE_BEGIN_ARGS(SRowWidget) : _Style(nullptr)`
- L78 _public prototype_ `SLATE_STYLE_ARGUMENT(FTableRowStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<IDashboardDataViewEntry> InData, TSharedRef<FTraceTableDashboardViewFactory> InFactory);`
- L82 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& Column) override;`
- L84 _public member_ `TSharedPtr<IDashboardDataViewEntry> Data;`
- L85 _public member_ `TSharedPtr<FTraceTableDashboardViewFactory> Factory;`

#### struct `UE::Audio::Insights::FTraceTableDashboardViewFactory::FColumnData`  
`struct FColumnData`  
_L170-183_
- L172 _public member_ `const FText DisplayName;`
- L173 _public member_ `const TFunction<FText(const IDashboardDataViewEntry&)> GetDisplayValue;`
- L174 _public member_ `const TFunction<FName(const IDashboardDataViewEntry&)> GetIconName;`
- L175 _public member_ `bool bDefaultHidden = false;`
- L176 _public member_ `const float FillWidth = 1.0f;`
- L177 _public member_ `const EHorizontalAlignment Alignment = HAlign_Left;`
- L178 _public member_ `const TFunction<FLinearColor(const IDashboardDataViewEntry&)> GetIconColor = nullptr;`
- L179 _public member_ `const TFunction<FText(const IDashboardDataViewEntry&)> GetIconTooltip = nullptr;`
- L180 _public member_ `const FName HeaderRowIconName = NAME_None;`
- L181 _public member_ `const FText HeaderRowTooltip = FText::GetEmpty();`
- L182 _public member_ `const bool bShowDisplayName = true;`

#### class `UE::Audio::Insights::FTraceObjectTableDashboardViewFactory`  
`class FTraceObjectTableDashboardViewFactory : public FTraceTableDashboardViewFactory`  
_L242-261_
- inherits: `FTraceTableDashboardViewFactory`
- L245 _public prototype_ `virtual ~FTraceObjectTableDashboardViewFactory() = default;`
- L247 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(TSharedRef<IDashboardDataViewEntry> InRowData, const FName& Column) override;`
- L248 _public prototype_ `virtual FReply OnDataRowKeyInput(const FGeometry& Geometry, const FKeyEvent& KeyEvent) const override;`
- L249 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L250 _public prototype_ `virtual void OnSelectionChanged(TSharedPtr<IDashboardDataViewEntry> SelectedItem, ESelectInfo::Type SelectInfo) override;`
- L254 _protected prototype_ `virtual TSharedRef<SWidget> MakeAssetMenuBar() const;`
- L256 _protected prototype_ `TArray<UObject*> GetSelectedEditableAssets() const;`
- L258 _protected prototype_ `bool OpenAsset() const;`
- L259 _protected prototype_ `bool BrowseToAsset() const;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Audio` (scope `UE`)
- L15 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMouseWheel);`
- L106 _function_ `` (scope `UE::Audio::Insights::FTraceTableDashboardViewFactory::FilterEntries`)
- L145 _function_ `` (scope `UE::Audio::Insights::FTraceTableDashboardViewFactory::SortByPredicate`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/TreeDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::IObjectTreeDashboardEntry`  
`class IObjectTreeDashboardEntry : public IDashboardDataTreeViewEntry`  
_L22-29_
- inherits: `IDashboardDataTreeViewEntry`
- desc: Tree view entries can inherit from this class to implement extra UObject functionality (ex: open, browse, edit, etc.)
- L25 _public prototype_ `virtual ~IObjectTreeDashboardEntry() = default;`
- L27 _public prototype_ `virtual TObjectPtr<UObject> GetObject() = 0;`
- L28 _public prototype_ `virtual const TObjectPtr<UObject> GetObject() const = 0;`

#### class `UE::Audio::Insights::FTraceTreeDashboardViewFactory`  
`class FTraceTreeDashboardViewFactory : public FTraceDashboardViewFactoryBase, public TSharedFromThis<FTraceTreeDashboardViewFactory>`  
_L36-200_
- inherits: `FTraceDashboardViewFactoryBase,TSharedFromThis<FTraceTreeDashboardViewFactory>`
- desc: Inherit from this class to create a tree view dashboard for Audio Insights. It contains a search textbox, filters can be optionally be implemented via GetFilterBarWidget and GetFilterBarButtonWidget. Item actions can be done via OnSelectionChanged, OnDataRowKeyInput, OnConstructContextMenu (for right click)
- L39 _public prototype_ `FTraceTreeDashboardViewFactory();`
- L40 _public prototype_ `virtual ~FTraceTreeDashboardViewFactory() = default;`
- L79 _protected prototype_ `virtual TSharedPtr<SWidget> GetFilterBarWidget();`
- L80 _protected prototype_ `virtual TSharedPtr<SWidget> GetFilterBarButtonWidget();`
- L82 _protected prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs);`
- L84 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const TSharedRef<FTraceTreeDashboardViewFactory::SRowWidget>& InRowWidget, const TSharedRef<IDashboardDataTreeViewEntry>& InRowData, const FName& Column) = 0;`
- L86 _protected prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<IDashboardDataTreeViewEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L88 _protected prototype_ `virtual TSharedPtr<SWidget> OnConstructContextMenu();`
- L90 _protected prototype_ `virtual void OnSelectionChanged(TSharedPtr<IDashboardDataTreeViewEntry> SelectedItem, ESelectInfo::Type SelectInfo);`
- L91 _protected prototype_ `virtual FReply OnDataRowKeyInput(const FGeometry& Geometry, const FKeyEvent& KeyEvent) const;`
- L93 _protected prototype_ `const FText& GetSearchFilterText() const;`
- L94 _protected prototype_ `virtual void SetSearchBoxFilterText(const FText& NewText);`
- L96 _protected prototype_ `virtual void RefreshFilteredEntriesListView() override;`
- L98 _protected prototype_ `virtual const TMap<FName, FHeaderRowColumnData>& GetHeaderRowColumns() const = 0;`
- L99 _protected function_ `virtual void OnHiddenColumnsListChanged()`
- L100 _protected prototype_ `virtual const TMap<FName, FColumnData>& GetColumns() const = 0;`
- L102 _protected prototype_ `virtual void SortTable() = 0;`
- L103 _protected function_ `virtual bool IsColumnSortable(const FName& ColumnId) const`
- L105 _protected function_ `virtual TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& GetTreeItemsSource()`
- L107 _protected function_ `virtual int32 GetDisplayedTreeDepth() const`
- L109 _protected function_ `virtual bool ShouldAutoExpand(const TSharedPtr<IDashboardDataTreeViewEntry>& Item) const`
- L111 _protected function_ `virtual bool ResetTreeData()`
- L123 _protected function_ `virtual bool IsDebugDrawEnabled() const`
- L124 _protected function_ `virtual void DebugDraw(float InElapsed, const TArray<TSharedPtr<IDashboardDataTreeViewEntry>>& InSelectedItems, ::Audio::FDeviceId InAudioDeviceId) const`
- L128 _protected function_ `template<typename TableProviderType> bool FilterEntries(TFunctionRef<bool(IDashboardDataTreeViewEntry&)> InPredicate)`
- L175 _protected member_ `TArray<TSharedPtr<IDashboardDataTreeViewEntry>> DataViewEntries;`
- L177 _protected member_ `TSharedPtr<SWidget> DashboardWidget;`
- L178 _protected member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L179 _protected member_ `TSharedPtr<STreeView<TSharedPtr<IDashboardDataTreeViewEntry>>> FilteredEntriesListView;`
- L181 _protected member_ `FName SortByColumn;`
- L182 _protected member_ `EColumnSortMode::Type SortMode = EColumnSortMode::None;`
- L186 _private prototype_ `virtual void UpdateDebugDraw(const float DeltaTime) override;`
- L189 _private prototype_ `TSharedRef<SHeaderRow> MakeHeaderRowWidget();`
- L191 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName InColumnId) const;`
- L192 _private prototype_ `void RequestSort();`
- L193 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type InSortPriority, const FName& InColumnId, const EColumnSortMode::Type InSortMode);`
- L194 _private prototype_ `void HandleRecursiveExpansion(TSharedPtr<IDashboardDataTreeViewEntry> Item, bool bIsItemExpanded);`
- L196 _private prototype_ `void TransformDataRecursive(const TSharedPtr<IDashboardDataTreeViewEntry>& OriginalEntry, TFunctionRef<bool(IDashboardDataTreeViewEntry&)> FilterPredicate, const int32 DepthToDisplayFrom, const bool bParentPassedFilter = true);`
- L198 _private member_ `TSharedPtr<SSearchBox> SearchBoxWidget;`
- L199 _private member_ `FText SearchBoxFilterText;`

#### struct `UE::Audio::Insights::FTraceTreeDashboardViewFactory::SRowWidget`  
`struct SRowWidget : public SMultiColumnTableRow<TSharedPtr<IDashboardDataTreeViewEntry>>`  
_L43-58_
- inherits: `SMultiColumnTableRow<TSharedPtr<IDashboardDataTreeViewEntry>>`
- L45 _public function_ `SLATE_BEGIN_ARGS(SRowWidget) : _RenderOpacity(1.0f)`
- L48 _public prototype_ `SLATE_ATTRIBUTE(float, RenderOpacity) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<IDashboardDataTreeViewEntry> InData, TSharedRef<FTraceTreeDashboardViewFactory> InFactory);`
- L52 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& Column) override;`
- L53 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L55 _public member_ `TSharedPtr<IDashboardDataTreeViewEntry> Data;`
- L56 _public member_ `TSharedPtr<FTraceTreeDashboardViewFactory> Factory;`
- L57 _public member_ `TAttribute<float> RenderOpacity;`

#### struct `UE::Audio::Insights::FTraceTreeDashboardViewFactory::FHeaderRowColumnData`  
`struct FHeaderRowColumnData`  
_L60-70_
- L62 _public member_ `const FText DisplayName;`
- L63 _public member_ `const FName IconName;`
- L64 _public member_ `const FText TooltipText = FText::GetEmpty();`
- L65 _public member_ `const bool bShowDisplayName = true;`
- L66 _public member_ `const bool bDefaultHidden = false;`
- L67 _public member_ `const float FillWidth = 1.0f;`
- L68 _public member_ `const TOptional<float> FixedWidth;`
- L69 _public member_ `const EHorizontalAlignment Alignment = HAlign_Left;`

#### struct `UE::Audio::Insights::FTraceTreeDashboardViewFactory::FColumnData`  
`struct FColumnData`  
_L72-77_
- L74 _public member_ `const TFunction<FText(const IDashboardDataTreeViewEntry&)> GetDisplayValue;`
- L75 _public member_ `const TFunction<FName(const IDashboardDataTreeViewEntry&)> GetIconName;`
- L76 _public member_ `const TFunction<FSlateColor(const IDashboardDataTreeViewEntry&)> GetTextColorValue;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L139 _function_ `` (scope `UE::Audio::Insights::FTraceTreeDashboardViewFactory::FilterEntries`)

### `Plugins/AudioInsights/Source/AudioInsights/Public/Views/VirtualLoopDashboardViewFactory.h` (Public)


#### class `UE::Audio::Insights::FVirtualLoopDashboardViewFactory`  
`class FVirtualLoopDashboardViewFactory : public FTraceObjectTableDashboardViewFactory`  
_L15-52_
- inherits: `FTraceObjectTableDashboardViewFactory`
- L18 _public prototype_ `FVirtualLoopDashboardViewFactory();`
- L19 _public prototype_ `virtual ~FVirtualLoopDashboardViewFactory() = default;`
- L21 _public prototype_ `virtual FName GetName() const override;`
- L22 _public prototype_ `virtual FText GetDisplayName() const override;`
- L23 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L24 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L26 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> InOwnerTab, const FSpawnTabArgs& InSpawnTabArgs) override;`
- L29 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDebugDrawEntries, float , const TArray<TSharedPtr<IDashboardDataViewEntry>>& , ::Audio::FDeviceId );`
- L30 _public member_ `inline static FOnDebugDrawEntries OnDebugDrawEntries;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> OnConstructContextMenu() override;`
- L33 _public prototype_ `virtual void OnSelectionChanged(TSharedPtr<IDashboardDataViewEntry> SelectedItem, ESelectInfo::Type SelectInfo) override;`
- L34 _public prototype_ `virtual FReply OnDataRowKeyInput(const FGeometry& Geometry, const FKeyEvent& KeyEvent) const override;`
- L38 _protected prototype_ `virtual void ProcessEntries(FTraceTableDashboardViewFactory::EProcessReason Reason) override;`
- L39 _protected prototype_ `virtual const TMap<FName, FTraceTableDashboardViewFactory::FColumnData>& GetColumns() const override;`
- L41 _protected prototype_ `virtual void SortTable() override;`
- L44 _protected prototype_ `virtual bool IsDebugDrawEnabled() const override;`
- L45 _protected prototype_ `virtual void DebugDraw(float InElapsed, const TArray<TSharedPtr<IDashboardDataViewEntry>>& InSelectedItems, ::Audio::FDeviceId InAudioDeviceId) const;`
- L50 _private member_ `FAssetEditorContextMenuHelper AssetContextMenuHelper;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOINSIGHTS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Audio` (scope `UE`)
- L13 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDebugDrawEntries, float , const TArray<TSharedPtr<IDashboardDataViewEntry>>& , ::Audio::FDeviceId );`
