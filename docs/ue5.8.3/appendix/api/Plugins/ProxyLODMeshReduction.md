# Plugins / ProxyLODMeshReduction

- module root: `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD`
- headers: 23; symbols: 752
- symbol kinds: class=28, enum=5, enumerator=12, function=210, macro=12, member=186, namespace=19, prototype=234, struct=9, typedef=35, union=2
- PrivateDependencyModuleNames: EditorFramework
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, MaterialUtilities, MeshDescription, MeshUtilities, PropertyEditor, QuadricMeshReduction, RHI, RawMesh, RenderCore, Slate, SlateCore, StaticMeshDescription, TraceLog, UnrealEd

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODBarycentricUtilities.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ProxyLOD`
- L16 _typedef_ `typedef std::array<double, 3> DArray3d;` (scope `ProxyLOD`) — Double precision array of length 3, used primarily for Barycentric coords.
- L20 _function_ `template <typename T> static T InterpolateVertexData(const DArray3d& BarycentricPos, const T(&VertexData)[3])` (scope `ProxyLOD`) — Interpolate Vertex Data to the location given in Barycentric Coords.
- L35 _function_ `static inline void ComputeScaledDistances(const DTriangle2d& Vertices, const DVec2d& Point, DArray3d& OutScaledDistances)` (scope `ProxyLOD`) — Compute Scaled Distances for all three sided of a 2d triangle V1V2, V2V0, V0V1 to the given point in the plane. @param  Vertices  Define a triangle on a 2d plane. @param  Point     A 2d point, form which to measure the scaled distances. @param  OutScaledDistances   Scaled distances to the three edges (V1-V2, V2-V0, V0-V1).
- L54 _function_ `static inline void ConvertScaledDistanceToBarycentric(const DTriangle2d& Vertices, DArray3d& InOutScaledDistances)` (scope `ProxyLOD`) — Convert pre-computed Scaled Distances to Barycentric coordinates for a 2d triangle V1V2, V2V0, V0V1. NB: In practice, use ComputeScaledDistances to arrive at signed scaled distances between triangle edges and a point If the signs all indicate (i.e. all positive) the point is inside the given triangle, use this function to convert to Barycentric coords. @param  Vertices                 Define a triangle on a 2d plane. @param  InOutScaledDistances     Precomputed scaled distances to a 2d point to be converted to Barycentric on return.
- L72 _function_ `static DArray3d ComputeBarycentricWeights(const DTriangle2d& Vertices, const DVec2d& Point)` (scope `ProxyLOD`) — Compute the barycentric weights at 2D @param Point assuming the 2D vertices are given in counter clockwise order. NB: This is for 2D triangles and points. @param  Vertices                 Define a triangle on a 2d plane. @param  Point                    Point on the plane. @return Barycentric coordinates (alpha, beta, gamma) of the point relative to the input triangle. alpha = 1 at Vertices[0],  beta = 1 at Vertices[1] and gamma = 1 at Vertices[2]
- L102 _function_ `static DArray3d ComputeBarycentricWeights(const FVector3f(&Vertices)[3], const FVector3f& Point)` (scope `ProxyLOD`) — Compute the barycentric weights at 3D @param Point projected onto the plane of triangle described in 3d. assuming triangle ertices are given in counter clockwise order. NB: This is for 3D triangles and points. @param  Vertices                 Define a triangle. @param  Point                    Point in 3d space. @return Barycentric coordinates (alpha, beta, gamma) of the point relative to the input triangle. alpha = 1 at Vertices[0],  beta = 1 at Vertices[1] and gamma = 1 at Vertices[2]

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODDebugTimer.h` (Private)


#### Free symbols / members of external scopes

- L14 _macro_ `#define PROXYLOD_DEBUG_TIMER(name_) (void)name_;`

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODGrid2d.h` (Private)


#### struct `ProxyLOD::FTextureAtlasDesc`  
`struct FTextureAtlasDesc`  
_L15-31_
- desc: Definition of the texture atlas texel resolution and gutter size, also in texels.
- L17 _public function_ `FTextureAtlasDesc() : Size() , Gutter()`
- L23 _public function_ `FTextureAtlasDesc(const FIntPoint& S, const double G) : Size(S) , Gutter(G)`
- L29 _public member_ `FIntPoint Size;`
- L30 _public member_ `float Gutter;`

#### class `ProxyLOD::TGrid`  
`template< typename GridDataType> class TGrid`  
_L40-137_
- desc: Template two-dimensional grid class that manages its own memory. NB: The first direction is the fast direction in memory.
- L43 _public typedef_ `typedef TSharedPtr<TGrid> Ptr;`
- L44 _public typedef_ `typedef GridDataType ValueType;`
- L51 _public function_ `static Ptr Create(int32 INum, int32 JNum)` — Construct a grid managed by a shared pointer @param  INum  number of elements in the 1st direction. @param  JNum  number of elements in the 2nd direction.
- L62 _public prototype_ `TGrid(uint32 INum, uint32 JNum);` — Constructor @param  INum  number of elements in the 1st direction. @param  JNum  number of elements in the 2nd direction.
- L68 _public prototype_ `~TGrid();` — Destructor. Deletes any allocated memory.
- L76 _public prototype_ `FIntPoint Size() const;` — The Shape of this two dimensional grid. @return (Imax, Jmax) the length of the 1st and 2nd dimensions mananged by this grid.
- L89 _public prototype_ `const ValueType& Get(const uint32 i, const uint32 j) const;` — Const and non-const access memory in 2d layout fashion. NB: i should be in the range [0, IMax -1] j should be in the range [0, JMax -1] @param i  The coordinate in first direction. @param j  The coordinate in second direction. @return const/nonconst reference to Value nominally stored at (i,j)
- L90 _public prototype_ `ValueType& Get(const uint32 i, const uint32 j);`
- L104 _public prototype_ `const ValueType& operator()(const uint32 i, const uint32 j) const;` — Const and non-const access memory in 2d layout fashion. NB: i should be in the range [0, IMax -1] j should be in the range [0, JMax -1] @param i  The coordinate in first direction. @param j  The coordinate in second direction. @return const/nonconst reference to Value nominally stored at (i,j)
- L105 _public prototype_ `ValueType& operator()(const uint32 i, const uint32 j);`
- L112 _public function_ `const ValueType* GetData() const` — Const and non-const access memory in linear fashion @return const/nonconst pointer to the head of the memory
- L116 _public function_ `ValueType* GetData()`
- L126 _public prototype_ `void Swap(TGrid<ValueType>& other);` — Swap the data payload of this grid with another grid containing the same data type payload.
- L132 _private function_ `TGrid(const TGrid& other)` — Can't copy me
- L134 _private member_ `uint32 IMax;`
- L135 _private member_ `uint32 JMax;`
- L136 _private member_ `GridDataType* DataArray;`
- L280 _function_ `template< typename GridDataType> TGrid<GridDataType>::TGrid(uint32 INum, uint32 JNum) : IMax(INum), JMax(JNum)`
- L289 _function_ `template< typename GridDataType> TGrid<GridDataType>::~TGrid()`
- L295 _function_ `template< typename GridDataType> FIntPoint TGrid<GridDataType>::Size() const`
- L300 _function_ `template< typename GridDataType> const GridDataType& TGrid<GridDataType>::Get(const uint32 i, const uint32 j) const`
- L308 _function_ `template< typename GridDataType> GridDataType& TGrid<GridDataType>::Get(const uint32 i, const uint32 j)`
- L316 _function_ `template< typename GridDataType> const GridDataType& TGrid<GridDataType>::operator()(const uint32 i, const uint32 j) const`
- L321 _function_ `template< typename GridDataType> GridDataType& TGrid<GridDataType>::operator()(const uint32 i, const uint32 j)`
- L326 _function_ `template< typename GridDataType> void TGrid<GridDataType>::Swap(TGrid<GridDataType>& other)`

#### class `ProxyLOD::TGridWrapper`  
`template <typename ValueType> class TGridWrapper`  
_L148-223_
- desc: Template wrapped used to give two-dimensional grid semantics to a pre-existing linear tarray. NB: The first direction is the fast direction in memory. This wrapper does not manage the memory of the TArray.
- L161 _public prototype_ `TGridWrapper(TArray<ValueType>& LinearArray, const FIntPoint& Shape);` — Constructor used to map a TArray to a grid. NB: It is required that the shape and the size fo the grid are consitent: Shape.X * Shape.Y == LinearArray.Num() @param  LinearArray  The underlying array to be expressed at a 2d grid. @param  Shape defines the (Imax, Jmax) extent of the grid
- L168 _public prototype_ `FIntPoint Size() const;` — The Shape of this two dimensional grid. @return (Imax, Jmax) the length of the 1st and 2nd dimensions managed by this grid.
- L181 _public prototype_ `const ValueType& Get(const int32 i, const int32 j) const;` — Const and non-const access memory in 2d layout fashion. NB: i should be in the range [0, IMax -1] j should be in the range [0, JMax -1] @param i  The coordinate in first direction. @param j  The coordinate in second direction. @return const/nonconst reference to Value nominally stored at (i,j)
- L182 _public prototype_ `ValueType& Get(const int32 i, const int32 j);`
- L195 _public prototype_ `const ValueType& operator()(const int32 i, const int32 j) const;` — Const and non-const access memory in 2d layout fashion. NB: i should be in the range [0, IMax -1] j should be in the range [0, JMax -1] @param i  The coordinate in first direction. @param j  The coordinate in second direction. @return const/nonconst reference to Value nominally stored at (i,j)
- L196 _public prototype_ `ValueType& operator()(const int32 i, const int32 j);`
- L204 _public function_ `const ValueType* GetData() const` — Const and non-const access memory in linear fashion @return const/nonconst pointer to the head of the memory
- L208 _public function_ `ValueType* GetData()`
- L216 _private prototype_ `TGridWrapper();` — No.  Can only construct with a TArray
- L218 _private prototype_ `TGridWrapper(const TGridWrapper&);` — No need to copy this wrapper.
- L220 _private member_ `int32 IMax;`
- L221 _private member_ `int32 JMax;`
- L222 _private member_ `ValueType* DataArray;`
- L229 _function_ `template <typename ValueType> TGridWrapper<ValueType>::TGridWrapper(TArray<ValueType>& LinearArray, const FIntPoint& Shape) : IMax(Shape.X), JMax(Shape.Y), DataArray(LinearArray.GetData())`
- L238 _function_ `template <typename ValueType> FIntPoint TGridWrapper<ValueType>::Size() const`
- L244 _function_ `template <typename ValueType> const ValueType& TGridWrapper<ValueType>::Get(const int32 i, const int32 j) const`
- L254 _function_ `template <typename ValueType> ValueType& TGridWrapper<ValueType>::Get(const int32 i, const int32 j)`
- L265 _function_ `template <typename ValueType> const ValueType& TGridWrapper<ValueType>::operator()(const int32 i, const int32 j) const`
- L271 _function_ `template <typename ValueType> ValueType& TGridWrapper<ValueType>::operator()(const int32 i, const int32 j)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ProxyLOD`

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODMaterialTransferUtilities.h` (Private)


#### class `ProxyLOD::FSrcMeshData`  
`class FSrcMeshData`  
_L135-185_
- L139 _public function_ `FSrcMeshData()`
- L141 _public function_ `FSrcMeshData(const FSrcMeshData& other) : TriangleId(other.TriangleId), MaterialId(other.MaterialId)`
- L153 _public function_ `void operator=(const FSrcMeshData& other)`
- L167 _public member_ `int32 TriangleId = -1;` — @todo - why not int16?
- L168 _public member_ `int32 MaterialId = -1;`
- L169 _public member_ `FVector2D UV;`
- L170 _public member_ `DArray3d BarycentricCoords = { 0., 0., 0. };`
- L173 _public member_ `int32 Forward;` — ray direction
- L180 _public member_ `int16 CoAligned = 1;`
- L184 _public member_ `int16 Handedness = 1;` — either 1 or -1

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ProxyLOD`
- L25 _typedef_ `typedef TGrid<FSrcMeshData> FSrcDataGrid;` (scope `ProxyLOD`) — Two dimensional grid implicitly mapping locations in texture atlas space to FSrcMeshData that references locations on the source geometry and perhaps more information about how that location was identified.
- L49 _prototype_ `FSrcDataGrid::Ptr CreateCorrespondence( const FMeshDescriptionArrayAdapter& SrcMesh, const FkDOPTree& SrckDOPTree, const FVertexDataMesh& ReducedMesh, const ProxyLOD::FRasterGrid& ReducedMeshUVGrid, const int32 TransferType, float MaxRayLength = 3.f);` (scope `ProxyLOD`) — Generate a map between UV locations on the simplified geometry and points on the Src geometry. This is done by firing rays from locations on the reduced mesh polys that correspond to texel centers in a texture atlas grid space and recording the poly and uv-coordinate location hit in the SrcMesh along with additional information. Texels in the resulting FSrcDataGrid that  have MaterialId = -1; @param SrcMesh             High poly grid that represents the source geometry. @param SrckDOPTree         kDOPTree of the SrcMesh. @param ReducedMesh         Low poly Mesh with UVs, that ostensibly represents the same geometry. @param ReducedMeshUVGrid   A mapping of the UVs on the ReducedMesh to the texture atlas space. @param TransferType        Controls the logic when a forward and reverse ray both hit high-res geometry. @param MaxRayLength        The maximum distance a ray is allowed to travel. @return FSrcDataGrid  - A texel in the SrcDataGrid(i,j) holds hit information that corresponds to a ray fired from the texel in ReducedMeshUVGrid(i,j). Because some locations in the texture atlas for the Reduced Mesh will fall outside of all the charts (i.e. be dead space), there will be texels in the SrcDataGrid that correspond to this space and will be given .MaterialId =-1 for quick identification.
- L81 _prototype_ `FSrcDataGrid::Ptr CreateCorrespondence( const openvdb::Int32Grid& ClosestSrcPolyGrid, const FMeshDescriptionArrayAdapter& SrcMesh, const FkDOPTree& SrckDOPTree, const FVertexDataMesh& ReducedMesh, const ProxyLOD::FRasterGrid& ReducedMeshUVGrid, const int32 TransferType, float MaxRayLength = 3.f);` (scope `ProxyLOD`) — Generate a map between UV locations on the simplified geometry and points on the Src geometry. This is done by using an existing data structure that holds the Id of the closes Src geometry poly in a sparse voxel grid. The sparsity of the grid (i.e. only values fairly close the the boundary of the src geomgery are populated) limits the utility of this functional variant.  In this approach the locations on the the reduced mesh polys that correspond to texel centers in a texture atlas grid space are projected onto the closest Src geometry poly and a record the Src poly and uv-coordinate location within that poly are stored in the resulting grid. Texels in the resulting FSrcDataGrid that  have MaterialId = -1; @param ClosestSrcPolyGrid  Sparse 3d grid that holds the Id of the closest poly to a given voxel. @param SrcMesh             High poly grid that represents the source geometry. @param SrckDOPTree         kDOPTree of the SrcMesh. @param ReducedMesh         Low poly Mesh with UVs, that ostensibly represents the same geometry. @param ReducedMeshUVGrid   A mapping of the UVs on the ReducedMesh to the texture atlas space. @param TransferType        Controls the logic when a forward and reverse ray both hit high-res geometry. @param MaxRayLength        The maximum distance a ray is allowed to travel. @return FSrcDataGrid  - A texel in the SrcDataGrid(i,j) holds hit information that corresponds to a ray fired from the texel in ReducedMeshUVGrid(i,j). Because some locations in the 
- L109 _prototype_ `void MapFlattenMaterials( const FMeshDescription& DstRawMesh, const FMeshDescriptionArrayAdapter& SrcMeshAdapter, const ProxyLOD::FSrcDataGrid& SuperSampledCorrespondenceGrid, const ProxyLOD::FRasterGrid& SuperSampledDstUVGrid, const ProxyLOD::FRasterGrid& DstUVGrid, const TArray<FFlattenMaterial>& InMaterials, const FColor UnresolvedSrcColor, FFlattenMaterial& OutMaterial);` (scope `ProxyLOD`) — Utility used generate new Flattened Materials for the DstRawMesh that correspond to the super-sampling of Flattened materials for the Source Geometry (SrcMeshAdapter). @param DstRawMesh                       Simplified Geometry @param SrcMeshAdapter                   High poly source meshes @param SuperSampledCorrespondenceGrid   High resolution Grid that maps locations in the texture atlas space ( of the Simplified Geometry ) to locations on the Src Geometry. @param SuperSampledDstUVGrid            High resolution Grid that maps locations in the texture atlas space ( of the Simplified Geometry) to positions on the Simplified Geometry. @param InMaterials                      Array of flattened materials corresponding to the various meshes in the Src geometry. @param UnresolvedSrcColor               Base color to be used when the src geometry can't be identified (e.g. regions where gap filling has closed doors and windows) @param OutMaterials                     Flattened materials for the Simplified Geometry. Map Diffuse, Specular, Metallic, Roughness, Normal, Emissive, Opacity to the correct materials. NB: EFlattenMaterialProperties: SubSurface, OpacityMask and AmbientOcclusion are not included
- L123 _prototype_ `void ColorMapFlattedMaterials( const FVertexDataMesh& VertexDataMesh, const FMeshDescriptionArrayAdapter& MeshAdapter, const ProxyLOD::FRasterGrid& UVGrid, const TArray<FFlattenMaterial>& InputMaterials, FFlattenMaterial& OutMaterial);` (scope `ProxyLOD`) — Testing Utility used generate new Flattened Materials for the DstRawMesh that corresponds to mapping each triangle id to a color.
- L132 _prototype_ `void CopyFlattenMaterial( const FFlattenMaterial& InMaterial, FFlattenMaterial& OutMaterial);` (scope `ProxyLOD`) — Used for testing - copies a flattened material

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODMeshAttrTransfer.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ProxyLOD`
- L21 _prototype_ `void TransferVertexColors(const FClosestPolyField& SrcPolyField, FMeshDescription& InOutMesh);` (scope `ProxyLOD`) — Transfers the Barycenteric-averaged wedge colors from a high poly mesh to a simplified version of the same geometry. NB: This is not a general purpose tool as it assumes the simplified geometry is within a small fixed distance of the source geometry. @param  SrcPolyField  The closest poly field derived from the high poly src mesh @param  InOutMesh     The target raw mesh.  Only the wedge colors on this target are updated.
- L34 _prototype_ `void TransferSrcNormals( const FClosestPolyField& SrcPolyField, FAOSMesh& InOutMesh );` (scope `ProxyLOD`) — Transfers Barycenteric-averaged vertex normals from a high poly mesh src mesh to a simplified version of the same geometry. NB: This is not a general purpose tool as it assumes the simplified geometry is within a small fixed distance of the source geometry. @param  SrcPolyField  The closest poly field derived from the high poly src mesh @param  InOutMesh     The target Array Of Structs Mesh.  Only the normal is updated.
- L45 _function_ `static void TransferSrcNormals( const FClosestPolyField& SrcPolyField, FPosSimplifierMesh& InOutMesh)` (scope `ProxyLOD`) — No OP! NB: This function is a No Op since the target mesh type does not support normals. The function only exists to simplify some templated code. @param  SrcPolyField  The closest poly field derived from the high poly src mesh @param  InOutMesh     The target Position Only mesh Mesh.  Only the normal is updated.
- L61 _prototype_ `void ProjectVertexWithSnapToNearest( const FClosestPolyField& SrcPolyField, FMeshDescription& InOutMesh );` (scope `ProxyLOD`) — Update the vertex position of low poly mesh to better align with a high poly src geometry. This will attempt to snap a low poly vertex to the location of the closest high poly source vertex if one is close, otherwise it will simply project the vertex 90% of the distance to the source surface. All other vertex attributes on the InOutMesh (e.g. Tangent Space) are unchanged by this. NB: This is not a general purpose tool as it assumes the simplified geometry is within a small fixed distance of the source geometry. @param  SrcPolyField  The closest poly field derived from the high poly src mesh @param  InOutMesh     The target low poly mesh.  Only the position is updated.
- L62 _prototype_ `void ProjectVertexWithSnapToNearest( const FClosestPolyField& SrcPolyField, FAOSMesh& InOutMesh );` (scope `ProxyLOD`)
- L63 _prototype_ `void ProjectVertexWithSnapToNearest( const FClosestPolyField& SrcPolyField, FVertexDataMesh& InOutMesh);` (scope `ProxyLOD`)
- L77 _prototype_ `void ProjectVertexOntoSrcSurface( const FClosestPolyField& SrcPolyField, FMeshDescription& InOutMesh );` (scope `ProxyLOD`) — Update the vertex position of low poly mesh to better align with a high poly src geometry. This will simply project the vertex 90% of the distance to the source surface. All other vertex attributes on the InOutMesh (e.g. Tangent Space) are unchanged by this. NB: This is not a general purpose tool as it assumes the simplified geometry is within a small fixed distance of the source geometry. @param  SrcPolyField  The closest poly field derived from the high poly src mesh @param  InOutMesh     The target low poly mesh.  Only the position is updated.
- L78 _prototype_ `void ProjectVertexOntoSrcSurface( const FClosestPolyField& SrcPolyField, FAOSMesh& InOutMesh );` (scope `ProxyLOD`)
- L79 _prototype_ `void ProjectVertexOntoSrcSurface( const FClosestPolyField& SrcPolyField, FVertexDataMesh& InOutMesh );` (scope `ProxyLOD`)
- L94 _prototype_ `void TransferMeshAttributes(const FClosestPolyField& SrcPolyField, FMeshDescription& InOutMesh);` (scope `ProxyLOD`) — Primarily intended as testing code. Update the tangent space, wedge colors, and first texture coords with the face-averaged value of the closest poly in the high poly SrcPolyField. NB: This is not a general purpose tool as it assumes the simplified geometry is within a small fixed distance of the source geometry. @param  SrcPolyField  The closest poly field derived from the high poly src mesh @param  InOutMesh     The target low poly mesh.

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODMeshConvertUtils.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace ProxyLOD`
- L31 _prototype_ `void MixedPolyMeshToRawMesh( const FMixedPolyMesh& InMesh, FMeshDescription& OutMesh );` (scope `ProxyLOD`) — Convert a mixed triangle and quad mesh to a triangle mesh type by splitting quads. No new vertices are created. NB: Default valued attributes are added to the resulting mesh, e.g. tangent space, colors, etc @param InMesh   Mesh with a mixture of quads and triangles. @param OutMesh  Triangle Mesh.
- L45 _prototype_ `template <typename T> void MixedPolyMeshToAOSMesh(const FMixedPolyMesh& InMesh, TAOSMesh<T>& OutMesh, const bool bClockWise = true);` (scope `ProxyLOD`) — Convert a mixed triangle and quad mesh to a triangle mesh type by splitting quads. No new vertices are created. NB: This does not attempt to add any additional attributes to the result.  Will need to separately compute vertex normals if desired. @param InMesh   Mesh with a mixture of quads and triangles. @param OutMesh  Triangle Mesh. @param bClockWise how to order the verts in a triangle
- L59 _prototype_ `void ConvertMesh(const FAOSMesh& InMesh, FMeshDescription& OutMesh);` (scope `ProxyLOD`) — Common interface to convert between various triangle-based mesh types. The conversions will maintain geometry and connectivity, but different mesh types support different attribute types and possibly different frequenceies even when the same attribute types exist on both mesh types ( e.g. FMeshDescription has per-wedge data while FVertexDataMesh has per-vertex attributes). @param InMesh   Source Mesh to convert. @param OutMesh  The result of the mesh conversion.  Any data already stored in OutMesh will be lost.
- L60 _prototype_ `void ConvertMesh(const FAOSMesh& InMesh, FVertexDataMesh& OutMesh);` (scope `ProxyLOD`)
- L61 _prototype_ `void ConvertMesh(const FVertexDataMesh& InMesh, FMeshDescription& OutMesh);` (scope `ProxyLOD`)
- L62 _prototype_ `void ConvertMesh(const FMeshDescription& InMesh, FVertexDataMesh& OutMesh);` (scope `ProxyLOD`)
- L75 _prototype_ `void AOSMeshToRawMesh( const FAOSMesh& InMesh, FMeshDescription& OutMesh );` (scope `ProxyLOD`) — Convert the simplifier-friendly array-of-structs mesh to a struct of arrays FMeshDescription. NB: This copies the AOSVertex normal to the wedge FMeshDescription::Tangentz. But additional FMeshDescription attributes, including tangent/bitangent are given default values. @param InMesh   Source Mesh to convert. @param OutMesh  The result of the mesh conversion.  Any data already stored in OutMesh will be lost.
- L87 _prototype_ `void VertexDataMeshToRawMesh( const FVertexDataMesh& InMesh, FMeshDescription& OutMesh );` (scope `ProxyLOD`) — Convert the uv-generation-friendly vertex data mesh to a struct of arrays FMeshDescription. In addition to connectivity and vertex locations, this also transfers tangent space and UVs. @param InMesh   Source Mesh to convert. @param OutMesh  The result of the mesh conversion.  Any data already stored in OutMesh will be lost.
- L98 _prototype_ `void RawMeshToVertexDataMesh( const FMeshDescription& InMesh, FVertexDataMesh& OutMesh );` (scope `ProxyLOD`) — Converts a FMeshDescription to a  uv-generation-friendly vertex data mesh.  This is potentially has some loss since the raw mesh is nominally a per-index data structure and the vertex data mesh is a per-vertex structure. In addition, this only transfers the first texture coordinate and ignores material ids and vertex colors. @param InMesh   Source Mesh to convert. @param OutMesh  The result of the mesh conversion.  Any data already stored in OutMesh will be lost.
- L104 _macro_ `#define PROXYLOD_CLOCKWISE_TRIANGLES 1`
- L107 _function_ `static FVector3f ComputeNormal(const FVector3f(&Tri)[3])`
- L121 _function_ `template <typename T> void ProxyLOD::MixedPolyMeshToAOSMesh(const FMixedPolyMesh& MixedPolyMesh, TAOSMesh<T>& DstAOSMesh, bool bClockWise)` (scope `ProxyLOD`) — Convert MixedPolyMesh to AOS Mesh.  This requires splitting quads to produce triangles.
- L145 _function_ `` (scope `ProxyLOD::MixedPolyMeshToAOSMesh`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODMeshParameterization.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ProxyLOD`
- L34 _prototype_ `bool GenerateUVs( FVertexDataMesh& InOutMesh, const FTextureAtlasDesc& InTextureAtlasDesc, const bool bVertexColorParts = false);` (scope `ProxyLOD`) — Primary entry point: Method that generates new UVs on the FVertexDataMesh according to the parameters specified in the FTextureAtlasDesc The underlying code uses Isometeric approach (Iso-Charts) in UV generation. As a debugging option, the updated InOutMesh can have vertex colors that distinguish the various UV charts. NB: The mesh vertex count may change as vertices are split on UV seams. @param InOutMesh            Mesh that will be updated by this function, adding UVs @param InTextureAtlasDesc   Description of the texel resolution of the desired texture atlas. @param bVertColorParts      Option to add vertex colors according the the chart in the texture atlas, used for debugging. @return 'true' if the UV generation succeeded,  'false' if it failed.
- L60 _prototype_ `bool GenerateUVs(FVertexDataMesh& InOutMesh, const FTextureAtlasDesc& TextureAtlasDesc, const bool bVertexColorParts, const float MaxStretch, const size_t MaxChartNumber, const bool bComputeIMTNormal, std::function<HRESULT __cdecl(float percentComplete)> StatusCallBack, float* MaxStretchOut = NULL, size_t* NumChartsOut = NULL);` (scope `ProxyLOD`) — Lower-level entry point: Method that generates new UVs on the FVertexDataMesh according to the parameters specified in the FTextureAtlasDesc The underlying code uses Isometeric approach (Iso-Charts) in UV generation. As a debugging option, the updated InOutMesh can have vertex colors that distinguish the various UV charts. NB: The mesh vertex count may change as vertices are split on UV seams. @param InOutMesh            Mesh that will be updated by this function, adding UVs @param InTextureAtlasDesc   Description of the texel resolution of the desired texture atlas. @param bVertColorParts      Option to add vertex colors according the the chart in the texture atlas, used for debugging. @param MaxStretch           The maximum amount of stretch between (0 - none and 1 - any) @param MaxChartNumber       Maximum number of charts required for the atlas.  If this is 0, will be parameterized solely on stretch. Note, not a hard limit - isochart will stop when a valid charting is found that is greater or equal to this number. @param bComputeIMTNormal    Compute a metric tensor from the normals.  Generally not a good thing. @param StatusCallBack       Allows for termination of the UV generation. @param MaxStretchOut        Actual max stretch used in computing uvs @param NumChartsOut         Number of charts actually generated @return 'true' if the UV generation succeeded,  'false' if it failed.
- L95 _prototype_ `bool GenerateUVs(const FTextureAtlasDesc& TextureAtlasDesc, const TArray<FVector3f>& VertexBuffer, const TArray<int32>& IndexBuffer, const TArray<int32>& AdjacencyBuffer, TFunction<bool(float)>& Callback, TArray<FVector2D>& UVVertexBuffer, TArray<int32>& UVIndexBuffer, TArray<int32>& VertexRemapArray, float& MaxStretch, int32& NumCharts);` (scope `ProxyLOD`) — Lower-level entry point: Method that generates new UVs inconstant with the mesh defined by the VertexBuffer/IndexBuffer according to the parameters specified in the FTextureAtlasDesc The underlying code uses Isometeric approach (Iso-Charts) in UV generation. This assumes that the caller has already generated the mesh adjacency information. @param InTextureAtlasDesc   Description of the texel resolution of the desired texture atlas. @param VertexBuffer         Positions of vertices @param IndexBuffer          Triangle definitions @param AdjacencyBuffer      3 entries for each face, each entry is the face index of the face that is adjacent to the given face. -1 means no face. @param StatusCallBack       Allows for termination of the UV generation. @param UVVertexBuffer       Resulting UVs @param UVIndexBuffer        Connectivity for the UVs @param VertexRemapArray     Array that remaps the vertices split by the UV generation to the source vertices. @param MaxStretch           On Input, The maximum amount of stretch between (0 - none and 1 - any), on Output the actual max stretch used. @param MaxChartNumber       On Input Maximum number of charts required for the atlas.  If this is 0, will be parameterized solely on stretch. Note, not a hard limit - isochart will stop when a valid charting is found that is greater or equal to this number. On Output: Number of charts actually generated @return 'true' if the UV generation succeeded,  'false' if it failed.
- L115 _prototype_ `bool GenerateAdjacenyAndCleanMesh(FVertexDataMesh& InOutMesh, std::vector<uint32>& OutAdjacency);` (scope `ProxyLOD`) — Generate adjacency data needed for the mesh, additionally this may alter the mesh in attempting to remove mesh degeneracy problems.  This method is primarily called within GenerateUVs @param InOutMesh          Mesh to process. @param OutAdjacency       Adjacency data understood by the DirectX Mesh code. @return  'true' if the mesh was successfully cleaned of all bow-ties.
- L125 _prototype_ `void GenerateAdjacency(const FVertexDataMesh& InMesh, std::vector<uint32>& OutAdjacencyArray);` (scope `ProxyLOD`) — Generate mesh adjacency used by mesh clean code and uv generation code. Various mesh types are supported. @param InOutMesh          Mesh to process. @param OutAdjacency       Adjacency data understood by the DirectX Mesh code.
- L126 _prototype_ `void GenerateAdjacency(const FAOSMesh& InMesh, std::vector<uint32>& OutAdjacencyArray);` (scope `ProxyLOD`)
- L127 _prototype_ `void GenerateAdjacency(const FMeshDescription& InMesh, std::vector<uint32>& OutAdjacencyArray);` (scope `ProxyLOD`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODMeshPartition.h` (Private)


#### class `ProxyLOD::FMajorAxisPartitionFunctor`  
`class FMajorAxisPartitionFunctor`  
_L236-270_
- L239 _public function_ `FMajorAxisPartitionFunctor(const ProxyLOD::FBBox& BBox, const int32 NumPartitions) : Num(NumPartitions)`
- L250 _public function_ `FMajorAxisPartitionFunctor(const FMajorAxisPartitionFunctor& other) : Num(other.Num), MajorIndex(other.MajorIndex), Min(other.Min), NumOnLength(other.NumOnLength)`
- L254 _public function_ `int32 operator()(const FVector(&Verts)[3]) const`
- L263 _public function_ `int32 NumPartitions() const`
- L266 _private member_ `int32 Num;`
- L267 _private member_ `int32 MajorIndex;`
- L268 _private member_ `float Min;`
- L269 _private member_ `float NumOnLength;`

#### union `ProxyLOD::MergeMeshArray::__anon1d796a740302::(anonymous)`  
`union`  
_L417-417_

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace ProxyLOD`
- L44 _prototype_ `template <typename VertexType, typename PartitionFunctor> void CreatePartitionArray( const TAOSMesh<VertexType>& InMesh, const PartitionFunctor& Functor, TArray<int32>& OutPartitionArray);` (scope `ProxyLOD`) — Create an array that maps triangle faces to various partitions. Required Interface struct FunctorInterface { int32 operator()(const FVector (&In)[3]); int32 NumPartitions() const ; }; @param InMesh             Triangle mesh - the various faces will be assigned to partitions. @param Functor            The partition functor takes the three verts of a triangle and returns a partition value @param OutPartitionArray  Has one entry for each face in the mesh - OutPartitionArray[i] indicates the partition assignment for face 'i'.  Any previous content will be destroyed.
- L64 _prototype_ `template <typename VertexType, typename PartitionFunctor> void PartitionMeshSplit( const TAOSMesh<VertexType>& InMesh, const PartitionFunctor& Functor, TArray<TAOSMesh<VertexType>>& OutMeshArray);` (scope `ProxyLOD`) — Generate an array of meshes that results from applying the partition functor to spatially split the mesh. Required Interface struct FunctorInterface { int32 operator()(const FVector (&In)[3]); int32 NumPartitions() const ; }; @param InMesh        Mesh to partition into multiple meshes. @param Functor       A functor that controls face to partition assignment. @param OutMeshArray  Array of meshes that corresponds to the original geometry.  Any previous content will be destroyed.
- L79 _prototype_ `template <typename VertexType> static void PartitionOnMajorAxis( const TAOSMesh<VertexType>& InMesh, const ProxyLOD::FBBox& InBBox, uint32 InNumPartitions, TArray<TAOSMesh<VertexType>>& OutMeshArray);` (scope `ProxyLOD`) — Decompose the bbox into "NumPartitions" equal sized blocks along the major axis, numbered [0.. NumPartitions-1]. A triangle is assigned to the partition with smallest id number that contains one of its verts. On return ResultMeshArray will hold a unique mesh for each logical partition. @param InMesh        Mesh to partition into multiple meshes. @param InBBox        The bounds that are subdivided into spatial partitions. @param OutMeshArray  Array of meshes that corresponds to the original geometry.  Any previous content will be destroyed.
- L95 _prototype_ `template <typename VertexType> bool MergeMeshArray( TArray<TAOSMesh<VertexType>>& InMeshArray, TAOSMesh<VertexType>& OutMesh);` (scope `ProxyLOD`) — Merges the input MeshArray into a single mesh. NB: Note this destroys the input mesh array NB: the resulting mesh has split verts on the seams of the merge. @param InMeshArray  Array of meshes.  Will be destroyed. @param OutMesh      Container holding the union of all meshes.  Will have split verts on seams.
- L112 _prototype_ `template <typename VertexType> bool MergeMeshArray( TArray<TAOSMesh<VertexType>>& InMeshArray, const TArray<int32> * InSeamVertArrayOfArrays, TAOSMesh<VertexType>& OutMesh);` (scope `ProxyLOD`) — Merges the input MeshArray into a single mesh.  This function makes use of tagged vertexes, called seam verts that have been identified as having a duplicate vertex in at least one other mesh.  In use these seam verts are identified by the simplifier as "locked" verts. NB: the duplicate locked verts should be eliminated. @param InMeshArray  Array of meshes.  Will be destroyed @param InSeamVerts  Array of Arrays of seam vertex identifiers.  One array of seam vertexes for each mesh in the mesh array.  These are special tags that indicate a duplicate (also taged) vertex should exist in at least one of the other meshes. @param OutMesh      On return this should hold a fully merged mesh - all "seam" vertices should be merged.
- L122 _function_ `template <typename VertexType, typename PartitionFunctor> void ProxyLOD::CreatePartitionArray( const TAOSMesh<VertexType>& Mesh, const PartitionFunctor& Functor, TArray<int32>& PartitionArray)` (scope `ProxyLOD`)
- L135 _function_ `` (scope `ProxyLOD::CreatePartitionArray`)
- L156 _function_ `template <typename VertexType, typename PartitionFunctor> void ProxyLOD::PartitionMeshSplit( const TAOSMesh<VertexType>& SrcMesh, const PartitionFunctor& Functor, TArray<TAOSMesh<VertexType>>& ResultMeshArray)` (scope `ProxyLOD`)
- L160 _typedef_ `typedef TAOSMesh<VertexType> MeshType;` (scope `ProxyLOD::PartitionMeshSplit`)
- L183 _function_ `` (scope `ProxyLOD::PartitionMeshSplit`)
- L234 _namespace_ `namespace ProxyLOD`
- L275 _function_ `template <typename VertexType> static void ProxyLOD::PartitionOnMajorAxis( const TAOSMesh<VertexType>& SrcMesh, const ProxyLOD::FBBox& BBox, uint32 NumPartitions, TArray<TAOSMesh<VertexType>>& ResultMeshArray)` (scope `ProxyLOD`)
- L293 _function_ `template <typename VertexType> bool ProxyLOD::MergeMeshArray( TArray<TAOSMesh<VertexType>>& MeshArray, TAOSMesh<VertexType>& ResultMesh)` (scope `ProxyLOD`)
- L347 _function_ `template <typename VertexType> bool ProxyLOD::MergeMeshArray( TArray<TAOSMesh<VertexType>>& MeshArray, const TArray<int32> * SeamVertArrayOfArrays, TAOSMesh<VertexType>& ResultMesh)` (scope `ProxyLOD`)
- L416 _function_ `` (scope `ProxyLOD::MergeMeshArray`)
- L417 _member_ `union { float f; uint32 i; } x;` (scope `ProxyLOD::MergeMeshArray::__anon1d796a740302::__anon1d796a74040a`)
- L417 _member_ `union { float f; uint32 i; } x;` (scope `ProxyLOD::MergeMeshArray::__anon1d796a740302::__anon1d796a74040a`)
- L418 _member_ `union { float f; uint32 i; } y;` (scope `ProxyLOD::MergeMeshArray::__anon1d796a740302::__anon1d796a74050a`)
- L418 _member_ `union { float f; uint32 i; } y;` (scope `ProxyLOD::MergeMeshArray::__anon1d796a740302::__anon1d796a74050a`)
- L419 _member_ `union { float f; uint32 i; } z;` (scope `ProxyLOD::MergeMeshArray::__anon1d796a740302::__anon1d796a74060a`)
- L419 _member_ `union { float f; uint32 i; } z;` (scope `ProxyLOD::MergeMeshArray::__anon1d796a740302::__anon1d796a74060a`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODMeshSDFConversions.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ProxyLOD`
- L27 _prototype_ `template <typename SrcMeshType> bool MeshToSDFVolume( const SrcMeshType& InMesh, const openvdb::math::Transform& InTransform, openvdb::FloatGrid::Ptr& OutSDFGrid, openvdb::Int32Grid* OutPolyIndexGrid = nullptr);` (scope `ProxyLOD`) — Generate a single sparse Signed Distance Field (SDF) Grid from the polys managed by InMesh, Optionally store the index of the closest poly is recorded in a sparse PolyIndexGrid. @param  InMesh			Source polygons to be voxelized. @param  OutSDFGrid        Resulting sparse signed distance field. @param  OutPolyIndexGrid  Optional resulting sparse grid. For each voxel with valid distance in the OutSDFGrid the index of the closest poly will be recorded in the corresponding voxel of the OutPolyIndedGrid. @retun 'true' is success, 'false' will generally be an out of memory error.
- L44 _prototype_ `template <typename DstMeshType> void SDFVolumeToMesh( const openvdb::FloatGrid::ConstPtr InSDFVolume, const double IsoValue, const double AdaptivityValue, DstMeshType& OutMesh);` (scope `ProxyLOD`) — Extract the isosurface (=IsoValue) of the given SDF volume, in the form of triangle mesh. NB: This produces geometry only, and ignores Tangents, Texture Coordinates and Colors etc. @param  InSDFVolume       Sparse signed distance field: voxel based representation of geometry. @param  IsoValue          Indicates the surface defined by this distance value. @param  AdaptivityValue   Internal adaptivity attempts to simplify regions of low curvature. Local face normals are compared using this value as a threshold. @param  OutMesh           Resulting triangular mesh that is consistent with the surface defined by the iso-value.
- L62 _prototype_ `template <typename AOSVertexType> void ExtractIsosurfaceWithNormals( const openvdb::FloatGrid::ConstPtr InSDFVolume, const double IsoValue, const double Adaptivity, TAOSMesh<AOSVertexType>& OutMesh);` (scope `ProxyLOD`) — Extract the isosurface (=IsoValue) of the given SDF volume, in the form of triangle mesh and adds very simple vertex normals. NB: This produces geometry only, and ignores Tangents, Texture Coordinates and Colors etc. @param  InSDFVolume       Sparse signed distance field: voxel based representation of geometry. @param  IsoValue          Indicates the surface defined by this distance value. @param  AdaptivityValue   Internal adaptivity attempts to simplify regions of low curvature. Local face normals are compared using this value as a threshold. @param  OutMesh           Resulting triangular mesh that is consistent with the surface defined by the iso-value.
- L85 _prototype_ `void CloseGaps(openvdb::FloatGrid::Ptr InOutSDFVolume, const double GapRadius, const int32 MaxDilations);` (scope `ProxyLOD`) — Updates the InOutSDFVollume to potentially close small holes and gaps in the iso-surface. This is particularly useful when processing distant buildings (where the doors and windows may only be a few voxels in size).  In this case, closing the openings may result in a water-tight mesh and thus remove interior geometry. NB: In addition to closing holes, this may merge nearby separate objects. @param InOutSDFVolume      Signed distance field that will be altered @param GapRadius           1/2 the length scale of the gap or hole size. @param MaxDilations        The max allowed number of dilation/erosion pairs, NB: If the GapRadius is large compared with the voxelsize of the input volume, the dilations and erosions will be done with a larger voxelsize (as determined by MaxDilations).
- L96 _prototype_ `void RemoveClipped(openvdb::FloatGrid::Ptr InOutSDFVolume, openvdb::FloatGrid::Ptr ClippingVolume);` (scope `ProxyLOD`) — Update the InOutSDFVolume by doing a CSG difference with the Clipping volume. NB: In addition to altering the InOutSDFVolume, this may destroy the clipping volume @param InOutSDFVolume     Signed distance field representing the interesting geometry. @param ClippingVolume     Signed distance field representing the region to be subtracted from the interesting geometry.
- L101 _function_ `template <typename SrcMeshType> bool ProxyLOD::MeshToSDFVolume(const SrcMeshType& InMesh, const openvdb::math::Transform& InTransform, openvdb::FloatGrid::Ptr& SDFGrid, openvdb::Int32Grid* PolyIndexGrid)` (scope `ProxyLOD`)
- L139 _function_ `template <typename DstMeshType> void ProxyLOD::SDFVolumeToMesh(const openvdb::FloatGrid::ConstPtr SDFVolume, const double IsoValue, const double Adaptivity, DstMeshType& OutMesh)` (scope `ProxyLOD`)
- L159 _function_ `template <typename AOSVertexType> void ProxyLOD::ExtractIsosurfaceWithNormals(const openvdb::FloatGrid::ConstPtr SDFVolume, const double IsoValue, const double Adaptivity, TAOSMesh<AOSVertexType>& OutMesh)` (scope `ProxyLOD`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODMeshTypes.h` (Private)


#### struct `FMixedPolyMesh`  
`struct FMixedPolyMesh`  
_L90-154_
- desc: Mesh type that holds minimal required data for openvdb iso-surface extraction interface. Implements the openvdb MeshDataAdapter interface. NB: std::vector required by the openvdb interface.
- L92 _public member_ `std::vector<openvdb::Vec3s> Points;`
- L93 _public member_ `std::vector<openvdb::Vec4I> Quads;`
- L94 _public member_ `std::vector<openvdb::Vec3I> Triangles;`
- L95 _public member_ `openvdb::math::Transform Transform;`
- L101 _public function_ `size_t polygonCount() const` — Total number of polygons
- L107 _public function_ `size_t pointCount() const` — Total number of points (vertex locations)
- L113 _public function_ `size_t vertexCount(size_t n) const` — Vertex count for polygon n
- L119 _public function_ `void getIndexSpacePoint(size_t n, size_t v, openvdb::Vec3d& pos) const` — Return position pos in local grid index space for polygon n and vertex v
- L135 _private function_ `bool PolygonIsQuad(size_t n) const`
- L140 _private function_ `bool PolygonIsTriangle(size_t n) const`
- L145 _private function_ `size_t GetQuadIndex(size_t n) const`
- L150 _private function_ `size_t GetTriangleIndex(size_t n) const`

#### struct `FVertexDataMesh`  
`struct FVertexDataMesh`  
_L162-183_
- desc: Vertex-based mesh type that works well with the DirectX  mesh tools. For this use case there are no split normals, i.e. Normal.Num() == Points.Num(); UVs.Num() == Points.Num();
- L164 _public member_ `TArray<uint32> Indices;`
- L165 _public member_ `TArray<FVector3f> Points;`
- L167 _public member_ `TArray<FVector3f> Normal;`
- L168 _public member_ `TArray<FVector3f> Tangent;`
- L169 _public member_ `TArray<FVector3f> BiTangent;`
- L172 _public member_ `TArray<FVector3f> TransferNormal;` — Optional. Used for ray shooting when transfering materials.
- L176 _public member_ `TArray<int32> TangentHanded;` — stores information about the tangentspace 1 = right handed.  -1 left handed
- L178 _public member_ `TArray<FVector2f> UVs;`
- L181 _public member_ `TArray<FColor> FaceColors;` — Per-face frequency
- L182 _public member_ `TArray<uint32> FacePartition;`

#### class `TAOSMesh`  
`template <typename SimplifierVertexType> class TAOSMesh`  
_L190-241_
- desc: A Triangle Mesh Array Of Structs (AOS) for the vertex data.  This should work with the simplification code.
- L194 _public typedef_ `typedef SimplifierVertexType VertexType;`
- L196 _public prototype_ `TAOSMesh();`
- L197 _public prototype_ `TAOSMesh(int32 VertCount, int32 FaceCount);`
- L199 _public prototype_ `~TAOSMesh();`
- L202 _public prototype_ `void Empty();` — reset the mesh to size zero, deleting content.
- L205 _public prototype_ `void Resize(int32 VertCount, int32 FaceCount);` — resize the mesh, deleting the current content.
- L208 _public prototype_ `void SetVertexAndIndexCount(uint32 VertCount, uint32 IndexCount);` — set the real vertex & index count after duplicate removal
- L211 _public prototype_ `void Swap(TAOSMesh& other);` — Swap content with an existing mesh of the same type.
- L215 _public prototype_ `openvdb::Vec3I GetFace(int32 FaceNumber) const;` — Get the indices that correspond to this face.
- L218 _public prototype_ `void GetPosArray(std::vector<FVector3f>& PosArray) const;` — Get an array of positions only.
- L222 _public prototype_ `int32 ComputeDegenerateTriCount() const;` — This method is for testing only.  Not designed for perf.
- L225 _public function_ `bool IsEmpty() const`
- L226 _public function_ `uint32 GetNumVertexes() const`
- L227 _public function_ `uint32 GetNumIndexes() const`
- L230 _public member_ `VertexType* Vertexes;` — unfettered public access.
- L231 _public member_ `uint32* Indexes;`
- L235 _private member_ `uint32 NumVertexes;`
- L236 _private member_ `uint32 NumIndexes;`
- L240 _private prototype_ `TAOSMesh(const TAOSMesh& other);`
- L603 _function_ `template <typename SimplifierVertexType> TAOSMesh<SimplifierVertexType>::TAOSMesh() : Vertexes(NULL), Indexes(NULL), NumVertexes(0), NumIndexes(0)`
- L611 _function_ `template <typename SimplifierVertexType> TAOSMesh<SimplifierVertexType>::TAOSMesh(int32 VertCount, int32 FaceCount) : Vertexes(NULL), Indexes(NULL), NumVertexes(0), NumIndexes(0)`
- L621 _function_ `template <typename SimplifierVertexType> TAOSMesh<SimplifierVertexType>::~TAOSMesh()`
- L627 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::Empty()`
- L639 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::Resize(int32 VertCount, int32 FaceCount)`
- L657 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::SetVertexAndIndexCount(uint32 VertCount, uint32 IndexCount)`
- L667 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::Swap(TAOSMesh& other)`
- L697 _function_ `template <typename SimplifierVertexType> openvdb::Vec3I TAOSMesh<SimplifierVertexType>::GetFace(int32 FaceNumber) const`
- L706 _function_ `template <typename SimplifierVertexType> void TAOSMesh<SimplifierVertexType>::GetPosArray(std::vector<FVector3f>& PosArray) const`
- L726 _function_ `template <typename SimplifierVertexType> int32 TAOSMesh<SimplifierVertexType>::ComputeDegenerateTriCount() const`

#### class `FMeshDescriptionAdapter`  
`class FMeshDescriptionAdapter`  
_L256-304_
- desc: Mesh adapter class that implements the needed API for the methods in openvdb that convert polygonal mesh to a signed distance field.
- L262 _public prototype_ `FMeshDescriptionAdapter(const FMeshDescription& InRawMesh, const openvdb::math::Transform& InTransform);` — Constructor
- L263 _public prototype_ `FMeshDescriptionAdapter(const FMeshDescriptionAdapter& other);`
- L266 _public prototype_ `size_t polygonCount() const;` — Total number of polygons
- L269 _public prototype_ `size_t pointCount() const;` — Total number of points (vertex locations)
- L272 _public function_ `size_t vertexCount(size_t n) const` — Vertex count for polygon n: currently FMeshDescription is just triangles.
- L275 _public prototype_ `void getIndexSpacePoint(size_t FaceNumber, size_t CornerNumber, openvdb::Vec3d& pos) const;` — Return position pos in local grid index space for polygon n and vertex v
- L280 _public function_ `const openvdb::math::Transform& GetTransform() const` — The transform used to map between the physical space of the mesh and the voxel space.
- L288 _private member_ `const FMeshDescription* RawMesh;` — Pointer to the raw mesh we are wrapping
- L294 _private prototype_ `void InitializeCacheData();` — Cache data
- L295 _private member_ `uint32 TriangleCount;`
- L296 _private member_ `TVertexAttributesConstRef<FVector3f> VertexPositions;`
- L298 _private member_ `TArray<FVertexInstanceID> IndexBuffer;` — Local version of the index array.  The FMeshDescription doesn't really have one.
- L303 _private member_ `const openvdb::math::Transform Transform;` — Transform used to convert the mesh space into the index space used by voxelization

#### enum `ERawPolyValues`  
`enum class ERawPolyValues : uint8`  
_L312-320_
- desc: Used to filter initialization of required values only
- L314 _public enumerator_ `None = 0`
- L315 _public enumerator_ `WedgeColors = (1 << 0)`
- L316 _public enumerator_ `WedgeTexCoords = (1 << 1)`
- L317 _public enumerator_ `WedgeTangents = (1 << 2)`
- L318 _public enumerator_ `VertexPositions = (1 << 3)`
- L319 _public enumerator_ `All = 0xff`

#### class `FMeshDescriptionArrayAdapter`  
`class FMeshDescriptionArrayAdapter`  
_L331-507_
- desc: Adapter class that make an array of raw meshes appear to be a single mesh with implementation of the methods to interact with the templated openvdb mesh to volume code. NB: This is only an adapter class that holds pointers to external objects.  It does not manage the lifetimes of those objects,
- L337 _public function_ `size_t polygonCount() const` — Total number of polygons managed by this class.
- L343 _public function_ `size_t pointCount() const` — Total number of points (positions) managed by this class
- L349 _public function_ `size_t vertexCount(size_t n) const` — Vertex count for polygon n: currently FMeshDescription is just triangles.
- L355 _public prototype_ `void getIndexSpacePoint(size_t FaceNumber, size_t CornerNumber, openvdb::Vec3d& pos) const;` — Return position pos in local grid index space for polygon (face number) n and vertex (conrner number) v
- L358 _public prototype_ `FMeshDescriptionArrayAdapter(const TArray<FMeshMergeData>& InMergeDataArray, const openvdb::math::Transform::Ptr InTransform);`
- L359 _public prototype_ `FMeshDescriptionArrayAdapter(const TArray<const FMeshMergeData*>& InMergeDataPtrArray);`
- L360 _public prototype_ `FMeshDescriptionArrayAdapter(const TArray<const FInstancedMeshMergeData*>& InMergeDataPtrArray);`
- L361 _public prototype_ `FMeshDescriptionArrayAdapter(const TArray<FMeshMergeData>& InMergeDataArray);`
- L362 _public prototype_ `FMeshDescriptionArrayAdapter(const TArray<FInstancedMeshMergeData>& InMergeDataArray);`
- L365 _public prototype_ `FMeshDescriptionArrayAdapter(const FMeshDescriptionArrayAdapter& other);` — copy constructor
- L368 _public prototype_ `~FMeshDescriptionArrayAdapter();` — Destructor
- L371 _public prototype_ `void GetWorldSpacePoint(size_t FaceNumber, size_t CornerNumber, openvdb::Vec3d& pos) const;` — Return position for polygon (face number) n and vertex (corner number) v
- L374 _public prototype_ `const FMeshMergeData& GetMeshMergeData(uint32 Idx) const;` — Access to the FMeshMergeData data elements in the array.
- L377 _public prototype_ `void UpdateMaterialsID();` — Set the FMeshMergeData material into the FMeshDescription
- L444 _public prototype_ `FMeshDescriptionArrayAdapter::FRawPoly GetRawPoly(const size_t FaceNumber, int32& OutMeshIdx, int32& OutInstanceIdx, int32& OutLocalFaceNumber, const ERawPolyValues RawPolyValues = ERawPolyValues::All ) const;` — Returns a copy of the data associated with this poly in the form of a struct. @param FaceNumber          The triangle Id when treating all the meshes as a single mesh @param OutMeshIdx          The Id of the actual mesh that owns this poly @param OutInstanceIdx      The instance index, if any, or INDEX_NONE @param OutLocalFaceNumber  The Id within that mesh of this poly @param RawPolyValues       Reduce computations by specifying which values will be used from FRawPoly. @return  A copy of the raw mesh data associated with this poly.
- L454 _public prototype_ `FMeshDescriptionArrayAdapter::FRawPoly GetRawPoly(const size_t FaceNumber, const ERawPolyValues RawPolyValues = ERawPolyValues::All ) const;` — Returns a copy of the data associated with this poly in the form of a struct. @param FaceNumber          The triangle Id when treating all the meshes as a single mesh @param RawPolyValues       Reduce computations by specifying which values will be used from FRawPoly. @return  A copy of the raw mesh data associated with this poly.
- L459 _public function_ `const openvdb::math::Transform& GetTransform() const` — The transform used to map between the physical space of the mesh and the voxel space.
- L464 _public function_ `void SetTransform(const openvdb::math::Transform::Ptr Xform)`
- L471 _public function_ `const ProxyLOD::FBBox& GetBBox() const` — Axis aligned bounding box that holds all the polys mananged by this class.
- L477 _protected prototype_ `void SetupInstances(int32 MeshCount, TFunctionRef<const FInstancedMeshMergeData* (uint32 Index)> GetMeshFunction);`
- L479 _protected prototype_ `void Construct(int32 MeshCount, TFunctionRef<const FMeshMergeData* (uint32 Index)> GetMeshFunction);`
- L480 _protected prototype_ `void Construct(int32 MeshCount, TFunctionRef<const FMeshMergeData* (uint32 Index)> GetMeshFunction, TFunctionRef<int32(uint32 Index)> GetInstanceCountFunction);`
- L482 _protected prototype_ `const FMeshDescription& GetRawMesh(const size_t FaceNumber, int32& MeshIdx, int32& InstanceIdx, int32& LocalFaceNumber, const FMeshDescriptionAttributesGetter** OutAttributesGetter) const;`
- L484 _protected prototype_ `void ComputeAABB(ProxyLOD::FBBox& InOutBBox);`
- L487 _protected member_ `openvdb::math::Transform::Ptr Transform;`
- L489 _protected member_ `size_t PointCount;`
- L490 _protected member_ `size_t PolyCount;`
- L492 _protected member_ `ProxyLOD::FBBox BBox;`
- L494 _protected member_ `std::vector<size_t> PolyOffsetArray;`
- L495 _protected member_ `std::vector<FMeshDescription*> RawMeshArray;`
- L496 _protected member_ `TArray<TArray<FTransform>> InstancesTransformArray;`
- L497 _protected member_ `TArray<TArray<FMatrix>> InstancesAdjointTArray;`
- L500 _protected member_ `TArray<FMeshDescriptionAttributesGetter> RawMeshArrayData;` — Use TArray because we need SetNumUninitialized
- L502 _protected member_ `std::vector<const FMeshMergeData*> MergeDataArray;`
- L505 _protected member_ `std::vector<std::vector<FVertexInstanceID>> IndexBufferArray;` — Need to build local index buffers for each mesh because the FMeshDescription doesn't natively have the construct.

#### class `FMeshDescriptionArrayAdapter::FRawPoly`  
`class FRawPoly`  
_L386-403_
- desc: Triangle class that contains the information associated with a single triangle in an FMeshDescription. NB: The FMeshDescription is a struct of arrays, this basically converts the data for a single poly into a struct.
- L389 _public member_ `int32 MeshIdx;`
- L391 _public member_ `int32 FaceMaterialIndex;`
- L393 _public member_ `uint32 FaceSmoothingMask;`
- L394 _public member_ `FVector3f VertexPositions[3];`
- L396 _public member_ `FVector3f WedgeTangentX[3];`
- L397 _public member_ `FVector3f WedgeTangentY[3];`
- L398 _public member_ `FVector3f WedgeTangentZ[3];`
- L400 _public member_ `FVector2D WedgeTexCoords[MAX_MESH_TEXTURE_COORDS_MD][3];`
- L402 _public member_ `FColor WedgeColors[3];`

#### class `FMeshDescriptionArrayAdapter::FMeshDescriptionAttributesGetter`  
`class FMeshDescriptionAttributesGetter`  
_L405-431_
- L408 _public function_ `FMeshDescriptionAttributesGetter(const FMeshDescription* MeshDescription)`
- L423 _public member_ `TVertexAttributesConstRef<FVector3f> VertexPositions;`
- L424 _public member_ `TVertexInstanceAttributesConstRef<FVector3f> VertexInstanceNormals;`
- L425 _public member_ `TVertexInstanceAttributesConstRef<FVector3f> VertexInstanceTangents;`
- L426 _public member_ `TVertexInstanceAttributesConstRef<float> VertexInstanceBinormalSigns;`
- L427 _public member_ `TVertexInstanceAttributesConstRef<FVector4f> VertexInstanceColors;`
- L428 _public member_ `TVertexInstanceAttributesConstRef<FVector2f> VertexInstanceUVs;`
- L429 _public member_ `int32 TriangleCount;`
- L430 _public member_ `TArray<uint32> FaceSmoothingMasks;`

#### class `FClosestPolyField`  
`class FClosestPolyField`  
_L527-596_
- desc: Class that associates reference geometry (in the form of a FMeshDescriptionArrayAdapter) and a sparse index grid. In standard use, the sparse index grid will hold the Id of the closest poly to the center of each voxel in the voxel. Example use: openvdb::FloatGrid::Ptr SDFVolume; openvdb::Int32Grid::Ptr SrcPolyIndexGrid = openvdb::Int32Grid::create(); ProxyLOD::MeshArrayToSDFVolume(MeshAdapter, SDFVolume, SrcPolyIndexGrid.get()); // Create an object that allows for closest poly queries against the source mesh. FClosestPolyField::Ptr SrcReference = FClosestPolyField::create(MeshAdapter, SrcPolyIndexGrid); NB: this does not manage the life time of the underlying data.
- L531 _public typedef_ `typedef std::shared_ptr<FClosestPolyField> Ptr;`
- L532 _public typedef_ `typedef std::shared_ptr<const FClosestPolyField> ConstPtr;`
- L534 _public function_ `static ConstPtr create(const FMeshDescriptionArrayAdapter& MeshArray, const openvdb::Int32Grid::Ptr SrcPolyIndexGrid)`
- L539 _public prototype_ `FClosestPolyField(const FMeshDescriptionArrayAdapter& MeshArray, const openvdb::Int32Grid::Ptr& SrcPolyIndexGrid);`
- L541 _public prototype_ `FClosestPolyField(const FClosestPolyField& other);`
- L577 _public prototype_ `FClosestPolyField::FPolyConstAccessor GetPolyConstAccessor() const;` — For threaded work, each thread should have its own PolyConstAccessor
- L585 _public function_ `double GetVoxelSize() const` — The voxel size used to represent the closest poly grid. @return double precision size of voxel.
- L590 _public function_ `const FMeshDescriptionArrayAdapter& MeshAdapter() const` — Access to the underlying reference geometry.
- L594 _private member_ `const FMeshDescriptionArrayAdapter* RawMeshArrayAdapter;`
- L595 _private member_ `openvdb::Int32Grid::ConstPtr ClosestPolyGrid;`

#### class `FClosestPolyField::FPolyConstAccessor`  
`class FPolyConstAccessor`  
_L548-572_
- desc: Accessor into the Closest Poly Field, thread safe - but does not manage the lifetime of any of the underlying objects (Meshes or index grid)
- L551 _public prototype_ `FPolyConstAccessor(const openvdb::Int32Grid* PolyIndexGrid, const FMeshDescriptionArrayAdapter* MeshArrayAdapter);`
- L561 _public prototype_ `FMeshDescriptionArrayAdapter::FRawPoly Get(const openvdb::Vec3d& WorldPos, bool& bSuccess) const;` — Return the closest poly, also let us know if the query failed. @param WorldPos    Query location in physical space - will be snapped to a voxel center internally. @param bSuccess    On return will be 'true' if the the voxel contained valid data, 'false' otherwise. @return FRawyPoly  Stuct holding all the data associated with the closest poly in the reference geometry.
- L562 _public function_ `FMeshDescriptionArrayAdapter::FRawPoly Get(const FVector3f& WorldPos, bool& bSuccess) const`
- L568 _private member_ `const FMeshDescriptionArrayAdapter* MeshArray;`
- L569 _private member_ `openvdb::Int32Grid::ConstAccessor CAccessor;`
- L570 _private member_ `const openvdb::math::Transform* XForm;`

#### Free symbols / members of external scopes

- L57 _function_ `template <typename ValueType> void ResizeArray(TArray<ValueType>& Array, int32 Size)` — Utility to resize an array with uninitialized data. NB: this destroys any content.
- L68 _function_ `template <typename ValueType> void ResizeInializedArray(TArray<ValueType>& Array, int32 Size)` — Utility to resize an array with constructor initialized data. NB: this destroys any content.
- L248 _typedef_ `typedef TAOSMesh<FPositionNormalVertex> FAOSMesh;` — Array of structs mesh composed of vertices that are compatible with the simplifier.
- L249 _typedef_ `typedef TAOSMesh<FPositionOnlyVertex> FPosSimplifierMesh;`
- L306 _namespace_ `namespace ProxyLOD`
- L308 _typedef_ `typedef openvdb::math::BBox<openvdb::Vec3s> FBBox;` (scope `ProxyLOD`)
- L322 _prototype_ `ENUM_CLASS_FLAGS(ERawPolyValues);`
- L713 _function_ `` (scope `TAOSMesh::GetPosArray`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODMeshUtilities.h` (Private)


#### enum `ProxyLOD::ENormalComputationMethod`  
`enum class ENormalComputationMethod : uint8`  
_L16-21_
- L18 _public enumerator_ `AreaWeighted`
- L19 _public enumerator_ `AngleWeighted`
- L20 _public enumerator_ `EqualWeighted`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ProxyLOD`
- L31 _prototype_ `void ComputeVertexNormals( FVertexDataMesh& InOutMesh, const ENormalComputationMethod Method = ENormalComputationMethod::AngleWeighted);` (scope `ProxyLOD`) — Calls into the direxXMesh library to compute the per-vertex normal, by default this will weight by area. NB: this is different than computing on the raw mesh, which can result in per-index tangent space. @param InOutMesh        Vertex-based mesh which will be updated by this function with with a per-vertex normal @param Method           Determine if the normal is angle-weighted or area-weighted or equal weighted.
- L43 _prototype_ `void ComputeTangentSpace(FMeshDescription& InOutMesh, const bool bRecomputeNormals = false );` (scope `ProxyLOD`) — Uses UE code in the Mesh Utilities module to compute the tangent space The computation is a Mikk-T(angent) space version of tangent space. NB: This updates the FMeshDescription::TangentX and FMeshDescription::TangentY and optionally TangentZ. This can result in a per-wedge tangent space if the normals are split. @param InOutMesh          FMeshDescription which will be updated by this function - adding a tangent space @param bRecomputeNormals  Determine if the normal should be recomputed as well (defualt - no).
- L53 _prototype_ `void ComputeTangentSpace( FVertexDataMesh& InOutMesh, const bool bRecomputeNormals = false );` (scope `ProxyLOD`) — Calls into the direxXMesh library to compute the per-vertex tangent and bitangent, optionally recomputes the normal. NB: this is different than computing on the raw mesh, which can result in per-index tangent space. @param InOutMesh          Vertex-based which will be updated by this function - adding a tangent space @param bRecomputeNormals  Determine if the normal should be recomputed as well (defualt - no).
- L61 _prototype_ `void ComputeFaceAveragedVertexNormals( FAOSMesh& InOutMesh );` (scope `ProxyLOD`) — Simple routine for adding face-averaged vertex normals to an Array of Structs vertex-based triangle mesh. @param InOutMesh  Vertex-based array of structs mesh, face averaged normals will be added.
- L70 _prototype_ `void AddDefaultTangentSpace( FVertexDataMesh& InOutMesh );` (scope `ProxyLOD`) — Add a default tangent space that is aligned with the coordinate axes :(1, 0, 0), (0, 1, 0), (0, 0, 1) to a vertex data mesh. NB: This tangent space really has nothing to do with the actual geometry of the mesh! @param InOutMesh  Vertex-based mesh to which we add the default tangent space.
- L78 _prototype_ `void AddNormals( FAOSMesh& InOutMesh );` (scope `ProxyLOD`) — Simple routine for adding face-averaged vertex normals to an Array of Structs vertex-based triangle mesh. @param InOutMesh  Vertex-based array of structs mesh, face averaged normals will be added.
- L79 _prototype_ `void AddNormals( TAOSMesh<FPositionOnlyVertex>& InOutMesh);` (scope `ProxyLOD`)
- L89 _prototype_ `int VerifyAdjacency(const uint32* EdgeAdjacentFaceArray, const uint32 NumEdgeAdjacentFaces);` (scope `ProxyLOD`) — Testing function using for debugging.  Verifies that if A is adjacent to B, then B is adjacent to A. Returns the number of failure cases ( should be zero!) @param  EdgeAdjacentFaceArray  Each element in the array corresponds to the edge of a triangle and holds index of the adjacent exterior face. @param  NumEdgeAdjacentFaces   Length of EdgeAdjacentFaceArray
- L100 _prototype_ `void SplitHardAngles(const float HardDegrees, FVertexDataMesh& InOutMesh);` (scope `ProxyLOD`) — Splits vertices along hard edges (as defined by the difference in face normals). NB: When a vertex is split, all the data is copied to the duplicate vertices - including any tangent space data. In general you will want to compute vertex normals and tangent space after doing this. @param HardAngleDegrees    The hard angle threshold, in degrees, used to determine if the vertices on an edge should be split. @param InOutMesh           The mesh that may be altered by the
- L115 _prototype_ `void SplitHardAngles(const float HardAngleRadians, const TArray<FVector3f>& FaceNormals, const int32 NumVerts, TArray<uint32>& Indices, std::vector<uint32_t>& AdditionalVertices);` (scope `ProxyLOD`) — Alters the connectivity to split vertices along hard edges (as defined by the difference in face normals). @param HardAngleRadians    The hard angle threshold, in radians, used to determine if the vertices on an edge should be split. @param FaceNormals         Pointer to array of face normals.  This is assumed to be of length NumIndices / 3. @param NumVerts            Total number of verts.  Usually this will be one more than the max of the Indices[] array. @param Indices             The index buffer.  Contents but not length maybe changed on return! @param AdditionalVertices  On return An array that maps old vertices to new ones (i.e. need to add Vertex[NumVerts + i] as a copy of VertexId = AdditionVertices[i] )
- L129 _prototype_ `void SplitVertices(FVertexDataMesh& InOutMesh, const std::vector<uint32_t>& dupVerts);` (scope `ProxyLOD`) — Splits vertices in the InOutMesh according to the mapping provided by the dupVerts array This assumes that the index buffer has already been updated to reflect the new vertices. @param InOutMesh           The mesh to be altered. @param dupVerts            A mapping of new vertices to old. If N = Number of vertices on input, the resulting mesh will have N + dupVerts.size()  verts. The vertices are duplicated with the following rule. Vertex[N + d] = Vertex[dupVert[d]]
- L134 _prototype_ `void CacheNormals(FVertexDataMesh& InMesh);` (scope `ProxyLOD`) — Copy the data in the member Normal Array to the memeber TransferNormal Array
- L146 _prototype_ `int32 CorrectCollapsedWalls( FMeshDescription& InOutMeshDescription, const float LengthScale);` (scope `ProxyLOD`) — Very thin walls can develop mesh interpenetration (opposing wall surfaces meet) during simplification.  This can produce rendering artifacts ( related to distance field shadows and ao). @param InOutMesh    Mesh that may have collapsed walls. This function attempts to slightly separate interpenetrating faces with opposing normals. @param LengthScale  Used to in a heuristic to determine the distance to move interpenetrating verts. @return  Number of detected inter-penetrations of opposing faced polys.
- L148 _prototype_ `int32 CorrectCollapsedWalls( FVertexDataMesh& InOutMesh, const float LengthScale );` (scope `ProxyLOD`)
- L151 _prototype_ `FBoxSphereBounds GetBounds(const FVertexDataMesh& InMesh);` (scope `ProxyLOD`)
- L152 _prototype_ `double GetWorldSpaceArea(const FVertexDataMesh& InMesh);` (scope `ProxyLOD`)
- L170 _prototype_ `void TestUniqueVertexes(const FMixedPolyMesh& InMesh);` (scope `ProxyLOD`) — Test to insure that no two vertexes share the same position. NB: Debugging function that does a checkslow. @param  InMesh  Mesh to test
- L171 _prototype_ `void TestUniqueVertexes(const FAOSMesh& InMesh);` (scope `ProxyLOD`)
- L182 _prototype_ `void ColorPartitions(FMeshDescription& InOutMesh, const std::vector<uint32>& PartitionArray );` (scope `ProxyLOD`) — Add vertex (or wedge) colors according to the partition assigned to each face by the PartitionArray. NB: The partition array must have an entry for each face.  PartitionArray[FaceID] = PartitionId @param InOutMesh       Mesh to be colored. @param PartitionArray  Maps each face to a partition.
- L183 _prototype_ `void ColorPartitions( FVertexDataMesh& InMesh, const std::vector<uint32>& PartitionArray );` (scope `ProxyLOD`)
- L191 _prototype_ `void AddWedgeColors(FMeshDescription& InOutMesh );` (scope `ProxyLOD`) — Simply color wedge colors according to index number. @param InOutMesh  Mesh to be colored.
- L200 _prototype_ `void ComputeBogusTangentAndBiTangent(FVertexDataMesh& InOutMesh);` (scope `ProxyLOD`) — Add a default tangent and bi tangent  aligned with the coordinate axes :(1, 0, 0), (0, 1, 0) to a mesh. NB: This tangent space really has nothing to do with the actual geometry of the mesh! @param InOutMesh  Vertex-based mesh to which we add the tangent and bitangent
- L209 _prototype_ `void ComputeBogusNormalTangentAndBiTangent(FVertexDataMesh& InOutMesh);` (scope `ProxyLOD`) — Add a default tangent space that is aligned with the coordinate axes :(1, 0, 0), (0, 1, 0), (0, 0, 1) to a vertex data mesh. NB: This tangent space really has nothing to do with the actual geometry of the mesh! @param InOutMesh  Vertex-based mesh to which we add the default tangent space.
- L217 _prototype_ `void MakeCube(FAOSMesh& OutMesh, float Length);` (scope `ProxyLOD`) — Make a cube, with side length "Length" and min/max corners at (0,0,0)  (L, L, L) @param OutMesh  On return holds the desired cube. @param Length   The length of a side of the cube.
- L218 _prototype_ `void MakeCube(TAOSMesh<FPositionOnlyVertex>& OutMesh, float Length);` (scope `ProxyLOD`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODOpenVDB.h` (Private)


#### Free symbols / members of external scopes

- L19 _macro_ `#define M_PI 3.14159265358979323846`
- L20 _macro_ `#define LOCAL_M_PI 1`
- L24 _macro_ `#define M_PI_2 1.57079632679489661923 // pi/2`
- L25 _macro_ `#define LOCAL_M_PI_2 1`
- L28 _macro_ `#define BOOST_ALLOW_DEPRECATED_HEADERS`

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODParallelSimplifier.h` (Private)


#### struct `__anoncb0d9cee0111::TCoAlignment`  
`template <typename VertexType> struct TCoAlignment`  
_L99-100_
- desc: Trait used to encode the defined limit of co-aligned faces when simplifing. A collapse that would causes the distance between two adjacent faces normals to be more than the CoAlignment will be penalized. NB: This is currently not being used, and the MeshSimplyElements.h has a hard-coded limit of 90-degrees. The TSimpTri<T>::ReplaceVertexIsValid() API needs to be extended to take the critical dot-product value.
- L105 _public member_ `constexpr static float Value = 0.f;` — 90 degrees

#### struct `__anoncb0d9cee0111::TCoAlignment`  
`template<> struct TCoAlignment<FPositionNormalVertex>`  
_L103-106_
- L105 _public member_ `constexpr static float Value = 0.f;` — 90 degrees

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ProxyLOD`
- L35 _prototype_ `template <typename TerminationCriterionType> static float SimplifyMesh( const TerminationCriterionType& Terminator, FAOSMesh& InOutMesh, TArray<int32>* OutSeamVertexArray = NULL);` (scope `ProxyLOD`) — Replaces the input mesh with a simplified mesh. Uses edge-collapse quadric-error based mesh simplification. The stopping criterion for mesh simplification is controlled by the Terminator struct TerminatorInterface { // Returns true if the simplification should terminate. // numTris - current number in the mesh // error   - quadric error of the next edge to collapse. bool operator()(const int32 numTris, float error); } @param  Terminator            Provides a stopping criterion for the simplification. @param  InOutMesh             The mesh to simplify and on return the simplified mesh. @param  OutSeamVertexArray    Optional pointer to array that will capture Ids of the vertices in the simplified mesh that are on mesh boundaries. @return  the max square error of an edge collapsed.
- L56 _prototype_ `void PartitionAndSimplifyMesh( const FBBox& SrcBBox, const float MinFractionToRetain, const float MaxFeatureCost, const int32 NumPartitions, FAOSMesh& InOutMesh);` (scope `ProxyLOD`) — Replaces the input mesh with a simplified mesh. Uses edge-collapse quadric-error based mesh simplification. The stopping criterion for mesh simplification derived from the MinFractionToRetain and MaxFeatureCost. ( 1 ) Partitions the mesh into NumPartitions, locks the vertices (and edges) on the partition boundaries and simplifies. ( 2 ) Merges the simplified meshes back to a single mesh. @param  SrcBBox               Spatial region that will be partitioned into NumPartitions along the major axis. @param  MinFractionToRetain   Fraction of original geometry to retain. Used in stopping criterion. @param  MaxFeatureCost        Limit to the error allowed when simplifying.  Used in stopping criterion. @param  InOutMesh             The mesh to simplify and on return the simplified mesh.
- L80 _prototype_ `void ParallelSimplifyMesh( const FClosestPolyField& SrcPolyField, const float MinFractionToRatain, const float MaxFeatureCost, FAOSMesh& InOutMesh);` (scope `ProxyLOD`) — Replaces the input mesh with a simplified mesh. Uses edge-collapse quadric-error based mesh simplification. The stopping criterion for mesh simplification derived from the MinFractionToRetain and MaxFeatureCost. This uses a fixed parallelism strategy with four waves of simplification. each retaining a smaller percentage of polys.  The majority of the work is done by first (higher) partition wave with subsequent waves cleaning up the seams that resulted from previous waves. @param  SrcPolyField          Container that holds the original (pre-voxelization / iso-surface extraction) used to help determine the target number of triangles for the simplifier. @param  MinFractionToRetain   Fraction of original geometry to retain. Used in stopping criterion. @param  MaxFeatureCost        Limit to the error allowed when simplifying.  Used in stopping criterion. @param  InOutMesh             The mesh to simplify and on return the simplified mesh.
- L89 _namespace_ `namespace (anonymous)`
- L112 _function_ `template <typename VertexType> static float CannonicalFeatureCost(float LenghtScale)` (scope `__anoncb0d9cee0111`) — Code used in testing the feature cost of simplifying an already perfect cube of a given size.
- L124 _function_ `template <typename TerminationCriterionType> static inline float ProxyLOD::SimplifyMesh(const TerminationCriterionType& Terminator, FAOSMesh& InOutMesh, TArray<int32>* SeamVertexArray)` (scope `ProxyLOD`)
- L128 _typedef_ `typedef FAOSMesh SimplifierMeshType;` (scope `ProxyLOD::SimplifyMesh`)
- L129 _typedef_ `typedef ProxyLOD::FQuadricMeshSimplifier FMeshSimplifier;` (scope `ProxyLOD::SimplifyMesh`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODQuadric.h` (Private)


#### class `ProxyLOD::FQuadric`  
`class FQuadric`  
_L142-174_
- desc: Error quadric for position only
- L145 _public function_ `FQuadric()`
- L148 _public prototype_ `FQuadric(const FVector& p0, const FVector& p1, const FVector& p2);` — Quadric for triangle
- L150 _public prototype_ `FQuadric(const FVector& p0, const FVector& p1, const FVector& faceNormal, const float edgeWeight);` — Quadric for boundary edge
- L152 _public prototype_ `void Zero();`
- L154 _public prototype_ `FQuadric& operator+=(const FQuadric& q);`
- L157 _public prototype_ `float Evaluate(const FVector& p) const;` — Evaluate error at point
- L159 _public member_ `double nxx;`
- L160 _public member_ `double nyy;`
- L161 _public member_ `double nzz;`
- L163 _public member_ `double nxy;`
- L164 _public member_ `double nxz;`
- L165 _public member_ `double nyz;`
- L167 _public member_ `double dnx;`
- L168 _public member_ `double dny;`
- L169 _public member_ `double dnz;`
- L171 _public member_ `double d2;`
- L173 _public member_ `double a;`
- L176 _function_ `inline FQuadric::FQuadric(const FVector& fp0, const FVector& fp1, const FVector& fp2)`
- L248 _function_ `inline FQuadric::FQuadric(const FVector& fp0, const FVector& fp1, const FVector& faceNormal, const float edgeWeight)`
- L311 _function_ `inline void FQuadric::Zero()`
- L330 _function_ `inline FQuadric& FQuadric::operator+=(const FQuadric& q)`
- L351 _function_ `inline float FQuadric::Evaluate(const FVector& Point) const`

#### class `ProxyLOD::TQuadricAttr`  
`template< uint32 NumAttributes > class TQuadricAttr`  
_L405-451_
- desc: Error quadric including attributes
- L408 _public function_ `TQuadricAttr()`
- L409 _public prototype_ `TQuadricAttr( const FVector& p0, const FVector& p1, const FVector& p2, const float* a0, const float* a1, const float* a2, const float* AttributeWeights );`
- L415 _public prototype_ `void Zero();`
- L417 _public prototype_ `TQuadricAttr< NumAttributes >& operator+=(const FQuadric& q);`
- L418 _public prototype_ `TQuadricAttr< NumAttributes >& operator+=(const TQuadricAttr< NumAttributes >& q);`
- L421 _public prototype_ `float Evaluate(const FVector& Point, const float* Attributes, const float* AttributeWeights) const;` — Evaluate error at point with attributes and weights
- L424 _public prototype_ `void CalcAttributes(const FVector& Point, float* Attributes, const float* AttributeWeights) const;` — Calculate attributes for point
- L426 _public member_ `double nxx;`
- L427 _public member_ `double nyy;`
- L428 _public member_ `double nzz;`
- L430 _public member_ `double nxy;`
- L431 _public member_ `double nxz;`
- L432 _public member_ `double nyz;`
- L434 _public member_ `double dnx;`
- L435 _public member_ `double dny;`
- L436 _public member_ `double dnz;`
- L438 _public member_ `double d2;`
- L440 _public member_ `double g[NumAttributes][3];`
- L441 _public member_ `double d[NumAttributes];`
- L443 _public member_ `double a;`
- L446 _public member_ `double nvx;`
- L447 _public member_ `double nvy;`
- L448 _public member_ `double nvz;`
- L449 _public member_ `double dv;`
- L454 _function_ `template< uint32 NumAttributes > inline TQuadricAttr< NumAttributes >::TQuadricAttr( const FVector& fp0, const FVector& fp1, const FVector& fp2, const float* attr0, const float* attr1, const float* attr2, const float* AttributeWeights)`
- L619 _function_ `template< uint32 NumAttributes > inline void TQuadricAttr< NumAttributes >::Zero()`
- L654 _function_ `template< uint32 NumAttributes > inline TQuadricAttr< NumAttributes >& TQuadricAttr< NumAttributes >::operator+=(const FQuadric& q)`
- L676 _function_ `template< uint32 NumAttributes > inline TQuadricAttr< NumAttributes >& TQuadricAttr< NumAttributes >::operator+=(const TQuadricAttr< NumAttributes >& q)`
- L713 _function_ `template< uint32 NumAttributes > inline float TQuadricAttr< NumAttributes >::Evaluate(const FVector& Point, const float* Attributes, const float* AttributeWeights) const`
- L789 _function_ `template< uint32 NumAttributes > inline void TQuadricAttr< NumAttributes >::CalcAttributes(const FVector& Point, float* Attributes, const float* AttributeWeights) const`

#### class `ProxyLOD::TQuadricAttrOptimizer`  
`template< uint32 NumAttributes > class TQuadricAttrOptimizer`  
_L811-854_
- L814 _public prototype_ `TQuadricAttrOptimizer();`
- L816 _public prototype_ `void AddQuadric(const FQuadric& q);`
- L817 _public prototype_ `void AddQuadric(const TQuadricAttr< NumAttributes >& q);`
- L820 _public prototype_ `bool Optimize(FVector& p) const;` — Find optimal point for minimal error
- L823 _private member_ `double nxx;`
- L824 _private member_ `double nyy;`
- L825 _private member_ `double nzz;`
- L827 _private member_ `double nxy;`
- L828 _private member_ `double nxz;`
- L829 _private member_ `double nyz;`
- L831 _private member_ `double dnx;`
- L832 _private member_ `double dny;`
- L833 _private member_ `double dnz;`
- L835 _private member_ `double a;`
- L838 _private member_ `double nvx;`
- L839 _private member_ `double nvy;`
- L840 _private member_ `double nvz;`
- L841 _private member_ `double dv;`
- L844 _private member_ `double BBtxx;`
- L845 _private member_ `double BBtyy;`
- L846 _private member_ `double BBtzz;`
- L847 _private member_ `double BBtxy;`
- L848 _private member_ `double BBtxz;`
- L849 _private member_ `double BBtyz;`
- L851 _private member_ `double Bdx;`
- L852 _private member_ `double Bdy;`
- L853 _private member_ `double Bdz;`
- L857 _function_ `template< uint32 NumAttributes > inline TQuadricAttrOptimizer< NumAttributes >::TQuadricAttrOptimizer()`
- L893 _function_ `template< uint32 NumAttributes > inline void TQuadricAttrOptimizer< NumAttributes >::AddQuadric(const FQuadric& q)`
- L911 _function_ `template< uint32 NumAttributes > inline void TQuadricAttrOptimizer< NumAttributes >::AddQuadric(const TQuadricAttr< NumAttributes >& q)`
- L956 _function_ `template< uint32 NumAttributes > inline bool TQuadricAttrOptimizer< NumAttributes >::Optimize(FVector& Point) const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define SINGULAR_QUADRIC_DET 1e-8`
- L13 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogProxyQuadric, Log, All);`
- L16 _macro_ `#define PROXYLOD_WEIGHT_BY_AREA 1`
- L17 _macro_ `#define PROXYLOD_VOLUME_CONSTRAINT 1`
- L19 _namespace_ `namespace ProxyLOD`
- L23 _function_ `static FORCEINLINE void CalcGradient(double* __restrict GradMatrix, float a0, float a1, float a2, double OutGrad[4])` (scope `ProxyLOD`)
- L33 _function_ `static FORCEINLINE double NormalizeSelf(double(&V)[3])` (scope `ProxyLOD`)
- L46 _function_ `static FORCEINLINE double NormalizeSelf(double& Vx, double& Vy, double& Vz)` (scope `ProxyLOD`)
- L59 _function_ `static bool CalcGradientMatrix(const double(&p0)[3], const double(&p1)[3], const double(&p2)[3], const double(&n)[3], double* __restrict OutGradMatrix)` (scope `ProxyLOD`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODRasterizer.h` (Private)


#### class `ProxyLOD::FRasterizerData`  
`class FRasterizerData`  
_L46-66_
- desc: Class to be used as a per-texel data type. A grid of this data type is used to map locations (i.e. texels) in the texture atlas to positions on the corresponding mesh. Records TriangleID, Signed Distance and Barycentric Coords.
- L50 _public function_ `FRasterizerData()`
- L52 _public function_ `FRasterizerData(const FRasterizerData& other) : SignedDistance(other.SignedDistance), TriangleId(other.TriangleId)`
- L60 _public member_ `double SignedDistance = std::numeric_limits<double>::max();`
- L61 _public member_ `int32 TriangleId = -1;`
- L65 _public member_ `DArray3d BarycentricCoords = { 0., 0., 0. };`

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace ProxyLOD`
- L76 _typedef_ `typedef TGrid<FRasterizerData> FRasterGrid;` (scope `ProxyLOD`) — A grid used to map locations (i.e. texels) in the texture atlas to positions on the corresponding mesh. By convention, those texels that fall outside of all UV space triangles will store the Id of the closest triangle and the distance to that triangle.
- L94 _prototype_ `FRasterGrid::Ptr RasterizeTriangles(const FVertexDataMesh& TriangleMesh, const FTextureAtlasDesc& TextureAtlasDesc, const int32 Padding, const int32 SuperSampleCount = 1);` (scope `ProxyLOD`) — Raterize the UVs from the input TriangleMesh into a 2d grid. The cells of the resulting grid may be put in correspondence with texels in a texture. @param TriangleMesh      Mesh with well defined UVs ( TriangleMesh.UVs ) @param TextureAtlasDesc  A description of the texture atlas used in the proxylod pipeline Primarily used to define the shape (IMax, JMax) of the resulting 2d Grid. @param Padding           In grid cells.  The bounding box for a UV triangle can be padded when rasterizing the triangle into the 2d grid. @param SuperSampleCount  Scales the TextureAtlas.Size to produce the RasterGrid.Size(). E.g. if   TextureAtlas.Size = 10,10 and SuperSampleCount = 4 then RasterGid.Size() = 20,20 @return Two-Dimensional grid of FRasterizerData used to map grid cells to mesh triangles and UV-barycenteric coords within the triangle.
- L109 _prototype_ `void DebugVertexAndTextureColors(FMeshDescription& InOutRawMesh, const ProxyLOD::FRasterGrid& InUVGrid, FFlattenMaterial& OutMaterial);` (scope `ProxyLOD`) — A Debug function that adds wedge colors to the input RawMesh and uses the texel map for the UVs of that RawMesh to make a material that holds the Barycentric-averaged vertex colors at each texel. It is assumed that UVGrid is the restult of rasterizing the UV triangles of the raw mesh. @param InOutRawMesh  Mesh with UVs - on return, wedge colors will have been added to the mesh @param InUVGrid      Rasterization of the UV triangles of the InOutGrid. @param OutMaterial   Material that, on return has the Barycenteric-averaged vertex colors.
- L114 _typedef_ `typedef TGrid<FLinearColor> FLinearColorGrid;` (scope `ProxyLOD`) — Two dimensional grid access to a TArray holding FLinearColor.
- L134 _prototype_ `bool DilateGrid(FLinearColorGrid& InOutRasterGrid, TGrid<int32>& InOutTopologyGrid);` (scope `ProxyLOD`) — This function performs a single step of color dilation, where previously marked "valid" cells in the input RasterGrid allow their values to spread to neighboring, "invalid" cells. On return, previously invalid cells that had at least one valid neighbor will be filled with the average value of valid neighbors and the Topology grid will be updated to indicate the new (valid) state of such cells. TopologyGrid(i, j) .ne. 0 then RasterGrid(i, j) is assumed to have a valid value. NB:  @param InOutToplogyGrid must have the same shape as @param InOutRasterGrid @param InOutRasterGrid     A 2d grid of linear colors, with valid values in a subset of grid cells. @param InOutTopologyGrid   Grid that implicitly labels RasterGrid cells as valid or invalid. @return Bool value indicating if any grid cells were actually updated during the Dilate

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODSimplifier.h` (Private)


#### class `ProxyLOD::TQuadricCache`  
`template <typename QuadricType> class TQuadricCache`  
_L35-120_
- desc: Cache to manage quadrics for the quadric mesh reduction.
- L39 _public prototype_ `TQuadricCache(int32 NumSVerts, int32 NumSTris);`
- L48 _public prototype_ `void RegisterCache(const SimpVertType* VertOffset, const SimpTriType* TriOffset);` — Associate the cache with the simplifier vert and triangle arrays. This must be done before the cache can be used. @param VertOffset  Pointer to the array of verts used by the simplifier @param TriOffset   Pointer to the array of Tris  used by the simplifier.
- L61 _public prototype_ `template <typename TriQuadricFatoryType> QuadricType GetQuadric(SimpVertType* v, const TriQuadricFatoryType& TriQuadricFactory);` — Get the Quadric. If the quadric for the requested SimplfierVert is out of date (dirty) then use the supplied TriQuadricFactor functor to compute a new quadric (and add it to the cache) QuadricType  TriQuadricFactor(SimpTriType& Tri); @param v                  The vert @param TriQuadricFactor   Method to compute new quadric from a triangle
- L75 _public prototype_ `template <typename EdgeQuadricFatoryType> ProxyLOD::FQuadric GetEdgeQuadric(SimpVertType* v, const EdgeQuadricFatoryType& EdgeQuadricFatory);` — Get the Edge Quadric. If the edge quadric for the requested SimplfierVert is out of date (dirty) then use the supplied EdgeQuadricFatory functor to compute a new quadric (and add it to the cache) FQuadric  EdgeQuadricFatory(v->GetPos(), vert->GetPos(), face->GetNormal()); @param v                  The vert @param EdgeQuadricFatory   Method to compute new quadric from a triangle
- L81 _public prototype_ `void DirtyVertQuadric(const SimpVertType* v);` — Mark the associated vertex quadric as dirty in the cache.
- L86 _public prototype_ `void DirtyTriQuadric(const SimpTriType* tri);` — Mark the associated triangle quadric as dirty in the cache.
- L91 _public prototype_ `void DirtEdgeQuadric(const SimpVertType* v);` — Mark the associated edge quadric as dirty in the cache.
- L95 _private prototype_ `uint32 GetVertIndex(const SimpVertType* vert) const;`
- L97 _private prototype_ `uint32 GetTriIndex(const SimpTriType* tri) const;`
- L103 _private prototype_ `TQuadricCache();`
- L107 _private member_ `TBitArray<> VertQuadricsValid;`
- L108 _private member_ `TArray< QuadricType > VertQuadrics;`
- L110 _private member_ `TBitArray<> TriQuadricsValid;`
- L111 _private member_ `TArray< QuadricType > TriQuadrics;`
- L113 _private member_ `TBitArray<> EdgeQuadricsValid;`
- L114 _private member_ `TArray< ProxyLOD::FQuadric > EdgeQuadrics;`
- L118 _private member_ `const SimpVertType* sVerts = NULL;`
- L119 _private member_ `const SimpTriType* sTris = NULL;`
- L690 _function_ `template <typename QuadricType > TQuadricCache< QuadricType >::TQuadricCache(int32 NumSVerts, int32 NumSTris)`
- L704 _function_ `template <typename QuadricType> void TQuadricCache< QuadricType>::RegisterCache(const SimpVertType* VertOffset, const SimpTriType* TriOffset)`
- L715 _function_ `template <typename QuadricType> template <typename TriQuadricFatoryType> QuadricType TQuadricCache< QuadricType>::GetQuadric(SimpVertType* v, const TriQuadricFatoryType& TriQuadricFactory)`
- L756 _function_ `template <typename QuadricType> template <typename EdgeQuadricFatoryType> ProxyLOD::FQuadric TQuadricCache< QuadricType>::GetEdgeQuadric(SimpVertType* v, const EdgeQuadricFatoryType& EdgeQuadricFatory)`
- L808 _function_ `template <typename QuadricType> FORCEINLINE void TQuadricCache< QuadricType>::DirtyVertQuadric(const SimpVertType* v)`
- L814 _function_ `template <typename QuadricType> FORCEINLINE void TQuadricCache< QuadricType>::DirtyTriQuadric(const SimpTriType* tri)`
- L820 _function_ `template <typename QuadricType> FORCEINLINE void TQuadricCache< QuadricType>::DirtEdgeQuadric(const SimpVertType* v)`
- L826 _function_ `template <typename QuadricType> FORCEINLINE uint32 TQuadricCache< QuadricType>::GetVertIndex(const SimpVertType* vert) const`
- L833 _function_ `template <typename QuadricType> FORCEINLINE uint32 TQuadricCache< QuadricType>::GetTriIndex(const SimpTriType* tri) const`

#### struct `ProxyLOD::VertToQuadricTrait`  
`template <typename VertType> struct VertToQuadricTrait`  
_L128-131_
- L130 _public typedef_ `typedef TQuadricAttr< VertType::NumAttributesValue > QuadricType;`
- L134 _public typedef_ `typedef ProxyLOD::FQuadric QuadricType;`

#### struct `ProxyLOD::VertToQuadricTrait`  
`template<> struct VertToQuadricTrait<FPositionOnlyVertex>`  
_L132-135_
- L130 _public typedef_ `typedef TQuadricAttr< VertType::NumAttributesValue > QuadricType;`
- L134 _public typedef_ `typedef ProxyLOD::FQuadric QuadricType;`

#### class `ProxyLOD::FSimplifierTerminatorBase`  
`class FSimplifierTerminatorBase`  
_L141-159_
- desc: Simple terminator class.  This should be expanded on to include an interrupter to allow the user to halt execution.
- L144 _public function_ `FSimplifierTerminatorBase(int32 MinTri, float MaxCost) : MaxFeatureCost(MaxCost), MinTriNumToRetain(MinTri)`
- L148 _public function_ `inline bool operator()(const int32 TriNum, const float SqrError)` — return true if the simplifier should terminate.
- L157 _public member_ `float MaxFeatureCost;`
- L158 _public member_ `int32 MinTriNumToRetain;`

#### class `ProxyLOD::FSimplifierTerminator`  
`class FSimplifierTerminator : public FSimplifierTerminatorBase`  
_L164-185_
- inherits: `FSimplifierTerminatorBase`
- desc: Termination criterion for single threaded simplifier
- L167 _public function_ `FSimplifierTerminator(int32 MinTri, int32 MaxTri, float MaxCost) : FSimplifierTerminatorBase(MinTri, MaxCost), MaxTriNumToRetain(MaxTri)`
- L171 _public function_ `inline bool operator()(const int32 TriNum, const float SqrError)` — return true if the simplifier should terminate.
- L183 _public member_ `int32 MaxTriNumToRetain;`

#### class `ProxyLOD::FQuadricMeshSimplifier`  
`class FQuadricMeshSimplifier`  
_L192-299_
- desc: Copyright (C) 2009 Nine Realms, Inc
- L194 _private typedef_ `typedef typename SimpVertType::TriIterator TriIterator;`
- L195 _private typedef_ `typedef typename VertToQuadricTrait<MeshVertType>::QuadricType QuadricType;`
- L196 _private typedef_ `typedef TQuadricCache<QuadricType> QuadricCacheType;`
- L200 _public prototype_ `FQuadricMeshSimplifier(const MeshVertType* Verts, uint32 NumVerts, const uint32* Indexes, uint32 NumIndexes, float CoAlignmentLimit);`
- L201 _public prototype_ `~FQuadricMeshSimplifier();`
- L203 _public prototype_ `void SetAttributeWeights(const float* weights);`
- L204 _public prototype_ `void SetBoundaryLocked();`
- L206 _public prototype_ `void InitCosts();`
- L209 _public prototype_ `template <typename TerminationCriterionType> float SimplifyMesh(TerminationCriterionType TerminationCriterion);`
- L211 _public function_ `int GetNumVerts() const`
- L212 _public function_ `int GetNumTris() const`
- L214 _public prototype_ `void OutputMesh(MeshVertType* Verts, uint32* Indexes, TArray<int32>* LockedVerts = NULL, int* OutNumVerts = NULL, int* OutNumIndexes = NULL) const;`
- L217 _protected prototype_ `void LockVertFlags(uint32 flag);`
- L218 _protected prototype_ `void UnlockVertFlags(uint32 flag);`
- L220 _protected prototype_ `void LockTriFlags(uint32 flag);`
- L221 _protected prototype_ `void UnlockTriFlags(uint32 flag);`
- L223 _protected prototype_ `void GatherUpdates(SimpVertType* v);`
- L225 _protected prototype_ `void GroupVerts();`
- L226 _protected prototype_ `void GroupEdges();`
- L228 _protected prototype_ `void InitVert(SimpVertType* v);`
- L230 _protected prototype_ `QuadricType GetQuadric(SimpVertType* v);`
- L231 _protected prototype_ `ProxyLOD::FQuadric GetEdgeQuadric(SimpVertType* v);`
- L234 _protected prototype_ `uint32 GetVertIndex(const SimpVertType* vert) const;` — TODO move away from pointers and remove these functions
- L235 _protected prototype_ `uint32 GetTriIndex(const SimpTriType* tri) const;`
- L236 _protected prototype_ `uint32 GetEdgeIndex(const SimpEdgeType* edge) const;`
- L238 _protected prototype_ `uint32 HashPoint(const FVector& p) const;`
- L239 _protected prototype_ `uint32 HashEdge(const SimpVertType* u, const SimpVertType* v) const;`
- L240 _protected prototype_ `SimpEdgeType* FindEdge(const SimpVertType* u, const SimpVertType* v);`
- L242 _protected prototype_ `void RemoveEdge(SimpEdgeType* edge);`
- L243 _protected prototype_ `void ReplaceEdgeVert(const SimpVertType* oldV, const SimpVertType* otherV, SimpVertType* newV);`
- L244 _protected prototype_ `void CollapseEdgeVert(const SimpVertType* oldV, const SimpVertType* otherV, SimpVertType* newV);`
- L246 _protected prototype_ `float ComputeNewVerts(SimpEdgeType* edge, TArray< MeshVertType, TInlineAllocator<16> >& newVerts);`
- L247 _protected prototype_ `FVector ComputeNewVertsPos(SimpEdgeType* edge, TArray< MeshVertType, TInlineAllocator<16> >& newVerts, TArray< QuadricType, TInlineAllocator<16> >& quadrics, ProxyLOD::FQuadric& edgeQuadric);`
- L249 _protected prototype_ `float ComputeEdgeCollapseCost(SimpEdgeType* edge);`
- L250 _protected prototype_ `void Collapse(SimpEdgeType* edge);`
- L252 _protected prototype_ `void UpdateTris();`
- L253 _protected prototype_ `void UpdateVerts();`
- L254 _protected prototype_ `void UpdateEdges();`
- L257 _protected prototype_ `int32 CountDegenerates() const;` — Included for testing.
- L259 _protected member_ `uint32 vertFlagLock;`
- L260 _protected member_ `uint32 triFlagLock;`
- L262 _protected member_ `float attributeWeights[NumAttributes+1];` — Note the +1 element is never used.
- L264 _protected member_ `SimpVertType* sVerts;`
- L265 _protected member_ `SimpTriType* sTris;`
- L267 _protected member_ `int numSVerts = 0;`
- L268 _protected member_ `int numSTris = 0;`
- L270 _protected member_ `int numVerts = 0;`
- L271 _protected member_ `int numTris = 0;`
- L276 _protected member_ `int degreeLimit = 24;` — prevent high valence verts.
- L277 _protected member_ `float degreePenalty = 100.0f;`
- L280 _protected member_ `float invalidPenalty = 1.e7;` — prevent edge folding
- L281 _protected member_ `float coAlignmentLimit = .0871557f;` — 85-degrees  -- currently not used!
- L284 _protected member_ `TArray< SimpEdgeType > edges;`
- L285 _protected member_ `FHashTable edgeHash;`
- L286 _protected member_ `FBinaryHeap<float> edgeHeap;`
- L290 _protected member_ `QuadricCacheType quadricCache;`
- L292 _protected member_ `TArray< SimpVertType* > updateVerts;`
- L293 _protected member_ `TArray< SimpTriType* > updateTris;`
- L294 _protected member_ `TArray< SimpEdgeType* > updateEdges;`
- L297 _private prototype_ `FQuadricMeshSimplifier();`
- L303 _function_ `FORCEINLINE void FQuadricMeshSimplifier::LockVertFlags(uint32 f)` — locking functions for nesting safety
- L309 _function_ `FORCEINLINE void FQuadricMeshSimplifier::UnlockVertFlags(uint32 f)`
- L314 _function_ `FORCEINLINE void FQuadricMeshSimplifier::LockTriFlags(uint32 f)`
- L320 _function_ `FORCEINLINE void FQuadricMeshSimplifier::UnlockTriFlags(uint32 f)`
- L329 _function_ `FORCEINLINE FQuadricMeshSimplifier::QuadricType FQuadricMeshSimplifier::GetQuadric(SimpVertType* v)`
- L344 _function_ `FORCEINLINE ProxyLOD::FQuadric FQuadricMeshSimplifier::GetEdgeQuadric(SimpVertType* v)`
- L357 _function_ `FORCEINLINE uint32 FQuadricMeshSimplifier::GetVertIndex(const SimpVertType* vert) const`
- L363 _function_ `FORCEINLINE uint32 FQuadricMeshSimplifier::GetTriIndex(const SimpTriType* tri) const`
- L370 _function_ `FORCEINLINE uint32 FQuadricMeshSimplifier::GetEdgeIndex(const SimpEdgeType* edge) const`
- L376 _function_ `FORCEINLINE uint32 FQuadricMeshSimplifier::HashPoint(const FVector& p) const`
- L390 _function_ `FORCEINLINE uint32 FQuadricMeshSimplifier::HashEdge(const SimpVertType* u, const SimpVertType* v) const`
- L399 _function_ `FORCEINLINE SimpEdgeType* FQuadricMeshSimplifier::FindEdge(const SimpVertType* u, const SimpVertType* v)`
- L416 _function_ `template< typename TerminationCriterionType> float FQuadricMeshSimplifier::SimplifyMesh(TerminationCriterionType TerminationCriterion)`

#### enum `ProxyLOD::FQuadricMeshSimplifier::(anonymous)`  
`enum`  
_L199-199_

#### union `ProxyLOD::FQuadricMeshSimplifier::HashPoint::(anonymous)`  
`union`  
_L378-378_

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace ProxyLOD`
- L25 _typedef_ `typedef FPositionNormalVertex MeshVertType;` (scope `ProxyLOD`) — Define the Simplifier types needed.
- L26 _typedef_ `typedef TSimpVert<MeshVertType> SimpVertType;` (scope `ProxyLOD`)
- L27 _typedef_ `typedef TSimpTri<MeshVertType> SimpTriType;` (scope `ProxyLOD`)
- L28 _typedef_ `typedef TSimpEdge<MeshVertType> SimpEdgeType;` (scope `ProxyLOD`)
- L199 _enumerator_ `enum { NumAttributes = MeshVertType::NumAttributesValue }; FQuadricMeshSimplifier(const MeshVertType* Verts, uint32 NumVerts, const uint32* Indexes, uint32 NumIndexes, float CoAlignmentLimit); ~FQuadricMeshSimplifier(); void SetAttributeWeights(const float* weights); void SetBoundaryLocked(); void InitCosts();` (scope `ProxyLOD::FQuadricMeshSimplifier::__anonab3f1ca10103`)
- L333 _function_ `` (scope `ProxyLOD::FQuadricMeshSimplifier::GetQuadric`)
- L348 _function_ `` (scope `ProxyLOD::FQuadricMeshSimplifier::GetEdgeQuadric`)
- L378 _member_ `union { float f; uint32 i; } x;` (scope `ProxyLOD::FQuadricMeshSimplifier::HashPoint::__anonab3f1ca1040a`)
- L378 _member_ `union { float f; uint32 i; } x;` (scope `ProxyLOD::FQuadricMeshSimplifier::HashPoint::__anonab3f1ca1040a`)
- L379 _member_ `union { float f; uint32 i; } y;` (scope `ProxyLOD::FQuadricMeshSimplifier::HashPoint::__anonab3f1ca1050a`)
- L379 _member_ `union { float f; uint32 i; } y;` (scope `ProxyLOD::FQuadricMeshSimplifier::HashPoint::__anonab3f1ca1050a`)
- L380 _member_ `union { float f; uint32 i; } z;` (scope `ProxyLOD::FQuadricMeshSimplifier::HashPoint::__anonab3f1ca1060a`)
- L380 _member_ `union { float f; uint32 i; } z;` (scope `ProxyLOD::FQuadricMeshSimplifier::HashPoint::__anonab3f1ca1060a`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODThreadedWrappers.h` (Private)


#### class `ProxyLOD::FTaskGroup`  
`class FTaskGroup`  
_L159-215_
- desc: Parallel Task Group - enqueues tasks to be run in parallel. This class can be constructed with FTrasGroup(false) to force single threaded behavior. NB: The syntax suggest launching (run) individual threads and joining (wait), but in fact this only enqueues task-based functors in a task manager, and there is no guarantee the tasks will actually be executed on separate threads, or even in parallel.
- L166 _public function_ `FTaskGroup()` — A task group constructed with the default constructor will enqueue tasks in the parallel task manager
- L174 _public function_ `FTaskGroup(bool Parallel) :bParallel(Parallel)` — Constructor determines if the task group will actually enqueue tasks in the parallel task manager, or simply run them consecutively. @param Parallel  - should be set to false for debugging to force single threaded behavior.
- L186 _public prototype_ `template <typename FunctorType> void Run(const FunctorType& Functor);` — Enqueue a functor in the task manager. NB: The functor will directly run if this task group was constructed with Parallel=false; @param Functor  - task to run.
- L196 _public prototype_ `template <typename FunctorType> void RunAndWait(const FunctorType& Functor);` — Run the functor on the current thread and wait for any other tasks enqueued by this task group to finish. NB: The functor will directly run if this task group was constructed with Parallel=false; @param Functor  - task to run.
- L203 _public function_ `void Wait()` — Wait for all tasks enqueued by this task group to finish. NB: No op if this task group was constructed with Parallel=false;
- L213 _private member_ `bool bParallel = true;`
- L214 _private member_ `tbb::task_group TBBTaskGroup;`
- L218 _function_ `template <typename FunctorType> void FTaskGroup::Run(const FunctorType& Functor)`
- L239 _function_ `template <typename FunctorType> void FTaskGroup::RunAndWait(const FunctorType& Functor)`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace ProxyLOD`
- L41 _typedef_ `typedef tbb::blocked_range<int32> FIntRange;` (scope `ProxyLOD`) — Splittable Range Types for parallel loops. NB: to satisfy load balancing needs, the parallel loop-based algorithms can split the range of an item of work to make smaller tasks.
- L42 _typedef_ `typedef tbb::blocked_range<uint32> FUIntRange;` (scope `ProxyLOD`)
- L43 _typedef_ `typedef tbb::blocked_range2d<int32> FIntRange2d;` (scope `ProxyLOD`)
- L76 _function_ `template <typename RangeType, typename FunctorType> void Parallel_For(const RangeType& Range, const FunctorType& Functor, const bool bParallel = true)` (scope `ProxyLOD`) — Range-based parallel for that supports internal range splitting.  The work may be split into multiple tasks. Example:  Data transformation of an array. TArray<float>  SrcArray; ... // target for data transformation TArray<float>  DstArray; // prep for parallel write Resize(DstArray, SrcArray.Num); ... auto Functor = [&DstArray, &SrcArray](const FIntRange& Range)->void { for (int i = Range.start(), I = Range.end(); i < I; ++i ) { DstArray[i] = SomeOpperation( SrcArray[i] ); } }; Parallel_For(FIntRange(0, SrcArray.Num), Functor); @param Range      RangeType(start, end) describes the range of the for loop @param Functor    Functor with Functor(const RangeType& range) signature performs sub-section of the for loop. @param bParallel  Bool to control parallel vs single threaded (default true).
- L84 _function_ `` (scope `ProxyLOD::Parallel_For`)
- L129 _function_ `template <typename RangeType, typename ValueType, typename FunctorType, typename ReduceFunctorType> ValueType Parallel_Reduce(const RangeType& Range, const ValueType& IdentityValue, const FunctorType& Functor, const ReduceFunctorType& ReduceFunctor, const bool bParallel = true)` (scope `ProxyLOD`) — Range-based reduction that supports internal range splitting. The work may be split into multiple tasks. Requires a functor that works on a subset of data, and a reduction functor that merges the results of multiple subsets. Example:  To sum all the numbers in an array of floats TArray<float>  MyArray; ... auto Functor = [&MyArray](const FIntRange& Range, float CurrentSum)->float { for (int i = Range.start(), I = Range.end(); i < I; ++i ) { CurrentSum += MyArray[i]; } return CurrentSum; }; auto ReduceFunctor = [](float A, float B)->float { return A + B; } Sum = Parallel_Reduce(FIntRange(0, MyArray.Num), 0, Functor, ReduceFunctor); @param Range          RangeType(start, end) describes the range of the work @param Functor        Functor(const RangeType& range, ValueType InitialValue) signature performs sub-section of the work, returns ValueType @param ReduceFunctor  ReduceFunctor(ValueType& A, ValueType& B) signature , returns value type. @param bParallel      Bool to control parallel vs single threaded (default true). @return Result of parallel reduce - of type ValueType.
- L137 _function_ `` (scope `ProxyLOD::Parallel_Reduce`)
- L226 _function_ `` (scope `ProxyLOD::FTaskGroup::Run`)
- L247 _function_ `` (scope `ProxyLOD::FTaskGroup::RunAndWait`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODTwoDTriangleUtilities.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ProxyLOD`
- L20 _typedef_ `typedef std::array<double, 2> DVec2d;` (scope `ProxyLOD`) — A double precision class that can be used as a two-dimensional vector. This is used primarily in the rasterization of UV data into a grid that can be used as a texture atlas correspondence table.
- L26 _typedef_ `typedef DVec2d DTriangle2d[3];` (scope `ProxyLOD`) — Lightweight structure that defines a double precision two-dimensional triangle using 3 DVec2ds.
- L31 _prototype_ `static double Dot(const DVec2d& V0, const DVec2d& V1);` (scope `ProxyLOD`) — Vetor-like fucnctions.
- L32 _prototype_ `static double LengthSqr(const DVec2d& V);` (scope `ProxyLOD`)
- L33 _prototype_ `static double Length(const DVec2d& V);` (scope `ProxyLOD`)
- L34 _prototype_ `static void Normalize(DVec2d& V);` (scope `ProxyLOD`)
- L35 _prototype_ `static DVec2d Scale(const double ScaleValue, const DVec2d& InV);` (scope `ProxyLOD`)
- L36 _prototype_ `static DVec2d Scale(const DVec2d& InV, const double ScaleValue);` (scope `ProxyLOD`)
- L37 _prototype_ `static DVec2d Subtract(const DVec2d& V0, const DVec2d& V1);` (scope `ProxyLOD`)
- L38 _prototype_ `static DVec2d Add(const DVec2d& V0, const DVec2d& V1);` (scope `ProxyLOD`)
- L49 _prototype_ `static void ComputeBBox(const DTriangle2d& Triangle, DVec2d& OutBBMin, DVec2d& OutBBMax);` (scope `ProxyLOD`) — Compute the axis aligned bounding box of a two-dimensional triangle.  Returned in the form of min and max corners. @param  Triangle      The input 2d triangle. @param  OutMin        Resulting Min corner @param  OutMax        Resulting Max cornner
- L61 _prototype_ `static double SqrDistanceToSegment(const DVec2d& VertA, const DVec2d& VertB, const DVec2d& Position);` (scope `ProxyLOD`) — Compute the square distance from the input Position to the line segment defined by the two vertices (A and B) @param  VertA     The start of the line segment. @param  VertB     The end of the line segment. @param  Position  Location of point from which to measure the square distance. @return The shortest distance between the location of Position and the line segment.
- L75 _prototype_ `static void SqrDistanceToSegment(const DVec2d& VertA, const DVec2d& VertB, const DVec2d& Position, DVec2d& OutProjectedPoint, double& OutDstSqr);` (scope `ProxyLOD`) — Compute the square distance to a line segment and the closest point on the segment
- L90 _prototype_ `static double ScaledDistanceToLine(const DVec2d& A, const DVec2d& B, const DVec2d& Point);` (scope `ProxyLOD`) — Compute the scaled, signed distance from the line  defined by the segment AB to the point P.  Will be positive if P is to the left of the line, and negative if to the right. This is the implicit function for a line between A and B, evaluated at Point.  The units of the result are length of the original line segment ( hence the "scaled" aspect of the result). @param   A, 2-d point that defines the start of the segment. @param   B, 2-d point that defines the end of the segment. @param   Point, location from which to measure the shortest distance. @return  Scaled, signed distance.
- L97 _function_ `static inline double ProxyLOD::Dot(const ProxyLOD::DVec2d& V0, const ProxyLOD::DVec2d& V1)` (scope `ProxyLOD`)
- L103 _function_ `static inline double ProxyLOD::LengthSqr(const DVec2d& V)` (scope `ProxyLOD`)
- L107 _function_ `static inline double ProxyLOD::Length(const DVec2d& V)` (scope `ProxyLOD`)
- L112 _function_ `static inline void ProxyLOD::Normalize(DVec2d& V)` (scope `ProxyLOD`)
- L119 _function_ `static inline ProxyLOD::DVec2d ProxyLOD::Scale(const double ScaleValue, const ProxyLOD::DVec2d& InV)` (scope `ProxyLOD`)
- L126 _function_ `static inline ProxyLOD::DVec2d ProxyLOD::Scale(const ProxyLOD::DVec2d& InV, const double ScaleValue)` (scope `ProxyLOD`)
- L131 _function_ `static inline ProxyLOD::DVec2d ProxyLOD::Subtract(const ProxyLOD::DVec2d& V0, const ProxyLOD::DVec2d& V1)` (scope `ProxyLOD`)
- L137 _function_ `static inline ProxyLOD::DVec2d ProxyLOD::Add(const ProxyLOD::DVec2d& V0, const ProxyLOD::DVec2d& V1)` (scope `ProxyLOD`)
- L143 _function_ `static inline void ProxyLOD::ComputeBBox(const ProxyLOD::DTriangle2d& Triangle, ProxyLOD::DVec2d& OutBBMin, ProxyLOD::DVec2d& OutBBMax)` (scope `ProxyLOD`)
- L161 _function_ `static inline double ProxyLOD::SqrDistanceToSegment(const ProxyLOD::DVec2d& VertA, const ProxyLOD::DVec2d& VertB, const ProxyLOD::DVec2d& Position)` (scope `ProxyLOD`)
- L205 _function_ `static inline void ProxyLOD::SqrDistanceToSegment(const ProxyLOD::DVec2d& VertA, const ProxyLOD::DVec2d& VertB, const ProxyLOD::DVec2d& Position, ProxyLOD::DVec2d& OutProjectedPoint, double& OutDstSqr)` (scope `ProxyLOD`)
- L260 _function_ `static inline double ProxyLOD::ScaledDistanceToLine(const DVec2d& A, const DVec2d& B, const DVec2d& Point)` (scope `ProxyLOD`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODVertexTypes.h` (Private)


#### class `FPositionOnlyVertex`  
`class FPositionOnlyVertex`  
_L15-98_
- desc: Class that represents the minimal vertex for the simplifier. No attributes are associated with the position. Implements the interface needed by templated simplifier code.
- L17 _private typedef_ `typedef FPositionOnlyVertex VertType;`
- L21 _public function_ `FPositionOnlyVertex()`
- L23 _public member_ `uint32 MaterialIndex = 0;`
- L24 _public member_ `FVector3f Position;`
- L26 _public function_ `FPositionOnlyVertex(const FPositionOnlyVertex& OtherVert) : MaterialIndex(OtherVert.MaterialIndex), Position(OtherVert.Position)`
- L33 _public function_ `static uint32 NumAttributes()` — Attributes are all assumed to be floats.
- L38 _public function_ `FVector3f& GetPos()` — Methods needed by the simplifier.
- L39 _public function_ `const FVector3f& GetPos() const`
- L42 _public function_ `float* GetAttributes()` — Required for the simplifier
- L43 _public function_ `const float* GetAttributes() const`
- L46 _public function_ `void Correct()` — Required for simplifier
- L49 _public function_ `bool operator==(const VertType& OtherVert) const` — Note this uses exact float compares..
- L59 _public function_ `bool operator!=(const VertType& OtherVert)`
- L64 _public function_ `VertType operator+(const VertType& OtherVert) const`
- L74 _public function_ `VertType operator-(const VertType& OtherVert) const` — NB: A-B != -(B-A) because of the material index.
- L84 _public function_ `VertType operator*(const float Scalar) const` — NB: The normal isn't unit length after this..
- L93 _public function_ `VertType operator/(const float Scalar) const`

#### enum `FPositionOnlyVertex::(anonymous)`  
`enum`  
_L19-19_
- desc: djh: this should really be 0, but the TQuadricAttrOptimizer will freakout..

#### class `FPositionNormalVertex`  
`class FPositionNormalVertex`  
_L105-195_
- desc: Simplifier vertex type that stores position and normal. Implements the interface needed by templated simplifier code.
- L107 _private typedef_ `typedef FPositionNormalVertex VertType;`
- L109 _public function_ `FPositionNormalVertex()`
- L113 _public member_ `uint32 MaterialIndex = 0;`
- L114 _public member_ `FVector3f Position;`
- L117 _public member_ `FVector3f Normal;` — ---- Attributes -------- currently just the components of the normal.
- L121 _public function_ `static uint32 NumAttributes()` — Attributes are all assumed to be floats.
- L128 _public function_ `uint32 GetMaterialIndex() const` — Methods needed by the simplifier.
- L129 _public function_ `FVector3f& GetPos()`
- L130 _public function_ `const FVector3f& GetPos() const`
- L131 _public function_ `float* GetAttributes()`
- L132 _public function_ `const float* GetAttributes() const`
- L135 _public function_ `void Correct()`
- L138 _public function_ `bool operator==(const VertType& OtherVert) const` — Note this uses exact float compares..
- L150 _public function_ `bool operator!=(const VertType& OtherVert)`
- L158 _public function_ `VertType operator+(const VertType& OtherVert) const` — NB: Addition isn't commutative since the MaterialIndex.. maybe Result.MaterialIndex = min(this->MaterialIndex, Other.MaterialIndex) would be better.
- L169 _public function_ `VertType operator-(const VertType& OtherVert) const` — NB: A-B != -(B-A) because of the material index.
- L180 _public function_ `VertType operator*(const float Scalar) const` — NB: The normal isn't unit length after this..
- L190 _public function_ `VertType operator/(const float Scalar) const`

#### enum `FPositionNormalVertex::(anonymous)`  
`enum`  
_L111-111_

#### Free symbols / members of external scopes

- L19 _enumerator_ `enum { NumAttributesValue = 0 }; FPositionOnlyVertex() {} uint32 MaterialIndex = 0; FVector3f Position; FPositionOnlyVertex(const FPositionOnlyVertex& OtherVert) :` (scope `FPositionOnlyVertex::__anon4d5bd8400103`) — djh: this should really be 0, but the TQuadricAttrOptimizer will freakout..
- L111 _enumerator_ `enum { NumAttributesValue = 3 }; uint32 MaterialIndex = 0; FVector3f Position; FVector3f Normal;` (scope `FPositionNormalVertex::__anon4d5bd8400203`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Private/ProxyLODkDOPInterface.h` (Private)


#### class `ProxyLOD::FUnitTransformDataProvider`  
`class FUnitTransformDataProvider`  
_L18-59_
- desc: Required class used by the kDOP system to account for scale and location of the geometry being stored in the acceleration structure. In our case the geometry exists in world space and no real transformation is needed.
- L21 _public typedef_ `typedef uint32 kDopIndexType;`
- L22 _public typedef_ `typedef TkDOPTree<const FUnitTransformDataProvider, uint32> kDopTreeType;`
- L24 _public function_ `FUnitTransformDataProvider( const TkDOPTree<const FUnitTransformDataProvider, kDopIndexType>& InkDopTree) : kDopTree(InkDopTree)` — Initialization constructor.
- L31 _public function_ `FORCEINLINE const TkDOPTree<const FUnitTransformDataProvider, kDopIndexType>& GetkDOPTree(void) const`
- L36 _public function_ `FORCEINLINE const FMatrix& GetLocalToWorld(void) const`
- L41 _public function_ `FORCEINLINE const FMatrix& GetWorldToLocal(void) const`
- L46 _public function_ `FORCEINLINE FMatrix GetLocalToWorldTransposeAdjoint(void) const`
- L51 _public function_ `FORCEINLINE float GetDeterminant(void) const`
- L58 _private member_ `const kDopTreeType& kDopTree;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ProxyLOD`
- L65 _typedef_ `typedef FUnitTransformDataProvider::kDopTreeType FkDOPTree;` (scope `ProxyLOD`) — Typedefs for our version of the k-dop tree and triangles.
- L66 _typedef_ `typedef FkDOPBuildCollisionTriangle<FUnitTransformDataProvider::kDopIndexType> FkDOPBuildTriangle;` (scope `ProxyLOD`)
- L78 _prototype_ `void BuildkDOPTree( const FMeshDescription& MeshDescription, FkDOPTree& kDOPTree);` (scope `ProxyLOD`) — Build the k-dop acceleration structure from various triangular mesh formats.  Only the location of the triangles is important. NB: Internally these are partially threaded. @param InMesh     Input triangle mesh @param kDOPTree   The resulting acceleration structure.
- L79 _prototype_ `void BuildkDOPTree( const FVertexDataMesh& InMesh, FkDOPTree& kDOPTree );` (scope `ProxyLOD`)
- L80 _prototype_ `void BuildkDOPTree( const FMeshDescriptionArrayAdapter& InMesh, FkDOPTree& kDOPTree);` (scope `ProxyLOD`)

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Public/IProxyLODPlugin.h` (Public)


#### class `IProxyLODMeshReduction`  
`class IProxyLODMeshReduction : public IMeshReductionModule`  
_L16-46_
- inherits: `IMeshReductionModule`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L27 _public function_ `static inline IProxyLODMeshReduction& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L42 _public function_ `virtual FString GetName() override`

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Public/ProxyLODParameterization.h` (Public)


#### class `IProxyLODParameterization`  
`class IProxyLODParameterization`  
_L12-64_
- L15 _public prototype_ `static TUniquePtr<IProxyLODParameterization> CreateTool();`
- L16 _public prototype_ `virtual ~IProxyLODParameterization()= default;`
- L18 _public prototype_ `virtual bool ParameterizeMeshDescription(FMeshDescription& MeshDescription, int32 Width, int32 Height, float GutterSpace, float Stretch, int32 ChartNum, bool bUseNormals, bool bRecomputeTangentSpace, bool bPrintDebugMessages) const = 0;`
- L52 _public prototype_ `virtual bool GenerateUVs(int32 Width, int32 Height, float GutterSpace, const TArray<FVector3f>& VertexBuffer, const TArray<int32>& IndexBuffer, const TArray<int32>& AdjacencyBuffer, TFunction<bool(float)>& Callback, TArray<FVector2D>& UVVertexBuffer, TArray<int32>& UVIndexBuffer, TArray<int32>& VertexRemapArray, float& MaxStretch, int32& NumCharts) const = 0;` — Lower-level entry point: Method that generates new UVs inconstant with the mesh defined by the VertexBuffer/IndexBuffer according to the parameters specified in the FTextureAtlasDesc The underlying code uses Isometeric approach (Iso-Charts) in UV generation. This assumes that the caller has already generated the mesh adjacency information. @param InTextureAtlasDesc   Description of the texel resolution of the desired texture atlas. @param VertexBuffer         Positions of vertices @param IndexBuffer          Triangle definitions @param AdjacencyBuffer      3 entries for each face, each entry is the face index of the face that is adjacent to the given face. -1 means no face. @param StatusCallBack       Allows for termination of the UV generation. @param UVVertexBuffer       Resulting UVs @param UVIndexBuffer        Connectivity for the UVs @param VertexRemapArray     Array that remaps the vertices split by the UV generation to the source vertices. @param MaxStretch           On Input, The maximum amount of stretch between (0 - none and 1 - any), on Output the actual max stretch used. @param MaxChartNumber       On Input Maximum number of charts required for the atlas.  If this is 0, will be parameterized solely on stretch. Note, not a hard limit - isochart will stop when a valid charting is found that is greater or equal to this number. On Output: Number of charts actually generated @return 'true' if the UV generation succeeded,  'false' if it failed.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PROXYLODMESHREDUCTION_API`

### `Plugins/Editor/ProxyLODPlugin/Source/ProxyLOD/Public/ProxyLODVolume.h` (Public)


#### class `IProxyLODVolume`  
`class IProxyLODVolume`  
_L14-63_
- L38 _public prototype_ `static TUniquePtr<IProxyLODVolume> CreateSDFVolumeFromMeshArray(const TArray<FMeshMergeData>& Geometry, float Step);` — Create OpenVDB volume from input geometry
- L39 _public prototype_ `static TUniquePtr<IProxyLODVolume> CreateSDFVolumeFromMeshArray(const TArray<FInstancedMeshMergeData>& Geometry, float Step);`
- L41 _public prototype_ `virtual ~IProxyLODVolume() = default;`
- L44 _public prototype_ `virtual double GetVoxelSize() const = 0;` — Get size of voxel cell
- L47 _public prototype_ `virtual FVector3i GetBBoxSize() const = 0;` — Get dimensions of bounding box of OpenVDB volume in multiple of size of voxel cell
- L50 _public prototype_ `virtual void CloseGaps(const double GapRadius, const int32 MaxDilations) = 0;` — Close any gap in OpenVDB volume which radius is less than given one in given maximum iteration
- L53 _public prototype_ `virtual void ConvertToRawMesh(FMeshDescription& OutRawMesh) const = 0;` — Extract iso distance 0 from OpenVDB volume as a RawMesh
- L56 _public prototype_ `virtual void ExpandNarrowBand(float ExteriorWidth, float InteriorWidth) = 0;` — Expand exterior and interior narrow band of OpenVDB volume by given amount
- L62 _public prototype_ `virtual float QueryDistance(const FVector& Point) const = 0;` — Returns distance between given point and iso distance 0 of OpenVDB volume. Note: Returned value is clamped between -'dimension of interior narrow band' and +'dimension of exterior narrow band'

#### struct `IProxyLODVolume::FVector3i`  
`struct FVector3i`  
_L18-35_
- desc: Helper class to extract dimensions in voxel size units of OpenVDB volume
- L20 _public member_ `int32 X;`
- L21 _public member_ `int32 Y;`
- L22 _public member_ `int32 Z;`
- L24 _public function_ `FVector3i(int32 InX, int32 InY, int32 InZ) : X(InX), Y(InY), Z(InZ)`
- L29 _public function_ `FORCEINLINE int32 operator[](int32 Index) const`
- L34 _public prototype_ `int32 MinIndex() const;`

#### class `IVoxelBasedCSG`  
`class IVoxelBasedCSG`  
_L68-131_
- L71 _public prototype_ `static TUniquePtr<IVoxelBasedCSG> CreateCSGTool(float VoxelSize);`
- L73 _public prototype_ `virtual ~IVoxelBasedCSG() = default;`
- L114 _public prototype_ `virtual double GetVoxelSize() const = 0;`
- L115 _public prototype_ `virtual void SetVoxelSize(double VolexSize) = 0;`
- L118 _public prototype_ `virtual FVector ComputeUnion(const TArray<IVoxelBasedCSG::FPlacedMesh>& MeshArray, FMeshDescription& ResultMesh, double Adaptivity = 0.1, double IsoSurfcae = 0.) const = 0;` — Will destroy UVs and other attributes  Returns the average location of the input meshes
- L120 _public prototype_ `virtual FVector ComputeDifference(const FPlacedMesh& PlacedMeshA, const FPlacedMesh& PlacedMeshB, FMeshDescription& ResultMesh, double Adaptivity, double IsoSurface) const = 0;`
- L121 _public prototype_ `virtual FVector ComputeIntersection(const FPlacedMesh& PlacedMeshA, const FPlacedMesh& PlacedMeshB, FMeshDescription& ResultMesh, double Adaptivity, double IsoSurface) const = 0;`
- L122 _public prototype_ `virtual FVector ComputeUnion(const FPlacedMesh& PlacedMeshA, const FPlacedMesh& PlacedMeshB, FMeshDescription& ResultMesh, double Adaptivity, double IsoSurface) const = 0;`
- L126 _public prototype_ `virtual bool ComputeUnion(IVoxelBasedCSG::FInterrupter& Interrupter, const TArray<IVoxelBasedCSG::FPlacedMesh>& MeshArray, FMeshDescription& ResultMesh, FVector& AverageTranslation, double Adaptivity, double IsoSurfcae) const = 0;` — interruptible versions. return true on success.
- L128 _public prototype_ `virtual bool ComputeDifference(IVoxelBasedCSG::FInterrupter& Interrupter, const FPlacedMesh& PlacedMeshA, const FPlacedMesh& PlacedMeshB, FMeshDescription& ResultMesh, FVector& AverageTranslation, double Adaptivity, double IsoSurface) const = 0;`
- L129 _public prototype_ `virtual bool ComputeIntersection(IVoxelBasedCSG::FInterrupter& Interrupter, const FPlacedMesh& PlacedMeshA, const FPlacedMesh& PlacedMeshB, FMeshDescription& ResultMesh, FVector& AverageTranslation, double Adaptivity, double IsoSurface) const = 0;`
- L130 _public prototype_ `virtual bool ComputeUnion(IVoxelBasedCSG::FInterrupter& Interrupter, const FPlacedMesh& PlacedMeshA, const FPlacedMesh& PlacedMeshB, FMeshDescription& ResultMesh, FVector& AverageTranslation, double Adaptivity, double IsoSurface) const = 0;`

#### class `IVoxelBasedCSG::FPlacedMesh`  
`class FPlacedMesh`  
_L75-100_
- L78 _public function_ `FPlacedMesh() : Mesh(nullptr)`
- L82 _public function_ `explicit FPlacedMesh(const FMeshDescription* MeshIn, const FTransform& TransformIn = FTransform::Identity) : Mesh(MeshIn), Transform(TransformIn)`
- L86 _public function_ `FPlacedMesh(const FPlacedMesh& other) : Mesh(other.Mesh) , Transform(other.Transform)`
- L91 _public function_ `FPlacedMesh& operator=(const FPlacedMesh& other)`
- L98 _public member_ `const FMeshDescription* Mesh;`
- L99 _public member_ `FTransform Transform;`

#### struct `IVoxelBasedCSG::FInterrupter`  
`struct FInterrupter`  
_L103-112_
- desc: the interrupter interface.
- L106 _public prototype_ `FInterrupter() = default;`
- L107 _public prototype_ `virtual ~FInterrupter() = default;`
- L109 _public function_ `virtual void start(const char* name = nullptr)` — templated openvdb code requires these functions.
- L110 _public function_ `virtual void end()`
- L111 _public function_ `virtual bool wasInterrupted(int percent = -1)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PROXYLODMESHREDUCTION_API`
