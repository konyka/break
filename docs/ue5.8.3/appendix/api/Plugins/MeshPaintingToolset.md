# Plugins / MeshPaintingToolset

- module root: `Plugins/MeshPainting/Source/MeshPaintingToolset`
- headers: 19; symbols: 693
- symbol kinds: class=47, delegate=4, enum=9, enumerator=29, function=66, macro=13, member=180, namespace=6, prototype=322, struct=12, typedef=3, variable=2
- PrivateDependencyModuleNames: Chaos, Core, CoreUObject, Engine, GeometryCollectionEngine, ImageCore, InterchangeEngine, InterchangePipelines, MeshDescription, RHI, RenderCore, StaticMeshDescription, TypedElementFramework, TypedElementRuntime, UnrealEd
- PublicDependencyModuleNames: EditorInteractiveToolsFramework, GeometryCore, InteractiveToolsFramework

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Private/MeshPaintChannelSet.h` (Private)


#### struct `FMeshPaintChannelDesc`  
`struct FMeshPaintChannelDesc`  
_L11-45_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `FName ChannelName;` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — Name of the channel that will appear in the paint tool.
- L20 _public member_ `TObjectPtr<UTexture2D> PaintTexture;` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — Texture that channel paints to.
- L23 _public member_ `bool bWriteRed = false;` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — True if the channel writes to the red channel.
- L26 _public member_ `bool bWriteGreen = false;` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — True if the channel writes to the green channel.
- L29 _public member_ `bool bWriteBlue = false;` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — True if the channel writes to the blue channel.
- L32 _public member_ `bool bWriteAlpha = false;` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — True if the channel writes to the alpha channel.
- L35 _public member_ `FVector2D UVToWorldScale = FVector2D::One();` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — World Units per UV unit.
- L38 _public member_ `FVector2D WorldToUVBias = FVector2D::Zero();` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — UV offset to apply after scaling from world into UV space.
- L41 _public member_ `FVector2D ClampUVMin = FVector2D::Zero();` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — Minimum clamp to apply to UV after scale and bias.
- L44 _public member_ `FVector2D ClampUVMax = FVector2D::One();` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — Maximum clamp to apply to UV after scale and bias.

#### class `UMeshPaintChannelSet`  
`class UMeshPaintChannelSet : public UDataAsset`  
_L48-59_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UDataAsset`
- L55 _public member_ `TArray<FMeshPaintChannelDesc> Channels;` — `UPROPERTY(EditAnywhere, Category=MeshPaint)` — The array of Channel Descriptions.
- L58 _public prototype_ `FMeshPaintChannelDesc const* GetChannelDesc(FName InChannelName) const;` — Return a channel with the matching ChannelName. If none is found return nullptr.

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/BaseMeshPaintComponentAdapter.h` (Public)


#### class `FBaseMeshPaintComponentAdapter`  
`class FBaseMeshPaintComponentAdapter : public IMeshPaintComponentAdapter, public FGCObject, public TSharedFromThis<FBaseMeshPaintComponentAdapter>`  
_L16-47_
- inherits: `IMeshPaintComponentAdapter,FGCObject,TSharedFromThis<FBaseMeshPaintComponentAdapter>`
- desc: Base mesh paint geometry adapter, handles basic sphere intersection using a Octree
- L20 _public prototype_ `virtual bool Initialize() override;` — Start IMeshPaintGeometryAdapter Overrides
- L21 _public prototype_ `virtual const TArray<FVector>& GetMeshVertices() const override;`
- L22 _public prototype_ `virtual const TArray<uint32>& GetMeshIndices() const override;`
- L23 _public prototype_ `virtual void GetVertexPosition(int32 VertexIndex, FVector& OutVertex) const override;`
- L24 _public prototype_ `virtual TArray<uint32> SphereIntersectTriangles(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const override;`
- L25 _public prototype_ `virtual void GetInfluencedVertexIndices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TSet<int32> &InfluencedVertices) const override;`
- L26 _public prototype_ `virtual void GetInfluencedVertexData(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TArray<TPair<int32, FVector>>& OutData) const override;`
- L27 _public prototype_ `virtual TArray<FVector> SphereIntersectVertices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const override;`
- L28 _public prototype_ `virtual bool RayIntersectAdapter(UE::Geometry::FIndex3i& HitTriangle, FVector& HitPosition, const FVector Start, const FVector End) const override;`
- L31 _public function_ `virtual FString GetReferencerName() const override`
- L36 _public prototype_ `virtual bool InitializeVertexData() = 0;`
- L38 _protected prototype_ `bool BuildOctree();`
- L41 _protected member_ `TArray<FVector> MeshVertices;` — Index and Vertex data populated by derived classes in InitializeVertexData
- L42 _protected member_ `TArray<uint32> MeshIndices;`
- L44 _protected member_ `TUniquePtr<FMeshPaintTriangleOctree> MeshTriOctree;` — Octree used for reducing the cost of sphere intersecting with triangles / vertices
- L45 _protected member_ `FIndexMeshArrayAdapterd Adapter;`
- L46 _protected member_ `TUniquePtr<UE::Geometry::TMeshAABBTree3<const FIndexMeshArrayAdapterd>> AABBTree;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`
- L13 _typedef_ `typedef UE::Geometry::TIndexMeshArrayAdapter<uint32, double> FIndexMeshArrayAdapterd;`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/BaseMeshPaintingToolProperties.h` (Public)


#### class `UMeshPaintingToolProperties`  
`class UMeshPaintingToolProperties : public UBrushBaseProperties`  
_L9-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBrushBaseProperties`
- L16 _public member_ `FLinearColor PaintColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category = ColorPainting)` — Color used for applying color painting
- L20 _public member_ `FLinearColor EraseColor = FLinearColor::Transparent;` — `UPROPERTY(EditAnywhere, Category = ColorPainting)` — Color used for erasing color painting
- L24 _public member_ `bool bEnableFlow = false;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Enable Brush Flow"))` — Enables "Flow" painting where paint is continually applied from the brush every tick
- L28 _public member_ `bool bOnlyFrontFacingTriangles = false;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Ignore Back-Facing"))` — Whether back-facing triangles should be ignored

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/IMeshPaintComponentAdapter.h` (Public)


#### class `IMeshPaintComponentAdapter`  
`class IMeshPaintComponentAdapter`  
_L28-118_
- desc: Interface for a class to provide mesh painting support for a subclass of UMeshComponent
- L32 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 MeshLODIndex) = 0;` — Constructs the adapter for a specific LOD index using the mesh component
- L35 _public prototype_ `virtual ~IMeshPaintComponentAdapter() = default;` — D-tor
- L38 _public prototype_ `virtual bool Initialize() = 0;` — Returns whether or not initialization of necessary data was successful
- L41 _public prototype_ `virtual void OnAdded() = 0;` — Called when this adapter is created and added to its owner (used for setting up)
- L44 _public prototype_ `virtual void OnRemoved() = 0;` — Called when this adapter is removed from its owner and deleted (used for cleaning up)
- L47 _public prototype_ `virtual bool IsValid() const = 0;` — Returns whether or not this adapter is in a valid state
- L50 _public prototype_ `virtual bool SupportsTexturePaint() const = 0;` — Whether or not this adapter supports texture asset painting
- L53 _public prototype_ `virtual bool SupportsTextureColorPaint() const = 0;` — Whether or not this adapter supports texture color painting
- L56 _public prototype_ `virtual bool SupportsVertexPaint() const = 0;` — Whether or not this adapter supports vertex painting
- L59 _public prototype_ `virtual int32 GetNumUVChannels() const = 0;` — Returns the number of UV channels for the current LOD index in the Mesh.
- L62 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const = 0;` — Returns the result of tracing a line on the component represented by this adapter
- L65 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) = 0;` — Retrieves a list of textures which are suitable for painting
- L68 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture, FMaterialUpdateContext& MaterialUpdateContext) const = 0;` — Applies or removes an override texture to use while rendering the meshes materials
- L71 _public prototype_ `void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture) const;` — `UE_DEPRECATED(5.7, "Use the version that takes a FMaterialUpdateContext.")`
- L74 _public prototype_ `virtual const TArray<FVector>& GetMeshVertices() const = 0;` — Returns the vertices for the current LOD index in the Mesh
- L77 _public prototype_ `virtual const TArray<uint32>& GetMeshIndices() const = 0;` — Returns the indices for the current LOD index in the Mesh
- L80 _public prototype_ `virtual void GetVertexPosition(int32 VertexIndex, FVector& OutVertex) const = 0;` — Returns the Vertex Position at Vertex Index from the Mesh
- L83 _public prototype_ `virtual void SetVertexColor(int32 VertexIndex, FColor Color, bool bInstance = true) = 0;` — Sets the Vertex Color at Vertex Index to Color inside of the Mesh
- L86 _public prototype_ `virtual void GetTextureCoordinate(int32 VertexIndex, int32 ChannelIndex, FVector2D& OutTextureCoordinate) const = 0;` — Returns the Texture Coordinate at Vertex Index from the Mesh
- L89 _public prototype_ `virtual void GetVertexColor(int32 VertexIndex, FColor& OutColor, bool bInstance = true) const = 0;` — Returns the Vertex Color at Vertex Index from the Mesh
- L92 _public prototype_ `virtual FMatrix GetComponentToWorldMatrix() const = 0;` — Returns the Component to World matrix from the Mesh Component
- L95 _public prototype_ `virtual void PreEdit() = 0;` — Pre Edit to setup necessary data
- L98 _public prototype_ `virtual void PostEdit() = 0;` — Post Edit to clear up or update necessary data
- L101 _public prototype_ `static void DefaultQueryPaintableTextures(int32 MaterialIndex, const UMeshComponent* MeshComponent, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList);` — Default functionality for querying textures from a mesh component which are suitable for texture painting
- L104 _public prototype_ `virtual TArray<uint32> SphereIntersectTriangles(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const = 0;` — Returns the triangle indices which intersect with the given sphere
- L107 _public prototype_ `virtual void GetInfluencedVertexIndices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TSet<int32> &InfluencedVertices) const = 0;` — Retrieves the influenced vertex indices which intersect the given sphere
- L110 _public prototype_ `virtual void GetInfluencedVertexData(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TArray<TPair<int32, FVector>>& OutData) const = 0;` — Retrieves the influenced vertex indices and positions that intersect the given sphere
- L113 _public prototype_ `virtual TArray<FVector> SphereIntersectVertices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const = 0;` — Returns the vertex positions which intersect the given sphere
- L116 _public prototype_ `virtual bool RayIntersectAdapter(UE::Geometry::FIndex3i& HitTriangle, FVector& HitPosition, const FVector Start, const FVector End) const = 0;` — Returns the hit result which intersect with the given ray

#### class `UE::MeshPaintingToolset::FDefaultTextureOverride`  
`class FDefaultTextureOverride final`  
_L126-142_
- desc: Provide a default implementation for the texture override(s) needed when painting a mesh component This object will keep track of the overridden material resources and remove the override when they are no longer referred by an default texture override
- L129 _public prototype_ `void ApplyOrRemoveTextureOverride(UMeshComponent* InMeshComponent, UTexture* SourceTexture, UTexture* OverrideTexture, FMaterialUpdateContext& MaterialUpdateContext) const;`
- L131 _public prototype_ `void ApplyOrRemoveTextureOverride(UMeshComponent* InMeshComponent, UTexture* SourceTexture, UTexture* OverrideTexture) const;` — `UE_DEPRECATED(5.7, "Use the version that takes a FMaterialUpdateContext.")`
- L133 _public prototype_ `~FDefaultTextureOverride();`
- L135 _public prototype_ `FDefaultTextureOverride() = default;`
- L137 _public prototype_ `FDefaultTextureOverride(const FDefaultTextureOverride& InOther);`
- L138 _public prototype_ `FDefaultTextureOverride(FDefaultTextureOverride&& InOther);`
- L140 _public prototype_ `FDefaultTextureOverride& operator=(const FDefaultTextureOverride& InOther);`
- L141 _public prototype_ `FDefaultTextureOverride& operator=(FDefaultTextureOverride&& InOther);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L23 _namespace_ `namespace ERHIFeatureLevel`
- L120 _namespace_ `namespace UE`
- L120 _namespace_ `namespace MeshPaintingToolset` (scope `UE`)

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintAdapterFactory.h` (Public)


#### class `FMeshPaintComponentAdapterFactory`  
`class FMeshPaintComponentAdapterFactory`  
_L13-23_
- L16 _public member_ `static TArray<TSharedPtr<IMeshPaintComponentAdapterFactory>> FactoryList;`
- L19 _public prototype_ `static TSharedPtr<class IMeshPaintComponentAdapter> CreateAdapterForMesh(UMeshComponent* InComponent, int32 InPaintingMeshLODIndex);`
- L20 _public prototype_ `static void InitializeAdapterGlobals();`
- L21 _public prototype_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector);`
- L22 _public prototype_ `static void CleanupGlobals();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintComponentAdapterFactory.h` (Public)


#### class `IMeshPaintComponentAdapterFactory`  
`class IMeshPaintComponentAdapterFactory`  
_L14-22_
- desc: Factory for IMeshPaintGeometryAdapter
- L17 _public prototype_ `virtual TSharedPtr<IMeshPaintComponentAdapter> Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) const = 0;`
- L18 _public prototype_ `virtual void InitializeAdapterGlobals() = 0;`
- L19 _public prototype_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) = 0;`
- L20 _public prototype_ `virtual void CleanupGlobals() = 0;`
- L21 _public prototype_ `virtual ~IMeshPaintComponentAdapterFactory() = default;`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintGeometryCollectionAdapter.h` (Public)


#### class `FMeshPaintGeometryCollectionComponentAdapter`  
`class FMeshPaintGeometryCollectionComponentAdapter : public FBaseMeshPaintComponentAdapter`  
_L20-76_
- inherits: `FBaseMeshPaintComponentAdapter`
- desc: FMeshPaintGeometryAdapterForSkeletalMeshes
- L23 _public prototype_ `static void InitializeAdapterGlobals();`
- L24 _public prototype_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector);`
- L25 _public prototype_ `static void CleanupGlobals();`
- L27 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) override;` — Start IMeshPaintGeometryAdapter Overrides
- L28 _public prototype_ `virtual ~FMeshPaintGeometryCollectionComponentAdapter();`
- L29 _public prototype_ `virtual bool Initialize() override;`
- L30 _public prototype_ `virtual void OnAdded() override;`
- L31 _public prototype_ `virtual void OnRemoved() override;`
- L32 _public prototype_ `virtual bool IsValid() const override;`
- L33 _public function_ `virtual bool SupportsTexturePaint() const override`
- L34 _public function_ `virtual bool SupportsTextureColorPaint() const override`
- L35 _public function_ `virtual bool SupportsVertexPaint() const override`
- L36 _public prototype_ `virtual int32 GetNumUVChannels() const override;`
- L37 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const override;`
- L38 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) override;`
- L39 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture, FMaterialUpdateContext& MaterialUpdateContext) const override;`
- L40 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L41 _public prototype_ `virtual void PreEdit() override;`
- L42 _public prototype_ `virtual void PostEdit() override;`
- L43 _public prototype_ `virtual void GetTextureCoordinate(int32 VertexIndex, int32 ChannelIndex, FVector2D& OutTextureCoordinate) const override;`
- L44 _public prototype_ `virtual void GetVertexColor(int32 VertexIndex, FColor& OutColor, bool bInstance = true) const override;`
- L45 _public prototype_ `virtual void SetVertexColor(int32 VertexIndex, FColor Color, bool bInstance = true) override;`
- L46 _public prototype_ `virtual FMatrix GetComponentToWorldMatrix() const override;`
- L50 _public prototype_ `virtual bool InitializeVertexData();` — Start FBaseMeshPaintGeometryAdapter Overrides
- L55 _protected member_ `FDelegateHandle GeometryCollectionChangedHandle;` — Delegate called when geometry collection is changed on the component
- L58 _protected member_ `TWeakObjectPtr<UGeometryCollectionComponent> GeometryCollectionComponent;` — Geometry Collection component represented by this adapter
- L60 _protected member_ `bool bSavedShowBoneColors = false;`
- L63 _protected member_ `UE::MeshPaintingToolset::FDefaultTextureOverride TextureOverridesState;` — Texture override state
- L67 _protected prototype_ `UGeometryCollection* GetGeometryCollectionObject() const;` — Get the underlying UGeometryCollection from the component, as a non-const object Caller must have already validated that the component weak pointer is still valid (as this is called per-vertex)
- L69 _protected prototype_ `void OnGeometryCollectionChanged();`
- L73 _protected prototype_ `bool HasValidGeometryCollection() const;` — Like IsValid() but does not verify that the cached data matches

#### class `FMeshPaintGeometryCollectionComponentAdapterFactory`  
`class FMeshPaintGeometryCollectionComponentAdapterFactory : public IMeshPaintComponentAdapterFactory`  
_L81-88_
- inherits: `IMeshPaintComponentAdapterFactory`
- L84 _public prototype_ `virtual TSharedPtr<IMeshPaintComponentAdapter> Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) const override;`
- L85 _public function_ `virtual void InitializeAdapterGlobals() override`
- L86 _public function_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) override`
- L87 _public function_ `virtual void CleanupGlobals() override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintHelpers.h` (Public)


#### struct `FPerLODVertexColorData`  
`struct FPerLODVertexColorData`  
_L41-45_
- desc: struct used to store the color data copied from mesh instance to mesh instance
- L43 _public member_ `TArray< FColor > ColorsByIndex;`
- L44 _public member_ `TMap<FVector, FColor> ColorsByPosition;`

#### struct `FPerComponentVertexColorData`  
`struct FPerComponentVertexColorData`  
_L48-64_
- desc: struct used to store the color data copied from mesh component to mesh component
- L50 _public function_ `FPerComponentVertexColorData(const UStaticMesh* InStaticMesh, int32 InComponentIndex) : OriginalMesh(InStaticMesh) , ComponentIndex(InComponentIndex)`
- L57 _public member_ `TWeakObjectPtr<const UStaticMesh> OriginalMesh;` — We match up components by the mesh they use
- L60 _public member_ `int32 ComponentIndex;` — We also match by component index
- L63 _public member_ `TArray<FPerLODVertexColorData> PerLODVertexColorData;` — Vertex colors by LOD

#### struct `FInstanceTexturePaintSettings`  
`struct FInstanceTexturePaintSettings`  
_L67-86_
- desc: Struct to hold MeshPaint settings on a per mesh basis
- L69 _public member_ `UTexture2D* SelectedTexture;`
- L70 _public member_ `int32 SelectedUVChannel;`
- L72 _public function_ `FInstanceTexturePaintSettings() : SelectedTexture(nullptr) , SelectedUVChannel(0)`
- L76 _public function_ `FInstanceTexturePaintSettings(UTexture2D* InSelectedTexture, int32 InSelectedUVSet) : SelectedTexture(InSelectedTexture) , SelectedUVChannel(InSelectedUVSet)`
- L81 _public function_ `void operator=(const FInstanceTexturePaintSettings& SrcSettings)`

#### class `FMeshPaintToolSettingHelpers`  
`class FMeshPaintToolSettingHelpers`  
_L89-99_
- desc: Struct for some static helper functions to store tool properties.
- L93 _public prototype_ `static void SavePropertiesForClassHeirachy(UInteractiveTool* InTool, UInteractiveToolPropertySet* InProperties);` — Store properties in a property set for later restore in a session. This saves settings per base class so that different class hierachies can share their base class data.
- L95 _public prototype_ `static void RestorePropertiesForClassHeirachy(UInteractiveTool* InTool, UInteractiveToolPropertySet* InProperties);` — Restore properties in a property that were saved in this session. This restores settings per base class so that different class hierachies can share their base class data.
- L98 _private prototype_ `static TCHAR const* GetCacheIdentifier();` — Get unique string used to identify property set in cache.

#### enum `ETexturePaintWeightTypes`  
`enum class ETexturePaintWeightTypes : uint8`  
_L102-115_
- reflection: `UENUM()`
- L105 _public enumerator_ `AlphaLerp = 2 UMETA(DisplayName = "Alpha (Two Textures)")` — Lerp Between Two Textures using Alpha Value
- L108 _public enumerator_ `RGB = 3 UMETA(DisplayName = "RGB (Three Textures)")` — Weighting Three Textures according to Channels
- L111 _public enumerator_ `ARGB = 4 UMETA(DisplayName = "ARGB (Four Textures)")` — Weighting Four Textures according to Channels
- L114 _public enumerator_ `OneMinusARGB = 5 UMETA(DisplayName = "ARGB - 1 (Five Textures)")` — Weighting Five Textures according to Channels

#### enum `ETexturePaintWeightIndex`  
`enum class ETexturePaintWeightIndex : uint8`  
_L118-125_
- reflection: `UENUM()`
- L120 _public enumerator_ `TextureOne = 0`
- L121 _public enumerator_ `TextureTwo`
- L122 _public enumerator_ `TextureThree`
- L123 _public enumerator_ `TextureFour`
- L124 _public enumerator_ `TextureFive`

#### struct `FPerVertexPaintActionArgs`  
`struct FPerVertexPaintActionArgs`  
_L128-135_
- desc: Parameters for paint actions, stored together for convenience
- L130 _public member_ `IMeshPaintComponentAdapter* Adapter;`
- L131 _public member_ `UMeshVertexPaintingToolProperties* BrushProperties;`
- L132 _public member_ `FVector CameraPosition;`
- L133 _public member_ `FHitResult HitResult;`
- L134 _public member_ `EMeshPaintModeAction Action;`

#### class `UMeshPaintingSubsystem`  
`class UMeshPaintingSubsystem : public UEngineSubsystem`  
_L142-318_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- L147 _public prototype_ `UMeshPaintingSubsystem();`
- L149 _public prototype_ `bool HasPaintableMesh(UActorComponent* Component);`
- L151 _public prototype_ `void RemoveInstanceVertexColors(UObject* Obj);` — Removes vertex colors associated with the object
- L154 _public prototype_ `void RemoveComponentInstanceVertexColors(UStaticMeshComponent* StaticMeshComponent);` — Removes vertex colors associated with the mesh component
- L157 _public prototype_ `UTexture* CreateMeshPaintTexture(UObject* Outer, uint32 TextureSize);` — Creates and returns a mesh paint texture that isn't attached to a mesh component
- L159 _public prototype_ `void CreateComponentMeshPaintTexture(UStaticMeshComponent* StaticMeshComponent);` — Creates mesh paint texture associated with the mesh component
- L160 _public prototype_ `void CreateComponentMeshPaintTexture(UStaticMeshComponent* StaticMeshComponent, FImageView const& InImage);`
- L163 _public prototype_ `void RemoveComponentMeshPaintTexture(UStaticMeshComponent* StaticMeshComponent);` — Removes mesh paint texture associated with the mesh component
- L166 _public prototype_ `bool PropagateColorsToRawMesh(UStaticMesh* StaticMesh, int32 LODIndex, FStaticMeshComponentLODInfo& ComponentLODInfo);` — Propagates per-instance vertex colors to the underlying Mesh for the given LOD Index
- L169 _public prototype_ `uint32 GetVertexColorBufferSize(UMeshComponent* MeshComponent, int32 LODIndex, bool bInstance);` — Retrieves the Vertex Color buffer size for the given LOD level in the Mesh
- L172 _public prototype_ `uint32 GetMeshPaintTextureResourceSize(UMeshComponent* MeshComponent);` — Retrieves the resource size for the mesh paint texture on the component
- L175 _public prototype_ `TArray<FVector> GetVerticesForLOD(const UStaticMesh* StaticMesh, int32 LODIndex);` — Retrieves the vertex positions from the given LOD level in the Mesh
- L178 _public prototype_ `TArray<FColor> GetColorDataForLOD(const UStaticMesh* StaticMesh, int32 LODIndex);` — Retrieves the vertex colors from the given LOD level in the Mesh
- L181 _public prototype_ `TArray<FColor> GetInstanceColorDataForLOD(const UStaticMeshComponent* MeshComponent, int32 LODIndex);` — Retrieves the per-instance vertex colors from the given LOD level in the StaticMeshComponent
- L184 _public prototype_ `void SetInstanceColorDataForLOD(UStaticMeshComponent* MeshComponent, int32 LODIndex, const TArray<FColor>& Colors);` — Sets the specific (LOD Index) per-instance vertex colors for the given StaticMeshComponent to the supplied Color array
- L187 _public prototype_ `void SetInstanceColorDataForLOD(UStaticMeshComponent* MeshComponent, int32 LODIndex, const FColor FillColor, const FColor MaskColor);` — Sets the specific (LOD Index) per-instance vertex colors for the given StaticMeshComponent to a single Color value
- L190 _public prototype_ `void FillStaticMeshVertexColors(UStaticMeshComponent* MeshComponent, int32 LODIndex, const FColor FillColor, const FColor MaskColor);` — Fills all vertex colors for all LODs found in the given mesh component with Fill Color
- L191 _public prototype_ `void FillSkeletalMeshVertexColors(USkeletalMeshComponent* MeshComponent, int32 LODIndex, const FColor FillColor, const FColor MaskColor);`
- L194 _public prototype_ `void SetColorDataForLOD(USkeletalMesh* SkeletalMesh, int32 LODIndex, const FColor FillColor, const FColor MaskColor);` — Sets all vertex colors for a specific LOD level in the SkeletalMesh to FillColor
- L196 _public prototype_ `void ApplyFillWithMask(FColor& InOutColor, const FColor& MaskColor, const FColor& FillColor);`
- L199 _public prototype_ `void ForceRenderMeshLOD(UMeshComponent* Component, int32 LODIndex);` — Forces the component to render LOD level at LODIndex instead of the view-based LOD level ( X = 0 means do not force the LOD, X > 0 means force the lod to X - 1 )
- L202 _public prototype_ `void ClearMeshTextureOverrides(const IMeshPaintComponentAdapter& GeometryInfo, UMeshComponent* InMeshComponent);` — `UE_DEPRECATED(5.7, "No longer supported. Will be a no-op.")`
- L205 _public prototype_ `void ApplyVertexColorsToAllLODs(IMeshPaintComponentAdapter& GeometryInfo, UMeshComponent* InMeshComponent);` — Applies vertex color painting found on LOD 0 to all lower LODs.
- L208 _public prototype_ `void ApplyVertexColorsToAllLODs(IMeshPaintComponentAdapter& GeometryInfo, UStaticMeshComponent* StaticMeshComponent);` — Applies the vertex colors found in LOD level 0 to all contained LOD levels in the StaticMeshComponent
- L211 _public prototype_ `void ApplyVertexColorsToAllLODs(IMeshPaintComponentAdapter& GeometryInfo, USkeletalMeshComponent* SkeletalMeshComponent);` — Applies the vertex colors found in LOD level 0 to all contained LOD levels in the SkeletalMeshComponent
- L214 _public prototype_ `int32 GetNumberOfLODs(const UMeshComponent* MeshComponent);` — Returns the number of Mesh LODs for the given MeshComponent
- L217 _public prototype_ `bool TryGetNumberOfLODs(const UMeshComponent* MeshComponent, int32& OutNumLODs);` — OutNumLODs is set to number of Mesh LODs for the given MeshComponent and returns true, or returns false of given mesh component has no valid LODs
- L220 _public prototype_ `int32 GetNumberOfUVs(const UMeshComponent* MeshComponent, int32 LODIndex) const;` — Returns the number of Texture Coordinates for the given MeshComponent
- L223 _public prototype_ `bool DoesMeshComponentContainPerLODColors(const UMeshComponent* MeshComponent);` — Checks whether or not the mesh components contains per lod colors (for all LODs)
- L226 _public prototype_ `void GetInstanceColorDataInfo(const UStaticMeshComponent* StaticMeshComponent, int32 LODIndex, int32& OutTotalInstanceVertexColorBytes);` — Retrieves the number of bytes used to store the per-instance LOD vertex color data from the mesh component
- L229 _public prototype_ `bool ApplyPerVertexPaintAction(FPerVertexPaintActionArgs& InArgs, FPerVertexPaintAction Action);` — Given arguments for an action, and an action - retrieves influences vertices and applies Action to them
- L231 _public prototype_ `bool GetPerVertexPaintInfluencedVertices(FPerVertexPaintActionArgs& InArgs, TSet<int32>& InfluencedVertices);`
- L234 _public prototype_ `bool ApplyPerTrianglePaintAction(IMeshPaintComponentAdapter* Adapter, const FVector& CameraPosition, const FVector& HitPosition, const UBrushBaseProperties* Settings, FPerTrianglePaintAction Action, bool bOnlyFrontFacingTriangles);` — Given the adapter, settings and view-information retrieves influences triangles and applies Action to them
- L237 _public prototype_ `bool PaintVertex(const FVector& InVertexPosition, const FMeshPaintParameters& InParams, FColor& InOutVertexColor);` — Applies vertex painting to InOutvertexColor according to the given parameters
- L240 _public prototype_ `void ApplyVertexColorPaint(const FMeshPaintParameters &InParams, const FLinearColor &OldColor, FLinearColor &NewColor, const float PaintAmount);` — Applies Vertex Color Painting according to the given parameters
- L243 _public prototype_ `void ApplyVertexWeightPaint(const FMeshPaintParameters &InParams, const FLinearColor &OldColor, FLinearColor &NewColor, const float PaintAmount);` — Applies Vertex Blend Weight Painting according to the given parameters
- L246 _public prototype_ `FLinearColor GenerateColorForTextureWeight(const int32 NumWeights, const int32 WeightIndex);` — Generate texture weight color for given number of weights and the to-paint index
- L249 _public prototype_ `float ComputePaintMultiplier(float SquaredDistanceToVertex2D, float BrushStrength, float BrushInnerRadius, float BrushRadialFalloff, float BrushInnerDepth, float BrushDepthFallof, float VertexDepthToBrush);` — Computes the Paint power multiplier value
- L252 _public prototype_ `bool IsPointInfluencedByBrush(const FVector& InPosition, const FMeshPaintParameters& InParams, float& OutSquaredDistanceToVertex2D, float& OutVertexDepthToBrush);` — Checks whether or not a point is influenced by the painting brush according to the given parameters
- L254 _public prototype_ `bool IsPointInfluencedByBrush(const FVector2D& BrushSpacePosition, const float BrushRadiusSquared, float& OutInRangeValue);`
- L257 _public prototype_ `template<typename T> void ApplyBrushToVertex(const FVector& VertexPosition, const FMatrix& InverseBrushMatrix, const float BrushRadius, const float BrushFalloffAmount, const float BrushStrength, const T& PaintValue, T& InOutValue);`
- L260 _public prototype_ `FColor PickVertexColorFromTextureData(const uint8* MipData, const FVector2D& UVCoordinate, const UTexture2D* Texture, const FColor ColorMask);` — Helper function to retrieve vertex color from a UTexture given a UVCoordinate
- L263 _public prototype_ `TSharedPtr<IMeshPaintComponentAdapter> GetAdapterForComponent(const UMeshComponent* InComponent) const;` — Map of geometry adapters for each selected mesh component
- L264 _public prototype_ `void AddToComponentToAdapterMap(const UMeshComponent* InComponent, const TSharedPtr<IMeshPaintComponentAdapter> InAdapter);`
- L266 _public prototype_ `TArray<UMeshComponent*> GetSelectedMeshComponents() const;`
- L267 _public prototype_ `void AddSelectedMeshComponents(const TArray<UMeshComponent*>& InComponents);`
- L268 _public prototype_ `bool FindHitResult(const FRay Ray, FHitResult& BestTraceResult);`
- L269 _public prototype_ `void ClearSelectedMeshComponents();`
- L270 _public prototype_ `TArray<UMeshComponent*> GetPaintableMeshComponents() const;`
- L271 _public prototype_ `void AddPaintableMeshComponent(UMeshComponent* InComponent);`
- L272 _public prototype_ `void ClearPaintableMeshComponents();`
- L273 _public prototype_ `TArray<FPerComponentVertexColorData> GetCopiedColorsByComponent() const;`
- L274 _public prototype_ `void SetCopiedColorsByComponent(TArray<FPerComponentVertexColorData>& InCopiedColors);`
- L275 _public prototype_ `void CacheSelectionData(const int32 PaintLODIndex, const int32 UVChannel);`
- L276 _public prototype_ `FIntPoint GetMinMaxUVChannelsToPaint() const;`
- L277 _public prototype_ `void ResetState();`
- L278 _public prototype_ `void Refresh();`
- L279 _public function_ `bool SelectionContainsPerLODColors() const`
- L280 _public function_ `void ClearSelectionLODColors()`
- L281 _public prototype_ `void UpdatePaintSupportState();`
- L282 _public function_ `bool GetSelectionSupportsVertexPaint() const`
- L283 _public function_ `bool GetSelectionSupportsTextureColorPaint() const`
- L284 _public function_ `bool GetSelectionSupportsTextureAssetPaint() const`
- L286 _public prototype_ `FImage const& GetCopiedTexture() const;`
- L287 _public prototype_ `void SetCopiedTexture(UTexture* InTexture);`
- L290 _public member_ `bool bNeedsRecache;`
- L293 _public member_ `TObjectPtr<UMeshComponent> LastPaintedComponent;` — `UPROPERTY(Transient)`
- L296 _private prototype_ `void CleanUp();`
- L300 _private member_ `TMap<FString, TSharedPtr<IMeshPaintComponentAdapter>> ComponentToAdapterMap;` — Map of geometry adapters for each selected mesh component
- L303 _private member_ `TArray<TWeakObjectPtr<UMeshComponent>> SelectedMeshComponents;` — Currently selected mesh components as provided by the mode class
- L306 _private member_ `TArray<TWeakObjectPtr<UMeshComponent>> PaintableComponents;` — Mesh components within the current selection which are eligible for painting
- L309 _private member_ `TArray<FPerComponentVertexColorData> CopiedColorsByComponent;` — Contains copied vertex color data
- L310 _private member_ `bool bSelectionContainsPerLODColors;`
- L313 _private member_ `FImage CopiedTextureData;` — Contains copied texture data
- L315 _private member_ `bool bSelectionSupportsVertexPaint;`
- L316 _private member_ `bool bSelectionSupportsTextureColorPaint;`
- L317 _private member_ `bool bSelectionSupportsTextureAssetPaint;`
- L321 _function_ `template<typename T> void UMeshPaintingSubsystem::ApplyBrushToVertex(const FVector& VertexPosition, const FMatrix& InverseBrushMatrix, const float BrushRadius, const float BrushFalloffAmount, const float BrushStrength, const T& PaintValue, T& InOutValue)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`
- L138 _delegate_ `DECLARE_DELEGATE_TwoParams(FPerVertexPaintAction, FPerVertexPaintActionArgs& , int32 );` — Delegates used to call per-vertex/triangle actions
- L138 _prototype_ `DECLARE_DELEGATE_TwoParams(FPerVertexPaintAction, FPerVertexPaintActionArgs& , int32 );` — Delegates used to call per-vertex/triangle actions
- L139 _delegate_ `DECLARE_DELEGATE_ThreeParams(FPerTrianglePaintAction, IMeshPaintComponentAdapter* , int32 , const int32[3] );`
- L139 _prototype_ `DECLARE_DELEGATE_ThreeParams(FPerTrianglePaintAction, IMeshPaintComponentAdapter* , int32 , const int32[3] );`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintInteractions.h` (Public)


#### class `UMeshPaintSelectionInterface`  
`class UMeshPaintSelectionInterface : public UInterface`  
_L20-23_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMeshPaintSelectionInterface`  
`class IMeshPaintSelectionInterface`  
_L25-31_
- L29 _public prototype_ `virtual bool IsMeshAdapterSupported(TSharedPtr<IMeshPaintComponentAdapter> MeshAdapter) const PURE_VIRTUAL(IMeshPaintSelectionInterface::IsMeshAdapterSupported, return false;);`
- L30 _public prototype_ `virtual bool AllowsMultiselect() const PURE_VIRTUAL(IMeshPaintSelectionInterface::AllowsMultiselect, return false;);`

#### class `UMeshPaintSelectionMechanic`  
`class UMeshPaintSelectionMechanic : public UInteractionMechanic`  
_L35-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractionMechanic`
- L40 _public prototype_ `FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos, bool bIsFallbackClick = false);`
- L41 _public prototype_ `void OnClicked(const FInputDeviceRay& ClickPos);`
- L42 _public function_ `void SetAddToSelectionSet(const bool bInNewSelectionType)`
- L47 _protected prototype_ `bool FindClickedComponentsAndCacheAdapters(const FInputDeviceRay& ClickPos);`
- L51 _protected member_ `TArray<TObjectPtr<UMeshComponent>> CachedClickedComponents;` — `UPROPERTY(Transient)`
- L53 _protected member_ `TArray<TObjectPtr<AActor>> CachedClickedActors;` — `UPROPERTY(Transient)`
- L54 _protected member_ `bool bAddToSelectionSet;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintSkeletalMeshAdapter.h` (Public)


#### class `FMeshPaintSkeletalMeshComponentAdapter`  
`class FMeshPaintSkeletalMeshComponentAdapter : public FBaseMeshPaintComponentAdapter`  
_L22-79_
- inherits: `FBaseMeshPaintComponentAdapter`
- desc: FMeshPaintGeometryAdapterForSkeletalMeshes
- L25 _public prototype_ `static void InitializeAdapterGlobals();`
- L26 _public prototype_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector);`
- L27 _public prototype_ `static void CleanupGlobals();`
- L29 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) override;` — Start IMeshPaintGeometryAdapter Overrides
- L30 _public prototype_ `virtual ~FMeshPaintSkeletalMeshComponentAdapter();`
- L31 _public prototype_ `virtual bool Initialize() override;`
- L32 _public prototype_ `virtual void OnAdded() override;`
- L33 _public prototype_ `virtual void OnRemoved() override;`
- L34 _public function_ `virtual bool IsValid() const override`
- L35 _public function_ `virtual bool SupportsTexturePaint() const override`
- L36 _public function_ `virtual bool SupportsTextureColorPaint() const override`
- L37 _public function_ `virtual bool SupportsVertexPaint() const override`
- L38 _public prototype_ `virtual int32 GetNumUVChannels() const override;`
- L39 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const override;`
- L40 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) override;`
- L41 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture, FMaterialUpdateContext& MaterialUpdateContext) const override;`
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
- L64 _protected member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — Skeletal mesh component represented by this adapter
- L66 _protected member_ `TObjectPtr<USkeletalMesh> ReferencedSkeletalMesh;` — Skeletal mesh currently set to the Skeletal Mesh Component
- L68 _protected member_ `FSkeletalMeshRenderData* MeshResource;` — Skeletal Mesh resource retrieved from the Skeletal Mesh
- L71 _protected member_ `FSkeletalMeshLODRenderData* LODData;` — LOD render data (at Mesh LOD Index) containing data to change
- L73 _protected member_ `FSkeletalMeshLODModel* LODModel;` — LOD model (source) data (at Mesh LOD Index) containing data to change
- L75 _protected member_ `int32 MeshLODIndex;` — LOD Index for which data has to be retrieved / altered
- L78 _protected member_ `UE::MeshPaintingToolset::FDefaultTextureOverride TextureOverridesState;` — Texture override state

#### class `FMeshPaintSkeletalMeshComponentAdapterFactory`  
`class FMeshPaintSkeletalMeshComponentAdapterFactory : public IMeshPaintComponentAdapterFactory`  
_L84-91_
- inherits: `IMeshPaintComponentAdapterFactory`
- L87 _public prototype_ `virtual TSharedPtr<IMeshPaintComponentAdapter> Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) const override;`
- L88 _public function_ `virtual void InitializeAdapterGlobals() override`
- L89 _public function_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) override`
- L90 _public function_ `virtual void CleanupGlobals() override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintSplineMeshAdapter.h` (Public)


#### class `FMeshPaintSplineMeshComponentAdapter`  
`class FMeshPaintSplineMeshComponentAdapter : public FMeshPaintStaticMeshComponentAdapter`  
_L12-16_
- inherits: `FMeshPaintStaticMeshComponentAdapter`
- L15 _public prototype_ `virtual bool InitializeVertexData() override;`

#### class `FMeshPaintSplineMeshComponentAdapterFactory`  
`class FMeshPaintSplineMeshComponentAdapterFactory : public FMeshPaintStaticMeshComponentAdapterFactory`  
_L21-25_
- inherits: `FMeshPaintStaticMeshComponentAdapterFactory`
- L24 _public prototype_ `virtual TSharedPtr<IMeshPaintComponentAdapter> Construct(class UMeshComponent* InComponent, int32 MeshLODIndex) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintStaticMeshAdapter.h` (Public)


#### class `FMeshPaintStaticMeshComponentAdapter`  
`class FMeshPaintStaticMeshComponentAdapter : public FBaseMeshPaintComponentAdapter`  
_L19-69_
- inherits: `FBaseMeshPaintComponentAdapter`
- L22 _public prototype_ `static void InitializeAdapterGlobals();`
- L23 _public prototype_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector);`
- L24 _public prototype_ `static void CleanupGlobals();`
- L26 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) override;` — Start IMeshPaintGeometryAdapter Overrides
- L27 _public prototype_ `virtual ~FMeshPaintStaticMeshComponentAdapter();`
- L28 _public prototype_ `virtual bool Initialize() override;`
- L29 _public function_ `virtual void OnAdded() override`
- L30 _public function_ `virtual void OnRemoved() override`
- L31 _public function_ `virtual bool IsValid() const override`
- L32 _public function_ `virtual bool SupportsTexturePaint() const override`
- L33 _public function_ `virtual bool SupportsTextureColorPaint() const override`
- L34 _public prototype_ `virtual int32 GetNumUVChannels() const override;`
- L35 _public function_ `virtual bool SupportsVertexPaint() const override`
- L36 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const override;`
- L37 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) override;`
- L38 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture, FMaterialUpdateContext& MaterialUpdateContext) const override;`
- L39 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L40 _public prototype_ `virtual void GetTextureCoordinate(int32 VertexIndex, int32 ChannelIndex, FVector2D& OutTextureCoordinate) const override;`
- L41 _public prototype_ `virtual void GetVertexColor(int32 VertexIndex, FColor& OutColor, bool bInstance = true) const override;`
- L42 _public prototype_ `virtual void SetVertexColor(int32 VertexIndex, FColor Color, bool bInstance = true) override;`
- L43 _public prototype_ `virtual FMatrix GetComponentToWorldMatrix() const override;`
- L44 _public prototype_ `virtual void PreEdit() override;`
- L45 _public prototype_ `virtual void PostEdit() override;`
- L49 _public prototype_ `virtual bool InitializeVertexData() override;` — Begin FMeshBasePaintGeometryAdapter
- L54 _protected prototype_ `void OnPostMeshBuild(UStaticMesh* StaticMesh);` — Callback for when the static mesh data is rebuilt
- L56 _protected prototype_ `void OnStaticMeshChanged(UStaticMeshComponent* StaticMeshComponent);` — Callback for when the static mesh on the component is changed
- L59 _protected member_ `TWeakObjectPtr<UStaticMeshComponent> StaticMeshComponent;` — Static mesh component represented by this adapter
- L61 _protected member_ `TObjectPtr<UStaticMesh> ReferencedStaticMesh;` — Static mesh currently set to the Static Mesh Component
- L63 _protected member_ `FStaticMeshLODResources* LODModel;` — LOD model (at Mesh LOD Index) containing data to change
- L65 _protected member_ `int32 MeshLODIndex;` — LOD Index for which data has to be retrieved / altered
- L68 _protected member_ `UE::MeshPaintingToolset::FDefaultTextureOverride TextureOverridesState;` — Texture override state

#### class `FMeshPaintStaticMeshComponentAdapterFactory`  
`class FMeshPaintStaticMeshComponentAdapterFactory : public IMeshPaintComponentAdapterFactory`  
_L74-81_
- inherits: `IMeshPaintComponentAdapterFactory`
- L77 _public prototype_ `virtual TSharedPtr<IMeshPaintComponentAdapter> Construct(class UMeshComponent* InComponent, int32 InMeshLODIndex) const override;`
- L78 _public function_ `virtual void InitializeAdapterGlobals() override`
- L79 _public function_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) override`
- L80 _public function_ `virtual void CleanupGlobals() override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintingToolset.h` (Public)
_(no declarations extracted)_

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshPaintingToolsetTypes.h` (Public)


#### enum `EMeshPaintDataColorViewMode`  
`enum class EMeshPaintDataColorViewMode : uint8`  
_L21-40_
- reflection: `UENUM()`
- desc: Mesh paint color view modes (somewhat maps to EVertexColorViewMode engine enum.)
- L24 _public enumerator_ `Normal UMETA(DisplayName = "Off")` — Normal view mode (vertex color visualization off)
- L27 _public enumerator_ `RGB UMETA(DisplayName = "RGB Channels")` — RGB only
- L30 _public enumerator_ `Alpha UMETA(DisplayName = "Alpha Channel")` — Alpha only
- L33 _public enumerator_ `Red UMETA(DisplayName = "Red Channel")` — Red only
- L36 _public enumerator_ `Green UMETA(DisplayName = "Green Channel")` — Green only
- L39 _public enumerator_ `Blue UMETA(DisplayName = "Blue Channel")` — Blue only

#### enum `EMeshPaintModeAction`  
`enum class EMeshPaintModeAction : uint8`  
_L43-50_
- desc: Mesh painting action (paint, erase)
- L46 _public enumerator_ `Paint` — Paint (add color or increase blending weight)
- L49 _public enumerator_ `Erase` — Erase (remove color or decrease blending weight)

#### class `FMeshPaintParameters`  
`class FMeshPaintParameters`  
_L53-78_
- desc: Mesh paint parameters
- L56 _public member_ `EMeshPaintModeAction PaintAction;`
- L57 _public member_ `FVector BrushPosition;`
- L58 _public member_ `FVector BrushNormal;`
- L59 _public member_ `FLinearColor BrushColor;`
- L60 _public member_ `float SquaredBrushRadius;`
- L61 _public member_ `float BrushRadialFalloffRange;`
- L62 _public member_ `float InnerBrushRadius;`
- L63 _public member_ `float BrushDepth;`
- L64 _public member_ `float BrushDepthFalloffRange;`
- L65 _public member_ `float InnerBrushDepth;`
- L66 _public member_ `float BrushStrength;`
- L67 _public member_ `FMatrix BrushToWorldMatrix;`
- L68 _public member_ `FMatrix InverseBrushToWorldMatrix;`
- L69 _public member_ `bool bWriteRed;`
- L70 _public member_ `bool bWriteGreen;`
- L71 _public member_ `bool bWriteBlue;`
- L72 _public member_ `bool bWriteAlpha;`
- L73 _public member_ `int32 TotalWeightCount;`
- L74 _public member_ `int32 PaintWeightIndex;`
- L75 _public member_ `FApplyVertexPaintData ApplyVertexDataDelegate;`
- L76 _public member_ `FVector2f BrushPosition2D;`
- L77 _public member_ `bool bUseFillBucket = false;`

#### struct `FTexturePaintTriangleInfo`  
`struct FTexturePaintTriangleInfo`  
_L81-86_
- desc: Structure used to hold per-triangle data for texture painting
- L83 _public member_ `FVector TriVertices[3];`
- L84 _public member_ `FVector2D TrianglePoints[3];`
- L85 _public member_ `FVector2D TriUVs[3];`

#### struct `FPaintableTexture`  
`struct FPaintableTexture`  
_L89-116_
- desc: Structure used to house and compare Texture and UV channel pairs
- L91 _public member_ `UTexture* Texture;`
- L92 _public member_ `int32 UVChannelIndex;`
- L93 _public member_ `bool bIsMeshTexture;`
- L95 _public function_ `FPaintableTexture() : Texture(nullptr) , UVChannelIndex(0) , bIsMeshTexture(false)`
- L105 _public function_ `FPaintableTexture(T InTexture = nullptr, uint32 InUVChannelIndex = 0, bool bInIsMeshTexture = false) : Texture(InTexture) , UVChannelIndex(InUVChannelIndex) , bIsMeshTexture(bInIsMeshTexture)`
- L112 _public function_ `bool operator==(const FPaintableTexture& rhs) const` — Overloaded equality operator for use with TArrays Contains method.

#### struct `FPaintTexture2DData`  
`struct FPaintTexture2DData`  
_L119-171_
- reflection: `USTRUCT()`
- L123 _public prototype_ `FPaintTexture2DData() = default;`
- L125 _public function_ `FPaintTexture2DData(UTexture2D* InPaintingTexture2D) : PaintingTexture2D(InPaintingTexture2D)`
- L132 _public member_ `TObjectPtr<UTexture2D> PaintingTexture2D;` — `UPROPERTY(Transient)` — The original texture that we're painting
- L136 _public member_ `TObjectPtr<UTextureRenderTarget2D> PaintRenderTargetTexture;` — `UPROPERTY(Transient)` — Render target texture for painting
- L140 _public member_ `TObjectPtr<class UVirtualTextureAdapter> PaintRenderTargetTextureAdapter;` — `UPROPERTY(Transient)` — Optional virtual texture adapter that we can use to visualize PaintRenderTargetTexture in materials that sample virtual textures
- L144 _public member_ `TObjectPtr<UTextureRenderTarget2D> PaintBrushRenderTargetTexture;` — `UPROPERTY(Transient)` — Optional render target texture used as an input while painting that contains a clone of the texture painting brush
- L148 _public member_ `TObjectPtr<UTextureRenderTarget2D> BrushRenderTargetTexture;` — `UPROPERTY(Transient)` — Temporary render target used to draw incremental paint to
- L152 _public member_ `TObjectPtr<UTextureRenderTarget2D> BrushMaskRenderTargetTexture;` — `UPROPERTY(Transient)` — Temporary render target used to store a mask of the affected paint region, updated every time we add incremental texture paint
- L156 _public member_ `TObjectPtr<UTextureRenderTarget2D> SeamMaskRenderTargetTexture;` — `UPROPERTY(Transient)` — Optional render target used to store generated mask for texture seams. We create this by projecting object triangles into texture space using the selected UV channel.
- L160 _public member_ `TArray<TObjectPtr<UMeshComponent>> TextureOverrideComponents;` — `UPROPERTY(Transient)` — Array of components that have the PaintRenderTargetTexture set as a texture override
- L164 _public member_ `TArray<TObjectPtr<UMeshComponent>> PaintedComponents;` — `UPROPERTY(Transient)` — Array of components that have been painted
- L167 _public member_ `TObjectPtr<UMeshComponent> SeamMaskComponent;` — Current component that was used to generate the texture seam mask used for texture dilation
- L170 _public member_ `bool bIsPaintingTexture2DModified = false;` — True if we have some painting applied to the PaintRenderTargetTexture.

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FApplyVertexPaintData, const FMeshPaintParameters& , const FLinearColor& , FLinearColor& , const float );`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FApplyVertexPaintData, const FMeshPaintParameters& , const FLinearColor& , FLinearColor& , const float );`
- L173 _namespace_ `namespace MeshPaintDefs`
- L178 _variable_ `static const int32 MaxSupportedPhysicalWeights = 4;` (scope `MeshPaintDefs`) — Currently we never support more than five channels (R, G, B, A, OneMinusTotal)
- L179 _variable_ `static const int32 MaxSupportedWeights = MaxSupportedPhysicalWeights + 1;` (scope `MeshPaintDefs`)

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshSelect.h` (Public)


#### class `UVertexAdapterClickToolBuilder`  
`class UVertexAdapterClickToolBuilder : public USingleClickToolBuilder`  
_L20-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickToolBuilder`
- desc: Builder for UVertexAdapterClickTool
- L25 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L26 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UTextureColorAdapterClickToolBuilder`  
`class UTextureColorAdapterClickToolBuilder : public USingleClickToolBuilder`  
_L34-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickToolBuilder`
- desc: Builder for UTextureColorAdapterClickTool
- L39 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L40 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UTextureAssetAdapterClickToolBuilder`  
`class UTextureAssetAdapterClickToolBuilder : public USingleClickToolBuilder`  
_L48-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickToolBuilder`
- desc: Builder for UTextureAssetAdapterClickTool
- L53 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L54 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UMeshClickTool`  
`class UMeshClickTool : public USingleClickTool, public IMeshPaintSelectionInterface`  
_L71-93_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `USingleClickTool,IMeshPaintSelectionInterface`
- desc: USingleClickTool is perhaps the simplest possible interactive tool. It simply reacts to default primary button clicks for the active device (eg left-mouse clicks). The function ::IsHitByClick() determines what is clickable by this Tool. The default is to return true, which means the click will activate anywhere (the Tool itself has no notion of Actors, Components, etc). You can override this function to, for example, filter out clicks that don't hit a target object, etc. The function ::OnClicked() implements the action that will occur when a click happens. You must override this to implement any kind of useful behavior.
- L76 _public prototype_ `UMeshClickTool();`
- L79 _public prototype_ `virtual void Setup() override;` — USingleClickTool overrides
- L80 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L81 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L82 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L83 _public prototype_ `virtual bool IsMeshAdapterSupported(TSharedPtr<IMeshPaintComponentAdapter> MeshAdapter) const override;`
- L84 _public function_ `virtual bool AllowsMultiselect() const override`
- L88 _protected member_ `static const int AdditiveSelectionModifier = 1;` — flags used to identify modifier keys/buttons
- L92 _protected member_ `TObjectPtr<UMeshPaintSelectionMechanic> SelectionMechanic;` — `UPROPERTY(Transient)`

#### class `UVertexAdapterClickTool`  
`class UVertexAdapterClickTool : public UMeshClickTool`  
_L96-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshClickTool`
- L101 _public function_ `virtual bool AllowsMultiselect() const override`

#### class `UTextureColorAdapterClickTool`  
`class UTextureColorAdapterClickTool : public UMeshClickTool`  
_L105-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshClickTool`
- L110 _public function_ `virtual bool AllowsMultiselect() const override`

#### class `UTextureAssetAdapterClickTool`  
`class UTextureAssetAdapterClickTool : public UMeshClickTool`  
_L114-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshClickTool`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshTexturePaintingTool.h` (Public)


#### class `UMeshTextureColorPaintingToolBuilder`  
`class UMeshTextureColorPaintingToolBuilder : public UInteractiveToolBuilder`  
_L31-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for the texture color mesh paint tool.
- L36 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L37 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L39 _public member_ `TWeakObjectPtr<UMeshToolManager> SharedMeshToolData;`

#### class `UMeshTextureAssetPaintingToolBuilder`  
`class UMeshTextureAssetPaintingToolBuilder : public UInteractiveToolBuilder`  
_L46-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for the texture asset mesh paint tool.
- L51 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L52 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L54 _public member_ `TWeakObjectPtr<UMeshToolManager> SharedMeshToolData;`

#### class `UMeshTexturePaintingToolProperties`  
`class UMeshTexturePaintingToolProperties : public UMeshPaintingToolProperties`  
_L62-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshPaintingToolProperties`
- desc: Base class for mesh texture paint properties.
- L69 _public member_ `bool bEnableSeamPainting = false;` — `UPROPERTY(EditAnywhere, Category = TexturePainting)` — Seam painting flag, True if we should enable dilation to allow the painting of texture seams
- L73 _public member_ `TObjectPtr<UTexture2D> PaintBrush = nullptr;` — `UPROPERTY(EditAnywhere, Category = TexturePainting, meta = (DisplayThumbnail = "true", TransientToolProperty))` — Optional Texture Brush to which Painting should use
- L77 _public member_ `float PaintBrushRotationOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = TexturePainting, meta = (TransientToolProperty, UIMin = "0.0", UIMax = "360.0", ClampMin = "0.0", ClampMax = "360.0"))` — Initial Rotation offset to apply to our paint brush
- L81 _public member_ `bool bRotateBrushTowardsDirection = false;` — `UPROPERTY(EditAnywhere, Category = TexturePainting, meta = (TransientToolProperty))` — Whether or not to continously rotate the brush towards the painting direction
- L85 _public member_ `bool bWriteRed = true;` — `UPROPERTY(EditAnywhere, Category = ColorPainting, meta = (DisplayName = "Red"))` — Whether or not to apply Texture Color Painting to the Red Channel
- L89 _public member_ `bool bWriteGreen = true;` — `UPROPERTY(EditAnywhere, Category = ColorPainting, meta = (DisplayName = "Green"))` — Whether or not to apply Texture Color Painting to the Green Channel
- L93 _public member_ `bool bWriteBlue = true;` — `UPROPERTY(EditAnywhere, Category = ColorPainting, meta = (DisplayName = "Blue"))` — Whether or not to apply Texture Color Painting to the Blue Channel
- L97 _public member_ `bool bWriteAlpha = false;` — `UPROPERTY(EditAnywhere, Category = ColorPainting, meta = (DisplayName = "Alpha"))` — Whether or not to apply Texture Color Painting to the Alpha Channel
- L100 _public function_ `virtual void GetWriteMask(bool& bOutWriteRed, bool& bOutWriteGreen, bool& bOutWriteBlue, bool& bOutWriteAlpha) const` — Get all of the write mask properties.

#### class `UMeshTextureColorPaintingToolProperties`  
`class UMeshTextureColorPaintingToolProperties : public UMeshTexturePaintingToolProperties`  
_L113-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshTexturePaintingToolProperties`
- desc: Class for texture color paint properties.
- L120 _public member_ `bool bPropagateToVertexColor = false;` — `UPROPERTY(EditAnywhere, Category = ColorPainting)` — Whether to copy all texture color painting to vertex colors.

#### class `UMeshTextureAssetPaintingToolProperties`  
`class UMeshTextureAssetPaintingToolProperties : public UMeshTexturePaintingToolProperties`  
_L127-162_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshTexturePaintingToolProperties`
- desc: Class for texture asset paint properties.
- L134 _public member_ `TObjectPtr<UMeshPaintChannelSet> ChannelSet;` — `UPROPERTY(EditAnywhere, Category = WorldChannels, meta = (DisplayThumbnail = "false"))` — The MeshPaintChannelSet asset that defines how a group of chanels map onto texture assets.
- L138 _public member_ `FName ChannelName;` — `UPROPERTY(EditAnywhere, Category = WorldChannels, meta = (GetOptions = "GetChannelNames", editcondition = "ChannelSet != nullptr"))` — The currently selected Channel from the ChannelSet.
- L142 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = TexturePainting, meta = (TransientToolProperty, editcondition = "ChannelSet == nullptr"))` — UV channel which should be used for painting textures.
- L146 _public member_ `TObjectPtr<UTexture2D> PaintTexture;` — `UPROPERTY(EditAnywhere, Category = TexturePainting, meta = (TransientToolProperty, DisplayThumbnail = "true", editcondition = "ChannelSet == nullptr"))` — Texture to which painting should be applied.
- L151 _protected prototype_ `TArray<FName> GetChannelNames() const;` — `UFUNCTION()` — Helper function to get the ChannelNames from the currently selected ChannelSet.
- L155 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L160 _protected prototype_ `virtual void GetWriteMask(bool& bOutWriteRed, bool& bOutWriteGreen, bool& bOutWriteBlue, bool& bOutWriteAlpha) const override;`

#### class `UMeshTexturePaintingTool`  
`class UMeshTexturePaintingTool : public UBaseBrushTool, public IMeshPaintSelectionInterface`  
_L169-267_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UBaseBrushTool,IMeshPaintSelectionInterface`
- desc: Base class for mesh texture painting tool.
- L174 _public prototype_ `UMeshTexturePaintingTool();`
- L176 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPaintingFinishedDelegate, UMeshComponent*);`
- L177 _public function_ `FOnPaintingFinishedDelegate& OnPaintingFinished()`
- L179 _public prototype_ `void FloodCurrentPaintTexture();`
- L181 _public function_ `virtual void GetModifiedTexturesToSave(TArray<UObject*>& OutTexturesToSave) const`
- L182 _public function_ `virtual int32 GetSelectedUVChannel(UMeshComponent const* InMeshComponent) const`
- L186 _protected prototype_ `virtual void Setup() override;`
- L187 _protected prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L188 _protected prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L189 _protected prototype_ `virtual void OnTick(float DeltaTime) override;`
- L190 _protected function_ `virtual bool HasCancel() const override`
- L191 _protected function_ `virtual bool HasAccept() const override`
- L192 _protected function_ `virtual bool CanAccept() const override`
- L193 _protected prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L194 _protected prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L195 _protected prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L196 _protected prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L197 _protected prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L198 _protected prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;`
- L199 _protected prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L200 _protected prototype_ `virtual double EstimateMaximumTargetDimension() override;`
- L203 _protected prototype_ `FPaintTexture2DData* GetPaintTargetData(const UTexture2D* InTexture);`
- L204 _protected prototype_ `FPaintTexture2DData* AddPaintTargetData(UTexture2D* InTexture);`
- L206 _protected prototype_ `void SetAllTextureOverrides(FMaterialUpdateContext& MaterialUpdateContext);`
- L207 _protected prototype_ `void ClearAllTextureOverrides(FMaterialUpdateContext& MaterialUpdateContext);`
- L209 _protected function_ `virtual UTexture2D* GetSelectedPaintTexture(UMeshComponent const* InMeshComponent) const`
- L210 _protected function_ `virtual void CacheTexturePaintData()`
- L211 _protected function_ `virtual bool CanPaintTextureToComponent(UTexture* InTexture, UMeshComponent const* InMeshComponent) const`
- L212 _protected function_ `virtual void ApplyWorldChannelUVs(TArrayView<FTexturePaintTriangleInfo> TriangleInfo) const`
- L215 _private prototype_ `void CacheSelectionData();`
- L216 _private prototype_ `void AddTextureOverrideToComponent(FPaintTexture2DData& TextureData, UMeshComponent* MeshComponent, const IMeshPaintComponentAdapter* MeshPaintAdapter, FMaterialUpdateContext& MaterialUpdateContext);`
- L217 _private prototype_ `double CalculateTargetEdgeLength(int TargetTriCount);`
- L218 _private prototype_ `void StartPaintingTexture(UMeshComponent* InMeshComponent, const IMeshPaintComponentAdapter& GeometryInfo);`
- L219 _private prototype_ `void UpdateResult();`
- L220 _private prototype_ `void GatherTextureTriangles(IMeshPaintComponentAdapter* Adapter, int32 TriangleIndex, const int32 VertexIndices[3], TArray<FTexturePaintTriangleInfo>* TriangleInfo, TArray<FTexturePaintMeshSectionInfo>* SectionInfos, int32 UVChannelIndex);`
- L221 _private prototype_ `bool Paint(const FVector& InRayOrigin, const FVector& InRayDirection);`
- L222 _private prototype_ `bool Paint(const TArrayView<TPair<FVector, FVector>>& Rays);`
- L223 _private prototype_ `void PaintTexture(FMeshPaintParameters& InParams, int32 UVChannel, TArray<FTexturePaintTriangleInfo>& InInfluencedTriangles, UMeshComponent* MeshComponent, const IMeshPaintComponentAdapter& GeometryInfo, FMeshPaintParameters* LastParams = nullptr);`
- L224 _private prototype_ `bool PaintInternal(const TArrayView<TPair<FVector, FVector>>& Rays, EMeshPaintModeAction PaintAction, float PaintStrength);`
- L225 _private prototype_ `void FinishPaintingTexture();`
- L226 _private prototype_ `void FinishPainting();`
- L230 _protected member_ `TArray<FPaintableTexture> PaintableTextures;` — Textures eligible for painting retrieved from the current selection
- L234 _protected member_ `TMap<TObjectPtr<UTexture2D>, FPaintTexture2DData> PaintTargetData;` — `UPROPERTY(Transient)` — Stores data associated with our paint target textures
- L238 _private member_ `TObjectPtr<UMeshPaintSelectionMechanic> SelectionMechanic;` — `UPROPERTY(Transient)`
- L241 _private member_ `TObjectPtr<UMeshTexturePaintingToolProperties> TextureProperties;` — `UPROPERTY(Transient)`
- L245 _private member_ `TObjectPtr<UTexture2D> PaintingTexture2D;` — `UPROPERTY(Transient)` — The original texture that we're painting
- L248 _private member_ `TUniquePtr<FScopedTransaction> PaintingTransaction;` — Hold the transaction while we are painting
- L250 _private member_ `double InitialMeshArea = 0;`
- L251 _private member_ `bool bArePainting = false;`
- L252 _private member_ `bool bResultValid = false;`
- L253 _private member_ `bool bStampPending = false;`
- L254 _private member_ `bool bInDrag = false;`
- L255 _private member_ `bool bRequestPaintBucketFill = false;`
- L256 _private member_ `bool bRequiresRuntimeVirtualTextureUpdates = false;`
- L258 _private member_ `bool bCachedClickRay = false;`
- L259 _private member_ `FRay PendingStampRay;`
- L260 _private member_ `FRay PendingClickRay;`
- L261 _private member_ `FVector2D PendingClickScreenPosition;`
- L263 _private member_ `TArray<FPaintRayResults> LastPaintRayResults;`
- L264 _private member_ `FHitResult LastBestHitResult;`
- L266 _private member_ `FOnPaintingFinishedDelegate OnPaintingFinishedDelegate;`

#### class `UMeshTextureColorPaintingTool`  
`class UMeshTextureColorPaintingTool : public UMeshTexturePaintingTool`  
_L276-304_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshTexturePaintingTool`
- desc: Class for texture color painting tool. This paints to special textures stored on the mesh components. Behavior should be similar to vertex painting (per instance painting stored on components). But painting texture colors instead of vertex colors is a better fit for very dense mesh types such as used by nanite.
- L281 _public prototype_ `UMeshTextureColorPaintingTool();`
- L285 _protected prototype_ `virtual void Setup() override;`
- L289 _protected function_ `virtual bool AllowsMultiselect() const override`
- L290 _protected prototype_ `virtual bool IsMeshAdapterSupported(TSharedPtr<IMeshPaintComponentAdapter> MeshAdapter) const override;`
- L291 _protected prototype_ `virtual UTexture2D* GetSelectedPaintTexture(UMeshComponent const* InMeshComponent) const override;`
- L292 _protected prototype_ `virtual int32 GetSelectedUVChannel(UMeshComponent const* InMeshComponent) const override;`
- L293 _protected prototype_ `virtual void GetModifiedTexturesToSave(TArray<UObject*>& OutTexturesToSave) const override;`
- L294 _protected prototype_ `virtual void CacheTexturePaintData() override;`
- L295 _protected prototype_ `virtual bool CanPaintTextureToComponent(UTexture* InTexture, UMeshComponent const* InMeshComponent) const override;`
- L300 _private member_ `TObjectPtr<UMeshTextureColorPaintingToolProperties> ColorProperties;` — `UPROPERTY(Transient)`
- L303 _private member_ `TObjectPtr<UTexture> MeshPaintDummyTexture;` — `UPROPERTY(Transient)`

#### class `UMeshTextureAssetPaintingTool`  
`class UMeshTextureAssetPaintingTool : public UMeshTexturePaintingTool`  
_L312-349_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshTexturePaintingTool`
- desc: Class for texture asset painting tool. This paints to texture assets directly from the mesh. The texture asset to paint is selected from the ones referenced in the mesh component's materials.
- L317 _public prototype_ `UMeshTextureAssetPaintingTool();`
- L320 _public prototype_ `void CycleTextures(int32 Direction);` — Change selected texture to previous or next available.
- L323 _public prototype_ `UTexture* GetSelectedPaintTextureWithOverride() const;` — Get the selected paint texture, and return the modified overriden texture if currently painting.
- L326 _public prototype_ `bool ShouldFilterTextureAsset(const FAssetData& AssetData) const;` — Returns true if asset shouldn't be shown in UI because it is not in our paintable texture array.
- L328 _public prototype_ `virtual int32 GetSelectedUVChannel(UMeshComponent const* InMeshComponent) const override;`
- L332 _protected prototype_ `virtual void Setup() override;`
- L336 _protected function_ `virtual bool AllowsMultiselect() const override`
- L337 _protected prototype_ `virtual bool IsMeshAdapterSupported(TSharedPtr<IMeshPaintComponentAdapter> MeshAdapter) const override;`
- L338 _protected prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L339 _protected prototype_ `virtual UTexture2D* GetSelectedPaintTexture(UMeshComponent const* InMeshComponent) const override;`
- L340 _protected prototype_ `virtual void GetModifiedTexturesToSave(TArray<UObject*>& OutTexturesToSave) const override;`
- L341 _protected prototype_ `virtual void CacheTexturePaintData() override;`
- L342 _protected prototype_ `virtual bool CanPaintTextureToComponent(UTexture* InTexture, UMeshComponent const* InMeshComponent) const override;`
- L343 _protected prototype_ `virtual void ApplyWorldChannelUVs(TArrayView<FTexturePaintTriangleInfo> TriangleInfo) const override;`
- L348 _private member_ `TObjectPtr<UMeshTextureAssetPaintingToolProperties> AssetProperties;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`
- L176 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPaintingFinishedDelegate, UMeshComponent*);`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/MeshVertexPaintingTool.h` (Public)


#### struct `FPaintRayResults`  
`struct FPaintRayResults`  
_L19-23_
- L21 _public member_ `FMeshPaintParameters Params;`
- L22 _public member_ `FHitResult BestTraceResult;`

#### enum `EMeshPaintWeightTypes`  
`enum class EMeshPaintWeightTypes : uint8`  
_L26-39_
- reflection: `UENUM()`
- L29 _public enumerator_ `AlphaLerp = 2 UMETA(DisplayName = "Alpha (Two Textures)")` — Lerp Between Two Textures using Alpha Value
- L32 _public enumerator_ `RGB = 3 UMETA(DisplayName = "RGB (Three Textures)")` — Weighting Three Textures according to Channels
- L35 _public enumerator_ `ARGB = 4 UMETA(DisplayName = "ARGB (Four Textures)")` — Weighting Four Textures according to Channels
- L38 _public enumerator_ `OneMinusARGB = 5 UMETA(DisplayName = "ARGB - 1 (Five Textures)")` — Weighting Five Textures according to Channels

#### enum `EMeshPaintTextureIndex`  
`enum class EMeshPaintTextureIndex : uint8`  
_L42-49_
- reflection: `UENUM()`
- L44 _public enumerator_ `TextureOne = 0`
- L45 _public enumerator_ `TextureTwo`
- L46 _public enumerator_ `TextureThree`
- L47 _public enumerator_ `TextureFour`
- L48 _public enumerator_ `TextureFive`

#### class `UMeshVertexColorPaintingToolBuilder`  
`class UMeshVertexColorPaintingToolBuilder : public UInteractiveToolBuilder`  
_L56-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L61 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L62 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UMeshVertexWeightPaintingToolBuilder`  
`class UMeshVertexWeightPaintingToolBuilder : public UInteractiveToolBuilder`  
_L66-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L71 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L72 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UMeshVertexPaintingToolProperties`  
`class UMeshVertexPaintingToolProperties : public UMeshPaintingToolProperties`  
_L77-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshPaintingToolProperties`
- L82 _public prototype_ `UMeshVertexPaintingToolProperties();`
- L86 _public member_ `bool bPaintOnSpecificLOD = false;` — `UPROPERTY(EditAnywhere, Category = VertexPainting, meta = (InlineEditConditionToggle, TransientToolProperty))` — When unchecked the painting on the base LOD will be propagate automatically to all other LODs when exiting the mode or changing the selection
- L90 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = VertexPainting, meta = (UIMin = "0", ClampMin = "0", EditCondition = "bPaintOnSpecificLOD", TransientToolProperty))` — Index of LOD to paint. If not set then paint is applied to all LODs.
- L94 _public member_ `float VertexPreviewSize;` — `UPROPERTY(EditAnywhere, Category = VertexPainting, meta = (UIMin = "0", ClampMin = "0"))` — Size of vertex points drawn when mesh painting is active.

#### class `UMeshVertexColorPaintingToolProperties`  
`class UMeshVertexColorPaintingToolProperties : public UMeshVertexPaintingToolProperties`  
_L98-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexPaintingToolProperties`
- L105 _public member_ `bool bWriteRed = true;` — `UPROPERTY(EditAnywhere, Category = ColorPainting, DisplayName = "Red")` — Whether or not to apply Vertex Color Painting to the Red Channel
- L109 _public member_ `bool bWriteGreen = true;` — `UPROPERTY(EditAnywhere, Category = ColorPainting, DisplayName = "Green")` — Whether or not to apply Vertex Color Painting to the Green Channel
- L113 _public member_ `bool bWriteBlue = true;` — `UPROPERTY(EditAnywhere, Category = ColorPainting, DisplayName = "Blue")` — Whether or not to apply Vertex Color Painting to the Blue Channel
- L117 _public member_ `bool bWriteAlpha = false;` — `UPROPERTY(EditAnywhere, Category = ColorPainting, DisplayName = "Alpha")` — Whether or not to apply Vertex Color Painting to the Alpha Channel

#### class `UMeshVertexWeightPaintingToolProperties`  
`class UMeshVertexWeightPaintingToolProperties : public UMeshVertexPaintingToolProperties`  
_L121-139_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexPaintingToolProperties`
- L126 _public prototype_ `UMeshVertexWeightPaintingToolProperties();`
- L130 _public member_ `EMeshPaintWeightTypes TextureWeightType;` — `UPROPERTY(EditAnywhere, Category = WeightPainting, meta = (EnumCondition = 1))` — Texture Blend Weight Painting Mode
- L134 _public member_ `EMeshPaintTextureIndex PaintTextureWeightIndex;` — `UPROPERTY(EditAnywhere, Category = WeightPainting, meta = (EnumCondition = 1))` — Texture Blend Weight index which should be applied during Painting
- L138 _public member_ `EMeshPaintTextureIndex EraseTextureWeightIndex;` — `UPROPERTY(EditAnywhere, Category = WeightPainting, meta = (EnumCondition = 1))` — Texture Blend Weight index which should be erased during Painting

#### class `UMeshVertexPaintingTool`  
`class UMeshVertexPaintingTool : public UBaseBrushTool, public IMeshPaintSelectionInterface`  
_L143-217_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UBaseBrushTool,IMeshPaintSelectionInterface`
- L148 _public prototype_ `UMeshVertexPaintingTool();`
- L150 _public prototype_ `void PaintLODChanged();`
- L151 _public prototype_ `void LODPaintStateChanged(const bool bLODPaintingEnabled);`
- L153 _public prototype_ `int32 GetMaxLODIndexToPaint() const;`
- L154 _public function_ `int32 GetCachedLODIndex() const`
- L156 _public prototype_ `void CycleMeshLODs(int32 Direction);`
- L158 _public function_ `FSimpleDelegate& OnPaintingFinished()`
- L161 _protected prototype_ `virtual void Setup() override;`
- L162 _protected prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L163 _protected prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L164 _protected prototype_ `virtual void OnTick(float DeltaTime) override;`
- L165 _protected function_ `virtual bool HasCancel() const override`
- L166 _protected function_ `virtual bool HasAccept() const override`
- L167 _protected function_ `virtual bool CanAccept() const override`
- L168 _protected prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L169 _protected prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L170 _protected prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L171 _protected prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L172 _protected prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L173 _protected prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;`
- L174 _protected prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L175 _protected function_ `virtual bool AllowsMultiselect() const override`
- L176 _protected prototype_ `virtual bool IsMeshAdapterSupported(TSharedPtr<IMeshPaintComponentAdapter> MeshAdapter) const override;`
- L177 _protected prototype_ `virtual double EstimateMaximumTargetDimension() override;`
- L179 _protected function_ `virtual void SetAdditionalPaintParameters(FMeshPaintParameters& InPaintParameters)`
- L182 _private prototype_ `void CacheSelectionData();`
- L183 _private prototype_ `void ApplyForcedLODIndex(int32 ForcedLODIndex);`
- L184 _private prototype_ `void UpdateResult();`
- L185 _private prototype_ `bool Paint(const FVector& InRayOrigin, const FVector& InRayDirection);`
- L186 _private prototype_ `bool Paint(const TArrayView<TPair<FVector, FVector>>& Rays);`
- L187 _private prototype_ `bool PaintInternal(const TArrayView<TPair<FVector, FVector>>& Rays, EMeshPaintModeAction PaintAction, float PaintStrength);`
- L188 _private prototype_ `void ApplyVertexData(FPerVertexPaintActionArgs& InArgs, int32 VertexIndex, FMeshPaintParameters Parameters);`
- L189 _private prototype_ `void FinishPainting();`
- L190 _private prototype_ `double CalculateTargetEdgeLength(int TargetTriCount);`
- L194 _private member_ `TObjectPtr<UMeshPaintSelectionMechanic> SelectionMechanic;` — `UPROPERTY(Transient)`
- L197 _private member_ `TObjectPtr<UMeshVertexPaintingToolProperties> VertexProperties;` — `UPROPERTY(Transient)`
- L200 _private member_ `int32 CachedLODIndex;` — Current LOD index used for painting / forcing
- L202 _private member_ `bool bCachedForceLOD;` — Whether or not a specific LOD level should be forced
- L204 _private member_ `double InitialMeshArea = 0;`
- L205 _private member_ `bool bArePainting = false;`
- L206 _private member_ `bool bResultValid = false;`
- L207 _private member_ `bool bStampPending = false;`
- L208 _private member_ `bool bInDrag = false;`
- L210 _private member_ `bool bCachedClickRay = false;`
- L211 _private member_ `FRay PendingStampRay;`
- L212 _private member_ `FRay PendingClickRay;`
- L213 _private member_ `FVector2D PendingClickScreenPosition;`
- L214 _private member_ `FHitResult LastBestHitResult;`
- L216 _private member_ `FSimpleDelegate OnPaintingFinishedDelegate;`

#### class `UMeshVertexColorPaintingTool`  
`class UMeshVertexColorPaintingTool : public UMeshVertexPaintingTool`  
_L220-235_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexPaintingTool`
- L225 _public prototype_ `UMeshVertexColorPaintingTool();`
- L228 _protected prototype_ `virtual void Setup() override;`
- L230 _protected prototype_ `virtual void SetAdditionalPaintParameters(FMeshPaintParameters& InPaintParameters) override;`
- L234 _private member_ `TObjectPtr<UMeshVertexColorPaintingToolProperties> ColorProperties;` — `UPROPERTY(Transient)`

#### class `UMeshVertexWeightPaintingTool`  
`class UMeshVertexWeightPaintingTool : public UMeshVertexPaintingTool`  
_L238-253_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexPaintingTool`
- L243 _public prototype_ `UMeshVertexWeightPaintingTool();`
- L246 _protected prototype_ `virtual void Setup() override;`
- L248 _protected prototype_ `virtual void SetAdditionalPaintParameters(FMeshPaintParameters& InPaintParameters);`
- L252 _private member_ `TObjectPtr<UMeshVertexWeightPaintingToolProperties> WeightProperties;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/TMeshPaintOctree.h` (Public)


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
- L34 _public function_ `inline static FBoxCenterAndExtent GetBoundingBox(const FMeshPaintTriangle& Element)` — Get the bounding box of the provided octree element. In this case, the box is merely the point specified by the element. @param	Element	Octree element to get the bounding box for @return	Bounding box of the provided octree element
- L48 _public function_ `inline static bool AreElementsEqual(const FMeshPaintTriangle& A, const FMeshPaintTriangle& B)` — Determine if two octree elements are equal @param	A	First octree element to check @param	B	Second octree element to check @return	true if both octree elements are equal, false if they are not
- L54 _public function_ `inline static void SetElementId(const FMeshPaintTriangle& Element, FOctreeElementId2 Id)` — Ignored for this implementation

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

- L20 _enumerator_ `enum { MaxElementsPerLeaf = 16 }; enum { MinInclusiveElementsPerNode = 7 }; enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; /** * Get the bounding box of the provided octree element. In this case` (scope `FMeshPaintTriangleOctreeSemantics::__anon0e0ddb400103`)
- L21 _enumerator_ `enum { MinInclusiveElementsPerNode = 7 }; enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; /** * Get the bounding box of the provided octree element. In this case` (scope `FMeshPaintTriangleOctreeSemantics::__anon0e0ddb400203`)
- L22 _enumerator_ `enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; /** * Get the bounding box of the provided octree element. In this case` (scope `FMeshPaintTriangleOctreeSemantics::__anon0e0ddb400303`)
- L59 _typedef_ `typedef TOctree2<FMeshPaintTriangle, FMeshPaintTriangleOctreeSemantics> FMeshPaintTriangleOctree;`

### `Plugins/MeshPainting/Source/MeshPaintingToolset/Public/TexturePaintToolset.h` (Public)


#### class `FMeshPaintBatchedElementParameters`  
`class FMeshPaintBatchedElementParameters : public FBatchedElementParameters`  
_L22-35_
- inherits: `FBatchedElementParameters`
- desc: Batched element parameters for texture paint shaders used for paint blending and paint mask generation
- L26 _public function_ `virtual void BindShaders(FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override` — Binds vertex and pixel shaders for this element
- L34 _public member_ `MeshPaintRendering::FMeshPaintShaderParameters ShaderParams;` — Shader parameters

#### class `FMeshPaintDilateBatchedElementParameters`  
`class FMeshPaintDilateBatchedElementParameters : public FBatchedElementParameters`  
_L38-51_
- inherits: `FBatchedElementParameters`
- desc: Batched element parameters for texture paint shaders used for texture dilation
- L42 _public function_ `virtual void BindShaders(FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override` — Binds vertex and pixel shaders for this element
- L50 _public member_ `MeshPaintRendering::FMeshPaintDilateShaderParameters ShaderParams;` — Shader parameters

#### struct `FTexturePaintMeshSectionInfo`  
`struct FTexturePaintMeshSectionInfo`  
_L54-61_
- desc: Helper struct to store mesh section information in
- L57 _public member_ `int32 FirstIndex;` — First vertex index in section
- L60 _public member_ `int32 LastIndex;` — Last vertex index in section

#### class `UTexturePaintToolset`  
`class UTexturePaintToolset : public UBlueprintFunctionLibrary`  
_L68-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Helpers functions for texture painting functionality
- L73 _public prototype_ `static void CopyTextureToRenderTargetTexture(UTexture* SourceTexture, UTextureRenderTarget2D* RenderTargetTexture, ERHIFeatureLevel::Type FeatureLevel);` — Static: Copies a texture to a render target texture
- L76 _public prototype_ `static bool GenerateSeamMask(UMeshComponent* MeshComponent, int32 UVSet, UTextureRenderTarget2D* SeamRenderTexture, UTexture2D* Texture, UTextureRenderTarget2D* RenderTargetTexture );` — Will generate a mask texture, used for texture dilation, and store it in the passed in render target
- L79 _public prototype_ `static int32 GetMaxSupportedBytesPerPixelForPainting();` — Returns the maximum bytes per pixel that are supported for source textures when painting. This limitation is set by CreateTempUncompressedTexture.
- L82 _public prototype_ `static EPixelFormat GetTempUncompressedTexturePixelFormat();` — Returns the pixel format that CreateTempUncompressedTexture uses to create render target data for painting.
- L85 _public prototype_ `static UTexture2D* CreateScratchUncompressedTexture(UTexture2D* SourceTexture);` — Static: Creates a temporary texture used to transfer data to a render target in memory
- L88 _public prototype_ `static void SetupInitialRenderTargetData(UTexture2D* InTextureSource, UTextureRenderTarget2D* InRenderTarget);` — Keep old legacy method of initializing render target data for the paint brush texture; @todo MeshPaint: Migrate to the method with texture re-use
- L91 _public prototype_ `static void FindMaterialIndicesUsingTexture(const UTexture* Texture, const UMeshComponent* MeshComponent, TArray<int32>& OutIndices);` — Tries to find Materials using the given Texture and retrieve the corresponding material indices from the MEsh Compon
- L94 _public prototype_ `static void RetrieveMeshSectionsForTextures(const UMeshComponent* MeshComponent, int32 LODIndex, TArray<const UTexture*> Textures, TArray<FTexturePaintMeshSectionInfo>& OutSectionInfo);` — Retrieve LOD mesh sections from MeshComponent which use one of the given textures
- L97 _public prototype_ `static void RetrieveMeshSectionsForMaterialIndices(const UMeshComponent* MeshComponent, int32 LODIndex, const TArray<int32>& MaterialIndices, TArray<FTexturePaintMeshSectionInfo>& OutSectionInfo);` — Retrieve LOD mesh sections from MeshComponent which contain one of the Material Indices
- L100 _public prototype_ `static void RetrieveTexturesForComponent(const UMeshComponent* Component, IMeshPaintComponentAdapter* Adapter, int32& OutDefaultIndex, TArray<FPaintableTexture>& OutTextures);` — Retrieves all Paintable Textures from the given MeshComponent

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPAINTINGTOOLSET_API`
