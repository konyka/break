# Developer / MaterialUtilities

- module root: `Source/Developer/MaterialUtilities`
- headers: 2; symbols: 134
- symbol kinds: class=3, enum=2, enumerator=15, function=22, macro=1, member=40, namespace=2, prototype=43, struct=6
- DynamicallyLoadedModuleNames: MeshMergeUtilities
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, Landscape, MaterialBaking, RHI, RenderCore, Renderer, UnrealEd
- PrivateIncludePathModuleNames: MeshMergeUtilities
- PublicDependencyModuleNames: GeometryCore, MeshDescription, StaticMeshDescription

### `Source/Developer/MaterialUtilities/Public/MaterialUtilities.h` (Public)


#### enum `EFlattenMaterialProperties`  
`enum class EFlattenMaterialProperties : uint8`  
_L41-56_
- reflection: `UENUM()`
- desc: TODO replace this with rendering property enum when extending the system
- L43 _public enumerator_ `Diffuse`
- L44 _public enumerator_ `Metallic`
- L45 _public enumerator_ `Specular`
- L46 _public enumerator_ `Roughness`
- L47 _public enumerator_ `Anisotropy`
- L48 _public enumerator_ `Normal`
- L49 _public enumerator_ `Tangent`
- L50 _public enumerator_ `Opacity`
- L51 _public enumerator_ `Emissive`
- L52 _public enumerator_ `SubSurface`
- L53 _public enumerator_ `OpacityMask`
- L54 _public enumerator_ `AmbientOcclusion = 16`
- L55 _public enumerator_ `NumFlattenMaterialProperties`

#### struct `FSectionInfo`  
`struct FSectionInfo`  
_L59-84_
- desc: Struct to store per section info used to populate data after (multiple) meshes are merged together
- L61 _public function_ `FSectionInfo() : Material(nullptr), MaterialSlotName(NAME_None), MaterialIndex(INDEX_NONE), StartIndex(INDEX_NONE), EndIndex(INDEX_NONE), bProcessed(false), OverlayMaterial(nullptr)`
- L64 _public member_ `class UMaterialInterface* Material;` — Material used by the section
- L66 _public member_ `FName MaterialSlotName;` — Name value for the section
- L68 _public member_ `TArray<FName> EnabledProperties;` — List of properties enabled for the section (collision, cast shadow etc)
- L70 _public member_ `int32 MaterialIndex;` — Original index of Material in the source data
- L72 _public member_ `int32 StartIndex;` — Index pointing to the start set of mesh indices that belong to this section
- L74 _public member_ `int32 EndIndex;` — Index pointing to the end set of mesh indices that belong to this section
- L76 _public member_ `bool bProcessed;` — Used while baking out materials, to check which sections are and aren't being baked out
- L78 _public member_ `class UMaterialInterface* OverlayMaterial;` — Overlay material used by the section
- L80 _public function_ `bool operator==(const FSectionInfo& Other) const`

#### struct `FFlattenMaterial`  
`struct FFlattenMaterial`  
_L87-200_
- desc: Structure used for storing intermediate baked down material data/samples
- L89 _public function_ `FFlattenMaterial() : RenderSize(0, 0) , bTwoSided(false) , bIsThinSurface(false) , bDitheredLODTransition(false) , BlendMode(BLEND_Opaque) , EmissiveScale(1.0f) , UVChannel(0)`
- L104 _public function_ `bool HasData() const`
- L110 _public function_ `void ReleaseData()` — Release all the sample data
- L119 _public function_ `void FillAlphaValues(const uint8 InAlphaValue)` — Set all alpha channel values with InAlphaValue
- L130 _public function_ `const bool DoesPropertyContainData(const EFlattenMaterialProperties Property) const`
- L132 _public function_ `const bool IsPropertyConstant(const EFlattenMaterialProperties Property) const`
- L134 _public function_ `const bool ShouldGenerateDataForProperty(const EFlattenMaterialProperties Property) const`
- L136 _public function_ `const FIntPoint GetPropertySize(const EFlattenMaterialProperties Property) const`
- L137 _public function_ `void SetPropertySize(const EFlattenMaterialProperties Property, const FIntPoint& InSize)`
- L139 _public function_ `TArray<FColor>& GetPropertySamples(const EFlattenMaterialProperties Property)`
- L140 _public function_ `const TArray<FColor>& GetPropertySamples(const EFlattenMaterialProperties Property) const`
- L143 _public member_ `FGuid MaterialId;` — Material Guid
- L144 _public member_ `FIntPoint RenderSize;`
- L147 _public member_ `bool bTwoSided;` — Flag whether or not the material will have to be two-sided
- L149 _public member_ `bool bIsThinSurface;` — Flag whether or not the material will have to be thin
- L151 _public member_ `bool bDitheredLODTransition;` — Flag whether or not the material will use dithered LOD transitions
- L153 _public member_ `EBlendMode BlendMode;` — Blend mode for the new material
- L155 _public member_ `float EmissiveScale;` — Scale (maximum baked down value) for the emissive property
- L157 _public member_ `int32 UVChannel;` — UV channel to use
- L160 _private function_ `FIntPoint& GetSizesEntry(const EFlattenMaterialProperties Property)`
- L169 _private function_ `TArray<FColor>& GetSamplesEntry(const EFlattenMaterialProperties Property)`
- L178 _private function_ `const FIntPoint& GetSizesEntry(const EFlattenMaterialProperties Property) const`
- L187 _private function_ `const TArray<FColor>& GetSamplesEntry(const EFlattenMaterialProperties Property) const`
- L197 _private member_ `FIntPoint PropertySizes[(uint32)EFlattenMaterialProperties::NumFlattenMaterialProperties];` — Texture sizes for each individual property
- L199 _private member_ `TArray<FColor> PropertySamples[(uint32)EFlattenMaterialProperties::NumFlattenMaterialProperties];` — Baked down texture samples for each individual property

#### struct `FExportMaterialProxyCache`  
`struct FExportMaterialProxyCache`  
_L203-214_
- desc: Export material proxy cache
- L207 _public member_ `class FMaterialRenderProxy* Proxies[MP_MAX];` — Material proxies for each property. Note: we're not handling all properties here, so hold only up to MP_Normal inclusive.
- L209 _public prototype_ `FExportMaterialProxyCache();`
- L210 _public prototype_ `~FExportMaterialProxyCache();`
- L213 _public prototype_ `void Release();` — Releasing the cached render proxies

#### struct `FMaterialMergeData`  
`struct FMaterialMergeData`  
_L217-271_
- desc: Intermediate material merging data
- L220 _public member_ `FExportMaterialProxyCache* ProxyCache;` — Material proxy cache, eliminates shader compilations when a material is baked out multiple times for different meshes
- L224 _public member_ `class UMaterialInterface* Material;` — Material that is being baked out
- L226 _public member_ `const struct FMeshDescription* Mesh;` — Raw mesh data used to bake out the material with, optional
- L228 _public member_ `const FSkeletalMeshLODRenderData* LODData;` — LODModel data used to bake out the material with, optional
- L230 _public member_ `int32 MaterialIndex;` — Material index to use when the material is baked out using mesh data (face material indices)
- L232 _public member_ `FBox2D TexcoordBounds;` — Optional tex coordinate bounds of original texture coordinates set
- L234 _public member_ `const TArray<FVector2D>& TexCoords;` — Optional new set of non-overlapping texture coordinates
- L236 _public member_ `FLightMapRef LightMap;`
- L237 _public member_ `FShadowMapRef ShadowMap;`
- L238 _public member_ `FUniformBufferRHIRef Buffer;`
- L239 _public member_ `int32 LightMapIndex;`
- L242 _public member_ `float EmissiveScale;` — Output emissive scale, maximum baked out emissive value (used to scale other samples, 1/EmissiveScale * Sample)
- L244 _public function_ `FMaterialMergeData( UMaterialInterface* InMaterial, const FMeshDescription* InMesh, const FSkeletalMeshLODRenderData* InLODData, int32 InMaterialIndex, FBox2D InTexcoordBounds, const TArray<FVector2D>& InTexCoords) : ProxyCache(nullptr) , Material(InMaterial) , Mesh(InMesh) , LODData(InLODData) , MaterialIndex(InMaterialIndex) , TexcoordBounds(InTexcoordBounds) , TexCoords(InTexCoords) , LightMapIndex(1) , EmissiveScale(0.0f)`
- L264 _public function_ `~FMaterialMergeData()`

#### class `FMaterialUtilities`  
`class FMaterialUtilities : public IModuleInterface`  
_L291-589_
- inherits: `IModuleInterface`
- desc: Material utilities
- L295 _public prototype_ `virtual void StartupModule() override;` — Begin IModuleInterface implementation
- L296 _public prototype_ `virtual void ShutdownModule() override;`
- L307 _public prototype_ `static FIntPoint FindMaxTextureSize(UMaterialInterface* InMaterialInterface, FIntPoint MinimumSize = FIntPoint(1, 1));` — Iterate through all textures used by the material and return the maximum texture resolution used @param MaterialInterface	The material to scan for texture size @param MinimumSize		The minimum size returned @return Size (width and height)
- L312 _public prototype_ `static bool SupportsExport(bool bIsOpaque, EMaterialProperty InMaterialProperty);` — Whether material utilities support exporting specified material blend mode and property
- L321 _public prototype_ `static bool ExportLandscapeMaterial(const ALandscapeProxy* InLandscape, FFlattenMaterial& OutFlattenMaterial);` — Flattens specified landscape material @param InLandscape			Target landscape @param OutFlattenMaterial	Output flattened material @return						Whether operation was successful
- L331 _public prototype_ `static bool ExportLandscapeMaterial(const ALandscapeProxy* InLandscape, const TSet<FPrimitiveComponentId>& HiddenPrimitives, FFlattenMaterial& OutFlattenMaterial);` — Flattens specified landscape material @param InLandscape			Target landscape @param HiddenPrimitives		Primitives to hide while rendering scene to texture @param OutFlattenMaterial	Output flattened material @return						Whether operation was successful
- L347 _public prototype_ `static UTexture2D* CreateTexture(UPackage* Outer, const FString& AssetLongName, FIntPoint Size, const TArray<FColor>& Samples, TextureCompressionSettings CompressionSettings, TextureGroup LODGroup, EObjectFlags Flags, bool bSRGB, const FGuid& SourceGuidHash = FGuid());` — Generates a texture from an array of samples @param Outer					Outer for the material and texture objects, if NULL new packages will be created for each asset @param AssetLongName			Long asset path for the new texture @param Size					Resolution of the texture to generate (must match the number of samples) @param Samples				Color data for the texture @param CompressionSettings	Compression settings for the new texture @param LODGroup				LODGroup for the new texture @param Flags					ObjectFlags for the new texture @param bSRGB					Whether to set the bSRGB flag on the new texture @param SourceGuidHash		(optional) Hash (stored as Guid) to use part of the texture source's DDC key. @return						The new texture.
- L360 _public prototype_ `static UTexture2D* CreateTexture(UPackage* Outer, const FString& AssetLongName, FIntPoint Size, const TArray<FColor>& Samples, const FCreateTexture2DParameters& CreateParams, EObjectFlags Flags);` — Generates a texture from an array of samples @param Outer					Outer for the material and texture objects, if NULL new packages will be created for each asset @param AssetLongName			Long asset path for the new texture @param Size					Resolution of the texture to generate (must match the number of samples) @param Samples				Color data for the texture @param CreateParams			Params about how to set up the texture @param Flags					ObjectFlags for the new texture @return						The new texture.
- L371 _public prototype_ `static UMaterial* CreateMaterial(const FFlattenMaterial& InFlattenMaterial, UPackage* InOuter, const FString& BaseName, EObjectFlags Flags, const struct FMaterialProxySettings& MaterialProxySettings, TArray<UObject*>& OutGeneratedAssets, const TextureGroup& InTextureGroup = TEXTUREGROUP_World);` — Creates UMaterial object from a flatten material @param Outer					Outer for the material and texture objects, if NULL new packages will be created for each asset @param BaseName				BaseName for the material and texture objects, should be a long package name in case Outer is not specified @param Flags					Object flags for the material and texture objects. @param OutGeneratedAssets	List of generated assets - material, textures @return						Returns a pointer to the constructed UMaterial object.
- L381 _public prototype_ `static UMaterialInstanceConstant* CreateInstancedMaterial(UMaterialInterface* BaseMaterial, UPackage* InOuter, const FString& BaseName, EObjectFlags Flags);`
- L389 _public prototype_ `static bool ExportBaseColor(ULandscapeComponent* LandscapeComponent, int32 TextureSize, TArray<FColor>& OutSamples);` — Creates bakes textures for a ULandscapeComponent @param LandscapeComponent		The component to bake textures for @return						Whether operation was successful
- L397 _public prototype_ `static FFlattenMaterial CreateFlattenMaterialWithSettings(const FMaterialProxySettings& InMaterialLODSettings);` — Creates a FFlattenMaterial instance with the given MaterialProxySettings data @param InMaterialLODSettings  Settings containing how to material should be merged @return						Set up FFlattenMaterial according to the given settings
- L407 _public prototype_ `static void AnalyzeMaterial(class UMaterialInterface* InMaterial, const struct FMaterialProxySettings& InMaterialSettings, int32& OutNumTexCoords, bool& OutRequiresVertexData);` — Analyzes given material to determine how many texture coordinates and whether or not vertex colors are used within the material Graph @param InMaterial 			Material to analyze @param InMaterialSettings 	Settings containing how to material should be merged @param OutNumTexCoords		Number of texture coordinates used across all properties flagged for merging @param OutRequiresVertexData	Flag whether or not Vertex Data is used in the material graph for the properties flagged for merging
- L409 _public prototype_ `static void AnalyzeMaterial(class UMaterialInterface* InMaterial, const TArray<EMaterialProperty>& Properties, int32& OutNumTexCoords, bool& OutRequiresVertexData);`
- L424 _public prototype_ `static void RemapUniqueMaterialIndices(const TArray<struct FSectionInfo>& InSections, const TArray<struct FRawMeshExt>& InMeshData, const TMap<FIntPoint, TArray<int32> >& InMaterialMap, const FMaterialProxySettings& InMaterialProxySettings, const bool bBakeVertexData, const bool bMergeMaterials, TArray<bool>& OutMeshShouldBakeVertexData, TMap<FIntPoint, TArray<int32> >& OutMaterialMap, TArray<struct FSectionInfo>& OutSections);` — Remaps material indices where possible to reduce the number of materials required for creating a proxy material @param InMaterials 					List of Material interfaces (non-unique) @param InMeshData						Array of meshes who use the materials in InMaterials @param InMaterialMap					Map of MeshIDAndLOD keys with a material index array as value mapping InMeshData to the InMaterials array @param InMaterialProxySettings		Settings for creating the proxy material @param bBakeVertexData 				Flag whether or not Vertex Data should be baked down @param bMergeMaterials 				Flag whether or not materials with be merged for this mesh @param OutMeshShouldBakeVertexData	Array with Flag for each mesh whether or not Vertex Data should be baked down or is required to @param OutMaterialMap					Map of MeshIDAndLOD keys with a material index array as value mapping InMeshData to the OutMaterials array @param OutMaterials					List of Material interfaces (unique)
- L431 _public prototype_ `static void OptimizeFlattenMaterial(FFlattenMaterial& InFlattenMaterial);` — Tries to optimize the flatten material's data by picking out constant values for the various properties @param InFlattenMaterial				Flatten material to optimize
- L438 _public prototype_ `static void ResizeFlattenMaterial(FFlattenMaterial& InFlattenMaterial, const struct FMeshProxySettings& InMeshProxySettings);` — Resizes flatten material's data if applicable by comparing it with the original settings @param InFlattenMaterial				Flatten material to optimize
- L441 _public prototype_ `static void OptimizeSampleArray(TArray<FColor>& InSamples, FIntPoint& InSampleSize);` — Tries to optimize the sample array (will set to const value if all samples are equal)
- L507 _public prototype_ `static bool ExportMaterialUVDensities(UMaterialInterface* InMaterial, EMaterialQualityLevel::Type QualityLevel, ERHIFeatureLevel::Type FeatureLevel, FExportErrorManager& OutErrors);` — `UE_DEPRECATED(5.7, "Please use ExportMaterialUVDensities with EShaderPlatform argument and not ERHIFeatureLevel::Type")` — Get the material texcoord scales applied on each textures @param InMaterial			Target material @param QualityLevel		Quality level used for the shader profiling. @param FeatureLevel		Feature level used for the shader profiling. @param OutErrors			Manager to log errors (removes duplicates and similar errors) @return					Whether operation was successful
- L508 _public prototype_ `static bool ExportMaterialUVDensities(UMaterialInterface* InMaterial, EMaterialQualityLevel::Type QualityLevel, EShaderPlatform InShaderPlatform, FExportErrorManager& OutErrors);`
- L511 _public prototype_ `static void DetermineMaterialImportance(const TArray<UMaterialInterface*>& InMaterials, TArray<float>& OutImportance);` — Calculates an importance value for the given set of materials according to the texture sampler usage
- L513 _public prototype_ `static void GeneratedBinnedTextureSquares(const FVector2D DestinationSize, TArray<float>& InTexureWeights, TArray<FBox2D>& OutGeneratedBoxes);` — Generates a set of texture boxes according to the given weights and final atlas texture size
- L516 _public prototype_ `static UMaterialInterface* CreateProxyMaterialAndTextures(UPackage* OuterPackage, const FString& AssetName, const FBakeOutput& BakeOutput, const FMeshData& MeshData, const FMaterialData& MaterialData, UMaterialOptions* Options);` — Creates a proxy material and the required texture assets
- L519 _public prototype_ `static UMaterialInterface* CreateProxyMaterialAndTextures(const FString& PackageName, const FString& AssetName, const FBakeOutput& BakeOutput, const FMeshData& MeshData, const FMaterialData& MaterialData, UMaterialOptions* Options);` — Creates a proxy material and the required texture assets
- L522 _public prototype_ `static UMaterialInstanceConstant* CreateFlattenMaterialInstance(UPackage* InOuter, const FMaterialProxySettings& InMaterialProxySettings, UMaterialInterface* InBaseMaterial, const FFlattenMaterial& FlattenMaterial, const FString& AssetBasePath, const FString& AssetBaseName, TArray<UObject*>& OutAssetsToSync, FMaterialUpdateContext* MaterialUpdateContext = nullptr);` — Creates a flatten material instance and the required texture assets
- L530 _public prototype_ `static float ComputeRequiredTexelDensityFromScreenSize(const float InScreenSize, float InWorldSpaceRadius);` — Compute the required texel density needed to properly represent an object/objects covering the provided world space radius @param InScreenSize		Screen size at which the objects are expected to be be shown @param InWorldSpaceRadius	World space radius of the objects @return					The required texel density per METER
- L538 _public prototype_ `static float ComputeRequiredTexelDensityFromDrawDistance(const float InDrawDistance, float InWorldSpaceRadius);` — Compute the required texel density needed to properly represent an object/objects covering the provided world space radius @param InDrawDistance		Draw distance at which the objects are expected to be shown @param InWorldSpaceRadius	World space radius of the objects @return					The required texel density per METER
- L545 _public prototype_ `static int32 GetTextureSizeFromTargetTexelDensity(const FMeshDescription& InMesh, float InTargetTexelDensity);` — Compute the required texture size to achieve a target texel density for the given mesh. @param InMesh					The mesh for which we want to create a flatten material. @param InTargetTexelDensity	The target texel density. @return The texture size needed to achieve the required texel density.
- L552 _public prototype_ `static int32 GetTextureSizeFromTargetTexelDensity(const UE::Geometry::FDynamicMesh3& Mesh, float TargetTexelDensity);` — Compute the required texture size to achieve a target texel density for the given mesh. @param InMesh					The mesh for which we want to create a flatten material. @param InTargetTexelDensity	The target texel density. @return The texture size needed to achieve the required texel density.
- L559 _public prototype_ `static int32 GetTextureSizeFromTargetTexelDensity(double InMesh3DArea, double InMeshUVArea, double InTargetTexelDensity);` — Compute the required texture size to achieve a target texel density, given the world to UV space ratio. @param InMesh3DArea	World space area of the mesh @param InMeshUVArea	UV space area of the mesh @return The texture size needed to achieve the required texel density.
- L562 _public prototype_ `static bool IsValidFlattenMaterial(const UMaterialInterface* InBaseMaterial);` — Validate that the provided material has all the required parameters needed to be considered a flattening material
- L565 _public prototype_ `static FString GetFlattenMaterialTextureName(EFlattenMaterialProperties InProperty, UMaterialInterface* InBaseMaterial);` — Get the name of the Texture parameter associated with a given flatten material property
- L577 _private prototype_ `static UTextureRenderTarget2D* CreateRenderTarget(bool bInForceLinearGamma, bool bNormalMap, EPixelFormat InPixelFormat, FIntPoint& InTargetSize );` — Creates and add or reuses a RenderTarget from the pool @param bInForceLinearGamma	Whether or not to force linear gamma @param InPixelFormat			Pixel format of the render target @param InTargetSize			Dimensions of the render target @return						Created render target
- L580 _private prototype_ `static void ClearRenderTargetPool();` — Clears the pool with available render targets
- L583 _private prototype_ `void OnPreGarbageCollect();` — Call back for garbage collector, cleans up the RenderTargetPool if CurrentlyRendering is set to false
- L586 _private member_ `static bool CurrentlyRendering;` — Flag to indicate whether or not a texture is currently being rendered out
- L588 _private member_ `static TArray<UTextureRenderTarget2D*> RenderTargetPool;` — Pool of available render targets, cached for re-using on consecutive property rendering

#### class `FMaterialUtilities::FExportErrorManager`  
`class FExportErrorManager`  
_L447-495_
- desc: Contains errors generated when exporting material texcoord scales. Used to prevent displaying duplicates, as instances using the same shaders get the same issues.
- L451 _public function_ `FExportErrorManager(EShaderPlatform InShaderPlatform) : ShaderPlatform(InShaderPlatform)`
- L467 _public prototype_ `void Register(const UMaterialInterface* Material, FName TextureName, int32 RegisterIndex, EErrorType ErrorType);` — Register a new error. @param Material			The material having this error. @param TextureName		The texture for which the scale could not be generated. @param RegisterIndex		The register index bound to this texture. @param ErrorType			The issue encountered.
- L472 _public prototype_ `void OutputToLog();` — Output all errors registered.
- L493 _private member_ `EShaderPlatform ShaderPlatform;`
- L494 _private member_ `TMap<FError, TArray<FInstance> > ErrorInstances;`

#### enum `FMaterialUtilities::FExportErrorManager::EErrorType`  
`enum EErrorType`  
_L453-457_
- L455 _public enumerator_ `EET_IncohorentValues`
- L456 _public enumerator_ `EET_NoValues`

#### struct `FMaterialUtilities::FExportErrorManager::FError`  
`struct FError`  
_L476-483_
- L478 _public member_ `const FMaterial* Material;`
- L479 _public member_ `int32 RegisterIndex;`
- L480 _public member_ `EErrorType ErrorType;`
- L482 _public prototype_ `bool operator==(const FError& Rhs) const;`

#### struct `FMaterialUtilities::FExportErrorManager::FInstance`  
`struct FInstance`  
_L485-489_
- L487 _public member_ `const UMaterialInterface* Material;`
- L488 _public member_ `FName TextureName;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MATERIALUTILITIES_API`
- L106 _function_ `return Algo::AnyOf(PropertySamples, [](const TArray<FColor>& Samples) { return !Samples.IsEmpty(); });` (scope `FFlattenMaterial::HasData`)
- L286 _namespace_ `namespace UE`
- L286 _namespace_ `namespace Geometry` (scope `UE`)

### `Source/Developer/MaterialUtilities/Public/MeshRendering.h` (Public)


#### class `FMeshRenderer`  
`class FMeshRenderer`  
_L17-40_
- desc: Class used as an interface for baking materials to textures using mesh/vertex-data
- L21 _public prototype_ `static bool RenderMaterial( FMaterialMergeData& InMaterialData, FMaterialRenderProxy* InMaterialProxy, EMaterialProperty InMaterialProperty, UTextureRenderTarget2D* InRenderTarget, TArray<FColor>& OutBMP );` — Renders out textures for each material property for the given material, using the given mesh data or by using a simple tile rendering approach
- L30 _public prototype_ `static bool RenderMaterialTexCoordScales( FMaterialMergeData& InMaterialData, FMaterialRenderProxy* InMaterialProxy, UTextureRenderTarget2D* InRenderTarget, TArray<FFloat16Color>& OutScales );` — Renders out texcoord scales
- L39 _private function_ `FMeshRenderer()` — This class never needs to be instantiated.
