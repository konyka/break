# Plugins / VEUVCore

- module root: `Plugins/Experimental/VEUV/Source/VEUVCore`
- headers: 14; symbols: 363
- symbol kinds: class=8, delegate=1, enum=3, enumerator=13, function=39, macro=5, member=209, namespace=16, prototype=31, struct=37, variable=1
- PrivateDependencyModuleNames: Eigen
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVCharting.h` (Private)


#### struct `VEUV::FAABounds`  
`struct FAABounds`  
_L11-15_
- L13 _public member_ `Eigen::Vector2f Min = Eigen::Vector2f::Constant(FLT_MAX);`
- L14 _public member_ `Eigen::Vector2f Max = Eigen::Vector2f::Constant(-FLT_MAX);`

#### struct `VEUV::FEVBounds`  
`struct FEVBounds`  
_L17-22_
- L19 _public member_ `Eigen::VectorXf Mean = Eigen::Vector2f::Zero();`
- L20 _public member_ `Eigen::VectorXf EV0 = Eigen::Vector2f::Zero();`
- L21 _public member_ `Eigen::VectorXf EV1 = Eigen::Vector2f::Zero();`

#### struct `VEUV::FChartContext`  
`struct FChartContext : FSolveRegion`  
_L24-33_
- inherits: `FSolveRegion`
- L26 _public member_ `FAABounds AABounds;`
- L27 _public member_ `FAABounds PackedAABounds;`
- L29 _public member_ `FEVBounds EVBounds;`
- L30 _public member_ `FEVBounds PackedEVBounds;`
- L32 _public member_ `float Area = 0.0f;`

#### struct `VEUV::FGlobalSolveContext`  
`struct FGlobalSolveContext : FSolveRegion`  
_L35-44_
- inherits: `FSolveRegion`
- L37 _public member_ `TSet<int32> SolvedCornerIndices;`
- L39 _public member_ `TArray<FChartContext> Charts;`
- L41 _public member_ `TArray<int32> VoxelChartIndices;`
- L43 _public member_ `bool bPackingSucceeded = true;`

#### struct `VEUV::FChartTraversalContext`  
`struct FChartTraversalContext`  
_L46-50_
- L48 _public member_ `TSet<int32> Visited;`
- L49 _public member_ `TSet<int32> Skipped;`

#### struct `VEUV::FTraversalInfo`  
`struct FTraversalInfo`  
_L52-56_
- L54 _public member_ `int32 From = INDEX_NONE;`
- L55 _public member_ `int32 To = INDEX_NONE;`

#### class `VEUV::FCharting`  
`class FCharting`  
_L58-98_
- L69 _public prototype_ `static void FillCharts( FVoxelGrid& Grid, FGlobalSolveContext& SolveContext, const TArray<Eigen::Vector3f>& Vertices, const TArray<Eigen::Vector3i>& Faces, const TArray<int32>& VertexVoxelIndices );` — Creates separate charts for folded/overlapping UVs @param Grid Parent grid @param SolveContext Solution to chart for @param Vertices Mesh vertices, must be cut to the voxel grid @param Faces Mesh faces, must be cut to the voxel grid @param VertexVoxelIndices All vertex voxel associations
- L83 _public prototype_ `static FTraversalInfo TraverseLowestCut( const FVoxelGrid& Grid, FChartTraversalContext& Charting );` — Get the first voxel that has the lowest cut to the current visitation context @param Grid Parent grid @param Charting Current context @return {, INDEX_NONE} if none available
- L94 _public prototype_ `static int32 FirstUnvisited( const FVoxelGrid& Grid, FChartTraversalContext& Charting );` — Get the first unvisited voxel @param Grid Parent grid @param Charting Current context @return INDEX_NONE if none available

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace VEUV`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVEigen.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define EIGEN_NO_DEBUG 1`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVGeometry.h` (Private)


#### struct `VEUV::FEigenMesh`  
`struct FEigenMesh`  
_L10-14_
- L12 _public member_ `TArray<Eigen::Vector3f> Vertices;`
- L13 _public member_ `TArray<Eigen::Vector3i> Faces;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace VEUV`
- L17 _namespace_ `namespace VEUV`
- L17 _namespace_ `namespace Geometry` (scope `VEUV`)
- L19 _function_ `inline float Square(float X)` (scope `VEUV::Geometry`)
- L24 _function_ `inline float WEdge(const Eigen::Vector2f& A, const Eigen::Vector2f& B)` (scope `VEUV::Geometry`)
- L29 _function_ `inline bool AABBTest(const Eigen::Vector3f& MinA, const Eigen::Vector3f& MaxA, const Eigen::Vector3f& MinB, const Eigen::Vector3f& MaxB)` (scope `VEUV::Geometry`)
- L37 _function_ `inline bool AABBPlaneTest(const Eigen::Vector3f& Min, const Eigen::Vector3f& Max, const Eigen::Vector3f& Normal, float D)` (scope `VEUV::Geometry`)
- L56 _function_ `inline bool TriBoxTest( const Eigen::Vector3f& BoxMin, const Eigen::Vector3f& BoxMax, const Eigen::Vector3f& P0, const Eigen::Vector3f& P1, const Eigen::Vector3f& P2, float PlaneEpsilon = 0.0f)` (scope `VEUV::Geometry`)
- L125 _function_ `inline bool PointInTri(const Eigen::Vector2f& P, const Eigen::Vector2f& A, const Eigen::Vector2f& B, const Eigen::Vector2f& C, float BoundaryEps = 0.0f)` (scope `VEUV::Geometry`)
- L138 _function_ `inline bool LineLineTest(const Eigen::Vector2f& A0, const Eigen::Vector2f& A1, const Eigen::Vector2f& B0, const Eigen::Vector2f& B1, float BoundaryEps = 1e-3f)` (scope `VEUV::Geometry`)
- L166 _function_ `inline bool LineTriTestOuter(const Eigen::Vector2f& A0, const Eigen::Vector2f& A1, const Eigen::Vector2f& B0, const Eigen::Vector2f& B1, const Eigen::Vector2f& B2, float BoundaryEps)` (scope `VEUV::Geometry`)
- L173 _function_ `inline bool TriTriTest( const Eigen::Vector2f& A0, const Eigen::Vector2f& A1, const Eigen::Vector2f& A2, const Eigen::Vector2f& B0, const Eigen::Vector2f& B1, const Eigen::Vector2f& B2, float BoundaryEps = 0.1f)` (scope `VEUV::Geometry`)
- L194 _function_ `template<typename FuncType> inline void IntersectSegmentPlane(const Eigen::Vector3f& A, const Eigen::Vector3f& B, const Eigen::Vector3f& N, float D, FuncType&& Func)` (scope `VEUV::Geometry`)
- L217 _function_ `template<typename FuncType> inline void IntersectTrianglePlane(const Eigen::Vector3f& A, const Eigen::Vector3f& B, const Eigen::Vector3f& C, const Eigen::Vector3f& N, float D, FuncType&& Func)` (scope `VEUV::Geometry`)
- L224 _function_ `inline bool ConditionalVoxelPointAdd(const Eigen::Vector3f& A, const Eigen::Vector3f& Center, const Eigen::Vector3f& Extent, float Eps = 1e-4f)` (scope `VEUV::Geometry`)
- L229 _function_ `inline void TriangulatePoints( const Eigen::Vector3f& TriA, const Eigen::Vector3f& TriB, const Eigen::Vector3f& TriC, TArray<Eigen::Vector3f>& Points, TArray<Eigen::Vector3f>& OutVertices, TArray<Eigen::Vector3f>& OutNormals, TArray<Eigen::Vector3i>& OutFaces)` (scope `VEUV::Geometry`)
- L256 _function_ `` (scope `VEUV::Geometry::TriangulatePoints`)
- L276 _function_ `inline void ClipTriangleToVoxel( const Eigen::Vector3f& A, const Eigen::Vector3f& B, const Eigen::Vector3f& C, const Eigen::Vector3f& Min, const Eigen::Vector3f& Max, TArray<Eigen::Vector3f>& OutPoints)` (scope `VEUV::Geometry`)
- L356 _function_ `inline void GetTrilinearWeights(float X, float Y, float Z, float OutW[8])` (scope `VEUV::Geometry`)
- L368 _function_ `inline void GetTrilinearPartialXYZDerivatives(float X, float Y, float Z, Eigen::Vector3f OutPD[8])` (scope `VEUV::Geometry`)
- L380 _function_ `inline Eigen::Vector3f SafeOrthogonalize( const Eigen::Vector3f& T1, const Eigen::Vector3f& V, const Eigen::Vector3f& Normal)` (scope `VEUV::Geometry`)
- L390 _function_ `inline Eigen::Vector3f GetBarycentrics(const Eigen::Vector3f& P, const Eigen::Vector3f& A, const Eigen::Vector3f& B, const Eigen::Vector3f& C)` (scope `VEUV::Geometry`)

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVPacking.h` (Private)


#### class `VEUV::FPacking`  
`class FPacking`  
_L11-37_
- L21 _public prototype_ `static void ReorientCharts( FVoxelGrid& Grid, FGlobalSolveContext& SolveContext, const TArray<Eigen::Vector3f>& Vertices, const TArray<Eigen::Vector3i>& Faces );` — Reorient the charts to be axis aligned, rotation determined by primary EVs @param Grid Parent grid @param SolveContext Solution to orient against @param Vertices All vertex @param Faces All faces
- L33 _public prototype_ `static void PackCharts( FVoxelGrid& Grid, FGlobalSolveContext& SolveContext );` — Pack a chart atlas @param Grid Parent grid @param SolveContext Solution to pack

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace VEUV`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVSampling.h` (Private)


#### class `VEUV::FSampling`  
`class FSampling`  
_L13-65_
- L25 _public prototype_ `static void SampleVoxels( FVoxelGrid& Grid, const FVEUVConfig& Config, const FNormalization& Norm, const TArray<Eigen::Vector3f>& Vertices, const TArray<Eigen::Vector3i>& Faces );` — Sample all voxels @param Grid Parent grid @param Config Build config @param Norm Normalization state @param Vertices Mesh vertex set @param Faces Mesh face set @param VertexVoxelIndices All vertex to voxel associations
- L42 _public prototype_ `static int32 AdaptiveResample( FVoxelGrid& Grid, const FVEUVConfig& Config, const FNormalization& Norm, const FSolveRegion& Region, const TArray<Eigen::Vector3f>& Vertices, const TArray<Eigen::Vector3i>& Faces );` — Adaptively resample voxels on error @param Grid Parent grid @param Config Build config @param Norm Normalization state @param Region The solve region to evaluate error against @param Vertices Mesh vertex set @param Faces Mesh face set
- L59 _public prototype_ `static float EvaluateSampleErrorR78( const FVoxelGrid& Grid, const FSolveRegion& Region, const FVoxelData& Voxel, const FSampleData& Sample );` — Evaluate a sample error @param Grid Parent grid @param Region The solve region to evaluate error against @param Voxel Voxel of the sample @param Sample Sample to evaluate @return

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace VEUV`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVSchedulers.h` (Private)


#### struct `VEUV::Schedulers::FAdam`  
`struct FAdam`  
_L10-63_
- L12 _public member_ `float Beta1 = 0.9f;`
- L13 _public member_ `float Beta2 = 0.999f;`
- L22 _public function_ `void Init(int32 CoeffCount)`
- L28 _public function_ `Eigen::VectorXf Step(Eigen::VectorXf& Gradient, float LR)`
- L44 _public function_ `void SetFromSnapshot(const FCoeffInvariantSnapshot& Snapshot)`
- L51 _public function_ `FCoeffInvariantSnapshot GetSnapshot()`
- L60 _public member_ `Eigen::VectorXf MomentA;`
- L61 _public member_ `Eigen::VectorXf MomentB;`
- L62 _public member_ `float Time = 0.0f;`

#### struct `VEUV::Schedulers::FAdam::FCoeffInvariantSnapshot`  
`struct FCoeffInvariantSnapshot`  
_L15-20_
- L17 _public member_ `float MomentAMean = 0.0f;`
- L18 _public member_ `float MomentBMean = 0.0f;`
- L19 _public member_ `float Time = 0.0f;`

#### struct `VEUV::Schedulers::FNormSlopeCondition`  
`struct FNormSlopeCondition`  
_L65-137_
- L67 _public member_ `int32 Window = 32;`
- L68 _public member_ `float Threshold = 1e-3f;`
- L69 _public member_ `float Eps = 1e-12f;`
- L71 _public function_ `bool Step(float CurrentMetric)`
- L100 _private function_ `bool GetWindowSlopeLS(float& Slope, float& MeanMetric)`
- L136 _private member_ `TArray<float> History;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace VEUV`
- L8 _namespace_ `namespace Schedulers` (scope `VEUV`)

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVSolver.h` (Private)


#### struct `VEUV::FSparseResidualRow`  
`struct FSparseResidualRow`  
_L14-21_
- L17 _public member_ `int32 JacobianResidualOffset = 0;` — Starting offset for jacobians
- L20 _public member_ `float Target = 0.0f;` — Target (B) RHS value for LS-solve

#### struct `VEUV::FSparseResidualRowControl`  
`struct FSparseResidualRowControl`  
_L23-34_
- L26 _public member_ `uint8 InfluenceCount = 0;` — Total number of influences this control has (i.e., corners)
- L29 _public member_ `uint8 RowCount = 0;` — Total number of rows for this control
- L32 _public member_ `int32 InfluenceOffset = 0;` — Starting offsets
- L33 _public member_ `int32 RowOffset = 0;`

#### struct `VEUV::FSparseResidualArray`  
`struct FSparseResidualArray`  
_L36-90_
- L43 _public function_ `FSnapshot Snapshot() const`
- L48 _public function_ `void Restore(const FSnapshot& Snapshot)`
- L56 _public function_ `void Preallocate(int32 NumControls, int32 MaxInfluencesPerControl, int32 RowsPerControl)`
- L80 _public member_ `int32 ControlOffset = 0;` — Current allocation offsets
- L81 _public member_ `int32 RowOffset = 0;`
- L82 _public member_ `int32 JacobianOffset = 0;`
- L83 _public member_ `int32 IndexOffset = 0;`
- L86 _public member_ `TArray<FSparseResidualRowControl> Controls;` — Payloads
- L87 _public member_ `TArray<FSparseResidualRow> Rows;`
- L88 _public member_ `TArray<float> JacobianResiduals;`
- L89 _public member_ `TArray<int32> Indices;`

#### struct `VEUV::FSparseResidualArray::FSnapshot`  
`struct FSnapshot`  
_L38-41_
- L40 _public member_ `int32 ControlsCount, RowsCount, JacobiansCount, IndicesCount;`
- L40 _public member_ `int32 ControlsCount, RowsCount, JacobiansCount, IndicesCount;`
- L40 _public member_ `int32 ControlsCount, RowsCount, JacobiansCount, IndicesCount;`
- L40 _public member_ `int32 ControlsCount, RowsCount, JacobiansCount, IndicesCount;`

#### struct `VEUV::FLocalCornerState`  
`struct FLocalCornerState`  
_L92-99_
- L95 _public member_ `bool bSolved = false;` — If solved, this corner is effectively pinned
- L98 _public member_ `int32 Mapping = 0;` — The corner mapping assigned

#### struct `VEUV::FLocalSolveContext`  
`struct FLocalSolveContext`  
_L101-111_
- L104 _public member_ `FSparseResidualArray SparseResiduals;` — All residuals, influences are the corners
- L107 _public member_ `int32 LocalCornerCount = 0;` — Total number of corners allocated
- L110 _public member_ `TMap<int32, FLocalCornerState> CornerStates;` — All corners

#### struct `VEUV::FSolveRegion`  
`struct FSolveRegion`  
_L113-120_
- L116 _public member_ `Eigen::VectorXf SolvedUV;` — Solved UVs per corners, [U0, V0, U1, V1, ...]
- L119 _public member_ `TArray<int32> VoxelIndices;` — All voxels considered

#### struct `VEUV::FUVNormalization`  
`struct FUVNormalization`  
_L122-136_
- L124 _public function_ `Eigen::Vector2f Transform(const Eigen::Vector2f& UV) const`
- L132 _public member_ `float MinU = 0.0f;`
- L133 _public member_ `float MinV = 0.0f;`
- L134 _public member_ `float UniformScale = 1.0f;`
- L135 _public member_ `TBitArray<> CornerMasks;`

#### class `VEUV::FSolver`  
`class FSolver`  
_L138-222_
- L149 _public prototype_ `static void SolveContinuousField78( FVoxelGrid& Grid, FSolveRegion& Region, const TSharedPtr<FDebugCapture>& Capture );` — Solve the continuous parameterization with the R78 residuals. Progressively seeds one voxel then solves each subsequent voxel against already-pinned neighbours in a 3x3x3 neighbourhood LLS. @param Grid Parent grid @param Region Region to solve for @param Capture Optional, debug capture
- L162 _public prototype_ `static void SolveContinuousDenseField78( FVoxelGrid& Grid, FSolveRegion& Region, const TSharedPtr<FDebugCapture>& Capture );` — Solve the continuous parameterization with the R78 residuals. Globally solves voxels against initial seed set, instead of 3x3x3 LLS. @param Grid Parent grid @param Region Region to solve for @param Capture Optional, debug capture
- L176 _public prototype_ `static int32 SolveGlobalFieldR10( FVoxelGrid& Grid, FSolveRegion& Region, const FEigenMesh& Mesh, int32 MaxIterations, const TSharedPtr<FDebugCapture>& Capture );` — Solve the global parameterization with the R10 residuals ? Internally this computes R78 on top of R10 @param Grid Parent grid @param Region Region to solve for @param MaxIterations Maximum number of iterations @param Capture Optional, debug capture
- L192 _public prototype_ `static int32 SolveGlobalFieldR9AB( FVoxelGrid& Grid, FSolveRegion& Region, Schedulers::FAdam::FCoeffInvariantSnapshot& Snapshot, const VEUV::FEigenMesh& Mesh, int32 MaxIterations, bool bIsInitialSolve, bool bForceInjectivity, const TSharedPtr<FDebugCapture>& Capture );` — Solve the global parameterization with the R9 residuals ? Internally this computes R78 on top of R9 @param Grid Parent grid @param Region Region to solve for @param MaxIterations Maximum number of iterations @param Capture Optional, debug capture
- L208 _public prototype_ `static FUVNormalization GetNormalization( const FVoxelGrid& Grid, FSolveRegion& Region );` — Normalize the produced UV solution @param Grid Parent grid @param Region Region to normalize for
- L218 _public prototype_ `static void Normalize( const FVoxelGrid& Grid, FSolveRegion& Region );` — Normalize the produced UV solution @param Grid Parent grid @param Region Region to normalize for

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace VEUV`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVSplitMesh.h` (Private)


#### class `VEUV::FSplitMesh`  
`class FSplitMesh`  
_L15-49_
- L26 _public prototype_ `static void SplitByVoxels( FVoxelGrid& Grid, const FEigenMesh& InMesh, FEigenMesh& OutMesh, TArray<int32>& OutVertexVoxelIndices, TArray<FVertexSource>& OutVertexSources);` — Split a mesh by all voxels @param Grid Parent grid @param InMesh Mesh to split @param OutMesh Split mesh @param OutVertexVoxelIndices Optiona, voxel association @param OutVertexSources Optional, sources for interpolation
- L42 _public prototype_ `static void SplitByChartSeams( FVoxelGrid& Grid, const FGlobalSolveContext& SolveContext, const FEigenMesh& InMesh, FEigenMesh& OutMesh, TArray<int32>& OutVertexVoxelIndices, TArray<FVertexSource>& OutVertexSources);` — Split a mesh by the solution seams @param Grid Parent grid @param SolveContext The solution from which the seams are derived @param InMesh Mesh to split @param OutMesh Split mesh @param OutVertexVoxelIndices Optiona, voxel association @param OutVertexSources Optional, sources for interpolation

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace VEUV`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVValidation.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `# define VEUV_VALIDATE 0`
- L12 _macro_ `#define VEUV_DO_CHECK (VEUV_VALIDATE || UE_BUILD_DEBUG)`
- L14 _namespace_ `namespace VEUV`
- L16 _function_ `FORCEINLINE void CheckFinite([[maybe_unused]] float V)` (scope `VEUV`)
- L23 _function_ `FORCEINLINE void CheckFinite([[maybe_unused]] const Eigen::Vector3f& V)` (scope `VEUV`)
- L32 _function_ `FORCEINLINE void CheckNormalized([[maybe_unused]] const Eigen::Vector3f& V)` (scope `VEUV`)

### `Plugins/Experimental/VEUV/Source/VEUVCore/Private/VEUVVoxelGrid.h` (Private)


#### struct `VEUV::FVoxelEdge`  
`struct FVoxelEdge`  
_L11-15_
- L13 _public member_ `Eigen::Vector3i A;`
- L14 _public member_ `Eigen::Vector3i B;`

#### struct `VEUV::FSampleData`  
`struct FSampleData`  
_L33-38_
- L35 _public member_ `Eigen::Vector3f Position;`
- L36 _public member_ `Eigen::Vector3f Normal;`
- L37 _public member_ `EVEUVSampleType Type = EVEUVSampleType::None;`

#### struct `VEUV::FVoxelData`  
`struct FVoxelData`  
_L40-67_
- L43 _public member_ `Eigen::Vector3i ID = Eigen::Vector3i::Zero();` — Local coordinate
- L46 _public member_ `Eigen::Vector3f LogicalMin = Eigen::Vector3f::Zero();` — Logical bounds
- L47 _public member_ `Eigen::Vector3f LogicalMax = Eigen::Vector3f::Zero();`
- L50 _public member_ `Eigen::Vector3f SampleAverageNormal = Eigen::Vector3f::Zero();` — Average normal within this voxel
- L53 _public member_ `TArray<int32> Faces;` — All faces intersecting this voxel
- L56 _public member_ `TArray<FSampleData> Samples;` — All samples allocated to this voxel
- L59 _public member_ `TArray<float> FaceAreaWeights;` — Sample probabilities
- L60 _public member_ `TArray<float> FaceComplexityWeights;`
- L63 _public member_ `Eigen::Vector2f CornerUVs[8];` — Solved UVs
- L66 _public member_ `bool bVisited = false;` — Has this voxel been visited?

#### struct `VEUV::FNormalization`  
`struct FNormalization`  
_L69-85_
- L72 _public member_ `Eigen::Vector3f Center = Eigen::Vector3f::Zero();` — Origin
- L75 _public member_ `float Scale = 1.0f;` — Uniform scale
- L78 _public prototype_ `static FNormalization Compute(TArray<Eigen::Vector3f>& Vertices);` — Compute for a set of vertices
- L81 _public prototype_ `Eigen::Vector3f ToWorld(const Eigen::Vector3f& Normalized) const;` — Transform a normalized position to world space
- L84 _public prototype_ `void Denormalize(TArray<Eigen::Vector3f>& Vertices) const;` — Denormalize against a set of vertices

#### class `VEUV::FVoxelGrid`  
`class FVoxelGrid`  
_L87-174_
- L91 _public member_ `FVEUVConfig Config;` — Build config
- L94 _public member_ `FIntVector VoxelCount = FIntVector::ZeroValue;` — Active voxel count per axis. Equal to Config.VoxelCount except along near-flat axes
- L97 _public member_ `TArray<FVoxelData> Voxels;` — All allocated voxels
- L100 _public member_ `TMap<FIntVector, int32> VoxelIndexMap;` — Voxel coordinate to index
- L103 _public member_ `TArray<int32> CornerIndices;` — Sparse corner index set
- L104 _public member_ `int32 CornerAllocator = 0;`
- L107 _public member_ `Eigen::Vector3f LogicalMin = Eigen::Vector3f::Zero();` — Logical bounds
- L108 _public member_ `Eigen::Vector3f LogicalMax = Eigen::Vector3f::Zero();`
- L111 _public member_ `int32 SeedVoxelIndex = 0;` — Seeded voxel index
- L118 _public prototype_ `void Distribute(const TArray<Eigen::Vector3f>& Vertices, const FVEUVConfig& Config);` — Distribute all voxels @param Vertices Vertices to fit voxel bounds against @param Config Build config
- L124 _public prototype_ `void FindOverlappingVoxels(const Eigen::Vector3f& A, const Eigen::Vector3f& B, const Eigen::Vector3f& C, TArray<int32, TInlineAllocator<32>>& OutVoxelIndices) const;` — Find all voxels that overlap a triangle @param OutVoxelIndices Intersecting or contained voxel(s)
- L133 _public prototype_ `Eigen::Vector2f SampleUVVoxelLogical(const Eigen::VectorXf& SolvedUV, int32 VoxelIndex, const Eigen::Vector3f& LogicalPosition) const;` — Sample the UVs of a particular solution @param SolvedUV Solved region @param VoxelIndex Voxel index to sample against @param LogicalPosition Local position within the logical space, not whole container @return Evaluated UV
- L142 _public prototype_ `Eigen::Vector2f SampleUV(const Eigen::VectorXf& SolvedUV, int32 VoxelIndex, const Eigen::Vector3f& Position) const;` — Sample the UVs of a particular solution @param SolvedUV Solved region @param VoxelIndex Voxel index to sample against @param Position The grid wise position @return Evaluated UV
- L150 _public prototype_ `Eigen::Vector2f SampleUV(const Eigen::VectorXf& SolvedUV, const Eigen::Vector3f& Position) const;` — Sample the UVs of a particular solution @param SolvedUV Solved region @param Position The grid wise position @return Evaluated UV
- L157 _public prototype_ `int32 GetVoxelIndexAtPosition(const Eigen::Vector3f& Position) const;` — Find the voxel index that contains a position via floor lookup. @param Position The grid wise position @return Voxel index of Position clamped to grid bounds
- L163 _public prototype_ `int32 AllocateCornerIndex(int32 X, int32 Y, int32 Z);` — Allocate a new corner index @return Index, may be reused
- L169 _public function_ `int32 GetCornerIndex(int32 X, int32 Y, int32 Z) const` — Get a potentially allocated corner index @return INDEX_NONE if not allocated

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace VEUV`
- L17 _variable_ `static inline FVoxelEdge GVoxelLocalPositiveEdges[] = { { { 0, 0, 0 }, { 1, 0, 0 } }, { { 0, 0, 0 }, { 0, 1, 0 } }, { { 0, 0, 0 }, { 0, 0, 1 } }, { { 0, 1, 0 }, { 1, 1, 0 } }, { { 0, 1, 0 }, { 0, 1, 1 } }, { { 1, 0, 0 }, { 1, 1, 0 } }, { { 1, 0, 0 }, { 1, 0, 1 } }, { { 0, 0, 1 }, { 0, 1, 1 } }, { { 0, 0, 1 }, { 1, 0, 1 } }, { { 1, 1, 0 }, { 1, 1, 1 } }, { { 0, 1, 1 }, { 1, 1, 1 } }, { { 1, 0, 1 }, { 1, 1, 1 } }, };` (scope `VEUV`)

### `Plugins/Experimental/VEUV/Source/VEUVCore/Public/VEUV/VEUVDebugCapture.h` (Public)


#### struct `VEUV::FDebugCapture`  
`struct FDebugCapture`  
_L12-73_
- L47 _public member_ `FString SectionName;` — Optional, name of this capture
- L50 _public member_ `FDateTime Timestamp;` — Time built
- L53 _public member_ `FVEUVConfig Config;` — Config used during builds
- L56 _public member_ `bool bWithSnapshots = false;` — If true, user requested snapshot capturing
- L59 _public member_ `TArray<float> R78ErrorHistory;` — Error history
- L60 _public member_ `TArray<float> R9ErrorHistory;`
- L61 _public member_ `TArray<float> R9GradNormHistory;`
- L62 _public member_ `TArray<float> R10GradNormHistory;`
- L65 _public member_ `TArray<FGeometrySnapshot> Snapshots;` — Snapshot history
- L68 _public member_ `FResult Result;` — The full VEUV result
- L70 _public member_ `TArray<FChartEVDebug> ChartEVs;`
- L71 _public member_ `TArray<FDebugSample> Samples;`
- L72 _public member_ `TArray<FVoxelDebug> Voxels;`

#### struct `VEUV::FDebugCapture::FDebugSample`  
`struct FDebugSample`  
_L15-20_
- desc: Debug sample point in world space
- L17 _public member_ `FVector Position;`
- L18 _public member_ `FColor Color;`
- L19 _public member_ `EVEUVSampleType Type = EVEUVSampleType::None;`

#### struct `VEUV::FDebugCapture::FChartEVDebug`  
`struct FChartEVDebug`  
_L23-28_
- desc: Per-chart EV-orientation debug data
- L25 _public member_ `FVector2f Mean;`
- L26 _public member_ `FVector2f EV0;`
- L27 _public member_ `FVector2f EV1;`

#### struct `VEUV::FDebugCapture::FVoxelDebug`  
`struct FVoxelDebug`  
_L31-36_
- desc: World voxel data
- L33 _public member_ `FVector Center;`
- L34 _public member_ `FVector Extent;`
- L35 _public member_ `bool bOccupied = false;`

#### struct `VEUV::FDebugCapture::FGeometrySnapshot`  
`struct FGeometrySnapshot`  
_L39-44_
- desc: Solver geometry snapshot
- L41 _public member_ `FString Name;`
- L42 _public member_ `TArray<FInt32Vector3> Faces;`
- L43 _public member_ `TArray<FVector2f> VertexUVs;`

#### class `VEUV::FDebugHistory`  
`class FDebugHistory`  
_L75-115_
- L78 _public prototype_ `static FDebugHistory& Get();`
- L80 _public function_ `void Add(TSharedPtr<FDebugCapture> Capture)`
- L93 _public function_ `TArray<TSharedPtr<FDebugCapture>> GetCaptures() const`
- L99 _public function_ `void Clear()`
- L105 _public member_ `int32 MaxHistory = 32;`
- L107 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCaptureAdded);`
- L108 _public member_ `FOnCaptureAdded OnCaptureAdded;`
- L111 _private prototype_ `FDebugHistory() = default;`
- L113 _private member_ `mutable FCriticalSection CriticalSection;`
- L114 _private member_ `TArray<TSharedPtr<FDebugCapture>> Captures;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API VEUVCORE_API`
- L10 _namespace_ `namespace VEUV`
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCaptureAdded);`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Public/VEUV/VEUVMesh.h` (Public)


#### struct `VEUV::FMesh`  
`struct FMesh`  
_L9-16_
- L12 _public member_ `TArray<FVector3f> Vertices;` — All vertices, assumed all used
- L15 _public member_ `TArray<FInt32Vector3> Faces;` — All triangles

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace VEUV`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Public/VEUV/VEUVOptimizer.h` (Public)


#### class `VEUV::FOptimizer`  
`class FOptimizer`  
_L13-23_
- L22 _public prototype_ `static FResult Compute(const FMesh& InputMesh, const FVEUVConfig& Config);` — Create and optimize a UV parameterization for a given mesh @param InputMesh Mesh to parameterize for @param Config Optimization config @return Resulting mesh

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VEUVCORE_API`
- L11 _namespace_ `namespace VEUV`

### `Plugins/Experimental/VEUV/Source/VEUVCore/Public/VEUV/VEUVTypes.h` (Public)


#### enum `EVEUVSampleType`  
`enum class EVEUVSampleType : uint8`  
_L10-16_
- desc: Sample type classification
- L12 _public enumerator_ `None`
- L13 _public enumerator_ `Area`
- L14 _public enumerator_ `Complexity`
- L15 _public enumerator_ `Adaptive`

#### enum `EVEUVVisualizationDebugMode`  
`enum class EVEUVVisualizationDebugMode : uint8`  
_L19-28_
- reflection: `UENUM()`
- L22 _public enumerator_ `None` — Write the actual UVs
- L25 _public enumerator_ `P_Area` — Debug, write the normalized probabilities
- L26 _public enumerator_ `P_Complexity`
- L27 _public enumerator_ `P_Combined`

#### struct `FVEUVSamplingConfig`  
`struct FVEUVSamplingConfig`  
_L31-70_
- reflection: `USTRUCT()`
- L37 _public member_ `int32 TotalSamples = 4096;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=1))` — Total sample budget, distributed across budgets
- L41 _public member_ `float ComplexityAlpha = 5.0f;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=0.0))` — Complexity amplification, 0 -> pure area sampling
- L45 _public member_ `float ComplexityBlend = 0.5f;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=0.0, ClampMax=1.0))` — Fraction of samples allocated to complex areas compared to area sampling
- L49 _public member_ `int32 ComplexityNormalBins = 12;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=1, ClampMax=128))` — Number of normal bins for complexity samples
- L53 _public member_ `float ComplexityFieldCellSize = 256.0f;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=1.0))` — Absolute size of each complexity field cell
- L57 _public member_ `int32 ComplexityFieldMaxResolution = 64;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=2, ClampMax=256))` — Hard limit to number of complexity fields per axis
- L61 _public member_ `int32 ComplexityDilutionIterations = 2;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=0, ClampMax=32))` — Number of dilution iterations for the complexity field
- L65 _public member_ `int32 AdaptiveSubdivisions = 4;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=0, ClampMax=16))` — Number of sub-cells for adaptive sampling
- L69 _public member_ `float AdaptiveFraction = 0.5f;` — `UPROPERTY(EditAnywhere, Category="Sampling", meta=(ClampMin=0.0, ClampMax=1.0))` — Fraction of total samples to allocate for adaptive samples

#### struct `FVEUVSolverConfig`  
`struct FVEUVSolverConfig`  
_L73-156_
- reflection: `USTRUCT()`
- L79 _public member_ `bool bEnableDiscreteLaplace = true;` — `UPROPERTY(EditAnywhere, Category="Solver")` — Enable standard Hessian discrete Laplacian regularization
- L83 _public member_ `bool bEnableDiagonalLMDamping = true;` — `UPROPERTY(EditAnywhere, Category="Solver")` — Enable Hessian nudge regularization
- L87 _public member_ `bool bEnableGlobalSolve = true;` — `UPROPERTY(EditAnywhere, Category="Solver")` — Enable the R9 global area-preservation solve.
- L91 _public member_ `float DiagonalNudgeAlpha = 1e-6f;` — `UPROPERTY(EditAnywhere, Category="Solver", meta=(ClampMin=0.0, ClampMax=1.0))` — Hessian regularization alpha
- L95 _public member_ `int32 GlobalIterations = 1000;` — `UPROPERTY(EditAnywhere, Category="Solver", meta=(ClampMin=1, ClampMax=10000))` — Number of R9 global solve iterations
- L99 _public member_ `float GlobalSolveLR = 1e-2f;` — `UPROPERTY(EditAnywhere, Category="Solver", meta=(ClampMin=0.0, ClampMax=1.0))` — Learning rate for the global R9 solve
- L108 _public member_ `float GlobalSolveR9abRegAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Solver", meta=(ClampMin=0.0))` — Regularization alpha between R78 and R9ab. R78 + R9ab * K * Alpha Higher values allocates more importance to area preservation, but sacrifices orthogonality and conformity.
- L118 _public member_ `float GlobalSolveR10RegAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Solver", meta=(ClampMin=0.0))` — Regularization alpha between R78 and R10. R78 + R10 * K * Alpha Higher values allocates more importance to map injectivity, but sacrifices orthogonality and conformity, and area preservation (indirectly).
- L125 _public member_ `bool bGlobalSolveGDFirstOrder = true;` — `UPROPERTY(EditAnywhere, Category="Solver")` — If true, uses implicit gradients with back-propagation instead of solving through the Hessian form. Much faster, but loses second order information (* not used yet).
- L131 _public member_ `bool bEnableInjectiveTerm = false;` — `UPROPERTY(EditAnywhere, Category="Solver")` — If true, enables a general injectivity conforming pre-pass that better pre-conditions the R9ab solve pass.
- L138 _public member_ `bool bGlobalSolveEnableLinearPrecond = true;` — `UPROPERTY(EditAnywhere, Category="Solver")` — If true, enables a linear (Cholesky) solve of the non-linear system as if it was linear to act as a pre-conditioning, reduces the amount of iterations required.
- L145 _public member_ `bool bEnableChartRefinement = true;` — `UPROPERTY(EditAnywhere, Category="Solver")` — Enable per-chart R9 refinement after charting. Individual charts will have a much easier time optimizing in isolation.
- L151 _public member_ `bool bChartRefinementForceInjectivity = false;` — `UPROPERTY(EditAnywhere, Category="Solver")` — If true, forces injectivity of each separate chart through a R10 hard constraint
- L155 _public member_ `float ChartRefinementIterationFraction = 0.2f;` — `UPROPERTY(EditAnywhere, Category="Solver", meta=(ClampMin=0.0, ClampMax=1.0))` — Fraction of GlobalIterations used for per-chart refinement.

#### struct `FVEUVChartingConfig`  
`struct FVEUVChartingConfig`  
_L159-178_
- reflection: `USTRUCT()`
- L165 _public member_ `bool bEnableRasterization = true;` — `UPROPERTY(EditAnywhere, Category="Charting")` — Enable rasterization-based overlap detection
- L169 _public member_ `int32 RasterizationWidth = 256;` — `UPROPERTY(EditAnywhere, Category="Charting", meta=(ClampMin=16, ClampMax=4096))` — Rasterization width for overlap detection
- L173 _public member_ `bool bEnableOverlapChecks = true;` — `UPROPERTY(EditAnywhere, Category="Charting")` — Enable overlap detection, if false, single charting
- L177 _public member_ `float UVRectOverlapEpsilon = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Charting", meta=(ClampMin=0.0))` — Epsilon for chart UV-rect checks

#### struct `FVEUVPackingConfig`  
`struct FVEUVPackingConfig`  
_L181-200_
- reflection: `USTRUCT()`
- L187 _public member_ `bool bEnableChartReorientation = true;` — `UPROPERTY(EditAnywhere, Category="Packing")` — Enable PCA-based chart reorientation for tighter packing
- L191 _public member_ `bool bEnableAtlasPacking = true;` — `UPROPERTY(EditAnywhere, Category="Packing")` — Enable atlas packing, if false, charts have no spatial relation
- L195 _public member_ `bool bEnableUVNormalization = false;` — `UPROPERTY(EditAnywhere, Category="Packing")` — Enable per-chart normalization, only relevant when packing is disabled
- L199 _public member_ `int32 AtlasPackWidth = 512;` — `UPROPERTY(EditAnywhere, Category="Packing", meta=(ClampMin=16, ClampMax=8192))` — Atlas packing width in texels

#### struct `FVEUVConfig`  
`struct FVEUVConfig`  
_L203-260_
- reflection: `USTRUCT()`
- L207 _public member_ `static FVEUVConfig Default;`
- L213 _public member_ `static const FGuid AlgorithmVersionGuid;` — Identity of the VEUV algorithm and its built-in defaults -- Regenerate when algorithm or default-config changes could cause a different result for same input
- L216 _public function_ `static FVEUVConfig LowQuality()` — Helper for a low-quality/fast-iteration build
- L227 _public member_ `const TCHAR* Label = TEXT("Sta` — Debugging label for this build
- L231 _public member_ `FIntVector VoxelCount = FIntVector(4, 4, 4);` — `UPROPERTY(EditAnywhere, Category="Grid", meta=(ClampMin=1, ClampMax=64))` — Number of voxels per axis
- L235 _public member_ `FTransform DebugWorldTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category="Debug")` — Optional, world transform for debug drawing. Applied to all debug points/boxes.
- L239 _public member_ `EVEUVVisualizationDebugMode UVVisualizeMode = EVEUVVisualizationDebugMode::None;` — `UPROPERTY(EditAnywhere, Category="Debug")` — Optional, visualizes certain attributes in the UV channels
- L243 _public member_ `bool bEnableVertexNormalization = true;` — `UPROPERTY(EditAnywhere, Category="Grid")` — Normalize vertices to [-1, 1], for most geometry this is required for well-formed optimization
- L247 _public member_ `FVEUVSamplingConfig Sampling;` — `UPROPERTY(EditAnywhere, Category="Config")` — Sampling settings
- L251 _public member_ `FVEUVSolverConfig Solver;` — `UPROPERTY(EditAnywhere, Category="Config")` — Solution solver settings
- L255 _public member_ `FVEUVChartingConfig Charting;` — `UPROPERTY(EditAnywhere, Category="Config")` — Charting settings
- L259 _public member_ `FVEUVPackingConfig Packing;` — `UPROPERTY(EditAnywhere, Category="Config")` — Atlas packing settings

#### enum `VEUV::EChartStatus`  
`enum class EChartStatus : uint8`  
_L264-271_
- L266 _public enumerator_ `Valid = 0`
- L267 _public enumerator_ `Empty = 1 << 0` — No voxels / no faces in this chart
- L268 _public enumerator_ `NonFinite = 1 << 1` — At least one vertex UV is NaN/Inf
- L269 _public enumerator_ `PackingFailed = 1 << 2` — Atlas packer couldn't allocate this chart at any power
- L270 _public enumerator_ `Inverted = 1 << 3` — At least one face has UV winding opposite to chart majority

#### struct `VEUV::FChart`  
`struct FChart`  
_L274-290_
- L277 _public member_ `TArray<int32> VoxelIndices;` — All voxels belonging to this chart
- L280 _public member_ `FBox2f Bounds = FBox2f(FVector2f(MAX_flt, MAX_flt), FVector2f(-MAX_flt, -MAX_flt));` — Axis aligned UV bounds
- L283 _public member_ `FBox2f PackedBounds = FBox2f(FVector2f(0.0f, 0.0f), FVector2f(0.0f, 0.0f));` — UV bounds after atlas allocation
- L286 _public member_ `float Area = 0.0f;` — World surface area
- L289 _public member_ `EChartStatus Status = EChartStatus::Valid;` — Per-chart status flags

#### struct `VEUV::FStatistics`  
`struct FStatistics`  
_L292-373_
- L294 _public member_ `double DistributeMs = 0;`
- L295 _public member_ `double SplitFacesMs = 0;`
- L296 _public member_ `double SampleVoxelsMs = 0;`
- L297 _public member_ `double ContinuousField78Ms = 0;`
- L298 _public member_ `double GlobalField9Ms = 0;`
- L299 _public member_ `int32 GlobalField9Iterations = 0;`
- L300 _public member_ `double GlobalField10Ms = 0;`
- L301 _public member_ `int32 GlobalField10Iterations = 0;`
- L302 _public member_ `double NormalizeMs = 0;`
- L303 _public member_ `double ChartingMs = 0;`
- L304 _public member_ `double ChartRefinementMs = 0;`
- L305 _public member_ `int32 ChartRefinementIterations = 0;`
- L306 _public member_ `double ReorientMs = 0;`
- L307 _public member_ `double PackMs = 0;`
- L308 _public member_ `double SplitFacesChartMs = 0;`
- L309 _public member_ `double EvalUVsMs = 0;`
- L310 _public member_ `double AdaptiveResampleMs = 0;`
- L311 _public member_ `double TotalMs = 0;`
- L313 _public member_ `const TCHAR* Label = nullptr;`
- L314 _public member_ `int32 InputVertices = 0;`
- L315 _public member_ `int32 InputFaces = 0;`
- L316 _public member_ `int32 OutputVertices = 0;`
- L317 _public member_ `int32 OutputFaces = 0;`
- L318 _public member_ `int32 ChartCount = 0;`
- L319 _public member_ `int32 VoxelCount = 0;`
- L320 _public member_ `int32 OccupiedVoxels = 0;`
- L321 _public member_ `int32 TotalSamples = 0;`
- L322 _public member_ `int32 AdaptiveSamplesAdded = 0;`
- L323 _public member_ `FIntVector ComplexityFieldResolution = FIntVector::ZeroValue;`
- L324 _public member_ `int32 RasterizationWidth = 0;`
- L325 _public member_ `int32 InvertedFaceCount = 0;`
- L326 _public member_ `int32 UnassignedFaceCount = 0;`
- L327 _public member_ `int32 FailedChartCount = 0;`
- L328 _public member_ `float InvertedUVArea = 0.0f;` — Sum of |signed UV area| over inverted faces
- L329 _public member_ `float TotalUVArea = 0.0f;` — Sum of |signed UV area| over all faces
- L331 _public function_ `FString ToString() const`
- L369 _public function_ `void Log() const`

#### struct `VEUV::FVertexSource`  
`struct FVertexSource`  
_L375-379_
- L377 _public member_ `int32 Vertices[3] = { INDEX_NONE, INDEX_NONE, INDEX_NONE };`
- L378 _public member_ `float Weights[3] = { 1.0f, 0.0f, 0.0f };`

#### struct `VEUV::FResult`  
`struct FResult`  
_L381-403_
- L384 _public member_ `FMesh OutputMesh;` — Resulting mesh, may have splits
- L387 _public member_ `TArray<FVector2f> VertexUVs;` — Produced vertex UVs, same indexing as output mesh.
- L390 _public member_ `TArray<FChart> Charts;` — All produced charts
- L393 _public member_ `TArray<int32> FaceChartIndices;` — Per-face chart index (-1 if unassigned)
- L396 _public member_ `TArray<FVertexSource> VertexSources;` — Interpolation sources for additional attributes, for reconstructing additional attributes and interpolating on splits
- L399 _public member_ `FStatistics Stats;` — Timing statistics
- L402 _public member_ `EChartStatus Status = EChartStatus::Valid;` — Bitwise-OR of per-chart statuses. Equals EChartStatus::Valid (0) iff every chart is Valid. Collection-level concerns (e.g. unassigned faces) are reported via FStatistics.

#### Free symbols / members of external scopes

- L262 _namespace_ `namespace VEUV`
- L272 _prototype_ `ENUM_CLASS_FLAGS(EChartStatus);` (scope `VEUV`)
