# Plugins / AvalancheViewport

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport`
- headers: 34; symbols: 599
- symbol kinds: class=24, delegate=4, enum=14, enumerator=46, function=42, member=144, prototype=304, struct=17, typedef=4
- PrivateDependencyModuleNames: AvalancheEditorCore, AvalancheShapes, InputCore, Json, Projects, SettingsEditor, Slate
- PublicDependencyModuleNames: Avalanche, AvalancheCore, Core, CoreUObject, DeveloperSettings, Engine, SlateCore, UnrealEd

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/AvaScreenAlignmentActorInfo.h` (Private)


#### struct `FAvaScreenAlignmentActorInfo`  
`struct FAvaScreenAlignmentActorInfo`  
_L12-82_
- desc: Information about an actor relative to the camera - world locations in camera space and screen locations.
- L67 _public prototype_ `[[nodiscard]] static FAvaScreenAlignmentActorInfo Create(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, AActor& InActor, EAvaAlignmentSizeMode InActorSizeMode);`
- L71 _public member_ `AActor* const Actor;` — The actor in question
- L73 _public member_ `const TBounds<double, FCoordinateSpace::World> ActorLocal;`
- L75 _public member_ `const TBounds<double, FCoordinateSpace::World> World;`
- L77 _public member_ `const TBounds<double, FCoordinateSpace::World> CameraLocal;`
- L79 _public member_ `const TBounds<float, FCoordinateSpace::Screen> Screen;`
- L81 _public prototype_ `[[nodiscard]] const TBounds<double, FCoordinateSpace::World>& GetWorldSpace(ESpace InSpace) const;`

#### struct `FAvaScreenAlignmentActorInfo::FCoordinateSpace`  
`struct FCoordinateSpace`  
_L14-21_

#### enum `FAvaScreenAlignmentActorInfo::FCoordinateSpace::Type`  
`enum Type : uint8`  
_L16-20_
- L18 _public enumerator_ `World = 0`
- L19 _public enumerator_ `Screen = 1`

#### enum `FAvaScreenAlignmentActorInfo::ESpace`  
`enum class ESpace : uint8`  
_L23-28_
- L25 _public enumerator_ `Actor`
- L26 _public enumerator_ `World`
- L27 _public enumerator_ `Camera`

#### struct `FAvaScreenAlignmentActorInfo::TBounds`  
`template<typename InRealType, uint8 InCoordinateSpace> struct TBounds`  
_L31-65_
- L33 _public typedef_ `using FRealType = InRealType;`
- L34 _public typedef_ `using FVectorType = UE::Math::TVector<FRealType>;`
- L35 _public typedef_ `using FTransformType = UE::Math::TTransform<FRealType>;`
- L37 _public member_ `static constexpr uint8 CoordinateSpace = InCoordinateSpace;`
- L40 _public member_ `FTransformType ToWorld;` — Transform from this coordinate space to world space.
- L43 _public member_ `FTransformType FromWorld;` — Transform from world space to this coordinate space.
- L46 _public member_ `FVectorType Location;` — Location of the actor in this coordinate space.
- L49 _public member_ `FVectorType Center;` — Geometric center in this coordinate space.
- L52 _public member_ `TArray<FVectorType> Vertices;` — Corner vertices in this coordinate space.
- L55 _public member_ `FVectorType Extent;` — Distance from the center to the edges in this coordinate space.
- L57 _public prototype_ `[[nodiscard]] FRealType GetComponent(EAvaHorizontalAlignment InHorizontalAlignment) const;`
- L59 _public prototype_ `[[nodiscard]] FRealType GetComponent(EAvaVerticalAlignment InVerticalAlignment) const;`
- L61 _public prototype_ `[[nodiscard]] FRealType GetComponent(EAvaDepthAlignment InDepthAlignment) const;`
- L63 _public prototype_ `[[nodiscard]] FVectorType GetCoordinate(EAvaHorizontalAlignment InHorizontalAlignment, EAvaVerticalAlignment InVerticalAlignment, EAvaDepthAlignment InDepthAlignment) const;`
- L87 _function_ `GetComponent(EAvaHorizontalAlignment InHorizontalAlignment) const`
- L126 _function_ `GetComponent(EAvaVerticalAlignment InVerticalAlignment) const`
- L165 _function_ `GetComponent(EAvaDepthAlignment InDepthAlignment) const`
- L204 _function_ `GetCoordinate(EAvaHorizontalAlignment InHorizontalAlignment, EAvaVerticalAlignment InVerticalAlignment, EAvaDepthAlignment InDepthAlignment) const`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/AvaViewportAxisUtils.h` (Private)


#### struct `TAvaAxisList`  
`template<typename T> struct TAvaAxisList`  
_L11-16_
- L13 _public member_ `T Horizontal;`
- L14 _public member_ `T Vertical;`
- L15 _public member_ `T Depth;`

#### struct `FAvaViewportAxisOrientation`  
`struct FAvaViewportAxisOrientation`  
_L18-22_
- L20 _public member_ `int32 Index;`
- L21 _public member_ `bool bCodirectional;`

#### class `FAvaViewportAxisUtils`  
`class FAvaViewportAxisUtils`  
_L26-43_
- L29 _public member_ `static constexpr FAvaViewportAxisMap WorldAxisIndexList = { {1, true}, {2, true}, {0, true} };`
- L36 _public prototype_ `[[nodiscard]] static FAvaViewportAxisMap CreateViewportAxisMap(const FTransform& InViewportCameraTransform, const AActor& InActor);` — Takes a viewport and actor's rotation and uses it to determine which of the actor's axes most closely match the camera's.
- L38 _public prototype_ `[[nodiscard]] static FAvaViewportAxisMap CreateViewportAxisMap(const FTransform& InViewportCameraTransform);`
- L40 _public prototype_ `[[nodiscard]] static FAvaViewportAxisMap CreateViewportAxisMap(const TAvaAxisList<FVector>& InReferenceVectors, const TAvaAxisList<FVector>& InAxisVectors);`
- L42 _public prototype_ `static EAxis::Type GetRotationAxisForVectorComponent(int32 InComponent);`

#### Free symbols / members of external scopes

- L24 _typedef_ `using FAvaViewportAxisMap = TAvaAxisList<FAvaViewportAxisOrientation>;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/AvaViewportDataActor.h` (Private)


#### class `AAvaViewportDataActor`  
`class AAvaViewportDataActor : public AActor`  
_L16-35_
- reflection: `UCLASS(NotPlaceable, Hidden, DisplayName = "Motion Design Viewport Data Actor")`
- inherits: `AActor`
- L21 _public prototype_ `AAvaViewportDataActor();`
- L23 _public prototype_ `virtual ~AAvaViewportDataActor() override = default;`
- L26 _public function_ `virtual bool IsLevelBoundsRelevant() const override` — Indicates whether this actor should participate in level bounds calculations.
- L28 _public function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L31 _public member_ `FAvaViewportData ViewportData;` — `UPROPERTY()`
- L34 _private function_ `virtual bool ActorTypeSupportsDataLayer() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/AvalancheViewportModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(AvaViewportLog, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AvaViewportLog, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/ViewportClient/EditorViewportClientUtilityWrapper.h` (Private)


#### class `FEditorViewportClientUtilityWrapper`  
`class FEditorViewportClientUtilityWrapper : public FAvaViewportClientUtilityProvider`  
_L11-60_
- inherits: `FAvaViewportClientUtilityProvider`
- L14 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FEditorViewportClientUtilityWrapper, FAvaViewportClientUtilityProvider) static bool IsValidLevelEditorViewportClient(const FViewportClient* InViewportClient);`
- L17 _public prototype_ `static FEditorViewportClient* GetValidLevelEditorViewportClient(const FViewport* InViewport);`
- L19 _public prototype_ `FEditorViewportClientUtilityWrapper(TSharedPtr<const FEditorViewportClient> InEditorViewportClient);`
- L24 _public prototype_ `virtual FVector2f GetViewportSize() const override;`
- L25 _public prototype_ `virtual FTransform GetViewportViewTransform() const override;`
- L29 _public function_ `virtual bool IsMotionDesignViewport() const override`
- L30 _public prototype_ `virtual const FEditorViewportClient* AsEditorViewportClient() const override;`
- L31 _public function_ `virtual bool SupportsZoom() const override` — No support
- L32 _public prototype_ `virtual float GetUnZoomedFOV() const override;`
- L33 _public prototype_ `virtual float GetZoomedFOV() const override;`
- L34 _public prototype_ `virtual FVector2f GetViewportOffset() const override;`
- L35 _public prototype_ `virtual FIntPoint GetVirtualViewportSize() const override;`
- L36 _public prototype_ `virtual FVector2f GetViewportWidgetSize() const override;`
- L37 _public prototype_ `virtual float GetViewportDPIScale() const override;`
- L38 _public prototype_ `virtual FAvaVisibleArea GetVirtualVisibleArea() const override;`
- L39 _public prototype_ `virtual FAvaVisibleArea GetZoomedVisibleArea() const override;`
- L40 _public prototype_ `virtual FAvaVisibleArea GetVirtualZoomedVisibleArea() const override;`
- L41 _public prototype_ `virtual FAvaVisibleArea GetVisibleArea() const override;`
- L42 _public prototype_ `virtual FVector2f GetUnconstrainedViewportMousePosition() const override;`
- L43 _public prototype_ `virtual FVector2f GetConstrainedViewportMousePosition() const override;`
- L44 _public prototype_ `virtual FVector2f GetUnconstrainedZoomedViewportMousePosition() const override;`
- L45 _public prototype_ `virtual FVector2f GetConstrainedZoomedViewportMousePosition() const override;`
- L46 _public function_ `virtual TSharedPtr<FAvaSnapOperation> GetSnapOperation() const override` — No support
- L47 _public function_ `virtual TSharedPtr<FAvaSnapOperation> StartSnapOperation() override` — No support
- L48 _public function_ `virtual bool EndSnapOperation(FAvaSnapOperation* InSnapOperation) override` — No support
- L49 _public function_ `virtual void OnActorSelectionChanged() override` — Nothing to do
- L50 _public function_ `virtual TSharedPtr<FAvaCameraZoomController> GetZoomController() const override` — No support
- L51 _public function_ `virtual UCameraComponent* GetCameraComponentViewTarget() const override` — No support
- L52 _public function_ `virtual AActor* GetViewTarget() const override` — No support
- L53 _public function_ `virtual void SetViewTarget(TWeakObjectPtr<AActor> InViewTarget) override` — No support
- L54 _public prototype_ `virtual UWorld* GetViewportWorld() const;`
- L55 _public function_ `virtual TSharedPtr<FAvaViewportPostProcessManager> GetPostProcessManager() const` — No support
- L59 _protected member_ `TWeakPtr<const FEditorViewportClient> EditorViewportClientWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/Visualizers/AvaViewportBackgroundVisualizer.h` (Private)


#### class `FAvaViewportBackgroundVisualizer`  
`class FAvaViewportBackgroundVisualizer : public FAvaViewportPostProcessVisualizer`  
_L11-51_
- inherits: `FAvaViewportPostProcessVisualizer`
- L14 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaViewportBackgroundVisualizer, FAvaViewportPostProcessVisualizer) FAvaViewportBackgroundVisualizer(TSharedRef<IAvaViewportClient> InAvaViewportClient);`
- L17 _public prototype_ `virtual ~FAvaViewportBackgroundVisualizer() override = default;`
- L19 _public prototype_ `UTexture* GetTexture() const;`
- L20 _public prototype_ `void SetTexture(UTexture* InTexture);`
- L23 _public prototype_ `virtual void UpdateForViewport(const FAvaVisibleArea& InVisibleArea, const FVector2f& InVisibleAreaOffset, const FVector2f& InWidgetSize, const FVector2f& InCameraOffset) override;`
- L28 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L29 _public prototype_ `virtual FString GetReferencerName() const override;`
- L33 _protected member_ `TObjectPtr<UTexture> Texture;`
- L36 _protected member_ `FVector TextureOffset;` — Offset from the top-left of the viewport where the texture should start in pixel space.
- L39 _protected member_ `FVector TextureScale;` — Scale of the texture. Larger values mean a larger texture.
- L43 _protected prototype_ `void SetTextureInternal(UTexture* InTexture);`
- L46 _protected prototype_ `virtual void LoadPostProcessInfo(const FAvaViewportPostProcessInfo& InPostProcessInfo) override;`
- L47 _protected prototype_ `virtual void UpdatePostProcessInfo(FAvaViewportPostProcessInfo& InPostProcessInfo) const override;`
- L48 _protected prototype_ `virtual void UpdatePostProcessMaterial() override;`
- L49 _protected prototype_ `virtual bool SetupPostProcessSettings(FPostProcessSettings& InPostProcessSettings) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/Visualizers/AvaViewportBoundingBoxVisualizer.h` (Private)


#### class `FAvaLevelViewportBoundingBoxVisualizer`  
`class FAvaLevelViewportBoundingBoxVisualizer : public IAvaViewportBoundingBoxVisualizer`  
_L10-31_
- inherits: `IAvaViewportBoundingBoxVisualizer`
- L13 _public prototype_ `UE_AVA_INHERITS(FAvaLevelViewportBoundingBoxVisualizer, IAvaViewportBoundingBoxVisualizer) FAvaLevelViewportBoundingBoxVisualizer();`
- L16 _public prototype_ `virtual ~FAvaLevelViewportBoundingBoxVisualizer() = default;`
- L19 _public prototype_ `virtual void Draw(UAvaSelectionProviderSubsystem& InSelectionProvider, UAvaBoundsProviderSubsystem& InBoundsProvider, FPrimitiveDrawInterface& InPDI) override;`
- L20 _public function_ `virtual EAvaViewportBoundingBoxOptimizationState GetOptimizationState() const override`
- L21 _public prototype_ `virtual void ResetOptimizationState() override;`
- L25 _protected member_ `EAvaViewportBoundingBoxOptimizationState OptimizationState;`
- L27 _protected prototype_ `void SetOptimizationRenderNothing(double InTaskTimeTaken);`
- L28 _protected prototype_ `void SetOptimizationRenderSelectedActors(double InTaskTimeTaken);`
- L29 _protected prototype_ `void SetOptimizationRenderSelectedActorsAndChildren(double InTaskTimeTaken);`
- L30 _protected prototype_ `void SetOptimizationRenderSelectionBounds();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/Visualizers/AvaViewportChannelVisualizer.h` (Private)


#### class `FAvaViewportChannelVisualizer`  
`class FAvaViewportChannelVisualizer : public FAvaViewportPostProcessVisualizer`  
_L10-21_
- inherits: `FAvaViewportPostProcessVisualizer`
- L13 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaViewportChannelVisualizer, FAvaViewportPostProcessVisualizer) FAvaViewportChannelVisualizer(TSharedRef<IAvaViewportClient> InAvaViewportClient, EAvaViewportPostProcessType InChannel);`
- L16 _public prototype_ `virtual ~FAvaViewportChannelVisualizer() override = default;`
- L19 _public prototype_ `virtual FString GetReferencerName() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/Visualizers/AvaViewportCheckerboardVisualizer.h` (Private)


#### class `FAvaViewportCheckerboardVisualizer`  
`class FAvaViewportCheckerboardVisualizer : public FAvaViewportPostProcessVisualizer`  
_L10-40_
- inherits: `FAvaViewportPostProcessVisualizer`
- L13 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaViewportCheckerboardVisualizer, FAvaViewportPostProcessVisualizer) FAvaViewportCheckerboardVisualizer(TSharedRef<IAvaViewportClient> InAvaViewportClient);`
- L19 _public prototype_ `virtual void UpdatePostProcessMaterial() override;`
- L23 _public prototype_ `virtual FString GetReferencerName() const override;`
- L26 _public prototype_ `void OnSettingChanged(UObject* InSettings, struct FPropertyChangedEvent& InPropertyChangeEvent);`
- L28 _public prototype_ `bool InitPostProcessMaterial();`
- L29 _public prototype_ `bool UpdateFromViewportSettings();`
- L33 _protected member_ `FVector CheckerboardColor0;` — First color of the checkerboard.
- L36 _protected member_ `FVector CheckerboardColor1;` — Second color of the checkerboard.
- L39 _protected member_ `FVector CheckerboardSize;` — Size of the checkerboard (in pixels).

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/Visualizers/AvaViewportPostProcessVisualizer.h` (Private)


#### class `FAvaViewportPostProcessVisualizer`  
`class FAvaViewportPostProcessVisualizer : public IAvaViewportPostProcessVisualizer, public FGCObject, public FEditorUndoClient`  
_L20-80_
- inherits: `IAvaViewportPostProcessVisualizer,FGCObject,FEditorUndoClient`
- L23 _public prototype_ `UE_AVA_INHERITS(FAvaViewportPostProcessVisualizer, IAvaViewportPostProcessVisualizer) FAvaViewportPostProcessVisualizer(TSharedRef<IAvaViewportClient> InAvaViewportClient);`
- L29 _public prototype_ `TSharedPtr<IAvaViewportClient> GetAvaViewportClient() const;`
- L31 _public function_ `float GetPostProcessOpacity() const`
- L32 _public prototype_ `void SetPostProcessOpacity(float InOpacity);`
- L34 _public prototype_ `FAvaViewportPostProcessInfo* GetPostProcessInfo() const;`
- L36 _public prototype_ `void LoadPostProcessInfo();`
- L39 _public prototype_ `virtual bool CanActivate(bool bInSilent) const override;`
- L42 _public prototype_ `virtual void OnActivate();`
- L43 _public prototype_ `virtual void OnDeactivate();`
- L45 _public prototype_ `virtual void UpdateForViewport(const FAvaVisibleArea& InVisibleArea, const FVector2f& InVisibleAreaOffset, const FVector2f& InWidgetSize, const FVector2f& InCameraOffset);`
- L48 _public prototype_ `void ApplyToSceneView(FSceneView* InSceneView) const;`
- L52 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L56 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L57 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L60 _protected member_ `TWeakPtr<IAvaViewportClient> AvaViewportClientWeak;`
- L62 _protected member_ `TObjectPtr<UMaterial> PostProcessBaseMaterial;`
- L64 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PostProcessMaterial;`
- L66 _protected member_ `float PostProcessOpacity;`
- L68 _protected member_ `bool bRequiresTonemapperSetting;`
- L70 _protected prototype_ `void SetPostProcessOpacityInternal(float InOpacity);`
- L72 _protected prototype_ `void UpdatePostProcessInfo();`
- L74 _protected prototype_ `virtual void LoadPostProcessInfo(const FAvaViewportPostProcessInfo& InPostProcessInfo);`
- L75 _protected prototype_ `virtual void UpdatePostProcessInfo(FAvaViewportPostProcessInfo& InPostProcessInfo) const;`
- L77 _protected prototype_ `virtual void UpdatePostProcessMaterial();`
- L79 _protected prototype_ `virtual bool SetupPostProcessSettings(FPostProcessSettings& InPostProcessSettings) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Private/Widgets/SAvaDraggableBox.h` (Private)


#### class `SAvaDraggableBox`  
`class SAvaDraggableBox : public SCompoundWidget`  
_L22-48_
- inherits: `SCompoundWidget`
- desc: A widget for the draggable box itself, which requires its parent to handle its positioning in response to the drag. Users probably shouldn't use this class directly; rather, they should use SAvaDraggableBoxOverlay, which will put its contents into a draggable box and properly handle the dragging without the user having to set it up.
- L25 _public function_ `SLATE_BEGIN_ARGS(SAvaDraggableBox)`
- L27 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SAvaDraggableBoxOverlay>& InDraggableOverlay);`
- L38 _public prototype_ `void OnDragUpdate(const FPointerEvent& InMouseEvent, const FDragInfo& InDragInfo, bool bInDropped);`
- L41 _public prototype_ `FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L42 _public prototype_ `FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L46 _protected member_ `TWeakPtr<SAvaDraggableBoxOverlay> DraggableOverlayWeak;`
- L47 _protected member_ `TSharedPtr<SWidget> InnerWidget;`

#### struct `SAvaDraggableBox::FDragInfo`  
`struct FDragInfo`  
_L32-36_
- L34 _public member_ `FAvaShapeEditorViewportControlPosition OriginalWidgetPosition;`
- L35 _public member_ `FVector2f OriginalMousePosition;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaScreenAlignmentEnums.h` (Public)


#### enum `EAvaRotationAxis`  
`enum class EAvaRotationAxis : uint8`  
_L7-13_
- L9 _public enumerator_ `Yaw = 1 << 0`
- L10 _public enumerator_ `Pitch = 1 << 1`
- L11 _public enumerator_ `Roll = 1 << 2`
- L12 _public enumerator_ `All = Yaw | Pitch | Roll`

#### enum `EAvaWorldAxis`  
`enum class EAvaWorldAxis : uint8`  
_L21-26_
- desc: In the order of the vector componennt determining that direction. X = Depth Y = Horizontal Z = Vertical
- L23 _public enumerator_ `Depth = 0`
- L24 _public enumerator_ `Horizontal = 1`
- L25 _public enumerator_ `Vertical = 2`

#### enum `EAvaScreenAxis`  
`enum class EAvaScreenAxis : uint8`  
_L34-39_
- desc: In the order of the vector componennt determining that direction. X = Horizontal Y = Vertical Z = Depth
- L36 _public enumerator_ `Horizontal = 0`
- L37 _public enumerator_ `Vertical = 1`
- L38 _public enumerator_ `Depth = 2`

#### enum `EAvaActorDistributionMode`  
`enum class EAvaActorDistributionMode : uint8`  
_L41-56_
- L48 _public enumerator_ `CenterDistance` — Equal distance between the center of each element. |===|  |===|   |=|  |=====|
- L55 _public enumerator_ `EdgeDistance` — Equal distance between the edges of each element. |===|  |===|  |=|  |==|

#### enum `EAvaAlignmentSizeMode`  
`enum class EAvaAlignmentSizeMode : uint8`  
_L58-62_
- L60 _public enumerator_ `Self`
- L61 _public enumerator_ `SelfAndChildren`

#### enum `EAvaAlignmentContext`  
`enum class EAvaAlignmentContext : uint8`  
_L64-68_
- L66 _public enumerator_ `SelectedActors`
- L67 _public enumerator_ `Screen`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaScreenAlignmentUtils.h` (Public)


#### class `FAvaScreenAlignmentUtils`  
`class FAvaScreenAlignmentUtils`  
_L19-82_
- L25 _public prototype_ `static void SizeActorToScreen(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, AActor& InActor, bool bInStretchToFit);` — Resizes the actor to the same size as the screen at its current depth.
- L31 _public prototype_ `static void FitActorToScreen(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, AActor& InActor, bool bInStretchToFit, bool bInAlignToNearestAxis);` — Resizes the actor to teh same size as the screen at its current depth and moves it to the center.
- L37 _public prototype_ `static void AlignActorRotationAxis(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, AActor& InActor, EAvaRotationAxis InAxis, const FRotator& InAlignToRotation, bool bInAlignToNearestAxis, bool bInBackwards);` — Aligns the given actor to the given rotation/axis.
- L43 _public prototype_ `static void AlignActorsCameraRotationAxis(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, const TArray<AActor*>& InActors, EAvaRotationAxis InAxis, bool bInAlignToNearestAxis, bool bInBackwards);` — Aligns the given actor to the given axis of the camera's rotation (looking at the camera).
- L50 _public prototype_ `static void AlignActorsHorizontal(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, const TArray<AActor*>& InActors, EAvaHorizontalAlignment InHorizontalAlignment, EAvaAlignmentSizeMode InActorSizeMode, EAvaAlignmentContext InContextType);` — Takes in a list of actors and aligns them hozitontally (their screen X coordinates will match)
- L56 _public prototype_ `static void AlignActorsVertical(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, const TArray<AActor*>& InActors, EAvaVerticalAlignment InVerticalAlignment, EAvaAlignmentSizeMode InActorSizeMode, EAvaAlignmentContext InContextType);` — Takes in a list of actors and aligns them vertically (their screen Y coordinates will match)
- L62 _public prototype_ `static void AlignActorsDepth(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, const TArray<AActor*>& InActors, EAvaDepthAlignment InDepthAlignment, EAvaAlignmentSizeMode InActorSizeMode);` — Takes in a list of actors and aligns them front to back (their screen z coordinates will match)
- L68 _public prototype_ `static void DistributeActorsHorizontal(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, const TArray<AActor*>& InActors, EAvaAlignmentSizeMode InActorSizeMode, EAvaActorDistributionMode InDistributionMode, EAvaAlignmentContext InContextType);` — Takes in a list of actors and distributes them hozitontally (their screen X coordinates will spread evenly)
- L74 _public prototype_ `static void DistributeActorsVertical(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, const TArray<AActor*>& InActors, EAvaAlignmentSizeMode InActorSizeMode, EAvaActorDistributionMode InDistributionMode, EAvaAlignmentContext InContextType);` — Takes in a list of actors and distributes them vertically (their screen Y coordinates will spread evenly)
- L80 _public prototype_ `static void DistributeActorsDepth(const TSharedRef<IAvaViewportWorldCoordinateConverter>& InCoordinateConverter, const TArray<AActor*>& InActors, EAvaAlignmentSizeMode InActorSizeMode, EAvaActorDistributionMode InDistributionMode);` — Takes in a list of actors and distributes them front to back (their screen Z coordinates will spread evenly)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportDataSubsystem.h` (Public)


#### struct `FAvaViewportData`  
`struct FAvaViewportData`  
_L17-35_
- reflection: `USTRUCT()`
- L22 _public member_ `TArray<FAvaViewportGuideInfo> GuideData;` — `UPROPERTY()`
- L25 _public member_ `FAvaViewportPostProcessInfo PostProcessInfo;` — `UPROPERTY()`
- L28 _public member_ `FIntPoint VirtualSize = FIntPoint::ZeroValue;` — `UPROPERTY()`
- L31 _public member_ `EAvaViewportVirtualSizeAspectRatioState VirtualSizeAspectRatioState = EAvaViewportVirtualSizeAspectRatioState::LockedToCamera;` — `UPROPERTY()`
- L34 _public member_ `TSoftObjectPtr<AActor> PilotedCamera;` — `UPROPERTY()`

#### class `UAvaViewportDataSubsystem`  
`class UAvaViewportDataSubsystem : public UWorldSubsystem, public TAvaWorldSubsystemInterface<UAvaViewportDataSubsystem>`  
_L38-61_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem,TAvaWorldSubsystemInterface<UAvaViewportDataSubsystem>`
- L43 _public prototype_ `virtual ~UAvaViewportDataSubsystem() override = default;`
- L45 _public prototype_ `FAvaViewportData* GetData();`
- L47 _public prototype_ `void ModifyDataSource();`
- L49 _public prototype_ `FAvaViewportGuidePresetProvider& GetGuidePresetProvider();`
- L52 _protected member_ `TWeakObjectPtr<AAvaViewportDataActor> DataActorWeak;`
- L54 _protected member_ `FAvaViewportGuidePresetProvider GuidePresetProvider;`
- L56 _protected prototype_ `AAvaViewportDataActor* GetDataActor();`
- L59 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportGeometry.h` (Public)


#### struct `FAvaViewportGeometry`  
`struct FAvaViewportGeometry`  
_L9-15_
- L11 _public member_ `FBox2f CameraBounds = FBox2f(FVector2f::ZeroVector, FVector2f::ZeroVector);`
- L12 _public member_ `FVector2f WidgetSize = FVector2f::ZeroVector;`
- L13 _public member_ `float WidgetDPIScale = 1.f;`
- L14 _public member_ `FIntPoint VirtualSize = FIntPoint::ZeroValue;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportGuideInfo.h` (Public)


#### enum `EAvaViewportGuideState`  
`enum class EAvaViewportGuideState : uint8`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `Disabled`
- L16 _public enumerator_ `Enabled`
- L17 _public enumerator_ `SnappedTo`

#### struct `FAvaViewportGuideInfo`  
`struct FAvaViewportGuideInfo`  
_L21-42_
- reflection: `USTRUCT()`
- L25 _public prototype_ `static bool DeserializeJson(const TSharedRef<FJsonObject>& InJsonObject, FAvaViewportGuideInfo& OutGuideInfo, const FVector2f& InViewportSize);`
- L27 _public prototype_ `bool SerializeJson(const TSharedRef<FJsonObject>& InJsonObject, const FVector2f& InViewportSize) const;`
- L30 _public member_ `TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Horizontal;` — `UPROPERTY()`
- L33 _public member_ `float OffsetFraction = 0.0f;` — `UPROPERTY()`
- L36 _public member_ `EAvaViewportGuideState State = EAvaViewportGuideState::Disabled;` — `UPROPERTY()`
- L39 _public member_ `bool bLocked = false;` — `UPROPERTY()`
- L41 _public function_ `bool IsEnabled() const`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportGuidePresetProvider.h` (Public)


#### struct `FAvaViewportGuidePresetProvider`  
`struct FAvaViewportGuidePresetProvider`  
_L15-31_
- L17 _public prototype_ `bool SaveGuidePreset(const FString& InPresetName, const TArray<FAvaViewportGuideInfo>& InGuides, const FVector2f InViewportSize);`
- L19 _public prototype_ `bool LoadGuidePreset(const FString& InPresetName, TArray<FAvaViewportGuideInfo>& OutGuides, const FVector2f InViewportSize);`
- L21 _public prototype_ `bool RemoveGuidePreset(const FString& InPresetName);`
- L23 _public prototype_ `TArray<FString> GetGuidePresetNames();`
- L25 _public prototype_ `FString GetLastAccessedGuidePresetName() const;`
- L28 _protected member_ `TWeakObjectPtr<AAvaViewportDataActor> DataActorWeak;`
- L30 _protected member_ `FString LastAccessedGuidePresetName;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportPostProcessManager.h` (Public)


#### enum `EAvaViewportPostProcessType`  
`enum class EAvaViewportPostProcessType : uint8`  
_L17-26_
- reflection: `UENUM()`
- L19 _public enumerator_ `None`
- L20 _public enumerator_ `Background`
- L21 _public enumerator_ `RedChannel`
- L22 _public enumerator_ `GreenChannel`
- L23 _public enumerator_ `BlueChannel`
- L24 _public enumerator_ `AlphaChannel`
- L25 _public enumerator_ `Checkerboard`

#### struct `FAvaViewportPostProcessInfo`  
`struct FAvaViewportPostProcessInfo`  
_L29-41_
- reflection: `USTRUCT()`
- L34 _public member_ `EAvaViewportPostProcessType Type = EAvaViewportPostProcessType::None;` — `UPROPERTY()`
- L37 _public member_ `TSoftObjectPtr<UTexture> Texture = nullptr;` — `UPROPERTY()`
- L40 _public member_ `float Opacity = 1.0f;` — `UPROPERTY()`

#### class `FAvaViewportPostProcessManager`  
`class FAvaViewportPostProcessManager : public IAvaTypeCastable`  
_L43-75_
- inherits: `IAvaTypeCastable`
- L46 _public prototype_ `UE_AVA_INHERITS(FAvaViewportPostProcessManager, IAvaTypeCastable) FAvaViewportPostProcessManager(TSharedRef<IAvaViewportClient> InAvaViewportClient);`
- L49 _public prototype_ `virtual ~FAvaViewportPostProcessManager() override = default;`
- L51 _public function_ `TSharedPtr<IAvaViewportClient> GetAvaViewportClient() const`
- L53 _public prototype_ `TSharedPtr<IAvaViewportPostProcessVisualizer> GetVisualizer(EAvaViewportPostProcessType InType) const;`
- L55 _public prototype_ `TSharedPtr<IAvaViewportPostProcessVisualizer> GetActiveVisualizer() const;`
- L57 _public prototype_ `FAvaViewportPostProcessInfo* GetPostProcessInfo() const;`
- L59 _public prototype_ `void UpdateSceneView(FSceneView* InSceneView);`
- L61 _public prototype_ `void LoadPostProcessInfo();`
- L63 _public prototype_ `EAvaViewportPostProcessType GetType() const;`
- L64 _public prototype_ `void SetType(EAvaViewportPostProcessType InType);`
- L66 _public prototype_ `float GetOpacity();`
- L67 _public prototype_ `void SetOpacity(float InOpacity);`
- L70 _protected member_ `TWeakPtr<IAvaViewportClient> AvaViewportClientWeak;`
- L72 _protected member_ `TMap<EAvaViewportPostProcessType, TSharedPtr<IAvaViewportPostProcessVisualizer>> Visualizers;`
- L74 _protected prototype_ `void ModifyDataSource();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportSettings.h` (Public)


#### struct `FAvaLevelViewportSafeFrame`  
`struct FAvaLevelViewportSafeFrame`  
_L15-28_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `float ScreenPercentage = 50.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Safe Frames", Meta=(Units=Percent, UIMin=0, UIMax=100, ClampMin=0, ClampMax=100))` — Distance from the center of the screen to the edge in percent.
- L24 _public member_ `FLinearColor Color = FLinearColor(1, 1, 1, 0.6f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Safe Frames")`
- L27 _public member_ `float Thickness = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Safe Frames", Meta = (UIMin = 1, UIMax = 8, ClampMin = 1, ClampMax = 8))`

#### enum `EAvaShapeEditorOverlayType`  
`enum class EAvaShapeEditorOverlayType : uint8`  
_L31-35_
- reflection: `UENUM()`
- L33 _public enumerator_ `ComponentVisualizerOnly`
- L34 _public enumerator_ `FullDetails`

#### struct `FAvaShapeEditorViewportControlPosition`  
`struct FAvaShapeEditorViewportControlPosition`  
_L38-50_
- reflection: `USTRUCT()`
- L43 _public member_ `TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Left;` — `UPROPERTY()`
- L46 _public member_ `TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Bottom;` — `UPROPERTY()`
- L49 _public member_ `FVector2f AlignmentOffset = FVector2f::ZeroVector;` — `UPROPERTY()`

#### class `UAvaViewportSettings`  
`class UAvaViewportSettings : public UDeveloperSettings`  
_L53-200_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "Viewport"))`
- inherits: `UDeveloperSettings`
- L58 _public prototype_ `UAvaViewportSettings();`
- L61 _public member_ `bool bEnableViewportOverlay;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L64 _public member_ `bool bEnableBoundingBoxes;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L67 _public member_ `TSoftObjectPtr<UMaterial> ViewportBackgroundMaterial;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L70 _public member_ `TSoftObjectPtr<UMaterial> ViewportCheckerboardMaterial;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L73 _public member_ `FLinearColor ViewportCheckerboardColor0;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L76 _public member_ `FLinearColor ViewportCheckerboardColor1;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L79 _public member_ `float ViewportCheckerboardSize;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L82 _public member_ `bool bEnableShapesEditorOverlay;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L86 _public member_ `EAvaShapeEditorOverlayType ShapeEditorOverlayType;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Viewport")` — Whether to show or hide the Shapes In-Viewport controls.
- L89 _public member_ `FAvaShapeEditorViewportControlPosition ShapeEditorViewportControlPosition;` — `UPROPERTY(Config)`
- L92 _public member_ `bool bGridEnabled;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Screen Grid")`
- L95 _public member_ `bool bGridAlwaysVisible;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Screen Grid")`
- L98 _public member_ `int32 GridSize;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Screen Grid", Meta = (UIMin = 1, UIMax = 256, ClampMin = 1, ClampMax = 256))`
- L101 _public member_ `FLinearColor GridColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Screen Grid")`
- L104 _public member_ `float GridThickness;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Screen Grid", Meta = (UIMin = 1, UIMax = 8, ClampMin = 1, ClampMax = 8))`
- L107 _public member_ `bool bPixelGridEnabled;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Pixel Grid")`
- L110 _public member_ `FLinearColor PixelGridColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Pixel Grid")`
- L113 _public member_ `int32 SnapState;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Snapping", Meta = (Bitmask, BitmaskEnum = "/Script/AvalancheViewport.EAvaViewportSnapState"))`
- L116 _public member_ `bool bSnapIndicatorsEnabled;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Snapping")`
- L119 _public member_ `FLinearColor SnapIndicatorColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Snapping")`
- L122 _public member_ `float SnapIndicatorThickness;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Snapping", Meta = (UIMin = 1, UIMax = 8, ClampMin = 1, ClampMax = 8))`
- L125 _public member_ `bool bGuidesEnabled;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Guides")`
- L140 _public member_ `FString GuideConfigPath;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Guides")` — Directory used to load and save guide json config files. The path will be checked against 3 possible locations: - Just itself (/Config/Guides) - Project (/Path/To/Project/Config/Guides) - Plugin (/Path/To/Plugin/Config/Guides) Example values: - /Config/Guides - D:\UnrealEngine\Config\Guides
- L143 _public member_ `FLinearColor EnabledGuideColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Guides")`
- L146 _public member_ `FLinearColor EnabledLockedGuideColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Guides")`
- L149 _public member_ `FLinearColor DisabledGuideColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Guides")`
- L152 _public member_ `FLinearColor DisabledLockedGuideColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Guides")`
- L155 _public member_ `FLinearColor DraggedGuideColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Guides")`
- L159 _public member_ `FLinearColor SnappedToGuideColor;` — `UPROPERTY(Config)` — Not yet implemented
- L162 _public member_ `float GuideThickness;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Guides", Meta = (UIMin = 1, UIMax = 8, ClampMin = 1, ClampMax = 8))`
- L165 _public member_ `bool bSafeFramesEnabled;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Safe Frames")`
- L168 _public member_ `TArray<FAvaLevelViewportSafeFrame> SafeFrames;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Safe Frames")`
- L171 _public member_ `FLinearColor CameraBoundsShadeColor;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Camera Bounds")`
- L174 _public member_ `bool bEnableTextureOverlay = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Texture Overlay")`
- L177 _public member_ `TSoftObjectPtr<UTexture> TextureOverlayTexture;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Texture Overlay")`
- L180 _public member_ `float TextureOverlayOpacity = 0.25;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Texture Overlay", Meta = (UIMin = 0.01, UIMax = 1, ClampMin = 0, ClampMax = 1))`
- L183 _public member_ `bool bTextureOverlayStretch = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Texture Overlay")`
- L186 _public prototype_ `EAvaViewportSnapState GetSnapState() const;` — `UFUNCTION(BlueprintPure, Category = "Motion Design")`
- L189 _public prototype_ `bool HasSnapState(EAvaViewportSnapState InSnapState);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design")`
- L192 _public prototype_ `void SetSnapState(EAvaViewportSnapState InSnapState);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design")`
- L194 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvaViewportSettingsChanged, const UAvaViewportSettings* , FName ) FOnAvaViewportSettingsChanged OnChange;`
- L197 _public prototype_ `void BroadcastSettingChanged(FName InSettingName);`
- L199 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L194 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvaViewportSettingsChanged, const UAvaViewportSettings* , FName ) FOnAvaViewportSettingsChanged OnChange;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportUtils.h` (Public)


#### struct `FAvaViewportUtils`  
`struct FAvaViewportUtils`  
_L18-82_
- L20 _public prototype_ `static FDelegateHandle RegisterViewportClientCaster(FAvaViewportClientCastDelegate::TFuncType InFunction);`
- L21 _public prototype_ `static void UnregisterViewportClientCaster(FDelegateHandle InDelegateHandle);`
- L23 _public prototype_ `static FDelegateHandle RegisterViewportCaster(FAvaViewportCastDelegate::TFuncType InFunction);`
- L24 _public prototype_ `static void UnregisterViewportCaster(FDelegateHandle InDelegateHandle);`
- L30 _public prototype_ `[[nodiscard]] static TSharedPtr<IAvaViewportClient> GetAsAvaViewportClient(FEditorViewportClient* InViewportClient);` — Uses the viewport client casters to attempt to create an IAvaViewportClient. Failing that, it will create backup wrapper for FEditorViewportClient if it's a valid Level Editor viewport.
- L36 _public prototype_ `[[nodiscard]] static FEditorViewportClient* GetAsEditorViewportClient(FViewport* InViewport);` — Uses the viewport caster  to attempt to get an FEditorViewportClient*. The level editor does not properly clean up its viewports so dangling pointers remain making this check necessary.
- L42 _public prototype_ `[[nodiscard]] static TSharedPtr<IAvaViewportClient> GetAvaViewportClient(FViewport* InViewport);` — Uses the viewport caster  to attempt to get an FEditorViewportClient*. The level editor does not properly clean up its viewports so dangling pointers remain making this check necessary.
- L44 _public prototype_ `static bool IsValidViewportSize(const FVector2f& InViewportSize);`
- L45 _public prototype_ `static bool IsValidViewportSize(const FIntPoint& InViewportSize);`
- L47 _public prototype_ `static float CalcFOV(float InViewportDimension, float InDistance);`
- L50 _public prototype_ `[[nodiscard]] static FTransform GetViewportViewTransform(FEditorViewportClient* InViewportClient);` — Calcs a viewport client's scene view and returns a transform of its rotation and location.
- L53 _public prototype_ `static FVector2D GetFrustumSizeAtDistance(float InHorizontalFoVDegrees, float InAspectRatio, double InDistance);` — Calculates the size of the frustum plane parallel to the camera's near clip plane at the given distance.
- L59 _public prototype_ `static FVector ViewportPositionToWorldPositionPerspective(const FVector2f& InViewportSize, const FVector2f& InViewportPosition, const FVector& InViewLocation, const FRotator& InViewRotation, float InHorizontalFoVDegrees, double InDistance);` — Translates the viewport position to the corresponding position on the frustum plane parallel to the camera's near clip plane at the given distance for perspective views.
- L66 _public prototype_ `static FVector ViewportPositionToWorldPositionOrthographic(const FVector2f& InViewportSize, const FVector2f& InViewportPosition, const FVector& InViewLocation, const FRotator& InViewRotation, float InOrthoWidth, double InDistance);` — Translates the viewport position to the corresponding position on the frustum plane parallel to the camera's near clip plane at the given distance for orthographic views.
- L73 _public prototype_ `static void WorldPositionToViewportPositionPerspective(const FVector2f& InViewportSize, const FVector& InWorldPosition, const FVector& InViewLocation, const FRotator& InViewRotation, float InHorizontalFoVDegrees, FVector2f& OutViewportPosition, double& OutDistance);` — Translates the position on the frustum plane parallel to the camera's near clip plane to the corresponding viewport position for perspective views.
- L80 _public prototype_ `static void WorldPositionToViewportPositionOrthographic(const FVector2f& InViewportSize, const FVector& InWorldPosition, const FVector& InViewLocation, const FRotator& InViewRotation, float InOrthoWidth, FVector2f& OutViewportPosition, double& OutDistance);` — Translates the position on the frustum plane parallel to the camera's near clip plane to the corresponding viewport position for orthographic views.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IAvaViewportClient>, FAvaViewportClientCastDelegate, FEditorViewportClient*) DECLARE_DELEGATE_RetVal_OneParam(FEditorViewportClient*, FAvaViewportCastDelegate, FViewport*) struct FAvaViewportUtils { static FDelegateHandle RegisterViewportClientCaster(FAvaViewportClientCastDelegate::TFuncType InFunction); static void UnregisterViewportClientCaster(FDelegateHandle InDelegateHandle); static FDelegateHandle RegisterViewportCaster(FAvaViewportCastDelegate::TFuncType InFunction); static void UnregisterViewportCaster(FDelegateHandle InDelegateHandle); [[nodiscard]] static TSharedPtr<IAvaViewportClient> GetAsAvaViewportClient(FEditorViewportClient* InViewportClient); [[nodiscard]] static FEditorViewportClient* GetAsEditorViewportClient(FViewport* InViewport); [[nodiscard]] static TSharedPtr<IAvaViewportClient> GetAvaViewportClient(FViewport* InViewport); static bool IsValidViewportSize(const FVector2f& InViewportSize); static bool IsValidViewportSize(const FIntPoint& InViewportSize); static float CalcFOV(float InViewportDimension, float InDistance); [[nodiscard]] static FTransform GetViewportViewTransform(FEditorViewportClient* InViewportClient); static FVector2D GetFrustumSizeAtDistance(float InHorizontalFoVDegrees, float InAspectRatio, double InDistance);`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FEditorViewportClient*, FAvaViewportCastDelegate, FViewport*) struct FAvaViewportUtils { static FDelegateHandle RegisterViewportClientCaster(FAvaViewportClientCastDelegate::TFuncType InFunction); static void UnregisterViewportClientCaster(FDelegateHandle InDelegateHandle); static FDelegateHandle RegisterViewportCaster(FAvaViewportCastDelegate::TFuncType InFunction); static void UnregisterViewportCaster(FDelegateHandle InDelegateHandle); [[nodiscard]] static TSharedPtr<IAvaViewportClient> GetAsAvaViewportClient(FEditorViewportClient* InViewportClient); [[nodiscard]] static FEditorViewportClient* GetAsEditorViewportClient(FViewport* InViewport); [[nodiscard]] static TSharedPtr<IAvaViewportClient> GetAvaViewportClient(FViewport* InViewport); static bool IsValidViewportSize(const FVector2f& InViewportSize); static bool IsValidViewportSize(const FIntPoint& InViewportSize); static float CalcFOV(float InViewportDimension, float InDistance); [[nodiscard]] static FTransform GetViewportViewTransform(FEditorViewportClient* InViewportClient); static FVector2D GetFrustumSizeAtDistance(float InHorizontalFoVDegrees, float InAspectRatio, double InDistance); /**`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportVirtualSizeEnums.h` (Public)


#### enum `EAvaViewportVirtualSizeAspectRatioState`  
`enum class EAvaViewportVirtualSizeAspectRatioState : uint8`  
_L8-13_
- reflection: `UENUM()`
- L10 _public enumerator_ `Unlocked`
- L11 _public enumerator_ `Locked`
- L12 _public enumerator_ `LockedToCamera`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaVisibleArea.h` (Public)


#### struct `FAvaVisibleArea`  
`struct FAvaVisibleArea`  
_L7-39_
- L9 _public member_ `FVector2f Offset;`
- L10 _public member_ `FVector2f VisibleSize;`
- L11 _public member_ `FVector2f AbsoluteSize;`
- L12 _public member_ `float DPIScale;`
- L14 _public prototype_ `FAvaVisibleArea();`
- L15 _public prototype_ `FAvaVisibleArea(const FVector2f& InAbsoluteSize);`
- L16 _public prototype_ `FAvaVisibleArea(const FVector2f& InAbsoluteSize, float InDPIScale);`
- L17 _public prototype_ `FAvaVisibleArea(const FVector2f& InOffset, const FVector2f& InVisibleSize, const FVector2f& InAbsoluteSize, float InDPIScale);`
- L19 _public prototype_ `bool IsValid() const;`
- L21 _public prototype_ `bool IsAbsoluteView() const;`
- L22 _public prototype_ `bool IsModifiedView() const;`
- L23 _public prototype_ `bool IsAbsoluteSize() const;`
- L24 _public prototype_ `bool IsZoomedView() const;`
- L25 _public prototype_ `bool IsCentered() const;`
- L26 _public prototype_ `bool IsOffset() const;`
- L28 _public prototype_ `float GetVisibleAreaFraction() const;`
- L29 _public prototype_ `float GetInvisibleAreaFraction() const;`
- L31 _public prototype_ `FVector2f GetVisiblePosition(const FVector2f& AbsolutePosition) const;`
- L32 _public prototype_ `FVector2f GetDPIScaledVisiblePosition(const FVector2f& AbsolutePosition) const;`
- L33 _public prototype_ `FVector2f GetAbsolutePosition(const FVector2f& VisiblePosition) const;`
- L34 _public prototype_ `FVector2f GetDPIScaledAbsolutePosition(const FVector2f& VisiblePosition) const;`
- L35 _public prototype_ `FVector2f GetVisibleAreaCenter() const;`
- L36 _public prototype_ `FVector2f GetAbsoluteVisibleAreaCenter() const;`
- L37 _public prototype_ `FVector2f GetAbsoluteAreaCenter() const;`
- L38 _public prototype_ `FVector2f GetInvisibleSize() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Interaction/AvaCameraZoomController.h` (Public)


#### class `FAvaCameraZoomController`  
`class FAvaCameraZoomController`  
_L12-116_
- L15 _public prototype_ `static bool IsCameraZoomPossible();`
- L17 _public prototype_ `FAvaCameraZoomController(TSharedRef<IAvaViewportClient> InAvaViewportClient, float InFallbackFOV);`
- L19 _public function_ `TSharedPtr<IAvaViewportClient> GetViewportClient() const`
- L24 _public prototype_ `bool CanZoom() const;`
- L26 _public function_ `uint8 GetZoomLevel() const`
- L31 _public prototype_ `void SetZoomLevel(uint8 InZoomLevel);`
- L32 _public prototype_ `bool IsZoomed() const;`
- L34 _public prototype_ `void ZoomIn();`
- L35 _public prototype_ `void ZoomInCursor();`
- L38 _public prototype_ `void ZoomInAroundPoint(const FVector2f& InScreenPosition);` — Zooms in maintaining the current PanOffsetFraction. Uses the absolute screen position.
- L41 _public prototype_ `void ZoomInRelativePoint(const FVector2f& InViewportPosition);` — Zooms in maintaining the position of the given viewport position. Uses the absolute screen position.
- L43 _public prototype_ `void ZoomOut();`
- L44 _public prototype_ `void ZoomOutCursor();`
- L47 _public prototype_ `void ZoomOutAroundPoint(const FVector2f& OutScreenPosition);` — Zooms out maintaining the current PanOffsetFraction. Uses the absolute screen position.
- L50 _public prototype_ `void ZoomOutRelativePoint(const FVector2f& OutViewportPosition);` — Zooms out maintaining the position of the given viewport position. Uses the absolute screen position.
- L52 _public prototype_ `void PanLeft();`
- L53 _public prototype_ `void PanRight();`
- L54 _public prototype_ `void PanUp();`
- L55 _public prototype_ `void PanDown();`
- L57 _public prototype_ `void FrameActor();`
- L59 _public prototype_ `void Reset();`
- L61 _public function_ `const FVector2f& GetPanOffsetFraction() const`
- L66 _public prototype_ `void SetPanOffsetFraction(const FVector2f& InOffsetFraction);`
- L67 _public prototype_ `void PanAdjust(const FVector2f& InDirection);`
- L70 _public prototype_ `void PanAdjustZoomed(const FVector2f& InZoomedDirection);` — Adjusts zoom pan based on current zoom settings.
- L72 _public prototype_ `void CenterOnPoint(const FVector2f& InPoint);`
- L73 _public prototype_ `void CenterOnBox(const FBox& InBoundingBox, const FTransform& InBoxTransform);`
- L75 _public function_ `bool IsPanning() const`
- L80 _public prototype_ `void StartPanning();`
- L81 _public prototype_ `void EndPanning();`
- L83 _public function_ `float GetFallbackFOV() const`
- L88 _public prototype_ `float GetDefaultFOV() const;`
- L89 _public prototype_ `float GetFOV() const;`
- L90 _public prototype_ `FVector2f GetCameraProjectionOffset() const;`
- L92 _public prototype_ `const FAvaVisibleArea& GetCachedVisibleArea() const;`
- L93 _public prototype_ `const FAvaVisibleArea& GetCachedZoomedVisibleArea() const;`
- L95 _public prototype_ `void UpdateVisibleAreas();`
- L98 _protected member_ `TWeakPtr<IAvaViewportClient> AvaViewportClientWeak;`
- L100 _protected member_ `const float FallbackFOV;`
- L102 _protected member_ `uint8 ZoomLevel;`
- L104 _protected member_ `FVector2f PanOffsetFraction;`
- L106 _protected member_ `bool bIsPanning;`
- L108 _protected member_ `FAvaVisibleArea CachedVisibleArea;`
- L109 _protected member_ `FAvaVisibleArea CachedZoomedVisibleArea;`
- L112 _private prototype_ `void ZoomIn_Internal();`
- L113 _private prototype_ `void ZoomOut_Internal();`
- L115 _private prototype_ `void InvalidateViewport();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Interaction/AvaChildTransformLockOperation.h` (Public)


#### class `FAvaChildTransformLockOperation`  
`class FAvaChildTransformLockOperation`  
_L21-38_
- desc: Resets child actors to their original transforms after the parent actor is moved. Will fail if an actor and its grandchild are both selected. Moving the child actor (actor->child->grandchild) will reset the relative transform of the grandchild. To be honest, I'm not sure how UE would handle this by default anyway...
- L24 _public prototype_ `FAvaChildTransformLockOperation(TSharedRef<IAvaViewportClient> InAvaViewportClient);`
- L26 _public prototype_ `void Save();`
- L28 _public prototype_ `void Restore();`
- L31 _protected member_ `TWeakPtr<IAvaViewportClient> AvaViewportClientWeak;`
- L33 _protected member_ `TMap<TWeakObjectPtr<AActor>, FTransform> ChildActorTransforms;`
- L35 _protected member_ `bool bAllowModify;`
- L37 _protected prototype_ `void AttemptModifyOnLockedActors();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Interaction/AvaDragOperation.h` (Public)


#### class `FAvaDragOperation`  
`class FAvaDragOperation`  
_L15-49_
- L18 _public prototype_ `FAvaDragOperation(TSharedRef<IAvaViewportClient> InAvaViewportClient, bool bInAllowSnapToChildren);`
- L19 _public prototype_ `virtual ~FAvaDragOperation();`
- L22 _public prototype_ `void PreMouseUpdate();` — Restore position of actors so they can be accurately dragged.
- L25 _public prototype_ `void PostMouseUpdate();` — Snap actors in their post-drag position.
- L27 _public function_ `bool IsValid() const`
- L33 _protected member_ `TWeakPtr<IAvaViewportClient> AvaViewportClientWeak;`
- L34 _protected member_ `TSharedPtr<FAvaSnapOperation> SnapOperation;`
- L35 _protected member_ `TArray<FAvaSnapPoint> DraggedObjectSnapPoints;`
- L38 _protected member_ `TMap<TWeakObjectPtr<UObject>, FVector> DraggedObjectStartLocations;` — Not const because we'll be moving them
- L45 _protected member_ `bool bValid;` — If we fail to init correctly, this will remain false. The only non-error that would cause this is if we're dragging components. Component drag-snapping us not currently supported.
- L47 _protected prototype_ `void Init(bool bInAllowSnapToChildren);`
- L48 _protected prototype_ `void Cleanup();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Interaction/AvaIsolateActorsOperation.h` (Public)


#### class `FAvaIsolateActorsOperation`  
`class FAvaIsolateActorsOperation`  
_L13-36_
- L16 _public prototype_ `FAvaIsolateActorsOperation(TSharedRef<IAvaViewportClient> InAvaViewportClient);`
- L18 _public function_ `TConstArrayView<TWeakObjectPtr<AActor>> GetIsolatedActors() const`
- L20 _public function_ `bool IsIsolatingActors() const`
- L22 _public prototype_ `bool CanToggleIsolateActors() const;`
- L24 _public prototype_ `void ToggleIsolateActors();`
- L26 _public prototype_ `void IsolateActors();`
- L28 _public prototype_ `void UnisolateActors();`
- L30 _public prototype_ `void AddIsolatedActorPrimitives(FSceneView* InSceneView);`
- L33 _protected member_ `TWeakPtr<IAvaViewportClient> AvaViewportClientWeak;`
- L35 _protected member_ `TArray<TWeakObjectPtr<AActor>> IsolatedActors;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Interaction/AvaSnapDefs.h` (Public)


#### enum `EAvaViewportSnapState`  
`enum class EAvaViewportSnapState : uint8`  
_L8-16_
- reflection: `UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L10 _public enumerator_ `Off = 0 UMETA(Hidden)`
- L11 _public enumerator_ `Global = 1 << 0`
- L12 _public enumerator_ `Screen = 1 << 1`
- L13 _public enumerator_ `Grid = 1 << 2`
- L14 _public enumerator_ `Actor = 1 << 3`
- L15 _public enumerator_ `All = Screen | Grid | Actor`

#### Free symbols / members of external scopes

- L18 _prototype_ `ENUM_CLASS_FLAGS(EAvaViewportSnapState);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Interaction/AvaSnapOperation.h` (Public)


#### struct `FAvaSnapPointLink`  
`struct FAvaSnapPointLink`  
_L21-41_
- L23 _public member_ `float Position;` — X or Y screen position
- L24 _public member_ `int32 SnapIdx;` — Index in the main snap array
- L26 _public function_ `FAvaSnapPointLink(float InPosition, int32 InSnapIdx) : Position(InPosition) , SnapIdx(InSnapIdx)`
- L32 _public function_ `bool operator<(const FAvaSnapPointLink& InOther) const`

#### class `FAvaSnapOperation`  
`class FAvaSnapOperation : public TSharedFromThis<FAvaSnapOperation>`  
_L43-179_
- inherits: `TSharedFromThis<FAvaSnapOperation>`
- L46 _public member_ `static inline const float MaximumSnapDistance = 10.f;`
- L49 _public prototype_ `static void GenerateLocalSnapPoints(AActor* InActor, TArray<FAvaSnapPoint>& InOutSnapPoints);` — Generates snap points for the given actor
- L52 _public prototype_ `static void GenerateLocalSnapPoints(AActor* InActor, const FVector& InOrigin, const FVector& InBoxExtent, TArray<FAvaSnapPoint>& InOutSnapPoints);` — Generates snap points based on a box extent
- L56 _public prototype_ `static void GenerateLocalSnapPoints(UPrimitiveComponent* InComponent, TArray<FAvaSnapPoint>& InOutSnapPoints);` — Generates snap points for the given component
- L59 _public prototype_ `static void GenerateLocalSnapPoints(UPrimitiveComponent* InComponent, const FVector& InOrigin, const FVector& InBoxExtent, TArray<FAvaSnapPoint>& InOutSnapPoints);` — Generates snap points based on a box extent
- L63 _public prototype_ `static void GenerateBoundsSnapPoints(const FVector& InOrigin, const FVector& InBoxExtent, TArray<FAvaSnapPoint>& InOutSnapPoints);` — Generates snap points based on a box extent with no actor reference
- L65 _public prototype_ `FAvaSnapOperation(FEditorViewportClient* InEditorViewportClient);`
- L66 _public prototype_ `virtual ~FAvaSnapOperation();`
- L68 _public function_ `const TArray<FAvaSnapPoint>& GetScreenSnapPoints() const`
- L73 _public function_ `void SetScreenSnapPoints(const TArray<FAvaSnapPoint>& InSnapPoints)`
- L78 _public function_ `const TArray<FAvaSnapPoint>& GetActorSnapPoints() const`
- L84 _public prototype_ `void GenerateScreenSnapPoints();` — Adds screen- and guide-based snap points
- L87 _public prototype_ `void GenerateComponentSnapPoints(const UActorComponent* InComponent);` — Generates snap points, excluding the actor for the given Dynamic Mesh
- L90 _public prototype_ `void GenerateActorSnapPoints(const TConstArrayView<TWeakObjectPtr<AActor>>& InSelectedActors, const TConstArrayView<TWeakObjectPtr<AActor>>& InExcludedActors);` — Generates snap points, excluding the list of actors
- L94 _public prototype_ `void AddActorSnapPoint(const FAvaSnapPoint& InSnapPoint);` — Adds a snap point for a shape to the list of shape snap points
- L97 _public prototype_ `void FinaliseSnapPoints();` — Sorts snap point links
- L99 _public prototype_ `FVector GetSelectionLocation() const;`
- L100 _public prototype_ `FVector GetDragOffset() const;`
- L102 _public prototype_ `const FAvaSnapPoint* const GetScreenSnapPoint(int32 InScreenSnapPointIdx) const;`
- L103 _public prototype_ `const FAvaSnapPoint* const GetActorSnapPoint(int32 InActorSnapPointIdx) const;`
- L104 _public prototype_ `const FAvaSnapPoint* const GetSnapPointByLink(int32 InSnapPointLinkIdx) const;`
- L107 _public prototype_ `bool SnapVectorComponent(float& InOutComponent, const TArray<FAvaSnapPointLink>& InSnapPointLinks, float InViewportSize, int32 InScreenSnapPointCount, int32& OutClosestSnapPointIdx, float& OutDistanceFromSnap);` — Returns true if we're snapped to a point. We may snap to the grid and not to a point. This returns false.
- L110 _public prototype_ `bool SnapX(float& InOutComponent, float InViewportSize, int32& OutClosestSnapPointIdx, float& OutDistanceFromSnap);`
- L111 _public prototype_ `bool SnapY(float& InOutComponent, float InViewportSize, int32& OutClosestSnapPointIdx, float& OutDistanceFromSnap);`
- L113 _public prototype_ `void SnapScreenLocationX(float& InOutScreenLocation);`
- L114 _public prototype_ `void SnapScreenLocationY(float& InOutScreenLocation);`
- L115 _public prototype_ `bool SnapDragLocation(const TArray<FAvaSnapPoint>& InDraggedActorSnapPoints, FVector& OutSnapOffset);`
- L117 _public prototype_ `void SnapScreenLocation(FVector2f& InOutScreenLocation);`
- L118 _public prototype_ `void SnapScreenLocation(FVector2f& InOutScreenLocation, bool bInSnapX, bool bInSnapY);`
- L119 _public prototype_ `bool SnapLocation(FVector& Location);`
- L121 _public function_ `bool WasSnappedToX() const`
- L125 _public prototype_ `void SetSnappedToX(bool bInSnappedTo);`
- L127 _public function_ `bool WasSnappedToY() const`
- L131 _public prototype_ `void SetSnappedToY(bool bInSnappedTo);`
- L133 _public function_ `bool WasSnappedTo() const`
- L138 _public function_ `const FVector2f& GetSnappedToLocation() const`
- L143 _public function_ `const FVector2f& GetSnapDistances() const`
- L153 _protected member_ `FEditorViewportClient* EditorViewportClient;` — Cannot ensure that this is available as a shared pointer. You can validate it by using FAvaViewportUtils::GetAsAvaViewportClient(EditorViewportClient)
- L156 _protected member_ `TSharedPtr<FSceneViewFamilyContext> CachedSceneViewFamily;` — SceneView used for calculating world/viewport translations
- L157 _protected member_ `FSceneView* CachedSceneView;`
- L160 _protected member_ `FVector SelectionStartLocation;` — Transform of the pivot when
- L163 _protected member_ `TArray<FAvaSnapPoint> ScreenSnapPoints;` — Snap points related to the screen and guides
- L166 _protected member_ `TArray<FAvaSnapPoint> ActorSnapPoints;` — Snap points related to actors
- L169 _protected member_ `TArray<FAvaSnapPointLink> SnapPointLinksX;` — Links to the above 2 arrays
- L170 _protected member_ `TArray<FAvaSnapPointLink> SnapPointLinksY;`
- L173 _protected member_ `int32 ClosestSnapPointLinkIdxX;` — Snap stuff
- L174 _protected member_ `int32 ClosestSnapPointLinkIdxY;`
- L175 _protected member_ `bool bSnappedToLinkX;`
- L176 _protected member_ `bool bSnappedToLinkY;`
- L177 _protected member_ `FVector2f SnapDistances;`
- L178 _protected member_ `FVector2f SnappedToLocation;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/ViewportClient/AvaViewportClientUtilityProvider.h` (Public)


#### class `FAvaViewportClientUtilityProvider`  
`class FAvaViewportClientUtilityProvider : public IAvaViewportClient`  
_L11-32_
- inherits: `IAvaViewportClient`
- L14 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaViewportClientUtilityProvider, IAvaViewportClient)`
- L18 _public prototype_ `virtual FVector ViewportPositionToWorldPosition(const FVector2f& InViewportPosition, double InDistance) const override;`
- L19 _public prototype_ `virtual void WorldPositionToViewportPosition(const FVector& InWorldPosition, FVector2f& OutViewportPosition, double& OutDistance) const override;`
- L23 _public prototype_ `virtual FVector2f GetViewportWidgetSize() const override;`
- L24 _public prototype_ `virtual FVector2f GetVirtualViewportScale() const override;`
- L25 _public prototype_ `virtual float GetAverageVirtualViewportScale() const override;`
- L26 _public prototype_ `virtual FVector2D GetZoomedFrustumSizeAtDistance(double InDistance) const override;`
- L27 _public prototype_ `virtual void OnCameraCut(AActor* InTarget, bool bInJumpCut) override;`
- L31 _protected prototype_ `static void NotifyJumpCut(AActor* InViewTarget);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/ViewportClient/IAvaViewportClient.h` (Public)


#### class `IAvaViewportClient`  
`class IAvaViewportClient : public IAvaViewportWorldCoordinateConverter`  
_L26-141_
- inherits: `IAvaViewportWorldCoordinateConverter`
- desc: Virtual size is one that scales the viewport's ruler's apparent size to the given size. A virtual size of 1920x1080 on a 960x540 viewport will mean pixels are half as big.
- L29 _public prototype_ `UE_AVA_INHERITS(IAvaViewportClient, IAvaViewportWorldCoordinateConverter) virtual bool IsMotionDesignViewport() const = 0;`
- L33 _public prototype_ `virtual const FEditorViewportClient* AsEditorViewportClient() const = 0;`
- L36 _public prototype_ `virtual bool SupportsZoom() const = 0;` — Returns true if the viewport client supports 2d zoom.
- L39 _public prototype_ `virtual float GetZoomedFOV() const = 0;` — Gets the FOV of the viewport client when zoomed in, if zoom is supported.
- L42 _public prototype_ `virtual float GetUnZoomedFOV() const = 0;` — Gets the FOV of the viewport client when not zoomed in.
- L45 _public prototype_ `virtual FIntPoint GetVirtualViewportSize() const = 0;` — Gets the full size of the viewport's virtual size when not zoomed in.
- L48 _public prototype_ `virtual FVector2f GetVirtualViewportScale() const = 0;` — Returns (virtual viewport size / viewport size)
- L51 _public prototype_ `virtual float GetAverageVirtualViewportScale() const = 0;` — Returns the average of the above.
- L54 _public prototype_ `virtual FVector2f GetViewportOffset() const = 0;` — Gets the viewport's offset from the containing widget.
- L57 _public prototype_ `virtual FVector2f GetViewportWidgetSize() const = 0;` — Gets the total size of the widget that contains the viewport.
- L60 _public prototype_ `virtual float GetViewportDPIScale() const = 0;` — Gets the DPI scale of the viewport.
- L63 _public prototype_ `virtual FAvaVisibleArea GetVisibleArea() const = 0;` — Gets the viewport's non-zoomed visible area. Only checks the full size of the viewport, ignoring zoom settings.
- L66 _public prototype_ `virtual FAvaVisibleArea GetVirtualVisibleArea() const = 0;` — Gets the viewport's non-zoomed virtual visible area. Only checks the full size of the viewport, ignoring zoom settings.
- L69 _public prototype_ `virtual FAvaVisibleArea GetZoomedVisibleArea() const = 0;` — Gets the viewport's zoomed visible area. Returns the full and calculated-zoom sizes.
- L72 _public prototype_ `virtual FAvaVisibleArea GetVirtualZoomedVisibleArea() const = 0;` — Gets the viewport's zoomed virtual visible area. Returns the full and calculated-zoom sizes.
- L75 _public prototype_ `virtual FVector2D GetZoomedFrustumSizeAtDistance(double InDistance) const = 0;` — Calculates the size of the frustum plane parallel to the camera's near clip plane at the given distance.
- L82 _public prototype_ `virtual FVector2f GetUnconstrainedViewportMousePosition() const = 0;` — Use the absolute mouse position on the viewport and the zoom settings to return the position of that point if the view were at the default zoom. Viewport offset and aspect ratio clamping are ignored.
- L88 _public prototype_ `virtual FVector2f GetConstrainedViewportMousePosition() const = 0;` — Use the absolute mouse position on the viewport and the zoom settings to return the position of that point if the view were at the default zoom.
- L97 _public prototype_ `virtual FVector2f GetUnconstrainedZoomedViewportMousePosition() const = 0;` — Use the absolute mouse position on the viewport and the zoom settings to return the position of that point. Viewport offset and aspect ratio clamping are ignored. E.g. with a zoom of 50% and a viewport resolution of 1000x600. If the mouse is in the far top left corner, the mouse position to resolve to 250x150.
- L106 _public prototype_ `virtual FVector2f GetConstrainedZoomedViewportMousePosition() const = 0;` — Use the absolute mouse position on the viewport and the zoom settings to return the position of that point. E.g. with a zoom of 50% and a viewport resolution of 1000x600. If the mouse is in the far top left corner, the mouse position to resolve to 250x150.
- L109 _public prototype_ `virtual TSharedPtr<FAvaSnapOperation> GetSnapOperation() const = 0;` — Gets an active snap operation on this viewport.
- L112 _public prototype_ `virtual TSharedPtr<FAvaSnapOperation> StartSnapOperation() = 0;` — Starts an active snap operation on this viewport. Snap operations are only weakly stored.
- L118 _public prototype_ `virtual bool EndSnapOperation(FAvaSnapOperation* InSnapOperation = nullptr) = 0;` — Ends the current snap operation and resets any references. If parameter specified, will only cancel the given snap operation.
- L121 _public prototype_ `virtual void OnActorSelectionChanged() = 0;` — Called when the actor selection changes.
- L124 _public prototype_ `virtual TSharedPtr<FAvaCameraZoomController> GetZoomController() const = 0;` — Returns the object responsible for 2d zooming and panning.
- L127 _public prototype_ `virtual UCameraComponent* GetCameraComponentViewTarget() const = 0;` — Returns the currently active camera component view target (if available)
- L130 _public prototype_ `virtual AActor* GetViewTarget() const = 0;` — Returns the currently active actor view target (if available)
- L133 _public prototype_ `virtual void SetViewTarget(TWeakObjectPtr<AActor> InViewTarget) = 0;` — Sets the current view target.
- L136 _public prototype_ `virtual void OnCameraCut(AActor* InCamera, bool bInJumpCut) = 0;` — Call this when a camera cut occurs.
- L138 _public prototype_ `virtual UWorld* GetViewportWorld() const = 0;`
- L140 _public prototype_ `virtual TSharedPtr<FAvaViewportPostProcessManager> GetPostProcessManager() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/ViewportClient/IAvaViewportWorldCoordinateConverter.h` (Public)


#### class `IAvaViewportWorldCoordinateConverter`  
`class IAvaViewportWorldCoordinateConverter : public IAvaTypeCastable`  
_L11-33_
- inherits: `IAvaTypeCastable`
- desc: Provider utility for converting to and from viewport/world coordinates and frustrum sizes.
- L14 _public prototype_ `UE_AVA_INHERITS(IAvaViewportWorldCoordinateConverter, IAvaTypeCastable) virtual FVector2f GetViewportSize() const = 0;`
- L20 _public prototype_ `virtual FVector2D GetFrustumSizeAtDistance(double InDistance) const = 0;` — Calculates the size of the frustum plane parallel to the camera's near clip plane at the given distance.
- L26 _public prototype_ `virtual FVector ViewportPositionToWorldPosition(const FVector2f& InViewportPosition, double InDistance) const = 0;` — Translates the viewport position to the corresponding position on the frustum plane parallel to the camera's near clip plane at the given distance.
- L29 _public prototype_ `virtual void WorldPositionToViewportPosition(const FVector& InWorldPosition, FVector2f& OutViewportPosition, double& OutDistance) const = 0;` — Translates the position on the frustum plane parallel to the camera's near clip plane to the corresponding viewport position.
- L32 _public prototype_ `virtual FTransform GetViewportViewTransform() const = 0;` — Returns the current view transform.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Visualizers/IAvaViewportBoundingBoxVisualizer.h` (Public)


#### enum `EAvaViewportBoundingBoxOptimizationState`  
`enum class EAvaViewportBoundingBoxOptimizationState : uint8`  
_L13-19_
- L15 _public enumerator_ `RenderNothing`
- L16 _public enumerator_ `RenderSelectedActors`
- L17 _public enumerator_ `RenderSelectedActorsAndChildren`
- L18 _public enumerator_ `RenderSelectionBounds`

#### class `IAvaViewportBoundingBoxVisualizer`  
`class IAvaViewportBoundingBoxVisualizer : public IAvaTypeCastable`  
_L21-29_
- inherits: `IAvaTypeCastable`
- L24 _public prototype_ `UE_AVA_INHERITS(IAvaViewportBoundingBoxVisualizer, IAvaTypeCastable) virtual void Draw(UAvaSelectionProviderSubsystem& InSelectionProvider, UAvaBoundsProviderSubsystem& InBoundsProvider, FPrimitiveDrawInterface& InPDI) = 0;`
- L27 _public prototype_ `virtual EAvaViewportBoundingBoxOptimizationState GetOptimizationState() const = 0;`
- L28 _public prototype_ `virtual void ResetOptimizationState() = 0;`

#### struct `FAvaViewportBoundingBoxVisualizerProvider`  
`struct FAvaViewportBoundingBoxVisualizerProvider`  
_L31-34_
- L33 _public prototype_ `static TSharedRef<IAvaViewportBoundingBoxVisualizer> CreateVisualizer();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Visualizers/IAvaViewportPostProcessVisualizer.h` (Public)


#### class `IAvaViewportPostProcessVisualizer`  
`class IAvaViewportPostProcessVisualizer : public IAvaTypeCastable`  
_L7-13_
- inherits: `IAvaTypeCastable`
- L10 _public prototype_ `UE_AVA_INHERITS(IAvaViewportPostProcessVisualizer, IAvaTypeCastable) virtual bool CanActivate(bool bInSilent) const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/Widgets/SAvaDraggableBoxOverlay.h` (Public)


#### class `SAvaDraggableBoxOverlay`  
`class SAvaDraggableBoxOverlay : public SCompoundWidget`  
_L20-53_
- inherits: `SCompoundWidget`
- desc: Class that can be used to place a draggable box into a viewport or some other large widget as an overlay. Just place the widget that you want to be draggable as the contents of SAvaDraggableBoxOverlay.
- L23 _public function_ `SLATE_BEGIN_ARGS(SAvaDraggableBoxOverlay)`
- L24 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `FVector2f GetBoxAlignmentOffset() const;` — Returns the current position of the box on the viewport.
- L33 _public prototype_ `void SetBoxAlignmentOffset(const FVector2f& InOffset, bool bInNormalisePosition = true);` — Sets the box offset from its alignment side. Bottom offsets from bottom, etc.
- L35 _public prototype_ `EHorizontalAlignment GetBoxHorizontalAlignment() const;`
- L37 _public prototype_ `void SetBoxHorizontalAlignment(EHorizontalAlignment InAlignment);`
- L39 _public prototype_ `EVerticalAlignment GetBoxVerticalAlignment() const;`
- L41 _public prototype_ `void SetBoxVerticalAlignment(EVerticalAlignment InAlignment);`
- L43 _public prototype_ `void SavePosition();`
- L46 _protected member_ `TSharedPtr<SBox> Container;`
- L47 _protected member_ `TSharedPtr<SWidget> DraggableBox;`
- L48 _protected member_ `EHorizontalAlignment HorizontalAlignment = HAlign_Fill;`
- L49 _protected member_ `EVerticalAlignment VerticalAlignment = VAlign_Fill;`
- L50 _protected member_ `FMargin Padding;`
- L52 _protected prototype_ `FMargin GetPadding() const;`
