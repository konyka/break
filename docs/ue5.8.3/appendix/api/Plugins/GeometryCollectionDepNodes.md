# Plugins / GeometryCollectionDepNodes

- module root: `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionDepNodes`
- headers: 4; symbols: 52
- symbol kinds: class=1, enum=3, enumerator=11, function=3, member=14, namespace=2, prototype=14, struct=3, typedef=1
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowEnginePlugin, Engine, GeometryCollectionEngine, GeometryCollectionNodes

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionDepNodes/Private/Dataflow/GeometryCollectionTransferVertexScalarAttributeDepNode.h` (Private)


#### enum `EDataflowTransferNodeFalloff`  
`enum class EDataflowTransferNodeFalloff : uint8`  
_L21-34_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Dataflow_Transfer_Squared UMETA(DisplayName = "Squared")` — Squared falloff based on distance from triangle
- L27 _public enumerator_ `Dataflow_Transfer_Linear UMETA(DisplayName = "Linear")` — Linear falloff based on distance from triangle
- L30 _public enumerator_ `Dataflow_Transfer_None UMETA(DisplayName = "None")` — No distance falloff
- L33 _public enumerator_ `Dataflow_Transfer_Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `EDataflowTransferNodeSampleScale`  
`enum class EDataflowTransferNodeSampleScale : uint8`  
_L37-51_
- reflection: `UENUM(BlueprintType)`
- L40 _public enumerator_ `Dataflow_Transfer_Component_Edge UMETA(DisplayName = "Component Max Edge")` — Bounding volume hierarchy cell size based on max edge length of each geometry group
- L43 _public enumerator_ `Dataflow_Transfer_Asset_Edge UMETA(DisplayName = "Asset Max Edge")` — Bounding volume hierarchy cell size based on max edge length of the whole asset
- L46 _public enumerator_ `Dataflow_Transfer_Asset_Bound UMETA(DisplayName = "Asset Max Bound")` — Bounding volume hierarchy cell size based on max length of the bounding box of the whole asset
- L50 _public enumerator_ `Dataflow_Transfer_Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `EDataflowTransferNodeBoundingVolume`  
`enum class EDataflowTransferNodeBoundingVolume : uint8`  
_L54-65_
- reflection: `UENUM(BlueprintType)`
- L57 _public enumerator_ `Dataflow_Transfer_Vertex UMETA(DisplayName = "Vertex")` — Bounding volume on vertices of the source triangle mesh
- L60 _public enumerator_ `Dataflow_Transfer_Triangle UMETA(DisplayName = "Triangle")` — Bounding volume on triangles of the source triangle mesh
- L64 _public enumerator_ `Dataflow_Transfer_Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FGeometryCollectionTransferVertexScalarAttributeNode`  
`struct FGeometryCollectionTransferVertexScalarAttributeNode : public FDataflowNode`  
_L71-146_
- reflection: `USTRUCT(meta = (Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Transfer float properties from a sample collection to a target collection.
- L81 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection"))` — Target collection to transfer vertex float attribute to.
- L85 _public member_ `FManagedArrayCollection FromCollection;` — `UPROPERTY(Meta = (DataflowInput, DisplayName = "FromCollection"))` — Sample collection to transfer vertex float attribute from.
- L89 _public member_ `FCollectionAttributeKey AttributeKey;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", Meta = (DataflowInput, DataflowOutput, DisplayName = "AttributeKey", DataflowPassthrough = "AttributeKey"))` — The name of the vertex attribute to generate indices from.
- L93 _public member_ `EDataflowTransferNodeBoundingVolume BoundingVolumeType = EDataflowTransferNodeBoundingVolume::Dataflow_Transfer_Triangle;` — `UPROPERTY(EditAnywhere, Category = "Thresholds")` — Bounding volume type for source assets[default: Triangle]
- L97 _public member_ `EDataflowTransferNodeSampleScale SampleScale = EDataflowTransferNodeSampleScale::Dataflow_Transfer_Asset_Bound;` — `UPROPERTY(EditAnywhere, Category = "Thresholds")` — Bounding volume hierarchy cell size for neighboring vertices to transfer into[default: Asset]
- L101 _public member_ `EDataflowTransferNodeFalloff Falloff = EDataflowTransferNodeFalloff::Dataflow_Transfer_Squared;` — `UPROPERTY(EditAnywhere, Category = "Thresholds")` — Falloff of sample value based on distance from sample triangle[default: Squared]
- L105 _public member_ `float FalloffThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds")` — Threshold based on distance from sample triangle.Values sampled past the threshold will falloff.[Defaults to 1 percent of triangle size(0.01)]
- L109 _public member_ `float EdgeMultiplier = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = (EditCondition = "SampleScale == EDataflowTransferNodeSampleScale::Dataflow_Transfer_Asset_Edge || SampleScale == EDataflowTransferNodeSampleScale::Dataflow_Transfer_Component_Edge", EditConditionHides))` — Edge multiplier for the Bounding Volume Hierarchy(BVH) target's particle search radius.
- L115 _public member_ `float BoundMultiplier = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = ( EditCondition = "SampleScale == EDataflowTransferNodeSampleScale::Dataflow_Transfer_Asset_Bound", EditConditionHides))` — Max bound multiplier for the Bounding Volume Hierarchy(BVH) target's particle search radius.
- L117 _public function_ `FGeometryCollectionTransferVertexScalarAttributeNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L130 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L136 _private prototype_ `TArray<FIntVector2> FindSourceToTargetGeometryMap(const FManagedArrayCollection& SourceCollection, const FManagedArrayCollection& TargetCollection) const;` — private helpers
- L137 _private prototype_ `void PairedGeometryTransfer(FCollectionAttributeKey Key, const TArray<FIntVector2>& PairedGeometry,const UE::Private::FTransferFacade& Sample, UE::Private::FTransferFacade& Target, TManagedArray<float>* TargetFloatArray) const;`
- L138 _private prototype_ `void NearestVertexTransfer(FCollectionAttributeKey Key, const UE::Private::FTransferFacade& Sample, UE::Private::FTransferFacade& Target, TManagedArray<float>* TargetFloatArray) const;`
- L139 _private prototype_ `static float MaxEdgeLength(TArray<FVector>& Vert, const TManagedArray<FIntVector3>& Tri, int VertexOFfset, int TriStart, int TriCount);`
- L140 _private prototype_ `static void BuildComponentSpaceVertices(const TManagedArray<FTransform3f>* LocalSpaceTransform, const TManagedArray<int32>* Parent, const TManagedArray<int32>* BoneMapArray, const TManagedArray<FVector3f>* VertexArray, int32 Start, int32 Count, TArray<FVector>& ComponentSpaceVertices);`
- L141 _private prototype_ `static UE::Private::BVH* BuildParticleSphereBVH(const TArray<FVector>& Vertices, float Radius);`
- L142 _private prototype_ `static bool TriangleHasWeightsToTransfer(const FIntVector3& T, const TManagedArray<float>& F);`
- L143 _private prototype_ `static void TriangleToVertexIntersections(UE::Private::BVH& VertexBVH, const TArray<FVector>& ComponentSpaceVertices, const FIntVector3& Triangle, TArray<int32>& OutTargetVertexIntersection);`
- L144 _private prototype_ `static float CalculateFalloffScale(EDataflowTransferNodeFalloff FalloffSetting, float Threshold, float Distance);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Private` (scope `UE`)
- L17 _typedef_ `typedef Chaos::TBoundingVolumeHierarchy<TArray<Chaos::FSphere*>, TArray<int32>, Chaos::FReal, 3> BVH;` (scope `UE::Private`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionDepNodes/Private/Dataflow/SetVertexColorFromFloatArrayDepNode.h` (Private)


#### struct `FSetVertexColorInCollectionFromFloatArrayDataflowNode`  
`struct FSetVertexColorInCollectionFromFloatArrayDataflowNode : public FDataflowNode`  
_L14-42_
- reflection: `USTRUCT(meta = (Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Set collection color based on input float array
- L26 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L30 _public member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Color")`
- L32 _public function_ `FSetVertexColorInCollectionFromFloatArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L40 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionDepNodes/Private/Dataflow/SetVertexColorFromVertexSelectionDepNode.h` (Private)


#### struct `FSetVertexColorInCollectionFromVertexSelectionDataflowNode`  
`struct FSetVertexColorInCollectionFromVertexSelectionDataflowNode : public FDataflowNode`  
_L14-46_
- reflection: `USTRUCT(meta = (Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Set the collections vertex color from the selection set.
- L26 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "VertexSelection", DataflowIntrinsic))`
- L30 _public member_ `FLinearColor SelectedColor = FLinearColor(FColor::Yellow);` — `UPROPERTY(EditAnywhere, Category = "Color")`
- L34 _public member_ `FLinearColor NonSelectedColor = FLinearColor(FColor::Blue);` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (DisplayName = "NonSelected Color"))`
- L36 _public function_ `FSetVertexColorInCollectionFromVertexSelectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L44 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionDepNodes/Public/Dataflow/GeometryCollectionDepNodesPlugin.h` (Public)


#### class `IGeometryCollectionDepNodesPlugin`  
`class IGeometryCollectionDepNodesPlugin : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
