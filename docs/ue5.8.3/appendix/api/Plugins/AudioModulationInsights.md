# Plugins / AudioModulationInsights

- module root: `Plugins/AudioModulationInsights/Source/AudioModulationInsights`
- headers: 8; symbols: 163
- symbol kinds: class=7, enum=1, enumerator=5, function=19, macro=2, member=33, namespace=9, prototype=67, struct=4, typedef=4, variable=12
- PrivateDependencyModuleNames: AudioInsights, AudioInsightsEditor, AudioMixerCore, CoreUObject, Engine, InputCore, Projects, Slate, SlateCore, TraceAnalysis
- PublicDependencyModuleNames: Core

### `Plugins/AudioModulationInsights/Source/AudioModulationInsights/Private/AudioModulationDataTypes.h` (Private)


#### enum `AudioModulationInsights::EModulatorTraceType`  
`enum class EModulatorTraceType : FModulatorTypeId`  
_L25-33_
- desc: mirrors EModulatorTraceType: Engine/Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationSystem.h
- L27 _public enumerator_ `ControlBus`
- L28 _public enumerator_ `ControlBusMix`
- L29 _public enumerator_ `Generator`
- L30 _public enumerator_ `ParameterPatch`
- L32 _public enumerator_ `COUNT`

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "AudioModulationInsights"`
- L10 _namespace_ `namespace AudioModulationInsights`
- L22 _typedef_ `using FBusId = uint32;` (scope `AudioModulationInsights`) — mirrors FBusId: Engine/Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/SoundControlBusProxy.h
- L23 _typedef_ `using FModulatorId = uint32;` (scope `AudioModulationInsights`) — mirrors FModulatorId: Engine/Source/Runtime/AudioExtensions/Public/IAudioModulation.h
- L24 _typedef_ `using FModulatorTypeId = uint32;` (scope `AudioModulationInsights`) — mirrors FModulatorTypeId: Engine/Source/Runtime/AudioExtensions/Public/IAudioModulation.h
- L35 _function_ `static inline FText GetModulatorTraceTypeName(const EModulatorTraceType InModulatorTraceType)` (scope `AudioModulationInsights`)
- L50 _namespace_ `namespace ModulatorColumnNames` (scope `AudioModulationInsights`)
- L52 _variable_ `const FName ModulatorIDColumnName{"Mod` (scope `AudioModulationInsights::ModulatorColumnNames`)
- L53 _variable_ `const FName ModulatorNameColumnName{"Mod` (scope `AudioModulationInsights::ModulatorColumnNames`)
- L54 _variable_ `const FName ModulatorTypeColumnName{"Mod` (scope `AudioModulationInsights::ModulatorColumnNames`)
- L55 _variable_ `const FName ModulatorValueColumnName{"Mod` (scope `AudioModulationInsights::ModulatorColumnNames`)
- L56 _variable_ `const FName ModulatorBypassedColumnName{"Byp` (scope `AudioModulationInsights::ModulatorColumnNames`)
- L59 _namespace_ `namespace ModulatorColors` (scope `AudioModulationInsights`)
- L61 _variable_ `const FSlateColor Default = FSlateColor(FColor::White);` (scope `AudioModulationInsights::ModulatorColors`)
- L62 _variable_ `const FSlateColor SelectedModulator = FSlateColor(FColor::Green);` (scope `AudioModulationInsights::ModulatorColors`)
- L63 _variable_ `const FSlateColor SelectedContributor = FSlateColor(FColor::Yellow);` (scope `AudioModulationInsights::ModulatorColors`)
- L66 _variable_ `static const FModulatorId InvalidModulatorId = -1;` (scope `AudioModulationInsights`)

### `Plugins/AudioModulationInsights/Source/AudioModulationInsights/Private/AudioModulationInsightsStyle.h` (Private)


#### class `FAudioModulationInsightsStyle`  
`class FAudioModulationInsightsStyle final : public FSlateStyleSet`  
_L9-19_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `FAudioModulationInsightsStyle();`
- L13 _public prototype_ `~FAudioModulationInsightsStyle();`
- L15 _public prototype_ `static const FAudioModulationInsightsStyle& Get();`
- L16 _public prototype_ `static const FName& GetStyleName();`
- L18 _public prototype_ `FSlateIcon CreateIcon(const FName& InName) const;`

### `Plugins/AudioModulationInsights/Source/AudioModulationInsights/Private/Messages/AudioModulationTraceMessages.h` (Private)


#### struct `AudioModulationInsights::FModulatorTraceMessageBase`  
`struct FModulatorTraceMessageBase : public UE::Audio::Insights::IAudioCachedMessage`  
_L19-36_
- inherits: `UE::Audio::Insights::IAudioCachedMessage`
- desc: Mirrors MODULATOR_TRACE_MESSAGE_BASE: Engine/Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationSystem.cpp
- L21 _public prototype_ `FModulatorTraceMessageBase() = default;`
- L22 _public function_ `FModulatorTraceMessageBase(const UE::Trace::IAnalyzer::FOnEventContext& InContext)`
- L31 _public function_ `virtual uint64 GetID() const override` — from UE::Audio::Insights::IAudioCachedMessage
- L32 _public function_ `virtual uint32 GetSizeOf() const override`
- L34 _public member_ `Audio::FDeviceId DeviceId = INDEX_NONE;`
- L35 _public member_ `FModulatorId ModulatorId = INDEX_NONE;`

#### struct `AudioModulationInsights::FActivateModulatorTraceMessage`  
`struct FActivateModulatorTraceMessage final : public FModulatorTraceMessageBase`  
_L39-56_
- inherits: `FModulatorTraceMessageBase`
- desc: Mirrors ActivateModulatorTraceMessage: Engine/Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationSystem.cpp
- L41 _public prototype_ `FActivateModulatorTraceMessage() = default;`
- L42 _public function_ `FActivateModulatorTraceMessage(const UE::Trace::IAnalyzer::FOnEventContext& InContext) : FModulatorTraceMessageBase(InContext)`
- L50 _public function_ `virtual uint32 GetSizeOf() const override` — from UE::Audio::Insights::IAudioCachedMessage
- L51 _public function_ `virtual const FName GetMessageName() const override`
- L52 _public prototype_ `virtual UE::Audio::Insights::FCacheWriteHandler GetCacheWriteHandler() const override;`
- L54 _public member_ `EModulatorTraceType ModulatorType { EModulatorTraceType::COUNT };`
- L55 _public member_ `FString ModulatorName;`

#### struct `AudioModulationInsights::FUpdateModulatorTraceMessage`  
`struct FUpdateModulatorTraceMessage final : public FModulatorTraceMessageBase`  
_L59-91_
- inherits: `FModulatorTraceMessageBase`
- desc: Mirrors UpdateModulatorTraceMessage: Engine/Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationSystem.cpp
- L61 _public prototype_ `FUpdateModulatorTraceMessage() = default;`
- L62 _public function_ `FUpdateModulatorTraceMessage(const UE::Trace::IAnalyzer::FOnEventContext& InContext) : FModulatorTraceMessageBase(InContext)`
- L83 _public function_ `virtual uint32 GetSizeOf() const override` — from UE::Audio::Insights::IAudioCachedMessage
- L84 _public function_ `virtual const FName GetMessageName() const override`
- L85 _public prototype_ `virtual UE::Audio::Insights::FCacheWriteHandler GetCacheWriteHandler() const override;`
- L87 _public member_ `float ModulatorValue { 1.0f };`
- L88 _public member_ `bool bIsBypassed { false };`
- L89 _public member_ `TArray<FModulatorId> ContributingModulatorIds;`
- L90 _public member_ `TArray<float> ContributingModulatorValues;`

#### struct `AudioModulationInsights::FDeactivateModulatorTraceMessage`  
`struct FDeactivateModulatorTraceMessage final : public FModulatorTraceMessageBase`  
_L94-102_
- inherits: `FModulatorTraceMessageBase`
- desc: Mirrors DeactivateModulatorTraceMessage: Engine/Plugins/Runtime/AudioModulation/Source/AudioModulation/Private/AudioModulationSystem.cpp
- L96 _public prototype_ `FDeactivateModulatorTraceMessage() = default;`
- L97 _public function_ `FDeactivateModulatorTraceMessage(const UE::Trace::IAnalyzer::FOnEventContext& InContext) : FModulatorTraceMessageBase(InContext)`
- L100 _public function_ `virtual const FName GetMessageName() const override` — from UE::Audio::Insights::IAudioCachedMessage
- L101 _public prototype_ `virtual UE::Audio::Insights::FCacheWriteHandler GetCacheWriteHandler() const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AudioModulationInsights`
- L11 _namespace_ `namespace ModulatorTraceMessageNames` (scope `AudioModulationInsights`)
- L13 _variable_ `inline const FName ActivateModulatorTraceMessage(TEXT("Acti` (scope `AudioModulationInsights::ModulatorTraceMessageNames`)
- L14 _variable_ `inline const FName UpdateModulatorTraceMessage(TEXT("Upda` (scope `AudioModulationInsights::ModulatorTraceMessageNames`)
- L15 _variable_ `inline const FName DeactivateModulatorTraceMessage(TEXT("Deac` (scope `AudioModulationInsights::ModulatorTraceMessageNames`)

### `Plugins/AudioModulationInsights/Source/AudioModulationInsights/Private/Providers/AudioModulationTraceProvider.h` (Private)


#### class `AudioModulationInsights::FAudioModulationDashboardEntry`  
`class FAudioModulationDashboardEntry final : public UE::Audio::Insights::FSoundAssetDashboardEntry`  
_L12-35_
- inherits: `UE::Audio::Insights::FSoundAssetDashboardEntry`
- L15 _public prototype_ `FAudioModulationDashboardEntry() = default;`
- L16 _public prototype_ `~FAudioModulationDashboardEntry() = default;`
- L18 _public prototype_ `static const FAudioModulationDashboardEntry& CastEntry(const UE::Audio::Insights::IDashboardDataViewEntry& InDataViewEntry);`
- L19 _public prototype_ `static FAudioModulationDashboardEntry& CastEntryMutable(UE::Audio::Insights::IDashboardDataViewEntry& InDataViewEntry);`
- L21 _public function_ `FText GetDisplayNameAsFText() const`
- L23 _public member_ `bool bIsBypassed { false };`
- L25 _public member_ `FModulatorId ModulatorId = INDEX_NONE;`
- L26 _public member_ `EModulatorTraceType ModulatorType { EModulatorTraceType::COUNT };`
- L28 _public member_ `float Value { 1.0f };`
- L29 _public member_ `float ContributingValue { 1.0f };`
- L31 _public member_ `TArray<FModulatorId> ContributingModulatorIds;`
- L32 _public member_ `TArray<float> ContributingModulatorValues;`
- L34 _public member_ `FString DisplayName;`

#### class `AudioModulationInsights::FAudioModulationTraceProvider`  
`class FAudioModulationTraceProvider final : public UE::Audio::Insights::TDeviceDataMapTraceProvider<uint32, TSharedPtr<FAudioModulationDashboardEntry>> , public TSharedFromThis<FAudioModulationTraceProvider>`  
_L37-66_
- inherits: `UE::Audio::Insights::TDeviceDataMapTraceProvider<uint32,TSharedPtr<FAudioModulationDashboardEntry>>,TSharedFromThis<FAudioModulationTraceProvider>`
- L42 _public function_ `FAudioModulationTraceProvider() : UE::Audio::Insights::TDeviceDataMapTraceProvider<uint32, TSharedPtr<FAudioModulationDashboardEntry>>(GetName_Static())`
- L46 _public function_ `static FName GetName_Static()`
- L47 _public prototype_ `TSharedPtr<FAudioModulationDashboardEntry> FindEntry(const FModulatorId InModulatorId) const;`
- L51 _private prototype_ `virtual UE::Trace::IAnalyzer* ConstructAnalyzer(TraceServices::IAnalysisSession& InSession) override;` — from UE::Audio::Insights::FTraceProviderBase via UE::Audio::Insights::TDeviceDataMapTraceProvider
- L52 _private prototype_ `virtual bool ProcessMessages() override;`
- L53 _private prototype_ `virtual void OnTimingViewTimeMarkerChanged(const double InTimeMarker) override;`
- L54 _private prototype_ `virtual void OnTimeControlMethodReset() override;`
- L56 _private prototype_ `TSharedPtr<FAudioModulationDashboardEntry>* FindOrAddEntry(const FActivateModulatorTraceMessage& InActivateModulatorTraceMessage);`
- L58 _private prototype_ `void ProcessActivateEntry(const FActivateModulatorTraceMessage& InActivateModulatorTraceMessage, const TSharedPtr<FAudioModulationDashboardEntry>* const OutAudioModulationDashboardEntry);`
- L59 _private prototype_ `void ProcessUpdateEntry(const FUpdateModulatorTraceMessage& InUpdateModulatorTraceMessage, const TSharedPtr<FAudioModulationDashboardEntry>* const OutAudioModulationDashboardEntry);`
- L60 _private prototype_ `void ProcessDeactivateEntry(const FDeactivateModulatorTraceMessage& InDeactivateModulatorTraceMessage, const TSharedPtr<FAudioModulationDashboardEntry>* const OutAudioModulationDashboardEntry);`
- L62 _private member_ `static constexpr double CacheHistoryLimitSec { 0.1 };`
- L63 _private member_ `UE::Audio::Insights::TAnalyzerMessageQueue<FActivateModulatorTraceMessage> ActivateModulatorTraceMessages { CacheHistoryLimitSec };`
- L64 _private member_ `UE::Audio::Insights::TAnalyzerMessageQueue<FUpdateModulatorTraceMessage> UpdateModulatorTraceMessages { CacheHistoryLimitSec };`
- L65 _private member_ `UE::Audio::Insights::TAnalyzerMessageQueue<FDeactivateModulatorTraceMessage> DeactivateModulatorTraceMessages { CacheHistoryLimitSec };`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AudioModulationInsights`

### `Plugins/AudioModulationInsights/Source/AudioModulationInsights/Private/Views/AudioModulationContributorsDashboardViewFactory.h` (Private)


#### class `AudioModulationInsights::FAudioModulationContributorsDashboardViewFactory`  
`class FAudioModulationContributorsDashboardViewFactory final : public UE::Audio::Insights::FTraceObjectTableDashboardViewFactory`  
_L10-43_
- inherits: `UE::Audio::Insights::FTraceObjectTableDashboardViewFactory`
- L14 _public prototype_ `FAudioModulationContributorsDashboardViewFactory();`
- L15 _public prototype_ `~FAudioModulationContributorsDashboardViewFactory();`
- L17 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L19 _public prototype_ `void ResetEntries();`
- L20 _public prototype_ `void UpdateEntries(TArray<TSharedPtr<UE::Audio::Insights::IDashboardDataViewEntry>> InEntries);`
- L21 _public function_ `FModulatorId GetSelectedModulatorId() const`
- L22 _public prototype_ `void OnMainWindowModulatorSelectionChanged(const FModulatorId InSelectedModulatorId);`
- L23 _public prototype_ `void ResetSelectedModulatorId();`
- L26 _private prototype_ `virtual FName GetName() const override;`
- L27 _private prototype_ `virtual FText GetDisplayName() const override;`
- L28 _private prototype_ `virtual FSlateIcon GetIcon() const override;`
- L29 _private prototype_ `virtual UE::Audio::Insights::EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L30 _private prototype_ `virtual TSharedPtr<SWidget> OnConstructContextMenu() override;`
- L31 _private prototype_ `virtual const TMap<FName, FColumnData>& GetColumns() const override;`
- L32 _private prototype_ `virtual void OnSelectionChanged(TSharedPtr<UE::Audio::Insights::IDashboardDataViewEntry> SelectedItem, ESelectInfo::Type SelectInfo) override;`
- L33 _private prototype_ `virtual FSlateColor GetRowColor(const TSharedPtr<UE::Audio::Insights::IDashboardDataViewEntry>& InRowDataPtr) override;`
- L36 _private function_ `virtual void SortTable() override` — Note: Intentionally not supporting sorting of the contributors. This ensures our selected modulator and final value to always be displayed at the top.
- L38 _private prototype_ `void BindCommands();`
- L39 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L41 _private member_ `FModulatorId SelectedModulatorId = InvalidModulatorId;`
- L42 _private member_ `FModulatorId MainWindowSelectedModulatorId = InvalidModulatorId;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AudioModulationInsights`

### `Plugins/AudioModulationInsights/Source/AudioModulationInsights/Private/Views/AudioModulationDashboardViewFactory.h` (Private)


#### class `AudioModulationInsights::FAudioModulationDashboardViewFactory`  
`class FAudioModulationDashboardViewFactory final : public UE::Audio::Insights::FTraceObjectTableDashboardViewFactory`  
_L13-53_
- inherits: `UE::Audio::Insights::FTraceObjectTableDashboardViewFactory`
- L16 _public prototype_ `FAudioModulationDashboardViewFactory();`
- L17 _public prototype_ `~FAudioModulationDashboardViewFactory();`
- L19 _public prototype_ `virtual FName GetName() const override;`
- L22 _private prototype_ `virtual FText GetDisplayName() const override;`
- L23 _private prototype_ `virtual FSlateIcon GetIcon() const override;`
- L24 _private prototype_ `virtual UE::Audio::Insights::EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L25 _private prototype_ `virtual void ProcessEntries(UE::Audio::Insights::FTraceTableDashboardViewFactory::EProcessReason Reason) override;`
- L26 _private prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L27 _private prototype_ `virtual const TMap<FName, UE::Audio::Insights::FTraceTableDashboardViewFactory::FColumnData>& GetColumns() const override;`
- L28 _private prototype_ `virtual void SortTable() override;`
- L29 _private prototype_ `virtual FSlateColor GetRowColor(const TSharedPtr<UE::Audio::Insights::IDashboardDataViewEntry>& InRowDataPtr) override;`
- L30 _private prototype_ `virtual TSharedPtr<SWidget> OnConstructContextMenu() override;`
- L31 _private prototype_ `virtual FReply OnDataRowKeyInput(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) const override;`
- L32 _private prototype_ `virtual void OnSelectionChanged(TSharedPtr<UE::Audio::Insights::IDashboardDataViewEntry> SelectedItem, ESelectInfo::Type SelectInfo) override;`
- L34 _private prototype_ `bool IsModulatorSelected() const;`
- L35 _private prototype_ `bool IsContributorWindowVisible() const;`
- L36 _private prototype_ `void ResetSelectedModulatorId();`
- L37 _private prototype_ `void UpdateContributorWatchWindow();`
- L38 _private prototype_ `void BindCommands();`
- L39 _private prototype_ `void FilterByModulatorName();`
- L40 _private prototype_ `void FilterByModulatorType();`
- L41 _private prototype_ `TSharedRef<SWidget> MakeModulatorTypeFilterWidget();`
- L43 _private typedef_ `using FComboBoxSelectionItem = TPair<EModulatorTraceType, FText>;`
- L44 _private member_ `TArray<TSharedPtr<FComboBoxSelectionItem>> ComboBoxModulatorTypes;`
- L45 _private member_ `TArray<TSharedPtr<UE::Audio::Insights::IDashboardDataViewEntry>> ContributingEntries;`
- L47 _private member_ `TSharedPtr<FAudioModulationContributorsDashboardViewFactory> ContributorsDashboard;`
- L48 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L49 _private member_ `TSharedPtr<FComboBoxSelectionItem> ComboBoxSelectedModulatorTypes;`
- L50 _private member_ `TSharedPtr<FAudioModulationTraceProvider> AudioModulationProvider;`
- L52 _private member_ `FModulatorId SelectedModulatorId = InvalidModulatorId;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AudioModulationInsights`

### `Plugins/AudioModulationInsights/Source/AudioModulationInsights/Private/Views/AudioModulationInsightsCommands.h` (Private)


#### class `AudioModulationInsights::FAudioModulationInsightsCommands`  
`class FAudioModulationInsightsCommands : public TCommands<FAudioModulationInsightsCommands>`  
_L11-24_
- inherits: `TCommands<FAudioModulationInsightsCommands>`
- L14 _public prototype_ `FAudioModulationInsightsCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public function_ `TSharedPtr<const FUICommandInfo> GetBrowseCommand() const`
- L19 _public function_ `TSharedPtr<const FUICommandInfo> GetEditCommand() const`
- L22 _private member_ `TSharedPtr<FUICommandInfo> Browse;`
- L23 _private member_ `TSharedPtr<FUICommandInfo> Edit;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AudioModulationInsights`

### `Plugins/AudioModulationInsights/Source/AudioModulationInsights/Public/AudioModulationInsightsModule.h` (Public)


#### class `FAudioModulationInsightsModule`  
`class FAudioModulationInsightsModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `TSharedPtr<AudioModulationInsights::FAudioModulationDashboardViewFactory> AudioModulationDashboardViewFactory;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOMODULATIONINSIGHTS_API`
