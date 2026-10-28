# Plugins / CADLibrary

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/CADLibrary`
- headers: 4; symbols: 93
- symbol kinds: class=3, enum=1, enumerator=8, function=10, macro=8, member=17, namespace=7, prototype=33, struct=2, typedef=1, variable=3
- PublicDependencyModuleNames: CADKernel, CADTools, Core, DatasmithCore, DynamicMesh, GeometryCore, MeshConversion, MeshDescription, StaticMeshDescription

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADLibrary/Private/MeshEditingWrapper.h` (Private)


#### struct `FElementMetaData`  
`struct FElementMetaData`  
_L22-27_
- L24 _public member_ `uint16 Category:4;`
- L25 _public member_ `uint16 Markers:4;`
- L26 _public member_ `uint16 Extras:4;`

#### enum `MeshCategory::EElementCategory`  
`enum EElementCategory : uint8_t`  
_L31-41_
- L33 _public enumerator_ `ElementCategoryUnused = 0`
- L34 _public enumerator_ `ElementCategoryFree = 1`
- L35 _public enumerator_ `ElementCategoryLine = 2`
- L36 _public enumerator_ `ElementCategorySurface = 3`
- L37 _public enumerator_ `ElementCategoryBorder = 4`
- L38 _public enumerator_ `ElementCategoryNonManifold = 5`
- L39 _public enumerator_ `ElementCategoryNonSurface = 6`
- L40 _public enumerator_ `ElementCategoryMax = 7`

#### class `FMeshEditingWrapper`  
`class FMeshEditingWrapper`  
_L95-146_
- L99 _private member_ `FMeshDescription& MeshDescription;`
- L101 _private member_ `TArray<FElementMetaData> VertexMetaData;`
- L102 _private member_ `TArray<FElementMetaData> EdgeMetaData;`
- L103 _private member_ `TArray<FElementMetaData> TriangleMetaData;`
- L106 _private member_ `TBitArray<> VertexInstanceMarker;` — for orientation purpose
- L112 _public prototype_ `FMeshEditingWrapper(FMeshDescription& InMeshDescription);`
- L113 _public prototype_ `~FMeshEditingWrapper();`
- L115 _public prototype_ `void UpdateMeshWrapper();`
- L117 _public prototype_ `void ResetTriangleMarkerRecursively(FTriangleID Triangle);`
- L118 _public prototype_ `bool IsTriangleMarked(FTriangleID Triangle) const;`
- L119 _public prototype_ `void SetTriangleMarked(FTriangleID Triangle);`
- L121 _public prototype_ `MeshCategory::EElementCategory GetEdgeCategory(FEdgeID Edge) const;`
- L122 _public prototype_ `bool IsEdgeOfCategory(FEdgeID Edge, MeshCategory::EElementCategory Category) const;`
- L123 _public prototype_ `bool IsVertexOfCategory(FVertexInstanceID Vertex, MeshCategory::EElementCategory Category) const;`
- L126 _public prototype_ `void GetTriangleBoundingBox(FTriangleID Triangle, FVector& MinCorner, FVector& MaxCorner, FVertexInstanceID HighestVertex[3], FVertexInstanceID LowestVertex[3]) const;` — Triangle
- L128 _public prototype_ `void SwapTriangleOrientation(FTriangleID Triangle);`
- L131 _public prototype_ `const FTriangleID GetOtherTriangleAtEdge(FEdgeID Edge, FTriangleID Triangle) const;` — Edge
- L138 _public prototype_ `bool GetEdgeDirectionInTriangle(FEdgeID Edge, int32 TriangleIndex) const;` — @param Edge           The edge defined by its FEdgeID to get direction in its connected triangle @param TriangleIndex  The triangle connected to the edge, 0 for the first, 1 for the second, ...
- L139 _public prototype_ `void DefineEdgeTopology(FEdgeID EdgeID);`
- L142 _public prototype_ `void SwapVertexNormal(FVertexInstanceID VertexID);` — Vertex
- L143 _public prototype_ `void GetVertexBoundingBox(FVertexInstanceID Vertex, FVector& MinCorner, FVector& MaxCorner, FVertexInstanceID HighestVertex[3], FVertexInstanceID LowestVertex[3]) const;`
- L145 _public prototype_ `void DefineVertexTopologyApproximation(FVertexID VertexID);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define EDGE_IS_HARD 0x01`
- L13 _macro_ `#define EDGE_IS_UV_SEAM 0x02`
- L15 _macro_ `#define ELEMENT_STATUS_MASK 0x01`
- L16 _macro_ `#define ELEMENT_FIRST_MARKER_MASK 0x02`
- L17 _macro_ `#define ELEMENT_SECOND_MARKER_MASK 0x04`
- L19 _macro_ `#define ELEMENT_CRITICAL_ZONE_MASK 0x01`
- L20 _macro_ `#define ELEMENT_PARTITION_BORDER_MASK 0x02`
- L29 _namespace_ `namespace MeshCategory`
- L44 _namespace_ `namespace MeshEditingWrapperUtils`
- L46 _variable_ `const FName Debug( "Debu` (scope `MeshEditingWrapperUtils`)
- L47 _variable_ `const FName FeatureLine( "Feat` (scope `MeshEditingWrapperUtils`)
- L48 _variable_ `const FName EdgeLength( "Edge` (scope `MeshEditingWrapperUtils`)
- L50 _function_ `FORCEINLINE bool IsElementMarkerSet(const FElementMetaData& ElementMetaData, const uint16 Mask)` (scope `MeshEditingWrapperUtils`)
- L55 _function_ `FORCEINLINE void SetElementMarker(FElementMetaData& ElementMetaData, const uint16 Mask)` (scope `MeshEditingWrapperUtils`)
- L60 _function_ `FORCEINLINE void ResetElementMarker(FElementMetaData& ElementMetaData, const uint16 Mask)` (scope `MeshEditingWrapperUtils`)
- L65 _function_ `FORCEINLINE bool IsElementExtraSet(const FElementMetaData& ElementMetaData, const uint16 Mask)` (scope `MeshEditingWrapperUtils`)
- L70 _function_ `FORCEINLINE void SetElementExtra(FElementMetaData& ElementMetaData, const bool Value, const uint16 Mask)` (scope `MeshEditingWrapperUtils`)
- L82 _function_ `FORCEINLINE void ResetElementExtra(FElementMetaData& ElementMetaData, const uint16 Mask)` (scope `MeshEditingWrapperUtils`)
- L87 _function_ `FORCEINLINE void ResetElementData(FElementMetaData& ElementMetaData)` (scope `MeshEditingWrapperUtils`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADLibrary/Private/MeshOperator.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace MeshOperator`
- L12 _prototype_ `void FixNonManifoldMesh(FMeshDescription& MeshDescription);` (scope `MeshOperator`)
- L14 _prototype_ `bool OrientMesh(FMeshDescription& MeshDescription);` (scope `MeshOperator`)
- L16 _prototype_ `void RecomputeNullNormal(FMeshDescription& MeshDescription);` (scope `MeshOperator`)
- L18 _prototype_ `void ResolveTJunctions(FMeshDescription& MeshDescription, double Tolerance);` (scope `MeshOperator`)

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADLibrary/Public/CADKernelTools.h` (Public)


#### class `CADLibrary::FCADKernelTools`  
`class FCADKernelTools`  
_L27-40_
- L30 _public prototype_ `static void DefineMeshCriteria(UE::CADKernel::FModelMesh& MeshModel, const FImportParameters& ImportParameters, double GeometricTolerance);`
- L32 _public prototype_ `static void GetBodyTessellation(const UE::CADKernel::FModelMesh& ModelMesh, const UE::CADKernel::FBody& Body, FBodyMesh& OutBodyMesh);`
- L37 _public prototype_ `static bool Tessellate(UE::CADKernel::FTopologicalShapeEntity& InCADKernelEntity, FMeshConversionContext& Context, FMeshDescription& OutMeshDescription);` — Tessellate a CADKernel entity and update the MeshDescription
- L39 _public prototype_ `static uint32 GetFaceTessellation(UE::CADKernel::FFaceMesh& FaceMesh, FBodyMesh& OutBodyMesh, FObjectDisplayDataId FaceMaterial);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CADKernel` (scope `UE`)
- L20 _namespace_ `namespace CADLibrary`

### `Plugins/Enterprise/DatasmithCADImporter/Source/CADLibrary/Public/CADMeshDescriptionHelper.h` (Public)


#### struct `CADLibrary::FMeshConversionContext`  
`struct FMeshConversionContext`  
_L24-39_
- L26 _public member_ `const FImportParameters& ImportParameters;`
- L27 _public member_ `const FMeshParameters& MeshParameters;`
- L28 _public member_ `TArray<int32> VertexIds;`
- L29 _public member_ `TArray<int32> SymmetricVertexIds;`
- L30 _public member_ `TSet<int32> PatchesToMesh;`
- L31 _public member_ `double GeometricTolerance = 0.001;`
- L33 _public function_ `FMeshConversionContext(const FImportParameters& InImportParams, const FMeshParameters& InMeshParameters, double InGeometricTolerance = 0.001) : ImportParameters(InImportParams) , MeshParameters(InMeshParameters) , GeometricTolerance(InGeometricTolerance)`

#### class `CADLibrary::FMeshDescriptionDataCache`  
`class FMeshDescriptionDataCache`  
_L52-82_
- desc: Macro data of MeshDescription. Needed to update a MeshDesction after a conversion of a DynamicMesh To a MeshDescription. Indeed, PolygonGroupId can be modify during the process of DynamicMesh and material slot names are not saved in a DynamicMesh. The only persistent data is the patchGroupId This class save the PatchGroupToPolygonGroup map and the MaterialSlotNames of the MeshDescription before the conversion into a DynamicMesh This information allows to restor the material slot name used by each PolygonGroup The call of UpdateMaterialSlotNames restor the information in the new or update MeshDescription
- L56 _private member_ `TMap<int32, FPolygonGroupID> PatchGroupToPolygonGroup;` — the mapping between PatchId and PolygonGroupId
- L59 _private member_ `TArray<FName> MaterialSlotNames;` — the mapping between PolygonGroupId and SlotNames
- L61 _private member_ `FName EmptyName;`
- L63 _private function_ `const FPolygonGroupID* Find(const int32 PatchGroupId) const`
- L68 _private function_ `const FName& GetSlotName(const FPolygonGroupID& GroupID) const`
- L79 _public prototype_ `FMeshDescriptionDataCache(FMeshDescription& Mesh);`
- L81 _public prototype_ `void RestoreMaterialSlotNames(FMeshDescription& MeshDestination) const;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define LAST_CT_MATERIAL_ID 0x00ffffff`
- L19 _namespace_ `namespace CADLibrary`
- L22 _typedef_ `using TColorMap = TMap<uint32, uint32>;` (scope `CADLibrary`)
- L84 _prototype_ `TSharedPtr<IDatasmithUEPbrMaterialElement> CreateDefaultUEPbrMaterial();` (scope `CADLibrary`)
- L85 _prototype_ `TSharedPtr<IDatasmithUEPbrMaterialElement> CreateUEPbrMaterialFromColor(const FColor& InColor);` (scope `CADLibrary`)
- L86 _prototype_ `TSharedPtr<IDatasmithUEPbrMaterialElement> CreateUEPbrMaterialFromMaterial(FCADMaterial& InMaterial, TSharedRef<IDatasmithScene> Scene);` (scope `CADLibrary`)
- L88 _prototype_ `bool ConvertBodyMeshToMeshDescription(const FMeshConversionContext& MeshConversionContext, FBodyMesh& Body, FMeshDescription& MeshDescription);` (scope `CADLibrary`)
- L95 _prototype_ `TPolygonAttributesRef<int32> EnableCADPatchGroups(FMeshDescription& OutMeshDescription);` (scope `CADLibrary`) — Enable per-triangle integer attribute named PolyTriGroups This integer defines the identifier of the PolyTriGroup containing the triangle. In case of mesh coming from a CAD file, a PolyTriGroup is associated to a CAD topological face
- L96 _prototype_ `void GetExistingPatches(FMeshDescription& Mesh, TSet<int32>& OutPatchIdSet);` (scope `CADLibrary`)
