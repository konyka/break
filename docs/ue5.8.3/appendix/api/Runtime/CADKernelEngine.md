# Runtime / CADKernelEngine

- module root: `Source/Runtime/Datasmith/CADKernel/Engine`
- headers: 12; symbols: 695
- symbol kinds: class=11, delegate=1, enum=7, enumerator=44, function=63, macro=2, member=124, namespace=44, prototype=378, struct=15, typedef=5, union=1
- PrivateDependencyModuleNames: CADKernel, GeometryCore, Json, MeshConversion, MeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: Core, CoreUObject, TechSoft

### `Source/Runtime/Datasmith/CADKernel/Engine/Private/CADKernelEngineLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCADKernelEngine, Log, All)`

### `Source/Runtime/Datasmith/CADKernel/Engine/Private/CADKernelEnginePrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CADKernel` (scope `UE`)
- L21 _namespace_ `namespace MeshUtilities` (scope `UE::CADKernel`)
- L26 _namespace_ `namespace Private` (scope `UE::CADKernel`)
- L28 _prototype_ `bool Tessellate(FModel& Model, const UE::CADKernel::FTessellationContext& Context, UE::CADKernel::MeshUtilities::FMeshWrapperAbstract& MeshWrapper, bool bEmptyMesh = false);` (scope `UE::CADKernel::Private`)
- L31 _prototype_ `bool GetFaceTrimmingCurves(const UE::CADKernel::FModel& Model, const UE::CADKernel::FTopologicalFace& Face, TArray<TArray<TArray<FVector>>>& CurvesOut);` (scope `UE::CADKernel::Private`) — For future use
- L32 _prototype_ `bool GetFaceTrimming2DPolylines(const UE::CADKernel::FModel& Model, const UE::CADKernel::FTopologicalFace& Face, TArray<TArray<FVector2d>>& PolylinesOut);` (scope `UE::CADKernel::Private`)
- L33 _prototype_ `bool GetFaceTrimming3DPolylines(const UE::CADKernel::FModel& Model, const UE::CADKernel::FTopologicalFace& Face, TArray<TArray<FVector>>& PolylinesOut);` (scope `UE::CADKernel::Private`)
- L35 _prototype_ `bool AddModelMesh(const UE::CADKernel::FModelMesh& ModelMesh, UE::CADKernel::MeshUtilities::FMeshWrapperAbstract& MeshWrapper);` (scope `UE::CADKernel::Private`)

### `Source/Runtime/Datasmith/CADKernel/Engine/Private/DynamicMeshWrapper.h` (Private)


#### class `UE::CADKernel::MeshUtilities::FDynamicMeshWrapper`  
`class FDynamicMeshWrapper : public FMeshWrapperAbstract`  
_L14-92_
- inherits: `FMeshWrapperAbstract`
- L17 _public prototype_ `FDynamicMeshWrapper(const FMeshExtractionContext& InContext, UE::Geometry::FDynamicMesh3& InMesh);`
- L19 _public prototype_ `virtual void ClearMesh() override;`
- L20 _public prototype_ `virtual bool ReserveNewTriangles(int32 AdditionalTriangleCount) override;`
- L21 _public prototype_ `virtual bool SetVertices(TArray<FVector>&& Vertices) override;`
- L22 _public prototype_ `virtual bool AddNewVertices(TArray<FVector>&& Vertices) override;`
- L23 _public prototype_ `virtual bool AddTriangle(int32 GroupID, uint32 MaterialID, const FArray3i& VertexIndices, const TArrayView<FVector3f>& Normals, const TArrayView<FVector2f>& TexCoords) override;`
- L24 _public prototype_ `virtual bool StartFaceTriangles(int32 TriangleCount, const TArray<FVector3f>& Normals, const TArray<FVector2f>& TexCoords) override;`
- L25 _public prototype_ `virtual bool StartFaceTriangles(const TArrayView<FVector>& Normals, const TArrayView<FVector2d>& TexCoords) override;`
- L26 _public prototype_ `virtual bool AddFaceTriangles(const TArray<FFaceTriangle>& FaceTriangles) override;`
- L27 _public function_ `virtual bool AddFaceTriangle(const FFaceTriangle& FaceTriangle) override`
- L31 _public prototype_ `virtual void EndFaceTriangles() override;`
- L33 _public prototype_ `virtual void FinalizeMesh() override;`
- L34 _public prototype_ `virtual void AddSymmetry() override;`
- L35 _public prototype_ `virtual void RecomputeNullNormal() override;`
- L36 _public prototype_ `virtual void OrientMesh() override;`
- L37 _public prototype_ `virtual void ResolveTJunctions() override;`
- L40 _private prototype_ `void InitializeAttributes();`
- L41 _private prototype_ `void AddTriangles();`
- L42 _private prototype_ `int32 AppendTriangle(UE::Geometry::FIndex3i& VertexIDs, int32 GroupID);`
- L45 _private member_ `UE::Geometry::FDynamicMesh3& MeshOut;`
- L47 _private member_ `TMap<uint32, int32> MaterialMapping;`
- L54 _private member_ `TArray<int32> VertIDMap;` — map from DynamicMesh vertex Id to MeshDecription FVertexID. NB: due to vertex splitting, multiple DynamicMesh vertex ids may map to the same MeshDescription FVertexID. ( a vertex split is a result of reconciling non-manifold MeshDescription vertex )
- L55 _private member_ `TMap<int32, UE::Geometry::FDynamicMeshPolygroupAttribute*> LayerMapping;`
- L57 _private member_ `UE::Geometry::FDynamicMeshNormalOverlay* NormalOverlay = nullptr;`
- L58 _private member_ `UE::Geometry::FDynamicMeshMaterialAttribute* MaterialIDAttrib = nullptr;`
- L59 _private member_ `UE::Geometry::FDynamicMeshUVOverlay* UVOverlay = nullptr;`
- L60 _private member_ `UE::Geometry::FDynamicMeshColorOverlay* ColorOverlay = nullptr;`
- L61 _private member_ `UE::Geometry::FDynamicMeshNormalOverlay* TangentOverlay = nullptr;`
- L62 _private member_ `UE::Geometry::FDynamicMeshNormalOverlay* BiTangentOverlay = nullptr;`
- L63 _private member_ `int32 TangentOverlayID = INDEX_NONE;`
- L64 _private member_ `int32 BiTangentOverlayID = INDEX_NONE;`
- L65 _private member_ `int32 ColorOverlayID = INDEX_NONE;`
- L67 _private member_ `bool bNewVerticesAdded = false;`
- L68 _private member_ `int32 VertexIdOffset = 0;`
- L69 _private member_ `TArray<int32> VertexMapping;`
- L84 _private member_ `TArray<FTriangleData> TriangleDataSet;`
- L85 _private member_ `TSet<int32> GroupIDSet;`
- L86 _private member_ `TArray<FVector3f> Normals;`
- L87 _private member_ `TArray<FVector2f> TexCoords;`
- L88 _private member_ `int32 LastNormalIndex = 0;`
- L89 _private member_ `int32 MaterialIDCount = 0;`
- L91 _private member_ `bool bIsFinalized = false;`

#### struct `UE::CADKernel::MeshUtilities::FDynamicMeshWrapper::FTriangleData`  
`struct FTriangleData`  
_L71-83_
- L73 _public member_ `int32 GroupID;`
- L74 _public member_ `uint32 MaterialID;`
- L75 _public member_ `FArray3i NormalIndices;`
- L76 _public member_ `FArray3i TexCoordIndices;`
- L77 _public function_ `FTriangleData(int32 InGroupID, uint32 InMaterialID, const FArray3i& InNormalIndices, const FArray3i& InTexCoordIndices) : GroupID(InGroupID) , MaterialID(InMaterialID) , NormalIndices(InNormalIndices) , TexCoordIndices(InTexCoordIndices)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CADKernel` (scope `UE`)
- L12 _namespace_ `namespace MeshUtilities` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Engine/Private/MeshDescriptionWrapper.h` (Private)


#### class `UE::CADKernel::MeshUtilities::FMeshDescriptionWrapper`  
`class FMeshDescriptionWrapper : public FMeshWrapperAbstract`  
_L13-128_
- inherits: `FMeshWrapperAbstract`
- L16 _public prototype_ `FMeshDescriptionWrapper(const FMeshExtractionContext& InContext, FMeshDescription& InMesh);`
- L18 _public prototype_ `virtual void ClearMesh() override;`
- L19 _public prototype_ `virtual bool ReserveNewTriangles(int32 AdditionalTriangleCount) override;`
- L20 _public prototype_ `virtual bool SetVertices(TArray<FVector>&& Vertices) override;`
- L21 _public prototype_ `virtual bool AddNewVertices(TArray<FVector>&& Vertices) override;`
- L22 _public prototype_ `virtual bool AddTriangle(int32 GroupID, uint32 MaterialID, const FArray3i& VertexIndices, const TArrayView<FVector3f>& Normals, const TArrayView<FVector2f>& TexCoords) override;`
- L23 _public prototype_ `virtual bool StartFaceTriangles(int32 TriangleCount, const TArray<FVector3f>& Normals, const TArray<FVector2f>& TexCoords) override;`
- L24 _public prototype_ `virtual bool StartFaceTriangles(const TArrayView<FVector>& Normals, const TArrayView<FVector2d>& TexCoords) override;`
- L25 _public prototype_ `virtual bool AddFaceTriangles(const TArray<FFaceTriangle>& FaceTriangles) override;`
- L26 _public function_ `virtual bool AddFaceTriangle(const FFaceTriangle& FaceTriangle) override`
- L30 _public prototype_ `virtual void EndFaceTriangles() override;`
- L32 _public prototype_ `virtual void FinalizeMesh() override;`
- L33 _public prototype_ `virtual void AddSymmetry() override;`
- L34 _public prototype_ `virtual void RecomputeNullNormal() override;`
- L35 _public prototype_ `virtual void OrientMesh() override;`
- L36 _public prototype_ `virtual void ResolveTJunctions() override;`
- L70 _private typedef_ `using FVertexID3 = TMeshDescEntity<FVertexID>;`
- L71 _private typedef_ `using FVertexInstanceID3 = TMeshDescEntity<FVertexInstanceID>;`
- L73 _private function_ `FPolygonGroupID GetPolygonGroupID(uint32 MaterialID)`
- L92 _private function_ `FEdgeID FindEdge(const FVertexID& Start, const FVertexID& End, bool& bIsBoundary)` — bIsBoundary is only modified if an edge exists
- L104 _private prototype_ `bool GetVertexInstances(const FArray3i& Vertices, FVertexInstanceID3& VertexInstances);`
- L107 _private member_ `int32 VertexIndexOffset = 0;`
- L108 _private member_ `FCADKernelStaticMeshAttributes Attributes;`
- L109 _private member_ `TVertexAttributesRef<FVector3f> VertexPositions;`
- L110 _private member_ `TVertexInstanceAttributesRef<FVertexID> VertexInstanceToVertex;`
- L111 _private member_ `TVertexInstanceAttributesRef<FVector3f> VertexInstanceNormals;`
- L112 _private member_ `TVertexInstanceAttributesRef<FVector3f> VertexInstanceTangents;`
- L113 _private member_ `TVertexInstanceAttributesRef<float> VertexInstanceBinormalSigns;`
- L114 _private member_ `TVertexInstanceAttributesRef<FVector4f> VertexInstanceColors;`
- L115 _private member_ `TVertexInstanceAttributesRef<FVector2f> VertexInstanceUVs;`
- L116 _private member_ `TPolygonAttributesRef<int32> PolygonAttributes;`
- L117 _private member_ `TPolygonGroupAttributesRef<FName> PolygonGroupImportedMaterialSlotNames;`
- L119 _private member_ `bool bSelectiveExtraction = false;`
- L120 _private member_ `TMap<uint32, FPolygonGroupID> MaterialToPolygonGroupMapping;`
- L121 _private member_ `FPolygonGroupID LastPolygonGroupID = -1;`
- L122 _private member_ `TArray<FVertexID> VertexIDs;`
- L123 _private member_ `TArray<FVector3f> Normals;`
- L124 _private member_ `TArray<FVector2f> TexCoords;`
- L126 _private member_ `FMeshDescription& Mesh;`
- L127 _private member_ `bool bIsFinalized = false;`

#### struct `UE::CADKernel::MeshUtilities::FMeshDescriptionWrapper::TMeshDescEntity`  
`template<typename VertexType> struct TMeshDescEntity`  
_L40-68_
- L54 _public function_ `TMeshDescEntity()`
- L55 _public function_ `TMeshDescEntity(VertexType ValA, VertexType ValB, VertexType ValC) : A(ValA), B(ValB), C(ValC)`
- L59 _public function_ `VertexType& operator[](int Index)`
- L64 _public function_ `const VertexType& operator[](int Index) const`

#### union `UE::CADKernel::MeshUtilities::FMeshDescriptionWrapper::TMeshDescEntity::(anonymous)`  
``  
_L43-52_

#### struct `UE::CADKernel::MeshUtilities::FMeshDescriptionWrapper::TMeshDescEntity::__anonf6e70b46010a::(anonymous)`  
``  
_L45-49_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CADKernel` (scope `UE`)
- L11 _namespace_ `namespace MeshUtilities` (scope `UE::CADKernel`)
- L46 _member_ `VertexType A;` (scope `UE::CADKernel::MeshUtilities::FMeshDescriptionWrapper::TMeshDescEntity::__anonf6e70b46010a::__anonf6e70b460208`)
- L47 _member_ `VertexType B;` (scope `UE::CADKernel::MeshUtilities::FMeshDescriptionWrapper::TMeshDescEntity::__anonf6e70b46010a::__anonf6e70b460208`)
- L48 _member_ `VertexType C;` (scope `UE::CADKernel::MeshUtilities::FMeshDescriptionWrapper::TMeshDescEntity::__anonf6e70b46010a::__anonf6e70b460208`)
- L51 _member_ `VertexType ABC[3] = { INDEX_NONE, INDEX_NONE, INDEX_NONE };` (scope `UE::CADKernel::MeshUtilities::FMeshDescriptionWrapper::TMeshDescEntity::__anonf6e70b46010a`)

### `Source/Runtime/Datasmith/CADKernel/Engine/Private/MeshTopologyHelper.h` (Private)


#### struct `UE::CADKernel::MeshUtilities::FElementMetaData`  
`struct FElementMetaData`  
_L17-22_
- L19 _public member_ `uint16 Category : 4;`
- L20 _public member_ `uint16 Markers : 4;`
- L21 _public member_ `uint16 Extras : 4;`

#### enum `UE::CADKernel::MeshUtilities::EElementType`  
`enum class EElementType : uint8_t`  
_L24-34_
- L26 _public enumerator_ `Unused = 0`
- L27 _public enumerator_ `Free = 1 << 0`
- L28 _public enumerator_ `Line = 1 << 1`
- L29 _public enumerator_ `Surface = 1 << 2`
- L30 _public enumerator_ `Border = 1 << 3`
- L31 _public enumerator_ `NonManifold = 1 << 4`
- L32 _public enumerator_ `NonSurface = 1 << 5`
- L33 _public enumerator_ `Max = 1 << 7`

#### class `UE::CADKernel::MeshUtilities::FMeshTopologyHelper`  
`class FMeshTopologyHelper`  
_L37-103_
- L41 _private member_ `FMeshDescription& Mesh;`
- L43 _private member_ `TArray<EElementType> VertexTypeSet;`
- L44 _private member_ `TArray<EElementType> EdgeTypeSet;`
- L46 _private member_ `TBitArray<> VertexInstanceMarker;`
- L47 _private member_ `TBitArray<> TriangleMarkers;`
- L50 _private function_ `static int32 type_width(EElementType Type)`
- L56 _public prototype_ `FMeshTopologyHelper(FMeshDescription& InMeshDescription);`
- L57 _public prototype_ `~FMeshTopologyHelper();`
- L59 _public prototype_ `void UpdateMeshWrapper();`
- L61 _public function_ `bool IsTriangleMarked(FTriangleID Triangle) const`
- L65 _public function_ `void SetTriangleMarked(FTriangleID Triangle)`
- L70 _public function_ `EElementType GetEdgeType(FEdgeID Edge) const`
- L75 _public function_ `bool IsEdgeOfType(FEdgeID Edge, EElementType Type) const`
- L80 _public prototype_ `bool IsVertexOfType(FVertexInstanceID Vertex, EElementType Type) const;`
- L83 _public prototype_ `void GetTriangleVertexExtremities(FTriangleID Triangle, FVector& MinCorner, FVector& MaxCorner, FIntVector& HighestVertex, FIntVector& LowestVertex) const;` — Triangle
- L85 _public prototype_ `void SwapTriangleOrientation(FTriangleID Triangle);`
- L88 _public prototype_ `const FTriangleID GetOtherTriangleAtEdge(FEdgeID Edge, FTriangleID Triangle) const;` — Edge
- L95 _public prototype_ `bool GetEdgeDirectionInTriangle(FEdgeID Edge, int32 TriangleIndex) const;` — @param Edge           The edge defined by its FEdgeID to get direction in its connected triangle @param TriangleIndex  The triangle connected to the edge, 0 for the first, 1 for the second, ...
- L96 _public prototype_ `void DefineEdgeTopology(FEdgeID EdgeID);`
- L99 _public prototype_ `void SwapVertexNormal(FVertexInstanceID VertexID);` — Vertex
- L100 _public prototype_ `void GetVertexExtremities(FVertexInstanceID Vertex, FVector& MinCorner, FVector& MaxCorner, FIntVector& HighestVertex, FIntVector& LowestVertex) const;`
- L102 _public prototype_ `void DefineVertexTopologyApproximation(FVertexID VertexID);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define ELEMENT_FIRST_MARKER_MASK 0x02`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CADKernel` (scope `UE`)
- L15 _namespace_ `namespace MeshUtilities` (scope `UE::CADKernel`)

### `Source/Runtime/Datasmith/CADKernel/Engine/Private/MeshUtilities.h` (Private)


#### class `UE::CADKernel::MeshUtilities::FCADKernelStaticMeshAttributes`  
`class FCADKernelStaticMeshAttributes : public FStaticMeshAttributes`  
_L30-56_
- inherits: `FStaticMeshAttributes`
- L34 _public function_ `explicit FCADKernelStaticMeshAttributes(FMeshDescription& InMeshDescription) : FStaticMeshAttributes(InMeshDescription)`
- L36 _public prototype_ `virtual void Register(bool bKeepExistingAttribute = false) override;`
- L38 _public function_ `bool IsValid() const`
- L54 _public prototype_ `TPolygonAttributesRef<int32> GetPolygonGroups();` — Enable per-triangle integer attribute named PolyTriGroups (see ExtendedMeshAttribute::PolyTriGroups) This integer defines the identifier of the PolyTriGroup containing the triangle. In case of mesh coming from a CAD file, a PolyTriGroup is associated to a CAD topological face
- L55 _public prototype_ `TPolygonAttributesConstRef<int32> GetPolygonGroups() const;`

#### class `UE::CADKernel::MeshUtilities::FMeshWrapperAbstract`  
`class FMeshWrapperAbstract`  
_L58-178_
- L85 _public function_ `FMeshWrapperAbstract(const FMeshExtractionContext& InContext) : Context(InContext)`
- L94 _public function_ `void Complete()` — Call this method when the building of the mesh is completed. Must be called before the pointer to the child class is deleted.
- L121 _public function_ `virtual ~FMeshWrapperAbstract()`
- L123 _public prototype_ `virtual void ClearMesh() = 0;`
- L125 _public prototype_ `virtual bool SetVertices(TArray<FVector>&& Vertices) = 0;`
- L127 _public prototype_ `virtual bool AddNewVertices(TArray<FVector>&& Vertices) = 0;`
- L129 _public prototype_ `virtual bool ReserveNewTriangles(int32 AdditionalTriangleCount) = 0;`
- L134 _public prototype_ `virtual bool StartFaceTriangles(int32 TriangleCount, const TArray<FVector3f>& Normals, const TArray<FVector2f>& TexCoords) = 0;` — Expected Normals.Num() == TexCoords.Num() == 3 * TriangleCount
- L135 _public prototype_ `virtual bool StartFaceTriangles(const TArrayView<FVector>& Normals, const TArrayView<FVector2d>& TexCoords) = 0;`
- L137 _public prototype_ `virtual bool AddFaceTriangles(const TArray<FFaceTriangle>& FaceTriangles) = 0;`
- L139 _public prototype_ `virtual bool AddFaceTriangle(const FFaceTriangle& FaceTriangle) = 0;`
- L141 _public prototype_ `virtual void EndFaceTriangles() = 0;`
- L148 _public prototype_ `virtual bool AddTriangle(int32 GroupID, uint32 MaterialID, const FArray3i& VertexIndices, const TArrayView<FVector3f>& Normals, const TArrayView<FVector2f>& TexCoords) = 0;` — Normals and TexCoords array are expected to be arrays of 3 elements Each value in those arrays is associated to the vertex in VertexIndices at the same index value, 0, 1 and 2.
- L150 _public function_ `bool IsFaceGroupValid(int32 GroupID)`
- L155 _public prototype_ `static TSharedPtr<FMeshWrapperAbstract> MakeWrapper(const FMeshExtractionContext& InContext, FMeshDescription& Mesh);`
- L156 _public prototype_ `static TSharedPtr<FMeshWrapperAbstract> MakeWrapper(const FMeshExtractionContext& Context, UE::Geometry::FDynamicMesh3& Mesh);`
- L159 _protected member_ `static constexpr FArray3i Clockwise{ 0, 1, 2 };`
- L160 _protected member_ `static constexpr FArray3i CounterClockwise{ 0, 2, 1 };`
- L162 _protected member_ `const FMeshExtractionContext& Context;`
- L163 _protected member_ `bool bAreVerticesSet = false;`
- L166 _protected member_ `static constexpr double ScaleUV = 0.001;` — #cad_import: The UV scaling should be done in CADKernel
- L169 _protected prototype_ `virtual void AddSymmetry() = 0;`
- L170 _protected prototype_ `virtual void FinalizeMesh() = 0;`
- L171 _protected prototype_ `virtual void RecomputeNullNormal() = 0;`
- L172 _protected prototype_ `virtual void OrientMesh() = 0;`
- L173 _protected prototype_ `virtual void ResolveTJunctions() = 0;`
- L176 _private member_ `bool bHasFaceGroupsToSkip = false;`
- L177 _private member_ `bool bIsComplete = false;`

#### struct `UE::CADKernel::MeshUtilities::FMeshWrapperAbstract::FFaceTriangle`  
`struct FFaceTriangle`  
_L61-83_
- L63 _public member_ `int32 GroupID;`
- L64 _public member_ `uint32 MaterialID;`
- L67 _public member_ `const FArray3i VertexIndices;` — Indices referencing the array of positions set calling SetVertices or the latest call to AddNewVertices
- L70 _public member_ `const FArray3i Normals;` — Indices referencing the array of normals, Normals, set calling StartFaceTriangles.
- L73 _public member_ `const FArray3i TexCoords;` — Indices referencing the array of texture coordinates, TexCoords, set calling StartFaceTriangles.
- L75 _public function_ `FFaceTriangle(int32 InGroupID, uint32 InMaterialID, const FArray3i& InVertexIndices, const FArray3i& InNormals, const FArray3i& InTexCoords) : GroupID(InGroupID) , MaterialID(InMaterialID) , VertexIndices(InVertexIndices) , Normals(InNormals) , TexCoords(InTexCoords)`

#### class `UE::CADKernel::MeshUtilities::FMeshOperations`  
`class FMeshOperations`  
_L265-270_
- L267 _private prototype_ `static bool OrientMesh(FMeshDescription& MeshDescription);`
- L268 _private prototype_ `static void ResolveTJunctions(FMeshDescription& MeshDescription, double Tolerance);`
- L269 _private prototype_ `static void RecomputeNullNormal(FMeshDescription& MeshDescriptione);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CADKernel` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Geometry` (scope `UE`)
- L26 _typedef_ `using FArray3i = UE::Geometry::FVector3i;`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace CADKernel` (scope `UE`)
- L28 _namespace_ `namespace MeshUtilities` (scope `UE::CADKernel`)
- L180 _prototype_ `void GetExistingFaceGroups(FMeshDescription& Mesh, TSet<int32>& FaceGroupsOut);` (scope `UE::CADKernel::MeshUtilities`)
- L181 _prototype_ `void GetExistingFaceGroups(UE::Geometry::FDynamicMesh3& Mesh, TSet<int32>& FaceGroupsOut);` (scope `UE::CADKernel::MeshUtilities`)
- L184 _function_ `template<typename VecType> void ConvertVectorArray(uint8 ModelCoordSys, UE::Geometry::TDynamicVector<VecType>& Array)` (scope `UE::CADKernel::MeshUtilities`)
- L223 _function_ `template<typename Type> UE::Math::TMatrix<Type> GetSymmetricMatrix(const UE::Math::TVector<Type>& Origin, const UE::Math::TVector<Type>& Normal)` (scope `UE::CADKernel::MeshUtilities`)

### `Source/Runtime/Datasmith/CADKernel/Engine/Private/TechSoft/TechSoftUniqueObjectImpl.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L9 _namespace_ `namespace TechSoft` (scope `UE::CADKernel`)
- L37 _prototype_ `template<> void TUniqueObject<A3DAsmModelFileData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L39 _prototype_ `template<> void TUniqueObject<A3DAsmPartDefinitionData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L41 _prototype_ `template<> void TUniqueObject<A3DAsmProductOccurrenceData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L43 _prototype_ `template<> void TUniqueObject<A3DAsmProductOccurrenceDataCV5>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L45 _prototype_ `template<> void TUniqueObject<A3DAsmProductOccurrenceDataSLW>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L47 _prototype_ `template<> void TUniqueObject<A3DAsmProductOccurrenceDataNX>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L49 _prototype_ `template<> void TUniqueObject<A3DBoundingBoxData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L51 _prototype_ `template<> void TUniqueObject<A3DCopyAndAdaptBrepModelData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L53 _prototype_ `template<> void TUniqueObject<A3DCrvCircleData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L55 _prototype_ `template<> void TUniqueObject<A3DCrvCompositeData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L57 _prototype_ `template<> void TUniqueObject<A3DCrvEllipseData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L59 _prototype_ `template<> void TUniqueObject<A3DCrvHelixData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L61 _prototype_ `template<> void TUniqueObject<A3DCrvHyperbolaData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L63 _prototype_ `template<> void TUniqueObject<A3DCrvLineData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L65 _prototype_ `template<> void TUniqueObject<A3DCrvNurbsData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L67 _prototype_ `template<> void TUniqueObject<A3DCrvParabolaData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L69 _prototype_ `template<> void TUniqueObject<A3DCrvPolyLineData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L71 _prototype_ `template<> void TUniqueObject<A3DCrvTransformData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L73 _prototype_ `template<> void TUniqueObject<A3DDomainData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L75 _prototype_ `template<> void TUniqueObject<A3DGlobalData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L77 _prototype_ `template<> void TUniqueObject<A3DGraphicsData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L79 _prototype_ `template<> void TUniqueObject<A3DIntervalData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L81 _prototype_ `template<> void TUniqueObject<A3DMiscAttributeData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L83 _prototype_ `template<> void TUniqueObject<A3DMiscCartesianTransformationData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L85 _prototype_ `template<> void TUniqueObject<A3DMiscEntityReferenceData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L87 _prototype_ `template<> void TUniqueObject<A3DMiscGeneralTransformationData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L89 _prototype_ `template<> void TUniqueObject<A3DMiscMaterialPropertiesData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L91 _prototype_ `template<> void TUniqueObject<A3DMiscReferenceOnCsysItemData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L93 _prototype_ `template<> void TUniqueObject<A3DMiscReferenceOnTessData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L95 _prototype_ `template<> void TUniqueObject<A3DMiscReferenceOnTopologyData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L97 _prototype_ `template<> void TUniqueObject<A3DMiscSingleAttributeData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L99 _prototype_ `template<> void TUniqueObject<A3DRWParamsExportPrcData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L101 _prototype_ `template<> void TUniqueObject<A3DRiBrepModelData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L103 _prototype_ `template<> void TUniqueObject<A3DRiCoordinateSystemData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L105 _prototype_ `template<> void TUniqueObject<A3DRiDirectionData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L107 _prototype_ `template<> void TUniqueObject<A3DRiPolyBrepModelData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L109 _prototype_ `template<> void TUniqueObject<A3DRiRepresentationItemData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L111 _prototype_ `template<> void TUniqueObject<A3DRiSetData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L113 _prototype_ `template<> void TUniqueObject<A3DRootBaseData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L115 _prototype_ `template<> void TUniqueObject<A3DRootBaseWithGraphicsData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L117 _prototype_ `template<> void TUniqueObject<A3DRWParamsTessellationData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L119 _prototype_ `template<> void TUniqueObject<A3DSewOptionsData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L121 _prototype_ `template<> void TUniqueObject<A3DSurfBlend01Data>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L123 _prototype_ `template<> void TUniqueObject<A3DSurfBlend02Data>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L125 _prototype_ `template<> void TUniqueObject<A3DSurfBlend03Data>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L127 _prototype_ `template<> void TUniqueObject<A3DSurfConeData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L129 _prototype_ `template<> void TUniqueObject<A3DSurfCylinderData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L131 _prototype_ `template<> void TUniqueObject<A3DSurfCylindricalData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L133 _prototype_ `template<> void TUniqueObject<A3DSurfExtrusionData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L135 _prototype_ `template<> void TUniqueObject<A3DSurfFromCurvesData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L137 _prototype_ `template<> void TUniqueObject<A3DSurfNurbsData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L139 _prototype_ `template<> void TUniqueObject<A3DSurfPipeData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L141 _prototype_ `template<> void TUniqueObject<A3DSurfPlaneData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L143 _prototype_ `template<> void TUniqueObject<A3DSurfRevolutionData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L145 _prototype_ `template<> void TUniqueObject<A3DSurfRuledData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L147 _prototype_ `template<> void TUniqueObject<A3DSurfSphereData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L149 _prototype_ `template<> void TUniqueObject<A3DSurfTorusData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L151 _prototype_ `template<> void TUniqueObject<A3DTess3DData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L153 _prototype_ `template<> void TUniqueObject<A3DTessBaseData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L155 _prototype_ `template<> void TUniqueObject<A3DTopoBodyData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L157 _prototype_ `template<> void TUniqueObject<A3DTopoBrepDataData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L159 _prototype_ `template<> void TUniqueObject<A3DTopoCoEdgeData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L161 _prototype_ `template<> void TUniqueObject<A3DTopoConnexData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L163 _prototype_ `template<> void TUniqueObject<A3DTopoContextData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L165 _prototype_ `template<> void TUniqueObject<A3DTopoEdgeData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L167 _prototype_ `template<> void TUniqueObject<A3DTopoFaceData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L169 _prototype_ `template<> void TUniqueObject<A3DTopoLoopData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L171 _prototype_ `template<> void TUniqueObject<A3DTopoShellData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L173 _prototype_ `template<> void TUniqueObject<A3DTopoUniqueVertexData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L175 _prototype_ `template<> void TUniqueObject<A3DTopoMultipleVertexData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L177 _prototype_ `template<> void TUniqueObject<A3DTopoWireEdgeData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L179 _prototype_ `template<> void TUniqueObject<A3DVector2dData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L181 _prototype_ `template<> void TUniqueObject<A3DVector3dData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L184 _prototype_ `template<> A3DStatus TUniqueObject<A3DAsmModelFileData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L186 _prototype_ `template<> A3DStatus TUniqueObject<A3DAsmPartDefinitionData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L188 _prototype_ `template<> A3DStatus TUniqueObject<A3DAsmProductOccurrenceData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L190 _prototype_ `template<> A3DStatus TUniqueObject<A3DAsmProductOccurrenceDataCV5>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L192 _prototype_ `template<> A3DStatus TUniqueObject<A3DAsmProductOccurrenceDataSLW>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L194 _prototype_ `template<> A3DStatus TUniqueObject<A3DAsmProductOccurrenceDataNX>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L196 _prototype_ `template<> A3DStatus TUniqueObject<A3DBoundingBoxData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L198 _prototype_ `template<> A3DStatus TUniqueObject<A3DCopyAndAdaptBrepModelData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L200 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvCircleData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L202 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvCompositeData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L204 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvEllipseData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L206 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvHelixData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L208 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvHyperbolaData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L210 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvLineData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L212 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvNurbsData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L214 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvParabolaData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L216 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvPolyLineData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L218 _prototype_ `template<> A3DStatus TUniqueObject<A3DCrvTransformData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L220 _prototype_ `template<> A3DStatus TUniqueObject<A3DDomainData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L222 _prototype_ `template<> A3DStatus TUniqueObject<A3DGlobalData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L224 _prototype_ `template<> A3DStatus TUniqueObject<A3DGraphicsData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L226 _prototype_ `template<> A3DStatus TUniqueObject<A3DIntervalData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L228 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscAttributeData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L230 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscCartesianTransformationData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L232 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscEntityReferenceData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L234 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscGeneralTransformationData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L236 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscMaterialPropertiesData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L238 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscReferenceOnCsysItemData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L240 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscReferenceOnTessData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L242 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscReferenceOnTopologyData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L244 _prototype_ `template<> A3DStatus TUniqueObject<A3DMiscSingleAttributeData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L246 _prototype_ `template<> A3DStatus TUniqueObject<A3DRWParamsExportPrcData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L248 _prototype_ `template<> A3DStatus TUniqueObject<A3DRiBrepModelData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L250 _prototype_ `template<> A3DStatus TUniqueObject<A3DRiCoordinateSystemData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L252 _prototype_ `template<> A3DStatus TUniqueObject<A3DRiDirectionData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L254 _prototype_ `template<> A3DStatus TUniqueObject<A3DRiPolyBrepModelData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L256 _prototype_ `template<> A3DStatus TUniqueObject<A3DRiRepresentationItemData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L258 _prototype_ `template<> A3DStatus TUniqueObject<A3DRiSetData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L260 _prototype_ `template<> A3DStatus TUniqueObject<A3DRootBaseData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L262 _prototype_ `template<> A3DStatus TUniqueObject<A3DRootBaseWithGraphicsData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L264 _prototype_ `template<> A3DStatus TUniqueObject<A3DRWParamsTessellationData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L266 _prototype_ `template<> A3DStatus TUniqueObject<A3DSewOptionsData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L268 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfBlend01Data>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L270 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfBlend02Data>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L272 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfBlend03Data>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L274 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfConeData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L276 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfCylinderData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L278 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfCylindricalData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L280 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfExtrusionData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L282 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfFromCurvesData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L284 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfNurbsData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L286 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfPipeData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L288 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfPlaneData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L290 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfRevolutionData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L292 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfRuledData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L294 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfSphereData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L296 _prototype_ `template<> A3DStatus TUniqueObject<A3DSurfTorusData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L298 _prototype_ `template<> A3DStatus TUniqueObject<A3DTess3DData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L300 _prototype_ `template<> A3DStatus TUniqueObject<A3DTessBaseData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L302 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoBodyData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L304 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoBrepDataData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L306 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoCoEdgeData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L308 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoConnexData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L310 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoContextData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L312 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoEdgeData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L314 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoFaceData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L316 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoLoopData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L318 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoShellData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L320 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoUniqueVertexData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L322 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoMultipleVertexData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L324 _prototype_ `template<> A3DStatus TUniqueObject<A3DTopoWireEdgeData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L326 _prototype_ `template<> A3DStatus TUniqueObject<A3DVector2dData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L328 _prototype_ `template<> A3DStatus TUniqueObject<A3DVector3dData>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L331 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DAsmModelFileData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L333 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DAsmPartDefinitionData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L335 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DAsmProductOccurrenceData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L337 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DAsmProductOccurrenceDataCV5>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L339 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DAsmProductOccurrenceDataSLW>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L341 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DAsmProductOccurrenceDataNX>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L343 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DBoundingBoxData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L345 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCopyAndAdaptBrepModelData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L347 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvCircleData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L349 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvCompositeData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L351 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvEllipseData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L353 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvHelixData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L355 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvHyperbolaData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L357 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvLineData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L359 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvNurbsData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L361 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvParabolaData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L363 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvPolyLineData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L365 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DCrvTransformData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L367 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DDomainData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L369 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DGlobalData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L371 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DGraphicsData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L373 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DIntervalData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L375 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscAttributeData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L377 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscCartesianTransformationData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L379 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscEntityReferenceData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L381 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscGeneralTransformationData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L383 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscMaterialPropertiesData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L385 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscReferenceOnCsysItemData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L387 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscReferenceOnTessData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L389 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscReferenceOnTopologyData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L391 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DMiscSingleAttributeData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L393 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRWParamsExportPrcData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L395 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRiBrepModelData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L397 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRiCoordinateSystemData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L399 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRiDirectionData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L401 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRiPolyBrepModelData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L403 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRiRepresentationItemData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L405 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRiSetData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L407 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRootBaseData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L409 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRootBaseWithGraphicsData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L411 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DRWParamsTessellationData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L413 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSewOptionsData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L415 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfBlend01Data>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L417 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfBlend02Data>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L419 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfBlend03Data>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L421 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfConeData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L423 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfCylinderData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L425 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfCylindricalData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L427 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfExtrusionData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L429 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfFromCurvesData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L431 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfNurbsData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L433 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfPipeData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L435 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfPlaneData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L437 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfRevolutionData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L439 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfRuledData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L441 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfSphereData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L443 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DSurfTorusData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L445 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTess3DData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L447 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTessBaseData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L449 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoBodyData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L451 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoBrepDataData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L453 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoCoEdgeData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L455 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoConnexData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L457 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoContextData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L459 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoEdgeData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L461 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoFaceData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L463 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoLoopData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L465 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoShellData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L467 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoUniqueVertexData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L469 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoMultipleVertexData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L471 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DTopoWireEdgeData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L473 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DVector2dData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L475 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DVector3dData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L480 _prototype_ `template<> void TUniqueObjectFromIndex<A3DGraphMaterialData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L482 _prototype_ `template<> void TUniqueObjectFromIndex<A3DGraphPictureData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L484 _prototype_ `template<> void TUniqueObjectFromIndex<A3DGraphRgbColorData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L486 _prototype_ `template<> void TUniqueObjectFromIndex<A3DGraphStyleData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L488 _prototype_ `template<> void TUniqueObjectFromIndex<A3DGraphTextureApplicationData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L490 _prototype_ `template<> void TUniqueObjectFromIndex<A3DGraphTextureDefinitionData>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L493 _prototype_ `template<> A3DStatus TUniqueObjectFromIndex<A3DGraphMaterialData>::GetData(const uint32 InEntityIndex);` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L495 _prototype_ `template<> A3DStatus TUniqueObjectFromIndex<A3DGraphPictureData>::GetData(const uint32 InEntityIndex);` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L497 _prototype_ `template<> A3DStatus TUniqueObjectFromIndex<A3DGraphRgbColorData>::GetData(const uint32 InEntityIndex);` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L499 _prototype_ `template<> A3DStatus TUniqueObjectFromIndex<A3DGraphStyleData>::GetData(const uint32 InEntityIndex);` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L501 _prototype_ `template<> A3DStatus TUniqueObjectFromIndex<A3DGraphTextureApplicationData>::GetData(const uint32 InEntityIndex);` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L503 _prototype_ `template<> A3DStatus TUniqueObjectFromIndex<A3DGraphTextureDefinitionData>::GetData(const uint32 InEntityIndex);` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L506 _prototype_ `template<> uint32 TUniqueObjectFromIndex<A3DGraphMaterialData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L508 _prototype_ `template<> uint32 TUniqueObjectFromIndex<A3DGraphPictureData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L510 _prototype_ `template<> uint32 TUniqueObjectFromIndex<A3DGraphRgbColorData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L512 _prototype_ `template<> uint32 TUniqueObjectFromIndex<A3DGraphStyleData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L514 _prototype_ `template<> uint32 TUniqueObjectFromIndex<A3DGraphTextureApplicationData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L516 _prototype_ `template<> uint32 TUniqueObjectFromIndex<A3DGraphTextureDefinitionData>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObjectFromIndex`)
- L521 _prototype_ `template<> void TUniqueObject<A3DUTF8Char*>::InitializeData();` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L523 _prototype_ `template<> A3DStatus TUniqueObject<A3DUTF8Char*>::GetData(const A3DEntity* InEntityPtr);` (scope `UE::CADKernel::TechSoft::TUniqueObject`)
- L525 _prototype_ `template<> const A3DEntity* TUniqueObject<A3DUTF8Char*>::GetDefaultIndexerValue() const;` (scope `UE::CADKernel::TechSoft::TUniqueObject`)

### `Source/Runtime/Datasmith/CADKernel/Engine/Private/TechSoft/TechSoftUtilities.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CADKernel` (scope `UE`)
- L16 _namespace_ `namespace MeshUtilities` (scope `UE::CADKernel`)
- L23 _namespace_ `namespace TechSoftUtilities` (scope `UE::CADKernel`)
- L25 _prototype_ `bool Tessellate(A3DRiRepresentationItem* Representation, const FTessellationContext& Settings, MeshUtilities::FMeshWrapperAbstract& MeshWrapper, bool bEmptyMesh = false);` (scope `UE::CADKernel::TechSoftUtilities`)
- L26 _prototype_ `bool TessellateRepresentation(A3DRiRepresentationItem* Representation, const FCADKernelTessellationSettings& Settings);` (scope `UE::CADKernel::TechSoftUtilities`)
- L27 _prototype_ `bool AddRepresentation(A3DRiRepresentationItem* Representation, double ModelUnitToMeter, MeshUtilities::FMeshWrapperAbstract& MeshWrapper);` (scope `UE::CADKernel::TechSoftUtilities`)
- L28 _prototype_ `FVector2d GetUVScale(const A3DTopoFace* TopoFace, double TextureUnit);` (scope `UE::CADKernel::TechSoftUtilities`)
- L29 _prototype_ `TSharedPtr<FJsonObject> GetJsonObject(A3DEntity* Entity, bool bIsLegacy = false);` (scope `UE::CADKernel::TechSoftUtilities`)
- L38 _prototype_ `bool SewBReps(const TArray<A3DRiBrepModel*>& BRepsIn, double Tolerance, TArray<A3DRiBrepModel*>& BRepsOut);` (scope `UE::CADKernel::TechSoftUtilities`) — Sew the in coming BReps together @param: BRepsIn @param: Tolerance is file's unit with which to operate the sewing @param: BRepsOut

### `Source/Runtime/Datasmith/CADKernel/Engine/Public/CADKernelEngine.h` (Public)


#### class `UE::CADKernel::FCADKernelUtilities`  
`class FCADKernelUtilities`  
_L31-45_
- L34 _public prototype_ `static bool Save(TSharedPtr<UE::CADKernel::FModel>& Model, const FString& FilePath);`
- L35 _public prototype_ `static bool Load(TSharedPtr<UE::CADKernel::FModel>& Model, const FString& FilePath);`
- L36 _public prototype_ `static bool Tessellate(UE::CADKernel::FModel& Model, const FTessellationContext& Context, FMeshDescription& MeshOut, bool bSkipDeletedFaces = false, bool bEmptyMesh = false);`
- L37 _public prototype_ `static bool Tessellate(UE::CADKernel::FModel& Model, const FTessellationContext& Context, UE::Geometry::FDynamicMesh3& MeshOut, bool bSkipDeletedFaces = false, bool bEmptyMesh = false);`
- L40 _public prototype_ `static void ApplyExtractionContext(const FMeshExtractionContext& Context, FMeshDescription& MeshInOut);` — Note: Meshes are expected to be in their native coordinates system and unit
- L41 _public prototype_ `static void ApplyExtractionContext(const FMeshExtractionContext& Context, UE::Geometry::FDynamicMesh3& MeshInOut);`
- L43 _public prototype_ `static void RegisterAttributes(FMeshDescription& MeshInOut, bool bKeepExistingAttribute = false);` — Set the proper attributes for FMeshDescription created from CAD data.
- L44 _public prototype_ `static bool ToRawData(TSharedPtr<UE::CADKernel::FModel>& Model, TArray<uint8>& RawDataOut);`

#### enum `UE::CADKernel::ECADFormat`  
`enum class ECADFormat`  
_L47-70_
- L49 _public enumerator_ `ACIS`
- L50 _public enumerator_ `AUTOCAD`
- L51 _public enumerator_ `CATIA`
- L52 _public enumerator_ `CATIA_CGR`
- L53 _public enumerator_ `CATIA_3DXML`
- L54 _public enumerator_ `CATIAV4`
- L55 _public enumerator_ `CREO`
- L56 _public enumerator_ `DWG`
- L57 _public enumerator_ `DGN`
- L58 _public enumerator_ `TECHSOFT`
- L59 _public enumerator_ `IFC`
- L60 _public enumerator_ `IGES`
- L61 _public enumerator_ `INVENTOR`
- L62 _public enumerator_ `JT`
- L63 _public enumerator_ `N_X`
- L64 _public enumerator_ `MICROSTATION`
- L65 _public enumerator_ `PARASOLID`
- L66 _public enumerator_ `SOLID_EDGE`
- L67 _public enumerator_ `SOLIDWORKS`
- L68 _public enumerator_ `STEP`
- L69 _public enumerator_ `OTHER`

#### class `UE::CADKernel::FTechSoftLibrary`  
`class FTechSoftLibrary`  
_L73-160_
- L76 _public prototype_ `static const TCHAR* GetVersion();`
- L77 _public prototype_ `static bool Initialize();`
- L78 _public function_ `static bool IsInitialized()`
- L82 _public prototype_ `static A3DRiRepresentationItem* CreateRIBRep(const TArray<A3DTopoShell*>& TopoShells);`
- L84 _public prototype_ `static A3DTopoEdge* CreateTopoEdge();`
- L85 _public prototype_ `static A3DTopoEdge* CreateTopoEdge(A3DTopoEdgeData& TopoEdgeData);`
- L86 _public prototype_ `static A3DTopoFace* CreateTopoFaceWithNaturalLoop(A3DSurfBase* CarrierSurface);`
- L87 _public prototype_ `static A3DTopoShell* CreateTopoShell(A3DTopoShellData& TopoShellData);`
- L88 _public prototype_ `static A3DTopoFace* CreateTopoFace(A3DTopoFaceData& TopoFaceData);`
- L89 _public prototype_ `static A3DTopoLoop* CreateTopoLoop(A3DTopoLoopData& TopoLoopData);`
- L90 _public prototype_ `static A3DTopoCoEdge* CreateTopoCoEdge(A3DTopoCoEdgeData& TopoCoEdgeData);`
- L91 _public prototype_ `static A3DStatus LinkCoEdges(A3DTopoCoEdge* CoEdgePtr, A3DTopoCoEdge* NeighbourCoEdgePtr);`
- L93 _public prototype_ `static A3DCrvNurbs* CreateTrimNurbsCurve(A3DCrvNurbs* CurveNurbsPtr, double UMin, double UMax, bool bIs2D);`
- L94 _public prototype_ `static A3DSurfNurbs* CreateSurfaceNurbs(A3DSurfNurbsData& SurfaceNurbsData);`
- L95 _public prototype_ `static A3DCrvNurbs* CreateCurveNurbs(A3DCrvNurbsData& CurveNurbsData);`
- L97 _public prototype_ `static A3DStatus SetEntityGraphicsColor(A3DEntity* InEntity, FColor Color);`
- L100 _public prototype_ `static A3DAsmModelFile* LoadModelFileFromFile(const A3DImport& Import, const TCHAR* Filename);`
- L101 _public prototype_ `static A3DAsmModelFile* LoadModelFile(const TCHAR* Filename, const FTechSoftImportOverrides& LoadOverrides, FString& OutReason);`
- L103 _public prototype_ `static A3DAsmModelFile* LoadModelFileFromPrcFile(const A3DUTF8Char* CADFileName, A3DRWParamsPrcReadHelper** ReadHelper);`
- L104 _public prototype_ `static A3DStatus AdaptBRepInModelFile(A3DAsmModelFile* ModelFile, const A3DCopyAndAdaptBrepModelData& Setting, int32& ErrorCount, A3DCopyAndAdaptBrepModelErrorData** Errors);`
- L105 _public prototype_ `static A3DStatus AdaptBRepModel(A3DAsmModelFile* ModelFile, const TCHAR* Filename);`
- L106 _public prototype_ `static A3DStatus DeleteModelFile(A3DAsmModelFile* ModelFile);`
- L107 _public prototype_ `static A3DStatus DeleteEntity(A3DEntity* EntityPtr);`
- L108 _public prototype_ `static double GetModelFileUnit(const A3DAsmModelFile* ModelFile);`
- L110 _public prototype_ `static FString CleanLabel(const FString& Name);`
- L111 _public prototype_ `static void GetOccurrenceChildren(const A3DAsmProductOccurrence* Node, TArray<const A3DAsmProductOccurrence*>& OutChildren);`
- L131 _public prototype_ `static void ExtractGraphicsProperties(const A3DEntity* Entity, FGraphicsProperties& Result);`
- L142 _public prototype_ `static bool ExtractMaterial(uint32 TechSoftMaterialIndex, const A3DGraphStyleData& GraphStyleData, FMaterial& ParsedMaterial);`
- L143 _public prototype_ `static FColor GetColorAt(uint32 ColorIndex);`
- L144 _public prototype_ `static TArray<uint32> GetStylesUsedOnFaces(A3DRiBrepModel* RepresentationItem);`
- L146 _public prototype_ `static bool ParseRootBaseData(const A3DEntity* Entity, TMap<FString, FString>& MetaData, FString& UniqueID, FString& Label);`
- L147 _public prototype_ `static void TraverseAttribute(const A3DMiscAttributeData& AttributeData, TMap<FString, FString>& OutMetaData);`
- L150 _public prototype_ `static bool IsMaterialTexture(const uint32 MaterialIndex);`
- L151 _public prototype_ `static bool GetEntityType(A3DRiRepresentationItem* RepresentationItem, A3DEEntityType& Type);`
- L153 _public prototype_ `static bool IsConfigurationSet(ECADFormat Format, const A3DAsmProductOccurrence* Occurrence);`
- L154 _public prototype_ `static A3DAsmProductOccurrence* FindConfiguration(const A3DAsmProductOccurrence* ConfigurationSetOccurrencePtr, TFunctionRef<bool(A3DAsmProductOccurrenceData& ConfigurationData)> Callback);`
- L159 _private member_ `static bool bIsInitialized;`

#### struct `UE::CADKernel::FTechSoftLibrary::FGraphicsProperties`  
`struct FGraphicsProperties`  
_L113-130_
- L115 _public member_ `bool bIsRemoved = false;`
- L116 _public member_ `bool bShow = true;`
- L118 _public member_ `int32 ColorUid = 0;`
- L119 _public member_ `int32 StyleIndex = 0;`
- L128 _public member_ `EInheritance MaterialInheritance = EInheritance::Unset;`

#### enum `UE::CADKernel::FTechSoftLibrary::FGraphicsProperties::EInheritance`  
`enum class EInheritance`  
_L121-126_
- L123 _public enumerator_ `Unset`
- L124 _public enumerator_ `Father`
- L125 _public enumerator_ `Child`

#### struct `UE::CADKernel::FTechSoftLibrary::FMaterial`  
`struct FMaterial`  
_L133-140_
- L135 _public member_ `FColor Diffuse;`
- L136 _public member_ `FColor Ambient;`
- L137 _public member_ `FColor Specular;`
- L138 _public member_ `float Shininess;`
- L139 _public member_ `float Transparency = 0;`

#### class `UE::CADKernel::FTechSoftUtilities`  
`class FTechSoftUtilities`  
_L162-184_
- L170 _public prototype_ `static bool Save(const TArray<A3DRiRepresentationItem*>& Representations, const FString& FilePath, const FString& Attributes = FString());` — @param FilePath: Absolute path to the prc file to load @param bSewModel: Optional argument to force a stitching of the model @param StitchingTolerance: Optional stitching tolerance in mm
- L171 _public function_ `static bool Save(A3DRiRepresentationItem* Representation, const FString& FilePath, const FString& Attributes = FString())`
- L175 _public prototype_ `static bool Tessellate(A3DRiRepresentationItem* Representation, const FTessellationContext& Context, FMeshDescription& MeshOut, bool bSkipDeletedFaces = false, bool bEmptyMesh = false);`
- L176 _public prototype_ `static bool Tessellate(A3DRiRepresentationItem* Representation, const FTessellationContext& Context, UE::Geometry::FDynamicMesh3& MeshOut, bool bSkipDeletedFaces = false, bool bEmptyMesh = false);`
- L178 _public prototype_ `static TSharedPtr<UE::CADKernel::FModel> TechSoftToCADKernel(A3DRiRepresentationItem* Representation, double Unit, double InGeometricTolerance);`
- L180 _public prototype_ `static A3DRiRepresentationItem* CADKernelToTechSoft(TSharedPtr<UE::CADKernel::FModel>& Model);` — Limitation: Non of the implicit geometry is supported
- L181 _public prototype_ `static A3DRiRepresentationItem* GetRepresentation(const TArray<uint8>& TechSoftRawData);`
- L182 _public prototype_ `static bool ToRawData(A3DRiRepresentationItem* Representation, int32 MaterialID, TArray<uint8>& RawDataOut);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CADKernel` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace CADKernel` (scope `UE`)
- L22 _namespace_ `namespace MeshUtilities` (scope `UE::CADKernel`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace CADKernel` (scope `UE`)
- L186 _namespace_ `namespace MathUtils` (scope `UE::CADKernel`)
- L192 _function_ `inline FTransform ConvertTransform(ECADKernelModelCoordSystem SourceCoordSystem, const FTransform& LocalTransform)` (scope `UE::CADKernel::MathUtils`) — Converts a transform from a given coordinates system to UE's one UE's coordinates system is ZUp_LeftHanded
- L225 _function_ `template<typename VecType> void ConvertVectorArray(ECADKernelModelCoordSystem ModelCoordSys, TArrayView<VecType>& Array)` (scope `UE::CADKernel::MathUtils`)
- L264 _function_ `template<typename VecType> void ConvertVectorArray(uint8 ModelCoordSys, TArrayView<VecType>& Array)` (scope `UE::CADKernel::MathUtils`)
- L270 _function_ `template<typename VecType> void ConvertVectorArray(ECADKernelModelCoordSystem ModelCoordSys, TArray<VecType>& Array)` (scope `UE::CADKernel::MathUtils`)
- L277 _function_ `template<typename VecType> void ConvertVectorArray(uint8 ModelCoordSys, TArray<VecType>& Array)` (scope `UE::CADKernel::MathUtils`)
- L284 _function_ `template<typename VecType> VecType ConvertVector(ECADKernelModelCoordSystem ModelCoordSys, const VecType& V)` (scope `UE::CADKernel::MathUtils`)
- L307 _function_ `template<typename VecType> VecType ConvertVector(uint8 ModelCoordSys, const VecType& V)` (scope `UE::CADKernel::MathUtils`)

### `Source/Runtime/Datasmith/CADKernel/Engine/Public/CADKernelEngineDefinitions.h` (Public)


#### enum `ECADKernelModelCoordSystem`  
`enum class ECADKernelModelCoordSystem : uint8`  
_L10-17_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `ZUp_LeftHanded`
- L13 _public enumerator_ `ZUp_RightHanded`
- L14 _public enumerator_ `YUp_LeftHanded`
- L15 _public enumerator_ `YUp_RightHanded`
- L16 _public enumerator_ `ZUp_RightHanded_FBXLegacy`

#### enum `ECADKernelStitchingTechnique`  
`enum ECADKernelStitchingTechnique : uint8`  
_L20-25_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `StitchingNone = 0`
- L23 _public enumerator_ `StitchingHeal`
- L24 _public enumerator_ `StitchingSew`

#### enum `ECADKernelTessellator`  
`enum ECADKernelTessellator : uint8`  
_L28-32_
- reflection: `UENUM(BlueprintType)`
- L30 _public enumerator_ `CADKernel = 0`
- L31 _public enumerator_ `TechSoft`

#### struct `FCADKernelModelParameters`  
`struct FCADKernelModelParameters`  
_L35-51_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public member_ `uint8 ModelCoordSys = uint8(ECADKernelModelCoordSystem::ZUp_LeftHanded);` — `UPROPERTY()` — value from FDatasmithUtils::ECADKernelModelCoordSystem
- L44 _public member_ `float ModelUnitToCentimeter = 1.;` — `UPROPERTY()` — Model is in centimeters
- L47 _public member_ `float ScaleFactor = 1.0f;` — `UPROPERTY()`
- L49 _public function_ `bool FromJson(const FString& JsonString) const`
- L50 _public function_ `FString ToJson() const`

#### struct `FCADKernelMeshParameters`  
`struct FCADKernelMeshParameters`  
_L54-75_
- reflection: `USTRUCT(BlueprintType)`
- L59 _public member_ `bool bNeedSwapOrientation = false;` — `UPROPERTY()`
- L62 _public member_ `bool bIsSymmetric = false;` — `UPROPERTY()`
- L65 _public member_ `FVector SymmetricOrigin = FVector::ZeroVector;` — `UPROPERTY()`
- L68 _public member_ `FVector SymmetricNormal = FVector::ZeroVector;` — `UPROPERTY()`
- L71 _public member_ `float ScaleFactor = 1.0f;` — `UPROPERTY()`
- L73 _public function_ `bool FromJson(const FString& JsonString) const`
- L74 _public function_ `FString ToJson() const`

#### struct `FCADKernelTessellationSettings`  
`struct FCADKernelTessellationSettings`  
_L78-215_
- reflection: `USTRUCT(BlueprintType)`
- L82 _public function_ `FCADKernelTessellationSettings( double InChordTolerance = 0.2, double InMaxEdgeLength = 0.0, double InNormalTolerance = 20.0, ECADKernelStitchingTechnique InStitchingTechnique = ECADKernelStitchingTechnique::StitchingSew, double InGeometricTolerance = 0.001, double InStichingTolerance = 0.001, ECADKernelTessellator InTessellator = ECADKernelTessellator::CADKernel ) : ChordTolerance(InChordTolerance) , MaxEdgeLength(InMaxEdgeLength) , NormalTolerance(InNormalTolerance) , StitchingTechnique(InStitchingTechnique) , Tessellator(InTessellator) , GeometricTolerance(InGeometricTolerance) , StitchingTolerance(InStichingTolerance)`
- L109 _protected member_ `double ChordTolerance;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Geometry & Tessellation Options", meta = (Units = cm, ToolTip = "Maximum distance between any generated triangle and the original surface. Smaller values make more triangles.", ClampMin = "0.005"))` — Maximum distance between any point on a triangle generated by the tessellation process and the actual surface. The lower the value the more triangles. Default value is 0.2, minimal value is 0.005 cm.
- L118 _protected member_ `double MaxEdgeLength;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Units = cm, DisplayName = "Max Edge Length", ToolTip = "Maximum length of any edge in the generated triangles. Smaller values make more triangles.", ClampMin = "0.0"))` — Maximum length of edges of triangles generated by the tessellation process. The length is in scene/model unit. The smaller the more triangles are generated. Value of 0 means no constraint on length of edges Default value is 0 to disable this criteria, and 1. cm is its minimal value if enable.
- L127 _public member_ `double NormalTolerance;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Units = deg, ToolTip = "Maximum angle between adjacent triangles. Smaller values make more triangles.", ClampMin = "5.0", ClampMax = "90.0"))` — Maximum angle between the normal of two triangles generated by the tessellation process. The angle is expressed in degree. The smaller the more triangles are generated. Default value is 20 degrees, min value is 5 degrees.
- L138 _public member_ `TEnumAsByte<ECADKernelStitchingTechnique> StitchingTechnique;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (ToolTip = "Stitching technique applied on model before tessellation. Sewing could impact number of objects."))` — Stitching technique applied on neighboring surfaces before tessellation. None : No stitching applied. This is the default. Sewing : Connects surfaces which physically share a boundary but not topologically within a set of objects. This technique can modify the structure of the model by removing and adding objects. Healing : Connects surfaces which physically share a boundary but not topologically within an object.
- L144 _public member_ `TEnumAsByte<ECADKernelTessellator> Tessellator = ECADKernelTessellator::CADKernel;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Tooltip = "Select tessellator to use. Default to CADKernel. Disabled if TechSoft is not available.", editCondition = "bWithTechSoft == true"))` — Indicates which tessellator to use: CADKernel or TechSoft. By default it is CADKernel.
- L152 _public member_ `bool bResolveTJunctions = false;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (EditCondition = "Tessellator == ECADKernelTessellator::TechSoft", EditConditionHides, Tooltip = "If true, enables the removal of T-Junctions from the resulting mesh. Default is false."))` — T-Junctions are edge configurations where a border vertex lies on an opposing border edge. If true, the mesh is analyzed and all T-Junctions found on the mesh will be resolved. Only applicable with the TechSoft tessellator. Default is false
- L162 _protected member_ `double GeometricTolerance = 0.001;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Units = cm, ToolTip = "Tolerance used to determine if a surface should be tessellated or not."))` — Tolerance used to determine if a surface should be tessellate or not. Any surface which is narrower than the geometric tolerance in one of the iso direction will not be tessellated Value is in centimeter
- L169 _protected member_ `double StitchingTolerance = 0.001;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Geometry & Tessellation Options", meta = (Units = cm, ToolTip = "Tolerance used to determine if two surfaces should be stitched.", editCondition = "StitchingTechnique!=ECADKernelStitchingTechnique::StitchingNone"))` — Tolerance used to determine if two surfaces should be stitched. Value is in centimeter
- L178 _public member_ `double UnitMultiplier = 1.;` — `UPROPERTY()` — #cadkernel_check: Verify that this new logic is properly used everywhere.
- L181 _public member_ `bool bWithTechSoft = bWithHoops;` — `UPROPERTY(Transient, meta = (EditCondition = false, EditConditionHides))`
- L183 _public member_ `static bool bWithHoops;`
- L185 _public function_ `bool operator == (const FCADKernelTessellationSettings& Other) const`
- L196 _public function_ `uint32 GetHash() const`
- L206 _public function_ `double GetGeometricTolerance(bool bInMillimeter = false) const` — Helper functions to get geometrical values in the right unit, cm (native) or mm
- L207 _public function_ `double GetStitchingTolerance(bool bInMillimeter = false) const`
- L208 _public function_ `double GetChordTolerance(bool bInMillimeter = false) const`
- L209 _public function_ `double GetMaxEdgeLength(bool bInMillimeter = false) const`
- L211 _public function_ `bool FromJson(const FString& JsonString) const`
- L212 _public function_ `FString ToJson() const`
- L214 _public function_ `bool UseCADKernel() const`

#### enum `ECADKernelRetessellationRule`  
`enum class ECADKernelRetessellationRule : uint8`  
_L218-222_
- reflection: `UENUM()`
- L220 _public enumerator_ `AllFaces = 0`
- L221 _public enumerator_ `SkipDeletedFaces`

#### struct `FCADKernelRetessellationSettings`  
`struct FCADKernelRetessellationSettings : public FCADKernelTessellationSettings`  
_L225-243_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FCADKernelTessellationSettings`
- L229 _public function_ `FCADKernelRetessellationSettings(double InChordTolerance = 0.2f, double InMaxEdgeLength = 0.0f, double InNormalTolerance = 20.0f, ECADKernelStitchingTechnique InStitchingTechnique = ECADKernelStitchingTechnique::StitchingSew, ECADKernelRetessellationRule InRetessellationRule = ECADKernelRetessellationRule::AllFaces) : FCADKernelTessellationSettings(InChordTolerance, InMaxEdgeLength, InNormalTolerance, InStitchingTechnique) , RetessellationRule(InRetessellationRule)`
- L235 _public function_ `FCADKernelRetessellationSettings(const FCADKernelTessellationSettings& TessellationSettings, ECADKernelRetessellationRule InRetessellationRule = ECADKernelRetessellationRule::AllFaces) : FCADKernelTessellationSettings(TessellationSettings) , RetessellationRule(InRetessellationRule)`
- L242 _public member_ `ECADKernelRetessellationRule RetessellationRule = ECADKernelRetessellationRule::AllFaces;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Retessellation Settings", meta = (ToolTip = "Regenerate deleted surfaces during retesselate or ignore them"))`

#### struct `UE::CADKernel::FUnitConverter`  
`struct FUnitConverter`  
_L247-255_
- L249 _public member_ `static const double CentimeterToMillimeter;`
- L250 _public member_ `static const double MillimeterToCentimeter;`
- L251 _public member_ `static const double CentimeterToMeter;`
- L252 _public member_ `static const double MeterToCentimeter;`
- L253 _public member_ `static const double MillimeterToMeter;`
- L254 _public member_ `static const double MeterToMillimeter;`

#### struct `UE::CADKernel::FTechSoftImportOverrides`  
`struct FTechSoftImportOverrides`  
_L257-262_
- L259 _public member_ `bool bLoadGeometryOnly = true;`
- L260 _public member_ `bool bLoadLoadNoDependency = false;`
- L261 _public member_ `bool bLoadStructureOnly = false;`

#### struct `UE::CADKernel::FMeshExtractionContext`  
`struct FMeshExtractionContext`  
_L264-270_
- L266 _public member_ `FCADKernelModelParameters ModelParams;`
- L267 _public member_ `FCADKernelMeshParameters MeshParams;`
- L268 _public member_ `mutable TSet<int32> FaceGroupsToExtract;`
- L269 _public member_ `bool bResolveTJunctions = false;`

#### struct `UE::CADKernel::FTessellationContext`  
`struct FTessellationContext : public FMeshExtractionContext`  
_L272-277_
- inherits: `FMeshExtractionContext`
- L274 _public member_ `FCADKernelTessellationSettings TessellationSettings;`
- L275 _public function_ `FTessellationContext()`
- L276 _public prototype_ `FTessellationContext(const FCADKernelModelParameters& ModelParams, const FCADKernelMeshParameters& MeshParams, const FCADKernelRetessellationSettings& Settings);`

#### Free symbols / members of external scopes

- L245 _namespace_ `namespace UE`
- L245 _namespace_ `namespace CADKernel` (scope `UE`)

### `Source/Runtime/Datasmith/CADKernel/Engine/Public/TechSoftIncludes.h` (Public)


#### Free symbols / members of external scopes

- L25 _macro_ `#define WITH_HOOPS`

### `Source/Runtime/Datasmith/CADKernel/Engine/Public/TechSoftUniqueObject.h` (Public)


#### class `UE::CADKernel::TechSoft::TUniqueObjectBase`  
`template<class ObjectType, class IndexerType> class TUniqueObjectBase`  
_L31-200_
- L38 _public function_ `TUniqueObjectBase() : bDataFromTechSoft(false) , Status(A3DStatus::A3D_SUCCESS)` — Constructor of an initialized ObjectType object
- L49 _public function_ `explicit TUniqueObjectBase(IndexerType DataPtr) : bDataFromTechSoft(false)` — Constructor of an filled ObjectType object with the data of DataPtr @param DataPtr: the pointer of the data to copy
- L56 _public function_ `~TUniqueObjectBase()`
- L64 _public function_ `A3DStatus FillFrom(IndexerType EntityPtr)` — Fill the structure with the data of a new DataPtr
- L84 _public function_ `template<typename... InArgTypes> A3DStatus FillWith(A3DStatus(*Getter)(const A3DEntity*, ObjectType*, InArgTypes&&...), const A3DEntity* EntityPtr, InArgTypes&&... Args)`
- L107 _public function_ `void Reset()` — Empty the structure
- L117 _public function_ `A3DStatus GetStatus()` — Return - A3DStatus::A3D_SUCCESS if the data is filled - A3DStatus::A3D_ERROR if the data is empty
- L125 _public function_ `const bool IsValid() const` — Return true if the data is filled
- L131 _public prototype_ `TUniqueObjectBase(const TUniqueObjectBase&) = delete;` — Non-copyable
- L132 _public prototype_ `TUniqueObjectBase& operator=(const TUniqueObjectBase&) = delete;`
- L136 _public function_ `const ObjectType& operator*() const`
- L141 _public function_ `ObjectType& operator*()`
- L147 _public function_ `const ObjectType* operator->() const`
- L153 _public function_ `ObjectType* operator->()`
- L162 _public function_ `ObjectType* GetPtr()` — Return the structure pointer
- L172 _private member_ `ObjectType Data;`
- L173 _private member_ `bool bDataFromTechSoft = false;`
- L174 _private member_ `A3DStatus Status = A3DStatus::A3D_ERROR;`
- L181 _private prototype_ `IndexerType GetDefaultIndexerValue() const;` — DefaultValue is used to initialize "Data" with GetData method According to IndexerType, the value is either nullptr for const A3DEntity* either something like "A3D_DEFAULT_MATERIAL_INDEX" ((A3DUns16)-1) for uint32 @see ResetData
- L183 _private prototype_ `void InitializeData();`
- L185 _private prototype_ `A3DStatus GetData(IndexerType AsmModelFilePtr);`
- L187 _private function_ `void ResetData()`

#### class `UE::CADKernel::TechSoft::FTechSoftDefaultValue`  
`class FTechSoftDefaultValue`  
_L208-217_
- L211 _public member_ `static const uint32 Material;`
- L212 _public member_ `static const uint32 Picture;`
- L213 _public member_ `static const uint32 RgbColor;`
- L214 _public member_ `static const uint32 Style;`
- L215 _public member_ `static const uint32 TextureApplication;`
- L216 _public member_ `static const uint32 TextureDefinition;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CADKernel` (scope `UE`)
- L7 _namespace_ `namespace TechSoft` (scope `UE::CADKernel`)
- L203 _typedef_ `template<class ObjectType> using TUniqueObject = TUniqueObjectBase<ObjectType, const A3DEntity*>;` (scope `UE::CADKernel::TechSoft`)
- L206 _typedef_ `template<class ObjectType> using TUniqueObjectFromIndex = TUniqueObjectBase<ObjectType, uint32>;` (scope `UE::CADKernel::TechSoft`)
