# Plugins / ModelingOperators

- module root: `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators`
- headers: 42; symbols: 1008
- symbol kinds: class=57, enum=34, enumerator=115, function=56, macro=35, member=473, namespace=78, prototype=153, struct=5, typedef=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryAlgorithms, GeometryCore, InteractiveToolsFramework, MeshConversion, SkeletalMeshDescription, TextureUtilitiesCommon

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/BackgroundModelingComputeSource.h` (Public)


#### class `UE::Geometry::TModelingOpTask`  
`template<typename OpType> class TModelingOpTask : public FAbortableBackgroundTask`  
_L27-64_
- inherits: `FAbortableBackgroundTask`
- desc: TModelingOpTask is an FAbortableBackgroundTask that executes a modeling operator of template type OpType. OpType must implement a function with signature void CalculateResult(FProgressCancel*) After work completes, ExtractOperator() can be used to recover the internal OpType instance, to get access to the completed work. See TBackgroundModelingComputeSource for example usage (however this class can be used by itself)
- L33 _public function_ `TModelingOpTask(TUniquePtr<OpType> OperatorIn) : Operator(MoveTemp(OperatorIn))`
- L40 _public function_ `TUniquePtr<OpType> ExtractOperator()` — @return the contained computation Operator
- L46 _protected member_ `TUniquePtr<OpType> Operator;`
- L49 _protected function_ `void DoWork()` — FAbortableBackgroundTask API
- L60 _protected function_ `inline TStatId GetStatId() const` — FAsyncTask framework required function

#### enum `UE::Geometry::EBackgroundComputeTaskStatus`  
`enum class EBackgroundComputeTaskStatus`  
_L75-93_
- desc: This status is returned by TBackgroundModelingComputeSource to indicate what state a background computation is in
- L78 _public enumerator_ `ValidResultAvailable` — Computation of a result has finished and is waiting to be returned
- L85 _public enumerator_ `DirtyResultAvailable` — We have a result available, but a recompute has been requested. The status is not yet InProgress only because there is a delay of CancelActiveOpDelaySeconds between the request and operation restart, and we have not yet restarted.
- L88 _public enumerator_ `Aborted` — Last active computation was canceled and nothing new has happend yet
- L90 _public enumerator_ `InProgress` — Computation is currently running
- L92 _public enumerator_ `NotComputing` — Not running active computation, and last result has already been returned, so no new results to report

#### class `UE::Geometry::TBackgroundModelingComputeSource`  
`template<typename OpType, typename OpTypeFactory> class TBackgroundModelingComputeSource`  
_L128-233_
- desc: TBackgroundModelingComputeSource is a container that can be used to repeatedly execute a background computation. The assumption is that this background computation may need to be canceled and restarted, ie if input parameters change due to user input/actions. Clients of the template must provide an OpType, which is the operation to execute, and a OpTypeFactory, which creates OpType instances on demand. The APIs that must be provided in these types are minimal: OpTypeFactory: - TUniquePtr<OpType> MakeNewOperator() OpType: - void CalculateResult(FProgressCancel*) The Client cancels the active computation and spawns a new one by calling NotifyActiveComputeInvalidated(). This does not immediately terminate the computation, it waits for a delay of .CancelActiveOpDelaySeconds for this active compute to finish. This both (1) allows for partial updates to appear at UI levels if the compute is fast enough and (2) avoids constantly respawning new computes as the user (for example) drags a slider parameter. However as a result of this delay the Client must Tick() this class regularly. CheckStatus() can be used to determine if the computation has finished, in which case a new result is available. ExtractResult() will return this result. Note that a cancelled computation does not necessarily immediately terminate even after the timeout. This requires that the OpType implementation test the provided ProgressCancel instance frequently. When the Operator is "cancelled" it is moved to a separ
- L131 _protected member_ `OpTypeFactory* OperatorSource = nullptr;`
- L132 _protected member_ `FAsyncTaskExecuterWithAbort<TModelingOpTask<OpType>>* ActiveBackgroundTask = nullptr;`
- L142 _protected member_ `EBackgroundComputeTaskState TaskState;` — internal state flag
- L144 _protected member_ `double AccumTime = 0;`
- L145 _protected member_ `double LastStartTime = 0;`
- L146 _protected member_ `mutable double LastEndTime = 0;` — mutable because it must be set in CheckStatus, which is const
- L147 _protected member_ `double LastInvalidateTime = 0;`
- L149 _protected member_ `TSharedPtr<std::atomic<int>> ActiveTaskCount;`
- L151 _protected prototype_ `void StartNewCompute();`
- L154 _public function_ `TBackgroundModelingComputeSource(OpTypeFactory* OperatorSourceIn) : OperatorSource(OperatorSourceIn)`
- L161 _public prototype_ `~TBackgroundModelingComputeSource() = default;`
- L167 _public prototype_ `void Tick(float DeltaTime);` — Tick the active computation. Client must call this frequently with valid DeltaTime parameter, as cancellation/restart cycles are based on time delay specified by CancelActiveOpDelaySeconds
- L172 _public prototype_ `void CancelActiveCompute();` — Cancel the active computation immediately and do not start a new one
- L178 _public prototype_ `void NotifyActiveComputeInvalidated();` — Cancel the active computation if one is running, after a delay of CancelActiveOpDelaySeconds. Then start a new one.
- L195 _public prototype_ `FStatus CheckStatus() const;` — Return status of the active background computation.
- L198 _public function_ `bool IsWaitingForBackgroundTasks(int32& NumTasks) const` — If waiting for background tasks, returns true, and sets NumTasks to the number of active tasks
- L211 _public prototype_ `TUniquePtr<OpType> ExtractResult();` — @return The last computed Operator. This may only be called once, the caller then owns the Operator.
- L216 _public function_ `double GetElapsedComputeTime() const` — @return duration in seconds of current computation
- L227 _public member_ `double CancelActiveOpDelaySeconds = 0.5;` — Default wait delay for cancel/restart cycle
- L229 _public member_ `int32 MaxActiveTaskCount = 5;` — Maximum number of active tasks to allow to run in the background until we wait to launch more
- L232 _private member_ `bool bWaitingForActiveTasksToFinish = false;`
- L245 _function_ `template<typename OpType, typename OpTypeFactory> void TBackgroundModelingComputeSource<OpType, OpTypeFactory>::Tick(float DeltaTime)`
- L274 _function_ `template<typename OpType, typename OpTypeFactory> void TBackgroundModelingComputeSource<OpType, OpTypeFactory>::CancelActiveCompute()`
- L285 _function_ `template<typename OpType, typename OpTypeFactory> void TBackgroundModelingComputeSource<OpType, OpTypeFactory>::StartNewCompute()`
- L301 _function_ `template<typename OpType, typename OpTypeFactory> void TBackgroundModelingComputeSource<OpType, OpTypeFactory>::NotifyActiveComputeInvalidated()`
- L323 _function_ `TBackgroundModelingComputeSource<OpType, OpTypeFactory>::CheckStatus() const`
- L367 _function_ `template<typename OpType, typename OpTypeFactory> TUniquePtr<OpType> TBackgroundModelingComputeSource<OpType, OpTypeFactory>::ExtractResult()`

#### enum `UE::Geometry::TBackgroundModelingComputeSource::EBackgroundComputeTaskState`  
`enum class EBackgroundComputeTaskState`  
_L134-139_
- L136 _public enumerator_ `NotActive = 0`
- L137 _public enumerator_ `ComputingResult = 1`
- L138 _public enumerator_ `WaitingToCancel = 2`

#### struct `UE::Geometry::TBackgroundModelingComputeSource::FStatus`  
`struct FStatus`  
_L180-190_
- L182 _public member_ `EBackgroundComputeTaskStatus TaskStatus = EBackgroundComputeTaskStatus::NotComputing;`
- L189 _public member_ `double ElapsedTime = -1;` — if TaskStatus == ValidResultAvailable then this is the time spent computing the (valid) result if TaskStatus == DirtyResultAvailable then this is the time spent computing the (dirty) result if TaskStatus == Aborted              then this is the time spent computing the result before the task was aborted if TaskStatus == InProgress           then this is the time spent computing the result so far if TaskStatus == NotComputing         then this is the time spent not computing anything

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/BaseOps/SimpleMeshProcessingBaseOp.h` (Public)


#### class `UE::Geometry::FMeshBoundaryCache`  
`class FMeshBoundaryCache`  
_L19-25_
- L22 _public member_ `TArray<bool> bIsBoundary;`
- L23 _public member_ `TArray<int32> BoundaryVerts;`
- L24 _public prototype_ `void Calculate(const FDynamicMesh3& Mesh);`

#### class `UE::Geometry::FSimpleMeshProcessingBaseOp`  
`class FSimpleMeshProcessingBaseOp : public FDynamicMeshOperator`  
_L35-53_
- inherits: `FDynamicMeshOperator`
- desc: Dynamic Mesh Operator that has a separate PositionBuffer that contains copy of input vertex positions. These can be modified by operator and then UpdateResultMeshPositions() can be copied to update ResultMesh. UpdateResultMeshNormals() recalculates normals
- L38 _public prototype_ `FSimpleMeshProcessingBaseOp(const FDynamicMesh3* Mesh);`
- L40 _public prototype_ `virtual ~FSimpleMeshProcessingBaseOp() = default;`
- L43 _public prototype_ `void SetTransform(const FTransformSRT3d& XForm);` — set ability on protected transform.
- L46 _public prototype_ `void UpdateResultMeshPositions();` — copy the PositionBuffer locations back to the ResultMesh
- L49 _public prototype_ `void UpdateResultMeshNormals();` — recompute noramls of ResultMesh
- L52 _protected member_ `TArray<FVector3d> PositionBuffer;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/BaseOps/VoxelBaseOp.h` (Public)


#### class `UE::Geometry::FVoxelBaseOp`  
`class FVoxelBaseOp : public FDynamicMeshOperator`  
_L16-49_
- inherits: `FDynamicMeshOperator`
- L19 _public prototype_ `virtual ~FVoxelBaseOp() = default;`
- L22 _public member_ `double MinComponentVolume = 0.0, MinComponentArea = 0.0;` — inputs
- L22 _public member_ `double MinComponentVolume = 0.0, MinComponentArea = 0.0;` — inputs
- L24 _public member_ `bool bAutoSimplify = true;`
- L25 _public member_ `double SimplifyMaxErrorFactor = 1.0;`
- L27 _public member_ `int OutputVoxelCount = 1024;`
- L28 _public member_ `int InputVoxelCount = 1024;`
- L30 _public member_ `bool bRemoveInternalSurfaces = false;`
- L33 _public function_ `template<typename TransformType> static FVector3d GetAverageTranslation(TArrayView<const TransformType> Transforms)`
- L48 _public prototype_ `virtual void PostProcessResult(FProgressCancel* Progress, double MeshCellSize);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CleaningOps/EditNormalsOp.h` (Public)


#### enum `ENormalCalculationMethod`  
`enum class ENormalCalculationMethod : uint8`  
_L16-24_
- reflection: `UENUM()`
- L19 _public enumerator_ `AreaWeighted` — Use triangle area to weight how much a triangle's normal contributes its vertices' normals
- L21 _public enumerator_ `AngleWeighted` — Use the angle of a triangle at a vertex to weight how much that triangle's normal contributes to that vertex's normal
- L23 _public enumerator_ `AreaAngleWeighting` — Multiply area and angle weights together for a combined weight controlling how much a triangle's normal contributes to its vertices' normals

#### enum `ESplitNormalMethod`  
`enum class ESplitNormalMethod : uint8`  
_L28-40_
- reflection: `UENUM()`
- L31 _public enumerator_ `UseExistingTopology` — Keep the existing split-normals structure on the mesh
- L33 _public enumerator_ `FaceNormalThreshold` — Recompute split-normals by grouping faces around each vertex based on an angle threshold
- L35 _public enumerator_ `FaceGroupID` — Recompute split-normals by grouping faces around each vertex that share a face/polygroup
- L37 _public enumerator_ `PerTriangle` — Set each triangle-vertex to have the face normal of that triangle's plane
- L39 _public enumerator_ `PerVertex` — Set each vertex to have a fully shared normal, i.e. no split normals

#### class `UE::Geometry::FEditNormalsOp`  
`class FEditNormalsOp : public FDynamicMeshOperator`  
_L47-80_
- inherits: `FDynamicMeshOperator`
- L50 _public prototype_ `virtual ~FEditNormalsOp() = default;`
- L53 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — inputs
- L54 _public member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> MeshPolygroups;`
- L58 _public member_ `TSet<int> EditTriangles;` — These are indices into OriginalMesh. If both are non-empty only edit the corresponding elements in the normal overlay otherwise operate on the whole normal overlay
- L59 _public member_ `TSet<int> EditVertices;`
- L61 _public member_ `bool bFixInconsistentNormals;`
- L62 _public member_ `bool bInvertNormals;`
- L63 _public member_ `bool bRecomputeNormals;`
- L64 _public member_ `ENormalCalculationMethod NormalCalculationMethod;`
- L65 _public member_ `ESplitNormalMethod SplitNormalMethod;`
- L66 _public member_ `bool bAllowSharpVertices;`
- L67 _public member_ `float NormalSplitThreshold;`
- L69 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L75 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L78 _private prototype_ `void CalculateResultWholeMesh(FProgressCancel* Progress);`
- L79 _private prototype_ `void CalculateResultSelection(FProgressCancel* Progress);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L42 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CleaningOps/HoleFillOp.h` (Public)


#### enum `EHoleFillOpFillType`  
`enum class EHoleFillOpFillType : uint8`  
_L13-30_
- reflection: `UENUM()`
- L16 _public enumerator_ `TriangleFan UMETA(DisplayName = "TriangleFan")` — Fill with a fan of triangles connected to a new central vertex.
- L19 _public enumerator_ `PolygonEarClipping UMETA(DisplayName = "PolygonEarClipping")` — Incrementally triangulate the hole boundary without introducing new interior vertices.
- L22 _public enumerator_ `Planar UMETA(DisplayName = "Planar")` — Choose a best-fit plane, project the boundary vertices to the plane, and use 2D Delaunay triangulation.
- L25 _public enumerator_ `Minimal UMETA(DisplayName = "Minimal")` — Fill with a triangulation which attempts to minimize Gaussian curvature and not introduce new interior vertices.
- L29 _public enumerator_ `Smooth UMETA(DisplayName = "Smooth")` — Fill hole with a simple triangulation, then alternate between smoothing and remeshing. Optionally include the triangles around the hole in the smoothing/remeshing.

#### struct `UE::Geometry::FFillOptions`  
`struct FFillOptions`  
_L38-45_
- L41 _public member_ `bool bRemoveIsolatedTriangles = false;` — Clean up triangles that have no neighbors
- L44 _public member_ `bool bQuickFillSmallHoles = false;` — Identify and quickly fill single-triangle holes

#### class `UE::Geometry::FHoleFillOp`  
`class FHoleFillOp : public FDynamicMeshOperator`  
_L47-70_
- inherits: `FDynamicMeshOperator`
- L53 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Ownership shared with Tool
- L55 _public member_ `EHoleFillOpFillType FillType = EHoleFillOpFillType::Minimal;`
- L56 _public member_ `double MeshUVScaleFactor = 1.0;`
- L57 _public member_ `TArray<UE::Geometry::FEdgeLoop> Loops;`
- L59 _public member_ `FFillOptions FillOptions;`
- L60 _public member_ `UE::Geometry::FSmoothFillOptions SmoothFillOptions;`
- L63 _public member_ `TArray<int32> NewTriangles;` — output
- L64 _public member_ `int NumFailedLoops = 0;`
- L67 _public prototype_ `void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator implementation
- L69 _public prototype_ `bool FillSingleTriangleHole(const FEdgeLoop& Loop, int32& NewGroupID);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L33 _namespace_ `namespace UE`
- L35 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CleaningOps/RemeshMeshOp.h` (Public)


#### enum `ERemeshType`  
`enum class ERemeshType : uint8`  
_L18-29_
- reflection: `UENUM()`
- desc: Remeshing modes
- L21 _public enumerator_ `Standard = 0 UMETA(DisplayName = "Standard")` — One pass over the entire mesh, then remesh only changed edges
- L24 _public enumerator_ `FullPass = 1 UMETA(DisplayName = "Full Pass")` — Multiple full passes over the entire mesh
- L27 _public enumerator_ `NormalFlow = 2 UMETA(DisplayName = "Normal Flow")` — One pass over the entire mesh, then remesh only changed edges. Use Normal flow to align triangles with input.

#### enum `ERemeshSmoothingType`  
`enum class ERemeshSmoothingType : uint8`  
_L33-43_
- reflection: `UENUM()`
- desc: Smoothing modes
- L36 _public enumerator_ `Uniform = 0 UMETA(DisplayName = "Uniform")` — Uniform Smoothing
- L39 _public enumerator_ `Cotangent = 1 UMETA(DisplayName = "Shape Preserving")` — Cotangent Smoothing
- L42 _public enumerator_ `MeanValue = 2 UMETA(DisplayName = "Mixed")` — Mean Value Smoothing

#### class `UE::Geometry::FRemeshMeshOp`  
`class FRemeshMeshOp : public FDynamicMeshOperator`  
_L52-146_
- inherits: `FDynamicMeshOperator`
- L55 _public prototype_ `virtual ~FRemeshMeshOp() = default;`
- L58 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — inputs
- L59 _public member_ `TSharedPtr<FDynamicMeshAABBTree3, ESPMode::ThreadSafe> OriginalMeshSpatial;`
- L61 _public member_ `ERemeshType RemeshType = ERemeshType::Standard;`
- L63 _public member_ `int RemeshIterations = 20;`
- L64 _public member_ `int MaxRemeshIterations = 20;`
- L65 _public member_ `double MinActiveEdgeFraction = 0.01;` — terminate remeshing if modified edge count in last pass is below this fraction of total edges
- L66 _public member_ `int ExtraProjectionIterations = 5;`
- L67 _public member_ `int TriangleCountHint = 0;`
- L68 _public member_ `float SmoothingStrength = 0.25f;`
- L69 _public member_ `double TargetEdgeLength = 1.0f;`
- L70 _public member_ `ERemeshSmoothingType SmoothingType;`
- L71 _public member_ `bool bDiscardAttributes = false;`
- L73 _public member_ `bool bNeedsWeightMaps = false;` — Note: if bDiscardAttributes and bNeedsWeightMaps are both true, the weight map attributes will be kept through remeshing (but other attributes will be discarded)
- L74 _public member_ `bool bPreserveSharpEdges = true;`
- L75 _public member_ `bool bFlips = true;`
- L76 _public member_ `bool bSplits = true;`
- L77 _public member_ `bool bCollapses = true;`
- L78 _public member_ `bool bReproject = true;`
- L79 _public member_ `bool bPreventNormalFlips = true;`
- L80 _public member_ `bool bPreventTinyTriangles = true;`
- L81 _public member_ `bool bReprojectConstraints = false;`
- L82 _public member_ `double BoundaryCornerAngleThreshold = 45.0;`
- L86 _public member_ `bool bResultMustHaveAttributesEnabled = false;` — When true, result will have attributes object regardless of whether attributes were discarded or present initially.
- L87 _public member_ `EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;`
- L87 _public member_ `EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;`
- L87 _public member_ `EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;`
- L89 _public member_ `FDynamicMesh3* ProjectionTarget = nullptr;`
- L90 _public member_ `FDynamicMeshAABBTree3* ProjectionTargetSpatial = nullptr;`
- L92 _public member_ `FTransformSRT3d TargetMeshLocalToWorld = FTransformSRT3d::Identity();`
- L93 _public member_ `FTransformSRT3d ToolMeshLocalToWorld = FTransformSRT3d::Identity();`
- L94 _public member_ `bool bUseWorldSpace = false;`
- L95 _public member_ `bool bParallel = true;`
- L97 _public member_ `TFunction<double(const FDynamicMesh3&, int VertexA, int VertexB)> CustomEdgeLengthScaleF;`
- L102 _public member_ `int FaceProjectionPassesPerRemeshIteration = 1;` — During each call to RemeshIteration, do this many passes of face-aligned projection
- L105 _public member_ `double SurfaceProjectionSpeed = 0.2;` — drag on surface projection
- L108 _public member_ `double NormalAlignmentSpeed = 0.2;` — drag on normal alignment
- L112 _public member_ `bool bSmoothInFillAreas = true;` — Control whether or not we want to apply mesh smoothing in "free" areas that have not projected to target surface. This smoothing is on applied in the ExtraProjections Iterations
- L115 _public member_ `float FillAreaDistanceMultiplier = 0.25;` — This is used as a multiplier on MaxEdgeLength to determine when we identify points as being in "free" areas
- L118 _public member_ `float FillAreaSmoothMultiplier = 0.25;` — This is used as a multiplier on the Remesher smoothing rate, applied to points identified as being in "free" areas
- L124 _public prototype_ `void SetUserSpecifiedConstraints(const FMeshConstraints& Constraints);` — Add arbitrary mesh constraints besides the boundary/seam constraints that are computed by this op
- L126 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L131 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator implementation
- L135 _public prototype_ `static double CalculateTargetEdgeLength(const FDynamicMesh3* Mesh, int TargetTriCount, double PrecomputedMeshArea = 0.0);`
- L140 _protected prototype_ `virtual TUniquePtr<FRemesher> CreateRemesher(ERemeshType Type, FDynamicMesh3* TargetMesh);`
- L144 _private member_ `FMeshConstraints UserSpecifiedConstraints;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L45 _namespace_ `namespace UE`
- L47 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CleaningOps/RemoveOccludedTrianglesOp.h` (Public)


#### class `UE::Geometry::FRemoveOccludedTrianglesOp`  
`class FRemoveOccludedTrianglesOp : public FDynamicMeshOperator`  
_L19-80_
- inherits: `FDynamicMeshOperator`
- L22 _public prototype_ `virtual ~FRemoveOccludedTrianglesOp() = default;`
- L25 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — inputs
- L27 _public member_ `TArray<TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe>> OccluderTrees;`
- L28 _public member_ `TArray<TSharedPtr<UE::Geometry::TFastWindingTree<FDynamicMesh3>, ESPMode::ThreadSafe>> OccluderWindings;`
- L29 _public member_ `TArray<FTransformSRT3d> OccluderTransforms;`
- L31 _public member_ `TArray<FTransformSRT3d> MeshTransforms;`
- L33 _public member_ `UE::Geometry::EOcclusionTriangleSampling TriangleSamplingMethod = UE::Geometry::EOcclusionTriangleSampling::Centroids;`
- L37 _public member_ `double NormalOffset = FMathd::ZeroTolerance;` — we nudge points out by this amount to try to counteract numerical issues
- L40 _public member_ `double WindingIsoValue = 0.5;` — use this as winding isovalue for WindingNumber mode
- L43 _public member_ `int AddRandomRays = 0;` — random rays to add beyond +/- major axes, for raycast sampling
- L46 _public member_ `int AddTriangleSamples = 0;` — add triangle samples per triangle (in addition to TriangleSamplingMethod)
- L49 _public member_ `int ShrinkRemoval = 0;` — once triangles to remove are identified, do iterations of boundary erosion, ie contract selection by boundary vertex one-rings
- L51 _public member_ `double MinAreaConnectedComponent = 0;`
- L53 _public member_ `int MinTriCountConnectedComponent = 0;`
- L56 _public member_ `bool bSetTriangleGroupInsteadOfRemoving = false;` — if true, we will set triangle group IDs for occluded triangles, rather than deleting the triangles
- L59 _public member_ `FName ActiveGroupLayer;` — name of the group layer to use if we are setting triangle groups instead of removing occluded triangles
- L62 _public member_ `bool bActiveGroupLayerIsDefault = true;` — if true, the ActiveGroupLayer is the name of the "default" layer, so we'll use the built-in group IDs
- L64 _public member_ `UE::Geometry::EOcclusionCalculationMode InsideMode = UE::Geometry::EOcclusionCalculationMode::FastWindingNumber;`
- L69 _public member_ `int CreatedGroupID = -1;` — outputs, used when bSetTriangleGroupInsteadOfRemoving is true
- L70 _public member_ `int CreatedGroupLayerIndex = -1;`
- L73 _public prototype_ `void SetTransform(const FTransform& Transform);`
- L79 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CompositionOps/BooleanMeshesOp.h` (Public)


#### enum `ECSGOperation`  
`enum class ECSGOperation : uint8`  
_L17-30_
- reflection: `UENUM()`
- desc: CSG operation types
- L20 _public enumerator_ `DifferenceAB = 0 UMETA(DisplayName = "Difference A - B")` — Subtract the second object from the first object
- L23 _public enumerator_ `DifferenceBA = 1 UMETA(DisplayName = "Difference B - A")` — Subtract the first object from the second object
- L26 _public enumerator_ `Intersect = 2 UMETA(DisplayName = "Intersection")` — Intersection of the two objects, i.e. where both objects overlap
- L29 _public enumerator_ `Union = 3 UMETA(DisplayName = "Union")` — Union of the two objects, i.e. merger of both objects

#### enum `ETrimOperation`  
`enum class ETrimOperation : uint8`  
_L33-40_
- reflection: `UENUM()`
- L36 _public enumerator_ `TrimA = 0 UMETA(DisplayName = "Trim A")` — Remove geometry from the first object using the second object
- L39 _public enumerator_ `TrimB = 1 UMETA(DisplayName = "Trim B")` — Remove geometry from the second object using the first object

#### enum `ETrimSide`  
`enum class ETrimSide : uint8`  
_L44-48_
- reflection: `UENUM()`
- L46 _public enumerator_ `RemoveInside = 0`
- L47 _public enumerator_ `RemoveOutside = 1`

#### class `UE::Geometry::FBooleanMeshesOp`  
`class FBooleanMeshesOp : public FDynamicMeshOperator`  
_L56-92_
- inherits: `FDynamicMeshOperator`
- L59 _public prototype_ `virtual ~FBooleanMeshesOp() override = default;`
- L62 _public member_ `ECSGOperation CSGOperation;` — inputs
- L63 _public member_ `ETrimOperation TrimOperation;`
- L64 _public member_ `ETrimSide TrimSide;`
- L65 _public member_ `bool bTrimMode = false;` — if true, do a trim operation instead of a boolean
- L66 _public member_ `TArray<TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe>> Meshes;`
- L67 _public member_ `TArray<FTransformSRT3d> Transforms;` — 1:1 with Meshes
- L68 _public member_ `bool bAttemptFixHoles = false;`
- L69 _public member_ `double WindingThreshold = 0.5;`
- L72 _public member_ `bool bTryCollapseExtraEdges = false;` — If true, try to do edge-collapses along cut edges to remove unnecessary edges inserted by cut
- L74 _public member_ `float TryCollapseExtraEdgesPlanarThresh = 0.01f;` — Angle threshold in degrees used for testing if two triangles should be considered coplanar, or two lines collinear
- L76 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L82 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L85 _public function_ `const TArray<int>& GetCreatedBoundaryEdges() const` — IDs of any newly-created boundary edges in the result mesh
- L91 _private member_ `TArray<int> CreatedBoundaryEdges;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L51 _namespace_ `namespace UE`
- L53 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CompositionOps/CubeGridBooleanOp.h` (Public)


#### class `UE::Geometry::FCubeGridBooleanOp`  
`class FCubeGridBooleanOp : public FDynamicMeshOperator`  
_L22-103_
- inherits: `FDynamicMeshOperator`
- desc: Operator meant to be used with UCubeGridTool that adds or subtracts a box to/from an input mesh, with options to weld the box's corners to make ramps/corners
- L27 _public prototype_ `virtual ~FCubeGridBooleanOp() = default;`
- L32 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;` — The mesh to add to or subtract from
- L33 _public member_ `FTransformSRT3d InputTransform = FTransformSRT3d::Identity();`
- L36 _public member_ `FOrientedBox3d WorldBox;` — Box from which to generate the second mesh
- L46 _public member_ `TSharedPtr<FCornerInfo> CornerInfo;`
- L49 _public member_ `bool bSubtract = false;` — Determines whether the box is added or subtracted from the mesh.
- L53 _public member_ `bool bKeepInputTransform = false;` — When true, mesh is constructed such that ResultTransform is InputTransform. When false, ResultTransform is based off of the centroid of the result.
- L58 _public member_ `bool bCrosswiseDiagonal = false;` — Only relevant when CornerInfo is used. When true, diagonal will generally prefer to lie flat across the non-planar top. This determines, for instance, whether a pulled corner results in a pyramid with three faces (if true) or four (if false).
- L61 _public member_ `int32 OpMeshMaterialID = 0;` — The material ID to give to triangles in the operator mesh.
- L74 _public member_ `TArray<int32, TFixedAllocator<6>> FaceUVOrientations;` — For each face of the op box (indexed as in IndexUtil::BoxFaces), determines the orientation in which the UV's should be assigned, which can be imagined as number of counterclockwise rotations of the face in the UV plane while keeping the corner labels the same. For instance, the corner UV's for orientation 0 are (0,0), (width, 0), (width, height), (0, height), whereas for orientation 1 they are (height, 0), (height, width), (0, width), (0,0) This is used to orient UV's in a uniform direction while extruding/pushing in different directions in the cube grid.
- L80 _public member_ `double OpMeshHeightUVOffset = 0;` — When setting UV's on the box, the component affected by height is adjusted by this offset. This is used to avoid "restarting" UV's when performing multiple operations with the same selection.
- L82 _public member_ `float UVScale = 1;`
- L83 _public member_ `bool bWorldSpaceUVs = true;`
- L88 _public member_ `TArray<int32, TFixedAllocator<4>> OpMeshSideGroups = { IndexConstants::InvalidID, IndexConstants::InvalidID, IndexConstants::InvalidID, IndexConstants::InvalidID };` — Both Input and Output: When not set to InvalidID, these will control the setting of the side groups in the operator mesh. This allows for the sides to keep the same groups with each step when selection is unchanged.
- L99 _public member_ `TSharedPtr<TArray<int32>, ESPMode::ThreadSafe> ChangedTids;` — Will be reset to a container storing tids whose positions or connectivity changed. Only filled if bTrackChangedTids is true.
- L100 _public member_ `bool bTrackChangedTids = false;`
- L102 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### struct `UE::Geometry::FCubeGridBooleanOp::FCornerInfo`  
`struct FCornerInfo`  
_L39-45_
- desc: Optional: information to weld corners along the Z axis to create ramps/pyramids/pyramid cutaways
- L44 _public member_ `bool WeldedAtBase[4] = { false, false, false, false };` — "Base" refers to the 0-3 indexed corners in FOrientedBox3d, and the flags here are true if the vertex is welded to its Z axis neighbor. The lower side on the Z axis is the enclosed area for the purposes of an operation.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L15 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CompositionOps/CurveSweepOp.h` (Public)


#### class `UE::Geometry::FCurveSweepOp`  
`class FCurveSweepOp : public FDynamicMeshOperator`  
_L20-83_
- inherits: `FDynamicMeshOperator`
- desc: Operation for sweeping a profile curve along a sweep curve to create a mesh.
- L31 _public prototype_ `virtual ~FCurveSweepOp() = default;`
- L34 _public member_ `TArray<FVector3d> ProfileCurve;` — Inputs
- L35 _public member_ `TArray<FFrame3d> SweepCurve;`
- L36 _public member_ `TSet<int32> ProfileVerticesToWeld;`
- L39 _public member_ `bool bProfileCurveIsClosed = false;` — If true, the last profile curve point will be considered connected to the first.
- L42 _public member_ `bool bSweepCurveIsClosed = false;` — If true, the last sweep point will be considered connected to the first.
- L45 _public member_ `bool bSharpNormals = true;` — Whether adjacent triangles should share averaged normals or have their own (to give sharpness)
- L49 _public member_ `double SharpNormalAngleTolerance = 0.1;` — When using sharp normals, the degree difference that adjacent triangles can have in their normals for them to be considered "coplanar" and therefore share normals.
- L52 _public member_ `ECapFillMode CapFillMode = ECapFillMode::Delaunay;` — What kind of cap to create
- L56 _public member_ `bool bUVsSkipFullyWeldedEdges = true;` — Whether fully welded edges (welded vertex to welded vertex) in the profile curve should affect the UV layout, since such edges don't generate triangles.
- L59 _public member_ `FVector2d UVScale = FVector2d(1, 1);` — Generated UV's will be multiplied by these values.
- L62 _public member_ `FVector2d UVOffset = FVector2d(0, 0);` — These values will be added to the generated UV's after applying UVScale.
- L65 _public member_ `bool bUVScaleRelativeWorld = false;` — If true, UVs are scaled to keep a consistent scale across differently sized geometry
- L68 _public member_ `double UnitUVInWorldCoordinates = 100;` — When bUVScaleRelativeWorld is true, the size in world coordinates of 1 UV coordinate
- L70 _public member_ `EProfileSweepPolygonGrouping PolygonGroupingMode = EProfileSweepPolygonGrouping::PerFace;`
- L72 _public member_ `EProfileSweepQuadSplit QuadSplitMode = EProfileSweepQuadSplit::ShortestDiagonal;`
- L76 _public member_ `double DiagonalTolerance = 0.01;` — When QuadSplitMode is ShortestDiagonal, biases one of the diagonals so that symmetric quads are split uniformly. The tolerance is a proportion allowable difference.
- L82 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### enum `UE::Geometry::FCurveSweepOp::ECapFillMode`  
`enum class ECapFillMode`  
_L23-29_
- L25 _public enumerator_ `None`
- L26 _public enumerator_ `Delaunay`
- L27 _public enumerator_ `EarClipping`
- L28 _public enumerator_ `CenterFan`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CompositionOps/MirrorOp.h` (Public)


#### class `UE::Geometry::FMirrorOp`  
`class FMirrorOp : public FDynamicMeshOperator`  
_L17-56_
- inherits: `FDynamicMeshOperator`
- L20 _public prototype_ `virtual ~FMirrorOp() = default;`
- L23 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Inputs
- L24 _public member_ `FVector3d LocalPlaneOrigin;`
- L25 _public member_ `FVector3d LocalPlaneNormal;`
- L28 _public member_ `double PlaneTolerance = FMathf::ZeroTolerance * 10.0;` — Tolerance to use when bCropFirst or bWeldAlongPlane is true.
- L31 _public member_ `bool bCropFirst = true;` — Whether to crop the result first along the plane.
- L34 _public member_ `bool bSimplifyAlongNewEdges = true;` — Whether to locally simplify the new edges created when cropping along the plane. Only relevant if bCropFirst is true.
- L37 _public member_ `bool bAppendToOriginal = true;` — If true, the mirrored portion is appended to the original. If false, the result is just the mirrored portion.
- L40 _public member_ `bool bWeldAlongPlane = true;` — Whether vertices on the mirror plane should be welded. Only relevant if bAppendToOriginal is true.
- L43 _public member_ `EMeshMirrorNormalMode WeldNormalMode = EMeshMirrorNormalMode::MirrorNormals;` — The normal compute method for welded vertices along the mirror plane.
- L46 _public member_ `bool bAllowBowtieVertexCreation = false;` — Whether, when welding, new bowtie vertex creation should be allowed.
- L48 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L54 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CompositionOps/SelfUnionMeshesOp.h` (Public)


#### class `UE::Geometry::FSelfUnionMeshesOp`  
`class FSelfUnionMeshesOp : public FDynamicMeshOperator`  
_L16-48_
- inherits: `FDynamicMeshOperator`
- L19 _public prototype_ `virtual ~FSelfUnionMeshesOp() = default;`
- L22 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> CombinedMesh;` — inputs
- L23 _public member_ `bool bAttemptFixHoles = false;`
- L24 _public member_ `double WindingNumberThreshold = .5;`
- L25 _public member_ `bool bTrimFlaps = false;`
- L28 _public member_ `bool bTryCollapseExtraEdges = false;` — If true, try to do edge-collapses along cut edges to remove unnecessary edges inserted by cut
- L30 _public member_ `float TryCollapseExtraEdgesPlanarThresh = 0.01f;` — Angle threshold in degrees used for testing if two triangles should be considered coplanar, or two lines collinear
- L32 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L38 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L41 _public function_ `TArray<int> GetCreatedBoundaryEdges() const` — IDs of any newly-created boundary edges in the result mesh
- L47 _private member_ `TArray<int> CreatedBoundaryEdges;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CompositionOps/VoxelBlendMeshesOp.h` (Public)


#### class `UE::Geometry::FVoxelBlendMeshesOp`  
`class FVoxelBlendMeshesOp : public FVoxelBaseOp`  
_L18-44_
- inherits: `FVoxelBaseOp`
- L21 _public prototype_ `virtual ~FVoxelBlendMeshesOp() = default;`
- L24 _public member_ `TArray<TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe>> Meshes;` — inputs
- L25 _public member_ `TArray<FTransform> Transforms;` — 1:1 with Meshes
- L27 _public member_ `double BlendFalloff = 10;`
- L28 _public member_ `double BlendPower = 2;`
- L30 _public member_ `bool bVoxWrap = false;`
- L31 _public member_ `bool bRemoveInternalsAfterVoxWrap = false;`
- L32 _public member_ `double ThickenShells = 0.0;`
- L34 _public member_ `bool bSubtract = false;`
- L36 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L42 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CompositionOps/VoxelMorphologyMeshesOp.h` (Public)


#### enum `EMorphologyOperation`  
`enum class EMorphologyOperation : uint8`  
_L18-32_
- reflection: `UENUM()`
- desc: Morphology operation types
- L21 _public enumerator_ `Dilate = 0` — Expand the shapes outward
- L24 _public enumerator_ `Contract = 1` — Shrink the shapes inward
- L27 _public enumerator_ `Close = 2` — Dilate and then contract, to delete small negative features (sharp inner corners, small holes)
- L30 _public enumerator_ `Open = 3` — Contract and then dilate, to delete small positive features (sharp outer corners, small isolated pieces)

#### class `UE::Geometry::FVoxelMorphologyMeshesOp`  
`class FVoxelMorphologyMeshesOp : public FVoxelBaseOp`  
_L39-63_
- inherits: `FVoxelBaseOp`
- L42 _public prototype_ `virtual ~FVoxelMorphologyMeshesOp() = default;`
- L45 _public member_ `TArray<TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe>> Meshes;` — inputs
- L46 _public member_ `TArray<FTransformSRT3d> Transforms;` — 1:1 with Meshes
- L48 _public member_ `double Distance = 1.0;`
- L49 _public member_ `EMorphologyOperation Operation;`
- L51 _public member_ `bool bVoxWrapInput = false;`
- L52 _public member_ `bool bRemoveInternalsAfterVoxWrap = false;`
- L53 _public member_ `double ThickenShells = 0.0;`
- L55 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L61 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L34 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CompositionOps/VoxelSolidifyMeshesOp.h` (Public)


#### class `UE::Geometry::FVoxelSolidifyMeshesOp`  
`class FVoxelSolidifyMeshesOp : public FVoxelBaseOp`  
_L18-43_
- inherits: `FVoxelBaseOp`
- L21 _public prototype_ `virtual ~FVoxelSolidifyMeshesOp() = default;`
- L24 _public member_ `TArray<TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe>> Meshes;` — inputs
- L25 _public member_ `TArray<FTransformSRT3d> Transforms;` — 1:1 with Meshes
- L27 _public member_ `double WindingThreshold = .5;`
- L28 _public member_ `double ExtendBounds = 1;`
- L29 _public member_ `bool bSolidAtBoundaries = true;`
- L30 _public member_ `int SurfaceSearchSteps = 3;`
- L32 _public member_ `bool bApplyThickenShells = false;`
- L33 _public member_ `double ThickenShells = 5;`
- L35 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L41 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CurveOps/GenerateCrossSectionOp.h` (Public)


#### class `UE::Geometry::FGenerateCrossSectionOp`  
`class FGenerateCrossSectionOp : public FDynamicMeshOperator`  
_L19-45_
- inherits: `FDynamicMeshOperator`
- L22 _public prototype_ `virtual ~FGenerateCrossSectionOp() = default;`
- L25 _public member_ `FVector3d LocalPlaneOrigin, LocalPlaneNormal;` — inputs
- L25 _public member_ `FVector3d LocalPlaneOrigin, LocalPlaneNormal;` — inputs
- L26 _public member_ `bool bSimplifyAlongNewEdges = true;`
- L27 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L29 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L35 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L39 _public prototype_ `TArray<TArray<FVector3d>> GetCutLoops() const;`
- L40 _public prototype_ `TArray<TArray<FVector3d>> GetCutSpans() const;`
- L44 _private member_ `TUniquePtr<FMeshPlaneCut> MeshCutter;`

#### class `UGenerateCrossSectionOpFactory`  
`class UGenerateCrossSectionOpFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L53-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L60 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L62 _public member_ `FVector3d LocalPlaneOrigin, LocalPlaneNormal;`
- L62 _public member_ `FVector3d LocalPlaneOrigin, LocalPlaneNormal;`
- L63 _public member_ `bool bSimplifyAlongNewEdges = true;`
- L65 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L66 _public member_ `UE::Geometry::FTransformSRT3d TargetTransform;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CurveOps/TriangulateCurvesOp.h` (Public)


#### enum `EFlattenCurveMethod`  
`enum class EFlattenCurveMethod : uint8`  
_L15-27_
- reflection: `UENUM()`
- L18 _public enumerator_ `DoNotFlatten` — Do not flatten the curves before triangulations
- L20 _public enumerator_ `ToBestFitPlane` — Fit planes to the curves, and flatten the curves by projection to their plane
- L22 _public enumerator_ `AlongX` — Flatten by projection along the X axis
- L24 _public enumerator_ `AlongY` — Flatten by projection along the Y axis
- L26 _public enumerator_ `AlongZ` — Flatten by projection along the Z axis

#### enum `ECombineCurvesMethod`  
`enum class ECombineCurvesMethod : uint8`  
_L30-42_
- reflection: `UENUM()`
- L33 _public enumerator_ `LeaveSeparate` — Triangulate each curve separately
- L35 _public enumerator_ `Union` — Triangulate the union of the curve polygons -- the space covered by any of the polygons
- L37 _public enumerator_ `Intersect` — Triangulate the intersection of the curve polygons -- the space covered by all of the polygons
- L39 _public enumerator_ `Difference` — Triangulate the difference of the first curve polygon minus the remaining curve polygons
- L41 _public enumerator_ `ExclusiveOr` — Triangulate the exclusive-or of the curve polygons -- the space covered by the first polygon, or the remaining polygons, but not both

#### enum `EOffsetClosedCurvesMethod`  
`enum class EOffsetClosedCurvesMethod : uint8`  
_L45-53_
- reflection: `UENUM()`
- L48 _public enumerator_ `DoNotOffset` — Do not offset the closed curves
- L50 _public enumerator_ `OffsetOuterSide` — Offset the outside of the closed curves -- growing or shrinking the solid shape
- L52 _public enumerator_ `OffsetBothSides` — Offset both sides of the closed curves -- creating hollow shapes that follow the curves with Curve Offset width

#### enum `EOffsetOpenCurvesMethod`  
`enum class EOffsetOpenCurvesMethod : uint8`  
_L56-62_
- reflection: `UENUM()`
- L59 _public enumerator_ `TreatAsClosed` — Treat open curves as if they were closed -- connecting the last point back to the first
- L61 _public enumerator_ `Offset` — Offset the open curves, creating shapes following the curves with Curve Offset width

#### enum `EOffsetJoinMethod`  
`enum class EOffsetJoinMethod : uint8`  
_L65-73_
- reflection: `UENUM()`
- L68 _public enumerator_ `Square` — Cut off corners between offset edges with square shapes
- L70 _public enumerator_ `Miter` — Miter corners between offset edges, extending the neighboring curve edges straight to their intersection point, unless that point is farther than the miter limit distance
- L72 _public enumerator_ `Round` — Smoothly join corners between offset edges with circular paths

#### enum `EOpenCurveEndShapes`  
`enum class EOpenCurveEndShapes : uint8`  
_L76-84_
- reflection: `UENUM()`
- L79 _public enumerator_ `Square` — Close the ends of open paths with square end caps
- L81 _public enumerator_ `Round` — Close the ends of open paths with round end caps
- L83 _public enumerator_ `Butt` — Close the ends of open paths abruptly with no end caps

#### class `UE::Geometry::FTriangulateCurvesOp`  
`class FTriangulateCurvesOp : public FDynamicMeshOperator`  
_L94-163_
- inherits: `FDynamicMeshOperator`
- desc: FTriangulateCurvesOp triangulates polygons/paths generated from USplineComponent inputs.
- L97 _public prototype_ `virtual ~FTriangulateCurvesOp() = default;`
- L104 _public prototype_ `void AddSpline(USplineComponent* Spline, double ErrorTolerance);` — Sample a spline with the given ErrorTolerance and add it as a curve
- L111 _public prototype_ `void AddWorldCurve(TArrayView<const FVector3d> WorldSpaceVertices, bool bClosed, const FTransform& ReferenceTransform);` — Add a curve in world space @param WorldSpaceVertices The vertices of the curve, in world space @param bClosed Whether the curve is closed, i.e. should include an edge from the last vertex back to the first vertex @param ReferenceTransform The transform that would take the curve vertices from local space to world space Note: The first curve's Reference Transform is used as the local reference frame for the triangulation, and will be the operator's Result Transform
- L120 _public member_ `double UVScaleFactor = 1.0;` — Scaling applied to the default UV values
- L123 _public member_ `bool bWorldSpaceUVScale = false;` — If true, UVs will be consistently scaled relative to the world space, otherwise UVs will be relative to the mesh bounds.
- L126 _public member_ `double Thickness = 0.0;` — If > 0, thicken the result mesh to make a solid
- L128 _public member_ `EFlattenCurveMethod FlattenMethod = EFlattenCurveMethod::DoNotFlatten;`
- L132 _public member_ `ECombineCurvesMethod CombineMethod = ECombineCurvesMethod::LeaveSeparate;`
- L134 _public member_ `EOffsetClosedCurvesMethod OffsetClosedMethod = EOffsetClosedCurvesMethod::DoNotOffset;`
- L135 _public member_ `EOffsetOpenCurvesMethod OffsetOpenMethod = EOffsetOpenCurvesMethod::TreatAsClosed;`
- L136 _public member_ `EOffsetJoinMethod OffsetJoinMethod = EOffsetJoinMethod::Square;`
- L137 _public member_ `EOpenCurveEndShapes OpenEndShape = EOpenCurveEndShapes::Square;`
- L138 _public member_ `double MiterLimit = 1.0;`
- L139 _public member_ `double CurveOffset = 1.0;`
- L141 _public member_ `bool bFlipResult = false;`
- L146 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator interface
- L157 _private member_ `TArray<FCurvePath> Paths;` — Paths for all splines, in world space
- L160 _private member_ `FTransform FirstPathTransform;` — Local to World transform of the first path
- L162 _private prototype_ `void ApplyThickness(double UseUVScaleFactor);`

#### struct `UE::Geometry::FTriangulateCurvesOp::FCurvePath`  
`struct FCurvePath`  
_L150-154_
- L152 _public member_ `bool bClosed = false;`
- L153 _public member_ `TArray<FVector3d> Vertices;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L86 _namespace_ `namespace UE`
- L87 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CuttingOps/EdgeLoopInsertionOp.h` (Public)


#### class `UE::Geometry::FEdgeLoopInsertionOp`  
`class FEdgeLoopInsertionOp : public FDynamicMeshOperator`  
_L18-58_
- inherits: `FDynamicMeshOperator`
- L21 _public prototype_ `virtual ~FEdgeLoopInsertionOp() = default;`
- L24 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Inputs:
- L25 _public member_ `TSharedPtr<const FGroupTopology, ESPMode::ThreadSafe> OriginalTopology;`
- L26 _public member_ `FGroupEdgeInserter::EInsertionMode Mode;`
- L27 _public member_ `double VertexTolerance;` — TODO: Add some defaults
- L28 _public member_ `int32 GroupEdgeID = FDynamicMesh3::InvalidID;`
- L29 _public member_ `TArray<double> InputLengths;`
- L30 _public member_ `bool bInputsAreProportions = false;`
- L31 _public member_ `int32 StartCornerID = FDynamicMesh3::InvalidID;`
- L35 _public member_ `TSet<int32> LoopEids;` — Outputs: Edge IDs in the ResultMesh corresponding to the loop.
- L38 _public member_ `TSharedPtr<TSet<int32>, ESPMode::ThreadSafe> ChangedTids;` — IDs of triangles in the OriginalMesh that were changed or deleted.
- L42 _public member_ `TSet<int32> ProblemGroupEdgeIDs;` — IDs of group edges in OriginalTopology that surround non-quad-like regions that stopped the loop.
- L44 _public member_ `TSharedPtr<FGroupTopology, ESPMode::ThreadSafe> ResultTopology;`
- L45 _public member_ `bool bSucceeded = false;`
- L47 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L54 _public prototype_ `void GetLoopEdgeLocations(TArray<TPair<FVector3d, FVector3d>>& EndPointPairsOut) const;` — Converts LoopEids into pairs of endpoints, since ResultMesh is inaccessible without extracting it. Can be used to render the added loops. Clears EndPointPairsOut before use.
- L57 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator implementation

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CuttingOps/GroupEdgeInsertionOp.h` (Public)


#### class `UE::Geometry::FGroupEdgeInsertionOp`  
`class FGroupEdgeInsertionOp : public FDynamicMeshOperator`  
_L19-61_
- inherits: `FDynamicMeshOperator`
- L22 _public prototype_ `virtual ~FGroupEdgeInsertionOp() = default;`
- L25 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Inputs:
- L26 _public member_ `TSharedPtr<const FGroupTopology, ESPMode::ThreadSafe> OriginalTopology;`
- L27 _public member_ `FGroupEdgeInserter::EInsertionMode Mode;`
- L28 _public member_ `double VertexTolerance = KINDA_SMALL_NUMBER * 10;`
- L30 _public member_ `FGroupEdgeInserter::FGroupEdgeSplitPoint StartPoint;`
- L31 _public member_ `FGroupEdgeInserter::FGroupEdgeSplitPoint EndPoint;`
- L33 _public member_ `int32 CommonGroupID = FDynamicMesh3::InvalidID;`
- L34 _public member_ `int32 CommonBoundaryIndex = 0;`
- L37 _public member_ `bool bShowingBaseMesh = false;` — This overrides the behavior to revert to the original mesh when CalculateResult is called.
- L42 _public member_ `TSet<int32> Eids;` — Edge ID's in the ResultMesh that together make up the new group edge.
- L45 _public member_ `TSharedPtr<TSet<int32>, ESPMode::ThreadSafe> ChangedTids;` — Triangle ID's in the OriginalMesh that got changed or deleted in the operation.
- L47 _public member_ `TSharedPtr<FGroupTopology, ESPMode::ThreadSafe> ResultTopology;`
- L48 _public member_ `bool bSucceeded = false;`
- L50 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L57 _public prototype_ `void GetEdgeLocations(TArray<TPair<FVector3d, FVector3d>>& EndPointPairsOut) const;` — Converts GroupEdgeEids into pairs of endpoints, since ResultMesh is inaccessible without extracting it. Can be used to render the added loops. Clears EndPointPairsOut before use.
- L60 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator implementation

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/CuttingOps/PlaneCutOp.h` (Public)


#### class `UE::Geometry::FPlaneCutOp`  
`class FPlaneCutOp : public FDynamicMeshOperator`  
_L18-41_
- inherits: `FDynamicMeshOperator`
- L21 _public prototype_ `virtual ~FPlaneCutOp() = default;`
- L24 _public member_ `FVector3d LocalPlaneOrigin, LocalPlaneNormal;` — inputs
- L24 _public member_ `FVector3d LocalPlaneOrigin, LocalPlaneNormal;` — inputs
- L25 _public member_ `bool bFillCutHole = true;`
- L26 _public member_ `bool bFillSpans = false;`
- L27 _public member_ `bool bKeepBothHalves = false;`
- L28 _public member_ `bool bSimplifyAlongNewEdges = true;`
- L29 _public member_ `double CutPlaneLocalThickness = 0;` — plane thickness in the local space of the mesh
- L30 _public member_ `double UVScaleFactor = 0;`
- L31 _public member_ `static const FName ObjectIndexAttribute;`
- L32 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L34 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L40 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/DeformationOps/ExtrudeOp.h` (Public)


#### class `UE::Geometry::FExtrudeOp`  
`class FExtrudeOp : public FDynamicMeshOperator`  
_L16-82_
- inherits: `FDynamicMeshOperator`
- L49 _public prototype_ `virtual ~FExtrudeOp() = default;`
- L52 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Inputs:
- L53 _public member_ `TArray<int32> TriangleSelection;`
- L54 _public member_ `double ExtrudeDistance = 0;`
- L55 _public member_ `EExtrudeMode ExtrudeMode = EExtrudeMode::MoveAndStitch;`
- L56 _public member_ `EDirectionMode DirectionMode = EDirectionMode::SelectedTriangleNormalsEven;`
- L57 _public member_ `double MaxScaleForAdjustingTriNormalsOffset = 4.0;`
- L59 _public member_ `FVector3d MeshSpaceExtrudeDirection;` — Only used if DirectionMode is SingleDirection
- L62 _public member_ `bool bUseColinearityForSettingBorderGroups = true;` — Used when setting groups for the sides when the extrusion includes a mesh border. When true, different groups are added based on colinearity of the border edges.
- L63 _public member_ `float UVScaleFactor = 1.0f;`
- L66 _public member_ `bool bShellsToSolids = true;` — Controls whether extruding an entire open-border patch should create a solid or an open shell
- L69 _public member_ `TArray<int32> ExtrudedFaceNewGids;` — Outputs
- L71 _public function_ `void SetTransform(const FTransformSRT3d& Transform)`
- L77 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator implementation
- L80 _protected prototype_ `virtual bool BooleanExtrude(FProgressCancel* Progress);`
- L81 _protected prototype_ `virtual bool MoveAndStitchExtrude(FProgressCancel* Progress);`

#### enum `UE::Geometry::FExtrudeOp::EExtrudeMode`  
`enum class EExtrudeMode`  
_L19-29_
- L23 _public enumerator_ `MoveAndStitch` — Performs extrusion by shifting the selected faces as stitching them to the border left behind.
- L28 _public enumerator_ `Boolean` — Performs the extrusion by extruding selected faces into a closed mesh first, and then performing a boolean with the original mesh. This allows the extrusion to cut holes through the mesh or to bridge sections.

#### enum `UE::Geometry::FExtrudeOp::EDirectionMode`  
`enum class EDirectionMode`  
_L31-46_
- L35 _public enumerator_ `SelectedTriangleNormals = 0` — Take the angle-weighed average of the selected triangles around each extruded vertex to determine vertex movement direction.
- L39 _public enumerator_ `SelectedTriangleNormalsEven = 1` — Like Selected Triangle Normals, but also adjusts the distances moved in an attempt to keep triangles parallel to their original facing.
- L42 _public enumerator_ `VertexNormals = 2` — Vertex normals, regardless of selection.
- L45 _public enumerator_ `SingleDirection = 3` — Extrude all triangles in the same direction regardless of their facing.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/DeformationOps/LatticeDeformerOp.h` (Public)


#### class `UE::Geometry::FLatticeDeformerOp`  
`class FLatticeDeformerOp : public FDynamicMeshOperator`  
_L17-48_
- inherits: `FDynamicMeshOperator`
- L21 _public prototype_ `FLatticeDeformerOp(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InOriginalMesh, TSharedPtr<UE::Geometry::FFFDLattice, ESPMode::ThreadSafe> InLattice, const TArray<FVector3d>& InLatticeControlPoints, UE::Geometry::ELatticeInterpolation InInterpolationType, bool bInDeformNormals);`
- L27 _public prototype_ `FLatticeDeformerOp(TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InOriginalMesh, TSharedPtr<FDynamicSubmesh3, ESPMode::ThreadSafe> InSubmesh, FTransform3d InWorldTransform, TSharedPtr<UE::Geometry::FFFDLattice, ESPMode::ThreadSafe> InLattice, const TArray<FVector3d>& InLatticeControlPoints, UE::Geometry::ELatticeInterpolation InInterpolationType, bool bInDeformNormals);`
- L36 _public prototype_ `void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator implementation
- L41 _protected member_ `const TSharedPtr<const UE::Geometry::FFFDLattice, ESPMode::ThreadSafe> Lattice;` — Inputs
- L42 _protected member_ `const TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L43 _protected member_ `const TSharedPtr<const FDynamicSubmesh3, ESPMode::ThreadSafe> Submesh;`
- L44 _protected member_ `const FTransform3d WorldTransform;`
- L45 _protected member_ `const TArray<FVector3d> LatticeControlPoints;`
- L46 _protected member_ `UE::Geometry::ELatticeInterpolation InterpolationType;`
- L47 _protected member_ `bool bDeformNormals = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/DeformationOps/MeshOffsetOps.h` (Public)


#### class `UE::Geometry::FMeshOffsetBaseOp`  
`class FMeshOffsetBaseOp : public FSimpleMeshProcessingBaseOp`  
_L27-127_
- inherits: `FSimpleMeshProcessingBaseOp`
- desc: Base class for Mesh Offset operations (ie displacement along some kind of normal) Optionally duplicates input mesh and joins the two together, either by welding along shared border or creating quad-strip join.
- L31 _public function_ `FMeshOffsetBaseOp(const FDynamicMesh3* Mesh) : FSimpleMeshProcessingBaseOp(Mesh)`
- L35 _public prototype_ `virtual void CalculateOffset(FProgressCancel* Progress) = 0;` — subclasses must implement this function, it should update ResultMesh
- L38 _public member_ `FInterval1d OffsetRange = FInterval1d(0.0, 1.0);` — positive range of offset distances (default offset will be max value unless there is a weightmap)
- L40 _public member_ `double OffsetSign = 1.0;` — sign of offset, should be +1 or -1
- L42 _public member_ `TSharedPtr<FMeshNormals> BaseNormals;`
- L43 _public member_ `FMeshBoundaryCache BoundaryCache;`
- L45 _public member_ `TSharedPtr<UE::Geometry::FMeshBoundaryLoops> BoundaryLoops;`
- L46 _public member_ `bool bFixedBoundary = false;`
- L48 _public member_ `bool bCreateShell = false;`
- L50 _public member_ `TSharedPtr<UE::Geometry::FIndexedWeightMap1f> WeightMap;`
- L51 _public member_ `bool bUseWeightMap = false;`
- L54 _public function_ `double GetOffsetDistance(int32 VertexID, double DefaultValue = 1.0) const` — @return signed offset distance at vertex, transformed by weight map iv applicable
- L62 _public function_ `virtual void CalculateResult(FProgressCancel* Progress) override`

#### class `UE::Geometry::FIterativeOffsetMeshOp`  
`class FIterativeOffsetMeshOp : public FMeshOffsetBaseOp`  
_L134-306_
- inherits: `FMeshOffsetBaseOp`
- L137 _public function_ `FIterativeOffsetMeshOp(const FDynamicMesh3* Mesh) : FMeshOffsetBaseOp(Mesh)`
- L139 _public member_ `int32 Steps = 1;`
- L140 _public member_ `double SmoothAlpha = 0.1;`
- L141 _public member_ `bool bReprojectSmooth = false;`
- L142 _public member_ `double BoundaryAlpha = 0.2;` — should not be > 0.9
- L144 _public function_ `virtual void CalculateOffset(FProgressCancel* Progress) override`
- L156 _public function_ `void Offset(FProgressCancel* Progress)`
- L212 _public function_ `void Offset_Smoothed(FProgressCancel* Progress)`

#### class `UE::Geometry::FLaplacianOffsetMeshOp`  
`class FLaplacianOffsetMeshOp : public FMeshOffsetBaseOp`  
_L314-350_
- inherits: `FMeshOffsetBaseOp`
- L317 _public function_ `FLaplacianOffsetMeshOp(const FDynamicMesh3* Mesh) : FMeshOffsetBaseOp(Mesh)`
- L319 _public member_ `bool bUniformWeights = true;`
- L320 _public member_ `double Softness = 0;`
- L322 _public function_ `virtual void CalculateOffset(FProgressCancel* Progress) override`
- L327 _public function_ `void Offset()`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)
- L260 _function_ `` (scope `UE::Geometry::FIterativeOffsetMeshOp::Offset_Smoothed`)
- L266 _function_ `FVector3d Centroid = FMeshWeights::UniformCentroid(*ResultMesh, vid, [&](int32 nbrvid) { return PositionBuffer[nbrvid]; });` (scope `UE::Geometry::FIterativeOffsetMeshOp::Offset_Smoothed::__anon0dd0eecf0102`)
- L280 _function_ `FVector3d Centroid = FMeshWeights::FilteredUniformCentroid(*ResultMesh, vid, [&](int32 nbrvid) { return PositionBuffer[nbrvid]; }, [&](int32 nbrvid) { return BoundaryCache.bIsBoundary[nbrvid]; });` (scope `UE::Geometry::FIterativeOffsetMeshOp::Offset_Smoothed::__anon0dd0eecf0302`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/ModelingOperators.h` (Public)


#### class `UE::Geometry::FDynamicMeshOperator`  
`class FDynamicMeshOperator`  
_L20-80_
- desc: FDynamicMeshOperator is a base interface for operator implementations that can produce a FDynamicMesh3 with associated FTransformSRT3d. This class exists so we can write generic code that works with any type of mesh operation of this style.
- L23 _protected member_ `TUniquePtr<FDynamicMesh3> ResultMesh;`
- L24 _protected member_ `FTransformSRT3d ResultTransform;`
- L25 _protected member_ `FGeometryResult ResultInfo;`
- L28 _public function_ `FDynamicMeshOperator()`
- L33 _public prototype_ `virtual ~FDynamicMeshOperator() = default;`
- L38 _public function_ `virtual void SetResultTransform(const FTransformSRT3d& Transform)` — Set the output transform
- L46 _public function_ `virtual void SetResultInfo(const FGeometryResult& Info)` — Set the output information
- L54 _public function_ `TUniquePtr<FDynamicMesh3> ExtractResult()` — @return ownership of the internal mesh that CalculateResult() produced
- L62 _public function_ `const FTransformSRT3d& GetResultTransform() const` — @return the transform applied to the mesh produced by CalculateResult()
- L70 _public function_ `const FGeometryResult& GetResultInfo() const` — @return the result information returned by CalculateResult()
- L79 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) = 0;` — Calculate the result of the operator. This will populate the internal Mesh and Transform. @param Progress implementors can use this object to report progress and determine if they should halt and terminate expensive computations

#### class `UE::Geometry::IDynamicMeshOperatorFactory`  
`class IDynamicMeshOperatorFactory`  
_L90-96_
- desc: A IDynamicMeshOperatorFactory is a base interface to a factory that creates FDynamicMeshOperators
- L93 _public prototype_ `virtual ~IDynamicMeshOperatorFactory() = default;`
- L95 _public prototype_ `virtual TUniquePtr<FDynamicMeshOperator> MakeNewOperator() = 0;`

#### class `UE::Geometry::TGenericDataOperator`  
`template<typename ResultType> class TGenericDataOperator`  
_L111-151_
- desc: TGenericDataOperator is a base interface for operator implementations that can produce an object of arbitrary data type. Ownership is unique, ie the Operator calculates the result and then the caller takes it via ExtractResult()
- L114 _protected member_ `TUniquePtr<ResultType> Result;`
- L118 _public typedef_ `using ResultTypeName = ResultType;`
- L120 _public function_ `TGenericDataOperator(bool bCreateInitialObject = true)`
- L128 _public prototype_ `virtual ~TGenericDataOperator() = default;`
- L133 _public function_ `void SetResult(TUniquePtr<ResultType>&& ResultIn)` — Set the result of the Operator (generally called by CalculateResult() implementation)
- L141 _public function_ `TUniquePtr<ResultType> ExtractResult()` — @return ownership of the internal data that CalculateResult() produced
- L150 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) = 0;` — Calculate the result of the operator. This must populate the internal Result data @param Progress implementors can use this object to report progress and determine if they should halt and terminate expensive computations

#### class `UE::Geometry::IGenericDataOperatorFactory`  
`template<typename ResultType> class IGenericDataOperatorFactory`  
_L162-168_
- desc: A IDynamicMeshOperatorFactory is a base interface to a factory that creates TGenericDataOperator instances that create the given ResultType
- L165 _public prototype_ `virtual ~IGenericDataOperatorFactory() = default;`
- L167 _public prototype_ `virtual TUniquePtr<TGenericDataOperator<ResultType>> MakeNewOperator() = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/ModelingOperatorsModule.h` (Public)


#### class `FModelingOperatorsModule`  
`class FModelingOperatorsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/ModelingTaskTypes.h` (Public)


#### class `UE::Geometry::TDeleterTask`  
`template<typename DeleteTaskType> class TDeleterTask : public FNonAbandonableTask`  
_L27-54_
- inherits: `FNonAbandonableTask`
- desc: TDeleterTask is a task that takes ownership of another FAsyncTask that is (presumably) still executing some operation. The DeleterTask waits for this FAsyncTask to complete, and then deletes it. TDeleterTask should be launched as a background task via FAutoDeleteAsyncTask, see FAsyncTaskExecuterWithAbort::CancelAndDelete for an example.
- L31 _public function_ `TDeleterTask(FAsyncTask<DeleteTaskType>* TaskIn) : Task(TaskIn)`
- L36 _public member_ `FAsyncTask<DeleteTaskType>* Task;` — The task we will delete, when it completes
- L38 _public function_ `void DoWork()`
- L50 _public function_ `inline TStatId GetStatId() const` — required for task system

#### class `UE::Geometry::FAsyncTaskExecuterWithAbort`  
`template<typename TTask> class FAsyncTaskExecuterWithAbort : public FAsyncTask<TTask>`  
_L73-108_
- inherits: `FAsyncTask<TTask>`
- desc: FAsyncTaskExecuterWithAbort is an extension of FAsyncTask that adds a bAbort flag. This flag is passed to the target TTask via a new function that it must implemented, SetAbortSource(). If the task-executing source wishes to cancel the contained task, then it calls CancelAndDelete(). This sets the abort flag to true, and spanws a TDeleterTask that will take ownership of the now-discarded background task, watch for it to be complete, and delete it, then delete itself. So after calling CancelAndDelete() the task-executing source may discard any reference to the original FAsyncTask (but not delete it!) @warning keep in mind that the target TTask may not terminate immediately (hence all the machinery). It may continue to use resources/CPU for some time.
- L77 _public member_ `bool bAbort = false;` — Set to true to abort the child task. CancelAndDelete() should be used in most cases, instead of changing bAbort directly.
- L80 _public member_ `TSharedPtr<std::atomic<int>> TaskCounter;` — Optional counter, if set will be decremented on task destruction
- L83 _public function_ `template <typename Arg0Type, typename... ArgTypes> FAsyncTaskExecuterWithAbort(Arg0Type&& Arg0, ArgTypes&&... Args) : FAsyncTask<TTask>(Forward<Arg0Type>(Arg0), Forward<ArgTypes>(Args)...)`
- L90 _public function_ `virtual ~FAsyncTaskExecuterWithAbort()`
- L103 _public function_ `void CancelAndDelete()` — Tells the child FAbandonableTask to terminate itself, via the bAbort flag passed in SetAbortSource, and then starts a TDeleterTask that waits for completion to delete this task.

#### class `UE::Geometry::FAsyncTaskExecuterWithProgressCancel`  
`template<typename TTask> class FAsyncTaskExecuterWithProgressCancel : public FAsyncTaskExecuterWithAbort<TTask>`  
_L114-164_
- inherits: `FAsyncTaskExecuterWithAbort<TTask>`
- desc: An extension of FAsyncTaskExecuterWithAbort that requires the task have a GetProgress() function Intended to be used with FAbortableBackgroundTask Provides a PollProgress method to report out task progress
- L117 _protected member_ `FProgressCancel* Progress = nullptr;`
- L118 _protected member_ `float LastProgressFrac;`
- L119 _protected member_ `FText LastProgressMessage;`
- L125 _public function_ `template <typename Arg0Type, typename... ArgTypes> FAsyncTaskExecuterWithProgressCancel(Arg0Type&& Arg0, ArgTypes&&... Args) : FAsyncTaskExecuterWithAbort<TTask>(Forward<Arg0Type>(Arg0), Forward<ArgTypes>(Args)...)`
- L133 _public function_ `bool PollProgress(float& OutProgressFrac, FText& OutProgressMessage)`

#### class `UE::Geometry::FAbortableBackgroundTask`  
`class FAbortableBackgroundTask : public FNonAbandonableTask`  
_L178-210_
- inherits: `FNonAbandonableTask`
- desc: FAbortableBackgroundTask is a FNonAbandonableTask intended for long-running background computations that might need to be interrupted, such as expensive operations driven by a UI tool that the user may wish to cancel. This class is intended to be used with FAsyncTaskExecuterWithAbort. In that case the SetAbortSource() function will be automatically called/configured. A FProgressCancel object can be returned which will allow expensive computations to check the value of this internal flag.
- L182 _private member_ `bool* bExternalAbortFlag = nullptr;` — pointer to a bool owned somewhere else. If that bool becomes true, this task should cancel further computation
- L184 _private member_ `FProgressCancel Progress;` — Internal ProgressCancel instance that can be passed to expensive compute functions, etc
- L188 _public function_ `FAbortableBackgroundTask()`
- L194 _public function_ `void SetAbortSource(bool* bAbortFlagLocation)` — Set the abort source flag.
- L200 _public function_ `bool IsAborted() const` — @return true if the task should stop computation
- L206 _public function_ `FProgressCancel* GetProgress()` — @return pointer to internal progress object which can be passed to expensive child computations

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)
- L190 _function_ `Progress.CancelF = [this]()` (scope `UE::Geometry::FAbortableBackgroundTask::FAbortableBackgroundTask`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/ParameterizationOps/RecomputeUVsOp.h` (Public)


#### enum `UE::Geometry::ERecomputeUVsUnwrapType`  
`enum class ERecomputeUVsUnwrapType`  
_L24-29_
- L26 _public enumerator_ `ExpMap = 0`
- L27 _public enumerator_ `ConformalFreeBoundary = 1`
- L28 _public enumerator_ `SpectralConformal = 2`

#### enum `UE::Geometry::ERecomputeUVsIslandMode`  
`enum class ERecomputeUVsIslandMode`  
_L33-37_
- L35 _public enumerator_ `PolyGroups = 0`
- L36 _public enumerator_ `UVIslands = 1`

#### class `UE::Geometry::FRecomputeUVsOp`  
`class FRecomputeUVsOp : public FDynamicMeshOperator`  
_L40-129_
- inherits: `FDynamicMeshOperator`
- L43 _public prototype_ `virtual ~FRecomputeUVsOp() = default;`
- L50 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;` — source mesh
- L53 _public member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> InputGroups;` — source groups (optional)
- L56 _public member_ `bool bAutoRotate = true;` — orientation control
- L59 _public member_ `bool bPackToOriginalBounds = false;` — Individual packing
- L62 _public member_ `bool bNormalizeAreas = true;` — area scaling
- L63 _public member_ `float AreaScaling = 1.0;`
- L66 _public member_ `int32 UVLayer = 0;` — UV layer
- L69 _public member_ `bool bPackUVs = true;` — Atlas Packing parameters
- L70 _public member_ `int32 PackingTextureResolution = 512;`
- L71 _public member_ `float PackingGutterWidth = 1.0f;`
- L73 _public member_ `ERecomputeUVsUnwrapType UnwrapType = ERecomputeUVsUnwrapType::ExpMap;`
- L74 _public member_ `ERecomputeUVsIslandMode IslandMode = ERecomputeUVsIslandMode::PolyGroups;`
- L79 _public member_ `bool bPreserveIrregularity = false;` — Spectral Conformal Map Options
- L84 _public member_ `int32 NormalSmoothingRounds = 0;` — ExpMap Options
- L85 _public member_ `double NormalSmoothingAlpha = 0.25;`
- L90 _public member_ `bool bMergingOptimization = false;` — Patch Merging options
- L91 _public member_ `double MergingThreshold = 1.5;`
- L92 _public member_ `double CompactnessThreshold = 9999999.0;` — effectively disabled as it usually is not a good idea
- L93 _public member_ `double MaxNormalDeviationDeg = 45.0;`
- L96 _public member_ `bool bUDIMsEnabled = false;` — UDIM options
- L99 _public member_ `TOptional<TSet<int32>> Selection;` — Selection
- L102 _public function_ `void SetTransform(const FTransformSRT3d& XForm)` — set ability on protected transform.
- L111 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L119 _protected prototype_ `bool IsValid() const;` — Check if operation is valid to do work. It may not be valid if there are conflicting or inconsistent options passed to it from the user.
- L121 _protected member_ `FGeometryResult NewResultInfo;`
- L123 _protected prototype_ `void NormalizeUVAreas(const FDynamicMesh3& Mesh, FDynamicMeshUVOverlay* Overlay, const TileConnectedComponents& TileComponents, float GlobalScale = 1.0f);`
- L125 _protected prototype_ `void CollectIslandComponentsPerTile(const FDynamicMeshUVOverlay& UVOverlay, TArray< TileConnectedComponents >& ComponentsPerTile, bool& UseExistingUVTopology);`
- L127 _protected prototype_ `virtual bool CalculateResult_Basic(FProgressCancel* Progress);`
- L128 _protected prototype_ `virtual bool CalculateResult_RegionOptimization(FProgressCancel* Progress);`

#### class `URecomputeUVsOpFactory`  
`class URecomputeUVsOpFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L142-160_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Can be hooked up to a UMeshOpPreviewWithBackgroundCompute to perform UV solving operations. Inherits from UObject so that it can hold a strong pointer to the settings UObject, which needs to be a UObject to be displayed in the details panel.
- L149 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L152 _public member_ `TObjectPtr<URecomputeUVsToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L154 _public member_ `TOptional<TSet<int32>> Selection;`
- L156 _public member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> InputGroups;`
- L157 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L158 _public function_ `TUniqueFunction<int32()> GetSelectedUVChannel = []()`
- L158 _public member_ `TUniqueFunction<int32()> GetSelectedUVChannel = []() { return 0; };`
- L159 _public member_ `UE::Geometry::FTransformSRT3d TargetTransform;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/ParameterizationOps/TexelDensityOp.h` (Public)


#### enum `ETexelDensityToolMode`  
`enum class ETexelDensityToolMode`  
_L16-21_
- reflection: `UENUM()`
- L18 _public enumerator_ `ApplyToIslands`
- L19 _public enumerator_ `ApplyToWhole`
- L20 _public enumerator_ `Normalize`

#### class `UUVEditorTexelDensitySettings`  
`class UUVEditorTexelDensitySettings : public UInteractiveToolPropertySet`  
_L24-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L30 _public prototype_ `virtual bool InSamplingMode() const;` — `UFUNCTION()`
- L33 _public member_ `ETexelDensityToolMode TexelDensityMode = ETexelDensityToolMode::ApplyToIslands;` — `UPROPERTY(EditAnywhere, Category = "TexelDensity", meta = (DisplayName = "Scale Mode", EditCondition = "!InSamplingMode" ))`
- L36 _public member_ `float TargetWorldUnits = 100;` — `UPROPERTY(EditAnywhere, Category = "TexelDensity", meta = (DisplayName = "World Units", EditCondition = "TexelDensityMode != ETexelDensityToolMode::Normalize"))`
- L39 _public member_ `float TargetPixelCount = 1024;` — `UPROPERTY(EditAnywhere, Category = "TexelDensity", meta = (DisplayName = "Pixels", EditCondition = "TexelDensityMode != ETexelDensityToolMode::Normalize && !InSamplingMode"))`
- L42 _public member_ `float TextureResolution = 1024;` — `UPROPERTY(EditAnywhere, Category = "TexelDensity", meta = (DisplayName = "Texture Dimensions", EditCondition = "TexelDensityMode != ETexelDensityToolMode::Normalize && !InSamplingMode", LinearDeltaSensitivity = 1000, Delta = 64, SliderExponent = 1, UIMin = 2, UIMax = 16384))`
- L45 _public member_ `bool bEnableUDIMLayout = false;` — `UPROPERTY(EditAnywhere, Category = "TexelDensity", meta = (DisplayName = "Use UDIMs", EditCondition = "TexelDensityMode != ETexelDensityToolMode::Normalize && !InSamplingMode", TransientToolProperty))`

#### enum `UE::Geometry::EUVTexelDensityOpModes`  
`enum class EUVTexelDensityOpModes`  
_L56-61_
- L58 _public enumerator_ `ScaleGlobal = 0`
- L59 _public enumerator_ `ScaleIslands = 1`
- L60 _public enumerator_ `Normalize = 2`

#### class `UE::Geometry::FUVEditorTexelDensityOp`  
`class FUVEditorTexelDensityOp : public FDynamicMeshOperator`  
_L63-96_
- inherits: `FDynamicMeshOperator`
- L66 _public prototype_ `virtual ~FUVEditorTexelDensityOp() = default;`
- L69 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — inputs
- L71 _public member_ `EUVTexelDensityOpModes TexelDensityMode = EUVTexelDensityOpModes::ScaleGlobal;`
- L73 _public member_ `int UVLayerIndex = 0;`
- L74 _public member_ `int TextureResolution = 1024;`
- L75 _public member_ `int TargetWorldSpaceMeasurement = 100;`
- L76 _public member_ `int TargetPixelCountMeasurement = 1024;`
- L78 _public member_ `bool bMaintainOriginatingUDIM = false;`
- L79 _public member_ `TOptional<TSet<int32>> Selection;`
- L80 _public member_ `TOptional<TMap<int32, int32>> TextureResolutionPerUDIM;`
- L81 _public member_ `FVector2f UVTranslation = FVector2f::Zero();`
- L83 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L89 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L92 _protected prototype_ `void ExecutePacker(FDynamicMeshUVPacker& Packer);`
- L93 _protected prototype_ `void ScaleMeshSubRegionByDensity(FDynamicMeshUVOverlay* UVLayer, const TArray<int32>& Tids, TSet<int32>& UVElements, int32 TileResolution);`

#### class `UUVTexelDensityOperatorFactory`  
`class UUVTexelDensityOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L108-124_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Can be hooked up to a UMeshOpPreviewWithBackgroundCompute to perform UV Layout operations. Inherits from UObject so that it can hold a strong pointer to the settings UObject, which needs to be a UObject to be displayed in the details panel.
- L114 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L117 _public member_ `TObjectPtr<UUVEditorTexelDensitySettings> Settings;` — `UPROPERTY()`
- L119 _public member_ `TOptional<TSet<int32>> Selection;`
- L120 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L121 _public function_ `TUniqueFunction<int32()> GetSelectedUVChannel = []()`
- L121 _public member_ `TUniqueFunction<int32()> GetSelectedUVChannel = []() { return 0; };`
- L122 _public member_ `FTransform TargetTransform;`
- L123 _public member_ `TOptional<TMap<int32, int32>> TextureResolutionPerUDIM;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L49 _namespace_ `namespace UE`
- L51 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/ParameterizationOps/UVLayoutOp.h` (Public)


#### enum `UE::Geometry::EUVLayoutOpLayoutModes`  
`enum class EUVLayoutOpLayoutModes`  
_L22-28_
- L24 _public enumerator_ `TransformOnly = 0`
- L25 _public enumerator_ `RepackToUnitRect = 1`
- L26 _public enumerator_ `StackInUnitRect = 2`
- L27 _public enumerator_ `Normalize = 3`

#### class `UE::Geometry::FUVLayoutOp`  
`class FUVLayoutOp : public FDynamicMeshOperator`  
_L30-63_
- inherits: `FDynamicMeshOperator`
- L33 _public prototype_ `virtual ~FUVLayoutOp() = default;`
- L36 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — inputs
- L38 _public member_ `EUVLayoutOpLayoutModes UVLayoutMode = EUVLayoutOpLayoutModes::RepackToUnitRect;`
- L40 _public member_ `int UVLayerIndex = 0;`
- L41 _public member_ `int TextureResolution = 128;`
- L42 _public member_ `bool bPreserveScale = false;`
- L43 _public member_ `bool bPreserveRotation = false;`
- L44 _public member_ `bool bAllowFlips = false;`
- L45 _public member_ `bool bAlwaysSplitBowties = true;`
- L46 _public member_ `float UVScaleFactor = 1.0;`
- L47 _public member_ `float GutterSize = 1.0;`
- L48 _public member_ `bool bMaintainOriginatingUDIM = false;`
- L49 _public member_ `TOptional<TSet<int32>> Selection;`
- L50 _public member_ `TOptional<TMap<int32, int32>> TextureResolutionPerUDIM;`
- L51 _public member_ `FVector2f UVTranslation = FVector2f::Zero();`
- L53 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L59 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L62 _protected prototype_ `void ExecutePacker(FDynamicMeshUVPacker& Packer);`

#### class `UUVLayoutOperatorFactory`  
`class UUVLayoutOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L75-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Can be hooked up to a UMeshOpPreviewWithBackgroundCompute to perform UV Layout operations. Inherits from UObject so that it can hold a strong pointer to the settings UObject, which needs to be a UObject to be displayed in the details panel.
- L81 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L84 _public member_ `TObjectPtr<UUVLayoutProperties> Settings;` — `UPROPERTY()`
- L85 _public member_ `TOptional<TSet<int32>> Selection;`
- L86 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L87 _public function_ `TUniqueFunction<int32()> GetSelectedUVChannel = []()`
- L87 _public member_ `TUniqueFunction<int32()> GetSelectedUVChannel = []() { return 0; };`
- L88 _public member_ `FTransform TargetTransform;`
- L89 _public member_ `TOptional<TMap<int32, int32>> TextureResolutionPerUDIM;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/ParameterizationOps/UVProjectionOp.h` (Public)


#### enum `EUVProjectionMethod`  
`enum class EUVProjectionMethod : uint8`  
_L15-25_
- reflection: `UENUM()`
- L18 _public enumerator_ `Box` — Calculate UVs by assigning triangles to faces of a box, and then apply per-box-face planar projection
- L20 _public enumerator_ `Cylinder` — Calculate UVs by assigning triangles to a cylinder using radial projection or cylinder end caps using planar projection
- L22 _public enumerator_ `Plane` — Calculate UVs by projecting to a plane
- L24 _public enumerator_ `ExpMap UMETA(DisplayName = "ExpMap")` — Calculate UVs by Exponential Map projection centered at the surface point nearest to the center of the input plane

#### class `UE::Geometry::FUVProjectionOp`  
`class FUVProjectionOp : public FDynamicMeshOperator`  
_L32-75_
- inherits: `FDynamicMeshOperator`
- L35 _public prototype_ `virtual ~FUVProjectionOp() = default;`
- L38 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — inputs
- L39 _public member_ `TSharedPtr<TArray<int32>, ESPMode::ThreadSafe> TriangleROI;`
- L40 _public member_ `int32 UseUVLayer = 0;`
- L43 _public member_ `FTransformSRT3d MeshToProjectionSpace;` — transform from Mesh into space of Projection Geometry
- L45 _public member_ `EUVProjectionMethod ProjectionMethod = EUVProjectionMethod::Box;`
- L46 _public member_ `FOrientedBox3d ProjectionBox;`
- L47 _public member_ `int32 MinRegionSize = 2;`
- L48 _public member_ `float CylinderSplitAngle = 45.0f;`
- L51 _public member_ `double BlendWeight = 0.0;` — ExpMap parameters for modifying normals
- L52 _public member_ `int32 SmoothingRounds = 0;`
- L53 _public member_ `double SmoothingAlpha = 0.5;`
- L56 _public member_ `FVector2f UVOrigin = FVector2f(0.5f,0.5f);` — position to use as UV origin
- L58 _public member_ `float UVRotationAngleDeg = 0.0;` — rotation applied to computed UVs
- L60 _public member_ `FVector2f UVScale = FVector2f::One();` — scale applied to computed UVs
- L62 _public member_ `FVector2f UVTranslate = FVector2f::Zero();` — translation applied to computed UVs
- L68 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator implementation
- L71 _public prototype_ `virtual void CalculateResult_Box(FProgressCancel* Progress);`
- L72 _public prototype_ `virtual void CalculateResult_Plane(FProgressCancel* Progress);`
- L73 _public prototype_ `virtual void CalculateResult_ExpMap(FProgressCancel* Progress);`
- L74 _public prototype_ `virtual void CalculateResult_Cylinder(FProgressCancel* Progress);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L27 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/PolyModelingOps/LinearExtrusionOp.h` (Public)


#### class `UE::Geometry::FLinearExtrusionOp`  
`class FLinearExtrusionOp : public FDynamicMeshOperator`  
_L21-126_
- inherits: `FDynamicMeshOperator`
- desc: LinearExtrusionOp extrudes a set of triangles of a mesh in a linear direction, with various options for how to process that extrusion.
- L24 _public prototype_ `virtual ~FLinearExtrusionOp() = default;`
- L31 _public member_ `TSharedPtr<FSharedConstDynamicMesh3> OriginalMeshShared;` — Handle to the source DynamicMesh
- L34 _public member_ `TArray<int32> TriangleSelection;` — Triangles of the OriginalMesh that should be extruded
- L37 _public member_ `FFrame3d StartFrame = FFrame3d();` — Initial frame of the Extrusion
- L39 _public member_ `FFrame3d ToFrame = FFrame3d();` — End frame of the Extrusion
- L41 _public member_ `FVector3d Scale = FVector3d::One();` — End scale of the Extrusion, relative to initial scale (1,1,1)
- L58 _public member_ `ESelectionShapeModifierMode RegionModifierMode = ESelectionShapeModifierMode::None;` — Current modifier applied to selection region
- L61 _public member_ `double RaycastMaxDistance = 9999.0;` — In RaycastToPlane mode, if raycast distance is > this value, fallback to no shape change
- L64 _public member_ `bool bShellsToSolids = true;` — If bShellsToSolids is true, patches surrounded by mesh boundaries will be extruded into closed solids instead of open shells
- L67 _public member_ `int32 NumSubdivisions = 0;` — Number of subdivisions along the extrusion "tubes"
- L74 _public member_ `bool bInferGroupsFromNeighbours = true;` — Assign new groups to regions of the extrusion "tube" based on the existing adjacent groups before extrusion. Each (disconnected) unique pair of group IDs gets a new unique group ID on the extrusion. If disabled, the entire extrusion tube will be assigned a single new group ID
- L77 _public member_ `bool bNewGroupPerSubdivision = true;` — If true, assign a separate group for each subdivision, otherwise all subdivisions have the same group
- L80 _public member_ `bool bRemapExtrudeGroups = true;` — assign new GroupIDs to each input GroupID in the extrude area. If false, disconnected extrude areas get single new group IDs
- L83 _public member_ `double CreaseAngleThresholdDeg = 180.0;` — if the opening angle at an edge of the extrusion tube is > this threshold, "cut" any group that crosses the edge into two groups
- L86 _public member_ `double UVScaleFactor = 1.0f;` — Scaling applied to the default UV values
- L89 _public member_ `bool bUVIslandPerGroup = true;` — If true, assign a new UV island for each new group, otherwise each disconnected extrusion tube is unwrapped to a single UV island
- L92 _public member_ `int SetMaterialID = 0;` — Constant Material ID to set along the extrusion tube
- L95 _public member_ `bool bInferMaterialID = true;` — If true, Material IDs around the border of the extrude area are propagated "down" the extrusion tube
- L98 _public member_ `bool bRecomputeNormals = true;` — Determine whether normals should be recomputed
- L103 _public member_ `bool bUseColinearityForSettingBorderGroups = true;` — (this parameter may not be relevant and perhaps should be removed...) Used when setting groups for the sides when the extrusion includes a mesh border. When true, different groups are added based on colinearity of the border edges.
- L117 _public prototype_ `virtual bool CalculateResultInPlace(FDynamicMesh3& EditMesh, FProgressCancel* Progress);` — Compute result applied directly to EditMesh @return true on success, false on error or if Progress is cancelled
- L123 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator interface

#### enum `UE::Geometry::FLinearExtrusionOp::ESelectionShapeModifierMode`  
`enum class ESelectionShapeModifierMode`  
_L48-56_
- desc: Modifier applied to the selected triangles during extrusion
- L51 _public enumerator_ `None = 0` — No modification, keep the same shape
- L53 _public enumerator_ `FlattenToPlane = 1` — Project the selection vertices to the XY plane of StartFrame before extruding
- L55 _public enumerator_ `RaycastToPlane = 2` — Cast a ray for each selection vertex against plane defined by ToFrame's Orgin/Z-Axis and use the hit position

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/PolyModelingOps/RegionOffsetOp.h` (Public)


#### class `UE::Geometry::FRegionOffsetOp`  
`class FRegionOffsetOp : public FDynamicMeshOperator`  
_L21-117_
- inherits: `FDynamicMeshOperator`
- desc: RegionOffsetOp extrudes a set of triangles of a mesh in a linear direction, with various options for how to process that extrusion.
- L24 _public prototype_ `virtual ~FRegionOffsetOp() = default;`
- L31 _public member_ `TSharedPtr<FSharedConstDynamicMesh3> OriginalMeshShared;` — Handle to the source DynamicMesh
- L34 _public member_ `TArray<int32> TriangleSelection;` — Triangles of the OriginalMesh that should be extruded
- L51 _public member_ `double OffsetDistance = 1.0;`
- L53 _public member_ `EOffsetComputationMode OffsetMode = EOffsetComputationMode::ApproximateConstantThickness;`
- L57 _public member_ `bool bShellsToSolids = true;` — If bShellsToSolids is true, patches surrounded by mesh boundaries will be extruded into closed solids instead of open shells
- L60 _public member_ `int32 NumSubdivisions = 0;` — Number of subdivisions along the extrusion "tubes"
- L67 _public member_ `bool bInferGroupsFromNeighbours = true;` — Assign new groups to regions of the extrusion "tube" based on the existing adjacent groups before extrusion. Each (disconnected) unique pair of group IDs gets a new unique group ID on the extrusion. If disabled, the entire extrusion tube will be assigned a single new group ID
- L70 _public member_ `bool bNewGroupPerSubdivision = true;` — If true, assign a separate group for each subdivision, otherwise all subdivisions have the same group
- L73 _public member_ `bool bRemapExtrudeGroups = true;` — assign new GroupIDs to each input GroupID in the extrude area. If false, disconnected extrude areas get single new group IDs
- L76 _public member_ `double CreaseAngleThresholdDeg = 180.0;` — if the opening angle at an edge of the extrusion tube is > this threshold, "cut" any group that crosses the edge into two groups
- L79 _public member_ `double UVScaleFactor = 1.0f;` — Scaling applied to the default UV values
- L82 _public member_ `bool bUVIslandPerGroup = true;` — If true, assign a new UV island for each new group, otherwise each disconnected extrusion tube is unwrapped to a single UV island
- L85 _public member_ `int SetMaterialID = 0;` — Constant Material ID to set along the extrusion tube
- L88 _public member_ `bool bInferMaterialID = true;` — If true, Material IDs around the border of the extrude area are propagated "down" the extrusion tube
- L91 _public member_ `bool bRecomputeNormals = true;` — Determine whether normals should be recomputed
- L96 _public member_ `bool bUseColinearityForSettingBorderGroups = true;` — (this parameter may not be relevant and perhaps should be removed...) Used when setting groups for the sides when the extrusion includes a mesh border. When true, different groups are added based on colinearity of the border edges.
- L108 _public prototype_ `virtual bool CalculateResultInPlace(FDynamicMesh3& EditMesh, FProgressCancel* Progress);` — Compute result applied directly to EditMesh @return true on success, false on error or if Progress is cancelled
- L114 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — FDynamicMeshOperator interface

#### enum `UE::Geometry::FRegionOffsetOp::EOffsetComputationMode`  
`enum class EOffsetComputationMode`  
_L40-48_
- L43 _public enumerator_ `VertexNormals = 0`
- L45 _public enumerator_ `FaceNormals = 1`
- L47 _public enumerator_ `ApproximateConstantThickness = 2`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/Properties/RecomputeUVsProperties.h` (Public)


#### enum `ERecomputeUVsPropertiesUnwrapType`  
`enum class ERecomputeUVsPropertiesUnwrapType`  
_L13-25_
- reflection: `UENUM()`
- L18 _public enumerator_ `ExpMap = 0 UMETA(DisplayName = "ExpMap")` — ExpMap UV flattening is very fast but has limited abilities to reduce stretching and distortion
- L20 _public enumerator_ `Conformal = 1` — Conformal UV flattening is increasingly expensive on large islands but reduces distortion
- L22 _public enumerator_ `SpectralConformal = 2` — Compared to the default Conformal method does not pin two vertices along the boundary which reduces the distortion but is more expensive to compute.
- L24 _public enumerator_ `IslandMerging = 3` — UV islands will be merged into larger islands if it does not increase stretching and distortion beyond defined limits

#### enum `ERecomputeUVsPropertiesIslandMode`  
`enum class ERecomputeUVsPropertiesIslandMode`  
_L29-37_
- reflection: `UENUM()`
- L34 _public enumerator_ `PolyGroups = 0 UMETA(DisplayName = "PolyGroups")` — Use PolyGroups defined by Active PolyGroup property to define initial UV islands.
- L36 _public enumerator_ `ExistingUVs = 1` — Use existing UV Layer to define UV islands, i.e. re-solve UV flattening based on existing UVs

#### enum `ERecomputeUVsToolOrientationMode`  
`enum class ERecomputeUVsToolOrientationMode`  
_L41-47_
- reflection: `UENUM()`
- L44 _public enumerator_ `None` — Do not rotate UV islands
- L46 _public enumerator_ `MinBounds` — Automatically rotate each UV island to reduce its bounding box size

#### enum `ERecomputeUVsPropertiesLayoutType`  
`enum class ERecomputeUVsPropertiesLayoutType`  
_L51-63_
- reflection: `UENUM()`
- L54 _public enumerator_ `None` — Do not apply additional layout options to unwrapped UVs
- L56 _public enumerator_ `Repack` — Uniformly scale and translate UV islands collectively to pack them into the unit square, i.e. fit between 0 and 1 with no overlap
- L58 _public enumerator_ `NormalizeToExistingBounds` — Scale and center all islands to fit within their original bounding boxes. Only applicable if using existing UVs.
- L60 _public enumerator_ `NormalizeToBounds` — Uniformly scale UV islands such that they have constant relative area, relative to object bounds
- L62 _public enumerator_ `NormalizeToWorld` — Uniformly scale UV islands such that they have constant relative area, relative to world space

#### class `URecomputeUVsToolProperties`  
`class URecomputeUVsToolProperties : public UInteractiveToolPropertySet`  
_L67-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L73 _public member_ `bool bEnablePolygroupSupport = true;` — `UPROPERTY(meta = (TransientToolProperty))`
- L77 _public member_ `ERecomputeUVsPropertiesIslandMode IslandGeneration = ERecomputeUVsPropertiesIslandMode::ExistingUVs;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap", meta = (EditCondition = "bEnablePolygroupSupport", EditConditionHides, HideEditConditionToggle = true))` — Generation method for initial UV islands.
- L81 _public member_ `ERecomputeUVsPropertiesUnwrapType UnwrapType = ERecomputeUVsPropertiesUnwrapType::SpectralConformal;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap")` — Type of UV flattening algorithm to use
- L85 _public member_ `ERecomputeUVsToolOrientationMode AutoRotation = ERecomputeUVsToolOrientationMode::MinBounds;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap")` — Type of automatic rotation applied to each UV island
- L89 _public member_ `bool bPreserveIrregularity = true;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap", meta = (EditCondition = "UnwrapType == ERecomputeUVsPropertiesUnwrapType::SpectralConformal", EditConditionHides, HideEditConditionToggle))` — If enabled, reduces distortion for meshes with triangles of vastly different sizes, This is only enabled if the Unwrap Type is set to Spectral Conformal.
- L94 _public member_ `int SmoothingSteps = 5;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap", meta = (UIMin = "0", UIMax = "25", ClampMin = "0", ClampMax = "1000", EditCondition = "UnwrapType == ERecomputeUVsPropertiesUnwrapType::ExpMap || UnwrapType == ERecomputeUVsPropertiesUnwrapType::IslandMerging", EditConditionHides, HideEditConditionToggle))` — Number of smoothing steps to apply; this slightly increases distortion but produces more stable results. This is only enabled if the Unwrap Type is set to ExpMap or Island Merging.
- L99 _public member_ `float SmoothingAlpha = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap", meta = (UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "1.0", EditCondition = "UnwrapType == ERecomputeUVsPropertiesUnwrapType::ExpMap || UnwrapType == ERecomputeUVsPropertiesUnwrapType::IslandMerging", EditConditionHides, HideEditConditionToggle))` — Smoothing parameter; larger values result in faster smoothing in each step. This is only enabled if the Unwrap Type is set to ExpMap or Island Merging.
- L104 _public member_ `float MergingDistortionThreshold = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap", meta = (DisplayName = "Distortion Threshold", UIMin = "1.0", UIMax = "5.0", ClampMin = "1.0", EditCondition = "UnwrapType == ERecomputeUVsPropertiesUnwrapType::IslandMerging", EditConditionHides, HideEditConditionToggle))` — Threshold for stretching and distortion below which island merging is allowed; larger values increase the allowable UV distortion. This is only enabled if the Unwrap Type is set to Island Merging.
- L109 _public member_ `float MergingAngleThreshold = 45.0f;` — `UPROPERTY(EditAnywhere, Category = "UV Unwrap", meta = (DisplayName = "Angle Threshold", UIMin = "0.0", UIMax = "90.0", ClampMin = "0.0", ClampMax = "180.0", EditCondition = "UnwrapType == ERecomputeUVsPropertiesUnwrapType::IslandMerging", EditConditionHides, HideEditConditionToggle))` — Threshold for the average face normal deviation below  which island merging is allowed. This is only enabled if the Unwrap Type is set to Island Merging.
- L113 _public member_ `ERecomputeUVsPropertiesLayoutType LayoutType = ERecomputeUVsPropertiesLayoutType::Repack;` — `UPROPERTY(EditAnywhere, Category = "UV Layout")` — Uniformly scale and translate UV islands collectively to pack them into the unit square, i.e. fit between 0 and 1 with no overlap.
- L118 _public member_ `int TextureResolution = 1024;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (UIMin = "64", UIMax = "2048", ClampMin = "2", ClampMax = "4096", EditCondition = "LayoutType == ERecomputeUVsPropertiesLayoutType::Repack", EditConditionHides, HideEditConditionToggle))` — Expected resolution of the output textures; this controls spacing left between UV islands to avoid interpolation artifacts. This is only enabled when the Layout Type is set to Repack.
- L123 _public member_ `float NormalizeScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (UIMin = "0.001", UIMax = "10", ClampMin = "0.00001", ClampMax = "1000000.0", EditCondition = "LayoutType == ERecomputeUVsPropertiesLayoutType::NormalizeToBounds || LayoutType == ERecomputeUVsPropertiesLayoutType::NormalizeToWorld", EditConditionHides, HideEditConditionToggle))` — Scaling factor used for UV island normalization/scaling. This is only enabled when the Layout Type is set to Normalize to Bounds or Normalize to World.
- L127 _public member_ `bool bEnableUDIMLayout = false;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (DisplayName = "Preserve UDIMs", EditCondition = "bUDIMCVAREnabled", EditConditionHides, HideEditConditionToggle = true))` — Enable UDIM aware layout and keep islands within their originating UDIM tiles when laying out.
- L130 _public member_ `bool bUDIMCVAREnabled = false;` — `UPROPERTY(Transient)`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/Properties/UVLayoutProperties.h` (Public)


#### enum `EUVLayoutType`  
`enum class EUVLayoutType`  
_L14-24_
- reflection: `UENUM()`
- desc: UV Layout Strategies for the UV Layout Tool
- L17 _public enumerator_ `Transform` — Apply Scale and Translation properties to all UV values
- L19 _public enumerator_ `Stack` — Uniformly scale and translate each UV island individually to pack it into the unit square, i.e. fit between 0 and 1 with overlap
- L21 _public enumerator_ `Repack` — Uniformly scale and translate UV islands collectively to pack them into the unit square, i.e. fit between 0 and 1 with no overlap
- L23 _public enumerator_ `Normalize` — Scale and translate UV islands to normalize the UV islands' area to match an average texel density.

#### class `UUVLayoutProperties`  
`class UUVLayoutProperties : public UInteractiveToolPropertySet`  
_L31-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: UV Layout Settings
- L38 _public member_ `EUVLayoutType LayoutType = EUVLayoutType::Repack;` — `UPROPERTY(EditAnywhere, Category = "UV Layout")` — Type of layout applied to input UVs
- L42 _public member_ `int TextureResolution = 1024;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (UIMin = "64", UIMax = "2048", ClampMin = "2", ClampMax = "4096"))` — Expected resolution of the output textures; this controls spacing left between UV islands to avoid interpolation artifacts
- L46 _public member_ `float Scale = 1;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (UIMin = "0.1", UIMax = "5.0", ClampMin = "0.0001", ClampMax = "10000"))` — Uniform scale applied to UVs after packing
- L50 _public member_ `FVector2D Translation = FVector2D(0,0);` — `UPROPERTY(EditAnywhere, Category = "UV Layout")` — Translation applied to UVs after packing, and after scaling
- L54 _public member_ `bool bPreserveScale = false;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (EditCondition = "LayoutType == EUVLayoutType::Repack"))` — Force the Repack layout type to preserve existing scaling of UV islands. Note, this might lead to the packing not fitting within a unit square, and therefore is disabled by default.
- L58 _public member_ `bool bPreserveRotation = false;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (EditCondition = "LayoutType == EUVLayoutType::Repack"))` — Force the Repack layout type to preserve existing rotation of UV islands. Note, this might lead to the packing not being as space efficient as possible, and therefore is disabled by default.
- L62 _public member_ `bool bAllowFlips = false;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (EditCondition = "LayoutType == EUVLayoutType::Repack && bPreserveRotation == false"))` — Allow the Repack layout type to flip the orientation of UV islands to save space. Note that this may cause problems for downstream operations, and therefore is disabled by default.
- L66 _public member_ `bool bEnableUDIMLayout = false;` — `UPROPERTY(EditAnywhere, Category = "UV Layout", meta = (DisplayName = "Preserve UDIMs", EditCondition="bUDIMCVAREnabled", EditConditionHides, HideEditConditionToggle = true))` — Enable UDIM aware layout and keep islands within their originating UDIM tiles when laying out.
- L69 _public member_ `bool bUDIMCVAREnabled = false;` — `UPROPERTY(Transient)`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/SkinningOps/SkinBindingOp.h` (Public)


#### class `UE::Geometry::FSkinBindingOp`  
`class FSkinBindingOp : public FDynamicMeshOperator`  
_L23-51_
- inherits: `FDynamicMeshOperator`
- L29 _public prototype_ `virtual ~FSkinBindingOp() override = default;` — note we disable deprecation warnings here due to the deprecated TransformHierarchy member below
- L33 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L36 _public member_ `TArray<TPair<FTransform, FMeshBoneInfo>> TransformHierarchy;` — `UE_DEPRECATED(5.8, "TransformHierarchy is now unused and should not be accessed.")`
- L38 _public member_ `FName ProfileName = FSkeletalMeshAttributes::DefaultSkinWeightProfileName;`
- L40 _public member_ `ESkinBindingType BindType = ESkinBindingType::DirectDistance;`
- L41 _public member_ `float Stiffness = 0.2f;`
- L42 _public member_ `int32 MaxInfluences = 5;`
- L43 _public member_ `int32 VoxelResolution = 256;`
- L45 _public prototype_ `void SetTransformHierarchyFromReferenceSkeleton(const FReferenceSkeleton& InRefSkeleton);`
- L47 _public prototype_ `virtual void CalculateResult(FProgressCancel* InProgress) override;`
- L50 _private member_ `TArray<SkinBinding::FBonePoseInfo> BoneTransformHierarchy;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L20 _typedef_ `using FDynamicMeshVertexSkinWeightsAttribute = TDynamicVertexSkinWeightsAttribute<FDynamicMesh3>;` (scope `UE::Geometry`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/SmoothingOps/CotanSmoothingOp.h` (Public)


#### class `UE::Geometry::FCotanSmoothingOp`  
`class FCotanSmoothingOp : public FSmoothingOpBase`  
_L15-32_
- inherits: `FSmoothingOpBase`
- L18 _public prototype_ `FCotanSmoothingOp(const FDynamicMesh3* Mesh, const FSmoothingOpBase::FOptions& OptionsIn);`
- L21 _public prototype_ `FCotanSmoothingOp(const FDynamicMesh3* Mesh, const FSmoothingOpBase::FOptions& OptionsIn, const FDynamicSubmesh3& Submesh);` — Support for smoothing only selected geometry
- L23 _public prototype_ `~FCotanSmoothingOp() override = default;`
- L25 _public prototype_ `void CalculateResult(FProgressCancel* Progress) override;`
- L29 _private prototype_ `void Smooth(FProgressCancel* Progress);` — Compute the smoothed result by using Cotan Biharmonic
- L31 _private prototype_ `double GetSmoothPower(int32 VertexID, bool bIsBoundary);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/SmoothingOps/IterativeSmoothingOp.h` (Public)


#### class `UE::Geometry::FIterativeSmoothingOp`  
`class FIterativeSmoothingOp : public FSmoothingOpBase`  
_L15-41_
- inherits: `FSmoothingOpBase`
- L18 _public prototype_ `FIterativeSmoothingOp(const FDynamicMesh3* Mesh, const FSmoothingOpBase::FOptions& OptionsIn);`
- L21 _public prototype_ `FIterativeSmoothingOp(const FDynamicMesh3* Mesh, const FSmoothingOpBase::FOptions& OptionsIn, const FDynamicSubmesh3& Submesh);` — Support for smoothing only selected geometry
- L23 _public prototype_ `~FIterativeSmoothingOp() override = default;`
- L27 _public prototype_ `void CalculateResult(FProgressCancel* Progress) override;` — Apply smoothing. results in an updated ResultMesh Note: if canceled using the optional FProgressCancel, the results may be in an unusable state.
- L31 _private prototype_ `double GetSmoothAlpha(int32 VertexID, bool bIsBoundary);`
- L34 _private prototype_ `void Smooth_Forward(bool bUniform, FProgressCancel* Progress = nullptr);` — uniform iterative smoothing
- L37 _private prototype_ `void Smooth_Implicit_Cotan(FProgressCancel* Progress = nullptr);` — cotan smoothing iterations
- L40 _private prototype_ `void Smooth_MeanValue(FProgressCancel* Progress = nullptr);` — mean value smoothing iterations

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/SmoothingOps/SmoothingOpBase.h` (Public)


#### class `UE::Geometry::FSmoothingOpBase`  
`class FSmoothingOpBase : public FDynamicMeshOperator`  
_L23-92_
- inherits: `FDynamicMeshOperator`
- L65 _public prototype_ `FSmoothingOpBase(const FDynamicMesh3* Mesh, const FOptions& OptionsIn);`
- L68 _public prototype_ `FSmoothingOpBase(const FDynamicMesh3* Mesh, const FOptions& OptionsIn, const FDynamicSubmesh3& Submesh);` — Support for smoothing only selected geometry
- L70 _public prototype_ `virtual ~FSmoothingOpBase() override = default;`
- L73 _public prototype_ `void SetTransform(const FTransformSRT3d& XForm);` — set ability on protected transform.
- L76 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override = 0;` — base class overrides this.  Results in updated ResultMesh.
- L79 _public prototype_ `void UpdateResultMesh();` — copy the PositionBuffer locations back to the ResultMesh and recompute normal if it exists.
- L82 _protected member_ `FOptions SmoothOptions;`
- L84 _protected member_ `TArray<FVector3d> PositionBuffer;`
- L87 _protected member_ `TUniquePtr<FDynamicMesh3> SavedMesh = nullptr;` — a copy of the original mesh to save information regarding the non-selected (/non-smoothed) mesh when applicable
- L90 _protected member_ `TArray<int32> SmoothedToOriginalMap;` — maps the VertexId in the smoothed mesh to the VertexId in the original mesh

#### struct `UE::Geometry::FSmoothingOpBase::FOptions`  
`struct FOptions`  
_L26-62_
- L29 _public member_ `float SmoothAlpha = 1.0;` — value in range [0,1] where 0 is no smoothing and 1 is full smoothing
- L32 _public member_ `float BoundarySmoothAlpha = 1.0;` — value in range [0,1] where 0 is no smoothing and 1 is full smoothing
- L35 _public member_ `int32 Iterations = 1;` — number of iterations for iterative smoothing
- L39 _public member_ `float SmoothPower = 1.0;` — Unconstrained value in range [0,FMathf::MaxValue] with 0=NoSmoothing and MaxValue=FullySmoothed Used by weighted implicit smoothing where weight is somewhat arbitrary...
- L42 _public member_ `bool bUseImplicit = false;` — if true use implicit smoothing (where that is possible - depends on smoother?)
- L45 _public member_ `bool bSmoothBoundary = true;` — if true smooth the boundary, otherwise keep it fixed
- L48 _public member_ `bool bUniform = false;` — if true use uniform weights, otherwise use something better
- L51 _public member_ `double WeightClamp = FMathf::MaxReal;` — use this value to clamp weights (eg for clamped mean value)
- L54 _public member_ `TSharedPtr<UE::Geometry::FMeshNormals> BaseNormals;` — mesh normals calculated for input mesh
- L57 _public member_ `double NormalOffset = 0.0;` — offset used by some smoothers
- L59 _public member_ `TSharedPtr<UE::Geometry::FIndexedWeightMap1f> WeightMap;`
- L60 _public member_ `bool bUseWeightMap = false;`
- L61 _public member_ `float WeightMapMinMultiplier = 0.0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/SpaceDeformerOps/BendMeshOp.h` (Public)


#### class `UE::Geometry::FBendMeshOp`  
`class FBendMeshOp : public FMeshSpaceDeformerOp`  
_L15-24_
- inherits: `FMeshSpaceDeformerOp`
- L18 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L20 _public member_ `double BendDegrees = 90;`
- L21 _public member_ `bool bLockBottom = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/SpaceDeformerOps/FlareMeshOp.h` (Public)


#### class `UE::Geometry::FFlareMeshOp`  
`class FFlareMeshOp : public FMeshSpaceDeformerOp`  
_L15-35_
- inherits: `FMeshSpaceDeformerOp`
- L18 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L21 _public member_ `double FlarePercentX = 100;` — 0% does nothing, 100% moves 2x away from Z axis at extremal point, -100% squishes down to Z axis at extremal point.
- L22 _public member_ `double FlarePercentY = 100;`
- L31 _public member_ `EFlareType FlareType = EFlareType::SinFlare;`

#### enum `UE::Geometry::FFlareMeshOp::EFlareType`  
`enum class EFlareType`  
_L24-29_
- L26 _public enumerator_ `SinFlare = 0` — Flaring is the curve sin(Pi y)  y in [0, 1]
- L27 _public enumerator_ `SinSqrFlare = 1` — Flaring is the curve sin(Pi y)**2  y in  [0, 1]  which makes the ends smooth out back into shape
- L28 _public enumerator_ `LinearFlare = 2` — Flaring is  2*y  y in [0, 1/2] and 2(1-y) y in (1/2, 1]

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/SpaceDeformerOps/MeshSpaceDeformerOp.h` (Public)


#### class `UE::Geometry::FMeshSpaceDeformerOp`  
`class FMeshSpaceDeformerOp : public FDynamicMeshOperator`  
_L16-42_
- inherits: `FDynamicMeshOperator`
- L21 _public member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Inputs
- L22 _public member_ `FFrame3d GizmoFrame;`
- L23 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L26 _public member_ `double LowerBoundsInterval;` — The lower bound of the region of space that the operator affects, relative to the gizmo position.
- L29 _public member_ `double UpperBoundsInterval;` — The upper bound of the region of space that the operator affects, relative to the gizmo position.
- L36 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;` — Copies over the original mesh into result mesh, and initializes ObjectToGizmo in preparation to whatever work the base class does. Note that the function will return if OriginalMesh was null but doesn't have a way to log the error, so the base class should check OriginalMesh itself as well.
- L41 _protected member_ `FMatrix ObjectToGizmo;` — transform, including translation, to gizmo space

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperators/Public/SpaceDeformerOps/TwistMeshOp.h` (Public)


#### class `UE::Geometry::FTwistMeshOp`  
`class FTwistMeshOp : public FMeshSpaceDeformerOp`  
_L15-24_
- inherits: `FMeshSpaceDeformerOp`
- L18 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L20 _public member_ `double TwistDegrees = 180;`
- L21 _public member_ `bool bLockBottom = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELINGOPERATORS_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)
