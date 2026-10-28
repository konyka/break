# Plugins / WorldPartitionHLODUtilities

- module root: `Plugins/Editor/WorldPartitionHLODUtilities/Source`
- headers: 10; symbols: 121
- symbol kinds: class=17, enum=2, enumerator=12, function=10, macro=3, member=37, prototype=34, struct=6
- DynamicallyLoadedModuleNames: GeometryProcessingInterfaces, MeshReductionInterface, MeshUtilities
- PrivateDependencyModuleNames: Engine, ImageWrapper, ImageWriteQueue, Json, JsonUtilities, MaterialBaking, MaterialUtilities, MeshDescription, MeshMergeUtilities, RHI, RenderCore, ScreenShotComparison, ScreenShotComparisonTools, Slate, SlateCore, StaticMeshDescription, WorldPartitionEditor
- PrivateIncludePathModuleNames: GeometryProcessingInterfaces
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Builders/HLODBuilderCustomHLODActor.h` (Public)


#### class `UHLODBuilderCustomHLODActorSettings`  
`class UHLODBuilderCustomHLODActorSettings : public UHLODBuilderSettings`  
_L10-15_
- reflection: `UCLASS(Blueprintable, Config = Engine, PerObjectConfig)`
- inherits: `UHLODBuilderSettings`
- L14 _private function_ `virtual bool IsReusingSourceMaterials() const override`

#### class `UHLODBuilderCustomHLODActor`  
`class UHLODBuilderCustomHLODActor : public UHLODBuilder`  
_L18-25_
- reflection: `UCLASS(HideDropdown)`
- inherits: `UHLODBuilder`
- L23 _public prototype_ `virtual TSubclassOf<UHLODBuilderSettings> GetSettingsClass() const override;`
- L24 _public prototype_ `virtual TArray<UActorComponent*> Build(const FHLODBuildContext& InHLODBuildContext, const TArray<UActorComponent *>& InSourceComponents) const override;`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Builders/HLODBuilderInstancing.h` (Public)


#### enum `EInstanceFilteringType`  
`enum class EInstanceFilteringType : uint8`  
_L12-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `FilterNone UMETA(DisplayName = "No Filtering")`
- L15 _public enumerator_ `FilterMinimumExtent`
- L16 _public enumerator_ `FilterMinimumArea`
- L17 _public enumerator_ `FilterMinimumVolume`

#### class `UHLODBuilderInstancingSettings`  
`class UHLODBuilderInstancingSettings : public UHLODBuilderSettings`  
_L21-56_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Config = Engine, PerObjectConfig)`
- inherits: `UHLODBuilderSettings`
- L25 _private prototype_ `virtual void ComputeHLODHash(FHLODHashBuilder& InHashBuilder) const override;`
- L30 _private function_ `virtual bool IsReusingSourceMaterials() const override` — By definition, instancing means reusing the source assets.
- L37 _private member_ `bool bDisallowNanite;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = Rendering)` — If enabled, the components created for the HLODs will not use Nanite. Necessary if you want to use the last LOD & the mesh is Nanite enabled, as forced LODs are ignored by Nanite
- L43 _private member_ `EInstanceFilteringType InstanceFilteringType;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = Filtering)` — Type of filtering to apply to instances. Instances that do not pass the filter will be excluded from the HLOD.
- L47 _private member_ `double MinimumExtent;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = Filtering, Meta = (DisplayName = "Minimum Extent", ToolTip = "Minimum Extent in Unreal Units", EditCondition = "InstanceFilteringType==EInstanceFilteringType::FilterMinimumExtent", EditConditionHides))` — Minimum extent for an instance to be included in the HLOD. 0 means no minimum.
- L51 _private member_ `double MinimumArea;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = Filtering, Meta = (DisplayName = "Minimum Area (uu²)", ToolTip = "Minimum area in square Unreal Units", EditCondition = "InstanceFilteringType==EInstanceFilteringType::FilterMinimumArea", EditConditionHides))` — Minimum area for an instance to be included in the HLOD. 0 means no minimum. Value is in Unreal Unit ^ 2
- L55 _private member_ `double MinimumVolume;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = Filtering, Meta = (DisplayName = "Minimum Volume (uu³)", ToolTip = "Minimum volume in cubic Unreal Units", EditCondition = "InstanceFilteringType==EInstanceFilteringType::FilterMinimumVolume", EditConditionHides))` — Minimum volume for an instance to be included in the HLOD. 0 means no minimum. Value is in Unreal Unit ^ 3

#### class `UHLODBuilderInstancing`  
`class UHLODBuilderInstancing : public UHLODBuilder`  
_L63-72_
- reflection: `UCLASS(MinimalAPI, HideDropdown)`
- inherits: `UHLODBuilder`
- desc: Build a AWorldPartitionHLOD whose components are ISMC
- L68 _public function_ `virtual bool RequiresWarmup() const override`
- L69 _public function_ `virtual bool ShouldIgnoreBatchingPolicy() const override`
- L70 _public prototype_ `virtual TSubclassOf<UHLODBuilderSettings> GetSettingsClass() const override;`
- L71 _public prototype_ `virtual TArray<UActorComponent*> Build(const FHLODBuildContext& InHLODBuildContext, const TArray<UActorComponent*>& InSourceComponents) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WORLDPARTITIONHLODUTILITIES_API`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Builders/HLODBuilderMeshApproximate.h` (Public)


#### class `UHLODBuilderMeshApproximateSettings`  
`class UHLODBuilderMeshApproximateSettings : public UHLODBuilderSettings`  
_L15-28_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UHLODBuilderSettings`
- L19 _private prototype_ `virtual void ComputeHLODHash(FHLODHashBuilder& InHashBuilder) const override;`
- L23 _private member_ `FMeshApproximationSettings MeshApproximationSettings;` — `UPROPERTY(EditAnywhere, Category = HLOD, meta=(EditInline))` — Mesh approximation settings
- L27 _private member_ `TObjectPtr<UMaterialInterface> HLODMaterial;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = HLOD, meta = (DisplayName = "HLOD Material"))` — Material that will be used by the generated HLOD static mesh

#### class `UHLODBuilderMeshApproximate`  
`class UHLODBuilderMeshApproximate : public UHLODBuilder`  
_L35-42_
- reflection: `UCLASS(MinimalAPI, HideDropdown)`
- inherits: `UHLODBuilder`
- desc: Build an approximated mesh using geometry from the provided actors
- L40 _public prototype_ `virtual TSubclassOf<UHLODBuilderSettings> GetSettingsClass() const override;`
- L41 _public prototype_ `virtual TArray<UActorComponent*> Build(const FHLODBuildContext& InHLODBuildContext, const TArray<UActorComponent*>& InSourceComponents) const override;`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Builders/HLODBuilderMeshMerge.h` (Public)


#### class `UHLODBuilderMeshMergeSettings`  
`class UHLODBuilderMeshMergeSettings : public UHLODBuilderSettings`  
_L15-34_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UHLODBuilderSettings`
- L19 _private prototype_ `virtual void ComputeHLODHash(FHLODHashBuilder& InHashBuilder) const override;`
- L25 _private function_ `virtual bool IsReusingSourceMaterials() const` — Merge mesh will only reuse the source materials when not merging the materials. In this case, the created mesh will have multiple sections, with each of them directly using the source materials.
- L29 _private member_ `FMeshMergingSettings MeshMergeSettings;` — `UPROPERTY(EditAnywhere, Category = HLOD)` — Merged mesh generation settings
- L33 _private member_ `TObjectPtr<UMaterialInterface> HLODMaterial;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = HLOD, meta = (DisplayName = "HLOD Material"))` — Material that will be used by the generated HLOD static mesh

#### class `UHLODBuilderMeshMerge`  
`class UHLODBuilderMeshMerge : public UHLODBuilder`  
_L41-48_
- reflection: `UCLASS(MinimalAPI, HideDropdown)`
- inherits: `UHLODBuilder`
- desc: Build a merged mesh using geometry from the provided actors
- L46 _public prototype_ `virtual TSubclassOf<UHLODBuilderSettings> GetSettingsClass() const override;`
- L47 _public prototype_ `virtual TArray<UActorComponent*> Build(const FHLODBuildContext& InHLODBuildContext, const TArray<UActorComponent*>& InSourceComponents) const override;`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Builders/HLODBuilderMeshSimplify.h` (Public)


#### class `UHLODBuilderMeshSimplifySettings`  
`class UHLODBuilderMeshSimplifySettings : public UHLODBuilderSettings`  
_L15-28_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UHLODBuilderSettings`
- L19 _private prototype_ `virtual void ComputeHLODHash(FHLODHashBuilder& InHashBuilder) const override;`
- L23 _private member_ `FMeshProxySettings MeshSimplifySettings;` — `UPROPERTY(EditAnywhere, Category = HLOD)` — Simplified mesh generation settings
- L27 _private member_ `TObjectPtr<UMaterialInterface> HLODMaterial;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = HLOD, meta = (DisplayName = "HLOD Material"))` — Material that will be used by the generated HLOD static mesh

#### class `UHLODBuilderMeshSimplify`  
`class UHLODBuilderMeshSimplify : public UHLODBuilder`  
_L35-42_
- reflection: `UCLASS(MinimalAPI, HideDropdown)`
- inherits: `UHLODBuilder`
- desc: Build a simplified mesh using geometry from the provided actors
- L40 _public prototype_ `virtual TSubclassOf<UHLODBuilderSettings> GetSettingsClass() const override;`
- L41 _public prototype_ `virtual TArray<UActorComponent*> Build(const FHLODBuildContext& InHLODBuildContext, const TArray<UActorComponent*>& InSourceComponents) const override;`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Modifiers/HLODModifierMeshDestruction.h` (Public)


#### class `UWorldPartitionHLODModifierMeshDestruction`  
`class UWorldPartitionHLODModifierMeshDestruction : public UWorldPartitionHLODModifier`  
_L16-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldPartitionHLODModifier`
- L20 _private prototype_ `virtual bool CanModifyHLOD(TSubclassOf<UHLODBuilder> InHLODBuilderClass) const override;`
- L21 _private prototype_ `virtual void BeginHLODBuild(const FHLODBuildContext& InHLODBuildContext) override;`
- L22 _private prototype_ `virtual void EndHLODBuild(TArray<UActorComponent*>&InOutComponents) override;`
- L23 _private prototype_ `virtual bool MustBeLoadedOnServer() const override;`
- L27 _private member_ `TUniquePtr<FDestructionMeshMergeExtension> DestructionMeshMergeExtension;` — Gathers a list of actors included in the merged mesh
- L30 _private member_ `FVector CachedWorldPosition;` — Cached from the HLOD Build Context provided to BeginHLODBuild()

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WORLDPARTITIONHLODUTILITIES_API`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/RebuildPolicies/HLODRebuildPolicyHashCompare.h` (Public)


#### class `UHLODRebuildPolicyHashData`  
`class UHLODRebuildPolicyHashData : public UHLODRebuildPolicyData`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `UHLODRebuildPolicyData`
- L15 _public function_ `virtual FString ToString() const override`
- L19 _public member_ `uint32 HLODHash;` — `UPROPERTY()`
- L23 _public member_ `FString HLODHashReport;` — `UPROPERTY(Transient)` — Transient, will be aggregated into the HLOD actor build report

#### class `UHLODRebuildPolicyHashCompare`  
`class UHLODRebuildPolicyHashCompare : public UHLODRebuildPolicy`  
_L34-45_
- reflection: `UCLASS()`
- inherits: `UHLODRebuildPolicy`
- desc: This HLOD rebuild policy computes a hash of various elements in order to detect any change that might impact the resulting HLODs. It is, in effect, extremely sensitive. It will: APPROVE a rebuild - if the old hash differs from the new hash REJECT  a rebuild - if the old hash equals the new hash
- L39 _protected function_ `virtual TSubclassOf<UHLODRebuildPolicyData> GetRebuildPolicyDataType() const override`
- L40 _protected prototype_ `virtual EHLODRebuildPolicyDecision Evaluate(const AWorldPartitionHLOD* InHLODActor, const UHLODRebuildPolicyData* InOldData, const UHLODRebuildPolicyData* InNewData, FString& OutReason) const override;`
- L41 _protected prototype_ `virtual UHLODRebuildPolicyData* ComputeDataForRebuildPolicy(const AWorldPartitionHLOD* InHLODActor, const TArray<UActorComponent*>& InSourceComponents, const UHLODRebuildPolicyData* InExistingPolicyData) const override;`
- L44 _private prototype_ `void ComputeHLODHash(FHLODHashBuilder& InHashBuilder, const AWorldPartitionHLOD* InHLODActor, const TArray<UActorComponent*>& InSourceComponents) const;`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/RebuildPolicies/HLODRebuildPolicyImageCompare.h` (Public)


#### enum `EHLODCaptureImageType`  
`enum EHLODCaptureImageType : uint8`  
_L10-20_
- reflection: `UENUM()`
- L12 _public enumerator_ `Capture_AlphaMask` — 8-bits
- L13 _public enumerator_ `Capture_BaseColor` — 24-bits
- L14 _public enumerator_ `Capture_Normal` — 24-bits
- L15 _public enumerator_ `Capture_Emissive` — 24-bits
- L16 _public enumerator_ `Capture_Metallic` — 8-bits
- L17 _public enumerator_ `Capture_Roughness` — 8-bits
- L18 _public enumerator_ `Capture_Specular` — 8-bits
- L19 _public enumerator_ `Num`

#### struct `THLODCaptureImageTraits`  
`template<EHLODCaptureImageType T> struct THLODCaptureImageTraits`  
_L22-22_
- L22 _public member_ `template<EHLODCaptureImageType T> struct THLODCaptureImageTraits { static constexpr int32 NumChannels = 1; };`

#### struct `THLODCaptureImageTraits`  
`template<EHLODCaptureImageType T> struct THLODCaptureImageTraits`  
_L23-23_
- L22 _public member_ `template<EHLODCaptureImageType T> struct THLODCaptureImageTraits { static constexpr int32 NumChannels = 1; };`

#### struct `THLODCaptureImageTraits`  
`template<EHLODCaptureImageType T> struct THLODCaptureImageTraits`  
_L24-24_
- L22 _public member_ `template<EHLODCaptureImageType T> struct THLODCaptureImageTraits { static constexpr int32 NumChannels = 1; };`

#### struct `THLODCaptureImageTraits`  
`template<EHLODCaptureImageType T> struct THLODCaptureImageTraits`  
_L25-25_
- L22 _public member_ `template<EHLODCaptureImageType T> struct THLODCaptureImageTraits { static constexpr int32 NumChannels = 1; };`

#### struct `FHLODCaptureImage`  
`struct FHLODCaptureImage`  
_L28-52_
- reflection: `USTRUCT()`
- L32 _public function_ `FHLODCaptureImage() : Width(0) , Height(0) , BytesPerPixel(0)`
- L39 _public member_ `int32 Width;` — `UPROPERTY()`
- L42 _public member_ `int32 Height;` — `UPROPERTY()`
- L45 _public member_ `uint8 BytesPerPixel;` — `UPROPERTY()`
- L48 _public member_ `TArray<uint8> PixelsCompressed;` — `UPROPERTY()` — Compressed, minimal number of channels (BytesPerPixel), saved to disk
- L51 _public member_ `TArray<FColor> Pixels;` — `UPROPERTY(Transient)` — Uncompressed, RGBA, not saved to disk

#### struct `FHLODCaptureFrame`  
`struct FHLODCaptureFrame`  
_L55-77_
- reflection: `USTRUCT()`
- L59 _public function_ `FHLODCaptureFrame() : CameraLocation(ForceInitToZero) , CameraRotation(ForceInitToZero) , OrthoWidth(0.0f)`
- L67 _public member_ `FVector CameraLocation;` — `UPROPERTY()`
- L70 _public member_ `FRotator CameraRotation;` — `UPROPERTY()`
- L73 _public member_ `float OrthoWidth;` — `UPROPERTY()`
- L76 _public member_ `FHLODCaptureImage Images[EHLODCaptureImageType::Num];` — `UPROPERTY()`

#### class `UHLODRebuildPolicyImageData`  
`class UHLODRebuildPolicyImageData : public UHLODRebuildPolicyData`  
_L80-107_
- reflection: `UCLASS()`
- inherits: `UHLODRebuildPolicyData`
- L86 _public member_ `FBox CaptureBounds;` — `UPROPERTY()`
- L89 _public member_ `TArray<FHLODCaptureFrame> CaptureFrames;` — `UPROPERTY()`
- L92 _public member_ `uint32 HLODLayerHash;` — `UPROPERTY()`
- L95 _public member_ `bool bNeedsDataCompression = false;` — `UPROPERTY(Transient)`
- L98 _public member_ `bool bNeedsDataDecompression = true;` — `UPROPERTY(Transient)`
- L100 _public prototype_ `void CompressData() const;`
- L101 _public prototype_ `bool DecompressData() const;`
- L105 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext InObjectSaveContext) override;`

#### class `UHLODRebuildPolicyImageCompare`  
`class UHLODRebuildPolicyImageCompare : public UHLODRebuildPolicy`  
_L117-140_
- reflection: `UCLASS(MinimalAPI, Config = Editor)`
- inherits: `UHLODRebuildPolicy`
- desc: This HLOD rebuild policy takes screen captures of the SOURCE actors over multiple angles (and for different GBuffer properties) It will then perform an SSIM evaluation in order to assess if there is a significant visual change between the old and new data set. It will: APPROVE a rebuild - if the difference between old vs new images is greater than the configured threshold REJECT  a rebuild - if the difference between old vs new images is less than the configured threshold
- L122 _protected function_ `virtual TSubclassOf<UHLODRebuildPolicyData> GetRebuildPolicyDataType() const override`
- L123 _protected prototype_ `virtual EHLODRebuildPolicyDecision Evaluate(const AWorldPartitionHLOD* InHLODActor, const UHLODRebuildPolicyData* InOldData, const UHLODRebuildPolicyData* InNewData, FString& OutReason) const override;`
- L124 _protected prototype_ `virtual UHLODRebuildPolicyData* ComputeDataForRebuildPolicy(const AWorldPartitionHLOD* InHLODActor, const TArray<UActorComponent*>& InSourceComponents, const UHLODRebuildPolicyData* InExistingPolicyData) const override;`
- L127 _protected member_ `uint32 MaxImageSize = 512;` — `UPROPERTY(Config)`
- L130 _protected member_ `uint32 WarmupFrameCount = 5;` — `UPROPERTY(Config)`
- L133 _protected member_ `float CaptureImageMargin = 0.10f;` — `UPROPERTY(Config)`
- L136 _protected member_ `float MaximumLocalError = 1.00f;` — `UPROPERTY(Config)`
- L139 _protected member_ `float MaximumGlobalError = 0.015f;` — `UPROPERTY(Config)`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Utilities/WorldPartitionHLODUtilities.h` (Public)


#### class `FWorldPartitionHLODUtilities`  
`class FWorldPartitionHLODUtilities : public IWorldPartitionHLODUtilities`  
_L10-21_
- inherits: `IWorldPartitionHLODUtilities`
- desc: FWorldPartitionHLODUtilities implementation
- L13 _public prototype_ `virtual TArray<AWorldPartitionHLOD*> CreateHLODActors(FHLODCreationContext& InCreationContext, const FHLODCreationParams& InCreationParams, const TArray<IStreamingGenerationContext::FActorInstance>& InActors) override;`
- L14 _public prototype_ `virtual bool BuildHLOD(const FHLODBuildParams& InBuildParams) override;`
- L15 _public prototype_ `virtual TSubclassOf<UHLODBuilder> GetHLODBuilderClass(const UHLODLayer* InHLODLayer) override;`
- L16 _public prototype_ `virtual UHLODBuilderSettings* CreateHLODBuilderSettings(UHLODLayer* InHLODLayer) override;`
- L17 _public prototype_ `virtual void SetHLODBuildEvaluator(IWorldPartitionHLODUtilities::FHLODBuildEvaluator BuildEvaluatorDelegate) override;`
- L20 _protected member_ `IWorldPartitionHLODUtilities::FHLODBuildEvaluator HLODBuildEvaluatorDelegate;`

### `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartitionHLODUtilitiesModule.h` (Public)


#### class `FWorldPartitionHLODUtilitiesModule`  
`class FWorldPartitionHLODUtilitiesModule : public IWorldPartitionHLODUtilitiesModule`  
_L12-22_
- inherits: `IWorldPartitionHLODUtilitiesModule`
- desc: IWorldPartitionHLODUtilities module interface
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual IWorldPartitionHLODUtilities* GetUtilities() override;`
- L21 _private member_ `IWorldPartitionHLODUtilities* Utilities;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API WORLDPARTITIONHLODUTILITIES_API`
