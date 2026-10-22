# Plugins / TemplateSequenceEditor

- module root: `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor`
- headers: 17; symbols: 148
- symbol kinds: class=17, function=11, member=19, prototype=98, struct=2, typedef=1
- PrivateDependencyModuleNames: AssetDefinition, BlueprintGraph, CinematicCamera, Core, CoreUObject, EditorFramework, Engine, InputCore, Kismet, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneTools, MovieSceneTracks, Sequencer, SequencerCore, Slate, SlateCore, TemplateSequence, TimeManagement, UnrealEd

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/AssetTools/AssetDefinition_CameraAnimationSequence.h` (Private)


#### class `UAssetDefinition_CameraAnimationSequence`  
`class UAssetDefinition_CameraAnimationSequence : public UAssetDefinition_TemplateSequence`  
_L14-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_TemplateSequence`
- L20 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L26 _protected prototype_ `virtual void InitializeToolkitParams(FTemplateSequenceToolkitParams& ToolkitParams) const override;`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/AssetTools/AssetDefinition_TemplateSequence.h` (Private)


#### class `UAssetDefinition_TemplateSequence`  
`class UAssetDefinition_TemplateSequence : public UAssetDefinitionDefault`  
_L13-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L27 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L28 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L33 _protected function_ `virtual void InitializeToolkitParams(FTemplateSequenceToolkitParams& ToolkitParams) const`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Customizations/CameraAnimationSequenceCustomization.h` (Private)


#### class `FCameraAnimationSequenceCustomization`  
`class FCameraAnimationSequenceCustomization : public FTemplateSequenceCustomizationBase`  
_L15-34_
- inherits: `FTemplateSequenceCustomizationBase`
- desc: The sequencer customization for camera animation sequences.
- L18 _private prototype_ `virtual void RegisterSequencerCustomization(FSequencerCustomizationBuilder& Builder) override;`
- L19 _private prototype_ `virtual void UnregisterSequencerCustomization() override;`
- L21 _private prototype_ `void ExtendViewMenu(FMenuBuilder& MenuBuilder);`
- L22 _private prototype_ `void ExtendToolbar(FToolBarBuilder& ToolbarBuilder);`
- L24 _private prototype_ `TSharedRef<SWidget> GetBoundCameraClassMenuContent();`
- L25 _private prototype_ `bool IsBoundToActorClass(UClass* InClass);`
- L27 _private prototype_ `void ToggleCameraInitiallyAdditiveToViewport();`
- L28 _private prototype_ `bool IsCameraInitiallyAdditiveToViewport();`
- L30 _private prototype_ `void SetCameraAdditiveToViewportOffset();`
- L31 _private prototype_ `bool CanSetCameraAdditiveToViewportOffset();`
- L33 _private member_ `TArray<UClass*> CameraActorClasses;`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Customizations/TemplateSequenceCustomization.h` (Private)


#### class `FTemplateSequenceCustomization`  
`class FTemplateSequenceCustomization : public FTemplateSequenceCustomizationBase`  
_L16-29_
- inherits: `FTemplateSequenceCustomizationBase`
- desc: The sequencer customization for template sequences.
- L19 _private prototype_ `virtual void RegisterSequencerCustomization(FSequencerCustomizationBuilder& Builder) override;`
- L20 _private prototype_ `virtual void UnregisterSequencerCustomization() override;`
- L22 _private prototype_ `void ExtendSequencerToolbar(FToolBarBuilder& ToolbarBuilder);`
- L24 _private prototype_ `bool OnSequencerReceivedDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, FReply& OutReply);`
- L25 _private prototype_ `ESequencerDropResult OnSequencerAssetsDrop(const TArray<UObject*>& Assets, const FAssetDragDropOp& DragDropOp);`
- L26 _private prototype_ `ESequencerDropResult OnSequencerClassesDrop(const TArray<TWeakObjectPtr<UClass>>& Classes, const FClassDragDropOp& DragDropOp);`
- L27 _private prototype_ `ESequencerDropResult OnSequencerActorsDrop(const TArray<TWeakObjectPtr<AActor>>& Actors, const FActorDragDropOp& DragDropOp);`
- L28 _private prototype_ `TSharedRef<SWidget> GetBoundActorClassMenuContent();`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Customizations/TemplateSequenceCustomizationBase.h` (Private)


#### class `FTemplateSequenceCustomizationBase`  
`class FTemplateSequenceCustomizationBase : public ISequencerCustomization`  
_L17-42_
- inherits: `ISequencerCustomization`
- desc: Base implementation of a template sequence customization for Sequencer.
- L20 _protected prototype_ `virtual void RegisterSequencerCustomization(FSequencerCustomizationBuilder& Builder) override;`
- L21 _protected prototype_ `virtual void UnregisterSequencerCustomization() override;`
- L23 _protected prototype_ `UClass* GetBoundActorClass() const;`
- L24 _protected prototype_ `FText GetBoundActorClassName() const;`
- L25 _protected prototype_ `void OnBoundActorClassPicked(UClass* ChosenClass);`
- L26 _protected prototype_ `void ChangeActorBinding(UObject* Object, UActorFactory* ActorFactory = nullptr, bool bSetupDefaults = true);`
- L28 _protected function_ `TSharedPtr<ISequencer> GetSequencer() const`
- L29 _protected function_ `UTemplateSequence* GetTemplateSequence() const`
- L31 _protected prototype_ `TSharedPtr<FExtender> CreateObjectBindingContextMenuExtender(UE::Sequencer::FViewModelPtr InViewModel);`
- L32 _protected prototype_ `void ExtendObjectBindingContextMenu(FMenuBuilder& MenuBuilder, TSharedPtr<UE::Sequencer::FObjectBindingModel> ObjectBindingModel);`
- L35 _private prototype_ `ESequencerPasteSupport OnPaste();`
- L36 _private prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType ChangeType);`
- L37 _private prototype_ `void OnSequencerClosed(TSharedRef<ISequencer> InSequencer);`
- L39 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L41 _private member_ `UTemplateSequence* TemplateSequence;`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Factories/CameraAnimationSequenceFactoryNew.h` (Private)


#### class `UCameraAnimationSequenceFactoryNew`  
`class UCameraAnimationSequenceFactoryNew : public UFactory`  
_L12-20_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Implements a factory for UCameraAnimationSequence objects.
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L19 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Factories/TemplateSequenceFactoryNew.h` (Private)


#### class `UTemplateSequenceFactoryNew`  
`class UTemplateSequenceFactoryNew : public UFactory`  
_L14-26_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Implements a factory for UTemplateSequence objects.
- L19 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L20 _private prototype_ `virtual bool ConfigureProperties() override;`
- L21 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L25 _private member_ `TSubclassOf<UObject> BoundActorClass;` — `UPROPERTY(EditAnywhere, Category=TemplateSequenceFactory)` — The root object binding class of the created template sequence.

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Factories/TemplateSequenceFactoryUtil.h` (Private)


#### class `FTemplateSequenceFactoryUtil`  
`class FTemplateSequenceFactoryUtil`  
_L16-27_
- desc: Utility class for template sequence factories
- L21 _public prototype_ `static UTemplateSequence* CreateTemplateSequence(UObject* InParent, FName InName, EObjectFlags Flags, TSubclassOf<UTemplateSequence> InSequenceClass, TSubclassOf<UObject> InObjectTemplateClass);` — Create a new template sequence
- L26 _private prototype_ `static void InitializeSpawnable(UMovieSceneSequence* InTemplateSequence, TSubclassOf<UObject> InObjectTemplateClass);` — Create a new spawnable for the chosen root object class.

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Misc/MovieSceneSequenceEditor_TemplateSequence.h` (Private)


#### struct `FMovieSceneSequenceEditor_TemplateSequence`  
`struct FMovieSceneSequenceEditor_TemplateSequence : FMovieSceneSequenceEditor`  
_L7-9_
- inherits: `FMovieSceneSequenceEditor`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Misc/TemplateSequenceEditorPlaybackContext.h` (Private)


#### class `FTemplateSequenceEditorPlaybackContext`  
`class FTemplateSequenceEditorPlaybackContext : public TSharedFromThis<FTemplateSequenceEditorPlaybackContext>`  
_L12-24_
- inherits: `TSharedFromThis<FTemplateSequenceEditorPlaybackContext>`
- desc: Class that manages the current UWorld context that a level-sequence editor should use for playback
- L16 _public prototype_ `UObject* GetPlaybackContext() const;`
- L20 _private prototype_ `static UWorld* ComputePlaybackContext();`
- L23 _private member_ `mutable TWeakObjectPtr<UWorld> WeakCurrentContext;` — Mutable cached context pointer

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Misc/TemplateSequenceEditorSettings.h` (Private)


#### class `UTemplateSequenceEditorSettings`  
`class UTemplateSequenceEditorSettings : public UObject`  
_L11-27_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Template Sequence Editor settings.
- L18 _public prototype_ `UTemplateSequenceEditorSettings(const FObjectInitializer& ObjectInitializer);`
- L22 _public member_ `bool bShowOutdatedAssetsInCameraAnimationTrackEditor = false;` — `UPROPERTY(config)` — Whether to show "outdated assets" by default in the camera animation track's asset picker.
- L26 _public member_ `bool bCameraInitiallyAdditiveToViewport = true;` — `UPROPERTY(config)` — Whether to set the viewport position as the initial value for additive camera sections.

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Misc/TemplateSequenceEditorSpawnRegister.h` (Private)


#### class `FTemplateSequenceEditorSpawnRegister`  
`class FTemplateSequenceEditorSpawnRegister : public FLevelSequenceEditorSpawnRegister`  
_L8-13_
- inherits: `FLevelSequenceEditorSpawnRegister`
- desc: Movie scene spawn register that knows how to handle spawning objects (actors) for a template sequence
- L11 _private prototype_ `virtual bool CanConvertSpawnableToPossessable(FMovieSceneSpawnable& Spawnable) const override;`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Misc/TemplateSequenceEditorUtil.h` (Private)


#### class `FTemplateSequenceEditorUtil`  
`class FTemplateSequenceEditorUtil`  
_L12-25_
- L15 _public prototype_ `FTemplateSequenceEditorUtil(UTemplateSequence* InTemplateSequence, ISequencer& InSequencer);`
- L17 _public prototype_ `void ChangeActorBinding(UObject* Object, UActorFactory* ActorFactory = nullptr, bool bSetupDefaults = true);`
- L21 _private member_ `UTemplateSequence* TemplateSequence;` — Template sequence to operate upon.
- L24 _private member_ `ISequencer& Sequencer;` — The sequencer currently editing the sequence.

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Styles/TemplateSequenceEditorStyle.h` (Private)


#### class `FTemplateSequenceEditorStyle`  
`class FTemplateSequenceEditorStyle final : public FSlateStyleSet`  
_L10-22_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the template sequence editor.
- L14 _public prototype_ `FTemplateSequenceEditorStyle();`
- L15 _public prototype_ `virtual ~FTemplateSequenceEditorStyle();`
- L17 _public prototype_ `static TSharedRef<FTemplateSequenceEditorStyle> Get();`
- L21 _private member_ `static TSharedPtr<FTemplateSequenceEditorStyle> Singleton;`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Systems/TemplateSequenceCameraPreviewSystem.h` (Private)


#### class `UTemplateSequenceCameraPreviewSystem`  
`class UTemplateSequenceCameraPreviewSystem : public UMovieSceneEntitySystem`  
_L15-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: A sequencer system that can write the current editor viewport transform into the initial values of the camera object's transform entities.
- L21 _public prototype_ `UTemplateSequenceCameraPreviewSystem(const FObjectInitializer& ObjInit);`
- L24 _public prototype_ `static void EnableNextFrame();` — Update the root camera's initial transform to the current editor viewport transform.
- L26 _public prototype_ `static void DisableNextFrame();` — Revert the root camera's initial transform to the origin.
- L30 _protected prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L31 _protected prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L35 _private member_ `static bool bEnableNextFrame;`
- L36 _private member_ `static bool bDisableNextFrame;`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/TemplateSequenceEditorToolkit.h` (Private)


#### struct `FTemplateSequenceToolkitParams`  
`struct FTemplateSequenceToolkitParams`  
_L17-20_
- L19 _public member_ `bool bCanChangeBinding = true;`

#### class `FTemplateSequenceEditorToolkit`  
`class FTemplateSequenceEditorToolkit : public FAssetEditorToolkit, public FGCObject`  
_L25-107_
- inherits: `FAssetEditorToolkit,FGCObject`
- desc: Implements an Editor toolkit for template sequences.
- L34 _public prototype_ `FTemplateSequenceEditorToolkit(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L37 _public prototype_ `virtual ~FTemplateSequenceEditorToolkit();` — Virtual destructor
- L49 _public prototype_ `void Initialize(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UTemplateSequence* TemplateSequence, const FTemplateSequenceToolkitParams& ToolkitParams);` — Initialize this asset editor. @param Mode Asset editing mode for this editor (standalone or world-centric). @param InitToolkitHost When Mode is WorldCentric, this is the level editor instance to spawn this editor within. @param TemplateSequence The animation to edit. @param TrackEditorDelegates Delegates to call to create auto-key handlers for this sequencer.
- L54 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L58 _public function_ `virtual FString GetReferencerName() const override`
- L63 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L64 _public prototype_ `virtual bool CanFindInContentBrowser() const override;`
- L69 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L70 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L71 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L72 _public prototype_ `virtual FText GetTabSuffix() const override;`
- L73 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L74 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L75 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L79 _private prototype_ `TSharedRef<FExtender> HandleMenuExtensibilityGetExtender(const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects);`
- L80 _private prototype_ `void HandleTrackMenuExtensionAddTrack(FMenuBuilder& AddTrackMenuBuilder, TArray<UObject*> ContextObjects);`
- L81 _private prototype_ `void HandleAddComponentActionExecute(UActorComponent* Component);`
- L83 _private prototype_ `void HandleActorAddedToSequencer(AActor* Actor, const FGuid Binding);`
- L85 _private prototype_ `void HandleMapChanged(class UWorld* NewWorld, EMapChangeType MapChangeType);`
- L87 _private prototype_ `void OnSequencerReceivedFocus();`
- L92 _private member_ `TObjectPtr<UTemplateSequence> TemplateSequence;` — Template sequence for our edit operation.
- L95 _private member_ `TSharedPtr<ISequencer> Sequencer;` — The sequencer used by this editor.
- L98 _private member_ `TSharedRef<ISlateStyle> Style;` — Pointer to the style set to use for toolkits.
- L101 _private member_ `FDelegateHandle SequencerExtenderHandle;` — Handle to the sequencer properties menu extender.
- L103 _private member_ `TSharedPtr<FTemplateSequenceEditorPlaybackContext> PlaybackContext;`
- L106 _private member_ `static const FName SequencerMainTabId;` — The tab ids for all the tabs used

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/TrackEditors/TemplateSequenceTrackEditor.h` (Private)


#### class `FTemplateSequenceTrackEditor`  
`class FTemplateSequenceTrackEditor : public FMovieSceneTrackEditor`  
_L18-51_
- inherits: `FMovieSceneTrackEditor`
- L21 _public prototype_ `FTemplateSequenceTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L23 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L27 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L28 _public prototype_ `virtual bool SupportsType(TSubclassOf<class UMovieSceneTrack> TrackClass) const override;`
- L29 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L30 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L31 _public prototype_ `TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L32 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L33 _public prototype_ `virtual bool IsResizable(UMovieSceneTrack* InTrack) const override;`
- L34 _public prototype_ `virtual void Resize(float NewSize, UMovieSceneTrack* InTrack) override;`
- L37 _private prototype_ `void AddTemplateSequenceAssetSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, const UClass* RootBindingClass);`
- L38 _private prototype_ `TSharedRef<SWidget> BuildTemplateSequenceAssetSubMenu(FGuid ObjectBinding, const UClass* RootBindingClass);`
- L40 _private prototype_ `void OnTemplateSequenceAssetSelected(const FAssetData& AssetData, TArray<FGuid> ObjectBindings);`
- L41 _private prototype_ `void OnTemplateSequenceAssetEnterPressed(const TArray<FAssetData>& AssetData, TArray<FGuid> ObjectBindings);`
- L43 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, FGuid ObjectBinding, UTemplateSequence* TemplateSequence);`
- L44 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, TArray<FGuid> ObjectBindings, UTemplateSequence* TemplateSequence);`
- L46 _private prototype_ `bool CanAddSubSequence(const UMovieSceneSequence& Sequence) const;`
- L47 _private prototype_ `const UClass* AcquireObjectClassFromObjectGuid(const FGuid& Guid);`
- L48 _private prototype_ `UCameraComponent* AcquireCameraComponentFromObjectGuid(const FGuid& Guid);`

#### class `FTemplateSequenceSection`  
`class FTemplateSequenceSection : public TSubSectionMixin<> , public TSharedFromThis<FTemplateSequenceSection>`  
_L53-72_
- inherits: `TSubSectionMixin<>,TSharedFromThis<FTemplateSequenceSection>`
- L58 _public prototype_ `FTemplateSequenceSection(TSharedPtr<ISequencer> InSequencer, UTemplateSequenceSection& InSection);`
- L59 _public prototype_ `virtual ~FTemplateSequenceSection() = default;`
- L61 _public prototype_ `virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;`
- L62 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L66 _private prototype_ `void BuildPropertyScalingSubMenu(FMenuBuilder& MenuBuilder, FGuid ObjectBinding);`
- L68 _private typedef_ `typedef TTuple<FGuid, FMovieScenePropertyBinding, ETemplateSectionPropertyScaleType> FScalablePropertyInfo;`
- L69 _private prototype_ `TArray<FScalablePropertyInfo> GetAnimatedProperties() const;`
- L70 _private prototype_ `int32 GetPropertyScaleFor(const FScalablePropertyInfo& AnimatedProperty) const;`
- L71 _private prototype_ `FText GetAnimatedPropertyScaleTypeSuffix(const FScalablePropertyInfo& AnimatedProperty) const;`
