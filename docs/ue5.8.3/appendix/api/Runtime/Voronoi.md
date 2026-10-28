# Runtime / Voronoi

- module root: `Source/Runtime/Experimental/Voronoi`
- headers: 3; symbols: 64
- symbol kinds: class=4, function=14, member=13, namespace=1, prototype=31, struct=1
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/Experimental/Voronoi/Private/voro++/src/v_base_wl.inl` (Private)


#### Free symbols / members of external scopes

- L17 _member_ `const unsigned int voro_base::wl[wl_seq_length*wl_hgridcu]={ 7,0x10203f,0x101fc0,0xfe040,0xfe03f,0x101fbf,0xfdfc0,0xfdfbf,0x10fe0bf,0x11020bf,0x11020c0,0x10fe0c0,0x2fe041,0x302041,0x301fc1,0x2fdfc1,0x8105fc0,0x8106040,0x810603f,0x8105fbf,0x701fbe,0x70203e,0x6fe03e,0x6fdfbe,0x30fdf3f,0x3101f3f,0x3101f40,0x30fdf40,0x180f9fc0,0x180fa040,0x180fa03f,0x180f9fbf,0x12fe0c1,0x13020c1,0x91060c0,0x91060bf,0x8306041,0x8305fc1,0x3301f41,0x32fdf41,0x182f9fc1,0x182fa041,0x190fa0c0,0x190fa0bf,0x16fe0be,0x17020be,0x870603e,0x8705fbe,0xb105f3f,0xb105f40,0x3701f3e,0x36fdf3e,0x186f9fbe,0x186fa03e,0x1b0f9f3f,0x1b0f9f40,0x93060c1,0x192fa0c1,0x97060be,0xb305f41,0x1b2f9f41,0x196fa0be,0xb705f3e,0x1b6f9f3e, 11,0x101fc0,0xfe040,0xfdfc0,0x10203f,0x101fbf,0xfe03f,0xfdfbf,0xfdfc1,0x101fc1,0x102041,0xfe041,0x10fe0c0,0x11020c0,0x8106040,0x8105fc0,0x8105fbf,0x810603f,0x11020bf,0x10fe0bf,0x180fa040,0x180f9fc0,0x30fdf40,0x3101f40,0x3101f3f,0x30fdf3f,0x180f9fbf,0x180fa03f,0x6fe03e,0x70203e,0x701fbe,0x6fdfbe,0x8105fc1,0x8106041,0x11020c1,0x10fe0c1,0x180fa041,0x180f9fc1,0x30fdf41,0x3101f41,0x91060c0,0x91060bf,0x190fa0c0,0x190fa0bf,0xb105f40,0xb105f3f,0x8705fbe,0x870603e,0x97020be,0x16fe0be,0x1b0f9f40,0x1b0f9f3f,0x36fdf3e,0xb701f3e,0x1b6f9fbe,0x196fa03e,0x93060c1,0xb305f41,0x192fa0c1,0x1b2f9f41,0x1b2fdfc2,0xb301fc2,0x9302042,0x192fe042, 11,0x101fc0,0xfe040,0xfdfc0,0xfdfbf,0x101fbf,0x10203f,0xfe03f,0xfe041,0x102041,0x101fc1,0xfdfc1,0x8105fc0,0x8106040,0x11020c0,0x10fe0c0,0x10fe0bf,0x11020bf,0x810603f,0x8105fbf,0x31 ...` (scope `voro_base`)

### `Source/Runtime/Experimental/Voronoi/Public/Voronoi/Voronoi.h` (Public)


#### struct `FVoronoiCellInfo`  
`struct FVoronoiCellInfo`  
_L20-26_
- desc: All the info you would typically want about a single cell in the Voronoi diagram, in the format that is easiest to compute
- L22 _public member_ `TArray<FVector> Vertices;`
- L23 _public member_ `TArray<int32> Faces;`
- L24 _public member_ `TArray<int32> Neighbors;`
- L25 _public member_ `TArray<FVector> Normals;`

#### class `FVoronoiComputeHelper`  
`class FVoronoiComputeHelper`  
_L38-52_
- desc: The Voronoi Compute Helper caches information to help compute cells quickly To safely parallelize voronoi diagram construction, create a separate compute helper per-thread
- L40 _private member_ `TPimplPtr<voro::voro_compute<voro::container>> Compute;`
- L43 _public function_ `FVoronoiComputeHelper()`
- L44 _public prototype_ `FVoronoiComputeHelper(const FVoronoiComputeHelper& Other) = delete;`
- L45 _public prototype_ `FVoronoiComputeHelper& operator=(const FVoronoiComputeHelper& Other) = delete;`
- L46 _public prototype_ `FVoronoiComputeHelper(FVoronoiComputeHelper&& Other) = default;`
- L47 _public prototype_ `FVoronoiComputeHelper& operator=(FVoronoiComputeHelper&& Other) = default;`
- L49 _public prototype_ `void Init();`

#### class `FVoronoiDiagram`  
`class FVoronoiDiagram`  
_L54-162_
- L56 _private member_ `int32 NumSites;`
- L57 _private member_ `TPimplPtr<voro::container> Container;`
- L58 _private member_ `FBox Bounds;`
- L61 _public member_ `const static int MinDefaultSitesPerThread;`
- L71 _public prototype_ `FVoronoiDiagram(const TArrayView<const FVector>& Sites, double ExtraBoundingSpace, double SquaredDistSkipPtThreshold = UE_KINDA_SMALL_NUMBER);` — Create a Voronoi diagram with the given sites, in a box bounding containing those sites @param Sites							Voronoi sites for the diagram @param ExtraBoundingSpace			Voronoi diagram will be computed within the bounding box of the sites + this amount of extra space in each dimension @param SquaredDistSkipPtThreshold	A safety threshold to avoid creating invalid cells: sites that are within this distance of an already-added site will not be added (If you know there will be no duplicate sites, can set to zero for faster perf.)
- L81 _public prototype_ `FVoronoiDiagram(const TArrayView<const FVector>& Sites, const FBox &Bounds, double ExtraBoundingSpace, double SquaredDistSkipPtThreshold = UE_KINDA_SMALL_NUMBER);` — Create a Voronoi diagram with the given sites, in a given bounding box @param Sites							Voronoi sites for the diagram @param Bounds						Bounding box within which to compute the Voronoi diagram @param ExtraBoundingSpace			Voronoi diagram will be computed within the input Bounds + this amount of extra space in each dimension @param SquaredDistSkipPtThreshold	A safety threshold to avoid creating invalid cells: sites that are within this distance of an already-added site will not be added. (If you know there will be no duplicate sites, can set to zero for faster perf.)
- L90 _public prototype_ `FVoronoiDiagram(int32 ExpectedNumSites, const FBox& Bounds, double ExtraBoundingSpace);` — Make a container for a Voronoi diagram without any points.  Call AddSites() after to finish creating the diagram. @param ExpectedNumSites		How many sites you expect to add in total @param Bounds				Bounding box within which to compute the Voronoi diagram @param ExtraBoundingSpace	Amount to expand the bounding box before computing the Voronoi diagram
- L95 _public function_ `FVoronoiDiagram() : NumSites(0), Container(nullptr), Bounds(EForceInit::ForceInit)` — Make an empty diagram, to be filled in with a subsequent call to "Initialize()"
- L98 _public prototype_ `FVoronoiDiagram(const FVoronoiDiagram& Other) = delete;`
- L99 _public prototype_ `FVoronoiDiagram& operator=(const FVoronoiDiagram& Other) = delete;`
- L100 _public prototype_ `FVoronoiDiagram(FVoronoiDiagram&& Other) = default;`
- L101 _public prototype_ `FVoronoiDiagram& operator=(FVoronoiDiagram&& Other) = default;`
- L112 _public prototype_ `void Initialize(const TArrayView<const FVector>& Sites, const FBox& Bounds, double ExtraBoundingSpace, double SquaredDistSkipPtThreshold = UE_KINDA_SMALL_NUMBER);` — Create a Voronoi diagram with the given sites, in a given bounding box.  Any previous data is discarded. @param Sites							Voronoi sites for the diagram @param Bounds						Bounding box within which to compute the Voronoi diagram @param ExtraBoundingSpace			Voronoi diagram will be computed within the input Bounds + this amount of extra space in each dimension @param SquaredDistSkipPtThreshold	A safety threshold to avoid creating invalid cells: sites that are within this distance of an already-added site will not be added. (If you know there will be no duplicate sites, can set to zero for faster perf.)
- L114 _public prototype_ `~FVoronoiDiagram();`
- L116 _public prototype_ `static FBox GetBounds(const TArrayView<const FVector>& Sites, double ExtraBoundingSpace = UE_DOUBLE_KINDA_SMALL_NUMBER);`
- L118 _public function_ `int32 Num() const`
- L123 _public prototype_ `void AddSites(const TArrayView<const FVector>& Sites, double SquaredDistSkipPtThreshold = 0.0f);`
- L125 _public prototype_ `void ComputeAllCellsSerial(TArray<FVoronoiCellInfo>& AllCells);`
- L126 _public prototype_ `void ComputeAllCells(TArray<FVoronoiCellInfo>& AllCells, int32 ApproxSitesPerThread = -1);`
- L128 _public prototype_ `void ComputeAllNeighbors(TArray<TArray<int32>>& AllNeighbors, bool bExcludeBounds = true, int32 ApproxSitesPerThread = -1);`
- L130 _public prototype_ `void ComputeCellEdgesSerial(TArray<TTuple<FVector, FVector>>& Edges, TArray<int32>& CellMember);`
- L131 _public prototype_ `void ComputeCellEdges(TArray<TTuple<FVector, FVector>>& Edges, TArray<int32>& CellMember, int32 ApproxSitesPerThread = -1);`
- L141 _public prototype_ `int32 FindCell(const FVector& Pos, FVoronoiComputeHelper& ComputeHelper, FVector& OutFoundSite) const;` — Find the closest Voronoi cell to a given position @param Pos				Position to query for closest point @param ComputeHelper		A valid helper as returned by GetComputeHelper() for this voronoi diagram @param OutFoundSite		The position of the closest Voronoi site, if any @return					The id of the Voronoi cell containing the given position, or -1 if position is outside diagram
- L143 _public function_ `int32 FindCell(const FVector& Pos, FVoronoiComputeHelper& ComputeHelper) const`
- L149 _public prototype_ `FVoronoiComputeHelper GetComputeHelper() const;`
- L151 _public function_ `int32 ApproxSitesPerThreadWithDefault(int32 ApproxSitesPerThreadIn)`
- L161 _private prototype_ `TArray<int32> GetParallelBlockRanges(int32 ApproxSitesPerThread);`

#### class `FVoronoiDiagramField`  
`class FVoronoiDiagramField`  
_L173-276_
- desc: Use a Voronoi diagram to support faster querying of Voronoi-like data from arbitrary sample points: - Distance to closest point - ID of closest point - IDs of closest two points - Distance to closest Voronoi cell boundary (not considering bounding box walls) Note: Queries are only thread safe if each thread has its own FVoronoiComputeHelper
- L175 _private member_ `TArray<FVector> Sites;`
- L176 _private member_ `TArray<TArray<int32>> Neighbors;`
- L177 _private member_ `FVoronoiDiagram Diagram;`
- L180 _public prototype_ `FVoronoiDiagramField() = default;`
- L182 _public function_ `FVoronoiDiagramField(const TArray<FVector>& SitesIn, const FBox& Bounds, double SquaredDistSkipPtThreshold = DBL_EPSILON)`
- L187 _public function_ `void Initialize(const TArray<FVector>& SitesIn, const FBox& Bounds, double SquaredDistSkipPtThreshold = DBL_EPSILON)`
- L194 _public prototype_ `FVoronoiDiagramField(const FVoronoiDiagramField& Other) = delete;`
- L195 _public prototype_ `FVoronoiDiagramField& operator=(const FVoronoiDiagramField& Other) = delete;`
- L196 _public prototype_ `FVoronoiDiagramField(FVoronoiDiagramField&& Other) = default;`
- L197 _public prototype_ `FVoronoiDiagramField& operator=(FVoronoiDiagramField&& Other) = default;`
- L199 _public function_ `inline FVoronoiComputeHelper GetComputeHelper() const`
- L205 _public function_ `double DistanceToCellWall(const FVector& Sample, FVoronoiComputeHelper& ComputeHelper, double InvalidValue = TNumericLimits<double>::Lowest())` — @return Distance to the nearest Voronoi cell boundary (ignoring bounding box walls), or InvalidValue if outside of bounds
- L237 _public function_ `TPair<int32, int32> ClosestTwoIDs(const FVector& Sample, FVoronoiComputeHelper& ComputeHelper)`
- L261 _public function_ `inline double DistanceToClosest(const FVector& Sample, FVoronoiComputeHelper& ComputeHelper, double InvalidValue = TNumericLimits<double>::Lowest())` — @return Distance to the nearest Voronoi site, or InvalidValue if outside of bounds
- L272 _public function_ `inline int32 ClosestID(const FVector& Sample, FVoronoiComputeHelper& ComputeHelper)`

#### Free symbols / members of external scopes

- L16 _prototype_ `bool VoronoiNeighbors(const TArrayView<const FVector> &Sites, TArray<TArray<int>> &Neighbors, bool bExcludeBounds = true, double SquaredDistSkipPtThreshold = UE_KINDA_SMALL_NUMBER);`
- L17 _prototype_ `bool GetVoronoiEdges(const TArrayView<const FVector> &Sites, const FBox& Bounds, TArray<TTuple<FVector, FVector>> &Edges, TArray<int32> &CellMember, double SquaredDistSkipPtThreshold = UE_KINDA_SMALL_NUMBER);`
- L29 _namespace_ `namespace voro`

### `Source/Runtime/Experimental/Voronoi/Public/Voronoi/VoronoiPlugin.h` (Public)


#### class `IVoronoiPlugin`  
`class IVoronoiPlugin : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IVoronoiPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
