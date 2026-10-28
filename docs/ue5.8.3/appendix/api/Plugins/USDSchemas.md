# Plugins / USDSchemas

- module root: `Plugins/Importers/USDImporter/Source/USDSchemas`
- headers: 22; symbols: 168
- symbol kinds: class=19, function=1, macro=11, member=13, namespace=9, prototype=104, typedef=11
- PrivateDependencyModuleNames: AudioEditor, BlueprintGraph, Boost, CinematicCamera, Core, CoreUObject, Engine, GeometryCache, GeometryCacheUSD, GeometryCore, HairStrandsCore, HairStrandsEditor, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes, InterchangePipelines, Kismet, LiveLinkAnimationCore, LiveLinkComponents, LiveLinkGraphNode, LiveLinkInterface, MaterialEditor, MaterialX, MeshDescription, MeshUtilities, PhysicsUtilities, PropertyEditor, RHI, RenderCore, Slate, SlateCore, SparseVolumeTexture, StaticMeshDescription, USDClasses, UnrealEd, UnrealUSDWrapper
- PublicDependencyModuleNames: USDUtilities

### `Plugins/Importers/USDImporter/Source/USDSchemas/Private/MeshTranslationImpl.h` (Private)


#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UsdUtils`
- L32 _namespace_ `namespace MeshTranslationImpl`
- L35 _prototype_ `TMap<const UsdUtils::FUsdPrimMaterialSlot*, UMaterialInterface*> ResolveMaterialAssignmentInfo( const pxr::UsdPrim& UsdPrim, const TArray<UsdUtils::FUsdPrimMaterialAssignmentInfo>& AssignmentInfo, UUsdAssetCache3& AssetCache, FUsdPrimLinkCache& PrimLinkCache, EObjectFlags Flags, bool bShareAssetsForIdenticalPrims );` (scope `MeshTranslationImpl`) — Resolves the material assignments in AssignmentInfo, returning an UMaterialInterface for each material slot
- L48 _prototype_ `void SetMaterialOverrides( const pxr::UsdPrim& Prim, const TArray<UMaterialInterface*>& ExistingAssignments, UMeshComponent& MeshComponent, FUsdSchemaTranslationContext& Context );` (scope `MeshTranslationImpl`) — Sets the material overrides on MeshComponent according to the material assignments of the UsdGeomMesh Prim. Warning: This function will temporarily switch the active LOD variant if one exists, so it's *not* thread safe!
- L55 _prototype_ `void RecordSourcePrimsForMaterialSlots( const TArray<UsdUtils::FUsdPrimMaterialAssignmentInfo>& LODIndexToMaterialInfo, UUsdMeshAssetUserData* UserData );` (scope `MeshTranslationImpl`)

### `Plugins/Importers/USDImporter/Source/USDSchemas/Private/USDGroomTranslatorUtils.h` (Private)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L27 _namespace_ `namespace UsdGroomTranslatorUtils`
- L30 _prototype_ `void CreateGroomBindingAsset( const pxr::UsdPrim& Prim, UUsdAssetCache3& AssetCache, FUsdPrimLinkCache& PrimLinkCache, EObjectFlags ObjectFlags, bool bShareAssetsForIdenticalPrims );` (scope `UsdGroomTranslatorUtils`) — Create the groom binding asset for the given Prim with GroomBindingAPI and cache it in the AssetCache
- L39 _prototype_ `void SetGroomFromPrim(const pxr::UsdPrim& Prim, const FUsdPrimLinkCache& PrimLinkCache, USceneComponent* SceneComponent);` (scope `UsdGroomTranslatorUtils`) — Set the groom asset targeted by the given prim with GroomBindingAPI on the SceneComponent (with a GroomComponent as a direct child)
- L42 _prototype_ `FString GetStrandsGroomCachePrimPath(const UE::FSdfPath& PrimPath);` (scope `UsdGroomTranslatorUtils`) — Get the (pseudo) prim path for the strands GroomCache associated with a groom prim

### `Plugins/Importers/USDImporter/Source/USDSchemas/Private/USDTranslatorUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UsdUnreal`
- L11 _namespace_ `namespace TranslatorUtils` (scope `UsdUnreal`)
- L14 _prototype_ `void AbandonFailedAsset(UObject* Asset, UUsdAssetCache3* AssetCache, FUsdPrimLinkCache* PrimLinkCache);` (scope `UsdUnreal::TranslatorUtils`) — Properly deletes the asset and removes it from the asset and info caches, if provided

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/Custom/MaterialXUSDShadeMaterialTranslator.h` (Public)


#### class `FMaterialXUsdShadeMaterialTranslator`  
`class FMaterialXUsdShadeMaterialTranslator : public FUsdShadeMaterialTranslator`  
_L13-21_
- inherits: `FUsdShadeMaterialTranslator`
- L15 _private typedef_ `using Super = FUsdShadeMaterialTranslator;`
- L20 _public prototype_ `virtual void CreateAssets() override;`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDGeomCameraTranslator.h` (Public)


#### class `FUsdGeomCameraTranslator`  
`class FUsdGeomCameraTranslator : public FUsdGeomXformableTranslator`  
_L11-21_
- inherits: `FUsdGeomXformableTranslator`
- L16 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L17 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L19 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L20 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDGeomMeshTranslator.h` (Public)


#### class `FBaseBuildStaticMeshTaskChain`  
`class FBaseBuildStaticMeshTaskChain : public FUsdSchemaTranslatorTaskChain`  
_L25-52_
- inherits: `FUsdSchemaTranslatorTaskChain`
- L28 _public prototype_ `explicit FBaseBuildStaticMeshTaskChain( const TSharedRef<FUsdSchemaTranslationContext>& InContext, const UE::FSdfPath& InPrimPath );`
- L35 _protected member_ `UE::FSdfPath PrimPath;` — Inputs
- L36 _protected member_ `TSharedRef<FUsdSchemaTranslationContext> Context;`
- L37 _protected member_ `TArray<FMeshDescription> LODIndexToMeshDescription;`
- L40 _protected member_ `UStaticMesh* StaticMesh = nullptr;` — Outputs
- L43 _protected member_ `TSharedPtr<FStaticMeshComponentRecreateRenderStateContext> RecreateRenderStateContextPtr;` — Required to prevent StaticMesh from being used for drawing while it is being rebuilt
- L46 _protected function_ `UE::FUsdPrim GetPrim() const`
- L51 _protected prototype_ `virtual void SetupTasks();`

#### class `FBuildStaticMeshTaskChain`  
`class FBuildStaticMeshTaskChain : public FBaseBuildStaticMeshTaskChain`  
_L54-76_
- inherits: `FBaseBuildStaticMeshTaskChain`
- L57 _public prototype_ `explicit FBuildStaticMeshTaskChain( const TSharedRef<FUsdSchemaTranslationContext>& InContext, const UE::FSdfPath& InPrimPath, const TOptional<UE::FSdfPath>& AlternativePrimToLinkAssetsTo = {} );`
- L65 _protected member_ `TArray<UsdUtils::FUsdPrimMaterialAssignmentInfo> LODIndexToMaterialInfo;` — Inputs
- L68 _protected member_ `FUsdCombinedPrimMetadata LODMetadata;` — We collect metadata early (during LOD parsing) so that we don't have to flip through LODs multiple times
- L71 _protected member_ `TOptional<UE::FSdfPath> AlternativePrimToLinkAssetsTo;` — Outputs
- L72 _protected member_ `bool bCollectedMetadata = false;`
- L75 _protected prototype_ `virtual void SetupTasks() override;`

#### class `FGeomMeshCreateAssetsTaskChain`  
`class FGeomMeshCreateAssetsTaskChain : public FBuildStaticMeshTaskChain`  
_L78-94_
- inherits: `FBuildStaticMeshTaskChain`
- L81 _public prototype_ `explicit FGeomMeshCreateAssetsTaskChain( const TSharedRef<FUsdSchemaTranslationContext>& InContext, const UE::FSdfPath& PrimPath, const TOptional<UE::FSdfPath>& AlternativePrimToLinkAssetsTo = {}, const FTransform& AdditionalTransform = FTransform::Identity );`
- L90 _protected member_ `FTransform AdditionalTransform;` — Inputs
- L93 _protected prototype_ `virtual void SetupTasks() override;`

#### class `FUsdGeomMeshTranslator`  
`class FUsdGeomMeshTranslator : public FUsdGeomXformableTranslator`  
_L96-130_
- inherits: `FUsdGeomXformableTranslator`
- L99 _public typedef_ `using Super = FUsdGeomXformableTranslator;`
- L103 _public prototype_ `FUsdGeomMeshTranslator(const FUsdGeomMeshTranslator& Other) = delete;`
- L104 _public prototype_ `FUsdGeomMeshTranslator& operator=(const FUsdGeomMeshTranslator& Other) = delete;`
- L106 _public prototype_ `virtual void CreateAssets() override;`
- L107 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L108 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L110 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L111 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L113 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`
- L118 _protected prototype_ `bool IsMeshPrim() const;` — Because of how the GroomTranslator derives the GeometryCacheTranslator that derives this, we may end up in situations where this translator is not invoked on Mesh prims directly, and so we just yield back to the Xformable translator
- L129 _protected prototype_ `bool ShouldSkipSkinnablePrim(bool bCheckForComponent = false) const;` — Returns true if the Mesh prim we're meant to translate is inside a SkelRoot and has the SkelBindingAPI. We handle skeletal data now via an UsdSkelSkeletonTranslator for each Skeleton prim we encounter (the SkelRootTranslator has been deprecated). The SkeletonTranslator can find the skinned meshes for its skeleton on its own, regardless of where they are, but the fact that we don't have a SkelRootTranslator collapsing anymore means we'll get FUsdGeomMeshTranslator invokations on skinned mesh prims that were already handled by a SkeletonTranslator somewhere else. This check lets us avoid those meshes. The "bCheckForComponent" parameter exists because we may want to always skip spawning assets for a skinnable prim (as a SkeletonTranslator may have already handled the mesh data), but still want to spawn a component in some cases (e.g. in the edge case that the skinned mesh prim has a transform and non-skinned children that inherit it)

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API USDSCHEMAS_API`
- L20 _namespace_ `namespace UsdUtils`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDGeomPointInstancerTranslator.h` (Public)


#### class `FUsdGeomPointInstancerCreateAssetsTaskChain`  
`class FUsdGeomPointInstancerCreateAssetsTaskChain : public FBuildStaticMeshTaskChain`  
_L14-31_
- inherits: `FBuildStaticMeshTaskChain`
- L17 _public prototype_ `explicit FUsdGeomPointInstancerCreateAssetsTaskChain( const TSharedRef<FUsdSchemaTranslationContext>& InContext, const UE::FSdfPath& InPrimPath, bool bIgnoreTopLevelTransform, bool bIgnoreTopLevelVisibility, const TOptional<UE::FSdfPath>& AlternativePrimToLinkAssetsTo = {} );`
- L26 _protected prototype_ `virtual void SetupTasks() override;`
- L29 _private member_ `bool bIgnoreTopLevelTransform = false;`
- L30 _private member_ `bool bIgnoreTopLevelVisibility = false;`

#### class `FUsdGeomPointInstancerTranslator`  
`class FUsdGeomPointInstancerTranslator : public FUsdGeomXformableTranslator`  
_L33-52_
- inherits: `FUsdGeomXformableTranslator`
- L36 _public typedef_ `using Super = FUsdGeomXformableTranslator;`
- L39 _public prototype_ `virtual void CreateAssets() override;`
- L40 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L41 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L48 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;` — Point instancers will always collapse (i.e. "be in charge of") their entire prim subtree. If we have a nested point instancer situation, the parentmost point instancer will be in charge of collapsing everything below it, so returning true to "CanBeCollapsed" in that case won't really help anything. We only return true from CanBeCollapsed if e.g. a generic Xform prim should be able to collapse us too (like when we're collapsing even simple, not-nested point instancers).
- L49 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L51 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDGeomPrimitiveTranslator.h` (Public)


#### class `FUsdGeomPrimitiveTranslator`  
`class FUsdGeomPrimitiveTranslator : public FUsdGeomXformableTranslator`  
_L13-30_
- inherits: `FUsdGeomXformableTranslator`
- L16 _public typedef_ `using Super = FUsdGeomXformableTranslator;`
- L19 _public prototype_ `FUsdGeomPrimitiveTranslator(const FUsdGeomPrimitiveTranslator& Other) = delete;`
- L20 _public prototype_ `FUsdGeomPrimitiveTranslator& operator=(const FUsdGeomPrimitiveTranslator& Other) = delete;`
- L22 _public prototype_ `virtual void CreateAssets() override;`
- L23 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L24 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L26 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L27 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L29 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDGeomXformableTranslator.h` (Public)


#### class `FUsdGeomXformableTranslator`  
`class FUsdGeomXformableTranslator : public FUsdSchemaTranslator`  
_L16-50_
- inherits: `FUsdSchemaTranslator`
- L21 _public prototype_ `explicit FUsdGeomXformableTranslator( TSubclassOf<USceneComponent> InComponentTypeOverride, TSharedRef<FUsdSchemaTranslationContext> InContext, const UE::FUsdTyped& InSchema );`
- L27 _public prototype_ `virtual void CreateAssets() override;`
- L28 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L29 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L31 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L32 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L34 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`
- L37 _public prototype_ `USceneComponent* CreateComponentsEx(TOptional<TSubclassOf<USceneComponent>> ComponentType, TOptional<bool> bNeedsActor);` — If the optional parameters are not set, we'll figure them out automatically.
- L44 _protected prototype_ `USceneComponent* CreateAlternativeDrawModeComponents(EUsdDrawMode DrawMode);` — Creates actors, components and assets in case we have an alt draw mode like bounds or cards. In theory *any* prim can have these, but we're placing these on FUsdGeomXformableTranslator as we're assuming only Xformables (something drawable in the first place) can realistically use an alternative draw mode (i.e. we're not going to do much placing these on a Material prim, that can't even have an Xform)
- L45 _protected prototype_ `void UpdateAlternativeDrawModeComponents(USceneComponent* SceneComponent, EUsdDrawMode DrawMode);`
- L46 _protected prototype_ `void CreateAlternativeDrawModeAssets(EUsdDrawMode DrawMode);`
- L49 _private member_ `TOptional<TSubclassOf<USceneComponent>> ComponentTypeOverride;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDGeometryCacheTranslator.h` (Public)


#### class `FUsdGeometryCacheTranslator`  
`class FUsdGeometryCacheTranslator : public FUsdGeomMeshTranslator`  
_L9-30_
- inherits: `FUsdGeomMeshTranslator`
- L12 _public typedef_ `using Super = FUsdGeomMeshTranslator;`
- L16 _public prototype_ `FUsdGeometryCacheTranslator(const FUsdGeometryCacheTranslator& Other) = delete;`
- L17 _public prototype_ `FUsdGeometryCacheTranslator& operator=(const FUsdGeometryCacheTranslator& Other) = delete;`
- L19 _public prototype_ `virtual void CreateAssets() override;`
- L20 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L21 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L23 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L24 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L26 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`
- L29 _private prototype_ `bool IsPotentialGeometryCacheRoot() const;`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDGroomTranslator.h` (Public)


#### class `FUsdGroomTranslator`  
`class FUsdGroomTranslator : public FUsdGeometryCacheTranslator`  
_L9-27_
- inherits: `FUsdGeometryCacheTranslator`
- L12 _public typedef_ `using Super = FUsdGeometryCacheTranslator;`
- L15 _public prototype_ `virtual void CreateAssets() override;`
- L17 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L18 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L20 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L21 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L23 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`
- L26 _private prototype_ `bool IsGroomPrim() const;`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDInfoCache.h` (Public)
_(no declarations extracted)_

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDLuxLightTranslator.h` (Public)


#### class `FUsdLuxLightTranslator`  
`class FUsdLuxLightTranslator : public FUsdGeomXformableTranslator`  
_L13-27_
- inherits: `FUsdGeomXformableTranslator`
- L15 _private typedef_ `using Super = FUsdGeomXformableTranslator;`
- L21 _public prototype_ `virtual void CreateAssets() override;`
- L22 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L23 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent);`
- L25 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L26 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDMediaSpatialAudioTranslator.h` (Public)


#### class `FUsdMediaSpatialAudioTranslator`  
`class FUsdMediaSpatialAudioTranslator : public FUsdGeomXformableTranslator`  
_L13-29_
- inherits: `FUsdGeomXformableTranslator`
- L15 _private typedef_ `using Super = FUsdGeomXformableTranslator;`
- L21 _public prototype_ `virtual void CreateAssets() override;`
- L22 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L23 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L25 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L26 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L28 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDNaniteAssemblyTranslator.h` (Public)


#### class `FUsdNaniteAssemblyTranslator`  
`class FUsdNaniteAssemblyTranslator : public FUsdSchemaTranslator`  
_L11-24_
- inherits: `FUsdSchemaTranslator`
- L16 _public typedef_ `using Super = FUsdSchemaTranslator;`
- L20 _public prototype_ `FUsdNaniteAssemblyTranslator(const FUsdNaniteAssemblyTranslator& Other) = delete;`
- L21 _public prototype_ `FUsdNaniteAssemblyTranslator& operator=(const FUsdNaniteAssemblyTranslator& Other) = delete;`
- L23 _public prototype_ `virtual void CreateAssets() override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDPrimLinkCache.h` (Public)
_(no declarations extracted)_

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDSchemaTranslator.h` (Public)
_(no declarations extracted)_

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDSchemasModule.h` (Public)


#### class `IUsdSchemasModule`  
`class IUsdSchemasModule : public IModuleInterface`  
_L13-18_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual FUsdSchemaTranslatorRegistry& GetTranslatorRegistry() = 0;` — `UE_DEPRECATED(5.6, "Use FUsdSchemaTranslatorRegistry::Get() from Objects/USDSchemaTranslator.h file in the USDUtilities module (USDCore plugin).")`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UsdUnreal`
- L20 _namespace_ `namespace Analytics` (scope `UsdUnreal`)
- L23 _prototype_ `void CollectSchemaAnalytics(const UE::FUsdStage& Stage, const FString& EventName);` (scope `UsdUnreal::Analytics`) — Collects analytics about custom schemas, unsupported native schemas, and the count of custom registered schema translators

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDShadeMaterialTranslator.h` (Public)


#### class `FUsdShadeMaterialTranslator`  
`class FUsdShadeMaterialTranslator : public FUsdSchemaTranslator`  
_L11-25_
- inherits: `FUsdSchemaTranslator`
- L16 _public prototype_ `virtual void CreateAssets() override;`
- L18 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L19 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L21 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`
- L24 _protected prototype_ `virtual void PostImportMaterial(const FString& PrefixedMaterialHash, UMaterialInterface* ImportedMaterial);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDSkelRootTranslator.h` (Public)
_(no declarations extracted)_

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDSkelSkeletonTranslator.h` (Public)


#### class `FUsdSkelSkeletonTranslator`  
`class FUsdSkelSkeletonTranslator : public FUsdGeomXformableTranslator`  
_L11-26_
- inherits: `FUsdGeomXformableTranslator`
- L13 _private typedef_ `using Super = FUsdGeomXformableTranslator;`
- L18 _public prototype_ `virtual void CreateAssets() override;`
- L19 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L20 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L22 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L23 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L25 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDSCHEMAS_API`

### `Plugins/Importers/USDImporter/Source/USDSchemas/Public/USDVolVolumeTranslator.h` (Public)


#### class `FUsdVolVolumeTranslator`  
`class FUsdVolVolumeTranslator : public FUsdGeomXformableTranslator`  
_L13-29_
- inherits: `FUsdGeomXformableTranslator`
- L15 _private typedef_ `using Super = FUsdGeomXformableTranslator;`
- L21 _public prototype_ `virtual void CreateAssets() override;`
- L22 _public prototype_ `virtual USceneComponent* CreateComponents() override;`
- L23 _public prototype_ `virtual void UpdateComponents(USceneComponent* SceneComponent) override;`
- L25 _public prototype_ `virtual bool CollapsesChildren(ECollapsingType CollapsingType) const override;`
- L26 _public prototype_ `virtual bool CanBeCollapsed(ECollapsingType CollapsingType) const override;`
- L28 _public prototype_ `virtual TSet<UE::FSdfPath> CollectAuxiliaryPrims() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API USDSCHEMAS_API`
