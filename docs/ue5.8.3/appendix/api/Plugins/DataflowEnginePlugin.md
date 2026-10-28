# Plugins / DataflowEnginePlugin

- module root: `Plugins/Dataflow/Source/DataflowEnginePlugin`
- headers: 10; symbols: 145
- symbol kinds: class=5, delegate=1, enum=1, enumerator=5, function=23, macro=3, member=48, namespace=6, prototype=41, struct=10, typedef=2
- PrivateDependencyModuleNames: Chaos, DataflowCore, DataflowEngine, DynamicMesh, Engine, GeometryCore, RHI, RenderCore
- PublicDependencyModuleNames: Core, CoreUObject, GeometryFramework

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Private/Dataflow/DataflowEngineAnyTypes.h` (Private)


#### struct `FDataflowTypedArrayTypePolicy`  
`template<typename T> struct FDataflowTypedArrayTypePolicy : public TDataflowMultiTypePolicy<T, TArray<T>>`  
_L15-18_
- inherits: `TDataflowMultiTypePolicy<T,TArray<T>>`
- desc: todo : move this to general type policy file ?

#### struct `FDataflowDynamicMeshArray`  
`struct FDataflowDynamicMeshArray : public FDataflowAnyType`  
_L24-33_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Dynamic mesh array TArray with compatibility to plug one single element
- L26 _public typedef_ `using FPolicyType = FDataflowTypedArrayTypePolicy<TObjectPtr<UDynamicMesh>>;`
- L27 _public typedef_ `using FStorageType = TArray<TObjectPtr<UDynamicMesh>>;`
- L32 _public member_ `TArray<TObjectPtr<UDynamicMesh>> Value;` — `UPROPERTY(EditAnywhere, Category=Value)`

#### struct `FDataflowConverter`  
`template<> struct FDataflowConverter<TArray<TObjectPtr<UDynamicMesh>>>`  
_L38-67_
- L41 _public function_ `template <typename TFromType> static void From(const TFromType& From, TArray<TObjectPtr<UDynamicMesh>>& To)`
- L54 _public function_ `template <typename TToType> static void To(const TArray<TObjectPtr<UDynamicMesh>>& From, TToType& To)`

#### Free symbols / members of external scopes

- L69 _namespace_ `namespace UE`
- L69 _namespace_ `namespace Dataflow` (scope `UE`)
- L71 _prototype_ `void RegisterEngineAnyTypes();` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Private/Dataflow/DataflowEngineContextCaching.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Dataflow` (scope `UE`)
- L13 _prototype_ `void ContextCachingCallbacks();` (scope `UE::Dataflow`) — Rendering callbacks for the Dataflow Rendering Factory

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Private/Dataflow/DataflowEnginePlugin.h` (Private)


#### class `IDataflowEnginePlugin`  
`class IDataflowEnginePlugin : public IModuleInterface`  
_L13-43_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L18 _public member_ `static FColor VertexColor;`
- L19 _public member_ `static FColor SelectionPrimaryColor;`
- L20 _public member_ `static FColor SelectionLockedPrimaryColor;`
- L29 _public function_ `static inline IDataflowEnginePlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L39 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Private/Dataflow/DataflowEnginePluginPrivate.h` (Private)


#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("DataflowEnginePlugin"), STATGROUP_DataflowEnginePlugin`

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Private/Dataflow/DataflowEngineSceneProxy.h` (Private)


#### struct `FDataflowTriangleSetMeshBatchData`  
`struct FDataflowTriangleSetMeshBatchData`  
_L15-23_
- L17 _public member_ `int32 FirstTriangleIndex = INDEX_NONE;`
- L18 _public member_ `int32 NumTriangles = INDEX_NONE;`
- L19 _public member_ `int32 MinVertexIndex = INDEX_NONE;`
- L20 _public member_ `int32 MaxVertexIndex = INDEX_NONE;`
- L21 _public member_ `int32 GeomIndex = INDEX_NONE;`
- L22 _public member_ `FTransform MeshTransform = FTransform::Identity;`

#### struct `FDataflowVertexBatchData`  
`struct FDataflowVertexBatchData`  
_L25-32_
- L27 _public member_ `int32 FirstElementIndex = INDEX_NONE;`
- L28 _public member_ `int32 NumElements = INDEX_NONE;`
- L29 _public member_ `int32 MinVertexIndex = INDEX_NONE;`
- L30 _public member_ `int32 MaxVertexIndex = INDEX_NONE;`
- L31 _public member_ `int32 VertexIndex = INDEX_NONE;`

#### class `FDataflowEngineSceneProxy`  
`class FDataflowEngineSceneProxy final : public FPrimitiveSceneProxy`  
_L34-100_
- inherits: `FPrimitiveSceneProxy`
- L38 _public prototype_ `FDataflowEngineSceneProxy(UDataflowComponent* Component);`
- L39 _public prototype_ `virtual ~FDataflowEngineSceneProxy();`
- L42 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L43 _public prototype_ `virtual bool CanBeOccluded() const override;`
- L44 _public function_ `virtual uint32 GetMemoryFootprint() const override`
- L45 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L46 _public prototype_ `virtual void CreateRenderThreadResources(FRHICommandListBase& RHICmdList) override;`
- L47 _public prototype_ `virtual void DestroyRenderThreadResources() override;`
- L48 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L50 _public prototype_ `virtual HHitProxy* CreateHitProxies(UPrimitiveComponent* Component, TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L56 _private member_ `UDataflowComponent* DataflowComponent = nullptr;`
- L57 _private member_ `FManagedArrayCollection* ConstantData = nullptr;`
- L58 _private member_ `UMaterialInterface* RenderMaterial = nullptr;`
- L60 _private member_ `TArray<HHitProxy*> LocalHitProxies;`
- L62 _private prototype_ `UMaterialInterface* GetRenderMaterial() const;`
- L69 _private member_ `TArray<FDataflowTriangleSetMeshBatchData> MeshBatchDatas;`
- L70 _private member_ `FMaterialRelevance MaterialRelevance;`
- L71 _private member_ `FLocalVertexFactory VertexFactory;`
- L72 _private member_ `FStaticMeshVertexBuffers VertexBuffers;`
- L73 _private member_ `FDynamicMeshIndexBuffer32 IndexBuffer;`
- L76 _private prototype_ `void CreateMeshRenderThreadResources(FRHICommandListBase& RHICmdList);` — Create rendering resources for surface selection data.
- L78 _private prototype_ `void DestroyMeshRenderThreadResources();` — Destroy rendering resources for surface selection data.
- L80 _private prototype_ `void GetMeshDynamicMeshElements(int32 ViewIndex, FMeshElementCollector& Collector) const;` — Build MeshElements for rendering surface selection data.
- L87 _private member_ `int32 NumRenderedVerts = 0;`
- L88 _private member_ `TArray<FDataflowVertexBatchData> VertexBatchDatas;`
- L89 _private member_ `FLocalVertexFactory BoxVertexFactory;`
- L90 _private member_ `FStaticMeshVertexBuffers BoxVertexBuffers;`
- L91 _private member_ `FDynamicMeshIndexBuffer32 BoxIndexBuffer;`
- L94 _private prototype_ `void CreateInstancedVertexRenderThreadResources(FRHICommandListBase& RHICmdList);` — Create rendering resources for vertex selection data.
- L96 _private prototype_ `void DestroyInstancedVertexRenderThreadResources();` — Destroy rendering resources for vertex selection data.
- L98 _private prototype_ `void GetDynamicInstancedVertexMeshElements(int32 ViewIndex, FMeshElementCollector& Collector) const;` — Build MeshElements for rendering vertex selection data.

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Public/Dataflow/DataflowActor.h` (Public)


#### class `ADataflowActor`  
`class ADataflowActor : public AActor`  
_L17-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L25 _public member_ `TObjectPtr<UDataflowComponent> DataflowComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destruction, meta = (ExposeFunctionCategories = "Components|Dataflow", AllowPrivateAccess = "true"))` — DataflowComponent
- L26 _public function_ `UDataflowComponent* GetDataflowComponent() const`
- L30 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWENGINEPLUGIN_API`

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Public/Dataflow/DataflowComponent.h` (Public)


#### class `UDataflowComponent`  
`class UDataflowComponent : public UPrimitiveComponent`  
_L21-91_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))`
- inherits: `UPrimitiveComponent`
- desc: UDataflowComponent
- L27 _public prototype_ `virtual ~UDataflowComponent();`
- L29 _public prototype_ `void Invalidate();`
- L30 _public prototype_ `void UpdateLocalBounds();`
- L34 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L37 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L38 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 Index) const override;`
- L42 _public prototype_ `virtual FMaterialRelevance GetMaterialRelevance(ERHIFeatureLevel::Type InFeatureLevel) const;` — `UE_DEPRECATED(5.7, "Please use GetMaterialRelevance with EShaderPlatform argument and not ERHIFeatureLevel::Type")` — Rendering Support
- L43 _public prototype_ `virtual FMaterialRelevance GetMaterialRelevance(EShaderPlatform InShaderPlatform) const;`
- L44 _public prototype_ `UMaterialInterface* GetDefaultMaterial() const;`
- L47 _public prototype_ `void ResetRenderTargets();` — Render Targets
- L48 _public prototype_ `void AddRenderTarget(const UDataflowEdNode* InTarget);`
- L49 _public function_ `const TArray<const UDataflowEdNode*>& GetRenderTargets() const`
- L52 _public function_ `void SetContext(TSharedPtr<UE::Dataflow::FContext> InContext)` — Context
- L55 _public prototype_ `void SetRenderingCollection(FManagedArrayCollection&& InCollection);` — RenderCollection
- L56 _public prototype_ `const FManagedArrayCollection& GetRenderingCollection() const;`
- L57 _public prototype_ `FManagedArrayCollection& ModifyRenderingCollection();`
- L60 _public function_ `void SetDataflow(const UDataflow* InDataflow)` — Dataflow
- L61 _public function_ `const UDataflow* GetDataflow() const`
- L64 _public function_ `const FDataflowSelectionState& GetSelectionState() const` — Selection
- L65 _public function_ `void SetSelectionState(const FDataflowSelectionState& InState)`
- L74 _public function_ `void SetViewMode(const UE::Dataflow::IDataflowConstructionViewMode* InViewMode)` — NOTE: Currently UDataflowComponent is not used in the Dataflow Editor. Instead the FDataflowConstructionScene converts the FRenderingFacade to a UDynamicMeshComponent. If we do start using UDataflowComponent we will need to update the current View Mode as it's changed using this function.
- L80 _private member_ `TSharedPtr<UE::Dataflow::FContext> Context;`
- L81 _private member_ `TArray<const UDataflowEdNode*> RenderTargets;`
- L82 _private member_ `TObjectPtr< const UDataflow> Dataflow;`
- L83 _private member_ `FManagedArrayCollection RenderCollection;`
- L85 _private member_ `bool bUpdateRender = true;`
- L86 _private member_ `bool bUpdateSelection = true;`
- L87 _private member_ `bool bBoundsNeedsUpdate = true;`
- L88 _private member_ `FBoxSphereBounds BoundingBox = FBoxSphereBounds(ForceInitToZero);`
- L89 _private member_ `FDataflowSelectionState SelectionState = FDataflowSelectionState(FDataflowSelectionState::EMode::DSS_Dataflow_None);`
- L90 _private member_ `const UE::Dataflow::IDataflowConstructionViewMode* ViewMode;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWENGINEPLUGIN_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Public/Dataflow/DataflowComponentSelectionState.h` (Public)


#### class `FDataflowSelectionState`  
`class FDataflowSelectionState`  
_L11-59_
- L35 _public function_ `FDataflowSelectionState(EMode InMode) : Mode(InMode)`
- L36 _public function_ `FDataflowSelectionState(const UDataflowComponent* DataflowComponent)`
- L41 _public prototype_ `void UpdateSelection(UDataflowComponent* DataflowComponent);`
- L43 _public function_ `bool IsEmpty() const`
- L49 _public function_ `bool operator==(const FDataflowSelectionState& A) const`
- L52 _public function_ `bool operator!=(const FDataflowSelectionState& A) const`
- L56 _public member_ `EMode Mode;`
- L57 _public member_ `TArray<ObjectID> Nodes;`
- L58 _public member_ `TArray<int32> Vertices;`

#### struct `FDataflowSelectionState::ObjectID`  
`struct ObjectID`  
_L14-24_
- L16 _public function_ `ObjectID(FString InName, int32 InID) : Name(InName), ID(InID)`
- L18 _public function_ `bool operator==(const ObjectID& A) const`
- L22 _public member_ `FString Name;`
- L23 _public member_ `int32 ID;`

#### enum `FDataflowSelectionState::EMode`  
`enum EMode`  
_L26-33_
- L28 _public enumerator_ `DSS_Dataflow_None`
- L29 _public enumerator_ `DSS_Dataflow_Object`
- L30 _public enumerator_ `DSS_Dataflow_Face`
- L31 _public enumerator_ `DSS_Dataflow_Vertex`
- L32 _public enumerator_ `DSS_Dataflow_Max`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API DATAFLOWENGINEPLUGIN_API`

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Public/Dataflow/DataflowConnectionTypes.h` (Public)


#### struct `FCollectionAttributeKey`  
`struct FCollectionAttributeKey`  
_L10-24_
- reflection: `USTRUCT(BlueprintType)`
- L14 _public function_ `FCollectionAttributeKey() : Attribute(""), Group("")`
- L15 _public function_ `FCollectionAttributeKey(FString InAttribute, FString InGroup) : Attribute(InAttribute), Group(InGroup)`
- L17 _public function_ `TPair<FName, FName> GetNamedKey()`
- L20 _public member_ `FString Attribute;` — `UPROPERTY(EditAnywhere, Category = "Collection Key")`
- L23 _public member_ `FString Group;` — `UPROPERTY(EditAnywhere, Category = "Collection Key")`

### `Plugins/Dataflow/Source/DataflowEnginePlugin/Public/Dataflow/DataflowEngineSceneHitProxies.h` (Public)


#### struct `HDataflowDefault`  
`struct HDataflowDefault : public HActor`  
_L15-22_
- inherits: `HActor`
- desc: HitProxy with for dataflow actor.
- L19 _public prototype_ `HDataflowDefault(AActor* InActor, const UPrimitiveComponent* InPrimitiveComponent);`
- L21 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`

#### struct `HDataflowNode`  
`struct HDataflowNode : public HActor`  
_L27-37_
- inherits: `HActor`
- desc: HitProxy with for dataflow actor.
- L29 _public prototype_ `DECLARE_HIT_PROXY() int32 GeometryIndex = INDEX_NONE;`
- L32 _public member_ `FString NodeName = FString("");`
- L34 _public prototype_ `HDataflowNode(AActor* InActor, const UPrimitiveComponent* InPrimitiveComponent, FString InNodeName, int32 InGeometryIndex);`
- L36 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`

#### struct `HDataflowVertex`  
`struct HDataflowVertex : public HActor`  
_L42-49_
- inherits: `HActor`
- desc: HitProxy with for dataflow actor.
- L46 _public prototype_ `HDataflowVertex(AActor* InActor, const UPrimitiveComponent* InPrimitiveComponent, int32 InVertexIndex);`
- L48 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`
