# Plugins / ModelingComponentsEditorOnly

- module root: `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly`
- headers: 21; symbols: 487
- symbol kinds: class=32, delegate=7, enum=9, enumerator=35, externvar=1, function=25, macro=12, member=115, namespace=12, prototype=224, struct=14, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AssetTools, BSPUtils, CoreUObject, Engine, InputCore, OpenSubdiv, PhysicsCore, RHI, RenderCore, SkeletalMeshModifiers, SkeletalMeshUtilitiesCommon, Slate, UnrealEd
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFramework, InteractiveToolsFramework, MeshConversion, MeshDescription, ModelingComponents, ModelingOperators, SkeletalMeshDescription, StaticMeshDescription

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/AssetUtils/CreateMaterialUtil.h` (Public)


#### enum `UE::AssetUtils::ECreateMaterialResult`  
`enum class ECreateMaterialResult`  
_L18-27_
- desc: Result enum returned by Create() functions below to indicate succes/error conditions
- L20 _public enumerator_ `Ok = 0`
- L21 _public enumerator_ `InvalidPackage = 1`
- L22 _public enumerator_ `InvalidBaseMaterial = 2`
- L23 _public enumerator_ `NameError = 3`
- L24 _public enumerator_ `DuplicateFailed = 4`
- L26 _public enumerator_ `UnknownError = 100`

#### struct `UE::AssetUtils::FMaterialAssetOptions`  
`struct FMaterialAssetOptions`  
_L32-39_
- desc: Options for new UMaterial asset created by Create() functions below.
- L35 _public member_ `UPackage* UsePackage = nullptr;` — this package will be used if it is not null, otherwise a new package will be created at NewAssetPath
- L36 _public member_ `FString NewAssetPath;`
- L38 _public member_ `bool bDeferPostEditChange = false;`

#### struct `UE::AssetUtils::FMaterialAssetResults`  
`struct FMaterialAssetResults`  
_L45-49_
- desc: Output information about a newly-created UMaterial, returned by Create functions below. Some fields may be null, if the relevant function did not create that type of object
- L47 _public member_ `UMaterial* NewMaterial = nullptr;`
- L48 _public member_ `UMaterialInstanceConstant* NewMaterialInstance = nullptr;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AssetUtils` (scope `UE`)
- L57 _prototype_ `ECreateMaterialResult CreateDuplicateMaterial( UMaterialInterface* BaseMaterial, FMaterialAssetOptions& Options, FMaterialAssetResults& ResultsOut);` (scope `UE::AssetUtils`) — Create a new UMaterial Asset by duplicating the parent UMaterial of BaseMaterial @param Options defines configuration for the new UMaterial Asset @param ResultsOut new UMaterial is returned here @return Ok, or error flag if some part of the creation process failed. On failure, no Asset is created.
- L70 _prototype_ `ECreateMaterialResult CreateDerivedMaterialInstance( UMaterialInterface* BaseMaterial, FMaterialAssetOptions& Options, FMaterialAssetResults& ResultsOut);` (scope `UE::AssetUtils`) — Create a new UMaterialInstanceConstant Asset derived from the parent UMaterial of BaseMaterial. If the input is a UMaterialInstanceConstant, duplicate it to preserve existing parameters/etc @param Options defines configuration for the new UMaterialInstanceConstant Asset @param ResultsOut new UMaterialInstanceConstant is returned here @return Ok, or error flag if some part of the creation process failed. On failure, no Asset is created.

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/AssetUtils/CreateSkeletalMeshUtil.h` (Public)


#### enum `UE::AssetUtils::ECreateSkeletalMeshResult`  
`enum class ECreateSkeletalMeshResult`  
_L23-30_
- desc: Result enum returned by Create functions below to indicate success/error conditions
- L25 _public enumerator_ `Ok = 0`
- L26 _public enumerator_ `InvalidPackage = 1`
- L27 _public enumerator_ `InvalidSkeleton = 2`
- L29 _public enumerator_ `UnknownError = 100`

#### struct `UE::AssetUtils::FSkeletalMeshAssetMeshes`  
`struct FSkeletalMeshAssetMeshes`  
_L37-42_
- desc: Set of input meshes for StaticMesh Create() functions below. Only one of the arrays should be initialized, and it's size should be equal to the number of LODs specified for the Asset.
- L39 _public member_ `TArray<const FDynamicMesh3*> DynamicMeshes;`
- L40 _public member_ `TArray<const FMeshDescription*> MeshDescriptions;`
- L41 _public member_ `TArray<FMeshDescription*> MoveMeshDescriptions;` — these will be MoveTemp()'d into the SkeletalMesh, so if initialized, this array will be invalid after Create call()

#### struct `UE::AssetUtils::FSkeletalMeshAssetOptions`  
`struct FSkeletalMeshAssetOptions`  
_L47-85_
- desc: Options for new USkeletalMesh asset created by Create() functions below.
- L50 _public member_ `UPackage* UsePackage = nullptr;` — This package will be used if it is not nullptr, otherwise a new package will be created at NewAssetPath
- L51 _public member_ `FString NewAssetPath;`
- L54 _public member_ `USkeleton* Skeleton = nullptr;` — The associated USkeleton object
- L57 _public member_ `FReferenceSkeleton* RefSkeleton = nullptr;` — The associated FReferenceSkeleton object. If null, the reference skeleton of the Skeleton object is used instead.
- L60 _public member_ `int32 NumSourceModels = 1;` — Number of SourceModels (ie LODs)
- L62 _public member_ `int32 NumMaterialSlots = 1;` — Number of Material Slots desired on the Asset. At least one will always be created.
- L65 _public member_ `bool bEnableRecomputeNormals = false;` — Controls whether or not the RecomputeNormals option will be enabled on the Asset
- L67 _public member_ `bool bEnableRecomputeTangents = true;` — Controls whether or not the RecomputeTangents option will be enabled on the Asset
- L70 _public member_ `bool bApplyNaniteSettings = false;` — Whether to use the specified NaniteSettings when generating the Asset. If false, the default settings (nanite disabled) will be used.
- L72 _public member_ `FMeshNaniteSettings NaniteSettings = FMeshNaniteSettings();` — Nanite settings to set on skeletal mesh asset, if bApplyNaniteSettings is true
- L75 _public member_ `bool bConvertBackToNonManifold = false;` — Whether to attempt to re-create the original non-manifold mesh from the (optional) non-manifold index map on the dynamic mesh.
- L78 _public member_ `TArray<FSkeletalMaterial> SkeletalMaterials;` — List of skeletal materials. These will be used over the AssetMaterials, if provided.
- L81 _public member_ `TArray<UMaterialInterface*> AssetMaterials;` — Optional list of materials to initialize the Asset with. If defined, size must be the same as NumMaterialSlots
- L84 _public member_ `FSkeletalMeshAssetMeshes SourceMeshes;` — Optional list of meshes to use to initialize SourceModels. If defined, only one array should be non-empty, and must be the same length as NumSourceModels.

#### struct `UE::AssetUtils::FSkeletalMeshResults`  
`struct FSkeletalMeshResults`  
_L91-95_
- desc: Output information about a newly-created StaticMesh, returned by Create functions below. Some fields may be null, if the relevant function did not create that type of object
- L94 _public member_ `USkeletalMesh* SkeletalMesh = nullptr;` — USkeletalMesh asset that was created

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AssetUtils` (scope `UE`)
- L104 _prototype_ `ECreateSkeletalMeshResult CreateSkeletalMeshAsset( const FSkeletalMeshAssetOptions& Options, FSkeletalMeshResults& ResultsOut);` (scope `UE::AssetUtils`) — Create a new UStaticMesh Asset based on the input Options @param Options defines configuration for the new UStaticMesh Asset @param ResultsOut new StaticMesh is returned here @return Ok, or error flag if some part of the creation process failed. On failure, no Asset is created.

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/AssetUtils/CreateStaticMeshUtil.h` (Public)


#### enum `UE::AssetUtils::ECreateStaticMeshResult`  
`enum class ECreateStaticMeshResult`  
_L27-33_
- desc: Result enum returned by Create functions below to indicate succes/error conditions
- L29 _public enumerator_ `Ok = 0`
- L30 _public enumerator_ `InvalidPackage = 1`
- L32 _public enumerator_ `UnknownError = 100`

#### struct `UE::AssetUtils::FStaticMeshAssetMeshes`  
`struct FStaticMeshAssetMeshes`  
_L40-45_
- desc: Set of input meshes for StaticMesh Create() functions below. Only one of the arrays should be initialized, and it's size should be equal to the number of LODs specified for the Asset.
- L42 _public member_ `TArray<const UE::Geometry::FDynamicMesh3*> DynamicMeshes;`
- L43 _public member_ `TArray<const FMeshDescription*> MeshDescriptions;`
- L44 _public member_ `TArray<FMeshDescription*> MoveMeshDescriptions;` — these will be MoveTemp()'d into the StaticMesh, so if initialized, this array will be invalid after Create call()

#### struct `UE::AssetUtils::FStaticMeshAssetOptions`  
`struct FStaticMeshAssetOptions`  
_L50-105_
- desc: Options for new UStaticMesh asset created by Create() functions below.
- L53 _public member_ `UPackage* UsePackage = nullptr;` — this package will be used if it is not null, otherwise a new package will be created at NewAssetPath
- L54 _public member_ `FString NewAssetPath;`
- L57 _public member_ `int32 NumSourceModels = 1;` — number of SourceModels (ie LODs)
- L59 _public member_ `int32 NumMaterialSlots = 1;` — number of Material Slots desired on the Asset. At least one will always be created.
- L62 _public member_ `bool bEnableRecomputeNormals = false;` — Controls whether or not the RecomputeNormals option will be enabled on the Asset
- L64 _public member_ `bool bEnableRecomputeTangents = true;` — Controls whether or not the RecomputeTangents option will be enabled on the Asset
- L67 _public member_ `bool bGenerateNaniteEnabledMesh = false;` — Whether to generate a nanite-enabled mesh
- L69 _public member_ `float NaniteProxyTrianglePercent_DEPRECATED = 0;` — Percentage of triangles to reduce down to for generating a coarse proxy mesh from the Nanite mesh. DEPRECATED, use NaniteSettings instead.
- L71 _public member_ `FMeshNaniteSettings NaniteSettings = FMeshNaniteSettings();` — Nanite settings to set on static mesh asset
- L74 _public member_ `bool bSupportRayTracing = true;` — Whether ray tracing will be supported on this mesh. Disable this to save memory if the generated mesh will only be rendered in the distance
- L77 _public member_ `bool bAllowDistanceField = true;` — Whether to allow distance field to be computed for this mesh. Disable this to save memory if the generated mesh will only be rendered in the distance
- L80 _public member_ `bool bGenerateLightmapUVs = false;` — Whether to generate lightmap uvs for the generated mesh
- L83 _public member_ `bool bUseFullPrecisionUVs = false;` — Whether to generate UVs with full floating point precision.
- L86 _public member_ `bool bCreatePhysicsBody = true;` — Controls whether the UBodySetup on the Asset will be created (generally should be true)
- L88 _public member_ `ECollisionTraceFlag CollisionType = ECollisionTraceFlag::CTF_UseDefault;` — set asset collision type
- L92 _public member_ `TArray<UMaterialInterface*> AssetMaterials;` — Optional list of materials to initialize the Asset with. If defined, size must be the same as NumMaterialSlots
- L95 _public member_ `FStaticMeshAssetMeshes SourceMeshes;` — Optional list of meshes to use to initialize SourceModels. If defined, only one array should be non-empty, and must be the same length as NumSourceModels.
- L98 _public member_ `bool bDeferPostEditChange = false;` — by default, PostEditChange() will be called to rebuild mesh, set true to skip this call
- L101 _public member_ `bool bBuildReversedIndexBuffer = true;` — Whether to build a reversed index buffer. Will double the memory usage of indices.
- L104 _public member_ `bool bConvertBackToNonManifold = false;` — Whether to attempt to re-create the original non-manifold mesh from the (optional) non-manifold index map on the dynamic mesh.

#### struct `UE::AssetUtils::FStaticMeshResults`  
`struct FStaticMeshResults`  
_L111-119_
- desc: Output information about a newly-created StaticMesh, returned by Create functions below. Some fields may be null, if the relevant function did not create that type of object
- L114 _public member_ `UStaticMesh* StaticMesh = nullptr;` — UStaticMesh asset that was created
- L116 _public member_ `UStaticMeshComponent* Component = nullptr;` — New Component that was created that references the Asset (or null, if no component is created)
- L118 _public member_ `UStaticMeshActor* Actor = nullptr;` — New Actor that was created for the Component (or null, if no component is created)

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace AssetUtils` (scope `UE`)
- L128 _prototype_ `ECreateStaticMeshResult CreateStaticMeshAsset( FStaticMeshAssetOptions& Options, FStaticMeshResults& ResultsOut);` (scope `UE::AssetUtils`) — Create a new UStaticMesh Asset based on the input Options @param Options defines configuration for the new UStaticMesh Asset @param ResultsOut new StaticMesh is returned here @return Ok, or error flag if some part of the creation process failed. On failure, no Asset is created.

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/AssetUtils/CreateTexture2DUtil.h` (Public)


#### enum `UE::AssetUtils::ECreateTexture2DResult`  
`enum class ECreateTexture2DResult`  
_L16-25_
- desc: Result enum returned by Create() functions below to indicate success/error conditions
- L18 _public enumerator_ `Ok = 0`
- L19 _public enumerator_ `InvalidPackage = 1`
- L20 _public enumerator_ `InvalidInputTexture = 2`
- L21 _public enumerator_ `NameError = 3`
- L22 _public enumerator_ `OverwriteTypeError = 4`
- L24 _public enumerator_ `UnknownError = 100`

#### struct `UE::AssetUtils::FTexture2DAssetOptions`  
`struct FTexture2DAssetOptions`  
_L31-41_
- desc: Options for new UTexture asset created by Create() functions below.
- L34 _public member_ `UPackage* UsePackage = nullptr;` — this package will be used if it is not null, otherwise a new package will be created at NewAssetPath
- L35 _public member_ `FString NewAssetPath;`
- L37 _public member_ `bool bDeferPostEditChange = false;`
- L40 _public member_ `bool bOverwriteIfExists = false;` — if NewAssetPath already exists, update the existing Texture2D.

#### struct `UE::AssetUtils::FTexture2DAssetResults`  
`struct FTexture2DAssetResults`  
_L47-50_
- desc: Output information about a newly-created UTexture2D, returned by Create functions below. Some fields may be null, if the relevant function did not create that type of object
- L49 _public member_ `UTexture2D* Texture = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AssetUtils` (scope `UE`)
- L58 _prototype_ `ECreateTexture2DResult SaveGeneratedTexture2DAsset( UTexture2D* GeneratedTexture, FTexture2DAssetOptions& Options, FTexture2DAssetResults& ResultsOut);` (scope `UE::AssetUtils`) — Convert a temporary UTexture2D in the Transient package into a serialized Asset @param Options defines configuration for the new UTexture2D Asset @param ResultsOut new UTexture2D is returned here @return Ok, or error flag if some part of the creation process failed. On failure, no Asset is created.

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ConversionUtils/DynamicMeshToVolume.h` (Public)


#### struct `UE::Conversion::FMeshToVolumeOptions`  
`struct FMeshToVolumeOptions`  
_L23-49_
- L29 _public member_ `bool bRespectGroupBoundaries = true;` — When true, coplanar components with different group IDs will not be merged into a single volume polygon.
- L36 _public member_ `bool bAutoSimplify = false;` — If true, simplify the input mesh to the specified target triangle count. Volumes with many faces/vertices are very expensive, and all Volume processing happens on the game thread, so this should generally be used to prevent significant Editor hangs.
- L39 _public member_ `int32 MaxTriangles = 250;` — If bAutoSimplify is true, it will simplify the mesh to this MaxTriangles count
- L42 _public member_ `bool bCleanDegenerate = true;` — If true, attempt to clean degenerate triangles before converting to a volume, as degenerate triangles can cause BSP construction to fail.
- L45 _public member_ `double MinTriangleArea = UE_DOUBLE_KINDA_SMALL_NUMBER;` — If bCleanDegenerate is true, defines the minimum triangle area to keep
- L48 _public member_ `double MinEdgeLength = .01;` — If bCleanDegenerate is true, defines the minimum triangle edge length to keep.

#### struct `UE::Conversion::FDynamicMeshFace`  
`struct FDynamicMeshFace`  
_L51-55_
- L53 _public member_ `FFrame3d Plane;`
- L54 _public member_ `TArray<FVector3d> BoundaryLoop;`

#### Free symbols / members of external scopes

- L16 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L18 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Conversion` (scope `UE`)
- L61 _prototype_ `void GetPolygonFaces(const FDynamicMesh3& InputMesh, const FMeshToVolumeOptions& Options, TArray<FDynamicMeshFace>& FacesOut, FProgressCancel* Progress = nullptr);` (scope `UE::Conversion`) — Gets an array of face objects that can be used to convert a dynamic mesh to a volume, based on given FMeshToVolumeOptions.
- L68 _prototype_ `void GetPolygonFaces(const FDynamicMesh3& InputMesh, TArray<FDynamicMeshFace>& Faces, bool bRespectGroupBoundaries);` (scope `UE::Conversion`) — Gets an array of face objects that can be used to convert a dynamic mesh to a volume. This version tries to merge coplanar triangles into polygons.
- L74 _prototype_ `void GetTriangleFaces(const FDynamicMesh3& InputMesh, TArray<FDynamicMeshFace>& Faces);` (scope `UE::Conversion`) — Gets an array of face objects that can be used to convert a dynamic mesh to a volume. This version makes each triangle its own face.
- L79 _prototype_ `void DynamicMeshToVolume(const FDynamicMesh3& InputMesh, AVolume* TargetVolume, const FMeshToVolumeOptions& Options = FMeshToVolumeOptions());` (scope `UE::Conversion`) — Converts a dynamic mesh to a volume.
- L81 _prototype_ `void DynamicMeshToVolume(const FDynamicMesh3& InputMesh, TArray<FDynamicMeshFace>& Faces, AVolume* TargetVolume);` (scope `UE::Conversion`)

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/EditorModelingObjectsCreationAPI.h` (Public)


#### class `UEditorModelingObjectsCreationAPI`  
`class UEditorModelingObjectsCreationAPI : public UModelingObjectsCreationAPI`  
_L31-109_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UModelingObjectsCreationAPI`
- desc: Implementation of UModelingObjectsCreationAPI suitable for use in UE Editor. - CreateMeshObject() currently creates a StaticMesh Asset/Actor, a Volume Actor or a DynamicMesh Actor - CreateTextureObject() currently creates a UTexture2D Asset - CreateMaterialObject() currently creates a UMaterial Asset This is intended to be registered in the ToolsContext ContextObjectStore. Static utility functions ::Register() / ::Find() / ::Deregister() can be used to do this in a consistent way. Several client-provided callbacks can be used to customize functionality (eg in Modeling Mode) - GetNewAssetPathNameCallback is called to determine an asset path. This can be used to do things like pop up an interactive path-selection dialog, use project-defined paths, etc - OnModelingMeshCreated is broadcast for each new created mesh object - OnModelingTextureCreated is broadcast for each new created texture object - OnModelingMaterialCreated is broadcast for each new created material object
- L37 _public prototype_ `virtual FCreateMeshObjectResult CreateMeshObject(const FCreateMeshObjectParams& CreateMeshParams) override;` — `UFUNCTION(BlueprintCallable, Category = "Modeling Objects")`
- L40 _public prototype_ `virtual FCreateTextureObjectResult CreateTextureObject(const FCreateTextureObjectParams& CreateTexParams) override;` — `UFUNCTION(BlueprintCallable, Category = "Modeling Objects")`
- L43 _public prototype_ `virtual FCreateMaterialObjectResult CreateMaterialObject(const FCreateMaterialObjectParams& CreateMaterialParams) override;` — `UFUNCTION(BlueprintCallable, Category = "Modeling Objects")`
- L46 _public prototype_ `virtual FCreateActorResult CreateNewActor(const FCreateActorParams& CreateActorParams) override;` — `UFUNCTION(BlueprintCallable, Category = "Modeling Objects")`
- L49 _public prototype_ `virtual FCreateComponentResult CreateNewComponentOnActor(const FCreateComponentParams& CreateComponentParams) override;` — `UFUNCTION(BlueprintCallable, Category = "Modeling Objects")`
- L56 _public function_ `virtual bool HasMoveVariants() const`
- L58 _public prototype_ `virtual FCreateMeshObjectResult CreateMeshObject(FCreateMeshObjectParams&& CreateMeshParams) override;`
- L60 _public prototype_ `virtual FCreateTextureObjectResult CreateTextureObject(FCreateTextureObjectParams&& CreateTexParams) override;`
- L62 _public prototype_ `virtual FCreateMaterialObjectResult CreateMaterialObject(FCreateMaterialObjectParams&& CreateMaterialParams) override;`
- L64 _public prototype_ `virtual FCreateActorResult CreateNewActor(FCreateActorParams&& CreateActorParams) override;`
- L66 _public prototype_ `virtual FCreateComponentResult CreateNewComponentOnActor(FCreateComponentParams&& CreateComponentParams) override;`
- L72 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FString, FGetAssetPathNameCallbackSignature, const FString& BaseName, const UWorld* TargetWorld, FString SuggestedFolder);`
- L73 _public member_ `FGetAssetPathNameCallbackSignature GetNewAssetPathNameCallback;`
- L75 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingMeshCreatedSignature, const FCreateMeshObjectResult& CreatedInfo);`
- L76 _public member_ `FModelingMeshCreatedSignature OnModelingMeshCreated;`
- L78 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingTextureCreatedSignature, const FCreateTextureObjectResult& CreatedInfo);`
- L79 _public member_ `FModelingTextureCreatedSignature OnModelingTextureCreated;`
- L81 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingMaterialCreatedSignature, const FCreateMaterialObjectResult& CreatedInfo);`
- L82 _public member_ `FModelingMaterialCreatedSignature OnModelingMaterialCreated;`
- L84 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingActorCreatedSignature, const FCreateActorResult& CreatedInfo);`
- L85 _public member_ `FModelingActorCreatedSignature OnModelingActorCreated;`
- L87 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingComponentCreatedSignature, const FCreateComponentResult& CreatedInfo);`
- L88 _public member_ `FModelingComponentCreatedSignature OnModelingComponentCreated;`
- L94 _public prototype_ `static UEditorModelingObjectsCreationAPI* Register(UInteractiveToolsContext* ToolsContext);`
- L95 _public prototype_ `static UEditorModelingObjectsCreationAPI* Find(UInteractiveToolsContext* ToolsContext);`
- L96 _public prototype_ `static bool Deregister(UInteractiveToolsContext* ToolsContext);`
- L103 _public prototype_ `FCreateMeshObjectResult CreateStaticMeshAsset(FCreateMeshObjectParams&& CreateMeshParams);` — internal implementations called by public functions
- L104 _public prototype_ `FCreateMeshObjectResult CreateVolume(FCreateMeshObjectParams&& CreateMeshParams);`
- L105 _public prototype_ `FCreateMeshObjectResult CreateDynamicMeshActor(FCreateMeshObjectParams&& CreateMeshParams);`
- L106 _public prototype_ `ECreateModelingObjectResult GetNewAssetPath(FString& OutNewAssetPath, const FString& BaseName, const UObject* StoreRelativeToObject, const UWorld* World);`
- L108 _public prototype_ `TArray<UMaterialInterface*> FilterMaterials(const TArray<UMaterialInterface*>& MaterialsIn);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`
- L72 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FString, FGetAssetPathNameCallbackSignature, const FString& BaseName, const UWorld* TargetWorld, FString SuggestedFolder);`
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingMeshCreatedSignature, const FCreateMeshObjectResult& CreatedInfo);`
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingTextureCreatedSignature, const FCreateTextureObjectResult& CreatedInfo);`
- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingMaterialCreatedSignature, const FCreateMaterialObjectResult& CreatedInfo);`
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingActorCreatedSignature, const FCreateActorResult& CreatedInfo);`
- L87 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FModelingComponentCreatedSignature, const FCreateComponentResult& CreatedInfo);`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ModelingComponentsEditorOnlyModule.h` (Public)


#### class `FModelingComponentsEditorOnlyModule`  
`class FModelingComponentsEditorOnlyModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ModelingToolTargetEditorOnlyUtil.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ToolTarget` (scope `UE`)
- L24 _prototype_ `TArray<EMeshLODIdentifier> GetAvailableLODs(const USkeletalMesh* SkeletalMesh, bool bSkipAutoGenerated);` (scope `UE::ToolTarget`) — @return available LODs on the Skeletal Mesh

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/Operations/SubdividePoly.h` (Public)


#### enum `ESubdivisionScheme`  
`enum class ESubdivisionScheme : uint8`  
_L19-30_
- reflection: `UENUM()`
- desc: Subdivision scheme
- L23 _public enumerator_ `Bilinear` — Subdivides like Catmull-Clark, but does not smooth the result (i.e. the vertices remain in their original planes).
- L26 _public enumerator_ `CatmullClark UMETA(DisplayName = "Catmull-Clark")` — Common subdivision scheme typically used with quad-dominant meshes. In our tools, it uses the group topology to build a cage that serves as the starting point.
- L29 _public enumerator_ `Loop` — Subdivision scheme developed by Charles Loop that operates directly on triangle meshes, and therefore does not use the group topology.

#### enum `ESubdivisionBoundaryScheme`  
`enum class ESubdivisionBoundaryScheme : uint8`  
_L33-48_
- reflection: `UENUM()`
- L37 _public enumerator_ `SmoothCorners` — Corners with only one adjoining face are smoothed along with the rest of the mesh boundary. For example, a square patch will have rounded corners.
- L41 _public enumerator_ `SharpCorners` — Corners with only one adjoining face are constrained to be passed through. For example, this will keep the corners of a vertically deformed square patch sharp even as the rest of the patch is vertically smoothed.

#### enum `ESubdivisionOutputNormals`  
`enum class ESubdivisionOutputNormals : uint8`  
_L56-66_
- reflection: `UENUM()`
- desc: Method for computing normals on the output mesh
- L59 _public enumerator_ `Interpolated` — Copy normals to poly mesh then interpolate to new triangles as we subdivide.
- L62 _public enumerator_ `Generated` — Recompute normals after subdivision
- L65 _public enumerator_ `None` — Leave normals uninitialized on output mesh

#### enum `ESubdivisionOutputUVs`  
`enum class ESubdivisionOutputUVs : uint8`  
_L72-79_
- reflection: `UENUM()`
- desc: Method for computing UVs on the output mesh
- L75 _public enumerator_ `Interpolated` — Copy UVs to poly mesh vertices then interpolate as we subdivide.
- L78 _public enumerator_ `None` — Leave UVs uninitialized on output mesh

#### class `FSubdividePoly`  
`class FSubdividePoly`  
_L88-133_
- desc: Interprets an FGroupTopology object as a poly mesh and refines it to a given level. Topological subdivision can be computed separately from the interpolation of vertex positions. A typical workflow might be to first precompute the refined topology, then compute the interpolated positions (and other vertex values) as the original polymesh is deformed.
- L92 _public prototype_ `FSubdividePoly(const FGroupTopology& InTopology, const FDynamicMesh3& InOriginalMesh, int InLevel);`
- L96 _public prototype_ `~FSubdividePoly();`
- L107 _public prototype_ `ETopologyCheckResult ValidateTopology();`
- L109 _public prototype_ `bool ComputeTopologySubdivision();`
- L111 _public prototype_ `bool ComputeSubdividedMesh(FDynamicMesh3& OutMesh);`
- L113 _public member_ `ESubdivisionScheme SubdivisionScheme = ESubdivisionScheme::CatmullClark;`
- L115 _public member_ `ESubdivisionBoundaryScheme BoundaryScheme = ESubdivisionBoundaryScheme::SharpCorners;`
- L117 _public member_ `ESubdivisionOutputNormals NormalComputationMethod = ESubdivisionOutputNormals::Generated;`
- L119 _public member_ `ESubdivisionOutputUVs UVComputationMethod = ESubdivisionOutputUVs::Interpolated;`
- L121 _public member_ `bool bNewPolyGroups = false;`
- L128 _private member_ `const FGroupTopology& GroupTopology;`
- L129 _private member_ `const FDynamicMesh3& OriginalMesh;`
- L130 _private member_ `int Level;`
- L132 _private member_ `TUniquePtr<RefinerImpl> Refiner;`

#### enum `FSubdividePoly::ETopologyCheckResult`  
`enum class ETopologyCheckResult`  
_L98-106_
- L100 _public enumerator_ `Ok = 0`
- L101 _public enumerator_ `NoGroups = 1`
- L102 _public enumerator_ `InsufficientGroups = 2`
- L103 _public enumerator_ `UnboundedPolygroup = 3`
- L104 _public enumerator_ `MultiBoundaryPolygroup = 4`
- L105 _public enumerator_ `DegeneratePolygroup = 5`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`
- L11 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FGroupTopology);`
- L12 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/Scene/LevelObjectsObserver.h` (Public)


#### class `FLevelObjectsObserver`  
`class FLevelObjectsObserver : public FEditorUndoClient`  
_L28-74_
- inherits: `FEditorUndoClient`
- desc: FLevelObjectsObserver is a utility class that tracks the active-set of Actors in a World, in the Editor, and emits events when the set changes. The goal is to guarantee that: - OnActorAdded will be emitted when an Actor comes into existence - OnActorRemoved will be emitted when an Actor ceases to exist (possibly after GC, though) - these signals will be unique, ie once per Actor This is a surprisingly complicated problem in the Editor due to the many ways that Actors might be created or destroyed, in particular via Undo/Redo. Note that it is not possible to guarantee that OnActorRemoved() fires before an Actor is GC'd. So, listeners should maintain TWeakObjectPtr<>'s on Actors if they need to know this information.
- L34 _public prototype_ `virtual ~FLevelObjectsObserver();` — Destructor.
- L39 _public prototype_ `void Initialize(UWorld* WorldIn);` — Begin watching WorldIn. This will emit OnActorAdded for all Actors in the World.
- L44 _public prototype_ `void Shutdown();` — Stop watching WorldIn. This will emit OnActorRemoved for all Actors that the Observer is currently aware of.
- L47 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient implementation
- L48 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FActorAddRemoveSignature, AActor*);`
- L55 _public member_ `FActorAddRemoveSignature OnActorAdded;` — OnActorAdded is emitted when a new Actor is detected
- L61 _public member_ `FActorAddRemoveSignature OnActorRemoved;` — OnActorRemoved is emitted when an existing Actor is destroyed. Note that the Actor pointer passed here may point to garbage, ie the Actor may have already been GC'd. Do not attempt to call functions on the pointer.
- L64 _protected member_ `UWorld* World = nullptr;` — target World
- L65 _protected member_ `TSet<AActor*> Actors;` — active set of Actors
- L67 _protected member_ `FDelegateHandle OnActorDeletedHandle;`
- L68 _protected member_ `FDelegateHandle OnActorAddedHandle;`
- L69 _protected member_ `FDelegateHandle OnActorListChangedHandle;`
- L71 _protected prototype_ `void OnUntrackedLevelChange();`
- L72 _protected prototype_ `void HandleActorAddedEvent(AActor* Actor);`
- L73 _protected prototype_ `void HandleActorDeletedEvent(AActor* Actor);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FActorAddRemoveSignature, AActor*);`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/Selection/StaticMeshSelector.h` (Public)


#### class `FStaticMeshSelector`  
`class FStaticMeshSelector : public FBaseDynamicMeshSelector`  
_L19-68_
- inherits: `FBaseDynamicMeshSelector`
- L24 _public prototype_ `virtual bool Initialize( FGeometryIdentifier SourceGeometryIdentifier);`
- L31 _public prototype_ `virtual void Shutdown() override;`
- L33 _public function_ `virtual bool SupportsSleep() const override` — disable sleep on StaticMesh Selector until we can properly track changes...
- L38 _public prototype_ `virtual bool IsLockable() const override;`
- L39 _public prototype_ `virtual bool IsLocked() const override;`
- L40 _public prototype_ `virtual void SetLockedState(bool bLocked) override;`
- L43 _public prototype_ `virtual IGeometrySelectionTransformer* InitializeTransformation(const FGeometrySelection& Selection) override;`
- L44 _public prototype_ `virtual void ShutdownTransformation(IGeometrySelectionTransformer* Transformer) override;`
- L46 _public prototype_ `virtual void UpdateAfterGeometryEdit( IToolsContextTransactionsAPI* TransactionsAPI, bool bInTransaction, TUniquePtr<UE::Geometry::FDynamicMeshChange> DynamicMeshChange, FText GeometryEditTransactionString) override;`
- L53 _protected member_ `TWeakObjectPtr<UStaticMeshComponent> WeakStaticMeshComponent = nullptr;`
- L54 _protected member_ `TWeakObjectPtr<UStaticMesh> WeakStaticMesh = nullptr;`
- L55 _protected member_ `FDelegateHandle StaticMesh_OnMeshChangedHandle;`
- L58 _protected member_ `TStrongObjectPtr<UDynamicMesh> LocalTargetMesh;` — TODO: this is not a great design, it would be better if something external could own this mesh...
- L59 _protected prototype_ `void CopyFromStaticMesh();`
- L61 _protected member_ `TSharedPtr<FBasicDynamicMeshSelectionTransformer> ActiveTransformer;`
- L62 _protected prototype_ `void CommitMeshTransform();`
- L66 _public prototype_ `static void SetAssetUnlockedOnCreation(UStaticMesh* StaticMesh);`
- L67 _public prototype_ `static void ResetUnlockedStaticMeshAssets();`

#### class `FStaticMeshComponentSelectorFactory`  
`class FStaticMeshComponentSelectorFactory : public IGeometrySelectorFactory`  
_L76-81_
- inherits: `IGeometrySelectorFactory`
- desc: FStaticMeshComponentSelectorFactory constructs FStaticMeshSelector instances for UStaticMeshComponents
- L79 _public prototype_ `virtual bool CanBuildForTarget(FGeometryIdentifier TargetIdentifier) const;`
- L80 _public prototype_ `virtual TUniquePtr<IGeometrySelector> BuildForTarget(FGeometryIdentifier TargetIdentifier) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/Selection/VolumeSelector.h` (Public)


#### class `FVolumeSelector`  
`class FVolumeSelector : public FBaseDynamicMeshSelector, public FEditorUndoClient`  
_L19-70_
- inherits: `FBaseDynamicMeshSelector,FEditorUndoClient`
- L24 _public prototype_ `virtual bool Initialize( FGeometryIdentifier SourceGeometryIdentifier);`
- L31 _public prototype_ `virtual void Shutdown() override;`
- L33 _public function_ `virtual bool SupportsSleep() const override` — disable sleep on VolumeSelector until we can properly track changes...
- L37 _public prototype_ `virtual bool IsLockable() const override;`
- L38 _public prototype_ `virtual bool IsLocked() const override;`
- L39 _public prototype_ `virtual void SetLockedState(bool bLocked) override;`
- L41 _public prototype_ `virtual IGeometrySelectionTransformer* InitializeTransformation(const FGeometrySelection& Selection) override;`
- L42 _public prototype_ `virtual void ShutdownTransformation(IGeometrySelectionTransformer* Transformer) override;`
- L44 _public prototype_ `virtual void UpdateAfterGeometryEdit( IToolsContextTransactionsAPI* TransactionsAPI, bool bInTransaction, TUniquePtr<UE::Geometry::FDynamicMeshChange> DynamicMeshChange, FText GeometryEditTransactionString) override;`
- L52 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient implementation
- L53 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L56 _public prototype_ `static void SetComponentUnlockedOnCreation(UBrushComponent* Component);`
- L57 _public prototype_ `static void ResetUnlockedBrushComponents();`
- L60 _protected member_ `AVolume* ParentVolume = nullptr;`
- L61 _protected member_ `UBrushComponent* BrushComponent = nullptr;`
- L64 _protected member_ `TStrongObjectPtr<UDynamicMesh> LocalTargetMesh;` — TODO: this is not a great design, it would be better if something external could own this mesh...
- L66 _protected prototype_ `void UpdateDynamicMeshFromVolume();`
- L68 _protected member_ `TSharedPtr<FBasicDynamicMeshSelectionTransformer> ActiveTransformer;`
- L69 _protected prototype_ `void CommitMeshTransform();`

#### class `FBrushComponentSelectorFactory`  
`class FBrushComponentSelectorFactory : public IGeometrySelectorFactory`  
_L79-84_
- inherits: `IGeometrySelectorFactory`
- desc: FVolumeComponentSelectorFactory constructs FVolumeSelector instances for UBrushComponents
- L82 _public prototype_ `virtual bool CanBuildForTarget(FGeometryIdentifier TargetIdentifier) const;`
- L83 _public prototype_ `virtual TUniquePtr<IGeometrySelector> BuildForTarget(FGeometryIdentifier TargetIdentifier) const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/TargetInterfaces/SkeletonCommitter.h` (Public)


#### class `USkeletonCommitter`  
`class USkeletonCommitter: public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ISkeletonCommitter`  
`class ISkeletonCommitter`  
_L19-26_
- L24 _public prototype_ `virtual void SetupSkeletonModifier(USkeletonModifier* InModifier) = 0;`
- L25 _public prototype_ `virtual void CommitSkeletonModifier(USkeletonModifier* InModifier) = 0;`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/TargetInterfaces/SkeletonProvider.h` (Public)


#### class `USkeletonProvider`  
`class USkeletonProvider : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ISkeletonProvider`  
`class ISkeletonProvider`  
_L19-25_
- L24 _public prototype_ `virtual FReferenceSkeleton GetSkeleton() const = 0;`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ToolTargets/DynamicMeshComponentToolTarget.h` (Public)


#### class `UDynamicMeshComponentToolTarget`  
`class UDynamicMeshComponentToolTarget : public UPrimitiveComponentToolTarget, public IMeshDescriptionCommitter, public IMeshDescriptionProvider, public IDynamicMeshProvider, public IDynamicMeshCommitter, public IMaterialProvider, public IPersistentDynamicMeshSource, public IPhysicsDataSource, public ISkeletonProvider, public ISkeletonCommitter`  
_L28-94_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UPrimitiveComponentToolTarget,IMeshDescriptionCommitter,IMeshDescriptionProvider,IDynamicMeshProvider,IDynamicMeshCommitter,IMaterialProvider,IPersistentDynamicMeshSource,IPhysicsDataSource,ISkeletonProvider,ISkeletonCommitter`
- desc: A ToolTarget backed by a DynamicMeshComponent
- L43 _public prototype_ `virtual bool IsValid() const override;`
- L48 _public prototype_ `const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) override;` — IMeshDescriptionProvider implementation
- L49 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() override;`
- L52 _public prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitMeshParams = FCommitMeshParameters()) override;` — IMeshDescritpionCommitter implementation
- L56 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider implementation
- L59 _public prototype_ `virtual void CommitDynamicMesh(const UE::Geometry::FDynamicMesh3& Mesh, const FDynamicMeshCommitInfo& CommitInfo) override;` — IDynamicMeshCommitter implementation
- L63 _public prototype_ `int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L64 _public prototype_ `UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L65 _public prototype_ `void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials) const override;`
- L66 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override;`
- L69 _public prototype_ `virtual UDynamicMesh* GetDynamicMeshContainer() override;` — IPersistentDynamicMeshSource implementation
- L70 _public prototype_ `virtual void CommitDynamicMeshChange(TUniquePtr<FToolCommandChange> Change, const FText& ChangeMessage) override;`
- L71 _public prototype_ `virtual bool HasDynamicMeshComponent() const override;`
- L72 _public prototype_ `virtual UDynamicMeshComponent* GetDynamicMeshComponent() override;`
- L75 _public prototype_ `virtual UBodySetup* GetBodySetup() const override;` — IPhysicsDataSource implementation
- L76 _public prototype_ `virtual IInterface_CollisionDataProvider* GetComplexCollisionProvider() const override;`
- L79 _public prototype_ `virtual FReferenceSkeleton GetSkeleton() const override;` — ISkeletonProvider implementation
- L82 _public prototype_ `virtual void SetupSkeletonModifier(USkeletonModifier* InModifier) override;` — ISkeletonCommitter implementation
- L83 _public prototype_ `virtual void CommitSkeletonModifier(USkeletonModifier* InModifier) override;`
- L89 _protected member_ `TUniquePtr<FMeshDescription> ConvertedMeshDescription;`
- L90 _protected member_ `bool bHaveMeshDescription = false;`

#### class `UDynamicMeshComponentToolTargetFactory`  
`class UDynamicMeshComponentToolTargetFactory : public UToolTargetFactory`  
_L99-108_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for UDynamicMeshComponentToolTarget to be used by the target manager.
- L105 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L107 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ToolTargets/SkeletalMeshComponentToolTarget.h` (Public)


#### class `USkeletalMeshComponentReadOnlyToolTarget`  
`class USkeletalMeshComponentReadOnlyToolTarget : public UPrimitiveComponentToolTarget, public IMeshDescriptionProvider, public IDynamicMeshProvider, public IMaterialProvider, public ISkeletalMeshBackedTarget, public ISkeletonProvider`  
_L30-76_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UPrimitiveComponentToolTarget,IMeshDescriptionProvider,IDynamicMeshProvider,IMaterialProvider,ISkeletalMeshBackedTarget,ISkeletonProvider`
- desc: A tool target backed by a skeletal mesh component that can provide and take a mesh description, without 'committer' interfaces for writing to the source skeletal mesh asset.
- L43 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget implementation
- L46 _public prototype_ `virtual const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) override;` — IMeshDescriptionProvider implementation
- L47 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() override;`
- L48 _public function_ `virtual bool SupportsLODs() const override`
- L49 _public prototype_ `virtual TArray<EMeshLODIdentifier> GetAvailableLODs(bool bSkipAutoGenerated = true) const override;`
- L50 _public function_ `virtual EMeshLODIdentifier GetMeshDescriptionLOD() const override`
- L54 _public prototype_ `virtual int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L55 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L56 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials) const override;`
- L57 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override;`
- L60 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider
- L61 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh(const FGetMeshParameters& InGetMeshParams) override;`
- L64 _public prototype_ `virtual USkeletalMesh* GetSkeletalMesh() const override;` — ISkeletalMeshBackedTarget implementation
- L67 _public prototype_ `virtual FReferenceSkeleton GetSkeleton() const override;` — ISkeletonProvider implementation
- L71 _protected member_ `EMeshLODIdentifier EditingLOD = EMeshLODIdentifier::LOD0;` — LOD to edit, default is to edit LOD0

#### class `USkeletalMeshComponentToolTarget`  
`class USkeletalMeshComponentToolTarget : public USkeletalMeshComponentReadOnlyToolTarget, public IMeshDescriptionCommitter, public IDynamicMeshCommitter, public ISkeletonCommitter`  
_L84-108_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `USkeletalMeshComponentReadOnlyToolTarget,IMeshDescriptionCommitter,IDynamicMeshCommitter,ISkeletonCommitter`
- desc: A tool target backed by a skeletal mesh component that can provide and take a mesh description.
- L94 _public prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitParams = FCommitMeshParameters()) override;` — IMeshDescriptionCommitter implementation
- L98 _public prototype_ `virtual void CommitDynamicMesh(const UE::Geometry::FDynamicMesh3& Mesh, const FDynamicMeshCommitInfo& CommitInfo) override;` — IDynamicMeshCommitter
- L102 _public prototype_ `virtual void SetupSkeletonModifier(USkeletonModifier* InModifier) override;` — ISkeletonCommitter
- L103 _public prototype_ `virtual void CommitSkeletonModifier(USkeletonModifier* InModifier) override;`

#### class `USkeletalMeshComponentReadOnlyToolTargetFactory`  
`class USkeletalMeshComponentReadOnlyToolTargetFactory : public UToolTargetFactory`  
_L113-122_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for USkeletalMeshComponentReadOnlyToolTarget to be used by the target manager.
- L119 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L121 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

#### class `USkeletalMeshComponentToolTargetFactory`  
`class USkeletalMeshComponentToolTargetFactory : public UToolTargetFactory`  
_L127-145_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for USkeletalMeshComponentToolTarget to be used by the target manager.
- L133 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L135 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`
- L137 _public prototype_ `static bool CanWriteToSource(const UObject* SourceObject);`
- L139 _public function_ `virtual EMeshLODIdentifier GetActiveEditingLOD() const`
- L140 _public prototype_ `virtual void SetActiveEditingLOD(EMeshLODIdentifier NewEditingLOD);`
- L144 _protected member_ `EMeshLODIdentifier EditingLOD = EMeshLODIdentifier::LOD0;` — LOD to edit, default is to edit LOD0

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ToolTargets/SkeletalMeshToolTarget.h` (Public)


#### class `USkeletalMeshReadOnlyToolTarget`  
`class USkeletalMeshReadOnlyToolTarget : public UToolTarget, public IMeshDescriptionProvider, public IDynamicMeshProvider, public IMaterialProvider, public ISkeletalMeshBackedTarget`  
_L29-83_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTarget,IMeshDescriptionProvider,IDynamicMeshProvider,IMaterialProvider,ISkeletalMeshBackedTarget`
- desc: A tool target backed by a read-only skeletal mesh. This is a special tool target that refers to the underlying asset (in this case a skeletal mesh), rather than indirectly through a component. This type of target is used in cases, such as opening an asset through the content browser, when there is no component available.
- L40 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget
- L43 _public prototype_ `virtual const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) override;` — IMeshDescriptionProvider implementation
- L44 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() override;`
- L45 _public function_ `virtual bool SupportsLODs() const override`
- L46 _public prototype_ `virtual TArray<EMeshLODIdentifier> GetAvailableLODs(bool bSkipAutoGenerated = true) const override;`
- L47 _public function_ `virtual EMeshLODIdentifier GetMeshDescriptionLOD() const override`
- L50 _public prototype_ `virtual int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L51 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L52 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials) const override;`
- L53 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override;`
- L56 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider
- L57 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh(const FGetMeshParameters& InGetMeshParams) override;`
- L60 _public prototype_ `virtual USkeletalMesh* GetSkeletalMesh() const override;` — ISkeletalMeshBackedTarget implementation
- L63 _protected member_ `TWeakObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;`
- L66 _protected member_ `EMeshLODIdentifier EditingLOD = EMeshLODIdentifier::LOD0;` — The LOD to edit if requested to get/commit at EMeshLODIdentifier::Default or if no specific LOD is requested.
- L75 _protected prototype_ `static bool IsValid(const USkeletalMesh* USkeletalMesh);` — `UE_DEPRECATED(5.3, "This function doesn't check anything skeletal mesh specific, only (badly) checks to see if the object is alive")`
- L77 _protected prototype_ `static TArray<EMeshLODIdentifier> GetAvailableLODs(const USkeletalMesh* SkeletalMesh, bool bSkipAutoGenerated);`
- L78 _protected prototype_ `static void GetMaterialSet(const USkeletalMesh* SkeletalMesh, FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials);`
- L80 _protected prototype_ `static bool CommitMaterialSetUpdate(USkeletalMesh* SkeletalMesh, const FComponentMaterialSet& MaterialSet, bool bApplyToAsset);`
- L82 _protected prototype_ `static int32 GetValidEditingLOD(const USkeletalMesh* SkeletalMesh, EMeshLODIdentifier RequestedEditingLOD);`

#### class `USkeletalMeshToolTarget`  
`class USkeletalMeshToolTarget : public USkeletalMeshReadOnlyToolTarget, public IMeshDescriptionCommitter, public IDynamicMeshCommitter`  
_L90-113_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `USkeletalMeshReadOnlyToolTarget,IMeshDescriptionCommitter,IDynamicMeshCommitter`
- desc: A tool target backed by a skeletal mesh.
- L99 _public prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitMeshParams = FCommitMeshParameters()) override;` — IMeshDescriptionCommitter implementation
- L103 _public prototype_ `virtual void CommitDynamicMesh(const UE::Geometry::FDynamicMesh3& Mesh, const FDynamicMeshCommitInfo& CommitInfo) override;` — IDynamicMeshCommitter
- L112 _protected prototype_ `static void CommitMeshDescription(USkeletalMesh* SkeletalMesh, const FCommitter& Committer, int32 LODIndex);`

#### class `USkeletalMeshReadOnlyToolTargetFactory`  
`class USkeletalMeshReadOnlyToolTargetFactory : public UToolTargetFactory`  
_L118-127_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for USkeletalMeshReadOnlyToolTarget to be used by the target manager.
- L124 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L126 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

#### class `USkeletalMeshToolTargetFactory`  
`class USkeletalMeshToolTargetFactory : public UToolTargetFactory`  
_L132-150_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for USkeletalMeshToolTarget to be used by the target manager.
- L138 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L140 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`
- L142 _public prototype_ `static bool CanWriteToSource(const UObject* SourceObject);`
- L144 _public function_ `virtual EMeshLODIdentifier GetActiveEditingLOD() const`
- L145 _public prototype_ `virtual void SetActiveEditingLOD(EMeshLODIdentifier NewEditingLOD);`
- L149 _protected member_ `EMeshLODIdentifier EditingLOD = EMeshLODIdentifier::LOD0;` — LOD to edit, default is to edit LOD0

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ToolTargets/StaticMeshComponentToolTarget.h` (Public)


#### class `UStaticMeshComponentReadOnlyToolTarget`  
`class UStaticMeshComponentReadOnlyToolTarget : public UPrimitiveComponentToolTarget, public IMeshDescriptionProvider, public IMaterialProvider, public IStaticMeshBackedTarget, public IDynamicMeshProvider, public IPhysicsDataSource`  
_L29-90_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UPrimitiveComponentToolTarget,IMeshDescriptionProvider,IMaterialProvider,IStaticMeshBackedTarget,IDynamicMeshProvider,IPhysicsDataSource`
- desc: A tool target backed by a static mesh component that can provide and take a mesh description, without 'committer' interfaces for writing to the source static mesh asset.
- L40 _public prototype_ `virtual void SetEditingLOD(EMeshLODIdentifier RequestedEditingLOD);` — Configure active LOD to edit. Can only call this after Component is configured in base UPrimitiveComponentToolTarget. If requested LOD does not exist, fall back to one that does.
- L43 _public function_ `virtual EMeshLODIdentifier GetEditingLOD() const` — @return current editing LOD
- L46 _public prototype_ `virtual bool IsValid() const override;`
- L51 _public prototype_ `virtual const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) override;` — IMeshDescriptionProvider implementation
- L52 _public prototype_ `virtual FMeshDescription GetMeshDescriptionCopy(const FGetMeshParameters& GetMeshParams) override;`
- L53 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() override;`
- L54 _public function_ `virtual bool SupportsLODs() const override`
- L55 _public prototype_ `virtual TArray<EMeshLODIdentifier> GetAvailableLODs(bool bSkipAutoGenerated = true) const override;`
- L56 _public function_ `virtual EMeshLODIdentifier GetMeshDescriptionLOD() const override`
- L57 _public prototype_ `virtual TArray<int32> GetPolygonGroupToMaterialIndexMap() const override;`
- L62 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider
- L63 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh(const FGetMeshParameters& InGetMeshParams) override;`
- L67 _public prototype_ `virtual int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L68 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L69 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials) const override;`
- L70 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override;`
- L73 _public prototype_ `virtual UStaticMesh* GetStaticMesh() const override;` — IStaticMeshBackedTarget
- L76 _public prototype_ `virtual UBodySetup* GetBodySetup() const override;` — IPhysicsDataSource
- L77 _public prototype_ `virtual IInterface_CollisionDataProvider* GetComplexCollisionProvider() const override;`
- L84 _protected member_ `EMeshLODIdentifier EditingLOD = EMeshLODIdentifier::LOD0;`
- L89 _private member_ `UStaticMeshToolTarget::FMeshDescriptionCache CachedMeshDescriptions;`

#### class `UStaticMeshComponentToolTarget`  
`class UStaticMeshComponentToolTarget : public UStaticMeshComponentReadOnlyToolTarget, public IMeshDescriptionCommitter, public IDynamicMeshCommitter`  
_L97-118_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UStaticMeshComponentReadOnlyToolTarget,IMeshDescriptionCommitter,IDynamicMeshCommitter`
- desc: A tool target backed by a static mesh component that can provide and take a mesh description.
- L104 _private prototype_ `virtual void CommitDynamicMesh(const UE::Geometry::FDynamicMesh3& Mesh, const FDynamicMeshCommitInfo& CommitInfo) override;` — IDynamicMeshCommitter
- L108 _private prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitParams = FCommitMeshParameters()) override;` — IMeshDescriptionCommitter implementation
- L114 _private function_ `virtual TArray<int32> GetPolygonGroupToMaterialIndexMap() const override` — Note: This method is on both the IMeshDescriptionCommitter and IMeshDescriptionProvider interface. The UStaticMeshComponentReadOnlyToolTarget base class only implements the Provider; we lift it to here so that the IMeshDescriptionCommitter interface will also find/call it.

#### class `UStaticMeshComponentToolTargetFactory`  
`class UStaticMeshComponentToolTargetFactory : public UToolTargetFactory`  
_L123-144_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for UStaticMeshComponentToolTarget to be used by the target manager.
- L128 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L130 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`
- L133 _public function_ `virtual EMeshLODIdentifier GetActiveEditingLOD() const`
- L134 _public prototype_ `virtual void SetActiveEditingLOD(EMeshLODIdentifier NewEditingLOD);`
- L136 _public prototype_ `static bool CanWriteToSource(const UObject* Source);`
- L140 _protected member_ `EMeshLODIdentifier EditingLOD = EMeshLODIdentifier::LOD0;` — LOD to edit, default is to edit LOD0
- L143 _private prototype_ `static const UStaticMesh* SourceToStaticMesh(const UObject* SourceObject);`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ToolTargets/StaticMeshToolTarget.h` (Public)


#### class `UStaticMeshReadOnlyToolTarget`  
`class UStaticMeshReadOnlyToolTarget : public UToolTarget, public IMeshDescriptionProvider, public IMaterialProvider, public IStaticMeshBackedTarget, public IDynamicMeshProvider`  
_L30-126_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTarget,IMeshDescriptionProvider,IMaterialProvider,IStaticMeshBackedTarget,IDynamicMeshProvider`
- desc: A tool target backed by a static mesh asset that can provide and take a mesh description, without 'committer' interfaces for writing to the source static mesh asset. This is a special tool target that refers to the underlying asset (in this case a static mesh), rather than indirectly through a component. This type of target is used in cases, such as opening an asset through the content browser, when there is no component available.
- L44 _public prototype_ `virtual void SetEditingLOD(EMeshLODIdentifier RequestedEditingLOD);` — Configure active LOD to edit. Can only call this after Component is configured in base UPrimitiveComponentToolTarget. If requested LOD does not exist, fall back to one that does.
- L47 _public function_ `virtual EMeshLODIdentifier GetEditingLOD() const` — @return current editing LOD
- L50 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget
- L53 _public prototype_ `virtual const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) override;` — IMeshDescriptionProvider implementation
- L54 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() override;`
- L55 _public function_ `virtual bool SupportsLODs() const override`
- L56 _public prototype_ `virtual TArray<EMeshLODIdentifier> GetAvailableLODs(bool bSkipAutoGenerated = true) const override;`
- L57 _public function_ `virtual EMeshLODIdentifier GetMeshDescriptionLOD() const override`
- L58 _public prototype_ `virtual TArray<int32> GetPolygonGroupToMaterialIndexMap() const override;`
- L61 _public prototype_ `static TArray<int32> MapSectionToMaterialID(const UStaticMesh* Mesh, EMeshLODIdentifier EditingLOD);` — helper to get the material mapping returned by GetPolygonGroupToMaterialIndexMap for any static mesh
- L65 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider
- L66 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh(const FGetMeshParameters& InGetMeshParams) override;`
- L70 _public prototype_ `virtual int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L71 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L72 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials) const override;`
- L73 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override;`
- L76 _public prototype_ `virtual UStaticMesh* GetStaticMesh() const override;` — IStaticMeshBackedTarget
- L87 _public typedef_ `using FMeshDescriptionCache = TMap<int32, FCachedMeshDescription>;`
- L99 _public prototype_ `static const FMeshDescription* GetMeshDescriptionWithScaleApplied(const UStaticMesh* Mesh, int32 UseLOD, FMeshDescriptionCache& Cache, const FGetMeshDescriptionOptions& Options = FGetMeshDescriptionOptions::Default());`
- L102 _protected member_ `TWeakObjectPtr<UStaticMesh> StaticMesh = nullptr;`
- L104 _protected member_ `EMeshLODIdentifier EditingLOD = EMeshLODIdentifier::LOD0;`
- L113 _protected prototype_ `static bool HasNonGeneratedLOD(const UStaticMesh* StaticMesh, EMeshLODIdentifier MeshLOD);` — returns true if the mesh has a non-generated LOD of the requested level.  Interprets EMeshLODIdentifier::Default as LOD0
- L114 _protected prototype_ `static EMeshLODIdentifier GetValidEditingLOD(const UStaticMesh* StaticMesh, EMeshLODIdentifier RequestedEditingLOD);`
- L116 _protected prototype_ `static TArray<EMeshLODIdentifier> GetAvailableLODs(const UStaticMesh* StaticMesh, bool bSkipAutoGenerated);`
- L117 _protected prototype_ `static void GetMaterialSet(const UStaticMesh* StaticMesh, FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials);`
- L119 _protected prototype_ `static bool CommitMaterialSetUpdate(UStaticMesh* SkeletalMesh, const FComponentMaterialSet& MaterialSet, bool bApplyToAsset);`
- L125 _private member_ `FMeshDescriptionCache CachedMeshDescriptions;` — In some cases we need to modify the mesh description that we pass to tools, e.g. to account for the BuildScale, and in those cases we retain the storage here to cover the lifetime of the pointer returned by GetMeshDescription()

#### struct `UStaticMeshReadOnlyToolTarget::FCachedMeshDescription`  
`struct FCachedMeshDescription`  
_L82-86_
- desc: helper struct to cache mesh descriptions, so we can provide the const ptr GetMeshDescription API while still handling the Build Scale
- L84 _public member_ `FMeshDescription* Source;`
- L85 _public member_ `TUniquePtr<FMeshDescription> Copy;`

#### struct `UStaticMeshReadOnlyToolTarget::FGetMeshDescriptionOptions`  
`struct FGetMeshDescriptionOptions`  
_L90-98_
- desc: helper to get the mesh description with build scale applied, using/updating the cache as needed
- L92 _public member_ `bool bAllowRecomputeNormals = true;`
- L93 _public member_ `bool bAllowRecomputeTangents = true;`
- L94 _public function_ `static FGetMeshDescriptionOptions Default()`

#### class `UStaticMeshToolTarget`  
`class UStaticMeshToolTarget : public UStaticMeshReadOnlyToolTarget, public IMeshDescriptionCommitter, public IDynamicMeshCommitter`  
_L136-165_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UStaticMeshReadOnlyToolTarget,IMeshDescriptionCommitter,IDynamicMeshCommitter`
- desc: A tool target backed by a static mesh asset that can provide and take a mesh description. This is a special tool target that refers to the underlying asset (in this case a static mesh), rather than indirectly through a component. This type of target is used in cases, such as opening an asset through the content browser, when there is no component available.
- L145 _public prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitParams = FCommitMeshParameters()) override;` — IMeshDescriptionCommitter implementation
- L149 _public prototype_ `virtual void CommitDynamicMesh(const UE::Geometry::FDynamicMesh3& Mesh, const FDynamicMeshCommitInfo& CommitInfo) override;` — IDynamicMeshCommitter
- L155 _public function_ `virtual TArray<int32> GetPolygonGroupToMaterialIndexMap() const override` — Note: This method is on both the IMeshDescriptionCommitter and IMeshDescriptionProvider interface. The UStaticMeshReadOnlyToolTarget base class only implements the Provider; we lift it to here so that the IMeshDescriptionCommitter interface will also find/call it.
- L163 _protected prototype_ `static void CommitMeshDescription(UStaticMesh* StaticMesh, const FCommitter& Committer, EMeshLODIdentifier EditingLODIn);`

#### class `UStaticMeshToolTargetFactory`  
`class UStaticMeshToolTargetFactory : public UToolTargetFactory`  
_L170-191_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for UStaticMeshToolTarget to be used by the target manager.
- L176 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L178 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`
- L183 _public function_ `virtual EMeshLODIdentifier GetActiveEditingLOD() const`
- L184 _public prototype_ `virtual void SetActiveEditingLOD(EMeshLODIdentifier NewEditingLOD);`
- L186 _public prototype_ `static bool CanWriteToSource(const UObject* Source);`
- L190 _protected member_ `EMeshLODIdentifier EditingLOD = EMeshLODIdentifier::LOD0;` — LOD to edit, default is to edit LOD0

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ToolTargets/VolumeComponentTarget.h` (Public)


#### class `FVolumeComponentTargetFactory`  
`class FVolumeComponentTargetFactory : public FComponentTargetFactory`  
_L13-18_
- inherits: `FComponentTargetFactory`
- L16 _public prototype_ `bool CanBuild(UActorComponent* Candidate) override;`
- L17 _public prototype_ `TUniquePtr<FPrimitiveComponentTarget> Build(UPrimitiveComponent* PrimitiveComponent) override;`

#### class `FVolumeComponentTarget`  
`class FVolumeComponentTarget : public FPrimitiveComponentTarget`  
_L21-41_
- inherits: `FPrimitiveComponentTarget`
- desc: Deprecated. Use the tool target instead.
- L25 _public prototype_ `FVolumeComponentTarget(UPrimitiveComponent* Component);`
- L27 _public prototype_ `FMeshDescription* GetMesh() override;`
- L28 _public prototype_ `void CommitMesh(const FCommitter&) override;`
- L30 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bAssetMaterials) const override;`
- L31 _public function_ `virtual void CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override`
- L33 _public prototype_ `virtual bool HasSameSourceData(const FPrimitiveComponentTarget& OtherTarget) const override;`
- L35 _public function_ `const UE::Conversion::FVolumeToMeshOptions& GetVolumeToMeshOptions()`
- L38 _protected member_ `TUniquePtr<FMeshDescription> ConvertedMeshDescription;`
- L40 _protected member_ `UE::Conversion::FVolumeToMeshOptions VolumeToMeshOptions;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponentsEditorOnly/Public/ToolTargets/VolumeComponentToolTarget.h` (Public)


#### class `UVolumeComponentToolTarget`  
`class UVolumeComponentToolTarget : public UPrimitiveComponentToolTarget, public IMaterialProvider, public IPhysicsDataSource, public IDynamicMeshCommitter, public IDynamicMeshProvider, public IMeshDescriptionCommitter, public IMeshDescriptionProvider`  
_L34-86_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UPrimitiveComponentToolTarget,IMaterialProvider,IPhysicsDataSource,IDynamicMeshCommitter,IDynamicMeshProvider,IMeshDescriptionCommitter,IMeshDescriptionProvider`
- desc: A tool target backed by AVolume
- L43 _public prototype_ `UVolumeComponentToolTarget();`
- L45 _public function_ `const UE::Conversion::FVolumeToMeshOptions& GetVolumeToMeshOptions()`
- L48 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider implementation
- L51 _public prototype_ `virtual void CommitDynamicMesh(const UE::Geometry::FDynamicMesh3& Mesh, const FDynamicMeshCommitInfo&) override;` — IDynamicMeshCommitter implementation
- L55 _public prototype_ `virtual int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L56 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L58 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials) const override;` — Ignores bPreferAssetMaterials
- L61 _public function_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override` — Doesn't actually do anything for a volume
- L64 _public prototype_ `virtual const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) override;` — IMeshDescriptionProvider implementation
- L65 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() override;`
- L68 _public prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitMeshParams = FCommitMeshParameters()) override;` — IMeshDescritpionCommitter implementation
- L72 _public prototype_ `virtual UBodySetup* GetBodySetup() const override;` — IPhysicsDataSource implementation
- L74 _public function_ `virtual IInterface_CollisionDataProvider* GetComplexCollisionProvider() const override` — always returns null because volumes do not support IInterface_CollisionDataProvider
- L79 _protected member_ `UE::Conversion::FVolumeToMeshOptions VolumeToMeshOptions;`
- L83 _protected member_ `TSharedPtr<FMeshDescription, ESPMode::ThreadSafe> ConvertedMeshDescription;` — This isn't for caching- we have to take ownership of the mesh description because it is expected for things like a static mesh.

#### class `UVolumeComponentToolTargetFactory`  
`class UVolumeComponentToolTargetFactory : public UToolTargetFactory`  
_L90-99_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for UVolumeComponentToolTarget to be used by the target manager.
- L96 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L98 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MODELINGCOMPONENTSEDITORONLY_API`
- L28 _externvar_ `extern TAutoConsoleVariable<int32> CVarModelingMaxVolumeTriangleCount;` — The CVar "modeling.VolumeMaxTriCount" is used as a cap on triangles that the various Modeling Mode Tools will allow an output AVolume to have. If this triangle count is exceeded, the mesh used to create/update the AVolume will be auto-simplified. This is necessary because all AVolume process is done on the game thread, and a large Volume (eg with 100k faces) will hang the editor for a long time when it is created. The default is set to 500.
