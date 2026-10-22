# Developer / MeshBuilder

- module root: `Source/Developer/MeshBuilder`
- headers: 7; symbols: 98
- symbol kinds: class=8, delegate=4, function=23, macro=4, member=21, namespace=4, prototype=29, struct=5
- DynamicallyLoadedModuleNames: NaniteBuilder
- PrivateDependencyModuleNames: ClothingSystemRuntimeNv, Core, CoreUObject, Engine, MeshBoneReduction, MeshBuilderCommon, MeshDescription, MeshReductionInterface, MeshUtilities, RHI, RawMesh, RenderCore, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, StaticMeshDescription
- PrivateIncludePathModuleNames: NaniteBuilder
- PublicDependencyModuleNames: MeshUtilitiesCommon

### `Source/Developer/MeshBuilder/Private/BuildOptimizationHelper.h` (Private)


#### class `BuildOptimizationHelper`  
`class BuildOptimizationHelper`  
_L10-348_
- L191 _public function_ `static void BuildDepthOnlyIndexBuffer( TArray<uint32>& OutDepthIndices, const FConstMeshBuildVertexView& InVertices, const TArray<uint32>& InIndices, const TArrayView<FStaticMeshSection>& InSections )`
- L257 _public function_ `static void CacheOptimizeVertexAndIndexBuffer( FMeshBuildVertexData& Vertices, TArray<TArray<uint32> >& PerSectionIndices, TArray<int32>& WedgeMap )`

#### struct `BuildOptimizationHelper::FIndexAndZ`  
`struct FIndexAndZ`  
_L14-28_
- desc: Helper struct for building acceleration structures.
- L16 _public member_ `float Z;`
- L17 _public member_ `int32 Index;`
- L20 _public function_ `FIndexAndZ()` — Default constructor.
- L23 _public function_ `FIndexAndZ(int32 InIndex, FVector V)` — Initialization constructor.

#### struct `BuildOptimizationHelper::FCompareIndexAndZ`  
`struct FCompareIndexAndZ`  
_L31-34_
- desc: Sorting function for vertex Z/index pairs.
- L33 _public function_ `FORCEINLINE bool operator()(FIndexAndZ const& A, FIndexAndZ const& B) const`

#### struct `BuildOptimizationHelper::FMeshEdge`  
`struct FMeshEdge`  
_L36-40_
- L38 _public member_ `int32 Vertices[2];`
- L39 _public member_ `int32 Faces[2];`

#### class `BuildOptimizationHelper::FMeshEdgeBuilder`  
`class FMeshEdgeBuilder`  
_L47-189_
- desc: This helper class builds the edge list for a mesh. It uses a hash of vertex positions to edges sharing that vertex to remove the n^2 searching of all previously added edges.
- L53 _protected member_ `const TArray<uint32>& Indices;` — The list of indices to build the edge data from
- L57 _protected member_ `const FConstMeshBuildVertexView& Vertices;` — The array of verts for vertex position comparison
- L61 _protected member_ `TArray<FMeshEdge>& Edges;` — The array of edges to create
- L65 _protected member_ `TMultiMap<FVector, FMeshEdge*> VertexToEdgeList;` — List of edges that start with a given vertex
- L76 _protected function_ `inline FMeshEdge* FindOppositeEdge(int32 Index1, int32 Index2)` — Searches the list of edges to see if this one matches an existing and returns a pointer to it if it does @param Index1 the first index to check for @param Index2 the second index to check for @return nullptr if no edge was found, otherwise the edge that was found
- L105 _protected function_ `inline void AddEdge(int32 Index1, int32 Index2, int32 Triangle)` — Updates an existing edge if found or adds the new edge to the list @param Index1 the first index in the edge @param Index2 the second index in the edge @param Triangle the triangle that this edge was found in
- L132 _public function_ `FMeshEdgeBuilder( const TArray<uint32>& InIndices, const FConstMeshBuildVertexView& InVertices, TArray<FMeshEdge>& OutEdges ) : Indices(InIndices), Vertices(InVertices), Edges(OutEdges)` — Initializes the values for the code that will build the mesh edge list
- L146 _public prototype_ `virtual ~FMeshEdgeBuilder() = default;` — Virtual dtor
- L152 _public function_ `void FindEdges(void)` — Uses a hash of indices to edge lists so that it can avoid the n^2 search through the full edge list
- L184 _public function_ `inline bool DoesEdgeMatch(int32 Index1, int32 Index2, FMeshEdge* OtherEdge)` — This function determines whether a given edge matches or not for a static mesh @param Index1 The first index of the edge being checked @param Index2 The second index of the edge @param OtherEdge The edge to compare. Was found via the map @return true if the edge is a match, false otherwise

### `Source/Developer/MeshBuilder/Private/BuildStatisticManager.h` (Private)


#### struct `BuildStatisticManager::FStatisticData`  
`struct FStatisticData`  
_L12-21_
- L15 _public function_ `FStatisticData() : TotalTime(0.0) , Counter(0)`
- L19 _public member_ `double TotalTime;`
- L20 _public member_ `uint32 Counter;`

#### class `BuildStatisticManager::FBuildStatisticScope`  
`class FBuildStatisticScope`  
_L23-43_
- L26 _public function_ `FBuildStatisticScope(const FString& InTimerDescription, FStatisticData& InStatisticData) : TimerDescription(InTimerDescription) , StatisticData(InStatisticData)`
- L32 _public function_ `~FBuildStatisticScope()`
- L40 _private member_ `FString TimerDescription;`
- L41 _private member_ `int32 StartTime;`
- L42 _private member_ `FStatisticData& StatisticData;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshDescriptionBuildStatistic, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshDescriptionBuildStatistic, Log, All);`
- L10 _namespace_ `namespace BuildStatisticManager`

### `Source/Developer/MeshBuilder/Public/IMeshBuilderModule.h` (Public)


#### class `IMeshBuilderModule`  
`class IMeshBuilderModule : public IModuleInterface`  
_L18-60_
- inherits: `IModuleInterface`
- L21 _public function_ `static inline IMeshBuilderModule& GetForPlatform(const ITargetPlatform* TargetPlatform)`
- L27 _public function_ `static inline IMeshBuilderModule& GetForRunningPlatform()`
- L33 _public function_ `virtual void AppendToDDCKey(FString& DDCKey, bool bSkeletal)`
- L35 _public prototype_ `virtual bool BuildMesh(class FStaticMeshRenderData& OutRenderData, const struct FStaticMeshBuildParameters& BuildParameters) = 0;`
- L38 _public function_ `virtual bool BuildMesh(class FStaticMeshRenderData& OutRenderData, class UObject* Mesh, const class FStaticMeshLODGroup& LODGroup, bool bAllowNanite) final` — `UE_DEPRECATED(5.5, "Use FStaticMeshBuildParameters instead.")`
- L47 _public prototype_ `virtual bool BuildMeshVertexPositions(class UObject* StaticMesh, TArray<uint32>& Indices, TArray<FVector3f>& Vertices, FStaticMeshSectionArray& Sections) = 0;`
- L50 _public function_ `virtual bool BuildSkeletalMesh(const struct FSkeletalMeshBuildParameters& SkeletalMeshBuildParameters) final` — `UE_DEPRECATED(5.6, "Use the overload that takes an FSkeletalMeshRenderData instead.")`
- L57 _public prototype_ `virtual bool BuildSkeletalMesh(class FSkeletalMeshRenderData& OutRenderData, const struct FSkeletalMeshBuildParameters& SkeletalMeshBuildParameters) = 0;`
- L59 _public function_ `virtual void PostBuildSkeletalMesh(class FSkeletalMeshRenderData* SkeletalMeshRenderData, class USkinnedAsset* SkinnedAsset)`

### `Source/Developer/MeshBuilder/Public/MeshBuilder.h` (Public)


#### class `FMeshBuilder`  
`class FMeshBuilder`  
_L24-57_
- desc: Abstract class which is the base class of all builder. All share code to build some render data should be found inside this class
- L27 _public prototype_ `FMeshBuilder();`
- L32 _public prototype_ `virtual bool Build(FStaticMeshRenderData& OutRenderData, const FStaticMeshBuildParameters& BuildParameters) = 0;` — Build function should be override and is the starting point for static mesh builders
- L35 _public prototype_ `virtual bool Build( FStaticMeshRenderData& OutRenderData, UStaticMesh* StaticMesh, const FStaticMeshLODGroup& LODGroup, bool bAllowNanite) final;` — `UE_DEPRECATED(5.5, "Use FStaticMeshBuildParameters instead.")`
- L41 _public prototype_ `virtual bool BuildMeshVertexPositions( UStaticMesh* StaticMesh, TArray<uint32>& Indices, TArray<FVector3f>& Vertices, FStaticMeshSectionArray& Sections) = 0;`
- L50 _public prototype_ `virtual bool Build(FSkeletalMeshRenderData& OutRenderData, const FSkeletalMeshBuildParameters& SkeletalMeshBuildParameters) = 0;` — Build function should be override and is the starting point for skeletal mesh builders
- L53 _public prototype_ `virtual bool Build(const FSkeletalMeshBuildParameters& SkeletalMeshBuildParameters) final;` — `UE_DEPRECATED(5.6, "Use the overload that takes FSkeletalMeshRenderData instead")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHBUILDER_API`

### `Source/Developer/MeshBuilder/Public/MeshDescriptionHelper.h` (Public)


#### class `FMeshDescriptionHelper`  
`class FMeshDescriptionHelper`  
_L19-61_
- L23 _public prototype_ `FMeshDescriptionHelper(FMeshBuildSettings* InBuildSettings);`
- L26 _public prototype_ `void SetupRenderMeshDescription(UObject* Owner, FMeshDescription& RenderMeshDescription, bool bForNanite, bool bNeedTangents);` — Build a render mesh description with the BuildSettings. This will update the RenderMeshDescription in place
- L28 _public prototype_ `void ReduceLOD(const FMeshDescription& BaseMesh, FMeshDescription& DestMesh, const struct FMeshReductionSettings& ReductionSettings, const FOverlappingCorners& InOverlappingCorners, float &OutMaxDeviation);`
- L30 _public prototype_ `void FindOverlappingCorners(const FMeshDescription& MeshDescription, float ComparisonThreshold);`
- L32 _public function_ `const FOverlappingCorners& GetOverlappingCorners() const`
- L42 _private member_ `FMeshBuildSettings* BuildSettings;`
- L43 _private member_ `FOverlappingCorners OverlappingCorners;`

#### struct `FMeshDescriptionHelper::FFanFace`  
`struct FFanFace`  
_L52-59_
- desc: Smoothing group interpretation helper structure.
- L54 _public member_ `int32 FaceIndex;`
- L55 _public member_ `int32 LinkedVertexIndex;`
- L56 _public member_ `bool bFilled;`
- L57 _public member_ `bool bBlendTangents;`
- L58 _public member_ `bool bBlendNormals;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHBUILDER_API`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshBuilder, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshBuilder, Log, All);`

### `Source/Developer/MeshBuilder/Public/SkeletalMeshBuilder.h` (Public)


#### class `FSkeletalMeshBuilder`  
`class FSkeletalMeshBuilder : public FMeshBuilder`  
_L18-48_
- inherits: `FMeshBuilder`
- L21 _public prototype_ `FSkeletalMeshBuilder();`
- L24 _public function_ `virtual bool Build(FStaticMeshRenderData& OutRenderData, const struct FStaticMeshBuildParameters& BuildParameters) override` — No support for static mesh build in this class
- L31 _public function_ `virtual bool BuildMeshVertexPositions( UStaticMesh* StaticMesh, TArray<uint32>& Indices, TArray<FVector3f>& Vertices, FStaticMeshSectionArray& Sections) override`
- L42 _public prototype_ `virtual bool Build(FSkeletalMeshRenderData& OutRenderData, const struct FSkeletalMeshBuildParameters& SkeletalMeshBuildParameters) override;`
- L44 _public prototype_ `virtual ~FSkeletalMeshBuilder() = default;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHBUILDER_API`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshBuilder, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshBuilder, Log, All);`

### `Source/Developer/MeshBuilder/Public/StaticMeshBuilder.h` (Public)


#### class `FStaticMeshBuilder`  
`class FStaticMeshBuilder : public FMeshBuilder`  
_L20-49_
- inherits: `FMeshBuilder`
- L23 _public prototype_ `FStaticMeshBuilder();`
- L24 _public prototype_ `virtual ~FStaticMeshBuilder() = default;`
- L26 _public prototype_ `virtual bool Build(FStaticMeshRenderData& OutRenderData, const FStaticMeshBuildParameters& BuildParameters) override;`
- L29 _public function_ `virtual bool Build(FSkeletalMeshRenderData& OutRenderData, const struct FSkeletalMeshBuildParameters& SkeletalMeshBuildParameters) override` — No support for skeletal mesh build in this class
- L36 _public prototype_ `virtual bool BuildMeshVertexPositions( UStaticMesh* StaticMesh, TArray<uint32>& Indices, TArray<FVector3f>& Vertices, FStaticMeshSectionArray& Sections) override;`
- L44 _private prototype_ `void OnBuildRenderMeshStart(class UStaticMesh* StaticMesh, const bool bInvalidateLighting);`
- L45 _private prototype_ `void OnBuildRenderMeshFinish(class UStaticMesh* StaticMesh, const bool bRebuildBoundsAndCollision);`
- L48 _private member_ `TSharedPtr<class FStaticMeshComponentRecreateRenderStateContext> RecreateRenderStateContext;` — Used to refresh all components in the scene that may be using a mesh we're editing

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHBUILDER_API`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStaticMeshBuilder, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStaticMeshBuilder, Log, All);`
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace Private` (scope `UE`)
- L51 _namespace_ `namespace StaticMeshBuilder` (scope `UE::Private`)
- L54 _prototype_ `void BuildVertexBuffer( UStaticMesh* StaticMesh, const FMeshDescription& MeshDescription, const FMeshBuildSettings& BuildSettings, TArray<int32>& OutWedgeMap, FStaticMeshSectionArray& OutSections, TArray<TArray<uint32>>& OutPerSectionIndices, FMeshBuildVertexData& BuildVertexData, const FOverlappingCorners& OverlappingCorners, TArray<int32>& RemapVerts, FBoxSphereBounds& MeshBounds, bool bNeedTangents, bool bNeedWedgeMap );` (scope `UE::Private::StaticMeshBuilder`)
- L69 _prototype_ `void BuildCombinedSectionIndices( const TArray<TArray<uint32>>& PerSectionIndices, FStaticMeshSectionArray& SectionsOut, TArray<uint32>& CombinedIndicesOut, bool& bNeeds32BitIndicesOut);` (scope `UE::Private::StaticMeshBuilder`)
