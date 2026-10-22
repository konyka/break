# Plugins / ContextualAnimationEditor

- module root: `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor`
- headers: 24; symbols: 450
- symbol kinds: class=26, enum=4, enumerator=11, function=52, member=101, namespace=1, prototype=249, struct=6
- PrivateDependencyModuleNames: AdvancedPreviewScene, AnimGraph, AssetTools, BlueprintGraph, ClassViewer, CoreUObject, DetailCustomizations, EditorFramework, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, KismetWidgets, LevelEditor, MovieScene, MovieSceneTools, MovieSceneTracks, Persona, Projects, PropertyEditor, RenderCore, Sequencer, SequencerCore, SequencerWidgets, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: AIModule, ContextualAnimation, Core, GameplayTags, MotionWarping, NavigationSystem

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimAssetEditorCommands.h` (Public)


#### class `FContextualAnimAssetEditorCommands`  
`class FContextualAnimAssetEditorCommands : public TCommands<FContextualAnimAssetEditorCommands>`  
_L8-37_
- inherits: `TCommands<FContextualAnimAssetEditorCommands>`
- L11 _public function_ `FContextualAnimAssetEditorCommands() : TCommands<FContextualAnimAssetEditorCommands>(TEXT("ContextualAnimAssetEditor"), NSLOCTEXT("Contexts", "ContextualAnim", "Contextual Anim"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ResetPreviewScene;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> NewAnimSet;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ShowIKTargetsDrawSelected;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ShowIKTargetsDrawAll;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ShowIKTargetsDrawNone;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ShowSelectionCriteriaActiveSet;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ShowSelectionCriteriaAllSets;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ShowSelectionCriteriaNone;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ShowEntryPosesActiveSet;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ShowEntryPosesAllSets;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ShowEntryPosesNone;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> Simulate;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimAssetEditorToolkit.h` (Public)


#### class `FContextualAnimAssetEditorToolkit`  
`class FContextualAnimAssetEditorToolkit : public FAssetEditorToolkit`  
_L18-70_
- inherits: `FAssetEditorToolkit`
- L22 _public prototype_ `FContextualAnimAssetEditorToolkit();`
- L23 _public prototype_ `virtual ~FContextualAnimAssetEditorToolkit();`
- L25 _public prototype_ `void InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UContextualAnimSceneAsset* SceneAsset);`
- L27 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L28 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L29 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L30 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L31 _public prototype_ `virtual FText GetToolkitName() const override;`
- L32 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L33 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L35 _public prototype_ `UContextualAnimSceneAsset* GetSceneAsset() const;`
- L36 _public function_ `FContextualAnimViewModel* GetViewModel() const`
- L38 _public prototype_ `void ResetPreviewScene();`
- L39 _public prototype_ `void ToggleSimulateMode();`
- L40 _public prototype_ `bool IsSimulateModeActive() const;`
- L45 _private prototype_ `bool CanMakeEdits() const;`
- L47 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L48 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetDetails(const FSpawnTabArgs& Args);`
- L49 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Timeline(const FSpawnTabArgs& Args);`
- L50 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetBrowser(const FSpawnTabArgs& Args);`
- L51 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& Args);`
- L53 _private prototype_ `void BindCommands();`
- L54 _private prototype_ `void ExtendToolbar();`
- L55 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L57 _private prototype_ `TSharedRef<SWidget> BuildSectionsMenu();`
- L58 _private prototype_ `TSharedRef<SWidget> BuildAnimSetMenu();`
- L60 _private prototype_ `void ShowNewAnimSetDialog();`
- L61 _private prototype_ `void AddAnimSetToActiveSection();`
- L63 _private member_ `TSharedPtr<SContextualAnimViewport> ViewportWidget;`
- L65 _private member_ `TSharedPtr<SContextualAnimAssetBrowser> AssetBrowserWidget;`
- L67 _private member_ `TSharedPtr<FContextualAnimPreviewScene> PreviewScene;`
- L69 _private member_ `TSharedPtr<FContextualAnimViewModel> ViewModel;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimEdMode.h` (Public)


#### struct `HSelectionCriterionHitProxy`  
`struct HSelectionCriterionHitProxy : public HHitProxy`  
_L12-28_
- inherits: `HHitProxy`
- L14 _public prototype_ `DECLARE_HIT_PROXY();`
- L16 _public function_ `HSelectionCriterionHitProxy(FName InRole, int32 InCriterionIdx, int32 InDataIdx, EHitProxyPriority InPriority = HPP_Wireframe) : HHitProxy(InPriority)`
- L24 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L26 _public member_ `FName Role = NAME_None;`
- L27 _public member_ `TPair<int32, int32> IndexPair;`

#### class `FContextualAnimEdMode`  
`class FContextualAnimEdMode : public FEdMode`  
_L30-60_
- inherits: `FEdMode`
- L34 _public member_ `const static FEditorModeID EdModeId;`
- L36 _public prototype_ `FContextualAnimEdMode();`
- L37 _public prototype_ `virtual ~FContextualAnimEdMode();`
- L39 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L40 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);`
- L41 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L42 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L43 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L44 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L45 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L46 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L47 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L48 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L49 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L50 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData);`
- L51 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData);`
- L53 _public prototype_ `bool GetHitResultUnderCursor(FHitResult& OutHitResult, FEditorViewportClient* InViewportClient, const FViewportClick& Click) const;`
- L55 _public prototype_ `void DrawIKTargetsForBinding(class FPrimitiveDrawInterface& PDI, const struct FContextualAnimSceneBinding& Binding) const;`
- L59 _private member_ `FContextualAnimViewModel* ViewModel = nullptr;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimEditorStyle.h` (Public)


#### class `FContextualAnimEditorStyle`  
`class FContextualAnimEditorStyle`  
_L9-30_
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L21 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the Shooter game
- L23 _public prototype_ `static FName GetStyleSetName();`
- L27 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L29 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimEditorTypes.h` (Public)


#### class `UContextualAnimNewIKTargetParams`  
`class UContextualAnimNewIKTargetParams : public UObject, public IBoneReferenceSkeletonProvider`  
_L15-64_
- reflection: `UCLASS()`
- inherits: `UObject,IBoneReferenceSkeletonProvider`
- desc: Object used to construct the New IK Target Widget
- L22 _public member_ `FName SourceRole = NAME_None;` — `UPROPERTY(VisibleAnywhere, Category = "Settings")`
- L25 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L28 _public member_ `EContextualAnimIKTargetProvider Provider = EContextualAnimIKTargetProvider::Autogenerated;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L31 _public member_ `FName TargetRole = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (GetOptions = "GetTargetRoleOptions"))`
- L34 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L37 _public member_ `FName GoalName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L40 _public member_ `int32 SectionIdx = INDEX_NONE;` — `UPROPERTY()`
- L42 _public function_ `UContextualAnimNewIKTargetParams(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L45 _public prototype_ `virtual USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle = nullptr) override;`
- L47 _public prototype_ `void Reset(const UContextualAnimSceneAsset& InSceneAsset, const UAnimSequenceBase& InAnimation);`
- L49 _public prototype_ `bool HasValidData() const;`
- L51 _public prototype_ `const UContextualAnimSceneAsset& GetSceneAsset() const;`
- L52 _public function_ `int32 GetSectionIdx() const`
- L55 _public prototype_ `TArray<FString> GetTargetRoleOptions() const;` — `UFUNCTION()`
- L60 _private member_ `TWeakObjectPtr<const UContextualAnimSceneAsset> SceneAssetPtr;` — `UPROPERTY()`
- L63 _private member_ `TArray<FName> CachedRoles;` — `UPROPERTY()`

#### struct `FContextualAnimNewAnimSetData`  
`struct FContextualAnimNewAnimSetData`  
_L67-87_
- reflection: `USTRUCT()`
- L72 _public member_ `FName RoleName = NAME_None;` — `UPROPERTY(VisibleAnywhere, Category = "Settings")`
- L75 _public member_ `TObjectPtr<class UAnimMontage> Animation = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L81 _public member_ `uint8 CustomMovementMode = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditConditionHides, EditCondition = "MovementMode==EMovementMode::MOVE_Custom"))`
- L84 _public member_ `bool bOptional = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")`

#### struct `FContextualAnimNewAnimSetParams`  
`struct FContextualAnimNewAnimSetParams`  
_L91-103_
- reflection: `USTRUCT()`
- desc: Struct used to construct the widget for adding a new set
- L96 _public member_ `FName SectionName = NAME_Default;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L99 _public member_ `TArray<FContextualAnimNewAnimSetData> Data;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Settings", meta = (TitleProperty = "RoleName"))`
- L102 _public member_ `float RandomWeight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimFactory.h` (Public)


#### class `UContextualAnimFactory`  
`class UContextualAnimFactory : public UFactory`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `UContextualAnimFactory(const FObjectInitializer& ObjectInitializer);`
- L17 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L18 _public prototype_ `virtual bool CanCreateNew() const override;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimMovieSceneNotifySection.h` (Public)


#### class `UContextualAnimMovieSceneNotifySection`  
`class UContextualAnimMovieSceneNotifySection : public UMovieSceneSection`  
_L17-47_
- reflection: `UCLASS()`
- inherits: `UMovieSceneSection`
- desc: MovieSceneSection used to represent an AnimNotify in Sequencer Panel Stores the FGuid of the AnimNotifyEvent this section is presenting
- L27 _public prototype_ `void Initialize(const FAnimNotifyEvent& NotifyEvent);` — Initialize this section from the supplied FAnimNotifyEvent. Sets the range of the section to match the range of the anim notify and cache the FGuid
- L30 _public function_ `const FGuid& GetAnimNotifyEventGuid() const` — Returns the track owner of this section
- L33 _public prototype_ `UContextualAnimMovieSceneNotifyTrack* GetOwnerTrack() const;` — Returns the track owner of this section
- L36 _public prototype_ `UAnimNotifyState* GetAnimNotifyState() const;` — Returns the actual AnimNotifyState this section is representing
- L39 _public prototype_ `FAnimNotifyEvent* GetAnimNotifyEvent() const;` — Returns the actual AnimNotifyEvent this section is representing
- L45 _private member_ `FGuid AnimNotifyEventGuid;` — `UPROPERTY()` — Guid of the actual AnimNotifyEvent this section is representing

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimMovieSceneNotifyTrack.h` (Public)


#### class `UContextualAnimMovieSceneNotifyTrack`  
`class UContextualAnimMovieSceneNotifyTrack : public UMovieSceneNameableTrack`  
_L18-75_
- reflection: `UCLASS()`
- inherits: `UMovieSceneNameableTrack`
- desc: MovieSceneTrack used to show the notifies in the animation the track was created from in Sequencer Panel
- L24 _public prototype_ `FContextualAnimViewModel& GetViewModel() const;`
- L30 _public prototype_ `void Initialize(UAnimSequenceBase& AnimationRef, const FAnimNotifyTrack& NotifyTrack);` — Initialize this track from a supplied animation and a notify track Adding all the FAnimNotifyEvents as sections in here and setting
- L33 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;` — Creates a new section for this track
- L36 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;` — Adds a new section to this track
- L39 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — Returns whether this track supports the supplied section class
- L42 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;` — Returns the list of all the sections in this track
- L45 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;` — Returns whether this track contains the supplied section
- L48 _public prototype_ `virtual bool IsEmpty() const override;` — Returns whether this track is empty (doesn't have any section in it)
- L51 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;` — Called when the supplied section is removed from Sequencer. Removes the actual Notify the section is representing
- L54 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;` — Called when a section at the supplied index is removed from Sequencer. Removes the actual Notify the section is representing
- L58 _public prototype_ `virtual EMovieSceneSectionMovedResult OnSectionMoved(UMovieSceneSection& Section, const FMovieSceneSectionMovedParams& Params) override;` — Called when a section in this track is moved. Updates the actual Notify the section is representing
- L61 _public function_ `virtual bool SupportsMultipleRows() const override`
- L64 _public prototype_ `UAnimSequenceBase& GetAnimation() const;` — Returns a reference to the animation this track was created from
- L70 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — List of sections in this track
- L74 _private member_ `TWeakObjectPtr<UAnimSequenceBase> Animation;` — `UPROPERTY()` — Ptr to the animation this track was created from

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimMovieSceneNotifyTrackEditor.h` (Public)


#### class `FContextualAnimMovieSceneNotifyTrackEditor`  
`class FContextualAnimMovieSceneNotifyTrackEditor : public FMovieSceneTrackEditor, public FGCObject`  
_L22-62_
- inherits: `FMovieSceneTrackEditor,FGCObject`
- desc: Handles section drawing and manipulation of a MovieSceneNotifyTrack
- L26 _public prototype_ `FContextualAnimMovieSceneNotifyTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L29 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L30 _public function_ `virtual FString GetReferencerName() const override`
- L33 _public prototype_ `virtual void OnInitialize() override;`
- L34 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L35 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L36 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L38 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L39 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L41 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L43 _public prototype_ `UContextualAnimMovieSceneSequence& GetMovieSceneSequence() const;`
- L47 _private member_ `TObjectPtr<UContextualAnimNewIKTargetParams> NewIKTargetParams;`
- L49 _private prototype_ `UContextualAnimMovieSceneNotifySection* CreateNewSection(UContextualAnimMovieSceneNotifyTrack* Track, int32 RowIndex, UClass* NotifyClass);`
- L51 _private prototype_ `UContextualAnimMovieSceneNotifySection* CreateNewIKSection(UContextualAnimMovieSceneNotifyTrack* Track, int32 RowIndex, const FName& GoalName);`
- L53 _private prototype_ `void BuildNewIKTargetSubMenu(FMenuBuilder& MenuBuilder, UContextualAnimMovieSceneNotifyTrack* Track, int32 RowIndex);`
- L55 _private prototype_ `void BuildNewIKTargetWidget(FMenuBuilder& MenuBuilder, UContextualAnimMovieSceneNotifyTrack* Track, int32 RowIndex);`
- L57 _private prototype_ `void AddNewNotifyTrack();`
- L59 _private prototype_ `void FillNewNotifyMenu(FMenuBuilder& MenuBuilder, bool bIsAnimNotifyState, UContextualAnimMovieSceneNotifyTrack* Track, int32 RowIndex);`
- L61 _private prototype_ `void CustomizeToolBar(FToolBarBuilder& ToolBarBuilder);`

#### class `FContextualAnimNotifySection`  
`class FContextualAnimNotifySection : public FSequencerSection`  
_L68-83_
- inherits: `FSequencerSection`
- desc: UI portion of a NotifySection in a NotifyTrack
- L72 _public function_ `FContextualAnimNotifySection(UMovieSceneSection& InSectionObject) : FSequencerSection(InSectionObject)`
- L76 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L77 _public prototype_ `virtual bool SectionIsResizable() const override;`
- L79 _public prototype_ `UContextualAnimMovieSceneNotifySection* GetNotifySection() const;`
- L80 _public prototype_ `FString GetNotifyName() const;`
- L82 _public prototype_ `static void PaintNotifyName(FSequencerSectionPainter& Painter, int32 LayerId, const FString& InEventString, float PixelPos, bool bIsEventValid);`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimMovieSceneSection.h` (Public)


#### class `UContextualAnimMovieSceneSection`  
`class UContextualAnimMovieSceneSection : public UMovieSceneSection`  
_L12-44_
- reflection: `UCLASS()`
- inherits: `UMovieSceneSection`
- L18 _public prototype_ `void Initialize(int32 InSectionIdx, int32 InAnimSetIdx, int32 InAnimTrackIdx, int32 InSegmentIdx = INDEX_NONE);`
- L21 _public prototype_ `UContextualAnimMovieSceneTrack& GetOwnerTrack() const;` — Returns the track owner of this section
- L23 _public prototype_ `FContextualAnimTrack& GetAnimTrack() const;`
- L25 _public function_ `FORCEINLINE int32 GetSectionIdx() const`
- L26 _public function_ `FORCEINLINE int32 GetAnimSetIdx() const`
- L27 _public function_ `FORCEINLINE int32 GetAnimTrackIdx() const`
- L28 _public function_ `FORCEINLINE int32 GetSegmentIdx() const`
- L33 _private member_ `int32 SectionIdx = INDEX_NONE;` — `UPROPERTY()`
- L36 _private member_ `int32 AnimSetIdx = INDEX_NONE;` — `UPROPERTY()`
- L39 _private member_ `int32 AnimTrackIdx = INDEX_NONE;` — `UPROPERTY()`
- L43 _private member_ `int32 SegmentIdx = INDEX_NONE;` — `UPROPERTY()` — Index into the computed timeline segments (INDEX_NONE for single-section mode)

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimMovieSceneSequence.h` (Public)


#### class `UContextualAnimMovieSceneSequence`  
`class UContextualAnimMovieSceneSequence : public UMovieSceneSequence`  
_L13-43_
- reflection: `UCLASS()`
- inherits: `UMovieSceneSequence`
- L19 _public prototype_ `UContextualAnimMovieSceneSequence(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `void Initialize(const TSharedRef<FContextualAnimViewModel>& ViewModelRef);`
- L23 _public prototype_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;`
- L24 _public prototype_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;`
- L25 _public prototype_ `virtual void LocateBoundObjects(const FGuid& ObjectId, UObject* Context, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L26 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L27 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L28 _public prototype_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;`
- L29 _public prototype_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* Context) override;`
- L30 _public prototype_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* Context) override;`
- L31 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L33 _public function_ `FContextualAnimViewModel& GetViewModel() const`
- L39 _private member_ `TMap<FGuid, TWeakObjectPtr<AActor>> BoundActors;` — `UPROPERTY()` — @TODO: Remove this and use the actors from the PreviewSceneManager
- L42 _private member_ `TWeakPtr<FContextualAnimViewModel> ViewModelPtr;` — Pointer to the view model that owns this sequence.

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimMovieSceneTrack.h` (Public)


#### class `UContextualAnimMovieSceneTrack`  
`class UContextualAnimMovieSceneTrack : public UMovieSceneNameableTrack`  
_L14-72_
- reflection: `UCLASS()`
- inherits: `UMovieSceneNameableTrack`
- L20 _public prototype_ `UContextualAnimMovieSceneTrack();`
- L22 _public prototype_ `void Initialize(const FName& InRole);`
- L24 _public function_ `FORCEINLINE FName GetRole() const`
- L26 _public prototype_ `FContextualAnimViewModel& GetViewModel() const;`
- L29 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;` — Creates a new section for this track
- L32 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;` — Adds a new section to this track
- L35 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — Returns whether this track supports the supplied section class
- L38 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;` — Returns the list of all the sections in this track
- L41 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;` — Returns whether this track contains the supplied section
- L44 _public prototype_ `virtual bool IsEmpty() const override;` — Returns whether this track is empty (doesn't have any section in it)
- L47 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;` — Called when the supplied section is removed from Sequencer. Removes the actual Notify the section is representing
- L50 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;` — Called when a section at the supplied index is removed from Sequencer. Removes the actual Notify the section is representing
- L54 _public prototype_ `virtual EMovieSceneSectionMovedResult OnSectionMoved(UMovieSceneSection& Section, const FMovieSceneSectionMovedParams& Params) override;` — Called when a section in this track is moved. Updates the actual Notify the section is representing
- L56 _public prototype_ `virtual FSlateColor GetLabelColor(const FMovieSceneLabelParams& LabelParams) const override;`
- L57 _public prototype_ `virtual FText GetDisplayNameToolTipText(const FMovieSceneLabelParams& LabelParams) const override;`
- L61 _public function_ `virtual bool SupportsMultipleRows() const override`
- L67 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — List of sections in this track
- L71 _private member_ `FName Role = NAME_None;` — `UPROPERTY()` — Role this track represents

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimMovieSceneTrackEditor.h` (Public)


#### class `FContextualAnimMovieSceneTrackEditor`  
`class FContextualAnimMovieSceneTrackEditor : public FMovieSceneTrackEditor`  
_L11-27_
- inherits: `FMovieSceneTrackEditor`
- desc: Handles section drawing and manipulation of a ContextualAnimMovieSceneTrack
- L15 _public prototype_ `FContextualAnimMovieSceneTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L18 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L19 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L20 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L21 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L22 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L23 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L24 _public function_ `virtual bool GetDefaultExpansionState(UMovieSceneTrack* InTrack) const override`
- L26 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);`

#### class `FContextualAnimSection`  
`class FContextualAnimSection : public FSequencerSection`  
_L33-46_
- inherits: `FSequencerSection`
- desc: UI portion of a NotifySection in a NotifyTrack
- L37 _public function_ `FContextualAnimSection(UMovieSceneSection& InSectionObject) : FSequencerSection(InSectionObject)`
- L41 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& InPainter) const override;`
- L42 _public prototype_ `virtual FReply OnSectionDoubleClicked(const FGeometry& SectionGeometry, const FPointerEvent& MouseEvent) override;`
- L43 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L44 _public prototype_ `virtual float GetSectionHeight() const override;`
- L45 _public function_ `virtual bool SectionIsResizable() const override`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimPreviewScene.h` (Public)


#### class `FContextualAnimPreviewScene`  
`class FContextualAnimPreviewScene : public FAdvancedPreviewScene`  
_L9-24_
- inherits: `FAdvancedPreviewScene`
- L13 _public prototype_ `FContextualAnimPreviewScene(ConstructionValues CVS, const TSharedRef<FContextualAnimAssetEditorToolkit>& EditorToolkit);`
- L14 _public prototype_ `~FContextualAnimPreviewScene()= default;`
- L16 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L18 _public function_ `TSharedRef<FContextualAnimAssetEditorToolkit> GetEditorToolkit() const`
- L23 _private member_ `TWeakPtr<FContextualAnimAssetEditorToolkit> EditorToolkitPtr;` — The asset editor toolkit we are embedded in

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimTypeActions.h` (Public)


#### class `FContextualAnimTypeActions`  
`class FContextualAnimTypeActions : public FAssetTypeActions_Base`  
_L7-17_
- inherits: `FAssetTypeActions_Base`
- L11 _public function_ `FContextualAnimTypeActions()`
- L12 _public prototype_ `virtual FText GetName() const override;`
- L13 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L14 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L15 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L16 _public prototype_ `virtual uint32 GetCategories() override;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimViewModel.h` (Public)


#### struct `FPreviewTimelineSegment`  
`struct FPreviewTimelineSegment`  
_L35-42_
- desc: Represents a single segment in the flattened multi-section preview timeline
- L37 _public member_ `int32 SectionIdx;` — Index into SceneAsset->Sections
- L38 _public member_ `int32 AnimSetIdx;` — Which anim set to use for this segment
- L39 _public member_ `int32 LoopIteration;` — 0-based loop iteration counter
- L40 _public member_ `float GlobalStartTime;` — Start time in the flattened timeline
- L41 _public member_ `float Duration;` — Max animation length across all tracks in this anim set

#### class `FContextualAnimViewModel`  
`class FContextualAnimViewModel : public TSharedFromThis<FContextualAnimViewModel>, public FGCObject, public FSelfRegisteringEditorUndoClient`  
_L44-281_
- inherits: `TSharedFromThis<FContextualAnimViewModel>,FGCObject,FSelfRegisteringEditorUndoClient`
- L63 _public prototype_ `FContextualAnimViewModel();`
- L64 _public prototype_ `virtual ~FContextualAnimViewModel();`
- L67 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L68 _public function_ `virtual FString GetReferencerName() const override`
- L71 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L72 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L73 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L75 _public prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L77 _public prototype_ `void Initialize(UContextualAnimSceneAsset* InSceneAsset, const TSharedRef<FContextualAnimPreviewScene>& InPreviewScene);`
- L78 _public prototype_ `void Shutdown();`
- L80 _public prototype_ `void SetDefaultMode();`
- L81 _public prototype_ `void SetNotifiesMode(const FContextualAnimTrack& AnimTrack);`
- L82 _public function_ `ETimelineMode GetTimelineMode() const`
- L83 _public function_ `UAnimSequenceBase* GetEditingAnimation() const`
- L84 _public prototype_ `void RefreshPreviewScene();`
- L85 _public prototype_ `void ResetTimeline();`
- L87 _public prototype_ `TSharedPtr<ISequencer> GetSequencer();`
- L88 _public prototype_ `TSharedPtr<FContextualAnimPreviewScene> GetPreviewScene();`
- L89 _public function_ `UMovieScene* GetMovieScene() const`
- L90 _public function_ `UContextualAnimMovieSceneSequence* GetMovieSceneSequence() const`
- L91 _public function_ `UContextualAnimSceneAsset* GetSceneAsset() const`
- L92 _public prototype_ `UContextualAnimMovieSceneTrack* FindTrackByRole(const FName& Role) const;`
- L93 _public function_ `TSharedPtr<IDetailsView> GetDetailsView()`
- L95 _public prototype_ `void AddNewAnimSet(const FContextualAnimNewAnimSetParams& Params);`
- L96 _public prototype_ `void RemoveSection(int32 SectionIdx);`
- L97 _public prototype_ `void RemoveAnimSet(int32 SectionIdx, int32 AnimSetIdx);`
- L99 _public prototype_ `void AddNewIKTarget(const UContextualAnimNewIKTargetParams& Params);`
- L101 _public prototype_ `void AnimationModified(UAnimSequenceBase& Animation);`
- L103 _public prototype_ `void SetActiveSection(int32 SectionIdx);`
- L104 _public prototype_ `int32 GetActiveSection() const;`
- L105 _public prototype_ `void SetActiveAnimSetForSection(int32 SectionIdx, int32 AnimSetIdx);`
- L106 _public prototype_ `int32 GetActiveAnimSetForSection(int32 SectionIdx) const;`
- L109 _public prototype_ `int32 GetDetailsSectionIdx() const;` — Returns the section index from the current selection, or the active section if nothing is selected
- L111 _public prototype_ `int32 GetDetailsAnimSetIdx() const;` — Returns the anim set index from the current selection, or the active anim set if nothing is selected
- L113 _public prototype_ `void StartSimulateMode();`
- L114 _public prototype_ `void StopSimulateMode();`
- L115 _public prototype_ `void ToggleSimulateMode();`
- L116 _public function_ `bool IsSimulateModeInactive() const`
- L117 _public function_ `bool IsSimulateModePaused() const`
- L118 _public function_ `bool IsSimulateModePlaying() const`
- L119 _public prototype_ `void StartSimulation();`
- L122 _public prototype_ `void TickSimulateMode(float DeltaTime);` — Called from FContextualAnimEdMode::Tick to poll montage state during multi-section simulate mode
- L125 _public prototype_ `bool TryBuildMultiSectionPreviewTimelineData();` — Attempts to build the flattened multi-section preview timeline from the asset's PreviewSequence entries. Returns true if segments were created.
- L128 _public prototype_ `bool ResolveGlobalTime(float GlobalTime, int32& OutSectionIdx, int32& OutAnimSetIdx, float& OutLocalTime, int32& OutSegmentIdx) const;` — Maps a global timeline position to section-local coordinates. Returns false if GlobalTime is out of range.
- L131 _public function_ `bool HasMultiSectionPreviewTimelineData() const` — Returns true if the multi-section preview timeline is active (has segments)
- L134 _public prototype_ `void TransitionPreviewToSegment(int32 SegmentIdx);` — Transitions preview to a different segment during scrubbing
- L136 _public prototype_ `void UpdatePreviewActorTransform(const FContextualAnimSceneBinding& Binding, float Time);`
- L138 _public prototype_ `void UpdateSelection(const AActor* SelectedActor);`
- L139 _public prototype_ `void UpdateSelection(FName Role, int32 CriterionIdx = INDEX_NONE, int32 CriterionDataIdx = INDEX_NONE);`
- L140 _public prototype_ `void UpdateSelection(int32 SectionIdx, int32 AnimSetIdx, int32 AnimTrackIdx);`
- L141 _public prototype_ `void ClearSelection();`
- L142 _public prototype_ `FContextualAnimSceneBinding* GetSelectedBinding() const;`
- L143 _public prototype_ `FContextualAnimTrack* GetSelectedAnimTrack() const;`
- L144 _public prototype_ `AActor* GetSelectedActor() const;`
- L145 _public prototype_ `class UContextualAnimSelectionCriterion* GetSelectedSelectionCriterion() const;`
- L146 _public prototype_ `FText GetSelectionDebugText() const;`
- L148 _public prototype_ `bool ProcessInputDelta(FVector& InDrag, FRotator& InRot, FVector& InScale);`
- L149 _public prototype_ `bool ShouldPreviewSceneDrawWidget() const;`
- L150 _public prototype_ `bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData);`
- L151 _public prototype_ `FVector GetWidgetLocationFromSelection() const;`
- L152 _public prototype_ `bool StartTracking();`
- L153 _public prototype_ `bool EndTracking();`
- L155 _public prototype_ `float GetPlaybackTime() const;`
- L157 _public prototype_ `bool CanMakeEdits() const;`
- L159 _public prototype_ `void CacheWarpPoints();`
- L160 _public prototype_ `void UpdateRoles();`
- L194 _private member_ `FContextualAnimEdSelectionInfo SelectionInfo;`
- L197 _private member_ `TObjectPtr<UContextualAnimSceneAsset> SceneAsset;` — Scene asset being viewed and edited by this view model.
- L200 _private member_ `TObjectPtr<UContextualAnimMovieSceneSequence> MovieSceneSequence;` — MovieSceneSequence for displaying this scene asset in the sequencer time line.
- L203 _private member_ `TObjectPtr<UMovieScene> MovieScene;` — MovieScene for displaying this scene asset in the sequencer time line.
- L206 _private member_ `TSharedPtr<ISequencer> Sequencer;` — Sequencer instance viewing and editing the scene asset
- L209 _private member_ `TWeakPtr<FContextualAnimPreviewScene> PreviewScenePtr;` — Weak pointer to the PreviewScene
- L212 _private member_ `FContextualAnimSceneBindings SceneBindings;` — Copy of the bindings so we can access them even when simulation mode is not playing (and SceneInstance is not valid)
- L215 _private member_ `int32 ActiveSectionIdx = 0;` — Active section idx
- L218 _private member_ `TMap<int32, int32> ActiveAnimSetMap;` — Active anim set for each section. Key = SectionIdx, Value = AnimSetIdx
- L221 _private member_ `EMovieScenePlayerStatus::Type PreviousSequencerStatus;` — The previous play status for sequencer time line.
- L224 _private member_ `float PreviousSequencerTime = 0.f;` — The previous time for the sequencer time line.
- L227 _private member_ `TArray<FPreviewTimelineSegment> ComputedTimeline;` — Flattened multi-section preview timeline segments
- L230 _private member_ `float TotalSequenceDuration = 0.f;` — Total duration of the flattened preview sequence
- L233 _private member_ `int32 CurrentSegmentIdx = INDEX_NONE;` — Current segment index during scrub/simulate in multi-section mode
- L236 _private member_ `bool bUpdatingAnimationFromSequencer = false;` — Flag for preventing OnAnimNotifyChanged from updating tracks when the change to the animation came from us
- L238 _private member_ `ESimulateModeState SimulateModeState = ESimulateModeState::Inactive;`
- L240 _private member_ `ETimelineMode TimelineMode = ETimelineMode::Default;`
- L242 _private member_ `TWeakObjectPtr<UAnimSequenceBase> EditingAnimation = nullptr;`
- L246 _private member_ `EModifyActorTransformInSceneState ModifyingActorTransformInSceneState = EModifyActorTransformInSceneState::Inactive;`
- L249 _private member_ `TWeakObjectPtr<AActor> ModifyingTransformInSceneCachedActor;` — Selected actor when the user starts modifying its transform in the scene
- L251 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L253 _private prototype_ `AActor* SpawnPreviewActor(const FContextualAnimTrack& AnimTrack);`
- L255 _private prototype_ `UWorld* GetWorld() const;`
- L257 _private prototype_ `UObject* GetPlaybackContext() const;`
- L259 _private prototype_ `void SequencerTimeChanged();`
- L261 _private prototype_ `void SequencerDataChanged(EMovieSceneDataChangeType DataChangeType);`
- L263 _private prototype_ `void SequencerPlayEvent();`
- L265 _private prototype_ `void SequencerStopEvent();`
- L267 _private prototype_ `void OnSequencerSelectionChangedSections(TArray<UMovieSceneSection*> Sections);`
- L269 _private prototype_ `void OnAnimNotifyChanged(UAnimSequenceBase* Animation);`
- L271 _private prototype_ `void CreateSequencer();`
- L273 _private prototype_ `void CreateDetailsView();`
- L275 _private prototype_ `void RefreshDetailsView();`
- L277 _private prototype_ `bool WantsToModifyMeshToSceneForSelectedActor() const;`
- L280 _private member_ `bool bInitialized = false;`

#### enum `FContextualAnimViewModel::ETimelineMode`  
`enum class ETimelineMode : uint8`  
_L50-54_
- L52 _public enumerator_ `Default`
- L53 _public enumerator_ `Notifies`

#### enum `FContextualAnimViewModel::ESimulateModeState`  
`enum class ESimulateModeState : uint8`  
_L56-61_
- L58 _public enumerator_ `Inactive` — Simulate Mode Inactive
- L59 _public enumerator_ `Paused` — Simulate Mode Active but interaction is not playing
- L60 _public enumerator_ `Playing` — Simulate Mode Active and interaction playing

#### struct `FContextualAnimViewModel::FContextualAnimEdSelectionInfo`  
`struct FContextualAnimEdSelectionInfo`  
_L164-193_
- L167 _public member_ `FName Role = NAME_None;` — Selected Role
- L169 _public member_ `int32 SectionIdx = INDEX_NONE;`
- L171 _public member_ `int32 AnimSetIdx = INDEX_NONE;`
- L174 _public member_ `TPair<int32, int32> Criterion;` — Key = Criterion Idx in the AnimTrack, Value = Data idx (e.g vertex idx)
- L177 _public member_ `FGuid NotifyGuid;` — FGuid of the selected AnimNotify
- L179 _public function_ `FContextualAnimEdSelectionInfo()`
- L184 _public function_ `void Reset()`

#### enum `FContextualAnimViewModel::EModifyActorTransformInSceneState`  
`enum class EModifyActorTransformInSceneState : uint8`  
_L245-245_
- desc: Enum to track the current state when modifying the transform of an actor in the scene
- L245 _public enumerator_ `enum class EModifyActorTransformInSceneState : uint8 { Inactive, Modifying, WaitingForConfirmation }; EModifyActorTransformInSceneState ModifyingActorTransformInSceneState = EModifyActorTransformInSceneState::Inactive; TWeakObjectPtr<AActor> ModifyingTransformInSceneCachedActor; TSharedPtr<IDetailsView> DetailsView;` — Enum to track the current state when modifying the transform of an actor in the scene
- L245 _public enumerator_ `enum class EModifyActorTransformInSceneState : uint8 { Inactive, Modifying, WaitingForConfirmation }; EModifyActorTransformInSceneState ModifyingActorTransformInSceneState = EModifyActorTransformInSceneState::Inactive; TWeakObjectPtr<AActor> ModifyingTransformInSceneCachedActor; TSharedPtr<IDetailsView> DetailsView;` — Enum to track the current state when modifying the transform of an actor in the scene
- L245 _public enumerator_ `enum class EModifyActorTransformInSceneState : uint8 { Inactive, Modifying, WaitingForConfirmation }; EModifyActorTransformInSceneState ModifyingActorTransformInSceneState = EModifyActorTransformInSceneState::Inactive; TWeakObjectPtr<AActor> ModifyingTransformInSceneCachedActor; TSharedPtr<IDetailsView> DetailsView;` — Enum to track the current state when modifying the transform of an actor in the scene

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EMovieScenePlayerStatus`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimViewportClient.h` (Public)


#### enum `EMultiOptionDrawMode`  
`enum class EMultiOptionDrawMode : uint8`  
_L11-16_
- L13 _public enumerator_ `None`
- L14 _public enumerator_ `Single`
- L15 _public enumerator_ `All`

#### class `FContextualAnimViewportClient`  
`class FContextualAnimViewportClient : public FEditorViewportClient`  
_L18-61_
- inherits: `FEditorViewportClient`
- L22 _public prototype_ `FContextualAnimViewportClient(const TSharedRef<FContextualAnimPreviewScene>& InPreviewScene, const TSharedRef<SContextualAnimViewport>& InViewport, const TSharedRef<FContextualAnimAssetEditorToolkit>& InAssetEditorToolkit);`
- L23 _public prototype_ `virtual ~FContextualAnimViewportClient()= default;`
- L26 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L27 _public prototype_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;`
- L28 _public prototype_ `virtual void TrackingStopped() override;`
- L32 _public function_ `TSharedRef<FContextualAnimPreviewScene> GetPreviewScene() const` — Get the preview scene we are viewing
- L34 _public function_ `TSharedRef<FContextualAnimAssetEditorToolkit> GetAssetEditorToolkit() const`
- L36 _public function_ `void SetIKTargetsDrawMode(EMultiOptionDrawMode Mode)`
- L37 _public function_ `bool IsIKTargetsDrawModeSet(EMultiOptionDrawMode Mode) const`
- L38 _public function_ `EMultiOptionDrawMode GetIKTargetsDrawMode() const`
- L40 _public function_ `void SetSelectionCriteriaDrawMode(EMultiOptionDrawMode Mode)`
- L41 _public function_ `bool IsSelectionCriteriaDrawModeSet(EMultiOptionDrawMode Mode) const`
- L42 _public function_ `EMultiOptionDrawMode GetSelectionCriteriaDrawMode() const`
- L44 _public function_ `void SetEntryPosesDrawMode(EMultiOptionDrawMode Mode)`
- L45 _public function_ `bool IsEntryPosesDrawModeSet(EMultiOptionDrawMode Mode) const`
- L46 _public function_ `EMultiOptionDrawMode GetEntryPosesDrawMode() const`
- L51 _private member_ `TWeakPtr<FContextualAnimPreviewScene> PreviewScenePtr;` — Preview scene we are viewing
- L54 _private member_ `TWeakPtr<FContextualAnimAssetEditorToolkit> AssetEditorToolkitPtr;` — Asset editor toolkit we are embedded in
- L56 _private member_ `EMultiOptionDrawMode IKTargetsDrawMode = EMultiOptionDrawMode::None;`
- L58 _private member_ `EMultiOptionDrawMode SelectionCriteriaDrawMode = EMultiOptionDrawMode::All;`
- L60 _private member_ `EMultiOptionDrawMode EntryPosesDrawMode = EMultiOptionDrawMode::All;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/ContextualAnimationEditor.h` (Public)


#### class `FContextualAnimationEditorModule`  
`class FContextualAnimationEditorModule : public IModuleInterface`  
_L11-26_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `static FContextualAnimationEditorModule& Get();`
- L23 _private member_ `FDelegateHandle MovieSceneAnimNotifyTrackEditorHandle;`
- L25 _private member_ `TSharedPtr<IAssetTypeActions> ContextualAnimAssetActions;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/DetailCustomizations/ContextualAnimNotifySectionDetailCustom.h` (Public)


#### class `FContextualAnimNotifySectionDetailCustom`  
`class FContextualAnimNotifySectionDetailCustom : public IDetailCustomization`  
_L13-24_
- inherits: `IDetailCustomization`
- desc: Detail Customization for ContextualAnimMovieSceneNotifySection
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L23 _protected member_ `TWeakObjectPtr<UContextualAnimMovieSceneNotifySection> Section;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/DetailCustomizations/ContextualAnimSceneAssetDetailCustom.h` (Public)


#### class `FContextualAnimSceneAssetDetailCustom`  
`class FContextualAnimSceneAssetDetailCustom : public IDetailCustomization`  
_L12-25_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedRef<FContextualAnimViewModel> ViewModelRef);`
- L18 _public prototype_ `FContextualAnimSceneAssetDetailCustom(TSharedRef<FContextualAnimViewModel> ViewModelRef);`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _protected member_ `TWeakPtr<FContextualAnimViewModel> ViewModelPtr;`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/SContextualAnimAssetBrowser.h` (Public)


#### class `SContextualAnimAssetBrowser`  
`class SContextualAnimAssetBrowser : public SBox`  
_L9-24_
- inherits: `SBox`
- L13 _public function_ `SLATE_BEGIN_ARGS(SContextualAnimAssetBrowser)`
- L14 _public prototype_ `SLATE_END_ARGS();`
- L16 _public prototype_ `void Construct(const FArguments& InArgs);`
- L17 _public prototype_ `virtual ~SContextualAnimAssetBrowser()= default;`
- L21 _private member_ `TSharedPtr<SBox> AssetBrowserBox;`
- L22 _private prototype_ `void OnAssetDoubleClicked(const FAssetData& AssetData);`
- L23 _private prototype_ `bool OnShouldFilterAsset(const FAssetData& AssetData);`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/SContextualAnimNewAnimSetDialog.h` (Public)


#### class `SContextualAnimNewAnimSetDialog`  
`class SContextualAnimNewAnimSetDialog : public SWindow`  
_L11-36_
- inherits: `SWindow`
- desc: Dialog for adding a new AnimSet
- L15 _public function_ `SLATE_BEGIN_ARGS(SContextualAnimNewAnimSetDialog)`
- L18 _public function_ `SContextualAnimNewAnimSetDialog() : UserResponse(EAppReturnType::Cancel)`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FContextualAnimViewModel>& InViewModel);`
- L25 _public prototype_ `EAppReturnType::Type Show();`
- L29 _protected member_ `TWeakPtr<FContextualAnimViewModel> WeakViewModel;`
- L31 _protected member_ `EAppReturnType::Type UserResponse;`
- L33 _protected member_ `TSharedPtr<FStructOnScope> WidgetStruct;`
- L35 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/SContextualAnimViewport.h` (Public)


#### struct `FContextualAnimViewportRequiredArgs`  
`struct FContextualAnimViewportRequiredArgs`  
_L13-23_
- L15 _public function_ `FContextualAnimViewportRequiredArgs(const TSharedRef<FContextualAnimAssetEditorToolkit>& InAssetEditorToolkit, const TSharedRef<FContextualAnimPreviewScene>& InPreviewScene) : AssetEditorToolkit(InAssetEditorToolkit) , PreviewScene(InPreviewScene)`
- L20 _public member_ `TSharedRef<FContextualAnimAssetEditorToolkit> AssetEditorToolkit;`
- L22 _public member_ `TSharedRef<FContextualAnimPreviewScene> PreviewScene;`

#### class `SContextualAnimViewport`  
`class SContextualAnimViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L25-62_
- inherits: `SEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L29 _public function_ `SLATE_BEGIN_ARGS(SContextualAnimViewport)`
- L30 _public prototype_ `SLATE_END_ARGS();`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, const FContextualAnimViewportRequiredArgs& InRequiredArgs);`
- L33 _public prototype_ `virtual ~SContextualAnimViewport()= default;`
- L36 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;`
- L37 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L38 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L44 _protected prototype_ `virtual void BindCommands() override;`
- L45 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L46 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L47 _protected prototype_ `virtual const FSlateBrush* OnGetViewportBorderBrush() const override;`
- L48 _protected prototype_ `virtual FSlateColor OnGetViewportBorderColorAndOpacity() const;`
- L52 _protected member_ `TSharedPtr<SContextualAnimViewportToolBar> ViewportToolbar;` — The viewport toolbar
- L55 _protected member_ `TSharedPtr<FContextualAnimViewportClient> ViewportClient;` — Viewport client
- L58 _protected member_ `TWeakPtr<FContextualAnimPreviewScene> PreviewScenePtr;` — The preview scene that we are viewing
- L61 _protected member_ `TWeakPtr<FContextualAnimAssetEditorToolkit> AssetEditorToolkitPtr;` — Asset editor toolkit we are embedded in

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimationEditor/Public/SContextualAnimViewportToolbar.h` (Public)


#### class `SContextualAnimViewportToolBar`  
`class SContextualAnimViewportToolBar : public SCommonEditorViewportToolbarBase`  
_L9-22_
- inherits: `SCommonEditorViewportToolbarBase`
- L12 _public function_ `SLATE_BEGIN_ARGS(SContextualAnimViewportToolBar)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SContextualAnimViewport> InViewport);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> GenerateShowMenu() const override;`
