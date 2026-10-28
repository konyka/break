# Runtime / StaticMeshDescription

- module root: `Source/Runtime/StaticMeshDescription`
- headers: 4; symbols: 166
- symbol kinds: class=4, delegate=2, enum=3, enumerator=13, externvar=11, function=56, member=19, namespace=7, prototype=46, struct=4, typedef=1
- DynamicallyLoadedModuleNames: GeometryProcessingInterfaces
- PrivateDependencyModuleNames: MeshUtilitiesCommon, RawMesh
- PrivateIncludePathModuleNames: GeometryProcessingInterfaces
- PublicDependencyModuleNames: Core, CoreUObject, MeshDescription

### `Source/Runtime/StaticMeshDescription/Public/StaticMeshAttributes.h` (Public)


#### class `FStaticMeshAttributes`  
`class FStaticMeshAttributes : public FMeshAttributes`  
_L53-122_
- inherits: `FMeshAttributes`
- L57 _public function_ `explicit FStaticMeshAttributes(FMeshDescription& InMeshDescription) : FMeshAttributes(InMeshDescription)`
- L61 _public prototype_ `virtual void Register(bool bKeepExistingAttribute = false) override;`
- L63 _public function_ `static bool IsReservedAttributeName(const FName InAttributeName)`
- L80 _public prototype_ `void RegisterTriangleNormalAndTangentAttributes();`
- L81 _public prototype_ `void UnregisterTriangleNormalAndTangentAttributes();`
- L87 _public prototype_ `void RegisterPolygonObjectNameAttribute();` — Registers a mesh attribute that is used to store the name of the object that contributed to each polygon. Used to partition the mesh into sub-objects, if needed. See GetPolygonObjectNames.
- L89 _public function_ `TVertexInstanceAttributesRef<FVector2f> GetVertexInstanceUVs()`
- L90 _public function_ `TVertexInstanceAttributesConstRef<FVector2f> GetVertexInstanceUVs() const`
- L92 _public function_ `TVertexInstanceAttributesRef<FVector3f> GetVertexInstanceNormals()`
- L93 _public function_ `TVertexInstanceAttributesConstRef<FVector3f> GetVertexInstanceNormals() const`
- L95 _public function_ `TVertexInstanceAttributesRef<FVector3f> GetVertexInstanceTangents()`
- L96 _public function_ `TVertexInstanceAttributesConstRef<FVector3f> GetVertexInstanceTangents() const`
- L98 _public function_ `TVertexInstanceAttributesRef<float> GetVertexInstanceBinormalSigns()`
- L99 _public function_ `TVertexInstanceAttributesConstRef<float> GetVertexInstanceBinormalSigns() const`
- L101 _public function_ `TVertexInstanceAttributesRef<FVector4f> GetVertexInstanceColors()`
- L102 _public function_ `TVertexInstanceAttributesConstRef<FVector4f> GetVertexInstanceColors() const`
- L104 _public function_ `TEdgeAttributesRef<bool> GetEdgeHardnesses()`
- L105 _public function_ `TEdgeAttributesConstRef<bool> GetEdgeHardnesses() const`
- L107 _public function_ `TTriangleAttributesRef<FVector3f> GetTriangleNormals()`
- L108 _public function_ `TTriangleAttributesConstRef<FVector3f> GetTriangleNormals() const`
- L110 _public function_ `TTriangleAttributesRef<FVector3f> GetTriangleTangents()`
- L111 _public function_ `TTriangleAttributesConstRef<FVector3f> GetTriangleTangents() const`
- L113 _public function_ `TTriangleAttributesRef<FVector3f> GetTriangleBinormals()`
- L114 _public function_ `TTriangleAttributesConstRef<FVector3f> GetTriangleBinormals() const`
- L117 _public function_ `TPolygonAttributesRef<FName> GetPolygonObjectNames()` — This attribute stores the name of the object that this part of the mesh was generated from, e.g. from a sub-object during import or during mesh merging.
- L118 _public function_ `TPolygonAttributesConstRef<FName> GetPolygonObjectNames() const`
- L120 _public function_ `TPolygonGroupAttributesRef<FName> GetPolygonGroupMaterialSlotNames()`
- L121 _public function_ `TPolygonGroupAttributesConstRef<FName> GetPolygonGroupMaterialSlotNames() const`

#### class `FStaticMeshConstAttributes`  
`class FStaticMeshConstAttributes : public FMeshConstAttributes`  
_L125-144_
- inherits: `FMeshConstAttributes`
- L129 _public function_ `explicit FStaticMeshConstAttributes(const FMeshDescription& InMeshDescription) : FMeshConstAttributes(InMeshDescription)`
- L133 _public function_ `TVertexInstanceAttributesConstRef<FVector2f> GetVertexInstanceUVs() const`
- L134 _public function_ `TVertexInstanceAttributesConstRef<FVector3f> GetVertexInstanceNormals() const`
- L135 _public function_ `TVertexInstanceAttributesConstRef<FVector3f> GetVertexInstanceTangents() const`
- L136 _public function_ `TVertexInstanceAttributesConstRef<float> GetVertexInstanceBinormalSigns() const`
- L137 _public function_ `TVertexInstanceAttributesConstRef<FVector4f> GetVertexInstanceColors() const`
- L138 _public function_ `TEdgeAttributesConstRef<bool> GetEdgeHardnesses() const`
- L139 _public function_ `TTriangleAttributesConstRef<FVector3f> GetTriangleNormals() const`
- L140 _public function_ `TTriangleAttributesConstRef<FVector3f> GetTriangleTangents() const`
- L141 _public function_ `TTriangleAttributesConstRef<FVector3f> GetTriangleBinormals() const`
- L142 _public function_ `TPolygonAttributesConstRef<FName> GetPolygonObjectNames() const`
- L143 _public function_ `TPolygonGroupAttributesConstRef<FName> GetPolygonGroupMaterialSlotNames() const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace MeshAttribute`
- L16 _namespace_ `namespace Vertex` (scope `MeshAttribute`)
- L20 _namespace_ `namespace VertexInstance` (scope `MeshAttribute`)
- L22 _externvar_ `extern const FName TextureCoordinate;` (scope `MeshAttribute::VertexInstance`)
- L23 _externvar_ `extern const FName Normal;` (scope `MeshAttribute::VertexInstance`)
- L24 _externvar_ `extern const FName Tangent;` (scope `MeshAttribute::VertexInstance`)
- L25 _externvar_ `extern const FName BinormalSign;` (scope `MeshAttribute::VertexInstance`)
- L26 _externvar_ `extern const FName Color;` (scope `MeshAttribute::VertexInstance`)
- L29 _namespace_ `namespace Edge` (scope `MeshAttribute`)
- L31 _externvar_ `extern const FName IsHard;` (scope `MeshAttribute::Edge`)
- L34 _namespace_ `namespace Triangle` (scope `MeshAttribute`)
- L36 _externvar_ `extern const FName Normal;` (scope `MeshAttribute::Triangle`)
- L37 _externvar_ `extern const FName Tangent;` (scope `MeshAttribute::Triangle`)
- L38 _externvar_ `extern const FName Binormal;` (scope `MeshAttribute::Triangle`)
- L41 _namespace_ `namespace Polygon` (scope `MeshAttribute`)
- L43 _externvar_ `extern const FName ObjectName;` (scope `MeshAttribute::Polygon`)
- L46 _namespace_ `namespace PolygonGroup` (scope `MeshAttribute`)
- L48 _externvar_ `extern const FName ImportedMaterialSlotName;` (scope `MeshAttribute::PolygonGroup`)

### `Source/Runtime/StaticMeshDescription/Public/StaticMeshDescription.h` (Public)


#### class `UStaticMeshDescription`  
`class UStaticMeshDescription : public UMeshDescriptionBase`  
_L27-85_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMeshDescriptionBase`
- desc: A wrapper for MeshDescription, customized for static meshes
- L33 _public prototype_ `virtual void RegisterAttributes() override;` — Register attributes required by static mesh description
- L35 _public function_ `virtual FStaticMeshAttributes& GetRequiredAttributes() override`
- L40 _public function_ `virtual const FStaticMeshAttributes& GetRequiredAttributes() const override`
- L46 _public prototype_ `FVector2D GetVertexInstanceUV(FVertexInstanceID VertexInstanceID, int32 UVIndex = 0) const;` — `UFUNCTION(BlueprintPure, Category="MeshDescription")`
- L49 _public prototype_ `void SetVertexInstanceUV(FVertexInstanceID VertexInstanceID, FVector2D UV, int32 UVIndex = 0);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")`
- L52 _public prototype_ `void CreateCube(FVector Center, FVector HalfExtents, FPolygonGroupID PolygonGroup, FPolygonID& PolygonID_PlusX, FPolygonID& PolygonID_MinusX, FPolygonID& PolygonID_PlusY, FPolygonID& PolygonID_MinusY, FPolygonID& PolygonID_PlusZ, FPolygonID& PolygonID_MinusZ);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")`
- L61 _public prototype_ `void SetPolygonGroupMaterialSlotName(FPolygonGroupID PolygonGroupID, const FName& SlotName);` — `UFUNCTION(BlueprintCallable, Category="MeshDescription")`
- L65 _public function_ `TVertexInstanceAttributesRef<FVector2f> GetVertexInstanceUVs()`
- L66 _public function_ `TVertexInstanceAttributesConstRef<FVector2f> GetVertexInstanceUVs() const`
- L68 _public function_ `TVertexInstanceAttributesRef<FVector3f> GetVertexInstanceNormals()`
- L69 _public function_ `TVertexInstanceAttributesConstRef<FVector3f> GetVertexInstanceNormals() const`
- L71 _public function_ `TVertexInstanceAttributesRef<FVector3f> GetVertexInstanceTangents()`
- L72 _public function_ `TVertexInstanceAttributesConstRef<FVector3f> GetVertexInstanceTangents() const`
- L74 _public function_ `TVertexInstanceAttributesRef<float> GetVertexInstanceBinormalSigns()`
- L75 _public function_ `TVertexInstanceAttributesConstRef<float> GetVertexInstanceBinormalSigns() const`
- L77 _public function_ `TVertexInstanceAttributesRef<FVector4f> GetVertexInstanceColors()`
- L78 _public function_ `TVertexInstanceAttributesConstRef<FVector4f> GetVertexInstanceColors() const`
- L80 _public function_ `TEdgeAttributesRef<bool> GetEdgeHardnesses()`
- L81 _public function_ `TEdgeAttributesConstRef<bool> GetEdgeHardnesses() const`
- L83 _public function_ `TPolygonGroupAttributesRef<FName> GetPolygonGroupMaterialSlotNames()`
- L84 _public function_ `TPolygonGroupAttributesConstRef<FName> GetPolygonGroupMaterialSlotNames() const`

### `Source/Runtime/StaticMeshDescription/Public/StaticMeshOperations.h` (Public)


#### enum `EComputeNTBsFlags`  
`enum class EComputeNTBsFlags : uint32`  
_L34-43_
- L36 _public enumerator_ `None = 0x00000000` — No flags
- L37 _public enumerator_ `Normals = 0x00000001` — Force-recompute the normals and implicitly force the recomputing of tangents.
- L38 _public enumerator_ `Tangents = 0x00000002` — Force-recompute the tangents.
- L39 _public enumerator_ `UseMikkTSpace = 0x00000004` — Used when force-recomputing the tangents, use MikkTSpace.
- L40 _public enumerator_ `WeightedNTBs = 0x00000008` — Use weight surface area and angle when computing NTBs to proportionally distribute the vertex instance contribution to the normal/tangent/binormal in a smooth group.    i.e. Weight solve the cylinder problem
- L41 _public enumerator_ `BlendOverlappingNormals = 0x00000010`
- L42 _public enumerator_ `IgnoreDegenerateTriangles = 0x00000020`

#### class `FStaticMeshOperations`  
`class FStaticMeshOperations`  
_L46-241_
- L65 _public prototype_ `static void ComputeTriangleTangentsAndNormals(FMeshDescription& MeshDescription, float ComparisonThreshold = 0.0f, const TCHAR* DebugName = nullptr);` — Set the triangle tangent, normal, binormal and triangleCenter for all triangles in the mesh description.
- L71 _public prototype_ `static void ComputeTangentsAndNormals(FMeshDescription& MeshDescription, EComputeNTBsFlags ComputeNTBsOptions);` — Recompute any invalid normal, tangent or Bi-Normal for every vertex in the mesh description with the given options. If the EComputeNTBsFlags Normals or Tangents are set, the corresponding data will be force-recomputed.
- L76 _public prototype_ `static void RecomputeNormalsAndTangentsIfNeeded(FMeshDescription& MeshDescription, EComputeNTBsFlags ComputeNTBsOptions);` — Make sure all normals and tangents are valid. If not, recompute them.
- L79 _public prototype_ `static void ComputeMikktTangents(FMeshDescription& MeshDescription, bool bIgnoreDegenerateTriangles);` — Compute tangent and Bi-Normal using mikkt space for every vertex in the mesh description.
- L82 _public prototype_ `static void DetermineEdgeHardnessesFromVertexInstanceNormals(FMeshDescription& MeshDescription, float Tolerance = UE_KINDA_SMALL_NUMBER);` — Determine the edge hardnesses from existing normals
- L85 _public prototype_ `static void ConvertToRawMesh(const FMeshDescription& SourceMeshDescription, FRawMesh& DestinationRawMesh, const TMap<FName, int32>& MaterialMap);` — Convert this mesh description into the old FRawMesh format.
- L88 _public prototype_ `static void ConvertFromRawMesh(const FRawMesh& SourceRawMesh, FMeshDescription& DestinationMeshDescription, const TMap<int32, FName>& MaterialMap, bool bSkipNormalsAndTangents = false, const TCHAR* DebugName = nullptr);` — Convert old FRawMesh format to MeshDescription.
- L90 _public prototype_ `static void AppendMeshDescription(const FMeshDescription& SourceMesh, FMeshDescription& TargetMesh, const FAppendSettings& AppendSettings);`
- L91 _public prototype_ `static void AppendMeshDescriptions(const TArray<const FMeshDescription*>& SourceMeshes, FMeshDescription& TargetMesh, const FAppendSettings& AppendSettings);`
- L99 _public prototype_ `static void HasInvalidVertexInstanceNormalsOrTangents(const FMeshDescription& MeshDescription, bool& bHasInvalidNormals, bool& bHasInvalidTangents);` — Check the mesh description's vertex instance normals and tangents to see if any of the values are invalid (e.g. nearly zero or they contain a NaN). \note This does not check if the vectors are normalized (which they should for correct normals and tangents). \param MeshDescription The mesh description object to check. \param bHasInvalidNormals The vertex instance normal attribute contains a near zero-length vector or a NaN component value. \param bHasInvalidTangents The vertex instance tangent attribute contains a near zero-length vector or a NaN component value.
- L102 _public function_ `static void AreNormalsAndTangentsValid(const FMeshDescription& MeshDescription, bool& bHasInvalidNormals, bool& bHasInvalidTangents)` — `UE_DEPRECATED(5.5, "Use HasInvalidVertexInstanceNormalsOrTangents")`
- L109 _public prototype_ `static void FindOverlappingCorners(FOverlappingCorners& OverlappingCorners, const FMeshDescription& MeshDescription, float ComparisonThreshold);` — Find all overlapping vertex using the threshold in the mesh description.
- L112 _public prototype_ `static int32 GetUVChartCount(FMeshDescription& MeshDescription, int32 SrcLightmapIndex, ELightmapUVVersion LightmapUVVersion, const FOverlappingCorners& OverlappingCorners);` — Find all charts in the mesh description.
- L128 _public prototype_ `static bool CreateLightMapUVLayout(FMeshDescription& MeshDescription, int32 SrcLightmapIndex, int32 DstLightmapIndex, int32 MinLightmapResolution, ELightmapUVVersion LightmapUVVersion, const FOverlappingCorners& OverlappingCorners);` — Find and pack UV charts for lightmap. The packing algorithm uses a rasterization method, hence the resolution parameter. If the given minimum resolution is not enough to handle all the charts, generation will fail. @param MeshDescription        Edited mesh @param SrcLightmapIndex       index of the source UV channel @param DstLightmapIndex       index of the destination UV channel @param MinLightmapResolution  Minimum resolution used for the packing @param LightmapUVVersion      Algorithm version @param OverlappingCorners     Overlapping corners of the given mesh @return                       UV layout correctly generated
- L137 _public prototype_ `static bool GenerateUniqueUVsForStaticMesh(const FMeshDescription& MeshDescription, int32 TextureResolution, bool bMergeIdenticalMaterials, TArray<FVector2D>& OutTexCoords);` — `UE_DEPRECATED(5.4, "Please use GenerateUV() instead.")` — Create some UVs from the specified mesh description data.
- L161 _public prototype_ `static bool GenerateUV(const FMeshDescription& MeshDescription, const FGenerateUVOptions& Options, TArray<FVector2D>& OutTexCoords);` — Generate UV coordinates from the specified mesh description data.
- L164 _public prototype_ `static bool AddUVChannel(FMeshDescription& MeshDescription);` — Add a UV channel to the MeshDescription.
- L167 _public prototype_ `static bool InsertUVChannel(FMeshDescription& MeshDescription, int32 UVChannelIndex);` — Insert a UV channel at the given index to the MeshDescription.
- L170 _public prototype_ `static bool RemoveUVChannel(FMeshDescription& MeshDescription, int32 UVChannelIndex);` — Remove the UV channel at the given index from the MeshDescription.
- L173 _public prototype_ `static void GeneratePlanarUV(const FMeshDescription& MeshDescription, const FUVMapParameters& Params, TMap<FVertexInstanceID, FVector2D>& OutTexCoords);` — Generate planar UV mapping for the MeshDescription
- L176 _public prototype_ `static void GenerateCylindricalUV(FMeshDescription& MeshDescription, const FUVMapParameters& Params, TMap<FVertexInstanceID, FVector2D>& OutTexCoords);` — Generate cylindrical UV mapping for the MeshDescription
- L179 _public prototype_ `static void GenerateBoxUV(const FMeshDescription& MeshDescription, const FUVMapParameters& Params, TMap<FVertexInstanceID, FVector2D>& OutTexCoords);` — Generate box UV mapping for the MeshDescription
- L193 _public prototype_ `static void SwapPolygonPolygonGroup(FMeshDescription& MeshDescription, int32 SectionIndex, int32 TriangleIndexStart, int32 TriangleIndexEnd, bool bRemoveEmptyPolygonGroup);` — Move some polygon to a new PolygonGroup(section) SectionIndex: The target section we want to assign the polygon. See bRemoveEmptyPolygonGroup to know how its used TriangleIndexStart: The triangle index is compute as follow: foreach polygon {TriangleIndex += Polygon->NumberTriangles} TriangleIndexEnd: The triangle index is compute as follow: foreach polygon {TriangleIndex += Polygon->NumberTriangles} bRemoveEmptyPolygonGroup: If true, any polygonGroup that is empty after moving a polygon will be delete. This parameter impact how SectionIndex is use If param is true  : PolygonGroupTargetID.GetValue() do not necessary equal SectionIndex in case there is less sections then SectionIndex If param is false : PolygonGroupTargetID.GetValue() equal SectionIndex, we will add all necessary missing PolygonGroupID (this can generate empty PolygonGroupID)
- L195 _public prototype_ `static void ConvertHardEdgesToSmoothGroup(const FMeshDescription& SourceMeshDescription, TArray<uint32>& FaceSmoothingMasks);`
- L197 _public prototype_ `static void ConvertSmoothGroupToHardEdges(const TArray<uint32>& FaceSmoothingMasks, FMeshDescription& DestinationMeshDescription);`
- L199 _public prototype_ `static bool HasVertexColor(const FMeshDescription& MeshDescription);`
- L201 _public prototype_ `static void BuildWeldedVertexIDRemap(const FMeshDescription& MeshDescription, const float WeldingThreshold, TMap<FVertexID, FVertexID>& OutVertexIDRemap);`
- L206 _public prototype_ `static FSHAHash ComputeSHAHash(const FMeshDescription& MeshDescription, bool bSkipTransientAttributes = false);` — Computes the SHA hash of all the attributes values in the MeshDescription. @param bSkipTransientAttributes     If param is true, do not include transient attributes in the hash computation.
- L209 _public prototype_ `static void FlipPolygons(FMeshDescription& MeshDescription);` — Flip the facing for a set of input polygons.
- L215 _public prototype_ `static void ApplyTransform(FMeshDescription& MeshDescription, const FTransform& Transform, bool bApplyCorrectNormalTransform = false);` — Transforms the MeshDescription data using the provided transform. @param bApplyCorrectNormalTransform Whether to correctly transform normals and tangents. Otherwise, will match the UE renderer and transform them without scale.
- L216 _public prototype_ `static void ApplyTransform(FMeshDescription& MeshDescription, const FMatrix& Transform, bool bApplyCorrectNormalTransform = false);`
- L222 _public prototype_ `static int32 GetUniqueVertexCount(const FMeshDescription& MeshDescription);` — Return the number of unique vertices, unique vertices are the result of welding all similar vertex instances (position, UV, tangent space, color,...)
- L223 _public prototype_ `static int32 GetUniqueVertexCount(const FMeshDescription& MeshDescription, const FOverlappingCorners& OverlappingCorners);`
- L231 _public prototype_ `static void ReorderMeshDescriptionPolygonGroups(const FMeshDescription& SourceMeshDescription , FMeshDescription& DestinationMeshDescription , TOptional<const FString> UnmatchMaterialNameWarning , TOptional<const FString> DestinationPolygonGroupCountDifferFromSource_Msg);` — Reorder the destination mesh description polygon groups in the same order has the source mesh description polygon groups. This function use the imported material name to reorder the section. Note: The material count MUST be the same for both the source and the destination. It will not reorder anything if the count is different.
- L237 _public prototype_ `static bool ValidateAndFixData(FMeshDescription& MeshDescription, const FString& DebugName);` — Verify the mesh data does not contain any NAN or INF float value, if such a case happen the value are set to zero or identity for matrix or quat.
- L240 _public prototype_ `static float ComputeMeshArea(const FMeshDescription& InMeshDescription);` — Compute the surface area of the mesh by iterating over each triangle.

#### struct `FStaticMeshOperations::FAppendSettings`  
`struct FAppendSettings`  
_L49-62_
- L56 _public member_ `FAppendPolygonGroupsDelegate PolygonGroupsDelegate;`
- L57 _public member_ `bool bMergeVertexColor = true;`
- L58 _public member_ `bool bMergeUVChannels[MAX_NUM_UV_CHANNELS] = {true};`
- L59 _public member_ `bool bMergeObjectName = false;`
- L60 _public member_ `FVector MergedAssetPivot = FVector::ZeroVector;`
- L61 _public member_ `TOptional<FTransform> MeshTransform;` — Apply a transformation on source mesh (see MeshTransform)

#### enum `FStaticMeshOperations::FAppendSettings::(anonymous)`  
``  
_L52-54_

#### enum `FStaticMeshOperations::EGenerateUVMethod`  
`enum class EGenerateUVMethod`  
_L139-146_
- L141 _public enumerator_ `Default`
- L142 _public enumerator_ `Legacy`
- L143 _public enumerator_ `UVAtlas`
- L144 _public enumerator_ `XAtlas`
- L145 _public enumerator_ `PatchBuilder`

#### struct `FStaticMeshOperations::FGenerateUVOptions`  
`struct FGenerateUVOptions`  
_L148-158_
- L151 _public member_ `int32 TextureResolution = 512;` — Expected texture resolution
- L154 _public member_ `bool bMergeTrianglesWithIdenticalAttributes = false;` — Wether to fold triangles sharing the same UVs & vertex colors in the generated UV mapping.
- L157 _public member_ `EGenerateUVMethod UVMethod = EGenerateUVMethod::Default;` — Method to use when generating UVs

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TMap<FPolygonGroupID, FPolygonGroupID> PolygonGroupMap;`
- L30 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStaticMeshOperations, Log, All);`
- L30 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStaticMeshOperations, Log, All);`
- L32 _delegate_ `DECLARE_DELEGATE_ThreeParams(FAppendPolygonGroupsDelegate, const FMeshDescription& , FMeshDescription& , PolygonGroupMap& ) enum class EComputeNTBsFlags : uint32 { None = 0x00000000,`
- L44 _prototype_ `ENUM_CLASS_FLAGS(EComputeNTBsFlags);`
- L53 _enumerator_ `MAX_NUM_UV_CHANNELS = 8` (scope `FStaticMeshOperations::FAppendSettings::__anonaac185ae0103`)

### `Source/Runtime/StaticMeshDescription/Public/UVMapSettings.h` (Public)


#### struct `FUVMapSettings`  
`struct FUVMapSettings`  
_L13-46_
- reflection: `USTRUCT(BlueprintType)`
- desc: UV map generation settings that are exposed to the user for scripting and through the editor
- L19 _public member_ `FVector Size;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UVMapSettings)` — Length, width, height of the UV mapping gizmo
- L23 _public member_ `FVector2D UVTile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UVMapSettings)` — Tiling of the UV mapping
- L27 _public member_ `FVector Position;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GizmoTransform)` — Position of the UV mapping gizmo
- L31 _public member_ `FRotator Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GizmoTransform)` — Rotation of the UV mapping gizmo (angles in degrees)
- L35 _public member_ `FVector Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GizmoTransform)` — Scale of the UV mapping gizmo
- L38 _public function_ `FUVMapSettings() : Size(1.0f) , UVTile(1.0f, 1.0f) , Position(0.0f) , Rotation(0) , Scale(1.0f)` — Default settings

#### struct `FUVMapParameters`  
`struct FUVMapParameters`  
_L48-83_
- L51 _public member_ `FVector Size;` — Length, width, height of the UV mapping gizmo
- L54 _public member_ `FVector2D UVTile;` — Tiling of the UV mapping
- L57 _public member_ `FVector Position;` — Position of the UV mapping gizmo
- L60 _public member_ `FQuat Rotation;` — Rotation of the UV mapping gizmo (angles in degrees)
- L63 _public member_ `FVector Scale;` — Scale of the UV mapping gizmo
- L66 _public function_ `FUVMapParameters() : Size(1.0f) , UVTile(1.0f, 1.0f) , Position(0.0f) , Rotation(ForceInit) , Scale(1.0f)` — Default settings
- L75 _public function_ `FUVMapParameters(const FVector& InPosition, const FQuat& InRotation, const FVector& InSize, const FVector& InScale, const FVector2D& InUVTile) : Size(InSize) , UVTile(InUVTile) , Position(InPosition) , Rotation(InRotation) , Scale(InScale)`
