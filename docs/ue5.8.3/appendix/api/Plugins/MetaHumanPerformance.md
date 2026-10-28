# Plugins / MetaHumanPerformance

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance`
- headers: 31; symbols: 716
- symbol kinds: class=34, delegate=23, enum=7, enumerator=20, function=31, macro=1, member=266, namespace=1, prototype=330, struct=3
- PrivateDependencyModuleNames: AdvancedPreviewScene, AnimationCore, AssetDefinition, AudioPlatformConfiguration, CameraCalibrationCore, CaptureDataCore, CaptureDataUtils, CinematicCamera, ContentBrowserData, ControlRig, ControlRigDeveloper, ControlRigEditor, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, EditorScriptingUtilities, IKRig, ImgMedia, InputCore, InteractiveToolsFramework, LensComponent, LevelSequence, LevelSequenceEditor, MediaAssets, MediaCompositing, MediaCompositingEditor, MetaHumanBodyTrackerInterface, MetaHumanCaptureDataEditor, MetaHumanCaptureUtils, MetaHumanCore, MetaHumanCoreEditor, MetaHumanFaceAnimationSolver, MetaHumanFaceContourTracker, MetaHumanIdentity, MetaHumanIdentityEditor, MetaHumanImageViewer, MetaHumanImageViewerEditor, MetaHumanPlatform, MetaHumanSequencer, MetaHumanSpeech2Face, MetaHumanToolkit, MovieScene, MovieSceneTools, MovieSceneTracks, NNE, OutputLog, PerformanceCaptureCore, Projects, PropertyEditor, RigLogicModule, RigVM, RigVMDeveloper, Sequencer, Slate, SlateCore, SpeechAnimationSolver, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: CaptureDataEditor, Core, Engine, MetaHumanBodyTrackerInterface, MetaHumanCaptureData, MetaHumanCoreEditor, MetaHumanCoreTech, MetaHumanCoreTechLib, MetaHumanPipeline, MetaHumanPipelineCore

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/AssetDefinitions/AssetDefinition_MetaHumanPerformance.h` (Private)


#### class `UAssetDefinition_MetaHumanPerformance`  
`class UAssetDefinition_MetaHumanPerformance : public UAssetDefinitionDefault`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Customizations/MetaHumanPerformanceCustomizations.h` (Private)


#### class `FMetaHumanPerformanceCustomization`  
`class FMetaHumanPerformanceCustomization : public IDetailCustomization`  
_L9-19_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Customizations/MetaHumanSequenceExportCustomization.h` (Private)


#### class `FMetaHumanSequenceExportCustomization`  
`class FMetaHumanSequenceExportCustomization : public IDetailCustomization`  
_L9-21_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L20 _private prototype_ `bool ShouldFilterBlueprint(const FAssetData& InAssetData) const;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanBodyAnimRetargeter.h` (Private)


#### class `FMetaHumanBodyAnimRetargeter`  
`class FMetaHumanBodyAnimRetargeter`  
_L12-29_
- L15 _public prototype_ `bool Initialize(const USkeletalMesh* InSourceMesh, const USkeletalMesh* InTargetMesh, const UIKRetargeter* InRetargeter);`
- L17 _public function_ `bool IsInitialized() const`
- L19 _public prototype_ `void RetargetFrame(const TMap<FString, FTransform>& InBodyAnimationData, TMap<FString, FTransform>& OutBodyAnimationData, float InDeltaTime);`
- L23 _private member_ `FIKRetargetProcessor Processor;`
- L25 _private member_ `FRetargetProfile Profile;`
- L27 _private member_ `TStrongObjectPtr<const USkeletalMesh> SourceMesh = nullptr;`
- L28 _private member_ `TStrongObjectPtr<const USkeletalMesh> TargetMesh = nullptr;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanCalibrationPickerOptions.h` (Private)


#### class `UMetaHumanCalibrationPickerOptions`  
`class UMetaHumanCalibrationPickerOptions : public UObject`  
_L10-18_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Options object shown in the calibration picker dialog's DetailsView.
- L17 _public member_ `TObjectPtr<UCameraCalibration> CameraCalibration;` — `UPROPERTY(EditAnywhere, Category = "Calibration")`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanPerformanceEditor.h` (Private)


#### class `UMetaHumanPerformanceEditor`  
`class UMetaHumanPerformanceEditor : public UAssetEditor`  
_L16-29_
- reflection: `UCLASS()`
- inherits: `UAssetEditor`
- L21 _public prototype_ `void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;`
- L22 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L24 _public prototype_ `void SetObjectToEdit(UObject* InObjects);`
- L28 _protected member_ `TObjectPtr<UObject> ObjectToEdit;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanPerformanceEditorContext.h` (Private)


#### class `UMetaHumanPerformanceEditorContext`  
`class UMetaHumanPerformanceEditorContext : public UObject`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _public member_ `TWeakPtr<FMetaHumanPerformanceEditorToolkit> MetaHumanPerformanceEditorToolkit;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanPerformanceEditorToolkit.h` (Private)


#### class `FMetaHumanPerformanceEditorToolkit`  
`class FMetaHumanPerformanceEditorToolkit : public FMetaHumanToolkitBase`  
_L25-202_
- inherits: `FMetaHumanToolkitBase`
- L30 _public prototype_ `FMetaHumanPerformanceEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L31 _public prototype_ `virtual ~FMetaHumanPerformanceEditorToolkit();`
- L34 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L35 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L36 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L37 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L38 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L39 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L40 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L41 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L42 _public prototype_ `virtual void HandleUndoOrRedoTransaction(const class FTransaction* InTransaction) override;`
- L46 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L47 _public prototype_ `virtual FString GetReferencerName() const override;`
- L53 _protected prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L54 _protected prototype_ `virtual void BindCommands() override;`
- L55 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L56 _protected prototype_ `virtual void HandleGetViewABMenuContents(EABImageViewMode InViewMode, class FMenuBuilder& InMenuBuilder) override;`
- L57 _protected prototype_ `virtual void HandleSequencerMovieSceneDataChanged(EMovieSceneDataChangeType InDataChangeType) override;`
- L58 _protected prototype_ `virtual void HandleSequencerGlobalTimeChanged() override;`
- L59 _protected prototype_ `virtual void HandleFootageDepthDataChanged(float InNear, float InFar) override;`
- L63 _protected prototype_ `virtual void InitToolMenuContext(struct FToolMenuContext& InMenuContext) override;`
- L68 _private member_ `TObjectPtr<class UMetaHumanPerformance> Performance = nullptr;` — The object being edited by this toolkit
- L71 _private member_ `static const FName ImageReviewTabId;` — Tabs
- L72 _private member_ `static const FName ControlRigTabId;`
- L74 _private prototype_ `TSharedRef<SDockTab> SpawnImageReviewTab(const FSpawnTabArgs& InArgs);`
- L75 _private prototype_ `TSharedRef<SDockTab> SpawnControlRigTab(const FSpawnTabArgs& InArgs);`
- L78 _private prototype_ `void InitPerformerViewport();` — Initialization
- L79 _private prototype_ `void ExtendToolBar();`
- L80 _private prototype_ `void ExtendMenu();`
- L83 _private prototype_ `TSharedRef<class FMetaHumanPerformanceViewportClient> GetMetaHumanPerformerViewportClient() const;` — Get the viewport client as a FMetaHumanPerformerViewportClient
- L86 _private member_ `TSharedPtr<SMetaHumanOverlayWidget<SMetaHumanImageViewer>> ImageViewer;` — 2D Image review window
- L87 _private member_ `FSlateBrush ImageViewerBrush;`
- L89 _private member_ `FGuid PerformerActorBindingId;`
- L90 _private member_ `FGuid PerformerFaceBindingId;`
- L91 _private member_ `FGuid PerformerBodyBindingId;`
- L92 _private member_ `FVector VisualizationObjectOffset = FVector::ZeroVector;`
- L94 _private prototype_ `void HandleDataInputTypeChanged(EDataInputType InDataInputType);`
- L95 _private prototype_ `void HandleSourceDataChanged(class UFootageCaptureData* InFootageCaptureData, class USoundWave* InAudio, bool bInResetRanges);`
- L96 _private prototype_ `void HandleIdentityChanged(class UMetaHumanIdentity* InIdentity);`
- L97 _private prototype_ `void HandleVisualizeObjectChanged(class UObject* InVisualizeObject);`
- L98 _private prototype_ `void HandleSkeletonParamsChanged();`
- L99 _private prototype_ `void HandleControlRigAssetReferenceChanged(const FControlRigAssetStrongReference& InControlRigAssetReference);`
- L100 _private prototype_ `void HandleHeadMovementModeChanged(EPerformanceHeadMovementMode InHeadMovementMode);`
- L101 _private prototype_ `void HandleHeadMovementReferenceFrameChanged(bool bInAutoChooseHeadMovementReferenceFrame, uint32 InHeadMovementReferenceFrame);`
- L102 _private prototype_ `void HandleNeutralPoseCalibrationChanged();`
- L103 _private prototype_ `void HandleFrameRangeChanged(int32 InStartFrame, int32 InEndFrame);`
- L104 _private prototype_ `void HandleRealtimeAudioChanged(bool bInRealtimeAudio);`
- L105 _private prototype_ `void HandleFrameProcessed(int32 InFrameNumber);`
- L106 _private prototype_ `void HandleStageProcessingFinished(int32 InStageCompleted);`
- L107 _private prototype_ `void HandleProcessingFinished(TSharedPtr<const UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L108 _private prototype_ `void HandleBodyTrackerModeChanged(EMetaHumanBodyTrackerMode InBodyTrackerMode);`
- L110 _private prototype_ `void DeleteSequencerKeysInProcessingRange();`
- L111 _private prototype_ `void UpdateSequencerAnimationData(int32 InFrameNumber);`
- L112 _private prototype_ `void UpdateControlRigHeadPose();`
- L113 _private prototype_ `void UpdatePostProcessAnimBP();`
- L115 _private prototype_ `FString GetPossessableNameFace() const;`
- L116 _private prototype_ `FString GetPossessableNameEffectiveBody() const;`
- L117 _private prototype_ `FString GetPossessableNameRealBody() const;`
- L118 _private prototype_ `FString GetPossessableNameActor() const;`
- L120 _private prototype_ `void UpdateVisualizationObject(UObject* InVisualizeObject);`
- L121 _private prototype_ `bool HasPropertyChanged(const class FTransaction* InTransaction, const FName& InPropertyName) const;`
- L122 _private prototype_ `void RebindSequencerPossessableObjects();`
- L125 _private prototype_ `FFrameRate GetFrameRate() const;` — Movie info
- L126 _private prototype_ `FFrameNumber GetCurrentFrameNumber() const;`
- L127 _private prototype_ `FFrameNumber GetCurrentAnimationFrameNumber() const;`
- L129 _private prototype_ `void SetControlsEnabled(bool bIsEnabled);`
- L132 _private prototype_ `bool CanProcess() const;` — Handle events from widgets in the editor
- L133 _private prototype_ `bool CanCancel() const;`
- L134 _private prototype_ `bool CanExportAnimation() const;`
- L135 _private prototype_ `bool CanExportLevelSequence() const;`
- L136 _private prototype_ `void HandleProcessButtonClicked();`
- L137 _private prototype_ `void HandleCancelButtonClicked();`
- L138 _private prototype_ `void HandleExportAnimationClicked();`
- L139 _private prototype_ `void HandleExportLevelSequenceClicked();`
- L140 _private prototype_ `void HandleViewSetupClicked(int32 InSlotIndexIndex, bool bInStore);`
- L141 _private prototype_ `void HandleImageReviewFocus();`
- L142 _private prototype_ `void HandleShowFramesAsTheyAreProcessed();`
- L145 _private prototype_ `bool DisplayWarningsBeforeProcessing(bool bInDeviceModelIsSet, bool bHasDepthData, bool bInConsistentRGBAndDepthCameras);` — Creates a dialog warning if either bInDeviceModelIsSet, bHasDepthData, or bInConsistentRGBAndDepthCameras are false, returns whether the user agrees to continue
- L148 _private prototype_ `bool ShowCalibrationPickerForDepthGeneration();` — Shows a dialog to pick a calibration asset when depth generation needs one. Returns true if user picked one and it was assigned.
- L151 _private member_ `TObjectPtr<class UMetaHumanPerformanceControlRigComponent> ControlRigComponent;` — The ControlRig component to be displayed in the AB viewport
- L154 _private member_ `TObjectPtr<class USceneComponent> VisualizationObjectComponent;` — The component used to visualize the animation results (face skel mesh, full MetaHuman)
- L158 _private member_ `TObjectPtr<class AMetaHumanBodyDriverActorInterface> BodyDriverActor;` — This actor also displays debugging info like intermediate animation states plus groundplane etc
- L161 _private member_ `TObjectPtr<class UMetaHumanFootageComponent> FootageComponent;` — The component used to display the footage in the AB views
- L164 _private member_ `TSharedPtr<class FMetaHumanCurveDataController> CurveDataController;` — The object that contains the low-level representation for the landmarks that are drawn on screen
- L167 _private member_ `TObjectPtr<class UMetaHumanContourData> DisplayContourData;` — The contour data being displayed on screen
- L173 _private member_ `FMetaHumanPerformanceControlRigViewportManager ControlRigManager;` — A helper class to manage the control rig viewport tab FBaseAssetToolkit only supports one viewport so any other tab that displays
- L176 _private member_ `TObjectPtr<class UControlRig> RecordControlRigFace;` — The ControlRig instance to be used when recording keys in Sequencer from animation data on the face
- L179 _private member_ `TObjectPtr<class UControlRig> RecordControlRigBody;` — The ControlRig instance to be used when recording keys in Sequencer from animation data on the body
- L182 _private prototype_ `FText GetStartProcessingShotButtonTooltipText() const;` — A delegate for dynamic Start Processing Shot button tooltip
- L185 _private prototype_ `FText GetCancelProcessingShotButtonTooltipText() const;` — A delegate for dynamic Cancel Processing Shot button tooltip
- L187 _private member_ `bool bShowFramesAsTheyAreProcessed = false;`
- L190 _private member_ `bool bIsToolkitInitializing = true;` — True if the toolkit is being initialized. This will set to false at the end of PostInitAssetEditor
- L192 _private prototype_ `void SendTelemetryForPerformanceExportRequest(bool InIsAnimationSequence, bool InIsWholeSequence);`
- L194 _private prototype_ `void GetExcludedFrameInfo(FFrameRate& OutSourceRate, FFrameRangeMap& OutExcludedFramesMap, int32& OutMediaStartFrame, TRange<FFrameNumber>& OutProcessingLimit) const;`
- L195 _private prototype_ `ERichCurveInterpMode GetInterpolationMode(int32 InFrameNumber) const;`
- L197 _private prototype_ `USkeletalMeshComponent* GetFaceSkeletalMeshComponent() const;`
- L198 _private prototype_ `USkeletalMeshComponent* GetBodySkeletalMeshComponent() const;`
- L199 _private prototype_ `class USkeletalMesh* GetFaceSkeletalMesh() const;`
- L201 _private member_ `TSharedPtr<class FMetaHumanPerformanceNotifier> ActiveNotifier;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanPerformanceFactoryNew.h` (Private)


#### class `UMetaHumanPerformanceFactoryNew`  
`class UMetaHumanPerformanceFactoryNew : public UFactory`  
_L14-26_
- reflection: `UCLASS(hideCategories = Object)`
- inherits: `UFactory`
- L20 _public prototype_ `UMetaHumanPerformanceFactoryNew();`
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual FText GetToolTip() const override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanPerformanceLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanPerformance, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanPerformance, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanPerformanceModule.h` (Private)


#### class `FMetaHumanPerformanceModule`  
`class FMetaHumanPerformanceModule : public IModuleInterface`  
_L7-23_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `FDelegateHandle MediaTrackEditorBindingHandle;`
- L18 _private member_ `FDelegateHandle AudioTrackEditorBindingHandle;`
- L21 _private member_ `FName PerformanceClassName;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L22 _private member_ `FName ExportLevelSequenceCustomizationClassName;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanPerformanceViewportSettings.h` (Private)


#### struct `FMetaHumanPerformanceViewportState`  
`struct FMetaHumanPerformanceViewportState`  
_L15-21_
- reflection: `USTRUCT()`
- L20 _public member_ `uint8 bShowControlRig : 1;` — `UPROPERTY()`

#### class `UMetaHumanPerformanceViewportSettings`  
`class UMetaHumanPerformanceViewportSettings : public UMetaHumanViewportSettings`  
_L24-48_
- reflection: `UCLASS()`
- inherits: `UMetaHumanViewportSettings`
- L31 _public prototype_ `UMetaHumanPerformanceViewportSettings();`
- L34 _public prototype_ `bool IsControlRigVisible(EABImageViewMode InView) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L37 _public prototype_ `void ToggleControlRigVisibility(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L42 _public member_ `FFrameTime CurrentFrameTime;` — `UPROPERTY()`
- L47 _private member_ `TMap<EABImageViewMode, FMetaHumanPerformanceViewportState> PerformanceViewportState;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/MetaHumanPerformerCommands.h` (Private)


#### class `FMetaHumanPerformanceCommands`  
`class FMetaHumanPerformanceCommands : public TCommands<FMetaHumanPerformanceCommands>`  
_L8-28_
- inherits: `TCommands<FMetaHumanPerformanceCommands>`
- L12 _public prototype_ `FMetaHumanPerformanceCommands();`
- L15 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L18 _public member_ `TSharedPtr<FUICommandInfo> StartProcessingShot;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> CancelProcessingShot;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ExportAnimation;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ExportLevelSequence;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> ToggleRig;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ToggleFootage;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ToggleControlRigDisplay;`
- L25 _public member_ `TArray<TSharedPtr<FUICommandInfo>> ViewSetupStore;`
- L26 _public member_ `TArray<TSharedPtr<FUICommandInfo>> ViewSetupRestore;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowFramesAsTheyAreProcessed;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceAudioSection.h` (Private)


#### class `FMetaHumanPerformanceAudioSection`  
`class FMetaHumanPerformanceAudioSection : public FAudioSection`  
_L7-21_
- inherits: `FAudioSection`
- L11 _public prototype_ `FMetaHumanPerformanceAudioSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);`
- L14 _public prototype_ `virtual bool SectionIsResizable() const;` — ISequencerSectionInterface
- L15 _public prototype_ `virtual bool IsReadOnly() const;`
- L16 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& InPainter) const override;`
- L19 _private member_ `TWeakPtr<ISequencer> SequencerPtr;`
- L20 _private member_ `UMovieSceneSection* Section = nullptr;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceAudioTrackEditor.h` (Private)


#### class `FMetaHumanPerformanceAudioTrackEditor`  
`class FMetaHumanPerformanceAudioTrackEditor : public FAudioTrackEditor`  
_L8-39_
- inherits: `FAudioTrackEditor`
- L16 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InOwningSequencer)` — Create a new track editor instance. This is called by ISequencerModule::RegisterPropertyTrackEditor when registering this editor
- L25 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates, which in the case of this track editor it is just an empty list
- L30 _public prototype_ `FMetaHumanPerformanceAudioTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L33 _public prototype_ `virtual bool SupportsSequence(class UMovieSceneSequence* InSequence) const override;` — ISequencerTrackEditor interface
- L34 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L35 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L36 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L38 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceMediaSection.h` (Private)


#### class `FMetaHumanPerformanceMediaSection`  
`class FMetaHumanPerformanceMediaSection : public FMetaHumanMediaSection`  
_L12-22_
- inherits: `FMetaHumanMediaSection`
- desc: Extends FMediaThumbnailSection to allow painting on top of the sequencer section
- L16 _public prototype_ `FMetaHumanPerformanceMediaSection(UMovieSceneMediaSection& InSection, TSharedPtr<class FTrackEditorThumbnailPool> InThumbnailPool, TSharedPtr<class ISequencer> InSequencer);`
- L19 _public prototype_ `virtual bool IsReadOnly() const override;`
- L20 _public prototype_ `virtual bool SectionIsResizable() const override;`
- L21 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& InPainter) const override;`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace MetaHumanPerformanceSectionPainterHelper`
- L27 _prototype_ `int32 PaintAnimationResults(FSequencerSectionPainter& InPainter, int32 InLayerId, const ISequencer* InSequencer, const UMovieSceneSection* InSection, const UMetaHumanPerformance* InPerformance, bool bInPaintAudioSection);` (scope `MetaHumanPerformanceSectionPainterHelper`)
- L28 _prototype_ `int32 PaintCurrentProcessingStage(FSequencerSectionPainter& InPainter, int32 InLayerId, const ISequencer* InSequencer, const UMovieSceneSection* InSection, const UMetaHumanPerformance* InPerformance);` (scope `MetaHumanPerformanceSectionPainterHelper`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceMediaTrackEditor.h` (Private)


#### class `FMetaHumanPerformanceMediaTrackEditor`  
`class FMetaHumanPerformanceMediaTrackEditor : public FMetaHumanMediaTrackEditor`  
_L12-31_
- inherits: `FMetaHumanMediaTrackEditor`
- desc: MediaTrackEditor that can be added to MetaHumanPerformanceSequences This can be used to customize the behavior of the sequencer track editor Right now this relies on the functionality available in FMediaTrackEditor
- L21 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InOwningSequencer)` — Create a new track editor instance. This is called by ISequencerModule::RegisterPropertyTrackEditor when registering this editor
- L26 _public prototype_ `FMetaHumanPerformanceMediaTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L29 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L30 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceMovieSceneAudioSection.h` (Private)


#### class `UMetaHumanPerformanceMovieSceneAudioSection`  
`class UMetaHumanPerformanceMovieSceneAudioSection : public UMovieSceneAudioSection`  
_L13-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneAudioSection`
- desc: Implements a MovieSceneAudioSection that holds a reference to a PerformanceShot asset allowing customization of how to display it in Sequencer
- L19 _public prototype_ `UMetaHumanPerformanceMovieSceneAudioSection(const FObjectInitializer& InObjectInitializer);`
- L22 _public member_ `TObjectPtr<class UMetaHumanPerformance> PerformanceShot;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceMovieSceneAudioTrack.h` (Private)


#### class `UMetaHumanPerformanceMovieSceneAudioTrack`  
`class UMetaHumanPerformanceMovieSceneAudioTrack : public UMovieSceneAudioTrack`  
_L13-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneAudioTrack`
- desc: Implements a UMovieSceneAudioTrack customized for the MetaHumanPerformance plugin
- L20 _public prototype_ `UMetaHumanPerformanceMovieSceneAudioTrack(const FObjectInitializer& InObjectInitializer);`
- L23 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceMovieSceneMediaSection.h` (Private)


#### class `UMetaHumanPerformanceMovieSceneMediaSection`  
`class UMetaHumanPerformanceMovieSceneMediaSection : public UMetaHumanMovieSceneMediaSection`  
_L13-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanMovieSceneMediaSection`
- desc: Implements a MovieSceneMediaSection that holds a reference to a PerformanceShot asset allowing customization of how to display it in Sequencer
- L19 _public prototype_ `UMetaHumanPerformanceMovieSceneMediaSection(const FObjectInitializer& InObjectInitializer);`
- L22 _public member_ `TObjectPtr<class UMetaHumanPerformance> PerformanceShot;` — `UPROPERTY()`
- L25 _public member_ `bool bIsDepthTrack = false;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceMovieSceneMediaTrack.h` (Private)


#### class `UMetaHumanPerformanceMovieSceneMediaTrack`  
`class UMetaHumanPerformanceMovieSceneMediaTrack : public UMetaHumanMovieSceneMediaTrack`  
_L13-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanMovieSceneMediaTrack`
- desc: Implements a MovieSceneMediaTrack customized for the MetaHumanPerformance plugin
- L19 _public prototype_ `UMetaHumanPerformanceMovieSceneMediaTrack(const FObjectInitializer& InObjectInitializer);`
- L22 _public prototype_ `virtual UMovieSceneSection* AddNewMediaSourceOnRow(UMediaSource& MediaSource, FFrameNumber Time, int32 RowIndex) override;`
- L23 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformancePlaybackContext.h` (Private)


#### class `FMetaHumanPerformancePlaybackContext`  
`class FMetaHumanPerformancePlaybackContext : public TSharedFromThis<FMetaHumanPerformancePlaybackContext>`  
_L8-18_
- inherits: `TSharedFromThis<FMetaHumanPerformancePlaybackContext>`
- L12 _public prototype_ `UObject* GetPlaybackContext() const;`
- L15 _private prototype_ `class UWorld* ComputePlaybackContext() const;`
- L17 _private member_ `mutable TWeakObjectPtr<class UWorld> WeakCurrentContext;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Sequencer/MetaHumanPerformanceSequence.h` (Private)


#### class `UMetaHumanPerformanceSequence`  
`class UMetaHumanPerformanceSequence : public UMovieSceneSequence`  
_L13-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSequence`
- desc: Movie scene used by the MetaHumanPerformance system
- L18 _public prototype_ `UMetaHumanPerformanceSequence(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;`
- L22 _public prototype_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;`
- L23 _public prototype_ `virtual void LocateBoundObjects(const FGuid& ObjectId, UObject* Context, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L24 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L25 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L26 _public prototype_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;`
- L27 _public prototype_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* Context) override;`
- L28 _public prototype_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* Context) override;`
- L31 _public prototype_ `virtual FText GetDisplayName() const override;`
- L32 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L37 _public member_ `TObjectPtr<UMovieScene> MovieScene;` — `UPROPERTY()`
- L41 _private member_ `TMap<FGuid, TObjectPtr<UObject>> Bindings;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/UI/MetaHumanPerformanceControlRigComponent.h` (Private)


#### class `UMetaHumanPerformanceControlRigComponent`  
`class UMetaHumanPerformanceControlRigComponent : public UPrimitiveComponent`  
_L14-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPrimitiveComponent`
- desc: Component capable of rendering ControlRigShape actors. It uses the same mechanism as a ChildActorComponent where upon being registered will spawn all control rig shape actors in the world
- L22 _public prototype_ `void SetControlRig(class UControlRig* InControlRig);` — Sets which control rig to use
- L25 _public prototype_ `void UpdateControlRigShapes();` — Updates the transform of all control rig shapes
- L28 _public prototype_ `FBox GetShapesBoundingBox() const;` — Get the bounding box of all visible control rig shapes
- L33 _public prototype_ `virtual void OnRegister() override;`
- L34 _public prototype_ `virtual void OnUnregister() override;`
- L35 _public prototype_ `virtual void OnComponentDestroyed(bool bInDestroyingHierarchy) override;`
- L41 _public member_ `TObjectPtr<class UControlRig> ControlRig;` — `UPROPERTY()`
- L44 _public member_ `TArray<TObjectPtr<class AControlRigShapeActor>> ShapeActors;` — `UPROPERTY()`
- L48 _public member_ `static const FName HeadIKControlName;`
- L49 _public member_ `static const FName HeadIKSwitchControlName;`
- L54 _protected prototype_ `virtual void OnVisibilityChanged() override;` — Applies the visibility to all control rig shape actors we are managing
- L59 _private prototype_ `void SpawnControlRigShapes();` — Spawn all control rig shapes
- L62 _private prototype_ `void DestroyControlRigShapes();` — Destroy all control rig shape actors

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/UI/MetaHumanPerformanceControlRigViewportClient.h` (Private)


#### class `FMetaHumanPerformance2DScrollBehaviorTarget`  
`class FMetaHumanPerformance2DScrollBehaviorTarget : public IClickDragBehaviorTarget`  
_L18-37_
- inherits: `IClickDragBehaviorTarget`
- desc: Allows click-dragging to move the camera in the XZ plane. Heavily based on FUVEditor2DScrollBehaviorTarget but not public on UE5.1
- L23 _public prototype_ `FMetaHumanPerformance2DScrollBehaviorTarget(class FMetaHumanPerformanceControlRigViewportClient* InViewportClient);`
- L26 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L27 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InPressPos) override;`
- L28 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) override;`
- L29 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& InReleasePos) override;`
- L30 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L34 _protected member_ `class FMetaHumanPerformanceControlRigViewportClient* ViewportClient = nullptr;`
- L35 _protected member_ `FVector OriginalCameraLocation;`
- L36 _protected member_ `FVector DragStart;`

#### class `FMetaHumanPerformance2DMouseWheelZoomBehaviorTarget`  
`class FMetaHumanPerformance2DMouseWheelZoomBehaviorTarget : public IMouseWheelBehaviorTarget`  
_L47-81_
- inherits: `IMouseWheelBehaviorTarget`
- desc: Allows the mouse wheel to move the camera forwards/backwards relative to the XZ plane, in the direction pointed to by the mouse. * Heavily based on FUVEditor2DMouseWheelZoomBehaviorTarget but not public on UE5.1
- L52 _public prototype_ `FMetaHumanPerformance2DMouseWheelZoomBehaviorTarget(class FMetaHumanPerformanceControlRigViewportClient* InViewportClient);`
- L55 _public prototype_ `virtual FInputRayHit ShouldRespondToMouseWheel(const FInputDeviceRay& InCurrentPos) override;`
- L56 _public prototype_ `virtual void OnMouseWheelScrollUp(const FInputDeviceRay& InCurrentPos) override;`
- L57 _public prototype_ `virtual void OnMouseWheelScrollDown(const FInputDeviceRay& InCurrentPos) override;`
- L67 _public prototype_ `void SetZoomAmount(double InPercentZoom);` — @param PercentZoomIn How much to move forward on each mouse wheel forward scroll. For instance, passing 20 here will decrease the distance to the XZ plane by 20% each time. The zoom out amount will be set in such a way that it undoes the same effect. For instance if 20 was passed here, zoom out amount will be 25% since zooming in by 20% and then out by 25% of the result gets you back to where you were.
- L68 _public prototype_ `void SetZoomLimits(double InZoomInLimit, double InZoomOutLimit);`
- L70 _public prototype_ `void SetCameraFarPlaneWorldY(double InCameraFarPlaneWorldY);`
- L71 _public prototype_ `void SetCameraNearPlaneProportionY(double InCameraFarPlaneProportionY);`
- L74 _protected member_ `class FMetaHumanPerformanceControlRigViewportClient* ViewportClient = nullptr;`
- L75 _protected member_ `double ZoomInProportion;`
- L76 _protected member_ `double ZoomOutProportion;`
- L77 _protected member_ `double ZoomInLimit;`
- L78 _protected member_ `double ZoomOutLimit;`
- L79 _protected member_ `double CameraFarPlaneWorldY;`
- L80 _protected member_ `double CameraNearPlaneProportionY;`

#### class `FMetaHumanPerformanceControlRigViewportClient`  
`class FMetaHumanPerformanceControlRigViewportClient : public FEditorViewportClient , public IInputBehaviorSource`  
_L92-123_
- inherits: `FEditorViewportClient,IInputBehaviorSource`
- desc: @brief The viewport client used to display the face board control rig in the performance editor This viewport client implements the IInputBehaviorSource which allows arbitrary camera behaviors to be added to the client. This implementation is heavily based on FUVEditor2DViewportClient.
- L97 _public prototype_ `FMetaHumanPerformanceControlRigViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene);`
- L100 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;`
- L101 _public prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L105 _public prototype_ `virtual FString GetReferencerName() const override;`
- L106 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L110 _public prototype_ `virtual const UInputBehaviorSet* GetInputBehaviors() const override;`
- L116 _private member_ `TObjectPtr<class UInputBehaviorSet> BehaviorSet;` — These get added in AddReferencedObjects for memory management
- L119 _private member_ `TUniquePtr<FMetaHumanPerformance2DMouseWheelZoomBehaviorTarget> ZoomBehaviourTarget;` — Implements the zoom behavior using the mouse wheel
- L122 _private member_ `TUniquePtr<FMetaHumanPerformance2DScrollBehaviorTarget> ScrollBehaviorTarget;` — Implements the scroll behavior that allows dragging the camera using the right mouse button

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/UI/MetaHumanPerformanceControlRigViewportManager.h` (Private)


#### class `FMetaHumanPerformanceControlRigViewportManager`  
`class FMetaHumanPerformanceControlRigViewportManager`  
_L11-50_
- desc: A utility class that holds all the information required to render ControlRig controls in a separate viewport tab. This also manages the ControlRig shape Actors that represent the controls in the world
- L16 _public prototype_ `FMetaHumanPerformanceControlRigViewportManager();` — Performs the initializations for things required to drive the control rig viewport
- L19 _public prototype_ `void SetControlRig(class UControlRig* InControlRig);` — Sets which control rig to use
- L21 _public prototype_ `void SetFaceBoardShapeColor(struct FLinearColor InColor);`
- L24 _public prototype_ `void UpdateControlRigShapes();` — Updates the control rig shapes based on the current values from the actual control rig used to drive the animation
- L27 _public prototype_ `void InitializeControlRigTabContents(TSharedRef<class SDockTab> InControlRigTab);` — Initializes the viewport tab contents to display the preview scene where the control rig shapes will be rendered
- L32 _private member_ `TSharedPtr<class FAssetEditorModeManager> EditorModeManager;` — A mode manager used in the control rig viewport client
- L35 _private member_ `TObjectPtr<class UMetaHumanPerformanceControlRigComponent> ControlRigComponent;` — The control rig component responsible for rendering the control rig controls
- L38 _private member_ `TSharedPtr<class FEditorViewportTabContent> ViewportTabContent;` — The viewport tab content where the control rig viewport is displayed.
- L41 _private member_ `AssetEditorViewportFactoryFunction ViewportDelegate;` — The viewport delegate used to initialize the control rig viewport widget.
- L44 _private member_ `TUniquePtr<class FPreviewScene> PreviewScene;` — The preview scene displayed in the control rig viewport
- L47 _private member_ `TSharedPtr<class FMetaHumanPerformanceControlRigViewportClient> ViewportClient;` — The viewport client that controls the control rig viewport
- L49 _private member_ `FDelegateHandle ControlRigOnExecuteDelegateHandle;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/UI/MetaHumanPerformanceStyle.h` (Private)


#### class `FMetaHumanPerformanceStyle`  
`class FMetaHumanPerformanceStyle : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `static FMetaHumanPerformanceStyle& Get();`
- L13 _public prototype_ `static void Register();`
- L14 _public prototype_ `static void Unregister();`
- L17 _private prototype_ `FMetaHumanPerformanceStyle();`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/UI/MetaHumanPerformanceViewportClient.h` (Private)


#### class `FMetaHumanPerformanceViewportClient`  
`class FMetaHumanPerformanceViewportClient : public FMetaHumanEditorViewportClient`  
_L7-37_
- inherits: `FMetaHumanEditorViewportClient`
- L11 _public prototype_ `FMetaHumanPerformanceViewportClient(FPreviewScene* InPreviewScene, class UMetaHumanPerformance* InPerformance);`
- L14 _public prototype_ `virtual TArray<class UPrimitiveComponent*> GetHiddenComponentsForView(EABImageViewMode InViewMode) const override;`
- L15 _public prototype_ `virtual void UpdateABVisibility(bool bInSetViewpoint = true) override;`
- L16 _public prototype_ `virtual bool ShouldShowCurves(EABImageViewMode InViewMode) const override;`
- L17 _public prototype_ `virtual bool ShouldShowControlVertices(EABImageViewMode InViewMode) const override;`
- L18 _public prototype_ `virtual void FocusViewportOnSelection() override;`
- L21 _public prototype_ `bool IsControlRigVisible(EABImageViewMode InViewMode) const;`
- L22 _public prototype_ `void ToggleControlRigVisibility(EABImageViewMode InViewMode);`
- L24 _public prototype_ `void SetRigComponent(TAttribute<class USkeletalMeshComponent*> InRigComponent);`
- L25 _public prototype_ `void SetFootageComponent(TAttribute<class UMetaHumanFootageComponent*> InFootageComponent);`
- L26 _public prototype_ `void SetControlRigComponent(TAttribute<class UMetaHumanPerformanceControlRigComponent*> InControlRigComponent);`
- L30 _protected member_ `TObjectPtr<class UMetaHumanPerformance> Performance;`
- L34 _private member_ `TAttribute<class UMetaHumanPerformanceControlRigComponent*> ControlRigComponent;`
- L35 _private member_ `TAttribute<class USkeletalMeshComponent*> RigComponent;`
- L36 _private member_ `TAttribute<class UMetaHumanFootageComponent*> FootageComponent;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Private/Utils/MetaHumanPerformanceNotifier.h` (Private)


#### class `FMetaHumanPerformanceNotifier`  
`class FMetaHumanPerformanceNotifier : public TSharedFromThis<FMetaHumanPerformanceNotifier>`  
_L11-33_
- inherits: `TSharedFromThis<FMetaHumanPerformanceNotifier>`
- L19 _public prototype_ `static TSharedRef<FMetaHumanPerformanceNotifier> Attach(UMetaHumanPerformance* InPerformance);`
- L21 _public prototype_ `explicit FMetaHumanPerformanceNotifier(UMetaHumanPerformance* InPerformance, FPrivateToken);`
- L22 _public prototype_ `~FMetaHumanPerformanceNotifier();`
- L24 _public prototype_ `FMetaHumanPerformanceNotifier(const FMetaHumanPerformanceNotifier&) = delete;`
- L25 _public prototype_ `FMetaHumanPerformanceNotifier& operator=(const FMetaHumanPerformanceNotifier&) = delete;`
- L27 _public prototype_ `void StartShowing();`
- L32 _private member_ `TPimplPtr<FImpl> Impl;`

#### struct `FMetaHumanPerformanceNotifier::FPrivateToken`  
`struct FPrivateToken`  
_L15-15_
- L15 _public prototype_ `struct FPrivateToken`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Public/MetaHumanPerformance.h` (Public)


#### enum `EDataInputType`  
`enum class EDataInputType : uint8`  
_L35-40_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `DepthFootage UMETA(DisplayName = "Depth Footage", ToolTip = "Process depth enabled footage and an identity into animation")`
- L38 _public enumerator_ `Audio UMETA(DisplayName = "Audio", ToolTip = "Process audio into animation")`
- L39 _public enumerator_ `MonoFootage UMETA(DisplayName = "Monocular Footage", ToolTip = "Process single view footage into animation")`

#### enum `ESolveType`  
`enum class ESolveType : uint8`  
_L43-49_
- reflection: `UENUM()`
- L45 _public enumerator_ `Preview UMETA(DisplayName = "Preview")`
- L46 _public enumerator_ `Standard UMETA(DisplayName = "Standard")`
- L47 _public enumerator_ `AdditionalTweakers UMETA(DisplayName = "Additional Tweakers")`
- L48 _public enumerator_ `AdditionalTweakersPlusChinCompress UMETA(DisplayName = "Additional Tweakers plus Chin Compress")`

#### enum `EPerformanceHeadMovementMode`  
`enum class EPerformanceHeadMovementMode : uint8`  
_L52-62_
- reflection: `UENUM()`
- L55 _public enumerator_ `TransformTrack` — Use a transform track to move the Skeletal Mesh based on its pivot point (root bone)
- L58 _public enumerator_ `ControlRig` — Enables the Head Control Switch in the Control Rig to use control rig for the Head Movement
- L61 _public enumerator_ `Disabled` — No head movement

#### enum `EStartPipelineErrorType`  
`enum class EStartPipelineErrorType : uint8`  
_L65-70_
- reflection: `UENUM()`
- L67 _public enumerator_ `None`
- L68 _public enumerator_ `NoFrames`
- L69 _public enumerator_ `Disabled`

#### class `UMetaHumanPerformance`  
`class UMetaHumanPerformance : public UObject`  
_L81-787_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: MetaHuman Performance Asset Produces an Animation Sequence for MetaHuman Control Rig by tracking facial expressions in video-footage from a Capture Source, imported through Capture Manager, using a SkeletalMesh obtained through MetaHuman Identity asset toolkit.
- L87 _public prototype_ `UMetaHumanPerformance();`
- L90 _public prototype_ `virtual void BeginDestroy() override;`
- L91 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyAboutToChange) override;`
- L92 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L93 _public prototype_ `virtual void PostEditUndo() override;`
- L94 _public prototype_ `virtual void PostInitProperties() override;`
- L95 _public prototype_ `virtual void PostLoad() override;`
- L96 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L98 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L100 _public prototype_ `virtual FPrimaryAssetId GetPrimaryAssetId() const override;`
- L103 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProcessingFinishedDynamic);`
- L107 _public member_ `FOnProcessingFinishedDynamic OnProcessingFinishedDynamic;` — `UPROPERTY(Transient, BlueprintAssignable, Category = "Processing")` — Dynamic delegate called when the pipeline finishes running
- L110 _public prototype_ `bool CanExportAnimation() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")`
- L118 _public prototype_ `void ExportAnimation(EPerformanceExportRange InExportRange);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")` — (DEPRECATED: use UMetaHumanPerformanceExportUtils::ExportAnimation instead) Export an animation sequence targeting the face skeleton. This will ask the user where to place the new animation sequence
- L121 _public prototype_ `bool DiagnosticsIndicatesProcessingIssue(FText& OutDiagnosticsWarningMessage) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Diagnostics")`
- L125 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataInputTypeChanged, EDataInputType InProcessingType);`
- L126 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSourceDataChanged, class UFootageCaptureData* InFootageCaptureData, class USoundWave* InAudio, bool InResetRanges);`
- L127 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIdentityChanged, class UMetaHumanIdentity* InIdentity);`
- L128 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisualizeMeshChanged, class USkeletalMesh* InVisualizeMesh);`
- L129 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisualizeObjectChanged, class UObject* InVisualizeObject);`
- L130 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSkeletonParamsChanged);`
- L131 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnDepthChanged, float InDepthDataNear, float InDepthDataFar, float InDepthMeshNear, float InDepthMeshFar);`
- L132 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFrameRangeChanged, int32 InStartFrame, int32 InEndFrame);`
- L133 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRealtimeAudioChanged, bool bInRealtimeAudio);`
- L134 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFrameProcessed, int32 InFrame);`
- L135 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessingFinished, TSharedPtr<const UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L136 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStage1ProcessingFinished);`
- L137 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageProcessingFinished, int32 InCurrentStage);`
- L138 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControlRigClassChanged, TSubclassOf<class UControlRig> InControlRigClass);`
- L139 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControlRigAssetReferenceChanged, const FControlRigAssetStrongReference& InControlRigAssetReference);`
- L140 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHeadMovementModeChanged, EPerformanceHeadMovementMode InHeadMovementMode);`
- L141 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHeadMovementReferenceFrameChanged, bool bInAutoChooseHeadMovementReferenceFrame, uint32 InHeadMovementReferenceFrame);`
- L142 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNeutralPoseCalibrationChanged);`
- L143 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnExcludedFramesChanged);`
- L144 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBodyTrackerModeChanged, EMetaHumanBodyTrackerMode InBodyTrackerMode);`
- L145 _public prototype_ `DECLARE_DELEGATE_RetVal(USkeletalMesh*, FOnGetHeadMesh);`
- L147 _public function_ `FOnDataInputTypeChanged& OnDataInputTypeChanged()`
- L148 _public function_ `FOnSourceDataChanged& OnSourceDataChanged()`
- L149 _public function_ `FOnIdentityChanged& OnIdentityChanged()`
- L151 _public function_ `FOnVisualizeMeshChanged& OnVisualizeMeshChanged()` — `UE_DEPRECATED(5.8, "This function is deprecated. Please use OnVisualizeObjectChanged instead.")`
- L152 _public function_ `FOnVisualizeObjectChanged& OnVisualizeObjectChanged()`
- L153 _public function_ `FOnSkeletonParamsChanged& OnSkeletonParamsChanged()`
- L154 _public function_ `FOnFrameRangeChanged& OnFrameRangeChanged()`
- L155 _public function_ `FOnRealtimeAudioChanged& OnRealtimeAudioChanged()`
- L156 _public function_ `FOnFrameProcessed& OnFrameProcessed()`
- L157 _public function_ `FOnProcessingFinished& OnProcessingFinished()`
- L159 _public function_ `FOnStage1ProcessingFinished& OnStage1ProcessingFinished()` — `UE_DEPRECATED(5.8, "This function is deprecated. Please use OnStageProcessingFinished instead.")`
- L160 _public function_ `FOnStageProcessingFinished& OnStageProcessingFinished()`
- L162 _public function_ `FOnControlRigClassChanged& OnControlRigClassChanged()` — `UE_DEPRECATED(5.8, "This function is deprecated. Please use OnControlRigAssetReferenceChanged instead.")`
- L163 _public function_ `FOnControlRigAssetReferenceChanged& OnControlRigAssetReferenceChanged()`
- L164 _public function_ `FOnHeadMovementModeChanged& OnHeadMovementModeChanged()`
- L165 _public function_ `FOnHeadMovementReferenceFrameChanged& OnHeadMovementReferenceFrameChanged()`
- L166 _public function_ `FOnNeutralPoseCalibrationChanged& OnNeutralPoseCalibrationChanged()`
- L167 _public function_ `FOnExcludedFramesChanged& OnExcludedFramesChanged()`
- L168 _public function_ `FOnBodyTrackerModeChanged& OnBodyTrackerModeChanged()`
- L169 _public function_ `FFrameRangeArrayBuilder::FOnGetCurrentFrame& OnGetCurrentFrame()`
- L170 _public function_ `FOnGetHeadMesh& OnGetHeadMesh()`
- L172 _public prototype_ `FFrameRate GetFrameRate() const;`
- L174 _public prototype_ `FString GetHashedPerformanceAssetID();`
- L180 _public member_ `EDataInputType InputType = EDataInputType::DepthFootage;` — `UPROPERTY(EditAnywhere, BlueprintSetter = "SetInputType", Category = "Data")` — Enum to indicate which data input type is being used for the performance
- L185 _public member_ `TObjectPtr<class UFootageCaptureData> FootageCaptureData;` — `UPROPERTY(EditAnywhere, BlueprintSetter = "SetFootageCaptureData", Category = "Data", meta = (EditCondition = "InputType != EDataInputType::Audio", EditConditionHides))` — Real-world footage data with the performance
- L189 _public member_ `TObjectPtr<class USoundWave> Audio;` — `UPROPERTY(EditAnywhere, BlueprintSetter = "SetAudio", Category = "Data", meta = (EditCondition = "InputType == EDataInputType::Audio", EditConditionHides))` — Audio of performance used with the Audio data input type
- L192 _public prototype_ `TObjectPtr<class USoundWave> GetAudioForProcessing() const;` — Getter for audio to use for processing. Either audio in FootageCaptureData or overridden by Audio
- L195 _public prototype_ `FTimecode GetAudioMediaTimecode() const;` — Getter for timecode from audio media
- L198 _public prototype_ `FFrameRate GetAudioMediaTimecodeRate() const;` — Getter for timecode rate from audio media
- L202 _public member_ `FString CaptureDataConfig;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Data", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — Display name of the config to use with the capture data
- L206 _public member_ `FString Camera;` — `UPROPERTY(EditAnywhere, Category = "Data", meta = (EditCondition = "InputType != EDataInputType::Audio", EditConditionHides))` — Name of camera (view) in the footage capture data calibration to use for display and processing
- L210 _public member_ `ETimecodeAlignment TimecodeAlignment = ETimecodeAlignment::Relative;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Timecode alignment type
- L214 _public member_ `TObjectPtr<class UMetaHumanIdentity> Identity;` — `UPROPERTY(EditAnywhere, BlueprintSetter = "SetIdentity", Category = "Data", DisplayName = "MetaHuman Identity", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — A digital double of the person performing in the footage, captured in the MetaHuman Identity asset
- L218 _public member_ `TObjectPtr<class UControlRigBlueprint> ControlRig_DEPRECATED;` — `UPROPERTY()` — Control Rig used to drive the animation
- L222 _public member_ `TSubclassOf<class UControlRig> ControlRigClass_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L226 _public member_ `FControlRigAssetStrongReference ControlRigAssetReference;` — `UPROPERTY(EditAnywhere, Category = "Visualization", DisplayName = "Control Rig", BlueprintSetter = "SetControlRigAssetReference", meta = (GetAssetFilter="ShouldFilterControlRigAsset"))`
- L231 _public member_ `TObjectPtr<class USkeletalMesh> VisualizationMesh;` — `UE_DEPRECATED(5.8, "This variable is deprecated. Please use VisualizationObject instead.")` — `UPROPERTY()` — Set a different object (e.g. head skel mesh or full MetaHuman) for visualizing the final animation
- L234 _public member_ `TObjectPtr<class UObject> VisualizationObject;` — `UPROPERTY(EditAnywhere, Category = "Visualization", meta = (GetAssetFilter = "ShouldFilterVisualizationObject"))`
- L237 _public member_ `bool bShowSkeleton = true;` — `UPROPERTY(EditAnywhere, Category = "Visualization")`
- L240 _public member_ `FVector SkeletonOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Visualization", meta = (EditCondition = "bShowSkeleton"))`
- L243 _public member_ `FColor SkeletonColor = FColor::Purple;` — `UPROPERTY(EditAnywhere, Category = "Visualization", meta = (EditCondition = "bShowSkeleton"))`
- L247 _public member_ `EPerformanceHeadMovementMode HeadMovementMode = EPerformanceHeadMovementMode::TransformTrack;` — `UPROPERTY(EditAnywhere, Category = "Visualization", meta = (EditCondition = "!bBodyTracking", EditConditionHides))` — Head movement type
- L251 _public member_ `uint32 HeadMovementReferenceFrame;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Visualization", meta = (EditCondition = "!bAutoChooseHeadMovementReferenceFrame"))` — Which frame to use as reference frame for head pose (if Auto Choose Head Movement Reference Frame is not selected), default to first processed frame. Changing this will cause a re-bake of Control Rig data
- L255 _public member_ `uint8 bAutoChooseHeadMovementReferenceFrame : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Visualization")` — If set to true, automatically pick the most front - facing frame as the reference frame for control-rig head movement calculation, default to true. Changing this will cause a re-bake of Control Rig data
- L259 _public member_ `int32 HeadMovementReferenceFrameCalculated = -1;` — `UPROPERTY(Transient)` — Head reference frame, calculated from the two properties above. If set to -1, indicates it has not been calculated
- L263 _public member_ `bool bNeutralPoseCalibrationEnabled = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, DisplayName = "Enable Neutral Pose Calibration", Category = "Visualization")` — If set to true perform neutral pose calibration for mono solve, default to false. Changing this will cause a re-bake of Control Rig data
- L267 _public member_ `uint32 NeutralPoseCalibrationFrame = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Visualization")` — Which frame to use as the neutral pose calibration for mono solve (if Enable Neutral Pose Calibration is selected), default to first processed frame. Changing this will cause a re-bake of Control Rig data
- L271 _public member_ `double NeutralPoseCalibrationAlpha = 1.0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Visualization", meta = (ClampMin = 0.0, ClampMax = 1.0))` — Neutral pose calibration alpha parameter, defaults to 1. Changing this will cause a re-bake of Control Rig data
- L275 _public member_ `TArray<FName> NeutralPoseCalibrationCurves = FMetaHumanRealtimeCalibration::GetDefaultProperties();` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Visualization")` — Set of curve names to apply neutral pose calibration to. Changing this will cause a re-bake of Control Rig data
- L279 _public member_ `TObjectPtr<class UMetaHumanFaceContourTrackerAsset> DefaultTracker;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — Tracker parameters for processing the footage
- L283 _public member_ `TObjectPtr<class UMetaHumanFaceAnimationSolver> DefaultSolver;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — Solver parameters for processing the footage
- L287 _public member_ `uint32 StartFrameToProcess;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters")` — The frame to start processing from
- L291 _public member_ `uint32 EndFrameToProcess;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters")` — The frame to end processing with
- L295 _public member_ `ESolveType SolveType = ESolveType::AdditionalTweakers;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — Enum to indicate which type of solve to perform
- L299 _public member_ `bool bEasyToEditControlCurves = false;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — Flag indicating whether we want to produce curves containing combinations of controls which are more easily editable than the normal solve result
- L304 _public member_ `bool bSkipPreview = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Run Preview Pass", Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::DepthFootage || (InputType == EDataInputType::MonoFootage && bBodyTracking)", EditConditionHides))` — Flag indicating if performance predictive solver preview should be ran
- L309 _public member_ `bool bSkipFiltering = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Filter Animation", Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — Flag indicating if process should run animation filtering
- L314 _public member_ `bool bFaceTracking = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Flag indicating if facial solving should be performed
- L319 _public member_ `bool bSkipTongueSolve = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Solve Tongue", Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::DepthFootage || InputType == EDataInputType::MonoFootage", EditConditionHides))` — Flag indicating if the process should run tongue solving
- L324 _public member_ `bool bBodyTracking = false;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", BlueprintSetter = "SetBodyTracking", meta = (EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Flag indicating if body tracking should be performed
- L329 _public member_ `bool bAutoBodyHeight = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Auto Body Height", Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Flag indicating if body height should be automatically inferred
- L333 _public member_ `float BodyHeight = 180.0f;` — `UPROPERTY(EditAnywhere, DisplayName = "Body Height", Category = "Processing Parameters", meta = (Units = "Centimeters", ClampMin=1, ClampMax=1000, NoSpinbox=true))` — Manual Body height. Values outside the range [145, 190] might lead to reduced tracking quality
- L340 _public member_ `float BodyDetectionConfidence = 0.7f;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Threshold for acquiring (or re-acquiring) the subject. Higher values demand a clearly visible subject before tracking begins; lower values allow tracking to start on difficult footage but risk locking onto the wrong subject.
- L347 _public member_ `float BodyTrackingConfidence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Threshold for maintaining the subject lock across frames. Higher values drop the subject during occlusion or fast motion, producing gaps; lower values follow through difficult moments but may drift onto the background or another subject.
- L352 _public member_ `bool bEnableFootLocking = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Enable Foot-Locking", Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Flag indicating if foot-locking should be enabled for the body solver
- L357 _public member_ `bool bSkipPerVertexSolve = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Run Per Vertex Solve", Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — Flag indicating if the process should run per-vertex solve (which is slow to process but gives slightly better animation results)
- L361 _public member_ `bool bRealtimeAudio = false;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::Audio", EditConditionHides))` — Flag indicating if we should use realtime audio solve
- L365 _public member_ `bool bDownmixChannels = true;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::Audio && !bRealtimeAudio", EditConditionHides))` — Downmix multi channel audio before solving into animation
- L369 _public member_ `uint32 AudioChannelIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (ClampMin = 0, ClampMax = 64))` — Specify the audio channel used to solve into animation
- L373 _public member_ `bool bGenerateBlinks = true;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::Audio && !bRealtimeAudio", EditConditionHides))` — Flag indicating if we should generate blinks
- L376 _public member_ `EAudioDrivenAnimationOutputControls AudioDrivenAnimationOutputControls = EAudioDrivenAnimationOutputControls::FullFace;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (DisplayName = "Process Mask", EditCondition = "InputType == EDataInputType::Audio && !bRealtimeAudio", EditConditionHides))`
- L380 _public member_ `FAudioDrivenAnimationModels AudioDrivenAnimationModels;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Processing Parameters", meta = (DisplayName = "Models", EditCondition = "InputType == EDataInputType::Audio && !bRealtimeAudio", EditConditionHides))` — The models to be used by audio driven animation
- L384 _public member_ `FMonocularAnimationPipelineModels MonocularAnimationPipelineModels;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Processing Parameters", meta = (DisplayName = "Facial Models", EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — The models to be used by the monocular pipeline
- L388 _public member_ `float FocalLength = -1;` — `UPROPERTY(VisibleAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — The estimated focal length of the footage
- L392 _public member_ `bool bHeadStabilization = true;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Reduces noise in head position and orientation.
- L399 _public member_ `float HeadAllowedRotationLeftRight = 45.0;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (Units = "Degrees", NoSpinbox = "true", UIMin = "0.0", UIMax = "90.0", ClampMin = "0.0", ClampMax = "90.0", EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Allowed yaw (left/right) head rotation in degrees. Frames where the head turns past this angle are treated as unsolved. Changing this requires reprocessing to take effect.
- L406 _public member_ `float HeadAllowedRotationUpDown = 30;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (Units = "Degrees", NoSpinbox = "true", UIMin = "0.0", UIMax = "90.0", ClampMin = "0.0", ClampMax = "90.0", EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Allowed pitch (up/down) head rotation in degrees. Frames where the head tilts past this angle are treated as unsolved. Changing this requires reprocessing to take effect.
- L413 _public member_ `EFaceUnsolvedFrameBehavior HeadRotationHandler = EFaceUnsolvedFrameBehavior::None;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — How to handle frames where head rotation exceeds the allowed yaw or pitch. - None: leave the frame empty; the exported curves will interpolate across the gap based on the curve interpolation setting. - Neutral Pose: fall back to a neutral face pose. Changing this requires reprocessing to take effect.
- L417 _public member_ `TObjectPtr<UMetaHumanRealtimeSmoothingParams> MonoSmoothingParams;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", DisplayName = "Smoothing", meta = (EditCondition = "InputType == EDataInputType::MonoFootage", EditConditionHides))` — Smoothing parameters to use for mono video processing
- L421 _public member_ `bool bShowFramesAsTheyAreProcessed = true;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters")` — Flag indicating if editor updates current frame to show the results as frames are processed
- L425 _public member_ `FAudioDrivenAnimationSolveOverrides AudioDrivenAnimationSolveOverrides;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters", meta = (DisplayName = "Solve Overrides", ExpandByDefault, EditCondition = "InputType == EDataInputType::Audio && !bRealtimeAudio", EditConditionHides))` — Settings to change the behavior of the audio driven animation solve
- L429 _public member_ `float MinDistance = 10.0;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters|Depth Generation", meta = (Units = "Centimeters", NoSpinbox = "true", UIMin = "0.0", UIMax = "200.0", EditCondition = "(InputType == EDataInputType::DepthFootage) && ShouldShowDepthParameters()", EditConditionHides))` — The minimum cm from the camera expected for valid depth information. Depth information closer than this will be ignored to help filter out noise.
- L433 _public member_ `float MaxDistance = 25.0;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters|Depth Generation", meta = (Units = "Centimeters", NoSpinbox = "true", UIMin = "0.0", UIMax = "200.0", EditCondition = "(InputType == EDataInputType::DepthFootage) && ShouldShowDepthParameters()", EditConditionHides))` — The maximum cm from the camera expected for valid depth information. Depth information beyond this will be ignored to help filter out noise.
- L437 _public member_ `EAudioDrivenAnimationMood RealtimeAudioMood = EAudioDrivenAnimationMood::AutoDetect;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters|Solve Overrides", meta = (DisplayName = "Mood", EditCondition = "InputType == EDataInputType::Audio && bRealtimeAudio", EditConditionHides))` — The mood of the realtime audio driven animation solve
- L441 _public member_ `float RealtimeAudioMoodIntensity = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters|Solve Overrides", meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0, Delta = 0.01, DisplayName = "Mood Intensity", EditCondition = "InputType == EDataInputType::Audio && bRealtimeAudio", EditConditionHides))` — The mood intensity of the realtime audio driven animation solve
- L445 _public member_ `int32 RealtimeAudioLookahead = 80.0;` — `UPROPERTY(EditAnywhere, Category = "Processing Parameters|Solve Overrides", meta = (UIMin = 80.0, ClampMin = 80.0, UIMax = 240.0, ClampMax = 240.0, Delta = 20.0, DisplayName = "Lookahead", EditCondition = "InputType == EDataInputType::Audio && bRealtimeAudio", EditConditionHides))` — The amount of time, in milliseconds, that the audio solver looks ahead into the audio stream to produce the current frame of animation. A larger value will produce higher quality animation but will come at the cost of increased latency.
- L450 _public member_ `bool bSkipDiagnostics = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Compute Diagnostics", Category = "Processing Diagnostics", meta = (EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — Flag indicating whether processing diagnostics should be calculated during processing
- L454 _public member_ `float MinimumDepthMapFaceCoverage = 80.0f;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics", meta = (UIMin = 0.0, UIMax = 100.0, ClampMin = 0.0, ClampMax = 100.0, EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — The minimum percentage of the face region which should have valid depth-map pixels. Below this value a diagnostic warning will be flagged.
- L458 _public member_ `float MinimumDepthMapFaceWidth = 120.0f;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics", meta = (ClampMin = 0.0, ClampMax = 10000.0, EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — The minimum required width of the face region on the depth-map in pixels. Below this value a diagnostic warning will be flagged.
- L462 _public member_ `float MaximumStereoBaselineDifferenceFromIdentity = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics", meta = (ClampMin = 0.0, ClampMax = 100.0, EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — The maximum allowed percentage difference in stereo baseline between Identity and Performance CaptureData camera calibrations. Above this value a diagnostic warning will be flagged.
- L466 _public member_ `float MaximumScaleDifferenceFromIdentity = 7.5f;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics", meta = (ClampMin = 0.0, ClampMax = 100.0, EditCondition = "InputType == EDataInputType::DepthFootage", EditConditionHides))` — The maximum allowed percentage difference in estimated head scale between Identity and Performance. Above this value a diagnostic warning will be flagged.
- L470 _public member_ `TArray<FFrameRange> UserExcludedFrames;` — `UPROPERTY(EditAnywhere, Category = "Excluded frames")` — Frames that the user has identified which are to be excluded from the processing, eg part of the footage where the face goes out of frame
- L474 _public member_ `TArray<FFrameRange> ProcessingExcludedFrames;` — `UPROPERTY(VisibleAnywhere, Category = "Excluded frames")` — Frames that the processing has identified as producing bad results and should not be exported
- L478 _public member_ `TObjectPtr<class UMetaHumanPerformanceViewportSettings> ViewportSettings;` — `UPROPERTY()` — Stores the viewport settings used in the Performance asset editor
- L482 _public member_ `TArray<uint8> AdditionalBodyTrackerData;` — `UPROPERTY()` — Stores data to extend body tracker functionality
- L486 _public prototype_ `EStartPipelineErrorType StartPipeline(bool bInIsScriptedProcessing = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Processing")` — Export options
- L489 _public prototype_ `void CancelPipeline();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Processing")`
- L492 _public prototype_ `bool IsProcessing() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Processing")`
- L495 _public prototype_ `bool CanProcess() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Processing")`
- L499 _public prototype_ `void SetFootageCaptureData(UFootageCaptureData* InFootageCaptureData);` — `UFUNCTION(BlueprintSetter)` — Sets the footage capture data. If the footage has an invalid frame rate, the assignment is rejected and FootageCaptureData is set to nullptr.
- L503 _public prototype_ `void SetInputType(EDataInputType InInputType);` — `UFUNCTION(BlueprintSetter)` — Sets the data input type for processing. Clears stale processing state from the previous mode. If the new type requires footage and the current footage has an invalid frame rate, FootageCaptureData is set to nullptr.
- L507 _public prototype_ `void SetAudio(USoundWave* InAudio);` — `UFUNCTION(BlueprintSetter)` — Sets the audio source. The value is always stored, but processing state is only updated when InputType is Audio.
- L511 _public prototype_ `void SetIdentity(UMetaHumanIdentity* InIdentity);` — `UFUNCTION(BlueprintSetter)` — Sets the MetaHuman Identity for this performance. Resets any existing processed output.
- L520 _public prototype_ `void SetProcessingRange(int32 InStartFrame, int32 InEndFrame);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Performance")` — Sets the processing range. Clamped to the active mode's frame limits, or held and applied later if no source data is loaded yet. If the request has no overlap with the limits, snaps to the full extent. Negative values are treated as zero.
- L524 _public prototype_ `void SetControlRigAssetReference(const FControlRigAssetStrongReference& InControlRigAssetReference);` — `UFUNCTION(BlueprintSetter)` — Sets the Control Rig asset reference directly. Passing an invalid reference loads the default Control Rig.
- L528 _public prototype_ `void SetDepthDistanceRange(float InMinDistance, float InMaxDistance);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Performance")` — Negatives clamped to zero; MinDistance clamped to not exceed MaxDistance.
- L531 _public prototype_ `void SetBlockingProcessing(bool bInBlockingProcessing);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Processing")`
- L534 _public prototype_ `void SetBodyTracking(bool bInBodyTracking);` — `UFUNCTION(BlueprintSetter)`
- L538 _public member_ `TArray<FDepthMapDiagnosticsResult> DepthMapDiagnosticResults;` — `UPROPERTY()` — Outputs
- L541 _public member_ `float ScaleEstimate = 1.0f;` — `UPROPERTY()`
- L544 _public member_ `TArray64<FFrameTrackingContourData> ContourTrackingResults;` — A 64 bit version of Contour Data array to support serialization of longer takes
- L547 _public member_ `TArray64<struct FFrameAnimationData> AnimationData;` — A 64 bit version of Animation Data array to support serialization of longer takes
- L552 _public prototype_ `bool ContainsAnimationData() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|AnimationData")` — `UE_DEPRECATED(5.8, "ContainsAnimationData() is deprecated. Use new ContainsAnimationDataType function which takes the data type as a parameter")` — Returns true if there is at least one animation frame with valid data, false otherwise
- L555 _public prototype_ `bool ContainsAnimationDataType(EFrameAnimationDataType InDataType) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|AnimationData")`
- L560 _public prototype_ `TArray<struct FFrameAnimationData> GetAnimationData(int32 InStartFrameNumber = 0, int32 InEndFrameNumber = -1) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|AnimationData")` — Caller is responsible to ensure data will fit into 32bit TArray
- L563 _public prototype_ `int32 GetNumberOfProcessedFrames() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|AnimationData")`
- L565 _public prototype_ `const TRange<FFrameNumber>& GetProcessingLimitFrameRange() const;`
- L566 _public prototype_ `const TMap<TWeakObjectPtr<UObject>, TRange<FFrameNumber>>& GetMediaFrameRanges() const;`
- L567 _public prototype_ `FFrameNumber GetMediaStartFrame() const;`
- L568 _public prototype_ `TRange<FFrameNumber> GetExportFrameRange(EPerformanceExportRange InExportRange) const;`
- L570 _public function_ `int32 GetPipelineStage() const`
- L571 _public function_ `int32 GetPipelineFrameRange() const`
- L572 _public function_ `int32 GetPipelineFrameRanges() const`
- L573 _public function_ `TArray<FFrameRange> GetPipelineFrameRangesArray() const`
- L575 _public prototype_ `int32 GetTotalPipelineStage() const;`
- L584 _public prototype_ `USkeletalMesh* GetHeadMesh() const;` — Returns the effective Head Skeletal Mesh used for visualization. If a VisualizationObject if set then this will be that object if its a Skel Mesh, but if the object is a MetaHuman BP object then the head component of that is returned. If no VisualizationObject if set the MetaHuman Identity skeletal mesh is returned; Returns nullptr if no valid Skeletal Mesh was found
- L593 _public prototype_ `USkeletalMesh* GetVisualizationMesh() const;` — `UE_DEPRECATED(5.8, "This function is deprecated. Please use GetHeadMesh instead.")`
- L596 _public prototype_ `FTransform CalculateReferenceFramePose();` — Calculate the head pose from the AnimationData, either using specified reference frame, or auto-selecting the best one
- L599 _public prototype_ `bool HasValidAnimationPose() const;` — Returns if any frame has valid pose in the AnimationData
- L602 _public prototype_ `FTransform GetFirstValidAnimationPose() const;` — Returns the first valid pose in the AnimationData
- L605 _public prototype_ `TSet<FString> GetAnimationCurveNames() const;` — Returns a list of animation curves used by this Performance
- L608 _public prototype_ `FText GetCannotProcessTooltipText() const;` — Returns tooltip text with a reason why processing cant be started
- L611 _public member_ `TArray<TSharedPtr<FString>> CameraNames;` — List of all RGB cameras (views) in the footage capture data
- L613 _public prototype_ `bool HasDepthData() const;`
- L616 _public prototype_ `bool NeedsCalibrationForDepthGeneration() const;` — Returns true if depth can be generated from stereo RGB cameras but calibration is missing
- L618 _public prototype_ `bool ShouldShowDepthParameters() const;` — `UFUNCTION()`
- L621 _public prototype_ `bool DepthCameraConsistentWithRGBCameraOrDiagnosticsNotEnabled() const;` — Returns true if the depth camera location is consistent with the RGB camera location, or diagnostics are not enabled
- L623 _public prototype_ `EFrameRangeType GetExcludedFrame(int32 InFrameNumber) const;`
- L626 _public prototype_ `static FVector GetSkelMeshReferenceBoneLocation(USkeletalMeshComponent* InSkelMeshComponent, const FName& InBoneName);` — Returns a bone position in the reference skeleton - used to account for variations in the heights of different MetaHumans
- L629 _public prototype_ `bool EstimateFocalLength(FString &OutErrorMessage);` — Estimate the focal length of the footage
- L631 _public prototype_ `UE_INTERNAL FTransform AudioDrivenHeadPoseTransform(const FTransform& InHeadBonePose) const;`
- L632 _public prototype_ `UE_INTERNAL FTransform AudioDrivenHeadPoseTransformInverse(const FTransform& InRootBonePose) const;`
- L636 _public prototype_ `bool HasSolverHierarchicalDefinitionsPlusChinCompressConfig() const;` — returns true if we have a valid SolverHierarchicalDefinitionsPlusChinCompressConfig, false otherwise (needed for back-compatibility with old configs)
- L642 _private prototype_ `static bool ShouldFilterControlRigAsset(const FAssetData& InAssetData);` — `UFUNCTION()` — Returns true if the given asset should be filtered out from the Control Rig asset picker.
- L645 _private prototype_ `bool ShouldFilterVisualizationObject(const FAssetData& InAssetData);` — `UFUNCTION()`
- L648 _private member_ `FOnDataInputTypeChanged OnDataInputTypeChangedDelegate;`
- L649 _private member_ `FOnSourceDataChanged OnSourceDataChangedDelegate;`
- L650 _private member_ `FOnIdentityChanged OnIdentityChangedDelegate;`
- L651 _private member_ `FOnVisualizeMeshChanged OnVisualizeMeshChangedDelegate;`
- L652 _private member_ `FOnVisualizeObjectChanged OnVisualizeObjectChangedDelegate;`
- L653 _private member_ `FOnSkeletonParamsChanged OnSkeletonParamsChangedDelegate;`
- L654 _private member_ `FOnFrameRangeChanged OnFrameRangeChangedDelegate;`
- L655 _private member_ `FOnRealtimeAudioChanged OnRealtimeAudioChangedDelegate;`
- L656 _private member_ `FOnFrameProcessed OnFrameProcessedDelegate;`
- L657 _private member_ `FOnProcessingFinished OnProcessingFinishedDelegate;`
- L658 _private member_ `FOnStage1ProcessingFinished OnStage1ProcessingFinishedDelegate;`
- L659 _private member_ `FOnStageProcessingFinished OnStageProcessingFinishedDelegate;`
- L660 _private member_ `FOnControlRigClassChanged OnControlRigClassChangedDelegate;`
- L661 _private member_ `FOnControlRigAssetReferenceChanged OnControlRigAssetReferenceChangedDelegate;`
- L662 _private member_ `FOnHeadMovementModeChanged OnHeadMovementModeChangedDelegate;`
- L663 _private member_ `FOnHeadMovementReferenceFrameChanged OnHeadMovementReferenceFrameChangedDelegate;`
- L664 _private member_ `FOnNeutralPoseCalibrationChanged OnNeutralPoseCalibrationChangedDelegate;`
- L665 _private member_ `FOnExcludedFramesChanged OnExcludedFramesChangedDelegate;`
- L666 _private member_ `FOnBodyTrackerModeChanged OnBodyTrackerModeChangedDelegate;`
- L667 _private member_ `FFrameRangeArrayBuilder::FOnGetCurrentFrame OnGetCurrentFrameDelegate;`
- L668 _private member_ `FOnGetHeadMesh OnGetHeadMeshDelegate;`
- L670 _private member_ `TArray<TSharedPtr<UE::MetaHuman::Pipeline::FPipeline>> Pipelines;`
- L671 _private member_ `TArray<FFrameRange> PipelineFrameRanges;`
- L672 _private member_ `TArray<FFrameRange> PipelineExcludedFrames;`
- L673 _private member_ `TArray<FFrameRange> RateMatchingExcludedFrames;`
- L674 _private member_ `int32 PipelineFrameRangesIndex = 0;`
- L675 _private member_ `int32 PipelineStage = 0;`
- L676 _private member_ `double PipelineStageStartTime = 0.0;`
- L677 _private member_ `FString SolverConfigData;`
- L678 _private member_ `FString SolverTemplateData;`
- L679 _private member_ `FString SolverDefinitionsData;`
- L680 _private member_ `FString SolverHierarchicalDefinitionsData;`
- L681 _private member_ `FString SolverHierarchicalDefinitionsPlusChinCompressData;`
- L682 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FTongueTrackerNode> TongueSolver;`
- L683 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FSpeechToAnimNode> SpeechToAnimSolver;`
- L684 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FHyprsenseRealtimeNode> RealtimeMonoSolver;`
- L685 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FRealtimeSpeechToAnimNode> RealtimeSpeechToAnimSolver;`
- L687 _private member_ `TSharedPtr<IMetaHumanBodyTrackerInterface::FBodyTrackerDataInterface> BodyTrackerData;`
- L688 _private member_ `int32 BodyTrackerFinalPipelineStage = 0;`
- L690 _private prototype_ `void StartPipelineStage();`
- L691 _private prototype_ `void SendTelemetryForProcessFootageRequest(TSharedPtr<const UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L693 _private member_ `FString TrackingResultsPinName;`
- L694 _private member_ `FString AnimationResultsPinName;`
- L695 _private member_ `FString DepthMapDiagnosticsResultsPinName;`
- L696 _private member_ `FString ScaleDiagnosticsResultsPinName;`
- L698 _private prototype_ `void FrameComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L699 _private prototype_ `void ProcessComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L701 _private prototype_ `void AddSpeechToAnimSolveToPipeline(UE::MetaHuman::Pipeline::FPipeline& InPipeline, TSharedPtr<UE::MetaHuman::Pipeline::FSpeechToAnimNode> InSpeechAnimNode, FString& OutAnimationResultsPinName);`
- L702 _private prototype_ `void AddTongueSolveToPipeline(UE::MetaHuman::Pipeline::FPipeline& InPipeline, TSharedPtr<UE::MetaHuman::Pipeline::FSpeechToAnimNode> InTongueSolveNode, TSharedPtr<UE::MetaHuman::Pipeline::FNode> InInputNode, TSharedPtr<UE::MetaHuman::Pipeline::FDropFrameNode> InDropFrameNode, TSharedPtr<UE::MetaHuman::Pipeline::FNode>& OutAnimationResultsNode, FString& OutAnimationResultsPinName);`
- L705 _private prototype_ `void ResetOutput(bool bInWholeSequence);`
- L707 _private member_ `bool bBlockingProcessing = false;`
- L710 _private member_ `static TWeakObjectPtr<UMetaHumanPerformance> CurrentlyProcessedPerformance;` — Only one performance asset can be processed at the time
- L712 _private prototype_ `void UpdateFrameRanges();`
- L713 _private prototype_ `float CalculateAudioProcessingOffset();`
- L715 _private member_ `TMap<TWeakObjectPtr<UObject>, TRange<FFrameNumber>> MediaFrameRanges;`
- L716 _private member_ `TRange<FFrameNumber> ProcessingLimitFrameRange = TRange<FFrameNumber>(0, 0);`
- L718 _private prototype_ `void LoadDefaultTracker();`
- L719 _private prototype_ `void LoadDefaultSolver();`
- L720 _private prototype_ `void LoadDefaultControlRig();`
- L722 _private prototype_ `void UpdateCaptureDataConfigName();`
- L723 _private prototype_ `void OnCaptureDataInternalsChanged();`
- L727 _private prototype_ `void SubscribeFootageObserver(UFootageCaptureData* InFootage);` — Wrappers around AddUObject / RemoveAll that keep SubscribedFootageCaptureData in sync with the real registration.
- L728 _private prototype_ `void UnsubscribeFootageObserver(UFootageCaptureData* InFootage);`
- L733 _private member_ `TWeakObjectPtr<UFootageCaptureData> SubscribedFootageCaptureData;` — The transaction system can roll back FootageCaptureData but cannot reverse the delegate registration on the other UObject; this mirror lets PostEditUndo detect and fix the divergence.
- L735 _private prototype_ `TArray<UE::MetaHuman::FSequencedImageTrackInfo> CreateSequencedImageTrackInfos();`
- L736 _private prototype_ `bool FootageCaptureDataViewLookupsAreValid() const;`
- L738 _private member_ `ETimecodeAlignment PreviousTimecodeAlignment = ETimecodeAlignment::None;`
- L741 _private member_ `TObjectPtr<UFootageCaptureData> PreviousFootageCaptureData;` — `UPROPERTY(Transient)`
- L744 _private member_ `TObjectPtr<UMetaHumanFaceAnimationSolver> PreviousDefaultSolver;` — `UPROPERTY(Transient)`
- L750 _private member_ `bool bHasPendingProcessingRange = false;` — `UPROPERTY(Transient)` — SetProcessingRange may be called before source data is loaded. The request is held here and applied by the next ApplySourceDataChange that runs against valid limits.
- L752 _private member_ `uint32 PendingStartFrameToProcess = 0;` — `UPROPERTY(Transient)`
- L754 _private member_ `uint32 PendingEndFrameToProcess = 0;` — `UPROPERTY(Transient)`
- L757 _private member_ `TArray<FFrameTrackingContourData> ContourTrackingResults_DEPRECATED;` — `UPROPERTY()`
- L760 _private member_ `TArray<struct FFrameAnimationData> AnimationData_DEPRECATED;` — `UPROPERTY()`
- L763 _private member_ `TObjectPtr<class USkeletalMesh> OverrideVisualizationMesh_DEPRECATED;` — `UPROPERTY()`
- L765 _private member_ `bool bMetaHumanAuthoringObjectsPresent = false;`
- L767 _private member_ `bool bIsScriptedProcessing = false;`
- L768 _private member_ `double ProcessingStartTime = 0.f;`
- L770 _private member_ `FString EstimateFocalLengthErrorMessage;`
- L771 _private member_ `bool bEstimateFocalLengthOK = false;`
- L772 _private prototype_ `void EstimateFocalLengthFrameComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L773 _private prototype_ `void EstimateFocalLengthProcessComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L775 _private prototype_ `bool HasFrameRateNominatorEqualZero();`
- L779 _private prototype_ `bool HasEmptyProcessingLimits() const;` — Sentinel for "no source data is loaded yet" - the active source yields no usable frame range.
- L781 _private prototype_ `void ApplySourceDataChange();`
- L783 _private prototype_ `void SetFaceTrackingModels();`
- L786 _private member_ `const FTransform AudioDrivenAnimationViewportTransform = FTransform(FRotator(0, 90, 0), FVector(40.0, 0.0, 0.0));` — Rotation and push back needed so things appear correctly in the viewport

#### Free symbols / members of external scopes

- L103 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProcessingFinishedDynamic);`
- L125 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataInputTypeChanged, EDataInputType InProcessingType);`
- L126 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSourceDataChanged, class UFootageCaptureData* InFootageCaptureData, class USoundWave* InAudio, bool InResetRanges);`
- L127 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIdentityChanged, class UMetaHumanIdentity* InIdentity);`
- L128 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisualizeMeshChanged, class USkeletalMesh* InVisualizeMesh);`
- L129 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisualizeObjectChanged, class UObject* InVisualizeObject);`
- L130 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSkeletonParamsChanged);`
- L131 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnDepthChanged, float InDepthDataNear, float InDepthDataFar, float InDepthMeshNear, float InDepthMeshFar);`
- L132 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFrameRangeChanged, int32 InStartFrame, int32 InEndFrame);`
- L133 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRealtimeAudioChanged, bool bInRealtimeAudio);`
- L134 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFrameProcessed, int32 InFrame);`
- L135 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessingFinished, TSharedPtr<const UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L136 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStage1ProcessingFinished);`
- L137 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageProcessingFinished, int32 InCurrentStage);`
- L138 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControlRigClassChanged, TSubclassOf<class UControlRig> InControlRigClass);`
- L139 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControlRigAssetReferenceChanged, const FControlRigAssetStrongReference& InControlRigAssetReference);`
- L140 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHeadMovementModeChanged, EPerformanceHeadMovementMode InHeadMovementMode);`
- L141 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHeadMovementReferenceFrameChanged, bool bInAutoChooseHeadMovementReferenceFrame, uint32 InHeadMovementReferenceFrame);`
- L142 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNeutralPoseCalibrationChanged);`
- L143 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnExcludedFramesChanged);`
- L144 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBodyTrackerModeChanged, EMetaHumanBodyTrackerMode InBodyTrackerMode);`
- L145 _delegate_ `DECLARE_DELEGATE_RetVal(USkeletalMesh*, FOnGetHeadMesh);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanPerformance/Public/MetaHumanPerformanceExportUtils.h` (Public)


#### enum `EPerformanceExportRange`  
`enum class EPerformanceExportRange : uint8`  
_L20-24_
- reflection: `UENUM()`
- L22 _public enumerator_ `ProcessingRange UMETA(DisplayName = "Processing Range")`
- L23 _public enumerator_ `WholeSequence UMETA(DisplayName = "Whole Sequence")`

#### enum `EPerformanceExportSkeleton`  
`enum class EPerformanceExportSkeleton`  
_L27-32_
- reflection: `UENUM()`
- L29 _public enumerator_ `PerformerSkeleton UMETA(DisplayName = "Performer Skeleton", Tooltip = "Output a copy of the skeleton the body was solved against, preserving the performer's proportions")`
- L30 _public enumerator_ `ExistingSkeleton UMETA(DisplayName = "Existing Skeleton", Tooltip = "Retarget onto a user-selected target skeleton via IK retargeting")`
- L31 _public enumerator_ `Raw UMETA(Hidden, DisplayName = "Raw")`

#### enum `EBodyUnsolvedFrameBehavior`  
`enum class EBodyUnsolvedFrameBehavior : uint8`  
_L36-42_
- reflection: `UENUM()`
- desc: How to handle frames without solved body data during Animation Sequence export.
- L39 _public enumerator_ `LastValidFrame UMETA(DisplayName = "Last Valid Frame")` — Repeat the most recent successfully solved frame's bone transforms.
- L41 _public enumerator_ `NeutralPose UMETA(DisplayName = "Neutral Pose")` — Use the skeleton's reference pose.

#### class `UMetaHumanPerformanceExportAnimationSettings`  
`class UMetaHumanPerformanceExportAnimationSettings : public UObject`  
_L48-167_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L55 _public function_ `UMetaHumanPerformanceExportAnimationSettings() : bEnableHeadMovement(true) , bShowExportDialog(true) , bAutoSaveAnimSequence(true) , bFortniteCompatibility(true) , ExportRange(EPerformanceExportRange::WholeSequence) , bExportFace(true) , bRemoveRedundantCurveKeys(true)`
- L67 _public member_ `uint8 bEnableHeadMovement : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Whether or not to enable the Head Movement in the exported Animation Sequence, default to true if head pose available
- L71 _public member_ `uint8 bShowExportDialog : 1;` — `UPROPERTY(BlueprintReadWrite, Category = "Export Settings")` — Whether or not to show the export dialog allowing the user to select where to place the animation sequence, default to true
- L75 _public member_ `uint8 bAutoSaveAnimSequence : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Whether or not to auto save the generated animation sequence, default to true
- L80 _public member_ `uint8 bFortniteCompatibility : 1;` — `UPROPERTY()` — Whether or not to set the metadata tags required to make the generated animation sequence compatible with Fortnite characters, default to true Currently this parameter is not exposed but could be in future.
- L84 _public member_ `EPerformanceExportRange ExportRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — The export range that will be used to generate the animation sequence, defaults to EPerformanceExportRange::WholeSequence
- L90 _public member_ `uint8 bExportFace : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (EditCondition = "IsBodyTrackerEnabled()", EditConditionHides))` — Whether to export face animation (blendshape curves) into the animation sequence. Disabled when the performance does not contain face animation data.
- L96 _public member_ `uint8 bExportBody : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (EditCondition = "IsBodyTrackerEnabled()", EditConditionHides))` — Whether to export body animation (bone tracks) into the animation sequence. Disabled when the performance does not contain body animation data.
- L101 _public member_ `EPerformanceExportSkeleton ExportSkeleton = EPerformanceExportSkeleton::PerformerSkeleton;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (EditCondition = "IsBodyTrackerEnabled() && bExportBody", EditConditionHides))` — Which skeleton the body animation is baked onto.
- L106 _public member_ `TObjectPtr<UObject> TargetSkeletonOrSkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (AllowedClasses = "/Script/Engine.Skeleton, /Script/Engine.SkeletalMesh", GetAssetFilter = "ShouldFilterTargetAsset", EditCondition = "(bExportFace && !bExportBody) || (bExportBody && ExportSkeleton == EPerformanceExportSkeleton::ExistingSkeleton)", EditConditionHides))` — The Skeleton or Skeletal Mesh to be used when recording the Animation Sequence
- L111 _public member_ `TObjectPtr<class UIKRetargeter> BodyRetargeter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (EditCondition = "bExportBody && ExportSkeleton == EPerformanceExportSkeleton::ExistingSkeleton", EditConditionHides))` — The retargeter to use when exporting body anim onto an existing skeleton
- L118 _public member_ `EBodyUnsolvedFrameBehavior BodyUnsolvedBehavior = EBodyUnsolvedFrameBehavior::LastValidFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (DisplayName = "Unsolved Frame Behavior", EditCondition = "IsBodyTrackerEnabled() && bExportBody", EditConditionHides))` — How to handle frames without solved body data during export (excluded, unprocessed, dropped). Hold Last Frame repeats the most recent solved frame; Reference Pose uses the skeleton rest pose. Leading unsolved frames (before the first solved frame) always use Reference Pose.
- L122 _public member_ `TEnumAsByte<ERichCurveInterpMode> CurveInterpolation = ERichCurveInterpMode::RCIM_Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — This defines how values between keys are calculated for curves
- L127 _public member_ `uint8 bRemoveRedundantCurveKeys : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (ScriptName = "remove_redundant_curve_keys;remove_redundant_keys"))` — Whether or not to remove redundant curve keys, default to true
- L131 _public member_ `FString AssetName;` — `UPROPERTY(BlueprintReadWrite, Category = "Asset Placement")` — The name of the level sequence. If bShowExportDialog is true the user will be able to select this value
- L135 _public member_ `FString PackagePath;` — `UPROPERTY(BlueprintReadWrite, Category = "Asset Placement")` — The package path where the animation sequence will be placed, if bShowExportDialog is true this option is ignored
- L140 _public member_ `TObjectPtr<class USkeletalMesh> SourceSkeletalMesh;` — `UPROPERTY(Transient)` — The source skeletal mesh the body animation was solved against (populated by the body tracker actor). Required for body export; set automatically by the editor toolkit.Scripted callers must set it manually.
- L145 _public member_ `TObjectPtr<class USkeletalMesh> SMPLSourceSkeletalMesh;` — `UPROPERTY(Transient)` — The SMPL skeletal mesh the raw body animation was solved against (populated by the body tracker actor). Required for SMPL body export; set automatically by the editor toolkit.Scripted callers must set it manually.
- L151 _public prototype_ `USkeleton* GetTargetSkeleton() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Compatibility")` — Returns the target Skeleton derived from TargetSkeletonOrSkeletalMesh
- L158 _public prototype_ `bool IsTargetSkeletonCompatible(const TSet<FString>& InCurves, TArray<FString>& OutMissingCurvesInSkeleton) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Compatibility")` — Checks if the Target Skeleton set in TargetSkeletonOrSkeletalMesh may have compatibility issues. The compatibility test will check if the the skeleton has all the requested curves and will return the missing curves in OutMissingCurvesInSkeleton.
- L161 _public prototype_ `bool IsBodyTrackerEnabled() const;` — `UFUNCTION()`
- L165 _public prototype_ `bool ShouldFilterTargetAsset(const FAssetData& InAssetData) const;` — `UFUNCTION()` — Asset picker filter for TargetSkeletonOrSkeletalMesh. When exporting body, only Skeletal Meshes are valid targets.

#### class `UMetaHumanPerformanceExportLevelSequenceSettings`  
`class UMetaHumanPerformanceExportLevelSequenceSettings : public UObject`  
_L173-284_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L180 _public function_ `UMetaHumanPerformanceExportLevelSequenceSettings() : bShowExportDialog(true) , bExportVideoTrack(true) , bExportDepthTrack(false) , bExportAudioTrack(true) , bExportImagePlane(true) , bExportDepthMesh(false) , bExportCamera(true) , bApplyLensDistortion(false) , bMatchCameraAspectRatioToOriginalFootage(false) , bExportIdentity(true) , bExportControlRigTrack(true) , bEnableControlRigHeadMovement(true) , bExportTransformTrack(true) , bKeepFrameRange(true) , bEnableMetaHumanHeadMovement(true) , bRemoveRedundantKeys(true)`
- L202 _public member_ `FString PackagePath;` — `UPROPERTY(BlueprintReadWrite, Category = "Asset Placement")` — The package path where the level sequence will be placed. If bShowExportDialog is true the user will be able to able to select this value
- L206 _public member_ `FString AssetName;` — `UPROPERTY(BlueprintReadWrite, Category = "Asset Placement")` — The name of the level sequence. If bShowExportDialog is true the user will be able to select this value
- L210 _public member_ `uint8 bShowExportDialog : 1;` — `UPROPERTY(BlueprintReadWrite, Category = "Export Settings")` — Whether or not to display to display a dialog to the user where the export options and path can be selected. Default to true
- L214 _public member_ `uint8 bExportVideoTrack : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media Tracks")` — Whether or not to export the video track. Default to true
- L218 _public member_ `uint8 bExportDepthTrack : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media Tracks")` — Whether or not to export the depth track, default to false
- L222 _public member_ `uint8 bExportAudioTrack : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media Tracks")` — Whether or not to export the audio track, default to true
- L226 _public member_ `uint8 bExportImagePlane : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (EditCondition = "bExportVideoTrack"))` — Whether or not to export the image plane. Ignored if bExportVideoTrack is false. Default to true
- L230 _public member_ `uint8 bExportDepthMesh : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (EditCondition = "bExportDepthTrack"))` — Whether or not to export the depth mesh. Ignored if bExportDepthTrack is false. Default to false
- L234 _public member_ `uint8 bExportCamera : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Whether or not to export a camera that matches the one used in the Performance. Default to true
- L238 _public member_ `uint8 bApplyLensDistortion : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (EditCondition = "bExportCamera"))` — Whether or not camera lens distortion should be applied to exported camera
- L242 _public member_ `uint8 bMatchCameraAspectRatioToOriginalFootage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings", meta = (EditCondition = "bExportCamera"))` — Whether or not to use the aspect ratio of the original camera footage for the exported camera. Default to false
- L246 _public member_ `uint8 bExportIdentity : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Export MetaHuman Identity", Category = "MetaHuman Identity Tracks")` — Whether or not export the Identity mesh. Default to true
- L250 _public member_ `uint8 bExportControlRigTrack : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman Identity Tracks", meta = (EditCondition = "bExportIdentity"))` — Whether or not to export the Control Rig track with baked data. Default to true
- L254 _public member_ `uint8 bEnableControlRigHeadMovement : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman Identity Tracks", meta = (EditCondition = "bExportIdentity && bExportControlRigTrack"))` — Whether or not to enable Head Movement using Control Rig.
- L258 _public member_ `uint8 bExportTransformTrack : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman Identity Tracks", meta = (EditCondition = "bExportIdentity"))` — Whether or not to bake the animation data into the rigid transform track for the Identity actor. Default to true
- L262 _public member_ `uint8 bKeepFrameRange : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Range", meta = (EditCondition = "ExportRange == EPerformanceExportRange::ProcessingRange", DisplayAfter = "ExportRange"))` — Whether or not to keep the frame range defined by the Processing Range. Disabling this will force the Level Sequence tracks to start at frame 0
- L267 _public member_ `uint8 bEnableMetaHumanHeadMovement : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman Tracks", DisplayName = "Enable MetaHuman Head Movement", meta = (EditCondition = "TargetMetaHumanClass != nullptr", DisplayAfter = "TargetMetaHumanClass"))` — Whether or not to enable the head movement switch in the Target MetaHuman
- L271 _public member_ `TObjectPtr<class UBlueprint> TargetMetaHumanClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman Tracks", DisplayName = "Target MetaHuman Class")` — Optional MetaHuman created as a spawnable in the exported Level Sequence
- L275 _public member_ `EPerformanceExportRange ExportRange = EPerformanceExportRange::WholeSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Range")` — The export range that will be used to generate the Level Sequence, defaults to EPerformanceExportRange::WholeSequence
- L279 _public member_ `TEnumAsByte<ERichCurveInterpMode> CurveInterpolation = ERichCurveInterpMode::RCIM_Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — This defines how values between keys are calculated for curves
- L283 _public member_ `uint8 bRemoveRedundantKeys : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Export Settings")` — Whether or not to remove redundant keys, default to true

#### class `UMetaHumanPerformanceExportUtils`  
`class UMetaHumanPerformanceExportUtils : public UObject`  
_L293-364_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Utility functions to export data from a Performance
- L302 _public prototype_ `static UMetaHumanPerformanceExportAnimationSettings* GetExportAnimationSequenceSettings(const class UMetaHumanPerformance* InPerformance);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export Settings")` — Returns a UMetaHumanPerformanceExportAnimationSettings configured based on the given Performance
- L306 _public prototype_ `static UMetaHumanPerformanceExportLevelSequenceSettings* GetExportLevelSequenceSettings(const class UMetaHumanPerformance* InPerformance);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export Settings")` — Returns a UMetaHumanPerformanceExportLevelSequenceSettings configured based on the given Performance
- L310 _public prototype_ `static class UAnimSequence* ExportAnimationSequence(class UMetaHumanPerformance* InPerformance, UMetaHumanPerformanceExportAnimationSettings* InExportSettings = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")` — Exports an animation sequence from a Performance using the given settings
- L314 _public prototype_ `static class ULevelSequence* ExportLevelSequence(class UMetaHumanPerformance* InPerformance, UMetaHumanPerformanceExportLevelSequenceSettings* InExportSettings = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")` — Exports a Level Sequence from a Performance using the given settings object
- L317 _public prototype_ `static void BakeControlRigAnimationData(class UMetaHumanPerformance* InPerformance, class UMovieSceneSequence* InSequence, int32 InFrameNumber, class UMovieSceneControlRigParameterSection* InControlRigSection, const FTransform& InReferenceFrameRootPose, ERichCurveInterpMode InCurveInterpolation = RCIM_Constant, class UControlRig* InRecordControlRig = nullptr, const FVector& InVisualizeMeshHeightOffset = FVector::ZeroVector);` — Bake Control Rig animation data of a particular frame from a Performance in the given Control Rig section
- L320 _public prototype_ `static void BakeTransformAnimationData(class UMetaHumanPerformance* InPerformance, class UMovieSceneSequence* InSequence, int32 InFrameNumber, class UMovieScene3DTransformSection* InTransformSection, ERichCurveInterpMode InCurveInterpolation = RCIM_Constant, const FTransform& InOffsetTransform = FTransform::Identity, const FVector& InVisualizeMeshHeightOffset = FVector::ZeroVector);` — Bake Transform animation data of a particular frame from a Performance in the given 3D Transform section
- L323 _public prototype_ `static void SetHeadControlSwitchEnabled(class UMovieSceneControlRigParameterTrack* InControlRigTrack, bool bInEnableHeadControl);` — Enables or disables the HeadControlSwitch in the given control rig track
- L325 _public prototype_ `static bool CanExportFaceAnimation(const class UMetaHumanPerformance* InPerformance);`
- L326 _public prototype_ `static bool CanExportBodyAnimation(const class UMetaHumanPerformance* InPerformance);`
- L327 _public prototype_ `static bool CanExportHeadMovement(const class UMetaHumanPerformance* InPerformance);`
- L328 _public prototype_ `static bool CanExportVideoTrack(const class UMetaHumanPerformance* InPerformance);`
- L329 _public prototype_ `static bool CanExportDepthTrack(const class UMetaHumanPerformance* InPerformance);`
- L330 _public prototype_ `static bool CanExportAudioTrack(const class UMetaHumanPerformance* InPerformance);`
- L331 _public prototype_ `static bool CanExportIdentity(const class UMetaHumanPerformance* InPerformance);`
- L332 _public prototype_ `static bool CanExportLensDistortion(const class UMetaHumanPerformance* InPerformance);`
- L335 _public prototype_ `static bool GetBoneGlobalTransform(const class USkeleton* InSkeleton, const FName& InBoneName, FTransform& OutTransform);` — Calculates the global transform of a bone in a given reference skeleton. Returns false if the requested bone was not found in the Skeleton
- L340 _private prototype_ `static void RecordControlRigKeys(class UMovieSceneControlRigParameterSection* InSection, FFrameNumber InFrameNumber, class UControlRig* InControlRig, ERichCurveInterpMode InCurveInterpolation = RCIM_Constant);` — Function used to record the given ControlRig controls in the section for the given frame number
- L343 _private prototype_ `static bool RecordAnimationSequence(const TArray<UObject*>& InNewAssets, class UMetaHumanPerformance* InPerformance, UMetaHumanPerformanceExportAnimationSettings* InExportSettings);` — Function used to record the animation sequence once the new Animation Sequence asset is created
- L345 _private prototype_ `static void PromptBodyCompatibilitySkeleton(USkeleton* InBodySkeleton);`
- L360 _private prototype_ `static void BakeControlRigTrack(const FBakeControlRigTrackParams& InParams);` — Internal helper function to bake the Animation data from a MetaHuman Performance into a Control Rig Track
- L363 _private prototype_ `static bool ApplyNeutralPoseCalibration(const UMetaHumanPerformance* InPerformance, const int32 InFrameNumber, FFrameAnimationData& InOutAnimationFrame);` — Apply neutral pose calibration

#### struct `UMetaHumanPerformanceExportUtils::FBakeControlRigTrackParams`  
`struct FBakeControlRigTrackParams`  
_L347-357_
- L349 _public member_ `class UMetaHumanPerformance* Performance = nullptr;`
- L350 _public member_ `class UMetaHumanPerformanceExportLevelSequenceSettings* ExportSettings = nullptr;`
- L351 _public member_ `TRange<FFrameNumber> ProcessingRange;`
- L352 _public member_ `ULevelSequence* LevelSequence = nullptr;`
- L353 _public member_ `UClass* ControlRigClass = nullptr;`
- L354 _public member_ `FGuid Binding;`
- L355 _public member_ `UObject* ObjectToBind = nullptr;`
- L356 _public member_ `bool bEnableHeadMovementSwitch = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METAHUMANPERFORMANCE_API`
