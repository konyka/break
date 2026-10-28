# Plugins / DynamicWind

- module root: `Plugins/Experimental/DynamicWind/Source/DynamicWind`
- headers: 6; symbols: 108
- symbol kinds: class=5, function=4, macro=2, member=49, prototype=38, struct=7, typedef=3
- DynamicallyLoadedModuleNames: NaniteBuilder
- PrivateDependencyModuleNames: CoreUObject, DerivedDataCache, Engine, Foliage, ImageCore, MeshBuilder, MeshBuilderCommon, MeshDescription, MeshUtilities, MeshUtilitiesCommon, NaniteUtilities, Projects, RHI, RHICore, RawMesh, RenderCore, Renderer, Slate, SlateCore, StaticMeshDescription
- PrivateIncludePathModuleNames: NaniteBuilder
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/DynamicWind/Source/DynamicWind/Internal/DynamicWindLog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDynamicWind, Log, All);`

### `Plugins/Experimental/DynamicWind/Source/DynamicWind/Private/DynamicWindProvider.h` (Private)


#### class `FDynamicWindTransformProvider`  
`class FDynamicWindTransformProvider`  
_L21-90_
- L24 _public prototype_ `explicit FDynamicWindTransformProvider(FScene& InScene);`
- L25 _public prototype_ `FDynamicWindTransformProvider() = delete;`
- L26 _public prototype_ `~FDynamicWindTransformProvider();`
- L28 _public prototype_ `bool Register();`
- L29 _public prototype_ `bool Unregister();`
- L31 _public prototype_ `static FDynamicWindTransformProvider* FindForScene(const FSceneInterface* Scene);`
- L33 _public prototype_ `void RegisterProxy(const FSkinningSceneExtensionProxy* ExtensionProxy, const UDynamicWindSkeletalData* InSkeletalData);`
- L34 _public prototype_ `void UnregisterProxy(const FSkinningSceneExtensionProxy* ExtensionProxy);`
- L35 _public prototype_ `int32 UpdateParameters(const FDynamicWindParameters& Parameters);`
- L37 _public prototype_ `float GetBlendedWindAmplitude() const;`
- L40 _private typedef_ `using FBoneDataBuffer = TPersistentByteAddressBuffer<FDynamicWindBoneData>;`
- L41 _private typedef_ `using FBoneDataUploader = TByteAddressBufferScatterUploader<FDynamicWindBoneData>;`
- L53 _private function_ `friend uint32 GetTypeHash(const FSkeletonKey& Key)`
- L72 _private prototype_ `void ProvideTransforms(FSkinningTransformProvider::FProviderContext& Context);`
- L75 _private member_ `FScene& Scene;`
- L77 _private member_ `TMap<FSkeletonKey, FSkeletonEntry> SkeletonLookup;`
- L78 _private member_ `FSpanAllocator BoneDataAllocator;`
- L79 _private member_ `FBoneDataBuffer BoneDataBuffer;`
- L81 _private member_ `FDynamicWindParameters WindParameters = {};`
- L83 _private member_ `uint64 LastSimulatedFrameNumber = 0u;`
- L85 _private member_ `float BlendedWindAmplitude = -1.0f;`
- L87 _private member_ `bool bIsRegistered = false;`
- L89 _private member_ `static TMap<const FScene*, FDynamicWindTransformProvider*> SceneProviderMap;`

#### struct `FDynamicWindTransformProvider::FSkeletonKey`  
`struct FSkeletonKey`  
_L43-57_
- L45 _public member_ `FGuid SkeletonGuid;`
- L46 _public member_ `bool bUsesBoneMap = false;`
- L48 _public function_ `bool operator==(const FSkeletonKey& Other) const`

#### struct `FDynamicWindTransformProvider::FSkeletonEntry`  
`struct FSkeletonEntry`  
_L59-70_
- L61 _public member_ `uint64 UserDataHash = 0;`
- L62 _public member_ `uint32 NumBones = 0;`
- L63 _public member_ `uint32 ReferenceCount = 0;`
- L65 _public member_ `FName SkeletonName;`
- L68 _public member_ `FDynamicWindSkeletonData Data;`
- L69 _public member_ `TArray<FDynamicWindBoneData> PendingBoneData;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define DYNAMIC_WIND_TRANSFORM_PROVIDER_GUID 0xDFD4874B, 0xEE57466D, 0x883D6419, 0xAFE99EAC`
- L19 _macro_ `#define DYNAMIC_WIND_DEBUG_SKELETON_NAMES (UE_BUILD_DEBUG | UE_BUILD_DEVELOPMENT)`

### `Plugins/Experimental/DynamicWind/Source/DynamicWind/Public/DynamicWindData.h` (Public)


#### class `UDynamicWindData`  
`class UDynamicWindData : public UTransformProviderData`  
_L10-24_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI, BlueprintType)`
- inherits: `UTransformProviderData`
- L15 _public prototype_ `virtual bool IsEnabled() const override;`
- L16 _public function_ `virtual bool IsGpuOnly() const override`
- L17 _public prototype_ `virtual const FGuid& GetTransformProviderID() const override;`
- L18 _public prototype_ `virtual uint32 GetUniqueAnimationCount() const override;`
- L19 _public prototype_ `virtual bool UsesSkeletonBatching() const override;`
- L20 _public prototype_ `virtual bool HasAnimationBounds() const override;`
- L21 _public prototype_ `virtual bool GetAnimationBounds(uint32 AnimationIndex, FRenderBounds& OutBounds) const override;`
- L22 _public prototype_ `virtual uint32 GetSkinningDataOffset(int32 InstanceIndex, const FTransform& ComponentTransform, const FSkinnedMeshInstanceData& InstanceData) const override;`
- L23 _public prototype_ `virtual FTransformProviderRenderProxy* CreateRenderProxy(FInstancedSkinningSceneExtensionProxy* ExtensionProxy) const override;`

#### class `FDynamicWindDataProxy`  
`class FDynamicWindDataProxy : public FTransformProviderRenderProxy`  
_L26-40_
- inherits: `FTransformProviderRenderProxy`
- L31 _public prototype_ `FDynamicWindDataProxy(const UDynamicWindData* BankData, FInstancedSkinningSceneExtensionProxy* SceneExtensionProxy);`
- L32 _public prototype_ `virtual ~FDynamicWindDataProxy();`
- L33 _public prototype_ `virtual void CreateRenderThreadResources(FSceneInterface& Scene, FRHICommandListBase& RHICmdList) override;`
- L34 _public prototype_ `virtual void DestroyRenderThreadResources() override;`
- L37 _private member_ `FInstancedSkinningSceneExtensionProxy* SceneExtensionProxy = nullptr;`
- L39 _private member_ `class FDynamicWindTransformProvider* TransformProvider = nullptr;`

### `Plugins/Experimental/DynamicWind/Source/DynamicWind/Public/DynamicWindParameters.h` (Public)


#### struct `FDynamicWindParameters`  
`struct FDynamicWindParameters`  
_L11-36_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `FVector SimulationCenter = FVector::Zero();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicWind")`
- L20 _public member_ `float SimulationExtents = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicWind")`
- L23 _public member_ `FVector WindDirection = FVector::ForwardVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicWind")`
- L26 _public member_ `float WindSpeed = 15.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicWind")`
- L29 _public member_ `float WindAmplitude = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicWind")`
- L32 _public member_ `TObjectPtr<UTexture> WindTexture = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicWind")`
- L35 _public member_ `FVector4f DebugModulation = FVector4f::Zero();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicWind")`

### `Plugins/Experimental/DynamicWind/Source/DynamicWind/Public/DynamicWindSkeletalData.h` (Public)


#### struct `FDynamicWindSimulationGroupData`  
`struct FDynamicWindSimulationGroupData`  
_L10-31_
- reflection: `USTRUCT()`
- L15 _public member_ `bool bUseDualInfluence = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data")`
- L18 _public member_ `float Influence = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data", meta=(EditCondition = "!bUseDualInfluence", EditConditionHides, ClampMin=0.0f, ClampMax=1.0f))`
- L21 _public member_ `float MinInfluence = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data", meta=(EditCondition = "bUseDualInfluence", EditConditionHides, ClampMin=0.0f, ClampMax=1.0f))`
- L24 _public member_ `float MaxInfluence = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data", meta=(EditCondition = "bUseDualInfluence", EditConditionHides, ClampMin=0.0f, ClampMax=1.0f))`
- L27 _public member_ `float ShiftTop = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data", meta=(EditCondition = "bUseDualInfluence", EditConditionHides, ClampMin=0.0f, ClampMax=1.0f))`
- L30 _public member_ `bool bIsTrunkGroup = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data", meta=(DisplayName = "Is Trunk?"))`

#### struct `FDynamicWindSimulationGroupBoneLookup`  
`struct FDynamicWindSimulationGroupBoneLookup`  
_L34-43_
- reflection: `USTRUCT()`
- L39 _public member_ `int32 SimulationGroupIndex = INDEX_NONE;` — `UPROPERTY()`
- L42 _public member_ `TSet<int32> BoneIndices;` — `UPROPERTY()`

#### struct `FDynamicWindBoneChainData`  
`struct FDynamicWindBoneChainData`  
_L46-55_
- reflection: `USTRUCT()`
- L51 _public member_ `uint32 NumBones = 0;` — `UPROPERTY()`
- L54 _public member_ `float ChainLength = 0.0f;` — `UPROPERTY()`

#### struct `FDynamicWindExtraBoneData`  
`struct FDynamicWindExtraBoneData`  
_L58-67_
- reflection: `USTRUCT()`
- L63 _public member_ `int32 BoneChainOriginBoneIndex = INDEX_NONE;` — `UPROPERTY()`
- L66 _public member_ `int32 IndexInBoneChain = 0;` — `UPROPERTY()`

#### class `UDynamicWindSkeletalData`  
`class UDynamicWindSkeletalData : public UAssetUserData`  
_L70-115_
- reflection: `UCLASS()`
- inherits: `UAssetUserData`
- L77 _public member_ `bool bIsEnabled = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data")` — When true, the SkeletalMesh object will be registered with the DynamicWind system.
- L81 _public member_ `bool bIsGroundCover = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data")` — If true, marks this object as ground cover, and won't attenuate wind based on bone height.
- L85 _public member_ `float GustAttenuation = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data")` — Uniformly attenuates the influence of wind on trunk simulation groups.
- L88 _public member_ `TArray<FDynamicWindSimulationGroupData> SimulationGroups;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Data")`
- L91 _public member_ `TArray<FDynamicWindSimulationGroupBoneLookup> SimulationGroupBones;` — `UPROPERTY()`
- L94 _public member_ `TMap<int32, FDynamicWindBoneChainData> BoneChains;` — `UPROPERTY()`
- L97 _public member_ `TMap<int32, FDynamicWindExtraBoneData> ExtraBonesData;` — `UPROPERTY()`
- L100 _public prototype_ `int32 GetBoneSimulationGroupIndex(int32 BoneIndex) const;`
- L101 _public prototype_ `float GetBoneInfluence(int32 BoneIndex) const;`
- L102 _public prototype_ `bool IsTrunkBone(int32 BoneIndex) const;`
- L103 _public prototype_ `float GetBoneChainLength(int32 BoneIndex) const;`
- L104 _public prototype_ `void RecalculateSkeletalDataHash();`
- L105 _public function_ `uint64 GetSkeletalDataHash() const`
- L108 _public prototype_ `virtual void PostLoad() override;`
- L110 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& Event) override;`
- L114 _private member_ `uint64 SkeletalDataHash = 0ull;`

### `Plugins/Experimental/DynamicWind/Source/DynamicWind/Public/DynamicWindSubsystem.h` (Public)


#### class `UDynamicWindSubsystem`  
`class UDynamicWindSubsystem : public UWorldSubsystem`  
_L18-46_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Rendering, Common))`
- inherits: `UWorldSubsystem`
- L23 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L25 _public prototype_ `virtual void PostInitialize() override;`
- L26 _public prototype_ `virtual void PreDeinitialize() override;`
- L30 _public prototype_ `float GetBlendedWindAmplitude() const;` — `UFUNCTION(BlueprintCallable, Category = "DynamicWind")`
- L33 _public prototype_ `void UpdateWindParameters(const FDynamicWindParameters& Parameters);` — `UFUNCTION(BlueprintCallable, Category = "DynamicWind")`
- L36 _private prototype_ `void CreateTransformProvider(UWorld& World);`
- L37 _private prototype_ `void ReleaseTransformProvider();`
- L39 _private typedef_ `using FTransformProviderPtr = TSharedPtr<FDynamicWindTransformProvider, ESPMode::ThreadSafe>;`
- L41 _private member_ `FTransformProviderPtr TransformProvider;`
- L43 _private member_ `FDelegateHandle OnPreRecreateScene;`
- L44 _private member_ `FDelegateHandle OnPostRecreateScene;`
