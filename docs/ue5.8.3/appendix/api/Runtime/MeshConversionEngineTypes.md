# Runtime / MeshConversionEngineTypes

- module root: `Source/Runtime/MeshConversionEngineTypes`
- headers: 7; symbols: 76
- symbol kinds: class=4, enum=1, enumerator=2, member=32, namespace=12, prototype=19, struct=6
- PublicDependencyModuleNames: Chaos, Core, Engine, GeometryCore, MeshConversion, MeshDescription, SkeletalMeshDescription, StaticMeshDescription

### `Source/Runtime/MeshConversionEngineTypes/Public/DynamicMeshToSkeleton.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Geometry` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Conversion` (scope `UE`)
- L23 _prototype_ `bool IsDynamicMeshCompatibleWithSkeleton(const FDynamicMesh3& InDynamicMesh, const USkeleton& InSkeleton, bool bDoParentChainCheck = true);` (scope `UE::Conversion`) — Verify if a dynamic mesh is compatible with a USkeleton @param InDynamicMesh  Dynamic mesh to compare the Skeleton against. Must have bone attributes enabled. @param InSkeleton Skeleton asset to compare against the dynamic mesh skeletal attributes @param bDoParentChainCheck  When true (the default) this method also compares if chains match with the parent. @return true if the skeleton is compatible with the supplied dynamic mesh, false if not.

### `Source/Runtime/MeshConversionEngineTypes/Public/GeometryCollectionToDynamicMesh.h` (Public)


#### struct `UE::Geometry::FGeometryCollectionToDynamicMeshes`  
`struct FGeometryCollectionToDynamicMeshes`  
_L16-93_
- L28 _public member_ `TArray<FMeshInfo> Meshes;`
- L63 _public prototype_ `bool Init(const FManagedArrayCollection& Collection, const FToMeshOptions& Options);` — Convert all meshes in the given collection to dynamic meshes
- L66 _public prototype_ `bool InitFromTransformSelection(const FManagedArrayCollection& Collection, TConstArrayView<int32> TransformIndices, const FToMeshOptions& Options);` — Convert the meshes in the collection at the given transforms to dynamic meshes
- L70 _public prototype_ `bool UpdateGeometryCollection(FGeometryCollection& Collection, const FToCollectionOptions& Options) const;` — Update a geometry collection with the current meshes array Note this updates a Geometry Collection rather than the more general FManagedArrayCollection because some of the updating code is specific to geometry collection
- L75 _public prototype_ `static int32 AppendMeshToCollection(FGeometryCollection& Collection, const FDynamicMesh3& Mesh, const FTransform& MeshTransform, const FToCollectionOptions& Options);` — Add a new mesh to the geometry collection Note this updates a Geometry Collection rather than the more general FManagedArrayCollection because some of the updating code is specific to geometry collection @return Index of added transform
- L80 _public prototype_ `static FName InternalFacePolyGroupName();` — Get the name used for the polygroup that we optionally set on the dynamic mesh, corresponding to the internal face tags of the geometry collection triangles
- L82 _public prototype_ `static FName VisibleFacePolyGroupName();` — Get the name used for the polygroup that we optionally set on the dynamic mesh, corresponding to the invisible face tags of the geometry collection triangles
- L88 _private prototype_ `bool InitHelper(const FManagedArrayCollection& Collection, bool bTransformInComponentSpace, TConstArrayView<FTransform3f> Transforms, bool bAllTransforms, TConstArrayView<int32> TransformIndices, const FToMeshOptions& Options);` — private helper method with shared implementation for all Init* methods @param bTransformInComponentSpace If false, the Transforms array holds transforms that are relative to the corresponding bone parent. If true, the Transforms are all relative to a common coordinate space.
- L89 _private prototype_ `static TConstArrayView<FTransform3f> GetCollectionTransforms(const FManagedArrayCollection& Collection);`
- L92 _private prototype_ `static bool UpdateCollection(const FTransform& FromCollection, const FDynamicMesh3& Mesh, int32 GeometryIdx, FGeometryCollection& Output, const FToCollectionOptions& Options);` — Update an existing geometry in a collection w/ a new mesh (w/ the same number of faces and vertices!)

#### struct `UE::Geometry::FGeometryCollectionToDynamicMeshes::FMeshInfo`  
`struct FMeshInfo`  
_L18-26_
- L21 _public member_ `int32 TransformIndex = -1;` — Transform Index of the bone represented
- L23 _public member_ `TUniquePtr<FDynamicMesh3> Mesh;` — Mesh holding the geometry at (or under) a given bone, in a common coordinate space
- L25 _public member_ `FTransform Transform = FTransform::Identity;` — Stores the Transform that has *already* been applied to the Mesh vertices, which took it from local bone space to a common space

#### enum `UE::Geometry::FGeometryCollectionToDynamicMeshes::EInvisibleFaceConversion`  
`enum class EInvisibleFaceConversion : uint8`  
_L32-36_
- L34 _public enumerator_ `Skip`
- L35 _public enumerator_ `TagWithPolygroup`

#### struct `UE::Geometry::FGeometryCollectionToDynamicMeshes::FToMeshOptions`  
`struct FToMeshOptions`  
_L38-47_
- L40 _public member_ `FTransform Transform = FTransform::Identity;`
- L42 _public member_ `bool bWeldVertices = false;`
- L43 _public member_ `bool bSaveIsolatedVertices = false;`
- L45 _public member_ `bool bInternalFaceTagsAsPolygroups = true;`
- L46 _public member_ `EInvisibleFaceConversion InvisibleFaces = EInvisibleFaceConversion::Skip;`

#### struct `UE::Geometry::FGeometryCollectionToDynamicMeshes::FToCollectionOptions`  
`struct FToCollectionOptions`  
_L49-60_
- L52 _public member_ `bool bDefaultFaceVisible = true;` — Whether to set faces with no 'visible' tag as visible (if true) or invisible (if false)
- L54 _public member_ `bool bDefaultFaceInternal = false;` — Whether to set faces with no 'internal' tag as internal (if true) or external (if false)
- L56 _public member_ `bool bAllowAppendAsRoot = false;` — Whether the appended geometry is allowed to be added as a root transform (if NewMeshParentIndex == -1)
- L59 _public member_ `int32 NewMeshParentIndex = -1;` — Parent index to use if adding a new mesh (with no existing transform) -- if invalid, will add to root

#### Free symbols / members of external scopes

- L9 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Source/Runtime/MeshConversionEngineTypes/Public/IndexedMeshToDynamicMesh.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Conversion` (scope `UE`)
- L21 _prototype_ `bool RenderBuffersToDynamicMesh( const FStaticMeshVertexBuffers& VertexData, const FRawStaticIndexBuffer& IndexData, const FStaticMeshSectionArray& SectionData, FDynamicMesh3& MeshOut, bool bAttemptToWeldSeams = false );` (scope `UE::Conversion`) — Convert rendering buffer data (from FStaticMeshLODResources) to a DynamicMesh3. The output FDynamicMesh3 attribute set will have as many UV channels as found in VertexData, as well as overlay Tangents enabled/copied, and MaterialID set. @param bAttemptToWeldSeams if true, try to weld seam edges together to create a more closed mesh using FMergeCoincidentMeshEdges

### `Source/Runtime/MeshConversionEngineTypes/Public/MeshConversionEngineTypesModule.h` (Public)


#### class `FMeshConversionEngineTypesModule`  
`class FMeshConversionEngineTypesModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Runtime/MeshConversionEngineTypes/Public/SkeletalMeshLODModelToDynamicMesh.h` (Public)


#### class `FSkeletalMeshLODModelToDynamicMesh`  
`class FSkeletalMeshLODModelToDynamicMesh`  
_L17-52_
- desc: Convert FSkeletalMeshLODModel to FDynamicMesh3
- L21 _public member_ `bool bPrintDebugMessages = false;` — If true, will print some possibly-helpful debugging spew to output log
- L24 _public member_ `bool bEnableOutputGroups = true;` — Should we initialize triangle groups on output mesh
- L27 _public member_ `bool bCalculateMaps = true;` — Should we calculate conversion index maps
- L30 _public member_ `bool bDisableAttributes = false;` — Ignore all mesh attributes (e.g. UV/Normal layers, material groups)
- L34 _public member_ `TArray<int32> TriIDMap;` — map from DynamicMesh triangle ID to FSkeletalMeshLODModel TriIdx
- L42 _public member_ `TArray<int32> VertIDMap;` — map from DynamicMesh vertex Id to  FSkeletalMeshLODModel FVertexID. NB: due to vertex splitting, multiple DynamicMesh vertex ids may map to the same  FSkeletalMeshLODModel FVertexID. ( a vertex split is a result of reconciling non-manifold  FSkeletalMeshLODModel vertex )
- L50 _public prototype_ `void Convert(const FSkeletalMeshLODModel* MeshIn, FDynamicMesh3& MeshOut, bool bCopyTangents = false);` — Default conversion of MeshDescription to DynamicMesh @param bCopyTangents  - if bDisableAttributes is false, this requests the tangent plane vectors (tangent and bitangent) be stored as overlays in the MeshOut DynamicAttributeSet, provided they exist on the MeshIn

### `Source/Runtime/MeshConversionEngineTypes/Public/SkeletalMeshLODRenderDataToDynamicMesh.h` (Public)


#### class `UE::Geometry::FSkeletalMeshLODRenderDataToDynamicMesh`  
`class FSkeletalMeshLODRenderDataToDynamicMesh`  
_L27-60_
- L47 _public prototype_ `static bool Convert( const FSkeletalMeshLODRenderData* SkeletalMeshResources, const FReferenceSkeleton& RefSkeleton, const ConversionOptions& Options, FDynamicMesh3& OutputMesh, bool bHasVertexColors, TFunctionRef<FColor(int32)> GetVertexColorFromLODVertexIndex);` — @param bHasVertexColors					Whether to add vertex colors to the output (if available) @param GetVertexColorFromLODVertexIndex	Function for getting the vertex color of a given vertex index
- L55 _public prototype_ `static bool Convert( const FSkeletalMeshLODRenderData* SkeletalMeshResources, const FReferenceSkeleton& RefSkeleton, const ConversionOptions& Options, FDynamicMesh3& OutputMesh);`

#### struct `UE::Geometry::FSkeletalMeshLODRenderDataToDynamicMesh::ConversionOptions`  
`struct ConversionOptions`  
_L32-43_
- desc: TODO: more options?
- L34 _public member_ `bool bWantNormals = true;`
- L35 _public member_ `bool bWantTangents = true;`
- L36 _public member_ `bool bWantUVs = true;`
- L37 _public member_ `bool bWantVertexColors = true;`
- L38 _public member_ `bool bWantMaterialIDs = true;`
- L39 _public member_ `bool bWantSkinWeights = true;`
- L42 _public member_ `FVector3d BuildScale = FVector3d::One();` — mesh vertex positions are multiplied by the build scale

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)

### `Source/Runtime/MeshConversionEngineTypes/Public/StaticMeshLODResourcesToDynamicMesh.h` (Public)


#### class `UE::Geometry::FStaticMeshLODResourcesToDynamicMesh`  
`class FStaticMeshLODResourcesToDynamicMesh`  
_L23-53_
- desc: FStaticMeshLODResourcesToDynamicMesh can be used to create a FDynamicMesh3 from a FStaticMeshLODResources, which is the variant of the mesh in a StaticMesh Asset used for rendering (and which is available at runtime). The FStaticMeshLODResources has vertices duplicated at any split UV/normal/tangent/color, ie in the overlays there will be a unique overlay element for each base mesh vertex.
- L41 _public prototype_ `static bool Convert( const FStaticMeshLODResources* StaticMeshResources, const ConversionOptions& Options, FDynamicMesh3& OutputMesh, bool bHasVertexColors, TFunctionRef<FColor(int32)> GetVertexColorFromLODVertexIndex);` — @param bHasVertexColors					Whether to add vertex colors to the output (if available) @param GetVertexColorFromLODVertexIndex	Function for getting the vertex color of a given vertex index
- L48 _public prototype_ `static bool Convert( const FStaticMeshLODResources* StaticMeshResources, const ConversionOptions& Options, FDynamicMesh3& OutputMesh);`

#### struct `UE::Geometry::FStaticMeshLODResourcesToDynamicMesh::ConversionOptions`  
`struct ConversionOptions`  
_L27-37_
- L29 _public member_ `bool bWantNormals = true;`
- L30 _public member_ `bool bWantTangents = true;`
- L31 _public member_ `bool bWantUVs = true;`
- L32 _public member_ `bool bWantVertexColors = true;`
- L33 _public member_ `bool bWantMaterialIDs = true;`
- L36 _public member_ `FVector3d BuildScale = FVector3d::One();` — mesh vertex positions are multiplied by the build scale

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)
