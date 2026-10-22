# Plugins / GeometryCollectionNodes

- module root: `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes`
- headers: 41; symbols: 3770
- symbol kinds: class=1, enum=54, enumerator=286, function=268, member=2003, namespace=96, prototype=654, struct=400, typedef=6, variable=2
- PrivateDependencyModuleNames: DataflowEditor, DynamicMesh, FractureEngine, GeometryAlgorithms, MeshConversion, MeshConversionEngineTypes, ModelingComponentsEditorOnly, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, UnrealEd
- PublicDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowEnginePlugin, DataflowMedialSkeleton, DataflowNodes, Engine, GeometryCollectionEngine, GeometryCore, GeometryDataflowNodes, GeometryFramework, MeshDescription, PlanarCut, StaticMeshDescription, Voronoi

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Private/Dataflow/GeometryCollectionRemoveMeshOverlapsNode.h` (Private)


#### enum `EDataflowRemoveOverlapsMeshSortOrder`  
`enum class EDataflowRemoveOverlapsMeshSortOrder`  
_L14-24_
- reflection: `UENUM()`
- desc: The mesh ordering for used when removing overlaps
- L17 _public enumerator_ `IncreasingVolume` — Process in order of increasing volume; largest is unchanged
- L19 _public enumerator_ `DecreasingVolume` — Process in order of decreasing volume; smallest is unchanged
- L21 _public enumerator_ `InputOrder` — Process in input ordering; last mesh is unchanged
- L23 _public enumerator_ `ReverseInputOrder` — Process in the reverse of the input ordering; first mesh is unchanged

#### struct `FRemoveMeshOverlapsDataflowNode`  
`struct FRemoveMeshOverlapsDataflowNode : public FDataflowNode`  
_L31-58_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Cut away any overlaps between input meshes, creating a set of non-overlapping meshes as output For example, given meshes w/ order [A, B, C], non-overlapping meshes will be [(A-B)-C, B-C, C]
- L41 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L45 _private member_ `TArray<TObjectPtr<UDynamicMesh>> DynamicMeshes;` — `UPROPERTY(EditAnywhere, Category = "Meshes", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "DynamicMeshes", DataflowIntrinsic))` — Dynamic Meshes to remove overlaps from
- L49 _private member_ `TArray<FTransform> PerMeshTransforms;` — `UPROPERTY(EditAnywhere, Category = "Meshes", meta = (DataflowInput))` — Optional transforms for input meshes. Will be baked into output. If not provided, meshes will not be transformed.
- L53 _private member_ `EDataflowRemoveOverlapsMeshSortOrder SubtractOrder = EDataflowRemoveOverlapsMeshSortOrder::InputOrder;` — `UPROPERTY(EditAnywhere, Category = "Ordering")` — Ordering to use when applying subtraction operations. Later meshes will be subtracted from earlier meshes in the ordering.
- L57 _private member_ `bool bSimplifyNewMeshEdges = true;` — `UPROPERTY(EditAnywhere, Category = "Boolean")` — Whether to simplify along new edges created by the mesh subtraction operations

#### Free symbols / members of external scopes

- L60 _namespace_ `namespace UE`
- L60 _namespace_ `namespace Dataflow` (scope `UE`)
- L62 _prototype_ `void GeometryCollectionRemoveMeshOverlapsNode();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Private/Dataflow/MeshMedialSkeletonConversionNodes.h` (Private)


#### enum `EDataflowMedialSkeletonConversionEdgeWeightMethod`  
`enum class EDataflowMedialSkeletonConversionEdgeWeightMethod : uint8`  
_L16-24_
- reflection: `UENUM()`
- L19 _public enumerator_ `EdgeLength` — Favor adding shorter edges first. (Note: Typically not desirable for an animation skeleton.)
- L21 _public enumerator_ `ArrayOrder` — Favor edges between clusters that are earlier in the medial skeleton array. Because medial spheres are added incrementally in the highest error locations, their order can approximate importance.
- L23 _public enumerator_ `AvgRadius` — Favor adding edges between larger medial spheres first

#### enum `EDataflowMedialSkeletonConversionMergeDisconnectedMethod`  
`enum class EDataflowMedialSkeletonConversionMergeDisconnectedMethod : uint8`  
_L27-33_
- reflection: `UENUM()`
- L30 _public enumerator_ `ConnectClosestBones` — For disconnected components, connect the closest pair of nodes in each disconnected component and the root component
- L32 _public enumerator_ `AddTopLevelRoot` — Add a top-level root node, and connect the selected root and all disconnected components to this node

#### enum `EDataflowMedialSkeletonConversionSelectRootMethod`  
`enum class EDataflowMedialSkeletonConversionSelectRootMethod : uint8`  
_L36-48_
- reflection: `UENUM()`
- L39 _public enumerator_ `ClosestToPoint` — Select the cluster closest to the RootSelectionPoint
- L41 _public enumerator_ `FarthestInDirection` — Select the cluster farthest in the RootSelectionDirection
- L43 _public enumerator_ `ClosestToBoundsCenter` — Select the cluster closest to the bounding box center of the medial skeleton
- L45 _public enumerator_ `LargestSphere` — Select the cluster with the largest medial sphere radius
- L47 _public enumerator_ `ArrayOrder` — Select the first cluster (index 0)

#### enum `EDataflowBindSkeletonMethod`  
`enum class EDataflowBindSkeletonMethod : uint8`  
_L51-61_
- reflection: `UENUM()`
- L56 _public enumerator_ `DirectDistance = 0` — Computes the binding strength by computing the Euclidean distance to the closest set of bones, where the strength of binding is proportional to the inverse distance. May cause bones to affects parts of geometry that, although close in space, may be topologically distant.
- L60 _public enumerator_ `GeodesicVoxel = 1` — Computes the binding by computing the geodesic distance from each set of bones. This is slower than the direct distance.

#### struct `FConvertMedialSkeletonToAnimationSkeletonDataflowNode`  
`struct FConvertMedialSkeletonToAnimationSkeletonDataflowNode : public FDataflowNode`  
_L68-121_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: FConvertMedialSkeletonToAnimationSkeletonDataflowNode DEPRECATED 5.8 - use FConvertMedialSkeletonToAnimationSkeletonDataflowNode_v2 instead
- L81 _public member_ `TObjectPtr<const UDynamicMesh> AvoidIntersectingMesh;` — `UPROPERTY(meta = (DataflowInput))` — If provided, edges not intersecting this mesh will be preferred for inclusion in the skeleton
- L84 _public member_ `FDataflowSkeleton Skeleton;` — `UPROPERTY(meta = (DataflowOutput))`
- L87 _public member_ `EDataflowMedialSkeletonConversionEdgeWeightMethod EdgeWeightMethod = EDataflowMedialSkeletonConversionEdgeWeightMethod::ArrayOrder;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L90 _public member_ `EDataflowMedialSkeletonConversionMergeDisconnectedMethod MergeDisconnectedMethod = EDataflowMedialSkeletonConversionMergeDisconnectedMethod::ConnectClosestBones;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L94 _public member_ `EDataflowMedialSkeletonConversionSelectRootMethod SelectRootMethod = EDataflowMedialSkeletonConversionSelectRootMethod::ArrayOrder;` — `UPROPERTY(EditAnywhere, Category = "Options")` — Method to automatically select the root cluster when RootClusterIndex is not specified
- L98 _public member_ `FVector RootSelectionPoint = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "SelectRootMethod == EDataflowMedialSkeletonConversionSelectRootMethod::ClosestToPoint"))` — When SelectRootMethod is ClosestToPoint, find the closest cluster to this point
- L102 _public member_ `FVector RootSelectionDirection = FVector(0, 0, -1);` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "SelectRootMethod == EDataflowMedialSkeletonConversionSelectRootMethod::FarthestInDirection"))` — When SelectRootMethod is FarthestInDirection, the direction to search along
- L106 _public member_ `int32 RootClusterIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — If non-negative, the index of the medial axis cluster (sphere) to use as the root of the Skeleton
- L110 _public member_ `bool bAddCustomAnimationRoot = false;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — If true, add an extra root bone at CustomAnimationRootPosition, unrelated to any medial skeleton cluster
- L114 _public member_ `FVector CustomAnimationRootPosition = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "bAddCustomAnimationRoot"))` — The world-space position for the custom root bone. Only used when bAddCustomAnimationRoot is true.
- L116 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L120 _public prototype_ `FConvertMedialSkeletonToAnimationSkeletonDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertMedialSkeletonToAnimationSkeletonDataflowNode_v2`  
`struct FConvertMedialSkeletonToAnimationSkeletonDataflowNode_v2 : public FDataflowNode`  
_L124-177_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L133 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Medial skeleton of input mesh
- L137 _private member_ `TObjectPtr<const UDataflowMesh> AvoidIntersectingMesh;` — `UPROPERTY(meta = (DataflowInput))` — If provided, edges not intersecting this mesh will be preferred for inclusion in the skeleton
- L140 _private member_ `FDataflowSkeleton Skeleton;` — `UPROPERTY(meta = (DataflowOutput))`
- L143 _private member_ `EDataflowMedialSkeletonConversionEdgeWeightMethod EdgeWeightMethod = EDataflowMedialSkeletonConversionEdgeWeightMethod::ArrayOrder;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L146 _private member_ `EDataflowMedialSkeletonConversionMergeDisconnectedMethod MergeDisconnectedMethod = EDataflowMedialSkeletonConversionMergeDisconnectedMethod::ConnectClosestBones;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L150 _private member_ `EDataflowMedialSkeletonConversionSelectRootMethod SelectRootMethod = EDataflowMedialSkeletonConversionSelectRootMethod::ArrayOrder;` — `UPROPERTY(EditAnywhere, Category = "Options")` — Method to automatically select the root cluster when RootClusterIndex is not specified
- L154 _private member_ `FVector RootSelectionPoint = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "SelectRootMethod == EDataflowMedialSkeletonConversionSelectRootMethod::ClosestToPoint"))` — When SelectRootMethod is ClosestToPoint, find the closest cluster to this point
- L158 _private member_ `FVector RootSelectionDirection = FVector(0, 0, -1);` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "SelectRootMethod == EDataflowMedialSkeletonConversionSelectRootMethod::FarthestInDirection"))` — When SelectRootMethod is FarthestInDirection, the direction to search along
- L162 _private member_ `int32 RootClusterIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — If non-negative, the index of the medial axis cluster (sphere) to use as the root of the Skeleton
- L166 _private member_ `bool bAddCustomAnimationRoot = false;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — If true, add an extra root bone at CustomAnimationRootPosition, unrelated to any medial skeleton cluster
- L170 _private member_ `FVector CustomAnimationRootPosition = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "bAddCustomAnimationRoot"))` — The world-space position for the custom root bone. Only used when bAddCustomAnimationRoot is true.
- L172 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L176 _public prototype_ `FConvertMedialSkeletonToAnimationSkeletonDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FBindSkeletonToMeshDataflowNode`  
`struct FBindSkeletonToMeshDataflowNode : public FDataflowNode`  
_L184-219_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: FBindSkeletonToMeshDataflowNode DEPRECATED 5.8 - use FBindSkeletonToMeshDataflowNode_v2 instead
- L193 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic, DataflowPassthrough = "Mesh"))` — Mesh to add an animation skeleton to
- L196 _private member_ `FDataflowSkeleton Skeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L200 _private member_ `EDataflowBindSkeletonMethod BindMethod = EDataflowBindSkeletonMethod::DirectDistance;` — `UPROPERTY(EditAnywhere, Category = "Options")` — Binding method to use
- L204 _private member_ `float Stiffness = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, ClampMin=0, ClampMax=1))` — Stiffness of binding. Lower values allow more distant bones to contribute more
- L208 _private member_ `int32 MaxInfluences = 5;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, ClampMin = 1, UIMax = 10))` — Maximum bones that will influence each vertex
- L212 _private member_ `int32 VoxelResolution = 256;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, ClampMin =1, UIMin = 8, ClampMax = 1024))` — The resolution of the voxel grid if doing geodesic voxel binding
- L214 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L218 _public prototype_ `FBindSkeletonToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FBindSkeletonToMeshDataflowNode_v2`  
`struct FBindSkeletonToMeshDataflowNode_v2 : public FDataflowNode`  
_L222-257_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L231 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic, DataflowPassthrough = "Mesh"))` — Mesh to add an animation skeleton to
- L234 _private member_ `FDataflowSkeleton Skeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L238 _private member_ `EDataflowBindSkeletonMethod BindMethod = EDataflowBindSkeletonMethod::DirectDistance;` — `UPROPERTY(EditAnywhere, Category = "Options")` — Binding method to use
- L242 _private member_ `float Stiffness = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, ClampMin = 0, ClampMax = 1))` — Stiffness of binding. Lower values allow more distant bones to contribute more
- L246 _private member_ `int32 MaxInfluences = 5;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, ClampMin = 1, UIMax = 10))` — Maximum bones that will influence each vertex
- L250 _private member_ `int32 VoxelResolution = 256;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, ClampMin = 1, UIMin = 8, ClampMax = 1024))` — The resolution of the voxel grid if doing geodesic voxel binding
- L252 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L256 _public prototype_ `FBindSkeletonToMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSkinMeshViaMedialSkeleton`  
`struct FSkinMeshViaMedialSkeleton : public FDataflowNode`  
_L264-337_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: FSkinMeshViaMedialSkeleton DEPRECATED 5.8 - use FSkinMeshViaMedialSkeleton_v2 instead
- L272 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic, DataflowPassthrough = "Mesh"))` — Mesh to add an animation skeleton to
- L276 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Medial skeleton of input mesh
- L279 _private member_ `EDataflowMedialSkeletonConversionEdgeWeightMethod EdgeWeightMethod = EDataflowMedialSkeletonConversionEdgeWeightMethod::ArrayOrder;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L282 _private member_ `EDataflowMedialSkeletonConversionMergeDisconnectedMethod MergeDisconnectedMethod = EDataflowMedialSkeletonConversionMergeDisconnectedMethod::ConnectClosestBones;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L286 _private member_ `EDataflowMedialSkeletonConversionSelectRootMethod SelectRootMethod = EDataflowMedialSkeletonConversionSelectRootMethod::ArrayOrder;` — `UPROPERTY(EditAnywhere, Category = "Options")` — Method to automatically select the root cluster when RootClusterIndex is not specified
- L290 _private member_ `FVector RootSelectionPoint = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "SelectRootMethod == EDataflowMedialSkeletonConversionSelectRootMethod::ClosestToPoint"))` — When SelectRootMethod is ClosestToPoint, find the closest cluster to this point
- L294 _private member_ `FVector RootSelectionDirection = FVector(0, 0, -1);` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "SelectRootMethod == EDataflowMedialSkeletonConversionSelectRootMethod::FarthestInDirection"))` — When SelectRootMethod is FarthestInDirection, the direction to search along
- L298 _private member_ `int32 RootClusterIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — If non-negative, the index of the medial axis cluster (sphere) to use as the root of the Skeleton
- L302 _private member_ `bool bAddCustomAnimationRoot = false;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — If true, add an extra root bone at CustomAnimationRootPosition. In constrained binding, this bone will not receive skin weights from clustered vertices.
- L306 _private member_ `FVector CustomAnimationRootPosition = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "bAddCustomAnimationRoot"))` — The world-space position for the custom root bone. Only used when bAddCustomAnimationRoot is true.
- L310 _private member_ `EDataflowBindSkeletonMethod BindMethod = EDataflowBindSkeletonMethod::DirectDistance;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — Binding method to use for skin weights
- L314 _private member_ `float Stiffness = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (DataflowInput, ClampMin=0, ClampMax=1))` — Stiffness of binding. Lower values allow more distant bones to contribute more
- L318 _private member_ `int32 MaxInfluences = 5;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (DataflowInput, ClampMin = 1, UIMax = 10))` — Maximum bones that will influence each vertex
- L322 _private member_ `int32 VoxelResolution = 256;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (DataflowInput, ClampMin = 1, UIMin = 8, ClampMax = 1024))` — The resolution of the voxel grid if doing geodesic voxel binding
- L330 _private member_ `int32 ClusterNeighborSearchRange = 1;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (DataflowInput, ClampMin = 1, UIMax = 5, ClampMax = 100))` — How far to search through medial skeleton neighbors when building bone groups for constrained skin binding. 1 = immediate neighbors only, 2 = neighbors of neighbors, etc. Higher values allow smoother blending across more bones but reduce locality.
- L332 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L336 _public prototype_ `FSkinMeshViaMedialSkeleton(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSkinMeshViaMedialSkeleton_v2`  
`struct FSkinMeshViaMedialSkeleton_v2 : public FDataflowNode`  
_L340-413_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L348 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic, DataflowPassthrough = "Mesh"))` — Mesh to add an animation skeleton to
- L352 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Medial skeleton of input mesh
- L355 _private member_ `EDataflowMedialSkeletonConversionEdgeWeightMethod EdgeWeightMethod = EDataflowMedialSkeletonConversionEdgeWeightMethod::ArrayOrder;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L358 _private member_ `EDataflowMedialSkeletonConversionMergeDisconnectedMethod MergeDisconnectedMethod = EDataflowMedialSkeletonConversionMergeDisconnectedMethod::ConnectClosestBones;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L362 _private member_ `EDataflowMedialSkeletonConversionSelectRootMethod SelectRootMethod = EDataflowMedialSkeletonConversionSelectRootMethod::ArrayOrder;` — `UPROPERTY(EditAnywhere, Category = "Options")` — Method to automatically select the root cluster when RootClusterIndex is not specified
- L366 _private member_ `FVector RootSelectionPoint = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "SelectRootMethod == EDataflowMedialSkeletonConversionSelectRootMethod::ClosestToPoint"))` — When SelectRootMethod is ClosestToPoint, find the closest cluster to this point
- L370 _private member_ `FVector RootSelectionDirection = FVector(0, 0, -1);` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "SelectRootMethod == EDataflowMedialSkeletonConversionSelectRootMethod::FarthestInDirection"))` — When SelectRootMethod is FarthestInDirection, the direction to search along
- L374 _private member_ `int32 RootClusterIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — If non-negative, the index of the medial axis cluster (sphere) to use as the root of the Skeleton
- L378 _private member_ `bool bAddCustomAnimationRoot = false;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — If true, add an extra root bone at CustomAnimationRootPosition. In constrained binding, this bone will not receive skin weights from clustered vertices.
- L382 _private member_ `FVector CustomAnimationRootPosition = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, EditCondition = "bAddCustomAnimationRoot"))` — The world-space position for the custom root bone. Only used when bAddCustomAnimationRoot is true.
- L386 _private member_ `EDataflowBindSkeletonMethod BindMethod = EDataflowBindSkeletonMethod::DirectDistance;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — Binding method to use for skin weights
- L390 _private member_ `float Stiffness = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (DataflowInput, ClampMin = 0, ClampMax = 1))` — Stiffness of binding. Lower values allow more distant bones to contribute more
- L394 _private member_ `int32 MaxInfluences = 5;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (DataflowInput, ClampMin = 1, UIMax = 10))` — Maximum bones that will influence each vertex
- L398 _private member_ `int32 VoxelResolution = 256;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (DataflowInput, ClampMin = 1, UIMin = 8, ClampMax = 1024))` — The resolution of the voxel grid if doing geodesic voxel binding
- L406 _private member_ `int32 ClusterNeighborSearchRange = 1;` — `UPROPERTY(EditAnywhere, Category = "Binding", meta = (DataflowInput, ClampMin = 1, UIMax = 5, ClampMax = 100))` — How far to search through medial skeleton neighbors when building bone groups for constrained skin binding. 1 = immediate neighbors only, 2 = neighbors of neighbors, etc. Higher values allow smoother blending across more bones but reduce locality.
- L408 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L412 _public prototype_ `FSkinMeshViaMedialSkeleton_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L415 _namespace_ `namespace UE`
- L415 _namespace_ `namespace Dataflow` (scope `UE`)
- L417 _prototype_ `void RegisterMeshMedialSkeletonConversionNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Private/Dataflow/MeshToSkeletalMeshTerminalNode.h` (Private)


#### struct `FMeshToSkeletalMeshTerminalNode`  
`struct FMeshToSkeletalMeshTerminalNode : public FDataflowTerminalNode`  
_L22-63_
- reflection: `USTRUCT(meta = (DataflowTerminal, Icon = "Icons.SkeletalMesh", Deprecated = "5.8"))`
- inherits: `FDataflowTerminalNode`
- desc: Terminal node to a save a skeletal mesh asset, as converted from a dynamic mesh. Note the mesh must have associated skeletal mesh attributes. The terminal node will create an asset if it does not exist yet
- L34 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowInput))` — Materials to use on the skeletal mesh
- L39 _public member_ `FString SkeletalMeshAssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path to the skeletal mesh asset to create or update
- L43 _public member_ `FString SkeletonAssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path to the skeleton asset to create or update
- L47 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Created Skeletal Mesh
- L51 _public member_ `TObjectPtr<USkeleton> SkeletonAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Created Skeleton
- L53 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L54 _public prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L57 _public prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L58 _public prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L62 _public prototype_ `FMeshToSkeletalMeshTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMeshToSkeletalMeshTerminalNode_v2`  
`struct FMeshToSkeletalMeshTerminalNode_v2 : public FDataflowTerminalNode`  
_L71-107_
- reflection: `USTRUCT(meta = (DataflowTerminal, Icon = "Icons.SkeletalMesh"))`
- inherits: `FDataflowTerminalNode`
- desc: Terminal node to save a skeletal mesh asset, as converted from a Dataflow mesh. The mesh must carry skeletal mesh attributes (bones). The terminal node will create the asset if it does not already exist.
- L79 _private member_ `TObjectPtr<const UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Surface mesh to convert (carries materials inline)
- L83 _private member_ `FString SkeletalMeshAssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path to the skeletal mesh asset to create or update
- L87 _private member_ `FString SkeletonAssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path to the skeleton asset to create or update
- L91 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMeshAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Created Skeletal Mesh
- L95 _private member_ `TObjectPtr<USkeleton> SkeletonAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Created Skeleton
- L97 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L98 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L101 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L102 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L106 _public prototype_ `FMeshToSkeletalMeshTerminalNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSkeletalMeshTerminalNode`  
`struct FSkeletalMeshTerminalNode : public FDataflowTerminalNode`  
_L114-142_
- reflection: `USTRUCT(meta = (DataflowTerminal, Experimental, Icon = "Icons.SkeletalMesh"))`
- inherits: `FDataflowTerminalNode`
- desc: Terminal to save to skeletal mesh from a mesh Note : the mesh must have associated skeletal mesh attributes and vbones must be compatible with the existing skeleton
- L122 _private member_ `TObjectPtr<const UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Surface mesh to convert
- L126 _private member_ `FString AssetPath;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))` — Path to the skeletal mesh asset to create or update
- L130 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMeshAsset = nullptr;` — `UPROPERTY(meta = (DataflowOutput))` — Created Skeletal Mesh
- L132 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L133 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L141 _public prototype_ `FSkeletalMeshTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L144 _namespace_ `namespace UE`
- L144 _namespace_ `namespace Dataflow` (scope `UE`)
- L146 _prototype_ `void RegisterMeshToSkeletalMeshTerminalNode();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Private/Dataflow/MeshWeightEditingNodes.h` (Private)


#### struct `FSmoothMeshBoneWeightsDataflowNode`  
`struct FSmoothMeshBoneWeightsDataflowNode : public FDataflowNode`  
_L16-42_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Smooth bone weights on a dynamic mesh using Laplacian weight smoothing.
- L28 _public member_ `float Strength = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, ClampMin = 0.0, ClampMax = 1.0))` — Blend factor between original and smoothed weights (0=no change, 1=fully smoothed)
- L32 _public member_ `int32 NumIterations = 1;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput, ClampMin = 1, UIMax = 20))` — Number of smoothing iterations to apply
- L36 _public member_ `FName WeightProfile = FSkeletalMeshAttributes::DefaultSkinWeightProfileName;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — Name of the skin weight profile to smooth.
- L38 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L41 _public prototype_ `FSmoothMeshBoneWeightsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Dataflow` (scope `UE`)
- L46 _prototype_ `void RegisterMeshWeightEditingNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Private/Dataflow/SubdivideMeshDataflowNodes.h` (Private)


#### enum `EDataflowSubdivideAutogenPolygroupsMode`  
`enum class EDataflowSubdivideAutogenPolygroupsMode : uint8`  
_L12-25_
- reflection: `UENUM()`
- L15 _public enumerator_ `Never` — Never auto-generate; error out if the configured polygroup layer is unsuitable.
- L18 _public enumerator_ `Always` — Always run polygon detection and overwrite the configured layer before subdividing.
- L21 _public enumerator_ `IfMissing` — Run polygon detection only when the configured polygroup layer does not exist on the mesh.
- L24 _public enumerator_ `IfMissingOrInvalid` — Same as IfMissing, plus re-run generation if the subdivider rejects the topology on the first attempt.

#### struct `FSubdivideMeshCatmullClarkDataflowNode`  
`struct FSubdivideMeshCatmullClarkDataflowNode : public FDataflowNode`  
_L32-62_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Apply Catmull-Clark subdivision to a DataflowMesh using its polygroups as the control cage. The subdivision is editor-only; in non-editor builds the input mesh is passed through unchanged.
- L41 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L45 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh", DataflowIntrinsic))` — DataflowMesh input/output
- L49 _private member_ `int32 Subdivisions = 1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1, ClampMax = 6))` — Number of subdivision levels to apply
- L53 _private member_ `bool bDefaultLayer = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — If true, use the mesh's default polygroup layer. If false, uses the extended polygroup layer at ExtendedLayerIndex.
- L57 _private member_ `int32 ExtendedLayerIndex = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "!bDefaultLayer", ClampMin = 0))` — Index of the extended polygroup layer to use when bDefaultLayer is false
- L61 _private member_ `EDataflowSubdivideAutogenPolygroupsMode AutogenPolygroups = EDataflowSubdivideAutogenPolygroupsMode::IfMissing;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to auto-generate polygroups (by finding likely quads) when the configured polygroup layer is missing or not subdividable.

#### Free symbols / members of external scopes

- L64 _namespace_ `namespace UE`
- L64 _namespace_ `namespace Dataflow` (scope `UE`)
- L66 _prototype_ `void RegisterSubdivideMeshDataflowNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/CreateColorArrayFromFloatArrayNode.h` (Public)


#### struct `FCreateColorArrayFromFloatArrayDataflowNode`  
`struct FCreateColorArrayFromFloatArrayDataflowNode : public FDataflowNode`  
_L17-49_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Set the vertex color on the collection based on the normalized float array.
- L25 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Float Array"))` — Float array to use as a scalar for the color
- L29 _public member_ `TArray<FLinearColor> ColorArray;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Linear Color Array"))` — Color array output
- L33 _public member_ `bool bNormalizeInput = true;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (DisplayName = "Normalize Input"))` — Enable normalization of input array
- L37 _public member_ `FLinearColor Color = FLinearColor(FColor::White);` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (DisplayName = "Color"))` — Base color for the normalized float array
- L40 _public function_ `FCreateColorArrayFromFloatArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L47 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/DataflowNodeAndPinTypeColors.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Dataflow` (scope `UE`)
- L7 _prototype_ `void RegisterGeometryCollectionNodesColors();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionArrayNodes.h` (Public)


#### struct `FGetFloatArrayElementDataflowNode`  
`struct FGetFloatArrayElementDataflowNode : public FDataflowNode`  
_L24-52_
- reflection: `USTRUCT(meta = (Deprecated = 5.6))`
- inherits: `FDataflowNode`
- desc: Returns the specified element from an array DEPRECATED 5.6 - use the generic GetArrayElement node instead
- L32 _public member_ `int32 Index = 0;` — `UPROPERTY(EditAnywhere, Category = "Index")` — Element index
- L36 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput))` — Array to get the element from
- L40 _public member_ `float FloatValue = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Specified element
- L42 _public function_ `FGetFloatArrayElementDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L50 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EFloatArrayToIntArrayFunctionEnum`  
`enum class EFloatArrayToIntArrayFunctionEnum : uint8`  
_L56-67_
- reflection: `UENUM(BlueprintType)`
- L58 _public enumerator_ `Dataflow_FloatToInt_Function_Floor UMETA(DisplayName = "Floor()")`
- L59 _public enumerator_ `Dataflow_FloatToInt_Function_Ceil UMETA(DisplayName = "Ceil()")`
- L60 _public enumerator_ `Dataflow_FloatToInt_Function_Round UMETA(DisplayName = "Round()")`
- L61 _public enumerator_ `Dataflow_FloatToInt_Function_Truncate UMETA(DisplayName = "Truncate()")`
- L62 _public enumerator_ `Dataflow_FloatToInt_NonZeroToIndex UMETA(DisplayName = "Non-zero to Index")`
- L63 _public enumerator_ `Dataflow_FloatToInt_ZeroToIndex UMETA(DisplayName = "Zero to Index")`
- L66 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FFloatArrayToIntArrayDataflowNode`  
`struct FFloatArrayToIntArrayDataflowNode : public FDataflowNode`  
_L75-109_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Converts a Float array to Int array using the specified method.
- L90 _public member_ `EFloatArrayToIntArrayFunctionEnum Function = EFloatArrayToIntArrayFunctionEnum::Dataflow_FloatToInt_NonZeroToIndex;` — `UPROPERTY(EditAnywhere, Category = "Float")` — Conversion method: Floor takes the floor of each input float value - 1.1 turns into 1. Ceil takes the ceil - 1.1 turns into 2. Round rounds to the nearest integer - 1.1 turns into 1. Tuncate trucates like a type cast - 1.1 turns into 1. Non-zero to Index appends the index of all non-zero values to the output array. Zero to Index appends the index of all zero values to the output array.
- L94 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(EditAnywhere, Category = "Float", meta = (DataflowInput))` — Float array value to convert
- L98 _public member_ `TArray<int32> IntArray;` — `UPROPERTY(meta = (DataflowOutput))` — Int array output
- L100 _public function_ `FFloatArrayToIntArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L107 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetArrayElementDataflowNode`  
`struct FGetArrayElementDataflowNode : public FDataflowNode`  
_L119-147_
- reflection: `USTRUCT(meta = (Deprecated = 5.6))`
- inherits: `FDataflowNode`
- desc: Returns the specified element from an array DEPRECATED 5.6 - use the generic GetArrayElement node instead
- L127 _public member_ `int32 Index = 0;` — `UPROPERTY(EditAnywhere, Category = "Index")` — Element index
- L131 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowInput))` — Array to get the element from
- L135 _public member_ `FVector Point = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput))` — Specified element
- L137 _public function_ `FGetArrayElementDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L145 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetNumArrayElementsDataflowNode`  
`struct FGetNumArrayElementsDataflowNode : public FDataflowNode`  
_L157-195_
- reflection: `USTRUCT(meta = (Deprecated = 5.6))`
- inherits: `FDataflowNode`
- desc: Returns the number of elements in an array DEPRECATED 5.6 - use the generic GetArraySize node instead
- L165 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "FloatArray"))` — Float array input
- L169 _public member_ `TArray<int32> IntArray;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "IntArray"))` — Int32 array input
- L173 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "VectorArray"))` — FVector array input
- L177 _public member_ `TArray<FVector3f> Vector3fArray;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Vector3fArray"))` — FVector3f array input
- L181 _public member_ `int32 NumElements = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of elements in the array
- L183 _public function_ `FGetNumArrayElementsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L193 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoolArrayToFaceSelectionDataflowNode`  
`struct FBoolArrayToFaceSelectionDataflowNode : public FDataflowNode`  
_L204-226_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Converts a TArray<bool> to a FDataflowFaceSelection
- L212 _public member_ `TArray<bool> BoolAttributeData;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — TArray<bool> data
- L215 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FaceSelection"))`
- L217 _public function_ `FBoolArrayToFaceSelectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L224 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ECompareOperation1Enum`  
`enum class ECompareOperation1Enum : uint8`  
_L230-240_
- reflection: `UENUM(BlueprintType)`
- L232 _public enumerator_ `Dataflow_Compare_Equal UMETA(DisplayName = "==")`
- L233 _public enumerator_ `Dataflow_Compare_Smaller UMETA(DisplayName = "<")`
- L234 _public enumerator_ `Dataflow_Compare_SmallerOrEqual UMETA(DisplayName = "<=")`
- L235 _public enumerator_ `Dataflow_Compare_Greater UMETA(DisplayName = ">")`
- L236 _public enumerator_ `Dataflow_Compare_GreaterOrEqual UMETA(DisplayName = ">=")`
- L239 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FFloatArrayToVertexSelectionDataflowNode`  
`struct FFloatArrayToVertexSelectionDataflowNode : public FDataflowNode`  
_L248-278_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Converts a TArray<float> to a FDataflowVertexSelection
- L256 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — TArray<floatl> array
- L260 _public member_ `ECompareOperation1Enum Operation = ECompareOperation1Enum::Dataflow_Compare_Greater;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Comparison operation
- L264 _public member_ `float Threshold = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Compare")`
- L267 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VertexSelection"))`
- L269 _public function_ `FFloatArrayToVertexSelectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L276 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFloatArrayNormalizeDataflowNode`  
`struct FFloatArrayNormalizeDataflowNode : public FDataflowNode`  
_L287-325_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Normalize the selected float data in a FloatArray
- L295 _public member_ `TArray<float> InFloatArray;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input VectorArray
- L299 _public member_ `FDataflowVertexSelection Selection;` — `UPROPERTY(meta = (DataflowInput))` — Selection for the operation
- L303 _public member_ `float MinRange = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L307 _public member_ `float MaxRange = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L311 _public member_ `TArray<float> OutFloatArray;` — `UPROPERTY(meta = (DataflowOutput))`
- L313 _public function_ `FFloatArrayNormalizeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L323 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FVectorArrayNormalizeDataflowNode`  
`struct FVectorArrayNormalizeDataflowNode : public FDataflowNode`  
_L334-367_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Normalize all the selected vectors in a VectorArray
- L342 _public member_ `TArray<FVector> InVectorArray;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input VectorArray
- L346 _public member_ `FDataflowVertexSelection Selection;` — `UPROPERTY(meta = (DataflowInput))` — Selection for the operation
- L350 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L354 _public member_ `TArray<FVector> OutVectorArray;` — `UPROPERTY(meta = (DataflowOutput))`
- L356 _public function_ `FVectorArrayNormalizeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L365 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FUnionIntArraysDataflowNode`  
`struct FUnionIntArraysDataflowNode : public FDataflowNode`  
_L371-395_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L378 _public member_ `TArray<int32> InArray1;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InArray1"))`
- L381 _public member_ `TArray<int32> InArray2;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InArray2"))`
- L384 _public member_ `TArray<int32> OutArray;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "OutArray", DataflowPassthrough = "InArray1"))`
- L386 _public function_ `FUnionIntArraysDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L394 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRemoveFloatArrayElementDataflowNode`  
`struct FRemoveFloatArrayElementDataflowNode : public FDataflowNode`  
_L404-432_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Removes the specified element from an array
- L412 _public member_ `int32 Index = 0;` — `UPROPERTY(EditAnywhere, Category = "Index")` — Element index
- L416 _public member_ `bool bPreserveOrder = true;` — `UPROPERTY(EditAnywhere, Category = "Order")` — Preserve order, if order not important set it to false for faster computation
- L420 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "FloatArray", DataflowIntrinsic))` — Array to remove the element from
- L422 _public function_ `FRemoveFloatArrayElementDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L430 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EStatisticsOperationEnum`  
`enum class EStatisticsOperationEnum : uint8`  
_L436-447_
- reflection: `UENUM(BlueprintType)`
- L438 _public enumerator_ `Dataflow_EStatisticsOperationEnum_Min UMETA(DisplayName = "Min", ToolTip = "")`
- L439 _public enumerator_ `Dataflow_EStatisticsOperationEnum_Max UMETA(DisplayName = "Max", ToolTip = "")`
- L440 _public enumerator_ `Dataflow_EStatisticsOperationEnum_Mean UMETA(DisplayName = "Mean", ToolTip = "")`
- L441 _public enumerator_ `Dataflow_EStatisticsOperationEnum_Median UMETA(DisplayName = "Median", ToolTip = "")`
- L442 _public enumerator_ `Dataflow_EStatisticsOperationEnum_Mode UMETA(DisplayName = "Mode", ToolTip = "")`
- L443 _public enumerator_ `Dataflow_EStatisticsOperationEnum_Sum UMETA(DisplayName = "Sum", ToolTip = "")`
- L446 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FFloatArrayComputeStatisticsDataflowNode`  
`struct FFloatArrayComputeStatisticsDataflowNode : public FDataflowNode`  
_L455-492_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Computes statistics of a float array
- L463 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Array to compute values from
- L467 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — TransformSelection describes which values to use, if not connected all the elements will be used
- L471 _public member_ `EStatisticsOperationEnum OperationName = EStatisticsOperationEnum::Dataflow_EStatisticsOperationEnum_Min;` — `UPROPERTY(EditAnywhere, Category = "Operation", meta = (DisplayName = "Operation"))` — Statistics Operation
- L475 _public member_ `float Value = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Computed value
- L479 _public member_ `TArray<int32> Indices;` — `UPROPERTY(meta = (DataflowOutput))` — Indices of elements with the computed value
- L481 _public function_ `FFloatArrayComputeStatisticsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L490 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRandomizeFloatArrayDataflowNode`  
`struct FRandomizeFloatArrayDataflowNode : public FDataflowNode`  
_L500-533_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Randomize elements in a float array (Random value will be in (RandomRangeMin, RandomRangeMax)
- L508 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "FloatArray", DataflowIntrinsic))` — Array to randomize
- L512 _public member_ `float RandomRangeMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, DisplayName = "Random Range Min"))` — Random range min
- L516 _public member_ `float RandomRangeMax = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, DisplayName = "Random Range Max"))` — Random range max
- L520 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L522 _public function_ `FRandomizeFloatArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L532 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowGetArraySizeNode`  
`struct FDataflowGetArraySizeNode : public FDataflowNode`  
_L539-557_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Get size of an array
- L547 _private member_ `FDataflowArrayTypes Array;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Array to get size from
- L551 _private member_ `int32 Size = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Computed value
- L553 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L556 _public prototype_ `FDataflowGetArraySizeNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowGetArrayElementNode`  
`struct FDataflowGetArrayElementNode : public FDataflowNode`  
_L563-587_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Get an element from an array
- L571 _private member_ `FDataflowArrayTypes Array;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Array", DataflowIntrinsic))` — Array to get the element from
- L575 _private member_ `int32 Index = 0;` — `UPROPERTY(EditAnywhere, Category = "Array", meta = (DataflowInput))` — Index to get the element at
- L579 _private member_ `FDataflowAllTypes Element;` — `UPROPERTY(meta = (DataflowOutput))` — Element from the array at the specified index
- L581 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L583 _private prototype_ `virtual FName GetDependentConnectionType(const FDataflowConnection& SourceConnection, const FDataflowConnection& DependentConnection) const override;`
- L586 _public prototype_ `FDataflowGetArrayElementNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowConvertToArrayNode`  
`struct FDataflowConvertToArrayNode : public FDataflowNode`  
_L594-614_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: convert a single element to an array
- L600 _public prototype_ `FDataflowConvertToArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L605 _private member_ `FDataflowArrayTypes Array;` — `UPROPERTY(meta = (DataflowOutput))` — Array to Convert to
- L609 _private member_ `FDataflowAllTypes Element;` — `UPROPERTY(meta = (DataflowInput))` — Element to convert to an array
- L611 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L613 _private prototype_ `virtual FName GetDependentConnectionType(const FDataflowConnection& SourceConnection, const FDataflowConnection& DependentConnection) const override;`

#### struct `FDataflowMakeArrayNode`  
`struct FDataflowMakeArrayNode : public FDataflowNode`  
_L620-654_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make an array from multiple elements of the same type. When elements are array type, the arrays are appended (nested arrays are not supported).
- L626 _public prototype_ `FDataflowMakeArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L631 _private member_ `FDataflowArrayTypes Array;` — `UPROPERTY(meta = (DataflowOutput))` — Array to Convert to
- L635 _private member_ `TArray<FDataflowAllTypes> Elements;` — `UPROPERTY()` — Elements to convert to an array
- L637 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L639 _private prototype_ `virtual FName GetDependentConnectionType(const FDataflowConnection& SourceConnection, const FDataflowConnection& DependentConnection) const override;`
- L641 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L642 _private function_ `virtual bool CanAddPin() const override`
- L643 _private function_ `virtual bool CanRemovePin() const override`
- L644 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L645 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L646 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L648 _private prototype_ `UE::Dataflow::TConnectionReference<FDataflowAllTypes> GetConnectionReference(int32 Index) const;`
- L650 _private member_ `static constexpr int32 NumRequiredInputs = 0;`
- L651 _private member_ `static constexpr int32 NumInitialElements = 2;`
- L653 _private member_ `inline static FName ArrayElementDependencyGroup = FName("Arr`

#### struct `FDataflowMakeManagedArrayCollectionArrayNode`  
`struct FDataflowMakeManagedArrayCollectionArrayNode : public FDataflowNode`  
_L660-678_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Append an element to an array of ManagedArrayCollections.
- L668 _private member_ `TArray<FManagedArrayCollection> Array;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Array", DataflowIntrinsic))` — Array to append to. If no input connection, a new array will be created
- L672 _private member_ `FManagedArrayCollection Element;` — `UPROPERTY(meta = (DataflowInput))` — The element to append.
- L674 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L677 _public prototype_ `FDataflowMakeManagedArrayCollectionArrayNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Dataflow`
- L680 _namespace_ `namespace UE`
- L680 _namespace_ `namespace Dataflow` (scope `UE`)
- L682 _prototype_ `void GeometryCollectionArrayNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionAssetNodes.h` (Public)


#### struct `FDataflowRootProxyMesh`  
`struct FDataflowRootProxyMesh`  
_L19-31_
- reflection: `USTRUCT()`
- L24 _public member_ `TObjectPtr<UStaticMesh> Mesh;` — `UPROPERTY(EditAnywhere, Category = RootProxyMesh)`
- L27 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = RootProxyMesh)`
- L30 _public member_ `TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = RootProxyMesh)`

#### struct `FMakeRootProxyMeshDataflowNode`  
`struct FMakeRootProxyMeshDataflowNode : public FDataflowNode`  
_L38-63_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Create a RootProxyMesh object (used by geometry collection assets)
- L46 _private member_ `TObjectPtr<UStaticMesh> Mesh;` — `UPROPERTY(EditAnywhere, Category = RootProxyMesh, meta = (DataflowInput))` — mesh to use as a proxy
- L50 _private member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = RootProxyMesh, meta = (DataflowInput))` — transform to use for the proxy, relative to the asset it will be used for
- L53 _private member_ `TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = RootProxyMesh, meta = (DataflowInput))`
- L57 _private member_ `FDataflowRootProxyMesh RootProxyMesh;` — `UPROPERTY(meta = (DataflowOutput))` — mesh to use as a proxy
- L59 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L62 _public prototype_ `FMakeRootProxyMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMakeRootProxyMeshArrayDataflowNode`  
`struct FMakeRootProxyMeshArrayDataflowNode : public FDataflowNode`  
_L70-84_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Create a RootProxyMesh Array (used by geometry collection assets)
- L78 _private member_ `TArray<FDataflowRootProxyMesh> RootProxyMeshes;` — `UPROPERTY(EditAnywhere, Category = RootProxyMesh, meta = (DataflowOutput))` — newly created array
- L80 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L83 _public prototype_ `FMakeRootProxyMeshArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FAddRootProxyMeshToArrayDataflowNode`  
`struct FAddRootProxyMeshToArrayDataflowNode : public FDataflowNode`  
_L91-108_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, DataflowTerminal))`
- inherits: `FDataflowNode`
- desc: Add a root proxy object to an array of root proxy mesh * (used by geometry collection assets)
- L99 _private member_ `TArray<FDataflowRootProxyMesh> RootProxyMeshes;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = RootProxyMeshes))` — Root proxy array to add the mesh to
- L102 _private member_ `FDataflowRootProxyMesh RootProxyMesh;` — `UPROPERTY(EditAnywhere, Category = RootProxyMesh, meta = (DataflowInput))`
- L104 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L107 _public prototype_ `FAddRootProxyMeshToArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGeometryCollectionTerminalDataflowNode_v2`  
`struct FGeometryCollectionTerminalDataflowNode_v2 : public FDataflowTerminalNode`  
_L114-139_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Geometry Collection asset terminal node
- L121 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L125 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Materials"))` — Materials to set on this asset
- L129 _private member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "InstancedMeshes"))` — array of instanced meshes
- L132 _private member_ `TArray<FDataflowRootProxyMesh> RootProxyMeshes;` — `UPROPERTY(meta = (DataflowInput))`
- L134 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L135 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L138 _public prototype_ `FGeometryCollectionTerminalDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGeometryCollectionTerminalDataflowNode`  
`struct FGeometryCollectionTerminalDataflowNode : public FDataflowTerminalNode`  
_L146-171_
- reflection: `USTRUCT(meta = (DataflowTerminal, Deprecated = "5.6"))`
- inherits: `FDataflowTerminalNode`
- desc: Geometry Collection asset terminal node Deprecated (5.6) - Use version 2 of the same node that only support material interface array as materials input
- L154 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DisplayName = "Collection"))`
- L158 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Materials", DisplayName = "Materials"))` — Materials array to use for this asset
- L161 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialInstances;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "MaterialInstances", DisplayName = "MaterialInstances"))`
- L165 _public member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "InstancedMeshes", DisplayName = "InstancedMeshes"))` — array of instanced meshes
- L167 _public prototype_ `FGeometryCollectionTerminalDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L169 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L170 _public prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`

#### struct `FGetGeometryCollectionAssetDataflowNode`  
`struct FGetGeometryCollectionAssetDataflowNode : public FDataflowNode`  
_L179-191_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get Current geometry collection asset Note : Use with caution as this may get replaced in a near future for a more generic getAsset node
- L185 _public prototype_ `FGetGeometryCollectionAssetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L186 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L190 _public member_ `TObjectPtr<UGeometryCollection> Asset;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Asset"))` — Asset this data flow graph instance is assigned to

#### struct `FGetGeometryCollectionSourcesDataflowNode`  
`struct FGetGeometryCollectionSourcesDataflowNode : public FDataflowNode`  
_L199-215_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get the list of the original mesh information used to create a specific geometryc collection asset each entry contains a mesh, a transform and a list of override materials
- L205 _public prototype_ `FGetGeometryCollectionSourcesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L206 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L210 _public member_ `TObjectPtr<UGeometryCollection> Asset;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Asset"))` — Asset to get geometry sources from
- L214 _public member_ `TArray<FGeometryCollectionSource> Sources;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Sources"))` — array of geometry sources

#### struct `FCreateGeometryCollectionFromSourcesDataflowNode`  
`struct FCreateGeometryCollectionFromSourcesDataflowNode : public FDataflowNode`  
_L223-251_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: create a geometry collection from a set of geometry sources DEPRECATED 5.6 : use the new node version with a single material array output
- L229 _public prototype_ `FCreateGeometryCollectionFromSourcesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L230 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L234 _public member_ `TArray<FGeometryCollectionSource> Sources;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Sources"))` — array of geometry sources
- L238 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection"))` — Geometry collection newly created
- L242 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Materials"))` — Materials array to use for this asset
- L246 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialInstances;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "MaterialInstances"))` — Materials array to use for this asset
- L250 _public member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "InstancedMeshes"))` — array of instanced meshes

#### struct `FCreateGeometryCollectionFromSourcesDataflowNode_v2`  
`struct FCreateGeometryCollectionFromSourcesDataflowNode_v2 : public FDataflowNode`  
_L258-288_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: create a geometry collection from a set of geometry sources if the source array is not connected, the source array from the current asset is going to be used
- L264 _public prototype_ `FCreateGeometryCollectionFromSourcesDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L267 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L271 _private member_ `TArray<FGeometryCollectionSource> Sources;` — `UPROPERTY(meta = (DataflowInput))` — array of geometry sources
- L275 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))` — Geometry collection newly created
- L279 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowOutput))` — Materials array to use for this asset
- L283 _private member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowOutput))` — array of instanced meshes
- L287 _private member_ `TArray<FDataflowRootProxyMesh> RootProxyMeshes;` — `UPROPERTY(meta = (DataflowOutput))` — corresponding source proxies

#### struct `FGeometryCollectionToCollectionDataflowNode`  
`struct FGeometryCollectionToCollectionDataflowNode : public FDataflowNode`  
_L295-323_
- reflection: `USTRUCT(meta = (DataflowContext = "GeometryCollection", DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts a UGeometryCollection asset to an FManagedArrayCollection DEPRECATED 5.6 : use the new version  that only has one material array output
- L303 _public member_ `TObjectPtr<UGeometryCollection> GeometryCollection;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Asset input
- L307 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection"))` — Geometry collection newly created
- L311 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Materials"))` — Materials array to use for this asset
- L315 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialInstances;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "MaterialInstances"))` — Material instances array from the static mesh
- L319 _public member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "InstancedMeshes"))` — Array of instanced meshes
- L321 _public prototype_ `FGeometryCollectionToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L322 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGeometryCollectionToCollectionDataflowNode_v2`  
`struct FGeometryCollectionToCollectionDataflowNode_v2 : public FDataflowNode`  
_L329-359_
- reflection: `USTRUCT(meta = (DataflowContext = "GeometryCollection", DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts a UGeometryCollection asset to an FManagedArrayCollection
- L335 _public prototype_ `FGeometryCollectionToCollectionDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L340 _private member_ `TObjectPtr<UGeometryCollection> GeometryCollection;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (DataflowInput))` — Asset input
- L344 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))` — Geometry collection newly created
- L348 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowOutput))` — Material instances array from the static mesh
- L352 _private member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowOutput))` — Array of instanced meshes
- L356 _private member_ `TArray<FDataflowRootProxyMesh> RootProxyMeshes;` — `UPROPERTY(meta = (DataflowOutput))` — corresponding source proxies
- L358 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBlueprintToCollectionDataflowNode`  
`struct FBlueprintToCollectionDataflowNode : public FDataflowNode`  
_L366-398_
- reflection: `USTRUCT(meta = (DataflowContext = "GeometryCollection", DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Create a geometry collection from an asset DEPRECATED 5.6 : use the new version  that only has one material array output
- L374 _public member_ `TObjectPtr<UBlueprint> Blueprint;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Asset input
- L378 _public member_ `bool bSplitComponents = false;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Split components
- L382 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection"))` — Geometry collection newly created
- L386 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Materials"))` — Materials array to use for this asset
- L390 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialInstances;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "MaterialInstances"))` — Material instances array from the static mesh
- L394 _public member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "InstancedMeshes"))` — Array of instanced meshes
- L396 _public prototype_ `FBlueprintToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L397 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBlueprintToCollectionDataflowNode_v2`  
`struct FBlueprintToCollectionDataflowNode_v2 : public FDataflowNode`  
_L405-439_
- reflection: `USTRUCT(meta = (DataflowContext = "GeometryCollection", DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Create a geometry collection from an asset
- L411 _public prototype_ `FBlueprintToCollectionDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L416 _private member_ `TObjectPtr<UBlueprint> Blueprint;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Asset input
- L420 _private member_ `bool bSplitComponents = false;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Split components
- L424 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))` — Geometry collection newly created
- L428 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowOutput))` — Material instances array from the static mesh
- L432 _private member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowOutput))` — Array of instanced meshes
- L436 _private member_ `TArray<FDataflowRootProxyMesh> RootProxyMeshes;` — `UPROPERTY(meta = (DataflowOutput))` — corresponding source proxies
- L438 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FAssetRandomSeedDataflowNode`  
`struct FAssetRandomSeedDataflowNode : public FDataflowNode`  
_L445-463_
- reflection: `USTRUCT(meta = (DataflowContext = "GeometryCollection", DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Create a random seed value from an asset
- L451 _public prototype_ `FAssetRandomSeedDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L456 _private member_ `int32 Seed = 0;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))` — Seed to combine with the seed generated from the asset path
- L460 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Random seed value
- L462 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Dataflow`
- L465 _namespace_ `namespace UE`
- L465 _namespace_ `namespace Dataflow` (scope `UE`)
- L467 _prototype_ `void GeometryCollectionEngineAssetNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionClusteringNodes.h` (Public)


#### enum `EClusterSizeMethodEnum`  
`enum class EClusterSizeMethodEnum : uint8`  
_L18-27_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Dataflow_ClusterSizeMethod_ByNumber UMETA(DisplayName = "By Number")`
- L21 _public enumerator_ `Dataflow_ClusterSizeMethod_ByFractionOfInput UMETA(DisplayName = "By Fraction Of Input")`
- L22 _public enumerator_ `Dataflow_ClusterSizeMethod_BySize UMETA(DisplayName = "By Size")`
- L23 _public enumerator_ `Dataflow_ClusterSizeMethod_ByGrid UMETA(DisplayName = "By Grid")`
- L26 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FAutoClusterDataflowNode`  
`struct FAutoClusterDataflowNode : public FDataflowNode`  
_L35-109_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Automatically group pieces of a fractured Collection into a specified number of clusters
- L43 _private member_ `EClusterSizeMethodEnum ClusterSizeMethod = EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByNumber;` — `UPROPERTY(EditAnywhere, Category = ClusterSize)` — How to choose the size of the clusters to create
- L47 _private member_ `int32 ClusterSites = 10;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DataflowInput, UIMin = 2, UIMax = 5000, EditCondition = "ClusterSizeMethod == EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByNumber"))` — Use a Voronoi diagram with this many Voronoi sites as a guide for deciding cluster boundaries
- L51 _private member_ `float ClusterFraction = 0.25;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DataflowInput, UIMin = 0.f, UIMax = 0.5f, EditCondition = "ClusterSizeMethod == EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByFractionOfInput"))` — Choose the number of Voronoi sites used for clustering as a fraction of the number of child bones to process
- L55 _private member_ `float SiteSize = 1;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DataflowInput, DisplayName = "Cluster Size", UIMin = ".01", UIMax = "100", ClampMin = ".0001", ClampMax = "10000", EditCondition = "ClusterSizeMethod == EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_BySize"))` — Choose the Edge-Size of the cube used to groups bones under a cluster (in cm).
- L59 _private member_ `int ClusterGridWidth = 2;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DataflowInput, ClampMin = "1", UIMax = "20", EditCondition = "ClusterSizeMethod == EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByGrid"))` — Choose the number of cluster sites to distribute along the X axis
- L63 _private member_ `int ClusterGridDepth = 2;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DataflowInput, ClampMin = "1", UIMax = "20", EditCondition = "ClusterSizeMethod == EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByGrid"))` — Choose the number of cluster sites to distribute along the Y axis
- L67 _private member_ `int ClusterGridHeight = 2;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DataflowInput, ClampMin = "1", UIMax = "20", EditCondition = "ClusterSizeMethod == EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByGrid"))` — Choose the number of cluster sites to distribute along the Z axis
- L71 _private member_ `int DriftIterations = 0;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DisplayName = "Grid Drift Iterations", ClampMin = "0", UIMax = "5", EditCondition = "ClusterSizeMethod == EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByGrid"))` — For a grid distribution, optionally iteratively recenter the grid points to the center of the cluster geometry (technically: applying K-Means iterations) to balance the shape and distribution of the clusters
- L75 _private member_ `float MinimumSize = 0;` — `UPROPERTY(EditAnywhere, Category = ClusterSize, meta = (DataflowInput, ClampMin = "0"))` — If a cluster has volume less than this value (in cm) cubed, then the auto-cluster process will attempt to merge it into a neighboring cluster.
- L79 _private member_ `bool bPreferConvexity = false;` — `UPROPERTY(EditAnywhere, Category = AutoCluster, meta = (EditCondition = "ClusterSizeMethod != EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByGrid"))` — Whether to favor clusters that have a convex shape. (Note: Does not support ByGrid clustering.)
- L83 _private member_ `float ConcavityTolerance = 0;` — `UPROPERTY(EditAnywhere, Category = AutoCluster, meta = (EditCondition = "bPreferConvexity && ClusterSizeMethod != EClusterSizeMethodEnum::Dataflow_ClusterSizeMethod_ByGrid"))` — If > 0, cube root of maximum concave volume to add per cluster (ignoring concavity of individual parts)
- L87 _private member_ `bool AutoCluster = true;` — `UPROPERTY(EditAnywhere, Category = AutoCluster, meta = (DisplayName = "Enforce Cluster Connectivity"))` — If true, bones will only be added to the same cluster if they are physically connected (either directly, or via other bones in the same cluster)
- L91 _private member_ `bool EnforceSiteParameters = true;` — `UPROPERTY(EditAnywhere, Category = AutoCluster, meta = (EditCondition = "AutoCluster == true"))` — If true, make sure the site parameters are matched as close as possible ( bEnforceConnectivity can make the number of site larger than the requested input may produce without it )
- L95 _private member_ `bool AvoidIsolated = true;` — `UPROPERTY(EditAnywhere, Category = AutoCluster)` — If true, prevent the creation of clusters with only a single child. Either by merging into a neighboring cluster, or not creating the cluster.
- L99 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Fractured GeometryCollection to cluster
- L103 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection", DataflowIntrinsic))` — Bone selection for the clustering
- L105 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L108 _public prototype_ `FAutoClusterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FClusterFlattenDataflowNode`  
`struct FClusterFlattenDataflowNode : public FDataflowNode`  
_L118-144_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Flattens selected bones. If no selection is provided, flattens all bones to level 1
- L127 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Fractured GeometryCollection to flatten
- L131 _public member_ `FDataflowTransformSelection OptionalTransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — If connected, clusters under the selected bones will be flattened. If no selection is provided, all bones will be flattened to level 1.
- L133 _public function_ `FClusterFlattenDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L142 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FClusterUnclusterDataflowNode`  
`struct FClusterUnclusterDataflowNode : public FDataflowNode`  
_L150-175_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Uncluster selected nodes
- L159 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Fractured GeometryCollection to uncluster
- L163 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — Bone selection
- L165 _public function_ `FClusterUnclusterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L173 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FClusterDataflowNode`  
`struct FClusterDataflowNode : public FDataflowNode`  
_L181-206_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Cluster selected nodes under a new parent
- L190 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection on which to cluster nodes
- L194 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — Bone selection
- L196 _public function_ `FClusterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L204 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EClusterNeighborSelectionMethodEnum`  
`enum class EClusterNeighborSelectionMethodEnum : uint8`  
_L211-215_
- reflection: `UENUM(BlueprintType)`
- L213 _public enumerator_ `Dataflow_ClusterNeighborSelectionMethod_LargestNeighbor UMETA(DisplayName = "Largest Neighbor")`
- L214 _public enumerator_ `Dataflow_ClusterNeighborSelectionMethod_NearestCenter UMETA(DisplayName = "Nearest Center")`

#### struct `FClusterMergeToNeighborsDataflowNode`  
`struct FClusterMergeToNeighborsDataflowNode : public FDataflowNode`  
_L221-266_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Merge selected bones to their neighbors
- L230 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection on which to merge bones into a neighboring cluster
- L234 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — Bone selection
- L238 _public member_ `EClusterNeighborSelectionMethodEnum NeighborSelectionMethod = EClusterNeighborSelectionMethodEnum::Dataflow_ClusterNeighborSelectionMethod_LargestNeighbor;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Merge To"))` — Method to choose which neighbor to merge
- L242 _public member_ `float MinVolumeCubeRoot = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, DisplayName = "Min Cluster Size", ClampMin = "0"))` — Size (cube root of volume) of minimum desired post-merge clusters; if > 0, selected clusters may be merged multiple times until the cluster size is above this value
- L246 _public member_ `bool bOnlyToConnected = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Whether to only allow clusters to merge if their bones are connected in the proximity graph
- L250 _public member_ `bool bOnlySameParent = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Whether to only allow clusters to merge if they have the same parent bone
- L252 _public function_ `FClusterMergeToNeighborsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L264 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FClusterMergeDataflowNode`  
`struct FClusterMergeDataflowNode : public FDataflowNode`  
_L273-298_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Merge selected bones under a new parent cluster
- L282 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection on which to merge bones into a cluster
- L286 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — Bone selection
- L288 _public function_ `FClusterMergeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L296 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FClusterIsolatedRootsDataflowNode`  
`struct FClusterIsolatedRootsDataflowNode : public FDataflowNode`  
_L305-325_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Add a single cluster to the Geometry Collection if it only has a single transform with no clusters
- L314 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to modify
- L316 _public function_ `FClusterIsolatedRootsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L323 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FClusterMagnetDataflowNode`  
`struct FClusterMagnetDataflowNode : public FDataflowNode`  
_L332-362_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Cluster by grouping the selected bones with their adjacent, neighboring bones.
- L341 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection on which to merge bones into a cluster
- L345 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — Bone selection
- L349 _public member_ `int32 Iterations = 1;` — `UPROPERTY(EditAnywhere, Category = "Cluster Magnet", meta = (ClampMin = "1", DataflowInput, DisplayName = "Iterations"))` — How many layers of neighbors to include in the clusters -- i.e. if 1, only direct neighbors are clustered; if 2, neighbors of neighbors are included, etc.
- L351 _public function_ `FClusterMagnetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L360 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Dataflow`
- L365 _namespace_ `namespace UE`
- L365 _namespace_ `namespace Dataflow` (scope `UE`)
- L367 _prototype_ `void GeometryCollectionClusteringNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionConversionNodes.h` (Public)


#### struct `FVectorToStringDataflowNode`  
`struct FVectorToStringDataflowNode : public FDataflowNode`  
_L18-39_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Description for this node
- L25 _public member_ `FVector Vector = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (DataflowInput))`
- L28 _public member_ `FString String = FString("");` — `UPROPERTY(meta = (DataflowOutput))`
- L30 _public function_ `FVectorToStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L37 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFloatToStringDataflowNode`  
`struct FFloatToStringDataflowNode : public FDataflowNode`  
_L47-68_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Description for this node
- L54 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Float", meta = (DataflowInput))`
- L57 _public member_ `FString String = FString("");` — `UPROPERTY(meta = (DataflowOutput))`
- L59 _public function_ `FFloatToStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L66 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FIntToStringDataflowNode`  
`struct FIntToStringDataflowNode : public FDataflowNode`  
_L76-97_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts an Int to a String
- L83 _public member_ `int32 Int = 0;` — `UPROPERTY(EditAnywhere, Category = "Int", meta = (DataflowInput))`
- L86 _public member_ `FString String = FString("");` — `UPROPERTY(meta = (DataflowOutput))`
- L88 _public function_ `FIntToStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L95 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoolToStringDataflowNode`  
`struct FBoolToStringDataflowNode : public FDataflowNode`  
_L105-126_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts a Bool to a String in a form of ("true", "false")
- L112 _public member_ `bool Bool = false;` — `UPROPERTY(EditAnywhere, Category = "Bool", meta = (DataflowInput))`
- L115 _public member_ `FString String = FString("");` — `UPROPERTY(meta = (DataflowOutput))`
- L117 _public function_ `FBoolToStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L124 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FIntToFloatDataflowNode`  
`struct FIntToFloatDataflowNode : public FDataflowNode`  
_L134-154_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts an Int to a Float
- L141 _public member_ `int32 Int = 0;` — `UPROPERTY(EditAnywhere, Category = "Int", meta = (DataflowInput))`
- L144 _public member_ `float Float = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L146 _public function_ `FIntToFloatDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L153 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FIntToDoubleDataflowNode`  
`struct FIntToDoubleDataflowNode : public FDataflowNode`  
_L162-182_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts an Int to a Double
- L169 _public member_ `int32 Int = 0;` — `UPROPERTY(EditAnywhere, Category = "Int", meta = (DataflowInput))`
- L172 _public member_ `double Double = 0.0;` — `UPROPERTY(meta = (DataflowOutput))`
- L174 _public function_ `FIntToDoubleDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L181 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFloatToDoubleDataflowNode`  
`struct FFloatToDoubleDataflowNode : public FDataflowNode`  
_L190-210_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts an Float to a Double
- L197 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Int", meta = (DataflowInput))`
- L200 _public member_ `double Double = 0.0;` — `UPROPERTY(meta = (DataflowOutput))`
- L202 _public function_ `FFloatToDoubleDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L209 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EFloatToIntFunctionEnum`  
`enum class EFloatToIntFunctionEnum : uint8`  
_L214-223_
- reflection: `UENUM(BlueprintType)`
- L216 _public enumerator_ `Dataflow_FloatToInt_Function_Floor UMETA(DisplayName = "Floor()")`
- L217 _public enumerator_ `Dataflow_FloatToInt_Function_Ceil UMETA(DisplayName = "Ceil()")`
- L218 _public enumerator_ `Dataflow_FloatToInt_Function_Round UMETA(DisplayName = "Round()")`
- L219 _public enumerator_ `Dataflow_FloatToInt_Function_Truncate UMETA(DisplayName = "Truncate()")`
- L222 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FFloatToIntDataflowNode`  
`struct FFloatToIntDataflowNode : public FDataflowNode`  
_L231-258_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts a Float to Int using the specified method
- L239 _public member_ `EFloatToIntFunctionEnum Function = EFloatToIntFunctionEnum::Dataflow_FloatToInt_Function_Round;` — `UPROPERTY(EditAnywhere, Category = "Float")` — Method to convert
- L243 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Float", meta = (DataflowInput))` — Float value to convert
- L247 _public member_ `int32 Int = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Int output
- L249 _public function_ `FFloatToIntDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L256 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FIntToBoolDataflowNode`  
`struct FIntToBoolDataflowNode : public FDataflowNode`  
_L266-287_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts an Int to a Bool
- L273 _public member_ `int32 Int = 0;` — `UPROPERTY(EditAnywhere, Category = "Int", meta = (DataflowInput))`
- L276 _public member_ `bool Bool = false;` — `UPROPERTY(meta = (DataflowOutput))`
- L278 _public function_ `FIntToBoolDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L285 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoolToIntDataflowNode`  
`struct FBoolToIntDataflowNode : public FDataflowNode`  
_L295-316_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts a Bool to an Int
- L302 _public member_ `bool Bool = false;` — `UPROPERTY(EditAnywhere, Category = "Bool", meta = (DataflowInput))`
- L305 _public member_ `int32 Int = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L307 _public function_ `FBoolToIntDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L314 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`
- L318 _namespace_ `namespace UE`
- L318 _namespace_ `namespace Dataflow` (scope `UE`)
- L320 _prototype_ `void GeometryCollectionConversionNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionDebugNodes.h` (Public)


#### struct `FConvexHullToMeshDataflowNode`  
`struct FConvexHullToMeshDataflowNode : public FDataflowNode`  
_L21-50_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Convert convex hulls on a geometry collection to a dynamic mesh
- L28 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L32 _private member_ `FDataflowTransformSelection OptionalSelectionFilter;` — `UPROPERTY(meta = (DataflowInput))` — Optional transform selection to convert hulls from -- if not provided, all convex hulls will be converted.
- L36 _private member_ `bool bUseRobustHulls = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to robustly extract valid/manifold meshes to represent the convex hulls. Note: Not necessary for simple visualization, but useful for downstream processing.
- L40 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Single mesh aggregating all the convex hulls together
- L44 _private member_ `TArray<TObjectPtr<UDynamicMesh>> Meshes;` — `UPROPERTY(meta = (DataflowOutput))` — Array of meshes for each convex hull found
- L46 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L49 _public prototype_ `FConvexHullToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSphereCoveringToMeshDataflowNode`  
`struct FSphereCoveringToMeshDataflowNode : public FDataflowNode`  
_L54-79_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Convert a sphere covering, as generated by the 'protect negative space' option on the "Generate Cluster Convex Hull" nodes, to a dynamic mesh
- L62 _public member_ `FDataflowSphereCovering SphereCovering;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — The sphere covering to convert to a mesh
- L66 _public member_ `int32 VerticesAlongEachSide = 8;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = 2))` — Number of vertices to use along each axis when creating a mesh for each sphere
- L69 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))`
- L71 _public function_ `FSphereCoveringToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L78 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSphereCoveringCountSpheresNode`  
`struct FSphereCoveringCountSpheresNode : public FDataflowNode`  
_L83-112_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Report the number of spheres in a sphere covering
- L91 _public member_ `FDataflowSphereCovering SphereCovering;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — The sphere covering to evaluate
- L95 _public member_ `int32 NumSpheres = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of spheres in the sphere covering
- L97 _public function_ `FSphereCoveringCountSpheresNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L104 _public function_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override`

#### struct `FMeshToOBJStringDebugDataflowNode`  
`struct FMeshToOBJStringDebugDataflowNode: public FDataflowNode`  
_L116-142_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Convert a mesh to a string formatted as an OBJ file, which can be read by many external mesh viewers
- L123 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput))`
- L127 _public member_ `bool bInvertFaces = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Whether to flip the orientation of the triangles in the OBJ output
- L131 _public member_ `FString StringOBJ;` — `UPROPERTY(meta = (DataflowOutput))` — A string representing the input mesh in the OBJ file format
- L133 _public function_ `FMeshToOBJStringDebugDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L141 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FWriteStringToFile`  
`struct FWriteStringToFile : public FDataflowNode`  
_L146-169_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Write a string to a file
- L155 _public member_ `FString FilePath;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Where file should be written on disk
- L159 _public member_ `FString FileContents;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Contents of the file to write
- L161 _public function_ `FWriteStringToFile(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L168 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSpheresToMeshDataflowNode`  
`struct FSpheresToMeshDataflowNode : public FDataflowNode`  
_L173-200_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Convert a TArray<FShere> to a dynamic mesh
- L181 _private member_ `TArray<FSphere> Spheres;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Array of spheres to convert to a mesh/meshes
- L185 _private member_ `int32 VerticesAlongEachSide = 4;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = 2))` — Number of vertices to use along each axis when creating a mesh for each sphere
- L189 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput, DataflowRenderGroups = ""))` — Single mesh aggregating all the spheres together
- L193 _private member_ `TArray<TObjectPtr<UDynamicMesh>> Meshes;` — `UPROPERTY(meta = (DataflowOutput))` — Array of meshes for each spheres found
- L195 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L198 _public prototype_ `FSpheresToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Dataflow`
- L202 _namespace_ `namespace UE`
- L202 _namespace_ `namespace Dataflow` (scope `UE`)
- L204 _prototype_ `void GeometryCollectionDebugNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionEditNodes.h` (Public)


#### struct `FPruneInCollectionDataflowNode`  
`struct FPruneInCollectionDataflowNode : public FDataflowNode`  
_L22-46_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Deletes selected bones from Collection. Empty clusters will be eliminated
- L30 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Fractured GeometryCollection to prune
- L34 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection", DataflowIntrinsic))` — Transform selection for pruning
- L36 _public function_ `FPruneInCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L44 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EVisibiltyOptionsEnum`  
`enum class EVisibiltyOptionsEnum : uint8`  
_L50-57_
- reflection: `UENUM(BlueprintType)`
- L52 _public enumerator_ `Dataflow_VisibilityOptions_Visible UMETA(DisplayName = "Visible")`
- L53 _public enumerator_ `Dataflow_VisibilityOptions_Invisible UMETA(DisplayName = "Hidden")`
- L56 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FSetVisibilityInCollectionDataflowNode`  
`struct FSetVisibilityInCollectionDataflowNode : public FDataflowNode`  
_L65-98_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Sets all selected bone's visibilty to Visible/Hidden
- L73 _public member_ `EVisibiltyOptionsEnum Visibility = EVisibiltyOptionsEnum::Dataflow_VisibilityOptions_Invisible;` — `UPROPERTY(EditAnywhere, Category = "Visibility")` — What to set the visibility of the selected bones
- L77 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Fractured GeometryCollection to set visibility
- L81 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Transform selection for setting visibility
- L85 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Face selection for setting visibility
- L87 _public function_ `FSetVisibilityInCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L96 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMergeInCollectionDataflowNode`  
`struct FMergeInCollectionDataflowNode : public FDataflowNode`  
_L107-131_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Merges selected bones into a single bone
- L115 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Fractured GeometryCollection to merge
- L119 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection", DataflowIntrinsic))` — Transform selection for merging
- L121 _public function_ `FMergeInCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L129 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Dataflow`
- L134 _namespace_ `namespace UE`
- L134 _namespace_ `namespace Dataflow` (scope `UE`)
- L136 _prototype_ `void GeometryCollectionEditNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionEmbedNodes.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Dataflow`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Dataflow` (scope `UE`)
- L21 _prototype_ `void GeometryCollectionEmbedNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionFieldNodes.h` (Public)


#### enum `EDataflowFieldFalloffType`  
`enum class EDataflowFieldFalloffType : uint8`  
_L21-31_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `Dataflow_FieldFalloffType_None UMETA(DisplayName = "None", ToolTip = "No falloff function is used")`
- L24 _public enumerator_ `Dataflow_FieldFalloffType_Linear UMETA(DisplayName = "Linear", ToolTip = "The falloff function will be proportional to x")`
- L25 _public enumerator_ `Dataflow_FieldFalloffType_Inverse UMETA(DisplayName = "Inverse", ToolTip = "The falloff function will be proportional to 1.0/x")`
- L26 _public enumerator_ `Dataflow_FieldFalloffType_Squared UMETA(DisplayName = "Squared", ToolTip = "The falloff function will be proportional to x*x")`
- L27 _public enumerator_ `Dataflow_FieldFalloffType_Logarithmic UMETA(DisplayName = "Logarithmic", ToolTip = "The falloff function will be proportional to log(x)")`
- L30 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FRadialFalloffFieldDataflowNode`  
`struct FRadialFalloffFieldDataflowNode : public FDataflowNode`  
_L40-116_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: RadialFalloff Field Dataflow node
- L47 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L51 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L55 _public member_ `FSphere Sphere = FSphere(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L59 _public member_ `FVector Translation = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L63 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L67 _public member_ `float MinRange = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L71 _public member_ `float MaxRange = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L75 _public member_ `float Default = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L79 _public member_ `EDataflowFieldFalloffType FalloffType = EDataflowFieldFalloffType::Dataflow_FieldFalloffType_Linear;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L83 _public member_ `TArray<float> FieldFloatResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L87 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L91 _public member_ `FDataflowVertexSelection FieldSelectionMask;` — `UPROPERTY(meta = (DataflowOutput))`
- L95 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L97 _public function_ `FRadialFalloffFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L114 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoxFalloffFieldDataflowNode`  
`struct FBoxFalloffFieldDataflowNode : public FDataflowNode`  
_L125-201_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: BoxFalloff Field Dataflow node
- L132 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L136 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L140 _public member_ `FBox Box = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L144 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L148 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L152 _public member_ `float MinRange = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L156 _public member_ `float MaxRange = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L160 _public member_ `float Default = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L164 _public member_ `EDataflowFieldFalloffType FalloffType = EDataflowFieldFalloffType::Dataflow_FieldFalloffType_Linear;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L168 _public member_ `TArray<float> FieldFloatResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L172 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L176 _public member_ `FDataflowVertexSelection FieldSelectionMask;` — `UPROPERTY(meta = (DataflowOutput))`
- L180 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L182 _public function_ `FBoxFalloffFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L199 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FPlaneFalloffFieldDataflowNode`  
`struct FPlaneFalloffFieldDataflowNode : public FDataflowNode`  
_L210-297_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: PlaneFalloff Field Dataflow node
- L218 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L222 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L226 _public member_ `FVector Position = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L230 _public member_ `FVector Normal = FVector(0.f, 0.f, 1.f);` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L234 _public member_ `float Distance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L238 _public member_ `FVector Translation = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L242 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L246 _public member_ `float MinRange = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L250 _public member_ `float MaxRange = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L254 _public member_ `float Default = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L258 _public member_ `EDataflowFieldFalloffType FalloffType = EDataflowFieldFalloffType::Dataflow_FieldFalloffType_Linear;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L262 _public member_ `TArray<float> FieldFloatResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L266 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L270 _public member_ `FDataflowVertexSelection FieldSelectionMask;` — `UPROPERTY(meta = (DataflowOutput))`
- L274 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L276 _public function_ `FPlaneFalloffFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L295 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowSetMaskConditionType`  
`enum class EDataflowSetMaskConditionType : uint8`  
_L306-314_
- reflection: `UENUM(BlueprintType)`
- L308 _public enumerator_ `Dataflow_SetMaskConditionType_Always UMETA(DisplayName = "Set Always", ToolTip = "The particle output value will be equal to Interior-value if the particle position is inside a sphere / Exterior-value otherwise.")`
- L309 _public enumerator_ `Dataflow_SetMaskConditionType_IFF_NOT_Interior UMETA(DisplayName = "Merge Interior", ToolTip = "The particle output value will be equal to Interior-value if the particle position is inside the sphere or if the particle input value is already Interior-Value / Exterior-value otherwise.")`
- L310 _public enumerator_ `Dataflow_SetMaskConditionType_IFF_NOT_Exterior UMETA(DisplayName = "Merge Exterior", ToolTip = "The particle output value will be equal to Exterior-value if the particle position is outside the sphere or if the particle input value is already Exterior-Value / Interior-value otherwise.")`
- L313 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FRadialIntMaskFieldDataflowNode`  
`struct FRadialIntMaskFieldDataflowNode : public FDataflowNode`  
_L322-384_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: RadialIntMask Field Dataflow node
- L330 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L334 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L338 _public member_ `FSphere Sphere = FSphere(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L342 _public member_ `FVector Translation = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L346 _public member_ `int32 InteriorValue = 1;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L350 _public member_ `int32 ExteriorValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L354 _public member_ `EDataflowSetMaskConditionType SetMaskConditionType = EDataflowSetMaskConditionType::Dataflow_SetMaskConditionType_Always;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L358 _public member_ `TArray<int32> FieldIntResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L362 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L366 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L368 _public function_ `FRadialIntMaskFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L382 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FUniformScalarFieldDataflowNode`  
`struct FUniformScalarFieldDataflowNode : public FDataflowNode`  
_L393-436_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: UniformScalar Field Dataflow node
- L401 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L405 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L409 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L413 _public member_ `TArray<float> FieldFloatResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L417 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L421 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L423 _public function_ `FUniformScalarFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L434 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FUniformVectorFieldDataflowNode`  
`struct FUniformVectorFieldDataflowNode : public FDataflowNode`  
_L445-493_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: UniformVector Field Dataflow node
- L453 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L457 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L461 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L465 _public member_ `FVector Direction = FVector(1.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L469 _public member_ `TArray<FVector> FieldVectorResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L473 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L477 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L479 _public function_ `FUniformVectorFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L491 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRadialVectorFieldDataflowNode`  
`struct FRadialVectorFieldDataflowNode : public FDataflowNode`  
_L502-550_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: RadialVector Field Dataflow node
- L510 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L514 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L518 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L522 _public member_ `FVector Position = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L526 _public member_ `TArray<FVector> FieldVectorResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L530 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L534 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L536 _public function_ `FRadialVectorFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L548 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRandomVectorFieldDataflowNode`  
`struct FRandomVectorFieldDataflowNode : public FDataflowNode`  
_L559-602_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: RandomVector Field Dataflow node
- L567 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L571 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L575 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L579 _public member_ `TArray<FVector> FieldVectorResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L583 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L587 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L589 _public function_ `FRandomVectorFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L600 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FNoiseFieldDataflowNode`  
`struct FNoiseFieldDataflowNode : public FDataflowNode`  
_L611-664_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Noise Field Dataflow node
- L619 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L623 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L627 _public member_ `float MinRange = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L631 _public member_ `float MaxRange = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L635 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L639 _public member_ `TArray<float> FieldFloatResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L643 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L647 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L649 _public function_ `FNoiseFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L662 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FUniformIntegerFieldDataflowNode`  
`struct FUniformIntegerFieldDataflowNode : public FDataflowNode`  
_L673-716_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: UniformInteger Field Dataflow node
- L681 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L685 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L689 _public member_ `int32 Magnitude = 0;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L693 _public member_ `TArray<int32> FieldIntResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L697 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L701 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L703 _public function_ `FUniformIntegerFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L714 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowWaveFunctionType`  
`enum class EDataflowWaveFunctionType : uint8`  
_L725-734_
- reflection: `UENUM(BlueprintType)`
- L727 _public enumerator_ `Dataflow_WaveFunctionType_Cosine UMETA(DisplayName = "Cosine", ToolTip = "Cosine wave that will move in time.")`
- L728 _public enumerator_ `Dataflow_WaveFunctionType_Gaussian UMETA(DisplayName = "Gaussian", ToolTip = "Gaussian wave that will move in time.")`
- L729 _public enumerator_ `Dataflow_WaveFunctionType_Falloff UMETA(DisplayName = "Falloff", ToolTip = "The radial falloff radius will move along temporal wave.")`
- L730 _public enumerator_ `Dataflow_WaveFunctionType_Decay UMETA(DisplayName = "Decay", ToolTip = "The magnitude of the field will decay in time.")`
- L733 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FWaveScalarFieldDataflowNode`  
`struct FWaveScalarFieldDataflowNode : public FDataflowNode`  
_L742-813_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: WaveScalar Field Dataflow node v2
- L750 _public member_ `TArray<FVector3f> SamplePositions;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L754 _public member_ `FDataflowVertexSelection SampleIndices;` — `UPROPERTY(meta = (DataflowInput))`
- L758 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L762 _public member_ `FVector Position = FVector(0.f);` — `UPROPERTY(meta = (DataflowInput))`
- L766 _public member_ `FVector Translation = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L770 _public member_ `float Wavelength = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L774 _public member_ `float Period = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L778 _public member_ `EDataflowWaveFunctionType FunctionType = EDataflowWaveFunctionType::Dataflow_WaveFunctionType_Cosine;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L782 _public member_ `EDataflowFieldFalloffType FalloffType = EDataflowFieldFalloffType::Dataflow_FieldFalloffType_Linear;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L786 _public member_ `TArray<float> FieldFloatResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L790 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L794 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L796 _public function_ `FWaveScalarFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L811 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowFloatFieldOperationType`  
`enum class EDataflowFloatFieldOperationType : uint8`  
_L822-833_
- reflection: `UENUM(BlueprintType)`
- L824 _public enumerator_ `Dataflow_FloatFieldOperationType_Multiply UMETA(DisplayName = "Multiply", ToolTip = "Multiply the fields output values : Output = Left * Right")`
- L825 _public enumerator_ `Dataflow_FloatFieldFalloffType_Divide UMETA(DisplayName = "Divide", ToolTip = "Divide the fields output values : Output = Left / Right")`
- L826 _public enumerator_ `Dataflow_FloatFieldFalloffType_Add UMETA(DisplayName = "Add", ToolTip = "Add the fields output values : Output = Left + Right")`
- L827 _public enumerator_ `Dataflow_FloatFieldFalloffType_Substract UMETA(DisplayName = "Subtract", ToolTip = "Subtract the fields output : Output = Left - Right")`
- L828 _public enumerator_ `Dataflow_FloatFieldFalloffType_Min UMETA(DisplayName = "Min", ToolTip = "Min of the fields output values: Output = Min(Left, Right)")`
- L829 _public enumerator_ `Dataflow_FloatFieldFalloffType_Max UMETA(DisplayName = "Max", ToolTip = "Max of the fields output values: Output = Max(Left, Right)")`
- L832 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FSumScalarFieldDataflowNode`  
`struct FSumScalarFieldDataflowNode : public FDataflowNode`  
_L842-895_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L849 _public member_ `TArray<float> FieldFloatLeft;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L853 _public member_ `TArray<int32> FieldRemapLeft;` — `UPROPERTY(meta = (DataflowInput))`
- L856 _public member_ `TArray<float> FieldFloatRight;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L860 _public member_ `TArray<int32> FieldRemapRight;` — `UPROPERTY(meta = (DataflowInput))`
- L864 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L868 _public member_ `EDataflowFloatFieldOperationType Operation = EDataflowFloatFieldOperationType::Dataflow_FloatFieldFalloffType_Add;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L872 _public member_ `bool bSwapInputs = false;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L876 _public member_ `TArray<float> FieldFloatResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L880 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L882 _public function_ `FSumScalarFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L893 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowVectorFieldOperationType`  
`enum class EDataflowVectorFieldOperationType : uint8`  
_L904-914_
- reflection: `UENUM(BlueprintType)`
- L906 _public enumerator_ `Dataflow_VectorFieldOperationType_Multiply UMETA(DisplayName = "Multiply", ToolTip = "Multiply the fields output values : Output = Left * Right")`
- L907 _public enumerator_ `Dataflow_VectorFieldFalloffType_Divide UMETA(DisplayName = "Divide", ToolTip = "Divide the fields output values : Output = Left / Right")`
- L908 _public enumerator_ `Dataflow_VectorFieldFalloffType_Add UMETA(DisplayName = "Add", ToolTip = "Add the fields output values : Output = Left + Right")`
- L909 _public enumerator_ `Dataflow_VectorFieldFalloffType_Substract UMETA(DisplayName = "Subtract", ToolTip = "Subtract the fields output : Output = Left - Right")`
- L910 _public enumerator_ `Dataflow_VectorFieldFalloffType_CrossProduct UMETA(DisplayName = "Cross product", ToolTip = "Cross product of the fields output values: Output = Left x Right")`
- L913 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FSumVectorFieldDataflowNode`  
`struct FSumVectorFieldDataflowNode : public FDataflowNode`  
_L922-984_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L929 _public member_ `TArray<float> FieldFloat;` — `UPROPERTY(meta = (DataflowInput))`
- L933 _public member_ `TArray<int32> FieldFloatRemap;` — `UPROPERTY(meta = (DataflowInput))`
- L936 _public member_ `TArray<FVector> FieldVectorLeft;` — `UPROPERTY(meta = (DataflowInput))`
- L940 _public member_ `TArray<int32> FieldRemapLeft;` — `UPROPERTY(meta = (DataflowInput))`
- L943 _public member_ `TArray<FVector> FieldVectorRight;` — `UPROPERTY(meta = (DataflowInput))`
- L947 _public member_ `TArray<int32> FieldRemapRight;` — `UPROPERTY(meta = (DataflowInput))`
- L951 _public member_ `float Magnitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput))`
- L955 _public member_ `EDataflowVectorFieldOperationType Operation = EDataflowVectorFieldOperationType::Dataflow_VectorFieldFalloffType_Add;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L958 _public member_ `bool bSwapVectorInputs = false;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L962 _public member_ `TArray<FVector> FieldVectorResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L966 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowOutput))`
- L968 _public function_ `FSumVectorFieldDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L982 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFieldMakeDenseFloatArrayDataflowNode`  
`struct FFieldMakeDenseFloatArrayDataflowNode : public FDataflowNode`  
_L996-1032_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Converts a sparse FloatArray (a selected subset of the whole incoming array) into a dense FloatArray (same number of elements as the incoming array using NumSamplePositions) using the Remap input NumSamplePositions controls the size of the output array, only indices smaller than l to than NumSamplePositions will be processed
- L1003 _public member_ `TArray<float> FieldFloatInput;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L1007 _public member_ `TArray<int32> FieldRemap;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L1011 _public member_ `int32 NumSamplePositions = 0;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (DataflowInput, DisplayName = "Number of Sample Positions"))`
- L1015 _public member_ `float Default = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Field")`
- L1019 _public member_ `TArray<float> FieldFloatResult;` — `UPROPERTY(meta = (DataflowOutput))`
- L1021 _public function_ `FFieldMakeDenseFloatArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1030 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Dataflow`
- L1034 _namespace_ `namespace UE`
- L1034 _namespace_ `namespace Dataflow` (scope `UE`)
- L1036 _prototype_ `void GeometryCollectionFieldNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionFracturingNodes.h` (Public)


#### struct `FUniformScatterPointsDataflowNode`  
`struct FUniformScatterPointsDataflowNode : public FDataflowNode`  
_L21-54_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- L28 _public member_ `int32 MinNumberOfPoints = 20;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 1))`
- L31 _public member_ `int32 MaxNumberOfPoints = 20;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 1))`
- L34 _public member_ `float RandomSeed = -1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))`
- L37 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))`
- L40 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))`
- L42 _public function_ `FUniformScatterPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L52 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FUniformScatterPointsDataflowNode_v2`  
`struct FUniformScatterPointsDataflowNode_v2 : public FDataflowNode`  
_L57-95_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L65 _public member_ `int32 MinNumberOfPoints = 20;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 1))` — Minimum for the random range
- L69 _public member_ `int32 MaxNumberOfPoints = 20;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 1))` — Maximum for the random range
- L73 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L77 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))` — BoundingBox to generate points inside of
- L81 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Generated points
- L83 _public function_ `FUniformScatterPointsDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L93 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FClusterScatterPointsDataflowNode`  
`struct FClusterScatterPointsDataflowNode : public FDataflowNode`  
_L98-155_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L107 _private member_ `int32 NumberClustersMin = 8;` — `UPROPERTY(EditAnywhere, Category = Scatter, meta = (DisplayName = "Min Num Clusters", UIMax = "200", ClampMin = "1", DataflowInput))` — Minimum number of clusters of points to create. The amount of clusters created will be chosen at random between Min and Max
- L111 _private member_ `int32 NumberClustersMax = 8;` — `UPROPERTY(EditAnywhere, Category = Scatter, meta = (DisplayName = "Max Num Clusters", UIMax = "200", ClampMin = "1", DataflowInput))` — Maximum number of clusters of points to create. The amount of clusters created will be chosen at random between Min and Max
- L115 _private member_ `int32 PointsPerClusterMin = 2;` — `UPROPERTY(EditAnywhere, Category = Scatter, meta = (DisplayName = "Min Points Per Cluster", UIMax = "200", ClampMin = "0", DataflowInput))` — Minimum number of points per cluster. The amount of points in each cluster will be chosen at random between Min and Max
- L119 _private member_ `int32 PointsPerClusterMax = 30;` — `UPROPERTY(EditAnywhere, Category = Scatter, meta = (DisplayName = "Max Points Per Cluster", UIMax = "200", ClampMin = "0", DataflowInput))` — Maximum number of points per cluster. The amount of points in each cluster will be chosen at random between Min and Max
- L126 _private member_ `float ClusterRadiusFractionMin = .1f;` — `UPROPERTY(EditAnywhere, Category = Scatter, meta = (DisplayName = "Min Dist from Center (as Frac of Bounds)", ClampMin = "0.0", UIMax = "1.0", DataflowInput))` — Minimum cluster radius (as fraction of the overall bounding box size). Cluster Radius Offset will be added to this. Each point will be placed at least this far (plus the Cluster Radius Offset) from its cluster center.
- L133 _private member_ `float ClusterRadiusFractionMax = .2f;` — `UPROPERTY(EditAnywhere, Category = Scatter, meta = (DisplayName = "Max Dist from Center (as Frac of Bounds)", ClampMin = "0.0", UIMax = "1.0", DataflowInput))` — Maximum cluster radius (as fraction of the overall bounding box size). Cluster Radius Offset will be added to this. Each point will be placed at most this far (plus the Cluster Radius Offset) from its cluster center.
- L137 _private member_ `float ClusterRadiusOffset = 0;` — `UPROPERTY(EditAnywhere, Category = Scatter, meta = (Units = "cm", DataflowInput))` — Cluster radius offset (in cm). This offset will be added to the 'Min/Max Dist from Center' distance
- L141 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = Scatter, meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L145 _private member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))` — BoundingBox to generate points inside of
- L149 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Generated points
- L151 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L154 _public prototype_ `FClusterScatterPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FRadialScatterPointsDataflowNode`  
`struct FRadialScatterPointsDataflowNode : public FDataflowNode`  
_L158-207_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- L165 _public member_ `FVector Center = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))`
- L168 _public member_ `FVector Normal = FVector(0.0, 0.0, 1.0);` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))`
- L171 _public member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 0.01f))`
- L174 _public member_ `int32 AngularSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 1, UIMax = 50))`
- L177 _public member_ `int32 RadialSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 1, UIMax = 50))`
- L180 _public member_ `float AngleOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))`
- L183 _public member_ `float Variability = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 0.f))`
- L186 _public member_ `float RandomSeed = -1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))`
- L189 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))`
- L191 _public function_ `FRadialScatterPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L205 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRadialScatterPointsDataflowNode_v2`  
`struct FRadialScatterPointsDataflowNode_v2 : public FDataflowNode`  
_L210-302_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L218 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))` — BoundingBox to generate points inside of
- L222 _public member_ `FVector Center = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))` — Center of generated pattern
- L226 _public member_ `FVector Normal = FVector(0.0, 0.0, 1.0);` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))` — Normal to plane in which sites are generated
- L230 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L234 _public member_ `int32 AngularSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = 1, UIMax = 50, ClampMin = "1"))` — Number of angular steps
- L238 _public member_ `float AngleOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))` — Angle offset at each radial step (in degrees)
- L242 _public member_ `float AngularNoise = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))` — Amount of global variation to apply to each angular step (in degrees)
- L246 _public member_ `float Radius = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = "0.0", ClampMin = "0.0"))` — Pattern radius (in cm)
- L250 _public member_ `int32 RadialSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = "1", UIMax = "50", ClampMin = "1"))` — Number of radial steps
- L254 _public member_ `float RadialStepExponent = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = ".01", UIMax = "10", ClampMin = ".01", ClampMax = "20"))` — Radial steps will follow a distribution based on this exponent, i.e., Pow(distance from center, RadialStepExponent)
- L258 _public member_ `float RadialMinStep = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = ".25", ClampMin = ".01"))` — Minimum radial separation between any two voronoi points (in cm)
- L262 _public member_ `float RadialNoise = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = "0"))` — Amount of global variation to apply to each radial step (in cm)
- L266 _public member_ `float RadialVariability = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Per Point Variability", meta = (DataflowInput, ClampMin = "0.0"))` — Amount to randomly displace each Voronoi site radially (in cm)
- L270 _public member_ `float AngularVariability = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Per Point Variability", meta = (DataflowInput, ClampMin = "0.0"))` — Amount to randomly displace each Voronoi site in angle (in degrees)
- L274 _public member_ `float AxialVariability = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Per Point Variability", meta = (DataflowInput, ClampMin = "0.0"))` — Amount to randomly displace each Voronoi site in the direction of the rotation axis (in cm)
- L278 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Generated points
- L280 _public function_ `FRadialScatterPointsDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L301 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGridScatterPointsDataflowNode`  
`struct FGridScatterPointsDataflowNode : public FDataflowNode`  
_L305-362_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L313 _public member_ `int32 NumberOfPointsInX = 5;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = "0", UIMax = "100", ClampMax = "200"))` — Number of points in X direction
- L317 _public member_ `int32 NumberOfPointsInY = 5;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = "0", UIMax = "100", ClampMax = "200"))` — Number of points in Y direction
- L321 _public member_ `int32 NumberOfPointsInZ = 5;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = "0", UIMax = "100", ClampMax = "200"))` — Number of points in Z direction
- L325 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L329 _public member_ `float MaxRandomDisplacementX = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = "0.0"))` — Random displacement in X direction will be in the range (-MaxRandomDisplacementX, MaxRandomDisplacementX)
- L333 _public member_ `float MaxRandomDisplacementY = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = "0.0"))` — Random displacement in Y direction will be in the range (-MaxRandomDisplacementY, MaxRandomDisplacementY)
- L337 _public member_ `float MaxRandomDisplacementZ = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, UIMin = "0.0"))` — Random displacement in Z direction will be in the range (-MaxRandomDisplacementZ, MaxRandomDisplacementZ)
- L341 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))` — BoundingBox to generate points inside of
- L345 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Generated points
- L347 _public function_ `FGridScatterPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L361 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FTransformPointsDataflowNode`  
`struct FTransformPointsDataflowNode : public FDataflowNode`  
_L368-384_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Transform an array of points
- L375 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput, DataflowInput, DataflowPassthrough = Points, DataflowIntrinsic))`
- L378 _private member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput))`
- L380 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L383 _public prototype_ `FTransformPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FAppendPointsDataflowNode`  
`struct FAppendPointsDataflowNode : public FDataflowNode`  
_L390-409_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Combine two arrays of points into one
- L397 _private member_ `TArray<FVector> PointsA;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L400 _private member_ `TArray<FVector> PointsB;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L403 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = PointsA))`
- L405 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L408 _public prototype_ `FAppendPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVoronoiFractureDataflowNode`  
`struct FVoronoiFractureDataflowNode : public FDataflowNode`  
_L418-491_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Voronoi fracture Fracture using a Voronoi diagram with a uniform random pattern, creating fracture pieces of similar volume across the shape.
- L425 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))`
- L428 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L432 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection", DataflowIntrinsic))`
- L435 _public member_ `float RandomSeed = -1.f;` — `UPROPERTY(EditAnywhere, Category = "Fracture", meta = (DataflowInput))`
- L438 _public member_ `float ChanceToFracture = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Fracture", meta = (DataflowInput, UIMin = 0.f, UIMax = 1.f))`
- L441 _public member_ `bool GroupFracture = true;` — `UPROPERTY(EditAnywhere, Category = "Fracture")`
- L444 _public member_ `float Grout = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Fracture", meta = (DataflowInput, UIMin = 0.f))`
- L447 _public member_ `float Amplitude = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L450 _public member_ `float Frequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.00001f))`
- L453 _public member_ `float Persistence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L456 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L459 _public member_ `int32 OctaveNumber = 4;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L462 _public member_ `float PointSpacing = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L465 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")`
- L468 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, UIMin = 0.f))`
- L470 _public function_ `FVoronoiFractureDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L489 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FVoronoiFractureDataflowNode_v2`  
`struct FVoronoiFractureDataflowNode_v2 : public FDataflowNode`  
_L500-616_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Voronoi fracture Fracture using a Voronoi diagram with a uniform random pattern, creating fracture pieces of similar volume across the shape.
- L508 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to fracture
- L512 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Voronoi source points
- L516 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "TransformSelection", DisplayName = "TransformSelection"))` — Pieces to fracture
- L520 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Transform"))` — Transform to apply to cut planes
- L525 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY()` — Seed for random
- L529 _public member_ `float ChanceToFracture = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Chance to fracture each selected bone. If 0, no bones will fracture; if 1, all bones will fracture.
- L533 _public member_ `bool SplitIslands = true;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands")` — Whether to split the fractured mesh pieces into separate islands based on geometric connectivity after fracturing
- L537 _public member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L541 _public member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L545 _public member_ `float Grout = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f))` — Amount of space to leave between cut pieces
- L549 _public member_ `float Amplitude = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Size of the Perlin noise displacement (in cm). If 0, no noise will be applied
- L553 _public member_ `float Frequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.00001f))` — Period of the Perlin noise.  Smaller values will create a smoother noise pattern
- L557 _public member_ `float Persistence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Persistence of the layers of Perlin noise. At each layer (octave) after the first, the amplitude of the Perlin noise is scaled by this factor
- L561 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Lacunarity of the layers of Perlin noise. At each layer (octave) after the first, the frequency of the Perlin noise is scaled by this factor
- L568 _public member_ `int32 OctaveNumber = 4;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Number of fractal layers of Perlin noise to apply. Each layer is additive, with Amplitude and Frequency parameters scaled by Persistence and Lacunarity Smaller values (1 or 2) will create noise that looks like gentle rolling hills, while larger values (> 4) will tend to look more like craggy mountains
- L572 _public member_ `float PointSpacing = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Distance (in cm) between vertices on cut surfaces where noise is added.  Larger spacing between vertices will create more efficient meshes with fewer triangles, but less resolution to see the shape of the added noise
- L581 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L588 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, UIMin = 0.f, EditCondition = "AddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L592 _public member_ `FDataflowTransformSelection NewGeometryTransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FracturedTransformSelection "))` — Fractured Pieces
- L594 _public function_ `FVoronoiFractureDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L615 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FPlaneCutterDataflowNode`  
`struct FPlaneCutterDataflowNode : public FDataflowNode`  
_L625-695_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Fracture / Planar tool Fracture using a set of noised up planes.
- L632 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))`
- L635 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L639 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection", DataflowIntrinsic))`
- L642 _public member_ `int32 NumPlanes = 1;` — `UPROPERTY(EditAnywhere, Category = "Fracture", meta = (DataflowInput, UIMin = 1))`
- L645 _public member_ `float RandomSeed = -1.f;` — `UPROPERTY(EditAnywhere, Category = "Fracture", meta = (DataflowInput))`
- L648 _public member_ `float Grout = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Fracture", meta = (DataflowInput, UIMin = 0.f))`
- L651 _public member_ `float Amplitude = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L654 _public member_ `float Frequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.00001f))`
- L657 _public member_ `float Persistence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L660 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L663 _public member_ `int32 OctaveNumber = 4;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L666 _public member_ `float PointSpacing = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))`
- L669 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")`
- L672 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, UIMin = 0.f))`
- L674 _public function_ `FPlaneCutterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L694 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FPlaneCutterDataflowNode_v2`  
`struct FPlaneCutterDataflowNode_v2 : public FDataflowNode`  
_L704-857_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Fracture / Planar tool Fracture using a set of noised up planes.
- L712 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to fracture
- L716 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))` — Bound for plane centers
- L720 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "TransformSelection", DisplayName = "TransformSelection"))` — Pieces to cut
- L724 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Transform Collection to Plane Space"))` — Transform to bring the collection into the space of the cutting planes
- L728 _public member_ `TArray<FTransform> CutPlanes;` — `UPROPERTY(EditAnywhere, Category = "Plane Cut", meta = (DataflowInput))` — Cutting planes to use. The cut plane normal is aligned to the Z-up of the transform.
- L732 _public member_ `int32 NumPlanes = 0;` — `UPROPERTY(EditAnywhere, Category = "Plane Cut", meta = (DataflowInput, DisplayName = "Add Random Cuts", ClampMin = 0))` — Number of random cutting planes to add, in addition to those specified in the Cut Planes array
- L736 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L740 _public member_ `float ChanceToFracture = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f, DisplayName = "Chance To Fracture Per Bone", UIMax = 1.f))` — Chance to fracture each selected bone. If 0, no bones will fracture; if 1, all bones will fracture.
- L744 _public member_ `bool SplitIslands = true;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands")` — Whether to split the fractured mesh pieces into separate islands based on geometric connectivity after fracturing
- L748 _public member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L752 _public member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L756 _public member_ `float Grout = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f))` — Amount of space to leave between cut pieces
- L760 _public member_ `float Amplitude = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Size of the Perlin noise displacement (in cm). If 0, no noise will be applied
- L764 _public member_ `float Frequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.00001f))` — Period of the Perlin noise.  Smaller values will create a smoother noise pattern
- L768 _public member_ `float Persistence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Persistence of the layers of Perlin noise. At each layer (octave) after the first, the amplitude of the Perlin noise is scaled by this factor
- L772 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Lacunarity of the layers of Perlin noise. At each layer (octave) after the first, the frequency of the Perlin noise is scaled by this factor
- L779 _public member_ `int32 OctaveNumber = 4;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Number of fractal layers of Perlin noise to apply. Each layer is additive, with Amplitude and Frequency parameters scaled by Persistence and Lacunarity Smaller values (1 or 2) will create noise that looks like gentle rolling hills, while larger values (> 4) will tend to look more like craggy mountains
- L783 _public member_ `float PointSpacing = 20.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Distance (in cm) between vertices on cut surfaces where noise is added.  Larger spacing between vertices will create more efficient meshes with fewer triangles, but less resolution to see the shape of the added noise
- L792 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L799 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, UIMin = 0.f, EditCondition = "AddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L802 _public member_ `EDataflowDebugDrawRenderType RenderType = EDataflowDebugDrawRenderType::Wireframe;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")`
- L805 _public member_ `float PlaneSizeMultiplier = 2.2f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (UIMin = "1.0", UIMax = "10.0", ClampMin = "1.0", ClampMax = "10.0"))`
- L808 _public member_ `bool bTranslucent = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (EditCondition = "RenderType==EDataflowDebugDrawRenderType::Shaded"))`
- L811 _public member_ `bool bRandomizeColors = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")`
- L814 _public member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (UIMin = "0"))`
- L817 _public member_ `float LineWidthMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (UIMin = "0.1", UIMax = "10.0", ClampMin = "0.1", ClampMax = "10.0"))`
- L821 _public member_ `FDataflowTransformSelection NewGeometryTransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FracturedTransformSelection "))` — Fractured Pieces
- L823 _public function_ `FPlaneCutterDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L847 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L850 _public function_ `virtual bool CanDebugDraw() const override`
- L854 _public prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L855 _public prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FExplodedViewDataflowNode`  
`struct FExplodedViewDataflowNode : public FDataflowNode`  
_L865-908_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: "Explodes" the pieces from the Collection for better visualization
- L873 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to explode
- L877 _public member_ `float UniformScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (DataflowInput))` — Scale amount to expand the pieces uniformly in all directions
- L881 _public member_ `FVector Scale = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (DataflowInput))` — Scale amounts to expand the pieces in all 3 directions
- L885 _public member_ `FVector Offset = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Exploded View", meta = (DataflowInput))` — Translate collection for exploded view
- L887 _public function_ `FExplodedViewDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L903 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L907 _private prototype_ `static bool GetValidGeoCenter(FGeometryCollection* Collection, const TManagedArray<int32>& TransformToGeometryIndex, const TArray<FTransform>& Transforms, const TManagedArray<TSet<int32>>& Children, const TManagedArray<FBox>& BoundingBox, int32 TransformIndex, FVector& OutGeoCenter);` — todo(chaos) this is a copy of a function in FractureEditorModeToolkit, we should move this to a common place

#### struct `FSliceCutterDataflowNode`  
`struct FSliceCutterDataflowNode : public FDataflowNode`  
_L917-1052_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Fracture / Slice tool Fracture with a grid of X, Y, and Z slices, with optional random variation in angle and offset.
- L925 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to fracture
- L928 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L932 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "TransformSelection", DisplayName = "TransformSelection"))` — The selected pieces to cut
- L936 _public member_ `int32 SlicesX = 3;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (DataflowInput, UIMin = "0"))` — Number of slices along the X axis
- L940 _public member_ `int32 SlicesY = 3;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (DataflowInput, UIMin = "0"))` — Number of slices along the Y axis
- L944 _public member_ `int32 SlicesZ = 1;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (DataflowInput, UIMin = "0"))` — Number of slices along the Z axis
- L948 _public member_ `float SliceAngleVariation = 0.f;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (DataflowInput, DisplayName = "Random Angle Variation", UIMin = "0.0", UIMax = "90.0"))` — Maximum angle (in degrees) to randomly rotate each slicing plane
- L952 _public member_ `float SliceOffsetVariation = 0.f;` — `UPROPERTY(EditAnywhere, Category = Slicing, meta = (DataflowInput, DisplayName = "Random Offset Variation", UIMin = "0.0"))` — Maximum distance (in cm) to randomly shift each slicing plane
- L956 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L960 _public member_ `float ChanceToFracture = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f, UIMax = 1.f))` — Chance to fracture each selected bone. If 0, no bones will fracture; if 1, all bones will fracture.
- L964 _public member_ `bool SplitIslands = true;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands")` — Whether to split the fractured mesh pieces into separate islands based on geometric connectivity after fracturing
- L968 _public member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L972 _public member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L976 _public member_ `float Grout = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f))` — Amount of space to leave between cut pieces
- L980 _public member_ `float Amplitude = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Size of the Perlin noise displacement (in cm). If 0, no noise will be applied
- L984 _public member_ `float Frequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.00001f))` — Period of the Perlin noise.  Smaller values will create a smoother noise pattern
- L988 _public member_ `float Persistence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Persistence of the layers of Perlin noise. At each layer (octave) after the first, the amplitude of the Perlin noise is scaled by this factor
- L992 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Lacunarity of the layers of Perlin noise. At each layer (octave) after the first, the frequency of the Perlin noise is scaled by this factor
- L999 _public member_ `int32 OctaveNumber = 4;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Number of fractal layers of Perlin noise to apply. Each layer is additive, with Amplitude and Frequency parameters scaled by Persistence and Lacunarity Smaller values (1 or 2) will create noise that looks like gentle rolling hills, while larger values (> 4) will tend to look more like craggy mountains
- L1003 _public member_ `float PointSpacing = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Distance (in cm) between vertices on cut surfaces where noise is added.  Larger spacing between vertices will create more efficient meshes with fewer triangles, but less resolution to see the shape of the added noise
- L1012 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L1019 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, UIMin = 0.f, EditCondition = "AddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L1023 _public member_ `FDataflowTransformSelection NewGeometryTransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FracturedTransformSelection "))` — Fractured Pieces
- L1025 _public function_ `FSliceCutterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1051 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBrickCutterDataflowNode`  
`struct FBrickCutterDataflowNode : public FDataflowNode`  
_L1062-1197_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Fracture / Brick tool Fracture with a customizable brick pattern. Note: Currently only supports fracturing with at least some (non-zero) Grout.
- L1070 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to cut
- L1074 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))` — Boundingbox to create the cutting planes in
- L1078 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "TransformSelection", DisplayName = "TransformSelection"))` — The selected pieces to cut
- L1082 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Transform"))` — Transform to apply to cut planes
- L1086 _public member_ `EFractureBrickBondEnum Bond = EFractureBrickBondEnum::Dataflow_FractureBrickBond_Stretcher;` — `UPROPERTY(EditAnywhere, Category = Brick)` — The brick bond pattern defines how the bricks are arranged
- L1090 _public member_ `float BrickLength = 194.f;` — `UPROPERTY(EditAnywhere, Category = Brick, meta = (DataflowInput, UIMin = "0.1", UIMax = "500.0", ClampMin = "0.001"))` — Brick length (in cm)
- L1094 _public member_ `float BrickHeight = 57.f;` — `UPROPERTY(EditAnywhere, Category = Brick, meta = (DataflowInput, UIMin = "0.1", UIMax = "500.0", ClampMin = "0.001"))` — Brick height (in cm)
- L1098 _public member_ `float BrickDepth = 92.f;` — `UPROPERTY(EditAnywhere, Category = Brick, meta = (DataflowInput, UIMin = "0.1", UIMax = "500.0", ClampMin = "0.001"))` — Brick depth (in cm)
- L1102 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L1106 _public member_ `float ChanceToFracture = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f, UIMax = 1.f))` — Chance to fracture each selected bone. If 0, no bones will fracture; if 1, all bones will fracture.
- L1110 _public member_ `bool SplitIslands = true;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands")` — Whether to split the fractured mesh pieces into separate islands based on geometric connectivity after fracturing
- L1114 _public member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L1118 _public member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L1122 _public member_ `float Grout = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f))` — Amount of space to leave between cut pieces
- L1126 _public member_ `float Amplitude = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Size of the Perlin noise displacement (in cm). If 0, no noise will be applied
- L1130 _public member_ `float Frequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.00001f))` — Period of the Perlin noise.  Smaller values will create a smoother noise pattern
- L1134 _public member_ `float Persistence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Persistence of the layers of Perlin noise. At each layer (octave) after the first, the amplitude of the Perlin noise is scaled by this factor
- L1138 _public member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Lacunarity of the layers of Perlin noise. At each layer (octave) after the first, the frequency of the Perlin noise is scaled by this factor
- L1145 _public member_ `int32 OctaveNumber = 4;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Number of fractal layers of Perlin noise to apply. Each layer is additive, with Amplitude and Frequency parameters scaled by Persistence and Lacunarity Smaller values (1 or 2) will create noise that looks like gentle rolling hills, while larger values (> 4) will tend to look more like craggy mountains
- L1149 _public member_ `float PointSpacing = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Distance (in cm) between vertices on cut surfaces where noise is added.  Larger spacing between vertices will create more efficient meshes with fewer triangles, but less resolution to see the shape of the added noise
- L1158 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L1165 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, UIMin = 0.f, EditCondition = "AddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L1169 _public member_ `FDataflowTransformSelection NewGeometryTransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FracturedTransformSelection "))` — Fractured Pieces
- L1171 _public function_ `FBrickCutterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1196 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMeshCutterDataflowNode`  
`struct FMeshCutterDataflowNode : public FDataflowNode`  
_L1206-1364_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Fracture / Mesh tool Fracture using the shape of a chosen static mesh and/or array of dynamic meshes
- L1214 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to cut
- L1218 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))` — Boundingbox to create the cutting planes in
- L1222 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "TransformSelection", DisplayName = "TransformSelection"))` — The selected pieces to cut
- L1226 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Transform"))` — Transform to apply to cut planes
- L1230 _public member_ `TArray<TObjectPtr<UDynamicMesh>> CuttingDynamicMeshes;` — `UPROPERTY(EditAnywhere, Category = "Mesh", meta = (DataflowInput))` — Dynamic Meshes to cut with
- L1234 _public member_ `TObjectPtr<UStaticMesh> CuttingStaticMesh;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DataflowInput))` — Static Mesh to cut with
- L1238 _public member_ `bool bUseHiRes = false;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DisplayName = "Use HiRes"))` — If using a Static Mesh to cut, attempt to use the Nanite HiRes source mesh, if available and non-empty.
- L1242 _public member_ `int32 LODLevel = 0;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DisplayName = "LOD Level"))` — If using a Static Mesh to cut, and not using the Nanite HiRes source mesh, use this LOD level's mesh
- L1246 _public member_ `EMeshCutterCutDistribution CutDistribution = EMeshCutterCutDistribution::SingleCut;` — `UPROPERTY(EditAnywhere, Category = Distribution)` — How to arrange the mesh cuts in space
- L1250 _public member_ `EMeshCutterPerCutMeshSelection PerCutMeshSelection = EMeshCutterPerCutMeshSelection::All;` — `UPROPERTY(EditAnywhere, Category = Distribution)` — When there are multiple cutting meshes, how to choose the cut mesh to apply at each location
- L1254 _public member_ `int32 NumberToScatter = 10;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, ClampMin = "1", UIMax = "5000", EditCondition = "CutDistribution == EMeshCutterCutDistribution::UniformRandom", EditConditionHides))` — Number of meshes to random scatter
- L1258 _public member_ `int32 GridX = 2;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, DisplayName = "Grid Width", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "CutDistribution == EMeshCutterCutDistribution::Grid", EditConditionHides))` — Number of meshes to add to grid in X
- L1262 _public member_ `int32 GridY = 2;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, DisplayName = "Grid Depth", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "CutDistribution == EMeshCutterCutDistribution::Grid", EditConditionHides))` — Number of meshes to add to grid in Y
- L1266 _public member_ `int32 GridZ = 2;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, DisplayName = "Grid Height", ClampMin = "1", UIMax = "100", ClampMax = "5000", EditCondition = "CutDistribution == EMeshCutterCutDistribution::Grid", EditConditionHides))` — Number of meshes to add to grid in Z
- L1270 _public member_ `float Variability = 0.f;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, DisplayName = "Variability", EditCondition = "CutDistribution == EMeshCutterCutDistribution::Grid", EditConditionHides, UIMin = "0.0", ClampMin = "0.0"))` — Magnitude of random displacement to cutting meshes
- L1274 _public member_ `float MinScaleFactor = .5;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, ClampMin = "0.001", EditCondition = "CutDistribution != EMeshCutterCutDistribution::SingleCut", EditConditionHides))` — Minimum scale factor to apply to cutting meshes. A random scale will be chosen between Min and Max
- L1278 _public member_ `float MaxScaleFactor = 1.5;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, ClampMin = "0.001", EditCondition = "CutDistribution != EMeshCutterCutDistribution::SingleCut", EditConditionHides))` — Maximum scale factor to apply to cutting meshes. A random scale will be chosen between Min and Max
- L1282 _public member_ `bool bRandomOrientation = true;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (EditCondition = "CutDistribution != EMeshCutterCutDistribution::SingleCut", EditConditionHides))` — Whether to randomly vary the orientation of the cutting meshes
- L1286 _public member_ `float RollRange = 180;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, DisplayName = "+/- Roll Range", EditCondition = "CutDistribution != EMeshCutterCutDistribution::SingleCut && bRandomOrientation", EditConditionHides, ClampMin = "0", ClampMax = "180"))` — Roll will be chosen between -Range and +Range
- L1290 _public member_ `float PitchRange = 180;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, DisplayName = "+/- Pitch Range", EditCondition = "CutDistribution != EMeshCutterCutDistribution::SingleCut && bRandomOrientation", EditConditionHides, ClampMin = "0", ClampMax = "180"))` — Pitch will be chosen between -Range and +Range
- L1294 _public member_ `float YawRange = 180;` — `UPROPERTY(EditAnywhere, Category = Distribution, meta = (DataflowInput, DisplayName = "+/- Yaw Range", EditCondition = "CutDistribution != EMeshCutterCutDistribution::SingleCut && bRandomOrientation", EditConditionHides, ClampMin = "0", ClampMax = "180"))` — Yaw will be chosen between -Range and +Range
- L1298 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = "0"))` — Seed for random
- L1302 _public member_ `float ChanceToFracture = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f, UIMax = 1.f))` — Chance to fracture each selected bone. If 0, no bones will fracture; if 1, all bones will fracture.
- L1306 _public member_ `bool SplitIslands = true;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands")` — Whether to split the fractured mesh pieces into separate islands based on geometric connectivity after fracturing
- L1310 _public member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L1314 _public member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L1323 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L1330 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, DisplayName = "Point Spacing", UIMin = 0.f, EditCondition = "AddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L1334 _public member_ `FDataflowTransformSelection NewGeometryTransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FracturedTransformSelection "))` — Fractured Pieces
- L1336 _public function_ `FMeshCutterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1363 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FUniformFractureDataflowNode`  
`struct FUniformFractureDataflowNode : public FDataflowNode`  
_L1373-1482_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Fracture / Uniform tool Fracture using a Voronoi diagram with a uniform random pattern, creating fracture pieces of similar volume across the shape.
- L1381 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to fracture
- L1385 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "TransformSelection", DisplayName = "TransformSelection"))` — Bones to fracture, if not connected it will fracture all the bones
- L1389 _private member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput))` — Transform to apply
- L1393 _private member_ `int32 MinVoronoiSites = 20;` — `UPROPERTY(EditAnywhere, Category = "Uniform Voronoi", meta = (DataflowInput, UIMin = "1", UIMax = "5000", ClampMin = "1"))` — Minimum Number of Voronoi sites. The amount of sites per Voronoi diagram will be chosen at random between Min and Max
- L1397 _private member_ `int32 MaxVoronoiSites = 20;` — `UPROPERTY(EditAnywhere, Category = "Uniform Voronoi", meta = (DataflowInput, UIMin = "1", UIMax = "5000", ClampMin = "1"))` — Maximum Number of Voronoi sites. The amount of sites per Voronoi diagram will be chosen at random between Min and Max
- L1401 _private member_ `int32 InternalMaterialID = 0;` — `UPROPERTY(EditAnywhere, Category = "Materials", meta = (DataflowInput, UIMin = "0", UIMax = "10", ClampMin = "0"))` — ID for the material for the newly created internal faces
- L1405 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = "-1", UIMax = "5000", ClampMin = "-1"))` — Random number generator seed for repeatability. If the value is -1, a different random seed will be used every time, otherwise the specified seed will always be used
- L1409 _private member_ `float ChanceToFracture = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Chance to fracture each selected bone. If 0, no bones will fracture; if 1, all bones will fracture.
- L1413 _private member_ `bool GroupFracture = true;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture")` — Generate a fracture pattern across all selected meshes.
- L1417 _private member_ `bool SplitIslands = true;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands")` — Whether to split the fractured mesh pieces into separate islands based on geometric connectivity after fracturing
- L1421 _private member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L1425 _private member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture|Split Islands", meta = (EditCondition = "SplitIslands", Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L1429 _private member_ `float Grout = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Common Fracture", meta = (DataflowInput, UIMin = 0.f))` — Amount of space to leave between cut pieces
- L1433 _private member_ `float Amplitude = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Size of the Perlin noise displacement (in cm). If 0, no noise will be applied
- L1437 _private member_ `float Frequency = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.00001f))` — Period of the Perlin noise.  Smaller values will create a smoother noise pattern
- L1441 _private member_ `float Persistence = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Persistence of the layers of Perlin noise. At each layer (octave) after the first, the amplitude of the Perlin noise is scaled by this factor
- L1445 _private member_ `float Lacunarity = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Lacunarity of the layers of Perlin noise. At each layer (octave) after the first, the frequency of the Perlin noise is scaled by this factor
- L1452 _private member_ `int32 OctaveNumber = 4;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Number of fractal layers of Perlin noise to apply. Each layer is additive, with Amplitude and Frequency parameters scaled by Persistence and Lacunarity Smaller values (1 or 2) will create noise that looks like gentle rolling hills, while larger values (> 4) will tend to look more like craggy mountains
- L1456 _private member_ `float PointSpacing = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Noise", meta = (DataflowInput, UIMin = 0.f))` — Distance (in cm) between vertices on cut surfaces where noise is added.  Larger spacing between vertices will create more efficient meshes with fewer triangles, but less resolution to see the shape of the added noise
- L1465 _private member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L1472 _private member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, UIMin = 0.f, EditCondition = "AddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L1476 _private member_ `FDataflowTransformSelection NewGeometryTransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FracturedTransformSelection "))` — Fractured Pieces
- L1479 _public prototype_ `FUniformFractureDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1481 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowVisualizeFractureColoringType`  
`enum class EDataflowVisualizeFractureColoringType : uint8`  
_L1485-1493_
- reflection: `UENUM(BlueprintType)`
- L1487 _public enumerator_ `ColorByParent UMETA(DisplayName = "Color by Parent")`
- L1488 _public enumerator_ `ColorByLevel UMETA(DisplayName = "Color by Level")`
- L1489 _public enumerator_ `ColorByCluster UMETA(DisplayName = "Color by Cluster")`
- L1490 _public enumerator_ `ColorByLeafLevel UMETA(DisplayName = "Color by Leaf Level")`
- L1491 _public enumerator_ `ColorByLeaf UMETA(DisplayName = "Color by Leaf")`
- L1492 _public enumerator_ `ColorByAttr UMETA(DisplayName = "Color by Attribute")`

#### struct `FMinSettings`  
`struct FMinSettings`  
_L1496-1505_
- reflection: `USTRUCT()`
- L1501 _public member_ `float MinAttrValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (DisplayName = "Minimum Attr Value", EditCondition = "ColoringType == EDataflowVisualizeFractureColoringType::ColorByAttr", EditConditionHides))`
- L1504 _public member_ `FLinearColor MinColor = FLinearColor(FLinearColor::Green);` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (EditCondition = "ColoringType == EDataflowVisualizeFractureColoringType::ColorByAttr", EditConditionHides))`

#### struct `FMaxSettings`  
`struct FMaxSettings`  
_L1508-1517_
- reflection: `USTRUCT()`
- L1513 _public member_ `float MaxAttrValue = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (DisplayName = "Maximum Attr Value", EditCondition = "ColoringType == EDataflowVisualizeFractureColoringType::ColorByAttr", EditConditionHides))`
- L1516 _public member_ `FLinearColor MaxColor = FLinearColor(FLinearColor::Red);` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (EditCondition = "ColoringType == EDataflowVisualizeFractureColoringType::ColorByAttr", EditConditionHides))`

#### struct `FVisualizeFractureDataflowNode`  
`struct FVisualizeFractureDataflowNode : public FDataflowNode`  
_L1525-1591_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Visualizing fracture/cluster info in fractured collection
- L1533 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to visualize
- L1537 _private member_ `int32 Level = 0;` — `UPROPERTY(EditAnywhere, Category = "Level", meta = (DataflowInput, UIMin = "0", ClampMin = "0"))`
- L1541 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, UIMin = "0", ClampMin = "0"))` — Seed for random
- L1545 _private member_ `bool bApplyExplodedView = true;` — `UPROPERTY(EditAnywhere, Category = "Exploded View")` — Use cluster level for coloring and explode
- L1549 _private member_ `float ExplodeAmount = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Exploded View", meta = (DataflowInput, UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0", EditCondition = "bApplyExplodedView"))` — Scale amount to expand the pieces uniformly in all directions
- L1553 _private member_ `FVector Scale = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Exploded View", meta = (DataflowInput, EditCondition = "bApplyExplodedView"))` — Scale amounts to expand the pieces in all 3 directions
- L1557 _private member_ `bool bApplyColor = true;` — `UPROPERTY(EditAnywhere, Category = "Color")`
- L1561 _private member_ `EDataflowVisualizeFractureColoringType ColoringType = EDataflowVisualizeFractureColoringType::ColorByLevel;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (EditCondition = "bApplyColor"))`
- L1565 _private member_ `int32 RandomColorRangeMin = 40;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (UIMin = "0", ClampMin = "0", UIMax = "255", ClampMax = "255"))`
- L1569 _private member_ `int32 RandomColorRangeMax = 190;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (UIMin = "0", ClampMin = "0", UIMax = "255", ClampMax = "255"))`
- L1573 _private member_ `FString Attribute;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (EditCondition = "ColoringType == EDataflowVisualizeFractureColoringType::ColorByAttr", EditConditionHides))`
- L1577 _private member_ `FMinSettings Min;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (EditCondition = "ColoringType == EDataflowVisualizeFractureColoringType::ColorByAttr", EditConditionHides))`
- L1581 _private member_ `FMaxSettings Max;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (EditCondition = "ColoringType == EDataflowVisualizeFractureColoringType::ColorByAttr", EditConditionHides))`
- L1585 _private member_ `FVector Offset = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Offset", meta = (DataflowInput))` — Translate collection for exploded view
- L1588 _public prototype_ `FVisualizeFractureDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1590 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowSetFloatArrayMethod`  
`enum class EDataflowSetFloatArrayMethod : uint8`  
_L1594-1599_
- reflection: `UENUM(BlueprintType)`
- L1596 _public enumerator_ `Random UMETA(DisplayName = "Random")`
- L1597 _public enumerator_ `Noise UMETA(DisplayName = "Noise")`
- L1598 _public enumerator_ `ByBoundingBox UMETA(DisplayName = "By BoundinBox")`

#### struct `FSetFloatAttributeDataflowNode`  
`struct FSetFloatAttributeDataflowNode : public FDataflowNode`  
_L1607-1641_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Set a float values in an array
- L1615 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to visualize
- L1619 _private member_ `FString Attribute;` — `UPROPERTY(EditAnywhere, Category = "Attribute")`
- L1623 _private member_ `EDataflowSetFloatArrayMethod Method = EDataflowSetFloatArrayMethod::Random;` — `UPROPERTY(EditAnywhere, Category = "Method")`
- L1627 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, UIMin = "0", EditCondition = "Method == EDataflowSetFloatArrayMethod::Random", EditConditionHides))` — Seed for random
- L1631 _private member_ `float NoiseScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, UIMin = "0", EditCondition = "Method == EDataflowSetFloatArrayMethod::Noise", EditConditionHides))` — Seed for random
- L1635 _private member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowOutput))` — Output float array
- L1638 _public prototype_ `FSetFloatAttributeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1640 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Dataflow`
- L1643 _namespace_ `namespace UE`
- L1643 _namespace_ `namespace Dataflow` (scope `UE`)
- L1645 _prototype_ `void GeometryCollectionFracturingNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionMakeNodes.h` (Public)


#### struct `FMakeLiteralStringDataflowNode`  
`struct FMakeLiteralStringDataflowNode : public FDataflowNode`  
_L29-48_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Make a literal string Deprecated (5.6)
- L36 _public member_ `FString Value = FString("");` — `UPROPERTY(EditAnywhere, Category = "String")`
- L39 _public member_ `FString String;` — `UPROPERTY(meta = (DataflowOutput))`
- L41 _public function_ `FMakeLiteralStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L47 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralStringDataflowNode_v2`  
`struct FMakeLiteralStringDataflowNode_v2 : public FDataflowNode`  
_L54-70_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a literal string
- L61 _public member_ `FString String;` — `UPROPERTY(EditAnywhere, Category = "String", meta = (DataflowOutput))`
- L63 _public function_ `FMakeLiteralStringDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L69 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakePointsDataflowNode`  
`struct FMakePointsDataflowNode : public FDataflowNode`  
_L78-97_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a points array from specified points
- L85 _public member_ `TArray<FVector> Point;` — `UPROPERTY(EditAnywhere, Category = "Point")`
- L88 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))`
- L90 _public function_ `FMakePointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L96 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EMakeBoxDataTypeEnum`  
`enum class EMakeBoxDataTypeEnum : uint8`  
_L101-108_
- reflection: `UENUM(BlueprintType)`
- L103 _public enumerator_ `Dataflow_MakeBox_DataType_MinMax UMETA(DisplayName = "Min/Max")`
- L104 _public enumerator_ `Dataflow_MakeBox_DataType_CenterSize UMETA(DisplayName = "Center/Size")`
- L107 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FMakeBoxDataflowNode`  
`struct FMakeBoxDataflowNode : public FDataflowNode`  
_L114-142_
- reflection: `USTRUCT(Meta = (Icon = "Icons.MakeStaticMesh"))`
- inherits: `FDataflowNode`
- desc: Make a box
- L120 _public prototype_ `FMakeBoxDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L124 _private member_ `EMakeBoxDataTypeEnum DataType = EMakeBoxDataTypeEnum::Dataflow_MakeBox_DataType_CenterSize;` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (DisplayName = "Input Data Type"))`
- L127 _private member_ `FVector Min = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (DataflowInput, EditCondition = "DataType == EMakeBoxDataTypeEnum::Dataflow_MakeBox_DataType_MinMax", EditConditionHides, GizmoType = "Translate"))`
- L130 _private member_ `FVector Max = FVector(100.0);` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (DataflowInput, EditCondition = "DataType == EMakeBoxDataTypeEnum::Dataflow_MakeBox_DataType_MinMax", EditConditionHides, GizmoType = "Translate"))`
- L133 _private member_ `FVector Center = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (DataflowInput, EditCondition = "DataType == EMakeBoxDataTypeEnum::Dataflow_MakeBox_DataType_CenterSize", EditConditionHides, GizmoType = "Translate"))`
- L136 _private member_ `FVector Size = FVector(100.0);` — `UPROPERTY(EditAnywhere, Category = "Box", meta = (DataflowInput, EditCondition = "DataType == EMakeBoxDataTypeEnum::Dataflow_MakeBox_DataType_CenterSize", EditConditionHides))`
- L139 _private member_ `FBox Box = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))`
- L141 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeSphereDataflowNode`  
`struct FMakeSphereDataflowNode : public FDataflowNode`  
_L151-175_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Description for this node
- L158 _public member_ `FVector Center = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (DataflowInput, GizmoType = "Translate"))`
- L161 _public member_ `float Radius = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (DataflowInput))`
- L164 _public member_ `FSphere Sphere = FSphere(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))`
- L166 _public function_ `FMakeSphereDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L174 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralFloatDataflowNode`  
`struct FMakeLiteralFloatDataflowNode : public FDataflowNode`  
_L182-201_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Make a float value Deprecated (5.6)
- L189 _public member_ `float Value = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Float")`
- L192 _public member_ `float Float = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L194 _public function_ `FMakeLiteralFloatDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L200 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralFloatDataflowNode_v2`  
`struct FMakeLiteralFloatDataflowNode_v2 : public FDataflowNode`  
_L207-223_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a float value
- L214 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Float", meta = (DataflowOutput))`
- L216 _public function_ `FMakeLiteralFloatDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L222 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralDoubleDataflowNode`  
`struct FMakeLiteralDoubleDataflowNode : public FDataflowNode`  
_L231-245_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a double value
- L238 _private member_ `double Double = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Double", meta = (DataflowOutput))`
- L241 _public prototype_ `FMakeLiteralDoubleDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L244 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralIntDataflowNode`  
`struct FMakeLiteralIntDataflowNode : public FDataflowNode`  
_L252-271_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Make an integer value Deprecated (5.6)
- L259 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = "Int")`
- L262 _public member_ `int32 Int = 0;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Int"))`
- L264 _public function_ `FMakeLiteralIntDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L270 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralIntDataflowNode_v2`  
`struct FMakeLiteralIntDataflowNode_v2 : public FDataflowNode`  
_L277-293_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make an integer value
- L284 _public member_ `int32 Int = 0;` — `UPROPERTY(EditAnywhere, Category = "Int", meta = (DataflowOutput))`
- L286 _public function_ `FMakeLiteralIntDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L292 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralBoolDataflowNode`  
`struct FMakeLiteralBoolDataflowNode : public FDataflowNode`  
_L300-319_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Make a bool value Deprecated(5.6)
- L307 _public member_ `bool Value = false;` — `UPROPERTY(EditAnywhere, Category = "Bool")`
- L310 _public member_ `bool Bool = false;` — `UPROPERTY(meta = (DataflowOutput))`
- L312 _public function_ `FMakeLiteralBoolDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L318 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralBoolDataflowNode_v2`  
`struct FMakeLiteralBoolDataflowNode_v2 : public FDataflowNode`  
_L325-341_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a bool value
- L332 _public member_ `bool Bool = false;` — `UPROPERTY(EditAnywhere, Category = "Bool", meta = (DataflowOutput))`
- L334 _public function_ `FMakeLiteralBoolDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L340 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeLiteralVectorDataflowNode`  
`struct FMakeLiteralVectorDataflowNode : public FDataflowNode`  
_L350-378_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Make a vector Deprecated(5.6) Use MakeVector3 instead
- L357 _public member_ `float X = float(0.0);` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (DataflowInput))`
- L360 _public member_ `float Y = float(0.0);` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (DataflowInput))`
- L363 _public member_ `float Z = float(0.0);` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (DataflowInput))`
- L366 _public member_ `FVector Vector = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Vector"))`
- L368 _public function_ `FMakeLiteralVectorDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L377 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeTransformDataflowNode`  
`struct FMakeTransformDataflowNode : public FDataflowNode`  
_L386-419_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make an FTransform Note: Originaly this version was depricated and replaced with FMakeTransformDataflowNode_v2 but when AnyRotationType was introduced with the ConvertAnyRotation node FMakeTransformDataflowNode_v2 became obsolete and this version became the current version again
- L394 _private member_ `FVector InTranslation = FVector(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, DisplayName = "Translation"))` — Translation
- L398 _private member_ `FVector InRotation = FVector(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, DisplayName = "Rotation"))` — Rotation as Euler
- L402 _private member_ `FVector InScale = FVector(1, 1, 1);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, DisplayName = "Scale"))` — Scale
- L406 _private member_ `FTransform OutTransform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Transform"))` — Result transform
- L408 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L411 _public function_ `FMakeTransformDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`

#### struct `FMakeTransformDataflowNode_v2`  
`struct FMakeTransformDataflowNode_v2 : public FDataflowNode`  
_L428-464_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Make a FTransform Deprecated (5.6) Use FMakeTransformDataflowNode instead
- L437 _private member_ `FVector Translation = FVector(0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput))` — Translation
- L441 _private member_ `FVector Rotation = FVector(0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput))` — Rotation as Euler
- L445 _private member_ `FRotator Rotator = FRotator(0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput))` — Rotation a Rotator
- L449 _private member_ `FQuat Quat = FQuat(ForceInit);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput))` — Rotation as a quaternion
- L453 _private member_ `FVector Scale = FVector(1.f, 1.f, 1.f);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput))` — Scale
- L457 _private member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowOutput))` — Result transform
- L460 _public prototype_ `FMakeTransformDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L463 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeQuaternionDataflowNode`  
`struct FMakeQuaternionDataflowNode : public FDataflowNode`  
_L472-504_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L479 _public member_ `float X = float(0.0);` — `UPROPERTY(EditAnywhere, Category = "Quaternion ", meta = (DataflowInput))`
- L482 _public member_ `float Y = float(0.0);` — `UPROPERTY(EditAnywhere, Category = "Quaternion", meta = (DataflowInput))`
- L485 _public member_ `float Z = float(0.0);` — `UPROPERTY(EditAnywhere, Category = "Quaternion", meta = (DataflowInput))`
- L488 _public member_ `float W = float(0.0);` — `UPROPERTY(EditAnywhere, Category = "Quaternion", meta = (DataflowInput))`
- L491 _public member_ `FQuat Quaternion = FQuat(ForceInitToZero);` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Quaternion"))`
- L493 _public function_ `FMakeQuaternionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L503 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeFloatArrayDataflowNode`  
`struct FMakeFloatArrayDataflowNode : public FDataflowNode`  
_L512-539_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: M
- L520 _public member_ `int32 NumElements = 1;` — `UPROPERTY(EditAnywhere, Category = "Float", meta = (DataflowInput, DisplayName = "Number of Elements", UIMin = "0"))` — Number of elements of the array
- L524 _public member_ `float Value = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Float", meta = (DataflowInput))` — Value to initialize the array with
- L528 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowOutput))` — Output float array
- L530 _public function_ `FMakeFloatArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L538 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeCollectionDataflowNode`  
`struct FMakeCollectionDataflowNode : public FDataflowNode`  
_L547-568_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make an empty ManagedArrayCollection
- L554 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))`
- L558 _private member_ `bool bAddRootTransform = false;` — `UPROPERTY(EditAnyWhere, Category = "Options")` — if true, create a root transform
- L561 _public function_ `FMakeCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L567 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeRotatorDataflowNode`  
`struct FMakeRotatorDataflowNode : public FDataflowNode`  
_L576-602_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a Rotator
- L584 _private member_ `float Pitch = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Rotator", meta = (DataflowInput))` — Rotation around the right axis (around Y axis), Looking up and down (0=Straight Ahead, +Up, -Down)
- L588 _private member_ `float Yaw = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Rotator", meta = (DataflowInput))` — Rotation around the up axis (around Z axis), Turning around (0=Forward, +Right, -Left)
- L592 _private member_ `float Roll = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Rotator", meta = (DataflowInput))` — Rotation around the forward axis (around X axis), Tilting your head, (0=Straight, +Clockwise, -CCW)
- L596 _private member_ `FRotator Rotator = FRotator(0.f, 0.f, 0.f);` — `UPROPERTY(meta = (DataflowOutput))` — Rotator output
- L599 _public prototype_ `FMakeRotatorDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L601 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBreakTransformDataflowNode`  
`struct FBreakTransformDataflowNode : public FDataflowNode`  
_L608-643_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Break a Transform into Translation, Rotation (Euler, Rotator, Quaternion), Scale
- L616 _private member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, GizmoType = "Transform"))` — Transform to break into components
- L620 _private member_ `FDataflowVectorTypes Translation;` — `UPROPERTY(meta = (DataflowOutput))` — Translation
- L624 _private member_ `FVector Rotation = FVector(0.f, 0.f, 0.f);` — `UPROPERTY(meta = (DataflowOutput))` — Rotation as Euler
- L628 _private member_ `FRotator Rotator = FRotator(0.f, 0.f, 0.f);` — `UPROPERTY(meta = (DataflowOutput))` — Rotation as a rotator
- L632 _private member_ `FQuat Quat = FQuat(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))` — Rotation as a quaternion
- L636 _private member_ `FDataflowVectorTypes Scale;` — `UPROPERTY(meta = (DataflowOutput))` — Scale
- L639 _public prototype_ `FBreakTransformDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L642 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakePlaneDataflowNode`  
`struct FMakePlaneDataflowNode : public FDataflowNode`  
_L650-688_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Make a plane Deprecated (5.8), use FMakePlaneDataflowNode_v2 instead
- L658 _private member_ `FVector BasePoint = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Plane", meta = (DataflowInput, GizmoType = "Translate"))` — Base point
- L662 _private member_ `FVector Normal = FVector::UpVector;` — `UPROPERTY(EditAnywhere, Category = "Plane", meta = (DataflowInput))` — Normal vector
- L666 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))` — DebugDraw settings
- L669 _private member_ `float PlaneSizeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (UIMin = "1.0", UIMax = "10.0", ClampMin = "1.0", ClampMax = "10.0"))`
- L673 _private member_ `FPlane Plane = FPlane(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L676 _public prototype_ `FMakePlaneDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L679 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L681 _private function_ `virtual bool CanDebugDraw() const override`
- L685 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L686 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FMakeIntArrayDataflowNode`  
`struct FMakeIntArrayDataflowNode : public FDataflowNode`  
_L696-722_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make an int32 array starting with Start with Count elements
- L704 _private member_ `int32 Start = 0;` — `UPROPERTY(EditAnywhere, Category = "Int", meta = (DataflowInput))` — First element of IntArray
- L708 _private member_ `int32 Count = 3;` — `UPROPERTY(EditAnywhere, Category = "Int", meta = (DataflowInput, UIMin = "0", ClampMin = "0"))` — Number of elements in IntArray
- L711 _private member_ `bool bReverseOrder = false;` — `UPROPERTY(EditAnywhere, Category = "Int")`
- L715 _private member_ `TArray<int32> IntArray;` — `UPROPERTY(meta = (DataflowOutput))` — IntArray
- L718 _public prototype_ `FMakeIntArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L721 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeIntArrayFromListDataflowNode`  
`struct FMakeIntArrayFromListDataflowNode : public FDataflowNode`  
_L730-752_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make an int32 array from a comma separated list, e.g. "0, 2, 5-10, 12-15"
- L738 _private member_ `FString List;` — `UPROPERTY(EditAnywhere, Category = "Int")` — First element of IntArray
- L741 _private member_ `bool bReverseOrder = false;` — `UPROPERTY(EditAnywhere, Category = "Int")`
- L745 _private member_ `TArray<int32> IntArray;` — `UPROPERTY(meta = (DataflowOutput))` — IntArray
- L748 _public prototype_ `FMakeIntArrayFromListDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L751 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakePlaneDataflowNode_v2`  
`struct FMakePlaneDataflowNode_v2 : public FDataflowNode`  
_L758-780_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a plane
- L766 _private member_ `FVector BasePoint = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Plane", meta = (DataflowInput))` — Base point
- L770 _private member_ `FVector Normal = FVector::UpVector;` — `UPROPERTY(EditAnywhere, Category = "Plane", meta = (DataflowInput))` — Normal vector
- L774 _private member_ `FDataflowPlane Plane;` — `UPROPERTY(meta = (DataflowOutput))` — Output plane
- L776 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L779 _public prototype_ `FMakePlaneDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMakePointsDataflowNode_v2`  
`struct FMakePointsDataflowNode_v2 : public FDataflowNode`  
_L788-804_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a points array from specified points
- L795 _private member_ `TArray<FVector> Point;` — `UPROPERTY(EditAnywhere, Category = "Point")`
- L798 _private member_ `FDataflowPoints Points;` — `UPROPERTY(meta = (DataflowOutput))`
- L800 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L803 _public prototype_ `FMakePointsDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMakeNumericArrayDataflowNode`  
`struct FMakeNumericArrayDataflowNode : public FDataflowNode`  
_L812-838_
- reflection: `USTRUCT(meta = (Icon = "Kismet.VariableList.ArrayTypeIcon"))`
- inherits: `FDataflowNode`
- desc: Make an array of any numeric type
- L820 _private member_ `int32 NumElements = 1;` — `UPROPERTY(EditAnywhere, Category = "Array", meta = (DataflowInput, DisplayName = "Number of Elements", UIMin = "0"))` — Number of elements of the array
- L824 _private member_ `FDataflowNumericTypes DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Array", meta = (DataflowInput))` — Default value for output, whichever value doesn't get set in the output array by the generator will have the default value
- L828 _private member_ `FDataflowValueGenerator Generator;` — `UPROPERTY(EditAnywhere, Category = "Generator", meta = (DataflowInput))` — Generator input
- L832 _private member_ `FDataflowNumericArrayTypes Array;` — `UPROPERTY(meta = (DataflowOutput))` — Output float array
- L834 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L837 _public prototype_ `FMakeNumericArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Dataflow`
- L840 _namespace_ `namespace UE`
- L840 _namespace_ `namespace Dataflow` (scope `UE`)
- L842 _prototype_ `void GeometryCollectionMakeNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionMaterialInterfaceNodes.h` (Public)


#### struct `FMakeMaterialInterfaceArrayDataflowNode`  
`struct FMakeMaterialInterfaceArrayDataflowNode : public FDataflowNode`  
_L20-34_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a array from a user defined list of material objects
- L30 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L33 _public prototype_ `FMakeMaterialInterfaceArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetMaterialInterfaceArraySizeDataflowNode`  
`struct FGetMaterialInterfaceArraySizeDataflowNode : public FDataflowNode`  
_L41-59_
- reflection: `USTRUCT(meta = (Deprecated = 5.6))`
- inherits: `FDataflowNode`
- desc: Get number of element in an material array DEPRECATED 5.6 - use the generic GetArraySize node instead
- L49 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialArray;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = MaterialArray, DataflowIntrinsic))` — Material array to get size from
- L53 _private member_ `int32 Size = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Size of the array
- L55 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L58 _public prototype_ `FGetMaterialInterfaceArraySizeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetMaterialInterfaceAssetDataflowNode`  
`struct FGetMaterialInterfaceAssetDataflowNode : public FDataflowNode`  
_L65-82_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Get a material interface from an existing asset
- L73 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DataflowOutput))` — Material asset to get
- L75 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L77 _private prototype_ `virtual bool SupportsAssetProperty(UObject* Asset) const override;`
- L78 _private prototype_ `virtual void SetAssetProperty(UObject* Asset) override;`
- L81 _public prototype_ `FGetMaterialInterfaceAssetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetFromMaterialInterfaceArrayDataflowNode`  
`struct FGetFromMaterialInterfaceArrayDataflowNode : public FDataflowNode`  
_L90-112_
- reflection: `USTRUCT(meta = (Deprecated = 5.6))`
- inherits: `FDataflowNode`
- desc: Get an element from a material array (if the index does not match the range of the array, null is returned) DEPRECATED 5.6 - use the generic GetArrayElement node instead
- L98 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialArray;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = MaterialArray, DataflowIntrinsic))` — Material array to get the material from
- L102 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(meta = (DataflowOutput))` — Material at the requested index ( may be null if index does not match the array range )
- L106 _private member_ `int32 Index = 0;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DataflowInput))` — Index in the array to get the material from. Invalid index will return null material
- L108 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L111 _public prototype_ `FGetFromMaterialInterfaceArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSetIntoMaterialInterfaceArrayDataflowNode`  
`struct FSetIntoMaterialInterfaceArrayDataflowNode : public FDataflowNode`  
_L119-141_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Set an element into a material array at a specific index (if the index does not match the range of the array, the array will remain unchanged)
- L127 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialArray;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = MaterialArray, DataflowIntrinsic))` — Material array to modify
- L131 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DataflowInput))` — Material to set at the specific index into the array
- L135 _private member_ `int32 Index = 0;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DataflowInput))` — Index Set the material at (if the index does not match the range of the array, the array will remain unchanged)
- L137 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L140 _public prototype_ `FSetIntoMaterialInterfaceArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FAddToMaterialInterfaceArrayDataflowNode`  
`struct FAddToMaterialInterfaceArrayDataflowNode : public FDataflowNode`  
_L147-177_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Add material(s) to an array
- L155 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialArray;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = MaterialArray))` — Material array to add to
- L158 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialsToAdd;` — `UPROPERTY()`
- L161 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L162 _private prototype_ `virtual bool CanAddPin() const override;`
- L163 _private prototype_ `virtual bool CanRemovePin() const override;`
- L164 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L165 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L166 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L167 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L170 _private prototype_ `UE::Dataflow::TConnectionReference<TObjectPtr<UMaterialInterface>> GetConnectionReference(int32 Index) const;`
- L172 _private member_ `static constexpr int32 NumOtherInputs = 1;` — MaterialArray
- L173 _private member_ `static constexpr int32 NumInitialVariableInputs = 1;`
- L176 _public prototype_ `FAddToMaterialInterfaceArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FAssignMaterialInterfaceToCollectionDataflowNode`  
`struct FAssignMaterialInterfaceToCollectionDataflowNode : public FDataflowNode`  
_L183-220_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Assign material to a set of face in a geometry collection
- L191 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection, DataflowIntrinsic))` — Collection to assign material to
- L195 _private member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput))` — Faces that will be set with this material index, if no selection is connected , all faces will be set
- L199 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialArray;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = MaterialArray, DataflowIntrinsic))` — Array holding the materials objects
- L203 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DataflowInput))` — Material to assign to the selection
- L207 _private member_ `int32 MaterialIndex = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Index where the material was set in the array
- L211 _private member_ `bool bMergeDuplicateMaterials = false;` — `UPROPERTY(EditAnywhere, Category = Material)` — If true, detect duplicate in the material array and only add the material in the array if it does not yet exists
- L213 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L216 _private prototype_ `int32 AddOrMergeMaterialToArray(TArray<TObjectPtr<UMaterialInterface>>& InOutMaterials, TObjectPtr<UMaterialInterface> InMaterialToAdd) const;` — add or merge a material and return the index where the material was set inthe array
- L219 _public prototype_ `FAssignMaterialInterfaceToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMaterialInterfaceTextureOverrideDataflowNode`  
`struct FMaterialInterfaceTextureOverrideDataflowNode : public FDataflowNode`  
_L227-250_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Duplicate the given material and replace the target texture with the override texture on the newly-created material
- L234 _public prototype_ `FMaterialInterfaceTextureOverrideDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L239 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Material"))`
- L242 _private member_ `TObjectPtr<const UTexture2D> TargetTexture;` — `UPROPERTY(EditAnywhere, Category = "Override", meta = (DataflowInput))`
- L245 _private member_ `TObjectPtr<UTexture2D> OverrideTexture;` — `UPROPERTY(EditAnywhere, Category = "Override", meta=(DataflowInput))`
- L248 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowMaterialFloatParameter`  
`struct FDataflowMaterialFloatParameter`  
_L255-265_
- reflection: `USTRUCT()`
- L261 _public member_ `FName Name;` — `UPROPERTY()`
- L264 _public member_ `float Value = 0;` — `UPROPERTY()`

#### struct `FDataflowMaterialVectorParameter`  
`struct FDataflowMaterialVectorParameter`  
_L268-278_
- reflection: `USTRUCT()`
- L274 _public member_ `FName Name;` — `UPROPERTY()`
- L277 _public member_ `FVector4 Value = FVector4(0,0,0,0);` — `UPROPERTY()`

#### struct `FDataflowMaterialTextureParameter`  
`struct FDataflowMaterialTextureParameter`  
_L281-291_
- reflection: `USTRUCT()`
- L287 _public member_ `FName Name;` — `UPROPERTY()`
- L290 _public member_ `TObjectPtr<UTexture> Value = nullptr;` — `UPROPERTY()`

#### struct `FDataflowMaterialParameters`  
`struct FDataflowMaterialParameters`  
_L294-307_
- reflection: `USTRUCT()`
- L300 _public member_ `TArray<FDataflowMaterialFloatParameter> FloatParameters;` — `UPROPERTY()`
- L303 _public member_ `TArray<FDataflowMaterialVectorParameter> VectorParameters;` — `UPROPERTY()`
- L306 _public member_ `TArray<FDataflowMaterialTextureParameter> TextureParameters;` — `UPROPERTY()`

#### struct `FMaterialInterfaceSetFloatParameterDataflowNode`  
`struct FMaterialInterfaceSetFloatParameterDataflowNode : public FDataflowNode`  
_L316-338_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Add a material float parameter to a parameters object Material parameters are used to create material instances
- L322 _public prototype_ `FMaterialInterfaceSetFloatParameterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L327 _private member_ `FDataflowMaterialParameters MaterialParameters;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "MaterialParameters"))`
- L330 _private member_ `FDataflowStringTypes ParameterName;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (DataflowInput))`
- L333 _private member_ `FDataflowNumericTypes ParameterValue;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (DataflowInput))`
- L336 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMaterialInterfaceSetVectorParameterDataflowNode`  
`struct FMaterialInterfaceSetVectorParameterDataflowNode : public FDataflowNode`  
_L347-369_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Add a material vector4 parameter to a parameters object Material parameters are used to create material instances
- L353 _public prototype_ `FMaterialInterfaceSetVectorParameterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L358 _private member_ `FDataflowMaterialParameters MaterialParameters;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "MaterialParameters"))`
- L361 _private member_ `FDataflowStringTypes ParameterName;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (DataflowInput))`
- L364 _private member_ `FDataflowVectorTypes ParameterValue;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (DataflowInput))`
- L367 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMaterialInterfaceSetTexture2DParameterDataflowNode`  
`struct FMaterialInterfaceSetTexture2DParameterDataflowNode : public FDataflowNode`  
_L378-400_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowNode`
- desc: Add a material texture parameter to a parameters object Material parameters are used to create material instances
- L384 _public prototype_ `FMaterialInterfaceSetTexture2DParameterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L389 _private member_ `FDataflowMaterialParameters MaterialParameters;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "MaterialParameters"))`
- L392 _private member_ `FDataflowStringTypes ParameterName;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (DataflowInput))`
- L395 _private member_ `TObjectPtr<UTexture2D> ParameterValue;` — `UPROPERTY(EditAnywhere, Category = "Parameter", meta = (DataflowInput))`
- L398 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMaterialInterfaceTerminalDataflowNode`  
`struct FMaterialInterfaceTerminalDataflowNode : public FDataflowTerminalNode`  
_L408-431_
- reflection: `USTRUCT(Meta = (MeshResizing, Experimental))`
- inherits: `FDataflowTerminalNode`
- desc: Make a material instance from another material
- L414 _public prototype_ `FMaterialInterfaceTerminalDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L419 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Material"))`
- L422 _private member_ `FString AssetPath;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (DataflowInput))`
- L425 _private member_ `FDataflowMaterialParameters MaterialParameters;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (DataflowInput))`
- L428 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L429 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`

#### Free symbols / members of external scopes

- L433 _namespace_ `namespace UE`
- L433 _namespace_ `namespace Dataflow` (scope `UE`)
- L435 _prototype_ `void RegisterGeometryCollectionMaterialInterfaceNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionMaterialNodes.h` (Public)


#### struct `FAddMaterialToCollectionDataflowNode`  
`struct FAddMaterialToCollectionDataflowNode : public FDataflowNode`  
_L30-78_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Adds Outside/Inside Materials to Outside/Inside faces Deprecated (5.6) - Use AssignMaterialToCollection node instead
- L38 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to add material(s) to
- L42 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "FaceSelection", DataflowIntrinsic))` — Face selection, the material(s) will be added to the selected faces
- L46 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Materials", DataflowIntrinsic))` — Materials array storing the materials
- L50 _public member_ `TObjectPtr<UMaterial> OutsideMaterial;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DataflowInput))` — Outside material to assign to the outside faces from the face selection
- L54 _public member_ `TObjectPtr<UMaterial> InsideMaterial;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DataflowInput))` — Inside material to assign to the inside faces from the face selection
- L58 _public member_ `bool bAssignOutsideMaterial = true;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DisplayName = "Assign Outside Material to Outside Faces"))` — If true, the outside material will be assigned to the outside faces from the face selection
- L62 _public member_ `bool bAssignInsideMaterial = false;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DisplayName = "Assign Inside Material to Inside Faces"))` — If true, the inside material will be assigned to the inside faces from the face selection
- L64 _public function_ `FAddMaterialToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L76 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FReAssignMaterialInCollectionDataflowNode`  
`struct FReAssignMaterialInCollectionDataflowNode : public FDataflowNode`  
_L88-136_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Reassign existing material(s) to Outside/Inside faces Deprecated (5.6) - Use AssignMaterialToCollection node instead
- L96 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for reassign the material(s)
- L100 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "FaceSelection", DataflowIntrinsic))` — Face selection, the material(s) will be assigned to the selected faces
- L104 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Materials", DataflowIntrinsic))` — Materials array storing the materials
- L108 _public member_ `int32 OutsideMaterialIdx = -1;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DataflowInput, DisplayName = "Outside Material Index", ArrayClamp = "Materials"))` — Index of the material in the Materials array to assign to the outside faces from the face selection
- L112 _public member_ `int32 InsideMaterialIdx = -1;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DataflowInput, DisplayName = "Inside Material Index", ArrayClamp = "Materials"))` — Index of the material in the Materials array to assign to the inside faces from the face selection
- L116 _public member_ `bool bAssignOutsideMaterial = false;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DisplayName = "Assign Outside Material to Outside Faces"))` — If true, the selected material from the Materials array will be assigned to the outside faces from the face selection
- L120 _public member_ `bool bAssignInsideMaterial = false;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DisplayName = "Assign Inside Material to Inside Faces"))` — If true, the selected material from the Materials array will be assigned to the inside faces from the face selection
- L122 _public function_ `FReAssignMaterialInCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L134 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMaterialsInfoDataflowNode`  
`struct FMaterialsInfoDataflowNode : public FDataflowNode`  
_L146-169_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Generates a formatted string of materials from the Materials array Deprecated (5.6)
- L154 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Materials array storing the materials
- L158 _public member_ `FString String;` — `UPROPERTY(meta = (DataflowOutput))` — Formatted string of the materials
- L160 _public function_ `FMaterialsInfoDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L167 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetMaterialFromMaterialsArrayDataflowNode`  
`struct FGetMaterialFromMaterialsArrayDataflowNode : public FDataflowNode`  
_L179-207_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Get a Material from a Materials array Deprecated (5.6) - Use GetFromMaterialArray instead
- L187 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Materials array storing the materials
- L191 _public member_ `TObjectPtr<UMaterial> Material;` — `UPROPERTY(meta = (DataflowOutput))` — Selected material from the Materials array
- L195 _public member_ `int32 MaterialIdx = 0;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DataflowInput, DisplayName = "Material Index"))` — Index in the Materials array for the selected material
- L197 _public function_ `FGetMaterialFromMaterialsArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L205 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ESetMaterialOperationTypeEnum`  
`enum class ESetMaterialOperationTypeEnum : uint8`  
_L211-218_
- reflection: `UENUM(BlueprintType)`
- L213 _public enumerator_ `Dataflow_SetMaterialOperationType_Add UMETA(DisplayName = "Add")`
- L214 _public enumerator_ `Dataflow_SetMaterialOperationType_Insert UMETA(DisplayName = "Insert")`
- L217 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FSetMaterialInMaterialsArrayDataflowNode`  
`struct FSetMaterialInMaterialsArrayDataflowNode : public FDataflowNode`  
_L227-261_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Set a Material in a Materials array Deprecated (5.6) - Use SetIntoMaterialArray instead
- L235 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Materials", DataflowIntrinsic))` — Materials array storing the materials
- L239 _public member_ `TObjectPtr<UMaterial> Material;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DataflowInput))` — Material to add/insert to/in Materials array
- L244 _public member_ `ESetMaterialOperationTypeEnum Operation = ESetMaterialOperationTypeEnum::Dataflow_SetMaterialOperationType_Add;` — `UPROPERTY(EditAnywhere, Category = "Material")` — Operation type for setting the material, add will add the new material to the end off Materials array, insert will insert the new material into Materials array at the index specified by MaterialIdx
- L248 _public member_ `int32 MaterialIdx = 0;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DataflowInput, DisplayName = "Material Index", EditCondition = "Operation == ESetMaterialOperationTypeEnum::Dataflow_SetMaterialOperationType_Insert", EditConditionHides))` — Index for inserting a nem material into the Materials array
- L250 _public function_ `FSetMaterialInMaterialsArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L259 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeMaterialDataflowNode`  
`struct FMakeMaterialDataflowNode : public FDataflowNode`  
_L271-293_
- reflection: `USTRUCT(meta=(Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Makes a material Deprecated (5.6)
- L279 _public member_ `TObjectPtr<UMaterial> InMaterial;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (DisplayName = "Material"))` — Material which will be outputed
- L283 _public member_ `TObjectPtr<UMaterial> Material;` — `UPROPERTY(meta = (DataflowOutput))` — Output material
- L285 _public function_ `FMakeMaterialDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L291 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeMaterialsArrayDataflowNode`  
`struct FMakeMaterialsArrayDataflowNode : public FDataflowNode`  
_L302-320_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Makes an empty Materials array Deprecated (5.6)
- L310 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowOutput))` — Output Matarials array
- L312 _public function_ `FMakeMaterialsArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L318 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Dataflow`
- L323 _namespace_ `namespace UE`
- L323 _namespace_ `namespace Dataflow` (scope `UE`)
- L325 _prototype_ `void GeometryCollectionMaterialNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionMathNodes.h` (Public)


#### struct `FAddDataflowNode`  
`struct FAddDataflowNode : public FDataflowNode`  
_L18-42_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L25 _public member_ `float FloatA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Add", meta = (DataflowInput))`
- L28 _public member_ `float FloatB = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Add", meta = (DataflowInput))`
- L31 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L33 _public function_ `FAddDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L41 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSubtractDataflowNode`  
`struct FSubtractDataflowNode : public FDataflowNode`  
_L50-74_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L57 _public member_ `float FloatA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Subtract", meta = (DataflowInput))`
- L60 _public member_ `float FloatB = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Subtract", meta = (DataflowInput))`
- L63 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L65 _public function_ `FSubtractDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L73 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMultiplyDataflowNode`  
`struct FMultiplyDataflowNode : public FDataflowNode`  
_L82-106_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L89 _public member_ `float FloatA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Multiply", meta = (DataflowInput))`
- L92 _public member_ `float FloatB = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Multiply", meta = (DataflowInput))`
- L95 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L97 _public function_ `FMultiplyDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L105 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSafeDivideDataflowNode`  
`struct FSafeDivideDataflowNode : public FDataflowNode`  
_L114-138_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L121 _public member_ `float FloatA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "SafeDivide", meta = (DataflowInput))`
- L124 _public member_ `float FloatB = 0.f;` — `UPROPERTY(EditAnywhere, Category = "SafeDivide", meta = (DataflowInput))`
- L127 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L129 _public function_ `FSafeDivideDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L137 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDivideDataflowNode`  
`struct FDivideDataflowNode : public FSafeDivideDataflowNode`  
_L141-150_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FSafeDivideDataflowNode`
- L147 _public function_ `FDivideDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FSafeDivideDataflowNode(InParam, InGuid)`

#### struct `FDivisionDataflowNode`  
`struct FDivisionDataflowNode : public FDataflowNode`  
_L158-186_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L165 _public member_ `float Dividend = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Division", meta = (DataflowInput))`
- L168 _public member_ `float Divisor = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Division", meta = (DataflowInput))`
- L171 _public member_ `float Remainder = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L174 _public member_ `int32 ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L176 _public function_ `FDivisionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L185 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSafeReciprocalDataflowNode`  
`struct FSafeReciprocalDataflowNode : public FDataflowNode`  
_L194-214_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L201 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "SafeReciprocal", meta = (DataflowInput))`
- L204 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L206 _public function_ `FSafeReciprocalDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L213 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSquareDataflowNode`  
`struct FSquareDataflowNode : public FDataflowNode`  
_L222-242_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L229 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Square", meta = (DataflowInput))`
- L232 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L234 _public function_ `FSquareDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L241 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSquareRootDataflowNode`  
`struct FSquareRootDataflowNode : public FDataflowNode`  
_L250-270_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L257 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "SquareRoot", meta = (DataflowInput))`
- L260 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L262 _public function_ `FSquareRootDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L269 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FInverseSqrtDataflowNode`  
`struct FInverseSqrtDataflowNode : public FDataflowNode`  
_L278-298_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L285 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "InverseSqrt", meta = (DataflowInput))`
- L288 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L290 _public function_ `FInverseSqrtDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L297 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCubeDataflowNode`  
`struct FCubeDataflowNode : public FDataflowNode`  
_L306-326_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L313 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Cube", meta = (DataflowInput))`
- L316 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L318 _public function_ `FCubeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L325 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FNegateDataflowNode`  
`struct FNegateDataflowNode : public FDataflowNode`  
_L334-354_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L341 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Negate", meta = (DataflowInput))`
- L344 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L346 _public function_ `FNegateDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L353 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FAbsDataflowNode`  
`struct FAbsDataflowNode : public FDataflowNode`  
_L362-382_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L369 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Abs", meta = (DataflowInput))`
- L372 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L374 _public function_ `FAbsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L381 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFloorDataflowNode`  
`struct FFloorDataflowNode : public FDataflowNode`  
_L390-410_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts a float to a nearest less or equal integer
- L397 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Floor", meta = (DataflowInput))`
- L400 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L402 _public function_ `FFloorDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L409 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCeilDataflowNode`  
`struct FCeilDataflowNode : public FDataflowNode`  
_L418-438_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts a float to the nearest greater or equal integer
- L425 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Ceil", meta = (DataflowInput))`
- L428 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L430 _public function_ `FCeilDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L437 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRoundDataflowNode`  
`struct FRoundDataflowNode : public FDataflowNode`  
_L446-466_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts a float to the nearest integer. Rounds up when the fraction is .5
- L453 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Round", meta = (DataflowInput))`
- L456 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L458 _public function_ `FRoundDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L465 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FTruncDataflowNode`  
`struct FTruncDataflowNode : public FDataflowNode`  
_L474-494_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts a float to the nearest integer. Rounds up when the fraction is .5
- L481 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Trunc", meta = (DataflowInput))`
- L484 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L486 _public function_ `FTruncDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L493 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFracDataflowNode`  
`struct FFracDataflowNode : public FDataflowNode`  
_L502-522_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns the fractional part of a float
- L509 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Frac", meta = (DataflowInput))`
- L512 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L514 _public function_ `FFracDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L521 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMinDataflowNode`  
`struct FMinDataflowNode : public FDataflowNode`  
_L530-554_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L537 _public member_ `float FloatA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Min", meta = (DataflowInput))`
- L540 _public member_ `float FloatB = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Min", meta = (DataflowInput))`
- L543 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L545 _public function_ `FMinDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L553 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMaxDataflowNode`  
`struct FMaxDataflowNode : public FDataflowNode`  
_L562-586_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L569 _public member_ `float FloatA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Max", meta = (DataflowInput))`
- L572 _public member_ `float FloatB = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Max", meta = (DataflowInput))`
- L575 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L577 _public function_ `FMaxDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L585 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMin3DataflowNode`  
`struct FMin3DataflowNode : public FDataflowNode`  
_L594-622_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L601 _public member_ `float FloatA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Min3", meta = (DataflowInput))`
- L604 _public member_ `float FloatB = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Min3", meta = (DataflowInput))`
- L607 _public member_ `float FloatC = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Min3", meta = (DataflowInput))`
- L610 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L612 _public function_ `FMin3DataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L621 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMax3DataflowNode`  
`struct FMax3DataflowNode : public FDataflowNode`  
_L630-658_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L637 _public member_ `float FloatA = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Max3", meta = (DataflowInput))`
- L640 _public member_ `float FloatB = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Max3", meta = (DataflowInput))`
- L643 _public member_ `float FloatC = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Max3", meta = (DataflowInput))`
- L646 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L648 _public function_ `FMax3DataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L657 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSignDataflowNode`  
`struct FSignDataflowNode : public FDataflowNode`  
_L666-686_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns 1, 0, or -1 depending on relation of Float to 0
- L673 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Sign", meta = (DataflowInput))`
- L676 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L678 _public function_ `FSignDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L685 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FClampDataflowNode`  
`struct FClampDataflowNode : public FDataflowNode`  
_L695-723_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Clamps X to be between Min and Max, inclusive DEPRECATED 5.6: Use the Clamp node that support all numerics types
- L702 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Clamp", meta = (DataflowInput))`
- L705 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Clamp", meta = (DataflowInput))`
- L708 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Clamp", meta = (DataflowInput))`
- L711 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L713 _public function_ `FClampDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L722 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFitDataflowNode`  
`struct FFitDataflowNode : public FDataflowNode`  
_L732-768_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Fits a value from one range to another Returns a number between newmin and newmax that is relative to num in the range between oldmin and oldmax. If the value is outside the old range, it will be clamped to the new range.
- L739 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Fit", meta = (DataflowInput))`
- L742 _public member_ `float OldMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Fit", meta = (DataflowInput))`
- L745 _public member_ `float OldMax = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Fit", meta = (DataflowInput))`
- L748 _public member_ `float NewMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Fit", meta = (DataflowInput))`
- L751 _public member_ `float NewMax = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Fit", meta = (DataflowInput))`
- L754 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L756 _public function_ `FFitDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L767 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FEFitDataflowNode`  
`struct FEFitDataflowNode : public FDataflowNode`  
_L777-813_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Fits a value from one range to another Takes the value num from the range (oldmin, oldmax) and shifts it to the corresponding value in the new range (newmin, newmax). Unlike fit, this function does not clamp values in the given range.
- L784 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "EFit", meta = (DataflowInput))`
- L787 _public member_ `float OldMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "EFit", meta = (DataflowInput))`
- L790 _public member_ `float OldMax = 1.f;` — `UPROPERTY(EditAnywhere, Category = "EFit", meta = (DataflowInput))`
- L793 _public member_ `float NewMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "EFit", meta = (DataflowInput))`
- L796 _public member_ `float NewMax = 1.f;` — `UPROPERTY(EditAnywhere, Category = "EFit", meta = (DataflowInput))`
- L799 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L801 _public function_ `FEFitDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L812 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FPowDataflowNode`  
`struct FPowDataflowNode : public FDataflowNode`  
_L821-845_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L828 _public member_ `float Base = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Pow", meta = (DataflowInput))`
- L831 _public member_ `float Exp = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Pow", meta = (DataflowInput))`
- L834 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L836 _public function_ `FPowDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L844 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FLogDataflowNode`  
`struct FLogDataflowNode : public FDataflowNode`  
_L853-877_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns log of A base Base (if Base ^ R == A, where R is ReturnValue)
- L860 _public member_ `float Base = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Log", meta = (DataflowInput))`
- L863 _public member_ `float A = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Log", meta = (DataflowInput))`
- L866 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L868 _public function_ `FLogDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L876 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FLogeDataflowNode`  
`struct FLogeDataflowNode : public FDataflowNode`  
_L885-905_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns log of A base Base (if Base ^ R == A, where R is ReturnValue)
- L892 _public member_ `float A = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Loge", meta = (DataflowInput))`
- L895 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L897 _public function_ `FLogeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L904 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FLerpDataflowNode`  
`struct FLerpDataflowNode : public FDataflowNode`  
_L913-941_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Linearly interpolates between A and B based on Alpha. (100% of A when Alpha = 0.0 and 100% of B when Alpha = 1.0)
- L920 _public member_ `float A = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Lerp", meta = (DataflowInput))`
- L923 _public member_ `float B = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Lerp", meta = (DataflowInput))`
- L926 _public member_ `float Alpha = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Lerp", meta = (DataflowInput, UIMin = 0.f, UIMax = 100.f))`
- L929 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L931 _public function_ `FLerpDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L940 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FWrapDataflowNode`  
`struct FWrapDataflowNode : public FDataflowNode`  
_L949-977_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L956 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Wrap", meta = (DataflowInput))`
- L959 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Wrap", meta = (DataflowInput))`
- L962 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Wrap", meta = (DataflowInput))`
- L965 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L967 _public function_ `FWrapDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L976 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FExpDataflowNode`  
`struct FExpDataflowNode : public FDataflowNode`  
_L985-1005_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L992 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Exp", meta = (DataflowInput))`
- L995 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L997 _public function_ `FExpDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1004 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSinDataflowNode`  
`struct FSinDataflowNode : public FDataflowNode`  
_L1013-1033_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns the sine of A. (Expects Radians)
- L1020 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Sin", meta = (DataflowInput))`
- L1023 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1025 _public function_ `FSinDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1032 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FArcSinDataflowNode`  
`struct FArcSinDataflowNode : public FDataflowNode`  
_L1041-1061_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns the arcsine of A. (ReturnValue is in Radians)
- L1048 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "ArcSin", meta = (DataflowInput, UIMin = -1.f, UIMax = 1.f))`
- L1051 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1053 _public function_ `FArcSinDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1060 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCosDataflowNode`  
`struct FCosDataflowNode : public FDataflowNode`  
_L1069-1089_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns the cosine of A. (Expects Radians)
- L1076 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Cos", meta = (DataflowInput))`
- L1079 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1081 _public function_ `FCosDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1088 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FArcCosDataflowNode`  
`struct FArcCosDataflowNode : public FDataflowNode`  
_L1097-1117_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns the arccosine of A. (ReturnValue is in Radians)
- L1104 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "ArcCos", meta = (DataflowInput, UIMin = -1.f, UIMax = 1.f))`
- L1107 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1109 _public function_ `FArcCosDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1116 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FTanDataflowNode`  
`struct FTanDataflowNode : public FDataflowNode`  
_L1125-1145_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns the cosine of A. (Expects Radians)
- L1132 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Tan", meta = (DataflowInput))`
- L1135 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1137 _public function_ `FTanDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1144 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FArcTanDataflowNode`  
`struct FArcTanDataflowNode : public FDataflowNode`  
_L1153-1173_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns the arccosine of A. (ReturnValue is in Radians)
- L1160 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "ArcTan", meta = (DataflowInput))`
- L1163 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1165 _public function_ `FArcTanDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1172 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FArcTan2DataflowNode`  
`struct FArcTan2DataflowNode : public FDataflowNode`  
_L1181-1205_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns the arccosine of A. (ReturnValue is in Radians)
- L1188 _public member_ `float Y = 0.f;` — `UPROPERTY(EditAnywhere, Category = "ArcTan2", meta = (DataflowInput))`
- L1191 _public member_ `float X = 0.f;` — `UPROPERTY(EditAnywhere, Category = "ArcTan2", meta = (DataflowInput))`
- L1194 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1196 _public function_ `FArcTan2DataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1204 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FNormalizeToRangeDataflowNode`  
`struct FNormalizeToRangeDataflowNode : public FDataflowNode`  
_L1213-1241_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Returns Float normalized to the given range
- L1220 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "NormalizeToRange", meta = (DataflowInput))`
- L1223 _public member_ `float RangeMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "NormalizeToRange", meta = (DataflowInput))`
- L1226 _public member_ `float RangeMax = 1.f;` — `UPROPERTY(EditAnywhere, Category = "NormalizeToRange", meta = (DataflowInput))`
- L1229 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1231 _public function_ `FNormalizeToRangeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1240 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FScaleVectorDataflowNode`  
`struct FScaleVectorDataflowNode : public FDataflowNode`  
_L1249-1273_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L1256 _public member_ `FVector Vector = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "ScaleVector", meta = (DataflowInput))`
- L1259 _public member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "ScaleVector", meta = (DataflowInput))`
- L1262 _public member_ `FVector ScaledVector = FVector(0.f);` — `UPROPERTY(meta = (DataflowOutput))`
- L1264 _public function_ `FScaleVectorDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1272 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDotProductDataflowNode`  
`struct FDotProductDataflowNode : public FDataflowNode`  
_L1281-1305_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L1288 _public member_ `FVector VectorA = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "DotProduct", meta = (DataflowInput))`
- L1291 _public member_ `FVector VectorB = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "DotProduct", meta = (DataflowInput))`
- L1294 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1296 _public function_ `FDotProductDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1304 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCrossProductDataflowNode`  
`struct FCrossProductDataflowNode : public FDataflowNode`  
_L1313-1337_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L1320 _public member_ `FVector VectorA = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "CrossProduct", meta = (DataflowInput))`
- L1323 _public member_ `FVector VectorB = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "CrossProduct", meta = (DataflowInput))`
- L1326 _public member_ `FVector ReturnValue = FVector(0.f);` — `UPROPERTY(meta = (DataflowOutput))`
- L1328 _public function_ `FCrossProductDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1336 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FNormalizeDataflowNode`  
`struct FNormalizeDataflowNode : public FDataflowNode`  
_L1345-1369_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L1352 _public member_ `FVector VectorA = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Normalize", meta = (DataflowInput))`
- L1355 _public member_ `float Tolerance = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "Normalize", meta = (DataflowInput))`
- L1358 _public member_ `FVector ReturnValue = FVector(0.f);` — `UPROPERTY(meta = (DataflowOutput))`
- L1360 _public function_ `FNormalizeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1368 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FLengthDataflowNode`  
`struct FLengthDataflowNode : public FDataflowNode`  
_L1377-1397_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L1384 _public member_ `FVector Vector = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Length", meta = (DataflowInput))`
- L1387 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1389 _public function_ `FLengthDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1396 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDistanceDataflowNode`  
`struct FDistanceDataflowNode : public FDataflowNode`  
_L1405-1429_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L1412 _public member_ `FVector PointA = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Distance", meta = (DataflowInput))`
- L1415 _public member_ `FVector PointB = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Distance", meta = (DataflowInput))`
- L1418 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1420 _public function_ `FDistanceDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1428 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FIsNearlyZeroDataflowNode`  
`struct FIsNearlyZeroDataflowNode : public FDataflowNode`  
_L1437-1457_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L1444 _public member_ `float Float = 0.f;` — `UPROPERTY(EditAnywhere, Category = "IsNearlyZero", meta = (DataflowInput))`
- L1447 _public member_ `bool ReturnValue = false;` — `UPROPERTY(meta = (DataflowOutput))`
- L1449 _public function_ `FIsNearlyZeroDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1456 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRandomFloatDataflowNode`  
`struct FRandomFloatDataflowNode : public FDataflowNode`  
_L1465-1490_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Generates a random float
- L1472 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L1475 _public member_ `float RandomSeed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Seed", meta = (DataflowInput, EditCondition = "bDeterministic"))`
- L1478 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1480 _public function_ `FRandomFloatDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1488 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRandomFloatInRangeDataflowNode`  
`struct FRandomFloatInRangeDataflowNode : public FDataflowNode`  
_L1498-1531_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Generates a random float between Min and Max
- L1505 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L1508 _public member_ `float RandomSeed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Seed", meta = (DataflowInput, EditCondition = "bDeterministic"))`
- L1511 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))`
- L1514 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))`
- L1517 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1519 _public function_ `FRandomFloatInRangeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1529 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRandomUnitVectorDataflowNode`  
`struct FRandomUnitVectorDataflowNode : public FDataflowNode`  
_L1540-1565_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Returns a random vector with length of 1
- L1547 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L1550 _public member_ `float RandomSeed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Seed", meta = (DataflowInput, EditCondition = "bDeterministic"))`
- L1553 _public member_ `FVector ReturnValue = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput))`
- L1555 _public function_ `FRandomUnitVectorDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1563 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRandomUnitVectorInConeDataflowNode`  
`struct FRandomUnitVectorInConeDataflowNode : public FDataflowNode`  
_L1574-1609_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Returns a random vector with length of 1, within the specified cone, with uniform random distribution
- L1581 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L1584 _public member_ `float RandomSeed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Seed", meta = (DataflowInput, EditCondition = "bDeterministic"))`
- L1588 _public member_ `FVector ConeDirection = FVector(0.0, 0.0, 1.0);` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))` — The base "center" direction of the cone
- L1592 _public member_ `float ConeHalfAngle = PI / 4.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))` — The half-angle of the cone (from ConeDir to edge), in degrees
- L1595 _public member_ `FVector ReturnValue = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput))`
- L1597 _public function_ `FRandomUnitVectorInConeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1607 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRadiansToDegreesDataflowNode`  
`struct FRadiansToDegreesDataflowNode : public FDataflowNode`  
_L1618-1639_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts radians to degrees
- L1625 _public member_ `float Radians = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Radians", meta = (DataflowInput))`
- L1628 _public member_ `float Degrees = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1630 _public function_ `FRadiansToDegreesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1637 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDegreesToRadiansDataflowNode`  
`struct FDegreesToRadiansDataflowNode : public FDataflowNode`  
_L1648-1669_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Converts degrees to radians
- L1655 _public member_ `float Degrees = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Degrees", meta = (DataflowInput))`
- L1658 _public member_ `float Radians = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1660 _public function_ `FDegreesToRadiansDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1667 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EMathConstantsEnum`  
`enum class EMathConstantsEnum : uint8`  
_L1672-1691_
- reflection: `UENUM(BlueprintType)`
- L1674 _public enumerator_ `Dataflow_MathConstants_Pi UMETA(DisplayName = "Pi")`
- L1675 _public enumerator_ `Dataflow_MathConstants_HalfPi UMETA(DisplayName = "HalfPi")`
- L1676 _public enumerator_ `Dataflow_MathConstants_TwoPi UMETA(DisplayName = "TwoPi")`
- L1677 _public enumerator_ `Dataflow_MathConstants_FourPi UMETA(DisplayName = "FourPi")`
- L1678 _public enumerator_ `Dataflow_MathConstants_InvPi UMETA(DisplayName = "InvPi")`
- L1679 _public enumerator_ `Dataflow_MathConstants_InvTwoPi UMETA(DisplayName = "InvTwoPi")`
- L1680 _public enumerator_ `Dataflow_MathConstants_Sqrt2 UMETA(DisplayName = "Sqrt2")`
- L1681 _public enumerator_ `Dataflow_MathConstants_InvSqrt2 UMETA(DisplayName = "InvSqrt2")`
- L1682 _public enumerator_ `Dataflow_MathConstants_Sqrt3 UMETA(DisplayName = "Sqrt3")`
- L1683 _public enumerator_ `Dataflow_MathConstants_InvSqrt3 UMETA(DisplayName = "InvSqrt3")`
- L1684 _public enumerator_ `Dataflow_FloatToInt_Function_E UMETA(DisplayName = "e")`
- L1685 _public enumerator_ `Dataflow_FloatToInt_Function_Gamma UMETA(DisplayName = "Gamma")`
- L1686 _public enumerator_ `Dataflow_FloatToInt_Function_GoldenRatio UMETA(DisplayName = "GoldenRatio")`
- L1687 _public enumerator_ `Dataflow_FloatToInt_Function_ZeroTolerance UMETA(DisplayName = "ZeroTolerance")`
- L1690 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FMathConstantsDataflowNode`  
`struct FMathConstantsDataflowNode : public FDataflowNode`  
_L1699-1721_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Offers a selection of Math constants
- L1707 _public member_ `EMathConstantsEnum Constant = EMathConstantsEnum::Dataflow_MathConstants_Pi;` — `UPROPERTY(EditAnywhere, Category = "Constants")` — Math constant to output
- L1711 _public member_ `float ReturnValue = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Selected Math constant
- L1713 _public function_ `FMathConstantsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1719 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FOneMinusDataflowNode`  
`struct FOneMinusDataflowNode : public FDataflowNode`  
_L1729-1749_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Returns 1.0 - A
- L1736 _public member_ `float A = 0.f;` — `UPROPERTY(EditAnywhere, Category = "OneMinus", meta = (DataflowInput))`
- L1739 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1741 _public function_ `FOneMinusDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1748 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFloatMathExpressionDataflowNode`  
`struct FFloatMathExpressionDataflowNode : public FDataflowNode`  
_L1757-1784_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Expression node for floats
- L1764 _public member_ `float A = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Variables", meta = (DataflowInput))`
- L1767 _public member_ `float B = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Variables", meta = (DataflowInput))`
- L1770 _public member_ `float C = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Variables", meta = (DataflowInput))`
- L1773 _public member_ `float D = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Variables", meta = (DataflowInput))`
- L1776 _public member_ `FString Expression;` — `UPROPERTY(EditAnywhere, Category = "Expression")`
- L1779 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L1781 _public prototype_ `FFloatMathExpressionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1783 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMathExpressionDataflowNode`  
`struct FMathExpressionDataflowNode : public FDataflowNode`  
_L1792-1819_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Expression node for floats
- L1799 _public member_ `FDataflowNumericTypes A;` — `UPROPERTY(EditAnywhere, Category = Inputs, meta = (DataflowInput))`
- L1802 _public member_ `FDataflowNumericTypes B;` — `UPROPERTY(EditAnywhere, Category = Inputs, meta = (DataflowInput))`
- L1805 _public member_ `FDataflowNumericTypes C;` — `UPROPERTY(EditAnywhere, Category = Inputs, meta = (DataflowInput))`
- L1808 _public member_ `FDataflowNumericTypes D;` — `UPROPERTY(EditAnywhere, Category = Inputs, meta = (DataflowInput))`
- L1811 _public member_ `FString Expression;` — `UPROPERTY(EditAnywhere, Category = Expression)`
- L1814 _public member_ `FDataflowNumericTypes ReturnValue;` — `UPROPERTY(meta = (DataflowOutput))`
- L1816 _public prototype_ `FMathExpressionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1818 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Dataflow`
- L1821 _namespace_ `namespace UE`
- L1821 _namespace_ `namespace Dataflow` (scope `UE`)
- L1823 _prototype_ `void GeometryCollectionMathNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionMeshNodes.h` (Public)


#### struct `FPointsToMeshDataflowNode`  
`struct FPointsToMeshDataflowNode : public FDataflowNode`  
_L35-63_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts points into a DynamicMesh
- L43 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Points input
- L47 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Mesh output
- L51 _public member_ `int32 TriangleCount = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Mesh triangle count
- L53 _public function_ `FPointsToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L61 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMeshProcessorDataflowNodeBase`  
`struct FMeshProcessorDataflowNodeBase : public FDataflowNode #if CPP , public FDataflowDynamicConnections::IOwnerInterface #endif`  
_L70-142_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode,FDataflowDynamicConnections::IOwnerInterface`
- desc: Base class for nodes that applying Geometry Script Mesh Processors
- L80 _public prototype_ `FMeshProcessorDataflowNodeBase() = default;`
- L82 _public function_ `FMeshProcessorDataflowNodeBase(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid), OwningObject(InParam.OwningObject) , DynamicConnections(UE::Dataflow::FPin::EDirection::INPUT, this, Cast<UDataflow>(InParam.OwningObject))`
- L88 _public function_ `~FMeshProcessorDataflowNodeBase()`
- L96 _protected member_ `TSubclassOf<UDynamicMeshProcessorBlueprint> MeshProcessor;` — `UPROPERTY(EditAnywhere, Category = "Processor Type")`
- L99 _protected member_ `TObjectPtr<UDynamicMeshProcessorBlueprint> MeshProcessorInstance;` — `UPROPERTY(EditAnywhere, Instanced, NoClear, Category = "Instance", meta = (ShowOnlyInnerProperties))`
- L101 _protected prototype_ `virtual void PostSerialize(const FArchive& Ar) override final;`
- L103 _protected prototype_ `void ApplyParametersToBlueprintInstance(UE::Dataflow::FContext& Context) const;`
- L108 _private function_ `virtual FDataflowNode* GetOwner(const FDataflowDynamicConnections* Caller) override` — Begin IOwnerInterface
- L109 _private function_ `virtual const FInstancedPropertyBag& GetPropertyBag(const FDataflowDynamicConnections* Caller) override`
- L112 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& PropertyChangedEvent) override;`
- L115 _private function_ `virtual bool EvaluateOnGameThreadOnly() const override` — Evaluate on game thread unless the blueprint opts in to async evaluation
- L121 _private prototype_ `virtual void OnDoubleClicked(UE::Dataflow::FContext* Context) const override;`
- L125 _private member_ `FDelegateHandle BlueprintChangeDelegateHandle;` — Handling for the selected blueprint being changed under the node (e.g., recompiled)
- L126 _private prototype_ `void TeardownBlueprintEvent();`
- L127 _private prototype_ `void SetupBlueprintEvent();`
- L128 _private prototype_ `void RefreshConnectionsFromBlueprint();`
- L132 _private member_ `TObjectPtr<UObject> OwningObject;` — `UPROPERTY(Transient)` — Remember the parent UObject so that we can properly parent MeshProcessorInstance when the MeshProcessor changes
- L135 _private member_ `FDataflowDynamicConnections DynamicConnections;` — `UPROPERTY()`
- L138 _private member_ `FInstancedPropertyBag PropertyBag;` — `UPROPERTY()`
- L141 _private member_ `TMap<FName, FName> CachedPropertyNameMap;` — Cached mapping from property bag names to their source blueprint property names, which can be different due to sanitization

#### struct `FApplyMeshProcessorToMeshDataflowNode`  
`struct FApplyMeshProcessorToMeshDataflowNode final : public FMeshProcessorDataflowNodeBase`  
_L148-167_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FMeshProcessorDataflowNodeBase`
- desc: Apply a Geometry Script Mesh Processors to an input UDynamicMesh
- L157 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh", DataflowIntrinsic))` — Input/Output mesh
- L159 _public function_ `FApplyMeshProcessorToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FMeshProcessorDataflowNodeBase(InParam, InGuid)`
- L166 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FApplyMeshProcessorToGeometryCollectionDataflowNode`  
`struct FApplyMeshProcessorToGeometryCollectionDataflowNode final : public FMeshProcessorDataflowNodeBase`  
_L173-206_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FMeshProcessorDataflowNodeBase`
- desc: Apply a Geometry Script Mesh Processors to the geometry of selected transforms in a geometry collection
- L182 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Input/Output mesh
- L186 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — Selected bones will have geometry script processing applied (if they have geometry). If not connected, all geometry will be processed.
- L190 _public member_ `bool bWeldVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether the processed mesh will have edges at normal/UV/color seams welded so they are treated as one edge during processing.
- L194 _public member_ `bool bPreserveIsolatedVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to preserve isolated vertices which aren't used by any triangles.
- L196 _public function_ `FApplyMeshProcessorToGeometryCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FMeshProcessorDataflowNodeBase(InParam, InGuid)`
- L205 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionToMeshesDataflowNode`  
`struct FCollectionSelectionToMeshesDataflowNode : public FDataflowNode`  
_L214-248_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts a Collection to a set of Dynamic Meshes per selected Transform
- L222 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Collection to convert
- L226 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — Geometry on or under selected bones will be converted to meshes, optionally after filtering the selection to leaves. If not connected, all geometry will be processed.
- L230 _public member_ `bool bConvertSelectionToLeaves = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to convert the input selection to only leaves, which may directly store geometry. Otherwise, meshes for selected cluster nodes will be generated by appending together geometry from leaf nodes.
- L234 _public member_ `bool bWeldVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether the processed mesh will have edges at normal/UV/color seams welded so they are treated as one edge during processing.
- L238 _public member_ `bool bPreserveIsolatedVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to preserve isolated vertices which aren't used by any triangles.
- L242 _public member_ `TArray<TObjectPtr<UDynamicMesh>> Meshes;` — `UPROPERTY(meta = (DataflowOutput))` — Output Array of DynamicMesh
- L244 _public prototype_ `FCollectionSelectionToMeshesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L246 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FAppendMeshesToCollectionDataflowNode`  
`struct FAppendMeshesToCollectionDataflowNode : public FDataflowNode`  
_L256-282_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Append Array of Meshes to Collection
- L264 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Meshes will be appended to this collection
- L268 _public member_ `FDataflowTransformSelection AddedSelection;` — `UPROPERTY(meta = (DataflowOutput))` — Selection of added transforms
- L272 _public member_ `TArray<TObjectPtr<UDynamicMesh>> Meshes;` — `UPROPERTY(meta = (DataflowInput))` — Dynamic Meshes to append
- L276 _public member_ `int32 ParentIndex = -1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Index of parent bone for appended meshes. If invalid, meshes will be appended to a root node.
- L278 _public prototype_ `FAppendMeshesToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L280 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoxToMeshDataflowNode`  
`struct FBoxToMeshDataflowNode : public FDataflowNode`  
_L291-319_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts a BoundingBox into a DynamicMesh
- L299 _public member_ `FBox Box = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — BoundingBox input
- L303 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Mesh output
- L307 _public member_ `int32 TriangleCount = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Mesh triangle count
- L309 _public function_ `FBoxToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L317 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMeshInfoDataflowNode`  
`struct FMeshInfoDataflowNode : public FDataflowNode`  
_L328-351_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Collects information from the DynamicMesh and outputs it into a formatted string
- L336 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — DynamicMesh for the information
- L340 _public member_ `FString InfoString = FString("");` — `UPROPERTY(meta = (DataflowOutput))` — Formatted output string
- L342 _public function_ `FMeshInfoDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L349 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMeshToCollectionDataflowNode`  
`struct FMeshToCollectionDataflowNode : public FDataflowNode`  
_L358-395_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Converts a DynamicMesh to a Collection DEPRECATED 5.8 - use FMeshToCollectionDataflowNode_v2 instead
- L366 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — DynamicMesh to convert
- L370 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))` — Output Collection
- L374 _public member_ `bool bSplitIslands = false;` — `UPROPERTY(EditAnywhere, Category = "General|SplitIslands", meta = (DataflowInput))` — Whether to split the mesh into multiple bones based on the mesh connectivity
- L378 _public member_ `bool bConnectIslandsByVertexOverlap = false;` — `UPROPERTY(EditAnywhere, Category = "General|SplitIslands", meta = (EditCondition = "bSplitIslands"))` — Whether to consider coincident vertices as connected even if the topology does not connect them
- L382 _public member_ `float ConnectVerticesThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "General|SplitIslands", meta = (EditCondition = "bSplitIslands", Units = "cm", ClampMin = 0.0))` — Vertices closer than this distance are considered to be overlapping
- L386 _public member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "General|SplitIslands", meta = (EditCondition = "bSplitIslands", Units = "cm", ClampMin = 0.0))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L390 _public member_ `bool bAddClusterRootForSingleMesh = false;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (DataflowInput))` — Whether to add a root cluster for the single mesh case. Note if the mesh is split, the root cluster will always be added.
- L392 _public prototype_ `FMeshToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L394 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMeshToCollectionDataflowNode_v2`  
`struct FMeshToCollectionDataflowNode_v2 : public FDataflowNode`  
_L401-443_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts a DynamicMesh to a Collection
- L409 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — DynamicMesh to convert
- L413 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))` — Output Collection
- L417 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowOutput))` — Material array output
- L421 _private member_ `bool bSplitIslands = false;` — `UPROPERTY(EditAnywhere, Category = "General|SplitIslands", meta = (DataflowInput))` — Whether to split the mesh into multiple bones based on the mesh connectivity
- L425 _private member_ `bool bConnectIslandsByVertexOverlap = false;` — `UPROPERTY(EditAnywhere, Category = "General|SplitIslands", meta = (EditCondition = "bSplitIslands"))` — Whether to consider coincident vertices as connected even if the topology does not connect them
- L429 _private member_ `float ConnectVerticesThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "General|SplitIslands", meta = (EditCondition = "bSplitIslands", Units = "cm", ClampMin = 0.0))` — Vertices closer than this distance are considered to be overlapping
- L433 _private member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "General|SplitIslands", meta = (EditCondition = "bSplitIslands", Units = "cm", ClampMin = 0.0))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L437 _private member_ `bool bAddClusterRootForSingleMesh = false;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (DataflowInput))` — Whether to add a root cluster for the single mesh case. Note if the mesh is split, the root cluster will always be added.
- L439 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L442 _public prototype_ `FMeshToCollectionDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FCollectionToMeshDataflowNode`  
`struct FCollectionToMeshDataflowNode : public FDataflowNode`  
_L451-493_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Converts a Collection to a DynamicMesh DEPRECATED 5.8 - use FCollectionToMeshDataflowNode_v2 instead
- L459 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Collection to convert
- L463 _public member_ `bool bCenterPivot = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to translate the mesh geometry to be centered around its bounding box.
- L467 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output DynamicMesh
- L469 _public function_ `FCollectionToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L477 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L482 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — Geometry on or under selected bones will be appended to the output mesh. If not connected, all geometry will be processed.
- L486 _private member_ `bool bWeldVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether the processed mesh will have edges at normal/UV/color seams welded so they are treated as one edge during processing.
- L490 _private member_ `bool bPreserveIsolatedVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to preserve isolated vertices which aren't used by any triangles.

#### struct `FCollectionToMeshDataflowNode_v2`  
`struct FCollectionToMeshDataflowNode_v2 : public FDataflowNode`  
_L499-537_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts a Collection to a DataflowMesh
- L507 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Collection to convert
- L511 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowInput))` — Material array from the static mesh
- L515 _private member_ `bool bCenterPivot = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to translate the mesh geometry to be centered around its bounding box.
- L519 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — Geometry on or under selected bones will be appended to the output mesh. If not connected, all geometry will be processed.
- L523 _private member_ `bool bWeldVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether the processed mesh will have edges at normal/UV/color seams welded so they are treated as one edge during processing.
- L527 _private member_ `bool bPreserveIsolatedVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to preserve isolated vertices which aren't used by any triangles.
- L531 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output dataflow mesh
- L533 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L536 _public prototype_ `FCollectionToMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FStaticMeshToMeshDataflowNode`  
`struct FStaticMeshToMeshDataflowNode : public FDataflowNode`  
_L545-581_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Converts a StaticMesh into a DynamicMesh DEPRECATED 5.8 - use FStaticMeshToMeshDataflowNode_v2 instead
- L553 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DataflowInput))` — StaticMesh to convert
- L557 _public member_ `bool bUseHiRes = false;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DisplayName = "Use HiRes"))` — Output the HiRes representation, if set to true and HiRes doesn't exist it will output empty mesh
- L561 _public member_ `int32 LODLevel = 0;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DisplayName = "LOD Level"))` — Specifies the LOD level to use
- L565 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L569 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialArray;` — `UPROPERTY(meta = (DataflowOutput))` — Output materials
- L571 _public function_ `FStaticMeshToMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L579 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetMeshBoundingBoxDataflowNode`  
`struct FGetMeshBoundingBoxDataflowNode : public FDataflowNode`  
_L588-615_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Get the local geometric bounding box a dynamic mesh DEPRECATED 5.8 - use FGetMeshBoundingBoxDataflowNode_v2 instead
- L596 _private member_ `TObjectPtr<const UDynamicMesh> Mesh = nullptr;` — `UPROPERTY(meta = (DataflowInput))` — dynamic mesh to compute the bouning box from
- L600 _private member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))` — Geometric bounding box of the input dynamic mesh
- L604 _private member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Center of the resulting bounding box
- L608 _private member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Dimensions of the resulting bounding box in centimers
- L610 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L613 _public prototype_ `FGetMeshBoundingBoxDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetMeshBoundingBoxDataflowNode_v2`  
`struct FGetMeshBoundingBoxDataflowNode_v2 : public FDataflowNode`  
_L621-648_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get the local geometric bounding box of a dataflow mesh
- L629 _private member_ `TObjectPtr<const UDataflowMesh> Mesh = nullptr;` — `UPROPERTY(meta = (DataflowInput))` — dynamic mesh to compute the bouning box from
- L633 _private member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))` — Geometric bounding box of the input dynamic mesh
- L637 _private member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Center of the resulting bounding box
- L641 _private member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Dimensions of the resulting bounding box in centimers
- L643 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L646 _public prototype_ `FGetMeshBoundingBoxDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMeshAppendDataflowNode`  
`struct FMeshAppendDataflowNode : public FDataflowNode`  
_L656-684_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Appends two meshes
- L664 _public member_ `TObjectPtr<UDynamicMesh> Mesh1;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh input
- L668 _public member_ `TObjectPtr<UDynamicMesh> Mesh2;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh input
- L672 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L674 _public function_ `FMeshAppendDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L682 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowMeshAppendDataflowNode`  
`struct FDataflowMeshAppendDataflowNode : public FDataflowNode`  
_L692-713_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Combine two Dataflow meshes
- L699 _public prototype_ `FDataflowMeshAppendDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L705 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh", DataflowIntrinsic))` — Mesh input/output
- L709 _private member_ `TObjectPtr<const UDataflowMesh> AppendMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to append
- L711 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMakeDataflowMeshDataflowNode`  
`struct FMakeDataflowMeshDataflowNode : public FDataflowNode`  
_L721-745_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Create a UDataflow mesh from an input UDynamicMesh and material array
- L728 _public prototype_ `FMakeDataflowMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L734 _private member_ `TObjectPtr<UDynamicMesh> InMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — DynamicMesh input
- L738 _private member_ `TArray<TObjectPtr<UMaterialInterface>> InMaterials;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Materials input
- L742 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — DataflowMesh output
- L744 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDuplicateMeshUVChannelNode`  
`struct FDuplicateMeshUVChannelNode : public FDataflowNode`  
_L752-776_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Create a new UV layer/channel in a UDataflowMesh
- L759 _public prototype_ `FDuplicateMeshUVChannelNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L765 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh", DataflowIntrinsic))` — DataflowMesh input/output
- L769 _private member_ `int32 SourceUVChannel = -1;` — `UPROPERTY(EditAnywhere, Category = Options)` — Index of the source UV channel
- L773 _private member_ `int32 NewUVChannel = -1;` — `UPROPERTY(meta = (DataflowOutput, DataflowUVChannel))` — Index of the added UV channel
- L775 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowMeshSplitIslandsMethod`  
`enum class EDataflowMeshSplitIslandsMethod : uint8`  
_L780-785_
- reflection: `UENUM(BlueprintType)`
- L782 _public enumerator_ `NoSplit`
- L783 _public enumerator_ `ByMeshTopology`
- L784 _public enumerator_ `ByVertexOverlap`

#### struct `FSplitMeshIslandsDataflowNode`  
`struct FSplitMeshIslandsDataflowNode : public FDataflowNode`  
_L794-822_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Split a mesh into a connected islands
- L801 _public prototype_ `FSplitMeshIslandsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L807 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh input
- L811 _private member_ `TArray<TObjectPtr<UDynamicMesh>> Meshes;` — `UPROPERTY(meta = (DataflowOutput))` — Meshes output
- L815 _private member_ `EDataflowMeshSplitIslandsMethod SplitMethod = EDataflowMeshSplitIslandsMethod::ByMeshTopology;` — `UPROPERTY(EditAnywhere, Category = "General")` — Whether to consider coincident vertices as connected even if the topology does not connect them
- L819 _private member_ `float ConnectVerticesThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = 0.0, EditCondition = "SplitMethod == EDataflowMeshSplitIslandsMethod::ByVertexOverlap"))` — Vertices closer than this distance are considered to be overlapping
- L821 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSplitDataflowMeshDataflowNode`  
`struct FSplitDataflowMeshDataflowNode : public FDataflowNode`  
_L830-856_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Split a UDataflow mesh into a UDynamicMesh and a material array
- L837 _public prototype_ `FSplitDataflowMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L843 _private member_ `TObjectPtr<UDataflowMesh> InMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — DataflowMesh input
- L847 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — DyanmicMesh output
- L851 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialArray;` — `UPROPERTY(meta = (DataflowOutput))` — Materials output
- L853 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L855 _private prototype_ `virtual void OnRenderOutput(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup, const TArray<UPrimitiveComponent*>& RenderComponents) const override;`

#### struct `FMeshCopyToPointsDataflowNode`  
`struct FMeshCopyToPointsDataflowNode : public FDataflowNode`  
_L867-904_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Copies the same mesh with scale onto points
- L875 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Points to copy meshes onto
- L879 _public member_ `TObjectPtr<UDynamicMesh> MeshToCopy;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DisplayName = "MeshToScatter"))` — Mesh to copy onto points
- L883 _public member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Copy")` — Scale applied to the mesh
- L887 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — merged result mesh
- L891 _public member_ `TArray<TObjectPtr<UDynamicMesh>> Meshes;` — `UPROPERTY(meta = (DataflowOutput))` — Result meshes as individual ones
- L893 _public function_ `FMeshCopyToPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L902 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetMeshDataDataflowNode`  
`struct FGetMeshDataDataflowNode : public FDataflowNode`  
_L913-946_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Outputs Mesh data
- L921 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh for the data
- L925 _public member_ `int32 VertexCount = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of vertices
- L929 _public member_ `int32 EdgeCount = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of edges
- L933 _public member_ `int32 TriangleCount = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of triangles
- L935 _public function_ `FGetMeshDataDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L944 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FStaticMeshToMeshDataflowNode_v2`  
`struct FStaticMeshToMeshDataflowNode_v2 : public FDataflowNode`  
_L952-978_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts a StaticMesh into a DataflowMesh
- L960 _private member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DataflowInput))` — StaticMesh to convert
- L964 _private member_ `bool bUseHiRes = false;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DisplayName = "Use HiRes"))` — Output the HiRes representation, if set to true and HiRes doesn't exist it will output empty mesh
- L968 _private member_ `int32 LODLevel = 0;` — `UPROPERTY(EditAnywhere, Category = "StaticMesh", meta = (DisplayName = "LOD Level"))` — Specifies the LOD level to use
- L972 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output Dataflow mesh
- L974 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L977 _public prototype_ `FStaticMeshToMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetMeshBoundingSphereDataflowNode`  
`struct FGetMeshBoundingSphereDataflowNode : public FDataflowNode`  
_L984-1011_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get the local geometric bounding sphere of a dataflow mesh
- L992 _private member_ `TObjectPtr<const UDataflowMesh> Mesh = nullptr;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Dataflow mesh to compute the bounding sphere from
- L996 _private member_ `FSphere BoundingSphere = FSphere(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))` — Geometric bounding sphere of the input dataflow mesh
- L1000 _private member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Center of the resulting bounding sphere
- L1004 _private member_ `float Radius = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Radius of the resulting bounding sphere in centimers
- L1006 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1009 _public prototype_ `FGetMeshBoundingSphereDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Dataflow`
- L1013 _namespace_ `namespace UE`
- L1013 _namespace_ `namespace Dataflow` (scope `UE`)
- L1015 _prototype_ `void GeometryCollectionMeshNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionNodes.h` (Public)


#### struct `FGetCollectionFromAssetDataflowNode`  
`struct FGetCollectionFromAssetDataflowNode : public FDataflowNode`  
_L33-53_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.7"))`
- inherits: `FDataflowNode`
- desc: Get a collection from a geometry collecion asset DEPRECATED 5.7 : use GeometryCollectionToCollection node instead
- L40 _public member_ `TObjectPtr<UGeometryCollection> CollectionAsset;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "Asset"))`
- L43 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))`
- L45 _public function_ `FGetCollectionFromAssetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L52 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FAppendCollectionAssetsDataflowNode`  
`struct FAppendCollectionAssetsDataflowNode : public FDataflowNode`  
_L62-94_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Description for this node
- L68 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L71 _public member_ `FManagedArrayCollection Collection1;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection", DataflowPassthrough = "Collection1"))`
- L74 _public member_ `FManagedArrayCollection Collection2;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Collection"))`
- L77 _public member_ `TArray<FString> GeometryGroupGuidsOut1;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "GeometryGroupIndicesOut1"))`
- L80 _public member_ `TArray<FString> GeometryGroupGuidsOut2;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "GeometryGroupIndicesOut2"))`
- L82 _public function_ `FAppendCollectionAssetsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L92 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FPrintStringDataflowNode`  
`struct FPrintStringDataflowNode : public FDataflowNode`  
_L103-132_
- reflection: `USTRUCT(meta = (Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Description for this node DEPRECATED 5.5 - use Print node ( core nodes )
- L110 _public member_ `bool bPrintToScreen = true;` — `UPROPERTY(EditAnywhere, Category = "Print")`
- L113 _public member_ `bool bPrintToLog = true;` — `UPROPERTY(EditAnywhere, Category = "Print")`
- L116 _public member_ `FColor Color = FColor::White;` — `UPROPERTY(EditAnywhere, Category = "Print")`
- L119 _public member_ `float Duration = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Print")`
- L122 _public member_ `FString String = FString("");` — `UPROPERTY(EditAnywhere, Category = "Print", meta = (DataflowInput))`
- L124 _public function_ `FPrintStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L130 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FLogStringDataflowNode`  
`struct FLogStringDataflowNode : public FDataflowNode`  
_L141-161_
- reflection: `USTRUCT(meta=(Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Description for this node DEPRECATED - use Print node ( core nodes )
- L148 _public member_ `bool bPrintToLog = true;` — `UPROPERTY(EditAnywhere, Category = "Print")`
- L151 _public member_ `FString String = FString("");` — `UPROPERTY(EditAnywhere, Category = "Print", meta = (DataflowInput))`
- L153 _public function_ `FLogStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L159 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoundingBoxDataflowNode`  
`struct FBoundingBoxDataflowNode : public FDataflowNode`  
_L168-193_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Get the geometric bounding box a collection in collection space DEPRECATED 5.8 - use CollectionBounds node instead
- L176 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))` — Collection to compute the bouning box from
- L180 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))` — Geometric bounding box of the input collection
- L184 _public member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Center of the resulting bounding box
- L188 _public member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Dimensions of the resulting bounding box in centimers
- L190 _public prototype_ `FBoundingBoxDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L192 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoundingBoxRatioDataflowNode`  
`struct FBoundingBoxRatioDataflowNode : public FDataflowNode`  
_L201-230_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get the bounding box a collection and compute its box ratio from a reference size The reference size is the length of a perfect cube representing a reference volume
- L207 _public prototype_ `FBoundingBoxRatioDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L212 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))` — Collection to compute the bounding box and ratio from
- L216 _private member_ `float ReferenceBoxSize = 100;` — `UPROPERTY(EditAnywhere, Category = "Proximity", meta = (DataflowInput, ClampMin = "0", UIMin = "0", Units = cm))` — Reference box size to use to compute the ratio
- L220 _private member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))` — Geometric bounding box of the input collection
- L224 _private member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Dimensions of the resulting bounding box in centimers
- L227 _private member_ `float BoxRatio = 1.0;` — `UPROPERTY(meta = (DataflowOutput))`
- L229 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoundingSphereDataflowNode`  
`struct FBoundingSphereDataflowNode : public FDataflowNode`  
_L236-257_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Compute the boudning sphere of the geometrry of a collection
- L243 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))`
- L246 _public member_ `FSphere BoundingSphere = FSphere(ForceInit);` — `UPROPERTY(meta = (DataflowOutput))`
- L248 _public function_ `FBoundingSphereDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L255 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EBoxLengthMeasurementMethod`  
`enum class EBoxLengthMeasurementMethod : uint8`  
_L260-268_
- reflection: `UENUM()`
- L262 _public enumerator_ `XAxis`
- L263 _public enumerator_ `YAxis`
- L264 _public enumerator_ `ZAxis`
- L265 _public enumerator_ `ShortestAxis`
- L266 _public enumerator_ `LongestAxis`
- L267 _public enumerator_ `Diagonal`

#### struct `FGetBoxLengthsDataflowNode`  
`struct FGetBoxLengthsDataflowNode : public FDataflowNode`  
_L276-323_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Create an array of lengths of bounding boxes (measured along an axis, diagonal, or the max/min axes) from an array of bounding boxes
- L284 _public member_ `TArray<FBox> Boxes;` — `UPROPERTY(meta = (DataflowInput))`
- L287 _public member_ `TArray<float> Lengths;` — `UPROPERTY(meta = (DataflowOutput))`
- L290 _public member_ `EBoxLengthMeasurementMethod MeasurementMethod = EBoxLengthMeasurementMethod::Diagonal;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L292 _public function_ `inline double BoxToMeasurement(const FBox& Box) const`
- L314 _public function_ `FGetBoxLengthsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L321 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBoundingBoxAverageExtentsDataflowNode`  
`struct FBoundingBoxAverageExtentsDataflowNode : public FDataflowNode`  
_L329-363_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get the bounding box average extents information
- L335 _public prototype_ `FBoundingBoxAverageExtentsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L340 _private member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput))` — Bounding box to get the information from
- L344 _private member_ `float AverageExtents = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Average of the 3 axis extents
- L348 _private member_ `float AverageHalfExtents = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Average of the 3 axis half extents
- L352 _private member_ `float MinLength = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Minimum edge length of the box
- L356 _private member_ `float MaxLength = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Maximum edge length of the box
- L360 _private member_ `float LengthRatio = 1.f;` — `UPROPERTY(meta = (DataflowOutput))` — Ratio of the min edge length over the max edge length
- L362 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FExpandBoundingBoxDataflowNode`  
`struct FExpandBoundingBoxDataflowNode : public FDataflowNode`  
_L369-406_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Break a bounding box into individual components ( Min/Max corners, Center, HalfExtents and Volume )
- L377 _public member_ `FBox BoundingBox = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Box"))` — Bounding box to get the information from
- L381 _public member_ `FVector Min = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput))` — Minimum corner ofthe bounding box
- L385 _public member_ `FVector Max = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput))` — Maximum corner ofthe bounding box
- L389 _public member_ `FVector Center = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput))` — Center point of the bounding box
- L393 _public member_ `FVector HalfExtents = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput))` — Distances from the center to any corner along the three axis
- L397 _public member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(meta = (DataflowOutput))` — Dimensions of the bounding box
- L401 _public member_ `float Volume = 0.0;` — `UPROPERTY(meta = (DataflowOutput))` — Total volume of the bounding box
- L403 _public prototype_ `FExpandBoundingBoxDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L405 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FExpandBoundingSphereDataflowNode`  
`struct FExpandBoundingSphereDataflowNode : public FDataflowNode`  
_L414-442_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Expands data of FSphere
- L421 _public member_ `FSphere BoundingSphere = FSphere(ForceInit);` — `UPROPERTY(meta = (DataflowInput))`
- L424 _public member_ `FVector Center = FVector(0.0);` — `UPROPERTY(meta = (DataflowOutput))`
- L427 _public member_ `float Radius = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L430 _public member_ `float Volume = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L432 _public function_ `FExpandBoundingSphereDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L441 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FExpandVectorDataflowNode`  
`struct FExpandVectorDataflowNode : public FDataflowNode`  
_L451-481_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Expands a Vector into X, Y, Z components
- L458 _public member_ `FVector Vector = FVector(0.0);` — `UPROPERTY(meta = (DataflowInput, GizmoType = Translate))`
- L461 _public member_ `float X = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L464 _public member_ `float Y = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L467 _public member_ `float Z = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L470 _public function_ `FExpandVectorDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L479 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FStringAppendDataflowNode`  
`struct FStringAppendDataflowNode : public FDataflowNode`  
_L490-515_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Concatenates two strings together to make a new string DEPRECATED - use new version of the same node
- L497 _public member_ `FString String1 = FString("");` — `UPROPERTY(EditAnywhere, Category = "String", meta = (DataflowInput))`
- L500 _public member_ `FString String2 = FString("");` — `UPROPERTY(EditAnywhere, Category = "String", meta = (DataflowInput))`
- L503 _public member_ `FString String = FString("");` — `UPROPERTY(meta = (DataflowOutput))`
- L505 _public function_ `FStringAppendDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L513 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FStringAppendDataflowNode_v2`  
`struct FStringAppendDataflowNode_v2 : public FDataflowNode`  
_L523-552_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Concatenates strings together to make a new string
- L530 _private member_ `TArray<FDataflowStringConvertibleTypes> Inputs;` — `UPROPERTY()`
- L533 _private member_ `FString String = FString("");` — `UPROPERTY(meta = (DataflowOutput))`
- L536 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L537 _private prototype_ `virtual bool CanAddPin() const override;`
- L538 _private prototype_ `virtual bool CanRemovePin() const override;`
- L539 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L540 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L541 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L542 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L545 _private prototype_ `UE::Dataflow::TConnectionReference<FDataflowStringConvertibleTypes> GetConnectionReference(int32 Index) const;`
- L547 _private member_ `static constexpr int32 NumOtherInputs = 0;` — No other inputs
- L548 _private member_ `static constexpr int32 NumInitialVariableInputs = 2;`
- L551 _public prototype_ `FStringAppendDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FHashStringDataflowNode`  
`struct FHashStringDataflowNode : public FDataflowNode`  
_L560-583_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Generates a hash value from a string
- L568 _public member_ `FString String = FString("");` — `UPROPERTY(meta = (DataflowInput))` — String to hash
- L572 _public member_ `int32 Hash = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Generated hash value
- L574 _public function_ `FHashStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L581 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FHashVectorDataflowNode`  
`struct FHashVectorDataflowNode : public FDataflowNode`  
_L592-615_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Generates a hash value from a vector
- L600 _public member_ `FVector Vector = FVector(0.0);` — `UPROPERTY(meta = (DataflowInput))` — Vector to hash
- L604 _public member_ `int32 Hash = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Generated hash value
- L606 _public function_ `FHashVectorDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L613 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetBoundingBoxesFromCollectionDataflowNode`  
`struct FGetBoundingBoxesFromCollectionDataflowNode : public FDataflowNode`  
_L624-652_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Gets BoundingBoxes of pieces from a Collection
- L632 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))` — Input Collection
- L636 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — The BoundingBoxes will be output for the bones selected in the TransformSelection
- L640 _public member_ `TArray<FBox> BoundingBoxes;` — `UPROPERTY(meta = (DataflowOutput))` — Output BoundingBoxes
- L642 _public function_ `FGetBoundingBoxesFromCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L650 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetRootIndexFromCollectionDataflowNode`  
`struct FGetRootIndexFromCollectionDataflowNode : public FDataflowNode`  
_L661-682_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get the root node index
- L668 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))`
- L671 _public member_ `int32 RootIndex = INDEX_NONE;` — `UPROPERTY(meta = (DataflowOutput))`
- L673 _public function_ `FGetRootIndexFromCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L680 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetCentroidsFromCollectionDataflowNode`  
`struct FGetCentroidsFromCollectionDataflowNode : public FDataflowNode`  
_L692-743_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Gets centroids of pieces from a Collection
- L700 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))` — Input Collection
- L704 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — The centroids will be output for the bones selected in the TransformSelection
- L708 _private member_ `bool bColorByLevel = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Control point color by level or setting
- L712 _private member_ `FLinearColor Color = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (EditCondition = "bColorByLevel == false", EditConditionHides))` — Point color
- L716 _private member_ `bool bSizeByLevel = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Control the point size by level or setting
- L720 _private member_ `float Size = 8.f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (EditCondition = "bSizeByLevel == false", EditConditionHides))` — Point size
- L724 _private member_ `FRuntimeFloatCurve PointSize;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Float curve to control point size by level
- L728 _private member_ `TArray<FVector> Centroids = TArray<FVector>();` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Points"))` — Output centroids
- L732 _private member_ `TArray<int32> Levels;` — `UPROPERTY(meta = (DataflowOutput))` — Hidden output to store computed level values for centroids
- L734 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L737 _private prototype_ `virtual bool CanDebugDraw() const override;`
- L738 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L739 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L742 _public prototype_ `FGetCentroidsFromCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### enum `ERotationOrderEnum`  
`enum class ERotationOrderEnum : uint8`  
_L747-758_
- reflection: `UENUM(BlueprintType)`
- L749 _public enumerator_ `Dataflow_RotationOrder_XYZ UMETA(DisplayName = "XYZ")`
- L750 _public enumerator_ `Dataflow_RotationOrder_YZX UMETA(DisplayName = "YZX")`
- L751 _public enumerator_ `Dataflow_RotationOrder_ZXY UMETA(DisplayName = "ZXY")`
- L752 _public enumerator_ `Dataflow_RotationOrder_XZY UMETA(DisplayName = "XZY")`
- L753 _public enumerator_ `Dataflow_RotationOrder_YXZ UMETA(DisplayName = "YXZ")`
- L754 _public enumerator_ `Dataflow_RotationOrder_ZYX UMETA(DisplayName = "ZYX")`
- L757 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FTransformCollectionDataflowNode`  
`struct FTransformCollectionDataflowNode : public FDataflowNode`  
_L766-816_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Transforms a Collection
- L774 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Output mesh
- L778 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — Transform selection for transforming
- L782 _public member_ `FVector Translate = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, GizmoType = Translate))` — Translation
- L786 _public member_ `ERotationOrderEnum RotationOrder = ERotationOrderEnum::Dataflow_RotationOrder_XYZ;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Rotation Order
- L790 _public member_ `FVector Rotate = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, GizmoType = Rotate, GizmoPosition = Translate))` — Rotation
- L794 _public member_ `FVector Scale = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (UIMin = 0.001f), meta = (DataflowInput, GizmoType = Scale, GizmoPosition = Translate))` — Scale
- L798 _public member_ `float UniformScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (UIMin = 0.001f))` — Uniform scale
- L802 _public member_ `FVector RotatePivot = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Pivot")` — Pivot for the rotation
- L806 _public member_ `FVector ScalePivot = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Pivot")` — Pivot for the scale
- L810 _public member_ `bool bInvertTransformation = false;` — `UPROPERTY(EditAnywhere, Category = "General")` — Invert the transformation
- L812 _public prototype_ `FTransformCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L814 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBakeTransformsInCollectionDataflowNode`  
`struct FBakeTransformsInCollectionDataflowNode : public FDataflowNode`  
_L825-844_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Bake transforms in Collection
- L833 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to bake transforms in
- L835 _public function_ `FBakeTransformsInCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L842 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FTransformMeshDataflowNode`  
`struct FTransformMeshDataflowNode : public FDataflowNode`  
_L851-913_
- reflection: `USTRUCT(meta = (Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Transforms a mesh DEPRECATED 5.8 - use FTransformMeshDataflowNode_v2 instead
- L859 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh", DataflowIntrinsic))` — Output mesh
- L863 _public member_ `FVector Translate = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, GizmoType = Translate))` — Translation
- L867 _public member_ `ERotationOrderEnum RotationOrder = ERotationOrderEnum::Dataflow_RotationOrder_XYZ;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Rotation Order
- L871 _public member_ `FVector Rotate = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, GizmoType = Rotate, GizmoPosition = Translate))` — Rotation
- L875 _public member_ `FVector Scale = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (UIMin = 0.001f, DataflowInput, GizmoType = Scale, GizmoPosition = Translate))` — Scale
- L883 _public member_ `float UniformScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (UIMin = 0.001f, DataflowInput))` — Uniform scale
- L887 _public member_ `FVector RotatePivot = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Pivot")` — Pivot for the rotation
- L891 _public member_ `FVector ScalePivot = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Pivot", meta = (DataflowInput))` — Pivot for the scale
- L895 _public member_ `bool bInvertTransformation = false;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (DataflowInput))` — Invert the transformation
- L897 _public function_ `FTransformMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L911 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ECompareOperationEnum`  
`enum class ECompareOperationEnum : uint8`  
_L916-927_
- reflection: `UENUM(BlueprintType)`
- L918 _public enumerator_ `Dataflow_Compare_Equal UMETA(DisplayName = "==")`
- L919 _public enumerator_ `Dataflow_Compare_Smaller UMETA(DisplayName = "<")`
- L920 _public enumerator_ `Dataflow_Compare_SmallerOrEqual UMETA(DisplayName = "<=")`
- L921 _public enumerator_ `Dataflow_Compare_Greater UMETA(DisplayName = ">")`
- L922 _public enumerator_ `Dataflow_Compare_GreaterOrEqual UMETA(DisplayName = ">=")`
- L923 _public enumerator_ `Dataflow_Compare_NotEqual UMETA(DisplayName = "!=")`
- L926 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FCompareIntDataflowNode`  
`struct FCompareIntDataflowNode : public FDataflowNode`  
_L935-967_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Comparison between integers
- L943 _public member_ `ECompareOperationEnum Operation = ECompareOperationEnum::Dataflow_Compare_Equal;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Comparison operation
- L947 _public member_ `int32 IntA = 0;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Int input
- L951 _public member_ `int32 IntB = 0;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Int input
- L955 _public member_ `bool Result = false;` — `UPROPERTY(meta = (DataflowOutput))` — Boolean result of the comparison
- L957 _public function_ `FCompareIntDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L965 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCompareFloatDataflowNode`  
`struct FCompareFloatDataflowNode : public FDataflowNode`  
_L976-1008_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Comparison between floats
- L984 _public member_ `ECompareOperationEnum Operation = ECompareOperationEnum::Dataflow_Compare_Equal;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Comparison operation
- L988 _public member_ `float FloatA = 0;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Float input
- L992 _public member_ `float FloatB = 0;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Float input
- L996 _public member_ `bool Result = false;` — `UPROPERTY(meta = (DataflowOutput))` — Boolean result of the comparison
- L998 _public function_ `FCompareFloatDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1006 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EBooleanOperationEnum`  
`enum class EBooleanOperationEnum : uint8`  
_L1012-1020_
- reflection: `UENUM(BlueprintType)`
- L1014 _public enumerator_ `Dataflow_And UMETA(DisplayName = "&&")`
- L1015 _public enumerator_ `Dataflow_Or UMETA(DisplayName = "||")`
- L1016 _public enumerator_ `Dataflow_Not UMETA(DisplayName = "!")`
- L1019 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FBooleanOperationDataflowNode`  
`struct FBooleanOperationDataflowNode : public FDataflowNode`  
_L1028-1060_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Boolean operations
- L1036 _public member_ `EBooleanOperationEnum Operation = EBooleanOperationEnum::Dataflow_And;` — `UPROPERTY(EditAnywhere, Category = "Boolean")` — Boolean operation
- L1040 _public member_ `bool bBoolA = false;` — `UPROPERTY(EditAnywhere, Category = "Boolean", Meta = (DataflowInput))` — Boolean input
- L1044 _public member_ `bool bBoolB = false;` — `UPROPERTY(EditAnywhere, Category = "Boolean", Meta = (EditCondition = "Operation != EBooleanOperationEnum::Dataflow_Not", DataflowInput))` — Boolean input
- L1048 _public member_ `bool bResult = false;` — `UPROPERTY(meta = (DataflowOutput))` — Boolean result of the operator
- L1050 _public function_ `FBooleanOperationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1058 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBranchMeshDataflowNode`  
`struct FBranchMeshDataflowNode : public FDataflowNode`  
_L1068-1101_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Branch between two mesh inputs based on boolean condition
- L1076 _public member_ `TObjectPtr<UDynamicMesh> MeshA;` — `UPROPERTY(meta = (DataflowInput))` — Mesh input
- L1080 _public member_ `TObjectPtr<UDynamicMesh> MeshB;` — `UPROPERTY(meta = (DataflowInput))` — Mesh input
- L1084 _public member_ `bool bCondition = false;` — `UPROPERTY(EditAnywhere, Category = "Branch")` — If true, Output = MeshA, otherwise Output = MeshB
- L1088 _public member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L1090 _public function_ `FBranchMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1099 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBranchCollectionDataflowNode`  
`struct FBranchCollectionDataflowNode : public FDataflowNode`  
_L1110-1144_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Branch between two Managed Array Collections based on Boolean condition
- L1119 _public member_ `FManagedArrayCollection TrueCollection;` — `UPROPERTY(meta = (DataflowInput))` — Collection input for the 'true' case
- L1123 _public member_ `FManagedArrayCollection FalseCollection;` — `UPROPERTY(meta = (DataflowInput))` — Collection input for the 'false' case
- L1127 _public member_ `bool bCondition = false;` — `UPROPERTY(EditAnywhere, Category = "Branch")` — Condition to select which Collection is chosen as ChosenCollection
- L1131 _public member_ `FManagedArrayCollection ChosenCollection;` — `UPROPERTY(meta = (DataflowOutput))` — Output Collection
- L1133 _public function_ `FBranchCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1142 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetSchemaDataflowNode`  
`struct FGetSchemaDataflowNode : public FDataflowNode`  
_L1154-1177_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Collects group and attribute information from the Collection and outputs it into a formatted string
- L1162 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))` — GeometryCollection  for the information
- L1166 _public member_ `FString String;` — `UPROPERTY(meta = (DataflowOutput))` — Formatted string containing the groups and attributes
- L1168 _public function_ `FGetSchemaDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1175 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FRemoveOnBreakDataflowNode`  
`struct FRemoveOnBreakDataflowNode : public FDataflowNode`  
_L1181-1225_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L1189 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to set theremoval data on
- L1193 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — selection to apply the data on ( if not specified the entire collection will be set )
- L1197 _public member_ `bool bEnabledRemoval = true;` — `UPROPERTY(EditAnywhere, Category = "Removal", meta = (DataflowInput))` — Whether or not to enable the removal on the selection
- L1201 _public member_ `FVector2f PostBreakTimer{0.0, 0.0};` — `UPROPERTY(EditAnywhere, Category = "Removal", meta = (DataflowInput))` — How long after the break the removal will start ( Min / Max )
- L1205 _public member_ `FVector2f RemovalTimer{0.0, 1.0};` — `UPROPERTY(EditAnywhere, Category = "Removal", meta = (DataflowInput))` — How long removal will last ( Min / Max )
- L1209 _public member_ `bool bClusterCrumbling = false;` — `UPROPERTY(EditAnywhere, Category = "Removal", meta = (DataflowInput))` — If applied to a cluster this will cause the cluster to crumble upon removal, otherwise will have no effect
- L1211 _public function_ `FRemoveOnBreakDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1223 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EAnchorStateEnum`  
`enum class EAnchorStateEnum : uint8`  
_L1229-1236_
- reflection: `UENUM(BlueprintType)`
- L1231 _public enumerator_ `Dataflow_AnchorState_Anchored UMETA(DisplayName = "Anchored")`
- L1232 _public enumerator_ `Dataflow_AnchorState_NotAnchored UMETA(DisplayName = "Not Anchored")`
- L1235 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FSetAnchorStateDataflowNode`  
`struct FSetAnchorStateDataflowNode : public FDataflowNode`  
_L1244-1275_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Sets the anchored state on the selected bones in a Collection
- L1252 _private member_ `EAnchorStateEnum AnchorState = EAnchorStateEnum::Dataflow_AnchorState_Anchored;` — `UPROPERTY(EditAnywhere, Category = "Anchoring")` — What anchor state to set on selected bones
- L1256 _private member_ `bool bSetNotSelectedBonesToOppositeState = false;` — `UPROPERTY(EditAnywhere, Category = "Anchoring")` — If true, sets the non selected bones to opposite anchor state
- L1260 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection to set anchor state on
- L1264 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection", DataflowIntrinsic))` — Bone selection for setting the state on
- L1266 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1269 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L1270 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L1274 _public prototype_ `FSetAnchorStateDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### enum `EDataflowGeometryCollectionDynamicState`  
`enum class EDataflowGeometryCollectionDynamicState : uint8`  
_L1278-1284_
- reflection: `UENUM(BlueprintType)`
- L1280 _public enumerator_ `None = 0 UMETA(DisplayName = "None")`
- L1281 _public enumerator_ `Dynamic = 1 UMETA(DisplayName = "Dynamic")`
- L1282 _public enumerator_ `Kinematic = 2 UMETA(DisplayName = "Kinematic")`
- L1283 _public enumerator_ `Static = 3 UMETA(DisplayName = "Static")`

#### struct `FSetDynamicStateDataflowNode`  
`struct FSetDynamicStateDataflowNode : public FDataflowNode`  
_L1292-1315_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Sets the dynamic state on the selected bones in a Collection
- L1300 _private member_ `EDataflowGeometryCollectionDynamicState DynamicState = EDataflowGeometryCollectionDynamicState::Kinematic;` — `UPROPERTY(EditAnywhere, Category = "State")` — Dynamic state to set on selected bones
- L1304 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection to set anchor state on
- L1308 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection", DataflowIntrinsic))` — Bone selection for setting the state on
- L1310 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1313 _public prototype_ `FSetDynamicStateDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### enum `EProximityMethodEnum`  
`enum class EProximityMethodEnum : uint8`  
_L1319-1328_
- reflection: `UENUM(BlueprintType)`
- L1322 _public enumerator_ `Dataflow_ProximityMethod_Precise UMETA(DisplayName = "Precise")` — Precise proximity mode looks for geometry with touching vertices or touching, coplanar, opposite - facing triangles.This works well with geometry fractured using our fracture tools.
- L1324 _public enumerator_ `Dataflow_ProximityMethod_ConvexHull UMETA(DisplayName = "ConvexHull")` — Convex Hull proximity mode looks for geometry with overlapping convex hulls(with an optional offset)
- L1327 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `EProximityContactFilteringMethodEnum`  
`enum class EProximityContactFilteringMethodEnum : uint8`  
_L1331-1342_
- reflection: `UENUM(BlueprintType)`
- L1334 _public enumerator_ `Dataflow_ProximityContactFilteringMethod_ProjectedBoundsOverlap UMETA(DisplayName = "Projected Bounds Overlap")` — Rejects proximity if the bounding boxes do not overlap by more than Contact Threshold centimeters in any major axis direction (or at least half the max possible). This can filter out corner connections of box-like shapes.
- L1336 _public enumerator_ `Dataflow_ProximityContactFilteringMethod_ConvexHullSharp UMETA(DisplayName = "Convex Hull Sharp Contact")` — Rejects proximity if the intersection of convex hulls (allowing for optional offset) follows a sharp, thin region which is not wider than Contact Threshold centimeters (or at least half the max possible).
- L1338 _public enumerator_ `Dataflow_ProximityContactFilteringMethod_ConvexHullArea UMETA(DisplayName = "Convex Hull Area Contact")` — Rejects proximity if the surface area of the intersection of convex hulls (allowing for optional offset) is smaller than Contact Threshold squared (or at least half the max possible).
- L1341 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `EConnectionContactAreaMethodEnum`  
`enum class EConnectionContactAreaMethodEnum : uint8`  
_L1345-1354_
- reflection: `UENUM(BlueprintType)`
- L1348 _public enumerator_ `Dataflow_ConnectionContactAreaMethod_None UMETA(DisplayName = "None")` — Do not compute contact areas
- L1350 _public enumerator_ `Dataflow_ProximityContactFilteringMethod_ConvexHullArea UMETA(DisplayName = "Convex Hull Area Contact")` — Compute approximate contact surface area via the intersection of convex hulls (allowing for optional offset)
- L1353 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FProximityDataflowNode`  
`struct FProximityDataflowNode : public FDataflowNode`  
_L1363-1414_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Icon = "FractureEditor.Proximity"))`
- inherits: `FDataflowNode`
- desc: Update the proximity (contact) graph for the bones in a Collection
- L1371 _private member_ `EProximityMethodEnum ProximityMethod = EProximityMethodEnum::Dataflow_ProximityMethod_Precise;` — `UPROPERTY(EditAnywhere, Category = "Proximity")` — Which method to use to decide whether a given piece of geometry is in proximity with another
- L1376 _private member_ `float DistanceThreshold = 1;` — `UPROPERTY(EditAnywhere, Category = "Proximity", meta = (DataflowInput, ClampMin = "0", Units = cm, EditCondition = "ProximityMethod == EProximityMethodEnum::Dataflow_ProximityMethod_ConvexHull || FilterContactMethod == EProximityContactFilteringMethodEnum::Dataflow_ProximityContactFilteringMethod_ConvexHullSharp || FilterContactMethod == EProximityContactFilteringMethodEnum::Dataflow_ProximityContactFilteringMethod_ConvexHullArea || ContactAreaMethod == EConnectionContactAreaMethodEnum::Dataflow_ProximityContactFilteringMethod_ConvexHullArea"))` — If hull-based proximity detection is enabled, amount to expand hulls when searching for overlapping neighbors
- L1380 _private member_ `float ContactThreshold = 0;` — `UPROPERTY(EditAnywhere, Category = "Proximity", meta = (DataflowInput, ClampMin = "0", Units = cm))` — If greater than zero, proximity will be additionally filtered by a 'contact' threshold, in cm, to exclude grazing / corner proximity
- L1384 _private member_ `EProximityContactFilteringMethodEnum FilterContactMethod = EProximityContactFilteringMethodEnum::Dataflow_ProximityContactFilteringMethod_ProjectedBoundsOverlap;` — `UPROPERTY(EditAnywhere, Category = "Proximity")` — How to use the Contact Threshold (if > 0) to filter out unwanted small or corner contacts from the proximity graph. If contact threshold is zero, no filtering is applied.
- L1388 _private member_ `bool bUseAsConnectionGraph = false;` — `UPROPERTY(EditAnywhere, Category = "Proximity")` — Whether to automatically transform the proximity graph into a connection graph to be used for simulation
- L1392 _private member_ `EConnectionContactAreaMethodEnum ContactAreaMethod = EConnectionContactAreaMethodEnum::Dataflow_ConnectionContactAreaMethod_None;` — `UPROPERTY(EditAnywhere, Category = "Proximity")` — The method used to compute contact areas for simulation purposes (only when 'Use As Connection Graph' is enabled)
- L1397 _private member_ `bool bRecomputeConvexHulls = true;` — `UPROPERTY(EditAnywhere, Category = "Proximity", meta = ( EditCondition = "ProximityMethod == EProximityMethodEnum::Dataflow_ProximityMethod_ConvexHull || FilterContactMethod == EProximityContactFilteringMethodEnum::Dataflow_ProximityContactFilteringMethod_ConvexHullSharp || FilterContactMethod == EProximityContactFilteringMethodEnum::Dataflow_ProximityContactFilteringMethod_ConvexHullArea || ContactAreaMethod == EConnectionContactAreaMethodEnum::Dataflow_ProximityContactFilteringMethod_ConvexHullArea"))` — Whether to compute new convex hulls for proximity, or use the pre-existing hulls on the Collection, when using convex hulls to determine proximity
- L1401 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection to update the proximity graph on
- L1403 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1406 _public function_ `FProximityDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`

#### struct `FCollectionSetPivotDataflowNode`  
`struct FCollectionSetPivotDataflowNode : public FDataflowNode`  
_L1423-1447_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Sets pivot for Collection
- L1431 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the pivot change
- L1435 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Pivot", meta = (DataflowInput))` — Pivot transform
- L1437 _public function_ `FCollectionSetPivotDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1445 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EStandardGroupNameEnum`  
`enum class EStandardGroupNameEnum : uint8`  
_L1451-1463_
- reflection: `UENUM(BlueprintType)`
- L1453 _public enumerator_ `Dataflow_EStandardGroupNameEnum_Transform UMETA(DisplayName = "Transform", ToolTip = "")`
- L1454 _public enumerator_ `Dataflow_EStandardGroupNameEnum_Geometry UMETA(DisplayName = "Geometry", ToolTip = "")`
- L1455 _public enumerator_ `Dataflow_EStandardGroupNameEnum_Faces UMETA(DisplayName = "Faces", ToolTip = "")`
- L1456 _public enumerator_ `Dataflow_EStandardGroupNameEnum_Vertices UMETA(DisplayName = "Vertices", ToolTip = "")`
- L1457 _public enumerator_ `Dataflow_EStandardGroupNameEnum_Material UMETA(DisplayName = "Material", ToolTip = "")`
- L1458 _public enumerator_ `Dataflow_EStandardGroupNameEnum_Breaking UMETA(DisplayName = "Breaking", ToolTip = "")`
- L1459 _public enumerator_ `Dataflow_EStandardGroupNameEnum_Custom UMETA(DisplayName = "Custom", ToolTip = "")`
- L1462 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `ECustomAttributeTypeEnum`  
`enum class ECustomAttributeTypeEnum : uint8`  
_L1466-1496_
- reflection: `UENUM(BlueprintType)`
- L1468 _public enumerator_ `Dataflow_CustomAttributeType_UInt8 UMETA(DisplayName = "UInt8", ToolTip = "Data type: UInt8")`
- L1469 _public enumerator_ `Dataflow_CustomAttributeType_Int32 UMETA(DisplayName = "Int32", ToolTip = "Data type: Int32")`
- L1470 _public enumerator_ `Dataflow_CustomAttributeType_Float UMETA(DisplayName = "Float", ToolTip = "Data type: Float")`
- L1471 _public enumerator_ `Dataflow_CustomAttributeType_Double UMETA(DisplayName = "Double", ToolTip = "Data type: Double")`
- L1472 _public enumerator_ `Dataflow_CustomAttributeType_Bool UMETA(DisplayName = "Bool", ToolTip = "Data type: Bool")`
- L1473 _public enumerator_ `Dataflow_CustomAttributeType_String UMETA(DisplayName = "String", ToolTip = "Data type: FString")`
- L1474 _public enumerator_ `Dataflow_CustomAttributeType_Vector2f UMETA(DisplayName = "Vector2D", ToolTip = "Data type: FVector2f")`
- L1475 _public enumerator_ `Dataflow_CustomAttributeType_Vector3f UMETA(DisplayName = "Vector", ToolTip = "Data type: FVector3f")`
- L1476 _public enumerator_ `Dataflow_CustomAttributeType_Vector3d UMETA(DisplayName = "Vector3d", ToolTip = "Data type: FVector3d")`
- L1477 _public enumerator_ `Dataflow_CustomAttributeType_Vector4f UMETA(DisplayName = "Vector4f", ToolTip = "Data type: FVector4f")`
- L1478 _public enumerator_ `Dataflow_CustomAttributeType_LinearColor UMETA(DisplayName = "LinearColor", ToolTip = "Data type: FLinearColor")`
- L1479 _public enumerator_ `Dataflow_CustomAttributeType_Transform UMETA(DisplayName = "Transform", ToolTip = "Data type: FTransform")`
- L1480 _public enumerator_ `Dataflow_CustomAttributeType_Quat4f UMETA(DisplayName = "Quat", ToolTip = "Data type: FQuat4f")`
- L1481 _public enumerator_ `Dataflow_CustomAttributeType_Box UMETA(DisplayName = "Box", ToolTip = "Data type: FBox")`
- L1482 _public enumerator_ `Dataflow_CustomAttributeType_Guid UMETA(DisplayName = "Guid", ToolTip = "Data type: FGuid")`
- L1483 _public enumerator_ `Dataflow_CustomAttributeType_Int32Set UMETA(DisplayName = "IntArray", ToolTip = "Data type: TSet<int32>")`
- L1484 _public enumerator_ `Dataflow_CustomAttributeType_Int32Array UMETA(DisplayName = "Int32Array", ToolTip = "Data type: TArray<int32>")`
- L1485 _public enumerator_ `Dataflow_CustomAttributeType_IntVector UMETA(DisplayName = "IntVector", ToolTip = "Data type: FIntVector")`
- L1486 _public enumerator_ `Dataflow_CustomAttributeType_IntVector2 UMETA(DisplayName = "IntVector2", ToolTip = "Data type: FIntVector2")`
- L1487 _public enumerator_ `Dataflow_CustomAttributeType_IntVector4 UMETA(DisplayName = "IntVector4", ToolTip = "Data type: FIntVector4")`
- L1488 _public enumerator_ `Dataflow_CustomAttributeType_IntVector2Array UMETA(DisplayName = "IntVector2Array", ToolTip = "Data type: TArray<FIntVector2>")`
- L1489 _public enumerator_ `Dataflow_CustomAttributeType_FloatArray UMETA(DisplayName = "FloatArray", ToolTip = "Data type: TArray<float>")`
- L1490 _public enumerator_ `Dataflow_CustomAttributeType_Vector2fArray UMETA(DisplayName = "Vector2DArray", ToolTip = "Data type: TArray<FVector2f>")`
- L1491 _public enumerator_ `Dataflow_CustomAttributeType_FVector3fArray UMETA(DisplayName = "FVectorArray", ToolTip = "Data type: TArray<FVector3f>")`
- L1495 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FAddCustomCollectionAttributeDataflowNode`  
`struct FAddCustomCollectionAttributeDataflowNode : public FDataflowNode`  
_L1504-1544_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Adds custom attribute to Collection
- L1512 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the custom attribute
- L1516 _public member_ `EStandardGroupNameEnum GroupName = EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Transform;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Group"))` — Standard group names
- L1520 _public member_ `FString CustomGroupName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Custom Group", EditCondition = "GroupName == EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Custom"))` — User specified group name
- L1524 _public member_ `FString AttrName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Attribute"))` — Attribute name
- L1528 _public member_ `ECustomAttributeTypeEnum CustomAttributeType = ECustomAttributeTypeEnum::Dataflow_CustomAttributeType_Float;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Attribute Type"))` — Attribute type
- L1532 _public member_ `int32 NumElements = 0;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Number of Elements"))` — Number of elements for the attribute
- L1534 _public function_ `FAddCustomCollectionAttributeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1542 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetNumElementsInCollectionGroupDataflowNode`  
`struct FGetNumElementsInCollectionGroupDataflowNode : public FDataflowNode`  
_L1553-1584_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Returns number of elements in a group in a Collection
- L1561 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Collection for the custom attribute
- L1565 _public member_ `EStandardGroupNameEnum GroupName = EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Transform;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Group"))` — Standard group names
- L1569 _public member_ `FString CustomGroupName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Custom Group", EditCondition = "GroupName == EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Custom"))` — User specified group name
- L1573 _public member_ `int32 NumElements = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of elements for the attribute
- L1575 _public function_ `FGetNumElementsInCollectionGroupDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1582 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetCollectionAttributeDataTypedDataflowNode`  
`struct FGetCollectionAttributeDataTypedDataflowNode : public FDataflowNode`  
_L1592-1667_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get attribute data from a Collection
- L1600 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Collection for the custom attribute
- L1604 _public member_ `FCollectionAttributeKey AttributeKey;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "AttributeKey"))` — Input to drive the Attribute and Group name
- L1608 _public member_ `EStandardGroupNameEnum GroupName = EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Transform;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Group"))` — Standard group names
- L1612 _public member_ `FString CustomGroupName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Custom Group", EditCondition = "GroupName == EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Custom"))` — User specified group name
- L1616 _public member_ `FString AttrName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Attribute"))` — Attribute name
- L1620 _public member_ `TArray<bool> BoolAttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Bool Array"))` — Bool type attribute data
- L1624 _public member_ `TArray<float> FloatAttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Float Array"))` — Float type attribute data
- L1628 _public member_ `TArray<double> DoubleAttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Double Array"))` — Float type attribute data
- L1632 _public member_ `TArray<int32> Int32AttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Int32 Array"))` — Int type attribute data
- L1636 _public member_ `TArray<FString> StringAttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "String Array"))` — Int type attribute data
- L1640 _public member_ `TArray<FVector3f> Vector3fAttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Vector3f Array"))` — Vector3f type attribute data
- L1644 _public member_ `TArray<FVector3d> Vector3dAttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Vector3d Array"))` — Vector3d type attribute data
- L1648 _public member_ `TArray<FLinearColor> LinearColorAttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Linear Color Array"))` — Vector3d type attribute data
- L1650 _public function_ `FGetCollectionAttributeDataTypedDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1665 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetCollectionAttributeDataTypedDataflowNode_v2`  
`struct FGetCollectionAttributeDataTypedDataflowNode_v2 : public FDataflowNode`  
_L1675-1731_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get attribute data from a Collection
- L1683 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the custom attribute
- L1687 _private member_ `FCollectionAttributeKey AttributeKey;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "AttributeKey"))` — Input to drive the Attribute and Group name
- L1691 _private member_ `EStandardGroupNameEnum GroupName = EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Transform;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Group"))` — Standard group names
- L1695 _private member_ `FString CustomGroupName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Custom Group", EditCondition = "GroupName == EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Custom"))` — User specified group name
- L1699 _private member_ `FString AttrName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Attribute"))` — Attribute name
- L1703 _private member_ `TArray<bool> BoolAttributeData;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Bool Array"))` — Bool type attribute data
- L1707 _private member_ `FDataflowNumericArrayTypes NumericArray;` — `UPROPERTY(meta = (DataflowOutput))` — Numeric Array types
- L1711 _private member_ `FDataflowVectorArrayTypes VectorArray;` — `UPROPERTY(meta = (DataflowOutput))` — Vector Array types
- L1715 _private member_ `FDataflowStringArrayTypes StringArray;` — `UPROPERTY(meta = (DataflowOutput))` — String Array types
- L1718 _public function_ `FGetCollectionAttributeDataTypedDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1730 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSetCollectionAttributeDataTypedDataflowNode`  
`struct FSetCollectionAttributeDataTypedDataflowNode : public FDataflowNode`  
_L1739-1815_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Set attribute data in a Collection
- L1747 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the custom attribute
- L1751 _public member_ `FCollectionAttributeKey AttributeKey;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "AttributeKey"))` — Input to drive the Attribute and Group name
- L1755 _public member_ `EStandardGroupNameEnum GroupName = EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Transform;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Group"))` — Standard group names
- L1759 _public member_ `FString CustomGroupName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Custom Group", EditCondition = "GroupName == EStandardGroupNameEnum::Dataflow_EStandardGroupNameEnum_Custom"))` — User specified group name
- L1763 _public member_ `FString AttrName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Attribute"))` — Attribute name
- L1767 _public member_ `TArray<bool> BoolAttributeData;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Bool Array"))` — Bool type attribute data
- L1771 _public member_ `TArray<float> FloatAttributeData;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Float Array"))` — Float type attribute data
- L1775 _public member_ `TArray<double> DoubleAttributeData;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Double Array"))` — Float type attribute data
- L1779 _public member_ `TArray<int32> Int32AttributeData;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Int32 Array"))` — Int type attribute data
- L1783 _public member_ `TArray<FString> StringAttributeData;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "String Array"))` — Int type attribute data
- L1787 _public member_ `TArray<FVector3f> Vector3fAttributeData;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Vector3f Array"))` — Vector3f type attribute data
- L1791 _public member_ `TArray<FVector3d> Vector3dAttributeData;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Vector3d Array"))` — Vector3d type attribute data
- L1795 _public member_ `TArray<FLinearColor> LinearColorAttributeData;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Linear Color Array"))` — LinearColor type attribute data
- L1797 _public function_ `FSetCollectionAttributeDataTypedDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1813 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSelectionToVertexListDataflowNode`  
`struct FSelectionToVertexListDataflowNode : public FDataflowNode`  
_L1823-1848_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L1832 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "VertexSelection", DataflowIntrinsic))`
- L1836 _public member_ `TArray<int32> VertexList;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VertexList"))`
- L1839 _public function_ `FSelectionToVertexListDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1846 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FMultiplyTransformDataflowNode`  
`struct FMultiplyTransformDataflowNode : public FDataflowNode`  
_L1856-1881_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Description for this node
- L1863 _public member_ `FTransform InLeftTransform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Left Transform"))`
- L1866 _public member_ `FTransform InRightTransform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Right Transform"))`
- L1869 _public member_ `FTransform OutTransform = FTransform::Identity;` — `UPROPERTY(meta = ( DataflowOutput, DisplayName = "Out Transform"))`
- L1871 _public function_ `FMultiplyTransformDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1879 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FInvertTransformDataflowNode`  
`struct FInvertTransformDataflowNode : public FDataflowNode`  
_L1889-1909_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Invert a transform.
- L1896 _public member_ `FTransform InTransform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "InTransform"))`
- L1899 _public member_ `FTransform OutTransform = FTransform::Identity;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "OutTransform"))`
- L1901 _public function_ `FInvertTransformDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1908 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBranchFloatDataflowNode`  
`struct FBranchFloatDataflowNode : public FDataflowNode`  
_L1917-1950_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Branch between two float inputs based on boolean condition
- L1925 _public member_ `float A = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Branch", meta = (DataflowInput))` — Float input
- L1929 _public member_ `float B = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Branch", meta = (DataflowInput))` — Float input
- L1933 _public member_ `bool bCondition = false;` — `UPROPERTY(EditAnywhere, Category = "Branch")` — If true, Output = A, otherwise Output = B
- L1937 _public member_ `float ReturnValue = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Output
- L1939 _public function_ `FBranchFloatDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1948 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FBranchIntDataflowNode`  
`struct FBranchIntDataflowNode : public FDataflowNode`  
_L1958-1991_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Branch between two int inputs based on boolean condition
- L1966 _public member_ `int32 A = 0;` — `UPROPERTY(EditAnywhere, Category = "Branch", meta = (DataflowInput))` — Int input
- L1970 _public member_ `int32 B = 0;` — `UPROPERTY(EditAnywhere, Category = "Branch", meta = (DataflowInput))` — Int input
- L1974 _public member_ `bool bCondition = false;` — `UPROPERTY(EditAnywhere, Category = "Branch")` — If true, Output = A, otherwise Output = B
- L1978 _public member_ `int32 ReturnValue = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Output
- L1980 _public function_ `FBranchIntDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1989 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FVisualizeTetrahedronsDataflowNode`  
`struct FVisualizeTetrahedronsDataflowNode : public FDataflowNode`  
_L2012-2039_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Visualize tetrahedrons in a collection
- L2023 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the custom attribute
- L2026 _private member_ `TArray<FVector> Vertices;` — `UPROPERTY(meta = (DataflowOutput))`
- L2029 _public function_ `FVisualizeTetrahedronsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L2037 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FPointsToCollectionDataflowNode`  
`struct FPointsToCollectionDataflowNode : public FDataflowNode`  
_L2047-2071_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Add point cloud to a collection as vertices
- L2055 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to add the points to
- L2059 _private member_ `TArray<FVector> Points;` — `UPROPERTY(EditAnywhere, Category = "Points", meta = (DataflowInput))` — Points to add to the collection
- L2062 _public function_ `FPointsToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L2070 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionToPointsDataflowNode`  
`struct FCollectionToPointsDataflowNode : public FDataflowNode`  
_L2079-2103_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get vertices from a collection as a point cloud
- L2087 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection storing the points
- L2091 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Points from the collection
- L2094 _public function_ `FCollectionToPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L2102 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSpheresToPointsDataflowNode`  
`struct FSpheresToPointsDataflowNode : public FDataflowNode`  
_L2111-2139_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Outputs Spheres as Points and radius values
- L2119 _private member_ `TArray<FSphere> Spheres;` — `UPROPERTY(meta = (DataflowInputDataflowIntrinsic))` — Input Spheres
- L2123 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Centers of the spheres
- L2127 _private member_ `TArray<float> Radii;` — `UPROPERTY(meta = (DataflowOutput))` — Radius values
- L2130 _public function_ `FSpheresToPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L2138 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionInfoDataflowNode`  
`struct FCollectionInfoDataflowNode : public FDataflowNode`  
_L2147-2171_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Outputs Collection info
- L2155 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection storing the points
- L2159 _private member_ `int32 MaxLevel = 0;` — `UPROPERTY(meta = (DataflowOutput))` — MaxLevel
- L2162 _public function_ `FCollectionInfoDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L2170 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FTransformMeshDataflowNode_v2`  
`struct FTransformMeshDataflowNode_v2 : public FDataflowNode`  
_L2179-2229_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Transforms a Dataflow mesh
- L2187 _private member_ `TObjectPtr<UDataflowMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Mesh", DataflowIntrinsic))` — Output mesh
- L2191 _private member_ `FVector Translate = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, GizmoType = Translate))` — Translation
- L2195 _private member_ `ERotationOrderEnum RotationOrder = ERotationOrderEnum::Dataflow_RotationOrder_XYZ;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Rotation Order
- L2199 _private member_ `FVector Rotate = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (DataflowInput, GizmoType = Rotate, GizmoPosition = Translate))` — Rotation
- L2203 _private member_ `FVector Scale = FVector(1.0);` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (UIMin = 0.001f, DataflowInput, GizmoType = Scale, GizmoPosition = Translate))` — Scale
- L2211 _private member_ `float UniformScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Transform", meta = (UIMin = 0.001f, DataflowInput))` — Uniform scale
- L2215 _private member_ `FVector RotatePivot = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Pivot", meta = (DataflowInput))` — Pivot for the rotation
- L2219 _private member_ `FVector ScalePivot = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Pivot", meta = (DataflowInput))` — Pivot for the scale
- L2223 _private member_ `bool bInvertTransformation = false;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (DataflowInput))` — Invert the transformation
- L2225 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L2228 _public prototype_ `FTransformMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Dataflow`
- L2231 _namespace_ `namespace UE`
- L2231 _namespace_ `namespace Dataflow` (scope `UE`)
- L2233 _prototype_ `void GeometryCollectionEngineNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionNodesPlugin.h` (Public)


#### class `IGeometryCollectionNodesPlugin`  
`class IGeometryCollectionNodesPlugin : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionOverrideNodes.h` (Public)


#### struct `FGetFloatOverrideFromAssetDataflowNode`  
`struct FGetFloatOverrideFromAssetDataflowNode : public FDataflowOverrideNode`  
_L19-39_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, DataflowOverride))`
- inherits: `FDataflowOverrideNode`
- L26 _public member_ `float Float = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L29 _public member_ `float FloatDefault = 0.f;` — `UPROPERTY(meta = (DataflowOutput))`
- L31 _public function_ `FGetFloatOverrideFromAssetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowOverrideNode(InParam, InGuid)`
- L38 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetIntOverrideFromAssetDataflowNode`  
`struct FGetIntOverrideFromAssetDataflowNode : public FDataflowOverrideNode`  
_L47-67_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, DataflowOverride))`
- inherits: `FDataflowOverrideNode`
- L54 _public member_ `int32 Int = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L57 _public member_ `int32 IntDefault = 0;` — `UPROPERTY(meta = (DataflowOutput))`
- L59 _public function_ `FGetIntOverrideFromAssetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowOverrideNode(InParam, InGuid)`
- L66 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetBoolOverrideFromAssetDataflowNode`  
`struct FGetBoolOverrideFromAssetDataflowNode : public FDataflowOverrideNode`  
_L75-95_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, DataflowOverride))`
- inherits: `FDataflowOverrideNode`
- L82 _public member_ `bool Bool = false;` — `UPROPERTY(meta = (DataflowOutput))`
- L85 _public member_ `bool BoolDefault = false;` — `UPROPERTY(meta = (DataflowOutput))`
- L87 _public function_ `FGetBoolOverrideFromAssetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowOverrideNode(InParam, InGuid)`
- L94 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetStringOverrideFromAssetDataflowNode`  
`struct FGetStringOverrideFromAssetDataflowNode : public FDataflowOverrideNode`  
_L103-123_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, DataflowOverride))`
- inherits: `FDataflowOverrideNode`
- L110 _public member_ `FString String;` — `UPROPERTY(meta = (DataflowOutput))`
- L113 _public member_ `FString StringDefault;` — `UPROPERTY(meta = (DataflowOutput))`
- L115 _public function_ `FGetStringOverrideFromAssetDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowOverrideNode(InParam, InGuid)`
- L122 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`
- L125 _namespace_ `namespace UE`
- L125 _namespace_ `namespace Dataflow` (scope `UE`)
- L127 _prototype_ `void GeometryCollectionOverrideNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionProcessingNodes.h` (Public)


#### struct `FCloseGeometryOnCollectionDataflowNode`  
`struct FCloseGeometryOnCollectionDataflowNode : public FDataflowNode`  
_L14-33_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L20 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))`
- L25 _public function_ `FCloseGeometryOnCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L32 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace Dataflow` (scope `UE`)
- L37 _prototype_ `void GeometryCollectionProcessingNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionSamplingNodes.h` (Public)


#### enum `EFilterPointSetWithMeshDataflowMethodFlags`  
`enum class EFilterPointSetWithMeshDataflowMethodFlags : uint8`  
_L23-32_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Flags to control which mesh point filtering method(s) are applied
- L25 _public enumerator_ `None = 0 UMETA(Hidden)`
- L27 _public enumerator_ `Winding = 1 << 0` — Use the winding number to filter inside or outside of the mesh
- L29 _public enumerator_ `MinDistance = 1 << 1` — Filter away points below a minimum mesh distance
- L31 _public enumerator_ `MaxDistance = 1 << 2` — Filter away points above a maximum mesh distance

#### struct `FFilterPointSetWithMeshDataflowNode`  
`struct FFilterPointSetWithMeshDataflowNode : public FDataflowNode`  
_L40-85_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Filter a point set to only the points inside or outside of a given mesh DEPRECATED 5.8 - use FFilterPointSetWithMeshDataflowNode_v2 instead
- L46 _public prototype_ `FFilterPointSetWithMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L51 _private member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to use to filter point set
- L54 _private member_ `uint8 FilterMethod = (uint8)EFilterPointSetWithMeshDataflowMethodFlags::Winding;` — `UPROPERTY(EditAnywhere, Category=Options, meta=(Bitmask, BitmaskEnum="/Script/GeometryCollectionNodes.EFilterPointSetWithMeshDataflowMethodFlags"))`
- L58 _private member_ `bool bKeepInside = true;` — `UPROPERTY(EditAnywhere, Category = WindingNumber, meta = (DataflowInput, EditCondition = "FilterMethod & \"/Script/GeometryCollectionNodes.EFilterPointSetWithMeshDataflowMethodFlags::Winding\""))` — Whether to keep the points inside or (if false) outside the mesh, when filtering by Winding Number.
- L62 _private member_ `float WindingThreshold = .5f;` — `UPROPERTY(EditAnywhere, Category = WindingNumber, meta = (DataflowInput))` — The winding number threshold to use for determining whether a point is inside or outside of the mesh, if corresponding Filter Method is set
- L66 _private member_ `float MinDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput, EditCondition = "FilterMethod & \"/Script/GeometryCollectionNodes.EFilterPointSetWithMeshDataflowMethodFlags::MinDistance\""))` — The min distance to surface to keep, if corresponding Filter Method is set
- L70 _private member_ `float MaxDistance = 1000.f;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput, EditCondition = "FilterMethod & \"/Script/GeometryCollectionNodes.EFilterPointSetWithMeshDataflowMethodFlags::MaxDistance\""))` — The max distance to surface to keep, if corresponding Filter Method is set
- L77 _private member_ `bool bUseSignedDistance = false;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput))` — Whether to use signed distances for the Min and Max Distance thresholds. Otherwise, unsigned distance is used. Note: Signs are computed via the Winding Number. The sign is negative if the point's Winding Number is below the Winding Threshold.
- L81 _private member_ `TArray<FVector> SamplePoints;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput))` — Points to filter
- L84 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FFilterPointSetWithMeshDataflowNode_v2`  
`struct FFilterPointSetWithMeshDataflowNode_v2 : public FDataflowNode`  
_L91-135_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Filter a point set to only the points inside or outside of a given Dataflow mesh
- L97 _public prototype_ `FFilterPointSetWithMeshDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L102 _private member_ `TObjectPtr<UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Dataflow mesh to use to filter point set
- L105 _private member_ `uint8 FilterMethod = (uint8)EFilterPointSetWithMeshDataflowMethodFlags::Winding;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (Bitmask, BitmaskEnum = "/Script/GeometryCollectionNodes.EFilterPointSetWithMeshDataflowMethodFlags"))`
- L109 _private member_ `bool bKeepInside = true;` — `UPROPERTY(EditAnywhere, Category = WindingNumber, meta = (DataflowInput, EditCondition = "FilterMethod & \"/Script/GeometryCollectionNodes.EFilterPointSetWithMeshDataflowMethodFlags::Winding\""))` — Whether to keep the points inside or (if false) outside the mesh, when filtering by Winding Number.
- L113 _private member_ `float WindingThreshold = .5f;` — `UPROPERTY(EditAnywhere, Category = WindingNumber, meta = (DataflowInput))` — The winding number threshold to use for determining whether a point is inside or outside of the mesh, if corresponding Filter Method is set
- L117 _private member_ `float MinDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput, EditCondition = "FilterMethod & \"/Script/GeometryCollectionNodes.EFilterPointSetWithMeshDataflowMethodFlags::MinDistance\""))` — The min distance to surface to keep, if corresponding Filter Method is set
- L121 _private member_ `float MaxDistance = 1000.f;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput, EditCondition = "FilterMethod & \"/Script/GeometryCollectionNodes.EFilterPointSetWithMeshDataflowMethodFlags::MaxDistance\""))` — The max distance to surface to keep, if corresponding Filter Method is set
- L128 _private member_ `bool bUseSignedDistance = false;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput))` — Whether to use signed distances for the Min and Max Distance thresholds. Otherwise, unsigned distance is used. Note: Signs are computed via the Winding Number. The sign is negative if the point's Winding Number is below the Winding Threshold.
- L132 _private member_ `FDataflowPoints SamplePoints;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput))` — Points to filter
- L134 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FUniformPointSamplingDataflowNode`  
`struct FUniformPointSamplingDataflowNode : public FDataflowNode`  
_L142-199_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Uniform Sampling on a DynamicMesh DEPRECATED 5.8 - use FUniformPointSamplingDataflowNode_v2 instead
- L150 _public member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to sample points on
- L154 _public member_ `float SamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Desired "radius" of sample points. Spacing between samples is at least 2x this value.
- L158 _public member_ `int32 MaxNumSamples = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0))` — Maximum number of samples requested. If 0 or default value, mesh will be maximally sampled
- L162 _public member_ `float SubSampleDensity = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Density of subsampling used in Poisson strategy. Larger numbers mean "more accurate" (but slower) results.
- L166 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Random Seed used to initialize sampling strategies
- L170 _public member_ `TArray<FVector> SamplePoints;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled positions on the mesh
- L174 _public member_ `TArray<int32> SampleTriangleIDs;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled triangleID
- L178 _public member_ `TArray<FVector> SampleBarycentricCoords;` — `UPROPERTY(meta = (DataflowOutput))` — Barycentric Coordinates of each Sample Point in it's respective Triangle.
- L182 _public member_ `int32 NumSamplePoints = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of Sampled positions on the mesh
- L184 _public function_ `FUniformPointSamplingDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L198 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FUniformPointSamplingDataflowNode_v2`  
`struct FUniformPointSamplingDataflowNode_v2 : public FDataflowNode`  
_L207-253_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Uniform Sampling on a Dataflow Mesh
- L215 _private member_ `TObjectPtr<UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to sample points on
- L219 _private member_ `float SamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Desired "radius" of sample points. Spacing between samples is at least 2x this value.
- L223 _private member_ `int32 MaxNumSamples = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0))` — Maximum number of samples requested. If 0 or default value, mesh will be maximally sampled
- L227 _private member_ `float SubSampleDensity = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Density of subsampling used in Poisson strategy. Larger numbers mean "more accurate" (but slower) results.
- L231 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Random Seed used to initialize sampling strategies
- L235 _private member_ `FDataflowPoints SamplePoints;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled positions on the mesh
- L239 _private member_ `TArray<int32> SampleTriangleIDs;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled triangleID
- L243 _private member_ `TArray<FVector> SampleBarycentricCoords;` — `UPROPERTY(meta = (DataflowOutput))` — Barycentric Coordinates of each Sample Point in it's respective Triangle.
- L247 _private member_ `int32 NumSamplePoints = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of Sampled positions on the mesh
- L249 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L252 _public prototype_ `FUniformPointSamplingDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FNonUniformPointSamplingDataflowNode`  
`struct FNonUniformPointSamplingDataflowNode : public FDataflowNode`  
_L260-336_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: NonUniform Sampling on a DynamicMesh DEPRECATED 5.8 - use FNonUniformPointSamplingDataflowNode_v2 instead
- L268 _public member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to sample points on
- L272 _public member_ `float SamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Desired "radius" of sample points. Spacing between samples is at least 2x this value.
- L276 _public member_ `int32 MaxNumSamples = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0))` — Maximum number of samples requested. If 0 or default value, mesh will be maximally sampled
- L280 _public member_ `float SubSampleDensity = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Density of subsampling used in Poisson strategy. Larger numbers mean "more accurate" (but slower) results.
- L284 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Random Seed used to initialize sampling strategies
- L288 _public member_ `float MaxSamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — If MaxSampleRadius > SampleRadius, then output sample radius will be in range [SampleRadius, MaxSampleRadius]
- L292 _public member_ `ENonUniformSamplingDistributionMode SizeDistribution = ENonUniformSamplingDistributionMode::ENonUniformSamplingDistributionMode_Uniform;` — `UPROPERTY(EditAnywhere, Category = Distribution)` — SizeDistribution setting controls the distribution of sample radii
- L296 _public member_ `float SizeDistributionPower = 2.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — SizeDistributionPower is used to control how extreme the Size Distribution shift is. Valid range is [1,10]
- L300 _public member_ `TArray<FVector> SamplePoints;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled positions on the mesh
- L304 _public member_ `TArray<float> SampleRadii;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled radii
- L308 _public member_ `TArray<int32> SampleTriangleIDs;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled triangleID
- L312 _public member_ `TArray<FVector> SampleBarycentricCoords;` — `UPROPERTY(meta = (DataflowOutput))` — Barycentric Coordinates of each Sample Point in it's respective Triangle.
- L316 _public member_ `int32 NumSamplePoints = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of Sampled positions on the mesh
- L318 _public function_ `FNonUniformPointSamplingDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L335 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FNonUniformPointSamplingDataflowNode_v2`  
`struct FNonUniformPointSamplingDataflowNode_v2 : public FDataflowNode`  
_L344-406_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: NonUniform Sampling on a Dataflow Mesh
- L352 _private member_ `TObjectPtr<UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to sample points on
- L356 _private member_ `float SamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Desired "radius" of sample points. Spacing between samples is at least 2x this value.
- L360 _private member_ `int32 MaxNumSamples = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0))` — Maximum number of samples requested. If 0 or default value, mesh will be maximally sampled
- L364 _private member_ `float SubSampleDensity = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Density of subsampling used in Poisson strategy. Larger numbers mean "more accurate" (but slower) results.
- L368 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Random Seed used to initialize sampling strategies
- L372 _private member_ `float MaxSamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — If MaxSampleRadius > SampleRadius, then output sample radius will be in range [SampleRadius, MaxSampleRadius]
- L376 _private member_ `ENonUniformSamplingDistributionMode SizeDistribution = ENonUniformSamplingDistributionMode::ENonUniformSamplingDistributionMode_Uniform;` — `UPROPERTY(EditAnywhere, Category = Distribution)` — SizeDistribution setting controls the distribution of sample radii
- L380 _private member_ `float SizeDistributionPower = 2.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — SizeDistributionPower is used to control how extreme the Size Distribution shift is. Valid range is [1,10]
- L384 _private member_ `FDataflowPoints SamplePoints;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled positions on the mesh
- L388 _private member_ `TArray<float> SampleRadii;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled radii
- L392 _private member_ `TArray<int32> SampleTriangleIDs;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled triangleID
- L396 _private member_ `TArray<FVector> SampleBarycentricCoords;` — `UPROPERTY(meta = (DataflowOutput))` — Barycentric Coordinates of each Sample Point in it's respective Triangle.
- L400 _private member_ `int32 NumSamplePoints = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of Sampled positions on the mesh
- L402 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L405 _public prototype_ `FNonUniformPointSamplingDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVertexWeightedPointSamplingDataflowNode`  
`struct FVertexWeightedPointSamplingDataflowNode : public FDataflowNode`  
_L413-500_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: VertexWeighted Sampling on a DynamicMesh DEPRECATED 5.8 - use FVertexWeightedPointSamplingDataflowNode_v2 instead
- L421 _public member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to sample points on
- L425 _public member_ `TArray<float> VertexWeights;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Weight array
- L429 _public member_ `float SamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Desired "radius" of sample points. Spacing between samples is at least 2x this value.
- L433 _public member_ `int32 MaxNumSamples = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0))` — Maximum number of samples requested. If 0 or default value, mesh will be maximally sampled
- L437 _public member_ `float SubSampleDensity = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Density of subsampling used in Poisson strategy. Larger numbers mean "more accurate" (but slower) results.
- L441 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Random Seed used to initialize sampling strategies
- L445 _public member_ `float MaxSamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — If MaxSampleRadius > SampleRadius, then output sample radius will be in range [SampleRadius, MaxSampleRadius]
- L449 _public member_ `ENonUniformSamplingDistributionMode SizeDistribution = ENonUniformSamplingDistributionMode::ENonUniformSamplingDistributionMode_Uniform;` — `UPROPERTY(EditAnywhere, Category = Distribution)` — SizeDistribution setting controls the distribution of sample radii
- L453 _public member_ `float SizeDistributionPower = 2.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — SizeDistributionPower is used to control how extreme the Size Distribution shift is. Valid range is [1,10]
- L456 _public member_ `ENonUniformSamplingWeightMode WeightMode = ENonUniformSamplingWeightMode::ENonUniformSamplingWeightMode_WeightedRandom;` — `UPROPERTY(EditAnywhere, Category = Distribution)`
- L459 _public member_ `bool bInvertWeights = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L463 _public member_ `TArray<FVector> SamplePoints;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled positions on the mesh
- L467 _public member_ `TArray<float> SampleRadii;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled radii
- L471 _public member_ `TArray<int32> SampleTriangleIDs;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled triangleID
- L475 _public member_ `TArray<FVector> SampleBarycentricCoords;` — `UPROPERTY(meta = (DataflowOutput))` — Barycentric Coordinates of each Sample Point in it's respective Triangle.
- L479 _public member_ `int32 NumSamplePoints = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of Sampled positions on the mesh
- L481 _public function_ `FVertexWeightedPointSamplingDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L499 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FVertexWeightedPointSamplingDataflowNode_v2`  
`struct FVertexWeightedPointSamplingDataflowNode_v2 : public FDataflowNode`  
_L508-580_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: VertexWeighted Sampling on a DynamicMesh If VertexWeights input is not connected it uses max weight for every vertex
- L516 _private member_ `TObjectPtr<UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Dataflow mesh to sample points on
- L520 _private member_ `TArray<float> VertexWeights;` — `UPROPERTY(meta = (DataflowInput))` — Weight array, number of elements in the array has to match number of vertices of the TargetMesh
- L524 _private member_ `float SamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Desired "radius" of sample points. Spacing between samples is at least 2x this value.
- L528 _private member_ `int32 MaxNumSamples = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0))` — Maximum number of samples requested. If 0 or default value, mesh will be maximally sampled
- L532 _private member_ `float SubSampleDensity = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — Density of subsampling used in Poisson strategy. Larger numbers mean "more accurate" (but slower) results.
- L536 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Random Seed used to initialize sampling strategies
- L540 _private member_ `float MaxSamplingRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — If MaxSampleRadius > SampleRadius, then output sample radius will be in range [SampleRadius, MaxSampleRadius]
- L544 _private member_ `ENonUniformSamplingDistributionMode SizeDistribution = ENonUniformSamplingDistributionMode::ENonUniformSamplingDistributionMode_Uniform;` — `UPROPERTY(EditAnywhere, Category = Distribution)` — SizeDistribution setting controls the distribution of sample radii
- L548 _private member_ `float SizeDistributionPower = 2.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = 0.f))` — SizeDistributionPower is used to control how extreme the Size Distribution shift is. Valid range is [1,10]
- L551 _private member_ `ENonUniformSamplingWeightMode WeightMode = ENonUniformSamplingWeightMode::ENonUniformSamplingWeightMode_WeightedRandom;` — `UPROPERTY(EditAnywhere, Category = Distribution)`
- L554 _private member_ `bool bInvertWeights = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L558 _private member_ `FDataflowPoints SamplePoints;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled positions on the mesh
- L562 _private member_ `TArray<float> SampleRadii;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled radii
- L566 _private member_ `TArray<int32> SampleTriangleIDs;` — `UPROPERTY(meta = (DataflowOutput))` — Sampled triangleID
- L570 _private member_ `TArray<FVector> SampleBarycentricCoords;` — `UPROPERTY(meta = (DataflowOutput))` — Barycentric Coordinates of each Sample Point in it's respective Triangle.
- L574 _private member_ `int32 NumSamplePoints = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of Sampled positions on the mesh
- L576 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L579 _public prototype_ `FVertexWeightedPointSamplingDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMeshMedialSkeletonSamplingDataflowNode`  
`struct FMeshMedialSkeletonSamplingDataflowNode : public FDataflowNode`  
_L587-631_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Sample the medial skeleton of a target mesh DEPRECATED 5.8 - use FMeshMedialSkeletonSamplingDataflowNode_v2 instead
- L595 _private member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to sample skeleton on
- L598 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowOutput))`
- L601 _private member_ `TArray<FSphere> MedialSpheres;` — `UPROPERTY(meta = (DataflowOutput, DataflowRenderGroups = "None"))`
- L605 _private member_ `int32 MaxSpheres = 1000;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1))` — Stop at this sphere count
- L609 _private member_ `float MinClusterErrorToSplit = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = .1, ClampMin = 0.))` — Do not split a cluster if its max error is below this threshold
- L613 _private member_ `int32 MinClusterSizeToKeep = 4;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1, UIMax = 10))` — Clusters with fewer vertices than this will be discarded
- L617 _private member_ `bool bSplitClustersIfEdgesIntersectSurface = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Whether to test medial skeleton edges for intersection w/ the input surface, and try to refine where these intersections are found
- L621 _private member_ `float ErrorScaleNearEdgeSurfaceIntersection = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput, ClampMin = 1, UIMax = 100))` — Factor to scale vertex error near skeleton-edge/input-surface intersections
- L625 _private member_ `float PosErrorWt = .2f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DisplayName = "Position Error Weight", DataflowInput, UIMin = .1, ClampMin = .001, ClampMax = 1))` — Weight for the position error term. Relative to plane error term, so normal and position error weights sum to 1. Should be in the (0,1] range.
- L627 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L630 _public prototype_ `FMeshMedialSkeletonSamplingDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMeshMedialSkeletonSamplingDataflowNode_v2`  
`struct FMeshMedialSkeletonSamplingDataflowNode_v2 : public FDataflowNode`  
_L639-683_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Sample the medial skeleton of a target Dataflow mesh
- L647 _private member_ `TObjectPtr<UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Dataflow mesh to sample skeleton on
- L650 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowOutput))`
- L653 _private member_ `TArray<FSphere> MedialSpheres;` — `UPROPERTY(meta = (DataflowOutput, DataflowRenderGroups = "None"))`
- L657 _private member_ `int32 MaxSpheres = 1000;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1))` — Stop at this sphere count
- L661 _private member_ `float MinClusterErrorToSplit = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, UIMin = .1, ClampMin = 0.))` — Do not split a cluster if its max error is below this threshold
- L665 _private member_ `int32 MinClusterSizeToKeep = 4;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1, UIMax = 10))` — Clusters with fewer vertices than this will be discarded
- L669 _private member_ `bool bSplitClustersIfEdgesIntersectSurface = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Whether to test medial skeleton edges for intersection w/ the input surface, and try to refine where these intersections are found
- L673 _private member_ `float ErrorScaleNearEdgeSurfaceIntersection = 10.f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput, ClampMin = 1, UIMax = 100))` — Factor to scale vertex error near skeleton-edge/input-surface intersections
- L677 _private member_ `float PosErrorWt = .2f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DisplayName = "Position Error Weight", DataflowInput, UIMin = .1, ClampMin = .001, ClampMax = 1))` — Weight for the position error term. Relative to plane error term, so normal and position error weights sum to 1. Should be in the (0,1] range.
- L679 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L682 _public prototype_ `FMeshMedialSkeletonSamplingDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSimplifyMedialSkeletonDataflowNode`  
`struct FSimplifyMedialSkeletonDataflowNode : public FDataflowNode`  
_L691-763_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Simplify a medial skeleton using the quadric error metric DEPRECATED 5.8 - use FSimplifyMedialSkeletonDataflowNode_v2 instead
- L699 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic))` — Medial skeleton to simplify
- L703 _private member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh the skeleton was sampled from, used to compute the error metric
- L706 _private member_ `TArray<FSphere> MedialSpheres;` — `UPROPERTY(meta = (DataflowOutput, DataflowRenderGroups = "None"))`
- L710 _private member_ `int32 MinSpheres = 1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1))` — Stop simplifying at this sphere count
- L715 _private member_ `float QEMErrorThresholdSqrt = 0.;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput, ClampMin = 0, DisplayName="Quadric Error Threshold (Sqrt)"))` — If positive, will not collapse edges if it would introduce more quadric error than the square of this threshold. (Note: Not a distance error threshold.)
- L719 _private member_ `float EdgeLengthThreshold = 0.;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, Units = "cm"))` — If positive, the maximum edge length to consider for collapse
- L723 _private member_ `float SphereRadiusThreshold = 0.;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, Units = "cm"))` — If positive, the maximum sphere radius to consider for collapse.  If either cluster's medial sphere on an edge has smaller radii, it is allowed to collapse.
- L728 _private member_ `float SphereOverlapThreshold = 0.;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, ClampMax = 1))` — If positive, the minimum medial sphere overlap fraction to consider for collapse -- so e.g. at 1.0 we will only collapse an edge if its smaller medial sphere is contained in the larger. (A degenerate zero-radius sphere is considered to fully overlap any sphere it touches.)
- L732 _private member_ `bool bOnlySimplifySurfaces = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — If true, only simplify edges of skeleton surfaces (edges that have triangles associated)
- L737 _private member_ `float ClusterSkeletonDistanceWt = .5f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, ClampMax = 1, UIMax = .9999))` — How much the simplifier should attempt to remain close to the initial skeleton, vs keeping medial spheres close to the mesh surface. In the [0,1] range. At 0 the original skeleton is not considered; at 1 the mesh surface is not considered.
- L741 _private member_ `bool bPreventEdgeSurfaceIntersections = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — If true, prevent collapses that would introduce intersections between skeleton edges and the mesh
- L745 _private member_ `float ClusterRegularizeWeight = 1e-6f;`
- L749 _private member_ `bool bSplitThinTriEdges = true;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput))` — Whether to split edges attached to skinny triangles before simplifying, which can add useful degrees of freedom to the simplifier
- L753 _private member_ `float SplitThinTriEdgeAngleThresholdDeg = 120.f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition="bSplitThinTriEdges", DataflowInput, ClampMin = 90, ClampMax = 180))` — Minimum angle (degrees) at the opposite vertex for an edge to be a split candidate
- L757 _private member_ `float SplitThinTriEdgePosErrorWt = .2f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition="bSplitThinTriEdges", DataflowInput, ClampMin = 0, ClampMax = 1))` — Position error weight used when re-clustering vertices after thin-triangle edge splits
- L759 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L762 _public prototype_ `FSimplifyMedialSkeletonDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSimplifyMedialSkeletonDataflowNode_v2`  
`struct FSimplifyMedialSkeletonDataflowNode_v2 : public FDataflowNode`  
_L769-841_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Simplify a medial skeleton using the quadric error metric
- L777 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic))` — Medial skeleton to simplify
- L781 _private member_ `TObjectPtr<UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh the skeleton was sampled from, used to compute the error metric
- L784 _private member_ `TArray<FSphere> MedialSpheres;` — `UPROPERTY(meta = (DataflowOutput, DataflowRenderGroups = "None"))`
- L788 _private member_ `int32 MinSpheres = 1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1))` — Stop simplifying at this sphere count
- L793 _private member_ `float QEMErrorThresholdSqrt = 0.;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput, ClampMin = 0, DisplayName = "Quadric Error Threshold (Sqrt)"))` — If positive, will not collapse edges if it would introduce more quadric error than the square of this threshold. (Note: Not a distance error threshold.)
- L797 _private member_ `float EdgeLengthThreshold = 0.;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, Units = "cm"))` — If positive, the maximum edge length to consider for collapse
- L801 _private member_ `float SphereRadiusThreshold = 0.;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, Units = "cm"))` — If positive, the maximum sphere radius to consider for collapse.  If either cluster's medial sphere on an edge has smaller radii, it is allowed to collapse.
- L806 _private member_ `float SphereOverlapThreshold = 0.;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, ClampMax = 1))` — If positive, the minimum medial sphere overlap fraction to consider for collapse -- so e.g. at 1.0 we will only collapse an edge if its smaller medial sphere is contained in the larger. (A degenerate zero-radius sphere is considered to fully overlap any sphere it touches.)
- L810 _private member_ `bool bOnlySimplifySurfaces = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — If true, only simplify edges of skeleton surfaces (edges that have triangles associated)
- L815 _private member_ `float ClusterSkeletonDistanceWt = .5f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, ClampMax = 1, UIMax = .9999))` — How much the simplifier should attempt to remain close to the initial skeleton, vs keeping medial spheres close to the mesh surface. In the [0,1] range. At 0 the original skeleton is not considered; at 1 the mesh surface is not considered.
- L819 _private member_ `bool bPreventEdgeSurfaceIntersections = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — If true, prevent collapses that would introduce intersections between skeleton edges and the mesh
- L823 _private member_ `float ClusterRegularizeWeight = 1e-6f;`
- L827 _private member_ `bool bSplitThinTriEdges = true;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput))` — Whether to split edges attached to skinny triangles before simplifying, which can add useful degrees of freedom to the simplifier
- L831 _private member_ `float SplitThinTriEdgeAngleThresholdDeg = 120.f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "bSplitThinTriEdges", DataflowInput, ClampMin = 90, ClampMax = 180))` — Minimum angle (degrees) at the opposite vertex for an edge to be a split candidate
- L835 _private member_ `float SplitThinTriEdgePosErrorWt = .2f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "bSplitThinTriEdges", DataflowInput, ClampMin = 0, ClampMax = 1))` — Position error weight used when re-clustering vertices after thin-triangle edge splits
- L837 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L840 _public prototype_ `FSimplifyMedialSkeletonDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### enum `ESubdivideEdgeRadiusReference`  
`enum class ESubdivideEdgeRadiusReference : uint8`  
_L845-853_
- reflection: `UENUM()`
- desc: Which sphere radius to use when computing radius-based target edge lengths
- L848 _public enumerator_ `Larger` — Use the larger of the two sphere radii on the edge
- L850 _public enumerator_ `Smaller` — Use the smaller of the two sphere radii on the edge
- L852 _public enumerator_ `Average` — Use the average of the two sphere radii on the edge

#### struct `FSubdivideMedialSkeletonDataflowNode`  
`struct FSubdivideMedialSkeletonDataflowNode : public FDataflowNode`  
_L860-909_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Subdivide a medial skeleton by splitting edges that exceed a target length DEPRECATED 5.8 - use FSubdivideMedialSkeletonDataflowNode_v2 instead
- L868 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic))` — Medial skeleton to subdivide
- L872 _private member_ `TObjectPtr<UDynamicMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh the skeleton was sampled from, used to re-cluster vertices after subdivision
- L875 _private member_ `TArray<FSphere> MedialSpheres;` — `UPROPERTY(meta = (DataflowOutput, DataflowRenderGroups = "None"))`
- L879 _private member_ `float TargetEdgeLengthRadiusFraction = 0.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0))` — If positive, target edge length as a fraction of a medial sphere radius on the edge (see Radius Reference)
- L883 _private member_ `ESubdivideEdgeRadiusReference RadiusReference = ESubdivideEdgeRadiusReference::Average;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, EditCondition = "TargetEdgeLengthRadiusFraction > 0"))` — Which sphere radius to reference when computing radius-based target edge lengths
- L887 _private member_ `float MinTargetEdgeLength = 0.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, Units = "cm"))` — If positive, minimum target edge length
- L891 _private member_ `float MaxTargetEdgeLength = 0.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, Units = "cm"))` — If positive, maximum target edge length. Also used as the target directly when Radius Fraction and Min are both 0
- L895 _private member_ `bool bSubdivideOnSurfaces = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — If true, also subdivide edges that have associated triangles (splitting those triangles)
- L899 _private member_ `float ReassignClusterPosErrorWt = .2f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput, ClampMin = 0, ClampMax = 1))` — Position error weight for re-clustering vertices after edge splits
- L903 _private member_ `bool bProjectNewMedialSpheres = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — If true, project newly-added spheres to the medial axis. Otherwise, new spheres will linearly interpolate their source edge spheres.
- L905 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L908 _public prototype_ `FSubdivideMedialSkeletonDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSubdivideMedialSkeletonDataflowNode_v2`  
`struct FSubdivideMedialSkeletonDataflowNode_v2 : public FDataflowNode`  
_L917-966_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Subdivide a medial skeleton by splitting edges that exceed a target length
- L925 _private member_ `FDataflowMedialSkeleton MedialSkeleton;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic))` — Medial skeleton to subdivide
- L929 _private member_ `TObjectPtr<UDataflowMesh> TargetMesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh the skeleton was sampled from, used to re-cluster vertices after subdivision
- L932 _private member_ `TArray<FSphere> MedialSpheres;` — `UPROPERTY(meta = (DataflowOutput, DataflowRenderGroups = "None"))`
- L936 _private member_ `float TargetEdgeLengthRadiusFraction = 0.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0))` — If positive, target edge length as a fraction of a medial sphere radius on the edge (see Radius Reference)
- L940 _private member_ `ESubdivideEdgeRadiusReference RadiusReference = ESubdivideEdgeRadiusReference::Average;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, EditCondition = "TargetEdgeLengthRadiusFraction > 0"))` — Which sphere radius to reference when computing radius-based target edge lengths
- L944 _private member_ `float MinTargetEdgeLength = 0.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, Units = "cm"))` — If positive, minimum target edge length
- L948 _private member_ `float MaxTargetEdgeLength = 0.f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, Units = "cm"))` — If positive, maximum target edge length. Also used as the target directly when Radius Fraction and Min are both 0
- L952 _private member_ `bool bSubdivideOnSurfaces = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — If true, also subdivide edges that have associated triangles (splitting those triangles)
- L956 _private member_ `float ReassignClusterPosErrorWt = .2f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput, ClampMin = 0, ClampMax = 1))` — Position error weight for re-clustering vertices after edge splits
- L960 _private member_ `bool bProjectNewMedialSpheres = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — If true, project newly-added spheres to the medial axis. Otherwise, new spheres will linearly interpolate their source edge spheres.
- L962 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L965 _public prototype_ `FSubdivideMedialSkeletonDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Dataflow`
- L968 _namespace_ `namespace UE`
- L968 _namespace_ `namespace Dataflow` (scope `UE`)
- L970 _prototype_ `void GeometryCollectionSamplingNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionSelectionNodes.h` (Public)


#### struct `FCollectionTransformSelectionAllDataflowNode`  
`struct FCollectionTransformSelectionAllDataflowNode : public FDataflowNode`  
_L29-53_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects all the bones for the Collection DEPRECATED 5.8 - use FCollectionSelectionAllDataflowNode instead
- L37 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L41 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L43 _public function_ `FCollectionTransformSelectionAllDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L51 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ESetOperationEnum`  
`enum class ESetOperationEnum : uint8`  
_L57-70_
- reflection: `UENUM(BlueprintType)`
- L60 _public enumerator_ `Dataflow_SetOperation_AND UMETA(DisplayName = "Intersect")` — Select elements that are selected in both incoming selections (Bitwise AND)
- L62 _public enumerator_ `Dataflow_SetOperation_OR UMETA(DisplayName = "Union")` — Select elements that are selected in either incoming selections (Bitwise OR)
- L64 _public enumerator_ `Dataflow_SetOperation_XOR UMETA(DisplayName = "Symmetric Difference (XOR)")` — Select elements that are selected in exactly one incoming selection (Bitwise XOR)
- L66 _public enumerator_ `Dataflow_SetOperation_Subtract UMETA(DisplayName = "Difference")` — Select elements that are selected in only the first of the incoming selections (Bitwise A AND (NOT B))
- L69 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FCollectionTransformSelectionSetOperationDataflowNode`  
`struct FCollectionTransformSelectionSetOperationDataflowNode : public FDataflowNode`  
_L79-111_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- L87 _public member_ `ESetOperationEnum Operation = ESetOperationEnum::Dataflow_SetOperation_AND;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Boolean operation
- L91 _public member_ `FDataflowTransformSelection TransformSelectionA;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelectionA", DataflowIntrinsic))` — Array of the selected bone indices
- L95 _public member_ `FDataflowTransformSelection TransformSelectionB;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelectionB", DataflowIntrinsic))` — Array of the selected bone indices
- L99 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection", DataflowPassthrough = "TransformSelectionA"))` — Array of the selected bone indices after operation
- L101 _public function_ `FCollectionTransformSelectionSetOperationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L109 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionInfoDataflowNode`  
`struct FCollectionTransformSelectionInfoDataflowNode : public FDataflowNode`  
_L119-147_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Generates a formatted string of the bones and the selection
- L127 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L131 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))` — GeometryCollection for the selection
- L135 _public member_ `FString String;` — `UPROPERTY(meta = (DataflowOutput))` — Formatted string of the bones and selection
- L137 _public function_ `FCollectionTransformSelectionInfoDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L145 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionNoneDataflowNode`  
`struct FCollectionTransformSelectionNoneDataflowNode : public FDataflowNode`  
_L156-180_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Generates an empty bone selection for the Collection DEPRECATED 5.8 - use FCollectionSelectionNoneDataflowNode instead
- L164 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L168 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L170 _public function_ `FCollectionTransformSelectionNoneDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L178 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionInvertDataflowNode`  
`struct FCollectionTransformSelectionInvertDataflowNode : public FDataflowNode`  
_L189-208_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Inverts selection of bones
- L197 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "TransformSelection", DataflowPassthrough = "TransformSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L199 _public function_ `FCollectionTransformSelectionInvertDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L206 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionRandomDataflowNode`  
`struct FCollectionTransformSelectionRandomDataflowNode : public FDataflowNode`  
_L217-256_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects bones randomly in the Collection DEPRECATED 5.8 - use FCollectionSelectionRandomDataflowNode instead
- L225 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Random")` — If true, it always generates the same result for the same RandomSeed
- L229 _public member_ `float RandomSeed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, EditCondition = "bDeterministic"))` — Seed for the random generation, only used if Deterministic is on
- L233 _public member_ `float RandomThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, UIMin = 0.f, UIMax = 1.f))` — Bones get selected if RandomValue < RandomThreshold
- L237 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L241 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L243 _public function_ `FCollectionTransformSelectionRandomDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L254 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionRootDataflowNode`  
`struct FCollectionTransformSelectionRootDataflowNode : public FDataflowNode`  
_L265-289_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects the root bones in the Collection
- L273 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L277 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L279 _public function_ `FCollectionTransformSelectionRootDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L287 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionCustomDataflowNode`  
`struct FCollectionTransformSelectionCustomDataflowNode : public FDataflowNode`  
_L299-328_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Selects specified bones in the GeometryCollection by using a space separated list, e.g. "0 1 2 12 23" DEPRECATED 5.6 - use FCollectionTransformSelectionCustomDataflowNode_v2 instead
- L307 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L311 _public member_ `FString BoneIndicies = FString();` — `UPROPERTY(EditAnywhere, Category = "Selection", meta=(DisplayName="Bone Indices"))` — Space separated list of bone indices to specify the selection, e.g. "0 1 2 3 23 34"
- L315 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L317 _public function_ `FCollectionTransformSelectionCustomDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L326 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionCustomDataflowNode_v2`  
`struct FCollectionTransformSelectionCustomDataflowNode_v2 : public FDataflowNode`  
_L337-358_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects specified bones in the GeometryCollection by using a comma separated list, e.g. "0, 2, 5-10, 12-15" DEPRECATED 5.8 - use FCollectionSelectionCustomDataflowNode instead
- L345 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L349 _public member_ `FString BoneIndices;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DisplayName = "Bone Indices"))` — Comma separated list of single or a range of bone indices to specify the selection, e.g. "0, 2, 5-10, 12-15"
- L353 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L355 _public prototype_ `FCollectionTransformSelectionCustomDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L357 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionFromIndexArrayDataflowNode`  
`struct FCollectionTransformSelectionFromIndexArrayDataflowNode : public FDataflowNode`  
_L366-396_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Convert index array to a transform selection
- L375 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to use for the selection. Note only valid bone indices for the collection will be included in the output selection.
- L379 _public member_ `TArray<int32> BoneIndices;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput))` — Array of bone indices to convert to a trannsform selection
- L383 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L385 _public function_ `FCollectionTransformSelectionFromIndexArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L394 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionParentDataflowNode`  
`struct FCollectionTransformSelectionParentDataflowNode : public FDataflowNode`  
_L405-430_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects the parents of the currently selected bones
- L413 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "TransformSelection", DataflowPassthrough = "TransformSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L417 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L419 _public function_ `FCollectionTransformSelectionParentDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L428 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionByPercentageDataflowNode`  
`struct FCollectionTransformSelectionByPercentageDataflowNode : public FDataflowNode`  
_L439-473_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Outputs the specified percentage of the selected bones DEPRECATED 5.8 - use FCollectionSelectionByPercentageDataflowNode instead
- L447 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "TransformSelection", DataflowPassthrough = "TransformSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L451 _public member_ `int32 Percentage = 100;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (UIMin = 0, UIMax = 100))` — Percentage to keep from the original selection
- L455 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Random")` — Sets the random generation to deterministic
- L459 _public member_ `float RandomSeed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, EditCondition = "bDeterministic"))` — Seed value for the random generation
- L461 _public function_ `FCollectionTransformSelectionByPercentageDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L471 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionChildrenDataflowNode`  
`struct FCollectionTransformSelectionChildrenDataflowNode : public FDataflowNode`  
_L482-507_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects the children of the selected bones
- L490 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "TransformSelection", DataflowPassthrough = "TransformSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L494 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L496 _public function_ `FCollectionTransformSelectionChildrenDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L505 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionSiblingsDataflowNode`  
`struct FCollectionTransformSelectionSiblingsDataflowNode : public FDataflowNode`  
_L516-541_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects the siblings of the selected bones
- L524 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "TransformSelection", DataflowPassthrough = "TransformSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L528 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L530 _public function_ `FCollectionTransformSelectionSiblingsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L539 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionLevelDataflowNode`  
`struct FCollectionTransformSelectionLevelDataflowNode : public FDataflowNode`  
_L550-575_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Expand the selection to include all nodes with the same level as the selected nodes
- L558 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "TransformSelection", DataflowPassthrough = "TransformSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L562 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L564 _public function_ `FCollectionTransformSelectionLevelDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L573 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionTargetLevelDataflowNode`  
`struct FCollectionTransformSelectionTargetLevelDataflowNode : public FDataflowNode`  
_L584-617_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects the root bones in the Collection
- L592 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L596 _public member_ `int32 TargetLevel = 1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0))` — Level to select
- L600 _public member_ `bool bSkipEmbedded = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to avoid embedded geometry in the selection (i.e., only select rigid and cluster nodes)
- L604 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L606 _public function_ `FCollectionTransformSelectionTargetLevelDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L615 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionContactDataflowNode`  
`struct FCollectionTransformSelectionContactDataflowNode : public FDataflowNode`  
_L627-656_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects the contact(s) of the selected bones
- L635 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "TransformSelection", DataflowPassthrough = "TransformSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L639 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L643 _public member_ `bool bAllowContactInParentLevels = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to allow contact with bones that are in a parent level
- L645 _public function_ `FCollectionTransformSelectionContactDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L654 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionLeafDataflowNode`  
`struct FCollectionTransformSelectionLeafDataflowNode : public FDataflowNode`  
_L665-689_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects the leaves in the Collection
- L673 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L677 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L679 _public function_ `FCollectionTransformSelectionLeafDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L687 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionClusterDataflowNode`  
`struct FCollectionTransformSelectionClusterDataflowNode : public FDataflowNode`  
_L700-724_
- reflection: `USTRUCT(meta = (Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- desc: Selects the clusters in the Collection Deprecated : this node had the wrong behavior and select the leaves instead Replace it by CollectionTransformSelectLeaf or use the second version of CollectionTransformSelectCluster
- L708 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L712 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L714 _public function_ `FCollectionTransformSelectionClusterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L722 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionClusterDataflowNode_v2`  
`struct FCollectionTransformSelectionClusterDataflowNode_v2 : public FDataflowNode`  
_L733-757_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Selects the clusters in the Collection this version works properly and address the issues found in the deprecated version 1
- L741 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L745 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L747 _public function_ `FCollectionTransformSelectionClusterDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L755 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ERangeSettingEnum`  
`enum class ERangeSettingEnum : uint8`  
_L761-770_
- reflection: `UENUM(BlueprintType)`
- L764 _public enumerator_ `Dataflow_RangeSetting_InsideRange UMETA(DisplayName = "Inside Range")` — Values for selection must be inside of the specified range
- L766 _public enumerator_ `Dataflow_RangeSetting_OutsideRange UMETA(DisplayName = "Outside Range")` — Values for selection must be outside of the specified range
- L769 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FSelectFloatArrayIndicesInRangeDataflowNode`  
`struct FSelectFloatArrayIndicesInRangeDataflowNode : public FDataflowNode`  
_L779-820_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects indices of a float array by range
- L787 _public member_ `TArray<float> Values;` — `UPROPERTY(meta = (DataflowInput))` — GeometryCollection for the selection
- L791 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (UIMin = 0.f, UIMax = 1000000000.f))` — Minimum value for the selection
- L795 _public member_ `float Max = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (UIMin = 0.f, UIMax = 1000000000.f))` — Maximum value for the selection
- L799 _public member_ `ERangeSettingEnum RangeSetting = ERangeSettingEnum::Dataflow_RangeSetting_InsideRange;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — Values for the selection has to be inside or outside [Min, Max] range
- L803 _public member_ `bool bInclusive = true;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — If true then range includes Min and Max values
- L807 _public member_ `TArray<int> Indices;` — `UPROPERTY(meta = (DataflowOutput))` — Indices of float Values matching the specified range
- L809 _public function_ `FSelectFloatArrayIndicesInRangeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L818 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionBySizeDataflowNode`  
`struct FCollectionTransformSelectionBySizeDataflowNode : public FDataflowNode`  
_L829-875_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects pieces based on their size
- L837 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L841 _public member_ `float SizeMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Size", meta = (UIMin = 0.f, UIMax = 1000000000.f))` — Minimum size for the selection
- L845 _public member_ `float SizeMax = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "Size", meta = (UIMin = 0.f, UIMax = 1000000000.f))` — Maximum size for the selection
- L849 _public member_ `ERangeSettingEnum RangeSetting = ERangeSettingEnum::Dataflow_RangeSetting_InsideRange;` — `UPROPERTY(EditAnywhere, Category = "Size")` — Values for the selection has to be inside or outside [Min, Max] range
- L853 _public member_ `bool bInclusive = true;` — `UPROPERTY(EditAnywhere, Category = "Size")` — If true then range includes Min and Max values
- L857 _public member_ `bool bUseRelativeSize = true;` — `UPROPERTY(EditAnywhere, Category = "Size")` — Whether to use the 'Relative Size' -- i.e., the Size / Largest Bone Size. Otherwise, Size is the cube root of Volume.
- L861 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L863 _public function_ `FCollectionTransformSelectionBySizeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L873 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionByVolumeDataflowNode`  
`struct FCollectionTransformSelectionByVolumeDataflowNode : public FDataflowNode`  
_L884-926_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects pieces based on their volume
- L892 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L896 _public member_ `float VolumeMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (UIMin = 0.f, UIMax = 1000000000.f))` — Minimum volume for the selection
- L900 _public member_ `float VolumeMax = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (UIMin = 0.f, UIMax = 1000000000.f))` — Maximum volume for the selection
- L904 _public member_ `ERangeSettingEnum RangeSetting = ERangeSettingEnum::Dataflow_RangeSetting_InsideRange;` — `UPROPERTY(EditAnywhere, Category = "Volume")` — Values for the selection has to be inside or outside [Min, Max] range
- L908 _public member_ `bool bInclusive = true;` — `UPROPERTY(EditAnywhere, Category = "Volume")` — If true then range includes Min and Max values
- L912 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L914 _public function_ `FCollectionTransformSelectionByVolumeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L924 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ESelectSubjectTypeEnum`  
`enum class ESelectSubjectTypeEnum : uint8`  
_L930-941_
- reflection: `UENUM(BlueprintType)`
- L933 _public enumerator_ `Dataflow_SelectSubjectType_Vertices UMETA(DisplayName = "Vertices")` — InBox must contain the vertices of the bone
- L935 _public enumerator_ `Dataflow_SelectSubjectType_BoundingBox UMETA(DisplayName = "BoundingBox")` — InBox must contain the BoundingBox of the bone
- L937 _public enumerator_ `Dataflow_SelectSubjectType_Centroid UMETA(DisplayName = "Centroid")` — InBox must contain the centroid of the bone
- L940 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FCollectionTransformSelectionInBoxDataflowNode`  
`struct FCollectionTransformSelectionInBoxDataflowNode : public FDataflowNode`  
_L949-995_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects bones if their Vertices/BoundingBox/Centroid in a box DEPRECATED 5.8 - use FCollectionSelectionByPrimitiveDataflowNode instead
- L957 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L961 _public member_ `FBox Box = FBox(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Box to contain Vertices/BoundingBox/Centroid
- L965 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Select")` — Transform for the box
- L969 _public member_ `ESelectSubjectTypeEnum Type = ESelectSubjectTypeEnum::Dataflow_SelectSubjectType_Centroid;` — `UPROPERTY(EditAnywhere, Category = "Select", DisplayName = "Type to Check in Box")` — Subject (Vertices/BoundingBox/Centroid) to check against box
- L973 _public member_ `bool bAllVerticesMustContainedInBox = true;` — `UPROPERTY(EditAnywhere, Category = "Select", meta = (EditCondition = "Type == ESelectSubjectTypeEnum::Dataflow_SelectSubjectType_Vertices"))` — If true all the vertices of the piece must be inside of box
- L977 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L979 _public function_ `FCollectionTransformSelectionInBoxDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L989 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L992 _public prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L993 _public prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FCollectionTransformSelectionInSphereDataflowNode`  
`struct FCollectionTransformSelectionInSphereDataflowNode : public FDataflowNode`  
_L1003-1049_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects bones if their Vertices/BoundingBox/Centroid in a sphere DEPRECATED 5.8 - use FCollectionSelectionByPrimitiveDataflowNode instead
- L1011 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1015 _public member_ `FSphere Sphere = FSphere(ForceInit);` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Sphere to contain Vertices/BoundingBox/Centroid
- L1019 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Select")` — Transform for the sphere
- L1023 _public member_ `ESelectSubjectTypeEnum Type = ESelectSubjectTypeEnum::Dataflow_SelectSubjectType_Centroid;` — `UPROPERTY(EditAnywhere, Category = "Select", DisplayName = "Type to Check in Sphere")` — Subject (Vertices/BoundingBox/Centroid) to check against box
- L1027 _public member_ `bool bAllVerticesMustContainedInSphere = true;` — `UPROPERTY(EditAnywhere, Category = "Select", meta = (EditCondition = "Type == ESelectSubjectTypeEnum::Dataflow_SelectSubjectType_Vertices"))` — If true all the vertices of the piece must be inside of box
- L1031 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L1033 _public function_ `FCollectionTransformSelectionInSphereDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1043 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1046 _public prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L1047 _public prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FCollectionVertexSelectionByBoxDataflowNode`  
`struct FCollectionVertexSelectionByBoxDataflowNode : public FDataflowNode`  
_L1058-1089_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects vertices they are contained in a transformed box DEPRECATED 5.8 - use FCollectionSelectionByPrimitiveDataflowNode instead
- L1064 _public prototype_ `FCollectionVertexSelectionByBoxDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1069 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1073 _private member_ `FBox Box = FBox(FVector(-50), FVector(+50));` — `UPROPERTY(EditAnywhere, Category = "Select", meta = (DataflowInput))` — Box to contain Vertices
- L1077 _private member_ `FTransform BoxTransform;` — `UPROPERTY(EditAnywhere, Category = "Select", meta = (DataflowInput))` — Transform for the box
- L1081 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowOutput))` — selected vertices
- L1083 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1086 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L1087 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FCollectionVertexSelectionBySphereDataflowNode`  
`struct FCollectionVertexSelectionBySphereDataflowNode : public FDataflowNode`  
_L1098-1125_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects vertices they are contained in a sphere DEPRECATED 5.8 - use FCollectionSelectionByPrimitiveDataflowNode instead
- L1104 _public prototype_ `FCollectionVertexSelectionBySphereDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1109 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1113 _private member_ `FSphere Sphere = FSphere(FVector(0, 0, 0), 50.0);` — `UPROPERTY(EditAnywhere, Category = "Select", meta = (DataflowInput))` — sphere to select vertices
- L1117 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowOutput))` — selected vertices
- L1119 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1122 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L1123 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FCollectionVertexSelectionByPlaneDataflowNode`  
`struct FCollectionVertexSelectionByPlaneDataflowNode : public FDataflowNode`  
_L1133-1173_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects vertices they are contained on a place side DEPRECATED 5.8 - use FCollectionSelectionByPrimitiveDataflowNode instead
- L1139 _public prototype_ `FCollectionVertexSelectionByPlaneDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1144 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1148 _private member_ `FTransform PlaneTransform = FTransform(FRotator(0, 90, 0));` — `UPROPERTY(EditAnywhere, Category = "Select", meta = (DataflowInput))` — plane to select vertices
- L1152 _private member_ `bool bPositiveSide = true;` — `UPROPERTY(EditAnywhere, Category = "Select")` — true to use the positive side of the plane
- L1156 _private member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowOutput))` — selected vertices
- L1160 _private member_ `float PlaneSize = 200;` — `UPROPERTY(EditAnywhere, Category = "DebugDraw", meta=(Units=cm, ClampMin = "0.001", UIMin = "0.001"))` — Size of the debug draw plane in cm
- L1164 _private member_ `int32 PlaneResolution = 20;` — `UPROPERTY(EditAnywhere, Category = "DebugDraw", meta = (ClampMin = "2", UIMin = "2"))` — number of vertices along an edge of the debug draw plane
- L1167 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1170 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L1171 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FCollectionTransformSelectionByFloatAttrDataflowNode`  
`struct FCollectionTransformSelectionByFloatAttrDataflowNode : public FDataflowNode`  
_L1181-1231_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects bones by a float attribute DEPRECATED 5.8 - use FCollectionSelectionByAttributeDataflowNode instead
- L1189 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1193 _public member_ `FString GroupName = FString("Tra` — `UPROPERTY(VisibleAnywhere, Category = "Attribute", meta = (DisplayName = "Group"))` — Group name for the attr
- L1197 _public member_ `FString AttrName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Attribute"))` — Attribute name
- L1201 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (UIMin = 0.f, UIMax = 1000000000.f))` — Minimum value for the selection
- L1205 _public member_ `float Max = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (UIMin = 0.f, UIMax = 1000000000.f))` — Maximum value for the selection
- L1209 _public member_ `ERangeSettingEnum RangeSetting = ERangeSettingEnum::Dataflow_RangeSetting_InsideRange;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — Values for the selection has to be inside or outside [Min, Max] range
- L1213 _public member_ `bool bInclusive = true;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — If true then range includes Min and Max values
- L1217 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Array of the selected bone indices
- L1219 _public function_ `FCollectionTransformSelectionByFloatAttrDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1229 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionTransformSelectionByIntAttrDataflowNode`  
`struct FCollectionTransformSelectionByIntAttrDataflowNode : public FDataflowNode`  
_L1240-1290_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects bones by an int attribute DEPRECATED 5.8 - use FCollectionSelectionByPrimitiveDataflowNode instead
- L1248 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1252 _public member_ `FString GroupName = FString("Tra` — `UPROPERTY(VisibleAnywhere, Category = "Attribute", meta = (DisplayName = "Group"))` — Group name for the attr
- L1256 _public member_ `FString AttrName = FString("");` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Attribute"))` — Attribute name
- L1260 _public member_ `int32 Min = 0;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (UIMin = 0, UIMax = 1000000000))` — Minimum value for the selection
- L1264 _public member_ `int32 Max = 1000;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (UIMin = 0, UIMax = 1000000000))` — Maximum value for the selection
- L1268 _public member_ `ERangeSettingEnum RangeSetting = ERangeSettingEnum::Dataflow_RangeSetting_InsideRange;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — Values for the selection has to be inside or outside [Min, Max] range
- L1272 _public member_ `bool bInclusive = true;` — `UPROPERTY(EditAnywhere, Category = "Attribute")` — If true then range includes Min and Max values
- L1276 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Transform selection including the new indices
- L1278 _public function_ `FCollectionTransformSelectionByIntAttrDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1288 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionVertexSelectionCustomDataflowNode`  
`struct FCollectionVertexSelectionCustomDataflowNode : public FDataflowNode`  
_L1300-1329_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects specified vertices in the GeometryCollection by using a space separated list DEPRECATED 5.8 - use FCollectionSelectionCustomDataflowNode instead
- L1308 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1312 _public member_ `FString VertexIndicies = FString();` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Space separated list of vertex indices to specify the selection
- L1316 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VertexSelection"))` — Vertex selection including the new indices
- L1318 _public function_ `FCollectionVertexSelectionCustomDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1327 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionFaceSelectionCustomDataflowNode`  
`struct FCollectionFaceSelectionCustomDataflowNode : public FDataflowNode`  
_L1339-1368_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects specified faces in the GeometryCollection by using a space separated list DEPRECATED 5.8 - use FCollectionSelectionCustomDataflowNode instead
- L1347 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1351 _public member_ `FString FaceIndicies = FString();` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Space separated list of face indices to specify the selection
- L1355 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FaceSelection"))` — Face selection including the new indices
- L1357 _public function_ `FCollectionFaceSelectionCustomDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1366 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionConvertDataflowNode`  
`struct FCollectionSelectionConvertDataflowNode : public FDataflowNode`  
_L1377-1418_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Converts Vertex/Face/Transform selection into Vertex/Face/Transform selection DEPRECATED 5.8 - use FCollectionSelectionConvertDataflowNode_v2 instead
- L1385 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1389 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "TransformSelection", DisplayName = "TransformSelection"))` — Transform selection including the new indices
- L1393 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "FaceSelection", DisplayName = "FaceSelection"))` — Face selection including the new indices
- L1397 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "VertexSelection", DisplayName = "VertexSelection"))` — Vertex selection including the new indices
- L1401 _public member_ `bool bAllElementsMustBeSelected = false;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — If true then for converting vertex/face selection to transform selection all vertex/face must be selected for selecting the associated transform
- L1403 _public function_ `FCollectionSelectionConvertDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1416 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionFaceSelectionInvertDataflowNode`  
`struct FCollectionFaceSelectionInvertDataflowNode : public FDataflowNode`  
_L1427-1446_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Inverts selection of faces
- L1435 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "FaceSelection", DataflowPassthrough = "FaceSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L1437 _public function_ `FCollectionFaceSelectionInvertDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1444 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionVertexSelectionByPercentageDataflowNode`  
`struct FCollectionVertexSelectionByPercentageDataflowNode : public FDataflowNode`  
_L1455-1489_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Outputs the specified percentage of the selected vertices DEPRECATED 5.8 - use FCollectionSelectionByPercentageDataflowNode instead
- L1463 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "VertexSelection", DataflowPassthrough = "VertexSelection", DataflowIntrinsic))` — Array of the selected bone indices
- L1467 _public member_ `int32 Percentage = 100;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (UIMin = 0, UIMax = 100))` — Percentage to keep from the original selection
- L1471 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Random")` — Sets the random generation to deterministic
- L1475 _public member_ `float RandomSeed = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, EditCondition = "bDeterministic"))` — Seed value for the random generation
- L1477 _public function_ `FCollectionVertexSelectionByPercentageDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1487 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionVertexSelectionSetOperationDataflowNode`  
`struct FCollectionVertexSelectionSetOperationDataflowNode : public FDataflowNode`  
_L1498-1530_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Runs boolean operation on VertexSelections Deprecated (5.6) : use the generic CollectionSelectionSetOperation node instead
- L1506 _public member_ `ESetOperationEnum Operation = ESetOperationEnum::Dataflow_SetOperation_AND;` — `UPROPERTY(EditAnywhere, Category = "Compare")` — Boolean operation
- L1510 _public member_ `FDataflowVertexSelection VertexSelectionA;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "VertexSelectionA", DataflowIntrinsic))` — Array of the selected vertex indices
- L1514 _public member_ `FDataflowVertexSelection VertexSelectionB;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "VertexSelectionB", DataflowIntrinsic))` — Array of the selected vertex indices
- L1518 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VertexSelection", DataflowPassthrough = "VertexSelectionA"))` — Array of the selected vertex indices after operation
- L1520 _public function_ `FCollectionVertexSelectionSetOperationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1528 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ESelectionByAttrGroup`  
`enum class ESelectionByAttrGroup : uint8`  
_L1533-1541_
- reflection: `UENUM(BlueprintType)`
- L1535 _public enumerator_ `Vertices UMETA(DisplayName = "Vertices")`
- L1536 _public enumerator_ `Faces UMETA(DisplayName = "Faces")`
- L1537 _public enumerator_ `Transform UMETA(DisplayName = "Transform")`
- L1538 _public enumerator_ `Geometry UMETA(DisplayName = "Geometry")`
- L1539 _public enumerator_ `Material UMETA(DisplayName = "Material")`
- L1540 _public enumerator_ `Curves UMETA(DisplayName = "Curves")`

#### enum `ESelectionByAttrOperation`  
`enum class ESelectionByAttrOperation : uint8`  
_L1553-1571_
- reflection: `UENUM(BlueprintType)`
- L1556 _public enumerator_ `Equal UMETA(DisplayName = "==")` — Select faces which attribute value equal with specified value
- L1558 _public enumerator_ `NotEqual UMETA(DisplayName = "!=")` — Select faces which attribute value not equal with specified value
- L1560 _public enumerator_ `Greater UMETA(DisplayName = ">")` — Select faces which attribute value greater than specified value
- L1562 _public enumerator_ `GreaterOrEqual UMETA(DisplayName = ">=")` — Select faces which attribute value greater or equal than specified value
- L1564 _public enumerator_ `Smaller UMETA(DisplayName = "<")` — Select faces which attribute value smaller than specified value
- L1566 _public enumerator_ `SmallerOrEqual UMETA(DisplayName = "<=")` — Select faces which attribute value greater than specified value
- L1568 _public enumerator_ `Maximum UMETA(DisplayName = "Max")` — Select faces which attribute value greater than specified value
- L1570 _public enumerator_ `Minimum UMETA(DisplayName = "Min")` — Select faces which attribute value greater than specified value

#### struct `FCollectionSelectionByAttrDataflowNode`  
`struct FCollectionSelectionByAttrDataflowNode : public FDataflowNode`  
_L1580-1649_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Selects specified Vertices/Faces/Transforms in the GeometryCollection by using an attribute value Currently supported attribute types: float, int32, String, bool DEPRECATED 5.8 - use FCollectionSelectionByAttributeDataflowNode instead
- L1588 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1592 _public member_ `FCollectionAttributeKey AttributeKey;` — `UPROPERTY(meta = (DataflowInput))` — AttributeKey input
- L1596 _public member_ `ESelectionByAttrGroup Group = ESelectionByAttrGroup::Faces;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Group
- L1600 _public member_ `FString Attribute = FString("Int` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Attribute for the selection
- L1604 _public member_ `ESelectionByAttrOperation Operation = ESelectionByAttrOperation::Equal;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Operation
- L1608 _public member_ `FString Value = FString("tru` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Attribute value for the operation
- L1612 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VertexSelection"))` — Vertex selection output
- L1616 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FaceSelection"))` — Face selection output
- L1620 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "TransformSelection"))` — Transform selection output
- L1624 _public member_ `FDataflowGeometrySelection GeometrySelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "GeometrySelection"))` — Geometry selection output
- L1628 _public member_ `FDataflowMaterialSelection MaterialSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "MaterialSelection"))` — Material selection output
- L1632 _public member_ `FDataflowCurveSelection CurveSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "CurveSelection"))` — Curve selection output
- L1634 _public function_ `FCollectionSelectionByAttrDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1648 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGeometrySelectionToVertexSelectionDataflowNode`  
`struct FGeometrySelectionToVertexSelectionDataflowNode final : public FDataflowNode`  
_L1657-1689_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.8"))`
- inherits: `FDataflowNode`
- desc: Converts GeometrySelection to VertexSelection DEPRECATED 5.8 - use FCollectionSelectionConvertDataflowNode_v2 instead
- L1665 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))` — GeometryCollection
- L1669 _public member_ `FString GeometryIndices = FString();` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Space separated list of geometry indices to specify the selection when GeometrySelection is not connected
- L1673 _public member_ `FDataflowGeometrySelection GeometrySelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "GeometrySelection"))` — Input geometry selection
- L1677 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "VertexSelection"))` — Vertex selection output
- L1679 _public function_ `FGeometrySelectionToVertexSelectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1688 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionSetOperationDataflowNode`  
`struct FCollectionSelectionSetOperationDataflowNode : public FDataflowNode`  
_L1697-1723_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Runs boolean operation on selection ( support all selection types )
- L1705 _private member_ `ESetOperationEnum Operation = ESetOperationEnum::Dataflow_SetOperation_AND;` — `UPROPERTY(EditAnywhere, Category = "Operation")` — Boolean operation
- L1709 _private member_ `FDataflowSelectionTypes SelectionA;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — First Selection object
- L1713 _private member_ `FDataflowSelectionTypes SelectionB;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Second Selection object
- L1717 _private member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "SelectionA"))` — Array of the selected bone indices after operation
- L1719 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1722 _public prototype_ `FCollectionSelectionSetOperationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FCollectionSelectionInvertDataflowNode`  
`struct FCollectionSelectionInvertDataflowNode : public FDataflowNode`  
_L1732-1746_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Inverts selection ( support all selection types )
- L1740 _private member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Selection", DataflowIntrinsic))` — selection to invert
- L1742 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1745 _public prototype_ `FCollectionSelectionInvertDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FCollectionSelectInternalFacesDataflowNode`  
`struct FCollectionSelectInternalFacesDataflowNode : public FDataflowNode`  
_L1754-1779_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Select internal faces
- L1762 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to select the internal faces from
- L1769 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — Transform selection to get the internal faces from if this input is not connected, then all internal faces from the collection will be returned
- L1773 _private member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowOutput))` — selection containing Internal faces
- L1775 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1778 _public prototype_ `FCollectionSelectInternalFacesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### enum `EDataflowCollectionSelectionByNameMethod`  
`enum class EDataflowCollectionSelectionByNameMethod: uint8`  
_L1782-1792_
- reflection: `UENUM()`
- L1785 _public enumerator_ `Exact` — name must match exactly the input text
- L1787 _public enumerator_ `StartsWith` — name must start with the input text
- L1789 _public enumerator_ `EndsWith` — name must end with the input text
- L1791 _public enumerator_ `Contains` — name must contain the input text

#### struct `FCollectionSelectTransformStringDataflowNode`  
`struct FCollectionSelectTransformStringDataflowNode : public FDataflowNode`  
_L1798-1828_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects transforms by name using a the BoneName attributeor other Transform group string typed attributes
- L1806 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the selection
- L1810 _private member_ `FString Attribute = "Bo` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Text to serach in the name
- L1814 _private member_ `FString SearchText;` — `UPROPERTY(EditAnywhere, Category = Options, meta=(DataflowInput))` — Text to serach in the name
- L1818 _private member_ `EDataflowCollectionSelectionByNameMethod Method = EDataflowCollectionSelectionByNameMethod::Contains;` — `UPROPERTY(EditAnywhere, Category = "Volume")` — Method to use to match the name
- L1822 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowOutput))` — output selection of the matching transforms
- L1824 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1827 _public prototype_ `FCollectionSelectTransformStringDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FCollectionSetTransformStringValueDataflowNode`  
`struct FCollectionSetTransformStringValueDataflowNode : public FDataflowNode`  
_L1837-1863_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Set selected transform string value the string format can use the following predefined value : - {Current} current value of the attribute - {Index} index in the selection passed as input
- L1845 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the selection
- L1849 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — input selection of the transforms to set - if not connected use all
- L1853 _private member_ `FString Attribute = "Bo` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Text to serach in the name
- L1857 _private member_ `FString TextToSet;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Text to set
- L1859 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1862 _public prototype_ `FCollectionSetTransformStringValueDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGetNumElementsInSelectionDataflowNode`  
`struct FGetNumElementsInSelectionDataflowNode : public FDataflowNode`  
_L1872-1893_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Returns number of elements in a Selection
- L1879 _private member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Selection", DataflowIntrinsic))`
- L1883 _private member_ `int32 NumElements = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of all (selected and non-selected) elements in the Selection
- L1887 _private member_ `int32 NumSelectedElements = 0;` — `UPROPERTY(meta = (DataflowOutput))` — Number of selected elements in the Selection
- L1889 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1892 _public prototype_ `FGetNumElementsInSelectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FCollectionSelectionCustomDataflowNode`  
`struct FCollectionSelectionCustomDataflowNode : public FDataflowNode`  
_L1903-1925_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Creates any type of selection from a collection by using a comma separated list
- L1911 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1915 _public member_ `FString Indices = FString();` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput))` — Comma separated list of indices (example: "0, 2, 5-10, 12-15") to specify the selection
- L1919 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Selection from the indices. To set the selection type rt mouse click on the Selection output
- L1921 _public prototype_ `FCollectionSelectionCustomDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1924 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionConvertDataflowNode_v2`  
`struct FCollectionSelectionConvertDataflowNode_v2 : public FDataflowNode`  
_L1936-1958_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Converts Vertex/Face/Transform selection into Vertex/Face/Transform selection Supported groups: Transform/Vertices/Faces/Geometry/Curves
- L1944 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1948 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Selection", DataflowIntrinsic))` — Vertex/Face/Transform selection to convert. To set the selection type rt mouse click on the Selection output
- L1952 _public member_ `bool bAllElementsMustBeSelected = false;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — If true then for converting vertex/face selection to transform selection all vertex/face must be selected for selecting the associated transform
- L1954 _public prototype_ `FCollectionSelectionConvertDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1957 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionAllDataflowNode`  
`struct FCollectionSelectionAllDataflowNode : public FDataflowNode`  
_L1968-1987_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects all the elements in the selected group from the collection
- L1976 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L1980 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Output selection. To set the selection type rt mouse click on the Selection output
- L1982 _public prototype_ `FCollectionSelectionAllDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L1985 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionNoneDataflowNode`  
`struct FCollectionSelectionNoneDataflowNode : public FDataflowNode`  
_L1997-2016_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects none of the elements in the selected group from the collection
- L2005 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L2009 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Output selection. To set the selection type rt mouse click on the Selection output
- L2011 _public prototype_ `FCollectionSelectionNoneDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L2014 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionRandomDataflowNode`  
`struct FCollectionSelectionRandomDataflowNode : public FDataflowNode`  
_L2026-2057_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects randomly in the collection from the specified group
- L2034 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L2038 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Random")` — If true, it always generates the same result for the same RandomSeed
- L2042 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, EditCondition = "bDeterministic"))` — Seed for the random generation, only used if Deterministic is on
- L2046 _public member_ `float RandomThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, UIMin = 0.f, UIMax = 1.f))` — Get selected if RandomValue < RandomThreshold
- L2050 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Output selection. To set the selection type rt mouse click on the Selection output
- L2052 _public prototype_ `FCollectionSelectionRandomDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L2055 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionByPercentageDataflowNode`  
`struct FCollectionSelectionByPercentageDataflowNode : public FDataflowNode`  
_L2067-2094_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects specified percentage of elements in the collection from the specified group
- L2075 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Selection", DataflowIntrinsic))` — Selection to selectt from by percentage
- L2079 _public member_ `int32 Percentage = 100;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput, UIMin = 0, ClampMin = 0, UIMax = 100, ClampMax = 100))` — Percentage to keep from the elements
- L2083 _public member_ `bool bDeterministic = false;` — `UPROPERTY(EditAnywhere, Category = "Random")` — If true, it always generates the same result for the same RandomSeed
- L2087 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput, EditCondition = "bDeterministic"))` — Seed for the random generation, only used if Deterministic is on
- L2089 _public prototype_ `FCollectionSelectionByPercentageDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L2092 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionByAttributeDataflowNode`  
`struct FCollectionSelectionByAttributeDataflowNode : public FDataflowNode`  
_L2105-2135_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects specified Vertices/Faces/Transforms/.... in the collection by using an attribute value Currently supported attribute types: float, int32, String, bool
- L2113 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L2117 _public member_ `FString Attribute = FString("Int` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Attribute for the selection
- L2121 _public member_ `ESelectionByAttrOperation Operation = ESelectionByAttrOperation::Equal;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Operation
- L2125 _public member_ `FString Value = FString("tru` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Attribute value for the operation
- L2129 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Selection output. To set the selection type rt mouse click on the Selection output
- L2131 _public prototype_ `FCollectionSelectionByAttributeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L2134 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionSelectionByPrimitiveDataflowNode`  
`struct FCollectionSelectionByPrimitiveDataflowNode : public FDataflowNode`  
_L2146-2193_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Selects elements which are contained in a transformed box Supported groups: Transform/Vertices/Faces/Geometry/Curves
- L2154 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L2158 _private member_ `FDataflowPrimitiveTypes Primitive;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput))` — Primitive used for the selection (Box, Sphere or Plane)
- L2162 _private member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput, GizmoType = "Transform"))` — Transform for the primitive
- L2166 _private member_ `bool bAllElementsMustBeSelected = false;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — If true then all elements must contained by the primitive (all vertices of a face, all vertices of a curve, etc.)
- L2170 _private member_ `bool bPositiveSide = true;` — `UPROPERTY(EditAnywhere, Category = "Select")` — Select elements on positive side of the plane. Only used for selection by plane.
- L2174 _private member_ `float PlaneSize = 250.f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Plane", meta = (UIMin = 1, ClampMin = 1))` — DebugDraw / Plane size
- L2178 _private member_ `int32 VertexPerEdge = 5;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Plane", meta = (UIMin = 2, ClampMin = 2))` — DebugDraw / Vertex per edge
- L2182 _private member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Output selection
- L2184 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L2187 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L2188 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L2192 _public prototype_ `FCollectionSelectionByPrimitiveDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### enum `ESelectionByMeshMethodFlags`  
`enum class ESelectionByMeshMethodFlags : uint8`  
_L2201-2207_
- reflection: `UENUM(BlueprintType)`
- desc: Flags to control which mesh point filtering method(s) are applied
- L2203 _public enumerator_ `None UMETA(DisplayName = "None")`
- L2204 _public enumerator_ `Winding UMETA(DisplayName = "Winding")`
- L2205 _public enumerator_ `MinDistance UMETA(DisplayName = "MinDistance")`
- L2206 _public enumerator_ `MaxDistance UMETA(DisplayName = "MaxDistance")`

#### struct `FCollectionSelectionByMeshDataflowNode`  
`struct FCollectionSelectionByMeshDataflowNode : public FDataflowNode`  
_L2214-2266_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Collection selection bassed on if the element is inside or outside of a given mesh
- L2220 _public prototype_ `FCollectionSelectionByMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L2225 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L2229 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh to use for the selection
- L2232 _private member_ `ESelectionByMeshMethodFlags FilterMethod = ESelectionByMeshMethodFlags::Winding;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L2236 _private member_ `bool bKeepInside = true;` — `UPROPERTY(EditAnywhere, Category = WindingNumber, meta = (DataflowInput, EditCondition = "FilterMethod == ESelectionByMeshMethodFlags::Winding"))` — Whether to keep the points inside or (if false) outside the mesh, when filtering by Winding Number.
- L2240 _private member_ `float WindingThreshold = .5f;` — `UPROPERTY(EditAnywhere, Category = WindingNumber, meta = (DataflowInput))` — The winding number threshold to use for determining whether a point is inside or outside of the mesh, if corresponding Filter Method is set
- L2244 _private member_ `float MinDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput, EditCondition = "FilterMethod == ESelectionByMeshMethodFlags::MinDistance"))` — The min distance to surface to keep, if corresponding Filter Method is set
- L2248 _private member_ `float MaxDistance = 1000.f;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput, EditCondition = "FilterMethod == ESelectionByMeshMethodFlags::MaxDistance"))` — The max distance to surface to keep, if corresponding Filter Method is set
- L2255 _private member_ `bool bUseSignedDistance = false;` — `UPROPERTY(EditAnywhere, Category = Distance, meta = (DataflowInput))` — Whether to use signed distances for the Min and Max Distance thresholds. Otherwise, unsigned distance is used. Note: Signs are computed via the Winding Number. The sign is negative if the point's Winding Number is below the Winding Threshold.
- L2259 _private member_ `bool bAllElementsMustBeSelected = false;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — If true then for converting vertex/face selection to transform selection all vertex/face must be selected for selecting the associated transform
- L2263 _private member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowOutput))` — Output selection
- L2265 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ESelectionToAttributeTypeFlags`  
`enum class ESelectionToAttributeTypeFlags : uint8`  
_L2272-2291_
- reflection: `UENUM(BlueprintType)`
- desc: Attribute type for SelectionToAttribute
- L2274 _public enumerator_ `Int UMETA(DisplayName = "Int")`
- L2275 _public enumerator_ `Float UMETA(DisplayName = "Float")`
- L2276 _public enumerator_ `Bool UMETA(DisplayName = "Bool")`
- L2277 _public enumerator_ `Double UMETA(DisplayName = "Double")`
- L2278 _public enumerator_ `String UMETA(DisplayName = "String")`
- L2279 _public enumerator_ `Name UMETA(DisplayName = "Name")`
- L2280 _public enumerator_ `Vec2f UMETA(DisplayName = "Vec2f")`
- L2281 _public enumerator_ `Vec3f UMETA(DisplayName = "Vec3f")`
- L2282 _public enumerator_ `Vec4f UMETA(DisplayName = "Vec4f")`
- L2283 _public enumerator_ `Vec2i UMETA(DisplayName = "Vec2i")`
- L2284 _public enumerator_ `Vec3i UMETA(DisplayName = "Vec3i")`
- L2285 _public enumerator_ `Vec4i UMETA(DisplayName = "Vec4i")`
- L2286 _public enumerator_ `Color UMETA(DisplayName = "Color")`
- L2287 _public enumerator_ `Transform UMETA(DisplayName = "Transform")`
- L2288 _public enumerator_ `Matrix UMETA(DisplayName = "Matrix")`
- L2289 _public enumerator_ `Quat UMETA(DisplayName = "Quat")`
- L2290 _public enumerator_ `Box UMETA(DisplayName = "Box")`

#### struct `FCollectionSelectionToAttributeDataflowNode`  
`struct FCollectionSelectionToAttributeDataflowNode : public FDataflowNode`  
_L2301-2335_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Creates specified attribute on the incoming selection's group and sets specified value to selected elements, the nonselected elements will be set to default valu. If the attribute already exists then sets specified value to selected elements.
- L2309 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection input
- L2313 _public member_ `FDataflowSelectionTypes Selection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Selection input. The type of this selection defines the group where the data will be stored
- L2317 _public member_ `ESelectionToAttributeTypeFlags AttributeType = ESelectionToAttributeTypeFlags::Int;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — Attribute type for storing the selection if not already in the collection
- L2321 _public member_ `FString Attribute = FString("Dum` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Attribute", DisplayName = "Attribute Name"))` — Attribute for storing the selection
- L2325 _public member_ `FString DefaultValue = FString("0")` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput))` — Attribute default value
- L2329 _public member_ `FString Value = FString("1")` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (DataflowInput, DisplayName = "Selection Value"))` — Attribute value
- L2331 _public prototype_ `FCollectionSelectionToAttributeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L2334 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Dataflow`
- L1543 _namespace_ `namespace UE`
- L1543 _namespace_ `namespace Dataflow` (scope `UE`)
- L1543 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L1545 _function_ `inline FName GetAttributeFromEnumAsName(const ESelectionByAttrGroup Value)` (scope `UE::Dataflow::Private`)
- L2339 _namespace_ `namespace UE`
- L2339 _namespace_ `namespace Dataflow` (scope `UE`)
- L2341 _prototype_ `void GeometryCollectionSelectionNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionSkeletalMeshToCollectionNode.h` (Public)


#### struct `FSkeletalMeshToCollectionDataflowNode`  
`struct FSkeletalMeshToCollectionDataflowNode : public FDataflowNode`  
_L18-43_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L24 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L27 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "SkeletalMesh"))`
- L30 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection"))`
- L33 _public member_ `bool bImportTransformOnly = false;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DisplayName = "Transforms Only"))`
- L35 _public function_ `FSkeletalMeshToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L42 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCollectionToSkeletalMeshDataflowNode`  
`struct FCollectionToSkeletalMeshDataflowNode : public FDataflowNode`  
_L47-74_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L54 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))`
- L57 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowInput))`
- L60 _private member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh = nullptr;` — `UPROPERTY(meta = (DataflowOutput))`
- L63 _private member_ `TObjectPtr<const USkeleton> Skeleton = nullptr;` — `UPROPERTY(meta = (DataflowOutput))`
- L65 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L68 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L69 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L73 _public prototype_ `FCollectionToSkeletalMeshDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionSkeletonToCollectionNode.h` (Public)


#### struct `FSkeletonToCollectionDataflowNode`  
`struct UE_DEPRECATED(5.5, "Use SkeletalMeshToCollection instead") FSkeletonToCollectionDataflowNode : public FDataflowNode`  
_L16-38_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Deprecated = "5.5"))`
- inherits: `FDataflowNode`
- L22 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L25 _public member_ `TObjectPtr<const USkeleton> Skeleton = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "Skeleton"))`
- L28 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection"))`
- L30 _public function_ `FSkeletonToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L37 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionStaticMeshToCollectionNode.h` (Public)


#### struct `FStaticMeshToCollectionDataflowNode_v2`  
`struct FStaticMeshToCollectionDataflowNode_v2 : public FDataflowNode`  
_L22-64_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Create a geometry collection from a UStaticMesh
- L30 _private member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (DataflowInput))` — Asset input
- L34 _private member_ `FTransform MeshTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (DataflowInput, GizmoType = "Transform"))` — Transform to apply to the mesh before converting it to a collection
- L38 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))` — Geometry collection newly created
- L42 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(meta = (DataflowOutput))` — Material array from the static mesh
- L46 _private member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowOutput))` — Array of instanced meshes
- L50 _private member_ `TArray<FDataflowRootProxyMesh> RootProxyMeshes;` — `UPROPERTY(meta = (DataflowOutput))` — corresponding source proxies
- L54 _private member_ `bool bSetInternalFromMaterialIndex = true;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Set the internal faces from material index
- L58 _private member_ `bool bSplitComponents = false;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Split components - when enabled, each island of the mesh will be converted to an individual transform in the collection
- L60 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L63 _public prototype_ `FStaticMeshToCollectionDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FStaticMeshToCollectionDataflowNode`  
`struct FStaticMeshToCollectionDataflowNode : public FDataflowNode`  
_L71-111_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowNode`
- desc: Create a geometry collection from a UStaticMesh Deprecated (5.6) - use the second version of StaticMeshToCollection node with only one materials ouput
- L79 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (DataflowInput, DisplayName = "StaticMesh"))` — Asset input
- L83 _public member_ `FTransform MeshTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (DataflowInput, GizmoType = "Transform"))` — Transform to apply to the mesh before converting it to a collection
- L87 _public member_ `bool bSetInternalFromMaterialIndex = true;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Set the internal faces from material index
- L91 _public member_ `bool bSplitComponents = false;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Split components
- L95 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Collection"))` — Geometry collection newly created
- L99 _public member_ `TArray<TObjectPtr<UMaterial>> Materials;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Materials"))` — Materials array to use for this asset
- L103 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialInstances;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "MaterialInstances"))` — Material instances array from the static mesh
- L107 _public member_ `TArray<FGeometryCollectionAutoInstanceMesh> InstancedMeshes;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "InstancedMeshes"))` — Array of instanced meshes
- L109 _public prototype_ `FStaticMeshToCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L110 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Dataflow`
- L113 _namespace_ `namespace UE`
- L113 _namespace_ `namespace Dataflow` (scope `UE`)
- L115 _prototype_ `void RegisterGeometryStaticMeshToCollectionNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionTextureNodes.h` (Public)


#### enum `ECollectionBakeTextureAttribute`  
`enum class ECollectionBakeTextureAttribute: int32`  
_L16-47_
- reflection: `UENUM()`
- L19 _public enumerator_ `None = (int32)UE::PlanarCut::EBakeAttributes::None` — no attribute selected
- L22 _public enumerator_ `DistanceToExternal = (int32)UE::PlanarCut::EBakeAttributes::DistanceToExternal` — Phi value : distance to the closest face
- L25 _public enumerator_ `AmbientOcclusion = (int32)UE::PlanarCut::EBakeAttributes::AmbientOcclusion` — Ambient occlusion
- L28 _public enumerator_ `Curvature = (int32)UE::PlanarCut::EBakeAttributes::Curvature` — surface smoothed curvature
- L31 _public enumerator_ `NormalX = (int32)UE::PlanarCut::EBakeAttributes::NormalX` — Normal X coordinate ( object space )
- L34 _public enumerator_ `NormalY = (int32)UE::PlanarCut::EBakeAttributes::NormalY` — Normal Y coordinate ( object space )
- L37 _public enumerator_ `NormalZ = (int32)UE::PlanarCut::EBakeAttributes::NormalZ` — Normal Z coordinate ( object space )
- L40 _public enumerator_ `PositionX = (int32)UE::PlanarCut::EBakeAttributes::PositionX` — Position X coordinate ( relative to object local bounds )
- L43 _public enumerator_ `PositionY = (int32)UE::PlanarCut::EBakeAttributes::PositionY` — Position Y coordinate ( relative to object local bounds )
- L46 _public enumerator_ `PositionZ = (int32)UE::PlanarCut::EBakeAttributes::PositionZ` — Position Z coordinate ( relative to object local bounds )

#### struct `FBakeTextureFromCollectionDataflowNode`  
`struct FBakeTextureFromCollectionDataflowNode : public FDataflowNode`  
_L54-168_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Bake a texture from a geometry collection Output to a 4 channels Image object  ( RGBA )
- L66 _public member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowOutput))` — Output image with the bake attributes
- L70 _public member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput))` — selection of faces to bake : if not connected, all faces will be used
- L74 _public member_ `EDataflowImageResolution Resolution = EDataflowImageResolution::Resolution512;` — `UPROPERTY(EditAnywhere, Category = ImageOptions, meta = (DataflowInput))` — resolution of the image to bake
- L78 _public member_ `bool bFullyPadGutter = false;` — `UPROPERTY(EditAnywhere, Category = ChannelOptions, meta = (DataflowInput))` — Whether to pad out gutter size so that all empty texels are filled
- L82 _public member_ `int32 GutterSize = 1;` — `UPROPERTY(EditAnywhere, Category = ChannelOptions, meta = (DataflowInput, EditCondition="!bFullyPadGutter", ClampMin = 1, UIMin = 1))` — Approximate space to fill in between UV islands, measured in texels. Ignored if Fully Pad Gutter is enabled.
- L86 _public member_ `bool bClearGutterAlpha = true;` — `UPROPERTY(EditAnywhere, Category = ChannelOptions, meta = (DataflowInput))` — If true, will clear the alpha channel for gutter pixels, so they are transparent and the UV boundaries are clearer. If false, gutter pixel values will be copied as-is from the nearest interior pixel.
- L90 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = ChannelOptions, meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "UVChannel", DataflowUVChannel, ClampMin = 0, ClampMax = 7, UIMin = 0, UIMax = 7))` — Index of the added UV channel
- L94 _public member_ `ECollectionBakeTextureAttribute RedChannel = ECollectionBakeTextureAttribute::DistanceToExternal;` — `UPROPERTY(EditAnywhere, Category = ChannelOptions)` — Attribute to bake in the red channel
- L98 _public member_ `ECollectionBakeTextureAttribute GreenChannel = ECollectionBakeTextureAttribute::AmbientOcclusion;` — `UPROPERTY(EditAnywhere, Category = ChannelOptions)` — Attribute to bake in the green channel
- L102 _public member_ `ECollectionBakeTextureAttribute BlueChannel = ECollectionBakeTextureAttribute::Curvature;` — `UPROPERTY(EditAnywhere, Category = ChannelOptions)` — Attribute to bake in the blue channel
- L106 _public member_ `ECollectionBakeTextureAttribute AlphaChannel = ECollectionBakeTextureAttribute::None;` — `UPROPERTY(EditAnywhere, Category = ChannelOptions)` — Attribute to bake in the alpha channel
- L113 _public member_ `float MaxDistance = 100;` — `UPROPERTY(EditAnywhere, Category = DistToOuterSettings, meta = ( DataflowInput, EditCondition = "RedChannel == ECollectionBakeTextureAttribute::DistanceToExternal || GreenChannel == ECollectionBakeTextureAttribute::DistanceToExternal || BlueChannel == ECollectionBakeTextureAttribute::DistanceToExternal || AlphaChannel == ECollectionBakeTextureAttribute::DistanceToExternal", UIMin = "1", UIMax = "100", ClampMin = ".01", ClampMax = "1000"))` — Max distance to search for the outer mesh surface
- L120 _public member_ `int32 OcclusionRays = 16;` — `UPROPERTY(EditAnywhere, Category = AmbientOcclusionSettings, meta = ( DataflowInput, EditCondition = "RedChannel == ECollectionBakeTextureAttribute::AmbientOcclusion || GreenChannel == ECollectionBakeTextureAttribute::AmbientOcclusion || BlueChannel == ECollectionBakeTextureAttribute::AmbientOcclusion || AlphaChannel == ECollectionBakeTextureAttribute::AmbientOcclusion", UIMin = "1", UIMax = "1024", ClampMin = "0", ClampMax = "50000"))` — Number of occlusion rays
- L127 _public member_ `float OcclusionBlurRadius = 2.25;` — `UPROPERTY(EditAnywhere, Category = AmbientOcclusionSettings, meta = ( DataflowInput, EditCondition = "RedChannel == ECollectionBakeTextureAttribute::AmbientOcclusion || GreenChannel == ECollectionBakeTextureAttribute::AmbientOcclusion || BlueChannel == ECollectionBakeTextureAttribute::AmbientOcclusion || AlphaChannel == ECollectionBakeTextureAttribute::AmbientOcclusion", UIMin = "0", UIMax = "10.0", ClampMin = "0", ClampMax = "100.0"))` — Pixel Radius of Gaussian Blur Kernel applied to AO map (0 will apply no blur)
- L134 _public member_ `float CurvatureBlurRadius = 2.25;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = ( DataflowInput, EditCondition = "RedChannel == ECollectionBakeTextureAttribute::Curvature || GreenChannel == ECollectionBakeTextureAttribute::Curvature || BlueChannel == ECollectionBakeTextureAttribute::Curvature || AlphaChannel == ECollectionBakeTextureAttribute::Curvature", UIMin = "0", UIMax = "10.0", ClampMin = "0", ClampMax = "100.0"))` — Pixel Radius of Gaussian Blur Kernel applied to Curvature map (0 will apply no blur)
- L141 _public member_ `int32 VoxelResolution = 128;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = ( DataflowInput, EditCondition = "RedChannel == ECollectionBakeTextureAttribute::Curvature || GreenChannel == ECollectionBakeTextureAttribute::Curvature || BlueChannel == ECollectionBakeTextureAttribute::Curvature || AlphaChannel == ECollectionBakeTextureAttribute::Curvature", UIMin = "8", UIMax = "512", ClampMin = "4", ClampMax = "1024"))` — Voxel resolution of smoothed shape representation
- L148 _public member_ `int32 SmoothingIterations = 10;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = ( DataflowInput, EditCondition = "RedChannel == ECollectionBakeTextureAttribute::Curvature || GreenChannel == ECollectionBakeTextureAttribute::Curvature || BlueChannel == ECollectionBakeTextureAttribute::Curvature || AlphaChannel == ECollectionBakeTextureAttribute::Curvature", UIMin = "2", UIMax = "100", ClampMin = "2", ClampMax = "1000"))` — Amount of smoothing iterations to apply before computing curvature
- L155 _public member_ `float ThicknessFactor = 4;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = ( DataflowInput, EditCondition = "RedChannel == ECollectionBakeTextureAttribute::Curvature || GreenChannel == ECollectionBakeTextureAttribute::Curvature || BlueChannel == ECollectionBakeTextureAttribute::Curvature || AlphaChannel == ECollectionBakeTextureAttribute::Curvature", UIMin = "2", UIMax = "10.0", ClampMin = "1", ClampMax = "100.0"))` — Distance to search for correspondence between fractured shape and smoothed shape, as factor of voxel size
- L162 _public member_ `float MaxCurvature = .1f;` — `UPROPERTY(EditAnywhere, Category = SmoothedCurvatureSettings, meta = ( DataflowInput, EditCondition = "RedChannel == ECollectionBakeTextureAttribute::Curvature || GreenChannel == ECollectionBakeTextureAttribute::Curvature || BlueChannel == ECollectionBakeTextureAttribute::Curvature || AlphaChannel == ECollectionBakeTextureAttribute::Curvature", UIMin = ".01", UIMax = "1", ClampMin = ".0001", ClampMax = "10"))` — Curvatures in the range [-MaxCurvature, MaxCurvature] will be mapped from [0,1]. Values outside that range will be clamped
- L164 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L167 _public prototype_ `FBakeTextureFromCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L170 _namespace_ `namespace UE`
- L170 _namespace_ `namespace Dataflow` (scope `UE`)
- L172 _prototype_ `void RegisterGeometryCollectionTextureNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionTransferVertexAttributeNode.h` (Public)


#### enum `EDataflowTransferVertexAttributeNodeFalloff`  
`enum class EDataflowTransferVertexAttributeNodeFalloff : uint8`  
_L17-30_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Squared UMETA(DisplayName = "Squared")` — Squared falloff based on distance from triangle
- L23 _public enumerator_ `Linear UMETA(DisplayName = "Linear")` — Linear falloff based on distance from triangle
- L26 _public enumerator_ `None UMETA(DisplayName = "None")` — No distance falloff
- L29 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `EDataflowTransferVertexAttributeNodeSourceScale`  
`enum class EDataflowTransferVertexAttributeNodeSourceScale : uint8`  
_L33-48_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `Component_Edge UMETA(DisplayName = "Component Max Edge")` — Bounding volume hierarchy cell size based on max edge length of each geometry group. Only works if there is 1-1 correspondence between source and target geometries, otherwise default to Asset Max Edge
- L40 _public enumerator_ `Asset_Edge UMETA(DisplayName = "Asset Max Edge")` — Bounding volume hierarchy cell size based on max edge length of the whole asset
- L43 _public enumerator_ `Asset_Bound UMETA(DisplayName = "Asset Max Bound")` — Bounding volume hierarchy cell size based on max length of the bounding box of the whole asset
- L47 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `EDataflowTransferVertexAttributeNodeBoundingVolume`  
`enum class EDataflowTransferVertexAttributeNodeBoundingVolume : uint8`  
_L51-62_
- reflection: `UENUM(BlueprintType)`
- L54 _public enumerator_ `Vertex UMETA(DisplayName = "Vertex")` — Bounding volume on vertices of the source mesh
- L57 _public enumerator_ `Triangle UMETA(DisplayName = "Triangle")` — Bounding volume on triangles of the source triangle mesh
- L61 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `EDataflowTransferVertexAttributeNodeTransferMethod`  
`enum class EDataflowTransferVertexAttributeNodeTransferMethod : uint8`  
_L65-78_
- reflection: `UENUM(BlueprintType)`
- L68 _public enumerator_ `Component UMETA(DisplayName = "Paired Geometry Transfer")` — Transfers vertex attribute between matched geometries.
- L71 _public enumerator_ `Global UMETA(DisplayName = "Global Transfer")` — Transfers vertex attribute globally. Warning: attributes on one geometry might bleed over to neighbor geometries.
- L74 _public enumerator_ `None UMETA(DisplayName = "None")` — No transfer
- L77 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FGeometryCollectionTransferVertexAttributeNode`  
`struct FGeometryCollectionTransferVertexAttributeNode : public FDataflowNode`  
_L90-162_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Transfer float properties from a source collection to a target collection. Component Transfer is used when all geometries from the source collection have matched names with the target collection. Otherwise, Global Transfer is used. Geometries are matched when the geometry's BoneName can be found as the start of the BoneName of a geometry in the target collection. Use TransformNameSuffix to add extra string to the source geometry's BoneName to avoid multiple matched names. For example, source geometry has name SK_10 and target geometry has name SK_10_tet1 For all names, Check BoneName attribute in Transform group in the collection.
- L100 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))` — Target collection to transfer vertex attribute to.
- L104 _public member_ `FManagedArrayCollection FromCollection;` — `UPROPERTY(Meta = (DataflowInput, DisplayName = "FromCollection"))` — Source collection to transfer vertex attribute from.
- L108 _public member_ `FCollectionAttributeKey AttributeKey = FCollectionAttributeKey(FString(""), FString("Vert` — `UPROPERTY(EditAnywhere, Category = "Dataflow", Meta = (DataflowInput, DataflowOutput, DisplayName = "AttributeKey", DataflowPassthrough = "AttributeKey"))` — The name of the vertex attribute to generate indices from.
- L112 _public member_ `EDataflowTransferVertexAttributeNodeTransferMethod TransferMethod = EDataflowTransferVertexAttributeNodeTransferMethod::Global;` — `UPROPERTY(EditAnywhere, Category = "Method")` — Transfer method [default: Paired Geometry Transfer]
- L116 _public member_ `EDataflowTransferVertexAttributeNodeBoundingVolume BoundingVolumeType = EDataflowTransferVertexAttributeNodeBoundingVolume::Triangle;` — `UPROPERTY(EditAnywhere, Category = "Thresholds")` — Bounding volume type for source assets[default: Triangle]
- L120 _public member_ `EDataflowTransferVertexAttributeNodeSourceScale SourceScale = EDataflowTransferVertexAttributeNodeSourceScale::Asset_Bound;` — `UPROPERTY(EditAnywhere, Category = "Thresholds")` — Bounding volume hierarchy cell size for neighboring vertices to transfer into[default: Asset]
- L124 _public member_ `EDataflowTransferVertexAttributeNodeFalloff Falloff = EDataflowTransferVertexAttributeNodeFalloff::None;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = (EditCondition = "BoundingVolumeType == EDataflowTransferVertexAttributeNodeBoundingVolume::Triangle", EditConditionHides))` — Falloff of source value based on distance from source triangle[default: Squared]
- L130 _public member_ `float FalloffThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = (EditCondition = "Falloff != EDataflowTransferVertexAttributeNodeFalloff::None" , EditConditionHides))` — Threshold based on distance from source triangle.Values past the threshold will falloff.[Defaults to 1 percent of triangle size(0.01)]
- L134 _public member_ `float EdgeMultiplier = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = (EditCondition = "SourceScale == EDataflowTransferVertexAttributeNodeSourceScale::Asset_Edge || SourceScale == EDataflowTransferVertexAttributeNodeSourceScale::Component_Edge", EditConditionHides))` — Edge multiplier for the Bounding Volume Hierarchy(BVH) target's particle search radius.
- L140 _public member_ `float BoundMultiplier = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = ( EditCondition = "SourceScale == EDataflowTransferVertexAttributeNodeSourceScale::Asset_Bound", EditConditionHides))` — Max bound multiplier for the Bounding Volume Hierarchy(BVH) target's particle search radius.
- L146 _public member_ `FString TransformNameSuffix = "_T` — `UPROPERTY(EditAnywhere, Category = "Paired Geometry Transfer", meta = ( EditCondition = "TransferMethod == EDataflowTransferVertexAttributeNodeTransferMethod::Component", EditConditionHides))` — Suffix of transform names added to the source geometry's BoneName for geometry matching during transfer[default: _Tet]. In CreateTetrahedron node we add _Tet to tetrahedral geometries.
- L148 _public function_ `FGeometryCollectionTransferVertexAttributeNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L161 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGeometryCollectionTransferVertexSkinWeightsNode`  
`struct FGeometryCollectionTransferVertexSkinWeightsNode : public FDataflowNode`  
_L174-236_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Transfer skin weights from a source collection to a target collection. Component Transfer is used when all geometries from the source collection have matched names with the target collection. Otherwise, Global Transfer is used. Geometries are matched when the geometry's BoneName can be found as the start of the BoneName of a geometry in the target collection. Use TransformNameSuffix to add extra string to the source geometry's BoneName to avoid multiple matched names. For example, source geometry has name SK_10 and target geometry has name SK_10_tet1 For all names, Check BoneName attribute in Transform group in the collection.
- L183 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))` — Target collection to transfer vertex attribute to.
- L187 _public member_ `FManagedArrayCollection FromCollection;` — `UPROPERTY(Meta = (DataflowInput, DisplayName = "FromCollection"))` — Source collection to transfer vertex attribute from.
- L191 _public member_ `EDataflowTransferVertexAttributeNodeTransferMethod TransferMethod = EDataflowTransferVertexAttributeNodeTransferMethod::Global;` — `UPROPERTY(EditAnywhere, Category = "Method")` — Transfer method [default: Paired Geometry Transfer]
- L195 _public member_ `EDataflowTransferVertexAttributeNodeBoundingVolume BoundingVolumeType = EDataflowTransferVertexAttributeNodeBoundingVolume::Triangle;` — `UPROPERTY(EditAnywhere, Category = "Thresholds")` — Bounding volume type for source assets[default: Triangle]
- L199 _public member_ `EDataflowTransferVertexAttributeNodeSourceScale SourceScale = EDataflowTransferVertexAttributeNodeSourceScale::Asset_Bound;` — `UPROPERTY(EditAnywhere, Category = "Thresholds")` — Bounding volume hierarchy cell size for neighboring vertices to transfer into[default: Asset]
- L203 _public member_ `EDataflowTransferVertexAttributeNodeFalloff Falloff = EDataflowTransferVertexAttributeNodeFalloff::None;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = (EditCondition = "BoundingVolumeType == EDataflowTransferVertexAttributeNodeBoundingVolume::Triangle", EditConditionHides))` — Falloff of source value based on distance from source triangle[default: Squared]
- L207 _public member_ `float FalloffThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = (EditCondition = "Falloff != EDataflowTransferVertexAttributeNodeFalloff::None", EditConditionHides))` — Threshold based on distance from source triangle.Values past the threshold will falloff.[Defaults to 1 percent of triangle size(0.01)]
- L211 _public member_ `float EdgeMultiplier = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = (EditCondition = "SourceScale == EDataflowTransferVertexAttributeNodeSourceScale::Asset_Edge || SourceScale == EDataflowTransferVertexAttributeNodeSourceScale::Component_Edge", EditConditionHides))` — Edge multiplier for the Bounding Volume Hierarchy(BVH) target's particle search radius.
- L217 _public member_ `float BoundMultiplier = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Thresholds", meta = ( EditCondition = "SourceScale == EDataflowTransferVertexAttributeNodeSourceScale::Asset_Bound", EditConditionHides))` — Max bound multiplier for the Bounding Volume Hierarchy(BVH) target's particle search radius.
- L223 _public member_ `FString TransformNameSuffix = "_T` — `UPROPERTY(EditAnywhere, Category = "Paired Geometry Transfer", meta = ( EditCondition = "TransferMethod == EDataflowTransferVertexAttributeNodeTransferMethod::Component", EditConditionHides))` — Suffix of transform names for geometry matching during transfer[default: _Tet]. In CreateTetrahedron node we add _Tet to tetrahedral geometries.
- L225 _public function_ `FGeometryCollectionTransferVertexSkinWeightsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L235 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `ESetKinematicVertexSelectionKinematicValue`  
`enum class ESetKinematicVertexSelectionKinematicValue : uint8`  
_L239-246_
- reflection: `UENUM(BlueprintType)`
- L242 _public enumerator_ `SetKinematic UMETA(DisplayName = "Kinematic")` — Set vertices to be kinematic
- L245 _public enumerator_ `SetNonKinematic UMETA(DisplayName = "Non-Kinematic")` — Set vertices to be dynamic

#### struct `FGeometryCollectionSetKinematicVertexSelectionNode`  
`struct FGeometryCollectionSetKinematicVertexSelectionNode : public FDataflowNode`  
_L252-280_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Set VertexSelection to be kinematic. Note that kinematic particles need skin weights.
- L260 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L264 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "VertexSelection"))` — Vertex Selection set to be kinematic
- L267 _public member_ `ESetKinematicVertexSelectionKinematicValue KinematicValue = ESetKinematicVertexSelectionKinematicValue::SetKinematic;` — `UPROPERTY(EditAnywhere, Category = "Method", meta = (DisplayName = "VertexSelection"))`
- L269 _public function_ `FGeometryCollectionSetKinematicVertexSelectionNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L279 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Dataflow`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionTriangleBoundaryIndicesNode.h` (Public)


#### struct `FTriangleBoundaryIndicesNode`  
`struct FTriangleBoundaryIndicesNode : public FDataflowNode`  
_L15-33_
- reflection: `USTRUCT(meta = (DataflowFlesh, Experimental))`
- inherits: `FDataflowNode`
- desc: Outputs boundary nodes of a triangle mesh
- L21 _private typedef_ `typedef FManagedArrayCollection DataType;`
- L24 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Collection", DataflowPassthrough = "Collection"))`
- L27 _private member_ `TArray<int32> BoundaryIndicesOut;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "BoundaryIndices"))`
- L29 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L32 _public prototype_ `FTriangleBoundaryIndicesNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionUVNodes.h` (Public)


#### struct `FAddUVChannelDataflowNode`  
`struct FAddUVChannelDataflowNode : public FDataflowNode`  
_L16-38_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Add a new UV channel to the collection note that there's a maximum of 8 channels that can be handled by a collection
- L28 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(meta = (DataflowOutput, DataflowUVChannel))` — Index of the added UV channel
- L32 _public member_ `FVector2f DefaultValue = { 0, 0 };` — `UPROPERTY(EditAnywhere, Category = Options)` — Value to initialize the UV with
- L34 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L37 _public prototype_ `FAddUVChannelDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FAutoUnwrapUVDataflowNode`  
`struct FAutoUnwrapUVDataflowNode : public FDataflowNode`  
_L44-70_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Auto unwrap UVs for a specific UV channel
- L52 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Target Collection
- L56 _private member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput))` — Faces to auto unwrap, no selection means all faces
- L60 _private member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "UVChannel", DataflowUVChannel, ClampMin = 0, ClampMax = 7, UIMin = 0, UIMax = 7))` — UV channel to unwrap into ( 0 by default )
- L64 _private member_ `int32 GutterSize = 1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1, UIMin = 1))` — Approximate space to leave between UV islands, measured in texels for 512x512 texture
- L66 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L69 _public prototype_ `FAutoUnwrapUVDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMergeUVIslandsDataflowNode`  
`struct FMergeUVIslandsDataflowNode : public FDataflowNode`  
_L76-112_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Merge adjacent UV Islands with similar normals for a specific UV channel
- L84 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Target Collection
- L88 _private member_ `FDataflowFaceSelection FaceSelection;` — `UPROPERTY(meta = (DataflowInput))` — Faces to auto unwrap, no selection means all faces
- L92 _private member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "UVChannel", DataflowUVChannel, ClampMin = 0, ClampMax = 7, UIMin = 0, UIMax = 7))` — UV channel to unwrap into ( 0 by default )
- L96 _private member_ `double AreaDistortionThreshold = 1.5;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, ClampMax = 10, UIMin = 0, UIMax = 10))` — Threshold for allowed area distortion from merging islands (when we use ExpMap to compute new UVs for the merged island)
- L99 _private member_ `double MaxNormalDeviationDeg = 45.0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 0, ClampMax = 180, UIMin = 0, UIMax = 90))` — Threshold for allowed normal deviation between merge-able islands
- L103 _private member_ `int32 NormalSmoothingRounds = 0;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput, ClampMin = 0, ClampMax = 500, UIMin = 0, UIMax = 100))` — Amount of normal smoothing to apply when computing new UVs for merged islands. More smoothing will result in UV maps that are less sensitive to local surface shape.
- L106 _private member_ `double NormalSmoothingAlpha = 0.25;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (DataflowInput, ClampMin = 0, ClampMax = 1, UIMin = 0, UIMax = 1))` — Strength of normal smoothing to apply when computing new UVs for merged islands. Stronger smoothing will result in UV maps that are less sensitive to local surface shape.
- L108 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L111 _public prototype_ `FMergeUVIslandsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FBoxProjectUVDataflowNode`  
`struct FBoxProjectUVDataflowNode : public FDataflowNode`  
_L118-159_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Generates UVs using a box projection
- L126 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Target Collection
- L134 _private member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "UVChannel", DataflowUVChannel, ClampMin = 0, ClampMax = 7, UIMin = 0, UIMax = 7))` — UV channel to unwrap into ( 0 by default )
- L138 _private member_ `int32 GutterSize = 1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput, ClampMin = 1, UIMin = 1))` — Approximate space to leave between UV islands, measured in texels for 512x512 texture
- L141 _private member_ `FVector ProjectionScale = { 100, 100, 100 };` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))`
- L144 _private member_ `FVector2f UVOffset = { 0.5, 0.5 };` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))`
- L147 _private member_ `bool bAutoFitToBounds = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))`
- L150 _private member_ `bool bCenterBoxAtPivot = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))`
- L153 _private member_ `bool bUniformProjectionScale = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))`
- L155 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L158 _public prototype_ `FBoxProjectUVDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L161 _namespace_ `namespace UE`
- L161 _namespace_ `namespace Dataflow` (scope `UE`)
- L163 _prototype_ `void RegisterGeometryCollectionUVNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionUtilityNodes.h` (Public)


#### enum `EConvexOverlapRemovalMethodEnum`  
`enum class EConvexOverlapRemovalMethodEnum : uint8`  
_L21-30_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `Dataflow_EConvexOverlapRemovalMethod_None UMETA(DisplayName = "None")`
- L24 _public enumerator_ `Dataflow_EConvexOverlapRemovalMethod_All UMETA(DisplayName = "All")`
- L25 _public enumerator_ `Dataflow_EConvexOverlapRemovalMethod_OnlyClusters UMETA(DisplayName = "Only Clusters")`
- L26 _public enumerator_ `Dataflow_EConvexOverlapRemovalMethod_OnlyClustersVsClusters UMETA(DisplayName = "Only Clusters vs Clusters")`
- L29 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### struct `FDataflowSphereCovering`  
`struct FDataflowSphereCovering`  
_L35-41_
- reflection: `USTRUCT()`
- desc: A set of spheres generated to represent empty space when creating a minimal set of convex hulls, e.g. in one of the Generate Cluster Convex Hulls nodes
- L40 _public member_ `UE::Geometry::FSphereCovering Spheres;`

#### struct `FDataflowConvexDecompositionSettings`  
`struct FDataflowConvexDecompositionSettings`  
_L45-91_
- reflection: `USTRUCT()`
- L52 _public member_ `float MinSizeToDecompose = 0.f;` — `UPROPERTY(EditAnywhere, Category = Filter, meta = (ClampMin = 0.0))` — If greater than zero, the minimum geometry size (cube root of volume) to consider for convex decomposition
- L56 _public member_ `float MaxGeoToHullVolumeRatioToDecompose = 1.f;` — `UPROPERTY(EditAnywhere, Category = Filter, meta = (ClampMin = 0.0, ClampMax = 1.0))` — If the geo volume / hull volume ratio is greater than this, do not consider convex decomposition
- L61 _public member_ `float ErrorTolerance = 0.f;` — `UPROPERTY(EditAnywhere, Category = Decomposition, meta = (ClampMin = 0.0, Units = cm, EditCondition = "!bProtectNegativeSpace"))` — Stop splitting when hulls have error less than this (expressed in cm; will be cubed for volumetric error). Note: Decomposition will only be performed if: bProtectNegativeSpace is true, ErrorTolerance is > 0, or MaxHullsPerGeometry > 1
- L66 _public member_ `int32 MaxHullsPerGeometry = -1;` — `UPROPERTY(EditAnywhere, Category = Decomposition, meta = (ClampMin = -1))` — If greater than zero, maximum number of convex hulls to use in each convex decomposition. Note: Decomposition will only be performed if: bProtectNegativeSpace is true, ErrorTolerance is > 0, or MaxHullsPerGeometry > 1
- L70 _public member_ `float MinThicknessTolerance = 0.f;` — `UPROPERTY(EditAnywhere, Category = Decomposition, meta = (ClampMin = 0.0))` — Optionally specify a minimum thickness (in cm) for convex parts; parts below this thickness will always be merged away. Overrides NumOutputHulls and ErrorTolerance when needed.
- L74 _public member_ `int32 NumAdditionalSplits = 4;` — `UPROPERTY(EditAnywhere, Category = Decomposition, meta = (ClampMin = 0, EditCondition = "!bProtectNegativeSpace"))` — Control the search effort spent per convex decomposition: larger values will require more computation but may find better convex decompositions
- L78 _public member_ `bool bProtectNegativeSpace = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace)` — Whether to drive decomposition by finding a negative space that should not be covered by convex hulls. If enabled, ErrorTolerance and NumAdditionalSplits will not be used.
- L82 _public member_ `bool bOnlyConnectedToHull = true;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace"))` — When protecting negative space, only look for space that is connected out to the convex hull. This removes inaccessable internal negative space from consideration.
- L86 _public member_ `float NegativeSpaceTolerance = 2.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (ClampMin = .01, UIMin = .1, Units = cm, EditCondition = "bProtectNegativeSpace"))` — Amount of space to leave between convex hulls and protected negative space
- L90 _public member_ `float NegativeSpaceMinRadius = 10.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (ClampMin = 0, Units = cm, EditCondition = "bProtectNegativeSpace"))` — Spheres smaller than this are not included in the negative space

#### struct `FMakeDataflowConvexDecompositionSettingsNode`  
`struct FMakeDataflowConvexDecompositionSettingsNode : public FDataflowNode`  
_L97-151_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Provide settings for running convex decomposition of geometry
- L105 _public member_ `float MinSizeToDecompose = 0.f;` — `UPROPERTY(EditAnywhere, Category = Filter, meta = (ClampMin = 0.0, DataflowInput))` — If greater than zero, the minimum geometry size (cube root of volume) to consider for convex decomposition
- L109 _public member_ `float MaxGeoToHullVolumeRatioToDecompose = 1.f;` — `UPROPERTY(EditAnywhere, Category = Filter, meta = (ClampMin = 0.0, ClampMax = 1.0, DataflowInput))` — If the geo volume / hull volume ratio is greater than this, do not consider convex decomposition
- L114 _public member_ `float ErrorTolerance = 0.f;` — `UPROPERTY(EditAnywhere, Category = Decomposition, meta = (ClampMin = 0.0, Units = cm, DataflowInput, EditCondition = "!bProtectNegativeSpace"))` — Stop splitting when hulls have error less than this (expressed in cm; will be cubed for volumetric error). Note: Decomposition will only be performed if: bProtectNegativeSpace is true, ErrorTolerance is > 0, or MaxHullsPerGeometry > 1
- L119 _public member_ `int32 MaxHullsPerGeometry = -1;` — `UPROPERTY(EditAnywhere, Category = Decomposition, meta = (ClampMin = -1, DataflowInput))` — If greater than zero, maximum number of convex hulls to use in each convex decomposition. Note: Decomposition will only be performed if: bProtectNegativeSpace is true, ErrorTolerance is > 0, or MaxHullsPerGeometry > 1
- L123 _public member_ `float MinThicknessTolerance = 0.f;` — `UPROPERTY(EditAnywhere, Category = Decomposition, meta = (ClampMin = 0.0, DataflowInput))` — Optionally specify a minimum thickness (in cm) for convex parts; parts below this thickness will always be merged away. Overrides NumOutputHulls and ErrorTolerance when needed.
- L127 _public member_ `int32 NumAdditionalSplits = 4;` — `UPROPERTY(EditAnywhere, Category = Decomposition, meta = (ClampMin = 0, DataflowInput, EditCondition = "!bProtectNegativeSpace"))` — Control the search effort spent per convex decomposition: larger values will require more computation but may find better convex decompositions
- L131 _public member_ `bool bProtectNegativeSpace = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput))` — Whether to drive decomposition by finding a negative space that should not be covered by convex hulls. If enabled, ErrorTolerance and NumAdditionalSplits will not be used.
- L135 _public member_ `bool bOnlyConnectedToHull = true;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, EditCondition = "bProtectNegativeSpace"))` — When protecting negative space, only look for space that is connected out to the convex hull. This removes inaccessable internal negative space from consideration.
- L139 _public member_ `float NegativeSpaceTolerance = 2.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = .01, UIMin = .1, Units = cm, EditCondition = "bProtectNegativeSpace"))` — Amount of space to leave between convex hulls and protected negative space
- L143 _public member_ `float NegativeSpaceMinRadius = 10.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm, EditCondition = "bProtectNegativeSpace"))` — Spheres smaller than this are not included in the negative space
- L146 _public member_ `FDataflowConvexDecompositionSettings DecompositionSettings;` — `UPROPERTY(meta = (DataflowOutput))`
- L148 _public prototype_ `FMakeDataflowConvexDecompositionSettingsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L150 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCreateLeafConvexHullsDataflowNode`  
`struct FCreateLeafConvexHullsDataflowNode : public FDataflowNode`  
_L154-223_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L161 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput))`
- L164 _private member_ `FDataflowSphereCovering SphereCovering;` — `UPROPERTY(meta = (DataflowOutput))`
- L168 _private member_ `FDataflowTransformSelection OptionalSelectionFilter;` — `UPROPERTY(meta = (DataflowInput))` — Optional transform selection to compute leaf hulls on -- if not provided, all leaf hulls will be computed.
- L172 _private member_ `EGenerateConvexMethod GenerateMethod = EGenerateConvexMethod::ComputedFromGeometry;` — `UPROPERTY(EditAnywhere, Category = Options)` — How convex hulls are generated -- computed from geometry, imported from external collision shapes, or an intersection of both options.
- L176 _private member_ `float IntersectIfComputedIsSmallerByFactor = 1.0f;` — `UPROPERTY(EditAnywhere, Category = IntersectionFilters, meta = (ClampMin = 0.0, ClampMax = 1.0, EditCondition = "GenerateMethod == EGenerateConvexMethod::IntersectExternalWithComputed"))` — If GenerateMethod is Intersect, only actually intersect when the volume of the Computed Hull is less than this fraction of the volume of the External Hull(s).
- L180 _private member_ `float MinExternalVolumeToIntersect = 0.0f;` — `UPROPERTY(EditAnywhere, Category = IntersectionFilters, meta = (ClampMin = 0.0, EditCondition = "GenerateMethod == EGenerateConvexMethod::IntersectExternalWithComputed"))` — If GenerateMethod is Intersect, only actually intersect if the volume of the External Hull(s) exceed this threshold.
- L184 _private member_ `bool bComputeIntersectionsBeforeHull = true;` — `UPROPERTY(EditAnywhere, Category = Convex, meta = (EditCondition = "GenerateMethod == EGenerateConvexMethod::IntersectExternalWithComputed"))` — Whether to compute the intersection before computing convex hulls. Typically should be enabled.
- L188 _private member_ `float SimplificationDistanceThreshold = 10.f;` — `UPROPERTY(EditAnywhere, Category = Convex, meta = (DataflowInput, ClampMin = 0.f, EditCondition = "GenerateMethod != EGenerateConvexMethod::ExternalCollision"))` — Computed convex hulls are simplified to keep points spaced at least this far apart (except where needed to keep the hull from collapsing to zero volume).
- L191 _private member_ `FDataflowConvexDecompositionSettings ConvexDecompositionSettings;` — `UPROPERTY(EditAnywhere, Category = Convex, meta = (DataflowInput))`
- L195 _private member_ `FDataflowSphereCovering RequireNegativeSpaceCovering;` — `UPROPERTY(meta = (DataflowInput))` — Negative space that must be used. Applies in addition to any automatically-detected covering added via ConvexDecompositionSettings.
- L198 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L202 _private member_ `bool bRandomizeColor = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Randomize color per convex hull
- L206 _private member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0", EditCondition = "bRandomizeColor==true", EditConditionHides))` — Random seed
- L209 _private member_ `FDataflowNodeSphereCoveringDebugDrawSettings SphereCoveringDebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (ShowOnlyInnerProperties))`
- L211 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L213 _private function_ `virtual bool CanDebugDraw() const override`
- L217 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L218 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L222 _public prototype_ `FCreateLeafConvexHullsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### enum `EPrimitiveCollisionShapeDataflowEnum`  
`enum class EPrimitiveCollisionShapeDataflowEnum : uint8`  
_L226-231_
- reflection: `UENUM()`
- L228 _public enumerator_ `Sphere`
- L229 _public enumerator_ `Box`
- L230 _public enumerator_ `Capsule`

#### struct `FSetExternalCollisionsFromPrimitiveDataflowNode`  
`struct FSetExternalCollisionsFromPrimitiveDataflowNode : public FDataflowNode`  
_L245-289_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection, Experimental))`
- inherits: `FDataflowNode`
- desc: Sets the ExternalCollisions attribute on each selected transform to a primitive shape (sphere / box / capsule) auto-fitted to that bone's geometry bounds. Any existing ExternalCollisions entry on the selected transforms is REPLACED. Shapes written here flow through the same runtime path used by static-mesh-imported primitive collisions: the GeometryCollection asset must have bImportCollisionFromSource enabled for the simulation to consume them. Empty/unconnected selection authors the shape on all rigid-leaf transforms.
- L252 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L256 _private member_ `FDataflowTransformSelection OptionalSelectionFilter;` — `UPROPERTY(meta = (DataflowInput))` — Transforms to author the shape on. If unconnected or empty, all rigid-leaf transforms are used.
- L260 _private member_ `EPrimitiveCollisionShapeDataflowEnum Shape = EPrimitiveCollisionShapeDataflowEnum::Box;` — `UPROPERTY(EditAnywhere, Category = "Shape")` — Which primitive shape to author. Size is fitted automatically to each bone's geometry bounds.
- L264 _private member_ `float Scale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Shape", meta = (DataflowInput, ClampMin = "0.01"))` — Uniform multiplier applied to the auto-fitted shape extents. 1.0 = exact AABB fit; >1 pads out, <1 shrinks.
- L269 _private member_ `bool bAlignToPrincipalAxis = true;` — `UPROPERTY(EditAnywhere, Category = "Shape", meta = ( EditCondition = "Shape != EPrimitiveCollisionShapeDataflowEnum::Sphere", EditConditionHides))` — For Box and Capsule: orient the shape along the bone geometry's principal axes (PCA over vertices) for a tighter fit. Off = axis-aligned (AABB) fit. No effect on Sphere (rotation-invariant).
- L272 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L274 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L277 _private function_ `virtual bool CanDebugDraw() const override`
- L281 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L282 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L285 _private prototype_ `void GetBoneSelection(UE::Dataflow::FContext& Context, const FManagedArrayCollection& InCollection, TArray<int32>& OutSelection) const;`
- L288 _public prototype_ `FSetExternalCollisionsFromPrimitiveDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FSimplifyConvexHullsDataflowNode`  
`struct FSimplifyConvexHullsDataflowNode : public FDataflowNode`  
_L292-346_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L299 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput))`
- L303 _private member_ `FDataflowTransformSelection OptionalSelectionFilter;` — `UPROPERTY(meta = (DataflowInput))` — Optional transform selection to compute leaf hulls on -- if not provided, all leaf hulls will be computed.
- L306 _private member_ `EConvexHullSimplifyMethod SimplifyMethod = EConvexHullSimplifyMethod::MeshQSlim;` — `UPROPERTY(EditAnywhere, Category = "Convex")`
- L310 _private member_ `float SimplificationAngleThreshold = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput, ClampMin = 0.f, EditCondition = "SimplifyMethod == EConvexHullSimplifyMethod::AngleTolerance"))` — Simplified hull should preserve angles larger than this (in degrees).  Used by the AngleTolerance simplification method.
- L314 _private member_ `float SimplificationDistanceThreshold = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput, ClampMin = 0.f, EditCondition = "SimplifyMethod == EConvexHullSimplifyMethod::MeshQSlim"))` — Simplified hull should stay within this distance of the initial convex hull. Used by the MeshQSlim simplification method.
- L318 _private member_ `int32 MinTargetTriangleCount = 12;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DisplayName = "Min Target Face Count", DataflowInput, ClampMin = 4))` — The minimum number of faces to use for the convex hull. For MeshQSlim simplification, this is a triangle count, which may be further reduced on conversion back to a convex hull.
- L322 _private member_ `bool bUseExistingVertices = false;` — `UPROPERTY(EditAnywhere, Category = "Convex")` — Whether to restrict the simplified hulls to only use vertices from the original hulls.
- L325 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L329 _private member_ `bool bRandomizeColor = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Randomize color per convex hull
- L333 _private member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0" , EditCondition = "bRandomizeColor==true", EditConditionHides))` — Random seed
- L335 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L337 _private function_ `virtual bool CanDebugDraw() const override`
- L341 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L342 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L345 _public prototype_ `FSimplifyConvexHullsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FCreateNonOverlappingConvexHullsDataflowNode`  
`struct FCreateNonOverlappingConvexHullsDataflowNode : public FDataflowNode`  
_L354-405_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Generates convex hull representation for the bones for simulation
- L361 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput))`
- L365 _private member_ `float CanExceedFraction = .5f;` — `UPROPERTY(EditAnywhere, Category = Convex, meta = (DataflowInput, DisplayName = "Allow Larger Hull Fraction", ClampMin = 0.f))` — Fraction (of geometry volume) by which a cluster's convex hull volume can exceed the actual geometry volume before instead using the hulls of the children.  0 means the convex volume cannot exceed the geometry volume; 1 means the convex volume is allowed to be 100% larger (2x) the geometry volume.
- L369 _private member_ `float SimplificationDistanceThreshold = 10.f;` — `UPROPERTY(EditAnywhere, Category = Convex, meta = (DataflowInput, ClampMin = 0.f))` — Computed convex hulls are simplified to keep points spaced at least this far apart (except where needed to keep the hull from collapsing to zero volume)
- L373 _private member_ `EConvexOverlapRemovalMethodEnum OverlapRemovalMethod = EConvexOverlapRemovalMethodEnum::Dataflow_EConvexOverlapRemovalMethod_All;` — `UPROPERTY(EditAnywhere, Category = AutomaticOverlapRemoval, meta = (DisplayName = "Remove Overlaps"))` — Whether and in what cases to automatically cut away overlapping parts of the convex hulls, to avoid the simulation 'popping' to fix the overlaps
- L377 _private member_ `float OverlapRemovalShrinkPercent = 0.f;` — `UPROPERTY(EditAnywhere, Category = AutomaticOverlapRemoval, meta = (DataflowInput, ClampMin = 0.f, ClampMax = 99.9f))` — Overlap removal will be computed as if convex hulls were this percentage smaller (in range 0-100)
- L381 _private member_ `float CanRemoveFraction = 0.3f;` — `UPROPERTY(EditAnywhere, Category = AutomaticOverlapRemoval, meta = (DataflowInput, DisplayName = "Max Removal Fraction", ClampMin = 0.01f, ClampMax = 1.f))` — Fraction of the convex hulls for a cluster that we can remove before using the hulls of the children
- L384 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L388 _private member_ `bool bRandomizeColor = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Randomize color per convex hull
- L392 _private member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0", EditCondition = "bRandomizeColor==true", EditConditionHides))` — Random seed
- L394 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L396 _private function_ `virtual bool CanDebugDraw() const override`
- L400 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L401 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L404 _public prototype_ `FCreateNonOverlappingConvexHullsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### enum `ENegativeSpaceSampleMethodDataflowEnum`  
`enum class ENegativeSpaceSampleMethodDataflowEnum : uint8`  
_L411-419_
- reflection: `UENUM()`
- desc: Method to distribute sampling spheres
- L414 _public enumerator_ `Uniform` — Place sample spheres in a uniform grid pattern
- L416 _public enumerator_ `VoxelSearch` — Use voxel-based subtraction and offsetting methods to specifically target concavities
- L418 _public enumerator_ `NavigableVoxelSearch` — Use a variant of VoxelSearch that aims to limit negative space to the space that can be accessed by a ball of radius >= MinRadius

#### struct `FCreateNegativeSpaceSphereCovering`  
`struct FCreateNegativeSpaceSphereCovering : public FDataflowNode`  
_L427-488_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Generates a negative space sphere covering for a given geometry collection or subset of bones in the collection
- L434 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))`
- L437 _private member_ `FDataflowSphereCovering SphereCovering;` — `UPROPERTY(meta = (DataflowOutput))`
- L441 _private member_ `FDataflowTransformSelection OptionalSelectionFilter;` — `UPROPERTY(meta = (DataflowInput))` — Optional transform selection -- if not provided, covering for all leaf geometry will be computed.
- L446 _private member_ `ENegativeSpaceSampleMethodDataflowEnum SampleMethod = ENegativeSpaceSampleMethodDataflowEnum::NavigableVoxelSearch;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace)` — Method to use to find and sample negative space
- L450 _private member_ `bool bRequireSearchSampleCoverage = true;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "SampleMethod != ENegativeSpaceSampleMethodDataflowEnum::Uniform"))` — Whether to require that all candidate locations identified by Voxel Search are covered by negative space samples, up to the specified Min Sample Spacing. Only applies to Voxel Search.
- L454 _private member_ `bool bOnlyConnectedToHull = true;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "SampleMethod != ENegativeSpaceSampleMethodDataflowEnum::Uniform"))` — When performing Voxel Search, only look for negative space that is connected out to the convex hull. This removes inaccessable internal negative space from consideration. Only applies to Voxel Search.
- L458 _private member_ `int32 TargetNumSamples = 50;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 1, EditCondition = "SampleMethod == ENegativeSpaceSampleMethodDataflowEnum::Uniform || !bRequireSearchSampleCoverage"))` — Approximate number of spheres to consider when covering negative space. Only applicable with the Uniform Sample Method or if Require Search Sample Coverage is disabled.
- L462 _private member_ `double MinSampleSpacing = 0.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm))` — Minimum desired spacing between spheres; if > 0, will attempt not to place sphere centers closer than this
- L466 _private member_ `double NegativeSpaceTolerance = 2.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = .01, UIMin = .1, Units = cm))` — Amount of space to leave between input geometry and protected negative space
- L470 _private member_ `double MinRadius = 10.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm))` — Spheres smaller than this are not included in the negative space
- L473 _private member_ `FDataflowNodeSphereCoveringDebugDrawSettings SphereCoveringDebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (ShowOnlyInnerProperties))`
- L476 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L478 _private function_ `virtual bool CanDebugDraw() const override`
- L482 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L483 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L487 _public prototype_ `FCreateNegativeSpaceSphereCovering(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGenerateClusterConvexHullsFromLeafHullsDataflowNode`  
`struct FGenerateClusterConvexHullsFromLeafHullsDataflowNode : public FDataflowNode`  
_L496-609_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Generates cluster convex hulls for leafs hulls
- L503 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput))`
- L507 _private member_ `FDataflowSphereCovering SphereCovering;` — `UPROPERTY(meta = (DataflowOutput))` — A representation of the negative space protected by the 'protect negative space' option. If negative space is not protected, this will contain zero spheres.
- L511 _private member_ `int32 ConvexCount = 2;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput, EditCondition = "ErrorTolerance == 0"))` — Maximum number of convex to generate for a specific cluster. Will be ignored if error tolerance is used instead
- L519 _private member_ `double ErrorTolerance = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput, UIMin = "0", UIMax = "100.", Units = cm))` — Error tolerance to use to decide to merge leaf convex together. This is in centimeters and represents the side of a cube, the volume of which will be used as threshold to know if the volume of the generated convex is too large compared to the sum of the volume of the leaf convex
- L523 _private member_ `bool bPreferExternalCollisionShapes = true;` — `UPROPERTY(EditAnywhere, Category = "Convex")` — Whether to prefer available External (imported) collision shapes instead of the computed convex hulls on the Collection
- L527 _private member_ `EAllowConvexMergeMethod AllowMerges = EAllowConvexMergeMethod::ByProximity;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DisplayName = "Allow Merges Between Bones"))` — Method to determine if the convex hulls from two separate bones can potentially be merged
- L531 _private member_ `EConvexHullProximityFilter MergeProximityFilter = EConvexHullProximityFilter::None;` — `UPROPERTY(EditAnywhere, Category = "Convex")` — Filter to optionally only consider spatially close convex hulls for merges
- L535 _private member_ `float MergeProximityDistanceThreshold = .1f;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (Units = cm, EditCondition = "MergeProximityFilter != EConvexHullProximityFilter::None"))` — If applying a convex hull proximity filter, the distance threshold to use for determining that two convex hulls are close enough to merge
- L539 _private member_ `FDataflowTransformSelection OptionalSelectionFilter;` — `UPROPERTY(meta = (DataflowInput))` — Optional transform selection to compute cluster hulls on -- if not provided, all cluster hulls will be computed.
- L543 _private member_ `bool bAllowMergingLeafHulls = false;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput))` — Also allow the same hull merging process to run on leaf hulls (merging hulls on leaves in the selection)
- L547 _private member_ `FDataflowSphereCovering RequireNegativeSpaceCovering;` — `UPROPERTY(meta = (DataflowInput))` — Negative space that must be used. Applies in addition to any automatically-detected covering added via bProtectNegativeSpace.
- L551 _private member_ `bool bProtectNegativeSpace = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput))` — Whether to generate a sphere cover to define negative space that should not be covered by convex hulls
- L555 _private member_ `ENegativeSpaceSampleMethodDataflowEnum SampleMethod = ENegativeSpaceSampleMethodDataflowEnum::Uniform;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Method to use to find and sample negative space
- L559 _private member_ `bool bRequireSearchSampleCoverage = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace && SampleMethod != ENegativeSpaceSampleMethodDataflowEnum::Uniform", EditConditionHides))` — Whether to require that all candidate locations identified by Voxel Search are covered by negative space samples, up to the specified Min Sample Spacing. Only applies to Voxel Search.
- L563 _private member_ `bool bOnlyConnectedToHull = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace && SampleMethod != ENegativeSpaceSampleMethodDataflowEnum::Uniform", EditConditionHides))` — When performing Voxel Search, only look for negative space that is connected out to the convex hull. This removes inaccessable internal negative space from consideration. Only applies to Voxel Search.
- L567 _private member_ `int32 TargetNumSamples = 50;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 1, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Approximate number of spheres to consider when covering negative space. Only applicable with the Uniform Sample Method or if Require Search Sample Coverage is disabled.
- L571 _private member_ `double MinSampleSpacing = 1.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Minimum desired spacing between spheres; if > 0, will attempt not to place sphere centers closer than this
- L575 _private member_ `double NegativeSpaceTolerance = 2.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = .01, UIMin = .1, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Amount of space to leave between convex hulls and protected negative space
- L579 _private member_ `double MinRadius = 10.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Spheres smaller than this are not included in the negative space
- L582 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L586 _private member_ `bool bRandomizeColor = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Randomize color per convex hull
- L590 _private member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0", EditCondition = "bRandomizeColor==true", EditConditionHides))` — Random seed
- L593 _private member_ `FDataflowNodeSphereCoveringDebugDrawSettings SphereCoveringDebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (ShowOnlyInnerProperties))`
- L595 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L597 _private function_ `virtual bool CanDebugDraw() const override`
- L601 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L602 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L606 _public prototype_ `FGenerateClusterConvexHullsFromLeafHullsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FGenerateClusterConvexHullsFromChildrenHullsDataflowNode`  
`struct FGenerateClusterConvexHullsFromChildrenHullsDataflowNode : public FDataflowNode`  
_L617-726_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Generates cluster convex hulls for children hulls
- L624 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput))`
- L628 _private member_ `FDataflowSphereCovering SphereCovering;` — `UPROPERTY(meta = (DataflowOutput))` — A representation of the negative space protected by the 'protect negative space' option. If negative space is not protected, this will contain zero spheres.
- L632 _private member_ `int32 ConvexCount = 2;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput, EditCondition = "ErrorTolerance == 0"))` — Maximum number of convex to generate for a specific cluster. Will be ignored if error tolerance is used instead
- L640 _private member_ `double ErrorTolerance = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput, UIMin = "0", UIMax = "100.", Units = cm))` — Error tolerance to use to decide to merge leaf convex together. This is in centimeters and represents the side of a cube, the volume of which will be used as threshold to know if the volume of the generated convex is too large compared to the sum of the volume of the leaf convex
- L644 _private member_ `bool bPreferExternalCollisionShapes = true;` — `UPROPERTY(EditAnywhere, Category = "Convex")` — Whether to prefer available External (imported) collision shapes instead of the computed convex hulls on the Collection
- L648 _private member_ `FDataflowTransformSelection OptionalSelectionFilter;` — `UPROPERTY(meta = (DataflowInput))` — Optional transform selection to compute cluster hulls on -- if not provided, all cluster hulls will be computed.
- L652 _private member_ `EConvexHullProximityFilter MergeProximityFilter = EConvexHullProximityFilter::None;` — `UPROPERTY(EditAnywhere, Category = "Convex")` — Filter to optionally only consider spatially close convex hulls for merges
- L656 _private member_ `float MergeProximityDistanceThreshold = .1f;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (Units = cm, EditCondition = "MergeProximityFilter != EConvexHullProximityFilter::None"))` — If applying a convex hull proximity filter, the distance threshold to use for determining that two convex hulls are close enough to merge
- L660 _private member_ `bool bAllowMergingLeafHulls = false;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput))` — Also allow the same hull merging process to run on leaf hulls (merging hulls on leaves in the selection)
- L664 _private member_ `FDataflowSphereCovering RequireNegativeSpaceCovering;` — `UPROPERTY(meta = (DataflowInput))` — Negative space that must be used. Applies in addition to any automatically-detected covering added via bProtectNegativeSpace.
- L668 _private member_ `bool bProtectNegativeSpace = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput))` — Whether to generate a sphere cover to define negative space that should not be covered by convex hulls
- L672 _private member_ `ENegativeSpaceSampleMethodDataflowEnum SampleMethod = ENegativeSpaceSampleMethodDataflowEnum::Uniform;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Method to use to find and sample negative space
- L676 _private member_ `bool bRequireSearchSampleCoverage = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace && SampleMethod != ENegativeSpaceSampleMethodDataflowEnum::Uniform", EditConditionHides))` — Whether to require that all candidate locations identified by Voxel Search are covered by negative space samples, up to the specified Min Sample Spacing. Only applies to Voxel Search.
- L680 _private member_ `bool bOnlyConnectedToHull = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace && SampleMethod != ENegativeSpaceSampleMethodDataflowEnum::Uniform", EditConditionHides))` — When performing Voxel Search, only look for negative space that is connected out to the convex hull. This removes inaccessable internal negative space from consideration. Only applies to Voxel Search.
- L684 _private member_ `int32 TargetNumSamples = 50;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 1, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Approximate number of spheres to consider when covering negative space. Only applicable with the Uniform Sample Method or if Require Search Sample Coverage is disabled.
- L688 _private member_ `double MinSampleSpacing = 1.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Minimum desired spacing between spheres; if > 0, will attempt not to place sphere centers closer than this
- L692 _private member_ `double NegativeSpaceTolerance = 2.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = .01, UIMin = .1, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Amount of space to leave between convex hulls and protected negative space
- L696 _private member_ `double MinRadius = 10.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Spheres smaller than this are not included in the negative space
- L699 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L703 _private member_ `bool bRandomizeColor = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Randomize color per convex hull
- L707 _private member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0", EditCondition = "bRandomizeColor==true", EditConditionHides))` — Random seed
- L710 _private member_ `FDataflowNodeSphereCoveringDebugDrawSettings SphereCoveringDebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (ShowOnlyInnerProperties))`
- L712 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L714 _private function_ `virtual bool CanDebugDraw() const override`
- L718 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L719 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L723 _public prototype_ `FGenerateClusterConvexHullsFromChildrenHullsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FClearConvexHullsDataflowNode`  
`struct FClearConvexHullsDataflowNode : public FDataflowNode`  
_L731-754_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Clear convex hulls from a collection
- L738 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))`
- L742 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput))` — [Optional] selection of transforms to clear convex on, if not set all the transform will be used
- L744 _public function_ `FClearConvexHullsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L753 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FCopyConvexHullsFromRootDataflowNode`  
`struct FCopyConvexHullsFromRootDataflowNode : public FDataflowNode`  
_L759-799_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Copy convex hulls from given transforms on a source collection to transforms on the target collection
- L765 _public prototype_ `FCopyConvexHullsFromRootDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L769 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))`
- L772 _private member_ `FManagedArrayCollection FromCollection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))`
- L776 _private member_ `bool bSkipIfEmpty = true;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DataflowInput))` — Whether to skip copying from roots with no convex hulls
- L779 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L783 _private member_ `bool bRandomizeColor = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Randomize color per convex hull
- L787 _private member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0"))` — Random seed
- L789 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L791 _private function_ `virtual bool CanDebugDraw() const override`
- L795 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L796 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`

#### struct `FMergeConvexHullsDataflowNode`  
`struct FMergeConvexHullsDataflowNode : public FDataflowNode`  
_L804-906_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Merge convex hulls on transforms with multiple hulls
- L811 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput))`
- L815 _private member_ `FDataflowSphereCovering SphereCovering;` — `UPROPERTY(meta = (DataflowOutput))` — A representation of the negative space protected by the 'protect negative space' option. If negative space is not protected, this will contain zero spheres.
- L819 _private member_ `int32 MaxConvexCount = -1;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput))` — Maximum number of convex to generate per transform. Ignored if < 0.
- L827 _private member_ `double ErrorTolerance = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (DataflowInput, ClampMin = "0", UIMax = "100.", Units = cm))` — Error tolerance to use to decide to merge leaf convex together. This is in centimeters and represents the side of a cube, the volume of which will be used as threshold to know if the volume of the generated convex is too large compared to the sum of the volume of the leaf convex
- L831 _private member_ `FDataflowTransformSelection OptionalSelectionFilter;` — `UPROPERTY(meta = (DataflowInput))` — Optional transform selection to compute cluster hulls on -- if not provided, all cluster hulls will be computed.
- L835 _private member_ `EConvexHullProximityFilter MergeProximityFilter = EConvexHullProximityFilter::None;` — `UPROPERTY(EditAnywhere, Category = "Convex")` — Filter to optionally only consider spatially close convex hulls for merges
- L839 _private member_ `float MergeProximityDistanceThreshold = .1f;` — `UPROPERTY(EditAnywhere, Category = "Convex", meta = (Units = cm, EditCondition = "MergeProximityFilter != EConvexHullProximityFilter::None"))` — If applying a convex hull proximity filter, the distance threshold to use for determining that two convex hulls are close enough to merge
- L843 _private member_ `FDataflowSphereCovering RequireNegativeSpaceCovering;` — `UPROPERTY(meta = (DataflowInput))` — Negative space that must be used. Applies in addition to any automatically-detected covering added via bProtectNegativeSpace.
- L847 _private member_ `bool bProtectNegativeSpace = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput))` — Whether to generate a sphere cover to define negative space that should not be covered by convex hulls
- L851 _private member_ `bool bComputeNegativeSpacePerBone = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Whether to compute separate negative space for each bone. Otherwise, a single negative space will be computed once and re-used for all bones.
- L855 _private member_ `ENegativeSpaceSampleMethodDataflowEnum SampleMethod = ENegativeSpaceSampleMethodDataflowEnum::Uniform;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Method to use to find and sample negative space
- L859 _private member_ `bool bRequireSearchSampleCoverage = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace && SampleMethod != ENegativeSpaceSampleMethodDataflowEnum::Uniform", EditConditionHides))` — Whether to require that all candidate locations identified by Voxel Search are covered by negative space samples, up to the specified Min Sample Spacing. Only applies to Voxel Search.
- L863 _private member_ `bool bOnlyConnectedToHull = false;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (EditCondition = "bProtectNegativeSpace && SampleMethod != ENegativeSpaceSampleMethodDataflowEnum::Uniform", EditConditionHides))` — When performing Voxel Search, only look for negative space that is connected out to the convex hull. This removes inaccessable internal negative space from consideration. Only applies to Voxel Search.
- L867 _private member_ `int32 TargetNumSamples = 50;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 1, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Approximate number of spheres to consider when covering negative space. Only applicable with the Uniform Sample Method or if Require Search Sample Coverage is disabled.
- L871 _private member_ `double MinSampleSpacing = 1.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Minimum desired spacing between spheres; if > 0, will attempt not to place sphere centers closer than this
- L875 _private member_ `double NegativeSpaceTolerance = 2.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = .01, UIMin = .1, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Amount of space to leave between convex hulls and protected negative space
- L879 _private member_ `double MinRadius = 10.0;` — `UPROPERTY(EditAnywhere, Category = NegativeSpace, meta = (DataflowInput, ClampMin = 0, Units = cm, EditCondition = "bProtectNegativeSpace", EditConditionHides))` — Spheres smaller than this are not included in the negative space
- L882 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L886 _private member_ `bool bRandomizeColor = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Randomize color per convex hull
- L890 _private member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0", EditCondition = "bRandomizeColor==true", EditConditionHides))` — Random seed
- L893 _private member_ `FDataflowNodeSphereCoveringDebugDrawSettings SphereCoveringDebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Sphere Covering", meta = (ShowOnlyInnerProperties))`
- L895 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L897 _private function_ `virtual bool CanDebugDraw() const override`
- L901 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L902 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L905 _public prototype_ `FMergeConvexHullsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FUpdateVolumeAttributesDataflowNode`  
`struct FUpdateVolumeAttributesDataflowNode : public FDataflowNode`  
_L915-927_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Update the Volume and Size attributes on the target Collection (and add them if they were not present)
- L922 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection, DataflowIntrinsic))`
- L924 _public prototype_ `FUpdateVolumeAttributesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L926 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FComputeVolumeStatsDataflowNode`  
`struct FComputeVolumeStatsDataflowNode : public FDataflowNode`  
_L933-972_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Compute information about the volume of a collection specific transform or root
- L939 _public prototype_ `FComputeVolumeStatsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L944 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = Collection, DataflowIntrinsic))` — Collection to collect the stats from
- L948 _private member_ `int32 TransformIndex = INDEX_NONE;` — `UPROPERTY(meta = (DataflowInput))` — Selection to consider , if set to -1 or not a valid transform in the collection, the root will be considered
- L952 _private member_ `float GeometryVolume = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Volume of the geometry in cm3
- L956 _private member_ `float ConvexVolume = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Volume of the single wrapping convex around the geometry in cm3
- L960 _private member_ `float VolumeRatio = 1.0f;` — `UPROPERTY(meta = (DataflowOutput))` — Ratio of the geometry volume in relation to the wrapping convex volume ( GeometryVolume / ConvexVolume )
- L964 _private member_ `float VolumePercentage = 100.f;` — `UPROPERTY(meta = (DataflowOutput))` — Percentage of the geometry volume in relation to the wrapping convex volume ( GeometryVolume / ConvexVolume * 100 )
- L968 _private member_ `float EmptySpaceCubeSize = 100.f;` — `UPROPERTY(meta = (DataflowOutput))` — Cube size of the empty space volume (cubic root of the volume = Edge size of a cube of similar volume)
- L971 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FGetConvexHullVolumeDataflowNode`  
`struct FGetConvexHullVolumeDataflowNode : public FDataflowNode`  
_L978-1025_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Get the sum of volumes of the convex hulls on the selected nodes
- L985 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput))`
- L989 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — The transforms to consider
- L993 _private member_ `float Volume = 0.f;` — `UPROPERTY(meta = (DataflowOutput))` — Sum of convex hull volumes
- L997 _private member_ `bool bSumChildrenForClustersWithoutHulls = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — For any cluster transform that has no convex hulls, whether to fall back to the convex hulls of the cluster's children. Otherwise, the cluster will not add to the total volume sum.
- L1001 _private member_ `bool bVolumeOfUnion = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to take the volume of the union of selected hulls, rather than the sum of each hull volume separately. This is more expensive but more accurate when hulls overlap.
- L1004 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ShowOnlyInnerProperties))`
- L1008 _private member_ `bool bRandomizeColor = true;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Randomize color per convex hull
- L1012 _private member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", meta = (ClampMin = "0", EditCondition = "bRandomizeColor==true", EditConditionHides))` — Random seed
- L1014 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1016 _private function_ `virtual bool CanDebugDraw() const override`
- L1020 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L1021 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L1024 _public prototype_ `FGetConvexHullVolumeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FFixTinyGeoDataflowNode`  
`struct FFixTinyGeoDataflowNode : public FDataflowNode`  
_L1034-1125_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Utilities / TinyGeo tool Merge pieces of geometry onto their neighbors -- use it to, for example, clean up too small pieces of geometry.
- L1042 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to use
- L1046 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — The selected pieces to use
- L1050 _public member_ `EFixTinyGeoMergeType MergeType = EFixTinyGeoMergeType::MergeGeometry;` — `UPROPERTY(EditAnywhere, Category = Distribution)` — Whether to merge small geometry, or small clusters
- L1054 _public member_ `bool bOnFractureLevel = true;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (EditCondition = "!bFractureLevelIsAll && MergeType == EFixTinyGeoMergeType::MergeClusters", EditConditionHides))` — Only consider bones at the current Fracture Level
- L1058 _public member_ `bool bOnlyClusters = false;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (EditCondition = "!bFractureLevelIsAll && MergeType == EFixTinyGeoMergeType::MergeClusters && bOnFractureLevel", EditConditionHides))` — Only auto-consider clusters for merging. Note that leaf nodes can still be consider if manually selected.
- L1062 _public member_ `bool bOnlySameParent = true;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (DisplayName = "Only Merge Clusters w/ Same Parent", EditCondition = "MergeType == EFixTinyGeoMergeType::MergeClusters", EditConditionHides))` — Only merge clusters to neighbors with the same parent in the hierarchy
- L1066 _public member_ `bool bGeometryOnlySameParent = false;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (DisplayName = "Only Merge Geometry w/ Same Parent", EditCondition = "MergeType == EFixTinyGeoMergeType::MergeGeometry", EditConditionHides))` — Only merge geometry to neighbors with the same parent in the hierarchy
- L1070 _public member_ `bool bFractureLevelIsAll = false;` — `UPROPERTY()` — Helper variable to let the EditConditions above check whether the Fracture Level is set to 'All'
- L1073 _public member_ `EFixTinyGeoNeighborSelectionMethod NeighborSelection = EFixTinyGeoNeighborSelectionMethod::LargestNeighbor;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (DisplayName = "Merge To"))`
- L1077 _public member_ `bool bOnlyToConnected = true;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (EditCondition = "MergeType == EFixTinyGeoMergeType::MergeClusters", EditConditionHides))` — Only merge pieces that are connected in the proximity graph.If unchecked, connected pieces will still be favored, but if none are available the closest disconnected piece can be merged.
- L1081 _public member_ `bool bUseCollectionProximityForConnections = false;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, AdvancedDisplay)` — Whether to use the Proximity (as computed by the Proximity node) to determine which bones are connected, and thus can be considered for merging. Otherwise will compute and use a reasonable default connectivity.
- L1085 _public member_ `EFixTinyGeoUseBoneSelection UseBoneSelection = EFixTinyGeoUseBoneSelection::NoEffect;` — `UPROPERTY(EditAnywhere, Category = MergeSettings, meta = (DisplayName = "Bone Selection"))` — Options for using the current bone selection
- L1088 _public member_ `EFixTinyGeoGeometrySelectionMethod SelectionMethod = EFixTinyGeoGeometrySelectionMethod::RelativeVolume;` — `UPROPERTY(EditAnywhere, Category = FilterSettings)`
- L1092 _public member_ `float MinVolumeCubeRoot = 1.f;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (DisplayName = "MinSize", ClampMin = ".00001", UIMin = ".1", UIMax = "10", EditCondition = "SelectionMethod == EFixTinyGeoGeometrySelectionMethod::VolumeCubeRoot", EditConditionHides))` — If size (cube root of volume) is less than this value, geometry should be merged into neighbors -- i.e. a value of 2 merges geometry smaller than a 2x2x2 cube
- L1097 _public member_ `float RelativeVolume = .01f;` — `UPROPERTY(EditAnywhere, Category = FilterSettings, meta = (ClampMin = "0", UIMax = ".1", ClampMax = "1.0", EditCondition = "SelectionMethod == EFixTinyGeoGeometrySelectionMethod::RelativeVolume", EditConditionHides))` — If cube root of volume relative to the overall shape's cube root of volume is less than this, the geometry should be merged into its neighbors. (Note: This is a bit different from the histogram viewer's "Relative Size," which instead shows values relative to the largest rigid bone.)
- L1106 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L1113 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, DisplayName = "Point Spacing", UIMin = 0.f, EditCondition = "AddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L1115 _public function_ `FFixTinyGeoDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1124 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FSplitIslandsDataflowNode`  
`struct FSplitIslandsDataflowNode : public FDataflowNode`  
_L1134-1160_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Utilities / Split Islands tool Split selected geometry into islands based on mesh connectivity and distances.
- L1142 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to use
- L1146 _private member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — The selected pieces to use
- L1150 _private member_ `float CloseVertexDistance = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Split Islands", meta = (Units = "cm", ClampMin = "0.0"))` — Distance threshold for connecting spatially-close vertices before computing islands
- L1154 _private member_ `float VertexToSurfaceBridgeDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Split Islands", meta = (Units = "cm", ClampMin = "0.0"))` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance. 0 = disabled.
- L1156 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L1159 _public prototype_ `FSplitIslandsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FRecomputeNormalsInGeometryCollectionDataflowNode`  
`struct FRecomputeNormalsInGeometryCollectionDataflowNode : public FDataflowNode`  
_L1168-1207_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Utilities / Normals tool Recompute normals and tangents.
- L1176 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to use
- L1180 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — The selected pieces to use
- L1184 _public member_ `bool bOnlyTangents = false;` — `UPROPERTY(EditAnywhere, Category = RecomputeSettings)` — Whether to only recompute tangents, and leave normals as they were
- L1188 _public member_ `bool bRecomputeSharpEdges = false;` — `UPROPERTY(EditAnywhere, Category = RecomputeSettings, meta = (EditCondition = "!bOnlyTangents"))` — If true, update where edges are 'sharp' by comparing adjacent triangle face normals vs the Sharp Edge Angle Threshold.
- L1192 _public member_ `float SharpEdgeAngleThreshold = 60.0f;` — `UPROPERTY(EditAnywhere, Category = RecomputeSettings, meta = (UIMin = "0.0", UIMax = "180.0", ClampMin = "0.0", ClampMax = "180.0", EditCondition = "bRecomputeSharpEdges && !bOnlyTangents"))` — Threshold on angle of change in face normals across an edge, above which we create a sharp edge if bRecomputeSharpEdges is true
- L1196 _public member_ `bool bOnlyInternalSurfaces = true;` — `UPROPERTY(EditAnywhere, Category = RecomputeSettings, AdvancedDisplay)` — Whether to only change internal surface normals / tangents
- L1198 _public function_ `FRecomputeNormalsInGeometryCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1206 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FResampleGeometryCollectionDataflowNode`  
`struct FResampleGeometryCollectionDataflowNode : public FDataflowNode`  
_L1217-1257_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Utilities / Resample tool Resample to add collision particles in large flat regions that otherwise might have poor collision response. Only useful to help improve Particle - Implicit collisions.
- L1225 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to use
- L1229 _public member_ `FDataflowTransformSelection TransformSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "TransformSelection"))` — The selected pieces to use
- L1238 _public member_ `bool AddSamplesForCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Collision")` — If enabled, add extra vertices (without triangles) to the geometry in regions where vertices are spaced too far apart (e.g. across large triangles) These extra vertices will be used as collision samples in particle-implicit collisions, and can help the physics system detect collisions more accurately Note this is *only* useful for simulations that use particle-implicit collisions
- L1245 _public member_ `float CollisionSampleSpacing = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Collision", meta = (DataflowInput, DisplayName = "Point Spacing", UIMin = 0.f, EditCondition = "AddSamplesForCollision"))` — The number of centimeters to allow between vertices on the mesh surface: If there are gaps larger than this, add additional vertices (without triangles) to help support particle-implicit collisions Only used if Add Samples For Collision is enabled
- L1247 _public function_ `FResampleGeometryCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1256 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FValidateGeometryCollectionDataflowNode`  
`struct FValidateGeometryCollectionDataflowNode : public FDataflowNode`  
_L1266-1296_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Editor Fracture Mode / Utilities / Validate tool Ensures that geometrycollection is valid and clean.
- L1274 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection to use
- L1278 _public member_ `bool bRemoveUnreferencedGeometry = true;` — `UPROPERTY(EditAnywhere, Category = CleanUnused)` — Find and remove any unused geometry data
- L1282 _public member_ `bool bRemoveClustersOfOne = false;` — `UPROPERTY(EditAnywhere, Category = Clustering)` — Whether to collapse any clusters with only a single child
- L1286 _public member_ `bool bRemoveDanglingClusters = false;` — `UPROPERTY(EditAnywhere, Category = Clustering)` — Remove dangling clusters -- Note this can invalidate caches
- L1288 _public function_ `FValidateGeometryCollectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L1295 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Dataflow`
- L1298 _namespace_ `namespace UE`
- L1298 _namespace_ `namespace Dataflow` (scope `UE`)
- L1300 _prototype_ `void GeometryCollectionUtilityNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionUtils.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Dataflow` (scope `UE`)
- L17 _namespace_ `namespace Utils` (scope `UE::Dataflow`)
- L20 _prototype_ `void DebugDrawProximity(IDataflowDebugDrawInterface& DataflowRenderingInterface, const FManagedArrayCollection& Collection, const FLinearColor Color, const float LineWidthMultiplier, const float CenterSize, const FLinearColor CenterColor, const bool bRandomizeColor, const int32 ColorRandomSeed);` (scope `UE::Dataflow::Utils`)
- L29 _prototype_ `FLinearColor GetColorByLevel(const FManagedArrayCollection& InCollection, int32 InLevel);` (scope `UE::Dataflow::Utils`)
- L32 _variable_ `const uint32 Error_InvalidChars = 1;` (scope `UE::Dataflow::Utils`)
- L33 _variable_ `const uint32 Error_InvalidFormatInSegment = 2;` (scope `UE::Dataflow::Utils`)
- L36 _prototype_ `bool ParseIndicesStr(const FString& InFramesString, TArray<int32>& OutIndices, uint32& OutErrorCode);` (scope `UE::Dataflow::Utils`) — e.g. "0, 2, 5-10, 12-15"

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionVertexScalarToVertexIndicesNode.h` (Public)


#### struct `FGeometryCollectionVertexScalarToVertexIndicesNode`  
`struct FGeometryCollectionVertexScalarToVertexIndicesNode : public FDataflowNode`  
_L16-43_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- desc: Convert an vertex float array to a list of indices
- L24 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput))`
- L28 _public member_ `FCollectionAttributeKey AttributeKey = FCollectionAttributeKey("", "Ver` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (DataflowInput, DisplayName = "AttributeKey"))` — The name of the vertex attribute and group to generate indices from.
- L32 _public member_ `float SelectionThreshold = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Selection Filter", Meta = (ClampMin = "0", ClampMax = "1"))` — The value threshold for what is included in the vertex list.
- L36 _public member_ `TArray<int32> VertexIndices = {};` — `UPROPERTY(Meta = (DataflowOutput, DisplayName = "VertexIndices"))` — Output list of indices
- L38 _public prototype_ `FGeometryCollectionVertexScalarToVertexIndicesNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L42 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Dataflow`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/GeometryCollectionVerticesNodes.h` (Public)


#### struct `FTransformCollectionAttributeDataflowNode`  
`struct FTransformCollectionAttributeDataflowNode : public FDataflowNode`  
_L16-50_
- reflection: `USTRUCT(meta = (DataflowGeometryCollection))`
- inherits: `FDataflowNode`
- L22 _public typedef_ `typedef FManagedArrayCollection DataType;`
- L26 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DisplayName = "Collection"))`
- L29 _public member_ `FTransform TransformIn = FTransform::Identity;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "Transform"))`
- L32 _public member_ `FTransform LocalTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L35 _public member_ `FString GroupName = FString("Ver` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L38 _public member_ `FString AttributeName = FString("Ver` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L41 _public function_ `FTransformCollectionAttributeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L49 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`
- L52 _namespace_ `namespace UE`
- L52 _namespace_ `namespace Dataflow` (scope `UE`)
- L54 _prototype_ `void GeometryCollectionVerticesNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/SetVertexColorFromFloatArrayNode.h` (Public)


#### struct `FSetVertexColorFromFloatArrayDataflowNode`  
`struct FSetVertexColorFromFloatArrayDataflowNode : public FDataflowNode`  
_L17-50_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Set the vertex color on the collection based on the normalized float array.
- L25 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection Passthrough
- L29 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Float array to use as a scalar for the color
- L33 _public member_ `bool bNormalizeInput = true;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (DisplayName = "Normalize Input"))` — Enable normalization of input array
- L37 _public member_ `FLinearColor Color = FLinearColor(FColor::White);` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (DisplayName = "Color"))` — Base color for the normalized float array
- L40 _public function_ `FSetVertexColorFromFloatArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L48 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/SetVertexColorFromVertexIndicesNode.h` (Public)


#### struct `FSetVertexColorFromVertexIndicesDataflowNode`  
`struct FSetVertexColorFromVertexIndicesDataflowNode : public FDataflowNode`  
_L15-43_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Set the vertex color of the collection based on the selection set.
- L23 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection Passthrough
- L27 _public member_ `TArray<int32> VertexIndicesIn;` — `UPROPERTY(EditAnywhere, Category = "Vertices", meta = (DataflowInput, DisplayName = "VertexIndices"))` — Vertex indices set
- L31 _public member_ `FLinearColor SelectedColor = FLinearColor(FColor::Yellow);` — `UPROPERTY(EditAnywhere, Category = "Color")` — Selected vertex color
- L33 _public function_ `FSetVertexColorFromVertexIndicesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L41 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Dataflow`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionNodes/Public/Dataflow/SetVertexColorFromVertexSelectionNode.h` (Public)


#### struct `FSetVertexColorFromVertexSelectionDataflowNode`  
`struct FSetVertexColorFromVertexSelectionDataflowNode : public FDataflowNode`  
_L16-44_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Set the vertex color of the collection based on the selection set.
- L24 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection Passthrough
- L28 _public member_ `FDataflowVertexSelection VertexSelection;` — `UPROPERTY(meta = (DataflowInput, DisplayName = "VertexSelection", DataflowIntrinsic))` — Vertex selection set
- L32 _public member_ `FLinearColor SelectedColor = FLinearColor(FColor::Yellow);` — `UPROPERTY(EditAnywhere, Category = "Color")` — Selected vertex color
- L34 _public function_ `FSetVertexColorFromVertexSelectionDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowNode(InParam, InGuid)`
- L42 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Dataflow`
