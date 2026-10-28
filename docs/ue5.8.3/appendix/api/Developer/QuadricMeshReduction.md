# Developer / QuadricMeshReduction

- module root: `Source/Developer/MeshSimplifier`
- headers: 4; symbols: 343
- symbol kinds: class=12, enum=2, enumerator=9, function=97, macro=5, member=115, prototype=95, struct=3, typedef=4, union=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MeshDescription, MeshUtilitiesCommon, NaniteUtilities, RenderCore, StaticMeshDescription
- PrivateIncludePathModuleNames: MeshReductionInterface

### `Source/Developer/MeshSimplifier/Private/MeshSimplify.h` (Private)


#### union `HashPosition::(anonymous)`  
`union`  
_L17-17_

#### class `FMeshSimplifier`  
`class FMeshSimplifier`  
_L45-183_
- L48 _public prototype_ `FMeshSimplifier( float* Verts, uint32 NumVerts, uint32* Indexes, uint32 NumIndexes, int32* MaterialIndexes, uint32 NumAttributes );`
- L49 _public prototype_ `~FMeshSimplifier() = default;`
- L51 _public function_ `void SetAttributeWeights( const float* Weights )`
- L52 _public function_ `void SetEdgeWeight( float Weight )`
- L53 _public function_ `void SetMaxEdgeLengthFactor( float Factor )`
- L54 _public function_ `void SetCorrectAttributes( void (*Function)( float* ) )`
- L55 _public function_ `void SetLimitErrorToSurfaceArea( bool Value )`
- L57 _public prototype_ `void LockPosition( const FVector3f& Position );`
- L59 _public prototype_ `float Simplify( uint32 TargetNumVerts, uint32 TargetNumTris, float TargetError, uint32 LimitNumVerts, uint32 LimitNumTris, float LimitError );`
- L62 _public prototype_ `void PreserveSurfaceArea();`
- L63 _public prototype_ `void ShrinkTriGroupWithMostSurfaceAreaLoss( float ShrinkAmount );`
- L64 _public prototype_ `void ShrinkVoxelTriangles( float ShrinkAmount, TBitArray<>& InVoxelTriangles );`
- L65 _public prototype_ `void DumpOBJ( const char* Filename );`
- L66 _public prototype_ `void Compact();`
- L68 _public function_ `uint32 GetRemainingNumVerts() const`
- L69 _public function_ `uint32 GetRemainingNumTris() const`
- L71 _public member_ `int32 DegreeLimit = 24;`
- L72 _public member_ `float DegreePenalty = 0.5f;`
- L73 _public member_ `float LockPenalty = 1e8f;`
- L74 _public member_ `float InversionPenalty = 100.0f;`
- L77 _protected member_ `uint32 NumVerts;`
- L78 _protected member_ `uint32 NumIndexes;`
- L79 _protected member_ `uint32 NumAttributes;`
- L80 _protected member_ `uint32 NumTris;`
- L82 _protected member_ `uint32 RemainingNumVerts;`
- L83 _protected member_ `uint32 RemainingNumTris;`
- L85 _protected member_ `float* Verts;`
- L86 _protected member_ `uint32* Indexes;`
- L87 _protected member_ `int32* MaterialIndexes;`
- L89 _protected member_ `const float* AttributeWeights = nullptr;`
- L90 _protected member_ `float EdgeWeight = 8.0f;`
- L91 _protected member_ `float MaxEdgeLengthFactor = 0.0f;`
- L92 _protected member_ `void (*CorrectAttributes)( float* ) = nullptr;`
- L93 _protected member_ `bool bLimitErrorToSurfaceArea = true;`
- L94 _protected member_ `bool bZeroWeights = false;`
- L96 _protected member_ `FHashTable VertHash;`
- L97 _protected member_ `FHashTable CornerHash;`
- L99 _protected member_ `TArray< uint32 > VertRefCount;`
- L100 _protected member_ `TArray< uint8 > CornerFlags;`
- L101 _protected member_ `TBitArray<> TriRemoved;`
- L109 _protected member_ `TArray< FPerMaterialDeltas > PerMaterialDeltas;`
- L116 _protected member_ `TArray< FPair > Pairs;`
- L117 _protected member_ `FHashTable PairHash0;`
- L118 _protected member_ `FHashTable PairHash1;`
- L119 _protected member_ `FBinaryHeap< float > PairHeap;`
- L121 _protected member_ `TArray< uint32 > MovedVerts;`
- L122 _protected member_ `TArray< uint32 > MovedCorners;`
- L123 _protected member_ `TArray< uint32 > MovedPairs;`
- L124 _protected member_ `TArray< uint32 > ReevaluatePairs;`
- L126 _protected member_ `TArray64< uint8 > TriQuadrics;`
- L127 _protected member_ `TArray< FEdgeQuadric > EdgeQuadrics;`
- L128 _protected member_ `TBitArray<> EdgeQuadricsValid;`
- L130 _protected member_ `TArray< float > WedgeAttributes;`
- L131 _protected member_ `FDisjointSet WedgeDisjointSet;`
- L133 _protected member_ `TArray< float > BackupVertData;`
- L134 _protected member_ `int32 BackupMaterialIndex = INDEX_NONE;`
- L135 _protected member_ `float BackupArea = 0.0f;`
- L136 _protected member_ `float TotalInputArea = 0.0f;`
- L137 _protected member_ `bool bBackupValid = false;`
- L148 _protected prototype_ `FVector3f& GetPosition( uint32 VertIndex );`
- L149 _protected prototype_ `const FVector3f& GetPosition( uint32 VertIndex ) const;`
- L150 _protected prototype_ `float* GetAttributes( uint32 VertIndex );`
- L151 _protected prototype_ `FQuadricAttr& GetTriQuadric( uint32 TriIndex );`
- L154 _protected prototype_ `template< typename FuncType > void ForAllVerts( const FVector3f& Position, FuncType&& Function ) const;`
- L157 _protected prototype_ `template< typename FuncType > void ForAllCorners( const FVector3f& Position, FuncType&& Function ) const;`
- L160 _protected prototype_ `template< typename FuncType > void ForAllPairs( const FVector3f& Position, FuncType&& Function ) const;`
- L162 _protected prototype_ `bool AddUniquePair( FPair& Pair, uint32 PairIndex );`
- L164 _protected prototype_ `void CalcTriQuadric( uint32 TriIndex );`
- L165 _protected prototype_ `void CalcEdgeQuadric( uint32 EdgeIndex );`
- L167 _protected prototype_ `float EvaluateMerge( const FVector3f& Position0, const FVector3f& Position1, bool bMoveVerts );`
- L169 _protected prototype_ `void BeginMovePosition( const FVector3f& Position );`
- L170 _protected prototype_ `void EndMovePositions();`
- L172 _protected prototype_ `uint32 CornerIndexMoved( uint32 TriIndex ) const;`
- L173 _protected prototype_ `bool TriWillInvert( uint32 TriIndex, const FVector3f& NewPosition ) const;`
- L175 _protected prototype_ `void RemoveTri( uint32 TriIndex );`
- L176 _protected prototype_ `void FixUpTri( uint32 TriIndex );`
- L177 _protected prototype_ `bool IsDuplicateTri( uint32 TriIndex ) const;`
- L178 _protected prototype_ `void SetVertIndex( uint32 Corner, uint32 NewVertIndex );`
- L179 _protected prototype_ `void RemoveDuplicateVerts( uint32 Corner );`
- L181 _protected prototype_ `void CaptureBackupTriangle( uint32 TriIndex, float Area );`
- L182 _protected prototype_ `void RestoreBackupTriangle( float& InOutMaxError );`
- L186 _function_ `FORCEINLINE FVector3f& FMeshSimplifier::GetPosition( uint32 VertIndex )`
- L191 _function_ `FORCEINLINE const FVector3f& FMeshSimplifier::GetPosition( uint32 VertIndex ) const`
- L196 _function_ `FORCEINLINE float* FMeshSimplifier::GetAttributes( uint32 VertIndex )`
- L201 _function_ `FORCEINLINE FQuadricAttr& FMeshSimplifier::GetTriQuadric( uint32 TriIndex )`
- L208 _function_ `template< typename FuncType > void FMeshSimplifier::ForAllVerts( const FVector3f& Position, FuncType&& Function ) const`
- L221 _function_ `template< typename FuncType > void FMeshSimplifier::ForAllCorners( const FVector3f& Position, FuncType&& Function ) const`
- L234 _function_ `template< typename FuncType > void FMeshSimplifier::ForAllPairs( const FVector3f& Position, FuncType&& Function ) const`

#### struct `FMeshSimplifier::FPerMaterialDeltas`  
`struct FPerMaterialDeltas`  
_L103-108_
- L105 _public member_ `float SurfaceArea;`
- L106 _public member_ `int32 NumTris;`
- L107 _public member_ `int32 NumDisjoint;`

#### struct `FMeshSimplifier::FPair`  
`struct FPair`  
_L111-115_
- L113 _public member_ `FVector3f Position0;`
- L114 _public member_ `FVector3f Position1;`

#### enum `FMeshSimplifier::ECornerFlags`  
`enum ECornerFlags`  
_L139-145_
- L141 _public enumerator_ `MergeMask = 3` — Merge position 0 or 1
- L142 _public enumerator_ `AdjTriMask = (1 << 2)` — Has been added to AdjTris
- L143 _public enumerator_ `LockedVertMask = (1 << 3)` — Vert is locked, disallowing position movement
- L144 _public enumerator_ `RemoveTriMask = (1 << 4)` — Triangle will overlap another after merge and should be removed

#### Free symbols / members of external scopes

- L8 _macro_ `#define SIMP_REBASE 1`
- L15 _function_ `FORCEINLINE uint32 HashPosition( const FVector3f& Position )`
- L17 _member_ `union { float f; uint32 i; } x;` (scope `HashPosition::__anon35e32d75010a`)
- L17 _member_ `union { float f; uint32 i; } x;` (scope `HashPosition::__anon35e32d75010a`)
- L18 _member_ `union { float f; uint32 i; } y;` (scope `HashPosition::__anon35e32d75020a`)
- L18 _member_ `union { float f; uint32 i; } y;` (scope `HashPosition::__anon35e32d75020a`)
- L19 _member_ `union { float f; uint32 i; } z;` (scope `HashPosition::__anon35e32d75030a`)
- L19 _member_ `union { float f; uint32 i; } z;` (scope `HashPosition::__anon35e32d75030a`)
- L32 _function_ `FORCEINLINE uint32 Cycle3( uint32 Value )`
- L39 _function_ `FORCEINLINE uint32 Cycle3( uint32 Value, uint32 Offset )`

### `Source/Developer/MeshSimplifier/Private/MeshSimplifyElements.h` (Private)


#### enum `ESimpElementFlags`  
`enum ESimpElementFlags`  
_L11-18_
- L13 _public enumerator_ `SIMP_DEFAULT = 0`
- L14 _public enumerator_ `SIMP_REMOVED = 1 << 0`
- L15 _public enumerator_ `SIMP_MARK1 = 1 << 1`
- L16 _public enumerator_ `SIMP_MARK2 = 1 << 2`
- L17 _public enumerator_ `SIMP_LOCKED = 1 << 3`

#### class `TSimpVert`  
`template< typename T > class TSimpVert`  
_L24-78_
- L27 _public prototype_ `TSimpVert();`
- L29 _public function_ `FVector3f& GetPos()`
- L30 _public function_ `const FVector3f& GetPos() const`
- L31 _public function_ `float* GetAttributes()`
- L32 _public function_ `const float* GetAttributes() const`
- L35 _public prototype_ `void EnableFlags( uint32 f );` — this vert
- L36 _public prototype_ `void DisableFlags( uint32 f );`
- L37 _public prototype_ `bool TestFlags( uint32 f ) const;`
- L39 _public prototype_ `void EnableAdjVertFlags( uint32 f );`
- L40 _public prototype_ `void DisableAdjVertFlags( uint32 f );`
- L42 _public prototype_ `void EnableAdjTriFlags( uint32 f );`
- L43 _public prototype_ `void DisableAdjTriFlags( uint32 f );`
- L46 _public prototype_ `template< typename Allocator > void FindAdjacentVerts( TArray< TSimpVert<T>*, Allocator >& adjVerts );`
- L49 _public prototype_ `void EnableFlagsGroup( uint32 f );` — all verts in group
- L50 _public prototype_ `void DisableFlagsGroup( uint32 f );`
- L53 _public prototype_ `void EnableAdjVertFlagsGroup( uint32 f );`
- L54 _public prototype_ `void DisableAdjVertFlagsGroup( uint32 f );`
- L56 _public prototype_ `void EnableAdjTriFlagsGroup( uint32 f );`
- L57 _public prototype_ `void DisableAdjTriFlagsGroup( uint32 f );`
- L60 _public prototype_ `template< typename Allocator > void FindAdjacentVertsGroup( TArray< TSimpVert<T>*, Allocator >& adjVerts );`
- L62 _public typedef_ `typedef TUnrolledLinkList< TSimpTri<T>*, 8 > TriList;`
- L63 _public typedef_ `typedef typename TriList::TIterator TriIterator;`
- L66 _public member_ `TSimpVert<T>* next;` — other verts sharing same point grouped
- L67 _public member_ `TSimpVert<T>* prev;`
- L70 _public member_ `uint32 flags;` — bitfield of ESimpElementFlags
- L72 _public member_ `T vert;`
- L77 _public member_ `TriList adjTris;` — Adjacent triangles, all triangles which reference this vert TODO could be link list of index buffer elements /3 gives tri index
- L132 _function_ `template< typename T > FORCEINLINE TSimpVert<T>::TSimpVert() : flags( SIMP_DEFAULT )`
- L140 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::EnableFlags( uint32 f )`
- L146 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::DisableFlags( uint32 f )`
- L152 _function_ `template< typename T > FORCEINLINE bool TSimpVert<T>::TestFlags( uint32 f ) const`
- L158 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::EnableAdjVertFlags( uint32 f )`
- L170 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::DisableAdjVertFlags( uint32 f )`
- L182 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::EnableAdjTriFlags( uint32 f )`
- L191 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::DisableAdjTriFlags( uint32 f )`
- L201 _function_ `template< typename T > template< typename Allocator > void TSimpVert<T>::FindAdjacentVerts( TArray< TSimpVert<T>*, Allocator >& adjVerts )`
- L218 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::EnableFlagsGroup( uint32 f )`
- L228 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::DisableFlagsGroup( uint32 f )`
- L238 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::EnableAdjVertFlagsGroup( uint32 f )`
- L248 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::DisableAdjVertFlagsGroup( uint32 f )`
- L258 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::EnableAdjTriFlagsGroup( uint32 f )`
- L268 _function_ `template< typename T > FORCEINLINE void TSimpVert<T>::DisableAdjTriFlagsGroup( uint32 f )`
- L279 _function_ `template< typename T > template< typename Allocator > void TSimpVert<T>::FindAdjacentVertsGroup( TArray< TSimpVert<T>*, Allocator >& adjVerts )`

#### class `TSimpTri`  
`template< typename T > class TSimpTri`  
_L81-102_
- L84 _public function_ `TSimpTri() : flags( SIMP_DEFAULT )`
- L88 _public prototype_ `void EnableFlags( uint32 f );`
- L89 _public prototype_ `void DisableFlags( uint32 f );`
- L90 _public prototype_ `bool TestFlags( uint32 f ) const;`
- L92 _public prototype_ `bool HasVertex( const TSimpVert<T>* v ) const;`
- L93 _public prototype_ `FVector3f GetNormal() const;`
- L95 _public prototype_ `bool ReplaceVertexIsValid( const TSimpVert<T>* oldV, const FVector3f& pos ) const;`
- L96 _public prototype_ `void ReplaceVertex( TSimpVert<T>* oldV, TSimpVert<T>* newV );`
- L98 _public member_ `TSimpVert<T>* verts[3];`
- L101 _public member_ `uint32 flags;` — bitfield of ESimpElementFlags
- L304 _function_ `template< typename T > FORCEINLINE void TSimpTri<T>::EnableFlags( uint32 f )`
- L310 _function_ `template< typename T > FORCEINLINE void TSimpTri<T>::DisableFlags( uint32 f )`
- L316 _function_ `template< typename T > FORCEINLINE bool TSimpTri<T>::TestFlags( uint32 f ) const`
- L322 _function_ `template< typename T > FORCEINLINE bool TSimpTri<T>::HasVertex( const TSimpVert<T>* v ) const`
- L328 _function_ `template< typename T > FORCEINLINE FVector3f TSimpTri<T>::GetNormal() const`
- L336 _function_ `template< typename T > FORCEINLINE bool TSimpTri<T>::ReplaceVertexIsValid( const TSimpVert<T>* oldV, const FVector3f& pos ) const`
- L364 _function_ `template< typename T > FORCEINLINE void TSimpTri<T>::ReplaceVertex( TSimpVert<T>* oldV, TSimpVert<T>* newV )`

#### class `TSimpEdge`  
`template< typename T > class TSimpEdge`  
_L105-125_
- L108 _public prototype_ `TSimpEdge();`
- L110 _public prototype_ `void EnableFlags( uint32 f );`
- L111 _public prototype_ `void DisableFlags( uint32 f );`
- L112 _public prototype_ `bool TestFlags( uint32 f ) const;`
- L117 _public member_ `TSimpEdge* next;` — Edge group Link list of all edges sharing the same end points, different attributes. Need multiple edges to know which in both vert groups are connected.
- L118 _public member_ `TSimpEdge* prev;`
- L120 _public member_ `TSimpVert<T>* v0;`
- L121 _public member_ `TSimpVert<T>* v1;`
- L124 _public member_ `uint32 flags;` — bitfield of ESimpElementFlags
- L385 _function_ `template< typename T > FORCEINLINE TSimpEdge<T>::TSimpEdge() : flags( SIMP_DEFAULT )`
- L393 _function_ `template< typename T > FORCEINLINE void TSimpEdge<T>::EnableFlags( uint32 f )`
- L399 _function_ `template< typename T > FORCEINLINE void TSimpEdge<T>::DisableFlags( uint32 f )`
- L405 _function_ `template< typename T > FORCEINLINE bool TSimpEdge<T>::TestFlags( uint32 f ) const`

### `Source/Developer/MeshSimplifier/Private/Quadric.h` (Private)


#### struct `TVec3`  
`template< typename T > struct TVec3`  
_L51-151_
- L53 _public member_ `T x;`
- L54 _public member_ `T y;`
- L55 _public member_ `T z;`
- L57 _public prototype_ `TVec3() = default;`
- L58 _public function_ `TVec3( T Scalar ) : x( Scalar ), y( Scalar ), z( Scalar )`
- L62 _public function_ `TVec3( T InX, T InY, T InZ ) : x( InX ), y( InY ), z( InZ )`
- L66 _public function_ `TVec3( const FVector3f& v ) : x( v.X ), y( v.Y ), z( v.Z )`
- L70 _public function_ `TVec3 operator-() const`
- L75 _public function_ `TVec3 operator*( T Scalar ) const`
- L83 _public function_ `TVec3 operator+( const TVec3& v ) const`
- L91 _public function_ `TVec3 operator-( const TVec3& v ) const`
- L99 _public function_ `TVec3& operator+=( const TVec3& v )`
- L107 _public function_ `T operator|( const TVec3& v ) const`
- L136 _public function_ `TVec3 operator^( const TVec3& v ) const`

#### class `FEdgeQuadric`  
`class FEdgeQuadric`  
_L163-183_
- L166 _public function_ `FEdgeQuadric()`
- L167 _public prototype_ `FEdgeQuadric( const QVec3 p0, const QVec3 p1, const float Weight );`
- L168 _public prototype_ `FEdgeQuadric( const QVec3 p0, const QVec3 p1, const QVec3 FaceNormal, const float Weight );`
- L170 _public prototype_ `void Zero();`
- L172 _public member_ `QScalar nxx;`
- L173 _public member_ `QScalar nyy;`
- L174 _public member_ `QScalar nzz;`
- L176 _public member_ `QScalar nxy;`
- L177 _public member_ `QScalar nxz;`
- L178 _public member_ `QScalar nyz;`
- L180 _public member_ `QVec3 n;`
- L182 _public member_ `QScalar a;`
- L185 _function_ `inline FEdgeQuadric::FEdgeQuadric( const QVec3 p0, const QVec3 p1, const QVec3 FaceNormal, const float Weight )`
- L215 _function_ `inline void FEdgeQuadric::Zero()`

#### class `FQuadric`  
`class FQuadric`  
_L232-264_
- desc: Error quadric for position only
- L235 _public function_ `FQuadric()`
- L237 _public prototype_ `FQuadric( const QVec3 p );` — Distance from point
- L239 _public prototype_ `FQuadric( const QVec3 n, const QVec3 p );` — Distance from line, n must be normalized
- L241 _public prototype_ `FQuadric( const QVec3 p0, const QVec3 p1, const QVec3 p2 );` — Distance from triangle
- L243 _public prototype_ `void Zero();`
- L245 _public prototype_ `FQuadric& operator+=( const FQuadric& q );`
- L247 _public prototype_ `void Add( const FEdgeQuadric& q, const FVector3f& Point );`
- L250 _public prototype_ `float Evaluate( const FVector3f& p ) const;` — Evaluate error at point
- L252 _public member_ `QScalar nxx;`
- L253 _public member_ `QScalar nyy;`
- L254 _public member_ `QScalar nzz;`
- L256 _public member_ `QScalar nxy;`
- L257 _public member_ `QScalar nxz;`
- L258 _public member_ `QScalar nyz;`
- L260 _public member_ `QVec3 dn;`
- L261 _public member_ `QScalar d2;`
- L263 _public member_ `QScalar a;`
- L266 _function_ `inline void FQuadric::Zero()`
- L282 _function_ `inline FQuadric& FQuadric::operator+=( const FQuadric& q )`
- L300 _function_ `inline void FQuadric::Add( const FEdgeQuadric& RESTRICT EdgeQuadric, const FVector3f& Point )`

#### class `FQuadricAttr`  
`class FQuadricAttr : public FQuadric`  
_L326-352_
- inherits: `FQuadric`
- desc: Error quadric including attributes Attributes are assumed to be allocated immediately after this struct! See TQuadricAttr below for expected layout for a static case.
- L329 _public function_ `FQuadricAttr()`
- L330 _public prototype_ `FQuadricAttr( const QVec3 p0, const QVec3 p1, const QVec3 p2, const float* a0, const float* a1, const float* a2, const float* AttributeWeights, uint32 NumAttributes );`
- L336 _public prototype_ `void Rebase( const FVector3f& Point, const float* Attributes, const float* AttributeWeights, uint32 NumAttributes );`
- L337 _public prototype_ `void Add( const FQuadricAttr& q, const FVector3f& Point, const float* Attribute, const float* AttributeWeights, uint32 NumAttributes );`
- L338 _public prototype_ `void Add( const FQuadricAttr& q, uint32 NumAttributes );`
- L340 _public prototype_ `void Zero( uint32 NumAttributes );`
- L343 _public prototype_ `float Evaluate( const FVector3f& Point, const float* Attributes, const float* AttributeWeights, uint32 NumAttributes ) const;` — Evaluate error at point with attributes and weights
- L346 _public prototype_ `float CalcAttributesAndEvaluate( const FVector3f& Point, float* Attributes, const float* AttributeWeights, uint32 NumAttributes ) const;` — Calculate attributes for point and evaluate error
- L349 _public member_ `QVec3 nv;`
- L350 _public member_ `QScalar dv;`

#### class `TQuadricAttr`  
`template< uint32 NumAttributes > class TQuadricAttr : public FQuadricAttr`  
_L358-384_
- inherits: `FQuadricAttr`
- desc: Error quadric including attributes Static NumAttributes version of FQuadricAttr.
- L361 _public function_ `TQuadricAttr()`
- L362 _public prototype_ `TQuadricAttr( const QVec3 p0, const QVec3 p1, const QVec3 p2, const float* a0, const float* a1, const float* a2, const float* AttributeWeights );`
- L368 _public prototype_ `void Rebase( const FVector3f& Point, const float* Attributes, const float* AttributeWeights );`
- L369 _public prototype_ `void Add( const TQuadricAttr< NumAttributes >& q, const FVector3f& Point, const float* Attribute, const float* AttributeWeights );`
- L371 _public prototype_ `void Zero();`
- L373 _public prototype_ `TQuadricAttr< NumAttributes >& operator+=( const FQuadric& q );`
- L374 _public prototype_ `TQuadricAttr< NumAttributes >& operator+=( const TQuadricAttr< NumAttributes >& q );`
- L377 _public prototype_ `float Evaluate( const FVector3f& Point, const float* Attributes, const float* AttributeWeights ) const;` — Evaluate error at point with attributes and weights
- L380 _public prototype_ `float CalcAttributesAndEvaluate( const FVector3f& Point, float* Attributes, const float* AttributeWeights ) const;` — Calculate attributes for point and evaluate error
- L382 _public member_ `QScalar g[ NumAttributes ][3];`
- L383 _public member_ `QScalar d[ NumAttributes ];`
- L387 _function_ `template< uint32 NumAttributes > inline TQuadricAttr< NumAttributes >::TQuadricAttr( const QVec3 p0, const QVec3 p1, const QVec3 p2, const float* a0, const float* a1, const float* a2, const float* AttributeWeights ) : FQuadricAttr( p0, p1, p2, a0, a1, a2, AttributeWeights, NumAttributes )`
- L399 _function_ `template< uint32 NumAttributes > inline void TQuadricAttr< NumAttributes >::Rebase( const FVector3f& Point, const float* Attribute, const float* AttributeWeights )`
- L407 _function_ `template< uint32 NumAttributes > inline void TQuadricAttr< NumAttributes >::Zero()`
- L413 _function_ `template< uint32 NumAttributes > inline TQuadricAttr< NumAttributes >& TQuadricAttr< NumAttributes >::operator+=( const TQuadricAttr< NumAttributes >& RESTRICT q )`
- L445 _function_ `template< uint32 NumAttributes > inline float TQuadricAttr< NumAttributes >::CalcAttributesAndEvaluate( const FVector3f& Point, float* RESTRICT Attributes, const float* RESTRICT AttributeWeights ) const`

#### class `FQuadricAttrOptimizer`  
`class FQuadricAttrOptimizer`  
_L451-490_
- L454 _public prototype_ `FQuadricAttrOptimizer();`
- L456 _public prototype_ `void AddQuadric( const FQuadric& q );`
- L457 _public prototype_ `void AddQuadric( const FQuadricAttr& q, uint32 NumAttributes );`
- L460 _public prototype_ `bool Optimize( FVector3f& Position ) const;` — Find optimal point for minimal error
- L461 _public prototype_ `bool OptimizeVolume( FVector3f& Position ) const;`
- L462 _public prototype_ `bool OptimizeLinear( const FVector3f& Position0, const FVector3f& Position1, FVector3f& Position ) const;`
- L465 _private member_ `QScalar nxx;`
- L466 _private member_ `QScalar nyy;`
- L467 _private member_ `QScalar nzz;`
- L469 _private member_ `QScalar nxy;`
- L470 _private member_ `QScalar nxz;`
- L471 _private member_ `QScalar nyz;`
- L473 _private member_ `QVec3 dn;`
- L475 _private member_ `QScalar a;`
- L478 _private member_ `QVec3 nv;`
- L479 _private member_ `QScalar dv;`
- L482 _private member_ `QScalar BBtxx;`
- L483 _private member_ `QScalar BBtyy;`
- L484 _private member_ `QScalar BBtzz;`
- L485 _private member_ `QScalar BBtxy;`
- L486 _private member_ `QScalar BBtxz;`
- L487 _private member_ `QScalar BBtyz;`
- L489 _private member_ `QVec3 Bd;`
- L492 _function_ `inline FQuadricAttrOptimizer::FQuadricAttrOptimizer()`
- L521 _function_ `inline void FQuadricAttrOptimizer::AddQuadric( const FQuadric& RESTRICT q )`
- L536 _function_ `inline void FQuadricAttrOptimizer::AddQuadric( const FQuadricAttr& RESTRICT q, uint32 NumAttributes )`

#### Free symbols / members of external scopes

- L17 _macro_ `#define WEIGHT_BY_AREA 1`
- L18 _macro_ `#define VOLUME_CONSTRAINT 1`
- L19 _macro_ `#define USE_FMA 0`
- L20 _macro_ `#define PSEUDO_INVERSE 0`
- L25 _function_ `template< typename T > inline T DifferenceOfProducts( T a, T b, T c, T d )` — Kahan's algorithm
- L35 _function_ `template< typename T > T TwoSumError( T a, T b )` — Knuth 1974
- L43 _function_ `template< typename T > T TwoProdError( T a, T b )`
- L154 _function_ `template< typename T > FORCEINLINE TVec3<T> operator*( T Scalar, const TVec3<T>& v )`
- L159 _typedef_ `using QScalar = double;`
- L160 _typedef_ `using QVec3 = TVec3< QScalar >;`

### `Source/Developer/MeshSimplifier/Private/UnrolledLinkList.h` (Private)


#### class `TUnrolledLinkList`  
`template< typename T, uint32 blockSize > class TUnrolledLinkList`  
_L19-90_
- L73 _public prototype_ `TUnrolledLinkList();`
- L75 _public function_ `uint32 Num() const`
- L77 _public prototype_ `void Add( const T& Element );`
- L78 _public prototype_ `void Remove( const T& Element );`
- L79 _public prototype_ `void Remove( const TIterator& i );`
- L81 _public prototype_ `void Clear();`
- L83 _public function_ `TIterator Begin()`
- L84 _public function_ `TIterator End()`
- L87 _protected member_ `TNode head;`
- L88 _protected member_ `TNode* freeNode;` — first node that has a free element
- L89 _protected member_ `uint32 num;`
- L93 _function_ `template< typename T, uint32 blockSize > FORCEINLINE TUnrolledLinkList<T, blockSize>::TUnrolledLinkList() : freeNode( &head ) , num(0)`
- L101 _function_ `template< typename T, uint32 blockSize > FORCEINLINE void TUnrolledLinkList<T, blockSize>::Add( const T& Element )`
- L121 _function_ `template< typename T, uint32 blockSize > FORCEINLINE void TUnrolledLinkList<T, blockSize>::Remove( const T& Element )`
- L134 _function_ `template< typename T, uint32 blockSize > FORCEINLINE void TUnrolledLinkList<T, blockSize>::Remove( const TIterator& i )`
- L158 _function_ `template< typename T, uint32 blockSize > FORCEINLINE void TUnrolledLinkList<T, blockSize>::Clear()`

#### class `TUnrolledLinkList::TNode`  
`class TNode`  
_L21-36_
- L25 _public function_ `TNode() : next(NULL) , prev(NULL)`
- L30 _public function_ `~TNode()`
- L33 _private member_ `T block[blockSize];`
- L34 _private member_ `TNode* next;`
- L35 _private member_ `TNode* prev;`

#### class `TUnrolledLinkList::TIterator`  
`class TIterator`  
_L39-70_
- L43 _public function_ `TIterator() : node(NULL) , index(0)`
- L48 _public function_ `T& operator*()`
- L49 _public function_ `T* operator->()`
- L51 _public function_ `bool operator==( const TIterator& i ) const`
- L52 _public function_ `bool operator!=( const TIterator& i ) const`
- L54 _public function_ `TIterator& operator++()`
- L63 _private function_ `TIterator( TNode* n, uint32 i ) : node(n) , index(i)`
- L68 _private member_ `TNode* node;`
- L69 _private member_ `uint32 index;`
