# Plugins / HierarchyTableAnimationRuntime

- module root: `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Runtime`
- headers: 6; symbols: 126
- symbol kinds: class=3, enum=3, enumerator=9, function=4, macro=3, member=47, prototype=48, struct=9
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, HierarchyTableRuntime

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Runtime/Public/AnimNode_BlendProfileLayeredBlend.h` (Public)


#### enum `EBlendProfileRotationBlendSpace`  
`enum class EBlendProfileRotationBlendSpace : uint8`  
_L19-27_
- reflection: `UENUM(BlueprintType)`
- desc: The space in which bone rotations are blended
- L22 _public enumerator_ `LocalSpace UMETA(DisplayName = "Local Space")` — Blend bone rotations in local space
- L24 _public enumerator_ `MeshSpace UMETA(DisplayName = "Mesh Space")` — Blend bone rotations in mesh space
- L26 _public enumerator_ `RootSpace UMETA(DisplayName = "Root Space")` — Blend bone rotations in root space (mesh space relative to the root bone)

#### struct `FAnimNode_BlendProfileLayeredBlend`  
`struct FAnimNode_BlendProfileLayeredBlend : public FAnimNode_Base`  
_L30-133_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L37 _public member_ `FPoseLink BasePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)` — The source pose
- L41 _public member_ `FPoseLink BlendPose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (BlueprintCompilerGeneratedDefaults))` — The target pose
- L47 _public member_ `TObjectPtr<UBlendProfileStandalone> BlendProfileAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config, meta = (PinHiddenByDefault))` — The blend profile mask asset to use to control layering of the pose, curves, and attributes
- L51 _public member_ `EBlendProfileRotationBlendSpace RotationBlendSpace = EBlendProfileRotationBlendSpace::LocalSpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config, meta = (PinHiddenByDefault))` — The space in which bone rotations are blended
- L57 _public member_ `bool bMeshSpaceRotationBlend_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "bMeshSpaceRotationBlend is deprecated, use RotationBlendSpace instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use RotationBlendSpace instead."))` — Whether to blend bone rotations in mesh space or in local space
- L61 _public member_ `bool bCustomCurveBlending;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)`
- L69 _protected member_ `FGuid SkeletonGuid;` — `UPROPERTY()` — Guids for skeleton used to determine whether the HierarchyTableBlendProfile need rebuilding
- L73 _protected member_ `FGuid VirtualBoneGuid;` — `UPROPERTY()` — Guid for virtual bones used to determine whether the HierarchyTableBlendProfile need rebuilding
- L77 _protected member_ `FGuid MaskTableGuid;` — `UPROPERTY()` — Guid for mask table used to determine whether the HierarchyTableBlendProfile need rebuilding
- L80 _protected member_ `uint16 RequiredBonesSerialNumber = 0;` — Serial number of the required bones container
- L84 _protected member_ `float BlendWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Runtime, meta = (BlueprintCompilerGeneratedDefaults, PinShownByDefault))` — The weight of target pose
- L88 _protected member_ `bool bBlendRootMotionBasedOnRootBone;` — `UPROPERTY(EditAnywhere, Category = Config)` — Whether to incorporate the per-bone blend weight of the root bone when lending root motion
- L91 _public function_ `FAnimNode_BlendProfileLayeredBlend() : bCustomCurveBlending(false) , CurveBlendingOption(ECurveBlendOption::Override) , BlendWeight(1.0f) , bBlendRootMotionBasedOnRootBone(true)`
- L102 _public prototype_ `~FAnimNode_BlendProfileLayeredBlend() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables this is a requirement for clang to compile without warnings.
- L103 _public prototype_ `FAnimNode_BlendProfileLayeredBlend(const FAnimNode_BlendProfileLayeredBlend&) = default;`
- L104 _public prototype_ `FAnimNode_BlendProfileLayeredBlend(FAnimNode_BlendProfileLayeredBlend&&) = default;`
- L105 _public prototype_ `FAnimNode_BlendProfileLayeredBlend& operator=(const FAnimNode_BlendProfileLayeredBlend&) = default;`
- L106 _public prototype_ `FAnimNode_BlendProfileLayeredBlend& operator=(FAnimNode_BlendProfileLayeredBlend&&) = default;`
- L110 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L111 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L112 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L113 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L114 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L119 _private prototype_ `bool ArePerBoneBlendWeightsValid(const USkeleton* InSkeleton) const;` — Check whether per-bone blend weights are valid according to the skeleton (GUID check)
- L122 _private prototype_ `void UpdateCachedBoneData(const FBoneContainer& RequiredBones, USkeleton* Skeleton);` — Update cached data if required
- L126 _private prototype_ `void UpdateDesiredBoneWeight();`
- L128 _private member_ `TArray<float> DesiredBoneBlendWeights;`
- L129 _private member_ `TArray<float> CurrentBoneBlendWeights;`
- L132 _private member_ `TObjectPtr<UBlendProfileStandalone> CachedBlendProfile;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HIERARCHYTABLEANIMATIONRUNTIME_API`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Runtime/Public/BlendProfileStandalone.h` (Public)


#### enum `EBlendProfileStandaloneType`  
`enum class EBlendProfileStandaloneType`  
_L14-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `WeightFactor`
- L17 _public enumerator_ `TimeFactor`
- L18 _public enumerator_ `BlendMask`

#### class `UBlendProfileStandalone`  
`class UBlendProfileStandalone : public UObject`  
_L22-80_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, BlueprintType)`
- inherits: `UObject`
- L28 _public prototype_ `virtual void PostLoad() override;`
- L30 _public prototype_ `virtual void BeginDestroy() override;`
- L31 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L32 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L37 _public prototype_ `void UpdateHierarchy();`
- L39 _public prototype_ `void UpdateCachedData();`
- L41 _public prototype_ `bool IsCachedDataStale() const;`
- L44 _public prototype_ `TObjectPtr<USkeleton> GetSkeleton() const;`
- L48 _public member_ `EBlendProfileStandaloneType Type;` — `UPROPERTY(VisibleAnywhere, Category=Default, AssetRegistrySearchable)`
- L52 _public member_ `TObjectPtr<UHierarchyTable> Table;` — `UPROPERTY()`
- L58 _public member_ `FBlendProfileStandaloneCachedData CachedBlendProfileData;` — `UPROPERTY()` — The flattened version of the table data for use at runtime instead of, slowly traversing the table tree.
- L62 _private prototype_ `void SetSkeleton(TObjectPtr<USkeleton> InSkeleton);`
- L64 _private prototype_ `void HandleSkeletonHierarchyChanged();`
- L68 _private member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(VisibleAnywhere, Category=Default)`
- L71 _private member_ `FGuid SkeletonHierarchyGuid;` — `UPROPERTY()`
- L74 _private member_ `FGuid SkeletonVirtualBonesHierarchyGuid;` — `UPROPERTY()`
- L78 _private member_ `FGuid CachedEntriesGuid;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HIERARCHYTABLEANIMATIONRUNTIME_API`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Runtime/Public/HierarchyTableAnimationRuntimeModule.h` (Public)


#### class `FHierarchyTableAnimationRuntimeModule`  
`class FHierarchyTableAnimationRuntimeModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Runtime/Public/HierarchyTableBlendProfile.h` (Public)


#### struct `FMaskedAttributeWeightSerialised`  
`struct FMaskedAttributeWeightSerialised`  
_L14-29_
- reflection: `USTRUCT()`
- L19 _public member_ `FName AttributeNamespace;` — `UPROPERTY()`
- L22 _public member_ `FName AttributeName;` — `UPROPERTY()`
- L25 _public member_ `int32 AttributeIndex = INDEX_NONE;` — `UPROPERTY()`
- L28 _public member_ `float Weight = 0.0f;` — `UPROPERTY()`

#### struct `FMaskedCurveWeightSerialised`  
`struct FMaskedCurveWeightSerialised`  
_L32-41_
- reflection: `USTRUCT()`
- L37 _public member_ `FName CurveName;` — `UPROPERTY()`
- L40 _public member_ `float Weight = 0.0f;` — `UPROPERTY()`

#### struct `FBlendProfileStandaloneCachedData`  
`struct FBlendProfileStandaloneCachedData`  
_L44-111_
- reflection: `USTRUCT()`
- L49 _public prototype_ `void UnpackCachedData();`
- L51 _public prototype_ `void Init(TObjectPtr<UHierarchyTable> InHierarchyTable, const EBlendProfileMode InMode);`
- L53 _public prototype_ `void Reset();`
- L79 _public prototype_ `const TArray<float>& GetBoneBlendWeights() const;`
- L81 _public prototype_ `const UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FCurveElement>& GetCurveBlendWeights() const;`
- L83 _public prototype_ `const TArray<FMaskedAttributeWeight>& GetAttributeBlendWeights() const;`
- L85 _public prototype_ `void ConstructBlendProfile(const TObjectPtr<UBlendProfile> OutBlendProfile) const;`
- L87 _public prototype_ `bool IsValidBoneIndex(const int32 BoneIndex) const;`
- L89 _public prototype_ `TObjectPtr<USkeleton> GetSkeleton() const;`
- L93 _private member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY()`
- L96 _private member_ `TArray<float> BoneBlendWeights;` — `UPROPERTY()`
- L99 _private member_ `TArray<FMaskedCurveWeightSerialised> SerializedCurveBlendWeights;` — `UPROPERTY()`
- L102 _private member_ `TArray<FMaskedAttributeWeightSerialised> SerializedAttributeBlendWeights;` — `UPROPERTY()`
- L105 _private member_ `EBlendProfileMode Mode = EBlendProfileMode::WeightFactor;` — `UPROPERTY()`
- L108 _private member_ `UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FCurveElement> CurveBlendWeights;`
- L110 _private member_ `TArray<FMaskedAttributeWeight> AttributeBlendWeights;`

#### struct `FBlendProfileStandaloneCachedData::FNamedFloat`  
`struct FNamedFloat`  
_L55-65_
- L57 _public member_ `FName Name;`
- L58 _public member_ `float Value;`
- L60 _public function_ `FNamedFloat(const FName InName, const float InValue) : Name(InName) , Value(InValue)`

#### struct `FBlendProfileStandaloneCachedData::FMaskedAttributeWeight`  
`struct FMaskedAttributeWeight`  
_L67-77_
- L69 _public member_ `UE::Anim::FAttributeId Attribute;`
- L70 _public member_ `float Weight;`
- L72 _public function_ `FMaskedAttributeWeight(const UE::Anim::FAttributeId InAttribute, const float InWeight) : Attribute(InAttribute) , Weight(InWeight)`

#### class `FHierarchyTableBlendProfile`  
`class FHierarchyTableBlendProfile : public IBlendProfileInterface`  
_L113-148_
- inherits: `IBlendProfileInterface`
- L116 _public prototype_ `FHierarchyTableBlendProfile() = default;`
- L117 _public prototype_ `virtual ~FHierarchyTableBlendProfile() = default;`
- L119 _public prototype_ `FHierarchyTableBlendProfile(TObjectPtr<UHierarchyTable> InHierarchyTable, const EBlendProfileMode InMode);`
- L121 _public prototype_ `FHierarchyTableBlendProfile(const TObjectPtr<USkeleton> InSkeleton, const EBlendProfileMode InMode);`
- L124 _public prototype_ `virtual float GetBoneBlendScale(int32 InBoneIdx) const override;` — IBlendProfileInterface
- L125 _public prototype_ `virtual int32 GetNumBlendEntries() const override;`
- L126 _public prototype_ `virtual int32 GetPerBoneInterpolationIndex(const FCompactPoseBoneIndex& InCompactPoseBoneIndex, const FBoneContainer& BoneContainer, const IInterpolationIndexProvider::FPerBoneInterpolationData* Data) const override;`
- L127 _public prototype_ `virtual int32 GetPerBoneInterpolationIndex(const FSkeletonPoseBoneIndex InSkeletonBoneIndex, const USkeleton* TargetSkeleton, const IInterpolationIndexProvider::FPerBoneInterpolationData* Data) const override;`
- L128 _public prototype_ `virtual EBlendProfileMode GetMode() const override;`
- L129 _public prototype_ `virtual TObjectPtr<USkeleton> GetSkeleton() const override;`
- L131 _public prototype_ `const UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FCurveElement>& GetCurveBlendWeights() const;`
- L132 _public prototype_ `const TArray<FBlendProfileStandaloneCachedData::FMaskedAttributeWeight>& GetAttributeBlendWeights() const;`
- L134 _public prototype_ `void ConstructBlendProfile(const TObjectPtr<UBlendProfile> OutBlendProfile) const;`
- L136 _public prototype_ `bool IsValidBoneIndex(const int32 BoneIndex) const;`
- L139 _private member_ `TObjectPtr<USkeleton> Skeleton;`
- L141 _private member_ `TArray<float> BoneBlendWeights;`
- L143 _private member_ `UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FCurveElement> CurveBlendWeights;`
- L145 _private member_ `TArray<FBlendProfileStandaloneCachedData::FMaskedAttributeWeight> AttributeBlendWeights;`
- L147 _private member_ `EBlendProfileMode Mode = EBlendProfileMode::WeightFactor;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HIERARCHYTABLEANIMATIONRUNTIME_API`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Runtime/Public/MaskProfile/HierarchyTableTypeMask.h` (Public)


#### struct `FHierarchyTable_ElementType_Mask`  
`struct FHierarchyTable_ElementType_Mask final : public FHierarchyTable_ElementType`  
_L10-21_
- reflection: `USTRUCT(DisplayName = "Mask")`
- inherits: `FHierarchyTable_ElementType`
- L14 _public function_ `FHierarchyTable_ElementType_Mask() : Value(1.0f)`
- L20 _public member_ `float Value;` — `UPROPERTY()`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Runtime/Public/SkeletonHierarchyTableType.h` (Public)


#### struct `FHierarchyTable_TableType_Skeleton`  
`struct FHierarchyTable_TableType_Skeleton final : public FHierarchyTable_TableType`  
_L12-18_
- reflection: `USTRUCT(DisplayName = "Skeleton")`
- inherits: `FHierarchyTable_TableType`
- L17 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### enum `ESkeletonHierarchyTable_TablePayloadEntryType`  
`enum class ESkeletonHierarchyTable_TablePayloadEntryType`  
_L21-26_
- reflection: `UENUM()`
- L23 _public enumerator_ `Bone`
- L24 _public enumerator_ `Curve`
- L25 _public enumerator_ `Attribute`

#### struct `FHierarchyTable_TablePayloadType_Skeleton`  
`struct FHierarchyTable_TablePayloadType_Skeleton final : public FHierarchyTable_TablePayloadType`  
_L29-35_
- reflection: `USTRUCT()`
- inherits: `FHierarchyTable_TablePayloadType`
- L34 _public member_ `ESkeletonHierarchyTable_TablePayloadEntryType EntryType = ESkeletonHierarchyTable_TablePayloadEntryType::Bone;` — `UPROPERTY()`
