# Plugins / SequencerAnimTools

- module root: `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools`
- headers: 11; symbols: 770
- symbol kinds: class=28, delegate=1, enum=4, enumerator=18, function=130, macro=1, member=243, namespace=24, prototype=294, struct=27
- PrivateDependencyModuleNames: Constraints, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, Engine, InputCore, InteractiveToolsFramework, LevelEditor, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneTools, MovieSceneTracks, Sequencer, UnrealEd
- PublicDependencyModuleNames: ControlRig, ControlRigEditor, Core, Slate, SlateCore

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Private/Sequencer/MotionTrailMovieSceneKey.h` (Private)


#### enum `UE::SequencerAnimTools::ETransformChannel`  
`enum class ETransformChannel : uint8`  
_L28-40_
- L30 _public enumerator_ `TranslateX = 0`
- L31 _public enumerator_ `TranslateY = 1`
- L32 _public enumerator_ `TranslateZ = 2`
- L33 _public enumerator_ `RotateX = 3`
- L34 _public enumerator_ `RotateY = 4`
- L35 _public enumerator_ `RotateZ = 5`
- L36 _public enumerator_ `ScaleX = 6`
- L37 _public enumerator_ `ScaleY = 7`
- L38 _public enumerator_ `ScaleZ = 8`
- L39 _public enumerator_ `MaxChannel = 8`

#### enum `UE::SequencerAnimTools::EGetKeyFrom`  
`enum class EGetKeyFrom`  
_L42-46_
- L44 _public enumerator_ `FromComponentDelta`
- L45 _public enumerator_ `FromTrailCache`

#### struct `UE::SequencerAnimTools::FTrailKeyInfo`  
`struct FTrailKeyInfo`  
_L48-64_
- L50 _public prototype_ `FTrailKeyInfo(const FFrameNumber InFrameNumber, UMovieSceneSection* InSection, FMovieSceneTransformTrail* InOwningTrail);`
- L54 _public prototype_ `void UpdateKeyTransform(EGetKeyFrom UpdateType);` — Re-eval transform or use given one
- L57 _public member_ `FTransform Transform;` — Key Specific info
- L58 _public member_ `FTransform ParentTransform;`
- L59 _public member_ `TMap<ETransformChannel, FKeyHandle> IdxMap;`
- L60 _public member_ `FFrameNumber FrameNumber;`
- L61 _public member_ `bool bDirty;`
- L63 _public member_ `FMovieSceneTransformTrail* OwningTrail;`

#### class `UE::SequencerAnimTools::FSortedKeys`  
`class FSortedKeys`  
_L68-208_
- desc: This class is a limtited version of TSortedMap that also exposes FindIndex and a new FindFromIndex function in order to get direct access to the hidden sorted array.
- L78 _public function_ `int32 FindIndex(FFrameNumber Key) const`
- L83 _public function_ `const TUniquePtr<FTrailKeyInfo>* Find(FFrameNumber Key) const`
- L93 _public function_ `int32 FindIndex(FFrameNumber Key)`
- L97 _public function_ `TUniquePtr<FTrailKeyInfo>* FindFromIndex(int32 Index)`
- L105 _public function_ `TUniquePtr<FTrailKeyInfo>* Find(FFrameNumber Key)`
- L114 _public function_ `bool Contains(FFrameNumber Key) const`
- L123 _public function_ `void Empty(int32 ExpectedNumElements = 0)`
- L128 _public function_ `void Reset()`
- L133 _public function_ `void Shrink()`
- L138 _public function_ `void Reserve(int32 Number)`
- L143 _public function_ `bool IsEmpty() const`
- L148 _public function_ `int32 Num() const`
- L153 _public function_ `TUniquePtr<FTrailKeyInfo>& FindChecked(FFrameNumber Key)`
- L160 _public function_ `const TUniquePtr<FTrailKeyInfo>& FindChecked(FFrameNumber Key) const`
- L167 _public function_ `TUniquePtr<FTrailKeyInfo>& operator[](FFrameNumber Key)`
- L171 _public function_ `const TUniquePtr<FTrailKeyInfo>& operator[](FFrameNumber Key) const`
- L176 _public function_ `FORCEINLINE TPair<FFrameNumber, TUniquePtr<FTrailKeyInfo>>* AllocateMemoryForEmplace(FFrameNumber&& InKey)`
- L188 _public function_ `TUniquePtr<FTrailKeyInfo>& Add(FFrameNumber &&InKey, TUniquePtr<FTrailKeyInfo> && InValue)`
- L197 _public function_ `void GetAllKeys(TArray<FTrailKeyInfo*>& OutKeys)`
- L207 _public member_ `TArray < TPair<FFrameNumber, TUniquePtr<FTrailKeyInfo>> > Keys;`

#### struct `UE::SequencerAnimTools::FSortedKeys::FKeyForward`  
`struct FKeyForward`  
_L70-76_
- L72 _public function_ `FORCEINLINE const FFrameNumber& operator()(const TPair<FFrameNumber, TUniquePtr<FTrailKeyInfo>>& Pair) const`

#### class `UE::SequencerAnimTools::FMotionTraiMovieScenelKeyTool`  
`class FMotionTraiMovieScenelKeyTool`  
_L210-258_
- L213 _public function_ `FMotionTraiMovieScenelKeyTool(FMovieSceneTransformTrail* InOwningTrail) : OwningTrail(InOwningTrail), SelectedKeysTransform(FTransform::Identity)`
- L216 _public prototype_ `~FMotionTraiMovieScenelKeyTool() = default;`
- L218 _public prototype_ `void Render(const FGuid& Guid, const FSceneView* View, FPrimitiveDrawInterface* PDI, bool bTrailIsEvaluating);`
- L219 _public prototype_ `void DrawHUD(const FSceneView* View, FCanvas* Canvas);`
- L221 _public prototype_ `bool HandleClick(const FGuid& Guid, FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, FInputClick Click);`
- L222 _public function_ `void StartDragging()`
- L223 _public prototype_ `bool IsSelected(FVector& OutVectorPosition, FQuat& OutRotation) const;`
- L224 _public prototype_ `void GetSelectedKeyPositions(TArray<FVector>& OutPositions) const;`
- L225 _public prototype_ `bool IsSelected() const;`
- L226 _public prototype_ `void OnSectionChanged();`
- L227 _public prototype_ `void UpdateKeys();`
- L228 _public prototype_ `void UpdateViewRange(const TRange<FFrameNumber>& InViewRange);`
- L229 _public prototype_ `void ClearSelection();`
- L230 _public prototype_ `FTrailKeyInfo* FindKey(const FFrameNumber& FrameNumber) const;`
- L231 _public prototype_ `TArray<FFrameNumber> SelectedKeyTimes() const;`
- L232 _public prototype_ `void SelectKeyTimes(const TArray<FFrameNumber>& Frames, bool KeepSelection);`
- L233 _public function_ `void SelectKeyInfo(FTrailKeyInfo* KeyInfo)`
- L234 _public function_ `FTransform GetSelectedKeysTransform() const`
- L235 _public prototype_ `void TranslateSelectedKeys(bool bRight);`
- L236 _public prototype_ `void DeleteSelectedKeys();`
- L237 _public function_ `bool IsAllSelected() const`
- L238 _public function_ `void GetAllKeys(TArray<FTrailKeyInfo*>& OutKeys)`
- L239 _public function_ `const FSortedKeys& GetSortedKeys()const`
- L240 _public prototype_ `TArray<FFrameNumber> GetTimesFromModifiedTimes(const TArray<FFrameNumber>& Frames, const FFrameNumber& LastFrame, const FFrameNumber& Step);`
- L242 _protected member_ `TRange<FFrameNumber> CachedViewFrameRange;`
- L243 _protected prototype_ `void UpdateSelectedKeysTransform() const;`
- L244 _protected prototype_ `bool ShouldRebuildKeys();`
- L245 _protected prototype_ `void BuildKeys();`
- L246 _protected prototype_ `void DirtyKeyTransforms();`
- L247 _protected prototype_ `TArray<FKeyHandle> GetSelectedKeyHandles(FMovieSceneChannel* Channel);`
- L249 _protected member_ `FSortedKeys Keys;`
- L250 _protected member_ `TSet<FTrailKeyInfo*> CachedSelection;` — current selection
- L252 _protected member_ `FMovieSceneTransformTrail* OwningTrail;`
- L253 _protected member_ `mutable FTransform SelectedKeysTransform;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SequencerAnimTools` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L20 _namespace_ `namespace SequencerAnimTools` (scope `UE`)

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Private/Sequencer/MovieSceneTransformTrail.h` (Private)


#### struct `UE::SequencerAnimTools::FCachedGuidsPerSignedObject`  
`struct FCachedGuidsPerSignedObject`  
_L28-32_
- desc: caching of tracks ans sections to handle signature changes.
- L30 _public member_ `TWeakObjectPtr<const UMovieSceneSignedObject> SignedObject;`
- L31 _public member_ `FGuid CachedGuid;`

#### struct `UE::SequencerAnimTools::FCachedTrackAndSections`  
`struct FCachedTrackAndSections`  
_L34-38_
- L36 _public member_ `FCachedGuidsPerSignedObject Track;`
- L37 _public member_ `TMap<TWeakObjectPtr<const UMovieSceneSection>, FCachedGuidsPerSignedObject> Sections;`

#### struct `UE::SequencerAnimTools::FOptionalParentSpace`  
`struct FOptionalParentSpace`  
_L41-57_
- desc: space that a trail may be in, includes Actor/ optional component and it's sequencer tracks/sections
- L43 _public function_ `FOptionalParentSpace() : bIsValid(false)`
- L45 _public member_ `UE::AIE::FActorAndWorldTransforms ParentSpace;` — this contains the actor/component
- L47 _public member_ `bool bIsValid;`
- L48 _public member_ `FName ComponentName;`
- L49 _public member_ `FGuid SpaceBindingID;`
- L50 _public member_ `UE::AIE::FSequencerTransformDependencies SpaceTransformDependencies;`
- L53 _public prototype_ `void SetSpace(TSharedPtr<ISequencer>& InSequencerPtr, AActor* InActor, const FName& InComponentName);` — set space and make it valid
- L54 _public prototype_ `void ClearSpace();`
- L56 _public prototype_ `static USceneComponent* GetComponentFromName(const AActor* InActor, const FName& InComponentName);`

#### struct `UE::SequencerAnimTools::FDrawCacheData`  
`struct FDrawCacheData`  
_L59-64_
- L61 _public member_ `TArray<FVector> PointsToDraw;`
- L62 _public member_ `TArray<FFrameNumber> Frames;`
- L63 _public member_ `TArray<FLinearColor> Color;`

#### class `UE::SequencerAnimTools::FMovieSceneTransformTrail`  
`class FMovieSceneTransformTrail : public FTrail`  
_L65-206_
- inherits: `FTrail`
- L69 _public prototype_ `FMovieSceneTransformTrail(const FGuid& InBindingID, USceneComponent* SceneComponent, const bool bInIsVisible, TWeakObjectPtr<UMovieSceneTrack> InWeakTrack, TSharedPtr<ISequencer> InSequencer);`
- L70 _public prototype_ `~FMovieSceneTransformTrail();`
- L74 _public prototype_ `virtual FTrailCurrentStatus UpdateTrail(const FNewSceneContext& NewSceneContext) override;`
- L75 _public prototype_ `virtual void Interp(const FFrameNumber& Time, FTransform& OutTransform, FTransform& OutParentTransform) override;`
- L76 _public prototype_ `virtual void UpdateFinished(const TRange<FFrameNumber>& UpdatedRange, const TArray<int32>& IndicesToCalcluate, bool bDoneCalculating) override;`
- L77 _public prototype_ `virtual void AddImportantTimes(TSet<FFrameNumber>& InOutImportantTimes) override;`
- L78 _public function_ `virtual FTransform GetOffsetTransform() const override`
- L79 _public prototype_ `virtual void ClearOffsetTransform() override;`
- L80 _public prototype_ `virtual void SetOffsetMode() override;`
- L81 _public prototype_ `virtual bool GetOffsetMode() const override;`
- L83 _public prototype_ `virtual FTransform GetParentSpaceTransform() const override;`
- L84 _public prototype_ `virtual void SetSpace(AActor* InActor, const FName& InComponentName) override;`
- L85 _public function_ `virtual void ClearSpace() override`
- L86 _public prototype_ `virtual void ClearCachedData() override;`
- L87 _public prototype_ `virtual void ReadyToDrawTrail(FColorState& ColorState, const FCurrentFramesInfo* InCurrentFramesInfo, bool bIsEvaluating, bool bIsPinned) override;`
- L88 _public prototype_ `virtual void ActorChanged(AActor* InActor) override;`
- L90 _public prototype_ `virtual void Render(const FGuid& Guid, const FSceneView* View, FPrimitiveDrawInterface* PDI, bool bTrailIsEvaluating) override;`
- L91 _public prototype_ `virtual void RenderEvaluating(const FGuid& Guid, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L92 _public prototype_ `virtual void DrawHUD(const FSceneView* View, FCanvas* Canvas) override;`
- L94 _public prototype_ `virtual bool HandleClick(const FGuid& Guid, FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, FInputClick Click) override;`
- L95 _public prototype_ `virtual bool IsAnythingSelected() const override;`
- L96 _public prototype_ `virtual bool IsAnythingSelected(FVector& OutVectorPosition, FQuat& OutRotation)const override;`
- L97 _public prototype_ `virtual bool IsAnythingSelected(TArray<FVector>& OutVectorPositions)const override;`
- L98 _public prototype_ `virtual bool IsTrailSelected() const override;`
- L99 _public prototype_ `virtual bool StartTracking() override;`
- L100 _public prototype_ `virtual bool ApplyDelta(const FVector& Pos, const FRotator& Rot, const FVector& WidgetLocation, bool bApplyToOffset) override;`
- L101 _public prototype_ `virtual bool EndTracking() override;`
- L102 _public prototype_ `virtual bool IsTracking() const override;`
- L104 _public prototype_ `virtual void HasStartedEvaluating() override;`
- L105 _public prototype_ `virtual void TranslateSelectedKeys(bool bRight) override;`
- L106 _public prototype_ `virtual void DeleteSelectedKeys() override;`
- L107 _public prototype_ `virtual void SelectNone() override;`
- L108 _public function_ `virtual int32 GetChannelOffset()const`
- L109 _public prototype_ `virtual TArray<FFrameNumber> GetKeyTimes() const override;`
- L110 _public prototype_ `virtual TArray<FFrameNumber> GetSelectedKeyTimes() const override;`
- L111 _public prototype_ `virtual void ForceEvaluateNextTick() override;`
- L112 _public prototype_ `virtual void GetColor(const FFrameNumber& CurrentTime, FColorState& InOutColorState) override;`
- L113 _public prototype_ `virtual bool HandleObjectsChanged(const TMap<UObject*, UObject*>& ReplacementMap) override;`
- L118 _public prototype_ `virtual void UpdateNeedsEvaluation(const FGuid& InTrailGuid, FSequencerTrailHierarchy* SequencerHierarchy);` — New Virtuals
- L120 _public function_ `TSharedPtr<ISequencer> GetSequencer() const`
- L121 _public function_ `FGuid GetCachedHierarchyGuid() const`
- L122 _public prototype_ `UMovieSceneSection* GetSection() const;`
- L124 _public function_ `void SetOffsetTransform(const FTransform& InOffsetTransform)`
- L125 _public function_ `const UE::AIE::FSequencerTransformDependencies& GetTransformDependencies()`
- L128 _public member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L131 _protected prototype_ `virtual bool HandleAltClick(FEditorViewportClient* InViewportClient, HNewMotionTrailProxy* Proxy, FInputClick Click);`
- L134 _protected prototype_ `void InternalDrawTrail(const FGuid& Guid, const FSceneView* View, FPrimitiveDrawInterface* PDI, const FDrawCacheData& InDrawData, bool bHitTesting, bool bTrailIsEvaluating) const;` — internal draw trail
- L137 _protected prototype_ `TOptional<FLinearColor> GetOverrideColor() const;` — if selected or selected and offset mode we draw different colors
- L141 _protected prototype_ `virtual void CheckAndUpdateObjects();` — do to spawnables, etc.. objects that we have may have been deleted or recreated, need to update them if they have
- L142 _protected prototype_ `static TArray<UObject*> GetBoundObjects(TSharedPtr<ISequencer>& InSequencerPtr, const FGuid& InGuid);`
- L144 _protected prototype_ `void CalculateUpdatedOffset();`
- L147 _protected member_ `bool bIsSelected;` — some interactive states/modes
- L148 _protected member_ `bool bIsOffsetMode;`
- L149 _protected member_ `FVector SelectedPos;`
- L150 _protected member_ `FQuat SelectedRotation;`
- L151 _protected member_ `bool bIsTracking;`
- L152 _protected member_ `TOptional<bool> bSetShowWidget;`
- L155 _protected member_ `TUniquePtr<FMotionTraiMovieScenelKeyTool> KeyTool;` — main tool for adjusting keys
- L158 _protected member_ `mutable FTransform PreviousParentSpaceTM = FTransform::Identity;` — previous parent space
- L160 _protected member_ `FGuid CachedHierarchyGuid;` — cached guid in the hierarchy
- L163 _protected prototype_ `bool TrailOrSpaceHasChanged();`
- L164 _protected prototype_ `void ExitOffsetMode();`
- L165 _protected prototype_ `bool BindingHasChanged(const FGuid& InBinding, const USceneComponent* InComponent, UE::AIE::FSequencerTransformDependencies& InDependencies);`
- L168 _protected member_ `FGuid BindingID;`
- L169 _protected member_ `TWeakObjectPtr<UMovieSceneTrack> MainTrack;`
- L170 _protected member_ `UE::AIE::FSequencerTransformDependencies TransformDependencies;`
- L172 _protected member_ `FTransform OffsetTransform;`
- L174 _protected member_ `TSharedPtr<UE::AIE::FArrayOfTransforms> CalculatedArrayOfTransforms;` — transforms calculated from evaluating control rigs and actors
- L176 _protected member_ `TSharedPtr<UE::AIE::FArrayOfTransforms> ArrayOfTransforms;` — calculated transforms plus any offset + parent
- L178 _protected member_ `TSharedPtr<UE::AIE::FArrayOfTransforms> ParentArrayOfTransforms;` — parent space transforms (optional)
- L179 _protected member_ `const FCurrentFramesInfo* CurrentFramesInfo;`
- L182 _protected member_ `FOptionalParentSpace ParentSpace;` — optional parent space
- L184 _protected member_ `mutable FDrawCacheData CachedDrawData;` — cached drawing data
- L186 _protected member_ `FDrawCacheData PreviousCachedDrawData;` — old cached draw data used to draw the trail when we are updating it
- L188 _protected member_ `TArray<FLinearColor> CachedHeatMap;` — cached color values for heat map

#### class `UE::SequencerAnimTools::FMovieSceneTransformTrail::FMovieSceneTransformTrailState`  
`class FMovieSceneTransformTrailState : public FTrail::FMotionTrailState`  
_L191-204_
- inherits: `FTrail::FMotionTrailState`
- L194 _public member_ `FGuid BindingID;`
- L195 _public member_ `TWeakObjectPtr<UMovieSceneTrack> MainTrack;`
- L196 _public member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L197 _public member_ `FLinearColor Color;`
- L198 _public member_ `EMotionTrailTrailStyle PinnedStyle;`
- L199 _public member_ `FTransform OffsetTransform;`
- L200 _public member_ `FOptionalParentSpace ParentSpace;`
- L201 _public prototype_ `void SaveFromTrail(const FMovieSceneTransformTrail* InTrail);`
- L202 _public prototype_ `void SetToTrail(FMovieSceneTransformTrail* InTrail) const;`

#### class `UE::SequencerAnimTools::FMovieSceneComponentTransformTrail`  
`class FMovieSceneComponentTransformTrail : public FMovieSceneTransformTrail`  
_L209-247_
- inherits: `FMovieSceneTransformTrail`
- L213 _public function_ `FMovieSceneComponentTransformTrail(const FGuid& InBindingID, USceneComponent* InComponent, const bool bInIsVisible, TWeakObjectPtr<UMovieSceneTrack> InWeakTrack, TSharedPtr<ISequencer> InSequencer) : FMovieSceneTransformTrail(InBindingID, InComponent, bInIsVisible, InWeakTrack, InSequencer), Component(InComponent)`
- L220 _public prototype_ `virtual void UpdateNeedsEvaluation(const FGuid& InTrailGuid, FSequencerTrailHierarchy* SequencerHierarchy) override;` — new
- L221 _public prototype_ `virtual FText GetName() const override;`
- L222 _public prototype_ `virtual TUniquePtr<FMotionTrailState> GetMotionTrailState() const;`
- L223 _public prototype_ `virtual bool HandleObjectsChanged(const TMap<UObject*, UObject*>& ReplacementMap);`
- L227 _private member_ `TWeakObjectPtr<USceneComponent> Component;`
- L229 _private prototype_ `virtual bool StartTracking() override;`
- L230 _private prototype_ `virtual bool ApplyDelta(const FVector& Pos, const FRotator& Rot, const FVector& WidgetLocation, bool bApplyToOffset) override;`
- L231 _private prototype_ `virtual bool EndTracking() override;`
- L234 _protected prototype_ `virtual bool HandleAltClick(FEditorViewportClient* InViewportClient, HNewMotionTrailProxy* Proxy, FInputClick Click) override;`
- L244 _private member_ `bool bStartTracking = false;`

#### class `UE::SequencerAnimTools::FMovieSceneComponentTransformTrail::FMovieSceneComponentTransformTrailState`  
`class FMovieSceneComponentTransformTrailState : public FMovieSceneTransformTrailState`  
_L237-242_
- inherits: `FMovieSceneTransformTrailState`
- L240 _public member_ `TWeakObjectPtr<USceneComponent> Component;`
- L241 _public prototype_ `virtual void RestoreTrail(FTrailHierarchy* TrailHierarchy) override;`

#### class `UE::SequencerAnimTools::FMovieSceneSocketTransformTrail`  
`class FMovieSceneSocketTransformTrail : public FMovieSceneTransformTrail`  
_L249-293_
- inherits: `FMovieSceneTransformTrail`
- L253 _public function_ `FMovieSceneSocketTransformTrail(const FGuid& InBindingID, USceneComponent* InComponent, const FName& InSocketName, const bool bInIsVisible, TWeakObjectPtr<UMovieSceneTrack> InWeakTrack, TSharedPtr<ISequencer> InSequencer) : FMovieSceneTransformTrail(InBindingID, InComponent, bInIsVisible, InWeakTrack, InSequencer), Component(InComponent), SocketName(InSocketName)`
- L262 _public prototype_ `virtual void UpdateNeedsEvaluation(const FGuid& InTrailGuid, FSequencerTrailHierarchy* SequencerHierarchy) override;` — new
- L263 _public prototype_ `virtual FText GetName() const override;`
- L264 _public prototype_ `virtual TUniquePtr<FMotionTrailState> GetMotionTrailState() const;`
- L265 _public prototype_ `virtual bool HandleObjectsChanged(const TMap<UObject*, UObject*>& ReplacementMap);`
- L270 _private prototype_ `virtual bool StartTracking() override;`
- L271 _private prototype_ `virtual bool ApplyDelta(const FVector& Pos, const FRotator& Rot, const FVector& WidgetLocation, bool bApplyToOffset) override;`
- L272 _private prototype_ `virtual bool EndTracking() override;`
- L273 _private prototype_ `virtual void DrawHUD(const FSceneView* View, FCanvas* Canvas) override;`
- L275 _private prototype_ `virtual bool HandleClick(const FGuid& Guid, FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, FInputClick Click) override;`
- L276 _private prototype_ `virtual bool IsAnythingSelected() const override;`
- L277 _private prototype_ `virtual bool IsAnythingSelected(FVector& OutVectorPosition, FQuat& OutRotation)const override;`
- L282 _protected member_ `TWeakObjectPtr<USceneComponent> Component;`
- L283 _protected member_ `FName SocketName;`

#### class `UE::SequencerAnimTools::FMovieSceneSocketTransformTrail::FMovieSceneSocketTransformTrailState`  
`class FMovieSceneSocketTransformTrailState : public FMovieSceneTransformTrailState`  
_L286-292_
- inherits: `FMovieSceneTransformTrailState`
- L289 _public member_ `TWeakObjectPtr<USceneComponent> Component;`
- L290 _public member_ `FName SocketName;`
- L291 _public prototype_ `virtual void RestoreTrail(FTrailHierarchy* TrailHierarchy) override;`

#### class `UE::SequencerAnimTools::FMovieSceneControlRigTransformTrail`  
`class FMovieSceneControlRigTransformTrail : public FMovieSceneTransformTrail`  
_L295-330_
- inherits: `FMovieSceneTransformTrail`
- L299 _public prototype_ `FMovieSceneControlRigTransformTrail(const FGuid& InBindingID, USceneComponent* SceneComponent, const bool bInIsVisible, TWeakObjectPtr<UMovieSceneTrack> InWeakTrack, TSharedPtr<ISequencer> InSequencer, const FName& InControlName, TSharedPtr<UE::AIE::FArrayOfTransforms>& InParentArrayOfTransforms);`
- L302 _public prototype_ `virtual void UpdateNeedsEvaluation(const FGuid& InTrailGuid, FSequencerTrailHierarchy* SequencerHierarchy) override;`
- L303 _public prototype_ `virtual FText GetName() const override;`
- L304 _public prototype_ `virtual TUniquePtr<FMotionTrailState> GetMotionTrailState() const;`
- L306 _public prototype_ `virtual bool StartTracking() override;`
- L307 _public prototype_ `virtual bool ApplyDelta(const FVector& Pos, const FRotator& Rot, const FVector& WidgetLocation, bool bApplyToOffset) override;`
- L308 _public prototype_ `virtual bool EndTracking() override;`
- L309 _public prototype_ `virtual int32 GetChannelOffset() const override;`
- L312 _protected prototype_ `virtual bool HandleAltClick(FEditorViewportClient* InViewportClient, HNewMotionTrailProxy* Proxy, FInputClick Click) override;`
- L315 _private member_ `bool bUseKeysForTrajectory = false;` — on when interatively moving
- L316 _private member_ `bool bStartTracking = false;`
- L318 _private member_ `FName ControlName;`

#### class `UE::SequencerAnimTools::FMovieSceneControlRigTransformTrail::FMovieSceneControlRigTransformTrailState`  
`class FMovieSceneControlRigTransformTrailState : public FMovieSceneTransformTrailState`  
_L321-328_
- inherits: `FMovieSceneTransformTrailState`
- L324 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> Owner;`
- L325 _public member_ `FName ControlName;`
- L326 _public prototype_ `virtual void RestoreTrail(FTrailHierarchy* TrailHierarchy) override;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace SequencerAnimTools` (scope `UE`)

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Private/Sequencer/SequencerTrailHierarchy.h` (Private)


#### enum `UE::SequencerAnimTools::EBindingVisibilityState`  
`enum class EBindingVisibilityState`  
_L36-40_
- L38 _public enumerator_ `AlwaysVisible`
- L39 _public enumerator_ `VisibleWhenSelected`

#### class `UE::SequencerAnimTools::FSequencerTrailHierarchy`  
`class FSequencerTrailHierarchy : public FTrailHierarchy`  
_L42-149_
- inherits: `FTrailHierarchy`
- L45 _public prototype_ `FSequencerTrailHierarchy(TWeakPtr<ISequencer> InWeakSequencer);`
- L48 _public prototype_ `void EvaluateActor(const FGuid& InKey, FActorForWorldTransforms& InActor,TSharedPtr<UE::AIE::FArrayOfTransforms>& WorldTransforms, TSharedPtr<UE::AIE::FArrayOfTransforms>& ParentWorldTransforms);` — New
- L49 _public prototype_ `void EvaluateControlRig(const FGuid& InKey, UControlRig* InControlRig, const FName& InControlName, TSharedPtr<UE::AIE::FArrayOfTransforms>& WorldTransforms);`
- L52 _public prototype_ `virtual void Initialize() override;` — FTrailHierarchy interface
- L53 _public prototype_ `virtual void Destroy() override;`
- L54 _public function_ `virtual ITrailHierarchyRenderer* GetRenderer() const override`
- L55 _public prototype_ `virtual FFrameNumber GetFramesPerFrame() const override;`
- L56 _public prototype_ `virtual FFrameNumber GetFramesPerSegment() const override;`
- L57 _public prototype_ `virtual const FCurrentFramesInfo* GetCurrentFramesInfo() const override;`
- L58 _public prototype_ `virtual bool CheckForChanges() override;`
- L60 _public prototype_ `virtual void RemoveTrail(const FGuid& InTrailGuid) override;`
- L61 _public prototype_ `virtual void Update() override;`
- L62 _public prototype_ `virtual void CalculateEvalRangeArray() override;`
- L63 _public prototype_ `virtual bool IsTrailEvaluating(const FGuid& InTrailGuid, bool bIndirectlyOnly) const override;`
- L67 _public prototype_ `void OnBindingVisibilityStateChanged(UObject* BoundObject, const EBindingVisibilityState VisibilityState);`
- L69 _public prototype_ `void OnActorChangedSomehow(AActor* InActor);` — called when added moved, deleted, added, all of which may need a refresh of a motion trail
- L70 _public prototype_ `void OnActorsChangedSomehow(TArray<AActor*>& InActors);`
- L72 _public prototype_ `virtual FFrameNumber GetLocalTime() const override;`
- L74 _public prototype_ `FGuid AddComponentToHierarchy(const FGuid& InBindingGuid, USceneComponent* CompToAdd, UMovieScene3DTransformTrack* TransformTrack);`
- L75 _public prototype_ `FGuid AddControlRigTrail(USkeletalMeshComponent* Component, UControlRig* ControlRig, UMovieSceneControlRigParameterTrack* CRTrack, const FName& ControlName);`
- L76 _public prototype_ `FGuid PinComponent(USceneComponent* InSceneComponent, FName InSocketName);`
- L82 _private prototype_ `void UpdateSequencerBindings(const TArray<FGuid>& SequencerBindings, TFunctionRef<void(UObject*, FTrail*, FGuid)> OnUpdated);`
- L83 _private prototype_ `void UpdateViewAndEvalRange();`
- L85 _private prototype_ `void RegisterControlRigDelegates(USkeletalMeshComponent* Component, UMovieSceneControlRigParameterTrack* CRParameterTrack);`
- L87 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L88 _private member_ `TMap<UObject*, FGuid> ObjectsTracked;`
- L89 _private member_ `TMap<USceneComponent*, TMap<FName, FGuid>> SocketsTracked;`
- L97 _private member_ `TMap<UControlRig*, FControlMapAndTransforms> ControlsTracked;`
- L101 _private member_ `TUniquePtr<FTrailHierarchyRenderer> HierarchyRenderer;`
- L103 _private member_ `FDelegateHandle OnActorAddedToSequencerHandle;`
- L104 _private member_ `FDelegateHandle OnSelectionChangedHandle;`
- L105 _private member_ `FDelegateHandle OnViewOptionsChangedHandle;`
- L106 _private member_ `FDelegateHandle OnObjectsReplacedHandle;`
- L113 _private member_ `TMap<UMovieSceneControlRigParameterTrack*, FControlRigDelegateHandles> ControlRigDelegateHandles;`
- L117 _private member_ `TArray<UE::AIE::FActorAndWorldTransforms> EvaluatingActors;` — new evaluate setup.. this is what we are evaluating...
- L118 _private member_ `TMap<UControlRig*, UE::AIE::FControlRigAndWorldTransforms> EvaluatingControlRigs;`
- L119 _private member_ `TSet<FGuid> EvaluatingTrails;`
- L122 _private member_ `FCurrentFramesInfo CurrentFramesInfo;` — current frames
- L124 _private prototype_ `void EvaluateSequencerAndSetTransforms();`
- L126 _private member_ `static TArray<TUniquePtr <FTrail::FMotionTrailState >> PreviouslyPinnedTrails;`
- L128 _public prototype_ `void PinTrail(FGuid InGuid);`
- L132 _private member_ `FGuid LastValidMovieSceneGuid;` — cached guid to check for updates
- L134 _private member_ `UE::Widget::EWidgetMode SavedWidgetMode;` — for offset mode
- L135 _private member_ `ECoordSystem SavedCoordSystem;`
- L137 _protected prototype_ `void ClearSelection();`
- L138 _protected prototype_ `void RegisterMotionTrailOptionDelegates();`
- L139 _protected prototype_ `void UnRegisterMotionTrailOptionDelegates();`
- L140 _protected prototype_ `void OnPinSelection(ETrailCategory Category);`
- L141 _protected prototype_ `void OnUnPinSelection(ETrailCategory Category);`
- L142 _protected prototype_ `void OnDeleteAllPinned(ETrailCategory Category);`
- L143 _protected prototype_ `void OnPinComponent(USceneComponent* InSceneComponent, FName SocketName);`
- L144 _protected prototype_ `void OnDeletePinned(FGuid InGuid);`
- L145 _protected prototype_ `void OnPutPinnedInSpace(FGuid InGuid, AActor* InActor, FName InComponentName);`
- L146 _protected prototype_ `void OnSetLinearColor(FGuid InGuid, FLinearColor Color);`
- L147 _protected prototype_ `void OnSetHasOffset(FGuid InGuid, bool bOffset);`

#### struct `UE::SequencerAnimTools::FSequencerTrailHierarchy::FControlMapAndTransforms`  
`struct FControlMapAndTransforms`  
_L92-96_
- L94 _public member_ `TMap < FName, FGuid> NameToTrail;`
- L95 _public member_ `TSharedPtr<UE::AIE::FArrayOfTransforms> ArrayOfTransforms;`

#### struct `UE::SequencerAnimTools::FSequencerTrailHierarchy::FControlRigDelegateHandles`  
`struct FControlRigDelegateHandles`  
_L108-112_
- L110 _public member_ `FDelegateHandle OnHierarchyModified;`
- L111 _public member_ `FDelegateHandle OnControlSelected;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequencerAnimTools` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequencerAnimTools` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Widget` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L33 _namespace_ `namespace SequencerAnimTools` (scope `UE`)

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Public/BaseSequencerAnimTool.h` (Public)


#### class `UBaseSequencerAnimTool`  
`class UBaseSequencerAnimTool : public UInterface`  
_L18-21_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IBaseSequencerAnimTool`  
`class IBaseSequencerAnimTool`  
_L23-28_
- L26 _private function_ `virtual bool ProcessCommandBindings(const FKey Key, const bool bRepeat) const`

#### struct `FSequencerAnimToolHelpers`  
`struct FSequencerAnimToolHelpers`  
_L30-41_
- L40 _public prototype_ `static void CreateGizmo(const FGizmoData& InData, TObjectPtr <UCombinedTransformGizmo>& OutCombinedGizmo, TObjectPtr<UTransformGizmo>& OutTRSGizmo);`

#### struct `FSequencerAnimToolHelpers::FGizmoData`  
`struct FGizmoData`  
_L32-39_
- L34 _public member_ `void* Owner = nullptr;`
- L35 _public member_ `UInteractiveToolManager* ToolManager = nullptr;`
- L36 _public member_ `UTransformProxy* TransformProxy = nullptr;`
- L37 _public member_ `UInteractiveGizmoManager* GizmoManager= nullptr;`
- L38 _public member_ `FString InstanceIdentifier;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCERANIMTOOLS_API`

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Public/MotionTrailTool.h` (Public)


#### class `FLeftRghtClickBehaviorTarget`  
`class FLeftRghtClickBehaviorTarget: public IClickBehaviorTarget`  
_L39-73_
- inherits: `IClickBehaviorTarget`
- desc: IClickBehaviorTarget Wrapper to handle left and right clicks
- L44 _public function_ `FLeftRghtClickBehaviorTarget()`
- L46 _public member_ `IClickBehaviorTarget* Target = nullptr;`
- L47 _public member_ `bool bIsLeft = true;`
- L49 _public member_ `bool bClicked = false;` — Target will check these and then revert them back after using them.
- L51 _public function_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override`
- L59 _public function_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override`
- L66 _public function_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override`

#### class `UMotionTrailToolBuilder`  
`class UMotionTrailToolBuilder : public UInteractiveToolBuilder`  
_L80-88_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for UMotionTrailTool
- L85 _public function_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override`
- L86 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `FMotionTrailCommands`  
`class FMotionTrailCommands : public TCommands<FMotionTrailCommands>`  
_L90-123_
- inherits: `TCommands<FMotionTrailCommands>`
- L93 _public function_ `FMotionTrailCommands() : TCommands<FMotionTrailCommands>( "MotionTrailCommands", NSLOCTEXT("MotionTrailTool", "MotionTrailCommands", "Motion Trail Commands"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L103 _public prototype_ `virtual void RegisterCommands() override;`
- L104 _public function_ `static const TMap<FName, TArray<TSharedPtr<FUICommandInfo>>>& GetCommands()`
- L111 _public member_ `TSharedPtr<FUICommandInfo> TranslateSelectedKeysLeft;` — Move selected keys one frame left
- L114 _public member_ `TSharedPtr<FUICommandInfo> TranslateSelectedKeysRight;` — Move seleced keys one frame right
- L117 _public member_ `TSharedPtr<FUICommandInfo> FrameSelection;` — Frame the selection
- L120 _public member_ `TSharedPtr<FUICommandInfo> DeselectAll;` — Deselect All
- L122 _public member_ `TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;`

#### class `UMotionTrailTool`  
`class UMotionTrailTool : public UMultiSelectionTool, public IClickBehaviorTarget, public IBaseSequencerAnimTool`  
_L127-278_
- reflection: `UCLASS()`
- inherits: `UMultiSelectionTool,IClickBehaviorTarget,IBaseSequencerAnimTool`
- L134 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos);` — IClickBehaviorTarget interface
- L135 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos);`
- L138 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IModifierToggleBehaviorTarget implementation, inherited through IClickBehaviorTarget
- L141 _public prototype_ `virtual void Setup() override;` — UInteractiveTool overrides
- L142 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L143 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L144 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L146 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L148 _public prototype_ `virtual TArray<UObject*> GetToolProperties(bool bEnabledOnly = true) const override;`
- L151 _public prototype_ `virtual bool ProcessCommandBindings(const FKey Key, const bool bRepeat) const override;` — IBaseSequencerAnimTool
- L155 _public function_ `void SetWorldGizmoModeManager(UWorld* World, UInteractiveGizmoManager* InGizmoManager, FEditorModeTools* InModeManager)`
- L161 _public function_ `UWorld* GetWorld() const`
- L163 _public function_ `FEditorModeTools* GetModeManager() const`
- L164 _public member_ `static FString TrailKeyTransformGizmoInstanceIdentifier;`
- L170 _public member_ `TObjectPtr<UTransformProxy> TransformProxy;` — `UPROPERTY()` — Support for gizmo. Since the points aren't individual components, we don't actually use UTransformProxy for the transform forwarding- we just use it for the callbacks.
- L172 _public member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo;` — `UPROPERTY()`
- L174 _public member_ `TObjectPtr<UTransformGizmo> TRSGizmo = nullptr;` — `UPROPERTY()`
- L176 _public member_ `FTransform StartDragTransform;`
- L177 _public member_ `bool bGizmoBeingDragged = false;`
- L179 _public member_ `FTransform GizmoTransform = FTransform::Identity;`
- L181 _public function_ `UE::SequencerAnimTools::FTrailHierarchy* GetHierarchyForSequencer(ISequencer* Sequencer) const`
- L182 _public function_ `const TArray<TSharedPtr<UE::SequencerAnimTools::FTrailHierarchy>>& GetHierarchies() const`
- L184 _public prototype_ `void AddTrailHierarchy(TSharedPtr<UE::SequencerAnimTools::FTrailHierarchy> InHierarchy);`
- L187 _public member_ `static FOnCreateAdditionalTrailHierarchies OnCreateAdditionalTrailHierarchies;` — Plugins register callbacks here to add custom trail hierarchies during SetupIntegration().
- L189 _public prototype_ `void SelectNone();`
- L192 _protected prototype_ `void SetupIntegration();`
- L193 _protected prototype_ `void ShutdownIntegration();`
- L194 _protected prototype_ `void UpdateGizmoVisibility();`
- L195 _protected prototype_ `void UpdateGizmoLocation();`
- L197 _protected prototype_ `void GizmoTransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L198 _protected prototype_ `void GizmoTransformStarted(UTransformProxy* Proxy);`
- L199 _protected prototype_ `void GizmoTransformEnded(UTransformProxy* Proxy);`
- L203 _protected prototype_ `void TranslateSelectedKeysLeft();` — Actions
- L204 _protected prototype_ `void TranslateSelectedKeysRight();`
- L205 _protected prototype_ `void FrameSelection();`
- L206 _protected prototype_ `void DeleteSelectedKeys();`
- L207 _protected prototype_ `bool SomeKeysAreSelected() const;`
- L210 _protected member_ `TArray<TSharedPtr<UE::SequencerAnimTools::FTrailHierarchy>> TrailHierarchies;`
- L211 _protected member_ `TMap<ISequencer*, UE::SequencerAnimTools::FTrailHierarchy*> SequencerHierarchies;`
- L213 _protected member_ `FDelegateHandle OnSequencersChangedHandle;`
- L215 _protected member_ `bool bManipulatorMadeChange = false;` — ed mode for manips
- L216 _protected member_ `int32 TransactionIndex = -1;`
- L220 _protected member_ `FLeftRghtClickBehaviorTarget LeftTarget;`
- L221 _protected member_ `FLeftRghtClickBehaviorTarget RightTarget;`
- L224 _protected member_ `TObjectPtr<USingleClickInputBehavior> LeftClickBehavior = nullptr;` — `UPROPERTY()`
- L227 _protected member_ `TObjectPtr<USingleClickInputBehavior> RightClickBehavior = nullptr;` — `UPROPERTY()`
- L231 _protected member_ `UWorld* TargetWorld = nullptr;`
- L232 _protected member_ `UInteractiveGizmoManager* GizmoManager = nullptr;`
- L233 _protected member_ `FEditorModeTools* ModeManager = nullptr;`
- L235 _protected member_ `int32 ShiftModifierId = 1;` — Support for Alt,Shift and Ctrl toggles
- L236 _protected member_ `bool bShiftModifierOn = false;`
- L237 _protected member_ `int32 CtrlModifierId = 2;`
- L238 _protected member_ `bool bCtrlModifierOn = false;`
- L239 _protected member_ `int32 AltModiferId = 3;`
- L240 _protected member_ `bool bAltModifierOn = false;`
- L243 _private prototype_ `bool IsHierarchyActive(const UE::SequencerAnimTools::FTrailHierarchy* Hierarchy) const;`
- L247 _private function_ `template<typename Func> void ForEachActiveHierarchy(Func&& InFunc) const` — Iterate all active hierarchies. The callable receives FTrailHierarchy&.
- L261 _private function_ `template<typename Func> bool ForEachActiveHierarchyUntil(Func&& InFunc) const` — Iterate active hierarchies with early-out. The callable returns bool: true to stop iteration, false to continue. Returns true if stopped early.
- L276 _private member_ `TSharedPtr<FUICommandList> CommandBindings;`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreateAdditionalTrailHierarchies, TArray<TSharedPtr<UE::SequencerAnimTools::FTrailHierarchy>>&, TWeakPtr<ISequencer>);` — Delegate for plugins to register additional trail hierarchies with UMotionTrailTool. Fired during SetupIntegration() after the standard FSequencerTrailHierarchy instances are created.
- L32 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreateAdditionalTrailHierarchies, TArray<TSharedPtr<UE::SequencerAnimTools::FTrailHierarchy>>&, TWeakPtr<ISequencer>);` — Delegate for plugins to register additional trail hierarchies with UMotionTrailTool. Fired during SetupIntegration() after the standard FSequencerTrailHierarchy instances are created.

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Public/SequencerAnimEditPivotTool.h` (Public)


#### class `USequencerPivotToolBuilder`  
`class USequencerPivotToolBuilder : public UInteractiveToolBuilder`  
_L48-55_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for USequencerPivotTool
- L53 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L54 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### struct `FSelectionDuringDrag`  
`struct FSelectionDuringDrag`  
_L57-61_
- L59 _public member_ `ULevelSequence* LevelSequence;`
- L60 _public member_ `FTransform CurrentTransform;`

#### struct `FControlRigSelectionDuringDrag`  
`struct FControlRigSelectionDuringDrag : public FSelectionDuringDrag`  
_L63-67_
- inherits: `FSelectionDuringDrag`
- L65 _public member_ `UControlRig* ControlRig;`
- L66 _public member_ `FName ControlName;`

#### struct `FActorSelectonDuringDrag`  
`struct FActorSelectonDuringDrag : public FSelectionDuringDrag`  
_L69-72_
- inherits: `FSelectionDuringDrag`
- L71 _public member_ `AActor* Actor;`

#### struct `FControlRigMappings`  
`struct FControlRigMappings`  
_L74-85_
- L76 _public member_ `TWeakObjectPtr<UControlRig> ControlRig;`
- L78 _public prototype_ `TOptional<FTransform> GetWorldTransform(const FName& Name) const;`
- L79 _public prototype_ `void SetFromWorldTransform(const FName& Name, const FTransform& WorldTransform);`
- L80 _public prototype_ `TArray<FName> GetAllControls() const;`
- L81 _public prototype_ `void SelectControls();`
- L82 _public prototype_ `bool IsAnyControlDeselected() const;`
- L84 _private member_ `TMap<FName, FTransform> PivotTransforms;`

#### struct `FActorMappings`  
`struct FActorMappings`  
_L87-96_
- L89 _public member_ `TWeakObjectPtr<AActor> Actor;`
- L91 _public prototype_ `TOptional<FTransform> GetWorldTransform() const;`
- L92 _public prototype_ `void SetFromWorldTransform(const FTransform& WorldTransform);`
- L93 _public prototype_ `void SelectActors();`
- L95 _private member_ `FTransform PivotTransform;`

#### struct `FSavedMappings`  
`struct FSavedMappings`  
_L98-102_
- L100 _public member_ `TMap<TWeakObjectPtr<UControlRig>, FControlRigMappings> ControlRigMappings;`
- L101 _public member_ `TMap<TWeakObjectPtr<AActor>, FActorMappings> ActorMappings;`

#### struct `FLastSelectedObjects`  
`struct FLastSelectedObjects`  
_L104-109_
- L106 _public member_ `TArray<FControlRigMappings> LastSelectedControlRigs;`
- L107 _public member_ `TArray<FActorMappings> LastSelectedActors;`

#### class `FEditPivotCommands`  
`class FEditPivotCommands : public TCommands<FEditPivotCommands>`  
_L110-136_
- inherits: `TCommands<FEditPivotCommands>`
- L113 _public function_ `FEditPivotCommands() : TCommands<FEditPivotCommands>( "SequencerEditPivotTool", NSLOCTEXT("SequencerEditPivotTool", "SequencerEditPivotTool", "Edit Pivot Commands"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L123 _public prototype_ `virtual void RegisterCommands() override;`
- L124 _public function_ `static const TMap<FName, TArray<TSharedPtr<FUICommandInfo>>>& GetCommands()`
- L131 _public member_ `TSharedPtr<FUICommandInfo> ResetPivot;` — Reset the Pivot
- L133 _public member_ `TSharedPtr<FUICommandInfo> ToggleFreePivot;` — Toggle Free/Pivot Mode
- L135 _public member_ `TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;`

#### class `USequencerPivotTool`  
`class USequencerPivotTool : public UMultiSelectionTool, public IClickBehaviorTarget , public IBaseSequencerAnimTool`  
_L143-280_
- reflection: `UCLASS()`
- inherits: `UMultiSelectionTool,IClickBehaviorTarget,IBaseSequencerAnimTool`
- desc: Pivot tool class
- L150 _public prototype_ `virtual void SetWorld(UWorld* World, UInteractiveGizmoManager* GizmoManager);` — UInteractiveTool overrides
- L151 _public prototype_ `virtual void Setup() override;`
- L152 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L153 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L154 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L155 _public function_ `virtual bool HasCancel() const override`
- L156 _public function_ `virtual bool HasAccept() const override`
- L157 _public function_ `virtual bool CanAccept() const override`
- L158 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L161 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget interface
- L162 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L165 _public prototype_ `virtual bool ProcessCommandBindings(const FKey Key, const bool bRepeat) const override;` — IBaseSequencerAnimTool
- L170 _public function_ `bool IsInPivotMode() const` — If In Pivot Mode, if not then in Free Mode
- L172 _public function_ `void TogglePivotMode()` — Toggle Pivot Mode
- L174 _public prototype_ `void SetPivotMode(bool bVal);` — Set Pivot Mode
- L178 _protected member_ `TObjectPtr<USingleClickInputBehavior> ClickBehavior = nullptr;` — `UPROPERTY()`
- L181 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L184 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`
- L187 _protected member_ `TObjectPtr<UTransformGizmo> TRSGizmo = nullptr;` — `UPROPERTY()`
- L190 _protected member_ `bool bInPivotMode = false;` — pivot may be in 'free' mode or 'pivot' mode
- L191 _protected member_ `bool bShiftPressedWhenStarted = false;`
- L192 _protected member_ `bool bCtrlPressedWhenStarted = false;`
- L193 _protected member_ `UWorld* TargetWorld = nullptr;` — target World we will raycast into
- L194 _protected member_ `UInteractiveGizmoManager* GizmoManager = nullptr;`
- L196 _protected member_ `FTransform StartDragTransform;`
- L197 _protected member_ `bool bGizmoBeingDragged = false;`
- L198 _protected member_ `bool bManipulatorMadeChange = false;`
- L199 _protected member_ `TUniquePtr<FScopedTransaction> Transaction = nullptr;`
- L200 _protected member_ `TArray<FControlRigSelectionDuringDrag> ControlRigDrags;`
- L201 _protected member_ `TArray<FActorSelectonDuringDrag> ActorDrags;`
- L202 _protected member_ `TArray<TSharedPtr<FControlRigInteractionScope>> InteractionScopes;`
- L205 _protected member_ `ULevelSequence* LevelSequence;` — since we are selection based we can cache this
- L206 _protected member_ `TArray<TWeakObjectPtr<UControlRig>> ControlRigs;`
- L207 _protected member_ `TWeakPtr<ISequencer> SequencerPtr;`
- L208 _protected member_ `TArray<TWeakObjectPtr<AActor>> Actors;`
- L210 _protected member_ `FTransform GizmoTransform = FTransform::Identity;`
- L211 _protected member_ `bool bPickingPivotLocation = false;` — mauy remove
- L212 _protected prototype_ `void UpdateGizmoVisibility();`
- L213 _protected prototype_ `void UpdateGizmoTransform();`
- L214 _protected prototype_ `void UpdateTransformAndSelectionOnEntering();`
- L215 _protected prototype_ `bool SetGizmoBasedOnSelection(bool bUseSaved = true);`
- L217 _protected prototype_ `FInputRayHit FindRayHit(const FRay& WorldRay, FVector& HitPos);` — raycasts into World
- L220 _protected prototype_ `void GizmoTransformChanged(UTransformProxy* Proxy, FTransform Transform);` — Callbacks we'll receive from the gizmo proxy
- L221 _protected prototype_ `void GizmoTransformStarted(UTransformProxy* Proxy);`
- L222 _protected prototype_ `void GizmoTransformEnded(UTransformProxy* Proxy);`
- L225 _protected prototype_ `void SavePivotTransforms();` — Handle Selection and Pivot Location
- L226 _protected prototype_ `void SaveLastSelected();`
- L229 _protected prototype_ `void DeactivateMe();` — selection delegates
- L230 _protected prototype_ `void RemoveDelegates();`
- L231 _protected prototype_ `void HandleControlSelected(UControlRig* Subject, FRigControlElement* InControl, bool bSelected);`
- L232 _protected prototype_ `void OnEditorSelectionChanged(UObject* NewSelection);`
- L233 _protected member_ `FDelegateHandle OnEditorSelectionChangedHandle;`
- L236 _protected prototype_ `void CreateAndShowPivotOverlay();` — Functions and variables for handling the overlay for switching between free and pivot mode
- L237 _protected prototype_ `void RemoveAndDestroyPivotOverlay();`
- L239 _protected prototype_ `FMargin GetPivotOverlayPadding() const;`
- L241 _protected member_ `static FVector2f LastPivotOverlayLocation;`
- L242 _protected member_ `TSharedPtr<SWidget> PivotWidget;`
- L243 _protected member_ `TOptional<bool> bSetShowWidget;`
- L245 _public prototype_ `void TryRemovePivotOverlay();`
- L246 _public prototype_ `void TryShowPivotOverlay();`
- L247 _public prototype_ `void UpdatePivotOverlayLocation(const FVector2D InLocation, TSharedPtr<IAssetViewport> ActiveLevelViewport);`
- L250 _private member_ `TSharedPtr<FUICommandList> CommandBindings;`
- L251 _private prototype_ `void ResetPivot();`
- L254 _private prototype_ `void PrepareRigForManipulation(UControlRig* InControlRig);` — Stores data related to InControlRig to prepare its manipulation
- L257 _private prototype_ `void PrepareActorForManipulation(AActor* InActor);` — Stores data related to InActor to prepare its manipulation
- L260 _private prototype_ `void SetControlTransform(const FControlRigSelectionDuringDrag& InControlDrag);` — Updates a control using provided FControlRigSelectionDuringDrag data.
- L263 _private member_ `FControlRigInteractionTransformContext TransformContext;` — Current transform context.
- L266 _private member_ `UE::AnimationEditMode::FControlRigKeyframer Keyframer;` — Used to store and apply keyframes. (if deferred)
- L269 _private member_ `UE::TransformConstraintUtil::FConstraintsInteractionCache ConstraintsCache;` — Per control constraints cache.
- L272 _private member_ `TMap<UControlRig*, UE::ControlRigEditMode::FInteractionDependencyCache> InteractionDependencies;` — Per ControlRig dependencies between the selected controls during interaction.
- L275 _private prototype_ `void UpdateBoundComponents();` — Updates the components bound to the control rigs for a responsive feedback
- L278 _public member_ `static FSavedMappings SavedPivotLocations;`
- L279 _public member_ `static FLastSelectedObjects LastSelectedObjects;`

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Public/SequencerAnimToolsModule.h` (Public)


#### class `UE::SequencerAnimTools::FSequencerAnimToolsModule`  
`class FSequencerAnimToolsModule : public IModuleInterface`  
_L16-29_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _private member_ `TSharedPtr<FUICommandList> CommandBindings;`
- L28 _private prototype_ `void OnMotionTralOptionChanged(FName PropertyName);` — delegates

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequencerAnimTools` (scope `UE`)

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Public/SequencerToolsEditMode.h` (Public)


#### class `USequencerToolsEditMode`  
`class USequencerToolsEditMode : public UBaseLegacyWidgetEdMode`  
_L11-37_
- reflection: `UCLASS()`
- inherits: `UBaseLegacyWidgetEdMode`
- L15 _public member_ `static FEditorModeID ModeName;`
- L17 _public prototype_ `USequencerToolsEditMode();`
- L18 _public prototype_ `virtual ~USequencerToolsEditMode();`
- L21 _public prototype_ `virtual void Enter();` — UEdMode interface
- L22 _public prototype_ `virtual void Exit();`
- L26 _public function_ `virtual bool UsesToolkits() const override`
- L27 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;`
- L28 _public function_ `virtual bool UsesTransformWidget() const override`
- L29 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L30 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L33 _private prototype_ `void LocalOnModeActivated(const FEditorModeID& InID, bool bIsActive);` — UEdMode has this already defined but it's not virtual
- L35 _private member_ `bool bDeactivateOnPIEStartStateToRestore;`
- L36 _private member_ `bool bDeactivateOnSaveWorldToRestore;`

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Public/Trail.h` (Public)


#### struct `UE::SequencerAnimTools::FInputClick`  
`struct FInputClick`  
_L26-34_
- L28 _public function_ `FInputClick()`
- L29 _public function_ `FInputClick(bool bA, bool bC, bool bS) : bAltIsDown(bA), bCtrlIsDown(bC), bShiftIsDown(bS)`
- L30 _public member_ `bool bAltIsDown = false;`
- L31 _public member_ `bool bCtrlIsDown = false;`
- L32 _public member_ `bool bShiftIsDown = false;`
- L33 _public member_ `bool bIsRightMouse = false;`

#### struct `UE::SequencerAnimTools::HBaseTrailProxy`  
`struct HBaseTrailProxy : public HHitProxy`  
_L35-44_
- inherits: `HHitProxy`
- L37 _public prototype_ `DECLARE_HIT_PROXY();`
- L39 _public member_ `FGuid Guid;`
- L40 _public function_ `HBaseTrailProxy(const FGuid& InGuid, EHitProxyPriority InPriority = HPP_Foreground) :HHitProxy(InPriority) ,Guid(InGuid)`

#### struct `UE::SequencerAnimTools::HNewMotionTrailProxy`  
`struct HNewMotionTrailProxy : public HBaseTrailProxy`  
_L46-59_
- inherits: `HBaseTrailProxy`
- L48 _public prototype_ `DECLARE_HIT_PROXY();`
- L50 _public member_ `FVector Point;`
- L51 _public member_ `FFrameNumber CurrentFrame;`
- L53 _public function_ `HNewMotionTrailProxy(const FGuid& InGuid, const FVector& InPoint, const FFrameNumber& InFrame) :HBaseTrailProxy(InGuid) , Point(InPoint) , CurrentFrame(InFrame)`

#### enum `UE::SequencerAnimTools::ETrailCacheState`  
`enum class ETrailCacheState : uint8`  
_L61-67_
- L63 _public enumerator_ `UpToDate = 2`
- L64 _public enumerator_ `Stale = 1`
- L65 _public enumerator_ `Dead = 0`
- L66 _public enumerator_ `NotUpdated = 3`

#### struct `UE::SequencerAnimTools::FTrailCurrentStatus`  
`struct FTrailCurrentStatus`  
_L70-74_
- desc: Status of trail, including possibly frames that must get updated on next evaluation
- L72 _public member_ `ETrailCacheState CacheState = ETrailCacheState::Stale;`
- L73 _public member_ `TArray<FFrameNumber> FramesMustUpdate;`

#### struct `UE::SequencerAnimTools::FColorState`  
`struct FColorState`  
_L77-91_
- desc: struct to cacluate color. The same struct is meant to be used in same loop, and will be set up by the owner(trail hierarchy).
- L79 _public member_ `bool bFirstFrame = true;`
- L80 _public member_ `FFrameNumber TicksPerFrame = FFrameNumber(100);`
- L81 _public member_ `FFrameNumber StartFrame;`
- L82 _public member_ `FFrameNumber SequencerTime;`
- L83 _public member_ `bool bIsPinned = false;`
- L84 _public member_ `EMotionTrailTrailStyle PinnedStyle;`
- L85 _public member_ `FLinearColor CalculatedColor = FColor(0xffffff);`
- L86 _public member_ `UMotionTrailToolOptions* Options = nullptr;`
- L88 _public prototype_ `void Setup(FTrailHierarchy* TrailHierarchy);`
- L89 _public prototype_ `void ReadyForTrail(bool bInIsPinned, EMotionTrailTrailStyle InPinnedStyle);`
- L90 _public prototype_ `EMotionTrailTrailStyle GetStyle() const;`

#### class `UE::SequencerAnimTools::FTrail`  
`class FTrail`  
_L94-210_
- desc: main abstract class that trails implement
- L98 _public function_ `FTrail(UObject* InOwner) : Owner(InOwner) ,CacheState(ETrailCacheState::Stale) , bForceEvaluateNextTick(true)`
- L104 _public prototype_ `virtual ~FTrail() = default;`
- L113 _public function_ `UObject* GetOwner() const`
- L118 _public prototype_ `virtual FTrailCurrentStatus UpdateTrail(const FNewSceneContext& NewSceneContext) = 0;` — main function to update trail each tick
- L120 _public function_ `virtual void Interp(const FFrameNumber& Time, FTransform& OutTransform, FTransform& OutParentTransform)` — get the transform at a specified time
- L123 _public function_ `virtual void UpdateFinished(const TRange<FFrameNumber>& UpdatedRange, const TArray<int32>& IndicesToCalcluate, bool bDoneCalcuating)` — when multiple frame update is finally finished
- L124 _public prototype_ `virtual FText GetName() const = 0;`
- L127 _public function_ `virtual void AddImportantTimes(TSet<FFrameNumber>& InOutImportantTimes)` — add set of important times for this trail to be used by the incremental evaluations, usually these are the edited times
- L130 _public function_ `virtual void Render(const FGuid& Guid, const FSceneView* View, FPrimitiveDrawInterface* PDI, bool bTrailIsEvaluating)` — Additional Render/HitTest event handling for specific trails, usually let default renderer handle it
- L131 _public function_ `virtual void RenderEvaluating(const FGuid& Guid, const FSceneView* View, FPrimitiveDrawInterface* PDI)`
- L132 _public function_ `virtual void DrawHUD(const FSceneView* View, FCanvas* Canvas)`
- L133 _public function_ `virtual bool HandleClick(const FGuid& Guid, FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, FInputClick Click)`
- L134 _public function_ `virtual bool IsAnythingSelected() const`
- L135 _public function_ `virtual bool IsAnythingSelected(FVector& OutVectorPosition, FQuat& OutRotation)const`
- L136 _public function_ `virtual bool IsAnythingSelected(TArray<FVector>& OutVectorPositions)const`
- L137 _public function_ `virtual bool IsTrailSelected() const`
- L138 _public function_ `virtual bool BoxSelect(FBox& InBox, bool InSelect = true)`
- L139 _public function_ `virtual bool FrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, bool InSelect = true)`
- L140 _public function_ `virtual void SetOffsetMode()`
- L141 _public function_ `virtual bool GetOffsetMode() const`
- L142 _public function_ `virtual bool StartTracking()`
- L143 _public function_ `virtual bool ApplyDelta(const FVector& Pos, const FRotator& Rot, const FVector& WidgetLocation, bool bApplyToOffset)`
- L144 _public function_ `virtual bool EndTracking()`
- L145 _public function_ `virtual bool IsTracking() const`
- L146 _public function_ `virtual void TranslateSelectedKeys(bool bRight)`
- L147 _public function_ `virtual void DeleteSelectedKeys()`
- L148 _public function_ `virtual void SelectNone()`
- L149 _public function_ `virtual void UpdateKeysInRange(const TRange<FFrameNumber>& ViewRange)`
- L150 _public function_ `virtual void ClearCachedData()`
- L151 _public function_ `virtual void HasStartedEvaluating()`
- L152 _public function_ `virtual void ReadyToDrawTrail(FColorState& ColorState, const FCurrentFramesInfo* InCurrentFramesInfo,bool bIsEvaluating, bool bIsPinned)`
- L153 _public function_ `virtual void ActorChanged(AActor* InActor)`
- L154 _public prototype_ `virtual bool HandleObjectsChanged(const TMap<UObject*, UObject*>& ReplacementMap);`
- L157 _public function_ `virtual TArray<FFrameNumber> GetKeyTimes() const` — Optionally implemented methods
- L158 _public function_ `virtual TArray<FFrameNumber> GetSelectedKeyTimes() const`
- L160 _public function_ `virtual void GetTrajectoryPointsForDisplay(const FCurrentFramesInfo& InCurrentFramesInfo, bool bIsEvaluating, TArray<FVector>& OutPoints, TArray<FFrameNumber>& OutFrames)`
- L167 _public function_ `virtual void GetTickPointsForDisplay(const FTrailScreenSpaceTransform& InScreenSpaceTransform, const FCurrentFramesInfo& InCurrentFramesInfo, bool bIsEvaluating, TArray<FVector2D>& OutTicks, TArray<FVector2D>& OutTickTangents)`
- L176 _public function_ `virtual FTransform GetOffsetTransform() const` — offset the trail from current position
- L177 _public function_ `virtual void ClearOffsetTransform()`
- L178 _public function_ `virtual bool HasOffsetTransform()`
- L180 _public function_ `virtual FTransform GetParentSpaceTransform() const` — set space and get space transform
- L181 _public function_ `virtual void SetSpace(AActor* InActor, const FName& InComponentName)`
- L182 _public function_ `virtual void ClearSpace()`
- L184 _public function_ `virtual void ForceEvaluateNextTick()`
- L186 _public prototype_ `virtual void GetColor(const FFrameNumber& CurrentTime, FColorState& InOutColorState);`
- L194 _public function_ `virtual TUniquePtr<FMotionTrailState> GetMotionTrailState() const`
- L196 _public function_ `FTrajectoryDrawInfo* GetDrawInfo() const`
- L198 _public function_ `ETrailCacheState GetCacheState() const`
- L203 _protected member_ `TWeakObjectPtr<UObject> Owner;`
- L204 _protected member_ `ETrailCacheState CacheState;`
- L206 _protected member_ `bool bForceEvaluateNextTick;`
- L207 _protected member_ `TUniquePtr<FTrajectoryDrawInfo> DrawInfo;`

#### struct `UE::SequencerAnimTools::FTrail::FNewSceneContext`  
`struct FNewSceneContext`  
_L106-111_
- L108 _public member_ `bool bCheckForChange;`
- L109 _public member_ `FGuid YourNode;`
- L110 _public member_ `class FTrailHierarchy* TrailHierarchy;`

#### class `UE::SequencerAnimTools::FTrail::FMotionTrailState`  
`class FMotionTrailState`  
_L188-193_
- desc: get and restore trail from it's data
- L191 _public prototype_ `virtual ~FMotionTrailState() = default;`
- L192 _public prototype_ `virtual void RestoreTrail(FTrailHierarchy* TrailHierarchy) = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SequencerAnimTools` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SequencerAnimTools` (scope `UE`)

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Public/TrailHierarchy.h` (Public)


#### struct `UE::SequencerAnimTools::FTrailVisibilityManager`  
`struct FTrailVisibilityManager`  
_L18-56_
- L20 _public function_ `bool IsTrailVisible(const FGuid& Guid, const FTrail* Trail, bool bShowSelected = true) const`
- L26 _public function_ `bool IsTrailAlwaysVisible(const FGuid& Guid) const`
- L30 _public function_ `void SetTrailAlwaysVisible(const FGuid& Guid, bool bSet)`
- L42 _public function_ `void Reset()`
- L51 _public member_ `TSet<FGuid> InactiveMask;` — Any trails whose cache state or parent's cache state has been marked as NotUpdated
- L52 _public member_ `TSet<FGuid> VisibilityMask;` — Any trails masked out by the user interface, ex bone trails
- L53 _public member_ `TSet<FGuid> AlwaysVisible;` — Any trails pinned by the user interface
- L54 _public member_ `TSet<FGuid> Selected;` — Any transform or bone trails selected in the user interface
- L55 _public member_ `TSet<FGuid> ControlSelected;` — Any control rig trails selected

#### class `UE::SequencerAnimTools::ITrailHierarchyRenderer`  
`class ITrailHierarchyRenderer`  
_L58-64_
- L61 _public prototype_ `virtual ~ITrailHierarchyRenderer() = default;`
- L62 _public prototype_ `virtual void Render(const FSceneView* View, FPrimitiveDrawInterface* PDI) = 0;`
- L63 _public prototype_ `virtual void DrawHUD(const FSceneView* View, FCanvas* Canvas) = 0;`

#### class `UE::SequencerAnimTools::FTrailHierarchyRenderer`  
`class FTrailHierarchyRenderer : public ITrailHierarchyRenderer`  
_L66-80_
- inherits: `ITrailHierarchyRenderer`
- L69 _public function_ `FTrailHierarchyRenderer(FTrailHierarchy* InOwningHierarchy, UMotionTrailToolOptions* InOptions) : OwningHierarchy(InOwningHierarchy), CachedOptions(InOptions)`
- L73 _public prototype_ `virtual void Render(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L74 _public prototype_ `virtual void DrawHUD(const FSceneView* View, FCanvas* Canvas) override;`
- L77 _private member_ `FTrailHierarchy* OwningHierarchy;`
- L78 _private member_ `UMotionTrailToolOptions* CachedOptions;`

#### class `UE::SequencerAnimTools::FTrailHierarchy`  
`class FTrailHierarchy`  
_L82-168_
- L86 _public function_ `FTrailHierarchy() :TickViewRange(TRange<FFrameNumber>(0,0)) ,TickEvalRange(TRange<FFrameNumber>(0,0)) ,TicksPerSegment(1) ,LastTickEvalRange(TRange<FFrameNumber>(0,0)) ,LastTicksPerSegment(1) , AllTrails() , TimingStats() , VisibilityManager()`
- L97 _public prototype_ `virtual ~FTrailHierarchy() = default;`
- L99 _public prototype_ `FTrailHierarchy(const FTrailHierarchy&) = delete;`
- L100 _public prototype_ `FTrailHierarchy& operator=(const FTrailHierarchy&) = delete;`
- L102 _public prototype_ `virtual void Initialize() = 0;`
- L103 _public prototype_ `virtual void Destroy() = 0;` — TODO: make dtor?
- L104 _public prototype_ `virtual ITrailHierarchyRenderer* GetRenderer() const = 0;`
- L105 _public prototype_ `virtual FFrameNumber GetLocalTime() const = 0;`
- L106 _public prototype_ `virtual FFrameNumber GetFramesPerFrame() const = 0;`
- L107 _public prototype_ `virtual FFrameNumber GetFramesPerSegment() const = 0;`
- L109 _public prototype_ `virtual const FCurrentFramesInfo* GetCurrentFramesInfo() const = 0;`
- L110 _public prototype_ `virtual bool IsVisible(const FGuid& InTrailGuid) const;`
- L111 _public prototype_ `virtual bool CheckForChanges() = 0;`
- L112 _public prototype_ `virtual bool IsTrailEvaluating(const FGuid& InTrailGuid, bool bIndirectlyOnly) const = 0;`
- L114 _public prototype_ `virtual void CalculateEvalRangeArray();`
- L115 _public prototype_ `virtual void Update();`
- L116 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, FInputClick Click);`
- L117 _public prototype_ `virtual bool IsHitByClick(HHitProxy* HitProx);`
- L118 _public prototype_ `virtual bool BoxSelect(FBox& InBox, bool InSelect = true);`
- L119 _public prototype_ `virtual bool FrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, bool InSelect = true) ;`
- L121 _public prototype_ `virtual bool IsAnythingSelected(FVector& OutVectorPosition, FQuat& OutRotation)const;`
- L122 _public prototype_ `virtual bool IsAnythingSelected(TArray<FVector>& OutVectorPositions, bool bAllPositions = false) const;`
- L123 _public prototype_ `virtual bool IsAnythingSelected() const;`
- L124 _public prototype_ `virtual void SelectNone();`
- L125 _public prototype_ `virtual bool IsSelected(const FGuid& Key) const;`
- L126 _public prototype_ `virtual bool IsAlwaysVisible(const FGuid Key) const;`
- L128 _public prototype_ `virtual void AddTrail(const FGuid& Key, TUniquePtr<FTrail>&& TrailPtr);`
- L129 _public prototype_ `virtual void RemoveTrail(const FGuid& Key);`
- L131 _public prototype_ `virtual bool StartTracking();`
- L132 _public prototype_ `virtual bool ApplyDelta(const FVector& Pos, const FRotator& Rot, const FVector& WidgetLocation, bool bApplyToOffset);`
- L133 _public prototype_ `virtual bool EndTracking();`
- L135 _public prototype_ `virtual void TranslateSelectedKeys(bool bRight);`
- L136 _public prototype_ `virtual void DeleteSelectedKeys();`
- L138 _public function_ `const TRange<FFrameNumber>& GetViewFrameRange() const`
- L139 _public function_ `FFrameNumber GetTicksPerSegment() const`
- L140 _public function_ `const TMap<FGuid, TUniquePtr<FTrail>>& GetAllTrails() const`
- L142 _public function_ `const TMap<FString, FTimespan>& GetTimingStats() const`
- L143 _public function_ `TMap<FString, FTimespan>& GetTimingStats()`
- L145 _public function_ `FTrailVisibilityManager& GetVisibilityManager()`
- L147 _public function_ `ETrailCategory GetTrailCategory() const`
- L150 _protected prototype_ `void RemoveTrailIfNotAlwaysVisible(const FGuid& Key);`
- L152 _protected prototype_ `void OpenContextMenu(const FGuid& TrailGuid);`
- L154 _protected member_ `TRange<FFrameNumber> TickViewRange;`
- L155 _protected member_ `TRange<FFrameNumber> TickEvalRange;`
- L157 _protected member_ `FFrameNumber TicksPerSegment;`
- L158 _protected member_ `TRange<FFrameNumber> LastTickEvalRange = TRange<FFrameNumber>(0, 0);`
- L159 _protected member_ `FFrameNumber LastTicksPerSegment = FFrameNumber(1);`
- L161 _protected member_ `TMap<FGuid, TUniquePtr<FTrail>> AllTrails;`
- L163 _protected member_ `TMap<FString, FTimespan> TimingStats;`
- L165 _protected member_ `FTrailVisibilityManager VisibilityManager;`
- L167 _protected member_ `ETrailCategory TrailCategory = ETrailCategory::None;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequencerAnimTools` (scope `UE`)

### `Plugins/Editor/SequencerAnimTools/Source/SequencerAnimTools/Public/TrajectoryDrawInfo.h` (Public)


#### class `UE::SequencerAnimTools::FTrailScreenSpaceTransform`  
`class FTrailScreenSpaceTransform`  
_L21-34_
- L24 _public function_ `FTrailScreenSpaceTransform(const FSceneView* InView, const float InDPIScale = 1.0f) : View(InView) , DPIScale(InDPIScale)`
- L29 _public prototype_ `TOptional<FVector2D> ProjectPoint(const FVector& Point) const;`
- L32 _private member_ `const FSceneView* View;`
- L33 _private member_ `const float DPIScale;`

#### struct `UE::SequencerAnimTools::FFrameCalculator`  
`struct FFrameCalculator`  
_L39-66_
- desc: This struct will give set of indices to calculate based upon number of frames and current bucket we are calculating. t
- L41 _public function_ `FFrameCalculator()`
- L45 _public prototype_ `void SetUpFrameCalculator(const UE::AIE::FFrameTimeByIndex& InCurrentFrameTimes, TRange<FFrameNumber> ViewRange);`
- L46 _public prototype_ `void AddMustHaveIndices(const TArray<int32>& InMustHaveIndices);`
- L47 _public prototype_ `void Reset();`
- L48 _public prototype_ `bool CalculateIndices();`
- L50 _public member_ `static int32 IndicesToCalculatePerBucket;`
- L51 _public member_ `UE::AIE::FFrameTimeByIndex CurrentFrameTimes;`
- L53 _public member_ `TArray<TRange<FFrameNumber>> Ranges;` — set of ranges of time we calculate, if view range is same as eval range this will just be one range that's equal to the CurrentFrameTimesRange
- L54 _public member_ `int32 CurrentRange;`
- L55 _public member_ `int32 CurrentRangeStartIndex;`
- L56 _public member_ `int32 CurrentRangeEndIndex;`
- L58 _public member_ `int32 NumOfBuckets;`
- L59 _public member_ `int32 CurrentBucket;`
- L60 _public member_ `TArray<int32> IndicesToCalculate;`
- L61 _public member_ `TArray<int32> MustHaveIndices;`
- L64 _private prototype_ `void CalculateStartEndIndices();`

#### struct `UE::SequencerAnimTools::FCurrentFramesInfo`  
`struct FCurrentFramesInfo`  
_L69-91_
- desc: Holds set of currently calculating frames
- L71 _public prototype_ `void SetViewRange(const TRange<FFrameNumber>& InViewRange, bool bInViewRangeIsEvalRange);`
- L72 _public prototype_ `void SetUpFrameTimes(const TRange<FFrameNumber>& InEvalFrameRange, const FFrameNumber& InFrameStep);`
- L73 _public prototype_ `void AddMustHaveTimes(const TSet<FFrameNumber>& InMustHaveTimes, const FFrameNumber& InFrameNumber);`
- L74 _public prototype_ `const TArray<int32>& IndicesToCalculate() const;`
- L75 _public prototype_ `bool KeepCalculating();`
- L76 _public prototype_ `void Reset();`
- L79 _public member_ `UE::AIE::FFrameTimeByIndex CurrentFrameTimes;` — range and frame rate, this is fixed and will only change if evaluation range(sequencer range/display rate) changes.
- L80 _public member_ `TRange<FFrameNumber> ViewRange;`
- L81 _public member_ `bool bViewRangeIsEvalRange = false;`
- L83 _public member_ `FFrameCalculator FrameCalculator;` — this also contains the indices to calculate
- L86 _public member_ `TSortedMap<int32, FFrameNumber> SortedTransformIndices;` — set of indices that slowly grow
- L88 _public member_ `TArray<int32> TransformIndices;` — cached array of the transform indices
- L90 _public member_ `TArray<FFrameNumber> CurrentFrames;` — all trails share this now

#### struct `UE::SequencerAnimTools::FTrajectoryDrawInfo`  
`struct FTrajectoryDrawInfo`  
_L94-120_
- L96 _public function_ `FTrajectoryDrawInfo(EMotionTrailTrailStyle InStyle, const FLinearColor& InColor, TSharedPtr<UE::AIE::FArrayOfTransforms>& InArrayOfTransforms, TSharedPtr<UE::AIE::FArrayOfTransforms>& InParentSpaceArrayOfTransforms) : Color(InColor) , ArrayOfTransforms(InArrayOfTransforms) , ParentSpaceTransforms(InParentSpaceArrayOfTransforms)`
- L103 _public prototype_ `~FTrajectoryDrawInfo() = default;`
- L104 _public prototype_ `void GetTrajectoryPointsForDisplay(const FTransform& OffsetTransform, const FTransform& ParentSpaceTransform, const FCurrentFramesInfo& InCurrentFramesInfo, bool bIsEvaluating, TArray<FVector>& OutPoints, TArray<FFrameNumber>& OutFrames);`
- L105 _public prototype_ `void GetTickPointsForDisplay(const FTransform& OffsetTransform, const FTransform& ParentSpaceTransform, const FTrailScreenSpaceTransform& ScreenSpaceTransform, const FCurrentFramesInfo & InCurrentFramesInfo, bool bIsEvaluating, TArray<FVector2D>& OutTicks, TArray<FVector2D>& OutTickTangents);`
- L106 _public prototype_ `FVector GetPoint(const FTransform& OffsetTransform, const FTransform& ParentSpaceTransform, const FCurrentFramesInfo& InDisplayContext, const FFrameNumber& InTime);`
- L109 _public function_ `void SetColor(const FLinearColor& InColor)`
- L110 _public function_ `FLinearColor GetColor() const`
- L111 _public function_ `void SetStyle(EMotionTrailTrailStyle InStyle)`
- L112 _public function_ `EMotionTrailTrailStyle GetStyle() const`
- L116 _protected member_ `EMotionTrailTrailStyle Style;`
- L117 _protected member_ `FLinearColor Color;`
- L118 _protected member_ `TSharedPtr<UE::AIE::FArrayOfTransforms> ArrayOfTransforms;`
- L119 _protected member_ `TSharedPtr<UE::AIE::FArrayOfTransforms> ParentSpaceTransforms;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SequencerAnimTools` (scope `UE`)
