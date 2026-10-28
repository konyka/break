# Developer / MeshMergeUtilities

- module root: `Source/Developer/MeshMergeUtilities`
- headers: 12; symbols: 284
- symbol kinds: class=11, delegate=1, function=15, macro=3, member=51, prototype=189, struct=6, typedef=8
- DynamicallyLoadedModuleNames: HierarchicalLODUtilities, MeshReductionInterface, MeshUtilities
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, Landscape, MaterialBaking, MaterialUtilities, MeshUtilitiesCommon, RHI, RenderCore, Renderer, Slate, SlateCore, StaticMeshEditor, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: HierarchicalLODUtilities
- PublicDependencyModuleNames: MeshDescription, RawMesh, StaticMeshDescription
- PublicIncludePathModuleNames: MeshReductionInterface

### `Source/Developer/MeshMergeUtilities/Private/MeshMergeHelpers.h` (Private)


#### class `FMeshMergeHelpers`  
`class FMeshMergeHelpers`  
_L25-77_
- L29 _public prototype_ `static void ExtractSections(const UStaticMeshComponent* Component, int32 LODIndex, TArray<FSectionInfo>& OutSections);` — Extracting section info data from static, skeletal mesh (components)
- L30 _public prototype_ `static void ExtractSections(const USkeletalMeshComponent* Component, int32 LODIndex, TArray<FSectionInfo>& OutSections);`
- L31 _public prototype_ `static void ExtractSections(const UStaticMesh* StaticMesh, int32 LODIndex, TArray<FSectionInfo>& OutSections);`
- L34 _public prototype_ `static void ExpandInstances(const UInstancedStaticMeshComponent* InInstancedStaticMeshComponent, FMeshDescription& InOutRawMesh);` — Expanding instance data from instanced static mesh components
- L37 _public prototype_ `static void RetrieveMesh(const UStaticMeshComponent* StaticMeshComponent, int32 LODIndex, FMeshDescription& OutMeshDescription, bool bPropagateVertexColours, bool bApplyComponentTransform = true);` — Extracting mesh data in FMeshDescription form from static, skeletal mesh (components)
- L38 _public prototype_ `static void RetrieveMesh(const USkeletalMeshComponent* SkeletalMeshComponent, int32 LODIndex, FMeshDescription& OutMeshDescription, bool bPropagateVertexColours, bool bApplyComponentTransform = false);`
- L39 _public prototype_ `static void RetrieveMesh(const UStaticMesh* StaticMesh, int32 LODIndex, FMeshDescription& OutMeshDescription);`
- L42 _public prototype_ `static bool CheckWrappingUVs(const TArray<FVector2D>& UVs);` — Checks whether or not the texture coordinates are outside of 0-1 UV ranges
- L43 _public prototype_ `static bool CheckWrappingUVs(const FMeshDescription& MeshDescription, int32 UVChannelIndex);`
- L46 _public prototype_ `static void CullTrianglesFromVolumesAndUnderLandscapes(const UWorld* World, const FBoxSphereBounds& Bounds, FMeshDescription& InOutRawMesh);` — Culls away triangles which are inside culling volumes or completely underneath the landscape
- L49 _public prototype_ `static void PropagateSplineDeformationToPhysicsGeometry(USplineMeshComponent* SplineMeshComponent, FKAggregateGeom& InOutPhysicsGeometry);` — Propagates deformation along spline to physics geometry data
- L52 _public prototype_ `static void RetrieveCullingLandscapeAndVolumes(UWorld* InWorld, const FBoxSphereBounds& EstimatedMeshProxyBounds, const TEnumAsByte<ELandscapeCullingPrecision::Type> PrecisionType, TArray<FMeshDescription*>& OutCullingMeshes);` — Retrieves all culling landscapes and volumes as FMeshDescription structures. Note the caller is responsible for deleting the heap data managed by OutCullingMeshes
- L55 _public prototype_ `static void TransformPhysicsGeometry(const FTransform& InTransform, const bool bBakeConvexTransform, struct FKAggregateGeom& AggGeom);` — Transforms physics geometry data using InTransform
- L58 _public prototype_ `static void ExtractPhysicsGeometry(UBodySetup* InBodySetup, const FTransform& ComponentToWorld, const bool bBakeConvexTransform, struct FKAggregateGeom& OutAggGeom);` — Extract physics geometry data from a body setup
- L61 _public prototype_ `static FVector2D GetValidUV(const FVector2D& UV);` — Ensure that UV is in valid 0-1 UV ranges
- L64 _public prototype_ `static void CalculateTextureCoordinateBoundsForMesh(const FMeshDescription& InMeshDescription, TArray<FBox2D>& OutBounds);` — Calculates UV coordinates bounds for the given MeshDescription
- L67 _public prototype_ `static bool PropagatePaintedColorsToMesh(const UStaticMeshComponent* StaticMeshComponent, int32 LODIndex, FMeshDescription& InOutMeshDescription);` — Propagates vertex painted colors from the StaticMeshComponent instance to MeshDescription
- L70 _public prototype_ `static bool IsLandscapeHit(const FVector& RayOrigin, const FVector& RayEndPoint, const UWorld* World, const TArray<ALandscapeProxy*>& LandscapeProxies, FVector& OutHitLocation);` — Checks whether or not the landscape proxy is hit given a ray start and end
- L73 _public prototype_ `static void MergeImpostersToMesh(TArray<const UStaticMeshComponent*> ImposterComponents, FMeshDescription& InOutMeshDescription, const FVector& InPivot, int32 BaseMaterialIndex, TArray<UMaterialInterface*>& OutImposterMaterials);` — Merges imposter meshes into the given MeshDescription.
- L76 _public prototype_ `static void FixupNonStandaloneMaterialReferences(UStaticMesh* InStaticMesh);` — Ensure a generated HLOD mesh is not referencing non standalone materials.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHMERGEUTILITIES_API`

### `Source/Developer/MeshMergeUtilities/Private/MeshMergeUtilities.h` (Private)


#### class `FMeshMergeUtilities`  
`class FMeshMergeUtilities : public IMeshMergeUtilities`  
_L19-84_
- inherits: `IMeshMergeUtilities`
- desc: Mesh Merge Utilities
- L23 _public prototype_ `FMeshMergeUtilities();`
- L25 _public prototype_ `virtual void BakeMaterialsForComponent(TArray<TWeakObjectPtr<UObject>>& OptionObjects, IMaterialBakingAdapter* Adapter) const override;`
- L26 _public prototype_ `virtual void BakeMaterialsForComponent(UStaticMeshComponent* StaticMeshComponent) const override;`
- L27 _public prototype_ `virtual void BakeMaterialsForComponent(USkeletalMeshComponent* SkeletalMeshComponent) const override;`
- L28 _public prototype_ `virtual void BakeMaterialsForMesh(UStaticMesh* Mesh) const override;`
- L29 _public prototype_ `virtual void MergeComponentsToStaticMesh(const TArray<UPrimitiveComponent*>& ComponentsToMerge, UWorld* World, const FMeshMergingSettings& InSettings, UMaterialInterface* InBaseMaterial, UPackage* InOuter, const FString& InBasePackageName, TArray<UObject*>& OutAssetsToSync, FVector& OutMergedActorLocation, const float ScreenSize, bool bSilent ) const;`
- L30 _public prototype_ `virtual void MergeComponentsToInstances(const TArray<UPrimitiveComponent*>& ComponentsToMerge, UWorld* World, ULevel* Level, const FMeshInstancingSettings& InSettings, bool bActuallyMerge = true, bool bReplaceSourceActors = false, FText* OutResultsText = nullptr) const override;`
- L32 _public prototype_ `virtual void CreateProxyMesh(const TArray<AActor*>& InActors, const struct FMeshProxySettings& InMeshProxySettings, UMaterialInterface* InBaseMaterial, UPackage* InOuter, const FString& InProxyBasePackageName, const FGuid InGuid, const FCreateProxyDelegate& InProxyCreatedDelegate, const bool bAllowAsync = false, const float ScreenSize = 1.0f) const override;`
- L33 _public prototype_ `virtual void CreateProxyMesh(const TArray<UStaticMeshComponent*>& InStaticMeshComps, const struct FMeshProxySettings& InMeshProxySettings, UMaterialInterface* InBaseMaterial, UPackage* InOuter, const FString& InProxyBasePackageName, const FGuid InGuid, const FCreateProxyDelegate& InProxyCreatedDelegate, const bool bAllowAsync = false, const float ScreenSize = 1.0f) const override;`
- L34 _public prototype_ `virtual void CreateProxyMesh(const TArray<AActor*>& InActors, const struct FMeshProxySettings& InMeshProxySettings, UPackage* InOuter, const FString& InProxyBasePackageName, const FGuid InGuid, const FCreateProxyDelegate& InProxyCreatedDelegate, const bool bAllowAsync = false, const float ScreenSize = 1.0f) const override;`
- L35 _public prototype_ `virtual void CreateProxyMesh(const TArray<UStaticMeshComponent*>& InStaticMeshComps, const struct FMeshProxySettings& InMeshProxySettings, UPackage* InOuter, const FString& InProxyBasePackageName, const FGuid InGuid, const FCreateProxyDelegate& InProxyCreatedDelegate, const bool bAllowAsync = false, const float ScreenSize = 1.0f) const override;`
- L37 _public prototype_ `virtual void RetrieveMeshDescription(const UStaticMeshComponent* InStaticMeshComponent, int32 LODIndex, FMeshDescription& InOutMeshDescription, bool bPropagateVertexColours) const override;`
- L38 _public prototype_ `virtual void RetrieveMeshDescription(const USkeletalMeshComponent* InSkeletalMeshComponent, int32 LODIndex, FMeshDescription& InOutMeshDescription, bool bPropagateVertexColours) const override;`
- L39 _public prototype_ `virtual void RetrieveMeshDescription(const UStaticMesh* InStaticMesh, int32 LODIndex, FMeshDescription& InOutMeshDescription) const override;`
- L41 _public prototype_ `virtual void RetrievePhysicsData(const TArray<UPrimitiveComponent*>& InComponents, TArray<FKAggregateGeom>& InOutPhysicsGeometry, UBodySetup*& OutBodySetupSource) const override;`
- L43 _public prototype_ `virtual void RegisterExtension(IMeshMergeExtension* InExtension) override;`
- L44 _public prototype_ `virtual void UnregisterExtension(IMeshMergeExtension* InExtension) override;`
- L47 _protected prototype_ `UMaterialInterface* CreateProxyMaterial(const FString &InBasePackageName, FString MergedAssetPackageName, UMaterialInterface* InBaseMaterial, UPackage* InOuter, const FMeshMergingSettings &InSettings, const FFlattenMaterial& OutMaterial, TArray<UObject *>& OutAssetsToSync, FMaterialUpdateContext* InMaterialUpdateContext = nullptr) const;` — Creates a proxy material instance at givne path and name
- L49 _protected prototype_ `void MergeFlattenedMaterials(TArray<struct FFlattenMaterial>& InMaterialList, int32 InGutter, FFlattenMaterial& OutMergedMaterial, TArray<FUVOffsetScalePair>& OutUVTransforms) const;` — Merges flattened material into atlas textures
- L51 _protected prototype_ `void FlattenBinnedMaterials(TArray<struct FFlattenMaterial>& InMaterialList, const TArray<FBox2D>& InMaterialBoxes, int32 InGutter, bool bCopyOnlyMaskedPixels, FFlattenMaterial& OutMergedMaterial, TArray<FUVOffsetScalePair>& OutUVTransforms) const;` — Merges flattened material into binned textures
- L53 _protected prototype_ `void CreateMergedMaterial(FMeshMergeDataTracker& InDataTracker, const FMeshMergingSettings& InSettings, const TArray<UStaticMeshComponent*>& InStaticMeshComponentsToMerge, TArray<FStaticMeshComponentAdapter>& InAdapters, const TArray<UMaterialInterface*>& InUniqueMaterials, const TMap<UMaterialInterface*, UMaterialInterface*>& InCollapsedMaterialMap, TMultiMap<FMeshLODKey, MaterialRemapPair>& InOutputMaterialsMap, bool bInMergeAllLODs, bool bInMergeMaterialData, const FVector& InMergedAssetPivot, FFlattenMaterial& OutFlattenMaterial) const;`
- L56 _protected prototype_ `void CreateMergedRawMeshes(FMeshMergeDataTracker& InDataTracker, const FMeshMergingSettings& InSettings, const TArray<UStaticMeshComponent*>& InStaticMeshComponentsToMerge, const TArray<UMaterialInterface*>& InUniqueMaterials, const TMap<UMaterialInterface*, UMaterialInterface*>& InCollapsedMaterialMap, const TMultiMap<FMeshLODKey, MaterialRemapPair>& InOutputMaterialsMap, bool bInMergeAllLODs, bool bInMergeMaterialData, const FVector& InMergedAssetPivot, TArray<FMeshDescription>& OutMergedRawMeshes) const;` — Helper function to create the final merged raw meshes
- L59 _protected prototype_ `float FlattenEmissivescale(TArray<struct FFlattenMaterial>& InMaterialList) const;` — Flattens out emissive scale across all flatten material instances
- L61 _protected prototype_ `UMaterialOptions* PopulateMaterialOptions(const FMaterialProxySettings& MaterialSettings) const;` — Populates material options object from legacy material proxy settings
- L63 _protected prototype_ `void PopulatePropertyEntry(const FMaterialProxySettings& MaterialSettings, EMaterialProperty MaterialProperty, struct FPropertyEntry& InOutPropertyEntry) const;` — Populates a single property entry with correct material baking settings
- L65 _protected prototype_ `void CopyTextureRect(const FColor* Src, const FIntPoint& SrcSize, FColor* Dst, const FIntPoint& DstSize, const FIntPoint& DstPos, bool bCopyOnlyMaskedPixels = false) const;` — Copies part (box) from a texture to another texture
- L67 _protected prototype_ `void SetTextureRect(const FColor& ColorValue, const FIntPoint& SrcSize, FColor* Dst, const FIntPoint& DstSize, const FIntPoint& DstPos) const;` — Sets a part (box) on a texture to ColorValue
- L69 _protected prototype_ `FIntPoint ConditionalImageResize(const FIntPoint& SrcSize, const FIntPoint& DesiredSize, TArray<FColor>& InOutImage, bool bLinearSpace) const;` — Conditionally resizes the source data into OutImage
- L71 _protected prototype_ `void ConvertOutputToFlatMaterials(const TArray<FBakeOutput>& BakeOutputs, const TArray<FMaterialData>& MaterialData, TArray<FFlattenMaterial> &FlattenedMaterials) const;` — Converts bake output structure data to flatten material format
- L75 _protected prototype_ `void TransferOutputToFlatMaterials(const TArray<FMaterialData>& InMaterialData, TArray<FBakeOutput>& InOutBakeOutputs, TArray<FFlattenMaterial> &OutFlattenedMaterials) const;` — Transfer bake output structure data to flatten material format. @warning This is a destructive operation for InOutBakeOutputs
- L78 _protected prototype_ `EFlattenMaterialProperties ToFlattenProperty(EMaterialProperty MaterialProperty) const;` — Converts material property enum value to flatten material property
- L80 _private member_ `FProxyGenerationProcessor* Processor;`
- L81 _private member_ `FDelegateHandle ModuleLoadedDelegateHandle;`
- L83 _private member_ `TArray<IMeshMergeExtension*> MeshMergeExtensions;`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TPair<uint32, uint32> MaterialRemapPair;`

### `Source/Developer/MeshMergeUtilities/Private/ProxyGenerationProcessor.h` (Private)


#### class `FProxyGenerationProcessor`  
`class FProxyGenerationProcessor : FTSTickerObjectBase`  
_L15-60_
- inherits: `FTSTickerObjectBase`
- L18 _public prototype_ `FProxyGenerationProcessor(const FMeshMergeUtilities* InOwner);`
- L19 _public prototype_ `~FProxyGenerationProcessor();`
- L21 _public prototype_ `void AddProxyJob(FGuid InJobGuid, FMergeCompleteData* InCompleteData);`
- L22 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L23 _public prototype_ `void ProxyGenerationComplete(FMeshDescription& OutProxyMesh, struct FFlattenMaterial& OutMaterial, const FGuid OutJobGUID);`
- L26 _public prototype_ `void ProxyGenerationFailed(const FGuid OutJobGUID, const FString& ErrorMessage);` — @third party BEGIN SIMPLYGON
- L31 _protected prototype_ `void OnMapChange(uint32 MapFlags);` — Called when the map has changed
- L34 _protected prototype_ `void OnNewCurrentLevel();` — Called when the current level has changed
- L37 _protected prototype_ `void ClearProcessingData();` — Clears the processing data array/map
- L48 _protected prototype_ `void ProcessJob(const FGuid& JobGuid, FProxyGenerationData* Data);`
- L49 _protected prototype_ `void OnModuleConfigurationCompleted();`
- L53 _protected member_ `TMap<FGuid, FMergeCompleteData*> ProxyMeshJobs;` — Holds Proxy mesh job data together with the job Guid
- L55 _protected member_ `TMap<FGuid, FProxyGenerationData*> ToProcessJobDataMap;` — Holds Proxy generation data together with the job Guid
- L57 _protected member_ `FCriticalSection StateLock;` — Critical section to keep ProxyMeshJobs/ToProcessJobDataMap access thread-safe
- L59 _protected member_ `const FMeshMergeUtilities* Owner;`

#### struct `FProxyGenerationProcessor::FProxyGenerationData`  
`struct FProxyGenerationData`  
_L41-46_
- desc: Structure storing the data required during processing
- L43 _public member_ `FMeshDescription RawMesh;`
- L44 _public member_ `FFlattenMaterial Material;`
- L45 _public member_ `FMergeCompleteData* MergeData;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshMerging, Verbose, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshMerging, Verbose, All);`

### `Source/Developer/MeshMergeUtilities/Public/IMaterialBakingAdapter.h` (Public)


#### class `IMaterialBakingAdapter`  
`class IMaterialBakingAdapter`  
_L13-54_
- L17 _public prototype_ `virtual int32 GetNumberOfLODs() const = 0;` — Returns the number of LODs for the data the adapter represents
- L19 _public prototype_ `virtual void RetrieveRawMeshData(int32 LODIndex, FMeshDescription& InOutRawMesh, bool bPropagateMeshData) const = 0;` — Retrieves model data in FMeshDescription form
- L21 _public prototype_ `virtual void RetrieveMeshSections(int32 LODIndex, TArray<FSectionInfo>& InOutSectionInfo) const = 0;` — Retrieves all mesh sections from underlying data
- L23 _public prototype_ `virtual int32 LightmapUVIndex() const = 0;` — Returns lightmap UV index used by mesh data
- L26 _public prototype_ `virtual void SetMaterial(int32 MaterialIndex, UMaterialInterface* Material) = 0;` — Sets material index to specified material value
- L28 _public prototype_ `virtual int32 GetMaterialIndex(int32 LODIndex, int32 SectionIndex) const = 0;` — Returns the material index for the given lod and section index
- L30 _public prototype_ `virtual void RemapMaterialIndex(int32 LODIndex, int32 SectionIndex, int32 NewMaterialIndex) = 0;` — Remaps the material index for the given lod and section index to the specified new one
- L32 _public prototype_ `virtual FName GetMaterialSlotName(int32 MaterialIndex) const = 0;` — Returns the material slot name for the given index
- L34 _public prototype_ `virtual FName GetImportedMaterialSlotName(int32 MaterialIndex) const = 0;` — Returns the importer material slot name for the given index
- L36 _public prototype_ `virtual int32 AddMaterial(UMaterialInterface* Material) = 0;` — Adds a new material to the underlying asset/data
- L38 _public prototype_ `virtual int32 AddMaterial(UMaterialInterface* Material, const FName& SlotName, const FName& ImportedSlotName) = 0;` — Adds a new material to the underlying asset/data and specify the slot names
- L41 _public prototype_ `virtual void UpdateUVChannelData() = 0;` — Update UV channel data on object the adapter represents
- L44 _public prototype_ `virtual void ApplySettings(int32 LODIndex, FMeshData& InOutMeshData) const = 0;` — Ability to apply custom settings to the FMeshData structure
- L47 _public prototype_ `virtual FBoxSphereBounds GetBounds() const = 0;` — Returns bounds of underlying data
- L49 _public prototype_ `virtual UPackage* GetOuter() const = 0;` — Returns outer package to use when creating new assets
- L51 _public prototype_ `virtual FString GetBaseName() const = 0;` — Returns base name to use for newly created assets
- L53 _public prototype_ `virtual bool IsAsset() const = 0;` — Returns whether or not the underlying data is an UAsset

### `Source/Developer/MeshMergeUtilities/Public/IMeshMergeExtension.h` (Public)


#### class `IMeshMergeExtension`  
`class IMeshMergeExtension`  
_L11-17_
- L14 _public prototype_ `virtual void OnCreatedMergedRawMeshes(const TArray<UStaticMeshComponent*>& MergedComponents, const class FMeshMergeDataTracker& DataTracker, TArray<FMeshDescription>& MergedMeshLODs) = 0;`
- L16 _public prototype_ `virtual void OnCreatedProxyMaterial(const TArray<UStaticMeshComponent*>& MergedComponents, UMaterialInterface* ProxyMaterial) = 0;`

### `Source/Developer/MeshMergeUtilities/Public/IMeshMergeUtilities.h` (Public)


#### class `IMeshMergeUtilities`  
`class IMeshMergeUtilities`  
_L38-146_
- L41 _public prototype_ `virtual ~IMeshMergeUtilities() = default;`
- L44 _public prototype_ `virtual void BakeMaterialsForComponent(TArray<TWeakObjectPtr<UObject>>& OptionObjects, IMaterialBakingAdapter* Adapter) const = 0;` — Bakes out (in place) materials for given adapter
- L46 _public prototype_ `virtual void BakeMaterialsForComponent(UStaticMeshComponent* StaticMeshComponent) const = 0;` — Bakes out (in place) materials for given static mesh component
- L48 _public prototype_ `virtual void BakeMaterialsForComponent(USkeletalMeshComponent* SkeletalMeshComponent) const = 0;` — Bakes out (in place) materials for given skeletal mesh component
- L50 _public prototype_ `virtual void BakeMaterialsForMesh(UStaticMesh* Mesh) const = 0;` — Bakes out (in place) materials for given static mesh asset
- L67 _public prototype_ `virtual void MergeComponentsToStaticMesh(const TArray<UPrimitiveComponent*>& ComponentsToMerge, UWorld* World, const FMeshMergingSettings& InSettings, UMaterialInterface* InBaseMaterial, UPackage* InOuter, const FString& InBasePackageName, TArray<UObject*>& OutAssetsToSync, FVector& OutMergedActorLocation, const float ScreenSize, bool bSilent ) const = 0;` — Merges components into a single Static Mesh (with possible baked out atlas-material) @param ComponentsToMerge - Components to merge @param World - World in which the component reside @param InSettings	- Settings to use @param InBaseMaterial - Base Material used for final proxy material (optional, can be null) @param InOuter - Outer if required @param InBasePackageName - Destination package name for a generated assets. Used if Outer is null. @param OutAssetsToSync Merged mesh assets @param OutMergedActorLocation	World position of merged mesh @param Screensize - final targeted screensize of mesh @param bSilent Non-verbose flag @return void
- L80 _public prototype_ `virtual void MergeComponentsToInstances(const TArray<UPrimitiveComponent*>& ComponentsToMerge, UWorld* World, ULevel* Level, const FMeshInstancingSettings& InSettings, bool bActuallyMerge = true, bool bReplaceSourceActors = false, FText* OutResultsText = nullptr) const = 0;` — Merges static mesh components into a single actor with multiple instanced static mesh components @param ComponentsToMerge - Components to merge @param World - World in which the components reside @level Level - The level in which to create the new merged actor @param InSettings	- Settings to use @param bActuallyMerge Whether to actually perform the merge (could just be fetching predicted results) @param OutResultsText (optional) Results of the merge @return void
- L91 _public prototype_ `virtual void CreateProxyMesh(const TArray<AActor*>& InActors, const struct FMeshProxySettings& InMeshProxySettings, UPackage* InOuter, const FString& InProxyBasePackageName, const FGuid InGuid, const FCreateProxyDelegate& InProxyCreatedDelegate, const bool bAllowAsync = false, const float ScreenSize = 1.0f) const = 0;` — Merges list of actors into single proxy mesh @param	Actors					List of Actors to merge @param	InProxySettings			Merge settings @param	InOuter					Package for a generated assets, if NULL new packages will be created for each asset @param	ProxyBasePackageName	Will be used for naming generated assets, in case InOuter is not specified ProxyBasePackageName will be used as long package name for creating new packages @param	OutAssetsToSync			Result assets - mesh, material
- L103 _public prototype_ `virtual void CreateProxyMesh(const TArray<AActor*>& InActors, const struct FMeshProxySettings& InMeshProxySettings, UMaterialInterface* InBaseMaterial, UPackage* InOuter, const FString& InProxyBasePackageName, const FGuid InGuid, const FCreateProxyDelegate& InProxyCreatedDelegate, const bool bAllowAsync = false, const float ScreenSize = 1.0f) const = 0;` — Merges list of actors into single proxy mesh @param	Actors					List of Actors to merge @param	InProxySettings			Merge settings @param	InBaseMaterial			Base Material used for final proxy material @param	InOuter					Package for a generated assets, if NULL new packages will be created for each asset @param	ProxyBasePackageName	Will be used for naming generated assets, in case InOuter is not specified ProxyBasePackageName will be used as long package name for creating new packages @param	OutAssetsToSync			Result assets - mesh, material
- L114 _public prototype_ `virtual void CreateProxyMesh(const TArray<UStaticMeshComponent*>& InComponents, const struct FMeshProxySettings& InMeshProxySettings, UPackage* InOuter, const FString& InProxyBasePackageName, const FGuid InGuid, const FCreateProxyDelegate& InProxyCreatedDelegate, const bool bAllowAsync = false, const float ScreenSize = 1.0f) const = 0;` — Merges list of static meshes into single proxy mesh @param	InComponents		    List of meshes to merge @param	InProxySettings			Merge settings @param	InOuter					Package for a generated assets, if NULL new packages will be created for each asset @param	ProxyBasePackageName	Will be used for naming generated assets, in case InOuter is not specified ProxyBasePackageName will be used as long package name for creating new packages @param	OutAssetsToSync			Result assets - mesh, material
- L126 _public prototype_ `virtual void CreateProxyMesh(const TArray<UStaticMeshComponent*>& InComponents, const struct FMeshProxySettings& InMeshProxySettings, UMaterialInterface* InBaseMaterial, UPackage* InOuter, const FString& InProxyBasePackageName, const FGuid InGuid, const FCreateProxyDelegate& InProxyCreatedDelegate, const bool bAllowAsync = false, const float ScreenSize = 1.0f) const = 0;` — Merges list of static meshes into single proxy mesh @param	InComponents		    List of meshes to merge @param	InProxySettings			Merge settings @param	InBaseMaterial			Base Material used for final proxy material @param	InOuter					Package for a generated assets, if NULL new packages will be created for each asset @param	ProxyBasePackageName	Will be used for naming generated assets, in case InOuter is not specified ProxyBasePackageName will be used as long package name for creating new packages @param	OutAssetsToSync			Result assets - mesh, material
- L129 _public prototype_ `virtual void RetrieveMeshDescription(const UStaticMeshComponent* InStaticMeshComponent, int32 LODIndex, FMeshDescription& InOutMeshDescription, bool bPropagateVertexColours) const = 0;` — Extract mesh data in FMeshDescription form from the provided static mesh component
- L131 _public prototype_ `virtual void RetrieveMeshDescription(const USkeletalMeshComponent* InSkeletalMeshComponent, int32 LODIndex, FMeshDescription& InOutMeshDescription, bool bPropagateVertexColours) const = 0;` — Extract mesh data in FMeshDescription form from the provided skeletal mesh component
- L133 _public prototype_ `virtual void RetrieveMeshDescription(const UStaticMesh* InStaticMesh, int32 LODIndex, FMeshDescription& InOutMeshDescription) const = 0;` — Extract mesh data in FMeshDescription form from the provided static mesh
- L142 _public prototype_ `virtual void RetrievePhysicsData(const TArray<UPrimitiveComponent*>& InComponents, TArray<FKAggregateGeom>& InOutPhysicsGeometry, UBodySetup*& OutBodySetupSource) const = 0;` — Extract physics geometry and body setup from set of primitive components. @param InComponents			List of components to extract the physics geometry from. @param InOutPhysicsGeometry	The list of extracted physics geometry. @param OutBodySetupSource	The BodySetup extracted.
- L144 _public prototype_ `virtual void RegisterExtension(IMeshMergeExtension* InExtension) = 0;`
- L145 _public prototype_ `virtual void UnregisterExtension(IMeshMergeExtension* InExtension) = 0;`

#### Free symbols / members of external scopes

- L36 _typedef_ `typedef TPair<FVector2D, FVector2D> FUVOffsetScalePair;` — Typedef pair of FVector2Ds, key == uv position offset and value == uv scaling factor

### `Source/Developer/MeshMergeUtilities/Public/MeshMergeData.h` (Public)


#### struct `FMeshMergeData`  
`struct FMeshMergeData`  
_L16-45_
- desc: Structure holding intermediate mesh merging data that is used throughout the mesh merging and proxy creation processes
- L18 _public function_ `FMeshMergeData() : RawMesh(nullptr) , SourceStaticMesh(nullptr) , bIsClippingMesh(false)`
- L24 _public function_ `void ReleaseData()`
- L34 _public member_ `FMeshDescription* RawMesh;` — Raw mesh data from the source static mesh
- L37 _public member_ `TArray<FBox2D> TexCoordBounds;` — Contains the original texture bounds, if the material requires baking down per-vertex data
- L39 _public member_ `TArray<FVector2D> NewUVs;` — Will contain non-overlapping texture coordinates, if the material requires baking down per-vertex data
- L41 _public member_ `class UStaticMesh* SourceStaticMesh;` — Pointer to the source static mesh instance
- L43 _public member_ `bool bIsClippingMesh;` — If set, the raw mesh should be used as clipping geometry
- L44 _public member_ `FString DebugJobName;`

#### struct `FInstancedMeshMergeData`  
`struct FInstancedMeshMergeData : public FMeshMergeData`  
_L47-50_
- inherits: `FMeshMergeData`
- L49 _public member_ `TArray<FTransform> InstanceTransforms;`

#### struct `FRawMeshExt`  
`struct FRawMeshExt`  
_L53-79_
- desc: Structure for encapsulating per LOD mesh merging data
- L55 _public function_ `FRawMeshExt() : SourceStaticMesh(nullptr)`
- L61 _public member_ `FMeshMergeData MeshLODData[MAX_STATIC_MESH_LODS];`
- L62 _public member_ `FKAggregateGeom AggGeom;`
- L65 _public member_ `class UStaticMesh* SourceStaticMesh;` — Pointer to the source static mesh instance
- L67 _public member_ `class UStaticMeshComponent* Component;`
- L70 _public member_ `int32 ExportLODIndex;` — Specific LOD index that is being exported
- L72 _public member_ `FLightMapRef LightMap;`
- L73 _public member_ `FShadowMapRef ShadowMap;`
- L76 _public member_ `bool bShouldExportLOD[MAX_STATIC_MESH_LODS];` — Whether or not a specific LOD should be exported
- L78 _public member_ `int32 MaxLODExport;` — Max LOD index that is exported

### `Source/Developer/MeshMergeUtilities/Public/MeshMergeDataTracker.h` (Public)


#### struct `FMeshLODKey`  
`struct FMeshLODKey`  
_L19-75_
- desc: Structure representing a mesh and lod index
- L22 _public function_ `FMeshLODKey(int32 MeshIndex, int32 LODIndex, UStaticMesh* InMesh = nullptr)`
- L29 _public function_ `explicit FMeshLODKey(uint32 InCombinedKey)`
- L36 _public function_ `UStaticMesh* GetMesh() const`
- L41 _public function_ `int32 GetMeshIndex() const`
- L46 _public function_ `int32 GetLODIndex() const`
- L51 _public function_ `uint32 GetVertexColorHash() const`
- L56 _public function_ `void SetVertexColorHash(uint32 InVertexColorHash)`
- L61 _public function_ `inline bool operator==(const FMeshLODKey& Other) const`
- L72 _protected member_ `uint32 CombinedKey;`
- L73 _protected member_ `UStaticMesh* Mesh;`
- L74 _protected member_ `uint32 VertexColorHash;`

#### struct `FMaterialKey`  
`struct FMaterialKey`  
_L78-101_
- desc: This helps identify materials that can be collapsed because of equivalence
- L80 _public function_ `FMaterialKey(const UMaterialInterface* InMaterial) : Material(InMaterial)`
- L85 _public function_ `inline bool operator==(const FMaterialKey& Other) const`
- L100 _public member_ `const UMaterialInterface* Material;`

#### class `FMeshMergeDataTracker`  
`class FMeshMergeDataTracker`  
_L110-224_
- desc: Used to keep track of in-flight data while meshes are merged and their corresponding materials baked down
- L113 _public prototype_ `FMeshMergeDataTracker();`
- L116 _public prototype_ `void ProcessRawMeshes();` — Looks at all available raw mesh data and processes it to populate some flags
- L119 _public prototype_ `void AddSectionRemapping(int32 MeshIndex, int32 LODIndex, int32 OriginalIndex, int32 UniqueIndex);` — Adding a mapping between the index for an original mesh section index and the mesh section it will be indexed to in the final mesh
- L121 _public prototype_ `void GetMeshLODsMappedToUniqueSection(int32 UniqueIndex, TArray<FMeshLODKey>& InOutMeshLODs);` — Retrieves the MeshLOD keys from which the original sections are mapped to the unique section index
- L123 _public prototype_ `void GetMappingsForMeshLOD(FMeshLODKey Key, TArray<SectionRemapPair>& InOutMappings);` — Retrieves all section mappings for the MeshLOD key
- L126 _public prototype_ `FMeshDescription& AddAndRetrieveRawMesh(int32 MeshIndex, int32 LODIndex, UStaticMesh* InMesh);` — Adds or retrieves raw mesh data for the mesh and LOD index
- L128 _public prototype_ `void RemoveRawMesh(int32 MeshIndex, int32 LODIndex);` — Removes raw mesh entry for the given mesh and LOD index
- L130 _public prototype_ `FMeshDescription* GetRawMeshPtr(int32 MeshIndex, int32 LODIndex);` — Retrieves Raw Mesh ptr for the given mesh and LOD index
- L132 _public prototype_ `FMeshDescription* GetRawMeshPtr(FMeshLODKey Key);` — Retrieves Raw Mesh ptr for the given MeshLOD key
- L134 _public prototype_ `FMeshDescription* FindRawMeshAndLODIndex(int32 MeshIndex, int32& OutLODIndex);` — Tries to retrieve a FMeshDescription and returns the LOD index it found an entry for
- L136 _public prototype_ `FMeshDescription* TryFindRawMeshForLOD(int32 MeshIndex, int32& InOutDesiredLODIndex);` — Tries to retrieve a FMeshDescription for the given mesh and LOD index, if it can't it will try to find an entry for each LOD levle below InOutDesiredLODIndex
- L139 _public prototype_ `TConstRawMeshIterator GetConstRawMeshIterator() const;` — Returns a const key/value iterator for the FMeshDescription entries
- L141 _public prototype_ `TRawMeshIterator GetRawMeshIterator();` — Returns a non-const key/value iterator for the FMeshDescription entries
- L144 _public prototype_ `void AddLightmapChannelRecord(int32 MeshIndex, int32 LODIndex, int32 LightmapChannelIndex);` — Adds a record of what channel lightmap data is stored at
- L147 _public prototype_ `int32 AddSection(const FSectionInfo& SectionInfo);` — Adds (unique) section to stored data
- L149 _public prototype_ `int32 NumberOfUniqueSections() const;` — Returns the number of unique sections
- L151 _public prototype_ `UMaterialInterface* GetMaterialForSectionIndex(int32 SectionIndex);` — Returns the material used by the unique section
- L153 _public prototype_ `const FSectionInfo& GetSection(int32 SectionIndex) const;` — Returns the unique section instance
- L155 _public prototype_ `void AddBakedMaterialSection(const FSectionInfo& SectionInfo);` — Clears out unique section to be replaced with the baked material one
- L158 _public prototype_ `void AddMaterialSlotName(UMaterialInterface *MaterialInterface, FName MaterialSlotName);` — Add a material slot name for a unique material instance.
- L160 _public prototype_ `FName GetMaterialSlotName(UMaterialInterface *MaterialInterface) const;` — Get the material slot name from a unique material instance.
- L163 _public prototype_ `void AddLODIndex(int32 LODIndex);` — Adds a LOD index which will be part of the final merged mesh
- L165 _public prototype_ `int32 GetNumLODsForMergedMesh() const;` — Retrieves number of LODs part of the final merged mesh
- L167 _public prototype_ `TConstLODIndexIterator GetLODIndexIterator() const;` — Iterates over LOD indices for mesh
- L170 _public prototype_ `void AddLightMapPixels(int32 Pixels);` — Add number of lightmap pixels used for one of the Meshes
- L172 _public prototype_ `int32 GetLightMapDimension() const;` — Returns the texture dimension required to distribute all of the lightmap pixels
- L175 _public prototype_ `bool DoesLODContainVertexColors(int32 LODIndex) const;` — Returns whether or not any raw mesh entry contains vertex colors for the specified LOD index
- L177 _public prototype_ `bool DoesAnyLODContainVertexColors() const;` — Returns whether or not any raw mesh entry contains vertex colors for any LOD index
- L179 _public prototype_ `bool DoesUVChannelContainData(int32 UVChannel, int32 LODIndex) const;` — Returns whether or not any raw mesh entry contains texture coordinates for the specified UV channel and LOD index
- L181 _public prototype_ `bool DoesUVChannelContainData(int32 UVChannel) const;` — Returns whether or not any raw mesh entry contains texture coordinates for the specified UV channel and any LOD index
- L183 _public prototype_ `bool DoesMeshLODRequireUniqueUVs(FMeshLODKey Key);` — Returns whether or not the raw mesh entry for the given MeshLOD key requires unique UVs for baking out its material(s)
- L185 _public prototype_ `int32 GetAvailableLightMapUVChannel() const;` — Returns the first available UV channel across all raw mesh entries, which will be a good fit for the lightmap UV index in the final mesh
- L187 _public prototype_ `void AddComponentToWedgeMapping(int32 MeshIndex, int32 LODIndex, uint32 WedgeIndex);`
- L188 _public prototype_ `uint32 GetComponentToWedgeMappng(int32 MeshIndex, int32 LODIndex) const;`
- L190 _public prototype_ `double GetTextureSizeFromTargetTexelDensity(float InTargetTexelDensity) const;`
- L194 _protected member_ `TMap<FMeshLODKey, FMeshDescription> RawMeshLODs;` — Mesh / LOD index, RawMesh
- L197 _protected member_ `TMap<FMeshLODKey, int32> LightmapChannelLODs;` — Mesh / LOD index, lightmap channel
- L200 _protected member_ `TArray<FMeshLODKey> RequiresUniqueUVs;` — Whether a key requires unique UVs
- L203 _protected member_ `TMap<UMaterialInterface *, FName> MaterialInterfaceToMaterialSlotName;` — Use this map to recycle the material slot name
- L206 _protected member_ `bool bWithVertexColors[MAX_STATIC_MESH_LODS];` — Flags for UV and vertex color usage
- L207 _protected member_ `bool bOcuppiedUVChannels[MAX_STATIC_MESH_LODS][MAX_MESH_TEXTURE_COORDS_MD];`
- L209 _protected member_ `int32 AvailableLightMapUVChannel;` — First available UV channel across all RawMesh entries
- L210 _protected member_ `int32 SummedLightMapPixels;`
- L213 _protected member_ `TMultiMap<FMeshLODKey, SectionRemapPair> UniqueSectionIndexPerLOD;` — Remapping pairs for each mesh and LOD index combination
- L215 _protected member_ `TMultiMap<uint32, FMeshLODKey> UniqueSectionToMeshLOD;` — Maps from each unique section index to all the RawMesh entries which contain an original section that's mapped to it
- L218 _protected member_ `TArray<int32> LODIndices;` — All LOD indices which should be populated in the final merged mesh
- L221 _protected member_ `TArray<FSectionInfo> UniqueSections;` — Unique set of sections in mesh
- L223 _protected member_ `TMap<FMeshLODKey, uint32> ComponentToWedgeOffsets;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHMERGEUTILITIES_API`
- L12 _typedef_ `typedef TPair<uint32, uint32> MeshLODPair;`
- L13 _typedef_ `typedef TPair<uint32, uint32> SectionRemapPair;`
- L14 _typedef_ `typedef TPair<uint32, uint32> MaterialRemapPair;`
- L66 _function_ `inline friend uint32 GetTypeHash(const FMeshLODKey& Item)`
- L104 _typedef_ `typedef TMap<FMeshLODKey, FMeshDescription>::TConstIterator TConstRawMeshIterator;` — Typedefs to allow for some nicer looking loops
- L105 _typedef_ `typedef TMap<FMeshLODKey, FMeshDescription>::TIterator TRawMeshIterator;`
- L107 _typedef_ `typedef TArray<int32>::TConstIterator TConstLODIndexIterator;`

### `Source/Developer/MeshMergeUtilities/Public/MeshMergeModule.h` (Public)


#### class `IMeshMergeModule`  
`class IMeshMergeModule : public IModuleInterface`  
_L9-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual const IMeshMergeUtilities& GetUtilities() const = 0;`
- L13 _public prototype_ `virtual IMeshMergeUtilities& GetUtilities() = 0;`

### `Source/Developer/MeshMergeUtilities/Public/SkeletalMeshAdapter.h` (Public)


#### class `FSkeletalMeshComponentAdapter`  
`class FSkeletalMeshComponentAdapter : public IMaterialBakingAdapter`  
_L11-40_
- inherits: `IMaterialBakingAdapter`
- desc: Adapter which takes a Skeletal Mesh asset to use for material baking (allows for changes to the asset itself)
- L14 _public prototype_ `FSkeletalMeshComponentAdapter(USkeletalMeshComponent* InSkeletalMeshComponent);`
- L17 _public prototype_ `virtual int32 GetNumberOfLODs() const override;` — Begin IMaterialBakingAdapter overrides
- L18 _public prototype_ `virtual void RetrieveRawMeshData(int32 LODIndex, FMeshDescription& InOutRawMesh, bool bPropogateMeshData) const override;`
- L19 _public prototype_ `virtual void RetrieveMeshSections(int32 LODIndex, TArray<FSectionInfo>& InOutSectionInfo) const override;`
- L20 _public prototype_ `virtual int32 GetMaterialIndex(int32 LODIndex, int32 SectionIndex) const override;`
- L21 _public function_ `virtual void ApplySettings(int32 LODIndex, FMeshData& InOutMeshData) const override`
- L22 _public prototype_ `virtual UPackage* GetOuter() const override;`
- L23 _public prototype_ `virtual FString GetBaseName() const override;`
- L24 _public prototype_ `virtual FName GetMaterialSlotName(int32 MaterialIndex) const override;`
- L25 _public prototype_ `virtual FName GetImportedMaterialSlotName(int32 MaterialIndex) const override;`
- L26 _public prototype_ `virtual void SetMaterial(int32 MaterialIndex, UMaterialInterface* Material) override;`
- L27 _public prototype_ `virtual void RemapMaterialIndex(int32 LODIndex, int32 SectionIndex, int32 NewMaterialIndex) override;`
- L28 _public prototype_ `virtual int32 AddMaterial(UMaterialInterface* Material) override;`
- L29 _public prototype_ `virtual int32 AddMaterial(UMaterialInterface* Material, const FName& SlotName, const FName& ImportedSlotName) override;`
- L30 _public prototype_ `virtual void UpdateUVChannelData() override;`
- L31 _public prototype_ `virtual bool IsAsset() const override;`
- L32 _public prototype_ `virtual int32 LightmapUVIndex() const override;`
- L33 _public prototype_ `virtual FBoxSphereBounds GetBounds() const override;`
- L37 _protected member_ `USkeletalMeshComponent * SkeletalMeshComponent;`
- L38 _protected member_ `USkeletalMesh* SkeletalMesh;`
- L39 _protected member_ `int32 NumLODs;`

### `Source/Developer/MeshMergeUtilities/Public/StaticMeshAdapter.h` (Public)


#### class `FStaticMeshAdapter`  
`class FStaticMeshAdapter : public IMaterialBakingAdapter`  
_L10-38_
- inherits: `IMaterialBakingAdapter`
- desc: Adapter which takes a Static Mesh asset to use for material baking (allows for changes to the asset itself)
- L13 _public prototype_ `FStaticMeshAdapter(UStaticMesh* InStaticMesh);`
- L16 _public prototype_ `virtual int32 GetNumberOfLODs() const override;` — Begin IMaterialBakingAdapter overrides
- L17 _public prototype_ `virtual void RetrieveRawMeshData(int32 LODIndex, FMeshDescription& InOutRawMesh, bool bPropogateMeshData) const override;`
- L18 _public prototype_ `virtual void RetrieveMeshSections(int32 LODIndex, TArray<FSectionInfo>& InOutSectionInfo) const override;`
- L19 _public prototype_ `virtual int32 GetMaterialIndex(int32 LODIndex, int32 SectionIndex) const override;`
- L20 _public prototype_ `virtual void ApplySettings(int32 LODIndex, FMeshData& InOutMeshData) const override;`
- L21 _public prototype_ `virtual UPackage* GetOuter() const override;`
- L22 _public prototype_ `virtual FString GetBaseName() const override;`
- L23 _public prototype_ `virtual FName GetMaterialSlotName(int32 MaterialIndex) const override;`
- L24 _public prototype_ `virtual FName GetImportedMaterialSlotName(int32 MaterialIndex) const override;`
- L25 _public prototype_ `virtual void SetMaterial(int32 MaterialIndex, UMaterialInterface* Material) override;`
- L26 _public prototype_ `virtual void RemapMaterialIndex(int32 LODIndex, int32 SectionIndex, int32 NewMaterialIndex) override;`
- L27 _public prototype_ `virtual int32 AddMaterial(UMaterialInterface* Material) override;`
- L28 _public prototype_ `virtual int32 AddMaterial(UMaterialInterface* Material, const FName& SlotName, const FName& ImportedSlotName) override;`
- L29 _public prototype_ `virtual void UpdateUVChannelData() override;`
- L30 _public prototype_ `virtual bool IsAsset() const override;`
- L31 _public prototype_ `virtual int32 LightmapUVIndex() const override;`
- L32 _public prototype_ `virtual FBoxSphereBounds GetBounds() const override;`
- L36 _protected member_ `UStaticMesh* StaticMesh;`
- L37 _protected member_ `int32 NumLODs;`

### `Source/Developer/MeshMergeUtilities/Public/StaticMeshComponentAdapter.h` (Public)


#### class `FStaticMeshComponentAdapter`  
`class FStaticMeshComponentAdapter : public IMaterialBakingAdapter`  
_L13-42_
- inherits: `IMaterialBakingAdapter`
- desc: Adapter which takes a Static Mesh Component instance to use for material baking (does not allow for changes to the underlying asset itself)
- L16 _public prototype_ `FStaticMeshComponentAdapter(UStaticMeshComponent* InStaticMeshComponent);`
- L19 _public prototype_ `virtual int32 GetNumberOfLODs() const override;` — Begin IMaterialBakingAdapter overrides
- L20 _public prototype_ `virtual void RetrieveRawMeshData(int32 LODIndex, FMeshDescription& InOutRawMesh, bool bPropogateMeshData) const override;`
- L21 _public prototype_ `virtual void RetrieveMeshSections(int32 LODIndex, TArray<FSectionInfo>& InOutSectionInfo) const override;`
- L22 _public prototype_ `virtual int32 GetMaterialIndex(int32 LODIndex, int32 SectionIndex) const override;`
- L23 _public prototype_ `virtual void ApplySettings(int32 LODIndex, FMeshData& InOutMeshData) const override;`
- L24 _public prototype_ `virtual UPackage* GetOuter() const override;`
- L25 _public prototype_ `virtual FString GetBaseName() const override;`
- L26 _public prototype_ `virtual FName GetMaterialSlotName(int32 MaterialIndex) const override;`
- L27 _public prototype_ `virtual FName GetImportedMaterialSlotName(int32 MaterialIndex) const override;`
- L28 _public prototype_ `virtual void SetMaterial(int32 MaterialIndex, UMaterialInterface* Material) override;`
- L29 _public prototype_ `virtual void RemapMaterialIndex(int32 LODIndex, int32 SectionIndex, int32 NewMaterialIndex) override;`
- L30 _public prototype_ `virtual int32 AddMaterial(UMaterialInterface* Material) override;`
- L31 _public prototype_ `virtual int32 AddMaterial(UMaterialInterface* Material, const FName& SlotName, const FName& ImportedSlotName) override;`
- L32 _public prototype_ `virtual void UpdateUVChannelData() override;`
- L33 _public prototype_ `virtual bool IsAsset() const override;`
- L34 _public prototype_ `virtual int32 LightmapUVIndex() const override;`
- L35 _public prototype_ `virtual FBoxSphereBounds GetBounds() const override;`
- L39 _protected member_ `UStaticMeshComponent* StaticMeshComponent;`
- L40 _protected member_ `UStaticMesh* StaticMesh;`
- L41 _protected member_ `int32 NumLODs;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHMERGEUTILITIES_API`
