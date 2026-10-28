# Editor / MeshPaint

- module root: `Source/Editor/MeshPaint`
- headers: 18; symbols: 465
- symbol kinds: class=24, delegate=2, enum=7, enumerator=15, function=51, macro=8, member=124, namespace=1, prototype=213, struct=14, typedef=4, variable=2
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools
- PrivateDependencyModuleNames: AppFramework, Core, CoreUObject, DesktopPlatform, EditorFramework, Engine, InputCore, MainFrame, MeshDescription, PropertyEditor, RHI, RenderCore, Slate, SlateCore, SourceControl, StaticMeshDescription, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, AssetTools, LevelEditor

### `Source/Editor/MeshPaint/Private/ImportVertexColorOptionsCustomization.h` (Private)


#### class `FVertexColorImportOptionsCustomization`  
`class FVertexColorImportOptionsCustomization : public IDetailCustomization`  
_L12-24_
- inherits: `IDetailCustomization`
- desc: Customization for importing vertex colors from a texture see SImportVertexColorOptions
- L15 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L23 _private prototype_ `TSharedRef<SHorizontalBox> CreateColorChannelWidget(TSharedRef<class IPropertyHandle> ChannelProperty);`

### `Source/Editor/MeshPaint/Private/SImportVertexColorOptions.h` (Private)


#### class `UVertexColorImportOptions`  
`class UVertexColorImportOptions : public UObject`  
_L15-66_
- reflection: `UCLASS()`
- inherits: `UObject`
- L20 _public function_ `UVertexColorImportOptions() : UVIndex(0), LODIndex(0), bRed(true), bBlue(true), bGreen(true), bAlpha(true), bImportToInstance(true), NumLODs(0), bCanImportToInstance(false)`
- L24 _public member_ `int UVIndex;` — `UPROPERTY(EditAnywhere, Category=Options)` — Texture Coordinate Channel to use for Sampling the Texture
- L28 _public member_ `int LODIndex;` — `UPROPERTY(EditAnywhere, Category = Options)` — LOD Index to import the Vertex Colors to
- L32 _public member_ `bool bRed;` — `UPROPERTY(EditAnywhere, Category = Options)` — Red Texture Channel
- L36 _public member_ `bool bBlue;` — `UPROPERTY(EditAnywhere, Category = Options)` — Blue Texture Channel
- L40 _public member_ `bool bGreen;` — `UPROPERTY(EditAnywhere, Category = Options)` — Green Texture Channel
- L44 _public member_ `bool bAlpha;` — `UPROPERTY(EditAnywhere, Category = Options)` — Alpha Texture Channel
- L48 _public member_ `bool bImportToInstance;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether or not to import the Vertex Colors to Mesh Component instance or the underlying Static Mesh
- L50 _public member_ `TMap<int32, int32> LODToMaxUVMap;`
- L51 _public member_ `int32 NumLODs;`
- L54 _public member_ `bool bCanImportToInstance;` — `UPROPERTY()`
- L56 _public function_ `FColor CreateColorMask() const`

#### class `SImportVertexColorOptions`  
`class SImportVertexColorOptions : public SCompoundWidget`  
_L71-132_
- inherits: `SCompoundWidget`
- L74 _public function_ `SLATE_BEGIN_ARGS(SImportVertexColorOptions)`
- L81 _public prototype_ `void Construct(const FArguments& InArgs);`
- L82 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L84 _public function_ `FReply OnImport()`
- L94 _public function_ `FReply OnCancel()`
- L104 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L114 _public function_ `bool ShouldImport() const`
- L119 _public function_ `UVertexColorImportOptions* GetOptions() const`
- L124 _public function_ `SImportVertexColorOptions()`
- L127 _private member_ `TWeakPtr< SWindow > WidgetWindow;`
- L128 _private member_ `TSharedPtr< SButton > ImportButton;`
- L129 _private member_ `bool bShouldImport;`
- L130 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L131 _private member_ `UVertexColorImportOptions* Options;`

### `Source/Editor/MeshPaint/Public/BaseMeshPaintGeometryAdapter.h` (Public)


#### class `FBaseMeshPaintGeometryAdapter`  
`class FBaseMeshPaintGeometryAdapter : public IMeshPaintGeometryAdapter`  
_L17-40_
- inherits: `IMeshPaintGeometryAdapter`
- desc: Base mesh paint geometry adapter, handles basic sphere intersection using a Octree
- L21 _public prototype_ `virtual bool Initialize() override;` — Start IMeshPaintGeometryAdapter Overrides
- L22 _public prototype_ `virtual const TArray<FVector>& GetMeshVertices() const override;`
- L23 _public prototype_ `virtual const TArray<uint32>& GetMeshIndices() const override;`
- L24 _public prototype_ `virtual void GetVertexPosition(int32 VertexIndex, FVector& OutVertex) const override;`
- L25 _public prototype_ `virtual TArray<uint32> SphereIntersectTriangles(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const override;`
- L26 _public prototype_ `virtual void GetInfluencedVertexIndices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TSet<int32> &InfluencedVertices) const override;`
- L27 _public prototype_ `virtual void GetInfluencedVertexData(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TArray<TPair<int32, FVector>>& OutData) const override;`
- L28 _public prototype_ `virtual TArray<FVector> SphereIntersectVertices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const override;`
- L31 _public prototype_ `virtual bool InitializeVertexData() = 0;`
- L33 _protected prototype_ `bool BuildOctree();`
- L36 _protected member_ `TArray<FVector> MeshVertices;` — Index and Vertex data populated by derived classes in InitializeVertexData
- L37 _protected member_ `TArray<uint32> MeshIndices;`
- L39 _protected member_ `TUniquePtr<FMeshPaintTriangleOctree> MeshTriOctree;` — Octree used for reducing the cost of sphere intersecting with triangles / vertices

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHPAINT_API`

### `Source/Editor/MeshPaint/Public/IMeshPaintGeometryAdapter.h` (Public)


#### class `IMeshPaintGeometryAdapter`  
`class IMeshPaintGeometryAdapter`  
_L16-99_
- desc: Interface for a class to provide mesh painting support for a subclass of UMeshComponent
- L20 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 MeshLODIndex) = 0;` — Constructs the adapter for a specific LOD index using the mesh component
- L23 _public prototype_ `virtual ~IMeshPaintGeometryAdapter() = default;` — D-tor
- L26 _public prototype_ `virtual bool Initialize() = 0;` — Returns whether or not initialization of necessary data was successful
- L29 _public prototype_ `virtual void OnAdded() = 0;` — Called when this adapter is created and added to its owner (used for setting up)
- L32 _public prototype_ `virtual void OnRemoved() = 0;` — Called when this adapter is removed from its owner and deleted (used for cleaning up)
- L35 _public prototype_ `virtual bool IsValid() const = 0;` — Returns whether or not this adapter is in a valid state
- L38 _public prototype_ `virtual bool SupportsTexturePaint() const = 0;` — Whether or not this adapter supports texture painting
- L41 _public prototype_ `virtual bool SupportsVertexPaint() const = 0;` — Whether or not this adapter supports vertex painting
- L44 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const = 0;` — Returns the result of tracing a line on the component represented by this adapter
- L47 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) = 0;` — Retrieves a list of textures which are suitable for painting
- L50 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture) const = 0;` — Applies or removes an override texture to use while rendering the meshes materials
- L53 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) = 0;` — Reference collecting to prevent GC-ing
- L56 _public prototype_ `virtual const TArray<FVector>& GetMeshVertices() const = 0;` — Returns the vertices for the current LOD index in the Mesh
- L59 _public prototype_ `virtual const TArray<uint32>& GetMeshIndices() const = 0;` — Returns the indices for the current LOD index in the Mesh
- L62 _public prototype_ `virtual void GetVertexPosition(int32 VertexIndex, FVector& OutVertex) const = 0;` — Returns the Vertex Position at Vertex Index from the Mesh
- L65 _public prototype_ `virtual void SetVertexColor(int32 VertexIndex, FColor Color, bool bInstance = true) = 0;` — Sets the Vertex Color at Vertex Index to Color inside of the Mesh
- L68 _public prototype_ `virtual void GetTextureCoordinate(int32 VertexIndex, int32 ChannelIndex, FVector2D& OutTextureCoordinate) const = 0;` — Returns the Texture Coordinate at Vertex Index from the Mesh
- L71 _public prototype_ `virtual void GetVertexColor(int32 VertexIndex, FColor& OutColor, bool bInstance = true) const = 0;` — Returns the Vertex Color at Vertex Index from the Mesh
- L74 _public prototype_ `virtual FMatrix GetComponentToWorldMatrix() const = 0;` — Returns the Component to World matrix from the Mesh Component
- L77 _public prototype_ `virtual void PreEdit() = 0;` — Pre Edit to setup necessary data
- L80 _public prototype_ `virtual void PostEdit() = 0;` — Post Edit to clear up or update necessary data
- L83 _public prototype_ `static void DefaultApplyOrRemoveTextureOverride(UMeshComponent* InMeshComponent, UTexture* SourceTexture, UTexture* OverrideTexture);` — Default functionality for applying or remove a texture override
- L86 _public prototype_ `static void DefaultQueryPaintableTextures(int32 MaterialIndex, const UMeshComponent* MeshComponent, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList);` — Default functionality for querying textures from a mesh component which are suitable for texture painting
- L89 _public prototype_ `virtual TArray<uint32> SphereIntersectTriangles(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const = 0;` — Returns the triangle indices which intersect with the given sphere
- L92 _public prototype_ `virtual void GetInfluencedVertexIndices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TSet<int32> &InfluencedVertices) const = 0;` — Retrieves the influenced vertex indices which intersect the given sphere
- L95 _public prototype_ `virtual void GetInfluencedVertexData(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TArray<TPair<int32, FVector>>& OutData) const = 0;` — Retrieves the influenced vertex indices and positions that intersect the given sphere
- L98 _public prototype_ `virtual TArray<FVector> SphereIntersectVertices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const = 0;` — Returns the vertex positions which intersect the given sphere

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHPAINT_API`

### `Source/Editor/MeshPaint/Public/IMeshPaintGeometryAdapterFactory.h` (Public)


#### class `IMeshPaintGeometryAdapterFactory`  
`class IMeshPaintGeometryAdapterFactory`  
_L14-22_
- desc: Factory for IMeshPaintGeometryAdapter
- L17 _public prototype_ `virtual TSharedPtr<IMeshPaintGeometryAdapter> Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) const = 0;`
- L18 _public prototype_ `virtual void InitializeAdapterGlobals() = 0;`
- L19 _public prototype_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) = 0;`
- L20 _public prototype_ `virtual void CleanupGlobals() = 0;`
- L21 _public prototype_ `virtual ~IMeshPaintGeometryAdapterFactory() = default;`

### `Source/Editor/MeshPaint/Public/IMeshPaintMode.h` (Public)


#### class `IMeshPaintEdMode`  
`class IMeshPaintEdMode : public FEdMode`  
_L25-101_
- inherits: `FEdMode`
- desc: Mesh Paint editor mode
- L29 _public prototype_ `IMeshPaintEdMode();` — Constructor
- L32 _public prototype_ `virtual ~IMeshPaintEdMode();` — Destructor
- L34 _public prototype_ `virtual void Initialize() = 0;`
- L35 _public prototype_ `virtual TSharedPtr<class FModeToolkit> GetToolkit() = 0;`
- L38 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L39 _public function_ `virtual FString GetReferencerName() const override`
- L45 _public function_ `virtual bool UsesToolkits() const override` — FEdMode interface
- L46 _public prototype_ `virtual void Enter() override;`
- L47 _public prototype_ `virtual void Exit() override;`
- L48 _public prototype_ `virtual bool ProcessCapturedMouseMoves(FEditorViewportClient* InViewportClient, FViewport* InViewport, const TArrayView<FIntPoint>& CapturedMouseMoves) override;`
- L49 _public function_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override`
- L50 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L51 _public prototype_ `virtual bool InputKey( FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent ) override;`
- L52 _public prototype_ `virtual void PostUndo() override;`
- L53 _public prototype_ `virtual void Render( const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI ) override;`
- L54 _public prototype_ `virtual bool Select( AActor* InActor, bool bInSelected ) override;`
- L55 _public prototype_ `virtual void ActorSelectionChangeNotify() override;`
- L56 _public function_ `virtual bool AllowWidgetMove() override`
- L57 _public function_ `virtual bool ShouldDrawWidget() const override`
- L58 _public function_ `virtual bool UsesTransformWidget() const override`
- L59 _public prototype_ `virtual void Tick( FEditorViewportClient* ViewportClient, float DeltaTime ) override;`
- L60 _public prototype_ `virtual bool ProcessEditDelete() override;`
- L64 _public prototype_ `IMeshPainter* GetMeshPainter();` — Returns the mesh painter for this mode
- L67 _private prototype_ `void OnPreSaveWorld(UWorld* World, FObjectPreSaveContext ObjectSaveContext);` — Called prior to saving a level
- L70 _private prototype_ `void OnPostSaveWorld(UWorld* World, FObjectPostSaveContext ObjectSaveContext);` — Called after saving a level
- L73 _private prototype_ `void OnPostImportAsset(UFactory* Factory, UObject* Object);` — Called when an asset has just been imported
- L76 _private prototype_ `void OnPostReimportAsset(UObject* Object, bool bSuccess);` — Called when an asset has just been reimported
- L79 _private prototype_ `void OnAssetRemoved(const FAssetData& AssetData);` — Called when an asset is deleted
- L82 _private prototype_ `void OnVRAction( FEditorViewportClient& ViewportClient, class UViewportInteractor* Interactor, const struct FViewportActionKeyInput& Action, bool& bOutIsInputCaptured, bool& bWasHandled );` — Called when the user presses a button on their motion controller device
- L86 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);` — Called when rerunning a construction script causes objects to be replaced
- L88 _private prototype_ `void OnResetViewMode();`
- L91 _private member_ `UViewportInteractor* PaintingWithInteractorInVR;` — When painting in VR, this is the hand index that we're painting with.  Otherwise INDEX_NONE.
- L94 _private member_ `bool bWasSelectionLockedOnStart;` — Will store the state of selection locks on start of paint mode so that it can be restored on close
- L97 _private member_ `FDelegateHandle SelectionChangedHandle;` — Delegate handle for registered selection change lambda
- L100 _protected member_ `IMeshPainter* MeshPainter;` — Painter used by this edit mode for applying paint actions

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPAINT_API`

### `Source/Editor/MeshPaint/Public/IMeshPainter.h` (Public)


#### class `IMeshPainter`  
`class IMeshPainter`  
_L29-133_
- desc: Base class for creating a mesh painter, has basic functionality combined with IMeshPaintMode and requires painting/situation-specific information to do actual painting
- L32 _public prototype_ `IMeshPainter();`
- L33 _public prototype_ `virtual ~IMeshPainter();`
- L36 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) = 0;` — Renders ray widgets for the active viewport interactors
- L39 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime);` — Base ticking functionality, keeps track of time and caches VR interactors
- L42 _public function_ `virtual bool IsPainting()` — Returns whether or not painting (of any sorts) is in progress
- L45 _public prototype_ `virtual void RegisterCommands(TSharedRef<FUICommandList> CommandList);` — Registers a base set of commands for altering UBrushSettings
- L48 _public prototype_ `virtual void UnregisterCommands(TSharedRef<FUICommandList> CommandList);` — Unregisters a base set of commands
- L51 _public prototype_ `virtual bool Paint(FViewport* Viewport, const FVector& InCameraOrigin, const FVector& InRayOrigin, const FVector& InRayDirection);` — 'Normal' painting functionality, called when the user tries to paint on a mesh using the mouse
- L54 _public prototype_ `virtual bool Paint(FViewport* Viewport, const FVector& InCameraOrigin, const TArrayView<TPair<FVector, FVector>>& Rays);` — 'Normal' painting functionality, called when the user tries to paint on a mesh using the mouse
- L57 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent);` — Allows painter to act on specific key actions
- L60 _public prototype_ `virtual void FinishPainting();` — If painting is in progress will propagate changes and cleanup the painting state
- L63 _public prototype_ `virtual void ActorSelected(AActor* Actor) = 0;` — Is called by the owning EdMode when an actor is de-selected in the viewport
- L65 _public prototype_ `virtual void ActorDeselected(AActor* Actor) = 0;` — Is called by the owning EdMode when an actor is selected in the viewport
- L68 _public prototype_ `virtual TSharedPtr<IMeshPaintGeometryAdapter> GetMeshAdapterForComponent( const UMeshComponent* Component) = 0;` — Tries to retrieves a valid mesh adapter for the given component (derived painters can cache these hence no base implementation)
- L71 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) = 0;` — Functionality to collect painter referenced objects to prevent GC
- L74 _public prototype_ `virtual UPaintBrushSettings* GetBrushSettings() = 0;` — Returns an instance of UPaintBrushSettings (base or derived) which contains the basic settings used for painting
- L77 _public prototype_ `virtual UMeshPaintSettings* GetPainterSettings() = 0;` — Returns an instance of UMeshPainterSettings used for specific types of painting
- L80 _public prototype_ `virtual TSharedPtr<class SWidget> GetWidget() = 0;` — Returns a SWidget which represents the painters state and allows for changes / extra functionality
- L83 _public prototype_ `virtual const FHitResult GetHitResult(const FVector& Origin, const FVector& Direction) = 0;` — Returns a HitResult structure given a origin and direction to trace a ray for
- L86 _public prototype_ `virtual void Refresh() = 0;` — Refreshes the underlying data
- L89 _public prototype_ `virtual void Reset() = 0;` — Resets the state of the painter
- L92 _protected prototype_ `virtual bool PaintInternal(const FVector& InCameraOrigin, const TArrayView<TPair<FVector, FVector>>& Rays, EMeshPaintAction PaintAction, float PaintStrength) = 0;` — Internal painting functionality, is called from Paint and PaintVR and implemented in the derived painters
- L95 _protected prototype_ `void RenderInteractors(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI, bool bRenderVertices, ESceneDepthPriorityGroup DepthGroup = SDPG_World);` — Renders viewport interactor widget
- L98 _protected prototype_ `virtual void RenderInteractorWidget(const FVector& InCameraOrigin, const FVector& InRayOrigin, const FVector& InRayDirection, FPrimitiveDrawInterface* PDI, EMeshPaintAction PaintAction, bool bRenderVertices, ESceneDepthPriorityGroup DepthGroup = SDPG_World);` — Functionality for rendering the interactor widget given its positional information and paint action
- L102 _protected member_ `bool bArePainting;` — Flag for whether or not we are currently painting
- L104 _protected member_ `float TimeSinceStartedPainting;` — Time kept since the user has started painting
- L106 _protected member_ `float Time;` — Overall time value kept for drawing effects
- L108 _protected member_ `float WidgetLineThickness;`
- L109 _protected member_ `FLinearColor WidgetLineColor;`
- L110 _protected member_ `FLinearColor VertexPointColor;`
- L111 _protected member_ `FLinearColor HoverVertexPointColor;`
- L113 _protected member_ `TSharedPtr<FUICommandList> UICommandList;`
- L117 _protected prototype_ `void BeginTransaction(const FText Description);` — Begins and keeps track of an Editor transaction with the given Description
- L119 _protected prototype_ `void EndTransaction();` — Ends the current transaction
- L121 _protected member_ `FScopedTransaction* PaintTransaction;` — Painting transaction instance which is currently active
- L126 _private prototype_ `void ChangeBrushRadius(float Multiplier);` — Change the brush radius by a percentage, multiplied by the given value.
- L129 _private prototype_ `void ChangeBrushStrength(float Multiplier);` — Change the brush radius by one increment, multiplied by the given value
- L132 _private prototype_ `void ChangeBrushFalloff(float Multiplier);` — Change the brush radius by one increment, multiplied by the given value

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPAINT_API`

### `Source/Editor/MeshPaint/Public/MeshPaintAdapterFactory.h` (Public)


#### class `FMeshPaintAdapterFactory`  
`class FMeshPaintAdapterFactory`  
_L17-27_
- L20 _public member_ `static TArray<TSharedPtr<IMeshPaintGeometryAdapterFactory>> FactoryList;`
- L23 _public prototype_ `static TSharedPtr<class IMeshPaintGeometryAdapter> CreateAdapterForMesh(UMeshComponent* InComponent, int32 InPaintingMeshLODIndex);`
- L24 _public prototype_ `static void InitializeAdapterGlobals();`
- L25 _public prototype_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector);`
- L26 _public prototype_ `static void CleanupGlobals();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPAINT_API`

### `Source/Editor/MeshPaint/Public/MeshPaintHelpers.h` (Public)


#### struct `FPerVertexPaintActionArgs`  
`struct FPerVertexPaintActionArgs`  
_L33-40_
- desc: Parameters for paint actions, stored together for convenience
- L35 _public member_ `IMeshPaintGeometryAdapter* Adapter;`
- L36 _public member_ `FVector CameraPosition;`
- L37 _public member_ `FHitResult HitResult;`
- L38 _public member_ `const UPaintBrushSettings* BrushSettings;`
- L39 _public member_ `EMeshPaintAction Action;`

#### class `MeshPaintHelpers`  
`class MeshPaintHelpers`  
_L46-180_
- L50 _public prototype_ `static void RemoveInstanceVertexColors(UObject* Obj);` — Removes vertex colors associated with the object
- L53 _public prototype_ `static void RemoveComponentInstanceVertexColors(UStaticMeshComponent* StaticMeshComponent);` — Removes vertex colors associated with the static mesh component
- L56 _public prototype_ `static bool PropagateColorsToRawMesh(UStaticMesh* StaticMesh, int32 LODIndex, FStaticMeshComponentLODInfo& ComponentLODInfo);` — Propagates per-instance vertex colors to the underlying Static Mesh for the given LOD Index
- L59 _public prototype_ `static uint32 GetVertexColorBufferSize(UMeshComponent* MeshComponent, int32 LODIndex, bool bInstance);` — Retrieves the Vertex Color buffer size for the given LOD level in the Static Mesh
- L62 _public prototype_ `static TArray<FVector> GetVerticesForLOD(const UStaticMesh* StaticMesh, int32 LODIndex);` — Retrieves the vertex positions from the given LOD level in the Static Mesh
- L65 _public prototype_ `static TArray<FColor> GetColorDataForLOD(const UStaticMesh* StaticMesh, int32 LODIndex);` — Retrieves the vertex colors from the given LOD level in the Static Mesh
- L68 _public prototype_ `static TArray<FColor> GetInstanceColorDataForLOD(const UStaticMeshComponent* MeshComponent, int32 LODIndex);` — Retrieves the per-instance vertex colors from the given LOD level in the StaticMeshComponent
- L71 _public prototype_ `static void SetInstanceColorDataForLOD(UStaticMeshComponent* MeshComponent, int32 LODIndex, const TArray<FColor>& Colors);` — Sets the specific (LOD Index) per-instance vertex colors for the given StaticMeshComponent to the supplied Color array
- L74 _public prototype_ `static void SetInstanceColorDataForLOD(UStaticMeshComponent* MeshComponent, int32 LODIndex, const FColor FillColor, const FColor MaskColor);` — Sets the specific (LOD Index) per-instance vertex colors for the given StaticMeshComponent to a single Color value
- L77 _public prototype_ `static void FillStaticMeshVertexColors(UStaticMeshComponent* MeshComponent, int32 LODIndex, const FColor FillColor, const FColor MaskColor);` — Fills all vertex colors for all LODs found in the given mesh component with Fill Color
- L78 _public prototype_ `static void FillSkeletalMeshVertexColors(USkeletalMeshComponent* MeshComponent, int32 LODIndex, const FColor FillColor, const FColor MaskColor);`
- L81 _public prototype_ `static void SetColorDataForLOD(USkeletalMesh* SkeletalMesh, int32 LODIndex, const FColor FillColor, const FColor MaskColor);` — Sets all vertex colors for a specific LOD level in the SkeletalMesh to FillColor
- L83 _public prototype_ `static void ApplyFillWithMask(FColor& InOutColor, const FColor& MaskColor, const FColor& FillColor);`
- L86 _public prototype_ `static void ImportVertexColorsFromTexture(UMeshComponent* MeshComponent);` — Helper function to import Vertex Colors from a Texture to the specified MeshComponent (makes use of SImportVertexColorsOptions Widget)
- L89 _public prototype_ `static bool IsInVRMode(const FEditorViewportClient* ViewportClient);` — Checks whether or not the given Viewport Client is a VR editor viewport client
- L92 _public prototype_ `static void SetViewportColorMode(EMeshPaintColorViewMode ColorViewMode, FEditorViewportClient* ViewportClient);` — Forces the Viewport Client to render using the given Viewport Color ViewMode
- L95 _public prototype_ `static void SetRealtimeViewport(bool bRealtime);` — Sets whether or not the level viewport should be real time rendered move or viewport as parameter?
- L98 _public prototype_ `static void ForceRenderMeshLOD(UMeshComponent* Component, int32 LODIndex);` — Forces the component to render LOD level at LODIndex instead of the view-based LOD level ( X = 0 means do not force the LOD, X > 0 means force the lod to X - 1 )
- L101 _public prototype_ `static void ClearMeshTextureOverrides(const IMeshPaintGeometryAdapter& GeometryInfo, UMeshComponent* InMeshComponent);` — Clears all texture overrides for this component.
- L104 _public prototype_ `static void ApplyVertexColorsToAllLODs(IMeshPaintGeometryAdapter& GeometryInfo, UMeshComponent* InMeshComponent);` — Applies vertex color painting found on LOD 0 to all lower LODs.
- L107 _public prototype_ `static void ApplyVertexColorsToAllLODs(IMeshPaintGeometryAdapter& GeometryInfo, UStaticMeshComponent* StaticMeshComponent);` — Applies the vertex colors found in LOD level 0 to all contained LOD levels in the StaticMeshComponent
- L110 _public prototype_ `static void ApplyVertexColorsToAllLODs(IMeshPaintGeometryAdapter& GeometryInfo, USkeletalMeshComponent* SkeletalMeshComponent);` — Applies the vertex colors found in LOD level 0 to all contained LOD levels in the SkeletalMeshComponent
- L113 _public prototype_ `static int32 GetNumberOfLODs(const UMeshComponent* MeshComponent);` — Returns the number of Mesh LODs for the given MeshComponent
- L116 _public prototype_ `static bool TryGetNumberOfLODs(const UMeshComponent* MeshComponent, int32& OutNumLODs);` — OutNumLODs is set to number of Mesh LODs for the given MeshComponent and returns true, or returns false of given mesh component has no valid LODs
- L119 _public prototype_ `static int32 GetNumberOfUVs(const UMeshComponent* MeshComponent, int32 LODIndex);` — Returns the number of Texture Coordinates for the given MeshComponent
- L122 _public prototype_ `static bool DoesMeshComponentContainPerLODColors(const UMeshComponent* MeshComponent);` — Checks whether or not the mesh components contains per lod colors (for all LODs)
- L125 _public prototype_ `static void GetInstanceColorDataInfo(const UStaticMeshComponent* StaticMeshComponent, int32 LODIndex, int32& OutTotalInstanceVertexColorBytes);` — Retrieves the number of bytes used to store the per-instance LOD vertex color data from the static mesh component
- L128 _public prototype_ `static bool ApplyPerVertexPaintAction(FPerVertexPaintActionArgs& InArgs, FPerVertexPaintAction Action);` — Given arguments for an action, and an action - retrieves influences vertices and applies Action to them
- L130 _public prototype_ `static bool GetPerVertexPaintInfluencedVertices(FPerVertexPaintActionArgs& InArgs, TSet<int32>& InfluencedVertices);`
- L133 _public prototype_ `static bool ApplyPerTrianglePaintAction(IMeshPaintGeometryAdapter* Adapter, const FVector& CameraPosition, const FVector& HitPosition, const UPaintBrushSettings* Settings, FPerTrianglePaintAction Action);` — Given the adapter, settings and view-information retrieves influences triangles and applies Action to them
- L136 _public prototype_ `static bool PaintVertex(const FVector& InVertexPosition, const FMeshPaintParameters& InParams, FColor& InOutVertexColor);` — Applies vertex painting to InOutvertexColor according to the given parameters
- L139 _public prototype_ `static void ApplyVertexColorPaint(const FMeshPaintParameters &InParams, const FLinearColor &OldColor, FLinearColor &NewColor, const float PaintAmount);` — Applies Vertex Color Painting according to the given parameters
- L142 _public prototype_ `static void ApplyVertexWeightPaint(const FMeshPaintParameters &InParams, const FLinearColor &OldColor, const float PaintAmount, FLinearColor &NewColor);` — Applies Vertex Blend Weight Painting according to the given parameters
- L145 _public prototype_ `static FLinearColor GenerateColorForTextureWeight(const int32 NumWeights, const int32 WeightIndex);` — Generate texture weight color for given number of weights and the to-paint index
- L148 _public prototype_ `static float ComputePaintMultiplier(float SquaredDistanceToVertex2D, float BrushStrength, float BrushInnerRadius, float BrushRadialFalloff, float BrushInnerDepth, float BrushDepthFallof, float VertexDepthToBrush);` — Computes the Paint power multiplier value
- L151 _public prototype_ `static bool IsPointInfluencedByBrush(const FVector& InPosition, const FMeshPaintParameters& InParams, float& OutSquaredDistanceToVertex2D, float& OutVertexDepthToBrush);` — Checks whether or not a point is influenced by the painting brush according to the given parameters
- L153 _public prototype_ `static bool IsPointInfluencedByBrush(const FVector2D& BrushSpacePosition, const float BrushRadiusSquared, float& OutInRangeValue);`
- L156 _public prototype_ `template<typename T> static void ApplyBrushToVertex(const FVector& VertexPosition, const FMatrix& InverseBrushMatrix, const float BrushRadius, const float BrushFalloffAmount, const float BrushStrength, const T& PaintValue, T& InOutValue);`
- L167 _public prototype_ `static bool RetrieveViewportPaintRays(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI, TArray<FPaintRay>& OutPaintRays);`
- L170 _protected prototype_ `static void ImportVertexColorsToStaticMesh(UStaticMesh* StaticMesh, const UVertexColorImportOptions* Options, UTexture2D* Texture);` — Imports vertex colors from a Texture to the specified Static Mesh according to user-set options
- L173 _protected prototype_ `static void ImportVertexColorsToStaticMeshComponent(UStaticMeshComponent* StaticMeshComponent, const UVertexColorImportOptions* Options, UTexture2D* Texture);` — Imports vertex colors from a Texture to the specified Static Mesh Component according to user-set options
- L176 _protected prototype_ `static void ImportVertexColorsToSkeletalMesh(USkeletalMesh* SkeletalMesh, const UVertexColorImportOptions* Options, UTexture2D* Texture);` — Imports vertex colors from a Texture to the specified Skeletal Mesh according to user-set options
- L179 _protected prototype_ `static FColor PickVertexColorFromTextureData(const uint8* MipData, const FVector2D& UVCoordinate, const UTexture2D* Texture, const FColor ColorMask);` — Helper function to retrieve vertex color from a UTexture given a UVCoordinate
- L183 _function_ `template<typename T> void MeshPaintHelpers::ApplyBrushToVertex(const FVector& VertexPosition, const FMatrix& InverseBrushMatrix, const float BrushRadius, const float BrushFalloffAmount, const float BrushStrength, const T& PaintValue, T& InOutValue)`

#### struct `MeshPaintHelpers::FPaintRay`  
`struct FPaintRay`  
_L159-165_
- L161 _public member_ `FVector CameraLocation;`
- L162 _public member_ `FVector RayStart;`
- L163 _public member_ `FVector RayDirection;`
- L164 _public member_ `UViewportInteractor* ViewportInteractor;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPAINT_API`
- L43 _delegate_ `DECLARE_DELEGATE_TwoParams(FPerVertexPaintAction, FPerVertexPaintActionArgs& , int32 );` — Delegates used to call per-vertex/triangle actions
- L43 _prototype_ `DECLARE_DELEGATE_TwoParams(FPerVertexPaintAction, FPerVertexPaintActionArgs& , int32 );` — Delegates used to call per-vertex/triangle actions
- L44 _delegate_ `DECLARE_DELEGATE_ThreeParams(FPerTrianglePaintAction, IMeshPaintGeometryAdapter* , int32 , const int32[3] );`
- L44 _prototype_ `DECLARE_DELEGATE_ThreeParams(FPerTrianglePaintAction, IMeshPaintGeometryAdapter* , int32 , const int32[3] );`

### `Source/Editor/MeshPaint/Public/MeshPaintModule.h` (Public)


#### class `IMeshPaintModule`  
`class IMeshPaintModule : public IModuleInterface`  
_L14-19_
- inherits: `IModuleInterface`
- desc: MeshPaint module interface
- L17 _public prototype_ `virtual void RegisterGeometryAdapterFactory(TSharedRef<IMeshPaintGeometryAdapterFactory> Factory) = 0;`
- L18 _public prototype_ `virtual void UnregisterGeometryAdapterFactory(TSharedRef<IMeshPaintGeometryAdapterFactory> Factory) = 0;`

### `Source/Editor/MeshPaint/Public/MeshPaintSettings.h` (Public)


#### enum `EMeshPaintColorViewMode`  
`enum class EMeshPaintColorViewMode : uint8`  
_L13-32_
- reflection: `UENUM()`
- desc: Mesh paint color view modes (somewhat maps to EVertexColorViewMode engine enum.)
- L16 _public enumerator_ `Normal UMETA(DisplayName = "Off")` — Normal view mode (vertex color visualization off)
- L19 _public enumerator_ `RGB UMETA(DisplayName = "RGB Channels")` — RGB only
- L22 _public enumerator_ `Alpha UMETA(DisplayName = "Alpha Channel")` — Alpha only
- L25 _public enumerator_ `Red UMETA(DisplayName = "Red Channel")` — Red only
- L28 _public enumerator_ `Green UMETA(DisplayName = "Green Channel")` — Green only
- L31 _public enumerator_ `Blue UMETA(DisplayName = "Blue Channel")` — Blue only

#### class `UPaintBrushSettings`  
`class UPaintBrushSettings : public UObject`  
_L35-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L40 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _public prototype_ `~UPaintBrushSettings();`
- L44 _public function_ `float GetBrushRadius() const`
- L45 _public prototype_ `void SetBrushRadius(float InRadius);`
- L47 _public function_ `float GetBrushStrength() const`
- L48 _public prototype_ `void SetBrushStrength(float InStrength);`
- L50 _public function_ `float GetBrushFalloff() const`
- L51 _public prototype_ `void SetBrushFalloff(float InFalloff);`
- L56 _protected member_ `float BrushRadius;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Radius", UIMin = "0.01", UIMax = "2048.0", ClampMin = "0.01", ClampMax = "250000.0"))` — Radius of the Brush used for Painting
- L60 _public member_ `float BrushRadiusMin;` — Min and Max brush radius retrieved from config
- L61 _public member_ `float BrushRadiusMax;`
- L65 _public member_ `float BrushStrength;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "1.0", ClampMin= "0.0", ClampMax = "1.0"))` — Strength of the brush (0.0 - 1.0)
- L69 _public member_ `float BrushFalloffAmount;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Falloff", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Amount of falloff to apply (0.0 - 1.0)
- L73 _public member_ `bool bEnableFlow;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Enable Brush Flow"))` — Enables "Flow" painting where paint is continually applied from the brush every tick
- L77 _public member_ `bool bOnlyFrontFacingTriangles;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Ignore Back-Facing"))` — Whether back-facing triangles should be ignored
- L81 _public member_ `EMeshPaintColorViewMode ColorViewMode;` — `UPROPERTY(EditAnywhere, Category = View)` — Color view mode used to display Vertex Colors

#### class `UMeshPaintSettings`  
`class UMeshPaintSettings : public UObject`  
_L85-95_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L93 _public member_ `float VertexPreviewSize;` — `UPROPERTY(config, EditAnywhere, Category=Visualization, Meta = (ClampMin = 0, UIMin = 0, UIMax = 10))` — Size of vertex points drawn when mesh painting is active.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPAINT_API`

### `Source/Editor/MeshPaint/Public/MeshPaintSkeletalMeshAdapter.h` (Public)


#### class `FMeshPaintGeometryAdapterForSkeletalMeshes`  
`class FMeshPaintGeometryAdapterForSkeletalMeshes : public FBaseMeshPaintGeometryAdapter`  
_L23-101_
- inherits: `FBaseMeshPaintGeometryAdapter`
- desc: FMeshPaintGeometryAdapterForSkeletalMeshes
- L26 _public prototype_ `static void InitializeAdapterGlobals();`
- L27 _public prototype_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector);`
- L28 _public prototype_ `static void CleanupGlobals();`
- L31 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) override;` — Start IMeshPaintGeometryAdapter Overrides
- L32 _public prototype_ `virtual ~FMeshPaintGeometryAdapterForSkeletalMeshes();`
- L33 _public prototype_ `virtual bool Initialize() override;`
- L34 _public prototype_ `virtual void OnAdded() override;`
- L35 _public prototype_ `virtual void OnRemoved() override;`
- L36 _public function_ `virtual bool IsValid() const override`
- L37 _public function_ `virtual bool SupportsTexturePaint() const override`
- L38 _public function_ `virtual bool SupportsVertexPaint() const override`
- L39 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const override;`
- L40 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) override;`
- L41 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture) const override;`
- L42 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L43 _public prototype_ `virtual void PreEdit() override;`
- L44 _public prototype_ `virtual void PostEdit() override;`
- L45 _public prototype_ `virtual void GetTextureCoordinate(int32 VertexIndex, int32 ChannelIndex, FVector2D& OutTextureCoordinate) const override;`
- L46 _public prototype_ `virtual void GetVertexColor(int32 VertexIndex, FColor& OutColor, bool bInstance = true) const override;`
- L47 _public prototype_ `virtual void SetVertexColor(int32 VertexIndex, FColor Color, bool bInstance = true) override;`
- L48 _public prototype_ `virtual FMatrix GetComponentToWorldMatrix() const override;`
- L52 _public prototype_ `virtual bool InitializeVertexData();` — Start FBaseMeshPaintGeometryAdapter Overrides
- L56 _protected prototype_ `void OnSkeletalMeshChanged();` — Callback for when the skeletal mesh on the component is changed
- L58 _protected prototype_ `void OnPostMeshCached(USkeletalMesh* SkeletalMesh);` — Callback for when skeletal mesh DDC data is rebuild
- L61 _protected member_ `FDelegateHandle SkeletalMeshChangedHandle;` — Delegate called when skeletal mesh is changed on the component
- L64 _protected member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — Skeletal mesh component represented by this adapter
- L66 _protected member_ `TObjectPtr<USkeletalMesh> ReferencedSkeletalMesh;` — Skeletal mesh currently set to the Skeletal Mesh Component
- L68 _protected member_ `FSkeletalMeshRenderData* MeshResource;` — Skeletal Mesh resource retrieved from the Skeletal Mesh
- L71 _protected member_ `FSkeletalMeshLODRenderData* LODData;` — LOD render data (at Mesh LOD Index) containing data to change
- L73 _protected member_ `FSkeletalMeshLODModel* LODModel;` — LOD model (source) data (at Mesh LOD Index) containing data to change
- L75 _protected member_ `int32 MeshLODIndex;` — LOD Index for which data has to be retrieved / altered
- L99 _protected typedef_ `typedef TMap<TObjectPtr<USkeletalMesh>, FSkeletalMeshReferencers> FMeshToComponentMap;`
- L100 _protected member_ `static FMeshToComponentMap MeshToComponentMap;`

#### struct `FMeshPaintGeometryAdapterForSkeletalMeshes::FSkeletalMeshReferencers`  
`struct FSkeletalMeshReferencers`  
_L78-97_
- desc: Helpers structure for keeping track of cached skeletal mesh data
- L80 _public function_ `FSkeletalMeshReferencers() : RestoreBodySetup(nullptr)`
- L95 _public member_ `TArray<FReferencersInfo> Referencers;`
- L96 _public member_ `TObjectPtr<UBodySetup> RestoreBodySetup;`

#### struct `FMeshPaintGeometryAdapterForSkeletalMeshes::FSkeletalMeshReferencers::FReferencersInfo`  
`struct FReferencersInfo`  
_L84-93_
- L86 _public function_ `FReferencersInfo(USkeletalMeshComponent* InSkeletalMeshComponent, ECollisionEnabled::Type InCachedCollisionType) : SkeletalMeshComponent(InSkeletalMeshComponent) , CachedCollisionType(InCachedCollisionType)`
- L91 _public member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;`
- L92 _public member_ `ECollisionEnabled::Type CachedCollisionType;`

#### class `FMeshPaintGeometryAdapterForSkeletalMeshesFactory`  
`class FMeshPaintGeometryAdapterForSkeletalMeshesFactory : public IMeshPaintGeometryAdapterFactory`  
_L106-113_
- inherits: `IMeshPaintGeometryAdapterFactory`
- L109 _public prototype_ `virtual TSharedPtr<IMeshPaintGeometryAdapter> Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) const override;`
- L110 _public function_ `virtual void InitializeAdapterGlobals() override`
- L111 _public function_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) override`
- L112 _public function_ `virtual void CleanupGlobals() override`

### `Source/Editor/MeshPaint/Public/MeshPaintSplineMeshAdapter.h` (Public)


#### class `FMeshPaintGeometryAdapterForSplineMeshes`  
`class FMeshPaintGeometryAdapterForSplineMeshes : public FMeshPaintGeometryAdapterForStaticMeshes`  
_L11-15_
- inherits: `FMeshPaintGeometryAdapterForStaticMeshes`
- L14 _public prototype_ `virtual bool InitializeVertexData() override;`

#### class `FMeshPaintGeometryAdapterForSplineMeshesFactory`  
`class FMeshPaintGeometryAdapterForSplineMeshesFactory : public FMeshPaintGeometryAdapterForStaticMeshesFactory`  
_L20-24_
- inherits: `FMeshPaintGeometryAdapterForStaticMeshesFactory`
- L23 _public prototype_ `virtual TSharedPtr<IMeshPaintGeometryAdapter> Construct(class UMeshComponent* InComponent, int32 MeshLODIndex) const override;`

### `Source/Editor/MeshPaint/Public/MeshPaintStaticMeshAdapter.h` (Public)


#### class `FMeshPaintGeometryAdapterForStaticMeshes`  
`class FMeshPaintGeometryAdapterForStaticMeshes : public FBaseMeshPaintGeometryAdapter`  
_L19-90_
- inherits: `FBaseMeshPaintGeometryAdapter`
- L22 _public prototype_ `static void InitializeAdapterGlobals();`
- L23 _public prototype_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector);`
- L24 _public prototype_ `static void CleanupGlobals();`
- L27 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) override;` — Start IMeshPaintGeometryAdapter Overrides
- L28 _public prototype_ `virtual ~FMeshPaintGeometryAdapterForStaticMeshes();`
- L29 _public prototype_ `virtual bool Initialize() override;`
- L30 _public prototype_ `virtual void OnAdded() override;`
- L31 _public prototype_ `virtual void OnRemoved() override;`
- L32 _public function_ `virtual bool IsValid() const override`
- L33 _public function_ `virtual bool SupportsTexturePaint() const override`
- L34 _public function_ `virtual bool SupportsVertexPaint() const override`
- L35 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const override;`
- L36 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) override;`
- L37 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture) const override;`
- L38 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L39 _public prototype_ `virtual void GetTextureCoordinate(int32 VertexIndex, int32 ChannelIndex, FVector2D& OutTextureCoordinate) const override;`
- L40 _public prototype_ `virtual void GetVertexColor(int32 VertexIndex, FColor& OutColor, bool bInstance = true) const override;`
- L41 _public prototype_ `virtual void SetVertexColor(int32 VertexIndex, FColor Color, bool bInstance = true) override;`
- L42 _public prototype_ `virtual FMatrix GetComponentToWorldMatrix() const override;`
- L43 _public prototype_ `virtual void PreEdit() override;`
- L44 _public prototype_ `virtual void PostEdit() override;`
- L48 _public prototype_ `virtual bool InitializeVertexData() override;` — Begin FMeshBasePaintGeometryAdapter
- L53 _protected prototype_ `void OnPostMeshBuild(UStaticMesh* StaticMesh);` — Callback for when the static mesh data is rebuilt
- L55 _protected prototype_ `void OnStaticMeshChanged(UStaticMeshComponent* StaticMeshComponent);` — Callback for when the static mesh on the component is changed
- L58 _protected member_ `TObjectPtr<UStaticMeshComponent> StaticMeshComponent;` — Static mesh component represented by this adapter
- L60 _protected member_ `TObjectPtr<UStaticMesh> ReferencedStaticMesh;` — Static mesh currently set to the Static Mesh Component
- L62 _protected member_ `FStaticMeshLODResources* LODModel;` — LOD model (at Mesh LOD Index) containing data to change
- L64 _protected member_ `int32 MeshLODIndex;` — LOD Index for which data has to be retrieved / altered
- L88 _protected typedef_ `typedef TMap<TObjectPtr<UStaticMesh>, FStaticMeshReferencers> FMeshToComponentMap;`
- L89 _protected member_ `static FMeshToComponentMap MeshToComponentMap;`

#### struct `FMeshPaintGeometryAdapterForStaticMeshes::FStaticMeshReferencers`  
`struct FStaticMeshReferencers`  
_L67-86_
- desc: Helpers structure for keeping track of cached static mesh data
- L69 _public function_ `FStaticMeshReferencers() : RestoreBodySetup(nullptr)`
- L84 _public member_ `TArray<FReferencersInfo> Referencers;`
- L85 _public member_ `TObjectPtr<UBodySetup> RestoreBodySetup;`

#### struct `FMeshPaintGeometryAdapterForStaticMeshes::FStaticMeshReferencers::FReferencersInfo`  
`struct FReferencersInfo`  
_L73-82_
- L75 _public function_ `FReferencersInfo(UStaticMeshComponent* InStaticMeshComponent, ECollisionEnabled::Type InCachedCollisionType) : StaticMeshComponent(InStaticMeshComponent) , CachedCollisionType(InCachedCollisionType)`
- L80 _public member_ `TObjectPtr<UStaticMeshComponent> StaticMeshComponent;`
- L81 _public member_ `ECollisionEnabled::Type CachedCollisionType;`

#### class `FMeshPaintGeometryAdapterForStaticMeshesFactory`  
`class FMeshPaintGeometryAdapterForStaticMeshesFactory : public IMeshPaintGeometryAdapterFactory`  
_L95-102_
- inherits: `IMeshPaintGeometryAdapterFactory`
- L98 _public prototype_ `virtual TSharedPtr<IMeshPaintGeometryAdapter> Construct(class UMeshComponent* InComponent, int32 InMeshLODIndex) const override;`
- L99 _public function_ `virtual void InitializeAdapterGlobals() override`
- L100 _public function_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) override`
- L101 _public function_ `virtual void CleanupGlobals() override`

### `Source/Editor/MeshPaint/Public/MeshPaintTypes.h` (Public)


#### enum `EMeshPaintAction`  
`enum class EMeshPaintAction : uint8`  
_L15-22_
- desc: Mesh painting action (paint, erase)
- L18 _public enumerator_ `Paint` — Paint (add color or increase blending weight)
- L21 _public enumerator_ `Erase` — Erase (remove color or decrease blending weight)

#### enum `EMeshPaintMode`  
`enum class EMeshPaintMode : uint8`  
_L26-33_
- reflection: `UENUM()`
- desc: Mesh paint mode
- L29 _public enumerator_ `PaintColors` — Painting colors directly
- L32 _public enumerator_ `PaintWeights` — Painting texture blend weights

#### enum `EMeshVertexPaintTarget`  
`enum class EMeshVertexPaintTarget : uint8`  
_L37-44_
- reflection: `UENUM()`
- desc: Vertex paint target
- L40 _public enumerator_ `ComponentInstance` — Paint the static mesh component instance in the level
- L43 _public enumerator_ `Mesh` — Paint the actual static mesh asset

#### class `FMeshPaintParameters`  
`class FMeshPaintParameters`  
_L47-71_
- desc: Mesh paint parameters
- L50 _public member_ `EMeshPaintMode PaintMode;`
- L51 _public member_ `EMeshPaintAction PaintAction;`
- L52 _public member_ `FVector BrushPosition;`
- L53 _public member_ `FVector BrushNormal;`
- L54 _public member_ `FLinearColor BrushColor;`
- L55 _public member_ `float SquaredBrushRadius;`
- L56 _public member_ `float BrushRadialFalloffRange;`
- L57 _public member_ `float InnerBrushRadius;`
- L58 _public member_ `float BrushDepth;`
- L59 _public member_ `float BrushDepthFalloffRange;`
- L60 _public member_ `float InnerBrushDepth;`
- L61 _public member_ `float BrushStrength;`
- L62 _public member_ `FMatrix BrushToWorldMatrix;`
- L63 _public member_ `FMatrix InverseBrushToWorldMatrix;`
- L64 _public member_ `bool bWriteRed;`
- L65 _public member_ `bool bWriteGreen;`
- L66 _public member_ `bool bWriteBlue;`
- L67 _public member_ `bool bWriteAlpha;`
- L68 _public member_ `int32 TotalWeightCount;`
- L69 _public member_ `int32 PaintWeightIndex;`
- L70 _public member_ `int32 UVChannel;`

#### struct `FTexturePaintTriangleInfo`  
`struct FTexturePaintTriangleInfo`  
_L74-79_
- desc: Structure used to hold per-triangle data for texture painting
- L76 _public member_ `FVector TriVertices[3];`
- L77 _public member_ `FVector2D TrianglePoints[3];`
- L78 _public member_ `FVector2D TriUVs[3];`

#### struct `FPaintableTexture`  
`struct FPaintableTexture`  
_L82-107_
- desc: Structure used to house and compare Texture and UV channel pairs
- L84 _public member_ `UTexture* Texture;`
- L85 _public member_ `int32 UVChannelIndex;`
- L87 _public function_ `FPaintableTexture() : Texture(nullptr) , UVChannelIndex(0)`
- L96 _public function_ `FPaintableTexture(T InTexture, uint32 InUVChannelIndex = 0) : Texture(InTexture) , UVChannelIndex(InUVChannelIndex)`
- L102 _public function_ `bool operator==(const FPaintableTexture& rhs) const` — Overloaded equality operator for use with TArrays Contains method.

#### struct `FPaintTexture2DData`  
`struct FPaintTexture2DData`  
_L109-155_
- L112 _public member_ `TObjectPtr<UTexture2D> PaintingTexture2D;` — The original texture that we're painting
- L113 _public member_ `bool bIsPaintingTexture2DModified;`
- L116 _public member_ `UTexture2D* PaintingTexture2DDuplicate;` — A copy of the original texture we're painting, used for restoration.
- L119 _public member_ `TObjectPtr<UTextureRenderTarget2D> PaintRenderTargetTexture;` — Render target texture for painting
- L122 _public member_ `TObjectPtr<UTextureRenderTarget2D> CloneRenderTargetTexture;` — Render target texture used as an input while painting that contains a clone of the original image
- L125 _public member_ `TArray< TObjectPtr<UMaterialInterface> > PaintingMaterials;` — List of materials we are painting on
- L128 _public function_ `FPaintTexture2DData() : PaintingTexture2D(nullptr), bIsPaintingTexture2DModified(false), PaintingTexture2DDuplicate(nullptr), PaintRenderTargetTexture(nullptr), CloneRenderTargetTexture(nullptr)` — Default ctor
- L136 _public function_ `FPaintTexture2DData(UTexture2D* InPaintingTexture2D, bool InbIsPaintingTexture2DModified = false) : PaintingTexture2D(InPaintingTexture2D), bIsPaintingTexture2DModified(InbIsPaintingTexture2DModified), PaintRenderTargetTexture(nullptr), CloneRenderTargetTexture(nullptr)`
- L144 _public function_ `void AddReferencedObjects(FReferenceCollector& Collector)` — Serializer

#### struct `FTextureTargetListInfo`  
`struct FTextureTargetListInfo`  
_L169-181_
- desc: Wrapper to expose texture targets to WPF code.
- L171 _public member_ `UTexture2D* TextureData;`
- L172 _public member_ `bool bIsSelected;`
- L173 _public member_ `uint32 UndoCount;`
- L174 _public member_ `uint32 UVChannelIndex;`
- L175 _public function_ `FTextureTargetListInfo(UTexture2D* InTextureData, int32 InUVChannelIndex, bool InbIsSelected = false) : TextureData(InTextureData) , bIsSelected(InbIsSelected) , UndoCount(0) , UVChannelIndex(InUVChannelIndex)`

#### struct `FMeshSelectedMaterialInfo`  
`struct FMeshSelectedMaterialInfo`  
_L186-195_
- desc: Wrapper to store which of a meshes materials is selected as well as the total number of materials.
- L188 _public member_ `int32 NumMaterials;`
- L189 _public member_ `int32 SelectedMaterialIndex;`
- L191 _public function_ `FMeshSelectedMaterialInfo(int32 InNumMaterials) : NumMaterials(InNumMaterials) , SelectedMaterialIndex(0)`

#### Free symbols / members of external scopes

- L157 _namespace_ `namespace MeshPaintDefs`
- L162 _variable_ `static const int32 MaxSupportedPhysicalWeights = 4;` (scope `MeshPaintDefs`) — Currently we never support more than five channels (R, G, B, A, OneMinusTotal)
- L163 _variable_ `static const int32 MaxSupportedWeights = MaxSupportedPhysicalWeights + 1;` (scope `MeshPaintDefs`)

### `Source/Editor/MeshPaint/Public/MeshPainterCommands.h` (Public)


#### class `FMeshPainterCommands`  
`class FMeshPainterCommands : public TCommands<FMeshPainterCommands>`  
_L14-35_
- inherits: `TCommands<FMeshPainterCommands>`
- desc: Base set of mesh painter commands
- L17 _public prototype_ `FMeshPainterCommands();`
- L22 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L25 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushRadius;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushRadius;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushStrength;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushStrength;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushFalloff;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushFalloff;`
- L34 _public member_ `TArray<TSharedPtr<FUICommandInfo>> Commands;`

### `Source/Editor/MeshPaint/Public/TMeshPaintOctree.h` (Public)


#### struct `FMeshPaintTriangle`  
`struct FMeshPaintTriangle`  
_L9-15_
- desc: Triangle for use in Octree for mesh paint optimization
- L11 _public member_ `uint32 Index;`
- L12 _public member_ `FVector Vertices[3];`
- L13 _public member_ `FVector Normal;`
- L14 _public member_ `FBoxCenterAndExtent BoxCenterAndExtent;`

#### struct `FMeshPaintTriangleOctreeSemantics`  
`struct FMeshPaintTriangleOctreeSemantics`  
_L18-58_
- desc: Semantics for the simple mesh paint octree
- L24 _public typedef_ `typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;`
- L34 _public function_ `FORCEINLINE static FBoxCenterAndExtent GetBoundingBox(const FMeshPaintTriangle& Element)` — Get the bounding box of the provided octree element. In this case, the box is merely the point specified by the element. @param	Element	Octree element to get the bounding box for @return	Bounding box of the provided octree element
- L48 _public function_ `FORCEINLINE static bool AreElementsEqual(const FMeshPaintTriangle& A, const FMeshPaintTriangle& B)` — Determine if two octree elements are equal @param	A	First octree element to check @param	B	Second octree element to check @return	true if both octree elements are equal, false if they are not
- L54 _public function_ `FORCEINLINE static void SetElementId(const FMeshPaintTriangle& Element, FOctreeElementId2 Id)` — Ignored for this implementation

#### enum `FMeshPaintTriangleOctreeSemantics::(anonymous)`  
`enum`  
_L20-20_

#### enum `FMeshPaintTriangleOctreeSemantics::(anonymous)`  
`enum`  
_L21-21_

#### enum `FMeshPaintTriangleOctreeSemantics::(anonymous)`  
`enum`  
_L22-22_

#### Free symbols / members of external scopes

- L20 _enumerator_ `enum { MaxElementsPerLeaf = 16 }; enum { MinInclusiveElementsPerNode = 7 }; enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; /** * Get the bounding box of the provided octree element. In this case` (scope `FMeshPaintTriangleOctreeSemantics::__anon6dc0fba70103`)
- L21 _enumerator_ `enum { MinInclusiveElementsPerNode = 7 }; enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; /** * Get the bounding box of the provided octree element. In this case` (scope `FMeshPaintTriangleOctreeSemantics::__anon6dc0fba70203`)
- L22 _enumerator_ `enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; /** * Get the bounding box of the provided octree element. In this case` (scope `FMeshPaintTriangleOctreeSemantics::__anon6dc0fba70303`)
- L59 _typedef_ `typedef TOctree2<FMeshPaintTriangle, FMeshPaintTriangleOctreeSemantics> FMeshPaintTriangleOctree;`

### `Source/Editor/MeshPaint/Public/TexturePaintHelpers.h` (Public)


#### class `FMeshPaintBatchedElementParameters`  
`class FMeshPaintBatchedElementParameters : public FBatchedElementParameters`  
_L16-29_
- inherits: `FBatchedElementParameters`
- desc: Batched element parameters for texture paint shaders used for paint blending and paint mask generation
- L20 _public function_ `virtual void BindShaders(FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override` — Binds vertex and pixel shaders for this element
- L28 _public member_ `MeshPaintRendering::FMeshPaintShaderParameters ShaderParams;` — Shader parameters

#### class `FMeshPaintDilateBatchedElementParameters`  
`class FMeshPaintDilateBatchedElementParameters : public FBatchedElementParameters`  
_L32-45_
- inherits: `FBatchedElementParameters`
- desc: Batched element parameters for texture paint shaders used for texture dilation
- L36 _public function_ `virtual void BindShaders(FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override` — Binds vertex and pixel shaders for this element
- L44 _public member_ `MeshPaintRendering::FMeshPaintDilateShaderParameters ShaderParams;` — Shader parameters

#### struct `FTexturePaintMeshSectionInfo`  
`struct FTexturePaintMeshSectionInfo`  
_L48-55_
- desc: Helper struct to store mesh section information in
- L51 _public member_ `int32 FirstIndex;` — First vertex index in section
- L54 _public member_ `int32 LastIndex;` — Last vertex index in section

#### class `TexturePaintHelpers`  
`class TexturePaintHelpers`  
_L61-96_
- desc: Helpers functions for texture painting functionality
- L65 _public prototype_ `static void CopyTextureToRenderTargetTexture(UTexture* SourceTexture, UTextureRenderTarget2D* RenderTargetTexture, ERHIFeatureLevel::Type FeatureLevel);` — Static: Copies a texture to a render target texture
- L68 _public prototype_ `static bool GenerateSeamMask(UMeshComponent* MeshComponent, int32 UVSet, UTextureRenderTarget2D* SeamRenderTexture, UTexture2D* Texture, UTextureRenderTarget2D* RenderTargetTexture );` — Will generate a mask texture, used for texture dilation, and store it in the passed in render target
- L71 _public prototype_ `static int32 GetMaxSupportedBytesPerPixelForPainting();` — Returns the maximum bytes per pixel that are supported for source textures when painting. This limitation is set by CreateTempUncompressedTexture.
- L74 _public prototype_ `static EPixelFormat GetTempUncompressedTexturePixelFormat();` — Returns the pixel format that CreateTempUncompressedTexture uses to create render target data for painting.
- L77 _public prototype_ `static UTexture2D* CreateTempUncompressedTexture(UTexture2D* SourceTexture);` — Static: Creates a temporary texture used to transfer data to a render target in memory
- L80 _public prototype_ `static void SetupInitialRenderTargetData(UTexture2D* InTextureSource, UTextureRenderTarget2D* InRenderTarget);` — Makes sure that the render target is ready to paint on
- L83 _public prototype_ `static void FindMaterialIndicesUsingTexture(const UTexture* Texture, const UMeshComponent* MeshComponent, TArray<int32>& OutIndices);` — Tries to find Materials using the given Texture and retrieve the corresponding material indices from the MEsh Compon
- L86 _public prototype_ `static void RetrieveMeshSectionsForTextures(const UMeshComponent* MeshComponent, int32 LODIndex, TArray<const UTexture*> Textures, TArray<FTexturePaintMeshSectionInfo>& OutSectionInfo);` — Retrieve LOD mesh sections from MeshComponent which use one of the given textures
- L89 _public prototype_ `static void RetrieveMeshSectionsForMaterialIndices(const UMeshComponent* MeshComponent, int32 LODIndex, const TArray<int32>& MaterialIndices, TArray<FTexturePaintMeshSectionInfo>& OutSectionInfo);` — Retrieve LOD mesh sections from MeshComponent which contain one of the Material Indices
- L92 _public prototype_ `static void RetrieveTexturesForComponent(const UMeshComponent* Component, IMeshPaintGeometryAdapter* Adapter, TArray<FPaintableTexture>& OutTextures);` — Retrieves all Paintable Textures from the given MeshComponent
- L95 _public prototype_ `static bool DoesMeshComponentUseTexture(UMeshComponent* MeshComponent, UTexture* Texture);` — Checks whether or not the given MeshComponent's materials use the specified texture

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHPAINT_API`
