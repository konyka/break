# Runtime / MeshUtilitiesCommon

- module root: `Source/Runtime/MeshUtilitiesCommon`
- headers: 5; symbols: 187
- symbol kinds: class=3, enum=2, enumerator=14, function=31, macro=1, member=67, namespace=1, prototype=57, struct=11
- PrivateDependencyModuleNames: Core

### `Source/Runtime/MeshUtilitiesCommon/Public/Allocator2D.h` (Public)


#### class `FAllocator2D`  
`class FAllocator2D`  
_L19-174_
- L64 _public prototype_ `FAllocator2D( EMode Mode, uint32 Width, uint32 Height, ELightmapUVVersion LayoutVersion );`
- L67 _public prototype_ `void Clear();` — Must clear before using
- L69 _public prototype_ `bool Find( FRect& Rect );`
- L70 _public prototype_ `bool Test( FRect Rect );`
- L71 _public prototype_ `void Alloc( FRect Rect );`
- L73 _public prototype_ `bool FindBitByBit( FRect& Rect, const FAllocator2D& Other );`
- L74 _public prototype_ `bool FindWithSegments( FRect& Rect, const FAllocator2D& Other, TFunctionRef<bool (const FAllocator2D::FRect&)> IsBestRect ) const;`
- L75 _public prototype_ `bool Test( FRect Rect, const FAllocator2D& Other );`
- L76 _public prototype_ `void Alloc( FRect Rect, const FAllocator2D& Other );`
- L78 _public prototype_ `uint64 GetBit( uint32 x, uint32 y ) const;`
- L79 _public prototype_ `void SetBit( uint32 x, uint32 y );`
- L80 _public prototype_ `void ClearBit( uint32 x, uint32 y );`
- L82 _public prototype_ `void CreateUsedSegments();`
- L83 _public prototype_ `void MergeRun( FRun& Run, const FRun& OtherRun, uint32 RectOffset, uint32 RectLength, uint32 PrimaryResolution , uint32 PerpendicularResolution );`
- L84 _public prototype_ `void MergeSegments( const FRect& Rect, const FAllocator2D& Other );`
- L86 _public prototype_ `void FlipX( const FRect& Rect );`
- L87 _public prototype_ `void FlipY( const FRect& Rect );`
- L89 _public prototype_ `uint32 GetUsedTexels() const;`
- L91 _public prototype_ `void CopyRuns( TArray<FRun>& Runs, const TArray<FRun>& OtherRuns, int32 MaxSize );`
- L94 _public prototype_ `FAllocator2D(const FAllocator2D& Other) = default;` — Take control of the copy assignment to reduce the amount of data movement to the strict minimum
- L95 _public prototype_ `FAllocator2D& operator = (const FAllocator2D& Other);`
- L98 _public prototype_ `FString ToString() const;` — Allow to visualize the content in ascii for debugging purpose. (i.e Watch or Immediate window).
- L101 _public prototype_ `FMD5Hash GetRasterMD5() const;` — Get the MD5 hash of the rasterized content
- L103 _public function_ `uint32 GetRasterWidth() const`
- L104 _public function_ `uint32 GetRasterHeight() const`
- L106 _public prototype_ `void ResetStats();`
- L107 _public prototype_ `void PublishStats( int32 ChartIndex, int32 Orientation, bool bFound, const FRect& Rect, const FRect& BestRect, const FMD5Hash& ChartMD5, TFunctionRef<bool (const FAllocator2D::FRect&)> IsBestRect );`
- L110 _protected prototype_ `bool TestOneRun( const FRun& Run, const FRun& OtherRun, uint32 RectOffset, uint32 RectLength, uint32 PrimaryResolution, uint32& OutFailedLength ) const;`
- L111 _protected prototype_ `bool TestAllRows( const FRect& Rect, const FAllocator2D& Other, uint32& FailedLength ) const;`
- L112 _protected prototype_ `bool TestAllColumns( const FRect& Rect, const FAllocator2D& Other, uint32& FailedLength ) const;`
- L113 _protected prototype_ `void InitRuns( TArray<FRun>& Runs, uint32 PrimaryResolution, uint32 PerpendicularRasterSize);`
- L114 _protected prototype_ `void InitSegments();`
- L115 _protected prototype_ `void AddUsedSegment( FRun& Run, uint32 StartPos, uint32 Length );`
- L118 _protected member_ `const EMode Mode;` — Enforce that those cannot be changed in flight
- L119 _protected member_ `const uint32 Width;`
- L120 _protected member_ `const uint32 Height;`
- L121 _protected member_ `const uint32 Pitch;`
- L122 _protected member_ `const ELightmapUVVersion LayoutVersion;`
- L124 _protected member_ `uint32 RasterWidth;`
- L125 _protected member_ `uint32 RasterHeight;`
- L126 _protected member_ `TArray< FRun > Rows;` — Represent rows in the grid
- L127 _protected member_ `TArray< FRun > Columns;` — Represent columns in the grid (used when version >= Segments2D).
- L128 _protected member_ `TArray< uint64 > Bits;`
- L131 _protected member_ `TArray< uint16 > SortedRowsIndex;` — Index inside rows that will be sorted by rows with longest used segment first
- L133 _protected member_ `TArray< uint16 > SortedColumnsIndex;` — Index inside columns that will be sorted by columns with longest used segment first
- L173 _private member_ `mutable FStats Stats;`
- L177 _function_ `inline uint64 FAllocator2D::GetBit( uint32 x, uint32 y ) const` — Returns non-zero if set
- L182 _function_ `inline void FAllocator2D::SetBit( uint32 x, uint32 y )`
- L198 _function_ `inline void FAllocator2D::ClearBit( uint32 x, uint32 y )`
- L203 _function_ `inline bool FAllocator2D::Test( FRect Rect )`
- L219 _function_ `inline bool FAllocator2D::Test( FRect Rect, const FAllocator2D& Other )`

#### enum `FAllocator2D::EMode`  
`enum class EMode`  
_L22-30_
- L26 _public enumerator_ `FreeSegments` — In this mode, segments represents free space Used for the layout merging usedsegments
- L29 _public enumerator_ `UsedSegments` — In this mode, segments represents used space Used for the rasterization of charts.

#### struct `FAllocator2D::FRect`  
`struct FRect`  
_L32-38_
- L34 _public member_ `uint32 X;`
- L35 _public member_ `uint32 Y;`
- L36 _public member_ `uint32 W;`
- L37 _public member_ `uint32 H;`

#### struct `FAllocator2D::FSegment`  
`struct FSegment`  
_L40-46_
- L42 _public member_ `uint32 StartPos;`
- L43 _public member_ `uint32 Length;`
- L45 _public function_ `bool operator<( const FSegment& Other ) const`

#### struct `FAllocator2D::FRun`  
`struct FRun`  
_L48-61_
- L50 _public member_ `uint32 LongestSegment;`
- L51 _public member_ `TArray< FSegment > Segments;`
- L60 _public member_ `TArray< uint16 > FreeSegmentsLookup;` — Contains mapping from pixel position to first segment index in search range. Only computed when we're in FreeSegments mode to help TestOneRun find the proper segment in O(c) at the expense of a likely cache miss. We'll use a threshold to use this method when the number of iterations saved is worth the cache miss. Obviously, using a uint16 here will reduce cache misses but impose an hopefully enough limitation of texture size 65536x65536 (4GB).

#### struct `FAllocator2D::FStats`  
`struct FStats`  
_L137-171_
- desc: Store iteration stats of the principal algorithms.
- L155 _public member_ `FStat FindWithSegmentsIterationsY;`
- L156 _public member_ `FStat FindWithSegmentsIterationsX;`
- L157 _public member_ `FStat FindWithSegmentsMovedPastPreviousBest;`
- L158 _public member_ `FStat TestAllRowsIterationsY;`
- L159 _public member_ `FStat FreeSegmentLookupCount;`
- L160 _public member_ `FStat FreeSegmentRangeIterations;`
- L161 _public member_ `FStat FreeSegmentFutureIterations;`
- L162 _public member_ `FStat FreeSegmentFutureHit;`
- L163 _public member_ `FStat FreeSegmentFutureHitStep;`
- L164 _public member_ `FStat FreeSegmentFutureMiss;`
- L165 _public member_ `FStat FreeSegmentFutureMissStep;`
- L167 _public function_ `void Reset()`

#### struct `FAllocator2D::FStats::FStat`  
`struct FStat`  
_L139-153_
- L142 _public function_ `inline void operator++(int)`
- L143 _public function_ `inline void operator+=(uint64 InValue)`
- L144 _public function_ `inline uint64 GetValue() const`
- L146 _private member_ `uint64 Value = 0;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define DEBUG_LAYOUT_STATS 0`

### `Source/Runtime/MeshUtilitiesCommon/Public/DisjointSet.h` (Public)


#### class `FDisjointSet`  
`class FDisjointSet`  
_L7-25_
- L10 _public function_ `FDisjointSet()`
- L11 _public prototype_ `FDisjointSet( const uint32 Size );`
- L13 _public prototype_ `void Init( uint32 Size );`
- L14 _public prototype_ `void Reset();`
- L15 _public prototype_ `void AddDefaulted( uint32 Num = 1 );`
- L17 _public prototype_ `void Union( uint32 x, uint32 y );`
- L18 _public prototype_ `void UnionSequential( uint32 x, uint32 y );`
- L19 _public prototype_ `uint32 Find( uint32 i );`
- L21 _public function_ `uint32 operator[]( uint32 i ) const`
- L24 _private member_ `TArray< uint32 > Parents;`
- L27 _function_ `inline FDisjointSet::FDisjointSet( const uint32 Size )`
- L32 _function_ `inline void FDisjointSet::Init( uint32 Size )`
- L41 _function_ `inline void FDisjointSet::Reset()`
- L46 _function_ `inline void FDisjointSet::AddDefaulted( uint32 Num )`
- L57 _function_ `inline void FDisjointSet::Union( uint32 x, uint32 y )` — Union with splicing
- L90 _function_ `inline void FDisjointSet::UnionSequential( uint32 x, uint32 y )` — Optimized version of Union when iterating for( x : 0 to N ) unioning x with lower indexes. Neither x nor y can have already been unioned with an index > x.
- L110 _function_ `inline uint32 FDisjointSet::Find( uint32 i )` — Find with path compression

### `Source/Runtime/MeshUtilitiesCommon/Public/LayoutUV.h` (Public)


#### struct `FMeshChart`  
`struct FMeshChart`  
_L14-36_
- L16 _public member_ `uint32 FirstTri;`
- L17 _public member_ `uint32 LastTri;`
- L19 _public member_ `FVector2f MinUV;`
- L20 _public member_ `FVector2f MaxUV;`
- L22 _public member_ `float UVArea;`
- L23 _public member_ `FVector2f UVScale;`
- L24 _public member_ `FVector2f WorldScale;`
- L26 _public member_ `float UVLengthSum;`
- L27 _public member_ `float WorldLengthSum;`
- L29 _public member_ `FVector2f PackingScaleU;`
- L30 _public member_ `FVector2f PackingScaleV;`
- L31 _public member_ `FVector2f PackingBias;`
- L33 _public member_ `int32 Join[4];`
- L35 _public member_ `int32 Id;` — Store a unique id so that we can come back to the initial Charts ordering when necessary

#### class `FLayoutUV`  
`class FLayoutUV`  
_L40-87_
- L64 _public prototype_ `FLayoutUV( IMeshView& InMeshView );`
- L65 _public function_ `void SetVersion( ELightmapUVVersion Version )`
- L66 _public prototype_ `int32 FindCharts( const FOverlappingCorners& OverlappingCorners );`
- L67 _public prototype_ `bool FindBestPacking( uint32 InTextureResolution );`
- L68 _public prototype_ `void CommitPackedUVs();`
- L70 _public prototype_ `static void LogStats();`
- L71 _public prototype_ `static void ResetStats();`
- L73 _private member_ `IMeshView& MeshView;`
- L74 _private member_ `ELightmapUVVersion LayoutVersion;`
- L76 _private member_ `TArray< FVector2f > MeshTexCoords;`
- L77 _private member_ `TArray< uint32 > MeshSortedTris;`
- L78 _private member_ `TArray< FMeshChart > MeshCharts;`
- L79 _private member_ `uint32 PackedTextureResolution;`
- L84 _private member_ `static TAtomic<uint64> FindBestPackingCount;`
- L85 _private member_ `static TAtomic<uint64> FindBestPackingCycles;`
- L86 _private member_ `static TAtomic<uint64> FindBestPackingEfficiency;`

#### struct `FLayoutUV::IMeshView`  
`struct IMeshView`  
_L51-62_
- desc: Abstract triangle mesh view interface that may be used by any module without introducing a dependency on a concrete mesh type (and thus potentially circular module references). This abstraction results in a performance penalty due to virtual dispatch, however it is expected to be insignificant compared to the rest of work done by FLayoutUV and cache misses due to indexed vertex data access.
- L53 _public prototype_ `virtual ~IMeshView() = default;`
- L55 _public prototype_ `virtual uint32 GetNumIndices() const = 0;`
- L56 _public prototype_ `virtual FVector3f GetPosition(uint32 Index) const = 0;`
- L57 _public prototype_ `virtual FVector3f GetNormal(uint32 Index) const = 0;`
- L58 _public prototype_ `virtual FVector2f GetInputTexcoord(uint32 Index) const = 0;`
- L60 _public prototype_ `virtual void InitOutputTexcoords(uint32 Num) = 0;`
- L61 _public prototype_ `virtual void SetOutputTexcoord(uint32 Index, const FVector2f& Value) = 0;`

### `Source/Runtime/MeshUtilitiesCommon/Public/MeshUtilitiesCommon.h` (Public)


#### enum `ELightmapUVVersion`  
`enum class ELightmapUVVersion : int32`  
_L7-21_
- L9 _public enumerator_ `BitByBit = 0`
- L10 _public enumerator_ `Segments = 1`
- L11 _public enumerator_ `SmallChartPacking = 2`
- L12 _public enumerator_ `ScaleChartsOrderingFix = 3`
- L13 _public enumerator_ `ChartJoiningLFix = 4`
- L14 _public enumerator_ `Allocator2DFlipFix = 5`
- L15 _public enumerator_ `ConsiderLightmapPadding = 6`
- L16 _public enumerator_ `ForceLightmapPadding = 7`
- L17 _public enumerator_ `Segments2D = 8`
- L18 _public enumerator_ `OptimalSurfaceArea = 9`
- L19 _public enumerator_ `ScaleByEdgesLength = 10`
- L20 _public enumerator_ `Latest = ScaleByEdgesLength`

#### struct `FBoneVertInfo`  
`struct FBoneVertInfo`  
_L27-32_
- desc: Contains the vertices that are most dominated by that bone. Vertices are in Bone space. Not used at runtime, but useful for fitting physics assets etc.
- L30 _public member_ `TArray<FVector3f> Positions;` — Invariant: Arrays should be same length!
- L31 _public member_ `TArray<FVector3f> Normals;`

#### struct `FIndexAndZ`  
`struct FIndexAndZ`  
_L35-49_
- desc: Helper struct for building acceleration structures.
- L37 _public member_ `float Z;`
- L38 _public member_ `int32 Index;`
- L41 _public function_ `FIndexAndZ()` — Default constructor.
- L44 _public function_ `FIndexAndZ(int32 InIndex, FVector3f V)` — Initialization constructor.

#### struct `FCompareIndexAndZ`  
`struct FCompareIndexAndZ`  
_L52-55_
- desc: Sorting function for vertex Z/index pairs.
- L54 _public function_ `inline bool operator()(FIndexAndZ const& A, FIndexAndZ const& B) const`

#### Free symbols / members of external scopes

- L60 _function_ `inline bool PointsEqual(const FVector3f& V1, const FVector3f& V2, float ComparisonThreshold)` — Returns true if the specified points are about equal
- L71 _namespace_ `namespace TriangleUtilities`
- L76 _function_ `static float ComputeTriangleArea(const FVector3f& PointA, const FVector3f& PointB, const FVector3f& PointC)` (scope `TriangleUtilities`) — This function compute the area of a triangle, it will return zero if the triangle is degenerated
- L84 _function_ `static float ComputeTriangleCornerAngle(const FVector3f& PointA, const FVector3f& PointB, const FVector3f& PointC)` (scope `TriangleUtilities`) — This function compute the angle of a triangle corner, it will return zero if the triangle is degenerated
- L102 _function_ `inline FMatrix44f GetTangentBasisFrisvad(FVector3f TangentZ)` — [Frisvad 2012, "Building an Orthonormal Basis from a 3D Unit Vector Without Normalization"]

### `Source/Runtime/MeshUtilitiesCommon/Public/OverlappingCorners.h` (Public)


#### struct `FOverlappingCorners`  
`struct FOverlappingCorners`  
_L15-50_
- desc: Container to hold overlapping corners. For a vertex, lists all the overlapping vertices
- L17 _public function_ `FOverlappingCorners()`
- L19 _public prototype_ `FOverlappingCorners(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, float ComparisonThreshold);`
- L20 _public prototype_ `FOverlappingCorners(const FLayoutUV::IMeshView& MeshView, float ComparisonThreshold);`
- L23 _public prototype_ `void Init(int32 NumIndices);` — Resets, pre-allocates memory, marks all indices as not overlapping in preperation for calls to Add()
- L26 _public prototype_ `void Add(int32 Key, int32 Value);` — Add overlapping indices pair
- L29 _public prototype_ `void FinishAdding();` — Sorts arrays, converts sets to arrays for sorting and to allow simple iterating code, prevents additional adding
- L32 _public prototype_ `uint32 GetAllocatedSize(void) const;` — Estimate memory allocated
- L37 _public function_ `const TArray<int32>& FindIfOverlapping(int32 Key) const` — @return array of sorted overlapping indices including input 'Key', empty array for indices that have no overlaps.
- L45 _private member_ `TArray<int32> IndexBelongsTo;`
- L46 _private member_ `TArray< TArray<int32> > Arrays;`
- L47 _private member_ `TArray< TSet<int32> > Sets;`
- L48 _private member_ `TArray<int32> EmptyArray;`
- L49 _private member_ `bool bFinishedAdding = false;`
