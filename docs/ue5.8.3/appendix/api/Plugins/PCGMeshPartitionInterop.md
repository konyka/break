# Plugins / PCGMeshPartitionInterop

- module root: `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop`
- headers: 20; symbols: 472
- symbol kinds: class=30, delegate=1, enum=2, enumerator=6, function=78, member=161, namespace=45, prototype=127, struct=21, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GeometryCore, GeometryFramework, Landscape, MeshPartition, MeshPartitionEditor, PCG, PCGCompute, PCGGeometryScriptInterop, RHI, RenderCore, Renderer

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Internal/Data/PCGMeshTerrainSectionData.h` (Internal)


#### struct `UE::MeshPartition::FPCGDataTypeInfoMeshTerrainSection`  
`struct FPCGDataTypeInfoMeshTerrainSection : public FPCGDataTypeInfo`  
_L18-23_
- reflection: `USTRUCT(meta = (PCG_DataTypeDisplayName = "Mesh Terrain Section"))`
- inherits: `FPCGDataTypeInfo`

#### class `UE::MeshPartition::UPCGMeshTerrainSectionData`  
`class UPCGMeshTerrainSectionData : public UPCGData`  
_L27-43_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- desc: Reference to a single mesh terrain section.
- L33 _public prototype_ `PCG_ASSIGN_TYPE_INFO(FPCGDataTypeInfoMeshTerrainSection) virtual void AddToCrc(FArchiveCrc32& Ar, bool bFullDataCrc) const override;`
- L35 _public prototype_ `virtual UPCGData* DuplicateData(FPCGContext* Context, bool bInitializeMetadata = true) const override;`
- L38 _public prototype_ `AActor* GetSectionActor() const;`
- L39 _public prototype_ `void SetSectionActor(AActor* InSectionActor);`
- L42 _private member_ `TWeakObjectPtr<AActor> SectionActor;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Data/PCGMeshPartitionData.h` (Private)


#### enum `UE::MeshPartition::EPCGQueryType`  
`enum class EPCGQueryType : uint8`  
_L16-26_
- reflection: `UENUM(BlueprintType, Meta=(DisplayName = "Mesh Partition PCG Query Type"))`
- L19 _public enumerator_ `Base` — Samples against the Mega Mesh Base modifiers directly before any procedural applications. Not valid at runtime
- L21 _public enumerator_ `Intermediate` — Samples the Mega Mega at intermediate build layer and sub priority. Not valid at runtime
- L23 _public enumerator_ `IntermediateLayer` — Samples the Mega Mega at intermediate build layers, not considering sub priority. Not valid at runtime
- L25 _public enumerator_ `Final` — Samples against the final built Mega Mesh (after all procedural application). Valid at runtime

#### struct `UE::MeshPartition::FPCGQueryParams`  
`struct FPCGQueryParams`  
_L29-103_
- reflection: `USTRUCT(BlueprintType, Meta = (DisplayName = "Mesh Partition PCG Query Params"))`
- L34 _public member_ `FVector RayOrigin = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable, EditCondition = "bOverrideDefaultParams", EditConditionHides))`
- L37 _public member_ `FVector RayDirection = FVector(0.0, 0.0, -1.0);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable, EditCondition = "bOverrideDefaultParams", EditConditionHides))`
- L40 _public member_ `double RayLength = 1.0e+7;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable, EditCondition = "bOverrideDefaultParams", EditConditionHides))`
- L43 _public member_ `MeshPartition::EPCGQueryType QueryType = MeshPartition::EPCGQueryType::Base;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable))`
- L48 _public member_ `FName LayerName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable, EditCondition = "QueryType == EPCGQueryType::Intermediate || QueryType == EPCGQueryType::IntermediateLayer", EditConditionHides))` — When sampling an intermediate build, the layer up to which to build the mesh (not including the layer itself, unless Inlcusive is set).
- L53 _public member_ `double SubPriority = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable, EditCondition = "QueryType == EPCGQueryType::Intermediate", EditConditionHides))` — When sampling an intermediate build, optional specific sub-priority up to which to build the mesh within the chosen priority layer (higher priorities are applied after lower).
- L58 _public member_ `bool bInclusive = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable, EditCondition = "QueryType == EPCGQueryType::Intermediate || QueryType == EPCGQueryType::IntermediateLayer", EditConditionHides))` — When sampling an intermediate build, whether we build up to but not including the given layer/sub-priority, or whether we include it.
- L64 _public member_ `uint8 bRecomputeVertexNormals : 1 = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, AdvancedDisplay, meta = (PCG_Overridable, EditCondition = "QueryType != EPCGQueryType::Base", EditConditionHides))` — When not sampling base sections, whether to update the vertex normals. Vertex normals are used for point rotations when converting to points.
- L68 _public member_ `uint8 bOverrideDefaultParams : 1 = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (DisplayName = "Set Ray Parameters", PCG_Overridable))` — Set ray parameters including origin, direction and length explicitly rather than deriving these from the generating actor bounds.
- L72 _public member_ `TArray<FName> Channels;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data|Attributes", meta = (PCG_Overridable))` — Specifies which channel we will want to sample.
- L76 _public member_ `uint8 bGetImpactPoint : 1 = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data|Attributes", meta = (PCG_Overridable))` — Create an attribute for the impact location in world space.
- L80 _public member_ `uint8 bGetImpactNormal : 1 = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data|Attributes", meta = (PCG_Overridable))` — Create an attribute for the impact normal.
- L84 _public member_ `uint8 bGetDistance : 1 = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data|Attributes", meta = (PCG_Overridable))` — Create an attribute for the distance between the ray origin and the impact point.
- L88 _public member_ `uint8 bGetFaceIndex : 1 = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data|Attributes", meta = (PCG_Overridable))` — Create an attribute for index of the hit face. Note: Will only work in complex traces.
- L92 _public member_ `uint8 bGetUVCoords : 1 = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data|Attributes", meta = (PCG_Overridable))` — Create an attribute for UV Coordinates of the surface hit. Note: Will only work in complex traces.
- L98 _public member_ `uint8 bAcceptAnyHitSection : 1 = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, AdvancedDisplay, meta = (PCG_Overridable))` — When false, raycast all possible sections to make sure we get the closest hit, but if true, accept any hit. This can be left true to speed up sampling, as long as your sections don't overlap in such a way that a sampling ray could hit multiple sections.
- L102 _public member_ `TSoftObjectPtr<AMeshPartition> MegaMeshOverride;` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (PCG_Overridable))` — When supplied, only the given megamesh will be queried. Otherwise, all megameshes in bounds will be queried.

#### class `UE::MeshPartition::UPCGMeshPartitionData`  
`class UPCGMeshPartitionData : public UPCGSurfaceData`  
_L106-165_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSurfaceData`
- L111 _public prototype_ `void Initialize(FPCGMeshPartitionElementContext* InContext, UWorld* InWorld, const FTransform& InTransform, const FBox& InBounds = FBox(EForceInit::ForceInit), const FBox& InLocalBounds = FBox(EForceInit::ForceInit));`
- L112 _public prototype_ `bool IsDataReady() const;`
- L115 _public prototype_ `virtual void AddToCrc(FArchiveCrc32& InAr, bool bInFullDataCrc) const override;`
- L119 _public function_ `virtual FBox GetBounds() const override`
- L120 _public function_ `virtual FBox GetStrictBounds() const override`
- L121 _public function_ `virtual bool IsBounded() const override`
- L122 _public prototype_ `virtual bool SamplePoint(const FTransform& InTransform, const FBox& InBounds, FPCGPoint& OutPoint, UPCGMetadata* OutMetadata) const override;`
- L123 _public function_ `virtual bool HasNonTrivialTransform() const override`
- L124 _public function_ `virtual FVector GetNormal() const override`
- L126 _protected prototype_ `virtual UPCGSpatialData* CopyInternal(FPCGContext* Context) const override;`
- L131 _public function_ `virtual bool SupportsBoundedPointData() const`
- L132 _public function_ `virtual const UPCGPointData* CreatePointData(FPCGContext* InContext) const override`
- L133 _public prototype_ `virtual const UPCGPointData* CreatePointData(FPCGContext* InContext, const FBox& InBounds) const override;`
- L134 _public prototype_ `virtual const UPCGPointArrayData* CreatePointArrayData(FPCGContext* InContext, const FBox& InBounds) const override;`
- L138 _public member_ `TWeakObjectPtr<UWorld> World = nullptr;` — `UPROPERTY()`
- L141 _public member_ `TWeakObjectPtr<UPCGComponent> OriginatingComponent = nullptr;` — `UPROPERTY()`
- L144 _public member_ `FBox Bounds = FBox(EForceInit::ForceInit);` — `UPROPERTY()`
- L147 _public member_ `MeshPartition::FPCGQueryParams QueryParams;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (ShowOnlyInnerProperties))`
- L161 _public member_ `TArray<FSectionData> SectionDatas;`
- L164 _private prototype_ `const UPCGBasePointData* CreateBasePointData(FPCGContext* Context, const FBox& InBounds, TSubclassOf<UPCGBasePointData> PointDataClass) const;`

#### struct `UE::MeshPartition::UPCGMeshPartitionData::FSectionData`  
`struct FSectionData`  
_L149-160_
- L151 _public member_ `TSharedPtr<const FMeshData> MeshData;`
- L153 _public member_ `FTransform Transform;`
- L155 _public member_ `TSharedPtr<const FMeshABBTree3> Spatial;`
- L157 _public member_ `Tasks::FTask BuildSpatialTask;`
- L159 _public member_ `TWeakObjectPtr<AMeshPartition> MegaMeshActor;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Data/PCGMeshPartitionSelectionKey.h` (Private)


#### enum `UE::MeshPartition::EPCGLayerSelectionKeyType`  
`enum class EPCGLayerSelectionKeyType`  
_L20-26_
- reflection: `UENUM()`
- desc: To control how the key is matched against other keys, keys are marked with their context for use. For example, the priority on a change key would match a listener key if the listener priority is higher, but not the reverse.
- L23 _public enumerator_ `Listener` — This key is used to listen to change events
- L25 _public enumerator_ `ChangeNotification` — This key is issued with change events

#### struct `UE::MeshPartition::FPCGLayerSelectionKey`  
`struct FPCGLayerSelectionKey : public FPCGCustomSelectionKey`  
_L33-88_
- reflection: `USTRUCT()`
- inherits: `FPCGCustomSelectionKey`
- desc: Selection Key used to listen to a mesh partition change. Mesh partition changes trigger selection key notifications corresponding to layers at the changed layer and above.
- L38 _public prototype_ `FPCGLayerSelectionKey() = default;`
- L39 _public prototype_ `explicit FPCGLayerSelectionKey(MeshPartition::EPCGQueryType InQueryType, FName InLayerName = NAME_None, double InSubPriority = 0, bool bInIsFromPrevious = false, EPCGLayerSelectionKeyType InKeyType = EPCGLayerSelectionKeyType::ChangeNotification);`
- L45 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L53 _protected member_ `MeshPartition::EPCGQueryType QueryType = MeshPartition::EPCGQueryType::Intermediate;` — `UPROPERTY()`
- L61 _protected member_ `FName LayerName = NAME_None;` — `UPROPERTY()` — Only relevant when QueryType is Intermediate or IntermediateLayer. Any change will also trigger a change with a None layer name, to allow matching against layers that are not found in the definition.
- L67 _protected member_ `double SubPriority = 0;` — `UPROPERTY()` — Only relevant when QueryType is Intermediate.
- L75 _protected member_ `bool bIsFromPrevious = false;` — `UPROPERTY()` — For change notifications, this is set to true if the change was made in a preceding layer. For query keys, this should be set to true if the change has to be made in a preceding layer or priority (i.e. matching is exclusive)
- L83 _protected member_ `EPCGLayerSelectionKeyType KeyType = EPCGLayerSelectionKeyType::ChangeNotification;` — `UPROPERTY()` — Marks this key as being a query (rather than a change notification), which determines how SubPriority and bIsFromPrevious are interpreted when matching against other keys (e.g. which SubPriority needs to be higher for a match).
- L85 _protected prototype_ `virtual bool IsMatchingInternal(const FPCGCustomSelectionKey& InCustomKey) const override;`
- L86 _protected prototype_ `virtual bool EqualsInternal(const FPCGCustomSelectionKey& InCustomKey) const override;`
- L87 _protected prototype_ `virtual uint32 GetTypeHashInternal() const override;`

#### struct `UE::MeshPartition::FPCGGlobalSelectionKey`  
`struct FPCGGlobalSelectionKey : public FPCGCustomSelectionKey`  
_L94-111_
- reflection: `USTRUCT()`
- inherits: `FPCGCustomSelectionKey`
- desc: Selection Key used to listen to global changes.
- L99 _public prototype_ `FPCGGlobalSelectionKey() = default;`
- L101 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L108 _protected prototype_ `virtual bool IsMatchingInternal(const FPCGCustomSelectionKey& InCustomKey) const override;`
- L109 _protected prototype_ `virtual bool EqualsInternal(const FPCGCustomSelectionKey& InCustomKey) const override;`
- L110 _protected prototype_ `virtual uint32 GetTypeHashInternal() const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGBakeMeshTerrainSectionMesh.h` (Private)


#### class `UE::MeshPartition::UPCGBakeMeshTerrainSectionMeshSettings`  
`class UPCGBakeMeshTerrainSectionMeshSettings : public UPCGSettings`  
_L24-47_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Renders a mesh terrain section into a texture by UV unwrap.
- L31 _public function_ `virtual FName GetDefaultNodeName() const override`
- L32 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L33 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L34 _public function_ `virtual EPCGSettingsType GetType() const override`
- L36 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L39 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L40 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L41 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L46 _public member_ `FPCGBakeMeshAttributesParams BakeParams;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### struct `UE::MeshPartition::FPCGBakeMeshTerrainSectionMeshContext`  
`struct FPCGBakeMeshTerrainSectionMeshContext : public FPCGContext`  
_L49-80_
- inherits: `FPCGContext`
- L52 _public prototype_ `virtual ~FPCGBakeMeshTerrainSectionMeshContext();`
- L55 _protected prototype_ `virtual void AddExtraStructReferencedObjects(FReferenceCollector& Collector) override;`
- L59 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — Static mesh of the section actor that we are rendering.
- L63 _public member_ `TObjectPtr<UPreviewMeshComponent> PreviewComponent;` — Set instead of StaticMesh when we fall back to the preview proxy path.
- L67 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — Render target the pass writes into.
- L70 _public member_ `TObjectPtr<UPCGRenderTargetData> OutputRenderTargetData;` — PCG-typed view of the render target produced as the node's output.
- L72 _public member_ `bool bSourceMeshSelected = false;`
- L73 _public member_ `bool bEnqueuedRenderCommand = false;`
- L76 _public member_ `bool bPinnedLOD0 = false;` — True once we have asked the streamer to force LOD0 resident for this static mesh.
- L79 _public member_ `bool bPrevForceMipsResident = false;` — Snapshot of bForceMiplevelsToBeResident captured before we set it. Restored when execution exits.

#### class `UE::MeshPartition::FPCGBakeMeshTerrainSectionMeshElement`  
`class FPCGBakeMeshTerrainSectionMeshElement : public IPCGElementWithCustomContext<FPCGBakeMeshTerrainSectionMeshContext>`  
_L82-90_
- inherits: `IPCGElementWithCustomContext<FPCGBakeMeshTerrainSectionMeshContext>`
- L85 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L86 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L89 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGGetMeshPartitionGrassTypes.h` (Private)


#### class `UE::MeshPartition::UPCGGetMeshPartitionGrassTypesSettings`  
`class UPCGGetMeshPartitionGrassTypesSettings : public UPCGSettings`  
_L20-55_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Emits an attribute set with the landscape grass types declared by a mesh partition definition's material.
- L27 _public function_ `virtual FName GetDefaultNodeName() const override`
- L28 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L29 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L30 _public function_ `virtual EPCGSettingsType GetType() const override`
- L34 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L35 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L36 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L42 _public member_ `TSoftObjectPtr<UMeshPartitionDefinition> Definition;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Mesh partition definition whose material is queried for landscape grass types.
- L46 _public member_ `FName GrassNameAttributeName = FName(TEXT("Gras` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Output attribute name for the material-side grass name (the FName key on the LandscapeGrassOutput input).
- L50 _public member_ `FName GrassTypeAttributeName = FName(TEXT("Gras` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Output attribute name for the soft object path to the ULandscapeGrassType asset.
- L54 _public member_ `bool bSynchronousLoad = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Debug")` — By default, the definition is loaded asynchronously; toggle to force synchronous load.

#### struct `UE::MeshPartition::FPCGGetMeshPartitionGrassTypesContext`  
`struct FPCGGetMeshPartitionGrassTypesContext : public FPCGContext, public IPCGAsyncLoadingContext`  
_L57-57_
- inherits: `FPCGContext,IPCGAsyncLoadingContext`

#### class `UE::MeshPartition::FPCGGetMeshPartitionGrassTypesElement`  
`class FPCGGetMeshPartitionGrassTypesElement : public IPCGElementWithCustomContext<FPCGGetMeshPartitionGrassTypesContext>`  
_L59-68_
- inherits: `IPCGElementWithCustomContext<FPCGGetMeshPartitionGrassTypesContext>`
- L62 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L63 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L66 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* InContext) const override;`
- L67 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGGetMeshPartitionTexelSizes.h` (Private)


#### class `UE::MeshPartition::UPCGGetMeshPartitionTexelSizesSettings`  
`class UPCGGetMeshPartitionTexelSizesSettings : public UPCGSettings`  
_L20-55_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Emits an attribute set with the channel textures and material cache texel sizes from a mesh partition definition.
- L27 _public function_ `virtual FName GetDefaultNodeName() const override`
- L28 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L29 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L30 _public function_ `virtual EPCGSettingsType GetType() const override`
- L34 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L35 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L36 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L42 _public member_ `TSoftObjectPtr<UMeshPartitionDefinition> Definition;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Mesh partition definition to read texel sizes from.
- L46 _public member_ `FName ChannelTexturesTexelSizeAttributeName = FName(TEXT("Chan` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Output attribute name for the channel textures texel size (in world units).
- L50 _public member_ `FName MaterialCacheTexelSizeAttributeName = FName(TEXT("Mate` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Output attribute name for the material cache texel size (in world units).
- L54 _public member_ `bool bSynchronousLoad = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Debug")` — By default, the definition is loaded asynchronously; toggle to force synchronous load.

#### struct `UE::MeshPartition::FPCGGetMeshPartitionTexelSizesContext`  
`struct FPCGGetMeshPartitionTexelSizesContext : public FPCGContext, public IPCGAsyncLoadingContext`  
_L57-57_
- inherits: `FPCGContext,IPCGAsyncLoadingContext`

#### class `UE::MeshPartition::FPCGGetMeshPartitionTexelSizesElement`  
`class FPCGGetMeshPartitionTexelSizesElement : public IPCGElementWithCustomContext<FPCGGetMeshPartitionTexelSizesContext>`  
_L59-68_
- inherits: `IPCGElementWithCustomContext<FPCGGetMeshPartitionTexelSizesContext>`
- L62 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L63 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L66 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* InContext) const override;`
- L67 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGGetMeshTerrainSection.h` (Private)


#### class `UE::MeshPartition::UPCGGetMeshTerrainSectionSettings`  
`class UPCGGetMeshTerrainSectionSettings : public UPCGSettings`  
_L16-35_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Emits one UPCGMeshTerrainSectionData per mesh terrain section that overlaps the generation volume.
- L23 _public function_ `virtual FName GetDefaultNodeName() const override`
- L24 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L25 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L26 _public function_ `virtual EPCGSettingsType GetType() const override`
- L27 _public function_ `virtual bool CanDynamicallyTrackKeys() const override`
- L31 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L32 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L33 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`

#### class `UE::MeshPartition::FPCGGetMeshTerrainSectionElement`  
`class FPCGGetMeshTerrainSectionElement : public IPCGElement`  
_L37-45_
- inherits: `IPCGElement`
- L40 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L41 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L44 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGGetMeshTerrainSectionActor.h` (Private)


#### class `UE::MeshPartition::UPCGGetMeshTerrainSectionActorSettings`  
`class UPCGGetMeshTerrainSectionActorSettings : public UPCGSettings`  
_L16-39_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Emits an attribute set with the soft object path to the actor of the given mesh terrain section.
- L23 _public function_ `virtual FName GetDefaultNodeName() const override`
- L24 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L25 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L26 _public function_ `virtual EPCGSettingsType GetType() const override`
- L30 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L31 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L32 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L38 _public member_ `FName OutputAttributeName = FName(TEXT("Acto` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings)` — Output attribute name for the section actor soft reference.

#### class `UE::MeshPartition::FPCGGetMeshTerrainSectionActorElement`  
`class FPCGGetMeshTerrainSectionActorElement : public IPCGElement`  
_L41-48_
- inherits: `IPCGElement`
- L44 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L47 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGGetMeshTerrainSectionChannelTextures.h` (Private)


#### class `UE::MeshPartition::UPCGGetMeshTerrainSectionChannelTexturesSettings`  
`class UPCGGetMeshTerrainSectionChannelTexturesSettings : public UPCGSettings`  
_L24-63_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Emits the input mesh terrain section's baked channel textures.
- L31 _public function_ `virtual FName GetDefaultNodeName() const override`
- L32 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L33 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L34 _public function_ `virtual EPCGSettingsType GetType() const override`
- L38 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L39 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L40 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L46 _public member_ `TArray<FName> SelectedChannels;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Channel names to operate on. Resolved against the parent mesh partition definition's channel list.
- L50 _public member_ `bool bExcludeSelectedChannels = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — When true, output every channel EXCEPT those in SelectedChannels. When false, output exactly SelectedChannels in user-given order.
- L54 _public member_ `bool bDropMissingChannels = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — When true, channels not present on this section are dropped from the output, making the output count vary by section. When false (default), missing channels are emitted as zero slices (or black textures in per-channel mode) so the output count and ordering stay stable across sections.
- L58 _public member_ `bool bOutputTextureArray = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Emit a single Texture 2D Array (true) or one Texture 2D per selected channel tagged with the channel name (false).
- L62 _public member_ `EPCGTextureFilter Filter = EPCGTextureFilter::Bilinear;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Filter mode applied when downstream nodes sample the emitted texture(s).

#### struct `UE::MeshPartition::FPCGGetMeshTerrainSectionChannelTexturesContext`  
`struct FPCGGetMeshTerrainSectionChannelTexturesContext : public FPCGContext`  
_L65-112_
- inherits: `FPCGContext`
- L68 _public prototype_ `virtual ~FPCGGetMeshTerrainSectionChannelTexturesContext();`
- L71 _protected prototype_ `virtual void AddExtraStructReferencedObjects(FReferenceCollector& Collector) override;`
- L75 _public member_ `TObjectPtr<UPCGTexture2DArrayData> OutputTextureArrayData = nullptr;` — Mode A: composited texture array
- L76 _public member_ `TRefCountPtr<IPooledRenderTarget> CompositedHandle;`
- L77 _public member_ `bool bRenderingComplete = false;`
- L80 _public member_ `TArray<TObjectPtr<UPCGTextureData>> OutputTextureDatas;` — Mode B: single texture per-channel
- L83 _public member_ `TArray<FName> EffectiveChannelNames;` — Resolved selection. Length is the output array size (or output texture count in mode B).
- L84 _public member_ `TArray<int32> EffectiveSliceIndices;` — -1 = absent on this section
- L86 _public member_ `TWeakObjectPtr<UTexture> SourceChannelTextureArray;`
- L87 _public member_ `TWeakObjectPtr<AActor> SectionActor;`
- L90 _public member_ `TObjectPtr<UTexture> BlackTexture;` — Per-channel mode fallback texture for absent channels.
- L93 _public member_ `bool bChannelsResolved = false;` — Effective channel/slice arrays populated.
- L96 _public member_ `bool bStreamingRequested = false;` — Source texture has requested streaming.
- L99 _public member_ `bool bPriorForceMipsResident = false;` — Snapshot of bForceMiplevelsToBeResident captured before we set it. Restored when execution exits.
- L102 _public member_ `bool bStreamingComplete = false;` — Source texture is fully streamed in.
- L105 _public member_ `double StreamingWaitStartTime = 0.0;` — Time the streaming wait began. Zero if no wait occurred.
- L108 _public member_ `bool bCompositeScheduled = false;` — RDG composite render command has been enqueued.
- L111 _public member_ `bool bUseFastPath = false;` — Source array maps 1:1 onto the output; skip the GPU composite.

#### class `UE::MeshPartition::FPCGGetMeshTerrainSectionChannelTexturesElement`  
`class FPCGGetMeshTerrainSectionChannelTexturesElement : public IPCGElementWithCustomContext<FPCGGetMeshTerrainSectionChannelTexturesContext>`  
_L114-122_
- inherits: `IPCGElementWithCustomContext<FPCGGetMeshTerrainSectionChannelTexturesContext>`
- L117 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L118 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L121 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGMeshPartitionModifierSpawnerElementBase.h` (Private)


#### class `TPCGMegaMeshModifierSpawnerElementBase`  
`template <typename SubclassOfIPCGElement> class TPCGMegaMeshModifierSpawnerElementBase : public SubclassOfIPCGElement`  
_L12-24_
- inherits: `SubclassOfIPCGElement`
- desc: Overrides functions that commonly need to be overriden on an element that will spawn a megamesh modifier via UE::MeshPartition::Utils::GetPCGManagedMegaMeshModifier.
- L16 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L20 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L23 _public function_ `virtual bool SupportsBasePointDataInputs(FPCGContext* InContext) const override`

#### Free symbols / members of external scopes

- L25 _typedef_ `using FPCGMegaMeshModifierSpawnerElementBase = TPCGMegaMeshModifierSpawnerElementBase<IPCGElement>;`

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGMeshPartitionPatchInstanceSpawner.h` (Private)


#### struct `UE::MeshPartition::FPCGPatchInstanceModifierSpawnerParams`  
`struct FPCGPatchInstanceModifierSpawnerParams`  
_L20-46_
- reflection: `USTRUCT(BlueprintType, Meta = (DisplayName = "Mesh Partition PCG Patch Instance Spawner Params"))`
- L25 _public member_ `float Radius = 150.f;` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L28 _public member_ `float Falloff = 150.f;` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L31 _public member_ `double Priority = 0.;` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L34 _public member_ `FName Type = TEXT("Pat` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L37 _public member_ `float MaxZDistance = 20000.f;` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L40 _public member_ `bool bWriteToWeightChannel = false;` — `UPROPERTY(EditAnywhere, Category=Patch)`
- L43 _public member_ `FName WeightChannelName;` — `UPROPERTY(EditAnywhere, Category=Patch, meta = (EditCondition="bWriteToWeightChannel", EditConditionHides))`
- L45 _public prototype_ `bool operator==(const MeshPartition::FPCGPatchInstanceModifierSpawnerParams& InOther) const;`

#### class `UE::MeshPartition::UPCGPatchInstanceSpawnerSettings`  
`class UPCGPatchInstanceSpawnerSettings : public UPCGSettings`  
_L49-69_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- L55 _public function_ `virtual FName GetDefaultNodeName() const override`
- L56 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L57 _public function_ `virtual EPCGSettingsType GetType() const override`
- L61 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L62 _protected function_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override`
- L63 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L68 _public member_ `MeshPartition::FPCGPatchInstanceModifierSpawnerParams SpawnerParams;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable, ShowOnlyInnerProperties))`

#### struct `UE::MeshPartition::PCGMegaMeshPatchInstanceSpawner::FExecutionContext`  
`struct FExecutionContext`  
_L73-80_
- L75 _public member_ `bool bSkipDueToReuse = false;`
- L76 _public member_ `bool bGenerateOutput = true;`
- L78 _public member_ `TWeakObjectPtr<MeshPartition::UInstancedPatchModifier> Modifier;`

#### struct `UE::MeshPartition::PCGMegaMeshPatchInstanceSpawner::FIterationContext`  
`struct FIterationContext`  
_L82-86_
- L84 _public member_ `AActor* TargetActor = nullptr;`
- L85 _public member_ `const UPCGBasePointData* PointData = nullptr;`

#### class `UE::MeshPartition::FPCGPatchInstanceSpawnerElement`  
`class FPCGPatchInstanceSpawnerElement : public TPCGMegaMeshModifierSpawnerElementBase<TPCGTimeSlicedElementBase< PCGMegaMeshPatchInstanceSpawner::FExecutionContext, PCGMegaMeshPatchInstanceSpawner::FIterationContext>>`  
_L89-96_
- inherits: `TPCGMegaMeshModifierSpawnerElementBase<TPCGTimeSlicedElementBase<PCGMegaMeshPatchInstanceSpawner::FExecutionContext,PCGMegaMeshPatchInstanceSpawner::FIterationContext>>`
- L93 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* Context) const override;`
- L94 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* Context) const override;`
- L95 _protected function_ `virtual EPCGElementExecutionLoopMode ExecutionLoopMode(const UPCGSettings* Settings) const override`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)
- L71 _namespace_ `namespace PCGMegaMeshPatchInstanceSpawner` (scope `UE::MeshPartition`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGMeshPartitionProjectionSpawner.h` (Private)


#### class `UE::MeshPartition::UPCGProjectionSpawnerSettings`  
`class UPCGProjectionSpawnerSettings : public UPCGSettings`  
_L29-76_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural), Meta = (DisplayName = "Mesh Partition PCG Projection Spawner Settings"))`
- inherits: `UPCGSettings`
- desc: Class that defines a PCG node for adding mesh projection modifier instances to a megamesh.
- L35 _public function_ `virtual FName GetDefaultNodeName() const override`
- L36 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L37 _public function_ `virtual EPCGSettingsType GetType() const override`
- L41 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L42 _protected function_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override`
- L43 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L49 _private member_ `double Priority = 0.;` — `UPROPERTY(EditAnywhere, Category = Modifier, Meta = (PCG_Overridable))`
- L52 _private member_ `FName Type = TEXT("Mes` — `UPROPERTY(EditAnywhere, Category = Modifier, Meta = (PCG_Overridable))`
- L55 _private member_ `TSoftObjectPtr<AMeshPartition> AffectedMegaMesh;` — `UPROPERTY(EditAnywhere, Category = Modifier, Meta = (PCG_Overridable))`
- L58 _private member_ `MeshPartition::EProjectModifierBlendMode BlendMode = MeshPartition::EProjectModifierBlendMode::Set;` — `UPROPERTY(EditAnywhere, Category = Modifier, Meta = (PCG_Overridable))`
- L61 _private member_ `MeshPartition::FProjectModifierFalloffSettings HeightFalloff;` — `UPROPERTY(EditAnywhere, Category = Height, Meta = (ShowOnlyInnerProperties))`
- L64 _private member_ `TArray<FProjectModifierWeightEntry> WeightChannels;` — `UPROPERTY(EditAnywhere, Category = Channels)`
- L73 _private member_ `FString CustomMeshTransformsAttribute = TEXT("Cus` — `UPROPERTY(EditAnywhere, Category = Modifier, AdvancedDisplay)` — By default, the mesh transforms are the same as the projection transform being used. However, the attribute with this name can be added to data in the InProjections pin to make meshes have a different transform from the projection. This allows for projecting in a direction that does not match the mesh Z axis, but could result in a projection missing the mesh entirely if the projection bounds don't intersect the mesh at that location.

#### struct `UE::MeshPartition::FPCGMegaMeshProjectionSpawner::FExecutionContext`  
`struct FExecutionContext`  
_L84-96_
- desc: Context that FPCGProjectionSpawnerElement prepares in PrepareDataInternal and holds across all time slice invocations in ExecuteInternal. This is const inside ExecuteSlice.
- L87 _public member_ `bool bNeedToFillOutputPin = false;` — Whether we need to copy our point inputs to the output pin
- L90 _public member_ `TWeakObjectPtr<MeshPartition::UInstancedProjectionModifier> ModifierComponent;`
- L94 _public member_ `TArray<const UPCGDynamicMeshData*> MeshInputs;` — We could unpack these each time inside ExecuteInternal, but might as well just carry them over.
- L95 _public member_ `TArray<const UPCGBasePointData*> ProjectionTransformInputs;`

#### struct `UE::MeshPartition::FPCGMegaMeshProjectionSpawner::FIterationContext`  
`struct FIterationContext`  
_L101-112_
- desc: Context held per top-level "iteration", which in this case is per input data object (i.e. bundle of points).
- L105 _public member_ `int32 NextPointIndexInData = 0;` — The next point inside our point data object to process. Updated while iterating so we can resume in the proper place if we time slice.
- L107 _public member_ `int32 NextMeshDataIndex = 0;` — Index of the next mesh to use while processing our point
- L110 _public member_ `TUniquePtr<const IPCGAttributeAccessor> TransformAccessor;` — Used to
- L111 _public member_ `TUniquePtr<const IPCGAttributeAccessorKeys> TransformKeys;`

#### class `UE::MeshPartition::FPCGProjectionSpawnerElement`  
`class FPCGProjectionSpawnerElement : public TPCGMegaMeshModifierSpawnerElementBase<TPCGTimeSlicedElementBase< MeshPartition::FPCGMegaMeshProjectionSpawner::FExecutionContext, MeshPartition::FPCGMegaMeshProjectionSpawner::FIterationContext>>`  
_L118-125_
- inherits: `TPCGMegaMeshModifierSpawnerElementBase<TPCGTimeSlicedElementBase<MeshPartition::FPCGMegaMeshProjectionSpawner::FExecutionContext,MeshPartition::FPCGMegaMeshProjectionSpawner::FIterationContext>>`
- desc: Class that actually performs spawning of mesh projection instances in PCG
- L122 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* Context) const override;`
- L123 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* Context) const override;`
- L124 _protected function_ `virtual EPCGElementExecutionLoopMode ExecutionLoopMode(const UPCGSettings* Settings) const override`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshPartition` (scope `UE`)
- L78 _namespace_ `namespace FPCGMegaMeshProjectionSpawner` (scope `UE::MeshPartition`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGMeshPartitionQuery.h` (Private)


#### class `UE::MeshPartition::UPCGQuerySettings`  
`class UPCGQuerySettings : public UPCGSettings`  
_L22-47_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural), Meta = (DisplayName = "Mesh Partition PCG Query Settings"))`
- inherits: `UPCGSettings`
- L28 _private function_ `virtual FName GetDefaultNodeName() const override`
- L29 _private function_ `virtual FText GetDefaultNodeTitle() const override`
- L30 _private prototype_ `virtual FText GetNodeTooltipText() const override;`
- L31 _private function_ `virtual EPCGSettingsType GetType() const override`
- L32 _private prototype_ `virtual void GetStaticTrackedKeys(FPCGSelectionKeyToSettingsMap& OutKeysToSettings, TArray<TObjectPtr<const UPCGGraph>>& OutVisitedGraphs) const override;`
- L33 _private function_ `virtual bool CanDynamicallyTrackKeys() const override`
- L34 _private prototype_ `virtual void ApplyDeprecationBeforeUpdatePins(UPCGNode* InOutNode, TArray<TObjectPtr<UPCGPin>>& InputPins, TArray<TObjectPtr<UPCGPin>>& OutputPins) override;`
- L38 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L39 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L41 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L46 _public member_ `MeshPartition::FPCGQueryParams QueryParams;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Data, meta = (PCG_Overridable, ShowOnlyInnerProperties))`

#### struct `UE::MeshPartition::FPCGMeshPartitionElementContext`  
`struct FPCGMeshPartitionElementContext : public FPCGContext`  
_L49-83_
- inherits: `FPCGContext`
- L66 _public member_ `TArray<FSectionData> SectionDatas;`
- L69 _public member_ `bool bSectionDataGathered = false;` — Used to keep track of our context initialization state (specifically, whether we've already kicked off SectionDatas work) if we take multiple slices to execute the node (due to the build taking time)
- L72 _public member_ `int32 NumFramesToWaitBeforeGathering = 1;` — @todo: It is possible for the Mesh Query to require a delay between spawning of modifiers and section gathering
- L76 _public member_ `TArray<TPair<int32, MeshPartition::FBuildTaskHandle>> PendingSectionTasks;` — If our builds of the mesh don't complete right away, holds handles to the ongoing tasks. The integer in the pair is an index into SectionDatas.
- L79 _public member_ `TObjectPtr<MeshPartition::UPCGMeshPartitionData> SurfaceData = nullptr;`
- L82 _protected prototype_ `virtual void AddExtraStructReferencedObjects(FReferenceCollector& Collector) override;`

#### struct `UE::MeshPartition::FPCGMeshPartitionElementContext::FSectionData`  
`struct FSectionData`  
_L51-64_
- L56 _public member_ `TWeakObjectPtr<MeshPartition::UPCGDataComponent> PCGData;`
- L58 _public member_ `TSharedPtr<const FMeshData> MeshData;`
- L59 _public member_ `TSharedPtr<const FMeshABBTree3> Spatial;`
- L60 _public member_ `FTransform MeshDataTransform = FTransform::Identity;`
- L63 _public member_ `TWeakObjectPtr<AMeshPartition> MegaMeshActor;` — Allows us to differentiate data coming from different MegaMeshes

#### class `UE::MeshPartition::FPCGMeshPartitionQueryElement`  
`class FPCGMeshPartitionQueryElement : public IPCGElement`  
_L85-94_
- inherits: `IPCGElement`
- L88 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L89 _public prototype_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* InContext) const override;`
- L91 _public function_ `virtual FPCGContext* CreateContext() override`
- L93 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGMeshPartitionSculptLayerWrite.h` (Private)


#### class `UE::MeshPartition::UPCGSculptLayerWriteSettings`  
`class UPCGSculptLayerWriteSettings : public UPCGSettings`  
_L38-122_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural), Meta = (DisplayName = "Mesh Partition PCG Layer Write Settings"))`
- inherits: `UPCGSettings`
- L45 _public function_ `virtual FName GetDefaultNodeName() const override`
- L46 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L47 _public function_ `virtual FText GetNodeTooltipText() const override`
- L52 _public function_ `virtual EPCGSettingsType GetType() const override`
- L56 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L57 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L58 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L66 _public member_ `FName Type = TEXT("Scu` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Type to use for the modifier that will be making modifications to the mesh
- L72 _public member_ `double Priority = 0.;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Priority for the modifier that will be making modifications to the mesh
- L76 _public member_ `TArray<FName> Channels;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Specifies which channels we will want to write. The points should have these as float attributes.
- L80 _public member_ `bool bSourcePositionIsAttribute = true;` — `UPROPERTY()`
- L86 _public member_ `FString SourcePositionsAttribute = TEXT("Sou` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (EditCondition = "bSourcePositionIsAttribute"))` — When the source positions are an attribute, the name of this attribute. It should be a FVector attribute.
- L92 _public member_ `bool bWritePositions = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When false, destination positions are not written (only channels are)
- L96 _public member_ `bool bDestinationPositionIsAttribute = false;` — `UPROPERTY()`
- L102 _public member_ `FString DestinationPositionsAttribute = TEXT("Des` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (EditCondition = "bDestinationPositionIsAttribute"))` — When the destination positions are an attribute, the name of this attribute. It should be a FVector attribute.
- L110 _public member_ `bool bConstrainToBounds = true;` — `UPROPERTY(EditAnywhere, Category = Settings, AdvancedDisplay)` — When true, any attempts to move points outside the bounds of the owning actor are clamped to the bounds of the actor. Disabling this will allow editing points outside your working PCG volume, but could cause huge modifier bounds if you accidentally try to write to nonsensical locations (such as using the wrong attribute accidentally).
- L118 _public member_ `bool bOnlyIncludeFullyModifiedTriangles = true;` — `UPROPERTY(EditAnywhere, Category = Settings, AdvancedDisplay)` — When creating the sculpt layer modifier, whether to only include triangles whose vertices were all written to, or triangles with any vertices written. Setting this to true can prevent unintentional 0's in weight channel application from unset vertices around the boundary, but would not include isolated written verts.
- L121 _public member_ `float MaxClosestPointDistance = 100;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### struct `UE::MeshPartition::FPCGSculptLayerWriteContext`  
`struct FPCGSculptLayerWriteContext : public FPCGContext`  
_L124-128_
- inherits: `FPCGContext`
- L126 _public member_ `TWeakObjectPtr<MeshPartition::UProjectMeshLayersModifier> ModifierComponent;`
- L127 _public member_ `bool bNeedToReinitialize = true;`

#### class `UE::MeshPartition::FPCGSculptLayerWriteElement`  
`class FPCGSculptLayerWriteElement : public FPCGMegaMeshModifierSpawnerElementBase`  
_L130-136_
- inherits: `FPCGMegaMeshModifierSpawnerElementBase`
- L133 _protected prototype_ `virtual FPCGContext* CreateContext() override;`
- L134 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* Context) const override;`
- L135 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* Context) const override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/Elements/PCGMeshPartitionWrite.h` (Private)


#### class `UE::MeshPartition::UPCGWriteSettings`  
`class UPCGWriteSettings : public UPCGSettings`  
_L22-97_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural), Meta = (DisplayName = "Mesh Partition PCG Write Settings"))`
- inherits: `UPCGSettings`
- L29 _public function_ `virtual FName GetDefaultNodeName() const override`
- L30 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L31 _public function_ `virtual FText GetNodeTooltipText() const override`
- L35 _public function_ `virtual EPCGSettingsType GetType() const override`
- L39 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L40 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L41 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L46 _public member_ `TSoftObjectPtr<AMeshPartition> AffectedMegaMesh;` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (PCG_Overridable))`
- L52 _public member_ `FName Type = TEXT("Sim` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Type to use for the modifier that will be making modifications to the mesh
- L58 _public member_ `double Priority = 0.;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Priority for the modifier that will be making modifications to the mesh
- L62 _public member_ `TArray<FName> Channels;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Specifies which channels we will want to write. The points should have these as float attributes.
- L66 _public member_ `bool bSourcePositionIsAttribute = true;` — `UPROPERTY()`
- L72 _public member_ `FString SourcePositionsAttribute = TEXT("Sou` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (EditCondition = "bSourcePositionIsAttribute"))` — When the source positions are an attribute, the name of this attribute. It should be a FVector attribute.
- L78 _public member_ `bool bWritePositions = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When false, destination positions are not written (only channels are)
- L82 _public member_ `bool bDestinationPositionIsAttribute = false;` — `UPROPERTY()`
- L88 _public member_ `FString DestinationPositionsAttribute = TEXT("Des` — `UPROPERTY(EditAnywhere, Category = Settings, Meta = (EditCondition = "bDestinationPositionIsAttribute"))` — When the destination positions are an attribute, the name of this attribute. It should be a FVector attribute.
- L96 _public member_ `bool bConstrainToBounds = true;` — `UPROPERTY(EditAnywhere, Category = Settings, AdvancedDisplay)` — When true, any attempts to move points outside the bounds of the owning actor are clamped to the bounds of the actor. Disabling this will allow editing points outside your working PCG volume, but could cause huge modifier bounds if you accidentally try to write to nonsensical locations (such as using the wrong attribute accidentally).

#### struct `UE::MeshPartition::FPCGMegaMeshWriteContext`  
`struct FPCGMegaMeshWriteContext : public FPCGContext`  
_L99-103_
- inherits: `FPCGContext`
- L101 _public member_ `TWeakObjectPtr<MeshPartition::USimpleWriteModifier> ModifierComponent;`
- L102 _public member_ `bool bNeedToReinitialize = true;`

#### class `UE::MeshPartition::FPCGWriteElement`  
`class FPCGWriteElement : public FPCGMegaMeshModifierSpawnerElementBase`  
_L105-111_
- inherits: `FPCGMegaMeshModifierSpawnerElementBase`
- L108 _protected prototype_ `virtual FPCGContext* CreateContext() override;`
- L109 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* Context) const override;`
- L110 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* Context) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/MeshPartitionPCGUtils.h` (Private)


#### struct `UE::MeshPartition::Utils::FGetPCGManagedMegaMeshModifierParams`  
`struct FGetPCGManagedMegaMeshModifierParams`  
_L29-39_
- desc: Param struct for GetPCGManagedMegaMeshModifier
- L32 _public member_ `FPCGContext* PCGContext = nullptr;` — Required parameters
- L33 _public member_ `const IPCGElement* Element = nullptr;`
- L36 _public member_ `AMeshPartition* MegaMesh = nullptr;` — Optional parameters: set common settings on a modifier
- L37 _public member_ `TOptional<FName> Layer;`
- L38 _public member_ `TOptional<double> Priority;`

#### struct `UE::MeshPartition::Utils::FGatherNewVertexDataFromPointDataInputParams`  
`struct FGatherNewVertexDataFromPointDataInputParams`  
_L55-62_
- L57 _public member_ `TArray<FPCGTaggedData> PointInputs;`
- L58 _public member_ `TArray<FName> ChannelsIn;`
- L59 _public member_ `TOptional<FString> SourcePositionsAttribute;`
- L60 _public member_ `TOptional<FString> DestPositionsAttribute;`
- L61 _public member_ `FPCGContext* ContextForLogging;`

#### class `UE::MeshPartition::UPCGManagedModifierResource`  
`class UPCGManagedModifierResource : public UPCGManagedComponent`  
_L88-121_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Meta = (DisplayName = "PCGManaged Mesh Partition Modifier Resource"))`
- inherits: `UPCGManagedComponent`
- desc: Wrapping class for a modifier managed by a pcg context, used internally by GetPCGManagedMegaMeshModifier().
- L95 _public function_ `template<typename ModifierComponentType> ModifierComponentType* GetComponent() const` — Helper for getting a cast version of the contained component
- L102 _public prototype_ `void Initialize(MeshPartition::UModifierComponent* InComponent, FPCGCrc SettingsCrc);`
- L104 _public function_ `FPCGCrc GetSettingsCrc() const`
- L107 _public function_ `virtual bool SupportsComponentReset() const override` — UPCGManagedComponent
- L108 _public prototype_ `virtual void ResetComponent() override;`
- L111 _public prototype_ `virtual bool Release(bool bHardRelease, TSet<TSoftObjectPtr<AActor>>& OutActorsToDelete) override;` — UPCGManagedResource
- L112 _public prototype_ `virtual void MarkAsUsed() override;`
- L113 _public prototype_ `virtual void MarkAsReused() override;`
- L114 _public prototype_ `virtual bool ReleaseIfUnused(TSet<TSoftObjectPtr<AActor>>& OutActorsToDelete) override;`
- L118 _private member_ `FPCGCrc SettingsCrc;` — `UPROPERTY()`
- L120 _private member_ `bool bSupportsComponentReset = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MeshPartition` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MeshPartition` (scope `UE`)
- L24 _namespace_ `namespace Utils` (scope `UE::MeshPartition`)
- L48 _function_ `template <typename ModifierClass> ModifierClass* GetPCGManagedMegaMeshModifier(FGetPCGManagedMegaMeshModifierParams& InParams, bool& bOutModifierWasReset)` (scope `UE::MeshPartition::Utils`) — Given the settings and element, uses the CRCs of inputs and settings to return a pcg-managed modifier that can be used by a pcg node. If the modifier does not implement IPCGReusableMegaMeshModifier, a new instance will always be created. If it does implement the interface, then an existing instance will be reused for any given settings CRC, and it will either be reset or returned as-is depending on whether the inputs CRC changed or didn't change, respectively.
- L52 _prototype_ `MeshPartition::UModifierComponent* GetPCGManagedMegaMeshModifier(TSubclassOf<MeshPartition::UModifierComponent> ModifierClass, FGetPCGManagedMegaMeshModifierParams& InParams, bool& bOutModifierWasReset);` (scope `UE::MeshPartition::Utils`)
- L66 _prototype_ `bool GatherNewVertexDataFromPointData( const FGatherNewVertexDataFromPointDataInputParams& InputParams, TArray<FVector3d>& SourcePositionsOut, TArray<FVector3d>* DestinationPositionsOut, TArray<TPair<FName, TArray<float>>>& WeightsOut);` (scope `UE::MeshPartition::Utils`) — Given pcg data that represents source and destination vertex positions and weights, unpack this data.
- L76 _prototype_ `AMeshPartition* FindClosestMegaMesh(const IPCGGraphExecutionSource& ExecutionSource);` (scope `UE::MeshPartition::Utils`) — Find MegaMesh whose bounds are closest to the execution source's bounds, or the first one whose bounds intersect the execution source bounds.
- L80 _namespace_ `namespace UE`
- L80 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/PCGManagedMeshPartitionInstancedProjectionModifier.h` (Private)


#### class `UE::MeshPartition::UPCGManagedInstancedProjectionModifier`  
`class UPCGManagedInstancedProjectionModifier : public UPCGManagedComponent`  
_L20-50_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPCGManagedComponent`
- desc: Class for managing a MeshPartition::UInstancedProjectionModifier spawned by a PCG node. Currently, each MeshPartition::UPCGProjectionSpawnerSettings node gets its own component. Once created, we can reuse the same component when rerunning the node by adjusting its settings and instances.
- L28 _public function_ `virtual bool SupportsComponentReset() const override` — UPCGManagedComponent
- L29 _public prototype_ `virtual void ResetComponent() override;`
- L32 _public prototype_ `virtual bool Release(bool bHardRelease, TSet<TSoftObjectPtr<AActor>>& OutActorsToDelete) override;` — UPCGManagedResource
- L33 _public prototype_ `virtual void MarkAsUsed() override;`
- L34 _public prototype_ `virtual void MarkAsReused() override;`
- L35 _public prototype_ `virtual bool ReleaseIfUnused(TSet<TSoftObjectPtr<AActor>>& OutActorsToDelete) override;`
- L37 _public prototype_ `MeshPartition::UInstancedProjectionModifier* GetComponent() const;`
- L38 _public prototype_ `void SetComponent(MeshPartition::UInstancedProjectionModifier* InComponent);`
- L40 _public function_ `uint64 GetSettingsUID() const`
- L41 _public function_ `void SetSettingsUID(uint64 InSettingsUID)`
- L49 _protected member_ `uint64 SettingsUID = -1;` — `UPROPERTY(Transient)` — Stores a unique identifier of MeshPartition::UPCGProjectionSpawnerSettings, to make sure that we don't try to reuse the same resource for another node.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Private/PCGManagedMeshPartitionPatchModifier.h` (Private)


#### struct `UE::MeshPartition::FPCGPatchInstanceModifierDescriptor`  
`struct FPCGPatchInstanceModifierDescriptor`  
_L15-44_
- reflection: `USTRUCT()`
- L19 _public prototype_ `FPCGPatchInstanceModifierDescriptor() = default;`
- L20 _public prototype_ `FPCGPatchInstanceModifierDescriptor(const FPCGPatchInstanceModifierSpawnerParams& InParams);`
- L23 _public member_ `float Radius = 1000.f;` — `UPROPERTY()`
- L26 _public member_ `float Falloff = 1000.f;` — `UPROPERTY()`
- L29 _public member_ `float MaxZDistance = 20000.f;` — `UPROPERTY()`
- L32 _public member_ `double Priority = 0.;` — `UPROPERTY()`
- L35 _public member_ `FName Type;` — `UPROPERTY()`
- L38 _public member_ `bool bWriteToWeightChannel = false;` — `UPROPERTY()`
- L41 _public member_ `FName WeightChannelName;` — `UPROPERTY()`
- L43 _public prototype_ `bool operator==(const FPCGPatchInstanceModifierDescriptor& InOther) const;`

#### class `UE::MeshPartition::UPCGManagedPatchModifier`  
`class UPCGManagedPatchModifier : public UPCGManagedComponent`  
_L47-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPCGManagedComponent`
- L52 _public prototype_ `virtual bool ReleaseIfUnused(TSet<TSoftObjectPtr<AActor>>& OutActorsToDelete) override;`
- L56 _public prototype_ `virtual void ResetComponent() override;`
- L57 _public function_ `virtual bool SupportsComponentReset() const override`
- L58 _public prototype_ `virtual void MarkAsReused() override;`
- L59 _public prototype_ `virtual void ForgetComponent() override;`
- L62 _public prototype_ `MeshPartition::UInstancedPatchModifier* GetComponent() const;`
- L63 _public prototype_ `void SetComponent(MeshPartition::UInstancedPatchModifier* InComponent);`
- L65 _public function_ `void SetDescriptorFromParams(const MeshPartition::FPCGPatchInstanceModifierSpawnerParams& InParams)`
- L66 _public function_ `const MeshPartition::FPCGPatchInstanceModifierDescriptor& GetDescriptor()`
- L68 _public function_ `uint64 GetSettingsUID() const`
- L69 _public function_ `void SetSettingsUID(uint64 InSettingsUID)`
- L73 _protected member_ `uint64 SettingsUID = -1;` — `UPROPERTY(Transient)` — purposefully a value that will never happen in data
- L76 _protected member_ `MeshPartition::FPCGPatchInstanceModifierDescriptor Descriptor;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Public/MeshPartitionPCGDataComponent.h` (Public)


#### class `UE::MeshPartition::UPCGDataComponent`  
`class UPCGDataComponent : public UActorComponent`  
_L20-51_
- reflection: `UCLASS(MinimalAPI, Meta = (DisplayName = "Mesh Partition PCG Data Component"))`
- inherits: `UActorComponent`
- desc: Caches mesh data required to sample a built mega mesh section quickly without performing conversions between mesh formats dynamically. #todo: This component is an intermediate step, we will eventually have a full caching system that will be able to store spatial trees and mesh data for layers in the procedural modifier stack.
- L25 _public prototype_ `UPCGDataComponent();`
- L28 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Implementation
- L29 _public prototype_ `virtual void PostLoad() override;`
- L33 _public prototype_ `virtual void OnUnregister() override;` — UActorComponent Implementation
- L36 _public function_ `TSharedPtr<const FMeshData> GetMesh() const`
- L38 _public prototype_ `void SetMesh(FMeshData&& InMesh);`
- L40 _public prototype_ `TSharedPtr<FMeshABBTree3> GetSpatial();`
- L42 _public function_ `Tasks::FTask GetSpatialBuildTask() const`
- L44 _protected prototype_ `void StartSpatialAsyncBuild();`
- L46 _protected member_ `TSharedPtr<FMeshData> Mesh;`
- L48 _protected member_ `TSharedPtr<FMeshABBTree3> Spatial;`
- L50 _protected member_ `Tasks::FTask AsyncSpatialBuild;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInterop/Public/PCGMeshPartitionInteropModule.h` (Public)


#### class `UE::MeshPartition::FPCGMegaMeshInteropModule`  
`class FPCGMegaMeshInteropModule final : public IModuleInterface`  
_L14-33_
- inherits: `IModuleInterface`
- L20 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L25 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L30 _private prototype_ `void OnPostEngineInit();`
- L31 _private prototype_ `void OnMegaMeshChanged(const UE::MeshPartition::FOnChangedEventInfo& ChangedEventInfo);`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGMegaMeshInterop, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGMegaMeshInterop, Log, All);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)
