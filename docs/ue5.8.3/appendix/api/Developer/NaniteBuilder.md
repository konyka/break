# Developer / NaniteBuilder

- module root: `Source/Developer/NaniteBuilder`
- headers: 19; symbols: 532
- symbol kinds: class=9, function=101, macro=2, member=268, namespace=17, prototype=90, struct=38, typedef=5, union=1, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, GeometryCore, ImageCore, NaniteUtilities, QuadricMeshReduction, RenderCore
- PrivateIncludePathModuleNames: MeshUtilitiesCommon

### `Source/Developer/NaniteBuilder/Private/BVHCluster.h` (Private)


#### class `FBVHCluster`  
`class FBVHCluster`  
_L9-35_
- L12 _public prototype_ `FBVHCluster( uint32 InNumElements, uint32 InMinPartitionSize, uint32 InMaxPartitionSize );`
- L15 _public prototype_ `template< typename FGetBounds > void Build( const FGetBounds& GetBounds );`
- L17 _public member_ `TArray< FRange > Ranges;`
- L18 _public member_ `TArray< uint32 > Indexes;`
- L19 _public member_ `TArray< uint32 > SortedTo;`
- L23 _private prototype_ `template< typename FGetBounds > void Build( uint32 Offset, uint32 Num, const FGetBounds& GetBounds );`
- L25 _private prototype_ `template< typename FGetBounds > uint32 Split( uint32 Offset, uint32 Num, const FGetBounds& GetBounds );`
- L27 _private prototype_ `template< typename FGetBounds > void Sort( uint32* RESTRICT Dst, uint32* RESTRICT Src, uint32 Num, int32 Dim, const FGetBounds& GetBounds );`
- L29 _private member_ `uint32 NumElements;`
- L30 _private member_ `uint32 MinPartitionSize;`
- L31 _private member_ `uint32 MaxPartitionSize;`
- L33 _private member_ `TArray< float > CostLeft;`
- L34 _private member_ `TArray< float > CostRight;`
- L38 _function_ `template< typename FGetBounds > void FBVHCluster::Build( const FGetBounds& GetBounds )`
- L47 _function_ `template< typename FGetBounds > void FBVHCluster::Build( uint32 Offset, uint32 Num, const FGetBounds& GetBounds )`
- L66 _function_ `template< typename FGetBounds > uint32 FBVHCluster::Split( uint32 Offset, uint32 Num, const FGetBounds& GetBounds )`
- L144 _function_ `template< typename FGetBounds > void FBVHCluster::Sort( uint32* RESTRICT Dst, uint32* RESTRICT Src, uint32 Num, int32 Dim, const FGetBounds& GetBounds )`

#### union `FBVHCluster::Sort::__anon9d1f68220102::(anonymous)`  
`union`  
_L151-151_

#### Free symbols / members of external scopes

- L148 _function_ `` (scope `FBVHCluster::Sort`)
- L151 _member_ `union { float f; uint32 i; } Center;` (scope `FBVHCluster::Sort::__anon9d1f68220102::__anon9d1f6822020a`)
- L151 _member_ `union { float f; uint32 i; } Center;` (scope `FBVHCluster::Sort::__anon9d1f68220102::__anon9d1f6822020a`)

### `Source/Developer/NaniteBuilder/Private/Cluster.h` (Private)


#### class `Nanite::FClusterRef`  
`class FClusterRef`  
_L24-44_
- L27 _public member_ `uint32 InstanceIndex;`
- L28 _public member_ `uint32 ClusterIndex;`
- L30 _public function_ `explicit FClusterRef( uint32 InClusterIndex ) : InstanceIndex( MAX_uint32 ) , ClusterIndex( InClusterIndex )`
- L34 _public function_ `explicit FClusterRef( uint32 InInstanceIndex, uint32 InClusterIndex ) : InstanceIndex( InInstanceIndex ) , ClusterIndex( InClusterIndex )`
- L39 _public function_ `bool IsInstance() const`
- L41 _public prototype_ `FCluster& GetCluster( FClusterDAG& DAG ) const;`
- L42 _public prototype_ `const FCluster& GetCluster( const FClusterDAG& DAG ) const;`
- L43 _public prototype_ `const FMatrix44f& GetTransform( const FClusterDAG& DAG ) const;`

#### struct `Nanite::FVertexFormat`  
`struct FVertexFormat`  
_L46-88_
- L48 _public member_ `uint8 NumTexCoords = 0;`
- L49 _public member_ `uint8 NumBoneInfluences = 0;`
- L50 _public member_ `bool bHasTangents : 1 = false;`
- L51 _public member_ `bool bHasCurveRadius : 1 = false;`
- L52 _public member_ `bool bHasColors : 1 = false;`
- L54 _public function_ `FORCEINLINE bool Matches( const FVertexFormat& Other ) const`
- L64 _public function_ `FORCEINLINE uint8 GetCurveRadiusOffset() const`
- L69 _public function_ `FORCEINLINE uint8 GetColorOffset() const`
- L74 _public function_ `FORCEINLINE uint8 GetUVOffset() const`
- L79 _public function_ `FORCEINLINE uint8 GetBoneInfluenceOffset() const`
- L84 _public function_ `FORCEINLINE uint8 GetVertSize() const`

#### class `Nanite::FVertexArray`  
`class FVertexArray`  
_L90-155_
- L93 _public member_ `TArray< float > Array;`
- L94 _public member_ `FVertexFormat Format;`
- L97 _private member_ `uint32 NumVerts = 0;`
- L98 _private member_ `uint8 CurveRadiusOffset;`
- L99 _private member_ `uint8 ColorOffset;`
- L100 _private member_ `uint8 UVOffset;`
- L101 _private member_ `uint8 BoneInfluenceOffset;`
- L102 _private member_ `uint8 VertSize;`
- L105 _public prototype_ `FVertexArray() = default;`
- L106 _public prototype_ `FVertexArray( const FVertexFormat& InFormat );`
- L108 _public prototype_ `void InitFormat();`
- L109 _public prototype_ `void CopyAttributes( uint32 DstVertIndex, uint32 SrcVertIndex, const FVertexArray& SrcVerts );`
- L110 _public prototype_ `void LerpAttributes( uint32 DstVertIndex, const FUintVector3& SrcVertIndexes, const FVertexArray& SrcVerts, const FVector3f& Barycentrics );`
- L111 _public prototype_ `uint32 FindOrAddHash( const float* Vert, uint32 VertIndex, FHashTable& HashTable ) const;`
- L112 _public prototype_ `void Sanitize();`
- L114 _public prototype_ `uint32 AddUninitialized( uint32 Count = 1 );`
- L115 _public prototype_ `uint32 Add( const void* Vert, uint32 Count = 1 );`
- L116 _public prototype_ `void RemoveAt( uint32 VertIndex, uint32 Count = 1 );`
- L118 _public function_ `FORCEINLINE uint8 GetVertSize() const`
- L119 _public function_ `FORCEINLINE uint32 Num() const`
- L120 _public function_ `FORCEINLINE void Reserve( uint32 Count )`
- L121 _public function_ `FORCEINLINE void SetNum( uint32 Count )`
- L123 _public function_ `FORCEINLINE FVector3f& GetPosition( uint32 VertIndex )`
- L124 _public function_ `FORCEINLINE float* GetAttributes( uint32 VertIndex )`
- L125 _public function_ `FORCEINLINE FVector3f& GetNormal( uint32 VertIndex )`
- L126 _public function_ `FORCEINLINE FVector3f& GetTangentX( uint32 VertIndex )`
- L127 _public function_ `FORCEINLINE float& GetTangentYSign( uint32 VertIndex )`
- L128 _public function_ `FORCEINLINE float& GetCurveRadius( uint32 VertIndex )`
- L129 _public function_ `FORCEINLINE FLinearColor& GetColor( uint32 VertIndex )`
- L130 _public function_ `FORCEINLINE FVector2f* GetUVs( uint32 VertIndex )`
- L131 _public function_ `FORCEINLINE FVector2f* GetBoneInfluences( uint32 VertIndex )`
- L133 _public function_ `FORCEINLINE const FVector3f& GetPosition( uint32 VertIndex ) const`
- L134 _public function_ `FORCEINLINE const float* GetAttributes( uint32 VertIndex ) const`
- L135 _public function_ `FORCEINLINE const FVector3f& GetNormal( uint32 VertIndex ) const`
- L136 _public function_ `FORCEINLINE const FVector3f& GetTangentX( uint32 VertIndex ) const`
- L137 _public function_ `FORCEINLINE const float& GetTangentYSign( uint32 VertIndex ) const`
- L138 _public function_ `FORCEINLINE const float& GetCurveRadius( uint32 VertIndex ) const`
- L139 _public function_ `FORCEINLINE const FLinearColor& GetColor( uint32 VertIndex ) const`
- L140 _public function_ `FORCEINLINE const FVector2f* GetUVs( uint32 VertIndex ) const`
- L141 _public function_ `FORCEINLINE const FVector2f* GetBoneInfluences( uint32 VertIndex ) const`
- L145 _private function_ `template< typename T > FORCEINLINE T* Fetch( uint32 VertIndex, uint32 Offset )`
- L151 _private function_ `template< typename T > FORCEINLINE const T* Fetch( uint32 VertIndex, uint32 Offset ) const`
- L157 _function_ `FORCEINLINE FVertexArray::FVertexArray( const FVertexFormat& InFormat ) : Format( InFormat )`
- L163 _function_ `FORCEINLINE void FVertexArray::InitFormat()`
- L172 _function_ `FORCEINLINE uint32 FVertexArray::AddUninitialized( uint32 Count )`
- L180 _function_ `FORCEINLINE uint32 FVertexArray::Add( const void* Verts, uint32 Count )`
- L187 _function_ `FORCEINLINE void FVertexArray::RemoveAt( uint32 VertIndex, uint32 Count )`

#### struct `Nanite::FMaterialRange`  
`struct FMaterialRange`  
_L193-201_
- L195 _public member_ `uint32 RangeStart;`
- L196 _public member_ `uint32 RangeLength;`
- L197 _public member_ `uint32 MaterialIndex;`
- L198 _public member_ `TArray<uint8, TInlineAllocator<12>> BatchTriCounts;`

#### struct `Nanite::FStripDesc`  
`struct FStripDesc`  
_L203-210_
- L205 _public member_ `uint32 Bitmasks[4][3] = {};`
- L206 _public member_ `uint32 NumPrevRefVerticesBeforeDwords = 0;`
- L207 _public member_ `uint32 NumPrevNewVerticesBeforeDwords = 0;`

#### class `Nanite::FCluster`  
`class FCluster`  
_L213-329_
- L216 _public function_ `FCluster()`
- L219 _public prototype_ `FCluster( const FConstMeshBuildVertexView& InVerts, TArrayView< const uint32 > InIndexes, TArrayView< const int32 > InMaterialIndexes, const FVertexFormat& InFormat, uint32 Begin, uint32 End, TArrayView< const uint32 > SortedIndexes, TArrayView< const uint32 > SortedTo, const FAdjacency& Adjacency );` — Triangle
- L229 _public prototype_ `FCluster( FCluster& SrcCluster, uint32 Begin, uint32 End, TArrayView< const uint32 > SortedIndexes, TArrayView< const uint32 > SortedTo, const FAdjacency& Adjacency );`
- L236 _public prototype_ `FCluster( const FClusterDAG& DAG, TArrayView< const FClusterRef > Children );`
- L239 _public prototype_ `FCluster( const FConstMeshBuildVertexView& InVerts, TArrayView< const FCurveIndex > InCurveIndexes, TArrayView< const int32 > InMaterialIndexes, const FVertexFormat& InFormat, uint32 Begin, uint32 End, TArrayView< const uint32 > SortedCurveIndexes);` — Curve
- L247 _public prototype_ `float SimplifyTriangles( const FClusterDAG& DAG, uint32 TargetNumTris, float TargetError = 0.0f, uint32 LimitNumTris = 0, const FRayTracingFallbackBuildSettings* RayTracingFallbackBuildSettings = nullptr );`
- L248 _public prototype_ `float SimplifyCurves( const FClusterDAG& DAG, uint32 TargetNumCurves, uint32 TargetNumSegments, float TargetError = 0.0f, uint32 LimitNumCurves = 0, const FRayTracingFallbackBuildSettings* RayTracingFallbackBuildSettings = nullptr );`
- L249 _public prototype_ `FAdjacency BuildAdjacency() const;`
- L250 _public prototype_ `void Split( FGraphPartitioner& Partitioner, const FAdjacency& Adjacency ) const;`
- L251 _public prototype_ `void Bound();`
- L252 _public prototype_ `void Voxelize( FClusterDAG& DAG, TArrayView< const FClusterRef > Children, float VoxelSize );`
- L253 _public prototype_ `void BuildMaterialRanges();`
- L255 _public function_ `FORCEINLINE bool IsVoxel() const`
- L256 _public function_ `FORCEINLINE bool IsCurve() const`
- L260 _private prototype_ `template< typename TTransformFunc > uint32 AddVertMismatched( uint32 SrcVertIndex, const FCluster& SrcCluster, FHashTable& HashTable, TTransformFunc&& TransformFunc );`
- L262 _private prototype_ `void CopyAttributes( uint32 DstVertIndex, uint32 SrcVertIndex, const FCluster& SrcCluster );`
- L263 _private prototype_ `void LerpAttributes( uint32 DstVertIndex, uint32 SrcTriIndex, const FCluster& SrcCluster, const FVector3f& Barycentrics );`
- L264 _private prototype_ `void VoxelsToBricks( TSparseMap< FIntVector3, uint32 >& VoxelMap );`
- L269 _public member_ `static const uint32 ClusterSize = 128;`
- L270 _public member_ `static const uint32 MaxNumSegmentPerCluster = NANITE_MAX_CLUSTER_VERTICES;`
- L272 _public member_ `uint32 NumTris = 0;`
- L274 _public member_ `FVertexArray Verts;`
- L275 _public member_ `TArray< uint32 > Indexes;`
- L276 _public member_ `TArray< int32 > MaterialIndexes;`
- L278 _public member_ `uint32 NumCurves = 0;`
- L279 _public member_ `TArray<FCurveIndex> CurveIndexes;`
- L280 _public member_ `uint32 CurveFadingIndex = 0;`
- L283 _public member_ `TArray< FIntVector3 > ExtraVoxels;`
- L286 _public member_ `TArray< uint8 > ExternalEdges;`
- L287 _public member_ `uint32 NumExternalEdges = 0;`
- L289 _public member_ `TArray< uint32 > ExtendedData;`
- L292 _public member_ `TBitArray<> VoxelTriangle;` — whether the triangle is a proxy for a voxel/brick
- L293 _public member_ `bool bHasVoxelTriangles = false;`
- L301 _public member_ `TArray< FBrick > Bricks;`
- L303 _public member_ `FBounds3f Bounds;`
- L304 _public member_ `uint64 GUID = 0;`
- L305 _public member_ `int32 MipLevel = 0;`
- L307 _public member_ `FIntVector QuantizedPosStart = { 0u, 0u, 0u };`
- L308 _public member_ `int32 QuantizedPosPrecision = 0u;`
- L309 _public member_ `FIntVector QuantizedPosBits = { 0u, 0u, 0u };`
- L311 _public member_ `float EdgeLength = 0.0f;`
- L312 _public member_ `float LODError = 0.0f;`
- L313 _public member_ `float SurfaceArea = 0.0f;`
- L314 _public member_ `float ParentLODError = 0.f;`
- L315 _public member_ `float ParentSphereBoundRadius = 0.f;`
- L317 _public member_ `FSphere3f SphereBounds;`
- L318 _public member_ `FSphere3f LODBounds;`
- L320 _public member_ `uint32 GroupIndex = MAX_uint32;`
- L321 _public member_ `uint32 GeneratingGroupIndex= MAX_uint32;`
- L322 _public member_ `uint32 PageIndex = MAX_uint32;`
- L324 _public member_ `TArray<FMaterialRange, TInlineAllocator<4>> MaterialRanges;`
- L325 _public member_ `TArray<FIntVector> QuantizedPositions;`
- L327 _public member_ `FStripDesc StripDesc;`
- L328 _public member_ `TArray<uint8> StripIndexData;`

#### struct `Nanite::FCluster::FBrick`  
`struct FBrick`  
_L295-300_
- L297 _public member_ `uint64 VoxelMask;`
- L298 _public member_ `FIntVector3 Position;`
- L299 _public member_ `uint32 VertOffset;`

#### struct `Nanite::FClusterAreaWeightedTriangleSampler`  
`struct FClusterAreaWeightedTriangleSampler : FWeightedRandomSampler`  
_L331-341_
- inherits: `FWeightedRandomSampler`
- L333 _public prototype_ `FClusterAreaWeightedTriangleSampler();`
- L334 _public prototype_ `void Init(const FCluster* InCluster);`
- L338 _protected prototype_ `virtual float GetWeights(TArray<float>& OutWeights)override;`
- L340 _protected member_ `const FCluster* Cluster;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define RAY_TRACE_VOXELS 1`
- L16 _namespace_ `namespace Nanite`

### `Source/Developer/NaniteBuilder/Private/ClusterDAG.h` (Private)


#### struct `Nanite::FClusterCurveStats`  
`struct FClusterCurveStats`  
_L20-27_
- L22 _public member_ `uint32 MinPointPerCurve = 0;`
- L23 _public member_ `uint32 MaxPointPerCurve = 0;`
- L24 _public member_ `uint32 AvgPointPerCurve = 0;`
- L26 _public member_ `uint32 TotalPointCount = 0;`

#### struct `Nanite::FClusterGroup`  
`struct FClusterGroup`  
_L33-46_
- L35 _public member_ `FSphere3f Bounds;`
- L36 _public member_ `FSphere3f LODBounds;`
- L37 _public member_ `float ParentLODError = 0.0f;`
- L38 _public member_ `int32 MipLevel = 0;`
- L39 _public member_ `uint32 MeshIndex = MAX_uint32;`
- L40 _public member_ `uint32 AssemblyPartIndex = MAX_uint32;`
- L41 _public member_ `bool bTrimmed = false;`
- L42 _public member_ `bool bRoot = false;`
- L44 _public member_ `FPageRangeKey PageRangeKey;`
- L45 _public member_ `TArray< FClusterRef > Children;`

#### struct `Nanite::FAssemblyPartData`  
`struct FAssemblyPartData`  
_L48-52_
- L50 _public member_ `uint32 FirstInstance = MAX_uint32;`
- L51 _public member_ `uint32 NumInstances = 0;`

#### struct `Nanite::FAssemblyInstanceData`  
`struct FAssemblyInstanceData`  
_L54-63_
- L56 _public member_ `FMatrix44f Transform;`
- L57 _public member_ `FSphere3f LODBounds;` — TODO Index the referencing group instead of copying its properties.
- L58 _public member_ `float ParentLODError;`
- L59 _public member_ `uint32 RootClusterIndex;`
- L60 _public member_ `uint32 RootGroupIndex;`
- L61 _public member_ `uint32 FirstBoneInfluence;`
- L62 _public member_ `uint32 NumBoneInfluences;`

#### class `Nanite::FClusterDAG`  
`class FClusterDAG`  
_L65-148_
- L68 _public function_ `FClusterDAG()`
- L70 _public prototype_ `void AddMesh( const FConstMeshBuildVertexView& Verts, TArrayView< const uint32 > Indexes, TArrayView< const int32 > MaterialIndexes, const FBounds3f& VertexBounds, const FVertexFormat& VertexFormat );`
- L77 _public prototype_ `void AddCurves( const FConstMeshBuildVertexView& Verts, TArrayView< const FCurveIndex > CurveIndexes, TArrayView< const int32 > MaterialIndexes, const FBounds3f& VertexBounds, const FVertexFormat& VertexFormat );`
- L84 _public function_ `void AddEmptyMesh()`
- L86 _public prototype_ `void ReduceMesh( uint32 MeshIndex );`
- L88 _public prototype_ `void FindCut( TArray< FClusterRef >& SelectedClusters, TSet< uint32 >& SelectedGroups, uint32 TargetNumTris, float TargetError, uint32 TargetOvershoot ) const;`
- L95 _public member_ `TArray< FCluster > Clusters;`
- L96 _public member_ `TArray< FClusterGroup > Groups;`
- L98 _public member_ `TArray< FAssemblyPartData > AssemblyPartData;`
- L99 _public member_ `TArray< FAssemblyInstanceData > AssemblyInstanceData;`
- L100 _public member_ `TArray< FVector2f > AssemblyBoneInfluences;`
- L102 _public member_ `TArray< TArray< FClusterRef >, TInlineAllocator<1> > MeshInput;`
- L106 _public member_ `FRayTracingScene RayTracingScene;` — TODO Always creates
- L109 _public member_ `FBounds3f TotalBounds;`
- L110 _public member_ `float SurfaceArea = 0.0f;`
- L125 _public member_ `FSettings Settings;`
- L127 _public member_ `bool bHasSkinning : 1 = false;`
- L128 _public member_ `bool bHasTangents : 1 = false;`
- L129 _public member_ `bool bHasCurveRadius : 1 = false;`
- L130 _public member_ `bool bHasColors : 1 = false;`
- L132 _public member_ `uint8 MaxTexCoords = 0;`
- L133 _public member_ `uint8 MaxBoneInfluences = 0;`
- L136 _private prototype_ `uint32 FindAdjacentClusters( TArray< TMap< uint32, uint32 > >& OutAdjacency, TArrayView< const FClusterRef > LevelClusters, uint32 NumExternalEdges );`
- L137 _private prototype_ `void GroupTriangleClusters( TArrayView< const FClusterRef > LevelClusters, uint32 NumExternalEdges );`
- L138 _private prototype_ `void GroupVoxelClusters( TArrayView< const FClusterRef > LevelClusters );`
- L139 _private prototype_ `void GroupCurveClusters(TArrayView<const FClusterRef> LevelClusters);`
- L142 _public prototype_ `void ReduceGroup( std::atomic< int32 >& NumClusters, uint32 MaxClusterSize, uint32 NumParents, int32 GroupIndex, uint32 MeshIndex );`

#### struct `Nanite::FClusterDAG::FSettings`  
`struct FSettings`  
_L112-124_
- L114 _public member_ `uint32 NumRays = 1;`
- L115 _public member_ `int32 VoxelLevel = 0;`
- L116 _public member_ `uint32 ExtraVoxelLevels = 0;`
- L117 _public member_ `float RayBackUp = 0.0f;`
- L118 _public member_ `float MaxEdgeLengthFactor = 0.0f;`
- L119 _public member_ `ENaniteShapePreservation ShapePreservation = ENaniteShapePreservation::None;`
- L120 _public member_ `bool bLerpUVs : 1 = true;`
- L121 _public member_ `bool bSeparable : 1 = false;`
- L122 _public member_ `bool bVoxelNDF : 1 = true;`
- L123 _public member_ `bool bVoxelOpacity : 1 = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOG_CRC( Array )`
- L17 _namespace_ `namespace Nanite`
- L29 _prototype_ `FClusterCurveStats GetClusterCurveStats(const TArrayView<const FCurveIndex>& CurveIndexes);` (scope `Nanite`)
- L30 _prototype_ `FClusterCurveStats GetClusterCurveStats(const TArray<int32>& CurveIndices, const TArrayView<const FCurveIndex>& CurvePointRanges);` (scope `Nanite`)
- L31 _prototype_ `FClusterCurveStats GetClusterCurveStats(const TArrayView<const FCurveIndex>& InCurveIndexes, const TArrayView<const uint32>& SortedCurveIndexes, uint32 Begin, uint32 End);` (scope `Nanite`)
- L150 _function_ `FORCEINLINE FCluster& FClusterRef::GetCluster( FClusterDAG& DAG ) const` (scope `Nanite::FClusterRef`)
- L155 _function_ `FORCEINLINE const FCluster& FClusterRef::GetCluster( const FClusterDAG& DAG ) const` (scope `Nanite::FClusterRef`)
- L160 _function_ `FORCEINLINE const FMatrix44f& FClusterRef::GetTransform( const FClusterDAG& DAG ) const` (scope `Nanite::FClusterRef`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncode.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Nanite`
- L18 _prototype_ `void BuildRayTracingData(FResources& Resources, TArray<FCluster>& Clusters);` (scope `Nanite`)
- L20 _prototype_ `bool Encode( FResources& Resources, FClusterDAG& ClusterDAG, const FMeshNaniteSettings& Settings, uint32 NumMeshes, uint32* OutTotalGPUSize );` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeConstrain.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Nanite`
- L13 _prototype_ `void ConstrainClusters(TArray<FClusterGroup>& ClusterGroups, TArray<FCluster>& Clusters);` (scope `Nanite`)
- L14 _prototype_ `void VerifyClusterConstraints(const TArray<FCluster>& Clusters);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeFixup.h` (Private)


#### struct `Nanite::FPartFixup`  
`struct FPartFixup`  
_L20-30_
- L22 _public member_ `uint32 PageIndex = MAX_uint32;`
- L23 _public member_ `uint32 StartClusterIndex = MAX_uint32;`
- L24 _public member_ `uint32 LeafCounter = 0u;` — 0 means part has no leaf clusters
- L26 _public member_ `TArray<FHierarchyNodeRef> HierarchyLocations;` — Assembly parts can be referenced from many hierarchy nodes
- L29 _public member_ `uint32 GroupIndex = MAX_uint32;` — Builder only

#### struct `Nanite::FParentFixup`  
`struct FParentFixup`  
_L32-38_
- L34 _public member_ `uint32 PageIndex = MAX_uint32;`
- L35 _public member_ `uint32 PartFixupPageIndex = MAX_uint32;`
- L36 _public member_ `uint32 PartFixupIndex = MAX_uint32;`
- L37 _public member_ `TArray<uint8> ClusterIndices;` — Clusters to change leaf status of

#### struct `Nanite::FGroupFixup`  
`struct FGroupFixup`  
_L41-52_
- desc: Group fixups are always stored in the LAST page.
- L43 _public member_ `FPageRangeKey PageDependencyRangeKey;`
- L44 _public member_ `uint32 Flags = 0;`
- L45 _public member_ `uint32 FirstPartFixup = MAX_uint32;`
- L46 _public member_ `uint32 NumPartFixups = MAX_uint32;`
- L48 _public member_ `TArray<FParentFixup> ParentFixups;`
- L51 _public member_ `uint32 GroupIndex = MAX_uint32;` — Builder only

#### struct `Nanite::FPageFixups`  
`struct FPageFixups`  
_L54-59_
- L56 _public member_ `TArray<FGroupFixup> GroupFixups;`
- L57 _public member_ `TArray<FPartFixup> PartFixups;`
- L58 _public member_ `TArray<uint16> ReconsiderPages;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Nanite`
- L61 _prototype_ `void CalculatePageDependenciesAndFixups( FResources& Resources, TArray<FPageFixups>& PageFixups, const TArray<FPage>& Pages, const FClusterDAG& ClusterDAG, const TArray<FClusterGroupPart>& Parts);` (scope `Nanite`)
- L68 _prototype_ `void PerformPageInternalFixup( const FResources& Resources, const TArray<FPage>& Pages, const FClusterDAG& ClusterDAG, const TArray<FClusterGroupPart>& Parts, uint32 PageIndex, TArray<FPackedCluster>& PackedClusters);` (scope `Nanite`)
- L76 _prototype_ `void BuildFixupChunkData(TArray<uint8>& OutData, const FPageFixups& PageFixups, uint32 NumClusters);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeGeometryData.h` (Private)


#### struct `Nanite::FVariableVertex`  
`struct FVariableVertex`  
_L13-22_
- desc: Wasteful to store size for every vert but easier this way.
- L15 _public member_ `const float* Data;`
- L16 _public member_ `uint32 SizeInBytes;`
- L18 _public function_ `bool operator==( FVariableVertex Other ) const`

#### struct `Nanite::FVertexMapEntry`  
`struct FVertexMapEntry`  
_L29-33_
- L31 _public member_ `uint32 LocalClusterIndex;`
- L32 _public member_ `uint32 VertexIndex;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Nanite`
- L24 _function_ `FORCEINLINE uint32 GetTypeHash( FVariableVertex Vert )` (scope `Nanite`)
- L35 _prototype_ `void CalculateEncodingInfos( TArray<FEncodingInfo>& EncodingInfos, const TArray<FCluster>& Clusters, int32 NormalPrecision, int32 TangentPrecision, int32 BoneWeightPrecision );` (scope `Nanite`)
- L43 _prototype_ `void EncodeGeometryData( const uint32 LocalClusterIndex, const FCluster& Cluster, const FEncodingInfo& EncodingInfo, const TArrayView<uint16> PageDependencies, const TArray<TMap<FVariableVertex, FVertexMapEntry>>& PageVertexMaps, TMap<FVariableVertex, uint32>& UniqueVertices, uint32& NumCodedVertices, FPageStreams& Streams);` (scope `Nanite`)
- L52 _prototype_ `TArray<TMap<FVariableVertex, FVertexMapEntry>> BuildVertexMaps( const TArray<FPage>& Pages, const TArray<FCluster>& Clusters, const TArray<FClusterGroupPart>& Parts);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeHierarchy.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Nanite`
- L16 _prototype_ `void BuildHierarchies( FResources& Resources, const FClusterDAG& ClusterDAG, TArray<FPage>& Pages, TArray<FClusterGroupPart>& Parts, TArray<FEncodingInfo>& EncodingInfos, uint32 NumMeshes );` (scope `Nanite`)
- L25 _prototype_ `void CalculateFinalPageHierarchyDepth(const FResources& Resources, TArray<FPage>& Pages);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeMaterial.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Nanite`
- L12 _prototype_ `uint32 CalcMaterialTableSize(const FCluster& Cluster);` (scope `Nanite`)
- L13 _prototype_ `uint32 PackMaterialInfo(const FCluster& Cluster, TArray<uint32>& OutMaterialTable, uint32 MaterialTableStartOffset);` (scope `Nanite`)
- L15 _prototype_ `void BuildMaterialRanges(TArray<FCluster>& Clusters);` (scope `Nanite`)
- L17 _prototype_ `void PrintMaterialRangeStats(const TArray<FCluster>& Clusters);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodePageAssignment.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Nanite`
- L16 _prototype_ `bool AssignClustersToPages( FClusterDAG& ClusterDAG, TArray<FPageRangeKey>& PageRangeLookup, const TArray<FEncodingInfo>& EncodingInfos, TArray<FPage>& Pages, TArray<FClusterGroupPart>& Parts, const uint32 MaxRootPages);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeShared.h` (Private)


#### struct `Nanite::FPageSections`  
`struct FPageSections`  
_L14-86_
- L16 _public member_ `uint32 Cluster = 0;`
- L17 _public member_ `uint32 ClusterBoneInfluence = 0;`
- L18 _public member_ `uint32 VoxelBoneInfluence = 0;`
- L19 _public member_ `uint32 MaterialTable = 0;`
- L20 _public member_ `uint32 VertReuseBatchInfo = 0;`
- L21 _public member_ `uint32 BoneInfluence = 0;`
- L22 _public member_ `uint32 BrickData = 0;`
- L23 _public member_ `uint32 ExtendedData = 0;`
- L24 _public member_ `uint32 DecodeInfo = 0;`
- L25 _public member_ `uint32 Index = 0;`
- L26 _public member_ `uint32 Position = 0;`
- L27 _public member_ `uint32 Attribute = 0;`
- L29 _public function_ `uint32 GetClusterBoneInfluenceSize() const`
- L30 _public function_ `uint32 GetVoxelBoneInfluenceSize() const`
- L31 _public function_ `uint32 GetMaterialTableSize() const`
- L32 _public function_ `uint32 GetVertReuseBatchInfoSize() const`
- L33 _public function_ `uint32 GetBoneInfluenceSize() const`
- L34 _public function_ `uint32 GetBrickDataSize() const`
- L35 _public function_ `uint32 GetExtendedDataSize() const`
- L36 _public function_ `uint32 GetDecodeInfoSize() const`
- L38 _public function_ `uint32 GetClusterOffset() const`
- L39 _public function_ `uint32 GetClusterBoneInfluenceOffset() const`
- L40 _public function_ `uint32 GetVoxelBoneInfluenceOffset() const`
- L41 _public function_ `uint32 GetMaterialTableOffset() const`
- L42 _public function_ `uint32 GetVertReuseBatchInfoOffset() const`
- L43 _public function_ `uint32 GetBoneInfluenceOffset() const`
- L44 _public function_ `uint32 GetBrickDataOffset() const`
- L45 _public function_ `uint32 GetExtendedDataOffset() const`
- L46 _public function_ `uint32 GetDecodeInfoOffset() const`
- L47 _public function_ `uint32 GetIndexOffset() const`
- L48 _public function_ `uint32 GetPositionOffset() const`
- L49 _public function_ `uint32 GetAttributeOffset() const`
- L50 _public function_ `uint32 GetTotal() const`
- L52 _public function_ `FPageSections GetOffsets() const`
- L71 _public function_ `void operator+=(const FPageSections& Other)`

#### struct `Nanite::FPageStreams`  
`struct FPageStreams`  
_L88-104_
- L90 _public member_ `TArray<uint32> StripBitmask;`
- L91 _public member_ `TArray<uint32> PageClusterPair;`
- L92 _public member_ `TArray<uint32> VertexRefBitmask;`
- L93 _public member_ `TArray<uint16> VertexRef;`
- L94 _public member_ `TArray<uint8> Index;`
- L95 _public member_ `TArray<uint8> Attribute;`
- L96 _public member_ `TArray<uint8> BoneInfluence;`
- L97 _public member_ `TArray<uint8> Brick;`
- L98 _public member_ `TArray<uint32> Extended;`
- L99 _public member_ `TArray<uint32> MaterialRange;`
- L100 _public member_ `TArray<uint32> VertReuseBatchInfo;`
- L101 _public member_ `TArray<uint8> LowByte;`
- L102 _public member_ `TArray<uint8> MidByte;`
- L103 _public member_ `TArray<uint8> HighByte;`

#### struct `Nanite::FPage`  
`struct FPage`  
_L106-118_
- L108 _public member_ `uint32 PartsStartIndex = 0;`
- L109 _public member_ `uint32 PartsNum = 0;`
- L110 _public member_ `uint32 NumClusters = 0;`
- L111 _public member_ `uint32 MaxHierarchyPartDepth = 0;` — Max depth of referenced parts
- L112 _public member_ `uint32 MaxHierarchyDepth = 0;` — Depth to guarantee next level can also be reached
- L113 _public member_ `uint32 MaxClusterBoneInfluences = 0;`
- L114 _public member_ `uint32 MaxVoxelBoneInfluences = 0;`
- L115 _public member_ `bool bRelativeEncoding = false;`
- L117 _public member_ `FPageSections GpuSizes;`

#### struct `Nanite::FHierarchyNodeRef`  
`struct FHierarchyNodeRef`  
_L120-124_
- L122 _public member_ `uint32 NodeIndex = MAX_uint32;`
- L123 _public member_ `uint32 ChildIndex = MAX_uint32;`

#### struct `Nanite::FClusterGroupPart`  
`struct FClusterGroupPart`  
_L126-136_
- L128 _public member_ `TArray<uint32> Clusters;`
- L129 _public member_ `FBounds3f Bounds;`
- L130 _public member_ `float MinLODError = MAX_flt;`
- L131 _public member_ `uint32 PageIndex = MAX_uint32;`
- L132 _public member_ `uint32 GroupIndex = MAX_uint32;`
- L133 _public member_ `uint32 PageClusterOffset = MAX_uint32;`
- L135 _public member_ `TArray<FHierarchyNodeRef> HierarchyNodeRefs;`

#### struct `Nanite::FUVInfo`  
`struct FUVInfo`  
_L138-142_
- L140 _public member_ `FUintVector2 Min = FUintVector2::ZeroValue;`
- L141 _public member_ `FUintVector2 NumBits = FUintVector2::ZeroValue;`

#### struct `Nanite::FPackedUVHeader`  
`struct FPackedUVHeader`  
_L144-147_
- L146 _public member_ `FUintVector2 Data;`

#### struct `Nanite::FClusterBoneInfluence`  
`struct FClusterBoneInfluence`  
_L149-152_
- L151 _public member_ `uint32 BoneIndex;`

#### struct `Nanite::FPackedVoxelBoneInfluence`  
`struct FPackedVoxelBoneInfluence`  
_L154-157_
- L156 _public member_ `uint32 Weight_BoneIndex;` — Weight: 8, BoneIndex: 24

#### struct `Nanite::FBoneInfluenceInfo`  
`struct FBoneInfluenceInfo`  
_L159-170_
- L161 _public member_ `uint32 DataOffset = 0;`
- L162 _public member_ `uint32 NumVertexBoneInfluences = 0;`
- L163 _public member_ `uint32 NumVertexBoneIndexBits = 0;`
- L164 _public member_ `uint32 NumVertexBoneWeightBits = 0;`
- L166 _public member_ `TArray<uint32> BrickBoneIndices;`
- L168 _public member_ `TArray<FClusterBoneInfluence> ClusterBoneInfluences;`
- L169 _public member_ `TArray<FPackedVoxelBoneInfluence> VoxelBoneInfluences;`

#### struct `Nanite::FPackedBrick`  
`struct FPackedBrick`  
_L172-177_
- L174 _public member_ `uint32 VoxelMask[2];`
- L175 _public member_ `uint32 PositionAndBrickMax[2];` — MaxX: 2, MaxY: 2, MaxZ: 2, PosX: 19, PosY: 19, PosZ: 19
- L176 _public member_ `uint32 VertOffset_BoneIndex;`

#### struct `Nanite::FEncodingInfo`  
`struct FEncodingInfo`  
_L179-198_
- L181 _public member_ `uint32 BitsPerIndex = 0;`
- L182 _public member_ `uint32 BitsPerAttribute = 0;`
- L184 _public member_ `uint32 NormalPrecision = 0;`
- L185 _public member_ `uint32 TangentPrecision = 0;`
- L187 _public member_ `uint32 CurveRadiusBits = 0;`
- L188 _public member_ `float CurveRadiusScale = 0;`
- L190 _public member_ `uint32 ColorMode = 0;`
- L191 _public member_ `FIntVector4 ColorMin = FIntVector4(0, 0, 0, 0);`
- L192 _public member_ `FIntVector4 ColorBits = FIntVector4(0, 0, 0, 0);`
- L194 _public member_ `FUVInfo UVs[NANITE_MAX_UVS];`
- L195 _public member_ `FBoneInfluenceInfo BoneInfluence;`
- L197 _public member_ `FPageSections GpuSizes;`

#### class `Nanite::FBitWriter`  
`class FBitWriter`  
_L200-238_
- L203 _public function_ `FBitWriter(TArray<uint8>& Buffer) : Buffer(Buffer), PendingBits(0ull), NumPendingBits(0)`
- L210 _public function_ `void PutBits(uint32 Bits, uint32 NumBits)`
- L224 _public function_ `void Flush(uint32 Alignment=1)`
- L235 _private member_ `TArray<uint8>& Buffer;`
- L236 _private member_ `uint64 PendingBits;`
- L237 _private member_ `int32 NumPendingBits;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Nanite`
- L242 _function_ `template<typename TLambda> void ProcessPageClusters(const FPage& Page, const TArray<FClusterGroupPart>& Parts, TLambda&& Lambda)` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeSkinning.h` (Private)


#### struct `Nanite::FPackedBoneInfluenceHeader`  
`struct FPackedBoneInfluenceHeader`  
_L15-24_
- L17 _public member_ `uint32 DataOffset_VertexInfluences = 0u;` — DataOffset: 22, NumVertexInfluences: 10
- L18 _public member_ `uint32 NumVertexBoneIndexBits_NumVertexBoneWeightBits = 0u;` — NumVertexBoneIndexBits: 6, NumVertexBoneWeightBits: 5
- L20 _public function_ `void SetDataOffset(uint32 Offset)`
- L21 _public function_ `void SetNumVertexInfluences(uint32 Num)`
- L22 _public function_ `void SetNumVertexBoneIndexBits(uint32 NumBits)`
- L23 _public function_ `void SetNumVertexBoneWeightBits(uint32 NumBits)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Nanite`
- L26 _prototype_ `void QuantizeBoneWeights(TArray<FCluster>& Clusters, int32 BoneWeightPrecision);` (scope `Nanite`)
- L28 _prototype_ `void QuantizeAndSortBoneInfluenceWeights(TArrayView<FVector2f> BoneInfluences, uint32 TargetTotalQuatizedWeight);` (scope `Nanite`)
- L30 _prototype_ `void CalculateInfluences(FBoneInfluenceInfo& InfluenceInfo, const FCluster& Cluster, int32 BoneWeightPrecision);` (scope `Nanite`)
- L31 _prototype_ `void PackBoneInfluenceHeader(FPackedBoneInfluenceHeader& PackedBoneInfluenceHeader, const FBoneInfluenceInfo& BoneInfluenceInfo);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeTriStrip.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Nanite`
- L12 _prototype_ `void ConstrainAndStripifyCluster(FCluster& Cluster);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/Encode/NaniteEncodeVertReuseBatch.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Nanite`
- L13 _prototype_ `void BuildVertReuseBatches(TArray<FCluster>& Clusters);` (scope `Nanite`)
- L14 _prototype_ `uint32 CalcVertReuseBatchInfoSize(const TArrayView<const FMaterialRange>& MaterialRanges);` (scope `Nanite`)
- L15 _prototype_ `void PackVertReuseBatchInfo(const TArrayView<const FMaterialRange>& MaterialRanges, TArray<uint32>& OutVertReuseBatchInfo);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/GraphPartitioner.h` (Private)


#### class `FGraphPartitioner`  
`class FGraphPartitioner`  
_L12-57_
- L25 _public member_ `TArray< FRange > Ranges;`
- L26 _public member_ `TArray< uint32 > Indexes;`
- L27 _public member_ `TArray< uint32 > SortedTo;`
- L30 _public prototype_ `FGraphPartitioner( uint32 InNumElements, int32 InMinPartitionSize, int32 InMaxPartitionSize );`
- L32 _public prototype_ `FGraphData* NewGraph( uint32 NumAdjacency ) const;`
- L34 _public prototype_ `void AddAdjacency( FGraphData* Graph, uint32 AdjIndex, idx_t Cost );`
- L35 _public prototype_ `void AddLocalityLinks( FGraphData* Graph, uint32 Index, idx_t Cost );`
- L38 _public prototype_ `template< typename FGetCenter > void BuildLocalityLinks( FDisjointSet& DisjointSet, const FBounds3f& Bounds, TConstArrayView< const int32 > GroupIndexes, FGetCenter& GetCenter );`
- L40 _public prototype_ `void Partition( FGraphData* Graph );`
- L41 _public prototype_ `void PartitionStrict( FGraphData* Graph, bool bThreaded );`
- L44 _private prototype_ `void BisectGraph( FGraphData* Graph, FGraphData* ChildGraphs[2] );`
- L45 _private prototype_ `void RecursiveBisectGraph( FGraphData* Graph );`
- L47 _private member_ `uint32 NumElements;`
- L48 _private member_ `int32 MinPartitionSize;`
- L49 _private member_ `int32 MaxPartitionSize;`
- L51 _private member_ `TAtomic< uint32 > NumPartitions;`
- L53 _private member_ `TArray< idx_t > PartitionIDs;`
- L54 _private member_ `TArray< int32 > SwappedWith;`
- L56 _private member_ `TSparseMultiMap< uint32, uint32 > LocalityLinks;`
- L59 _function_ `FORCEINLINE void FGraphPartitioner::AddAdjacency( FGraphData* Graph, uint32 AdjIndex, idx_t Cost )`
- L65 _function_ `FORCEINLINE void FGraphPartitioner::AddLocalityLinks( FGraphData* Graph, uint32 Index, idx_t Cost )`
- L76 _function_ `template< typename FGetCenter > void FGraphPartitioner::BuildLocalityLinks( FDisjointSet& DisjointSet, const FBounds3f& Bounds, TConstArrayView< const int32 > GroupIndexes, FGetCenter& GetCenter )`

#### struct `FGraphPartitioner::FGraphData`  
`struct FGraphData`  
_L15-23_
- L17 _public member_ `int32 Offset;`
- L18 _public member_ `int32 Num;`
- L20 _public member_ `TArray< idx_t > Adjacency;`
- L21 _public member_ `TArray< idx_t > AdjacencyCost;`
- L22 _public member_ `TArray< idx_t > AdjacencyOffset;`

#### Free symbols / members of external scopes

- L86 _function_ `` (scope `FGraphPartitioner::BuildLocalityLinks`)

### `Source/Developer/NaniteBuilder/Private/NaniteAssemblyBuild.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Nanite`
- L13 _prototype_ `bool AddAssemblyParts(FIntermediateResources& AssemblyResources, const FInputAssemblyData& AssemblyData);` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Private/NaniteIntermediateResources.h` (Private)


#### struct `Nanite::FIntermediateResources`  
`struct FIntermediateResources`  
_L15-27_
- desc: Intermediate representation of the Nanite mesh data for building.
- L17 _public member_ `FClusterDAG ClusterDAG;`
- L19 _public member_ `TArray<FMeshDataSection> Sections;`
- L21 _public member_ `float SurfaceArea = 0.0f;` — Only used for computing relative error for fallback and trim.
- L23 _public member_ `uint32 NumInputTriangles = 0;` — Mesh-based input
- L24 _public member_ `uint32 NumInputCurves = 0;` — Curve-based input
- L25 _public member_ `uint32 NumInputVertices = 0;`
- L26 _public member_ `uint32 ResourceFlags = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Nanite`

### `Source/Developer/NaniteBuilder/Private/NaniteRayTracingScene.h` (Private)


#### struct `Nanite::FRay1`  
`struct FRay1 : public RTCRayHit`  
_L16-33_
- inherits: `RTCRayHit`
- L18 _public function_ `void SetRay( FVector3f Origin, FVector3f Direction, FVector2f Time )`

#### struct `Nanite::TRayN`  
`template< typename T > struct TRayN : public T`  
_L36-53_
- inherits: `T`
- L38 _public function_ `void SetRay( uint32 Index, FVector3f Origin, FVector3f Direction, FVector2f Time )`

#### class `Nanite::FRayTracingScene`  
`class FRayTracingScene`  
_L60-151_
- L63 _public member_ `RTCDevice Device = nullptr;`
- L64 _public member_ `RTCScene Scene = nullptr;`
- L66 _public member_ `TMap< uint32, FIntVector2 > InstanceMap;`
- L68 _public prototype_ `static uint32 AddCluster( RTCDevice Device, RTCScene Scene, const FCluster& Cluster );`
- L69 _public prototype_ `static uint32 AddInstance( RTCDevice Device, RTCScene Scene, RTCScene InstancedScene, const FMatrix44f& Transform );`
- L72 _public prototype_ `FRayTracingScene();`
- L73 _public prototype_ `~FRayTracingScene();`
- L75 _public prototype_ `void AddCluster( const FCluster& Cluster );`
- L76 _public prototype_ `void AddInstance( RTCScene InstancedScene, const FMatrix44f& Transform, uint32 InstanceIndex, uint32 ClusterOffset );`
- L78 _public function_ `void Intersect1( FRay1& Ray ) const`
- L89 _public function_ `void Intersect16( FRay16& Ray ) const`
- L103 _public function_ `bool GetHit( const FRay1& Ray, uint32& HitInstanceIndex, uint32& HitClusterIndex, uint32& HitTriIndex, FVector3f& HitBarycentrics ) const`
- L128 _public function_ `template< typename T > bool GetHit( const TRayN<T>& Ray, uint32 Index, uint32& HitInstanceIndex, uint32& HitClusterIndex, uint32& HitTriIndex, FVector3f& HitBarycentrics ) const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Nanite`
- L55 _typedef_ `using FRay4 = TRayN< RTCRayHit4 >;` (scope `Nanite`)
- L56 _typedef_ `using FRay8 = TRayN< RTCRayHit8 >;` (scope `Nanite`)
- L57 _typedef_ `using FRay16 = TRayN< RTCRayHit16 >;` (scope `Nanite`)

### `Source/Developer/NaniteBuilder/Public/NaniteBuilder.h` (Public)


#### struct `Nanite::FInputAssemblyData`  
`struct FInputAssemblyData`  
_L26-48_
- L34 _public function_ `bool IsValid() const`
- L36 _public member_ `TArray<FNaniteAssemblyNode> Nodes;`
- L37 _public member_ `TArray<FBuiltPartData> Parts;`
- L38 _public member_ `TArray<FMatrix44f> ComposedRefPose;` — Skinned assemblies only
- L47 _public member_ `TArray<uint16> SkeletonToUnifiedBoneIndex;` — Optional per-skeleton-bone remap from skeleton index to unified bone index. When the containing skeletal mesh uses unified bone maps (bOptimizeForInstancing), assembly bone influences must be remapped from skeleton space into unified space at DAG build time so downstream consumers (vertex bone buffers, fallback decode) see consistent indices. Empty when unified bone maps are not in use, in which case bone indices stay in skeleton space. Indexed by skeleton bone index; value is the unified bone index, or INDEX_NONE (0xFFFF) for skeleton bones that aren't in the unified map.

#### struct `Nanite::FInputAssemblyData::FBuiltPartData`  
`struct FBuiltPartData`  
_L28-32_
- L30 _public member_ `FAssemblyPartResourceRef Resource;`
- L31 _public member_ `FMaterialRemapTable MaterialRemap;`

#### struct `Nanite::FRayTracingFallbackBuildSettings`  
`struct FRayTracingFallbackBuildSettings`  
_L50-62_
- L52 _public member_ `float FallbackPercentTriangles = 1.0f;`
- L53 _public member_ `float FallbackRelativeError = 2.0f;`
- L54 _public member_ `float FoliageOverOcclusionBias = 0.0f;`
- L56 _public function_ `bool IsFallbackReduced() const`

#### class `Nanite::IBuilderModule`  
`class IBuilderModule : public IModuleInterface`  
_L64-141_
- inherits: `IModuleInterface`
- L73 _public function_ `static inline IBuilderModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L83 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L88 _public prototype_ `virtual const FString& GetVersionString() const = 0;`
- L115 _public function_ `virtual FAssemblyPartResourceRef BuildAssemblyPart( FInputMeshData& InputMeshData, const FMeshNaniteSettings& Settings)`
- L122 _public function_ `virtual bool Build( FResources& Resources, FInputMeshData& InputMeshData, FOutputMeshData* OutFallbackMeshData, FOutputMeshData* OutRayTracingFallbackMeshData, const FRayTracingFallbackBuildSettings* RayTracingFallbackBuildSettings, const FMeshNaniteSettings& Settings, FInputAssemblyData* AssemblyData = nullptr)`
- L134 _public function_ `virtual bool BuildMaterialIndices( const FMeshDataSectionArray& SectionArray, const uint32 TriangleCount, TArray<int32>& OutMaterialIndices)`

#### struct `Nanite::IBuilderModule::FInputMeshData`  
`struct FInputMeshData`  
_L90-106_
- L92 _public member_ `FMeshBuildVertexData Vertices;`
- L93 _public member_ `TArray<uint32> TriangleIndices;`
- L94 _public member_ `TArray<uint32> TriangleCounts;`
- L95 _public member_ `TArray<int32> MaterialIndices;`
- L96 _public member_ `FMeshDataSectionArray Sections;`
- L97 _public member_ `FBounds3f VertexBounds;`
- L98 _public member_ `uint8 NumTexCoords = 0;`
- L99 _public member_ `uint8 NumBoneInfluences = 0;`
- L100 _public member_ `float PercentTriangles = 1.0f;`
- L101 _public member_ `float MaxDeviation = 0.0f;`
- L104 _public member_ `TArray<uint32> CurveCounts;` — Curve
- L105 _public member_ `TArray<FCurveIndex> CurveIndices;` — Offset/Count: Curve's vertices are stored contiguously

#### struct `Nanite::IBuilderModule::FOutputMeshData`  
`struct FOutputMeshData`  
_L108-113_
- L110 _public member_ `FMeshBuildVertexData Vertices;`
- L111 _public member_ `TArray<uint32> TriangleIndices;`
- L112 _public member_ `FMeshDataSectionArray Sections;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Nanite`
- L19 _variable_ `const int32 MaxSectionArraySize = 64;` (scope `Nanite`)
- L23 _typedef_ `using FAssemblyPartResourceRef = TSharedPtr<FIntermediateResources, ESPMode::NotThreadSafe>;` (scope `Nanite`)
- L24 _typedef_ `using FMaterialRemapTable = TStaticArray<uint32, MaxSectionArraySize>;` (scope `Nanite`)
