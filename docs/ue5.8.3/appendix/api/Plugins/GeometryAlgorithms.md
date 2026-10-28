# Plugins / GeometryAlgorithms

- module root: `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms`
- headers: 20; symbols: 405
- symbol kinds: class=9, enum=8, enumerator=31, function=71, macro=1, member=127, namespace=40, prototype=70, struct=14, typedef=31, variable=3
- PrivateDependencyModuleNames: Eigen
- PublicDependencyModuleNames: Core, GeometryCore

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Private/Curve/ClipperUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Geometry`)
- L15 _typedef_ `using IntegralType = int64;` (scope `UE::Geometry::Private`) — Matches what's in the clipper lib, precision can change per platform and int64 doesn't reflect this
- L17 _variable_ `static constexpr IntegralType IntMin = 0;` (scope `UE::Geometry::Private`)
- L18 _variable_ `static constexpr IntegralType IntMax = 9007199254740991;` (scope `UE::Geometry::Private`) — fit to double bits, product of 2^53 - 1
- L19 _variable_ `static constexpr IntegralType IntRange = IntMax - IntMin;` (scope `UE::Geometry::Private`)
- L22 _prototype_ `template <typename RealType, typename OutputType> static Clipper2Lib::Point<OutputType> PackVector(const TVector2<RealType> InVector, const TVector2<RealType>& InMin, const RealType& InRange);` (scope `UE::Geometry::Private`)
- L25 _prototype_ `template <typename InputType, typename RealType> static TVector2<RealType> UnpackVector(const Clipper2Lib::Point<InputType>& InPoint, const TVector2<RealType>& InMin, const RealType& InRange);` (scope `UE::Geometry::Private`)
- L28 _prototype_ `template <typename RealType, typename OutputType> static Clipper2Lib::Path<OutputType> ConvertPolygonToPath(const TPolygon2<RealType>& InPolygon, const TVector2<RealType>& InMin = {}, const RealType& InRange = {});` (scope `UE::Geometry::Private`)
- L31 _prototype_ `template <typename RealType, typename OutputType> static Clipper2Lib::Path<OutputType> ConvertPolygonToPath(const TArrayView<UE::Math::TVector2<RealType>>& InPolygon, const TVector2<RealType>& InMin = {}, const RealType& InRange = {});` (scope `UE::Geometry::Private`)
- L34 _prototype_ `template <typename RealType, typename OutputType> static Clipper2Lib::Paths<OutputType> ConvertPolygonsToPaths(const TArray<TArrayView<UE::Math::TVector2<RealType>>>& InPolygons, const TVector2<RealType>& InMin = {}, const RealType& InRange = {});` (scope `UE::Geometry::Private`)
- L37 _prototype_ `template <typename RealType, typename OutputType> static Clipper2Lib::Paths<OutputType> ConvertGeneralizedPolygonToPath(const UE::Geometry::TGeneralPolygon2<RealType>& InPolygon, const TVector2<RealType>& InMin = {}, const RealType& InRange = {});` (scope `UE::Geometry::Private`)
- L40 _prototype_ `template <typename RealType, typename OutputType> static void AddGeneralizedPolygonToPaths(Clipper2Lib::Paths<OutputType>& OutPaths, const UE::Geometry::TGeneralPolygon2<RealType>& InPolygon, const TVector2<RealType>& InMin = {}, const RealType& InRange = {});` (scope `UE::Geometry::Private`)
- L43 _prototype_ `template <typename InputType, typename RealType> static TPolygon2<RealType> ConvertPathToPolygon(const Clipper2Lib::Path<InputType>& InPath, const TVector2<RealType>& InMin = {}, const RealType& InRange = {});` (scope `UE::Geometry::Private`)
- L46 _prototype_ `template <typename InputType, typename RealType> static void ConvertPolyTreeToPolygons(const Clipper2Lib::PolyPath<InputType>* InPaths, TArray<UE::Geometry::TGeneralPolygon2<RealType>>& OutPolygons, const TVector2<RealType>& InMin = {} , const RealType& InRange = {}, int ParentPolygonIdx = -1);` (scope `UE::Geometry::Private`)
- L49 _prototype_ `template<typename InputType, typename RealType> TArray<TVector2<RealType>> ConvertPathToUEPath(const Clipper2Lib::Path<InputType>& InPath, const TVector2<RealType>& InMin, const RealType& InRange);` (scope `UE::Geometry::Private`)
- L52 _prototype_ `template<typename InputType, typename RealType> TArray<TArray<TVector2<RealType>>> ConvertPathsToUEPaths(const Clipper2Lib::Paths<InputType>& InPaths, const TVector2<RealType>& InMin, const RealType& InRange);` (scope `UE::Geometry::Private`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Private/Curve/ClipperUtils.inl` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Geometry` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Geometry`)
- L10 _function_ `template <typename RealType, typename OutputType> Clipper2Lib::Point<OutputType> PackVector(const TVector2<RealType> InVector, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L23 _function_ `template <typename InputType, typename RealType> TVector2<RealType> UnpackVector(const Clipper2Lib::Point<InputType>& InPoint, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L37 _function_ `template <typename RealType, typename OutputType> static Clipper2Lib::Path<OutputType> ConvertPolygonToPath(const TPolygon2<RealType>& InPolygon, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L57 _function_ `template <typename RealType, typename OutputType> static Clipper2Lib::Path<OutputType> ConvertPolygonToPath(const TArrayView<UE::Math::TVector2<RealType>>& InPolygon, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L77 _function_ `template <typename RealType, typename OutputType> Clipper2Lib::Paths<OutputType> ConvertPolygonsToPaths(const TArray<TArrayView<UE::Math::TVector2<RealType>>>& InPolygons, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L89 _function_ `template <typename RealType, typename OutputType> void AddGeneralizedPolygonToPaths(Clipper2Lib::Paths<OutputType>& OutPaths, const UE::Geometry::TGeneralPolygon2<RealType>& InPolygon, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L99 _function_ `template <typename RealType, typename OutputType> Clipper2Lib::Paths<OutputType> ConvertGeneralizedPolygonToPath(const UE::Geometry::TGeneralPolygon2<RealType>& InPolygon, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L107 _function_ `template <typename InputType, typename RealType> TPolygon2<RealType> ConvertPathToPolygon(const Clipper2Lib::Path<InputType>& InPath, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L127 _function_ `template <typename InputType, typename RealType> void ConvertPolyTreeToPolygons(const Clipper2Lib::PolyPath<InputType>* InPaths, TArray<UE::Geometry::TGeneralPolygon2<RealType>>& OutPolygons, const TVector2<RealType>& InMin, const RealType& InRange, int ParentPolygonIdx)` (scope `UE::Geometry::Private`)
- L156 _function_ `template<typename InputType, typename RealType> TArray<TVector2<RealType>> ConvertPathToUEPath(const Clipper2Lib::Path<InputType>& InPath, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)
- L176 _function_ `template<typename InputType, typename RealType> TArray<TArray<TVector2<RealType>>> ConvertPathsToUEPaths(const Clipper2Lib::Paths<InputType>& InPaths, const TVector2<RealType>& InMin, const RealType& InRange)` (scope `UE::Geometry::Private`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Private/GteUtil.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)
- L22 _function_ `template<typename Real> gte::Vector2<Real> Convert(const UE::Math::TVector2<Real>& Vec)` (scope `UE::Geometry`)
- L28 _function_ `template<typename Real> UE::Math::TVector2<Real> Convert(const gte::Vector2<Real>& Vec)` (scope `UE::Geometry`)
- L34 _function_ `template<typename Real> gte::Vector3<Real> Convert(const UE::Math::TVector<Real>& Vec)` (scope `UE::Geometry`)
- L40 _function_ `template<typename Real> UE::Math::TVector<Real> Convert(const gte::Vector3<Real>& Vec)` (scope `UE::Geometry`)
- L46 _function_ `template<typename Real> gte::Line3<Real> Convert(const TLine3<Real>& Line)` (scope `UE::Geometry`)
- L52 _function_ `template<typename Real> gte::Circle3<Real> Convert(const TCircle3<Real>& Circle)` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/Arrangement2d.h` (Public)


#### struct `UE::Geometry::FArrangement2d`  
`struct FArrangement2d`  
_L34-577_
- desc: Arrangement2d constructs a planar arrangement of a set of 2D line segments. When a segment is inserted, existing edges are split, and the inserted segment becomes multiple graph edges. So, the resulting FDynamicGraph2d should not have any edges that intersect. Calculations are performed in double-precision, so there is no guarantee of correctness. [TODO] multi-level segment has to accelerate find_intersecting_edges() [TODO] maybe smarter handling
- L37 _public member_ `FDynamicGraph2d Graph;` — graph of arrangement
- L40 _public member_ `TPointHashGrid2d<int> PointHash;` — PointHash for vertices of graph
- L43 _public member_ `double VertexSnapTol = 0.00001;` — points within this tolerance are merged
- L45 _public function_ `FArrangement2d(const FAxisAlignedBox2d& BoundsHint) : PointHash(FMath::Max(FMathd::ZeroTolerance, BoundsHint.MaxDim() / 64), -1)`
- L50 _public function_ `FArrangement2d(double PointHashCellSize) : PointHash(FMath::Max(FMathd::ZeroTolerance, PointHashCellSize), -1)`
- L66 _public prototype_ `bool AttemptTriangulate(TArray<FIndex3i>& Triangles, TArray<int32>& SkippedEdges, int32 BoundaryEdgeGroupID);` — `UE_DEPRECATED(5.1, "Please use the Triangulate or TriangulateWithBoundary functions instead, which are explicit about whether a BoundaryEdgeGroupID should be present")` — Attempts to triangulates the arrangement with a constrained Delaunay triangulation NOTE: Will return all triangles if no edges found with the BoundaryEdgeGroupID NOTE: May fail if arrangement has self-intersections Triangles: Output triangles (as indices into Graph vertices) SkippedEdges: Output indices of edges that the algorithm failed to insert BoundaryEdgeGroupID: ID of edges corresponding to a boundary; if we have a closed loop of these boundary edges on output triangulation, will discard triangles outside this return: false if triangulation algo knows it failed (note Triangles may still have some triangulation of the input in this case; for example it may just be missing some required edges)
- L70 _public prototype_ `bool AttemptTriangulate(TArray<FIntVector>& Triangles, TArray<int32>& SkippedEdges, int32 BoundaryEdgeGroupID);` — `UE_DEPRECATED(5.1, "Please use the Triangulate or TriangulateWithBoundary functions instead, which are explicit about whether a BoundaryEdgeGroupID should be present")` — Variant of AttemptTriangulate using FIntVector instead of FIndex3i; Note this incurs an extra copy of the triangle array
- L81 _public prototype_ `bool TriangulateWithBoundaryAndHoles(TArray<FIndex3i>& Triangles, int32 BoundaryEdgeGroupID, int32 HoleEdgeGroupID);` — Attempts to triangulate the arrangement with a constrained Delaunay triangulation NOTE: May fail if arrangement has self-intersections @param Triangles				Output triangles (as indices into Graph vertices) @param BoundaryEdgeGroupID	ID of edges corresponding to a boundary: triangles outside these edges will be removed @param HoleEdgeGroupID		ID of edges corresponding to internal holes: triangles inside these edges will be removed @return						false if triangulation algo knows it failed; will still likely have some triangulation even in this case
- L91 _public prototype_ `bool TriangulateWithBoundary(TArray<FIndex3i>& Triangles, int32 BoundaryEdgeGroupID);` — Attempts to triangulate the arrangement with a constrained Delaunay triangulation NOTE: May fail if arrangement has self-intersections @param Triangles				Output triangles (as indices into Graph vertices) @param BoundaryEdgeGroupID	ID of edges corresponding to a boundary: triangles outside these edges will be removed @return						false if triangulation algo knows it failed; will still likely have some triangulation even in this case
- L100 _public prototype_ `bool Triangulate(TArray<FIndex3i>& Triangles);` — Attempts to triangulate the arrangement with a constrained Delaunay triangulation NOTE: May fail if arrangement has self-intersections @param Triangles				Output triangles (as indices into Graph vertices) @return						false if triangulation algo knows it failed; will still likely have some triangulation even in this case
- L105 _public function_ `bool HasSelfIntersections()` — Check if current Graph has self-intersections; not optimized, only for debugging
- L126 _public function_ `FIndex2i SplitEdgeAtPoint(int EdgeID, FVector2d Point)` — Subdivide edge at a given position
- L139 _public function_ `bool HasVertexNear(FVector2d Point, double SearchRadius)` — Check if vertex exists in region
- L147 _public function_ `int Insert(const FVector2d& Pt)` — Insert isolated point P into the arrangement
- L156 _public function_ `int32 InsertNewIsolatedPointUnsafe(const FVector2d& Pt)` — Insert isolated point P into the arrangement when you know by construction it's not too close to any vertex or edge Much faster, but will break things if you use it to insert a point that is on top of any existing element!
- L166 _public function_ `void Insert(const FVector2d& A, const FVector2d& B, int GID = -1)` — insert segment [A,B] into the arrangement
- L174 _public function_ `void Insert(const FSegment2d& Segment, int GID = -1)` — insert segment into the arrangement
- L195 _public function_ `void Insert(const FPolygon2d& Poly, int GID = -1)` — * sequentially insert segments of polygon
- L211 _public function_ `void ConnectOpenBoundaries(double DistThresh)` — connect open boundary vertices within DistThresh, by inserting new segments
- L241 _protected function_ `int insert_point(const FVector2d& P, double Tol = 0)` — insert pt P into the arrangement, splitting existing edges as necessary
- L287 _protected function_ `bool insert_segment(FVector2d A, FVector2d B, int GID = -1, double Tol = 0)` — insert edge [A,B] into the arrangement, splitting existing edges as necessary
- L424 _protected function_ `FIndex2i split_segment_at_t(int EID, double T, double Tol)` — insert new point into segment EID at parameter value T If T is within Tol of endpoint of segment, we use that instead.
- L468 _protected function_ `int find_existing_vertex(FVector2d Pt)` — find existing vertex at point, if it exists
- L475 _protected function_ `int find_nearest_vertex(FVector2d Pt, double SearchRadius, int IgnoreVID = -1)` — find closest vertex, within SearchRadius
- L491 _protected function_ `int find_nearest_boundary_vertex(FVector2d Pt, double SearchRadius, int IgnoreVID = -1)` — find nearest boundary vertex, within SearchRadius
- L515 _protected function_ `bool find_intersecting_edges(FVector2d A, FVector2d B, TArray<FIntersection>& Hits, double Tol = 0)` — find set of edges in graph that intersect with edge [A,B]
- L550 _protected function_ `bool find_intersecting_floating_vertices(const FSegment2d &SegAB, int32 AID, int32 BID, TArray<FSegmentPoint>& Hits, double Tol = 0)`
- L576 _private prototype_ `bool TriangulateInternal(TArray<FIndex3i>& Triangles, bool bHasBoundaryEdgeGroupID, int32 BoundaryEdgeGroupID, bool bHasHoleGroupID, int32 HoleEdgeGroupID, bool bLegacyKeepTrianglesIfBoundaryNotFound, TArray<int32>* SkippedEdges);` — Full-featured implementation for all Triangulate function variants to call

#### struct `UE::Geometry::FArrangement2d::FSegmentPoint`  
`struct FSegmentPoint`  
_L232-236_
- L234 _public member_ `double T;`
- L235 _public member_ `int VID;`

#### struct `UE::Geometry::FArrangement2d::FIntersection`  
`struct FIntersection`  
_L504-510_
- L506 _public member_ `int EID;`
- L507 _public member_ `int SideX;`
- L508 _public member_ `int SideY;`
- L509 _public member_ `FIntrSegment2Segment2d Intr;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L395 _function_ `points.Sort([](const FSegmentPoint& pa, const FSegmentPoint& pb) { return pa.T < pb.T; });` (scope `UE::Geometry::FArrangement2d::insert_segment`) — sort by T
- L477 _function_ `auto FuncDistSq = [&](int B)` (scope `UE::Geometry::FArrangement2d::find_nearest_vertex`)
- L478 _function_ `auto FuncIgnore = [&](int VID)` (scope `UE::Geometry::FArrangement2d::find_nearest_vertex`)
- L493 _function_ `auto FuncDistSq = [&](int B)` (scope `UE::Geometry::FArrangement2d::find_nearest_boundary_vertex`)
- L494 _function_ `auto FuncIgnore = [&](int VID)` (scope `UE::Geometry::FArrangement2d::find_nearest_boundary_vertex`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/ConstrainedDelaunay2.h` (Public)


#### struct `UE::Geometry::TConstrainedDelaunay2`  
`template<typename RealType> struct TConstrainedDelaunay2`  
_L26-157_
- desc: This is a version of FDelaunay (which can also do Constrained Delaunay triangulation), but with added support for: 1. Explicit "Hole" edges that must be cut out of the result (FDelaunay relies only on winding rules to create holes) 2. Option to duplicate vertices to split any 'bowtie' vertices If you do not need either of these features, FDelaunay may be the faster option.
- L31 _public member_ `TArray<TVector2<RealType>> Vertices;` — inputs
- L34 _public member_ `TArray<FIndex2i> Edges;` — Edges and HoleEdges must not be intersecting; use Arrangment2D to pre-process any input w/ intersecting edges
- L35 _public member_ `TArray<FIndex2i> HoleEdges;` — Any triangles inside 'hole' edges *must* be cut out
- L40 _public member_ `bool bOrientedEdges = true;`
- L41 _public member_ `bool bOutputCCW = false;`
- L42 _public member_ `bool bSplitBowties = false;`
- L51 _public member_ `EFillRule FillRule = EFillRule::Odd;`
- L53 _public function_ `inline bool ClassifyFromRule(int Winding)`
- L72 _public function_ `template<class InputRealType> void Add(const FDynamicGraph2<InputRealType>& Graph)`
- L95 _public function_ `template<class InputRealType> void Add(const TPolygon2<InputRealType>& Polygon, bool bIsHole = false)`
- L119 _public function_ `template<class InputRealType> void Add(const TGeneralPolygon2<InputRealType>& GPolygon)`
- L130 _public prototype_ `bool AddWithIntersectionResolution(const TPolygon2<RealType>& Polygon);` — Add Polygon with self-intersections resolved. Returns false if resolving self-intersections failed.
- L132 _public prototype_ `bool AddWithIntersectionResolution(const TGeneralPolygon2<RealType>& GeneralPolygon);` — Add General Polygon with self-intersections resolved. Returns false if resolving self-intersections failed.
- L137 _public member_ `TArray<FIndex3i> Triangles;` — outputs
- L140 _public member_ `int AddedVerticesStartIndex = -1;` — If vertices were added to output (e.g. to split bowties), this is set to the index of the first added vertex
- L147 _public prototype_ `bool Triangulate();` — Populate Triangles @return false if Triangulation failed
- L156 _public prototype_ `bool Triangulate(TFunctionRef<bool(const TArray<TVector2<RealType>>&, const FIndex3i&)> KeepTriangle);` — Populate Triangles with override function to determine which triangles are in or out. Note that boundary edges and hole edges are treated as equivalent by this function; only the KeepTriangle function determines what triangles are excluded. @param KeepTriangle Function to check whether the given triangle should be kept in the output @return false if Triangulation failed

#### enum `UE::Geometry::TConstrainedDelaunay2::EFillRule`  
`enum class EFillRule`  
_L44-50_
- L45 _public enumerator_ `Odd = 0`
- L47 _public enumerator_ `NonZero` — bOrientedEdges must be true for the below
- L48 _public enumerator_ `Positive`
- L49 _public enumerator_ `Negative`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L166 _prototype_ `template<typename RealType> TArray<FIndex3i> ConstrainedDelaunayTriangulate(const TGeneralPolygon2<RealType>& GeneralPolygon);` (scope `UE::Geometry`) — Convenience function; invokes TConstrainedDelaunay2::Triangulate with most-often-used options @param GeneralPolygon A general polygon, which may include holes. @return An array of triangle indices.  Indices refer to a flat array w/ the outer polygon vertices first, and the hole vertices appended after.
- L176 _prototype_ `template<typename RealType> TArray<FIndex3i> ConstrainedDelaunayTriangulateWithVertices(const TGeneralPolygon2<RealType>& GeneralPolygon, TArray<TVector2<RealType>>& OutVertices);` (scope `UE::Geometry`) — Convenience function; invokes TConstrainedDelaunay2::Triangulate with most-often-used options. @param GeneralPolygon A general polygon, which may include holes. @param OutVertices Output array of vertices used in the triangulation. @return An array of triangle indices.
- L178 _typedef_ `typedef TConstrainedDelaunay2<float> FConstrainedDelaunay2f;` (scope `UE::Geometry`)
- L179 _typedef_ `typedef TConstrainedDelaunay2<double> FConstrainedDelaunay2d;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/Curve/BSplineCurveFit.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Geometry` (scope `UE`)
- L27 _prototype_ `bool BSplineCurveFit(const TArray<FVector2f>& DataPoints, const int32 SplineDegree, const int32 NumControlPoints, TArray<FVector2f>& ControlPointsOut);` (scope `UE::Geometry`) — Compute the control points that result from a best fit of the provided 2d data points when using b-splines of the specified degree. This fit assumes the sample points are evenly spaced in 't' over the interval [0, 1]. and the knot vector has unique knots at  j / (NumControlPoints - SplineDegree) for j in [0, (NumControlPoints - Degree)]. the knots at 0 and 1 each have multiplicity SplineDegree + 1, while the internal knots just have multiplicity 1. @param DataPoints       - an array of 2d points the b-spline will attempt to fit @param SplineDegree     - the degree of the underling b-spline.  Must be greater that 0. @param NumControlPoints - requested number of control points solved for. Note: requires SplineDegree < NumControlPoints <= DataPoints.Num() @param ControlPointsOut - on successful return, an array of 2d control points of the specified length ( on failure the array is unchanged ). @return true on success.
- L46 _prototype_ `bool BSplineCurveFit(const TArray<FVector3f>& DataPoints, const int32 SplineDegree, const int32 NumControlPoints, TArray<FVector3f>& ControlPointsOut);` (scope `UE::Geometry`) — Compute the control points that result from a best fit of the provided 3d data points when using b-splines of the specified degree. This fit assumes the sample points are evenly spaced in 't' over the interval [0, 1]. and the knot vector has unique knots at  j / (NumControlPoints - SplineDegree) for j in [0, (NumControlPoints - Degree)]. the knots at 0 and 1 each have multiplicity SplineDegree + 1, while the internal knots just have multiplicity 1. @param DataPoints       - an array of 3d points the b-spline will attempt to fit @param SplineDegree     - the degree of the underling b-spline.  Must be greater that 0. @param NumControlPoints - requested number of control points solved for. Note: requires SplineDegree < NumControlPoints <= DataPoints.Num() @param ControlPointsOut - on successful return, an array of 3d control points of the specified length  ( on failure the array is unchanged ). @return true on success.

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/Curve/PolygonIntersectionUtils.h` (Public)


#### enum `UE::Geometry::EPolygonBooleanOp`  
`enum class EPolygonBooleanOp : uint8`  
_L10-16_
- L12 _public enumerator_ `Union`
- L13 _public enumerator_ `Difference`
- L14 _public enumerator_ `Intersect`
- L15 _public enumerator_ `ExclusiveOr`

#### class `UE::Geometry::TBooleanPolygon2Polygon2`  
`template <EPolygonBooleanOp OperationType, typename GeometryType, typename RealType> class TBooleanPolygon2Polygon2`  
_L20-35_
- desc: Produces the boolean'd result of PolygonA and PolygonB depending on the OperationType. Both polygons must be closed.
- L24 _public member_ `GeometryType PolygonA;` — Input
- L25 _public member_ `GeometryType PolygonB;`
- L28 _public member_ `TArray<UE::Geometry::TGeneralPolygon2<RealType>> Result;` — Output
- L30 _public prototype_ `TBooleanPolygon2Polygon2( const GeometryType& InPolygonA, const GeometryType& InPolygonB);`
- L34 _public prototype_ `bool ComputeResult();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Geometry` (scope `UE`)
- L38 _typedef_ `template <EPolygonBooleanOp OperationType> using TBooleanGeneralPolygon2GeneralPolygon2f = TBooleanPolygon2Polygon2<OperationType, TGeneralPolygon2<float>, float>;` (scope `UE::Geometry`)
- L41 _typedef_ `template <EPolygonBooleanOp OperationType> using TBooleanGeneralPolygon2GeneralPolygon2d = TBooleanPolygon2Polygon2<OperationType, TGeneralPolygon2<double>, double>;` (scope `UE::Geometry`)
- L45 _typedef_ `template <typename GeometryType, typename RealType> using TUnionPolygon2Polygon2 = TBooleanPolygon2Polygon2<EPolygonBooleanOp::Union, GeometryType, RealType>;` (scope `UE::Geometry`) — Produces the combined result of PolygonA and PolygonB. Both must be closed.
- L47 _typedef_ `typedef TUnionPolygon2Polygon2<TGeneralPolygon2<float>, float> FUnionGeneralPolygon2GeneralPolygon2f;` (scope `UE::Geometry`)
- L48 _typedef_ `typedef TUnionPolygon2Polygon2<TGeneralPolygon2<double>, double> FUnionGeneralPolygon2GeneralPolygon2d;` (scope `UE::Geometry`)
- L52 _typedef_ `template <typename GeometryType, typename RealType> using TDifferencePolygon2Polygon2 = TBooleanPolygon2Polygon2<EPolygonBooleanOp::Difference, GeometryType, RealType>;` (scope `UE::Geometry`) — Produces the result of PolygonA with the shape of PolygonB removed. Both must be closed.
- L54 _typedef_ `typedef TDifferencePolygon2Polygon2<TGeneralPolygon2<float>, float> FDifferenceGeneralPolygon2GeneralPolygon2f;` (scope `UE::Geometry`)
- L55 _typedef_ `typedef TDifferencePolygon2Polygon2<TGeneralPolygon2<double>, double> FDifferenceGeneralPolygon2GeneralPolygon2d;` (scope `UE::Geometry`)
- L59 _typedef_ `template <typename GeometryType, typename RealType> using TIntersectPolygon2Polygon2 = TBooleanPolygon2Polygon2<EPolygonBooleanOp::Intersect, GeometryType, RealType>;` (scope `UE::Geometry`) — Produces the areas of each polygon that are also present in the other as a combined result. Both must be closed.
- L61 _typedef_ `typedef TIntersectPolygon2Polygon2<TGeneralPolygon2<float>, float> FIntersectGeneralPolygon2GeneralPolygon2f;` (scope `UE::Geometry`)
- L62 _typedef_ `typedef TIntersectPolygon2Polygon2<TGeneralPolygon2<double>, double> FIntersectGeneralPolygon2GeneralPolygon2d;` (scope `UE::Geometry`)
- L66 _typedef_ `template <typename GeometryType, typename RealType> using TExclusiveOrPolygon2Polygon2 = TBooleanPolygon2Polygon2<EPolygonBooleanOp::ExclusiveOr, GeometryType, RealType>;` (scope `UE::Geometry`) — Produces the areas of each polygon not present in the other as a combined result. Both must be closed.
- L68 _typedef_ `typedef TExclusiveOrPolygon2Polygon2<TGeneralPolygon2<float>, float> FExclusiveOrGeneralPolygon2GeneralPolygon2f;` (scope `UE::Geometry`)
- L69 _typedef_ `typedef TExclusiveOrPolygon2Polygon2<TGeneralPolygon2<double>, double> FExclusiveOrGeneralPolygon2GeneralPolygon2d;` (scope `UE::Geometry`)
- L75 _prototype_ `bool PolygonsUnion(TArrayView<const FGeneralPolygon2d> Polygons, TArray<FGeneralPolygon2d>& ResultOut, bool bCopyInputOnFailure);` (scope `UE::Geometry`) — Populate ResultOut with the union of the input Polygons @param bCopyInputOnFailure		If true, copy the input Polygons to ResultOut if the union is not successfully computed. Otherwise, ResultOut is left empty on failure.
- L78 _prototype_ `bool PolygonsDifference(TArrayView<const FGeneralPolygon2d> PosPolygons, TArrayView<const FGeneralPolygon2d> NegPolygons, TArray<FGeneralPolygon2d>& ResultOut);` (scope `UE::Geometry`) — Populate ResultOut with the difference of PosPolygons minus NegPolygons
- L81 _prototype_ `bool PolygonsIntersection(TArrayView<const FGeneralPolygon2d> SubjPolygons, TArrayView<const FGeneralPolygon2d> ClipPolygons, TArray<FGeneralPolygon2d>& ResultOut);` (scope `UE::Geometry`) — Populate ResultOut with the intersection of SubjPolygons with ClipPolygons
- L84 _prototype_ `bool PolygonsExclusiveOr(TArrayView<const FGeneralPolygon2d> SubjPolygons, TArrayView<const FGeneralPolygon2d> ClipPolygons, TArray<FGeneralPolygon2d>& ResultOut);` (scope `UE::Geometry`) — Populate ResultOut with the 'exclusive or' of SubjPolygons with ClipPolygons
- L87 _prototype_ `bool PathsIntersection(const TArray<TArrayView<FVector2d>>& Paths, TArrayView<const FGeneralPolygon2d> ClipPolygons, TArray<TArray<FVector2d>>& PathsOut);` (scope `UE::Geometry`) — Populate PathsOut with the intersected SubjPaths with ClipPolygons
- L90 _prototype_ `bool PathsDifference(const TArray<TArrayView<FVector2d>>& Paths, TArrayView<const FGeneralPolygon2d> ClipPolygons, TArray<TArray<FVector2d>>& PathsOut);` (scope `UE::Geometry`) — Populate PathsOut with the clipped SubjPaths with ClipPolygons

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/Curve/PolygonOffsetUtils.h` (Public)


#### enum `UE::Geometry::EPolygonOffsetJoinType`  
`enum class EPolygonOffsetJoinType : uint8`  
_L10-15_
- L12 _public enumerator_ `Square`
- L13 _public enumerator_ `Round` — Square,		  Uniform squaring on all convex edge joins.
- L14 _public enumerator_ `Miter` — Round,		  Arcs on all convex edge joins.

#### enum `UE::Geometry::EPolygonOffsetEndType`  
`enum class EPolygonOffsetEndType : uint8`  
_L17-24_
- L19 _public enumerator_ `Polygon`
- L20 _public enumerator_ `Joined` — Polygon,	  Offsets only one side of a closed path
- L21 _public enumerator_ `Butt` — Joined,		  Offsets both sides of a path, with joined ends
- L22 _public enumerator_ `Square` — Butt,		  Offsets both sides of a path, with square blunt ends
- L23 _public enumerator_ `Round` — Square,		  Offsets both sides of a path, with square extended ends

#### class `UE::Geometry::TOffsetPolygon2`  
`template <typename GeometryType, typename RealType> class TOffsetPolygon2`  
_L28-47_
- desc: Offsets a given polygon (a polyline or closed polygon), determined by EndType by a  given amount.
- L32 _public member_ `TArray<GeometryType> Polygons;` — Input
- L33 _public member_ `RealType Offset = 1.0;`
- L34 _public member_ `RealType MiterLimit = 2.0;` — Minimum value is clamped to 2.0
- L35 _public member_ `double MaxStepsPerRadian = -1;` — If > 0 and JoinType is Round, limit the maximum steps per radian to this value
- L36 _public member_ `double DefaultStepsPerRadianScale = 1.0;` — If JoinType is Round, multiply the default-computed steps per radian by this amount.
- L37 _public member_ `EPolygonOffsetJoinType JoinType = EPolygonOffsetJoinType::Square;`
- L38 _public member_ `EPolygonOffsetEndType EndType = EPolygonOffsetEndType::Polygon;`
- L41 _public member_ `TArray<UE::Geometry::TGeneralPolygon2<RealType>> Result;` — Output
- L43 _public prototype_ `explicit TOffsetPolygon2(const TArray<GeometryType>& InPolygons);`
- L44 _public prototype_ `TOffsetPolygon2() = default;`
- L46 _public prototype_ `bool ComputeResult();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Geometry` (scope `UE`)
- L49 _typedef_ `typedef TOffsetPolygon2<TArrayView<TVector2<float>>, float> FOffsetPolygon2f;` (scope `UE::Geometry`)
- L50 _typedef_ `typedef TOffsetPolygon2<TArrayView<TVector2<double>>, double> FOffsetPolygon2d;` (scope `UE::Geometry`)
- L64 _prototype_ `bool PolygonsOffset( double Offset, TArrayView<const FGeneralPolygon2d> Polygons, TArray<FGeneralPolygon2d>& ResultOut, bool bCopyInputOnFailure, double MiterLimit, EPolygonOffsetJoinType JoinType = EPolygonOffsetJoinType::Square, EPolygonOffsetEndType EndType = EPolygonOffsetEndType::Polygon, double MaxStepsPerRadian = -1.0, double DefaultStepsPerRadianScale = 1.0);` (scope `UE::Geometry`) — Offset an array of general polygons. Note: Input polygons should not overlap; to process overlapping polygons, call PolygonsUnion first. @param Offset		The amount to offset the polygons. @param Polygons		The polygons to offset @param ResultOut		On success, will be filled with the resulting polygons. Note: It is ok to pass the same array as both the input and output. @param bCopyInputOnFailure Whether to copy the input polygons to the result on failure. @param MiterLimit	If JoinType is Miter, this limits how far each miter join can extend @param JoinType		How to join/extend corners between two edges @param EndType		Should generally be Polygon. Otherwise, input is interpreted as a path, and offset is a 'thickening' applied to each side. @param MaxStepsPerRadian				For Round JoinType, sets a maximum number of vertices to add per radian of curve. If <= 0, no maximum is used. @param DefaultStepsPerRadianScale	For Round JoinType, scales the default number of vertices to add per radian of curve. The default number is extremely large, so a value near 1e-3 is typical here.
- L86 _prototype_ `bool PolygonsOffsets( double FirstOffset, double SecondOffset, TArrayView<const FGeneralPolygon2d> Polygons, TArray<FGeneralPolygon2d>& ResultOut, bool bCopyInputOnFailure, double MiterLimit, EPolygonOffsetJoinType JoinType = EPolygonOffsetJoinType::Square, EPolygonOffsetEndType EndType = EPolygonOffsetEndType::Polygon, double MaxStepsPerRadian = -1.0, double DefaultStepsPerRadianScale = 1.0);` (scope `UE::Geometry`) — Perform two offsets of the input polygons, intended to support "opening" or "closing" operations Note: Input polygons should not overlap; to process overlapping polygons, call PolygonsUnion first. @param FirstOffset	The initial amount to offset the polygons. @param SecondOffset	The second amount to offset the polygons. @param Polygons		The polygons to offset @param ResultOut		On success, will be filled with the resulting polygons. Note: It is ok to pass the same array as both the input and output. @param bCopyInputOnFailure Whether to copy the input polygons to the result on failure. @param MiterLimit	If JoinType is Miter, this limits how far each miter join can extend @param JoinType		How to join/extend corners between two edges @param EndType		Should generally be Polygon. Otherwise, input is interpreted as a path, and offset is a 'thickening' applied to each side. @param MaxStepsPerRadian				For Round JoinType, sets a maximum number of vertices to add per radian of circular join. If <= 0, no maximum is used. @param DefaultStepsPerRadianScale	For Round JoinType, scales the default number of vertices to add per radian of curve. The default number is extremely large, so a value near 1e-3 is typical here.

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/Distance/DistLine3Circle3.h` (Public)


#### class `UE::Geometry::TDistLine3Circle3`  
`template <typename Real> class TDistLine3Circle3`  
_L21-50_
- desc: Compute unsigned distance and closest-points between 3D line and 3D circle
- L25 _public member_ `TLine3<Real> Line;` — Input
- L26 _public member_ `TCircle3<Real> Circle;`
- L29 _public member_ `Real DistanceSquared = -1.0;` — Output
- L31 _public member_ `int NumClosestPairs = 0;`
- L32 _public member_ `TVector<Real> LineClosest[2];`
- L33 _public member_ `TVector<Real> CircleClosest[2];`
- L34 _public member_ `bool bIsEquiDistant;`
- L36 _public function_ `TDistLine3Circle3(const TLine3<Real>& LineIn, const TCircle3<Real>& CircleIn) : Line(LineIn), Circle(CircleIn)`
- L40 _public function_ `Real Get()`
- L44 _public function_ `Real GetSquared()`
- L49 _public prototype_ `Real ComputeResult();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L52 _typedef_ `typedef TDistLine3Circle3<float> FDistLine3Circle3f;` (scope `UE::Geometry`)
- L53 _typedef_ `typedef TDistLine3Circle3<double> FDistLine3Circle3d;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/DynamicMeshMikkTWrapper.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace DynamicMeshMikkTWrapper`
- L10 _prototype_ `bool IsSupported();` (scope `DynamicMeshMikkTWrapper`) — @return true if the current platform supports MikkT tangent calculations
- L19 _prototype_ `bool ComputeTangents(UE::Geometry::FMeshTangentsd& MeshTangents, int32 UVLayer);` (scope `DynamicMeshMikkTWrapper`) — Compute MikkT tangents for the given MeshTangents @param MeshTangents Tangents to fill in. Must have a valid target mesh set. @param UVLayer The UV layer tangents should reference @return true if tangents were successfully computed (i.e. platform supported mikkt + requested mesh and UV layer were valid)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/FTetWildWrapper.h` (Public)


#### enum `UE::Geometry::FTetWild::EFilterOutsideMethod`  
`enum class EFilterOutsideMethod`  
_L10-17_
- L12 _public enumerator_ `None` — Do not remove outside tets from the result
- L13 _public enumerator_ `FloodFill` — Floodfill from tagged boundary faces of the active tet mesh
- L14 _public enumerator_ `InputSurface` — Use the winding number of the input surface mesh
- L15 _public enumerator_ `TrackedSurface` — Use the winding number of tagged boundary faces on the active tet mesh
- L16 _public enumerator_ `SmoothOpenBoundary` — Smooth the non-input faces that separate inside from outside, before filtering

#### struct `UE::Geometry::FTetWild::FTetMeshParameters`  
`struct FTetMeshParameters`  
_L19-52_
- L21 _public member_ `EFilterOutsideMethod OutsideFilterMethod = EFilterOutsideMethod::TrackedSurface;`
- L24 _public member_ `bool bCoarsen = false;` — Whether to coarsen the tet mesh result
- L26 _public member_ `bool bExtractManifoldBoundarySurface = false;` — Whether to enforce that the output boundary surface should be manifold. (Only relevant if a final surface is extracted)
- L28 _public member_ `bool bSkipSimplification = false;` — Whether to skip the initial simplification step
- L31 _public member_ `bool bApplySizing = false;` — Whether to apply a sizing field, interpolated over a background tet mesh, to control edge lengths
- L32 _public member_ `TArray<FVector> SizingFieldVertices;`
- L33 _public member_ `TArray<FIntVector4> SizingFieldTets;`
- L34 _public member_ `TArray<double> SizingFieldValues;`
- L37 _public member_ `double IdealEdgeLengthRel = 0.05;` — Ideal edge length relative to bounding box size
- L40 _public member_ `double IdealEdgeLength = 0.05;` — `UE_DEPRECATED(5.6, "Use IdealEdgeLengthRel instead.")`
- L43 _public member_ `double EpsRel = 1e-3;` — Relative tolerance, controlling how closely the mesh must follow the input surface
- L46 _public member_ `int32 MaxIts = 80;` — Maximum number of optimization iterations
- L48 _public member_ `double StopEnergy = 10;` — Energy at which to stop optimizing tet quality and accept the result
- L51 _public member_ `bool bInvertOutputTets = false;` — Whether to invert tets relative to what UE typically expects in the final output

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Geometry` (scope `UE`)
- L8 _namespace_ `namespace FTetWild` (scope `UE::Geometry`)
- L66 _prototype_ `bool ComputeTetMesh( const FTetMeshParameters& Params, const TArray<FVector>& InVertices, const TArray<FIntVector3>& InFaces, TArray<FVector>& OutVertices, TArray<FIntVector4>& OutTets, FProgressCancel* Progress = nullptr);` (scope `UE::Geometry::FTetWild`) — Use the fTetWild algorithm to compute a tetrahedral mesh for the input surface mesh @param Params		fTetWild algorithm parameters @param InVertices	Surface mesh vertices as a vertex buffer @param InFaces		Surface mesh faces as indices into InVertices @param OutVertices	Tet mesh vertices @param OutTets		Tetrahedra as indices into OutVertices @param Progress		Optional FProgressCancel object to support cancelling the computation and reporting progress @return true if algorithm succeeded, false if it failed or was cancelled

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/FitCapsule3.h` (Public)


#### class `UE::Geometry::TFitCapsule3`  
`template<typename RealType> class TFitCapsule3`  
_L20-54_
- desc: Fit a Capsule to a set of 3D points. Currently solved by using least-squares to fit a line to the point set. This does not guarantee that the capsule is the minimal possible volume.
- L26 _public member_ `bool bResultValid = false;` — Set to true in Solve() on success
- L28 _public member_ `TCapsule3<RealType> Capsule;` — The capsule computed in Solve()
- L39 _public prototype_ `bool Solve(int32 NumPoints, TFunctionRef<TVector<RealType>(int32)> GetPointFunc);` — Calculate a Capsule that contains the given Point Set and store in Output variables @return true if capsule was found
- L45 _public function_ `static bool Solve(int32 NumPoints, TFunctionRef<TVector<RealType>(int32)> GetPointFunc, TCapsule3<RealType>& CapsuleOut)` — Calculate a Capsule that contains the given Point Set and return in CapsuleOut @return true if capsule was found

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L56 _typedef_ `typedef TFitCapsule3<float> FFitCapsule3f;` (scope `UE::Geometry`)
- L57 _typedef_ `typedef TFitCapsule3<double> FFitCapsule3d;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/GeometryAlgorithmsModule.h` (Public)


#### class `FGeometryAlgorithmsModule`  
`class FGeometryAlgorithmsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/Intersection/IntrCylinderBox3.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L16 _prototype_ `template <typename RealType> bool DoesCylinderIntersectBox( const TAxisAlignedBox3<RealType>& Box, const TVector<RealType>& CylinderCenter, const TVector<RealType>& CylinderDirection, RealType CylinderRadius, RealType CylinderHeight);` (scope `UE::Geometry`) — Compute intersection between a cylinder and a 3D axis-aligned box.

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/MinVolumeBox3.h` (Public)


#### class `UE::Geometry::TMinVolumeBox3`  
`template<typename RealType> class TMinVolumeBox3`  
_L26-61_
- desc: Calculate a Minimal-Volume Oriented Box for a set of 3D points. This internally first computes the Convex Hull of the point set. The minimal box is then guaranteed to be aligned with one of the faces of the convex hull. Note that this is increasingly expensive as the Convex Hull face count increases.
- L37 _public prototype_ `bool Solve(int32 NumPoints, TFunctionRef<TVector<RealType>(int32)> GetPointFunc, bool bMostAccurateFit = false, FProgressCancel* Progress = nullptr);` — Calculate the minimal box for the given point set. @param NumPoints number of points in the set, ie GetPointFunc can be called for any integer in range [0...NumPoints) @param GetPointFunc function that returns a 3D point for a valid Index @param bMostAccurateFit if true, use the most expensive method to get the best-possible fit @param Progress optionally allow early-cancel of the box fit operation @return true if minimal box was found
- L48 _public prototype_ `bool SolveSubsample(int32 NumPoints, int32 NumSamplePoints, TFunctionRef<TVector<RealType>(int32)> GetPointFunc, bool bMostAccurateFit = false, FProgressCancel* Progress = nullptr);` — Calculate the minimal box for a Subsampling of MaxPoints points of a point set @param NumPoints number of points in the set, ie GetPointFunc can be called for any integer in range [0...NumPoints) @param NumSamplePoints maximum number of points to sample from NumPoints. Currently a random-ish subset is selected. @param GetPointFunc function that returns a 3D point for a valid Index @param bMostAccurateFit if true, use the most expensive method to get the best-possible fit @param Progress optionally allow early-cancel of the box fit operation @return true if minimal box was found
- L52 _public prototype_ `bool IsSolutionAvailable() const;` — @return true if minimal box is available
- L55 _public prototype_ `void GetResult(TOrientedBox3<RealType>& BoxOut);` — @return minimal box in BoxOut
- L58 _protected prototype_ `void Initialize(bool bMostAccurateFit);`
- L60 _protected member_ `TPimplPtr<TMinVolumeBox3Internal<RealType>> Internal;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L63 _typedef_ `typedef TMinVolumeBox3<float> FMinVolumeBox3f;` (scope `UE::Geometry`)
- L64 _typedef_ `typedef TMinVolumeBox3<double> FMinVolumeBox3d;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/MinVolumeSphere3.h` (Public)


#### class `UE::Geometry::TMinVolumeSphere3`  
`template<typename RealType> class TMinVolumeSphere3`  
_L23-43_
- desc: Calculate a Minimal-Volume Sphere for a set of 3D points. @warning Currently this processes input points in a randomized order so the results are not strictly deterministic. In particular if it fails you might try calling it again...
- L31 _public prototype_ `bool Solve(int32 NumPoints, TFunctionRef<TVector<RealType>(int32)> GetPointFunc, bool bUseExactComputation = false);` — Calculate the minimal sphere for the given point set. @param bUseExactComputation If true, high-precision Rational number types are used for the calculation, rather than doubles. This is slower but more precise. @return true if minimal sphere was found
- L34 _public prototype_ `bool IsSolutionAvailable() const;` — @return true if minimal box is available
- L37 _public prototype_ `void GetResult(TSphere3<RealType>& SphereOut);` — @return minimal sphere in SphereOut
- L40 _protected prototype_ `void Initialize(int32 NumPoints, bool bUseExactComputation);`
- L42 _protected member_ `TPimplPtr<TMinVolumeSphere3Internal<RealType>> Internal;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L45 _typedef_ `typedef TMinVolumeSphere3<float> FMinVolumeSphere3f;` (scope `UE::Geometry`)
- L46 _typedef_ `typedef TMinVolumeSphere3<double> FMinVolumeSphere3d;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/PCA3.h` (Public)


#### struct `UE::Geometry::FComputePCA3Options`  
`struct FComputePCA3Options`  
_L13-19_
- L16 _public member_ `bool bSortEigenvalues = true;` — Whether to sort the eigenvalues in decreasing order, so the largest components are first
- L18 _public member_ `bool bScaleDataToUnitCube = true;` — Whether to uniformly re-scale the data to fit in a unit cube before computing PCA. Note the scale factor applied will be stored in TPCA3::ScaleFactor.

#### class `UE::Geometry::TPCA3`  
`template<typename RealType> class TPCA3`  
_L22-37_
- L25 _public prototype_ `bool Compute(TConstArrayView<UE::Math::TVector<RealType>> Points, const FComputePCA3Options& Options = FComputePCA3Options());`
- L31 _public member_ `UE::Math::TVector<RealType> Mean;`
- L32 _public member_ `TStaticArray<UE::Math::TVector<RealType>, 3> Eigenvectors;`
- L33 _public member_ `UE::Math::TVector<RealType> Eigenvalues;`
- L36 _public member_ `UE::Math::TVector<RealType> ScaleFactor = UE::Math::TVector<RealType>::One();` — Any scale factor applied to the input data will be stored here

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L39 _typedef_ `typedef TPCA3<float> FPCA3f;` (scope `UE::Geometry`)
- L40 _typedef_ `typedef TPCA3<double> FPCA3d;` (scope `UE::Geometry`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/Parameterization/UVMetrics.h` (Public)


#### class `UE::Geometry::FUVMetrics`  
`class FUVMetrics`  
_L13-19_
- L16 _public prototype_ `static double ReedBeta(const UE::Geometry::FDynamicMesh3& Mesh, int32 UVChannel, int32 Tid);`
- L17 _public prototype_ `static double Sander(const UE::Geometry::FDynamicMesh3& Mesh, int32 UVChannel, int32 Tid, bool bUseL2);`
- L18 _public prototype_ `static double TexelDensity(const UE::Geometry::FDynamicMesh3& Mesh, int32 UVChannel, int32 Tid, int32 MapSize);`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API GEOMETRYALGORITHMS_API`
- L8 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/Skeletonization/MeshMedialAxisSampling.h` (Public)


#### struct `UE::Geometry::MedialAxis::FShrinkMedialBall`  
`struct FShrinkMedialBall`  
_L29-265_
- desc: Algorithm adapted from "3D medial axis point approximation using nearest neighbors and the normal field" by Ma et al. Starting from a surface point + normal, aims to find a "medial axis ball" touching that point and one other point w/ center along Point,-Normal ray, via iteratively shrinking an estimated radius to touch the surface point + a nearest point Note that the returned sphere may not touch the input surface point, esp. in corner cases where the actual medial ball would have zero radius.
- L32 _public member_ `int32 MaxIters = 20;` — Max iterations of shrinking to apply
- L34 _public member_ `double MinDelta = UE_DOUBLE_KINDA_SMALL_NUMBER;` — Threshold to stop iterating, if radius or center changes less than this
- L36 _public member_ `double RadiusThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER;` — Stop iterating below this radius (if > 0). Returned radius may still be smaller than this.
- L40 _public function_ `template<typename MeshType> bool FindLocalMinCurvatureRadius(const MeshType& Mesh, FVector3d& SurfacePoint, FVector3d& SurfaceNormal, TConstArrayView<int32> NbrVIDs, double& OutFoundRadius)` — Method to 'hot start' the search via local vertex neighborhood, using a provided neighborhood
- L50 _public function_ `bool FindLocalMinCurvatureRadius(const FDynamicMesh3& Mesh, FVector3d& SurfacePoint, FVector3d& SurfaceNormal, int32 SurfaceVID, double& OutFoundRadius)` — Method to 'hot start' the search via local vertex neighborhood, using the neighborhood information in the dynamic mesh
- L74 _public function_ `template<typename MeshType> FSphere Find(const TMeshAABBTree3<MeshType>& MeshBVH, const FVector3d& SurfacePoint, const FVector3d& SurfaceNormal, bool bRadiusHotStart, double InitialRadius, TFunctionRef<bool(int32)> EarlyStopAtTIDFn)` — Shrink a sphere touching a given SurfacePoint, with center along the line through its SurfaceNormal until the sphere approximately touches two closest surface points including the input point Note: Sphere will often not actually touch the input surface point due to discretization error, since we set the radius s.t. the sphere remains inside the input surface @param MeshBVH BVH of the surface @param SurfacePoint Reference point that the medial ball should approximately touch @param SurfaceNormal Normal at the SurfacePoint; note for vertices/edges this should be a smooth normal @param bRadiusHotStart If true, the InitialRadius should be a more accurate initial guess e.g. provided via one of the FindLocalMinCurvatureRadius methods @param InitialRadius If non-negative, initial radius to use for the sphere-shrinking search. Otherwise, will be automatically set from the surface bounding box's max dimension @param EarlyStopAtTIDFn Use when starting from a vertex/edge to stop in the discrete neighborhood of that source vertex/edge. Passed the current closest triangle ID.
- L160 _public function_ `template<typename MeshType> FSphere FindWithImplicitWeld(const TMeshAABBTree3<MeshType>& MeshBVH, int32 WeldedSurfacePointVID, TFunctionRef<int32(int32)> VIDtoWeldVIDFn, const FVector3d& SurfacePoint, const FVector3d& SurfaceNormal, bool bRadiusHotStart, double InitialRadius)`
- L184 _public function_ `template<typename MeshType> bool Project(const TMeshAABBTree3<MeshType>& MeshBVH, FSphere& InOutToProject, double InitialSearchRadius = -1, const TFastWindingTree<MeshType>* MeshFWTree = nullptr, TFunctionRef<int32(int32)>* VIDtoWeldVIDFn = nullptr )` — Project an existing sphere to a surface-contained sphere, searching along the line through the initial sphere center and corresponding closest surface point @param MeshBVH BVH of the surface @param InOutToProject Sphere to project @param InitialSearchRadius If non-negative, initial radius to use for the sphere-shrinking search. Otherwise, will be automatically set from the surface bounding box's max dimension @param MeshFWTree If non-null, test the fast winding of the center before projecting, and reverse the search direction if it's outside. Otherwise, a (less robust) normal test will be used instead. @param VIDtoWeldVIDFn If provided, early-stop the search when it hits a triangle sharing a welded vertex with the starting triangle. Can help prevent over-shrinking from discretization. @return true if the sphere was updated via projection, false otherwise (e.g. if the BVH was empty, or if we couldn't get a valid search normal)
- L247 _private function_ `bool ShrinkFromLocalVertex(const FVector3d& SurfacePoint, const FVector3d& SurfaceNormal, const FVector3d& LocalVertex, double& InOutRadius)` — Update curvature estimate from local vertex in neighborhood of SurfacePoint

#### struct `UE::Geometry::MedialAxis::FMedialSkeleton`  
`struct FMedialSkeleton`  
_L270-364_
- desc: Simple representation of a surface's medial skeleton, as a set of spheres + connectivity on those spheres, and a mapping to the surface vertices
- L273 _public member_ `TArray<FSphere> Spheres;` — Medial spheres, 1 per cluster, indexed by cluster index
- L275 _public member_ `TArray<int32> VIDtoClusterIndex;` — Mapping from source mesh vertex IDs to cluster Index
- L278 _public typedef_ `using FNbrArray = TArray<int32, TInlineAllocator<16>>;` — Inline-allocated array used for representing the typically-small neighborhoods in the cluster connectivity graph
- L280 _public member_ `TArray<FNbrArray> ClusterNeighbors;` — Indices of neighbors of clusters, for each cluster
- L282 _public member_ `TArray<FIndex3i> ClusterTriangles;` — Triangles of the medial skeleton, where the skeleton is a surface rather than a chain. Note: Not oriented, and generally not manifold -- so cannot be directly appended to an FDynamicMesh3
- L286 _public prototype_ `bool CheckValidity(EValidityCheckFailMode FailMode = EValidityCheckFailMode::Ensure) const;` — Check that the skeleton data structures are internally consistent Note: Relatively expensive, intended for debugging / testing
- L289 _public function_ `template<typename TriangleMeshType> bool IsCompatibleWithMesh(const TriangleMeshType& Mesh) const`
- L308 _public function_ `template<typename TriangleMeshType> void ComputeClusterTriangles(const TriangleMeshType& Mesh, TFunctionRef<int32(int32)> VIDtoWeldVIDFn)` — Compute the ClusterTriangles array for the current FMedialSkeleton, given a Mesh and assuming VIDtoClusterIndex is already computed
- L336 _public function_ `template<typename TriangleMeshType> void ComputeClusterNeighbors(const TriangleMeshType& Mesh, TFunctionRef<int32(int32)> VIDtoWeldVIDFn)` — Compute the ClusterNeighbors array for the current FMedialSkeleton, given a Mesh and assuming Spheres and VIDtoClusterIndex are already computed

#### struct `UE::Geometry::MedialAxis::FMedialSkeletonToTreeSkeletonOptions`  
`struct FMedialSkeletonToTreeSkeletonOptions`  
_L368-436_
- L400 _public member_ `EEdgeWeightMethod EdgeWeightMethod = EEdgeWeightMethod::ArrayOrder;`
- L401 _public member_ `EMergeDisconnectedMethod MergeDisconnectedMethod = EMergeDisconnectedMethod::ConnectClosestBones;`
- L402 _public member_ `ESelectRootMethod SelectRootMethod = ESelectRootMethod::ArrayOrder;`
- L405 _public member_ `FVector3d RootSelectionPoint = FVector3d::ZeroVector;` — When SelectRootMethod is ClosestToPoint, the point to use
- L407 _public member_ `FVector3d RootSelectionDirection = -FVector3d::UnitZ();` — When SelectRootMethod is FarthestInDirection, the direction to use
- L411 _public member_ `TOptional<FVector3d> CustomRootPosition;` — If set, always add a top-level root bone at this position (not corresponding to a medial skeleton cluster) Note: When MergeDisconnectedMethod==AddTopLevelRoot, this will also be used as that top level root bone.
- L427 _public prototype_ `template<typename MeshType> static void ToHierarchy(const FMedialSkeleton& InMedialSkeleton, const TMeshAABBTree3<MeshType>* AvoidIntersectingMeshBVH, TArray<int32>& OutParent, TArray<FTransform>& OutTransform, FMedialSkeletonToTreeSkeletonOptions Options, int32 RootIndex = INDEX_NONE, TArray<int32>* OutBoneIndexToMedialIndex = nullptr, TArray<int32>* OutMedialIndexToBoneIndex = nullptr);` — Remap a medial skeleton to a hierarchical skeleton suitable for using in a URefSkeleton for animation Note the indices of the hierarchical skeleton bones will be remapped from the medial skeleton, because URefSkeleton requires that parent bone indices be smaller than child bone indices @param InMedialSkeleton Input medial skeleton @param AvoidIntersectingMeshBVH Surface that the output skeleton should prefer not to cross. (Surface-intersecting edges will still be added as-needed, if the non-intersecting edges are not sufficient to create a spanning tree.) @param OutParent Output hierarchy, as parent indices @param OutTransform Relative transforms for each bone. 1:1 with OutParent. @param Options Additional options to control the skeleton conversion @param RootIndex Specify the medial skeleton cluster to prefer as the root bone. If INDEX_NONE, a default root will be selected automatically. @param OutBoneIndexToMedialIndex Optional mapping from hierarchical skeleton bone indices to source medial skeleton cluster indices @param OutMedialIndexToBoneIndex Optional mapping from source medial skeleton cluster indices to hierarchical skeleton bone indices
- L431 _public function_ `static void ToHierarchy(const FMedialSkeleton& InMedialSkeleton, TArray<int32>& OutParent, TArray<FTransform>& OutTransform, FMedialSkeletonToTreeSkeletonOptions Options, int32 RootIndex = INDEX_NONE, TArray<int32>* OutBoneIndexToMedialIndex = nullptr, TArray<int32>* OutMedialIndexToBoneIndex = nullptr)` — Same as above ToHierarchy method, but without the AvoidIntersectingMeshBVH parameter

#### enum `UE::Geometry::MedialAxis::FMedialSkeletonToTreeSkeletonOptions::EEdgeWeightMethod`  
`enum class EEdgeWeightMethod`  
_L371-379_
- desc: Method to select which edges of the medial skeleton are prioritized for inclusion in the hierarchical skeleton
- L374 _public enumerator_ `EdgeLength` — Favor adding shorter edges first
- L376 _public enumerator_ `ArrayOrder` — Favor edges between clusters that are earlier in the medial skeleton array. Because medial spheres are added incrementally in the highest error locations, their order can approximate importance.
- L378 _public enumerator_ `AvgRadius` — Favor adding edges between larger medial spheres first

#### enum `UE::Geometry::MedialAxis::FMedialSkeletonToTreeSkeletonOptions::EMergeDisconnectedMethod`  
`enum class EMergeDisconnectedMethod`  
_L382-388_
- desc: Method to merge disconnected components of the medial skeleton into a single hierarchy
- L385 _public enumerator_ `ConnectClosestBones` — Connect closest bones across disconnected components until there is a single hierarchy
- L387 _public enumerator_ `AddTopLevelRoot` — Add a top-level root node, and connect the selected root and all disconnected components to this node

#### enum `UE::Geometry::MedialAxis::FMedialSkeletonToTreeSkeletonOptions::ESelectRootMethod`  
`enum class ESelectRootMethod`  
_L391-398_
- desc: Method to automatically select the medial cluster to use as animation skeleton root, if a root cluster index is not specified
- L393 _public enumerator_ `ClosestToPoint`
- L394 _public enumerator_ `FarthestInDirection`
- L395 _public enumerator_ `ClosestToBoundsCenter`
- L396 _public enumerator_ `LargestSphere`
- L397 _public enumerator_ `ArrayOrder`

#### struct `UE::Geometry::MedialAxis::FSkeletonSubdivider`  
`struct FSkeletonSubdivider`  
_L438-467_
- L441 _public member_ `TFunction<double(const FSphere& A, const FSphere& B)> GetTargetEdgeLength;` — Function to compute a new target edge length from the medial spheres on the current edge
- L444 _public member_ `bool bSubdivideOnSurfaces = false;` — If true, allow subdividing edges that have associated triangles (also splitting these triangles)
- L447 _public member_ `double ReassignClusterPosErrorWt = .2;` — When re-clustering for subdivided edges, weight to use for the position error term. Equivalent in meaning to PosErrorWt in FSkeletonViaSampling.
- L450 _public member_ `bool bReprojectMedialSpheres = false;` — If true, project newly-added spheres to the medial axis. Otherwise, new spheres will linearly interpolate their source edge spheres.
- L454 _public prototype_ `template<typename MeshType> void Subdivide(FMedialSkeleton& Skeleton, const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<FVector3d(int32)> GetVertexNormal, TFunctionRef<int32(int32)> VIDtoWeldVIDFn, const TFastWindingTree<MeshType>* MeshFWTree = nullptr);`
- L457 _public function_ `template<typename MeshType> void Subdivide(FMedialSkeleton& Skeleton, const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<bool(int32)> OptionalBoundaryVertexFilter = [](int32)->bool { return false; }, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER, const TFastWindingTree<MeshType>* MeshFWTree = nullptr);`
- L457 _public prototype_ `template<typename MeshType> void Subdivide(FMedialSkeleton& Skeleton, const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<bool(int32)> OptionalBoundaryVertexFilter = [](int32)->bool { return false; }, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER, const TFastWindingTree<MeshType>* MeshFWTree = nullptr);`
- L459 _public function_ `void Subdivide(FMedialSkeleton& Skeleton, const TMeshAABBTree3<FDynamicMesh3>& MeshBVH, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER, const TFastWindingTree<FDynamicMesh3>* MeshFWTree = nullptr)`
- L466 _public prototype_ `void Subdivide(FMedialSkeleton& Skeleton);` — Subdivide a skeleton without referencing an associated mesh. Will clear the medial skeleton's VIDtoClusterIndex map, and will ignore bReprojectMedialSpheres

#### struct `UE::Geometry::MedialAxis::FSkeletonSimplifier`  
`struct FSkeletonSimplifier`  
_L469-527_
- L475 _public member_ `int32 MinSpheres = 1;` — Stop simplifying at this sphere count
- L478 _public member_ `double QEMErrorThreshold = -1;` — If positive, will not collapse edges if it would introduce more error than this threshold. Note: Error value is defined by the internal accumulated quadric metric, *not* a straightforward distance.
- L481 _public member_ `double EdgeLengthThreshold = -1;` — If positive, the maximum edge length to consider for collapse
- L484 _public member_ `double SphereRadiusThreshold = -1;` — If positive, the maximum medial sphere radius to consider for collapse (will not collapse if both cluster's medial sphere radii on an edge are larger than this)
- L489 _public member_ `double SphereOverlapThreshold = -1;` — If positive, will only collapse edges with medial spheres whose overlap depth is at least this fraction of the smaller sphere's diameter -- so at 1.0 we will only simplify an edge if the smaller sphere is fully contained inside the larger (A degenerate zero-radius sphere is considered to fully overlap any sphere it touches.)
- L492 _public member_ `bool bOnlySimplifySurfaces = false;` — If true, only simplify edges that have triangles associated
- L496 _public member_ `double ClusterSkeletonDistanceWt = .5;` — How much the simplifier should attempt to remain close to the initial skeleton, vs attempting to keep medial spheres close to the mesh surface. Relative term, should be in the [0,1] range. At 0, the original skeleton will not be considered; at 1, the mesh surface will not be considered.
- L499 _public member_ `bool bPreventEdgeSurfaceIntersections = true;` — If true, prevent collapses that would introduce intersections between skeleton edges and the mesh
- L506 _public member_ `double ClusterRegularizeWeight = FMathd::ZeroTolerance;` — Regularization weight encouraging skeleton clusters to keep their original positions and radii.
- L509 _public member_ `bool bSplitThinTriEdges = true;` — Whether to split edges attached to skinny triangles, as a pre-process before simplifying, which can help add useful degrees of freedom to the simplifier
- L511 _public member_ `double SplitThinTriEdgeAngleThresholdDeg = 120;` — Minimum angle of triangle opposite an edge at which to potentially split the edge
- L513 _public member_ `double SplitThinTriEdgePosErrorWt = .2;` — When re-clustering for split edges, weight to use for the position error term. Equivalent in meaning to PosErrorWt in FSkeletonViaSampling.
- L517 _public prototype_ `template<typename MeshType> void Simplify(FMedialSkeleton& Skeleton, const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<FVector3d(int32)> GetVertexNormal, TFunctionRef<int32(int32)> VIDtoWeldVIDFn);`
- L520 _public function_ `template<typename MeshType> void Simplify(FMedialSkeleton& Skeleton, const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<bool(int32)> OptionalBoundaryVertexFilter = [](int32)->bool { return false; }, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER);`
- L520 _public prototype_ `template<typename MeshType> void Simplify(FMedialSkeleton& Skeleton, const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<bool(int32)> OptionalBoundaryVertexFilter = [](int32)->bool { return false; }, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER);`
- L522 _public function_ `void Simplify(FMedialSkeleton& Skeleton, const TMeshAABBTree3<FDynamicMesh3>& MeshBVH, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER)`

#### struct `UE::Geometry::MedialAxis::FSkeletonViaSampling`  
`struct FSkeletonViaSampling`  
_L532-634_
- desc: Implementation/adaptation of "Dynamic Skeletonization via Variational Medial Skeletal Sampling" by Huang et al with some surface-focused additions -- optionally uses raycasts to guide refinement, and fast winding to guide medial-sphere projection
- L537 _public member_ `int32 MaxSpheres = 10;` — Stop at this sphere count
- L539 _public member_ `double MinClusterErrorToSplit = .1;` — Do not split a cluster if its max error is below this threshold
- L541 _public member_ `double PosErrorWt = .2;` — Weight for the position error term. Relative to plane error term, so normal and position error weights sum to 1. Should be in the (0,1] range.
- L543 _public member_ `bool bSplitClustersIfEdgesIntersectSurface = true;` — Whether to test medial skeleton edges for intersection w/ the input surface, and try to refine where these intersections are found
- L545 _public member_ `double ErrorScaleNearEdgeSurfaceIntersection = 10.;` — Factor to scale vertex error near skeleton-edge/input-surface intersections
- L547 _public member_ `int32 MinClusterSizeToKeep = 4;` — Clusters with fewer vertices than this will be discarded
- L550 _public member_ `FShrinkMedialBall ShrinkMedial;` — Settings for the medial ball shrinking, used to initialize medial spheres and to project spheres into the surface
- L553 _public member_ `TOptional<FSkeletonSimplifier> Simplifier;` — Optional simplifier, to be run after generating the initial skeleton. Saves re-computing some values compared to running the simplifier separately after.
- L561 _public member_ `int32 MaxSplitPerIteration = -1;` — Maximum cluster splits to apply per iteration (if > 0) -- Setting this to a low value can force the algorithm to target higher error more aggressively, at the cost of requiring many more full iterations. Prefer using MaxSplitFractionPerIteration and MinFractionOfMaxErrorToSplit instead, which scale better with the number of clusters.
- L564 _public member_ `double MaxSplitFractionPerIteration = .2;` — Maximum fraction of current cluster count to split per iteration (if > 0) -- Functionally similar to MaxSplitPerIteration but scales better with larger cluster counts
- L568 _public member_ `double MinFractionOfMaxErrorToSplit = .75;` — Minimum vertex error to allow a cluster split, as fraction of current maximum vertex error -- This helps to avoid splitting relatively low-error regions when there is significantly-higher error elsewhere since the higher error region will often split into multiple clusters that should all be split before the low error region
- L576 _public member_ `int8 OptimizeSpheresForIterationsPostClusterChange = 2;` — Number of full passes (top-level skeleton building iterations) to keep optimizing spheres after the cluster vertex assignments have changed This allows us to 'sleep' the spheres for clusters where vertices have not changed. Note: Should generally be at least 1 so that at least one optimization pass is applied. Higher values will allow for the optimization to smooth out the result of the sphere projection, (since projection happens separately after the optimization) and potentially amortize gauss-newton iterations over multiple passes -- i.e., one could try raising this value and lowering MaxGaussNewtonIterations.
- L578 _public member_ `int32 MaxGaussNewtonIterations = 10;` — Maximum number of gauss-newton iterations to apply to improve sphere fit
- L580 _public member_ `double GaussNewtonConvergenceThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER;` — Stop optimization if the norm of the change in sphere parameters is less than this
- L582 _public member_ `int32 MinClusterSizeToOptimize = 4;` — Minimum number of vertices in a cluster below which we will not optimize (because the optimization may not capture a good medial sphere if it has too few samples)
- L584 _public member_ `int32 UseLocalClusterVertexReassignmentAtClusterCount = 100;` — Number of clusters at which to switch to local cluster assignment updates, rather than global searches. If < 0, always use global search.
- L597 _public prototype_ `template<typename MeshType> FMedialSkeleton ComputeSkeleton(const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<FVector3d(int32)> GetVertexNormal, TFunctionRef<int32(int32)> VIDtoWeldVIDFn, const TFastWindingTree<MeshType>* MeshFWTree = nullptr);` — Compute mesh skeleton Current Supported Mesh Types: FDynamicMesh3, FTriangleMeshAdapterd @param MeshBVH BVH of the surface @param GetVertexNormal Helper to provide per-vertex surface normals @param VIDtoWeldVIDFn Mapping from vertex ID to implicit 'welded' vertex ID, to handle cases where multiple vertices should be treated as one @param MeshFWTree Optional fast winding tree; if provided will be used for more-robust medial sphere projection
- L610 _public function_ `template<typename MeshType> FMedialSkeleton ComputeSkeleton(const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<bool(int32)> OptionalWeldVertexFilter = [](int32)->bool {return true;}, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER, const TFastWindingTree<MeshType>* MeshFWTree = nullptr);` — Compute mesh skeleton This version will compute vertex normals for you, and will optionally consider near-coincident vertices as welded Current Supported Mesh Types: FDynamicMesh3, FTriangleMeshAdapterd @param MeshBVH BVH of the surface @param OptionalWeldVertexFilter Optionally filter what vertices are candidates to be welded. Return true if the vertex is a candidate to weld. @param ImplicitVertexNormalWeldThreshold If > 0, when computing vertex normals will consider coincident boundary vertices as implicitly welded if they're closer than this threshold distance @param MeshFWTree Optional fast winding tree; if provided will be used for more-robust medial sphere projection
- L610 _public prototype_ `template<typename MeshType> FMedialSkeleton ComputeSkeleton(const TMeshAABBTree3<MeshType>& MeshBVH, TFunctionRef<bool(int32)> OptionalWeldVertexFilter = [](int32)->bool {return true;}, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER, const TFastWindingTree<MeshType>* MeshFWTree = nullptr);` — Compute mesh skeleton This version will compute vertex normals for you, and will optionally consider near-coincident vertices as welded Current Supported Mesh Types: FDynamicMesh3, FTriangleMeshAdapterd @param MeshBVH BVH of the surface @param OptionalWeldVertexFilter Optionally filter what vertices are candidates to be welded. Return true if the vertex is a candidate to weld. @param ImplicitVertexNormalWeldThreshold If > 0, when computing vertex normals will consider coincident boundary vertices as implicitly welded if they're closer than this threshold distance @param MeshFWTree Optional fast winding tree; if provided will be used for more-robust medial sphere projection
- L620 _public function_ `FMedialSkeleton ComputeSkeleton(const TMeshAABBTree3<FDynamicMesh3>& MeshBVH, double ImplicitVertexNormalWeldThreshold = UE_DOUBLE_KINDA_SMALL_NUMBER, const TFastWindingTree<FDynamicMesh3>* MeshFWTree = nullptr)` — Compute mesh skeleton This version will compute vertex normals for you, and will optionally consider near-coincident boundary vertices as welded @param MeshBVH BVH of the surface @param ImplicitVertexNormalWeldThreshold If > 0, when computing vertex normals will consider coincident boundary vertices as implicitly welded if they're closer than this threshold distance @param MeshFWTree Optional fast winding tree; if provided will be used for more-robust medial sphere projection
- L629 _private prototype_ `void RemoveSmallClusters(FMedialSkeleton& Result, TArray<int32>& InOutClusterSize, TArray<int32>& OutRemapClusters, TArray<std::atomic<int8>>& OutUpdatedClusters, TFunctionRef<void(int32)> AssignVertexCluster);` — Helper to remove clusters smaller than MinClusterSizeToKeep

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)
- L22 _namespace_ `namespace MedialAxis` (scope `UE::Geometry`)
- L165 _function_ `` (scope `UE::Geometry::MedialAxis::FShrinkMedialBall::FindWithImplicitWeld`)
- L230 _function_ `` (scope `UE::Geometry::MedialAxis::FShrinkMedialBall::Project`)
- L240 _function_ `InOutToProject = Find(MeshBVH, ClosePoint, RadiusSearchDir, false, InitialSearchRadius, [](int32 TID) {return false;});` (scope `UE::Geometry::MedialAxis::FShrinkMedialBall::Project`)
- L462 _function_ `Subdivide(Skeleton, MeshBVH, [&Mesh](int32 VID)->bool {return Mesh.IsBoundaryVertex(VID);}, ImplicitVertexNormalWeldThreshold, MeshFWTree);` (scope `UE::Geometry::MedialAxis::FSkeletonSubdivider::Subdivide`)
- L525 _function_ `Simplify(Skeleton, MeshBVH, [&Mesh](int32 VID)->bool {return Mesh.IsBoundaryVertex(VID);}, ImplicitVertexNormalWeldThreshold);` (scope `UE::Geometry::MedialAxis::FSkeletonSimplifier::Simplify`)
- L623 _function_ `return ComputeSkeleton(MeshBVH, [&Mesh](int32 VID)->bool {return Mesh.IsBoundaryVertex(VID);}, ImplicitVertexNormalWeldThreshold, MeshFWTree);` (scope `UE::Geometry::MedialAxis::FSkeletonViaSampling::ComputeSkeleton`)

### `Plugins/Runtime/GeometryProcessing/Source/GeometryAlgorithms/Public/XAtlasWrapper.h` (Public)


#### struct `XAtlasWrapper::XAtlasChartOptions`  
`struct XAtlasChartOptions`  
_L11-30_
- L13 _public member_ `XAtlasParameterizeFunc ParamFunc = nullptr;`
- L15 _public member_ `float MaxChartArea = 0.0f;` — Don't grow charts to be larger than this. 0 means no limit.
- L16 _public member_ `float MaxBoundaryLength = 0.0f;` — Don't grow charts to have a longer boundary than this. 0 means no limit.
- L19 _public member_ `float NormalDeviationWeight = 2.0f;` — Weights determine chart growth. Higher weights mean higher cost for that metric.
- L20 _public member_ `float RoundnessWeight = 0.01f;`
- L21 _public member_ `float StraightnessWeight = 6.0f;`
- L22 _public member_ `float NormalSeamWeight = 4.0f;` — If > 1000, normal seams are fully respected.
- L23 _public member_ `float TextureSeamWeight = 0.5f;`
- L25 _public member_ `float MaxCost = 2.0f;` — If total of all metrics * weights > maxCost, don't grow chart. Lower values result in more charts.
- L26 _public member_ `uint32_t MaxIterations = 1;` — Number of iterations of the chart growing and seeding phases. Higher values result in better charts.
- L28 _public member_ `bool bUseInputMeshUvs = false;` — Use MeshDecl::vertexUvData for charts.
- L29 _public member_ `bool bFixWinding = false;` — Enforce consistent texture coordinate winding.

#### struct `XAtlasWrapper::XAtlasPackOptions`  
`struct XAtlasPackOptions`  
_L32-67_
- L35 _public member_ `uint32_t MaxChartSize = 0;` — Charts larger than this will be scaled down. 0 means no limit.
- L38 _public member_ `uint32_t Padding = 0;` — Number of pixels to pad charts with.
- L43 _public member_ `float TexelsPerUnit = 0.0f;` — Unit to texel scale. e.g. a 1x1 quad with texelsPerUnit of 32 will take up approximately 32x32 texels in the atlas. If 0, an estimated value will be calculated to approximately match the given resolution. If resolution is also 0, the estimated value will approximately match a 1024x1024 atlas.
- L48 _public member_ `uint32_t Resolution = 0;` — If 0, generate a single atlas with texelsPerUnit determining the final resolution. If not 0, and texelsPerUnit is not 0, generate one or more atlases with that exact resolution. If not 0, and texelsPerUnit is 0, texelsPerUnit is estimated to approximately match the resolution.
- L51 _public member_ `bool bBilinear = true;` — Leave space around charts for texels that would be sampled by bilinear filtering.
- L54 _public member_ `bool bBlockAlign = false;` — Align charts to 4x4 blocks. Also improves packing speed, since there are fewer possible chart locations to consider.
- L57 _public member_ `bool bBruteForce = false;` — Slower, but gives the best result. If false, use random chart placement.
- L60 _public member_ `bool bCreateImage = false;` — Create Atlas::image
- L63 _public member_ `bool bRotateChartsToAxis = true;` — Rotate charts to the axis of their convex hull.
- L66 _public member_ `bool bRotateCharts = true;` — Rotate charts to improve packing.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace XAtlasWrapper`
- L9 _typedef_ `typedef void (*XAtlasParameterizeFunc)(const float* Positions, float* TexCoords, uint32_t VertexCount, const uint32_t* Indices, uint32_t IndexCount);` (scope `XAtlasWrapper`)
- L70 _prototype_ `bool ComputeUVs(const TArray<int32>& IndexBuffer, const TArray<FVector3f>& VertexBuffer, const XAtlasChartOptions& ChartOptions, const XAtlasPackOptions& PackOptions, TArray<FVector2D>& UVVertexBuffer, TArray<int32>& UVIndexBuffer, TArray<int32>& VertexRemapArray);` (scope `XAtlasWrapper`)
