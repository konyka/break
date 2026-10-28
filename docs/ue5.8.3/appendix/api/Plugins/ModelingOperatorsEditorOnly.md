# Plugins / ModelingOperatorsEditorOnly

- module root: `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly`
- headers: 8; symbols: 220
- symbol kinds: class=12, enum=7, enumerator=32, function=5, macro=6, member=115, namespace=12, prototype=30, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, MeshBuilder, MeshReductionInterface, MeshUtilities, ProxyLODMeshReduction
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryAlgorithms, GeometryCore, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshUtilitiesCommon, ModelingOperators, StaticMeshDescription

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly/Public/CleaningOps/SimplifyMeshOp.h` (Public)


#### enum `ESimplifyTargetType`  
`enum class ESimplifyTargetType : uint8`  
_L20-39_
- reflection: `UENUM()`
- L23 _public enumerator_ `Percentage = 0 UMETA(DisplayName = "Percentage")` — Percentage of input triangles
- L26 _public enumerator_ `TriangleCount = 1 UMETA(DisplayName = "Triangle Count")` — Target triangle count
- L29 _public enumerator_ `VertexCount = 2 UMETA(DisplayName = "Vertex Count")` — Target vertex count
- L32 _public enumerator_ `EdgeLength = 3 UMETA(DisplayName = "Edge Length")` — Target edge length
- L35 _public enumerator_ `QuadricError = 5 UMETA(DisplayName = "Quadric Error")` — Quadric error threshold
- L38 _public enumerator_ `MinimalPlanar = 4 UMETA(Hidden)` — Apply all allowable edge collapses that do not change the shape

#### enum `ESimplifyType`  
`enum class ESimplifyType : uint8`  
_L42-65_
- reflection: `UENUM()`
- L45 _public enumerator_ `QEM = 0 UMETA(DisplayName = "QEM")` — Fastest. Standard quadric error metric.
- L48 _public enumerator_ `Attribute = 1 UMETA(DisplayName = "Normal Aware")` — Potentially higher quality. Takes the normal into account.
- L51 _public enumerator_ `UEStandard = 2 UMETA(DisplayName = "UE Standard")` — Highest quality reduction.
- L54 _public enumerator_ `MinimalExistingVertex = 3 UMETA(DisplayName = "Existing Positions")` — Edge collapse to existing vertices only.  Quality may suffer.
- L57 _public enumerator_ `MinimalPlanar = 4 UMETA(DisplayName = "Minimal Shape-Preserving")` — Collapse any spurious edges but do not change the 3D shape.
- L60 _public enumerator_ `MinimalPolygroup = 5 UMETA(DisplayName = "Minimal PolyGroup-Preserving")` — Only preserve polygroup boundaries; ignore all other shape features
- L63 _public enumerator_ `ClusterBased = 6` — Simplify by locally clustering vertices, and re-creating the mesh triangles from the cluster connectivity

#### class `UE::Geometry::FSimplifyMeshOp`  
`class FSimplifyMeshOp : public FDynamicMeshOperator`  
_L73-150_
- inherits: `FDynamicMeshOperator`
- L76 _public prototype_ `virtual ~FSimplifyMeshOp() = default;`
- L81 _public member_ `ESimplifyTargetType TargetMode;` — Inputs
- L82 _public member_ `ESimplifyType SimplifierType;`
- L83 _public member_ `int TargetPercentage, TargetCount;`
- L83 _public member_ `int TargetPercentage, TargetCount;`
- L84 _public member_ `float TargetEdgeLength;`
- L85 _public member_ `float TargetQuadricError;`
- L86 _public member_ `bool bDiscardAttributes, bReproject, bPreventNormalFlips, bPreserveSharpEdges, bAllowSeamCollapse, bPreventTinyTriangles;`
- L86 _public member_ `bool bDiscardAttributes, bReproject, bPreventNormalFlips, bPreserveSharpEdges, bAllowSeamCollapse, bPreventTinyTriangles;`
- L86 _public member_ `bool bDiscardAttributes, bReproject, bPreventNormalFlips, bPreserveSharpEdges, bAllowSeamCollapse, bPreventTinyTriangles;`
- L86 _public member_ `bool bDiscardAttributes, bReproject, bPreventNormalFlips, bPreserveSharpEdges, bAllowSeamCollapse, bPreventTinyTriangles;`
- L86 _public member_ `bool bDiscardAttributes, bReproject, bPreventNormalFlips, bPreserveSharpEdges, bAllowSeamCollapse, bPreventTinyTriangles;`
- L86 _public member_ `bool bDiscardAttributes, bReproject, bPreventNormalFlips, bPreserveSharpEdges, bAllowSeamCollapse, bPreventTinyTriangles;`
- L89 _public member_ `bool bResultMustHaveAttributesEnabled = false;` — When true, result will have attributes object regardless of whether attributes were discarded or present initially.
- L90 _public member_ `UE::Geometry::EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;`
- L90 _public member_ `UE::Geometry::EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;`
- L90 _public member_ `UE::Geometry::EEdgeRefineFlags MeshBoundaryConstraint, GroupBoundaryConstraint, MaterialBoundaryConstraint;`
- L92 _public member_ `float MinimalPlanarAngleThresh = 0.01f;` — Angle threshold in degrees used for testing if two triangles should be considered coplanar, or two lines collinear
- L95 _public member_ `float PolyEdgeAngleTolerance = 0.1f;` — For minimal polygroup-preserving simplification: Threshold angle change (in degrees) along a polygroup edge, above which a vertex must be added
- L98 _public member_ `float BoundaryEdgeAngleTolerance = 30.0f;` — For cluster-based simplification, equivalent to PolyEdgeAngleTolerance but only for boundary edges. Helpful for preserving open boundary shape.
- L100 _public member_ `bool bGeometricDeviationConstraint = false;`
- L101 _public member_ `float GeometricTolerance = 0.0f;`
- L104 _public member_ `float RegularizeWeight = 0.f;` — Weight of optional regularization term, for QEM-based simplifiers
- L107 _public member_ `TFunction<double(const FDynamicMesh3&, int VertexA, int VertexB)> CustomGeometricErrorScaleF;` — QEM simplifier custom scales to apply to errors and edge lengths. Note this is in effect the inverse of scaling the tolerances / target lengths.
- L108 _public member_ `TFunction<double(const FDynamicMesh3&, int VertexA, int VertexB)> CustomEdgeLengthScaleF;`
- L110 _public member_ `TFunction<double(const FDynamicMesh3&, int Vertex)> CustomQuadricErrorScaleF;` — Custom per-vertex quadric error scaling. Values should be greater than zero.
- L113 _public member_ `TFunction<double(int32)> ClusterTargetEdgeLengthScaleF = nullptr;` — Cluster simplifier custom scales apply to the *target* edge lengths, and so is conceptually the inverse of the above scales.
- L116 _public member_ `TSharedPtr<FMeshDescription, ESPMode::ThreadSafe> OriginalMeshDescription;` — stored for the UEStandard path
- L118 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — stored for the GeometryProcessing custom simplifier paths (currently precomputed once in tool setup)
- L119 _public member_ `TSharedPtr<FDynamicMeshAABBTree3, ESPMode::ThreadSafe> OriginalMeshSpatial;`
- L121 _public member_ `IMeshReduction* MeshReduction;`
- L135 _public prototype_ `static bool ComputeStandardSimplifier(IMeshReduction* MeshReduction, const FMeshDescription& SrcMeshDescription, FDynamicMesh3& OutResult, float PercentReduction, bool bTriBasedReduction, bool bDiscardAttributes, FProgressCancel* Progress = nullptr);` — Simple helper to compute UE Standard simplified mesh @param MeshReduction Interface for mesh reduction; must be non-null @param SrcMeshDescription Input mesh @param OutResult Simplified mesh will be written to this mesh @param PercentReduction Percent to reduce @param bTriBasedReduction Whether to reduce based on triangles; otherwise, will reduce based on vertices @param bDiscardAttributes Whether to discard attributes when simplifying @param Progress If non-null, can early-out if this is set to request cancellation @return true if succeeded, false otherwise (e.g. if cancelled)
- L140 _public function_ `void SetTransform(const FTransform& Transform)` — set ability on protected transform.
- L149 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MODELINGOPERATORSEDITORONLY_API`
- L67 _namespace_ `namespace UE`
- L69 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly/Public/CompositionOps/VoxelBooleanMeshesOp.h` (Public)


#### class `UE::Geometry::FVoxelBooleanMeshesOp`  
`class FVoxelBooleanMeshesOp : public FDynamicMeshOperator`  
_L21-57_
- inherits: `FDynamicMeshOperator`
- L24 _public prototype_ `virtual ~FVoxelBooleanMeshesOp() = default;`
- L36 _public member_ `TArray<TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe>> Meshes;` — inputs
- L37 _public member_ `TArray<FTransformSRT3d> Transforms;` — 1:1 with Meshes
- L39 _public member_ `int32 VoxelCount = 128;`
- L40 _public member_ `double VoxelSizeD = 1.0;`
- L41 _public member_ `double AdaptivityD = 0;`
- L42 _public member_ `double IsoSurfaceD = 0;`
- L43 _public member_ `bool bAutoSimplify = false;`
- L44 _public member_ `EBooleanOperation Operation = EBooleanOperation::DifferenceBA;`
- L50 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L55 _private prototype_ `float ComputeVoxelSize() const;` — compute the voxel size based on the voxel count and the input geometry

#### enum `UE::Geometry::FVoxelBooleanMeshesOp::EBooleanOperation`  
`enum class EBooleanOperation`  
_L26-32_
- L28 _public enumerator_ `DifferenceAB = 0`
- L29 _public enumerator_ `DifferenceBA = 1`
- L30 _public enumerator_ `Intersect = 2`
- L31 _public enumerator_ `Union = 3`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGOPERATORSEDITORONLY_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly/Public/CompositionOps/VoxelMergeMeshesOp.h` (Public)


#### class `UE::Geometry::FVoxelMergeMeshesOp`  
`class FVoxelMergeMeshesOp : public FDynamicMeshOperator`  
_L21-49_
- inherits: `FDynamicMeshOperator`
- L24 _public prototype_ `virtual ~FVoxelMergeMeshesOp() = default;`
- L27 _public member_ `TArray<TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe>> Meshes;` — inputs
- L28 _public member_ `TArray<FTransformSRT3d> Transforms;` — 1:1 with Meshes
- L30 _public member_ `int32 VoxelCount = 128;`
- L31 _public member_ `double VoxelSizeD = 1.0;`
- L32 _public member_ `double AdaptivityD = 0;`
- L33 _public member_ `double IsoSurfaceD = 0;`
- L34 _public member_ `bool bAutoSimplify = false;`
- L36 _public member_ `double FastCollapseVoxelSizeMultipler = 1.2;`
- L37 _public member_ `int NumFastCollapsePasses = 10;`
- L43 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L48 _private prototype_ `float ComputeVoxelSize() const;` — compute the voxel size based on the voxel count and the input geometry

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGOPERATORSEDITORONLY_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly/Public/CuttingOps/EmbedPolygonsOp.h` (Public)


#### enum `EEmbeddedPolygonOpMethod`  
`enum class EEmbeddedPolygonOpMethod : uint8`  
_L17-24_
- reflection: `UENUM()`
- L19 _public enumerator_ `TrimOutside`
- L20 _public enumerator_ `TrimInside`
- L21 _public enumerator_ `InsertPolygon`
- L22 _public enumerator_ `CutThrough`
- L23 _public enumerator_ `CutOutside`

#### class `UE::Geometry::FEmbedPolygonsOp`  
`class FEmbedPolygonsOp : public FDynamicMeshOperator`  
_L32-79_
- inherits: `FDynamicMeshOperator`
- L35 _public prototype_ `virtual ~FEmbedPolygonsOp() = default;`
- L39 _public member_ `FFrame3d PolygonFrame;` — inputs
- L40 _public member_ `FPolygon2d EmbedPolygon;`
- L41 _public member_ `bool bCutWithBoolean;`
- L42 _public member_ `bool bAttemptFixHolesOnBoolean;`
- L45 _public function_ `FPolygon2d GetPolygon()` — TODO: switch to FGeneralPolygon2d?
- L50 _public member_ `bool bDiscardAttributes;`
- L52 _public member_ `EEmbeddedPolygonOpMethod Operation;`
- L56 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L62 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L66 _public member_ `TArray<int> EdgesOnFailure;` — Outputs
- L67 _public member_ `TArray<int> EmbeddedEdges;`
- L68 _public member_ `bool bOperationSucceeded;`
- L71 _private prototype_ `void RecordEmbeddedEdges(TArray<int>& PathVertIDs);`
- L73 _private prototype_ `void BooleanPath(FProgressCancel* Progress);`
- L78 _private prototype_ `TArray<FPolygon2d> CleanPolygon(const FPolygon2d& Input);` — Fix issues like self-intersection on an input polygon Note: We could change this to return an array of general polygons in the future, to handle the most general case, but currently the embedding process does not support holes

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MODELINGOPERATORSEDITORONLY_API`
- L26 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly/Public/ModelingOperatorsEditorOnlyModule.h` (Public)


#### class `FModelingOperatorsEditorOnlyModule`  
`class FModelingOperatorsEditorOnlyModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly/Public/ParameterizationOps/CalculateTangentsOp.h` (Public)


#### enum `EMeshTangentsType`  
`enum class EMeshTangentsType : uint8`  
_L15-25_
- reflection: `UENUM()`
- L18 _public enumerator_ `MikkTSpace = 0` — Standard MikkTSpace tangent calculation
- L20 _public enumerator_ `FastMikkTSpace = 1` — MikkTSpace-like blended per-triangle tangents, with the blending being based on existing mesh, normals, and UV topology
- L22 _public enumerator_ `PerTriangle = 2` — Project per-triangle tangents onto normals
- L24 _public enumerator_ `CopyExisting = 3` — Use existing source mesh tangents

#### class `UE::Geometry::FCalculateTangentsOp`  
`class FCalculateTangentsOp : public TGenericDataOperator<FMeshTangentsd>`  
_L32-58_
- inherits: `TGenericDataOperator<FMeshTangentsd>`
- L35 _public prototype_ `virtual ~FCalculateTangentsOp() = default;`
- L38 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> SourceMesh;` — inputs
- L39 _public member_ `TSharedPtr<FMeshTangentsf, ESPMode::ThreadSafe> SourceTangents;`
- L42 _public member_ `EMeshTangentsType CalculationMethod;` — parameters
- L44 _public member_ `int32 TargetUVLayer = 0;` — Compute tangents with respect to this UV layer
- L47 _public member_ `bool bNoAttributesError = false;` — error flags
- L53 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L55 _public prototype_ `virtual void CalculateStandard(FProgressCancel* Progress, TUniquePtr<FMeshTangentsd>& Tangents);`
- L56 _public prototype_ `virtual void CalculateMikkT(FProgressCancel* Progress, TUniquePtr<FMeshTangentsd>& Tangents);`
- L57 _public prototype_ `virtual void CopyFromSource(FProgressCancel* Progress, TUniquePtr<FMeshTangentsd>& Tangents);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGOPERATORSEDITORONLY_API`
- L27 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly/Public/ParameterizationOps/ParameterizeMeshOp.h` (Public)


#### enum `UE::Geometry::EParamOpBackend`  
`enum class EParamOpBackend`  
_L25-30_
- L27 _public enumerator_ `PatchBuilder = 0`
- L28 _public enumerator_ `UVAtlas = 1`
- L29 _public enumerator_ `XAtlas = 2`

#### class `UE::Geometry::FParameterizeMeshOp`  
`class FParameterizeMeshOp : public FDynamicMeshOperator`  
_L32-126_
- inherits: `FDynamicMeshOperator`
- L35 _public prototype_ `virtual ~FParameterizeMeshOp() = default;`
- L42 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;` — source mesh
- L45 _public member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> InputGroups;` — source groups (optional)
- L48 _public member_ `float Stretch = 0.11f;` — UVAtlas generation parameters
- L49 _public member_ `int32 NumCharts = 0;`
- L52 _public member_ `int32 XAtlasMaxIterations = 1;` — XAtlas generation parameters
- L55 _public member_ `int32 InitialPatchCount = 100;` — PatchBuilder generation parameters
- L56 _public member_ `bool bRespectInputGroups = false;`
- L57 _public member_ `float PatchCurvatureAlignmentWeight = 1.0f;`
- L58 _public member_ `float PatchMergingMetricThresh = 1.5f;`
- L59 _public member_ `float PatchMergingAngleThresh = 45.0f;`
- L60 _public member_ `int ExpMapNormalSmoothingSteps = 5;`
- L61 _public member_ `float ExpMapNormalSmoothingAlpha = 0.25f;`
- L64 _public member_ `int32 UVLayer = 0;` — UV layer
- L67 _public member_ `bool bPackToUDIMSByOriginPolygroup = false;` — UDIM support
- L70 _public member_ `bool bEnablePacking = true;` — Atlas Packing parameters
- L71 _public member_ `int32 Height = 512;`
- L72 _public member_ `int32 Width = 512;`
- L73 _public member_ `float Gutter = 2.5f;`
- L75 _public member_ `EParamOpBackend Method = EParamOpBackend::UVAtlas;`
- L78 _public function_ `void SetTransform(const FTransformSRT3d& XForm)` — set ability on protected transform.
- L87 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L110 _protected member_ `FGeometryResult NewResultInfo;`
- L112 _protected prototype_ `bool ComputeUVs_UVAtlas(FDynamicMesh3& InOutMesh, TFunction<bool(float)>& Interrupter);`
- L113 _protected prototype_ `bool ComputeUVs_XAtlas(FDynamicMesh3& InOutMesh, TFunction<bool(float)>& Interrupter);`
- L114 _protected prototype_ `bool ComputeUVs_PatchBuilder(FDynamicMesh3& InOutMesh, FProgressCancel* Progress);`
- L116 _protected prototype_ `void CopyNewUVsToMesh( FDynamicMesh3& Mesh, const FLinearMesh& LinearMesh, const FDynamicMesh3& FlippedMesh, const TArray<FVector2D>& UVVertexBuffer, const TArray<int32>& UVIndexBuffer, const TArray<int32>& VertexRemapArray, bool bReverseOrientation);`
- L125 _protected prototype_ `void LayoutToUDIMByPolygroup(FDynamicMesh3& InOutMesh, UE::Geometry::FPolygroupSet& InputGroups);`

#### struct `UE::Geometry::FParameterizeMeshOp::FLinearMesh`  
`struct FLinearMesh`  
_L93-108_
- desc: dense index/vertex buffer based representation of the data needed for parameterization
- L95 _public prototype_ `FLinearMesh(const FDynamicMesh3& Mesh, UE::Geometry::FPolygroupSet* InputGroups);`
- L98 _public member_ `TArray<int32> IndexBuffer;` — Stripped down mesh
- L99 _public member_ `TArray<FVector3f> VertexBuffer;`
- L102 _public member_ `TArray<int32> VertToID;` — Map from offset in the VertexBuffer to the VertexID in the FDynamicMesh
- L106 _public member_ `TArray<int32> AdjacencyBuffer;` — Adjacency[tri], Adjacency[tri+1], Adjacency[tri+2] are the three tris adjacent to tri.

#### class `UParameterizeMeshOperatorFactory`  
`class UParameterizeMeshOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L138-163_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Can be hooked up to a UMeshOpPreviewWithBackgroundCompute to perform UV parameterization operations. Inherits from UObject so that it can hold a strong pointer to the settings UObject, which needs to be a UObject to be displayed in the details panel.
- L144 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L147 _public member_ `TObjectPtr<UParameterizeMeshToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L150 _public member_ `TObjectPtr<UParameterizeMeshToolUVAtlasProperties> UVAtlasProperties = nullptr;` — `UPROPERTY()`
- L153 _public member_ `TObjectPtr<UParameterizeMeshToolXAtlasProperties> XAtlasProperties = nullptr;` — `UPROPERTY()`
- L156 _public member_ `TObjectPtr<UParameterizeMeshToolPatchBuilderProperties> PatchBuilderProperties = nullptr;` — `UPROPERTY()`
- L159 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> InputGroups;
- L160 _public function_ `TUniqueFunction<int32()> GetSelectedUVChannel = []()`
- L160 _public member_ `TUniqueFunction<int32()> GetSelectedUVChannel = []() { return 0; };`
- L161 _public function_ `TUniqueFunction<TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe>()> GetPolygroups = []()`
- L161 _public member_ `TUniqueFunction<TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe>()> GetPolygroups = []() { return nullptr; };`
- L162 _public member_ `FTransform TargetTransform;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MODELINGOPERATORSEDITORONLY_API`
- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingOperatorsEditorOnly/Public/Properties/ParameterizeMeshProperties.h` (Public)


#### enum `EParameterizeMeshUVMethod`  
`enum class EParameterizeMeshUVMethod`  
_L12-22_
- reflection: `UENUM()`
- L17 _public enumerator_ `PatchBuilder = 0` — Compute automatic UVs using the Patch Builder technique
- L19 _public enumerator_ `UVAtlas = 1` — Compute automatic UVs using the UVAtlas technique
- L21 _public enumerator_ `XAtlas = 2` — Compute automatic UVs using the XAtlas technique

#### class `UParameterizeMeshToolProperties`  
`class UParameterizeMeshToolProperties : public UInteractiveToolPropertySet`  
_L26-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L32 _public member_ `EParameterizeMeshUVMethod Method = EParameterizeMeshUVMethod::PatchBuilder;` — `UPROPERTY(EditAnywhere, Category = AutoUV)` — Automatic UV generation technique to use

#### class `UParameterizeMeshToolUVAtlasProperties`  
`class UParameterizeMeshToolUVAtlasProperties : public UInteractiveToolPropertySet`  
_L40-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for the UVAtlas Automatic UV Generation Method
- L46 _public member_ `float IslandStretch = 0.11f;` — `UPROPERTY(EditAnywhere, Category = UVAtlas, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Maximum amount of stretch, from none to unbounded. If zero stretch is specified, each triangle will likely be its own UV island.
- L50 _public member_ `int NumIslands = 0;` — `UPROPERTY(EditAnywhere, Category = UVAtlas, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "10000"))` — Hint at number of UV islands. The default of 0 means it is determined automatically.
- L54 _public member_ `int TextureResolution = 1024;` — `UPROPERTY(EditAnywhere, Category = UVAtlas, meta = (UIMin = "64", UIMax = "2048", ClampMin = "2", ClampMax = "4096"))` — Expected resolution of the output textures; this controls spacing left between UV islands to avoid interpolation artifacts.
- L58 _public member_ `bool bUsePolygroups;` — `UPROPERTY(EditAnywhere, Category = UVAtlas, meta = (DisplayName = "Constrain to PolyGroups", EditCondition = bPolygroupsEnabled, EditConditionHides, HideEditConditionToggle))` — Generate new UVs based on polygroups from specified layer.
- L62 _public member_ `bool bLayoutUDIMPerPolygroup;` — `UPROPERTY(EditAnywhere, Category = UVAtlas, meta = (EditCondition = "bUsePolygroups && bUDIMsEnabled", EditConditionHides, HideEditConditionToggle))` — Layout resulting islands on UDIMs based on polygroups.
- L66 _public member_ `bool bPolygroupsEnabled;` — `UPROPERTY()` — Controls if polygroup options are available to the user.
- L70 _public member_ `bool bUDIMsEnabled;` — `UPROPERTY()` — Controls if UDIM options are available to the user.

#### class `UParameterizeMeshToolXAtlasProperties`  
`class UParameterizeMeshToolXAtlasProperties : public UInteractiveToolPropertySet`  
_L75-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L81 _public member_ `int MaxIterations = 1;` — `UPROPERTY(EditAnywhere, Category = XAtlas, meta = (UIMin = "1", UIMax = "10", ClampMin = "1", ClampMax = "1000"))` — Number of solve iterations; higher values generally result in better UV islands.

#### class `UParameterizeMeshToolPatchBuilderProperties`  
`class UParameterizeMeshToolPatchBuilderProperties : public UInteractiveToolPropertySet`  
_L86-137_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L92 _public member_ `int InitialPatches = 100;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (UIMin = "1", UIMax = "1000", ClampMin = "1", ClampMax = "99999999"))` — Number of initial patches the mesh will be split into before island merging.
- L96 _public member_ `float CurvatureAlignment = 1.0f;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (UIMin = "0.1", UIMax = "2.0", ClampMin = "0.01", ClampMax = "100.0"))` — Alignment of the initial patches to creases in the mesh.
- L100 _public member_ `float MergingDistortionThreshold = 1.5f;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (DisplayName = "Distortion Threshold", UIMin = "1.0", UIMax = "5.0", ClampMin = "1.0"))` — Threshold for stretching and distortion below which island merging is allowed; larger values increase the allowable UV distortion.
- L104 _public member_ `float MergingAngleThreshold = 45.0f;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (DisplayName = "Angle Threshold", UIMin = "0.0", UIMax = "90.0", ClampMin = "0.0", ClampMax = "180.0"))` — Threshold for the average face normal deviation below which island merging is allowed.
- L108 _public member_ `int SmoothingSteps = 5;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (UIMin = "0", UIMax = "25", ClampMin = "0", ClampMax = "1000"))` — Number of smoothing steps to apply; this slightly increases distortion but produces more stable results.
- L112 _public member_ `float SmoothingAlpha = 0.25f;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (UIMin = "0", UIMax = "1.0", ClampMin = "0", ClampMax = "1.0"))` — Smoothing parameter; larger values result in faster smoothing in each step.
- L116 _public member_ `bool bRepack = true;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder)` — Automatically pack result UVs into the unit square, i.e. fit between 0 and 1 with no overlap.
- L120 _public member_ `int TextureResolution = 1024;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (UIMin = "64", UIMax = "2048", ClampMin = "2", ClampMax = "4096", EditCondition = bRepack))` — Expected resolution of the output textures; this controls spacing left between UV islands to avoid interpolation artifacts. This is only enabled when Repack is enabled.
- L124 _public member_ `bool bUsePolygroups;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (DisplayName = "Constrain to PolyGroups", EditCondition = bPolygroupsEnabled, EditConditionHides, HideEditConditionToggle))` — Generate new UVs based on polygroups from specified layer.
- L128 _public member_ `bool bLayoutUDIMPerPolygroup;` — `UPROPERTY(EditAnywhere, Category = PatchBuilder, meta = (EditCondition = "bUsePolygroups && bUDIMsEnabled", EditConditionHides, HideEditConditionToggle))` — Layout resulting islands on UDIMs based on polygroups.
- L132 _public member_ `bool bPolygroupsEnabled;` — `UPROPERTY()` — Controls if polygroup options are available to the user.
- L136 _public member_ `bool bUDIMsEnabled;` — `UPROPERTY()` — Controls if UDIM options are available to the user.
