# Editor / ComponentVisualizers

- module root: `Source/Editor/ComponentVisualizers`
- headers: 22; symbols: 451
- symbol kinds: class=32, enum=4, enumerator=13, function=75, macro=16, member=100, namespace=2, prototype=193, struct=13, typedef=3
- PrivateDependencyModuleNames: AIModule, Core, CoreUObject, EditorFramework, Engine, InputCore, LevelEditor, PropertyEditor, Slate, SlateCore, UnrealEd, ViewportInteraction

### `Source/Editor/ComponentVisualizers/Public/AttenuatedComponentVisualizer.h` (Public)


#### class `TAttenuatedComponentVisualizer`  
`template<class T> class TAttenuatedComponentVisualizer : public FComponentVisualizer`  
_L12-129_
- inherits: `FComponentVisualizer`
- L16 _public function_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override`
- L128 _private prototype_ `virtual bool IsVisualizerEnabled(const FEngineShowFlags& ShowFlags) const = 0;`

### `Source/Editor/ComponentVisualizers/Public/AudioComponentVisualizer.h` (Public)


#### class `FAudioComponentVisualizer`  
`class FAudioComponentVisualizer : public TAttenuatedComponentVisualizer<UAudioComponent>`  
_L8-15_
- inherits: `TAttenuatedComponentVisualizer<UAudioComponent>`
- L11 _private function_ `virtual bool IsVisualizerEnabled(const FEngineShowFlags& ShowFlags) const override`

### `Source/Editor/ComponentVisualizers/Public/ComponentVisualizers.h` (Public)


#### class `FComponentVisualizersModule`  
`class FComponentVisualizersModule : public IModuleInterface`  
_L13-52_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L24 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L31 _public function_ `virtual bool SupportsDynamicReloading() override` — Override this to set whether your module is allowed to be unloaded on the fly @return	Whether the module supports shutdown separate from the rest of the engine.
- L37 _public prototype_ `void RegisterComponentVisualizer(FName ComponentClassName, TSharedPtr<FComponentVisualizer> Visualizer);` — Register a visualizer for a particular component class
- L40 _public prototype_ `void MuteComponentVisualizer(FName ComponentClassName);` — Mutes a registered visualizer so that it will no longer be used. Can be restored without re-registering.
- L43 _public prototype_ `void UnmuteComponentVisualizer(FName ComponentClassName);` — Unmutes a muted visualizer so that it will be used again by the editor.
- L48 _private member_ `TArray<FName> RegisteredComponentClassNames;` — Array of component class names we have registered, so we know what to unregister afterwards
- L51 _private member_ `TMap<FName, TSharedPtr<FComponentVisualizer>> MutedComponentVisualizers;` — Set of muted component visualizers. We must retain the shared pointer so we can unregister from the editor.

### `Source/Editor/ComponentVisualizers/Public/ConstraintComponentVisualizer.h` (Public)


#### class `FConstraintComponentVisualizer`  
`class FConstraintComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/DecalComponentVisualizer.h` (Public)


#### class `FDecalComponentVisualizer`  
`class FDecalComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/ForceFeedbackComponentVisualizer.h` (Public)


#### class `FForceFeedbackComponentVisualizer`  
`class FForceFeedbackComponentVisualizer : public TAttenuatedComponentVisualizer<UForceFeedbackComponent>`  
_L8-15_
- inherits: `TAttenuatedComponentVisualizer<UForceFeedbackComponent>`
- L11 _private function_ `virtual bool IsVisualizerEnabled(const FEngineShowFlags& ShowFlags) const override`

### `Source/Editor/ComponentVisualizers/Public/LocalFogVolumeComponentVisualizer.h` (Public)


#### class `FLocalFogVolumeComponentVisualizer`  
`class FLocalFogVolumeComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/Manipulator.h` (Public)


#### class `AManipulator`  
`class UE_DEPRECATED(5.7, "The ViewportInteraction module is being deprecated alongside VR Editor mode.") AManipulator : public AActor, public IViewportInteractableInterface`  
_L27-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor,IViewportInteractableInterface`
- L33 _public prototype_ `AManipulator();`
- L36 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L37 _public prototype_ `virtual bool IsEditorOnly() const final;`
- L41 _public prototype_ `virtual void OnPressed(UViewportInteractor* Interactor, const FHitResult& InHitResult, bool& bOutResultedInDrag) override;`
- L42 _public prototype_ `virtual void OnHover(UViewportInteractor* Interactor) override;`
- L43 _public prototype_ `virtual void OnHoverEnter(UViewportInteractor* Interactor, const FHitResult& InHitResult) override;`
- L44 _public prototype_ `virtual void OnHoverLeave(UViewportInteractor* Interactor, const UActorComponent* NewComponent) override;`
- L45 _public prototype_ `virtual void OnDragRelease(UViewportInteractor* Interactor) override;`
- L46 _public function_ `virtual class UViewportDragOperationComponent* GetDragOperationComponent() override`
- L47 _public function_ `virtual bool CanBeSelected() override`
- L51 _public prototype_ `void SetAssociatedComponent(USceneComponent* SceneComponent);` — Set the component that should be moved when the manipulator was moved.
- L57 _private member_ `TObjectPtr<USceneComponent> AssociatedComponent;` — `UPROPERTY()` — The component to transform when this manipulator was moved.
- L61 _private member_ `TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;` — `UPROPERTY()` — Visual representation of this manipulator.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/PhysicalAnimationComponentVisualizer.h` (Public)


#### class `FPhysicsAnimationComponentVisualizer`  
`class FPhysicsAnimationComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/PointLightComponentVisualizer.h` (Public)


#### class `FTextureLightProfileVisualizer`  
`class FTextureLightProfileVisualizer`  
_L17-29_
- L20 _public prototype_ `FTextureLightProfileVisualizer();`
- L22 _public prototype_ `void DrawVisualization(UTextureLightProfile* TextureLightProfile, const FTransform& LightTM, const FSceneView* View, FPrimitiveDrawInterface* PDI);`
- L25 _private prototype_ `bool UpdateIntensitiesCache(UTextureLightProfile* TextureLightProfile, const FTransform& LightTM);`
- L27 _private member_ `const UTextureLightProfile* CachedLightProfile;`
- L28 _private member_ `TArray< float > IntensitiesCache;`

#### class `FPointLightComponentVisualizer`  
`class FPointLightComponentVisualizer : public FComponentVisualizer`  
_L31-40_
- inherits: `FComponentVisualizer`
- L35 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L39 _private member_ `FTextureLightProfileVisualizer LightProfileVisualizer;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/RadialForceComponentVisualizer.h` (Public)


#### class `FRadialForceComponentVisualizer`  
`class FRadialForceComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization( const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI ) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/RectLightComponentVisualizer.h` (Public)


#### class `FRectLightComponentVisualizer`  
`class FRectLightComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/SensingComponentVisualizer.h` (Public)


#### class `FSensingComponentVisualizer`  
`class FSensingComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/SplineComponentVisualizer.h` (Public)


#### struct `UE::SplineComponentVisualizer::FPDICache`  
`struct FPDICache`  
_L58-173_
- L143 _public typedef_ `using FLineBatch = TElementBatch<FRenderableLine>;`
- L144 _public typedef_ `using FPointBatch = TElementBatch<FRenderablePoint>;`
- L146 _public function_ `void Reset()`
- L152 _public function_ `void Draw(FPrimitiveDrawInterface* PDI) const`
- L158 _public function_ `void AddBatch(FLineBatch&& LineBatch)`
- L164 _public function_ `void AddBatch(FPointBatch&& PointBatch)`
- L170 _public member_ `TArray<FLineBatch> LineBatches;`
- L171 _public member_ `TArray<FPointBatch> PointBatches;`
- L172 _public member_ `bool bDirty = true;`

#### struct `UE::SplineComponentVisualizer::FPDICache::FRenderableLine`  
`struct FRenderableLine`  
_L60-91_
- L62 _public function_ `FRenderableLine() : Start(ForceInitToZero) , End(ForceInitToZero) , Color(ForceInitToZero) , DepthPriority(SDPG_World) , Thickness(0.0f) , DepthBias(0.0f)`
- L71 _public function_ `FRenderableLine(const FVector& InStart, const FVector& InEnd, const FColor& InColor, const ESceneDepthPriorityGroup InDepthPriority = SDPG_World, const float InThickness = 0.0f, const float InDepthBias = 0.0f) : Start(InStart) , End(InEnd) , Color(InColor) , DepthPriority(InDepthPriority) , Thickness(InThickness) , DepthBias(InDepthBias)`
- L80 _public function_ `void Draw(FPrimitiveDrawInterface* PDI) const`
- L85 _public member_ `FVector Start;`
- L86 _public member_ `FVector End;`
- L87 _public member_ `FColor Color;`
- L88 _public member_ `ESceneDepthPriorityGroup DepthPriority;`
- L89 _public member_ `float Thickness;`
- L90 _public member_ `float DepthBias;`

#### struct `UE::SplineComponentVisualizer::FPDICache::FRenderablePoint`  
`struct FRenderablePoint`  
_L93-118_
- L95 _public function_ `FRenderablePoint() : Position(ForceInitToZero) , Color(ForceInitToZero) , Size(0.f) , DepthPriority(SDPG_World)`
- L102 _public function_ `FRenderablePoint(const FVector& InPosition, const FColor& InColor, const float InSize, const ESceneDepthPriorityGroup InDepthPriority = SDPG_World) : Position(InPosition) , Color(InColor) , Size(InSize) , DepthPriority(InDepthPriority)`
- L109 _public function_ `void Draw(FPrimitiveDrawInterface* PDI) const`
- L114 _public member_ `FVector Position;`
- L115 _public member_ `FColor Color;`
- L116 _public member_ `float Size;`
- L117 _public member_ `ESceneDepthPriorityGroup DepthPriority;`

#### struct `UE::SplineComponentVisualizer::FPDICache::TElementBatch`  
`template <typename ElementType> struct TElementBatch`  
_L121-141_
- L123 _public member_ `TArray<ElementType> Elements;`
- L124 _public function_ `TFunction<HHitProxy*()> AllocHitProxyFunc = []() -> HHitProxy*`
- L124 _public member_ `TFunction<HHitProxy*()> AllocHitProxyFunc = []() -> HHitProxy* { return nullptr; };`
- L126 _public function_ `void Draw(FPrimitiveDrawInterface* PDI) const`
- L135 _private function_ `HHitProxy* AllocateHitProxy() const`

#### enum `ESelectedTangentHandle`  
`enum class ESelectedTangentHandle`  
_L179-184_
- reflection: `UENUM()`
- desc: Tangent handle selection modes.
- L181 _public enumerator_ `None`
- L182 _public enumerator_ `Leave`
- L183 _public enumerator_ `Arrive`

#### class `USplineComponentVisualizerSelectionState`  
`class USplineComponentVisualizerSelectionState : public UObject`  
_L188-284_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- desc: Selection state data that will be captured by scoped transactions.
- L195 _public prototype_ `int32 GetVerifiedLastKeyIndexSelected(const int32 InNumSplinePoints) const;` — Checks LastKeyIndexSelected is valid given the number of splint points and returns its value.
- L198 _public prototype_ `void GetVerifiedSelectedTangentHandle(const int32 InNumSplinePoints, int32& OutSelectedTangentHandle, ESelectedTangentHandle& OutSelectedTangentHandleType) const;` — Checks TangentHandle and TangentHandleType are valid and sets relevant output parameters.
- L200 _public function_ `const FComponentPropertyPath GetSplinePropertyPath() const`
- L201 _public function_ `void SetSplinePropertyPath(const FComponentPropertyPath& InSplinePropertyPath)`
- L203 _public function_ `const TSet<int32>& GetSelectedKeys() const`
- L204 _public function_ `TSet<int32>& ModifySelectedKeys()`
- L206 _public function_ `int32 GetLastKeyIndexSelected() const`
- L207 _public function_ `void SetLastKeyIndexSelected(const int32 InLastKeyIndexSelected)`
- L209 _public function_ `int32 GetSelectedSegmentIndex() const`
- L210 _public function_ `void SetSelectedSegmentIndex(const int32 InSelectedSegmentIndex)`
- L212 _public function_ `int32 GetSelectedTangentHandle() const`
- L213 _public function_ `void SetSelectedTangentHandle(const int32 InSelectedTangentHandle)`
- L215 _public function_ `int32 GetSelectedAttributeIndex() const`
- L216 _public function_ `FName GetSelectedAttributeName() const`
- L217 _public function_ `void SetSelectedAttribute(const int32 InSelectedAttributeIndex = INDEX_NONE, const FName& InSelectedAttributeName = NAME_None)`
- L228 _public function_ `ESelectedTangentHandle GetSelectedTangentHandleType() const`
- L229 _public function_ `void SetSelectedTangentHandleType(const ESelectedTangentHandle InSelectedTangentHandle)`
- L231 _public function_ `FVector GetSelectedSplinePosition() const`
- L232 _public function_ `void SetSelectedSplinePosition(const FVector& InSelectedSplinePosition)`
- L234 _public function_ `FQuat GetCachedRotation() const`
- L235 _public function_ `void SetCachedRotation(const FQuat& InCachedRotation)`
- L237 _public prototype_ `void Reset();`
- L238 _public prototype_ `void ClearSelectedKeys();`
- L239 _public prototype_ `void ClearSelectedSegmentIndex();`
- L240 _public prototype_ `void ClearSelectedTangentHandle();`
- L241 _public function_ `void ClearSelectedAttribute()`
- L243 _public prototype_ `bool IsSplinePointSelected(const int32 InIndex) const;`
- L248 _protected member_ `FComponentPropertyPath SplinePropertyPath;` — `UPROPERTY()` — Property path from the parent actor to the component
- L252 _protected member_ `TSet<int32> SelectedKeys;` — `UPROPERTY()` — Indices of keys we have selected
- L256 _protected member_ `int32 LastKeyIndexSelected = INDEX_NONE;` — `UPROPERTY()` — Index of the last key we selected
- L260 _protected member_ `int32 SelectedSegmentIndex = INDEX_NONE;` — `UPROPERTY()` — Index of segment we have selected
- L264 _protected member_ `int32 SelectedTangentHandle = INDEX_NONE;` — `UPROPERTY()` — Index of tangent handle we have selected
- L268 _protected member_ `ESelectedTangentHandle SelectedTangentHandleType = ESelectedTangentHandle::None;` — `UPROPERTY()` — The type of the selected tangent handle
- L272 _protected member_ `int32 SelectedAttributeIndex = INDEX_NONE;` — `UPROPERTY()` — Index of attribute handle we have selected
- L275 _protected member_ `FName SelectedAttributeName = NAME_None;` — `UPROPERTY()`
- L279 _protected member_ `FVector SelectedSplinePosition;` — `UPROPERTY()` — Position on spline we have selected
- L283 _protected member_ `FQuat CachedRotation;` — `UPROPERTY()` — Cached rotation for this point

#### struct `HSplineVisProxy`  
`struct HSplineVisProxy : public HComponentVisProxy`  
_L287-299_
- inherits: `HComponentVisProxy`
- desc: Base class for clickable spline editing proxies
- L289 _public prototype_ `DECLARE_HIT_PROXY( );`
- L291 _public function_ `HSplineVisProxy(const UActorComponent* InComponent) : HComponentVisProxy(InComponent, HPP_Wireframe)`
- L295 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`

#### struct `HSplineKeyProxy`  
`struct HSplineKeyProxy : public HSplineVisProxy`  
_L302-317_
- inherits: `HSplineVisProxy`
- desc: Proxy for a spline key
- L304 _public prototype_ `DECLARE_HIT_PROXY( );`
- L306 _public function_ `HSplineKeyProxy(const UActorComponent* InComponent, int32 InKeyIndex) : HSplineVisProxy(InComponent) , KeyIndex(InKeyIndex)`
- L311 _public member_ `int32 KeyIndex;`
- L313 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`

#### struct `HSplineAttributeKeyProxy`  
`struct HSplineAttributeKeyProxy : public HSplineVisProxy`  
_L320-335_
- inherits: `HSplineVisProxy`
- desc: Proxy for spline attribute key (as opposed to a positional control point)
- L322 _public prototype_ `DECLARE_HIT_PROXY( );`
- L324 _public function_ `HSplineAttributeKeyProxy(const UActorComponent* InComponent, int32 InKeyIndex) : HSplineVisProxy(InComponent) , KeyIndex(InKeyIndex)`
- L329 _public member_ `int32 KeyIndex;`
- L331 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`

#### struct `HSplineSegmentProxy`  
`struct HSplineSegmentProxy : public HSplineVisProxy`  
_L338-353_
- inherits: `HSplineVisProxy`
- desc: Proxy for a spline segment
- L340 _public prototype_ `DECLARE_HIT_PROXY( );`
- L342 _public function_ `HSplineSegmentProxy(const UActorComponent* InComponent, int32 InSegmentIndex) : HSplineVisProxy(InComponent) , SegmentIndex(InSegmentIndex)`
- L347 _public member_ `int32 SegmentIndex;`
- L349 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`

#### struct `HSplineTangentHandleProxy`  
`struct HSplineTangentHandleProxy : public HSplineVisProxy`  
_L356-373_
- inherits: `HSplineVisProxy`
- desc: Proxy for a tangent handle
- L358 _public prototype_ `DECLARE_HIT_PROXY( );`
- L360 _public function_ `HSplineTangentHandleProxy(const UActorComponent* InComponent, int32 InKeyIndex, bool bInArriveTangent) : HSplineVisProxy(InComponent) , KeyIndex(InKeyIndex) , bArriveTangent(bInArriveTangent)`
- L366 _public member_ `int32 KeyIndex;`
- L367 _public member_ `bool bArriveTangent;`
- L369 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`

#### enum `ESplineComponentSnapMode`  
`enum class ESplineComponentSnapMode`  
_L376-381_
- desc: Accepted modes for snapping points.
- L378 _public enumerator_ `Snap`
- L379 _public enumerator_ `AlignToTangent`
- L380 _public enumerator_ `AlignPerpendicularToTangent`

#### class `FSplineComponentVisualizer`  
`class FSplineComponentVisualizer : public FComponentVisualizer, public FGCObject PRAGMA_DISABLE_INTERNAL_WARNINGS , public ISplineDetailsProvider PRAGMA_DISABLE_INTERNAL_WARNINGS`  
_L384-697_
- inherits: `FComponentVisualizer,FGCObjectPRAGMA_DISABLE_INTERNAL_WARNINGS,ISplineDetailsProviderPRAGMA_DISABLE_INTERNAL_WARNINGS`
- desc: SplineComponent visualizer/edit functionality
- L389 _private typedef_ `using FPDICache = UE::SplineComponentVisualizer::FPDICache;`
- L393 _public prototype_ `FSplineComponentVisualizer();`
- L394 _public prototype_ `virtual ~FSplineComponentVisualizer();`
- L397 _public prototype_ `virtual void OnRegister() override;`
- L398 _public prototype_ `virtual bool ShouldShowForSelectedSubcomponents(const UActorComponent* Component) override;`
- L399 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L400 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;`
- L402 _public prototype_ `virtual void DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;` — Draw HUD on viewport for the supplied component
- L403 _public prototype_ `virtual void EndEditing() override;`
- L404 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;`
- L405 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* ViewportClient, FMatrix& OutMatrix) const override;`
- L406 _public prototype_ `virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;`
- L407 _public prototype_ `virtual bool HandleInputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L409 _public prototype_ `virtual bool HandleModifiedClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;` — Handle click modified by Alt, Ctrl and/or Shift. The input HitProxy may not be on this component.
- L411 _public prototype_ `virtual bool HandleBoxSelect(const FBox& InBox, FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — Handle box select input
- L413 _public prototype_ `virtual bool HandleFrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — Handle frustum select input
- L415 _public prototype_ `virtual bool HasFocusOnSelectionBoundingBox(FBox& OutBoundingBox) override;` — Return whether focus on selection should focus on bounding box defined by active visualizer
- L417 _public prototype_ `virtual bool HandleSnapTo(const bool bInAlign, const bool bInUseLineTrace, const bool bInUseBounds, const bool bInUsePivot, AActor* InDestination) override;` — Pass snap input to active visualizer
- L419 _public prototype_ `virtual void TrackingStopped(FEditorViewportClient* InViewportClient, bool bInDidMove) override;` — Gets called when the mouse tracking has stopped (dragging behavior)
- L421 _public prototype_ `virtual UActorComponent* GetEditedComponent() const override;` — Get currently edited component, this is needed to reset the active visualizer after undo/redo
- L422 _public prototype_ `virtual TSharedPtr<SWidget> GenerateContextMenu() const override;`
- L423 _public prototype_ `virtual bool IsVisualizingArchetype() const override;`
- L427 _public prototype_ `virtual void GenerateContextMenuSections(FMenuBuilder& InMenuBuilder) const;` — Add menu sections to the context menu
- L430 _public prototype_ `virtual USplineComponent* GetEditedSplineComponent() const override;` — Get the spline component we are currently editing
- L432 _public function_ `const virtual TSet<int32>& GetSelectedKeys() const override`
- L435 _public prototype_ `virtual bool HandleSelectFirstLastSplinePoint(USplineComponent* InSplineComponent, bool bFirstPoint) override;` — Select first or last spline point, returns true if the spline component being edited has changed
- L437 _public prototype_ `virtual void HandleSelectPrevNextSplinePoint(bool bNext, bool bAddToSelection) override;`
- L440 _public prototype_ `virtual bool HandleSelectAllSplinePoints(USplineComponent* InSplineComponent) override;` — Select all spline points, , returns true if the spline component being edited has changed
- L443 _public prototype_ `void OnSelectPrevNextSplinePoint(bool bNextPoint, bool bAddToSelection);` — Select next or prev spline point, loops when last point is currently selected
- L446 _public prototype_ `virtual void SetCachedRotation(const FQuat& NewRotation) override;` — Sets the new cached rotation on the visualizer
- L450 _protected prototype_ `bool IsAnySelectedKeyIndexOutOfRange(const USplineComponent* Comp) const;` — Determine if any selected key index is out of range (perhaps because something external has modified the spline)
- L453 _protected prototype_ `bool IsSingleKeySelected() const;` — Whether a single spline key is currently selected
- L456 _protected prototype_ `bool AreMultipleKeysSelected() const;` — Whether a multiple spline keys are currently selected
- L459 _protected prototype_ `bool AreKeysSelected() const;` — Whether any keys are currently selected
- L462 _protected prototype_ `void SelectSplinePoint(int32 SelectIndex, bool bAddToSelection);` — Select spline point at specified index
- L465 _protected prototype_ `bool TransformSelectedTangent(EPropertyChangeType::Type InPropertyChangeType, const FVector& InDeltaTranslate);` — Transforms selected tangent by given translation
- L468 _protected prototype_ `bool TransformSelectedKeys(EPropertyChangeType::Type InPropertyChangeType, const FVector& InDeltaTranslate, const FRotator& InDeltaRotate = FRotator::ZeroRotator, const FVector& InDeltaScale = FVector::ZeroVector);` — Transforms selected tangent by given translate, rotate and scale
- L471 _protected prototype_ `bool TransformSelectedAttribute(EPropertyChangeType::Type InPropertyChangeType, const FVector& InDeltaTranslate);` — Transforms selected attribute by given translation
- L474 _protected prototype_ `virtual void ChangeSelectionState(int32 Index, bool bIsCtrlHeld);` — Update the key selection state of the visualizer
- L477 _protected prototype_ `virtual bool DuplicateKeyForAltDrag(const FVector& InDrag);` — Alt-drag: duplicates the selected spline key
- L480 _protected prototype_ `virtual bool UpdateDuplicateKeyForAltDrag(const FVector& InDrag);` — Alt-drag: updates duplicated selected spline key
- L483 _protected prototype_ `virtual float FindNearest(const FVector& InLocalPos, int32 InSegmentStartIndex, FVector& OutSplinePos, FVector& OutSplineTangent) const;` — Return spline data for point on spline closest to input point
- L486 _protected prototype_ `virtual void SplitSegment(const FVector& InWorldPos, int32 InSegmentIndex, bool bCopyFromSegmentBeginIndex = true);` — Split segment using given world position
- L489 _protected prototype_ `virtual void UpdateSplitSegment(const FVector& InDrag);` — Update split segment based on drag offset
- L492 _protected prototype_ `virtual void AddSegment(const FVector& InWorldPos, bool bAppend);` — Add segment to beginning or end of spline
- L495 _protected prototype_ `virtual void UpdateAddSegment(const FVector& InWorldPos);` — Add segment to beginning or end of spline
- L498 _protected prototype_ `virtual void ResetAllowDuplication();` — Alt-drag: duplicates the selected spline key
- L501 _protected prototype_ `virtual void SnapKeysToLastSelectedAxisPosition(const EAxis::Type InAxis, TArray<int32> InSnapKeys);` — Snapping: snap keys to axis position of last selected key
- L504 _protected prototype_ `virtual void SnapKeyToActor(const AActor* InActor, const ESplineComponentSnapMode SnapMode);` — Snapping: snap key to selected actor
- L507 _protected prototype_ `virtual void SnapKeyToTransform(const ESplineComponentSnapMode InSnapMode, const FVector& InWorldPos, const FVector& InWorldUpVector, const FVector& InWorldForwardVector, const FVector& InScale, const USplineMetadata* InCopySplineMetadata = nullptr, const int32 InCopySplineMetadataKey = 0);` — Snapping: generic method for snapping selected keys to given transform
- L516 _protected prototype_ `virtual void SetSnapToActorMode(const bool bInIsSnappingToActor, const ESplineComponentSnapMode InSnapMode = ESplineComponentSnapMode::Snap);` — Snapping: set snap to actor temporary mode
- L519 _protected prototype_ `virtual bool GetSnapToActorMode(ESplineComponentSnapMode& OutSnapMode) const;` — Snapping: get snap to actor temporary mode
- L522 _protected prototype_ `virtual void ResetTempModes();` — Reset temporary modes after inputs are handled.
- L525 _protected prototype_ `const USplineComponent* UpdateSelectedSplineComponent(HComponentVisProxy* VisProxy);` — Updates the component and selected properties if the component has changed
- L527 _protected prototype_ `void OnDeleteKey();`
- L528 _protected prototype_ `bool CanDeleteKey() const;`
- L531 _protected prototype_ `void OnDuplicateKey();` — Duplicates selected spline keys in place
- L532 _protected prototype_ `bool IsKeySelectionValid() const;`
- L534 _protected prototype_ `void OnAddKeyToSegment();`
- L535 _protected prototype_ `bool CanAddKeyToSegment() const;`
- L537 _protected prototype_ `void OnSnapKeyToNearestSplinePoint(ESplineComponentSnapMode InSnapMode);`
- L539 _protected prototype_ `void OnSnapKeyToActor(const ESplineComponentSnapMode InSnapMode);`
- L541 _protected prototype_ `void OnSnapAllToAxis(EAxis::Type InAxis);`
- L543 _protected prototype_ `void OnSnapSelectedToAxis(EAxis::Type InAxis);`
- L545 _protected prototype_ `void OnStraightenKey(int32 Direction);`
- L546 _protected prototype_ `void StraightenKey(int32 KeyToStraighten, int32 KeyToStraightenToward);`
- L548 _protected prototype_ `void OnToggleSnapTangentAdjustment();`
- L549 _protected prototype_ `bool IsSnapTangentAdjustment() const;`
- L551 _protected prototype_ `void OnLockAxis(EAxis::Type InAxis);`
- L552 _protected prototype_ `bool IsLockAxisSet(EAxis::Type InAxis) const;`
- L554 _protected prototype_ `void OnResetToAutomaticTangent(EInterpCurveMode Mode);`
- L555 _protected prototype_ `bool CanResetToAutomaticTangent(EInterpCurveMode Mode) const;`
- L557 _protected prototype_ `void OnSetKeyType(EInterpCurveMode Mode);`
- L558 _protected prototype_ `bool IsKeyTypeSet(EInterpCurveMode Mode) const;`
- L560 _protected prototype_ `void OnSetVisualizeRollAndScale();`
- L561 _protected prototype_ `bool IsVisualizingRollAndScale() const;`
- L563 _protected prototype_ `void OnSetDiscontinuousSpline();`
- L564 _protected prototype_ `bool IsDiscontinuousSpline() const;`
- L566 _protected prototype_ `void OnToggleClosedLoop();`
- L567 _protected prototype_ `bool IsClosedLoop() const;`
- L569 _protected prototype_ `void OnResetToDefault();`
- L570 _protected prototype_ `bool CanResetToDefault() const;`
- L572 _protected prototype_ `void OnAddAttributeKey();`
- L573 _protected prototype_ `bool CanAddAttributeKey() const;`
- L575 _protected prototype_ `void OnDeleteAttributeKey();`
- L576 _protected prototype_ `bool CanDeleteAttributeKey() const;`
- L579 _protected prototype_ `void OnSelectFirstLastSplinePoint(bool bFirstPoint);` — Select first or last spline point
- L582 _protected prototype_ `void OnSelectAllSplinePoints();` — Select all spline points, if no spline points selected yet the currently edited spline component will be set as well
- L584 _protected prototype_ `bool CanSelectSplinePoints() const;`
- L587 _protected prototype_ `void GenerateSelectSplinePointsSubMenu(FMenuBuilder& MenuBuilder) const;` — Generate the submenu containing available selection actions
- L590 _protected prototype_ `void GenerateSplinePointTypeSubMenu(FMenuBuilder& MenuBuilder) const;` — Generate the submenu containing the available point types
- L593 _protected prototype_ `void GenerateTangentTypeSubMenu(FMenuBuilder& MenuBuilder) const;` — Generate the submenu containing the available auto tangent types
- L596 _protected prototype_ `void GenerateSnapAlignSubMenu(FMenuBuilder& MenuBuilder) const;` — Generate the submenu containing the available snap/align actions
- L599 _protected prototype_ `void GenerateLockAxisSubMenu(FMenuBuilder& MenuBuilder) const;` — Generate the submenu containing the lock axis types
- L602 _protected prototype_ `void GenerateAttributeMenuSection(FMenuBuilder& InMenuBuilder) const;` — Extends the provided MenuBuilder with an Attribute section
- L605 _protected prototype_ `TSharedPtr<SWidget> GenerateChannelWidget() const;` — Generate the channel creator/selector widget.
- L606 _protected prototype_ `TSharedPtr<SWidget> GenerateChannelCreatorWidget() const;`
- L607 _protected prototype_ `TSharedPtr<SWidget> GenerateChannelSelectorWidget() const;`
- L610 _protected prototype_ `TSharedPtr<SWidget> GenerateAttributeEditorWidget() const;` — Generate the attribute editor widget.
- L613 _protected prototype_ `void SetEditedSplineComponent(const USplineComponent* InSplineComponent);` — Helper function to set edited component we are currently editing
- L615 _protected prototype_ `void CreateSplineGeneratorPanel();`
- L617 _protected prototype_ `void OnDeselectedInEditor(TObjectPtr<USplineComponent> SplineComponent);`
- L619 _protected prototype_ `bool ShouldUseForSpline(const USplineComponent* SplineComponent) const override;`
- L620 _protected prototype_ `void ActivateVisualization() override;`
- L621 _protected prototype_ `bool IsEnabledForSpline(const USplineComponent* InSplineComponent) const;`
- L624 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector);` — FGCObject interface
- L625 _protected function_ `virtual FString GetReferencerName() const override`
- L632 _protected member_ `TSharedPtr<FUICommandList> SplineComponentVisualizerActions;` — Output log commands
- L635 _protected member_ `TObjectPtr<USplineComponentVisualizerSelectionState> SelectionState;` — Current selection state
- L638 _protected member_ `bool bAllowDuplication;` — Whether we currently allow duplication when dragging
- L641 _protected member_ `bool bDuplicatingSplineKey;` — Alt-drag: True when in process of duplicating a spline key.
- L644 _protected member_ `bool bUpdatingAddSegment;` — Alt-drag: True when in process of adding end segment.
- L647 _protected member_ `uint32 DuplicateDelay;` — Alt-drag: Delays duplicating control point to accumulate sufficient drag input offset.
- L650 _protected member_ `FVector DuplicateDelayAccumulatedDrag;` — Alt-drag: Accumulates delayed drag offset.
- L653 _protected member_ `float DuplicateCacheSplitSegmentParam;` — Alt-drag: Cached segment parameter for split segment at new control point
- L657 _protected member_ `EAxis::Type AddKeyLockedAxis;` — Axis to fix when adding new spline points. Uses the value of the currently selected spline point's X, Y, or Z value when fix is not equal to none.
- L660 _protected member_ `bool bIsSnappingToActor;` — Snap: True when in process of snapping to actor which needs to be Ctrl-Selected.
- L663 _protected member_ `ESplineComponentSnapMode SnapToActorMode;` — Snap: Snap to actor mode.
- L666 _protected member_ `FProperty* SplineCurvesProperty;` — `UE_DEPRECATED(5.7, "SplineCurvesProperty is deprecated, please use SplineProperties.")`
- L669 _protected member_ `TArray<FProperty*> SplineProperties;` — The set of properties to mark as dirty when manipulating the target spline component.
- L671 _protected member_ `FDelegateHandle DeselectedInEditorDelegateHandle;`
- L673 _protected function_ `void UpdateSharedAttributeNames() const`
- L685 _protected member_ `mutable TArray<TSharedPtr<FName>> SharedAttributeNames;`
- L689 _private member_ `FDelegateHandle OnObjectTransactedHandle;`
- L691 _private member_ `mutable TMap<TWeakObjectPtr<const USplineComponent>, FPDICache> PDICache;`
- L692 _private prototype_ `void DirtyPDICache(const USplineComponent* SplineComp);`
- L693 _private prototype_ `void UpdatePDICache(const USplineComponent* SplineComp);`
- L695 _private member_ `TSharedPtr<SSplineGeneratorPanel> SplineGeneratorPanel;`
- L696 _private member_ `static TWeakPtr<SWindow> WeakExistingWindow;`

#### class `ISplineComponentVisualizerSuppressor`  
`class ISplineComponentVisualizerSuppressor : public IModularFeature`  
_L704-713_
- inherits: `IModularFeature`
- desc: Allows implements to suppress the visualizer (disabling rendering, input capture, etc.) for a particular spline component.
- L708 _public prototype_ `virtual ~ISplineComponentVisualizerSuppressor() = default;`
- L710 _public function_ `static FName GetModularFeatureName()`
- L712 _public prototype_ `virtual bool ShouldSuppress(const USplineComponent* SplineComponent) const = 0;`

#### Free symbols / members of external scopes

- L35 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`
- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace SplineComponentVisualizer` (scope `UE`)
- L680 _function_ `` (scope `FSplineComponentVisualizer::UpdateSharedAttributeNames`)

### `Source/Editor/ComponentVisualizers/Public/SplineDetailsProvider.h` (Public)


#### class `ISplineDetailsProvider`  
`class ISplineDetailsProvider : public IModularFeature`  
_L18-52_
- inherits: `IModularFeature`
- desc: Interface for spline details panels to interact with spline editing tools. This interface was extracted from FSplineComponentVisualizer to integrate a replacement of that visualizer into the spline component details customization.
- L21 _public prototype_ `virtual ~ISplineDetailsProvider() = default;`
- L24 _public function_ `static FName GetModularFeatureName()` — Get the modular feature name for registration/lookup
- L30 _public prototype_ `virtual bool ShouldUseForSpline(const USplineComponent* SplineComponent) const = 0;` — Check if this implementation should be used for the given spline component
- L33 _public prototype_ `virtual const TSet<int32>& GetSelectedKeys() const = 0;` — Get the currently selected spline point indices
- L36 _public prototype_ `virtual USplineComponent* GetEditedSplineComponent() const = 0;` — Get the spline component currently being edited by this system
- L39 _public prototype_ `virtual bool HandleSelectFirstLastSplinePoint(USplineComponent* SplineComp, bool bFirst) = 0;` — Select the first or last spline point
- L42 _public prototype_ `virtual void HandleSelectPrevNextSplinePoint(bool bNext, bool bAddToSelection) = 0;` — Select the previous or next spline point
- L45 _public prototype_ `virtual bool HandleSelectAllSplinePoints(USplineComponent* SplineComp) = 0;` — Select all spline points
- L48 _public function_ `virtual void SetCachedRotation(const FQuat& NewRotation)` — Set the cached rotation for the spline component
- L51 _public function_ `virtual void ActivateVisualization()` — Activate the visualization for the edited spline component

### `Source/Editor/ComponentVisualizers/Public/SplineGeneratorPanel.h` (Public)


#### enum `EShapeAddMode`  
`enum class EShapeAddMode : uint8`  
_L36-42_
- reflection: `UENUM()`
- L38 _public enumerator_ `AppendAfter = 0x01`
- L39 _public enumerator_ `AppendBefore = 0x02`
- L40 _public enumerator_ `InsertAfter = 0x04`
- L41 _public enumerator_ `InsertBefore = 0x08`

#### class `USplineGeneratorBase`  
`class USplineGeneratorBase : public UObject`  
_L47-78_
- reflection: `UCLASS(config = EditorSettings)`
- inherits: `UObject`
- L52 _public function_ `USplineGeneratorBase() : ShapeAddMode(EShapeAddMode::AppendAfter)`
- L56 _public prototype_ `void Init(TWeakPtr<FSplineComponentVisualizer> InSplineComponentVisualizer);`
- L57 _public prototype_ `void Reset();`
- L58 _public prototype_ `void PreviewCurve();`
- L60 _public function_ `virtual void BuildCurve()`
- L61 _public function_ `virtual int32 GetNumPoints() const`
- L64 _public member_ `EShapeAddMode ShapeAddMode;` — `UPROPERTY(Transient, EditAnywhere, Category = GenerateOptions, Meta = (ToolTip = "How to add the shape to the selection"))`
- L66 _public member_ `int32 StartKey;`
- L70 _protected prototype_ `int32 GetAddIndex(int32 Index) const;` — Helper method to return the index for adding a spline point
- L72 _protected prototype_ `int32 GetItrIndex(int32 Index) const;` — Helper method to return the index for an added spline point after all points have been added
- L74 _protected member_ `FSplineCurves CachedSplineCurves;`
- L76 _protected member_ `TWeakObjectPtr<USplineComponent> SelectedSplineComponent;`
- L77 _protected member_ `TWeakPtr<FSplineComponentVisualizer> WeakSplineVis;`

#### class `UCircleSplineGenerator`  
`class UCircleSplineGenerator : public USplineGeneratorBase`  
_L81-112_
- reflection: `UCLASS(config = EditorSettings, DisplayName = "Circle")`
- inherits: `USplineGeneratorBase`
- L86 _public function_ `UCircleSplineGenerator() : NumberOfPoints(3) , Radius(100.f) , bReverseDir(false) , bKeepFirstKeyTangent(true) , bBranchRight(false)`
- L94 _public prototype_ `virtual void BuildCurve() override;`
- L96 _public function_ `virtual int32 GetNumPoints() const override`
- L99 _public member_ `int32 NumberOfPoints;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ToolTip = "Number of points making up shape", ClampMin = "2"))`
- L102 _public member_ `float Radius;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta=(ToolTip="Radius of circle", ClampMin = "0"))`
- L105 _public member_ `bool bReverseDir;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta=(ToolTip="If enabled, will reverse the direction of the circle"))`
- L108 _public member_ `bool bKeepFirstKeyTangent;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta=(ToolTip="If enabled, will start the shape tangent to the current path"))`
- L111 _public member_ `bool bBranchRight;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta=(ToolTip = "If enabled, will switch the circle's center to the right of the curve", EditCondition="bKeepFirstKeyTangent"))`

#### class `UArcSplineGenerator`  
`class UArcSplineGenerator : public USplineGeneratorBase`  
_L115-150_
- reflection: `UCLASS(config = EditorSettings, DisplayName = "Arc")`
- inherits: `USplineGeneratorBase`
- L120 _public function_ `UArcSplineGenerator() : NumberOfPoints(4) , Radius(100.f) , Degrees(90.f) , bReverseDir(false) , bKeepFirstKeyTangent(true) , bBranchRight(false)`
- L129 _public prototype_ `virtual void BuildCurve() override;`
- L131 _public function_ `virtual int32 GetNumPoints() const override`
- L134 _public member_ `int32 NumberOfPoints;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ToolTip = "Number of points making up shape", ClampMin = "2"))`
- L137 _public member_ `float Radius;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ToolTip = "Radius of arc", ClampMin = "0"))`
- L140 _public member_ `float Degrees;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ToolTip = "Degree of arc", ClampMin = "0"))`
- L143 _public member_ `bool bReverseDir;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta = (ToolTip = "If enabled, will reverse the direction of the arc"))`
- L146 _public member_ `bool bKeepFirstKeyTangent;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta = (ToolTip = "If enabled, will start the shape tangent to the current path"))`
- L149 _public member_ `bool bBranchRight;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta = (ToolTip = "If enabled, will switch the arc's center to the right of the curve", EditCondition = "bKeepFirstKeyTangent"))`

#### class `USquareSplineGenerator`  
`class USquareSplineGenerator : public USplineGeneratorBase`  
_L153-172_
- reflection: `UCLASS(config = EditorSettings, DisplayName = "Square")`
- inherits: `USplineGeneratorBase`
- L158 _public function_ `USquareSplineGenerator() : Length(100.f) , bBranchRight(false)`
- L163 _public prototype_ `virtual void BuildCurve() override;`
- L165 _public function_ `virtual int32 GetNumPoints() const override`
- L168 _public member_ `float Length;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ClampMin = "0"))`
- L171 _public member_ `bool bBranchRight;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta = (ToolTip = "If enabled, will switch the shape's center to the right of the curve"))`

#### class `UEllipseSplineGenerator`  
`class UEllipseSplineGenerator : public USplineGeneratorBase`  
_L175-208_
- reflection: `UCLASS(config = EditorSettings, DisplayName = "Ellipse")`
- inherits: `USplineGeneratorBase`
- L180 _public function_ `UEllipseSplineGenerator() : NumberOfPoints(10) , Length(200.f) , Width(200.f) , bReverseDir(false) , bKeepFirstKeyTangent(true) , bBranchRight(false)`
- L189 _public prototype_ `virtual void BuildCurve() override;`
- L192 _public member_ `int32 NumberOfPoints;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ClampMin = "2"))`
- L195 _public member_ `float Length;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ClampMin = "0"))`
- L198 _public member_ `float Width;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ClampMin = "0"))`
- L201 _public member_ `bool bReverseDir;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta = (ToolTip = "If enabled, will reverse the direction of the arc"))`
- L204 _public member_ `bool bKeepFirstKeyTangent;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta = (ToolTip = "If enabled, will start the shape tangent to the current path"))`
- L207 _public member_ `bool bBranchRight;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta = (ToolTip = "If enabled, will switch the shape's center to the right of the curve", EditCondition = "bKeepFirstKeyTangent"))`

#### class `URectangleSplineGenerator`  
`class URectangleSplineGenerator : public USplineGeneratorBase`  
_L211-234_
- reflection: `UCLASS(config = EditorSettings, DisplayName = "Rectangle")`
- inherits: `USplineGeneratorBase`
- L216 _public function_ `URectangleSplineGenerator() : Length(100.f) , Width(100.f) , bBranchRight(false)`
- L222 _public prototype_ `virtual void BuildCurve() override;`
- L224 _public function_ `virtual int32 GetNumPoints() const override`
- L227 _public member_ `float Length;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ClampMin = "0"))`
- L230 _public member_ `float Width;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ClampMin = "0"))`
- L233 _public member_ `bool bBranchRight;` — `UPROPERTY(Transient, EditAnywhere, Category = OtherParameters, Meta = (ToolTip = "If enabled, will switch the shape's center to the right of the curve"))`

#### class `ULineSplineGenerator`  
`class ULineSplineGenerator : public USplineGeneratorBase`  
_L237-265_
- reflection: `UCLASS(config = EditorSettings, DisplayName = "Line")`
- inherits: `USplineGeneratorBase`
- L242 _public function_ `ULineSplineGenerator() : NumberOfPoints(5) , Length(100.f) , bEnableUpToNextPoint(false) , bUpToNextPoint(false)`
- L249 _public prototype_ `virtual void BuildCurve() override;`
- L251 _public function_ `virtual int32 GetNumPoints() const override`
- L254 _public member_ `int32 NumberOfPoints;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ClampMin = "1"))`
- L257 _public member_ `double Length;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ClampMin = "0", EditCondition = "!bUpToNextPoint"))`
- L260 _public member_ `bool bEnableUpToNextPoint;` — `UPROPERTY()`
- L263 _public member_ `bool bUpToNextPoint;` — `UPROPERTY(Transient, EditAnywhere, Category = ShapeParameters, Meta = (ToolTip = "If enabled, will add points up until the next existing point", EditCondition = "bEnableUpToNextPoint"))`

#### class `SSplineGeneratorPanel`  
`class SSplineGeneratorPanel : public SCompoundWidget`  
_L267-298_
- inherits: `SCompoundWidget`
- L270 _public function_ `SLATE_BEGIN_ARGS(SSplineGeneratorPanel)`
- L273 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FSplineComponentVisualizer> InWeakSplineComponentVisualizer);`
- L277 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L278 _public prototype_ `virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;`
- L281 _public prototype_ `void OnWindowClosed(const TSharedRef<SWindow>&);` — SWindow Interface
- L283 _public prototype_ `void OnSelectionUpdated();`
- L285 _public prototype_ `~SSplineGeneratorPanel();`
- L289 _private member_ `TSharedPtr<IDetailsView> DetailView;`
- L291 _private member_ `TWeakPtr<FSplineComponentVisualizer> WeakSplineComponentVisualizer;`
- L292 _private member_ `USplineGeneratorBase* SplineGen;`
- L294 _private member_ `TArray<UObject*> ShapeGenRegistry;`
- L297 _private member_ `TUniquePtr<class FScopedTransaction> ActiveTransaction;` — The currently open transaction (if any)

#### Free symbols / members of external scopes

- L44 _prototype_ `ENUM_CLASS_FLAGS(EShapeAddMode);`

### `Source/Editor/ComponentVisualizers/Public/SplineMeshComponentVisualizer.h` (Public)


#### struct `HSplineMeshVisProxy`  
`struct HSplineMeshVisProxy : public HComponentVisProxy`  
_L29-36_
- inherits: `HComponentVisProxy`
- desc: Base class for clickable spline mesh component editing proxies
- L31 _public prototype_ `DECLARE_HIT_PROXY( );`
- L33 _public function_ `HSplineMeshVisProxy(const UActorComponent* InComponent) : HComponentVisProxy(InComponent, HPP_Wireframe)`

#### struct `HSplineMeshKeyProxy`  
`struct HSplineMeshKeyProxy : public HSplineMeshVisProxy`  
_L39-49_
- inherits: `HSplineMeshVisProxy`
- desc: Proxy for a spline mesh component key
- L41 _public prototype_ `DECLARE_HIT_PROXY( );`
- L43 _public function_ `HSplineMeshKeyProxy(const UActorComponent* InComponent, int32 InKeyIndex) : HSplineMeshVisProxy(InComponent) , KeyIndex(InKeyIndex)`
- L48 _public member_ `int32 KeyIndex;`

#### struct `HSplineMeshTangentHandleProxy`  
`struct HSplineMeshTangentHandleProxy : public HSplineMeshVisProxy`  
_L52-64_
- inherits: `HSplineMeshVisProxy`
- desc: Proxy for a tangent handle
- L54 _public prototype_ `DECLARE_HIT_PROXY( );`
- L56 _public function_ `HSplineMeshTangentHandleProxy(const UActorComponent* InComponent, int32 InKeyIndex, bool bInArriveTangent) : HSplineMeshVisProxy(InComponent) , KeyIndex(InKeyIndex) , bArriveTangent(bInArriveTangent)`
- L62 _public member_ `int32 KeyIndex;`
- L63 _public member_ `bool bArriveTangent;`

#### class `FSplineMeshComponentVisualizer`  
`class FSplineMeshComponentVisualizer : public FComponentVisualizer`  
_L67-117_
- inherits: `FComponentVisualizer`
- desc: SplineMeshComponent visualizer/edit functionality
- L70 _public prototype_ `FSplineMeshComponentVisualizer();`
- L71 _public prototype_ `virtual ~FSplineMeshComponentVisualizer();`
- L74 _public prototype_ `virtual void OnRegister() override;`
- L75 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L76 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;`
- L77 _public prototype_ `virtual void EndEditing() override;`
- L78 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;`
- L79 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* ViewportClient, FMatrix& OutMatrix) const override;`
- L80 _public prototype_ `virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;`
- L81 _public prototype_ `virtual bool HandleInputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L82 _public prototype_ `virtual TSharedPtr<SWidget> GenerateContextMenu() const override;`
- L86 _public prototype_ `USplineMeshComponent* GetEditedSplineMeshComponent() const;` — Get the spline component we are currently editing
- L91 _protected prototype_ `FInterpCurveVector GetSpline(const USplineMeshComponent* SplineMeshComp) const;` — Get a spline object for the specified spline mesh component
- L94 _protected prototype_ `void NotifyComponentModified();` — Syncs changes made by the visualizer in the actual component
- L97 _protected member_ `FComponentPropertyPath SplineMeshPropertyPath;` — Property path from the parent actor to the component
- L100 _protected member_ `int32 SelectedKey;` — Index of the key we selected
- L103 _protected member_ `int32 SelectedTangentHandle;` — Index of tangent handle we have selected
- L116 _protected member_ `ESelectedTangentHandle::Type SelectedTangentHandleType;` — The type of the selected tangent handle

#### struct `FSplineMeshComponentVisualizer::ESelectedTangentHandle`  
`struct ESelectedTangentHandle`  
_L105-113_

#### enum `FSplineMeshComponentVisualizer::ESelectedTangentHandle::Type`  
`enum Type`  
_L107-112_
- L109 _public enumerator_ `None`
- L110 _public enumerator_ `Leave`
- L111 _public enumerator_ `Arrive`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/SpotLightComponentVisualizer.h` (Public)


#### class `FSpotLightComponentVisualizer`  
`class FSpotLightComponentVisualizer : public FComponentVisualizer`  
_L15-24_
- inherits: `FComponentVisualizer`
- L19 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L23 _private member_ `FTextureLightProfileVisualizer LightProfileVisualizer;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/SpringArmComponentVisualizer.h` (Public)


#### class `FSpringArmComponentVisualizer`  
`class FSpringArmComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/SpringComponentVisualizer.h` (Public)


#### class `FSpringComponentVisualizer`  
`class FSpringComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/StereoLayerComponentVisualizer.h` (Public)


#### class `FStereoLayerComponentVisualizer`  
`class FStereoLayerComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`

### `Source/Editor/ComponentVisualizers/Public/WorldPartitionStreamingSourceComponentVisualizer.h` (Public)


#### class `FWorldPartitionStreamingSourceComponentVisualizer`  
`class FWorldPartitionStreamingSourceComponentVisualizer : public FComponentVisualizer`  
_L14-20_
- inherits: `FComponentVisualizer`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMPONENTVISUALIZERS_API`
