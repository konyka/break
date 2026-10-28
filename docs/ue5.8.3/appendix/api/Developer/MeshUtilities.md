# Developer / MeshUtilities

- module root: `Source/Developer/MeshUtilities`
- headers: 4; symbols: 206
- symbol kinds: class=3, delegate=1, enum=1, enumerator=4, function=12, macro=1, member=74, namespace=5, prototype=88, struct=13, typedef=4
- DynamicallyLoadedModuleNames: AnimationBlueprintEditor, AnimationEditor, MaterialBaking, MeshMergeUtilities, SkeletalMeshEditor
- PrivateDependencyModuleNames: ClothingSystemRuntimeCommon, Core, CoreUObject, EditorFramework, Engine, GraphColor, HierarchicalLODUtilities, Landscape, LevelEditor, MeshBoneReduction, MeshBuilderCommon, MeshDescription, MeshUtilitiesCommon, MeshUtilitiesEngine, Persona, PropertyEditor, RHI, RawMesh, RenderCore, SkeletalMeshUtilitiesCommon, Slate, SlateCore, StaticMeshDescription, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: AnimationBlueprintEditor, AnimationEditor, MaterialBaking, SkeletalMeshEditor
- PublicDependencyModuleNames: MaterialUtilities
- PublicIncludePathModuleNames: MeshMergeUtilities

### `Source/Developer/MeshUtilities/Private/MeshRepresentationCommon.h` (Private)


#### struct `FEmbreeTriangleDesc`  
`struct FEmbreeTriangleDesc`  
_L24-33_
- L26 _public member_ `int16 ElementIndex;`
- L28 _public function_ `bool IsTwoSided() const`

#### struct `FEmbreeGeometryAsset`  
`struct FEmbreeGeometryAsset`  
_L35-48_
- L37 _public member_ `TArray<uint32> IndexArray;`
- L38 _public member_ `TArray<FVector3f> VertexArray;`
- L39 _public member_ `TArray<FEmbreeTriangleDesc> TriangleDescs;` — The material ID of each triangle.
- L41 _public member_ `uint32 NumVertices;`
- L42 _public member_ `uint32 NumTriangles;`
- L44 _public member_ `uint32 SectionNumTwoSidedTriangles;`
- L45 _public member_ `uint32 SectionNumTriangles;`
- L47 _public member_ `RTCScene Scene = nullptr;`

#### struct `FEmbreeGeometry`  
`struct FEmbreeGeometry`  
_L50-54_
- L52 _public member_ `const FEmbreeGeometryAsset* Asset;`
- L53 _public member_ `uint32 GeometryId = RTC_INVALID_GEOMETRY_ID;`

#### class `FEmbreeScene`  
`class FEmbreeScene`  
_L56-84_
- L60 _public prototype_ `const FEmbreeGeometryAsset* AddGeometryAsset( const FSourceMeshDataForDerivedDataTask* SourceMeshData, const FStaticMeshLODResources* LODModel, TConstArrayView<FSignedDistanceFieldBuildSectionData> SectionData, bool bIncludeTranslucentTriangles, bool bInstantiable);`
- L67 _public prototype_ `const FEmbreeGeometry* AddGeometry(const FEmbreeGeometryAsset* GeometryAsset);`
- L69 _public prototype_ `const FEmbreeGeometry* AddGeometryInstance(const FEmbreeGeometryAsset* GeometryAsset, const FMatrix44f& Transform);`
- L71 _public prototype_ `void Commit();`
- L73 _public member_ `FString MeshName;`
- L74 _public member_ `bool bGenerateAsIfTwoSided = false;`
- L76 _public member_ `RTCDevice Device = nullptr;`
- L77 _public member_ `RTCScene Scene = nullptr;`
- L79 _public member_ `TIndirectArray<FEmbreeGeometryAsset> GeometryAssets;`
- L80 _public member_ `TIndirectArray<FEmbreeGeometry> Geometries;`
- L82 _public member_ `int32 NumTrianglesTotal = 0;`
- L83 _public member_ `bool bMostlyTwoSided = false;`

#### struct `FEmbreeRay`  
`struct FEmbreeRay : public RTCRayHit`  
_L87-113_
- inherits: `RTCRayHit`
- L89 _public function_ `FEmbreeRay() : ElementIndex(-1)`
- L100 _public function_ `FVector3f GetHitNormal() const`
- L105 _public function_ `bool IsHitTwoSided() const`
- L112 _public member_ `int32 ElementIndex;` — Additional Outputs.

#### struct `FEmbreeRayQueryContext`  
`struct FEmbreeRayQueryContext : public RTCRayQueryContext`  
_L116-140_
- inherits: `RTCRayQueryContext`
- L118 _public function_ `FEmbreeRayQueryContext() : ElementIndex(-1)`
- L129 _public function_ `bool IsHitTwoSided() const`
- L136 _public member_ `int32 SkipPrimId = RTC_INVALID_GEOMETRY_ID;` — Hit against this primitive will be ignored
- L139 _public member_ `int32 ElementIndex;` — Additional Outputs.

#### Free symbols / members of external scopes

- L16 _macro_ `#define RTC_INVALID_GEOMETRY_ID ((unsigned int)-1)`
- L17 _typedef_ `typedef void* RTCDevice;`
- L18 _typedef_ `typedef void* RTCScene;`
- L19 _typedef_ `typedef void* RTCGeometry;`
- L144 _namespace_ `namespace MeshRepresentation`
- L147 _prototype_ `void SetupEmbreeScene(FString MeshName, bool bGenerateAsIfTwoSided, FEmbreeScene& OutEmbreeScene);` (scope `MeshRepresentation`)
- L149 _prototype_ `void DeleteEmbreeScene(FEmbreeScene& EmbreeScene);` (scope `MeshRepresentation`)
- L151 _prototype_ `int64_t MemoryEstimateForEmbreeScene(uint64_t IndexCount);` (scope `MeshRepresentation`)
- L153 _prototype_ `bool AddMeshDataToEmbreeScene(FEmbreeScene& EmbreeScene, const FMeshDataForDerivedDataTask& MeshData, bool bIncludeTranslucentTriangles);` (scope `MeshRepresentation`)

### `Source/Developer/MeshUtilities/Private/MeshUtilitiesPrivate.h` (Private)


#### class `FMeshUtilities`  
`class FMeshUtilities : public IMeshUtilities`  
_L18-181_
- inherits: `IMeshUtilities`
- L22 _private member_ `FString VersionString;` — Cached version string.
- L24 _private member_ `bool bUsingNvTriStrip;` — True if NvTriStrip is being used for tri order optimization.
- L26 _private member_ `bool bDisableTriangleOrderOptimization;` — True if we disable triangle order optimization.  For debugging purposes only
- L29 _private function_ `virtual const FString& GetVersionString() const override` — IMeshUtilities interface.
- L34 _private prototype_ `virtual void FixupMaterialSlotNames(UStaticMesh* StaticMesh) const override;`
- L36 _private prototype_ `virtual void FixupMaterialSlotNames(USkeletalMesh* SkeletalMesh) const override;`
- L38 _private prototype_ `virtual bool BuildStaticMesh( FStaticMeshRenderData& OutRenderData, UStaticMesh* StaticMesh, const FStaticMeshLODGroup& LODGroup ) override;`
- L44 _private prototype_ `virtual void BuildStaticMeshVertexAndIndexBuffers( TArray<FStaticMeshBuildVertex>& OutVertices, TArray<TArray<uint32> >& OutPerSectionIndices, TArray<int32>& OutWedgeMap, const FRawMesh& RawMesh, const FOverlappingCorners& OverlappingCorners, const TMap<uint32, uint32>& MaterialToSectionMapping, float ComparisonThreshold, FVector3f BuildScale, int32 ImportVersion ) override;`
- L56 _private prototype_ `virtual bool GenerateStaticMeshLODs(UStaticMesh* StaticMesh, const FStaticMeshLODGroup& LODGroup) override;`
- L59 _private prototype_ `virtual int64_t MemoryForGenerateSignedDistanceFieldVolumeData( const FMeshDataForDerivedDataTask& MeshData, float DistanceFieldResolutionScale );`
- L65 _private prototype_ `virtual void GenerateSignedDistanceFieldVolumeData( FString MeshName, const FMeshDataForDerivedDataTask& MeshData, float DistanceFieldResolutionScale, bool bGenerateAsIfTwoSided, class FDistanceFieldVolumeData& OutData) override;` — Builds a signed distance field volume for the given mesh.
- L72 _private prototype_ `virtual int64 MemoryForGenerateMeshCardRepresentation(uint64_t IndexCount);`
- L74 _private prototype_ `virtual bool GenerateCardRepresentationData( FString MeshName, const FMeshDataForDerivedDataTask& MeshData, const FDistanceFieldVolumeData* DistanceFieldVolumeData, int32 MaxLumenMeshCards, bool bGenerateAsIfTwoSided, class FCardRepresentationData& OutData) override;`
- L82 _private prototype_ `virtual void RecomputeTangentsAndNormalsForRawMesh(bool bRecomputeTangents, bool bRecomputeNormals, const FMeshBuildSettings& InBuildSettings, FRawMesh &OutRawMesh) const override;`
- L83 _private prototype_ `virtual void RecomputeTangentsAndNormalsForRawMesh(bool bRecomputeTangents, bool bRecomputeNormals, const FMeshBuildSettings& InBuildSettings, const FOverlappingCorners& InOverlappingCorners, FRawMesh &OutRawMesh) const override;`
- L85 _private prototype_ `virtual bool GenerateUniqueUVsForStaticMesh(const FRawMesh& RawMesh, int32 TextureResolution, TArray<FVector2f>& OutTexCoords) const override;`
- L86 _private prototype_ `virtual bool GenerateUniqueUVsForStaticMesh(const FRawMesh& RawMesh, int32 TextureResolution, bool bMergeIdenticalMaterials, TArray<FVector2f>& OutTexCoords) const override;`
- L88 _private prototype_ `virtual bool BuildSkeletalMesh(FSkeletalMeshLODModel& LODModel, const FString& SkeletalMeshName, const FReferenceSkeleton& RefSkeleton, const TArray<SkeletalMeshImportData::FVertInfluence>& Influences, const TArray<SkeletalMeshImportData::FMeshWedge>& Wedges, const TArray<SkeletalMeshImportData::FMeshFace>& Faces, const TArray<FVector3f>& Points, const TArray<int32>& PointToOriginalMap, const MeshBuildOptions& BuildOptions = MeshBuildOptions(), TArray<FText> * OutWarningMessages = nullptr, TArray<FName> * OutWarningNames = nullptr) override;`
- L90 _private prototype_ `virtual void CacheOptimizeIndexBuffer(TArray<uint16>& Indices) override;`
- L91 _private prototype_ `virtual void CacheOptimizeIndexBuffer(TArray<uint32>& Indices) override;`
- L92 _private prototype_ `void CacheOptimizeVertexAndIndexBuffer(TArray<FStaticMeshBuildVertex>& Vertices, TArray<TArray<uint32> >& PerSectionIndices, TArray<int32>& WedgeMap);`
- L94 _private prototype_ `virtual void BuildSkeletalAdjacencyIndexBuffer( const TArray<FSoftSkinVertex>& VertexBuffer, const uint32 TexCoordCount, const TArray<uint32>& Indices, TArray<uint32>& OutPnAenIndices ) override;`
- L112 _private prototype_ `virtual void CalculateTriangleTangent(const FSoftSkinVertex& VertexA, const FSoftSkinVertex& VertexB, const FSoftSkinVertex& VertexC, TArray<FVector3f>& OutTangents, float CompareThreshold) override;` — Calculate The tangent bi normal and normal for the triangle define by the tree SoftSkinVertex. @note The function will always fill properly the OutTangents array with 3 FVector. If the triangle is degenerated the OutTangent will contain zeroed vectors. @param VertexA - First triangle vertex. @param VertexB - Second triangle vertex. @param VertexC - Third triangle vertex. @param OutTangents - The function allocate the TArray with 3 FVector, to represent the triangle tangent, bi normal and normal. @param CompareThreshold - The threshold use to compare a tangent vector with zero.
- L114 _private prototype_ `virtual void CalcBoneVertInfos(USkeletalMesh* SkeletalMesh, TArray<FBoneVertInfo>& Infos, bool bOnlyDominant, int32 LodIndex = 0) override;`
- L123 _private prototype_ `virtual UStaticMesh* ConvertMeshesToStaticMesh(const TArray<UMeshComponent*>& InMeshComponents, const FTransform& InRootTransform = FTransform::Identity, const FString& InPackageName = FString()) override;` — Convert a set of mesh components in their current pose to a static mesh. @param	InMeshComponents		The mesh components we want to convert @param	InRootTransform			The transform of the root of the mesh we want to output @param	InPackageName			The package name to create the static mesh in. If this is empty then a dialog will be displayed to pick the mesh. @return a new static mesh (specified by the user)
- L133 _private prototype_ `void BuildSkeletalModelFromChunks(FSkeletalMeshLODModel& LODModel, const FReferenceSkeleton& RefSkeleton, TArray<FSkinnedMeshChunk*>& Chunks, const TArray<int32>& PointToOriginalMap, bool bCacheOptimize = true);` — Builds a renderable skeletal mesh LOD model. Note that the array of chunks will be destroyed during this process! @param LODModel				Upon return contains a renderable skeletal mesh LOD model. @param RefSkeleton			The reference skeleton associated with the model. @param Chunks				Skinned mesh chunks from which to build the renderable model. @param PointToOriginalMap	Maps a vertex's RawPointIdx to its index at import time.
- L135 _private prototype_ `virtual void FindOverlappingCorners(FOverlappingCorners& OutOverlappingCorners, const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, float ComparisonThreshold) const override;`
- L137 _private prototype_ `void FindOverlappingCorners(FOverlappingCorners& OutOverlappingCorners, FRawMesh const& RawMesh, float ComparisonThreshold) const;`
- L139 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface.
- L140 _private prototype_ `virtual void ShutdownModule() override;`
- L142 _private prototype_ `virtual void ExtractMeshDataForGeometryCache(FRawMesh& RawMesh, const FMeshBuildSettings& BuildSettings, TArray<FStaticMeshBuildVertex>& OutVertices, TArray<TArray<uint32> >& OutPerSectionIndices, int32 ImportVersion);`
- L144 _private prototype_ `virtual void CalculateTextureCoordinateBoundsForSkeletalMesh(const FSkeletalMeshLODModel& LODModel, TArray<FBox2D>& OutBounds) const override;`
- L146 _private prototype_ `virtual bool GenerateUniqueUVsForSkeletalMesh(const FSkeletalMeshLODModel& LODModel, int32 TextureResolution, TArray<FVector2f>& OutTexCoords) const override;`
- L148 _private prototype_ `virtual bool RemoveBonesFromMesh(USkeletalMesh* SkeletalMesh, int32 LODIndex, const TArray<FName>* BoneNamesToRemove) const override;`
- L149 _private prototype_ `virtual bool GetBoneReductionData(const USkeletalMesh* SkeletalMesh, int32 LODIndex, TMap<uint16, uint16>& OutBonesToReplace) const override;`
- L151 _private prototype_ `virtual void CalculateTangents(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, const TArray<FVector2f>& InUVs, const TArray<uint32>& InSmoothingGroupIndices, const uint32 InTangentOptions, TArray<FVector3f>& OutTangentX, TArray<FVector3f>& OutTangentY, TArray<FVector3f>& OutNormals) const override;`
- L152 _private prototype_ `virtual void CalculateMikkTSpaceTangents(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, const TArray<FVector2f>& InUVs, const TArray<FVector3f>& InNormals, bool bIgnoreDegenerateTriangles, TArray<FVector3f>& OutTangentX, TArray<FVector3f>& OutTangentY) const override;`
- L153 _private prototype_ `virtual void CalculateNormals(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, const TArray<FVector2f>& InUVs, const TArray<uint32>& InSmoothingGroupIndices, const uint32 InTangentOptions, TArray<FVector3f>& OutNormals) const override;`
- L154 _private prototype_ `virtual void CalculateOverlappingCorners(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, bool bIgnoreDegenerateTriangles, FOverlappingCorners& OutOverlappingCorners) const override;`
- L156 _private prototype_ `virtual void GenerateRuntimeSkinWeightData(const FSkeletalMeshLODModel* ImportedModel, const TArray<FRawSkinWeight>& InRawSkinWeights, bool bInUseHighPrecisionWeights, FRuntimeSkinWeightProfileData& InOutSkinWeightOverrideData, const FSkeletalMeshUnifiedBoneIndices* UnifiedBoneIndices = nullptr) const override;`
- L158 _private prototype_ `virtual void CreateImportDataFromLODModel(USkeletalMesh* SkeletalMesh, bool bInResetReductionAsNeeded) const override;`
- L160 _private prototype_ `void RegisterMenus();`
- L166 _protected prototype_ `void AddMakeStaticMeshEntryToToolMenu(FName InToolbarName);`
- L168 _protected prototype_ `void AddLevelViewportMenuExtender();`
- L170 _protected prototype_ `void RemoveLevelViewportMenuExtender();`
- L172 _protected prototype_ `TSharedRef<FExtender> GetLevelViewportContextMenuExtender(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> InActors);`
- L174 _protected prototype_ `void ConvertActorMeshesToStaticMeshUIAction(const TArray<AActor*> InActors);`
- L176 _protected member_ `FDelegateHandle ModuleLoadedDelegateHandle;`
- L177 _protected member_ `FDelegateHandle LevelViewportExtenderHandle;`
- L178 _protected member_ `FDelegateHandle AnimationBlueprintEditorExtenderHandle;`
- L179 _protected member_ `FDelegateHandle AnimationEditorExtenderHandle;`
- L180 _protected member_ `FDelegateHandle SkeletonEditorExtenderHandle;`

#### Free symbols / members of external scopes

- L183 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshUtilities, Verbose, All);`
- L183 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshUtilities, Verbose, All);`
- L184 _namespace_ `namespace MeshUtilities`
- L187 _prototype_ `void GenerateStratifiedUniformHemisphereSamples(int32 NumSamples, FRandomStream& RandomStream, TArray<FVector3f>& Samples);` (scope `MeshUtilities`) — Generates unit length, stratified and uniformly distributed direction samples in a hemisphere.

### `Source/Developer/MeshUtilities/Private/SkeletalMeshTools.h` (Private)


#### struct `FSkeletalMeshVertIndexAndZ`  
`struct FSkeletalMeshVertIndexAndZ`  
_L19-23_
- desc: this is used for a sub-quadratic routine to find "equal" verts
- L21 _public member_ `int32 Index;`
- L22 _public member_ `float Z;`

#### struct `FSoftSkinBuildVertex`  
`struct FSoftSkinBuildVertex`  
_L25-36_
- L27 _public member_ `FVector3f Position;`
- L28 _public member_ `FVector3f TangentX,` — Tangent, U-direction
- L29 _public member_ `TangentY,` — Binormal, V-direction
- L30 _public member_ `TangentZ;` — Normal
- L31 _public member_ `FVector2f UVs[MAX_TEXCOORDS];` — UVs
- L32 _public member_ `FColor Color;` — VertexColor
- L33 _public member_ `FBoneIndexType InfluenceBones[MAX_TOTAL_INFLUENCES];`
- L34 _public member_ `uint16 InfluenceWeights[MAX_TOTAL_INFLUENCES];`
- L35 _public member_ `uint32 PointWedgeIdx;`

#### struct `FSkinnedMeshChunk`  
`struct FSkinnedMeshChunk`  
_L42-56_
- desc: A chunk of skinned mesh vertices used as intermediate data to build a renderable skinned mesh.
- L45 _public member_ `int32 MaterialIndex;` — The material index with which this chunk should be rendered.
- L47 _public member_ `int32 OriginalSectionIndex;` — The original section index for which this chunk was generated.
- L49 _public member_ `TArray<FSoftSkinBuildVertex> Vertices;` — The vertices associated with this chunk.
- L51 _public member_ `TArray<uint32> Indices;` — The indices of the triangles in this chunk.
- L53 _public member_ `TArray<FBoneIndexType> BoneMap;` — If not empty, contains a map from bones referenced in this chunk to the skeleton.
- L55 _public member_ `int32 ParentChunkSectionIndex;` — The parent original section index for which this chunk was generated. INDEX_NONE for parent the value of the parent for BONE child chunked

#### struct `FSkinnedModelData`  
`struct FSkinnedModelData`  
_L61-77_
- desc: Skinned model data needed to generate skinned mesh chunks for reprocessing.
- L64 _public member_ `TArray<FSoftSkinVertex> Vertices;` — Vertices of the model.
- L66 _public member_ `TArray<uint32> Indices;` — Indices of the model.
- L68 _public member_ `TArray<uint32> RawPointIndices;` — Contents of the model's RawPointIndices bulk data.
- L70 _public member_ `TArray<int32> MeshToImportVertexMap;` — Map of vertex index to the original import index.
- L72 _public member_ `TArray<FSkelMeshSection> Sections;` — Per-section information.
- L74 _public member_ `TIndirectArray<TArray<FBoneIndexType> > BoneMaps;` — Per-section bone maps.
- L76 _public member_ `int32 NumTexCoords;` — The number of valid texture coordinates.

#### Free symbols / members of external scopes

- L79 _namespace_ `namespace SkeletalMeshTools`
- L81 _function_ `inline bool SkeletalMesh_UVsEqual(const SkeletalMeshImportData::FMeshWedge& V1, const SkeletalMeshImportData::FMeshWedge& V2, const FOverlappingThresholds& OverlappingThresholds, const int32 UVIndex = 0)` (scope `SkeletalMeshTools`)
- L96 _prototype_ `bool AreSkelMeshVerticesEqual( const FSoftSkinBuildVertex& V1, const FSoftSkinBuildVertex& V2, const FOverlappingThresholds& OverlappingThresholds);` (scope `SkeletalMeshTools`) — @return true if V1 and V2 are equal
- L107 _prototype_ `void BuildSkeletalMeshChunks( const TArray<SkeletalMeshImportData::FMeshFace>& Faces, const TArray<FSoftSkinBuildVertex>& RawVertices, TArray<FSkeletalMeshVertIndexAndZ>& RawVertIndexAndZ, const FOverlappingThresholds &OverlappingThresholds, TArray<FSkinnedMeshChunk*>& OutChunks, bool& bOutTooManyVerts );` (scope `SkeletalMeshTools`) — Creates chunks and populates the vertex and index arrays inside each chunk @param Faces						List of raw faces @param RawVertices				List of raw created, unordered, unwelded vertices @param RawVertIndexAndZ			List of indices into the RawVertices array and each raw vertex Z position.  This is used for fast lookup of overlapping vertices @param OverlappingThresholds		The thresholds to use to compute overlap vertex instance @param OutChunks					Created array of chunks
- L114 _prototype_ `void ChunkSkinnedVertices(TArray<FSkinnedMeshChunk*>& Chunks, TMap<uint32, TArray<FBoneIndexType>>& AlternateBoneIDs, int32 MaxBonesPerChunk);` (scope `SkeletalMeshTools`) — Splits chunks to satisfy the requested maximum number of bones per chunk @param Chunks			Chunks to split. Upon return contains the results of splitting chunks. @param MaxBonesPerChunk	The maximum number of bones a chunk may reference.

### `Source/Developer/MeshUtilities/Public/MeshUtilities.h` (Public)


#### enum `ETangentOptions::Type`  
`enum Type`  
_L40-46_
- L42 _public enumerator_ `None = 0`
- L43 _public enumerator_ `BlendOverlappingNormals = 0x1`
- L44 _public enumerator_ `IgnoreDegenerateTriangles = 0x2`
- L45 _public enumerator_ `UseMikkTSpace = 0x4`

#### struct `FSignedDistanceFieldBuildSectionData`  
`struct FSignedDistanceFieldBuildSectionData`  
_L49-54_
- L51 _public member_ `EBlendMode BlendMode = BLEND_Opaque;`
- L52 _public member_ `bool bTwoSided = false;`
- L53 _public member_ `bool bAffectDistanceFieldLighting = true;`

#### struct `FSignedDistanceFieldBuildPartData`  
`struct FSignedDistanceFieldBuildPartData`  
_L56-60_
- L58 _public member_ `FSourceMeshDataForDerivedDataTask SourceMeshData;`
- L59 _public member_ `TArray<FSignedDistanceFieldBuildSectionData> SectionData;`

#### struct `FMeshDataForDerivedDataTask`  
`struct FMeshDataForDerivedDataTask`  
_L62-70_
- L64 _public member_ `const FSourceMeshDataForDerivedDataTask* SourceMeshData;`
- L65 _public member_ `const FStaticMeshLODResources* LODModel;`
- L66 _public member_ `TConstArrayView<FSignedDistanceFieldBuildSectionData> SectionData;`
- L67 _public member_ `TConstArrayView<FSignedDistanceFieldBuildPartData> Parts;`
- L68 _public member_ `TConstArrayView<FNaniteAssemblyNode> Nodes;`
- L69 _public member_ `FBoxSphereBounds3f Bounds;`

#### class `IMeshUtilities`  
`class IMeshUtilities : public IModuleInterface`  
_L74-421_
- inherits: `IModuleInterface`
- L87 _public prototype_ `virtual bool GenerateUniqueUVsForStaticMesh(const FRawMesh& RawMesh, int32 TextureResolution, TArray<FVector2f>& OutTexCoords) const = 0;` — Calculates (new) non-overlapping UV coordinates for the given Raw Mesh @param RawMesh - Raw Mesh to generate UV coordinates for @param TextureResolution - Texture resolution to take into account while generating the UVs @param bMergeIdenticalMaterials - Whether faces with identical materials can be treated as one in the resulting set of unique UVs @param OutTexCoords - New set of UV coordinates @return bool - whether or not generating the UVs succeeded
- L88 _public prototype_ `virtual bool GenerateUniqueUVsForStaticMesh(const FRawMesh& RawMesh, int32 TextureResolution, bool bMergeIdenticalMaterials, TArray<FVector2f>& OutTexCoords) const = 0;`
- L92 _public prototype_ `virtual const FString& GetVersionString() const = 0;` — Returns a string uniquely identifying this version of mesh utilities.
- L99 _public prototype_ `virtual void FixupMaterialSlotNames(UStaticMesh* StaticMesh) const = 0;` — Used to make sure all imported material slot name are unique and non empty. @param StaticMesh @param bForceUniqueSlotName	If true, make sure all slot names are unique as well.
- L106 _public prototype_ `virtual void FixupMaterialSlotNames(USkeletalMesh* SkeletalMesh) const = 0;` — Used to make sure all imported material slot name are unique and non empty. @param SkeletalMesh @param bForceUniqueSlotName	If true, make sure all slot names are unique as well.
- L112 _public prototype_ `virtual bool BuildStaticMesh( class FStaticMeshRenderData& OutRenderData, UStaticMesh* StaticMesh, const class FStaticMeshLODGroup& LODGroup ) = 0;` — Builds a renderable static mesh using the provided source models and the LOD groups settings. @returns true if the renderable mesh was built successfully.
- L118 _public prototype_ `virtual void BuildStaticMeshVertexAndIndexBuffers( TArray<FStaticMeshBuildVertex>& OutVertices, TArray<TArray<uint32> >& OutPerSectionIndices, TArray<int32>& OutWedgeMap, const FRawMesh& RawMesh, const FOverlappingCorners& OverlappingCorners, const TMap<uint32, uint32>& MaterialToSectionMapping, float ComparisonThreshold, FVector3f BuildScale, int32 ImportVersion ) = 0;`
- L135 _public prototype_ `virtual bool GenerateStaticMeshLODs( UStaticMesh* StaticMesh, const class FStaticMeshLODGroup& LODGroup ) = 0;` — Builds a static mesh using the provided source models and the LOD groups settings, and replaces the RawMeshes with the reduced meshes. Does not modify renderable data. @returns true if the meshes were built successfully.
- L141 _public prototype_ `virtual void GenerateSignedDistanceFieldVolumeData( FString MeshName, const FMeshDataForDerivedDataTask& MeshData, float DistanceFieldResolutionScale, bool bGenerateAsIfTwoSided, class FDistanceFieldVolumeData& OutData) = 0;` — Builds a signed distance field volume for the given mesh.
- L148 _public prototype_ `virtual int64_t MemoryForGenerateSignedDistanceFieldVolumeData( const FMeshDataForDerivedDataTask& MeshData, float DistanceFieldResolutionScale ) = 0;`
- L154 _public function_ `virtual void GenerateSignedDistanceFieldVolumeData( FString MeshName, const FSourceMeshDataForDerivedDataTask& SourceMeshData, const FStaticMeshLODResources& LODModel, class FQueuedThreadPool& ThreadPool, const TArray<FSignedDistanceFieldBuildSectionData>& SectionData, const FBoxSphereBounds3f& Bounds, float DistanceFieldResolutionScale, bool bGenerateAsIfTwoSided, class FDistanceFieldVolumeData& OutData)` — `UE_DEPRECATED(5.6, "Provide FMeshDataForDerivedDataTask instead.")`
- L174 _public prototype_ `virtual int64 MemoryForGenerateMeshCardRepresentation(uint64_t IndexCount) = 0;`
- L176 _public prototype_ `virtual bool GenerateCardRepresentationData( FString MeshName, const FMeshDataForDerivedDataTask& MeshData, const class FDistanceFieldVolumeData* DistanceFieldVolumeData, int32 MaxLumenMeshCards, bool bGenerateAsIfTwoSided, class FCardRepresentationData& OutData) = 0;`
- L185 _public function_ `virtual bool GenerateCardRepresentationData( FString MeshName, const FSourceMeshDataForDerivedDataTask& SourceMeshData, const FStaticMeshLODResources& LODModel, class FQueuedThreadPool& ThreadPool, const TArray<FSignedDistanceFieldBuildSectionData>& SectionData, const FBoxSphereBounds& Bounds, const class FDistanceFieldVolumeData* DistanceFieldVolumeData, int32 MaxLumenMeshCards, bool bGenerateAsIfTwoSided, class FCardRepresentationData& OutData)` — `UE_DEPRECATED(5.6, "Provide FMeshDataForDerivedDataTask instead.")`
- L250 _public prototype_ `virtual bool BuildSkeletalMesh( FSkeletalMeshLODModel& LODModel, const FString& SkeletalMeshName, const FReferenceSkeleton& RefSkeleton, const TArray<SkeletalMeshImportData::FVertInfluence>& Influences, const TArray<SkeletalMeshImportData::FMeshWedge>& Wedges, const TArray<SkeletalMeshImportData::FMeshFace>& Faces, const TArray<FVector3f>& Points, const TArray<int32>& PointToOriginalMap, const MeshBuildOptions& BuildOptions = MeshBuildOptions(), TArray<FText> * OutWarningMessages = NULL, TArray<FName> * OutWarningNames = NULL ) = 0;` — Create all render specific data for a skeletal mesh LOD model @returns true if the mesh was built successfully.
- L266 _public prototype_ `virtual void CacheOptimizeIndexBuffer(TArray<uint16>& Indices) = 0;` — Cache optimize the index buffer.
- L269 _public prototype_ `virtual void CacheOptimizeIndexBuffer(TArray<uint32>& Indices) = 0;` — Cache optimize the index buffer.
- L272 _public prototype_ `virtual void BuildSkeletalAdjacencyIndexBuffer( const TArray<struct FSoftSkinVertex>& VertexBuffer, const uint32 TexCoordCount, const TArray<uint32>& Indices, TArray<uint32>& OutPnAenIndices ) = 0;` — Build adjacency information for the skeletal mesh used for tessellation.
- L290 _public prototype_ `virtual void CalculateTriangleTangent(const FSoftSkinVertex& VertexA, const FSoftSkinVertex& VertexB, const FSoftSkinVertex& VertexC, TArray<FVector3f>& OutTangents, float CompareThreshold) = 0;` — Calculate The tangent, bi normal and normal for the triangle define by the tree SoftSkinVertex. @note The function will always fill properly the OutTangents array with 3 FVector. If the triangle is degenerated the OutTangent will contain zeroed vectors. @param VertexA - First triangle vertex. @param VertexB - Second triangle vertex. @param VertexC - Third triangle vertex. @param OutTangents - The function allocate the TArray with 3 FVector, to represent the triangle tangent, bi normal and normal. @param CompareThreshold - The threshold use to compare a tangent vector with zero.
- L300 _public prototype_ `virtual void CalcBoneVertInfos( USkeletalMesh* SkeletalMesh, TArray<FBoneVertInfo>& Infos, bool bOnlyDominant, int32 LodIndex = 0) = 0;` — Calculate the verts associated weighted to each bone of the skeleton. The vertices returned are in the local space of the bone. @param	SkeletalMesh	The target skeletal mesh. @param	Infos			The output array of vertices associated with each bone. @param	bOnlyDominant	Controls whether a vertex is added to the info for a bone if it is most controlled by that bone, or if that bone has ANY influence on that vert.
- L309 _public prototype_ `virtual UStaticMesh* ConvertMeshesToStaticMesh(const TArray<UMeshComponent*>& InMeshComponents, const FTransform& InRootTransform = FTransform::Identity, const FString& InPackageName = FString()) = 0;` — Convert a set of mesh components in their current pose to a static mesh. @param	InMeshComponents		The mesh components we want to convert @param	InRootTransform			The transform of the root of the mesh we want to output @param	InPackageName			The package name to create the static mesh in. If this is empty then a dialog will be displayed to pick the mesh. @return a new static mesh (specified by the user)
- L317 _public prototype_ `virtual void CalculateTextureCoordinateBoundsForSkeletalMesh(const FSkeletalMeshLODModel& LODModel, TArray<FBox2D>& OutBounds) const = 0;` — Calculates UV coordinates bounds for the given Skeletal Mesh @param InRawMesh - Skeletal Mesh to calculate the bounds for @param OutBounds - Out texture bounds (min-max)
- L326 _public prototype_ `virtual bool GenerateUniqueUVsForSkeletalMesh(const FSkeletalMeshLODModel& LODModel, int32 TextureResolution, TArray<FVector2f>& OutTexCoords) const = 0;` — Calculates (new) non-overlapping UV coordinates for the given Skeletal Mesh @param LODModel - Skeletal Mesh to generate UV coordinates for @param TextureResolution - Texture resolution to take into account while generating the UVs @param OutTexCoords - New set of UV coordinates @return bool - whether or not generating the UVs succeeded
- L337 _public prototype_ `virtual bool RemoveBonesFromMesh(USkeletalMesh* SkeletalMesh, int32 LODIndex, const TArray<FName>* BoneNamesToRemove) const = 0;` — Remove Bones based on LODInfo setting @param SkeletalMesh	Mesh that needs bones to be removed @param LODIndex		Desired LOD to remove bones [ 0 based ] @param BoneNamesToRemove	List of bone names to remove @return true if success
- L350 _public prototype_ `virtual bool GetBoneReductionData(const USkeletalMesh* SkeletalMesh, int32 LODIndex, TMap<uint16, uint16>& OutBonesToReplace) const = 0;` — Predict which bones bone reduction will remove for a given LOD and compute the reparent map. This is a read-only operation — it does not modify the mesh. Used by the unified bone map builder to determine reparent targets that need unified bone slots. @param SkeletalMesh		Mesh to inspect @param LODIndex			LOD to query @param OutBonesToReplace	Map of [removed bone index -> reparent target bone index] @return true if any bones would be removed
- L364 _public prototype_ `virtual void CalculateTangents(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, const TArray<FVector2f>& InUVs, const TArray<uint32>& InSmoothingGroupIndices, const uint32 InTangentOptions, TArray<FVector3f>& OutTangentX, TArray<FVector3f>& OutTangentY, TArray<FVector3f>& OutNormals) const = 0;` — Calculates Tangents and Normals for a given set of vertex data @param InVertices Vertices that make up the mesh @param InIndices Indices for the Vertex array @param InUVs Texture coordinates (per-index based) @param InSmoothingGroupIndices Smoothing group index (per-face based) @param InTangentOptions Flags for Tangent calculation @param OutTangentX Array to hold calculated Tangents @param OutTangentY Array to hold calculated Bitangents @param OutNormals Array to hold calculated normals (if already contains normals will use those instead for the tangent calculation)
- L377 _public prototype_ `virtual void CalculateMikkTSpaceTangents(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, const TArray<FVector2f>& InUVs, const TArray<FVector3f>& InNormals, bool bIgnoreDegenerateTriangles, TArray<FVector3f>& OutTangentX, TArray<FVector3f>& OutTangentY) const = 0;` — Calculates MikkTSpace Tangents for a given set of vertex data with normals provided @param InVertices Vertices that make up the mesh @param InIndices Indices for the Vertex array @param InUVs Texture coordinates (per-index based) @param InNormals Normals used for the tangent calculation (must be normalized) @param bIgnoreDegenerateTriangles Flag for MikkTSpace to skip degenerate triangles fix-up path @param OutTangentX Array to hold calculated Tangents @param OutTangentY Array to hold calculated Bitangents
- L389 _public prototype_ `virtual void CalculateNormals(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, const TArray<FVector2f>& InUVs, const TArray<uint32>& InSmoothingGroupIndices, const uint32 InTangentOptions, TArray<FVector3f>& OutNormals) const = 0;` — Calculates Normals for a given set of vertex data @param InVertices Vertices that make up the mesh @param InIndices Indices for the Vertex array @param InUVs Texture coordinates (per-index based) @param InSmoothingGroupIndices Smoothing group index (per-face based) @param InTangentOptions Flags for Tangent calculation @param OutNormals Array to hold calculated normals
- L399 _public prototype_ `virtual void CalculateOverlappingCorners(const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, bool bIgnoreDegenerateTriangles, FOverlappingCorners& OutOverlappingCorners) const = 0;` — Calculates the overlapping corners for a given set of vertex data @param InVertices Vertices that make up the mesh @param InIndices Indices for the Vertex array @param bIgnoreDegenerateTriangles Indicates if we should skip degenerate triangles @param OutOverlappingCorners Container to hold the overlapping corners. For a vertex, lists all the overlapping vertices.
- L401 _public prototype_ `virtual void RecomputeTangentsAndNormalsForRawMesh(bool bRecomputeTangents, bool bRecomputeNormals, const FMeshBuildSettings& InBuildSettings, FRawMesh &OutRawMesh) const = 0;`
- L402 _public prototype_ `virtual void RecomputeTangentsAndNormalsForRawMesh(bool bRecomputeTangents, bool bRecomputeNormals, const FMeshBuildSettings& InBuildSettings, const FOverlappingCorners& InOverlappingCorners, FRawMesh &OutRawMesh) const = 0;`
- L404 _public prototype_ `virtual void FindOverlappingCorners(FOverlappingCorners& OutOverlappingCorners, const TArray<FVector3f>& InVertices, const TArray<uint32>& InIndices, float ComparisonThreshold) const = 0;`
- L407 _public prototype_ `virtual void GenerateRuntimeSkinWeightData( const FSkeletalMeshLODModel* ImportedModel, const TArray<FRawSkinWeight>& InRawSkinWeights, bool bInUseHighPrecisionWeights, struct FRuntimeSkinWeightProfileData& InOutSkinWeightOverrideData, const FSkeletalMeshUnifiedBoneIndices* UnifiedBoneIndices = nullptr) const = 0;` — Used to generate runtime skin weight data from Editor-only data
- L420 _public prototype_ `virtual void CreateImportDataFromLODModel(USkeletalMesh* InSkeletalMesh, bool bInResetReductionAsNeeded = false) const = 0;` — This function create the import data using the LODModel. You can call this function if you load an asset that was not re-import since the build refactor and the chunking is more agressive than the bake data in the LODModel. You can also need this function if you create a skeletalmesh with LODModel instead of import data, so your newly created skeletalmesh can be build properly. If the LODModel is not being pulled out of the old reduction storage, and bInResetReductionAsNeeded is true, then the reduction settings for that LOD will be reset to avoid regenerating the mesh even more reduced.

#### struct `IMeshUtilities::MeshBuildOptions`  
`struct MeshBuildOptions`  
_L207-244_
- desc: Helper structure for skeletal mesh import options
- L209 _public function_ `MeshBuildOptions() : BoneInfluenceLimit(0) , bRemoveDegenerateTriangles(false) , bComputeNormals(true) , bComputeTangents(true) , bUseMikkTSpace(false) , bComputeWeightedNormals(false) , bCacheOptimize(true) , TargetPlatform(nullptr)`
- L221 _public member_ `int32 BoneInfluenceLimit;`
- L222 _public member_ `bool bRemoveDegenerateTriangles;`
- L223 _public member_ `bool bComputeNormals;`
- L224 _public member_ `bool bComputeTangents;`
- L225 _public member_ `bool bUseMikkTSpace;`
- L226 _public member_ `bool bComputeWeightedNormals;`
- L227 _public member_ `bool bCacheOptimize;`
- L228 _public member_ `FOverlappingThresholds OverlappingThresholds;`
- L229 _public member_ `const class ITargetPlatform* TargetPlatform;`
- L231 _public function_ `void FillOptions(const FSkeletalMeshBuildSettings& SkeletalMeshBuildSettings)`

#### Free symbols / members of external scopes

- L29 _typedef_ `typedef FIntPoint FMeshIdAndLOD;`
- L31 _namespace_ `namespace SkeletalMeshImportData`
- L38 _namespace_ `namespace ETangentOptions`
