# Plugins / TetMeshing

- module root: `Plugins/Experimental/TetMeshing/Source/TetMeshing`
- headers: 3; symbols: 70
- symbol kinds: class=3, delegate=1, enum=1, enumerator=1, function=31, member=22, namespace=4, prototype=2, struct=3, typedef=2
- PrivateDependencyModuleNames: MeshConversion, MeshUtilitiesCommon, StaticMeshDescription
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, DynamicMesh, GeometryAlgorithms, GeometryCore, MeshDescription

### `Plugins/Experimental/TetMeshing/Source/TetMeshing/Public/Generate/IsosurfaceStuffing.h` (Public)


#### enum `UE::Geometry::ERootFindingMethod`  
`enum class ERootFindingMethod : uint8`  
_L17-21_
- L19 _public enumerator_ `Bisection`

#### class `UE::Geometry::TIsosurfaceStuffing`  
`template<typename RealType, ERootFindingMethod RootMethod = ERootFindingMethod::Bisection> class TIsosurfaceStuffing : public TTetMeshGenerator<RealType>`  
_L24-720_
- inherits: `TTetMeshGenerator<RealType>`
- L27 _public typedef_ `using TVec3 = UE::Math::TVector<RealType>;`
- L31 _public member_ `UE::Math::TBox<RealType> Bounds;` — Parameters for generation
- L32 _public member_ `RealType CellSize;`
- L35 _public member_ `TFunction<RealType(TVec3)> Implicit;` — Implicit is the implicit function defining the desired output shape, typically a fast winding or signed distance function It should be larger than IsoValue inside the desired shape, and smaller than IsoValue outside
- L36 _public member_ `RealType IsoValue = 0;`
- L38 _public member_ `int32 RootModeSteps = 5;` — Number of steps to take when root finding
- L41 _public function_ `virtual TIsosurfaceStuffing& Generate() override`
- L114 _public function_ `virtual void Reset() override`
- L151 _protected member_ `TMap<int64, FGridPtData> ComputedGridPts;`
- L152 _protected member_ `TMap<int64, FCutData> ComputedCutPts;`
- L155 _protected function_ `inline TVec3 GetUnwarpedGridPos(const FGridPt& Pt) const` — Get grid coordinates s.t. Cell 0,0,0's center is at the minimum corner of Bounds
- L160 _protected function_ `TVec3 ComputeEdgeCutPos(TVec3 APos, RealType AVal, TVec3 BPos, RealType BVal) const`
- L218 _protected function_ `static constexpr int64 GetMajorAxisEdgeTag(int64 Axis)` — Axis should be 0, 1, or 2 for X, Y, or Z
- L223 _protected function_ `static constexpr int64 GetCornerEdgeTag(FIntVector3 Delta)` — Delta should be 0 or 1 for each coordinate
- L230 _protected function_ `static int64 GetEdgeID(FGridPt A, FGridPt B)` — Return a unique ID for the BCC edge connecting A to B (note: assumes A,B are connected in the BCC lattice)
- L269 _protected function_ `static inline int64 GetGridID(const FGridPt& Pt)`
- L273 _protected function_ `static inline int64 GetGridID(FIntVector3 Idx, bool bIsCenter)`
- L277 _protected function_ `static int64 GetGridID(int32 X, int32 Y, int32 Z, bool bIsCenter)`
- L282 _protected function_ `static void GetEdges(FGridPt Pt, int64 EdgeIDsOut[14], FGridPt OtherPtOut[14])`
- L340 _protected function_ `inline int16 ImplicitValueToLabel(RealType Value) const` — TODO: Update this for the multi-label case?
- L346 _protected function_ `inline RealType LabelToImplicitValue(int16 Label) const` — TODO: Note this is incompatible with Lerp-based iso-surface finding
- L351 _protected function_ `FGridPtData GetGridPtData(const FGridPt& Pt, TVec3& PosOut, bool bAllowWarp = true)`
- L462 _protected function_ `static RealType GetAlpha(const TVec3& APos, const TVec3& BPos, const TVec3& Between)`
- L470 _protected function_ `bool GetCutData(int64 EdgeID, const FGridPt& A, const FGridPt& B, const TVec3& APos, const TVec3& BPos, int16 LabelA, int16 LabelB, RealType AlphaThreshold, FCutData& CutOut, RealType& AlphaOut)`
- L499 _protected function_ `int32 GetOrAddCutVertex(const FGridPt& A, const FGridPt& B)`
- L513 _protected function_ `void ProcessTet(FGridPt Pts[4], FGridPtData Data[4])` — TODO: should this take the pre-fetched edge data as well? Stuff output tetrahedra into the given background tetrahedron

#### struct `UE::Geometry::TIsosurfaceStuffing::FGridPt`  
`struct FGridPt`  
_L123-134_
- L125 _public member_ `FIntVector3 Idx;`
- L126 _public member_ `bool bIsCenter;`
- L128 _public function_ `FGridPt(FIntVector3 Idx, bool bIsCenter) : Idx(Idx), bIsCenter(bIsCenter)`
- L130 _public function_ `FGridPt() : Idx(-1, -1, -1), bIsCenter(false)`
- L132 _public function_ `FGridPt(int32 X, int32 Y, int32 Z, bool bIsCenter) : Idx(X, Y, Z), bIsCenter(bIsCenter)`

#### struct `UE::Geometry::TIsosurfaceStuffing::FGridPtData`  
`struct FGridPtData`  
_L136-141_
- L138 _public member_ `int32 VertexIndex = INDEX_NONE;` — Output vertex index; only applicable if Label >= 0
- L139 _public member_ `int16 Label;` — Negative = Outside, 0 = On surfaces, >=1 = inside surface w/ label indicated
- L140 _public member_ `bool bWarpProcessed = false;`

#### struct `UE::Geometry::TIsosurfaceStuffing::FCutData`  
`struct FCutData`  
_L143-149_
- L145 _public member_ `int32 VertexIndex = INDEX_NONE;` — Output vertex index; can be unset
- L146 _public member_ `TVec3 CutPos;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Geometry` (scope `UE`)
- L411 _function_ `` (scope `UE::Geometry::TIsosurfaceStuffing::GetGridPtData`)
- L521 _function_ `` (scope `UE::Geometry::TIsosurfaceStuffing::ProcessTet`)

### `Plugins/Experimental/TetMeshing/Source/TetMeshing/Public/Generate/TetMeshGenerator.h` (Public)


#### class `UE::Geometry::TTetMeshGenerator`  
`template<typename RealType> class TTetMeshGenerator`  
_L18-133_
- desc: Base class for tetrahedral mesh generators (eg like to generate sphere, cylinder, etc) Subclasses must implement ::Generate()
- L21 _public typedef_ `using TVec3 = UE::Math::TVector<RealType>;`
- L24 _public member_ `TArray<TVec3> Vertices;` — Array of vertex positions
- L27 _public member_ `TArray<FIntVector4> Tets;` — Array of tetrahedron corner positions, stored as tuples of indices into Vertices array
- L29 _public member_ `TArray<int32> TetIDs;` — Optional array of tetrahedron IDs.  If non-empty, should be same length as Tets array.
- L30 _public member_ `bool bCreateTetIDs = false;`
- L33 _public member_ `TArray<FIntVector3> Triangles;` — Optional array of triangle corner indices, which should correspond to faces of existing tetrahedra
- L35 _public member_ `TArray<int32> TriangleIDs;` — Optional array of ID tags for triangles. If non-empty, should be same length as Triangles array.
- L36 _public member_ `bool bCreateTriangleIDs = false;`
- L41 _public member_ `bool bReverseOrientation = false;` — If true, reverse orientation of created mesh
- L43 _public function_ `virtual ~TTetMeshGenerator()`
- L51 _public prototype_ `virtual TTetMeshGenerator& Generate() = 0;` — Subclasses implement this to generate mesh
- L55 _public function_ `virtual void Reset()` — clear arrays so that Generate() can be run again
- L68 _public function_ `void SetBufferSizes(int32 NumVertices, int32 NumTetrahedra, bool bIncludeTetIDs, int32 NumTriangles, bool bIncludeTriangleIDs)` — Set the various internal buffers to the correct sizes for the given element counts
- L87 _public function_ `void ExtendBufferSizes(int32 AddVertices, int32 AddTriangles, int32 AddTets)` — Extends the various internal buffers to the correct sizes for the given additional element counts
- L115 _public function_ `inline int32 AppendTet(int32 A, int32 B, int32 C, int32 D, int32 TetID = -1)`
- L124 _public function_ `inline int32 AppendTetOriented(FIntVector4 Tet, bool bFlipOrientation, int32 TetID = -1)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/TetMeshing/Source/TetMeshing/Public/TetMeshingPlugin.h` (Public)


#### class `ITetMeshingPlugin`  
`class ITetMeshingPlugin : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L25 _public function_ `static inline ITetMeshingPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTetMeshing, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTetMeshing, Log, All);`
