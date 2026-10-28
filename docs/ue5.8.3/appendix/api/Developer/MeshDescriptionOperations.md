# Developer / MeshDescriptionOperations

- module root: `Source/Developer/MeshDescriptionOperations`
- headers: 1; symbols: 32
- symbol kinds: class=1, enum=1, enumerator=5, prototype=24, typedef=1
- PrivateDependencyModuleNames: MeshDescription
- PublicDependencyModuleNames: Core, StaticMeshDescription

### `Source/Developer/MeshDescriptionOperations/Public/MeshDescriptionOperations.h` (Public)


#### class `FMeshDescriptionOperations`  
`class FMeshDescriptionOperations`  
_L27-162_
- desc: FMeshDescriptionOperations has been deprecated, most of it's features have been moved over FStaticMeshOperations.
- L39 _public typedef_ `typedef FStaticMeshOperations::FAppendSettings FAppendSettings;`
- L43 _public prototype_ `static void ConvertToRawMesh(const FMeshDescription& SourceMeshDescription, FRawMesh& DestinationRawMesh, const TMap<FName, int32>& MaterialMap);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::ConvertToRawMesh() instead.")` — Convert this mesh description into the old FRawMesh format.
- L47 _public prototype_ `static void ConvertFromRawMesh(const FRawMesh& SourceRawMesh, FMeshDescription& DestinationMeshDescription, const TMap<int32, FName>& MaterialMap);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::ConvertFromRawMesh() instead.")` — Convert old FRawMesh format to MeshDescription.
- L50 _public prototype_ `static void AppendMeshDescription(const FMeshDescription& SourceMesh, FMeshDescription& TargetMesh, FAppendSettings& AppendSettings);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::AppendMeshDescription() instead.")`
- L56 _public prototype_ `static void RecomputeNormalsAndTangentsIfNeeded(FMeshDescription& MeshDescription, ETangentOptions TangentOptions, bool bForceRecomputeNormals = false, bool bForceRecomputeTangents = false);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::RecomputeNormalsAndTangentsIfNeeded() instead.")` — Check if all normals and tangents are valid, if not recompute them
- L63 _public prototype_ `static void CreatePolygonNTB(FMeshDescription& MeshDescription, float ComparisonThreshold);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::CreatComputePolygonTangentsAndNormals() instead.")` — Compute normal, tangent and Bi-Normal for every polygon in the mesh description. (this do not compute Vertex NTBs) It also remove the degenerated polygon from the mesh description
- L67 _public prototype_ `static void CreateNormals(FMeshDescription& MeshDescription, ETangentOptions TangentOptions, bool bComputeTangent);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::CreateNormals() instead.")` — Compute normal, tangent and Bi-Normal(only if bComputeTangent is true) for every vertex in the mesh description.
- L71 _public prototype_ `static void CreateMikktTangents(FMeshDescription& MeshDescription, ETangentOptions TangentOptions);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::CreateMikktTangents() instead.")` — Compute tangent and Bi-Normal using mikkt space for every vertex in the mesh description.
- L75 _public prototype_ `static void FindOverlappingCorners(FOverlappingCorners& OverlappingCorners, const FMeshDescription& MeshDescription, float ComparisonThreshold);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::FindOverlappingCorners() instead.")` — Find all overlapping vertex using the threshold in the mesh description.
- L79 _public prototype_ `static int32 GetUVChartCount(FMeshDescription& MeshDescription, int32 SrcLightmapIndex, ELightmapUVVersion LightmapUVVersion, const FOverlappingCorners& OverlappingCorners);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::GetUVChartCount() instead.")` — Find all charts in the mesh description.
- L96 _public prototype_ `static bool CreateLightMapUVLayout(FMeshDescription& MeshDescription, int32 SrcLightmapIndex, int32 DstLightmapIndex, int32 MinLightmapResolution, ELightmapUVVersion LightmapUVVersion, const FOverlappingCorners& OverlappingCorners);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::CreateLightMapUVLayout() instead.")` — Find and pack UV charts for lightmap. The packing algorithm uses a rasterization method, hence the resolution parameter. If the given minimum resolution is not enough to handle all the charts, generation will fail. @param MeshDescription        Edited mesh @param SrcLightmapIndex       index of the source UV channel @param DstLightmapIndex       index of the destination UV channel @param MinLightmapResolution  Minimum resolution used for the packing @param LightmapUVVersion      Algorithm version @param OverlappingCorners     Overlapping corners of the given mesh @return                       UV layout correctly generated
- L105 _public prototype_ `static bool GenerateUniqueUVsForStaticMesh(const FMeshDescription& MeshDescription, int32 TextureResolution, bool bMergeIdenticalMaterials, TArray<FVector2D>& OutTexCoords);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::GenerateUniqueUVsForStaticMesh() instead.")` — Create some UVs from the specified mesh description data.
- L109 _public prototype_ `static bool AddUVChannel(FMeshDescription& MeshDescription);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::AddUVChannel() instead.")` — Add a UV channel to the MeshDescription.
- L113 _public prototype_ `static bool InsertUVChannel(FMeshDescription& MeshDescription, int32 UVChannelIndex);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::InsertUVChannel() instead.")` — Insert a UV channel at the given index to the MeshDescription.
- L117 _public prototype_ `static bool RemoveUVChannel(FMeshDescription& MeshDescription, int32 UVChannelIndex);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::RemoveUVChannel() instead.")` — Remove the UV channel at the given index from the MeshDescription.
- L121 _public prototype_ `static void GeneratePlanarUV(const FMeshDescription& MeshDescription, const FUVMapParameters& Params, TMap<FVertexInstanceID, FVector2D>& OutTexCoords);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::GeneratePlanarUV() instead.")` — Generate planar UV mapping for the MeshDescription
- L125 _public prototype_ `static void GenerateCylindricalUV(FMeshDescription& MeshDescription, const FUVMapParameters& Params, TMap<FVertexInstanceID, FVector2D>& OutTexCoords);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::GenerateCylindricalUV() instead.")` — Generate cylindrical UV mapping for the MeshDescription
- L129 _public prototype_ `static void GenerateBoxUV(const FMeshDescription& MeshDescription, const FUVMapParameters& Params, TMap<FVertexInstanceID, FVector2D>& OutTexCoords);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::GenerateBoxUV() instead.")` — Generate box UV mapping for the MeshDescription
- L132 _public prototype_ `static void RemapPolygonGroups(FMeshDescription& MeshDescription, TMap<FPolygonGroupID, FPolygonGroupID>& Remap);` — `UE_DEPRECATED(4.25, "Use FMeshDescription::RemapPolygonGroups() instead.")`
- L145 _public prototype_ `static void SwapPolygonPolygonGroup(FMeshDescription& MeshDescription, int32 SectionIndex, int32 TriangleIndexStart, int32 TriangleIndexEnd, bool bRemoveEmptyPolygonGroup);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::SwapPolygonPolygonGroup() instead.")` — Move some polygon to a new PolygonGroup(section) SectionIndex: The target section we want to assign the polygon. See bRemoveEmptyPolygonGroup to know how its used TriangleIndexStart: The triangle index is compute as follow: foreach polygon {TriangleIndex += Polygon->NumberTriangles} TriangleIndexEnd: The triangle index is compute as follow: foreach polygon {TriangleIndex += Polygon->NumberTriangles} bRemoveEmptyPolygonGroup: If true, any polygonGroup that is empty after moving a polygon will be delete. This parameter impact how SectionIndex is use If param is true  : PolygonGroupTargetID.GetValue() do not necessary equal SectionIndex in case there is less sections then SectionIndex If param is false : PolygonGroupTargetID.GetValue() equal SectionIndex, we will add all necessary missing PolygonGroupID (this can generate empty PolygonGroupID)
- L148 _public prototype_ `static void ConvertHardEdgesToSmoothGroup(const FMeshDescription& SourceMeshDescription, TArray<uint32>& FaceSmoothingMasks);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::ConvertHardEdgesToSmoothGroup() instead.")`
- L151 _public prototype_ `static void ConvertSmoothGroupToHardEdges(const TArray<uint32>& FaceSmoothingMasks, FMeshDescription& DestinationMeshDescription);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::ConvertSmoothGroupToHardEdges() instead.")`
- L154 _public prototype_ `static bool HasVertexColor(const FMeshDescription& MeshDescription);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::HasVertexColor() instead.")`
- L157 _public prototype_ `static void BuildWeldedVertexIDRemap(const FMeshDescription& MeshDescription, const float WeldingThreshold, TMap<FVertexID, FVertexID>& OutVertexIDRemap);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::BuildWeldedVertexIDRemap() instead.")`
- L161 _public prototype_ `static FSHAHash ComputeSHAHash(const FMeshDescription& MeshDescription);` — `UE_DEPRECATED(4.25, "Use FStaticMeshOperations::ComputeSHAHash() instead.")` — Computes the SHA hash of all the attributes values in the MeshDescription.

#### enum `FMeshDescriptionOperations::ETangentOptions`  
`enum ETangentOptions`  
_L30-37_
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `BlendOverlappingNormals = 0x00000001`
- L34 _public enumerator_ `IgnoreDegenerateTriangles = 0x00000002`
- L35 _public enumerator_ `UseMikkTSpace = 0x00000004`
- L36 _public enumerator_ `UseWeightedAreaAndAngle = 0x00000008` — Use surface area and angle as a ratio when computing normals
