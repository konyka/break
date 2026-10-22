# Plugins / MovieSceneAnimMixerEditor

- module root: `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor`
- headers: 27; symbols: 636
- symbol kinds: class=32, delegate=2, enum=1, enumerator=3, function=53, member=158, namespace=45, prototype=333, struct=9
- PrivateDependencyModuleNames: AssetRegistry, BlueprintGraph, EditorFramework, EditorInteractiveToolsFramework, Engine, InputCore, LevelEditor, LevelSequence, MovieScene, MovieSceneAnimMixer, MovieSceneTools, MovieSceneTracks, Persona, PropertyEditor, Sequencer, SequencerAnimTools, SequencerCore, SequencerWidgets, Slate, SlateCore, ToolMenus, UAF, UAFEditor, UAFUncookedOnly, UnrealEd
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationCore, Core, CoreUObject, MovieSceneAnimMixer, Sequencer, SequencerCore

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/MovieSceneAnimationMaskDecorationEditor.h` (Other)


#### class `UE::Sequencer::FAnimMixerMaskSection`  
`class FAnimMixerMaskSection : public FSequencerSection`  
_L12-35_
- inherits: `FSequencerSection`
- L16 _public function_ `FAnimMixerMaskSection(UMovieSceneSection& InSection) : FSequencerSection(InSection)`
- L21 _public function_ `virtual FText GetSectionTitle() const override`

#### class `UE::Sequencer::FMovieSceneAnimationMaskDecorationEditor`  
`class FMovieSceneAnimationMaskDecorationEditor : public ISequencerDecorationEditor`  
_L37-45_
- inherits: `ISequencerDecorationEditor`
- L40 _public prototype_ `virtual UClass* GetDecorationClass() const override;`
- L41 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L43 _public prototype_ `virtual TSharedPtr<ISequencerSection> MakeSectionInterface(UMovieSceneSection& Section, UMovieSceneTrack& OwningTrack, FGuid ObjectBinding) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimBusSectionInterface.h` (Private)


#### class `UE::Sequencer::FAnimBusSectionInterface`  
`class FAnimBusSectionInterface : public FSequencerSection , public TSharedFromThis<FAnimBusSectionInterface>`  
_L19-43_
- inherits: `FSequencerSection,TSharedFromThis<FAnimBusSectionInterface>`
- desc: Section interface for bus sections in Animation Mixer tracks. Inherits from FSequencerSection for proper background rendering, and adds bus-specific title and context menu.
- L24 _public prototype_ `FAnimBusSectionInterface(UMovieSceneSection& InSection, UMovieSceneTrack& InTrack, FGuid InObjectBinding, TWeakPtr<ISequencer> InSequencer);`
- L26 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L27 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L28 _public prototype_ `virtual FText GetSectionToolTip() const override;`
- L29 _public function_ `virtual bool SectionIsResizable() const override`
- L30 _public function_ `virtual bool IsDeletable() const override`
- L31 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L34 _private prototype_ `void PopulateChangeBusMenu(FMenuBuilder& MenuBuilder);`
- L35 _private prototype_ `void ChangeBusName(FName NewBusName);`
- L37 _private prototype_ `UMovieSceneAnimBusSection* GetBusSection() const;`
- L38 _private prototype_ `UMovieSceneAnimationMixerTrack* GetMixerTrack() const;`
- L40 _private member_ `TWeakObjectPtr<UMovieSceneTrack> WeakTrack;`
- L41 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L42 _private member_ `FGuid ObjectBindingId;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimBusSectionMenuProvider.h` (Private)


#### class `FAnimBusSectionMenuProvider`  
`class FAnimBusSectionMenuProvider : public IMovieSceneAnimMixerItemMenuProvider`  
_L9-15_
- inherits: `IMovieSceneAnimMixerItemMenuProvider`
- desc: Menu provider for adding bus sections to Animation Mixer layers. Shows a submenu with known bus names plus a "New Bus..." entry.
- L12 _public prototype_ `virtual const UClass* GetHandledMixerItemClass() const override;`
- L13 _public prototype_ `virtual void PopulateAddMixerItemMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TSharedPtr<ISequencer> Sequencer, int32 RowIndex) override;`
- L14 _public function_ `virtual int32 GetMixerItemMenuPriority() const override`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimBusTargetMenuProvider.h` (Private)


#### class `FAnimBusTargetMenuProvider`  
`class FAnimBusTargetMenuProvider : public IMovieSceneAnimMixerTargetMenuProvider`  
_L9-37_
- inherits: `IMovieSceneAnimMixerTargetMenuProvider`
- desc: Target menu provider for the Bus Target type. Shows a submenu with known bus names plus a "New Bus..." entry.
- L12 _public prototype_ `virtual UScriptStruct* GetHandledTargetStructType() const override;`
- L15 _public prototype_ `virtual void PopulateTargetMenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected, TSharedPtr<ISequencer> Sequencer, UMovieSceneAnimationMixerTrack* Track) override;` — Override the 5-param version to use sequencer/track for bus listing and cycle checks
- L23 _public prototype_ `virtual void PopulateTargetMenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected) override;` — 3-param fallback
- L28 _public function_ `virtual int32 GetTargetMenuPriority() const override`
- L31 _private prototype_ `void PopulateBusTargetSubmenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected, TSharedPtr<ISequencer> Sequencer, UMovieSceneAnimationMixerTrack* Track);`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimMixerDecorationMenuProviders.h` (Private)


#### class `FMaskDecorationMenuProvider`  
`class FMaskDecorationMenuProvider : public IMovieSceneDecorationMenuProvider`  
_L12-34_
- inherits: `IMovieSceneDecorationMenuProvider`
- desc: Decoration menu provider for masks (UMovieSceneAnimationMaskDecoration). Adds a "Mask" menu entry that allows the user to select a blend mask asset, which will create a mask section with that asset as its blend mask.
- L17 _public prototype_ `virtual UClass* GetHandledDecorationClass() const override;` — IMovieSceneDecorationMenuProvider
- L18 _public prototype_ `virtual void PopulateAddDecorationMenu(FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, UMovieSceneDecorationContainerObject* DecorationContainer, TWeakPtr<ISequencer> InSequencer) override;`
- L20 _public function_ `virtual int32 GetDecorationMenuPriority() const override` — Masks are high priority.
- L24 _private prototype_ `const USkeleton* FindSkeletonForObject(const TObjectPtr<UObject>& Object);`
- L26 _private prototype_ `void PopulateMaskSubmenu(FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, UMovieSceneDecorationContainerObject* DecorationContainer, TWeakPtr<ISequencer> InSequencer);`
- L28 _private prototype_ `void OnCreateNewBlendMask(UMovieSceneDecorationContainerObject* DecorationContainer, TWeakPtr<ISequencer> WeakSequencer);`
- L30 _private prototype_ `void OnMaskAssetSelected(const FAssetData& AssetData, UMovieSceneDecorationContainerObject* DecorationContainer, TWeakPtr<ISequencer> Sequencer);`
- L32 _private prototype_ `bool FilterBlendMasks(const FAssetData& AssetData, const USkeleton* Skeleton);`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimMixerEditorBusUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AnimMixerEditorBusUtils`
- L17 _prototype_ `TArray<UMovieSceneAnimationMixerTrack*> GatherMixerTracksForSameObject( UMovieSceneAnimationMixerTrack* Track, ISequencer& Sequencer);` (scope `AnimMixerEditorBusUtils`) — Gather all mixer tracks across the sequence hierarchy that are bound to the same object as the given track. Resolves the track's binding through the compiled hierarchy (not just the focused sequence) so this works correctly for tracks in any sub-sequence.
- L22 _prototype_ `TArray<UMovieSceneAnimationMixerTrack*> GatherMixerTracksForBoundObject( UObject* BoundObject, ISequencer& Sequencer);` (scope `AnimMixerEditorBusUtils`) — Gather all mixer tracks bound to the given object across the sequence hierarchy. Use when no track exists yet to resolve a binding from.
- L29 _prototype_ `TArray<FName> GatherBusNamesFromTracks(TArrayView<UMovieSceneAnimationMixerTrack* const> MixerTracks);` (scope `AnimMixerEditorBusUtils`) — Gather the bus names (targets and sections) referenced by the given mixer tracks, sorted. Buses are scoped per bound object, so pass the tracks for a single character (see GatherMixerTracksForSameObject) to get the buses relevant to that character rather than every bus in the sequence.

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimMixerTargetMenuProviders.h` (Private)


#### class `FAutomaticTargetMenuProvider`  
`class FAutomaticTargetMenuProvider : public IMovieSceneAnimMixerTargetMenuProvider`  
_L11-20_
- inherits: `IMovieSceneAnimMixerTargetMenuProvider`
- desc: Target menu provider for the Automatic target type (base FMovieSceneMixedAnimationTarget). Adds a simple "Automatic" menu entry.
- L14 _public prototype_ `virtual UScriptStruct* GetHandledTargetStructType() const override;`
- L15 _public prototype_ `virtual void PopulateTargetMenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected) override;`
- L19 _public function_ `virtual int32 GetTargetMenuPriority() const override`

#### class `FAnimInstanceTargetMenuProvider`  
`class FAnimInstanceTargetMenuProvider : public IMovieSceneAnimMixerTargetMenuProvider`  
_L26-35_
- inherits: `IMovieSceneAnimMixerTargetMenuProvider`
- desc: Target menu provider for the Custom Anim Instance target type. Adds a simple "Custom Anim Instance" menu entry.
- L29 _public prototype_ `virtual UScriptStruct* GetHandledTargetStructType() const override;`
- L30 _public prototype_ `virtual void PopulateTargetMenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected) override;`
- L34 _public function_ `virtual int32 GetTargetMenuPriority() const override`

#### class `FAnimBlueprintTargetMenuProvider`  
`class FAnimBlueprintTargetMenuProvider : public IMovieSceneAnimMixerTargetMenuProvider`  
_L42-57_
- inherits: `IMovieSceneAnimMixerTargetMenuProvider`
- desc: Target menu provider for the Anim Blueprint Target type. Queries the bound object's anim instance for SequencerMixerTarget nodes and creates a submenu with discovered target names, plus the default name.
- L45 _public prototype_ `virtual UScriptStruct* GetHandledTargetStructType() const override;`
- L46 _public prototype_ `virtual void PopulateTargetMenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected) override;`
- L50 _public function_ `virtual int32 GetTargetMenuPriority() const override`
- L53 _private prototype_ `void PopulateAnimBlueprintTargetSubmenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected);`

#### class `FAnimNextInjectionTargetMenuProvider`  
`class FAnimNextInjectionTargetMenuProvider : public IMovieSceneAnimMixerTargetMenuProvider`  
_L64-79_
- inherits: `IMovieSceneAnimMixerTargetMenuProvider`
- desc: Target menu provider for the UAF Module Injection target type. Queries the bound object's AnimNextComponent for injection sites and creates a submenu with discovered injection sites, plus the default one.
- L67 _public prototype_ `virtual UScriptStruct* GetHandledTargetStructType() const override;`
- L68 _public prototype_ `virtual void PopulateTargetMenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected) override;`
- L72 _public function_ `virtual int32 GetTargetMenuPriority() const override`
- L75 _private prototype_ `void PopulateAnimNextTargetSubmenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected);`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimMixerTrailHierarchy.h` (Private)


#### class `UE::Sequencer::FAnimMixerTrailHierarchy`  
`class FAnimMixerTrailHierarchy : public UE::SequencerAnimTools::FTrailHierarchy`  
_L16-83_
- inherits: `UE::SequencerAnimTools::FTrailHierarchy`
- desc: Trail hierarchy for animation mixer root motion trajectory visualization. Manages FMixerRootMotionTrail instances and drives incremental bake evaluation to populate trajectory transforms one bucket per tick.
- L19 _public prototype_ `FAnimMixerTrailHierarchy(TWeakPtr<ISequencer> InWeakSequencer);`
- L22 _public prototype_ `virtual void Initialize() override;` — FTrailHierarchy interface
- L23 _public prototype_ `virtual void Destroy() override;`
- L24 _public prototype_ `virtual UE::SequencerAnimTools::ITrailHierarchyRenderer* GetRenderer() const override;`
- L25 _public prototype_ `virtual FFrameNumber GetFramesPerFrame() const override;`
- L26 _public prototype_ `virtual FFrameNumber GetFramesPerSegment() const override;`
- L27 _public prototype_ `virtual const UE::SequencerAnimTools::FCurrentFramesInfo* GetCurrentFramesInfo() const override;`
- L28 _public prototype_ `virtual bool CheckForChanges() override;`
- L29 _public prototype_ `virtual void Update() override;`
- L30 _public prototype_ `virtual void CalculateEvalRangeArray() override;`
- L31 _public prototype_ `virtual bool IsTrailEvaluating(const FGuid& InTrailGuid, bool bIndirectlyOnly) const override;`
- L32 _public prototype_ `virtual bool IsHitByClick(HHitProxy* HitProxy) override;`
- L34 _public prototype_ `virtual FFrameNumber GetLocalTime() const override;`
- L35 _public function_ `TWeakPtr<ISequencer> GetSequencer() const`
- L39 _public function_ `void SetSuppressChangeDetection(bool bSuppress)` — Set during ApplyDelta to prevent CheckForChanges from invalidating trails while a synchronous re-bake is in progress
- L43 _public prototype_ `void RequestRebakeAll();` — Request a synchronous rebake of all trails on the next Update. Called from the edit mode's InputDelta when root offsets change.
- L47 _public prototype_ `void InvalidateAllTrails();` — Invalidate the cached trajectory data for all trails without rebuilding them. Call on data changes (key edits, section moves) that don't add/remove tracks.
- L50 _public prototype_ `void InvalidateTrailForTrack(UMovieSceneAnimationMixerTrack* MixerTrack);` — Invalidate the cached trajectory data for a specific mixer track's trail.
- L53 _private prototype_ `void UpdateViewAndEvalRange();`
- L54 _private prototype_ `void RebuildTrailsFromSequencer();`
- L55 _private prototype_ `void SyncTrailsWithSequencer();`
- L56 _private prototype_ `void EvaluateAndSetTransforms();`
- L57 _private prototype_ `void SynchronousRebakeIfNeeded();`
- L58 _private prototype_ `void OnSelectionChanged();`
- L60 _private prototype_ `void RegisterPinDelegates();`
- L61 _private prototype_ `void UnregisterPinDelegates();`
- L62 _private prototype_ `void OnPinSelection(ETrailCategory Category);`
- L63 _private prototype_ `void OnUnPinSelection(ETrailCategory Category);`
- L64 _private prototype_ `void OnDeleteAllPinned(ETrailCategory Category);`
- L66 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L69 _private member_ `TMap<TWeakObjectPtr<UMovieSceneAnimationMixerTrack>, FGuid> TrackedMixerTrails;` — Map from mixer track to the trail's GUID in AllTrails
- L72 _private member_ `TSet<FGuid> EvaluatingTrails;` — Trails being incrementally evaluated
- L74 _private member_ `UE::SequencerAnimTools::FCurrentFramesInfo CurrentFramesInfo;`
- L75 _private member_ `TUniquePtr<UE::SequencerAnimTools::FTrailHierarchyRenderer> HierarchyRenderer;`
- L77 _private member_ `FGuid LastMovieSceneGuid;`
- L78 _private member_ `bool bSuppressChangeDetection = false;`
- L79 _private member_ `FDelegateHandle OnViewOptionsChangedHandle;`
- L80 _private member_ `FDelegateHandle OnSelectionChangedObjectGuidsHandle;`
- L81 _private member_ `FDelegateHandle OnSelectionChangedSectionsHandle;`
- L82 _private member_ `FDelegateHandle OnSelectionChangedTracksHandle;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimTransitionSectionInterface.h` (Private)


#### class `UE::Sequencer::FAnimTransitionSectionInterface`  
`class FAnimTransitionSectionInterface : public ISequencerSection , public TSharedFromThis<FAnimTransitionSectionInterface>`  
_L22-70_
- inherits: `ISequencerSection,TSharedFromThis<FAnimTransitionSectionInterface>`
- desc: Section interface for animation mixer transition sections. Provides custom rendering and interaction constraints for transitions.
- L27 _public prototype_ `FAnimTransitionSectionInterface(UMovieSceneSection& InSection, UMovieSceneTrack& InTrack, FGuid InObjectBinding);`
- L30 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L31 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L32 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L33 _public prototype_ `virtual FText GetSectionToolTip() const override;`
- L34 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L35 _public prototype_ `virtual void GenerateSectionLayout(class ISectionLayoutBuilder& LayoutBuilder) override;`
- L36 _public function_ `virtual bool IsReadOnly() const override`
- L37 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L40 _public prototype_ `virtual void BeginResizeSection() override;` — Custom resize behavior: resizing the transition adjusts the from/to sections
- L41 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeFrameNumber) override;`
- L44 _public function_ `virtual bool SectionIsResizable() const override` — Transition sections cannot be resized beyond the from section's start or to section's end
- L47 _public function_ `virtual bool IsDeletable() const override` — Transition sections cannot be explicitly deleted - they are removed automatically when overlap goes away
- L50 _public function_ `virtual bool SupportsOutlinerColumnToggle(FName ColumnName) const override` — Transition sections should not expose mute/solo/lock/deactivate/condition column options
- L53 _public function_ `virtual bool ShouldShowKeyAreaWhenCollapsed() const override` — Transition sections draw their own curve visualization in OnPaintSection, so don't show the key area when collapsed
- L56 _protected prototype_ `UMovieSceneAnimTransitionSectionBase* GetTransitionSection() const;`
- L59 _private prototype_ `void PopulateChangeTypeMenu(FMenuBuilder& MenuBuilder);`
- L60 _private prototype_ `void ChangeTransitionType(UClass* NewTransitionClass);`
- L62 _private member_ `TWeakObjectPtr<UMovieSceneSection> SectionPtr;`
- L63 _private member_ `TWeakObjectPtr<UMovieSceneTrack> TrackPtr;`
- L64 _private member_ `FGuid ObjectBindingId;`
- L67 _private member_ `TRange<FFrameNumber> InitialFromRange;` — Cached state for resize operations
- L68 _private member_ `TRange<FFrameNumber> InitialToRange;`
- L69 _private member_ `TRange<FFrameNumber> InitialTransitionRange;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/AnimationMixerTrackEditMode.h` (Private)


#### struct `HMixerEditModeRootHitProxy`  
`struct HMixerEditModeRootHitProxy : public HHitProxy`  
_L25-37_
- inherits: `HHitProxy`
- desc: Hit proxy for clicking on root bone points rendered by the mixer edit mode
- L27 _public prototype_ `DECLARE_HIT_PROXY();`
- L29 _public member_ `TWeakObjectPtr<UMovieSceneSection> Section;`
- L30 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkelMeshComp;`
- L32 _public function_ `HMixerEditModeRootHitProxy(UMovieSceneSection* InSection, USkeletalMeshComponent* InComp) : HHitProxy(HPP_Foreground) , Section(InSection) , SkelMeshComp(InComp)`

#### struct `UE::Sequencer::FOffsetDragState`  
`struct FOffsetDragState`  
_L46-72_
- desc: Tracks accumulated drag state for offset channel keying. Shared between the edit mode (root control gizmo) and trail key tool (trail gizmo).
- L48 _public member_ `FVector DragStartLocationOffset = FVector::ZeroVector;`
- L49 _public member_ `FRotator DragStartRotationOffset = FRotator::ZeroRotator;`
- L50 _public member_ `FVector AccumulatedLocalDrag = FVector::ZeroVector;`
- L51 _public member_ `FRotator AccumulatedLocalRot = FRotator::ZeroRotator;`
- L53 _public function_ `void Reset()`
- L62 _public prototype_ `void SnapshotFromDecoration(UMovieSceneRootMotionSettingsDecoration* Decoration, FFrameTime Time);` — Snapshot the current offset channel values at a given time
- L68 _public prototype_ `void AccumulateWorldDelta(const FVector& WorldDrag, const FRotator& WorldRot, const FTransform& ComponentTransform, const FQuat& AccumulatedRotation, bool bWorldSpace);` — Accumulate a world-space gizmo delta into the running offset, undoing what the evaluator applies to the offset on its way to world space: the mesh component transform, scale included, in animation space only, then the accumulated/initial-root rotation the offset is keyed relative to. Rotation is authored in world axes for both spaces.
- L70 _public function_ `FVector GetCurrentLocationOffset() const`
- L71 _public function_ `FRotator GetCurrentRotationOffset() const`

#### struct `UE::Sequencer::FMixerSelectedRootData`  
`struct FMixerSelectedRootData`  
_L75-85_
- desc: Tracks which section/mesh/decoration is selected for gizmo interaction
- L77 _public member_ `TWeakObjectPtr<UMovieSceneSection> Section;`
- L78 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> MeshComp;`
- L79 _public member_ `TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration> Decoration;`
- L81 _public function_ `bool operator==(const FMixerSelectedRootData& Other) const`

#### class `UAnimationMixerTrackEditMode`  
`class UAnimationMixerTrackEditMode : public UBaseLegacyWidgetEdMode, public IGizmoEdModeInterface`  
_L92-207_
- reflection: `UCLASS()`
- inherits: `UBaseLegacyWidgetEdMode,IGizmoEdModeInterface`
- desc: Edit mode for animation mixer tracks providing trajectory drawing, per-section skeleton visualization, and gizmo-based root motion offset keying.
- L96 _public member_ `static FEditorModeID ModeName;`
- L98 _public prototype_ `UAnimationMixerTrackEditMode();`
- L101 _public prototype_ `virtual void Enter() override;` — UEdMode interface
- L102 _public prototype_ `virtual void Exit() override;`
- L103 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L104 _public prototype_ `virtual void SelectNone() override;`
- L107 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — ILegacyEdModeViewportInterface
- L108 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L109 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L110 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L111 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L112 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L113 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L114 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L115 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L118 _public function_ `virtual bool UsesToolkits() const override` — ILegacyEdModeWidgetInterface
- L119 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L120 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L121 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L122 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L123 _public prototype_ `virtual EAxisList::Type GetWidgetAxisToDraw(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L124 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L125 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L127 _public prototype_ `void SetSequencer(const TSharedPtr<ISequencer>& InSequencer);`
- L128 _public function_ `void SetTrailHierarchy(const TSharedPtr<UE::Sequencer::FAnimMixerTrailHierarchy>& InHierarchy)`
- L129 _public prototype_ `void InvalidateAllCachedPoses();`
- L134 _public prototype_ `static void KeyOffsetChannels( UMovieSceneRootMotionSettingsDecoration* Decoration, const FVector& LocationOffset, const FRotator& RotationOffset, FFrameNumber KeyTime, const bool bShouldAutoKey);` — Key the Location/Rotation channels on the decoration at a specific frame time. Static so it can be called from trail key editing as well.
- L144 _public prototype_ `FQuat GetCachedAnimSpaceAccumulatedRotation(UMovieSceneSection* Section) const;` — Rotation of the accumulated/initial-root transform the section's offset is keyed relative to, from the last cached pose evaluation. Identity if the section has no cached pose. Used to map a world drag to the offset.
- L147 _private prototype_ `bool IsSomethingSelected() const;`
- L148 _private prototype_ `bool IsTrailKeySelected() const;`
- L149 _private prototype_ `bool BeginDragInternal();`
- L150 _private prototype_ `bool EndDragInternal();`
- L151 _private prototype_ `void InvalidateOffsetCacheForSelection();`
- L155 _private prototype_ `void OnSequencerSectionSelectionChanged(TArray<UMovieSceneSection*> SelectedSections);` — Respond to sequencer section selection changes by auto-selecting roots for sections that have a root motion settings decoration
- L157 _private prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType DataChangeType);`
- L158 _private prototype_ `void OnEditorModeIDChanged(const FEditorModeID& ModeID, bool bIsEnteringMode);`
- L162 _private prototype_ `void EnsureWidgetPriority();` — Moves this mode to the end of the active mode list so its widget-location query is selected first by FEditorModeTools::GetWidgetLocation.
- L165 _private prototype_ `USkeletalMeshComponent* FindSkelMeshForSection(UMovieSceneSection* Section) const;` — Find the skeletal mesh component bound to a section's track in the sequencer
- L181 _private prototype_ `FCachedSectionPose& GetOrEvaluateSectionPose( UMovieSceneSection* Section, UMovieSceneAnimationMixerTrack* MixerTrack, USkeletalMeshComponent* SkelMeshComp, FFrameNumber CurrentFrame);` — Evaluate or retrieve the cached skeleton pose for a section
- L187 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L188 _private member_ `TWeakPtr<UE::Sequencer::FAnimMixerTrailHierarchy> WeakTrailHierarchy;`
- L189 _private member_ `TArray<UE::Sequencer::FMixerSelectedRootData> SelectedRootData;`
- L190 _private member_ `FTransform CurrentRootTransform;`
- L192 _private member_ `UE::Sequencer::FOffsetDragState DragState;`
- L195 _private member_ `TMap<FObjectKey, FCachedSectionPose> CachedSectionPoses;` — Per-section cached skeleton poses, keyed by section object
- L198 _private member_ `FFrameNumber LastRenderedFrame = FFrameNumber(TNumericLimits<int32>::Min());` — Last frame we rendered at, used to detect scrub position changes
- L200 _private member_ `bool bIsTransacting = false;`
- L201 _private member_ `bool bManipulatorMadeChange = false;`
- L202 _private member_ `bool bReorderingSelf = false;`
- L204 _private member_ `FDelegateHandle SectionSelectionChangedHandle;`
- L205 _private member_ `FDelegateHandle MovieSceneDataChangedHandle;`
- L206 _private member_ `FDelegateHandle EditorModeIDChangedHandle;`

#### struct `UAnimationMixerTrackEditMode::FCachedSectionPose`  
`struct FCachedSectionPose`  
_L168-178_
- desc: Cached skeleton pose for a single section, invalidated when scrub time or data changes
- L170 _public member_ `FFrameNumber CachedAtFrame;`
- L171 _public member_ `FTransform RootMotionTransform = FTransform::Identity;`
- L172 _public member_ `UE::UAF::FLODPoseHeap Pose;`
- L173 _public member_ `UE::UAF::FDataHandle RefPoseHandle;`
- L174 _public member_ `TArray<FTransform> WorldBoneTransforms;`
- L175 _public member_ `TArray<int32> ParentBoneIndices;`
- L176 _public member_ `FVector RootBoneLocation = FVector::ZeroVector;`
- L177 _public member_ `FTransform AnimSpaceAccumulatedTransform = FTransform::Identity;`

#### Free symbols / members of external scopes

- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/LayerWeightDecorationEditor.h` (Private)


#### class `UE::Sequencer::FLayerWeightDecorationEditor`  
`class FLayerWeightDecorationEditor : public ISequencerDecorationEditor`  
_L10-16_
- inherits: `ISequencerDecorationEditor`
- L13 _public prototype_ `virtual UClass* GetDecorationClass() const override;`
- L15 _public prototype_ `virtual TSharedPtr<ISequencerSection> MakeSectionInterface(UMovieSceneSection& Section, UMovieSceneTrack& OwningTrack, FGuid ObjectBinding) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/LayerWeightDecorationMenuProvider.h` (Private)


#### class `FLayerWeightDecorationMenuProvider`  
`class FLayerWeightDecorationMenuProvider : public IMovieSceneDecorationMenuProvider`  
_L10-21_
- inherits: `IMovieSceneDecorationMenuProvider`
- desc: Decoration menu provider for layer weight (UMovieSceneLayerWeightDecoration). Adds a "Layer Weight" menu entry that creates a layer weight section spanning the current playback range.
- L14 _public prototype_ `virtual UClass* GetHandledDecorationClass() const override;`
- L15 _public prototype_ `virtual void PopulateAddDecorationMenu(FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, UMovieSceneDecorationContainerObject* DecorationContainer, TWeakPtr<ISequencer> InSequencer) override;`
- L16 _public function_ `virtual int32 GetDecorationMenuPriority() const override`
- L20 _private prototype_ `void OnAddLayerWeight(UMovieSceneDecorationContainerObject* DecorationContainer, TWeakPtr<ISequencer> WeakSequencer);`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/MVVM/AnimationMixerLayoutHelpers.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Sequencer` (scope `UE`)
- L24 _namespace_ `namespace AnimationMixerHelpers` (scope `UE::Sequencer`)
- L29 _prototype_ `void LayoutSections( const TArray<UMovieSceneSection*>& Sections, UMovieSceneTrack* TrackForSections, TSharedPtr<FViewModel> Owner, FViewModelChildren& OutlinerChildren, FViewModelChildren& SectionChildren, FSectionModelStorageExtension* SectionStorage, TSharedPtr<ISequencerTrackEditor> TrackEditor, const FGuid& ObjectBinding, bool bCreateSectionOutliners, bool& bOutChildrenNeedLayout, TOptional<int32> PreviousLayoutNumSections = TOptional<int32>());` (scope `UE::Sequencer::AnimationMixerHelpers`) — Lays out sections for the given track: handles both single and multiple section cases
- L46 _prototype_ `void UpdateLayerRowIndices( UMovieSceneAnimationMixerLayer* Layer, UMovieSceneAnimationMixerTrack* MixerTrack, int32 NewRowIndex, const TSet<UMovieSceneSection*>* ExcludeSections = nullptr);` (scope `UE::Sequencer::AnimationMixerHelpers`) — Update row indices for a layer's contents (sections and child tracks) Common pattern used in drag/cleanup operations

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/MixerLinkedAnimTrackProvider.h` (Private)


#### class `FMixerLinkedAnimTrackProvider`  
`class FMixerLinkedAnimTrackProvider : public IMovieSceneLinkedAnimTrackProvider`  
_L19-52_
- inherits: `IMovieSceneLinkedAnimTrackProvider`
- desc: Linked animation track provider for the Animation Mixer. When a binding has a UMovieSceneAnimationMixerTrack, this provider creates the linked anim track as a child track inside the mixer and handles isolation by toggling mixer tracks rather than individual tracks.
- L22 _public function_ `FMixerLinkedAnimTrackProvider(UE::Sequencer::FAnimationMixerTrackEditor* InTrackEditor) : TrackEditor(InTrackEditor)`
- L27 _public function_ `virtual int32 GetLinkedAnimTrackPriority() const override`
- L28 _public prototype_ `virtual bool CanHandleBinding(const TWeakPtr<ISequencer>& InSequencer, FGuid InBindingID) const override;`
- L29 _public prototype_ `virtual UMovieSceneTrack* GetLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid InInBindingID) const override;`
- L30 _public prototype_ `virtual UMovieSceneTrack* GetOrCreateLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid InBindingID, UE::Sequencer::FCommonAnimationTrackEditor& TrackEditor) override;`
- L31 _public prototype_ `virtual bool IsolateLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid InBindingID, bool bIsolate) override;`
- L32 _public prototype_ `virtual void UpdateLinkedAnimSectionRange(const TWeakPtr<ISequencer>& InSequencer, FGuid InBindingID) override;`
- L33 _public prototype_ `virtual bool DeleteLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid InBindingID) override;`
- L34 _public prototype_ `virtual bool TryBakeLinkedAnimSequence( const TWeakPtr<ISequencer>& InSequencer, FGuid InBindingID, UAnimSequence* InAnimSequence, const FLevelSequenceAnimSequenceLinkItem& InLinkItem) override;`
- L42 _private prototype_ `bool HasMixerTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid InInBindingID) const;` — Whether or not it has a mixer track
- L45 _private prototype_ `TPair<UMovieSceneAnimationMixerTrack*,UMovieSceneSection*> FindMixerTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid InBindingID) const;` — Find the MixerTrack on the binding and associated section, if any. It may return a mixer track with no section, which means we still need to create the section
- L47 _private prototype_ `UMovieSceneSkeletalAnimationTrack* FindLinkedChildTrack( UMovieSceneAnimationMixerTrack* MixerTrack, const TArray<struct FLevelSequenceAnimSequenceLinkItem*>& LinkedItems) const;` — Find the child skeletal animation track inside a MixerTrack that contains the linked anim sequence.
- L51 _private member_ `UE::Sequencer::FAnimationMixerTrackEditor* TrackEditor = nullptr;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/MixerRootMotionTrail.h` (Private)


#### class `UE::Sequencer::FMixerRootMotionTrail`  
`class FMixerRootMotionTrail : public UE::SequencerAnimTools::FTrail`  
_L23-98_
- inherits: `UE::SequencerAnimTools::FTrail`
- desc: Custom trail for animation mixer root motion trajectory visualization. Uses AnimMixerBakeEvaluation to get root motion transforms rather than reading component transforms, so it works for all root motion destination types.
- L26 _public prototype_ `FMixerRootMotionTrail( UMovieSceneAnimationMixerTrack* InMixerTrack, TWeakPtr<ISequencer> InSequencer);`
- L29 _public prototype_ `~FMixerRootMotionTrail();`
- L32 _public prototype_ `virtual UE::SequencerAnimTools::FTrailCurrentStatus UpdateTrail(const FNewSceneContext& NewSceneContext) override;` — FTrail interface
- L33 _public prototype_ `virtual void UpdateFinished(const TRange<FFrameNumber>& UpdatedRange, const TArray<int32>& IndicesToCalcluate, bool bDoneCalcuating) override;`
- L34 _public prototype_ `virtual FText GetName() const override;`
- L35 _public prototype_ `virtual void Render(const FGuid& Guid, const FSceneView* View, FPrimitiveDrawInterface* PDI, bool bTrailIsEvaluating) override;`
- L36 _public prototype_ `virtual void GetTrajectoryPointsForDisplay(const UE::SequencerAnimTools::FCurrentFramesInfo& InCurrentFramesInfo, bool bIsEvaluating, TArray<FVector>& OutPoints, TArray<FFrameNumber>& OutFrames) override;`
- L37 _public prototype_ `virtual void ClearCachedData() override;`
- L38 _public prototype_ `virtual void ReadyToDrawTrail(UE::SequencerAnimTools::FColorState& ColorState, const UE::SequencerAnimTools::FCurrentFramesInfo* InCurrentFramesInfo, bool bIsEvaluating, bool bIsPinned) override;`
- L39 _public prototype_ `virtual bool HandleObjectsChanged(const TMap<UObject*, UObject*>& ReplacementMap) override;`
- L41 _public prototype_ `virtual bool HandleClick(const FGuid& Guid, FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, UE::SequencerAnimTools::FInputClick Click) override;`
- L42 _public prototype_ `virtual bool IsAnythingSelected() const override;`
- L43 _public prototype_ `virtual bool IsAnythingSelected(FVector& OutVectorPosition, FQuat& OutRotation) const override;`
- L44 _public prototype_ `virtual bool IsAnythingSelected(TArray<FVector>& OutVectorPositions) const override;`
- L45 _public prototype_ `virtual void SelectNone() override;`
- L46 _public prototype_ `virtual bool StartTracking() override;`
- L47 _public prototype_ `virtual bool ApplyDelta(const FVector& Pos, const FRotator& Rot, const FVector& WidgetLocation, bool bApplyToOffset) override;`
- L48 _public prototype_ `virtual bool EndTracking() override;`
- L50 _public prototype_ `UMovieSceneAnimationMixerTrack* GetMixerTrack() const;`
- L53 _public prototype_ `void SetDecorations(TArray<TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration>>&& InDecorations);` — Set the decorations whose offset channels provide key times (one per section)
- L56 _public prototype_ `void SetBoundComponent(USkeletalMeshComponent* InComponent);` — Set the bound skeletal mesh component for world-to-local delta conversion
- L59 _public function_ `void SetHierarchy(FAnimMixerTrailHierarchy* InHierarchy)` — Set the owning hierarchy for synchronous re-bake during key drags
- L62 _public prototype_ `FTransform GetTransformAtFrame(FFrameNumber Frame) const;` — Interpolate a transform from the baked trajectory at a specific frame
- L65 _public function_ `TSharedPtr<UE::AIE::FArrayOfTransforms>& GetCalculatedTransforms()` — Provides the transform array that the trail hierarchy populates during bake evaluation
- L67 _public function_ `bool NeedsSynchronousRebake() const`
- L68 _public function_ `void ClearSynchronousRebakeFlag()`
- L69 _public function_ `void RequestSynchronousRebake()`
- L72 _private member_ `TWeakObjectPtr<UMovieSceneAnimationMixerTrack> WeakMixerTrack;`
- L73 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L74 _private member_ `TArray<TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration>> Decorations;`
- L75 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> WeakBoundComponent;`
- L76 _private member_ `FAnimMixerTrailHierarchy* OwningHierarchy = nullptr;`
- L79 _private member_ `TSharedPtr<UE::AIE::FArrayOfTransforms> CalculatedArrayOfTransforms;` — Transforms computed by bake evaluation
- L81 _private member_ `TSharedPtr<UE::AIE::FArrayOfTransforms> ArrayOfTransforms;` — Transforms used for drawing (copied from calculated, may include offset)
- L83 _private member_ `TUniquePtr<FMixerTrailKeyTool> KeyTool;`
- L91 _private member_ `mutable FDrawCacheData CachedDrawData;`
- L93 _private member_ `const UE::SequencerAnimTools::FCurrentFramesInfo* CurrentFramesInfo = nullptr;`
- L94 _private member_ `bool bIsTracking = false;`
- L95 _private member_ `bool bNeedsSynchronousRebake = false;`
- L97 _private member_ `FOffsetDragState DragState;`

#### struct `UE::Sequencer::FMixerRootMotionTrail::FDrawCacheData`  
`struct FDrawCacheData`  
_L85-90_
- L87 _public member_ `TArray<FVector> PointsToDraw;`
- L88 _public member_ `TArray<FFrameNumber> Frames;`
- L89 _public member_ `TArray<FLinearColor> Color;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/MixerTrailKeyTool.h` (Private)


#### struct `UE::Sequencer::FMixerTrailKeyInfo`  
`struct FMixerTrailKeyInfo`  
_L22-28_
- L24 _public member_ `FFrameNumber FrameNumber;`
- L25 _public member_ `FTransform Transform;`
- L26 _public member_ `TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration> Decoration;`
- L27 _public member_ `bool bDirty = true;`

#### struct `UE::Sequencer::HMixerTrailKeyProxy`  
`struct HMixerTrailKeyProxy : public HHitProxy`  
_L31-44_
- inherits: `HHitProxy`
- desc: Hit proxy for clicking on mixer trail keys in the viewport
- L33 _public prototype_ `DECLARE_HIT_PROXY();`
- L35 _public member_ `FGuid Guid;`
- L36 _public member_ `FMixerTrailKeyInfo* KeyInfo;`
- L38 _public function_ `HMixerTrailKeyProxy(const FGuid& InGuid, FMixerTrailKeyInfo* InKeyInfo) : HHitProxy(HPP_UI) , Guid(InGuid) , KeyInfo(InKeyInfo)`

#### class `UE::Sequencer::FMixerTrailKeyTool`  
`class FMixerTrailKeyTool`  
_L48-94_
- desc: Renders and manages interactive offset keys on the mixer root motion trail. Keys are drawn at positions interpolated from the baked trajectory array.
- L51 _public prototype_ `explicit FMixerTrailKeyTool(FMixerRootMotionTrail* InOwningTrail);`
- L52 _public prototype_ `~FMixerTrailKeyTool() = default;`
- L54 _public prototype_ `void SetDecorations(TArray<TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration>>&& InDecorations);`
- L57 _public prototype_ `void BuildKeys();` — Rebuild the key list from all decoration channels
- L60 _public prototype_ `void DirtyKeyTransforms();` — Mark all key transforms dirty so they re-interpolate from the trail cache
- L63 _public prototype_ `void UpdateKeys();` — Update dirty key transforms from the trail's baked trajectory
- L66 _public prototype_ `void UpdateViewRange(const TRange<FFrameNumber>& InViewRange);` — Cache the current view frame range for culling key rendering
- L68 _public prototype_ `void Render(const FGuid& Guid, const FSceneView* View, FPrimitiveDrawInterface* PDI, bool bTrailIsEvaluating);`
- L69 _public prototype_ `bool HandleClick(const FGuid& Guid, FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, UE::SequencerAnimTools::FInputClick Click);`
- L71 _public prototype_ `bool IsSelected() const;`
- L72 _public prototype_ `bool IsSelected(FVector& OutVectorPosition, FQuat& OutRotation) const;`
- L73 _public prototype_ `bool IsSelected(TArray<FVector>& OutVectorPositions) const;`
- L74 _public prototype_ `void ClearSelection();`
- L76 _public prototype_ `TArray<FFrameNumber> GetSelectedKeyTimes() const;`
- L77 _public prototype_ `FFrameNumber GetPrimarySelectedKeyTime() const;`
- L78 _public prototype_ `UMovieSceneRootMotionSettingsDecoration* GetPrimarySelectedKeyDecoration() const;`
- L82 _public prototype_ `void ApplyWorldDelta(FFrameNumber KeyFrame, const FVector& WorldPosDelta, const FRotator& WorldRotDelta);` — Directly move a key's cached transform by a world-space delta. Used during gizmo drags to keep the gizmo in sync without re-evaluation.
- L85 _private prototype_ `void UpdateSelectedKeysTransform() const;`
- L87 _private member_ `FMixerRootMotionTrail* OwningTrail;`
- L88 _private member_ `TArray<TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration>> Decorations;`
- L90 _private member_ `TArray<TUniquePtr<FMixerTrailKeyInfo>> Keys;`
- L91 _private member_ `TSet<FMixerTrailKeyInfo*> CachedSelection;`
- L92 _private member_ `mutable FTransform SelectedKeysTransform;`
- L93 _private member_ `TRange<FFrameNumber> CachedViewFrameRange;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequencerAnimTools` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/MovieSceneAnimMixerEditorModule.h` (Private)


#### class `UE::MovieScene::FAnimMixerRootMotionOffsetProvider`  
`class FAnimMixerRootMotionOffsetProvider : public IMovieSceneRootMotionOffsetProvider`  
_L24-30_
- inherits: `IMovieSceneRootMotionOffsetProvider`
- L27 _public prototype_ `virtual FTransform GetRootMotionOffset(const UMovieSceneEntitySystemLinker* Linker, UObject* AnimatedObject) const override;`
- L28 _public prototype_ `virtual FTransform GetRootMotionOffset(const UMovieSceneEntitySystemLinker* Linker, UObject* AnimatedObject, const UObject* EditingContext) const override;`
- L29 _public prototype_ `virtual void UpdateRootMotionOffset(UMovieSceneEntitySystemLinker* Linker, UObject* AnimatedObject) override;`

#### class `UE::MovieScene::FAnimMixerBakeScope`  
`class FAnimMixerBakeScope : public IMovieSceneAnimSequenceBakeScope`  
_L37-42_
- inherits: `IMovieSceneAnimSequenceBakeScope`
- desc: Forwards Begin/End to UMovieSceneAnimMixerSystem::Push/PopForceRootBoneDestinationScope so the binding-level AnimSeq/CR bake recorder captures mixer root motion on the root bone rather than seeing it applied to the actor.
- L40 _public prototype_ `virtual void BeginBakeScope() override;`
- L41 _public prototype_ `virtual void EndBakeScope() override;`

#### class `UE::MovieScene::FMovieSceneAnimMixerEditorModule`  
`class FMovieSceneAnimMixerEditorModule : public IModuleInterface, public IAnimGraph_SequencerMixerTargetConnector`  
_L44-83_
- inherits: `IModuleInterface,IAnimGraph_SequencerMixerTargetConnector`
- L49 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L50 _public prototype_ `virtual void ShutdownModule() override;`
- L52 _public prototype_ `virtual void GetSequencerMixerTargetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`
- L55 _private member_ `FDelegateHandle AnimationTrackEditorHandle;`
- L56 _private member_ `FDelegateHandle AnimationMixerTrackModelHandle;`
- L59 _private member_ `TUniquePtr<FAutomaticTargetMenuProvider> AutomaticTargetMenuProvider;` — Target menu providers
- L60 _private member_ `TUniquePtr<FAnimInstanceTargetMenuProvider> AnimInstanceTargetMenuProvider;`
- L61 _private member_ `TUniquePtr<FAnimBlueprintTargetMenuProvider> AnimBlueprintTargetMenuProvider;`
- L62 _private member_ `TUniquePtr<FAnimNextInjectionTargetMenuProvider> AnimNextInjectionTargetMenuProvider;`
- L63 _private member_ `TUniquePtr<FAnimBusTargetMenuProvider> BusTargetMenuProvider;`
- L66 _private member_ `TUniquePtr<FAnimBusSectionMenuProvider> BusSectionMenuProvider;` — Bus section menu provider
- L69 _private member_ `FDelegateHandle RootMotionTargetDecorationEditorHandle;` — Decoration editor factory handles
- L70 _private member_ `FDelegateHandle RootMotionSettingsDecorationEditorHandle;`
- L71 _private member_ `FDelegateHandle AnimMaskingDecorationEditorHandle;`
- L72 _private member_ `FDelegateHandle LayerWeightDecorationEditorHandle;`
- L73 _private member_ `FDelegateHandle MirroringDecorationEditorHandle;`
- L76 _private member_ `TUniquePtr<FMaskDecorationMenuProvider> MaskDecorationMenuProvider;` — Decoration menu providers
- L77 _private member_ `TUniquePtr<FLayerWeightDecorationMenuProvider> LayerWeightDecorationMenuProvider;`
- L78 _private member_ `FAnimMixerRootMotionOffsetProvider AnimMixerRootMotionProvider;`
- L82 _private member_ `FAnimMixerBakeScope BakeScope;` — Scope provider that forces mixer root motion onto the root bone during binding-level AnimSeq / CR bake recording.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace MovieScene` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/MovieSceneAnimMixerEditorStyle.h` (Private)


#### class `FMovieSceneAnimMixerEditorStyle`  
`class FMovieSceneAnimMixerEditorStyle final : public FSlateStyleSet`  
_L12-46_
- inherits: `FSlateStyleSet`
- desc: Style set containing icons for the Animation Mixer outliner rows. Used by the mixer track, layer model, section interfaces, and decoration editors to resolve per-track/row brushes.
- L16 _public function_ `FMovieSceneAnimMixerEditorStyle() : FSlateStyleSet("MovieSceneAnimMixerEditorStyle")`
- L36 _public function_ `~FMovieSceneAnimMixerEditorStyle()`
- L41 _public function_ `static FMovieSceneAnimMixerEditorStyle& Get()`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/MovieSceneAnimationMixerTrackEditor.h` (Private)


#### class `UE::Sequencer::FAnimMixerAnimationSection`  
`class FAnimMixerAnimationSection : public FCommonAnimationSection`  
_L29-56_
- inherits: `FCommonAnimationSection`
- desc: Section interface for skeletal animation sections within a mixer track. Handles transition padding, context menus for creating transitions between overlapping sections, and disables the legacy bone matching UI.
- L34 _public function_ `FAnimMixerAnimationSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer) : FCommonAnimationSection(InSection, InSequencer)`
- L39 _public function_ `virtual bool ShouldShowLegacyBoneMatching() const override`
- L40 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L42 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L43 _public prototype_ `virtual FMargin GetContentPadding() const override;`
- L44 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L46 _public prototype_ `void PopulateCreateTransitionMenu(FMenuBuilder& MenuBuilder);`
- L47 _public prototype_ `void PopulateTransitionTypeMenu(FMenuBuilder& MenuBuilder, UMovieSceneSection* OtherSection, TArray<UClass*> TransitionClasses);`
- L48 _public prototype_ `void CreateTransitionToSection(UMovieSceneSection* FromSection, UMovieSceneSection* ToSection, UClass* TransitionClass);`
- L52 _private prototype_ `float CalculateTransitionPadding(const FTimeToPixel& TimeConverter) const;`
- L55 _private member_ `mutable float CachedTransitionPaddingLeft = 0.0f;` — Cached transition padding calculated in OnPaintSection for use in GetContentPadding

#### class `UE::Sequencer::FAnimationMixerTrackEditor`  
`class FAnimationMixerTrackEditor : public FCommonAnimationTrackEditor , public IMovieSceneAnimMixerItemMenuProvider`  
_L58-134_
- inherits: `FCommonAnimationTrackEditor,IMovieSceneAnimMixerItemMenuProvider`
- L64 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L67 _public function_ `static void RegisterCustomMixerAnimSection(const UClass* InClass, FOnMakeSectionInterfaceDelegate InMakeSectionInterfaceDelegate)`
- L72 _public function_ `static void UnregisterCustomMixerAnimSection(const UClass* InClass)`
- L79 _public prototype_ `FAnimationMixerTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L83 _public prototype_ `virtual FText GetDisplayName() const override;`
- L84 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L85 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerColumnWidget(const FBuildColumnWidgetParams& Params, const FName& ColumnName) override;`
- L86 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L87 _public prototype_ `virtual void OnInitialize() override;`
- L88 _public prototype_ `virtual void OnRelease() override;`
- L89 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L90 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L91 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L92 _public prototype_ `virtual TSubclassOf<UMovieSceneCommonAnimationTrack> GetTrackClass() const override;`
- L93 _public function_ `virtual bool ShouldActivateSkeletalAnimEditMode() const override`
- L94 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L97 _public prototype_ `virtual const UClass* GetHandledMixerItemClass() const override;` — IMovieSceneAnimMixerItemMenuProvider interface
- L98 _public prototype_ `virtual void PopulateAddMixerItemMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TSharedPtr<ISequencer> Sequencer, int32 RowIndex) override;`
- L99 _public prototype_ `virtual void PopulateObjectBindingAnimationMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass, bool bIsInsideSubmenu) override;`
- L100 _public function_ `virtual int32 GetObjectBindingAnimationMenuPriority() const override` — Highest priority - appears first
- L105 _private prototype_ `TSharedRef<SWidget> BuildAddSectionSubMenu(TWeakViewModelPtr<IOutlinerExtension> WeakViewModel, TWeakViewModelPtr<FSequencerEditorViewModel> WeakEditor);`
- L106 _private prototype_ `void HandleAddAnimationTrackMenuEntryExecute(TArray<FGuid> ObjectBindings);`
- L107 _private prototype_ `void HandleAddMixerTrackWithTarget(TArray<FGuid> ObjectBindings, TInstancedStruct<FMovieSceneMixedAnimationTarget> Target);`
- L108 _private prototype_ `void BuildTargetSelectionMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, const UClass* ObjectClass);`
- L109 _private prototype_ `void PopulateAddAnimationMenu(FMenuBuilder& MenuBuilder, TWeakViewModelPtr<IOutlinerExtension> WeakViewModel, TWeakViewModelPtr<FSequencerEditorViewModel> WeakEditor);`
- L111 _private prototype_ `bool FilterAnimSequences(const FAssetData& AssetData, USkeleton* Skeleton);`
- L112 _private prototype_ `void OnAnimationAssetSelected(const FAssetData& AssetData, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track);`
- L113 _private prototype_ `void OnAnimationAssetEnterPressed(const TArray<FAssetData>& AssetData, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track);`
- L115 _private prototype_ `void OnCreateAdditionalTrailHierarchies( TArray<TSharedPtr<UE::SequencerAnimTools::FTrailHierarchy>>& TrailHierarchies, TWeakPtr<ISequencer> WeakSequencer);`
- L119 _private member_ `FDelegateHandle AdditionalTrailHierarchiesHandle;`
- L120 _private member_ `TSharedPtr<FAnimMixerTrailHierarchy> MixerTrailHierarchy;`
- L122 _private member_ `bool bRegisteredLevelEditorMode = false;`
- L124 _private member_ `static int32 MixerEditModeRefCount;`
- L125 _private prototype_ `static void RegisterMakeSectionInterfaceCallback(const UClass* SectionClass, FOnMakeSectionInterfaceDelegate Callback);`
- L126 _private prototype_ `static void UnregisterMakeSectionInterfaceCallback(const UClass* SectionClass);`
- L130 _public member_ `bool bFilterAssetBySkeleton = true;` — Filter state for Bake To Control Rig (passed by ref to shared helpers; public for layer model access)
- L132 _public member_ `static TMap<const UClass*, FOnMakeSectionInterfaceDelegate> MakeSectionInterfaceCallbacks;`
- L133 _public member_ `TUniquePtr<FMixerLinkedAnimTrackProvider> MixerLinkedAnimProvider;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SequencerAnimTools` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Sequencer` (scope `UE`)
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedRef<ISequencerSection>, FOnMakeSectionInterfaceDelegate, UMovieSceneSection&, UMovieSceneTrack&, FGuid);`
- L21 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedRef<ISequencerSection>, FOnMakeSectionInterfaceDelegate, UMovieSceneSection&, UMovieSceneTrack&, FGuid);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/RootMotionSettingsDecorationEditor.h` (Private)


#### class `UE::Sequencer::FRootMotionSettingsDecorationEditor`  
`class FRootMotionSettingsDecorationEditor : public ISequencerDecorationEditor`  
_L20-117_
- inherits: `ISequencerDecorationEditor`
- desc: Decoration editor for UMovieSceneRootMotionSettingsDecoration. Provides the "Root Transform" right-click context menu with transform mode selection, re-center, and bone matching.
- L23 _public function_ `explicit FRootMotionSettingsDecorationEditor(TSharedRef<ISequencer> InSequencer) : WeakSequencer(InSequencer)`
- L29 _public prototype_ `virtual UClass* GetDecorationClass() const override;`
- L30 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L31 _public prototype_ `virtual FSlateIcon GetMenuIcon() const override;`
- L33 _public prototype_ `virtual void OnSectionInterfaceCreated( UMovieSceneSection& Section, UObject& Decoration, TWeakPtr<ISequencer> Sequencer) override;`
- L38 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L40 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneSection& Section, UObject& Decoration, const FGuid& ObjectBinding, TWeakPtr<ISequencer> Sequencer) override;`
- L46 _public prototype_ `virtual TSharedPtr<SWidget> CreateKeyEditor( UObject& Decoration, UMovieSceneSection& Section, FMovieSceneChannelHandle ChannelHandle, TWeakPtr<ISequencer> Sequencer, const FGuid& ObjectBindingID) override;`
- L53 _public prototype_ `virtual TSharedPtr<SWidget> CreateKeyFrameWidget( UObject& Decoration, UMovieSceneSection& Section, FMovieSceneChannelHandle ChannelHandle, TWeakPtr<ISequencer> Sequencer, const FGuid& ObjectBindingID, TSharedPtr<UE::Sequencer::FViewModel> ChannelGroupModel) override;`
- L62 _private prototype_ `void PopulateRootTransformMenu( FMenuBuilder& MenuBuilder, TWeakObjectPtr<UMovieSceneSection> Section, TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration> Settings, FGuid ObjectBinding, TWeakPtr<ISequencer> Sequencer);`
- L69 _private prototype_ `void RecenterRootTransform( UMovieSceneSection* Section, UMovieSceneRootMotionSettingsDecoration* Settings, TWeakPtr<ISequencer> Sequencer);`
- L74 _private prototype_ `static void OpenBoneMatchDialog( UMovieSceneSection* Section, UMovieSceneRootMotionSettingsDecoration* Settings, FGuid ObjectBinding, TWeakPtr<ISequencer> Sequencer);`
- L80 _private prototype_ `static void OnBoneMatchAccepted( const FMovieSceneBoneMatchData& MatchSettings, UMovieSceneSection* Section, UMovieSceneRootMotionSettingsDecoration* Settings, TWeakPtr<ISequencer> Sequencer);`
- L86 _private prototype_ `void RematchBone( UMovieSceneSection* Section, UMovieSceneRootMotionSettingsDecoration* Settings, TWeakPtr<ISequencer> Sequencer);`
- L91 _private prototype_ `void ClearBoneMatch( UMovieSceneSection* Section, UMovieSceneRootMotionSettingsDecoration* Settings, TWeakPtr<ISequencer> Sequencer);`
- L96 _private prototype_ `void HandleBoneMatchKeyMoved(FMovieSceneChannel* Channel, const TArray<FKeyMoveEventItem>& Items);`
- L97 _private prototype_ `void HandleBoneMatchKeyDeleted(FMovieSceneChannel* Channel, const TArray<FKeyAddOrDeleteEventItem>& Items);`
- L98 _private prototype_ `void HandleDecorationSignatureChanged(TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration> WeakDecoration);`
- L109 _private prototype_ `FTrackedSectionInfo* FindTrackedInfoForChannel(FMovieSceneChannel* Channel, UMovieSceneRootMotionSettingsDecoration*& OutDecoration);`
- L111 _private member_ `TMap<TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration>, FTrackedSectionInfo> TrackedDecorations;`
- L112 _private member_ `TSet<TWeakObjectPtr<UMovieSceneRootMotionSettingsDecoration>> PendingRematches;`
- L113 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L116 _private member_ `bool bHandlingSignatureChange = false;` — Guards Tick from re-entering when PropagateRematch's Modify() fires signature events on dependents.

#### struct `UE::Sequencer::FRootMotionSettingsDecorationEditor::FTrackedSectionInfo`  
`struct FTrackedSectionInfo`  
_L100-107_
- L102 _public member_ `TWeakObjectPtr<UMovieSceneSection> Section;`
- L103 _public member_ `FDelegateHandle DecorationSigHandle;`
- L104 _public member_ `FDelegateHandle SectionSigHandle;`
- L105 _public member_ `FGuid LastDecorationSignature;`
- L106 _public member_ `FGuid LastSectionSignature;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/RootMotionTargetDecorationEditor.h` (Private)


#### class `UE::Sequencer::FRootMotionTargetSectionInterface`  
`class FRootMotionTargetSectionInterface : public ISequencerSection , public TSharedFromThis<FRootMotionTargetSectionInterface>`  
_L20-35_
- inherits: `ISequencerSection,TSharedFromThis<FRootMotionTargetSectionInterface>`
- desc: Section interface for root motion sections displayed under decoration outliners. Provides basic display with the channel data for root motion destination.
- L25 _public prototype_ `FRootMotionTargetSectionInterface(UMovieSceneSection& InSection, UMovieSceneTrack& InTrack, FGuid InObjectBinding);`
- L28 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L29 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L30 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L31 _public function_ `virtual bool IsReadOnly() const override`
- L34 _private member_ `TWeakObjectPtr<UMovieSceneSection> SectionPtr;`

#### class `UE::Sequencer::FRootMotionTargetDecorationEditor`  
`class FRootMotionTargetDecorationEditor : public ISequencerDecorationEditor`  
_L41-51_
- inherits: `ISequencerDecorationEditor`
- desc: Decoration editor for UMovieSceneRootMotionTargetDecoration. Creates section interfaces for the root motion sections that the decoration provides.
- L44 _public prototype_ `virtual UClass* GetDecorationClass() const override;`
- L45 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L46 _public prototype_ `virtual FSlateIcon GetMenuIcon() const override;`
- L47 _public prototype_ `virtual TSharedPtr<ISequencerSection> MakeSectionInterface( UMovieSceneSection& Section, UMovieSceneTrack& OwningTrack, FGuid ObjectBinding) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Private/SBoneMatchDialog.h` (Private)


#### class `SBoneMatchDialog`  
`class SBoneMatchDialog : public SCompoundWidget`  
_L20-86_
- inherits: `SCompoundWidget`
- desc: Modal dialog for configuring bone matching parameters.
- L24 _public function_ `SLATE_BEGIN_ARGS(SBoneMatchDialog) : _Sequencer(nullptr) , _TargetSection(nullptr) , _MixerTrack(nullptr) , _Decoration(nullptr)`
- L30 _public prototype_ `SLATE_ARGUMENT(ISequencer*, Sequencer) SLATE_ARGUMENT(UMovieSceneSection*, TargetSection) SLATE_ARGUMENT(UMovieSceneAnimationMixerTrack*, MixerTrack) SLATE_ARGUMENT(UMovieSceneRootMotionSettingsDecoration*, Decoration) SLATE_ARGUMENT(FGuid, ObjectBinding) SLATE_EVENT(FOnBoneMatchAccepted, OnAccepted) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `FReply OpenDialog(bool bModal = true);`
- L41 _public prototype_ `void CloseDialog();`
- L46 _private prototype_ `void BuildReferenceSectionList();` — Build the list of candidate reference sections
- L49 _private prototype_ `void RebuildMatchTimeModeOptions();` — Build the match time mode option list
- L52 _private prototype_ `void OnBoneSelectionChanged(FName NewBoneName);` — Callbacks
- L53 _private prototype_ `void OnReferenceSectionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L54 _private prototype_ `void OnMatchTimeModeChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L55 _private prototype_ `FReply OnOKClicked();`
- L57 _private member_ `ISequencer* Sequencer = nullptr;`
- L58 _private member_ `UMovieSceneSection* TargetSection = nullptr;`
- L59 _private member_ `UMovieSceneAnimationMixerTrack* MixerTrack = nullptr;`
- L60 _private member_ `UMovieSceneRootMotionSettingsDecoration* Decoration = nullptr;`
- L61 _private member_ `FGuid ObjectBinding;`
- L62 _private member_ `FOnBoneMatchAccepted OnAccepted;`
- L64 _private member_ `TWeakPtr<SWindow> DialogWindow;`
- L66 _private member_ `FName BoneName;`
- L67 _private member_ `TWeakObjectPtr<UMovieSceneSection> ReferenceSection;`
- L68 _private member_ `uint8 MatchTimeMode = 0;`
- L70 _private member_ `bool bMatchLocationX = true;`
- L71 _private member_ `bool bMatchLocationY = true;`
- L72 _private member_ `bool bMatchLocationZ = false;`
- L73 _private member_ `bool bMatchRotationX = false;`
- L74 _private member_ `bool bMatchRotationY = false;`
- L75 _private member_ `bool bMatchRotationZ = true;`
- L78 _private member_ `TArray<TWeakObjectPtr<UMovieSceneSection>> ReferenceSections;` — Reference section options
- L79 _private member_ `TArray<TSharedPtr<FString>> ReferenceSectionNames;`
- L80 _private member_ `int32 SelectedReferenceSectionIndex = INDEX_NONE;`
- L83 _private member_ `TArray<EBoneMatchTimeMode> FilteredMatchTimeModes;` — Match time mode options (filtered to only include valid modes for current overlap)
- L84 _private member_ `TArray<TSharedPtr<FString>> MatchTimeModeNames;`
- L85 _private member_ `int32 SelectedMatchTimeModeIndex = 0;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBoneMatchAccepted, const FMovieSceneBoneMatchData&);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBoneMatchAccepted, const FMovieSceneBoneMatchData&);`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Public/AnimBlueprintExtension_SequencerMixerTarget.h` (Public)


#### class `UAnimBlueprintExtension_SequencerMixerTarget`  
`class UAnimBlueprintExtension_SequencerMixerTarget : public UAnimBlueprintExtension`  
_L14-21_
- reflection: `UCLASS()`
- inherits: `UAnimBlueprintExtension`
- desc: Extension for brokering Animation Mixer data between sequencer and animation blueprints.
- L20 _private member_ `FAnimSubsystem_SequencerMixer Subsystem;` — `UPROPERTY()`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Public/AnimGraphNode_SequencerMixerTarget.h` (Public)


#### class `UAnimGraphNode_SequencerMixerTarget`  
`class UAnimGraphNode_SequencerMixerTarget : public UAnimGraphNode_Base`  
_L11-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base`
- L18 _public member_ `FAnimNode_SequencerMixerTarget Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L21 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L22 _public prototype_ `virtual FText GetTooltipText() const override;`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L27 _public prototype_ `virtual FString GetNodeCategory() const override;`
- L28 _public prototype_ `virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;`
- L29 _public prototype_ `virtual void GetRequiredExtensions(TArray<TSubclassOf<UAnimBlueprintExtension>>& OutExtensions) const override;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Public/AnimMixerBakeHelper.h` (Public)


#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Sequencer` (scope `UE`)
- L21 _namespace_ `namespace AnimMixerBake` (scope `UE::Sequencer`)
- L29 _prototype_ `bool ExportMixerToAnimSequence( const TSharedPtr<ISequencer>& Sequencer, UAnimSequence* AnimSequence, UAnimSeqExportOption* ExportOptions, USkeletalMeshComponent* SkelMeshComp, UMovieSceneAnimationMixerTrack* MixerTrack, const UE::MovieScene::AnimMixerBakeEvaluation::FBakeFilter& Filter = {});` (scope `UE::Sequencer::AnimMixerBake`) — Fills a UAnimSequence from mixer EvaluateRange results. Filter defaults to empty (evaluates entire track); populate IncludeOnlySections for per-layer bake. Respects all UAnimSeqExportOption settings (transforms, curves, interpolation, name filters, etc.).
- L52 _prototype_ `void BuildBakeMenuSection( FMenuBuilder& MenuBuilder, const TSharedPtr<ISequencer>& Sequencer, UMovieSceneAnimationMixerTrack* MixerTrack, USkeletalMeshComponent* SkelMeshComp, USkeleton* Skeleton, FGuid ObjectBinding, UObject* BoundObject, bool& bFilterAssetBySkeleton, const UE::MovieScene::AnimMixerBakeEvaluation::FBakeFilter& Filter, TFunction<UMovieSceneTrack*(UMovieScene*, TSubclassOf<UMovieSceneTrack>)> ChildTrackFactory, TFunction<void(UMovieSceneTrack*, UObject*, bool)> OnComplete, const FText& EntryLabelVerb = FText::GetEmpty(), FCanExecuteAction CanExecuteOverride = FCanExecuteAction(), const FText& DisabledTooltipOverride = FText::GetEmpty());` (scope `UE::Sequencer::AnimMixerBake`) — Builds the full "Bake" menu section into MenuBuilder: - "{EntryLabelVerb} to Anim Sequence" entry (with asset creation dialog + notification) - "{EntryLabelVerb} to Control Rig" submenu (via IMovieSceneAnimMixerBakeProvider, if registered) Works for both whole-track and per-layer contexts. Callers provide: - Filter: empty for whole track, populated with priority range for layer(s) - EntryLabelVerb: prefix used in leaf entry labels (e.g. "Bake", "Bake Layer", "Bake Selected Layers") - ChildTrackFactory: creates a child track in the mixer (the provider passes the track class) - OnComplete: post-bake actions (muting source layers/tracks, etc.) - CanExecuteOverride (optional): controls enable/disable state of the leaf entries. Defaults to always-enabled. - DisabledTooltipOverride (optional): tooltip shown when CanExecuteOverride returns false. Empty falls back to the normal enabled tooltip.

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Public/MVVM/AnimationMixerLayerModel.h` (Public)


#### class `UE::Sequencer::FAnimationMixerLayerModel`  
`class FAnimationMixerLayerModel : public FEvaluableOutlinerItemModel , public IRenameableExtension , public IResizableExtension , public ITrackExtension , public ITrackRowExtension , public ISectionOwnerExtension , public ITopLevelChannelHolderExtension , public ITrackAreaExtension , public ILockableExtension , public IGroupableExtension , public ISortableExtension , public IDraggableOutlinerExtension , public IDeletableExtension , public IConditionableExtension`  
_L49-229_
- inherits: `FEvaluableOutlinerItemModel,IRenameableExtension,IResizableExtension,ITrackExtension,ITrackRowExtension,ISectionOwnerExtension,ITopLevelChannelHolderExtension,ITrackAreaExtension,ILockableExtension,IGroupableExtension,ISortableExtension,IDraggableOutlinerExtension,IDeletableExtension,IConditionableExtension`
- desc: View model for an Animation Mixer Layer. A layer can contain either: - Multiple sections (any combo of mixed types that produce anim poses) - A single child track (e.g., Control Rig track) that occupies the entire layer Implements all the same extensions as FTrackModel and FTrackRowModel to support: - Drag/drop reordering via ITrackExtension::SetRowIndex() - Section management - Channel display - Locking, muting, soloing - Context menus - Being treated as a 'track' for child tracks
- L67 _public prototype_ `UE_SEQUENCER_DECLARE_CASTABLE(FAnimationMixerLayerModel , FEvaluableOutlinerItemModel , IRenameableExtension , IResizableExtension , ITrackExtension , ITrackRowExtension , ISectionOwnerExtension , ITopLevelChannelHolderExtension , ITrackAreaExtension , ILockableExtension , IGroupableExtension , ISortableExtension , IDraggableOutlinerExtension , IDeletableExtension , IConditionableExtension);`
- L84 _public prototype_ `explicit FAnimationMixerLayerModel(UMovieSceneAnimationMixerTrack* InParentTrack, UMovieSceneAnimationMixerLayer* InLayer);` — Constructor for layer containing sections
- L87 _public prototype_ `explicit FAnimationMixerLayerModel(UMovieSceneAnimationMixerTrack* InParentTrack, UMovieSceneAnimationMixerLayer* InLayer, UMovieSceneTrack* InChildTrack);` — Constructor for layer containing a child track
- L89 _public prototype_ `~FAnimationMixerLayerModel();`
- L92 _public prototype_ `void RefreshLayout(bool bChildrenNeedLayout = true);` — Refreshes the layout of the layer model including all child sections/outliner items
- L94 _public function_ `UMovieSceneAnimationMixerLayer* GetLayer() const`
- L96 _public function_ `UMovieSceneAnimationMixerTrack* GetParentMixerTrack() const`
- L98 _public function_ `bool HasChildTrack() const`
- L100 _public function_ `UMovieSceneTrack* GetChildTrack() const`
- L103 _public prototype_ `virtual UMovieSceneTrack* GetTrack() const override;` — ~ ITrackExtension
- L104 _public prototype_ `virtual TSharedPtr<ISequencerTrackEditor> GetTrackEditor() const override;`
- L107 _public prototype_ `virtual int32 GetRowIndex() const override;` — ~ ITrackRowExtension
- L108 _public prototype_ `virtual bool SetRowIndex(int32 InRowIndex) override;`
- L109 _public prototype_ `virtual UMovieSceneTrack* GetParentTrack() const override;`
- L112 _public prototype_ `virtual FViewModelChildren GetSectionModels() override;` — ~ ISectionOwnerExtension
- L115 _public prototype_ `virtual FViewModelChildren GetTopLevelChannels() override;` — ~ ITopLevelChannelHolderExtension
- L118 _public prototype_ `virtual FOutlinerSizing GetOutlinerSizing() const override;` — ~ IOutlinerExtension
- L119 _public prototype_ `virtual TSharedPtr<SWidget> CreateOutlinerViewForColumn(const FCreateOutlinerViewParams& InParams, const FName& InColumnName) override;`
- L120 _public prototype_ `virtual FSlateFontInfo GetLabelFont() const override;`
- L121 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L122 _public prototype_ `virtual FText GetLabel() const override;`
- L123 _public prototype_ `virtual FSlateColor GetLabelColor() const override;`
- L124 _public prototype_ `virtual FText GetLabelToolTipText() const override;`
- L127 _public prototype_ `virtual bool IsDimmed() const override;` — ~ IDimmableExtension
- L130 _public prototype_ `virtual bool IsResizable() const override;` — ~ IResizableExtension
- L131 _public prototype_ `virtual void Resize(float NewSize) override;`
- L134 _public prototype_ `virtual ELockableLockState GetLockState() const override;` — ~ ILockableExtension Interface
- L135 _public prototype_ `virtual void SetIsLocked(bool bIsLocked) override;`
- L138 _public prototype_ `virtual const UMovieSceneCondition* GetCondition() const override;` — ~ IConditionableExtension Interface
- L139 _public prototype_ `virtual EConditionableConditionState GetConditionState() const override;`
- L140 _public prototype_ `virtual void SetConditionEditorForceTrue(bool bEditorForceTrue) override;`
- L143 _public prototype_ `virtual FTrackAreaParameters GetTrackAreaParameters() const override;` — ~ ITrackAreaExtension
- L144 _public prototype_ `virtual FViewModelVariantIterator GetTrackAreaModelList() const override;`
- L145 _public prototype_ `virtual FViewModelVariantIterator GetTopLevelChildTrackAreaModels() const override;`
- L148 _public prototype_ `virtual void CreateCurveModels(TArray<TUniquePtr<FCurveModel>>& OutCurveModels) override;` — ~ ICurveEditorTreeItem
- L151 _public prototype_ `virtual void GetIdentifierForGrouping(TStringBuilder<128>& OutString) const override;` — ~ IGroupableIdentifier
- L154 _public prototype_ `virtual bool CanRename() const override;` — ~ IRenameableExtension
- L155 _public prototype_ `virtual void Rename(const FText& NewName) override;`
- L156 _public prototype_ `virtual bool IsRenameValidImpl(const FText& NewName, FText& OutErrorMessage) const override;`
- L159 _public prototype_ `virtual void SortChildren() override;` — ~ ISortableExtension
- L160 _public prototype_ `virtual FSortingKey GetSortingKey() const override;`
- L161 _public prototype_ `virtual void SetCustomOrder(int32 InCustomOrder) override;`
- L164 _public prototype_ `virtual bool CanDrag() const override;` — ~ IDraggableOutlinerExtension
- L167 _public prototype_ `virtual bool IsDeactivated() const override;` — ~ FEvaluableOutlinerItemModel
- L168 _public prototype_ `virtual void SetIsDeactivated(bool bInIsDeactivated) override;`
- L171 _public prototype_ `virtual bool HasCurves() const override;` — ~ FOutlinerItemModel
- L172 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder) override;`
- L173 _public prototype_ `virtual bool GetDefaultExpansionState() const override;`
- L174 _public prototype_ `virtual void BuildSidebarMenu(FMenuBuilder& MenuBuilder) override;`
- L175 _public prototype_ `virtual void SetExpansion(bool bInIsExpanded) override;`
- L178 _public prototype_ `virtual bool CanDelete(FText* OutErrorMessage) const override;` — ~ IDeletableExtension
- L179 _public prototype_ `virtual void Delete() override;`
- L182 _public prototype_ `virtual bool IsMuted() const override;` — ~ IMutableExtension
- L183 _public prototype_ `virtual void SetIsMuted(bool bIsMuted) override;`
- L186 _public prototype_ `virtual bool IsSolo() const override;` — ~ ISoloableExtension
- L187 _public prototype_ `virtual void SetIsSoloed(bool bIsSoloed) override;`
- L190 _public prototype_ `virtual void OnConstruct() override;` — ~ FViewModel interface
- L199 _private prototype_ `bool GetSavedExpansionState() const;` — Query the saved expansion state from editor data without checking for children. This is needed during layout because IsExpanded() checks for children, but we're in the process of building them.
- L202 _private member_ `FViewModelListHead SectionList{EViewModelListType::TrackArea};` — A second children list for the sections inside this layer
- L203 _private member_ `FViewModelListHead TopLevelChannelList{FTrackModel::GetTopLevelChannelGroupType()};`
- L206 _private member_ `TWeakObjectPtr<UMovieSceneAnimationMixerTrack> WeakParentTrack;` — The parent animation mixer track
- L209 _private member_ `TWeakObjectPtr<UMovieSceneAnimationMixerLayer> WeakLayer;` — The layer data object
- L212 _private member_ `TWeakObjectPtr<UMovieSceneTrack> WeakChildTrack;` — Child track if this layer contains one (e.g., Control Rig)
- L215 _private member_ `TSharedPtr<ISequencerTrackEditor> TrackEditor;` — Track editor for the child track or parent track
- L217 _private member_ `TOptional<int32> PreviousLayoutNumSections = TOptional<int32>();`
- L220 _private member_ `TOptional<int32> PreviousLayoutNumRows = TOptional<int32>();` — Populated row count from the previous child-track layout; a change forces a relayout.
- L223 _private prototype_ `void OnChildTrackChanged();` — Handles lightweight decoration sync when child track changes
- L224 _private member_ `FDelegateHandle ChildTrackChangedHandle;`
- L227 _private prototype_ `void OnLayerChanged();` — Handles decoration sync when layer changes
- L228 _private member_ `FDelegateHandle LayerChangedHandle;`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerEditor/Public/MVVM/AnimationMixerTrackModel.h` (Public)


#### struct `UE::Sequencer::FAnimMixerDropPreview`  
`struct FAnimMixerDropPreview`  
_L22-46_
- desc: Drop preview data for dragging sections in Animation Mixer track
- L31 _public member_ `EZone Zone = EZone::OntoLayer;`
- L32 _public member_ `int32 TargetRowIndex = INDEX_NONE;`
- L33 _public member_ `float VirtualTop = 0.0f;`
- L34 _public member_ `float VirtualBottom = 0.0f;`
- L35 _public member_ `TRange<FFrameNumber> SectionFrameRange;`
- L37 _public function_ `bool operator==(const FAnimMixerDropPreview& Other) const`
- L42 _public function_ `bool operator!=(const FAnimMixerDropPreview& Other) const`

#### enum `UE::Sequencer::FAnimMixerDropPreview::EZone`  
`enum class EZone`  
_L24-29_
- L26 _public enumerator_ `AboveLayer` — Insert new layer above target
- L27 _public enumerator_ `BelowLayer` — Insert new layer below target
- L28 _public enumerator_ `OntoLayer` — Drop sections onto existing layer

#### class `UE::Sequencer::FAnimationMixerTrackModel`  
`class FAnimationMixerTrackModel : public FTrackModel`  
_L53-108_
- inherits: `FTrackModel`
- desc: Custom track model for Animation Mixer tracks. Supports hierarchical child tracks (e.g., control rig tracks) that render as nested tracks under the anim mixer track. Uses preview-based dragging with outliner-style drop indicators.
- L56 _public prototype_ `UE_SEQUENCER_DECLARE_CASTABLE(FAnimationMixerTrackModel, FTrackModel);`
- L58 _public prototype_ `explicit FAnimationMixerTrackModel(UMovieSceneTrack* Track);`
- L61 _public prototype_ `virtual void OnConstruct() override;` — ~ FViewModel interface
- L64 _public prototype_ `virtual FViewModelVariantIterator GetTopLevelChildTrackAreaModels() const override;` — ~ ITrackAreaExtension
- L67 _public prototype_ `virtual bool IsDeactivated() const override;` — ~ FEvaluableOutlinerItemModel
- L68 _public prototype_ `virtual void SetIsDeactivated(bool bInIsDeactivated) override;`
- L71 _public prototype_ `virtual void OnBeginSectionVerticalDrag() override;` — ~ ISectionDragOwnerExtension - Preview-based drag with outliner-style drop indicators
- L72 _public prototype_ `virtual bool OnSectionVerticalDrag(const FSectionVerticalDragContext& Context) override;`
- L73 _public prototype_ `virtual void OnEndSectionVerticalDrag(const FSectionVerticalDragContext& Context) override;`
- L74 _public prototype_ `virtual int32 OnPaintSectionDragPreview( const FGeometry& TrackAreaGeometry, const class FVirtualTrackArea& VirtualTrackArea, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L84 _protected prototype_ `virtual void ForceUpdate() override;`
- L87 _protected prototype_ `virtual void ShiftRowsDownFromIndex(int32 StartIndex, const TSet<UMovieSceneSection*>& ExcludeSections) override;` — Override section drag functions to consider both sections AND child tracks
- L91 _private prototype_ `bool IsRowOccupiedByChildTrack(int32 RowIndex) const;` — Check if a row is occupied by a child track (prevents section drops on child track layers)
- L94 _private prototype_ `TOptional<FAnimMixerDropPreview> ComputeDropPreview(const FSectionVerticalDragContext& Context) const;` — Compute drop preview without modifying the track
- L97 _private prototype_ `bool ApplyDropPreview(const FAnimMixerDropPreview& Preview, const FSectionVerticalDragContext& Context);` — Apply the cached preview to actually move sections
- L100 _private member_ `bool bIsInDrag = false;` — Track if we're currently in a drag operation (to prevent view mode changes during drag)
- L103 _private member_ `mutable TOptional<FAnimMixerDropPreview> CachedPreview;` — Cached drop preview (only valid during drag)
- L106 _private member_ `FViewModelListHead LayerBarList;` — Layer bar shown when the track is collapsed
- L107 _private member_ `TSharedPtr<FLayerBarModel> LayerBar;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)
