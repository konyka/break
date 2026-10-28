# Plugins / AudioInsightsEditor

- module root: `Plugins/AudioInsights/Source/AudioInsightsEditor`
- headers: 12; symbols: 238
- symbol kinds: class=11, delegate=2, function=8, macro=3, member=57, namespace=28, prototype=127, struct=2
- PrivateDependencyModuleNames: AudioInsights, AudioMixer, AudioWidgets, AudioWidgetsCore, CoreUObject, DeveloperSettings, Engine, InputCore, OutputLog, Projects, SignalProcessing, Slate, SlateCore, TraceAnalysis, TraceLog, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: AudioMixerCore, Core

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/Analyzers/SubmixAudioAnalyzerRack.h` (Private)


#### class `UE::Audio::Insights::FSubmixAudioAnalyzerRack`  
`class FSubmixAudioAnalyzerRack : public TSharedFromThis<FSubmixAudioAnalyzerRack>`  
_L16-31_
- inherits: `TSharedFromThis<FSubmixAudioAnalyzerRack>`
- L19 _public prototype_ `FSubmixAudioAnalyzerRack(TWeakObjectPtr<USoundSubmix> InSoundSubmix);`
- L20 _public prototype_ `virtual ~FSubmixAudioAnalyzerRack();`
- L22 _public prototype_ `TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> InOwnerTab, const FSpawnTabArgs& InSpawnTabArgs);`
- L24 _public prototype_ `void RebuildAudioAnalyzerRack(TWeakObjectPtr<USoundSubmix> InSoundSubmix);`
- L27 _private prototype_ `void CleanupAudioAnalyzerRack();`
- L29 _private member_ `TSharedRef<AudioWidgets::FAudioAnalyzerRack> AudioAnalyzerRack;`
- L30 _private member_ `TWeakObjectPtr<USoundSubmix> SoundSubmix;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AudioWidgets`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Audio` (scope `UE`)
- L14 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/AudioInsightsEditorDashboardFactory.h` (Private)


#### class `UE::Audio::Insights::FEditorDashboardFactory`  
`class FEditorDashboardFactory : public IDashboardFactory, public TSharedFromThis<FEditorDashboardFactory>`  
_L20-108_
- inherits: `IDashboardFactory,TSharedFromThis<FEditorDashboardFactory>`
- L23 _public prototype_ `FEditorDashboardFactory();`
- L24 _public prototype_ `virtual ~FEditorDashboardFactory();`
- L26 _public prototype_ `TSharedRef<SDockTab> MakeDockTabWidget(const FSpawnTabArgs& Args);`
- L28 _public prototype_ `virtual void RegisterViewFactory(TSharedRef<IDashboardViewFactory> InFactory) override;`
- L29 _public prototype_ `virtual void UnregisterViewFactory(FName InDashboardName) override;`
- L30 _public prototype_ `virtual ::Audio::FDeviceId GetDeviceId() const override;`
- L32 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnActiveAudioDeviceChanged);`
- L33 _public member_ `FOnActiveAudioDeviceChanged OnActiveAudioDeviceChanged;`
- L36 _private prototype_ `void OnWorldRegisteredToAudioDevice(const UWorld* InWorld, ::Audio::FDeviceId InDeviceId);`
- L37 _private prototype_ `void OnWorldUnregisteredFromAudioDevice(const UWorld* InWorld, ::Audio::FDeviceId InDeviceId);`
- L39 _private prototype_ `void OnDeviceCreated(::Audio::FDeviceId InDeviceId);`
- L40 _private prototype_ `void OnDeviceDestroyed(::Audio::FDeviceId InDeviceId);`
- L42 _private prototype_ `void OnTraceStarted(FTraceAuxiliary::EConnectionType InTraceType, const FString& InTraceDestination);`
- L44 _private prototype_ `void OnOnlyTraceAudioChannelsPropertyChanged(const bool bInOnlyTraceAudioChannels);`
- L46 _private prototype_ `void OnPIEStarted(bool bSimulating);`
- L47 _private prototype_ `void OnPIEStopped(bool bSimulating);`
- L49 _private prototype_ `void CreateTraceBookmark();`
- L51 _private prototype_ `void RefreshDeviceSelector();`
- L52 _private prototype_ `void ResetDelegates();`
- L54 _private prototype_ `void BindCommands();`
- L56 _private prototype_ `TSharedRef<SWidget> MakeMenuBarWidget();`
- L57 _private prototype_ `TSharedRef<SWidget> MakeMainToolbarWidget();`
- L59 _private prototype_ `TSharedRef<SWidget> MakeTraceModeButton(const ETraceMode InTraceButtonMode);`
- L61 _private prototype_ `TSharedRef<SWidget> MakeEnableTracesOverlay();`
- L62 _private prototype_ `TSharedRef<SWidget> MakeEnableTracesButton();`
- L63 _private prototype_ `FReply OnEnableTracesClicked();`
- L65 _private prototype_ `TSharedRef<SWidget> CreateEditorPreferencesButtonWidget();`
- L67 _private prototype_ `void SetActiveDeviceId(const ::Audio::FDeviceId InDeviceId);`
- L68 _private prototype_ `void InitDelegates();`
- L69 _private prototype_ `TSharedRef<FTabManager::FLayout> GetDefaultTabLayout();`
- L71 _private prototype_ `void RegisterTabSpawners();`
- L72 _private prototype_ `void UnregisterTabSpawners();`
- L74 _private prototype_ `TSharedRef<FTabManager::FLayout> LoadLayoutFromConfig();`
- L75 _private prototype_ `void SaveLayoutToConfig();`
- L77 _private prototype_ `bool ShouldOnlyTraceAudioChannels() const;`
- L79 _private member_ `FDelegateHandle OnWorldRegisteredToAudioDeviceHandle;`
- L80 _private member_ `FDelegateHandle OnWorldUnregisteredFromAudioDeviceHandle;`
- L82 _private member_ `FDelegateHandle OnDeviceCreatedHandle;`
- L83 _private member_ `FDelegateHandle OnDeviceDestroyedHandle;`
- L85 _private member_ `FDelegateHandle OnTraceStartedHandle;`
- L87 _private member_ `FDelegateHandle OnPIEStartedHandle;`
- L88 _private member_ `FDelegateHandle OnPIEStoppedHandle;`
- L90 _private member_ `FDelegateHandle OnOnlyTraceAudioChannelsPropertyChangedHandle;`
- L92 _private member_ `bool bIsLayoutReseting = false;`
- L94 _private member_ `TSharedPtr<FToolbarWidgets> ToolbarWidgets;`
- L96 _private member_ `TSharedPtr<FTabManager> DashboardTabManager;`
- L97 _private member_ `TSharedPtr<FWorkspaceItem> DashboardWorkspace;`
- L99 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L101 _private member_ `TArray<TSharedPtr<::Audio::FDeviceId>> AudioDeviceIds;`
- L102 _private member_ `TSharedPtr<SComboBox<TSharedPtr<::Audio::FDeviceId>>> AudioDeviceComboBox;`
- L105 _private member_ `int32 BookmarkIndex = 0;`
- L107 _private member_ `TMap<FName, TSharedPtr<IDashboardViewFactory>> DashboardViewFactories;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Audio` (scope `UE`)
- L18 _namespace_ `namespace Insights` (scope `UE::Audio`)
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnActiveAudioDeviceChanged);`

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/AudioInsightsEditorModule.h` (Private)


#### class `UE::Audio::Insights::FAudioInsightsEditorModule`  
`class FAudioInsightsEditorModule final : public IAudioInsightsEditorModule`  
_L17-63_
- inherits: `IAudioInsightsEditorModule`
- L20 _public prototype_ `FAudioInsightsEditorModule() = default;`
- L21 _public prototype_ `virtual ~FAudioInsightsEditorModule() = default;`
- L23 _public prototype_ `FAudioInsightsEditorModule(const FAudioInsightsEditorModule&) = delete;`
- L24 _public prototype_ `FAudioInsightsEditorModule& operator=(const FAudioInsightsEditorModule&) = delete;`
- L25 _public prototype_ `FAudioInsightsEditorModule(FAudioInsightsEditorModule&&) = delete;`
- L26 _public prototype_ `FAudioInsightsEditorModule& operator=(FAudioInsightsEditorModule&&) = delete;`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public prototype_ `virtual void RegisterDashboardViewFactory(TSharedRef<IDashboardViewFactory> InDashboardFactory) override;`
- L31 _public prototype_ `virtual void UnregisterDashboardViewFactory(FName InName) override;`
- L32 _public prototype_ `virtual void RegisterEventLogCategories(const TMap<FString, TSet<FString>>& InCategoriesToEvents) override;`
- L33 _public prototype_ `virtual void RegisterEventLogDisplayNames(const TMap<FString, FText>& InDisplayNames) override;`
- L35 _public prototype_ `virtual ::Audio::FDeviceId GetDeviceId() const override;`
- L37 _public prototype_ `TSharedPtr<FEditorDashboardFactory> GetDashboardFactory();`
- L38 _public prototype_ `const TSharedPtr<FEditorDashboardFactory> GetDashboardFactory() const;`
- L40 _public prototype_ `static bool IsModuleLoaded();`
- L41 _public prototype_ `static FAudioInsightsEditorModule& GetChecked();`
- L42 _public prototype_ `virtual IAudioInsightsTraceModule& GetTraceModule() override;`
- L43 _public prototype_ `virtual class FAudioInsightsCacheManager& GetCacheManager() override;`
- L44 _public prototype_ `virtual class FAudioInsightsTimingViewExtender& GetTimingViewExtender() override;`
- L45 _public prototype_ `virtual class FAudioInsightsDetailsSelectionManager& GetDetailsSelectionManager() override;`
- L48 _private prototype_ `void RegisterMenus();`
- L50 _private prototype_ `TSharedRef<SDockTab> CreateDashboardTabWidget(const FSpawnTabArgs& Args);`
- L52 _private prototype_ `void OnModularFeatureRegistered(const FName& Name, IModularFeature* ModularFeature);`
- L53 _private prototype_ `void OnModularFeatureUnregistered(const FName& Name, IModularFeature* ModularFeature);`
- L55 _private member_ `inline static const FName AudioInsightsEditorModuleName = "Au`
- L57 _private member_ `TSharedPtr<FEditorDashboardFactory> DashboardFactory;`
- L58 _private member_ `TSharedPtr<FAudioEventLogDashboardViewFactory> EventLogViewFactory;`
- L60 _private member_ `FVirtualLoopsDebugDraw VirtualLoopsDebugDraw;`
- L62 _private member_ `TSharedPtr<FPluginTemplateDescription> AudioInsightsPluginTemplateDescription;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Audio` (scope `UE`)
- L13 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/AudioInsightsPluginTemplate.h` (Private)


#### struct `FAudioInsightsPluginTemplateDescription`  
`struct FAudioInsightsPluginTemplateDescription : FPluginTemplateDescription`  
_L12-20_
- inherits: `FPluginTemplateDescription`
- desc: Used to create custom templates for Audio Insights.
- L14 _public prototype_ `FAudioInsightsPluginTemplateDescription(FText InName, FText InDescription, FString InOnDiskPath);`
- L17 _public prototype_ `virtual void UpdatePluginNameTextWhenTemplateSelected(FText& OutPluginNameText) override;` — FPluginTemplateDescription overrides
- L18 _public prototype_ `virtual void UpdatePluginNameTextWhenTemplateUnselected(FText& OutPluginNameText) override;`
- L19 _public prototype_ `virtual void CustomizeDescriptorBeforeCreation(FPluginDescriptor& Descriptor) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOINSIGHTSEDITOR_API`

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/Views/AudioAnalyzerRackDashboardViewFactory.h` (Private)


#### class `UE::Audio::Insights::FAudioAnalyzerRackDashboardViewFactory`  
`class FAudioAnalyzerRackDashboardViewFactory : public IDashboardViewFactory, public TSharedFromThis<FAudioAnalyzerRackDashboardViewFactory>`  
_L13-27_
- inherits: `IDashboardViewFactory,TSharedFromThis<FAudioAnalyzerRackDashboardViewFactory>`
- L16 _public prototype_ `virtual FName GetName() const override;`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L19 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L20 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L23 _private prototype_ `void HandleOnActiveAudioDeviceChanged();`
- L25 _private member_ `TSharedPtr<FSubmixAudioAnalyzerRack> SubmixAudioAnalyzerRack;`
- L26 _private member_ `TObjectPtr<USoundSubmix> MainSubmix;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)
- L9 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/Views/DetailsDashboardViewFactory.h` (Private)


#### class `UE::Audio::Insights::SDetailsDashboardWindow`  
`class SDetailsDashboardWindow final : public SOverlay`  
_L19-32_
- inherits: `SOverlay`
- L22 _public function_ `SLATE_BEGIN_ARGS(SDetailsDashboardWindow)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FUICommandList>& InCommandList);`
- L27 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L28 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L31 _private member_ `TSharedPtr<FUICommandList> CommandList;`

#### class `UE::Audio::Insights::FDetailsDashboardViewFactory`  
`class FDetailsDashboardViewFactory final : public IDashboardViewFactory, public TSharedFromThis<FDetailsDashboardViewFactory>`  
_L34-74_
- inherits: `IDashboardViewFactory,TSharedFromThis<FDetailsDashboardViewFactory>`
- L37 _public prototype_ `FDetailsDashboardViewFactory() = default;`
- L38 _public prototype_ `~FDetailsDashboardViewFactory() = default;`
- L40 _public prototype_ `virtual FName GetName() const override;`
- L41 _public prototype_ `virtual FText GetDisplayName() const override;`
- L42 _public prototype_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override;`
- L43 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L44 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override;`
- L47 _private prototype_ `TSharedRef<SWidget> CreateAssetHeaderWidget();`
- L48 _private prototype_ `TSharedRef<SDetailsDashboardWindow> CreateDetailsViewWidget();`
- L49 _private prototype_ `void BindCommands();`
- L50 _private prototype_ `void BindOnAssetChangedDelegate();`
- L52 _private prototype_ `void OnAssetSelectionChanged(const TObjectPtr<UObject> InAsset);`
- L54 _private prototype_ `TSharedRef<SWidget> MakeAssetMenuBar() const;`
- L55 _private prototype_ `TObjectPtr<UObject> GetSelectedEditableAsset() const;`
- L57 _private prototype_ `void OpenAsset() const;`
- L58 _private prototype_ `void BrowseToAsset() const;`
- L59 _private prototype_ `void SaveAsset() const;`
- L60 _private prototype_ `void SaveAllAssets() const;`
- L61 _private prototype_ `bool CanSaveAsset() const;`
- L62 _private prototype_ `UPackage* GetAssetPackage() const;`
- L64 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L65 _private member_ `TSharedPtr<SWidget> DetailsViewWidget;`
- L66 _private member_ `TSharedPtr<SWidget> NoSelectionMessageWidget;`
- L67 _private member_ `TSharedPtr<SDetailsDashboardWindow> DashboardWidget;`
- L69 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L70 _private member_ `TSharedPtr<SImage> AssetIconImage;`
- L71 _private member_ `TSharedPtr<STextBlock> AssetNameText;`
- L73 _private member_ `FDelegateHandle AssetSelectionChangedHandle;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Audio` (scope `UE`)
- L17 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/Views/SoundAttenuationVisualizer.h` (Private)


#### class `UE::Audio::Insights::FSoundAttenuationVisualizer`  
`class FSoundAttenuationVisualizer`  
_L11-24_
- L14 _public prototype_ `explicit FSoundAttenuationVisualizer(const FColor& InColor);`
- L15 _public prototype_ `void Draw(float InDeltaTime, const FTransform& InTransform, const UObject& InObject, const UWorld& InWorld) const;`
- L17 _public function_ `const FColor& GetColor() const`
- L20 _private member_ `const FColor Color { 155, 155, 255 };`
- L22 _private member_ `mutable TMultiMap<EAttenuationShape::Type, FBaseAttenuationSettings::AttenuationShapeDetails> ShapeDetailsMap;`
- L23 _private member_ `mutable uint32 LastObjectId = INDEX_NONE;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Audio` (scope `UE`)
- L7 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/Views/ViewportDashboardViewFactory.h` (Private)


#### class `UE::Audio::Insights::FViewportDashboardViewFactory`  
`class FViewportDashboardViewFactory : public IDashboardViewFactory`  
_L15-48_
- inherits: `IDashboardViewFactory`
- L18 _public function_ `virtual FName GetName() const override`
- L23 _public function_ `virtual FText GetDisplayName() const override`
- L28 _public function_ `virtual EDefaultDashboardTabStack GetDefaultTabStack() const override`
- L33 _public function_ `virtual FSlateIcon GetIcon() const override`
- L38 _public function_ `virtual TSharedRef<SWidget> MakeWidget(TSharedRef<SDockTab> OwnerTab, const FSpawnTabArgs& SpawnTabArgs) override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "AudioInsights"`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Audio` (scope `UE`)
- L13 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Private/Views/VirtualLoopsDebugDraw.h` (Private)


#### class `UE::Audio::Insights::FVirtualLoopsDebugDraw`  
`class FVirtualLoopsDebugDraw`  
_L11-23_
- L14 _public prototype_ `FVirtualLoopsDebugDraw();`
- L15 _public prototype_ `~FVirtualLoopsDebugDraw();`
- L17 _public prototype_ `void DebugDraw(float InElapsed, const TArray<TSharedPtr<IDashboardDataViewEntry>>& InSelectedItems, ::Audio::FDeviceId InAudioDeviceId);`
- L20 _private prototype_ `void DebugDrawEntries(float InElapsed, const TArray<TSharedPtr<IDashboardDataViewEntry>>& InSelectedItems, ::Audio::FDeviceId InAudioDeviceId) const;`
- L22 _private member_ `FSoundAttenuationVisualizer AttenuationVisualizer;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Audio` (scope `UE`)
- L7 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Public/AudioInsightsEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioInsightsEditor, Log, All);`

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Public/AudioInsightsEditorSettings.h` (Public)


#### class `UAudioInsightsEditorSettings`  
`class UAudioInsightsEditorSettings : public UDeveloperSettings`  
_L18-94_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- L23 _public prototype_ `UAudioInsightsEditorSettings();`
- L25 _public prototype_ `virtual FName GetCategoryName() const override;`
- L26 _public prototype_ `virtual FText GetSectionText() const override;`
- L27 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L29 _public prototype_ `virtual void PostInitProperties() override;`
- L30 _public prototype_ `virtual void BeginDestroy() override;`
- L31 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L32 _public prototype_ `virtual void PostEditUndo() override;`
- L36 _public member_ `bool bWorldFilterDefaultsToFirstClient = false;` — `UPROPERTY(Config, EditAnywhere, Category="World Filter")` — Whether to automatically set the first PIE client in Audio Insights World Filter.
- L40 _public member_ `bool bOnlyTraceAudioChannels = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Trace Channels")` — Disable all non - command line trace channels apart from Audio, Audio Mixer and Bookmark when starting a live monitoring / live trace.This will reduce the file size of snapshots / trace sessions while using Audio Insights.
- L44 _public member_ `FSpectrogramRackUnitSettings SpectrogramSettings;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram, meta = (ShowOnlyInnerProperties))` — Settings for analyzer rack spectrogram widget
- L48 _public member_ `FSpectrumAnalyzerRackUnitSettings SpectrumAnalyzerSettings;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer, meta = (ShowOnlyInnerProperties))` — Settings for analyzer rack spectrum analyzer widget
- L52 _public member_ `FAudioEventLogSettings EventLogSettings;` — `UPROPERTY(EditAnywhere, config, Category = EventLog, meta = (ShowOnlyInnerProperties))` — Settings for the Event Log
- L56 _public member_ `FSoundDashboardSettings SoundDashboardSettings;` — `UPROPERTY(EditAnywhere, config, Category = SoundDashboard, meta = (ShowOnlyInnerProperties))` — Settings for the Sound Dashboard
- L60 _public member_ `FSignalFlowSettings SignalFlowSettings;` — `UPROPERTY(EditAnywhere, config, Category = SignalFlow, meta = (ShowOnlyInnerProperties))` — Settings for the Signal Flow Dashboard
- L62 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlyTraceAudioChannelsPropertyChanged, const bool);`
- L63 _public member_ `FOnOnlyTraceAudioChannelsPropertyChanged OnOnlyTraceAudioChannelsPropertyChanged;`
- L72 _private prototype_ `bool VerifyEventLogInput(const TDoubleLinkedList<FProperty*>::TDoubleLinkedListNode& ActiveMemberNode, FPropertyChangedChainEvent& PropertyChangedEvent);`
- L74 _private prototype_ `void RefreshEventFilter();`
- L75 _private prototype_ `bool VerifyCategoryEdit();`
- L76 _private prototype_ `bool VerifyCustomEventNameEdit(const FPropertyChangedChainEvent& PropertyChangedEvent, const FMapProperty* CategoryToEventMapProperty, const FSetProperty* EventNamesSetProperty);`
- L78 _private prototype_ `FString* GetEditedCategoryKey(const FPropertyChangedChainEvent& PropertyChangedEvent, const FMapProperty* CategoryToEventMapProperty) const;`
- L79 _private prototype_ `EditedEvent GetEditedEvent(const FPropertyChangedChainEvent& PropertyChangedEvent, const FSetProperty* EditedEventsSetProperty, const FAudioEventLogCustomEvents& Events) const;`
- L80 _private prototype_ `bool IsEventNameUnique(const FString& EditedEventName, const FString& EditedFilterCategory, const int32 EditedLogicalIndex) const;`
- L82 _private prototype_ `void ShowNotification(const FText& TitleText, const FText& SubText) const;`
- L84 _private member_ `FDelegateHandle OnRequestReadEventLogSettingsHandle;`
- L85 _private member_ `FDelegateHandle OnRequestWriteEventLogSettingsHandle;`
- L87 _private member_ `FDelegateHandle OnRequestReadSoundDashboardSettingsHandle;`
- L88 _private member_ `FDelegateHandle OnRequestWriteSoundDashboardSettingsHandle;`
- L90 _private member_ `FDelegateHandle OnRequestReadSignalFlowSettingsHandle;`
- L91 _private member_ `FDelegateHandle OnRequestWriteSignalFlowSettingsHandle;`
- L93 _private member_ `const TMap<FString, TSet<FString>> InBuiltAudioLogEventTypes;`

#### struct `UAudioInsightsEditorSettings::EditedEvent`  
`struct EditedEvent`  
_L66-70_
- L68 _public member_ `FString* EventName = nullptr;`
- L69 _public member_ `int32 LogicalIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOINSIGHTSEDITOR_API`
- L62 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlyTraceAudioChannelsPropertyChanged, const bool);`

### `Plugins/AudioInsights/Source/AudioInsightsEditor/Public/IAudioInsightsEditorModule.h` (Public)


#### class `IAudioInsightsEditorModule`  
`class IAudioInsightsEditorModule : public IAudioInsightsModuleInterface`  
_L21-36_
- inherits: `IAudioInsightsModuleInterface`
- L24 _public prototype_ `virtual void RegisterDashboardViewFactory(TSharedRef<UE::Audio::Insights::IDashboardViewFactory> InDashboardFactory) = 0;`
- L25 _public prototype_ `virtual void UnregisterDashboardViewFactory(FName InName) = 0;`
- L27 _public prototype_ `virtual ::Audio::FDeviceId GetDeviceId() const = 0;`
- L29 _public prototype_ `virtual IAudioInsightsTraceModule& GetTraceModule() override;`
- L31 _public prototype_ `virtual TSharedRef<SDockTab> CreateDashboardTabWidget(const FSpawnTabArgs& Args) = 0;`
- L33 _public prototype_ `static bool IsModuleLoaded();`
- L35 _public prototype_ `static IAudioInsightsEditorModule& GetChecked();`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Audio` (scope `UE`)
- L15 _namespace_ `namespace Insights` (scope `UE::Audio`)
