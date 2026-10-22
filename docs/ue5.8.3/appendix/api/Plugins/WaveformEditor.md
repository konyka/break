# Plugins / WaveformEditor

- module root: `Plugins/Editor/WaveformEditor/Source/WaveformEditor`
- headers: 17; symbols: 289
- symbol kinds: class=17, delegate=1, enum=3, enumerator=10, function=3, macro=2, member=102, namespace=3, prototype=147, struct=1
- PrivateDependencyModuleNames: AssetDefinition, AudioEditor, ClassViewer, PropertyEditor
- PublicDependencyModuleNames: AssetRegistry, AudioExtensions, AudioSynesthesiaCore, AudioWidgets, ContentBrowser, Core, CoreUObject, DeveloperSettings, EditorScriptingUtilities, EditorStyle, Engine, InputCore, SignalProcessing, Slate, SlateCore, ToolMenus, UnrealEd, WaveformEditorWidgets, WaveformTransformations, WaveformTransformationsWidgets

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/IWaveformEditorDetailsProvider.h` (Private)


#### class `IWaveformEditorDetailsProvider`  
`class IWaveformEditorDetailsProvider`  
_L10-14_
- L13 _public prototype_ `virtual void GetHandlesForUObjectProperties(const TObjectPtr<UObject> InUObject, TArray<TSharedRef<IPropertyHandle>>& OutPropertyHandles) = 0;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/ResaveSoundWaveLoudnessCommandlet.h` (Private)


#### class `UResaveSoundWaveLoudnessCommandlet`  
`class UResaveSoundWaveLoudnessCommandlet : public UResavePackagesCommandlet`  
_L26-50_
- reflection: `UCLASS()`
- inherits: `UResavePackagesCommandlet`
- desc: Commandlet to migrate legacy USoundWave assets that are missing loudness metadata (LUFS and SamplePeakDB). These values were not computed on import prior to 5.8. Inherits from UResavePackagesCommandlet, so all standard path filtering and source control options are available: # Migrate all SoundWaves in the project UnrealEditor.exe Project.uproject -run=ResaveSoundWaveLoudness -AutoCheckOut # Scope to specific content folders (+ delimited for multiple paths) UnrealEditor.exe Project.uproject -run=ResaveSoundWaveLoudness -PACKAGEFOLDER=/Game/Audio+/Game/SFX -AutoCheckOut # With batched source control and auto-checkin UnrealEditor.exe Project.uproject -run=ResaveSoundWaveLoudness -AutoCheckOut -AutoCheckIn -BatchSourceControl
- L31 _public prototype_ `UResaveSoundWaveLoudnessCommandlet();`
- L34 _public prototype_ `virtual int32 Main(const FString& Params) override;` — UCommandlet interface
- L38 _protected prototype_ `virtual bool ShouldSkipPackage(const FString& Filename) override;` — UResavePackagesCommandlet interface
- L39 _protected prototype_ `virtual void PerformAdditionalOperations(UObject* Object, bool& bSavePackage) override;`
- L43 _private member_ `int32 NumMigrated = 0;` — Number of SoundWaves that had loudness data computed and will be resaved.
- L46 _private member_ `int32 NumSkipped = 0;` — Number of SoundWaves that already had valid loudness data.
- L49 _private member_ `int32 NumFailed = 0;` — Number of SoundWaves where loudness analysis failed (no raw PCM data).

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/TransformedWaveformViewFactory.h` (Private)


#### enum `TransformedWaveformViewFactory::EReceivedInteractionType`  
`enum class EReceivedInteractionType`  
_L24-30_
- L26 _public enumerator_ `MouseButtonUp`
- L27 _public enumerator_ `MouseButtonDown`
- L28 _public enumerator_ `MouseMove`
- L29 _public enumerator_ `COUNT`

#### class `FTransformedWaveformViewFactory`  
`class FTransformedWaveformViewFactory`  
_L33-47_
- L36 _public prototype_ `static FTransformedWaveformViewFactory& Get();`
- L37 _public prototype_ `static void Create();`
- L39 _public prototype_ `FTransformedWaveformView GetTransformedView(TObjectPtr<USoundWave> SoundWaveToView, TSharedRef<FSparseSampledSequenceTransportCoordinator> TransportCoordinator, FNotifyHook* OwnerNotifyHook = nullptr, TSharedPtr<FWaveformEditorZoomController> InZoomController = nullptr);`
- L42 _private prototype_ `void SetUpWaveformPanelInteractions(TSharedRef<STransformedWaveformViewPanel> WaveformPanel, TSharedRef<FSparseSampledSequenceTransportCoordinator> TransportCoordinator, TSharedPtr<FWaveformEditorZoomController> InZoomController = nullptr, TSharedPtr<SWaveformTransformationsOverlay> InTransformationsOverlay = nullptr);`
- L43 _private prototype_ `FReply HandleTimeRulerInteraction(const TransformedWaveformViewFactory::EReceivedInteractionType MouseInteractionType, TSharedRef<FSparseSampledSequenceTransportCoordinator> TransportCoordinator, const TSharedRef<SWidget> TimeRulerWidget, const FPointerEvent& MouseEvent, const FGeometry& Geometry);`
- L45 _private member_ `static TUniquePtr<FTransformedWaveformViewFactory> Instance;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WAVEFORMEDITOR_API`
- L22 _namespace_ `namespace TransformedWaveformViewFactory`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/WaveformEditorDetailsCustomization.h` (Private)


#### class `FWaveformTransformationsDetailsCustomization`  
`class FWaveformTransformationsDetailsCustomization : public IDetailCustomization`  
_L11-16_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

#### class `FWaveformTransformationsDetailsProvider`  
`class FWaveformTransformationsDetailsProvider : public IDetailCustomization, public IWaveformEditorDetailsProvider`  
_L19-31_
- inherits: `IDetailCustomization,IWaveformEditorDetailsProvider`
- L23 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L27 _public prototype_ `virtual void GetHandlesForUObjectProperties(const TObjectPtr<UObject> InUObject, TArray<TSharedRef<IPropertyHandle>>& OutPropertyHandles) override;` — IWaveformEditorDetailsProvider interface
- L30 _private member_ `TSharedPtr<class IPropertyHandle> CachedTransformationsHandle;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/WaveformEditorInstantiator.h` (Private)


#### class `FWaveformEditorInstantiator`  
`class FWaveformEditorInstantiator : public IWaveformEditorInstantiator, public TSharedFromThis<FWaveformEditorInstantiator>`  
_L11-25_
- inherits: `IWaveformEditorInstantiator,TSharedFromThis<FWaveformEditorInstantiator>`
- L14 _public prototype_ `virtual void ExtendContentBrowserSelectionMenu() override;`
- L17 _public prototype_ `virtual void RegisterAsSoundwaveEditor() override;` — Registers using a delegate as the default editor for soundwave assets without main engine referencing waveform plugin in Sound Wave Asset Definition
- L18 _public prototype_ `virtual ~FWaveformEditorInstantiator() = default;`
- L21 _private prototype_ `virtual void CreateWaveformEditor(TArray<USoundWave*> SoundWavesToEdit) override;`
- L22 _private prototype_ `void ExecuteReImportAndOverwriteTransformations(const FToolMenuContext& MenuContext);`
- L23 _private prototype_ `bool CanSoundWaveBeOpenedInEditor(const USoundWave* SoundWaveToEdit);`
- L24 _private prototype_ `void DisplayErrorDialog(const FText& ErrorMessage) const;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/WaveformEditorTransformationsSettings.h` (Private)


#### class `UWaveformEditorTransformationsSettings`  
`class UWaveformEditorTransformationsSettings : public UDeveloperSettings`  
_L16-41_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, defaultconfig, meta = (DisplayName = "Waveform Editor Transformations"))`
- inherits: `UDeveloperSettings`
- desc: Settings to regulate Waveform Transformations behavior inside Waveform Editor plugin.
- L21 _private prototype_ `virtual FName GetCategoryName() const;`
- L24 _private prototype_ `virtual FText GetSectionText() const override;`
- L25 _private prototype_ `virtual FName GetSectionName() const override;`
- L37 _public member_ `TSet<TSubclassOf<UWaveformTransformationBase>> LaunchTransformations;` — `UPROPERTY(config, EditAnywhere, Category = "Launch Options")` — A Transformation chain that will be added to the inspected Soundwave if there aren't any Using TSet to limit each transformation type to one instance to reduce complexity and create a more consistent experience USoundWave::Transformations is a TArray because changing it to TSet will delete user data UWaveformTransformationTrimFade is hidden from selection via details customization because it is added automatically and removed if unused
- L40 _public member_ `float NoiseThreshold = -60.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Zero Crossing Options", meta = (ClampMin = "-144.0", ClampMax = "0.0"))`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/WaveformEditorTransformationsSettingsCustomization.h` (Private)


#### class `FWaveformTransformationLaunchClassFilter`  
`class FWaveformTransformationLaunchClassFilter : public IClassViewerFilter`  
_L12-17_
- inherits: `IClassViewerFilter`
- desc: Hides UWaveformTransformationTrimFade from the class viewer, since it is auto-applied and would be a no-op in LaunchTransformations.
- L15 _public prototype_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override;`
- L16 _public prototype_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override;`

#### class `FWaveformEditorTransformationsSettingsCustomization`  
`class FWaveformEditorTransformationsSettingsCustomization : public IDetailCustomization`  
_L20-26_
- inherits: `IDetailCustomization`
- desc: Installs the launch-transformation class filter onto the Waveform Editor Transformations settings panel, working around DisallowedClasses being ignored for TSet<TSubclassOf<>> properties.
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/WaveformEditorWaveWriter.h` (Private)


#### enum `WaveformEditorWaveWriter::EChannelFormat`  
`enum class EChannelFormat : int32`  
_L11-15_
- L13 _public enumerator_ `Mono = 1`
- L14 _public enumerator_ `Stereo`

#### class `FWaveformEditorWaveWriter`  
`class FWaveformEditorWaveWriter`  
_L19-45_
- L22 _public prototype_ `explicit FWaveformEditorWaveWriter(USoundWave* InSoundWave);`
- L24 _public prototype_ `bool CanCreateSoundWaveAsset() const;`
- L27 _public prototype_ `void ExportTransformedWaveform(bool bIsAsync);` — bIsAsync allows the editor to not hang per file say on bulk operations vs. specific cases that must have sync behaviour like tests
- L29 _public prototype_ `WaveformEditorWaveWriter::EChannelFormat GetExportChannelsFormat() const;`
- L30 _public prototype_ `void SetExportChannelsFormat(const WaveformEditorWaveWriter::EChannelFormat InTargetChannelFormat);`
- L33 _private prototype_ `WaveformEditorWaveWriter::EChannelFormat GetSupportedFormatFromChannelCount(const int InChannelCount) const;`
- L35 _private prototype_ `Audio::TSampleBuffer<int16> GenerateSampleBuffer() const;`
- L36 _private prototype_ `Audio::TSampleBuffer<int16> DownmixBufferToMono(const Audio::FAlignedFloatBuffer& InSampleBuffer, const uint32 InNumChannels, const uint32 InSampleRate) const;`
- L37 _private prototype_ `Audio::TSampleBuffer<int16> UpmixBufferToStereo(const Audio::FAlignedFloatBuffer& InSampleBuffer, const uint32 InNumChannels, const uint32 InSampleRate) const;`
- L39 _private prototype_ `void NormalizeBufferToValue(Audio::FAlignedFloatBuffer& InOutBuffer, const float InTargetMaxValue) const;`
- L41 _private member_ `const WaveformEditorWaveWriter::EChannelFormat DefaultExportFormat = WaveformEditorWaveWriter::EChannelFormat::Stereo;`
- L42 _private member_ `USoundWave* SourceSoundWave = nullptr;`
- L43 _private member_ `TUniquePtr<Audio::FSoundWavePCMWriter> WaveWriter = nullptr;`
- L44 _private member_ `WaveformEditorWaveWriter::EChannelFormat TargetChannelsFormat;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace WaveformEditorWaveWriter`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/IWaveformEditorInstantiator.h` (Public)


#### class `IWaveformEditorInstantiator`  
`class IWaveformEditorInstantiator`  
_L9-17_
- L12 _public prototype_ `virtual void ExtendContentBrowserSelectionMenu() = 0;`
- L13 _public prototype_ `virtual void RegisterAsSoundwaveEditor() = 0;`
- L16 _private prototype_ `virtual void CreateWaveformEditor(TArray<USoundWave*> SoundWavesToEdit) = 0;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/IWaveformEditorModule.h` (Public)


#### class `IWaveformEditorModule`  
`class IWaveformEditorModule : public IModuleInterface`  
_L9-13_
- inherits: `IModuleInterface`
- L12 _private prototype_ `virtual void RegisterContentBrowserExtensions(IWaveformEditorInstantiator* Instantiator) = 0;` — Registers waveform editor asset actions.

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/TransformedWaveformView.h` (Public)


#### struct `FTransformedWaveformView`  
`struct FTransformedWaveformView`  
_L8-17_
- L10 _public member_ `TSharedPtr<STransformedWaveformViewPanel> ViewWidget;`
- L11 _public member_ `TSharedPtr<FWaveformEditorSequenceDataProvider> DataProvider;`
- L13 _public function_ `bool IsValid()`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/WaveformEditor.h` (Public)


#### class `FWaveformEditor`  
`class FWaveformEditor : public FAssetEditorToolkit , public FEditorUndoClient , public FGCObject , public FNotifyHook`  
_L24-237_
- inherits: `FAssetEditorToolkit,FEditorUndoClient,FGCObject,FNotifyHook`
- L31 _public prototype_ `bool Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, USoundWave* SoundWaveToEdit);`
- L32 _public prototype_ `virtual ~FWaveformEditor();`
- L35 _public prototype_ `virtual bool CloseWindow(EAssetEditorCloseReason InCloseReason) override;` — FAssetEditorToolkit interface
- L36 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L37 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L38 _public prototype_ `virtual FName GetEditorName() const override;`
- L39 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L40 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L41 _public prototype_ `virtual EVisibility GetVisibilityWhileAssetCompiling() const override;`
- L42 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L43 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L45 _public prototype_ `void OnAssetReimport(UObject* ReimportedObject, bool bSuccessfullReimport);`
- L48 _public prototype_ `void NotifyPreChange(class FEditPropertyChain* PropertyAboutToChange) override;` — FNotifyHook interface
- L49 _public prototype_ `void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged) override;`
- L52 _public prototype_ `void PostUndo(bool bSuccess) override;` — FEditorUndo interface
- L53 _public prototype_ `void PostRedo(bool bSuccess) override;`
- L54 _public prototype_ `bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L55 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L57 _public prototype_ `void ExportWaveform(bool bIsAsync);`
- L60 _public prototype_ `void SkipToNextMarker();` — Skips the playhead to the next marker
- L61 _public prototype_ `void ResetPlaybackToStart();`
- L63 _public function_ `TSharedPtr<class FSparseSampledSequenceTransportCoordinator> GetTransportCoordinator()`
- L64 _public function_ `const int64 GetPlayheadFramePosition() const`
- L66 _public member_ `static const double EndTimeInvalid;`
- L69 _private prototype_ `bool InitializeAudioComponent();`
- L70 _private prototype_ `bool CreateTransportController();`
- L71 _private prototype_ `bool InitializeZoom();`
- L72 _private prototype_ `bool BindDelegates();`
- L73 _private prototype_ `bool SetUpAssetReimport();`
- L74 _private prototype_ `void ExecuteReimport();`
- L75 _private prototype_ `void ExecuteOverwriteTransformations();`
- L78 _private prototype_ `const TSharedRef<FTabManager::FLayout> SetupStandaloneLayout();` — Sets the wave editor layout
- L81 _private prototype_ `bool RegisterToolbar();` — Toolbar Setup
- L82 _private prototype_ `bool BindCommands();`
- L83 _private prototype_ `TSharedRef<SWidget> GenerateFadeInOptionsMenu();`
- L84 _private prototype_ `TSharedRef<SWidget> GenerateFadeOutOptionsMenu();`
- L85 _private prototype_ `TSharedRef<SWidget> GenerateExportOptionsMenu();`
- L86 _private prototype_ `TSharedRef<SWidget> GenerateImportOptionsMenu();`
- L87 _private prototype_ `bool CanExecuteReimport() const;`
- L90 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);` — Details tabs set up
- L91 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Transformations(const FSpawnTabArgs& Args);`
- L92 _private prototype_ `bool CreateDetailsViews();`
- L95 _private prototype_ `TSharedRef<SDockTab> SpawnTab_WaveformDisplay(const FSpawnTabArgs& Args);` — Waveform view tab setup
- L96 _private prototype_ `bool CreateWaveformView();`
- L97 _private prototype_ `bool CreateTransportCoordinator();`
- L98 _private prototype_ `void BindWaveformViewDelegates(FWaveformEditorSequenceDataProvider& ViewDataProvider, STransformedWaveformViewPanel& ViewWidget);`
- L99 _private prototype_ `void RemoveWaveformViewDelegates(FWaveformEditorSequenceDataProvider& ViewDataProvider, STransformedWaveformViewPanel& ViewWidget);`
- L102 _private prototype_ `void HandlePlaybackPercentageChange(const UAudioComponent* InComponent, const USoundWave* InSoundWave, const float InPlaybackPercentage);` — Playback delegates handlers
- L103 _private prototype_ `void HandleAudioComponentPlayStateChanged(const UAudioComponent* InAudioComponent, EAudioComponentPlayState NewPlayState);`
- L104 _private prototype_ `void HandlePlayheadScrub(const float InTargetPlayBackRatio, const bool bIsMoving);`
- L107 _private prototype_ `void HandleRenderDataUpdate();` — Data View Delegates Handlers
- L108 _private prototype_ `void HandleDisplayRangeUpdate(const TRange<double>);`
- L111 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject overrides
- L112 _private prototype_ `virtual FString GetReferencerName() const override;`
- L113 _private prototype_ `bool CanPressPlayButton() const;`
- L114 _private prototype_ `bool CreateWaveWriter();`
- L115 _private prototype_ `const UWaveformEditorTransformationsSettings* GetWaveformEditorTransformationsSettings() const;`
- L116 _private prototype_ `void AddDefaultTransformations();`
- L119 _private prototype_ `void NotifyPostTransformationChange(const EPropertyChangeType::Type& PropertyChangeType = EPropertyChangeType::ArrayAdd);` — Transformation Functions
- L121 _private prototype_ `TObjectPtr<UWaveformTransformationTrimFade> GetTrimFadeTransformation() const;` — Relies on there being only one TrimFade Transformation on the soundwave
- L122 _private prototype_ `TObjectPtr<UWaveformTransformationTrimFade> GetOrAddTrimFadeTransformation(const bool bMarkModify = true);`
- L124 _private prototype_ `TObjectPtr<UWaveformTransformationMarkers> GetOrAddMarkerTransformation();`
- L126 _private prototype_ `TObjectPtr<UWaveformTransformationMarkers> GetMarkerTransformation() const;` — Relies on there being only one Marker Transformation on the soundwave
- L127 _private prototype_ `TObjectPtr<UWaveformTransformationMarkers> AddMarkerTransformation();`
- L130 _private prototype_ `void BindDelegatesForActiveTransformations();` — Get all active transformations and bind the waveform editor delegates
- L131 _private prototype_ `void UnBindDelegatesForActiveTransformations();`
- L133 _private prototype_ `void ToggleFadeIn();`
- L134 _private prototype_ `bool CanFadeIn();`
- L136 _private prototype_ `void ToggleFadeOut();`
- L137 _private prototype_ `bool CanFadeOut();`
- L138 _private prototype_ `void CreateMarker(bool bIsLoopRegion);`
- L139 _private prototype_ `void DeleteMarker();`
- L140 _private prototype_ `void SkipToNextZeroCrossing();`
- L141 _private prototype_ `void RegenerateTransformations();`
- L142 _private prototype_ `void UpdateTransformations(bool bMarkDirty = true);`
- L143 _private prototype_ `void UpdateRenderElements();`
- L144 _private prototype_ `void UpdateTransportState();`
- L148 _private prototype_ `void UpdateSoundWaveProperties();` — Update SoundWave LUFS and SamplePeak values
- L153 _private prototype_ `void NotifySoundWavePostEditChangeProperty(const FName& PropertyName, const EPropertyChangeType::Type PropertyChangeType = EPropertyChangeType::ValueSet);` — SoundWave->PostEditChange() calls UpdateAsset() which kills all playback of the sound asset. Calling SoundWave->PostEditChangeProperty(PropertyChangedEvent) with a valid property event avoids this.
- L155 _private prototype_ `void ModifyMarkerLoopRegion(ELoopModificationControls Modification);`
- L156 _private prototype_ `void CycleMarkerLoopRegion(ELoopModificationControls Modification);`
- L158 _private prototype_ `void SetCuePointOrigin(TObjectPtr<UWaveformTransformationMarkers> MarkerTransformation);`
- L159 _private prototype_ `void PromptToChangeCuePointOrigin();`
- L161 _private member_ `FTransformedWaveformView WaveformView;`
- L164 _private member_ `TSharedPtr<class FWaveformEditorWaveWriter> WaveWriter = nullptr;` — Exports the edited waveform to a new asset
- L167 _private member_ `TSharedPtr<class FSparseSampledSequenceTransportCoordinator> TransportCoordinator = nullptr;` — Manages Transport info in waveform panel
- L170 _private member_ `TSharedPtr<FWaveformEditorTransportController> TransportController = nullptr;` — Controls Transport of the audio component
- L173 _private member_ `TSharedPtr<FWaveformEditorZoomController> ZoomManager = nullptr;` — Controls and propagates zoom level
- L176 _private member_ `TSharedPtr<IDetailsView> PropertiesDetails;` — Properties tab
- L179 _private member_ `TSharedPtr<IDetailsView> TransformationsDetails;` — Transformations tab
- L182 _private member_ `static const FName AppIdentifier;` — Settings Editor App Identifier
- L185 _private member_ `static const FName PropertiesTabId;` — Tab Ids
- L186 _private member_ `static const FName TransformationsTabId;`
- L187 _private member_ `static const FName WaveformDisplayTabId;`
- L188 _private member_ `static const FName EditorName;`
- L189 _private member_ `static const FName ToolkitFName;`
- L190 _private member_ `TObjectPtr<USoundWave> SoundWave = nullptr;`
- L191 _private member_ `TObjectPtr<UAudioComponent> AudioComponent = nullptr;`
- L192 _private member_ `bool bWasPlayingBeforeScrubbing = false;`
- L193 _private member_ `bool bIsInteractingWithTransformations = false;`
- L194 _private member_ `bool bWasPlayingBeforeChange = false;`
- L196 _private member_ `bool bDeferredRenderUpdatePending = false;` — Defer UpdateRenderElements onto a single ticker fire so heavy regen doesn't run every mouse-move.
- L198 _private member_ `FTSTicker::FDelegateHandle DeferredRenderTickerHandle;` — Handle to the in-flight one-shot ticker, kept so a non-interactive supersede or the destructor can cancel the pending fire.
- L199 _private member_ `float LastReceivedPlaybackPercent = 0.f;`
- L200 _private member_ `EAudioComponentPlayState TransformInteractionPlayState = EAudioComponentPlayState::Stopped;`
- L201 _private member_ `float PlaybackTimeBeforeTransformInteraction = 0.f;`
- L202 _private member_ `float StartTimeBeforeTransformInteraction = 0.f;`
- L203 _private member_ `FWaveTransformUObjectConfiguration TransformationChainConfig;`
- L205 _private member_ `static constexpr float DefaultFadeInAmount = 0.5f;`
- L206 _private member_ `float CachedFadeInAmount = 0.f;`
- L207 _private member_ `TSubclassOf<UTransformationFadeFunction> FadeInType = UWaveformTransformationFade::FadeModeToFadeFunctionMap[EWaveEditorTransformationFadeMode::Exponential];`
- L209 _private member_ `static constexpr float DefaultFadeOutAmount = 0.5f;`
- L210 _private member_ `float CachedFadeOutAmount = 0.f;`
- L211 _private member_ `TSubclassOf<UTransformationFadeFunction> FadeOutType = UWaveformTransformationFade::FadeModeToFadeFunctionMap[EWaveEditorTransformationFadeMode::Exponential];`
- L215 _private member_ `bool bCueChangeRegisteredByWaveformEditor = false;` — Tracking bool to ensure we detect wave cue changes and regenerate transformations Checking the event is bound may have issues if other systems need to subscribe for wave cue array changes
- L224 _private member_ `} ReimportMode;`
- L226 _private prototype_ `FText GetReimportButtonToolTip() const;`
- L227 _private prototype_ `FText GetExportButtonToolTip() const;`
- L229 _private member_ `TSharedPtr<SNotificationItem> ReopenNotificationItem = nullptr;`
- L230 _private member_ `TSharedPtr<SNotificationItem> ChangeCuePointOriginNotificationItem = nullptr;`
- L232 _private member_ `bool bMarkerTransformationIsActive = false;`
- L236 _private member_ `bool bSoundWaveBeingDeleted = false;` — Set to true when the editor is being closed because the SoundWave asset is being deleted or invalidated. Guards against unsafe SoundWave modification in the destructor cleanup path.

#### enum `FWaveformEditor::EWaveEditorReimportMode`  
`enum class EWaveEditorReimportMode : uint8`  
_L217-224_
- L219 _public enumerator_ `SameFile = 0`
- L220 _public enumerator_ `SameFileOverwrite`
- L221 _public enumerator_ `SelectFile`
- L222 _public enumerator_ `COUNT`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API WAVEFORMEDITOR_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/WaveformEditorCommands.h` (Public)


#### class `FWaveformEditorCommands`  
`class FWaveformEditorCommands : public TCommands<FWaveformEditorCommands>`  
_L9-67_
- inherits: `TCommands<FWaveformEditorCommands>`
- L12 _public prototype_ `FWaveformEditorCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;`
- L15 _public prototype_ `static const FWaveformEditorCommands& Get();`
- L18 _public member_ `TSharedPtr<FUICommandInfo> PlaySoundWave;` — Soundwave Playback controls
- L19 _public member_ `TSharedPtr<FUICommandInfo> PauseSoundWave;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> StopSoundWave;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayback;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> ReturnToStart;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ZoomIn;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ZoomOut;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ExportWaveform;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ExportFormatMono;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ExportFormatStereo;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ReimportAsset;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ReimportModeSameFile;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ReimportModeSameFileOverwriteTransformations;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ReimportModeNewFile;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ToggleFadeIn;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> FadeInLinear;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> FadeInExponential;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> FadeInLogarithmic;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> FadeInSigmoid;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ToggleFadeOut;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> FadeOutLinear;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> FadeOutExponential;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> FadeOutLogarithmic;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> FadeOutSigmoid;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> LeftBoundsIncrease;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> LeftBoundsDecrease;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> RightBoundsIncrease;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> RightBoundsDecrease;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> LeftBoundsNextZeroCrossing;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> LeftBoundsPreviousZeroCrossing;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> RightBoundsNextZeroCrossing;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> RightBoundsPreviousZeroCrossing;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> BoundsIncrementIncrease;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> BoundsIncrementDecrease;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> SelectNextLoop;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> SelectPreviousLoop;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> CreateMarker;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> CreateLoopRegion;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> DeleteMarker;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> SkipToNextMarker;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> SkipToNextZeroCrossing;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/WaveformEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWaveformEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWaveformEditor, Log, All);`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/WaveformEditorModule.h` (Public)


#### class `FWaveformEditorModule`  
`class FWaveformEditorModule : public IWaveformEditorModule`  
_L19-34_
- inherits: `IWaveformEditorModule`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _private prototype_ `virtual void RegisterContentBrowserExtensions(IWaveformEditorInstantiator* Instantiator) override;`
- L28 _private member_ `TSharedPtr<IWaveformEditorInstantiator> WaveformEditorInstantiator = nullptr;`
- L30 _private member_ `FDelegateHandle OnPostEngineInitHandle;`
- L31 _private member_ `FDelegateHandle OnAssetPostImportHandle;`
- L32 _private member_ `FDelegateHandle OnSoundBasePreviewHandle;`
- L33 _private member_ `FDelegateHandle OnPackageReloadedHandle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace WaveformAnalysis`
- L16 _prototype_ `bool AnalyzeSoundWaveLoudness(UObject* Object, bool bMarkDirty = true);` (scope `WaveformAnalysis`) — Analyzes loudness of a sound wave and sets LUFS/SamplePeakDB values. Returns true if a soundwave was analyzed.

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/WaveformEditorToolMenuContext.h` (Public)


#### class `UWaveformEditorToolMenuContext`  
`class UWaveformEditorToolMenuContext : public UObject`  
_L12-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L18 _public member_ `TWeakPtr<FWaveformEditor> WaveformEditor;`

### `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Public/WaveformEditorTransportController.h` (Public)


#### class `FWaveformEditorTransportController`  
`class FWaveformEditorTransportController`  
_L8-36_
- L11 _public prototype_ `explicit FWaveformEditorTransportController(UAudioComponent* InAudioComponent);`
- L12 _public prototype_ `~FWaveformEditorTransportController();`
- L14 _public prototype_ `void Play();`
- L15 _public prototype_ `void Play(const float StartTime);`
- L16 _public prototype_ `void Pause();`
- L17 _public prototype_ `void Stop();`
- L18 _public prototype_ `void TogglePlayback();`
- L19 _public prototype_ `bool CanPlay() const;`
- L20 _public prototype_ `bool CanStop() const;`
- L21 _public prototype_ `bool IsPaused() const;`
- L22 _public prototype_ `bool IsPlaying() const;`
- L23 _public prototype_ `void CacheStartTime(const float StartTime);`
- L24 _public prototype_ `void Seek(const float SeekTime);`
- L25 _public prototype_ `float GetCachedAudioStartTimeAsPercentage() const;`
- L28 _private prototype_ `const bool SoundBaseIsValid() const;`
- L30 _private prototype_ `void HandleAudioComponentPlayStateChanged(const UAudioComponent* InAudioComponent, EAudioComponentPlayState NewPlayState);` — Playback delegates handlers
- L31 _private member_ `FDelegateHandle AudioComponentPlayStateChangedDelegateHandle;`
- L33 _private member_ `UAudioComponent* AudioComponent = nullptr;`
- L34 _private member_ `float CachedAudioStartTime = 0.f;`
- L35 _private member_ `bool bCachedTimeDuringPause = false;`
