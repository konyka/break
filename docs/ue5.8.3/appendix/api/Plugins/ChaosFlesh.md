# Plugins / ChaosFlesh

- module root: `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh`
- headers: 8; symbols: 104
- symbol kinds: class=4, function=2, macro=1, member=32, namespace=6, prototype=55, struct=1, typedef=3
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, InputCore

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh/Public/ChaosFlesh/ChaosFlesh.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFlesh, Log, All);`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh/Public/ChaosFlesh/ChaosFleshCollectionFacade.h` (Public)


#### class `Chaos::FFleshCollectionFacade`  
`class FFleshCollectionFacade`  
_L11-83_
- L13 _private member_ `const FFleshCollection& ConstCollection;`
- L14 _private member_ `FFleshCollection* Collection = nullptr;`
- L17 _public prototype_ `FFleshCollectionFacade(FFleshCollection& InCollection);`
- L19 _public prototype_ `FFleshCollectionFacade(const FFleshCollection& InCollection);`
- L22 _public prototype_ `bool IsValid() const;` — Are all the public attributes avaiable.
- L25 _public prototype_ `bool IsTetrahedronValid() const;` — Has tetrahedral attributes {Tetrahderon, Vertices}.
- L28 _public prototype_ `bool IsHierarchyValid() const;` — Has hierarchy attributes {BoneName, Transform, Parent, Child}.
- L31 _public prototype_ `bool IsGeometryValid() const;` — Has geometry attributes {TransformToGeometryIndex VertexStart VertexCount FaceStart FaceCount}.
- L34 _public prototype_ `int NumTransforms() const;` — Num of transform elements in the collection
- L37 _public prototype_ `int NumVertices() const;` — Num of vertex elements in the collection
- L40 _public prototype_ `int NumFaces() const;` — Num of face elements in the collection
- L43 _public prototype_ `int NumGeometry() const;` — Num of geometry elements in the collection
- L46 _public prototype_ `int AppendGeometry(const FFleshCollection& NewGeomerty);` — Add geometry to the collection
- L49 _public prototype_ `void GlobalMatrices(TArray<FTransform>& ComponentTransform);` — Global Matrices of the collection
- L52 _public prototype_ `FTransform3f GlobalMatrix3f(int32 InIndex);` — Single Global Matrix of index in the collection
- L56 _public prototype_ `template<class T> const TManagedArray<T>* FindAttribute(FString AttributeName, FString Group) const;` — View a Attribute on the collection
- L60 _public prototype_ `template<class T> TManagedArray<T>* ModifyAttribute(FString AttributeName, FString Group) const;` — Edit a Attribute on the collection
- L63 _public prototype_ `void ComponentSpaceVertices(TArray<FVector3f>& OutComponentSpaceVertices) const;` — All the vertices mapped into component space.
- L66 _public prototype_ `void ComponentSpaceVertices(TArray<FVector3f>& OutComponentSpaceVertices, int32 Start, int32 Count) const;` — Range of vertices mapped into component space
- L69 _public member_ `TManagedArrayAccessor<FString> BoneName;` — Public Attributes
- L70 _public member_ `TManagedArrayAccessor<FTransform3f> Transform;`
- L71 _public member_ `TManagedArrayAccessor<int32> TransformToGeometryIndex;`
- L72 _public member_ `TManagedArrayAccessor<int32> Parent;`
- L73 _public member_ `TManagedArrayAccessor< TSet<int32> > Child;`
- L74 _public member_ `TManagedArrayAccessor<int32> BoneMap;`
- L75 _public member_ `TManagedArrayAccessor<FVector3f> Vertex;`
- L76 _public member_ `TManagedArrayAccessor<FIntVector3> Indices;`
- L77 _public member_ `TManagedArrayAccessor<FIntVector4> Tetrahedron;`
- L78 _public member_ `TManagedArrayAccessor<int32> GeometryToTransformIndex;`
- L79 _public member_ `TManagedArrayAccessor<int32> VertexStart;`
- L80 _public member_ `TManagedArrayAccessor<int32> VertexCount;`
- L81 _public member_ `TManagedArrayAccessor<int32> FaceStart;`
- L82 _public member_ `TManagedArrayAccessor<int32> FaceCount;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh/Public/ChaosFlesh/ChaosFleshModule.h` (Public)


#### class `IChaosFleshModuleInterface`  
`class IChaosFleshModuleInterface : public IModuleInterface`  
_L13-15_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _macro_ `#define CHAOS_FLESH_MODULE_NAME "ChaosFlesh"`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh/Public/ChaosFlesh/FleshCollection.h` (Public)


#### class `FFleshCollection`  
`class FFleshCollection : public FTetrahedralCollection`  
_L17-48_
- inherits: `FTetrahedralCollection`
- desc: FFleshCollection (FTetrehidralCollection)
- L20 _public typedef_ `typedef FTetrahedralCollection Super;`
- L21 _public typedef_ `typedef GeometryCollection::Facades::FSelectionFacade::FSelectionKey FBindingKey;`
- L23 _public prototype_ `FFleshCollection();`
- L24 _public prototype_ `FFleshCollection(FFleshCollection&) = delete;`
- L25 _public prototype_ `FFleshCollection& operator=(const FFleshCollection&) = delete;`
- L26 _public prototype_ `FFleshCollection(FFleshCollection&&) = default;`
- L27 _public prototype_ `FFleshCollection& operator=(FFleshCollection&&) = default;`
- L32 _public prototype_ `static FFleshCollection* NewFleshCollection(const FTetrahedralCollection& Base);` — Create a GeometryCollection from Vertex and Indices arrays
- L33 _public prototype_ `static FFleshCollection* NewFleshCollection(const TArray<FVector>& Vertices, const TArray<FIntVector3>& SurfaceElements, const TArray<FIntVector4>& Elements, bool bReverseVertexOrder = true);`
- L34 _public prototype_ `static FFleshCollection* NewFleshCollection(const TArray<FVector>& Vertices, const TArray<FIntVector4>& Elements, const bool bReverseVertexOrder = true, const bool KeepInteriorFaces = false, const bool InvertFaces = false);`
- L35 _public prototype_ `static void Init(FFleshCollection* Collection, const TArray<FVector>& Vertices, const TArray<FIntVector3>& SurfaceElements, const TArray<FIntVector4>& Elements, bool bReverseVertexOrder = true);`
- L42 _public member_ `static const FName MassAttribute;` — Mass Attribute FManagedArray<float> Mass = this->FindAttribute<float>("Mass",FGeometryCollection::VerticesGroup);
- L43 _public member_ `TManagedArray<float> Mass;`
- L46 _protected prototype_ `void Construct();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L50 _function_ `inline Chaos::FChaosArchive& operator<<(Chaos::FChaosArchive& Ar, FFleshCollection& Value)`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh/Public/ChaosFlesh/FleshCollectionUtility.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ChaosFlesh`
- L12 _prototype_ `void GetTetFaces(const FIntVector4& Tet, FIntVector3& Face1, FIntVector3& Face2, FIntVector3& Face3, FIntVector3& Face4, const bool invert = false);` (scope `ChaosFlesh`)
- L13 _prototype_ `void GetSurfaceElements(const TArray<FIntVector4>& Tets, TArray<FIntVector3>& SurfaceElements, const bool KeepInteriorFaces, const bool InvertFaces = false);` (scope `ChaosFlesh`)
- L15 _prototype_ `TArray<int32> CompactSurfaceVertices(const TArray<FVector3f>& Vertices, const TArray<FIntVector3>& SurfaceElements, TArray<FVector3f>& OutVertices, TArray<FIntVector3>& OutSurfaceElements);` (scope `ChaosFlesh`) — Delete vertices that are not used in SurfaceElements and returns a new-to-old vertex map.

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh/Public/ChaosFlesh/TetrahedralCollection.h` (Public)


#### class `FTetrahedralCollection`  
`class FTetrahedralCollection : public FGeometryCollection`  
_L19-108_
- inherits: `FGeometryCollection`
- desc: FTetrahedralCollection (FGeometryCollection)
- L21 _private typedef_ `typedef FGeometryCollection Super;`
- L24 _public prototype_ `FTetrahedralCollection();`
- L25 _public prototype_ `FTetrahedralCollection(FTetrahedralCollection &) = delete;`
- L26 _public prototype_ `FTetrahedralCollection& operator=(const FTetrahedralCollection &) = delete;`
- L27 _public prototype_ `FTetrahedralCollection(FTetrahedralCollection &&) = default;`
- L28 _public prototype_ `FTetrahedralCollection& operator=(FTetrahedralCollection &&) = default;`
- L33 _public prototype_ `static FTetrahedralCollection* NewTetrahedralCollection(const TArray<FVector>& Vertices, const TArray<FIntVector3>& SurfaceElements, const TArray<FIntVector4>& Elements,bool bReverseVertexOrder = true);` — Create a GeometryCollection from Vertex and Indices arrays
- L34 _public prototype_ `static void Init(FTetrahedralCollection* Collection, const TArray<FVector>& Vertices, const TArray<FIntVector3>& SurfaceElements, const TArray<FIntVector4>& Elements, bool bReverseVertexOrder = true);`
- L36 _public prototype_ `void UpdateBoundingBox();`
- L38 _public prototype_ `void AppendCollection(const FTetrahedralCollection& InCollection);`
- L40 _public prototype_ `int32 AppendGeometry(const FTetrahedralCollection& GeometryCollection, int32 MaterialIDOffset = 0, bool ReindexAllMaterials = true, const FTransform& TransformRoot = FTransform::Identity);`
- L46 _public prototype_ `void InitIncidentElements(const int32 GeometryIndex=-1);` — Build \c IncidentElements and \c IncidentElementsLocalIndex. \p GeometryIndex - ID of the geometry entry to restrict operation to; -1 does all.
- L51 _public prototype_ `virtual void SetDefaults(FName Group, uint32 StartSize, uint32 NumElements) override;` — SetDefaults for new entries on this collection.
- L56 _public prototype_ `void ReorderElements(FName Group, const TArray<int32>& NewOrder) override;` — Reorders elements in a group. NewOrder must be the same length as the group.
- L58 _public prototype_ `void ReorderTetrahedralElements(const TArray<int32>& NewOrder);`
- L63 _public prototype_ `void RemoveVertices(const TArray<int32>& SortedVertexIndices);` — Remove selected vertices.
- L68 _public member_ `static const FName TetrahedralGroup;` — Attribute Groups
- L69 _public member_ `static const FName BindingsGroup;`
- L75 _public member_ `static const FName TetrahedronAttribute;` — Tetrahedron Attribute TManagedArray<FIntVector4> Tetrahedron = this->FindAttribute<FIntVector4>(FTetrahedralCollection::TetrahedronAttribute,FTetrahedralCollection::TetrahedralGroup);
- L76 _public member_ `TManagedArray<FIntVector4> Tetrahedron;`
- L78 _public member_ `static const FName TetrahedronStartAttribute;`
- L79 _public member_ `TManagedArray<int32> TetrahedronStart;`
- L80 _public member_ `static const FName TetrahedronCountAttribute;`
- L81 _public member_ `TManagedArray<int32> TetrahedronCount;`
- L87 _public member_ `static const FName IncidentElementsAttribute;` — Incident Elements Attribute For each vertex, a list of tetrahedra that includes that vertex.
- L88 _public member_ `TManagedArray<TArray<int32>> IncidentElements;`
- L94 _public member_ `static const FName IncidentElementsLocalIndexAttribute;` — Incident Elements Attribute For each incident element, the vertex's index in the tetrahedron.
- L95 _public member_ `TManagedArray<TArray<int32>> IncidentElementsLocalIndex;`
- L100 _public member_ `static const FName GuidAttribute;` — Guid Attribute
- L101 _public member_ `TManagedArray<FString> Guid;`
- L105 _protected prototype_ `void Construct();`
- L107 _protected prototype_ `virtual void Append(const FManagedArrayCollection& InCollection) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L110 _function_ `inline Chaos::FChaosArchive& operator<<(Chaos::FChaosArchive& Ar, FTetrahedralCollection& Value)`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh/Public/ChaosFlesh/TetrahedralExampleGeometry.h` (Public)


#### struct `ChaosFlesh::ExampleGeometry::UnitTetrahedron`  
`struct UnitTetrahedron`  
_L13-16_
- L15 _public prototype_ `static TUniquePtr<FTetrahedralCollection> Create();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ChaosFlesh`
- L11 _namespace_ `namespace ExampleGeometry` (scope `ChaosFlesh`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFlesh/Public/Meshing/ChaosFleshRadialMeshing.h` (Public)


#### Free symbols / members of external scopes

- L5 _prototype_ `void RadialTetMesh(const FVector::FReal InnerRadius, const FVector::FReal OuterRadius, const FVector::FReal Height, const int32 RadialSample, const int32 AngularSample, const int32 VerticalSample, const FVector::FReal BulgeDistance, TArray<FIntVector4>& TetElements, TArray<FVector>& TetVertices);`
- L6 _prototype_ `void RadialHexMesh(const FVector::FReal InnerRadius, const FVector::FReal OuterRadius, const FVector::FReal Height, const int32 RadialSample, const int32 AngularSample, const int32 VerticalSample, const FVector::FReal BulgeDistance, TArray<int32>& HexElements, TArray<FVector>& HexVertices);`
- L7 _prototype_ `void RegularHexMesh2TetMesh(const TArray<FVector>& HexVertices, const TArray<int32>& HexElements, TArray<FVector>& TetVertices, TArray<FIntVector4>& TetElements);`
- L8 _prototype_ `void ComputeHexMeshFaces(const TArray<int32>& HexElements, TArray<FIntVector2>& CommonFaces);`
- L11 _prototype_ `template <typename Func1, typename Func2, typename Func3> void ComputeMeshFaces(const TArray<int32>& mesh, Func1 GreaterThan, Func2 Equal, TArray<FIntVector2>& CommonFaces, Func3 GenerateFace, int32 PointsPerFace);`
- L12 _prototype_ `void GenerateHexFaceMesh(const TArray<int32>& HexElements, TArray<int32>& Faces);`
