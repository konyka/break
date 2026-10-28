# Developer / BSPUtils

- module root: `Source/Developer/BSPUtils`
- headers: 2; symbols: 69
- symbol kinds: class=3, enum=2, enumerator=7, function=5, macro=1, member=13, prototype=33, struct=3, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: 

### `Source/Developer/BSPUtils/Public/BSPOps.h` (Public)


#### class `FBSPOps`  
`class FBSPOps`  
_L12-76_
- L32 _public prototype_ `static void csgPrepMovingBrush( ABrush* Actor );`
- L33 _public prototype_ `static void csgCopyBrush( ABrush* Dest, ABrush* Src, uint32 PolyFlags, EObjectFlags ResFlags, bool bNeedsPrep, bool bCopyPosRotScale, bool bAllowEmpty = false );`
- L34 _public prototype_ `static ABrush* csgAddOperation( ABrush* Actor, uint32 PolyFlags, EBrushType BrushType );`
- L35 _public prototype_ `static int32 bspAddVector( UModel* Model, const FVector* V, bool Exact );`
- L36 _public prototype_ `static int32 bspAddPoint( UModel* Model, const FVector* V, bool Exact );`
- L37 _public prototype_ `static void bspBuild( UModel* Model, enum EBspOptimization Opt, int32 Balance, int32 PortalBias, int32 RebuildSimplePolys, int32 iNode );`
- L38 _public prototype_ `static void bspRefresh( UModel* Model, bool NoRemapSurfs );`
- L39 _public prototype_ `static void bspBuildBounds( UModel* Model );`
- L40 _public prototype_ `static void bspValidateBrush( UModel* Brush, bool ForceValidate, bool DoStatusUpdate );`
- L41 _public prototype_ `static void bspUnlinkPolys( UModel* Brush );`
- L42 _public prototype_ `static int32 bspAddNode( UModel* Model, int32 iParent, enum ENodePlace ENodePlace, uint32 NodeFlags, FPoly* EdPoly );`
- L47 _public prototype_ `static void RebuildBrush(UModel* Brush);` — Rebuild some brush internals
- L49 _public prototype_ `static FPoly BuildInfiniteFPoly( UModel* Model, int32 iNode );`
- L52 _public prototype_ `static void HandleVolumeShapeChanged(AVolume& Volume);` — Called when an AVolume shape is changed
- L55 _public member_ `static int32 GErrors;` — Errors encountered in Csg operation.
- L56 _public member_ `static bool GFastRebuild;`
- L62 _protected prototype_ `static void RotateBrushVerts(ABrush* Brush, const FRotator& Rotation, bool bClearComponents);` — Rotates the specified brush's vertices.
- L64 _protected prototype_ `static void SplitPolyList ( UModel *Model, int32 iParent, ENodePlace NodePlace, int32 NumPolys, FPoly **PolyList, EBspOptimization Opt, int32 Balance, int32 PortalBias, int32 RebuildSimplePolys );`

#### enum `FBSPOps::EBspOptimization`  
`enum EBspOptimization`  
_L16-21_
- desc: Quality level for rebuilding Bsp.
- L18 _public enumerator_ `BSP_Lame`
- L19 _public enumerator_ `BSP_Good`
- L20 _public enumerator_ `BSP_Optimal`

#### enum `FBSPOps::ENodePlace`  
`enum ENodePlace`  
_L24-30_
- desc: Possible positions of a child Bsp node relative to its parent (for BspAddToNode)
- L26 _public enumerator_ `NODE_Back = 0` — Node is in back of parent              -> Bsp[iParent].iBack.
- L27 _public enumerator_ `NODE_Front = 1` — Node is in front of parent             -> Bsp[iParent].iFront.
- L28 _public enumerator_ `NODE_Plane = 2` — Node is coplanar with parent           -> Bsp[iParent].iPlane.
- L29 _public enumerator_ `NODE_Root = 3` — Node is the Bsp root and has no parent -> Bsp[0].

#### struct `FBspPointsKey`  
`struct FBspPointsKey`  
_L82-103_
- L84 _public member_ `int32 X;`
- L85 _public member_ `int32 Y;`
- L86 _public member_ `int32 Z;`
- L88 _public function_ `FBspPointsKey(int32 InX, int32 InY, int32 InZ) : X(InX) , Y(InY) , Z(InZ)`

#### struct `FBspIndexedPoint`  
`struct FBspIndexedPoint`  
_L105-114_
- L107 _public function_ `FBspIndexedPoint(const FVector& InPoint, int32 InIndex) : Point(InPoint) , Index(InIndex)`
- L112 _public member_ `FVector Point;`
- L113 _public member_ `int32 Index;`

#### struct `FBspPointsGridItem`  
`struct FBspPointsGridItem`  
_L117-120_
- L119 _public member_ `TArray<FBspIndexedPoint, TInlineAllocator<16>> IndexedPoints;`

#### class `FBspPointsGrid`  
`class FBspPointsGrid`  
_L126-150_
- desc: Represents a sparse granular 3D grid into which points are added for quick (~O(1)) lookup. The 3D space is divided into a grid with a given granularity. Points are considered to have a given radius (threshold) and are added to the grid cube they fall in, and to up to seven neighbours if they overlap.
- L129 _public function_ `FBspPointsGrid(float InGranularity, float InThreshold, int32 InitialSize = 0) : OneOverGranularity(1.0f / InGranularity) , Threshold(InThreshold)`
- L137 _public prototype_ `void Clear(int32 InitialSize = 0);`
- L139 _public prototype_ `int32 FindOrAddPoint(const FVector& Point, int32 Index, float Threshold);`
- L141 _public member_ `static FBspPointsGrid* GBspPoints;`
- L142 _public member_ `static FBspPointsGrid* GBspVectors;`
- L145 _private member_ `float OneOverGranularity;`
- L146 _private member_ `float Threshold;`
- L148 _private typedef_ `typedef TMap<FBspPointsKey, FBspPointsGridItem> FGridMap;`
- L149 _private member_ `FGridMap GridMap;`

#### Free symbols / members of external scopes

- L79 _typedef_ `typedef FBSPOps::ENodePlace ENodePlace;` — @todo: remove when uses of ENodePlane have been replaced with FBSPOps::ENodePlace.
- L94 _function_ `friend FORCEINLINE bool operator == (const FBspPointsKey& A, const FBspPointsKey& B)`
- L99 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FBspPointsKey& Key)`

### `Source/Developer/BSPUtils/Public/BSPUtils.h` (Public)


#### class `FBSPUtils`  
`class FBSPUtils`  
_L16-101_
- L20 _public prototype_ `static void bspRepartition( UWorld* InWorld, int32 iNode );` — Repartition Bsp tree
- L23 _public prototype_ `static int32 bspNodeToFPoly( UModel* Model, int32 iNode, FPoly* EdPoly );` — Convert a Bsp node to an EdPoly.  Returns number of vertices in Bsp node.
- L29 _public prototype_ `static void bspCleanup( UModel* Model );` — Clean up all nodes after a CSG operation.  Resets temporary bit flags and unlinks empty leaves.  Removes zero-vertex nodes which have nonzero-vertex coplanars.
- L36 _public prototype_ `static void bspBuildFPolys( UModel* Model, bool SurfLinks, int32 iNode, TArray<FPoly>* DestArray = NULL );` — Build EdPoly list from a model's Bsp. Not transactional. @param DestArray helps build bsp FPolys in non-main threads. It also allows to perform this action without GUndo interfering. Temporary results will be written to DestArray. Defaults to Model->Polys->Element
- L38 _public prototype_ `static void bspMergeCoplanars( UModel* Model, bool RemapLinks, bool MergeDisparateTextures );`
- L43 _public prototype_ `static int32 bspBrushCSG( ABrush* Actor, UModel* Model, UModel* TempModel, UMaterialInterface* SelectedMaterialInstance, uint32 PolyFlags, EBrushType BrushType, ECsgOper CSGOper, bool bBuildBounds, bool bMergePolys, bool bReplaceNULLMaterialRefs, bool bShowProgressBar=true );` — Performs any CSG operation between the brush and the world.
- L50 _public prototype_ `static void bspOptGeom( UModel* Model );` — Optimize a level's Bsp, eliminating T-joints where possible, and building side links.  This does not always do a 100% perfect job, mainly due to imperfect levels, however it should never fail or return incorrect results.
- L56 _public prototype_ `static void polySetAndClearPolyFlags(UModel *Model, uint32 SetBits, uint32 ClearBits,bool SelectedOnly, bool UpdateBrush);` — Sets and clears all Bsp node flags.  Affects all nodes, even ones that don't really exist.
- L68 _public prototype_ `static bool polyFindBrush(UModel* InModel, int32 iSurf, FPoly &Poly);` — Find the Brush EdPoly corresponding to a given Bsp surface. @param InModel	Model to get poly from @param iSurf		surface index @param Poly returns true if poly not available
- L71 _public prototype_ `static bool polyFindMaster(UModel* InModel, int32 iSurf, FPoly &Poly);` — `UE_DEPRECATED(5.1, "polyFindMaster is deprecated; please use polyFindBrush instead")`
- L79 _public prototype_ `static void polyUpdateBrush(UModel* Model, int32 iSurf, bool bUpdateTexCoords, bool bOnlyRefreshSurfaceMaterials);` — Update the brush EdPoly corresponding to a newly-changed poly to reflect its new properties. Doesn't do any transaction tracking.
- L82 _public prototype_ `static void polyUpdateMaster(UModel* Model, int32 iSurf, bool bUpdateTexCoords, bool bOnlyRefreshSurfaceMaterials);` — `UE_DEPRECATED(5.1, "polyUpdateMaster is deprecated; please use polyUpdateBrush instead")`
- L88 _public prototype_ `static void polyGetLinkedPolys(ABrush* InBrush, FPoly* InPoly, TArray<FPoly>* InPolyList);` — Populates a list with all polys that are linked to the specified poly.  The resulting list includes the original poly.
- L94 _public prototype_ `static void polySplitOverlappingEdges( TArray<FPoly>* InPolyList, TArray<FPoly>* InResult );` — Takes a list of polygons and creates a new list of polys which have no overlapping edges.  It splits edges as necessary to achieve this.
- L100 _public prototype_ `static void polyGetOuterEdgeList(TArray<FPoly>* InPolyList, TArray<FEdge>* InEdgeList);` — Takes a list of polygons and returns a list of the outside edges (edges which are not shared by other polys in the list).

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BSPUTILS_API`
