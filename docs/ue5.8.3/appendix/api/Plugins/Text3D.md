# Plugins / Text3D

- module root: `Plugins/VirtualProduction/Text3D/Source/Text3D`
- headers: 59; symbols: 1611
- symbol kinds: class=51, delegate=6, enum=17, enumerator=68, function=234, macro=3, member=431, namespace=45, prototype=699, struct=37, typedef=10, variable=10
- PrivateDependencyModuleNames: DeveloperSettings, FreeType2, GeometryAlgorithms, GeometryCore, GeometryFramework, GeometryScriptingCore, HarfBuzz, ICU, MeshDescription, MeshMergeUtilities, Slate, SlateCore, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyph.h` (Private)


#### struct `FText3DPolygonGroup`  
`struct FText3DPolygonGroup`  
_L15-19_
- L17 _public member_ `int32 FirstVertex;`
- L18 _public member_ `int32 FirstTriangle;`

#### class `FText3DGlyph`  
`class FText3DGlyph`  
_L23-39_
- L26 _public prototype_ `FText3DGlyph();`
- L28 _public prototype_ `void Build(FText3DCachedMesh& InMesh, EText3DMeshType InMeshType, UMaterialInterface* InDefaultMaterial);`
- L30 _public prototype_ `const FMeshDescription& GetMeshDescription() const;`
- L31 _public prototype_ `FMeshDescription& GetMeshDescription();`
- L32 _public prototype_ `FStaticMeshAttributes& GetStaticMeshAttributes();`
- L33 _public prototype_ `TText3DGroupList& GetGroups();`
- L36 _private member_ `FMeshDescription MeshDescription;`
- L37 _private member_ `FStaticMeshAttributes StaticMeshAttributes;`
- L38 _private member_ `TText3DGroupList Groups;`

#### Free symbols / members of external scopes

- L21 _typedef_ `using TText3DGroupList = TArray<FText3DPolygonGroup, TFixedAllocator<static_cast<int32>(EText3DGroupType::TypeCount)>>;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphArrangement.h` (Private)


#### struct `FText3DGlyphArrangement`  
`struct FText3DGlyphArrangement`  
_L12-50_
- desc: @brief Modified copy of FArrangement2d, has edge directions
- L14 _public typedef_ `using FIndex2i = UE::Geometry::FIndex2i;`
- L15 _public typedef_ `using FSegment2f = UE::Geometry::FSegment2f;`
- L16 _public typedef_ `using FSegment2d = UE::Geometry::FSegment2d;`
- L17 _public typedef_ `using FAxisAlignedBox2f = UE::Geometry::FAxisAlignedBox2f;`
- L19 _public member_ `UE::Geometry::FDynamicGraph2d Graph;`
- L20 _public member_ `UE::Text3D::FPointHashGrid2d PointHash;`
- L21 _public member_ `TMap<int32, bool> Directions;` — bool - from A to B
- L23 _public member_ `static constexpr double VertexSnapTol = 0.001;`
- L25 _public prototype_ `explicit FText3DGlyphArrangement(const FAxisAlignedBox2f& InBoundsHint);`
- L26 _public prototype_ `void Insert(const FSegment2f& Segment);`
- L43 _protected prototype_ `int32 InsertPoint(const FVector2d& InPoint, double InTol = 0);`
- L44 _protected prototype_ `bool InsertSegment(FVector2d InA, FVector2d InB, double InTol = 0);`
- L45 _protected prototype_ `UE::Geometry::FIndex2i SplitSegmentAtDistance(int InEID, double InDistance, double InTol);`
- L46 _protected prototype_ `int32 FindExistingVertex(const FVector2d& InPoint) const;`
- L47 _protected prototype_ `int32 FindNearestVertex(const FVector2d& InPoint, double InSearchRadius, int InIgnoreVID = -1) const;`
- L48 _protected prototype_ `bool FindIntersectingEdges(const FVector2d& InA, const FVector2d& InB, TArray<FIntersection>& OutHits, double InTol = 0) const;`
- L49 _protected prototype_ `bool FindIntersectingVertices(const FSegment2d& InSegmentAB, int32 InVIDA, int32 InVIDB, TArray<FSegmentPoint>& OutHits, double InTol = 0);`

#### struct `FText3DGlyphArrangement::FSegmentPoint`  
`struct FSegmentPoint`  
_L29-33_
- L31 _public member_ `double T;`
- L32 _public member_ `int VID;`

#### struct `FText3DGlyphArrangement::FIntersection`  
`struct FIntersection`  
_L35-41_
- L37 _public member_ `int EID;`
- L38 _public member_ `int SideX;`
- L39 _public member_ `int SideY;`
- L40 _public member_ `UE::Geometry::FIntrSegment2Segment2d Intr;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphContour.h` (Private)


#### class `FText3DGlyphContour`  
`class FText3DGlyphContour final : public TArray<FText3DGlyphPartPtr>`  
_L8-34_
- inherits: `TArray<FText3DGlyphPartPtr>`
- L17 _public prototype_ `FText3DGlyphContour() = default;`
- L18 _public prototype_ `~FText3DGlyphContour();`
- L20 _public function_ `int32 Find(const FText3DGlyphPartConstPtr Edge)`
- L28 _public prototype_ `void SetNeighbours();` — Set Prev and Next in parts.
- L33 _public prototype_ `void CopyFrom(const FText3DGlyphContour& Other);` — Copy parts from other contour. @param Other - Controur from which parts should be copied.

#### struct `FText3DGlyphContour::FPathEntry`  
`struct FPathEntry`  
_L11-15_
- L13 _public member_ `int32 Prev;`
- L14 _public member_ `int32 Next;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphContourList.h` (Private)


#### class `FText3DGlyphContourList`  
`class FText3DGlyphContourList final : public TDoubleLinkedList<FText3DGlyphContour>`  
_L11-35_
- inherits: `TDoubleLinkedList<FText3DGlyphContour>`
- L14 _public prototype_ `FText3DGlyphContourList() = default;`
- L15 _public prototype_ `FText3DGlyphContourList(const FText3DGlyphContourList& Other);`
- L21 _public prototype_ `void Initialize(FText3DGlyphData& Data);` — Initialize Countours. @param Data - Needed to add vertices for split corners.
- L27 _public prototype_ `FText3DGlyphContour& Add();` — Create contour. @return Reference to created contour.
- L32 _public prototype_ `void Remove(const FText3DGlyphContour& Contour);` — Remove contour. @param Contour - Const reference to contour that should be removed.
- L34 _public prototype_ `void Reset();`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphContourNode.h` (Private)


#### struct `FText3DGlyphContourNode`  
`struct FText3DGlyphContourNode final`  
_L15-51_
- L17 _public function_ `explicit FText3DGlyphContourNode(const TOptional<FPolygon2f> InContour, const bool bInCanHaveIntersections, const bool bInClockwise) : Contour(InContour) , bCanHaveIntersections(bInCanHaveIntersections) , bClockwise(bInClockwise)`
- L24 _public member_ `TOptional<FPolygon2f> Contour;`
- L27 _public member_ `bool bCanHaveIntersections;` — Needed for dividing contours with self-intersections: default value is true, false for parts of divided contours
- L29 _public member_ `bool bClockwise;`
- L32 _public member_ `TArray<FText3DGlyphContourNode> Children;` — Contours that are inside this contour
- L35 _public function_ `void Print(int32 InDepth = 0) const` — Debug print to display contour data

#### Free symbols / members of external scopes

- L13 _typedef_ `using TText3DGlyphContourNodeShared = TSharedPtr<FText3DGlyphContourNode>;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphData.h` (Private)


#### class `FText3DGlyphData`  
`class FText3DGlyphData final`  
_L10-127_
- desc: Used to add vertices and triangles from different classes
- L17 _public prototype_ `explicit FText3DGlyphData();` — Constructor. @param InGlyph - Glyph that is being created.
- L19 _public function_ `const FText3DGlyph& GetGlyph() const`
- L24 _public function_ `FText3DGlyph& GetGlyph()`
- L34 _public prototype_ `void SetCurrentGroup(const EText3DGroupType Type, const float GroupExpandIn);` — Set group that is being created. @param Type - Group type. @param GroupExpandIn - Total expand of group (not needed now because intersections are not ready).
- L42 _public prototype_ `void PrepareSegment(const float PlannedExtrudeIn, const float PlannedExpandIn, const FVector2D NormalStartIn, const FVector2D NormalEndIn);` — Set data needed for bevelling one segment. @param PlannedExtrudeIn - Extrude. @param PlannedExpandIn - Expand. @param NormalStartIn - Normal in the start of segment. @param NormalEndIn - Normal in the end of segment.
- L48 _public prototype_ `void SetTarget(const float ExtrudeTargetIn, const float ExpandTargetIn);` — Set data for single bevelling in segment (needed for intersections). @param ExtrudeTargetIn - Extrude. @param ExpandTargetIn - Expand.
- L50 _public prototype_ `int32 AddVertices(const int32 Count);`
- L51 _public prototype_ `int32 AddVertex(const FText3DGlyphPartConstPtr& Point, const FVector2D TangentX, const FVector& TangentZ, const FVector2D TextureCoordinates = {0.f, 0.f});`
- L52 _public prototype_ `int32 AddVertex(const FVector2D Position, const FVector2D TangentX, const FVector& TangentZ, const FVector2D TextureCoordinates = {0.f, 0.f});`
- L53 _public prototype_ `int32 AddVertex(const FVector& Position, const FVector& TangentX, const FVector& TangentZ, const FVector2D TextureCoordinates);`
- L55 _public prototype_ `void AddTriangles(const int32 Count);`
- L56 _public prototype_ `void AddTriangle(const int32 A, const int32 B, const int32 C);`
- L58 _public prototype_ `float GetGroupExpand() const;`
- L60 _public prototype_ `float GetPlannedExtrude() const;`
- L61 _public prototype_ `float GetPlannedExpand() const;`
- L66 _public prototype_ `void IncreaseDoneExtrude();` — Executed after segment was beveled.
- L68 _public prototype_ `FVector ComputeTangentZ(const FText3DGlyphPartConstPtr& Edge, const float DoneExpand);`
- L76 _public prototype_ `FVector2D Expanded(const FText3DGlyphPartConstPtr& Point) const;` — FPart::Expanded for total expand value Data::ExpandTarget. @param Point - Point for which position should be computed. @return Computed position.
- L84 _public prototype_ `void FillEdge(const FText3DGlyphPartPtr& Edge, const bool bSkipLastTriangle, bool bFlipNormals = false);` — Make triangulation of edge along paths of it's vertices (from end of previous triangulation to result of points' expansion). Removes covered points' indices from paths. @param Edge - Edge that has to be filled. @param bSkipLastTriangle - Do not create last triangle (furthest from end of previous triangulation). @param bFlipNormals - Reverse the geometry facing direction.
- L87 _private member_ `FText3DGlyph Glyph;`
- L89 _private member_ `EText3DGroupType CurrentGroup;`
- L90 _private member_ `float GroupExpand;`
- L92 _private member_ `float PlannedExtrude;`
- L93 _private member_ `float PlannedExpand;`
- L95 _private member_ `FVector2D NormalStart;`
- L96 _private member_ `FVector2D NormalEnd;`
- L98 _private member_ `float ExtrudeTarget;`
- L99 _private member_ `float ExpandTarget;`
- L101 _private member_ `float DoneExtrude;`
- L104 _private member_ `int32 VertexCountBeforeAdd;`
- L105 _private member_ `int32 AddVertexIndex;`
- L107 _private member_ `int32 TriangleCountBeforeAdd;`
- L108 _private member_ `int32 AddTriangleIndex;`
- L118 _private prototype_ `FVector GetVector(const FVector2D Position, const float Height) const;` — Transform position from glyph coordinate system to 3d. @param Position - Point position. @param Height - Offset in direction orthogonal to surface of front cap. @return 3d coordinate.
- L126 _private prototype_ `void MakeTriangleFanAlongNormal(const FText3DGlyphPartConstPtr& Cap, const FText3DGlyphPartPtr& Normal, const bool bNormalIsCapNext, const bool bSkipLastTriangle);` — Make triangle fan, called from FData::FillEdge. @param Cap - Cap of triangle fan. @param Normal - Point, fan will be created along it's normal. @param bNormalIsCapNext - Normal is next point after cap or vice versa. @param bSkipLastTriangle - See FData::FillEdge.

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphLoader.h` (Private)


#### class `FText3DGlyphLoader`  
`class FText3DGlyphLoader final`  
_L21-243_
- desc: Creates glyph geometry data from a font glyphs
- L24 _public prototype_ `explicit FText3DGlyphLoader();`
- L27 _public prototype_ `FText3DGlyphContourNode GenerateContourList(const UE::Text3D::FGlyphOutline& InGlyphOutline);`
- L132 _private member_ `int32 EndIndex;`
- L133 _private member_ `TDoubleLinkedList<FVector2f> ProcessedContour;`
- L134 _private member_ `FVector2D FirstPosition;`
- L136 _private member_ `TArray<int32> Junctions;` — List of junctions in path
- L138 _private member_ `int32 VertexID;` — Current vertex that should be added to path
- L140 _private member_ `TArray<int32> DividedContourIDs;` — Path
- L143 _private prototype_ `TOptional<FPolygon2f> CreateContour(const UE::Text3D::FGlyphOutline& InGlyphOutline, int32 InContourIndex);`
- L144 _private prototype_ `TOptional<FPolygon2f> ProcessFreetypeOutline(const UE::Text3D::FGlyphOutline& InGlyphOutline, int32 InContourIndex);`
- L152 _private prototype_ `bool IsInside(const FPolygon2f& ContourA, const FPolygon2f& ContourB) const;` — Checks if ContourA is inside ContourB. @param ContourA @param ContourB
- L159 _private prototype_ `void Insert(FText3DGlyphContourNode&& NodeA, FText3DGlyphContourNode& NodeB) const;` — Insert NodeA inside NodeB. @param NodeA @param NodeB
- L165 _private prototype_ `void FixParityAndDivide(FText3DGlyphContourNode& Node, const bool bInClockwise);` — Reverse contour if it's initial parity differs from the one it should have, find self-intersections and, if found, divide to contours without self-intersections. @param Node - Function is called recursively to fix all contours inside Node->Contour. @param bInClockwise - The parity that contours listed in Node->Nodes should have.
- L167 _private prototype_ `bool RemoveBadPoints(FPolygon2f& InOutContour) const;`
- L169 _private prototype_ `bool IsBadNormal(const FPolygon2f& InContour, const int32 InPoint) const;`
- L170 _private prototype_ `bool MergedWithNext(const FPolygon2f& InContour, const int32 Point) const;`
- L172 _private prototype_ `FText3DGlyphArrangement MakeArrangement(const FPolygon2f& InContour);`
- L177 _private prototype_ `bool FindJunction(const FText3DGlyphArrangement& InArrangement);` — Find vertex that belongs to more then 2 edges and write it's ID to VertexID member. @return Was such vertex found?
- L182 _private prototype_ `bool FindRegular(const FText3DGlyphArrangement& InArrangement);` — Find vertex that belongs to 2 edges and write it's ID to VertexID member. @return Was such vertex found?
- L183 _private prototype_ `TArray<FVector2f> CopyVertices(const FText3DGlyphArrangement& InArrangement) const;`
- L188 _private prototype_ `void DetachBadContour();` — Separate bad contour (the one that is not a closed loop) from path.
- L195 _private prototype_ `void DetachFinishedContour(const int32 RepeatedJunctionIndex, const TArray<FVector2f>& InitialVertices, FText3DGlyphContourNode& RootForDetaching);` — Separate closed loop from path. @param RepeatedJunctionIndex - Index of start (and end) of loop in list of junctions. @param InitialVertices - Previously copied graph vertices. @param RootForDetaching - Separate root node for detaching.
- L202 _private prototype_ `int32 FindStartOfDetachedContour(const int32 RepeatedJunctionIndex);` — Find start of contour that is detached, remove it from list of junctions. @param RepeatedJunctionIndex - Index of start (and end) of loop in list of junctions. @return Index in path of first (and last) vertex of loop.
- L207 _private prototype_ `void RemoveDetachedContourFromPath(const int32 JunctionIndexInContour);` — Remove separated contour from path. @param JunctionIndexInContour - Index in path of first (and last) vertex of loop.
- L214 _private prototype_ `void AddPoint(FText3DGlyphArrangement& InArrangement, const bool bForceJunction = false);` — Add vertex to path @param InArrangement the arrangement to query @param bForceJunction - Needed for separating last loop, it has no junctions so any other vertex has to be treated as one.
- L220 _private prototype_ `void RemoveUnneededNodes(FText3DGlyphContourNode& Node) const;` — Check what nodes have same parity as their parents and remove them, they cover the area that already is covered by parent. @param Node - Processed node.
- L228 _private prototype_ `void MergeRootForDetaching(FText3DGlyphContourNode&& RemovedNode, FText3DGlyphContourNode& RootForDetaching, FText3DGlyphContourNode& RemovedNodeParent) const;` — Merge separate root to regular one. @param RemovedNode - Contour that was divided. @param RootForDetaching - Separate root that stores result of division. @param RemovedNodeParent - Parent of contour that was divided.
- L235 _private prototype_ `int32 FindOutgoing(const FText3DGlyphArrangement& InArrangement, const int32 Junction) const;` — Choose next path direction in junction vertex. @param Junction - Vertex ID of junction. @return Edge ID of chosen direction.
- L236 _private prototype_ `bool IsOutgoing(const FText3DGlyphArrangement& InArrangement, const int32 Junction, const int32 EID) const;`
- L239 _private prototype_ `int32 GetOtherEdgeVertex(const FText3DGlyphArrangement& InArrangement, const int32 EID, const int32 VID) const;` — Copied from FDynamicGraph2d because it's private there
- L242 _private prototype_ `void SortedVtxEdges(const FText3DGlyphArrangement& InArrangement, const int32 VID, TArray<int32>& Sorted) const;` — Fixed version of FDynamicGraph2d::SortedVtxEdges

#### class `FText3DGlyphLoader::FLine`  
`class FLine final`  
_L31-39_
- L34 _public prototype_ `FLine(const FVector2D PositionIn);`
- L35 _public prototype_ `void Add(FText3DGlyphLoader* const Loader);`
- L38 _private member_ `const FVector2D Position;`

#### class `FText3DGlyphLoader::FCurve`  
`class FCurve`  
_L41-92_
- L44 _public prototype_ `FCurve(const bool bLineIn);`
- L45 _public prototype_ `virtual ~FCurve();`
- L47 _public prototype_ `void Add(FText3DGlyphLoader* const LoaderIn);`
- L60 _protected prototype_ `static bool OnOneLine(const FVector2D A, const FVector2D B, const FVector2D C);` — Check if 3 points are on one line. @param A - Point A. @param B - Point B. @param C - Point C. @return Are points on one line?
- L64 _protected member_ `const bool bLine;` — Is curve a line?
- L65 _protected member_ `FText3DGlyphLoader* Loader;`
- L67 _protected member_ `const float StartT;`
- L68 _protected member_ `const float EndT;`
- L71 _private member_ `int32 Depth;`
- L72 _private member_ `int32 MaxDepth;`
- L74 _private member_ `TDoubleLinkedList<FVector2f>::TDoubleLinkedListNode* First;`
- L75 _private member_ `TDoubleLinkedList<FVector2f>::TDoubleLinkedListNode* Last;`
- L78 _private member_ `bool bFirstSplit;` — Needed to make additional splits near start and end of curve
- L79 _private member_ `bool bLastSplit;`
- L85 _private prototype_ `void ComputeMaxDepth();` — Compute max depth (depends on curve length, step is fixed).
- L86 _private prototype_ `void Split(const FPointData& Start, const FPointData& End);`
- L87 _private prototype_ `void CheckPart(const FPointData& Start, const FPointData& End);`
- L88 _private prototype_ `virtual void UpdateTangent(FPointData* const Middle);`
- L90 _private prototype_ `virtual FVector2D Position(const float T) const = 0;`
- L91 _private prototype_ `virtual FVector2D Tangent(const float T) = 0;`

#### class `FText3DGlyphLoader::FQuadraticCurve`  
`class FQuadraticCurve final : public FCurve`  
_L94-107_
- inherits: `FCurve`
- L97 _public prototype_ `FQuadraticCurve(const FVector2D A, const FVector2D B, const FVector2D C);`
- L100 _private member_ `const FVector2D E;`
- L101 _private member_ `const FVector2D F;`
- L102 _private member_ `const FVector2D G;`
- L105 _private prototype_ `FVector2D Position(const float T) const override;`
- L106 _private prototype_ `FVector2D Tangent(const float T) override;`

#### class `FText3DGlyphLoader::FCubicCurve`  
`class FCubicCurve final : public FCurve`  
_L109-130_
- inherits: `FCurve`
- L112 _public prototype_ `FCubicCurve(const FVector2D A, const FVector2D B, const FVector2D C, const FVector2D D);`
- L115 _private member_ `const FVector2D E;`
- L116 _private member_ `const FVector2D F;`
- L117 _private member_ `const FVector2D G;`
- L118 _private member_ `const FVector2D H;`
- L121 _private member_ `bool bSharpStart;` — Sharp means that curve derivative has zero length, it's actually sharp only in middle case
- L122 _private member_ `bool bSharpMiddle;`
- L123 _private member_ `bool bSharpEnd;`
- L126 _private prototype_ `void UpdateTangent(FPointData* const Middle) override;`
- L128 _private prototype_ `FVector2D Position(const float t) const override;`
- L129 _private prototype_ `FVector2D Tangent(const float t) override;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Text3D` (scope `UE`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphMeshBuilder.h` (Private)


#### class `FText3DGlyphMeshBuilder`  
`class FText3DGlyphMeshBuilder final`  
_L18-163_
- desc: Creates the glyph mesh from glyph data
- L32 _public prototype_ `void CreateMeshes(const FText3DGlyphContourNode& InRoot, const float InExtrude, const float InBevel, const EText3DBevelType InBevelType, const int32 InBevelSegments, const bool bInOutline, const float InOutlineExpand, const EText3DOutlineType InOutlineType);` — CreateMeshes @param InRoot - Tree of contours. @param InExtrude - Orthogonal (to front cap) offset value. @param InBevel - Bevel value (bevel happens before extrude). @param InBevelType - Defines shape of beveled part. @param InBevelSegments - Segments count. @param bInOutline - Front face has outline and is not filled. @param InOutlineExpand - Offsets the outline by the specified amount. @param InOutlineType - Defines the outline behavior.
- L33 _public prototype_ `void SetFrontAndBevelTextureCoordinates(const float Bevel);`
- L34 _public prototype_ `void MirrorGroups(const float Extrude);`
- L37 _public prototype_ `void MovePivot(const FVector& InNewPivot);` — Move the mesh pivot based on pivot ratio 0-1
- L40 _public prototype_ `void BuildMesh(FText3DCachedMesh& InMesh, EText3DMeshType InMeshType, UMaterialInterface* InDefaultMaterial);` — Creates the actual mesh
- L43 _public prototype_ `FBox GetMeshBounds() const;` — Get actual glyph bounds once built
- L46 _public prototype_ `FVector GetMeshOffset() const;` — Get actual glyph offset
- L49 _private member_ `FVector MeshOffset = FVector::ZeroVector;`
- L50 _private member_ `FVector PivotOffset = FVector::ZeroVector;`
- L51 _private member_ `FText3DGlyphData Data;`
- L52 _private member_ `FText3DGlyphContourList Contours;`
- L61 _private prototype_ `void CreateFrontMesh(const FText3DGlyphContourNode& Root, const bool bOutline, const float OutlineExpand, const EText3DOutlineType InOutlineType);` — Create 'Front' part of glyph. @param Root - Tree root. @param bOutline - Front face has outline and is not filled. @param OutlineExpand - Offsets the outline by the specified amount. @param InOutlineType - Defines the outline behavior.
- L69 _private prototype_ `void CreateBevelMesh(const float Bevel, const EText3DBevelType Type, const int32 BevelSegments);` — Create 'Bevel' part of glyph (actually half of it, will be mirrored later). @param Bevel - Bevel value (bevel happens before extrude). @param Type - Defines shape of beveled part. @param BevelSegments - Segments count.
- L78 _private prototype_ `void CreateExtrudeMesh(float Extrude, float Bevel, const EText3DBevelType Type, bool bFlipNormals = false);` — Create 'Extrude' part of glyph. @param Extrude - Extrude value. @param Bevel - Bevel value (bevel happens before extrude). @param Type - Defines shape of beveled part. @param bFlipNormals - Reverse the geometry facing direction.
- L84 _private prototype_ `void CreateOutlineMesh(float InOutlineExpand);` — Create 'Outline' part of glyph. Not compatible with Bevel @param InOutlineExpand - outline expansion value.
- L89 _private prototype_ `void MirrorGroup(const EText3DGroupType TypeIn, const EText3DGroupType TypeOut, const float Extrude);` — Copies and reflect source group into a destination group based on extrusion value
- L96 _private prototype_ `void AddToVertexCount(const FText3DGlyphContourNode& Node, int32& OutVertexCount);` — Recursively compute vertex count in tree. @param Node - Tree node. @param OutVertexCount - Pointer to counter.
- L104 _private prototype_ `void TriangulateAndConvert(const FText3DGlyphContourNode& Node, int32& OutVertexIndex, const bool bOutline, const EText3DOutlineType InOutlineType);` — Triangulate solid region with holes and convert contours to old format. @param Node - Tree node. @param OutVertexIndex - Pointer to last used vertex index. @param bOutline - Front face has outline and is not filled.
- L106 _private prototype_ `void BevelLinearWithSegments(const float Extrude, const float Expand, const int32 BevelSegments, const FVector2D Normal);`
- L107 _private prototype_ `void BevelCurve(const float Angle, const int32 BevelSegments, TFunction<FVector2D(const float CurrentCos, const float CurrentSin, const float NextCos, const float Next)> ComputeOffset);`
- L108 _private prototype_ `void BevelWithSteps(const float Bevel, const int32 Steps, const int32 BevelSegments);`
- L118 _private prototype_ `void BevelLinear(const float Extrude, const float Expand, FVector2D NormalStart, FVector2D NormalEnd, const bool bSmooth);` — Bevel one segment. @param Extrude - Documented in ContourList.h. @param Expand - Documented in ContourList.h. @param NormalStart - Normal at start of segment (minimum DoneExpand). @param NormalEnd - Normal at end of segment (maximum DoneExpand). @param bSmooth - Is angle between start of this segment and end of previous segment smooth?
- L123 _private prototype_ `void DuplicateContourVertices();` — Duplicate contour vertices (used to make sharp angle between bevel steps)
- L128 _private prototype_ `void BevelPartsWithoutIntersectingNormals();` — Continue with trivial bevel till FData::Expand.
- L134 _private prototype_ `void EmptyPaths(const FText3DGlyphPartPtr& Point) const;` — Clear PathPrev and PathNext. @param Point - Point which paths should be cleared.
- L141 _private prototype_ `void ExpandPoint(const FText3DGlyphPartPtr& Point, const FVector2D TextureCoordinates = FVector2D(0.f, 0.f));` — Same as previous function but does not cover the intersection-case. @param Point - Point that should be expanded. @param TextureCoordinates - Texcture coordinates of added vertices.
- L147 _private prototype_ `void ExpandPointWithoutAddingVertices(const FText3DGlyphPartPtr& Point);` — Common code for expanding, vertices are added uninitialized. @param Point - Expanded point.
- L154 _private prototype_ `void AddVertexSmooth(const FText3DGlyphPartConstPtr& Point, const FVector2D TextureCoordinates);` — Add vertex for smooth point. @param Point - Expanded point. @param TextureCoordinates - Texture coordinates of added vertex.
- L162 _private prototype_ `void AddVertexSharp(const FText3DGlyphPartConstPtr& Point, const FText3DGlyphPartConstPtr& Edge, const FVector2D TextureCoordinates);` — Add vertex for sharp point. @param Point - Expanded point. @param Edge - Edge from which TangentX and TangentZ will be assigned. @param TextureCoordinates - Texture coordinates of added vertex.

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphOutline.h` (Private)


#### struct `UE::Text3D::FGlyphOutline`  
`struct FGlyphOutline`  
_L30-45_
- desc: Mirrors the struct of 'FT_Outline' to be used outside of the loaded glyph. FT_Load_Glyph is not thread-safe when using the same FT_Face, so the data needs to be saved in this struct for expensive computations to be done in multiple threads.
- L32 _public prototype_ `static FGlyphOutline MakeOutline(const FT_Outline& InOutline);`
- L35 _public member_ `TArray<FT_Vector> Points;` — Outline's points
- L38 _public member_ `TArray<FFTOutlineTagsType> Tags;` — Points flags
- L41 _public member_ `TArray<FFTOutlineContoursType> Contours;` — Contour end points
- L44 _public member_ `int32 Flags = 0;` — Outline Masks

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Text3D` (scope `UE`)
- L18 _typedef_ `using FFTOutlineTagsType = unsigned char;` (scope `UE::Text3D`)
- L19 _typedef_ `using FFTOutlineContoursType = unsigned short;` (scope `UE::Text3D`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DGlyphPart.h` (Private)


#### struct `FText3DGlyphPart`  
`struct FText3DGlyphPart final`  
_L17-95_
- desc: Part represents point and it's next edge (counterclockwise one).
- L19 _public member_ `static constexpr float CosMaxAngleSideTangent = 0.995f;`
- L20 _public member_ `static constexpr float CosMaxAngleSides = -0.9f;`
- L36 _public prototype_ `FText3DGlyphPart();`
- L37 _public prototype_ `FText3DGlyphPart(const FText3DGlyphPartConstPtr& Other);`
- L40 _public member_ `FText3DGlyphPartPtr Prev;` — Previous part.
- L43 _public member_ `FText3DGlyphPartPtr Next;` — Next part.
- L46 _public member_ `FVector2D Position;` — Position, is equal to position of last vertex in paths (in coordinate system of glyph).
- L49 _public member_ `float DoneExpand;` — Offset in surface of front cap that this point already made.
- L51 _public member_ `FVector2D TangentX;`
- L54 _public member_ `FVector2D Normal;` — Point normal, a bisector of angle.
- L57 _public member_ `bool bSmooth;` — If true, previous and next edges are in one smoothing group.
- L59 _public member_ `FVector2D InitialPosition;`
- L63 _public member_ `TArray<int32> PathPrev;` — Path used for triangulation of previous edge.
- L66 _public member_ `TArray<int32> PathNext;` — Path used for triangulation of next edge.
- L69 _public member_ `float AvailableExpandNear;` — Offset needed for an IntersectionNear to happen.
- L72 _public member_ `FAvailableExpandsFar AvailableExpandsFar;` — List of pairs (edge, offset) for IntersectionFar.
- L74 _public prototype_ `float TangentsDotProduct() const;`
- L75 _public prototype_ `float Length() const;`
- L77 _public prototype_ `void ResetDoneExpand();`
- L78 _public prototype_ `void ComputeTangentX();`
- L79 _public prototype_ `bool ComputeNormal();`
- L80 _public prototype_ `void ComputeSmooth();`
- L82 _public prototype_ `bool ComputeNormalAndSmooth();`
- L84 _public prototype_ `void ResetInitialPosition();`
- L85 _public prototype_ `void ComputeInitialPosition();`
- L87 _public prototype_ `void DecreaseExpandsFar(const float Delta);`
- L94 _public prototype_ `FVector2D Expanded(const float Value) const;` — Compute position to which point will be expanded. @param Value - Offset in surface of front cap. @return Computed position.

#### class `FText3DGlyphPart::FAvailableExpandsFar`  
`class FAvailableExpandsFar final : public TMap<FText3DGlyphPartPtr, float>`  
_L22-34_
- inherits: `TMap<FText3DGlyphPartPtr,float>`
- L25 _public function_ `void Add(const FText3DGlyphPartConstPtr Edge, const float Value)`
- L30 _public function_ `void Remove(const FText3DGlyphPartConstPtr Edge)`

#### Free symbols / members of external scopes

- L13 _typedef_ `using FText3DGlyphPartPtr = TSharedPtr<FText3DGlyphPart>;`
- L14 _typedef_ `using FText3DGlyphPartConstPtr = TSharedPtr<const FText3DGlyphPart>;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/GeometryBuilders/Text3DPointHashGrid2d.h` (Private)


#### class `UE::Text3D::FPointHashGrid2d`  
`class FPointHashGrid2d`  
_L16-52_
- desc: This is a simplified re-implementation of TPointHashGrid2 but without the FCriticalSection to allow for copying and because it was unnecessary in our context.
- L24 _public prototype_ `FPointHashGrid2d(double InCellSize, int32 InInvalidValue);` — Construct 2D hash grid @param InCellSize size of grid cells @param InInvalidValue this value will be returned by queries if no valid result is found (e.g. bounded-distance query)
- L27 _public prototype_ `int32 GetInvalidValue() const;` — Invalid grid value
- L34 _public prototype_ `void InsertPoint(int32 InValue, const FVector2D& InPosition);` — Insert at given position. @param InValue the point/value to insert @param InPosition the position associated with this value
- L44 _public prototype_ `TPair<int32, double> FindNearestInRadius(const FVector2D& InQueryPoint, double InRadius , TFunctionRef<double(int32)> InDistanceSqFunc , TFunctionRef<bool(int32)> InIgnoreFunc = [](const int32 data) { return false; }) const;` — Find nearest point in grid, within a given sphere @param InQueryPoint the center of the query sphere @param InRadius the radius of the query sphere @param InDistanceSqFunc Function you provide which measures the distance between QueryPoint and a Value @param InIgnoreFunc optional Function you may provide which will result in a Value being ignored if IgnoreFunc(Value) returns true @return the found pair (Value,DistanceFunc(Value)), or (InvalidValue,MaxDouble) if not found
- L46 _public function_ `, TFunctionRef<bool(int32)> InIgnoreFunc = [](const int32 data)`
- L49 _private member_ `TMultiMap<UE::Geometry::FVector2i, int32> Hash;`
- L50 _private member_ `UE::Geometry::FScaleGridIndexer2d Indexer;`
- L51 _private member_ `int32 InvalidValue;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Text3D` (scope `UE`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/LayoutBuilders/Text3DLayout.h` (Private)


#### class `FText3DLayout`  
`class FText3DLayout final : public FTextLayout`  
_L9-28_
- inherits: `FTextLayout`
- desc: An implementation of FTextLayout, which discards most Slate widget specific functionality.
- L13 _public prototype_ `explicit FText3DLayout(const FTextBlockStyle& InStyle = FTextBlockStyle::GetDefault());` — Optionally provide a custom TextBlock style.
- L15 _public function_ `const FTextBlockStyle& GetTextStyle() const`
- L22 _protected member_ `FTextBlockStyle TextStyle;` — Parameters relevant to text layout.
- L25 _protected prototype_ `virtual TSharedRef<IRun> CreateDefaultTextRun( const TSharedRef<FString>& NewText, const FTextRange& NewRange) const override;` — Required but unused override.

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/LayoutBuilders/Text3DLayoutShaper.h` (Private)


#### class `FText3DLayoutShaper`  
`class FText3DLayoutShaper final`  
_L21-52_
- desc: A singleton that handles shaping operations and writes the result to a provided TextLayout.
- L25 _public prototype_ `static TSharedPtr<FText3DLayoutShaper> Get();` — Returns TextShaper singleton.
- L31 _public prototype_ `void ShapeBidirectionalText( const TSharedPtr<FSlateStyleSet>& InStyles, const FTextBlockStyle& InDefaultStyle, const FString& Text, const TSharedPtr<FTextLayout>& TextLayout, const TSharedPtr<FRichTextLayoutMarshaller>& TextMarshaller, TArray<UE::Text3D::Layout::FGlyphLine>& OutShapedLines);` — Arranges the provided text to match the requested layout, accounting for scale, offsets etc. Analogous to FSlateFontCache::ShapeBidirectionalText.
- L43 _public function_ `explicit FText3DLayoutShaper(FPrivateToken)`
- L50 _private prototype_ `FText3DLayoutShaper(const FText3DLayoutShaper&) = delete;`
- L51 _private prototype_ `FText3DLayoutShaper& operator=(const FText3DLayoutShaper&) = delete;`

#### struct `FText3DLayoutShaper::FPrivateToken`  
`struct FPrivateToken`  
_L40-40_
- L40 _public prototype_ `struct FPrivateToken`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Text3D` (scope `UE`)
- L15 _namespace_ `namespace Layout` (scope `UE::Text3D`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/LayoutBuilders/Text3DShapedGlyphLine.h` (Private)


#### struct `UE::Text3D::Layout::FGlyphEntry`  
`struct FGlyphEntry`  
_L16-42_
- desc: Contains text glyph information for a single character
- L18 _public prototype_ `FGlyphEntry() = default;`
- L19 _public function_ `FGlyphEntry(const FShapedGlyphEntry& InEntry) : Entry(InEntry)`
- L25 _public member_ `FName StyleTag = NAME_None;` — Style applied on this entry
- L28 _public member_ `float Size = 48.f;` — Actual size of the glyph
- L31 _public member_ `FShapedGlyphEntry Entry;` — Actual entry for the glyph
- L39 _public member_ `FT_Pos FaceSizeMetricsAscender = 0;` — Cached metrics when the glyph is shaped. In between Text3D incremental build phases (specifically between Layout Prepare Build and Layout Pre Renderer Update), size metrics might change for an external reason (e.g. a text block widget with the same font).
- L40 _public member_ `FT_Pos FaceSizeMetricsDescender = 0;`

#### struct `UE::Text3D::Layout::FGlyphLine`  
`struct FGlyphLine`  
_L45-70_
- desc: Contains text line metric with sufficient information to fetch and transform each character.
- L48 _public prototype_ `float GetWidthAdvance(const int32 InIndex, const float InKerning, const float InWordSpacing) const;` — Get's the offset from the previous character, accounting for kerning and word spacing.
- L51 _public member_ `TArray<FGlyphEntry> Glyphs;` — The corresponding shaped glyph for each character in this line of text.
- L54 _public member_ `float Width = 0.0f;` — Stored result of line width
- L57 _public member_ `TArray<float> GlyphAdvances;` — Glyph advance on this line
- L60 _public member_ `TextBiDi::ETextDirection TextDirection = TextBiDi::ETextDirection::LeftToRight;` — Direction of the text in the line
- L63 _public member_ `float MaxFontHeight = 0.f;` — Max font height for this line calculated based on MaxFontAscender and MaxFontDescender
- L66 _public member_ `float MaxFontAscender = 0.f;` — Positive value representing max height above baseline
- L69 _public member_ `float MaxFontDescender = 0.f;` — Positive value representing max height below baseline

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Text3D` (scope `UE`)
- L13 _namespace_ `namespace Layout` (scope `UE::Text3D`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/LayoutBuilders/Text3DShapedGlyphText.h` (Private)


#### struct `UE::Text3D::Layout::FGlyphText`  
`struct FGlyphText`  
_L15-45_
- desc: Contains text metrics with sufficient information to fetch and transform each line.
- L18 _public prototype_ `static bool IsValidGlyph(const FGlyphEntry& InGlyph);` — Check if a glyph is valid and visible (can be rendered)
- L20 _public prototype_ `FGlyphText();`
- L22 _public prototype_ `void Reset();`
- L23 _public prototype_ `void CalculateWidth();`
- L26 _public member_ `TArray<float> Kernings;` — Individual character kerning
- L29 _public member_ `TArray<TSharedPtr<FFreeTypeFace>> FontFaces;` — Individual character font faces
- L32 _public member_ `float Tracking;` — General tracking for all characters
- L35 _public member_ `float WordSpacing;` — Spacing between words
- L38 _public member_ `float MaxWidth;` — Maximum width allowed
- L41 _public member_ `bool bWrap;` — Whether to wrap words
- L44 _public member_ `TArray<FGlyphLine> Lines;` — Lines calculated based on current text

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Text3D` (scope `UE`)
- L12 _namespace_ `namespace Layout` (scope `UE::Text3D`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Logs/Text3DLogs.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogText3D, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogText3D, Log, All);`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Renderers/DynamicMesh/Text3DDynamicMeshRenderer.h` (Private)


#### class `UText3DDynamicMeshRenderer`  
`class UText3DDynamicMeshRenderer : public UText3DRendererBase`  
_L19-102_
- reflection: `UCLASS(DisplayName="DynamicMeshRenderer", ClassGroup="Text3D", HideCategories=(Renderer))`
- inherits: `UText3DRendererBase`
- desc: Renderer that uses a single dynamic mesh component to render all characters Text3DComponent - Text3DDynamicMesh
- L59 _protected prototype_ `virtual void OnCreate() override;`
- L60 _protected prototype_ `virtual void OnUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L61 _protected prototype_ `virtual void OnClear() override;`
- L62 _protected prototype_ `virtual void OnDestroy() override;`
- L63 _protected prototype_ `virtual EText3DMeshType GetMeshType() const override;`
- L64 _protected prototype_ `virtual FName GetFriendlyName() const override;`
- L65 _protected prototype_ `virtual FBox OnCalculateBounds() const override;`
- L66 _protected prototype_ `virtual void OnIterateManagedPrimitives(TFunctionRef<void(TNotNull<const UPrimitiveComponent*>)> InFunc) const override;`
- L68 _protected prototype_ `virtual void OnDebugModeEnabled() override;`
- L69 _protected prototype_ `virtual void OnDebugModeDisabled() override;`
- L74 _protected prototype_ `virtual void PostRename(UObject* InOldOuter, const FName InOldName) override;`
- L75 _protected prototype_ `virtual void BeginDestroy() override;`
- L79 _protected prototype_ `void SetDebugMode(bool bInEnabled);`
- L82 _protected prototype_ `void AllocateGlyphMeshData(FScopedMeshEditor& InMeshEditor, int32 InCount);`
- L83 _protected prototype_ `void AppendGlyphMesh(FScopedMeshEditor& InMeshEditor, uint16 InIndex, uint32 InGlyphIndex, UDynamicMesh* InMesh);`
- L84 _protected prototype_ `void ClearMesh();`
- L85 _protected prototype_ `void ClearGlyphMesh(FScopedMeshEditor& InMeshEditor, uint16 InIndex);`
- L86 _protected prototype_ `void SetGlyphMeshTransform(FScopedMeshEditor& InMeshEditor, uint16 InIndex, const FTransform& InTransform, bool bInVisible);`
- L88 _protected prototype_ `void SaveMesh(const FScopedMeshEditor& InMeshEditor);`
- L89 _protected prototype_ `void RestoreMesh(FScopedMeshEditor& InMeshEditor);`
- L92 _protected member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Renderer", meta=(EditCondition="false", EditConditionHides))`
- L94 _protected member_ `TArray<FGlyphMeshData> GlyphMeshData;`
- L95 _protected member_ `TOptional<FScopedMeshEditor> ScopedMeshEditor;`
- L96 _protected member_ `TOptional<UE::Geometry::FDynamicMesh3> CachedMesh;`
- L101 _protected member_ `TOptional<UE::Geometry::FDynamicMesh3> OriginalMesh;` — Mesh generated by the geometry update. Not modified by other extensions. Used as ground truth to avoid dealing with delta transforms (floating point inaccuracies)

#### struct `UText3DDynamicMeshRenderer::FGlyphMeshData`  
`struct FGlyphMeshData`  
_L25-32_
- desc: Used to store data about character glyph mesh
- L27 _public member_ `bool bVisible = true;`
- L28 _public member_ `uint16 GlyphIndex = 0;`
- L29 _public member_ `TArray<int32> MaterialSlots;`
- L30 _public member_ `FTransform CurrentTransform = FTransform::Identity;`
- L31 _public member_ `FBox Bounds = FBox(ForceInitToZero);`

#### enum `UText3DDynamicMeshRenderer::EMeshEditorUpdateType`  
`enum class EMeshEditorUpdateType : uint8`  
_L35-40_
- desc: Mesh update type
- L37 _public enumerator_ `None`
- L38 _public enumerator_ `Fast`
- L39 _public enumerator_ `Full`

#### struct `UText3DDynamicMeshRenderer::FScopedMeshEditor`  
`struct FScopedMeshEditor`  
_L43-56_
- desc: Used to push render changes when destroyed
- L45 _public function_ `explicit FScopedMeshEditor(UText3DDynamicMeshRenderer* InComponent) : Owner(InComponent)`
- L49 _public prototype_ `~FScopedMeshEditor();`
- L50 _public prototype_ `void EditMesh(const TFunctionRef<void(UE::Geometry::FDynamicMesh3&)>& InFunctor, EMeshEditorUpdateType InType);`
- L51 _public prototype_ `void ProcessMesh(const TFunctionRef<void(const UE::Geometry::FDynamicMesh3&)>& InFunctor) const;`
- L54 _private member_ `UText3DDynamicMeshRenderer* Owner;`
- L55 _private member_ `EMeshEditorUpdateType UpdateType = EMeshEditorUpdateType::None;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Renderers/StaticMeshes/Text3DStaticMeshesRenderer.h` (Private)


#### class `UText3DStaticMeshesRenderer`  
`class UText3DStaticMeshesRenderer : public UText3DRendererBase`  
_L24-90_
- reflection: `UCLASS(DisplayName="StaticMeshesRenderer", ClassGroup="Text3D", HideCategories=(Renderer))`
- inherits: `UText3DRendererBase`
- desc: Legacy/default renderer for Text3D Each text character is rendered as a StaticMesh within its own StaticMeshComponent Text3DComponent - Text3DRoot (Root) --- Text3DStaticMeshComponent (Character) Eg: The text "Hello" will be rendered using 5 StaticMeshComponents
- L31 _public prototype_ `int32 GetGlyphCount();` — `UFUNCTION(BlueprintCallable, Category = "Rendering|Components|Text3D")` — Gets the number of font glyphs that are currently used
- L35 _public prototype_ `UStaticMeshComponent* GetGlyphMeshComponent(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Rendering|Components|Text3D")` — Gets the StaticMeshComponent of a glyph
- L39 _public prototype_ `const TArray<UStaticMeshComponent*>& GetGlyphMeshComponents();` — `UFUNCTION(BlueprintCallable, Category = "Rendering|Components|Text3D")` — Gets all the glyph meshes
- L44 _public prototype_ `void ConvertToStaticMesh();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Converts the text to a single static mesh, this is an heavy operation
- L49 _protected prototype_ `virtual void OnCreate() override;`
- L50 _protected prototype_ `virtual void OnUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L51 _protected prototype_ `virtual void OnClear() override;`
- L52 _protected prototype_ `virtual void OnDestroy() override;`
- L53 _protected prototype_ `virtual EText3DMeshType GetMeshType() const override;`
- L54 _protected prototype_ `virtual FName GetFriendlyName() const override;`
- L55 _protected prototype_ `virtual FBox OnCalculateBounds() const override;`
- L56 _protected prototype_ `virtual void OnIterateManagedPrimitives(TFunctionRef<void(TNotNull<const UPrimitiveComponent*>)> InFunc) const override;`
- L58 _protected prototype_ `virtual void OnDebugModeEnabled() override;`
- L59 _protected prototype_ `virtual void OnDebugModeDisabled() override;`
- L64 _protected prototype_ `virtual void PostRename(UObject* InOldOuter, const FName InOldName) override;`
- L67 _protected prototype_ `void AllocateComponents(int32 InNewCharacterCount);`
- L73 _protected prototype_ `UStaticMeshComponent* FindTemplate() const;` — If UText3DProjectSettings::UseExistingCharactersAsTemplates is enabled, finds the first valid existing mesh component to use as template Otherwise this returns null and new character meshes will be default allocated.
- L76 _protected prototype_ `void SetDebugMode(bool bEnabled);`
- L81 _protected member_ `TObjectPtr<USceneComponent> TextRoot;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Renderer", meta=(EditCondition="false", EditConditionHides))` — Holds all character components
- L85 _protected member_ `TArray<TObjectPtr<UStaticMeshComponent>> CharacterMeshes;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Renderer", meta=(EditCondition="false", EditConditionHides))` — Each character mesh is held in these components
- L89 _protected member_ `TArray<TObjectPtr<UStaticMeshComponent>> CharacterMeshesPool;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Reusable components to avoid creating and destroying them, recycle components or create new ones when pool is empty

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Subsystems/Text3DBuildSystem.h` (Private)


#### class `UText3DBuildSystem`  
`class UText3DBuildSystem : public UWorldSubsystem, public FTickableGameObject, public IText3DBuildSystemInterface`  
_L24-104_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UWorldSubsystem,FTickableGameObject,IText3DBuildSystemInterface`
- desc: Manages all the text builds for a world It's different from UText3DEngineSubsystem to keep these text builders referencing the text components scoped within the same world.
- L29 _public prototype_ `UText3DBuildSystem();`
- L31 _public prototype_ `static UText3DBuildSystem* Get(TNotNull<const UText3DComponent*> InComponent);`
- L39 _public prototype_ `void RequestTextBuild(TNotNull<UText3DComponent*> InComponent, EText3DRendererFlags InFlags, bool bInBlockingBuild);` — Adds the text component to the queue of builders @param InComponent the component to request build for @param InFlags the renderer flags for the build @param bInBlockingBuild whether the build should be blocking (immediate) or incremental (deferred, across multiple frames)
- L42 _public prototype_ `int32 RemoveTextBuild(TNotNull<UText3DComponent*> InComponent);` — Removes the builders that relate to the given component
- L45 _public prototype_ `void IncrementalTextBuild();` — Called on tick to process builders and call IncrementalBuild on them
- L52 _public prototype_ `void BlockBuildTexts();` — `UFUNCTION(BlueprintCallable, Category="Text 3D")` — Executes any remaining text builds with no time budget. Warning: This can cause a hitch and should only be used when the result is needed immediately regardless of hitch.
- L56 _public prototype_ `bool IsBuildingText() const;` — `UFUNCTION(BlueprintPure, Category="Text 3D")` — Returns true if there are Text3D components being built
- L60 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L61 _protected prototype_ `virtual void Deinitialize() override;`
- L65 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`
- L69 _protected prototype_ `virtual bool IsTickableInEditor() const override;`
- L70 _protected prototype_ `virtual void Tick(float InDeltaTime) override;`
- L71 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L75 _protected prototype_ `virtual bool IsBuildInProgress() const override;`
- L76 _protected prototype_ `virtual void FlushBuilds() override;`
- L77 _protected prototype_ `virtual void HidePrimitivesBeingBuilt(FSceneView& InSceneView) const override;`
- L82 _private prototype_ `void ConditionallyRegisterDelegates();` — Registers the build delegates only if they haven't been registered yet
- L85 _private prototype_ `void UnregisterDelegates();` — Unregisters the build delegates
- L88 _private member_ `TArray<UE::Text3D::FTextBuilder> QueuedBuilders;` — Builders that are not yet processed
- L91 _private member_ `TArray<UE::Text3D::FTextBuilder> TextBuilders;` — Active builders
- L94 _private member_ `TSharedPtr<UE::Text3D::FText3DSceneViewExtension> SceneViewExtension;` — Scene view extension to hide any primitive from text actors that are pending build
- L97 _private member_ `TOptional<uint64> BeginFrameCycles;` — Cycles measured in begin frame
- L100 _private member_ `uint64 BudgetDeficit = 0;` — Accumulated cycles spent on blocking updates to determine if next tick an update should happen
- L103 _private member_ `FDelegateHandle BeginFrameHandle;` — Handle to the begin frame call to keep track how long this frame's been going for

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Text3D` (scope `UE`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Subsystems/Text3DEngineSubsystem.h` (Private)


#### struct `FText3DBuildGlyphMeshDesc`  
`struct FText3DBuildGlyphMeshDesc`  
_L17-29_
- desc: Struct containing the necessary information to build glyphs
- L21 _public member_ `UE::Text3D::FGlyphOutline GlyphOutline;` — Generated outline to build from
- L23 _public member_ `TSharedPtr<FFreeTypeFace> FontFace;` — Shared font face
- L26 _public member_ `uint32 GlyphIndex = 0;` — Index to the glyph to build
- L28 _public member_ `int32 GlyphParametersIndex = 0;` — Set when queuing the mesh desc to map to the glyph parameters used

#### struct `FText3DFontFaceCache`  
`struct FText3DFontFaceCache`  
_L32-118_
- reflection: `USTRUCT()`
- L37 _public prototype_ `static uint32 GetFontFaceHash(const TSharedPtr<FFreeTypeFace>& InFontFace);`
- L39 _public prototype_ `static uint32 GetGlyphMeshHash(uint32 InGlyphIndex, const FGlyphMeshParameters& InParameters);`
- L41 _public prototype_ `FText3DFontFaceCache() = default;`
- L44 _public prototype_ `explicit FText3DFontFaceCache(const TSharedPtr<FFreeTypeFace>& InFontFace);`
- L45 _public prototype_ `void UpdateFontFace(const TSharedPtr<FFreeTypeFace>& InFontFace);`
- L57 _public prototype_ `TOptional<FText3DBuildGlyphMeshDesc> PrepareCachedMesh(uint32 InGlyphIndex, const FGlyphMeshParameters& InParameters, bool& bOutAlreadyCached);` — Loads the glyph contours and allocates the cached meshes the BuildGlyphMesh will be using (across multiple threads) This happens in the game thread. @param InGlyphIndex the glyph index to get the hash for @param InParameters the mesh parameters for the glyph @param bOutAlreadyCached is set to true if the glyph mesh is already cached @return the glyph mesh desc if a new mesh was prepared. Unset otherwise (if already cached, or if glyph outline load failed).
- L76 _public prototype_ `void BuildGlyphMesh(const FBuildGlyphMeshSharedDesc& InSharedParams, const FBuildGlyphMeshInstanceDesc& InInstanceParams);` — Builds a glyph mesh and saves the mesh (static and optionally dynamic) to the cached mesh struct This is called from multiple threads.
- L79 _public prototype_ `const FText3DCachedMesh* FindGlyphMesh(uint32 InGlyphHash) const;`
- L80 _public prototype_ `FText3DCachedMesh* FindGlyphMesh(uint32 InGlyphHash);`
- L81 _public prototype_ `uint32 CleanupCache();`
- L83 _public prototype_ `FString ToDebugString() const;`
- L84 _public prototype_ `bool IsValid() const;`
- L85 _public prototype_ `uint32 GetCacheRefCount() const;`
- L86 _public prototype_ `uint32 GetCacheGlyphCount() const;`
- L88 _public function_ `bool operator==(const FText3DFontFaceCache& InOther) const`
- L93 _public function_ `bool operator!=(const FText3DFontFaceCache& InOther) const`
- L105 _private prototype_ `TOptional<UE::Text3D::FGlyphOutline> LoadGlyphOutline(uint32 InGlyphIndex) const;`
- L108 _private member_ `TSharedPtr<FFreeTypeFace> FontFace;` — Font face for a Font+Typeface
- L113 _private member_ `TMap<uint32, FText3DCachedMesh> GlyphMeshes;` — `UPROPERTY()` — Glyph indexes to cached meshes
- L117 _private member_ `uint32 FontFaceHash = 0;` — `UPROPERTY()` — Hash to uniquely identify this struct

#### struct `FText3DFontFaceCache::FBuildGlyphMeshSharedDesc`  
`struct FBuildGlyphMeshSharedDesc`  
_L60-64_
- desc: Data that does not change for a batch build
- L62 _public member_ `TNotNull<UText3DEngineSubsystem*> TextSubsystem;`
- L63 _public member_ `UMaterialInterface* DefaultMaterial;`

#### struct `FText3DFontFaceCache::FBuildGlyphMeshInstanceDesc`  
`struct FBuildGlyphMeshInstanceDesc`  
_L66-71_
- desc: Data that changes per build call in a batch
- L68 _public member_ `TNotNull<const UE::Text3D::FGlyphOutline*> GlyphOutline;`
- L69 _public member_ `TNotNull<const FGlyphMeshParameters*> GlyphMeshParameters;`
- L70 _public member_ `uint32 GlyphIndex;`

#### class `UText3DEngineSubsystem`  
`class UText3DEngineSubsystem : public UEngineSubsystem, public FSelfRegisteringExec`  
_L121-187_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem,FSelfRegisteringExec`
- L126 _public prototype_ `static UText3DEngineSubsystem* Get();`
- L128 _public prototype_ `void ScheduleCacheCleanup();`
- L131 _public prototype_ `UMaterial* GetDefaultMaterial() const;` — Returns the default material for text meshes
- L134 _public prototype_ `FText3DFontFaceCache* FindOrAddCachedFontFace(const TSharedPtr<FFreeTypeFace>& InFontFace);`
- L135 _public prototype_ `FText3DFontFaceCache* FindCachedFontFace(const TSharedPtr<FFreeTypeFace>& InFontFace);`
- L138 _public prototype_ `FText3DFontFaceCache* FindCachedFontFace(uint32 InFontFaceHash);`
- L141 _public prototype_ `void QueueBuildGlyphMeshes(TArray<FText3DBuildGlyphMeshDesc>&& InMeshDescs, const FGlyphMeshParameters& InGlyphMeshParameters);` — Adds the given mesh desc and glyph parameters to the queue
- L144 _public prototype_ `int32 GetQueuedGlyphMeshBuildCount() const;` — Returns the number of glyph meshes pending build
- L147 _public prototype_ `void ProcessBuildGlyphMeshes();` — Processes the queued mesh descs and glyph parameters across multiple threads
- L151 _private prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L152 _private prototype_ `virtual void Deinitialize() override;`
- L156 _private prototype_ `virtual bool Exec_Dev(UWorld* InWorld, const TCHAR* InCmd, FOutputDevice& InAr) override;`
- L161 _private prototype_ `void OnText3DSettingsChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);` — Called when the UText3DProjectSettings has changed
- L164 _private prototype_ `void UpdateDefaultMaterial();` — Updates the cached default material
- L166 _private prototype_ `bool CleanupCache(float);`
- L167 _private prototype_ `void PrintCache() const;`
- L168 _private prototype_ `void ClearCache();`
- L171 _private member_ `TMap<uint32, FText3DFontFaceCache> CachedFontFaces;` — `UPROPERTY()`
- L174 _private member_ `TArray<FText3DBuildGlyphMeshDesc> QueuedMeshDescs;` — Queued mesh descs to build next
- L177 _private member_ `TArray<FGlyphMeshParameters> QueuedGlyphMeshParameters;` — Glyph mesh parameters that the queued mesh descs reference
- L181 _private member_ `TObjectPtr<UMaterial> CachedDefaultMaterial;` — `UPROPERTY()` — the default material to use for text meshes
- L183 _private member_ `FTSTicker::FDelegateHandle CacheCleanupDelegate;`
- L186 _private member_ `bool bGlyphMeshBuildInProgress = false;` — Flag to prevent cleaning while building glyph meshes

#### Free symbols / members of external scopes

- L98 _function_ `friend uint32 GetTypeHash(const FText3DFontFaceCache& InValue)`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Text3DBuilder.h` (Private)


#### enum `UE::Text3D::EBuildPhase`  
`enum class EBuildPhase : uint8`  
_L14-30_
- desc: Enumeration of the different phases of the text building process
- L17 _public enumerator_ `NotStarted` — Build has not started yet
- L19 _public enumerator_ `PrepareExtensions` — Prepares the Text3D extensions for building
- L21 _public enumerator_ `PreRendererUpdate` — Calls PreRendererUpdate for the Text3D extensions
- L23 _public enumerator_ `RendererUpdate` — Runs the 'Update' for the Text3D renderer
- L25 _public enumerator_ `PostRendererUpdate` — Calls PostRendererUpdate for the Text3D extensions
- L27 _public enumerator_ `Succeeded` — Build completed successfully
- L29 _public enumerator_ `Canceled` — Build was canceled

#### enum `UE::Text3D::EBuildResult`  
`enum class EBuildResult : uint8`  
_L33-41_
- desc: The build result for incremental builds
- L36 _public enumerator_ `OutOfBudget` — Build ran out of time budget
- L38 _public enumerator_ `PhaseCompleted` — A build phase has completed
- L40 _public enumerator_ `BuildCompleted` — Build completed

#### class `UE::Text3D::FTextBuilder`  
`class FTextBuilder`  
_L44-209_
- desc: Manages the building of text for the Text3D Component
- L60 _public prototype_ `explicit FTextBuilder(UText3DComponent* InComponent);`
- L66 _public prototype_ `bool PrepareFlags(EText3DRendererFlags InFlags);` — Adds the given renderer flags to this builder. Should only be done for builders that have not started yet. @return true if flags were added or false if nothing happened because the builder is already in progress.
- L68 _public function_ `UText3DComponent* GetComponent() const`
- L73 _public function_ `EText3DRendererFlags GetFlags() const`
- L78 _public function_ `EBuildPhase GetPhase() const`
- L84 _public prototype_ `FString GetDebugName() const;` — Gets a debug string to identify the builder
- L87 _public prototype_ `FString GetDebugStatus() const;` — Gets a debug string to identify the builder
- L90 _public prototype_ `bool IsInProgress() const;` — Returns true if the builder is currently in progress (i.e. between not-started and completed)
- L93 _public prototype_ `bool IsComplete() const;` — Returns true if the builder has completed building the component
- L95 _public function_ `bool GetUseBlockingBuild() const`
- L100 _public function_ `void SetUseBlockingBuild(bool bInUseBlockingBuild)`
- L106 _public prototype_ `void BlockingBuild();` — Fully starts / resumes and finishes the build
- L120 _public prototype_ `void Update(const FUpdateParams& InParams);` — Builds the component every call with a budget end and update phase
- L123 _public prototype_ `void CancelBuild();` — Cancels the build
- L126 _public prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap);` — Called by the owning text world subsystem when object replacement has taken place
- L129 _public prototype_ `void AddReferencedObjects(FReferenceCollector& InCollector);` — Called by the owning text world subsystem to gather objects referenced by this builder
- L133 _private prototype_ `bool IsInRenderingPhases() const;` — Whether the builder is currently in rendering phases
- L136 _private prototype_ `EBuildResult BuildInternal();` — Calls the appropriate function depending on the current phase
- L139 _private prototype_ `bool IsWithinPhaseLimit() const;` — Returns true if the current phase of the build is still less than or equal to the limit, or always true if no limit is set
- L142 _private prototype_ `bool IsWithinBudget() const;` — Returns true if the current cycles is less than the budgeted end cycle or if no budget has been set at all
- L144 _private prototype_ `EBuildResult IterateExtensions(TFunctionRef<bool(FExtensionElement&)> InFunc);`
- L147 _private prototype_ `EBuildResult PrepareComponent();` — Phase 1 - calls BeginBuild on the component and gathers the component's extensions
- L150 _private prototype_ `EBuildResult PrepareExtensions();` — Phase 2- calls PrepareBuild on the extensions
- L153 _private prototype_ `EBuildResult PreRendererUpdate();` — Phase 3 - calls PreRendererUpdate on the extensions for a single renderer flag
- L156 _private prototype_ `EBuildResult RendererUpdate();` — Phase 4 - calls Update on the component's renderer for a single renderer flag
- L163 _private prototype_ `EBuildResult PostRendererUpdate();` — Phase 5 - calls PostRendererUpdate on the extensions for a single renderer flag Once this phase finishes, the next available renderer flag is gotten and if available, build loops back to Phase 3. If there's no available renderer flag left the build finishes.
- L166 _private prototype_ `EBuildResult Next();` — Called to move onto the next phase
- L169 _private prototype_ `void Finish();` — Called when the build has completed
- L172 _private member_ `TObjectPtr<UText3DComponent> Component;` — Component to build
- L175 _private member_ `TArray<FExtensionElement> Extensions;` — Extensions being built
- L178 _private member_ `TOptional<uint64> BudgetEnd;` — If set, the cycle that the build should stop when past it
- L181 _private member_ `int32 ExtensionIndex = INDEX_NONE;` — Current extension being updated. Relevant only to certain phases
- L184 _private member_ `int32 StarvedFrames = 0;` — Number of frames that the incremental build has not been able to execute
- L187 _private member_ `EText3DRendererFlags Flags = EText3DRendererFlags::None;` — Renderer flags for the built
- L190 _private member_ `EText3DRendererFlags FlagsLeft = EText3DRendererFlags::None;` — Remaining renderer flags used exclusively for the renderer phase
- L193 _private member_ `uint8 CurrentFlag = 1;` — Current renderer flag. Relevant only to the renderer phases. Does not reset on phase change.
- L196 _private member_ `EBuildPhase Phase = EBuildPhase::NotStarted;` — Current build phase
- L202 _private member_ `TOptional<EBuildPhase> TempPhaseLimit;` — Temporary max build phase that is allowed by the incremental update. Set to a new value every incremental update call.
- L205 _private member_ `bool bUseBlockingBuild = false;` — Whether blocking build is used for this builder
- L208 _private member_ `mutable bool bSkipNextBudgetCheck = false;` — Whether budget check should be skipped to avoid querying cycles when unnecessary. Resets every IsWithinBudget() call

#### struct `UE::Text3D::FTextBuilder::FExtensionElement`  
`struct FExtensionElement`  
_L47-57_
- desc: Holds the data needed for the Text3D extension during the build process
- L50 _public member_ `TObjectPtr<UText3DExtensionBase> Object = nullptr;` — Text3D extension being built
- L52 _public member_ `EText3DRendererFlags PreRendererFlagsLeft = EText3DRendererFlags::None;` — Remaining flags left for the pre renderer phase.
- L54 _public member_ `EText3DRendererFlags PostRendererFlagsLeft = EText3DRendererFlags::None;` — Remaining flags left for the post renderer phase.
- L56 _public member_ `bool bActive = true;` — Whether the extension is active, or has completed and is not needed for the rest of the renderer updates

#### struct `UE::Text3D::FTextBuilder::FUpdateParams`  
`struct FUpdateParams`  
_L108-118_
- L111 _public member_ `TOptional<uint64> BudgetEnd;` — If set, the cycle that the build should stop when past it. If unset, no budget end (analogous to a blocking build)
- L113 _public member_ `int32 MaxStarvedFrames = 0;` — The maximum number of frames the build frame can starve.
- L115 _public member_ `TOptional<UE::Text3D::EBuildPhase> TempMaxUpdatePhase;` — If set, temporary max build phase that is allowed by the incremental update. If unset, no limit.
- L117 _public member_ `mutable bool bBuildTimeExceeded = false;` — Whether the build time has been exceeded already. Updated by the incremental build calls when this happens. Any non-starving incremental build will be skipped

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Text3D` (scope `UE`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Text3DComponentInstanceData.h` (Private)


#### struct `FText3DComponentInstanceData`  
`struct FText3DComponentInstanceData : public FActorComponentInstanceData`  
_L20-46_
- reflection: `USTRUCT()`
- inherits: `FActorComponentInstanceData`
- L24 _public prototype_ `FText3DComponentInstanceData() = default;`
- L25 _public prototype_ `explicit FText3DComponentInstanceData(const UText3DComponent* InSourceComponent);`
- L28 _public prototype_ `virtual bool ContainsData() const override;`
- L29 _public prototype_ `virtual void ApplyToComponent(UActorComponent* InComponent, const ECacheApplyPhase InCacheApplyPhase) override;`
- L30 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L35 _private member_ `TObjectPtr<UText3DRendererBase> TextRenderer = nullptr;` — Source text renderer
- L38 _private member_ `TObjectPtr<UText3DCharacterExtensionBase> CharacterExtension = nullptr;` — Source extensions
- L39 _private member_ `TObjectPtr<UText3DGeometryExtensionBase> GeometryExtension = nullptr;`
- L40 _private member_ `TObjectPtr<UText3DLayoutExtensionBase> LayoutExtension = nullptr;`
- L41 _private member_ `TObjectPtr<UText3DMaterialExtensionBase> MaterialExtension = nullptr;`
- L42 _private member_ `TObjectPtr<UText3DRenderingExtensionBase> RenderingExtension = nullptr;`
- L43 _private member_ `TObjectPtr<UText3DStyleExtensionBase> StyleExtension = nullptr;`
- L44 _private member_ `TObjectPtr<UText3DTokenExtensionBase> TokenExtension = nullptr;`
- L45 _private member_ `TArray<TObjectPtr<UText3DLayoutEffectBase>> LayoutEffects;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Text3DInternalTypes.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Text3D` (scope `UE`)
- L9 _namespace_ `namespace Material` (scope `UE::Text3D`)
- L11 _prototype_ `TConstArrayView<FName> GetSlotNames();` (scope `UE::Text3D::Material`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Text3DModule.h` (Private)


#### class `FText3DModule`  
`class FText3DModule final : public IModuleInterface`  
_L25-41_
- inherits: `IModuleInterface`
- L28 _public prototype_ `FText3DModule();`
- L31 _public prototype_ `virtual void StartupModule() override;`
- L32 _public prototype_ `virtual void ShutdownModule() override;`
- L36 _public prototype_ `static FT_Library GetFreeTypeLibrary();`
- L39 _private member_ `FT_Library FreeTypeLib;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define generic __identifier(generic)`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Text3DSceneViewExtension.h` (Private)


#### class `UE::Text3D::FText3DSceneViewExtension`  
`class FText3DSceneViewExtension : public FSceneViewExtensionBase`  
_L11-24_
- inherits: `FSceneViewExtensionBase`
- desc: Scene view extensions to hide any primitive managed by Text3D that is still under construction
- L14 _public function_ `explicit FText3DSceneViewExtension(const FAutoRegister& InAutoRegister) : FSceneViewExtensionBase(InAutoRegister)`
- L21 _protected prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L22 _protected prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Text3D` (scope `UE`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Private/Utilities/Text3DScopedLog.h` (Private)


#### struct `UE::Text3D::FScopedLog`  
`struct FScopedLog`  
_L15-21_
- desc: Handles adding and removing 'scope levels' for log clarity
- L17 _public prototype_ `FScopedLog();`
- L18 _public prototype_ `~FScopedLog();`
- L20 _public prototype_ `const TCHAR* GetLogPrefix() const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_TEXT3D_LOG_SCOPE_ENABLED 1 && !NO_LOGGING`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Text3D` (scope `UE`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Characters/Text3DCharacterBase.h` (Public)


#### class `UText3DCharacterBase`  
`class UText3DCharacterBase : public UObject`  
_L15-126_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=(Character))`
- inherits: `UObject`
- desc: Holds data for a single character in Text3D
- L20 _public prototype_ `static FName GetRelativeLocationPropertyName();`
- L21 _public prototype_ `static FName GetRelativeRotationPropertyName();`
- L22 _public prototype_ `static FName GetRelativeScalePropertyName();`
- L23 _public prototype_ `static FName GetVisiblePropertyName();`
- L25 _public prototype_ `FTransform& GetTransform(bool bInReset);`
- L28 _public function_ `void SetCharacter(const FString& InCharacter)`
- L33 _public function_ `const FString& GetCharacter() const`
- L39 _public prototype_ `const UE::Text3D::Geometry::FCachedFontFaceGlyphHandle& GetFontFaceGlyphHandle() const;`
- L40 _public prototype_ `void SetFontFaceGlyphHandle(const UE::Text3D::Geometry::FCachedFontFaceGlyphHandle& InHandle);`
- L42 _public prototype_ `void SetStyleTag(FName InStyle);`
- L43 _public function_ `FName GetStyleTag() const`
- L48 _public prototype_ `uint32 GetGlyphIndex() const;`
- L49 _public prototype_ `const FText3DCachedMesh* GetGlyphMesh() const;`
- L50 _public prototype_ `void GetGlyphMeshBoundsAndOffset(FBox& OutBounds, FVector& OutOffset) const;`
- L53 _public prototype_ `void SetRelativeLocation(const FVector& InLocation);` — `UFUNCTION()`
- L54 _public function_ `const FVector& GetRelativeLocation() const`
- L60 _public prototype_ `void SetRelativeRotation(const FRotator& InRotation);` — `UFUNCTION()`
- L61 _public function_ `const FRotator& GetRelativeRotation() const`
- L67 _public prototype_ `void SetRelativeScale(const FVector& InScale);` — `UFUNCTION()`
- L68 _public function_ `const FVector& GetRelativeScale() const`
- L74 _public prototype_ `void SetVisibility(bool bInVisibility);` — `UFUNCTION()`
- L75 _public function_ `bool GetVisibility() const`
- L81 _public function_ `virtual float GetCharacterKerning() const` — Get character custom kerning
- L87 _public prototype_ `virtual void ResetCharacterState();` — Reset properties to their initial state when character is recycled
- L92 _protected prototype_ `virtual void PostEditUndo() override;`
- L93 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L97 _protected prototype_ `void OnCharacterDataChanged(EText3DRendererFlags InFlags) const;`
- L102 _protected member_ `FString Character;` — `UPROPERTY(VisibleAnywhere, Category="Character", Transient, meta=(EditCondition="false", EditConditionHides, AllowPrivateAccess="true"))` — Used for TitleProperty of the array to display this instead of the index
- L106 _protected member_ `FVector RelativeLocation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Character", meta=(AllowPrivateAccess = "true"))`
- L109 _protected member_ `FRotator RelativeRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Character", meta=(AllowPrivateAccess = "true"))`
- L112 _protected member_ `FVector RelativeScale = FVector::OneVector;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Character", meta=(Delta="0.05", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", ClampMin="0", AllowPrivateAccess = "true"))`
- L115 _protected member_ `bool bVisible = true;` — `UPROPERTY(EditAnywhere, Setter="SetVisibility", Getter="GetVisibility", Category="Character", meta=(AllowPrivateAccess = "true"))`
- L119 _protected member_ `FName StyleTag = NAME_None;` — `UPROPERTY(VisibleAnywhere, Setter, Getter, Category="Character")` — Tag used to identify the custom style applied to this character
- L122 _protected member_ `FTransform Transform = FTransform::Identity;` — Final transform after all extensions are applied
- L125 _protected member_ `UE::Text3D::Geometry::FCachedFontFaceGlyphHandle FontFaceGlyphHandle;` — Handle to the current glyph mesh this character represents

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Characters/Text3DCharacterTransform.h` (Public)


#### class `UText3DCharacterTransform`  
`class UText3DCharacterTransform : public USceneComponent`  
_L18-237_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(Text3D), HideCategories = (Collision, Tags, Activation, Cooking, Rendering, Physics, Mobility, LOD, AssetUserData, Navigation, Transform))`
- inherits: `USceneComponent`
- desc: This class should no longer be used with Text3D It is only kept to migrate properties to the newer system See UText3DLayoutTransformEffect that can be added in section Text3DComponent/Layout/LayoutEffects
- L23 _public prototype_ `UText3DCharacterTransform();`
- L25 _public function_ `bool GetLocationEnabled() const`
- L30 _public function_ `float GetLocationProgress() const`
- L35 _public function_ `EText3DCharacterEffectOrder GetLocationOrder() const`
- L40 _public function_ `float GetLocationRange() const`
- L45 _public function_ `FVector GetLocationDistance() const`
- L50 _public function_ `bool GetRotationEnabled() const`
- L55 _public function_ `float GetRotationProgress() const`
- L60 _public function_ `EText3DCharacterEffectOrder GetRotationOrder() const`
- L65 _public function_ `float GetRotationRange() const`
- L70 _public function_ `FRotator GetRotationBegin() const`
- L75 _public function_ `FRotator GetRotationEnd() const`
- L80 _public function_ `bool GetScaleEnabled() const`
- L85 _public function_ `float GetScaleProgress() const`
- L90 _public function_ `EText3DCharacterEffectOrder GetScaleOrder() const`
- L95 _public function_ `float GetScaleRange() const`
- L100 _public function_ `FVector GetScaleBegin() const`
- L105 _public function_ `FVector GetScaleEnd() const`
- L113 _public prototype_ `void SetLocationEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Location")`
- L116 _public prototype_ `void SetLocationProgress(float Progress);` — `UFUNCTION(BlueprintCallable, Category = "Location")`
- L119 _public prototype_ `void SetLocationOrder(EText3DCharacterEffectOrder Order);` — `UFUNCTION(BlueprintCallable, Category = "Location")`
- L122 _public prototype_ `void SetLocationRange(float Range);` — `UFUNCTION(BlueprintCallable, Category = "Location")`
- L125 _public prototype_ `void SetLocationDistance(FVector Distance);` — `UFUNCTION(BlueprintCallable, Category = "Location")`
- L130 _public prototype_ `void SetRotateEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Rotate")`
- L133 _public prototype_ `void SetRotateProgress(float Progress);` — `UFUNCTION(BlueprintCallable, Category = "Rotate")`
- L136 _public prototype_ `void SetRotateOrder(EText3DCharacterEffectOrder Order);` — `UFUNCTION(BlueprintCallable, Category = "Rotate")`
- L139 _public prototype_ `void SetRotateRange(float Range);` — `UFUNCTION(BlueprintCallable, Category = "Rotate")`
- L142 _public prototype_ `void SetRotateBegin(FRotator Value);` — `UFUNCTION(BlueprintCallable, Category = "Rotate")`
- L145 _public prototype_ `void SetRotateEnd(FRotator Value);` — `UFUNCTION(BlueprintCallable, Category = "Rotate")`
- L150 _public prototype_ `void SetScaleEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Scale")`
- L153 _public prototype_ `void SetScaleProgress(float Progress);` — `UFUNCTION(BlueprintCallable, Category = "Scale")`
- L156 _public prototype_ `void SetScaleOrder(EText3DCharacterEffectOrder Order);` — `UFUNCTION(BlueprintCallable, Category = "Scale")`
- L159 _public prototype_ `void SetScaleRange(float Range);` — `UFUNCTION(BlueprintCallable, Category = "Scale")`
- L162 _public prototype_ `void SetScaleBegin(FVector Value);` — `UFUNCTION(BlueprintCallable, Category = "Scale")`
- L165 _public prototype_ `void SetScaleEnd(FVector Value);` — `UFUNCTION(BlueprintCallable, Category = "Scale")`
- L168 _protected prototype_ `UText3DComponent* GetText3DComponent() const;`
- L169 _protected prototype_ `UText3DLayoutTransformEffect* GetText3DLayoutTransformEffect() const;`
- L172 _protected prototype_ `virtual void OnComponentCreated() override;`
- L176 _protected prototype_ `virtual void PostLoad() override;`
- L179 _protected prototype_ `void PrintDeprecationLog() const;`
- L184 _protected member_ `bool bLocationEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetLocationEnabled, Category = "Location")`
- L187 _protected member_ `float LocationProgress;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetLocationProgress, Category = "Location", meta = (EditCondition = "bLocationEnabled", ClampMin = 0, ClampMax = 100))`
- L190 _protected member_ `EText3DCharacterEffectOrder LocationOrder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetLocationOrder, Category = "Location", meta = (EditCondition = "bLocationEnabled"))`
- L193 _protected member_ `float LocationRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetLocationRange, Category = "Location", meta = (EditCondition = "bLocationEnabled", ClampMin = 0, ClampMax = 100))`
- L196 _protected member_ `FVector LocationDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetLocationDistance, Category = "Location", meta = (EditCondition = "bLocationEnabled"))`
- L201 _protected member_ `bool bRotateEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetRotateEnabled, Category = "Rotate")`
- L204 _protected member_ `float RotateProgress;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetRotateProgress, Category = "Rotate", meta = (EditCondition = "bRotateEnabled", ClampMin = 0, ClampMax = 100))`
- L207 _protected member_ `EText3DCharacterEffectOrder RotateOrder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetRotateOrder, Category = "Rotate", meta = (EditCondition = "bRotateEnabled"))`
- L210 _protected member_ `float RotateRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetRotateRange, Category = "Rotate", meta = (EditCondition = "bRotateEnabled", ClampMin = 0, ClampMax = 100))`
- L213 _protected member_ `FRotator RotateBegin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetRotateBegin, Category = "Rotate", meta = (EditCondition = "bRotateEnabled"))`
- L216 _protected member_ `FRotator RotateEnd;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetRotateEnd, Category = "Rotate", meta = (EditCondition = "bRotateEnabled"))`
- L221 _protected member_ `bool bScaleEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetScaleEnabled, Category = "Scale")`
- L224 _protected member_ `float ScaleProgress;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetScaleProgress, Category = "Scale", meta = (EditCondition = "bScaleEnabled", ClampMin = 0, ClampMax = 100))`
- L227 _protected member_ `EText3DCharacterEffectOrder ScaleOrder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetScaleOrder, Category = "Scale", meta = (EditCondition = "bScaleEnabled"))`
- L230 _protected member_ `float ScaleRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetScaleRange, Category = "Scale", meta = (EditCondition = "bScaleEnabled", ClampMin = 0, ClampMax = 100))`
- L233 _protected member_ `FVector ScaleBegin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetScaleBegin, Category = "Scale", meta = (EditCondition = "bScaleEnabled", ClampMin = 0))`
- L236 _protected member_ `FVector ScaleEnd;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetScaleEnd, Category = "Scale", meta = (EditCondition = "bScaleEnabled", ClampMin = 0))`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Characters/Text3DDefaultCharacter.h` (Public)


#### class `UText3DDefaultCharacter`  
`class UText3DDefaultCharacter : public UText3DCharacterBase`  
_L11-39_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories=(Character))`
- inherits: `UText3DCharacterBase`
- desc: Holds data for a single character in Text3D
- L16 _public prototype_ `static FName GetKerningPropertyName();`
- L18 _public prototype_ `void SetKerning(float InKerning);`
- L19 _public function_ `float GetKerning() const`
- L27 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L32 _protected prototype_ `virtual float GetCharacterKerning() const override;`
- L33 _protected prototype_ `virtual void ResetCharacterState() override;`
- L38 _protected member_ `float Kerning = 0.f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Character", meta=(AllowPrivateAccess = "true"))` — Kerning adjusts the space between this character

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DCharacterExtensionBase.h` (Public)


#### class `UText3DCharacterExtensionBase`  
`class UText3DCharacterExtensionBase : public UText3DExtensionBase`  
_L13-44_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DExtensionBase`
- desc: Extension that handles character data for Text3D
- L19 _public function_ `virtual uint16 GetCharacterCount() const` — Get the amount of character
- L25 _public function_ `virtual UText3DCharacterBase* GetCharacter(uint16 InCharacter) const` — Get per character data
- L31 _public function_ `virtual TConstArrayView<UText3DCharacterBase*> GetCharacters() const` — Get all character data
- L37 _public function_ `virtual void AllocateCharacters(uint16 InCount)` — Allocate visible characters to store data
- L42 _public member_ `uint16 TextCharacterIndex = 0;` — `UPROPERTY(EditInstanceOnly, Transient, Category="Character", meta=(TextCharacterSelector, AllowPrivateAccess=true))` — Used for detail customization within editor

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DDefaultCharacterExtension.h` (Public)


#### class `UText3DDefaultCharacterExtension`  
`class UText3DDefaultCharacterExtension : public UText3DCharacterExtensionBase`  
_L11-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UText3DCharacterExtensionBase`
- L17 _protected prototype_ `virtual uint16 GetCharacterCount() const override;`
- L18 _protected prototype_ `virtual UText3DCharacterBase* GetCharacter(uint16 InCharacter) const override;`
- L19 _protected prototype_ `virtual TConstArrayView<UText3DCharacterBase*> GetCharacters() const override;`
- L20 _protected prototype_ `virtual void AllocateCharacters(uint16 InCount) override;`
- L24 _protected prototype_ `virtual void PostLoad() override;`
- L28 _protected prototype_ `void AllocateTextCharacters(uint16 InCharacterCount);` — Allocate character data by using pool or creating new object
- L32 _protected member_ `TArray<TObjectPtr<UText3DCharacterBase>> TextCharacters;` — `UPROPERTY(Instanced)` — Characters composing the active text
- L36 _protected member_ `TArray<TObjectPtr<UText3DCharacterBase>> TextCharactersPool;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Pool of characters to reuse when text changes to avoid creating new objects

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DDefaultGeometryExtension.h` (Public)


#### class `UText3DDefaultGeometryExtension`  
`class UText3DDefaultGeometryExtension : public UText3DGeometryExtensionBase`  
_L9-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UText3DGeometryExtensionBase`
- L16 _public function_ `float GetExtrude() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Geometry")` — Get the text extrusion size and signal the primitives to be rebuilt
- L23 _public prototype_ `void SetExtrude(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")` — Set the text extrusion size and signal the primitives to be rebuilt
- L27 _public function_ `float GetBevel() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Geometry")` — Get the 3d bevel value
- L34 _public prototype_ `void SetBevel(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")` — Set the 3d bevel value
- L38 _public function_ `EText3DBevelType GetBevelType() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Geometry")` — Get the 3d bevel type
- L45 _public prototype_ `void SetBevelType(const EText3DBevelType Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")` — Set the 3d bevel type
- L49 _public function_ `int32 GetBevelSegments() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Geometry")` — Get the amount of segments that will be used to tessellate the Bevel
- L56 _public prototype_ `void SetBevelSegments(const int32 Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")` — Set the amount of segments that will be used to tessellate the Bevel
- L60 _public function_ `bool GetUseOutline() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Geometry")` — Get whether an outline is applied.
- L67 _public prototype_ `void SetUseOutline(const bool bValue);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")` — Set whether an outline is applied.
- L71 _public function_ `float GetOutline() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Geometry")` — Get the outline width.
- L78 _public prototype_ `void SetOutline(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")` — Set the outline width.
- L81 _public prototype_ `void SetOutlineType(EText3DOutlineType InType);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")`
- L84 _public function_ `EText3DOutlineType GetOutlineType() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Geometry")`
- L90 _public prototype_ `void SetPivotHAlignment(EText3DHorizontalTextAlignment InPivot);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")`
- L92 _public function_ `EText3DHorizontalTextAlignment GetPivotHAlignment() const`
- L98 _public prototype_ `void SetPivotVAlignment(EText3DVerticalTextAlignment InPivot);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")`
- L100 _public function_ `EText3DVerticalTextAlignment GetPivotVAlignment() const`
- L106 _public prototype_ `void SetCollisionEnabled(ECollisionEnabled::Type InCollisionEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Geometry")`
- L109 _public function_ `ECollisionEnabled::Type GetCollisionEnabled() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Geometry")`
- L116 _protected prototype_ `virtual void PostInitProperties() override;`
- L118 _protected prototype_ `virtual void PostEditUndo() override;`
- L119 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L124 _protected prototype_ `virtual EText3DHorizontalTextAlignment GetGlyphHAlignment() const override;`
- L125 _protected prototype_ `virtual EText3DVerticalTextAlignment GetGlyphVAlignment() const override;`
- L126 _protected prototype_ `virtual ECollisionEnabled::Type GetGlyphCollisionEnabled() const override;`
- L127 _protected prototype_ `virtual const FGlyphMeshParameters* GetGlyphMeshParameters() const override;`
- L131 _protected prototype_ `virtual void PrepareBuild(EText3DRendererFlags InUpdateFlags) override;`
- L132 _protected prototype_ `virtual EText3DExtensionResult PreRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L133 _protected prototype_ `virtual EText3DExtensionResult PostRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L136 _protected prototype_ `void OnGeometryOptionsChanged();`
- L137 _protected prototype_ `void OnCollisionEnabledChanged();`
- L139 _protected prototype_ `float GetMaxBevel() const;`
- L140 _protected prototype_ `FVector GetPivotOffset() const;`
- L144 _protected member_ `float Extrude = 5.0f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Geometry", meta = (ClampMin = 0, AllowPrivateAccess = "true"))` — Size of the extrude
- L148 _protected member_ `float Bevel = 0.0f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Geometry", meta = (EditCondition = "!bUseOutline && Extrude > 0", ClampMin = 0, AllowPrivateAccess = "true"))` — Size of bevel
- L152 _protected member_ `EText3DBevelType BevelType = EText3DBevelType::Convex;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Geometry", meta = (EditCondition = "!bUseOutline && Extrude > 0", AllowPrivateAccess = "true"))` — Bevel Type
- L156 _protected member_ `int32 BevelSegments = 8;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Geometry", meta = (EditCondition = "!bUseOutline && Extrude > 0", ClampMin = 1, ClampMax = 15, AllowPrivateAccess = "true"))` — Bevel Segments (Defines the amount of tesselation for the bevel part)
- L160 _protected member_ `bool bUseOutline = false;` — `UPROPERTY(EditAnywhere, Getter = "GetUseOutline", Setter = "SetUseOutline", Category = "Geometry", meta = (AllowPrivateAccess = "true"))` — Generate Outline
- L164 _protected member_ `float Outline = 0.5f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Geometry", meta = (EditCondition = "bUseOutline", AllowPrivateAccess = "true"))` — Outline expand/offset amount, incompatible with bevel
- L168 _protected member_ `EText3DOutlineType OutlineType = EText3DOutlineType::Stroke;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Geometry", meta = (EditCondition = "bUseOutline", AllowPrivateAccess = "true"))` — Outline Type
- L172 _protected member_ `EText3DHorizontalTextAlignment PivotHAlignment = EText3DHorizontalTextAlignment::Left;` — `UPROPERTY(EditAnywhere, DisplayName="Character Pivot Alignment Horizontal", Getter, Setter, Category = "Geometry", meta = (AllowPrivateAccess = "true"))` — Pivot alignment of each character
- L176 _protected member_ `EText3DVerticalTextAlignment PivotVAlignment = EText3DVerticalTextAlignment::Bottom;` — `UPROPERTY(Getter, Setter, meta=(ValidEnumValues="Bottom"))` — Pivot alignment of each character
- L179 _protected member_ `TEnumAsByte<ECollisionEnabled::Type> CollisionEnabled = ECollisionEnabled::QueryAndPhysics;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Geometry", meta=(AllowPrivateAccess = "true"))`
- L182 _private member_ `FGlyphMeshParameters GlyphMeshParameters;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DDefaultLayoutExtension.h` (Public)


#### class `UText3DDefaultLayoutExtension`  
`class UText3DDefaultLayoutExtension : public UText3DLayoutExtensionBase`  
_L18-248_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UText3DLayoutExtensionBase`
- L23 _public prototype_ `static FName GetUseMaxWidthPropertyName();`
- L24 _public prototype_ `static FName GetUseMaxHeightPropertyName();`
- L25 _public prototype_ `static FName GetMaxHeightPropertyName();`
- L26 _public prototype_ `static FName GetMaxWidthPropertyName();`
- L27 _public prototype_ `static FName GetScaleProportionallyPropertyName();`
- L31 _public function_ `float GetTracking() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the tracking value and signal the primitives to be rebuilt
- L38 _public prototype_ `void SetTracking(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the tracking value and signal the primitives to be rebuilt
- L42 _public function_ `float GetLineSpacing() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the line spacing value and signal the primitives to be rebuilt
- L49 _public prototype_ `void SetLineSpacing(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the line spacing value and signal the primitives to be rebuilt
- L53 _public function_ `float GetWordSpacing() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the word spacing value and signal the primitives to be rebuilt
- L60 _public prototype_ `void SetWordSpacing(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the word spacing value and signal the primitives to be rebuilt
- L64 _public function_ `EText3DHorizontalTextAlignment GetHorizontalAlignment() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the horizontal alignment value and signal the primitives to be rebuilt
- L71 _public prototype_ `void SetHorizontalAlignment(const EText3DHorizontalTextAlignment value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the horizontal alignment value and signal the primitives to be rebuilt
- L75 _public function_ `EText3DVerticalTextAlignment GetVerticalAlignment() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the vertical alignment and signal the primitives to be rebuilt
- L82 _public prototype_ `void SetVerticalAlignment(const EText3DVerticalTextAlignment value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the vertical alignment and signal the primitives to be rebuilt
- L86 _public function_ `bool GetUseMaxWidth() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Whether a maximum width is specified
- L93 _public prototype_ `void SetUseMaxWidth(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Enable / Disable a Maximum Width
- L97 _public function_ `float GetMaxWidth() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the Maximum Width - If width is larger, mesh will scale down to fit MaxWidth value
- L104 _public prototype_ `void SetMaxWidth(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the Maximum Width - If width is larger, mesh will scale down to fit MaxWidth value
- L108 _public function_ `EText3DMaxWidthHandling GetMaxWidthBehavior() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the Maximum Width Handling - Whether to wrap before scaling when the text size reaches the max width
- L115 _public prototype_ `void SetMaxWidthBehavior(const EText3DMaxWidthHandling Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the Maximum Width Handling - Whether to wrap before scaling when the text size reaches the max width
- L119 _public function_ `bool GetUseMaxHeight() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Whether a maximum height is specified
- L126 _public prototype_ `void SetUseMaxHeight(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Enable / Disable a Maximum Height
- L130 _public function_ `float GetMaxHeight() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the Maximum Height - If height is larger, mesh will scale down to fit MaxHeight value
- L137 _public prototype_ `void SetMaxHeight(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the Maximum Height - If height is larger, mesh will scale down to fit MaxHeight value
- L141 _public function_ `bool GetScalesProportionally() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get if the mesh should scale proportionally when Max Width/Height is set
- L148 _public prototype_ `void SetScaleProportionally(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set if the mesh should scale proportionally when Max Width/Height is set
- L152 _public function_ `ETextShapingMethod GetTextShapingMethod() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Layout")` — Get the current method of shaping text
- L159 _public prototype_ `void SetTextShapingMethod(ETextShapingMethod InTextShapingMethod);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Layout")` — Set the method to shape text
- L164 _protected prototype_ `virtual void PostEditUndo() override;`
- L165 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L170 _protected prototype_ `virtual float GetTextHeight() const override;`
- L171 _protected prototype_ `virtual FVector GetTextScale() const override;`
- L172 _protected prototype_ `virtual FVector GetLineLocation(int32 LineIndex) const override;`
- L176 _protected prototype_ `virtual void PrepareBuild(EText3DRendererFlags InUpdateFlags) override;`
- L177 _protected prototype_ `virtual EText3DExtensionResult PreRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L178 _protected prototype_ `virtual EText3DExtensionResult PostRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L181 _protected prototype_ `void CalculateTextScale();`
- L182 _protected prototype_ `void OnLayoutOptionsChanged();`
- L183 _protected prototype_ `void OnTextShapingMethodChanged();`
- L187 _protected member_ `EText3DHorizontalTextAlignment HorizontalAlignment = EText3DHorizontalTextAlignment::Left;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Layout", meta = (AllowPrivateAccess = "true", CustomAlignmentWidget))` — Horizontal text alignment
- L191 _protected member_ `EText3DVerticalTextAlignment VerticalAlignment = EText3DVerticalTextAlignment::FirstLine;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Layout", meta = (AllowPrivateAccess = "true", CustomAlignmentWidget))` — Vertical text alignment
- L195 _protected member_ `float Tracking = 0.0f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Layout", meta = (AllowPrivateAccess = "true"))` — Text tracking affects all characters
- L199 _protected member_ `float LineSpacing = 0.0f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Layout", meta = (AllowPrivateAccess = "true"))` — Extra line spacing
- L203 _protected member_ `float WordSpacing = 0.0f;` — `UPROPERTY(EditAnywhere, Setter, Category = "Layout", meta = (AllowPrivateAccess = "true"))` — Extra word spacing
- L207 _protected member_ `float MaxWidth = 500.f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Layout", meta = (EditCondition = "bUseMaxWidth", DisplayAfter="bUseMaxWidth", ClampMin = 1, AllowPrivateAccess = "true"))` — Sets a maximum width to the 3D Text
- L211 _protected member_ `EText3DMaxWidthHandling MaxWidthBehavior = EText3DMaxWidthHandling::Scale;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Layout", meta = (EditCondition="bUseMaxWidth", DisplayAfter="MaxWidth", AllowPrivateAccess = "true"))` — Dictates how to handle the text if it exceeds the max width
- L215 _protected member_ `float MaxHeight = 500.0f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Layout", meta = (EditCondition = "bUseMaxHeight", DisplayAfter="bUseMaxHeight", ClampMin = 1, AllowPrivateAccess = "true"))` — Sets a maximum height to the 3D Text
- L219 _protected member_ `bool bUseMaxWidth = false;` — `UPROPERTY(EditAnywhere, Getter = "GetUseMaxWidth", Setter = "SetUseMaxWidth", Category = "Layout", meta = (AllowPrivateAccess = "true"))` — Enables a maximum width to the 3D Text
- L223 _protected member_ `bool bUseMaxHeight = false;` — `UPROPERTY(EditAnywhere, Getter = "GetUseMaxHeight", Setter = "SetUseMaxHeight", Category = "Layout", meta = (AllowPrivateAccess = "true"))` — Enables a maximum height to the 3D Text
- L227 _protected member_ `bool bScaleProportionally = true;` — `UPROPERTY(EditAnywhere, Getter = "GetScalesProportionally", Setter = "SetScaleProportionally", Category = "Layout", meta = (AllowPrivateAccess = "true"))` — Should the mesh scale proportionally when Max Width/Height is set
- L231 _protected member_ `ETextShapingMethod TextShapingMethod = ETextShapingMethod::Auto;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Layout", meta = (AllowPrivateAccess = "true"), AdvancedDisplay)` — The method to use for shaping the text
- L235 _private member_ `FVector TextScale = FVector::ZeroVector;` — Additional scale to apply to the text.
- L238 _private member_ `TSharedPtr<UE::Text3D::Layout::FGlyphText> GlyphText;` — Caches the last result of ShapedText, to allow faster updates of layout changes.
- L241 _private member_ `TSharedPtr<FText3DLayout> TextLayout;` — Stores the text layout calculated by the TextLayoutMarshaller.
- L244 _private member_ `TSharedPtr<FRichTextLayoutMarshaller> TextLayoutMarshaller;` — Determines how text is laid out, ie. parsing line breaks.
- L247 _private member_ `TArray<UE::Text3D::Geometry::FCachedFontFaceGlyphHandle> GlyphHandles;` — Temporary storage for the glyph handles while text is built

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Text3D` (scope `UE`)
- L12 _namespace_ `namespace Layout` (scope `UE::Text3D`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DDefaultMaterialExtension.h` (Public)


#### class `UText3DDefaultMaterialExtension`  
`class UText3DDefaultMaterialExtension : public UText3DMaterialExtensionBase`  
_L13-364_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UText3DMaterialExtensionBase`
- L19 _public prototype_ `void SetStyle(EText3DMaterialStyle InStyle);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L22 _public function_ `EText3DMaterialStyle GetStyle() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L28 _public prototype_ `void SetFrontColor(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L31 _public function_ `const FLinearColor& GetFrontColor() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L37 _public prototype_ `void SetBackColor(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L40 _public function_ `const FLinearColor& GetBackColor() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L46 _public prototype_ `void SetExtrudeColor(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L49 _public function_ `const FLinearColor& GetExtrudeColor() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L55 _public prototype_ `void SetBevelColor(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L58 _public function_ `const FLinearColor& GetBevelColor() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L64 _public prototype_ `void SetGradientColorA(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L67 _public function_ `const FLinearColor& GetGradientColorA() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L73 _public prototype_ `void SetGradientColorB(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L76 _public function_ `const FLinearColor& GetGradientColorB() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L82 _public prototype_ `void SetGradientSmoothness(float InGradientSmoothness);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L85 _public function_ `float GetGradientSmoothness() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L91 _public prototype_ `void SetGradientOffset(float InGradientOffset);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L94 _public function_ `float GetGradientOffset() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L100 _public prototype_ `void SetGradientRotation(float InGradientRotation);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L103 _public function_ `float GetGradientRotation() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L109 _public prototype_ `void SetTextureAsset(UTexture2D* InTextureAsset);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L112 _public function_ `UTexture2D* GetTextureAsset() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L118 _public prototype_ `void SetTextureTiling(const FVector2D& InTextureTiling);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L121 _public function_ `const FVector2D& GetTextureTiling() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L127 _public prototype_ `void SetBlendMode(EText3DMaterialBlendMode InBlendMode);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L130 _public function_ `EText3DMaterialBlendMode GetBlendMode() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L136 _public prototype_ `void SetIsUnlit(bool bInIsUnlit);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L139 _public function_ `bool GetIsUnlit() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L145 _public prototype_ `void SetOpacity(float InOpacity);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L148 _public function_ `float GetOpacity() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L154 _public prototype_ `void SetUseMask(bool bInUseMask);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L157 _public function_ `bool GetUseMask() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L163 _public prototype_ `void SetMaskOffset(float InMaskOffset);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L166 _public function_ `float GetMaskOffset() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L172 _public prototype_ `void SetMaskSmoothness(float InMaskSmoothness);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L175 _public function_ `float GetMaskSmoothness() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L181 _public prototype_ `void SetMaskRotation(float InMaskRotation);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L184 _public function_ `float GetMaskRotation() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L190 _public prototype_ `void SetUseSingleMaterial(bool bInUse);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L193 _public function_ `bool GetUseSingleMaterial() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L199 _public prototype_ `void SetFrontMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L202 _public function_ `UMaterialInterface* GetFrontMaterial() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L208 _public prototype_ `void SetBevelMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L211 _public function_ `UMaterialInterface* GetBevelMaterial() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L217 _public prototype_ `void SetExtrudeMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L220 _public function_ `UMaterialInterface* GetExtrudeMaterial() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L226 _public prototype_ `void SetBackMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Material")`
- L229 _public function_ `UMaterialInterface* GetBackMaterial() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Material")`
- L234 _public prototype_ `FVector GetGradientDirection() const;`
- L236 _public prototype_ `void PreCacheMaterials();`
- L239 _public prototype_ `virtual void PostLoad() override;`
- L240 _public prototype_ `virtual void PostInitProperties() override;`
- L241 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L243 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L244 _public prototype_ `virtual void PostEditUndo() override;`
- L249 _public prototype_ `virtual EText3DExtensionResult PreRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L250 _public prototype_ `virtual EText3DExtensionResult PostRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L254 _public prototype_ `virtual void SetMaterial(const UE::Text3D::Material::FMaterialParameters& InParameters, UMaterialInterface* InMaterial) override;`
- L255 _public prototype_ `virtual UMaterialInterface* GetMaterial(const UE::Text3D::Material::FMaterialParameters& InParameters) const override;`
- L256 _public prototype_ `virtual void RegisterMaterialOverride(FName InTag) override;`
- L257 _public prototype_ `virtual void UnregisterMaterialOverride(FName InTag) override;`
- L258 _public prototype_ `virtual void ForEachMaterial(TFunctionRef<bool(const UE::Text3D::Material::FMaterialParameters&, UMaterialInterface*)> InFunctor) const override;`
- L259 _public prototype_ `virtual int32 GetMaterialCount() const override;`
- L260 _public prototype_ `virtual void GetMaterialNames(TArray<FName>& OutNames) const override;`
- L264 _protected prototype_ `UMaterialInstanceDynamic* FindOrAdd(EText3DGroupType InGroup, FName InTag = NAME_None);`
- L265 _protected prototype_ `UMaterialInstanceDynamic* Find(EText3DGroupType InGroup, FName InTag = NAME_None) const;`
- L266 _protected prototype_ `void SetVectorParameter(TConstArrayView<UMaterialInstanceDynamic*> InMaterials, FName InKey, FVector InValue);`
- L267 _protected prototype_ `void SetVectorParameter(TConstArrayView<UMaterialInstanceDynamic*> InMaterials, FName InKey, FLinearColor InValue);`
- L268 _protected prototype_ `void SetScalarParameter(TConstArrayView<UMaterialInstanceDynamic*> InMaterials, FName InKey, float InValue);`
- L269 _protected prototype_ `void SetTextureParameter(TConstArrayView<UMaterialInstanceDynamic*> InMaterials, FName InKey, UTexture* InValue);`
- L270 _protected prototype_ `void OnMaterialOptionsChanged();`
- L271 _protected prototype_ `void OnCustomMaterialChanged();`
- L274 _protected prototype_ `void ClearParameterValues();` — Clears the parameter values of all materials that are MIDs in this extension
- L277 _protected member_ `EText3DMaterialStyle Style = EText3DMaterialStyle::Solid;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(AllowPrivateAccess="true"))`
- L280 _protected member_ `FLinearColor FrontColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(EditCondition="Style == EText3DMaterialStyle::Solid", EditConditionHides, AllowPrivateAccess="true"))`
- L283 _protected member_ `FLinearColor BackColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(EditCondition="Style == EText3DMaterialStyle::Solid", EditConditionHides, AllowPrivateAccess="true"))`
- L286 _protected member_ `FLinearColor ExtrudeColor = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(EditCondition="Style == EText3DMaterialStyle::Solid", EditConditionHides, AllowPrivateAccess="true"))`
- L289 _protected member_ `FLinearColor BevelColor = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(EditCondition="Style == EText3DMaterialStyle::Solid", EditConditionHides, AllowPrivateAccess="true"))`
- L292 _protected member_ `FLinearColor GradientColorA = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(EditCondition="Style == EText3DMaterialStyle::Gradient", EditConditionHides, AllowPrivateAccess="true"))`
- L295 _protected member_ `FLinearColor GradientColorB = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(EditCondition="Style == EText3DMaterialStyle::Gradient", EditConditionHides, AllowPrivateAccess="true"))`
- L298 _protected member_ `float GradientSmoothness = 0.1f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(ClampMin=0.0, ClampMax=1.0, EditCondition="Style == EText3DMaterialStyle::Gradient", EditConditionHides, AllowPrivateAccess="true"))`
- L301 _protected member_ `float GradientOffset = 0.5f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta = (ClampMin=0.0, ClampMax=1.0, EditCondition="Style == EText3DMaterialStyle::Gradient", EditConditionHides, AllowPrivateAccess="true"))`
- L304 _protected member_ `float GradientRotation = 0.0f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta = (ClampMin=0.0, ClampMax=1.0, EditCondition="Style == EText3DMaterialStyle::Gradient", EditConditionHides, AllowPrivateAccess="true"))`
- L307 _protected member_ `TObjectPtr<UTexture2D> TextureAsset;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(EditCondition="Style == EText3DMaterialStyle::Texture", EditConditionHides, AllowPrivateAccess="true"))`
- L310 _protected member_ `FVector2D TextureTiling = FVector2D::One();` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(Delta=0.1, EditCondition="Style == EText3DMaterialStyle::Texture", EditConditionHides, AllowPrivateAccess="true"))`
- L313 _protected member_ `bool bIsUnlit = true;` — `UPROPERTY(EditAnywhere, Getter="GetIsUnlit", Setter="SetIsUnlit", Category="Material", meta=(EditCondition="Style != EText3DMaterialStyle::Custom", EditConditionHides, AllowPrivateAccess="true"))`
- L316 _protected member_ `EText3DMaterialBlendMode BlendMode = EText3DMaterialBlendMode::Opaque;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(EditCondition="Style != EText3DMaterialStyle::Custom", EditConditionHides, AllowPrivateAccess="true"))`
- L319 _protected member_ `float Opacity = 1.f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(ClampMin=0.0, ClampMax=1.0, EditCondition="Style != EText3DMaterialStyle::Custom && BlendMode == EText3DMaterialBlendMode::Translucent", EditConditionHides, AllowPrivateAccess="true"))`
- L323 _protected member_ `bool bUseMask = false;` — `UPROPERTY(EditAnywhere, Getter="GetUseMask", Setter="SetUseMask", Category="Material", meta=(EditCondition="Style != EText3DMaterialStyle::Custom && BlendMode == EText3DMaterialBlendMode::Translucent", EditConditionHides, AllowPrivateAccess="true"))` — Enable text shader mask
- L326 _protected member_ `float MaskOffset = 1.f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(ClampMin=0.0, ClampMax=1.0, EditCondition="bUseMask && Style != EText3DMaterialStyle::Custom && BlendMode == EText3DMaterialBlendMode::Translucent", EditConditionHides, AllowPrivateAccess="true"))`
- L329 _protected member_ `float MaskSmoothness = 0.1f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(ClampMin=0.0, ClampMax=1.0, EditCondition="bUseMask && Style != EText3DMaterialStyle::Custom && BlendMode == EText3DMaterialBlendMode::Translucent", EditConditionHides, AllowPrivateAccess="true"))`
- L332 _protected member_ `float MaskRotation = 0.0f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category="Material", meta=(ClampMin=0.0, ClampMax=1.0, EditCondition="bUseMask && Style != EText3DMaterialStyle::Custom && BlendMode == EText3DMaterialBlendMode::Translucent", EditConditionHides, AllowPrivateAccess="true"))`
- L336 _protected member_ `bool bUseSingleMaterial = false;` — `UPROPERTY(EditAnywhere, Getter="GetUseSingleMaterial", Setter="SetUseSingleMaterial", Category = "Material", meta = (EditCondition="Style == EText3DMaterialStyle::Custom", EditConditionHides, AllowPrivateAccess = "true"))` — Use primary material for all available slots
- L340 _protected member_ `TObjectPtr<UMaterialInterface> FrontMaterial;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Material", meta = (EditCondition="Style == EText3DMaterialStyle::Custom", EditConditionHides, AllowPrivateAccess = "true"))` — Material for the front part
- L344 _protected member_ `TObjectPtr<UMaterialInterface> BevelMaterial;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Material", meta = (EditCondition="!bUseSingleMaterial && Style == EText3DMaterialStyle::Custom", EditConditionHides, AllowPrivateAccess = "true"))` — Material for the bevel part
- L348 _protected member_ `TObjectPtr<UMaterialInterface> ExtrudeMaterial;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Material", meta = (EditCondition="!bUseSingleMaterial && Style == EText3DMaterialStyle::Custom", EditConditionHides, AllowPrivateAccess = "true"))` — Material for the extruded part
- L352 _protected member_ `TObjectPtr<UMaterialInterface> BackMaterial;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Material", meta = (EditCondition="!bUseSingleMaterial && Style == EText3DMaterialStyle::Custom", EditConditionHides, AllowPrivateAccess = "true"))` — Material for the back part
- L356 _protected member_ `TArray<FText3DMaterialOverride> MaterialOverrides;` — `UPROPERTY(Transient, DuplicateTransient)` — Additional overrides defined for specific group
- L360 _protected member_ `TMap<FText3DMaterialGroupKey, TObjectPtr<UMaterialInstanceDynamic>> GroupDynamicMaterials;` — `UPROPERTY(Transient, DuplicateTransient)` — Cached group dynamic materials created during session based on their options
- L363 _protected member_ `FBox LocalTextBounds = FBox(ForceInitToZero);` — Used to pass bounds to material

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DDefaultRenderingExtension.h` (Public)


#### class `UText3DDefaultRenderingExtension`  
`class UText3DDefaultRenderingExtension : public UText3DRenderingExtensionBase`  
_L11-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UText3DRenderingExtensionBase`
- desc: Extension that handles rendering data for Text3D
- L18 _public function_ `bool GetCastShadow() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Rendering")` — Get the value of CastShadow.
- L25 _public prototype_ `void SetCastShadow(bool bInCastShadow);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Rendering")` — Set the value of CastShadow.
- L29 _public function_ `bool GetCastHiddenShadow() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Rendering")` — Get the value of CastHiddenShadow.
- L36 _public prototype_ `void SetCastHiddenShadow(bool bInCastShadow);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Rendering")` — Set the value of CastHiddenShadow.
- L40 _public function_ `bool GetAffectDynamicIndirectLighting() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Rendering")` — Get the value of AffectDynamicIndirectLighting.
- L47 _public prototype_ `void SetAffectDynamicIndirectLighting(bool bInValue);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Rendering")` — Set the value of AffectDynamicIndirectLighting.
- L51 _public function_ `bool GetAffectIndirectLightingWhileHidden() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Rendering")` — Get the value of AffectIndirectLightingWhileHidden.
- L58 _public prototype_ `void SetAffectIndirectLightingWhileHidden(bool bInValue);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Rendering")` — Set the value of AffectIndirectLightingWhileHidden.
- L62 _public function_ `bool GetHoldout() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Rendering")` — Get the value of Holdout.
- L69 _public prototype_ `void SetHoldout(bool bInHoldout);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Rendering")` — Set the value of Holdout.
- L74 _protected prototype_ `virtual void PostEditUndo() override;`
- L75 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L80 _protected prototype_ `virtual bool GetTextCastShadow() const override;`
- L81 _protected prototype_ `virtual bool GetTextCastHiddenShadow() const override;`
- L82 _protected prototype_ `virtual bool GetTextAffectDynamicIndirectLighting() const override;`
- L83 _protected prototype_ `virtual bool GetTextAffectIndirectLightingWhileHidden() const override;`
- L84 _protected prototype_ `virtual bool GetTextHoldout() const override;`
- L87 _protected prototype_ `void OnRenderingOptionsChanged();`
- L91 _protected member_ `bool bCastShadow = true;` — `UPROPERTY(EditAnywhere, Getter = "GetCastShadow", Setter = "SetCastShadow", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Controls whether the text glyphs should cast a shadow or not.
- L95 _protected member_ `bool bCastHiddenShadow = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Hidden Shadow", Getter = "GetCastShadow", Setter = "SetCastShadow", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Controls whether the text glyphs should cast a shadow or not.
- L99 _protected member_ `bool bAffectDynamicIndirectLighting = true;` — `UPROPERTY(EditAnywhere, Getter = "GetAffectDynamicIndirectLighting", Setter = "SetAffectDynamicIndirectLighting", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Controls whether the primitive should influence indirect lighting.
- L103 _protected member_ `bool bAffectIndirectLightingWhileHidden = false;` — `UPROPERTY(EditAnywhere, Getter="GetAffectIndirectLightingWhileHidden", Setter="SetAffectIndirectLightingWhileHidden", Category = "Rendering", meta = (EditCondition = "bAffectDynamicIndirectLighting", AllowPrivateAccess = "true"))` — Controls whether the primitive should affect indirect lighting when hidden. This flag is only used if bAffectDynamicIndirectLighting is true.
- L107 _protected member_ `bool bHoldout = false;` — `UPROPERTY(EditAnywhere, Getter="GetHoldout", Setter="SetHoldout", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — If this is True, this primitive will render black with an alpha of 0, but all secondary effects (shadows, reflections, indirect lighting) remain. This feature requires activating the project setting(s) "Alpha Output", and "Support Primitive Alpha Holdout" if using the deferred renderer.

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DDefaultStyleExtension.h` (Public)


#### class `UText3DDefaultStyleExtension`  
`class UText3DDefaultStyleExtension : public UText3DStyleExtensionBase`  
_L15-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UText3DStyleExtensionBase`
- L20 _public prototype_ `UText3DDefaultStyleExtension();`
- L23 _public prototype_ `void SetStyleSet(UText3DStyleSet* InStyleSet);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L26 _public function_ `UText3DStyleSet* GetStyleSet() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L34 _protected prototype_ `virtual void PostEditUndo() override;`
- L35 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L40 _protected prototype_ `virtual TSharedPtr<FTextBlockStyle> GetDefaultStyle() const override;`
- L41 _protected prototype_ `virtual TSharedPtr<FSlateStyleSet> GetCustomStyles() const override;`
- L42 _protected prototype_ `virtual UText3DStyleBase* GetStyle(FName InStyle) const override;`
- L46 _protected prototype_ `virtual void PrepareBuild(EText3DRendererFlags InUpdateFlags) override;`
- L47 _protected prototype_ `virtual EText3DExtensionResult PreRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L48 _protected prototype_ `virtual EText3DExtensionResult PostRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L51 _protected prototype_ `void OnStyleSetUpdated(UText3DStyleSet* InStyleSet);`
- L52 _protected prototype_ `void OnStyleSetChanged();`
- L56 _protected member_ `TObjectPtr<UText3DStyleSet> StyleSet;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Style", meta=(AllowPrivateAccess="true"))` — A style set asset that defines custom style rules
- L63 _protected member_ `TArray<TObjectPtr<UText3DStyleBase>> Styles;` — `UPROPERTY(EditAnywhere, Instanced, DisplayName="Styles Override", Category="Style", NoClear, meta=(AllowPrivateAccess="true"))` — Define your styles and use them in text like this <MyStyle>...</>, the text between start and end tag will have this style applied
- L66 _private member_ `TSharedPtr<FTextBlockStyle> DefaultFontStyle;`
- L67 _private member_ `TSharedPtr<FSlateStyleSet> TextStyleSet;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DDefaultTokenExtension.h` (Public)


#### class `UText3DDefaultTokenExtension`  
`class UText3DDefaultTokenExtension : public UText3DTokenExtensionBase`  
_L12-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UText3DTokenExtensionBase`
- L19 _protected prototype_ `virtual void PostEditUndo() override;`
- L20 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L25 _protected prototype_ `virtual const FText& GetFormattedText() const override;`
- L29 _protected prototype_ `virtual void PrepareBuild(EText3DRendererFlags InUpdateFlags) override;`
- L30 _protected prototype_ `virtual EText3DExtensionResult PreRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L31 _protected prototype_ `virtual EText3DExtensionResult PostRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L40 _protected member_ `TArray<TObjectPtr<UText3DTokenBase>> Tokens;` — `UPROPERTY(EditAnywhere, Instanced, Category="Token", NoClear, meta=(AllowPrivateAccess="true"))` — Define your tokens and use them in text like this {MyCustomToken}, {MyCustomToken} will be swapped by the content of the token called MyCustomToken, This can be used with remote control or sequencer to swap part of the text
- L43 _protected member_ `FText FormattedText;` — `UPROPERTY(Transient)`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DEffectExtensionBase.h` (Public)


#### struct `FText3DRange`  
`struct FText3DRange`  
_L9-45_
- L11 _public member_ `static constexpr uint16 Unbound = std::numeric_limits<uint16>::max();`
- L13 _public prototype_ `FText3DRange() = default;`
- L14 _public function_ `explicit FText3DRange(uint16 InStartIndex, uint16 InCount) : StartIndex(InStartIndex) , Count(InCount)`
- L20 _public function_ `bool IsUnbound() const`
- L25 _public function_ `bool IsEndUnbound() const`
- L30 _public function_ `bool IsStartUnbound() const`
- L35 _public function_ `bool IsInRange(uint16 InIndex) const`
- L43 _public member_ `uint16 StartIndex = Unbound;`
- L44 _public member_ `uint16 Count = Unbound;`

#### class `UText3DEffectExtensionBase`  
`class UText3DEffectExtensionBase : public UText3DExtensionBase`  
_L49-76_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DExtensionBase`
- desc: Extension for custom effects on Text3D
- L54 _public function_ `UText3DEffectExtensionBase() : UText3DExtensionBase()`
- L58 _public function_ `explicit UText3DEffectExtensionBase(uint16 InPriority) : UText3DExtensionBase(InPriority)`
- L64 _protected prototype_ `virtual EText3DExtensionResult PreRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L65 _protected prototype_ `virtual EText3DExtensionResult PostRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) override;`
- L68 _protected function_ `virtual FText3DRange GetTargetRange() const`
- L73 _protected function_ `virtual void ApplyEffect(uint32 InCharacterIndex, uint32 InCharacterCount)`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DExtensionBase.h` (Public)


#### enum `EText3DExtensionResult`  
`enum class EText3DExtensionResult : uint8`  
_L11-19_
- L14 _public enumerator_ `Active` — Extension is still needed, keep it around
- L16 _public enumerator_ `Finished` — Extension is done for this update round, should not be called anymore
- L18 _public enumerator_ `Failed` — Extension failed to execute properly, do not continue

#### class `UText3DExtensionBase`  
`class UText3DExtensionBase : public UObject`  
_L26-69_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UObject`
- desc: Extensions are piece of data and logic needed to render Text3D that can be reused by multiple renderers, they execute once during every renderer update at the right moment
- L31 _public function_ `UText3DExtensionBase() : UText3DExtensionBase(0)`
- L35 _public function_ `UText3DExtensionBase(uint16 InPriority) : UpdatePriority(InPriority)`
- L40 _public function_ `virtual void PrepareBuild(EText3DRendererFlags InUpdateFlags)` — Prepare the extensions before a build occurs
- L45 _public function_ `virtual EText3DExtensionResult PreRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters)` — Perform an update of the extension behavior before renderer execute based on condition above
- L51 _public function_ `virtual EText3DExtensionResult PostRendererUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters)` — Perform an update of the extension behavior after renderer execute based on condition above
- L57 _public function_ `uint16 GetUpdatePriority() const` — Used to sort extensions and execute them before others
- L62 _public prototype_ `UText3DComponent* GetText3DComponent() const;`
- L65 _protected prototype_ `void RequestUpdate(EText3DRendererFlags InFlags, bool bInImmediateUpdate=false) const;`
- L68 _private member_ `uint16 UpdatePriority = 0;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DGeometryExtensionBase.h` (Public)


#### class `UText3DGeometryExtensionBase`  
`class UText3DGeometryExtensionBase : public UText3DExtensionBase`  
_L18-53_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DExtensionBase`
- desc: Extension that handles geometry data for Text3D
- L23 _public function_ `UText3DGeometryExtensionBase() : UText3DExtensionBase(UE::Text3D::Priority::Geometry)`
- L29 _public function_ `virtual const FText3DCachedMesh* FindOrLoadGlyphMesh(UText3DCharacterBase* InCharacter) const final` — `UE_DEPRECATED(5.7, "Deprecated do not use anymore, use character getter directly")` — Deprecated do not use anymore, use character getter directly
- L34 _public function_ `virtual EText3DHorizontalTextAlignment GetGlyphHAlignment() const`
- L39 _public function_ `virtual EText3DVerticalTextAlignment GetGlyphVAlignment() const`
- L44 _public function_ `virtual ECollisionEnabled::Type GetGlyphCollisionEnabled() const`
- L49 _public function_ `virtual const FGlyphMeshParameters* GetGlyphMeshParameters() const`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DLayoutEffectBase.h` (Public)


#### class `UText3DLayoutEffectBase`  
`class UText3DLayoutEffectBase : public UText3DEffectExtensionBase`  
_L10-18_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DEffectExtensionBase`
- desc: Extension for layout effects on Text3D
- L15 _public function_ `UText3DLayoutEffectBase() : UText3DEffectExtensionBase(UE::Text3D::Priority::Effect)`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DLayoutExtensionBase.h` (Public)


#### class `UText3DLayoutExtensionBase`  
`class UText3DLayoutExtensionBase : public UText3DExtensionBase`  
_L13-36_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DExtensionBase`
- desc: Extension that handles layout data for Text3D
- L18 _public function_ `UText3DLayoutExtensionBase() : UText3DExtensionBase(UE::Text3D::Priority::Layout)`
- L22 _public function_ `virtual float GetTextHeight() const`
- L27 _public function_ `virtual FVector GetTextScale() const`
- L32 _public function_ `virtual FVector GetLineLocation(int32 LineIndex) const`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DLayoutTransformEffect.h` (Public)


#### class `UText3DLayoutTransformEffect`  
`class UText3DLayoutTransformEffect : public UText3DLayoutEffectBase`  
_L13-276_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, ClassGroup=Text3D, DisplayName="TransformEffect", AutoExpandCategories=(Transform))`
- inherits: `UText3DLayoutEffectBase`
- desc: Extension that handles transform data for Text3D
- L19 _public prototype_ `void SetLocationEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L21 _public function_ `bool GetLocationEnabled() const`
- L27 _public prototype_ `void SetLocationProgress(float Progress);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L29 _public function_ `float GetLocationProgress() const`
- L35 _public prototype_ `void SetLocationOrder(EText3DCharacterEffectOrder Order);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L37 _public function_ `EText3DCharacterEffectOrder GetLocationOrder() const`
- L43 _public prototype_ `void SetLocationBegin(const FVector& InBegin);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L45 _public function_ `FVector GetLocationBegin() const`
- L51 _public prototype_ `void SetLocationEnd(const FVector& InEnd);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L53 _public function_ `FVector GetLocationEnd() const`
- L59 _public prototype_ `void SetLocationEaseCurve(UCurveFloat* InEaseCurve);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L61 _public function_ `UCurveFloat* GetLocationEaseCurve() const`
- L67 _public prototype_ `void SetLocationStagger(bool bInStagger);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L69 _public function_ `bool GetLocationStagger() const`
- L75 _public prototype_ `void SetRotationEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L77 _public function_ `bool GetRotationEnabled() const`
- L83 _public prototype_ `void SetRotationProgress(float Progress);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L85 _public function_ `float GetRotationProgress() const`
- L91 _public prototype_ `void SetRotationOrder(EText3DCharacterEffectOrder Order);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L93 _public function_ `EText3DCharacterEffectOrder GetRotationOrder() const`
- L99 _public prototype_ `void SetRotationBegin(const FRotator& Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L101 _public function_ `FRotator GetRotationBegin() const`
- L107 _public prototype_ `void SetRotationEnd(const FRotator& Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L109 _public function_ `FRotator GetRotationEnd() const`
- L115 _public prototype_ `void SetRotationEaseCurve(UCurveFloat* InEaseCurve);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L117 _public function_ `UCurveFloat* GetRotationEaseCurve() const`
- L123 _public prototype_ `void SetRotationStagger(bool bInStagger);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L125 _public function_ `bool GetRotationStagger() const`
- L131 _public prototype_ `void SetScaleEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L133 _public function_ `bool GetScaleEnabled() const`
- L139 _public prototype_ `void SetScaleProgress(float Progress);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L141 _public function_ `float GetScaleProgress() const`
- L147 _public prototype_ `void SetScaleOrder(EText3DCharacterEffectOrder Order);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L149 _public function_ `EText3DCharacterEffectOrder GetScaleOrder() const`
- L155 _public prototype_ `void SetScaleBegin(const FVector& Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L157 _public function_ `FVector GetScaleBegin() const`
- L163 _public prototype_ `void SetScaleEnd(const FVector& Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L165 _public function_ `FVector GetScaleEnd() const`
- L171 _public prototype_ `void SetScaleEaseCurve(UCurveFloat* InEaseCurve);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L173 _public function_ `UCurveFloat* GetScaleEaseCurve() const`
- L179 _public prototype_ `void SetScaleStagger(bool bInStagger);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Transform")`
- L181 _public function_ `bool GetScaleStagger() const`
- L187 _protected prototype_ `UText3DLayoutTransformEffect();`
- L191 _protected prototype_ `virtual void PostEditUndo() override;`
- L192 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L197 _protected prototype_ `virtual void ApplyEffect(uint32 InGlyphIndex, uint32 InGlyphCount) override;`
- L200 _protected prototype_ `void OnTransformOptionsChanged();`
- L202 _protected prototype_ `int32 GetEffectPosition(int32 Index, int32 Total, EText3DCharacterEffectOrder Order) const;`
- L203 _protected prototype_ `float CalculateEffect(int32 InIndex, int32 InTotal, EText3DCharacterEffectOrder InOrder, float InProgress, const UCurveFloat* InEaseCurve, bool bInStagger) const;`
- L208 _protected member_ `bool bLocationEnabled = false;` — `UPROPERTY(EditAnywhere, Getter="GetLocationEnabled", Setter="SetLocationEnabled", Category = "Transform")`
- L211 _protected member_ `float LocationProgress = 0.f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bLocationEnabled", EditConditionHides, ClampMin = 0, ClampMax = 100, Units=Percent))`
- L214 _protected member_ `EText3DCharacterEffectOrder LocationOrder = EText3DCharacterEffectOrder::Normal;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bLocationEnabled", EditConditionHides))`
- L217 _protected member_ `FVector LocationBegin = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bLocationEnabled", EditConditionHides))`
- L220 _protected member_ `FVector LocationEnd = FVector(100.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bLocationEnabled", EditConditionHides))`
- L224 _protected member_ `TObjectPtr<UCurveFloat> LocationEaseCurve;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category = "Transform", meta = (EditCondition = "bLocationEnabled", EditConditionHides))` — Provide a 0-1 ease curve, leaving this unset will result in linear ease
- L227 _protected member_ `bool bLocationStagger = false;` — `UPROPERTY(EditAnywhere, Getter="GetLocationStagger", Setter="SetLocationStagger", Category = "Transform", meta = (EditCondition = "bLocationEnabled", EditConditionHides))`
- L232 _protected member_ `bool bRotationEnabled = false;` — `UPROPERTY(EditAnywhere, Getter="GetRotationEnabled", Setter="SetRotationEnabled", Category = "Transform")`
- L235 _protected member_ `float RotationProgress = 0.0f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bRotationEnabled", EditConditionHides, ClampMin = 0, ClampMax = 100, Units=Percent))`
- L238 _protected member_ `EText3DCharacterEffectOrder RotationOrder = EText3DCharacterEffectOrder::Normal;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bRotationEnabled", EditConditionHides))`
- L241 _protected member_ `FRotator RotationBegin = FRotator(-90.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bRotationEnabled", EditConditionHides))`
- L244 _protected member_ `FRotator RotationEnd = FRotator(0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bRotationEnabled", EditConditionHides))`
- L248 _protected member_ `TObjectPtr<UCurveFloat> RotationEaseCurve;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category = "Transform", meta = (EditCondition = "bRotationEnabled", EditConditionHides))` — Provide a 0-1 ease curve, leaving this unset will result in linear ease
- L251 _protected member_ `bool bRotationStagger = false;` — `UPROPERTY(EditAnywhere, Getter="GetRotationStagger", Setter="SetRotationStagger", Category = "Transform", meta = (EditCondition = "bRotationEnabled", EditConditionHides))`
- L256 _protected member_ `bool bScaleEnabled = false;` — `UPROPERTY(EditAnywhere, Getter="GetScaleEnabled", Setter="SetScaleEnabled", Category = "Transform")`
- L259 _protected member_ `float ScaleProgress = 0.f;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bScaleEnabled", EditConditionHides, ClampMin = 0, ClampMax = 100, Units=Percent))`
- L262 _protected member_ `EText3DCharacterEffectOrder ScaleOrder = EText3DCharacterEffectOrder::Normal;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bScaleEnabled", EditConditionHides))`
- L265 _protected member_ `FVector ScaleBegin = FVector(1.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bScaleEnabled", EditConditionHides, ClampMin = 0))`
- L268 _protected member_ `FVector ScaleEnd = FVector::OneVector;` — `UPROPERTY(EditAnywhere, Getter, Setter, Category = "Transform", meta = (EditCondition = "bScaleEnabled", EditConditionHides, ClampMin = 0))`
- L272 _protected member_ `TObjectPtr<UCurveFloat> ScaleEaseCurve;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category = "Transform", meta = (EditCondition = "bScaleEnabled", EditConditionHides))` — Provide a 0-1 ease curve, leaving this unset will result in linear ease
- L275 _protected member_ `bool bScaleStagger = false;` — `UPROPERTY(EditAnywhere, Getter="GetScaleStagger", Setter="SetScaleStagger", Category = "Transform", meta = (EditCondition = "bScaleEnabled", EditConditionHides))`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DMaterialExtensionBase.h` (Public)


#### class `UText3DMaterialExtensionBase`  
`class UText3DMaterialExtensionBase : public UText3DExtensionBase`  
_L13-77_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DExtensionBase`
- desc: Extension that handles materials for Text3D
- L18 _public function_ `UText3DMaterialExtensionBase() : UText3DExtensionBase(UE::Text3D::Priority::Material)`
- L24 _public function_ `virtual void SetMaterial(EText3DGroupType InGroup, UMaterialInterface* InMaterial)` — `UE_DEPRECATED(5.7, "Please use SetMaterial with FMaterialParameters instead")` — Set default material for a specific group
- L33 _public function_ `virtual UMaterialInterface* GetMaterial(EText3DGroupType InGroup) const` — `UE_DEPRECATED(5.7, "Please use GetMaterial with FMaterialParameters instead")` — Get default material of a specific group
- L41 _public function_ `virtual void SetMaterial(const UE::Text3D::Material::FMaterialParameters& InParameters, UMaterialInterface* InMaterial)` — Set the material for a specific group
- L47 _public function_ `virtual UMaterialInterface* GetMaterial(const UE::Text3D::Material::FMaterialParameters& InParameters) const` — Get the material for a specific group
- L53 _public function_ `virtual void RegisterMaterialOverride(FName InTag)` — Register a new material override
- L58 _public function_ `virtual void UnregisterMaterialOverride(FName InTag)` — Unregister a material override previously defined
- L63 _public function_ `virtual void ForEachMaterial(TFunctionRef<bool(const UE::Text3D::Material::FMaterialParameters&, UMaterialInterface*)> InFunctor) const` — Loop through each material available, return false to stop the operation
- L68 _public function_ `virtual int32 GetMaterialCount() const` — Get amount of material in use
- L74 _public function_ `virtual void GetMaterialNames(TArray<FName>& OutNames) const` — Retrieve material override names

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DRenderingExtensionBase.h` (Public)


#### class `UText3DRenderingExtensionBase`  
`class UText3DRenderingExtensionBase : public UText3DExtensionBase`  
_L11-44_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DExtensionBase`
- desc: Extension that handles rendering data for Text3D
- L16 _public function_ `UText3DRenderingExtensionBase() : UText3DExtensionBase(UE::Text3D::Priority::Rendering)`
- L20 _public function_ `virtual bool GetTextCastShadow() const`
- L25 _public function_ `virtual bool GetTextCastHiddenShadow() const`
- L30 _public function_ `virtual bool GetTextAffectDynamicIndirectLighting() const`
- L35 _public function_ `virtual bool GetTextAffectIndirectLightingWhileHidden() const`
- L40 _public function_ `virtual bool GetTextHoldout() const`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DStyleExtensionBase.h` (Public)


#### class `UText3DStyleExtensionBase`  
`class UText3DStyleExtensionBase : public UText3DExtensionBase`  
_L17-43_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DExtensionBase`
- desc: Extension that handles formatting styles for Text3D
- L22 _public function_ `UText3DStyleExtensionBase() : UText3DExtensionBase(UE::Text3D::Priority::Style)`
- L27 _public function_ `virtual TSharedPtr<FTextBlockStyle> GetDefaultStyle() const` — Default style used by text when no other style is applied
- L33 _public function_ `virtual TSharedPtr<FSlateStyleSet> GetCustomStyles() const` — Custom defined styles to apply on text
- L39 _public function_ `virtual UText3DStyleBase* GetStyle(FName InStyleName) const` — Get the style with a specific name if any

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Extensions/Text3DTokenExtensionBase.h` (Public)


#### class `UText3DTokenExtensionBase`  
`class UText3DTokenExtensionBase : public UText3DExtensionBase`  
_L11-25_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UText3DExtensionBase`
- desc: Extension that handles text transformation
- L16 _public function_ `UText3DTokenExtensionBase() : UText3DExtensionBase(UE::Text3D::Priority::Token)`
- L21 _public function_ `virtual const FText& GetFormattedText() const` — Get the transformed text

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/IText3DBuildSystem.h` (Public)


#### class `UText3DBuildSystemInterface`  
`class UText3DBuildSystemInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IText3DBuildSystemInterface`  
`class IText3DBuildSystemInterface`  
_L16-32_
- L22 _public prototype_ `virtual bool IsBuildInProgress() const = 0;` — Returns true if there are builders yet to complete
- L28 _public prototype_ `virtual void FlushBuilds() = 0;` — Executes any remaining text builds with no time budget. Warning: This can cause a hitch and should only be used when the result is needed immediately regardless of hitch.
- L31 _public prototype_ `virtual void HidePrimitivesBeingBuilt(FSceneView& InSceneView) const = 0;` — Adds the Text3D-managed primitives that are being built to the scene view's hidden primitive list

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Renderers/Text3DRendererBase.h` (Public)


#### class `UText3DRendererBase`  
`class UText3DRendererBase : public UObject`  
_L18-97_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UObject`
- desc: Base class for a rendering implementation of Text3D The whole rendering logic should be encapsulated into an instance of this class
- L24 _public prototype_ `void Create();` — Allocate renderer resources
- L27 _public prototype_ `void Update(const UE::Text3D::Renderer::FUpdateParameters& InParameters);` — Update rendering state
- L30 _public prototype_ `void Clear();` — Clears the active rendering state
- L33 _public prototype_ `void Destroy();` — Cleanup renderer resources
- L36 _public prototype_ `FBox GetBounds() const;` — Get cached bounds from last update
- L39 _public prototype_ `void IterateManagedPrimitives(TFunctionRef<void(TNotNull<const UPrimitiveComponent*>)> InFunc) const;` — Calls the given functor for every primitive the renderer implementation manages
- L42 _public prototype_ `virtual EText3DMeshType GetMeshType() const PURE_VIRTUAL(UText3DRendererBase::GetMeshType, return EText3DMeshType::Unknown; );` — Get the mesh type that this renderer uses
- L45 _public prototype_ `virtual FName GetFriendlyName() const PURE_VIRTUAL(UText3DRendererBase::GetFriendlyName, return NAME_None; );` — Get the implementation name for debug purposes
- L48 _public function_ `bool IsInitialized() const` — Is the renderer initialized (render state created)
- L55 _protected prototype_ `virtual void OnCreate() PURE_VIRTUAL(UText3DRendererBase::OnCreate, );` — Create and setup the implementation components, called on load or creation
- L58 _protected prototype_ `virtual void OnUpdate(const UE::Text3D::Renderer::FUpdateParameters& InParameters) PURE_VIRTUAL(UText3DRendererBase::OnUpdate, );` — Update rendering state of text characters, called when render state is outdated
- L61 _protected prototype_ `virtual void OnClear() PURE_VIRTUAL(UText3DRendererBase::OnClear, );` — Clear rendering state and remove all visible characters
- L64 _protected prototype_ `virtual void OnDestroy() PURE_VIRTUAL(UText3DRendererBase::OnDestroy, );` — Destroy and clean the implementation components, called on destroy or deactivation
- L67 _protected prototype_ `virtual FBox OnCalculateBounds() const PURE_VIRTUAL(UText3DRendererBase::OnCalculateBounds, return FBox(ForceInitToZero); );` — Calculate the bounds of the rendered text
- L70 _protected function_ `virtual void OnIterateManagedPrimitives(TFunctionRef<void(TNotNull<const UPrimitiveComponent*>)> InFunc) const` — Calls the given functor for every primitive the renderer implementation manages
- L75 _protected prototype_ `void BindDebugDelegate();`
- L76 _protected prototype_ `void UnbindDebugDelegate();`
- L77 _protected prototype_ `void OnTextSettingsChanged(UObject* InSettings, FPropertyChangedEvent& InEvent);`
- L78 _protected prototype_ `void OnDebugModeChanged();`
- L81 _protected function_ `virtual void OnDebugModeEnabled()` — Called when entering debug mode in editor
- L84 _protected function_ `virtual void OnDebugModeDisabled()` — Called when exiting debug mode in editor
- L87 _protected prototype_ `UText3DComponent* GetText3DComponent() const;`
- L90 _protected prototype_ `void RefreshBounds();` — Recalculates bounds when a layout or geometry change happened
- L93 _private member_ `TOptional<FBox> CachedBounds;`
- L94 _private member_ `bool bInitialized = false;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Settings/Text3DProjectSettings.h` (Public)


#### class `UText3DProjectSettings`  
`class UText3DProjectSettings : public UDeveloperSettings`  
_L18-212_
- reflection: `UCLASS(MinimalAPI, Config=Text3D, meta=(DisplayName="Text3D"))`
- inherits: `UDeveloperSettings`
- desc: Settings for Text3D plugin
- L25 _public prototype_ `static const UText3DProjectSettings* Get();`
- L26 _public prototype_ `static UText3DProjectSettings* GetMutable();`
- L29 _public prototype_ `static FName GetDebugModePropertyName();`
- L30 _public prototype_ `static FName GetDefaultMaterialPropertyName();`
- L65 _public prototype_ `UText3DProjectSettings();`
- L67 _public prototype_ `UMaterial* GetDefaultMaterial() const;`
- L68 _public prototype_ `UText3DStyleSet* GetDefaultStyleSet() const;`
- L69 _public prototype_ `UFont* GetFallbackFont() const;`
- L70 _public prototype_ `UFontFace* GetFallbackFontFace() const;`
- L71 _public prototype_ `const FString& GetFontDirectory() const;`
- L73 _public prototype_ `UMaterial* GetBaseMaterial(const FText3DMaterialKey& InKey) const;`
- L76 _public prototype_ `void SetScheduleFontFaceGlyphCleanup(bool bInEnabled);` — `UE_DEPRECATED(5.8, "Font face glyph fixed scheduled cleanup is deprecated. Glyphs are cleaned up on-demand")`
- L79 _public prototype_ `bool GetScheduleFontFaceGlyphCleanup() const;` — `UE_DEPRECATED(5.8, "Font face glyph fixed scheduled cleanup is deprecated. Glyphs are cleaned up on-demand")`
- L82 _public prototype_ `void SetFontFaceGlyphCleanupPeriod(float InValue);` — `UE_DEPRECATED(5.8, "Font face glyph fixed scheduled cleanup is deprecated. Glyphs are cleaned up on-demand")`
- L85 _public prototype_ `float GetFontFaceGlyphCleanupPeriod() const;` — `UE_DEPRECATED(5.8, "Font face glyph fixed scheduled cleanup is deprecated. Glyphs are cleaned up on-demand")`
- L88 _public prototype_ `void SetFontFaceGlyphCleanupDelay(float InDelay);` — Sets the amount of time, in seconds, to wait before a cleanup happens after a mesh becomes unused
- L91 _public function_ `float GetFontFaceGlyphCleanupDelay() const` — The amount of time, in seconds, to wait before a cleanup happens after a mesh becomes unused
- L97 _public prototype_ `void OpenEditorSettingsWindow() const;`
- L98 _public prototype_ `TConstArrayView<FString> GetFavoriteFonts() const;`
- L99 _public prototype_ `bool GetShowOnlyMonospaced() const;`
- L100 _public prototype_ `bool GetShowOnlyBold() const;`
- L101 _public prototype_ `bool GetShowOnlyItalic() const;`
- L103 _public prototype_ `void AddFavoriteFont(const FString& InFontName);`
- L104 _public prototype_ `void RemoveFavoriteFont(const FString& InFontName);`
- L105 _public prototype_ `void SetShowOnlyMonospaced(bool InShowOnlyMonospaced);`
- L106 _public prototype_ `void SetShowOnlyBold(bool InShowOnlyBold);`
- L107 _public prototype_ `void SetShowOnlyItalic(bool InShowOnlyItalic);`
- L109 _public prototype_ `bool GetDebugMode() const;`
- L113 _public prototype_ `bool ShouldForceDisableTextCollision() const;` — Returns whether Text3D collision should be forced disabled
- L115 _public function_ `bool GetUseExistingCharactersAsTemplates() const`
- L121 _protected prototype_ `void AddMaterial(FText3DMaterialKey&& InKey, TSoftObjectPtr<UMaterial>&& InMaterial);`
- L124 _protected prototype_ `virtual void PostInitProperties() override;`
- L126 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InChangeEvent) override;`
- L131 _protected prototype_ `void Save();`
- L136 _protected member_ `TSoftObjectPtr<UMaterial> DefaultMaterial;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Default custom material used on Text
- L140 _protected member_ `TSoftObjectPtr<UText3DStyleSet> DefaultStyleSet;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Default style rules to apply on a new Text3D instance
- L144 _protected member_ `TSoftObjectPtr<UFont> FallbackFont;` — `UPROPERTY(Config, EditAnywhere, DisplayName="Default Font", Category="Text3D")` — Default font used on new instance or when the selected font is unavailable
- L148 _protected member_ `TSoftObjectPtr<UFontFace> FallbackFontFace;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Font face used as fallback when no font faces are found
- L152 _protected member_ `FString FontDirectory;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Default project directory where system fonts will be imported and stored as UFont
- L156 _protected member_ `bool bScheduleFontFaceGlyphCleanup_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "Font face glyph fixed scheduled cleanup is deprecated. Glyphs are cleaned up on-demand")` — `UPROPERTY(meta=(DeprecatedProperty))`
- L160 _protected member_ `float FontFaceGlyphCleanupPeriod_DEPRECATED = 300.f;` — `UE_DEPRECATED(5.8, "Font face glyph fixed scheduled cleanup is deprecated. Glyphs are cleaned up on-demand. Use FontFaceGlyphCleanupDelay instead")` — `UPROPERTY(meta=(DeprecatedProperty))`
- L164 _protected member_ `float FontFaceGlyphCleanupDelay = 5.f;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Once a glyph mesh becomes unused, how long to wait before a cleanup happens. <= 0 means immediate.
- L171 _protected member_ `bool bForceDisableTextCollision = false;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Option to disable Text3D collisions globally, as Text3D with collisions can have a significant hit on perf. NOTE: Enabling this and saving levels with text3D will leave them in the 'No Collision' state.
- L174 _protected member_ `std::atomic<bool> ForceDisableTextCollision;` — Mirror atomic version of bForceDisableTextCollision
- L181 _protected member_ `bool bUseExistingCharactersAsTemplates = true;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D Renderer")` — If enabled, when generating components for characters, attempt to use existing character components as templates. New characters components will duplicate from these existing character components, rather than constructing default ones.
- L186 _protected member_ `TArray<FString> FavoriteFonts;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Favorites fonts pinned in the font viewer dropdown
- L190 _protected member_ `bool bShowOnlyMonospaced = false;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Only show monospaced fonts in font viewer
- L194 _protected member_ `bool bShowOnlyBold = false;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Only show fonts with bold support in font viewer
- L198 _protected member_ `bool bShowOnlyItalic = false;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Only show fonts with italic support in font viewer
- L202 _protected member_ `TArray<FString> SystemFontNames;` — `UPROPERTY(VisibleAnywhere, Transient, AdvancedDisplay, Category="Text3D")` — System font names retrieved from the current platform
- L206 _protected member_ `bool bDebugMode = false;` — `UPROPERTY(Config, EditAnywhere, Category="Text3D")` — Debug Text3D components tree hierarchy
- L211 _protected member_ `TMap<FText3DMaterialKey, TSoftObjectPtr<UMaterial>> BaseMaterials;` — `UPROPERTY(Transient)` — Base parent material

#### struct `UText3DProjectSettings::FMaterialParameters`  
`struct FMaterialParameters`  
_L33-63_
- L35 _public member_ `static const FLazyName Mode;`
- L38 _public member_ `static const FLazyName SolidColor;` — Solid
- L39 _public member_ `static const FLazyName Opacity;`
- L42 _public member_ `static const FLazyName GradientOffset;` — Gradient
- L43 _public member_ `static const FLazyName GradientColorA;`
- L44 _public member_ `static const FLazyName GradientColorB;`
- L45 _public member_ `static const FLazyName GradientRotation;`
- L46 _public member_ `static const FLazyName GradientSmoothness;`
- L49 _public member_ `static const FLazyName MainTexture;` — Texture
- L50 _public member_ `static const FLazyName TexturedUTiling;`
- L51 _public member_ `static const FLazyName TexturedVTiling;`
- L54 _public member_ `static const FLazyName BoundsOrigin;` — Bounds
- L55 _public member_ `static const FLazyName BoundsSize;`
- L56 _public member_ `static const FLazyName TextPosition;`
- L59 _public member_ `static const FLazyName MaskEnabled;` — Mask
- L60 _public member_ `static const FLazyName MaskRotation;`
- L61 _public member_ `static const FLazyName MaskOffset;`
- L62 _public member_ `static const FLazyName MaskSmoothness;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Styles/Text3DStyleBase.h` (Public)


#### class `UText3DStyleBase`  
`class UText3DStyleBase : public UObject`  
_L17-146_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, ClassGroup=Text3D, DisplayName="FormatStyle", AutoExpandCategories=(Style))`
- inherits: `UObject`
- desc: Text3D rich text format styles
- L22 _public prototype_ `UText3DStyleBase();`
- L25 _public prototype_ `void SetStyleName(FName InName);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L28 _public function_ `FName GetStyleName() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L34 _public prototype_ `void SetOverrideFont(bool bInOverride);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L37 _public function_ `bool GetOverrideFont() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L43 _public prototype_ `void SetFont(UFont* InFont);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L46 _public function_ `UFont* GetFont() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L52 _public prototype_ `void SetFontTypeface(FName InTypeface);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L55 _public function_ `FName GetFontTypeface() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L61 _public prototype_ `void SetOverrideFontSize(bool bInOverride);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L64 _public function_ `bool GetOverrideFontSize() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L70 _public prototype_ `void SetFontSize(float InSize);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L73 _public function_ `float GetFontSize() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L79 _public prototype_ `void SetOverrideFrontColor(bool bInOverride);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L82 _public function_ `bool GetOverrideFrontColor() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L88 _public prototype_ `void SetFrontColor(FLinearColor InColor);` — `UFUNCTION(BlueprintCallable, Category = "Text3D|Style")`
- L91 _public function_ `FLinearColor GetFrontColor() const` — `UFUNCTION(BlueprintPure, Category = "Text3D|Style")`
- L97 _public prototype_ `void ConfigureStyle(FTextBlockStyle& OutStyle) const;` — Sets the proper values on the text block style
- L102 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L106 _protected prototype_ `void OnStylePropertiesChanged();`
- L107 _protected prototype_ `void OnFontChanged();`
- L110 _protected prototype_ `TArray<FName> GetTypefaceNames() const;` — `UFUNCTION()`
- L111 _protected prototype_ `TArrayView<const FTypefaceEntry> GetAvailableTypefaces() const;`
- L115 _protected member_ `FName StyleName = NAME_None;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Style", meta=(AllowPrivateAccess="true"))` — Style name used in text
- L119 _protected member_ `bool bOverrideFont = true;` — `UPROPERTY(EditAnywhere, Setter="SetOverrideFont", Getter="GetOverrideFont", Category="Style", meta=(AllowPrivateAccess="true", InlineEditConditionToggle))` — Behavior for the font rule of this style
- L123 _protected member_ `TObjectPtr<UFont> Font;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Style", meta=(EditCondition="bOverrideFont", AdvancedFontPicker, AllowPrivateAccess="true"))` — Text font defines the style of rendered characters
- L127 _protected member_ `FName FontTypeface;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Style", meta=(EditCondition="bOverrideFont", GetOptions="GetTypefaceNames", AllowPrivateAccess="true"))` — Text font face, subset within font like bold, italic, regular
- L131 _protected member_ `bool bOverrideFontSize = true;` — `UPROPERTY(EditAnywhere, Setter="SetOverrideFontSize", Getter="GetOverrideFontSize", Category="Style", meta=(AllowPrivateAccess="true", InlineEditConditionToggle))` — Behavior for the size rule of this style
- L135 _protected member_ `float FontSize = 48.f;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Style", meta=(ClampMin="0.1", EditCondition="bOverrideFontSize", AllowPrivateAccess="true"))` — Text font size to render and scale each character
- L139 _protected member_ `bool bOverrideFrontColor = true;` — `UPROPERTY(EditAnywhere, Setter="SetOverrideFrontColor", Getter="GetOverrideFrontColor", Category="Style", meta=(AllowPrivateAccess="true", InlineEditConditionToggle))` — Behavior for the front color rule of this style
- L143 _protected member_ `FLinearColor FrontColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Style", meta=(EditCondition="bOverrideFrontColor", AllowPrivateAccess="true"))` — Text front color

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Styles/Text3DStyleSet.h` (Public)


#### class `UText3DStyleSet`  
`class UText3DStyleSet : public UObject`  
_L12-44_
- reflection: `UCLASS(MinimalAPI, DisplayName="Text3D Style Set", AutoExpandCategories=(Style))`
- inherits: `UObject`
- desc: Text3D Style Set used to store multiple reusable styles
- L19 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStyleSetUpdated, UText3DStyleSet* ) static FOnStyleSetUpdated::RegistrationType& OnStyleSetUpdated()`
- L26 _public function_ `TConstArrayView<TObjectPtr<UText3DStyleBase>> GetStyles() const`
- L32 _protected member_ `static FOnStyleSetUpdated OnStyleSetUpdatedDelegate;`
- L36 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L40 _protected prototype_ `void OnStyleSetPropertiesChanged();`
- L43 _protected member_ `TArray<TObjectPtr<UText3DStyleBase>> Styles;` — `UPROPERTY(EditAnywhere, Instanced, Category="Style", NoClear, meta=(AllowPrivateAccess="true"))`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStyleSetUpdated, UText3DStyleSet* ) static FOnStyleSetUpdated::RegistrationType& OnStyleSetUpdated() { return OnStyleSetUpdatedDelegate; } TConstArrayView<TObjectPtr<UText3DStyleBase>> GetStyles() const { return Styles; } protected: static FOnStyleSetUpdated OnStyleSetUpdatedDelegate;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Text3DActor.h` (Public)


#### class `AText3DActor`  
`class AText3DActor : public AActor`  
_L11-33_
- reflection: `UCLASS(ClassGroup = (Text3D), Meta = (DisplayName = "Text 3D", ComponentWrapperClass))`
- inherits: `AActor`
- L16 _public prototype_ `AText3DActor();`
- L19 _public function_ `UText3DComponent* GetText3DComponent() const` — Returns Text3D subobject
- L26 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L32 _private member_ `TObjectPtr<UText3DComponent> Text3DComponent;` — `UPROPERTY(Category = Text, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Text3DComponent.h` (Public)


#### class `UText3DComponent`  
`class UText3DComponent : public USceneComponent`  
_L35-701_
- reflection: `UCLASS(MinimalAPI , ClassGroup = (Text3D) , PrioritizeCategories="Text Character Layout Geometry Material Rendering Transform" , HideCategories=(Replication,Collision,HLOD,Physics,Networking,Input,Actor,Cooking,LevelInstance,Streaming,DataLayers,WorldPartition) , meta = (BlueprintSpawnableComponent))`
- inherits: `USceneComponent`
- L43 _public prototype_ `UText3DComponent();`
- L48 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTextGenerated);` — Delegate called after text is rebuilt
- L53 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FTextGeneratedNative);` — Delegate called after text is rebuilt
- L54 _public function_ `FTextGeneratedNative::RegistrationType& OnTextGenerated()`
- L59 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FTextUpdated, UText3DComponent*, EText3DRendererFlags);`
- L60 _public function_ `FTextUpdated::RegistrationType& OnTextPostUpdate()`
- L65 _public function_ `FTextUpdated::RegistrationType& OnTextPreUpdate()`
- L72 _public function_ `const FText& GetText() const` — `UFUNCTION(BlueprintPure, BlueprintGetter, Category = "Text3D")` — Get the text value
- L79 _public prototype_ `void SetText(const FText& Value);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Text3D")` — Set the text value and signal the primitives to be rebuilt
- L86 _public prototype_ `const FText& GetFormattedText() const;` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Returns the Text property, after being formatted by the FormatText virtual function. If FormatText is not overriden, the return FText will be the same as the Text property.
- L89 _public prototype_ `void SetEnforceUpperCase(bool bInEnforceUpperCase);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Text3D")`
- L92 _public function_ `bool GetEnforceUpperCase() const` — `UFUNCTION(BlueprintPure, BlueprintGetter, Category = "Text3D")`
- L99 _public function_ `UFont* GetFont() const` — `UFUNCTION(BlueprintPure, BlueprintGetter, Category = "Text3D")` — Get the text font
- L106 _public prototype_ `void SetFont(UFont* InFont);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Text3D")` — Set the text font and signal the primitives to be rebuilt
- L110 _public prototype_ `void SetFontSize(float InSize);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the text font size
- L113 _public prototype_ `float GetFontSize() const;` — `UFUNCTION(BlueprintPure, Category = "Text3D")`
- L117 _public prototype_ `void SetHasOutline(const bool bValue);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set whether an outline is applied.
- L121 _public prototype_ `void SetOutlineExpand(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the outline width.
- L125 _public prototype_ `void SetExtrude(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the text extrusion size and signal the primitives to be rebuilt
- L129 _public prototype_ `void SetBevel(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the 3d bevel value
- L133 _public prototype_ `void SetBevelType(const EText3DBevelType Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the 3d bevel type
- L137 _public prototype_ `void SetBevelSegments(const int32 Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the amount of segments that will be used to tessellate the Bevel
- L140 _public prototype_ `UMaterialInterface* GetFrontMaterial() const;` — Get the text front material
- L144 _public prototype_ `void SetFrontMaterial(UMaterialInterface* Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the text front material
- L147 _public prototype_ `UMaterialInterface* GetBevelMaterial() const;` — Get the text bevel material
- L151 _public prototype_ `void SetBevelMaterial(UMaterialInterface* Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the text bevel material
- L154 _public prototype_ `UMaterialInterface* GetExtrudeMaterial() const;` — Get the text extrude material
- L158 _public prototype_ `void SetExtrudeMaterial(UMaterialInterface* Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the text extrude material
- L161 _public prototype_ `UMaterialInterface* GetBackMaterial() const;` — Get the text back material
- L165 _public prototype_ `void SetBackMaterial(UMaterialInterface* Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the text back material
- L168 _public prototype_ `float GetKerning() const;` — Get the kerning value and signal the primitives to be rebuilt
- L172 _public prototype_ `void SetKerning(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the kerning value and signal the primitives to be rebuilt
- L175 _public prototype_ `float GetLineSpacing() const;` — Get the line spacing value and signal the primitives to be rebuilt
- L179 _public prototype_ `void SetLineSpacing(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the line spacing value and signal the primitives to be rebuilt
- L182 _public prototype_ `float GetWordSpacing() const;` — Get the word spacing value and signal the primitives to be rebuilt
- L186 _public prototype_ `void SetWordSpacing(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the word spacing value and signal the primitives to be rebuilt
- L189 _public prototype_ `EText3DHorizontalTextAlignment GetHorizontalAlignment() const;` — Get the horizontal alignment value and signal the primitives to be rebuilt
- L193 _public prototype_ `void SetHorizontalAlignment(const EText3DHorizontalTextAlignment value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the horizontal alignment value and signal the primitives to be rebuilt
- L196 _public prototype_ `EText3DVerticalTextAlignment GetVerticalAlignment() const;` — Get the vertical alignment and signal the primitives to be rebuilt
- L200 _public prototype_ `void SetVerticalAlignment(const EText3DVerticalTextAlignment value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the vertical alignment and signal the primitives to be rebuilt
- L203 _public prototype_ `bool HasMaxWidth() const;` — Whether a maximum width is specified
- L207 _public prototype_ `void SetHasMaxWidth(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Enable / Disable a Maximum Width
- L210 _public prototype_ `float GetMaxWidth() const;` — Get the Maximum Width - If width is larger, mesh will scale down to fit MaxWidth value
- L214 _public prototype_ `void SetMaxWidth(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the Maximum Width - If width is larger, mesh will scale down to fit MaxWidth value
- L217 _public prototype_ `EText3DMaxWidthHandling GetMaxWidthHandling() const;` — Get the Maximum Width Handling - Whether to wrap before scaling when the text size reaches the max width
- L221 _public prototype_ `void SetMaxWidthHandling(const EText3DMaxWidthHandling Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the Maximum Width Handling - Whether to wrap before scaling when the text size reaches the max width
- L224 _public prototype_ `bool HasMaxHeight() const;` — Whether a maximum height is specified
- L228 _public prototype_ `void SetHasMaxHeight(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Enable / Disable a Maximum Height
- L231 _public prototype_ `float GetMaxHeight() const;` — Get the Maximum Height - If height is larger, mesh will scale down to fit MaxHeight value
- L235 _public prototype_ `void SetMaxHeight(const float Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the Maximum Height - If height is larger, mesh will scale down to fit MaxHeight value
- L238 _public prototype_ `bool ScalesProportionally() const;` — Get if the mesh should scale proportionally when Max Width/Height is set
- L242 _public prototype_ `void SetScaleProportionally(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set if the mesh should scale proportionally when Max Width/Height is set
- L245 _public prototype_ `bool CastsShadow() const;` — Get the value of CastShadow.
- L249 _public prototype_ `void SetCastShadow(bool NewCastShadow);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Set the value of CastShadow.
- L253 _public prototype_ `void GetBounds(FVector& Origin, FVector& BoxExtent) const;` — `UFUNCTION(BlueprintCallable, Category = "Text3D")` — Get whole text rendered bounds
- L256 _public prototype_ `FBox GetBounds() const;` — Get whole text rendered bounds
- L260 _public function_ `FName GetTypeface() const` — `UFUNCTION(BlueprintPure, BlueprintGetter, Category = "Text3D")` — Get the typeface
- L267 _public prototype_ `void SetTypeface(const FName InTypeface);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Text3D")` — Set the typeface
- L269 _public prototype_ `void RefreshTypeface();`
- L272 _public prototype_ `void SetTextRendererClass(const TSubclassOf<UText3DRendererBase>& InClass);` — `UFUNCTION(BlueprintCallable, Category = "Text3D")`
- L275 _public function_ `TSubclassOf<UText3DRendererBase> GetTextRendererClass() const` — `UFUNCTION(BlueprintPure, Category = "Text3D")`
- L280 _public function_ `const FText3DStatistics& GetStatistics() const`
- L285 _public prototype_ `void RequestUpdate(EText3DRendererFlags InFlags, bool bInImmediateUpdate=false);`
- L287 _public prototype_ `int32 GetTypeFaceIndex() const;`
- L289 _public prototype_ `const FTypefaceEntry* GetTypeFaceEntry() const;`
- L291 _public prototype_ `UText3DRendererBase* GetTextRenderer() const;`
- L294 _public prototype_ `UText3DRendererBase* GetTextRenderer(TSubclassOf<UText3DRendererBase> InRendererClass) const;` — `UFUNCTION(BlueprintCallable, Category="Text3D", meta=(DeterminesOutputType="InRendererClass"))`
- L297 _public prototype_ `UText3DTokenExtensionBase* GetTokenExtension(TSubclassOf<UText3DTokenExtensionBase> InExtensionClass);` — `UFUNCTION(BlueprintCallable, Category="Text3D", meta=(DeterminesOutputType="InExtensionClass"))`
- L299 _public function_ `UText3DTokenExtensionBase* GetTokenExtension() const`
- L305 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DTokenExtensionBase>::Value)> T* GetCastedTokenExtension() const`
- L311 _public prototype_ `UText3DStyleExtensionBase* GetStyleExtension(TSubclassOf<UText3DStyleExtensionBase> InExtensionClass);` — `UFUNCTION(BlueprintCallable, Category="Text3D", meta=(DeterminesOutputType="InExtensionClass"))`
- L313 _public function_ `UText3DStyleExtensionBase* GetStyleExtension() const`
- L319 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DStyleExtensionBase>::Value)> T* GetCastedStyleExtension() const`
- L325 _public prototype_ `UText3DLayoutExtensionBase* GetLayoutExtension(TSubclassOf<UText3DLayoutExtensionBase> InExtensionClass);` — `UFUNCTION(BlueprintCallable, Category="Text3D", meta=(DeterminesOutputType="InExtensionClass"))`
- L327 _public function_ `UText3DLayoutExtensionBase* GetLayoutExtension() const`
- L333 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DLayoutExtensionBase>::Value)> T* GetCastedLayoutExtension() const`
- L339 _public prototype_ `UText3DMaterialExtensionBase* GetMaterialExtension(TSubclassOf<UText3DMaterialExtensionBase> InExtensionClass);` — `UFUNCTION(BlueprintCallable, Category="Text3D", meta=(DeterminesOutputType="InExtensionClass"))`
- L341 _public function_ `UText3DMaterialExtensionBase* GetMaterialExtension() const`
- L347 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DMaterialExtensionBase>::Value)> T* GetCastedMaterialExtension() const`
- L353 _public prototype_ `UText3DGeometryExtensionBase* GetGeometryExtension(TSubclassOf<UText3DGeometryExtensionBase> InExtensionClass);` — `UFUNCTION(BlueprintCallable, Category="Text3D", meta=(DeterminesOutputType="InExtensionClass"))`
- L355 _public function_ `UText3DGeometryExtensionBase* GetGeometryExtension() const`
- L361 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DGeometryExtensionBase>::Value)> T* GetCastedGeometryExtension() const`
- L367 _public prototype_ `UText3DRenderingExtensionBase* GetRenderingExtension(TSubclassOf<UText3DRenderingExtensionBase> InExtensionClass);` — `UFUNCTION(BlueprintCallable, Category="Text3D", meta=(DeterminesOutputType="InExtensionClass"))`
- L369 _public function_ `UText3DRenderingExtensionBase* GetRenderingExtension() const`
- L375 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DRenderingExtensionBase>::Value)> T* GetCastedRenderingExtension() const`
- L381 _public prototype_ `TArray<UText3DLayoutEffectBase*> GetLayoutEffects(TSubclassOf<UText3DLayoutEffectBase> InEffectClass);` — `UFUNCTION(BlueprintCallable, Category="Text3D", meta=(DeterminesOutputType="InEffectClass"))`
- L383 _public function_ `TConstArrayView<UText3DLayoutEffectBase*> GetLayoutEffects() const`
- L388 _public function_ `UText3DCharacterExtensionBase* GetCharacterExtension() const`
- L394 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DCharacterExtensionBase>::Value)> T* GetCastedCharacterExtension() const`
- L399 _public prototype_ `uint16 GetCharacterCount() const;`
- L401 _public prototype_ `UText3DCharacterBase* GetCharacter(uint16 InCharacterIndex) const;`
- L404 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DCharacterBase>::Value)> T* GetCastedCharacter(uint16 InCharacterIndex) const`
- L409 _public prototype_ `void ForEachCharacter(const TFunctionRef<void(UText3DCharacterBase*, uint16, uint16)>& InFunctor) const;`
- L412 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UText3DCharacterBase>::Value)> void ForEachCastedCharacter(const TFunctionRef<void(T*, uint16, uint16)>& InFunctor) const`
- L421 _public prototype_ `bool GatherExtensions(TAdderReserverRef<UText3DExtensionBase*> OutExtensions) const;` — Retrieves all the extensions for this component (not sorted)
- L424 _public prototype_ `bool BeginBuild(TNotNull<EText3DRendererFlags*> InOutFlags);` — Prepares the component for a build
- L427 _public prototype_ `void FinishBuild(EText3DRendererFlags InFlags);` — Called when the text has finished building
- L430 _public prototype_ `void CancelBuild();` — Called when the build is cancelled
- L438 _public function_ `bool GetUseBlockingBuild() const` — `UFUNCTION(BlueprintPure, BlueprintGetter, Category = "Text3D")` — Determines whether text3d is using blocking builds. If true, the builds are blocking (non-incrementally). Otherwise builds are done incrementally. When true, this does not mean that the build will be executed immediately, just that when it does execute, it will be performed non-incrementally (i.e. finish in that same frame).
- L449 _public prototype_ `void SetUseBlockingBuild(bool bInUseBlockingBuild);` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Text3D")` — Set whether to use blocking builds. If true, the builds are blocking (non-incrementally). Otherwise builds are done incrementally. When true, this does not mean that the build will be executed immediately, just that when it does execute, it will be performed non-incrementally (i.e. finish in that same frame).
- L454 _protected prototype_ `virtual void OnVisibilityChanged() override;` — Intercept and propagate a change on this component to all children.
- L456 _protected prototype_ `virtual void OnHiddenInGameChanged() override;` — Intercept and propagate a change on this component to all children.
- L460 _protected prototype_ `virtual void OnComponentCreated() override;`
- L461 _protected prototype_ `virtual void OnComponentDestroyed(bool bInDestroyingHierarchy) override;`
- L462 _protected prototype_ `virtual void OnRegister() override;`
- L463 _protected prototype_ `virtual void OnUnregister() override;`
- L464 _protected prototype_ `virtual void PostApplyToComponent() override;`
- L465 _protected prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L469 _protected prototype_ `virtual void Serialize(FArchive& InArchive) override;`
- L470 _protected prototype_ `virtual void PostLoad() override;`
- L471 _protected prototype_ `virtual void PostEditImport() override;`
- L472 _protected prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L474 _protected prototype_ `virtual void PostCDOCompiled(const FPostCDOCompiledContext& InContext) override;`
- L475 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L476 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L483 _protected prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UFont*, FOnResolveFontByName, const FString& InFontName) static FOnResolveFontByName OnResolveFontByNameDelegate;`
- L487 _protected prototype_ `void SetFontByName(const FString& InFontName);` — Legacy : used to resolve font by their names
- L491 _protected prototype_ `void ForceUpdateText();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Refresh text to force update render state
- L495 _protected prototype_ `void OpenProjectSettings();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Open Text project settings editor window
- L500 _protected prototype_ `TArray<FName> GetTypefaceNames() const;` — `UFUNCTION()` — Get the type faces supported for the current font
- L507 _protected prototype_ `virtual void FormatText(FText& InOutText) const;` — Will be called when text geometry is generated. Override it to customize text formatting in the final geometry, without affecting the Text property. Use GetFormattedText() to retrieve a FText with the result of this formatting.
- L510 _protected prototype_ `void OnTextRendererClassChanged();` — Called when TextRendererClass is changed
- L513 _protected prototype_ `void OnTextChanged();` — Called when Text is changed
- L516 _protected prototype_ `void OnFontPropertiesChanged();` — Called when font options are changed
- L520 _protected member_ `TSubclassOf<UText3DRendererBase> TextRendererClass;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Text", NoClear, meta=(ShowDisplayNames, AllowPrivateAccess="true"))` — The renderer class to use to create the text geometry
- L524 _protected member_ `FText Text;` — `UPROPERTY(EditAnywhere, Getter, Setter, BlueprintSetter="SetText", BlueprintGetter="GetText", Category = "Text", meta = (MultiLine = true, AllowPrivateAccess = "true"))` — The text to generate a 3d mesh
- L528 _protected member_ `TObjectPtr<UFont> Font;` — `UPROPERTY(EditAnywhere, Getter, Setter, BlueprintSetter="SetFont", BlueprintGetter="GetFont", DisplayName = "Default Font", Category = "Text", meta = (AdvancedFontPicker, AllowPrivateAccess = "true"))` — Text font defines the style of rendered characters
- L532 _protected member_ `FName Typeface;` — `UPROPERTY(EditAnywhere, Getter, Setter, BlueprintSetter="SetTypeface", BlueprintGetter="GetTypeface", DisplayName = "Default Typeface", Category = "Text", meta = (AllowPrivateAccess = "true", GetOptions="GetTypefaceNames"))` — Text font face, subset within font like bold, italic, regular
- L536 _protected member_ `float FontSize = 48.f;` — `UPROPERTY(EditAnywhere, Getter, Setter, DisplayName = "Default FontSize", Category = "Text", meta=(ClampMin = "0.1", AllowPrivateAccess = "true"))` — Text font size defines the size of each rendered character
- L540 _protected member_ `bool bEnforceUpperCase = false;` — `UPROPERTY(EditAnywhere, Getter="GetEnforceUpperCase", Setter="SetEnforceUpperCase", BlueprintSetter="SetEnforceUpperCase", BlueprintGetter="GetEnforceUpperCase", Category = "Text", meta = (AllowPrivateAccess="true"))` — Whether to force upper case for text
- L548 _protected member_ `bool bUseBlockingBuild = false;` — `UPROPERTY(EditAnywhere, Getter="GetUseBlockingBuild", BlueprintGetter="GetUseBlockingBuild", Setter="SetUseBlockingBuild", BlueprintSetter="SetUseBlockingBuild", Category="Text", meta=(AllowPrivateAccess="true"))` — Whether to use blocking builds for text by default. If true, the builds are blocking (non-incrementally). Otherwise builds are done incrementally. When true, this does not mean that the build will be executed immediately, just that when it does execute, it will be performed non-incrementally (i.e. finish in that same frame).
- L551 _protected member_ `TObjectPtr<UText3DTokenExtensionBase> TokenExtension;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Token", meta=(AllowPrivateAccess="true"))`
- L554 _protected member_ `TObjectPtr<UText3DStyleExtensionBase> StyleExtension;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Style", meta=(AllowPrivateAccess="true"))`
- L557 _protected member_ `TObjectPtr<UText3DCharacterExtensionBase> CharacterExtension;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Character", meta=(AllowPrivateAccess="true"))`
- L560 _protected member_ `TObjectPtr<UText3DLayoutExtensionBase> LayoutExtension;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Layout", meta=(AllowPrivateAccess="true"))`
- L563 _protected member_ `TArray<TObjectPtr<UText3DLayoutEffectBase>> LayoutEffects;` — `UPROPERTY(EditAnywhere, Instanced, Category="LayoutEffects", meta=(AllowPrivateAccess="true"))`
- L566 _protected member_ `TObjectPtr<UText3DGeometryExtensionBase> GeometryExtension;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Geometry", meta=(AllowPrivateAccess="true"))`
- L569 _protected member_ `TObjectPtr<UText3DMaterialExtensionBase> MaterialExtension;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Material", meta=(AllowPrivateAccess="true"))`
- L572 _protected member_ `TObjectPtr<UText3DRenderingExtensionBase> RenderingExtension;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Rendering", meta=(AllowPrivateAccess="true"))`
- L576 _private member_ `TObjectPtr<UText3DRendererBase> TextRenderer;` — `UPROPERTY(VisibleAnywhere, Instanced, NoClear, Category="Text", meta=(AllowPrivateAccess="true", NoResetToDefault))`
- L579 _private member_ `FTextGenerated TextGeneratedDelegate;` — `UPROPERTY(BlueprintAssignable, Category=Events, meta=(AllowPrivateAccess="true", DisplayName="On Text Generated"))`
- L582 _private member_ `EText3DRendererFlags PreRegisterUpdateFlags = EText3DRendererFlags::None;` — Accumulated update flags to trigger on OnRegister()
- L584 _private member_ `FTextGeneratedNative TextGeneratedNativeDelegate;`
- L587 _private member_ `FTextUpdated TextPreUpdateDelegate;` — Called before text is updated
- L590 _private member_ `FTextUpdated TextPostUpdateDelegate;` — Called after text is updated
- L593 _private member_ `bool bIsUpdatingText = false;` — Flagged as true when text is being updated
- L596 _private member_ `FText3DStatistics Statistics;` — Text statistics cached since last text generation
- L598 _private prototype_ `bool IsTypefaceAvailable(FName InTypeface) const;`
- L599 _private prototype_ `TArrayView<const FTypefaceEntry> GetAvailableTypefaces() const;`
- L601 _private prototype_ `void UpdateStatistics();`
- L603 _private prototype_ `void OnComponentTransformed(USceneComponent*, EUpdateTransformFlags, ETeleportType);`
- L605 _private prototype_ `bool IsCompiledFromBlueprint() const;`
- L607 _private member_ `bool bZeroScaled = false;`
- L612 _private member_ `TObjectPtr<UMaterialInterface> FrontMaterial_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L616 _private member_ `TObjectPtr<UMaterialInterface> BevelMaterial_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L620 _private member_ `TObjectPtr<UMaterialInterface> ExtrudeMaterial_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L624 _private member_ `TObjectPtr<UMaterialInterface> BackMaterial_DEPRECATED;` — `UE_DEPRECATED(5.6, "Use Material Extension instead")` — `UPROPERTY()`
- L628 _private member_ `float Extrude_DEPRECATED = 5.0f;` — `UE_DEPRECATED(5.6, "Use Geometry Extension instead")` — `UPROPERTY()`
- L632 _private member_ `float Bevel_DEPRECATED = 0.0f;` — `UE_DEPRECATED(5.6, "Use Geometry Extension instead")` — `UPROPERTY()`
- L636 _private member_ `EText3DBevelType BevelType_DEPRECATED = EText3DBevelType::Convex;` — `UE_DEPRECATED(5.6, "Use Geometry Extension instead")` — `UPROPERTY()`
- L640 _private member_ `int32 BevelSegments_DEPRECATED = 8;` — `UE_DEPRECATED(5.6, "Use Geometry Extension instead")` — `UPROPERTY()`
- L644 _private member_ `bool bOutline_DEPRECATED = false;` — `UE_DEPRECATED(5.6, "Use Geometry Extension instead")` — `UPROPERTY()`
- L648 _private member_ `float OutlineExpand_DEPRECATED = 0.5f;` — `UE_DEPRECATED(5.6, "Use Geometry Extension instead")` — `UPROPERTY()`
- L652 _private member_ `EText3DHorizontalTextAlignment HorizontalAlignment_DEPRECATED = EText3DHorizontalTextAlignment::Left;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L656 _private member_ `EText3DVerticalTextAlignment VerticalAlignment_DEPRECATED = EText3DVerticalTextAlignment::FirstLine;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L660 _private member_ `float Kerning_DEPRECATED = 0.0f;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L664 _private member_ `float LineSpacing_DEPRECATED = 0.0f;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L668 _private member_ `float WordSpacing_DEPRECATED = 0.0f;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L672 _private member_ `bool bHasMaxWidth_DEPRECATED = false;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L676 _private member_ `float MaxWidth_DEPRECATED = 500.f;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L680 _private member_ `bool bHasMaxHeight_DEPRECATED = false;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L684 _private member_ `EText3DMaxWidthHandling MaxWidthHandling_DEPRECATED = EText3DMaxWidthHandling::Scale;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L688 _private member_ `float MaxHeight_DEPRECATED = 500.0f;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L692 _private member_ `bool bScaleProportionally_DEPRECATED = true;` — `UE_DEPRECATED(5.6, "Use Layout Extension instead")` — `UPROPERTY()`
- L696 _private member_ `bool bCastShadow_DEPRECATED = true;` — `UE_DEPRECATED(5.6, "Use Rendering Extension instead")` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Text3D` (scope `UE`)
- L48 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTextGenerated);` — Delegate called after text is rebuilt
- L53 _delegate_ `DECLARE_MULTICAST_DELEGATE(FTextGeneratedNative);` — Delegate called after text is rebuilt
- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FTextUpdated, UText3DComponent*, EText3DRendererFlags);`
- L415 _function_ `` (scope `UText3DComponent::ForEachCastedCharacter`)
- L483 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UFont*, FOnResolveFontByName, const FString& InFontName) static FOnResolveFontByName OnResolveFontByNameDelegate;`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Text3DComponentVersion.h` (Public)


#### struct `FText3DComponentVersion`  
`struct FText3DComponentVersion`  
_L8-24_
- desc: Used for versioning, only used internally
- L23 _public member_ `static constexpr FGuid GUID = FGuid(0x9261D8A4, 0xBF424601, 0xA21FC0A3, 0x9D839565);`

#### enum `FText3DComponentVersion::Type`  
`enum Type : int32`  
_L10-21_
- L12 _public enumerator_ `PreVersioning = 0`
- L18 _public enumerator_ `Extensions` — Full refactoring of Text3D, splitting logic into extensions to be reused across multiple renderers Geometry, Layout, Material, Rendering Integrating children class (AvaText3DComponent) features into native Text3D
- L19 _public enumerator_ `VersionPlusOne`
- L20 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Text3DDelegates.h` (Public)


#### struct `UE::Text3D::FText3DBuildContext`  
`struct UE_INTERNAL FText3DBuildContext`  
_L13-19_
- L15 _public prototype_ `explicit FText3DBuildContext(const Renderer::FUpdateParameters& InUpdateParameters);`
- L18 _public member_ `EText3DRendererFlags UpdateFlags = EText3DRendererFlags::None;` — All dirty flags for this update

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEXT3D_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Text3D` (scope `UE`)
- L22 _prototype_ `void BroadcastPreRendererUpdate(const FText3DBuildContext& InBuildContext);` (scope `UE::Text3D`) — Called before the Text3D renderer update
- L24 _prototype_ `void BroadcastPostRendererUpdate(const FText3DBuildContext& InBuildContext);` (scope `UE::Text3D`) — Called after the Text3D renderer update
- L27 _prototype_ `UE_INTERNAL TMulticastDelegateRegistration<void(const FText3DBuildContext&)>& OnText3DPreRendererUpdate();` (scope `UE::Text3D`) — Delegate called before the Text3D renderer update
- L29 _prototype_ `UE_INTERNAL TMulticastDelegateRegistration<void(const FText3DBuildContext&)>& OnText3DPostRendererUpdate();` (scope `UE::Text3D`) — Delegate called after the Text3D renderer update

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Text3DTypes.h` (Public)


#### enum `EText3DRendererFlags`  
`enum class EText3DRendererFlags : uint8`  
_L18-31_
- desc: Enumerate Text3D update flags based on their priority
- L20 _public enumerator_ `None`
- L22 _public enumerator_ `Geometry = 1 << 0` — Update whole geometry for text
- L24 _public enumerator_ `Layout = 1 << 1` — Update layout for characters (transform)
- L26 _public enumerator_ `Material = 1 << 2` — Update materials slots
- L28 _public enumerator_ `Visibility = 1 << 3` — Update visibility/lighting properties
- L30 _public enumerator_ `All = Geometry | Layout | Visibility | Material` — Update everything

#### enum `EText3DMaterialStyle`  
`enum class EText3DMaterialStyle : uint8`  
_L35-42_
- reflection: `UENUM()`
- L37 _public enumerator_ `Invalid UMETA(Hidden)`
- L38 _public enumerator_ `Solid`
- L39 _public enumerator_ `Gradient`
- L40 _public enumerator_ `Texture`
- L41 _public enumerator_ `Custom`

#### enum `EText3DMaterialBlendMode`  
`enum class EText3DMaterialBlendMode : uint8`  
_L45-50_
- reflection: `UENUM()`
- L47 _public enumerator_ `Invalid UMETA(Hidden)`
- L48 _public enumerator_ `Opaque`
- L49 _public enumerator_ `Translucent`

#### enum `EText3DFontStyleFlags`  
`enum class EText3DFontStyleFlags : uint8`  
_L53-59_
- reflection: `UENUM()`
- L55 _public enumerator_ `None = 0`
- L56 _public enumerator_ `Monospace = 1 << 0`
- L57 _public enumerator_ `Bold = 1 << 1`
- L58 _public enumerator_ `Italic = 1 << 2`

#### enum `EText3DBevelType`  
`enum class EText3DBevelType : uint8`  
_L62-71_
- reflection: `UENUM()`
- L64 _public enumerator_ `Linear`
- L65 _public enumerator_ `HalfCircle`
- L66 _public enumerator_ `Convex`
- L67 _public enumerator_ `Concave`
- L68 _public enumerator_ `OneStep`
- L69 _public enumerator_ `TwoSteps`
- L70 _public enumerator_ `Engraved`

#### enum `EText3DOutlineType`  
`enum class EText3DOutlineType : uint8`  
_L74-78_
- reflection: `UENUM()`
- L76 _public enumerator_ `Stroke`
- L77 _public enumerator_ `Fill`

#### enum `EText3DMeshType`  
`enum class EText3DMeshType : uint8`  
_L81-86_
- reflection: `UENUM()`
- L83 _public enumerator_ `Unknown`
- L84 _public enumerator_ `Static`
- L85 _public enumerator_ `Dynamic`

#### enum `EText3DGroupType`  
`enum class EText3DGroupType : uint8`  
_L89-97_
- reflection: `UENUM()`
- L91 _public enumerator_ `Front = 0`
- L92 _public enumerator_ `Bevel = 1`
- L93 _public enumerator_ `Extrude = 2`
- L94 _public enumerator_ `Back = 3`
- L96 _public enumerator_ `TypeCount = 4`

#### enum `EText3DVerticalTextAlignment`  
`enum class EText3DVerticalTextAlignment : uint8`  
_L100-106_
- reflection: `UENUM()`
- L102 _public enumerator_ `FirstLine UMETA(DisplayName = "First Line")`
- L103 _public enumerator_ `Top UMETA(DisplayName = "Top")`
- L104 _public enumerator_ `Center UMETA(DisplayName = "Center")`
- L105 _public enumerator_ `Bottom UMETA(DisplayName = "Bottom")`

#### enum `EText3DHorizontalTextAlignment`  
`enum class EText3DHorizontalTextAlignment : uint8`  
_L109-114_
- reflection: `UENUM()`
- L111 _public enumerator_ `Left UMETA(DisplayName = "Left")`
- L112 _public enumerator_ `Center UMETA(DisplayName = "Center")`
- L113 _public enumerator_ `Right UMETA(DisplayName = "Right")`

#### enum `EText3DMaxWidthHandling`  
`enum class EText3DMaxWidthHandling : uint8`  
_L117-123_
- reflection: `UENUM()`
- L120 _public enumerator_ `Scale UMETA(DisplayName = "Scale")` — Scales the text to meet the max width
- L122 _public enumerator_ `WrapAndScale UMETA(DisplayName = "Wrap and Scale")` — First wraps the text (if possible) and then scales to meet the max width

#### enum `EText3DCharacterEffectOrder`  
`enum class EText3DCharacterEffectOrder : uint8`  
_L126-132_
- reflection: `UENUM()`
- L128 _public enumerator_ `Normal UMETA(DisplayName = "Left To Right")`
- L129 _public enumerator_ `FromCenter UMETA(DisplayName = "From Center")`
- L130 _public enumerator_ `ToCenter UMETA(DisplayName = "To Center")`
- L131 _public enumerator_ `Opposite UMETA(DisplayName = "Right To Left")`

#### struct `FText3DWordStatistics`  
`struct FText3DWordStatistics`  
_L134-141_
- L137 _public member_ `FTextRange ActualRange;` — Actual range taking into account whitespaces
- L140 _public member_ `FTextRange RenderRange;` — Render range not taking into account whitespaces

#### struct `FText3DStatistics`  
`struct FText3DStatistics`  
_L143-147_
- L145 _public member_ `TArray<FText3DWordStatistics> Words;`
- L146 _public member_ `int32 WhiteSpaces;`

#### struct `FText3DFontFamily`  
`struct FText3DFontFamily`  
_L149-166_
- L151 _public function_ `void AddFontFace(const FString& InFontFaceName, const FString& InFontFacePath)`
- L162 _public member_ `FString FontFamilyName;` — Family these font faces belong to
- L165 _public member_ `TMap<FString, FString> FontFacePaths;` — Map of each font face with name -> path

#### struct `FText3DMaterialKey`  
`struct FText3DMaterialKey`  
_L170-201_
- reflection: `USTRUCT()`
- desc: Used to identify a specific material type
- L174 _public prototype_ `FText3DMaterialKey() = default;`
- L175 _public function_ `explicit FText3DMaterialKey(EText3DMaterialBlendMode InBlend, bool bInIsUnlit) : BlendMode(InBlend) , bIsUnlit(bInIsUnlit)`
- L180 _public function_ `bool operator==(const FText3DMaterialKey& Other) const`
- L186 _public function_ `bool operator!=(const FText3DMaterialKey& Other) const`
- L197 _public member_ `EText3DMaterialBlendMode BlendMode = EText3DMaterialBlendMode::Invalid;` — `UPROPERTY()`
- L200 _public member_ `bool bIsUnlit = false;` — `UPROPERTY()`

#### struct `FText3DMaterialGroupKey`  
`struct FText3DMaterialGroupKey`  
_L204-245_
- reflection: `USTRUCT()`
- L208 _public prototype_ `FText3DMaterialGroupKey() = default;`
- L209 _public function_ `explicit FText3DMaterialGroupKey(FText3DMaterialKey InKey, EText3DGroupType InGroup, FName InTag) : Key(InKey) , Group(InGroup) , Tag(InTag)`
- L215 _public function_ `bool operator==(const FText3DMaterialGroupKey& Other) const`
- L222 _public function_ `bool operator!=(const FText3DMaterialGroupKey& Other) const`
- L237 _public member_ `FText3DMaterialKey Key;` — `UPROPERTY()` — Defines what the material specs are
- L240 _public member_ `EText3DGroupType Group = EText3DGroupType::Front;` — Defines to which group this material is applied
- L244 _public member_ `FName Tag = NAME_None;` — `UPROPERTY()` — Defines a tag to differentiate materials by style

#### struct `FGlyphMeshParameters`  
`struct FGlyphMeshParameters`  
_L248-293_
- reflection: `USTRUCT()`
- L253 _public member_ `float Extrude = 5.0f;` — `UPROPERTY()`
- L256 _public member_ `float Bevel = 0.0f;` — `UPROPERTY()`
- L259 _public member_ `EText3DBevelType BevelType = EText3DBevelType::Convex;` — `UPROPERTY()`
- L262 _public member_ `int32 BevelSegments = 8;` — `UPROPERTY()`
- L265 _public member_ `bool bOutline = false;` — `UPROPERTY()`
- L268 _public member_ `float OutlineExpand = 0.5f;` — `UPROPERTY()`
- L271 _public member_ `EText3DOutlineType OutlineType = EText3DOutlineType::Stroke;` — `UPROPERTY()`
- L274 _public member_ `FVector PivotOffset = FVector::ZeroVector;` — `UPROPERTY()`
- L277 _public member_ `EText3DMeshType MeshType = EText3DMeshType::Unknown;` — `UPROPERTY()`

#### struct `FText3DCachedMesh`  
`struct FText3DCachedMesh`  
_L296-319_
- reflection: `USTRUCT()`
- L301 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY()`
- L304 _public member_ `TObjectPtr<UDynamicMesh> DynamicMesh;` — `UPROPERTY()`
- L307 _public member_ `FBox MeshBounds = FBox(ForceInitToZero);` — `UPROPERTY()`
- L311 _public member_ `FVector MeshOffset = FVector::ZeroVector;` — `UPROPERTY()` — Pivot offset
- L315 _public member_ `FVector2D FontFaceGlyphSize = FVector2D::ZeroVector;` — `UPROPERTY()` — Used to scale mesh to achieve different font size
- L318 _public member_ `uint32 RefCount = 0;` — Amount of active usage of this glyph, used for cleanup

#### struct `FText3DMaterialOverride`  
`struct FText3DMaterialOverride`  
_L322-347_
- reflection: `USTRUCT()`
- L327 _public member_ `FName Tag = NAME_None;` — `UPROPERTY()`
- L331 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY()` — Materials where index = EText3DGroupType
- L333 _public function_ `bool operator==(const FText3DMaterialOverride& Other) const`
- L338 _public function_ `bool operator!=(const FText3DMaterialOverride& Other) const`

#### struct `UE::Text3D::Renderer::FUpdateParameters`  
`struct FUpdateParameters`  
_L374-384_
- L377 _public member_ `EText3DRendererFlags UpdateFlags = EText3DRendererFlags::None;` — All dirty flags for this update
- L380 _public member_ `EText3DRendererFlags CurrentFlag = EText3DRendererFlags::None;` — Current flag being updated
- L383 _public member_ `bool bIsLastFlag = false;` — Whether CurrentFlag is the last flag of UpdateFlags

#### struct `UE::Text3D::Geometry::FCachedFontFaceGlyphHandle`  
`struct FCachedFontFaceGlyphHandle`  
_L390-420_
- desc: Acts as a handle for FText3DCachedMesh
- L392 _public prototype_ `FCachedFontFaceGlyphHandle() = default;`
- L393 _public prototype_ `FCachedFontFaceGlyphHandle(const FText3DFontFaceCache& InFontFaceCache, uint32 InGlyphIndex, const FGlyphMeshParameters& InGlyphMeshParameters);`
- L394 _public prototype_ `FCachedFontFaceGlyphHandle(const FCachedFontFaceGlyphHandle& InOther);`
- L395 _public prototype_ `FCachedFontFaceGlyphHandle(FCachedFontFaceGlyphHandle&& InOther);`
- L396 _public prototype_ `~FCachedFontFaceGlyphHandle();`
- L398 _public prototype_ `FCachedFontFaceGlyphHandle& operator=(const FCachedFontFaceGlyphHandle& InOther);`
- L399 _public prototype_ `FCachedFontFaceGlyphHandle& operator=(FCachedFontFaceGlyphHandle&& InOther);`
- L401 _public prototype_ `void Unset();`
- L403 _public prototype_ `const FText3DCachedMesh* Resolve() const;`
- L404 _public prototype_ `FText3DCachedMesh* Resolve();`
- L406 _public function_ `bool IsValid() const`
- L411 _public function_ `uint32 GetGlyphIndex() const`
- L417 _private member_ `uint32 FontFaceHash = 0;`
- L418 _private member_ `uint32 GlyphIndex = 0;`
- L419 _private member_ `uint32 GlyphMeshHash = 0;`

#### struct `UE::Text3D::Material::FMaterialParameters`  
`struct FMaterialParameters`  
_L425-432_
- L428 _public member_ `FName Tag = NAME_None;` — Tag used to identify a material section, none = default
- L431 _public member_ `EText3DGroupType Group = EText3DGroupType::Front;` — Group used to identify an entry in the material section

#### Free symbols / members of external scopes

- L32 _prototype_ `ENUM_CLASS_FLAGS(EText3DRendererFlags);`
- L191 _function_ `friend uint32 GetTypeHash(const FText3DMaterialKey& InMaterialSettings)`
- L227 _function_ `friend uint32 GetTypeHash(const FText3DMaterialGroupKey& InMaterialSettings)`
- L279 _function_ `friend uint32 GetTypeHash(const FGlyphMeshParameters& InElement)`
- L343 _function_ `friend uint32 GetTypeHash(const FText3DMaterialOverride& InElement)`
- L349 _namespace_ `namespace UE`
- L349 _namespace_ `namespace Text3D` (scope `UE`)
- L351 _namespace_ `namespace Priority` (scope `UE::Text3D`)
- L353 _variable_ `static constexpr uint16 Token = 0;` (scope `UE::Text3D::Priority`)
- L354 _variable_ `static constexpr uint16 Geometry = 1;` (scope `UE::Text3D::Priority`)
- L355 _variable_ `static constexpr uint16 Style = 2;` (scope `UE::Text3D::Priority`)
- L356 _variable_ `static constexpr uint16 Layout = 3;` (scope `UE::Text3D::Priority`)
- L357 _variable_ `static constexpr uint16 Effect = 4;` (scope `UE::Text3D::Priority`)
- L358 _variable_ `static constexpr uint16 Material = 5;` (scope `UE::Text3D::Priority`)
- L359 _variable_ `static constexpr uint16 Rendering = 6;` (scope `UE::Text3D::Priority`)
- L362 _namespace_ `namespace Metrics` (scope `UE::Text3D`)
- L365 _variable_ `static constexpr float FontSize = 48.f;` (scope `UE::Text3D::Metrics`) — Default value to match size across different Text3D version
- L367 _variable_ `static constexpr float FontSizeInverse = 1.f / FontSize;` (scope `UE::Text3D::Metrics`) — Scale used to transform freetype face result to get normalized values based on our font size
- L369 _variable_ `static constexpr float Convert26Dot6ToPixel = 1.f / 64.f;` (scope `UE::Text3D::Metrics`) — Freetype conversion ratio to pixel
- L372 _namespace_ `namespace Renderer` (scope `UE::Text3D`)
- L387 _namespace_ `namespace Geometry` (scope `UE::Text3D`)
- L423 _namespace_ `namespace Material` (scope `UE::Text3D`)

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Tokens/Text3DTokenBase.h` (Public)


#### class `UText3DTokenBase`  
`class UText3DTokenBase : public UObject`  
_L10-46_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, ClassGroup=Text3D, DisplayName="Token", AutoExpandCategories=(Token))`
- inherits: `UObject`
- desc: Text3D token to swap variable by its content
- L15 _public prototype_ `void SetTokenName(FName InName);`
- L16 _public function_ `FName GetTokenName() const`
- L21 _public prototype_ `void SetContent(const FText& InContent);`
- L22 _public function_ `const FText& GetContent() const`
- L28 _public prototype_ `virtual void CollectTokens(FFormatNamedArguments& InNamedArguments);` — Collects named tokens and their content for replacement
- L33 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L37 _protected prototype_ `void OnTokenPropertiesChanged();`
- L41 _protected member_ `FName TokenName = NAME_None;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Token", meta=(AllowPrivateAccess="true"))` — Token variable that will be swapped
- L45 _protected member_ `FText Content;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Token", meta=(AllowPrivateAccess="true"))` — Content that replaces token in the text

### `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Utilities/Text3DUtilities.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Text3D` (scope `UE`)
- L17 _namespace_ `namespace Utilities` (scope `UE::Text3D`)
- L20 _prototype_ `IText3DBuildSystemInterface* FindBuildSystem(const UObject* InWorldContextObject);` (scope `UE::Text3D::Utilities`) — Finds the text build system for the given world context object
- L22 _namespace_ `namespace Font` (scope `UE::Text3D::Utilities`)
- L25 _prototype_ `bool GetSanitizeFontName(const UFont* InFont, FString& OutFontName);` (scope `UE::Text3D::Utilities::Font`) — Get proper font name without invalid chars
- L28 _prototype_ `bool GetFontName(const UFont* InFont, FString& OutFontName);` (scope `UE::Text3D::Utilities::Font`) — Get font name based on object/import/legacy name
- L31 _prototype_ `void SanitizeFontName(FString& InOutFontName);` (scope `UE::Text3D::Utilities::Font`) — Replace invalid object name chars and spaces
- L34 _prototype_ `bool GetFontStyle(const UFont* InFont, EText3DFontStyleFlags& OutFontStyleFlags);` (scope `UE::Text3D::Utilities::Font`) — Detect font style (italic, bold, monospaced)
- L37 _prototype_ `bool GetFontStyle(const FText3DFontFamily& InFontFamily, EText3DFontStyleFlags& OutFontStyleFlags);` (scope `UE::Text3D::Utilities::Font`) — Detect font style (italic, bold, monospaced)
- L40 _prototype_ `bool GetFontFaces(const UFont* InFont, TArray<UFontFace*>& OutFontFaces);` (scope `UE::Text3D::Utilities::Font`) — Get font faces that compose the font
- L44 _namespace_ `namespace Conversion` (scope `UE::Text3D::Utilities`)
- L47 _prototype_ `bool PickAssetPath(const FString& InDefaultPath, FString& OutPickedPath);` (scope `UE::Text3D::Utilities::Conversion`) — Pick in which folder the asset object will be saved
- L50 _prototype_ `AStaticMeshActor* ConvertToStaticMesh(const UText3DComponent* InComponent);` (scope `UE::Text3D::Utilities::Conversion`) — Converts the text component in a static mesh object and spawns a static mesh actor
