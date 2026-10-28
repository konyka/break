# Developer / NaniteUtilities

- module root: `Source/Developer/NaniteUtilities`
- headers: 13; symbols: 406
- symbol kinds: class=5, enum=1, enumerator=3, function=230, macro=2, member=99, namespace=12, prototype=28, struct=8, typedef=15, union=1, variable=2
- PrivateDependencyModuleNames: DesktopWidgets, GeometryCore, ImageCore
- PublicDependencyModuleNames: Core, Engine

### `Source/Developer/NaniteUtilities/Public/AdaptiveTessellator.h` (Public)


#### class `Nanite::AdaptiveTessellation::FAdaptiveTessellator`  
`FAdaptiveTessellator`  
_L51-105_
- reflection: `UE_DEPRECATED(5.8, "Nanite::FAdaptiveTessellator has moved to UE::GeometryCore::FAdaptiveTessellator")`
- L55 _public prototype_ `FAdaptiveTessellator( TArray< FLerpVert >& InVerts, TArray< uint32 >& InIndexes, TArray< int32 >& InMaterialIndexes, float InTargetError, float InSampleRate, bool bCrackFree, FDispFunc InGetDisplacement, FBoundsFunc InGetErrorBounds, FNumFunc InGetNumSamples, bool bApplyDisplacement = true );`
- L69 _protected member_ `FDispFunc GetDisplacement;`
- L70 _protected member_ `FBoundsFunc GetErrorBounds;`
- L71 _protected member_ `FNumFunc GetNumSamples;`
- L73 _protected member_ `float TargetError;`
- L74 _protected member_ `float SampleRate;`
- L76 _protected member_ `TArray< FLerpVert >& Verts;`
- L77 _protected member_ `TArray< uint32 >& Indexes;`
- L78 _protected member_ `TArray< int32 >& MaterialIndexes;`
- L80 _protected member_ `TArray< FVector3f > Displacements;`
- L81 _protected member_ `TArray< int32 > AdjEdges;`
- L88 _protected member_ `TArray< FTriangle > Triangles;`
- L90 _protected member_ `TArray< uint32 > FindRequests;`
- L91 _protected member_ `TArray< uint32 > SplitRequests;`
- L92 _protected member_ `std::atomic< uint32 > NumSplits;`
- L94 _protected prototype_ `void AddFindRequest( uint32 TriIndex );`
- L95 _protected prototype_ `void RemoveSplitRequest( uint32 TriIndex );`
- L96 _protected prototype_ `void LinkEdge( int32 EdgeIndex0, int32 EdgeIndex1 );`
- L98 _protected prototype_ `FVector3f GetTriNormal( uint32 TriIndex ) const;`
- L99 _protected prototype_ `bool CouldFlipEdge( uint32 EdgeIndex ) const;`
- L100 _protected prototype_ `void TryDelaunayFlip( uint32 EdgeIndex );`
- L102 _protected prototype_ `void FindSplit( uint32 TriIndex );`
- L103 _protected prototype_ `void FindSplitBVH( uint32 TriIndex );`
- L104 _protected prototype_ `void SplitTriangle( uint32 TriIndex );`

#### struct `Nanite::AdaptiveTessellation::FAdaptiveTessellator::FTriangle`  
`struct FTriangle`  
_L83-87_
- L85 _public member_ `FVector3f SplitBarycentrics;`
- L86 _public member_ `int32 RequestIndex = -1;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Nanite`
- L21 _namespace_ `namespace AdaptiveTessellation` (scope `Nanite`)
- L23 _typedef_ `using FDispFunc = TFunctionRef< FVector3f( const FVector3f&,` (scope `Nanite::AdaptiveTessellation`)
- L31 _typedef_ `using FBoundsFunc = TFunctionRef< FVector2f( const FVector3f[3],` (scope `Nanite::AdaptiveTessellation`)
- L42 _typedef_ `using FNumFunc = TFunctionRef< int32( const FVector3f[3],` (scope `Nanite::AdaptiveTessellation`)
- L120 _prototype_ `void TessellateAdaptive( TArray< FLerpVert >& Verts, TArray< uint32 >& Indexes, TArray< int32 >& MaterialIndexes, float TargetError, float SampleRate, bool bCrackFree, FDispFunc GetDisplacement, FBoundsFunc GetErrorBounds, FNumFunc GetNumSamples, bool bApplyDisplacement = true, int32 InMode = -1);` (scope `Nanite::AdaptiveTessellation`) — Apply adaptive displacement to the input mesh. @param Verts vertices @param Indexes triangles, expressed as vertex indices grouped as triplets @param MaterialIndexes material ids per triangle @param TargetError refine until TargetError^2 is reached in GetErrorBounds callback. @param SampleRate  feature size (one-dimensional) up to which features are sampled in the displacement function @param bCrackFree if enabled, vertices that previously coincided remain at the same position even if disconnected @param GetDisplacement callback to evaluate the displacement @param GetErrorBounds callback to query an error interval at a subtriangle @param GetNumSamples callback to query the number of samples for a subtriangle

### `Source/Developer/NaniteUtilities/Public/AdaptiveTessellatorDisplace.h` (Public)


#### class `Nanite::DisplacementPolicyFunctor`  
`class DisplacementPolicyFunctor`  
_L95-178_
- desc: same as above but use function references as original nanite code
- L98 _public typedef_ `using FIndex3i = UE::Geometry::FIndex3i;`
- L100 _public typedef_ `using FDispFunc = TFunctionRef< FVector3f ( const FVector3f&,`
- L108 _public typedef_ `using FVectorDispFunc = TFunctionRef < FVector3f( const FVector3f&,`
- L114 _public typedef_ `using FBoundsFunc = TFunctionRef< FVector2f ( const FVector3f[3],`
- L125 _public typedef_ `using FNumFunc = TFunctionRef< int32 ( const FVector3f[3],`
- L133 _public function_ `DisplacementPolicyFunctor(FMinimalMesh& InMesh, FDispFunc InGetDisplacement, FVectorDispFunc InGetVectorDisplacement, FBoundsFunc InGetErrorBounds, FNumFunc InGetNumSamples) : Mesh(InMesh) , GetDisplacementFunc(InGetDisplacement) , GetVectorDisplacementFunc(InGetVectorDisplacement) , GetErrorBoundsFunc(InGetErrorBounds) , GetNumSamplesFunc(InGetNumSamples)`
- L146 _public function_ `FVector3f GetVertexDisplacement(const int32 VertexIndex, const int32 TriIndex) const`
- L151 _public function_ `FVector3f GetDisplacement(const FVector3f Barycentrics, const int TriIndex) const`
- L157 _public function_ `FVector2f GetErrorBounds(const FVector3f* const Barycentrics, const FVector3f Displacement0, const FVector3f Displacement1, const FVector3f Displacement2, const int TriIndex )`
- L167 _public function_ `int32 GetNumSamples(const FVector3f* const Barycentrics, const FIndex3i& Triangle, const int TriIndex) const`
- L173 _private member_ `const FMinimalMesh& Mesh;`
- L174 _private member_ `FDispFunc GetDisplacementFunc;`
- L175 _private member_ `FVectorDispFunc GetVectorDisplacementFunc;`
- L176 _private member_ `FBoundsFunc GetErrorBoundsFunc;`
- L177 _private member_ `FNumFunc GetNumSamplesFunc;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Nanite`
- L15 _function_ `inline void InterpolateNormalsAndUVs( const FVector3f& Barycentrics, const FLerpVert& Vert0, const FLerpVert& Vert1, const FLerpVert& Vert2, FVector2f& OutUV, FVector3f& OutNormal)` (scope `Nanite`)
- L33 _function_ `inline FVector2f GetErrorBounds( const FVector3f Barycentrics[3], const FVector3f VertexNormals[3], const FVector2f VertexUVs[3], const FVector3f Displacements[3], const UE::Geometry::FDisplacementMap& DisplacementMap)` (scope `Nanite`)
- L46 _function_ `inline FVector2f GetErrorBounds( const FVector3f Barycentrics[3], const FLerpVert& Vert0, const FLerpVert& Vert1, const FLerpVert& Vert2, const FVector3f& Displacement0, const FVector3f& Displacement1, const FVector3f& Displacement2, const UE::Geometry::FDisplacementMap& DisplacementMap)` (scope `Nanite`)
- L64 _function_ `template <typename T> inline int32 GetNumSamples( const UE::Math::TVector<T> Barycentrics[3], const FVector2f VertexUVs[3], const FVector2f MapRes)` (scope `Nanite`)

### `Source/Developer/NaniteUtilities/Public/AdaptiveTessellatorMesh.h` (Public)


#### class `Nanite::FMinimalMesh`  
`class FMinimalMesh`  
_L20-351_
- desc: Mesh topology implementation for UE::Geometry::FAdaptiveTesselation. TriEdgeIndex is always in [0..2] and corresponds to enumerating triangle edges and vertices in order The edge connects the vertices Tri[TriEdgeIndex], Tri[(TriEdgeIndex+1)%3].
- L23 _public typedef_ `using FIndex3i = UE::Geometry::FIndex3i;`
- L25 _public typedef_ `using RealType = float;`
- L26 _public typedef_ `using VecType = FVector3f;`
- L35 _public function_ `FMinimalMesh( TArray<FLerpVert>& InVerts,`
- L112 _public function_ `FORCEINLINE int32 GetVertexIndex(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L120 _public function_ `FORCEINLINE FIndex3i GetTriangle(const int32 TriIndex) const`
- L132 _public function_ `FORCEINLINE FVector3f GetVertexPosition(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L137 _public function_ `FORCEINLINE FVector3f GetVertexPosition(const int32 VertexIndex) const`
- L142 _public function_ `FORCEINLINE void SetVertexPosition(const int32 VertexIndex, const FVector3f Position) const`
- L147 _public function_ `FORCEINLINE void GetTriVertices(const int32 TriIndex, FVector3f& v0, FVector3f& v1, FVector3f& v2) const`
- L154 _public function_ `FORCEINLINE int32 MaxVertexID() const`
- L159 _public function_ `FORCEINLINE bool IsValidVertex(const int32 VertexID) const`
- L164 _public function_ `FORCEINLINE int32 MaxTriID() const`
- L169 _public function_ `FORCEINLINE bool IsValidTri(const int32 TriIndex) const`
- L175 _public function_ `FORCEINLINE int32 GetAdjTriangle(const int32 TriIndex, const int32 TriEdgeIndex) const` — Return the triangle index on the other side of the half edge given by TriIndex, TriEdgeIndex or IndexConstants::InvalidID on boundary
- L186 _public function_ `FORCEINLINE TPair<int32,int32> GetAdjEdge(const int32 TriIndex, const int32 TriEdgeIndex) const` — Return the triangle index on the other side of the half edge given by TriIndex, TriEdgeIndex or IndexConstants::InvalidID on boundary
- L196 _public function_ `FORCEINLINE bool EdgeManifoldCheck(const int32 TriIndex, const int32 TriEdgeIndex) const`
- L214 _public function_ `FORCEINLINE bool AllowEdgeFlip(const int32 TriIndex, const int32 TriEdgeIndex, const int32 AdjTriIndex ) const`
- L219 _public function_ `FORCEINLINE bool AllowEdgeSplit(const int32 TriIndex, const int32 TriEdgeIndex ) const`
- L224 _public function_ `FORCEINLINE FVector3f GetTriangleNormal(const int32 TriIndex) const`
- L238 _public prototype_ `UE::Geometry::FEdgeSplitInfo SplitEdge(const int32 TriIndex, const int32 TriEdgeIndex, const float SplitWeight);` — Split given triangle edge. The new position is SplitWeight * V0 + (1-SplitWeight) * V1.
- L241 _public prototype_ `UE::Geometry::FPokeInfo PokeTriangle(const int32 TriIndex, const FVector3f Barycentrics);` — Introduce new vertex in triangle, connect to all three vertices and split into three new triangles.
- L243 _public prototype_ `UE::Geometry::FFlipEdgeInfo FlipEdge(const int32 TriIndex, const int32 TriEdgeIndex);`
- L245 _public function_ `bool IsTriangleSoup() const`
- L254 _public function_ `const FLerpVert& GetLerpVert(const int32 Idx) const`
- L259 _public function_ `int32 GetMaterialIndex(const int32 TriIndex) const`
- L266 _private function_ `inline int32 AddInterpolatedVertex(const FVector3f Barycentrics, const int32 TriIndex)` — Added interpolation of corner vertices of triangle according to barycentric coordinates and return new vertex index.
- L288 _private function_ `inline int32 AddInterpolatedVertex(const FVector2f Barycentrics, int32 VertexIndex0, int32 VertexIndex1)` — Added interpolation of corner vertices of edge according to barycentric coordinates and return new vertex index.
- L304 _private function_ `FORCEINLINE int32 HalfEdgeCount() const`
- L309 _private function_ `void LinkEdge( int32 EdgeIndex0, int32 EdgeIndex1 )`
- L321 _private function_ `bool HasIdenticalUVs( uint32 VID0, uint32 VID1 )`
- L344 _private member_ `TArray<FLerpVert>& Verts;` — per-vertex
- L345 _private member_ `TArray<uint32>& Indexes;` — triangle as triplets
- L346 _private member_ `TArray<int32>& MaterialIndexes;` — per triangle material index
- L348 _private member_ `TArray<int32> AdjEdges;` — half-edge to neighboring half-edge (or -1 on boundary)
- L349 _private member_ `const EEdgeSplitMode EdgeSplitMode;` — how to we handle edge splits
- L350 _private member_ `const bool bTriangleSoup;` — if true, don't assume the vertex indices provide mesh connectivity
- L354 _function_ `inline UE::Geometry::FEdgeSplitInfo FMinimalMesh::SplitEdge(const int32 TriIndex, const int32 TriEdgeIndex, const float SplitWeight)`
- L472 _function_ `inline UE::Geometry::FPokeInfo FMinimalMesh::PokeTriangle(const int32 TriIndex, const FVector3f Barycentrics)`
- L531 _function_ `inline UE::Geometry::FFlipEdgeInfo FMinimalMesh::FlipEdge(const int32 TriIndex, const int32 TriEdgeIndex)`

#### enum `Nanite::FMinimalMesh::EEdgeSplitMode`  
`enum class EEdgeSplitMode`  
_L28-33_
- L30 _public enumerator_ `AlwaysCrack` — when splitting edges, always duplicate vertex
- L31 _public enumerator_ `PreserveSeams` — only split vertex if there is a material or UV seam
- L32 _public enumerator_ `CrackFree` — never split, always average

#### struct `Nanite::FMinimalMesh::FMinimalMesh::FSortEdge`  
`struct FSortEdge`  
_L52-61_
- L54 _public member_ `size_t EdgeIndex;`
- L55 _public member_ `int32 VtxA, VtxB;`
- L55 _public member_ `int32 VtxA, VtxB;`
- L57 _public function_ `FORCEINLINE bool operator<(const FSortEdge& other) const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Nanite`
- L92 _function_ `` (scope `Nanite::FMinimalMesh::FMinimalMesh`)

### `Source/Developer/NaniteUtilities/Public/LerpVert.h` (Public)


#### struct `FLerpVert`  
`struct FLerpVert`  
_L9-86_
- desc: Lerpable version of FStaticMeshBuildVertex
- L11 _public member_ `FVector3f Position;`
- L13 _public member_ `FVector3f TangentX;`
- L14 _public member_ `FVector3f TangentY;`
- L15 _public member_ `FVector3f TangentZ;`
- L17 _public member_ `FLinearColor Color;`
- L18 _public member_ `FVector2f UVs[MAX_STATIC_TEXCOORDS];`
- L20 _public function_ `FLerpVert()`
- L28 _public function_ `FLerpVert( FStaticMeshBuildVertex In ) : Position( In.Position ) , TangentX( In.TangentX ) , TangentY( In.TangentY ) , TangentZ( In.TangentZ )`
- L40 _public function_ `operator FStaticMeshBuildVertex() const`
- L55 _public function_ `FLerpVert& operator+=( const FLerpVert& Other )`
- L69 _public function_ `FLerpVert operator*( const float a ) const`

#### Free symbols / members of external scopes

- L88 _function_ `inline FArchive& operator<<(FArchive& Ar, FLerpVert& LerpVert)`

### `Source/Developer/NaniteUtilities/Public/MatrixUtil.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `template< typename T > bool LUPFactorize( T* RESTRICT A, uint32* RESTRICT Pivot, uint32 Size, T Epsilon )` — LUP factorization using Doolittle's method with partial pivoting
- L62 _function_ `template< typename T > void LUPSolve( const T* RESTRICT LU, const uint32* RESTRICT Pivot, uint32 Size, const T* RESTRICT b, T* RESTRICT x )` — Solve system of equations A*x = b
- L84 _function_ `template< typename T > bool LUPSolveIterate( const T* RESTRICT A, const T* RESTRICT LU, const uint32* RESTRICT Pivot, uint32 Size, const T* RESTRICT b, T* RESTRICT x )` — Newton's method iterative refinement.
- L124 _namespace_ `namespace JacobiSVD`
- L164 _function_ `template< typename T > inline void Update( T* RESTRICT A, T s, T tau, uint32 d1, uint32 d2 )` (scope `JacobiSVD`)
- L173 _function_ `template< typename T > bool Rotation3( T* RESTRICT A, T* RESTRICT V, T* RESTRICT Z, const T tol, int j, int k, int L )` (scope `JacobiSVD`)
- L227 _function_ `template< typename T > bool Rotation4( T* RESTRICT A, T* RESTRICT V, T* RESTRICT Z, const T tol, int j, int k, int L1, int L2 )` (scope `JacobiSVD`)
- L283 _function_ `template< typename T > inline T MaxOffDiagSymm( T* RESTRICT A, uint32 Size )` (scope `JacobiSVD`)
- L296 _function_ `template< typename T > void EigenSolver3( T* RESTRICT A, T* RESTRICT S, T* RESTRICT V, const T tol )` (scope `JacobiSVD`) — Diagonalize matrix A = V S V^T
- L344 _function_ `template< typename T > void EigenSolver4( T* RESTRICT A, T* RESTRICT S, T* RESTRICT V, const T tol )` (scope `JacobiSVD`) — Diagonalize matrix A = V S V^T
- L389 _function_ `template< typename T > void PseudoInverse( T* RESTRICT S, uint32 Size, T Tolerance )` — Moore-Penrose pseudo inverse
- L405 _function_ `template< typename T > void PseudoSolve( const T* RESTRICT V, const T* RESTRICT S, uint32 Size, const T* RESTRICT b, T* RESTRICT x )`
- L425 _function_ `template< typename T > bool PseudoSolveIterate( const T* RESTRICT A, const T* RESTRICT V, const T* RESTRICT S, uint32 Size, const T* RESTRICT b, T* RESTRICT x )` — Newton's method iterative refinement.

### `Source/Developer/NaniteUtilities/Public/MonteCarlo.h` (Public)


#### Free symbols / members of external scopes

- L8 _function_ `FORCEINLINE FVector2f UniformSampleDisk( FVector2f E )`
- L18 _function_ `FORCEINLINE FVector3f UniformSampleSphere( FVector2f E )`
- L34 _function_ `FORCEINLINE FVector2f GaussianSampleDisk( FVector2f E, float Sigma, float Window )` — exp( -0.5 * x^2 / Sigma^2 )
- L53 _function_ `FORCEINLINE uint32 EvolveSobolSeed( uint32& Seed )` — All Sobol code adapted from PathTracingRandomSequence.ush
- L67 _function_ `FORCEINLINE FVector4f LatticeSampler( uint32 SampleIndex, uint32& Seed )`
- L83 _function_ `FORCEINLINE uint32 FastOwenScrambling( uint32 Index, uint32 Seed )`
- L92 _function_ `FORCEINLINE FVector2f SobolSampler( uint32 SampleIndex, uint32& Seed )`

### `Source/Developer/NaniteUtilities/Public/NaniteLayout.h` (Public)


#### class `Nanite::FSettingsLayout`  
`template<typename TMeshType, bool bSupportsForceEnable, bool bSupportsHighRes> class FSettingsLayout : public TSharedFromThis<FSettingsLayout<TMeshType, bSupportsForceEnable, bSupportsHighRes>>`  
_L84-1303_
- inherits: `TSharedFromThis<FSettingsLayout<TMeshType,bSupportsForceEnable,bSupportsHighRes>>`
- L87 _public typedef_ `typedef TMeshType MeshType;`
- L90 _public function_ `FSettingsLayout()`
- L135 _public prototype_ `~FSettingsLayout() = default;`
- L138 _public member_ `static const int32 DisplayPositionPrecisionAuto = MIN_int32;` — Position Precision range selectable in the UI.
- L139 _public member_ `static const int32 DisplayPositionPrecisionMin = -6;`
- L140 _public member_ `static const int32 DisplayPositionPrecisionMax = 13;`
- L142 _public function_ `static int32 PositionPrecisionIndexToValue(int32 Index)`
- L158 _public function_ `static int32 PositionPrecisionValueToIndex(int32 Value)`
- L172 _public function_ `static FString PositionPrecisionValueToDisplayString(int32 Value)` — Display string to show in menus.
- L188 _public member_ `static const int32 DisplayNormalPrecisionAuto = -1;` — Normal Precision range selectable in the UI.
- L189 _public member_ `static const int32 DisplayNormalPrecisionMin = 5;`
- L190 _public member_ `static const int32 DisplayNormalPrecisionMax = 15;`
- L192 _public function_ `static int32 NormalPrecisionIndexToValue(int32 Index)`
- L208 _public function_ `static int32 NormalPrecisionValueToIndex(int32 Value)`
- L222 _public function_ `static FString NormalPrecisionValueToDisplayString(int32 Value)` — Display string to show in menus.
- L229 _public member_ `static const int32 DisplayTangentPrecisionAuto = -1;` — Tangent Precision range selectable in the UI.
- L230 _public member_ `static const int32 DisplayTangentPrecisionMin = 4;`
- L231 _public member_ `static const int32 DisplayTangentPrecisionMax = 12;`
- L233 _public function_ `static int32 TangentPrecisionIndexToValue(int32 Index)`
- L249 _public function_ `static int32 TangentPrecisionValueToIndex(int32 Value)`
- L263 _public function_ `static FString TangentPrecisionValueToDisplayString(int32 Value)` — Display string to show in menus.
- L270 _public member_ `static const int32 DisplayBoneWeightPrecisionAuto = -1;` — Bone Weight Precision range selectable in the UI.
- L271 _public member_ `static const int32 DisplayBoneWeightPrecisionRigid = 0;`
- L272 _public member_ `static const int32 DisplayBoneWeightPrecisionMin = 4;`
- L273 _public member_ `static const int32 DisplayBoneWeightPrecisionMax = 16;`
- L275 _public function_ `static int32 BoneWeightPrecisionIndexToValue(int32 Index)`
- L295 _public function_ `static int32 BoneWeightPrecisionValueToIndex(int32 Value)`
- L313 _public function_ `static FString BoneWeightPrecisionValueToDisplayString(int32 Value)` — Display string to show in menus.
- L322 _public member_ `static const int32 DisplayMinimumResidencyMinimalIndex = 0;` — Residency range selectable in the UI.
- L323 _public member_ `static const int32 DisplayMinimumResidencyExpRangeMin = 5;`
- L324 _public member_ `static const int32 DisplayMinimumResidencyExpRangeMax = 15;`
- L325 _public member_ `static const int32 DisplayMinimumResidencyFullIndex = DisplayMinimumResidencyExpRangeMax - DisplayMinimumResidencyExpRangeMin + 2;`
- L327 _public function_ `static uint32 MinimumResidencyIndexToValue(int32 Index)`
- L343 _public function_ `static int32 MinimumResidencyValueToIndex(uint32 Value)`
- L361 _public function_ `static FString MinimumResidencyValueToDisplayString(uint32 Value)` — Display string to show in menus.
- L373 _public function_ `const FMeshNaniteSettings& GetSettings() const`
- L378 _public function_ `void UpdateSettings(const FMeshNaniteSettings& InSettings)`
- L384 _public function_ `bool IsApplyNeeded() const` — Returns true if settings have been changed and an Apply is needed to update the asset.
- L392 _public function_ `void ApplyChanges()` — Apply current Nanite settings to the mesh.
- L413 _protected function_ `FReply OnApply()`
- L419 _protected function_ `ECheckBoxState IsEnabledChecked() const`
- L430 _protected function_ `void OnEnabledChanged(ECheckBoxState NewState)`
- L435 _protected function_ `void OnPositionPrecisionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)`
- L448 _protected function_ `void OnNormalPrecisionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)`
- L461 _protected function_ `void OnTangentPrecisionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)`
- L474 _protected function_ `void OnBoneWeightPrecisionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)`
- L487 _protected function_ `void OnResidencyChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)`
- L500 _protected function_ `FReply OnOpenProjectSettings()`
- L506 _protected function_ `float GetKeepPercentTriangles() const`
- L511 _protected function_ `void OnKeepPercentTrianglesChanged(float NewValue)`
- L517 _protected function_ `void OnKeepPercentTrianglesCommitted(float NewValue, ETextCommit::Type TextCommitType)`
- L526 _protected function_ `float GetTrimRelativeError() const`
- L531 _protected function_ `void OnTrimRelativeErrorChanged(float NewValue)`
- L536 _protected function_ `float GetFallbackPercentTriangles() const`
- L541 _protected function_ `void OnFallbackPercentTrianglesChanged(float NewValue)`
- L547 _protected function_ `void OnFallbackPercentTrianglesCommitted(float NewValue, ETextCommit::Type TextCommitType)`
- L556 _protected function_ `float GetFallbackRelativeError() const`
- L561 _protected function_ `void OnFallbackRelativeErrorChanged(float NewValue)`
- L566 _protected function_ `int32 GetDisplacementUVChannel() const`
- L571 _protected function_ `void OnDisplacementUVChannelChanged(int32 NewValue)`
- L576 _protected function_ `FString GetHiResSourceFilename() const`
- L589 _protected function_ `void SetHiResSourceFilename(const FString& NewSourceFile)`
- L614 _protected function_ `bool DoesHiResDataExists() const`
- L628 _protected function_ `bool IsHiResDataEmpty() const`
- L633 _protected function_ `FReply OnImportHiRes()`
- L652 _protected function_ `FReply OnRemoveHiRes()`
- L667 _protected function_ `FReply OnReimportHiRes()`
- L681 _protected function_ `FReply OnReimportHiResWithNewFile()`
- L696 _protected function_ `bool IsSkeletalMesh() const`
- L702 _public function_ `void AddToDetailsPanel( TWeakObjectPtr<TMeshType> WeakMeshPtr, IDetailLayoutBuilder& DetailBuilder, int32 SortOrder, bool bInitiallyCollapsed )`
- L1274 _public function_ `inline MeshType* GetMesh() const`
- L1284 _public function_ `inline void RefreshTool()`
- L1292 _public member_ `TDelegate<MeshType* ()> OnGetMesh;`
- L1293 _public member_ `TDelegate<void()> OnRefreshTool;`
- L1296 _protected member_ `TArray<TSharedPtr<FString>> PositionPrecisionOptions;`
- L1297 _protected member_ `TArray<TSharedPtr<FString>> NormalPrecisionOptions;`
- L1298 _protected member_ `TArray<TSharedPtr<FString>> TangentPrecisionOptions;`
- L1299 _protected member_ `TArray<TSharedPtr<FString>> BoneWeightPrecisionOptions;`
- L1300 _protected member_ `TArray<TSharedPtr<FString>> ResidencyOptions;`
- L1302 _protected member_ `FMeshNaniteSettings NaniteSettings;`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace Nanite`
- L41 _macro_ `#define LOCTEXT_NAMESPACE "NaniteLayout"`
- L44 _function_ `template< typename StructType, typename CopyFuncType > IDetailPropertyRow& AddDefaultRow( IDetailCategoryBuilder& CategoryBuilder, StructType& Struct, FName PropertyName, CopyFuncType CopyFunc )` (scope `Nanite`)
- L51 _function_ `` (scope `Nanite::AddDefaultRow`)
- L67 _function_ `template< typename StructType, typename MemberType > IDetailPropertyRow& AddDefaultRow( IDetailCategoryBuilder& CategoryBuilder, StructType& Struct, MemberType (StructType::*MemberPointer), FName PropertyName )` (scope `Nanite`)
- L76 _macro_ `#define NANITE_ADD_DEFAULT_ROW(PropertyName) \`
- L709 _typedef_ `typedef FSettingsLayout<TMeshType, bSupportsForceEnable, bSupportsHighRes> TSettingsType;` (scope `Nanite::FSettingsLayout::AddToDetailsPanel`)
- L718 _function_ `` (scope `Nanite::FSettingsLayout::AddToDetailsPanel`)
- L786 _function_ `TAttribute<bool> NaniteEnabledAttr = TAttribute<bool>::Create(TAttribute<bool>::FGetter::CreateLambda([NaniteEnabledCheck]() -> bool { return NaniteEnabledCheck->IsChecked(); }));` (scope `Nanite::FSettingsLayout::AddToDetailsPanel`)
- L787 _function_ `TAttribute<bool> NaniteEnabledAndNoHiResDataAttr = TAttribute<bool>::Create(TAttribute<bool>::FGetter::CreateLambda([this, NaniteEnabledCheck]() -> bool {return NaniteEnabledCheck->IsChecked() && IsHiResDataEmpty(); }));` (scope `Nanite::FSettingsLayout::AddToDetailsPanel`)
- L788 _function_ `TAttribute<bool> NaniteEnabledWithVoxelsAttr = TAttribute<bool>::Create(TAttribute<bool>::FGetter::CreateLambda([this, NaniteEnabledCheck]() -> bool { return NaniteEnabledCheck->IsChecked() && NaniteSettings.ShapePreservation == ENaniteShapePreservation::Voxelize; }));` (scope `Nanite::FSettingsLayout::AddToDetailsPanel`)

### `Source/Developer/NaniteUtilities/Public/Optimize.h` (Public)


#### Free symbols / members of external scopes

- L7 _function_ `FORCEINLINE float InverseLerp( float y, float x0, float y0, float x1, float y1 )`
- L15 _function_ `FORCEINLINE float InverseLerp( float y, float x0, float y0, float x1, float y1, float x2, float y2 )`
- L38 _function_ `template< typename FuncType > float BrentRootFind( float y, float Tolerance, float xA, float yA, float xB, float yB, float xGuess, bool bInitialGuess, int32 MaxIter, FuncType&& Func )` — Brent's method
- L132 _function_ `template< typename FuncType > float DownhillSimplex( FVector2f& x, float xDelta, float Tolerance, int32 MaxIter, FuncType&& Func )` — Nelder-Mead optimization TODO This is only 2D, make any dimensions.

### `Source/Developer/NaniteUtilities/Public/Range.h` (Public)


#### struct `FRange`  
`struct FRange`  
_L7-15_
- L9 _public member_ `uint32 Begin;`
- L10 _public member_ `uint32 End;`
- L12 _public function_ `uint32 Num() const`
- L14 _public function_ `bool operator<( const FRange& Other) const`

### `Source/Developer/NaniteUtilities/Public/Rasterizer.h` (Public)


#### struct `Rasterizer::FTriangle`  
`struct FTriangle`  
_L39-166_
- desc: Fixed point rasterization
- L41 _public member_ `FIntVector2 Vert0;`
- L42 _public member_ `FIntVector2 Vert1;`
- L43 _public member_ `FIntVector2 Vert2;`
- L45 _public member_ `FIntVector2 MinPixel;`
- L46 _public member_ `FIntVector2 MaxPixel;`
- L48 _public member_ `FIntVector2 Edge01;`
- L49 _public member_ `FIntVector2 Edge12;`
- L50 _public member_ `FIntVector2 Edge20;`
- L52 _public member_ `int32 C0;`
- L53 _public member_ `int32 C1;`
- L54 _public member_ `int32 C2;`
- L56 _public member_ `bool bBackFace;`
- L58 _public function_ `FTriangle( const FVector3f Verts[3], FIntVector2 ScissorMin, FIntVector2 ScissorMax, int32 SubpixelDilate = 0 )`
- L109 _public function_ `inline bool IsCovered( int32 x, int32 y ) const`
- L122 _public function_ `template< typename FFunc > void ForAllCovered( FFunc&& Func ) const`
- L150 _public function_ `inline FVector3f GetBarycentrics( int32 x, int32 y ) const`

#### struct `Rasterizer::FTriangle3f`  
`struct FTriangle3f`  
_L184-322_
- desc: Floating point rasterization
- L186 _public member_ `FVector3f Vert0;`
- L187 _public member_ `FVector3f Vert1;`
- L188 _public member_ `FVector3f Vert2;`
- L190 _public member_ `FVector3f Min;`
- L191 _public member_ `FVector3f Max;`
- L193 _public member_ `FVector3f Edge01;`
- L194 _public member_ `FVector3f Edge12;`
- L195 _public member_ `FVector3f Edge20;`
- L197 _public member_ `FVector4f Plane;`
- L199 _public function_ `inline FTriangle3f()`
- L200 _public function_ `inline FTriangle3f( const FVector3f Verts[3] )`
- L217 _public function_ `inline FVector3f GetBarycentrics( float x, float y ) const`
- L234 _public function_ `inline FVector3f GetBarycentrics( const FVector3f& Point ) const`
- L254 _public function_ `inline bool IsCovered( const FVector2f& Center, const FVector2f& Extent ) const`
- L263 _public function_ `inline bool IsCovered( int32 x, int32 y, float PixelExtent = 0.0f ) const`
- L268 _public function_ `inline bool IsCovered( FVector3f Origin, FVector3f Direction, FVector2f Time )`
- L292 _public function_ `inline FVector3f GetDepthPlane() const`
- L304 _public function_ `inline FTriangle3f Swizzle( int32 X, int32 Y, int32 Z ) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Rasterizer`
- L11 _variable_ `constexpr int32 SubpixelBits = 8;` (scope `Rasterizer`)
- L12 _variable_ `constexpr int32 SubpixelSamples = 1 << SubpixelBits;` (scope `Rasterizer`)
- L14 _function_ `FORCEINLINE int32 EdgeC( const FIntVector2& Edge, const FIntVector2& Vert, int32 SubpixelDilate = 0 )` (scope `Rasterizer`)
- L168 _function_ `inline bool IsCovered( const FVector2f& Edge, const FVector2f& Vert, const FVector2f& Center, const FVector2f& Extent )` (scope `Rasterizer`)
- L327 _function_ `template< typename FWritePixel > void RasterizeTri( const FVector3f Verts[3], const FIntRect& ScissorRect, uint32 SubpixelDilate, bool bBackFaceCull, FWritePixel&& WritePixel )`
- L341 _function_ `` (scope `RasterizeTri`)
- L355 _function_ `template< typename FWriteVoxel > void VoxelizeTri6( const Rasterizer::FTriangle3f& Tri, FWriteVoxel&& WriteVoxel )` — 6-separating voxelization
- L453 _function_ `template< typename FWriteVoxel > void VoxelizeTri26( const Rasterizer::FTriangle3f& Tri, FWriteVoxel&& WriteVoxel )` — 26-separating voxelization, conservative

### `Source/Developer/NaniteUtilities/Public/SGGX.h` (Public)


#### struct `TSGGX`  
`template< typename T > struct TSGGX`  
_L15-47_
- L17 _public typedef_ `template< typename U > using TVector2 = UE::Math::TVector2<U>;`
- L18 _public typedef_ `template< typename U > using TVector2 = UE::Math::TVector2<U>;`
- L20 _public member_ `T xx;`
- L21 _public member_ `T yy;`
- L22 _public member_ `T zz;`
- L24 _public member_ `T xy;`
- L25 _public member_ `T xz;`
- L26 _public member_ `T yz;`
- L28 _public prototype_ `TSGGX() = default;`
- L29 _public prototype_ `TSGGX( const TVector<T>& Normal );`
- L31 _public prototype_ `TSGGX& operator+=( const TSGGX& Other );`
- L32 _public prototype_ `TSGGX& operator+=( const TVector<T>& Normal );`
- L34 _public prototype_ `TSGGX& operator*=( T Scalar );`
- L35 _public prototype_ `TSGGX& operator/=( T Scalar );`
- L37 _public prototype_ `TSGGX operator+( const TSGGX& Other ) const;`
- L38 _public prototype_ `TSGGX operator*( T Scalar ) const;`
- L40 _public prototype_ `T ProjectedArea( const TVector<T>& Direction ) const;`
- L41 _public prototype_ `T SurfaceArea() const;`
- L43 _public prototype_ `void EigenSolve( TVector<T>& Values, TVector<T> Vectors[3] ) const;`
- L44 _public prototype_ `void FitIsotropic( TVector<T>& Center, TVector2<T>& Alpha ) const;`
- L46 _public prototype_ `static T SurfaceArea( const TVector<T>& EigenValues );`
- L50 _function_ `template< typename T > FORCEINLINE TSGGX<T>::TSGGX( const TVector<T>& Normal )`
- L63 _function_ `template< typename T > FORCEINLINE TSGGX<T>& TSGGX<T>::operator+=( const TSGGX<T>& Other )`
- L77 _function_ `template< typename T > FORCEINLINE TSGGX<T>& TSGGX<T>::operator+=( const TVector<T>& Normal )`
- L83 _function_ `template< typename T > FORCEINLINE TSGGX<T>& TSGGX<T>::operator*=( T Scalar )`
- L97 _function_ `template< typename T > FORCEINLINE TSGGX<T>& TSGGX<T>::operator/=( T Scalar )`
- L111 _function_ `template< typename T > FORCEINLINE TSGGX<T> TSGGX<T>::operator+( const TSGGX<T>& Other ) const`
- L117 _function_ `template< typename T > FORCEINLINE TSGGX<T> TSGGX<T>::operator*( T Scalar ) const`
- L129 _function_ `template< typename T > FORCEINLINE T TSGGX<T>::ProjectedArea( const TVector<T>& Direction ) const`
- L144 _function_ `template< typename T > void TSGGX<T>::EigenSolve( TVector<T>& Values, TVector<T> Vectors[3] ) const`
- L169 _function_ `template< typename T > void TSGGX<T>::FitIsotropic( TVector<T>& Center, TVector2<T>& Alpha ) const`
- L226 _function_ `template< typename T > T TSGGX<T>::SurfaceArea( const TVector<T>& Values )`
- L246 _function_ `template< typename T > T TSGGX<T>::SurfaceArea() const`

#### Free symbols / members of external scopes

- L123 _function_ `template< typename T > FORCEINLINE TSGGX<T> operator*( T Scalar, const TSGGX<T>& SGGX )`
- L206 _function_ `FORCEINLINE float SurfaceAreaEllipsoid( float a, float b, float c )` — Approx surface area of ellipsoid

### `Source/Developer/NaniteUtilities/Public/TriangleUtil.h` (Public)


#### union `Nanite::HashPosition::(anonymous)`  
`union`  
_L13-13_

#### class `Nanite::FEdgeHash`  
`class FEdgeHash`  
_L166-211_
- desc: /\ /  \ o-<<-o o->>-o \  / \/
- L169 _public member_ `FHashTable HashTable;`
- L171 _public function_ `FEdgeHash( int32 Num ) : HashTable( 1 << FMath::FloorLog2( Num ), Num )`
- L176 _public function_ `template< typename FGetPosition > void Add_Concurrent( int32 EdgeIndex, FGetPosition&& GetPosition )`
- L189 _public function_ `template< typename FGetPosition, typename FuncType > void ForAllMatching( int32 EdgeIndex, bool bAdd, FGetPosition&& GetPosition, FuncType&& Function )`

#### struct `Nanite::FAdjacency`  
`struct FAdjacency`  
_L214-253_
- L216 _public member_ `TArray< int32 > Direct;`
- L217 _public member_ `TMultiMap< int32, int32 > Extended;`
- L219 _public function_ `FAdjacency( int32 Num )`
- L224 _public function_ `void Link( int32 EdgeIndex0, int32 EdgeIndex1 )`
- L240 _public function_ `template< typename FuncType > void ForAll( int32 EdgeIndex, FuncType&& Function ) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Nanite`
- L11 _function_ `FORCEINLINE uint32 HashPosition( const FVector3f& Position )` (scope `Nanite`)
- L13 _member_ `union { float f; uint32 i; } x;` (scope `Nanite::HashPosition::__anon7ee2e3cd010a`)
- L13 _member_ `union { float f; uint32 i; } x;` (scope `Nanite::HashPosition::__anon7ee2e3cd010a`)
- L14 _member_ `union { float f; uint32 i; } y;` (scope `Nanite::HashPosition::__anon7ee2e3cd020a`)
- L14 _member_ `union { float f; uint32 i; } y;` (scope `Nanite::HashPosition::__anon7ee2e3cd020a`)
- L15 _member_ `union { float f; uint32 i; } z;` (scope `Nanite::HashPosition::__anon7ee2e3cd030a`)
- L15 _member_ `union { float f; uint32 i; } z;` (scope `Nanite::HashPosition::__anon7ee2e3cd030a`)
- L28 _function_ `FORCEINLINE uint32 Cycle3( uint32 Value )` (scope `Nanite`)
- L35 _function_ `FORCEINLINE uint32 Cycle3( uint32 Value, uint32 Offset )` (scope `Nanite`)
- L40 _function_ `FORCEINLINE float EquilateralArea( float EdgeLength )` (scope `Nanite`)
- L46 _function_ `FORCEINLINE float EquilateralEdgeLength( float Area )` (scope `Nanite`)
- L52 _function_ `FORCEINLINE float TriangleArea( float a, float b, float c )` (scope `Nanite`)
- L63 _function_ `FORCEINLINE int32 ApproxNumTris( int32 a, int32 b, int32 c )` (scope `Nanite`) — a,b,c are tessellation factors for each edge
- L73 _namespace_ `namespace Barycentric` (scope `Nanite`)
- L76 _function_ `FORCEINLINE float LengthSquared( const FVector3f& Barycentrics0, const FVector3f& Barycentrics1, const FVector3f& EdgeLengthsSqr )` (scope `Nanite::Barycentric`) — [ Schindler and Chen 2012, "Barycentric Coordinates in Olympiad Geometry" https://web.evanchen.cc/handouts/bary/bary-full.pdf ]
- L96 _function_ `FORCEINLINE float SubtriangleArea( const FVector3f& Barycentrics0, const FVector3f& Barycentrics1, const FVector3f& Barycentrics2, float TriangleArea )` (scope `Nanite::Barycentric`)
- L103 _function_ `FORCEINLINE float DistanceToEdge( float Barycentric, float EdgeLength, float TriangleArea )` (scope `Nanite::Barycentric`) — https://math.stackexchange.com/questions/3748903/closest-point-to-triangle-edge-with-barycentric-coordinates
- L109 _function_ `FORCEINLINE float Cotangent( const FVector3f& Barycentrics0, const FVector3f& Barycentrics1, const FVector3f& Barycentrics2, const FVector3f& EdgeLengthsSqr, float TriangleArea )` (scope `Nanite::Barycentric`) — Angle at corner 0
- L127 _function_ `FORCEINLINE void SubtriangleBarycentrics( uint32 TriX, uint32 TriY, uint32 FlipTri, uint32 NumSubdivisions, FVector3f Barycentrics[3] )` (scope `Nanite`)

### `Source/Developer/NaniteUtilities/Public/VectorMathOps.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Math` (scope `UE`)
- L10 _function_ `template< typename T > FORCEINLINE TVector2<T> operator+( T S, const TVector2<T>& V )` (scope `UE::Math`)
- L14 _function_ `template< typename T > FORCEINLINE TVector2<T> operator-( T S, const TVector2<T>& V )` (scope `UE::Math`)
- L18 _function_ `template< typename T > FORCEINLINE TIntVector2<T> operator+( const TIntVector2<T>& V, T S )` (scope `UE::Math`)
- L22 _function_ `template< typename T > FORCEINLINE TIntVector2<T> operator-( const TIntVector2<T>& V, T S )` (scope `UE::Math`)
- L26 _function_ `template< typename T > FORCEINLINE TIntVector2<T> operator+( T S, const TIntVector2<T>& V )` (scope `UE::Math`)
- L30 _function_ `template< typename T > FORCEINLINE TIntVector2<T> operator-( T S, const TIntVector2<T>& V )` (scope `UE::Math`)
- L34 _function_ `template< typename T > FORCEINLINE TIntVector2<T> operator*( T S, const TIntVector2<T>& V )` (scope `UE::Math`)
- L38 _function_ `template< typename T > FORCEINLINE FVector2f operator+( const TIntVector2<T>& V, float S )` (scope `UE::Math`)
- L42 _function_ `template< typename T > FORCEINLINE FVector2f operator-( const TIntVector2<T>& V, float S )` (scope `UE::Math`)
- L46 _function_ `template< typename T > FORCEINLINE FVector2f operator+( float S, const TIntVector2<T>& V )` (scope `UE::Math`)
- L50 _function_ `template< typename T > FORCEINLINE FVector2f operator-( float S, const TIntVector2<T>& V )` (scope `UE::Math`)
- L54 _function_ `template< typename T > FORCEINLINE FVector2f operator*( const TIntVector2<T>& V, float S )` (scope `UE::Math`)
- L58 _function_ `template< typename T > FORCEINLINE FVector2f operator*( float S, const TIntVector2<T>& V )` (scope `UE::Math`)
- L62 _function_ `template< typename T > FORCEINLINE FVector2f operator/( float S, const TVector2<T>& V )` (scope `UE::Math`)
- L66 _function_ `template< typename T > FORCEINLINE TIntVector2<T>& operator+=( TIntVector2<T>& V, T S )` (scope `UE::Math`)
- L70 _function_ `template< typename T > FORCEINLINE TIntVector2<T>& operator-=( TIntVector2<T>& V, T S )` (scope `UE::Math`)
- L74 _function_ `template< typename T > FORCEINLINE FVector2f operator+( const FVector2f& F, const TIntVector2<T>& I )` (scope `UE::Math`)
- L78 _function_ `template< typename T > FORCEINLINE FVector2f operator+( const TIntVector2<T>& I, const FVector2f& F )` (scope `UE::Math`)
- L82 _function_ `template< typename T > FORCEINLINE FVector2f operator-( const FVector2f& F, const TIntVector2<T>& I )` (scope `UE::Math`)
- L86 _function_ `template< typename T > FORCEINLINE FVector2f operator-( const TIntVector2<T>& I, const FVector2f& F )` (scope `UE::Math`)
- L90 _function_ `template< typename T > FORCEINLINE TIntVector2<T> Abs( const TIntVector2<T>& V )` (scope `UE::Math`)
- L94 _function_ `template< typename T > FORCEINLINE TIntVector2<T> Min( const TIntVector2<T>& A, const TIntVector2<T>& B )` (scope `UE::Math`)
- L98 _function_ `template< typename T > FORCEINLINE TIntVector2<T> Max( const TIntVector2<T>& A, const TIntVector2<T>& B )` (scope `UE::Math`)
- L102 _function_ `template< typename T > FORCEINLINE TIntVector2<T> Min3( const TIntVector2<T>& A, const TIntVector2<T>& B, const TIntVector2<T>& C )` (scope `UE::Math`)
- L106 _function_ `template< typename T > FORCEINLINE TIntVector2<T> Max3( const TIntVector2<T>& A, const TIntVector2<T>& B, const TIntVector2<T>& C )` (scope `UE::Math`)
- L110 _function_ `template< typename T > FORCEINLINE TVector2<T> Abs( const TVector2<T>& V )` (scope `UE::Math`)
- L114 _function_ `template< typename T > FORCEINLINE TVector2<T> Min( const TVector2<T>& A, const TVector2<T>& B )` (scope `UE::Math`)
- L118 _function_ `template< typename T > FORCEINLINE TVector2<T> Max( const TVector2<T>& A, const TVector2<T>& B )` (scope `UE::Math`)
- L122 _function_ `template< typename T > FORCEINLINE TVector2<T> Min3( const TVector2<T>& A, const TVector2<T>& B, const TVector2<T>& C )` (scope `UE::Math`)
- L126 _function_ `template< typename T > FORCEINLINE TVector2<T> Max3( const TVector2<T>& A, const TVector2<T>& B, const TVector2<T>& C )` (scope `UE::Math`)
- L130 _function_ `template< typename T > FORCEINLINE TVector2<T> Floor( const TVector2<T>& V )` (scope `UE::Math`)
- L134 _function_ `template< typename T > FORCEINLINE TVector2<T> Ceil( const TVector2<T>& V )` (scope `UE::Math`)
- L138 _function_ `FORCEINLINE FIntVector2 FloorToInt( const FVector2f& V )` (scope `UE::Math`)
- L139 _function_ `FORCEINLINE FIntVector3 FloorToInt( const FVector3f& V )` (scope `UE::Math`)
- L140 _function_ `FORCEINLINE FIntVector4 FloorToInt( const FVector4f& V )` (scope `UE::Math`)
- L142 _function_ `FORCEINLINE FIntVector2 RoundToInt( const FVector2f& V )` (scope `UE::Math`)
- L143 _function_ `FORCEINLINE FIntVector3 RoundToInt( const FVector3f& V )` (scope `UE::Math`)
- L144 _function_ `FORCEINLINE FIntVector4 RoundToInt( const FVector4f& V )` (scope `UE::Math`)
- L146 _function_ `FORCEINLINE FIntVector2 CeilToInt( const FVector2f& V )` (scope `UE::Math`)
- L147 _function_ `FORCEINLINE FIntVector3 CeilToInt( const FVector3f& V )` (scope `UE::Math`)
- L148 _function_ `FORCEINLINE FIntVector4 CeilToInt( const FVector4f& V )` (scope `UE::Math`)
- L151 _namespace_ `namespace Scalar` (scope `UE::Math`)
- L153 _function_ `template< typename T > FORCEINLINE T Abs( const T A )` (scope `UE::Math::Scalar`)
- L154 _function_ `template< typename T > FORCEINLINE T Abs( const T A )` (scope `UE::Math::Scalar`)
- L155 _function_ `template< typename T > FORCEINLINE T Abs( const T A )` (scope `UE::Math::Scalar`)
- L156 _function_ `template< typename T > FORCEINLINE T Abs( const T A )` (scope `UE::Math::Scalar`)
- L157 _function_ `template< typename T > FORCEINLINE T Min( const T A, const T B )` (scope `UE::Math::Scalar`)
- L158 _function_ `template< typename T > FORCEINLINE T Max( const T A, const T B )` (scope `UE::Math::Scalar`)
- L159 _function_ `template< typename T > FORCEINLINE T Min3( const T A, const T B, const T C )` (scope `UE::Math::Scalar`)
- L160 _function_ `template< typename T > FORCEINLINE T Max3( const T A, const T B, const T C )` (scope `UE::Math::Scalar`)
